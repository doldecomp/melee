#include "grmaterial.h"

#include "gr/types.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/it_2E6A.h"
#include "it/ithitbox.h"
#include "it/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <baselib/forward.h>

#include <dolphin/os.h>
#include <baselib/debug.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/id.h>
#include <baselib/jobj.h>
#include <baselib/mobj.h>
#include <baselib/state.h>
#include <baselib/tev.h>
#include <baselib/texp.h>
#include <baselib/tobj.h>

/* 1C897C */ static void grMaterial_801C897C(HSD_JObj* jobj, u32 flags);
/* 1C8D44 */ Item_GObj*
grMaterial_801C8D44(int arg0, int arg1, Ground* arg2, Vec3* arg3, int arg4,
                    void (*arg5)(Item_GObj*, Ground*),
                    void (*arg6)(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32),
                    void (*arg7)(Item_GObj*, Ground*, HSD_GObj*));
/* 1C8E48 */ static bool grMaterial_801C8E48(HSD_GObj* gobj);
/* 1C8E74 */ static void grMaterial_801C8E74(void);
/* 1C8EF8 */ static void fn_801C8EF8(HSD_MObj* mobj, u32 rendermode);
/* 1C9490 */ void grMaterial_801C9490(Item_GObj* gobj, CommandInfo* cmd);

static inline ColorOverlay* grMaterial_GetOverlay(Ground* gp)
{
    return (ColorOverlay*) ((u8*) gp + 0x40);
}

struct grMaterial_MObjInfo {
    /*   +0 */ HSD_ClassInfo parent;
    /*  +3C */ HSD_MObjSetupFunc setup;
    /*  +40 */ int (*load)(HSD_MObj* mobj, HSD_MObjDesc* desc);
    /*  +44 */ HSD_TExp* (*make_texp)(HSD_MObj* mobj, HSD_TObj* tobj_top,
                                      HSD_TExp** list);
    /*  +48 */ void (*setup_tev)(HSD_MObj* mobj, HSD_TObj* tobj,
                                 u32 rendermode);
    /*  +4C */ void (*unset)(HSD_MObj* mobj, u32 rendermode);
    /*  +50 */ u8 pad_x50[0xDC - 0x50];
    /*  +DC */ char library_name[0xF4 - 0xDC];
};

/* 3E0A20 */ static struct grMaterial_MObjInfo grMaterial_803E0A20 = { 0 };
/* 4D4560 */ static char grMaterial_804D4560[] = "gr_mobj";
/* 4D4568 */ static char grMaterial_804D4568[] = "0";
/* 4D456C */ static ItCmd grMaterial_804D456C[1] = {
    grMaterial_801C9470,
};

static u32 data_section_pad[35] = { 0 };

void grMaterial_801C87D0(HSD_JObj* jobj, u32 flags)
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
                     HSD_CLASS_INFO(&hsdMObj),
                     grMaterial_803E0A20.library_name, "gr_mobj",
                     sizeof(HSD_MObjInfo), sizeof(HSD_MObj));
    HSD_CLASS_INFO(&grMaterial_803E0A20)->release =
        HSD_CLASS_INFO(&hsdMObj)->release;
    HSD_CLASS_INFO(&grMaterial_803E0A20)->amnesia =
        HSD_CLASS_INFO(&hsdMObj)->amnesia;
    grMaterial_803E0A20.setup = fn_801C8EF8;
    grMaterial_803E0A20.load = hsdMObj.load;
    grMaterial_803E0A20.make_texp = hsdMObj.make_texp;
}

