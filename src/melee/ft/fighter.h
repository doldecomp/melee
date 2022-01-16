#ifndef _fighter_h_
#define _fighter_h_
#include <global.h>
#include <dolphin/types.h>
typedef struct _ftAttributes2D4 {
    u8 data[0x94];
    f32 unk94;
} ftAttributes2D4;
typedef struct _Fighter {
    u8 data0[0x2D4];
    ftAttributes2D4* unk2D4;
    u8 data2D8[0x169C];
    s32 x1974;
    u8 data1978[0x8B8];
    u32 x222C;
    u32 x2230;
    u32 x2234;
    u32 x2238;
    u32 x223C;
    u32 x2240;
    u32 x2244;
    u32 x2248;
    u32 x224C;
    u32 data2250[0x19c];
} Fighter;
void func_800704F0(struct _HSD_GObj* arg0, s32 arg1, f32 arg2);
void func_80070CC4(struct _HSD_GObj* arg0, int arg1);
void func_80070FB4(struct _HSD_GObj* arg0, s32 arg1, s32 arg2);
void func_80074A4C(struct _HSD_GObj* arg0, int arg1, int arg2);
// .sdata2
float lbl_804D96B0;

#endif

