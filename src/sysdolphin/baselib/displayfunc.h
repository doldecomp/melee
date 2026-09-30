/**
 * @file displayfunc.h
 * @brief Scene graph and JObj rendering dispatch functions
 * @details Manages the rendering pipeline, Z-sorting (translucent objects), and GX state setup for drawing.
 */
#ifndef INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H
#define INCLUDE_SYSDOLPHIN_BASELIB_DISPLAYFUNC_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <sysdolphin/baselib/jobj.h>

#define DOBJ_TRSP_SHIFT 1
#define JOBJ_TRSP_SHIFT 18

#define JOBJ_OPA 0x40000
#define JOBJ_XLU 0x80000
#define JOBJ_TEXEDGE 0x100000

/**
 * @brief Clears the internal Z-List memory and pointers.
 * @param lo Lower memory bound (unused)
 * @param hi Upper memory bound (unused)
 */
void _HSD_DispForgetMemory(void* lo, void* hi);
/**
 * @brief Initializes the allocator data for Z-List entries.
 */
void HSD_ZListInitAllocData(void);

/**
 * @brief Draws a full-screen quad to manually clear the frame/depth buffer.
 * @param top_res Top bound
 * @param bottom_res Bottom bound
 * @param left_res Left bound
 * @param right_res Right bound
 * @param neg_z_val Z depth
 * @param enable_color Whether to write to the color buffer
 * @param enable_alpha Whether to write to the alpha buffer
 * @param enable_depth Whether to write to the depth buffer
 */
void HSD_EraseRect(f32 top_res, f32 bottom_res, f32 left_res, f32 right_res,
                   f32 neg_z_val, int enable_color, int enable_alpha,
                   int enable_depth);

/**
 * @brief Calculates and assigns the final position matrix for a JObj, applying billboard logic if necessary.
 * @param jobj The JObj
 * @param vmtx The view matrix
 * @param pmtx The projection matrix
 */
void HSD_JObjMakePositionMtx(HSD_JObj* jobj, Mtx vmtx, Mtx pmtx);
/**
 * @brief Computes the node matrix for an envelope skinning JObj relative to its skeleton root.
 * @param m The JObj
 * @param mtx Output matrix pointer
 * @return Pointer to the populated matrix, or NULL if root
 */
MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx);
/**
 * @brief Main dispatch function to render a JObj (DObjs or particle nodes) with the specified transparency pass.
 * @param jobj The JObj to render
 * @param vmtx The view matrix
 * @param flags Transparency mask to filter which objects are drawn
 * @param rendermode Rendering mode flags
 */
void HSD_JObjDisp(HSD_JObj* jobj, MtxPtr, HSD_TrspMask flags, u32 rendermode);
/**
 * @brief Directly renders the DObjs associated with a JObj.
 * @param jobj The JObj
 * @param vmtx The view matrix
 * @param pmtx The projection matrix
 * @param trsp_mask Transparency mask
 * @param rendermode Rendering mode flags
 */
void HSD_JObjDispSub(HSD_JObj* jobj, MtxPtr vmtx, MtxPtr pmtx,
                     HSD_TrspMask trsp_mask, u32 rendermode);
/**
 * @brief Displays the DObjs attached to a JObj, routing them to the direct pass or Z-List based on transparency.
 * @param jobj The JObj
 * @param vmtx The view matrix
 * @param trsp_mask Transparency mask
 * @param rendermode Rendering mode flags
 */
void HSD_JObjDispDObj(HSD_JObj* jobj, MtxPtr vmtx, HSD_TrspMask trsp_mask,
                      u32 rendermode);

/**
 * @brief Walks up the JObj hierarchy to find the root skeleton node.
 * @param jobj The starting JObj
 * @return The root skeleton JObj, or NULL if not found
 */
HSD_JObj* HSD_JObjFindSkeleton(HSD_JObj* jobj);

/**
 * @brief Initializes the GX hardware state for direct rendering.
 * @param vtxfmt Vertex format index
 * @param rendermode Rendering mode flags
 */
void HSD_StateInitDirect(int vtxfmt, u32 rendermode);

/**
 * @brief Sorts the queued Z-List objects by depth.
 */
void _HSD_ZListSort(void);
/**
 * @brief Dispatches rendering for all objects currently in the sorted Z-List.
 */
void _HSD_ZListDisp(void);
/**
 * @brief Clears the Z-List and frees associated allocations.
 */
void _HSD_ZListClear(void);

/**
 * @brief Sets the global callback used for rendering particle JObjs.
 * @param func The callback function
 */
void HSD_JObjSetSPtclCallback(void (*func)(s32, s32, s32, HSD_JObj*));

/**
 * @brief Sets the erase color used by HSD_EraseRect.
 * @param r Red component
 * @param g Green component
 * @param b Blue component
 * @param a Alpha component
 */
void HSD_SetEraseColor(u8 r, u8 g, u8 b, u8 a);

#endif
