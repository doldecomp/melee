#include "gmfixedcamera.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmvsmelee.h"
#include "types.h"

#include "gm/gmmovieend.h"
#include "if/if_2FD9.h"
#include "mn/types.h"

GameModeState gm_Mode_CameraVs_States[] = {
    {
        0,
        3,
        0,
        gm_801B9F10,
        gm_801B9F3C,
        {
            GS_CSS,
            &gmVsMelee_CssData,
            &gmVsMelee_CssData,
        },
    },
    {
        1,
        3,
        0,
        gm_801B9F64,
        gm_801B9F8C,
        {
            GS_SSS,
            &gmVsMelee_SssData,
            &gmVsMelee_SssData,
        },
    },
    {
        2,
        3,
        0,
        gm_801B9FC8,
        gm_801B9FFC,
        {
            GS_VS,
            &gmVsMelee_StartData,
            &gmVsMelee_VsExitInfo,
        },
    },
    {
        3,
        3,
        0,
        gm_801BA024,
        gm_801BA058,
        {
            GS_SUDDEN_DEATH,
            &gmVsMelee_StartData,
            &gmVsMelee_SuddenDeathExitInfo,
        },
    },
    {
        4,
        3,
        0,
        gm_801BA078,
        gm_801BA098,
        {
            GS_RESULTS,
            &gmVsMelee_ResultsEnterData,
            NULL,
        },
    },
    {
        0x80,
        2,
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
        0x81,
        2,
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
        0xC0,
        2,
        0,
        gm_ModeState_Prize_OnEnter,
        gm_ModeState_Prize_OnExit,
        {
            GS_PRIZE_INTERFACE,
            &if_Scene_Prize_EnterData,
            NULL,
        },
    },
    { -1 },
};

void gm_801B9F10(GameModeState* scene)
{
    gmVsMelee_EnterCss(scene, &gmMainLib_804D3EE0->modes.vs_fixed_camera, 7);
}

void gm_801B9F3C(GameModeState* scene)
{
    gmVsMelee_ExitCss(scene, &gmMainLib_804D3EE0->modes.vs_fixed_camera);
}

void gm_801B9F64(GameModeState* scene)
{
    gmVsMelee_EnterSss(scene, &gmMainLib_804D3EE0->modes.vs_fixed_camera);
}

void gm_801B9F8C(GameModeState* scene)
{
    gmVsMelee_ExitSss(scene, &gmMainLib_804D3EE0->modes.vs_fixed_camera, 0);
}

void fn_801B9FB8(StartMeleeData* start, UNUSED StartMeleeData* vs)
{
    start->rules.on_unpause_override = gm_80165290;
}

void gm_801B9FC8(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->modes.vs_fixed_camera;
    gmVsMelee_EnterVs(scene, data, fn_801B9FB8, NULL);
}

void gm_801B9FFC(GameModeState* scene)
{
    gmVsMelee_ExitVs(scene, 4, 3);
}

void gm_801BA024(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->modes.vs_fixed_camera;
    gmVsMelee_EnterSuddenDeath(scene, data, fn_801B9FB8, NULL);
}

void gm_801BA058(GameModeState* scene)
{
    gmVsMelee_ExitSuddenDeath(scene);
}

void gm_801BA078(GameModeState* scene)
{
    gmVsMelee_EnterResults(scene);
}

void gm_801BA098(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->modes.vs_fixed_camera;
    gmVsMelee_ExitResults(scene, data, 0);
}

void gm_Mode_CameraVs_OnInit(void)
{
    gm_InitVsMode(&gmMainLib_804D3EE0->modes.vs_fixed_camera);
}

void gm_Mode_CameraVs_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
