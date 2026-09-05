#include "gm_1B03.h"

#include <dolphin/types.h>
#include "types.h"

#include <melee/mn/forward.h>
#include <melee/pl/forward.h>

#include "gm_unsplit.h"
#include "types.h"
#include <melee/mn/types.h>

/**
 * Update character tints
 *
 * If any two players are the same character, team, and subcolor (tint),
 * increment the tint of one of them.
 */
void gm_SetupSubColors(StartMeleeData* start)
{
    ssize_t i;
    ssize_t j;

    if (start->rules.is_teams != true) {
        return;
    }

    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        for (j = 0; j < GM_MAX_PLAYERS; j++) {
            if (i == j) {
                continue;
            }
            if (start->players[i].team == start->players[j].team &&
                start->players[i].ckind == start->players[j].ckind &&
                start->players[i].sub_color == start->players[j].sub_color)
            {
                start->players[j].sub_color++;
            }
        }
    }
}

static inline void player_standings_inline(StartMeleeData* arg0,
                                           MatchEnd* arg1, int i,
                                           u32 is_big_loser, int var_r7)
{
    if (is_big_loser == 0 && var_r7 > 0) {
        s8 var_r6 = arg1->player_standings[i].ckind;
        if (var_r6 == 0x12 || var_r6 == 0x13) {
            if (arg1->player_standings[i].ftkind == 7) {
                var_r6 = 0x13;
            } else {
                var_r6 = 0x12;
            }
        }
        arg0->players[i].ckind = var_r6;
        arg0->players[i].stocks = 1;
        arg0->players[i].x12 = 0x12C;
    } else {
        arg0->players[i].slot_type = Gm_PKind_NA;
    }
}

static inline int gm_801B0474_inline(MatchEnd* arg1, int i)
{
    if (arg1->match_kind == 1) {
        if (arg1->outcome == OUTCOME_TIMEOUT) {
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

void gm_SetupSuddenDeath(StartMeleeData* start, MatchEnd* end)
{
    int var_r7;
    int i;

    start->rules.match_kind = MatchKind_Stock;
    start->rules.x0_6 = false;
    start->rules.x2_5 = false;

    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        if (start->players[i].slot_type != Gm_PKind_NA) {
            var_r7 = gm_801B0474_inline(end, i);
            if (end->is_teams == 1) {
                player_standings_inline(
                    start, end, i,
                    end->team_standings[end->player_standings[i].team]
                        .is_big_loser,
                    var_r7);
            } else {
                player_standings_inline(start, end, i,
                                        end->player_standings[i].is_big_loser,
                                        var_r7);
            }
        }
    }
}

void gm_801B05F4(PlayerInitData* player, int slot)
{
    player->slot = slot + 1;
    if (slot == 2) {
        slot = 3;
    } else if (slot == 3) {
        slot = 2;
    }
    player->team = slot;
}

void gm_SetupHumanPlayer(PlayerInitData* player, u8 ckind, u8 color, u8 stocks,
                         u8 slot)
{
    player->slot_type = Gm_PKind_Human;
    player->ckind = ckind;
    player->color = color;
    player->stocks = stocks;
    gm_801B05F4(player, slot);
}

void gm_SetupCpuPlayer(PlayerInitData* arg0, u8 ckind, u8 color, u8 stocks,
                       u8 slot)
{
    arg0->slot_type = Gm_PKind_Cpu;
    arg0->ckind = ckind;
    arg0->color = color;
    arg0->stocks = stocks;
    gm_801B05F4(arg0, slot);
    arg0->team = 4;
}

void gm_801B06B0(CSSData* css_data, u8 type, s8 c_kind, s8 stocks, s8 color,
                 u8 arg5, u8 level, u8 slot)
{
    gm_InitVsMode(&css_data->vs);
    css_data->match_type = type;
    css_data->unk_0x0 = slot + 1;
    css_data->vs.start.players[slot].ckind = c_kind;
    css_data->vs.start.players[slot].stocks = stocks;
    css_data->vs.start.players[slot].color = color;
    css_data->vs.start.players[slot].cpu_level = level;
    css_data->vs.start.players[slot].nametag = arg5;
    css_data->vs.start.players[0].cpu_level = level;
    css_data->vs.start.players[0].stocks = stocks;
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
        *c_kind = css_data->vs.start.players[slot].ckind;
    }
    if (stocks != NULL) {
        *stocks = css_data->vs.start.players[slot].stocks;
    }
    if (color != NULL) {
        *color = css_data->vs.start.players[slot].color;
    }
    if (level != NULL) {
        *level = css_data->vs.start.players[slot].cpu_level;
    }
    if (nametag != NULL) {
        *nametag = css_data->vs.start.players[slot].nametag;
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
    css_data->vs.start.players[var_r0].ckind = c_kind;
    css_data->vs.start.players[var_r0].stocks = stocks;
    css_data->vs.start.players[var_r0].color = color;
    css_data->vs.start.players[var_r0].cpu_level = level;
    css_data->vs.start.players[var_r0].nametag = arg4;
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
        *c_kind = css_data->vs.start.players[slot].ckind;
    }
    if (stocks != NULL) {
        *stocks = css_data->vs.start.players[slot].stocks;
    }
    if (color != NULL) {
        *color = css_data->vs.start.players[slot].color;
    }
    if (level != NULL) {
        *level = css_data->vs.start.players[slot].cpu_level;
    }
    if (arg4 != NULL) {
        *arg4 = css_data->vs.start.players[slot].nametag;
    }
}
