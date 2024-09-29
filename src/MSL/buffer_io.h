#ifndef _BUFFER_IO_H_
#define _BUFFER_IO_H_

#include <platform.h>

typedef struct _BufferIoUnkFlagStruct {
    /* 0x00 */ struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
} BufferIoUnkFlagStruct;

typedef struct _BufferIoUnkStruct {
    /* 0x00 */ s32 x00;
    /* 0x04 */ BufferIoUnkFlagStruct x04;
    /* 0x05 */ BufferIoUnkFlagStruct x05;
    /* 0x06 */ BufferIoUnkFlagStruct x06;
    /* 0x07 */ BufferIoUnkFlagStruct x07;
    /* 0x08 */ s32 x08_filler[3];
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ s32 x28;
    /* 0x2C */ s32 x2C_filler;
    /* 0x30 */ s32 x30;
    /* 0x34 */ s32 x34_filler[2];
    /* 0x3C */ s32 (*x3C)(s32 x3C_arg0, s32 x3C_arg1, s32* x3C_arg2,
                          s32 x3C_arg3);
    /* 0x40 */ s32 x40_filler;
    /* 0x44 */ s32 x44;
} BufferIoUnkStruct;

void __prep_buffer(BufferIoUnkStruct* arg0);
s32 __flush_buffer(BufferIoUnkStruct* arg0, s32* arg1);

#endif
