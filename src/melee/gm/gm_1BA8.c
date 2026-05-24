#include "gm_1BA8.h"

#include "gm_1BA8.static.h"

#include "gm_unsplit.h"

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
#include <melee/it/items/itevyoshiegg.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/gr/ground.h>
#include <melee/if/ifstock.h>
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

/* 49E548 */ static struct gm_8049E548_t gm_8049E548;

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

#pragma push
#pragma dont_inline on
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
#pragma pop

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
    u8 chars[33];
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    void* data = gm_801A427C(arg0);
    struct gm_804D6900_t* entry = gm_804D6900[ev->unk_535];
    u8* dst = chars;
    s32 count = 0;
    s32 i;

    for (i = 0; i < 0x21; i++) {
        u8 c = ((u8*) entry->x4)[i];
        if (c == 0x21) {
            break;
        }
        {
            s32 found = 0;
            s32 k;
            for (k = 0; k < arg1; k++) {
                if (*(s8*) ((u8*) data + 0x60 + k * 0x24) == (s8) c) {
                    found++;
                }
            }
            if (found == 0) {
                *dst++ = c;
                count++;
            }
        }
    }
    return chars[HSD_Randi(count)];
}

/// #gm_801BAD70

void gm_801BB758(GameScene* arg0)
{
    MatchExitInfo* exit = gm_801A4284(arg0);
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    u8 stage = ev->unk_535;
    u8 b;
    enum CharacterKind kind;
    s32 t;

    gm_8016A164();
    if (*(u8*) ((u8*) exit + 0x10) == 8) {
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
            PreloadCacheScene* gc = lbDvd_8001822C();
            lbDvd_80018C6C();
            gc->game_cache.entries[0].char_id = (s8) ev->x0;
            gc->game_cache.entries[0].color = ev->x1;
            lbDvd_80018254();
            lbDvd_80017700(4);
        }
        gm_SetPendingScene(1);
        return;
    }
    if (*(u8*) ((u8*) exit + 0x10) == 7) {
        gm_801A42F8(1);
        return;
    }
    ev->x3C += gm_80168940((MatchEnd*) ((u8*) &gm_80497758 + 0x28C));
    ev->x40 += *(s32*) ((u8*) exit + 0x14);
    b = ((u8*) ev)[0xB];
    if (((b >> 3) & 1) && ((b >> 5) & 1)) {
        ev->x24 = *(s8*) ((u8*) &gm_80497758 + 0x2EC);
        ev->x28 = *(u16*) ((u8*) &gm_80497758 + 0x2F0);
        ev->xB_2 = 0;
        ev->xB_5 = 0;
        t = ev->x20;
        ev->x20 = t + 1;
        gm_801BBB64();
        gm_SetPendingScene(1);
        return;
    }
    if (ev->xB_1) {
        s32 cur = ev->xC;
        s32 best = gmMainLib_8015CF5C(stage);
        s32 upd = 0;
        if (ev->xB_6) {
            if (best == 0 || cur < best) {
                best = cur;
                upd = 1;
            }
        } else if ((u32) cur > (u32) best) {
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
    if (ev->unk_535 == gm_801BEBC0(0x32) && *(s32*) ((u8*) exit + 0x6C) == 3) {
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
    if ((u8) kind != 0x21) {
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
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    struct gm_804D6900_t** pp;
    s32 idx = gmMainLib_804D3EE0->unk_530.unk_535;
    s8* p;
    void* cd;
    u8* inner;
    s32 var_r3;

    if (*gm_804D6900[idx]->x14 != 0x21) {
        ev->x44 = 0;
    } else {
        ev->x44 = 1;
    }
    pp = &gm_804D6900[idx];
    ev->x48 = (InternalStageId) *(u16*) ((u8*) (*pp)->x8 + 6);
    p = (*pp)->x14;
    if (p != NULL) {
        ev->x4C[0] = *(u8*) p;
        ev->x50[0] = ((u8*) p)[3];
    } else {
        ev->x4C[0] = 0x21;
        ev->x50[0] = 0;
    }
    p = (*pp)->x18;
    if (p != NULL) {
        ev->x4C[1] = *(u8*) p;
        ev->x50[1] = ((u8*) p)[3];
    } else {
        ev->x4C[1] = 0x21;
        ev->x50[1] = 0;
    }
    p = *(s8**) ((u8*) *pp + 0x1C);
    if (p != NULL) {
        ev->x4C[2] = *p;
        ev->x50[2] = ((u8*) p)[3];
    } else {
        ev->x4C[2] = 0x21;
        ev->x50[2] = 0;
    }
    p = *(s8**) ((u8*) *pp + 0x20);
    if (p != NULL) {
        ev->x4C[3] = *p;
        ev->x50[3] = ((u8*) p)[3];
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

    var_r3 = idx;
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
        cd = ((void**) ((u8*) (*pp)->x10 + 0x10))[ev->x20];
        ev->x4C[1] = *(u8*) cd;
        ev->x50[1] = ((u8*) cd)[3];
        return (s32) cd;
    case 35:
        if (ev->x20 == 0) {
            ev->x44 = 2;
            inner = (u8*) (*pp)->x10;
            cd = ((void**) (inner + 0x10))[0];
            ev->x4C[1] = *(u8*) cd;
            ev->x50[1] = ((u8*) cd)[3];
            cd = ((void**) (inner + 0x10))[2];
            ev->x4C[2] = *(u8*) cd;
            ev->x50[2] = ((u8*) cd)[3];
            cd = ((void**) (inner + 0x10))[3];
            ev->x4C[3] = *(u8*) cd;
            ev->x50[3] = ((u8*) cd)[3];
            return (s32) cd;
        }
        if (ev->x20 == 1) {
            ev->x44 = 4;
            inner = (u8*) (*pp)->x10;
            cd = ((void**) (inner + 0x10))[1];
            ev->x4C[1] = *(u8*) cd;
            ev->x50[1] = ((u8*) cd)[3];
            cd = ((void**) (inner + 0x10))[4];
            ev->x4C[2] = *(u8*) cd;
            ev->x50[2] = ((u8*) cd)[3];
            return (s32) cd;
        }
        return var_r3;
    case 43:
        cd = (void*) (*pp)->x4->x4;
        ev->x4C[2] = *(s8*) cd;
        ev->x50[2] = ((u8*) cd)[3];
        var_r3 = (s32) cd;
        /* fallthrough */
    default:
        return var_r3;
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

    temp_r29 = gm_804D6900;
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
    struct gm_804D6900_t** var_r29 = gm_804D6900;
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    s32 idx = gmMainLib_804D3EE0->unk_530.unk_535;
    u8* inner;
    void* cd;
    u8 ckind;
    u8 costume;
    lbl_8046B6A0_t* mi;
    s32 i;
    s8 chr;

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
        var_r29 = gm_804D6900;
        break;
    }

    switch (idx) {
    case 35:
        if (ev->x20 == 0) {
            inner = (u8*) var_r29[idx]->x10;
            cd = ((void**) (inner + 0x10))[2];
            ftLib_80087508(
                Player_800325C8((CharacterKind) (s8) *(u8*) cd, 0),
                *((u8*) cd + 3));
            cd = ((void**) (inner + 0x10))[3];
            ftLib_80087508(
                Player_800325C8((CharacterKind) (s8) *(u8*) cd, 0),
                *((u8*) cd + 3));
        } else {
            cd = ((void**) ((u8*) var_r29[idx]->x10 + 0x10))[4];
            ftLib_80087508(
                Player_800325C8((CharacterKind) (s8) *(u8*) cd, 0),
                *((u8*) cd + 3));
        }
        break;
    case 43:
        chr = Player_800325C8(
            (CharacterKind) (s8) *(u8*) var_r29[idx]->x4->x4, 0);
        ftLib_80087508(chr, ev->x50[2]);
        if (ev->x0 == 4) {
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
        for (i = ev->x20; i < (s32) *(u8*) var_r29[idx]->x10; i++) {
            cd = ((void**) ((u8*) var_r29[idx]->x10 + 0x10))[i];
            ckind = *(u8*) cd;
            costume = *((u8*) cd + 3);
            if ((s8) ev->x0 == (s8) ckind && (u8) ev->x1 == costume) {
                if (costume <= 2) {
                    costume += 1;
                } else {
                    costume = 0;
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
        }
        break;
    case 35:
        if (ev->x20 == 0) {
            inner = (u8*) var_r29[idx]->x10;
            cd = ((void**) (inner + 0x10))[0];
            ckind = *(u8*) cd;
            costume = *((u8*) cd + 3);
            if ((s8) ev->x0 == (s8) ckind && (u8) ev->x1 == costume) {
                if (costume <= 2) {
                    costume += 1;
                } else {
                    costume = 0;
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
            cd = ((void**) (inner + 0x10))[2];
            ckind = *(u8*) cd;
            costume = *((u8*) cd + 3);
            if ((s8) ev->x0 == (s8) ckind && (u8) ev->x1 == costume) {
                if (costume <= 2) {
                    costume += 1;
                } else {
                    costume = 0;
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
            cd = ((void**) (inner + 0x10))[3];
            ckind = *(u8*) cd;
            costume = *((u8*) cd + 3);
            if ((s8) ev->x0 == (s8) ckind && (u8) ev->x1 == costume) {
                if (costume <= 2) {
                    costume += 1;
                } else {
                    costume = 0;
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
        }
        if (ev->x20 <= 1) {
            inner = (u8*) var_r29[idx]->x10;
            cd = ((void**) (inner + 0x10))[1];
            ckind = *(u8*) cd;
            costume = *((u8*) cd + 3);
            if ((s8) ev->x0 == (s8) ckind && (u8) ev->x1 == costume) {
                if (costume <= 2) {
                    costume += 1;
                } else {
                    costume = 0;
                }
            }
            gm_8016A9E8(ckind, (s8) costume);
            cd = ((void**) (inner + 0x10))[4];
            ckind = *(u8*) cd;
            costume = *((u8*) cd + 3);
            if ((s8) ev->x0 == (s8) ckind && (u8) ev->x1 == costume) {
                if (costume <= 2) {
                    costume += 1;
                } else {
                    costume = 0;
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
                                    gm_803DF94C[idx]->x0, 0x15);
}

static u8 gm_803DF918[] = {
    0x00, 0x11, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
    0x0B, 0x0C, 0x0D, 0x24, 0x0F, 0x10, 0x01, 0x12, 0x13, 0x14, 0x15,
    0x1A, 0x17, 0x18, 0x19, 0x16, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x2F, 0x23, 0x0E, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
    0x2C, 0x2D, 0x2E, 0x22, 0x30, 0x31, 0x32,
};

extern gm_803DF94C_t gm_804D4330, gm_804D43B8, gm_804D4340, gm_804D4348,
    gm_804D4350, gm_804D4358, gm_804D4360, gm_804D4368, gm_804D4370,
    gm_804D4378, gm_804D4380, gm_804D4388, gm_804D4390, gm_804D4398,
    gm_804D4450, gm_804D43A8, gm_804D43B0, gm_804D4338, gm_804D43C0,
    gm_804D43C8, gm_804D43D0, gm_804D43D8, gm_804D4400, gm_804D43E8,
    gm_804D43F0, gm_804D43F8, gm_804D43E0, gm_804D4408, gm_804D4410,
    gm_804D4418, gm_804D4420, gm_804D4428, gm_804D4430, gm_804D4438,
    gm_804D44A8, gm_804D4448, gm_804D43A0, gm_804D4458, gm_804D4460,
    gm_804D4468, gm_804D4470, gm_804D4478, gm_804D4480, gm_804D4488,
    gm_804D4490, gm_804D4498, gm_804D44A0, gm_804D4440, gm_804D44B0,
    gm_804D44B8, gm_804D44C0;

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
    struct gm_804D6900_x4_t* temp_r30 = gm_804D6900[0]->x4;
    PAD_STACK(0x18);

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
        gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535]->x4;
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
    struct gm_804D6900_t** temp_r29 = gm_804D6900;
    struct EventData* ev = &gmMainLib_804D3EE0->unk_530;
    u8 idx = gmMainLib_804D3EE0->unk_530.unk_535;
    struct gm_804D6900_x4_t* x4 = (*temp_r29)->x4;
    struct gm_804D6900_t** entry;
    u8* inner;
    void* cd;
    u8 ckind;
    u8 costume;
    lbl_8046B6A0_t* mi;
    s32 var_r0;

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
        inner = (u8*) (*entry)->x10;
        cd = ((void**) (inner + 0x10))[ev->x20];
        ckind = *(u8*) cd;
        costume = *((u8*) cd + 3);
        if ((s8) ev->x0 == (s8) ckind && (u8) ev->x1 == costume) {
            if (costume <= 2) {
                costume += 1;
            } else {
                costume = 0;
            }
        }
        gm_8016AC44((s8) ckind, (s8) costume);
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
    mi = gm_8016AE38();
    if (gmMainLib_804D3EE0->unk_530.xB_0) {
        var_r0 = 0;
    } else if (((*(u8*) &mi->x24C8 >> 1U) & 1) && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
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

    if (ev->x10 == 0) {
        Vec3* src = (Vec3*) gm_804D6900[ev->unk_535]->x4;
        pos.x = src->x;
        pos.y = src->y;
        pos.z = src->z;
        itEvYoshiEgg_Spawn(&pos);
        ev->x10 += 1;
    }
    if (ev->x18 != 0) {
        ev->xB_1 = 0;
        lbAudioAx_80028B90();
        gm_SetGameSpeed(1.0f);
        gm_8016B33C(6);
        gm_8016B364(0x148);
        gm_8016B378(0x28);
        gm_8016B328();
        HSD_GObjPLink_80390228(arg0);
        return;
    }
    rules = gm_8016AE38();
    if (ev->xB_0) {
        cond = 0;
    } else if (((((u8*) &rules->x24C8)[0] >> 1) & 1) && gm_8016AEEC() == 0 &&
               gm_8016AEFC() == 0x3B) {
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

/// #gm_801BDE94

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

    temp_r28 = gm_804D6900;
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
        arg0, gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535]->xC->x16);
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
    return gm_804D6900[arg0]->x8->x1_0;
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
    struct gm_804D6900_t** array = gm_804D6900;
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
    temp_r3 = gm_804D6900[gmMainLib_804D3EE0->unk_530.unk_535];
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

/* 49C178 */ static u8 gm_8049C178[16];

#pragma push
#pragma dont_inline on
void gm_801BEFA4(int ckind)
{
    gm_8049C178[0] = ckind;
}
#pragma pop

CharacterKind gm_801BEFB0(void)
{
    return gm_8049C178[0];
}

#pragma push
#pragma dont_inline on
void gm_801BEFC0(int arg0)
{
    gm_8049C178[1] = arg0;
}
#pragma pop

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
    if (g_debugLevel >= 3) {
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
    s32 spB8[27];
    s32 sp40[30];
    s32 count;
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    s32 pick;
    s32 dup;
    s32 added;
    s32 prev;
    u8 c;
    u8 cur_id;

    count = 0;
    c = 0;
    do {
        if (gm_80164840(c) != 0) {
            spB8[count] = c;
            count += 1;
        }
        c += 1;
    } while ((s32) c < 0x1A);
    spB8[count] = 0x1A;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            b = spB8[j];
            a = spB8[i];
            if ((s32) ((u8*) gmMainLib_804D3EE0)[a + 2] >
                (s32) ((u8*) gmMainLib_804D3EE0)[b + 2]) {
                spB8[i] = b;
                spB8[j] = a;
            }
        }
    }
    added = 0;
    do {
        do {
            pick = spB8[HSD_Randi(8)];
            dup = 0;
            for (j = 0; j < added; j++) {
                if (pick == gm_801BF648(j) ||
                    (pick == 0x12 && gm_801BF648(j) == 0x13) ||
                    (pick == 0x13 && gm_801BF648(j) == 0x12)) {
                    dup = 1;
                }
            }
        } while (dup != 0);
        gm_801BF634(added, (s8) pick);
        gm_801BF65C(added, 0);
        added += 1;
        ((u8*) gmMainLib_804D3EE0)[pick + 2] += 1;
    } while (added < 4);
    gm_801BF6C8(HSD_Randi(4));
    do {
        gm_801BF6E8(HSD_Randi(4));
        prev = gm_801BF6F8();
    } while (gm_801BF6D8() == prev);

    count = 0;
    c = 0;
    do {
        if (gm_80164430(gm_801641CC(c)) != 0) {
            sp40[count] = c;
            count += 1;
        }
        c += 1;
    } while ((s32) c < 0x1D);
    sp40[count] = 0x1D;
    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            b = sp40[j];
            a = sp40[i];
            if ((s32) ((u8*) gmMainLib_804D3EE0)[a + 0x1C] >
                (s32) ((u8*) gmMainLib_804D3EE0)[b + 0x1C]) {
                sp40[i] = b;
                sp40[j] = a;
            }
        }
    }
    do {
        pick = sp40[HSD_Randi(8)];
        cur_id = gm_801BF694();
    } while ((s32) gm_801641CC((u8) pick) == (s32) cur_id);
    gm_801BF684((s16) gm_801641CC((u8) pick));
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
    gm_801BEFA4(8);
    gm_801BEFC0(HSD_Randi(4));
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
