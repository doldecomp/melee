#include "gr/gricemt.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/gobjgxlink.h"
#include "baselib/gobjproc.h"
#include "baselib/random.h"
#include "cm/camera.h"
#include "ef/efsync.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grlib.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "mp/mplib.h"

#include <m2c_macros.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

/* 1F8C64 */ static void fn_801F8C64(Item_GObj* gobj, Ground* u1, Vec3* u2,
                                     HSD_GObj* u3, f32 u4);
/* 1F91EC */ static void FUN_801f91ec(HSD_GObj* param_1, s16* param_2,
                                      int param_3, int param_4, int param_5,
                                      int param_6, int param_7,
                                      mpLib_Callback param_8);

// StageData grIm_803E8974 = {
//     45,
//     grTFc_803E8918,
//     "/GrTFc.dat",
//     grTFalco_802207F4,
//     grTFalco_802207F0,
//     grTfalco_UnkStage0_OnLoad,
//     grTfalco_UnkStage0_OnStart,
//     grTFalco_80220894,
//     grTFalco_80220ACC,
//     grTFalco_80220B78,
//     1,
// };

/*struct {
    Vec3 unk0;
    Vec3 unkC;
    Vec3 unk18;
    Vec3 unk24;
    Vec3 unk40;
} grIm_803B8220;*/
Vec3 grIm_803B8220[] = { { 0.0, 0.0, 0.0 },
                         { -8.0, 15.0, 0.0 },
                         { 8.0, 15.0, 0.0 },
                         { -24.0, 15.0, 0.0 },
                         { 24.0, 15.0, 0.0 } };

HSD_GObj* grIm_804D69E8;
HSD_GObj* grIm_804D69EC;
HSD_GObj* grIm_804D69F0;
IceMountainParams* grIm_804D69F4;

/// @brief Ice Mountain row data - 12 bytes each.
typedef struct IceMtRowData {
    s32 id; // Row identifier, compared with xAC[i] values
    u32 x4;
    u32 x8;
} IceMtRowData;

IceMtRowData grIm_803E4068[6];

S16Vec3 grIm_803E40B0[] = {
    { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }, { 2, 0, 0 }
};

StageCallbacks grIm_803E4718[] = { { grIceMt_801F72D4, grIceMt_801F75DC,
                                     grIceMt_801F75E4, grIceMt_801F75E4, 0 },
                                   { grIceMt_801F7D94, grIceMt_801F7EE0,
                                     grIceMt_801F7EE8, grIceMt_801F7F1C, 0 },
                                   { grIceMt_801F7F70, grIceMt_801F8154,
                                     grIceMt_801F815C, grIceMt_801F81B4, 0 },
                                   { grIceMt_801F8208, grIceMt_801F835C,
                                     grIceMt_801F8364, grIceMt_801F8398, 0 },
                                   { grIceMt_801F83EC, grIceMt_801F85BC,
                                     grIceMt_801F85C4, grIceMt_801F8608, 0 },
                                   { grIceMt_801F865C, grIceMt_801F87C0,
                                     grIceMt_801F87C8, grIceMt_801F87FC, 0 },
                                   { grIceMt_801F8850, grIceMt_801F89A4,
                                     grIceMt_801F89AC, grIceMt_801F89E0, 0 },
                                   { 0, 0, 0, 0, 0 },
                                   { grIceMt_801F8A34, grIceMt_801F8B08,
                                     grIceMt_801F8B10, grIceMt_801F8C60, 0 },
                                   { grIceMt_801F75FC, grIceMt_801F7720,
                                     grIceMt_801F7728, grIceMt_801F77AC, 0 },
                                   { grIceMt_801F785C, grIceMt_801F796C,
                                     grIceMt_801F7A2C, grIceMt_801F7D90, 0 } };

StageData grIm_803E4800 = {
    0x16,
    grIm_803E4718,
    "/GrIm.dat",
    grIceMt_801F686C,
    grIceMt_801F6868,
    grIceMt_801F7080,
    grIceMt_801F71DC,
    grIceMt_801F71E0,
    grIceMt_801FA8F8,
    grIceMt_801FA900,
    1,
    grIm_803E40B0,
    3,
};

const float grIm_804DB574 = 0.0F;
const float grIm_804DB5B0 = -1.0F;
const float grIm_804DB5B4 = 1.0F;
const float grIm_804DB5B8 = 6.0F;

void grIceMt_801F6868(bool id) {}

#define ICEMT_FIELD_MAX 6

