/**
 * @file aobj.c
 * @brief Animation Object (AObj) API implementation
 * @details The AObj is the core keyframe animation interpolation system. It manages playback state, frame timing, and applies FObjDesc chains (frame objects) that define keyframed animation tracks targeting specific object properties (translation, rotation, scaling, etc.).
 */

#include "aobj.h"

#include <math.h>
#include <stdarg.h>
#include <string.h>

#include "cobj.h" // IWYU pragma: keep
#include "debug.h"
#include "dobj.h"
#include "fog.h"
#include "id.h"
#include "jobj.h"
#include "list.h"
#include "lobj.h"
#include "mobj.h"
#include "pobj.h"
#include "robj.h"
#include "tobj.h"
#include "wobj.h"

HSD_ObjAllocData aobj_alloc_data;

static HSD_SList* endcallback_list;

static s32 HSD_AObj_804D762C;
static s32 HSD_AObj_804D7630;

/**
 * @brief Initializes the object allocation data for AObjs
 */
void HSD_AObjInitAllocData(void)
{
    HSD_ObjAllocInit(&aobj_alloc_data, sizeof(HSD_AObj), 4);
}

/**
 * @brief Gets the AObj allocation data structure
 * @return Pointer to the HSD_ObjAllocData for AObjs
 */
HSD_ObjAllocData* HSD_AObjGetAllocData(void)
{
    return &aobj_alloc_data;
}

/**
 * @brief Gets the flags of an AObj
 * @param aobj The Animation Object
 * @return The 32-bit flags of the AObj, or 0 if aobj is NULL
 */
u32 HSD_AObjGetFlags(HSD_AObj* aobj)
{
    return aobj ? aobj->flags : 0;
}

/**
 * @brief Sets specific flags on an AObj
 * @param aobj The Animation Object
 * @param flags The flags to set (only AOBJ_LOOP and AOBJ_NO_UPDATE are allowed)
 */
void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE);
        aobj->flags |= flags;
    }
}

/**
 * @brief Clears specific flags from an AObj
 * @param aobj The Animation Object
 * @param flags The flags to clear (only AOBJ_LOOP and AOBJ_NO_UPDATE are allowed)
 */
void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE);
        aobj->flags &= ~flags;
    }
}

/**
 * @brief Sets the FObj (Frame Object) chain for an AObj
 * @param aobj The Animation Object
 * @param fobj The Frame Object chain to attach
 */
void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj)
{
    if (!aobj) {
        return;
    }

    if (aobj->fobj) {
        HSD_FObjRemoveAll(aobj->fobj);
    }
    aobj->fobj = fobj;
}

/**
 * @brief Initializes the global end callback variables for AObjs
 */
void HSD_AObjInitEndCallBack(void)
{
    HSD_AObj_804D762C = 0;
    HSD_AObj_804D7630 = 0;
}

/**
 * @brief Invokes registered end callbacks for AObjs if the animation has finished
 */
void HSD_AObjInvokeCallBacks(void)
{
    HSD_SList* list;

    if (HSD_AObj_804D762C != 0 && HSD_AObj_804D7630 == 0) {
        list = endcallback_list;
        while (list) {
            void (*func)(void) = list->data;
            (*func)();
            list = list->next;
        }
    }
}

/**
 * @brief Requests the AObj to begin animation playback at a specific frame
 * @param aobj The Animation Object
 * @param frame The starting frame
 */
void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame)
{
    u32 flags;

    if (!aobj) {
        return;
    }

    aobj->curr_frame = frame;

    flags = aobj->flags & ~AOBJ_NO_ANIM;
    aobj->flags = flags | AOBJ_FIRST_PLAY;

    HSD_FObjReqAnimAll(aobj->fobj, frame);
}

/**
 * @brief Stops animation playback on an AObj
 * @param aobj The Animation Object
 * @param obj The target object being animated (e.g. JObj, MObj)
 * @param func The update function to evaluate final animation states
 */
