#include "gmclassic.h"

#include "gm_unsplit.h"

#include <sysdolphin/baselib/random.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbdvd.h>

extern UNK_T gmClassic_80470708[];
extern DebugGameOverData gmClassic_80470850;
extern UNK_T gmClassic_8047086C;
extern UNK_T gmClassic_80472AF8;
u8 gm_804908A0[112];
UNK_T gmClassic_804D68D0;

typedef struct gmClassicMatchup {
    /* 0x00 */ u16 x00;
    /* 0x02 */ union {
        s8 x02[3];
        u8 x02_u8[3];
    };
    /* 0x05 */ u8 x05;
} gmClassicMatchup;
ASSERT_SIZE(gmClassicMatchup, 6);

typedef struct gmClassicMatchupData {
    /* 0x00 */ gmClassicMatchup x00;
    /* 0x06 */ u8 pad_06[2];
} gmClassicMatchupData;
ASSERT_SIZE(gmClassicMatchupData, 8);

typedef struct gmClassicIntroData {
    /* 0x00 */ s32 x00;
    /* 0x04 */ s32 x04;
    /* 0x08 */ u8 x08;
    /* 0x09 */ u8 x09;
    /* 0x0A */ u8 x0A;
    /* 0x0B */ u8 x0B;
    /* 0x0C */ u8 x0C;
    /* 0x0D */ u8 x0D[3];
    /* 0x10 */ u8 x10[3];
    /* 0x13 */ u8 x13[3];
    /* 0x16 */ u8 x16[3];
    /* 0x19 */ u8 x19[3];
    /* 0x1C */ u8 x1C[3];
    /* 0x1F */ u8 x1F;
} gmClassicIntroData;
ASSERT_SIZE(gmClassicIntroData, 0x20);

typedef struct gmClassic_80490880Data {
    /* 0x00 */ gmClassicIntroData x00;
    /* 0x20 */ u8 x20[0x0C];
    /* 0x2C */ u8 x2C[0x28];
    /* 0x54 */ u8 x54[0x20];
    /* 0x74 */ u8 x74[0x0C];
    /* 0x80 */ u8 x80[0x10];
} gmClassic_80490880Data;
ASSERT_SIZE(gmClassic_80490880Data, 0x90);

typedef struct gmClassic_803DDEC8Data {
    /* 0x000 */ gm_803DDEC8Struct x00[12];
    /* 0x0C0 */ gmClassicMatchup x0C0[2];
    /* 0x0CC */ gmClassicMatchup x0CC[39];
    /* 0x1B6 */ u8 pad_1B6[2];
    /* 0x1B8 */ gmClassicMatchup x1B8[30];
    /* 0x26C */ gmClassicMatchup x26C[11];
    /* 0x2AE */ u8 pad_2AE[2];
    /* 0x2B0 */ gmClassicMatchup x2B0[10];
    /* 0x2EC */ u8 pad_2EC[4];
} gmClassic_803DDEC8Data;
ASSERT_SIZE(gmClassic_803DDEC8Data, 0x2F0);

typedef struct gmClassicSceneData {
    /* 0x000 */ GameModeState scenes[26];
    /* 0x270 */ gmClassic_803DDEC8Data matchups;
} gmClassicSceneData;
ASSERT_SIZE(gmClassicSceneData, 0x560);

static gmClassic_80490880Data gmClassic_80490880;

GameModeState gm_Mode_Classic_States[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        1,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        8,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        9,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        16,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        17,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        24,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        25,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        32,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        33,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        40,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        41,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        48,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        49,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        56,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        57,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        64,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        65,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        72,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        73,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        80,
        lbDvdPreload_3,
        0,
        gmClassic_801B3500,
        NULL,
        {
            GS_INTRO_EASY,
            &gmClassic_80490880,
            &gmClassic_804D68D0,
        },
    },
    {
        81,
        lbDvdPreload_3,
        0,
        gmClassic_801B3A34,
        gmClassic_801B3B40,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        104,
        lbDvdPreload_3,
        0,
        NULL,
        gmClassic_801B3F18,
        {
            GS_COMING_SOON,
            NULL,
            NULL,
        },
    },
    {
        105,
        lbDvdPreload_3,
        0,
        gmClassic_801B3D44,
        gmClassic_801B3D84,
        {
            GS_GAMEOVER,
            &gmClassic_80470850,
            &gmClassic_80470850,
        },
    },
    {
        112,
        lbDvdPreload_3,
        0,
        gmClassic_801B3DD8,
        gmClassic_801B3E44,
        {
            GS_CSS,
            &gmClassic_80470708,
            &gmClassic_80470708,
        },
    },
    { -1 },
};

