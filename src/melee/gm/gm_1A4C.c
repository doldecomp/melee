#include "gm_1A4C.h"

#include "gm_1A4C.static.h"

#include "gm_unsplit.h"

#include <dolphin/dvd.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/vi.h>
#include <melee/cm/camera.h>
#include <melee/db/db.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ftdemo.h>
#include <melee/it/item.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/gmtitle.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbbgflash.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbmthp.h>
#include <melee/lb/lbsnap.h>
#include <melee/lb/types.h>
#include <melee/mn/mn_2295.h>
#include <melee/mn/mngallery.h>
#include <melee/mn/types.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/ty/toy.h>
#include <melee/un/un_2FC9.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/devcom.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/particle.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <sysdolphin/baselib/video.h>


/// #gm_801A6254

void gm_801A6308(MinorScene* arg0)
{
    gm_SetScenePendingMinor(0);
}

/// #gm_801A632C_OnEnter

/// #gm_801A637C_OnEnter

static u32 gm_804D6738;
static u8 gm_804D673C;

void gm_801A64A8_OnFrame(void)
{
    int temp_r31;
    bool var_r30;

    var_r30 = false;
    lbMthp_8001F578();
    temp_r31 = lbMthp_8001F5C4();
    if (lbMthp_8001F604() != 0) {
        gm_804D6738++;
    } else {
        gm_804D6738 = temp_r31;
    }
    if (gm_804D673C != 0) {
        gm_804D673C--;
        return;
    }
    if (gmMainLib_8046B0F0.xC != 0 && lbMthp_8001F604() == 0) {
        var_r30 = true;
    }
    if (gm_804D6738 >= 0x1A4 || (gm_801A36A0(gm_801BF010()) & 0x1000) || var_r30) {
        lbAudioAx_800236DC();
        lbAudioAx_80023694();
        if (var_r30) {
            gm_801A4B74();
            return;
        }
        gm_801A4B60();
    }
}

#pragma push
#pragma dont_inline on
bool gm_801A659C(int arg0)
{
    switch (gm_801A4310()) {
    case 21:
        return gm_80160474(arg0, 3);
    case 22:
        return gm_80160474(arg0, 4);
    case 26:
        return gm_80160474(arg0, gm_801BF050());
    default:
        return gm_80160474(arg0, 5);
    }
}
#pragma pop

void gm_801A6630(int arg0)
{
    u8* tmp = gm_801A4B9C();
    *tmp = arg0;
    gm_801A4B60();
}

/// #fn_801A6664

void fn_801A6844(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

Vec3 gm_803DB2C8 = { 0, 182, 0 };
Vec3 gm_803DB2D4 = { 0, 125, 0 };

void fn_801A6868(HSD_GObj* unused)
{
    Vec3 spC;
    Player_LoadPlayerCoords(0, &spC);
    if (spC.y >= gm_803DB2D4.y) {
        spC.y += (gm_803DB2D4.y - gm_803DB2C8.y) / 300.0F;
        Player_80032A04(0, &spC);
    }
}

static HSD_Archive* gm_804D6744;
static HSD_GObj* gm_804D674C;

static float gm_803DB2EC[] = {
    0.6f,
    0.5f,
    0.75f,
    0.7f,
    0.7f,
    0.4f,
    0.8f,
    0.75f,
    0.9f,
    0.7f,
    0.6f,
    0.6f,
    0.75f,
    0.7f,
    0.65f,
    0.7f,
    0.6f,
    0.7f,
    0.8f,
    0.7f,
    0.7f,
    0.7f,
    1.0f,
    0.7f,
    0.4f,
    0.5f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
};

void gm_801A68D8(void)
{
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;
    float temp_f31;
    float tmp;
    float mult;
    PAD_STACK(0x18);

    gm_801A4B90();
    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(0, NULL);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    ftDemo_ObjAllocInit();
    Player_80036E20(gm_801BEFB0(), gm_804D6744, 2);
    Player_80036CF0(0);
    Player_SetPlayerCharacter(0, gm_801BEFB0());
    Player_SetCostumeId(0, gm_801BEFD0());
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, 2);
    Player_SetFacingDirection(0, 1.0F);
    Player_80032768(0, &gm_803DB2C8);
    Player_80036F34(0, 7);

    temp_r3 = Player_GetEntity(0);
    gm_804D674C = temp_r3;
    lb_8000BA0C(GET_JOBJ(temp_r3), 0.6F);
    HSD_GObjProc_8038FD54(temp_r3, fn_801A6868, 4);

    temp_r3_2 = Player_GetEntityAtIndex(0, 1);
    if (temp_r3_2 != NULL) {
        lb_8000BA0C(GET_JOBJ(temp_r3_2), 0.6F);
    }
    temp_f31 = Player_80032BB0(0);
    tmp = gm_803DB2EC[gm_801BEFB0()];
    mult = 1.0F / temp_f31;
    Player_SetScale(0, mult * tmp);
}

