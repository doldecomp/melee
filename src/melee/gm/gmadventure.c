#include "gmadventure.h"

#include "gm_unsplit.h"

#include <sysdolphin/baselib/random.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/gr/ground.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>

extern UNK_T gm_80470708[];
extern DebugGameOverData gm_80470850;
extern MatchExitInfo gm_8047086C;
extern StartMeleeData gm_80472AF8;

typedef struct CutsceneData {
    u8 x0; ///< CharacterKind
    u8 x1; ///< color
    u8 x2;
    u8 x3; ///< color
    u8 x4;
    u8 x5;
    u8 x6;
} CutsceneData;

typedef struct IntroData {
    u8 x0;
    u8 x1;
    u16 x2;
} IntroData;

static CutsceneData gm_804D68D8;
static IntroData gm_804D68E0;

/// The scenes are divided up into "blocks" for each stage of adventure mode,
/// in multiples of 8. Skipping to the next block goes on to the next stage.
#define NEXT_SCENEBLOCK_AFTER(x) (((x) + 8) & ~(8 - 1))

/// @todo fill this out with the rest of the scenes
enum {
    ADVENTURE_INTRO = 0x0,
    ADVENTURE_MUSHROOM_KINGDOM,
    ADVENTURE_LUIGI_CUTSCENE,
    ADVENTURE_MARIO_PEACH_FIGHT,

    ADVENTURE_KIRBY_INTRO = 0x20,
    ADVENTURE_KIRBY_FIGHT,
    ADVENTURE_TEAMKIRBY_INTRO,
    ADVENTURE_TEAMKIRBY_FIGHT,
    ADVENTURE_GIANTKIRBY_INTRO,
    ADVENTURE_GIANTKIRBY_FIGHT,

    ADVENTURE_BACK_TO_CSS = 0x70,
};

