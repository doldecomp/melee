# Directory layout notes migrated from `dir.dox` files

## `src/melee/ft/kinds/`

@todo Rename to @c entities to match @c gr and @c it.

## `src/melee/ft/kinds/ftMasterHand/`

@defgroup ftmasterhand ftMasterHand
@todo These splits work with the floats but are not what one would expect
      for the text section.

## `src/melee/gm/`

@brief Top-level game code. Houses #main.

## `src/melee/gr/`

@todo Create @c entities directory to hold individual stages.

## `src/melee/it/`

@todo Create @c entities directory to hold individual items.

## `src/sysdolphin/baselib/`

@todo Rename this to a root directory called @c HSD or @c hsd and delete its
parent (@c sysdolphin).

## Unplaced notes

### Notes migrated from `src/melee/gm/gm_1A36.dox`

Index into #controller_map containing a union of all inputs from all
controllers.


### Notes migrated from `src/melee/gm/types.dox`

Unplaced: `GameState::game_mode_override` no longer exists under that name.

Optional callback installed by #gm_801A4014. When set and the return value
is not #GM_COUNT, `runGameMode` runs that game mode once before
resuming the current mode's scene graph.
