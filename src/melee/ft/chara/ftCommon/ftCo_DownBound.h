#ifndef GALE01_096F0C
#define GALE01_096F0C

#include <platform.h>
#include "ftCommon/forward.h"

#include <placeholder.h>

extern enum_t ftCo_DownBound_SfxIds[4];

#ifdef M2CTX
struct _m2c_stack_ftCo_800976A4 {
    /* 0x00 */ char pad_0[0x14];
    /* 0x14 */ float sp14;
    /* 0x18 */ Vec3 vec0;
    /* 0x24 */ Vec3 vec1;
    /* 0x30 */ IntVec3 ivec;
    /* 0x3C */ enum_t sp3C;
    /* 0x40 */ enum_t sp40;
    /* 0x44 */ enum_t sp44;
    /* 0x48 */ char pad_48[0x18];
}; /* size = 0x60 */
#endif

/* 097570 */ bool ftCo_80097570(ftCo_GObj* gobj);
/* 096FCC */ void ftCo_80097630(ftCo_Fighter* fp, enum_t* sfx_ids,
                                float threshold);
/* 097040 */ /* static */ void ftCo_800976A4(ftCo_GObj* gobj);
/* 097270 */ /* static */ void ftCo_800978D4(ftCo_GObj* gobj);
/* 0972E8 */ /* static */ void ftCo_8009794C(ftCo_GObj* gobj);
/* 097490 */ /* static */ void ftCo_80097AF4(ftCo_GObj* gobj);
/* 0976DC */ /* static */ void ft_80097D40(ftCo_GObj* gobj);
/* 097724 */ /* static */ void ftCo_80097D88(ftCo_GObj* gobj);
/* 09775C */ void ftCo_DownBound_Anim(ftCo_GObj* gobj);
/* 0977B8 */ void ftCo_DownBound_IASA(ftCo_GObj* gobj);
/* 0977BC */ void ftCo_DownBound_Phys(ftCo_GObj* gobj);
/* 0977DC */ void ftCo_DownBound_Coll(ftCo_GObj* gobj);

#endif
