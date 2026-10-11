#!/usr/bin/env python3
"""docs/spec/diagnostics.md and the code tables of the sources agree.

  diagnostic_codes_tests.py SOURCE_ROOT

- Every runtime failure code (include/quidra/abi/runtime_failure.hpp), every
  error-value code (include/quidra/abi/error_record.hpp) and every
  compile-time code the frontend reports (error("CODE", ...) in src/) is
  documented: a row of diagnostics.md names it in backquotes.
- Every documented code is emitted somewhere: its spelling is a string of
  the sources.
- Every detail name, reason, mode and subject of an error-value schema (the
  closed lists of error_record.hpp) is documented with its code.
- UNHANDLED_ERROR is no longer emitted: no source names it, and
  diagnostics.md lists it only as removed.
"""
import pathlib
import re
import sys


# Documented codes that no source reports today, each with the reason its row
# stays: an explicit list, so that a new stale row still fails.
DOCUMENTED_NOT_REPORTED = {
    # Duplicate arguments report ARGUMENT_MISMATCH; the row is older than this
    # check and is left to the documentation of call arguments.
    "DUPLICATE_ARGUMENT",
}


def strings_of(text):
    return set(re.findall(r'"([A-Z][A-Z0-9]*(?:_[A-Z0-9]+)*)"', text))


def main():
    if len(sys.argv) != 2:
        print(__doc__.strip(), file=sys.stderr)
        return 2
    root = pathlib.Path(sys.argv[1])
    docs = (root / "docs/spec/diagnostics.md").read_text(encoding="utf-8")
    failure_header = (root / "include/quidra/abi/runtime_failure.hpp").read_text(encoding="utf-8")
    record_header = (root / "include/quidra/abi/error_record.hpp").read_text(encoding="utf-8")
    sources = [p for p in (root / "src").rglob("*") if p.suffix in (".cpp", ".hpp", ".inc", ".mm")]
    source_text = "\n".join(p.read_text(encoding="utf-8", errors="replace") for p in sources)
    source_text += failure_header + record_header

    documented = set(re.findall(r"^\| `([A-Z][A-Z0-9_]*)` \|", docs, re.MULTILINE))
    failures = []

    runtime_codes = re.findall(r'RuntimeFailureCodeInfo\{RuntimeFailureCode::\w+, "([A-Z0-9_]+)"\}',
                               failure_header)
    error_codes = re.findall(r'ErrorValueCodeInfo\{ErrorValueCode::\w+, "([A-Z0-9_]+)"', record_header)
    compile_codes = set()
    for path in sources:
        text = path.read_text(encoding="utf-8", errors="replace")
        compile_codes.update(re.findall(r'\berror\(\s*"([A-Z][A-Z0-9_]+)"', text))
    if not runtime_codes or not error_codes or not compile_codes:
        print("diagnostic_codes_tests: a code table was not found", file=sys.stderr)
        return 1

    for code in sorted(set(runtime_codes) | set(error_codes) | compile_codes):
        if code not in documented:
            failures.append(f"{code} is reported but has no row in diagnostics.md")
    emitted = strings_of(source_text) | {"ERROR"}
    for code in sorted(documented - DOCUMENTED_NOT_REPORTED):
        if code not in emitted:
            failures.append(f"{code} has a row in diagnostics.md but no source reports it")

    # The closed lists and the detail names of the error-value schemas.
    lists = dict(re.findall(r"inline constexpr std::array<std::string_view, \d+> (\w+)\{([^}]*)\}",
                            record_header))
    for name in ("file_reasons", "file_open_modes", "parse_reasons", "input_read_reasons",
                 "input_format_reasons", "conversion_subject_spellings",
                 "conversion_reason_spellings", "error_detail_names"):
        if name not in lists:
            failures.append(f"error_record.hpp has no list {name}")
            continue
        for spelling in re.findall(r'"([^"]+)"', lists[name]):
            if f"`{spelling}`" not in docs:
                failures.append(f"{spelling} ({name}) is not documented in diagnostics.md")

    if "UNHANDLED_ERROR" in strings_of(source_text):
        failures.append("UNHANDLED_ERROR is still named by a source")
    for line in docs.splitlines():
        if "UNHANDLED_ERROR" in line and "removed" not in line.lower():
            failures.append("diagnostics.md names UNHANDLED_ERROR other than as removed: " + line)
    if "UNHANDLED_ERROR" in documented:
        failures.append("UNHANDLED_ERROR has a row of a code still reported")

    if failures:
        for failure in failures:
            print("diagnostic_codes_tests: " + failure, file=sys.stderr)
        return 1
    print(f"diagnostic_codes_tests: {len(documented)} documented codes agree with the sources")
    return 0


if __name__ == "__main__":
    sys.exit(main())
