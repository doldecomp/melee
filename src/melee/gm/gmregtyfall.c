#include "gmregtyfall.h"

#include "gm_unsplit.h"
#include "math.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftdemo.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbspdisplay.h"
#include "mn/mnmain.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tylist.h"

#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sobjlib.h>
#include <baselib/tobj.h>

struct ImageDesc_Array {
    HSD_ImageDesc x0[2][2];
    u8 x60[0xC];
};

/* 4D67AC */ SceneDesc* gm_804D67AC;
/* 4D67A8 */ SceneDesc* gm_804D67A8;
/* 4D67A4 */ SceneDesc* gm_804D67A4;
/* 4D67A0 */ SceneDesc* gm_804D67A0;
/* 4D679C */ HSD_Archive* gm_804D679C;
/* 4D6798 */ HSD_Joint* gm_804D6798;
/* 4D6794 */ int gm_804D6794;
/* 4D6790 */ int gm_804D6790;
/* 4D6788 */ struct HSD_SObjDesc gm_804D6788;
/* 4D6784 */ int gm_804D6784;
/* 4D6780 */ int gm_804D6780;
/* 4D677C */ HSD_GObj* gm_804D677C;
/* 4D6778 */ HSD_GObj* gm_804D6778;
/* 4D6774 */ int gm_804D6774;
/* 4D6770 */ int gm_804D6770;
/* 4D676C */ HSD_GObj* gm_804D676C;
/* 4D6768 */ HSD_GObj* gm_804D6768;
/* 4D6760 */ struct HSD_SObjDesc gm_804D6760;
/* 4D675C */ int gm_804D675C;
/* 4D6758 */ int gm_804D6758;
/* 4D6754 */ HSD_GObj* gm_804D6754;
/* 4D6750 */ int gm_804D6750;
/* 4D674C */ HSD_GObj* gm_804D674C;
/* 4D6748 */ SceneDesc* gm_804D6748;
/* 4D6744 */ HSD_Archive* gm_804D6744;
/* 4D6740 */ u8 gm_804D6740;
/* 4809D0 */ HSD_ImageDesc gm_804809D0[2];
/* 4808F8 */ static struct ImageDesc_Array gm_804808F8;
/* 480964 */ static struct ImageDesc_Array gm_80480964;

/* 3DB2C8 */ Vec3 gm_803DB2C8 = { 0.0f, 182.0f, 0.0f };
/* 3DB2D4 */ Vec3 gm_803DB2D4 = { 0.0f, 125, 0.0f };
/* 3DB2E0 */ Vec3 gm_803DB2E0 = { 0.5f, -7.0f, 0.0f };

static struct {
    u8 x0, x1, x2, x3;
} gm_804D4278 = { 0xAA, 0xAA, 0xFF, 0xFF };

static void order_sdata2(void)
{
    (void) 60.0f;
    (void) 0.0f;
    (void) deg_to_rad;
    (void) 1.0f;
}

