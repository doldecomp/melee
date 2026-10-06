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
melee-dat symbols check-motions # packed animations against runtime motion tables
melee-dat types dump -n HSD_Joint   # a type as the tool sees it
melee-dat types duplicates  # records with the same layout under different names
melee-dat types unhoisted   # dat types declared in .c files
melee-dat types export -o types.bin # the types, for --types
melee-dat native codegen --out-dir schema # native schema
melee-dat native expect     # what the walk reaches, for native's tests
```

Run with `cargo run -rqp melee-dat -- <command> --dwarf build/ppc-dwarf/melee.elf`,
or `--types build/GALE01/dat/types.bin` (from the samples build; faster than
reading the DWARF).

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

They record them with `DAT_ROOTS` (in `dat_macros.h`), which declares a
witness of each destination's type, annotated with the name. An array
destination is loaded into its first element. A root is
untyped if its destination is `void*`, and skipped if its name isn't a
string literal or a global string.

Names the code builds at runtime go in `config/GALE01/dat_symbols.txt`,
used for publics no loader types. Lines are `name = dat:address;`, like
decomp-toolkit's `symbols.txt` with the dat in the section's place:

```text
*_figatree = Pl??AJ.dat:*; // type:FigaTree
ftDataEmblem_unused_joint = PlFe.dat:0x3AD70; // type:HSD_Joint
```

An address of `*` matches a public symbol by name. An address instead
gives a C alias for data no public symbol names, such as the root of data
nothing points to: it needs a dat (in a packed file, the first archive) and
a `type:`, and the walk starts there after the public symbols. Names and
dats take `*` and `?`. The first line with a matching archive
wins, then the first `*` line. The attributes mirror the annotations:
`type:T` like `DAT_TYPE(T)` (`T` or `T*`), and a count like `DAT_COUNT` and
`DAT_EXTENT`: `count:N`, or `extent` for as many as fit before the next
public symbol or pointer target, and `terminated:V` like
`DAT_TERMINATED(V)`. `script:TABLE`, like `DAT_SCRIPT(TABLE)`, makes an
address's root a command script. A count also applies where the loader already gives
the type, e.g. `map_plit = *:*; // terminated:0` for a null-terminated
list of `LightList*`. Raw data (textures, palettes) is
`type:u8 extent` or `type:u16 extent`, like the extracted blobs in
`config.yml`.

When a loader names roots through a global table, `DAT_BIND` on its name
field carries the table's context into each root's walk. For example, the
fighter loader indexes `ftData_803C1F40[kind].b`:

```c
struct StringPair {
    char* a;
    char* b DAT_BIND(fighter_kind, _index);
};
```

Expanding the name table binds `fighter_kind` to each element's index.
These values are retained in the compact types file and apply to the root
(including every element of an array root) and everything reached from it.
Expressions can use `_index`, macros, enum constants, and bindings from
earlier fields on the path. Unresolved bindings are omitted, as during the
archive walk. A field's `DAT_BIND` can shadow them; they don't carry over to
other roots. `ftData.x48_items` binds `item_index` to `_index`, so its C
pointer union selects Samus's grapple-beam accessory in slot 4, joints in
Link/Young Link slot 6, Kirby slot 4, Yoshi slot 3 and Sheik slots 4/5,
Game & Watch's visibility table in slot 10, Jigglypuff's costume parts in
slot 1, and an `Article` in the other slots.

## Samples

Samples check that the types explain the archives' data. Each archive is a
unit, sliced into a target object, and C generated from the current types
must compile its samples to the same bytes and relocations. The samples are
chosen across every archive: for each type (and each variant its tagged
unions choose), the fewest instances that together show every case its
fields take anywhere in the game. Cases are per field: a pointer null,
relocated, unrelocated or -1; a float zero, negative zero, positive,
negative, subnormal, infinite or NaN; an integer zero, positive, negative or
relocated; a bitfield zero or not; and nonzero padding. Instances the walk
found nothing wrong in come first. The rest of each archive is matched as
inferred data.

They build in their own CMake preset, in the native dev shell
(`nix develop .#native`):

```sh
cmake --preset dat
cmake --build --preset dat
melee-dat samples report build/GALE01/dat
```

`build/GALE01/dat` holds everything, and is an objdiff project. Each
archive is a unit `<module>/<archive>`, grouped by the two letters its name
starts with (`Pl/PlMr`, `Gr/GrFs`), under `dat/` in objdiff like the code's
`main/`:

- `melee.elf`: the DWARF build for that game version
- `types.bin`: its types, deduplicated once for every step
- `metadata/pick/<archive>.pick`: the instances chosen in each archive,
  rewritten only when they change
- `target/<unit>.o`: the whole archive, in two sections (objdiff lists
  them by name):
  - `.0.sampled`: the sampled objects, with pointers as relocations
  - `.1.inferred`: the rest of the archive, as uninitialized data, which
    objdiff never diffs bytes of: one symbol per piece, split wherever an
    object, public symbol or pointer target starts. The base defines the
    pieces the walk explains here too, so objdiff matches them by name and
    size; the rest show as missing. A piece is explained when it's typed
    data (an object up to its type's end, a script up to its end command)
    with no relocation the walk can't explain. Bytes a pointer says are
    bytes (`u8` texels, strings, keyframes) are explained up to the next
    object

  Each symbol's offset in the archive is its virtual address in a
  `.note.split`, as decomp-toolkit writes for split code; objdiff shows it.
  `target/<unit>.samples` says what each sample is; `target/<unit>.rest.o`
  is the base's `.1.inferred`
- `metadata/<unit>.types`: a hash of the types the archive's roots
  lead to, rewritten only when it changes, which the other steps depend on;
  `metadata/<unit>.formatted` records that the C is formatted
- `src/<unit>.h`: declares the archive's public symbols, typed by their
  roots, then its samples, the archive's externs and the other data they
  point to
- `src/<unit>.c`: only for a unit with samples: their designated
  initializers, generated from the types. Both are formatted in place with
  the repository's `.clang-format`
- `src/macros.h`: what the generated C includes (`LOCAL`), like
  dtk's `macros.inc`; from `samples macros`
- `base/<unit>.o`: that C, compiled with the DWARF build's flags, one
  section per variable (`obj/<unit>.o`), then linked with
  `target/<unit>.ld` and `target/<unit>.rest.o` into `.0.sampled` in the
  target's order (clang lays variables out where they are first pointed
  to, not where they are defined) and `.1.inferred`

`compile_commands.json` there gives clangd the same flags as the build;
clang-tidy is off for `src/`.

A unit is complete in objdiff only when the types explain every public
symbol and relocation without walk issues, and every symbol in the target's
`.1.inferred` section is also inferred in the base. Typing a symbol's start
alone does not make it complete if the rest of its data is unexplained.

Data is named as the archive names it (its public symbols, global in both
objects). Everything else is `LOCAL` (`static`, kept where nothing points to
it), named after the field the walk first reached it through, then its
offset: `child_x1A0`, `x1C_4_x2818`. Data the samples point to that isn't
written as C (elided: declared as the type the walk reached it as, spelled
as the pointers to it spell it, e.g. `Mtx`, `HSD_Joint x[2]`, `u16 x[256]`;
`UNK_T` where nothing typed reaches it or it was reached as several types)
is local in both objects too, but the C declares
it `extern`, so its name starts with its root to stay unique, e.g.
`ftDataMario_x0_common_attr_x3AC8`. The base's references to it stay
undefined; objdiff compares them by name. Externs, other archives' symbols the
loader links in, start with the unit's name (`GrFz_<extern>` in
`GrFz.dat`).

Each unit is five steps (`samples types`, `samples slice`, `samples
codegen`, format, compile), and `samples project` writes `objdiff.json`
from all of them; `samples macros` writes `src/macros.h`. The archives come
from `orig/GALE01/files` (`MELEE_DAT_FILES`); `MELEE_DAT` takes a prebuilt
`melee-dat`, else the build compiles it with cargo.

Configuration fails if `MELEE_DAT_FILES` contains no `.dat` archives.
Extract the game's files there first, or use an existing extraction with
`cmake --preset dat -DMELEE_DAT_FILES=/path/to/files`.

A pointer the type has as an integer is written as its raw value, so
objdiff shows the missing relocation; so does data in padding, or a float
that doesn't round-trip. A union is written through the member its tag
chose; a union object is declared as that member (`typeof(((union U *)
0)->member)`), since the archive only holds that member's bytes.

What to sample is up to you, in the build's cache: by default the chosen
instances above. `MELEE_DAT_SAMPLES_ALL` takes archive
globs whose every typed object becomes a sample, e.g.
`cmake --preset dat -DMELEE_DAT_SAMPLES_ALL="PlFx.dat;Gr*.dat"`, and
`MELEE_DAT_SAMPLES_EXCLUDE` type globs never to sample (data they point to
stays bytes), for records too bulky to want in C.

Use `samples report` for the verdict: objdiff's own report measures data
per section and misses relocation differences. To check a type change, edit
the header and rebuild the preset.

For decomp.dev, export an objdiff version-2 report instead:

```sh
melee-dat samples report --objdiff > build/GALE01/dat/report.json
```

Each unit represents an archive file, including all archives in a packed
file. `total_data` is its whole data region, rather than only its selected
samples. `matched_data` counts inferred non-sample pieces plus the bytes of
fully matching C samples, including their relocations. Partial sample scores
contribute only to `fuzzy_match_percent`. `complete` and `complete_data` describe
full inference, independently of sample matching. The existing `--json`
report retains its sample and weighted coverage measures.

