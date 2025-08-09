#include "gmadventure.h"

#include "gm_unsplit.h"

#include <melee/gm/gmmain_lib.h>

extern UNK_T gm_80470708[];
extern DebugGameOverData gm_80470850;
extern MatchExitInfo gm_8047086C;
extern StartMeleeData gm_80472AF8;
extern UNK_T gm_804D68D8[];
extern UNK_T gm_804D68E0[];

MinorScene gm_803DE1B8_MinorScenes[] = {
    {
        0,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        1,
        2,
        0,
        gm_801B4064,
        gm_801B44A0,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        2,
        2,
        0,
        gm_801B45A4,
        0,
        {
            MN_CUTSCENE_LUIGI,
            &gm_804D68D8,
            0,
        },
    },
    {
        3,
        2,
        0,
        gm_801B461C,
        gm_801B4684,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        8,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        9,
        2,
        0,
        gm_801B4768,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0xA,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x10,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x11,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x12,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x18,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x19,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x1A,
        2,
        0,
        gm_801B4430,
        0,
        {
            MN_CUTSCENE_BRINSTAR,
            &gm_804D68D8,
            0,
        },
    },
    {
        0x1B,
        2,
        0,
        gm_801B47FC,
        gm_801B4860,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x1C,
        2,
        0,
        0,
        0,
        {
            MN_CUTSCENE_EXPLOSION,
            0,
            0,
        },
    },
    {
        0x20,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x21,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x22,
        2,
        0,
        gm_801B4974,
        0,
        {
            MN_CUTSCENE_3KIRBYS,
            &gm_804D68D8,
            0,
        },
    },
    {
        0x23,
        2,
        0,
        gm_801B4B28,
        gm_801B4C5C,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x24,
        2,
        0,
        gm_801B4430,
        0,
        {
            MN_CUTSCENE_GIANTKIRBY,
            &gm_804D68D8,
            0,
        },
    },
    {
        0x25,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x28,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x29,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x2A,
        2,
        0,
        gm_801B4D34,
        0,
        {
            MN_CUTSCENE_STARFOX,
            0,
            0,
        },
    },
    {
        0x2B,
        2,
        0,
        gm_801B4DAC,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x30,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x31,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x38,
        2,
        0,
        0,
        0,
        {
            MN_CUTSCENE_FZERO,
            0,
            0,
        },
    },
    {
        0x39,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x3A,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x3B,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x40,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x41,
        2,
        0,
        gm_801B4E58,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x48,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x49,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x50,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x51,
        2,
        0,
        gm_801B4064,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x52,
        2,
        0,
        gm_801B4430,
        0,
        {
            MN_CUTSCENE_METAL,
            &gm_804D68D8,
            0,
        },
    },
    {
        0x53,
        2,
        0,
        gm_801B4EB8,
        gm_801B4170,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x58,
        2,
        0,
        gm_801B3F40,
        0,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            0,
        },
    },
    {
        0x59,
        2,
        0,
        gm_801B4F44,
        gm_801B4FCC,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x5A,
        2,
        0,
        gm_801B4430,
        gm_801B5078,
        {
            MN_CUTSCENE_BOWSERTOY,
            &gm_804D68D8,
            0,
        },
    },
    {
        0x5B,
        2,
        0,
        gm_801B4430,
        0,
        {
            MN_CUTSCENE_GIGATRANSFORM,
            &gm_804D68D8,
            0,
        },
    },
    {
        0x5C,
        2,
        0,
        gm_801B4064,
        gm_801B50C4,
        {
            MN_VS,
            &gm_80472AF8,
            &gm_8047086C,
        },
    },
    {
        0x5D,
        2,
        0,
        gm_801B4430,
        gm_801B518C,
        {
            MN_CUTSCENE_GIGADEFEATED,
            &gm_804D68D8,
            0,
        },
    },
    {
        0x68,
        2,
        0,
        0,
        gm_801B4408,
        {
            MN_COMING_SOON,
            0,
            0,
        },
    },
    {
        0x69,
        2,
        0,
        gm_801B4254,
        gm_801B4294,
        {
            MN_GAMEOVER,
            &gm_80470850,
            &gm_80470850,
        },
    },
    {
        0x70,
        2,
        0,
        gm_801B42E8,
        gm_801B4350,
        {
            MN_CSS,
            &gm_80470708,
            &gm_80470708,
        },
    },
    { -1 },
};

/// #gm_801B3F40

/// #gm_801B4064

/// #gm_801B4170

void gm_801B4254(MinorScene* arg0)
{
    DebugGameOverData* data = gm_801A427C(arg0);
    gm_8017C9A8(data, gm_8017E424(), 0);
}

void gm_801B4294(MinorScene* arg0)
{
    DebugGameOverData* data = gm_801A4284(arg0);
    gm_8017CA38(data, gm_8017E424(), gmMainLib_8015CDD4(), 0);
}

/// #gm_801B42E8

/// #gm_801B4350

/// #gm_801B4408

/// #gm_801B4430

/// #gm_801B44A0

/// #gm_801B45A4

/// #gm_801B461C

/// #gm_801B4684

/// #gm_801B4768

/// #gm_801B47FC

/// #gm_801B4860

/// #gm_801B4974

/// #gm_801B4B28

/// #gm_801B4C5C

/// #gm_801B4D34

/// #gm_801B4DAC

/// #gm_801B4E58

/// #gm_801B4EB8

/// #gm_801B4F44

/// #gm_801B4FCC

/// #gm_801B5078

/// #gm_801B50C4

/// #gm_801B518C

/// #gm_801B51CC_OnInit

/// #gm_801B5214_OnLoad
