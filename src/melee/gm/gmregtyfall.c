#include "gmregtyfall.h"

#include "gm/gmregtyfall.static.h"

#include "gm_unsplit.h"

#include "baselib/jobj.h"

#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <sysdolphin/baselib/tobj.h>
#include <melee/cm/camera.h>
#include <melee/ef/efasync.h>
#include <melee/ef/eflib.h>
#include <melee/ft/ft_0C31.h>
#include <melee/ft/ftdemo.h>
#include <melee/gr/ground.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/mn/mnmain.h>
#include <melee/mp/mpcoll.h>
#include <melee/pl/player.h>
#include <melee/sc/types.h>
#include <melee/ty/toy.h>
#include <melee/ty/tylist.h>

static Vec3 gm_803DB2C8 = { 0, 182, 0 };
static Vec3 gm_803DB2D4 = { 0, 125, 0 };
static Vec3 gm_803DB2E0 = { 0.5, -7, 0 };

#pragma push
#pragma dont_inline on
bool gm_801A659C(int arg0)
{
    switch (gm_801A4310()) {
    case MJ_CLASSIC_GOVER:
        return gm_80160474(arg0, 3);
    case MJ_ADVENTURE_GOVER:
        return gm_80160474(arg0, 4);
    case MJ_DEBUG_GOVER:
        return gm_80160474(arg0, gm_801BF050());
    default:
        return gm_80160474(arg0, 5);
    }
}

void gm_801A6630(int arg0)
{
    u8* tmp = gm_801A4B9C();
    *tmp = arg0;
    gm_801A4B60();
}
#pragma pop

static int gm_804D6750;
static HSD_GObj* gm_804D6754;
static int gm_804D6758;
static int gm_804D675C;
static struct {
    HSD_ImageDesc* x0;
    UNK_T x4;
} gm_804D6760;
static HSD_GObj* gm_804D677C;
static int gm_804D6780;
static int gm_804D6784;
static struct {
    HSD_ImageDesc* x0;
    UNK_T x4;
} gm_804D6788;
static int gm_804D6790;
static int gm_804D6794;

static HSD_ImageDesc gm_804808F8[2][2];
static u8 bss_pad_0[0xC];
static HSD_ImageDesc gm_80480964[2][2];
static u8 bss_pad_1[0xC];
static HSD_ImageDesc gm_804809D0[2];

static struct {
    u8 x0, x1, x2, x3;
} gm_804D4278 = { 0xAA, 0xAA, 0xFF, 0xFF };

void fn_801A6664(HSD_GObj* arg0)
{
    HSD_SObj_803A477C_t* temp_r3;
    HSD_SObj_803A477C_t* temp_r3_2;

    HSD_JObjAnimAll((HSD_JObj*) arg0->hsd_obj);
    if ((s32) gm_804D6758 != 0) {
        HSD_SObjLib_803A4740(gm_804D6754->hsd_obj);
        gm_804D6760.x0 = &gm_804808F8[gm_804D675C][0];
        gm_804D6760.x4 = NULL;
        temp_r3 = HSD_SObjLib_803A477C(gm_804D6754, (s32) &gm_804D6760, 0, 0,
                                       0x80, 0);
        temp_r3->x10 = 60.0f;
        temp_r3->x14 = 0.0f;
        gm_804D675C = gm_804D675C == 0;
        if (gm_804D6750 != 0) {
            if (gm_804D6750 > 0xFF) {
                gm_804D6750 -= 6;
            } else {
                gm_804D6750 -= 3;
            }
            if (gm_804D6750 < 0) {
                gm_804D6750 = 0;
            }
        }
        if (gm_804D6750 > 0xFF) {
            temp_r3->x3F = 0xFF;
        } else {
            temp_r3->x3F = gm_804D6750;
        }
    }
    if (gm_804D6780 != 0) {
        if (gm_804D6790 != 0) {
            gm_804D6790 -= 1;
            return;
        }
        gm_804D6790 = 7;
        HSD_SObjLib_803A4740(gm_804D677C->hsd_obj);
        gm_804D6788.x0 = &gm_804809D0[gm_804D6784];
        gm_804D6788.x4 = 0;
        temp_r3_2 = HSD_SObjLib_803A477C(gm_804D677C, (s32) &gm_804D6788, 0, 0,
                                         0x80, 0);
        temp_r3_2->x10 = 60.0f;
        temp_r3_2->x14 = 0.0f;
        temp_r3_2->x3C = gm_804D4278.x0;
        temp_r3_2->x3D = gm_804D4278.x1;
        temp_r3_2->x3E = gm_804D4278.x2;
        if (gm_804D6794 < 0xBE) {
            gm_804D6794 += 0xA;
            if (gm_804D6794 > 0xBE) {
                gm_804D6794 = 0xBE;
            }
        }
        temp_r3_2->x3F = gm_804D6794;
        gm_804D6784 = gm_804D6784 == 0;
    }
}

