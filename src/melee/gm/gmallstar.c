#include "gmallstar.h"

#include "gm/gmallstar.static.h"

#include "gm_unsplit.h"
#include "gmregcommon.h"

#include "baselib/random.h"
#include "gr/ground.h"

#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbdvd.h>

extern CSSData gmClassic_80470708;
extern DebugGameOverData gmClassic_80470850;
extern MatchExitInfo gmClassic_8047086C;
extern StartMeleeData gmClassic_80472AF8;

GameScene gm_803DE930_Scenes[] = {
    {
        0,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        1,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        8,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        9,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x10,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x11,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x18,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x19,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x20,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x21,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x28,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x29,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x30,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x31,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x38,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x39,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x40,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x41,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x48,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x49,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x50,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x51,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x58,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x59,
        3,
        0,
        gm_801B5ACC,
        gm_801B5E7C,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x60,
        3,
        0,
        gm_801B5624,
        gm_801B59AC,
        {
            GS_VS,
            &gmClassic_80472AF8,
            &gmClassic_8047086C,
        },
    },
    {
        0x68,
        3,
        0,
        NULL,
        gm_801B607C,
        {
            GS_COMING_SOON,
            NULL,
            NULL,
        },
    },
    {
        0x69,
        3,
        0,
        gm_801B5EB4,
        gm_801B5EE4,
        {
            GS_GAMEOVER,
            &gmClassic_80470850,
            &gmClassic_80470850,
        },
    },
    {
        0x70,
        3,
        0,
        gm_801B5F50,
        gm_801B5FB4,
        {
            GS_CSS,
            &gmClassic_80470708,
            &gmClassic_80470708,
        },
    },
    {
        -1,
    },
};

static gm_803DEBE8_t gm_803DEBE8[25] = {
    { 0xB1, 0xB1, 0, 8 },    { 0xB2, 0xB2, 0, 1 },    { 0xB3, 0xB3, 0, 6 },
    { 0xB4, 0xB4, 0, 0x10 }, { 0xB5, 0xB5, 0, 0x11 }, { 0xB6, 0xB6, 0, 4 },
    { 0xB7, 0xB7, 0, 2 },    { 0xB8, 0xB8, 0, 0xD },  { 0xB9, 0xB9, 0, 7 },
    { 0xBA, 0xBA, 0, 0 },    { 0xBB, 0xBB, 0, 0xB },  { 0xBC, 0xBC, 0, 0xF },
    { 0xBD, 0xBD, 0, 0xE },  { 0xBE, 0xBE, 0, 0xC },  { 0xBF, 0xBF, 0, 0x12 },
    { 0xC0, 0xC0, 0, 9 },    { 0xC1, 0xC1, 0, 0xA },  { 0xC2, 0xC2, 0, 5 },
    { 0xC3, 0xC3, 0, 0x16 }, { 0xC4, 0xC4, 0, 0x15 }, { 0xC5, 0xC5, 0, 0x14 },
    { 0xC6, 0xC6, 0, 0x18 }, { 0xC7, 0xC7, 0, 0x17 }, { 0xC9, 0xC9, 0, 0x19 },
    { 0xC8, 0xC8, 0, 3 }
};

static AllstarRoundInfo gm_803DEC4C[26] = {
    { 0, 1 },  { 1, 1 },  { 2, 1 },  { 3, 1 },  { 4, 2 },  { 6, 2 },  { 8, 2 },
    { 10, 2 }, { 12, 3 }, { 15, 3 }, { 18, 3 }, { 21, 3 }, { 24, 1 },
};

gm_80490940_t gm_80490940[5];

