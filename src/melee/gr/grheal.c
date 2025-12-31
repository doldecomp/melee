#include "gr/grheal.h"

#include "gr/grheal.static.h"

#include "placeholder.h"

#include <platform.h>

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "dolphin/types.h"

#include "gr/forward.h"

#include "gm/gm_1832.h"
#include "gr/granime.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

void grHeal_8021EF38(bool arg0) {}

void grHeal_8021EF3C(void)
{
    grHeal_804D6AF0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grHeal_8021EFEC(0);
    grHeal_8021EFEC(1);
    grHeal_8021EFEC(3);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C3980(2.0F * Stage_GetBlastZoneTopOffset());
}

void grHeal_8021EFBC(void) {}

void grHeal_8021EFC0(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grHeal_8021EFE4(void)
{
    return false;
}

Ground_GObj* grHeal_8021EFEC(u32 idx)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grHeal_803E8454[idx];

    gobj = Ground_801C14D0(idx);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 273, idx);
    }

    return gobj;
}

/// #grHeal_8021F0D8

bool grHeal_8021F170(Ground_GObj* gobj)
{
    return false;
}

void grHeal_8021F178(Ground_GObj* gobj) {}

void grHeal_8021F17C(Ground_GObj* gobj) {}

/// #grHeal_8021F180

bool grHeal_8021F41C(Ground_GObj* gobj)
{
    return false;
}

s32 fn_8021F424(void)
{
    Ground_GObj* ground;
    Ground* gp;

    ground = Ground_801C2BA4(1);
    if (ground != NULL) {
        gp = ground->user_data;
        if ((gp != NULL) && (gp->gv.unk.xC4 != 0)) {
            return 1;
        }
    }
    return 0;
}

void grHeal_8021F474(Ground_GObj* ground)
{
    Ground* gp;

    gp = ground->user_data;
    Ground_801C3D44(fn_8021F424, 10.0f, 20.0f);
    lb_800115F4();
    gp->gv.flatzone2.xC4 = 0;
}

void grHeal_8021F4BC(Ground_GObj* gobj) {}

void fn_8021F4C0(Ground* gp, void* arg2, s32 arg4, s32 arg5, s32 arg6)
{
    if ((((*(u8*) ((u8*) arg4 + 0x34) >> 3U) & 0xF) == 1) &&
        ((arg6 - 1) <= 1U))
    {
        gp->gv.unk.xC4 = 1;
    }
}

void grHeal_8021F4E8(s32 arg0, HSD_JObj* parent_jobj)
{
    Ground_GObj* ground;
    HSD_JObj* jobj;
    HSD_JObj* child;

    ground = grHeal_8021EFEC(4U);
    if (ground == NULL) {
        __assert(grHeal_803E851C, 0x1B8U, "gobj");
    }
    grAnime_801C8138(ground, 4, 0);
    grAnime_801C7FF8(ground, 0, 7, 0, (f32) arg0, 0.0f);
    jobj = GET_JOBJ(ground);
    child = HSD_JObjGetChild(jobj);
    HSD_JObjReparent(child, parent_jobj);
    HSD_JObjClearFlagsAll(child, 0x10U);
    Ground_801C4A08(ground);
}

void grHeal_8021F5C8(Ground_GObj* gobj) {}

bool grHeal_8021F5CC(Ground_GObj* gobj)
{
    return false;
}

void grHeal_8021F5D4(Ground_GObj* gobj) {}

void grHeal_8021F5D8(Ground_GObj* gobj) {}

void grHeal_8021F5DC(Ground_GObj* ground)
{
    Ground* gp;

    gp = ground->user_data;
    gp->x10_flags.b2 = false;
    grAnime_801C8138(ground, gp->map_id, 0);
}

bool grHeal_8021F618(Ground_GObj* gobj)
{
    return false;
}

void grHeal_8021F620(Ground_GObj* gobj) {}

void grHeal_8021F624(Ground_GObj* gobj) {}

void grHeal_8021F628(s32 arg0, HSD_JObj* jobj_parent)
{
    Ground_GObj* ground;
    HSD_JObj* jobj;
    HSD_JObj* child;

    ground = grHeal_8021EFEC(2U);
    if (ground == NULL) {
        __assert(grHeal_803E851C, 0x201U, "gobj");
    }
    grAnime_801C8138(ground, 2, 0);
    grAnime_801C7FF8(ground, 0, 7, 0, (f32) arg0, 0.0f);
    jobj = GET_JOBJ(ground);
    child = HSD_JObjGetChild(jobj);
    HSD_JObjReparent(child, jobj_parent);
    Ground_801C4A08(ground);
}

void grHeal_8021F6F8(Ground_GObj* gobj) {}

bool grHeal_8021F6FC(Ground_GObj* gobj)
{
    return false;
}

void grHeal_8021F704(Ground_GObj* gobj) {}

void grHeal_8021F708(Ground_GObj* gobj) {}

u32 grHeal_8021F70C(u32 character_id)
{
    s32* entry;
    int frame;

    frame = 0;
    if ((s32) character_id == 0x13) {
        character_id = 0x12;
    }

    entry = (s32*) &grHeal_803E851C[0xD];

    while (entry[frame] != -1 && entry[frame] != character_id) {
        frame++;
    }

    if (grHeal_803E83B8[frame] == -1) {
        OSReport("*** Not found Next Player!(%d)\n", frame);
        frame = 0;
    }
    return frame;
}

void grHeal_8021F79C(s32 arg0, s32 idx, s32 arg2)
{
    HSD_GObj* gp;
    HSD_JObj* jobj;
    BobOmbRain bobomb_rain;
    PAD_STACK(4);

    gp = Ground_801C2BA4(0);
    jobj = Ground_801C3FA4(gp, idx);
    bobomb_rain.x0 = gp;
    bobomb_rain.x4 = NULL;
    bobomb_rain.x14 = arg0;
    bobomb_rain.x18 = arg2;
    bobomb_rain.x1C.b0 = 1;
    lb_8000B1CC(jobj, NULL, &bobomb_rain.x8_vec);
    it_8026BE84(&bobomb_rain);
}

DynamicsDesc* grHeal_8021F830(enum_t arg0)
{
    return false;
}

bool grHeal_8021F838(Vec3* arg0, int arg1, HSD_JObj* jobj)
{
    return true;
}
