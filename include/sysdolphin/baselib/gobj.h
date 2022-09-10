#ifndef _gobj_h_
#define _gobj_h_

#include <dolphin/types.h>

#include <sysdolphin/baselib/objalloc.h>

#define HSD_GOBJ_GXLINK_NONE ((u8) 0xFF)
#define HSD_GOBJ_OBJ_NONE 0xFF

#define HSD_GOBJ_CLASS_STAGE 0x3
#define HSD_GOBJ_CLASS_FIGHTER 0x4
#define HSD_GOBJ_CLASS_ITEM 0x6
#define HSD_GOBJ_CLASS_ITEMLINK 0x7 // Used by chain-type items in-game to link multiple parts together
#define HSD_GOBJ_CLASS_EFFECT 0x8

typedef struct _HSD_GObj {
    /* 0x00 */ u16 classifier;
    /* 0x02 */ u8 p_link;
    /* 0x03 */ u8 gx_link;
    /* 0x04 */ u8 p_priority;
    /* 0x05 */ u8 render_priority;
    /* 0x06 */ u8 obj_kind;
    /* 0x07 */ u8 user_data_kind;
    /* 0x08 */ struct _HSD_GObj* next;
    /* 0x0C */ struct _HSD_GObj* prev;
    /* 0x10 */ struct _HSD_GObj* next_gx;
    /* 0x14 */ struct _HSD_GObj* prev_gx;
    /* 0x18 */ struct _HSD_GObjProc* proc;
    /* 0x1C */ void (*render_cb)(struct _HSD_GObj* gobj, s32 code);
    /* 0x20 */ u64 gxlink_prios;
    /* 0x28 */ void* hsd_obj;
    /* 0x2C */ void* user_data;
    /* 0x30 */ void (*user_data_remove_func)(void* data);
    /* 0x34 */ void* x34_unk;
} HSD_GObj;

typedef struct _HSD_GObjProc {
    /* 0x00 */ struct _HSD_GObjProc* child;
    /* 0x04 */ struct _HSD_GObjProc* next;
    /* 0x08 */ struct _HSD_GObjProc* prev;
    /* 0x0C */ u8 s_link;
    /* 0x0D */ u8 flags_1 : 1;
    /* 0x0D */ u8 flags_2 : 1;
    /* 0x0D */ u8 flags_3 : 2;
    /* 0x10 */ struct _HSD_GObj* gobj;
    /* 0x14 */ void (*callback)(struct _HSD_GObj*);
} HSD_GObjProc;

typedef struct _HSD_GObjLibInitDataType {
    u8 p_link_max;                  // 804CE380
    u8 gx_link_max;                 // 804CE381
    u8 gproc_pri_max;               // 804CE382
    u32 unk_1;                      // 804CE384
    u64* unk_2;                     // 804CE388
    HSD_ObjAllocData gobj_def;      // 804CE38C
    HSD_ObjAllocData gobj_proc_def; // 804CE3B8
} HSD_GObjLibInitDataType;

typedef struct _HSD_GObjList {
    /* 0x00 */ HSD_GObj* x0;
    /* 0x04 */ HSD_GObj* x4;
    /* 0x08 */ HSD_GObj* x8;
    /* 0x0C */ HSD_GObj* xC;
    /* 0x10 */ HSD_GObj* x10;
    /* 0x14 */ HSD_GObj* x14;
    /* 0x18 */ HSD_GObj* x18;
    /* 0x1C */ HSD_GObj* x1C;
    /* 0x20 */ HSD_GObj* x20_fighters;
    /* 0x24 */ HSD_GObj* x24_items;
    /* 0x28 */ HSD_GObj* x28;
    /* 0x2C */ HSD_GObj* x2C;
    /* 0x30 */ HSD_GObj* x30;
    /* 0x34 */ HSD_GObj* x34;
    /* 0x38 */ HSD_GObj* x38;
    /* 0x3C */ HSD_GObj* x3C;
    /* 0x40 */ HSD_GObj* x40;
    /* 0x44 */ HSD_GObj* x44;
    /* 0x48 */ HSD_GObj* x48;
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
} lbl_804CE3E4;

extern HSD_GObj* lbl_804D797C;
extern HSD_GObj** lbl_804D7820;
extern HSD_GObj** lbl_804D7824;
extern HSD_GObjLibInitDataType HSD_GObjLibInitData;
extern HSD_GObj** plinklow_gobjs;
extern HSD_GObjList* lbl_804D782C;
extern u8 lbl_804D784B[5];

void func_80390C5C(HSD_GObj* gobj);
void func_80390C84(HSD_GObj* gobj);
void func_80390CAC(HSD_GObj* gobj);
u32 func_80390EB8(s32 i);
void func_803910D8(HSD_GObj*, s32);
u8 func_803912A8(struct _GObjUnkStruct*, struct _GObjFuncs*);
HSD_GObj* func_803901F0(u16 classifier, u8 p_link, u8 priority);

#endif
