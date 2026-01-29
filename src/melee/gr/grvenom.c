#include "grvenom.h"

#include <platform.h>

#include "gr/grcorneria.h"
#include "gr/grdisplay.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "if/ifcoget.h"
#include "if/ifstatus.h"
#include "lb/lb_00B0.h"

#include <baselib/aobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>

/// #grVenom_8020362C

void grVenom_80203B14(bool arg) {}

/// #grVenom_80203B18

void grVenom_80203DD0(void)
{
    HSD_GObj* gobj;
    HSD_LObj* lobj;

    gobj = HSD_GObj_Entities->xC;
    while (gobj != NULL) {
        if (HSD_GObjGetClassifier(gobj) == 0xC) {
            lobj = GET_LOBJ(gobj);
            while (lobj != NULL) {
                HSD_ForeachAnim(lobj, LOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjSetFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                lobj = HSD_LObjGetNext(lobj);
            }
            return;
        }
        gobj = HSD_GObjGetNext(gobj);
    }
}

void grVenom_80203E80(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grVenom_80203EA4(void)
{
    return false;
}

// Decompilation of grVenom_80203EAC
// TODO: grVe_Data should be defined in gr/types.h or a proper header
typedef struct grVe_Data {
    char x0[0x44];
    StageCallbacks callbacks[1];  // at offset 0x44
    char x58[0x1B8 - 0x58];
    char x1B8_file[0x1DC - 0x1B8];  // 0x1B8: "%s:%d..." string
    char x1DC_func[0x20];          // 0x1DC: function name or filename
} grVe_Data;

extern grVe_Data grVe_803E5348;

Ground_GObj* grVenom_80203EAC(int gobj_id)
{
    Ground_GObj* gobj;
    Ground* gp;
    grVe_Data* base = &grVe_803E5348;
    StageCallbacks* callbacks = &((StageCallbacks*)((char*)base + 0x44))[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport(&base->x1B8_file[0], &base->x1DC_func[0], 0x23B, gobj_id);
    }

    return gobj;
}

void grVenom_80203F98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grVenom_80203FC4(Ground_GObj* arg)
{
    return false;
}

void grVenom_80203FCC(Ground_GObj* arg) {}

void grVenom_80203FD0(Ground_GObj* arg) {}

// Decompilation of grVenom_80203FD4

#include "gr/grvenom.h"
#include "gr/inlines.h"
#include "gr/ground.h"
#include "gr/granime.h"

void grVenom_80203FD4(Ground_GObj* gobj)
{
    HSD_JObj* jobj1;
    HSD_JObj* jobj4;
    HSD_JObj* jobj3;
    HSD_JObj* jobj2;
    HSD_JObj* jobj5;
    HSD_JObj* jobj6;
    Ground* gp = gobj->user_data;

    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
    jobj6 = Ground_801C3FA4(gobj, 6);
    jobj5 = Ground_801C3FA4(gobj, 5);
    jobj2 = Ground_801C3FA4(gobj, 2);
    jobj3 = Ground_801C3FA4(gobj, 3);
    jobj4 = Ground_801C3FA4(gobj, 4);
    jobj1 = Ground_801C3FA4(gobj, 1);
    Ground_801C4E70(jobj1, jobj4, jobj3, jobj2, jobj5, jobj6);
    gp = gobj->user_data;
    gp->x10_flags.b2 = 0;
}

bool grVenom_802040A4(Ground_GObj* arg)
{
    return false;
}

void grVenom_802040AC(Ground_GObj* arg) {}

void grVenom_802040B0(Ground_GObj* arg) {}

// Decompilation of fn_802040B4

enum_t Stage_80225194(void);

void fn_802040B4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    if (Stage_80225194() == 0xE4) {
        gp->gv.venom.xC8 = 1;
    }
}

/// #grVenom_802040F0

bool grVenom_8020427C(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_80204284

void grVenom_80204424(Ground_GObj* arg) {}

// Decompilation of grVenom_80204428
// FAKE MATCH: grVenom_GroundVars has wrong types for this function

#include <platform.h>
#include "gr/ground.h"
#include "gr/inlines.h"
#include "mp/mplib.h"

void grVenom_80204428(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    gp->gv.venom.xC4 = (u32)Ground_801C3FA4(gobj, 4);
    gp->gv.venom.xC8 = (u32)Ground_801C3FA4(gobj, 0xE);
    gp->gv.venom.xCC = (u32)Ground_801C3FA4(gobj, 0x10);
    gp->gv.venom.xD0 = (u32)Ground_801C3FA4(gobj, 0x11);
    *(u32*)&gp->gv.venom.xD4 = (u32)Ground_801C3FA4(gobj, 0x12);
    *(u32*)&gp->gv.venom.xD8 = (u32)Ground_801C3FA4(gobj, 0x13);
    *(u32*)&gp->gv.venom.xDC = (u32)Ground_801C3FA4(gobj, 0x15);

    // Access bitfields using mutecity2 which has 8 bitfields at xC4_flags
    // xC4_flags is at offset 0, we need offset 0x1C, so shift by 7 u32s
    gp->gv.mutecity2.xC4_flags.b0 = 0;
    gp->gv.mutecity2.xC4_flags.b1 = 0;
    gp->gv.mutecity2.xC4_flags.b2 = 0;
    gp->gv.mutecity2.xC4_flags.b3 = 0;
    gp->gv.mutecity2.xC4_flags.b4 = 0;
    gp->gv.mutecity2.xC4_flags.b5 = 0;
    gp->gv.mutecity2.xC4_flags.b6 = 0;

    gp->gv.venom.xE4 = 0.0F;

    Ground_801C5440(gp, 0, 0x6B6C3);
    mpLib_80057BC0(2);
}

bool grVenom_80204544(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_8020454C

void grVenom_80204B84(Ground_GObj* arg) {}

/// #grVenom_80204B88

void grVenom_80204CE0(Ground_GObj* arg) {}

bool grVenom_80204CE4(Ground_GObj* arg)
{
    return false;
}

void grVenom_80204CEC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s32 temp;
    PAD_STACK(8);

    ifStatus_802F6898();
    un_802FF570();

    if (Ground_801C2BA4(1) == NULL) {
        if (grCorneria_801E2598(gp->gv.venom.xC4, gp->gv.venom.xC8) != 0) {
            temp = gp->gv.venom.xCC;
            gp->gv.venom.xCC = temp - 1;
            if (temp < 0) {
                HSD_GObj* other = (HSD_GObj*) grVenom_80203EAC(1);
                Ground* other_gp = other->user_data;
                grCorneria_801E2738(other, &other_gp->gv.venom.xC4, gp->gv.venom.xC4, gp->gv.venom.xC8);
                gp->gv.venom.xC8 = gp->gv.venom.xC8 + 1;
                gp->gv.venom.xCC = 0;
            }
        } else {
            temp = gp->gv.venom.xCC;
            gp->gv.venom.xCC = temp - 1;
            if (temp < 0) {
                Ground_801C4A08(gobj);
            }
        }
    }
}

void grVenom_80204DB0(Ground_GObj* gobj)
{
    ifStatus_802F68F0();
    un_802FF620();
}

// Decompilation of grVenom_80204DD4
// Unit: main/melee/gr/grvenom
// Manual expansion of HSD_JObjSetScaleX/Y without using inline functions

void grVenom_80204DD4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;

    Ground_801C2ED0(jobj, gp->map_id);

    // HSD_JObjSetScaleX(jobj, 1.0F) expanded:
    ((jobj) ? ((void) 0) : __assert("jobj.h", 0x308, "jobj"));
    jobj->scale.x = 1.0F;
    if (!(jobj->flags & (1 << 25))) {
        if (jobj != 0L && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }

    // HSD_JObjSetScaleY(jobj, 1.0F) expanded:
    ((jobj) ? ((void) 0) : __assert("jobj.h", 0x317, "jobj"));
    jobj->scale.y = 1.0F;
    if (!(jobj->flags & (1 << 25))) {
        if (jobj != 0L && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

bool grVenom_80204EF4(Ground_GObj* arg)
{
    return false;
}

bool grVenom_80204EFC(Ground_GObj* arg)
{
    return Ground_801C2FE0(arg);
}

void grVenom_80204F1C(Ground_GObj* arg) {}

/// #grVenom_80204F20

bool grVenom_802052D8(Ground_GObj* arg)
{
    return false;
}

// Decompilation of grVenom_802052E0
// TODO: VenomSpawnData struct should be defined in gr/types.h or grvenom.h
typedef struct {
    u8 pad[0x218];
    f32 x;
    f32 y;
    f32 z;
} VenomSpawnData;

void grVenom_802052E0(Ground_GObj* gobj, Vec3* pos)
{
    s32* spawn_table = (s32*)&grVe_803E5348;
    Ground* gp;
    HSD_JObj* jobj;
    Vec3 jobj_pos;
    u32 spawn_idx;
    s32 data_idx;
    VenomSpawnData* spawn_data;

    if (gobj != NULL) {
        gp = gobj->user_data;
        Ground_801C2BA4(5);
        jobj = Ground_801C3FA4(gobj, 5);
        lb_8000B1CC(jobj, NULL, &jobj_pos);
        spawn_idx = gp->gv.venom.xC8;
        data_idx = spawn_table[spawn_idx + 11];
        spawn_data = (VenomSpawnData*)((u8*)spawn_table + data_idx * 12);
        pos->x = jobj_pos.x + spawn_data->x;
        pos->y = jobj_pos.y + spawn_data->y;
        pos->z = jobj_pos.z + spawn_data->z;
    } else {
        pos->z = 0.0F;
        pos->y = 0.0F;
        pos->x = 0.0F;
    }
}

/// #grVenom_802053B0

void grVenom_802056AC(Ground_GObj* arg) {}

// Decompilation of grVenom_802056B0

extern int grVe_803E5380[];
extern int grVe_803E5680[];
extern u32 grVe_804D6A34;

void grVenom_802056B0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    int* joint_idx;
    int joint_offset;
    int* joints;
    int joint_id;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->gv.venom.xC8 = grVe_804D6A34;
    joint_idx = grVe_803E5380;
    joints = grVe_803E5680;
    gp->gv.venom.xD0 = 0;
    gp->gv.venom.xDC = 0.0F;
    gp->gv.venom.xE8 = 0.0F;
    gp->gv.venom.xE4 = 0.0F;
    gp->gv.venom.xE0 = 0.0F;
    joint_offset = joint_idx[gp->gv.venom.xC8];
    joint_id = joints[joint_offset];
    mpJointListAdd(joint_id);

    Ground_801C2ED0(jobj, gp->map_id);
}

bool grVenom_80205750(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_80205758

void grVenom_80205AD0(Ground_GObj* arg) {}

/// #grVenom_80205AD4

bool grVenom_80205DF0(Ground_GObj* arg)
{
    return false;
}

s32 grVenom_80205DF8(Vec3* pos)
{
    if (pos->x > Stage_GetBlastZoneRightOffset()) {
        return 1;
    }
    if (pos->x < Stage_GetBlastZoneLeftOffset()) {
        return 1;
    }
    if (pos->y > Stage_GetBlastZoneTopOffset()) {
        return 1;
    }
    if (pos->y < Stage_GetBlastZoneBottomOffset()) {
        return 1;
    }
    return 0;
}

// Decompilation of grVenom_80205E84

float Stage_GetBlastZoneBottomOffset(void);
float Stage_GetBlastZoneLeftOffset(void);
float Stage_GetBlastZoneRightOffset(void);
float Stage_GetBlastZoneTopOffset(void);

s32 grVenom_80205E84(Vec2* pos)
{
    if (pos->x > Stage_GetBlastZoneRightOffset() - 20.0F) {
        return 1;
    }
    if (pos->x < 20.0F + Stage_GetBlastZoneLeftOffset()) {
        return 1;
    }
    if (pos->y > Stage_GetBlastZoneTopOffset() - 20.0F) {
        return 1;
    }
    if (pos->y < 20.0F + Stage_GetBlastZoneBottomOffset()) {
        return 1;
    }
    return 0;
}

/// #grVenom_80205F30

void grVenom_80206870(Ground_GObj* arg) {}

/// #grVenom_80206874

bool grVenom_80206B68(Ground_GObj* arg)
{
    return false;
}

void grVenom_80206B70(Ground_GObj* arg)
{
    grVenom_80205F30(arg);
}

void grVenom_80206B90(Ground_GObj* arg) {}

void grVenom_80206B94(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    smashTaunt_801E2550(gobj, &gp->gv.smashtaunt);
}

bool grVenom_80206BBC(Ground_GObj* arg)
{
    return false;
}

void grVenom_80206BC4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grCorneria_801E277C(gobj, &gp->gv.corneria);
}

void grVenom_80206BEC(Ground_GObj* arg) {}

/// #grVenom_80206BF0

// Decompilation of grVenom_80206CB0

void grVenom_80206CB0(s32 arg0)
{
    HSD_GObj* gobj;

    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        if (arg0 != 0) {
            Ground_801C4A08(gobj);
        }
        gobj = Ground_801C2BA4(1);
        if (gobj != NULL) {
            Ground_801C4A08(gobj);
        }
        HSD_SisLib_803A5F50(1);
    }
}

// Decompilation of grVenom_80206D10
// Unit: main/melee/gr/grvenom

int mpJointFromLine(int line_id);

s32 grVenom_80206D10(s32 arg0)
{
    s32 in_range;
    s32 result;
    u32 diff;

    if (stage_info.internal_stage_id == VENOM && arg0 != -1) {
        result = mpJointFromLine(arg0);
        diff = result - 3;
        in_range = 1;
        if (diff > 1U) {
            in_range = 0;
        }
        if (in_range != 0) {
            return 1;
        }
    }
    return 0;
}

DynamicsDesc* grVenom_80206D74(enum_t arg)
{
    return false;
}

// Decompilation of grVenom_80206D7C
// Unit: main/melee/gr/grvenom

// arg0 appears to be some struct with a float at offset 0x4
// arg1 is unused
// arg2 is an HSD_JObj* that gets passed to lb_8000B1CC

bool grVenom_80206D7C(void* arg0, s32 arg1, HSD_JObj* arg2)
{
    Vec3 sp20;
    Vec3 sp14;
    HSD_GObj* gobj;
    Ground* gp;

    lb_8000B1CC(arg2, NULL, &sp20);
    gobj = Ground_801C2BA4(5);
    if (gobj != NULL) {
        gp = gobj->user_data;
        if (gp != NULL && (HSD_JObj*)gp->gv.venom.xD0 == arg2) {
            lb_8000B1CC((HSD_JObj*)gp->gv.venom.xCC, NULL, &sp14);
            if (*(f32*)((u8*)arg0 + 0x4) > sp14.y) {
                return 0;
            }
        }
    }
    if (*(f32*)((u8*)arg0 + 0x4) > sp20.y) {
        return 1;
    }
    return 0;
}
