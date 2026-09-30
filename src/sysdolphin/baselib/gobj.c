/**
 * @file gobj.c
 * @brief Main Game Object execution loop and rendering dispatch.
 * @details Implements the core per-frame process scheduler (HSD_GObj_RunProcs),
 *          which updates all active entity callbacks across priority tiers, handles
 *          deferred lifecycle events (deletions and priority migrations), and drives
 *          multi-pass GX rendering traversals.
 * Module prefix: HSD_GObj / GObj (SysDolphin Base Library entity system)
 */

#include "gobj.h"

#include "fog.h"
#include "gobjplink.h"
#include "gobjproc.h"
#include "lobj.h"

/// 2D lookup table caching the tail proc for each (p_link, s_link) bucket.
HSD_GObjProc** HSD_GObj_ProcList;

/// Array of head pointers for each process priority tier (s_link 0..2).
HSD_GObjProc** HSD_GObj_GObjProcHead;

/// Frame cycle / parity counter (cycles 0 -> 1 -> 2 -> 0) preventing duplicate proc execution.
s32 HSD_GObj_804D783C;

/// Pointer to the currently executing process callback.
HSD_GObjProc* HSD_GObj_CurrentInvokedProc;

/// Current priority tier (s_link) being evaluated in HSD_GObj_RunProcs.
s32 HSD_GObj_CurrentInvokedSLink;

/// Next process to execute, preserved in case the current proc mutates the chain.
HSD_GObjProc* HSD_GObj_NextInvokedProc;

/// Array of head pointers for each process link group (0..63).
HSD_GObj** HSD_GObjPLinkHead;

/// Array of tail pointers for each process link group (0..63).
HSD_GObj** plinklow_gobjs;

/// Array of head pointers for each GX render link queue (0..64).
HSD_GObj** HSD_GObjGXLinkHead;

/// Array of tail pointers for each GX render link queue (0..64).
HSD_GObj** HSD_GObj_804D7820;

/// Pointer to the GObj owning the currently executing process.
HSD_GObj* HSD_GObj_CurrentInvokedProcGObj;

/// Pointer to the camera GObj currently executing in HSD_GObj_80390FC0.
HSD_GObj* HSD_GObj_804D7818;

/// Pointer to the GObj currently being rendered in render_gobj().
HSD_GObj* HSD_GObj_804D7814;

/// Array of registered object destructor callbacks.
GObjFunc* HSD_GObj_804D7810;

/**
 * @brief Mapping from render pass index to JObj display flags.
 * @details
 * - Pass 0: 1 = HSD_JOBJ_ALL / opaque geometry
 * - Pass 1: 4 = HSD_JOBJ_OPA / translucent geometry
 * - Pass 2: 2 = HSD_JOBJ_XLU / shadow / transparent geometry
 * - Pass 3: 0 = No display
 */
int HSD_GObj_804085F0[] = { 1, 4, 2, 0 };

/**
 * @brief Sets flags_1 on all processes attached to a GObj.
 * @param proc Head of the process child list.
 * @param value New value for flags_1 (1 = pause, 0 = resume).
 */
static inline void GObj_SetFlag1_inline(HSD_GObjProc* proc, u8 value)
{
    while (proc != NULL) {
        proc->flags_1 = value;
        proc = proc->child;
    }
}

/**
 * @brief Sets flags_2 on all processes attached to a GObj.
 * @param proc Head of the process child list.
 * @param value New value for flags_2.
 */
static inline void GObj_SetFlag2_inline(HSD_GObjProc* proc, u8 value)
{
    while (proc != NULL) {
        proc->flags_2 = value;
        proc = proc->child;
    }
}

/**
 * @brief Suspends all processes attached to a GObj by setting flags_1 = 1.
 * @param gobj Target Game Object.
 */
void HSD_GObj_80390C5C(HSD_GObj* gobj)
{
    GObj_SetFlag1_inline(gobj->proc, 1);
}

