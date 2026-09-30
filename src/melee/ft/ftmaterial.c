/**
 * @file ftmaterial.c
 * @brief Fighter material and texture state system implementation
 * @details Handles the material and texture state for fighters, including color overlays, visibility, and rendering modes like metal or shadows.
 * Module prefix: ft
 */
#include "ftmaterial.h"

#include "fighter.h"
#include "forward.h"
#include "ft_0C8C.h"
#include "ftCo_800C7CA0.h"
#include "ftdevice.h"
#include "kinds/ftCommon/ftCo_09F4.h"
#include "types.h"
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbrefract.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/tobj.h>

HSD_MObjInfo ftMObj = { ftMaterial_800BF260 };

struct ft_MObjInfo {
    HSD_MObjInfo parent;
    HSD_TevDesc tevdesc_tmpl;
    HSD_TECnst texp_tmpl;
};

static HSD_TevDesc ftMaterial_803C69D0 = {
    NULL,
    TEVCONF_MODE,
    GX_TEVSTAGE0,
    GX_TEXCOORD_NULL,
    GX_TEXCOORD_NULL,
    GX_COLOR_NULL,
    { {
        GX_TEV_ADD,   GX_CC_CPREV,    GX_CC_ZERO,     GX_CC_ZERO,
        GX_CC_ZERO,   GX_CS_SCALE_1,  GX_TB_ZERO,     GX_ENABLE,
        GX_TEVPREV,   GX_TEV_ADD,     GX_CA_ZERO,     GX_CA_ZERO,
        GX_CA_ZERO,   GX_CA_APREV,    GX_CS_SCALE_1,  GX_TB_ZERO,
        GX_DISABLE,   GX_TEVPREV,     GX_TC_LINEAR,   GX_TEV_SWAP0,
        GX_TEV_SWAP0, GX_TEV_KCSEL_1, GX_TEV_KASEL_1,
    } },
};

static HSD_TECnst ftMaterial_803C6A44 = {
    HSD_TE_CNST, NULL, NULL, HSD_TE_RGB, HSD_TE_U8, 0xFF, 0xFF, 0, 0,
};

/**
 * @brief Initializes the fighter MObj info struct with custom setup callbacks.
 */
void ftMaterial_800BF260(void)
{
    hsdInitClassInfo(&ftMObj.parent, &hsdMObj.parent,
                     "sysdolphin_base_library", "ft_mobj",
                     sizeof(HSD_MObjInfo), sizeof(HSD_MObj));
    ftMObj.setup = (HSD_MObjSetupFunc) (Event) ftMaterial_800BF2B8;
}

/**
 * @brief Main material setup callback for fighter meshes. Configures rendering flags for metal, shadow, toon, and custom overlays.
 * @param mobj The material object being set up
 * @param rendermode The current render mode flags
 * @param unused Unused parameter
 */
