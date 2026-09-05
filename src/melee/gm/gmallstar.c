#include "gm/gmallstar.static.h"

static inline void gm_801B5324_inline(s8* char_ids, gm_803DEBE8_t* opp_data,
                                      s32 round)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        char_ids[i] = 0x21;
    }
    for (i = 0; i < gm_803DEC4C[round].count; i++) {
        char_ids[i] = opp_data[i].x3;
    }
}

void gm_801B5324(UnkAllstarData* arg0, s32 arg1)
{
    s8 chars[3];
    u8 colors[3];
    s8* chars_ptr;
    s32 is_last_round;
    gm_803DEBE8_t* opp_data;
    struct GameCache* gc;
    s32 slot_idx;
    s32 i;
    u64 audio;
    PAD_STACK(4);

    is_last_round = 0;

    {
        u32 start = gm_803DEC4C[arg1].start;
        opp_data = &gm_803DEBE8[start];
    }

    gm_801B5324_inline(chars, opp_data, arg1);

    for (i = 0; i < 3; i++) {
        colors[i] = arg0->x0.x54(arg1, arg0->x0.x0.cpu_level, (u8) i);
    }

    gmRegSetupEnemyColorTable(arg0->x0.x0.ckind, arg0->x0.x0.color, chars,
                              colors);

    chars_ptr = chars;
    if (arg1 == 0xC) {
        chars_ptr[0] = 3;
        colors[0] = 0;
        is_last_round = 1;
        chars_ptr[1] = 3;
        colors[1] = 0;
        chars_ptr[2] = 3;
        colors[2] = 0;
    }

    gc = &lbDvd_GetPreloadCacheScene()->game_cache;
    lbDvd_80018C6C();
    slot_idx = 0;
    gc->entries[slot_idx].char_id = (s32) arg0->x0.x0.ckind;
    gc->entries[slot_idx].color = arg0->x0.x0.color;
    slot_idx++;
    lbDvd_80018254();
    lbDvd_80018C2C(0xC7);
    lbDvd_80017700(4);

    for (i = 0; i < 3; i++) {
        if (chars[i] != 0x21) {
            gc->entries[slot_idx].char_id = chars[i];
            if (is_last_round != 0) {
                gc->entries[slot_idx].color = 0xFF;
            } else {
                gc->entries[slot_idx].color = colors[i];
            }
            slot_idx++;
        }
    }

    gc->stkind = opp_data->x2;
    lbDvd_80018254();

    audio = lbAudioAx_80026E84((CharacterKind) arg0->x0.x0.ckind);
    {
        s32 j;
        for (j = 0; j < 3; j++) {
            audio |= lbAudioAx_80026E84(chars[j]);
        }
    }

    audio |= lbAudioAx_80026EBC(opp_data->x2);
    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC, audio);
    lbAudioAx_80027168();
}

static inline void gm_801B5624_inline(s8* char_ids, gm_803DEBE8_t* opp_data,
                                      u16 round)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        char_ids[i] = 0x21;
    }
    for (i = 0; i < gm_803DEC4C[round].count; i++) {
        char_ids[i] = opp_data[i].x3;
    }
}

void gm_801B5624(GameModeState* arg0)
{
    s8 chars[3];
    StartMeleeData* data;
    u8* base;
    UnkAllstarData* allstar;
    gm_803DEBE8_t* opp_data;
    u16 round;
    u8 color;
    PAD_STACK(8);

    base = (u8*) gm_Mode_AllStar_States;
    data = gm_GetGameModeStateEnterData(arg0);
    allstar = &gm_80473A18;
    round = gm_8017BE84(arg0->id);

    {
        u32 start = gm_803DEC4C[round].start;
        opp_data = &gm_803DEBE8[start];
    }

    gm_801B5624_inline(chars, opp_data, round);

    allstar->x0.xB = 4;
    allstar->x0.x8 = 0;

    round = gm_8017BE84(arg0->id);
    {
        gm_803DEBE8_t* opp = (gm_803DEBE8_t*) (base + 0x2B8) +
                             ((AllstarRoundInfo*) (base + 0x31C))[round].start;
        color = ((u8*) gm_80490940)[((u32) opp - (u32) (base + 0x2B8)) >> 2];
    }

    round = gm_8017BE84(arg0->id);

    gm_8017CE34(data, &allstar->x0, chars, 0, 0, 0, 0, (s32) opp_data->x2,
                (s32) round, (s32) color);

    data->rules.x0_6 = 1;
    data->rules.timer_counts_up = 1;
    data->rules.x1_0 = 1;
    data->rules.time_limit = (s32) allstar->x9C / 60;
    data->rules.x14 = ((s32) allstar->x9C % 60) + 1;
    data->rules.x20 &= 0xFFFFFFFFFFFBFCFFULL;

    if (arg0->id == 0) {
        data->players[0].xC_b1 = 1;
    } else {
        data->players[0].xC_b1 = 0;
    }

    if (arg0->id == 0x60) {
        u8* cpu_level = &allstar->x0.x0.cpu_level;
        f32 f31;
        f32 f30;
        u8 opp_count;

        f30 = gm_8018A1D8(0xC, *cpu_level);
        f31 = gm_8018A188(0xC, *cpu_level);
        opp_count = gm_8018A228(0xC, *cpu_level, 0);

        gm_8016A22C(3, 0x21, 0x21, 0, 0, 0, 1, 0, 0,
                    (u8) data->players[0].ckind, data->players[0].color,
                    (s32) opp_count, 0x19, 5, 1, 0, 1, f31, f30);

        data->rules.x4_5 = 1;
        data->rules.x0_3 = 6;
        gm_8016A21C(&data->rules);
    }

    data->players[0].x10 = allstar->x74;
    gm_LoadRumbleEnabled(data);
    allstar->x0.x0.mode = arg0->id;
}

