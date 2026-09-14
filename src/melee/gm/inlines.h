#ifndef MELEE_GM_INLINES_H
#define MELEE_GM_INLINES_H

#include <melee/gm/gmregtyfall.h>
#include <melee/ty/toy.h>

static inline s32 gmClampResultStat(s32 value)
{
    if (value > 999999) {
        value = 999999;
    } else if (value < -999999) {
        value = -999999;
    }
    return value;
}

/// @todo Figure out where this goes
static inline s32 fn_801A7FB4_inline(void)
{
    s32 i;
    s32 count;
    count = 0;
    for (i = count; i < 0x1A; i++) {
        if (Toy_803048C0(gm_801A659C(i)) ? true : false) {
            count++;
        }
    }
    return count;
}

static inline s32 fn_801A7FB4_inline2(void)
{
    s32 count;
    s32 i;
    count = 0;
    for (i = count; i < 0x1A; i++) {
        if (Toy_803048C0(gm_801A659C(i)) ? true : false) {
            count++;
        }
    }
    return count;
}

static inline f32 gmTournament_GetPlayerX(u8 player_count, s32 player)
{
    if ((s32) player_count == 4) {
        return (13.0f * (f32) player) + -19.5f;
    }
    if ((s32) player_count == 3) {
        return 6.5f + ((13.0f * (f32) player) - 19.5f);
    }
    return 6.5f + ((13.0f * (2.0f * (f32) player)) - 19.5f);
}

static inline void gmTournament_SetPlayerX(f32* x, u8 player_count, s32 player)
{
    if ((s32) player_count == 4) {
        *x = (13.0f * (f32) player) + -19.5f;
    } else if ((s32) player_count == 3) {
        *x = 6.5f + ((13.0f * (f32) player) - 19.5f);
    } else {
        *x = 6.5f + ((13.0f * (2.0f * (f32) player)) - 19.5f);
    }
}

#endif
