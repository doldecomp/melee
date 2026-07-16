#include "grmaterial.h"

#include "gr/types.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/it_2E6A.h"
#include "it/ithitbox.h"
#include "it/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbspdisplay.h"

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
/* 1C8E74 */ static void grMaterial_801C8E74(void);
/* 1C8EF8 */ static void fn_801C8EF8(HSD_MObj* mobj, u32 rendermode);

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
    /*  +50 */ HSD_TevDesc tevdesc_tmpl;
    /*  +C4 */ HSD_TECnst texp_tmpl;
};

/* 3E0A20 */ static struct grMaterial_MObjInfo grMaterial_803E0A20 = {
    { { grMaterial_801C8E74 } },
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    {
        NULL,
        1,
        0,
        0xFF,
        0xFF,
        0xFF,
        {
            {
                GX_TEV_ADD,   GX_CC_CPREV,    GX_CC_ZERO,     GX_CC_ZERO,
                GX_CC_ZERO,   GX_CS_SCALE_1,  GX_TB_ZERO,     GX_DISABLE,
                GX_TEVPREV,   GX_TEV_ADD,     GX_CA_ZERO,     GX_CA_ZERO,
                GX_CA_ZERO,   GX_CA_APREV,    GX_CS_SCALE_1,  GX_TB_ZERO,
                GX_DISABLE,   GX_TEVPREV,     GX_TC_LINEAR,   GX_TEV_SWAP0,
                GX_TEV_SWAP0, GX_TEV_KCSEL_1, GX_TEV_KASEL_1,
            },
        },
    },
    { HSD_TE_CNST, NULL, NULL, HSD_TE_RGB, HSD_TE_U8, 0xFF, 0xFF },
};

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

static void fn_801C8EF8(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObj* tobj;
    u8 pad1[0xC];
    GXColor sp114;
    HSD_TevDesc sp_tevdesc;
    u8 pad2[0x54];
    HSD_TECnst sp_cnst;
    u8 pad3[0x10];
    Ground* gp;
    HSD_TObj** cur_tobj;
    s32 reg1_lt4_for_kcsel;
    s32 temp;
    s32 alpha_reg;
    s32 reg2;
    s32 reg1_lt4;
    s32 reg1;
    u32 mobj_rendermode;

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
    HSD_ASSERT(0xF3, mobj->tevdesc);
    HSD_TExpSetupTev(mobj->tevdesc, mobj->texp);
    HSD_TObjSetupVolatileTev(tobj, mobj_rendermode);

    gp = HSD_GObj_804D7814->user_data;
    (void) gp;
    if (grMaterial_GetOverlay(gp)->x7C_color_enable || gp->x10_flags.b6) {
        sp_cnst = grMaterial_803E0A20.texp_tmpl;
        sp_tevdesc = grMaterial_803E0A20.tevdesc_tmpl;
        sp_tevdesc.stage = HSD_StateAssignTev();
        if (grMaterial_GetOverlay(gp)->x7C_color_enable) {
            reg1 = lbGetFreeColorRegister(0, mobj, NULL);
            if (reg1 == -1) {
                OSReport("can't find free color register!\n");
                HSD_ASSERT(0x7A, 0);
            }
            sp_cnst.comp = reg1_lt4 = 1;
            sp_cnst.ctype = temp = 0;
            sp_cnst.reg = (u8) reg1;
            sp_cnst.val = &gp->x6C;
            HSD_TExpSetReg((HSD_TExp*) &sp_cnst);
            if (reg1 < 4) {
                !reg1;
            } else {
                reg1_lt4 = 0;
            }
            if (reg1_lt4 != 0) {
                temp = 4;
            } else {
                temp = 0;
            }
            reg2 = lbGetFreeColorRegister(temp, mobj, (HSD_TExp*) &sp_cnst);
            if (reg2 == -1) {
                OSReport("can't find free color register!\n");
                HSD_ASSERT(0x88, 0);
            }
            sp_cnst.comp = reg1_lt4_for_kcsel = 1;
            sp_cnst.ctype = temp = 0;
            sp_cnst.reg = (u8) reg2;
            sp114.r = gp->x6C.a;
            sp114.g = gp->x6C.a;
            sp114.b = gp->x6C.a;
            sp_cnst.val = &sp114;
            HSD_TExpSetReg((HSD_TExp*) &sp_cnst);
            sp_tevdesc.u.tevconf.clr_b = lb_8000CC8C(reg1);
            sp_tevdesc.u.tevconf.clr_c = lb_8000CC8C(reg2);
            if (reg1 < 4) {
                !reg1;
            } else {
                reg1_lt4_for_kcsel = 0;
            }
            if (reg1_lt4_for_kcsel != 0) {
                sp_tevdesc.u.tevconf.kcsel = lb_8000CCA4(reg1);
            } else {
                if (reg2 < 4) {
                    temp = 1;
                } else {
                    temp = 0;
                }
                if (temp != 0) {
                    sp_tevdesc.u.tevconf.kcsel = lb_8000CCA4(reg2);
                }
            }
        }
        if (gp->x10_flags.b6) {
            alpha_reg = lbGetFreeAlphaRegister(0, mobj, NULL);
            if (alpha_reg == -1) {
                OSReport("can't find free alpha register!\n");
                HSD_ASSERT(0xA7, 0);
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
            if ((mobj = dobj != NULL ? dobj->mobj : NULL) != NULL) {
                hsdChangeClass(mobj, &grMaterial_803E0A20);
            }
            dobj = dobj != NULL ? dobj->next : NULL;
        }
    }
    jobj = jobj == NULL ? NULL : jobj->child;
    while (jobj != NULL) {
        grandchild = jobj;
        if (jobj != NULL) {
            if (jobj->flags & 0x4020) {
                cond = 0;
            } else {
                cond = 1;
            }
            if (cond != 0) {
                dobj = HSD_JObjGetDObj(grandchild);
                while (dobj != NULL) {
                    if ((mobj = dobj != NULL ? dobj->mobj : NULL) != NULL) {
                        hsdChangeClass(mobj, &grMaterial_803E0A20);
                    }
                    dobj = dobj != NULL ? dobj->next : NULL;
                }
            }
            if (jobj == NULL) {
                grandchild = NULL;
            } else {
                grandchild = jobj->child;
            }
            while (grandchild != NULL) {
                grMaterial_801C92C0(grandchild);
                if (grandchild == NULL) {
                    grandchild = NULL;
                } else {
                    grandchild = grandchild->next;
                }
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

/* 4D456C */ static ItCmd grMaterial_804D456C[1] = {
    grMaterial_801C9470,
};

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
