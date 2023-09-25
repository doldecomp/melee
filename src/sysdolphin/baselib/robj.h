#ifndef _robj_h_
#define _robj_h_

#include <baselib/forward.h>

#include <baselib/aobj.h>
#include <baselib/fobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>

#define TYPE_MASK 0x70000000
#define REFTYPE_JOBJ 0x10000000
#define REFTYPE_IKHINT 0x40000000

struct HSD_Rvalue {
    struct HSD_Rvalue* next;
    u32 flags;
    HSD_JObj* jobj;
};

struct HSD_RvalueList {
    u32 flags;
    struct HSD_Joint* joint;
    struct HSD_RvalueList* next;
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
    union {
        f32 (*func)(void);
        u8* bytecode;
    } expr;
    HSD_Rvalue* rvalue;
    u32 nb_args;
    u8 is_bytecode;
};

struct HSD_ExpDesc {
    f32 (*func)(void);
    struct HSD_RvalueList* rvalue;
};

struct HSD_ByteCodeExpDesc {
    u8* bytecode;
    struct HSD_RvalueList* rvalue;
};

struct HSD_RObj {
    HSD_RObj* next;
    u32 flags;
    union {
        HSD_JObj* jobj;
        HSD_Exp exp;
        f32 limit;
        HSD_IKHint ik_hint;
    } u;
    HSD_AObj* aobj;
};

struct HSD_RObjDesc {
    struct HSD_RObjDesc* next;
    u32 flags; // 0x04
    union {
        u32 i;
        struct HSD_ExpDesc* exp;
        struct HSD_ByteCodeExpDesc* bcexp;
        struct HSD_IKHintDesc* ik_hint;
        struct HSD_Joint* joint;
        f32 limit;
    } u;
};

struct HSD_RObjAnimJoint {
    HSD_RObjAnimJoint* next;
    HSD_AObjDesc* aobjdesc;
};

void _HSD_RObjForgetMemory(void* low, void* high);
void HSD_RObjInitAllocData(void);
HSD_ObjAllocData* HSD_RObjGetAllocData(void);
HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void);
HSD_RObj* HSD_RObjAlloc(void);
void HSD_RObjFree(HSD_RObj* robj);

void HSD_RObjSetFlags(HSD_RObj* robj, u32 flags);
HSD_RObj* HSD_RObjGetByType(HSD_RObj* robj, u32 type, u32 subtype);
void HSD_RObjAnimAll(HSD_RObj* robj);
void HSD_RObjRemoveAnimAllByFlags(HSD_RObj* robj, u32 flags);
void HSD_RObjRemoveAnimAll(HSD_RObj* robj);
void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, f32 startframe, u32 flags);
void HSD_RObjReqAnimAll(HSD_RObj* robj, f32 startframe);
void HSD_RObjAddAnimAll(HSD_RObj* robj, HSD_RObjAnimJoint* anim);

void HSD_RObjRemove(HSD_RObj*);
void HSD_RObjRemoveAll(HSD_RObj*);
void HSD_RObjResolveRefsAll(HSD_RObj*, HSD_RObjDesc*);
HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc*);
void HSD_RObjSetConstraintObj(HSD_RObj* robj, void* obj);
void HSD_RObjUpdateAll(HSD_RObj* robj, HSD_JObj* jobj, HSD_ObjUpdateFunc);
int HSD_RObjGetGlobalPosition(HSD_RObj* robj, int, Vec3* translate);

void HSD_RObjRemoveAnimByFlags(HSD_RObj* robj, u32 flags);
void HSD_RObjReqAnimByFlags(HSD_RObj* robj, f32 startframe, u32 flags);
void HSD_RObjAddAnim(HSD_RObj* robj, HSD_RObjAnimJoint* anim);
void HSD_RObjAnim(HSD_RObj* robj);

void HSD_RvalueRemoveAll(HSD_Rvalue* rvalue);

#endif
