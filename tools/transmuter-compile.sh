#!/bin/bash
# Transmuter compile wrapper — replicates the `mwcc_sjis` ninja rule for a
# single preprocessed TU (ctx-style source file).
#
# Usage: transmuter-compile.sh <input.c> <output.o>
#
# Must be invoked with CWD set to the Melee repo root so the -i include paths
# resolve. Transmuter passes --cwd for this.

set -e

INPUT="$1"
OUTPUT="$2"

if [ -z "$INPUT" ] || [ -z "$OUTPUT" ]; then
    echo "usage: $0 <input.c> <output.o>" >&2
    exit 2
fi

MW_VERSION="GC/1.2.5n"
REPO="$(cd "$(dirname "$0")/.." && pwd)"

# Pick PE loader: on Linux x86_64/aarch64, prefer wibo if present (matches
# Melee's configure.py); otherwise fall back to wine.
case "$(uname -s)" in
    Linux)
        if [ -x "$REPO/build/tools/wibo" ]; then
            WRAPPER="$REPO/build/tools/wibo"
        elif command -v wibo >/dev/null 2>&1; then
            WRAPPER="wibo"
        else
            WRAPPER="wine"
        fi
        ;;
    *)
        WRAPPER="wine"
        ;;
esac

CFLAGS=(
    -nowraplines -cwd source -Cpp_exceptions off -proc gekko -fp hardware
    -align powerpc -nosyspath -fp_contract on -O4,p -multibyte -enum int
    -nodefaults -inline auto
    -pragma "cats off" -pragma "warn_notinlined off"
    -RTTI off -str reuse
    -DBUILD_VERSION=0 -DVERSION_GALE01
    -maxerrors 1 -msgstyle std -warn off -warn iserror
    -i src -i src/MSL -i src/Runtime -i extern/dolphin/include
    -i src/melee -i src/melee/ft/chara -i src/sysdolphin
    -lang=c
)

cd "$REPO"

exec "$WRAPPER" "build/tools/sjiswrap.exe" \
    "build/compilers/${MW_VERSION}/mwcceppc.exe" \
    "${CFLAGS[@]}" \
    -c "$INPUT" \
    -o "$OUTPUT"
