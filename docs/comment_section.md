# CodeWarrior `.comment` section

Files built with `mwcc` contain a `.comment` section:

```
$ powerpc-eabi-readelf -We object.o

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .text             PROGBITS        00000000 000034 000708 00  AX  0   0  4
  ...
  [16] .comment          PROGBITS        00000000 00153b 0001b4 01      0   0  1
```

The `.comment` section contains information that `mwld` uses during linking, primarily symbol alignment and a "force active" / export flag.

If missing, `mwld` will **not** adjust the alignment of symbols or remove any unused symbols.

This behavior is quite useful in some cases. When we split our program into objects, we're working from the final post-aligned, post-stripped result, and don't want the linker to make any changes. Most decompilation projects rely on this behavior unintentionally, since their generated objects don't contain a `.comment` section. (For example, objects built with `powerpc-eabi-as`.)

However, we need the `.comment` section for some purposes:

- Reproducing the [common BSS inflation bug](common_bss.md#inflation-bug) requires the `.comment` section present, due to the above. The linker inflates the size of the first common BSS symbol in a TU, but won't actually move any data around unless the `.comment` section is present.
- In newer versions of the linker, using common BSS at all _without_ a valid `.comment` section will cause an internal linker error.

When the `.comment` section is generated, decomp-toolkit will mark all global symbols as "exported" to prevent any deadstripping, since the presence of the `.comment` section itself enables deadstripping.

Generating the `.comment` section and setting the "export" flag is also useful to prevent the linker from removing entire objects. A missing `.comment` section will prevent the removal of unused symbols _inside_ of an object, but the linker will still remove the entire object itself if it thinks it's unused.

## Contents

The contents of this section follow a very simple format:

### Header

`[0x0 size: 0xB]` Magic: `43 6F 64 65 57 61 72 72 69 6F 72` ("CodeWarrior")  

`[0xB size: 0x1]` Version(?): `XX`

It's not known whether this field actually affects `mwld` in any way, but it's configurable for completeness sake. (See `mw_comment_version` in [`config.example.yml`](/config/GAMEID/config.example.yml).)

Known values:

- `08` (8) - CodeWarrior for GameCube 1.0+
- `0A` (10) - CodeWarrior for GameCube 1.3.2+
- `0B` (11), `0C` (12) - CodeWarrior for GameCube 2.7+ (difference unknown)
- `0E` (14), `0F` (15) - CodeWarrior for GameCube 3.0a3+ (difference unknown)

`[0xC size: 0x4]` Compiler version: `XX XX XX XX`

First 3 bytes are major, minor, and patch version numbers.  
4th byte is unknown, but is always `01`.

Example: `Version 2.3.3 build 144` -> `02 03 00 01`  
Often the `.exe`'s properties (which `--help` reads from) and the internal version number (here) will differ.

`[0x10 size: 1]` Pool data: `XX`

- `00` - Data pooling disabled
- `01` - Data pooling enabled

`[0x11 size: 1]` Float type: `XX`

- `00` - Floating point disabled
- `01` - Software floating point
- `02` - Hardware floating point

`[0x12 size: 2]` Processor type: `00 16` (Gekko)

`[0x14 size: 1]` Unknown, always `2C`. Possibly the start of symbol entries.

`[0x15 size: 1]` "Quirk" flags: `XX`

Bitfield of miscellaneous flags. Known flags:

- `01` - "Incompatible return small structs"
- `02` - "Incompatible SFPE double params"
- `04` - "Unsafe global reg vars"

`[0x16 size: 22]` Padding until `0x2C`

### Symbol entry

At `0x2C` is the first symbol entry. There is one 8 byte entry per ELF symbol.

This includes the "null" ELF symbol, so the first entry will be all 0's.

`[0x0 size: 4]` Alignment: `XX XX XX XX`

`[0x4 size: 1]` Visibility flags(?): `XX`

Known values:

- `00` - Default
- `0D` - Weak
- `0E` - Unknown, also weak?

`[0x5 size: 1]` Active flags(?): `XX`

Known values:

- `00` - Default
- `08` - Force active / export. Prevents the symbol from being deadstripped.  
  When applied on a section symbol, the entire section is kept as-is. This is used
  by `mwcc` when data pooling is triggered (indicated by a symbol like `...data.0`), likely to prevent the hard-coded section-relative offsets from breaking.  
  Can also be set using `#pragma force_active on` or `__declspec(export)`.
- `10` - Unknown
- `20` - Unknown

`[0x6 size: 2]` Padding(?): `00 00`
