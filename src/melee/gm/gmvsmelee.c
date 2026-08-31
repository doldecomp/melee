#include "gmvsmelee.h"

#include "gm_1A3F.h"
#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "gmresult.h"
#include "gmresultplayer.h"
#include "types.h"

#include <platform.h>

#include "gm/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbcardnew.h"
#include "lb/lbdvd.h"
#include "lb/lbtime.h"
#include "mn/types.h"

#include "pl/forward.h"

/* 1A5360 */ static u8 gm_801A5360(MatchEnd*);
/* 4807B0 */ CSSData gmVsMelee_CssData;
/* 480668 */ SSSData gmVsMelee_SssData;
/* 480530 */ StartMeleeData gmVsMelee_StartData;
/* 479D98 */ MatchExitInfo gm_80479D98;
/* 47E2A4 */ MatchExitInfo gm_8047E2A4;
/* 47C020 */ ResultsMatchInfo gm_8047C020;
/* 4D6730 */ static u8 ko_counts[GM_MAX_PLAYERS];

VsModeData* gm_801A5244(void)
{
    return &gmMainLib_804D3EE0->vs_melee;
}

u8* gmVsMelee_GetKOCounts(void)
{
    return ko_counts;
}

void gm_801A5258(u8* ko_counts, MatchEnd* end)
{
    ssize_t i;
    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        if (end->player_standings[i].slot_type == Gm_PKind_Human) {
            ko_counts[i] =
                lbTime_8000AF74(ko_counts[i], end->player_standings[i].x20);
        }
    }
}

bool gm_801A52D0(MatchEnd* end)
{
    ssize_t i;
    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        if (end->player_standings[i].slot_type == Gm_PKind_Human) {
            return true;
        }
    }
    return false;
}

u8 gm_801A5360(MatchEnd* end)
{
    s32 loser = U16_MAX;
    ssize_t i;
    ssize_t player;
    s32 losers[GM_MAX_PLAYERS];

    if (end->is_teams == 1) {
        for (i = 0; i < GM_MAX_PLAYERS; i++) {
            losers[i] = end->player_standings[i].is_small_loser +
                        (end->team_standings[end->player_standings[i].team]
                             .is_small_loser
                         << 8);
        }
    } else {
        for (i = 0; i < GM_MAX_PLAYERS; i++) {
            losers[i] = end->player_standings[i].is_small_loser;
        }
    }

    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        if (end->player_standings[i].slot_type == Gm_PKind_Human &&
            losers[i] < loser)
        {
            loser = losers[i];
            player = i;
        }
    }

    if (loser != U16_MAX) {
        return player;
    }

    HSD_ASSERT(178, 0);
    return 0;
}

void gm_Mode_Vs_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->vs_melee);
    gmMainLib_8015CDEC();
}

void gmVsMelee_ResetKOCounts(void)
{
    memzero(&ko_counts, sizeof(ko_counts));
}

void gm_Mode_Vs_OnLoad(void)
{
    gmVsMelee_ResetKOCounts();
}

void gm_Mode_Vs_OnUnload(void) {}

void gmVsMelee_EnterCss(GameModeState* state, VsModeData* vs,
                        MatchKind match_type)
{
    CSSData* css = gm_GetGameModeStateEnterData(state);
    css->match_type = match_type;
    css->ko_counts = ko_counts;
    css->vs = *vs;
    lbDvd_800174BC();
}

void gmVsMelee_ExitCss(GameModeState* state, VsModeData* vs)
{
    CSSData* css = gm_GetGameModeStateExitData(state);
    if (css->pending_scene_change == 2) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return;
    }

    *vs = css->vs;
    {
        u64 mask = 0;
        ssize_t i;
        for (i = 0; i < GM_MAX_PLAYERS; i++) {
            mask |= lbAudioAx_80026E84(css->vs.start.players[i].ckind);
        }
        lbAudioAx_80026F2C(20);
        lbAudioAx_8002702C(4, mask);
        lbAudioAx_80027168();
    }
}

void gmVsMelee_EnterSss(GameModeState* state, VsModeData* vs)
{
    SSSData* sss = gm_GetGameModeStateEnterData(state);
    sss->vs = *vs;
    gm_80167FC4(sss);
}

void gmVsMelee_ExitSss(GameModeState* state, VsModeData* vs, u8 state_id)
{
    SSSData* sss = gm_GetGameModeStateExitData(state);
    if (sss->start_game) {
        *vs = sss->vs;
        lbAudioAx_80026F2C(24);
        lbAudioAx_8002702C(8, lbAudioAx_80026EBC(vs->start.rules.stkind));
        lbAudioAx_80027168();
    } else {
        gm_SetNextGameModeStateId(state_id);
    }
}

void gm_801A583C(GameModeState* state, VsModeData* vs,
                 gm_StartMeleeCallback start_cb,
                 gm_PlayerInitCallback player_cb)
{
    StartMeleeData* start = gm_GetGameModeStateEnterData(state);
    ssize_t i;

    gm_80167BC8(vs);
    start->rules = vs->start.rules;

    if (start->rules.match_kind == MatchKind_Stock) {
        start->rules.x2_0 = true;
    }
    start->rules.x4_1 = true;

    if (start_cb != NULL) {
        start_cb(start, &vs->start);
    }

    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        start->players[i] = vs->start.players[i];
    }

    if (player_cb != NULL) {
        for (i = 0; i < GM_MAX_PLAYERS; i++) {
            player_cb(&start->players[i], &vs->start.players[i]);
        }
    }

    gm_DetermineSubColors(start);
    gm_8016F088(start);
    gm_80168FC4();
}

