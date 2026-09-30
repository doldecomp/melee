/**
 * @file dobj.c
 * @brief Display Object (DObj) implementation for the Sysdolphin scene graph.
 * @details Implements lifecycle, hierarchy loading, animation dispatch, and GX display list
 * rendering for DObj mesh nodes attached to JObj bones.
 * Module prefix: HSD (Sysdolphin)
 */

#include "dobj.h"

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "mobj.h"
#include "pobj.h"
#include <dolphin/os.h>

static void DObjInfoInit(void);

/// Global class descriptor and virtual method table for HSD_DObj
HSD_DObjInfo hsdDObj = { DObjInfoInit };

/// Optional override class information for custom polymorphic DObj allocations
static HSD_ClassInfo* default_class = NULL;

/// Currently active DObj being processed / rendered
static HSD_DObj* current_dobj = NULL;

/**
 * @brief Sets the currently active DObj pointer.
 * @param dobj Pointer to active HSD_DObj
 */
void HSD_DObjSetCurrent(HSD_DObj* dobj)
{
    current_dobj = dobj;
}

/**
 * @brief Retrieves the render and state flags of a DObj.
 * @param dobj Pointer to HSD_DObj
 * @return Bitfield of flags, or 0 if dobj is NULL
 */
u32 HSD_DObjGetFlags(HSD_DObj* dobj)
{
    if (dobj != NULL) {
        return dobj->flags;
    }
    return 0;
}

/**
 * @brief Sets specific flag bits on a DObj.
 * @param dobj Pointer to HSD_DObj
 * @param flags Bitmask of flags to set (bitwise OR)
 */
void HSD_DObjSetFlags(HSD_DObj* dobj, u32 flags)
{
    if (dobj != NULL) {
        dobj->flags |= flags;
    }
}

/**
 * @brief Clears specific flag bits on a DObj.
 * @param dobj Pointer to HSD_DObj
 * @param flags Bitmask of flags to clear (bitwise AND NOT)
 */
void HSD_DObjClearFlags(HSD_DObj* dobj, u32 flags)
{
    if (dobj != NULL) {
        dobj->flags &= ~flags;
    }
}

/**
 * @brief Modifies a masked subset of flags on a DObj.
 * @param dobj Pointer to HSD_DObj
 * @param flags New bit values to apply within the mask
 * @param mask Bitmask specifying which flags to modify
 */
void HSD_DObjModifyFlags(HSD_DObj* dobj, u32 flags, u32 mask)
{
    if (dobj == NULL) {
        return;
    }

    dobj->flags = (dobj->flags & ~mask) | (flags & mask);
}

/**
 * @brief Removes animations from a DObj matching specified flag bits.
 * @details If bit 1 (0x2) is set, detaches and frees the DObj's AObj.
 * Also removes matching animations across all attached PObjs and MObjs.
 * @param dobj Pointer to HSD_DObj
 * @param flags Animation removal filter flags
 */
void HSD_DObjRemoveAnimByFlags(HSD_DObj* dobj, u32 flags)
{
    if (dobj == NULL) {
        return;
    }

    if ((flags & 2) != 0) {
        HSD_AObjRemove(dobj->aobj);
        dobj->aobj = NULL;
    }
    HSD_PObjRemoveAnimAllByFlags(dobj->pobj, flags);
    HSD_MObjRemoveAnimByFlags(dobj->mobj, flags);
}

/**
 * @brief Removes animations from an entire DObj sibling chain matching flags.
 * @param dobj Head of HSD_DObj chain
 * @param flags Animation removal filter flags
 */
void HSD_DObjRemoveAnimAllByFlags(HSD_DObj* dobj, u32 flags)
{
    HSD_DObj* cur;

    if (dobj == NULL) {
        return;
    }

    for (cur = dobj; cur != NULL; cur = cur->next) {
        HSD_DObjRemoveAnimByFlags(cur, flags);
    }
}

/**
 * @brief Attaches material and shape animations to a single DObj.
 * @param dobj Pointer to HSD_DObj
 * @param mat_anim Material animation for MObj
 * @param sh_anim Shape animation for PObj chain
 */
