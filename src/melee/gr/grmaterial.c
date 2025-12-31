#include "grmaterial.h"

#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/it_2E6A.h"
#include "it/types.h"

#include "lb/forward.h"
#include <baselib/forward.h>

#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/id.h>
#include <baselib/jobj.h>

/* 1C897C */ static void grMaterial_801C897C(HSD_JObj* jobj, u32 flags);
/* 1C8D44 */ static Item_GObj*
grMaterial_801C8D44(int arg0, int arg1, Ground* arg2, Vec3* arg3, int arg4,
                    void (*arg5)(Item_GObj*, Ground*),
                    void (*arg6)(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32),
                    void (*arg7)(Item_GObj*, Ground*, HSD_GObj*));
/* 1C8E48 */ static bool grMaterial_801C8E48(HSD_GObj* gobj);
/* 1C8E74 */ static void grMaterial_801C8E74(void);
/* 1C8EF8 */ static void fn_801C8EF8(HSD_MObj* mobj, u32 rendermode);
/* 3E0A20 */ static HSD_MObjInfo grMaterial_803E0A20 = { 0 };

static u32 data_section_pad[35] = { 0 };

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

Item_GObj*
grMaterial_801C8CFC(int arg0, int arg1, Ground* arg2, HSD_JObj* arg3,
                    void (*arg4)(Item_GObj*, Ground*),
                    void (*arg5)(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32),
                    void (*arg6)(Item_GObj*, Ground*, HSD_GObj*))
{
    return it_802E6AEC(arg2, arg0, arg1, arg3, NULL, 0, arg4, arg5, arg6);
}

Item_GObj* grMaterial_801C8D44(int arg0, int arg1, Ground* arg2, Vec3* arg3,
                               int arg4, void (*arg5)(Item_GObj*, Ground*),
                               void (*arg6)(Item_GObj*, Ground*, Vec3*,
                                            HSD_GObj*, f32),
                               void (*arg7)(Item_GObj*, Ground*, HSD_GObj*))
{
    return it_802E6AEC(arg2, arg0, arg1, 0, arg3, arg4, arg5, arg6, arg7);
}

void grMaterial_801C8D98(HSD_GObj* gobj, int id)
{
    it_802725D4(gobj);
    Item_80268E5C(gobj, id, 2);
}

void grMaterial_801C8DE0(Item_GObj* gobj, float arg8, float arg9, float argA,
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

void grMaterial_801C8E08(Item_GObj* gobj)
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
    if (it->x524_cmd.u != NULL) {
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

/// #fn_801C8EF8

/// #grMaterial_801C92C0

/// #grMaterial_801C9470

/// #grMaterial_801C9490

void grMaterial_801C94D8(void* obj)
{
    HSD_JObj* hsd_obj = obj;
    HSD_DObj* var_r30;
    HSD_JObj* var_r30_2;
    HSD_MObj* var_r3;
    s32 var_r0;
    u8 _[0x18];

    if (hsd_obj != NULL) {
        if (hsd_obj->flags & 0x4020) {
            var_r0 = 0;
        } else {
            var_r0 = 1;
        }
        if (var_r0 != 0) {
            var_r30 = HSD_JObjGetDObj(hsd_obj);
            while (var_r30 != NULL) {
                if (var_r30 != NULL) {
                    var_r3 = var_r30->mobj;
                } else {
                    var_r3 = NULL;
                }
                if (var_r3 != NULL) {
                    hsdChangeClass(var_r3, &grMaterial_803E0A20);
                }
                if (var_r30 != NULL) {
                    var_r30 = var_r30->next;
                } else {
                    var_r30 = NULL;
                }
            }
        }
        if (hsd_obj == NULL) {
            var_r30_2 = NULL;
        } else {
            var_r30_2 = hsd_obj->child;
        }
        while (var_r30_2 != NULL) {
            grMaterial_801C92C0(var_r30_2);
            if (var_r30_2 == NULL) {
                var_r30_2 = NULL;
            } else {
                var_r30_2 = var_r30_2->next;
            }
        }
    }
}

/// #grMaterial_801C95C4

typedef struct {
    u8 _pad0[0x10];
    /* 0x10:4 */ u8 x10_upper : 4;
    /* 0x10:3 */ u8 x10_b3 : 1;
    u8 x10_lower : 3;
    u8 _pad1[0x40 - 0x11];
    /* 0x40 */ s32 x40;
    /* 0x44 */ s32 x44;
    /* 0x48 */ s32 x48;
    /* 0x4C */ s32 x4C;
    u8 _pad2[0xBC - 0x50];
    /* 0xBC:7 */ u8 xBC_b7 : 1;
    /* 0xBC:6 */ u8 xBC_b6 : 1;
    u8 xBC_rest : 6;
} grMaterialData;

void grMaterial_801C9604(HSD_GObj* gobj, int arg1, int arg2)
{
    grMaterialData* gp = gobj->user_data;
    u8 val;

    gp->x44 = arg2;
    gp->x48 = arg1;
    gp->x40 = 0;
    gp->x4C = 0;
    val = gp->xBC_b6 = 0;
    gp->xBC_b7 = val;
    gp->x10_b3 = 0;
    grMaterial_801C9698(gobj);
}

/// #fn_801C9664

/// #grMaterial_801C9698
