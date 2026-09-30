/**
 * @file gobjproc.c
 * @brief Game Object Process (GObjProc) scheduling management.
 * @details Implements insertion, unlinking, allocation, and deletion for
 *          HSD_GObjProc tasks. Handles priority sorting within s_link tiers
 *          and deferred task removal during active execution loops.
 * Module prefix: HSD_GObjProc / GObjProc (SysDolphin Base Library entity system)
 */

#include "gobjproc.h"

#include "debug.h"
#include "gobj.h"
#include "objalloc.h"

/**
 * @brief Inserts a GObjProc into the global priority schedule list.
 * @details Finds the correct insertion position within the s_link priority tier.
 *          It first checks the cached proc in HSD_GObj_ProcList for the parent GObj's
 *          p_link. If present, it scans backwards through predecessor GObjs to insert
 *          after the latest proc of the same s_link. Otherwise, it searches earlier
 *          p_link groups. If no predecessor is found, it inserts at the head of the
 *          s_link tier (HSD_GObj_GObjProcHead[s_link]). Finally, it prepends the proc
 *          to its parent GObj's child list.
 * @param gproc Target process to queue.
 */
void HSD_GObjProc_QueueProc(HSD_GObjProc* gproc)
{
    HSD_GObj* proc_gobj;
    HSD_GObjProc* dst_proc;
    u8 s_link;
    int p_link;

    proc_gobj = gproc->gobj;
    s_link = gproc->s_link;
    p_link = proc_gobj->p_link;

    // Scan through this GObjProc until we find a destination GObjProc
    // with the same s_link where we can insert it.
    //
    // Start at the current proc's GObj, and scan backwards through
    // all previous GObjs' procs.
    if (HSD_GObj_ProcList[p_link + s_link * (HSD_GObjLibInitData.p_link_max +
                                             1)] != NULL)
    {
        HSD_GObj* cur_gobj = proc_gobj;
        while (cur_gobj != NULL) {
            dst_proc = cur_gobj->proc;
            while (dst_proc != NULL) {
                if (dst_proc->s_link == s_link) {
                    if (HSD_GObj_ProcList[p_link +
                                          s_link *
                                              (HSD_GObjLibInitData.p_link_max +
                                               1)] == dst_proc)
                    {
                        HSD_GObj_ProcList[p_link +
                                          s_link *
                                              (HSD_GObjLibInitData.p_link_max +
                                               1)] = gproc;
                    }
                    goto insert_at_dst;
                }
                dst_proc = dst_proc->child;
            }
            cur_gobj = cur_gobj->prev;
        }
    } else {
        HSD_GObj_ProcList[p_link + s_link * (HSD_GObjLibInitData.p_link_max +
                                             1)] = gproc;
    }

    // If we got here, we still don't have a destination,
    // so scan through earlier p_link buckets for a preceding proc.
    while (p_link-- != 0) {
        dst_proc =
            HSD_GObj_ProcList[p_link +
                              s_link * (HSD_GObjLibInitData.p_link_max + 1)];
        if (dst_proc != NULL) {
            goto insert_at_dst;
        }
    }

    // If no predecessor was found, insert at the head of the global s_link priority list.
    if (true) {
        gproc->next = HSD_GObj_GObjProcHead[s_link];
        HSD_GObj_GObjProcHead[s_link] = gproc;
        gproc->prev = NULL;
    } else {
        // Alternatively, jump here when a predecessor destination was located in the chain.
    insert_at_dst:
        gproc->next = dst_proc->next;
        dst_proc->next = gproc;
        gproc->prev = dst_proc;
    }

    // Maintain reverse linked-list pointer
    if (gproc->next != NULL) {
        gproc->next->prev = gproc;
    }

    // Prepend proc to the owning GObj's vertical child list
    gproc->child = proc_gobj->proc;
    proc_gobj->proc = gproc;

    // If inserting into the currently executing chain during a deferred mutation,
    // update HSD_GObj_NextInvokedProc so the new proc executes next in sequence.
    if (HSD_GObj_DelayedProcInfo.x0.x0.in_delayed_proc &&
        gproc->prev == HSD_GObj_CurrentInvokedProc &&
        gproc->next == HSD_GObj_NextInvokedProc &&
        s_link == HSD_GObj_CurrentInvokedSLink)
    {
        HSD_GObj_NextInvokedProc = gproc;
    }
}

/**
 * @brief Removes a process from the global horizontal priority schedule list.
 * @details Unlinks gproc from next/prev pointers in the s_link queue, updates the
 *          head pointer if gproc was at the front, and updates the cached HSD_GObj_ProcList
 *          bucket entry.
 * @param gproc Target process to unqueue.
 */
