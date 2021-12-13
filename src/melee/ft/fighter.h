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
struct ftAttributes {
    u8 unkData[0x94];
    f32 unk94;
};
#endif