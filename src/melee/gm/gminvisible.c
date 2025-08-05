#include "gminvisible.h"

#include "gm_unsplit.h"
#include "gmscextern.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>

MinorScene gm_803DF390_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801BA30C,
        gm_801BA338,
        {
            MN_CSS,
            gm_804807B0,
            gm_804807B0,
        },
    },
    {
        1,
        3,
        0,
        gm_801BA360,
        gm_801BA388,
        {
            MN_SSS,
            gm_80480668,
            gm_80480668,
        },
    },
    {
        2,
        3,
        0,
        gm_801BA3C8,
        gm_801BA3FC,
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
        gm_801BA424,
        gm_801BA458,
        {
            MN_SUDDEN_DEATH,
            &gm_80480530,
            gm_8047E2A4,
        },
    },
    {
        4,
        3,
        0,
        gm_801BA478,
        gm_801BA498,
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
            gm_804D6860,
            gm_804D6860,
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
            un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

void gm_801BA30C(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_810;
    gm_801A5618(scene, data, 6);
}

void gm_801BA338(MinorScene* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_810);
}

void gm_801BA360(MinorScene* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_810);
}

void gm_801BA388(MinorScene* scene)
{
    gm_801A57A8(scene, &gmMainLib_804D3EE0->unk_810, 0);
}

void fn_801BA3B4(PlayerInitData* arg0, PlayerInitData* unused)
{
    arg0->xC_b4 = true;
}

void gm_801BA3C8(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_810;
    gm_801A583C(scene, data, NULL, fn_801BA3B4);
}

void gm_801BA3FC(MinorScene* scene)
{
    gm_801A5AF0(scene, 4, 3);
}

void gm_801BA424(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_810;
    gm_801A5C3C(scene, data, NULL, fn_801BA3B4);
}

void gm_801BA458(MinorScene* scene)
{
    gm_801A5EC8(scene);
}

void gm_801BA478(MinorScene* scene)
{
    gm_801A5F00(scene);
}

void gm_801BA498(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_810;
    gm_801A5F64(scene, data, 0);
}

void gm_801BA4C4_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_810);
}

void gm_801BA4EC_OnLoad(void)
{
    gm_801A55C4();
}