void gm_801B5324(UnkAllstarData* arg0, u8 arg1)
{
    s8 chars[3];
    u8 colors[3];
    u8* base;
    gm_803DEBE8_t* opp_data;
    s32 is_last_round;
    s32 count_processed;
    s32 count;
    struct PreloadCacheScene* gc;
    s32 slot_idx;
    u64 audio;
    s32 i;
    PAD_STACK(16);

    base = (u8*) gm_803DE930_Scenes;
    is_last_round = 0;
    count_processed = 0;

    {
        u32 start = ((AllstarRoundInfo*) (base + 0x31C))[arg1].start;
        opp_data = (gm_803DEBE8_t*) (base + 0x2B8) + start;
        count = ((AllstarRoundInfo*) (base + 0x31C))[arg1].count;
    }

    chars[0] = 0x21;
    chars[1] = 0x21;
    chars[2] = 0x21;

    if (count > 0) {
        if (count > 8) {
            u32 blocks = (u32) (count - 8 + 7) >> 3;
            gm_803DEBE8_t* src = opp_data;
            s8* dst = chars;
            if (count - 8 > 0) {
                do {
                    count_processed += 8;
                    dst[0] = (s8) src[0].x3;
                    dst[1] = src[1].x3;
                    dst[2] = src[2].x3;
                    dst[3] = src[3].x3;
                    dst[4] = src[4].x3;
                    dst[5] = src[5].x3;
                    dst[6] = src[6].x3;
                    dst[7] = src[7].x3;
                    src += 8;
                    dst += 8;
                } while (--blocks);
            }
        }

        {
            gm_803DEBE8_t* src2 = &opp_data[count_processed];
            s8* dst2 = &chars[count_processed];
            s32 remaining = ((AllstarRoundInfo*) (base + 0x31C))[arg1].count -
                            count_processed;
            if (count_processed <
                ((AllstarRoundInfo*) (base + 0x31C))[arg1].count)
            {
                do {
                    u8 val = src2->x3;
                    src2++;
                    *dst2 = (s8) val;
                    dst2++;
                } while (--remaining);
            }
        }
    }

    {
        u8* cp = colors;
        for (i = 0; i < 3; i++) {
            *cp = arg0->x54(arg1, arg0->x0.cpu_level, (u8) i);
            cp++;
        }
    }

    gmRegSetupEnemyColorTable(arg0->x0.ckind, arg0->x0.color, chars, colors);

    if ((s32) arg1 == 0xC) {
        chars[0] = 3;
        colors[0] = 0;
        is_last_round = 1;
        chars[1] = 3;
        colors[1] = 0;
        chars[2] = 3;
        colors[2] = 0;
    }

    gc = lbDvd_8001822C();
    slot_idx = 1;
    lbDvd_80018C6C();
    gc->game_cache.entries[0].char_id = (s32) (s8) arg0->x0.ckind;
    gc->game_cache.entries[0].color = arg0->x0.color;
    lbDvd_80018254();
    lbDvd_80018C2C(0xC7);
    lbDvd_80017700(4);

    {
        s32 idx = slot_idx;
        for (i = 0; i < 3; i++) {
            if ((s8) chars[i] != 0x21) {
                gc->game_cache.entries[idx].char_id = chars[i];
                if (is_last_round != 0) {
                    gc->game_cache.entries[idx].color = 0xFF;
                } else {
                    gc->game_cache.entries[idx].color = colors[i];
                }
                idx++;
            }
        }
    }

    gc->game_cache.stage_id = (InternalStageId) opp_data->x2;
    lbDvd_80018254();

    audio = lbAudioAx_80026E84((CharacterKind) (s8) arg0->x0.ckind);
    {
        s8* cp = chars;
        for (i = 0; i < 3; i++) {
            audio |= lbAudioAx_80026E84(cp[i]);
        }
    }

    audio |= lbAudioAx_80026EBC((InternalStageId) opp_data->x2);
    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC, audio);
    lbAudioAx_80027168();
}

