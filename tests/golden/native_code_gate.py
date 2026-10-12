#!/usr/bin/env python3
"""Code identity with metadata, and the scope of tail-record changes.

Each input is compiled once in each mode. These are structural checks;
the step exit measurement owns timing. No benchmark source is rewritten.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys


def run(args, **kwargs):
    result = subprocess.run([str(a) for a in args], text=True, capture_output=True, **kwargs)
    if result.returncode:
        raise RuntimeError(f'{args[0]} failed:\n{result.stdout}{result.stderr}')
    return result.stdout


def info(tool, artifact):
    return json.loads(run([tool, artifact]))


def driver():
    # A test-only compiler driver, selected through the existing native
    # toolchain override. The production CLI gains no gate options.
    args = sys.argv[2:]
    inputs = [Path(arg) for arg in args if arg.endswith('.ll')]
    stdin_ir = '-c' in args and '-' in args
    changed = '-c' in args and (stdin_ir or len(inputs) == 1 and inputs[0].name != 'calls.ll')
    if changed and not stdin_ir:
        shutil.copyfile(os.environ['QUIDRA_GATE_IR'], inputs[0])
    if not changed and '-c' not in args and os.environ.get('QUIDRA_GATE_CAPTURE_LINK') == '1':
        capture = Path(os.environ['QUIDRA_GATE_OBJECT'] + '.inputs')
        capture.mkdir()
        module = Path(os.environ['QUIDRA_GATE_OBJECT'] + '.source').read_text()
        for index, arg in enumerate(args):
            source = Path(arg)
            if str(source) == module or source.suffix not in ('.a', '.lib', '.o', '.obj'):
                continue
            if source.is_file():
                destination = capture / (str(index) + source.suffix)
                if source.suffix in ('.a', '.lib'):
                    digest = hashlib.sha256(source.read_bytes()).hexdigest()
                    cache = Path(os.environ['QUIDRA_GATE_LINK_CACHE']) / (digest + source.suffix)
                    if not cache.is_file():
                        shutil.copyfile(source, cache)
                    os.link(cache, destination)
                else:
                    shutil.copyfile(source, destination)
    if '-c' not in args:
        args = ['--driver-mode=g++', *args]
    if stdin_ir:
        with Path(os.environ['QUIDRA_GATE_IR']).open('rb') as source:
            result = subprocess.run([os.environ['QUIDRA_GATE_DRIVER'], *args], stdin=source)
    else:
        result = subprocess.run([os.environ['QUIDRA_GATE_DRIVER'], *args])
    if result.returncode == 0 and changed:
        output = Path(args[args.index('-o') + 1])
        shutil.copyfile(output, os.environ['QUIDRA_GATE_OBJECT'])
        Path(os.environ['QUIDRA_GATE_OBJECT'] + '.source').write_text(str(output))
    raise SystemExit(result.returncode)


def relocation_mask(metadata, relocation):
    _, kind, size, _, _, _ = relocation
    machine, format_name = metadata['machine'], metadata['format']
    if machine == 'arm64' and format_name == 'macho':
        masks = {2: 0x03ffffff, 3: 0x60ffffe0, 4: 0x003ffc00,
                 5: 0x60ffffe0, 6: 0x003ffc00, 8: 0x60ffffe0, 9: 0x003ffc00, 10: 0}
        if kind in masks and size == 4:
            return masks[kind].to_bytes(4, 'little')
        if kind in (0, 1, 7):
            return bytes([255]) * size
    if machine == 'x86_64':
        supported = {'macho': {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                     'elf': {1, 2, 4, 9, 10, 11, 24, 41, 42},
                     'coff': set(range(1, 10)) | {11}}
        if kind in supported[format_name] and size in (2, 4, 8):
            return bytes([255]) * size
    raise RuntimeError(f'unsupported code relocation: {format_name}/{machine}/{kind}/{size}')


def linked_inputs(tool, ar, capture, archive_cache):
    variants = {}
    def add(metadata):
        for symbol, function in metadata['functions'].items():
            identity = dict(code=function['code'], relocations=function['relocations'], machine=metadata['machine'], format=metadata['format'])
            variants.setdefault(symbol, []).append(identity)
    for artifact in sorted(capture.iterdir()):
        if artifact.suffix not in ('.a', '.lib'):
            add(info(tool, artifact))
            continue
        state = artifact.stat()
        cache_key = (state.st_dev, state.st_ino)
        if cache_key in archive_cache:
            for metadata in archive_cache[cache_key]:
                add(metadata)
            continue
        member_metadata = []
        members = run([ar, 't', artifact]).splitlines()
        if len(set(members)) != len(members):
            raise RuntimeError(f'duplicate archive member names: {artifact}')
        extracted = capture / (artifact.name + '.members')
        extracted.mkdir()
        for index, member in enumerate(members):
            result = subprocess.run([str(ar), 'p', str(artifact), member], capture_output=True)
            if result.returncode:
                raise RuntimeError(f'cannot read archive member {member}')
            data = result.stdout
            if not (data.startswith((b'\x7fELF', b'\xcf\xfa\xed\xfe')) or data[:2] in (b'\x64\x86', b'\x64\xaa')):
                continue
            path = extracted / (str(index) + '.o')
            path.write_bytes(data)
            metadata = info(tool, path)
            member_metadata.append(metadata)
            add(metadata)
        archive_cache[cache_key] = member_metadata
    identities = {symbol: sorted(items, key=lambda item: json.dumps(item, sort_keys=True))
                  for symbol, items in variants.items()}
    functions = {}
    for symbol, items in identities.items():
        first = items[0]
        # Duplicate private names may refer to different local constants.
        # A field is still proven relocated when every possible input
        # has the same raw code and relocation field shape. Keep all
        # target identities for the before/after comparison.
        def shape(item):
            return (item['code'], item['machine'], item['format'],
                    [relocation[:-1] for relocation in item['relocations']])
        if all(shape(item) == shape(first) for item in items):
            functions[symbol] = first
    return functions, identities


def disassembly(objdump, artifact, functions):
    # Bytes outside an actual input-object relocation remain exact. This
    # includes local branches, instruction opcodes and register operands.
    output = run([objdump, '--disassemble', artifact])
    symbols = {}
    for line in run([objdump, '--syms', artifact]).splitlines():
        fields = line.split()
        if len(fields) > 2 and re.fullmatch(r'[0-9a-fA-F]+', fields[0]) and fields[-1] in functions:
            symbols.setdefault(int(fields[0], 16), []).append(fields[-1])
    section = ''
    name = ''
    base = 0
    source = None
    masks = {}
    instructions = []
    for line in output.splitlines():
        match = re.match(r'Disassembly of section (.+):', line)
        if match:
            section = match[1]
            continue
        match = re.match(r'^([0-9a-fA-F]+) <(.+)>:$', line)
        if match:
            base = int(match[1], 16)
            names = symbols.get(base, [])
            name = match[2] if match[2] in functions else (names[0] if len(names) == 1 else match[2])
            source = functions.get(name)
            masks = {}
            if source:
                for relocation in source['relocations']:
                    offset = relocation[0]
                    for index, byte in enumerate(relocation_mask(source, relocation)):
                        masks[offset + index] = masks.get(offset + index, 0) | byte
            continue
        match = re.match(r'^\s*([0-9a-fA-F]+):\s+((?:[0-9a-fA-F]{2}(?:\s+|$))+|[0-9a-fA-F]{8}\s+)', line)
        if not match:
            continue
        address = int(match[1], 16)
        fields = match[2].split()
        raw = int(fields[0], 16).to_bytes(4, 'little') if len(fields) == 1 and len(fields[0]) == 8 else bytes.fromhex(''.join(fields))
        offset = address - base
        normalized = bytes(byte & ~masks.get(offset + index, 0) for index, byte in enumerate(raw))
        instructions.append((section, name, offset, normalized.hex()))
    if not instructions:
        raise RuntimeError(f'no code disassembled from {artifact}')
    return instructions


def code_sizes(objdump, artifact):
    sections = {}
    for line in run([objdump, '--section-headers', artifact]).splitlines():
        row = re.match(r'\s*\d+\s+(\S+)\s+([0-9a-fA-F]+)\s+', line)
        if row and (row[1] == '__text' or row[1].startswith('.text')):
            sections[row[1]] = int(row[2], 16)
    if not sections:
        raise RuntimeError(f'no code section sizes read from {artifact}')
    return sections


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mode', choices=('object', 'executable', 'scope'))
    parser.add_argument('--quidra', required=True, type=Path)
    parser.add_argument('--golden', required=True, type=Path)
    parser.add_argument('--info', required=True, type=Path)
    parser.add_argument('--clang', required=True, type=Path)
    parser.add_argument('--objdump', type=Path)
    parser.add_argument('--ar', type=Path)
    parser.add_argument('--out', required=True, type=Path)
    parser.add_argument('inputs', nargs='+', type=Path)
    args = parser.parse_args()
    for key in ('quidra', 'golden', 'info', 'clang'):
        setattr(args, key, getattr(args, key).resolve())
    if args.mode == 'executable' and (args.objdump is None or args.ar is None):
        parser.error('executable mode requires --objdump and --ar')
    args.out.mkdir(parents=True, exist_ok=True)
    link_cache = args.out.resolve() / 'link-cache'
    link_cache.mkdir()
    archive_cache = {}
    # The shell launcher passes every compiler argument literally.
    launcher = args.out.resolve() / 'driver'
    import shlex
    launcher.write_text('#!/bin/sh\nexec ' + shlex.quote(sys.executable) + ' ' +
                        shlex.quote(str(Path(__file__).resolve())) + ' --driver "$@"\n')
    launcher.chmod(0o755)
    for index, source in enumerate(args.inputs):
        source = source.resolve()
        work = args.out.resolve() / str(index)
        work.mkdir()
        views = 'llvm,llvm.no-calls,llvm.no-tail-records,tail-recorded-functions'
        run([args.golden, '--out', work / 'views', '--views', views, source], cwd=source.parent)
        before_view = 'llvm.no-tail-records' if args.mode == 'scope' else 'llvm.no-calls'
        after_view = 'llvm' if args.mode == 'scope' else 'llvm.no-tail-records'
        objects = []
        executables = []
        for label, view in (('before', before_view), ('after', after_view)):
            ir = work / 'views' / view
            if not ir.is_file():
                raise RuntimeError(f'{view} unavailable for {source}')
            object_path = work / (label + '.o')
            executable = work / label
            env = dict(os.environ, QUIDRA_CLANGXX=str(launcher),
                       QUIDRA_GATE_DRIVER=str(args.clang), QUIDRA_GATE_IR=str(ir),
                       QUIDRA_GATE_OBJECT=str(object_path),
                       QUIDRA_GATE_CAPTURE_LINK='1' if args.mode == 'executable' else '0',
                       QUIDRA_GATE_LINK_CACHE=str(link_cache))
            run([args.quidra, 'build', source, '-o', executable], cwd=source.parent, env=env)
            if not object_path.is_file():
                raise RuntimeError('the module compilation was not intercepted')
            objects.append(info(args.info, object_path))
            executables.append(executable)
        before, after = objects
        if args.mode == 'object':
            if before['machine'] != after['machine'] or before['sections'] != after['sections']:
                raise RuntimeError(f'code or code relocations changed: {source}')
        elif args.mode == 'executable':
            if before['machine'] != after['machine'] or before['sections'] != after['sections']:
                raise RuntimeError(f'input code or relocation identities changed: {source}')
            linked = []
            identities = []
            for label, metadata in (('before', before), ('after', after)):
                functions, input_identities = linked_inputs(args.info, args.ar, work / (label + '.o.inputs'), archive_cache)
                identities.append(input_identities)
                functions.update({symbol: dict(code=metadata['sections'], relocations=function['relocations'], machine=metadata['machine'], format=metadata['format'])
                                  for symbol, function in metadata['functions'].items()})
                linked.append(functions)
            if identities[0] != identities[1]:
                raise RuntimeError(f'linked object identities changed: {source}')
            left = disassembly(args.objdump, executables[0], linked[0])
            right = disassembly(args.objdump, executables[1], linked[1])
            if code_sizes(args.objdump, executables[0]) != code_sizes(args.objdump, executables[1]) or left != right:
                raise RuntimeError(f'linked instructions changed: {source}')
        else:
            recorded = set((work / 'views' / 'tail-recorded-functions').read_text().splitlines())
            allowed = recorded | {'_' + name for name in recorded}
            for metadata in (before, after):
                for symbol, function in metadata['functions'].items():
                    if function['logical'] in recorded or set(function['inlined']) & recorded:
                        allowed.add(symbol)
            changed = []
            for symbol in sorted(before['functions'].keys() | after['functions'].keys()):
                left = before['functions'].get(symbol)
                right = after['functions'].get(symbol)
                if left is not None and right is not None:
                    if (left['code'], left['relocations']) == (right['code'], right['relocations']):
                        continue
                changed.append(symbol)
                if symbol not in allowed:
                    raise RuntimeError(f'tail records changed an unrelated function {symbol}: {source}')
            print(f'{source.name}: {len(recorded)} recorded functions; {len(changed)} changed functions')
        print(f'{args.mode}: {source.name} passed', flush=True)


if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] == '--driver':
        driver()
    else:
        main()
