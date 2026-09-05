#ifndef _SOUNDTEST_H_
#define _SOUNDTEST_H_

#include <Runtime/platform.h>

#include <melee/if/forward.h>

#include <melee/if/types.h>

#include <melee/mn/forward.h>

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

struct UnkSoundTestData1 {
    /* 0x00 */ s32 unk_0; /* inferred */
    /* 0x04 */ s32 unk_4; /* inferred */
    /* 0x08 */ u8 unk_8;  /* inferred */
    /* 0x09 */ u8 unk_9;  /* inferred */
    /* 0x0A */ u8 unk_A;  /* inferred */
    /* 0x0B */ u8 unk_B;  /* inferred */
    /* 0x0C */ u8 unk_C;  /* inferred */
    /* 0x0D */ u8 unk_D;  /* inferred */
    /* 0x0E */ u8 unk_E;  /* inferred */
    /* 0x0F */ u8 unk_F;  /* inferred */
    /* 0x10 */ u8 unk_10; /* inferred */
    /* 0x11 */ u8 unk_11; /* inferred */
    /* 0x12 */ u8 unk_12; /* inferred */
    /* 0x13 */ u8 unk_13; /* inferred */
    /* 0x14 */ u8 unk_14; /* inferred */
    /* 0x15 */ u8 unk_15; /* inferred */
    /* 0x16 */ u8 unk_16; /* inferred */
    /* 0x17 */ u8 unk_17; /* inferred */
    /* 0x18 */ u8 unk_18; /* inferred */
    /* 0x19 */ u8 unk_19; /* inferred */
    /* 0x1A */ u8 unk_1A; /* inferred */
    /* 0x1B */ u8 unk_1B; /* inferred */
    /* 0x1C */ u8 unk_1C; /* inferred */
    /* 0x1D */ u8 unk_1D; /* inferred */
    /* 0x1E */ u8 unk_1E; /* inferred */
}; /* size = 0x20 */
ASSERT_SIZE(struct UnkSoundTestData1, 0x20);

/* 2FF7DC */ void un_802FF7DC(void);
/* 2FF884 */ bool un_802FF884(char*);
/* 2FFCD0 */ void un_802FFCD0(int, void*);
/* 2FFD94 */ void un_802FFD94(int a, void* b, soundtest_callback c);
/* 2FFEE0 */ void un_802FFEE0(struct UnkSoundTestData0*);
/* 2FFF2C */ void un_802FFF2C(StartMeleeData*);
/* 301BA8 */ void un_80301BA8(struct UnkSoundTestData1* out);
/* 301C64 */ void un_80301C64(un_80301C64_t*);
/* 3F9FA4 */ extern struct SoundTestMenuData un_803F9FA4;
/* 3FA4E0 */ extern struct un_80304138_objalloc_t_x8 un_803FA4E0[11];
/* 3FA790 */ extern struct un_80304138_objalloc_t_x8 un_803FA790[4];
/* 3FC4CC */ extern struct un_80304138_objalloc_t_x8 un_803FC4CC[10];

#endif
