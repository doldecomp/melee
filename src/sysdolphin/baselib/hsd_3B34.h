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
/* 4D79A0 */ extern u8* hsd_804D79A0;
/* 4D79A4 */ extern u8* hsd_804D79A4;
/* 4D79A8 */ extern s32 hsd_804D79A8;
/* 4D79AC */ extern s32 hsd_804D79AC;
/* 4D79B0 */ extern u8 hsd_804D79B0[8];
/* 4D79B8 */ extern u8* hsd_804D79B8;
/* 4D79BC */ extern u8* hsd_804D79BC;
/* 4D79C0 */ extern s32 hsd_804D79C0;
/* 4D79C4 */ extern s32 hsd_804D79C4;
/* 4D79C8 */ extern u8 hsd_804D79C8;

#endif
