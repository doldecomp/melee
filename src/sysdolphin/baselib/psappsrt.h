#ifndef SYSDOLPHIN_BASELIB_PSAPPSRT_H
#define SYSDOLPHIN_BASELIB_PSAPPSRT_H

#include <platform.h>
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

typedef struct _UnkGeneratorMember { // MexTK: GeneratorAppSRT
    u32 x0_fill[2];
    S32Vec3 x8;
    u8 x14_fill[0x10];
    f32 x24;
    f32 x28;
    f32 x2C;
    u8 x30_fill[0x72];
    s8 xA2;
} UnkGeneratorMember;

/// @remarks MexTK: Particle
struct UnkGeneratorStruct {
    struct UnkGeneratorStruct* next;
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
/* 003A0E3C */ void HSD_PSAppSrt_803A425C(unk_t, s32);
u16 psRemoveGeneratorSRT(unk_t);
u16 psRemoveParticleAppSRT(unk_t);
UnkGeneratorMember* psAddGeneratorAppSRT_begin(UnkGeneratorStruct*, s32);
u16 psAttachParticleAppSRT(unk_t, unk_t);

#endif