/**
 * @brief Resumes all processes attached to a GObj by clearing flags_1 = 0.
 * @param gobj Target Game Object.
 */
void HSD_GObj_80390C84(HSD_GObj* gobj)
{
    GObj_SetFlag1_inline(gobj->proc, 0);
}

/**
 * @brief Clears secondary pause flag (flags_2 = 0) on all processes attached to a GObj.
 * @param gobj Target Game Object.
 */
void HSD_GObj_80390CAC(HSD_GObj* gobj)
{
    GObj_SetFlag2_inline(gobj->proc, 0);
}

/**
 * @brief Sets process frame-parity flags to match current cycle counter.
 * @details Prevents the GObj's processes from running again during the current frame step.
 * @param gobj Target Game Object.
 */
void HSD_GObj_80390CD4(HSD_GObj* gobj)
{
    HSD_GObjProc* proc = gobj->proc;

    while (proc != NULL) {
        proc->flags_3 = HSD_GObj_804D783C;
        proc = proc->child;
    }
}

/**
 * @brief Main engine process scheduler; updates all active GObj processes for the frame.
 * @details Iterates through priority tiers (s_link 0..gproc_pri_max, typically 0..2)
 *          and traverses each linked list of HSD_GObjProc tasks. Checks global p_link pause
 *          masks (hitlag/freeze) and per-proc suspend flags. Handles deferred lifecycle
 *          mutations (HSD_GObj_DelayedProcInfo) triggered from within callbacks safely.
 */
void HSD_GObj_RunProcs(void)
{
    s32 s_link_pri;
    HSD_GObjProc* proc;
    HSD_GObj* gobj;

    // 64-bit bitmask of paused p_link groups (e.g. during hitlag, hitpause, or screen freeze)
    u64 pause_mask =
        HSD_GObjLibInitData.unk_2 != NULL ? *HSD_GObjLibInitData.unk_2 : 0;

    // Advance global frame cycle counter (mod 3: 0, 1, 2)
    HSD_GObj_804D783C += 1;
    if (HSD_GObj_804D783C > 2) {
        HSD_GObj_804D783C = 0;
    }

    // Traverse process priority tiers (0: highest/pre-update, 1: standard update, 2: post-update)
    for (s_link_pri = 0; s_link_pri <= HSD_GObjLibInitData.gproc_pri_max; s_link_pri++) {
        HSD_GObj_CurrentInvokedSLink = s_link_pri;
        proc = HSD_GObj_GObjProcHead[s_link_pri];
        while (proc != NULL) {
            HSD_GObj_NextInvokedProc = proc->next;

            // Only run if proc has not already been executed during this frame cycle
            if (proc->flags_3 != HSD_GObj_804D783C) {
                proc->flags_3 = HSD_GObj_804D783C;
                gobj = proc->gobj;

                // Check group pause bitmask and individual proc suspension flags
                if (!(pause_mask & (1LL << gobj->p_link)) && !(proc->flags_1) &&
                    !(proc->flags_2))
                {
                    HSD_GObj_CurrentInvokedProcGObj = gobj;
                    HSD_GObj_CurrentInvokedProc = proc;

                    // Execute process callback
                    proc->on_invoke(proc->gobj);

                    HSD_GObj_NextInvokedProc = proc->next;

                    // Handle deferred mutations requested while callback was active
                    if (HSD_GObj_DelayedProcInfo.x0.flags != 0) {
                        HSD_GObj_DelayedProcInfo.x0.x0.in_delayed_proc = 1;

                        if (HSD_GObj_DelayedProcInfo.x0.x0.delay_remove_gobj) {
                            // Deferred GObj destruction
                            HSD_GObjFree(proc->gobj);
                        } else {
                            if (HSD_GObj_DelayedProcInfo.x0.x0
                                    .delay_change_gobj_pri)
                            {
                                // Deferred priority / p_link migration
                                HSD_GObjPLink_ChangeGObjPri_Unk(
                                    HSD_GObj_DelayedProcInfo.type, proc->gobj,
                                    HSD_GObj_DelayedProcInfo.p_link,
                                    HSD_GObj_DelayedProcInfo.p_prio,
                                    HSD_GObj_DelayedProcInfo.gobj);
                            }
                            if (HSD_GObj_DelayedProcInfo.x0.x0
                                    .delay_remove_proc)
                            {
                                // Deferred proc removal
                                HSD_GObjProc_RemoveProc(proc);
                            }
                        }
                        HSD_GObj_DelayedProcInfo.x0.flags = 0;
                    }
                    HSD_GObj_CurrentInvokedProcGObj = NULL;
                    HSD_GObj_CurrentInvokedProc = NULL;
                }
            }
            proc = HSD_GObj_NextInvokedProc;
        }
    }
}

