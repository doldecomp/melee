#include "gmregclear.h"
#include "platform.h"

#include "gm/forward.h"

#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmadventure.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/if/ifstatus.h>
#include <melee/pl/player.h>

typedef struct AdventureStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct; ///< Divided by 100 to get ratio
    /* 0x04 */ u16 scale1_pct; ///< Divided by 100 to get ratio
    /* 0x06 */ u8 pad_6[0x14];
} AdventureStageEntry;
ASSERT_SIZE(AdventureStageEntry, 0x1A);

static UnkAdventureData lbl_80472C30;

AdventureStageEntry lbl_803D7AC0[110] = {
    { 4, 0, 0x28, 0x1c2, { 1 } },
    { 3, 0, 0x32, 0x190, { 2 } },
    { 3, 0, 0x3c, 0x140, { 4 } },
    { 2, 0, 0x46, 0xf0, { 5 } },
    { 1, 0, 0x50, 0xaa, { 6 } },
    { 4, 0, 0x50, 0x8c, { 0, 0, 0x10, 0, 0, 4 } },
    { 3, 0, 0x5e, 0x70, { 3, 0, 0x10, 3, 0, 4 } },
    { 3, 0, 0x64, 0x6b, { 5, 0, 0x10, 4, 0, 4 } },
    { 3, 0, 0x6e, 0x69, { 7, 0, 0x10, 7, 0, 4 } },
    { 2, 0, 0x78, 0x5f, { 8, 0, 0x10, 8, 0, 4 } },
    { 4, 0, 0x50, 0x8c, { 1, 0, 4, 1, 1, 8 } },
    { 4, 0, 0x64, 0x5a, { 2, 0, 4, 2, 1, 8 } },
    { 3, 0, 0x6e, 0x46, { 4, 0, 4, 3, 1, 8 } },
    { 2, 0, 0x78, 0x32, { 7, 0, 4, 6, 1, 8 } },
    { 1, 0, 0x82, 0x28, { 9, 0, 4, 9, 1, 8 } },
    { 4, 0, 0x3c, 0x17c, { 1, 0,    4, 0,    0, 0, 0, 0, 0, 0,
                           0, 0x64, 0, 0x64, 0, 0, 4, 0, 0, 4 } },
    { 4, 0, 0x50, 0xfa, { 3, 0,    4, 0,    0, 0, 0, 0, 0, 0,
                          0, 0x64, 0, 0x64, 0, 0, 4, 0, 0, 4 } },
    { 3, 0, 0x5a, 0xc8, { 5, 0,    4, 0,    0, 0, 0, 0, 0, 0,
                          0, 0x64, 0, 0x64, 0, 0, 4, 0, 0, 4 } },
    { 2, 0, 0x5f, 0xa0, { 7, 0,    4, 0,    0, 0, 0, 0, 0, 0,
                          0, 0x64, 0, 0x64, 0, 0, 4, 0, 0, 4 } },
    { 1, 0, 0x6e, 0x78, { 8, 0,    4, 0,    0, 0, 0, 0, 0, 0,
                          0, 0x64, 0, 0x64, 0, 0, 4, 0, 0, 4 } },
    { 3, 0, 0x46, 0xa0, { 1 } },
    { 2, 0, 0x50, 0x8c, { 3 } },
    { 2, 0, 0x5a, 0x78, { 5 } },
    { 1, 0, 0x64, 0x69, { 7 } },
    { 1, 0, 0x6c, 0x5f, { 9 } },
    { 4, 0, 0x50, 0x7d, { 2, 0, 4 } },
    { 4, 0, 0x5a, 0x6e, { 6, 0, 4 } },
    { 3, 0, 0x64, 0x64, { 8, 0, 4 } },
    { 3, 0, 0x76, 0x5f, { 9, 0, 4 } },
    { 2, 0, 0x82, 0x5a, { 9, 0, 4 } },
    { 3, 0, 0x50, 0x82, { 2, 0, 4 } },
    { 3, 0, 0x5a, 0x6e, { 5, 0, 4 } },
    { 2, 0, 0x64, 0x64, { 7, 0, 4 } },
    { 2, 0, 0x73, 0x58, { 8, 0, 4 } },
    { 1, 0, 0x82, 0x4a, { 9, 0, 4 } },
    { 0xff },
    { 0xff },
    { 0xff },
    { 0xff },
    { 0xff },
    { 3, 0, 0x50, 0xaa, { 2, 0, 4 } },
    { 2, 0, 0x64, 0x82, { 4, 0, 4 } },
    { 2, 0, 0x78, 0x6e, { 6, 0, 4 } },
    { 1, 0, 0x82, 0x64, { 8, 0, 4 } },
    { 0xff, 0, 0x8c, 0x5a, { 9, 0, 4 } },
    { 3, 0, 0x3c, 0x1f4, { 1 } },
    { 2, 0, 0x46, 0x190, { 3 } },
    { 2, 0, 0x50, 0x12c, { 4 } },
    { 1, 0, 0x5a, 0xc8, { 6 } },
    { 0xff, 0, 0x64, 0xaf, { 7 } },
    { 3, 0, 0x46, 0xf0, { 2, 0, 0x1b } },
    { 2, 0, 0x4b, 0xb4, { 4, 0, 0x1b } },
    { 2, 0, 0x50, 0x82, { 6, 0, 0x1b } },
    { 1, 0, 0x64, 0x64, { 7, 0, 4 } },
    { 1, 0, 0x78, 0x5a, { 9, 0, 4 } },
    { 2, 0, 0x50, 0xb4, { 2, 0, 0x1b } },
    { 2, 0, 0x5a, 0x96, { 4, 0, 4 } },
    { 2, 0, 0x64, 0x82, { 5, 0, 0x12 } },
    { 2, 0, 0x76, 0x6e, { 6, 0, 0x12 } },
    { 2, 0, 0x82, 0x64, { 7, 0, 0x12 } },
    { 2, 0, 0x3c, 0xd2, { 2, 1, 8 } },
    { 2, 0, 0x46, 0xb4, { 4, 1, 8 } },
    { 2, 0, 0x5a, 0x8c, { 6, 1, 8 } },
    { 2, 0, 0x69, 0x78, { 8, 1, 8 } },
    { 2, 0, 0x75, 0x64, { 9, 1, 8 } },
    { 4, 0, 0x3c, 0x1a4, { 1 } },
    { 4, 0, 0x4e, 0x140, { 4 } },
    { 4, 0, 0x58, 0xc8, { 5 } },
    { 3, 0, 0x62, 0xaa, { 7 } },
    { 2, 0, 0x6d, 0x96, { 8 } },
    { 0xff },
    { 0xff },
    { 0xff },
    { 0xff },
    { 0xff },
    { 2, 0, 0x50, 0x96, { 3, 0, 4 } },
    { 2, 0, 0x64, 0x6e, { 6, 0, 4 } },
    { 2, 0, 0x6e, 0x64, { 8, 0, 4 } },
    { 2, 0, 0x78, 0x5a, { 9, 0, 4 } },
    { 2, 0, 0x82, 0x46, { 9, 2, 4 } },
    { 4,
      0,
      0x46,
      0xbe,
      { 1, 0, 0x1d, 1, 2, 0x1d, 1, 1, 0x1b, 0, 0, 0x64, 0, 0x64 } },
    { 4,
      0,
      0x50,
      0x96,
      { 3, 0, 0x1d, 3, 2, 0x1d, 2, 1, 0x1d, 0, 0, 0x64, 0, 0x64 } },
    { 4,
      0,
      0x5a,
      0x82,
      { 5, 0, 0x1d, 4, 2, 0x1d, 4, 1, 0x1d, 0, 0, 0x64, 0, 0x64 } },
    { 4,
      0,
      0x64,
      0x6e,
      { 7, 0, 0x1d, 6, 2, 0x1d, 5, 1, 0x1d, 0, 0, 0x64, 0, 0x64 } },
    { 4,
      0,
      0x82,
      0x64,
      { 8, 0, 0x1d, 8, 2, 0x1d, 8, 1, 0x1d, 0, 0, 0x64, 0, 0x64 } },
    { 2, 0, 0x50, 0xbe, { 1 } },
    { 2, 0, 0x55, 0x8c, { 3 } },
    { 2, 0, 0x5a, 0x82, { 4 } },
    { 2, 0, 0x5f, 0x78, { 6 } },
    { 2, 0, 0x64, 0x64, { 9 } },
    { 2, 0, 0x32, 0x1a4, { 1 } },
    { 2, 0, 0x3c, 0x172, { 3 } },
    { 2, 0, 0x46, 0x118, { 5 } },
    { 2, 0, 0x50, 0xc8, { 6 } },
    { 2, 0, 0x5a, 0x96, { 8 } },
    { 2, 0, 0x46, 0xbe, { 1, 0, 0x1b, 1, 0, 0x1b } },
    { 2, 0, 0x5a, 0x96, { 3, 0, 0x1b, 2, 0, 0x1b } },
    { 2, 0, 0x64, 0x82, { 5, 0, 0x1b, 3, 0, 0x1b } },
    { 2, 0, 0x6e, 0x6e, { 6, 0, 0x1b, 5, 0, 0x1b } },
    { 2, 0, 0x78, 0x5a, { 8, 0, 0x1b, 7, 0, 0x1b } },
    { 3, 0, 0x46, 0x82, { 2, 0, 4 } },
    { 2, 0, 0x5d, 0x73, { 4, 0, 4 } },
    { 2, 0, 0x64, 0x69, { 6, 3, 4 } },
    { 1, 0, 0x6e, 0x58, { 8, 3, 4 } },
    { 0xff, 0, 0x78, 0x4b, { 9, 3, 4 } },
    { 2, 0, 1, 1, { 0, 0, 4 } },
    { 2, 0, 1, 1, { 0, 0, 4 } },
    { 1, 0, 0x87, 0x3a, { 7, 0, 4 } },
    { 1, 0, 0x94, 0x32, { 8, 0, 4 } },
    { 0xff, 0, 0xa0, 0x26, { 9, 0, 4 } },
};

