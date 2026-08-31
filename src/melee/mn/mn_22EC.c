#include "mnmain.h"

#include "dolphin/pad.h"
#include "mn/types.h"

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/tobj.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/mn/mncharsel.h>

float mn_8022EC18(HSD_JObj* arg0, AnimLoopSettings* arg1, HSD_TypeMask arg2)
{
    float temp_f1;
    float var_f31;

    temp_f1 = mn_8022F298(arg0);
    if (!(arg1->start_frame <= temp_f1) || !(temp_f1 <= arg1->end_frame)) {
        HSD_JObjReqAnimAll(arg0, *(volatile float*) &arg1->start_frame);
        mn_8022F3D8(arg0, 0xFFU, arg2);
    }
    if (arg1->loop_frame == -0.1f) {
        var_f31 = mn_8022F298(arg0);
        if (var_f31 < arg1->end_frame) {
            HSD_JObjAnimAll(arg0);
            var_f31 = mn_8022F298(arg0);
            if (var_f31 > arg1->end_frame) {
                var_f31 = arg1->end_frame;
                HSD_JObjReqAnimAll(arg0, var_f31);
                mn_8022F3D8(arg0, 0xFFU, arg2);
                HSD_JObjAnimAll(arg0);
            }
        }
    } else {
        HSD_JObjAnimAll(arg0);
        var_f31 = mn_8022F298(arg0);
        if (var_f31 >= arg1->end_frame) {
            var_f31 = arg1->loop_frame + (var_f31 - arg1->end_frame);
            HSD_JObjReqAnimAll(arg0, var_f31);
            mn_8022F3D8(arg0, 0xFFU, arg2);
            HSD_JObjAnimAll(arg0);
        }
    }
    return var_f31;
}

/// @brief updates a jobjs animation in accordance to the passed in anim loop
/// setting
/// @param jobj HSD_JObj*
/// @param anim_loop AnimLoopSettings*
/// @return the current frame of the jobjs animation
float mn_8022ED6C(HSD_JObj* jobj, AnimLoopSettings* anim_loop)
{
    float end_frame;
    float cur_frame;

    cur_frame = mn_8022F298(jobj);
    if (!(anim_loop->start_frame <= cur_frame &&
          cur_frame <= anim_loop->end_frame))
    {
        HSD_JObjReqAnimAll(jobj, *(volatile f32*) &anim_loop->start_frame);
    }
    if (anim_loop->loop_frame == -0.1f) {
        cur_frame = mn_8022F298(jobj);
        end_frame = anim_loop->end_frame;
        if (cur_frame < end_frame) {
            HSD_JObjAnimAll(jobj);
            cur_frame = mn_8022F298(jobj);
            end_frame = anim_loop->end_frame;
            if (cur_frame > end_frame) {
                cur_frame = end_frame;
                HSD_JObjReqAnimAll(jobj, cur_frame);
                HSD_JObjAnimAll(jobj);
            }
        }
    } else {
        HSD_JObjAnimAll(jobj);
        cur_frame = mn_8022F298(jobj);
        end_frame = anim_loop->end_frame;
        if (cur_frame >= end_frame) {
            cur_frame = anim_loop->loop_frame + (cur_frame - end_frame);
            HSD_JObjReqAnimAll(jobj, cur_frame);
            HSD_JObjAnimAll(jobj);
        }
    }
    return cur_frame;
}

float mn_8022EE84(HSD_JObj* arg0, AnimLoopSettings* arg1,
                  enum _HSD_TypeMask arg2)
{
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;
    f32 var_f31;

    temp_f1 = mn_8022F298(arg0);
    if (!(arg1->start_frame <= temp_f1) || !(temp_f1 <= arg1->end_frame)) {
        HSD_JObjReqAnim(arg0, *(volatile float*) &arg1->start_frame);
        mn_8022F3D8(arg0, 0xFF, arg2);
    }
    if (arg1->loop_frame == -0.1f) {
        var_f31 = mn_8022F298(arg0);
        if (arg1->end_frame != var_f31) {
            HSD_JObjAnim(arg0);
            var_f31 = mn_8022F298(arg0);
            temp_f0 = arg1->end_frame;
            if (var_f31 > temp_f0) {
                var_f31 = temp_f0;
                HSD_JObjReqAnim(arg0, var_f31);
                mn_8022F3D8(arg0, 0xFFU, arg2);
                HSD_JObjAnim(arg0);
            }
        }
    } else {
        HSD_JObjAnim(arg0);
        var_f31 = mn_8022F298(arg0);
        temp_f0_2 = arg1->end_frame;
        if (var_f31 >= temp_f0_2) {
            var_f31 = arg1->loop_frame + (var_f31 - temp_f0_2);
            HSD_JObjReqAnim(arg0, var_f31);
            mn_8022F3D8(arg0, 0xFFU, arg2);
            HSD_JObjAnim(arg0);
        }
    }
    return var_f31;
}

