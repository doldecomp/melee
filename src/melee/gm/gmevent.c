#include "gmevent.h"

#include "gm_unsplit.h"

#include "ft/forward.h"

#include "melee/cm/camera.h"
#include "melee/ft/ftbosslib.h"
#include "melee/ft/ftlib.h"
#include "melee/gm/gm_1601.h"
#include "melee/gm/gm_16F1.h"
#include "melee/gm/gm_unsplit.h"
#include "melee/gm/gmmain_lib.h"
#include "melee/gm/types.h"
#include "melee/gr/ground.h"
#include "melee/if/ifstock.h"
#include "melee/it/items/itevyoshiegg.h"
#include "melee/lb/lb_0219.h"
#include "melee/lb/lbarchive.h"
#include "melee/lb/lbaudio_ax.h"
#include "melee/lb/lbbgflash.h"
#include "melee/lb/lbdvd.h"
#include "melee/lb/types.h"
#include "melee/mn/types.h"

#include "melee/pl/forward.h"

#include "melee/pl/player.h"
#include "melee/pl/plbonuslib.h"

#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/random.h>

#ifdef MUST_MATCH
#include <MetroTRK/intrinsics.h>
#endif

struct UnkSmallLoadData {
    u8 pad[8];
};

typedef struct gm_801BAB40_src {
    /* 0x00 */ s8 c_kind;
    /* 0x01 */ u8 slot_type;
    /* 0x02 */ u8 stocks;
    /* 0x03 */ u8 color;
    /* 0x04 */ u8 x5;
    /* 0x05 */ u8 sub_color;
    /* 0x06 */ u8 team;
    /* 0x07 */ u8 xB;
    /* 0x08 */ u8 flags;
    /* 0x09 */ u8 xE;
    /* 0x0A */ u8 cpu_level;
    /* 0x0B */ u8 pad;
    /* 0x0C */ u16 x12;
    /* 0x0E */ u16 hp;
    /* 0x10 */ f32 x18;
    /* 0x14 */ f32 x1C;
    /* 0x18 */ f32 x20;
} gm_801BAB40_src;

struct gm_event_char_list {
    u8 c_kind[33];
};

/// Per-level match init data; shares its first two bytes' bitfield layout
/// with #StartMeleeRules.
struct gm_evinit {
    /* 0x00 */ u32 x0_0 : 3;
    /* 0x00 */ u32 x0_3 : 3;
    /* 0x00 */ u32 x0_6 : 1;
    /* 0x00 */ u32 x0_7 : 1;
    /* 0x01 */ u32 x1_0 : 1;
    /* 0x01 */ u32 x1_1 : 1;
    /* 0x01 */ u32 x1_2 : 1;
    /* 0x01 */ u32 x1_3 : 1;
    /* 0x01 */ u32 x1_4 : 1;
    /* 0x01 */ u32 x1_5 : 3;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ s8 unk3;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ u64 x10;
    /* 0x18 */ s32 x18;
    /* 0x1C */ f32 x1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
};

/// Per-round stage and opponent table, for levels with multiple rounds.
struct gm_evstage_table {
    /* 0x00 */ u8 count;
    /* 0x01 */ u8 pad1;
    /* 0x02 */ u16 stage[7];
    /* 0x10 */ struct gm_801BAB40_src* entries[5];
};

struct gm_evbonus {
    /* 0x00 */ s8 c_kind;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 color;
    /* 0x07 */ u8 pad7;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ u8 flags;
    /* 0x15 */ u8 x15;
    /* 0x16 */ u8 x16;
    /* 0x17 */ u8 x17;
};

struct gm_804D6900_t {
    /* 0x00 */ u8 kind;
    /* 0x01 */ u8 flags; ///< top 3 bits: player count
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ struct gm_804D6900_x4_t {
        int x0;
        intptr_t x4;
    }* x4;
    /* 0x08 */ struct gm_evinit* x8;
    /* 0x0C */ struct gm_evbonus* xC;
    /* 0x10 */ struct gm_evstage_table* x10;
    /* 0x14 */ struct gm_801BAB40_src* player_init[5];
};

/* 1BA938 */ static void gm_801BA938(struct EventData*, int lo, int hi, bool);
/* 1BAA60 */ static void onEnterCss(GameModeState*);
/* 1BAAD0 */ static void onExitCss(GameModeState*);
/* 1BAB40 */ static void gm_801BAB40(PlayerInitData*, struct gm_801BAB40_src*);
/* 1BAC9C */ static s32 gm_801BAC9C(GameModeState*, s32);
/* 1BAD70 */ static void onEnterVs(GameModeState*);
/* 1BB758 */ static void onExitVs(GameModeState*);
/* 1BBB64 */ static void gm_801BBB64(void);
/* 1BBFE8 */ static void fn_801BBFE8(void);
/* 1BC00C */ static void gm_801BC00C(void);
/* 1BC488 */ static int gm_801BC488(UNK_PARAMS);
/* 1BC4F4 */ static UNK_RET gm_801BC4F4(HSD_GObj*);
/* 1BC670 */ static void gm_801BC670(HSD_GObj*);
/* 1BC754 */ static void gm_801BC754(HSD_GObj*);
/* 1BC9E8 */ static void gm_801BC9E8(HSD_GObj*);
/* 1BCAF0 */ static void gm_801BCAF0(HSD_GObj*);
/* 1BCC9C */ static void gm_801BCC9C(HSD_GObj*);
/* 1BCF20 */ static void gm_801BCF20(HSD_GObj*);
/* 1BCF40 */ static void gm_801BCF40(HSD_GObj*);
/* 1BD028 */ static void gm_801BD028(HSD_GObj*);
/* 1BD164 */ static void gm_801BD164(HSD_GObj*);
/* 1BD30C */ static void gm_801BD30C(HSD_GObj*);
/* 1BD44C */ static void gm_801BD44C(HSD_GObj*);
/* 1BD46C */ static void gm_801BD46C(HSD_GObj*);
/* 1BD658 */ static void gm_801BD658(HSD_GObj*);
/* 1BD7FC */ static void gm_801BD7FC(HSD_GObj*);
/* 1BD93C */ static void gm_801BD93C(HSD_GObj*);
/* 1BDAD4 */ static void gm_801BDAD4(HSD_GObj*);
/* 1BDAF4 */ static void gm_801BDAF4(HSD_GObj*);
/* 1BDC08 */ static void gm_801BDC08(HSD_GObj*);
/* 1BDD44 */ static void gm_801BDD44(HSD_GObj*);
/* 1BDE94 */ static void gm_801BDE94(HSD_GObj*);
/* 1BE37C */ static void gm_801BE37C(HSD_GObj*);
/* 1BE39C */ static void gm_801BE39C(HSD_GObj*);
/* 1BE618 */ static void gm_801BE618(HSD_GObj*);
/* 1BE638 */ static void gm_801BE638(HSD_GObj*);
/* 1BEA10 */ static void gm_801BEA10(int);
/* 1BEA4C */ static void gm_801BEA4C(int);
/* 1BEA88 */ static void gm_801BEA88(int, int);
/* 1BEAF0 */ static void gm_801BEAF0(int);
/* 1BEB2C */ static void gm_801BEB2C(int);
/* 497758 */ static CSSData css_data;
/* 4978A0 */ static StartMeleeData vs_enter_data;
/* 4979D8 */ static MatchExitInfo vs_exit_data[2];
/* 4D6900 */ static struct gm_804D6900_t** gm_804D6900[2];

GameModeState gm_Mode_Event_States[] = {
    {
        0,
        lbDvdPreload_3,
        0,
        onEnterCss,
        onExitCss,
        {
            GS_CSS,
            &css_data,
            &css_data,
        },
    },
    {
        1,
        lbDvdPreload_3,
        0,
        onEnterVs,
        onExitVs,
        {
            GS_VS,
            &vs_enter_data,
            &vs_exit_data,
        },
    },
    { -1 },
};

void gm_801BA8FC(void)
{
    lbArchive_LoadSymbols("GmEvent.dat", &gm_804D6900,
                          "sqEventInitDataLevelTbl", 0);
}

void gm_801BA938(struct EventData* arg0, int lo, int hi, bool arg3)
{
    struct GameCache* cache = &lbDvd_GetPreloadCacheScene()->game_cache;
    u64 mask;
    s8 char_id;
    int i;

    for (i = lo; i < hi; i++) {
        char_id = arg0->x4C[i];
        if (char_id != CHKIND_NONE) {
            cache->entries[i].char_id = char_id;
            cache->entries[i].color = arg0->x50[i];
            if (arg0->x45 != 0 && i > 0 && arg0->x4C[i] == 4) {
                cache->entries[i].x5 = 0;
            }
        }
    }

    if (arg3 != 0) {
        cache->stkind = arg0->x48;
    }
    lbDvd_80018254();
    mask = 0;
    for (i = lo; i < hi; i++) {
        if (arg0->x4C[i] != CHKIND_NONE) {
            mask |= lbAudioAx_80026E84(arg0->x4C[i]);
        }
    }
    mask |= lbAudioAx_80026EBC(arg0->x48);
    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC, mask);
    lbAudioAx_80027168();
}