static gmClassic_803DDEC8Data gmClassic_803DDEC8 = {
    {
        { 0x00, 0x00, 0, 0, 300, 0, 2 },
        { 0x01, 0x10, 0, 0, 300, 0, 4 },
        { 0x02, 0x80, 1, 0, 120, 0, 4 },
        { 0x03, 0x00, 0, 0, 300, 0, 2 },
        { 0x04, 0x02, 0, 0, 300, 0, 4 },
        { 0x05, 0x80, 3, 0, 120, 0, 4 },
        { 0x06, 0x00, 0, 0, 300, 0, 2 },
        { 0x07, 0x08, 0, 0, 300, 10, 4 },
        { 0x08, 0x80, 2, 0, 180, 0, 4 },
        { 0x09, 0x04, 0, 0, 300, 0, 2 },
        { 0x0a, 0x20, 0, 0, 300, 0, 2 },
        { 0x0d, 0x00, 0, 0, 0, 0, 0 },
    },
    {
        { 176, { 30, 26, 33 }, 0 },
        { 328, { 0, 0, 0 }, 0 },
    },
    {
        { 86, { 8, 33, 33 }, 0 },   { 87, { 8, 33, 33 }, 0 },
        { 88, { 1, 33, 33 }, 0 },   { 89, { 1, 33, 33 }, 0 },
        { 90, { 6, 33, 33 }, 0 },   { 91, { 6, 33, 33 }, 0 },
        { 92, { 16, 33, 33 }, 0 },  { 93, { 16, 33, 33 }, 0 },
        { 94, { 17, 33, 33 }, 0 },  { 95, { 17, 33, 33 }, 0 },
        { 96, { 4, 33, 33 }, 0 },   { 97, { 4, 33, 33 }, 0 },
        { 98, { 2, 33, 33 }, 0 },   { 99, { 2, 33, 33 }, 0 },
        { 100, { 13, 33, 33 }, 0 }, { 101, { 7, 33, 33 }, 0 },
        { 102, { 7, 33, 33 }, 0 },  { 103, { 0, 33, 33 }, 0 },
        { 104, { 0, 33, 33 }, 0 },  { 105, { 11, 33, 33 }, 0 },
        { 106, { 11, 33, 33 }, 0 }, { 107, { 15, 33, 33 }, 0 },
        { 108, { 5, 33, 33 }, 0 },  { 109, { 5, 33, 33 }, 0 },
        { 110, { 12, 33, 33 }, 0 }, { 111, { 12, 33, 33 }, 0 },
        { 112, { 18, 33, 33 }, 0 }, { 113, { 9, 33, 33 }, 0 },
        { 114, { 10, 33, 33 }, 0 }, { 115, { 10, 33, 33 }, 0 },
        { 116, { 14, 33, 33 }, 0 }, { 117, { 14, 33, 33 }, 0 },
        { 118, { 22, 33, 33 }, 0 }, { 119, { 21, 33, 33 }, 0 },
        { 120, { 21, 33, 33 }, 0 }, { 121, { 20, 33, 33 }, 0 },
        { 122, { 20, 33, 33 }, 0 }, { 124, { 24, 33, 33 }, 0 },
        { 328, { 0, 0, 0 }, 0 },
    },
    { 0 },
    {
        { 125, { 8, 5, 33 }, 0 },   { 126, { 8, 12, 33 }, 0 },
        { 127, { 1, 2, 33 }, 0 },   { 128, { 6, 18, 33 }, 0 },
        { 129, { 6, 21, 33 }, 0 },  { 130, { 6, 7, 33 }, 0 },
        { 131, { 9, 6, 33 }, 0 },   { 132, { 16, 0, 33 }, 0 },
        { 133, { 16, 2, 33 }, 0 },  { 134, { 17, 7, 33 }, 0 },
        { 135, { 17, 11, 33 }, 0 }, { 136, { 4, 13, 33 }, 0 },
        { 137, { 4, 24, 33 }, 0 },  { 138, { 4, 15, 33 }, 0 },
        { 139, { 4, 14, 33 }, 0 },  { 140, { 2, 20, 33 }, 0 },
        { 141, { 2, 0, 33 }, 0 },   { 142, { 13, 24, 33 }, 0 },
        { 143, { 13, 15, 33 }, 0 }, { 144, { 7, 22, 33 }, 0 },
        { 145, { 11, 12, 33 }, 0 }, { 146, { 11, 10, 33 }, 0 },
        { 147, { 0, 20, 33 }, 0 },  { 148, { 5, 10, 33 }, 0 },
        { 149, { 5, 12, 33 }, 0 },  { 150, { 5, 18, 33 }, 0 },
        { 151, { 12, 18, 33 }, 0 }, { 152, { 18, 21, 33 }, 0 },
        { 153, { 18, 9, 33 }, 0 },  { 328, { 0, 0, 0 }, 0 },
    },
    {
        { 155, { 8, 33, 33 }, 0 },
        { 156, { 1, 33, 33 }, 0 },
        { 157, { 6, 33, 33 }, 0 },
        { 158, { 17, 33, 33 }, 0 },
        { 159, { 7, 33, 33 }, 0 },
        { 160, { 0, 33, 33 }, 0 },
        { 161, { 15, 33, 33 }, 0 },
        { 162, { 5, 33, 33 }, 0 },
        { 163, { 22, 33, 33 }, 0 },
        { 164, { 21, 33, 33 }, 0 },
        { 328, { 0, 0, 0 }, 0 },
    },
    { 0 },
    {
        { 165, { 8, 8, 8 }, 0 },
        { 166, { 1, 1, 1 }, 0 },
        { 167, { 4, 4, 4 }, 0 },
        { 168, { 7, 7, 7 }, 0 },
        { 169, { 11, 11, 11 }, 0 },
        { 170, { 15, 15, 15 }, 0 },
        { 174, { 0, 0, 0 }, 0 },
        { 172, { 24, 24, 24 }, 0 },
        { 173, { 3, 3, 3 }, 0 },
        { 328, { 0, 0, 0 }, 0 },
    },
    { 0 },
};