void HSD_AObjStopAnim(HSD_AObj* aobj, void* obj, HSD_ObjUpdateFunc func)
{
    if (!aobj) {
        return;
    }

    HSD_FObjStopAnimAll(aobj->fobj, obj, func, aobj->framerate);
    aobj->flags |= AOBJ_NO_ANIM;
}

/**
 * @brief Gets the wrapped frame value after looping
 * @param aobj The Animation Object
 * @return The properly wrapped frame within the loop bounds
 */
static inline f32 getLoopedFrame(HSD_AObj* aobj)
{
    f32 y = aobj->end_frame - aobj->rewind_frame;
    f32 x = aobj->curr_frame - aobj->rewind_frame;
    return fmodf(x, y) + aobj->rewind_frame;
}

/**
 * @brief Interprets the animation, advancing the time and evaluating keyframes
 * @param aobj The Animation Object
 * @param obj The target object being animated
 * @param update_func The update function applied during interpolation
 */
void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj,
                           HSD_ObjUpdateFunc update_func)
{
    f32 rate = 0;

    if (!aobj || aobj->flags & AOBJ_NO_ANIM) {
        return;
    }

    if (aobj->flags & AOBJ_FIRST_PLAY) {
        aobj->flags &= ~AOBJ_FIRST_PLAY;
        rate = 0.0F;
    } else {
        rate = aobj->framerate;
        aobj->curr_frame += aobj->framerate;
    }

    if ((aobj->flags & AOBJ_LOOP) && aobj->end_frame <= aobj->curr_frame) {
        if (aobj->rewind_frame < aobj->end_frame) {
            HSD_FObjStopAnimAll(aobj->fobj, obj, update_func, rate);
            aobj->curr_frame = getLoopedFrame(aobj);
            HSD_FObjReqAnimAll(aobj->fobj, aobj->curr_frame);
        } else {
            aobj->curr_frame = aobj->end_frame;
        }
        rate = 0.0F;
        aobj->flags |= AOBJ_REWINDED;
    } else {
        aobj->flags &= ~AOBJ_REWINDED;
    }

    if (aobj->flags & AOBJ_NO_UPDATE) {
        HSD_FObjInterpretAnimAll(aobj->fobj, obj, NULL, rate);
    } else {
        HSD_FObjInterpretAnimAll(aobj->fobj, obj, update_func, rate);
    }

    if (!(aobj->flags & AOBJ_LOOP) && aobj->end_frame <= aobj->curr_frame) {
        HSD_AObjStopAnim(aobj, obj, update_func);
    }

    if (aobj->flags & AOBJ_NO_ANIM) {
        HSD_AObj_804D762C += 1;
    } else {
        HSD_AObj_804D7630 += 1;
    }
}

/**
 * @brief Loads an AObj from an AObjDesc description structure
 * @param aobjdesc The AObj description
 * @return The loaded Animation Object
 */
HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc)
{
    HSD_FObjDesc* fobjdesc;
    HSD_AObj* aobj;

    u8 _[4];

    HSD_FObj* fobj;
    HSD_IDKey id;
    HSD_Obj* target_obj;

    if (aobjdesc != NULL) {
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, aobjdesc->flags);
        HSD_AObjSetRewindFrame(aobj, 0.0F);
        HSD_AObjSetEndFrame(aobj, aobjdesc->end_frame);
        fobjdesc = aobjdesc->fobjdesc;
        fobj = HSD_FObjLoadDesc(fobjdesc);
        HSD_AObjSetFObj(aobj, fobj);
        id = (HSD_IDKey) aobjdesc->obj_id;
        if (id != 0U) {
            HSD_Obj* hsd_obj = HSD_IDGetDataFromTable(0, id, 0);
            target_obj = hsd_obj;
            if (hsd_obj != NULL) {
                ref_INC(hsd_obj);
            } else {
                target_obj = (HSD_Obj*) HSD_JObjLoadJoint(aobjdesc->obj_id);
            }
            if (aobj != NULL) {
                if (aobj->hsd_obj != NULL) {
                    HSD_JObjUnref((HSD_JObj*) aobj->hsd_obj);
                }
                aobj->hsd_obj = target_obj;
            }
        }
        return aobj;
    }
    return NULL;
}