static void fn_801C8EF8(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TECnst sp_cnst;
    HSD_TevDesc sp_tevdesc;
    GXColor sp114;
    Ground* gp;
    HSD_TObj* tobj;
    HSD_TObj** cur_tobj;
    s32 reg1;
    s32 reg2;
    s32 alpha_reg;
    s32 var_r24;
    s32 var_r23;
    s32 var_r0;
    u32 mobj_rendermode;
    char* base = (char*) &grMaterial_803E0A20;
    PAD_STACK(0x74);

    HSD_StateInitTev();
    mobj_rendermode = mobj->rendermode;
    HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                         mobj->mat->specular, mobj->mat->alpha);
    if (mobj_rendermode & RENDER_SPECULAR) {
        HSD_SetMaterialShininess(mobj->mat->shininess);
    }
    cur_tobj = NULL;
    tobj = mobj->tobj;
    if ((mobj_rendermode & RENDER_SHADOW) && tobj_shadows != NULL) {
        cur_tobj = &tobj;
        while (*cur_tobj != NULL) {
            cur_tobj = &(*cur_tobj)->next;
        }
        *cur_tobj = tobj_shadows;
    }
    if ((mobj_rendermode & RENDER_TOON) && tobj_toon != NULL &&
        tobj_toon->imagedesc != NULL)
    {
        tobj_toon->next = tobj;
        tobj = tobj_toon;
    }
    HSD_TObjSetup(tobj);
    HSD_TObjSetupTextureCoordGen(tobj);
    if (mobj->tevdesc == NULL) {
        __assert(base + 0xF4, 0xF3, base + 0x104);
    }
    HSD_TExpSetupTev(mobj->tevdesc, mobj->texp);
    HSD_TObjSetupVolatileTev(tobj, mobj_rendermode);

    gp = HSD_GObj_804D7814->user_data;
    if (grMaterial_GetOverlay(gp)->x7C_color_enable || gp->x10_flags.b6) {
        sp_cnst = *(HSD_TECnst*) (base + 0xC4);
        sp_tevdesc = *(HSD_TevDesc*) (base + 0x50);
        sp_tevdesc.stage = HSD_StateAssignTev();
        if (grMaterial_GetOverlay(gp)->x7C_color_enable) {
            reg1 = lbGetFreeColorRegister(0, mobj, NULL);
            if (reg1 == -1) {
                OSReport(base + 0x114);
                __assert(base + 0xF4, 0x7A, grMaterial_804D4568);
            }
            var_r24 = 1;
            sp_cnst.comp = 1;
            sp_cnst.ctype = 0;
            sp_cnst.reg = (u8) reg1;
            sp_cnst.val = &gp->x6C;
            HSD_TExpSetReg((HSD_TExp*) &sp_cnst);
            if (reg1 < 4) {
            } else {
                var_r24 = 0;
            }
            if (var_r24 != 0) {
                var_r0 = 4;
            } else {
                var_r0 = 0;
            }
            reg2 = lbGetFreeColorRegister(var_r0, mobj, (HSD_TExp*) &sp_cnst);
            if (reg2 == -1) {
                OSReport(base + 0x114);
                __assert(base + 0xF4, 0x88, grMaterial_804D4568);
            }
            var_r23 = 1;
            sp_cnst.comp = 1;
            sp_cnst.ctype = 0;
            sp_cnst.reg = (u8) reg2;
            sp114.r = gp->x6C.a;
            sp114.g = gp->x6C.a;
            sp114.b = gp->x6C.a;
            sp_cnst.val = &sp114;
            HSD_TExpSetReg((HSD_TExp*) &sp_cnst);
            sp_tevdesc.u.tevconf.clr_b = lb_8000CC8C(reg1);
            sp_tevdesc.u.tevconf.clr_c = lb_8000CC8C(reg2);
            if (reg1 < 4) {
            } else {
                var_r23 = 0;
            }
            if (var_r23 != 0) {
                sp_tevdesc.u.tevconf.kcsel = lb_8000CCA4(reg1);
            } else {
                if (reg2 < 4) {
                    var_r0 = 1;
                } else {
                    var_r0 = 0;
                }
                if (var_r0 != 0) {
                    sp_tevdesc.u.tevconf.kcsel = lb_8000CCA4(reg2);
                }
            }
        }
        if (gp->x10_flags.b6) {
            alpha_reg = lbGetFreeAlphaRegister(0, mobj, NULL);
            if (alpha_reg == -1) {
                OSReport(base + 0x138);
                __assert(base + 0xF4, 0xA7, grMaterial_804D4568);
            }
            sp_cnst.comp = 5;
            sp_cnst.ctype = 3;
            sp_cnst.reg = (u8) alpha_reg;
            sp_cnst.val = &gp->xC0;
            HSD_TExpSetReg((HSD_TExp*) &sp_cnst);
            sp_tevdesc.u.tevconf.alpha_b = GX_CA_APREV;
            sp_tevdesc.u.tevconf.alpha_c = lb_8000CD90(alpha_reg);
            sp_tevdesc.u.tevconf.alpha_d = GX_CA_ZERO;
        }
        HSD_SetupTevStage(&sp_tevdesc);
    }
    HSD_SetupRenderModeWithCustomPE(mobj_rendermode, mobj->pe);
    if (cur_tobj != NULL) {
        *cur_tobj = NULL;
    }
}

