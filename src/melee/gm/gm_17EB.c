#include "gmregclear.h"
#include <Runtime/platform.h>

#include "forward.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "types.h"
#include <melee/pl/player.h>

typedef struct AllstarStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct; ///< Divided by 100 to get ratio
    /* 0x04 */ u16 scale1_pct; ///< Divided by 100 to get ratio
    /* 0x06 */ u8 pad_6[0xA];
    /* 0x10 */ u16 scale2_pct; ///< Divided by 100 to get ratio
    /* 0x12 */ u16 scale3_pct; ///< Divided by 100 to get ratio
    /* 0x14 */ u8 pad_14[0x6];
} AllstarStageEntry;
ASSERT_SIZE(AllstarStageEntry, 0x1A);

typedef struct {
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
} u8_bits;

static u8 lbl_80472CB0[0x78];

AllstarStageEntry lbl_803D85F0[55] = {
    { 4, 0, 0x3c, 0xaf, { 0, 0, 9 } },
    { 3, 0, 0x55, 0x78, { 2, 0, 4 } },
    { 3, 0, 0x64, 0x64, { 4, 0, 4 } },
    { 2, 0, 0x64, 0x64, { 7, 0, 4 } },
    { 1, 0, 0x78, 0x5a, { 9, 3, 8 } },
    { 4, 0, 0x46, 0xa0, { 1, 0, 4, 2, 0, 9 }, 0x50, 0x5a, { 8, 1, 4 } },
    { 4, 0, 0x55, 0x78, { 3, 0, 4, 3, 0, 4 }, 0x50, 0x64, { 7, 1, 4 } },
    { 3, 0, 0x64, 0x64, { 5, 0, 4, 4, 0, 4 }, 0x50, 0x73, { 6, 1, 4 } },
    { 3, 0, 0x64, 0x5a, { 6, 0, 4, 6, 0, 8 }, 0x50, 0x82, { 4, 1, 4 } },
    { 1, 0, 0x73, 0x50, { 8, 3, 4, 8, 0, 8 }, 0x50, 0x96, { 3, 1, 4 } },
    { 0xff },
    { 0xff },
    { 0xff },
    { 0xff },
    { 0xff },
    { 4, 0, 0x4b, 0x8c, { 2, 0, 4 } },
    { 4, 0, 0x5a, 0x6e, { 5, 0, 4 } },
    { 4, 0, 0x64, 0x64, { 8, 0, 4 } },
    { 4, 0, 0x73, 0x55, { 9, 0, 4 } },
    { 4, 0, 0x86, 0x46, { 9, 0, 4 } },
    { 3, 0, 0x46, 0x168, { 2, 0, 0x1b }, 0x64, 0x64, { 6, 2, 4, 6, 1, 4 } },
    { 3, 0, 0x50, 0xf0, { 3, 0, 0x1b }, 0x64, 0x5a, { 5, 2, 4, 5, 1, 4 } },
    { 2, 0, 0x5a, 0xb4, { 5, 0, 0x1b }, 0x64, 0x50, { 2, 2, 4, 2, 1, 9 } },
    { 2, 0, 0x64, 0x8c, { 7, 0, 4 }, 0x64, 0x50, { 1, 2, 4, 1, 1, 9 } },
    { 1, 0, 0x78, 0x64, { 8, 0, 4 }, 0x64, 0x50, { 0, 2, 4, 0, 1, 9 } },
    { 0xff },
    { 0xff },
    { 0xff },
    { 0xff },
    { 0xff },
    { 2, 0, 0x55, 0x82, { 3, 0, 4 } },
    { 2, 0, 0x64, 0x6e, { 6, 0, 4 } },
    { 2, 0, 0x5a, 0x82, { 5, 0, 4 } },
    { 2, 0, 0x64, 0x6e, { 6, 0, 0x12 } },
    { 1, 0, 0x6e, 0x5a, { 8, 0, 0x12 } },
    { 3, 0, 0x3c, 0x190, { 1, 0, 0x19 } },
    { 3, 0, 0x46, 0x104, { 3, 0, 0x17 } },
    { 2, 0, 0x50, 0xc8, { 4, 0, 0x17 } },
    { 2, 0, 0x5a, 0x9b, { 5, 0, 0x17 } },
    { 1, 0, 0x6e, 0x78, { 7, 0, 0x17 } },
    { 2, 0, 0x64, 0x64, { 1, 0, 4, 0, 0, 4, 0, 0, 4 }, 0x64, 0x64 },
    { 2, 0, 0x64, 0x64, { 1, 0, 4, 0, 0, 4, 0, 0, 4 }, 0x64, 0x64 },
    { 2, 0, 0x64, 0x64, { 1, 0, 4, 0, 0, 4, 0, 0, 4 }, 0x64, 0x64 },
    { 2, 0, 0x64, 0x64, { 1, 0, 4, 0, 0, 4, 0, 0, 4 }, 0x64, 0x64 },
    { 2, 0, 0x64, 0x64, { 1, 0, 4, 0, 0, 4, 0, 0, 4 }, 0x64, 0x64 },
    { 2, 0, 0x50, 0xb4, { 1, 0, 0x1b } },
    { 2, 0, 0x5a, 0x82, { 3, 0, 0x1b } },
    { 2, 0, 0x64, 0x64, { 5, 0, 0x1b } },
    { 1, 0, 0x6e, 0x55, { 8, 0, 0x1b } },
    { 0xff, 0, 0x7d, 0x44, { 9, 0, 0x1b } },
    { 2, 0, 0x32, 0x64, { 5, 0, 4 } },
    { 2, 0, 0x4b, 0x64, { 6, 0, 4 } },
    { 2, 0, 0x64, 0x64, { 7, 0, 4 } },
    { 2, 0, 0x96, 0x64, { 8, 0, 4 } },
    { 0xff, 0, 0xc8, 0x64, { 9, 0, 4 } },
};