void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim,
                     HSD_ShapeAnimDObj* sh_anim)
{
    HSD_ShapeAnim* shapeanim;

    if (dobj == NULL) {
        return;
    }

    if (sh_anim != NULL) {
        shapeanim = sh_anim->shapeanim;
    } else {
        shapeanim = NULL;
    }

    HSD_PObjAddAnimAll(dobj->pobj, shapeanim);
    HSD_MObjAddAnim(dobj->mobj, mat_anim);
}

/**
 * @brief Attaches parallel chains of material and shape animations to a DObj chain.
 * @param dobj Head of HSD_DObj linked list
 * @param matanim Head of HSD_MatAnim linked list
 * @param shapeanimdobj Head of HSD_ShapeAnimDObj linked list
 */
void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim,
                        HSD_ShapeAnimDObj* shapeanimdobj)
{
    HSD_DObj* cur_dobj;
    HSD_MatAnim* cur_matanim;
    HSD_ShapeAnimDObj* cur_shapeanim;

    if (dobj == NULL) {
        return;
    }

    for (cur_dobj = dobj, cur_matanim = matanim, cur_shapeanim = shapeanimdobj; cur_dobj != NULL;
         cur_dobj = cur_dobj->next, cur_matanim = next_p(cur_matanim), cur_shapeanim = next_p(cur_shapeanim))
    {
        HSD_DObjAddAnim(cur_dobj, cur_matanim, cur_shapeanim);
    }
}

/**
 * @brief Requests animation playback start at a specific frame for matching flags.
 * @param dobj Pointer to HSD_DObj
 * @param startframe Starting frame number for playback
 * @param flags Filter flags determining which animations to update
 */
void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, f32 startframe, u32 flags)
{
    if (dobj == NULL) {
        return;
    }

    HSD_PObjReqAnimAllByFlags(dobj->pobj, startframe, flags);
    HSD_MObjReqAnimByFlags(dobj->mobj, startframe, flags);
}

/**
 * @brief Requests animation playback across an entire DObj chain by flags.
 * @param dobj Head of HSD_DObj linked list
 * @param startframe Starting frame number for playback
 * @param flags Filter flags determining which animations to update
 */
void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, f32 startframe, u32 flags)
{
    HSD_DObj* cur;

    if (dobj == NULL) {
        return;
    }

    for (cur = dobj; cur != NULL; cur = cur->next) {
        HSD_DObjReqAnimByFlags(cur, startframe, flags);
    }
}

/**
 * @brief Requests animation playback across an entire DObj chain with all flags (0x7FF).
 * @param dobj Head of HSD_DObj linked list
 * @param startframe Starting frame number for playback
 */
void HSD_DObjReqAnimAll(HSD_DObj* dobj, f32 startframe)
{
    HSD_DObj* cur;

    if (dobj == NULL) {
        return;
    }

    for (cur = dobj; cur != NULL; cur = cur->next) {
        HSD_DObjReqAnimByFlags(cur, startframe, 0x7FF);
    }
}

/**
 * @brief Advances animation by one tick on a single DObj (PObjs and MObj).
 * @param dobj Pointer to HSD_DObj
 */
void HSD_DObjAnim(HSD_DObj* dobj)
{
    if (dobj == NULL) {
        return;
    }

    HSD_PObjAnimAll(dobj->pobj);
    HSD_MObjAnim(dobj->mobj);
}

/**
 * @brief Advances animation by one tick across an entire DObj linked list.
 * @param dobj Head of HSD_DObj linked list
 */
void HSD_DObjAnimAll(HSD_DObj* dobj)
{
    HSD_DObj* cur;

    if (dobj == NULL) {
        return;
    }

    for (cur = dobj; cur != NULL; cur = cur->next) {
        HSD_DObjAnim(cur);
    }
}

/**
 * @brief Loads DObj hierarchy from archive descriptor.
 * @details Recursively loads sibling DObjs, loads the associated MObj material
 * and PObj polygon list, and classifies material blending mode into DObj render flags:
 * - 0x00000000: Opaque geometry -> flag bit 0x2
 * - 0x40000000: Translucent / Alpha blended -> flag bit 0x8
 * - 0x60000000: Punch-through / Alpha tested -> flag bit 0x4
 * Mask 0xE (bits 1, 2, 3) covers these blending category bits.
 * @param dobj Pointer to uninitialized HSD_DObj instance
 * @param desc Pointer to HSD_DObjDesc descriptor
 * @return 0 on success
 */
