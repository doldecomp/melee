#include "gm_1BFA.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmvsmelee.h"
#include "types.h"

#include "baselib/memory.h"

#include "gm/forward.h"

#include "if/if_2FD9.h"

#include "lb/forward.h"

#include "lb/inlines.h"
#include "lb/lb_00B0.h"
#include "lb/lbtime.h"
#include "ty/toy.h"

enum {
    state_approach,
    state_vs,
    state_prize,
};

/* 1BFBA8 */ static void onExitVs(GameModeState*);
/* 1BFF7C */ static void onExitPrize(GameModeState*);

GameModeState gm_Mode_ChallengerApproach_States[] = {
    {
        state_approach,
        lbDvdPreload_2,
        0,
        gm_ModeState_Approach_OnEnter,
        NULL,
        {
            GS_APPROACH,
            &gmVsMelee_ApproachData,
            &gmVsMelee_ApproachData,
        },
    },
    {
        state_vs,
        lbDvdPreload_2,
        0,
        gm_ModeState_ApproachVs_OnEnter,
        onExitVs,
        {
            GS_VS,
            &gmVsMelee_StartData,
            &gmVsMelee_VsExitInfo,
        },
    },
    {
        state_prize,
        lbDvdPreload_2,
        0,
        gm_ModeState_Prize_OnEnter,
        onExitPrize,
        {
            GS_PRIZE_INTERFACE,
            &if_Scene_Prize_EnterData,
            NULL,
        },
    },
    { GM_GAMEMODESTATE_TERMINATE },
};

void gm_ModeState_Approach_OnEnter(GameModeState* arg0)
{
    VsApproachData* vs = gm_GetGameModeStateEnterData(arg0);
    ChallengerData* challenger = gm_GetChallengerData();
    vs->cpu_ckind = challenger->cpu_ckind;
    vs->human_slot = challenger->human_slot;
    lbCardGame_SetupArchive();
}

void gm_ModeState_ApproachVs_OnEnter(GameModeState* state)
{
    StartMeleeData* start = gm_GetGameModeStateEnterData(state);
    ChallengerData* challenger = gm_GetChallengerData();
    gm_SetupRulesDefaults(&start->rules);
    gm_SetupAllPlayerDefaults(start->players);
    start->rules.x0_6 = false;
    start->rules.match_kind = MatchKind_Stock;
    start->rules.x0_3 = 2;
    start->rules.stkind =
        gm_GetChallengerStKind(gm_CKindToSelKind(challenger->cpu_ckind));
    gm_SetupHumanPlayer(&start->players[0], challenger->human_ckind,
                        challenger->human_color, 1, challenger->human_slot);
    gm_SetupCpuPlayer(&start->players[1], challenger->cpu_ckind, 0, 1, 1);
    { /// @todo Inline?
        u8 human_nametag = challenger->human_nametag;
        start->players[0].nametag = human_nametag;
        start->players[1].nametag = GM_NAMETAG_NONE;
        start->players[1].cpu_kind = CpuKind_4;
        start->players[1].cpu_level =
            gm_DecideChallengerCpuLevel(challenger->cpu_ckind, human_nametag);
    }
    gm_LoadRumbleEnabled(start);
}

