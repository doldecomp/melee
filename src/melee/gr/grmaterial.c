#include "lb/forward.h"
#include <baselib/forward.h>

#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/it_2E6A.h"
#include "it/types.h"

#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/id.h>
#include <baselib/jobj.h>

/* 1C8EF8 */ static void fn_801C8EF8(HSD_MObj* mobj, u32 rendermode);

HSD_MObjInfo grMaterial_803E0A20 = { 0 };
u32 data_section_pad[35] = { 0 };

static void grMaterial_801C87D0(HSD_JObj* jobj, u32 flags)
{
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    u32 unused;

    if (jobj != NULL) {
        dobj = HSD_JObjGetDObj(jobj);
        while (dobj != NULL) {
            if ((mobj = dobj != NULL ? dobj->mobj : NULL) != NULL) {
                HSD_MObjSetFlags(mobj, flags);
            }
            dobj = dobj != NULL ? dobj->next : NULL;
        }
    }
}

void grMaterial_801C8858(HSD_JObj* jobj, u32 arg1)
{
    u32 unused[8];
    if (jobj == NULL) {
        return;
    }
    grMaterial_801C87D0(jobj, arg1);
    jobj = jobj == NULL ? NULL : jobj->child;
    while (jobj != NULL) {
        grMaterial_801C8858(jobj, arg1);
        jobj = jobj == NULL ? NULL : jobj->next;
    }
}

void grMaterial_801C897C(HSD_JObj* jobj, u32 flags)
{
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    u32 unused;

    if (jobj != NULL) {
        dobj = HSD_JObjGetDObj(jobj);
        while (dobj != NULL) {
            if ((mobj = dobj != NULL ? dobj->mobj : NULL) != NULL) {
                HSD_MObjClearFlags(mobj, flags);
            }
            dobj = dobj != NULL ? dobj->next : NULL;
        }
    }
}

void grMaterial_801C8A04(HSD_JObj* jobj, u32 arg1)
{
    u32 unused[8];
    if (jobj == NULL) {
        return;
    }
    grMaterial_801C897C(jobj, arg1);
    jobj = jobj == NULL ? NULL : jobj->child;
    while (jobj != NULL) {
        grMaterial_801C8A04(jobj, arg1);
        jobj = jobj == NULL ? NULL : jobj->next;
    }
}

HSD_JObj* grMaterial_801C8B28(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        while (HSD_JObjGetParent(jobj) != NULL) {
            jobj = HSD_JObjGetParent(jobj);
        }
    }
    return jobj;
}

void grMaterial_801C8B68(HSD_JObj* jobj, int arg1)
{
    HSD_JObj* var_r30;
    int var_r0;
    int var_r3;

    var_r3 = 0;
    if (jobj != NULL) {
        if (arg1 != 0) {
            !arg1;
        } else {
            if (jobj->flags & 0x4000) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }
            if (var_r0) {
                var_r3 = 1;
            }
        }
        if (var_r3) {
            HSD_IDInsertToTable(NULL, (u32) jobj, jobj);
        }
        if (!(jobj->flags & 0x1000)) {
            jobj = HSD_JObjGetChild(jobj);
            while (jobj != NULL) {
                var_r30 = jobj;
                var_r3 = 0;
                if (jobj != NULL) {
                    if (arg1 != 0) {
                        !arg1;
                    } else {
                        if (jobj->flags & 0x4000) {
                            var_r0 = 1;
                        } else {
                            var_r0 = 0;
                        }
                        if (var_r0) {
                            var_r3 = 1;
                        }
                    }
                    if (var_r3) {
                        HSD_IDInsertToTable(NULL, (u32) var_r30, var_r30);
                    }
                    if (!(jobj->flags & 0x1000)) {
                        var_r30 = HSD_JObjGetChild(jobj);
                        while (var_r30 != NULL) {
                            grMaterial_801C8B68(var_r30, arg1);
                            var_r30 = HSD_JObjGetNext(var_r30);
                        }
                    }
                }
                jobj = HSD_JObjGetNext(jobj);
            }
        }
    }
}

void grMaterial_801C8CDC(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

void grMaterial_801C8CFC(int arg0, int arg1, Ground* arg2, HSD_JObj* arg3,
                         int arg4, HSD_GObjEvent arg5, int arg6)
{
    it_802E6AEC(arg2, arg0, arg1, arg3, NULL, 0, arg4, arg5, arg6);
}

void grMaterial_801C8D44(int arg0, int arg1, Ground* arg2, Vec3* arg3,
                         int arg4, int arg5, HSD_GObjEvent arg6, int arg7)
{
    it_802E6AEC(arg2, arg0, arg1, 0, arg3, arg4, arg5, arg6, arg7);
}

void grMaterial_801C8D98(HSD_GObj* gobj, int id)
{
    it_802725D4(gobj);
    Item_80268E5C(gobj, id, 2);
}

void grMaterial_801C8DE0(HSD_GObj* gobj, float arg8, float arg9, float argA,
                         float argB, float argC, float argD, float argE)
{
    Item* it = gobj->user_data;
    HurtCapsule* hurt = it->xACC_itemHurtbox;
    hurt->a_offset.x = arg8;
    hurt->a_offset.y = arg9;
    hurt->a_offset.z = argA;
    hurt->b_offset.x = argB;
    hurt->b_offset.y = argC;
    hurt->b_offset.z = argD;
    hurt->scale = argE;
}

void grMaterial_801C8E08(HSD_GObj* gobj)
{
    it_802756E0(gobj);
}

void grMaterial_801C8E28(HSD_GObj* gobj)
{
    it_802756D0(gobj);
}

bool grMaterial_801C8E48(HSD_GObj* gobj)
{
    Item* it = gobj->user_data;
    if (it->x52C_item_script != NULL) {
        return false;
    }
    return true;
}

void grMaterial_801C8E68(HSD_GObj* gobj, GroundOrAir ground_or_air)
{
    Item* it = gobj->user_data;
    it->ground_or_air = ground_or_air;
}

void grMaterial_801C8E74(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&grMaterial_803E0A20),
                     HSD_CLASS_INFO(&hsdMObj), "sysdolphin_base_library",
                     "gr_mobj", sizeof(HSD_MObjInfo), sizeof(HSD_MObj));
    HSD_CLASS_INFO(&grMaterial_803E0A20)->release =
        HSD_CLASS_INFO(&hsdMObj)->release;
    HSD_CLASS_INFO(&grMaterial_803E0A20)->amnesia =
        HSD_CLASS_INFO(&hsdMObj)->amnesia;
    grMaterial_803E0A20.setup = fn_801C8EF8;
    grMaterial_803E0A20.load = hsdMObj.load;
    grMaterial_803E0A20.make_texp = hsdMObj.make_texp;
}
