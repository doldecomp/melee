#ifndef _gobj_h_
#define _gobj_h_

#include "include/dolphin/types.h"

typedef struct _HSD_GObj {
    u16 classifier;
    s8 p_link;
    s8 gx_link;
    u8 p_priority;
    u8 render_priority;
    s8 obj_kind;
    s8 user_data_kind;
    struct _HSD_GObj* next; //0x08
    struct _HSD_GObj* prev; //0x0C
    struct _HSD_GObj* next_gx; //0x10
    struct _HSD_GObj* prev_gx; //0x14
    struct _HSD_GObjProc* proc; //0x18
    void (*render_cb)(struct _HSD_GObj* gobj, int code); //0x1C
    u64 gxlink_prios;
    void* hsd_obj;
    void* data;
    void (*user_data_remove_func)(void* data);
    void* x34_unk;
} HSD_GObj;

typedef struct _HSD_GObjProc {
    struct _HSD_GObjProc* child; //0x0
    struct _HSD_GObjProc* next; //0x4
    struct _HSD_GObjProc* prev; //0x8
    u8 s_link; //0xC
    u8 flags; //0xD
    struct _HSD_GObj* gobj; //0x10
    void (*callback)(struct _HSD_GObj*); //0x14
} HSD_GObjProc;

#endif

BOOL func_80390C5C(HSD_GObj* gobj);
BOOL func_80390C84(HSD_GObj* gobj);
