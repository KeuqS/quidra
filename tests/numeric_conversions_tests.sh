#!/usr/bin/env bash
set -euo pipefail
QUIDRA="$(realpath "$1")"
ROOT="$(realpath "$2")"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
"$QUIDRA" build "$ROOT/tests/numeric_conversions.qui" -o "$TMP/conversions"
"$TMP/conversions" > "$TMP/actual"
diff -u "$ROOT/tests/numeric_conversions.expected" "$TMP/actual"
