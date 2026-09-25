#ifndef _SOUNDTEST_H_
#define _SOUNDTEST_H_

#include <Runtime/platform.h>

#include <melee/if/forward.h>

#include <melee/if/types.h>

struct SoundTestMenuData {
    /* 0x000 */ struct un_80304138_objalloc_t_x8 entries[11];
    /* 0x160 */ char x160[0xC];
    /* 0x16C */ char x16C[0x18];
};

/* 2FF7DC */ void un_802FF7DC(void);
/* 2FF884 */ bool un_802FF884(char*);
/* 3F9FA4 */ extern struct SoundTestMenuData un_803F9FA4;

#endif