/**
 * @brief Removes and frees an AObj, its FObjs, and unreferences its target object
 * @param aobj The Animation Object
 */
void HSD_AObjRemove(HSD_AObj* aobj)
{
    if (!aobj) {
        return;
    }

    if (aobj) {
        if (aobj->fobj) {
            HSD_FObjRemoveAll(aobj->fobj);
        }
        aobj->fobj = NULL;
    }

    if (aobj) {
        if (aobj->hsd_obj != NULL) {
            HSD_JObjUnref((HSD_JObj*) aobj->hsd_obj);
        }
        aobj->hsd_obj = NULL;
    }
    HSD_AObjFree(aobj);
}

/**
 * @brief Allocates a new AObj instance
 * @return A new Animation Object
 */
HSD_AObj* HSD_AObjAlloc(void)
{
    HSD_AObj* new = HSD_ObjAlloc(HSD_AObjGetAllocData());
    HSD_ASSERT(489, new);

    memset(new, 0, sizeof(HSD_AObj));
    new->flags = AOBJ_NO_ANIM;
    new->framerate = 1.0F;
    return new;
}

/**
 * @brief Frees an AObj instance
 * @param aobj The Animation Object
 */
void HSD_AObjFree(HSD_AObj* aobj)
{
    if (!aobj) {
        return;
    }

    HSD_ObjFree(HSD_AObjGetAllocData(), aobj);
}

static void callbackForeachFunc(HSD_AObj* aobj, void* obj, HSD_Type type,
                                void* func, AObj_Arg_Type arg_type,
                                callbackArg* arg)
{
    switch (arg_type) {
    case AOBJ_ARG_A:
        (*(void (*)(HSD_AObj*)) func)(aobj);
        return;
    case AOBJ_ARG_AF:
        (*(void (*)(HSD_AObj*, f32)) func)(aobj, arg->f);
        return;
    case AOBJ_ARG_AV:
        (*(void (*)(HSD_AObj*, void*)) func)(aobj, arg->v);
        return;
    case AOBJ_ARG_AU:
        (*(void (*)(HSD_AObj*, u32)) func)(aobj, arg->d);
        return;
    case AOBJ_ARG_AO:
        (*(void (*)(HSD_AObj*, void*)) func)(aobj, obj);
        return;
    case AOBJ_ARG_AOT:
        (*(void (*)(HSD_AObj*, void*, HSD_Type)) func)(aobj, obj, type);
        return;
    case AOBJ_ARG_AOF:
        (*(void (*)(HSD_AObj*, void*, f32)) func)(aobj, obj, arg->f);
        return;
    case AOBJ_ARG_AOV:
        (*(void (*)(HSD_AObj*, void*, void*)) func)(aobj, obj, arg->v);
        return;
    case AOBJ_ARG_AOU:
        (*(void (*)(HSD_AObj*, void*, u32)) func)(aobj, obj, arg->d);
        return;
    case AOBJ_ARG_AOTF:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, f32)) func)(aobj, obj, type,
                                                            arg->f);
        return;
    case AOBJ_ARG_AOTV:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, void*)) func)(aobj, obj, type,
                                                              arg->v);
        return;
    case AOBJ_ARG_AOTU:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, u32)) func)(aobj, obj, type,
                                                            arg->d);
        return;
    }
}

static void FogForeachAnim(HSD_Fog* fog, HSD_TypeMask mask, Event func,
                           AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (mask & FOG_MASK && fog != NULL && fog->aobj != NULL) {
        callbackForeachFunc(fog->aobj, fog, FOG_TYPE, func, arg_type, arg);
    }
}

