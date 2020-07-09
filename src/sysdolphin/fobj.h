#ifndef _fobj_h_
#define _fobj_h_

#include "global.h"

#include "object.h"

#define HSD_A_OP_NONE 0
#define HSD_A_OP_CON 1
#define HSD_A_OP_LIN 2
#define HSD_A_OP_SPL0 3
#define HSD_A_OP_SPL 4
#define HSD_A_OP_SLP 5
#define HSD_A_OP_KEY 6

#define HSD_A_FRAC_FLOAT (0 << 5)
#define HSD_A_FRAC_S16 (1 << 5)
#define HSD_A_FRAC_U16 (2 << 5)
#define HSD_A_FRAC_S8 (3 << 5)
#define HSD_A_FRAC_U8 (4 << 5)

#define TYPE_ROBJ 1
#define TYPE_JOBJ 12

typedef struct _HSD_FObj {
    struct _HSD_FObj* next;
    u8* ad;
    u8* ad_head;
    u32 length;
    u8 flags;
    u8 op;
    u8 op_intrp;
    u8 obj_type;
    u8 frac_value;
    u8 frac_slope;
    u16 nb_pack;
    s16 startframe;
    u16 fterm;
    f32 time;
    f32 p0;
    f32 p1;
    f32 d0;
    f32 d1;
} HSD_FObj;

typedef struct _HSD_FObjDesc {
    struct _HSD_FObjDesc* next;
    u32 length;
    f32 startframe;
    u8 type;
    u8 frac_value;
    u8 frac_slope;
    u8 dummy0;
    u8* ad;
} HSD_FObjDesc;

typedef struct _HSD_FObjData {
    f32 fv;
    s32 iv;
    Vec p;
} FObjData;

#endif
