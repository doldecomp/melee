#include "gmslomo.h"

#include "gm_unsplit.h"
#include "gmmovieend.h"
#include "gmvsdata.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>

MinorScene gm_803DF468_MinorScenes[] = {
    {
        0,
        3,
        0,
        gm_801BA50C,
        gm_801BA538,
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
        gm_801BA560,
        gm_801BA588,
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
        gm_801BA5C0,
        gm_801BA5F4,
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
        gm_801BA61C,
        gm_801BA650,
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
        gm_801BA670,
        gm_801BA690,
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

void gm_801BA50C(MinorScene* scene)
{
    gm_801A5618(scene, &gmMainLib_804D3EE0->unk_1210, 0xA);
}

void gm_801BA538(MinorScene* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_1210);
}

void gm_801BA560(MinorScene* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_1210);
}

void gm_801BA588(MinorScene* scene)
{
    gm_801A57A8(scene, &gmMainLib_804D3EE0->unk_1210, 0);
}

/// Sets game speed to 1/2 for slowmo melee
void fn_801BA5B4(StartMeleeData* data, StartMeleeData* unused)
{
    data->rules.x34 = 0.5F;
}

void gm_801BA5C0(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_1210;
    gm_801A583C(scene, data, fn_801BA5B4, NULL);
}

void gm_801BA5F4(MinorScene* scene)
{
    gm_801A5AF0(scene, 4, 3);
}

void gm_801BA61C(MinorScene* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_1210;
    gm_801A5C3C(scene, data, fn_801BA5B4, NULL);
}

void gm_801BA650(MinorScene* scene)
{
    gm_801A5EC8(scene);
}

void gm_801BA670(MinorScene* scene)
{
    gm_801A5F00(scene);
}

void gm_801BA690(MinorScene* scene)
{
    gm_801A5F64(scene, &gmMainLib_804D3EE0->unk_1210, 0);
}

void gm_801BA6BC_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_1210);
}

void gm_801BA6E4_OnLoad(void)
{
    gm_801A55C4();
}
