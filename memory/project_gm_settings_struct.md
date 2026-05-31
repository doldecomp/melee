---
name: project-gm-settings-struct
description: gm/if match-settings functions are blocked on a shared un_803FA258 column-major settings global
metadata:
  type: project
---

Several remaining unstubbed functions read a shared match-settings global at
`un_803FA258` (declared `extern int un_803FA258[]` in gm_1B03.c) and the
adjacent `un_803FA128` (0x130-byte object; offsets ≥0x130 are actually
`un_803FA258` fields, since `0x803FA128 + 0x130 == 0x803FA258`). The data is
**column-major**: each setting (c_kind, slot_type, color, …) is an int[6] (one
per player), so `un_803FA258[field/4 + player]`. Functions that need this:
`un_802FFF2C` (StartMeleeData fill), `gm_801B0DD0` (matched 73% via array
indexing — see commit), and likely the larger gm results functions.

**Why:** defining a proper `un_803FA258` struct + the per-player column layout
is a coordinated change affecting multiple gm/if functions.
**How to apply:** array-index `un_803FA258` (it's `int[]`) rather than chasing a
struct; map decomp `un_803FA128.unkXXX` (XXX≥0x130) to `un_803FA258[(XXX-0x130)/4]`.
Related systemic struct work: THPFileInfo tail layout [[project_gm_decomp_systemic]].