void ftMaterial_800BF2B8(HSD_MObj* mobj, u32 rendermode, u32 unused)
{
    Fighter* fp;
    HSD_TObj* tobj;
    HSD_TExp texp;
    HSD_PEDesc pe;
    HSD_TObj** cur_tobj;
    HSD_TExp* new_texp;
    HSD_PEDesc* pe_desc;

    fp = GET_FIGHTER(HSD_GObj_804D7814);

    if (fp->x2226_b5) {
        lbRefract_80022998(mobj, rendermode,
                           fp->smash_attrs.x2134_vibrateFrame);
        return;
    }

    if (!fp->x2223_b2 && (!fp->x2228_b0 || !fp->x2224_b0)) {
        if (fp->is_metal) {
            mobj = ft_804D6580;
        } else if (fp->x2227_b3) {
            mobj = ft_804D6588;
        }
    }

    HSD_StateInitTev();

    {
        rendermode = mobj->rendermode;
        HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                             mobj->mat->specular, mobj->mat->alpha);
        if (rendermode & RENDER_SPECULAR) {
            HSD_SetMaterialShininess(mobj->mat->shininess);
        }
        {
            cur_tobj = NULL;
            {
                tobj = mobj->tobj;
                if (rendermode & RENDER_SHADOW && tobj_shadows != NULL) {
                    cur_tobj = &tobj;
                    while (*cur_tobj != NULL) {
                        cur_tobj = &(*cur_tobj)->next;
                    }
                    *cur_tobj = tobj_shadows;
                }
                if ((rendermode & RENDER_TOON) && tobj_toon != NULL &&
                    tobj_toon->imagedesc != NULL)
                {
                    tobj_toon->next = tobj;
                    tobj = tobj_toon;
                }
                HSD_TObjSetup(tobj);
                HSD_TObjSetupTextureCoordGen(tobj);
                HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj, rendermode);
            }
            if (fp->x61D != 0xFF) {
                rendermode |= RENDER_NO_ZUPDATE | RENDER_XLU;
            }
            {
                HSD_TExp* temp_texp =
                    ftMaterial_800BF534(fp, mobj, &texp, rendermode);
                new_texp = temp_texp;
                ftMaterial_800BF6BC(fp, mobj, new_texp);
                if (fp->x2223_b2 && !fp->x2223_b3) {
                    rendermode |= RENDER_NO_ZUPDATE;
                }
                {
                    if (fp->x2223_b3 && fp->x61D == 0xFF) {
                        pe.flags = (1 << 3) | (1 << 4) | (1 << 5);
                        pe.dst_alpha = 0;
                        pe.type = 0;
                        pe.src_factor = 4;
                        pe_desc = &pe;
                        pe.dst_factor = 5;
                        pe.logic_op = 15;
                        pe.z_comp = 3;
                        pe.alpha_comp0 = 7;
                        pe.ref0 = 0;
                        pe.alpha_op = 0;
                        pe.alpha_comp1 = 7;
                        pe.ref1 = 0;
                    } else {
                        pe_desc = mobj->pe;
                    }
                    HSD_SetupRenderModeWithCustomPE(rendermode, pe_desc);
                }
                if (new_texp == NULL) {
                    ftCo_8009F75C(fp, true);
                }
            }
            if (cur_tobj != NULL) {
                *cur_tobj = NULL;
            }
        }
    }
}

/**
 * @brief Configures TEV registers for fighter lighting overlays.
 * @param fp Fighter instance
 * @param mobj Material object
 * @param texp Texture expression struct
 * @param rendermode Render mode flags
 * @return Updated texture expression pointer, or NULL
 */
HSD_TExp* ftMaterial_800BF534(Fighter* fp, HSD_MObj* mobj, HSD_TExp* texp,
                              u32 rendermode)
{
    HSD_TevDesc sp_tevdesc;
    s32 color_reg;
    bool is_reg_free;
    struct ft_MObjInfo* info = (struct ft_MObjInfo*) &ftMObj;
    ColorOverlay* overlay = ftCo_800C0658(fp);

    if (overlay->x7C_flag2 && overlay->x7C_light_enable) {
        if (!(rendermode & RENDER_XLU) && !fp->x2223_b2) {
            texp->cnst = info->texp_tmpl;
            is_reg_free = lbGetFreeColorRegister(0, mobj, NULL);
            color_reg = is_reg_free;
            if (color_reg == -1) {
                HSD_ASSERTREPORT(240, 0, "can't find free color register!\n");
            }
            texp->cnst.reg = (u8) color_reg;
            texp->cnst.val = &overlay->x50_light_color;
            HSD_TExpSetReg(texp);

            sp_tevdesc = info->tevdesc_tmpl;
            sp_tevdesc.stage = HSD_StateAssignTev();
            sp_tevdesc.color = 2;
            sp_tevdesc.u.tevconf.clr_a = GX_CC_ZERO;
            sp_tevdesc.u.tevconf.clr_b = lb_8000CC8C(color_reg);
            sp_tevdesc.u.tevconf.clr_c = GX_CC_RASA;
            is_reg_free = false;
            sp_tevdesc.u.tevconf.clr_d = GX_CC_CPREV;
            if (color_reg < 4) {
                is_reg_free = true;
            }
            if (is_reg_free) {
                sp_tevdesc.u.tevconf.kcsel = lb_8000CCA4(color_reg);
            }
            HSD_SetupTevStage(&sp_tevdesc);
            return texp;
        }
        ftCo_8009F75C(fp, false);
    }
    return NULL;
}

/**
 * @brief Configures TEV registers for fighter coloring and opacity states (e.g. damage flash, invisible).
 * @param fp Fighter instance
 * @param mobj Material object
 * @param texp Texture expression struct
 */