MinorScene gm_803DE1B8_MinorScenes[] = {
    {
        ADVENTURE_INTRO,
        2,
        0,
        gm_801B3F40,
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
        },
    },
    {
        ADVENTURE_MUSHROOM_KINGDOM,
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
        ADVENTURE_LUIGI_CUTSCENE,
        2,
        0,
        gm_801B45A4,
        NULL,
        {
            MN_CUTSCENE_LUIGI,
            &gm_804D68D8,
            NULL,
        },
    },
    {
        ADVENTURE_MARIO_PEACH_FIGHT,
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
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
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
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
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
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
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
        NULL,
        {
            MN_CUTSCENE_BRINSTAR,
            &gm_804D68D8,
            NULL,
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
        NULL,
        NULL,
        {
            MN_CUTSCENE_EXPLOSION,
            NULL,
            NULL,
        },
    },
    {
        ADVENTURE_KIRBY_INTRO,
        2,
        0,
        gm_801B3F40,
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
        },
    },
    {
        ADVENTURE_KIRBY_FIGHT,
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
        ADVENTURE_TEAMKIRBY_INTRO,
        2,
        0,
        gm_801B4974,
        NULL,
        {
            MN_CUTSCENE_3KIRBYS,
            &gm_804D68D8,
            NULL,
        },
    },
    {
        ADVENTURE_TEAMKIRBY_FIGHT,
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
        ADVENTURE_GIANTKIRBY_INTRO,
        2,
        0,
        gm_801B4430,
        NULL,
        {
            MN_CUTSCENE_GIANTKIRBY,
            &gm_804D68D8,
            0,
        },
    },
    {
        ADVENTURE_GIANTKIRBY_FIGHT,
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
        NULL,
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
        NULL,
        {
            MN_CUTSCENE_STARFOX,
            NULL,
            NULL,
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
            NULL,
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
        NULL,
        NULL,
        {
            MN_CUTSCENE_FZERO,
            NULL,
            NULL,
        },
    },
    {
        0x39,
        2,
        0,
        gm_801B3F40,
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
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
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
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
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
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
        NULL,
        {
            MN_CUTSCENE_METAL,
            &gm_804D68D8,
            NULL,
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
        NULL,
        {
            MN_INTRO_NORMAL,
            &gm_804D68E0,
            NULL,
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
            NULL,
        },
    },
    {
        0x5B,
        2,
        0,
        gm_801B4430,
        NULL,
        {
            MN_CUTSCENE_GIGATRANSFORM,
            &gm_804D68D8,
            NULL,
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
            NULL,
        },
    },
    {
        0x68,
        2,
        0,
        NULL,
        gm_801B4408,
        {
            MN_COMING_SOON,
            NULL,
            NULL,
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
        ADVENTURE_BACK_TO_CSS,
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

struct gm_803DE650_t gm_803DE650[] = {
    {
        0x00,
        0x00,
        0x0000,
        0x0000,
        0x003B,
        0x04,
        0x00,
        CKIND_YOSHI,
        CKIND_YOSHI,
        CKIND_YOSHI,
    },
    {
        0x01,
        0x09,
        0x01A4,
        0x0000,
        0x003B,
        0x04,
        0x00,
        CKIND_YOSHI,
        CKIND_YOSHI,
        CKIND_YOSHI,
    },
    {
        0x02,
        0x00,
        0x0000,
        0x0000,
        0x003B,
        0x04,
        0x00,
        CHKIND_NONE,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x03,
        0x00,
        0x00F0,
        0x0000,
        0x003C,
        0x03,
        0x00,
        CKIND_MARIO,
        CKIND_PEACH,
        CHKIND_NONE,
    },
    {
        0x08,
        0x00,
        0x0000,
        0x0000,
        0x003D,
        0x04,
        0x00,
        CKIND_DONKEY,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x09,
        0x00,
        0x00F0,
        0x0000,
        0x003D,
        0x03,
        0x00,
        CKIND_DONKEY,
        CKIND_DONKEY,
        CHKIND_NONE,
    },
    {
        0x0A,
        0x02,
        0x00F0,
        0x0000,
        0x003E,
        0x02,
        0x00,
        CKIND_DONKEY,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x10,
        0x00,
        0x0000,
        0x0000,
        0x003F,
        0x04,
        0x00,
        CKIND_LINK,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x11,
        0x09,
        0x01A4,
        0x0000,
        0x003F,
        0x04,
        0x00,
        CKIND_LINK,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x12,
        0x00,
        0x00F0,
        0x0000,
        0x0040,
        0x02,
        0x00,
        CKIND_ZELDA,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x18,
        0x00,
        0x0000,
        0x0000,
        0x0041,
        0x04,
        0x00,
        CKIND_SAMUS,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x19,
        0x00,
        0x00F0,
        0x0000,
        0x0041,
        0x02,
        0x00,
        CKIND_SAMUS,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x1A,
        0x00,
        0x0000,
        0x0000,
        0x0042,
        0x04,
        0x00,
        CHKIND_NONE,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x1B,
        0x41,
        0x0028,
        0x0000,
        0x0042,
        0x04,
        0xFF,
        CHKIND_NONE,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x1C,
        0x00,
        0x0000,
        0x0000,
        0x0042,
        0x04,
        0x00,
        CHKIND_NONE,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x20,
        0x00,
        0x0000,
        0x0000,
        0x0043,
        0x04,
        0x00,
        CKIND_KIRBY,
        CKIND_KIRBY,
        CKIND_KIRBY,
    },
    {
        0x21,
        0x00,
        0x00F0,
        0x0000,
        0x0043,
        0x02,
        0x00,
        CKIND_KIRBY,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x22,
        0x00,
        0x0000,
        0x000F,
        0x0044,
        0x04,
        0x00,
        CKIND_KIRBY,
        CKIND_KIRBY,
        CKIND_KIRBY,
    },
    {
        0x23,
        0x08,
        0x00F0,
        0x000F,
        0x0044,
        0x04,
        0x00,
        CKIND_KIRBY,
        CKIND_KIRBY,
        CKIND_KIRBY,
    },
    {
        0x24,
        0x00,
        0x0000,
        0x0000,
        0x0045,
        0x04,
        0x00,
        CHKIND_NONE,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x25,
        0x02,
        0x00F0,
        0x0000,
        0x0045,
        0x02,
        0x00,
        CKIND_KIRBY,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x28,
        0x00,
        0x0000,
        0x0000,
        0x0046,
        0x04,
        0x00,
        CKIND_FOX,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x29,
        0x00,
        0x00F0,
        0x0000,
        0x0046,
        0x02,
        0x00,
        CKIND_FOX,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x2A,
        0x00,
        0x0000,
        0x0000,
        0x0047,
        0x04,
        0x00,
        CKIND_FOX,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x2B,
        0x00,
        0x00F0,
        0x0000,
        0x0047,
        0x02,
        0x00,
        CKIND_FOX,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x30,
        0x00,
        0x0000,
        0x0000,
        0x0048,
        0x04,
        0x00,
        CKIND_PIKACHU,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x31,
        0x08,
        0x00F0,
        0x000C,
        0x0048,
        0x04,
        0x00,
        CKIND_PIKACHU,
        CKIND_PICHU,
        CKIND_PURIN,
    },
    {
        0x38,
        0x00,
        0x0000,
        0x0000,
        0x0049,
        0x04,
        0x00,
        CHKIND_NONE,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x39,
        0x00,
        0x0000,
        0x0000,
        0x0049,
        0x04,
        0x00,
        CKIND_CAPTAIN,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x3A,
        0x41,
        0x00F0,
        0x0000,
        0x0049,
        0x04,
        0x00,
        CHKIND_NONE,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x3B,
        0x00,
        0x00F0,
        0x0000,
        0x004A,
        0x02,
        0x00,
        CKIND_CAPTAIN,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x40,
        0x00,
        0x0000,
        0x0000,
        0x004B,
        0x04,
        0x00,
        CKIND_NESS,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x41,
        0x00,
        0x00F0,
        0x0000,
        0x004B,
        0x04,
        0x00,
        0x0B,
        0x0B,
        0x0B,
        0x00,
        0x00,
        0x00,
    },
    {
        0x48,
        0x00,
        0x0000,
        0x0000,
        0x004C,
        0x04,
        0x00,
        CKIND_POPONANA,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x49,
        0x09,
        0x00F0,
        0x0000,
        0x004C,
        0x04,
        0x00,
        CKIND_POPONANA,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x50,
        0x00,
        0x0000,
        0x0000,
        0x004E,
        0x04,
        0x00,
        CKIND_BOY,
        CKIND_GIRL,
        CHKIND_NONE,
    },
    {
        0x51,
        0x08,
        0x00F0,
        0x000F,
        0x004E,
        0x06,
        0x00,
        CKIND_BOY,
        CKIND_GIRL,
        CHKIND_NONE,
    },
    {
        0x52,
        0x00,
        0x0000,
        0x0000,
        0x004F,
        0x04,
        0x00,
        CKIND_MARIO,
        CKIND_LUIGI,
        CHKIND_NONE,
    },
    {
        0x53,
        0x04,
        0x00F0,
        0x0000,
        0x004F,
        0x03,
        0x00,
        CKIND_MARIO,
        CKIND_LUIGI,
        CHKIND_NONE,
    },
    {
        0x58,
        0x00,
        0x0000,
        0x0000,
        0x0050,
        0x04,
        0x00,
        CKIND_KOOPA,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x59,
        0x02,
        0x00F0,
        0x0000,
        0x0050,
        0x02,
        0x00,
        CKIND_KOOPA,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x5A,
        0x00,
        0x0000,
        0x0000,
        0x0050,
        0x04,
        0x00,
        CKIND_KOOPA,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x5B,
        0x00,
        0x0000,
        0x0000,
        0x0051,
        0x04,
        0x00,
        CKIND_GKOOPS,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x5C,
        0x20,
        0x00F0,
        0x0000,
        0x0051,
        0x02,
        0x00,
        CKIND_GKOOPS,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    {
        0x5D,
        0x00,
        0x00F0,
        0x0000,
        0x0051,
        0x02,
        0x00,
        CKIND_GKOOPS,
        CHKIND_NONE,
        CHKIND_NONE,
    },
    { 0xFF },
};

static u8 gm_80490910[ARRAY_SIZE(gm_803DE650)];

static inline int getIndex(int scene_id)
{
    return ((uintptr_t) gm_8017E4C4(scene_id) - (uintptr_t) gm_803DE650) /
           sizeof(gm_803DE650[0]);
}

static inline void setValUnk(int scene_id, bool temp_r30)
{
    int i = ((uintptr_t) gm_8017E4C4(scene_id) - (uintptr_t) gm_803DE650) /
            sizeof(gm_803DE650[0]);
    if (temp_r30 != 0) {
        gm_80490910[i] = 2;
    } else {
        gm_80490910[i] = 1;
    }
}

void gm_801B3F40(MinorScene* arg0)
{
    struct gm_803DE650_t* temp_r31;
    UnkAdventureData* temp_r3;
    u64 temp_ret;
    IntroData* temp_r30;
    int i;

    temp_ret = 0;
    temp_r30 = gm_801A427C(arg0);
    temp_r31 = gm_8017E4C4(arg0->idx);
    temp_r3 = gm_8017E424();
    temp_r3->x0.x7 = arg0->idx;
    temp_r30->x1 = gm_8017BE84(arg0->idx);
    temp_r30->x2 = temp_r31->x6;
    temp_r30->x0 = temp_r3->x0.slot;
    temp_ret |= lbAudioAx_80026E84(temp_r3->x0.ckind);
    for (i = 0; i < 3; i++) {
        s8 ckind = temp_r3->x0.xC.x24[i].ckind;
        if (ckind != CHKIND_NONE) {
            temp_ret |= lbAudioAx_80026E84(ckind);
        }
    }
    for (i = 0; i < 3; i++) {
        if (temp_r31->xA[i] != CHKIND_NONE) {
            temp_ret |= lbAudioAx_80026E84(temp_r31->xA[i]);
            if (temp_r31->xA[i] == CKIND_KIRBY) {
                temp_ret |= 0x200004000;
            }
        }
    }
    temp_ret |= lbAudioAx_80026EBC(temp_r31->x6);
    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC, temp_ret);
    lbAudioAx_80027168();
}

void gm_801B4064(MinorScene* arg0)
{
    struct gm_803DE650_t* temp_r31;
    int var_r30;
    int var_r29;
    StartMeleeData* temp_r28;
    UnkAdventureData* temp_r27;
    u8 tmp;

    PAD_STACK(8);

    temp_r28 = gm_801A427C(arg0);
    temp_r31 = gm_8017E4C4(arg0->idx);
    temp_r27 = gm_8017E424();
    if (temp_r31->x4 != 0) {
        var_r30 = 1;
        var_r29 = 0;
    } else {
        var_r30 = 0;
        var_r29 = 1;
    }
    temp_r27->x0.x8 = temp_r31->x1;
    temp_r27->x0.x9 = 0;
    temp_r27->x0.xB = temp_r31->x8;
    temp_r27->x0.xA = temp_r31->x9;
    tmp = gm_80490910[getIndex(arg0->idx)];

    gm_8017CE34(temp_r28, temp_r27, temp_r31->xA, temp_r31->x4, var_r30,
                var_r29, temp_r31->x2, temp_r31->x6, gm_8017E48C(arg0), tmp);
    gm_8016F088(temp_r28);
    if (temp_r31->x1 & 8) {
        temp_r28->rules.x44 = gm_8017C838;
    }
}

void gm_801B4170(MinorScene* arg0)
{
    MatchExitInfo* temp_r28 = gm_801A4284(arg0);
    UnkAdventureData* temp_r31 = gm_8017E424();
    setValUnk(arg0->idx, temp_r28->x8);
    if (gm_8017D7AC(temp_r28, &temp_r31->x0, 0x69) &&
        gm_8017E4C4(arg0->idx)[1].x0 == 0xFF)
    {
        gm_8017CBAC(temp_r31, gmMainLib_8015CDD4(), 0x16);
    }
}

void gm_801B4254(MinorScene* scene)
{
    DebugGameOverData* data = gm_801A427C(scene);
    gm_8017C9A8(data, &gm_8017E424()->x0, 0);
}

void gm_801B4294(MinorScene* scene)
{
    DebugGameOverData* data = gm_801A4284(scene);
    gm_8017CA38(data, &gm_8017E424()->x0, gmMainLib_8015CDD4(), 0);
}

void gm_801B42E8(MinorScene* scene)
{
    CSSData* css = gm_801A427C(scene);
    struct gmm_x0_528_t* temp_r31 = gmMainLib_8015CDD4();
    gm_801B06B0(css, 0xC, temp_r31->c_kind, temp_r31->stocks, temp_r31->color,
                temp_r31->x4, temp_r31->cpu_level, gm_8017E424()->x0.slot);
}

void gm_801B4350(MinorScene* scene)
{
    CSSData* css = gm_801A4284(scene);
    struct gmm_x0_528_t* temp_r29 = gmMainLib_8015CDD4();
    UnkAdventureData* temp_r31 = gm_8017E424();

    if (css->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_801B0730(css, &temp_r29->c_kind, &temp_r29->stocks, &temp_r29->color,
                &temp_r29->x4, &temp_r29->cpu_level);
    temp_r31->x0.ckind = temp_r29->c_kind;
    temp_r31->x0.color = temp_r29->color;
    temp_r31->x0.cpu_level = temp_r29->cpu_level;
    temp_r31->x0.stocks = temp_r29->stocks;
    temp_r31->x0.x4 = temp_r29->x4;
    gm_SetScenePendingMinor(temp_r29->x5 << 3);
    gm_80168F88();
}

void gm_801B4408(MinorScene* scene)
{
    gm_801A42E8(MJ_MENU);
    gm_801A42D4();
}

void gm_801B4430(MinorScene* scene)
{
    CutsceneData* temp_r30 = gm_801A427C(scene);
    struct gmm_x0_528_t* temp_r31 = gmMainLib_8015CDD4();
    UnkAdventureData* temp_r3 = gm_8017E424();
    u8 var_r0;

    if (temp_r3->x0.ckind == CKIND_ZELDA && temp_r3->x0.xC.x12 != 0) {
        var_r0 = CKIND_SEAK;
    } else {
        var_r0 = temp_r3->x0.ckind;
    }
    temp_r30->x0 = var_r0;
    temp_r30->x1 = temp_r31->color;
}

void gm_801B44A0(MinorScene* scene)
{
    MatchExitInfo* temp_r30 = gm_801A4284(scene);
    UnkAdventureData* temp_r29 = gm_8017E424();

    setValUnk(scene->idx, temp_r30->x8);

    if (gm_8017D7AC(temp_r30, &temp_r29->x0, 0x69)) {
        /**
         * Luigi challenger approaching condition:
         * Reach the flagpole with 2 in the seconds place
         */
        u32 seconds = temp_r30->x4 % 60;
        if (seconds % 10 == 2) {
            gm_SetScenePendingMinor(ADVENTURE_LUIGI_CUTSCENE);
        } else {
            gm_SetScenePendingMinor(ADVENTURE_MARIO_PEACH_FIGHT);
        }
    }
}

void gm_801B45A4(MinorScene* scene)
{
    CutsceneData* temp_r31 = gm_801A427C(scene);
    UnkAdventureData* temp_r7 = gm_8017E424();
    u8 colors[3] = { 0 };
    s8 ckinds[3] = { CKIND_MARIO, CKIND_LUIGI, CHKIND_NONE };

    gmRegSetupEnemyColorTable(temp_r7->x0.ckind, temp_r7->x0.color, ckinds,
                              colors);
    temp_r31->x1 = colors[0];
    temp_r31->x3 = colors[1];
}

void gm_801B461C(MinorScene* scene)
{
    gm_801B4064(scene);

    /// If we got here from the Luigi cutscene, change Mario to Luigi.
    if (gm_801A42B4() == ADVENTURE_LUIGI_CUTSCENE) {
        StartMeleeData* data = gm_801A427C(scene);
        UnkAdventureData* adventure = gm_8017E424();
        data->players[1].c_kind = CKIND_LUIGI;
        data->players[1].color = gm_804D68D8.x3;
        adventure->x74 = 1;
    }
}

void gm_801B4684(MinorScene* scene)
{
    MatchExitInfo* temp_r29 = gm_801A4284(scene);
    UnkAdventureData* temp_r31 = gm_8017E424();

    setValUnk(scene->idx, temp_r29->x8);

    if (gm_8017D7AC(temp_r29, &temp_r31->x0, 0x69)) {
        /// Unlock conditions for Luigi (match completed in under 1 minute)
        if (temp_r29->match_end.frame_count / 60 <= 60) {
            temp_r31->x75 = 1;
        } else {
            temp_r31->x75 = 0;
        }
    }
}

void gm_801B4768(MinorScene* scene)
{
    StartMeleeData* data = gm_801A427C(scene);
    int i;
    gm_801B4064(scene);
    for (i = 0; i < 3; i++) {
        if (data->players[i + 1].slot_type == Gm_PKind_Cpu) {
            data->players[i + 1].x20 *= 0.5F;
        }
    }
}

void gm_801B47FC(MinorScene* scene)
{
    UnkAdventureData* temp_r31;
    StartMeleeData* temp_r30;

    temp_r30 = gm_801A427C(scene);
    temp_r31 = gm_8017E424();
    gm_801B4064(scene);
    temp_r30->rules.x50 = gm_8017E7A0;
    temp_r31->x0.x7 = 0x20;
}

static inline void gm_801B4860_inline0(MinorScene* scene)
{
    MatchExitInfo* exit_info = gm_801A4284(scene);
    if (exit_info->match_end.result != 1) {
        UnkAdventureData* tmp = gm_8017E424();
        tmp->x76 = 1;
    } else {
        exit_info->match_end.player_standings[0].stocks++;
    }
}

static inline void gm_801B4860_inline1(MinorScene* scene)
{
    MatchExitInfo* exit_info = gm_801A4284(scene);
    UnkAdventureData* adv_data = gm_8017E424();

    setValUnk(scene->idx, exit_info->x8);

    if (gm_8017D7AC(exit_info, &adv_data->x0, 0x69) &&
        gm_8017E4C4(scene->idx)[1].x0 == 0xFF)
    {
        gm_8017CBAC(adv_data, gmMainLib_8015CDD4(), 0x16);
    }
}

void gm_801B4860(MinorScene* scene)
{
    gm_801B4860_inline0(scene);
    gm_801B4860_inline1(scene);
}

void gm_801B4974(MinorScene* arg0)
{
    int count;
    UnkAdventureData* temp_r29;
    UnkAdventureData* temp_r3;
    struct gm_803DE650_t* temp_r25_2;
    struct gm_803DE650_t* temp_r30;
    struct gmm_x0_528_t* temp_r24;
    u8 temp_r3_2;
    s8 var_r4;
    u8* temp_r24_2;
    CutsceneData* temp_r25;
    CutsceneData* temp_r28;
    u8* temp_r31;

    temp_r28 = gm_801A427C(arg0);
    temp_r29 = gm_8017E424();
    temp_r25 = gm_801A427C(arg0);
    temp_r24 = gmMainLib_8015CDD4();
    temp_r3 = gm_8017E424();
    var_r4 = temp_r3->x0.ckind;
    if (var_r4 == CKIND_ZELDA && temp_r3->x0.xC.x12 != 0) {
        var_r4 = CKIND_SEAK;
    }
    temp_r25->x0 = var_r4;
    temp_r25->x1 = temp_r24->color;
    temp_r30 = gm_8017E4C4(arg0->idx);
    temp_r24_2 = gm_80169520();
    temp_r31 = gm_80169540();
    count = gm_8017E48C(arg0);
    temp_r25_2 = gm_8017E4C4(arg0->idx);
    gm_8016A22C(temp_r25_2->xA[0], temp_r25_2->xA[1], temp_r25_2->xA[2],
                temp_r25_2->xD, temp_r25_2->xE, temp_r25_2->xF, 1, 0, 1,
                temp_r29->x0.ckind, temp_r29->x0.color,
                temp_r29->x4C(count, temp_r29->x0.cpu_level, 0),
                temp_r25_2->x4, gm_8017BE8C(temp_r25_2->xA), 1, 0, 1,
                temp_r29->x64(count, temp_r29->x0.cpu_level),
                temp_r29->x68(count, temp_r29->x0.cpu_level));

    temp_r29->x0.xC.x11 = 1;
    temp_r28->x3 = *temp_r24_2;
    temp_r28->x4 = temp_r31[temp_r30->x4 - 2];
    temp_r28->x5 = temp_r31[temp_r30->x4 - 1];
    temp_r28->x6 = temp_r31[temp_r30->x4 - 3];
}

static inline void inline0(MinorScene* scene)
{
    UnkAdventureData* adv_data = gm_8017E424();
    if (adv_data->x0.xC.x11 != 1) {
        UNK_T unused1 = gm_80169520();
        UNK_T unused2 = gm_80169540();
        int count = gm_8017E48C(scene);
        struct gm_803DE650_t* temp_r29 = gm_8017E4C4(scene->idx);
        gm_8016A22C(temp_r29->xA[0], temp_r29->xA[1], temp_r29->xA[2],
                    temp_r29->xD, temp_r29->xE, temp_r29->xF, 1, 0, 1,
                    adv_data->x0.ckind, adv_data->x0.color,
                    adv_data->x4C(count, adv_data->x0.cpu_level, 0),
                    temp_r29->x4, gm_8017BE8C(temp_r29->xA), 1, 0, 1,
                    adv_data->x64(count, adv_data->x0.cpu_level),
                    adv_data->x68(count, adv_data->x0.cpu_level));
        adv_data->x0.xC.x11 = 1;
    }
}

void gm_801B4B28(MinorScene* scene)
{
    inline0(scene);
    gm_801B4064(scene);
}

void gm_801B4C5C(MinorScene* scene)
{
    MatchExitInfo* temp_r30 = gm_801A4284(scene);
    UnkAdventureData* temp_r29 = gm_8017E424();

    setValUnk(scene->idx, temp_r30->x8);

    /// If the player took longer than 30 seconds, skip the Giant Kirby battle.
    if (gm_8017D7AC(temp_r30, &temp_r29->x0, 0x69) &&
        temp_r30->match_end.frame_count / 60 > 30)
    {
        gm_SetScenePendingMinor(
            NEXT_SCENEBLOCK_AFTER(ADVENTURE_GIANTKIRBY_FIGHT));
    }
}

void gm_801B4D34(MinorScene* scene)
{
    UnkAdventureData* temp_r30 = gm_8017E424();
    struct gm_803DE650_t* temp_r31 = gm_8017E4C4(scene->idx);

    /**
     * If Falco is unlocked,
     * the player will fight him instead about 1/3 of the time.
     */
    if (gm_80164840(CKIND_FALCO) && HSD_Randi(100) <= 33) {
        temp_r30->x7C = CKIND_FALCO;
    } else {
        temp_r30->x7C = temp_r31->xA[0];
    }
}

void gm_801B4DAC(MinorScene* scene)
{
    UnkAdventureData* temp_r30 = gm_8017E424();
    StartMeleeData* data = gm_801A427C(scene);
    gm_801B4064(scene);
    if (temp_r30->x7C == CKIND_FALCO) {
        s8 ckinds[3] = { CKIND_FALCO, CHKIND_NONE, CHKIND_NONE };
        u8 colors[3] = { 0 };
        colors[0] = data->players[1].color;
        gmRegSetupEnemyColorTable(temp_r30->x0.ckind, temp_r30->x0.color,
                                  ckinds, colors);
        data->players[1].c_kind = CKIND_FALCO;
        data->players[1].color = colors[0];
    }
}

void gm_801B4E58(MinorScene* scene)
{
    StartMeleeData* data;
    gm_8017E424();
    data = gm_801A427C(scene);
    gm_801B4064(scene);
    data->rules.x20 = 1 << 7; ///< enabling an item, which one?
    data->rules.xB = 4;
}

void gm_801B4EB8(MinorScene* scene)
{
    StartMeleeData* data = gm_801A427C(scene);
    int i;
    gm_801B4064(scene);

    /// If Luigi isn't unlocked, don't spawn him for this match.
    if (!gm_80164840(CKIND_LUIGI)) {
        for (i = 0; i < 3; i++) {
            if (data->players[i + 1].c_kind == CKIND_LUIGI) {
                data->players[i + 1].slot_type = Gm_PKind_NA;
            }
        }
    }
}

void gm_801B4F44(MinorScene* scene)
{
    StartMeleeData* data = gm_801A427C(scene);
    int i;
    gm_801B4064(scene);
    for (i = 0; i < 3; i++) {
        if (data->players[i + 1].slot_type == Gm_PKind_Cpu) {
            data->players[i + 1].x20 = 1.4F;
        }
    }
    data->rules.x50 = gm_8017E7FC;
}

void gm_801B4FCC(MinorScene* scene)
{
    MatchExitInfo* temp_r30 = gm_801A4284(scene);
    UnkAdventureData* temp_r29 = gm_8017E424();
    setValUnk(scene->idx, temp_r30->x8);
    gm_8017D7AC(temp_r30, &temp_r29->x0, 0x69);
}

void gm_801B5078(MinorScene* scene)
{
    UnkAdventureData* temp_r3 = gm_8017E424();
    if (temp_r3->x77 == 0) {
        gm_8017CBAC(temp_r3, gmMainLib_8015CDD4(), 0x16);
    }
}

void gm_801B50C4(MinorScene* scene)
{
    MatchExitInfo* temp_r31 = gm_801A4284(scene);
    UnkAdventureData* temp_r30 = gm_8017E424();

    UnkAdventureData* temp_r3 = gm_8017E424();
    if (temp_r3->x0.stocks == temp_r31->match_end.player_standings[0].stocks) {
        temp_r3->x78 = 1;
    }

    setValUnk(scene->idx, temp_r31->x8);

    gm_8017D7AC(temp_r31, &temp_r30->x0, 0x69);
}

void gm_801B518C(MinorScene* scene)
{
    UnkAdventureData* data = gm_8017E424();
    gm_8017CBAC(data, gmMainLib_8015CDD4(), 0x16);
}

void gm_801B51CC_OnInit(void)
{
    struct gmm_x0_528_t* temp_r3;

    temp_r3 = gmMainLib_8015CDD4();
    temp_r3->c_kind = CHKIND_NONE;
    temp_r3->color = 0;
    temp_r3->stocks = 3;
    temp_r3->cpu_level = 0;
    temp_r3->x4 = 0x78;
    temp_r3->x5 = 0;
}

void gm_801B5214_OnLoad(void)
{
    int i;
    int j;
    UnkAdventureData* data;

    data = gm_8017E424();
    gmMainLib_8015CDD4();
    gm_8017C984(data);
    memzero(data, sizeof(*data));
    data->x74 = 0;

    for (i = 0; i < ARRAY_SIZE(gm_80490910); i++) {
        gm_80490910[i] = 0;
    }

    gm_8017DB58(data->x0.xC.x24);
    data->x0.slot = gm_801677F0();
    data->x48 = gm_8017E500;
    data->x4C = gm_8017E5C8;
    data->x50 = gm_8017E630;
    data->x54 = gm_8017E5FC;
    data->x64 = gm_8017E528;
    data->x68 = gm_8017E578;
    data->x58 = gm_8017E704;
    data->x5C = gm_8017E76C;
    data->x60 = gm_8017E738;
    data->x6C = gm_8017E664;
    data->x70 = gm_8017E6B4;
    gm_SetSceneMinor(ADVENTURE_BACK_TO_CSS);
    gm_80172174();
    Ground_801C5A28();
}
