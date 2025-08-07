#include "gmgiant.h"

#include "gm_unsplit.h"
#include "gmmovieend.h"
#include "gmvsdata.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>

MinorScene gm_803DF060_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801B8FB8,
        gm_801B8FE4,
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
        gm_801B900C,
        gm_801B9034,
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
        gm_801B9084,
        gm_801B90B8,
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
        gm_801B90E0,
        gm_801B9114,
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
        gm_801B9134,
        gm_801B9154,
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

void gm_801B8FB8(MinorScene* scene)
{
    gm_801A5618(scene, &gmMainLib_804D3EE0->unk_F90, 4);
}

void gm_801B8FE4(MinorScene* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_F90);
}

void gm_801B900C(MinorScene* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_F90);
}

void gm_801B9034(MinorScene* scene)
{
    gm_801A57A8(scene, &gmMainLib_804D3EE0->unk_F90, 0);
}

void fn_801B9060(PlayerInitData* arg0, PlayerInitData* unused)
{
    arg0->x20 = 1.8f;
    arg0->x1C = 1.0f;
    arg0->x18 = 1.5f;
    arg0->xB = 2;
}

void gm_801B9084(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_F90;
    gm_801A583C(scene, data, NULL, fn_801B9060);
}

void gm_801B90B8(MinorScene* scene)
{
    gm_801A5AF0(scene, 4U, 3U);
}

void gm_801B90E0(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_F90;
    gm_801A5C3C(scene, data, NULL, fn_801B9060);
}

void gm_801B9114(MinorScene* scene)
{
    gm_801A5EC8(scene);
}

void gm_801B9134(MinorScene* scene)
{
    gm_801A5F00(scene);
}

void gm_801B9154(MinorScene* scene)
{
    gm_801A5F64(scene, &gmMainLib_804D3EE0->unk_F90, 0);
}

void gm_801B9180_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_F90);
}

void gm_801B91A8_OnLoad(void)
{
    gm_801A55C4();
}
