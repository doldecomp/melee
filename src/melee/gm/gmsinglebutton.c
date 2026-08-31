#include "gmsinglebutton.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmvsmelee.h"
#include "types.h"

#include "if/if_2FD9.h"
#include "mn/types.h"

/* extern functions referenced in Scenes */

extern void gm_ModeState_ApproachVs_OnExit(GameModeState*);
extern void gm_ModeState_Prize_OnExit(GameModeState*);

GameModeState gm_Mode_SingleButtonVs_States[] = {
    {
        0,
        3,
        0,
        gm_801BA10C,
        gm_801BA138,
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
        gm_801BA160,
        gm_801BA188,
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
        gm_801BA1C8,
        gm_801BA1FC,
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
        gm_801BA224,
        gm_801BA258,
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
        gm_801BA278,
        gm_801BA298,
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

void gm_801BA10C(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_BD0;
    gmVsMelee_EnterCss(scene, data, 8);
}

void gm_801BA138(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_BD0;
    gmVsMelee_ExitCss(scene, data);
}

void gm_801BA160(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_BD0;
    gmVsMelee_EnterSss(scene, data);
}

void gm_801BA188(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_BD0;
    gmVsMelee_ExitSss(scene, data, 0);
}

void fn_801BA1B4(StartMeleeData* data, StartMeleeData* unused)
{
    data->rules.single_button = true;
}

void gm_801BA1C8(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_BD0;
    gm_801A583C(scene, data, fn_801BA1B4, NULL);
}

void gm_801BA1FC(GameModeState* scene)
{
    gm_801A5AF0(scene, 4, 3);
}

void gm_801BA224(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_BD0;
    gmVsMelee_EnterSuddenDeath(scene, data, fn_801BA1B4, NULL);
}

void gm_801BA258(GameModeState* scene)
{
    gmVsMelee_ExitSuddenDeath(scene);
}

void gm_801BA278(GameModeState* scene)
{
    gmVsMelee_EnterResults(scene);
}

void gm_801BA298(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_BD0;
    gmVsMelee_ExitResults(scene, data, 0);
}

void gm_Mode_SingleButtonVs_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_BD0);
}

void gm_Mode_SingleButtonVs_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
