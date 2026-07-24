#include "gm_17C9.h"

#include "gm_17C0.h"
#include "gm_17E4.h"
#include "gm_17EB.h"
#include "gmregclear.h"
#include "platform.h"

#include "baselib/forward.h"

#include "dolphin/pad.h"

#include "gm/forward.h"

#include <math_ppc.h>
#include <dolphin/gx.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/util.h>
#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_16AE.h>
#include <melee/gm/gm_16F1.h>
#include <melee/gm/gm_17AD.h>
#include <melee/gm/gm_17BA.h>
#include <melee/gm/gm_1832.h>
#include <melee/gm/gm_19EF.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gm_1A45.h>
#include <melee/gm/gm_1A7A.h>
#include <melee/gm/gm_1ADD.h>
#include <melee/gm/gm_1AED.h>
#include <melee/gm/gm_1B03.h>
#include <melee/gm/gm_1BA8.h>
#include <melee/gm/gm_1BFA.h>
#include <melee/gm/gmadventure.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmregcommon.h>
#include <melee/gm/gmtoulib.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/gr/grpushon.h>
#include <melee/gr/stage.h>
#include <melee/if/ifcoget.h>
#include <melee/if/ifnametag.h>
#include <melee/if/ifstatus.h>
#include <melee/if/ifstock.h>
#include <melee/if/iftime.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbspdisplay.h>
#include <melee/lb/lbtime.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <melee/ty/toy.h>

typedef struct lbl_804706D8_t {
    s16 x0;
    u8 x2;
    u8 x3;
} lbl_804706D8_t;

lbl_804706D8_t lbl_804706D8[12];

typedef struct RegClearCharEntry {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
} RegClearCharEntry;

void gm_8017C984(UNK_T arg0)
{
    memzero(arg0, 0x74);
}

extern u8 lbl_803B7C08[][5];

void gm_8017C9A8(DebugGameOverData* arg0, Unk1PData* arg1, u8 arg2)
{
    PAD_STACK(8);
    arg0->x0 = arg1->xC.x18;
    arg0->x8 = arg2;
    arg0->ckind = arg1->ckind;
    arg0->slot = arg1->slot;
    arg0->x15 = arg1->x4;
    arg0->x18 = gm_801623D8();
    arg0->x16 = lbl_803B7C08[arg2][arg1->cpu_level];
}

void gm_8017CA38(DebugGameOverData* arg0, Unk1PData* arg1, gmm_x0_528_t* arg2,
                 u8 arg3)
{
    u8 temp_r31;

    arg1->xC.x14 = arg0->x18;
    gm_801623FC(arg1->xC.x14);
    if (arg0->xC == 0) {
        temp_r31 = gm_80173224(arg3, 0);
        switch (gm_GetCurrentGameMode()) {
        case GM_CLASSIC:
            fn_80162BFC(arg1->ckind, arg0->x4);
            break;
        case GM_ADVENTURE:
            fn_80162DF8(arg1->ckind, arg0->x4);
            break;
        case GM_ALLSTAR:
            fn_80162FF4(arg1->ckind, arg0->x4);
            break;
        }
        Ground_801C5A60();
        gm_8017390C(fn_8017DF90(), 0);
        gm_80173EEC();
        gm_80172898(0x40);
        if (temp_r31 == CHKIND_NONE) {
            if (gm_80173754(1, arg1->slot) == 0) {
                gm_ChangeGameModeAfterCurrentScene(GM_MENU);
            }
        } else {
            gm_801736E8(arg1->ckind, arg1->color, arg1->slot, arg1->x4,
                        temp_r31, 1U);
            gm_ChangeGameModeAfterCurrentScene(GM_CHALLENGER_APPROACH);
        }
    } else {
        arg1->xC.x18 = lbTime_8000AEC8((u32) arg0->x4, 1U);
        arg1->stocks = arg2->stocks;
        arg1->xC.xD = lbTime_8000AF74((u32) arg1->xC.xD, 1);
        gm_SetPendingSceneIndex(arg1->x7);
    }
}

