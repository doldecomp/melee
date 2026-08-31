#include "gmtiny.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmmovieend.h"
#include "gmvsmelee.h"
#include "types.h"

#include "if/if_2FD9.h"

GameModeState gm_Mode_TinyVs_States[] = {
    {
        0,
        3,
        0,
        gm_801B8DA8,
        gm_801B8DD4,
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
        gm_801B8DFC,
        gm_801B8E24,
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
        gm_801B8E74,
        gm_801B8EA8,
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
        gm_801B8ED0,
        gm_801B8F04,
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
        gm_801B8F24,
        gm_801B8F44,
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
        gm_801BFABC,
        gm_801A6254,
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

void gm_801B8DA8(GameModeState* scene)
{
    gmVsMelee_EnterCss(scene, &gmMainLib_804D3EE0->unk_E50, 5);
}

void gm_801B8DD4(GameModeState* scene)
{
    gmVsMelee_ExitCss(scene, &gmMainLib_804D3EE0->unk_E50);
}

void gm_801B8DFC(GameModeState* scene)
{
    gmVsMelee_EnterSss(scene, &gmMainLib_804D3EE0->unk_E50);
}

void gm_801B8E24(GameModeState* scene)
{
    gmVsMelee_ExitSss(scene, &gmMainLib_804D3EE0->unk_E50, 0);
}

void fn_801B8E50(PlayerInitData* arg0, PlayerInitData* unused)
{
    arg0->x20 = 0.35f;
    arg0->x1C = 0.5f;
    arg0->x18 = 1.0f;
    arg0->xB = 1;
}

void gm_801B8E74(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_E50;
    gm_801A583C(scene, data, NULL, fn_801B8E50);
}

void gm_801B8EA8(GameModeState* scene)
{
    gm_801A5AF0(scene, 4U, 3U);
}

void gm_801B8ED0(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_E50;
    gmVsMelee_EnterSuddenDeath(scene, data, NULL, fn_801B8E50);
}

void gm_801B8F04(GameModeState* scene)
{
    gmVsMelee_ExitSuddenDeath(scene);
}

void gm_801B8F24(GameModeState* scene)
{
    gm_801A5F00(scene);
}

void gm_801B8F44(GameModeState* scene)
{
    gm_801A5F64(scene, &gmMainLib_804D3EE0->unk_E50, 0);
}

void gm_Mode_TinyVs_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_E50);
}

void gm_Mode_TinyVs_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}