Publish only this JSON as `GALE01-dat_report`, so DAT progress is a separate
version from the game's `GALE01_report`. CI's current build image has no
`.dat` files in `/orig/GALE01/files`; it needs extracted archives before it
can build the samples and publish their report.

In nix, `melee-dat-samples` is the same build, given the game's files in the
store:

```sh
nix store add --name melee-GALE01-files orig/GALE01/files
nix build .#melee-dat-samples
```

## Packed animation validation

`symbols check-motions` reads the fighter filenames and motion counts from
the linked game ELF, then checks each nonempty `ftData.xC` motion's file
offset, exact size and public `FigaTree` name against its `Pl*AJ.dat` archive.
It fails if a reference lands between archives, has the wrong size, or names
a symbol absent from that archive. Empty motions and shared references are
valid. Archives no motion references are reported and retained; padding need
not be zero.

```sh
melee-dat symbols check-motions --elf build/GALE01/main.elf --files orig/GALE01/files
```

The ELF needs its symbols and initialized data, but no DWARF. Counts come
from `ftData_Table_Unk0`, and the filenames from `ftData_803C1F40` and
`ftData_803C23E4`. This checks normal fighter animations; demo motion tables
and nested motion-file archives are separate follow-ups.

## Native archive interface

`native/` is a C library that reads archives into the game's own types on
any platform: the boundary between the GameCube's data (big-endian, 32-bit
pointers stored as offsets) and modern hardware and compilers.
`melee-dat native codegen` writes its schema from the types: a descriptor
for each type (`dat/schema.h`), as the archive lays it out, with where each
member goes natively, by `offsetof` and `sizeof`, so the host's compiler
decides the native layout. The library is a port of the walk
(`src/walk.rs`) that converts as it goes:

- scalars are byte-swapped and widened as their types say;
- pointers point to the native objects they reach, which are shared;
- counted, terminated and extent arrays are contiguous, with references to
  individual elements sharing their storage;
- unions are chosen by `DAT_IF`, as the walk chooses them.

Raw bytes and `DAT_BLOB` formats (texels, display lists, keyframes),
command scripts and untyped pointers stay as the archive has them, pointing
into a copy of its data (`dat_raw`). Externs are null, as the loader leaves
them, and -1 stays -1.

The schema is a directory of C, generated when configuring, in `schema/`
of the build:

- `melee_dat.h`: `melee_dat_schema`, and each type's index, `DAT_TYPE_*`
- `types/<header>.c`: the types a header of the game's declares, each a
  `dat_type_*` descriptor with its members, their annotations as written in
  comments, and what refers to them (pointers, arrays); `types/base.c` the
  types no header of the game's declares
- `roots/<module>.c`: each archive's roots, by module (`Pl`, `Gr`)
- `macros.c`, `scripts.c`: the macros the annotations use, and the code's
  tables of script command lengths
- `schema.c`: every type and name, by index

```c
static const DatMember struct_ftDynamics_x0_members[] = {
    { DAT_MEMBER(struct ftDynamics_x0, dynamicsNum, 0x0, DAT_TYPE_int) },
    /* dat:count(dynamicsNum) */
    {
        DAT_MEMBER(struct ftDynamics_x0, ftDynamicBones, 0x4, DAT_TYPE_BoneDynamicsTemplate_ptr),
        .count = DAT_NAME(dynamicsNum),
    },
};
```

```c
#include "melee_dat.h"

DatArchive* archive = dat_open(&melee_dat_schema, bytes, size, &error);
dat_load_roots(archive, "PlMr.dat", 0); // or every root dat-cli types
ftData* mario = dat_public(archive, "ftDataMario", DAT_TYPE_ftData);
dat_close(archive);
```

Load the roots before retaining native object pointers. Discovering an array
after an element was converted on its own can move that element into the
array's storage. Pointer fields in converted objects are updated; pointers
already returned to the caller cannot be updated.

The dat preset builds it with the host's compiler and runs its tests from
`ctest --test-dir build/GALE01/dat`; on its own, from the native dev shell:

```sh
cmake -S tools/dat-cli/native -B build/native/x86_64
cmake --build build/native/x86_64 && ctest --test-dir build/native/x86_64
```

With `-DCMAKE_TOOLCHAIN_FILE=tools/dat-cli/native/toolchains/i686.cmake`
for 32-bit little-endian, or `ppc32-linux.cmake` for 32-bit big-endian
under qemu.

- `tests/unit.c`: a hand-written schema over an archive built in the test.
- `tests/raw_refs.c`: shared raw references, relocated zero, externs and
  unselected union members.
- `tests/array_refs.c`: element identity in counted and nested arrays,
  differing host strides, cycles and mutations through shared references,
  with the array or its elements visited first.
