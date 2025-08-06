#include "gmtiny.h"

#include "gm_unsplit.h"
#include "gmmovieend.h"
#include "gmvsdata.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>

MinorScene gm_803DEF88_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801B8DA8,
        gm_801B8DD4,
        {
            MN_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        1,
        3,
        0,
        gm_801B8DFC,
        gm_801B8E24,
        {
            MN_SSS,
            &gm_80480668,
            &gm_80480668,
        },
    },
    {
        2,
        3,
        0,
        gm_801B8E74,
        gm_801B8EA8,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        3,
        3,
        0,
        gm_801B8ED0,
        gm_801B8F04,
        {
            MN_SUDDEN_DEATH,
            &gm_80480530,
            &gm_8047E2A4,
        },
    },
    {
        4,
        3,
        0,
        gm_801B8F24,
        gm_801B8F44,
        {
            MN_RESULTS,
            &gm_8047C020,
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
            MN_APPROACH,
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
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        0xC0,
        2,
        0,
        gm_801BFCFC,
        gm_801A6308,
        {
            MN_PRIZE_INTERFACE,
            &un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

void gm_801B8DA8(MinorScene* scene)
{
    gm_801A5618(scene, &gmMainLib_804D3EE0->unk_E50, 5);
}

void gm_801B8DD4(MinorScene* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_E50);
}

void gm_801B8DFC(MinorScene* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_E50);
}

void gm_801B8E24(MinorScene* scene)
{
    gm_801A57A8(scene, &gmMainLib_804D3EE0->unk_E50, 0);
}

void fn_801B8E50(PlayerInitData* arg0, PlayerInitData* unused)
{
    arg0->x20 = 0.35f;
    arg0->x1C = 0.5f;
    arg0->x18 = 1.0f;
    arg0->xB = 1;
}

void gm_801B8E74(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_E50;
    gm_801A583C(scene, data, NULL, fn_801B8E50);
}

void gm_801B8EA8(MinorScene* scene)
{
    gm_801A5AF0(scene, 4U, 3U);
}

void gm_801B8ED0(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_E50;
    gm_801A5C3C(scene, data, NULL, fn_801B8E50);
}

void gm_801B8F04(MinorScene* scene)
{
    gm_801A5EC8(scene);
}

void gm_801B8F24(MinorScene* scene)
{
    gm_801A5F00(scene);
}

void gm_801B8F44(MinorScene* scene)
{
    gm_801A5F64(scene, &gmMainLib_804D3EE0->unk_E50, 0);
}

void gm_801B8F70_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_E50);
}

void gm_801B8F98_OnLoad(void)
{
    gm_801A55C4();
}
