#ifndef GALE01_390730
#define GALE01_390730

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include "sysdolphin/baselib/objalloc.h"

#define HSD_GOBJ_GXLINK_NONE ((u8) 0xFF)
#define HSD_GOBJ_OBJ_NONE 0xFF

typedef struct HSD_GObj {
    /*  +0 */ u16 classifier;
    /*  +2 */ u8 p_link;
    /*  +3 */ u8 gx_link;
    /*  +4 */ u8 p_priority;
    /*  +5 */ u8 render_priority;
    /*  +6 */ u8 obj_kind;
    /*  +7 */ u8 user_data_kind;
    /*  +8 */ HSD_GObj* next;
    /*  +C */ HSD_GObj* prev;
    /* +10 */ HSD_GObj* next_gx;
    /* +14 */ HSD_GObj* prev_gx;
    /* +18 */ HSD_GObjProc* proc;
    /* +1C */ GObj_RenderFunc render_cb;
    /* +20 */ u64 gxlink_prios;
    /* +28 */ void* hsd_obj;
    /* +2C */ void* user_data;
    /* +30 */ void (*user_data_remove_func)(void* data);
    /* +34 */ void* x34_unk;
} HSD_GObj;

typedef void (*GObjFunc)(HSD_Obj*);

struct GObjFuncs {
    struct GObjFuncs* next;
    u8 size;
    GObjFunc* funcs;
};

typedef struct _HSD_GObjLibInitDataType {
    u8 p_link_max;    // 804CE380
    u8 gx_link_max;   // 804CE381
    u8 gproc_pri_max; // 804CE382
    GObjFuncs* funcs; // 804CE384
    u64* unk_2;       // 804CE388
} HSD_GObjLibInitDataType;

extern struct _unk_gobj_struct {
    union {
        u32 flags;
        struct {
            u32 in_delayed_proc : 1;
            u32 delay_remove_gobj : 1;
            u32 delay_remove_proc : 1;
            u32 delay_change_gobj_pri : 1;
        };
    };
    u32 type;
    u8 p_link;
    u8 p_prio;
    HSD_GObj* gobj;
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

void HSD_GObj_80390C5C(HSD_GObj* gobj);
void HSD_GObj_80390C84(HSD_GObj* gobj);
void HSD_GObj_80390CAC(HSD_GObj* gobj);
u32 HSD_GObj_80390EB8(s32 i);
void HSD_GObj_803910D8(HSD_GObj*, int);
u8 HSD_GObj_803912A8(HSD_GObjLibInitDataType*, GObjFuncs*);
HSD_GObj* GObj_Create(u16 classifier, u8 p_link, u8 priority);
void HSD_GObj_JObjCallback(HSD_GObj* gobj, int arg1);
void HSD_GObj_80390CD4(HSD_GObj* gobj);
void HSD_GObj_RunProcs(void);
void HSD_GObj_80390FC0(void);
void HSD_GObj_LObjCallback(HSD_GObj* gobj, int unused);
void HSD_GObj_FogCallback(HSD_GObj* gobj, int unused);
void HSD_GObj_80391120(HSD_Obj* obj);
void HSD_GObj_803911C0(HSD_Obj* obj);
void HSD_GObj_80391260(HSD_GObjLibInitDataType*);
void HSD_GObjSetInitDefaults(HSD_GObjLibInitDataType* arg0);
void HSD_GObj_80390ED0(HSD_GObj* gobj, u32 mask);
void HSD_GObjInit(HSD_GObjLibInitDataType*);

static inline void* HSD_GObjGetUserData(HSD_GObj* gobj)
{
    return gobj->user_data;
}

static inline void* HSD_GObjGetHSDObj(HSD_GObj* gobj)
{
    return gobj->hsd_obj;
}

static inline u16 HSD_GObjGetClassifier(HSD_GObj* gobj)
{
    return gobj->classifier;
}

static inline HSD_GObj* HSD_GObjGetNext(HSD_GObj* gobj)
{
    return gobj->next;
}

#define GET_COBJ(gobj) ((HSD_CObj*) HSD_GObjGetHSDObj(gobj))
#define GET_FOG(gobj) ((HSD_Fog*) HSD_GObjGetHSDObj(gobj))
#define GET_JOBJ(gobj) ((HSD_JObj*) HSD_GObjGetHSDObj(gobj))
#define GET_LOBJ(gobj) ((HSD_LObj*) HSD_GObjGetHSDObj(gobj))

#endif
