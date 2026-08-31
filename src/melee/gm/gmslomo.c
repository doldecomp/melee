#include "gmslomo.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmmovieend.h"
#include "gmvsmelee.h"
#include "types.h"

#include "if/if_2FD9.h"

GameModeState gm_Mode_SlowMo_States[] = {
    {
        0,
        3,
        0,
        gm_801BA50C,
        gm_801BA538,
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
        gm_801BA560,
        gm_801BA588,
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
        gm_801BA5C0,
        gm_801BA5F4,
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
        gm_801BA61C,
        gm_801BA650,
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
        gm_801BA670,
        gm_801BA690,
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
            &gm_804D6860,
            &gm_804D6860,
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
            &un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

void gm_801BA50C(GameModeState* scene)
{
    gmVsMelee_EnterCss(scene, &gmMainLib_804D3EE0->unk_1210, 0xA);
}

void gm_801BA538(GameModeState* scene)
{
    gmVsMelee_ExitCss(scene, &gmMainLib_804D3EE0->unk_1210);
}

void gm_801BA560(GameModeState* scene)
{
    gmVsMelee_EnterSss(scene, &gmMainLib_804D3EE0->unk_1210);
}

void gm_801BA588(GameModeState* scene)
{
    gmVsMelee_ExitSss(scene, &gmMainLib_804D3EE0->unk_1210, 0);
}

/// Sets game speed to 1/2 for slowmo melee
void fn_801BA5B4(StartMeleeData* data, StartMeleeData* unused)
{
    data->rules.x34 = 0.5F;
}

void gm_801BA5C0(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_1210;
    gmVsMelee_EnterVs(scene, data, fn_801BA5B4, NULL);
}

void gm_801BA5F4(GameModeState* scene)
{
    gmVsMelee_ExitVs(scene, 4, 3);
}

void gm_801BA61C(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_1210;
    gmVsMelee_EnterSuddenDeath(scene, data, fn_801BA5B4, NULL);
}

void gm_801BA650(GameModeState* scene)
{
    gmVsMelee_ExitSuddenDeath(scene);
}

void gm_801BA670(GameModeState* scene)
{
    gmVsMelee_EnterResults(scene);
}

void gm_801BA690(GameModeState* scene)
{
    gmVsMelee_ExitResults(scene, &gmMainLib_804D3EE0->unk_1210, 0);
}

void gm_Mode_SlowMo_OnInit(void)
{
    gm_InitVsMode(&gmMainLib_804D3EE0->unk_1210);
}

void gm_Mode_SlowMo_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
