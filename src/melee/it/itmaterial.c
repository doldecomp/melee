#include "itmaterial.h"

#include "ft/ftdevice.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "lb/lb_00B0.h"

#include <baselib/dobj.h>
#include <baselib/tev.h>

struct it_MObjInfo {
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
    /*  +DC */ char library_name[0xF4 - 0xDC];
    /*  +F4 */ char report_fmt_no_register[0x118 - 0xF4];
    /* +118 */ char assert_file[0x128 - 0x118];
    /* +128 */ char report_fmt_no_register_2[0x150 - 0x128];
};
void it_80277D08(void)
{
    hsdInitClassInfo(&it_803F1F90.parent, &hsdMObj.parent,
                     it_803F1F90.library_name, "it_mobj", 0x50, 0x20);
    it_803F1F90.parent.release = hsdMObj.parent.release;
    it_803F1F90.parent.amnesia = hsdMObj.parent.amnesia;
    it_803F1F90.setup = (HSD_MObjSetupFunc) (Event) fn_80277D8C;
    it_803F1F90.load = hsdMObj.load;
    it_803F1F90.make_texp = hsdMObj.make_texp;
}

void fn_80277D8C(HSD_MObj* mobj, u32 rendermode_arg, u32 unused_arg)
{
    HSD_TObj* tobj2;
    HSD_TExp sp38;
    HSD_PEDesc pe_desc;
    Item* item = GET_ITEM(HSD_GObj_804D7814);
    HSD_PEDesc* setup_render_arg;
    HSD_TObj** tobj1_ptr;
    u32 rendermode;

    HSD_StateInitTev();
    rendermode = mobj->rendermode;
    HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                         mobj->mat->specular, mobj->mat->alpha);
    if (rendermode & 8) {
        HSD_SetMaterialShininess(mobj->mat->shininess);
    }
    tobj1_ptr = NULL;
    tobj2 = mobj->tobj;
    if ((rendermode & 0x04000000) && tobj_shadows) {
        tobj1_ptr = &tobj2;
        while (*tobj1_ptr != NULL) {
            tobj1_ptr = &(*tobj1_ptr)->next;
        }
        *tobj1_ptr = tobj_shadows;
    }
    if ((rendermode & 0x1000) && (tobj_toon != NULL) &&
        (tobj_toon->imagedesc != NULL))
    {
        tobj_toon->next = tobj2;
        tobj2 = tobj_toon;
    }
    HSD_TObjSetup(tobj2);
    HSD_TObjSetupTextureCoordGen(tobj2);
    HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj2, rendermode);
    it_80278108(item, mobj, it_80277F90(item, mobj, &sp38));
    if (item->x5C9 != 0xFF) {
        rendermode |= 0x60000000;
    }
    if (item->xDCF_flag.b4 && !item->xDCF_flag.b5) {
        rendermode |= 0x20000000;
    }
    if (item->xDCF_flag.b5 && (item->x5C9 == 0xFF)) {
        pe_desc.flags = 0x38;
        pe_desc.dst_alpha = 0;
        pe_desc.type = 0;
        pe_desc.src_factor = 4;
        setup_render_arg = &pe_desc;
        pe_desc.dst_factor = 5;
        pe_desc.logic_op = 0xF;
        pe_desc.z_comp = 3;
        pe_desc.alpha_comp0 = 7;
        pe_desc.ref0 = 0;
        pe_desc.alpha_op = 0;
        pe_desc.alpha_comp1 = 7;
        pe_desc.ref1 = 0;
    } else {
        setup_render_arg = mobj->pe;
    }
    HSD_SetupRenderModeWithCustomPE(rendermode, setup_render_arg);
    if (tobj1_ptr != NULL) {
        *tobj1_ptr = NULL;
    }
}

HSD_TExp* it_80277F90(Item* item, HSD_MObj* mobj, HSD_TExp* arg2)
{
    HSD_TevDesc sp14;
    struct it_MObjInfo* info = &it_803F1F90;
    s32 reg;
    int chk;

    if (!item->xDCF_flag.b4 && item->x548_colorOverlay.x7C_flag2 &&
        item->x548_colorOverlay.x7C_light_enable)
    {
        arg2->cnst = info->texp_tmpl;
        reg = lbGetFreeColorRegister(0, mobj, NULL);
        if (reg == -1) {
            OSReport(info->report_fmt_no_register);
            __assert(info->assert_file, 0xDD, "0");
        }
        arg2->cnst.reg = reg;
        arg2->cnst.val = &item->x548_colorOverlay.x50_light_color;
        HSD_TExpSetReg(arg2);
        sp14 = info->tevdesc_tmpl;
        sp14.stage = HSD_StateAssignTev();
        sp14.color = 2;
        sp14.u.tevconf.clr_a = GX_CC_ZERO;
        sp14.u.tevconf.clr_b = lb_8000CC8C(reg);
        sp14.u.tevconf.clr_c = GX_CC_RASA;
        sp14.u.tevconf.clr_d = chk = 0;
        if (reg < 4) {
            chk = 1;
        }
        if (chk) {
            sp14.u.tevconf.kcsel = lb_8000CCA4(reg);
        }
        HSD_SetupTevStage(&sp14);
        return arg2;
    }
    return NULL;
}

