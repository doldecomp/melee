# TODO

## Samples

- `PlSs` `x8_hurtbones_x352D8` (66.7%) and `PlGw` `dyn_descs_0_x78F0`
  (85.7%) don't match. PlSs's
  cause: `ftData_Item` is `Article*` for every slot, but Samus's slot 4 is
  `UNK_SAMUS_S1` (the grapple beam accessory; `ftSs_Init_CreateThrowGrapple
  Beam`), so everything behind `ftDataSamus.x48_items->[4]` is mistyped (8
  mismatches in the every-object build). Fix: a `bind:` attribute on roots
  in `dat_symbols.txt` (e.g. the fighter kind on `ftData*`), and
  `ftData_Item` as a union chosen by `DAT_IF` on that kind and `_index`.
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

- The generated C has some redundant parentheses (clang-tidy is off for
  `src/` in the build directory, so nothing reports them). Find and drop
  them in codegen.
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
- `ftData.x48_items` entries are typed `Article` (`ftData_Item`), but
  some slots are joints or other structs: Samus 4, Game & Watch 10,
  Kirby 4, Yoshi 3, Sheik 4/5, Link 6, Jigglypuff 1. These give about 140
  findings. Binding the fighter kind at each `ftData` root (its index in
  the loader's name table) would let a union pick per slot. The same binding
  would type `Article.x4_special` for fighter items.
- Fighters' part animations (`ftData_x1C.x8`) sit next to `HSD_AnimJoint`
  trees that nothing points to. Their relocations can't be explained.

Not errors:

- 23 objects reached as both `HSD_CameraAnim` and `HSD_WObjAnim`: the
  exporter reuses identical bytes. The walker could recognize this.
- `-1` in pointer fields means none. Counted, not reported.

## Stopgaps

- `ItemStateArray` uses `DAT_EXTENT`. Its length is the largest `anim_id` in
  the item kind's `ItemStateTable`, plus one. Replace with a `DAT_COUNT`
  based on `Article::kind` once the counts are available (item state enums,
  or reading the tables from the ELF).
- `ItemSpecialAttributes` covers 25 common item kinds. Missing:
  - types defined in `.c` files: G_Shell, MSBomb, StarRod, Hammer,
    StarRod_Star
  - inconsistent types: R_Shell, Foods, Kinoko
  - never used: ScBall, RabbitC, MetalB, Spycloak
  - all character items and Pokémon
- `ftData.xC`/`x14` (actions), `x1C` (part animations) and their `x8`,
  and `ftData_x20.x0` use `DAT_EXTENT`. The counts are in DOL tables per
  fighter kind (`ftData_Table_Unk0`, `ftData_UnkIntPairs`), or only in code.
- `FigaTree.tracks` uses `DAT_EXTENT`. Its length is the sum of `nodes`
  (`DAT_TERMINATED(-1)`), which needs a new annotation.
- `*_image` and `*_tlut` are typed `u8[]`/`u16[]` up to the next public or
  pointer target, for the ones no reached `HSD_ImageDesc` or
  `HSD_TlutDesc` sizes (e.g. GrIz and GrPu, whose descs nothing reached
  points to). Vertex arrays (`HSD_VtxDescList.vertex`) are still raw: their
  count is the largest index the display lists use.

## Coverage

- Loaded into untyped destinations, types unknown:
  `sqEventInitDataLevelTbl`, `tournament_box*_array`, `mnNameDefaultName*`
  (and `mnNameAutoName*`), `MemCardIconData`, `MemSnapIconData`,
  `effKirbyPichuDataTable`.
- `toy.c` loads trophy symbols through `symbol_name` fields of its tables;
  those are covered by name patterns instead.
- `ftDemo*MotionFile*` are `u8[]`: packed archives like `Pl??AJ.dat`,
  relocated by `ftData` at runtime. They could be read as nested archives.
- About 15,000 `void*` fields aren't followed. Use `DAT_TYPE` where the type
  is known.
- Ground's light override scans use `light_word_count` as a record count.
  The archive stores a count of 32-bit words: all 71 stage tables end at
  `light_word_count / 2` two-word records. The DAT annotation uses that
  length; the matching runtime retains the original scan bound. Reading
  past the table previously made neighbouring `LightList`s look like
  alternate entries, but every actual entry's second word is flags.

## Tool

- Only pointers are checked against relocations. Wrong scalar types go
  unnoticed.

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
