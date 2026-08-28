#include "gm_1B14.h"

#include "gm_1B03.h"
#include "gm_1B0FF.h"
#include "gmvsdata.h"

#include "gm/gm_1A3F.h"
#include "gm/gmmovieend.h"
#include "if/if_2FD9.h"

#include "lb/forward.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmresult.h"
#include "melee/gm/gmtoulib.h"
#include "melee/gm/gmvsmelee.h"
#include "melee/gm/types.h"
#include "melee/lb/lbcardgame.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/types.h"
#include "melee/mn/types.h"

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

GameScene gm_803DDAC0_Scenes[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        gm_801B1724,
        NULL,
        {
            GS_TOU_SETUP,
            NULL,
            NULL,
        },
    },
    {
        1,
        lbDvdPreload_3,
        0,
        NULL,
        NULL,
        {
            GS_TOU_BRACKET,
            NULL,
            NULL,
        },
    },
    {
        2,
        lbDvdPreload_3,
        0,
        NULL,
        NULL,
        {
            GS_TOU_ALT,
            NULL,
            NULL,
        },
    },
    {
        3,
        lbDvdPreload_3,
        0,
        gm_801B174C,
        gm_801B1788,
        {
            GS_SSS,
            &gm_8048BD20,
            &gm_8048BD20,
        },
    },
    {
        4,
        lbDvdPreload_3,
        0,
        gm_801B1810,
        gm_801B1834,
        {
            GS_VS,
            &gm_804876D8,
            &gm_80487810,
        },
    },
    {
        5,
        lbDvdPreload_3,
        0,
        gm_801B18D4,
        gm_801B1A2C,
        {
            GS_SUDDEN_DEATH,
            &gm_804876D8,
            &gm_8048BE68,
        },
    },
    {
        6,
        lbDvdPreload_3,
        0,
        gm_801B1A84,
        gm_801B1AD4,
        {
            GS_RESULTS,
            gm_80489A98,
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

void gm_801B1724(GameScene* arg0)
{
    lb_8001C550();
    lb_8001D164(0);
}

void gm_801B174C(GameScene* arg0)
{
    SSSData* sss;

    sss = gm_GetGameSceneLoadData(arg0);
    sss->x1 = 0;
    sss->no_lras = 1;
    sss->force_stage_id = -1;
    sss->unk_stage = 0;
}

void gm_801B1788(GameScene* arg0)
{
    u16 stage;
    SSSData* sss;

    sss = gm_GetGameSceneLeaveData(arg0);
    if (sss->start_game != 0) {
        gm_SetPendingSceneIndex(4);
        stage = sss->data.data.rules.xE;
        gm_GetTournamentData()->x28 = stage;
        return;
    }
    if (gm_804771C4.match_type == 0) {
        gm_8019A828();
        gm_SetPendingSceneIndex(1);
        return;
    }
    gm_GetTournamentData()->x32 = 0;
    gm_SetPendingSceneIndex(2);
}

void gm_801B1810(GameScene* arg0)
{
    StartMeleeData* data = gm_GetGameSceneLoadData(arg0);
    gm_801905F0(data);
}

void gm_801B1834(GameScene* arg0)
{
    MatchExitInfo* mei;

    mei = gm_GetGameSceneLeaveData(arg0);
    if (gm_801A52D0(&mei->match_end) != 0) {
        gm_8016260C(mei->match_end.x5, mei->match_end.result);
        gm_801628C4(mei->match_end.frame_count / 60,
                    gm_80162800(&mei->match_end));
    }
    if ((gm_80167140(&mei->match_end) != 0) &&
        (gm_8018F1B0(&mei->match_end) != 0))
    {
        gm_SetPendingSceneIndex(5);
        return;
    }
    gm_SetPendingSceneIndex(6);
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void gm_801B18D4(GameScene* arg0)
{
    StartMeleeData* smd;
    StartMeleeData* src = &gm_804876D8;
    s32 i;

    smd = gm_GetGameSceneLoadData(arg0);

    for (i = 0; i < 4; i++) {
        smd->players[i] = src->players[i];
    }

    /// @todo :: figure out how to call this not inlined
    gm_801B0474(smd, &((MatchExitInfo*) (src + 1))->match_end);
}
#ifdef MUST_MATCH
#pragma pop
#endif

void gm_801B1A2C(GameScene* arg0)
{
    MatchExitInfo* mei;

    mei = gm_GetGameSceneLeaveData(arg0);
    gm_801629B4(mei->match_end.frame_count / 60);
    gm_80166CCC(&gm_80487810.match_end, &mei->match_end);
}

void gm_801B1A84(GameScene* arg0)
{
    ResultsMatchInfo* rmi;

    rmi = gm_GetGameSceneLoadData(arg0);
    rmi->match_end = gm_80487810.match_end;
}

void gm_801B1AD4(GameScene* arg0)
{
    ResultsMatchInfo* rmi;

    rmi = gm_GetGameSceneLoadData(arg0);
    gm_80477738 = rmi->match_end;

    gm_8016247C(gm_801688AC(&rmi->match_end));
    if (gm_804771C4.match_type == 0) {
        gm_SetPendingSceneIndex(1);
        gm_GetTournamentData()->cur_option = 0x1F;
        return;
    }
    gm_8019E634();
    gm_SetPendingSceneIndex(2);
}
