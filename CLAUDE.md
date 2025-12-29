# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a decompilation project for Super Smash Bros. Melee (GameCube, US v1.02). The goal is to write C code that compiles to byte-identical PowerPC assembly using the original Metrowerks CodeWarrior compiler.

## Build Commands

```bash
# Initial setup (extract main.dol from game ISO to orig/GALE01/)
python configure.py    # Generate build.ninja
ninja                  # Build the project

# Diffing individual functions (use objdiff GUI tool)
# Download from https://github.com/encounter/objdiff
```

## Tooling Setup

```bash
python -m venv --upgrade-deps .venv
. .venv/bin/activate                    # Linux/macOS
pip install -r reqs/decomp.txt          # m2c decompiler + tools
```

## Decompilation Workflow

```bash
# Decompile a function using m2c
python tools/decomp.py <function_name>           # e.g., ftColl_8007B8CC
python tools/decomp.py <function_name> -c        # With syntax highlighting
python tools/decomp.py <function_name> -w        # Write output to source file

# Generate context for decomp.me
python tools/m2ctx/m2ctx.py
```

## Code Architecture

### Source Structure (`src/`)

The main game code is in `src/melee/` organized by two-letter module prefixes (from original HAL assert messages):

| Prefix | Module | Description |
|--------|--------|-------------|
| `cm` | Camera | Camera system |
| `db` | Debug | Debug utilities |
| `ef` | Effect | Visual effects |
| `ft` | Fighter | Player characters |
| `gm` | Game | Main game loop |
| `gr` | Ground | Stages/levels |
| `if` | Interface | UI elements |
| `it` | Items | Item logic |
| `lb` | Library | Utility wrappers |
| `mn` | Menu | Menu screens |
| `mp` | Map | Stage collisions |
| `pl` | Player | Player (user) data |
| `sc` | Scene | Game modes |
| `ty` | Toy | Trophies |
| `vi` | Visual | Cutscenes |

Fighter-specific code is in `src/melee/ft/chara/` with two-letter fighter abbreviations (e.g., `ftFx` = Fox, `ftMs` = Marth, `ftMr` = Mario).

### HAL's Object System (`src/sysdolphin/baselib/`)

Core library classes use single-letter prefixes:
- `GObj` - Game/Global Object (entity container)
- `JObj` - Joint (skeletal hierarchy)
- `DObj` - Draw/Display object
- `AObj` - Animation
- `CObj` - Camera
- `MObj` - Material
- `TObj` - Texture

### Other Libraries

- `src/dolphin/` - Dolphin SDK
- `src/MetroTRK/` - Metrowerks debugger
- `src/MSL/` - Metrowerks Standard Library
- `src/Runtime/` - Gekko hardware runtime

## Build Configuration

- `config/GALE01/symbols.txt` - Symbol names and addresses
- `config/GALE01/splits.txt` - Translation unit boundaries
- Compiler: `mwcc_247_92` with `-O4,p -inline auto -nodefaults`

## Coding Conventions

### Naming
- Function prefix matches filename: `lbVector_sin`, `ftFox_LaserOnDeath`
- Lower camel case for file prefix, upper camel case for function name

### Structs
```c
typedef struct Player {
    /* 0x00 */ u8 x0_thing;
    /* 0x04 */ u32 x4_filler[3];
    /* 0x10 */ u8 x10_thing;
};
```
Prefix struct fields with hex offset (e.g., `x0_`, `x4_`, `x10_`).

### Literals
- Unsigned: `123U`
- Float: `1.23F` (uppercase F, never bare `1.23`)
- Hex: `0xABC` (uppercase, lowercase x)
- Long: `123456L`, `123456LU`

### Formatting
Run `git clang-format` on staged files before committing.

### Conditionals
- Explicit NULL checks: `if (ptr != NULL)` not `if (!ptr)`
- Stub functions must have explicit `return;`

## Common Abbreviations

`cb` = callback, `coll` = collision, `cur` = current, `dmg` = damage, `dst` = destination, `ft` = fighter, `gr` = ground, `idx` = index, `it` = item, `kb` = knockback, `lr` = left/right (facing), `pos` = position, `src` = source, `vel` = velocity, `unk` = unknown