/// #grIceMt_801F686C
void grIceMt_801F686C(void)
{
    s32 field30;
    s32 field29;
    s32 field28;
    u32 row_idx;
    s16* xAC;
    s32 id;
    f32 y_pos;
    f32 y_pos2;
    f32 y_pos3;
    f32 y_pos4;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    grIm_804D69F4 = Ground_801C49F8();
    stage_info.unk8C.b4 = true;
    stage_info.unk8C.b5 = false;
    grIceMt_801F71E8(0);
    grIceMt_801F71E8(8);
    Ground_801C3260(1);
    Ground_801C3260(2);
    Ground_801C3260(3);
    Ground_801C3260(4);
    Ground_801C3260(5);
    Ground_801C3260(6);

    if (Stage_80225194() == 76) {
        // First loop: find row where neither xAC[0] nor xAC[1] matches
        for (row_idx = 0; row_idx < ICEMT_FIELD_MAX; row_idx++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[row_idx].id;
            if (xAC[0] == id) {
                continue;
            }
            if (xAC[1] == id) {
                continue;
            }
            field30 = grIm_803E4068[row_idx].id;
            break;
        }
        if (row_idx >= ICEMT_FIELD_MAX) {
            __assert("gricemt.c", 0x258, "<ICEMT_FIELD_MAX>");
        }

        // Second loop: find row where xAC[0], xAC[1], and field30 don't match
        for (row_idx = 0; row_idx < ICEMT_FIELD_MAX; row_idx++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[row_idx].id;
            if (xAC[0] == id) {
                continue;
            }
            if (xAC[1] == id) {
                continue;
            }
            if (field30 == id) {
                continue;
            }
            field29 = grIm_803E4068[row_idx].id;
            break;
        }
        if (row_idx >= ICEMT_FIELD_MAX) {
            __assert("gricemt.c", 0x261, "<ICEMT_FIELD_MAX>");
        }

        // Third loop: find row where xAC[0], xAC[1], field30, and field29
        // don't match
        for (row_idx = 0; row_idx < ICEMT_FIELD_MAX; row_idx++) {
            xAC = grIm_804D69F4->xAC;
            id = grIm_803E4068[row_idx].id;
            if (xAC[0] == id) {
                continue;
            }
            if (xAC[1] == id) {
                continue;
            }
            if (field30 == id) {
                continue;
            }
            if (field29 == id) {
                continue;
            }
            field28 = grIm_803E4068[row_idx].id;
            break;
        }
        if (row_idx >= ICEMT_FIELD_MAX) {
            __assert("gricemt.c", 0x26B, "<ICEMT_FIELD_MAX>");
        }

        // Calculate Y positions for the 3 topi platforms
        y_pos = Ground_801C0498();
        xAC = grIm_804D69F4->xAC;
        y_pos = grIm_804DB570 * y_pos;
        y_pos = y_pos + grIceMt_801F993C(grIm_803E4068[xAC[0]].id,
                                         grIm_803E4068[xAC[1]].id);
        y_pos2 = y_pos + grIceMt_801F993C(grIm_803E4068[xAC[1]].id, field30);
        y_pos3 = y_pos2 + grIceMt_801F993C(field30, field29);
        y_pos4 = y_pos3 + grIceMt_801F993C(field29, field28);

        // Set up first topi (grIm_804D69E8)
        gobj = grIceMt_801F71E8(grIm_803E4068[xAC[2]].id);
        if (gobj == NULL) {
            __assert("gricemt.c", 0x27C, "bg_gobj");
        }
        jobj = gobj->hsd_obj;
        if (jobj == NULL) {
            __assert("gricemt.c", 0x27D, "jobj");
        }
        HSD_JObjSetTranslateY(jobj, y_pos2);
        grIm_804D69E8 = gobj;

        // Set up second topi (grIm_804D69EC)
        gobj = grIceMt_801F71E8(grIm_803E4068[xAC[3]].id);
        if (gobj == NULL) {
            __assert("gricemt.c", 0x281, "bg_gobj");
        }
        jobj = gobj->hsd_obj;
        if (jobj == NULL) {
            __assert("gricemt.c", 0x282, "jobj");
        }
        HSD_JObjSetTranslateY(jobj, y_pos3);
        grIm_804D69EC = gobj;

        // Set up third topi (grIm_804D69F0)
        gobj = grIceMt_801F71E8(grIm_803E4068[xAC[4]].id);
        if (gobj == NULL) {
            __assert("gricemt.c", 0x286, "bg_gobj");
        }
        jobj = gobj->hsd_obj;
        if (jobj == NULL) {
            __assert("gricemt.c", 0x287, "jobj");
        }
        HSD_JObjSetTranslateY(jobj, y_pos4);
        grIm_804D69F0 = gobj;

        grIceMt_801F71E8(0xA);
    } else {
        grIceMt_801F71E8(9);
        grIm_804D69E8 = NULL;
        grIm_804D69EC = NULL;
        grIm_804D69F0 = NULL;
    }
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grIceMt_801F7080(void)
{
    // Ground_801C2BA4(5);
    int iVar1;
    HSD_GObj* gobj;

    Vec3 x;
    if (grIm_804D69E8) {
        Ground_801C4A08(grIm_804D69E8);
    }
    if (grIm_804D69EC) {
        Ground_801C4A08(grIm_804D69EC);
    }
    if (grIm_804D69F0) {
        Ground_801C4A08(grIm_804D69F0);
    }
    gobj = Ground_801C2BA4(1);
    if (gobj) {
        Ground_801C2FE0(gobj);
    }
    gobj = Ground_801C2BA4(2);
    if (gobj) {
        Ground_801C2FE0(gobj);
    }
    gobj = Ground_801C2BA4(3);
    if (gobj) {
        Ground_801C2FE0(gobj);
    }
    gobj = Ground_801C2BA4(4);
    if (gobj) {
        Ground_801C2FE0(gobj);
    }
    gobj = Ground_801C2BA4(5);
    if (gobj) {
        Ground_801C2FE0(gobj);
    }
    gobj = Ground_801C2BA4(6);
    if (gobj) {
        Ground_801C2FE0(gobj);
    }
    if (Stage_80225194() == 76) {
        grZakoGenerator_801CAE04(&grIm_804D69F4->xBC);
        if (grIm_804D69F4->xB8 != 0) {
            iVar1 = HSD_Randi(grIm_804D69F4->xB8);
        } else {
            iVar1 = 0;
        }
        if (iVar1 == 0) {
            grZakoGenerator_801CAEB0(Ground_801C5940(), Ground_801C5840());
        }

        grZakoGenerator_801CADE0();
    } else {
        grZakoGenerator_801CAE04(0);
    }
    x = grIm_803B8220[0];
    grLib_801C96F8(0x7534, 0x1E, &x);
    ////grLib_801C96F8(30000,30,{0,0,0});
}

void grIceMt_801F71DC(void) {}

bool grIceMt_801F71E0(void)
{
    return false;
}

/// #grIceMt_801F71E8
HSD_GObj* grIceMt_801F71E8(int gobj_id)
{
    HSD_GObj* gobj;
    gobj = Ground_801C14D0(gobj_id);
    // StageCallbacks* callbacks = &grIm_803E4718[gobj_id];
    if (gobj != NULL) {
        Ground* gp = GET_GROUND(gobj);
        gp->x8_callback = 0;
        gp->xC_callback = 0;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        // if(grIm_803E4718[gobj_id]) {
        //	int bruh = 4;
        // }
        if (grIm_803E4718->callback3 != NULL) {
            gp->x1C_callback = grIm_803E4718->callback3;
        }

        if (grIm_803E4718->callback0 != NULL) {
            grIm_803E4718->callback0(gobj);
        }

        if (grIm_803E4718->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, grIm_803E4718->callback2, 4);
        }
        // HSD_GObjProc_8038FD54(gobj,gobj_id,4);
        // if(callbacks) {
        //	callbacks->callback0(gobj);
        // }
    } else {
        OSReport("s:%d: couldn t get gobj(id=%d)\n", "gricemt.c", 0x35C,
                 gobj_id);
    }

    return gobj;
}