void it_80278108(Item* item, HSD_MObj* mobj, HSD_TExp* texp)
{
    GXColor sp168;
    u8 _padA[84];
    HSD_TECnst spFC;
    u8 _padB[80];
    GXColor unused;
    HSD_TECnst sp90;
    HSD_TevDesc sp1C;
    bool chk1;
    s32 var_r0;
    s32 reg1;
    s32 reg2;
    s32 var_r3;
    ColorOverlay* overlay;
    struct it_MObjInfo* info = &it_803F1F90;

    if (item->xDCF_flag.b5) {
        return;
    }
    overlay = &item->x548_colorOverlay;
    chk1 = false;
    if (item->xDCF_flag.b3) {
        if (item->owner != NULL && item->xDC8_word.flags.x13) {
            overlay = ftCo_800C0674(item->owner);
        }
    }
    if (item->xDCF_flag.b4) {
        chk1 = true;
        sp168 = item->xBC8.x0_unk;
    } else if (item->x5C8) {
        if (overlay->x7C_color_enable) {
            u32 temp_alpha;
            s32 inv_alpha;
            GXColor* item_color = &item->xBC4;
            GXColor* color_hex = &overlay->x2C_hex;
            s32 temp_r8;
            s32 temp_r7;
            s32 temp_r4;

            temp_alpha =
                ((0xFF - item_color->a) * (0xFF - color_hex->a)) / 255;
            if ((s32) temp_alpha == 0xFF) {
                sp168 = overlay->x2C_hex;
            } else {
                inv_alpha = 0xFF - temp_alpha;
                temp_r8 = item_color->r;
                temp_r8 += (color_hex->a * (color_hex->r - temp_r8)) / 255;
                temp_r7 = temp_r8 * 0xFF;
                temp_r4 = temp_r7 / inv_alpha;
                sp168.r = temp_r4;
                if (sp168.r != 0) {
                    sp168.a = temp_r7 / sp168.r;
                } else {
                    sp168.a = ((inv_alpha - temp_r8) * 0xFF) / 255;
                }
                {
                    u8 temp_r8_3 = item_color->g;
                    sp168.g = ((temp_r8_3 +
                                ((color_hex->a * (color_hex->g - temp_r8_3)) /
                                 255)) *
                               0xFF) /
                              inv_alpha;
                }
                {
                    u8 temp_r6 = item_color->b;
                    sp168.b =
                        ((temp_r6 +
                          ((color_hex->a * (color_hex->b - temp_r6)) / 255)) *
                         0xFF) /
                        inv_alpha;
                }
            }
            chk1 = true;
        } else {
            chk1 = true;
            sp168 = item->xBC4;
        }
    } else if (overlay->x7C_color_enable) {
        chk1 = true;
        sp168 = overlay->x2C_hex;
    }
    if (chk1) {
        spFC = info->texp_tmpl;
        reg1 = lbGetFreeColorRegister(0, mobj, texp);
        if (reg1 == -1) {
            OSReport(info->report_fmt_no_register);
            __assert(info->assert_file, 0x144, "0");
        }
        spFC.reg = reg1;
        spFC.val = &sp168;
        HSD_TExpSetReg((HSD_TExp*) &spFC);
        spFC.next = texp;
        if (reg1 < 4) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            var_r3 = 4;
        } else {
            var_r3 = 0;
        }
        reg2 = lbGetFreeColorRegister(var_r3, mobj, (HSD_TExp*) &spFC);
        if (reg2 == -1) {
            OSReport(info->report_fmt_no_register_2);
            __assert(info->assert_file, 0x152, "0");
        }
        if (item->x5C9 != 0xFF) {
            sp90 = info->texp_tmpl;
            sp90.reg = reg2;
            sp90.comp = 5;
            sp90.idx = 3;
            sp90.val = &item->x5C9;
            spFC.next = (HSD_TExp*) &sp90;
        } else {
            spFC.next = NULL;
        }
        spFC.reg = reg2;
        {
            GXColor* color = (GXColor*) ((u8*) &sp1C - 4);
            u8 alpha = sp168.a;

            color->r = alpha;
            color->g = alpha;
            color->b = alpha;
            spFC.val = color;
        }
        HSD_TExpSetReg((HSD_TExp*) &spFC);
        sp1C = info->tevdesc_tmpl;
        sp1C.stage = HSD_StateAssignTev();
        sp1C.u.tevconf.clr_b = lb_8000CC8C(reg1);
        sp1C.u.tevconf.clr_c = lb_8000CC8C(reg2);
        if (reg1 < 4) {
            var_r0 = 1;
        } else {
            var_r0 = 0;
        }
        if (var_r0 != 0) {
            sp1C.u.tevconf.kcsel = lb_8000CCA4(reg1);
        } else {
            if (reg2 < 4) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }
            if (var_r0 != 0) {
                sp1C.u.tevconf.kcsel = lb_8000CCA4(reg2);
            }
        }
        if (item->x5C9 != 0xFF) {
            sp1C.u.tevconf.alpha_d = lb_8000CD90(reg2);
            if (reg2 < 4) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }
            if (var_r0 != 0) {
                sp1C.u.tevconf.kasel = lb_8000CDA8(reg2);
            }
        }
        HSD_SetupTevStage(&sp1C);
    }
}

