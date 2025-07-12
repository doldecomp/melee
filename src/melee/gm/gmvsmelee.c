#include "gm/forward.h"
#include "mn/forward.h"
#include "gm/gmvsmelee.static.h"
#include "gmvsmelee.h"
#include "gm/gm_1B03.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcardgame.h"
#include "lb/lbcardnew.h"
#include "lb/lbtime.h"

#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbdvd.h>

/* 4D6730 */ extern u8 gm_804D6730[6];

VsModeData* gm_801A5244(void)
{
    return &gmMainLib_804D3EE0->unk_590;
}

u8 *gm_801A5250(void)
{
    return gm_804D6730;
}

void gm_801A5258(u8 *n_ko, MatchEnd* match_end)
{
    s32 i;
    for (i = 0; i < 6; i++) {
        if (match_end->player_standings[i].slot_type == 0) {
            n_ko[i] = lbTime_8000AF74((u32)n_ko[i], match_end->player_standings[i].x20);
        }
    }
}

bool gm_801A52D0(MatchEnd* end_info)
{
    s32 i;
    for (i = 0; i < 6; i++) {
        if (end_info->player_standings[i].slot_type == 0) {
            return true;
        }
    }
    return false;
}

s32 gm_801A5360(MatchEnd* match_end)
{
    s32 i;
    u8 player;
    s32 loser;
    u32 losers[6];

    if (match_end->is_teams == 1) {
        for (i = 0; i < 6; i++) {
            losers[i] =
                match_end->player_standings[i].is_small_loser +
                (match_end->team_standings[match_end->player_standings[i].team].is_small_loser << 8);
        }
    } else {
        for (i = 0; i < 6; i++) {
            losers[i] = match_end->player_standings[i].is_small_loser;
        }
    }

    for (i = 0; i < 6; i++) {
        if ((match_end->player_standings[i].slot_type == 0) && (losers[i] < 0xFFFF)) {
            loser = losers[i];
            player = i;
        }
    }

    if (loser != 0xFFFF) {
        return player;
    }
    __assert("gmvsmelee.c", 0xB2U, "0");
    return 0;
}

void gm_801A5598_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_590);
    gmMainLib_8015CDEC();
}

void gm_801A55C4(void)
{
    memzero(&gm_804D6730, 6);
}

void gm_801A55EC_OnLoad(void)
{
    memzero(&gm_804D6730, 6);
}


void gm_801A5614_OnUnload(void) {}

void gm_801A5618(MinorScene* minor_data, VsModeData* vs_data, int match_type)
{
    CSSData* css_data = gm_801A427C(minor_data);
    css_data->match_type = match_type;
    css_data->ko_star_counts = gm_804D6730;
    css_data->data = *vs_data;
    lbDvd_800174BC();
}

void gm_801A5680(MinorScene* minor_data, VsModeData* vs_data)
{
    CSSData* css_data;
    u64 mask;
    s32 i;

    css_data = gm_801A4284(minor_data);
    if (css_data->pending_scene_change == 2) {
        gm_801A42F8(1); // returns to CSS
        return;
    }
    *vs_data = css_data->data;

    mask = 0;
    for (i = 0; i < 6; i++) {
        mask |= lbAudioAx_80026E84((u32)css_data->data.data.players[i].x0);
    }
    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(4, mask);
    lbAudioAx_80027168();
}

void gm_801A5754(MinorScene* minor_data, VsModeData* vs_data)
{
    SSSData* sss_data = gm_801A427C(minor_data);
    sss_data->data = *vs_data;
    gm_80167FC4(sss_data);
}

void gm_801A57A8(MinorScene* minor_data, VsModeData* vs_data, s32 id)
{
    SSSData* sss_data;

    sss_data = gm_801A4284(minor_data);
    if (sss_data->start_game != 0) {
        *vs_data = sss_data->data;
        lbAudioAx_80026F2C(0x18);
        lbAudioAx_8002702C(8, lbAudioAx_80026EBC((u16)vs_data->data.rules.xE));
        lbAudioAx_80027168();
    }
    else {
        gm_SetScenePendingMinor(id);
    }
}

void gm_801A583C(MinorScene* minor_data, VsModeData* vs_data,
                 void (*callback)(StartMeleeData*, StartMeleeData*),
                 void (*callback2)(PlayerInitData*, PlayerInitData*))
{
    StartMeleeData* match_start_data;
    s32 i;

    match_start_data = gm_801A427C(minor_data);
    gm_80167BC8(vs_data);
    match_start_data->rules = vs_data->data.rules;

    if (match_start_data->rules.x0_0 == 1) {
        match_start_data->rules.x2_0 = 1;
    }
    match_start_data->rules.x4_1 = 1;

    if (callback != NULL) {
        callback(match_start_data,&vs_data->data);
    }

    for (i = 0; i < 6; ++i) {
        match_start_data->players[i] = vs_data->data.players[i];
    }

    if (callback2 != NULL) {
        for (i = 0; i < 6; ++i) {
            callback2(&match_start_data->players[i],&vs_data->data.players[i]);
        }
    }

    gm_801B0348(match_start_data);
    gm_8016F088(match_start_data);
    gm_80168FC4();
}

