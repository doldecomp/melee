git ls-files -z |
    while IFS= read -rd '' f; do
        tail -c1 <"$f" |
            read -r _ || echo >>"$f"
    done