void it_80278574(HSD_GObj* gobj, GXColor* arg1)
{
    HSD_DObj* var_r3;
    HSD_JObj* var_r0;
    HSD_JObj* var_r0_2;
    HSD_JObj* var_r0_3;
    HSD_JObj* var_r0_4;
    HSD_JObj* var_r0_5;
    HSD_JObj* var_r0_6;
    HSD_JObj* var_r0_7;
    HSD_JObj* var_r0_8;
    HSD_JObj* var_r31;
    HSD_JObj* var_r3_2;
    HSD_JObj* var_r3_3;
    HSD_MObj* temp_r4;
    HSD_Material* temp_r4_2;
    PAD_STACK(4);

    // var_r31 = GET_JOBJ(gobj->hsd_obj);
    var_r31 = gobj->hsd_obj;
    while (var_r31 != NULL) {
        var_r3 = HSD_JObjGetDObj(var_r31);
        while (var_r3 != NULL) {
            temp_r4 = var_r3->mobj;
            if (temp_r4 != NULL) {
                temp_r4_2 = temp_r4->mat;
                if (temp_r4_2 != NULL) {
                    temp_r4_2->diffuse = *arg1;
                }
            }
            if (var_r3 != NULL) {
                var_r3 = var_r3->next;
            } else {
                var_r3 = NULL;
            }
        }
        if (var_r31 == NULL) {
            var_r0 = NULL;
        } else {
            var_r0 = var_r31->child;
        }
        if (var_r0 != NULL) {
            if (var_r31 == NULL) {
                var_r0_2 = NULL;
            } else {
                var_r0_2 = var_r31->child;
            }
            var_r31 = var_r0_2;
        } else {
            if (var_r31 == NULL) {
                var_r0_3 = NULL;
            } else {
                var_r0_3 = var_r31->next;
            }
            if (var_r0_3 != NULL) {
                if (var_r31 == NULL) {
                    var_r0_4 = NULL;
                } else {
                    var_r0_4 = var_r31->next;
                }
                var_r31 = var_r0_4;
            } else {
            loop_25:
                if (var_r31 == NULL) {
                    var_r0_5 = NULL;
                } else {
                    var_r0_5 = var_r31->parent;
                }
                if (var_r0_5 == NULL) {
                    var_r31 = NULL;
                } else {
                    if (var_r31 == NULL) {
                        var_r3_2 = NULL;
                    } else {
                        var_r3_2 = var_r31->parent;
                    }
                    if (var_r3_2 == NULL) {
                        var_r0_6 = NULL;
                    } else {
                        var_r0_6 = var_r3_2->next;
                    }
                    if (var_r0_6 != NULL) {
                        if (var_r31 == NULL) {
                            var_r3_3 = NULL;
                        } else {
                            var_r3_3 = var_r31->parent;
                        }
                        if (var_r3_3 == NULL) {
                            var_r0_7 = NULL;
                        } else {
                            var_r0_7 = var_r3_3->next;
                        }
                        var_r31 = var_r0_7;
                    } else {
                        if (var_r31 == NULL) {
                            var_r0_8 = NULL;
                        } else {
                            var_r0_8 = var_r31->parent;
                        }
                        var_r31 = var_r0_8;
                        goto loop_25;
                    }
                }
            }
        }
    }
}

struct it_MObjInfo it_803F1F90 = {
    { { it_80277D08 } },
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
                GX_TEV_ADD,
                GX_CC_CPREV,
                GX_CC_ZERO,
                GX_CC_ZERO,
                GX_CC_ZERO,
                GX_CS_SCALE_1,
                GX_TB_ZERO,
                1,
                GX_TEVPREV,
                GX_TEV_ADD,
                GX_CA_ZERO,
                GX_CA_ZERO,
                GX_CA_ZERO,
                GX_CA_APREV,
                GX_CS_SCALE_1,
                GX_TB_ZERO,
                0,
                GX_TEVPREV,
                GX_TC_LINEAR,
                GX_TEV_SWAP0,
                GX_TEV_SWAP0,
                GX_TEV_KCSEL_1,
                GX_TEV_KASEL_1,
            },
        },
    },
    { HSD_TE_CNST, NULL, NULL, HSD_TE_RGB, HSD_TE_U8, 0xFF, 0xFF },
    "sysdolphin_base_library",
    "can\'t find free color register!\n",
    "itmaterial.c",
    "can\'t find free color ratio register!\n",
};