void onEnterCss(GameModeState* arg0)
{
    struct EventData* temp_r31 = &gmMainLib_804D3EE0->unk_530;
    CSSData* css = gm_GetGameSceneLoadData(arg0);
    PAD_STACK(8);

    gm_801B06B0(css, 0xE, temp_r31->x2, 0, temp_r31->x3, temp_r31->x4, 0,
                temp_r31->x6);
    if (temp_r31->x44 == 1) {
        gm_801BA938(temp_r31, 1, 4, true);
    }
}

void onExitCss(GameModeState* arg0)
{
    CSSData* temp_r3;
    struct EventData* temp_r31;

    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_GetGameSceneLeaveData(arg0);
    if (temp_r3->pending_scene_change == 2) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return;
    }
    gm_801B0730(temp_r3, &temp_r31->x2, NULL, &temp_r31->x3, &temp_r31->x4,
                NULL);
    temp_r31->x8 = -1;
    temp_r31->x9 = -1;
    temp_r31->xA = -1;
}

void gm_801BAB40(PlayerInitData* arg0, gm_801BAB40_src* src)
{
    gm_8016795C(arg0);
    arg0->c_kind = src->c_kind;
    arg0->slot_type = src->slot_type;
    arg0->stocks = src->stocks;
    arg0->color = src->color;
    arg0->slot = 0;
    arg0->x5 = src->x5;
    arg0->sub_color = src->sub_color;
    arg0->handicap = 9;
    arg0->team = src->team;
    arg0->xA = 0x78;
    arg0->xB = src->xB;
    arg0->xC_b0 = 0;
    arg0->xC_b1 = (src->flags & 0x80) >> 7;
    arg0->xC_b2 = (src->flags & 0x40) >> 6;
    arg0->xC_b3 = (src->flags & 0x20) >> 5;
    arg0->xC_b4 = (src->flags & 0x10) >> 4;
    arg0->xC_b6 = (src->flags & 0x08) >> 3;
    arg0->xC_b7 = (src->flags & 0x04) >> 2;
    arg0->xD_b1 = 0;
    arg0->xD_b2 = 0;
    arg0->xD_b4 = 0;
    arg0->xE = src->xE;
    arg0->cpu_level = src->cpu_level;
    arg0->x10 = 0;
    arg0->x12 = src->x12;
    arg0->hp = src->hp;
    arg0->x18 = src->x18;
    arg0->x1C = src->x1C;
    arg0->x20 = src->x20;
}

s32 gm_801BAC9C(GameModeState* arg0, s32 arg1)
{
    UNUSED u8 _[8];
    u8 chars[CHKIND_MAX];
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    StartMeleeData* data = gm_GetGameSceneLoadData(arg0);
    s32 i;
    s32 found;
    s32 count = 0;
    s32 k;
    struct gm_event_char_list* src =
        (struct gm_event_char_list*) (*gm_804D6900)[ev->unk_535]->x4;
    PAD_STACK(8);

    for (i = 0; i < CHKIND_MAX; i++) {
        u8* ptr = &src->c_kind[i];
        u8 c = *ptr;
        if ((s32) c == CHKIND_MAX) {
            break;
        }
        found = 0;
        for (k = 0; k < arg1; k++) {
            if (data->players[k].c_kind == (s8) *ptr) {
                found++;
            }
        }
        if (found == 0) {
            chars[count] = c;
            count++;
        }
    }
    return chars[HSD_Randi(count)];
}

/// Accessor for the event data block inside gmMainLib_804D3EE0.
static inline struct EventData* gm_GetEventData(void)
{
    return &gmMainLib_804D3EE0->unk_530;
}

static inline u8 gm_GetNextColor(u8 color)
{
    if (color <= 2) {
        color++;
    } else {
        color = 0;
    }
    return color;
}

