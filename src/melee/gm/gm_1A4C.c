#include "gm_1A4C.h"

#include "gm_unsplit.h"

#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <melee/gm/gmregtyfall.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbmthp.h>
#include <melee/mn/mnmain.h>
#include <melee/ty/toy.h>
#include <melee/un/un_2FC9.h>

extern Event gm_804D6724;

void fn_801A7A44(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void fn_801A7A68(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static HSD_GObj* gm_804D67B0;
static HSD_GObj* gm_804D67B4;

void fn_801A7A8C(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        HSD_GObjPLink_80390228(gm_804D67B0);
        HSD_GObjPLink_80390228(gm_804D67B4);
        mn_8022F0F0(3);
        gm_801A9630();
        HSD_GObjPLink_80390228(gobj);
    }
}

/// #gm_801A7B00

/// #fn_801A7FB4

void fn_801A80CC(HSD_GObj* gobj)
{
    HSD_LObjAnimAll(GET_LOBJ(gobj));
}

void fn_801A80F0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void gm_801A8114(HSD_JObj* arg0, int arg1)
{
    HSD_JObj* transJobj;
    float scale;

    if (arg0 == NULL) {
        transJobj = NULL;
    } else {
        transJobj = arg0->child;
    }

    HSD_JObjSetTranslateX(transJobj, un_803060BC(arg1, 0));
    HSD_JObjSetTranslateY(transJobj, un_803060BC(arg1, 1));
    HSD_JObjSetTranslateZ(transJobj, un_803060BC(arg1, 2));

    HSD_JObjSetRotationY(transJobj, 0.017453292f * un_803060BC(arg1, 5));

    scale = un_803060BC(arg1, 3) * (1.0F / un_803060BC(arg1, 4));
    if (transJobj == NULL) {
        __assert("gmregenddisp.c", 0x16BU, "transJobj");
    }

    HSD_JObjSetScaleX(transJobj, scale);
    HSD_JObjSetScaleY(transJobj, scale);
    HSD_JObjSetScaleZ(transJobj, scale);
}

void fn_801A851C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
    HSD_JObjSetTranslateZ(GET_JOBJ(gobj), 2.0F);
    if (gm_801A4BA8() == 0x174) {
        lbAudioAx_800237A8(0x7EF41, 0x7F, 0x40);
    }
}

/// #gm_801A85E4

/// #gm_801A8D54

/// #gm_801A9094

