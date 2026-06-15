# WIP PR Split Plan

This file tracks the plan for breaking the current aggregate WIP branch into
reviewable PRs. The goal is not to open everything at once. Open two to three
draft PRs at a time, get them clean, merge or revise them, then rebase the
aggregate branch and move to the next wave.

Current aggregate branch:

- Branch: `codex/split-up/mn`
- Draft PR: https://github.com/doldecomp/melee/pull/2702
- Last clean aggregate head: `0a7823d6ef78bf58e1e3c8cdf6fff8e99c3ff7c2`
- Validation state at that head: clean build, clean CI, no known regressions

Currently open slice PRs:

- 1/14: GM mode flow - https://github.com/doldecomp/melee/pull/2704
- 2/14: GM mode-specific work - https://github.com/doldecomp/melee/pull/2705
- 3/14: GR common and routes - https://github.com/doldecomp/melee/pull/2706

## Operating Plan

1. Keep the aggregate WIP branch as the source of truth until slices land.
2. For each slice, branch from current `origin/master` and apply only the files
   in that slice.
3. Ship only exact-match, no-regression work. Keep fuzzy or risky leftovers on
   the aggregate WIP branch until they become boring enough to review.
4. Open two to three draft PRs at a time.
5. After a slice lands, rebase the aggregate WIP branch, rerun the regression
   report, and update this file.
6. If a slice regresses, either fix it in the slice or drop the regressing part
   from that PR and leave it on the aggregate WIP branch.

Recommended gate for each slice:

```sh
ninja build/GALE01/main.dol
ninja changes_all
```

The final report for each slice should have:

- `build/GALE01/main.dol: OK`
- zero broken matches
- zero fuzzy regressions
- zero unit, section, or function metric regressions

## Recommended Waves

Open only one wave at a time unless review is moving quickly.

| Wave | PRs | Why |
| --- | --- | --- |
| 1 | `01-gm-mode-flow`, `02-gm-mode-specific` | Start with one subsystem and keep review context focused. |
| 2 | `11-ui-items-small-systems`, `14-thp-and-toy` | Smaller mixed systems after the first GM cleanup settles. |
| 3 | `03-gr-common-and-routes`, `04-gr-stage-pass-a` | Start ground work with common/routing plus one stage batch. |
| 4 | `05-gr-stage-pass-b`, `06-gr-stage-pass-c` | Finish the ground/stage work without making one huge GR review. |
| 5 | `07-ft-common` | Large and important enough to stand alone. |
| 6 | `08-ft-fighter-and-core` | Fighter/core work after `ftCommon` is understood. |
| 7 | `09-mn-rules-name-stage`, `10-mn-misc-menus` | Menu work split between rule/name/stage and miscellaneous screens. |
| 8 | `12-lb-support-libraries`, `13-hsd-baselib` | Support/library changes last because they are broadest and easiest to make noisy. |

If reviewers prefer fewer concurrent PRs, use two at a time. If a wave looks
quiet after CI, add the next small slice rather than opening all remaining work.

## Slice Breakdown

Status values:

- `planned`: not opened yet
- `draft`: draft PR exists
- `ready`: review-ready and CI clean
- `merged`: landed upstream
- `held`: intentionally kept local because it is fuzzy, risky, or regressing

### 01-gm-mode-flow

Status: `draft`
PR: https://github.com/doldecomp/melee/pull/2704
QA: `in progress`

Files:

```text
src/melee/gm/gm_1601.c
src/melee/gm/gm_16AE.c
src/melee/gm/gm_16F1.c
src/melee/gm/gm_1832.c
src/melee/gm/gm_18A5.c
src/melee/gm/gm_19EF.c
src/melee/gm/gm_1A4C.c
src/melee/gm/gm_1B03.c
src/melee/gm/gm_1BFA.c
src/melee/gm/gmmain_lib.c
```

Notes:

- Main game-mode flow and related helpers.
- Keep any shared declaration or naming churn out unless this slice needs it to
  build cleanly.

### 02-gm-mode-specific

Status: `draft`
PR: https://github.com/doldecomp/melee/pull/2705
QA: `in progress`

Files:

```text
src/melee/gm/gmallstar.c
src/melee/gm/gmcamera.c
src/melee/gm/gmclassic.c
src/melee/gm/gmregclear.c
src/melee/gm/gmresultplayer.c
src/melee/gm/gmstaffroll.c
src/melee/gm/gmtou.c
```

