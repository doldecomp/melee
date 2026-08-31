#include "gmlightning.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmmovieend.h"
#include "gmvsmelee.h"
#include "types.h"

#include "if/if_2FD9.h"

GameModeState gm_Mode_LightningVs_States[] = {
    {
        0,
        3,
        0,
        gm_801BA704,
        gm_801BA730,
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
        gm_801BA758,
        gm_801BA780,
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
        gm_801BA7B8,
        gm_801BA7EC,
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
        gm_801BA814,
        gm_801BA848,
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
        gm_801BA868,
        gm_801BA888,
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

void gm_801BA704(GameModeState* scene)
{
    gmVsMelee_EnterCss(scene, &gmMainLib_804D3EE0->unk_1350, 9);
}

void gm_801BA730(GameModeState* scene)
{
    gmVsMelee_ExitCss(scene, &gmMainLib_804D3EE0->unk_1350);
}

void gm_801BA758(GameModeState* scene)
{
    gmVsMelee_EnterSss(scene, &gmMainLib_804D3EE0->unk_1350);
}

void gm_801BA780(GameModeState* scene)
{
    gmVsMelee_ExitSss(scene, &gmMainLib_804D3EE0->unk_1350, 0);
}

/// Sets game speed to 1.25F for lightning melee
static void fn_801BA7AC(StartMeleeData* data, StartMeleeData* unused)
{
    data->rules.x34 = 1.25F;
}

void gm_801BA7B8(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_1350;
    gm_801A583C(scene, data, fn_801BA7AC, NULL);
}

void gm_801BA7EC(GameModeState* scene)
{
    gm_801A5AF0(scene, 4, 3);
}

void gm_801BA814(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_1350;
    gmVsMelee_EnterSuddenDeath(scene, data, fn_801BA7AC, NULL);
}

void gm_801BA848(GameModeState* scene)
{
    gmVsMelee_ExitSuddenDeath(scene);
}

void gm_801BA868(GameModeState* scene)
{
    gmVsMelee_EnterResults(scene);
}

void gm_801BA888(GameModeState* scene)
{
    gmVsMelee_ExitResults(scene, &gmMainLib_804D3EE0->unk_1350, 0);
}

void gm_Mode_LightningVs_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_1350);
}

void gm_Mode_LightningVs_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
