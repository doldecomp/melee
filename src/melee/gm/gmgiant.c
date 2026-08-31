#include "gmgiant.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmmovieend.h"
#include "gmvsmelee.h"
#include "types.h"

#include "if/if_2FD9.h"

GameModeState gm_Mode_GiantVs_States[] = {
    {
        0,
        3,
        0,
        gm_801B8FB8,
        gm_801B8FE4,
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
        gm_801B900C,
        gm_801B9034,
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
        gm_801B9084,
        gm_801B90B8,
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
        gm_801B90E0,
        gm_801B9114,
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
        gm_801B9134,
        gm_801B9154,
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
        gm_801BFA6C,
        NULL,
        {
            GS_APPROACH,
            &gm_804D6860,
            &gm_804D6860,
        },
    },
    {
        0x81,
        2,
        0,
        gm_ModeState_EnterApproachVs,
        gm_ModeState_ExitApproachVs,
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

void gm_801B8FB8(GameModeState* scene)
{
    gmVsMelee_EnterCss(scene, &gmMainLib_804D3EE0->unk_F90, 4);
}

void gm_801B8FE4(GameModeState* scene)
{
    gmVsMelee_ExitCss(scene, &gmMainLib_804D3EE0->unk_F90);
}

void gm_801B900C(GameModeState* scene)
{
    gmVsMelee_EnterSss(scene, &gmMainLib_804D3EE0->unk_F90);
}

void gm_801B9034(GameModeState* scene)
{
    gmVsMelee_ExitSss(scene, &gmMainLib_804D3EE0->unk_F90, 0);
}

void fn_801B9060(PlayerInitData* arg0, PlayerInitData* unused)
{
    arg0->x20 = 1.8f;
    arg0->x1C = 1.0f;
    arg0->x18 = 1.5f;
    arg0->xB = 2;
}

void gm_801B9084(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_F90;
    gm_801A583C(scene, data, NULL, fn_801B9060);
}

void gm_801B90B8(GameModeState* scene)
{
    gm_801A5AF0(scene, 4U, 3U);
}

void gm_801B90E0(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_F90;
    gmVsMelee_EnterSuddenDeath(scene, data, NULL, fn_801B9060);
}

void gm_801B9114(GameModeState* scene)
{
    gmVsMelee_ExitSuddenDeath(scene);
}

void gm_801B9134(GameModeState* scene)
{
    gmVsMelee_EnterResults(scene);
}

void gm_801B9154(GameModeState* scene)
{
    gmVsMelee_ExitResults(scene, &gmMainLib_804D3EE0->unk_F90, 0);
}

void gm_Mode_GiantVs_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_F90);
}

void gm_Mode_GiantVs_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
