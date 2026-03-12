#!/bin/bash
# Find all C files with /// # stub markers and run find_stubs.py on them.
# Outputs combined JSON sorted by size.

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$REPO_ROOT"

# Find all .c files containing stub markers
FILES=$(grep -rl '/// #' src/melee/ --include='*.c' 2>/dev/null || true)

if [ -z "$FILES" ]; then
    echo "[]"
    exit 0
fi

python3 scripts/find_stubs.py $FILES