UnkAdventureData* gm_GetAdventureData(void)
{
    return &lbl_80472C30;
}

u8 gm_8017E430(void)
{
    return gm_GetAdventureData()->x0.x0.slot;
}

u8 gm_8017E440(void)
{
    UnkAdventureData* r31 = gm_GetAdventureData();
    if (gm_RumbleEnabledForPlayer(r31->x0.x0.slot, r31->x0.x0.nametag) ==
        false)
    {
        return 4;
    }
    return r31->x0.x0.slot;
}

u8 gm_8017E48C(GameModeState* scene)
{
    u8 count = 0;
    int i;
    for (i = 0; scene->id != gm_Mode_Adventure_States[i].id; i++) {
        if (gm_Mode_Adventure_States[i].info.scene_kind == GS_VS) {
            count++;
        }
    }
    return count;
}

struct gm_803DE650_t* gm_8017E4C4(u8 arg0)
{
    struct gm_803DE650_t* ptr;
#ifdef MUST_MATCH
    (void) 100.0F;
#endif
    for (ptr = gm_803DE650; ptr->x0 != 0xFF; ptr++) {
        if (ptr->x0 == arg0) {
            return ptr;
        }
    }
    return NULL;
}

/// Get adventure stage kind for given difficulty and stage slot.
/// The (u8) cast on difficulty is required - these functions are called
/// via function pointers typed as f32(*)(int, u8) in UnkAdventureData.
u8 gm_8017E500(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].stage_kind;
}