void HSD_GObjProc_UnqueueProc(HSD_GObjProc* gproc)
{
    int p_link = gproc->gobj->p_link;
    int s_link = gproc->s_link;

    // Advance next invoked proc if gproc was slated to run next
    if (HSD_GObj_DelayedProcInfo.x0.x0.in_delayed_proc &&
        gproc == HSD_GObj_NextInvokedProc)
    {
        HSD_GObj_NextInvokedProc = gproc->next;
    }

    // If gproc was cached as the tail proc for its (p_link, s_link) bucket, update cache
    if (gproc ==
        HSD_GObj_ProcList[p_link +
                          s_link * (HSD_GObjLibInitData.p_link_max + 1)])
    {
        if (gproc->prev != NULL && gproc->prev->gobj->p_link == p_link) {
            HSD_GObj_ProcList[p_link +
                              s_link * (HSD_GObjLibInitData.p_link_max + 1)] =
                gproc->prev;
        } else {
            HSD_GObj_ProcList[p_link +
                              s_link * (HSD_GObjLibInitData.p_link_max + 1)] =
                NULL;
        }
    }

    // Unlink from horizontal chain
    if (gproc->prev != NULL) {
        gproc->prev->next = gproc->next;
    } else {
        HSD_GObj_GObjProcHead[s_link] = gproc->next;
    }
    if (gproc->next != NULL) {
        gproc->next->prev = gproc->prev;
    }
}

/**
 * @brief Unlinks a process from both the global schedule and its parent GObj.
 * @param gproc Target process to unlink.
 */
void HSD_GObjProc_UnlinkProcFromGObj(HSD_GObjProc* gproc)
{
    HSD_GObj* gobj = gproc->gobj;
    HSD_GObjProc_UnqueueProc(gproc);

    // Unlink from owning GObj's vertical child chain
    if (gobj->proc == gproc) {
        gobj->proc = gproc->child;
    } else {
        HSD_GObjProc* curr_proc = gobj->proc;
        while (curr_proc->child != gproc) {
            curr_proc = curr_proc->child;
        }
        curr_proc->child = gproc->child;
    }
}

/**
 * @brief Inline assertion verifying that a process allocation succeeded.
 * @param gproc Allocated process pointer to check.
 */
static inline void assertProc(HSD_GObjProc* gproc)
{
    HSD_ASSERT(31, gproc);
}

/**
 * @brief Allocates and initializes a new process on a Game Object.
 * @param gobj Owning Game Object container.
 * @param func Callback function to execute when invoked.
 * @param pri Priority tier (s_link: 0..2).
 * @return Pointer to newly allocated and queued HSD_GObjProc.
 */
HSD_GObjProc* HSD_GObj_SetupProc(HSD_GObj* gobj, HSD_GObjEvent func, u8 pri)
{
    HSD_GObjProc* gproc;

    u8 _[8];

    gproc = HSD_ObjAlloc(&gobjproc_alloc_data);
    assertProc(gproc);
    HSD_ASSERT(216, pri <= HSD_GObjLibInitData.gproc_pri_max);
    gproc->s_link = pri;
    gproc->flags_1 = gproc->flags_2 = 0;
    gproc->flags_3 = 3; // Initial sentinel parity, distinct from frame cycle 0, 1, 2
    gproc->gobj = gobj;
    gproc->on_invoke = func;
    HSD_GObjProc_QueueProc(gproc);
    return gproc;
}

/**
 * @brief Removes and frees a process node.
 * @details If the process is currently being executed by HSD_GObj_RunProcs, deletion
 *          is deferred (via HSD_GObj_DelayedProcInfo) to prevent list corruption.
 * @param gproc Process to remove.
 */
void HSD_GObjProc_RemoveProc(HSD_GObjProc* gproc)
{
    if (!HSD_GObj_DelayedProcInfo.x0.x0.in_delayed_proc &&
        gproc == HSD_GObj_CurrentInvokedProc)
    {
        // Defer removal until on_invoke returns
        HSD_GObj_DelayedProcInfo.x0.x0.delay_remove_proc = true;
    } else {
        HSD_GObjProc_UnlinkProcFromGObj(gproc);
        HSD_ObjFree(&gobjproc_alloc_data, gproc);
    }
}

/**
 * @brief Removes and frees all processes attached to a Game Object.
 * @param gobj Owning Game Object whose processes will be cleared.
 */
void HSD_GObjProc_RemoveAllProcs(HSD_GObj* gobj)
{
    HSD_GObjProc* curr_proc = gobj->proc;
    while (curr_proc != NULL) {
        HSD_GObjProc* next_child = curr_proc->child;
        HSD_GObjProc_RemoveProc(curr_proc);
        curr_proc = next_child;
    }
}
