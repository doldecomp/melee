#include "gm/forward.h"
#include "mn/forward.h"
#include "gm/gmvsmelee.static.h"
#include "gmvsmelee.h"
#include "lb/lb_00B0.h"
#include "lb/lbtime.h"

#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lbdvd.h>

/* 4D6730 */ extern u8 gm_804D6730;

VsModeData* gm_801A5244(void)
{
    return &gmMainLib_804D3EE0->unk_590;
}

UNK_T gm_801A5250(void)
{
    return &gm_804D6730;
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


/// #gm_801A5360

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
    css_data->ko_star_counts = &gm_804D6730;
    css_data->data = *vs_data;
    lbDvd_800174BC();
}

/// #gm_801A5680

void gm_801A5754(MinorScene* minor_data, VsModeData* vs_data)
{
    SSSData* sss_data = gm_801A427C(minor_data);
    sss_data->data = *vs_data;
    gm_80167FC4();
}

/// #gm_801A57A8

/// #gm_801A583C

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
        gm_801628C4((u32)match_exit_info->match_end.frame_count / 60, gm_80162800(match_exit_info->match_end.xC));
    }

    if (gm_80167140(&match_exit_info->match_end) == 0) {
        gm_SetScenePendingMinor(id);
    }
    else {
        gm_SetScenePendingMinor(id2);
    }
}

/// #gm_801A5C3C

void gm_801A5EC8(MinorScene* arg0)
{
    MatchExitInfo* exit_info;

    exit_info = gm_801A4284(arg0);
    gm_80166CCC(&gm_80479D98.match_end, &exit_info->match_end);
}

void gm_801A5F00(MinorScene* minor_data)
{
    MatchEnd* exit_info = gm_801A427C(minor_data);
    gm_80177724(exit_info);
    *exit_info = gm_80479D98.match_end;
}

/// #gm_801A5F64
