#!/usr/bin/env bash
set -oeu pipefail

tr -d '\n' |
    sed -e 's/\s\+/ /g' -e 's/;/&\n/g' |
    sort -t\  -k1n |
    uniq |
    clang-format -
