#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"

typedef enum ftMarioAction {
    AS_MARIO_UNK1 = ASID_MAX,
    AS_MARIO_UNK2,
    AS_MARIO_SPECIALN,
    AS_MARIO_SPECIALAIRN,
    AS_MARIO_SPECIALS,
    AS_MARIO_SPECIALAIRS,
    AS_MARIO_SPECIALHI,
    AS_MARIO_SPECIALAIRHI,
    AS_MARIO_SPECIALLW,
    AS_MARIO_SPECIALAIRLW,
    AS_MARIO_MAX,
} ftMarioAction;

#define MARIO_AUX_STATES_COUNT 2

// Flags used by Mario & Dr. Mario in Action State Change //

// SpecialN/SpecialAirN (Fireball / Megavitamin) //

// SpecialS/SpecialAirS (Cape / Super Sheet) //

#define FTMARIO_SPECIALS_COLL_FLAG                                             \
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |     \
        FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |            \
        FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |    \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |          \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// SpecialLw/SpecialAirLw (Mario / Dr. Tornado ) //

#define FTMARIO_SPECIALLW_COLL_FLAG                                            \
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |                  \
        FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |            \
        FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |    \
        FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |          \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

#endif