void fn_801A9498(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static s32 gm_804D67C4;

void fn_801A94BC(HSD_GObj* gobj)
{
    int i;
    int var_r31;
    HSD_CObj* cobj;
    PAD_STACK(0x10);

    cobj = GET_COBJ(gobj);
    gm_801A4310();
    var_r31 = 0;
    for (i = 0; i < 0x1A; i++) {
        if (un_803048C0(gm_801A659C(i)) ? true : false) {
            var_r31++;
        }
    }
    if (var_r31 <= 5) {
        if (cobj->aobj->curr_frame < 160.0f) {
            HSD_CObjAnim(cobj);
        } else if (--gm_804D67C4 == 0) {
            gm_801A4B60();
        }
        return;
    }

    gm_801A4310();
    var_r31 = 0;
    for (i = 0; i < 0x1A; i++) {
        if (un_803048C0(gm_801A659C(i)) ? true : false) {
            var_r31++;
        }
    }
    if (var_r31 <= 0xD) {
        if (cobj->aobj->curr_frame < 190.0f) {
            HSD_CObjAnim(cobj);
        } else if (--gm_804D67C4 == 0) {
            gm_801A4B60();
        }
    } else {
        if (cobj->aobj->curr_frame < cobj->aobj->end_frame) {
            HSD_CObjAnim(cobj);
        } else if (--gm_804D67C4 == 0) {
            gm_801A4B60();
        }
    }
}

/// #gm_801A9630

static u8 gm_804D67C8;
static u8 gm_804D67C9;

char* gm_803DB8B8[] = {
    // clang-format off
    "GmRegendSimpleCaptain.thp",
    "GmRegendSimpleDonkey.thp",
    "GmRegendSimpleFox.thp",
    "GmRegendSimpleGamewatch.thp",
    "GmRegendSimpleKirby.thp",
    "GmRegendSimpleKoopa.thp",
    "GmRegendSimpleLink.thp",
    "GmRegendSimpleLuigi.thp",
    "GmRegendSimpleMario.thp",
    "GmRegendSimpleMarth.thp",
    "GmRegendSimpleMewtwo.thp",
    "GmRegendSimpleNess.thp",
    "GmRegendSimplePeach.thp",
    "GmRegendSimplePikachu.thp",
    "GmRegendSimplePoponana.thp",
    "GmRegendSimplePurin.thp",
    "GmRegendSimpleSamus.thp",
    "GmRegendSimpleYoshi.thp",
    "GmRegendSimpleZeldaseak.thp",
    "GmRegendSimpleFalco.thp",
    "GmRegendSimpleClink.thp",
    "GmRegendSimpleDrmario.thp",
    "GmRegendSimpleRoy.thp",
    "GmRegendSimplePichu.thp",
    "GmRegendSimpleGanon.thp",
    // clang-format on
};

char* gm_803DBBF4[] = {
    // clang-format off
    "GmRegendAdventureCaptain.thp",
    "GmRegendAdventureDonkey.thp",
    "GmRegendAdventureFox.thp",
    "GmRegendAdventureGamewatch.thp",
    "GmRegendAdventureKirby.thp",
    "GmRegendAdventureKoopa.thp",
    "GmRegendAdventureLink.thp",
    "GmRegendAdventureLuigi.thp",
    "GmRegendAdventureMario.thp",
    "GmRegendAdventureMarth.thp",
    "GmRegendAdventureMewtwo.thp",
    "GmRegendAdventureNess.thp",
    "GmRegendAdventurePeach.thp",
    "GmRegendAdventurePikachu.thp",
    "GmRegendAdventurePoponana.thp",
    "GmRegendAdventurePurin.thp",
    "GmRegendAdventureSamus.thp",
    "GmRegendAdventureYoshi.thp",
    "GmRegendAdventureZeldaseak.thp",
    "GmRegendAdventureFalco.thp",
    "GmRegendAdventureClink.thp",
    "GmRegendAdventureDrmario.thp",
    "GmRegendAdventureRoy.thp",
    "GmRegendAdventurePichu.thp",
    "GmRegendAdventureGanon.thp",
    // clang-format on
};

char* gm_803DBF10[] = {
    // clang-format off
    "GmRegendAllstarCaptain.thp",
    "GmRegendAllstarDonkey.thp",
    "GmRegendAllstarFox.thp",
    "GmRegendAllstarGamewatch.thp",
    "GmRegendAllstarKirby.thp",
    "GmRegendAllstarKoopa.thp",
    "GmRegendAllstarLink.thp",
    "GmRegendAllstarLuigi.thp",
    "GmRegendAllstarMario.thp",
    "GmRegendAllstarMarth.thp",
    "GmRegendAllstarMewtwo.thp",
    "GmRegendAllstarNess.thp",
    "GmRegendAllstarPeach.thp",
    "GmRegendAllstarPikachu.thp",
    "GmRegendAllstarPoponana.thp",
    "GmRegendAllstarPurin.thp",
    "GmRegendAllstarSamus.thp",
    "GmRegendAllstarYoshi.thp",
    "GmRegendAllstarZeldaseak.thp",
    "GmRegendAllstarFalco.thp",
    "GmRegendAllstarClink.thp",
    "GmRegendAllstarDrmario.thp",
    "GmRegendAllstarRoy.thp",
    "GmRegendAllstarPichu.thp",
    "GmRegendAllstarGanon.thp",
    // clang-format on
};

void gm_801A9B30_OnEnter(UNK_T unused)
{
    struct {
        int x0;
        int x4;
        int x8;
        int xC;
        float x10;
        float x14;
        u8 pad[0x40 - 0x18];
        u32 x40;
    }* temp_r3_3;
    s32 temp_r31;
    HSD_GObj* gobj;
    HSD_GObj* temp_r29;
    const char* thpfile;
    s32 var_r3_3;
    int var_r3;

    gm_804D67C8 = 0x1E;
    gm_804D67C9 = 0;
    temp_r29 = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(temp_r29, 0x280, 0x1E0, 8);
    temp_r29->gxlink_prios = 0x800;
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0x10);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    lbBgFlash_800209F4();
    gobj = GObj_Create(0xE, 0xF, 0);
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, lbMthp8001F928, 0xB, 0);
    temp_r31 = gm_801BEFB0();
    var_r3 = gm_801A4310();
    if (var_r3 == MJ_DEBUG_GOVER) {
        var_r3 = gm_801BF050();
    }
    switch (var_r3) {
    case MJ_CLASSIC_GOVER:
        thpfile = gm_803DB8B8[temp_r31];
        break;
    case MJ_ADVENTURE_GOVER:
        thpfile = gm_803DBBF4[temp_r31];
        break;
    default:
        thpfile = gm_803DBF10[temp_r31];
        break;
    }
    lbMthp8001FAA0(thpfile, 0x230, 0x1A0);
    temp_r3_3 = lbMthp8001F890(gobj);
    temp_r3_3->x10 = 320.0F;
    temp_r3_3->x14 = 240.0F;
    temp_r3_3->x40 |= 2;
    switch (gm_801A4310()) {
    case MJ_CLASSIC_GOVER:
        var_r3_3 = gm_8017DFF4(1);
        break;
    case MJ_ADVENTURE_GOVER:
        var_r3_3 = gm_8017DFF4(0);
        break;
    default:
        var_r3_3 = gm_8017DFF4(2);
        break;
    }
    if (var_r3_3 == 4) {
        lbAudioAx_800237A8(0x9C45, 0x7F, 0x40);
    } else {
        lbAudioAx_800237A8(0x9C41, 0x7F, 0x40);
    }
}

void gm_801A9D0C_OnFrame(void)
{
    if (gm_804D67C8 != 0) {
        gm_804D67C8--;
    } else if (gm_804D67C9 != 0) {
        gm_804D67C9--;
        if (gm_804D67C9 == 0) {
            if (gm_801A4310() == MJ_DEBUG_GOVER) {
                gm_801A6630(6);
            } else {
                gm_801A6630(1);
            }
        }
    } else {
        if (gm_801A36A0(gm_801BF010()) & 0x1100) {
            lbBgFlash_8002063C(0x3C);
            gm_804D67C9 = 0x3C;
            lbAudioAx_80023694();
            lbAudioAx_80024030(1);
        }
    }
}