void onEnterVs(GameModeState* arg0)
{
    struct EventData* ev = gm_GetEventData();
    StartMeleeData* md = gm_GetGameSceneLoadData(arg0);
    u8 level = ev->unk_535;
    s32 player_idx;
    struct gm_804D6900_t** levels;
    gm_803DF94C_t** event_info = gm_803DF94C;
    struct GameCache* cache;
    int i;
    PAD_STACK(0x10);

    lbArchive_LoadSymbols("GmEvent.dat", &gm_804D6900,
                          "sqEventInitDataLevelTbl", 0);
    levels = gm_804D6900[0];
    gm_80167A64(&md->rules);
    md->rules.match_mode = levels[level]->x8->x0_0;
    md->rules.x0_3 = levels[level]->x8->x0_3;
    md->rules.x0_6 = levels[level]->x8->x0_6;
    md->rules.timer_counts_up = levels[level]->x8->x0_7;
    md->rules.x1_0 = 1;
    md->rules.x1_1 = 0;
    md->rules.x1_2 = 0;
    md->rules.x1_3 = 0;
    md->rules.timer_shows_hours = 0;
    md->rules.friendly_fire = levels[level]->x8->x1_1;
    md->rules.x2_2 = 0;
    md->rules.single_button = 0;
    md->rules.disable_pausing = 0;
    md->rules.x2_5 = levels[level]->x8->x1_2;
    md->rules.x3_1 = 1;
    md->rules.x3_2 = 1;
    md->rules.x3_3 = 1;
    md->rules.x3_4 = 1;
    md->rules.x3_5 = 1;
    md->rules.x3_7 = 0;
    md->rules.x4_2 = 0;
    md->rules.x4_3 = 1;
    md->rules.x4_4 = 0;
    md->rules.x4_6 = 0;
    md->rules.x4_7 = 0;
    md->rules.x5_0 = 1;
    md->rules.x5_1 = 0;
    md->rules.x5_2 = levels[level]->x8->x1_3;
    md->rules.x5_3 = levels[level]->x8->x1_4;
    md->rules.x7 = 0;
    md->rules.is_teams = levels[level]->x8->unk2;
    md->rules.x9 = 0;
    md->rules.xA = 0;
    md->rules.xB = levels[level]->x8->unk3;
    md->rules.xC = levels[level]->x8->unk4;
    md->rules.xD = 0x6E;
    md->rules.stkind = levels[level]->x8->unk6;
    md->rules.time_limit = levels[level]->x8->unk8;
    md->rules.x14 = 0;
    md->rules.x18 = 0;
    md->rules.x20 = levels[level]->x8->x10;
    md->rules.x28 = levels[level]->x8->x18;
    md->rules.x30 = levels[level]->x8->x1C;
    md->rules.x34 = levels[level]->x8->unk20;
    md->rules.x44 = fn_801BBFE8;
    if (md->rules.timer_counts_up & 1) {
        ev->xB_0 = 1;
    }
    if (levels[level]->x8->x1_0) {
        ev->xB_6 = 1;
    }
    if (levels[level]->x8->unk24 != 1.0f) {
        ev->x1C = levels[level]->x8->unk24;
    }
    if (levels[level]->kind == 2) {
        u16 stage;
        ev->xB_4 = 1;
        stage = levels[level]->x10->stage[ev->x20];
        md->rules.stkind = stage;
        ev->x48 = stage;
        if (ev->x20 > 0) {
            md->rules.x1_2 = 1;
            md->rules.x1_3 = 1;
            md->rules.time_limit = ev->x2C;
        }
        gm_8016A92C(&md->rules);
    }

    for (i = 0; i < 6; i++) {
        md->players[i].slot_type = Gm_PKind_NA;
    }

    for (player_idx = 0; player_idx < ((levels[level]->flags >> 5) & 7);
         player_idx++)
    {
        while (levels[level]->player_init[player_idx] == NULL) {
            player_idx++;
        }
        gm_801BAB40(&md->players[player_idx],
                    levels[level]->player_init[player_idx]);
        if (player_idx == 0) {
            u8 c;
            gm_801B05F4(md->players, ev->x6);
            ev->x7 = md->players[0].team;
            if (md->players[0].c_kind == CHKIND_NONE) {
                md->players[0].c_kind = ev->x2;
                md->players[0].color = ev->x3;
                md->players[0].xA = ev->x4;
            }
            c = md->players[0].c_kind;
            ev->x0 = c;
            ev->x4C[0] = c;
            c = md->players[0].color;
            ev->x1 = c;
            ev->x50[0] = c;
            md->players[0].xC_b0 = gm_801677F8(ev->x6, md->players[0].xA);
        } else {
            s8 c_kind;
            if (levels[level]->player_init[player_idx]->team == 0) {
                md->players[player_idx].team = md->players[0].team;
                md->players[player_idx].xD_b1 = 1;
            }
            if (levels[level]->player_init[player_idx]->c_kind == CHKIND_NONE)
            {
                s8* t = &ev->x8 + player_idx - 1;
                s8 v = *t;
                if (v == -1) {
                    u8 nv = gm_801BAC9C(arg0, player_idx);
                    md->players[player_idx].c_kind = nv;
                    *t = md->players[player_idx].c_kind;
                } else {
                    md->players[player_idx].c_kind = v;
                }
            }
            c_kind = md->players[player_idx].c_kind;
            if (c_kind == md->players[0].c_kind) {
                u8 c = md->players[player_idx].color;
                if (c == md->players[0].color) {
                    md->players[player_idx].color = gm_GetNextColor(c);
                }
            }
            if (md->players[0].c_kind == CKIND_SEAK &&
                md->players[player_idx].c_kind == CKIND_ZELDA)
            {
                u8 c = md->players[player_idx].color;
                if (c == md->players[0].color) {
                    md->players[player_idx].color = gm_GetNextColor(c);
                }
            }
            if (player_idx < 4) {
                ev->x4C[player_idx] = md->players[player_idx].c_kind;
                ev->x50[player_idx] = md->players[player_idx].color;
            }
        }
    }

    if (levels[level]->kind == 2) {
        if (ev->x20 > 0) {
            s8 c;
            md->players[0].stocks = (s8) ev->x24;
            md->players[0].x10 = ev->x28;
            md->players[0].xC_b1 = 0;
            c = ev->x38;
            if (c != 0x21) {
                md->players[0].c_kind = c;
                ev->x0 = c;
                ev->x4C[0] = c;
            }
        }
        gm_801BAB40(&md->players[1], levels[level]->x10->entries[ev->x20]);
        if (md->players[1].c_kind == md->players[0].c_kind) {
            u8 c = md->players[1].color;
            if (c == md->players[0].color) {
                md->players[1].color = gm_GetNextColor(c);
            }
        }
        if (md->players[0].c_kind == CKIND_SEAK &&
            md->players[1].c_kind == CKIND_ZELDA)
        {
            u8 c = md->players[1].color;
            if (c == md->players[0].color) {
                md->players[1].color = gm_GetNextColor(c);
            }
        }
        ev->x4C[1] = md->players[1].c_kind;
        ev->x50[1] = md->players[1].color;
    }
    if (level == 0x2B) {
        s32 c2 = ev->x4C[2];
        u8 c = ev->x50[2];
        /// @todo remove void cast hack
        /// maybe the inline that will resolve the pad stack will fix this?
        (void) c2;
        if (ev->x4C[0] == c2 && ev->x50[0] == c) {
            ev->x50[2] = gm_GetNextColor(c);
        }
    }
    if (level == 0x31) {
        md->players[1].spawn_dir = 1;
        md->players[2].spawn_dir = -1;
        md->players[1].xD_b0 = 1;
        md->players[2].xD_b0 = 1;
        md->players[1].xD_b2 = 1;
        md->players[2].xD_b2 = 1;
    }
    if (levels[level]->kind == 1) {
        struct gm_evbonus* bonus;
        int x5_flag;
        s8 k;
        u8 color2;
        ev->xB_3 = 1;
        bonus = levels[level]->xC;
        if (bonus->x5 == 1) {
            x5_flag = 1;
            if ((s8) ev->x0 == bonus->c_kind) {
                u8 c;
                if (ev->x1 == (c = bonus->color)) {
                    ev->x50[1] = gm_GetNextColor(c);
                }
            }
        } else {
            x5_flag = 0;
        }
        bonus = levels[level]->xC;
        k = bonus->c_kind;
        if (k == 4) {
            color2 = bonus->x17;
        } else {
            color2 = 0;
        }
        gm_8016A22C(k, 0x21, 0x21, ev->x50[1], 0, 0, x5_flag, 0, color2,
                    ev->x0, ev->x1, bonus->x1, bonus->x2, bonus->x3, bonus->x4,
                    0, 1, bonus->x8, bonus->xC);
        gm_8016A414(levels[level]->xC->x10);
        gm_8016A21C(&md->rules);
        if ((levels[level]->xC->flags >> 7) & 1) {
            gm_8016A434();
        }
        if (event_info[level]->x4 != NULL) {
            gm_8016A404((s32) event_info[level]->x4);
        }
        if (levels[level]->xC->x15 != 0) {
            gm_8016A424(levels[level]->xC->x15);
        }
    }
    cache = &lbDvd_GetPreloadCacheScene()->game_cache;
    switch (ev->x44) {
    case 0:
        gm_801BA938(ev, 0, 4, 1);
        break;
    case 1:
        gm_801BA938(ev, 0, 4, 1);
        break;
    case 2:
        cache->entries[0].char_id = ev->x4C[0];
        cache->entries[0].color = ev->x50[0];
        lbDvd_80018254();
        lbDvd_80018C2C(0xC7);
        gm_801BA938(ev, 1, 4, 1);
        break;
    case 3:
        lbDvd_80018C2C(0xC7);
        gm_801BA938(ev, 1, 4, 1);
        break;
    case 4:
        lbDvd_80018C6C();
        cache->entries[0].char_id = ev->x4C[0];
        cache->entries[0].color = ev->x50[0];
        lbDvd_80018254();
        lbDvd_80017700(4);
        gm_801BA938(ev, 1, 4, 1);
        break;
    }
    gm_8016F088(md);
    gm_80168F88();
}

void onExitVs(GameModeState* arg0)
{
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    MatchExitInfo* exit = gm_GetGameSceneLeaveData(arg0);
    u8 stage = ev->unk_535;
    u8 b;
    u8 kind;
    s32 t;

    gm_8016A164();
    if (exit->match_end.result == OUTCOME_RETRY) {
        s32 do_save = 0;
        if (ev->x20 != 0) {
            do_save = 1;
        }
        if (stage == 0x31) {
            do_save = 0;
        }
        ev->xB_5 = 0;
        ev->x20 = 0;
        ev->x24 = 0;
        ev->x28 = 0;
        ev->x2C = 0;
        ev->x30 = 0;
        ev->x34 = 0;
        ev->x38 = 0x21;
        ev->x3C = 0;
        ev->x40 = 0;
        gm_801BBB64();
        if (do_save != 0) {
            struct GameCache* gc = &lbDvd_GetPreloadCacheScene()->game_cache;
            lbDvd_80018C6C();
            gc->entries[0].char_id = (s8) ev->x0;
            gc->entries[0].color = ev->x1;
            lbDvd_80018254();
            lbDvd_80017700(4);
        }
        gm_SetPendingSceneIndex(1);
        return;
    }
    if (exit->match_end.result == OUTCOME_NO_CONTEST) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
        return;
    }
    ev->x3C += gm_80168940(&vs_exit_data[0].match_end);
    ev->x40 += (s32) exit->match_end.frame_count;
    b = ((u8*) ev)[0xB];
    if (((b >> 3) & 1) && ((b >> 5) & 1)) {
        ev->x24 = vs_exit_data[0].match_end.player_standings[0].stocks;
        ev->x28 = vs_exit_data[0].match_end.player_standings[0].percent;
        ev->xB_2 = 0;
        ev->xB_5 = 0;
        t = ev->x20;
        ev->x20 = t + 1;
        gm_801BBB64();
        gm_SetPendingSceneIndex(1);
        return;
    }
    if (ev->xB_1) {
        u32 cur = ev->xC;
        u32 best = gmMainLib_8015CF5C(stage);
        s32 upd = 0;
        if (ev->xB_6) {
            if (best == 0 || cur < best) {
                best = cur;
                upd = 1;
            }
        } else if (cur > best) {
            best = cur;
            upd = 1;
        }
        if (upd != 0) {
            gmMainLib_8015CF70(stage, best);
        }
        gmMainLib_8015CEB4(stage);
    }
    gm_8016247C(ev->x3C);
    gm_80162968((u32) ev->x40 / 60);
    if (ev->xB_1) {
        kind = gm_801732D8(ev->unk_535);
    } else {
        kind = CHKIND_MAX;
    }
    if (ev->unk_535 == gm_801BEBC0(0x32) &&
        exit->match_end.player_standings[0].stocks == 3)
    {
        gmMainLib_8015CF84();
    }
    if (ev->xB_1) {
        u16 sid = gm_8017335C();
        if (sid != 0x148) {
            gm_80164504(sid);
        }
    }
    if (ev->xB_1) {
        gm_80173D3C(ev->unk_535);
    }
    gm_80173EEC();
    gm_80172898(0x10);
    if (kind != CHKIND_MAX) {
        gm_801736E8(ev->x0, ev->x1, ev->x6, ev->x4, kind, GM_MENU);
        gm_ChangeGameModeAfterCurrentScene(GM_CHALLENGER_APPROACH);
        return;
    }
    if (gm_80173754(1, ev->x6) == 0) {
        gm_ChangeGameModeAfterCurrentScene(GM_MENU);
    }
}