/// #grIceMt_801F72D4
// extern char grIm_803B8220;
extern char grIm_804D4718;
extern char grIm_804D4720;

void grIceMt_801F72D4(Ground_GObj* arg0)
{
    Vec3 sp3C;
    u32 sp38;
    u32 sp34;
    u32 sp30;
    u32 sp2C;
    u32 sp28;
    u32 sp24;
    u32 sp20;
    u32 sp1C;
    u32 sp18;
    u32 sp14;
    u32 sp10;
    HSD_JObj* jobj;
    Ground* gp = GET_GROUND(arg0);
    grAnime_801C8138(arg0, gp->map_id, 0);
    jobj = Ground_801C3FA4(arg0, 0x12);
    if (jobj != 0) {
        sp3C = grIm_803B8220[1];
        HSD_JObjSetTranslate(jobj, &sp3C);
    }
    jobj = Ground_801C3FA4(arg0, 0x13);
    if (jobj != 0) {
        sp3C = grIm_803B8220[2];
        HSD_JObjSetTranslate(jobj, &sp3C);
    }
    jobj = Ground_801C3FA4(arg0, 0x14);
    if (jobj != 0) {
        sp3C = grIm_803B8220[3];
        HSD_JObjSetTranslate(jobj, &sp3C);
    }
    jobj = Ground_801C3FA4(arg0, 0x15);
    if (jobj != 0) {
        sp3C = grIm_803B8220[4];
        HSD_JObjSetTranslate(jobj, &sp3C);
    }
    Ground_801C39C0();
    Ground_801C3BB4();
}

bool grIceMt_801F75DC(Ground_GObj* arg0)
{
    return false;
}

void grIceMt_801F75E4(Ground_GObj* arg0) {}

void grIceMt_801F75E8(Ground_GObj* arg0) {}

void fn_801F75EC(HSD_GObj* arg0)
{
    GET_GROUND(arg0)->gv.icemt.xD8 = 0;
}

