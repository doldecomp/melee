#include "gm_18A1.h"

#include "gm_16AE.h"
#include "gmmain_lib.h"
#include "gmregclear.h"
#include "types.h"

#include <melee/pl/player.h>

/// Classic mode stage data.
typedef struct ClassicStageEntry {
    /* 0x00 */ u8 stage_kind;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 scale0_pct; ///< Divided by 100 to get ratio
    /* 0x04 */ u16 scale1_pct; ///< Divided by 100 to get ratio
    /* 0x06 */ u8 pad_6[0xA];
} ClassicStageEntry;

typedef struct {
    u8 b7 : 1, b6 : 1, b5 : 1, b4 : 1, b3 : 1, b2 : 1, b1 : 1, b0 : 1;
} u8_bits;

/* 473A18 */ UnkAllstarData gm_80473A18;

static ClassicStageEntry gmTraining_ClassicStages[65] = {
    { 4, 0, 50, 170, { 0, 1, 0x17, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 70, 140, { 1, 1, 0x17, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 80, 120, { 3, 1, 0x17, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, 0, 90, 100, { 5, 1, 0x17, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, 0, 100, 95, { 7, 1, 0x17, 0, 0, 0, 0, 0, 0, 0 } },
    { 4, 0, 50, 170, { 1, 2, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 70, 140, { 3, 2, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 80, 115, { 4, 2, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, 0, 90, 100, { 6, 2, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, 0, 100, 95, { 8, 2, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 4, 0, 50, 170, { 2, 3, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 70, 140, { 4, 3, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 80, 110, { 5, 3, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, 0, 90, 100, { 7, 3, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, 0, 100, 95, { 9, 3, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 4, 0, 50, 170, { 3, 1, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 70, 140, { 5, 1, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 80, 120, { 6, 1, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, 0, 90, 105, { 8, 1, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, 0, 100, 95, { 9, 1, 4, 0, 0, 0, 0, 0, 0, 0 } },
    { 4, 0, 50, 170, { 0, 2, 0x17, 0, 2, 0x17, 0, 0, 0, 0 } },
    { 3, 0, 67, 140, { 2, 2, 0x17, 2, 2, 0x17, 0, 0, 0, 0 } },
    { 3, 0, 78, 120, { 3, 2, 0x17, 3, 2, 0x17, 0, 0, 0, 0 } },
    { 2, 0, 90, 105, { 5, 2, 4, 4, 2, 4, 0, 0, 0, 0 } },
    { 1, 0, 100, 100, { 6, 2, 4, 6, 2, 4, 0, 0, 0, 0 } },
    { 4, 0, 50, 170, { 1, 3, 0x17, 1, 3, 0x17, 0, 0, 0, 0 } },
    { 3, 0, 67, 140, { 3, 3, 4, 3, 3, 0x17, 0, 0, 0, 0 } },
    { 3, 0, 78, 120, { 4, 3, 4, 3, 3, 4, 0, 0, 0, 0 } },
    { 2, 0, 90, 105, { 5, 3, 4, 5, 3, 4, 0, 0, 0, 0 } },
    { 1, 0, 100, 100, { 7, 3, 4, 7, 3, 4, 0, 0, 0, 0 } },
    { 4, 0, 50, 170, { 2, 1, 0x17, 1, 1, 0x17, 0, 0, 0, 0 } },
    { 3, 0, 70, 140, { 3, 1, 4, 3, 1, 4, 0, 0, 0, 0 } },
    { 3, 0, 78, 120, { 4, 1, 4, 4, 1, 4, 0, 0, 0, 0 } },
    { 2, 0, 90, 105, { 6, 1, 4, 5, 1, 4, 0, 0, 0, 0 } },
    { 1, 0, 102, 100, { 8, 1, 4, 7, 1, 4, 0, 0, 0, 0 } },
    { 4, 0, 50, 170, { 2, 2, 4, 2, 2, 4, 0, 0, 0, 0 } },
    { 3, 0, 70, 130, { 3, 2, 4, 3, 2, 4, 0, 0, 0, 0 } },
    { 3, 0, 80, 110, { 5, 2, 4, 4, 2, 4, 0, 0, 0, 0 } },
    { 2, 0, 90, 105, { 7, 2, 4, 5, 2, 4, 0, 0, 0, 0 } },
    { 1, 0, 105, 100, { 9, 2, 4, 8, 2, 4, 0, 0, 0, 0 } },
    { 4, 0, 50, 170, { 0, 3, 0x17, 0, 3, 0x17, 0, 3, 0x17, 0 } },
    { 3, 0, 67, 130, { 2, 3, 0x17, 2, 3, 0x17, 1, 3, 0x17, 0 } },
    { 3, 0, 78, 110, { 3, 3, 0x17, 3, 3, 0x17, 3, 3, 0x17, 0 } },
    { 2, 0, 89, 100, { 4, 3, 4, 4, 3, 0x17, 4, 3, 0x17, 0 } },
    { 1, 0, 100, 100, { 6, 3, 4, 6, 3, 4, 6, 3, 0x17, 0 } },
    { 4, 0, 50, 170, { 1, 1, 0x17, 1, 1, 0x17, 1, 1, 0x17, 0 } },
    { 3, 0, 69, 125, { 2, 1, 0x17, 2, 1, 0x17, 2, 1, 0x17, 0 } },
    { 3, 0, 75, 110, { 4, 1, 0x11, 4, 1, 0x17, 3, 1, 0x17, 0 } },
    { 2, 0, 89, 100, { 5, 1, 4, 4, 1, 0x11, 4, 1, 0x17, 0 } },
    { 1, 0, 100, 100, { 7, 1, 4, 7, 1, 4, 7, 1, 0x11, 0 } },
    { 4, 0, 50, 170, { 1, 2, 0x17, 1, 2, 0x17, 1, 2, 0x17, 0 } },
    { 3, 0, 70, 125, { 3, 2, 0x11, 3, 2, 0x17, 3, 2, 0x17, 0 } },
    { 3, 0, 79, 112, { 4, 2, 4, 4, 2, 0x11, 4, 2, 0x17, 0 } },
    { 2, 0, 90, 100, { 5, 2, 4, 5, 2, 4, 4, 2, 0x11, 0 } },
    { 1, 0, 100, 100, { 8, 2, 4, 8, 2, 4, 7, 2, 4, 0 } },
    { 4, 0, 50, 170, { 2, 3, 0x17, 2, 3, 0x17, 1, 3, 0x17, 0 } },
    { 3, 0, 70, 125, { 4, 3, 0x11, 4, 3, 4, 3, 3, 0x17, 0 } },
    { 3, 0, 80, 110, { 5, 3, 4, 4, 3, 0x11, 4, 3, 0x17, 0 } },
    { 2, 0, 92, 100, { 6, 3, 4, 5, 3, 4, 5, 3, 0x11, 0 } },
    { 1, 0, 105, 96, { 9, 3, 4, 8, 3, 4, 8, 3, 0x11, 0 } },
    { 4, 0, 20, 360, { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 30, 320, { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 3, 0, 40, 300, { 3, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 2, 0, 48, 240, { 5, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
    { 1, 0, 55, 200, { 7, 0, 0, 0, 0, 0, 0, 0, 0, 0 } },
};

STATIC_ASSERT(sizeof(gmTraining_ClassicStages[0]) == 0x10);
STATIC_ASSERT(sizeof(gmTraining_ClassicStages) == 0x410);

u8 gm_8018A160(u8 difficulty, u8 stage_slot)
{
    return gmTraining_ClassicStages[stage_slot + (difficulty * 5)].stage_kind;
}

f32 gm_8018A188(u8 difficulty, u8 stage_slot)
{
    return (f32) gmTraining_ClassicStages[stage_slot + (difficulty * 5)]
               .scale0_pct /
           100.0F;
}

f32 gm_8018A1D8(u8 difficulty, u8 stage_slot)
{
    return (f32) gmTraining_ClassicStages[stage_slot + (difficulty * 5)]
               .scale1_pct /
           100.0F;
}

u8 gm_8018A228(u8 difficulty, u8 stage_slot, u8 idx)
{
    return gmTraining_ClassicStages[stage_slot + (difficulty * 5)]
        .pad_6[idx * 3];
}

u8 gm_8018A25C(u8 difficulty, u8 stage_slot, u8 arg2)
{
    return gmTraining_ClassicStages[stage_slot + difficulty * 5]
        .pad_6[arg2 * 3 + 1];
}

u8 gm_8018A290(u8 difficulty, u8 stage_slot, u8 idx)
{
    return gmTraining_ClassicStages[stage_slot + (difficulty * 5)]
        .pad_6[2 + idx * 3];
}

f32 gm_8018A2C4(u8 difficulty, u8 stage_slot)
{
    return (f32) gmTraining_ClassicStages[stage_slot + (difficulty * 5)]
               .scale0_pct /
           100.0F;
}

f32 gm_8018A314(u8 difficulty, u8 stage_slot)
{
    return (f32) gmTraining_ClassicStages[stage_slot + (difficulty * 5)]
               .scale1_pct /
           100.0F;
}

void fn_8018A364(int arg0_int)
{
    MatchEnd* arg0 = (MatchEnd*) arg0_int;
    struct StartMeleeRules* rules;
    gmm_x0_528_t* main_data;
    UnkAllstarData* data;
    u32 total_time;

    rules = gm_GetRules();
    data = &gm_80473A18;

    if (fn_8017E318() > 0) {
        ((u8_bits*) &arg0->_x448[2])->b3 = 1;
    }

    if (rules->x4_5) {
        main_data = gmMainLib_8015CDE0();
        total_time = data->x0.xC.x20 + gm_8016AEDC();
        ((u8_bits*) &arg0->_x448[0])->b5 = 1;

        if (data->x0.x0.cpu_level == 4) {
            ((u8_bits*) &arg0->_x448[0])->b2 = 1;
        }

        if (total_time < 0x6270U) {
            ((u8_bits*) &arg0->_x448[2])->b6 = 1;
        } else if (total_time < 0x9AB0U) {
            ((u8_bits*) &arg0->_x448[2])->b7 = 1;
        }

        if ((u32) data->x0.xC.x1C == 0U && arg0->player_standings[0].x44 == 0)
        {
            ((u8_bits*) &arg0->_x448[1])->b1 = 1;
        }

        if (data->x0.xC.xE != 0) {
            ((u8_bits*) &arg0->_x448[2])->b5 = 1;
        }

        if (data->x0.xC.xF != 0) {
            ((u8_bits*) &arg0->_x448[2])->b4 = 1;
        }

        if ((data->x0.xC.x1C + arg0->player_standings[0].x44) ==
            (u32) Player_GetDamage(0))
        {
            ((u8_bits*) &arg0->_x448[0])->b1 = 1;
        }

        if (data->x0.xC.xD != 0) {
            ((u8_bits*) &arg0->_x448[1])->b0 = 1;
            return;
        }

        if (arg0->player_standings[0].stocks == main_data->stocks) {
            ((u8_bits*) &arg0->_x448[1])->b2 = 1;
        }
    }
}