void gm_Mode_Event_OnInit(void)
{
    struct EventData* temp_r6;
    int i;

    temp_r6 = &gmMainLib_804D3EE0->unk_530;
    gmMainLib_804D3EE0->unk_530.x0 = 0;
    temp_r6->x1 = 0;
    temp_r6->x2 = 0x21;
    temp_r6->x3 = 0;
    temp_r6->x4 = 0x78;
    temp_r6->unk_535 = 0;
    temp_r6->x6 = 0;
    temp_r6->x7 = 0;
    temp_r6->x8 = -1;
    temp_r6->x9 = -1;
    temp_r6->xA = -1;
    temp_r6->xB_0 = false;
    temp_r6->xB_1 = false;
    temp_r6->xB_2 = false;
    temp_r6->xB_3 = false;
    temp_r6->xB_4 = false;
    temp_r6->xB_5 = false;
    temp_r6->xB_6 = false;
    temp_r6->xC = 0;
    temp_r6->x10 = 0;
    temp_r6->x14 = 0;
    temp_r6->x18 = 0;
    temp_r6->x1C = 1.0F;
    temp_r6->x20 = 0;
    temp_r6->x24 = 0;
    temp_r6->x28 = 0;
    temp_r6->x2C = 0;
    temp_r6->x30 = 0;
    temp_r6->x34 = 0;
    temp_r6->x38 = 0x21;
    temp_r6->x3C = 0;
    temp_r6->x40 = 0;
    temp_r6->x44 = -1;
    temp_r6->x45 = 0;
    temp_r6->x48 = 0;

    for (i = 0; i < 4; i++) {
        temp_r6->x4C[i] = 0x21;
        temp_r6->x50[i] = 0;
    }
}

static inline void gm_801BBB64_inline(struct EventData* ev)
{
    struct gm_804D6900_t** tbl = gm_804D6900[0];
    u8 idx = ev->unk_535;
    if ((*tbl[idx]->player_init)->c_kind != CHKIND_NONE) {
        ev->x44 = 0;
    } else {
        ev->x44 = 1;
    }
}

void gm_801BBB64(void)
{
    struct gm_804D6900_t** pp;
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    struct gm_804D6900_t** tbl = gm_804D6900[0];
    u8 idx = ev->unk_535;
    gm_801BAB40_src* player_init;
    gm_801BAB40_src* event_entry;
    struct gm_804D6900_x4_t* x4;
    int i;

    gm_801BBB64_inline(ev);

    pp = &tbl[idx];
    ev->x48 = (*pp)->x8->unk6;

    for (i = 0; i < 4; i++) {
        player_init = (*pp)->player_init[i];
        if (player_init != NULL) {
            ev->x4C[i] = player_init->c_kind;
            ev->x50[i] = (*pp)->player_init[i]->color;
        } else {
            ev->x4C[i] = CHKIND_NONE;
            ev->x50[i] = 0;
        }
    }

    if ((*pp)->kind == 1) {
        ev->x4C[1] = (*pp)->xC->c_kind;
        if ((*pp)->xC->x5 == 1) {
            ev->x50[1] = (*pp)->xC->color;
        } else {
            ev->x50[1] = 0xFF;
        }
        if ((s32) (*pp)->xC->x17 == 1) {
            ev->x45 = 1;
        } else {
            ev->x45 = 0;
        }
    } else {
        ev->x45 = 0;
    }

    switch (idx) {
    case 9:
    case 19:
    case 29:
    case 39:
    case 48:
        if (ev->x20 == 0) {
            ev->x44 = 3;
        } else {
            ev->x44 = 4;
        }
        event_entry = (*pp)->x10->entries[ev->x20];
        ev->x4C[1] = event_entry->c_kind;
        event_entry = (*pp)->x10->entries[ev->x20];
        ev->x50[1] = event_entry->color;
        return;
    case 35:
        if (ev->x20 == 0) {
            ev->x44 = 2;
            event_entry = (*pp)->x10->entries[0];
            ev->x4C[1] = event_entry->c_kind;
            event_entry = (*pp)->x10->entries[0];
            ev->x50[1] = event_entry->color;
            event_entry = (*pp)->x10->entries[2];
            ev->x4C[2] = event_entry->c_kind;
            event_entry = (*pp)->x10->entries[2];
            ev->x50[2] = event_entry->color;
            event_entry = (*pp)->x10->entries[3];
            ev->x4C[3] = event_entry->c_kind;
            event_entry = (*pp)->x10->entries[3];
            ev->x50[3] = event_entry->color;
            return;
        }
        if (ev->x20 == 1) {
            ev->x44 = 4;
            event_entry = (*pp)->x10->entries[1];
            ev->x4C[1] = event_entry->c_kind;
            event_entry = (*pp)->x10->entries[1];
            ev->x50[1] = event_entry->color;
            event_entry = (*pp)->x10->entries[4];
            ev->x4C[2] = event_entry->c_kind;
            event_entry = (*pp)->x10->entries[4];
            ev->x50[2] = event_entry->color;
            return;
        }
        break;
    case 43:
        x4 = (*pp)->x4;
        event_entry = (gm_801BAB40_src*) x4->x4;
        ev->x4C[2] = event_entry->c_kind;
        event_entry = (gm_801BAB40_src*) x4->x4;
        ev->x50[2] = event_entry->color;
        return;
    }
}

void gm_Mode_Event_OnLoad(void)
{
    struct EventData* temp_r30;
    struct gm_804D6900_t** temp_r29;
    u8 temp_r28;
    u8 temp_r3;
    PAD_STACK(8);

    temp_r30 = &gmMainLib_804D3EE0->unk_530;
    gm_801BA8FC();

    temp_r29 = gm_804D6900[0];
    temp_r28 = temp_r30->unk_535;
    temp_r30->x0 = 0;
    temp_r30->x1 = 0;
    temp_r30->x6 = gm_801677F0();
    temp_r30->x7 = 0;
    temp_r30->xB_0 = false;
    temp_r30->xB_1 = false;
    temp_r30->xB_2 = false;
    temp_r30->xB_3 = false;
    temp_r30->xB_4 = false;
    temp_r30->xB_5 = false;
    temp_r30->xB_6 = false;
    temp_r30->xC = 0;
    temp_r30->x10 = 0;
    temp_r30->x14 = 0;
    temp_r30->x18 = 0;
    temp_r30->x1C = 1.0F;
    temp_r30->x20 = 0;
    temp_r30->x24 = 0;
    temp_r30->x28 = 0;
    temp_r30->x2C = 0;
    temp_r30->x30 = 0;
    temp_r30->x34 = 0;
    temp_r30->x38 = 0x21;
    temp_r30->x3C = 0;
    temp_r30->x40 = 0;
    gm_801BBB64();
    if (temp_r29[temp_r28]->player_init[0]->c_kind != 0x21) {
        gm_SetSceneIndex(1);
    }
}

void gm_Mode_Event_OnUnload(void) {}

void fn_801BBFE8(void)
{
    gm_GetCurrentGameMode();
    gm_801BC00C();
}

static inline void gm_801BC00C_inline(gm_801BAB40_src* event_entry)
{
    u8 ckind = event_entry->c_kind;
    u8 costume = event_entry->color;
    struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;

    if ((s8) ev2->x0 == (s8) ckind && ev2->x1 == costume) {
        if (costume <= 2) {
            costume += 1;
        } else {
            costume = 0;
        }
    }
    gm_8016A9E8(ckind, (s8) costume);
}

static inline s8 gm_801BC00C_GetCharacter(gm_801BAB40_src* event_entry)
{
    return Player_800325C8((CharacterKind) event_entry->c_kind, 0);
}

static inline CharacterKind
gm_801BC00C_GetCharacterKind(gm_801BAB40_src* event_entry)
{
    return (CharacterKind) event_entry->c_kind;
}