Notes:

- Mode-specific GM implementations.
- `gmresult.c` was intentionally dropped from the aggregate WIP because it
  caused the remaining `.sdata` regression.

### 03-gr-common-and-routes

Status: `draft`
PR: https://github.com/doldecomp/melee/pull/2706
QA: `in progress`

Files:

```text
src/melee/gr/granime.c
src/melee/gr/grmaterial.c
src/melee/gr/ground.c
src/melee/gr/grpushon.c
src/melee/gr/grzakogenerator.c
src/melee/gr/grbigblueroute.c
src/melee/gr/grkinokoroute.c
src/melee/gr/grshrineroute.c
```

Notes:

- Common ground code and route helpers.
- This should give reviewers shared context before stage-specific batches.

### 04-gr-stage-pass-a

Status: `planned`

Files:

```text
src/melee/gr/grbigblue.c
src/melee/gr/grcorneria.c
src/melee/gr/grmutecity.c
src/melee/gr/grrcruise.c
src/melee/gr/grvenom.c
```

Notes:

- Larger stage files with relatively heavy churn.
- Split further if one stage carries non-obvious helper or data changes.

### 05-gr-stage-pass-b

Status: `planned`

Files:

```text
src/melee/gr/grgreens.c
src/melee/gr/grinishie1.c
src/melee/gr/groldkongo.c
src/melee/gr/grzebes.c
src/melee/gr/grpstadium.c
```

Notes:

- Second heavy stage batch.
- Keep this separate from pass A so GR review is not one oversized diff.

### 06-gr-stage-pass-c

Status: `planned`

Files:

```text
src/melee/gr/grflatzone.c
src/melee/gr/grfourside.c
src/melee/gr/grhomerun.c
src/melee/gr/grkongo.c
src/melee/gr/groldpupupu.c
src/melee/gr/groldyoshi.c
src/melee/gr/gronett.c
src/melee/gr/grpura.c
src/melee/gr/gryorster.c
```

Notes:

- Smaller remaining stage files.
- Can be combined with pass B only if both are very clean and reviewers are
  comfortable with a larger GR follow-up.

### 07-ft-common

Status: `planned`

Files:

```text
src/melee/ft/chara/ftCommon/ftCo_09F7.c
src/melee/ft/chara/ftCommon/ftCo_0A01.c
src/melee/ft/chara/ftCommon/ftCo_Bury.c
src/melee/ft/chara/ftCommon/ftCo_Damage.c
src/melee/ft/chara/ftCommon/ftCo_DamageIce.c
src/melee/ft/chara/ftCommon/ftCo_DownBound.c
src/melee/ft/chara/ftCommon/ftCo_Guard.c
src/melee/ft/chara/ftCommon/ftCo_ItemThrow.c
src/melee/ft/chara/ftCommon/ftCo_Shouldered.c
src/melee/ft/chara/ftCommon/ftCo_ThrownKirby.c
src/melee/ft/chara/ftCommon/ftCo_WarpStar.c
```

Notes:

- `ftCo_0A01.c` is the review anchor and may justify splitting this into
  `ft-common-large-state` and `ft-common-small-actions`.

### 08-ft-fighter-and-core

Status: `planned`

Files:

```text
src/melee/ft/chara/ftKirby/ftkirby.c
src/melee/ft/chara/ftKirby/ftkirbyspecialmars.c
src/melee/ft/chara/ftKirby/ftkirbyspecialn.c
src/melee/ft/chara/ftNana/ftNn_Init.c
src/melee/ft/chara/ftYoshi/ftYs_SpecialS.c
src/melee/ft/ft_0892.c
src/melee/ft/ft_0CDD.c
src/melee/ft/ftcoll.c
src/melee/ft/ftcpuattack.c
src/melee/ft/ftmaterial.c
src/melee/ft/ftmetal.c
```

Notes:

- Fighter-specific and FT core work.
- `ftcpuattack.c` is the largest file in this slice and deserves focused
  review.

### 09-mn-rules-name-stage

Status: `planned`

Files:

```text
src/melee/mn/mnmainrule.c
src/melee/mn/mnruleplus.c
src/melee/mn/mnitemsw.c
src/melee/mn/mnstagesw.c
src/melee/mn/mnstagesel.c
src/melee/mn/mnname.c
src/melee/mn/mnnamenew.c
```

