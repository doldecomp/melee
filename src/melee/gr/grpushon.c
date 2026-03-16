#include "grpushon.h"

#include "placeholder.h"
#include "types.h"

#include <platform.h>

#include "cm/camera.h"
#include "ft/ftdevice.h"
#include "ft/ftlib.h"

#include "gr/forward.h"

#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "lb/lb_00F9.h"
#include "lb/types.h"
#include "mp/mplib.h"
#include "sysdolphin/baselib/lobj.h"

#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/random.h>

struct grPushOn_Entry {
    s32 x0;
    s16 x4;
    s16 x6;
};

struct grPushOn_Lookup {
    s32 key;
    s32 value;
};

static struct {
    s32 x0;
    DynamicsDesc* x4;
    DynamicsDesc* x8;
    DynamicsDesc* xC;
    DynamicsDesc* x10;
    DynamicsDesc* x14;
    bool x18;
    struct grPushOn_Entry x1c[0x1E];
    struct grPushOn_Lookup x10c[0x21];
}* grPushOn_804D6AB8;

extern Vec3 grPushOn_803B8440;
extern Vec3 grPushOn_803B8458;
extern Vec3 grPushOn_803B8464;
extern HSD_LightDesc grPushOn_803E7B74;
extern HSD_LightDesc grPushOn_803E7B90;

StageCallbacks grPushOn_803E7AC8[3] = {
    { grPushOn_802184CC, grPushOn_80218590, grPushOn_80218598,
      grPushOn_8021859C, 0 },
    { grPushOn_802185A0, grPushOn_80218670, grPushOn_802186C8,
      grPushOn_802187A4, 0xC0000000 },
    { grPushOn_802187A8, grPushOn_80218880, grPushOn_80218888,
      grPushOn_80218ED0, 0 },
};

StageData grPushOn_803E7B10 = {
    PUSHON,
    grPushOn_803E7AC8,
    "/GrNPo.dat",
    grPushOn_802182C8,
    grPushOn_802182C4,
    grPushOn_80218330,
    grPushOn_80218378,
    grPushOn_802183DC,
    grPushOn_80219458,
    grPushOn_80219528,
    (1 << 0),
    NULL,
    0,
};

void grPushOn_802182C4(bool arg) {}

void grPushOn_802182C8(void)
{
    grPushOn_804D6AB8 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
    grPushOn_802183E4(0);
    grPushOn_802183E4(1);
    mpLib_80057BC0(0);
}

void grPushOn_80218330(void)
{
    HSD_GObj* gobj;
    Vec3 vec;

    grPushOn_802183E4(2);
    gobj = Ground_801C57A4();
    if (gobj != NULL) {
        ftLib_80086644(gobj, &vec);
        Ground_801C38BC(vec.x, vec.y);
        Camera_8002F3AC();
    }
}

void grPushOn_80218378(void)
{
    bool val;
    grZakoGenerator_801CAE04(NULL);
    val = grPushOn_804D6AB8->x18;
    if (val) {
        val = HSD_Randi(grPushOn_804D6AB8->x18);
    } else {
        val = false;
    }
    if (!val) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grPushOn_802183DC(void)
{
    return false;
}

HSD_GObj* grPushOn_802183E4(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grPushOn_803E7AC8[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grpushon.c", 222,
                 gobj_id);
    }

    return gobj;
}

void grPushOn_802184CC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Vec3 cam_offset;

    grAnime_801C8138(gobj, gp->map_id, 0);
    Ground_801C39C0();
    Ground_801C3BB4();
    Stage_UnkSetVec3TCam_Offset(&cam_offset);
    Ground_801C3880(0.5f * (Stage_GetCamBoundsTopOffset() +
                            Stage_GetBlastZoneTopOffset()) -
                    cam_offset.y);
    Ground_801C3890(0.5f * (Stage_GetCamBoundsBottomOffset() +
                            Stage_GetBlastZoneBottomOffset()) -
                    cam_offset.y);
    Ground_801C38A0(0.5f * (Stage_GetCamBoundsLeftOffset() +
                            Stage_GetBlastZoneLeftOffset()) -
                    cam_offset.x);
    Ground_801C38AC(0.5f * (Stage_GetCamBoundsRightOffset() +
                            Stage_GetBlastZoneRightOffset()) -
                    cam_offset.x);
}

bool grPushOn_80218590(Ground_GObj* arg)
{
    return false;
}

void grPushOn_80218598(Ground_GObj* arg) {}

void grPushOn_8021859C(Ground_GObj* arg) {}

void grPushOn_802185A0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    ftCo_800C07F8(gobj, 3, fn_802192A4);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C752C(jobj, 1, 0x77A4, HSD_AObjSetFlags, 3, 0x20000000);
    gp->u.map.xC4_b0 = false;
    mpJointSetCb1(3, gp, fn_802190A0);
    mpJointSetCb1(4, gp, fn_802190A0);
    mpJointSetCb1(5, gp, fn_802190A0);
}

bool grPushOn_80218670(Ground_GObj* arg)
{
    return false;
}

bool fn_80218678(void)
{
    HSD_GObj* gobj = Ground_801C2BA4(1);
    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
        if (gp != NULL) {
            if (gp->u.map.xC4_b0) {
                return true;
            }
        }
    }
    return false;
}

