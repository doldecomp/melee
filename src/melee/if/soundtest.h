#ifndef _SOUNDTEST_H_
#define _SOUNDTEST_H_

#include <platform.h>

#include "if/forward.h"

#include "if/types.h"

#include "mn/forward.h"

/// @todo Merge with ::SoundTestMenuData
struct SoundTestData {
    u32 x0;
    void (*x4)(void);
    char* x8; ///< "Sound Test Menu"
    u8 pad_xC[0x17];
    u8 x23;
    void (*x24)(void);
    char* x28; ///< "Sound Mode "
};

struct SoundTestMenuData {
    /* 0x000 */ struct un_80304138_objalloc_t_x8 entries[11];
    /* 0x160 */ char x160[0xC];
    /* 0x16C */ char x16C[0x18];
};

/* 2FF7DC */ void un_802FF7DC(void);
/* 2FF884 */ bool un_802FF884(char*);
/* 2FFCD0 */ void un_802FFCD0(int, void*);
/* 2FFD94 */ void un_802FFD94(int a, void* b, soundtest_callback c);
/* 2FFEE0 */ void un_802FFEE0(s32*);
/* 2FFF2C */ void un_802FFF2C(StartMeleeData*);
/* 301BA8 */ void un_80301BA8(void* out);
/* 301C64 */ void un_80301C64(un_80301C64_t*);
/* 3F9FA4 */ extern struct SoundTestMenuData un_803F9FA4;

#endif
