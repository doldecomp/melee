#include "gminvisible.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmmovieend.h"
#include "gmvsmelee.h"
#include "types.h"

#include "gm/gmvsmode.h"
#include "if/if_2FD9.h"

/* 1BA30C */ static void onEnterCss(GameModeState* state);
/* 1BA338 */ static void onExitCss(GameModeState* state);
/* 1BA360 */ static void onEnterSss(GameModeState* state);
/* 1BA388 */ static void onExitSss(GameModeState* state);
/* 1BA3B4 */ static void fn_801BA3B4(PlayerInitData* arg0,
                                     PlayerInitData* unused);
/* 1BA3C8 */ static void onEnterVs(GameModeState* state);
/* 1BA3FC */ static void onExitVs(GameModeState* state);
/* 1BA424 */ static void gm_801BA424(GameModeState* state);
/* 1BA458 */ static void gm_801BA458(GameModeState* state);
/* 1BA478 */ static void gm_801BA478(GameModeState* state);
/* 1BA498 */ static void gm_801BA498(GameModeState* state);

GameModeState gm_Mode_InvisibleVs_States[] = {
    {
        gmVsMode_State_Css,
        lbDvdPreload_3,
        0,
        onEnterCss,
        onExitCss,
        {
            GS_CSS,
            &gmVsMelee_CssData,
            &gmVsMelee_CssData,
        },
    },
    {
        gmVsMode_State_Sss,
        lbDvdPreload_3,
        0,
        onEnterSss,
        onExitSss,
        {
            GS_SSS,
            &gmVsMelee_SssData,
            &gmVsMelee_SssData,
        },
    },
    {
        gmVsMode_State_Vs,
        lbDvdPreload_3,
        0,
        onEnterVs,
        onExitVs,
        {
            GS_VS,
            &gmVsMelee_StartData,
            &gmVsMelee_VsExitInfo,
        },
    },
    {
        gmVsMode_State_SuddenDeath,
        lbDvdPreload_3,
        0,
        gm_801BA424,
        gm_801BA458,
        {
            GS_SUDDEN_DEATH,
            &gmVsMelee_StartData,
            &gmVsMelee_SuddenDeathExitInfo,
        },
    },
    {
        gmVsMode_State_Results,
        lbDvdPreload_3,
        0,
        gm_801BA478,
        gm_801BA498,
        {
            GS_RESULTS,
            &gmVsMelee_ResultsEnterData,
            NULL,
        },
    },
    {
        gmVsMode_State_Approach,
        lbDvdPreload_2,
        0,
        gm_ModeState_Approach_OnEnter,
        NULL,
        {
            GS_APPROACH,
            &gm_804D6860,
            &gm_804D6860,
        },
    },
    {
        gmVsMode_State_ApproachVs,
        lbDvdPreload_2,
        0,
        gm_ModeState_ApproachVs_OnEnter,
        gm_ModeState_ApproachVs_OnExit,
        {
            GS_VS,
            &gmVsMelee_StartData,
            &gmVsMelee_VsExitInfo,
        },
    },
    {
        gmVsMode_State_Prize,
        lbDvdPreload_2,
        0,
        gm_ModeState_Prize_OnEnter,
        gm_ModeState_Prize_OnExit,
        {
            GS_PRIZE_INTERFACE,
            &un_804A1F48,
            NULL,
        },
    },
    { GM_GAMEMODESTATE_TERMINATE },
};

void onEnterCss(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->vs_invisible;
    gmVsMelee_EnterCss(scene, data, 6);
}

void onExitCss(GameModeState* scene)
{
    gmVsMelee_ExitCss(scene, &gmMainLib_804D3EE0->vs_invisible);
}

void onEnterSss(GameModeState* scene)
{
    gmVsMelee_EnterSss(scene, &gmMainLib_804D3EE0->vs_invisible);
}

void onExitSss(GameModeState* scene)
{
    gmVsMelee_ExitSss(scene, &gmMainLib_804D3EE0->vs_invisible, 0);
}

void fn_801BA3B4(PlayerInitData* start, UNUSED PlayerInitData* vs)
{
    start->vs_invisible = true;
}

void onEnterVs(GameModeState* state)
{
    VsModeData* vs = &gmMainLib_804D3EE0->vs_invisible;
    gm_801A583C(state, vs, NULL, fn_801BA3B4);
}

void onExitVs(GameModeState* state)
{
    gm_801A5AF0(state, gmVsMode_State_Results, gmVsMode_State_SuddenDeath);
}

void gm_801BA424(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->vs_invisible;
    gmVsMelee_EnterSuddenDeath(scene, data, NULL, fn_801BA3B4);
}

void gm_801BA458(GameModeState* scene)
{
    gmVsMelee_ExitSuddenDeath(scene);
}

void gm_801BA478(GameModeState* scene)
{
    gmVsMelee_EnterResults(scene);
}

void gm_801BA498(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->vs_invisible;
    gmVsMelee_ExitResults(scene, data, 0);
}

void gm_Mode_InvisibleVs_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->vs_invisible);
}

void gm_Mode_InvisibleVs_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