void grPushOn_802186C8(Ground_GObj* gobj)
{
    Vec3 vec;
    Ground* gp = gobj->user_data;
    PAD_STACK(12);

    vec = grPushOn_803B8440;
    Ground_801C3D44(fn_80218678, 25.0f, 20.0f);
    {
        HSD_GObj* gobj2 = Ground_801C57A4();
        if (gobj2 != NULL) {
            ftLib_80086644(gobj2, &vec);
            Ground_801C0498();
            if (vec.y < 0.0f) {
                Ground_801C0498();
                vec.y = 0.0f;
            } else if (vec.y > 800.0f * Ground_801C0498()) {
                vec.y = 800.0f * Ground_801C0498();
            }
            Ground_801C38BC(vec.x, vec.y);
        }
    }
    lb_800115F4();
    gp->u.map.xC4_b0 = false;
}

void grPushOn_802187A4(Ground_GObj* arg) {}

void grPushOn_802187A8(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_LObj* lobj;

    gp->u.pushon.gobj = ((HSD_GObj*) HSD_GObj_804D7824)->next_gx;
    PAD_STACK(16);
    grPushOn_802190D0(gp->u.pushon.gobj);
    lobj = ((HSD_GObj*) gp->u.pushon.gobj)->hsd_obj;
    gp->u.pushon.count = 0;
    while (lobj != NULL) {
        gp->u.pushon.lobjs[gp->u.pushon.count] = lobj;
        gp->u.pushon.lobj_flags[gp->u.pushon.count] = HSD_LObjGetFlags(lobj);
        lobj = lobj == NULL ? NULL : lobj->next;
        gp->u.pushon.count++;
    }
    gp->u.pushon.point_light = grPushOn_80218ED4(gp->u.pushon.gobj);
    gp->u.pushon.spot_light = grPushOn_80218FC0(gp->u.pushon.gobj);
    grPushOn_80218888(gobj);
}

bool grPushOn_80218880(Ground_GObj* arg)
{
    return false;
}

/// #grPushOn_80218888

void grPushOn_80218ED0(Ground_GObj* arg) {}

HSD_LObj* grPushOn_80218ED4(HSD_GObj* gobj)
{
    HSD_LObj* new_lobj;
    HSD_LObj* lobj;
    Vec3 pos;
    PAD_STACK(8);

    if (gobj == NULL || (lobj = gobj->hsd_obj) == NULL) {
        return NULL;
    }
    while ((lobj == NULL ? NULL : lobj->next) != NULL) {
        lobj = lobj == NULL ? NULL : lobj->next;
    }
    new_lobj = HSD_LObjLoadDesc(&grPushOn_803E7B74);
    if (new_lobj != NULL) {
        pos = grPushOn_803B8458;
        HSD_LObjSetNext(lobj, new_lobj);
        HSD_LObjSetPosition(new_lobj, &pos);
        HSD_LObjSetFlags(new_lobj, 0x20);
    }
    return new_lobj;
}

HSD_LObj* grPushOn_80218FC0(HSD_GObj* gobj)
{
    HSD_LObj* new_lobj;
    HSD_LObj* lobj;
    Vec3 pos;
    PAD_STACK(8);

    if (gobj == NULL || (lobj = gobj->hsd_obj) == NULL) {
        return NULL;
    }
    while ((lobj == NULL ? NULL : lobj->next) != NULL) {
        lobj = lobj == NULL ? NULL : lobj->next;
    }
    new_lobj = HSD_LObjLoadDesc(&grPushOn_803E7B90);
    if (new_lobj != NULL) {
        pos = grPushOn_803B8464;
        HSD_LObjSetNext(lobj, new_lobj);
        HSD_LObjSetPosition(new_lobj, &pos);
    }
    return new_lobj;
}

/// Ground collision callback for pushon stage elements.
/// Activates push behavior when collision flags indicate contact (b1234 == 1).
void fn_802190A0(Ground* gp, s32 joint_id, CollData* coll, s32 unk,
                 mpLib_GroundEnum ground_enum, f32 arg5)
{
    if (((*(u8*) &coll->x34_flags >> 3U) & 0xF) == 1 &&
        (ground_enum - 1) <= 1U)
    {
        gp->u.map.xC4_b0 = true;
    }
}

/// #grPushOn_802190D0

void grPushOn_80219204(int arg0, int* out1, int* out2)
{
    int idx = arg0 - 0x99;
    *out1 = grPushOn_804D6AB8->x1c[idx].x0;
    *out2 = grPushOn_804D6AB8->x1c[idx].x4;
}

int grPushOn_80219230(int arg0)
{
    s32 i = 0;
    s32 key;

    while (i < 0x21 && (key = grPushOn_804D6AB8->x10c[i].key) != -1) {
        if (key == arg0) {
            return grPushOn_804D6AB8->x10c[i].value;
        }
        i++;
    }
    __assert("grpushon.c", 0x35DU, "0");
}

/// #fn_802192A4

DynamicsDesc* grPushOn_80219458(enum_t arg0)
{
    s32 joint;
    s32 kind;

    if (arg0 != -1) {
        joint = mpJointFromLine(arg0);
        if (joint != -1) {
            if (joint == 1) {
                mpLineGetKind(arg0);
                return grPushOn_804D6AB8->x4;
            }
            if (joint == 2) {
                kind = mpLineGetKind(arg0);
                if (kind == 1) {
                    return grPushOn_804D6AB8->x8;
                }
                if (kind == 2) {
                    return grPushOn_804D6AB8->xC;
                }
                if (kind == 4) {
                    return grPushOn_804D6AB8->x10;
                }
                if (kind == 8) {
                    return grPushOn_804D6AB8->x14;
                }
                return NULL;
            }
            return NULL;
        }
    }
    return NULL;
}

bool grPushOn_80219528(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
