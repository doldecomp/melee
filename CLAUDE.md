# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

WIP decompilation of Super Smash Bros. Melee (NTSC 1.02, GALE01). The goal is to write C code that compiles to binary-identical PowerPC assembly as the original game. Success = 100% match with the original DOL.

## Build Commands

```bash
python3 configure.py    # Generate build.ninja and objdiff.json
ninja                   # Build main.dol
ninja diff              # Show differences vs original
```

Dependencies: Python 3.11+, Ninja, Metrowerks CodeWarrior compiler (in container), Wine Crossover (macOS), Wine/WiBo (Linux).

### macOS Setup

```bash
brew install ninja
brew install --cask --no-quarantine gcenx/wine/wine-crossover
```

After OS upgrades, re-unquarantine Wine: `sudo xattr -rd com.apple.quarantine '/Applications/Wine Crossover.app'`

### Python Tools

```bash
python -m venv --upgrade-deps .venv
. .venv/bin/activate
pip install -r reqs/decomp.txt
python tools/decomp.py function_name    # Decompile a function (use -h for options)
```

## Code Style

Enforced by `.clang-format`. Run `git clang-format` on staged files before committing.

- 4 spaces, 79 column limit, LF line endings
- Left-aligned pointers: `int* ptr`
- Explicit NULL checks: `if (ptr != NULL)` not `if (!ptr)`
- Literals: `123U` (u32), `1.23F` (f32), `1.23L` (f64), `0xABC` (hex)
- Empty stubs: `{}` not `{ return; }`
- Struct members prefixed with hex offset: `/* 0x10 */ u8 x10_thing;`

### Naming

Functions are prefixed with their file name: `ftCo_Attack100_Enter`, `lbVector_sin`, `ftFox_LaserOnDeath`. File names use lowerCamelCase, function names use UpperCamelCase. Standard library reimplementations use lowercase.

### Module Prefixes

- `ft` = fighter, `it` = item, `gr` = ground/stage, `gm` = game, `lb` = library
- `cm` = camera, `db` = debug, `ef` = effect, `if` = interface, `mn` = menu
- `mp` = map/collision, `pl` = player, `sc` = scene, `ty` = trophy, `vi` = visual

### Common Abbreviations

accel, atk (attack), cb (callback), coll (collision), dmg (damage), dst (destination), ecb (environmental collision box), ev (entity variables), grav (gravity), idx (index), kb (knockback), lr (left/right facing), mag (magnitude), mv (motion variables), phys (physics), pos (position), sfx (sound effect), spd (speed), vel (velocity), unk (unknown)

## Architecture

```
src/
├── melee/           # Game code
│   ├── ft/          # Fighter system (largest subsystem)
│   │   └── chara/   # Character-specific code (ftCommon/, ftFox/, etc.)
│   ├── gr/          # Stage code
│   ├── it/          # Items
│   ├── gm/          # Game loop
│   ├── lb/          # Utility library
│   ├── sc/          # Scene/game mode management
│   └── ...
├── sysdolphin/baselib/  # HAL's core library (GObj, HSD framework)
├── dolphin/             # Dolphin SDK
├── MSL/                 # Metrowerks Standard Library
└── Runtime/             # Gekko hardware runtime
```

Key config files:
- `config/GALE01/symbols.txt` — All 34k+ symbols and addresses
- `config/GALE01/splits.txt` — Object file section mappings
- `configure.py` — Build configuration and object matching status

## Decompilation Workflow

1. Find target function address in `config/GALE01/symbols.txt`
2. Decompile assembly to C (using `python tools/decomp.py`, m2c, or decomp.me)
3. Iterate until `objdiff` shows 100% match
4. Run `ninja` to verify no regressions

### Diffing with objdiff

After building, `objdiff.json` is generated. Use [objdiff](https://github.com/encounter/objdiff) to visually compare objects. Enable "Relax relocation diffs" in Diff Options. Auto-rebuilds on source changes.

### Game Files

Extract `main.dol` from a GALE01 ISO (via Dolphin Emulator) to `orig/GALE01/`.

## Notes on Making Matches

- Aim for **true matches** (code the developer would have written, e.g. `var->x3[i*2] = 3`) over **fake matches** (technically matching slop, e.g. `*(s16*) var+x3+i*2 = 3`).
- Avoid raw pointer arithmetic — the original devs most likely didn't use it.
- Convert `i=0; do { ...; i++; } while (i<10)` into `for (i=0; i<10; i++) { ... }`.
- Avoid `goto`/labels — use control flow (`if`, `for`, `while`) instead.
- For struct fields, label with local hex offset: `struct { /* 0x00 */ u16 x00; /* 0x02 */ u16 x02; }`. Optionally add global offset if relevant.
- **Ignore register swaps** — if all instances of a register in the target map to a different register in our code, count it as matched (solved later via permuter).
- When the stack is off by `n` bytes, use `PAD_STACK(n);` at the end of the stack.
- Use `ABS(n)` for `x=n; if(x>0) x=-x` patterns.
- Use `MIN(n,m)` / `MAX(n,m)` for clamping patterns.
- New structs should be proper structs (not `extern u8[]`). Follow the naming scheme above and use `u8 pad_xx[n]` for padding.
- To access fields inside `pad[...]`, split the pad: `pad_xx[n], var_to_use, pad_yy[m]`.

## Fighter Character Codes

Mr (Mario), Lg (Luigi), Kb (Kirby), Pk (Pikachu), Ss (Samus), Lk (Link), Fx (Fox), Dk (Donkey Kong), Kp (Bowser), Pe (Peach), Ys (Yoshi), Fc (Falco), Ms (Marth), Gn (Ganondorf), Mt (Mewtwo), Zd (Zelda), Sk (Sheik), Pr (Jigglypuff), Cl (Young Link), Dr (Dr. Mario), Fe (Roy), Ca (Captain Falcon), Ns (Ness), Pc (Pichu)

## Decomp Permuter

[decomp-permuter](https://github.com/simonlindholm/decomp-permuter) automatically permutes C source to find better matches. Supports PowerPC.

```bash
# Setup (in permuter repo)
python3 -m pip install pynacl toml Levenshtein

# For ninja-based projects, create permuter_settings.toml at project root:
# build_system = "ninja"

# Import a function to permute
./import.py <path/to/file.c> <path/to/file.s>

# Run (use -j for multithreaded)
./permuter.py -j directory/
```

Score of 0 = perfect match. Use `PERM_GENERAL(a, b, ...)` macros in source to test specific alternatives. `PERM_RANDOMIZE(code)` enables random variations in a region. Best when only regalloc differences remain — pick sensible suggestions from results.

## CI

GitHub Actions builds in `ghcr.io/doldecomp/build-melee:main` container. Validates both "link" mode (compiles and links) and "diff" mode (no regressions vs base branch).
