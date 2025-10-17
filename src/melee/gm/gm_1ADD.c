#include "gm_1ADD.h"

#include "gm_unsplit.h"

#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lblanguage.h>
#include <melee/sc/types.h>

static struct unkd4d0 {
    struct unkd4d0* next;
    struct unkd4d0* unk4;
    struct unkd4d0_8 {
        struct unkd4d0_8* next;
        struct unkd4d0_8* unk4;
        int unk8;
        int unkC;
        float unk10;
        float unk14;
        u8 pad18[0x8];
        HSD_GObj* unk20;
        HSD_Text* unk24;
    }* unk8;
    int unkC;
    int unk10;
    float unk14;
    float unk18;
    HSD_GObj* unk1C;
    HSD_Text* unk20;
} gm_803DD4D0 = { 0 };

static SceneDesc* gm_804D6868;
static int gm_804D686C;

void gm_801ADDD8(void)
{
    memzero(&gm_803DD4D0, sizeof(gm_803DD4D0));
    gm_803DD4D0.unkC = -0x3E7;
    gm_801AEBB0();
}

bool gm_801ADE1C(int arg0, int arg1, f32 arg2, f32 arg3)
{
    HSD_Text* text;
    struct unkd4d0* temp_r0;
    struct unkd4d0* next;
    struct unkd4d0* cur;

    cur = &gm_803DD4D0;
    next = HSD_MemAlloc(sizeof(struct unkd4d0));
    memzero(next, sizeof(struct unkd4d0));
    next->unkC = arg0;
    next->unk10 = arg1;
    next->unk14 = arg2;
    next->unk18 = arg3;

    for (; true; cur = cur->next) {
        if (cur->next != NULL) {
            continue;
        }

        cur->next = next;
        next->unk4 = cur;
        next->next = NULL;
        next->unk8 = NULL;
        next->unk1C = gm_801AECC4(1);
        if (next->unk1C != NULL) {
            HSD_JObjSetTranslateX(GET_JOBJ(next->unk1C), next->unk14);
        }
        if (next->unk1C != NULL) {
            HSD_JObjSetTranslateY(GET_JOBJ(next->unk1C), next->unk18);
        }
        next->unk20 =
            HSD_SisLib_803A5ACC(3, gm_804D686C, -14.0F + next->unk14,
                                -9.0F - next->unk18, 0.0F, 30.8F, 4.6F);
        text = next->unk20;
        text->x34.x = 0.079F;
        text->x34.y = 0.079F;
        next->unk20->default_alignment = 0;
        next->unk20->default_fitting = 0;
        HSD_SisLib_803A6368(next->unk20, next->unk10);
        break;
    }

    return true;
}

int gm_801AE050(int arg0, int arg1, int arg2, float arg3, float arg4)
{
    HSD_GObj* temp_r3_3;
    HSD_Text* temp_r3_4;
    HSD_Text* temp_r3_7;
    struct unkd4d0* var_r31;
    struct unkd4d0_8* temp_r0;
    struct unkd4d0_8* temp_r0_2;
    struct unkd4d0_8* temp_r3;
    struct unkd4d0_8* var_r4;
    PAD_STACK(0x10);

    var_r31 = gm_803DD4D0.next;
    temp_r3 = HSD_MemAlloc(sizeof(*temp_r3));
    memzero(temp_r3, sizeof(*temp_r3));
    temp_r3->unk8 = arg1;
    temp_r3->unkC = arg2;
    temp_r3->unk10 = arg3;
    temp_r3->unk14 = arg4;
    for (; var_r31 != NULL; var_r31 = var_r31->next) {
        if (var_r31->unkC == arg0) {
            var_r4 = var_r31->unk8;
            if (var_r4 == NULL) {
                var_r31->unk8 = temp_r3;
                temp_r3->next = NULL;
                temp_r3->unk4 = NULL;
                temp_r3->unk20 = gm_801AECC4(0);
                if (temp_r3->unk20 != NULL) {
                    HSD_JObjSetTranslateX(GET_JOBJ(temp_r3->unk20),
                                          temp_r3->unk10);
                }
                temp_r3_3 = temp_r3->unk20;
                if (temp_r3_3 != NULL) {
                    HSD_JObjSetTranslateY(GET_JOBJ(temp_r3_3), temp_r3->unk14);
                }
                temp_r3->unk24 = HSD_SisLib_803A5ACC(
                    3, gm_804D686C, 2.2F * temp_r3->unk10 - 1.0F,
                    2.232143F * -temp_r3->unk14 - 1.3F, 0.0F, 2.0F, 2.0F);
                temp_r3_4 = temp_r3->unk24;
                temp_r3_4->x34.x = 0.1F;
                temp_r3_4->x34.y = 0.1F;
                temp_r3->unk24->default_alignment = 1;
                temp_r3->unk24->default_fitting = 0;
                HSD_SisLib_803A6368(temp_r3->unk24, temp_r3->unkC);
                continue;
            }
            for (; true; var_r4 = var_r4->next) {
                if (var_r4->next != NULL) {
                    continue;
                }
                var_r4->next = temp_r3;
                temp_r3->next = NULL;
                temp_r3->unk4 = var_r4;
                temp_r3->unk20 = gm_801AECC4(0);
                if (temp_r3->unk20 != NULL) {
                    HSD_JObjSetTranslateX(GET_JOBJ(temp_r3->unk20),
                                          temp_r3->unk10);
                }
                if (temp_r3->unk20 != NULL) {
                    HSD_JObjSetTranslateY(GET_JOBJ(temp_r3->unk20),
                                          temp_r3->unk14);
                }
                temp_r3->unk24 = HSD_SisLib_803A5ACC(
                    3, gm_804D686C, 2.2F * temp_r3->unk10 - 1.0F,
                    2.232143F * -temp_r3->unk14 - 1.3F, 0.0F, 2.0F, 2.0F);
                temp_r3_7 = temp_r3->unk24;
                temp_r3_7->x34.x = 0.1F;
                temp_r3_7->x34.y = 0.1F;
                temp_r3->unk24->default_alignment = 1;
                temp_r3->unk24->default_fitting = 0;
                HSD_SisLib_803A6368(temp_r3->unk24, temp_r3->unkC);
                break;
            }
        }
    }
    return true;
}