void gm_801BC00C(void)
{
    struct gm_804D6900_t** event_levels;
    struct EventData* ev = gm_GetEventData();
    u8 idx = ev->unk_535;
    gm_803DF94C_t** event_info = gm_803DF94C;
    gm_801BAB40_src* event_entry;
    u8 ckind;
    u8 costume;
    lbl_8046B6A0_t* mi;
    s32 i;
    s8 chr;
    PAD_STACK(0x38);

    ev->xB_1 = 0;
    ev->x10 = 0;
    ev->x14 = 0;
    ev->x18 = 0;

    switch (idx) {
    case 4:
    case 9:
    case 12:
    case 15:
    case 19:
    case 21:
    case 23:
    case 27:
    case 29:
    case 35:
    case 39:
    case 43:
    case 44:
    case 48:
        lbArchive_LoadSymbols("GmEvent.dat", &gm_804D6900,
                              "sqEventInitDataLevelTbl", 0);
        event_levels = gm_804D6900[0];
        break;
    }

    switch (idx) {
    case 35:
        if (ev->x20 == 0) {
            event_entry = event_levels[idx]->x10->entries[2];
            ftLib_80087508(
                Player_800325C8((CharacterKind) event_entry->c_kind, 0),
                event_entry->color);
            event_entry = event_levels[idx]->x10->entries[3];
            ftLib_80087508(
                Player_800325C8((CharacterKind) event_entry->c_kind, 0),
                event_entry->color);
        } else {
            event_entry = event_levels[idx]->x10->entries[4];
            ftLib_80087508(
                Player_800325C8(gm_801BC00C_GetCharacterKind(event_entry), 0),
                event_entry->color);
        }
        break;
    case 43:
        chr = gm_801BC00C_GetCharacter(
            (gm_801BAB40_src*) event_levels[idx]->x4->x4);
        ftLib_80087508(chr, ev->x50[2]);
        if ((s8) ev->x0 == 4) {
            Player_80031DA8(chr, ev->x1);
        }
        break;
    }

    switch (idx) {
    case 9:
    case 19:
    case 29:
    case 35:
    case 39:
    case 48:
        if (ev->x20 > 0) {
            mi = gm_16AE_GetUnkData_1();
            mi->timer_seconds = ev->x2C;
            mi->unk_2C = ev->x30;
        }
        break;
    }

    switch (idx) {
    case 9:
    case 19:
    case 29:
    case 39:
    case 48:
        for (i = ev->x20; i < event_levels[idx]->x10->count; i++) {
            event_entry = event_levels[idx]->x10->entries[i];
            gm_801BC00C_inline(event_entry);
        }
        break;
    case 35:
        if (ev->x20 == 0) {
            event_entry = event_levels[idx]->x10->entries[0];
            gm_801BC00C_inline(event_entry);
            event_entry = event_levels[idx]->x10->entries[2];
            gm_801BC00C_inline(event_entry);
            event_entry = event_levels[idx]->x10->entries[3];
            gm_801BC00C_inline(event_entry);
        }
        if (ev->x20 <= 1) {
            event_entry = event_levels[idx]->x10->entries[1];
            gm_801BC00C_inline(event_entry);
            event_entry = event_levels[idx]->x10->entries[4];
            gm_801BC00C_inline(event_entry);
        }
        break;
    }

    if (idx == 0x24) {
        lbBgFlash_80021A10(0.2f);
    }
    Camera_80030E34(ev->x1C);
    HSD_GObj_SetupProc(GObj_Create(0xF, 0x11, 0), event_info[idx]->x0, 0x15);
}

static u8 gm_803DF918[] = {
    0x00, 0x11, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
    0x0B, 0x0C, 0x0D, 0x24, 0x0F, 0x10, 0x01, 0x12, 0x13, 0x14, 0x15,
    0x1A, 0x17, 0x18, 0x19, 0x16, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x2F, 0x23, 0x0E, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
    0x2C, 0x2D, 0x2E, 0x22, 0x30, 0x31, 0x32,
};

static gm_803DF94C_t gm_804D4330 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4338 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4340 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4348 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4350 = { gm_801BC9E8, NULL };
static gm_803DF94C_t gm_804D4358 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4360 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4368 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4370 = { gm_801BCAF0, NULL };
static gm_803DF94C_t gm_804D4378 = { gm_801BCF20, NULL };
static gm_803DF94C_t gm_804D4380 = { gm_801BCF40, NULL };
static gm_803DF94C_t gm_804D4388 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4390 = { gm_801BD028, NULL };
static gm_803DF94C_t gm_804D4398 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D43A0 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D43A8 = { gm_801BC754, gm_801BEA10 };
static gm_803DF94C_t gm_804D43B0 = { gm_801BD164, NULL };
static gm_803DF94C_t gm_804D43B8 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D43C0 = { gm_801BD30C, NULL };
static gm_803DF94C_t gm_804D43C8 = { gm_801BD44C, NULL };
static gm_803DF94C_t gm_804D43D0 = { gm_801BD46C, NULL };
static gm_803DF94C_t gm_804D43D8 = { gm_801BD658, gm_801BEA4C };
static gm_803DF94C_t gm_804D43E0 = { gm_801BC754, NULL };

/// @todo Fix this callback signature
static gm_803DF94C_t gm_804D43E8 = {
    gm_801BC754,
    (void (*)(int))(void*) gm_801BEA88,
};

static gm_803DF94C_t gm_804D43F0 = { gm_801BD7FC, NULL };
static gm_803DF94C_t gm_804D43F8 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4400 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4408 = { gm_801BC754, gm_801BEAF0 };
static gm_803DF94C_t gm_804D4410 = { gm_801BD93C, NULL };
static gm_803DF94C_t gm_804D4418 = { gm_801BDAD4, NULL };
static gm_803DF94C_t gm_804D4420 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4428 = { gm_801BDAF4, NULL };
static gm_803DF94C_t gm_804D4430 = { gm_801BDC08, NULL };
static gm_803DF94C_t gm_804D4438 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4440 = { gm_801BDD44, NULL };
static gm_803DF94C_t gm_804D4448 = { gm_801BDE94, NULL };
static gm_803DF94C_t gm_804D4450 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4458 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4460 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4468 = { gm_801BE37C, NULL };
static gm_803DF94C_t gm_804D4470 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4478 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4480 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D4488 = { gm_801BE39C, NULL };
static gm_803DF94C_t gm_804D4490 = { gm_801BC754, gm_801BEB2C };
static gm_803DF94C_t gm_804D4498 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D44A0 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D44A8 = { gm_801BC754, NULL };
static gm_803DF94C_t gm_804D44B0 = { gm_801BE618, NULL };
static gm_803DF94C_t gm_804D44B8 = { gm_801BE638, NULL };
static gm_803DF94C_t gm_804D44C0 = { gm_801BC754, NULL };

/// @todo move above usage
gm_803DF94C_t* gm_803DF94C[] = {
    &gm_804D4330, &gm_804D43B8, &gm_804D4340, &gm_804D4348, &gm_804D4350,
    &gm_804D4358, &gm_804D4360, &gm_804D4368, &gm_804D4370, &gm_804D4378,
    &gm_804D4380, &gm_804D4388, &gm_804D4390, &gm_804D4398, &gm_804D4450,
    &gm_804D43A8, &gm_804D43B0, &gm_804D4338, &gm_804D43C0, &gm_804D43C8,
    &gm_804D43D0, &gm_804D43D8, &gm_804D4400, &gm_804D43E8, &gm_804D43F0,
    &gm_804D43F8, &gm_804D43E0, &gm_804D4408, &gm_804D4410, &gm_804D4418,
    &gm_804D4420, &gm_804D4428, &gm_804D4430, &gm_804D4438, &gm_804D44A8,
    &gm_804D4448, &gm_804D43A0, &gm_804D4458, &gm_804D4460, &gm_804D4468,
    &gm_804D4470, &gm_804D4478, &gm_804D4480, &gm_804D4488, &gm_804D4490,
    &gm_804D4498, &gm_804D44A0, &gm_804D4440, &gm_804D44B0, &gm_804D44B8,
    &gm_804D44C0
};

int gm_801BC488(void)
{
    lbl_8046B6A0_24C_t* tmp = gm_8016B774();
    lbl_8046B6A0_24C_t spC;
    PAD_STACK(4);

    spC = *tmp;

    gm_80166378(&spC);
    if (spC.xE == 1) {
        return spC.x16;
    }
    return 4;
}