void ftMaterial_800BF6BC(Fighter* fp, HSD_MObj* mobj, HSD_TExp* texp)
{
    GXColor overlay_color;
    u8 _padA[84];
    HSD_TECnst sp_cnst1;
    u8 _padB[84];
    HSD_TECnst sp_cnst2;
    HSD_TevDesc sp_tevdesc;
    GXColor color;

    s32 has_overlay;
    s32 var_r0;
    s32 free_color_reg1;
    s32 free_color_reg2;
    s32 var_r3;
    ColorOverlay* overlay;
    s32 sub_color_idx;
    struct ft_MObjInfo* info = (struct ft_MObjInfo*) &ftMObj;

    if (!fp->x2223_b3) {
        overlay = ftCo_800C0658(fp);
        has_overlay = 0;
        sub_color_idx = fp->sub_color;
        if (fp->x2228_b0 && fp->x2224_b0) {
            if (fp->is_metal) {
                sub_color_idx = 4;
            } else if (fp->x2227_b3) {
                sub_color_idx = 5;
            }
        }
        if (fp->x2223_b2) {
            has_overlay = 1;
            overlay_color = fp->x610_color_rgba[1];
        } else if (sub_color_idx != 0) {
            if (overlay->x7C_color_enable) {
                u32 temp_alpha;
                s32 inv_alpha;
                GXColor* fp_color = &fp->x610_color_rgba[0];
                GXColor* color_hex = &overlay->x2C_hex;
                s32 temp_r8;
                s32 temp_r7;

                temp_alpha =
                    ((0xFF - fp_color->a) * (0xFF - color_hex->a)) / 255;
                if ((s32) temp_alpha == 0xFF) {
                    overlay_color = overlay->x2C_hex;
                } else {
                    inv_alpha = 0xFF - temp_alpha;
                    temp_r8 = fp_color->r;
                    temp_r8 += (color_hex->a * (color_hex->r - temp_r8)) / 255;
                    temp_r7 = temp_r8 * 0xFF;
                    overlay_color.r = (u8) (temp_r7 / inv_alpha);
                    if (overlay_color.r != 0) {
                        overlay_color.a = temp_r7 / overlay_color.r;
                    } else {
                        overlay_color.a = ((inv_alpha - temp_r8) * 0xFF) / 255;
                    }
                    {
                        u8 temp_r8_3 = fp_color->g;
                        overlay_color.g =
                            ((temp_r8_3 +
                              ((color_hex->a * (color_hex->g - temp_r8_3)) /
                               255)) *
                             0xFF) /
                            inv_alpha;
                    }
                    {
                        u8 temp_r6 = fp_color->b;
                        overlay_color.b =
                            ((temp_r6 +
                              ((color_hex->a * (color_hex->b - temp_r6)) /
                               255)) *
                             0xFF) /
                            inv_alpha;
                    }
                }
                has_overlay = 1;
            } else {
                has_overlay = 1;
                overlay_color = p_ftCommonData->sub_colors[sub_color_idx - 1];
            }
        } else if (overlay->x7C_color_enable) {
            has_overlay = 1;
            overlay_color = overlay->x2C_hex;
        }
        if (has_overlay != 0) {
            sp_cnst1 = info->texp_tmpl;
            free_color_reg1 = lbGetFreeColorRegister(0, mobj, texp);
            if (free_color_reg1 == -1) {
                HSD_ASSERTREPORT(352, 0, "can't find free color register!\n");
            }
            sp_cnst1.reg = (u8) free_color_reg1;
            sp_cnst1.val = &overlay_color;
            HSD_TExpSetReg((HSD_TExp*) &sp_cnst1);
            sp_cnst1.next = texp;
            if (free_color_reg1 < 4) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }
            if (var_r0 != 0) {
                var_r3 = 4;
            } else {
                var_r3 = 0;
            }
            free_color_reg2 = lbGetFreeColorRegister(var_r3, mobj, (HSD_TExp*) &sp_cnst1);
            if (free_color_reg2 == -1) {
                HSD_ASSERTREPORT(366, 0,
                                 "can't find free color ratio register!\n");
            }
            if (fp->x61D != 0xFF) {
                sp_cnst2 = info->texp_tmpl;
                sp_cnst2.reg = (u8) free_color_reg2;
                sp_cnst2.comp = 5;
                sp_cnst2.idx = 3;
                sp_cnst2.val = &fp->x61D;
                sp_cnst1.next = (HSD_TExp*) &sp_cnst2;
            } else {
                sp_cnst1.next = NULL;
            }
            sp_cnst1.reg = (u8) free_color_reg2;
            color.r = overlay_color.a;
            color.g = overlay_color.a;
            color.b = overlay_color.a;
            sp_cnst1.val = &color;
            HSD_TExpSetReg((HSD_TExp*) &sp_cnst1);
            sp_tevdesc = info->tevdesc_tmpl;
            sp_tevdesc.stage = HSD_StateAssignTev();
            sp_tevdesc.u.tevconf.clr_b = lb_8000CC8C(free_color_reg1);
            sp_tevdesc.u.tevconf.clr_c = lb_8000CC8C(free_color_reg2);
            if (free_color_reg1 < 4) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }
            if (var_r0 != 0) {
                sp_tevdesc.u.tevconf.kcsel = lb_8000CCA4(free_color_reg1);
            } else {
                if (free_color_reg2 < 4) {
                    var_r0 = 1;
                } else {
                    var_r0 = 0;
                }
                if (var_r0 != 0) {
                    sp_tevdesc.u.tevconf.kcsel = lb_8000CCA4(free_color_reg2);
                }
            }
            if (fp->x61D != 0xFF) {
                sp_tevdesc.u.tevconf.alpha_d = lb_8000CD90(free_color_reg2);
                if (free_color_reg2 < 4) {
                    var_r0 = 1;
                } else {
                    var_r0 = 0;
                }
                if (var_r0 != 0) {
                    sp_tevdesc.u.tevconf.kasel = lb_8000CDA8(free_color_reg2);
                }
            }
            HSD_SetupTevStage(&sp_tevdesc);
        }
    }
}