/// #grIceMt_801F75FC
/// @note This function treats xF4 area as s16 indices during initialization.
/// The same memory is later interpreted as pointers by other functions.
void grIceMt_801F75FC(Ground_GObj* arg0)
{
    u32 iVar1;
    s16 val;
    Ground* gp = GET_GROUND(arg0);
    memzero(&gp->gv.icemt.xDC, 0x18);
    memzero(&gp->gv.icemt.xF4, 0x14);
    do {
        iVar1 = HSD_Randi(6);
        val = gp->gv.icemt.xF4[iVar1];
    } while (val != 0);
    gp->gv.icemt.xF4[iVar1] = *(s16*) grIm_804D69F4;
    gp->gv.icemt.xC4 = (s16) grIm_803E4068[iVar1].id;
    do {
        iVar1 = HSD_Randi(6);
        val = gp->gv.icemt.xF4[iVar1];
    } while (val != 0);
    gp->gv.icemt.xF4[iVar1] = *(s16*) grIm_804D69F4;
    gp->gv.icemt.xC6 = (s16) grIm_803E4068[iVar1].id;
    grIceMt_801FA0BC((int) &gp->gv.icemt.xC4);
    gp->gv.icemt.xDA = 0;
    gp->gv.icemt.xC8 = 0;
    gp->gv.icemt.xCE = 0;
    gp->gv.icemt.xCA = 0;
    gp->gv.icemt.xCC = 0;
    gp->gv.icemt.xD0 = -1;
    gp->gv.icemt.xD4 = 0;
    gp->gv.icemt.xD8 = 1;
    Ground_801C10B8(arg0, fn_801F75EC);
    return;
}

bool grIceMt_801F7720(Ground_GObj* arg0)
{
    return false;
}

/// #grIceMt_801F7728
void grIceMt_801F7728(Ground_GObj* arg0)
{
    float y;
    Ground* gp = GET_GROUND(arg0);
    if (gp->gv.icemt.xD8 == 0) {
        grIceMt_801FA364(&gp->gv.corneria.xC8, &y, fn_801F8E58, arg0);
        grIceMt_801F9ACC(grIceMt_801F96E0(-y));
        grIceMt_801F9668(y);
    }
}

void grIceMt_801F77AC(Ground_GObj* arg0) {}

/// #fn_801F77B0
void fn_801F77B0(HSD_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    // 803E4544
    // mpJointGetCb1();
    mpJointSetCb1(4, gp, grIceMt_801FA7F0);
}

/// #grIceMt_801F785C
void grIceMt_801F785C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    // Index into grIm_803E4068 using row indices from grIm_804D69F4->xAC
    gp->gv.icemt.xC4 = (s16) grIm_803E4068[grIm_804D69F4->xAC[1]].id;
    gp->gv.icemt.xC6 = (s16) grIm_803E4068[grIm_804D69F4->xAC[0]].id;

    grIceMt_801FA0BC((int) &gp->gv.icemt.xC4);

    gp->gv.icemt.xDC = 0;
    gp->gv.icemt.xE0 = 2;
    gp->gv.icemt.xDE = 0;

    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b1 = 0;
    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b2 = 0;
    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b3 = 0;
    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b4 = 0;

    gp->gv.icemt.xDA = 0;
    gp->gv.icemt.xE4 = grIm_804DB574;
    gp->gv.icemt.xC8 = 0;
    gp->gv.icemt.xCE = 0;
    gp->gv.icemt.xCA = 0;
    gp->gv.icemt.xCC = 0;
    gp->gv.icemt.xD0 = -1;
    gp->gv.icemt.xD4 = grIm_804DB574;

    ((UnkFlagStruct*) &gp->gv.icemt.xD8)->b7 = 1;

    Ground_801C10B8(gobj, fn_801F77B0);
}

/// #grIceMt_801F796C gricemt.c
bool grIceMt_801F796C(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_GObj* gobj;
    if (gp->gv.icemt2.xC4 != NULL) {
        gobj = Ground_801C2BA4(gp->gv.icemt2.xC4);
        if (gobj == NULL) {
            __assert("gricemt.c", 0x475, "mgobj");
        }
    }
    if (gp->gv.icemt.xCC != NULL) {
        gobj = Ground_801C2BA4(gp->gv.icemt2.xC4);
        if (gobj == NULL) {
            __assert("gricemt.c", 0x4A7, "mgobj");
        }
    }
    //__assert("gricemt.c",0x475,"mgobj");
    grIceMt_801F785C(arg0);
    return 0;
}

/// #grIceMt_801F7A2C

void grIceMt_801F7D90(Ground_GObj* arg0) {}

/// #grIceMt_801F7D94
void grIceMt_801F7D94(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 3);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 4);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 11);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 12);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 13);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 14);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 17);
    // gp->gv.icemt.xD8 = 1;
}