static int DObjLoad(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    dobj->next = HSD_DObjLoadDesc(desc->next);
    dobj->mobj = HSD_MObjLoadDesc(desc->mobjdesc);
    dobj->pobj = HSD_PObjLoadDesc(desc->pobjdesc);

    if (dobj->mobj != NULL) {
        switch (dobj->mobj->rendermode & 0x60000000) {
        case 0:
            HSD_DObjModifyFlags(dobj, 2, 0xE);
            break;
        case 0x40000000:
            HSD_DObjModifyFlags(dobj, 8, 0xE);
            break;
        case 0x60000000:
            HSD_DObjModifyFlags(dobj, 4, 0xE);
            break;
        default:
            OSReport("mobj has unexpected blending flags (0x%x).",
                     dobj->mobj->rendermode);
            HSD_Panic(__FILE__, 312, "\0");
        }
    }
    return 0;
}

/**
 * @brief Instantiates and loads a DObj hierarchy from archive descriptor data.
 * @details Resolves the class info (or uses default DObj class), allocates memory,
 * and calls the virtual load method to populate child MObjs, PObjs, and sibling DObjs.
 * @param desc Pointer to HSD_DObjDesc descriptor
 * @return Pointer to newly allocated HSD_DObj, or NULL if desc is NULL
 */
HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc)
{
    HSD_DObj* dobj;
    HSD_ClassInfo* info;

    if (desc == NULL) {
        return NULL;
    }

    if (desc->class_name == NULL ||
        (info = hsdSearchClassInfo(desc->class_name)) == NULL)
    {
        dobj = HSD_DObjAlloc();
    } else {
        dobj = HSD_DOBJ(hsdNew(info));
        if (dobj == NULL) {
            __assert(__FILE__, 378, "dobj");
        }
    }
    HSD_DOBJ_METHOD(dobj)->load(dobj, desc);

    return dobj;
}

/**
 * @brief Frees a single HSD_DObj instance via the class system destructor.
 * @param dobj Pointer to HSD_DObj to free
 */
void HSD_DObjRemove(HSD_DObj* dobj)
{
    hsdDelete(dobj);
}

/**
 * @brief Recursively frees an entire linked list of DObjs and their associated children.
 * @param dobj Head of HSD_DObj linked list to free
 */
void HSD_DObjRemoveAll(HSD_DObj* dobj)
{
    HSD_DObj* next_dobj;

    for (; dobj != NULL; dobj = next_dobj) {
        next_dobj = dobj->next;
        HSD_DObjRemove(dobj);
    }
}

/**
 * @brief Sets the default class used when allocating new DObj instances.
 * @param info Pointer to HSD_ClassInfo (must inherit from hsdDObj)
 */
void HSD_DObjSetDefaultClass(HSD_ClassInfo* info)
{
    if (info) {
        if (!hsdIsDescendantOf(info, &hsdDObj)) {
            // The line number here is totally made up, this function is
            // removed in practice but the string isn't
            __assert(__FILE__, __LINE__, "hsdIsDescendantOf(info, &hsdDObj)");
        }
    }
    default_class = info;
}

/**
 * @brief Allocates an uninitialized HSD_DObj instance.
 * @return Pointer to newly allocated HSD_DObj
 */
HSD_DObj* HSD_DObjAlloc(void)
{
    HSD_DObj* dobj = hsdNew(default_class ? default_class : &hsdDObj.parent);
    if (dobj == NULL) {
        __assert(__FILE__, 525, "dobj");
    }
    return dobj;
}

/**
 * @brief Resolves internal pointers and memory offsets for a DObj's PObj chain from descriptors.
 * @param dobj Pointer to HSD_DObj
 * @param desc Pointer to corresponding HSD_DObjDesc
 */
void HSD_DObjResolveRefs(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    if (dobj == NULL || desc == NULL) {
        return;
    }
    HSD_PObjResolveRefsAll(dobj->pobj, desc->pobjdesc);
}

