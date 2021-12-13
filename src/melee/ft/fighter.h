#ifndef _fighter_h_
#define _fighter_h_
#include <global.h>
#include <dolphin/types.h>
struct Fighter {
    u8 unkData0[0x2D4];
    u8* unk2D4;
    u8 unkData2D8[0x169C];
    s32 unk1974;
    u8 unkData1978[0x8B8];
    u32 unk222C;
    u8 unkData2230[0x10];
    u32 unk2240;
    u32 unk2244;
    u32 unk2248;
    u32 unk224C;
    u32 unkData2250[0x19c];
};
struct ftAttributes2D4 {
    u8 unkData[0x94];
    f32 unk94;
};
void func_800704F0(struct _HSD_GObj* arg0, s32 arg1, f32 arg2);
void func_80070CC4(struct _HSD_GObj* arg0, int arg1);
void func_80070FB4(struct _HSD_GObj* arg0, s32 arg1, s32 arg2);
void func_80074A4C(struct _HSD_GObj* arg0, int arg1, int arg2);
// .sdata2
float lbl_804D96B0;

#endif