bool grIceMt_801F7EE0(Ground_GObj* arg0)
{
    return false;
}

void grIceMt_801F7EE8(Ground_GObj* arg0)
{
    PAD_STACK(8);
    grIceMt_801F98A8(arg0);
    Ground_801C2FE0(arg0);
}

/// #grIceMt_801F7F1C
void grIceMt_801F7F1C(Ground_GObj* arg0)
{
    int i = 0;
    Ground* gp = GET_GROUND(arg0);
    do {
        if (42 != 0) {
            grMaterial_801C8CDC(arg0);
        }
        i++;
    } while (i < 2);
}

/// #grIceMt_801F7F70
void grIceMt_801F7F70(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    jobj = Ground_801C3FA4(arg0, 4);
    jobj2 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 7);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 9);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 21);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 14);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 20);
    // gp->gv.icemt.xD8 = 1;
}

bool grIceMt_801F8154(Ground_GObj* param1)
{
    return false;
}

/// #grIceMt_801F815C
void grIceMt_801F815C(Ground_GObj* param1)
{
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
    return;
}

/// #grIceMt_801F81B4
void grIceMt_801F81B4(Ground_GObj* arg0)
{
    int i = 0;
    Ground* gp = GET_GROUND(arg0);
    do {
        if (42 != 0) {
            grMaterial_801C8CDC(arg0);
        }
        i++;
    } while (i < 2);
}

/// #grIceMt_801F8208
void grIceMt_801F8208(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 7);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 21);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 14);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 20);
    // gp->gv.icemt.xD8 = 1;
}

bool grIceMt_801F835C(Ground_GObj* param1)
{
    return false;
}

/// #grIceMt_801F8364
void grIceMt_801F8364(Ground_GObj* arg0)
{
    grIceMt_801F98A8(arg0);
    Ground_801C2FE0(arg0);
}

/// #grIceMt_801F8398
void grIceMt_801F8398(Ground_GObj* arg0)
{
    int i = 0;
    Ground* gp = GET_GROUND(arg0);
    do {
        if (42 != 0) {
            grMaterial_801C8CDC(arg0);
        }
        i++;
    } while (i < 2);
}

/// #grIceMt_801F83EC
void grIceMt_801F83EC(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    Ground_801C0498();
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    jobj = Ground_801C3FA4(arg0, 7);
    jobj2 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 9);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 10);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 11);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 23);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 20);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 21);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 22);
    // gp->gv.icemt.xD8 = 1;
}

bool grIceMt_801F85BC(Ground_GObj* param1)
{
    return false;
}

/// #grIceMt_801F85C4
void grIceMt_801F85C4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    grIceMt_801F929C((HSD_GObj*) &gp->gv.icemt.xF8[4]);
    grIceMt_801F98A8(gobj);
    Ground_801C2FE0(gobj);
}
/// #grIceMt_801F8608
void grIceMt_801F8608(Ground_GObj* arg0)
{
    int i = 0;
    Ground* gp = GET_GROUND(arg0);
    do {
        if (42 != 0) {
            grMaterial_801C8CDC(arg0);
        }
        i++;
    } while (i < 2);
}

/// #grIceMt_801F865C
void grIceMt_801F865C(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    // Ground_801C0498();
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    // jobj = Ground_801C3FA4(arg0,7);
    // jobj2 = Ground_801C3FA4(arg0,5);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 7);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 9);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 22);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 20);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 21);
    // gp->gv.icemt.xD8 = 1;
}

bool grIceMt_801F87C0(Ground_GObj* param1)
{
    return false;
}

/// #grIceMt_801F87C8
void grIceMt_801F87C8(Ground_GObj* param1)
{
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
    return;
}

/// @todo Rename: This is callback3 (destroy) for row 5 in grIm_803E4718.
/// Destroys HSD_GObj* stored in icemt.xF8[0-4].
void grIceMt_801F87FC(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    int i;
    for (i = 0; i < 5; i++) {
        HSD_GObj* temp;
        if ((temp = gp->gv.icemt.xF8[i]) != NULL) {
            grMaterial_801C8CDC(temp);
        }
    }
}

/// #grIceMt_801F8850
void grIceMt_801F8850(Ground_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    // Ground_801C0498();
    Ground_801C2ED0(arg0->hsd_obj, gp->map_id);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    // jobj = Ground_801C3FA4(arg0,7);
    // jobj2 = Ground_801C3FA4(arg0,5);
    gp->gv.icemt2.xC8 = Ground_801C3FA4(arg0, 5);
    gp->gv.icemt2.xCC = Ground_801C3FA4(arg0, 6);
    gp->gv.icemt2.xD0 = Ground_801C3FA4(arg0, 7);
    gp->gv.icemt2.xD4 = Ground_801C3FA4(arg0, 8);
    gp->gv.icemt2.xD8 = Ground_801C3FA4(arg0, 21);
    gp->gv.icemt2.xDC = Ground_801C3FA4(arg0, 14);
    gp->gv.icemt2.xE0 = Ground_801C3FA4(arg0, 15);
    gp->gv.icemt2.xE4 = Ground_801C3FA4(arg0, 16);
    gp->gv.icemt2.xE8 = Ground_801C3FA4(arg0, 17);
    gp->gv.icemt2.xEC = Ground_801C3FA4(arg0, 18);
    gp->gv.icemt2.xF0 = Ground_801C3FA4(arg0, 19);
    gp->gv.icemt2.xF4 = Ground_801C3FA4(arg0, 20);
    // gp->gv.icemt.xD8 = 1;
}

