git ls-files -z |
    sed -z -E '/\.(sha1|png)$/d' |
    while IFS= read -rd '' f; do
        tail -c1 <"$f" |
            read -r _ || echo >>"$f"
    done