void gm_801B59AC(GameModeState* arg0)
{
    u8* base = (u8*) gm_Mode_AllStar_States;
    MatchExitInfo* exit = gm_GetGameModeStateExitData(arg0);
    u8 idx = arg0->id;
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
    if (gm_8017D7AC(exit, &data->x0, 0x69) != 0 && arg0->id == 0x60) {
        gm_8017CBAC((UnkAdventureData*) data, gmMainLib_8015CDE0(), 0x17);
    }
}

void fn_801B5AA8(int arg0)
{
    lbBgFlash_8002063C(0x78);
}

static inline void gm_801B5ACC_inline1(AllstarRoundInfo* ri)
{
    s32 end_idx = ri[1].start;
    gm_803DEBE8_t* opp = &gm_803DEBE8[end_idx];

    while (end_idx < 0x19) {
        gm_8016A998((s8) opp->x3, 0);
        opp++;
        end_idx++;
    }
}

void gm_801B5ACC(GameModeState* arg0)
{
    s8 chars[3];
    u8 color;
    u16 round;
    StartMeleeData* data;
    u16 rest_round;
    s32 i;
    PAD_STACK(7 * 4);

    chars[0] = CHKIND_NONE;
    chars[1] = CHKIND_NONE;
    chars[2] = CHKIND_NONE;
    data = gm_GetGameModeStateEnterData(arg0);
    gm_80473A18.x0.x8 |= (1 << 7);

    round = gm_8017BE84(arg0->id);
    {
        uintptr_t opp = (uintptr_t) &gm_803DEBE8[gm_803DEC4C[round].start];
        color = ((u8*) gm_80490940)[((u32) opp - (u32) gm_803DEBE8) >> 2];
    }

    gm_8017CE34(data, &gm_80473A18.x0, chars, 0, 0, 0, 0, 85, 0, (s32) color);

    data->rules.x0_6 = 0;
    data->rules.timer_counts_up = 1;
    data->rules.x1_0 = 1;
    data->rules.time_limit = (s32) gm_80473A18.x9C / GM_FPS;
    data->rules.x14 = (s32) gm_80473A18.x9C % GM_FPS;
    data->rules.xD = GM_NAMETAG_NONE;
    data->players[0].x10 = gm_80473A18.x74;
    data->players[0].xD_b2 = 1;
    data->rules.x7 = 9;
    rest_round = gm_8017BE84(arg0->id);

    {
        UnkAllstarData* allstar = &gm_80473A18;
        AllstarRoundInfo* ri = &gm_803DEC4C[rest_round];

        for (i = 0; i < ri->count; i++) {
            u8* slot_ptr;
            s32 slot;
            u8* p;
            do {
                slot = HSD_Randi(CKIND_PLAYABLE_COUNT);
                p = (u8*) allstar + slot;
                slot_ptr = p + 0x76;
            } while ((s32) p[0x76] != CHKIND_NONE);
            *slot_ptr = gm_803DEBE8[i + ri->start].x3;
        }

        for (i = 0; i < (&gm_803DEC4C[rest_round])[1].count; i++) {
            gm_80473A18.x96[i] =
                gm_803DEBE8[(&gm_803DEC4C[rest_round])[1].start + i].x3;
        }

        gm_80473A18._94[1] = (u8) i;
        gm_80473A18._94[0] = (u8) (rest_round + 1);
        data->players[0].xC_b1 = 0;
        data->rules.x1_2 = 1;
        data->rules.x1_3 = 1;
        data->rules.x4_4 = 0;
        gm_LoadRumbleEnabled(data);
        gm_8016A92C(&data->rules);

        gm_801B5ACC_inline1(&gm_803DEC4C[rest_round]);

        gm_801B5324(allstar, (s32) rest_round + 1);
        data->rules.x50 = (void (*)(u8))(Event) fn_801B5AA8;
    }
}

