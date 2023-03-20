#ifndef MELEE_FT_CHARA_FTMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTMARIO_FORWARD_H

#include "ft/forward.h"

typedef enum ftMarioAction {
    ftMario_AS_Unk_341 = ASID_MAX,
    ftMario_AS_Unk_342,
    ftMario_AS_SpecialN,
    ftMario_AS_SpecialAirN,
    ftMario_AS_SpecialS,
    ftMario_AS_SpecialAirS,
    ftMario_AS_SpecialHi,
    ftMario_AS_SpecialAirHi,
    ftMario_AS_SpecialLw,
    ftMario_AS_SpecialAirLw,
    ftMario_AS_Count,
} ftMarioAction;

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
