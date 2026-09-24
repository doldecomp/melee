#ifndef _SOUNDTEST_H_
#define _SOUNDTEST_H_

#include <Runtime/platform.h>

#include <melee/if/forward.h>
#include <melee/mn/forward.h>

#include <melee/if/types.h>

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

struct UnkSoundTestData0 {
    u16 x0;
    u16 x2;
    s32 x4;
    s32 x8;
};
ASSERT_SIZE(struct UnkSoundTestData0, 0xC);

struct un_803FA258_t {
    /* 0x000 */ int x0;
    /* 0x004 */ int x4;
    /* 0x008 */ int x8;
    /* 0x00C */ int xC;
    /* 0x010 */ int x10[5];
    /* 0x024 */ int x24[5];
    /* 0x038 */ int x38[4];
    /* 0x048 */ int x48[4];
    /* 0x058 */ int x58[4];
    /* 0x068 */ int x68[4];
    /* 0x078 */ f32 x78[4];
    /* 0x088 */ f32 x88[4];
    /* 0x098 */ f32 x98[4];
    /* 0x0A8 */ int xA8[4];
    /* 0x0B8 */ int xB8[4];
    /* 0x0C8 */ int xC8;
    /* 0x0CC */ int xCC[4];
    /* 0x0DC */ int xDC[4];
    /* 0x0EC */ f32 xEC;
    /* 0x0F0 */ u16 xF0;
    /* 0x0F2 */ u8 _padF2[2];
    /* 0x0F4 */ u8 xF4;
    /* 0x0F5 */ u8 xF5;
    /* 0x0F6 */ u8 xF6;
    /* 0x0F7 */ u8 xF7;
    /* 0x0F8 */ int xF8;
    /* 0x0FC */ int xFC;
    /* 0x100 */ int x100;
    /* 0x104 */ int x104;
    /* 0x108 */ int x108;
    /* 0x10C */ int x10C;
    /* 0x110 */ int x110;
    /* 0x114 */ int x114;
    /* 0x118 */ int x118;
    /* 0x11C */ int x11C;
    /* 0x120 */ int x120;
    /* 0x124 */ int x124;
    /* 0x128 */ int x128;
    /* 0x12C */ int x12C;
    /* 0x130 */ int x130;
    /* 0x134 */ int x134;
    /* 0x138 */ void* x138;
    /* 0x13C */ int x13C;
    /* 0x140 */ int x140;
    /* 0x144 */ int x144[17];
    /* 0x188 */ int x188;
    /* 0x18C */ int x18C;
};

/* 2FF7DC */ void un_802FF7DC(void);
/* 2FF884 */ bool un_802FF884(char*);
/* 2FFCD0 */ void un_802FFCD0(int, void*);
/* 2FFD94 */ void un_802FFD94(int a, void* b, soundtest_callback c);
/* 2FFE0C */ bool fn_802FFE0C(enum soundtest_callback_arg0);
/* 2FFE6C */ bool fn_802FFE6C(enum soundtest_callback_arg0);
/* 2FFEA4 */ bool un_802FFEA4(enum soundtest_callback_arg0);
/* 2FFEE0 */ void un_802FFEE0(struct UnkSoundTestData0*);
/* 2FFF2C */ void un_802FFF2C(StartMeleeData*);
/* 3F9FA4 */ extern struct SoundTestMenuData un_803F9FA4;
/* 3FA4E0 */ extern struct un_80304138_objalloc_t_x8 un_803FA4E0[11];
/* 4D5880 */ extern char* un_804D5880[2];

#endif
