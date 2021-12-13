#ifndef _ness_h_
#define _ness_h_
#include <global.h>

#include <dolphin/types.h>
struct ftNess_0 {
    u8 padding0[0x222C];
    u32 unk222C;
    u8 padding1[0x10];
    u32 unk2240;
    u32 unk2244;
    u32 unk2248;
    u32 unk224C;
};
struct ftNess_1 {
    u8 padding[0x2C];
    struct ftNess_0* unk2C;
};
void func_80074A4C(struct ftNess_1* arg0, int arg1, int arg2);

void ftNess_Reset(struct ftNess_1* arg0, s32 arg1);
#endif