HERE=$(dirname "$(readlink -f $0)")
ctx_includes="ctx_includes.h"
ctx=ctx.c
includes=false
pattern=
clear=false
log=false
generate=false

usage="$(basename "$0") [-hicgxl] [-p pattern]

where
    -h  help: show this message
    -i  includes: regenerate $ctx_includes
    -c  context: regenerate $ctx
    -g  generate: run m2c and output each asm file to ./src/<original path>/<filename>.s.c
    -p  pattern: restrict generation paths to a given pattern
    -x  clear: clear the console before executing this script
    -l  log: tee output to gen.log"

while getopts ":hgicp:xl" arg; do
    case $arg in
    h)
        echo "$usage"
        exit
        ;;
    g) generate=true ;;
    i) includes=true ;;
    c) context=true ;;
    p) pattern=$OPTARG ;;
    x) clear=true ;;
    l) log=true ;;
    :)
        printf "missing argument for -%s\n" "$OPTARG" >&2
        echo "$usage" >&2
        exit 1
        ;;
    \?)
        printf "illegal option: -%s\n" "$OPTARG" >&2
        echo "$usage" >&2
        exit 1
        ;;
    esac
done

if [ "$clear" = true ]; then
    clear
fi

pushd "$HERE"

go() {
    out_path="$(echo "$1" | sed 's/asm/src/').c"
    mkdir -p $(dirname "$out_path")
    echo "Generating code from $1 to $out_path"
    (
        echo "#include <$ctx_includes>"$'\n'
        python tools/m2c/m2c.py -t ppc-mwcc-c --valid-syntax --context "./src/$ctx" "$1"
    ) |
        cat >"$out_path"
}

gen() {
    if [ "$includes" = true ]; then
        echo "Generating $ctx_includes."

        (
            echo -e "#pragma region include"
            find include/ src/ -type f -name "*.h" |
                sed -r -e "/include\/$ctx_includes/d" -e 's/((include|src)\/)?(.*)/#include <\3>/'
            echo -e "#pragma endregion\n\n#pragma region m2c_macros\n"
            cat ./tools/m2c/m2c_macros.h
            echo -e "\n#pragma endregion"
        ) |
            cat >"include/$ctx_includes"
    fi

    if [ "$context" = true ]; then
        result=$(python tools/m2ctx/m2ctx.py "include/$ctx_includes")
        if [ $? != 0 ]; then
            exit $?
        fi
        echo "$result" | cat >"src/$ctx"
    fi

    if [ "$generate" = true ]; then
        pattern="*/${pattern}*.s"
        find ./asm -iwholename "$pattern" -print0 | while IFS= read -r -d '' file; do go "$file"; done
    fi
}

if [ "$log" = true ]; then
    gen | tee -a gen.log
else
    gen
fi

popd