#pragma push
#pragma dont_inline on
bool gm_801A659C(int arg0)
{
    switch (gm_801A4310()) {
    case GM_CLASSIC_GOVER:
        return gm_80160474(arg0, 3);
    case GM_ADVENTURE_GOVER:
        return gm_80160474(arg0, 4);
    case GM_DEBUG_GOVER:
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

void fn_801A6664(HSD_GObj* arg0)
{
    HSD_SObj* temp_r3;
    HSD_SObj* temp_r3_2;

    HSD_JObjAnimAll((HSD_JObj*) arg0->hsd_obj);
    if ((s32) gm_804D6758 != 0) {
        HSD_SObjLib_803A4740(gm_804D6754->hsd_obj);
        gm_804D6760.image = &gm_804808F8.x0[gm_804D675C][0];
        gm_804D6760.tlut = NULL;
        temp_r3 =
            HSD_SObjLib_803A477C(gm_804D6754, &gm_804D6760, 0, 0, 0x80, 0);
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
        gm_804D6788.image = &gm_804809D0[gm_804D6784];
        gm_804D6788.tlut = NULL;
        temp_r3_2 =
            HSD_SObjLib_803A477C(gm_804D677C, &gm_804D6788, 0, 0, 0x80, 0);
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
    efLib_Init();
    efAsync_LoadSync(0);
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
    HSD_GObj_SetupProc(temp_r3, fn_801A6868, 4);

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

static void order_data(void)
{
    (void) "!(jobj->flags & JOBJ_USE_QUATERNION)";
}

void fn_801A6ACC(HSD_GObj* gobj, int unused)
{
    PAD_STACK(0x18);
    if (HSD_CObjSetCurrent(gobj->hsd_obj)) {
        Camera_800313E0(gobj, 1);
        gm_804D6758 = 1;
        HSD_ImageDescCopyFromEFB(&gm_804808F8.x0[gm_804D675C][0], 0x3C, 0, 0,
                                 0);
        HSD_ImageDescCopyFromEFB(&gm_804808F8.x0[gm_804D675C][1], 0x3C, 0, 1,
                                 1);
        HSD_CObjEndCurrent();
    }
}

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
        HSD_Free(gm_80480964.x0[0][0].image_ptr);
        HSD_Free(gm_80480964.x0[0][1].image_ptr);
        HSD_Free(gm_80480964.x0[1][0].image_ptr);
        HSD_Free(gm_80480964.x0[1][1].image_ptr);
        gm_801A7B00();
        HSD_GObjPLink_80390228(gobj);
    }
}

void fn_801A6C30(HSD_GObj* gobj)
{
    HSD_CObjAnim(gobj->hsd_obj);
}

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
    HSD_GObj_SetupProc(gobj, fn_801A6C30, 0);

    for (i = 0; i < 2; i++) {
        gm_804808F8.x0[i][0].image_ptr = NULL;
        gm_804808F8.x0[i][1].image_ptr = NULL;
        lb_800121FC(&gm_804808F8.x0[i][0], 0x1EA, 0x1E0, 5, 0);
        lb_800121FC(&gm_804808F8.x0[i][1], 0x1EA, 0x1E0, 0x16, 0);
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
    HSD_GObj_SetupProc(gobj, fn_801A6B6C, 0);

    for (i = 0; i < 2; i++) {
        gm_80480964.x0[i][0].image_ptr = NULL;
        gm_80480964.x0[i][1].image_ptr = NULL;
        lb_800121FC(&gm_80480964.x0[i][0], 0x1EA, 0x1E0, 5, 0);
        lb_800121FC(&gm_80480964.x0[i][1], 0x1EA, 0x1E0, 0x16, 0);
    }
}

void gm_801A6EE4(void)
{
    GameModeKind var_r29;

    PAD_STACK(4);

    gm_801A4B90();
    Toy_803124BC();
    Toy_803102D0();
    switch (gm_801A4310()) {
    case GM_CLASSIC_GOVER:
        var_r29 = GM_CLASSIC;
        break;
    case GM_ADVENTURE_GOVER:
        var_r29 = GM_ADVENTURE;
        break;
    case GM_DEBUG_GOVER:
        var_r29 = gm_801BF050();
        break;
    default:
        var_r29 = GM_ALLSTAR;
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
    case GM_CLASSIC_GOVER:
    case GM_CLASSIC:
        gm_804D679C = lbArchive_LoadSymbols("TyMcCmDs.dat", NULL);
        break;
    case GM_ADVENTURE_GOVER:
    case GM_ADVENTURE:
        gm_804D679C = lbArchive_LoadSymbols("TyMcR1Ds.dat", NULL);
        break;
    default:
        gm_804D679C = lbArchive_LoadSymbols("TyMcR2Ds.dat", NULL);
        break;
    }
}

static inline void gm_801A7070_InitTextures(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        gm_804809D0[i].image_ptr = NULL;
        lb_800121FC(&gm_804809D0[i], 0x1EA, 0x1E0, 5, 0);
    }
}

static inline void gm_801A7070_InitTexturesAndCreateGObj(HSD_GObj** gobj)
{
    gm_801A7070_InitTextures();
    *gobj = GObj_Create(0xE, 0xD, 0);
}

static inline void gm_801A7070_SetPosition(int trophy, HSD_JObj* jobj,
                                            f32* translate_z)
{
    f32 translate_x;
    f32 translate_y;

    translate_x = -Toy_803060BC(trophy, 0);
    HSD_JObjSetTranslateXWithMtxDirty(jobj, translate_x);
    translate_y = -Toy_803060BC(trophy, 1);
    HSD_JObjSetTranslateYWithMtxDirty(jobj, translate_y);
    *translate_z = -Toy_803060BC(trophy, 2);
}

static inline void gm_801A7070_SetupGObj(HSD_JObj* jobj, HSD_GObj* gobj,
                                         s32* trophy)
{
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    *trophy = gm_801A659C(gm_801BEFB0());
}

void gm_801A7070_OnEnter(void* unused)
{
    s32 trophy;
    HSD_JObj* player_jobj;
    HSD_JObj* trophy_jobj;
    HSD_JObj* main_jobj;
    HSD_JObj* trophy_root;

    f32 main_scale;
    f32 translate_z;
    f32 rotation_y;
    f32 inverse_scale;
    f32 trophy_scale;
    f32 root_scale;

    HSD_JObj* constraint_target;
    HSD_GObj* gobj;
    HSD_LObj* lobj;
    PAD_STACK(100);

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
    gobj = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(gm_804D6748->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
    /// the rest of the gobj spawns creates/handles multiple cameras or deal
    /// with sobjs
    gm_801A6C54();
    gm_801A6DC0();
    gobj = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(gobj, 0x280, 0x1E0, 0xC);
    HSD_GObjGXLink_8039084C(gobj);
    GObj_SetupGXLinkMax(gobj, fn_801A6A48, 0xC);
    gobj->gxlink_prios = 0x40000;
    gobj = GObj_Create(0x13, 0x14, 0);
    HSD_SObjLib_803A55DC(gobj, 0x280, 0x1E0, 9);
    HSD_GObjGXLink_8039084C(gobj);
    GObj_SetupGXLinkMax(gobj, HSD_SObjLib_803A54EC, 9);
    gobj->gxlink_prios = 0x200;

    gm_801A7070_InitTexturesAndCreateGObj(&gobj);
    gm_804D677C = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, HSD_SObjLib_803A49E0, 9, 0);
    gobj = GObj_Create(0xE, 0x18, 0);
    gm_804D676C = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, HSD_SObjLib_803A49E0, 0x12, 0);
    gobj = GObj_Create(0xE, 0x18, 0);
    gm_804D6754 = gobj;
    HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, NULL);
    GObj_SetupGXLink(gobj, HSD_SObjLib_803A49E0, 0x12, 0);
    gm_801A68D8();
    gm_801A4B90();

    // create jobj
    gm_804D6768 = gobj = GObj_Create(0xE, 0xF, 0);
    main_jobj = HSD_JObjLoadJoint(gm_804D6798);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, main_jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    main_scale = gm_803DB2EC[gm_801BEFB0()];
    HSD_JObjSetScaleX(main_jobj, main_scale);
    HSD_JObjSetScaleY(main_jobj, main_scale);
    HSD_JObjSetScaleZ(main_jobj, main_scale);

    HSD_GObj_SetupProc(gobj, fn_801A6664, 0x17);
    player_jobj = Player_80036EA0(0);
    lb_8000C1C0(HSD_JObjGetChild(HSD_JObjGetChild(
                    HSD_JObjGetChild(HSD_JObjGetChild(main_jobj)))),
                player_jobj);
    lb_8000C290(HSD_JObjGetChild(HSD_JObjGetChild(
                    HSD_JObjGetChild(HSD_JObjGetChild(main_jobj)))),
                player_jobj);
    gm_801A4B90();
    gobj = GObj_Create(0xE, 0xF, 0);
    gm_804D6778 = gobj;
    trophy_root = HSD_JObjLoadJoint(gm_804D67AC->models[0]->joint);
    gm_801A7070_SetupGObj(trophy_root, gobj, &trophy);

    trophy_jobj = HSD_JObjGetChild(trophy_root);
    gm_801A7070_SetPosition(trophy, trophy_jobj, &translate_z);
    HSD_JObjSetTranslateZWithMtxDirty(trophy_jobj, translate_z);

    rotation_y = -(0.017453292f * Toy_803060BC(trophy, 5));
    HSD_JObjSetRotationYWithMtxDirty(trophy_jobj, rotation_y);
    inverse_scale = 1.0f / Toy_803060BC(trophy, 3);
    trophy_scale = Toy_803060BC(trophy, 4);
    trophy_scale = trophy_scale * inverse_scale;
    HSD_JObjSetScaleXWithMtxDirty(trophy_jobj, trophy_scale);
    HSD_JObjSetScaleYWithMtxDirty(trophy_jobj, trophy_scale);
    HSD_JObjSetScaleZWithMtxDirty(trophy_jobj, trophy_scale);
    root_scale = gm_803DB2EC[gm_801BEFB0()];
    HSD_JObjSetScaleX(trophy_root, root_scale);
    HSD_JObjSetScaleY(trophy_root, root_scale);
    HSD_JObjSetScaleZ(trophy_root, root_scale);

    HSD_GObj_SetupProc(gobj, fn_801A6844, 0x17);
    constraint_target = gm_804D6768->hsd_obj;
    constraint_target = HSD_JObjGetNext(HSD_JObjGetChild(HSD_JObjGetChild(
        HSD_JObjGetChild(HSD_JObjGetChild(HSD_JObjGetChild(constraint_target))))));
    lb_8000C1C0(gobj->hsd_obj, constraint_target);
    lb_8000C290(gobj->hsd_obj, constraint_target);
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