- `tests/types.c`: the game's own types through the schema: each fighter's
  `ftData`, read by C member access, against the archive's bytes.
- `tests/e2e.c`: every archive the walk has roots in. `melee-dat native
  expect` prints what the walk reaches (objects, pointers, extents, union
  choices, issues); the library's `dat_trace` prints the same of its own
  walk, which must match line for line. Then `dat_verify` reads every
  native object back against the data.

## Annotations

For what C types can't express. From `libs/doldecomp/include/dat_macros.h`;
they compile to nothing outside the DWARF build. If a type is wrong, fix the
type instead.

| Annotation | Meaning |
| --- | --- |
| `DAT_COUNT(n)` | Array of, or pointer to, `n` elements. A fixed array's count must fit its declared bound. On a pointer typedef, `n` is in the bindings, for lists of counted lists. |
| `DAT_IF(cond)` | Union member is valid when `cond` holds; the first match wins, so a last `DAT_IF(true)` is a catch-all. |
| `DAT_TYPE(T)` | `void*` points to a `T`. Also on a `void*` typedef, for arrays of them. |
| `DAT_EXTENT` | Array, or pointer to elements, that runs as far as the data does. Stopgap for lengths only the code knows. |
| `DAT_BIND(T::f, value)` | `T::f` is `value` for everything reached through this member. |
| `DAT_SCRIPT(table)`, `DAT_SCRIPT(length)` | Pointer to a command script: opcode in the top 6 bits; opcodes 0-9 are the generic commands (`Command_Execute`), and the script's own from 10 are as long in words as `table` (an array in the code) says, or as `length`, an expression in `_command` (the command's first word), e.g. `itCommandLength(_command)`. Ends at opcode 0, or a command whose `length` is 0; relocated words point to more script. |
| `DAT_TERMINATED(value)` | Pointer to elements up to one whose first word (or whole value, if smaller) is `value` and not a relocated pointer: `0` for null-terminated lists, `GX_VA_NULL` for vertex descriptors, `-1` for `s8` lists. On a member, or on a pointer typedef for nested lists. `DAT_TERMINATED(value, n)`: the terminator is `n` elements long, for lists that end in it more than once. |
| `DAT_BLOB` | On a `u8` typedef: one format of bytes the archive doesn't break down: keyframe streams (`HSD_FObjData`), texels (`HSD_ImageData`), display lists (`HSD_DisplayList`). The size comes from the pointer, e.g. `DAT_COUNT(length)`. Raw `u8` data stays unexplained. |

Expressions are C. Names resolve to fields of the enclosing record, then
bindings, then macros and enum constants. `_index` is the element index
inside arrays and counted pointers. Float fields convert to integers as C
would. Calls are to functions of the code that the tool ports
(`interop/dwarf/expr.rs`), so an annotation can say what the game itself
computes: `GXGetTexBufferSize`.

```c
void* unk0 DAT_COUNT(unk4);
s32 unk4;

HSD_Spline* spline DAT_IF((flags & JOBJ_SPLINE) != 0);

HSD_ImageData* image_ptr DAT_COUNT(GXGetTexBufferSize(
    width, height, format, mipmap, maxLOD + 1));

Article** x4 DAT_COUNT(It_Kind_Section_Common_Extended_End) DAT_BIND(Article::kind, _index);
ItCapsuleAttr capsule DAT_IF(Article::kind == It_Kind_Capsule);
```

## Workflow

1. `symbols walk` or `symbols coverage`, pick a mismatch.
2. Fix the type in `src`, or annotate it.
3. `ninja` (must stay at 100%), then `cmake --build --preset dat` and
   `samples report`, or rebuild `ppc-dwarf` and walk again.

Known problems and coverage gaps are in `TODO.md`.

## Source

- `src/cmd/`: the commands.
- `src/config.rs`: `dat.yml`.
- `src/interop/dwarf.rs`: DWARF reader.
- `src/interop/dwarf/cache.rs`: the compact types file (`types export`).
- `src/interop/dwarf/canonical.rs`: dedupes types across compile units.
- `src/interop/dwarf/render.rs`: types as C.
- `src/interop/dwarf/annotation.rs`, `expr.rs`: annotation and expression parsers.
- `src/interop/dwarf/roots.rs`: roots from the loaders' records.
- `src/interop/hsd.rs`: archive format (mirrors `archive.c`, `lbarchive.c`).
- `src/walk.rs`: the walk.
- `src/coverage.rs`: gap, trailing and unreferenced relocations.
- `src/symbols.rs`: `dat_symbols.txt`.
- `src/samples.rs`: sample selection, target objects and C.
- `src/cmd/native.rs`: the native archive interface's tables, and what it
  should reach.
- `native/`: the native archive interface (C), its tests and toolchains.