/// @brief updates a jobjs looping animation.
/// if the end frame is -0.1f, the animation will stop after reaching the end
/// frame.
/// @param arg0 HSD_JObj
/// @param arg1 AnimLoopSettings
float mn_8022EFD8(HSD_JObj* arg0, AnimLoopSettings* arg1)
{
    float temp_f0_2;
    float temp_f1;
    float var_f31;

    temp_f1 = mn_8022F298(arg0);
    if (!(arg1->start_frame <= temp_f1) || !(temp_f1 <= arg1->end_frame)) {
        HSD_JObjReqAnim(arg0, *(volatile float*) &arg1->start_frame);
    }
    if (arg1->loop_frame == -0.1f) {
        var_f31 = mn_8022F298(arg0);
        if (arg1->end_frame != var_f31) {
            HSD_JObjAnim(arg0);
            var_f31 = mn_8022F298(arg0);
            if (var_f31 > arg1->end_frame) {
                var_f31 = arg1->end_frame;
                HSD_JObjReqAnim(arg0, var_f31);
                HSD_JObjAnim(arg0);
            }
        }
    } else {
        HSD_JObjAnim(arg0);
        var_f31 = mn_8022F298(arg0);
        temp_f0_2 = arg1->end_frame;
        if (var_f31 >= temp_f0_2) {
            var_f31 = arg1->loop_frame + (var_f31 - temp_f0_2);
            HSD_JObjReqAnim(arg0, var_f31);
            HSD_JObjAnim(arg0);
        }
    }
    return var_f31;
}

void mn_8022F0F0(int arg0)
{
    HSD_GObj* curr = ((HSD_GObj**) HSD_GObj_Entities)[(u8) arg0];
    PAD_STACK(8);
    while (curr != NULL) {
        HSD_GObj* next = curr->next;
        HSD_GObjPLink_80390228(curr);
        curr = next;
    }
}

void mn_8022F138(u16 arg0, u16 arg1)
{
    int i;
    PAD_STACK(0x18);
    for (i = arg0; i <= arg1; i++) {
        mn_8022F0F0(i);
    }
}

static inline void mn_8022F1A8_inline(u8 arg0)
{
    HSD_GObj* curr = ((HSD_GObj**) HSD_GObj_Entities)[arg0];
    PAD_STACK(8);
    while (curr != NULL) {
        HSD_GObj* next = curr->next;
        HSD_GObj_80390CD4(curr);
        curr = next;
    }
}

void mn_8022F1A8(u16 arg0, u16 arg1)
{
    int i;
    PAD_STACK(8);
    for (i = arg0; i <= arg1; i++) {
        mn_8022F1A8_inline(i);
    }
}

bool mn_8022F218(void)
{
    if (gm_GetButtonsTriggered(PAD_MAX_CONTROLLERS) & PAD_LR_START) {
        return true;
    }
    return false;
}

void mn_8022F268(void)
{
    gmMainLib_GetGameRules()->force_main_menu = 1;
}

/// @brief returns the current frame of jobjs animation
float mn_8022F298(HSD_JObj* jobj)
{
    HSD_AObj* aobj;
    HSD_DObj* dobj;
    HSD_MObj* mobj;
    HSD_TObj* tobj;

    aobj = jobj->aobj;
    if (aobj != NULL) {
        return aobj->curr_frame;
    }
    dobj = jobj->u.dobj;
    if (dobj != NULL) {
        mobj = dobj->mobj;
        if (mobj != NULL) {
            aobj = mobj->aobj;
            if (aobj != NULL) {
                return aobj->curr_frame;
            }
            tobj = mobj->tobj;
            if (tobj != NULL) {
                aobj = tobj->aobj;
                if (aobj != NULL) {
                    return aobj->curr_frame;
                }
            }
        }
    }
    if (!(jobj->flags & 0x1000)) {
        jobj = jobj->child;
        while (jobj != NULL) {
            float frame = mn_8022F298(jobj);
            if (frame != -1.0f) {
                return frame;
            }
            jobj = jobj->next;
        }
    }
    return -1.0f;
}

void mn_8022F360(HSD_AObj* aobj, void* obj, u32 arg2)
{
    HSD_FObj* fobj = aobj->fobj;
    while (fobj != NULL) {
        if (fobj->obj_type == arg2 || arg2 == 0xFF) {
            HSD_FObjStopAnim(fobj, obj, NULL, 0.0F);
        }
        fobj = fobj->next;
    }
}

void mn_8022F3D8(HSD_JObj* jobj, u8 arg1, HSD_TypeMask mask)
{
    HSD_ForeachAnim(jobj, JOBJ_TYPE, mask, mn_8022F360, AOBJ_ARG_AOU, arg1);
}

#define MY_MAX(x, y) ((x) < (y) ? (y) : (x))
#define MY_MIN(x, y) ((x) > (y) ? (y) : (x))

/**
 * Moves x toward a target value in increments of dx.
 * Returns +1 if x was increased toward the target value,
 * -1 if it was decreased toward the target value,
 * and 0 if it was already at the target and was unchanged.
 */
int mn_8022F410(float* x, const float* target, float dx)
{
    if (*x == *target) {
        return 0;
    }
    if (*x < *target) {
        *x = MY_MIN(*x + dx, *target);
        return +1;
    } else {
        *x = MY_MAX(*x - dx, *target);
        return -1;
    }
}

/// Same as mn_8022F410, but for int values instead of float.
int mn_8022F470(int* x, const int* target, int dx)
{
    if (*x == *target) {
        return 0;
    }
    if (*x < *target) {
        *x = MY_MIN(*x + dx, *target);
        return +1;
    } else {
        *x = MY_MAX(*x - dx, *target);
        return -1;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void mn_8022F4CC(void)
{
    if (gm_GetCurrentGameMode() == GM_TOURNAMENT) {
        HSD_SisLib_803A5E70();
        mn_8022EBDC();
        gm_80190EA4();
        return;
    }
    if (gm_GetCurrentGameMode() == GM_MENU) {
        mn_80229894(2, 3, 3);
        return;
    }
    HSD_SisLib_803A5E70();
    mn_8022EBDC();
    mnCharSel_802640A0();
}
#ifdef MUST_MATCH
#pragma pop
#endif
