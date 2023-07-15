# Super Smash Bros Melee
[![GC/Wii Decompilation](https://discordapp.com/api/guilds/727908905392275526/widget.png?style=shield)](https://discord.gg/hKx3FJJgrV)
[![build-melee](https://github.com/doldecomp/melee/actions/workflows/build-melee.yml/badge.svg)](https://github.com/doldecomp/melee/actions/workflows/build-melee.yml)
[![publish-packages](https://github.com/doldecomp/melee/actions/workflows/publish-packages.yml/badge.svg)](https://github.com/doldecomp/melee/actions/workflows/publish-packages.yml)
[![publish-pages](https://github.com/doldecomp/melee/actions/workflows/publish-pages.yml/badge.svg)](https://github.com/doldecomp/melee/actions/workflows/publish-pages.yml)

This repo contains a WIP decompilation of Super Smash Bros Melee (US).

> **Note**
>
> The DOL this repository builds can be shifted! Meaning you are able to now add and remove code as you see fit, for modding or research purposes.

It builds the following DOL:

v1.02 - main.dol: `sha1: 08e0bf20134dfcb260699671004527b2d6bb1a45`

# Building

## Windows

The easiest way to get set up is with [scoop](https://scoop.sh/). You will also need our compilers (linked below).

1. Open a PowerShell window (`Win+X`). You do not need admin privileges.
1. Install `scoop`, `git`, `python`, and `mingw`. You can skip these if you already have `git`, `python` (3.9+), `bash`, `gcc`, and `make` in your `PATH`.
    ```ps1
    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser # Optional: Needed to run a remote script the first time
    irm get.scoop.sh | iex
    scoop install git python mingw
    ```
1. Clone the repository and change directory into it.
    ```ps1
    cd ~/Documents # Or wherever you want to put Melee
    git clone 'https://github.com/doldecomp/melee.git'
    cd melee
    ```
1. Download our [compilers zip archive](https://cdn.discordapp.com/attachments/727909624342380615/1129879865433264158/MELEE_COMPILERS_N.zip) and rename the `GC` subfolder to `mwcc_compiler`, and place it in `/tools`. You can do this manually, or use the following PowerShell snippet (from inside your melee directory):
    ```ps1
    $url = 'https://cdn.discordapp.com/attachments/727909624342380615/1129879865433264158/MELEE_COMPILERS_N.zip'
    $tmp = New-TemporaryFile
    Invoke-WebRequest -Uri $url -OutFile $tmp
    $zip = Rename-Item $tmp -NewName ($tmp.BaseName + '.zip') -PassThru

    $dir = New-Item -ItemType Directory `
        -Path (Join-Path $env:Temp 'MELEE_COMPILERS')

    Expand-Archive -Path $zip -DestinationPath $dir

    $path = Get-ChildItem -Path $dir.FullName | `
            Select-Object -ExpandProperty FullName
    Copy-Item -Path $path -Destination "tools/mwcc_compiler" -Recurse

    Remove-Item -Force $zip
    Remove-Item -Recurse -Force $dir
    ```
1. Run `make` using `bash` to build the project:
    ```ps1
    bash -c 'make -j"$NUMBER_OF_PROCESSORS" GENERATE_MAP=1'
    ```
1. Optional: Install a Python [virtual environment](https://docs.python.org/3/library/venv.html).
    If you want to use the Python tooling we have in `/tools`, you can create a `venv`. This tooling is not required to build the project, but you'll need it if you want to use `asm-differ`, `m2ctx`, etc.
    ```ps1
    python -m venv --upgrade-deps 'venv'
    ```
    * You'll need to activate it whenever you open a new shell.
        ```ps1
        venv/Scripts/Activate.ps1
        ```
    * After that, you can install or update our packages with:
        ```ps1
        pip install -r 'requirements.txt' --use-pep517
        ```
    * Now you can run `m2ctx` to get a context to use with [decomp.me](https://doldecomp.github.io/melee/getting_started.html#autotoc_md2). The following command will add it to your clipboard automatically; you can run with `--help` to see all the options:
        ```ps1
        python tools/m2ctx/m2ctx.py -px
        ```
1. Check out our [Getting Started guide](https://doldecomp.github.io/melee/getting_started.html)!

## Linux

### Requirements
* [devkitPro](https://devkitpro.org/wiki/Getting_Started)
* `python3` (`pacman -S python3`)
* `gcc` (`pacman -S gcc`)

### Instructions

1. Download [`MELEE_COMPILERS.zip`](https://cdn.discordapp.com/attachments/727909624342380615/1129879865433264158/MELEE_COMPILERS_N.zip) and extract the GC compilers to `tools/mwcc_compiler/`.
2. Run the `make` command:
    ```sh
    make -j$(nproc) GENERATE_MAP=1
    ```

You can refer to our [`Dockerfile`](/.github/packages/build-linux/Dockerfile) to see how our CI builds on Ubuntu.

## Containers

We offer containerized [Linux](https://github.com/doldecomp/melee/pkgs/container/melee%2Fbuild-linux) and [Windows](https://github.com/doldecomp/melee/pkgs/container/melee%2Fbuild-windows) build environments, which you can run through [`podman`](https://podman.io/getting-started/) or [`docker`](https://www.docker.com/get-started/) on any supported platform, including macOS.

```sh
melee_path="$PWD"
make_flags='GENERATE_MAP=1'
build_target="$melee_path/build"

docker run --rm \
  --volume "$melee_path:/input:ro" \
  --volume "$build_target:/output" \
  --env MAKE_FLAGS="$make_flags" \
  ghcr.io/doldecomp/melee/build-linux:latest
```

# Contributing

Contributions are welcome! If you're new to decomp, check out our [Getting Started guide](https://doldecomp.github.io/melee/getting_started.html). Before [opening a pull request](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request), please read our [contributing guidelines](CONTRIBUTING.md). If you're new to Git and don't know how to create a pull request, we encourage you to [create an issue](https://github.com/doldecomp/melee/issues/new) with your decomp.me link and a maintainer will add your code to the repository.

We're also happy to answer any questions in the `#melee` channel on Discord.

[![Gamecube/Wii Decompilation Discord](https://discordapp.com/api/guilds/727908905392275526/widget.png?style=banner2)](https://discord.gg/hKx3FJJgrV)

# FAQ
## What can be done after decompiling Melee?

Note that this project's purpose is to only match the ASM with C code. This is entirely for research and archival purposes. After this is created, you essentially have a C project that can be compiled into Melee, but it won't be portable (aka you can't compile it to run on a normal computer).

So creating mods would be a lot easier as C code is much easier to consume than ASM. However, there are additional projects that could be undertaken once this is complete, but those technical endeavours are out-of-scope for this repo.

## Do we know how the compiler works?

- Kind of. We don’t have its source though.

### How do we get the compiler to pick a certain register allocation?

Considering we don't have the source for the compiler, this is kind of "anything goes" territory. Unfortunately [register allocation is an NP-hard problem](https://en.wikipedia.org/wiki/Register_allocation?oldformat=true) which means there are all types of heuristics you can use to select registers, some of which can be confused by things as silly as variable names.

One option is to attempt to automatically [permute the source code](https://github.com/simonlindholm/decomp-permuter) to get the correct register allocation.
