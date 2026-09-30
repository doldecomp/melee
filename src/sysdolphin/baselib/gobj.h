/**
 * @file gobj.h
 * @brief Core Game Object (GObj) entity structure and management definitions.
 * @details Defines the universal HSD_GObj container struct representing all dynamic
 *          game entities in Super Smash Bros. Melee (fighters, items, cameras, lights,
 *          stages, effects, and HUD/UI elements). GObjs link logic update processes
 *          (HSD_GObjProc), render queues (GX links), 3D scene graph nodes (HSD_JObj,
 *          HSD_CObj, HSD_LObj, HSD_Fog), and high-level gameplay state (user_data).
 * Module prefix: HSD_GObj / GObj (SysDolphin Base Library entity system)
 */

#ifndef GALE01_390730
#define GALE01_390730

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/objalloc.h>

/// Sentinel indicating that a GObj is not assigned to any GX render queue.
#define HSD_GOBJ_GXLINK_NONE ((u8) 0xFF)

/// Sentinel indicating no HSD 3D engine object is attached.
#define HSD_GOBJ_OBJ_NONE 0xFF

/// Maximum process link group index (0..63, fits in a 64-bit bitmask).
#define HSD_GOBJ_PLINK_MAX 63

/// Maximum standard GX render link group index (0..63). Index 64 is reserved for cameras.
#define HSD_GOBJ_GX_LINK_MAX 63

/// Maximum process priority level index (0, 1, 2).
#define HSD_GOBJPROC_PRI_MAX 2

/**
 * @brief Universal Game Object container for all runtime entities.
 * @details Every interactive or rendered entity in Melee (Fighter, Item, Camera,
 *          Stage, Particle, etc.) is represented by an HSD_GObj instance.
 */
typedef struct HSD_GObj {
    /*  +0 */ u16 classifier;            ///< Classification tag (e.g. fighter, item, camera).
    /*  +2 */ u8 p_link;                 ///< Process link bucket index (0..63) for logic execution order.
    /*  +3 */ u8 gx_link;                ///< GX render link bucket index (0..63, or 0xFF if unlinked).
    /*  +4 */ u8 p_priority;             ///< Priority within p_link group (lower values execute earlier).
    /*  +5 */ u8 render_priority;        ///< Priority within gx_link group (lower values draw earlier).
    /*  +6 */ u8 obj_kind;               ///< Attached HSD object type (Camera, Light, JObj, Fog).
    /*  +7 */ u8 user_data_kind;         ///< User data type identifier.
    /*  +8 */ HSD_GObj* next;            ///< Next GObj in the same process link group.
    /*  +C */ HSD_GObj* prev;            ///< Previous GObj in the same process link group.
    /* +10 */ HSD_GObj* next_gx;         ///< Next GObj in the same GX render link group.
    /* +14 */ HSD_GObj* prev_gx;         ///< Previous GObj in the same GX render link group.
    /* +18 */ HSD_GObjProc* proc;        ///< Head of attached logic process list (linked via child).
    /* +1C */ GObj_RenderFunc render_cb; ///< Rendering callback function invoked during GX pass.
    /* +20 */ u64 gxlink_prios;          ///< Bitmask of GX link buckets to render (used by cameras).
    /* +28 */ void* hsd_obj;             ///< Pointer to attached HSD engine object (HSD_JObj, HSD_CObj, etc.).
    /* +2C */ void* user_data;           ///< Pointer to gameplay entity data (e.g. Fighter*, Item*).
    /* +30 */ void (*user_data_remove_func)(void* data); ///< Destructor callback for user_data.
    /* +34 */ void* x34_unk;             ///< Reserved / unused pointer.
} HSD_GObj;

/// Function pointer type for HSD object lifecycle handlers.
typedef void (*GObjFunc)(HSD_Obj*);

/**
 * @brief Table of object lifecycle callbacks for registered engine object types.
 */
struct GObjFuncs {
    struct GObjFuncs* next; ///< Next table in the registry linked list.
    u8 size;                ///< Number of function pointers in funcs array.
    GObjFunc* funcs;        ///< Array of object lifecycle function pointers.
};

/**
 * @brief Initialization parameters for the SysDolphin GObj subsystem.
 */
typedef struct _HSD_GObjLibInitDataType {
    u8 p_link_max;    ///< Maximum process link index (default 63). 804CE380
    u8 gx_link_max;   ///< Maximum GX render link index (default 63). 804CE381
    u8 gproc_pri_max; ///< Maximum process priority tier (default 2). 804CE382
    GObjFuncs* funcs; ///< Registered object lifecycle handlers. 804CE384
    u64* unk_2;       ///< Pointer to 64-bit pause/freeze bitmask for p_links. 804CE388
} HSD_GObjLibInitDataType;