void gm_801B5624(GameScene* arg0)
{
    s8 chars[3];
    StartMeleeData* data;
    u8* base;
    gm_803DEBE8_t* opp_data;
    UnkAllstarData* allstar;
    s32 i;
    s32 count;
    u16 round;
    u8 color;
    PAD_STACK(8);

    base = (u8*) gm_803DE930_Scenes;
    data = gm_801A427C(arg0);
    allstar = &gm_80473A18;
    round = gm_8017BE84(arg0->idx);

    {
        u32 start = ((AllstarRoundInfo*) (base + 0x31C))[round].start;
        opp_data = (gm_803DEBE8_t*) (base + 0x2B8) + start;
    }

    chars[0] = 0x21;
    chars[1] = 0x21;
    chars[2] = 0x21;

    count = ((AllstarRoundInfo*) (base + 0x31C))[round].count;
    for (i = 0; i < count; i++) {
        chars[i] = opp_data[i].x3;
    }

    allstar->x0.xB = 4;
    allstar->x0.x8 = 0;

    round = gm_8017BE84(arg0->idx);
    {
        gm_803DEBE8_t* opp = (gm_803DEBE8_t*) (base + 0x2B8) +
                             ((AllstarRoundInfo*) (base + 0x31C))[round].start;
        color = ((u8*) gm_80490940)[((u32) opp - (u32) (base + 0x2B8)) >> 2];
    }

    round = gm_8017BE84(arg0->idx);

    gm_8017CE34(data, (UnkAdventureData*) allstar, chars, 0, 0, 0, 0,
                (s32) opp_data->x2, (s32) round, (s32) color);

    data->rules.x0_6 = 1;
    data->rules.x0_7 = 1;
    data->rules.x1_0 = 1;
    data->rules.x10 = (s32) allstar->x9C / 60;
    data->rules.x14 = ((s32) allstar->x9C % 60) + 1;
    data->rules.x20 &= 0xFFFFFFFFFFFBFCFFULL;

    if ((u8) arg0->idx == 0) {
        data->players[0].xC_b1 = 1;
    } else {
        data->players[0].xC_b1 = 0;
    }

    if ((u8) arg0->idx == 0x60) {
        f32 f30 = gm_8018A1D8(0xC, allstar->x0.cpu_level);
        f32 f31 = gm_8018A188(0xC, allstar->x0.cpu_level);
        u8 opp_count = gm_8018A228(0xC, allstar->x0.cpu_level, 0);

        gm_8016A22C(3, 0x21, 0x21, 0, 0, 0, 1, 0, 0,
                    (u8) data->players[0].c_kind, data->players[0].color,
                    (s32) opp_count, 0x19, 5, 1, 0, 1, f31, f30);

        data->rules.x4_5 = 1;
        data->rules.x0_3 = 6;
        gm_8016A21C(&data->rules);
    }

    data->players[0].x10 = allstar->x74;
    gm_8016F088(data);
    allstar->x0.x7 = arg0->idx;
}

void gm_801B59AC(GameScene* arg0)
{
    u8* base = (u8*) gm_803DE930_Scenes;
    MatchExitInfo* exit = gm_801A4284(arg0);
    u8 idx = arg0->idx;
    s32 result = exit->x8;
    UnkAllstarData* data = &gm_80473A18;
    u16 round = gm_8017BE84(idx);
    gm_803DEBE8_t* opp = (gm_803DEBE8_t*) (base + 0x2B8) +
                         ((AllstarRoundInfo*) (base + 0x31C))[round].start;
    u32 i = ((u32) opp - (u32) (base + 0x2B8)) >> 2;

    if (result != 0) {
        ((u8*) gm_80490940)[i] = 2;
    } else {
        ((u8*) gm_80490940)[i] = 1;
    }
    data->x74 = exit->match_end.player_standings[0].percent;
    data->x9C += exit->match_end.frame_count;
    if (gm_8017D7AC(exit, &data->x0, 0x69) != 0 && (u8) arg0->idx == 0x60) {
        gm_8017CBAC((UnkAdventureData*) data, gmMainLib_8015CDE0(), 0x17);
    }
}

void fn_801B5AA8(int arg0)
{
    lbBgFlash_8002063C(0x78);
}

