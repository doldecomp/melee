#include "gmvsmode.h"

#include "gmvsdata.h"

#include "gm/gm_1A3F.h"
#include "gm/gmmovieend.h"
#include "if/if_2FD9.h"

#include "lb/forward.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmresult.h"
#include "melee/gm/gmvsmelee.h"
#include "melee/gm/types.h"
#include "melee/lb/types.h"

/* 1B13B8 */ static void onEnterDebugVs(GameScene*);
/* 1B14A0 */ static void onEnterCss(GameScene*);
/* 1B14DC */ static void onExitCss(GameScene*);
/* 1B1514 */ static void onEnterSss(GameScene*);
/* 1B154C */ static void OnExitSss(GameScene*);
/* 1B1588 */ static void onEnterVs(GameScene*);
/* 1B15C8 */ static void onExitVs(GameScene*);
/* 1B1648 */ static void onEnterSuddenDeath(GameScene*);
/* 1B1688 */ static void onExitSuddenDeath(GameScene*);
/* 1B16A8 */ static void onEnterResults(GameScene*);
/* 1B16C8 */ static void onExitResults(GameScene*);

GameScene gm_803DD9A0_Scenes[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        onEnterCss,
        onExitCss,
        {
            GS_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        1,
        lbDvdPreload_3,
        0,
        onEnterSss,
        OnExitSss,
        {
            GS_SSS,
            &gm_80480668,
            &gm_80480668,
        },
    },
    {
        2,
        lbDvdPreload_3,
        0,
        onEnterVs,
        onExitVs,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        3,
        lbDvdPreload_3,
        0,
        onEnterSuddenDeath,
        onExitSuddenDeath,
        {
            GS_SUDDEN_DEATH,
            &gm_80480530,
            &gm_8047E2A4,
        },
    },
    {
        4,
        lbDvdPreload_3,
        0,
        onEnterResults,
        onExitResults,
        {
            GS_RESULTS,
            &gm_8047C020,
            NULL,
        },
    },
    {
        128,
        lbDvdPreload_2,
        0,
        gm_801BFA6C,
        NULL,
        {
            GS_APPROACH,
            &gm_804D6860,
            &gm_804D6860,
        },
    },
    {
        129,
        lbDvdPreload_2,
        0,
        gm_801BFABC,
        gm_801A6254,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        192,
        lbDvdPreload_2,
        0,
        gm_801BFCFC,
        gm_801A6308,
        {
            GS_PRIZE_INTERFACE,
            &un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

GameScene gm_803DDA78_Scenes[] = {
    {
        1,
        lbDvdPreload_2,
        0,
        onEnterDebugVs,
        NULL,
        {
            GS_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        3,
        lbDvdPreload_2,
        0,
        onEnterResults,
        NULL,
        {
            GS_RESULTS,
            &gm_8047C020,
            NULL,
        },
    },
    { -1 },
};

void onEnterDebugVs(GameScene* arg0)
{
    StartMeleeData* data = gm_GetGameSceneLoadData(arg0);
    int i;

    gm_80167A64(&data->rules);
    data->rules.xE = 0x20;
    data->rules.xB = -1;
    data->rules.xC = -1;
    data->rules.x0_0 = 0;

    for (i = 0; i < 6; i++) {
        gm_8016795C(&data->players[i]);
        data->players[i].stocks = 0;
        data->players[i].xE = 4;
    }

    data->players[0].c_kind = CKIND_LINK;
    data->players[1].c_kind = CKIND_MARIO;
    data->players[2].c_kind = CKIND_LINK;
    data->players[3].c_kind = CKIND_LINK;

    data->players[0].slot_type = Gm_PKind_Human;
    data->players[1].slot_type = Gm_PKind_Human;
    data->players[2].slot_type = Gm_PKind_NA;
    data->players[3].slot_type = Gm_PKind_NA;

    data->players[0].xC_b0 = false;
    data->players[1].xC_b0 = false;
    data->players[2].xC_b0 = false;
    data->players[3].xC_b0 = false;

    gm_80168FC4();
}

void onEnterCss(GameScene* arg0)
{
    gm_801A5618(arg0, gm_801A5244(), 0);
}

void onExitCss(GameScene* arg0)
{
    gm_801A5680(arg0, gm_801A5244());
}

void onEnterSss(GameScene* arg0)
{
    gm_801A5754(arg0, gm_801A5244());
}

void OnExitSss(GameScene* arg0)
{
    gm_801A57A8(arg0, gm_801A5244(), 0);
}

void onEnterVs(GameScene* arg0)
{
    gm_801A583C(arg0, gm_801A5244(), NULL, NULL);
}

void onExitVs(GameScene* arg0)
{
    s32 i;
    MatchExitInfo* mei;

    gm_801A5AF0(arg0, 4, 3);
    mei = gm_GetGameSceneLeaveData(arg0);
    for (i = 0; i < 6; i++) {
        if (mei->match_end.player_standings[i].slot_type != Gm_PKind_NA) {
            gm_80162A98(mei->match_end.player_standings[i].x20);
            gm_80162B4C(mei->match_end.player_standings[i].self_destructs);
            gm_80162A4C(mei->match_end.player_standings[i].x44);
        }
    }
}

void onEnterSuddenDeath(GameScene* arg0)
{
    gm_801A5C3C(arg0, gm_801A5244(), NULL, NULL);
}

void onExitSuddenDeath(GameScene* arg0)
{
    gm_801A5EC8(arg0);
}

void onEnterResults(GameScene* arg0)
{
    gm_801A5F00(arg0);
}

void onExitResults(GameScene* arg0)
{
    gm_801A5F64(arg0, gm_801A5244(), 0);
    if (gm_801743A4(gm_8047C020.match_end.result) == 0) {
        gm_801623A4(&gm_8047C020.match_end);
    }
}
