#include "gmclassic.h"

#include "gm_unsplit.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbdvd.h>

extern UNK_T gm_80470708[];
extern DebugGameOverData gm_80470850;
extern UNK_T gm_8047086C;
extern UNK_T gm_80472AF8;
extern UNK_T gm_80490880;
extern UNK_T gm_804D68D0;

MinorScene gm_803DDC58_MinorScenes[] = {
    {
        0x00,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x01,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x08,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x09,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x10,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x11,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x18,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x19,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x20,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x21,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x28,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x29,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x30,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x31,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x38,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x39,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x40,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x41,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x48,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x49,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x50,
        3,
        0,
        gm_801B3500,
        NULL,
        {
            MN_INTRO_EASY,
            &gm_80490880,
            &gm_804D68D0,
        },
    },
    {
        0x51,
        3,
        0,
        gm_801B3A34,
        gm_801B3B40,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x68,
        3,
        0,
        NULL,
        gm_801B3F18,
        { MN_COMING_SOON, NULL, NULL },
    },
    {
        0x69,
        3,
        0,
        gm_801B3D44,
        gm_801B3D84,
        {
            MN_GAMEOVER,
            &gm_80470850,
            &gm_80470850,
        },
    },
    {
        0x70,
        3,
        0,
        gm_801B3DD8,
        gm_801B3E44,
        {
            MN_CSS,
            &gm_80470708,
            &gm_80470708,
        },
    },
    { -1 },
};

/// #gm_801B2BA4

/// #gm_801B2D54

/// #gm_801B2F78_OnLoad

void gm_801B34B8_OnInit(void)
{
    struct gmm_x0_528_t* temp_r3 = gmMainLib_8015CDC8();
    temp_r3->c_kind = 0x21;
    temp_r3->color = 0;
    temp_r3->stocks = 3;
    temp_r3->cpu_level = 0;
    temp_r3->x4 = 0x78;
    temp_r3->x5 = 0;
}

/// #gm_801B3500

/// #gm_801B3A34

/// #gm_801B3B40

void gm_801B3D44(MinorScene* scene)
{
    struct DebugGameOverData* temp_r31 = gm_801A427C(scene);
    gm_8017C9A8(temp_r31, &gm_8017EB30()->x0, 1);
}

void gm_801B3D84(MinorScene* scene)
{
    DebugGameOverData* temp_r30 = gm_801A4284(scene);
    gm_8017CA38(temp_r30, &gm_8017EB30()->x0, gmMainLib_8015CDC8(), 1);
}

void gm_801B3DD8(MinorScene* scene)
{
    CSSData* css = gm_801A427C(scene);
    struct gmm_x0_528_t* temp_r31 = gmMainLib_8015CDC8();
    gm_801B06B0(css, 0xB, temp_r31->c_kind, temp_r31->stocks, temp_r31->color,
                temp_r31->x4, temp_r31->cpu_level, gm_8017EB30()->x0.x3);
    lbDvd_800174BC();
}

/// #gm_801B3E44

void gm_801B3F18(MinorScene* scene)
{
    gm_801A42E8(MJ_MENU);
    gm_801A42D4();
}