void gm_801B5ACC(GameScene* arg0)
{
    s8 chars[3];
    StartMeleeData* data;
    u8* base;
    UnkAllstarData* allstar;
    u16 round;
    u8 color;
    s32 i;
    s32 next_count;

    PAD_STACK(24);
    chars[0] = 0x21;
    chars[1] = 0x21;
    chars[2] = 0x21;
    base = (u8*) gm_803DE930_Scenes;
    data = gm_801A427C(arg0);
    allstar = &gm_80473A18;
    allstar->x0.x8 |= 0x80;

    round = gm_8017BE84(arg0->idx);
    {
        gm_803DEBE8_t* opp =
            (gm_803DEBE8_t*) (base + 0x2B8) + gm_803DEC4C[round].start;
        color = ((u8*) gm_80490940)[((u32) opp - (u32) (base + 0x2B8)) >> 2];
    }

    gm_8017CE34(data, (UnkAdventureData*) allstar, chars, 0, 0, 0, 0, 0x55, 0,
                (s32) color);

    data->rules.x0_6 = 0;
    data->rules.x0_7 = 1;
    data->rules.x1_0 = 1;
    data->rules.x10 = (s32) allstar->x9C / 60;
    data->rules.x14 = (s32) allstar->x9C % 60;
    data->rules.xD = 0x78;
    data->players[0].x10 = allstar->x74;
    data->players[0].xD_b2 = 1;
    data->rules.x7 = 9;

    round = gm_8017BE84(arg0->idx);

    {
        AllstarRoundInfo* ri = &gm_803DEC4C[round];
        for (i = 0; i < (s32) ri->count; i++) {
            s32 slot;
            do {
                slot = HSD_Randi(0x1A);
            } while ((s32) allstar->x76[slot] != 0x21);
            allstar->x76[slot] = gm_803DEBE8[ri->start + i].x3;
        }
    }

    {
        AllstarRoundInfo* ri2 = &gm_803DEC4C[round];
        s32 next_start;

        next_count = (s32) ri2[1].count;
        next_start = (s32) ri2[1].start;
        for (i = 0; i < next_count; i++) {
            allstar->_94[2 + i] = gm_803DEBE8[next_start + i].x3;
        }
    }

    allstar->_94[1] = (u8) next_count;
    allstar->_94[0] = (u8) (round + 1);
    data->players[0].xC_b1 = 0;
    data->rules.x1_2 = 1;
    data->rules.x1_3 = 1;
    data->rules.x4_4 = 0;
    gm_8016F088(data);
    gm_8016A92C(&data->rules);

    {
        s32 end_idx = (s32) gm_803DEC4C[round + 1].start;
        gm_803DEBE8_t* opp = &gm_803DEBE8[end_idx];
        while (end_idx < 0x19) {
            gm_8016A998((s8) opp->x3, 0);
            opp++;
            end_idx++;
        }
    }

    gm_801B5324(allstar, round + 1);
    data->rules.x50 = (void (*)(u8))(Event) fn_801B5AA8;
}

void gm_801B5E7C(GameScene* arg0)
{
    MatchExitInfo* exit = gm_801A4284(arg0);
    gm_80473A18.x74 = exit->match_end.player_standings[0].percent;
    gm_8017D7AC(exit, &gm_80473A18.x0, 0x69);
}

void gm_801B5EB4(GameScene* arg0)
{
    DebugGameOverData* data = gm_801A427C(arg0);
    gm_8017C9A8(data, &gm_80473A18.x0, 2);
}

void gm_801B5EE4(GameScene* arg0)
{
    DebugGameOverData* data = gm_801A4284(arg0);
    UnkAllstarData* r30 = &gm_80473A18;
    gm_8017CA38(data, &r30->x0, gmMainLib_8015CDE0(), 2);
    if (data->xC != 0) {
        r30->x74 = 0;
    }
}

void gm_801B5F50(GameScene* arg0)
{
    CSSData* temp_r31;
    struct gmm_x0_528_t* temp_r3;

    temp_r31 = gm_801A427C(arg0);
    temp_r3 = gmMainLib_8015CDE0();
    gm_801B06B0(temp_r31, 0xD, temp_r3->c_kind, temp_r3->stocks,
                temp_r3->color, temp_r3->x4, temp_r3->cpu_level,
                gm_80473A18.x0.slot);
    lbDvd_800174BC();
}

/// #gm_801B5F50