void gm_801AE44C(int arg0, float val)
{
    struct unkd4d0* cur;

    for (cur = gm_803DD4D0.next; cur != NULL; cur = cur->next) {
        if (cur->unkC == arg0) {
            HSD_JObj* jobj = GET_JOBJ(cur->unk1C);
            HSD_JObjAddTranslationY(jobj->child->child->child->next, -val);
        }
    }
}

void gm_801AE544(int arg0, float val)
{
    struct unkd4d0* cur;

    for (cur = gm_803DD4D0.next; cur != NULL; cur = cur->next) {
        if (cur->unkC == arg0) {
            HSD_JObj* jobj = GET_JOBJ(cur->unk1C);
            HSD_JObjAddTranslationY(jobj->child->child->child->next->child,
                                    -val);
        }
    }
}

void gm_801AE640(int arg0, int arg1)
{
    struct unkd4d0* var_r31;
    struct unkd4d0_8* var_r30;
    HSD_JObj* temp_r6;

    var_r31 = gm_803DD4D0.next;
    while (var_r31 != NULL) {
        var_r30 = var_r31->unk8;
        while (var_r30 != NULL) {
            if (var_r30->unk8 == arg1) {
                if (var_r30->unk20 != NULL) {
                    temp_r6 = GET_JOBJ(var_r30->unk20);
                    temp_r6->child->child->u.dobj->mobj->mat->diffuse.r = 0xFF;
                    temp_r6->child->child->u.dobj->mobj->mat->diffuse.g = 0xCC;
                    temp_r6->child->child->u.dobj->mobj->mat->diffuse.b = 0x33;
                }
                if (var_r30->unk24 != NULL) {
                    var_r30->unk24->text_color.r = 0xFF;
                    var_r30->unk24->text_color.g = 0xCC;
                    var_r30->unk24->text_color.b = 0x33;
                    HSD_SisLib_803A6368(var_r30->unk24, var_r30->unkC);
                }
            }
            var_r30 = var_r30->next;
        }
        var_r31 = var_r31->next;
    }
}

void gm_801AE74C(int arg0, int arg1)
{
    struct unkd4d0* var_r31;
    struct unkd4d0_8* var_r30;
    HSD_JObj* temp_r4;

    var_r31 = gm_803DD4D0.next;
    while (var_r31 != NULL) {
        var_r30 = var_r31->unk8;
        while (var_r30 != NULL) {
            if (var_r30->unk8 == arg1) {
                if (var_r30->unk20 != NULL) {
                    temp_r4 = GET_JOBJ(var_r30->unk20);
                    temp_r4->child->child->u.dobj->mobj->mat->diffuse.r = 0x66;
                    temp_r4->child->child->u.dobj->mobj->mat->diffuse.g = 0x66;
                    temp_r4->child->child->u.dobj->mobj->mat->diffuse.b = 0x66;
                }
                if (var_r30->unk24 != NULL) {
                    var_r30->unk24->text_color.r = 0x66;
                    var_r30->unk24->text_color.g = 0x66;
                    var_r30->unk24->text_color.b = 0x66;
                    HSD_SisLib_803A6368(var_r30->unk24, var_r30->unkC);
                }
            }
            var_r30 = var_r30->next;
        }
        var_r31 = var_r31->next;
    }
}