void gm_801B5E7C(GameModeState* arg0)
{
    MatchExitInfo* exit = gm_GetGameModeStateExitData(arg0);
    gm_80473A18.x74 = exit->match_end.player_standings[0].percent;
    gm_8017D7AC(exit, &gm_80473A18.x0, 0x69);
}

void gm_801B5EB4(GameModeState* arg0)
{
    DebugGameOverData* data = gm_GetGameModeStateEnterData(arg0);
    gm_8017C9A8(data, &gm_80473A18.x0, 2);
}

void gm_801B5EE4(GameModeState* arg0)
{
    DebugGameOverData* data = gm_GetGameModeStateExitData(arg0);
    UnkAllstarData* r30 = &gm_80473A18;
    gm_8017CA38(data, &r30->x0, gmMainLib_8015CDE0(), 2);
    if (data->xC != 0) {
        r30->x74 = 0;
    }
}

void gm_801B5F50(GameModeState* arg0)
{
    CSSData* temp_r31;
    struct gmm_x0_528_t* temp_r3;

    temp_r31 = gm_GetGameModeStateEnterData(arg0);
    temp_r3 = gmMainLib_8015CDE0();
    gm_801B06B0(temp_r31, 0xD, temp_r3->c_kind, temp_r3->stocks,
                temp_r3->color, temp_r3->nametag, temp_r3->cpu_level,
                gm_80473A18.x0.x0.slot);
    lbDvd_SetupVsPreloadCache();
}

/// #gm_801B5F50

void gm_801B5FB4(GameModeState* arg0)
{
    CSSData* temp_r31 = gm_GetGameModeStateExitData(arg0);
    struct gmm_x0_528_t* temp_r30 = gmMainLib_8015CDE0();
    UnkAllstarData* r29 = &gm_80473A18;

    if (temp_r31->pending_scene_change == 2) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return;
    }
    gm_801B0730(temp_r31, &temp_r30->c_kind, &temp_r30->stocks,
                &temp_r30->color, &temp_r30->nametag, &temp_r30->cpu_level);
    r29->x0.x0.ckind = temp_r30->c_kind;
    r29->x0.x0.color = temp_r30->color;
    r29->x0.x0.cpu_level = temp_r30->cpu_level;
    r29->x0.x0.stocks = temp_r30->stocks;
    r29->x0.x0.nametag = temp_r30->nametag;
    gm_SetNextGameModeStateId((temp_r30->x5 * 8) & 0xF8);
    gm_80168F88();
    gm_801B5324(r29, temp_r30->x5);
}

void gm_801B607C(GameModeState* unused)
{
    gm_SetPendingGameMode(GM_MENU);
    gm_SetNewGameModePending();
}

void gm_Mode_AllStar_OnLoad(void)
{
    UnkAllstarData* data;
    u32 index;
    int temp;
    gm_803DEBE8_t tmp;
    PAD_STACK(8);

    data = &gm_80473A18;
    gmMainLib_8015CDE0();
    gm_8017C984(data);

    {
        u8* pp = (u8*) gm_80490940;
        int i;
        for (i = 25; i > 0; i--) {
            *pp++ = 0;
        }
    }

    gm_8017DB58(data->x0.xC.x24);
    data->x0.x0.slot = gm_801677F0();
    data->x0.x48 = gm_8018A160;
    data->x0.x4C = gm_8018A228;
    data->x0.x50 = gm_8018A290;
    data->x0.x54 = gm_8018A25C;
    data->x0.x58 = NULL;
    data->x0.x64 = gm_8018A2C4;
    data->x0.x68 = gm_8018A314;

    for (index = 0; index < 25; index++) {
        gm_803DEBE8_t* opponent = &gm_803DEBE8[index];
        opponent->x2 = ((u8*) opponent)[HSD_Randi(2)];
    }

    for (index = 0; index < 0x17; index++) {
        u32 rand_offset = HSD_Randi(0x18 - index);
        tmp = gm_803DEBE8[index];
        {
            gm_803DEBE8_t* swap = &gm_803DEBE8[index + rand_offset];
            gm_803DEBE8[index] = *swap;
            *swap = tmp;
        }
    }

    data->x74 = 0;
    data->x9C = 0;
    {
        int i;
        temp = 0x21;
        for (i = 0; i < 0x1A; i++) {
            gm_80473A18.x76[i] = temp;
        }
    }

    {
        u8* p = gm_80473A18.x90;
        p[0] = 1;
        p[1] = 1;
        p[2] = 1;
        p[3] = 1;
    }

    gm_SetGameModeStateId(0x70U);
    gm_80172174();
    Ground_801C5A28();
}

void gm_Mode_AllStar_OnInit(void)
{
    struct gmm_x0_528_t* temp_r3 = gmMainLib_8015CDE0();
    temp_r3->c_kind = CHKIND_NONE;
    temp_r3->color = 0;
    temp_r3->stocks = 1;
    temp_r3->cpu_level = 0;
    temp_r3->nametag = 0x78;
    temp_r3->x5 = 0;
}
