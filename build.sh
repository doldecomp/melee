#!/usr/bin/env bash

HERE=$(dirname "$(readlink -f $0)")
clean=false
rebuild_pattern=
expected=false
generate_map=0
non_matching=0
skip_check=0
frank=0
clear=false
log=false
dump=false
job_count=1
format=false

usage="$(basename "$0") [-hcefmnsxldp] [-r pattern] [-j threads]

where
    -h  help: show this message
    -c  clean: \"make clean\" before running make
    -r  rebuild: delete *.o files matching the given pattern; -c takes priority
    -e  expected: after a successful make run, sync ./build to ./expected/build
                  (requires \"pacman -S rsync\")
    -f  frank: pass EPILOGUE_PROCESS=1 to make
    -m  map: pass GENERATE_MAP=1 to make
    -n  non-matching: pass NON_MATCHING=1 to make
    -s  skip check: pass SKIP_CHECK=1 to make
    -x  clear: clear the console before executing this script
    -l  log: tee output to build.log
    -d  dump: dump the built dol to asm afterward
              (requires rust and \"cargo install --git https://github.com/InusualZ/dadosod\"
    -j  jobs: pass a number of threads to make
    -p  pretty: run \"make format\" before running make"

while getopts ":hcemnsfxldpr:j:" arg; do
    case $arg in
    h)
        echo "$usage"
        exit
        ;;
    c) clean=true ;;
    r) rebuild_pattern=$OPTARG ;;
    e) expected=true ;;
    m) generate_map=1 ;;
    n) non_matching=1 ;;
    s) skip_check=1 ;;
    f) frank=1 ;;
    x) clear=true ;;
    l) log=true ;;
    d) dump=true ;;
    j) job_count=$OPTARG ;;
    p) format=true ;;
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

if [ $clear = true ]; then
    clear
fi

pushd "$HERE"
build_time() {
    date +%T.%N
}

build() {
    echo
    echo "Build started at $(build_time)."

    if [ "$format" = true ]; then
        echo "Formatting."
        make format
    fi

    if [ "$clean" = true ]; then
        echo "Cleaning."
        make clean
    elif [ "$rebuild_pattern" ]; then
        rebuild_pattern="*/${rebuild_pattern}*.o"
        echo "Deleting files matching pattern $rebuild_pattern"
        find ./build -iwholename $rebuild_pattern -delete
    fi

    make_flags="NON_MATCHING=$non_matching GENERATE_MAP=$generate_map EPILOGUE_PROCESS=$frank SKIP_CHECK=$skip_check -j $job_count"
    echo "Running make with $make_flags"
    make $make_flags
    result=$?

    if [ "$result" != 0 ]; then
        echo "Build failed at $(build_time)."
    fi

    if [ -f './build/ssbm.us.1.2/GALE01.map' ]; then
        echo "Parsing map."
        python "tools/parse_map.py"
    fi

    if [ "$dump" = true ]; then
        echo "Dumping main.dol to dump."
        rm -rf dump
        mkdir -p dump
        dadosod dol "build/ssbm.us.1.2/main.dol" -m "build/map.csv" -o "dump"
    fi

    if [ "$expected" = true ] && [ "$result" = 0 ]; then
        echo "Syncing build to expected."
        mkdir -p build expected/build
        rsync -a --delete build/ expected/build/

        if [ "$dump" = true ]; then
            echo "Syncing dump to expected."
            mkdir -p dump expected/dump
            rsync -a --delete dump/ expected/dump/
        fi
    fi

    echo "Build finished at $(build_time)."
    exit "$result"
}

if [ "$log" = true ]; then
    build | tee -a build.log
else
    build
fi

popd