/// @param id0 Next state id if one or zero winners
/// @param id1 Next state id if multiple winners
void gm_801A5AF0(GameModeState* state, u8 id0, u8 id1)
{
    MatchExitInfo* exit = gm_GetGameModeStateExitData(state);
    ssize_t i;

    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        if (exit->match_end.player_standings[i].slot_type == Gm_PKind_Human) {
            gm_80162574(exit->match_end.player_standings[i].ckind,
                        exit->match_end.result);
        }
    }

    if (gm_801A52D0(&exit->match_end)) {
        gm_8016260C(exit->match_end.match_kind, exit->match_end.result);
        gm_801628C4(exit->match_end.frame_count / GM_FPS,
                    gm_80162800(&exit->match_end));
    }

    if (!gm_MatchHasMultipleWinners(&exit->match_end)) {
        gm_SetNextGameModeStateId(id0);
    } else {
        gm_SetNextGameModeStateId(id1);
    }
}

/// SuddenDeath_Enter ??
void gm_801A5C3C(GameModeState* state, VsModeData* vs,
                 gm_StartMeleeCallback start_cb,
                 gm_PlayerInitCallback player_cb)
{
    StartMeleeData* start;
    s32 i;

    start = gm_GetGameModeStateEnterData(state);
    start->rules = vs->start.rules;

    if (start_cb != NULL) {
        start_cb(start, &vs->start);
    }

    for (i = 0; i < GM_MAX_PLAYERS; i++) {
        start->players[i] = vs->start.players[i];
    }

    if (player_cb != NULL) {
        for (i = 0; i < 6; ++i) {
            player_cb(&start->players[i], &vs->start.players[i]);
        }
    }
    gm_DetermineSubColors(start);
    gm_8016F088(start);
    gm_801B0474(start, &gm_80479D98.match_end);
}

/// SuddenDeath_Exit ??
void gm_801A5EC8(GameModeState* state)
{
    MatchExitInfo* exit_data = gm_GetGameModeStateExitData(state);
    gm_80166CCC(&gm_80479D98.match_end, &exit_data->match_end);
}

/// Results_Enter ??
void gm_801A5F00(GameModeState* state)
{
    ResultsMatchInfo* enter_data = gm_GetGameModeStateEnterData(state);
    gm_80177724(enter_data);
    enter_data->match_end = gm_80479D98.match_end;
}

/// Results_Exit ??
void gm_801A5F64(GameModeState* state, VsModeData* vs, u8 state_id)
{
    MatchEnd* match_end;
    u8* ko = ko_counts;
    bool unk_bool;
    int idx;
    u8 unk;
    u16 foo;

    match_end = &gm_80479D98.match_end;
    if (!gm_801743A4(match_end->result)) {
        gm_80168638(match_end);
        gm_80168710(match_end, vs);
    }

    gm_801A5258(ko, match_end);

    if (gm_801A52D0(match_end)) {
        gm_8016247C(gm_801688AC(match_end));
        if (state[1].id != (u8) -1) {
            gm_GetVsPlayMatchTotal();
            unk_bool = false;
            idx = gm_801A5360(match_end);
            unk = gm_80172DD4(gmMainLib_8015ED98()->x0);
            if (unk != CHKIND_NONE) {
                gm_801736E8(match_end->player_standings[idx].ckind,
                            (match_end->player_standings[idx].x3), idx,
                            match_end->player_standings[idx].x4, unk, 0);
                gm_SetNextGameModeStateId(0x80);
                unk_bool = true;
            } else if ((unk = gm_80172D78()) != CHKIND_NONE) {
                gm_801736E8(match_end->player_standings[idx].ckind,
                            (match_end->player_standings[idx].x3), idx,
                            match_end->player_standings[idx].x4, unk, 0);
                gm_SetNextGameModeStateId(0x80);
                unk_bool = true;
            } else if ((unk = gm_80172E74()) != CHKIND_NONE) {
                gm_801736E8(match_end->player_standings[idx].ckind,
                            (match_end->player_standings[idx].x3), idx,
                            match_end->player_standings[idx].x4, unk, 0);
                gm_SetNextGameModeStateId(0x80);
                unk_bool = true;
            }
            foo = gm_80172F00(gmMainLib_8015EDB0()->x0);
            if (foo != 0x148) {
                gm_80164504(foo);
            }
            gm_80173DE4(&gm_80479D98.match_end);
            gm_80172898(1);
            gm_80173EEC();
            if (!unk_bool && gm_801721EC()) {
                gm_801736E8(CHKIND_NONE, 0, idx, 120, unk, 0);
                gm_SetNextGameModeStateId(0xC0);
                unk_bool = true;
            }
            if (unk_bool) {
                lb_8001C550();
                lb_8001D164(0);
                lb_8001CE00();
                return;
            }
        }
    }

    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
    gm_SetNextGameModeStateId(state_id);
}