void gm_8017CBAC(UnkAdventureData* arg0, gmm_x0_528_t* arg1, u8 arg2)
{
    s32 temp_r3_2;
    u8 temp_r31;
    u8* temp_r3;

    temp_r31 = gm_CKindToSelKind(arg0->x0.ckind);
    Ground_801C5A60();
    switch (arg2) {
    case 21:
        gmMainLib_8015D134(temp_r31);
        fn_80162BFC(arg0->x0.ckind, arg0->x0.xC.x18);
        temp_r3 = gmMainLib_8015D194(temp_r31);
        if (*temp_r3 < arg0->x0.cpu_level) {
            *temp_r3 = arg0->x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D1AC(temp_r31);
        if ((arg0->x0.cpu_level == 4) &&
            ((temp_r3_2 == 0) || (arg1->stocks < temp_r3_2)))
        {
            gmMainLib_8015D1C8(temp_r31, arg1->stocks);
        }
        break;
    case 22:
        gmMainLib_8015D25C(temp_r31);
        fn_80162DF8(arg0->x0.ckind, arg0->x0.xC.x18);
        temp_r3 = gmMainLib_8015D2BC(temp_r31);
        if (*temp_r3 < arg0->x0.cpu_level) {
            *temp_r3 = arg0->x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D2D4(temp_r31);
        if ((arg0->x0.cpu_level == 4) &&
            ((temp_r3_2 == 0) || (arg1->stocks < temp_r3_2)))
        {
            gmMainLib_8015D2F0(temp_r31, arg1->stocks);
        }
        break;
    case 23:
        gmMainLib_8015D384(temp_r31);
        fn_80162FF4(arg0->x0.ckind, arg0->x0.xC.x18);
        if (!gm_80164430(0x1F)) {
            gm_80164504(0x1F);
        }
        temp_r3 = gmMainLib_8015D3E4(temp_r31);
        if (*temp_r3 < arg0->x0.cpu_level) {
            *temp_r3 = arg0->x0.cpu_level;
        }
        temp_r3_2 = gmMainLib_8015D3FC(temp_r31);
        if ((arg0->x0.cpu_level == 4) &&
            (temp_r3_2 == 0 || arg1->stocks < temp_r3_2))
        {
            gmMainLib_8015D418(temp_r31, arg1->stocks);
        }
        break;
    }
    lb_8001C550();
    lb_8001D164(0);
    lb_8001CE00();
    gm_SetPendingGameMode(arg2);
    gm_SetNewGameModePending();
}

u8 gm_8017CD94(UnkAdventureData* arg0, int arg1, int arg2, int arg3)
{
    u8 num_colors;
    u8 result;

    num_colors = gm_80169238(arg1);
    if (arg0->x54 != NULL) {
        result = arg0->x54(arg2, arg0->x0.cpu_level, arg3);
        if (num_colors != 0) {
            return result % num_colors;
        }
        return 0;
    }
    return 0;
}

static inline s32 gm_8017CE34_CountEnemies(s8* arg0)
{
    s32 count = 0;

    if ((s32) (u8) arg0[0] != 0x21) {
        count = 1;
    }
    {
        s8* p = &arg0[1];
        if ((s32) *p != 0x21) {
            count += 1;
        }
        if ((s32) p[1] != 0x21) {
            count += 1;
        }
    }
    return count;
}

static inline void gm_8017CE34_SetupColors(UnkAdventureData* arg1, s32 count,
                                           s8* arg2, u8* colors)
{
    s32 color_idx;

    {
        u8* out_color = colors;
        s8* kind_iter = arg2;
        for (color_idx = 0; color_idx < 3; color_idx++) {
            u8 kind = (u8) *kind_iter;
            u8 num_colors = gm_80169238(kind);
            u8 color_id;
            if (arg1->x54 != NULL) {
                u8 requested_color;
                requested_color =
                    arg1->x54((u8) count, arg1->x0.cpu_level, (u8) color_idx);
                if (num_colors != 0) {
                    color_id = requested_color % num_colors;
                } else {
                    color_id = 0;
                }
            } else {
                color_id = 0;
            }
            *out_color = color_id;
            out_color += 1;
            kind_iter += 1;
        }
    }
}

s32 gm_8017CE34(StartMeleeData* arg0, UnkAdventureData* arg1, s8* arg2,
                u8 arg3, u8 arg4, u8 arg5, s32 arg6, InternalStageId arg7,
                s32 count, s32 arg9)
{
    u8 colors[16];
    u8 enemy_level;
    s32 boss_count;
    u8 enemy_cpu_type;
    s32 player_idx;
    f32 attack_ratio;
    u8 player_stocks;
    u8 player_ckind;
    u8 flags;
    s8* enemy_kind;
    f32 defense_ratio;
    u8 enemy_ckind;
    s32 enemy_count;
    s32 enemy_idx;
    s32 sp8;
    u8* color_iter;
    f32 one;

    PAD_STACK(4);

    boss_count = 0;
    enemy_level = 0;
    enemy_cpu_type = 0;
    arg1->x0.xC.xC = 1;
    fn_8017E21C();
    fn_8016F030(arg0);
    one = lbl_804DA42C;
    arg0->rules.x30 = one;
    arg0->rules.x4_4 = 1;

    switch (arg9) {
    case 0:
        arg0->rules.xA = 0;
        break;
    case 1:
        arg0->rules.xA = 3;
        break;
    case 2:
        arg0->rules.xA = 2;
        break;
    }

    arg0->rules.x1_1 = 1;
    arg0->rules.x4_2 = 1;
    arg0->rules.x4_3 = 1;
    arg0->rules.x2_5 = 0;
    arg0->rules.x0_3 = arg1->x0.xB;

    if (arg6 != 0) {
        arg0->rules.x10 = (u32) arg6;
        arg0->rules.x0_6 = 1;
    } else {
        arg0->rules.x0_6 = 0;
    }

    arg0->rules.x18 = (u32) arg1->x0.xC.x18;
    arg0->rules.xE = (u16) arg7;
    arg0->rules.xB = arg1->x48((u8) count, arg1->x0.cpu_level);

    arg0->rules.x20 = (u64) -1;

    enemy_count = gm_8017CE34_CountEnemies(arg2);
    if (enemy_count == 0) {
        arg0->rules.x5_1 = 1;
    }
    if (arg1->x0.x8 & 1) {
        arg0->rules.x2_7 = 1;
    }
    if (arg1->x0.x8 & 0x20) {
        arg0->rules.x4_5 = 1;
    }
    if (arg1->x0.x8 & 0x80) {
        arg1->x0.xC.xC = 5;
        switch ((s32) arg1->x0.x9) {
        case 1:
            arg0->rules.on_pause_override = gm_80165290;
            arg0->rules.x9 = 1;
            arg0->rules.x3_1 = 0;
            arg0->players[0].xC_b1 = 0;
            break;
        case 2:
            arg0->rules.x9 = 3;
            arg0->rules.x44 = fn_8017C7EC;
            break;
        case 3:
            arg0->rules.x9 = 2;
            arg0->rules.x7 = 9;
            arg0->rules.x4_4 = 0;
            arg0->rules.x50 = (void (*)(u8)) fn_8017C7A0;
            arg0->rules.xD = 0x30;
            break;
        }
    }

    if ((arg1->x0.x8 & 0x80) != 0) {
        player_stocks = 1;
    } else {
        player_stocks = arg1->x0.stocks;
    }

    player_ckind = (u8) arg1->x0.ckind;
    if ((player_ckind == 0x12) && ((u8) arg1->x0.xC.x12 != 0)) {
        player_ckind = 0x13;
    } else if (((arg1->x0.x8 & 0x80) != 0) && ((u8) arg1->x0.x9 == 1) &&
               ((s8) player_ckind == 0xE))
    {
        player_ckind = 0x20;
    }

    gm_801B0620(arg0->players, player_ckind, arg1->x0.color, player_stocks,
                arg1->x0.slot);
    arg0->players[0].xA = arg1->x0.x4;
    arg0->players[0].spawn_dir = (s8) arg1->x0.xA;

    {
        u8 team_color;
        if (arg1->x58 != NULL) {
            team_color = arg1->x58((u8) count, arg1->x0.cpu_level, 0);
        } else {
            team_color = 0;
        }

        {
            player_idx =
                fn_8017DD7C(arg0->players, arg1->x0.xC.x24, team_color) + 1;
            arg0->rules.is_teams = 1;
        }
    }

    attack_ratio = arg1->x64((u8) count, arg1->x0.cpu_level);
    defense_ratio = arg1->x68((u8) count, arg1->x0.cpu_level);

    color_iter = colors;
    gm_8017CE34_SetupColors(arg1, count, arg2, color_iter);

    {
        s32 temp_r3_4 = arg1->x0.x8 & 8;
        if ((temp_r3_4 != 0) && ((u8) arg1->x0.xC.x11 == 0)) {
            s32 base_enemy_count;
            s32 event_enemy_count;
            s32 special_stage;
            s32 special_enemy_mode;
            u8 first_enemy;
            u32 stage_flags;

            base_enemy_count = gm_8017CE34_CountEnemies(arg2);
            arg1->x0.xC.xC = 3;
            event_enemy_count = base_enemy_count;
            special_stage = 0;
            special_enemy_mode = 0;
            sp8 = 0;
            if (arg1->x4C != NULL) {
                enemy_level = arg1->x4C((u8) count, arg1->x0.cpu_level, 0U);
            }

            first_enemy = (u8) arg2[0];
            if ((s8) first_enemy != 4) {
                if ((u8) (first_enemy - 0x1B) <= 1U) {
                    arg0->rules.x0_3 = 6;
                    event_enemy_count = 5;
                    colors[0] = 0;
                    special_stage = 1;
                    special_enemy_mode = 1;
                } else if (((s8) first_enemy == 0xD) &&
                           (((s32) arg2[1] != 0xD) || ((s32) arg2[2] != 0xD)))
                {
                    special_enemy_mode = 2;
                }
            }

            {
                s32 stage_id = Stage_8022519C(arg7);
                stage_flags = Ground_801C5AD0(stage_id);
            }

            {
                u8 player_ckind = (u8) arg1->x0.ckind;
                gm_8016A22C((s8) (u8) arg2[0], (s8) arg2[1], (s8) arg2[2],
                            colors[0], colors[1], (s32) colors[2],
                            special_stage, special_enemy_mode, sp8,
                            player_ckind, arg1->x0.color, (s32) enemy_level,
                            (s32) arg3, event_enemy_count, (s32) stage_flags,
                            (s32) arg5, (s32) arg4, attack_ratio,
                            defense_ratio);
            }
            gm_8016A21C(&arg0->rules);
            arg1->x0.xC.x11 = 0;
            if (arg1->x0.x8 & 4) {
                fn_8016A450();
            }
            if ((u8) special_enemy_mode == 1) {
                fn_8016A46C();
                arg0->players[0].xC_b5 = 1;
            }
        } else if (temp_r3_4 != 0) {
            gm_8016A21C(&arg0->rules);
            arg1->x0.xC.x11 = 0;
        }
    }

    gmRegSetupEnemyColorTable((s8) (u8) arg1->x0.ckind, arg1->x0.color, arg2,
                              colors);

    enemy_idx = 0;
    for (;;) {
        enemy_kind = &arg2[enemy_idx];
        if ((s32) (u8) enemy_kind[0] != 0x21) {
            if (arg1->x0.x8 & 8) {
                if (arg1->x4C != NULL) {
                    enemy_level =
                        arg1->x4C((u8) count, arg1->x0.cpu_level, 0U);
                }
                if (arg1->x50 != NULL) {
                    enemy_cpu_type =
                        arg1->x50((u8) count, arg1->x0.cpu_level, 0U);
                }
            } else {
                if (arg1->x4C != NULL) {
                    u8 selected_enemy_level =
                        arg1->x4C((u8) count, arg1->x0.cpu_level, enemy_idx);
                    enemy_level = selected_enemy_level;
                }
                if (arg1->x50 != NULL) {
                    enemy_cpu_type =
                        arg1->x50((u8) count, arg1->x0.cpu_level, enemy_idx);
                }
            }
            gm_8016795C(&arg0->players[player_idx]);
            arg0->players[player_idx].slot_type = 1;
            arg0->players[player_idx].c_kind = (s8) (u8) enemy_kind[0];
            arg0->players[player_idx].stocks = 1;
            arg0->players[player_idx].cpu_level = enemy_level;
            arg0->players[player_idx].xE = enemy_cpu_type;
            arg0->players[player_idx].x18 = attack_ratio;
            arg0->players[player_idx].x1C = defense_ratio;
            arg0->players[player_idx].color = *color_iter;
            if (arg1->x0.x8 & 2) {
                arg0->players[player_idx].x20 = 2.0f;
                arg0->players[player_idx].xB = 2;
            } else {
                arg0->players[player_idx].x20 = one;
                arg0->players[player_idx].xB = 0;
            }
            if (arg1->x0.x8 & 4) {
                arg0->players[player_idx].xC_b2 = 1;
                arg0->players[player_idx].xE = 0x1B;
            }
            if ((s32) arg0->players[player_idx].c_kind == 0x1D) {
                arg0->players[player_idx].xC_b1 = 0;
            }
            enemy_ckind = (u8) arg0->players[player_idx].c_kind;
            if (((s8) enemy_ckind == 0x1A) || ((s8) enemy_ckind == 0x1E)) {
                arg0->players[player_idx].xC_b7 = 1;
                arg0->players[player_idx].hp = 0x12C;
                arg0->players[player_idx].xD_b2 = 1;
                arg0->players[player_idx].xD_b0 = 1;
                arg0->players[player_idx].xD_b2 = 1;
                arg0->players[player_idx].spawn_dir = -1;
                if ((s32) arg0->players[player_idx].c_kind == 0x1E) {
                    arg0->players[player_idx].slot_type = 3;
                }
                boss_count += 1;
            }
            if ((u8) arg0->rules.is_teams == 1) {
                arg0->players[player_idx].team = 4;
            }
            player_idx += 1;
            if (player_idx >= 6) {
                break;
            }
        } else {
            if (((s32) enemy_idx == 0) && ((s32) enemy_kind[1] == 0x1A)) {
                arg0->players[player_idx].slot_type = 3;
                player_idx += 1;
            }
        }
        enemy_idx += 1;
        color_iter += 1;
        if ((s32) enemy_idx >= 3) {
            break;
        }
    }

    {
        s32 i;
        for (i = player_idx; i < 6; i++) {
            arg0->players[i].slot_type = 3;
        }
    }

    flags = arg1->x0.x8;
    if (flags & 0x40) {
        arg1->x0.xC.xC = 7;
    } else if (flags & 1) {
        if ((flags & 8) && (arg3 > 1U)) {
            arg1->x0.xC.xC = 4;
        } else {
            arg1->x0.xC.xC = 2;
        }
    }
    if (boss_count != 0) {
        arg0->rules.x1_2 = 1;
        arg0->rules.x1_3 = 1;
        arg0->rules.x1_4 = 1;
        arg0->rules.x0_3 = 3;
        arg0->rules.disable_pausing = 1;
        arg0->rules.x7 = 0;
        arg0->rules.x44 = (void (*)(void)) fn_8017C71C;
        arg1->x0.xC.xC = 6;
    }
    if (arg7 == 0x49) {
        arg1->x0.xC.xC = 8;
    }
    return (s32) flags;
}

bool gm_8017D7AC(MatchExitInfo* arg0, Unk1PData* arg1, u8 arg2)
{
    u8 temp_r0;

    arg1->xC.x14 =
        lbTime_8000AEC8(arg1->xC.x14, arg0->match_end.player_standings[0].xE);
    gm_8016247C(arg0->match_end.player_standings[0].xE);
    arg1->xC.x1C =
        lbTime_8000AEC8(arg1->xC.x1C, arg0->match_end.player_standings[0].x44);
    gm_80162968(arg0->match_end.frame_count / 60);
    if (!(arg1->x8 & 0x80)) {
        arg1->xC.x20 =
            lbTime_8000AEC8(arg1->xC.x20, arg0->match_end.frame_count);
    }
    if (arg0->match_end.player_standings[0].character_id == 7) {
        arg1->xC.x12 = 1;
    } else {
        arg1->xC.x12 = 0;
    }
    if (fn_8016B510() != 0) {
        arg1->xC.xF = 1;
    }
    if (fn_8016B4BC() != 0) {
        arg1->xC.xE = 1;
    }
    temp_r0 = arg0->match_end.result;
    if ((temp_r0 == 7 || temp_r0 == 8) && DbLevel <= 2) {
        switch (gm_GetCurrentGameMode()) {
        case GM_CLASSIC:
            fn_80162BFC(arg1->ckind, arg1->xC.x18);
            break;
        case GM_ADVENTURE:
            fn_80162DF8(arg1->ckind, arg1->xC.x18);
            break;
        case GM_ALLSTAR:
            fn_80162FF4(arg1->ckind, arg1->xC.x18);
            break;
        }
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return 0;
    }
    fn_8017E3C8();
    if (!(arg1->x8 & 0x80)) {
        arg1->stocks = arg0->match_end.player_standings[0].stocks;
        if (arg1->stocks != 0) {
            if (arg0->match_end.result == 1) {
                arg1->stocks--;
                if (arg1->stocks == 0) {
                    gm_SetPendingSceneIndex(arg2);
                    return 0;
                }
                if (!(arg1->x8 & 0x40)) {
                    arg1->xC.x10++;
                    gm_SetPendingSceneIndex(gm_GetCurrentSceneIndex());
                    return 0;
                }
            }
        } else {
            arg1->xC.x10 = 0;
            gm_SetPendingSceneIndex(arg2);
            return 0;
        }
    }
    arg1->xC.x18 = arg0->x0;
    arg1->xC.x10 = 0;
    return 1;
}

s32 fn_8017D9C0(u8* arg0, u8* arg1)
{
    u8* base;
    u8* p;
    s32 i;
    s32 j;
    u8 temp;
    u8* dst;
    u8 ch;
    s32 excluded_idx;
    s32 rejected_idx;
    s32 len;

    p = base = lbl_803D79F0;
    len = 0;
    while ((s32) *p != 0x21) {
        p++;
        len++;
    }

    p = base;
    for (j = 0; j < len; j++) {
        temp = *p;
        dst = &base[HSD_Randi(len)];
        *p = *dst;
        p++;
        *dst = temp;
    }

    p = base;
    for (i = 0; i < len; i++) {
        if (gm_IsCKindUnlocked(*p) != 0) {
            ch = *p;
            for (excluded_idx = 0; excluded_idx < 4; excluded_idx++) {
                if ((s8) ch == (s8) arg0[excluded_idx]) {
                    excluded_idx = -1;
                    break;
                }
            }
            if (excluded_idx != -1) {
                for (rejected_idx = 0; rejected_idx < 3; rejected_idx++) {
                    if ((s8) ch == (s8) arg1[rejected_idx]) {
                        rejected_idx = -1;
                        break;
                    }
                }
                if (rejected_idx != -1) {
                    return (s32) base[i];
                }
            }
        }
        p++;
    }

    return 0x21;
    PAD_STACK(8);
}

void gm_8017DB58(struct Unk1PData_x24* arg0)
{
    int i;
    for (i = 0; i < 3; i++) {
        arg0[i].ckind = CHKIND_NONE;
    }
}

u8 gm_8017DB6C(gm_8017DB6C_arg0_t* arg0, int index)
{
    return arg0[index].x0;
}

u8 gm_8017DB78(gm_8017DB6C_arg0_t* arg0, int index)
{
    return arg0[index].x1;
}

s32 gm_8017DB88(void* arg0, u8 arg1, s32 arg2, s32 arg3, u8* arg4, u8 arg5,
                u8 (*arg6)(s32, s32, u8), u8 (*arg7)(s32, s32, u8),
                u8 (*arg8)(s32, s32, u8), f32 (*arg9)(s32, s32),
                f32 (*arg10)(s32, s32))
{
    u8 chars[4];
    s32 val;
    f32 fval;

    {
        u8* p;
        RegClearCharEntry* out;
        s32 i;
        s32 count;

        count = fn_8017DE54(arg1, arg4);
        chars[1] = 0x21;
        out = arg0;
        chars[2] = 0x21;
        p = chars;
        i = 0;
        chars[3] = 0x21;
        chars[0] = arg5;
        for (; i < count; i++) {
            p[1] = fn_8017D9C0(chars, arg4);
            out->x0 = p[1];
            if (arg8 != NULL) {
                val = arg8(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x1 = val;
            if (arg6 != NULL) {
                val = arg6(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x2 = val;
            if (arg7 != NULL) {
                val = arg7(arg3, arg2, (u8) i);
            } else {
                val = 0;
            }
            out->x3 = val;
            if (arg9 != NULL) {
                fval = arg9(arg3, arg2);
            } else {
                fval = 0.0f;
            }
            out->x4 = fval;
            if (arg10 != NULL) {
                fval = arg10(arg3, arg2);
            } else {
                fval = 0.0f;
            }
            out->x8 = fval;
            p++;
            out++;
        }
        for (; i < 3; i++) {
            ((RegClearCharEntry*) arg0)[i].x0 = 0x21;
        }
        return count;
    }
}

s32 fn_8017DD7C(PlayerInitData* arg0, Unk1PData_x24* arg1, u8 arg2)
{
    s32 index = 1;
    int i;
    for (i = 0; i < 3; i++) {
        if (arg1[i].ckind != CHKIND_NONE) {
            gm_8016795C(&arg0[index]);
            arg0[index].c_kind = arg1[i].ckind;
            arg0[index].slot_type = 1;
            arg0[index].stocks = 1;
            arg0[index].team = arg0->team;
            arg0[index].color = arg1[i].x1;
            arg0[index].xE = arg1[i].x3;
            arg0[index].cpu_level = arg1[i].x2;
            arg0[index].x18 = arg1[i].x4;
            arg0[index].x1C = arg1[i].x8;
            arg0[index].xD_b1 = 1;
            if (arg0[index].c_kind == CKIND_GKOOPS) {
                arg0[index].xC_b1 = 0;
            }
            index++;
        }
    }
    return index - 1;
}

s32 fn_8017DE54(u8 arg0, u8* arg1)
{
    u8* p;
    s32 count;

    if (arg0 & 0x20) {
        return 0;
    }
    if (arg0 & 0x10) {
        count = 0;
        if ((s32) arg1[0] != 0x21) {
            count = 1;
        }
        p = &arg1[1];
        if ((s32) *p != 0x21) {
            count += 1;
        }
        if ((s32) p[1] != 0x21) {
            count += 1;
        }
        return 3 - count;
    }
    if (arg0 & 2) {
        return 2;
    }
    return 0;
}

Unk1PData* fn_8017DEC8(int arg0)
{
    switch (arg0) {
    case 0:
        return &gm_GetAdventureData()->x0;
    case 1:
        return &gm_GetAllStarData()->x0;
    case 2:
        return &gm_80473A18.x0;
    default:
        return NULL;
    }
}

Unk1PData* fn_8017DF28(void)
{
    switch (gm_GetCurrentGameMode()) {
    case GM_CLASSIC:
        return &gm_GetAllStarData()->x0;
    case GM_ADVENTURE:
        return &gm_GetAdventureData()->x0;
    case GM_ALLSTAR:
        return &gm_80473A18.x0;
    default:
        return NULL;
    }
}

u8 fn_8017DF90(void)
{
    switch (gm_GetCurrentGameMode()) {
    case GM_CLASSIC:
        return 1;
    case GM_ADVENTURE:
        return 0;
    case GM_ALLSTAR:
        return 2;
    default:
        return 3;
    }
}

int gm_8017DFF4(int arg0)
{
    Unk1PData* var_r3 = fn_8017DEC8(arg0);
    if (var_r3 != NULL) {
        return var_r3->cpu_level;
    }
    return -1;
}

int gm_8017E068(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->cpu_level;
    }
    return -1;
}

int fn_8017E0E4(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    if (var_r3 != NULL) {
        return var_r3->xC.xC;
    }
    return -1;
}

bool fn_8017E160(void)
{
    Unk1PData* var_r3 = fn_8017DF28();
    struct Unk1PData_xC* temp_r3_2;

    if (var_r3 != NULL) {
        int i;
        for (i = 0; i < 3; i++) {
            if (var_r3->xC.x24[i].ckind != CHKIND_NONE) {
                return true;
            }
        }
        return false;
    }
    return false;
}

void fn_8017E21C(void)
{
    int i;
    for (i = 0; i < 12; i++) {
        lbl_804706D8[i].x0 = -1;
    }
}

s8 gm_8017E280(u16 arg0, u32 arg1)
{
    lbl_804706D8_t* var_r7 = lbl_804706D8;
    s32 index;
    index = 0;
    for (index = 0; index < 12; index++) {
        if (arg0 == var_r7[index].x0) {
            var_r7[index].x2 += arg1;
            return var_r7[index].x2;
        }
    }
    index = 0;
    for (index = 0; index < 12; index++) {
        if (var_r7[index].x0 == -1) {
            var_r7[index].x0 = arg0;
            var_r7[index].x2 = arg1;
            return (u8) arg1;
        }
    }
    return -1;
}

int fn_8017E318(void)
{
    int i;
    int sum = 0;
    for (i = 0; i < 12; i++) {
        if (lbl_804706D8[i].x0 != -1) {
            sum += lbl_804706D8[i].x2;
        }
    }
    return sum;
}

void fn_8017E3C8(void)
{
    int i = 0;
    PAD_STACK(8);
    for (i = 0; i < 12; i++) {
        if (lbl_804706D8[i].x0 != -1) {
            Toy_SetUnlockState(lbl_804706D8[i].x0, lbl_804706D8[i].x2);
        }
    }
}
