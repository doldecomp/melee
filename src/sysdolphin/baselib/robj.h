#ifndef _robj_h_
#define _robj_h_

#include <global.h>

#include "sysdolphin/baselib/objalloc.h"

#include "sysdolphin/baselib/aobj.h"
#include "sysdolphin/baselib/fobj.h"
#include "sysdolphin/baselib/jobj.h"

#define TYPE_MASK 0x70000000
#define REFTYPE_JOBJ 0x10000000
#define REFTYPE_IKHINT 0x40000000

typedef struct _HSD_Rvalue {
    struct _HSD_Rvalue* next;
    u32 flags;
    struct _HSD_JObj* jobj;
} HSD_Rvalue;

typedef struct _HSD_RvalueList {
    u32 flags;
    struct _HSD_JObjDesc* joint;
    struct _HSD_RvalueList* next;
} HSD_RvalueList;

typedef struct _HSD_IKHint {
    f32 bone_length;
    f32 rotate_x;
} HSD_IKHint;

typedef struct _HSD_IKHintDesc {
    f32 bone_length;
    f32 rotate_x;
} HSD_IKHintDesc;

typedef struct _HSD_Exp {
    union {
        f32 (*func)(void);
        u8* bytecode;
    } expr;
    struct _HSD_Rvalue* rvalue;
    u32 nb_args;
    u8 is_bytecode;
} HSD_Exp;

typedef struct _HSD_ExpDesc {
    f32 (*func)(void);
    struct _HSD_RvalueList* rvalue;
} HSD_ExpDesc;

typedef struct _HSD_ByteCodeExpDesc {
    u8* bytecode;
    struct _HSD_RvalueList* rvalue;
} HSD_ByteCodeExpDesc;

typedef struct _HSD_RObj {
    struct _HSD_RObj* next;
    u32 flags;
    union {
        struct _HSD_JObj* jobj;
        struct _HSD_Exp exp;
        f32 limit;
        struct _HSD_IKHint ik_hint;
    } u;
    struct _HSD_AObj* aobj;
} HSD_RObj;

typedef struct _HSD_RObjDesc {
    struct _HSD_RObjDesc* next;
    u32 flags; //0x04
    union {
        u32 i;
        struct _HSD_ExpDesc* exp;
        struct _HSD_ByteCodeExpDesc* bcexp;
        struct _HSD_IKHintDesc* ik_hint;
        struct _HSD_JObjDesc* joint;
        f32 limit;
    } u;
} HSD_RObjDesc;

typedef struct _HSD_RObjAnimJoint {
    struct _HSD_RObjAnimJoint* next;
    struct _HSD_AObjDesc* aobjdesc;
} HSD_RObjAnimJoint;


void _HSD_RObjForgetMemory(void);
void HSD_RObjInitAllocData(void);
HSD_ObjAllocData* HSD_RObjGetAllocData(void);
HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void);
HSD_RObj* HSD_RObjAlloc(void);
void HSD_RObjSetFlags(HSD_RObj* robj, u32 flags);
HSD_RObj* HSD_RObjGetByType(HSD_RObj* robj, u32 type, u32 subtype);
void HSD_RObjAnimAll(HSD_RObj* robj);
void HSD_RObjRemoveAnimAllByFlags(HSD_RObj* robj, u32 flags);
void HSD_RObjRemoveAnimAll(HSD_RObj* robj);
void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, f32 startframe, u32 flags);
void HSD_RObjReqAnimAll(HSD_RObj* robj, f32 startframe);
void HSD_RObjAddAnimAll(HSD_RObj* robj, HSD_RObjAnimJoint* anim);

void HSD_RObjRemoveAll(HSD_RObj*);
void HSD_RObjResolveRefsAll(HSD_RObj*, HSD_RObjDesc*);
HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc*);

#endif
