#include "gm_1B03.h"

#include "gm_1B03.static.h"

#include "gm/gm_1A3F.h"
#include "if/soundtest.h"

#include "mn/forward.h"
#include <melee/pl/forward.h>

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/db/db.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gmresultplayer.h>
#include <melee/gm/gmtou.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbmthp.h>
#include <melee/lb/lbsnap.h>
#include <melee/lb/lbtime.h>
#include <melee/lb/types.h>
#include <melee/mn/mngallery.h>
#include <melee/mn/mnsnap.h>
#include <melee/mn/types.h>
#include <melee/vi/types.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>

extern TmData gm_804771C4;

/* 480F20 */ MatchExitInfo gm_80480F20;
/* 48E5F8 */ UNK_T gm_8048E5F8[0x2288 / 4];
/* 48E4C0 */ StartMeleeData gm_8048E4C0;
/* 48E378 */ SSSData gm_8048E378;
/* 48E230 */ CSSData gm_8048E230;
/* 48BE68 */ UNK_T gm_8048BE68[0x23C8 / 4];
/* 48BD20 */ UNK_T gm_8048BD20[0x148 / 4];
/* 489A98 */ UNK_T gm_80489A98[0x2288 / 4];
/* 487810 */ MatchExitInfo gm_80487810;
/* 4876D8 */ StartMeleeData gm_804876D8;
/* 485454 */ UNK_T gm_80485454[0x2284 / 4];
/* 485438 */ UNK_T gm_80485438[0x1C / 4];
/* 48542C */ UNK_T gm_8048542C[0xC / 4];
/* 4831A8 */ struct ResultsMatchInfo gm_804831A8;
/* 480DC8 */ static UNK_T gm_80480DC8[0x20 / 4];
/* 480DE8 */ static StartMeleeData gm_80480DE8;

/* 3DD6A0 */ GameScene gm_803DD6A0_Scenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B087C,
        gm_801B089C,
        {
            NULL,
            NULL,
            gm_804D6878,
        },
    },
    { 0xFF },
};

