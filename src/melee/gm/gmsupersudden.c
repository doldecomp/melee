#include "gmsupersudden.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmmovieend.h"
#include "gmvsmelee.h"
#include "types.h"

#include <melee/if/if_2FD9.h>
#include <melee/mn/types.h>

GameModeState gm_Mode_SuperSuddenDeath_States[] = {
    {
        0,
        3,
        0,
        gm_801B8BB4,
        gm_801B8BE0,
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
        gm_801B8C08,
        gm_801B8C30,
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
        gm_801B8C68,
        gm_801B8C9C,
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
        gm_801B8CC4,
        gm_801B8CF4,
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
        gm_801B8D14,
        gm_801B8D34,
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

void gm_801B8BB4(GameModeState* scene)
{
    gmVsMelee_EnterCss(scene, &gmMainLib_804D3EE0->modes.unk_6D0, 3);
}

void gm_801B8BE0(GameModeState* scene)
{
    gmVsMelee_ExitCss(scene, &gmMainLib_804D3EE0->modes.unk_6D0);
}

void gm_801B8C08(GameModeState* scene)
{
    gmVsMelee_EnterSss(scene, &gmMainLib_804D3EE0->modes.unk_6D0);
}

void gm_801B8C30(GameModeState* scene)
{
    gmVsMelee_ExitSss(scene, &gmMainLib_804D3EE0->modes.unk_6D0, 0);
}

void fn_801B8C5C(PlayerInitData* arg0, PlayerInitData* unused)
{
    arg0->x12 = 0x12C;
}

void gm_801B8C68(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->modes.unk_6D0;
    gmVsMelee_EnterVs(scene, data, NULL, fn_801B8C5C);
}

void gm_801B8C9C(GameModeState* scene)
{
    gmVsMelee_ExitVs(scene, 4, 3);
}

void gm_801B8CC4(GameModeState* scene)
{
    gmVsMelee_EnterSuddenDeath(scene, &gmMainLib_804D3EE0->modes.unk_6D0, NULL,
                               NULL);
}

void gm_801B8CF4(GameModeState* scene)
{
    gmVsMelee_ExitSuddenDeath(scene);
}

void gm_801B8D14(GameModeState* scene)
{
    gmVsMelee_EnterResults(scene);
}

void gm_801B8D34(GameModeState* scene)
{
    gmVsMelee_ExitResults(scene, &gmMainLib_804D3EE0->modes.unk_6D0, 0);
}

void gm_Mode_SuperSuddenDeath_OnInit(void)
{
    gm_InitVsMode(&gmMainLib_804D3EE0->modes.unk_6D0);
}

void gm_Mode_SuperSuddenDeath_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
