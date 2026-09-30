# dat-cli

Types the contents of `.dat` archives using the decomp's own types, and
reports where they don't match the data.

Types are read from the DWARF build. The symbols the code loads by name are
the roots; from each root, the walk follows pointer fields through the
archive and checks them against its relocation table.

## Setup

In the nix devshell:

```sh
cmake --preset ppc-dwarf
cmake --build --preset ppc-dwarf
```

This produces `build/ppc-dwarf/melee.elf`. Pass it with `--dwarf`, or set
`MELEE_DWARF_ELF`. Archives are read from `orig/GALE01/files`
(see `config/GALE01/dat.yml`).

## Commands

```sh
melee-dat symbols coverage  # how much of the archives the walk explains
melee-dat symbols walk    # walk every archive, print mismatches
melee-dat symbols roots   # symbols loaded by name, with their types
melee-dat symbols check   # root types against the archives' symbol sizes
melee-dat types dump -n HSD_Joint   # a type as the tool sees it
```

Run with `cargo run -rqp melee-dat -- <command> --dwarf build/ppc-dwarf/melee.elf`.

`walk` reports:

- **unrelocated pointer**: a pointer field holds a non-null value that isn't
  relocated. The field probably isn't a pointer, or the struct is wrong.
- **relocated scalar**: a non-pointer field is relocated. It's probably a
  pointer.
- **ambiguous union**: no member of a union could be picked.
- **reached as several types**: the same object is reached through fields of
  different types.

Each line includes the path from the root symbol.

## Coverage

`symbols coverage` walks the archives and counts the relocations the walk
explains. The rest are one of:

- **gap**: inside a typed object, or in data a pointer reaches. A type is
  missing or wrong.
- **trailing**: after the end of a typed object, where nothing points. The
  type is too short, or the data after it is unreferenced.
- **unreferenced**: nothing reaches it from a public symbol.

`reachable` is the explained share of the relocations that aren't
unreferenced.

```sh
melee-dat symbols coverage                    # by archive family
melee-dat symbols coverage --by archive       # archives with the largest gaps
melee-dat symbols coverage --by owner         # gaps by the object they follow
melee-dat symbols coverage --by field         # void* fields not followed
melee-dat symbols coverage --by public        # public symbols with no type
melee-dat symbols coverage -a 'Pl??.dat'      # only matching archives
melee-dat symbols coverage -a PlMr.dat --list # every unexplained relocation
melee-dat symbols coverage --format json      # everything, like objdiff's report.json
melee-dat symbols coverage --format markdown  # the tables, for a PR or issue
```

`--top N` limits table rows (default 25, 0 for all). The JSON report has
`measures`, `units` (archives, with their gaps by owner, untyped publics and
fields) and `categories` (families). `--list` adds each unit's unexplained
relocations.

## Roots

The loaders record what they load in the DWARF build:

- `lbArchive_LoadSymbols` and the other `lbArchive` loaders, from the
  `(&dst, "name")` pairs.
- `HSD_ArchiveGetPublicAs(type, archive, name)`, a typed
  `HSD_ArchiveGetPublicAddress`.

A root is untyped if its destination is `void*`, and skipped if its name
isn't a string literal or a global string.

Names the code builds at runtime go in `config/GALE01/dat_symbols.txt`,
used for publics no loader types:

```text
*_figatree = Pl??AJ.dat; // type:FigaTree
```

Names and archives take `*` and `?`. The first line with a matching archive
wins, then the first `*` line. Types can be `T`, `T*`, `T[N]`, or `T[]` for
as many as fit before the next public symbol or pointer target. Raw data
(textures, palettes) is typed as `u8[]` or `u16[]`, like the extracted
blobs in `config.yml`.

## Samples

Samples check that the types explain the archives' data. Each archive is a
unit: its best-typed instance of each type (and of each variant its tagged
unions choose) is sliced into a target object, and C generated from the
current types must compile to the same bytes and relocations.

They build in their own CMake preset, in the dev shell:

```sh
cmake --preset dat
cmake --build --preset dat
melee-dat samples report build/GALE01/dat
```

`build/GALE01/dat` holds everything, and is an objdiff project:

- `melee.elf`: the DWARF build for that game version
- `types.bin`: its types, deduplicated once for every step
- `target/<archive>.o`: the sampled objects from the archive, named as the
  archive names them (its public symbol, else `x<OFFSET>`), with pointers as
  relocations; `target/<archive>.samples` says what each is
- `src/<archive>/<root>.{h,c}`: per root of the archive (the public
  symbol its samples were reached from), a header declaring its samples and
  the other data they point to, and designated initializers generated from
  the types; pointers into other roots include those roots' headers
- `src/<archive>.c`: the unit, which includes every root's source; all of
  `src` is generated into `gen` and formatted with the repository's
  `.clang-format`
- `base/<archive>.o`: that C, compiled with the DWARF build's flags

`compile_commands.json` there gives clangd the same flags as the build.

Each unit is four steps (`samples slice`, `samples codegen`, format,
compile), and `samples project` writes `objdiff.json` from all of them. The archives come
from `orig/GALE01/files` (`MELEE_DAT_FILES`); `MELEE_DAT` takes a prebuilt
`melee-dat`, else the build compiles it with cargo.

A pointer the type has as an integer is written as its raw value, so
objdiff shows the missing relocation; so does data in padding, or a float
that doesn't round-trip. A union is written through the member its tag
chose; a union object is declared as that member (`typeof(((union U *)
0)->member)`), since the archive only holds that member's bytes.

Use `samples report` for the verdict: objdiff's own report measures data
per section and misses relocation differences. To check a type change, edit
the header and rebuild the preset.

In nix, `melee-dat-samples` is the same build, given the game's files in the
store:

```sh
nix store add --name melee-GALE01-files orig/GALE01/files
nix build .#melee-dat-samples
```

## Annotations

For what C types can't express. From `libs/doldecomp/include/dat_macros.h`;
they compile to nothing outside the DWARF build. If a type is wrong, fix the
type instead.

| Annotation | Meaning |
| --- | --- |
| `DAT_COUNT(n)` | Pointer to `n` elements. |
| `DAT_IF(cond)` | Union member is valid when `cond` holds. |
| `DAT_TYPE(T)` | `void*` points to a `T`. Also on a `void*` typedef, for arrays of them. |
| `DAT_EXTENT` | Array, or pointer to elements, that runs as far as the data does. Stopgap for lengths only the code knows. |
| `DAT_BIND(T::f, value)` | `T::f` is `value` for everything reached through this member. |
| `DAT_SCRIPT(table, len...)` | Pointer to a command script: opcode in the top 6 bits, lengths in words from the listed values, then from `table` in the code. Ends at opcode 0; relocated words point to more script. |
| `DAT_NULLTERM` | Pointer to elements up to one whose first word is zero. On a member, or on a pointer typedef for nested lists. |

Expressions are C. Names resolve to fields of the enclosing record, then
bindings, then macros and enum constants. `_index` is the element index
inside arrays and counted pointers.

```c
void* unk0 DAT_COUNT(unk4);
s32 unk4;

HSD_Spline* spline DAT_IF((flags & JOBJ_SPLINE) != 0);

Article** x4 DAT_COUNT(It_Kind_Monster_Start) DAT_BIND(Article::kind, _index);
ItCapsuleAttr capsule DAT_IF(Article::kind == It_Kind_Capsule);
```

## Workflow

1. `symbols walk`, pick a mismatch.
2. Fix the type in `src`, or annotate it.
3. `ninja` (must stay at 100%), rebuild `ppc-dwarf`, walk again.

Known problems and coverage gaps are in `TODO.md`.

## Source

- `src/interop/dwarf.rs`: DWARF reader.
- `src/interop/dwarf/canonical.rs`: dedupes types across compile units.
- `src/interop/dwarf/annotation.rs`, `expr.rs`: annotation and expression parsers.
- `src/interop/dwarf/roots.rs`: roots from the loaders' records.
- `src/interop/hsd.rs`: archive format (mirrors `archive.c`, `lbarchive.c`).
- `src/walk.rs`: the walk.
- `src/coverage.rs`: gap, trailing and unreferenced relocations.
- `src/symbols.rs`: `dat_symbols.txt`.
- `src/samples.rs`: sample selection, target objects and C.
