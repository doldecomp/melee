# TODO

## Samples

- `PlGw` `dyn_descs_0_x78F0` (85.7%) doesn't match.
- `types unhoisted` lists dat types declared in `.c` files: none left. The
  stage `*_YakumonoParam` structs aren't reachable (`void*` in the stage
  info) and differ per stage.
- `PlFx` `x0_common_attr_x4018` is an `ItemAttr` sample, but two other
  samples point to it as `HSD_ShapeAnimJoint*` and `HSD_AnimJoint*` (casts
  in `ftDataFox.c`). Likely a field that is a union of those, chosen by
  something the walk doesn't bind.
- A union object whose tag chooses no member has no sample (`CmdUnion`,
  which is a script; item attributes of fighter items, whose kind isn't
  bound).

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
- `yakumono_param` has no type for about 40 stages, including every
  `GrT*` target test. Their code doesn't read it, or reads it locally.

- `ItemStateDesc.x4_matanim_joint` and `x8_parameters` hold unrelocated
  values in some items' first state (10 cases: `GrCn.dat`, `ItCo.dat`, ...).
  They aren't always those pointer types.

- Articles in Kirby's copies (`ftKbCopy*`) and in `ftData.x48_items` leave
  `x4_specialAttributes` ambiguous: their item kinds aren't bound. The
  kinds are known per slot (`ftKb_SpecialN_800F16D0`).
- Fighters' part animations (`ftData_x1C.x8`) sit next to `HSD_AnimJoint`
  trees that nothing points to, whose subtrees the part animations reach.
  `dat_symbols.txt` types their heads by address.

Not errors:

- 23 objects reached as both `HSD_CameraAnim` and `HSD_WObjAnim`: the
  exporter reuses identical bytes. The walker could recognize this.
- `-1` in pointer fields means none. Counted, not reported.

- `ItCo.dat` 0x50A0-0x7DDC (right after `itPublicData.x8`) is a
  byte-for-byte copy of 0x2FC-0x303C whose pointers point to the
  originals. `dat_symbols.txt` types its structs and scripts by address; its
  43 `ItemSpecialAttributes` (kinds unbound) remain.

## Stopgaps

- `FtPartsDesc.vis_table` uses `DAT_EXTENT` for its costume rows; their
  number comes from the fighter's costume table in the DOL. Each row's
  visibility lists are counted by `model_num`.
- `ItemStateArray` uses `DAT_EXTENT`. Its length is the largest `anim_id` in
  the item kind's `ItemStateTable`, plus one. Replace with a `DAT_COUNT`
  based on `Article::kind` once the counts are available (item state enums,
  or reading the tables from the ELF).
- `ItemSpecialAttributes` selects common and related items except Sword,
  ScBall and Spycloak. Sword's first three fields are pointer-typed but
  hold unrelocated scalar values; ScBall and Spycloak still lack layouts.
  Bind and annotate the remaining character items and Pokémon.
- `ftData.xC`/`x14` (actions), `x1C` (part animations) and their `x8`,
  and `ftData_x20.x0` use `DAT_EXTENT`. The counts are in DOL tables per
  fighter kind (`ftData_Table_Unk0`, `ftData_UnkIntPairs`), or only in code.
- `FigaTree.tracks` uses `DAT_EXTENT`. Its length is the sum of `nodes`
  (`DAT_TERMINATED(-1)`), which needs a new annotation.
- `*_image` and `*_tlut` are `type:u8 extent`/`type:u16 extent`, up to the
  next public or pointer target, for the ones no reached `HSD_ImageDesc` or
  `HSD_TlutDesc` sizes (e.g. GrIz and GrPu, whose descs nothing reached
  points to).
- Vertex arrays (`HSD_VtxDescList.vertex`, an `HSD_VertexArray` blob) run
  to the next object. Their length is (the largest index the display lists
  use + 1) × `stride`. Plan:
  - The evaluator gets a byte-slice value besides integers: a pointer
    field whose own annotation gives its length (`DAT_COUNT`,
    `DAT_TERMINATED`) evaluates to the data it points to. `DAT_BIND` scopes
    and `call` take such values; functions stay pure over fixed bytes.
  - `HSD_PObjDesc.verts` binds `DAT_BIND(dl, display) DAT_BIND(descs,
    verts)`; `vertex` gets `DAT_COUNT((GXMaxIndex(dl, descs, attr) + 1) *
    stride)`.
  - `GXMaxIndex` is a tool-side helper, not a port: it decodes the display
    list as the GameCube lays it out (opcode byte, `u16` vertex count, then
    per vertex an entry per attribute in `verts` order: `GX_INDEX8` 1 byte,
    `GX_INDEX16` 2, `GX_DIRECT` inline by `comp_cnt`/`comp_type`; up to the
    0 opcode) and returns the largest index for `attr`.
  - Arrays shared between PObjs already take the largest extent. Shape
    animations (`HSD_ShapeSetDesc.vertex_idx_list`) index them too.
- The particle banks (`EffectDataTable.cmd_bank`/`tex_bank`, `map_ptcl`,
  `map_texg`) use `DAT_EXTENT`/`extent`. Their headers give their sizes, as
  `psInitDataBankLocate` reads them: a header struct with counted members,
  or a sizer like `DAT_SCRIPT`'s.

## Coverage

- `ALDYakuAll` (`StageInfo.ald_yaku_all`) is a null-terminated table of
  item scripts, loaded as `void*`: a null, then the scripts from index 1
  (as `Ground` reads them), then a null. The scripts are typed by address
  (`script:`); the lists (~900 bytes) need a pointer typedef with
  `DAT_SCRIPT` and a list that skips its first null.
- `PlSb.dat` 0x75C-0x1444, after Sandbag's `FtSFX`, parses as subaction
  commands but has no end command before the next object: not standalone
  scripts. Nothing points into it.

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

- A sample whose type runs into the next one: `coll_data` in `GrBb.dat`
  ends 4 bytes into `stage_params_xC6B98`. The type is probably too long.
- Unit diffs scale with symbol count: the `Pl*AJ.dat` animation archives
  have ~44k symbols each and take ~4s to diff in objdiff.

## Reporting (low priority)

- decomp.dev ingests objdiff-format reports from workflow artifacts named
  `<version>_report`. A `GALE01-dat_report` artifact would show as its own
  version without touching `GALE01`'s numbers. Folding dats into the main
  report as REL-like units would lower `GALE01`'s data percentage:
  decomp.dev sums every unit and ignores `module_name`.
- The report has to come from dat-cli: `objdiff-cli report` measures data
  per combined section and misses relocation differences. Units per archive, `matched_data` as the bytes of objects
  whose sample matches.
- Unknown whether CI's `/orig` has `orig/GALE01/files`.
