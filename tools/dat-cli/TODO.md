# TODO

## Sample findings

- `HeartContainerAttr` doesn't match (92.9%).
- `itEgg_ItemVars` with `ItemSpecialAttributes` as `.kusudama`: the union's
  first member can't carry that variant. `ItemSpecialAttributes`'
  `hammer_head`, `m_ball` and `tomato` have no types of their own.
- HSD-owned coverage gaps come from stage containers: `UnkStageDat_x8_t`'s
  `unk4`/`unk8`/`unkC` are animation lists indexed by animation (count only
  in code), `x28` is a `u8` flag per animation, and the map header's
  `unk10` holds 8-byte records, not `HSD_Spline*`.

## Samples

- C89 initializes a union through its first member only, and MWCC has no
  designated initializers or `__typeof__`. A union object is sampled per
  variant its tag chooses, as that member's own type. A union inside a
  sample is written through its first member, which has to carry the
  chosen variant (as large, with pointers wherever it has them); others
  are listed as needing a type of their own.

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
- `EffectDataTable` only has its two particle banks. The records after them
  (an `f32` and four pointers each) aren't typed.

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
- `FigaTree.tracks` uses `DAT_EXTENT`. Its length is the sum of `nodes` up
  to -1, which needs a new annotation.
- `*_image` and `*_tlut` are `u8[]`/`u16[]` up to the next public or
  pointer target. Their exact sizes come from their `HSD_ImageDesc` and
  `HSD_TlutDesc`, which a real element type could use.

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

## Tool

- Only pointers are checked against relocations. Wrong scalar types go
  unnoticed.

## Reporting (low priority)

- decomp.dev ingests objdiff-format reports from workflow artifacts named
  `<version>_report`. A `GALE01-dat_report` artifact would show as its own
  version without touching `GALE01`'s numbers. Folding dats into the main
  report as REL-like units would lower `GALE01`'s data percentage:
  decomp.dev sums every unit and ignores `module_name`.
- The report has to come from dat-cli: `objdiff-cli report` measures data
  per combined section and misses relocation differences, and can't hold
  whole archives. Units per archive, `matched_data` as the bytes of objects
  whose sample matches.
- Unknown whether CI's `/orig` has `orig/GALE01/files`.
