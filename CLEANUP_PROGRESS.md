# Melee Decompilation Cleanup Progress

> Automated documentation and annotation of the [doldecomp/melee](https://github.com/doldecomp/melee) decompilation.
> Fork: [beammeupscottyyy/melee](https://github.com/beammeupscottyyy/melee)

## Status Legend
- ✅ Complete
- 🔄 In Progress
- ❌ Not Started

---

## Phase 1: Core Game Logic

### src/melee/ft/ (Fighter System)

#### Core Headers
- ✅ ft/forward.h — Forward declarations, enums, character IDs
- 🔄 ft/types.h — Fighter struct, ftCommonData, per-character attributes
- ✅ ft/fighter.h — Core fighter API declarations
- ❌ ft/inlines.h
- ❌ ft/dobjlist.h

#### Core Sources
- ❌ ft/fighter.c — Fighter initialization, state machine, main loop
- ✅ ft/ftaction.c — Action state transition logic
- ❌ ft/ftanim.c — Animation system
- ✅ ft/ftcoll.c — Fighter collision detection
- ❌ ft/ftcommon.c — Common fighter utilities
- ✅ ft/ftdata.c — Fighter data loading
- ❌ ft/ftlib.c — Fighter library functions
- ❌ ft/ftparts.c — Fighter model parts management
- ✅ ft/ftcmdscript.c — CPU command script interpreter & input VM
- ❌ ft/ftdynamics.c — Physics/bone dynamics
- ❌ ft/ftcamera.c — Fighter camera tracking
- ❌ ft/ftchangeparam.c — Parameter modification (items, etc.)
- ❌ ft/ftcliffcommon.c — Ledge grab mechanics
- ❌ ft/ftcolanim.c — Color/material animation
- ❌ ft/ftcpuattack.c — CPU AI attack logic
- ❌ ft/ftdemo.c — Demo/replay playback
- ❌ ft/ftdevice.c — Device/stage interaction
- ❌ ft/ftdrawcommon.c — Common draw routines
- ❌ ft/ftmaterial.c — Material/texture handling
- ❌ ft/ftmetal.c — Metal form effects
- ❌ ft/ftwalljump.c — Wall jump mechanics
- ❌ ft/ftwalkcommon.c — Walking mechanics
- ❌ ft/ftwaitanim.c — Idle animation

#### Common Action States (ftCo_*)
- ❌ ft/ftCo_800C703C.c through ft/ftCo_800C7CA0.c

#### Numbered Modules (ft_0XXX)
- ❌ ft/ft_0763.c through ft/ft_3C61.c

#### Character-Specific (ft/kinds/)
- ❌ ftMario/ ftFox/ ftCaptain/ ftDonkey/ ftKirby/ ftKoopa/
- ❌ ftLink/ ftSeak/ ftNess/ ftPeach/ ftPopo/ ftNana/
- ❌ ftPikachu/ ftSamus/ ftYoshi/ ftPurin/ ftMewtwo/ ftLuigi/
- ❌ ftMars/ ftZelda/ ftCLink/ ftDrMario/ ftFalco/ ftPichu/
- ❌ ftGameWatch/ ftGanon/ ftEmblem/ ftMasterHand/ ftCrazyHand/
- ❌ ftZakoBoy/ ftZakoGirl/ ftSandbag/

### src/melee/it/ (Items) — ❌ Not Started
### src/melee/gr/ (Stages) — ❌ Not Started
### src/melee/pl/ (Player/Input) — ❌ Not Started
### src/melee/cm/ (Camera) — ❌ Not Started
### src/melee/gm/ (Game Mode) — ❌ Not Started
### src/melee/ef/ (Effects) — ❌ Not Started
### src/melee/db/ (Debug) — ❌ Not Started
### src/melee/if/ (Interface/HUD) — ❌ Not Started
### src/melee/lb/ (Library) — ❌ Not Started
### src/melee/mn/ (Menu) — ❌ Not Started
### src/melee/mp/ (Map) — ❌ Not Started
### src/melee/sc/ (Scene) — ❌ Not Started
### src/melee/sfx/ (Sound) — ❌ Not Started
### src/melee/ty/ (Trophy) — ❌ Not Started
### src/melee/vi/ (Video) — ❌ Not Started

## Phase 2: Engine (src/sysdolphin/) — ❌ Not Started
## Phase 3: SDK/Runtime — ❌ Not Started
