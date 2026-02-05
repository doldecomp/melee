#ifndef GALE01_20B864
#define GALE01_20B864

#include <placeholder.h>

#include "gr/forward.h"
#include "lb/forward.h"
#include "sc/forward.h"

#include <dolphin/mtx.h>

struct grBigBlueRoute_8020DA9C_t {
    /* +0 */ char pad_0[0x8];
    /* +8 */ int x8;
};

typedef struct {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2_5 : 4;
    u8 b6 : 1;
    u8 b7 : 1;
} RouteEntryFlags;

typedef struct {
    RouteEntryFlags flags;
    u8 pad_1[3];
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    f32 x20;
    u8 pad_24[4];
    void* x28;
} RouteEntry;

/* 20B864 */ void grBigBlueRoute_8020B864(bool);
/* 20B89C */ void grBigBlueRoute_8020B89C(void);
/* 20B920 */ void grBigBlueRoute_8020B920(void);
/* 20B95C */ void grBigBlueRoute_8020B95C(void);
/* 20B9CC */ bool grBigBlueRoute_8020B9CC(void);
/* 20B9D4 */ HSD_GObj* grBigBlueRoute_8020B9D4(int);
/* 20BABC */ void grBigBlueRoute_8020BABC(Ground_GObj*);
/* 20BB00 */ bool grBigBlueRoute_8020BB00(Ground_GObj*);
/* 20BB08 */ void grBigBlueRoute_8020BB08(Ground_GObj*);
/* 20BB0C */ void grBigBlueRoute_8020BB0C(Ground_GObj*);
/* 20BB10 */ void grBigBlueRoute_8020BB10(Ground_GObj*);
/* 20BB58 */ bool grBigBlueRoute_8020BB58(Ground_GObj*);
/* 20BB60 */ void grBigBlueRoute_8020BB60(Ground_GObj*);
/* 20BB64 */ void grBigBlueRoute_8020BB64(Ground_GObj*);
/* 20BB68 */ void grBigBlueRoute_8020BB68(Ground_GObj*);
/* 20BC24 */ bool grBigBlueRoute_8020BC24(Ground_GObj*);
/* 20BC2C */ void grBigBlueRoute_8020BC2C(Ground_GObj*);
/* 20BC30 */ void grBigBlueRoute_8020BC30(Ground_GObj*);
/* 20BC34 */ void grBigBlueRoute_8020BC34(Ground_GObj*);
/* 20BC68 */ void grBigBlueRoute_8020BC68(Ground_GObj*);
/* 20BF30 */ bool grBigBlueRoute_8020BF30(Ground_GObj*);
/* 20BF38 */ void grBigBlueRoute_8020BF38(Ground_GObj*);
/* 20C13C */ void grBigBlueRoute_8020C13C(Ground_GObj*);
/* 20C140 */ void grBigBlueRoute_8020C140(Ground_GObj*);
/* 20C1D4 */ bool grBigBlueRoute_8020C1D4(Ground_GObj*);
/* 20C1DC */ void grBigBlueRoute_8020C1DC(Ground_GObj*);
/* 20C210 */ void grBigBlueRoute_8020C210(Ground_GObj*);
/* 20C238 */ void grBigBlueRoute_8020C238(Ground_GObj*);
/* 20C530 */ s32 grBigBlueRoute_8020C530(Ground_GObj*);
/* 20C85C */ void grBigBlueRoute_8020C85C(Ground_GObj*);
/* 20CD20 */ UNK_RET grBigBlueRoute_8020CD20(Ground_GObj*);
/* 20DA9C */ int grBigBlueRoute_8020DA9C(struct grBigBlueRoute_8020DA9C_t*);
/* 20DAB4 */ void grBigBlueRoute_8020DAB4(HSD_JObj**, float, int);
/* 20DD64 */ void grBigBlueRoute_8020DD64(Vec3*);
/* 20DE48 */ DynamicModelDesc* grBigBlueRoute_8020DE48(void);
/* 20DEAC */ UNK_RET fn_8020DEAC(UNK_PARAMS);
/* 20DED4 */ void grBigBlueRoute_8020DED4(Point3d*);
/* 20DF78 */ DynamicsDesc* grBigBlueRoute_8020DF78(enum_t);
/* 20DF80 */ bool grBigBlueRoute_8020DF80(Vec3*, int arg, HSD_JObj* jobj);

#endif