static HSD_ImageDesc gm_804808F8[4];
static HSD_ImageDesc gm_80480964[4];
static HSD_ImageDesc gm_804809D0[2];
static int gm_804D6758;
static int gm_804D675C;
static int gm_804D6780;
static int gm_804D6784;

void fn_801A6A48(HSD_GObj* gobj, int arg1)
{
    if (HSD_CObjSetCurrent(gobj->hsd_obj) != 0) {
        HSD_SObjLib_803A54EC(gobj, arg1);
        gm_804D6780 = 1;
        HSD_ImageDescCopyFromEFB(&gm_804809D0[gm_804D6784], 0x3C, 0, 0, 1);
        HSD_CObjEndCurrent();
    }
}

void fn_801A6ACC(HSD_GObj* gobj)
{
    PAD_STACK(0x18);
    if (HSD_CObjSetCurrent(gobj->hsd_obj)) {
        Camera_800313E0(gobj, 1);
        gm_804D6758 = 1;
        HSD_ImageDescCopyFromEFB(&gm_804808F8[gm_804D675C * 2], 0x3C, 0, 0, 0);
        HSD_ImageDescCopyFromEFB(&gm_804808F8[gm_804D675C * 2] + 1, 0x3C, 0, 1, 1);
        HSD_CObjEndCurrent();
    }
}

extern HSD_GObj* gm_804D6754;
extern HSD_GObj* gm_804D6768;
extern HSD_GObj* gm_804D676C;
extern HSD_GObj* gm_804D6778;
extern HSD_GObj* gm_804D677C;

void fn_801A6B6C(HSD_GObj* gobj)
{
    HSD_AObj* aobj;
    HSD_CObj* cobj;

    cobj = gobj->hsd_obj;
    HSD_CObjAnim(cobj);
    aobj = cobj->aobj;
    if (aobj->curr_frame == aobj->end_frame) {
        Player_80031EBC(0);
        HSD_GObjPLink_80390228(gm_804D6768);
        HSD_GObjPLink_80390228(gm_804D6778);
        HSD_GObjPLink_80390228(gm_804D6754);
        HSD_GObjPLink_80390228(gm_804D676C);
        HSD_GObjPLink_80390228(gm_804D677C);
        mn_8022F0F0(3);
        HSD_Free(gm_80480964[0].image_ptr);
        HSD_Free(gm_80480964[1].image_ptr);
        HSD_Free(gm_80480964[2].image_ptr);
        HSD_Free(gm_80480964[3].image_ptr);
        gm_801A7B00();
        HSD_GObjPLink_80390228(gobj);
    }
}

void fn_801A6C30(HSD_GObj* gobj)
{
    HSD_CObjAnim(gobj->hsd_obj);
}

/// #gm_801A6C54