/**
 * @brief Global tracking structure for deferred mutations requested during proc execution.
 * @details Prevents list corruption when callbacks delete GObjs, remove procs, or change
 *          priorities while the scheduler is traversing the active process list.
 */
extern struct _unk_gobj_struct {
    union _unk_gobj_struct_x0 {
        u32 flags;
        struct _unk_gobj_struct_x0_x0 {
            u32 in_delayed_proc : 1;       ///< Set when currently executing a deferred action.
            u32 delay_remove_gobj : 1;     ///< Deferred GObj deletion requested.
            u32 delay_remove_proc : 1;     ///< Deferred proc removal requested.
            u32 delay_change_gobj_pri : 1; ///< Deferred GObj priority change requested.
        } x0;
    } x0;
    u32 type;       ///< Insertion type for deferred priority change.
    u8 p_link;      ///< New process link group for deferred priority change.
    u8 p_prio;      ///< New priority within group for deferred priority change.
    HSD_GObj* gobj; ///< Target reference GObj for relative repositioning.
} HSD_GObj_DelayedProcInfo;

extern GObjFunc* HSD_GObj_804D7810;
extern HSD_GObj* HSD_GObj_804D7814;
extern HSD_GObj* HSD_GObj_804D7818;
extern HSD_GObj* HSD_GObj_CurrentInvokedProcGObj;
extern HSD_GObj** HSD_GObj_804D7820;
extern HSD_GObj** HSD_GObjGXLinkHead;
extern HSD_GObj** plinklow_gobjs;
extern HSD_GObj** HSD_GObjPLinkHead;
extern HSD_GObjProc* HSD_GObj_NextInvokedProc;
extern s32 HSD_GObj_CurrentInvokedSLink;
extern HSD_GObjProc* HSD_GObj_CurrentInvokedProc;
extern s32 HSD_GObj_804D783C;
extern HSD_GObjProc** HSD_GObj_GObjProcHead;
extern HSD_GObjProc** HSD_GObj_ProcList;
extern s8 HSD_GObj_FogKind;
extern u8 HSD_GObj_JObjKind;
extern s8 HSD_GObj_LightKind;
extern u8 HSD_GObj_CameraKind;
extern HSD_ObjAllocData gobj_alloc_data;
extern HSD_ObjAllocData gobjproc_alloc_data;

extern HSD_GObjLibInitDataType HSD_GObjLibInitData;

/**
 * @brief Suspends all processes attached to a GObj by setting flags_1 = 1.
 * @param gobj Target Game Object.
 */
void HSD_GObj_80390C5C(HSD_GObj* gobj);

/**
 * @brief Resumes all processes attached to a GObj by clearing flags_1 = 0.
 * @param gobj Target Game Object.
 */
void HSD_GObj_80390C84(HSD_GObj* gobj);

/**
 * @brief Clears secondary pause flag (flags_2 = 0) on all processes attached to a GObj.
 * @param gobj Target Game Object.
 */
void HSD_GObj_80390CAC(HSD_GObj* gobj);

/**
 * @brief Maps a render pass index (0..3) to JObj display flags.
 * @param i Render pass index (0: All/Opaque, 1: Translucent, 2: Shadow/XLU, 3: None).
 * @return Bitmask of HSD_JOBJ_DISP_* flags.
 */
u32 HSD_GObj_80390EB8(s32 i);

/**
 * @brief Camera GObj render callback; sets current CObj and triggers GX passes.
 * @param gobj Camera Game Object.
 * @param renderpass Render pass index / flag.
 */
void HSD_GObj_803910D8(HSD_GObj* gobj, intptr_t renderpass);

/**
 * @brief Registers a table of object lifecycle callbacks in the GObj library.
 * @param init_data GObj library initialization data structure.
 * @param funcs Table of object lifecycle callbacks to register.
 * @return Starting kind index assigned to this function table.
 */
u8 HSD_GObj_803912A8(HSD_GObjLibInitDataType* init_data, GObjFuncs* funcs);

/**
 * @brief Creates a new Game Object and appends it to its priority group.
 * @param classifier Entity classification tag.
 * @param p_link Process link group index (0..63).
 * @param priority Execution priority within the process link group.
 * @return Pointer to newly allocated HSD_GObj, or NULL if pool is exhausted.
 */
HSD_GObj* GObj_Create(u16 classifier, u8 p_link, u8 priority);

/**
 * @brief Default JObj rendering callback; invokes HSD_JObjDispAll for the attached JObj.
 * @param gobj Game Object with attached HSD_JObj.
 * @param arg1 Render pass index mapped via HSD_GObj_80390EB8.
 */
void HSD_GObj_JObjCallback(HSD_GObj* gobj, intptr_t arg1);

