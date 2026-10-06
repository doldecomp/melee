# TODO

## Samples

- The stage `*_YakumonoParam` structs aren't reachable (`void*` in the
  stage info) and differ per stage: `dat_symbols.txt` types them by archive.
- A union object whose tag chooses no member has no sample (`CmdUnion`,
  which is a script; item attributes of kinds with no variant).

- objdiff can diff whole archives: the cost is the size of each symbol,
  not of the object, and blob data is understood and typed data is
  sliced. Sampling could become a choice rather than a necessity
  (`MELEE_DAT_SAMPLES_ALL` for every archive).

## Walk findings

- `SdIntro.dat`: `SIS_IntroData[0]` points to the end of the data.
- `grPushon_YakumonoParam.x0` and `grShrineRoute_YakumonoParam.x10` are
  touch-line `lbColl_80008D30_arg1*`, written through
  `ftDevice_Callback0`'s `Vec3*` out parameter. That callback type is shared
  by two device tables with different outputs. `grZe_YakumonoParam` hides a
  pointer at 0x2C in `pad_14`.
- Some earlier by-address roots are misaligned inside data now reached
  from its real root, e.g. `GrGb_unused_x8E4C8` (`HSD_MatAnimJoint`) in
  the shapeanim list of the model desc at GrGb 0x8E4F0, and
  `EfDkData_unused_x9B9C`. Leftover `HSD_ShapeAnimJoint` trees (8-byte
  `_HSD_ShapeAnim`s that `HSD_MatAnimJoint` misreads) in `EfCoData`,
  `EfDkData` and `EfMrData` have no root yet. The orphan model desc lists
  in `PlCl`, `PlLk` and `PlSs` are left out: their animation trees have
  the `FObjDesc`s noted below.
- `GrMc.dat`'s `RObjAnimJoint`s at 0x301A4 and 0x301F4 have a third word
  pointing to an `HSD_AObjDesc` nothing else reaches; the code reads only
  two.
- `GrIz.dat` 0xF86D0, after the light list at 0xF84B8, holds pointers to
  0xD3980 and 0xD3B0C of unknown type.

- `ftDataFox.x48_items[4]` isn't an `Article`: its words are small integers.
- Kirby's Game & Watch and Yoshi copies (`PlKbCpGw`, `PlKbCpYs`) have
  `dynamics` that don't fit `ftDynamics`.
- Some unused trees typed by address in `dat_symbols.txt` don't fit:
  `PlGn*` 0x5D7C8 and 0x5D978 aren't material animations (their `_HSD_MatAnim`s
  overlap other nodes) and are left untyped. The trees at `PlCl`
  0x19428 and 0x1969C, `PlLk` 0x18BA8 and 0x18E1C, and `PlSs` 0x15898 are
  untyped: as `HSD_AnimJoint`s, an `FObjDesc`'s `ad` runs 0x80000 bytes
  past the data.
- Fighters' part animations (`ftData_x1C.x8`) sit next to `HSD_AnimJoint`
  trees that nothing points to, whose subtrees the part animations reach.
  `dat_symbols.txt` types their heads by address.

Not errors:

- About 1,500 objects are reached as several types: mostly HSD animation
  records (`HSD_MatAnimJoint`, `_HSD_MatAnim`, `_HSD_RenderAnim`, ...)
  whose identical bytes the exporter reuses, `HSD_CObjDesc` and its
  perspective member, and `char`/`unsigned char`. The walker could
  recognize these.
- `-1` in pointer fields means none. Counted, not reported.

- `ItCo.dat` 0x50A0-0x7DDC (right after `itPublicData.x8`) is a
  byte-for-byte copy of 0x2FC-0x303C whose pointers point to the
  originals. `dat_symbols.txt` types its structs, scripts and item
  attributes (by their originals' kinds) by address.

## Stopgaps

- `FtPartsDesc.vis_table` uses `DAT_EXTENT` for its costume rows; their
  number comes from the fighter's costume table in the DOL. Each row's
  visibility lists are counted by `model_num`.
- `ItemStateArray` uses `DAT_EXTENT`. Its length is the largest `anim_id` in
  the item kind's `ItemStateTable`, plus one. Replace with a `DAT_COUNT`
  based on `Article::kind` once the counts are available (item state enums,
  or reading the tables from the ELF).
- `ItemSpecialAttributes` selects a variant by `Article::kind`, bound in
  `itPublicData`, stage items (`gr_itkind`), fighters' items
  (`DAT_MATCH_FTITEM`) and Kirby's copies (`DAT_MATCH_KBCOPY`). Items
  whose code reads none of their attributes (ScBall, Spycloak, bows,
  blasters, capes, Peach's parasol and Toad, Thunder Jolt in the air,
  Sheik's held needle, PK Thunder's last trail, Ness's bat, Kirby's
  `It_Kind_Unk1`, `Pokemon_Unk`), and Master Hand's third and Young Link's
  sixth item slots, which aren't registered with a kind, are
  `itUnreadAttributes`: `DAT_EXTENT` words. Their sizes are only where the
  next object starts.
- Some fighters' items are followed by words nothing points to, between
  the `Article` and the next item's `ItemStateArray` (`PlSs`, `PlSk`,
  `PlNs`, `PlPp`, `PlLk`, `PlCl`): pointers to the animations the item's
  own states use, sometimes with -1s, like `ItemStateDesc`s of states the
  item kind's table doesn't index.
