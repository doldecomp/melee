#ifndef __GALE01_00F9F8
#define __GALE01_00F9F8

#include "lb_00F9.h" // IWYU pragma: export
#include "platform.h"

#include <placeholder.h>

struct _m2c_stack_lb_80014638 {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ Vec3 sp18; /* inferred */
    /* 0x24 */ Vec3 sp24; /* inferred */
    /* 0x30 */ Vec3 sp30;
    /* 0x3C */ char pad_3C[4];
}; /* size = 0x40 */
STATIC_ASSERT(sizeof(struct _m2c_stack_lb_80014638) == 0x40);

/* 0103D8 */ static bool lb_800103D8(Vec3* vec, float x0, float x1, float x2,
                                     float x3, float offset);
/* 011B74 */ static void lb_80011B74(HSD_DObj* dobj, u32 flags);
/* 013BB0 */ static bool lb_80013BB0(ColorOverlay* arg);
/* 013BB8 */ static bool lb_80013BB8(ColorOverlay* arg);
/* 013BE4 */ static bool lb_80013BE4(ColorOverlay* arg);
/* 013FF0 */ static bool lb_80013FF0(ColorOverlay* arg);
/* 014234 */ static bool lb_80014234(ColorOverlay* arg);
/* 4D3770 */ static GXColor yellow;
/* 4D63A0 */ static struct lb_804D63A0_t* lb_804D63A0;
/* 4D63A4 */ static struct DynamicsData* cur_data;
/* 4D63A8 */ static struct lb_804D63A8_t* lb_804D63A8;
/* 4D63AC */ static struct lb_80011A50_t* lb_804D63AC;
/* 4D63B0 */ static struct lb_80011A50_t* lb_804D63B0;
/* 4D63B4 */ static enum_t lb_804D63B4;
/* 4D63C0 */ static struct Fighter_804D653C_t* lb_804D63C0;

#endif
