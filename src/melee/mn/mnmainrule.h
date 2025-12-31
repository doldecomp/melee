#ifndef MELEE_MN_MAINRULE_H
#define MELEE_MN_MAINRULE_H

#include <placeholder.h>

#include <sysdolphin/baselib/forward.h>

struct mn_80231634_t {
    /*  +0 */ char pad_0[0x10];
    /* +10 */ int x10;
};

/* 22F538 */ void fn_8022F538(HSD_GObj*);
/* 22FB88 */ void mn_8022FB88(u8 arg0, s32 arg1);
/* 22FD18 */ void mn_8022FD18(u8 arg0);
/* 22FEC8 */ void mn_8022FEC8(HSD_GObj* gobj, s32 arg1, u8 arg2);
/* 230198 */ void mn_80230198(void* arg0, s32 arg1, u8 arg2);
/* 230274 */ void mn_80230274(void);
/* 2307F8 */ void mn_802307F8(s32 arg0, s32 arg1, s32 arg2);
/* 2308F0 */ void mn_802308F0(HSD_GObj* gobj, s32 arg1);
/* 2309F0 */ void fn_802309F0(HSD_GObj* gobj);
/* 230D18 */ void mn_80230D18(HSD_GObj* gobj, s32 arg1);
/* 230E38 */ HSD_GObj* mn_80230E38(int);
/* 231634 */ int mn_80231634(struct mn_80231634_t*);
/* 23164C */ void mn_8023164C(void);
/* 231714 */ void mn_80231714(void);
/* 2317E4 */ void mn_802317E4(HSD_Archive*, int);
/* 231804 */ void mn_80231804(HSD_Archive*, int);
/* 231F80 */ void mn_80231F80(HSD_GObj* gobj);
/* 23201C */ void fn_8023201C(HSD_GObj* gobj);
/* 232458 */ void mn_80232458(u8 arg0);
/* 2324E4 */ void mn_802324E4(u8 arg0, void* arg1);
/* 232660 */ void mn_80232660(HSD_GObj* gobj, s32 arg1, u8 arg2);
/* 2327A4 */ void mn_802327A4(void);
/* 232D4C */ void mn_80232D4C(HSD_GObj* gobj, s32 arg1);
/* 232F44 */ void fn_80232F44(HSD_GObj* gobj);
/* 233218 */ void mn_80233218(HSD_GObj* gobj);
/* 2339FC */ void mn_802339FC(void);

#endif