UnkAllstarData* gm_GetAllStarData(void)
{
    return (UnkAllstarData*) lbl_80472CB0;
}

u8 gm_8017EB3C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].stage_kind;
}

u8 gm_8017EB64(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_6[arg2 * 3];
}

u8 gm_8017EB98(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_6[arg2 * 3 + 1];
}

u8 gm_8017EBCC(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_6[arg2 * 3 + 2];
}

f32 gm_8017EC00(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].scale2_pct / 100.0F;
}

f32 gm_8017EC50(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].scale3_pct / 100.0F;
}

u8 gm_8017ECA0(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].pad_14[arg2 * 3];
}

u8 gm_8017ECD4(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + (difficulty * 5)].pad_14[arg2 * 3 + 1];
}

u8 gm_8017ED08(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return lbl_803D85F0[stage_slot + (difficulty * 5)].pad_14[arg2 * 3 + 2];
}

f32 gm_8017ED3C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].scale0_pct / 100.0F;
}

f32 gm_8017ED8C(u8 difficulty, u8 stage_slot)
{
    return lbl_803D85F0[stage_slot + difficulty * 5].scale1_pct / 100.0F;
}

bool fn_8017EDDC(void)
{
    UnkAllstarData* p;

    if (gm_GetCurrentGameMode() == GM_CLASSIC) {
        p = gm_GetAllStarData();
        if (p->x0.xC.xD == 0 && p->x0.x0.cpu_level >= 2 &&
            p->x0.xC.x20 < 0x5208)
        {
            return true;
        }
    }
    return false;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void fn_8017EE40(int arg0_int)
{
    MatchEnd* arg0 = (MatchEnd*) arg0_int;
    struct StartMeleeRules* rules;
    UnkAllstarData* allstar;
    gmm_x0_528_t* main_data;
    u32 total_time;
    int i;

    rules = gm_GetRules();
    allstar = (UnkAllstarData*) lbl_80472CB0;

    if (fn_8017E318() > 0) {
        ((u8_bits*) &arg0->_x448[2])->b3 = 1;
    }

    if (rules->x4_5) {
        main_data = gmMainLib_8015CDC8();
        total_time = allstar->x0.xC.x20 + gm_8016AEDC();
        ((u8_bits*) &arg0->_x448[0])->b7 = 1;

        if (allstar->x0.x0.cpu_level == 4) {
            ((u8_bits*) &arg0->_x448[0])->b4 = 1;
        }

        if (total_time < 0x3840U) {
            ((u8_bits*) &arg0->_x448[2])->b6 = 1;
        } else if (total_time < 0x5460U) {
            ((u8_bits*) &arg0->_x448[2])->b7 = 1;
        }

        if ((u32) allstar->x0.xC.x1C == 0U &&
            arg0->player_standings[0].x44 == 0U)
        {
            ((u8_bits*) &arg0->_x448[1])->b1 = 1;
        }

        if (allstar->x0.xC.xE != 0) {
            ((u8_bits*) &arg0->_x448[2])->b5 = 1;
        }

        if (allstar->x0.xC.xF != 0) {
            ((u8_bits*) &arg0->_x448[2])->b4 = 1;
        }

        if (allstar->x0.xC.xD != 0) {
            ((u8_bits*) &arg0->_x448[1])->b0 = 1;
        } else if (arg0->player_standings[0].stocks == (s32) main_data->stocks)
        {
            ((u8_bits*) &arg0->_x448[1])->b2 = 1;
        }
    }

    for (i = 0; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) == Gm_PKind_Cpu &&
            Player_GetPlayerCharacter(i) == CKIND_CREZYH)
        {
            ((u8_bits*) &arg0->_x448[0])->b0 = 1;
            return;
        }
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif
