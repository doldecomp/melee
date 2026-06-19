#include "gm_1BA8.h"

#include "gm_1BA8.static.h"

#include "gm_unsplit.h"

#include "vi/vi1201v1.h"

#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gmresultplayer.h>
#include <melee/gm/gmtou.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/if/ifstock.h>
#include <melee/it/items/itevyoshiegg.h>
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
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/vi/types.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0401.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi0502.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>
#include <melee/vi/vi1201v2.h>

GameScene gm_803DF618_Scenes[] = {
    {
        0,
        3,
        0,
        gm_801BAA60,
        gm_801BAAD0,
        {
            GS_CSS,
            &gm_80497758,
            &gm_80497758,
        },
    },
    {
        1,
        3,
        0,
        gm_801BAD70,
        gm_801BB758,
        {
            GS_VS,
            &gm_804978A0,
            &gm_804979D8,
        },
    },
    { 0xFF },
};

extern u8 gm_804D68F8;
extern u8 gm_804D68F9;

void gm_801BA8FC(void)
{
    lbArchive_LoadSymbols("GmEvent.dat", &gm_804D6900,
                          "sqEventInitDataLevelTbl", 0);
}

void gm_801BA938(struct EventData* arg0, int lo, int hi, bool arg3)
{
    struct GameCache* temp_r7 = &lbDvd_8001822C()->game_cache;
    u64 mask;
    s8 char_id;
    int i;

    for (i = lo; i < hi; i++) {
        char_id = arg0->x4C[i];
        if (char_id != CHKIND_NONE) {
            temp_r7->entries[i].char_id = char_id;
            temp_r7->entries[i].color = arg0->x50[i];
            if (arg0->x45 != 0 && i > 0 && arg0->x4C[i] == 4) {
                temp_r7->entries[i].x5 = 0;
            }
        }
    }

    if (arg3 != 0) {
        temp_r7->stage_id = arg0->x48;
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

void gm_801BAA60(GameScene* arg0)
{
    struct EventData* temp_r31 = &gmMainLib_804D3EE0->unk_530;
    CSSData* css = gm_801A427C(arg0);
    PAD_STACK(8);

    gm_801B06B0(css, 0xE, temp_r31->x2, 0, temp_r31->x3, temp_r31->x4, 0,
                temp_r31->x6);
    if (temp_r31->x44 == 1) {
        gm_801BA938(temp_r31, 1, 4, true);
    }
}

void gm_801BAAD0(GameScene* arg0)
{
    CSSData* temp_r3;
    struct EventData* temp_r31;

    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_801A4284(arg0);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(GM_MENU);
        return;
    }
    gm_801B0730(temp_r3, &temp_r31->x2, NULL, &temp_r31->x3, &temp_r31->x4,
                NULL);
    temp_r31->x8 = -1;
    temp_r31->x9 = -1;
    temp_r31->xA = -1;
}

typedef struct gm_801BAB40_src {
    /* 0x00 */ u8 c_kind;
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

void gm_801BAB40(PlayerInitData* arg0, int arg1)
{
    gm_801BAB40_src* src = (gm_801BAB40_src*) arg1;
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

s32 gm_801BAC9C(GameScene* arg0, s32 arg1)
{
    UNUSED u8 _[8];
    u8 chars[33];
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    StartMeleeData* data = gm_801A427C(arg0);
    s32 i;
    s32 found;
    s32 k;
    s32 count = 0;
    struct gm_event_char_list* src =
        (struct gm_event_char_list*) gm_804D6900[ev->unk_535][0]->x4;
    PAD_STACK(8);

    for (i = 0; i < 0x21; i++) {
        u8 c = src->c_kind[i];
        if ((s32) c == 0x21) {
            break;
        }
        {
            found = 0;
            for (k = 0; k < arg1; k++) {
                if (data->players[k].c_kind == (s8) c) {
                    found++;
                }
            }
            if (found == 0) {
                chars[count] = c;
                count++;
            }
        }
    }
    return chars[HSD_Randi(count)];
}

struct gm_evspawn {
    /* 0x0 */ s8 unk0;
    /* 0x1 */ u8 pad1[2];
    /* 0x3 */ u8 unk3;
};

struct gm_evx10 {
    u8 pad[0x10];
    struct gm_evspawn* unk10;
    struct gm_evspawn* unk14;
    struct gm_evspawn* unk18;
    struct gm_evspawn* unk1C;
    struct gm_evspawn* unk20;
};

struct gm_evstage {
    u8 pad[2];
    u16 stage;
};

struct gm_evinit {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ s8 unk3;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u16 unk6;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ u8 padC[4];
    /* 0x10 */ u32 x10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ f32 x1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
};

struct gm_evstage_list {
    u16 count;
    u16 stage[1];
};

struct gm_evspawn_table {
    u8 count;
    u8 pad[0xF];
    gm_801BAB40_src* entries[5];
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

struct gm_evlevel {
    /* 0x00 */ u8 kind;
    /* 0x01 */ u8 flags;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ struct gm_804D6900_x4_t* x4;
    /* 0x08 */ StartMeleeRules* x8;
    /* 0x0C */ struct gm_evbonus* xC;
    /* 0x10 */ void* x10;
    /* 0x14 */ gm_801BAB40_src* player_init[5];
};

struct gm_random_history {
    u8 pad0[2];
    u8 character_usage[0x1A];
    u8 stage_usage[0x1D];
};

void gm_801BAD70(GameScene* arg0)
{
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    StartMeleeData* md = gm_801A427C(arg0);
    u8* r3b = (u8*) md;
    u8 level = ev->unk_535;
    gm_803DF94C_t** event_info = gm_803DF94C;
    struct gm_804D6900_t** levels;
    struct gm_804D6900_t** lvlpp;
    struct gm_evlevel* level_info;
    s32 player_idx;
    s32 player_init_off;
    s32 spawn_off;
    PAD_STACK(0x20);

    lbArchive_LoadSymbols("GmEvent.dat", &gm_804D6900,
                          "sqEventInitDataLevelTbl", 0);
    levels = gm_804D6900[0];
    gm_80167A64(&md->rules);
    lvlpp = &levels[level];
    level_info = (struct gm_evlevel*) *lvlpp;
    md->rules.x0_0 = (*lvlpp)->x8->x0_0;
    md->rules.x0_3 = (*lvlpp)->x8->x0_3;
    md->rules.x0_6 = (*lvlpp)->x8->x0_6;
    md->rules.x0_7 = (*lvlpp)->x8->x0_7;
    md->rules.x1_0 = 1;
    md->rules.x1_1 = 0;
    md->rules.x1_2 = 0;
    md->rules.x1_3 = 0;
    md->rules.timer_shows_hours = 0;
    md->rules.x1_7 = (*lvlpp)->x8->x1_1;
    md->rules.x2_2 = 0;
    md->rules.x2_3 = 0;
    md->rules.x2_4 = 0;
    md->rules.x2_5 = (*lvlpp)->x8->x1_2;
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
    md->rules.x5_2 = (*lvlpp)->x8->x1_3;
    md->rules.x5_3 = (*lvlpp)->x8->x1_4;
    md->rules.x7 = 0;
    md->rules.is_teams = ((struct gm_evinit*) (*lvlpp)->x8)->unk2;
    md->rules.x9 = 0;
    md->rules.xA = 0;
    md->rules.xB = ((struct gm_evinit*) (*lvlpp)->x8)->unk3;
    md->rules.xC = ((struct gm_evinit*) (*lvlpp)->x8)->unk4;
    md->rules.xD = 0x6E;
    md->rules.xE = ((struct gm_evinit*) (*lvlpp)->x8)->unk6;
    md->rules.x10 = ((struct gm_evinit*) (*lvlpp)->x8)->unk8;
    md->rules.x14 = 0;
    md->rules.x18 = 0;
    {
        struct gm_evinit* init = (struct gm_evinit*) (*lvlpp)->x8;
        u32 x10 = init->x10;
        *(s32*) (r3b + 0x24) = init->unk14;
        *(u32*) (r3b + 0x20) = x10;
    }
    md->rules.x28 = ((struct gm_evinit*) (*lvlpp)->x8)->x18;
    md->rules.x30 = ((struct gm_evinit*) (*lvlpp)->x8)->x1C;
    md->rules.x34 = ((struct gm_evinit*) (*lvlpp)->x8)->unk20;
    md->rules.x44 = fn_801BBFE8;
    if (r3b[0] & 1) {
        ev->xB_0 = 1;
    }
    if ((((struct gm_evinit*) (*lvlpp)->x8)->unk1 >> 7) & 1) {
        ev->xB_6 = 1;
    }
    if (((struct gm_evinit*) (*lvlpp)->x8)->unk24 != 1.0f) {
        ev->x1C = ((struct gm_evinit*) (*lvlpp)->x8)->unk24;
    }
    if (level_info->kind == 2) {
        struct gm_evstage_list* stage_list;
        u16 stage;
        ev->xB_4 = 1;
        stage_list = level_info->x10;
        stage = stage_list->stage[ev->x20];
        md->rules.xE = stage;
        ev->x48 = (InternalStageId) stage;
        if (ev->x20 > 0) {
            md->rules.x1_2 = 1;
            md->rules.x1_3 = 1;
            md->rules.x10 = ev->x2C;
        }
        gm_8016A92C(&md->rules);
    }
    r3b[0x61] = 3;
    player_idx = 0;
    player_init_off = 0;
    r3b[0x85] = 3;
    spawn_off = 0;
    r3b[0xA9] = 3;
    r3b[0xCD] = 3;
    r3b[0xF1] = 3;
    r3b[0x115] = 3;

    while (player_idx < (s32) ((level_info->flags >> 5) & 7)) {
        gm_801BAB40_src* init = level_info->player_init[player_idx];
        while (init == NULL) {
            player_idx += 1;
            player_init_off += 0x24;
            spawn_off += 4;
            init = level_info->player_init[player_idx];
        }
        gm_801BAB40((PlayerInitData*) (r3b + player_init_off + 0x60),
                    (int) init);
        if (player_idx == 0) {
            gm_801B05F4((PlayerInitData*) (r3b + 0x60), ev->x6);
            ev->x7 = r3b[0x69];
            if ((s8) r3b[0x60] == 0x21) {
                r3b[0x60] = ev->x2;
                r3b[0x63] = ev->x3;
                r3b[0x6A] = ev->x4;
            }
            {
                u8 c = r3b[0x60];
                ev->x0 = c;
                ev->x4C[0] = (s8) c;
            }
            {
                u8 c = r3b[0x63];
                ev->x1 = c;
                ev->x50[0] = c;
            }
            r3b[0x6C] = (r3b[0x6C] & ~0x80) |
                        ((gm_801677F8(ev->x6, r3b[0x6A]) << 7) & 0x80);
        } else {
            if (init->team == 0) {
                r3b[player_init_off + 0x69] = r3b[0x69];
                ((PlayerInitData*) (r3b + player_init_off + 0x60))->xD_b1 = 1;
            }
            if ((s8) init->c_kind == 0x21) {
                s8* t = &ev->x8 + player_idx - 1;
                s8 v = *t;
                if (v == -1) {
                    u8 nv = gm_801BAC9C(arg0, player_idx);
                    r3b[player_init_off + 0x60] = nv;
                    *t = (s8) r3b[player_init_off + 0x60];
                } else {
                    r3b[player_init_off + 0x60] = v;
                }
            }
            if ((s8) r3b[player_init_off + 0x60] == (s8) r3b[0x60]) {
                u8 c = r3b[player_init_off + 0x63];
                if (c == r3b[0x63]) {
                    if (c <= 2) {
                        c += 1;
                    } else {
                        c = 0;
                    }
                    r3b[player_init_off + 0x63] = c;
                }
            }
            if ((s8) r3b[0x60] == 0x13 &&
                (s8) r3b[player_init_off + 0x60] == 0x12)
            {
                u8 c = r3b[player_init_off + 0x63];
                if (c == r3b[0x63]) {
                    if (c <= 2) {
                        c += 1;
                    } else {
                        c = 0;
                    }
                    r3b[player_init_off + 0x63] = c;
                }
            }
            if (player_idx < 4) {
                ev->x4C[player_idx] = (s8) r3b[player_init_off + 0x60];
                ev->x50[player_idx] = r3b[player_init_off + 0x63];
            }
        }
        player_idx += 1;
        player_init_off += 0x24;
        spawn_off += 4;
    }

    if (level_info->kind == 2) {
        if (ev->x20 > 0) {
            r3b[0x62] = (s8) ev->x24;
            *(s16*) (r3b + 0x70) = (s16) ev->x28;
            ((PlayerInitData*) (r3b + 0x60))->xC_b1 = 0;
            {
                u8 c = ev->x38;
                if (c != 0x21) {
                    r3b[0x60] = c;
                    ev->x0 = c;
                    ev->x4C[0] = (s8) c;
                }
            }
        }
        {
            struct gm_evspawn_table* spawn_table = level_info->x10;
            gm_801BAB40((PlayerInitData*) (r3b + 0x84),
                        (int) spawn_table->entries[ev->x20]);
        }
        if ((s8) r3b[0x84] == (s8) r3b[0x60]) {
            u8 c = r3b[0x87];
            if (c == r3b[0x63]) {
                if (c <= 2) {
                    c += 1;
                } else {
                    c = 0;
                }
                r3b[0x87] = c;
            }
        }
        if ((s8) r3b[0x60] == 0x13 && (s8) r3b[0x84] == 0x12) {
            u8 c = r3b[0x87];
            if (c == r3b[0x63]) {
                if (c <= 2) {
                    c += 1;
                } else {
                    c = 0;
                }
                r3b[0x87] = c;
            }
        }
        ev->x4C[1] = (s8) r3b[0x84];
        ev->x50[1] = r3b[0x87];
    }
    if (level == 0x2B) {
        u8 c = ev->x50[2];
        if ((s8) (u8) ev->x4C[2] == (s8) (u8) ev->x4C[0] &&
            (u8) ev->x50[0] == c)
        {
            if (c <= 2) {
                c = c + 1;
            } else {
                c = 0;
            }
            ev->x50[2] = c;
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
    if (level_info->kind == 1) {
        struct gm_evbonus* bonus = level_info->xC;
        int var_r9;
        s8 k;
        s32 sp8;
        ev->xB_3 = 1;
        if (bonus->x5 == 1) {
            var_r9 = 1;
            if ((s8) ev->x0 == bonus->c_kind) {
                u8 c;
                if ((u8) ev->x1 == (c = bonus->color)) {
                    if (c <= 2) {
                        c = c + 1;
                    } else {
                        c = 0;
                    }
                    ev->x50[1] = c;
                }
            }
        } else {
            var_r9 = 0;
        }
        k = bonus->c_kind;
        sp8 = (k == 4) ? bonus->x17 : 0;
        gm_8016A22C(k, 0x21, 0x21, ev->x50[1], 0, 0, var_r9, 0, sp8, ev->x0,
                    ev->x1, bonus->x1, bonus->x2, bonus->x3, bonus->x4, 0, 1,
                    bonus->x8, bonus->xC);
        gm_8016A414(bonus->x10);
        gm_8016A21C(&md->rules);
        if ((bonus->flags >> 7) & 1) {
            gm_8016A434();
        }
        if (event_info[level]->x4 != NULL) {
            gm_8016A404((s32) event_info[level]->x4);
        }
        if (bonus->x15 != 0) {
            gm_8016A424((s8) bonus->x15);
        }
    }
    {
        struct GameCache* cache = &lbDvd_8001822C()->game_cache;
        switch ((s8) (u8) ev->x44) {
        case 0:
            gm_801BA938(ev, 0, 4, 1);
            break;
        case 1:
            gm_801BA938(ev, 0, 4, 1);
            break;
        case 2:
            cache->entries[0].char_id = (s8) ev->x4C[0];
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
            cache->entries[0].char_id = (s8) ev->x4C[0];
            cache->entries[0].color = ev->x50[0];
            lbDvd_80018254();
            lbDvd_80017700(4);
            gm_801BA938(ev, 1, 4, 1);
            break;
        }
    }
    gm_8016F088(md);
    gm_80168F88();
}

void gm_801BB758(GameScene* arg0)
{
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    MatchExitInfo* exit = gm_801A4284(arg0);
    u8 stage = ev->unk_535;
    u8 b;
    u8 kind;
    s32 t;

    gm_8016A164();
    if (exit->match_end.result == 8) {
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
            struct GameCache* gc = &lbDvd_8001822C()->game_cache;
            lbDvd_80018C6C();
            gc->entries[0].char_id = (s8) ev->x0;
            gc->entries[0].color = ev->x1;
            lbDvd_80018254();
            lbDvd_80017700(4);
        }
        gm_SetPendingScene(1);
        return;
    }
    if (exit->match_end.result == 7) {
        gm_801A42F8(1);
        return;
    }
    ev->x3C += gm_80168940(&gm_804979D8[0].match_end);
    ev->x40 += (s32) exit->match_end.frame_count;
    b = ((u8*) ev)[0xB];
    if (((b >> 3) & 1) && ((b >> 5) & 1)) {
        ev->x24 = gm_804979D8[0].match_end.player_standings[0].stocks;
        ev->x28 = gm_804979D8[0].match_end.player_standings[0].percent;
        ev->xB_2 = 0;
        ev->xB_5 = 0;
        t = ev->x20;
        ev->x20 = t + 1;
        gm_801BBB64();
        gm_SetPendingScene(1);
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
        int sid = gm_8017335C();
        if ((u16) sid != 0x148) {
            gm_80164504(sid);
        }
    }
    if (ev->xB_1) {
        gm_80173D3C(ev->unk_535);
    }
    gm_80173EEC();
    gm_80172898(0x10);
    if (kind != 0x21) {
        gm_801736E8(ev->x0, ev->x1, ev->x6, ev->x4, kind, 1);
        gm_801A42F8(0x14);
        return;
    }
    if (gm_80173754(1, ev->x6) == 0) {
        gm_801A42F8(1);
    }
}

void gm_801BBA60_OnInit(void)
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

s32 gm_801BBB64(void)
{
    struct gm_804D6900_t** pp;
    struct EventData* ev;
    struct gm_804D6900_t** tbl;
    s32 idx;
    s8* player_init;
    void* event_entry;
    struct gm_804D6900_x4_t* x4;
    s32 result;

    ev = &gmMainLib_804D3EE0->unk_530;
    tbl = gm_804D6900[0];
    idx = gmMainLib_804D3EE0->unk_530.unk_535;
    if (*tbl[idx]->x14 != 0x21) {
        ev->x44 = 0;
    } else {
        ev->x44 = 1;
    }
    pp = &tbl[idx];
    ev->x48 = (InternalStageId) * (u16*) ((u8*) (*pp)->x8 + 6);
    player_init = (*pp)->x14;
    if (player_init != NULL) {
        ev->x4C[0] = *(u8*) player_init;
        ev->x50[0] = ((u8*) (*pp)->x14)[3];
    } else {
        ev->x4C[0] = 0x21;
        ev->x50[0] = 0;
    }
    player_init = (*pp)->x18;
    if (player_init != NULL) {
        ev->x4C[1] = *(u8*) player_init;
        ev->x50[1] = ((u8*) (*pp)->x18)[3];
    } else {
        ev->x4C[1] = 0x21;
        ev->x50[1] = 0;
    }
    player_init = *(s8**) ((u8*) *pp + 0x1C);
    if (player_init != NULL) {
        ev->x4C[2] = *player_init;
        ev->x50[2] = ((u8*) *(s8**) ((u8*) *pp + 0x1C))[3];
    } else {
        ev->x4C[2] = 0x21;
        ev->x50[2] = 0;
    }
    player_init = *(s8**) ((u8*) *pp + 0x20);
    if (player_init != NULL) {
        ev->x4C[3] = *player_init;
        ev->x50[3] = ((u8*) *(s8**) ((u8*) *pp + 0x20))[3];
    } else {
        ev->x4C[3] = 0x21;
        ev->x50[3] = 0;
    }
    if (*(u8*) *pp == 1) {
        ev->x4C[1] = (s8) (*pp)->xC->unk0[0];
        if ((*pp)->xC->unk0[5] == 1) {
            ev->x50[1] = (*pp)->xC->unk0[6];
        } else {
            ev->x50[1] = 0xFF;
        }
        if (((u8*) (*pp)->xC)[0x17] == 1) {
            ev->x45 = 1;
        } else {
            ev->x45 = 0;
        }
    } else {
        ev->x45 = 0;
    }

    result = idx;
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
        event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[ev->x20];
        ev->x4C[1] = *(u8*) event_entry;
        event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[ev->x20];
        ev->x50[1] = ((u8*) event_entry)[3];
        return (s32) event_entry;
    case 35:
        if (ev->x20 == 0) {
            ev->x44 = 2;
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[0];
            ev->x4C[1] = *(u8*) event_entry;
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[0];
            ev->x50[1] = ((u8*) event_entry)[3];
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[2];
            ev->x4C[2] = *(u8*) event_entry;
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[2];
            ev->x50[2] = ((u8*) event_entry)[3];
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[3];
            ev->x4C[3] = *(u8*) event_entry;
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[3];
            ev->x50[3] = ((u8*) event_entry)[3];
            return (s32) event_entry;
        }
        if (ev->x20 == 1) {
            ev->x44 = 4;
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[1];
            ev->x4C[1] = *(u8*) event_entry;
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[1];
            ev->x50[1] = ((u8*) event_entry)[3];
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[4];
            ev->x4C[2] = *(u8*) event_entry;
            event_entry = ((void**) ((u8*) (*pp)->x10 + 0x10))[4];
            ev->x50[2] = ((u8*) event_entry)[3];
            return (s32) event_entry;
        }
        return result;
    case 43:
        x4 = (*pp)->x4;
        event_entry = (void*) x4->x4;
        ev->x4C[2] = *(s8*) event_entry;
        event_entry = (void*) x4->x4;
        ev->x50[2] = ((u8*) event_entry)[3];
        result = (s32) event_entry;
        /* fallthrough */
    default:
        return result;
    }
}

void gm_801BBEA8_OnLoad(void)
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
    if (*temp_r29[temp_r28]->x14 != 0x21) {
        gm_SetScene(1);
    }
}

void gm_801BBFE4_OnUnload(void) {}

void fn_801BBFE8(void)
{
    gm_801A4310();
    gm_801BC00C();
}

s32 gm_801BC00C(void)
{
    struct gm_804D6900_t** event_levels;
    gm_803DF94C_t** event_info = gm_803DF94C;
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    u8 idx = gmMainLib_804D3EE0->unk_530.unk_535;
    void* event_entry;
    u8 ckind;
    u8 costume;
    lbl_8046B6A0_t* mi;
    s32 i;
    s32 entry_offset;
    s8 chr;
    PAD_STACK(0x40);

    gmMainLib_804D3EE0->unk_530.xB_1 = 0;
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
            event_entry = ((void**) ((u8*) event_levels[idx]->x10 + 0x10))[2];
            ftLib_80087508(
                Player_800325C8((CharacterKind) (s8) * (u8*) event_entry, 0),
                *((u8*) event_entry + 3));
            event_entry = ((void**) ((u8*) event_levels[idx]->x10 + 0x10))[3];
            ftLib_80087508(
                Player_800325C8((CharacterKind) (s8) * (u8*) event_entry, 0),
                *((u8*) event_entry + 3));
        } else {
            event_entry = ((void**) ((u8*) event_levels[idx]->x10 + 0x10))[4];
            ftLib_80087508(
                Player_800325C8((CharacterKind) (s8) * (u8*) event_entry, 0),
                *((u8*) event_entry + 3));
        }
        break;
    case 43:
        chr = Player_800325C8(
            (CharacterKind) (s8) * (u8*) event_levels[idx]->x4->x4, 0);
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
            mi = gm_8016AE44();
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
        for (i = ev->x20, entry_offset = i * 4;
             i < (s32) * (u8*) event_levels[idx]->x10; i++, entry_offset += 4)
        {
            event_entry =
                *(void**) ((u8*) event_levels[idx]->x10 + entry_offset + 0x10);
            ckind = *(u8*) event_entry;
            costume = *((u8*) event_entry + 3);
            {
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                if ((s8) ev2->x0 == (s8) ckind && (u8) ev2->x1 == costume) {
                    if (costume <= 2) {
                        costume += 1;
                    } else {
                        costume = 0;
                    }
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
        }
        break;
    case 35:
        if (ev->x20 == 0) {
            event_entry = ((void**) ((u8*) event_levels[idx]->x10 + 0x10))[0];
            ckind = *(u8*) event_entry;
            costume = *((u8*) event_entry + 3);
            {
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                if ((s8) ev2->x0 == (s8) ckind && (u8) ev2->x1 == costume) {
                    if (costume <= 2) {
                        costume += 1;
                    } else {
                        costume = 0;
                    }
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
            event_entry = ((void**) ((u8*) event_levels[idx]->x10 + 0x10))[2];
            ckind = *(u8*) event_entry;
            costume = *((u8*) event_entry + 3);
            {
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                if ((s8) ev2->x0 == (s8) ckind && (u8) ev2->x1 == costume) {
                    if (costume <= 2) {
                        costume += 1;
                    } else {
                        costume = 0;
                    }
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
            event_entry = ((void**) ((u8*) event_levels[idx]->x10 + 0x10))[3];
            ckind = *(u8*) event_entry;
            costume = *((u8*) event_entry + 3);
            {
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                if ((s8) ev2->x0 == (s8) ckind && (u8) ev2->x1 == costume) {
                    if (costume <= 2) {
                        costume += 1;
                    } else {
                        costume = 0;
                    }
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
        }
        if (ev->x20 <= 1) {
            event_entry = ((void**) ((u8*) event_levels[idx]->x10 + 0x10))[1];
            ckind = *(u8*) event_entry;
            costume = *((u8*) event_entry + 3);
            {
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                if ((s8) ev2->x0 == (s8) ckind && (u8) ev2->x1 == costume) {
                    if (costume <= 2) {
                        costume += 1;
                    } else {
                        costume = 0;
                    }
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
            event_entry = ((void**) ((u8*) event_levels[idx]->x10 + 0x10))[4];
            ckind = *(u8*) event_entry;
            costume = *((u8*) event_entry + 3);
            {
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                if ((s8) ev2->x0 == (s8) ckind && (u8) ev2->x1 == costume) {
                    if (costume <= 2) {
                        costume += 1;
                    } else {
                        costume = 0;
                    }
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
        }
        break;
    }

    if (idx == 0x24) {
        lbBgFlash_80021A10(0.2f);
    }
    Camera_80030E34(ev->x1C);
    return (s32) HSD_GObj_SetupProc(GObj_Create(0xF, 0x11, 0),
                                    event_info[idx]->x0, 0x15);
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
    (void (*)(int)) gm_801BEA88,
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

GameScene gm_803DFA18_Scenes[] = {
    {
        0,
        2,
        0,
        NULL,
        gm_801BEC80,
        {
            GS_TOY_GALLERY,
            NULL,
            &gm_804D6908,
        },
    },
    { 0xFF },
};

GameScene gm_803DFA48_Scenes[] = {
    {
        0,
        2,
        0,
        gm_801BECA8,
        gm_801BECD0,
        {
            GS_TOY_LOTTERY,
            NULL,
            &gm_804D6910,
        },
    },
    { 0xFF },
};

GameScene gm_803DFA78_Scenes[] = {
    {
        0,
        2,
        0,
        NULL,
        gm_801BED14,
        {
            GS_TOY_COLLECTION,
            NULL,
            &gm_804D6918,
        },
    },
    { 0xFF },
};

GameScene gm_803DFAA8_Scenes[] = {
    {
        0,
        2,
        0,
        gm_801BED3C,
        gm_801BEDA8,
        {
            GS_CSS,
            &gm_8049BEE8,
            NULL,
        },
    },
    { 0xFF },
};

GameScene gm_803DFAD8_Scenes[] = {
    {
        0,
        2,
        0,
        gm_801BEE58,
        NULL,
        {
            GS_SSS,
            &gm_8049C030,
            NULL,
        },
    },
    { 0xFF },
};

GameScene gm_803DFB08[] = {
    {
        0,
        2,
        0,
        NULL,
        NULL,
        {
            GS_REGEND_TOYFALL,
            NULL,
            &gm_804D6920,
        },
    },
    {
        1,
        2,
        0,
        NULL,
        NULL,
        {
            GS_STAFFROLL,
            NULL,
            NULL,
        },
    },
    {
        2,
        2,
        0,
        NULL,
        gm_801BEF84,
        {
            GS_MOVIE_END,
            NULL,
            NULL,
        },
    },
    {
        3,
        2,
        0,
        NULL,
        gm_801BEE9C,
        {
            GS_REGEND_CONGRATS,
            NULL,
            &gm_804D6920,
        },
    },
    { 0xFF },
};

GameScene gm_803DFB80_Scenes[] = {
    {
        0,
        2,
        0,
        NULL,
        NULL,
        {
            GS_REGEND_TOYFALL,
            NULL,
            &gm_804D6920,
        },
    },
    {
        1,
        2,
        0,
        NULL,
        gm_801BEE9C,
        {
            GS_REGEND_CONGRATS,
            NULL,
            &gm_804D6920,
        },
    },
    { 0xFF },
};

GameScene gm_803DFBC8_Scenes[] = {
    {
        0,
        3,
        0,
        gm_801BF85C,
        gm_801BF898,
        {
            GS_MOVIE_OPENING,
            NULL,
            NULL,
        },
    },
    {
        1,
        3,
        0,
        gm_801BF4DC,
        NULL,
        {
            GS_VS,
            &gm_8049C188,
            &gm_8049C2C0,
        },
    },
    {
        2,
        3,
        0,
        gm_801B087C,
        gm_801BF060,
        {
            GS_TITLE,
            NULL,
            &gm_804D6930,
        },
    },
    {
        3,
        3,
        0,
        gm_801BF4DC,
        NULL,
        {
            GS_VS,
            &gm_8049C188,
            &gm_8049C2C0,
        },
    },
    {
        4,
        3,
        0,
        NULL,
        gm_801BF8B8,
        {
            GS_MOVIE_HOWTO,
            NULL,
            NULL,
        },
    },
    {
        5,
        3,
        0,
        NULL,
        gm_801BF8D8,
        {
            GS_MOVIE_OMAKE15,
            NULL,
            NULL,
        },
    },
    { 0xFF },
};

GameScene gm_803DFC70_Scenes[] = {
    {
        0,
        2,
        0,
        gm_801BF728,
        NULL,
        {
            GS_CUTSCENE_LUIGI,
            &un_804D6F3C,
            NULL,
        },
    },
    {
        1,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_BRINSTAR,
            &un_804D6F60,
            NULL,
        },
    },
    {
        2,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_EXPLOSION,
            NULL,
            NULL,
        },
    },
    {
        3,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_3KIRBYS,
            &un_804D6F84,
            NULL,
        },
    },
    {
        4,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_GIANTKIRBY,
            &un_804D6FA8,
            NULL,
        },
    },
    {
        5,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_STARFOX,
            NULL,
            NULL,
        },
    },
    {
        6,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_FZERO,
            NULL,
            NULL,
        },
    },
    {
        7,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_METAL,
            &un_804D6FD8,
            NULL,
        },
    },
    {
        8,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_BOWSERTOY,
            &un_804D7004,
            NULL,
        },
    },
    {
        9,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_GIGATRANSFORM,
            &un_804D7038,
            NULL,
        },
    },
    {
        10,
        2,
        0,
        NULL,
        NULL,
        {
            GS_CUTSCENE_GIGADEFEATED,
            NULL,
            NULL,
        },
    },
    {
        11,
        2,
        0,
        NULL,
        gm_801BF834,
        {
            GS_REGEND_CONGRATS,
            &gm_804D6928,
            &gm_804D692C,
        },
    },
    { 0xFF },
};

GameScene gm_803DFDA8_Scenes[] = {
    {
        0,
        2,
        0,
        gm_801BF8F8,
        gm_801BF920,
        {
            GS_PROG_SCAN,
            &gm_804D6938,
            &gm_804D693C,
        },
    },
    { 0xFF },
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
    if (Player_80036394(0) == 7) {
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
    switch (gm_8016AE38()->x24C8.x0_0) {
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
        temp_r3 = gm_8016AE38();
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
        temp_r3_2 = gm_8016AE38();
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
        gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535][0]->x4;
    u32 coins = Player_GetCoins(0);
    PAD_STACK(0x28);

    if (coins >= temp_r30->x0) {
        gm_801BC4F4(gobj);
        return;
    }
    temp_r30_2 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_8016AE38();
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
            if (ftLib_800872A4(temp_r3) == FTKIND_SEAK) {
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
    temp_r3_2 = gm_8016AE38();
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
    u8* inner;
    struct gm_evspawn* cd;
    u8 costume;
    lbl_8046B6A0_t* mi;
    s32 var_r0;
    PAD_STACK(0x40);

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
        ev2 = &gmMainLib_804D3EE0->unk_530;
        inner = (u8*) (*entry)->x10;
        cd = ((struct gm_evspawn**) (inner + 0x10))[ev->x20];
        costume = cd->unk3;
        if ((s8) ev2->x0 == cd->unk0 && (u8) ev2->x1 == costume) {
            if (costume <= 2) {
                costume += 1;
            } else {
                costume = 0;
            }
        }
        gm_8016AC44(cd->unk0, (s8) costume);
        if (ev->x20 >= (s32) (*(u8*) (*entry)->x10 - 1)) {
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
        struct EventData* temp_r31 = &gmMainLib_804D3EE0->unk_530;
        mi = gm_8016AE38();
        if (temp_r31->xB_0) {
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
    temp_r3 = gm_8016AE38();
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
    rules = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    temp_r3 = gm_8016AE38();
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
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    u8 level = ev->unk_535;
    u64 mask;
    struct gm_804D6900_x4_t* x4 = (*tbl)->x4;
    PAD_STACK(0x44);

    if (!ev->xB_5) {
        ev->xB_5 = 1;
        if (ev->x20 == 0) {
            mask = lbAudioAx_80026E84(
                (enum CharacterKind)(s8) (u8) *tbl[level]->x14);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind)((struct gm_evx10*) tbl[level]->x10)
                    ->unk10->unk0);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind)((struct gm_evx10*) tbl[level]->x10)
                    ->unk18->unk0);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind)((struct gm_evx10*) tbl[level]->x10)
                    ->unk1C->unk0);
        } else {
            mask = lbAudioAx_80026E84(
                (enum CharacterKind)(s8) (u8) *tbl[level]->x14);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind)((struct gm_evx10*) tbl[level]->x10)
                    ->unk14->unk0);
            mask |= lbAudioAx_80026E84(
                (enum CharacterKind)((struct gm_evx10*) tbl[level]->x10)
                    ->unk20->unk0);
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
                gm_801BAB40(&sp50,
                            (int) ((struct gm_evx10*) tbl[level]->x10)->unk18);
                gm_8016EDDC(2, &sp50);
            }
            break;
        case 1:
            if (Player_GetStocks(2) <= 0) {
                ev->x18 = 2;
                gm_801BAB40(&sp50,
                            (int) ((struct gm_evx10*) tbl[level]->x10)->unk1C);
                gm_8016EDDC(3, &sp50);
            }
            break;
        case 2:
            if (Player_GetStocks(3) <= 0) {
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                struct gm_evspawn* sp =
                    ((struct gm_evx10*) tbl[level]->x10)->unk1C;
                u8 color = sp->unk3;
                if ((s8) ev2->x0 == sp->unk0 && (u8) ev2->x1 == color) {
                    if (color <= 2) {
                        color += 1;
                    } else {
                        color = 0;
                    }
                }
                gm_8016AC44(sp->unk0, color);
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
                gm_801BAB40(&sp50,
                            (int) ((struct gm_evx10*) tbl[level]->x10)->unk20);
                gm_8016EDDC(2, &sp50);
            }
            break;
        case 1:
            if (Player_GetStocks(2) <= 0) {
                struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
                struct gm_evspawn* sp =
                    ((struct gm_evx10*) tbl[level]->x10)->unk20;
                u8 color = sp->unk3;
                if ((s8) ev2->x0 == sp->unk0 && (u8) ev2->x1 == color) {
                    if (color <= 2) {
                        color += 1;
                    } else {
                        color = 0;
                    }
                }
                gm_8016AC44(sp->unk0, color);
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
        struct EventData* ev2 = &gmMainLib_804D3EE0->unk_530;
        lbl_8046B6A0_t* info = gm_8016AE38();
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
        temp_ret |= lbAudioAx_80026E84(*temp_r28[temp_r0]->x18);
        temp_ret |= lbAudioAx_80026E84(*(s8*) temp_r30->x4);
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
        gm_801BAB40(&sp40, temp_r30->x4);
        sp40.color = temp_r31->x50[2];
        gm_8016EDDC(2, &sp40);
    }
    temp_r27_5 = &gmMainLib_804D3EE0->unk_530;
    temp_r3_2 = gm_8016AE38();
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
            lbl_8046B6A0_t* tmp = gm_8016AE38();
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
            temp_r3 = gm_8016AE38();
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
    temp_r3_4 = gm_8016AE38();
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
        arg0, gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535][0]->xC->x16);
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
    return gm_804D6900[arg0][0]->x8->x1_0;
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
        return 0x21;
    }

    ptr = *(u8**) ((u8*) entry + 0x14);
    return *ptr;
}

UNK_T gm_801BEC54(void)
{
    struct gm_804D6900_t* temp_r3;
    temp_r3 = gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535][0];
    if (temp_r3 == NULL) {
        return NULL;
    }
    return temp_r3->x4;
}

void gm_801BEC80(GameScene* arg)
{
    gm_801A42E8(GM_MENU);
    gm_801A42D4();
}

void gm_801BECA8(GameScene* arg)
{
    lb_8001C550();
    lb_8001D164(0);
}

void gm_801BECD0(GameScene* arg)
{
    gm_80172898(4);
    if (!gm_80173754(1, 0)) {
        gm_801A42E8(GM_MENU);
        gm_801A42D4();
    }
}

void gm_801BED14(GameScene* arg)
{
    gm_801A42E8(GM_MENU);
    gm_801A42D4();
}

void gm_801BED3C(GameScene* arg0)
{
    CSSData* temp_r31 = gm_801A427C(arg0);
    temp_r31->data = *gm_801A5244();

    gm_80164F18();
    if (temp_r31->match_type & 1) {
        gm_80164A0C(7);
    }
}

void gm_801BEDA8(GameScene* arg0)
{
    CSSData* css = gm_801A427C(arg0);
    VsModeData* vs = gm_801A5244();

    if (css->pending_scene_change == 2) {
        if (css->match_type != 0) {
            css->match_type--;
        } else {
            css->match_type = 0x17;
        }
    } else {
        css->match_type = (css->match_type + 1) % 24;
    }

    *vs = css->data;
}

void gm_801BEE58(GameScene* arg0)
{
    SSSData* var_r3 = gm_801A427C(arg0);
    var_r3->data = gmMainLib_804D3EE0->unk_590;
}

void gm_801BEE9C(GameScene* arg0)
{
    s8* temp_r28;
    u8 temp_r27; ///< maybe CharacterKind?

    temp_r28 = arg0->info.leave_data;
    temp_r27 = gm_80173224(gm_801BF030(), 1);
    if (gm_801BEFB0() == CKIND_GAMEWATCH && !gm_80164430(0x1B)) {
        gm_80164504(0x1B);
    }
    gm_8017390C(gm_801BF030(), 1);
    gm_80173EEC();
    gm_80172898(0x40);
    if (temp_r27 == 0x21) {
        if (!gm_80173754(1, gm_801BEFD0())) {
            gm_801A42E8(*temp_r28);
        }
    } else {
        gm_801736E8(gm_801BEFB0(), gm_801BEFD0(), gm_801BF010(), gm_801BEFF0(),
                    temp_r27, *temp_r28);
        gm_801A42E8(GM_CHALLENGER_APPROACH);
    }
    gm_801A42D4();
}

void gm_801BEF84(GameScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BEFA4(int ckind)
{
    gm_8049C178[0] = ckind;
}

static inline void gm_801BEFA4_inner3(int ckind)
{
    gm_801BEFA4(ckind);
}

static inline void gm_801BEFA4_inner2(int ckind)
{
    gm_801BEFA4_inner3(ckind);
}

static inline void gm_801BEFA4_inner(int ckind)
{
    gm_801BEFA4_inner2(ckind);
}

static inline void gm_801BEFA4_noinline(int ckind)
{
    gm_801BEFA4_inner(ckind);
}

CharacterKind gm_801BEFB0(void)
{
    return gm_8049C178[0];
}

void gm_801BEFC0(int arg0)
{
    gm_8049C178[1] = arg0;
}

static inline void gm_801BEFC0_inner3(int arg0)
{
    gm_801BEFC0(arg0);
}

static inline void gm_801BEFC0_inner2(int arg0)
{
    gm_801BEFC0_inner3(arg0);
}

static inline void gm_801BEFC0_inner(int arg0)
{
    gm_801BEFC0_inner2(arg0);
}

static inline void gm_801BEFC0_noinline(int arg0)
{
    gm_801BEFC0_inner(arg0);
}

int gm_801BEFD0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 1);
}

void gm_801BEFE0(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 0xA) = arg0;
}

int gm_801BEFF0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 0xA);
}

void gm_801BF000(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 9) = arg0;
}

int gm_801BF010(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 9);
}

void gm_801BF020(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 8) = arg0;
}

int gm_801BF030(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 8);
}

void gm_801BF040(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 2) = arg0;
}

int gm_801BF050(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 2);
}

void gm_801BF060(GameScene* arg0)
{
    int* temp_r3 = gm_801A4284(arg0);
    if (DbLevel >= 3) {
        if (*temp_r3 & 0x100) {
            gm_801A42E8(GM_DEBUG_VS);
            gm_801A42D4();
        } else if (*temp_r3 & 0x1000) {
            gm_801A42E8(GM_MENU);
            gm_801A42D4();
        } else if (*temp_r3 & 0x400) {
            gm_801A42E8(GM_DEBUG_SOUND_TEST);
            gm_801A42D4();
        } else if (*temp_r3 & 0x800) {
            gm_801A42E8(GM_DEBUG);
            gm_801A42D4();
        }
    } else if (*temp_r3 & 0x1000) {
        gm_80173EEC();
        gm_80172898(0x100);
        if (!gm_80173754(1, 0)) {
            gm_801A42E8(GM_MENU);
        }
        gm_801A42D4();
    }
}

void gm_801BF128(void)
{
    s32 character_pool[29];
    s32 stage_pool[30];
    s32 c;
    s32 count;
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    s32 pick;
    s32 dup;
    s32 prev;
    u8 cur_id;
    PAD_STACK(0x38);

    count = 0;
    c = 0;
    do {
        if (gm_80164840(c) != 0) {
            character_pool[count] = c;
            count += 1;
        }
        c += 1;
    } while ((s32) c < 0x1A);
    character_pool[count] = 0x1A;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            a = character_pool[i];
            b = character_pool[j];
            if ((s32) ((u8*) gmMainLib_804D3EE0)[a + 2] >
                (s32) ((u8*) gmMainLib_804D3EE0)[b + 2])
            {
                character_pool[i] = b;
                character_pool[j] = a;
            }
        }
    }
    c = 0;
    do {
        do {
            j = character_pool[HSD_Randi(8)];
            dup = 0;
            for (pick = 0; pick < c; pick++) {
                if (j == gm_801BF648(pick) ||
                    (j == 0x12 && gm_801BF648(pick) == 0x13) ||
                    (j == 0x13 && gm_801BF648(pick) == 0x12))
                {
                    dup = 1;
                }
            }
        } while (dup != 0);
        gm_801BF634(c, j);
        gm_801BF65C(c, 0);
        c += 1;
        ((u8*) gmMainLib_804D3EE0)[j + 2] += 1;
    } while (c < 4);
    gm_801BF6C8(HSD_Randi(4));
    do {
        gm_801BF6E8(HSD_Randi(4));
        prev = gm_801BF6F8();
    } while (gm_801BF6D8() == prev);

    count = 0;
    c = 0;
    do {
        if (gm_80164430(gm_801641CC(c)) != 0) {
            stage_pool[count] = c;
            count += 1;
        }
        c += 1;
    } while ((s32) c < 0x1D);
    stage_pool[count] = 0x1D;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            a = stage_pool[i];
            b = stage_pool[j];
            if ((s32) ((u8*) gmMainLib_804D3EE0)[a + 0x1C] >
                (s32) ((u8*) gmMainLib_804D3EE0)[b + 0x1C])
            {
                stage_pool[i] = b;
                stage_pool[j] = a;
            }
        }
    }
    do {
        pick = stage_pool[HSD_Randi(8)];
        cur_id = gm_801BF694();
    } while ((s32) gm_801641CC((u8) pick) == (s32) cur_id);
    gm_801BF684(gm_801641CC((u8) pick));
    ((u8*) gmMainLib_804D3EE0)[pick + 0x1C] += 1;
    gm_801BF6A8(HSD_Randi(4));
}

void gm_801BF3F8(void)
{
    struct GameCache* var_r31;
    u64 temp_ret;
    int i;
    int j;
    int c_kind;

    var_r31 = &lbDvd_8001822C()->game_cache;
    lbDvd_80018C6C();

    for (i = 0; i < 4; i++) {
        var_r31->entries[i].char_id = gm_801BF648(i);
        var_r31->entries[i].color = gm_801BF670(i);
    }
    var_r31->stage_id = gm_801BF694();
    lbDvd_80018254();

    temp_ret = 4;
    for (j = 0; j < 4; j++) {
        c_kind = gm_801BF648(j);
        if (c_kind != CHKIND_NONE) {
            temp_ret |= lbAudioAx_80026E84(c_kind);
        }
    }
    temp_ret |= lbAudioAx_80026EBC(gm_801BF694());
    lbAudioAx_80026F2C(0x1E);
    lbAudioAx_8002702C(0xE, temp_ret);
    lbAudioAx_80027168();
}

void gm_801BF4DC(GameScene* arg0)
{
    StartMeleeData* temp_r31;
    VsModeData* temp_r30;
    int i;

    temp_r30 = &gmMainLib_804D3EE0->unk_1710;
    temp_r31 = gm_801A427C(arg0);
    gm_80167BC8(temp_r30);
    gm_8016F088(temp_r31);
    gm_80168FC4();
    gm_80167A64(&temp_r31->rules);

    temp_r31->rules.x0_0 = gm_801BF6B8();
    temp_r31->rules.x0_6 = false;
    temp_r31->rules.x10 = 0;
    temp_r31->rules.x1_0 = false;
    temp_r31->rules.x1_2 = true;
    temp_r31->rules.x1_3 = true;
    temp_r31->rules.x2_4 = true;
    temp_r31->rules.x7 = 0;
    temp_r31->rules.x44 = gm_80183218;
    temp_r31->rules.x34 = 1.0F;
    temp_r31->rules.xE = (u16) gm_801BF694();
    gm_80167A14(temp_r31->players);

    for (i = 0; i < 4; i++) {
        CharacterKind kind = gm_801BF648(i);
        temp_r31->players[i].c_kind = kind;
        temp_r31->players[i].color = gm_801BF670(i);
        temp_r31->players[i].slot_type = Gm_PKind_Cpu;
        temp_r31->players[i].cpu_level = 9;
        temp_r31->players[i].xE = 4;
        temp_r31->players[i].xC_b1 = false;
        if (temp_r31->rules.x0_0 == 1) {
            temp_r31->players[i].stocks = 0x63;
        }
    }
}

