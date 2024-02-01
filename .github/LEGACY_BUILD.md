# Building with Make (legacy)

> [!CAUTION]
> It is recommended that you follow the ninja build instructions unless you have a specific reason to use Make.

## Windows

The easiest way to get set up is with [scoop](https://scoop.sh/). You will also need our compilers (linked below).

1. Open a PowerShell window (`Win+X`). You do not need admin privileges.
1. Install `scoop`, `git`, `python`, `mingw`, and `cmake`. You can skip these if you already have `git`, `python` (3.9+), `bash`, `gcc`, `make`, and `cmake` in your `PATH`.
    ```ps1
    Set-ExecutionPolicy RemoteSigned -Scope CurrentUser # Optional: Needed to run a remote script the first time
    irm get.scoop.sh | iex
    scoop install git python mingw cmake
    ```
1. Clone the repository and change directory into it.
    ```ps1
    cd ~/Documents # Or wherever you want to put Melee
    git clone 'https://github.com/doldecomp/melee.git'
    cd melee
    ```
1. Download our [compilers zip archive](https://mega.nz/file/BU43wKxT#rVC11Rl7DPxfSn7V9Iu--8E7m7gc1gsJWtfVBbfmKwQ) and rename the `GC` subfolder to `mwcc_compiler`, and place it in `/tools`. You can do this manually, or use the following PowerShell snippet (from inside your melee directory):
    ```ps1
    & scoop install megatools
    $url = 'https://mega.nz/file/BU43wKxT#rVC11Rl7DPxfSn7V9Iu--8E7m7gc1gsJWtfVBbfmKwQ'
    $zip = [System.IO.Path]::GetTempFileName() -replace '\.[^.]+$','.zip'
    & megatools dl --no-progress --path "$zip" "$url"

    $dir = New-Item -ItemType Directory `
        -Path (Join-Path $env:Temp 'MELEE_COMPILERS')

    Expand-Archive -Path $zip -DestinationPath $dir

    $path = Get-ChildItem -Path $dir.FullName | `
            Select-Object -ExpandProperty FullName
    Copy-Item -Path $path -Destination "tools/mwcc_compiler" -Recurse

    Remove-Item -Force $zip
    Remove-Item -Recurse -Force $dir

    # Optional: Uninstall megatools
    & scoop uninstall megatools
    ```
1. Run `make` using `bash` to build the project:
    ```ps1
    bash -c 'make -j"$NUMBER_OF_PROCESSORS" GENERATE_MAP=1'
    ```

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
  --user "$(id -u):$(id -g)" \
  --volume "$melee_path:/input:ro" \
  --volume "$build_target:/output" \
  --env MAKE_FLAGS="$make_flags" \
  ghcr.io/doldecomp/melee/build-linux:latest
```