/// @todo Possible split here due to usage of #gm_80480DC8
/* 3DD6D0 */ GameScene gm_803DD6D0_Scenes[] = {
    {
        0x00,
        0x02,
        0,
        gm_801B09C0,
        NULL,
        {
            GS_DEBUG_MENU,
            gm_804D6890,
            NULL,
        },
    },
    {
        0x01,
        0x02,
        0,
        gm_801B0A34,
        NULL,
        {
            GS_DEBUG_MENU,
            gm_804D6890,
            NULL,
        },
    },
    {
        0x02,
        0x02,
        0,
        gm_801B0AC8,
        NULL,
        {
            GS_DEBUG_MENU,
            gm_804D6890,
            NULL,
        },
    },
    {
        0x03,
        0x02,
        0,
        gm_801B0B00,
        gm_801B0B24,
        {
            GS_PRIZE_INTERFACE,
            gm_8048542C,
            NULL,
        },
    },
    {
        0x04,
        0x02,
        0,
        gm_801B0B48,
        NULL,
        {
            GS_VS,
            &gm_80480DE8,
            &gm_80480F20,
        },
    },
    {
        0x05,
        0x02,
        0,
        gm_801B0B8C,
        gm_801B0BF0,
        {
            GS_RESULTS,
            &gm_804831A8,
            &gm_804831A8,
        },
    },
    {
        0x06,
        0x02,
        0,
        gm_801B0C18,
        gm_801B099C,
        {
            GS_INTRO_EASY,
            gm_80480DC8,
            gm_804D6880,
        },
    },
    {
        0x07,
        0x02,
        0,
        gm_801B0C50,
        gm_801B099C,
        {
            GS_INTRO_ALLSTAR,
            gm_804D6884,
            gm_804D688C,
        },
    },
    {
        0x08,
        0x02,
        0,
        NULL,
        gm_801B099C,
        {
            GS_COMING_SOON,
            NULL,
            NULL,
        },
    },
    {
        0x09,
        0x02,
        0,
        gm_801B0C74,
        gm_801B099C,
        {
            GS_GAMEOVER,
            gm_80485438,
            gm_80485438,
        },
    },
    {
        0x0A,
        0x02,
        0,
        gm_801B0CF0,
        gm_801B099C,
        {
            GS_APPROACH,
            gm_804D6898,
            gm_804D6898,
        },
    },
    {
        0x0B,
        0x02,
        0,
        gm_801B0DD0,
        gm_801B0F1C,
        {
            GS_RESULTS,
            gm_80485454,
            NULL,
        },
    },
    {
        0x0C,
        0x02,
        0,
        NULL,
        gm_801B099C,
        {
            GS_MOVIE_OPENING,
            NULL,
            NULL,
        },
    },
    {
        0x0D,
        0x02,
        0,
        gm_801B0F60,
        gm_801B0F90,
        {
            GS_MEMCARD,
            gm_804D689C,
            gm_804D68A4,
        },
    },
    {
        0x0E,
        0x02,
        0,
        NULL,
        NULL,
        {
            GS_STAFFROLL,
            NULL,
            NULL,
        },
    },
    { 0xFF },
};

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
        if (arg1->result == 1) {
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

#pragma push
#pragma dont_inline on
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
#pragma pop

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

void gm_801B087C(GameScene* arg0)
{
    lbDvd_800174BC();
}

void gm_801B089C(GameScene* scene)
{
    int* temp_r3 = gm_801A4284(scene);
    if (DbLevel >= 3) {
        if (*temp_r3 & 0x100) {
            gm_801A42E8(GM_DEBUG_VS);
        } else if (*temp_r3 & 0x1000) {
            gm_80173EEC();
            gm_80172898(0x100);
            if (!gm_80173754(1, 0)) {
                gm_801A42E8(GM_MENU);
            }
        } else if (*temp_r3 & 0x400) {
            gm_801A42E8(GM_DEBUG_SOUND_TEST);
        } else if (*temp_r3 & 0x800) {
            gm_801A42E8(GM_DEBUG);
        } else {
            gm_801BF708(1);
            gm_801A42E8(GM_OPENING_MV);
        }
    } else if (*temp_r3 & 0x1000) {
        gm_80173EEC();
        gm_80172898(0x100);
        if (!gm_80173754(1, 0)) {
            gm_801A42E8(GM_MENU);
        }
    } else {
        gm_801BF708(1);
        gm_801A42E8(GM_OPENING_MV);
    }
    gm_801A42D4();
}

void gm_801B099C(GameScene* unused)
{
    gm_SetPendingScene(0);
}

struct UnkUnloadData {
    UNK_T x0;
    UNK_T x4;
};

extern UNK_T un_803FA4E0[];
extern UNK_T un_803FA790[];
extern UNK_T un_803FC4CC[];

void gm_801B09C0(GameScene* arg0)
{
    struct UnkUnloadData* temp_r3 = gm_801A427C(arg0);
    temp_r3->x0 = un_803FA4E0;
    temp_r3->x4 = fn_801B09F8;
}

int fn_801B09F8(int arg0)
{
    if (arg0 == 0) {
        lbAudioAx_80024030(0);
        gm_801A42F8(GM_TITLE);
        gm_801A4B60();
    }
    return 0;
}

void gm_801B0A34(GameScene* arg0)
{
    struct UnkUnloadData* temp_r3 = gm_801A427C(arg0);
    temp_r3->x0 = un_803FA790;
    temp_r3->x4 = fn_801B0A8C;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

int fn_801B0A8C(int arg0)
{
    if (arg0 == 0) {
        lbAudioAx_80024030(0);
        gm_SetPendingScene(0);
        gm_801A4B60();
    }
    return 0;
}

void gm_801B0AC8(GameScene* arg0)
{
    struct UnkUnloadData* temp_r3 = gm_801A427C(arg0);
    temp_r3->x0 = un_803FC4CC;
    temp_r3->x4 = fn_801B0A8C;
}

void gm_801B0B00(GameScene* arg0)
{
    un_802FFEE0(gm_801A427C(arg0));
}

void gm_801B0B24(GameScene* arg0)
{
    gm_SetPendingScene(2);
}

void gm_801B0B48(GameScene* arg0)
{
    un_802FFF2C(gm_801A427C(arg0));
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void gm_801B0B8C(GameScene* arg0)
{
    struct ResultsMatchInfo* temp_r3 = gm_801A427C(arg0);
    gm_80177724(temp_r3);
    temp_r3->match_end = gm_80480F20.match_end;
}

void gm_801B0BF0(GameScene* arg0)
{
    gm_801A4284(arg0);
    gm_SetPendingScene(0);
}

void gm_801B0C18(GameScene* arg0)
{
    UNK_T* temp_r31 = gm_801A427C(arg0);
    gm_80168F88();
    un_80301BA8(temp_r31);
}

void gm_801B0C50(GameScene* arg0)
{
    un_80301C64(gm_801A427C(arg0));
}

extern int un_803FA258[];

void gm_801B0C74(GameScene* arg0)
{
    struct DebugGameOverData* data;

    data = gm_801A427C(arg0);
    data->x0 = 0x1869F;
    data->x8 = 1;
    data->ckind = un_803FA258[0x4D];
    data->slot = 0;
    data->x15 = 0x78;
    data->x18 = HSD_Randi(0x3E8);
    data->x16 = (HSD_Randi(0xA) + 1);
}

void gm_801B0CF0(GameScene* arg0)
{
    u8* temp_r3 = gm_801A427C(arg0);
    temp_r3[1] = 0;

    switch (un_803FA258[0x50]) {
    default:
    case 12:
        temp_r3[0] = 0x19;
        break;
    case 1:
        temp_r3[0] = 3;
        break;
    case 2:
        temp_r3[0] = 7;
        break;
    case 3:
        temp_r3[0] = 9;
        break;
    case 4:
        temp_r3[0] = 0xA;
        break;
    case 5:
        temp_r3[0] = 0xF;
        break;
    case 6:
        temp_r3[0] = 0x14;
        break;
    case 7:
        temp_r3[0] = 0x15;
        break;
    case 8:
        temp_r3[0] = 0x16;
        break;
    case 9:
        temp_r3[0] = 0x17;
        break;
    case 10:
        temp_r3[0] = 0x18;
        break;
    case 11:
        temp_r3[0] = 0x19;
        break;
    }
}

void gm_801B0DD0(GameScene* arg0)
{
    u64 sfx_result = 0;
    int i;
    struct DebugResultsData* data = gm_801A427C(arg0);
    MatchEnd* match_end = &data->match_end;

    data->x0_0 = un_803FA258[0x5E];
    data->x0_1 = un_803FA258[0x5F];
    data->x1 = un_803FA258[0x5A];
    data->x2 = un_803FA258[0x5B];
    data->x3 = un_803FA258[0x5C];
    data->x4 = un_803FA258[0x5D];

    gm_80166A98(match_end, un_803FA258[0x60] & 0xFF, (s8) un_803FA258[0x51],
                un_803FA258[0x56] - 1, (s8) un_803FA258[0x52],
                un_803FA258[0x57] - 1, (s8) un_803FA258[0x53],
                un_803FA258[0x58] - 1, (s8) un_803FA258[0x54],
                un_803FA258[0x59] - 1);

    for (i = 0; i < 4; i++) {
        if (match_end->player_standings[i].slot_type != 3 &&
            match_end->player_standings[i].is_big_loser == 0)
        {
            sfx_result |= lbAudioAx_80026E84(
                match_end->player_standings[i].character_kind);
        }
    }

    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(0x4, sfx_result);
    gm_80168FC4();
    gm_801701A0();
    PAD_STACK(8);
}

void gm_801B0F1C(GameScene* arg0)
{
    lbAudioAx_800236DC();
    if (HSD_PadCopyStatus->button & HSD_PAD_L) {
        gm_SetPendingScene(0xB);
    } else {
        gm_SetPendingScene(0);
    }
}

void gm_801B0F60(GameScene* arg0)
{
    struct DebugMemcardData* data;

    data = gm_801A427C(arg0);
    data->x0 = 1;
    data->x4 = 0;
}

void gm_801B0F90(GameScene* arg0)
{
    gm_801A4284(arg0);
    gm_SetPendingScene(0);
}
