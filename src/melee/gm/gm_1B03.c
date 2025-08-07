#include "gm_1B03.h"

#include "gm_1B03.static.h"

#include "gmmovieend.h"
#include "gmvsdata.h"

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
#include <melee/mn/types.h>
#include <melee/un/un_2FC9.h>
#include <melee/vi/types.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>

extern TmData gm_804771C4;

/* 477738 */ extern ResultsMatchInfo gm_80477738;
/* 4876D8 */ static StartMeleeData gm_804876D8;
/* 487810 */ static MatchExitInfo gm_80487810;

static u32 gm_804D6878[2];

MinorScene gm_803DD6A0_MinorScenes[] = {
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

static UNK_T gm_80480DC8[0x20 / 4];
static StartMeleeData gm_80480DE8;
static MatchExitInfo gm_80480F20;
static struct ResultsMatchInfo gm_804831A8;
static UNK_T gm_8048542C[0xC / 4];
static UNK_T gm_80485438[0x1C / 4];
static UNK_T gm_80485454[0x2284 / 4];

static UNK_T gm_804D6880[0x4 / 4];
static UNK_T gm_804D6884[0x8 / 4];
static UNK_T gm_804D688C[0x4 / 4];
static UNK_T gm_804D6890[0x8 / 4];
static UNK_T gm_804D6898[0x4 / 4];
static UNK_T gm_804D689C[0x8 / 4];
static UNK_T gm_804D68A4[0x8 / 4];

// file boundary?
static UNK_T gm_804D68A4_pad[0x4 / 4];

MinorScene gm_803DD6D0_MinorScenes[] = {
    {
        0x00,
        0x02,
        0,
        gm_801B09C0,
        NULL,
        {
            MN_DEBUG_MENU,
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
            MN_DEBUG_MENU,
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
            MN_DEBUG_MENU,
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
            MN_PRIZE_INTERFACE,
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
            MN_VS,
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
            MN_RESULTS,
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
            MN_INTRO_EASY,
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
            MN_INTRO_ALLSTAR,
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
            MN_COMING_SOON,
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
            MN_GAMEOVER,
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
            MN_APPROACH,
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
            MN_RESULTS,
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
            MN_MOVIE_OPENING,
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
            MN_MEMCARD,
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
            MN_STAFFROLL,
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

    if (arg0->rules.x8 != 1) {
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
        arg0->players[i].slot_type = 3;
    }
}

static inline int gm_801B0474_inline(MatchEnd* arg1, int i)
{
    if (arg1->x5 == 1) {
        if (arg1->result == 1) {
            return arg1->player_standings[i].stocks;
        } else {
            u8 var_r7 = arg1->player_standings[i].stocks;
            if (arg1->player_standings[i].x28 >= arg1->frame_count) {
                switch (var_r7) {
                case 0:
                    break;
                default:
                    return var_r7;
                }
            }
        }
    }
    return 1;
}

void gm_801B0474(StartMeleeData* arg0, MatchEnd* arg1)
{
    int var_r7;
    s8 var_r6;
    int i;

    arg0->rules.x0_0 = 1;
    arg0->rules.x0_6 = false;
    arg0->rules.x2_5 = false;

    for (i = 0; i < 6; i++) {
        if (arg0->players[i].slot_type != 3) {
            var_r7 = gm_801B0474_inline(arg1, i);
            if (arg1->is_teams == 1) {
                player_standings_inline(
                    arg0, arg1, i, var_r7,
                    arg1->team_standings[arg1->player_standings[i].team]
                        .is_big_loser);
            } else {
                player_standings_inline(
                    arg0, arg1, i, var_r7,
                    arg1->player_standings[i].is_big_loser);
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

void gm_801B0620(PlayerInitData* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4)
{
    arg0->slot_type = 0;
    arg0->c_kind = arg1;
    arg0->color = arg2;
    arg0->stocks = arg3;
    gm_801B05F4(arg0, arg4);
}

void gm_801B0664(PlayerInitData* arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4)
{
    arg0->slot_type = 1;
    arg0->c_kind = arg1;
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
void gm_801B0730(CSSData* css_data, s8* c_kind, s8* stocks, u8* color,
                 s8* arg4, u8* level)
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
    if (arg4 != NULL) {
        *arg4 = css_data->data.data.players[slot].xA;
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

void gm_801B087C(MinorScene* arg0)
{
    lbDvd_800174BC();
}

void gm_801B089C(MinorScene* scene)
{
    int* temp_r3 = gm_801A4284(scene);
    if (g_debugLevel >= 3) {
        if (*temp_r3 & 0x100) {
            gm_801A42E8(0xE);
        } else if (*temp_r3 & 0x1000) {
            gm_80173EEC();
            gm_80172898(0x100);
            if (gm_80173754(1, 0) == 0) {
                gm_801A42E8(1);
            }
        } else if (*temp_r3 & 0x400) {
            gm_801A42E8(7);
        } else if (*temp_r3 & 0x800) {
            gm_801A42E8(6);
        } else {
            gm_801BF708(1);
            gm_801A42E8(0x18);
        }
    } else if (*temp_r3 & 0x1000) {
        gm_80173EEC();
        gm_80172898(0x100);
        if (gm_80173754(1, 0) == 0) {
            gm_801A42E8(1);
        }
    } else {
        gm_801BF708(1);
        gm_801A42E8(0x18);
    }
    gm_801A42D4();
}

void gm_801B099C(MinorScene* unused)
{
    gm_SetScenePendingMinor(0);
}

struct UnkUnloadData {
    UNK_T x0;
    UNK_T x4;
};

extern UNK_T un_803FA4E0[];
extern UNK_T un_803FA790[];
extern UNK_T un_803FC4CC[];

void gm_801B09C0(MinorScene* arg0)
{
    struct UnkUnloadData* temp_r3 = gm_801A427C(arg0);
    temp_r3->x0 = un_803FA4E0;
    temp_r3->x4 = fn_801B09F8;
}

int fn_801B09F8(int arg0)
{
    if (arg0 == 0) {
        lbAudioAx_80024030(0);
        gm_801A42F8(MJ_TITLE);
        gm_801A4B60();
    }
    return 0;
}

void gm_801B0A34(MinorScene* arg0)
{
    struct UnkUnloadData* temp_r3 = gm_801A427C(arg0);
    temp_r3->x0 = un_803FA790;
    temp_r3->x4 = fn_801B09F8;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

int fn_801B0A8C(int arg0)
{
    if (arg0 == 0) {
        lbAudioAx_80024030(0);
        gm_SetScenePendingMinor(0);
        gm_801A4B60();
    }
    return 0;
}

void gm_801B0AC8(MinorScene* arg0)
{
    struct UnkUnloadData* temp_r3 = gm_801A427C(arg0);
    temp_r3->x0 = un_803FC4CC;
    temp_r3->x4 = fn_801B09F8;
}

void gm_801B0B00(MinorScene* arg0)
{
    un_802FFEE0(gm_801A427C(arg0));
}

void gm_801B0B24(MinorScene* arg0)
{
    gm_SetScenePendingMinor(2);
}

void gm_801B0B48(MinorScene* arg0)
{
    un_802FFF2C(gm_801A427C(arg0));
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x20);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void gm_801B0B8C(MinorScene* arg0)
{
    struct ResultsMatchInfo* temp_r3 = gm_801A427C(arg0);
    gm_80177724(temp_r3);
    temp_r3->match_end = gm_80480F20.match_end;
}

void gm_801B0BF0(MinorScene* arg0)
{
    gm_801A4284(arg0);
    gm_SetScenePendingMinor(0);
}

void gm_801B0C18(MinorScene* arg0)
{
    UNK_T* temp_r31 = gm_801A427C(arg0);
    gm_80168F88();
    un_80301BA8(temp_r31);
}

void gm_801B0C50(MinorScene* arg0)
{
    un_80301C64(gm_801A427C(arg0));
}

extern int un_803FA258[];

void gm_801B0C74(MinorScene* arg0)
{
    struct DebugGameOverData* data;

    data = gm_801A427C(arg0);
    data->x0 = 0x1869F;
    data->x8 = 1;
    data->x10 = un_803FA258[0x4D];
    data->x14 = 0;
    data->x15 = 0x78;
    data->x18 = HSD_Randi(0x3E8);
    data->x16 = (HSD_Randi(0xA) + 1);
}

void gm_801B0CF0(MinorScene* arg0)
{
    u8* temp_r3 = gm_801A427C(arg0);
    temp_r3[1] = 0;

    switch (un_803FA258[0x50]) {
    default:
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
    case 12:
        temp_r3[0] = 0x19;
        break;
    }
}

/// #gm_801B0DD0

void gm_801B0F1C(MinorScene* arg0)
{
    lbAudioAx_800236DC();
    if (HSD_PadCopyStatus->button & HSD_PAD_L) {
        gm_SetScenePendingMinor(0xB);
    } else {
        gm_SetScenePendingMinor(0);
    }
}

void gm_801B0F60(MinorScene* arg0)
{
    struct DebugMemcardData* data;

    data = gm_801A427C(arg0);
    data->x0 = 1;
    data->x4 = 0;
}

void gm_801B0F90(MinorScene* arg0)
{
    gm_801A4284(arg0);
    gm_SetScenePendingMinor(0);
}

static UNK_T gm_804D68B0[0x8 / 4];

MinorScene gm_803DD888_MinorScenes[] = {
    {
        0,
        2,
        0,
        gm_801B0FB8,
        NULL,
        {
            MN_DEBUG_MENU,
            gm_804D68B0,
            NULL,
        },
    },
    { -1 },
};

void gm_801B0FB8(MinorScene* arg0)
{
    struct DebugSoundTestData* data;

    data = gm_801A427C(arg0);
    data->x0 = &un_803F9FA4;
    data->x4 = 0;
    un_802FF7DC();
    un_802FF884("/audio");
}

static GameRules* gm_804D68B8;
static UNK_T gm_804D68BC;

MinorScene gm_803DD8B8_MinorScenes[] = {
    {
        0,
        2,
        0,
        gm_801B0FF8,
        gm_801B138C,
        {
            MN_MENU,
            &gm_804D68B8,
            &gm_804D68BC,
        },
    },
    { -1 },
};

void gm_801B0FF8(MinorScene* arg0)
{
    GameRules* temp_r3;
    struct gm_801B0FF8_arg0_x10_t* temp_r31;
    MajorSceneKind var_r0;

    temp_r31 = arg0->info.unk_struct_0;
    lb_8001C550();
    lb_8001D164(0);
    lbSnap_8001E218(HSD_MemAlloc(lbSnap_8001E204()),
                    HSD_MemAlloc(lbSnap_8001E210()));
    {
        ssize_t i;
        for (i = 0; i < (signed) ARRAY_SIZE(mnGallery_804A0B90); i++) {
            mnGallery_804A0B90[i] =
                HSD_MemAlloc(sizeof(struct mnGallery_804A0B90_t));
        }
    }
    lbDvd_80018C6C();
    lbDvd_8001823C();
    lbDvd_80018254();
    mnGallery_80258940();
    temp_r3 = gmMainLib_8015CC34();
    if (temp_r3->unk_x0 != 0) {
        temp_r3->unk_x0 = 0;
        temp_r31->x0 = 0;
        temp_r31->x1 = 0;
        temp_r31->x2 = 1;
        return;
    }
    temp_r31->x2 = 1;
    var_r0 = gm_801A4320();
    if (var_r0 == MJ_CHALLENGER_APPROACH) {
        var_r0 = gm_801737D8();
    }
    switch (var_r0) {
    case MJ_CLASSIC:
        temp_r31->x0 = 6;
        temp_r31->x1 = 0;
        return;
    case MJ_ADVENTURE:
        temp_r31->x0 = 6;
        temp_r31->x1 = 1;
        return;
    case MJ_ALLSTAR:
        temp_r31->x0 = 6;
        temp_r31->x1 = 2;
        return;
    case MJ_CLASSIC_GOVER:
        temp_r31->x0 = 6;
        temp_r31->x1 = 0;
        return;
    case MJ_ADVENTURE_GOVER:
        temp_r31->x0 = 6;
        temp_r31->x1 = 1;
        return;
    case MJ_ALLSTAR_GOVER:
        temp_r31->x0 = 6;
        temp_r31->x1 = 2;
        return;
    case MJ_EVENT:
        temp_r31->x0 = 7;
        temp_r31->x1 = 0;
        return;
    case MJ_TARGET_TEST:
        temp_r31->x0 = 9;
        temp_r31->x1 = 0;
        return;
    case MJ_10MAN_VS:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 0;
        return;
    case MJ_100MAN_VS:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 1;
        return;
    case MJ_3MIN_VS:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 2;
        return;
    case MJ_15MIN_VS:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 3;
        return;
    case MJ_ENDLESS_VS:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 4;
        return;
    case MJ_CRUEL_VS:
        temp_r31->x0 = 0x21;
        temp_r31->x1 = 5;
        return;
    case MJ_HOME_RUN_CONTEST:
        temp_r31->x0 = 9;
        temp_r31->x1 = 1;
        return;
    case MJ_TRAINING:
        temp_r31->x0 = 1;
        temp_r31->x1 = 4;
        return;
    case MJ_VS:
        temp_r31->x0 = 2;
        temp_r31->x1 = 0;
        return;
    case MJ_TOURNAMENT:
        temp_r31->x0 = 2;
        temp_r31->x1 = 1;
        return;
    case MJ_CAMERA_MODE:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 0;
        return;
    case MJ_STAMINA_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 1;
        return;
    case MJ_SUPER_SUDDEN_DEATH_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 2;
        return;
    case MJ_GIANT_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 3;
        return;
    case MJ_TINY_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 4;
        return;
    case MJ_INVISIBLE_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 5;
        return;
    case MJ_SLOMO_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 9;
        return;
    case MJ_LIGHTNING_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 8;
        return;
    case MJ_FIXED_CAMERA_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 6;
        return;
    case MJ_SINGLE_BUTTON_VS:
        temp_r31->x0 = 0xC;
        temp_r31->x1 = 7;
        return;
    case MJ_TOY_GALLERY:
        temp_r31->x0 = 3;
        temp_r31->x1 = 0;
        return;
    case MJ_TOY_LOTTERY:
        temp_r31->x0 = 3;
        temp_r31->x1 = 1;
        return;
    case MJ_TOY_COLLECTION:
        temp_r31->x0 = 3;
        temp_r31->x1 = 3;
        return;
    case MJ_MENU:
        temp_r31->x0 = 4;
        temp_r31->x1 = 4;
        return;
    default:
        temp_r31->x0 = 0;
        temp_r31->x1 = 0;
        return;
    }
}

void gm_801B138C(MinorScene* arg0)
{
    struct MainMenuExitData* data = arg0->info.unk_struct_1;

    gm_801A42E8(data->x0);
    gm_801A42D4();
}

MinorScene gm_803DD9A0_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B14A0,
        gm_801B14DC,
        {
            MN_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B1514,
        gm_801B154C,
        {
            MN_SSS,
            &gm_80480668,
            &gm_80480668,
        },
    },
    {
        0x02,
        0x03,
        0,
        gm_801B1588,
        gm_801B15C8,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        0x03,
        0x03,
        0,
        gm_801B1648,
        gm_801B1688,
        {
            MN_SUDDEN_DEATH,
            &gm_80480530,
            &gm_8047E2A4,
        },
    },
    {
        0x04,
        0x03,
        0,
        gm_801B16A8,
        gm_801B16C8,
        {
            MN_RESULTS,
            &gm_8047C020,
            NULL,
        },
    },
    {
        0x80,
        0x02,
        0,
        gm_801BFA6C,
        NULL,
        {
            MN_APPROACH,
            &gm_804D6860,
            &gm_804D6860,
        },
    },
    {
        0x81,
        0x02,
        0,
        gm_801BFABC,
        gm_801A6254,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        0xC0,
        0x02,
        0,
        gm_801BFCFC,
        gm_801A6308,
        {
            MN_PRIZE_INTERFACE,
            &un_804A1F48,
            NULL,
        },
    },
    { 0xFF },
};

MinorScene gm_803DDA78_MinorScenes[] = {
    {
        0x01,
        0x02,
        0,
        gm_801B13B8,
        NULL,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    {
        0x03,
        0x02,
        0,
        gm_801B16A8,
        NULL,
        {
            MN_RESULTS,
            &gm_8047C020,
            NULL,
        },
    },
    { 0xFF },
};

static UNK_T gm_80489A98[0x2288 / 4];
static UNK_T gm_8048BD20[0x148 / 4];
static UNK_T gm_8048BE68[0x23C8 / 4];

MinorScene gm_803DDAC0_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B1724,
        NULL,
        {
            MN_TOU_SETUP,
            NULL,
            NULL,
        },
    },
    {
        0x01,
        0x03,
        0,
        NULL,
        NULL,
        {
            MN_TOU_BRACKET,
            NULL,
            NULL,
        },
    },
    {
        0x02,
        0x03,
        0,
        NULL,
        NULL,
        {
            MN_TOU_ALT,
            NULL,
            NULL,
        },
    },
    {
        0x03,
        0x03,
        0,
        gm_801B174C,
        gm_801B1788,
        {
            MN_SSS,
            gm_8048BD20,
            gm_8048BD20,
        },
    },
    {
        0x04,
        0x03,
        0,
        gm_801B1810,
        gm_801B1834,
        {
            MN_VS,
            &gm_804876D8,
            &gm_80487810,
        },
    },
    {
        0x05,
        0x03,
        0,
        gm_801B18D4,
        gm_801B1A2C,
        {
            MN_SUDDEN_DEATH,
            &gm_804876D8,
            gm_8048BE68,
        },
    },
    {
        0x06,
        0x03,
        0,
        gm_801B1A84,
        gm_801B1AD4,
        {
            MN_RESULTS,
            gm_80489A98,
            NULL,
        },
    },
    { 0xFF },
};

extern UNK_T gm_8048E230[];
extern UNK_T gm_8048E378[];
static StartMeleeData gm_8048E4C0;
extern UNK_T gm_8048E5F8[];

MinorScene gm_803DDB80_MinorScenes[] = {
    { 0x00,
      0x03,
      0,
      gm_801B1B74,
      gm_801B1C24,
      {
          MN_CSS,
          gm_8048E230,
          gm_8048E230,
      } },
    {
        0x01,
        0x03,
        0,
        gm_801B1EB8,
        gm_801B1EEC,
        {
            MN_SSS,
            gm_8048E378,
            gm_8048E378,
        },
    },
    {
        0x02,
        0x03,
        0,
        gm_801B1F70,
        gm_801B2204,
        {
            MN_TRAINING_MODE,
            &gm_8048E4C0,
            gm_8048E5F8,
        },
    },
    { 0xFF },
};

extern UNK_T gm_804D68C8[];

MinorScene gm_803DDBE0_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B24B4,
        gm_801B2510,
        {
            MN_CAMERA_VS,
            gm_804D68C8,
            gm_804D68C8,
        },
    },
    {
        0x01,
        0x03,
        0,
        gm_801B254C,
        gm_801B25D4,
        {
            MN_CSS,
            &gm_804807B0,
            &gm_804807B0,
        },
    },
    {
        0x02,
        0x03,
        0,
        gm_801B26AC,
        gm_801B2704,
        {
            MN_SSS,
            &gm_80480668,
            &gm_80480668,
        },
    },
    {
        0x03,
        0x03,
        0,
        gm_801B2790,
        gm_801B2AF8,
        {
            MN_VS,
            &gm_80480530,
            &gm_80479D98,
        },
    },
    { 0xFF },
};

extern UNK_T gm_80470708[];
extern UNK_T gm_80470850[];
extern UNK_T gm_8047086C[];
extern UNK_T gm_80472AF8[];
extern UNK_T gm_80490880[];
extern UNK_T gm_804D68D0[];

MinorScene gm_803DDC58_MinorScenes[] = {
    {
        0x00,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x01,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x08,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x09,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x10,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x11,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x18,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x19,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x20,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x21,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x28,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x29,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x30,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x31,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x38,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x39,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x40,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x41,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x48,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x49,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x50,
        0x03,
        0,
        gm_801B3500,
        NULL,
        MN_INTRO_EASY,
        gm_80490880,
        gm_804D68D0,
    },
    {
        0x51,
        0x03,
        0,
        gm_801B3A34,
        gm_801B3B40,
        MN_VS,
        gm_80472AF8,
        gm_8047086C,
    },
    {
        0x68,
        0x03,
        0,
        NULL,
        gm_801B3F18,
        MN_COMING_SOON,
        NULL,
        NULL,
    },
    {
        0x69,
        0x03,
        0,
        gm_801B3D44,
        gm_801B3D84,
        MN_GAMEOVER,
        gm_80470850,
        gm_80470850,
    },
    {
        0x70,
        0x03,
        0,
        gm_801B3DD8,
        gm_801B3E44,
        MN_CSS,
        gm_80470708,
        gm_80470708,
    },
    { 0xFF },
};

void gm_801B13B8(MinorScene* arg0)
{
    StartMeleeData* temp_r28 = gm_801A427C(arg0);
    int i;

    gm_80167A64(&temp_r28->rules);
    temp_r28->rules.xE = 0x20;
    temp_r28->rules.xB = -1;
    temp_r28->rules.xC = -1;
    temp_r28->rules.x0_0 = 0;

    for (i = 0; i < 6; i++) {
        gm_8016795C(&temp_r28->players[i]);
        temp_r28->players[i].stocks = 0;
        temp_r28->players[i].xE = 4;
    }

    temp_r28->players[0].c_kind = 6;
    temp_r28->players[1].c_kind = 8;
    temp_r28->players[2].c_kind = 6;
    temp_r28->players[3].c_kind = 6;

    temp_r28->players[0].slot_type = 0;
    temp_r28->players[1].slot_type = 0;
    temp_r28->players[2].slot_type = 3;
    temp_r28->players[3].slot_type = 3;

    temp_r28->players[0].xC_b0 = false;
    temp_r28->players[1].xC_b0 = false;
    temp_r28->players[2].xC_b0 = false;
    temp_r28->players[3].xC_b0 = false;

    gm_80168FC4();
}

void gm_801B14A0(MinorScene* arg0)
{
    gm_801A5618(arg0, gm_801A5244(), 0);
}

void gm_801B14DC(MinorScene* arg0)
{
    gm_801A5680(arg0, gm_801A5244());
}

void gm_801B1514(MinorScene* arg0)
{
    gm_801A5754(arg0, gm_801A5244());
}

void gm_801B154C(MinorScene* arg0)
{
    gm_801A57A8(arg0, gm_801A5244(), 0);
}

void gm_801B1588(MinorScene* arg0)
{
    gm_801A583C(arg0, gm_801A5244(), NULL, NULL);
}

void gm_801B15C8(MinorScene* arg0)
{
    s32 i;
    MatchExitInfo* mei;

    gm_801A5AF0(arg0, 4, 3);
    mei = gm_801A4284(arg0);
    for (i = 0; i < 6; i++) {
        if (mei->match_end.player_standings[i].slot_type != 3) {
            gm_80162A98(mei->match_end.player_standings[i].x20);
            gm_80162B4C(mei->match_end.player_standings[i].self_destructs);
            gm_80162A4C(mei->match_end.player_standings[i].x44);
        }
    }
}

void gm_801B1648(MinorScene* arg0)
{
    gm_801A5C3C(arg0, gm_801A5244(), NULL, NULL);
}

void gm_801B1688(MinorScene* arg0)
{
    gm_801A5EC8(arg0);
}

void gm_801B16A8(MinorScene* arg0)
{
    gm_801A5F00(arg0);
}

void gm_801B16C8(MinorScene* arg0)
{
    gm_801A5F64(arg0, gm_801A5244(), 0);
    if (gm_801743A4(gm_8047C020.match_end.result) == 0) {
        gm_801623A4(&gm_8047C020.match_end);
    }
}

void gm_801B1724(MinorScene* arg0)
{
    lb_8001C550();
    lb_8001D164(0);
}

void gm_801B174C(MinorScene* arg0)
{
    SSSData* sss;

    sss = gm_801A427C(arg0);
    sss->x1 = 0;
    sss->no_lras = 1;
    sss->force_stage_id = -1;
    sss->unk_stage = 0;
}

void gm_801B1788(MinorScene* arg0)
{
    u16 stage;
    SSSData* sss;

    sss = gm_801A4284(arg0);
    if (sss->start_game != 0) {
        gm_SetScenePendingMinor(4);
        stage = sss->data.data.rules.xE;
        gm_8018F634()->x28 = stage;
        return;
    }
    if (gm_804771C4.x4 == 0) {
        gm_8019A828();
        gm_SetScenePendingMinor(1);
        return;
    }
    gm_8018F634()->x32 = 0;
    gm_SetScenePendingMinor(2);
}

void gm_801B1810(MinorScene* arg0)
{
    gm_801A427C(arg0);
    gm_801905F0();
}

void gm_801B1834(MinorScene* arg0)
{
    MatchExitInfo* mei;

    mei = gm_801A4284(arg0);
    if (gm_801A52D0(&mei->match_end) != 0) {
        gm_8016260C(mei->match_end.x5, mei->match_end.result);
        gm_801628C4(mei->match_end.frame_count / 60,
                    gm_80162800(&mei->match_end));
    }
    if ((gm_80167140(&mei->match_end) != 0) &&
        (gm_8018F1B0(&mei->match_end) != 0))
    {
        gm_SetScenePendingMinor(5);
        return;
    }
    gm_SetScenePendingMinor(6);
}

#pragma dont_inline on
void gm_801B18D4(MinorScene* arg0)
{
    StartMeleeData* smd;
    s32 i;

    smd = gm_801A427C(arg0);

    for (i = 0; i < 4; i++) {
        smd->players[i] = gm_804876D8.players[i];
    }

    /// TODO :: figure out how to call this not inlined
    gm_801B0474(smd, &gm_80487810.match_end);
}
#pragma dont_inline reset

void gm_801B1A2C(MinorScene* arg0)
{
    MatchExitInfo* mei;

    mei = gm_801A4284(arg0);
    gm_801629B4(mei->match_end.frame_count / 60);
    gm_80166CCC(&gm_80487810.match_end, &mei->match_end);
}

void gm_801B1A84(MinorScene* arg0)
{
    ResultsMatchInfo* rmi;

    rmi = gm_801A427C(arg0);
    rmi->match_end = gm_80487810.match_end;
}

void gm_801B1AD4(MinorScene* arg0)
{
    ResultsMatchInfo* rmi;

    rmi = gm_801A427C(arg0);
    /// why is there a subi? another match end struct?
    gm_80477738.match_end = rmi->match_end;

    gm_8016247C(gm_801688AC(&rmi->match_end));
    if ((s32) gm_804771C4.x4 == 0) {
        gm_SetScenePendingMinor(1);
        gm_8018F634()->x0 = 0x1F;
        return;
    }
    gm_8019E634();
    gm_SetScenePendingMinor(2);
}

extern u8 gm_804D68C0;
extern u8 gm_804D68C1;

#pragma dont_inline on
void gm_801B1B74(MinorScene* arg0)
{
    VsModeData* vs_data;
    CSSData* css;
    PAD_STACK(8);

    vs_data = &gmMainLib_804D3EE0->unk_D10;
    css = gm_801A427C(arg0);
    if ((u8) gm_804D68C1 != 0) {
        lb_8001C550();
        lb_8001D164(0);
        lb_8001CE00();
    }
    gm_801B06B0(css, 0x17U, vs_data->data.players[0].c_kind, 1,
                vs_data->data.players[0].color, vs_data->data.players[0].xA,
                9U, gm_804D68C0);
    gm_801B07B4(css, vs_data->data.players[1].c_kind, 1,
                vs_data->data.players[1].color, vs_data->data.players[1].xA,
                0U, gm_804D68C0);
    lbDvd_800174BC();
    gm_804D68C1 = lbTime_8000AF74((u32) gm_804D68C1, 1);
}
#pragma dont_inline reset

/// #gm_801B1C24

void gm_801B1EB8(MinorScene* arg0)
{
    SSSData* sss;

    sss = gm_801A427C(arg0);
    sss->x1 = 0;
    sss->force_stage_id = -1;
    sss->unk_stage = 0;
}

void gm_801B1EEC(MinorScene* arg0)
{
    VsModeData* vs_data;
    SSSData* sss;
    s16 stage_id;

    vs_data = &gmMainLib_804D3EE0->unk_D10;
    sss = gm_801A4284(arg0);
    if (sss->start_game == 0) {
        gm_SetScenePendingMinor(0);
        return;
    }
    stage_id = sss->data.data.rules.xE;
    gm_80473814.x6 = stage_id;
    vs_data->data.rules.xE = stage_id;
    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, lbAudioAx_80026EBC((enum InternalStageId)(
                                                 u16) vs_data->data.rules.xE));
    lbAudioAx_80027168();
}

void fn_801B1F6C(int unused) {}

#pragma push
#pragma dont_inline on
void gm_801B1F70(MinorScene* arg0)
{
    VsModeData* vs;
    StartMeleeData* data;
    int i;

    vs = &gmMainLib_804D3EE0->unk_D10;
    data = gm_801A427C(arg0);
    gm_80167A64(&data->rules);

    data->rules = vs->data.rules;
    data->rules.x3C = fn_801B1F6C;

    data->rules.x3_6 = true;
    data->rules.x2_5 = false;
    data->rules.x2_1 = true;
    gm_80167A14(data->players);

    for (i = 0; i < 4; i++) {
        data->players[i] = vs->data.players[i];
        data->players[i].xC_b1 = false;
        data->players[i].xD_b2 = true;
    }

    gm_801B0620(&data->players[0], vs->data.players[0].c_kind,
                vs->data.players[0].color, 1, gm_804D68C0);

    for (i = 1; i < 4; i++) {
        PlayerInitData* var_r30 = &data->players[i];
        gm_801B0664(&data->players[i], vs->data.players[i].c_kind,
                    vs->data.players[i].color, 1,
                    vs->data.players[i].slot - 1);
        if (i - 1 != 0) {
            data->players[i].slot_type = 3;
        }
    }

    gm_8016F088(data);
    gm_80189CDC(data);
}
#pragma pop

void gm_801B2204(MinorScene* arg0)
{
    MatchExitInfo* temp_r3;

    temp_r3 = gm_801A4284(arg0);
    gm_80162968(temp_r3->match_end.frame_count / 60);
    gm_8016247C(temp_r3->match_end.player_standings[0].xE);
    gm_80163298(
        temp_r3->match_end.player_standings[0].character_kind,
        (u16) gm_80188454(
            (s8) temp_r3->match_end.player_standings[0].character_kind));
    gm_80173BC4(temp_r3->match_end.player_standings[0].character_kind);
    gm_80173EEC();
    if (gm_80173754(0x1C, gm_804D68C0) == 0) {
        gm_SetScenePendingMinor(MJ_TITLE);
    }
    lbAudioAx_80024030(1);
}

void gm_801B2298_OnInit(void)
{
    VsModeData* temp_r31 = &gmMainLib_804D3EE0->unk_D10;
    int i;

    gm_80167B50(temp_r31);

    for (i = 0; i < 4; i++) {
        temp_r31->data.players[i].color = i;
        temp_r31->data.players[i].xE = 0;
        if (i != 0) {
            temp_r31->data.players[1].c_kind = 0x21;
        }
        gm_80473814.players[i] = temp_r31->data.players[i];
    }
}

extern u8 gm_804D68C0;
extern u8 gm_804D68C1;

void gm_801B23C4_OnLoad(void)
{
    gm_804D68C0 = gm_801677F0();
    gm_804D68C1 = 0;
}

UNK_T gm_801B23F0(void)
{
    size_t size = GXGetTexBufferSize(0x280, 0x1E0, 4, 0, 0);
    lbDvd_80017740(0, 0x7D6, 4, 4, OSRoundUp32B(size), 0, 1, 0x20, 0);
    lbDvd_80017740(0, 0x7D7, 4, 4, lbSnap_8001E204(), 0, 1, 0x20, 0);
    return lbDvd_80017740(0, 0x7D8, 4, 4, lbSnap_8001E210(), 0, 1, 0x20, 0);
}

void gm_801B24B4(MinorScene* arg0)
{
    Unk80433380_48* temp_r31_2;
    struct GameCache* temp_r31;

    temp_r31 = &lbDvd_8001822C()->game_cache;
    lbDvd_800174BC();
    temp_r31->major_id = MJ_CAMERA_MODE;
    lbDvd_80018254();
    lb_8001C550();
    temp_r31_2 = lbDvd_GetPreloadedArchive(0x7D8);
    lbSnap_8001E218(lbDvd_GetPreloadedArchive(0x7D7), temp_r31_2);
}

void gm_801B2510(MinorScene* arg0)
{
    int* data = gm_801A4284(arg0);
    int temp_r0 = *data;
    if (temp_r0 == 1 || temp_r0 == 2) {
        gm_801A42F8(MJ_MENU);
    }
}

void gm_801B254C(MinorScene* arg0)
{
    VsModeData* temp_r31;
    u8* temp_r3;
    CSSData* temp_r30;
    struct GameCache* temp_r30_2;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    temp_r30 = gm_801A427C(arg0);
    temp_r3 = gm_801A5250();

    temp_r30->match_type = 1;
    temp_r30->ko_star_counts = temp_r3;

    temp_r30->data = *temp_r31;

    temp_r30_2 = &lbDvd_8001822C()->game_cache;
    lbDvd_800174BC();
    temp_r30_2->major_id = MJ_CAMERA_MODE;
    lbDvd_80018254();
}

void gm_801B25D4(MinorScene* arg0)
{
    VsModeData* temp_r31;
    u64 temp_ret;
    CSSData* temp_r3;
    int i;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    temp_r3 = gm_801A4284(arg0);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(1);
        return;
    }

    *temp_r31 = temp_r3->data;

    temp_ret = 0;
    for (i = 0; i < 6; i++) {
        temp_ret |= lbAudioAx_80026E84(temp_r3->data.data.players[i].c_kind);
    }

    lbAudioAx_80026F2C(0x14);
    lbAudioAx_8002702C(4, temp_ret);
    lbAudioAx_80027168();
}

void gm_801B26AC(MinorScene* arg0)
{
    SSSData* sss;
    VsModeData* vs;
    vs = &gmMainLib_804D3EE0->unk_950;
    sss = gm_801A427C(arg0);
    sss->data = *vs;
    gm_80167FC4(sss);
}

void gm_801B2704(MinorScene* arg0)
{
    VsModeData* temp_r31;
    SSSData* var_r3;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    var_r3 = gm_801A4284(arg0);
    if (var_r3->start_game != 0) {
        *temp_r31 = var_r3->data;
        lbAudioAx_80026F2C(0x18);
        lbAudioAx_8002702C(8, lbAudioAx_80026EBC(temp_r31->data.rules.xE));
        lbAudioAx_80027168();
        return;
    }
    gm_SetScenePendingMinor(MN_MENU);
}

void gm_801B2790(MinorScene* arg0)
{
    VsModeData* temp_r31;
    StartMeleeData* temp_r30;
    int i;

    temp_r31 = &gmMainLib_804D3EE0->unk_950;
    temp_r30 = gm_801A427C(arg0);
    gm_80167BC8(temp_r31);

    temp_r30->rules = temp_r31->data.rules;
    temp_r30->rules.x0_0 = 0;

    temp_r31->data.rules.x4_4 = false;

    temp_r30->rules.x0_6 = temp_r31->data.rules.x4_7;

    temp_r30->rules.x5_0 = true;
    temp_r30->rules.x1_2 = true;
    temp_r30->rules.x1_3 = true;
    temp_r30->rules.x2_5 = false;
    temp_r30->rules.x2_6 = false;
    temp_r30->rules.x3_1 = false;
    temp_r30->rules.x4_0 = false;

    temp_r30->rules.x38 = gm_80165268;
    temp_r30->rules.x3C = gm_80165268;
    temp_r30->rules.x40 = gm_8016BE80;
    temp_r30->rules.x44 = gmCamera_801A31FC;
    temp_r30->rules.x48 = gmCamera_801A3098;
    temp_r30->rules.x4C = gmCamera_801A30E4;

    temp_r30->rules.xD = 1;
    temp_r30->rules.x2_4 = false;

    for (i = 0; i < 6; i++) {
        temp_r30->players[i] = temp_r31->data.players[i];
        temp_r30->players[i].xD_b3 = true;
    }

    gm_801B0348(temp_r30);
    gm_8016F088(temp_r30);
    gm_80168FC4();
    lb_8001C550();
    lbSnap_8001E218(lbDvd_GetPreloadedArchive(0x7D7),
                    lbDvd_GetPreloadedArchive(0x7D8));
}

void gm_801B2AF8(MinorScene* arg0)
{
    VsModeData* temp_r30;
    u8* temp_r29;

    temp_r30 = &gmMainLib_804D3EE0->unk_950;
    temp_r29 = (void*) gm_801A5250();
    gm_80168638(&gm_80479D98.match_end);
    gm_80168710(&gm_80479D98.match_end, temp_r30);
    gm_8016247C(gm_801688AC(&gm_80479D98.match_end));
    gm_801A5258(temp_r29, &gm_80479D98.match_end);
    gm_SetScenePendingMinor(MN_MENU);
}

void gm_801B2B7C_OnInit(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_950);
}

/// #gm_801B2BA4

/// #gm_801B2D54

/// #gm_801B2F78_OnLoad

void gm_801B34B8_OnInit(void)
{
    u8* temp_r3 = gmMainLib_8015CDC8();
    temp_r3[0] = 0x21;
    temp_r3[2] = 0;
    temp_r3[1] = 3;
    temp_r3[3] = 0;
    temp_r3[4] = 0x78;
    temp_r3[5] = 0;
}

/// #gm_801B3500

/// #gm_801B3A34

/// #gm_801B3B40

void gm_801B3D44(MinorScene* arg0)
{
    struct UnkAllstarData* temp_r31 = gm_801A427C(arg0);
    gm_8017C9A8(temp_r31, gm_8017EB30(), 1);
}

/// #gm_801B3D84

/// #gm_801B3DD8

/// #gm_801B3E44

/// #gm_801B3F18

/// #gm_801B3F40

/// #gm_801B4064

/// #gm_801B4170

/// #gm_801B4254

/// #gm_801B4294

/// #gm_801B42E8

/// #gm_801B4350

/// #gm_801B4408

/// #gm_801B4430

/// #gm_801B44A0

/// #gm_801B45A4

/// #gm_801B461C

/// #gm_801B4684

/// #gm_801B4768

/// #gm_801B47FC

/// #gm_801B4860

/// #gm_801B4974

/// #gm_801B4B28

/// #gm_801B4C5C

/// #gm_801B4D34

/// #gm_801B4DAC

/// #gm_801B4E58

/// #gm_801B4EB8

/// #gm_801B4F44

/// #gm_801B4FCC

/// #gm_801B5078

/// #gm_801B50C4

/// #gm_801B518C

/// #gm_801B51CC_OnInit

/// #gm_801B5214_OnLoad

/// #gm_801B5324

/// #gm_801B5624

/// #gm_801B59AC

void fn_801B5AA8(int arg0)
{
    lbBgFlash_8002063C(0x78);
}

/// #gm_801B5ACC

/// #gm_801B5E7C

/// #gm_801B5EB4

/// #gm_801B5EE4

/// #gm_801B5F50

/// #gm_801B5FB4

void gm_801B607C(MinorScene* arg)
{
    gm_801A42E8(1);
    gm_801A42D4();
}

/// #gm_801B60A4_OnLoad

/// #gm_801B62D8_OnInit

UNK_T gm_801B6320(void)
{
    return &gmMainLib_804D3EE0->unk_530.unk_584;
}

/// #gm_801B632C

/// #gm_801B63C4

static StartMeleeData gm_80490AA8;

/// #gm_801B6428

/// #gm_801B65D4

/// #gm_801B67E8_OnInit

extern u8 gm_804D68E8;
extern u8 gm_804D68E9;

void gm_801B6808_OnLoad(void)
{
    gm_804D68E8 = gm_801677F0();
    gm_804D68E9 = 0;
}

void gm_801B6834(void)
{
    gm_80167B50(&gmMainLib_804D3EE0->unk_1490);
}

extern u8 gm_804D68F0;
extern s8 gm_804D68F1;

void gm_801B685C(void)
{
    gm_804D68F0 = gm_801677F0();
    gm_804D68F1 = 0;
    lb_8001C550();
}

/// #gm_801B688C

void gm_801B69C0(StartMeleeData* arg0)
{
    gmMainLib_8015CC34();
    arg0->rules.x0_0 = 0;
    arg0->rules.x0_6 = true;
    arg0->rules.x0_7 = true;
    arg0->rules.x10 = 0;
    arg0->rules.timer_shows_hours = true;
    arg0->rules.x4_2 = true;
    arg0->rules.x2_5 = false;
    arg0->rules.x5_0 = false;
    arg0->rules.x4_4 = false;
    arg0->rules.x4_3 = true;
    arg0->rules.x5_1 = true;
    arg0->rules.x8 = 1;
    arg0->rules.xE = 0x11D;
    arg0->rules.x18 = 0;
    arg0->rules.xB = 2;
    arg0->rules.x2C = 0.5F;
    arg0->rules.x20 = 0xFFFFFFFFFFFBFCFF;
    arg0->rules.x44 = gm_80182174;
    arg0->rules.x3_3 = true;
    arg0->rules.x3_2 = true;
    arg0->rules.x0_3 = 6;
}

/// #gm_801B6AD8

/// #gm_801B6B70

/// #gm_801B6BE8

/// #gm_801B6F44

/// #gm_801B7044

/// #gm_801B70DC

/// #gm_801B7154

/// #gm_801B74F0

/// #gm_801B75F0

/// #gm_801B7688

/// #gm_801B7700

/// #gm_801B7AA0

/// #gm_801B7B74

/// #gm_801B7C0C

/// #gm_801B7C84

/// #gm_801B8024

/// #gm_801B8110

/// #gm_801B81A8

/// #gm_801B8220

/// #gm_801B8580

/// #gm_801B863C

/// #gm_801B86D4

/// #gm_801B874C

/// #gm_801B8AF8
