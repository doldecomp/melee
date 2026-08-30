#include "gmfixedcamera.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmvsdata.h"
#include "gmvsmelee.h"
#include "types.h"

#include "gm/gmmovieend.h"
#include "if/if_2FD9.h"
#include "mn/types.h"

GameModeState gm_Mode_CameraVs_States[] = {
    {
        0,
        3,
        0,
        gm_801B9F10,
        gm_801B9F3C,
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
        gm_801B9F64,
        gm_801B9F8C,
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
        gm_801B9FC8,
        gm_801B9FFC,
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
        gm_801BA024,
        gm_801BA058,
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
        gm_801BA078,
        gm_801BA098,
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

void gm_801B9F10(GameModeState* scene)
{
    gm_801A5618(scene, &gmMainLib_804D3EE0->unk_A90, 7);
}

void gm_801B9F3C(GameModeState* scene)
{
    gm_801A5680(scene, &gmMainLib_804D3EE0->unk_A90);
}

void gm_801B9F64(GameModeState* scene)
{
    gm_801A5754(scene, &gmMainLib_804D3EE0->unk_A90);
}

void gm_801B9F8C(GameModeState* scene)
{
    gm_801A57A8(scene, &gmMainLib_804D3EE0->unk_A90, 0);
}

void fn_801B9FB8(StartMeleeData* arg0, StartMeleeData* arg1)
{
    arg0->rules.on_unpause_override = gm_80165290;
}

void gm_801B9FC8(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_A90;
    gm_801A583C(scene, data, fn_801B9FB8, NULL);
}

void gm_801B9FFC(GameModeState* scene)
{
    gm_801A5AF0(scene, 4, 3);
}

void gm_801BA024(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_A90;
    gm_801A5C3C(scene, data, fn_801B9FB8, NULL);
}

void gm_801BA058(GameModeState* scene)
{
    gm_801A5EC8(scene);
}

void gm_801BA078(GameModeState* scene)
{
    gm_801A5F00(scene);
}

void gm_801BA098(GameModeState* scene)
{
    VsModeData* data = &gmMainLib_804D3EE0->unk_A90;
    gm_801A5F64(scene, data, 0);
}

void gm_Mode_CameraVs_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_A90);
}

void gm_Mode_CameraVs_OnLoad(void)
{
    gm_801A55C4();
}
