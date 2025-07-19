#ifndef SYSDOLPHIN_BASELIB_PSAPPSRT_H
#define SYSDOLPHIN_BASELIB_PSAPPSRT_H

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h"

#include "baselib/objalloc.h"

#include <dolphin/mtx.h>

#define PSAPPSRT_UNK_B09 (1 << 9)
#define PSAPPSRT_UNK_B10 (1 << 10)
#define PSAPPSRT_UNK_B11 (1 << 11)

/// @remarks MexTK: GeneratorAppSRT
struct UnkGeneratorMember {
    UNK_T x0;
    UnkGeneratorStruct* x4;
    Vec3 x8;
    Vec3 x14;
    // u8 x20_fill[4];
    u32 x20_unk;
    Vec3 x24;
    u8 x30;
    u8 x31_fill[0x71];
    s8 xA2;
};

/// @remarks MexTK: ptclGen
struct UnkGeneratorStruct {
    UnkGeneratorStruct* next;
    u32 x4_kind;
    u8 x8_fill[0x8];
    HSD_JObj* x10_jobj;
    u16 x14_fill;
    u16 x16_flags;
    u8 x18_fill[0x24 - 0x18];
    f32 x24, x28, x2C;
    u8 x30_fill[0x54 - 0x30];
    UnkGeneratorMember* x54;
};

/// @remarks MexTK: Particle
struct UnkGeneratorStruct2 {
    u8 x0_fill[0x8C - 0x0];
    UnkGeneratorMember* x8C;
    u8 x90_fill[0x98 - 0x90];
};

/* 003A0D18 */ bool psInitAppSRT(int, int);
/* 003A0D58 */ s32 psAddGeneratorAppSRT(s32, u16);
/* 003A0E3C */ void HSD_PSAppSrt_803A425C(UNK_T, s32);
u16 psRemoveGeneratorSRT(UNK_T);
u16 psRemoveParticleAppSRT(UNK_T);
UnkGeneratorMember* psAddGeneratorAppSRT_begin(UnkGeneratorStruct*, s32);
u16 psAttachParticleAppSRT(UNK_T, UNK_T);

extern HSD_ObjAllocData HSD_PSAppSrt_804D10B0;

#endif