void gm_801BC4F4(HSD_GObj* gobj)
{
    s32 temp_r0;
    u32 temp_r30;
    u32 temp_r29;
    struct EventData* temp_r28;
    u32 var_r27;
    int i;
    bool var_r25;
    u32 var_r4;
    PAD_STACK(8);

    temp_r30 = gmMainLib_804D3EE0->unk_530.unk_535;
    temp_r28 = &gmMainLib_804D3EE0->unk_530;
    temp_r28->xB_1 = true;
    temp_r29 = gmMainLib_8015CF5C(temp_r30);
    var_r25 = false;
    if (temp_r28->xB_6) {
        var_r4 = gm_8016AEDC();
        var_r4 += temp_r28->x34;
        if (temp_r30 == 0x31) {
            var_r4 = temp_r28->x34;
        }
        if (var_r4 > 0x34BBF) {
            var_r4 = 0x34BBF;
        }
        temp_r28->xC = var_r4;
        if (temp_r29 == 0 || var_r4 < temp_r29) {
            var_r25 = true;
        }
    } else {
        var_r27 = 0;
        for (i = 1; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) != Gm_PKind_NA) {
                var_r27 += Player_GetKOsByPlayerIndex(0, i);
            }
        }
        if (temp_r30 == 0x1F) {
            var_r27 = Player_GetKOsByPlayerIndex(0, 1) - pl_8003FBFC(0);
        }
        if (var_r27 > -1) {
            var_r27 = -1;
        }
        temp_r28->xC = var_r27;
        if (var_r27 > temp_r29) {
            var_r25 = true;
        }
    }
    Player_80036844(0, 1);
    lbAudioAx_80028B90();
    gm_SetGameSpeed(1.0F);
    if (var_r25) {
        gm_8016B33C(2);
        gm_8016B350(0x9C40);
        gm_8016B364(0x144);
    } else {
        gm_8016B33C(2);
        gm_8016B364(0x145);
    }
    gm_8016B328();
    HSD_GObjPLink_80390228(gobj);
}

void gm_801BC670(HSD_GObj* arg0)
{
    struct EventData* temp_r31 = &gmMainLib_804D3EE0->unk_530;
    struct gm_804D6900_x4_t* temp_r30 = gm_804D6900[0][0]->x4;
    PAD_STACK(0x10);

    temp_r31->xB_2 = true;
    temp_r31->x10 = 0x78 - temp_r30->x4;
    temp_r31->x2C = gm_8016AEEC();
    temp_r31->x30 = gm_8016AEFC();
    if (temp_r31->x2C < temp_r30->x0) {
        temp_r31->x2C = temp_r30->x0;
        temp_r31->x30 = 0;
    }
    if (Player_80036394(0) == FTKIND_SEAK) {
        temp_r31->x38 = 0x13;
    } else {
        temp_r31->x38 = 0x21;
    }
    temp_r31->x34 += gm_8016AEDC();
    Player_80036844(0, 1);
    lbAudioAx_80028B90();
    gm_SetGameSpeed(1.0F);
    gm_8016B33C(8);
    gm_8016B328();
}

void gm_801BC754(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    lbl_8046B6A0_t* temp_r3_2;
    bool var_r0;
    bool var_r0_2;
    int count;
    int i;
    struct EventData* temp_r29;
    struct EventData* temp_r28;
    struct EventData* temp_r28_2;
    struct EventData* temp_r28_3;

    PAD_STACK(0x48);

    temp_r29 = &gmMainLib_804D3EE0->unk_530;
    switch (gm_16AE_GetUnkData_0()->x24C8.match_mode) {
    case 1:
        count = 0;
        temp_r28 = &gmMainLib_804D3EE0->unk_530;
        for (i = 1; i < 6; i++) {
            if (Player_GetPlayerSlotType(i) != Gm_PKind_NA &&
                Player_GetStocks(i) != 0)
            {
                count += 1;
            }
        }
        if (temp_r28->xB_3) {
            count += gm_80169384();
        }
        if (count == 0) {
            gm_801BC4F4(gobj);
            return;
        }
        if (Player_GetP1Stock() <= 0) {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
            return;
        }
        temp_r28_2 = &gmMainLib_804D3EE0->unk_530;
        temp_r3 = gm_16AE_GetUnkData_0();
        if (temp_r28_2->xB_0) {
            var_r0 = false;
        } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
                   gm_8016AEFC() == 0x3B)
        {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
        if (var_r0) {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
        }
        break;
    case 0:
    case 2:
        temp_r28_3 = &gmMainLib_804D3EE0->unk_530;
        temp_r3_2 = gm_16AE_GetUnkData_0();
        if (temp_r28_3->xB_0) {
            var_r0_2 = false;
        } else if (temp_r3_2->x24C8.x0_6 && gm_8016AEEC() == 0 &&
                   gm_8016AEFC() == 0x3B)
        {
            var_r0_2 = true;
        } else {
            var_r0_2 = false;
        }
        if (var_r0_2) {
            if (temp_r29->x7 == gm_801BC488()) {
                gm_801BC4F4(gobj);
                return;
            }
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
        }
        break;
    }
}