void fn_801A6D78(HSD_GObj* gobj)
{
    PAD_STACK(0x18);
    if (HSD_CObjSetCurrent(gobj->hsd_obj)) {
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

/// #gm_801A6DC0

/// #gm_801A6EE4

/// #gm_801A7070_OnEnter

static u8 gm_804D6740;

void gm_801A79D4_OnFrame(void)
{
    if (gm_804D6740 != 0) {
        gm_804D6740--;
    } else if (gm_801A36A0(gm_801BF010()) & 0x1000) {
        lbAudioAx_80023694();
        lbAudioAx_80024030(1);
        gm_801A4B60();
    }
}

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

/// #gm_801A8114

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

/// #gm_801A9B30_OnEnter

static u8 gm_804D67C8;
static u8 gm_804D67C9;

void gm_801A9D0C_OnFrame(void)
{
    if (gm_804D67C8 != 0) {
        gm_804D67C8--;
    } else if (gm_804D67C9 != 0) {
        gm_804D67C9--;
        if (gm_804D67C9 == 0) {
            if (gm_801A4310() == 0x1A) {
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

/// #gm_801A9DD0

/// #fn_801A9FCC

void fn_801AA0E8(void)
{
    hsd_80392528(fn_801A9FCC);
}

extern Event gm_804D6724;

static bool gm_804D67D0;
static HSD_GObj* gm_804D67D4;
static HSD_GObj* gm_804D67D8;
static bool gm_804D67DC;
static u8 gm_804D67E0;
static u8 gm_804D67E1;
static u8 gm_804D67E2;
static u32 gm_804D67E4;
static HSD_GObj* gm_804D67E8;
static u32 gm_804D67EC;
static int gm_804D67F0;
static HSD_GObj* gm_804D67F4;

static int gm_803DBFB4[] = {
    0x000004E2,
    0x00000002,
    0x0000018A,
    0x00000001,
    0x00010000,
    0x00000002,
};

void gm_801AA110_OnEnter(UNK_T arg0)
{
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;
    HSD_GObj* temp_r3_3;
    PAD_STACK(8);

    gm_804D67D0 = 0;
    gm_804D67D4 = 0;
    gm_804D67D8 = 0;
    gm_804D67EC = 0;
    gm_804D67E0 = 0;
    gm_804D67E1 = 0;
    gm_804D67DC = 0;
    gm_804D67E2 = 0;
    gmTitle_801A1AC0();
    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 4);
    lbAudioAx_80027168();
    gmMainLib_8015F588(0);
    gmTitle_801A1A3C();
    gmTitle_801A19AC();
    gmTitle_801A1944();

    temp_r3 = GObj_Create(0x13, 0x14, 0);
    gm_804D67F4 = temp_r3;
    gm_801A9DD0(temp_r3, 0x280, 0x1E0, 8, 0);
    temp_r3->gxlink_prios = 0x800;

    temp_r3_2 = GObj_Create(0x13, 0x14, 0);
    gm_801A9DD0(temp_r3_2, 0x280, 0x1E0, 0xB, 1);
    temp_r3_2->gxlink_prios = 0x20000;
    gmTitle_801A185C();

    temp_r3_3 = GObj_Create(0xE, 0xF, 0);
    gm_804D67E8 = temp_r3_3;
    GObj_SetupGXLink(temp_r3_3, lbMthp_8001F67C, 0xB, 0);
    lbMthp_8001F624(temp_r3_3, 0x280, 0x1E0);

    lbAudioAx_80027648();
    lbAudioAx_80023F28(0x3E);
    lbAudioAx_80024E50(1);
    lbMthp_8001F410("MvOpen.mth", gm_803DBFB4, 0, 0, 0);
    lbAudioAx_80024E50(0);
    gm_804D6724 = fn_801AA0E8;
}

void gm_801AA28C_OnFrame(void)
{
    HSD_GObj* temp_r3_2;
    int temp_r3;
    struct {
        u8 pad[0x10];
        float x10, x14;
    }* temp_r3_3;
    PAD_STACK(4);

    lbMthp_8001F578();
    temp_r3 = lbMthp_8001F5C4();
    if ((u32) gm_804D67EC > 0x1518) {
        gm_804D67EC += 1;
    } else {
        gm_804D67EC = (u32) temp_r3;
    }
    if (lbLang_IsSettingUS() != 0) {
        if (gm_804D67E0 == 0 && gm_804D67EC >= 0x13AA) {
            lbAudioAx_800237A8(0x4E21, 0x7F, 0x40);
            gm_804D67E0 = 1;
        }
    } else {
        if (gm_804D67E0 == 0 && gm_804D67EC >= 0x1374) {
            lbAudioAx_800237A8(0x4E22, 0x7F, 0x40);
            gm_804D67E0 = 1;
        }
        if (gm_804D67E1 == 0 && gm_804D67EC >= 0x13EC) {
            lbAudioAx_800237A8(0x4E23, 0x7F, 0x40);
            gm_804D67E1 = 1;
        }
    }
    if (((u8) gm_804D67E2 == 0) && ((u32) gm_804D67EC >= 0x1374U)) {
        gmMainLib_8015F500();
        gm_804D67E2 = 1;
    }
    if (gm_804D67D4 == NULL && gm_804D67EC >= 0x1C6 && gm_804D67EC < 0x202) {
        temp_r3_2 = GObj_Create(0xEU, 0xFU, 0U);
        HSD_GObjObject_80390A70(temp_r3_2, HSD_SObjLib_804D7960, NULL);
        GObj_SetupGXLink(temp_r3_2, HSD_SObjLib_803A49E0, 0x11U, 0U);
        temp_r3_3 = HSD_SObjLib_803A477C(temp_r3_2, gm_804D67F0, 0, 0, 0x80, 0);
        temp_r3_3->x10 = 82.0f;
        temp_r3_3->x14 = 290.0f;
        gm_804D67D4 = temp_r3_2;
    }
    if ((gm_804D67D4 != NULL) && ((u32) gm_804D67EC >= 0x202)) {
        HSD_GObjPLink_80390228(gm_804D67D4);
        gm_804D67D4 = NULL;
    }
    if ((gm_804D67D8 == NULL) && ((u32) gm_804D67EC >= 0x3B6) && (gm_804D67EC < 0x3CE)) {
        gm_804D67D8 = gmTitle_801A12C4();
    }
    if ((gm_804D67D8 != NULL) && (gm_804D67EC >= 0x3CE)) {
        HSD_GObjPLink_80390228(gm_804D67D8);
        gm_804D67D8 = NULL;
    }
    if (!gm_804D67D0 && (gm_804D67EC >= 0x140A)) {
        gmTitle_801A165C();
        gm_804D67D0 = true;
        gm_804D67E4 = (600.0f + (400.0f + gm_804D67EC));
    }
    if (lbMthp_8001F604() != 0 && !gm_804D67DC && gm_804D67D0) {
        gm_801BF3F8();
        gm_804D67DC = true;
    }
    if (gm_804D67D0 && (gm_804D67EC == gm_804D67E4)) {
        lbAudioAx_800236DC();
        gm_801A4B60();
    } else if (gmMainLib_8046B0F0.xC != 0 && lbMthp_8001F604() == 0) {
        gmMainLib_8015F500();
        lbAudioAx_800236DC();
        lbAudioAx_80023694();
        gm_801A4B74();
        gm_801A42E8(0);
        gm_801A42D4();
    } else if (gm_804D67EC > 0x157C) {
        if (gm_801A36A0(4) & 0x1000) {
            gmMainLib_8015F500();
            lbAudioAx_800236DC();
            lbAudioAx_80024030(1);
            gm_801A4B60();
            gm_80173EEC();
            gm_80172898(0x100);
            if (gm_80173754(1, 0) == 0) {
                gm_801A42E8(1);
            }
            gm_801A42D4();
        }
    } else {
        if (gm_801A36A0(4) & 0x1100) {
            gmMainLib_8015F500();
            lbAudioAx_800236DC();
            lbAudioAx_80023694();
            lbAudioAx_80024030(1);
            gm_801A4B60();
            gm_801A42E8(0);
            gm_801A42D4();
        }
    }
}

bool gm_801AA644(void)
{
    return gmMainLib_8015EDD4();
}

bool gm_801AA664(int arg0)
{
    gm_80164840(arg0);
}

bool gm_801AA688(void)
{
    PAD_STACK(4);
    return gm_80164840(9) || gm_80164840(0x17);
}

void gm_801AA6D8(s16 arg0)
{
    un_803048C0(arg0);
}

bool gm_801AA6FC(void)
{
    PAD_STACK(4);
    return un_803048C0(0x10B) || un_803048C0(0x10A) || un_803048C0(0x109);
}

bool gm_801AA774(void)
{
    PAD_STACK(4);
    return un_803048C0(0x107) || un_803048C0(0x108);
}

void gm_801AA7C4_OnFrame(void)
{
    if (gm_804D6814 >= 0x134D) {
        lbAudioAx_80028B90();
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

void fn_801AA7F8(HSD_GObj* gobj)
{
    HSD_CObj* cobj = gobj->hsd_obj;
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_CObjAnim(cobj);
        }
    }
}

static int gm_804D6800;

void fn_801AA854(HSD_GObj* gobj, int code)
{
    int i;
    HSD_CObj* cobj = gobj->hsd_obj;
    Mtx sp10;

    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(gm_804D6838->color.r, gm_804D6838->color.g, gm_804D6838->color.b, 0xFF);
        HSD_CObjEraseScreen(cobj, 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(NULL);
        PSMTXCopy(cobj->view_mtx, sp10);
        gobj = HSD_GObj_804D7824[9];
        while (gobj != NULL) {
            if (gobj != HSD_GObj_804D7824[9]) {
                __assert("gmstaffroll.c", 0x167, "gobj == HSD_GObjGXLinkHead[Gm_GObj_GXLink_PlyCursor]");
            }
            for (i = gm_804D6800 - 1; i >= 0; i--) {
                if (gm_804D67F8[gm_804D67FC[i].index].win[0] == 0) {
                    __assert("gmstaffroll.c", 0x169, "staffInfo[staffInfoSortBuf[i].index].win[0]");
                }
                if (gm_804D67F8[gm_804D67FC[i].index].win[1] == 0) {
                    __assert("gmstaffroll.c", 0x16A, "staffInfo[staffInfoSortBuf[i].index].win[1]");
                }
                PSMTXConcat(cobj->view_mtx, gm_804D67FC[i].x4->mtx, cobj->view_mtx);
                if (cobj->view_mtx[2][2] >= 0.0F) {
                    HSD_SisLib_803A84BC(gm_804D67F8[gm_804D67FC[i].index].win[0]->x54, 2);
                    HSD_SisLib_803A84BC(gm_804D67F8[gm_804D67FC[i].index].win[1]->x54, 2);
                }
                PSMTXCopy(sp10, cobj->view_mtx);
            }
            gobj = gobj->next_gx;
        }
        HSD_CObjEndCurrent();
    }
}

void fn_801AAA28(HSD_GObj* gobj, int code)
{
    int i;
    HSD_GObj_803910D8(gobj, code);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        for (i = 0; i < 6; i++) {
            if (gm_80480D58[i] != NULL) {
                HSD_SisLib_803A84BC(gm_80480D58[i]->x54, 2);
            }
        }
        if (gm_804D680C != NULL) {
            HSD_SisLib_803A84BC(gm_804D680C->x54, 2);
        }
    }
    HSD_CObjEndCurrent();
}

void fn_801AAABC(HSD_GObj* gobj)
{
    HSD_LObj* lobj = gobj->hsd_obj;
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_LObjAnimAll(lobj);
        }
    }
}

void fn_801AAB18(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int i;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_JObjAnimAll(jobj);
        }
    }
}

