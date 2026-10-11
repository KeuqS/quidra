#!/usr/bin/env python3
"""Regenerate the embedded CUDA kernel from the shared half/complex source."""
import argparse
from pathlib import Path
import re
import subprocess
import tempfile

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--clang', default='clang++')
args = parser.parse_args()
root = Path(__file__).resolve().parents[1]
header = (root / 'src/device_numeric_kernel.inc').read_text()
body = header.split('R"QNUM(\n', 1)[1].split('\n)QNUM";', 1)[0]
native = (root / 'include/quidra/native_extension.h').read_text()
dtypes = re.search(r'enum qcore_dtype\s*\{.*?\};', native, re.S).group()
with tempfile.TemporaryDirectory() as directory:
    source = Path(directory) / 'numeric.cu'
    assembly = Path(directory) / 'numeric.ptx'
    codes = (root / 'include/quidra/abi/tensor_codes.hpp').read_text().replace('#pragma once', '')
    source.write_text(dtypes + '\n' + codes + '\n' + body)
    subprocess.run([args.clang, '-target', 'x86_64-unknown-linux-gnu', '-x', 'cuda',
                    '--cuda-device-only', '-nocudainc', '-nocudalib', '--cuda-gpu-arch=sm_50',
                    '-O2', '-ffp-contract=off', '-S', str(source), '-o', str(assembly)], check=True)
    ptx = '\n'.join(line.split('//', 1)[0].rstrip() for line in assembly.read_text().splitlines())
    ptx = '\n'.join(line for line in ptx.splitlines() if line.strip()) + '\n'
    if re.search(r'^\s*\.extern\b', ptx, re.M):
        raise RuntimeError('The CUDA kernel must have no external device-library dependency')
    chunks = []
    current = ''
    for line in ptx.splitlines(keepends=True):
        if len(current) + len(line) > 30000:
            chunks.append(current)
            current = ''
        current += line
    if current:
        chunks.append(current)
    text = ('// Generated from device_numeric_kernel.inc. Regenerate with generate_numeric_ptx.py.\n'
            'const std::string& numeric_kernel_ptx() {\n'
            '    static const std::string code = [] {\n        std::string result;\n')
    for chunk in chunks:
        text += '        result += R"QPTX(\n' + chunk + ')QPTX";\n'
    text += '        return result;\n    }();\n    return code;\n}\n'
    (root / 'src/device_numeric_ptx.inc').write_text(text)