void fn_801A6844(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

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
    0.6f, 0.5f,  0.75f, 0.7f,  0.7f, 0.4f, 0.8f, 0.75f, 0.9f, 0.7f, 0.6f,
    0.6f, 0.75f, 0.7f,  0.65f, 0.7f, 0.6f, 0.7f, 0.8f,  0.7f, 0.7f, 0.7f,
    1.0f, 0.7f,  0.4f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
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
    Player_SetSlottype(0, Gm_PKind_Demo);
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

void fn_801A6A48(HSD_GObj* gobj, int arg1)
{
    if (HSD_CObjSetCurrent(gobj->hsd_obj) != 0) {
        HSD_SObjLib_803A54EC(gobj, arg1);
        gm_804D6780 = 1;
        HSD_ImageDescCopyFromEFB(&gm_804809D0[gm_804D6784], 0x3C, 0, 0, 1);
        HSD_CObjEndCurrent();
    }
}

void fn_801A6ACC(HSD_GObj* gobj, int unused)
{
    PAD_STACK(0x18);
    if (HSD_CObjSetCurrent(gobj->hsd_obj)) {
        Camera_800313E0(gobj, 1);
        gm_804D6758 = 1;
        HSD_ImageDescCopyFromEFB(&gm_804808F8[gm_804D675C][0], 0x3C, 0, 0, 0);
        HSD_ImageDescCopyFromEFB(&gm_804808F8[gm_804D675C][1], 0x3C, 0, 1, 1);
        HSD_CObjEndCurrent();
    }
}

extern HSD_GObj* gm_804D6768;
extern HSD_GObj* gm_804D676C;
extern int gm_804D6770;
extern int gm_804D6774;
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
        HSD_Free(gm_80480964[0][0].image_ptr);
        HSD_Free(gm_80480964[0][1].image_ptr);
        HSD_Free(gm_80480964[1][0].image_ptr);
        HSD_Free(gm_80480964[1][1].image_ptr);
        gm_801A7B00();
        HSD_GObjPLink_80390228(gobj);
    }
}

void fn_801A6C30(HSD_GObj* gobj)
{
    HSD_CObjAnim(gobj->hsd_obj);
}

static u8 gm_804D6740;
static SceneDesc* gm_804D6748;
static UNK_T gm_804D6798;
static HSD_Archive* gm_804D679C;
static SceneDesc* gm_804D67A0;
static SceneDesc* gm_804D67A4;
static SceneDesc* gm_804D67A8;
static SceneDesc* gm_804D67AC;

void gm_801A6C54(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    int i;

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) gm_804D6748->cameras[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, fn_801A6ACC, 8);
    gobj->gxlink_prios = 0x61;
    HSD_CObjAddAnim(cobj, gm_804D6748->cameras[0].anims[0]);
    HSD_CObjReqAnim(cobj, 0.0F);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(gobj, fn_801A6C30, 0);

    for (i = 0; i < 2; i++) {
        gm_804808F8[i][0].image_ptr = NULL;
        gm_804808F8[i][1].image_ptr = NULL;
        lb_800121FC(&gm_804808F8[i][0], 0x1EA, 0x1E0, 5, 0);
        lb_800121FC(&gm_804808F8[i][1], 0x1EA, 0x1E0, 0x16, 0);
    }
}

void fn_801A6D78(HSD_GObj* gobj, int unused)
{
    PAD_STACK(0x18);
    if (HSD_CObjSetCurrent(gobj->hsd_obj)) {
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void gm_801A6DC0(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    int i;

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) gm_804D6748->cameras[0].desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, fn_801A6D78, 0xB);
    gobj->gxlink_prios = 0x801;
    HSD_CObjAddAnim(cobj, gm_804D6748->cameras[0].anims[0]);
    HSD_CObjReqAnim(cobj, 0.0F);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(gobj, fn_801A6B6C, 0);

    for (i = 0; i < 2; i++) {
        gm_80480964[i][0].image_ptr = NULL;
        gm_80480964[i][1].image_ptr = NULL;
        lb_800121FC(&gm_80480964[i][0], 0x1EA, 0x1E0, 5, 0);
        lb_800121FC(&gm_80480964[i][1], 0x1EA, 0x1E0, 0x16, 0);
    }
}

static void data_reorder(HSD_JObj* jobj)
{
    HSD_JObjSetRotationX(jobj, 0);
}