void onExitVs(GameModeState* state)
{
    MatchExitInfo* mei = gm_GetGameModeStateExitData(state);
    ChallengerData* challenger = gm_GetChallengerData();
    gm_80162968(mei->match_end.frame_count / GM_FPS);
    gm_8016247C(mei->match_end.player_standings[0].xE);
    if (mei->match_end.outcome != OUTCOME_NO_CONTEST &&
        mei->match_end.outcome != OUTCOME_RETRY &&
        mei->match_end.player_standings[0].stocks != 0)
    {
        gm_UnlockCKind(challenger->cpu_ckind);
    } else {
        gmMainLib_8015DB2C(gm_CKindToUnlockIndex(challenger->cpu_ckind));
    }
    gm_80173EEC();
    gm_80172898(0x100U);
    if (!gm_801721EC()) {
        gm_SetPendingGameMode(challenger->curr_mode);
        gm_SetNewGameModePending();
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
static UNK_T* gm_801BFC60(u32 arg0, s32 arg1, u32 arg2, u32 arg3, UNK_T* arg4)
{
    struct un_804A1F48_t* temp_r3;

    if (arg1 == 0) {
        if_Scene_Prize_EnterData.x0 = arg0;
        if_Scene_Prize_EnterData.x4 = arg3;
        if_Scene_Prize_EnterData.x2 = arg2;
        return (&if_Scene_Prize_EnterData.x8);
    }
    temp_r3 = HSD_MemAlloc(sizeof(*temp_r3));
    if (temp_r3 != NULL) {
        temp_r3->x0 = arg0;
        temp_r3->x4 = arg3;
        temp_r3->x2 = arg2;
        *arg4 = temp_r3;
        return (&temp_r3->x8);
    }
    return arg4;
}
#ifdef MUST_MATCH
#pragma pop
#endif

static u8 gm_8049E558[0x170];

void gm_ModeState_Prize_OnEnter(GameModeState* arg0)
{
    u8* var_r28;
    u32* temp_r29_2;
    u8* p3;
    u8* var_r26;
    int var_r28_3;
    s32 var_r27_2_s11;
#ifdef MUST_MATCH
    s32 var_r27_2;
#endif
    void** var_r31;
    int var_r25_2;
    void** temp_r3;
    s32 var_r30;
    gm_GetGameModeStateEnterData(arg0);
    var_r31 = 0;
    gm_GetChallengerData();
    var_r30 = 0;
    memzero(gm_8049E558, 0x42);
    p3 = &gm_8049E558[0x44];
    memzero(p3, TY_TROPHY_COUNT);
    Toy_803124BC();
#ifdef MUST_MATCH
    var_r27_2_s11 = var_r27_2;
#endif
    p3 = gm_8049E558;
    {
        int var_r25;
        u32 KP;
        for (var_r25 = 0, KP = 1; var_r25 < 0x42; var_r25++) {
            if (gm_8017219C(var_r25) != 0) {
                temp_r3 = gm_801BFC60(var_r25, var_r30, 0,
                                      *gmMainLib_8015D804(var_r25), var_r31);
                gm_8049E558[var_r25] = KP;
                var_r31 = temp_r3;
                var_r30 += 1;
            }
        }
    }
    var_r26 = p3;
    var_r26 += 0x44;
    var_r28 = var_r26;
    for (var_r25_2 = 0; var_r25_2 < TY_TROPHY_COUNT; var_r25_2++) {
        if (gmMainLib_8015DA1C(var_r25_2) != 0) {
            if (gmMainLib_8015DA90(var_r25_2) == 0) {
                u32* KP = gmMainLib_8015D970(var_r25_2);
                *KP = lbTime_GetTimeInSeconds();
                gmMainLib_8015DA40(var_r25_2);
                Toy_SetUnlockState((s16) var_r25_2, 1);
            }
            *var_r28 = Toy_803048C0(var_r25_2);
            var_r31 = gm_801BFC60(0x3E, var_r30, var_r25_2,
                                  *gmMainLib_8015D970(var_r25_2), var_r31);
            var_r30 = var_r30 + 1;
        }
        var_r28 += 1;
    }

    gm_80173EEC();
    gm_80172898(0xFFFFU);
    for (var_r28_3 = 0; var_r28_3 < 0x42; var_r28_3++, p3++) {
        if (*p3 == 0 && gm_8017219C(var_r28_3) != 0) {
            var_r31 = gm_801BFC60(var_r28_3, var_r30, 0,
                                  *gmMainLib_8015D804(var_r28_3), var_r31);
            var_r30 += 1;
        }
    }

    for (var_r27_2_s11 = 0; var_r27_2_s11 < TY_TROPHY_COUNT; var_r27_2_s11++) {
        if ((*var_r26 < Toy_803048C0(var_r27_2_s11) ||
             Toy_803048C0(var_r27_2_s11) == 0) &&
            gmMainLib_8015DA1C(var_r27_2_s11) != 0)
        {
            if (gmMainLib_8015DA90(var_r27_2_s11) == 0) {
                temp_r29_2 = gmMainLib_8015D970(var_r27_2_s11);
                *temp_r29_2 = lbTime_GetTimeInSeconds();
                gmMainLib_8015DA40(var_r27_2_s11);
                Toy_SetUnlockState((s32) ((s16) var_r27_2_s11), 1);
            }
            var_r31 = gm_801BFC60(0x3E, var_r30, var_r27_2_s11,
                                  *gmMainLib_8015D970(var_r27_2_s11), var_r31);
            var_r30 += 1;
        }
        var_r26 += 1;
    }

    gm_80172174();
    gm_80174180();
    if (var_r31 != NULL) {
        *var_r31 = 0;
    }
    lbCardGame_SetupArchive();
}

void onExitPrize(UNUSED GameModeState* state)
{
    gm_SetPendingGameMode(gm_GetChallengerData()->curr_mode);
    gm_SetNewGameModePending();
}