void gm_801A5AF0(MinorScene* minor_data, u32 id, u32 id2)
{
    MatchExitInfo* match_exit_info;
    int i;
    bool active_player;

    match_exit_info = gm_801A4284(minor_data);

    for (i = 0; i < 6; i++) {
        if (match_exit_info->match_end.player_standings[i].slot_type == 0) {
            gm_80162574(match_exit_info->match_end.player_standings[i].character_kind, match_exit_info->match_end.result);
        }
    }

    for (i = 0; i < 6; i++) {
        if (match_exit_info->match_end.player_standings[i].slot_type == 0) {
            active_player = true;
            break;
        }
        else {
            active_player = false;
        }
    }

    if (active_player != false) {
        gm_8016260C(match_exit_info->match_end.x5, match_exit_info->match_end.result);
        gm_801628C4((u32)match_exit_info->match_end.frame_count / 60, gm_80162800(&match_exit_info->match_end));
    }

    if (gm_80167140(&match_exit_info->match_end) == 0) {
        gm_SetScenePendingMinor(id);
    }
    else {
        gm_SetScenePendingMinor(id2);
    }
}

void gm_801A5C3C(MinorScene* minor_data, VsModeData* vs_data,
                 void (*callback)(StartMeleeData*, StartMeleeData*),
                 void (*callback2)(PlayerInitData*, PlayerInitData*))
{
    StartMeleeData* match_start_data;
    s32 i;

    match_start_data = gm_801A427C(minor_data);
    match_start_data->rules = vs_data->data.rules;

    if (callback != NULL) {
        callback(match_start_data,&vs_data->data);
    }

    for (i = 0; i < 6; ++i) {
        match_start_data->players[i] = vs_data->data.players[i];
    }

    if (callback2 != NULL) {
        for (i = 0; i < 6; ++i) {
            callback2(&match_start_data->players[i],&vs_data->data.players[i]);
        }
    }
    gm_801B0348(match_start_data);
    gm_8016F088(match_start_data);
    gm_801B0474(match_start_data, &gm_80479D98.match_end);
}

void gm_801A5EC8(MinorScene* minor_data)
{
    MatchExitInfo* exit_info;

    exit_info = gm_801A4284(minor_data);
    gm_80166CCC(&gm_80479D98.match_end, &exit_info->match_end);
}

void gm_801A5F00(MinorScene* minor_data)
{
    MatchEnd* exit_info = gm_801A427C(minor_data);
    gm_80177724(exit_info);
    gm_80479D98.match_end = *exit_info;
}

void gm_801A5F64(MinorScene* minor_data, VsModeData* vs_data, u8 next_scene)
{
    s32 i;
    s32 idx;
    s32 unk;
    bool unk_bool;
    bool is_active;
    bool result;
    MatchEnd* match_end;

    match_end = &gm_80479D98.match_end;
    result = gm_801743A4(match_end->result);
    if (!result) {
        gm_80168638(match_end);
        gm_80168710(match_end, vs_data);
    }

    for (i = 0; i < 6; i++) {
        if (match_end->player_standings[i].slot_type == 0) {
            // TODO :: not sure how to match this, maybe gm_804D6730 is the wrong type?
            *gm_804D6730 = lbTime_8000AF74(*gm_804D6730, match_end->player_standings[i].x20);
        }
    }

    for (i = 0; i < 6; i++) {
        if (match_end->player_standings[i].slot_type == 0) {
            is_active = true;
            break;
        }
    }

    if (is_active) {
        gm_801688AC(match_end);
        gm_8016247C();
        if (minor_data->info.class_id != 0xFF) {
            gm_8016279C();
            unk_bool = false;
            idx = gm_801A5360(match_end);
            unk = gm_80172DD4(gmMainLib_8015ED98());
            if (unk != 0x21) {
                gm_801736E8(match_end->player_standings[idx].character_kind,
                            (match_end->player_standings[idx].x3),
                            idx,
                            match_end->player_standings[idx].x4,
                            unk,
                            0);
                gm_SetScenePendingMinor(0x80);
                unk_bool = true;
            }
            else if (gm_80172D78() != 0x21) {
                gm_801736E8(match_end->player_standings[idx].character_kind,
                            (match_end->player_standings[idx].x3),
                            idx,
                            match_end->player_standings[idx].x4,
                            gm_80172D78(),
                            0);
                gm_SetScenePendingMinor(0x80);
                unk_bool = true;
            }
            else if (gm_80172E74() != 0x21) {
                gm_801736E8(match_end->player_standings[idx].character_kind,
                            (match_end->player_standings[idx].x3),
                            idx,
                            match_end->player_standings[idx].x4,
                            gm_80172E74(),
                            0);
                gm_SetScenePendingMinor(0x80);
                unk_bool = true;
            }
        }
        if (gm_80172F00(gmMainLib_8015EDB0()->x0) != 0x148) {
            gm_80164504();
        }
        gm_80173DE4(&gm_80479D98.match_end);
        gm_80172898(1);
        gm_80173EEC();
        if ((unk_bool == 0) && (gm_801721EC() != false)) {
            gm_801736E8(0x21U, 0, idx, 0x78U, unk, 0);
            gm_SetScenePendingMinor(0xC0);
            unk_bool = 1;
        }
        if (unk_bool != false) {
            lb_8001C550();
            lb_8001D164(0);
            lb_8001CE00();
            return;
        }
    }

    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
    gm_SetScenePendingMinor(next_scene);
}