/**
 * @brief Retrieves JObj display flags for a given render pass.
 * @param i Render pass index (0..3).
 * @return Display flags (1: All/Opa, 4: Opa, 2: Xlu, 0: None).
 */
u32 HSD_GObj_80390EB8(s32 i)
{
    return HSD_GObj_804085F0[i];
}

/**
 * @brief Invokes the render callback of a GObj, preserving the current rendering context.
 * @param cur Target Game Object to render.
 * @param i Render pass index.
 */
static inline void render_gobj(HSD_GObj* cur, int i)
{
    HSD_GObj* saved = HSD_GObj_804D7814;
    HSD_GObj_804D7814 = cur;
    cur->render_cb(cur, i);
    HSD_GObj_804D7814 = saved;
}

/**
 * @brief Renders all GX link groups enabled in a camera GObj's priority mask.
 * @details For each pass bit set in mask, iterates through active GX link groups (0..63)
 *          enabled by gobj->gxlink_prios, and invokes render callbacks for all GObjs in each group.
 * @param gobj Camera Game Object containing the gxlink_prios bitmask.
 * @param mask Bitmask of render passes to execute (e.g. 7 = passes 0, 1, 2).
 */
void HSD_GObj_80390ED0(HSD_GObj* gobj, u32 mask)
{
    s32 pass_idx = 0;
    while (mask) {
        if (mask & 1) {
            u64 link_mask = gobj->gxlink_prios;
            s32 link_idx = 0;
            while (link_mask) {
                if (link_mask & 1) {
                    HSD_GObj* curr_gobj;
                    for (curr_gobj = HSD_GObjGXLinkHead[link_idx]; curr_gobj != NULL;
                         curr_gobj = curr_gobj->next_gx)
                    {
                        if (curr_gobj->render_cb != NULL) {
                            render_gobj(curr_gobj, pass_idx);
                        }
                    }
                }
                link_idx++;
                link_mask >>= 1;
            }
        }
        pass_idx++;
        mask >>= 1;
    }
}

/**
 * @brief Executes render callbacks for all camera GObjs in the max GX link group.
 * @details Iterates through HSD_GObjGXLinkHead[gx_link_max + 1] and invokes each
 *          camera's render callback (typically HSD_GObj_803910D8), which in turn
 *          initiates multi-pass rendering for scene objects via HSD_GObj_80390ED0.
 */
void HSD_GObj_80390FC0(void)
{
    HSD_GObj* saved_camera_gobj;
    HSD_GObj* curr_gobj = HSD_GObjGXLinkHead[HSD_GObjLibInitData.gx_link_max + 1];
    while (curr_gobj != NULL) {
        if (curr_gobj->render_cb != NULL) {
            saved_camera_gobj = HSD_GObj_804D7818;
            HSD_GObj_804D7818 = curr_gobj;
            curr_gobj->render_cb(curr_gobj, 0);
            HSD_GObj_804D7818 = saved_camera_gobj;
        }
        curr_gobj = curr_gobj->next_gx;
    }
}

struct _unk_gobj_struct HSD_GObj_DelayedProcInfo;
HSD_ObjAllocData gobjproc_alloc_data;
HSD_ObjAllocData gobj_alloc_data;
HSD_GObjLibInitDataType HSD_GObjLibInitData;
