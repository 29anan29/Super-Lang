#!/bin/bash
# Apply canonical formatters to source files.
# Usage: ./scripts/apply-format.sh [directory]

DIR="${1:-src}"

if command -v clang-format &> /dev/null; then
    find "$DIR" -name '*.c' -o -name '*.h' | xargs clang-format -i 2>/dev/null
    echo "clang-format applied to $DIR"
else
    echo "clang-format not found; skipping C formatting"
fi

echo "Format complete."
