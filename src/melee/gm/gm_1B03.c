#include "gm_1B03.h"

#include "dolphin/types.h"
#include "gm/types.h"

#include "mn/forward.h"
#include <melee/pl/forward.h>

#include <melee/gm/gm_unsplit.h>
#include <melee/gm/types.h>
#include <melee/mn/types.h>

/**
 * Update character tints
 *
 * If any two players are the same character, team, and subcolor (tint),
 * increment the tint of one of them.
 */
void gm_801B0348(StartMeleeData* arg0)
{
    int i;
    int j;

    if (arg0->rules.is_teams != true) {
        return;
    }

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            if (i == j) {
                continue;
            }
            if (arg0->players[i].team == arg0->players[j].team &&
                arg0->players[i].c_kind == arg0->players[j].c_kind &&
                arg0->players[i].sub_color == arg0->players[j].sub_color)
            {
                arg0->players[j].sub_color++;
            }
        }
    }
}

static inline void player_standings_inline(StartMeleeData* arg0,
                                           MatchEnd* arg1, int i,
                                           u32 is_big_loser, int var_r7)
{
    if (is_big_loser == 0 && var_r7 > 0) {
        s8 var_r6 = arg1->player_standings[i].character_kind;
        if (var_r6 == 0x12 || var_r6 == 0x13) {
            if (arg1->player_standings[i].character_id == 7) {
                var_r6 = 0x13;
            } else {
                var_r6 = 0x12;
            }
        }
        arg0->players[i].c_kind = var_r6;
        arg0->players[i].stocks = 1;
        arg0->players[i].x12 = 0x12C;
    } else {
        arg0->players[i].slot_type = Gm_PKind_NA;
    }
}

static inline int gm_801B0474_inline(MatchEnd* arg1, int i)
{
    if (arg1->x5 == 1) {
        if (arg1->result == OUTCOME_TIMEOUT) {
            return arg1->player_standings[i].stocks;
        } else {
            u8 var_r7 = arg1->player_standings[i].stocks;
            if (arg1->player_standings[i].x28 < arg1->frame_count ||
                var_r7 != 0)
            {
                return var_r7;
            }
        }
    }
    return 1;
}

void gm_801B0474(StartMeleeData* arg0, MatchEnd* arg1)
{
    int var_r7;
    int i;

    arg0->rules.x0_0 = 1;
    arg0->rules.x0_6 = false;
    arg0->rules.x2_5 = false;

    for (i = 0; i < 6; i++) {
        if (arg0->players[i].slot_type != Gm_PKind_NA) {
            var_r7 = gm_801B0474_inline(arg1, i);
            if (arg1->is_teams == 1) {
                player_standings_inline(
                    arg0, arg1, i,
                    arg1->team_standings[arg1->player_standings[i].team]
                        .is_big_loser,
                    var_r7);
            } else {
                player_standings_inline(arg0, arg1, i,
                                        arg1->player_standings[i].is_big_loser,
                                        var_r7);
            }
        }
    }
}

void gm_801B05F4(PlayerInitData* arg0, int arg1)
{
    arg0->slot = arg1 + 1;
    if (arg1 == 2) {
        arg1 = 3;
    } else if (arg1 == 3) {
        arg1 = 2;
    }
    arg0->team = arg1;
}

void gm_801B0620(PlayerInitData* arg0, u8 c_kind, u8 arg2, u8 arg3, u8 arg4)
{
    arg0->slot_type = Gm_PKind_Human;
    arg0->c_kind = c_kind;
    arg0->color = arg2;
    arg0->stocks = arg3;
    gm_801B05F4(arg0, arg4);
}

void gm_801B0664(PlayerInitData* arg0, u8 c_kind, u8 arg2, u8 arg3, u8 arg4)
{
    arg0->slot_type = Gm_PKind_Cpu;
    arg0->c_kind = c_kind;
    arg0->color = arg2;
    arg0->stocks = arg3;
    gm_801B05F4(arg0, arg4);
    arg0->team = 4;
}

void gm_801B06B0(CSSData* css_data, u8 type, s8 c_kind, s8 stocks, s8 color,
                 u8 arg5, u8 level, u8 slot)
{
    gm_80167B50(&css_data->data);
    css_data->match_type = type;
    css_data->unk_0x0 = slot + 1;
    css_data->data.data.players[slot].c_kind = c_kind;
    css_data->data.data.players[slot].stocks = stocks;
    css_data->data.data.players[slot].color = color;
    css_data->data.data.players[slot].cpu_level = level;
    css_data->data.data.players[slot].xA = arg5;
    css_data->data.data.players[0].cpu_level = level;
    css_data->data.data.players[0].stocks = stocks;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void gm_801B0730(CSSData* css_data, s8* c_kind, u8* stocks, u8* color,
                 u8* nametag, u8* level)
{
    s32 slot;

    slot = css_data->unk_0x0 - 1;
    if (c_kind != NULL) {
        *c_kind = css_data->data.data.players[slot].c_kind;
    }
    if (stocks != NULL) {
        *stocks = css_data->data.data.players[slot].stocks;
    }
    if (color != NULL) {
        *color = css_data->data.data.players[slot].color;
    }
    if (level != NULL) {
        *level = css_data->data.data.players[slot].cpu_level;
    }
    if (nametag != NULL) {
        *nametag = css_data->data.data.players[slot].xA;
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

void gm_801B07B4(CSSData* css_data, s8 c_kind, s8 stocks, s8 color, u8 arg4,
                 u8 level, u8 arg6)
{
    s32 var_r0;

    if (arg6 == 0) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    css_data->data.data.players[var_r0].c_kind = c_kind;
    css_data->data.data.players[var_r0].stocks = stocks;
    css_data->data.data.players[var_r0].color = color;
    css_data->data.data.players[var_r0].cpu_level = level;
    css_data->data.data.players[var_r0].xA = arg4;
}

void gm_801B07E8(CSSData* css_data, s8* c_kind, s8* stocks, s8* color,
                 s8* arg4, u8* level)
{
    s32 slot;

    if ((css_data->unk_0x0 - 1) == 0) {
        slot = 1;
    } else {
        slot = 0;
    }
    if (c_kind != NULL) {
        *c_kind = css_data->data.data.players[slot].c_kind;
    }
    if (stocks != NULL) {
        *stocks = css_data->data.data.players[slot].stocks;
    }
    if (color != NULL) {
        *color = css_data->data.data.players[slot].color;
    }
    if (level != NULL) {
        *level = css_data->data.data.players[slot].cpu_level;
    }
    if (arg4 != NULL) {
        *arg4 = css_data->data.data.players[slot].xA;
    }
}
