/**
 * @file robj.h
 * @brief Reference/Constraint Object (RObj) subsystem for SysDolphin
 * @details Implements constraint objects and effectors used for Inverse Kinematics (IK).
 * Defines bone chain endpoints, angular limits, and position targets that the JObj IK solver 
 * uses to procedurally position limbs. Supports bytecode evaluation for complex constraints.
 */
#ifndef _robj_h_
#define _robj_h_

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h> // IWYU pragma: export

#include <dat_macros.h>

#include <dolphin/mtx.h>
#include <sysdolphin/baselib/objalloc.h>

#define ROBJ_TYPE_MASK 0x70000000
#define REFTYPE_EXP 0x00000000
#define REFTYPE_JOBJ 0x10000000
#define REFTYPE_LIMIT 0x20000000
#define REFTYPE_BYTECODE 0x30000000
#define REFTYPE_IKHINT 0x40000000

struct HSD_Rvalue {
    HSD_Rvalue* next;
    u32 flags;
    HSD_JObj* jobj;
};

struct HSD_RvalueList {
    u32 flags;
    HSD_Joint* joint;
};

struct HSD_IKHint {
    f32 bone_length;
    f32 rotate_x;
};

struct HSD_IKHintDesc {
    f32 bone_length;
    f32 rotate_x;
};

struct HSD_Exp {
    union HSD_Exp_expr {
        f32 (*func)(void*);
        u8* bytecode;
    } expr;
    HSD_Rvalue* rvalue;
    u32 nb_args;
    u8 is_bytecode;
};

struct HSD_ExpDesc {
    f32 (*func)(void*);
    HSD_RvalueList* rvalue;
};

struct HSD_ByteCodeExpDesc {
    u8* bytecode;
    HSD_RvalueList* rvalue;
};

struct HSD_RObj {
    HSD_RObj* next;
    u32 flags;
    union HSD_RObj_u {
        HSD_JObj* jobj;
        HSD_Exp exp;
        f32 limit;
        HSD_IKHint ik_hint;
    } u;
    HSD_AObj* aobj;
};

struct HSD_RObjDesc {
    HSD_RObjDesc* next;
    u32 flags; // 0x04
    union HSD_RObjDesc_u {
        u32 i DAT_IF(false);
        HSD_ExpDesc* exp DAT_IF((flags & ROBJ_TYPE_MASK) == REFTYPE_EXP);
        HSD_ByteCodeExpDesc* bcexp DAT_IF((flags & ROBJ_TYPE_MASK) ==
                                          REFTYPE_BYTECODE);
        HSD_IKHintDesc* ik_hint DAT_IF((flags & ROBJ_TYPE_MASK) ==
                                       REFTYPE_IKHINT);
        HSD_Joint* joint DAT_IF((flags & ROBJ_TYPE_MASK) == REFTYPE_JOBJ);
        f32 limit DAT_IF((flags & ROBJ_TYPE_MASK) == REFTYPE_LIMIT);
    } u;
};

struct HSD_RObjAnimJoint {
    HSD_RObjAnimJoint* next;
    HSD_AObjDesc* aobjdesc;
};

/** @brief Forgets RObj memory allocations between low and high pointers */
void _HSD_RObjForgetMemory(void* low, void* high);
/** @brief Initializes the memory allocator for RObj and Rvalue objects */
void HSD_RObjInitAllocData(void);
/** @brief Retrieves the allocator data for RObj instances */
HSD_ObjAllocData* HSD_RObjGetAllocData(void);
/** @brief Retrieves the allocator data for Rvalue instances */
HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void);

/** @brief Allocates a new Constraint Object (RObj) */
HSD_RObj* HSD_RObjAlloc(void);
/** @brief Frees a previously allocated Constraint Object (RObj) */
void HSD_RObjFree(HSD_RObj* robj);

/** @brief Sets flags on a constraint object */
void HSD_RObjSetFlags(HSD_RObj* robj, u32 flags);
/** @brief Searches a linked list of RObjs for one matching the specified type and subtype */
HSD_RObj* HSD_RObjGetByType(HSD_RObj* robj, u32 type, u32 subtype);

