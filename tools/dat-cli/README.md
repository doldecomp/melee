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

## Roots

The loaders record what they load in the DWARF build:

- `lbArchive_LoadSymbols` and the other `lbArchive` loaders, from the
  `(&dst, "name")` pairs.
- `HSD_ArchiveGetPublicAs(type, archive, name)`, a typed
  `HSD_ArchiveGetPublicAddress`.

A root is untyped if its destination is `void*`, and skipped if its name
isn't a string literal or a global string.

## Annotations

For what C types can't express. From `libs/doldecomp/include/dat_macros.h`;
they compile to nothing outside the DWARF build. If a type is wrong, fix the
type instead.

| Annotation | Meaning |
| --- | --- |
| `DAT_COUNT(n)` | Pointer to `n` elements. |
| `DAT_IF(cond)` | Union member is valid when `cond` holds. |
| `DAT_TYPE(T)` | `void*` points to a `T`. |
| `DAT_EXTENT` | Array runs as far as the data does. Stopgap for lengths only the code knows. |
| `DAT_BIND(T::f, value)` | `T::f` is `value` for everything reached through this member. |
| `DAT_NULLTERM` | Pointer to elements up to a zeroed one. |

Expressions are C. Names resolve to fields of the enclosing record, then
bindings, then macros and enum constants. `_index` is the element index
inside arrays and counted pointers.

```c
void* unk0 DAT_COUNT(unk4);
s32 unk4;

HSD_Spline* spline DAT_IF((flags & JOBJ_SPLINE) != 0);

Article** x4 DAT_COUNT(It_Kind_Kuriboh) DAT_BIND(Article::kind, _index);
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
- `samples`, `src/symbols.rs`: unfinished.