static void TObjForeachAnim(HSD_TObj* tobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; tobj != NULL; tobj = tobj->next) {
        if (mask & TOBJ_MASK && tobj->aobj != NULL) {
            callbackForeachFunc(tobj->aobj, tobj, TOBJ_TYPE, func, arg_type,
                                arg);
        }
    }
}

static void RObjForeachAnim(HSD_RObj* robj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; robj != NULL; robj = robj->next) {
        if (mask & ROBJ_MASK && robj->aobj != NULL) {
            callbackForeachFunc(robj->aobj, robj, ROBJ_TYPE, func, arg_type,
                                arg);
        }
    }
}

static void WObjForeachAnim(HSD_WObj* wobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (wobj == NULL) {
        return;
    }

    if (mask & WOBJ_MASK && wobj->aobj != NULL) {
        callbackForeachFunc(wobj->aobj, wobj, WOBJ_TYPE, func, arg_type, arg);
    }
    RObjForeachAnim(wobj->robj, mask, func, arg_type, arg);
}

static void CObjForeachAnim(HSD_CObj* cobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (cobj == NULL) {
        return;
    }

    if (mask & COBJ_MASK && cobj->aobj != NULL) {
        callbackForeachFunc(cobj->aobj, cobj, COBJ_TYPE, func, arg_type, arg);
    }
    WObjForeachAnim(cobj->eyepos, mask, func, arg_type, arg);
    WObjForeachAnim(cobj->interest, mask, func, arg_type, arg);
}

static void LObjForeachAnim(HSD_LObj* lobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; lobj != NULL; lobj = lobj->next) {
        if (mask & LOBJ_MASK && lobj->aobj != NULL) {
            callbackForeachFunc(lobj->aobj, lobj, LOBJ_TYPE, func, arg_type,
                                arg);
        }
        WObjForeachAnim(lobj->position, mask, func, arg_type, arg);
        WObjForeachAnim(lobj->interest, mask, func, arg_type, arg);
    }
}

static void PObjForeachAnim(HSD_PObj* pobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (mask & POBJ_MASK && pobj != NULL &&
        pobj_type(pobj) == POBJ_SHAPEANIM && pobj->u.shape_set != NULL &&
        pobj->u.shape_set->aobj != NULL)
    {
        callbackForeachFunc(pobj->u.shape_set->aobj, pobj, POBJ_TYPE, func,
                            arg_type, arg);
    }
}

static void MObjForeachAnim(HSD_MObj* mobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (mobj == NULL) {
        return;
    }

    if (mask & MOBJ_MASK && mobj->aobj != NULL) {
        callbackForeachFunc(mobj->aobj, mobj, MOBJ_TYPE, func, arg_type, arg);
    }
    TObjForeachAnim(mobj->tobj, mask, func, arg_type, arg);
}

static void DObjForeachAnim(HSD_DObj* dobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; dobj != NULL; dobj = dobj->next) {
        if (mask & DOBJ_MASK && dobj->aobj != NULL) {
            callbackForeachFunc(dobj->aobj, dobj, DOBJ_TYPE, func, arg_type,
                                arg);
        }
        MObjForeachAnim(dobj->mobj, mask, func, arg_type, arg);
        PObjForeachAnim(dobj->pobj, mask, func, arg_type, arg);
    }
}

static void JObjForeachAnim(HSD_JObj* obj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    HSD_ASSERT(715, obj);

    if (mask & JOBJ_MASK && obj->aobj != NULL) {
        callbackForeachFunc(obj->aobj, obj, JOBJ_TYPE, func, arg_type, arg);
    }
    if (union_type_dobj(obj)) {
        DObjForeachAnim(obj->u.dobj, mask, func, arg_type, arg);
    }
    RObjForeachAnim(obj->robj, mask, func, arg_type, arg);
    if (!(obj->flags & JOBJ_INSTANCE)) {
        for (obj = obj->child; obj != NULL; obj = obj->next) {
            JObjForeachAnim(obj, mask, func, arg_type, arg);
        }
    }
}