void gm_801BF634(s32 arg0, s8 character_kind)
{
    gm_8049E548.c_kind[arg0] = character_kind;
}

int gm_801BF648(s32 arg0)
{
    return (u8) gm_8049E548.c_kind[arg0];
}

void gm_801BF65C(s32 arg0, s8 arg1)
{
    gm_8049E548.x4[arg0] = arg1;
}

u8 gm_801BF670(s32 arg0)
{
    return gm_8049E548.x4[arg0];
}

void gm_801BF684(s16 arg0)
{
    gm_8049E548.unk_C = arg0;
}

u8 gm_801BF694(void)
{
    return gm_8049E548.unk_C;
}

void gm_801BF6A8(s8 arg0)
{
    gm_8049E548.unk_A = arg0;
}

u8 gm_801BF6B8(void)
{
    return gm_8049E548.unk_A;
}

void gm_801BF6C8(s8 arg0)
{
    gm_8049E548.unk_8 = arg0;
}

int gm_801BF6D8(void)
{
    return gm_8049E548.unk_8;
}

void gm_801BF6E8(s8 arg0)
{
    gm_8049E548.unk_9 = arg0;
}

int gm_801BF6F8(void)
{
    return gm_8049E548.unk_9;
}

void gm_801BF708(s8 arg0)
{
    gm_8049E548.unk_E = arg0;
}

