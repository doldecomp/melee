#ifndef GALE01_1E3734
#define GALE01_1E3734

#include <melee/gr/forward.h>
#include <melee/it/forward.h>
#include <melee/lb/forward.h>
#include <melee/sc/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/* 1E3734 */ void grOnett_801E3734(bool);
/* 1E3738 */ void grOnett_801E3738(void);
/* 1E37C4 */ void grOnett_801E37C4(void);
/* 1E37C8 */ void grOnett_801E37C8(void);
/* 1E37EC */ bool grOnett_801E37EC(void);
/* 1E37F4 */ HSD_GObj* grOnett_801E37F4(int);
/* 1E38DC */ void grOnett_801E38DC(Ground_GObj*);
/* 1E3920 */ bool grOnett_801E3920(Ground_GObj*);
/* 1E3928 */ void grOnett_801E3928(Ground_GObj*);
/* 1E392C */ void grOnett_801E392C(Ground_GObj*);
/* 1E3930 */ void grOnett_801E3930(Ground_GObj*);
/* 1E3A34 */ void grOnett_801E3A34(Ground_GObj*);
/* 1E3C58 */ bool grOnett_801E3C58(Ground_GObj*);
/* 1E3C60 */ void grOnett_801E3C60(Ground_GObj*);
/* 1E3CE0 */ void grOnett_801E3CE0(Ground_GObj*);
/* 1E3CE4 */ void grOnett_801E3CE4(Ground_GObj*);
/* 1E3D98 */ bool grOnett_801E3D98(Ground_GObj*);
/* 1E3DA0 */ void grOnett_801E3DA0(Ground_GObj*);
/* 1E40E0 */ void grOnett_801E40E0(Ground_GObj*);
/* 1E41B0 */ void grOnett_801E41B0(Ground_GObj*);
/* 1E41C8 */ void grOnett_801E41C8(Ground_GObj*);
/* 1E43D8 */ bool grOnett_801E43D8(Ground_GObj*);
/* 1E43E0 */ void grOnett_801E43E0(Ground_GObj*);
/* 1E502C */ void grOnett_801E502C(Ground_GObj*);
/* 1E5030 */ void grOnett_801E5030(Item_GObj*, Ground*);
/* 1E5140 */ void grOnett_801E5140(s32 idx);
/* 1E5194 */ void grOnett_801E5194(Ground*, s32, s32);
/* 1E5214 */ void grOnett_801E5214(Ground_GObj*);
/* 1E5538 */ void grOnett_801E5538(Ground_GObj*);
/* 1E56FC */ DynamicModelDesc* grOnett_801E56FC(void);
/* 1E5760 */ lbColl_80008D30_arg1* grOnett_801E5760(enum_t);
/* 1E5768 */ bool grOnett_801E5768(Vec3*, int, HSD_JObj*);
/* 3E2858 */ extern StageData grOt_StageData;

/// Onett stage yakumono parameters
struct grOnett_YakumonoParam {
    /* 0x00 */ f32 awning_initial;
    /* 0x04 */ f32 max_velocity;
    /* 0x08 */ f32 vel_threshold;
    /* 0x0C */ f32 pos_threshold;
    /* 0x10 */ f32 damping;
    /* 0x14 */ f32 spring_force;
    /* 0x18 */ f32 spring_constant;
    /* 0x1C */ f32 max_displacement;
    /* 0x20 */ f32 awning_delta;
    /* 0x24 */ f32 x24;
    /* 0x28 */ f32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ f32 x30;
    /* 0x34 */ f32 x34;
    /* 0x38 */ f32 x38;
    /* 0x3C */ f32 x3C;
    /* 0x40 */ f32 x40;
    /* 0x44 */ f32 x44;
    /* 0x48 */ f32 x48;
    /* 0x4C */ f32 x4C;
    /* 0x50 */ f32 x50;
    /* 0x54 */ f32 x54;
    /* 0x58 */ f32 x58;
    /* 0x5C */ f32 x5C;
    /* 0x60 */ f32 x60;
    /* 0x64 */ f32 x64;
};

#endif
