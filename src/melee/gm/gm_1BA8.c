#include "gm_1BA8.h"

#include "gm_unsplit.h"

#include "gm_1B03.static.h"

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

/* 49E548 */ static struct gm_8049E548_t gm_8049E548;

extern u8 gm_804D68F8;
extern u8 gm_804D68F9;

static UNK_T gm_804D6900;

void gm_801BA8FC(void)
{
    lbArchive_LoadSymbols("GmEvent.dat", &gm_804D6900,
                          "sqEventInitDataLevelTbl", 0);
}

/// #gm_801BA938

#pragma push
#pragma dont_inline on
void gm_801BAA60(MinorScene* arg0)
{
    struct EventData* temp_r31 = &gmMainLib_804D3EE0->unk_530;
    CSSData* css = gm_801A427C(arg0);
    PAD_STACK(8);

    gm_801B06B0(css, 0xE, temp_r31->x2, 0, temp_r31->x3, temp_r31->x4, 0,
                temp_r31->x6);
    if (temp_r31->x44 == 1) {
        gm_801BA938(temp_r31, 1, 4, 1);
    }
}
#pragma pop

void gm_801BAAD0(MinorScene* arg0)
{
    CSSData* temp_r3;
    struct EventData* temp_r31;

    temp_r31 = &gmMainLib_804D3EE0->unk_530;
    temp_r3 = gm_801A4284(arg0);
    if (temp_r3->pending_scene_change == 2) {
        gm_801A42F8(MJ_MENU);
        return;
    }
    gm_801B0730(temp_r3, &temp_r31->x2, NULL, &temp_r31->x3, &temp_r31->x4,
                NULL);
    temp_r31->x8 = -1;
    temp_r31->x9 = -1;
    temp_r31->xA = -1;
}

/// #gm_801BAB40

/// #gm_801BAC9C

/// #gm_801BAD70

/// #gm_801BB758

/// #gm_801BBA60_OnInit

/// #gm_801BBB64

/// #gm_801BBEA8_OnLoad

void gm_801BBFE4_OnUnload(void) {}

void fn_801BBFE8(void)
{
    gm_801A4310();
    gm_801BC00C();
}

/// #gm_801BC00C

/// #gm_801BC488

/// #gm_801BC4F4

/// #gm_801BC670

/// #gm_801BC754

/// #gm_801BC9E8

/// #gm_801BCAF0

/// #gm_801BCC9C

void gm_801BCF20(HSD_GObj* gobj)
{
    gm_801BCC9C(gobj);
}

/// #gm_801BCF40

/// #gm_801BD028

/// #gm_801BD164

/// #gm_801BD30C

/// #gm_801BD44C

/// #gm_801BD46C

/// #gm_801BD658

/// #gm_801BD7FC

/// #gm_801BD93C

/// #gm_801BDAD4

/// #gm_801BDAF4

/// #gm_801BDC08

/// #gm_801BDD44

/// #gm_801BDE94

/// #gm_801BE37C

/// #gm_801BE39C

/// #gm_801BE618

/// #gm_801BE638

/// #gm_801BEA10

/// #gm_801BEA4C

/// #gm_801BEA88

/// #gm_801BEAF0

/// #gm_801BEB2C

void gm_801BEB68(s32 arg0)
{
    M2C_FIELD(gmMainLib_804D3EE0, s32*, 0x548) = arg0;
}

void gm_801BEB74(u8 arg0)
{
    gmMainLib_804D3EE0->unk_530.unk_535 = arg0;
}

u8 gm_801BEB80(void)
{
    return gmMainLib_804D3EE0->unk_530.unk_535;
}

/// #gm_801BEB8C

extern u8 gm_803DF918[];

u8 gm_801BEBA8(u8 arg0)
{
    return gm_803DF918[arg0];
}

/// #gm_801BEBC0

/// #gm_801BEBF8

/// #gm_801BEC54

void gm_801BEC80(MinorScene* arg)
{
    gm_801A42E8(1);
    gm_801A42D4();
}

void gm_801BECA8(MinorScene* arg)
{
    lb_8001C550();
    lb_8001D164(0);
}

void gm_801BECD0(MinorScene* arg)
{
    gm_80172898(4);
    if (gm_80173754(1, 0) == 0) {
        gm_801A42E8(1);
        gm_801A42D4();
    }
}

void gm_801BED14(MinorScene* arg)
{
    gm_801A42E8(1);
    gm_801A42D4();
}

/// #gm_801BED3C

/// #gm_801BEDA8

