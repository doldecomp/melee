#include "gmsupersudden.h"

#include "gm_unsplit.h"
#include "gmmovieend.h"
#include "gmscextern.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/mn/types.h>

extern UNK_T gm_8047E2A4[];
extern UNK_T gm_80480668[];
extern UNK_T gm_804807B0[];
extern UNK_T gm_804D6860[];
extern UNK_T un_804A1F48[];
extern StartMeleeData gm_80480530;
extern MatchExitInfo gm_80479D98;
extern ResultsMatchInfo gm_8047C020;

MinorScene gm_803DEEB0_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801B8BB4,
        gm_801B8BE0,
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
        gm_801B8C08,
        gm_801B8C30,
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
        gm_801B8C68,
        gm_801B8C9C,
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
        gm_801B8CC4,
        gm_801B8CF4,
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
        gm_801B8D14,
        gm_801B8D34,
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

void gm_801B8BB4(MinorScene* scene)
{
    gm_801A5618(scene, &gmMainLib_804D3EE0->unk_6D0, 3);
}

void gm_801B8BE0(MinorScene* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_6D0);
}

void gm_801B8C08(MinorScene* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_6D0);
}

void gm_801B8C30(MinorScene* scene)
{
    gm_801A57A8(scene, &gmMainLib_804D3EE0->unk_6D0, 0);
}

void fn_801B8C5C(PlayerInitData* arg0, PlayerInitData* unused)
{
    arg0->x12 = 0x12C;
}

void gm_801B8C68(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_6D0;
    gm_801A583C(scene, data, NULL, fn_801B8C5C);
}

void gm_801B8C9C(MinorScene* scene)
{
    gm_801A5AF0(scene, 4, 3);
}

void gm_801B8CC4(MinorScene* scene)
{
    gm_801A5C3C(scene, &gmMainLib_804D3EE0->unk_6D0, NULL, NULL);
}

void gm_801B8CF4(MinorScene* scene)
{
    gm_801A5EC8(scene);
}

void gm_801B8D14(MinorScene* scene)
{
    gm_801A5F00(scene);
}

void gm_801B8D34(MinorScene* scene)
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
