# Super Smash Bros Melee

This repo contains a WIP decompilation of Super Smash Bros Melee (US).

It builds the following DOL:

main.dol: `sha1: 08e0bf20134dfcb260699671004527b2d6bb1a45`

## Building

### Required tools

* [devkitPro](https://devkitpro.org/wiki/Getting_Started)
* Python3 (`pacman -S msys/python3`)
* gcc (`pacman -S gcc`)

### Instructions

1. Obtain a clean DOL of Melee 1.2 and place it in the base working directory and name it `baserom.dol`.
2. Obtain a copy of the MWCC (Build 158) PowerPC and place it in tools/mwcc_compiler/1.0/ folder in tools/. (NOTE: This compiler's executables [mwcceppc.exe mwasmeppc.exe and mwldeppc.exe] can be installed with Codewarrior 1.0 for Gamecube, but no license or crack is provided with this project. Please obtain access to the compiler on your own.) If you are in the Gamecube/Wii Decompilation discord (not public at this time, but if you are interested and have the skillset to contribute, please DM Revo#7090 on Discord for access), download GC_COMPILERS.zip and extract it to tools/mwcc_compiler/.
3. Run the `make` command

## Contributions

Contributions and PRs are welcome.