f32 gm_8017E528(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].scale0_pct / 100.0F;
}

f32 gm_8017E578(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].scale1_pct / 100.0F;
}

u8 gm_8017E5C8(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[arg2 * 3];
}

u8 gm_8017E5FC(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[1 + arg2 * 3];
}

u8 gm_8017E630(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[arg2 * 3 + 2];
}

f32 gm_8017E664(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].scale0_pct / 100.0F;
}

f32 gm_8017E6B4(u8 difficulty, u8 stage_slot)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].scale1_pct / 100.0F;
}

u8 gm_8017E704(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[0x0E + arg2 * 3];
}

u8 gm_8017E738(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[0xF + arg2 * 3];
}

u8 gm_8017E76C(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D7AC0[stage_slot + difficulty * 5].pad_6[0x10 + (arg2 * 3)];
}

void gm_8017E7A0(u8 matchResult)
{
    if (matchResult == OUTCOME_TIMEOUT) {
        Player_LoseStock(0);
        ifStatus_802F6948(0);
        ifStatus_802F6E3C(0);
    }
}

bool gm_8017E7E0(void)
{
    return gm_GetAdventureData()->x7C == 0x14;
}

void gm_8017E7FC(u8 matchResult)
{
    UnkAdventureData* r31 = gm_GetAdventureData();
    bool cond;

    if (gm_GetCurrentGameMode() == GM_ADVENTURE && r31->x0.x0.cpu_level >= 2 &&
        r31->x0.xC.x20 + gm_8016AEDC() < 0xFD20U)
    {
        cond = true;
    } else {
        cond = false;
    }

    if (!cond) {
        struct StartMeleeRules* rules = gm_GetRules();
        rules->x4_5 = 1;
        r31->x77 = 0;
        gm_SetNextGameModeStateId(0x5A);
    } else {
        r31->x77 = 1;
        gm_SetNextGameModeStateId(0x5A);
    }
}

