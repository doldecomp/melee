#!/usr/bin/env bash

function rename_module_symbols_asm {
    sed -rn 's/^(func|lbl)_([0-9A-F]{8})\b:$/\1_\2/pg' "$1" | while read line
    do
        new_line="$2_${line#*_}"
        replace_symbol "$line" "$new_line"
    done
}

function rename_module_symbols_c {
    sed -rn 's/^(static )?(inline )?(asm )?\w+\**\s+(func|lbl)_([0-9A-F]{8})\(.*\);?$/\4_\5/p' "$1" | while read line
    do
        new_line="$2_${line#*_}"
        replace_symbol "$line" "$new_line"
    done
}

function get_guard {
    local guard=$(echo "$1" | sed -e 's~/\|\.~_~g' -e 's/^src_//' -e 's/\w/\U\0/g')
    echo "$guard"
}

function get_include_guard {
    local guard=$(get_guard $1)
    echo "#ifndef $guard
#define $guard"
}

function rename_header {
    local old_guard=$(get_guard $1)
    local new_guard=$(get_guard $2)
    local find=$(realpath --relative-to="src" $1)
    local replace=$(realpath --relative-to="src" $2)
    mv "$1" "$2"
    sed -Ei -e "s@#(ifndef|define) [A-Z0-9_]+\$@#\1 $new_guard@" "$2"
    replace_symbol "$find" "$replace"
}

function gen_header {
    local out_base="$(basename $1)"
    local out_base="${out_base%.*}"
    local out_path="$(dirname $1)/$out_base.h"
    local guard=$(get_include_guard $out_path)
    local text="$guard

#include <Runtime/platform.h>

#endif"

    if [[ -f "$out_path" ]]; then
        printf '%s\n\n%s\n' "$text" "$(cat $out_path)" >$out_path
    else
        echo "$text" >$out_path
    fi
}

function convert_hex {
    perl -Mbigint -lpi -e 's{\b0x[\da-f]{1,7}U?\b}{hex($&)}gie' "$1"
}

alias qd='qalc -p 10'
alias qx='qalc -p 16'

export WINEDEBUG=-all
