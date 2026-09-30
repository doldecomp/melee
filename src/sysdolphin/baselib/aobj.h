/**
 * @file aobj.h
 * @brief Animation Object (AObj) API
 * @details The AObj is the core keyframe animation interpolation system. It manages playback state, frame timing, and applies FObjDesc chains (frame objects) that define keyframed animation tracks targeting specific object properties (translation, rotation, scaling, etc.).
 */

#ifndef _aobj_h_
#define _aobj_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/fobj.h>
#include <sysdolphin/baselib/objalloc.h>
#include <sysdolphin/baselib/object.h>

#define AOBJ_REWINDED (1 << 26)
#define AOBJ_FIRST_PLAY (1 << 27)
#define AOBJ_NO_UPDATE (1 << 28)
#define AOBJ_LOOP (1 << 29)
#define AOBJ_NO_ANIM (1 << 30)

typedef enum _AObj_Arg_Type {
    AOBJ_ARG_A,
    AOBJ_ARG_AF,
    AOBJ_ARG_AV,
    AOBJ_ARG_AU,
    AOBJ_ARG_AO,
    AOBJ_ARG_AOF,
    AOBJ_ARG_AOV,
    AOBJ_ARG_AOU,
    AOBJ_ARG_AOT,
    AOBJ_ARG_AOTF,
    AOBJ_ARG_AOTV,
    AOBJ_ARG_AOTU,
} AObj_Arg_Type;

typedef union _callbackArg {
    f32 f;
    u32 d;
    void* v;
} callbackArg;

struct HSD_AObj {
    u32 flags;
    f32 curr_frame;
    f32 rewind_frame;
    f32 end_frame;
    f32 framerate;
    HSD_FObj* fobj;
    struct HSD_Obj* hsd_obj;
};

struct HSD_AObjDesc {
    u32 flags;
    f32 end_frame;
    HSD_FObjDesc* fobjdesc;
    /// The joint to animate. Its address is also the key the joint's
    /// object is registered under once loaded.
    HSD_Joint* obj_id;
};

struct HSD_AnimJoint {
    HSD_AnimJoint* child;
    HSD_AnimJoint* next;
    HSD_AObjDesc* aobjdesc;
    HSD_RObjAnimJoint* robj_anim;
    u32 flags;
};

/**
 * @brief Initializes the object allocation data for AObjs
 */
void HSD_AObjInitAllocData(void);

/**
 * @brief Gets the AObj allocation data structure
 * @return Pointer to the HSD_ObjAllocData for AObjs
 */
HSD_ObjAllocData* HSD_AObjGetAllocData(void);

/**
 * @brief Gets the flags of an AObj
 * @param aobj The Animation Object
 * @return The 32-bit flags of the AObj, or 0 if aobj is NULL
 */
u32 HSD_AObjGetFlags(HSD_AObj* aobj);

/**
 * @brief Sets specific flags on an AObj
 * @param aobj The Animation Object
 * @param flags The flags to set (only AOBJ_LOOP and AOBJ_NO_UPDATE are allowed)
 */
void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags);

/**
 * @brief Clears specific flags from an AObj
 * @param aobj The Animation Object
 * @param flags The flags to clear (only AOBJ_LOOP and AOBJ_NO_UPDATE are allowed)
 */
void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags);

/**
 * @brief Sets the FObj (Frame Object) chain for an AObj
 * @param aobj The Animation Object
 * @param fobj The Frame Object chain to attach
 */
void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj);

/**
 * @brief Initializes the global end callback variables for AObjs
 */
void HSD_AObjInitEndCallBack(void);

/**
 * @brief Invokes registered end callbacks for AObjs if the animation has finished
 */
void HSD_AObjInvokeCallBacks(void);

/**
 * @brief Requests the AObj to begin animation playback at a specific frame
 * @param aobj The Animation Object
 * @param frame The starting frame
 */
void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame);

/**
 * @brief Stops animation playback on an AObj
 * @param aobj The Animation Object
 * @param obj The target object being animated (e.g. JObj, MObj)
 * @param func The update function to evaluate final animation states
 */
void HSD_AObjStopAnim(HSD_AObj* aobj, void* obj, HSD_ObjUpdateFunc func);

/**
 * @brief Interprets the animation, advancing the time and evaluating keyframes
 * @param aobj The Animation Object
 * @param obj The target object being animated
 * @param update_func The update function applied during interpolation
 */
void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj,
                           HSD_ObjUpdateFunc update_func);

/**
 * @brief Loads an AObj from an AObjDesc description structure
 * @param aobjdesc The AObj description
 * @return The loaded Animation Object
 */
HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc);

/**
 * @brief Removes and frees an AObj, its FObjs, and unreferences its target object
 * @param aobj The Animation Object
 */
void HSD_AObjRemove(HSD_AObj* aobj);

/**
 * @brief Allocates a new AObj instance
 * @return A new Animation Object
 */
HSD_AObj* HSD_AObjAlloc(void);

/**
 * @brief Frees an AObj instance
 * @param aobj The Animation Object
 */
void HSD_AObjFree(HSD_AObj* aobj);

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
                     AObj_Arg_Type arg_type, ...);

/**
 * @brief Sets the animation playback rate for an AObj
 * @param aobj The Animation Object
 * @param rate The playback rate
 */
void HSD_AObjSetRate(HSD_AObj* aobj, f32 rate);

/**
 * @brief Sets the rewind (loop start) frame for an AObj
 * @param aobj The Animation Object
 * @param frame The rewind frame
 */
void HSD_AObjSetRewindFrame(HSD_AObj* aobj, f32 frame);

/**
 * @brief Sets the end frame for an AObj
 * @param aobj The Animation Object
 * @param frame The end frame
 */
void HSD_AObjSetEndFrame(HSD_AObj* aobj, f32 frame);

/**
 * @brief Sets the current playback frame for an AObj, requesting animation if active
 * @param aobj The Animation Object
 * @param frame The current frame
 */
void HSD_AObjSetCurrentFrame(HSD_AObj* aobj, f32 frame);

/**
 * @brief Clears the end callback list memory reference
 * @param low Lower memory boundary (unused)
 * @param high Upper memory boundary (unused)
 */
void _HSD_AObjForgetMemory(void* low, void* high);

/**
 * @brief Gets the current frame of an AObj
 * @param aobj The Animation Object
 * @return The current frame
 */
static inline f32 HSD_AObjGetCurrFrame(HSD_AObj* aobj)
{
    HSD_ASSERT(0x92, aobj);
    return aobj->curr_frame;
}

/**
 * @brief Gets the end frame of an AObj
 * @param aobj The Animation Object
 * @return The end frame
 */
static inline f32 HSD_AObjGetEndFrame(HSD_AObj* aobj)
{
    HSD_ASSERT(0xAA, aobj);
    return aobj->end_frame;
}

#endif
