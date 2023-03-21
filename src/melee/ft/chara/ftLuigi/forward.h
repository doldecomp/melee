#ifndef MELEE_FT_CHARA_FTLUIGI_FORWARD_H
#define MELEE_FT_CHARA_FTLUIGI_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

typedef enum ftLuigiAction {
    MS_LUIGI_SPECIALN = ftCo_MS_Count,
    MS_LUIGI_SPECIALAIRN,
    MS_LUIGI_SPECIALS_START,
    MS_LUIGI_SPECIALS_HOLD,
    MS_LUIGI_SPECIALS_FLY,
    MS_LUIGI_SPECIALS_END,
    MS_LUIGI_SPECIALS_LAUNCH,
    MS_LUIGI_SPECIALS_MISFIRE,
    MS_LUIGI_SPECIALAIRS_START,
    MS_LUIGI_SPECIALAIRS_HOLD,
    MS_LUIGI_SPECIALAIRS_FLY,
    MS_LUIGI_SPECIALAIRS_END,
    MS_LUIGI_SPECIALAIRS_LAUNCH,
    MS_LUIGI_SPECIALAIRS_MISFIRE,
    MS_LUIGI_SPECIALHI,
    MS_LUIGI_SPECIALAIRHI,
    MS_LUIGI_SPECIALLW,
    MS_LUIGI_SPECIALAIRLW,
} ftLuigiAction;

// Flags used by Luigi in Motion State Change //

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