/**
 * @brief Applies a callback function to all AObjs recursively down an object hierarchy
 * @param obj The root object (e.g. JObj)
 * @param type The type of the root object
 * @param mask A bitmask defining which object types to traverse
 * @param func The callback function to invoke
 * @param arg_type The argument signature type for the callback
 * @param ... Variable arguments passed to the callback
 */
void HSD_ForeachAnim(void* obj, HSD_Type type, HSD_TypeMask mask, void* func,
                     AObj_Arg_Type arg_type, ...)
{
    va_list ap;
    callbackArg arg;

    if (obj == NULL) {
        return;
    }

    va_start(ap, arg_type);
    switch (arg_type) {
    case AOBJ_ARG_A:
    case AOBJ_ARG_AO:
    case AOBJ_ARG_AOT:
        break;
    case AOBJ_ARG_AF:
    case AOBJ_ARG_AOF:
    case AOBJ_ARG_AOTF:
        arg.f = va_arg(ap, f64);
        break;
    case AOBJ_ARG_AV:
    case AOBJ_ARG_AOV:
    case AOBJ_ARG_AOTV:
        arg.v = va_arg(ap, void*);
        break;
    case AOBJ_ARG_AU:
    case AOBJ_ARG_AOU:
    case AOBJ_ARG_AOTU:
        arg.d = va_arg(ap, u32);
        break;
    default:
        HSD_Panic(__FILE__, 826, "unexpected argument format.\n");
        break;
    }

    switch (type) {
    case JOBJ_TYPE:
        JObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case DOBJ_TYPE:
        DObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case MOBJ_TYPE:
        MObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case POBJ_TYPE:
        PObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case TOBJ_TYPE:
        TObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case LOBJ_TYPE:
        LObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case COBJ_TYPE:
        CObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case ROBJ_TYPE:
        RObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case WOBJ_TYPE:
        WObjForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    case FOG_TYPE:
        FogForeachAnim(obj, mask, func, arg_type, &arg);
        break;
    default:
        HSD_Panic(__FILE__, 862, "unexpected type of object.\n");
        break;
    }
    va_end(ap);
}

/**
 * @brief Sets the animation playback rate for an AObj
 * @param aobj The Animation Object
 * @param rate The playback rate
 */
void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate)
{
    if (!aobj) {
        return;
    }
    aobj->framerate = rate;
}

/**
 * @brief Sets the rewind (loop start) frame for an AObj
 * @param aobj The Animation Object
 * @param frame The rewind frame
 */
void HSD_AObjSetRewindFrame(HSD_AObj* aobj, f32 frame)
{
    if (!aobj) {
        return;
    }
    aobj->rewind_frame = frame;
}

/**
 * @brief Sets the end frame for an AObj
 * @param aobj The Animation Object
 * @param frame The end frame
 */
void HSD_AObjSetEndFrame(HSD_AObj* aobj, f32 frame)
{
    if (!aobj) {
        return;
    }
    aobj->end_frame = frame;
}

/**
 * @brief Sets the current playback frame for an AObj, requesting animation if active
 * @param aobj The Animation Object
 * @param frame The current frame
 */
void HSD_AObjSetCurrentFrame(HSD_AObj* aobj, f32 frame)
{
    if (!aobj) {
        return;
    }

    if (!(aobj->flags & AOBJ_NO_ANIM) && aobj) {
        aobj->curr_frame = frame;
        aobj->flags = (aobj->flags & 0xBFFFFFFF) | AOBJ_FIRST_PLAY;
        HSD_FObjReqAnimAll(aobj->fobj, frame);
    }
}

/**
 * @brief Clears the end callback list memory reference
 * @param low Lower memory boundary (unused)
 * @param high Upper memory boundary (unused)
 */
void _HSD_AObjForgetMemory(void* low, void* high)
{
    endcallback_list = NULL;
}