/// #gm_801BEE58

/// #gm_801BEE9C

void gm_801BEF84(MinorScene* arg)
{
    lbMthp_8001F800();
}

/* 49C178 */ static u8 gm_8049C178[16];

#pragma push
#pragma dont_inline on
void gm_801BEFA4(s8 arg0)
{
    gm_8049C178[0] = arg0;
}
#pragma pop

int gm_801BEFB0(void)
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

u8 gm_801BEFD0(void)
{
    return M2C_FIELD(&gm_8049C178, u8*, 1);
}

void gm_801BEFE0(s8 arg0)
{
    M2C_FIELD(&gm_8049C178, s8*, 0xA) = arg0;
}

u8 gm_801BEFF0(void)
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

u8 gm_801BF030(void)
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

void gm_801BF060(MinorScene* arg0)
{
    int* temp_r3 = gm_801A4284(arg0);
    if (g_debugLevel >= 3) {
        if (*temp_r3 & 0x100) {
            gm_801A42E8(0xE);
            gm_801A42D4();
        } else if (*temp_r3 & 0x1000) {
            gm_801A42E8(1);
            gm_801A42D4();
        } else if (*temp_r3 & 0x400) {
            gm_801A42E8(7);
            gm_801A42D4();
        } else if (*temp_r3 & 0x800) {
            gm_801A42E8(6);
            gm_801A42D4();
        }
    } else if (*temp_r3 & 0x1000) {
        gm_80173EEC();
        gm_80172898(0x100);
        if (gm_80173754(1, 0) == 0) {
            gm_801A42E8(1);
        }
        gm_801A42D4();
    }
}

/// #gm_801BF128

/// #gm_801BF3F8

void gm_801BF4DC(MinorScene* arg0)
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
    temp_r31->rules.x34 = 1.0f;
    temp_r31->rules.xE = (u16) gm_801BF694();
    gm_80167A14(temp_r31->players);

    for (i = 0; i < 4; i++) {
        int tmp = gm_801BF648(i);
        temp_r31->players[i].c_kind = tmp;
        temp_r31->players[i].color = gm_801BF670(i);
        temp_r31->players[i].slot_type = 1;
        temp_r31->players[i].cpu_level = 9;
        temp_r31->players[i].xE = 4;
        temp_r31->players[i].xC_b1 = false;
        if (temp_r31->rules.x0_0 == 1) {
            temp_r31->players[i].stocks = 0x63;
        }
    }
}

void gm_801BF634(s32 arg0, s8 arg1)
{
    gm_8049E548.pad_0[arg0] = arg1;
}

s8 gm_801BF648(s32 arg0)
{
    return gm_8049E548.pad_0[arg0];
}

void gm_801BF65C(s32 arg0, s8 arg1)
{
    M2C_FIELD(&gm_8049E548.pad_0[arg0], s8*, 4) = arg1;
}

u8 gm_801BF670(s32 arg0)
{
    return M2C_FIELD(&gm_8049E548.pad_0[arg0], u8*, 4);
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

u8 gm_801BF6D8(void)
{
    return gm_8049E548.unk_8;
}

void gm_801BF6E8(s8 arg0)
{
    M2C_FIELD(&gm_8049E548, s8*, 9) = arg0;
}

u8 gm_801BF6F8(void)
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

extern u8 un_804D6F3C[8];
extern u8 un_804D6FD8[8];

void gm_801BF728(MinorScene* arg)
{
    s32 temp_r31;
    s32 temp_r31_2;
    PAD_STACK(4);

    un_804D6F3C[1] = 1;
    un_804D6F3C[3] = 1;
    vi0102_8031D020(0xE, HSD_Randi(4));
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

void gm_801BF834(MinorScene* arg)
{
    gm_801A42E8(0);
    gm_801A42D4();
}

void gm_801BF85C(MinorScene* arg)
{
    PreloadCacheScene* temp_r31 = lbDvd_8001822C();
    PAD_STACK(4);
    lbDvd_800174BC();
    temp_r31->is_heap_persistent[1] = 0;
    lbDvd_80018254();
}

void gm_801BF898(MinorScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8B8(MinorScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8D8(MinorScene* arg)
{
    lbMthp_8001F800();
}

void gm_801BF8F8(MinorScene* arg0)
{
    int* val = gm_801A427C(arg0);
    *val = 1;
}

void gm_801BF920(MinorScene* arg0)
{
    gm_801A4284(arg0);
    gm_801A42F8(MJ_BOOT);
}
