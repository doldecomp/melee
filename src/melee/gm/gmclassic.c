#include "gmclassic.h"

#include "gm_unsplit.h"

#include <melee/gm/gmmain_lib.h>

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
    u8* temp_r3 = gmMainLib_8015CDC8();
    temp_r3[0] = 0x21;
    temp_r3[2] = 0;
    temp_r3[1] = 3;
    temp_r3[3] = 0;
    temp_r3[4] = 0x78;
    temp_r3[5] = 0;
}

/// #gm_801B3500

/// #gm_801B3A34

/// #gm_801B3B40

void gm_801B3D44(MinorScene* arg0)
{
    struct DebugGameOverData* temp_r31 = gm_801A427C(arg0);
    gm_8017C9A8(temp_r31, gm_8017EB30(), 1);
}

/// #gm_801B3D84

/// #gm_801B3DD8

/// #gm_801B3E44

/// #gm_801B3F18