Notes:

- Rule, item, stage, and name-entry menu work.
- `mnmainrule.c` and `mnnamenew.c` are the likely review hotspots.

### 10-mn-misc-menus

Status: `planned`

Files:

```text
src/melee/mn/mncharsel.c
src/melee/mn/mndatadel.c
src/melee/mn/mndiagram.c
src/melee/mn/mndiagram3.c
src/melee/mn/mnevent.c
src/melee/mn/mninfo.c
src/melee/mn/mnsnap.c
src/melee/mn/mnsound.c
src/melee/mn/mnsoundtest.c
src/melee/mn/mnvibration.c
```

Notes:

- Remaining menu screens with smaller individual diffs.
- Can be reviewed after the rule/name/stage slice settles.

### 11-ui-items-small-systems

Status: `planned`

Files:

```text
src/melee/cm/camera.c
src/melee/ef/efsync.c
src/melee/if/if_2F72.c
src/melee/if/ifcoget.c
src/melee/if/ifmagnify.c
src/melee/if/ifprize.c
src/melee/if/ifstatus.c
src/melee/if/ifstock.c
src/melee/if/soundtest.c
src/melee/if/textdraw.c
src/melee/it/items/itarwinglaser.c
src/melee/it/items/itflipper.c
src/melee/it/items/itkusudama.c
src/melee/it/items/itlinkboomerang.c
src/melee/it/items/itlinkhookshot.c
src/melee/it/items/itpikachuthunder.c
src/melee/it/itspawn.c
src/melee/mp/mpcoll.c
src/melee/mp/mpisland.c
src/melee/mp/mplib.c
src/melee/pl/pltrick.c
src/melee/vi/vi0401.c
src/melee/vi/vi0501.c
src/melee/vi/vi1201v1.c
src/melee/vi/vi1201v2.c
```

Notes:

- Small systems grouped to avoid too many tiny PRs.
- If this is too broad for review, split `if/` into its own interface/HUD PR
  and keep the remaining small systems together.

### 12-lb-support-libraries

Status: `planned`

Files:

```text
src/melee/lb/lb_00F9.c
src/melee/lb/lb_0192.c
src/melee/lb/lbarq.c
src/melee/lb/lbaudio_ax.c
src/melee/lb/lbbgflash.c
src/melee/lb/lbcollision.c
src/melee/lb/lbdvd.c
src/melee/lb/lbmemory.c
src/melee/lb/lbmthp.c
src/melee/lb/lbrefract.c
src/melee/lb/lbshadow.c
src/melee/lb/lbsnap.c
src/melee/lb/lbsnap.static.h
```

Notes:

- Melee support-library work.
- `lbaudio_ax.c` and `lbbgflash.c` are the review anchors.

### 13-hsd-baselib

Status: `planned`

Files:

```text
src/sysdolphin/baselib/axdriver.c
src/sysdolphin/baselib/hsd_3A94.c
src/sysdolphin/baselib/hsd_3AA7.c
src/sysdolphin/baselib/hsd_3AA7.h
src/sysdolphin/baselib/hsd_3B2E.c
src/sysdolphin/baselib/hsd_3B34.c
src/sysdolphin/baselib/hsd_3B5C.c
src/sysdolphin/baselib/leak.c
src/sysdolphin/baselib/particle.c
src/sysdolphin/baselib/psdisp.c
src/sysdolphin/baselib/sislib.c
src/sysdolphin/baselib/sobjlib.c
src/sysdolphin/baselib/synth.c
src/sysdolphin/baselib/texpdag.c
```

Notes:

- Broad HSD/baselib work, so keep it separate from Melee gameplay files.
- `particle.c`, `hsd_3AA7.c`, and `texpdag.c` are large enough to call out in
  the PR body.

### 14-thp-and-toy

Status: `planned`

Files:

```text
extern/dolphin/src/dolphin/thp/THPDec.c
src/melee/ty/toy.c
src/melee/ty/tydisplay.c
src/melee/ty/tyfigupon.c
```

Notes:

- THP decode work plus trophy/toy files.
- If reviewers prefer pure subsystem PRs, split this into `extern-thp` and
  `ty-trophy`.

## Update Log

- 2026-06-15: Opened draft PRs 1/14, 2/14, and 3/14. Marked them as in QA.
- 2026-06-15: Initial split plan created from aggregate WIP branch after CI and
  regression cleanup.