/// #fn_801AAB74

/// #fn_801AB200

void fn_801AC67C(HSD_GObj* gobj)
{
    int i;
    HSD_Fog* fog = gobj->hsd_obj;
    if (gm_804D6818 == 0) {
        for (i = 0; i < gm_804D681C; i++) {
            HSD_FogInterpretAnim(fog);
        }
    }
}

void gm_801AC6D8_OnEnter(UNK_T unused)
{
    HSD_JObj* jobj_arr[2];
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    int i;
    int const gx_link = 11;
    PAD_STACK(0x10);

    efLib_8005B4B8();
    efAsync_8006737C(0);
    gm_804D67F8 = HSD_MemAlloc(sizeof(struct gm_804D67F8_t));
    gm_804D67FC = HSD_MemAlloc(sizeof(struct gm_804D67FC_t));
    HSD_SisLib_803A62A0(0, "SdStRoll.dat", "SIS_StRollData");
    HSD_SisLib_803A611C(0, (void*) -1, 9, 13, 0, 18, 0, 19);
    lbAudioAx_80026F2C(28);
    lbAudioAx_8002702C(16, 0x4000000000000ULL);
    lbAudioAx_80027168();
    gm_804D683C = lbArchive_80016DBC(
        "GmStRoll.dat", &gm_804D6840, "ScGamRegStaffroll_scene_data",
        &gm_804D6844, "ScGamRegStaffrollNames_scene_modelset", 0);
    {
        gobj = GObj_Create(17, 19, 0);
        cobj = HSD_CObjLoadDesc(gm_804D6840->cameras[0].desc);
        gm_804D6830 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_801AA854, 5);
        gobj->gxlink_prios = 0x189;
        HSD_CObjAddAnim(cobj, gm_804D6840->cameras[0].anims[0]);
        HSD_CObjReqAnim(cobj, 0.0F);
        HSD_GObjProc_8038FD54(gobj, fn_801AA7F8, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(19, 20, 0);
        HSD_CObj* cobj = HSD_CObjLoadDesc(&gm_803DD0F0);
        gm_804D6834 = cobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(gobj, fn_801AAA28, 8);
        gobj->gxlink_prios = 1LL << gx_link;
    }
    {
        HSD_GObj* gobj = GObj_Create(gx_link, 3, 0);
        HSD_LObj* lobj = lb_80011AC4(gm_804D6840->lights);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
        GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
        HSD_LObjReqAnimAll(lobj, 0.0F);
        HSD_GObjProc_8038FD54(gobj, fn_801AAABC, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(0xA, 3, 0);
        HSD_Fog* fog = HSD_FogLoadDesc(gm_804D6840->fogs[0].desc);
        gm_804D6838 = fog;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
        GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 3, 0);
        HSD_Fog_8037DE7C(fog, gm_804D6840->fogs[0].anims[0]->aobjdesc);
        HSD_FogReqAnim(fog, 0.0F);
        HSD_GObjProc_8038FD54(gobj, fn_801AC67C, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(3, 5, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[1]->joint);
        gm_804D682C = jobj;
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 3, 0);
        gm_8016895C(jobj, gm_804D6840->models[1], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        {
            if (lbLang_IsSettingUS()) {
                lb_80011E24(jobj, jobj_arr, 103, 20, -1);
                M2C_FIELD(M2C_FIELD(jobj_arr[1]->u.dobj->mobj,
                                    void**, 8),
                          s32*, 0x58) =
                    M2C_FIELD(
                        M2C_FIELD(jobj_arr[1]->u.dobj->mobj,
                                  void**, 8),
                        s32*, 0x58);
            }
        }
        HSD_GObjProc_8038FD54(gobj, fn_801AAB18, 0);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[0]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, NULL, 9, 0);
        gm_8016895C(jobj, gm_804D6844[0], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        {
            /// @todo Length of #gm_804D6844 is 10
            for (i = 1; i < 10; i++) {
                HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6844[i]->joint);
                gm_8016895C(jobj, gm_804D6844[i], 0);
                HSD_JObjReqAnimAll(jobj, 0.0F);
                while (jobj->child != NULL) {
                    HSD_JObjReparent(jobj->child, jobj);
                }
            }
        }
        HSD_GObjProc_8038FD54(gobj, fn_801AAB74, 1);
    }
    {
        HSD_GObj* gobj = GObj_Create(14, 15, 0);
        HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6840->models[0]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, gx_link, 0);
        gm_8016895C(jobj, gm_804D6840->models[0], 0);
        lb_80011E24(jobj, jobj_arr, ARRAY_SIZE(jobj_arr), 20, -1);
        HSD_JObjReqAnimAll(jobj_arr[0], 0.0F);
        HSD_JObjReqAnimAll(jobj_arr[1], 0.0F);
        HSD_GObjProc_8038FD54(gobj, fn_801AB200, 13);
    }
    lbAudioAx_80027648();
    {
        u32 r = HSD_Randi(5);
        lbAudioAx_80023F28(lbAudioAx_8002305C(gm_801BEFB0(), !-r));
        lbBgFlash_800209F4();
        gm_804D6804.x0 = gm_804D6804.x4 = 0.0F;
        memzero(gm_804D67F8, sizeof(struct gm_804D67F8_t));
        gm_80480D58[0] = 0;
        gm_80480D58[1] = 0;
        gm_80480D58[2] = 0;
        gm_80480D58[3] = 0;
        gm_80480D58[4] = 0;
        gm_80480D58[5] = 0;
        gm_804D680C = NULL;
        gm_804D6810 = 0;
        gm_804D6814 = 0;
        gm_804D6818 = 0;
        gm_804D681C = 1;
        gm_804D6820 = 0;
        gm_804D6824 = gm_804D6828 = 0.0F;
        gm_804D6848 = 0;
        gm_804D684C = 0;
    }
}

