#include "tyfigupon.h"

#include "inlines.h"
#include "toy.h"
#include "types.h"

#include "if/types.h"
#include "lb/lbaudio_ax.h"

#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/random.h>

void tyFigupon_80314AA8(HSD_JObj* jobj, char* anim_str, char* matanim_str,
                        char* shapeanim_str)
{
    HSD_AnimJoint* ajoint;
    HSD_MatAnimJoint* majoint;
    HSD_ShapeAnimJoint* sajoint;
    struct un_804D6EF4_t* data = un_804D6EF4;
    PAD_STACK(16);

    if (anim_str != NULL) {
        ajoint = HSD_ArchiveGetPublicAddress(data->archive, anim_str);
    } else {
        ajoint = NULL;
    }
    if (matanim_str != NULL) {
        majoint = HSD_ArchiveGetPublicAddress(data->archive, matanim_str);
    } else {
        majoint = NULL;
    }
    if (shapeanim_str != NULL) {
        sajoint = HSD_ArchiveGetPublicAddress(data->archive, shapeanim_str);
    } else {
        sajoint = NULL;
    }
    HSD_JObjAddAnimAll(jobj, ajoint, majoint, sajoint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
}

/// #un_80314B54

void tyFigupon_80314BE4(HSD_GObj* gobj, int unused)
{
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_SetEraseColor(0x19, 0x19, 0x33, 0xFF);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(NULL);
        HSD_CObjEndCurrent();
    }
}

void tyFigupon_80314C5C(HSD_GObj* gobj)
{
    Toy* tp1 = GET_TOY(gobj);
    struct un_804D6EF4_t* temp_r29 = un_804D6EF4;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(0x38);
    if (tp1 != NULL) {
        if (tp1->x8 % 30 == 0) {
            HSD_JObjReqAnimAll(jobj, 0.0f);
        }
        HSD_JObjAnimAll(jobj);
        if (--tp1->x8 != 0) {
            tp1->translate.y += tp1->offset.y;
            if (jobj->translate.x > HSD_JObjGetTranslationX(temp_r29->x18)) {
                HSD_JObjAddTranslationX(jobj, tp1->translate.x);
            }
            if (jobj->translate.z > HSD_JObjGetTranslationZ(temp_r29->x18)) {
                HSD_JObjAddTranslationZ(jobj, tp1->translate.z);
            }
            HSD_JObjAddTranslationY(jobj, tp1->translate.y);
        } else {
            lbAudioAx_800237A8(146, 127, 64);
            tp1->x8 = 0;
            HSD_GObjPLink_80390228(gobj);
        }
    } else {
        Toy* tp = HSD_MemAlloc(sizeof(Toy));
        if (tp != NULL) {
            GObj_InitUserData(gobj, 0, Toy_RemoveUserData, tp);
        }
        HSD_JObjReqAnimAll(jobj, HSD_Randi(15));
        HSD_AObjSetRate(jobj->child->aobj, 1.0f);
        {
            float temp_f30 = HSD_JObjGetTranslationX(temp_r29->x14);
            float temp_f29_6 = HSD_JObjGetTranslationY(temp_r29->x14);
            float temp_f31 = HSD_JObjGetTranslationZ(temp_r29->x14);
            float temp_f28 = HSD_JObjGetTranslationX(temp_r29->x18);
            float temp_f27 = HSD_JObjGetTranslationY(temp_r29->x18);
            float temp_f26 = HSD_JObjGetTranslationZ(temp_r29->x18);
            float temp_f30_2 = (3.0f * HSD_Randf()) + temp_f30;
            float var_f3 = temp_f28 - temp_f30_2;
            float temp_f29_7 = (3.0f * HSD_Randf()) + temp_f29_6;
            float var_f3_2;
            float var_f2;
            {
                if (var_f3 < 0.0f) {
                    var_f3 = -var_f3;
                }
                var_f2 = temp_f26 - temp_f31;
                tp->translate.x = -0.74f * (var_f3 / 30.0f);
                if (var_f2 < 0.0f) {
                    var_f2 = -var_f2;
                }
                var_f3_2 = temp_f27 - temp_f29_7;
            }
            tp->translate.z = -0.72f * (var_f2 / 30.0f);
            tp->translate.y = 0.4f;
            tp->offset.y = -0.026666667f;
            if (var_f3_2 < 0.0f) {
                var_f3_2 = -var_f3_2;
            }
            tp->x8 = 35.0f + var_f3_2;
            temp_r29->x56 = tp->x8;
            HSD_JObjSetTranslateX(jobj, temp_f30_2);
            HSD_JObjSetTranslateY(jobj, temp_f29_7);
            HSD_JObjSetTranslateZ(jobj, temp_f31);
        }
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        lbAudioAx_80023870(147, 127, 64, 26);
    }
}

/// #fn_803152BC

/// #un_803153EC

/// #fn_80315574

/// #fn_803155C8

/// #fn_80315C44

/// #fn_80316170

/// #fn_8031638C

/// #un_80316420

/// #fn_803168DC

void tyFigupon_80316BF8(void)
{
    lbAudioAx_80023F28(0x35);
    HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
}

/// #fn_80316C24

/// #un_8031753C

/// #un_80317A60

/// #un_80317D80_OnEnter

/// #un_803181BC
