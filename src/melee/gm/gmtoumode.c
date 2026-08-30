#include "gmtoumode.h"

#include "gm_1B03.h"

#include "gm/gm_1A3F.h"

#include "lb/forward.h"

#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmtoulib.h"
#include "melee/gm/gmvsmelee.h"
#include "melee/gm/types.h"
#include "melee/lb/lbcardgame.h"
#include "melee/lb/lbcardnew.h"
#include "melee/lb/types.h"
#include "melee/mn/types.h"

/* 1B1724 */ static void gm_801B1724(GameModeState*);
/* 1B174C */ static void gm_801B174C(GameModeState*);
/* 1B1788 */ static void gm_801B1788(GameModeState*);
/* 1B1810 */ static void gm_801B1810(GameModeState*);
/* 1B1834 */ static void gm_801B1834(GameModeState*);
/* 1B18D4 */ static void gm_801B18D4(GameModeState*);
/* 1B1A2C */ static void gm_801B1A2C(GameModeState*);
/* 1B1A84 */ static void gm_801B1A84(GameModeState*);
/* 1B1AD4 */ static void gm_801B1AD4(GameModeState*);
/* 4876D8 */ static StartMeleeData gm_804876D8;
/* 487810 */ static MatchExitInfo gm_80487810;
/* 489A98 */ static UNK_T gm_80489A98[0x2288 / 4];
/* 48BD20 */ static UNK_T gm_8048BD20[0x148 / 4];
/* 48BE68 */ static UNK_T gm_8048BE68[0x23C8 / 4];

GameModeState gm_Mode_Tournament_States[] = {
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

void gm_801B1724(GameModeState* arg0)
{
    lb_8001C550();
    lb_8001D164(0);
}

void gm_801B174C(GameModeState* arg0)
{
    SSSData* sss;

    sss = gm_GetGameSceneLoadData(arg0);
    sss->x1 = 0;
    sss->no_lras = 1;
    sss->force_stage_id = -1;
    sss->unk_stage = 0;
}

void gm_801B1788(GameModeState* arg0)
{
    u16 stage;
    SSSData* sss;

    sss = gm_GetGameSceneLeaveData(arg0);
    if (sss->start_game != 0) {
        gm_SetPendingSceneIndex(4);
        stage = sss->data.data.rules.stkind;
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

void gm_801B1810(GameModeState* arg0)
{
    StartMeleeData* data = gm_GetGameSceneLoadData(arg0);
    gm_801905F0(data);
}

void gm_801B1834(GameModeState* arg0)
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
void gm_801B18D4(GameModeState* arg0)
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

void gm_801B1A2C(GameModeState* arg0)
{
    MatchExitInfo* mei;

    mei = gm_GetGameSceneLeaveData(arg0);
    gm_801629B4(mei->match_end.frame_count / 60);
    gm_80166CCC(&gm_80487810.match_end, &mei->match_end);
}

void gm_801B1A84(GameModeState* arg0)
{
    ResultsMatchInfo* rmi;

    rmi = gm_GetGameSceneLoadData(arg0);
    rmi->match_end = gm_80487810.match_end;
}

void gm_801B1AD4(GameModeState* arg0)
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