/**
 * @brief Iterates through all JObjs and DObjs of the fighter and forcefully overrides their diffuse color.
 * @param gobj Fighter GObj
 * @param diffuse The diffuse color to apply
 */
void ftMaterial_800BFB4C(Fighter_GObj* gobj, GXColor* diffuse)
{
    HSD_JObj* curr_jobj = GET_JOBJ(gobj);

    while (curr_jobj != NULL) {
        HSD_DObj* curr_dobj = HSD_JObjGetDObj(curr_jobj);
        while (curr_dobj != NULL) {
            HSD_MObj* mobj = curr_dobj != NULL ? curr_dobj->mobj : NULL;
            if (mobj != NULL) {
                if (mobj->mat != NULL) {
                    HSD_Material* mat = mobj->mat;
                    mat->diffuse = *diffuse;
                }
            }
            curr_dobj = curr_dobj != NULL ? curr_dobj->next : NULL;
        }
        if (!(HSD_JObjGetFlags(curr_jobj) & JOBJ_INSTANCE)) {
            HSD_JObj* child;
            if (curr_jobj == NULL) {
                child = NULL;
            } else {
                child = curr_jobj->child;
            }
            if (child != NULL) {
                HSD_JObj* child;
                if (curr_jobj == NULL) {
                    child = NULL;
                } else {
                    child = curr_jobj->child;
                }
                curr_jobj = child;
                continue;
            }
        }
        {
            HSD_JObj* next;
            if (curr_jobj == NULL) {
                next = NULL;
            } else {
                next = curr_jobj->next;
            }
            if (next != NULL) {
                HSD_JObj* next;
                if (curr_jobj == NULL) {
                    next = NULL;
                } else {
                    next = curr_jobj->next;
                }
                curr_jobj = next;
            } else {
                while (true) {
                    HSD_JObj* parent;
                    if (curr_jobj == NULL) {
                        parent = NULL;
                    } else {
                        parent = curr_jobj->parent;
                    }
                    if (parent == NULL) {
                        curr_jobj = NULL;
                    } else {
                        HSD_JObj* parent;
                        if (curr_jobj == NULL) {
                            parent = NULL;
                        } else {
                            parent = curr_jobj->parent;
                        }
                        {
                            HSD_JObj* next;
                            if (parent == NULL) {
                                next = NULL;
                            } else {
                                next = parent->next;
                            }
                            if (next != NULL) {
                                HSD_JObj* parent;
                                if (curr_jobj == NULL) {
                                    parent = NULL;
                                } else {
                                    parent = curr_jobj->parent;
                                }
                                {
                                    HSD_JObj* next;
                                    if (parent == NULL) {
                                        next = NULL;
                                    } else {
                                        next = parent->next;
                                    }
                                    curr_jobj = next;
                                }
                            } else {
                                HSD_JObj* parent;
                                if (curr_jobj == NULL) {
                                    parent = NULL;
                                } else {
                                    parent = curr_jobj->parent;
                                }
                                curr_jobj = parent;
                                continue;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}
