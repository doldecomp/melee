/**
 * @file gobjproc.h
 * @brief Game Object Process (GObjProc) scheduling structures and management.
 * @details Represents an executable per-frame or event-driven task attached to an
 *          HSD_GObj. Processes are linked vertically to their owning GObj via child
 *          pointers and arranged horizontally across global priority tiers (s_link 0..2)
 *          via next/prev pointers for execution in HSD_GObj_RunProcs().
 * Module prefix: HSD_GObjProc / GObjProc (SysDolphin Base Library entity system)
 */

#ifndef SYSDOLPHIN_BASELIB_GOBJPROC_H
#define SYSDOLPHIN_BASELIB_GOBJPROC_H

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

/**
 * @brief Game Object Process node representing an executable callback task.
 * @details Each process belongs to an owning GObj and participates in a dual-linked
 *          topology: vertically attached to the GObj via child pointers, and horizontally
 *          threaded through global priority schedule queues via next/prev pointers.
 */
struct HSD_GObjProc {
    /* 0x00 */ HSD_GObjProc* child;        ///< Next process attached to the same owning GObj.
    /* 0x04 */ HSD_GObjProc* next;         ///< Next process in the global priority execution list.
    /* 0x08 */ HSD_GObjProc* prev;         ///< Previous process in the global priority execution list.
    /* 0x0C */ u8 s_link;                  ///< Execution priority tier (0..2; lower values execute earlier).
    /* 0x0D */ u8 flags_1 : 1;             ///< Primary suspend flag (1: suspended, 0: active).
    /* 0x0D */ u8 flags_2 : 1;             ///< Secondary suspend/freeze flag (1: frozen, 0: active).
    /* 0x0D */ u8 flags_3 : 2;             ///< Frame cycle parity tag (prevents duplicate execution per frame).
    /* 0x0D */ u8 flags_4 : 2;             ///< Reserved flags.
    /* 0x10 */ HSD_GObj* gobj;             ///< Pointer to owning Game Object container.
    /* 0x14 */ HSD_GObjEvent on_invoke;    ///< Callback function executed during process invocation.
};

/**
 * @brief Inserts a process into the global priority schedule list.
 * @details Determines insertion point within the s_link queue using the parent GObj's
 *          p_link ordering and the cached HSD_GObj_ProcList lookup table.
 * @param gproc Target process to queue.
 */
/* 38FAA8 */ void HSD_GObjProc_QueueProc(HSD_GObjProc* gproc);

/**
 * @brief Removes a process from the global priority schedule list.
 * @details Unlinks gproc from the horizontal next/prev chain and updates HSD_GObj_ProcList
 *          and HSD_GObj_GObjProcHead pointers.
 * @param gproc Target process to unqueue.
 */
/* 38FC18 */ void HSD_GObjProc_UnqueueProc(HSD_GObjProc* gproc);

/**
 * @brief Unlinks a process from both the global schedule and its parent GObj.
 * @param gproc Target process to unlink.
 */
/* 38FCE4 */ void HSD_GObjProc_UnlinkProcFromGObj(HSD_GObjProc* gproc);

/**
 * @brief Allocates and initializes a new process on a Game Object.
 * @param gobj Owning Game Object.
 * @param func Callback function to execute during updates.
 * @param pri Priority tier (s_link: 0..2).
 * @return Pointer to newly allocated HSD_GObjProc.
 */
/* 38FD54 */ HSD_GObjProc* HSD_GObj_SetupProc(HSD_GObj* gobj, HSD_GObjEvent func, u8 pri);

/**
 * @brief Removes and frees a process, deferring removal if currently running.
 * @param gproc Process to remove.
 */
/* 38FE24 */ void HSD_GObjProc_RemoveProc(HSD_GObjProc* gproc);

/**
 * @brief Removes and frees all processes attached to a Game Object.
 * @param gobj Owning Game Object whose processes will be cleared.
 */
/* 38FED4 */ void HSD_GObjProc_RemoveAllProcs(HSD_GObj* gobj);

#endif