u8 gm_801BF718(void)
{
    return gm_8049E548.unk_E;
}

void gm_801BF728(GameScene* arg)
{
    s32 temp_r31;
    s32 temp_r31_2;
    PAD_STACK(4);

    un_804D6F3C[1] = 1;
    un_804D6F3C[3] = 1;
    vi0401_8031D020(0xE, HSD_Randi(4));
    temp_r31 = HSD_Randi(4);
    un_8031D9E4(0xE, HSD_Randi(4), temp_r31);
    un_804D6F84[4] = HSD_Randi(0x1B);
    un_804D6F84[5] = HSD_Randi(0x1B);
    un_804D6F84[6] = HSD_Randi(0x1B);
    temp_r31_2 = HSD_Randi(4);
    un_8031E110(0xE, HSD_Randi(4), temp_r31_2);
    un_804D6FD8[0] = 0xE;
    un_804D6FD8[1] = HSD_Randi(4);
    un_8031F980(0xE, HSD_Randi(4));
    un_803204B0(0xE, HSD_Randi(4));
    gm_801BEFA4_noinline(8);
    gm_801BEFC0_noinline(HSD_Randi(4));
}

void gm_801BF834(GameScene* arg)
{
    gm_801A42E8(GM_TITLE);
    gm_801A42D4();
}

void gm_801BF85C(GameScene* arg)
{
    PreloadCacheScene* temp_r31 = lbDvd_8001822C();
    PAD_STACK(4);
    lbDvd_800174BC();
    temp_r31->is_heap_persistent[1] = false;
    lbDvd_80018254();
}

void gm_801BF898(GameScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8B8(GameScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8D8(GameScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8F8(GameScene* arg0)
{
    int* val = gm_801A427C(arg0);
    *val = 1;
}

void gm_801BF920(GameScene* arg0)
{
    gm_801A4284(arg0);
    gm_801A42F8(GM_BOOT);
}