/**
 * @brief Resolves internal pointers and memory offsets across parallel DObj and descriptor chains.
 * @param dobj Head of HSD_DObj linked list
 * @param desc Head of HSD_DObjDesc linked list
 */
void HSD_DObjResolveRefsAll(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    for (; dobj != NULL && desc != NULL; dobj = dobj->next, desc = desc->next)
    {
        HSD_DObjResolveRefs(dobj, desc);
    }
}

/**
 * @brief Dummy function to force linker retention of assertion error strings in .rodata.
 * @param dobj Pointer to HSD_DObj
 * @param mobj Pointer to HSD_MObj
 */
void forceStringAllocation(
    HSD_DObj* dobj,
    HSD_MObj*
        mobj) // This function exists for the sole purpose of causing strings
              // to end up in data by the compiler despite not being used
{
    if (dobj->pobj == NULL) {
        __assert(__FILE__, 700, "can not find specified pobj in link.\n");
    }
    if (dobj->pobj == NULL) {
        __assert(__FILE__, 702, "can not find specified pobj in link.");
    }
    if (dobj->mobj != mobj) {
        __assert(__FILE__, 704, "dobj->mobj == mobj");
    }
}

/**
 * @brief Dispatches GX display list rendering for a DObj.
 * @details Binds the DObj's material (MObj), sets up GX pipeline state, renders
 * all polygon primitives in the PObj chain, and restores material state.
 * @param dobj Pointer to HSD_DObj to render
 * @param vmtx Camera view transform matrix
 * @param pmtx Joint/bone model-view transform matrix
 * @param rendermode Rendering mode and pipeline flags (bit 0x04000000 bypasses material setup)
 */
void HSD_DObjDisp(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    HSD_PObj* cur_pobj;

    HSD_MObjSetCurrent(dobj->mobj);
    /* Bit 0x04000000 bypasses material setup (e.g. for external silhouette/shadow passes) */
    if ((rendermode & 0x4000000) == 0) {
        HSD_MOBJ_METHOD(dobj->mobj)->setup(dobj->mobj, rendermode);
    }
    for (cur_pobj = dobj->pobj; cur_pobj != NULL; cur_pobj = cur_pobj->next) {
        HSD_POBJ_METHOD(cur_pobj)->disp(cur_pobj, vmtx, pmtx, rendermode);
    }
    if ((rendermode & 0x4000000) == 0) {
        HSD_MOBJ_METHOD(dobj->mobj)->unset(dobj->mobj, rendermode);
    }
    HSD_MObjSetCurrent(NULL);
}

/**
 * @brief Class destructor for HSD_DObj instances.
 * @details Cleans up child MObj, PObj chain, and AObj, then chains to parent class release.
 * @param o Base HSD_Class pointer of the DObj being destroyed
 */
static void DObjRelease(HSD_Class* o)
{
    HSD_DObj* dobj = HSD_DOBJ(o);

    HSD_MObjRemove(dobj->mobj);
    HSD_PObjRemoveAll(dobj->pobj);
    HSD_AObjRemove(dobj->aobj);

    HSD_PARENT_INFO(&hsdDObj)->release(o);
}

/**
 * @brief Memory purge and class reset callback for HSD_DObj.
 * @details Resets the default class pointer if matching the purged class and chains to parent.
 * @param info Pointer to HSD_ClassInfo being purged
 */
static void DObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    HSD_PARENT_INFO(&hsdDObj)->amnesia(info);
}

/**
 * @brief Class initialization routine for HSD_DObj.
 * @details Registers the HSD_DObj class in the Sysdolphin class registry and binds
 * virtual methods (release, amnesia, disp, load).
 */
static void DObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdDObj), HSD_CLASS_INFO(&hsdClass),
                     "sysdolphin_base_library", "hsd_dobj",
                     sizeof(HSD_DObjInfo), sizeof(HSD_DObj));

    HSD_CLASS_INFO(&hsdDObj)->release = DObjRelease;
    HSD_CLASS_INFO(&hsdDObj)->amnesia = DObjAmnesia;
    HSD_DOBJ_INFO(&hsdDObj)->disp = HSD_DObjDisp;
    HSD_DOBJ_INFO(&hsdDObj)->load = DObjLoad;
}
