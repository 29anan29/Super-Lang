#!/usr/bin/env sh
# apply-format.sh — run the idiomatic formatter for the given files/dirs.
#
# Usage:
#   sh apply-format.sh <path> [<path> ...]
#
# Picks a formatter per file extension across many languages. Any formatter
# that is not on PATH is skipped with a warning; files without a matching
# formatter are skipped with a note. No network calls.
set -eu

if [ "$#" -lt 1 ]; then
  echo "usage: $0 <path> [<path> ...]" >&2
  exit 2
fi

missing() {
  echo "WARNING: '$1' not found on PATH; skipping matching files" >&2
}

has() { command -v "$1" >/dev/null 2>&1; }

format_one() { # <file>
  case "$1" in
    *.c|*.h|*.cpp|*.hpp|*.cc|*.cxx)   has clang-format        && clang-format -i "$1"                 || missing clang-format ;;
    *.go)                             has gofmt              && gofmt -w "$1"                       || missing gofmt ;;
    *.rs)                             has rustfmt            && rustfmt --edition 2021 "$1" 2>/dev/null || missing rustfmt ;;
    *.zig)                            has zig                && zig fmt "$1"                        || missing zig ;;
    *.java)                           has google-java-format && google-java-format --replace "$1"    || missing google-java-format ;;
    *.kt|*.kts)                       has ktlint             && ktlint format "$1"                   || missing ktlint ;;
    *.cs)                             has dotnet             && dotnet format "$1" 2>/dev/null       || missing dotnet ;;
    *.swift)                          has swift-format       && swift-format -i "$1"                 || missing swift-format ;;
    *.php)                            has php-cs-fixer       && php-cs-fixer fix "$1" 2>/dev/null    || missing php-cs-fixer ;;
    *.py)                             has black              && black -q "$1"                        || missing black ;;
    *.js|*.jsx|*.ts|*.tsx)            has prettier           && prettier --write "$1" 2>/dev/null    || missing prettier ;;
    *.rb)                             has rubocop            && rubocop -A "$1" 2>/dev/null          || missing rubocop ;;
    *.dart)                           has dart               && dart format "$1"                     || missing dart ;;
    *.scala)                          has scalafmt           && scalafmt --stdout < "$1" > "$1.cs.tmp" \
                                                               && mv "$1.cs.tmp" "$1" \
                                                               || missing scalafmt ;;
    *)                                echo "skip (no formatter): $1" ;;
  esac
}

for src in "$@"; do
  if [ -d "$src" ]; then
    # Recurse on this script per matched file so the case logic runs in one
    # shell invocation; POSIX sh cannot export functions into a subshell.
    find "$src" \( -name '*.c'  -o -name '*.h'    -o -name '*.cpp' -o -name '*.hpp' -o \
                    -name '*.cc' -o -name '*.cxx' -o -name '*.go'   -o -name '*.rs'   -o \
                    -name '*.zig' -o -name '*.java' -o -name '*.kt' -o -name '*.kts' -o \
                    -name '*.cs'  -o -name '*.swift' -o -name '*.php' -o -name '*.py' -o \
                    -name '*.js'  -o -name '*.jsx'  -o -name '*.ts'  -o -name '*.tsx' -o \
                    -name '*.rb'  -o -name '*.dart' -o -name '*.scala' \) -print0 \
      | xargs -0 -r -n1 "$0"
    continue
  fi
  format_one "$src"
done