#ifndef __GALE01_00F9F8
#define __GALE01_00F9F8

#include "lb_00F9.h" // IWYU pragma: export
#include "platform.h"

#include <placeholder.h>

struct lb_8000FD18_t {
    char pad_0[0x94];
};

struct lb_80013FF0_t {
    /* 0x00 */ int x0;
    UNK_T x4;
    /* 0x08 */ int* unk_8;
    /* 0x0C */ char pad_C[0x70];
    /* 0x7C */ u8 x7C_0 : 1;
    /* 0x7C */ u8 x7C_1 : 1;
    /* 0x7D */ char pad_7D[3];
}; /* size = 0x80 */

struct lb_804D63A0_t {
    /* +0 */ char pad_0[0xBE00];
};
STATIC_ASSERT(sizeof(struct lb_804D63A0_t) == 0xBE00);

struct lb_804D63A8_t {
    /* +0 */ char pad_0[0x1C0];
};
STATIC_ASSERT(sizeof(struct lb_804D63A8_t) == 0x1C0);

struct _m2c_stack_lb_800119DC {
    /* 0x00 */ char pad_0[0x1C];
    struct lb_80011A50_t sp1C;
    /* 0x4C */ char pad_4C[0xC];
}; /* size = 0x58 */

/* 0103D8 */ static bool lb_800103D8(Vec3* vec, float x0, float x1, float x2,
                                     float x3, float offset);
/* 011B74 */ static void lb_80011B74(HSD_DObj* dobj, u32 flags);
/* 013BB0 */ static bool lb_80013BB0(void);
/* 013BB8 */ static int lb_80013BB8(struct lb_80013FF0_t*);
/* 013BE4 */ static int lb_80013BE4(ColorOverlay*);
/* 013FF0 */ static int lb_80013FF0(struct lb_80013FF0_t*);
/* 014234 */ static int lb_80014234(struct lb_80013FF0_t*);
/* 4D63A0 */ static struct lb_804D63A0_t* lb_804D63A0;
/* 4D63A4 */ static struct DynamicsData* cur_data;
/* 4D63A8 */ static struct lb_804D63A8_t* lb_804D63A8;
/* 4D63B4 */ static enum_t lb_804D63B4;
/* 4D63C0 */ static struct Fighter_804D653C_t* lb_804D63C0;
/* 4D3770 */ static GXColor yellow;

#endif
