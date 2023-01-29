#!/usr/bin/env bash

git ls-files -z |
    sed -z -E -e '/\.(sha1|png)$/d' -e '/\btools\/m2c\b/d' |
    while IFS= read -rd '' f; do
        tail -c1 <"$f" |
            read -r _ || echo >>"$f"
    done
