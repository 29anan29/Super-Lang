#!/bin/bash
# Check style: trailing whitespace, over-long lines, mixed indentation, editor modelines.
# Usage: ./scripts/check-style.sh [directory]

DIR="${1:-src}"
errors=0

# Check for trailing whitespace
if grep -rn '[[:space:]]$' "$DIR" --include='*.c' --include='*.h' 2>/dev/null; then
    echo "FAIL: Trailing whitespace found"
    errors=$((errors + 1))
fi

# Check for lines > 100 chars
if grep -rn '^.\{101,\}' "$DIR" --include='*.c' --include='*.h' 2>/dev/null; then
    echo "FAIL: Lines over 100 columns found"
    errors=$((errors + 1))
fi

# Check for mixed tabs/spaces (lines with both)
if grep -rnP '\t.*[ ]{2,}|[ ]{2,}\t' "$DIR" --include='*.c' --include='*.h' 2>/dev/null; then
    echo "FAIL: Mixed tabs and spaces found"
    errors=$((errors + 1))
fi

# Check for editor modelines
if grep -rn 'vim:\|emacs:\|-.*mode:' "$DIR" --include='*.c' --include='*.h' 2>/dev/null; then
    echo "FAIL: Editor modelines found"
    errors=$((errors + 1))
fi

# Check for file headers
for f in $(find "$DIR" -name '*.c' -o -name '*.h'); do
    if ! head -1 "$f" | grep -q '^\s*/\*'; then
        echo "FAIL: Missing file header in $f"
        errors=$((errors + 1))
    fi
done

if [ $errors -eq 0 ]; then
    echo "PASS: No style violations found"
else
    echo "FAIL: $errors style violation(s) found"
fi

exit $errors
