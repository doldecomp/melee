#ifndef MELEE_MN_MAINRULE_H
#define MELEE_MN_MAINRULE_H

#include <placeholder.h>

#include <sysdolphin/baselib/forward.h>

struct mn_80231634_t {
    /*  +0 */ char pad_0[0x10];
    /* +10 */ int x10;
};

/* 22F538 */ void fn_8022F538(HSD_GObj*);
/* 22FB88 */ UNK_RET mn_8022FB88(UNK_PARAMS);
/* 22FD18 */ UNK_RET mn_8022FD18(UNK_PARAMS);
/* 22FEC8 */ UNK_RET mn_8022FEC8(UNK_PARAMS);
/* 230198 */ UNK_RET mn_80230198(UNK_PARAMS);
/* 230274 */ UNK_RET mn_80230274(UNK_PARAMS);
/* 2307F8 */ void mn_802307F8(s32, s32, s32);
/* 2308F0 */ UNK_RET mn_802308F0(UNK_PARAMS);
/* 2309F0 */ UNK_RET fn_802309F0(UNK_PARAMS);
/* 230D18 */ UNK_RET mn_80230D18(UNK_PARAMS);
/* 230E38 */ HSD_GObj* mn_80230E38(int);
/* 231634 */ int mn_80231634(struct mn_80231634_t*);
/* 23164C */ void mn_8023164C(void);
/* 231714 */ void mn_80231714(void);
/* 2317E4 */ void mn_802317E4(HSD_Archive*, int);
/* 231804 */ void mn_80231804(HSD_Archive*, int);
/* 231F80 */ UNK_RET mn_80231F80(UNK_PARAMS);

#endif