void gm_801A6EE4(void)
{
    MajorSceneKind var_r29;

    PAD_STACK(4);

    gm_801A4B90();
    un_803124BC();
    un_803102D0();
    switch (gm_801A4310()) {
    case MJ_CLASSIC_GOVER:
        var_r29 = MJ_CLASSIC;
        break;
    case MJ_ADVENTURE_GOVER:
        var_r29 = MJ_ADVENTURE;
        break;
    case MJ_DEBUG_GOVER:
        var_r29 = gm_801BF050();
        break;
    default:
        var_r29 = MJ_ALLSTAR;
        break;
    }
    lbArchive_LoadSymbols(gm_801604DC(gm_801BEFB0(), var_r29), &gm_804D6798,
                          gm_80160564(gm_801BEFB0(), var_r29), 0);
    gm_804D6744 = lbArchive_LoadSymbols(
        "GmRegEnd", &gm_804D6748, "cut1CanimScene", &gm_804D67A8,
        "cut2CanimScene", &gm_804D67A4, "cut3CanimScene", &gm_804D67A0,
        "cut3BgScene", 0);
    lbArchive_LoadSymbols("GmRgStnd.dat", &gm_804D67AC, "standScene", 0);
    switch (var_r29) {
    case MJ_CLASSIC_GOVER:
    case MJ_CLASSIC:
        gm_804D679C = lbArchive_LoadSymbols("TyMcCmDs.dat", NULL);
        break;
    case MJ_ADVENTURE_GOVER:
    case MJ_ADVENTURE:
        gm_804D679C = lbArchive_LoadSymbols("TyMcR1Ds.dat", NULL);
        break;
    default:
        gm_804D679C = lbArchive_LoadSymbols("TyMcR2Ds.dat", NULL);
        break;
    }
}

// static inline void gm_801A7070_create_lobj(void)
// {

// }