bool grIceMt_801F89A4(Ground_GObj* arg0)
{
    return false;
}

/// #grIceMt_801F89AC
void grIceMt_801F89AC(Ground_GObj* param1)
{
    grIceMt_801F98A8(param1);
    Ground_801C2FE0(param1);
    return;
}

/// #grIceMt_801F89E0
void grIceMt_801F89E0(Ground_GObj* arg0)
{
    int i = 0;
    Ground* gp = GET_GROUND(arg0);
    do {
        if (42 != 0) {
            grMaterial_801C8CDC(arg0);
        }
        i++;
    } while (i < 2);
}

/// #grIceMt_801F8A34
void grIceMt_801F8A34(Ground_GObj* arg0)
{
    int i = 0;
    Ground* gp = GET_GROUND(arg0);
    grAnime_801C8138(arg0, gp->map_id, 0);
    grAnime_801C77FC(arg0, 0, 7);
    Ground_801C4E70(Ground_801C3FA4(arg0, 1), Ground_801C3FA4(arg0, 2),
                    Ground_801C3FA4(arg0, 3), Ground_801C3FA4(arg0, 4),
                    Ground_801C3FA4(arg0, 5), Ground_801C3FA4(arg0, 6));
}

bool grIceMt_801F8B08(Ground_GObj* arg0)
{
    return false;
}

/// #grIceMt_801F8B10
void grIceMt_801F8B10(Ground_GObj* arg0)
{
    HSD_JObj* jobj;
    double dVar3;
    double dVar4;
    dVar4 = 0.3;
    jobj = Ground_801C3FA4(arg0, 8);
    HSD_JObjGetTranslationY(jobj);
    dVar4 = Ground_801C0498();
    HSD_JObjSetTranslateY(jobj, 4);
}

void grIceMt_801F8C60(Ground_GObj* arg0) {}

void fn_801F8C64(Item_GObj* gobj, Ground* u1, Vec3* u2, HSD_GObj* u3, f32 u4)
{
    Vec3 pos;
    Item* it = GET_ITEM(gobj);
    grMaterial_801C8E28(gobj);

    HSD_JObjSetFlagsAll(it->xDD4_itemVar.mato.x4, 0x10);
    it_8026B294(gobj, &pos);
    efSync_Spawn(0x445, gobj, &pos);
    Ground_801C53EC(310);
    Camera_80030E44(2, &pos);
}

/// @brief Creates material items and attaches them to Entity05 platform JObjs.
/// @param gobj The Entity05 Ground_GObj
/// @param joint_indices Array of joint indices to get parent JObjs from
/// @param count Number of items to create (max 20)
/// @param output_array Array to store created Item_GObj pointers
void grIceMt_801F8CDC(Ground_GObj* gobj, s16* joint_indices, int count,
                      HSD_GObj** output_array)
{
    Ground* gp = gobj->user_data;
    UnkArchiveStruct* archive;
    void* jobj_desc;
    HSD_JObj* parent_jobjs[20];
    HSD_JObj* parent_jobj;
    HSD_JObj* child_jobj;
    Item_GObj* item;
    int i;
    u8 unused[24];

    archive = grDatFiles_801C6324();
    jobj_desc = archive->unk4->unk8[7].unk0;

    if (count > 20) {
        __assert("gricemt.c", 0x7D4, "count <= 20");
    }

    for (i = 0; i < count; i++) {
        parent_jobjs[i] = Ground_801C3FA4(gobj, joint_indices[i]);
    }

    for (i = 0; i < count; i++) {
        parent_jobj = parent_jobjs[i];
        if (parent_jobj == NULL) {
            __assert("gricemt.c", 0x7E3, "parent_jobj");
        }

        child_jobj = HSD_JObjLoadJoint(jobj_desc);
        if (child_jobj == NULL) {
            __assert("gricemt.c", 0x7E6, "child_jobj");
        }

        HSD_JObjAddChild(parent_jobj, child_jobj);

        item = grMaterial_801C8CFC(8, 0, gp, parent_jobj, NULL, fn_801F8C64,
                                   NULL);
        if (item != NULL) {
            grMaterial_801C8DE0(item, grIm_804DB574, grIm_804DB5B0,
                                grIm_804DB574, grIm_804DB574, grIm_804DB5B4,
                                grIm_804DB574, grIm_804DB5B8);
            grMaterial_801C8E08(item);
            grMaterial_801C8E68(item, 0);
        }
        output_array[i] = item;
    }
}