void gm_801ACC90_OnLeave(UNK_T unused) {}

UNK_T gm_801ACC94(void)
{
    return &gm_803DD2C0;
}

extern HSD_GObj* gm_804D6850;

void gm_801ACCA0_OnEnter(UNK_T unused)
{
    HSD_GObj* gobj;
    PAD_STACK(8);

    gobj = GObj_Create(0x13, 0x14, 0);
    gm_801A9DD0(gobj, 0x280, 0x1E0, 8, 0);
    gobj->gxlink_prios = 1 << 0xB;

    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D6850 = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, lbMthp_8001F67C, 0xB, 0);
    lbMthp_8001F624(gobj, 0x280, 0x1E0);
    lbAudioAx_80023F28(0x24);
    lbAudioAx_80024E50(1);
    lbMthp_8001F410("MvHowto.mth", gm_803DD2C0, 0, 0, 0);
    lbAudioAx_80024E50(0);
    gm_804D6724 = fn_801AA0E8;
}

void gm_801ACD8C_OnFrame(void)
{
    bool var_r31 = false;
    PAD_STACK(4);

    lbMthp_8001F578();
    lbMthp_8001F5C4();
    if (gmMainLib_8046B0F0.xC != 0 && lbMthp_8001F604() == 0) {
        var_r31 = true;
    }
    if (lbMthp_8001F604() != 0 || (gm_801A36A0(4) & 0x1100) || var_r31) {
        lbAudioAx_800236DC();
        lbAudioAx_80023694();
        if (var_r31 != 0) {
            gm_801A4B74();
        } else {
            gm_801A4B60();
        }
        if (gm_801A36A0(4) & 0x1100) {
            lbAudioAx_80024030(1);
            gm_801A42E8(0);
            gm_801A42D4();
        } else if (gmMainLib_8015DB00() != 5) {
            gmMainLib_8015DB18();
            gm_SetScenePendingMinor(0);
        }
    }
}