static inline void gmClassic_InitMatchupOrder(const gmClassicMatchup* matchups,
                                              u8* order)
{
    s32 count;
    s32 i;

    for (count = 0; matchups[count].x00 != 0x148; count++) {
    }

    for (i = 0; i < count; i++) {
        order[i] = i;
    }

    for (i = 0; i < count; i++) {
        s32 swap_idx = HSD_Randi(count);
        u8 tmp = order[i];
        order[i] = order[swap_idx];
        order[swap_idx] = tmp;
    }
}

static gmClassicMatchup* gmClassic_801B2BA4(gmClassicMatchup* arg0, u8* arg1,
                                            gm_803DDEC8Struct* arg2)
{
    gmClassicMatchup* result;
    gmClassicMatchup* entry;
    gm_803DDEC8Struct* temp;
    u8* order;
    s32 outer;
    s8 target_char;
    int cur_char;
    s32 j;
    s32 k;
    s32 count;
    s32 stage1;

    result = NULL;
    target_char = gmMainLib_8015CDC8()->c_kind;
    order = arg1;
    outer = 0;

    goto check;
loop:
    entry = &arg0[*order];
    for (j = 0; j < 3; j++) {
        cur_char = entry->x02[j];

        if (cur_char == CHKIND_NONE) {
            continue;
        }
        if (gm_80164430(entry->x00) == 0) {
            goto next;
        }
        if (gm_IsCKindUnlocked(cur_char) == 0) {
            goto next;
        }
        if (cur_char == target_char) {
            goto next;
        }

        for (temp = arg2; temp->x0 != 0xD; temp++) {
            for (k = 0; k < 3; k++) {
                if (temp->xC != NULL && cur_char == temp->xC->x02[k]) {
                    goto next;
                }
            }
        }

        for (temp = arg2; temp->x0 != 0xD; temp++) {
            if (temp->xC != NULL) {
                stage1 = Stage_8022519C(entry->x00);
                if (Stage_8022519C(temp->xC->x00) == stage1) {
                    result = entry;
                    goto next;
                }
            }
        }
    }
    if (entry != NULL) {
        return entry;
    }
next:
    outer++;
    order++;
check:
    count = 0;
    while (arg0[count].x00 != 0x148) {
        count++;
    }
    if (outer < count) {
        goto loop;
    }

    if (result != NULL) {
        return result;
    }
    return NULL;
}