/// #fn_801F8E58

/// #fn_801F9038

IceMountainParams* fn_801F9150(HSD_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    return grIm_804D69F4;
}

void fn_801F91A4(void) {}

/// #fn_801F91A8 grIm_804D69F4
/// @todo This function reads xAC[gp->xE0] and returns grIm_803E4068[index].id
HSD_GObj* fn_801F91A8(HSD_GObj* arg0)
{
    Ground* gp = GET_GROUND(arg0);
    s16 index = grIm_804D69F4->xAC[gp->gv.icemt.xE0];
    if (index == -1) {
        return (HSD_GObj*) (s32) index;
    }
    return (HSD_GObj*) grIm_803E4068[index].id;
}

/// #grIceMt_801F91EC
void FUN_801f91ec(HSD_GObj* param_1, s16* param_2, int param_3, int param_4,
                  int param_5, int param_6, int param_7,
                  mpLib_Callback param_8)
{
    Ground* gp = GET_GROUND(param_1);
    param_2[0] = 0;
    param_2[1] = 0;
    param_2[2] = param_3;
    param_2[3] = param_4;
    param_2[4] = param_5;
    param_2[5] = param_6;
    param_2[6] = param_7;
    grAnime_801C7A04(param_1, param_3, 7, -20);
    if (param_4 != -1) {
        grAnime_801C7A04(param_1, param_4, 7, -20);
    }
    mpJointSetCb1(param_5, gp, param_8);
}

/// #grIceMt_801F929C
void grIceMt_801F929C(HSD_GObj* arg0)
{
    mpLib_80057BC0(2);
    mpJointListAdd(2);
    grAnime_801C83D0(arg0, 2, 7);
}