static HSD_GObj* gm_804D6858;

void gm_801ACE94_OnEnter(void* unused)
{
    HSD_GObj* gobj;
    struct {
        u8 pad[0x10];
        float x10;
        float x14;
    }* temp_r3_2;

    gobj = GObj_Create(0x13, 0x14, 0);
    gm_801A9DD0(gobj, 0x280, 0x1E0, 8, 0);
    gobj->gxlink_prios = 0x800;

    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D6858 = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, lbMthp_8001F67C, 0xB, 0);
    temp_r3_2 = lbMthp_8001F624(gobj, 0x1C0, 0x150);
    temp_r3_2->x10 = 96.0f;
    temp_r3_2->x14 = 72.0f;
    lbAudioAx_80023F28(0x52);
    lbAudioAx_80024E50(1);
    lbMthp_8001F410("MvOmake15.mth", NULL, 0, 0, 0);
    lbAudioAx_80024E50(0);
    gm_804D6724 = fn_801AA0E8;
}

void gm_801ACF8C_OnFrame(void)
{
    bool var_r31 = false;
    PAD_STACK(4);

    lbMthp_8001F578();
    lbMthp_8001F5C4();
    if (gmMainLib_8046B0F0.xC != 0 && lbMthp_8001F604() == 0) {
        var_r31 = true;
    }
    if (lbMthp_8001F604() != 0 || (gm_801A36A0(4) & 0x1100) || var_r31) {
        lbAudioAx_800236DC();
        if (var_r31 != 0) {
            gm_801A4B74();
        } else {
            gm_801A4B60();
        }
        gmMainLib_8015DB0C(0);
        if ((gm_801A36A0(4) & 0x1100) || var_r31) {
            if (var_r31 == 0) {
                lbAudioAx_80024030(1);
            }
            gm_801A42E8(0);
            gm_801A42D4();
        }
    }
}