static gmClassicMatchupData gm_804D4318 = { { 0x148, { 0x21, 0x21, 0x21 }, 0 },
                                            { 0, 0 } };
static gmClassicMatchupData gm_804D4320 = { { 0x052, { 0x21, 0x21, 0x21 }, 0 },
                                            { 0, 0 } };
static gmClassicMatchupData gm_804D4328 = { { 0x053, { 0x21, 0x21, 0x21 }, 0 },
                                            { 0, 0 } };

static gm_803DDEC8Struct* gmClassic_801B2D54(gm_803DDEC8Struct* arg0)
{
    gmClassic_80490880Data* o = &gmClassic_80490880;
    gm_803DDEC8Struct* ptr;
    gmClassicSceneData* scene_data =
        (gmClassicSceneData*) gm_Mode_Classic_States;

    for (ptr = arg0; ptr->x0 != 0xD; ptr++) {
        if (ptr->x1 & 8) {
            gmClassicMatchup* result =
                gmClassic_801B2BA4(scene_data->matchups.x2B0, o->x80, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
    }

    for (ptr = arg0; ptr->x0 != 0xD; ptr++) {
        u8 flags = ptr->x1;
        if ((flags & 2) && !(flags & 0x20)) {
            gmClassicMatchup* result =
                gmClassic_801B2BA4(scene_data->matchups.x26C, o->x74, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
    }

    for (ptr = arg0; ptr->x0 != 0xD; ptr++) {
        u8 flags = ptr->x1;
        if ((flags & 0x10) && !(flags & 0x20)) {
            gmClassicMatchup* result =
                gmClassic_801B2BA4(scene_data->matchups.x1B8, o->x54, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
    }

    for (ptr = arg0; ptr->x0 != 0xD; ptr++) {
        u8 flags = ptr->x1;
        if (flags == 0 || flags == 4) {
            gmClassicMatchup* result =
                gmClassic_801B2BA4(scene_data->matchups.x0CC, o->x2C, arg0);
            if (result != NULL) {
                ptr->xC = result;
            } else {
                for (;;) {
                }
            }
        }
    }

    for (ptr = arg0; ptr->x0 != 0xD; ptr++) {
        if (ptr->x1 == 0x80) {
            u8 x2val = ptr->x2;
            switch ((s32) x2val) {
            case 1:
                ptr->xC = &gm_804D4318.x00;
                break;
            case 2:
                ptr->xC = &gm_804D4320.x00;
                break;
            case 3:
                ptr->xC = &gm_804D4328.x00;
                break;
            }
        }
    }

    for (ptr = arg0; ptr->x0 != 0xD; ptr++) {
        if (ptr->x1 & 0x20) {
            ptr->xC = scene_data->matchups.x0C0;
            return ptr;
        }
    }
    return ptr;
}

void gm_Mode_Classic_OnLoad(void)
{
    UnkAllstarData* data;
    gmClassicSceneData* scene_data =
        (gmClassicSceneData*) gm_Mode_Classic_States;
    gmClassic_80490880Data* o = &gmClassic_80490880;
    gm_803DDEC8Struct* entry;
    s32 i;
    PAD_STACK(32);

    for (entry = scene_data->matchups.x00; entry->x0 != 0x0D; entry++) {
        entry->xC = NULL;
    }

    gmClassic_InitMatchupOrder(scene_data->matchups.x2B0,
                               gmClassic_80490880.x80);
    gmClassic_InitMatchupOrder(scene_data->matchups.x26C,
                               gmClassic_80490880.x74);
    gmClassic_InitMatchupOrder(scene_data->matchups.x1B8,
                               gmClassic_80490880.x54);
    gmClassic_InitMatchupOrder(scene_data->matchups.x0CC,
                               gmClassic_80490880.x2C);

    data = gm_GetAllStarData();
    gmMainLib_8015CDC8();
    gm_8017C984(data);

    for (i = 0; i < 2; i++) {
        s32 j;
        for (j = 0; j < 6; j++) {
            o->x20[i * 6 + j] = 0;
        }
    }

    gm_8017DB58(data->x0.xC.x24);
    data->x0.slot = gm_801677F0();
    data->x48 = gm_8017EB3C;
    data->x4C = gm_8017EB64;
    data->x50 = gm_8017EBCC;
    data->x54 = gm_8017EB98;
    data->x64 = gm_8017ED3C;
    data->x68 = gm_8017ED8C;
    data->x58 = gm_8017ECA0;
    data->x5C = gm_8017ED08;
    data->x60 = gm_8017ECD4;
    data->x6C = gm_8017EC00;
    data->x70 = gm_8017EC50;

    gm_SetSceneIndex(0x70U);
    gm_80172174();
    Ground_801C5A28();
}

void gm_Mode_Classic_OnInit(void)
{
    struct gmm_x0_528_t* temp_r3 = gmMainLib_8015CDC8();
    temp_r3->c_kind = CHKIND_NONE;
    temp_r3->color = 0;
    temp_r3->stocks = 3;
    temp_r3->cpu_level = 0;
    temp_r3->x4 = 0x78;
    temp_r3->x5 = 0;
}

static inline StKind gmClassic_GetStKind(gm_803DDEC8Struct* entry,
                                         UnkAllstarData* ad)
{
    if (entry->x1 == 0x80 && entry->x2 == 1) {
        return (u16) gm_801647F8(ad->x0.ckind);
    }
    return entry->xC->x00;
}

void gmClassic_801B3500(GameModeState* arg0)
{
    gmClassicIntroData* sd;
    gm_803DDEC8Struct* entry;
    int i;
    UnkAllstarData* ad;
    int ally_count;
    int enemy_count;
    struct GameCache* gc;
    int count;
    u64 audio;
    s8 ckind;
    gm_803DDEC8Struct* new_var;

    sd = gm_GetGameSceneLoadData(arg0);
    entry = &gmClassic_803DDEC8.x00[(u8) gm_8017BE84(arg0->id)];
    new_var = entry;
    ad = gm_GetAllStarData();
    enemy_count = 0;
    ad->x0.x7 = arg0->id;
    sd->x0A = entry->x0 + 1;
    sd->x08 = ad->x0.slot;

    if (entry->x1 & 0x80) {
        sd->x00 = 3;
    } else if (entry->x1 & 8) {
        sd->x00 = 4;
    } else if (entry->x1 & 0x10) {
        sd->x00 = 1;
    } else if (entry->x1 & 2) {
        sd->x00 = 2;
    } else {
        sd->x00 = 0;
    }

    if (sd->x00 == 3) {
        switch (entry->x2) {
        case 1:
            sd->x04 = 1;
            break;
        case 2:
            sd->x04 = 2;
            break;
        case 3:
            sd->x04 = 3;
            break;
        }
    } else {
        sd->x04 = 0;
    }

    for (i = 0; i < 3; i++) {
        sd->x10[i] = entry->xC->x02[i];
        sd->x16[i] = gm_8017CD94((UnkAdventureData*) ad, entry->xC->x02[i],
                                 entry->x0, i);
        gmRegSetupEnemyColorTable(ad->x0.ckind, ad->x0.color, entry->xC->x02,
                                  sd->x16);
        if (entry->x1 & 4) {
            sd->x1C[i] = 1;
        } else {
            sd->x1C[i] = 0;
        }
        if (sd->x10[i] != 0x21) {
            enemy_count++;
        }
    }
    sd->x0C = enemy_count;

    ally_count = 1;
    ckind = ad->x0.ckind;
    if (ckind == CKIND_ZELDA && ad->x0.xC.x12 != 0) {
        sd->x0D[0] = CKIND_SEAK;
    } else {
        sd->x0D[0] = ckind;
    }
    sd->x13[0] = ad->x0.color;

    gm_8017DB88(ad->x0.xC.x24, entry->x1, ad->x0.cpu_level,
                (u8) gm_8017BE84(arg0->id), entry->xC->x02_u8, sd->x0D[0],
                (u8 (*)(s32, s32, u8))(Event) ad->x58,
                (u8 (*)(s32, s32, u8))(Event) ad->x5C,
                (u8 (*)(s32, s32, u8))(Event) ad->x60,
                (f32 (*)(s32, s32))(Event) ad->x6C,
                (f32 (*)(s32, s32))(Event) ad->x70);

    for (i = 1; i < 3; i++) {
        sd->x0D[i] = gm_8017DB6C((gm_8017DB6C_arg0_t*) ad->x0.xC.x24, i - 1);
        sd->x13[i] = gm_8017DB78((gm_8017DB6C_arg0_t*) ad->x0.xC.x24, i - 1);
        if (sd->x0D[i] != 0x21) {
            ally_count++;
        }
    }
    sd->x0B = ally_count;
    sd->x09 = ad->x0.x4;

    gc = &lbDvd_GetPreloadCacheScene()->game_cache;
    lbDvd_80018C6C();
    count = 0;
    gc->entries[count].char_id = sd->x0D[0];
    gc->entries[count].color = ad->x0.color;
    count++;
    lbDvd_80018254();
    lbDvd_80018C2C(0xC7);
    lbDvd_80017700(4);

    for (i = 0; i < 3; i++) {
        s8 echar = entry->xC->x02[i];
        if (echar != 0x21) {
            gc->entries[count].char_id = echar;
            if (entry->x1 & 8) {
                gc->entries[count].color = 0xFF;
            } else {
                gc->entries[count].color = sd->x16[i];
            }
            count++;
        }
    }

    for (i = 0; i < 3; i++) {
        s8 achar = ad->x0.xC.x24[i].ckind;
        if (achar != 0x21) {
            gc->entries[count].char_id = achar;
            gc->entries[count].color = ad->x0.xC.x24[i].x1;
            count++;
        }
    }

    lbDvd_80018254();

    if (entry->x1 == 0x80 && entry->x2 == 1) {
        gc->stkind = (u16) gm_801647F8(ad->x0.ckind);
    } else if (entry->x1 == 4) {
        gc->stkind = 0xAF;
    } else {
        gc->stkind = entry->xC->x00;
    }

    lbDvd_80018254();

    audio = lbAudioAx_80026E84(ad->x0.ckind);

    for (i = 0; i < 3; i++) {
        s8 achar = ad->x0.xC.x24[i].ckind;
        if (achar != 0x21) {
            audio |= lbAudioAx_80026E84(achar);
        }
    }

    for (i = 0; i < 3; i++) {
        if (entry->xC->x02[i] != 0x21) {
            audio |= lbAudioAx_80026E84(new_var->xC->x02[i]);
            if (entry->xC->x02[i] == 4) {
                audio |= ((u64) 2 << 32) | 0x4000;
            }
        }
    }

    audio |= lbAudioAx_80026EBC(gmClassic_GetStKind(entry, ad));

    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC, audio);
    lbAudioAx_80027168();
}

void gmClassic_801B3A34(GameModeState* arg0)
{
    StartMeleeData* temp_r30;
    gm_803DDEC8Struct* temp_r31;
    u8 flags;
    u8 temp_r28;
    int idx_val;
    int var_r27;
    StartMeleeData* new_var;
    s32 sp8;
    s32 spC;
    UnkAllstarData* temp_r29;

    PAD_STACK(8);

    temp_r30 = gm_GetGameSceneLoadData(arg0);
    temp_r31 = &gmClassic_803DDEC8.x00[(u8) gm_8017BE84(arg0->id)];
    temp_r29 = gm_GetAllStarData();
    new_var = temp_r30;
    var_r27 = temp_r31->xC->x00;
    if (temp_r31->x1 == 0x80 && temp_r31->x2 == 1) {
        var_r27 = gm_801647F8(temp_r29->x0.ckind) & 0xFFFF;
    }
    flags = temp_r31->x1;
    if (flags == 4) {
        var_r27 = 0xAF;
    }
    temp_r29->x0.x8 = flags;
    temp_r29->x0.x9 = temp_r31->x2;
    temp_r29->x0.xB = temp_r31->x8;
    idx_val = (u16) gm_8017BE84(arg0->id) - 1;
    temp_r28 = gm_804908A0[idx_val];
    sp8 = (u16) gm_8017BE84(arg0->id);
    spC = temp_r28;
    gm_8017CE34(new_var, (UnkAdventureData*) temp_r29, temp_r31->xC->x02,
                temp_r31->x6, 1, 0, temp_r31->x4, var_r27, sp8, spC);
    gm_8016F088(new_var);
}

void gmClassic_801B3B40(GameModeState* arg0)
{
    MatchExitInfo* mei;
    UnkAllstarData* asd;
    s32 exit_result;
    gm_803DDEC8Struct* entry;
    u8 unused[16];
    s32 sp18;
    s32 sp14;
    s32 idx;
    u8 char_id;
    u32* time_ptr;
    s32* best_ptr;
    u8 id;
    s32 mask;
    PAD_STACK(4);

    mei = (MatchExitInfo*) gm_GetGameSceneLeaveData(arg0);
    asd = gm_GetAllStarData();
    entry = &gmClassic_803DDEC8.x00[(u8) gm_8017BE84(arg0->id)];
    exit_result = mei->x8;
    id = arg0->id;
    idx = ((u16) gm_8017BE84(id)) - 1;
    if (exit_result != 0) {
        gm_804908A0[idx] = 2;
    } else {
        gm_804908A0[idx] = 1;
    }

    if (gm_8017D7AC(mei, &asd->x0, 0x69) != 0 && entry[1].x0 == 0xD) {
        gm_8017CBAC((UnkAdventureData*) asd, gmMainLib_8015CDC8(), 0x15);
    }

    if (entry->x1 == 0x80 && entry->x2 == 1) {
        char_id = gm_CKindToSelKind((u8) asd->x0.ckind);
        time_ptr = gmMainLib_8015D438(char_id);
        best_ptr = gmMainLib_8015D450(char_id);
        Ground_801C1DE4(&sp18, &sp14);

        if (sp18 == 0) {
            mask = 1 << char_id;
            if (asd->x0.ckind && asd->x0.ckind) {
            }
            if (!(mask & gmMainLib_8015EDBC()->x8)) {
                *best_ptr = (s32) mei->match_end.frame_count;
                gmMainLib_8015EDBC()->x8 |= mask;
            } else {
                if ((u32) *best_ptr > mei->match_end.frame_count) {
                    *best_ptr = (s32) mei->match_end.frame_count;
                }
            }
            gmMainLib_8015ED98()->x1C |= mask;
            gmMainLib_8015EDB0()->x4 |= mask;
        }

        if (gmMainLib_8015D48C(char_id) == 0) {
            if (sp18 == 0) {
                gmMainLib_8015D4E8(char_id, 1);
                *time_ptr = mei->match_end.frame_count;
                return;
            }
            {
                u32 diff = sp14 - sp18;
                if ((*time_ptr) < diff) {
                    *time_ptr = sp14 - sp18;
                }
            }
        } else if (sp18 == 0) {
            if ((*time_ptr) > mei->match_end.frame_count) {
                *time_ptr = mei->match_end.frame_count;
            }
        }
    }
}

void gmClassic_801B3D44(GameModeState* scene)
{
    struct DebugGameOverData* temp_r31 = gm_GetGameSceneLoadData(scene);
    gm_8017C9A8(temp_r31, &gm_GetAllStarData()->x0, 1);
}

void gmClassic_801B3D84(GameModeState* scene)
{
    DebugGameOverData* temp_r30 = gm_GetGameSceneLeaveData(scene);
    gm_8017CA38(temp_r30, &gm_GetAllStarData()->x0, gmMainLib_8015CDC8(), 1);
}

void gmClassic_801B3DD8(GameModeState* scene)
{
    CSSData* css = gm_GetGameSceneLoadData(scene);
    struct gmm_x0_528_t* temp_r31 = gmMainLib_8015CDC8();
    gm_801B06B0(css, 0xB, temp_r31->c_kind, temp_r31->stocks, temp_r31->color,
                temp_r31->x4, temp_r31->cpu_level,
                gm_GetAllStarData()->x0.slot);
    lbDvd_800174BC();
}

void gmClassic_801B3E44(GameModeState* scene)
{
    CSSData* temp_r30 = gm_GetGameSceneLeaveData(scene);
    gmm_x0_528_t* temp_r29 = gmMainLib_8015CDC8();
    UnkAllstarData* temp_r31 = gm_GetAllStarData();
    gm_803DDEC8Struct* r4 = gmClassic_803DDEC8.x00;
    if (temp_r30->pending_scene_change == 2) {
        // This only happens when, instead of pressing start to begin the game,
        // we press back to exit.
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return;
    }
    gm_801B0730(temp_r30, &temp_r29->c_kind, &temp_r29->stocks,
                &temp_r29->color, &temp_r29->x4, &temp_r29->cpu_level);
    temp_r31->x0.ckind = temp_r29->c_kind;
    temp_r31->x0.color = temp_r29->color;
    temp_r31->x0.cpu_level = temp_r29->cpu_level;
    temp_r31->x0.stocks = temp_r29->stocks;
    temp_r31->x0.x4 = temp_r29->x4;
    gmClassic_801B2D54(r4);
    gm_SetPendingSceneIndex(temp_r29->x5 << 3);
    gm_80168F88();
}

void gmClassic_801B3F18(GameModeState* scene)
{
    gm_SetPendingGameMode(GM_MENU);
    gm_SetNewGameModePending();
}
