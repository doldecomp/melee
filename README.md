# Super Smash Bros Melee

This repo contains a WIP decompilation of Super Smash Bros Melee (US).

```diff
- INFORMATION! -

The DOL this repository builds can be shifted! Meaning you are able to now
add and remove code as you see fit, for modding or research purposes.
```

It builds the following DOL:
v1.02 - main.dol: `sha1: 08e0bf20134dfcb260699671004527b2d6bb1a45`

# Building

## Required tools

* [devkitPro](https://devkitpro.org/wiki/Getting_Started)
* Python3 (`pacman -S msys/python3`)
* gcc (`pacman -S gcc`)

## Instructions

1. Download GC_WII_COMPILERS.zip from (https://cdn.discordapp.com/attachments/727918646525165659/917185027656286218/GC_WII_COMPILERS.zip) and extract the GC compilers to tools/mwcc_compiler/.
2. Run the `make` command

# Contributing

If you're new to decomp or getting started, check out our [Getting Started guide](GETTING_STARTED.md)! Once you're in a place that you're ready to open a PR, check out our [Contributing guidelines](CONTRIBUTING.md).

# FAQ
## What can be done after decompiling Melee?

Note that this project's purpose is to only match the ASM with C code. This is entirely for research and archival purposes. After this is created, you essentially have a C project that can be compiled into Melee, but it won't be portable (aka you can't compile it to run on a normal computer).

So creating mods would be a lot easier as C code is much easier to consume than ASM. However, there are additional projects that could be undertaken once this is complete, but those technical endeavours are out-of-scope for this repo.

## Do we know how the compiler works?

- Kind of. We don’t have its source though.

### How do we get the compiler to pick a certain register allocation?

Considering we don't have the source for the compiler, this is kind of "anything goes" territory. Unfortunately [register allocation is an NP-hard problem](https://en.wikipedia.org/wiki/Register_allocation?oldformat=true) which means there are all types of heuristics you can use to select registers, some of which can be confused by things as silly as variable names.

One option is to attempt to automatically [permute the source code](https://github.com/simonlindholm/decomp-permuter) to get the correct register allocation.

### How do I set up the source permuter?

TODO


## Contributions

Gamecube/Wii Decompilation Discord: https://discord.gg/hKx3FJJgrV

Contributions and PRs are welcome.

