#ifndef GALE01_3B3408
#define GALE01_3B3408

#include <Runtime/platform.h>

#include <setjmp.h>

typedef struct JpegWork {
    jmp_buf buf;
    s32 x118[0x100];
    s32 x518[0x40];
    s32 x618[0x40];
    s32 coef[0x40];
    s32 prev_dc[3];
} JpegWork;

/* 3B3408 */ void hsd_803B3408(u8*, s32, s32, s32, s32);
/* 3B3CD8 */ void hsd_803B3CD8(s32);
/* 3B46D4 */ void hsd_803B46D4(void);
/* 3B4A2C */ void hsd_803B4A2C(void);
/* 3B4D64 */ void hsd_803B4D64(u32, u32);
/* 3B51C8 */ s32 hsd_803B51C8(s32, s32, s32, char*, s32);
/* 3B5C2C */ void hsd_803B5C2C(s32);
/* 3B5C4C */ s32 hsd_803B5C4C(s32);
/* 3B5D70 */ s32 hsd_803B5D70(s32, s32);
/* 3B5EA0 */ void hsd_803B5EA0(s32);
/* 3B6BE4 */ s32 hsd_803B6BE4(char*, s32, void*);

#endif