void gm_801A7070_OnEnter(void* unused)
{
    s32 temp_r29;
    HSD_JObj* temp_r27_4;
    HSD_GObj* temp_r27;
    HSD_GObj* temp_r27_2;
    HSD_GObj* temp_r27_3;
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_2;
    HSD_GObj* temp_r3_3;
    HSD_JObj* var_r27_2;
    HSD_GObj* temp_r3_4;
    HSD_GObj* temp_r3_6;
    HSD_JObj* temp_r3_5;
    HSD_JObj* temp_r3_7;

    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_f31_4;
    f32 temp_f31_5;
    f32 temp_f31_6;
    f32 temp_f31_7;
    f32 temp_f31_8;

    HSD_JObj* temp_r3_8;
    int i;
    HSD_GObj* gobj;
    HSD_LObj* lobj;
    PAD_STACK(108);

    gm_804D6740 = 0x1E;
    gm_804D6750 = 0x320;
    gm_804D6754 = NULL;
    gm_804D6758 = 0;
    gm_804D675C = 0;
    gm_804D676C = NULL;
    gm_804D6770 = 0;
    gm_804D6774 = 0;
    gm_804D677C = NULL;
    gm_804D6780 = 0;
    gm_804D6784 = 0;
    gm_804D6794 = 0;
    gm_804D6790 = 7;

    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0x1C, 0x10000000000000);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    /// archive loads
    gm_801A6EE4();
    /// create lights
    temp_r27 = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(gm_804D6748->lights);
    HSD_GObjObject_80390A70(temp_r27, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(temp_r27, HSD_GObj_LObjCallback, 0, 0);
    /// create cameras
    gm_801A6C54();
    gm_801A6DC0();
    temp_r27_2 = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(temp_r27_2, 0x280, 0x1E0, 0xC);
    HSD_GObjGXLink_8039084C(temp_r27_2);
    GObj_SetupGXLinkMax(temp_r27_2, fn_801A6A48, 0xC);
    temp_r27_2->gxlink_prios = 0x40000;
    temp_r27_3 = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(temp_r27_3, 0x280, 0x1E0, 9);
    HSD_GObjGXLink_8039084C(temp_r27_3);
    GObj_SetupGXLinkMax(temp_r27_3, HSD_SObjLib_803A54EC, 9);
    temp_r27_3->gxlink_prios = 0x200;

    for (i = 0; i < 2; i++) {
        gm_804809D0[i].image_ptr = NULL;
        lb_800121FC(&gm_804809D0[i], 0x1EA, 0x1E0, 5, 0);
    }

    temp_r3 = GObj_Create(0xE, 0xD, 0);
    gm_804D677C = temp_r3;
    HSD_GObjObject_80390A70(temp_r3, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(temp_r3, HSD_SObjLib_803A49E0, 9, 0);
    temp_r3_2 = GObj_Create(0xE, 0x18, 0);
    gm_804D676C = temp_r3_2;
    HSD_GObjObject_80390A70(temp_r3_2, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(temp_r3_2, HSD_SObjLib_803A49E0, 0x12, 0);
    temp_r3_3 = GObj_Create(0xE, 0x18, 0);
    gm_804D6754 = temp_r3_3;
    HSD_GObjObject_80390A70(temp_r3_3, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(temp_r3_3, HSD_SObjLib_803A49E0, 0x12, 0);
    gm_801A68D8();
    gm_801A4B90();
    temp_r3_4 = GObj_Create(0xE, 0xF, 0);
    gm_804D6768 = temp_r3_4;
    temp_r3_5 = HSD_JObjLoadJoint(gm_804D6798);
    HSD_GObjObject_80390A70(temp_r3_4, HSD_GObj_804D7849, temp_r3_5);
    GObj_SetupGXLink(temp_r3_4, HSD_GObj_JObjCallback, 0xB, 0);
    temp_f31 = gm_803DB2EC[gm_801BEFB0()];
    HSD_JObjSetScaleX(temp_r3_5, temp_f31);
    HSD_JObjSetScaleY(temp_r3_5, temp_f31);
    HSD_JObjSetScaleZ(temp_r3_5, temp_f31);

    HSD_GObjProc_8038FD54(temp_r3_4, fn_801A6664, 0x17);
    temp_r27_4 = Player_80036EA0(0);
    lb_8000C1C0(HSD_JObjGetChild(HSD_JObjGetChild(
                    HSD_JObjGetChild(HSD_JObjGetChild(temp_r3_5)))),
                temp_r27_4);
    lb_8000C290(HSD_JObjGetChild(HSD_JObjGetChild(
                    HSD_JObjGetChild(HSD_JObjGetChild(temp_r3_5)))),
                temp_r27_4);
    gm_801A4B90();
    temp_r3_6 = GObj_Create(0xE, 0xF, 0);
    gm_804D6778 = temp_r3_6;
    temp_r3_7 = HSD_JObjLoadJoint(gm_804D67AC->models[0]->joint);
    HSD_GObjObject_80390A70(temp_r3_6, HSD_GObj_804D7849, temp_r3_7);
    GObj_SetupGXLink(temp_r3_6, HSD_GObj_JObjCallback, 0xB, 0);

    temp_r29 = gm_801A659C(gm_801BEFB0());
    var_r27_2 = HSD_JObjGetChild(temp_r3_7);
    temp_f31_2 = -un_803060BC(temp_r29, 0);
    fake_HSD_JObjSetTranslateX(var_r27_2, temp_f31_2);
    temp_f31_3 = -un_803060BC(temp_r29, 1);
    fake_HSD_JObjSetTranslateY(var_r27_2, temp_f31_3);
    temp_f31_4 = -un_803060BC(temp_r29, 2);
    fake_HSD_JObjSetTranslateZ(var_r27_2, temp_f31_4);

    temp_f31_5 = -(0.017453292f * un_803060BC(temp_r29, 5));
    fake_HSD_JObjSetRotationY(var_r27_2, temp_f31_5);
    temp_f31_6 = 1.0f / un_803060BC(temp_r29, 3);
    temp_f31_7 = un_803060BC(temp_r29, 4);
    temp_f31_7 = temp_f31_7 * temp_f31_6;
    fake_HSD_JObjSetScaleX(var_r27_2, temp_f31_7);
    fake_HSD_JObjSetScaleY(var_r27_2, temp_f31_7);
    fake_HSD_JObjSetScaleZ(var_r27_2, temp_f31_7);
    temp_f31_8 = gm_803DB2EC[gm_801BEFB0()];
    HSD_JObjSetScaleX(temp_r3_7, temp_f31_8);
    HSD_JObjSetScaleY(temp_r3_7, temp_f31_8);
    HSD_JObjSetScaleZ(temp_r3_7, temp_f31_8);

    HSD_GObjProc_8038FD54(temp_r3_6, fn_801A6844, 0x17);
    temp_r3_8 = gm_804D6768->hsd_obj;
    temp_r3_8 = HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(
        HSD_JObjGetChild(HSD_JObjGetChild(HSD_JObjGetChild(temp_r3_8))))));
    lb_8000C1C0(temp_r3_6->hsd_obj, temp_r3_8);
    lb_8000C290(temp_r3_6->hsd_obj, temp_r3_8);
    lbAudioAx_800237A8(0x7EF40, 0x7FU, 0x40U);
}

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
