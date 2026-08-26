/// @file
/// @brief Seems to deal with the challenger approaching functions.
#include "gm_1BFA.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "types.h"

#include "baselib/memory.h"
#include "if/if_2FD9.h"
#include "lb/lb_00B0.h"
#include "lb/lbcardgame.h"
#include "lb/lbcardnew.h"
#include "lb/lbtime.h"
#include "ty/toy.h"

extern UNK_T gm_804D6860[];
extern StartMeleeData gm_80480530;
extern MatchExitInfo gm_80479D98;

GameScene gm_803DFE48_Scenes[] = {
    {
        0,
        2,
        0,
        gm_801BFA6C,
        NULL,
        {
            GS_APPROACH,
            gm_804D6860,
            gm_804D6860,
        },
    },
    {
        1,
        2,
        0,
        gm_801BFABC,
        gm_801BFBA8,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        2,
        2,
        0,
        gm_801BFCFC,
        gm_801BFF7C,
        {
            GS_PRIZE_INTERFACE,
            &un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

void gm_801BFA6C(GameScene* arg0)
{
    lbl_8046DBD8_t* temp_r3;
    VsApproachData* temp_r31;

    temp_r31 = gm_GetGameSceneLoadDataCallback(arg0);
    temp_r3 = gm_GetChallengerData();
    temp_r31->x0 = temp_r3->x4;
    temp_r31->x1 = temp_r3->x2;
    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
}

void gm_801BFABC(GameScene* arg0)
{
    lbl_8046DBD8_t* temp_r31;
    StartMeleeData* temp_r30;
    u8 tmp;

    temp_r30 = gm_GetGameSceneLoadDataCallback(arg0);
    temp_r31 = gm_GetChallengerData();
    gm_80167A64(&temp_r30->rules);
    gm_80167A14(temp_r30->players);
    temp_r30->rules.x0_6 = false;
    temp_r30->rules.x0_0 = 1;
    temp_r30->rules.x0_3 = 2;
    temp_r30->rules.xE = gm_8016075C(gm_CKindToSelKind(temp_r31->x4));
    gm_801B0620(&temp_r30->players[0], temp_r31->x0, temp_r31->x1, 1,
                temp_r31->x2);
    gm_801B0664(&temp_r30->players[1], temp_r31->x4, 0, 1, 1);
    tmp = temp_r31->x3;
    temp_r30->players[0].xA = tmp;
    temp_r30->players[1].xA = 0x78;
    temp_r30->players[1].xE = 4;
    temp_r30->players[1].cpu_level = gm_80172CC0(temp_r31->x4, tmp);
    gm_8016F088(temp_r30);
}

void gm_801BFBA8(GameScene* arg0)
{
    lbl_8046DBD8_t* temp_r31;
    u8 temp_r0;
    MatchExitInfo* mei;

    mei = gm_GetGameSceneLeaveDataCallback(arg0);
    temp_r31 = gm_GetChallengerData();
    gm_80162968(mei->match_end.frame_count / 60);
    gm_8016247C((s32) mei->match_end.player_standings[0].xE);
    temp_r0 = mei->match_end.result;
    if ((temp_r0 != OUTCOME_NO_CONTEST) && (temp_r0 != OUTCOME_RETRY) &&
        (mei->match_end.player_standings[0].stocks != 0))
    {
        gm_UnlockCKind((s32) temp_r31->x4);
    } else {
        gmMainLib_8015DB2C(gm_CKindToUnlockIndex((s32) temp_r31->x4));
    }
    gm_80173EEC();
    gm_80172898(0x100U);
    if (gm_801721EC() == 0) {
        gm_SetPendingGameMode((s8) temp_r31->x5);
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
        un_804A1F48.x0 = arg0;
        un_804A1F48.x4 = arg3;
        un_804A1F48.x2 = arg2;
        return (&un_804A1F48.x8);
    }
    temp_r3 = HSD_MemAlloc(sizeof(struct un_804A1F48_t));
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

void gm_801BFCFC(GameScene* arg0)
{
    u8* var_r28;
    u32* temp_r29_2;
    u8* p3;
    u8* var_r26;
    int var_r28_3;
    s32 var_r27_2_s11;
    s32 var_r27_2;
    void** var_r31;
    int var_r25_2;
    void** temp_r3;
    s32 var_r30;
    gm_GetGameSceneLoadDataCallback(arg0);
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
                *KP = lbTime_8000AFBC();
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
                *temp_r29_2 = lbTime_8000AFBC();
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
    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
}

void gm_801BFF7C(GameScene* arg0)
{
    gm_SetPendingGameMode((s8) gm_GetChallengerData()->x5);
    gm_SetNewGameModePending();
}