void grMaterial_801C92C0(HSD_JObj* jobj)
{
    HSD_DObj* dobj;
    HSD_JObj* grandchild;
    HSD_MObj* mobj;
    s32 cond;
    u32 unused[8];

    if (jobj == NULL) {
        return;
    }
    if (jobj->flags & 0x4020) {
        cond = 0;
    } else {
        cond = 1;
    }
    if (cond != 0) {
        dobj = HSD_JObjGetDObj(jobj);
        while (dobj != NULL) {
            mobj = dobj != NULL ? dobj->mobj : NULL;
            if (mobj != NULL) {
                hsdChangeClass(mobj, &grMaterial_803E0A20);
            }
            dobj = dobj != NULL ? dobj->next : NULL;
        }
    }
    jobj = jobj == NULL ? NULL : jobj->child;
    while (jobj != NULL) {
        if (jobj != NULL) {
            if (jobj->flags & 0x4020) {
                cond = 0;
            } else {
                cond = 1;
            }
            if (cond != 0) {
                dobj = HSD_JObjGetDObj(jobj);
                while (dobj != NULL) {
                    mobj = dobj != NULL ? dobj->mobj : NULL;
                    if (mobj != NULL) {
                        hsdChangeClass(mobj, &grMaterial_803E0A20);
                    }
                    dobj = dobj != NULL ? dobj->next : NULL;
                }
            }
            grandchild = jobj == NULL ? NULL : jobj->child;
            while (grandchild != NULL) {
                grMaterial_801C92C0(grandchild);
                grandchild = grandchild == NULL ? NULL : grandchild->next;
            }
        }
        jobj = jobj == NULL ? NULL : jobj->next;
    }
}

void grMaterial_801C9470(Item_GObj* gobj, CommandInfo* cmd)
{
    grMaterial_801C9490(gobj, cmd);
}

void grMaterial_801C9490(Item_GObj* gobj, CommandInfo* cmd)
{
    Ground* gp = gobj->user_data;
    u32 val = (*(u16*) cmd->ptr[0] >> 2) & 0xFF;
    gp->xC0 = (f32) val;
    gp->x10_flags.b6 = 1;
}

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

void grMaterial_801C95C4(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    lb_80014498(grMaterial_GetOverlay(gp));
    gp->x10_flags.b4 = 1;
}

// TODO: is this GET_GROUND? calling it directly didn't work.
inline Ground* grMaterial_801C9604_inline(HSD_GObj* arg0)
{
    return arg0->user_data;
}

void grMaterial_801C9604(HSD_GObj* gobj, int arg1, bool arg2)
{
    Ground* gp = grMaterial_801C9604_inline(gobj);
    ColorOverlay* co = grMaterial_GetOverlay(gp);
    co->x4_pri = arg2;
    co->x8_ptr1 = (union ColorOverlay_x8_t*) arg1;
    co->x0_timer = 0;
    co->xC_loop = 0;
    co->x7C_color_enable = co->x7C_flag2 = 0;
    gp->x10_flags.b4 = 0;
    grMaterial_801C9698(gobj);
}

void fn_801C9664(Item_GObj* gobj, CommandInfo* cmd, int arg2)
{
    int idx = arg2 - 21;
    grMaterial_804D456C[idx](gobj, cmd);
}

void grMaterial_801C9698(HSD_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    if (lb_80014258(gobj, grMaterial_GetOverlay(gp), fn_801C9664)) {
        gp->x10_flags.b4 = 1;
    }
}
