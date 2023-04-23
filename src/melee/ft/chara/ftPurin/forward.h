#ifndef MELEE_FT_CHARA_FTPURIN_FORWARD_H
#define MELEE_FT_CHARA_FTPURIN_FORWARD_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

static u32 const ftPr_MF_Special ATTRIBUTE_USED =
    FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_UpdatePhys | FtStateChange_FreezeState;

static u32 const ftPr_MF_SpecialHi ATTRIBUTE_USED =
    ftPr_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveGfx;

static u32 const ftPr_MF_SpecialLw ATTRIBUTE_USED =
    ftPr_MF_Special | FtStateChange_PreserveColAnimHitStatus;

static u32 const ftPr_MF_SpecialN ATTRIBUTE_USED =
    ftPr_MF_Special | FtStateChange_PreserveFastFall |
    FtStateChange_PreserveSfx;

static u32 const ftPr_MF_SpecialS ATTRIBUTE_USED =
    ftPr_MF_Special | FtStateChange_PreserveGfx | FtStateChange_PreserveSfx;

static u32 const ftPr_MF_SpecialAirHi ATTRIBUTE_USED =
    ftPr_MF_SpecialHi | FtStateChange_SkipUpdateParasol;

static u32 const ftPr_MF_SpecialAirLw ATTRIBUTE_USED =
    ftPr_MF_SpecialLw | FtStateChange_SkipUpdateParasol;

static u32 const ftPr_MF_SpecialAirN ATTRIBUTE_USED =
    ftPr_MF_SpecialN | FtStateChange_SkipUpdateParasol;

static u32 const ftPr_MF_SpecialAirS ATTRIBUTE_USED =
    ftPr_MF_SpecialS | FtStateChange_SkipUpdateParasol;

static u32 const ftPr_MF_SpecialNCharged ATTRIBUTE_USED =
    ftPr_MF_SpecialN | FtStateChange_Unk_19;

static u32 const ftPr_SpecialAirNCharged ATTRIBUTE_USED =
    ftPr_MF_SpecialNCharged | FtStateChange_SkipUpdateParasol;

typedef enum ftPurin_MotionState {
    ftPr_MS_Jump2 = ftCo_MS_Count,
    ftPr_MS_Jump3,
    ftPr_MS_Jump4,
    ftPr_MS_Jump5,
    ftPr_MS_Jump6,
    ftPr_MS_SpecialN_ChargeStartR,
    ftPr_MS_SpecialN_ChargeStartL,
    ftPr_MS_SpecialN_ChargeLoop,
    ftPr_MS_SpecialN_ChargeFull,
    ftPr_MS_SpecialN_ChargeRelease,
    ftPr_MS_SpecialN_StartTurn,
    ftPr_MS_SpecialN_EndR,
    ftPr_MS_SpecialN_EndL,
    ftPr_MS_SpecialAirN_ChargeStartR,
    ftPr_MS_SpecialAirN_ChargeStartL,
    ftPr_MS_SpecialAirN_ChargeLoop,
    ftPr_MS_SpecialAirN_ChargeFull,
    ftPr_MS_SpecialAirN_ChargeRelease,
    ftPr_MS_SpecialAirN_StartTurn,
    ftPr_MS_SpecialAirN_EndR,
    ftPr_MS_SpecialAirN_EndL,
    ftPr_MS_SpecialN_Hit,
    ftPr_MS_SpecialS,
    ftPr_MS_SpecialAirS,
    ftPr_MS_SpecialHiL,
    ftPr_MS_SpecialAirHiL,
    ftPr_MS_SpecialHiR,
    ftPr_MS_SpecialAirHiR,
    ftPr_MS_SpecialLwL,
    ftPr_MS_SpecialAirLwL,
    ftPr_MS_SpecialLwR,
    ftPr_MS_SpecialAirLwR,
} ftPurin_MotionState;

#endif
