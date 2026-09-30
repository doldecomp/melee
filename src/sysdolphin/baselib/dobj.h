/**
 * @file dobj.h
 * @brief Display Object (DObj) declarations for the Sysdolphin scene graph.
 * @details Represents renderable mesh nodes attached to JObj bones in Sysdolphin.
 * Each DObj references an MObj (material/texture attributes) and a chain of PObjs
 * (polygonal primitive geometry and GX display lists).
 * Module prefix: HSD (Sysdolphin)
 */

#ifndef SYSDOLPHIN_BASELIB_DOBJ_H
#define SYSDOLPHIN_BASELIB_DOBJ_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <dolphin/mtx.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/mobj.h>

/// Flag indicating that this DObj should not be rendered
#define DOBJ_HIDDEN 0x1

/**
 * @brief Display Object structure representing a renderable mesh node.
 * @details Attached to a parent JObj (joint/bone). A single JObj can hold a linked list
 * of DObjs. Each DObj binds material properties (MObj), geometry primitives (PObj chain),
 * optional animation drivers (AObj), and rendering state flags.
 */
struct HSD_DObj {
    HSD_Class parent; ///< Base class instance data
    HSD_DObj* next;   ///< Next sibling DObj in linked list (0x04)
    HSD_MObj* mobj;   ///< Material and texture attributes (0x08)
    HSD_PObj* pobj;   ///< Linked list of polygon primitives / display lists (0x0C)
    HSD_AObj* aobj;   ///< Animation object controlling visibility/properties (0x10)
    u32 flags;        ///< Render state and blending mode flags (0x14)
};

/**
 * @brief Descriptor structure for loading a DObj from archive data (DAT files).
 */
struct HSD_DObjDesc {
    char* class_name;       ///< Name of custom class to instantiate, or NULL for default
    HSD_DObjDesc* next;     ///< Next sibling DObj descriptor in archive
    HSD_MObjDesc* mobjdesc; ///< Material descriptor
    HSD_PObjDesc* pobjdesc; ///< Polygon primitive chain descriptor
};

/**
 * @brief Class information and virtual method table for HSD_DObj.
 */
struct HSD_DObjInfo {
    HSD_ClassInfo parent;                                              ///< Base class information
    void (*disp)(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode);  ///< Virtual display method (0x3C)
    int (*load)(HSD_DObj* dobj, HSD_DObjDesc* desc);                   ///< Virtual descriptor loader method (0x40)
};

/**
 * @brief Shape animation node linking vertex morph target animations to DObjs.
 */
struct HSD_ShapeAnimDObj {
    HSD_ShapeAnimDObj* next;   ///< Next shape animation node in chain
    HSD_ShapeAnim* shapeanim;  ///< Vertex shape / morph target animation data
};

#define HSD_DOBJ(o) ((HSD_DObj*) (o))
#define HSD_DOBJ_INFO(i) ((HSD_DObjInfo*) (i))
#define HSD_DOBJ_METHOD(o) HSD_DOBJ_INFO(HSD_CLASS_METHOD(o))

/**
 * @brief Sets the currently active DObj pointer.
 * @param dobj Pointer to the active HSD_DObj
 */
void HSD_DObjSetCurrent(HSD_DObj* dobj);

/**
 * @brief Retrieves the render and state flags of a DObj.
 * @param dobj Pointer to the HSD_DObj
 * @return Bitfield of flags, or 0 if dobj is NULL
 */
u32 HSD_DObjGetFlags(HSD_DObj* dobj);

/**
 * @brief Sets specific flag bits on a DObj.
 * @param dobj Pointer to the HSD_DObj
 * @param flags Bitmask of flags to set (bitwise OR)
 */
void HSD_DObjSetFlags(HSD_DObj* dobj, u32 flags);

/**
 * @brief Clears specific flag bits on a DObj.
 * @param dobj Pointer to the HSD_DObj
 * @param flags Bitmask of flags to clear (bitwise AND NOT)
 */
void HSD_DObjClearFlags(HSD_DObj* dobj, u32 flags);

/**
 * @brief Modifies a masked subset of flags on a DObj.
 * @param dobj Pointer to the HSD_DObj
 * @param flags New bit values to apply within the mask
 * @param mask Bitmask specifying which flags to modify
 */
void HSD_DObjModifyFlags(HSD_DObj* dobj, u32 flags, u32 mask);

/**
 * @brief Removes animations from a DObj matching specified flag bits.
 * @details If bit 1 (0x2) is set, detaches and frees the DObj's AObj.
 * Also removes matching animations across all attached PObjs and MObjs.
 * @param dobj Pointer to the HSD_DObj
 * @param flags Animation removal filter flags
 */
void HSD_DObjRemoveAnimByFlags(HSD_DObj* dobj, u32 flags);

/**
 * @brief Removes animations from an entire DObj sibling chain matching flags.
 * @param dobj Pointer to the head of the HSD_DObj chain
 * @param flags Animation removal filter flags
 */
