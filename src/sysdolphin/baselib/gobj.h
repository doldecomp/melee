#ifndef GALE01_390730
#define GALE01_390730

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h" // IWYU pragma: export

#include "baselib/objalloc.h"

struct _GObjUnkStruct;

#define HSD_GOBJ_GXLINK_NONE ((u8) 0xFF)
#define HSD_GOBJ_OBJ_NONE 0xFF

#define HSD_GOBJ_CLASS_STAGE 0x3
#define HSD_GOBJ_CLASS_FIGHTER 0x4
#define HSD_GOBJ_CLASS_ITEM 0x6

/// Used by chain-type items in-game to link multiple parts together
#define HSD_GOBJ_CLASS_ITEMLINK 0x7

#define HSD_GOBJ_CLASS_EFFECT 0x8

struct HSD_GObj {
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
};

typedef struct _HSD_GObjLibInitDataType {
    u8 p_link_max;                  // 804CE380
    u8 gx_link_max;                 // 804CE381
    u8 gproc_pri_max;               // 804CE382
    u32 unk_1;                      // 804CE384
    u64* unk_2;                     // 804CE388
    HSD_ObjAllocData gobj_def;      // 804CE38C
    HSD_ObjAllocData gobj_proc_def; // 804CE3B8
} HSD_GObjLibInitDataType;

/// @todo Belongs in `melee/` somewhere
typedef struct _HSD_GObjList {
    /*  +0 */ HSD_GObj* x0;
    /*  +4 */ HSD_GObj* x4;
    /*  +8 */ HSD_GObj* x8;
    /*  +C */ HSD_GObj* xC;
    /* +10 */ HSD_GObj* x10;
    /* +14 */ HSD_GObj* x14;
    /* +18 */ HSD_GObj* x18;
    /* +1C */ HSD_GObj* x1C;
    /* +20 */ HSD_GObj* fighters;
    /* +24 */ HSD_GObj* items;
    /* +28 */ HSD_GObj* x28;
    /* +2C */ HSD_GObj* x2C;
    /* +30 */ HSD_GObj* x30;
    /* +34 */ HSD_GObj* x34;
    /* +38 */ HSD_GObj* x38;
    /* +3C */ HSD_GObj* x3C;
    /* +40 */ HSD_GObj* x40;
    /* +44 */ HSD_GObj* x44;
    /* +48 */ HSD_GObj* x48;
} HSD_GObjList;

extern struct _unk_gobj_struct {
    union {
        u32 flags;
        struct {
            u32 b0 : 1;
            u32 b1 : 1;
            u32 b2 : 1;
            u32 b3 : 1;
        };
    };
    u32 type;
    u8 p_link;
    u8 p_prio;
    HSD_GObj* gobj;
} HSD_GObj_804CE3E4;

typedef struct _GObjUnkStruct GObjUnkStruct;
typedef struct _GObjFuncs GObjFuncs;

extern HSD_GObj* HSD_GObj_804D7818;
extern HSD_GObj* HSD_GObj_804D781C;
extern HSD_GObjProc* HSD_GObj_804D7830;
extern HSD_GObjProc* HSD_GObj_804D7838;
extern HSD_GObjProc** HSD_GObj_804D7840;
extern s32 HSD_GObj_804D7834;
extern s32 HSD_GObj_804D783C;
// extern HSD_GObj* HSD_SisLib_804D797C; @todo: is this actually correct?
extern HSD_GObj** HSD_GObj_804D7820;
extern HSD_GObj** HSD_GObj_804D7824;
extern HSD_GObjLibInitDataType HSD_GObjLibInitData;
extern HSD_GObj** plinklow_gobjs;
extern HSD_GObjList* HSD_GObj_Entities;
extern u8 HSD_GObj_804D784B[5];

extern GObjFuncs HSD_GObj_80408610;
extern s8 HSD_GObj_804D7848;
extern s8 HSD_GObj_804D7849;
extern s8 HSD_GObj_804D784A;
extern GObjFuncs HSD_GObj_80408620;

void HSD_GObj_80390C5C(HSD_GObj* gobj);
void HSD_GObj_80390C84(HSD_GObj* gobj);
void HSD_GObj_80390CAC(HSD_GObj* gobj);
u32 HSD_GObj_80390EB8(s32 i);
void HSD_GObj_803910D8(HSD_GObj*);
u8 HSD_GObj_803912A8(GObjUnkStruct*, GObjFuncs*);
HSD_GObj* GObj_Create(u16 classifier, u8 p_link, u8 priority);
void HSD_GObj_80391070(HSD_GObj* gobj, int arg1);
void HSD_GObj_80390CD4(HSD_GObj* gobj);
void HSD_GObj_80390CFC(void);
void render_gobj(HSD_GObj* cur, int i);
void HSD_GObj_80390FC0(void);
void HSD_GObj_80391044(HSD_GObj* gobj);
void HSD_GObj_803910B4(HSD_GObj* gobj);
void HSD_GObj_80391120(HSD_Obj* obj);
void HSD_GObj_803911C0(HSD_Obj* obj);
void HSD_GObj_80391260(struct _GObjUnkStruct* arg0);
void HSD_GObj_803912E0(GObjFuncs* arg0);
void HSD_GObj_80390ED0(HSD_GObj* gobj, u32 mask);
extern HSD_GObj* HSD_GObj_804D7814;

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