void gm_801AE848(int arg0)
{
    struct unkd4d0* var_r31;
    struct unkd4d0* temp_r30;
    struct unkd4d0_8* var_r30;
    struct unkd4d0_8* temp_r29;

    var_r31 = gm_803DD4D0.next;
    while (var_r31 != NULL) {
        if (var_r31->unkC == arg0) {
            var_r30 = var_r31->unk8;
            while (var_r30 != NULL) {
                temp_r29 = var_r30;
                var_r30 = var_r30->next;
                if (temp_r29->unk20 != NULL) {
                    HSD_GObjPLink_80390228(temp_r29->unk20);
                }
                if (temp_r29->unk24 != NULL) {
                    HSD_SisLib_803A5CC4(temp_r29->unk24);
                }
                HSD_Free(temp_r29);
            }
            if (var_r31->unk4 != NULL) {
                var_r31->unk4->next = var_r31->next;
            }
            if (var_r31->next != NULL) {
                var_r31->next->unk4 = var_r31->unk4;
            }
            temp_r30 = var_r31;
            var_r31 = var_r31->next;
            if (temp_r30->unk1C != NULL) {
                HSD_GObjPLink_80390228(temp_r30->unk1C);
            }
            if (temp_r30->unk20 != NULL) {
                HSD_SisLib_803A5CC4(temp_r30->unk20);
            }
            HSD_Free(temp_r30);
        } else {
            var_r31 = var_r31->next;
        }
    }
}

void fn_801AE948(HSD_GObj* arg0)
{
    struct unkd4d0* var_r31;
    struct unkd4d0_8* var_r30;

    var_r31 = gm_803DD4D0.next;
    while (var_r31 != NULL) {
        var_r30 = var_r31->unk8;
        if (var_r31->unk1C != NULL) {
            HSD_JObjSetTranslateX(GET_JOBJ(var_r31->unk1C), var_r31->unk14);
            HSD_JObjSetTranslateY(GET_JOBJ(var_r31->unk1C), var_r31->unk18);
        }
        while (var_r30 != NULL) {
            if (var_r30->unk20 != NULL) {
                HSD_JObjSetTranslateX(GET_JOBJ(var_r30->unk20),
                                      var_r30->unk10);
                HSD_JObjSetTranslateY(GET_JOBJ(var_r30->unk20),
                                      var_r30->unk14);
            }
            var_r30 = var_r30->next;
        }
        var_r31 = var_r31->next;
    }
}

void gm_801AEBB0(void)
{
    HSD_GObj* gobj;
    PAD_STACK(4);

    lbArchive_80016DBC("NtMsgWin.dat", &gm_804D6868, "ScNtcCommon_scene_data",
                       0);

    if (lbLang_IsSavedLanguageUS()) {
        HSD_SisLib_803A62A0(3, "SdMsgBox.usd", "SIS_MessageData");
    } else {
        HSD_SisLib_803A62A0(3, "SdMsgBox.dat", "SIS_MessageData");
    }

    gobj = GObj_Create(20, 21, 0);
    {
        HSD_CObj* desc = HSD_CObjLoadDesc(gm_804D6868->cameras[0].desc);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, desc);
    }
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 0);
    gobj->gxlink_prios = 0x4000;

    gm_804D686C = HSD_SisLib_803A611C(3, gobj, 9, 13, 0, 14, 0, 18);
    HSD_GObjProc_8038FD54(GObj_Create(15, 17, 0), fn_801AE948, 0);
}

HSD_GObj* gm_801AECC4(int model_idx)
{
    HSD_GObj* gobj = GObj_Create(9, 13, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(gm_804D6868->models[model_idx]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 14, 0);
    gm_8016895C(jobj, gm_804D6868->models[model_idx], 0);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    if (model_idx == 1) {
        HSD_JObjSetFlagsAll(jobj->child->child->next->child->next,
                            JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(jobj->child->child->next->next, JOBJ_HIDDEN);
    }
    return gobj;
}

static inline HSD_PadStatus* get_master_status(u8 i)
{
    return &HSD_PadMasterStatus[i];
}

static inline HSD_PadStatus* get_copy_status(u8 i)
{
    return &HSD_PadCopyStatus[i];
}

u32 gm_801AEDC8(void)
{
    u32 result = 0;
    int i;
    for (i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        if (get_master_status(i)->err == 0) {
            result |= get_copy_status(i)->trigger;
        }
    }
    return result;
}