typedef struct {
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
} u8_bits;

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void fn_8017E8A4(int arg0_int)
{
    MatchEnd* arg0 = (MatchEnd*) arg0_int;
    lbl_8046B6A0_t* gm = gm_16AE_GetUnkData_0();
    struct gm_803DE650_t* stage = gm_8017E4C4(gm_GetCurrentSceneIndex());
    UnkAdventureData* adv = &lbl_80472C30;
    u8* flags = arg0->_x448;
    gmm_x0_528_t* main_data;
    u32 total_time;
    int i;

    if (fn_8017E318() > 0) {
        ((u8_bits*) &flags[2])->b3 = 1;
    }

    if (gm->x24C8.x4_5) {
        main_data = gmMainLib_8015CDD4();
        total_time = adv->x0.xC.x20 + gm_8016AEDC();
        ((u8_bits*) &flags[0])->b6 = 1;

        if (adv->x0.x0.cpu_level == 4) {
            ((u8_bits*) &flags[0])->b3 = 1;
        }

        if (total_time < 0xC4E0U) {
            ((u8_bits*) &flags[2])->b6 = 1;
        } else if (total_time < 0x13560U) {
            ((u8_bits*) &flags[2])->b7 = 1;
        }

        if ((u32) adv->x0.xC.x1C == 0U && arg0->player_standings[0].x44 == 0U)
        {
            ((u8_bits*) &flags[1])->b1 = 1;
        }

        if (adv->x0.xC.xE != 0) {
            ((u8_bits*) &flags[2])->b5 = 1;
        }

        if (adv->x0.xC.xF != 0) {
            ((u8_bits*) &flags[2])->b4 = 1;
        }

        if (adv->x0.xC.xD != 0) {
            ((u8_bits*) &flags[1])->b0 = 1;
        } else if (arg0->player_standings[0].stocks == (s32) main_data->stocks)
        {
            ((u8_bits*) &arg0->_x448[1])->b2 = 1;
        }
    }

    if (stage->x0 == 3) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
                Player_GetPlayerCharacter(i) == CKIND_LUIGI)
            {
                ((u8_bits*) &flags[1])->b7 = 1;
                return;
            }
        }
    }

    if (stage->x0 == 0x11) {
        if (gm->unk_C >= 5) {
            ((u8_bits*) &flags[1])->b6 = 1;
            return;
        }
    }

    if (stage->x0 == 0x25) {
        ((u8_bits*) &flags[1])->b5 = 1;
        return;
    } else if (stage->x0 == 0x53) {
        for (i = 0; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
                Player_GetPlayerCharacter(i) == CKIND_LUIGI)
            {
                ((u8_bits*) &flags[1])->b4 = 1;
                return;
            }
        }
    }

    if (stage->x0 == 0x5C) {
        ((u8_bits*) &flags[1])->b3 = 1;
    }

    PAD_STACK(8);
}
#ifdef MUST_MATCH
#pragma pop
#endif