/** @brief Interprets animations for an entire linked list of constraint objects */
void HSD_RObjAnimAll(HSD_RObj* robj);
/** @brief Removes animations matching specific flags for all constraint objects in a list */
void HSD_RObjRemoveAnimAllByFlags(HSD_RObj* robj, u32 flags);
/** @brief Removes all animations for all constraint objects in a list */
void HSD_RObjRemoveAnimAll(HSD_RObj* robj);
/** @brief Requests an animation state starting at a given frame for specific flags across a list of RObjs */
void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, f32 startframe, u32 flags);
/** @brief Requests an animation state starting at a given frame for all flags across a list of RObjs */
void HSD_RObjReqAnimAll(HSD_RObj* robj, f32 startframe);
/** @brief Associates an animation joint description with all constraint objects in a list */
void HSD_RObjAddAnimAll(HSD_RObj* robj, HSD_RObjAnimJoint* anim);

/** @brief Recursively removes a constraint object and its child references */
void HSD_RObjRemove(HSD_RObj*);
/** @brief Removes all constraint objects in a linked list */
void HSD_RObjRemoveAll(HSD_RObj*);

/** @brief Resolves JObj and Rvalue references from an RObjDesc into an RObj */
void HSD_RObjResolveRefs(HSD_RObj*, HSD_RObjDesc*);
/** @brief Resolves JObj and Rvalue references for an entire linked list of constraint objects */
void HSD_RObjResolveRefsAll(HSD_RObj*, HSD_RObjDesc*);
/** @brief Loads a constraint object from its descriptor definition */
HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc*);

/** @brief Associates a primary constraint target object with an RObj */
void HSD_RObjSetConstraintObj(HSD_RObj* robj, void* obj);
/** @brief Applies updates (IK constraints, limits, evaluations) to a target object driven by a list of RObjs */
void HSD_RObjUpdateAll(HSD_RObj* robj, void* obj, HSD_ObjUpdateFunc);
/** @brief Calculates the global position of a specified constraint */
int HSD_RObjGetGlobalPosition(HSD_RObj* robj, int, Vec3* translate);

/** @brief Removes animations matching specific flags from a single constraint object */
void HSD_RObjRemoveAnimByFlags(HSD_RObj* robj, u32 flags);
/** @brief Requests an animation state at a specified frame for a single constraint object using flags */
void HSD_RObjReqAnimByFlags(HSD_RObj* robj, f32 startframe, u32 flags);
/** @brief Associates an animation joint description with a single constraint object */
void HSD_RObjAddAnim(HSD_RObj* robj, HSD_RObjAnimJoint* anim);
/** @brief Evaluates animations for a single constraint object */
void HSD_RObjAnim(HSD_RObj* robj);

/** @brief Allocates an expression variable (Rvalue) */
HSD_Rvalue* HSD_RvalueAlloc(void);
/** @brief Removes/frees a single Rvalue */
void HSD_RvalueRemove(HSD_Rvalue* rvalue);
/** @brief Removes/frees a linked list of Rvalues */
void HSD_RvalueRemoveAll(HSD_Rvalue* rvalue);
/** @brief Resolves JObj pointers for an Rvalue using its list descriptor */
void HSD_RvalueResolveRefs(HSD_Rvalue* rvalue, HSD_RvalueList* list);
/** @brief Resolves JObj pointers for an entire list of Rvalues */
void HSD_RvalueResolveRefsAll(HSD_Rvalue* rvalue, HSD_RvalueList* list);

/** @brief Checks if the RObj has standard reference flags (0) */
static inline bool RObjHasFlags(HSD_RObj* robj)
{
    if ((robj->flags & ROBJ_TYPE_MASK) == 0) {
        return true;
    }
    return false;
}

/** @brief Checks if the active/enable flag is set (0x80000000) */
static inline bool RObjHasFlags2(HSD_RObj* robj)
{
    if ((robj->flags & 0x80000000) != 0) {
        return true;
    }
    return false;
}

/** @brief Checks if the RObj's reference type is a limit */
static inline bool RObjHasLimitReftype(HSD_RObj* robj)
{
    if ((robj->flags & ROBJ_TYPE_MASK) == REFTYPE_LIMIT) {
        return true;
    }
    return false;
}

#endif
