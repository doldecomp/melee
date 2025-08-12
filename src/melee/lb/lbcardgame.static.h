#ifndef __GALE01_019880
#define __GALE01_019880

#include "lbcardgame.h" // IWYU pragma: export

#include <placeholder.h>
#include <platform.h>

#include <dolphin/os/OSAlarm.h>
#include <sysdolphin/baselib/cobj.h>
#include <melee/sc/types.h>

struct lb_80433318_t {
    /* +0  */ int x0;
    /* +4  */ int x4;
    /* +8  */ int x8;
    /* +C  */ bool xC;
    /* +10 */ int x10;
    /* +14 */ int x14;
    /* +18 */ bool enable;
    /* +30 */ char _1C[0x40];
    /* +5C */ int* x5C;
    /* +60 */ int x60;
    /* +64 */ SceneDesc* x64;
};
STATIC_ASSERT(sizeof(struct lb_80433318_t) == 0x68);

/* 433318 */ static struct lb_80433318_t lb_80433318;

#endif