- `itSpecialAttrsHead`, the record monsters' and stage items' attributes
  start with, has duplicates: `itNokoNoko_DatAttrs2`, `itPatapataDatAttrs`,
  `itOldkuriAttributes_x0`, `itOldottoseaAttributes_x0`,
  `itWhiteBeaAttributes_x0`, and `s32*` in Heiho's and Birdo's.
- `ftData.xC`/`x14` (actions), `x1C` (part animations) and their `x8`,
  and `ftData_x20.x0` use `DAT_EXTENT`. The counts are in DOL tables per
  fighter kind (`ftData_Table_Unk0`, `ftData_UnkIntPairs`), or only in code.
- `FigaTree.tracks` uses `DAT_EXTENT`. Its length is the sum of `nodes`
  (`DAT_TERMINATED(-1)`), which needs a new annotation.
- `*_image` and `*_tlut` are `type:u8 extent`/`type:u16 extent`, up to the
  next public or pointer target, for the ones no reached `HSD_ImageDesc` or
  `HSD_TlutDesc` sizes (e.g. GrIz and GrPu, whose descs nothing reached
  points to).
- Vertex arrays are sized by `GXMaxIndex` over the display lists of the
  shapes that reach their descriptors. Shape-animation index lists
  (`HSD_ShapeSetDesc.vertex_idx_list` and `normal_idx_list`) aren't sized
  yet. Descriptors reached without a display list retain `DAT_EXTENT`
  inference. Exact index-list lengths and the largest vertex index across
  both display lists and shape-animation lists remain to be inferred.
- The particle banks (`EffectDataTable.cmd_bank`/`tex_bank`, `map_ptcl`,
  `map_texg`) use `DAT_EXTENT`/`extent`. Their headers give their sizes, as
  `psInitDataBankLocate` reads them: a header struct with counted members,
  or a sizer like `DAT_SCRIPT`'s.

## Coverage

- `PlSb.dat` 0x75C-0x1444 contains 33 unreferenced subaction subroutines
  after Sandbag's `FtSFX`. Each ends with a return (opcode 6), but none has
  an end command. Address roots for these subroutines would need to stop
  at a return. Stopping all scripts at returns would leave about 10 KB of
  fighters' `xC` scripts unexplained: the walker currently reaches that
  data by continuing past returns. That data would need address roots too.

- The name entry lists (`mnNameAutoName*`, `mnNameRefuseName*`) are
  counted in `dat_symbols.txt`: they end in a pointer to an empty string,
  which `DAT_TERMINATED` can't express.
- `toy.c` loads trophy symbols through `symbol_name` fields of its tables;
  those are covered by name patterns instead.
- `ftDemo*MotionFile*` are `u8[]`: packed archives like `Pl??AJ.dat`,
  relocated by `ftData` at runtime. They could be read as nested archives.
- About 15,000 `void*` fields aren't followed. Use `DAT_TYPE` where the type
  is known.

## Tool

- Demo motion tables (`ftData.x14`) and nested `ftDemo*MotionFile*` archives
  still need the packed-range check used for `ftData.xC` animations.
- One relocation is at a halfword (`TyMnInfo.dat` 0x25F6): the walk assumes
  pointers on words, so it's unexplained.

- Only pointers are checked against relocations. Wrong scalar types go
  unnoticed.
- The DWARF build compiles against aurora's console headers, not
  `libs/dolphin`. So the SDK types the archives use come from aurora:
  annotating them means redeclaring them in `dat_macros.h` (`MtxPtr`), and
  aurora lacks pieces (the GXVert inlines, shimmed in `dat_macros.h`). Move
  the DAT build to our own dolphin headers instead. They need a lot of
  cleanup first to build with clang as C23.

## Native archive interface

- An array root whose first element was already visited uses the walker's
  existing one-object view, even when a later request gives a larger count.
- A pointer to plain data without `DAT_COUNT`, `DAT_EXTENT` or
  `DAT_TERMINATED` is one element natively, as the walk types it.
- Plain unions (no pointers) are converted as their largest member.
- `DAT_TYPE` on an integer narrower than a native pointer keeps the offset.
- Scripts stay big-endian words with offsets; their readers need
  `dat_raw` to follow them.
- Packed archives (`Pl??AJ.dat`) are opened by size, like the walk.
- The host build is gcc; a pure clang toolchain needs a wrapped host clang
  beside the unwrapped one the DWARF build uses, and a ppc32 sysroot.

## Objects

- Unit diffs scale with symbol count: the `Pl*AJ.dat` animation archives
  have ~44k symbols each and take ~4s to diff in objdiff.

## Reporting (low priority)

- decomp.dev ingests objdiff-format reports from workflow artifacts named
  `<version>_report`. A `GALE01-dat_report` artifact would show as its own
  version without touching `GALE01`'s numbers. Folding dats into the main
  report as REL-like units would lower `GALE01`'s data percentage:
  decomp.dev sums every unit and ignores `module_name`.
- `samples report --objdiff` exports the report from dat-cli, including
  sample relocation differences and whole-archive data totals. Build the
  samples and upload its `report.json` as `GALE01-dat_report` in CI once
  the inputs are available.
- CI's current `melee-build:main` image has an empty
  `/orig/GALE01/files` directory (checked on 2026-10-06): provide the
  extracted archives before enabling DAT reporting.
