#include "gmsupersudden.h"

#include "gm_unsplit.h"
#include "gmmovieend.h"
#include "gmvsdata.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/mn/types.h>

GameScene gm_803DEEB0_Scenes[] = {
    {
        0,
        3,
        0,
        gm_801B8BB4,
        gm_801B8BE0,
        {
            GS_CSS,
            &gm_804807B0,
            &gm_804807B0,
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
            &gm_80480668,
            &gm_80480668,
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
            &gm_80480530,
            &gm_80479D98,
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
            &gm_80480530,
            &gm_8047E2A4,
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
            GS_PRIZE_INTERFACE,
            &un_804A1F48,
            NULL,
        },
    },
    { -1 },
};

void gm_801B8BB4(GameScene* scene)
{
    gm_801A5618(scene, &gmMainLib_804D3EE0->unk_6D0, 3);
}

void gm_801B8BE0(GameScene* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_6D0);
}

void gm_801B8C08(GameScene* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_6D0);
}

void gm_801B8C30(GameScene* scene)
{
    gm_801A57A8(scene, &gmMainLib_804D3EE0->unk_6D0, 0);
}

void fn_801B8C5C(PlayerInitData* arg0, PlayerInitData* unused)
{
    arg0->x12 = 0x12C;
}

void gm_801B8C68(GameScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_6D0;
    gm_801A583C(scene, data, NULL, fn_801B8C5C);
}

void gm_801B8C9C(GameScene* scene)
{
    gm_801A5AF0(scene, 4, 3);
}

void gm_801B8CC4(GameScene* scene)
{
    gm_801A5C3C(scene, &gmMainLib_804D3EE0->unk_6D0, NULL, NULL);
}

void gm_801B8CF4(GameScene* scene)
{
    gm_801A5EC8(scene);
}

void gm_801B8D14(GameScene* scene)
{
    gm_801A5F00(scene);
}

void gm_801B8D34(GameScene* scene)
{
    gm_801A5F64(scene, &gmMainLib_804D3EE0->unk_6D0, 0);
}

void gm_801B8D60_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_6D0);
}

void gm_801B8D88_OnLoad(void)
{
    gm_801A55C4();
}
