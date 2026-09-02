#include "gminvisible.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmmovieend.h"
#include "gmvsmelee.h"
#include "types.h"

#include "gm/gmvsmode.h"
#include "if/if_2FD9.h"
#include "mn/types.h"

/* 1BA30C */ static void onEnterCss(GameModeState* state);
/* 1BA338 */ static void onExitCss(GameModeState* state);
/* 1BA360 */ static void onEnterSss(GameModeState* state);
/* 1BA388 */ static void onExitSss(GameModeState* state);
/* 1BA3B4 */ static void initVsPlayer(PlayerInitData* arg0,
                                      PlayerInitData* unused);
/* 1BA3C8 */ static void onEnterVs(GameModeState* state);
/* 1BA3FC */ static void onExitVs(GameModeState* state);
/* 1BA424 */ static void onEnterSuddenDeath(GameModeState* state);
/* 1BA458 */ static void onExitSuddenDeath(GameModeState* state);
/* 1BA478 */ static void onEnterResults(GameModeState* state);
/* 1BA498 */ static void onExitResults(GameModeState* state);

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
        onEnterSuddenDeath,
        onExitSuddenDeath,
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
        onEnterResults,
        onExitResults,
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
            &gmVsMelee_ApproachData,
            &gmVsMelee_ApproachData,
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
            &if_Scene_Prize_EnterData,
            NULL,
        },
    },
    { GM_GAMEMODESTATE_TERMINATE },
};

void onEnterCss(GameModeState* state)
{
    VsModeData* vs = &gmMainLib_804D3EE0->vs_invisible;
    gmVsMelee_EnterCss(state, vs, VS_INVISIBLE);
}

void onExitCss(GameModeState* state)
{
    gmVsMelee_ExitCss(state, &gmMainLib_804D3EE0->vs_invisible);
}

void onEnterSss(GameModeState* state)
{
    gmVsMelee_EnterSss(state, &gmMainLib_804D3EE0->vs_invisible);
}

void onExitSss(GameModeState* state)
{
    gmVsMelee_ExitSss(state, &gmMainLib_804D3EE0->vs_invisible,
                      gmVsMode_State_Css);
}

void initVsPlayer(PlayerInitData* start, UNUSED PlayerInitData* vs)
{
    start->vs_invisible = true;
}

void onEnterVs(GameModeState* state)
{
    VsModeData* vs = &gmMainLib_804D3EE0->vs_invisible;
    gmVsMelee_EnterVs(state, vs, NULL, initVsPlayer);
}

void onExitVs(GameModeState* state)
{
    gmVsMelee_ExitVs(state, gmVsMode_State_Results,
                     gmVsMode_State_SuddenDeath);
}

void onEnterSuddenDeath(GameModeState* state)
{
    VsModeData* vs = &gmMainLib_804D3EE0->vs_invisible;
    gmVsMelee_EnterSuddenDeath(state, vs, NULL, initVsPlayer);
}

void onExitSuddenDeath(GameModeState* state)
{
    gmVsMelee_ExitSuddenDeath(state);
}

void onEnterResults(GameModeState* state)
{
    gmVsMelee_EnterResults(state);
}

void onExitResults(GameModeState* state)
{
    VsModeData* vs = &gmMainLib_804D3EE0->vs_invisible;
    gmVsMelee_ExitResults(state, vs, gmVsMode_State_Css);
}

void gm_Mode_InvisibleVs_OnInit(void)
{
    gm_InitVsMode(&gmMainLib_804D3EE0->vs_invisible);
}

void gm_Mode_InvisibleVs_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