void gm_801BC9E8(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r30_2;
    struct gm_804D6900_x4_t* temp_r30 =
        (*gm_804D6900)[gmMainLib_804D3EE0->unk_530.unk_535]->x4;
    u32 coins = Player_GetCoins(0);
    PAD_STACK(0x28);

    if (coins >= temp_r30->x0) {
        gm_801BC4F4(gobj);
        return;
    }
    temp_r30_2 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r30_2->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BCAF0(HSD_GObj* gobj)
{
    HSD_GObj* temp_r3;
    lbl_8046B6A0_t* temp_r3_2;
    s32 var_r0;
    s32 var_r0_2;
    struct EventData* temp_r30;
    s32 var_r30;
    s32 var_r29;
    PAD_STACK(0x28);

    var_r30 = 1;
    var_r29 = 0;
    do {
        if ((Player_GetStocks(var_r30) <= 0) &&
            (temp_r3 = Player_GetEntity(var_r30), ((temp_r3 == NULL) == 0)))
        {
            if (ftLib_GetKind(temp_r3) == FTKIND_SEAK) {
                var_r0 = 1;
            } else {
                Player_SetStocks(var_r30, 1);
                gm_8016F00C(var_r30);
                goto block_6;
            }
        } else {
        block_6:
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            var_r29 += 1;
        }
        var_r30 += 1;
    } while (var_r30 < 3);
    if (var_r29 == 2) {
        gm_801BC4F4(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r30 = &gmMainLib_804D3EE0->unk_530;
    temp_r3_2 = gm_16AE_GetUnkData_0();
    if (temp_r30->xB_0) {
        var_r0_2 = 0;
    } else if (temp_r3_2->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0_2 = 1;
    } else {
        var_r0_2 = 0;
    }
    if (var_r0_2 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BCC9C(HSD_GObj* arg0)
{
    struct gm_804D6900_t** temp_r29 = gm_804D6900[0];
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    u8 idx = gmMainLib_804D3EE0->unk_530.unk_535;
    struct gm_804D6900_x4_t* x4 = (*temp_r29)->x4;
    struct EventData* ev2;
    struct gm_804D6900_t** entry;
    struct gm_evstage_table* inner;
    gm_801BAB40_src* cd;
    u8 costume;
    lbl_8046B6A0_t* mi;
    s32 var_r0;
    PAD_STACK(0x38);

    if (gmMainLib_804D3EE0->unk_530.xB_2) {
        ev->x10 -= 1;
        if (ev->x10 < 0) {
            lbBgFlash_8002063C(x4->x4);
            HSD_GObjPLink_80390228(arg0);
        }
        return;
    }
    if (Player_GetStocks(1) <= 0) {
        entry = &temp_r29[idx];
        inner = (*entry)->x10;
        cd = inner->entries[ev->x20];
        ev2 = &gmMainLib_804D3EE0->unk_530;
        costume = cd->color;
        if ((s8) ev2->x0 == cd->c_kind && ev2->x1 == costume) {
            if (costume <= 2) {
                costume += 1;
            } else {
                costume = 0;
            }
        }
        gm_8016AC44(cd->c_kind, (s8) costume);
        if (ev->x20 >= (s32) ((*entry)->x10->count - 1)) {
            gm_801BC4F4(arg0);
            return;
        }
        if (Player_GetP1Stock() <= 0) {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0f);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(arg0);
            return;
        }
        gm_801BC670(arg0);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
        return;
    }
    {
        struct EventData* ev3 = gm_GetEventData();
        mi = gm_16AE_GetUnkData_0();
        if (ev3->xB_0) {
            var_r0 = 0;
        } else if (((*(u8*) &mi->x24C8 >> 1U) & 1) && gm_8016AEEC() == 0 &&
                   gm_8016AEFC() == 0x3B)
        {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
    }
}

void gm_801BCF20(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

void gm_801BCF40(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gm_801BC4F4(gobj);
    }
}

void gm_801BD028(HSD_GObj* arg0)
{
    Vec3 pos;
    lbl_8046B6A0_t* rules;
    s32 cond;
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    struct gm_804D6900_t** levels = gm_804D6900[0];
    u8 level = gmMainLib_804D3EE0->unk_530.unk_535;
    PAD_STACK(0x1C);

    if (gmMainLib_804D3EE0->unk_530.x10 == 0) {
        Vec3* src = (Vec3*) levels[level]->x4;
        pos.x = src->x;
        pos.y = src->y;
        pos.z = src->z;
        itEvYoshiEgg_Spawn(&pos);
        ev->x10 += 1;
    }
    if (ev->x18 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = 0;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
        return;
    }
    ev = &gmMainLib_804D3EE0->unk_530;
    rules = gm_16AE_GetUnkData_0();
    if (ev->xB_0) {
        cond = 0;
    } else if (rules->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        gm_801BC4F4(arg0);
    }
}

void gm_801BD164(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    s32 temp_r30;
    s32 var_r0;
    struct EventData* temp_r30_2;
    PAD_STACK(0x28);

    if (Player_GetStocks(2) <= 0) {
        temp_r30 = Player_GetKOsByPlayerIndex(1, 2);
        if (Player_GetKOsByPlayerIndex(0, 2) > temp_r30) {
            gm_801BC4F4(gobj);
        } else {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
        }
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r30_2 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r30_2->xB_0) {
        var_r0 = 0;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BD30C(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    s32 var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Player_GetStocks(1) <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r31->xB_0) {
        var_r0 = 0;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        gm_801BC4F4(gobj);
    }
}

void gm_801BD44C(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

void gm_801BD46C(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    s32 var_r0;
    struct EventData* temp_r31;
    s32 var_r30;
    int i;
    int count;
    HSD_GObj* p;
    PAD_STACK(0x38);

    count = 0;
    for (i = 1; i < 3; i++) {
        p = Player_GetEntityAtIndex(i, 1);
        if (p != NULL) {
            var_r30 = ftLib_8008731C(p);
        }
        if (var_r30 != 0) {
            count++;
        }
    }
    if (count == 2) {
        gm_801BC4F4(gobj);
        return;
    }
    for (i = 1; i < 3; i++) {
        if (Player_GetStocks(i) <= 0) {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0F);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(gobj);
            return;
        }
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r31->xB_0) {
        var_r0 = 0;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BD658(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    s32 var_r30;
    int i;
    struct EventData* temp_r28;
    struct EventData* temp_r28_2;
    PAD_STACK(0x28);

    var_r30 = 0;
    temp_r28 = &gmMainLib_804D3EE0->unk_530;
    for (i = 1; i < 6; i++) {
        if (Player_GetPlayerSlotType(i) != Gm_PKind_NA &&
            Player_GetStocks(i) != 0)
        {
            var_r30 += 1;
        }
    }
    if (temp_r28->xB_3) {
        var_r30 += gm_80169384();
    }
    if (var_r30 == 0) {
        gm_801BC4F4(gobj);
        ifStock_802FA2D0(0);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r28_2 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r28_2->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BD7FC(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Player_GetStocks(1) <= 0) {
        gm_801BC4F4(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BD93C(HSD_GObj* gobj)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x38);

    if (Player_GetStocks(2) <= 0) {
        gm_801BC4F4(gobj);
        return;
    }
    if (Player_GetStocks(1) <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BDAD4(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

void gm_801BDAF4(HSD_GObj* arg0)
{
    lbl_8046B6A0_t* temp_r3;
    s32 temp_r30_2;
    s32 temp_r31;
    bool var_r0;
    struct EventData* temp_r30;
    PAD_STACK(0x10);

    temp_r30 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r30->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0 != 0) {
        temp_r30_2 = pl_8003FC20(1);
        temp_r31 = Player_GetKOsByPlayerIndex(0, 1);
        if (temp_r31 - pl_8003FBFC(0) > temp_r30_2) {
            gm_801BC4F4(arg0);
            return;
        }
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
    }
}

void gm_801BDC08(HSD_GObj* arg0)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Ground_801C1D84() != 0U) {
        gm_801BC4F4(arg0);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
    }
}

void gm_801BDD44(HSD_GObj* arg0)
{
    lbl_8046B6A0_t* temp_r3;
    bool var_r0;
    struct EventData* temp_r31;
    PAD_STACK(0x20);

    if (Player_GetStocks(2) <= 0 && Player_GetStocks(3) <= 0) {
        gm_801BC4F4(arg0);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
        return;
    }
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_16AE_GetUnkData_0();
    if (temp_r31->xB_0) {
        var_r0 = false;
    } else if (temp_r3->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
    }
}

void gm_801BDE94(HSD_GObj* arg0)
{
    PlayerInitData sp50;
    struct gm_804D6900_t** tbl = gm_804D6900[0];
    struct EventData* ev = gm_GetEventData();
    u8 level = ev->unk_535;
    u64 mask;
    struct gm_804D6900_x4_t* x4 = (*tbl)->x4;
    PAD_STACK(0x3C);

    if (!ev->xB_5) {
        ev->xB_5 = 1;
        if (ev->x20 == 0) {
            mask = lbAudioAx_80026E84((enum CharacterKind)(s8) (u8) tbl[level]
                                          ->player_init[0]
                                          ->c_kind);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind) tbl[level]->x10->entries[0]->c_kind);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind) tbl[level]->x10->entries[2]->c_kind);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind) tbl[level]->x10->entries[3]->c_kind);
        } else {
            mask = lbAudioAx_80026E84((enum CharacterKind)(s8) (u8) tbl[level]
                                          ->player_init[0]
                                          ->c_kind);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind) tbl[level]->x10->entries[1]->c_kind);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind) tbl[level]->x10->entries[4]->c_kind);
        }
        lbAudioAx_80026F2C(0x14);
        lbAudioAx_8002702C(4, mask);
        lbAudioAx_80027168();
        lbAudioAx_80027648();
    }

    if (ev->xB_2) {
        ev->x10 -= 1;
        if (ev->x10 < 0) {
            lbBgFlash_8002063C(x4->x4);
            HSD_GObjPLink_80390228(arg0);
        }
        return;
    } else if (ev->x20 == 0) {
        switch (ev->x18) {
        case 0:
            if (Player_GetStocks(1) <= 0) {
                ev->x18 = 1;
                gm_801BAB40(&sp50, tbl[level]->x10->entries[2]);
                gm_8016EDDC(2, &sp50);
            }
            break;
        case 1:
            if (Player_GetStocks(2) <= 0) {
                ev->x18 = 2;
                gm_801BAB40(&sp50, tbl[level]->x10->entries[3]);
                gm_8016EDDC(3, &sp50);
            }
            break;
        case 2:
            if (Player_GetStocks(3) <= 0) {
                gm_801BAB40_src* sp = tbl[level]->x10->entries[3];
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                u8 color = sp->color;
                if ((s8) ev2->x0 == sp->c_kind && ev2->x1 == color) {
                    if (color <= 2) {
                        color += 1;
                    } else {
                        color = 0;
                    }
                }
                gm_8016AC44(sp->c_kind, color);
                if (Player_GetP1Stock() <= 0) {
                    gmMainLib_804D3EE0->unk_530.xB_1 = false;
                    lbAudioAx_80028B90();
                    gm_SetGameSpeed(1.0f);
                    gm_8016B33C(6);
                    gm_8016B364(0x148);
                    gm_8016B378(0x28);
                    gm_8016B328();
                    HSD_GObjPLink_80390228(arg0);
                    return;
                }
                gm_801BC670(arg0);
                return;
            }
            break;
        }
    } else {
        switch (ev->x18) {
        case 0:
            if (Player_GetStocks(1) <= 0) {
                ev->x18 = 1;
                gm_801BAB40(&sp50, tbl[level]->x10->entries[4]);
                gm_8016EDDC(2, &sp50);
            }
            break;
        case 1:
            if (Player_GetStocks(2) <= 0) {
                gm_801BAB40_src* sp = tbl[level]->x10->entries[4];
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                u8 color = sp->color;
                if ((s8) ev2->x0 == sp->c_kind && ev2->x1 == color) {
                    if (color <= 2) {
                        color += 1;
                    } else {
                        color = 0;
                    }
                }
                gm_8016AC44(sp->c_kind, color);
                gm_801BC4F4(arg0);
                return;
            }
            break;
        }
    }

    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
        return;
    }
    {
        struct EventData* ev2 = gm_GetEventData();
        lbl_8046B6A0_t* info = gm_16AE_GetUnkData_0();
        int do_end;
        if (ev2->xB_0) {
            do_end = 0;
        } else if (info->x24C8.x0_6 && gm_8016AEEC() == 0 &&
                   gm_8016AEFC() == 0x3B)
        {
            do_end = 1;
        } else {
            do_end = 0;
        }
        if (do_end != 0) {
            gmMainLib_804D3EE0->unk_530.xB_1 = false;
            lbAudioAx_80028B90();
            gm_SetGameSpeed(1.0f);
            gm_8016B33C(6);
            gm_8016B364(0x148);
            gm_8016B378(0x28);
            gm_8016B328();
            HSD_GObjPLink_80390228(arg0);
        }
    }
}

