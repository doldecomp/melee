# Super Smash Bros Melee
[![build-melee](https://github.com/doldecomp/melee/actions/workflows/build-melee.yml/badge.svg)](https://github.com/doldecomp/melee/actions/workflows/build-melee.yml)
[![publish-packages](https://github.com/doldecomp/melee/actions/workflows/publish-packages.yml/badge.svg)](https://github.com/doldecomp/melee/actions/workflows/publish-packages.yml)
[![publish-pages](https://github.com/doldecomp/melee/actions/workflows/publish-pages.yml/badge.svg)](https://github.com/doldecomp/melee/actions/workflows/publish-pages.yml)
[![GC/Wii Decompilation](https://discordapp.com/api/guilds/727908905392275526/widget.png?style=shield)](https://discord.gg/hKx3FJJgrV)

This repo contains a WIP decompilation of Super Smash Bros Melee (US).

> [!TIP]
> The DOL this repository builds can be shifted! Meaning you are able to now add and remove code as you see fit, for modding or research purposes.

It builds `main.dol`:

|Version|Game ID|SHA-1
-|-|-
1.02|`GALE01`|`08e0bf20134dfcb260699671004527b2d6bb1a45`

# Dependencies

## Windows:
On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

## macOS:
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):
  ```
  brew install ninja
  ```
- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):
  ```
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

After OS upgrades, if macOS complains about `Wine Crossover.app` being unverified, you can unquarantine it using:
```sh
sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'
```

## Linux:
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- For non-x86(_64) platforms: Install wine from your package manager.
  - For x86(_64), [WiBo](https://github.com/decompals/WiBo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

# Building
- Clone the repository:
  ```
  git clone https://github.com/doldecomp/melee.git --depth=1
  ```
- Using [Dolphin Emulator](https://dolphin-emu.org/), find your ISO and click `Properties`. Go to the `Filesystem` tab, right-click `Disc - GALE01` and select `Extract System Data`. Choose `orig/GALE01` of this repository.
  - To save space, only `main.dol` (and `.gitkeep`) are necessary. Other files can be deleted.
  ![](assets/dolphin-extract.png)
- Configure:
  ```
  python configure.py
  ```
- Build:
  ```
  ninja
  ```

# Tooling

We use Python for our command line tooling. It is recommended that you use a [virtual environment](https://docs.python.org/3/library/venv.html).

1. Create a virtual environment.
    ```sh
    python -m venv --upgrade-deps '.venv'
    ```
1. You'll need to activate it whenever you open a new shell.
    * Windows:
        ```ps1
        .venv/Scripts/Activate.ps1
        ```
    * Linux/macOS:
        ```ps1
        . .venv/bin/activate
        ```
1. After that, you can install or update our packages with:
    ```sh
    pip install -r requirements.txt
    ```
1. Now you can run `decomp.py` to decomp a function using [m2c](https://github.com/matt-kempster/m2c). Pass it `-h` to see all the options.
    ```sh
    python tools/decomp.py my_function_name
    ```

# Modding
Coming soon.

# Containers
Coming soon.

# Building with Make (legacy)

See [Building with Make](LEGACY_BUILD.md).

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