/// #fn_801F9338
void fn_801F9338(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    // mpLib_80057BC0(2);
    // mpJointListAdd(2);
    // grAnime_801C83D0(arg0,2,7);
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

/// #fn_801F9448
void fn_801F9448(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    // mpLib_80057BC0(2);
    // mpJointListAdd(2);
    // grAnime_801C83D0(arg0,2,7);
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

/// #fn_801F9558
void fn_801F9558(Ground* gp, int arg1, CollData* arg2, s32 arg3,
                 mpLib_GroundEnum arg4, float arg8)
{
    // mpLib_80057BC0(2);
    // mpJointListAdd(2);
    // grAnime_801C83D0(arg0,2,7);
    grIceMt_801FA7F0(gp, arg1, arg2, arg3, arg4, arg8);
}

void grIceMt_801F9668(float arg8)
{
    HSD_GObj* gobj;
    Ground* gp;

    gobj = Ground_801C2BA4(8);
    if (gobj == NULL) {
        __assert("gricemt.c", 0xA37, "bg_gobj");
    }
    gp = GET_GROUND(gobj);
    if (gp == NULL) {
        __assert("gricemt.c", 0xA38, "bg_gp");
    }

    gp->gv.icemt2.xC4 = arg8;
}

float grIceMt_801F96E0(float y)
{
    HSD_GObj* jobj;
    double dVar3;
    double dVar4;
    dVar4 = 0.3;

    jobj = Ground_801C2BA4(4);
    if (jobj == NULL) {
        __assert("gricemt.c", 2629, "mgobj");
    }
    if (jobj->hsd_obj == NULL) {
        __assert("gricemt.c", 2630, "jobj");
    }
    HSD_JObjAddTranslationY(jobj->hsd_obj, y);
    jobj = Ground_801C2BA4(7);
    if (jobj == NULL) {
        __assert("gricemt.c", 2639, "mgobj");
    }
    if (jobj->hsd_obj == NULL) {
        __assert("gricemt.c", 2630, "jobj");
    }
    HSD_JObjAddTranslationY(jobj->hsd_obj, y);
    // HSD_JObjGetTranslationY(jobj);
    // dVar4 = Ground_801C0498();
    // HSD_JObjSetTranslateY(jobj,4);
    return 0;
}

/// #grIceMt_801F98A8
/// @note Checks bit 6 of icemt2.xC4 (as byte) - clears it and does cleanup.
int grIceMt_801F98A8(Ground_GObj* param1)
{
    Ground* gp = param1->user_data;
    u8 flags = *(u8*) &gp->gv.icemt2.xC4;
    HSD_JObj** ptrs = &gp->gv.icemt2.xC8;

    if (flags & 0x40) {
        *(u8*) &gp->gv.icemt2.xC4 = flags & ~0x40;
        if (ptrs[0]) {
            Ground_801C2D0C(0, ptrs[0]);
        }
        if (ptrs[1]) {
            Ground_801C2D0C(1, ptrs[1]);
        }
        if (ptrs[2]) {
            Ground_801C2D0C(2, ptrs[2]);
        }
        if (ptrs[3]) {
            Ground_801C2D0C(3, ptrs[3]);
        }
    }
    return 0;
}

/// #grIceMt_801F993C

/// #grIceMt_801F9ACC
// void grIceMt_801F9ACC() {
void grIceMt_801F9ACC(float y)
{
    HSD_GObj* jobj;
    double dVar3;
    double dVar4;
    dVar4 = 0.3;

    jobj = Ground_801C2BA4(4);
    if (jobj == NULL) {
        __assert("gricemt.c", 2629, "mgobj");
    }
    HSD_JObjGetTranslationY(jobj->hsd_obj);
    dVar4 = Ground_801C0498();
    HSD_JObjSetTranslateY(jobj->hsd_obj, y);
    Ground_801C32AC(4);
    Ground_801C32AC(4);
    Ground_801C32AC(4);

    HSD_JObjSetTranslateY(jobj->hsd_obj, y);
    grIceMt_801FA854();
}

/// #grIceMt_801FA0BC

/// #grIceMt_801FA364

int fn_801FA4CC(int num)
{ // https://decomp.me/scratch/pSJNA
    if (num == 1) {
        Ground_801C5740(num);
        num = 1;
    } else {
        num = 0;
    }
    return num;
}

int grIceMt_801FA500(HSD_GObj* param1)
{
    int iVar1 = NULL;
    int iVar2;
    int iVar3;
    iVar3 = 0;
    if (param1->hsd_obj == NULL) {
        __assert("gricemt.c", 2993, "jobj");
        iVar1 = 0;
        //} else {
        //	ivar1 = param1->hsd_obj
    }
    do {
        if (iVar1 == 0) {
            return iVar3;
        }
        iVar3++;
    } while (true);
}

/// #grIceMt_801FA6D8
void grIceMt_801FA6D8(HSD_GObj* param1)
{
    if ((Stage_80225194() == 76) && (Ground_801C2BA4(10)) &&
        GET_GROUND(param1))
    {
        Ground* gp = GET_GROUND(param1);
        // if (param1->user_data) {
        gp->gv.icemt.xCE = grIm_804D69F4->x3A; // gp->xC_callback;
        //}
    }
}

// extern f32 grIm_804DB574;

void grIceMt_801FA728(Vec3* arg0)
{
    HSD_GObj* temp_r3;
    HSD_GObj* temp_r3_3;
    Ground* temp_r3_2;
    Ground* temp_r3_4;

    if (Stage_80225194() == 0x4C) {
        temp_r3 = Ground_801C2BA4(10);
        if (temp_r3 != NULL) {
            temp_r3_2 = temp_r3->user_data;
            if (temp_r3_2 != NULL) {
                arg0->x = 0;
                arg0->y = -temp_r3_2->gv.icemt.xD4;
                arg0->z = 0;
                return;
            }
        }
        arg0->z = 0;
        arg0->y = 0;
        arg0->x = 0;
        return;
    }
    temp_r3_3 = Ground_801C2BA4(9);
    if (temp_r3_3 != NULL) {
        temp_r3_4 = temp_r3_3->user_data;
        if (temp_r3_4 != NULL) {
            arg0->x = 0;
            arg0->y = -temp_r3_4->gv.icemt.xD4;
            arg0->z = 0;
            return;
        }
    }
    arg0->z = 0;
    arg0->y = 0;
    arg0->x = 0;
}

/// #grIceMt_801FA7F0
void grIceMt_801FA7F0(Ground* gp, s32 arg1, CollData* arg2, s32 arg3,
                      mpLib_GroundEnum arg4, float arg8)
{
    HSD_GObj* playerGObj = Ground_801C57A4();
    if ((Ground_801C2BA4(10)) && (playerGObj->user_data))
    { // && playerGObj->userdata) {
    }
}

/// #grIceMt_801FA854
void grIceMt_801FA854(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(0);
    HSD_JObj* jobj;

    if (gobj) {
        jobj = Ground_801C3FA4(gobj, 0x12);
        if (jobj) {
            Ground_801C2D0C(4, jobj);
        }
        jobj = Ground_801C3FA4(gobj, 0x13);
        if (jobj) {
            Ground_801C2D0C(5, jobj);
        }
        jobj = Ground_801C3FA4(gobj, 0x14);
        if (jobj) {
            Ground_801C2D0C(6, jobj);
        }
        jobj = Ground_801C3FA4(gobj, 0x15);
        if (jobj) {
            Ground_801C2D0C(7, jobj);
        }
    }
    return;
}

DynamicsDesc* grIceMt_801FA8F8(enum_t id)
{
    return 0;
}

bool grIceMt_801FA900(Vec3* a, int id, HSD_JObj* jobj)
{
    return true;
}