void gm_801B5FB4(GameScene* arg0)
{
    CSSData* temp_r31 = gm_801A4284(arg0);
    struct gmm_x0_528_t* temp_r30 = gmMainLib_8015CDE0();
    UnkAllstarData* r29 = &gm_80473A18;

    if (temp_r31->pending_scene_change == 2) {
        gm_801A42F8(GM_MENU);
        return;
    }
    gm_801B0730(temp_r31, &temp_r30->c_kind, &temp_r30->stocks,
                &temp_r30->color, &temp_r30->x4, &temp_r30->cpu_level);
    r29->x0.ckind = temp_r30->c_kind;
    r29->x0.color = temp_r30->color;
    r29->x0.cpu_level = temp_r30->cpu_level;
    r29->x0.stocks = temp_r30->stocks;
    r29->x0.x4 = temp_r30->x4;
    gm_SetPendingScene((temp_r30->x5 * 8) & 0xF8);
    gm_80168F88();
    gm_801B5324(r29, temp_r30->x5);
}

void gm_801B607C(GameScene* unused)
{
    gm_801A42E8(GM_MENU);
    gm_801A42D4();
}

void gm_801B60A4_OnLoad(void)
{
    UnkAllstarData* data;
    gm_803DEBE8_t* var_r29;
    gm_803DEBE8_t* var_r30;
    u32 var_r28;
    int temp;
    gm_803DEBE8_t tmp;

    data = &gm_80473A18;
    gmMainLib_8015CDE0();
    gm_8017C984(data);

    {
        gm_80490940_t* p = gm_80490940;
        char* pp = (char*) p;
        int i;
        for (i = 25; i > 0; i--) {
            pp[i] = 0;
        }
    }

    gm_8017DB58(data->x0.xC.x24);
    data->x0.slot = gm_801677F0();
    data->x48 = gm_8018A160;
    data->x4C = gm_8018A228;
    data->x50 = gm_8018A290;
    data->x54 = gm_8018A25C;
    data->x58 = NULL;
    data->x64 = gm_8018A2C4;
    var_r29 = gm_803DEBE8;
    data->x68 = gm_8018A314;
    var_r30 = var_r29;
    for (var_r28 = 0; var_r28 < 25; var_r28++) {
        var_r30->x2 = *((&var_r30->x0) + HSD_Randi(2));
        var_r30++;
    }

    var_r30 = gm_803DEBE8;
    for (var_r28 = 0; var_r28 < 0x17; var_r28++) {
        gm_803DEBE8_t* swap = &var_r30[var_r28 + HSD_Randi(0x18 - var_r28)];
        tmp = *var_r29;
        *var_r29 = *swap;
        var_r29++;
        *swap = tmp;
    }

    data->x74 = 0;
    {
        UnkAllstarData* p = &gm_80473A18;
        int i = 0x18;
        p->x9C = 0;
        temp = 0x21;
        p->x76[0] = temp;
        p->x76[1] = temp;
        p->x76[2] = temp;
        p->x76[3] = temp;
        p->x76[4] = temp;
        p->x76[5] = temp;
        p->x76[6] = temp;
        p->x76[7] = temp;
        p->x76[8] = temp;
        p->x76[9] = temp;
        p->x76[0xA] = temp;
        p->x76[0xB] = temp;
        p->x76[0xC] = temp;
        p->x76[0xD] = temp;
        p->x76[0xE] = temp;
        p->x76[0xF] = temp;
        p->x76[0x10] = temp;
        p->x76[0x11] = temp;
        p->x76[0x12] = temp;
        p->x76[0x13] = temp;
        p->x76[0x14] = temp;
        p->x76[0x15] = temp;
        p->x76[0x16] = temp;
        p->x76[0x17] = temp;

        temp = 0x1A;
        if (i < temp) {
            u8* q = ((u8*) p) + i;
            i = temp - i;
            do {
                *(q++ + 0x76) = temp;
            } while (--i != 0);
        }
    }

    {
        u8* p = gm_80473A18.x90;
        p[0] = 1;
        p[1] = 1;
        p[2] = 1;
        p[3] = 1;
    }

    gm_SetScene(0x70U);
    gm_80172174();
    Ground_801C5A28();
}

void gm_801B62D8_OnInit(void)
{
    struct gmm_x0_528_t* temp_r3 = gmMainLib_8015CDE0();
    temp_r3->c_kind = CHKIND_NONE;
    temp_r3->color = 0;
    temp_r3->stocks = 1;
    temp_r3->cpu_level = 0;
    temp_r3->x4 = 0x78;
    temp_r3->x5 = 0;
}