/**
 * @brief Synchronizes process frame-parity flags with current global cycle count.
 * @param gobj Target Game Object whose processes will be updated.
 */
void HSD_GObj_80390CD4(HSD_GObj* gobj);

/**
 * @brief Main engine process scheduler; executes all active GObj processes for the frame.
 * @details Iterates through priority tiers (s_link 0..2) and processes, checking pause
 *          masks and frame parity flags, then invokes each process callback while handling
 *          deferred mutations (deletion, priority changes).
 */
void HSD_GObj_RunProcs(void);

/**
 * @brief Executes render callbacks for all camera GObjs in the max GX link group.
 * @details Iterates through HSD_GObjGXLinkHead[gx_link_max + 1] and invokes render_cb,
 *          typically triggering camera scene rendering passes via HSD_GObj_803910D8.
 */
void HSD_GObj_80390FC0(void);

/**
 * @brief LObj setup callback for Light Game Objects.
 * @param gobj Light Game Object.
 * @param unused Unused parameter.
 */
void HSD_GObj_LObjCallback(HSD_GObj* gobj, intptr_t unused);

/**
 * @brief Fog setup callback for Fog Game Objects.
 * @param gobj Fog Game Object.
 * @param unused Unused parameter.
 */
void HSD_GObj_FogCallback(HSD_GObj* gobj, intptr_t unused);

/**
 * @brief Releases a reference to an HSD object and frees it if refcount reaches zero.
 * @param obj Target HSD object.
 */
void HSD_GObj_80391120(HSD_Obj* obj);

/**
 * @brief Destructor callback for HSD objects attached to GObjs.
 * @param obj Target HSD object.
 */
void HSD_GObj_803911C0(HSD_Obj* obj);

/**
 * @brief Registers default built-in object types (Camera, Light, JObj, Fog).
 * @param init_data GObj library initialization data structure.
 */
void HSD_GObj_80391260(HSD_GObjLibInitDataType* init_data);

/**
 * @brief Populates default initialization parameters for the GObj library.
 * @param init_data Output pointer to receive default parameters.
 */
void HSD_GObjSetInitDefaults(HSD_GObjLibInitDataType* init_data);

/**
 * @brief Renders all GX link groups enabled in the GObj's priority mask across specified passes.
 * @param gobj Camera Game Object containing the gxlink_prios bitmask.
 * @param mask Bitmask of render passes to execute (typically 7 = 0b111 for 3 passes).
 */
void HSD_GObj_80390ED0(HSD_GObj* gobj, u32 mask);

/**
 * @brief Initializes the SysDolphin GObj entity subsystem.
 * @details Allocates process link tables, GX render link tables, process priority lists,
 *          and memory pools for HSD_GObj and HSD_GObjProc allocations.
 * @param init_data Subsystem configuration parameters.
 */
void HSD_GObjInit(HSD_GObjLibInitDataType* init_data);

/**
 * @brief Retrieves the user data pointer attached to a GObj.
 * @param gobj Target Game Object.
 * @return Pointer to gameplay entity data (e.g. Fighter*, Item*).
 */
static inline void* HSD_GObjGetUserData(HSD_GObj* gobj)
{
    return gobj->user_data;
}

/**
 * @brief Retrieves the HSD engine object attached to a GObj.
 * @param gobj Target Game Object.
 * @return Pointer to engine object (e.g. HSD_JObj*, HSD_CObj*).
 */
static inline void* HSD_GObjGetHSDObj(HSD_GObj* gobj)
{
    return gobj->hsd_obj;
}

/**
 * @brief Retrieves the classification identifier of a GObj.
 * @param gobj Target Game Object.
 * @return Entity classifier ID.
 */
static inline u16 HSD_GObjGetClassifier(HSD_GObj* gobj)
{
    return gobj->classifier;
}

/**
 * @brief Retrieves the next GObj in the same process link group.
 * @param gobj Target Game Object.
 * @return Pointer to next HSD_GObj in the linked list.
 */
static inline HSD_GObj* HSD_GObjGetNext(HSD_GObj* gobj)
{
    return gobj->next;
}

/// Convenience macro to cast attached engine object to HSD_CObj*.
#define GET_COBJ(gobj) ((HSD_CObj*) HSD_GObjGetHSDObj(gobj))

/// Convenience macro to cast attached engine object to HSD_Fog*.
#define GET_FOG(gobj) ((HSD_Fog*) HSD_GObjGetHSDObj(gobj))

/// Convenience macro to cast attached engine object to HSD_JObj*.
#define GET_JOBJ(gobj) ((HSD_JObj*) HSD_GObjGetHSDObj(gobj))

/// Convenience macro to cast attached engine object to HSD_LObj*.
#define GET_LOBJ(gobj) ((HSD_LObj*) HSD_GObjGetHSDObj(gobj))

#endif