void HSD_DObjRemoveAnimAllByFlags(HSD_DObj* dobj, u32 flags);

/**
 * @brief Attaches material and shape animations to a single DObj.
 * @param dobj Pointer to the HSD_DObj
 * @param mat_anim Pointer to material animation to attach to MObj
 * @param sh_anim Pointer to shape animation node to attach to PObj chain
 */
void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim,
                     HSD_ShapeAnimDObj* sh_anim);

/**
 * @brief Attaches parallel chains of material and shape animations to a DObj chain.
 * @param dobj Head of HSD_DObj linked list
 * @param matanim Head of HSD_MatAnim linked list
 * @param shapeanimdobj Head of HSD_ShapeAnimDObj linked list
 */
void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim,
                        HSD_ShapeAnimDObj* shapeanimdobj);

/**
 * @brief Requests animation playback start at a specific frame for matching flags.
 * @param dobj Pointer to the HSD_DObj
 * @param startframe Starting frame number for playback
 * @param flags Filter flags determining which animations to update
 */
void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, f32 startframe, u32 flags);

/**
 * @brief Requests animation playback across an entire DObj chain by flags.
 * @param dobj Head of HSD_DObj linked list
 * @param startframe Starting frame number for playback
 * @param flags Filter flags determining which animations to update
 */
void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, f32 startframe, u32 flags);

/**
 * @brief Requests animation playback across an entire DObj chain with all flags (0x7FF).
 * @param dobj Head of HSD_DObj linked list
 * @param startframe Starting frame number for playback
 */
void HSD_DObjReqAnimAll(HSD_DObj* dobj, f32 startframe);

/**
 * @brief Advances animation by one tick on a single DObj (PObjs and MObj).
 * @param dobj Pointer to the HSD_DObj
 */
void HSD_DObjAnim(HSD_DObj* dobj);

/**
 * @brief Advances animation by one tick across an entire DObj linked list.
 * @param dobj Head of HSD_DObj linked list
 */
void HSD_DObjAnimAll(HSD_DObj* dobj);

/**
 * @brief Instantiates and loads a DObj hierarchy from archive descriptor data.
 * @details Resolves the class info (or uses default DObj class), allocates memory,
 * and calls the virtual load method to populate child MObjs, PObjs, and sibling DObjs.
 * @param desc Pointer to the HSD_DObjDesc descriptor
 * @return Pointer to newly allocated HSD_DObj, or NULL if desc is NULL
 */
HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc);

/**
 * @brief Recursively frees an entire linked list of DObjs and their associated children.
 * @param dobj Head of HSD_DObj linked list to free
 */
void HSD_DObjRemoveAll(HSD_DObj* dobj);

/**
 * @brief Allocates an uninitialized HSD_DObj instance.
 * @return Pointer to newly allocated HSD_DObj
 */
HSD_DObj* HSD_DObjAlloc(void);

/**
 * @brief Resolves internal pointers and memory offsets for a DObj's PObj chain from descriptors.
 * @param dobj Pointer to the HSD_DObj
 * @param desc Pointer to the corresponding HSD_DObjDesc
 */
void HSD_DObjResolveRefs(HSD_DObj* dobj, HSD_DObjDesc* desc);

/**
 * @brief Resolves internal pointers and memory offsets across parallel DObj and descriptor chains.
 * @param dobj Head of HSD_DObj linked list
 * @param desc Head of HSD_DObjDesc linked list
 */
void HSD_DObjResolveRefsAll(HSD_DObj* dobj, HSD_DObjDesc* desc);

/**
 * @brief Dispatches GX display list rendering for a DObj.
 * @details Binds the DObj's material (MObj), sets up GX pipeline state, renders
 * all polygon primitives in the PObj chain, and restores material state.
 * @param dobj Pointer to the HSD_DObj to render
 * @param vmtx Camera view transform matrix
 * @param pmtx Joint/bone model-view transform matrix
 * @param rendermode Rendering mode and pipeline flags
 */
void HSD_DObjDisp(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode);

/**
 * @brief Frees a single HSD_DObj instance via the class system destructor.
 * @param dobj Pointer to the HSD_DObj to free
 */
void HSD_DObjRemove(HSD_DObj* dobj);

/**
 * @brief Sets the default class used when allocating new DObj instances.
 * @param info Pointer to HSD_ClassInfo (must inherit from hsdDObj)
 */
void HSD_DObjSetDefaultClass(HSD_ClassInfo* info);

/**
 * @brief Dummy function to force linker retention of assertion error strings in .rodata.
 * @param dobj Pointer to HSD_DObj
 * @param mobj Pointer to HSD_MObj
 */
void forceStringAllocation(HSD_DObj* dobj, HSD_MObj* mobj);

/// Global class descriptor and virtual method table for HSD_DObj
extern HSD_DObjInfo hsdDObj;

#endif
