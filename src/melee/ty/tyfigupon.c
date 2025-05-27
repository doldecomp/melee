#include <placeholder.h>

#include "tyfigupon.h"

#include "inlines.h"
#include "toy.h"
#include "types.h"

#include "baselib/gobj.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjuserdata.h"
#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"
#include "lb/lbaudio_ax.h"
#include "un/types.h"
#include "un/un_2FC9.h"

/// #un_80314AA8

/// #un_80314B54

/// #fn_80314BE4

void un_80314C5C(HSD_GObj* gobj)
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

/// #fn_80316BF8

/// #fn_80316C24

/// #un_8031753C

/// #un_80317A60

/// #un_80317D80

/// #un_803181BC
