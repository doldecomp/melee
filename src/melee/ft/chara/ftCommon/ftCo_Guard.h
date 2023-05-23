#ifndef GALE01_091A2C
#define GALE01_091A2C

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include <common_structs.h>
#include <placeholder.h>

#ifdef M2CTX
struct _m2c_stack_ft_80092450 {
    /* 0x00 */ char pad_0[0x10];
    /* 0x10 */ AbsorbDesc absorb;
    /* 0x24 */ char pad_24[0xC];
}; /* size = 0x30 */

struct _m2c_stack_ft_80093BC0 {
    /* 0x00 */ char pad_0[0x14];
    /* 0x14 */ AbsorbDesc absorb;
    /* 0x28 */ char pad_28[8];
}; /* size = 0x30 */

struct _m2c_stack_ftCo_80092908 {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ AbsorbDesc absorb;
    /* 0x2C */ char pad_2C[0x14];
}; /* size = 0x40 */

struct _m2c_stack_ft_80091D58 {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ Vec3 scl;
    /* 0x24 */ char pad_24[0xC];
}; /* size = 0x30 */

struct _m2c_stack_ftCo_8009388C {
    /* 0x00 */ char pad_0[0x14];
    /* 0x14 */ ReflectDesc reflect;
    /* 0x35 */ char pad_35[0x10];
}; /* size = 0x48 */

struct _m2c_stack_ftCo_80093A50 {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ ReflectDesc reflect;
    /* 0x3C */ AbsorbDesc absorb;
    /* 0x50 */ char pad_50[0x18];
}; /* size = 0x68 */

struct _m2c_stack_ftCo_800921DC {
    /* 0x00 */ char pad_0[0x18];
    /* 0x18 */ Vec3 vec;
    /* 0x24 */ char pad_24[0x14];
}; /* size = 0x38 */

struct _m2c_stack_ftCo_GuardReflect_Anim {
    /* 0x00 */ char pad_0[0x24];
    /* 0x24 */ AbsorbDesc absorb;
    /* 0x38 */ char pad_38[0x10];
}; /* size = 0x48 */

struct _m2c_stack_ftCo_GuardSetOff_Anim {
    /* 0x00 */ char pad_0[0x30];
    /* 0x30 */ AbsorbDesc absorb;
    /* 0x44 */ char pad_44[4];
    /* 0x48 */ Vec3 scl;
    /* 0x54 */ char pad_54[0x14];
}; /* size = 0x68 */

struct _m2c_stack_ftCo_80091E78 {
    /* 0x00 */ char pad_0[0x24];
    /* 0x24 */ Vec3 scl;
    /* 0x30 */ char pad_30[0x30];
}; /* size = 0x60 */

struct _m2c_stack_ftCo_80092F2C {
    /* 0x00 */ char pad_0[0x2C];
    /* 0x2C */ Vec3 scl;
    /* 0x38 */ AbsorbDesc absorb;
    /* 0x4C */ char pad_4C[0x2C];
}; /* size = 0x78 */

static char* ftCo_804D3AF8 = "jobj.h";
static char* ftCo_804D3B00 = "jobj";
#endif

/* 091A2C */ bool ftCo_80091A2C(ftCo_GObj* gobj);
/* 091A4C */ bool ft_80091A4C(ftCo_GObj* gobj);
/* 091AD8 */ bool ftCo_80091AD8(ftCo_GObj* gobj, int mv_x20);
/* 091B90 */ void ftCo_80091B90(ftCo_GObj* gobj, int);
/* 091B9C */ void ftCo_80091B9C(ftCo_GObj* gobj);
/* 091D58 */ void ft_80091D58(ftCo_Fighter* fp);
/* 092450 */ void ft_80092450(ftCo_GObj* gobj);
/* 0925A4 */ bool ft_800925A4(ftCo_GObj* gobj);
/* 0926DC */ void ftCo_GuardOn_Anim(ftCo_GObj* gobj);
/* 092758 */ void ftCo_GuardOn_IASA(ftCo_GObj* gobj);
/* 092870 */ void ftCo_GuardOn_Phys(ftCo_GObj* gobj);
/* 0928AC */ void ftCo_GuardOn_Coll(ftCo_GObj* gobj);
/* 092ED8 */ float ft_80092ED8(int, float);
/* 093240 */ void ft_80093240(ftCo_GObj* gobj);
/* 0932DC */ void ft_800932DC(ftCo_GObj* gobj);
/* 093694 */ bool ft_80093694(ftCo_GObj* gobj);
/* 09370C */ void ft_8009370C(HSD_GObj*, HSD_GObjEvent);

#endif
