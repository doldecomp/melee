#!/bin/sh

SOURCES=$(find src -name '*.c' -or -name '*.h')

for file in $SOURCES; do
  clang @compile_flags.txt \
    -fno-color-diagnostics \
    -fsyntax-only \
    -ferror-limit=0 \
     "$file" 2>&1 \
    | grep -P '^.*?:\d+:\d+: (warning|error):.*'
done
