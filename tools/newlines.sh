#!/usr/bin/env bash

git ls-files -z |
    sed -z -E -e '/\.(sha1|png)$/d' -e '/\btools\/\b(m2c|calcprogress)\b/d' |
    while IFS= read -rd '' f; do
        tail -c1 <"$f" |
            read -r _ || echo >>"$f"
    done
