#include "gm_1B14.h"

#include "gm_1B0FF.h"
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

GameScene gm_803DD9A0_Scenes[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        gm_801B14A0,
        gm_801B14DC,
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
        gm_801B1514,
        gm_801B154C,
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
        gm_801B1588,
        gm_801B15C8,
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
        gm_801B1648,
        gm_801B1688,
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
        gm_801B16A8,
        gm_801B16C8,
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
        gm_801B13B8,
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
        gm_801B16A8,
        NULL,
        {
            GS_RESULTS,
            &gm_8047C020,
            NULL,
        },
    },
    { -1 },
};

void gm_801B14A0(GameScene* arg0)
{
    gm_801A5618(arg0, gm_801A5244(), 0);
}

void gm_801B14DC(GameScene* arg0)
{
    gm_801A5680(arg0, gm_801A5244());
}

void gm_801B1514(GameScene* arg0)
{
    gm_801A5754(arg0, gm_801A5244());
}

void gm_801B154C(GameScene* arg0)
{
    gm_801A57A8(arg0, gm_801A5244(), 0);
}

void gm_801B1588(GameScene* arg0)
{
    gm_801A583C(arg0, gm_801A5244(), NULL, NULL);
}

void gm_801B15C8(GameScene* arg0)
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

void gm_801B1648(GameScene* arg0)
{
    gm_801A5C3C(arg0, gm_801A5244(), NULL, NULL);
}

void gm_801B1688(GameScene* arg0)
{
    gm_801A5EC8(arg0);
}

void gm_801B16A8(GameScene* arg0)
{
    gm_801A5F00(arg0);
}

void gm_801B16C8(GameScene* arg0)
{
    gm_801A5F64(arg0, gm_801A5244(), 0);
    if (gm_801743A4(gm_8047C020.match_end.result) == 0) {
        gm_801623A4(&gm_8047C020.match_end);
    }
}
