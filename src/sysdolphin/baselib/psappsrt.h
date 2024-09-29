#ifndef SYSDOLPHIN_BASELIB_PSAPPSRT_H
#define SYSDOLPHIN_BASELIB_PSAPPSRT_H

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h"

#include <dolphin/mtx/types.h>

#define PSAPPSRT_UNK_B09 (1 << 9)
#define PSAPPSRT_UNK_B10 (1 << 10)
#define PSAPPSRT_UNK_B11 (1 << 11)

/// MexTK: GeneratorAppSRT
struct UnkGeneratorMember {
    UNK_T x0;
    UnkGeneratorStruct* x4;
    S32Vec3 x8;
    u8 x14_fill[0x10];
    f32 x24;
    f32 x28;
    f32 x2C;
    u8 x30_fill[0x72];
    s8 xA2;
};

/// @remarks MexTK: Particle
struct UnkGeneratorStruct {
    UnkGeneratorStruct* next;
    u8 x4_fill[0xC];
    HSD_JObj* x10_jobj;
    u16 x14_fill;
    u16 x16_flags;
    u8 x18_fill[0x24 - 0x18];
    f32 x24, x28, x2C;
    u8 x30_fill[0x54 - 0x30];
    UnkGeneratorMember* x54;
};

/* 003A0D18 */ bool psInitAppSRT(int, int);
/* 003A0D58 */ s32 psAddGeneratorAppSRT(s32, u16);
/* 003A0E3C */ void HSD_PSAppSrt_803A425C(UNK_T, s32);
u16 psRemoveGeneratorSRT(UNK_T);
u16 psRemoveParticleAppSRT(UNK_T);
UnkGeneratorMember* psAddGeneratorAppSRT_begin(UnkGeneratorStruct*, s32);
u16 psAttachParticleAppSRT(UNK_T, UNK_T);

#endif
