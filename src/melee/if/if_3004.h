#ifndef _IF_3004_H_
#define _IF_3004_H_

#include <Runtime/platform.h>

#include <melee/if/forward.h>

#include <melee/if/types.h>

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

/* 301420 */ bool un_80301420(enum soundtest_callback_arg0);
/* 301BA8 */ void un_80301BA8(struct UnkSoundTestData1* out);
/* 301C64 */ void un_80301C64(un_80301C64_t*);
/* 3FA790 */ extern struct un_80304138_objalloc_t_x8 un_803FA790[4];
/* 3FC4CC */ extern struct un_80304138_objalloc_t_x8 un_803FC4CC[10];

#endif
