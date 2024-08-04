# Dolphin SDK 2001 Libraries

Decompilation of the archive library files of the 5/22/2001 version of the Dolphin SDK. **This repository does not provide a complete copy of that version of the SDK.** This repo is focusing on the built code libraries within this version and is *not a complete replacement.*

## Compatibility

Currently this repository supports building the following libraries:

:heavy_check_mark: = 100% Complete
:warning: = In Progress, at least 1 or more files done.
:x: = No code yet

| Library Name | Progress |
| ------------ | ---------- |
| ai           | :heavy_check_mark: |
| amcnotstub   | :heavy_check_mark: |
| amcstubs     | :heavy_check_mark: |
| ar           | :heavy_check_mark: |
| ax           | :heavy_check_mark: |
| axfx         | :heavy_check_mark: |
| base         | :heavy_check_mark: |
| card         | :heavy_check_mark: |
| db           | :heavy_check_mark: |
| demo         | :heavy_check_mark: |
| dolformat    | :heavy_check_mark: |
| dsp          | :heavy_check_mark: |
| dtk          | :heavy_check_mark: |
| dvd          | :heavy_check_mark: |
| fileCache    | :heavy_check_mark: |
| G2D          | :heavy_check_mark: |
| gx           | :heavy_check_mark: |
| hio          | :heavy_check_mark: |
| mcc          | :heavy_check_mark: |
| mix          | :heavy_check_mark: |
| mtx          | :heavy_check_mark: |
| odemustubs   | :heavy_check_mark: |
| odenotstub   | :heavy_check_mark: |
| os           | :heavy_check_mark: |
| pad          | :heavy_check_mark: |
| perf         | :heavy_check_mark: |
| seq          | :heavy_check_mark: |
| support      | :heavy_check_mark: |
| syn          | :heavy_check_mark: |
| texPalette   | :heavy_check_mark: |
| vi           | :heavy_check_mark: |

## Preparation

After cloning the repo, you can copy your copies of the .a files to baserom/ and run `make extract` to disassemble these files to source files with DTK.

The build process requires the following packages:

- build-essential
- binutils-powerpc-linux-gnu

Under Debian / Ubunutu you can install them with the following commands:

```bash
sudo apt update
sudo apt install build-essential
```

If building any Dolphin SDK Libraries you can install binutils-powerpc-linux-gnu with:

```bash
sudo apt install binutils-powerpc-linux-gnu
```

Running `make` will then setup DTK if necessary and build all supported libraries.
