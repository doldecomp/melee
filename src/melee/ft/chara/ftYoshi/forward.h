#ifndef MELEE_FT_CHARA_FTYOSHI_FORWARD_H
#define MELEE_FT_CHARA_FTYOSHI_FORWARD_H

#include "ft/forward.h"
#include "ftCommon/forward.h"

struct S_UNK_YOSHI1;

/// @todo Fix names
typedef enum ftYs_MotionFlags {
    ftYs_MF_Special = FtStateChange_SkipUpdateModel |
                      FtStateChange_SkipUpdateItemVis |
                      FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState,
    ftYs_MF_MS_341 = FtStateChange_Unk_UpdatePhys,
    ftYs_MF_ShieldStart =
        FtStateChange_PreserveFastFall | FtStateChange_PreserveGfx |
        FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateAnimVel |
        FtStateChange_Unk_6 | FtStateChange_SkipUpdateColAnim |
        FtStateChange_Unk_UpdatePhys,
    ftYs_MF_ShieldHold = FtStateChange_Unk_19 | FtStateChange_Unk_UpdatePhys,
    ftYs_MF_SpecialN = ftYs_MF_Special | FtStateChange_PreserveFastFall,
    ftYs_MF_SpecialAirHi = ftYs_MF_SpecialN | FtStateChange_PreserveGfx |
                           FtStateChange_SkipUpdateThrowException,
    ftYs_MF_UnkBase = ftYs_MF_Special | FtStateChange_PreserveSfx,
    ftYs_MF_SpecialAirS = ftYs_MF_UnkBase | FtStateChange_PreserveGfx,
    ftYs_MF_MS_366 = ftYs_MF_UnkBase | FtStateChange_PreserveColAnimHitStatus,
    ftYs_MF_SpecialS = ftYs_MF_SpecialN | FtStateChange_SkipUpdateParasol,
    ftYs_MF_MS_365 = ftYs_MF_SpecialAirHi | FtStateChange_SkipUpdateParasol,
    ftYs_MF_SpecialHi = ftYs_MF_SpecialAirS | FtStateChange_SkipUpdateParasol,
    ftYs_MF_MS_368 = ftYs_MF_MS_366 | FtStateChange_SkipUpdateParasol,
} ftYs_MotionFlags;

typedef enum ftYoshi_MotionState {
    ftYs_MS_Unk_341 = ftCo_MS_Count,
    ftYs_MS_Shield_Hold,
    ftYs_MS_Shield_Release,
    ftYs_MS_Shield_Damage,
    ftYs_MS_Shield_Start,
    ftYs_MS_SpecialN,
    ftYs_MS_SpecialN_CatchStart,
    ftYs_MS_SpecialN_Catch,
    ftYs_MS_SpecialAirN,
    ftYs_MS_SpecialAirN_CatchStart,
    ftYs_MS_SpecialAirN_Catch,
    ftYs_MS_SpecialS_Start,
    ftYs_MS_SpecialS,
    ftYs_MS_SpecialS_Turn,
    ftYs_MS_SpecialS_End,
    ftYs_MS_SpecialAirS_Start,
    ftYs_MS_SpecialAirS,
    ftYs_MS_SpecialAirS_Rebound,
    ftYs_MS_SpecialAirS_End,
    ftYs_MS_SpecialHi,
    ftYs_MS_SpecialAirHi,
    ftYs_MS_SpecialLw,
    ftYs_MS_SpecialLw_Land,
    ftYs_MS_SpecialAirLw,

    ftYs_MS_Unk_365,
    ftYs_MS_Unk_366,
    ftYs_MS_Unk_367,
    ftYs_MS_Unk_368,
} ftYoshi_MotionState;

#endif
