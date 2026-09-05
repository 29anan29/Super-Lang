#!/usr/bin/env sh
# check-style.sh — quick, dependency-free style lint for the coding standard.
#
# Usage:
#   sh check-style.sh [--width=N] [--skip-header] <path> [<path> ...]
#
# Scans source files under <path> for the most common violations before/during
# a review. No network calls, no installed linters required. Exits non-zero if
# any issue is found.
#
# Checks:
#   - trailing whitespace on any line
#   - lines longer than --width (default 80)
#   - mixed leading indentation (both tabs and spaces in the indent run)
#   - editor modelines (vim:/ex: set, Emacs -*-) embedded in source
#   - (unless --skip-header) the first non-shebang line is a comment header
set -u

WIDTH=80
CHECK_HEADER=1

usage() {
  echo "usage: $0 [--width=N] [--skip-header] <path>..." >&2
  exit 2
}

# Print matching source files, one per line.
emit_sources() { # <root>
  find "$1" -type f \( -name '*.c' -o -name '*.h' -o -name '*.cpp' -o \
    -name '*.hpp' -o -name '*.cc' -o -name '*.cxx' -o -name '*.go' -o \
    -name '*.rs' -o -name '*.zig' -o -name '*.java' -o -name '*.kt' -o \
    -name '*.kts' -o -name '*.cs' -o -name '*.swift' -o -name '*.php' -o \
    -name '*.py' -o -name '*.js' -o -name '*.jsx' -o -name '*.ts' -o \
    -name '*.tsx' -o -name '*.rb' -o -name '*.dart' -o -name '*.scala' \)
}

check_file() { # <file> ; prints issues per line
  awk -v f="$1" -v W="$WIDTH" -v hd="$CHECK_HEADER" '
    {
      n++
      if ($0 ~ /[ \t]$/) { print "trailing-whitespace: " f ": " n }
      if (length($0) > W) { print "long-line: " f ": " n " (len " length($0) " > " W ")" }
      lead = $0
      sub(/[^ \t].*/, "", lead)          # keep only the leading indent run
      if (lead ~ / / && lead ~ /\t/) { print "mixed-indent: " f ": " n }
      if ($0 ~ /vim:/ || $0 ~ /ex: set/ || $0 ~ /-\*-/) {
        print "editor-modeline: " f ": " n
      }
      if (hd == 1 && !seen && !($0 ~ /^[ \t]*$/)) {
        seen = 1
        first = $0
        sub(/^[ \t]*/, "", first)
        c = substr(first, 1, 1)
        if (c != "#" && c != "/" && c != ";" && c != "\"")
          print "no-file-header: " f " (first code line is not a comment)"
      }
    }
  ' "$1"
}

while [ "$#" -gt 0 ] && [ "${1#-}" != "$1" ]; do
  case "$1" in
    --width=*) WIDTH="${1#--width=}" ;;
    --skip-header) CHECK_HEADER=0 ;;
    *) usage ;;
  esac
  shift
done

[ "$#" -lt 1 ] && usage

files=
for src in "$@"; do
  if [ -d "$src" ]; then
    files="$files
$(emit_sources "$src")"
  elif [ -f "$src" ]; then
    files="$files
$src"
  fi
done

total=0
if [ -n "$files" ]; then
  out="$(printf '%s\n' "$files" | sed '/^[[:space:]]*$/d' | while IFS= read -r f; do check_file "$f"; done)"
  [ -n "$out" ] && { printf '%s\n' "$out"; total="$(printf '%s\n' "$out" | grep -c . 2>/dev/null || true)"; }
fi

echo
echo "summary: $total issue(s) in scanned files"
[ "$total" -eq 0 ]