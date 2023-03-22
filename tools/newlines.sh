#!/usr/bin/env bash
set -euo pipefail

git ls-files -z |
    sed -z -E -e '/\.(sha1|png)$/d' -e '/\btools\/m2c\b/d' |
    while IFS= read -rd '' f; do
        if [ -e "$f" ]; then
            tail -c1 <"$f" |
                read -r _ || echo >>"$f"
        fi
    done
