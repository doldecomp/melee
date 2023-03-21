#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H

#include "ftCommon/forward.h"

typedef enum ftGameWatchAction {
    MS_GAMEWATCH_ATTACK11 = ftCo_MS_Count,
    MS_GAMEWATCH_ATTACK100START,
    MS_GAMEWATCH_ATTACK100LOOP,
    MS_GAMEWATCH_ATTACK100END,
    MS_GAMEWATCH_ATTACKLW3,
    MS_GAMEWATCH_ATTACKS4,
    MS_GAMEWATCH_ATTACKAIRN,
    MS_GAMEWATCH_ATTACKAIRB,
    MS_GAMEWATCH_ATTACKAIRHI,
    MS_GAMEWATCH_LANDINGAIRN,
    MS_GAMEWATCH_LANDINGAIRB,
    MS_GAMEWATCH_LANDINGAIRHI,
    MS_GAMEWATCH_SPECIALN,
    MS_GAMEWATCH_SPECIALAIRN,
    MS_GAMEWATCH_SPECIALS1,
    MS_GAMEWATCH_SPECIALS2,
    MS_GAMEWATCH_SPECIALS3,
    MS_GAMEWATCH_SPECIALS4,
    MS_GAMEWATCH_SPECIALS5,
    MS_GAMEWATCH_SPECIALS6,
    MS_GAMEWATCH_SPECIALS7,
    MS_GAMEWATCH_SPECIALS8,
    MS_GAMEWATCH_SPECIALS9,
    MS_GAMEWATCH_SPECIALAIRS1,
    MS_GAMEWATCH_SPECIALAIRS2,
    MS_GAMEWATCH_SPECIALAIRS3,
    MS_GAMEWATCH_SPECIALAIRS4,
    MS_GAMEWATCH_SPECIALAIRS5,
    MS_GAMEWATCH_SPECIALAIRS6,
    MS_GAMEWATCH_SPECIALAIRS7,
    MS_GAMEWATCH_SPECIALAIRS8,
    MS_GAMEWATCH_SPECIALAIRS9,
    MS_GAMEWATCH_SPECIALHI,
    MS_GAMEWATCH_SPECIALAIRHI,
    MS_GAMEWATCH_SPECIALLW,
    MS_GAMEWATCH_SPECIALLW_CATCH,
    MS_GAMEWATCH_SPECIALLW_SHOOT,
    MS_GAMEWATCH_SPECIALAIRLW,
    MS_GAMEWATCH_SPECIALAIRLW_CATCH,
    MS_GAMEWATCH_SPECIALAIRLW_SHOOT,
} ftGameWatchAction;

// Oil Panic Charge Level Macros //

typedef enum ftGameWatch_PanicLevel {
    GAMEWATCH_PANIC_EMPTY,
    GAMEWATCH_PANIC_LOW,
    GAMEWATCH_PANIC_MID,
    GAMEWATCH_PANIC_FULL,
} ftGameWatch_PanicLevel;

// Mr. Game & Watch Action State Change Flags //

// Chef (SpecialN/SpecialAirN) //
#define FTGAMEWATCH_SPECIALN_COLL_FLAG                                        \
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |    \
        FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateMatAnim |     \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// Judgement (SpecialS/SpecialAirS) //
#define FTGAMEWATCH_SPECIALS_COLL_FLAG                                        \
    FtStateChange_PreserveColAnimHitStatus | FtStateChange_SkipUpdateHit |    \
        FtStateChange_SkipUpdateModel | FtStateChange_SkipUpdateMatAnim |     \
        FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |           \
        FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |              \
        FtStateChange_SkipUpdateModelPartVis |                                \
        FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27

// Oil Panic (SpecialLw/SpecialAirLw) //

// Mr. Game & Watch Action State IDs //

#endif
