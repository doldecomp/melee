#ifndef MELEE_FT_CHARA_FTLUIGI_FORWARD_H
#define MELEE_FT_CHARA_FTLUIGI_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftLuigiAction {
    AS_LUIGI_SPECIALN = ftCo_AS_Count,
    AS_LUIGI_SPECIALAIRN,
    AS_LUIGI_SPECIALS_START,
    AS_LUIGI_SPECIALS_HOLD,
    AS_LUIGI_SPECIALS_FLY,
    AS_LUIGI_SPECIALS_END,
    AS_LUIGI_SPECIALS_LAUNCH,
    AS_LUIGI_SPECIALS_MISFIRE,
    AS_LUIGI_SPECIALAIRS_START,
    AS_LUIGI_SPECIALAIRS_HOLD,
    AS_LUIGI_SPECIALAIRS_FLY,
    AS_LUIGI_SPECIALAIRS_END,
    AS_LUIGI_SPECIALAIRS_LAUNCH,
    AS_LUIGI_SPECIALAIRS_MISFIRE,
    AS_LUIGI_SPECIALHI,
    AS_LUIGI_SPECIALAIRHI,
    AS_LUIGI_SPECIALLW,
    AS_LUIGI_SPECIALAIRLW,
} ftLuigiAction;

// Flags used by Luigi in Action State Change //

// SpecialN/SpecialAirN (Fireball)

#define FTLUIGI_SPECIALN_COLL_FLAG                                            \
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim

// SpecialS/SpecialAirS (Green Missile)

// Misfire

// SpecialLw (Luigi Cyclone)

#define FTLUIGI_SPECIALLW_FLAG                                                \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |                 \
        FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |   \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |         \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

#endif
