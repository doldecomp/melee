#ifndef GALE01_0BD19C
#define GALE01_0BD19C

#include "ft/forward.h"

#include <placeholder.h>
#include <dolphin/mtx/types.h>

struct _m2c_stack_ftCo_800BD1DC {
    /* 0x00 */ char pad_0[0x24];
    /* 0x24 */ float sp24; /* inferred */
    /* 0x28 */ float sp28; /* inferred */
    /* 0x2C */ char pad_2C[4];
    /* 0x30 */ float sp30; /* inferred */
    /* 0x34 */ float sp34; /* inferred */
    /* 0x38 */ char pad_38[0x20];
}; /* size = 0x58 */

struct _m2c_stack_ftCo_800BD39C {
    /* 0x00 */ char pad_0[0x24];
    /* 0x24 */ Vec3 scale;
    /* 0x30 */ char pad_30[4];
    /* 0x34 */ Vec3 pos;
    /* 0x40 */ char pad_40[0x18];
}; /* size = 0x58 */

/* static */ extern char* ftCo_804D3BB0;
/* static */ extern char* ftCo_804D3BB8;
/* static */ extern char* ftCo_804D3BC0;

/* 0BD19C */ float ftCo_800BD19C(Fighter_GObj* gobj, Vec3* pos);
/* 0BD1DC */ void ftCo_800BD1DC(Fighter_GObj* gobj, Fighter_GObj* victim_gobj);
/* 0BD38C */ void ftCo_CaptureKirby_Anim(Fighter_GObj*);
/* 0BD390 */ void ftCo_CaptureKirby_IASA(Fighter_GObj*);
/* 0BD394 */ void ftCo_CaptureKirby_Phys(Fighter_GObj*);
/* 0BD398 */ void ftCo_CaptureKirby_Coll(Fighter_GObj*);
/* 0BD39C */ void ftCo_800BD39C(Fighter_GObj* gobj);

#endif