void gm_801BE37C(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

void gm_801BE39C(HSD_GObj* gobj)
{
    PlayerInitData sp40;
    lbl_8046B6A0_t* temp_r3_2;
    struct EventData* temp_r31;
    struct gm_804D6900_x4_t* temp_r30;
    struct gm_804D6900_t** temp_r28;
    struct EventData* temp_r27_5;
    bool var_r0;
    u64 temp_ret;
    u8 temp_r0;

    PAD_STACK(0x34);

    temp_r28 = gm_804D6900[0];
    temp_r0 = gmMainLib_804D3EE0->unk_530.unk_535;
    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r30 = temp_r28[temp_r0]->x4;
    if (!temp_r31->xB_5) {
        temp_r31->xB_5 = true;
        temp_ret = lbAudioAx_80026E84(Player_GetPlayerCharacter(0));
        temp_ret |=
            lbAudioAx_80026E84(temp_r28[temp_r0]->player_init[1]->c_kind);
        temp_ret |=
            lbAudioAx_80026E84(((gm_801BAB40_src*) temp_r30->x4)->c_kind);
        lbAudioAx_80026F2C(0x14);
        lbAudioAx_8002702C(4, temp_ret);
        lbAudioAx_80027168();
        lbAudioAx_80027648();
    }
    if (temp_r31->x10 != 0 && Player_GetStocks(2) <= 0) {
        gm_801BC4F4(gobj);
        return;
    }
    if (Player_GetStocks(1) <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    if (temp_r31->x10 == 0 && gm_8016AEEC() >= temp_r30->x0) {
        temp_r31->x10 = 1;
        gm_801BAB40(&sp40, (gm_801BAB40_src*) temp_r30->x4);
        sp40.color = temp_r31->x50[2];
        gm_8016EDDC(2, &sp40);
    }
    temp_r27_5 = &gmMainLib_804D3EE0->unk_530;
    temp_r3_2 = gm_16AE_GetUnkData_0();
    if (temp_r27_5->xB_0) {
        var_r0 = false;
    } else if (temp_r3_2->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BE618(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

void gm_801BE638(HSD_GObj* gobj)
{
    int temp_r31;
    struct EventData* temp_r30;
    int temp_r29;
    struct EventData* temp_r28_4;
    int temp_r28_3;
    int temp_r28_2;
    int temp_r28;
    lbl_8046B6A0_t* temp_r3;
    lbl_8046B6A0_t* temp_r3_4;
    int temp_r0_2;
    int temp_r3_2;
    int temp_r3_3;
    int var_r0;

    PAD_STACK(0x20);

    temp_r30 = &gmMainLib_804D3EE0->unk_530;
    temp_r31 = ftBossLib_8015C74C();
    temp_r28 = ftBossLib_8015C7EC();
    temp_r29 = ftBossLib_8015C92C();
    switch (temp_r30->x20) {
    case 0:
        if (Player_GetRemainingHP(1) <= 0 || Player_GetRemainingHP(2) <= 0) {
            temp_r30->x20 = 1;
            temp_r30->x10 = 0;
        }
        break;
    case 1:
        if (Player_GetRemainingHP(1) <= 0 && Player_GetRemainingHP(2) <= 0) {
            temp_r30->x20 = 2;
            temp_r30->x10 = 0;
        }
        break;
    case 2:
        break;
    }
    if (Player_GetRemainingHP(1) <= 0 && Player_GetRemainingHP(2) <= 0) {
        temp_r28_2 = temp_r31 + temp_r29;
        if (temp_r30->x10 == 0) {
            lbl_8046B6A0_t* tmp = gm_16AE_GetUnkData_0();
            tmp->hud_enabled = 0;
            if (temp_r30->x18 == 1) {
                temp_r30->x18 = 2;
            } else {
                temp_r30->x18 = 1;
            }
            ftBossLib_8015CB9C(temp_r30->x18);
            gm_801A4634(6);
            Player_80031790(0);
            Player_80036844(0, 1);
            temp_r30->x34 = gm_8016AEDC();
            temp_r3 = gm_16AE_GetUnkData_0();
            temp_r3->x24C8.x0_6 = false;
        }
        if (temp_r30->x10 == temp_r31) {
            lbAudioAx_8002438C(0x4E200);
            ftBossLib_8015CC14();
            gm_801A4674(6);
            gm_SetGameSpeed(0.5F);
            lbBgFlash_80020688(temp_r29);
        }
        temp_r0_2 = temp_r30->x10;
        if (temp_r0_2 >= temp_r28_2) {
            gm_801BC4F4(gobj);
            return;
        }
        if (temp_r0_2 >= temp_r31) {
            lbAudioAx_80028B6C();
        }
        if ((temp_r30->x10 % 30) == 0) {
            gm_80167858((s32) temp_r30->x6, Player_GetNametagSlotID(0), 2,
                        0x1E);
            Camera_80030E44(3, NULL);
        }
        temp_r3_2 = temp_r30->x10;
        if (temp_r3_2 <= temp_r28_2) {
            temp_r30->x10 = temp_r3_2 + 1;
        }
    } else if (Player_GetRemainingHP(1) <= 0 || Player_GetRemainingHP(2) <= 0)
    {
        if (Player_GetRemainingHP(1) <= 0) {
            temp_r30->x18 = 1;
        } else {
            temp_r30->x18 = 2;
        }
        temp_r28_3 = temp_r31 + temp_r28;
        if ((s32) temp_r30->x10 == 0) {
            ftBossLib_8015CB9C(temp_r30->x18);
            gm_801A4634(6);
        }
        if ((s32) temp_r30->x10 == temp_r31) {
            lbAudioAx_8002438C(0x4E200);
            ftBossLib_8015CC14();
            gm_801A4674(6);
            gm_SetGameSpeed(0.5F);
        }
        if ((s32) temp_r30->x10 == temp_r28_3) {
            gm_SetGameSpeed(1.0F);
        }
        temp_r3_3 = temp_r30->x10;
        if (temp_r3_3 <= temp_r28_3) {
            temp_r30->x10 = temp_r3_3 + 1;
        }
    }
    if (Player_GetP1Stock() <= 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
        return;
    }
    temp_r28_4 = &gmMainLib_804D3EE0->unk_530;
    temp_r3_4 = gm_16AE_GetUnkData_0();
    if (temp_r28_4->xB_0) {
        var_r0 = 0;
    } else if (temp_r3_4->x24C8.x0_6 && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B)
    {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        gmMainLib_804D3EE0->unk_530.xB_1 = false;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0F);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(gobj);
    }
}

void gm_801BEA10(int arg0)
{
    Player_SetPlayerAndEntityCpuType(
        arg0, (*gm_804D6900)[gmMainLib_804D3EE0->unk_530.unk_535]->xC->x16);
}

void gm_801BEA4C(int arg0)
{
    gm_801BEA10(arg0);
}

void gm_801BEA88(int arg0, int arg1)
{
    PAD_STACK(0x10);
    gm_801BEA10(arg0);
    if (arg1 == 0) {
        Player_SetModelScale(arg0, 2.0F);
    }
}

/// #gm_801BEA88

void gm_801BEAF0(int arg0)
{
    gm_801BEA10(arg0);
}

void gm_801BEB2C(int arg0)
{
    gm_801BEA10(arg0);
}

void gm_801BEB68(int arg0)
{
    gmMainLib_804D3EE0->unk_530.x18 = arg0;
}

void gm_801BEB74(u8 arg0)
{
    gmMainLib_804D3EE0->unk_530.unk_535 = arg0;
}

u8 gm_801BEB80(void)
{
    return gmMainLib_804D3EE0->unk_530.unk_535;
}

bool gm_801BEB8C(u8 arg0)
{
    return (*gm_804D6900)[arg0]->x8->x1_0;
}

u8 gm_801BEBA8(u8 arg0)
{
    return gm_803DF918[arg0];
}

u8 gm_801BEBC0(u8 arg0)
{
    u8* tmp = gm_803DF918;
    u8 i;
    for (i = 0; i < 0x33; i++) {
        if (arg0 == tmp[i]) {
            break;
        }
    }
    return i;
}

u8 gm_801BEBF8(u8 arg0)
{
    u8* table = gm_803DF918;
    u8 i;
    struct gm_804D6900_t** array = gm_804D6900[0];
    struct gm_804D6900_t* entry;
    u8* ptr;

    for (i = 0; i < 0x33; i++) {
        if (arg0 == table[i]) {
            break;
        }
    }

    entry = array[i];
    if (entry == NULL) {
        return CHKIND_NONE;
    }

    ptr = *(u8**) ((u8*) entry + 0x14);
    return *ptr;
}

UNK_T gm_801BEC54(void)
{
    struct gm_804D6900_t* temp_r3;
    temp_r3 = (*gm_804D6900)[gmMainLib_804D3EE0->unk_530.unk_535];
    if (temp_r3 == NULL) {
        return NULL;
    }
    return temp_r3->x4;
}
