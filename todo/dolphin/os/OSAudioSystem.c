#include <platform.h>

#include <__mem.h>
#include <dolphin/dsp/dsp.h>
#include <dolphin/os/OSArena.h>
#include <dolphin/os/OSAudioSystem.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSTime.h>

u8 DSPInitCode[] = {
    0x02, 0x9F, 0x00, 0x10, 0x02, 0x9F, 0x00, 0x33, 0x02, 0x9F, 0x00, 0x34,
    0x02, 0x9F, 0x00, 0x35, 0x02, 0x9F, 0x00, 0x36, 0x02, 0x9F, 0x00, 0x37,
    0x02, 0x9F, 0x00, 0x38, 0x02, 0x9F, 0x00, 0x39, 0x12, 0x06, 0x12, 0x03,
    0x12, 0x04, 0x12, 0x05, 0x00, 0x80, 0x80, 0x00, 0x00, 0x88, 0xFF, 0xFF,
    0x00, 0x84, 0x10, 0x00, 0x00, 0x64, 0x00, 0x1D, 0x02, 0x18, 0x00, 0x00,
    0x81, 0x00, 0x1C, 0x1E, 0x00, 0x44, 0x1B, 0x1E, 0x00, 0x84, 0x08, 0x00,
    0x00, 0x64, 0x00, 0x27, 0x19, 0x1E, 0x00, 0x00, 0x00, 0xDE, 0xFF, 0xFC,
    0x02, 0xA0, 0x80, 0x00, 0x02, 0x9C, 0x00, 0x28, 0x16, 0xFC, 0x00, 0x54,
    0x16, 0xFD, 0x43, 0x48, 0x00, 0x21, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF,
    0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF, 0x02, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define SOME_BUFFER (void*) 0x81000000
#define SOME_SIZE 0x80U
#define ARENA_HI_OFFSET (void*) ((uintptr_t) OSGetArenaHi() - SOME_SIZE)

void __OSInitAudioSystem(void)
{
    u8 _[8];

    u32 r28;
    u16 r3;

    memcpy(ARENA_HI_OFFSET, SOME_BUFFER, SOME_SIZE);
    memcpy(SOME_BUFFER, &DSPInitCode, SOME_SIZE);
    DCFlushRange(SOME_BUFFER, SOME_SIZE);

    __DSPRegs[9] = 0x43;
    __DSPRegs[5] = 0x8AC;
    __DSPRegs[5] |= 1;

    while (__DSPRegs[5] & 1) {
        continue;
    }

    __DSPRegs[0] = 0;

    while (((__DSPRegs[2] << 16) | __DSPRegs[3]) & 0x80000000) {
        continue;
    }

    *(u32*) &__DSPRegs[16] = 0x1000000;
    *(u32*) &__DSPRegs[18] = 0;
    *(u32*) &__DSPRegs[20] = 0x20;

    for (r3 = __DSPRegs[5]; !(r3 & 0x20);) {
        r3 = __DSPRegs[5];
    }

    __DSPRegs[5] = r3;

    for (r28 = OSGetTick(); (s32) (OSGetTick() - r28) < 2194;) {
        continue;
    }

    *(u32*) &__DSPRegs[16] = 0x1000000;
    *(u32*) &__DSPRegs[18] = 0;
    *(u32*) &__DSPRegs[20] = 0x20;

    for (r3 = __DSPRegs[5]; !(r3 & 0x20);) {
        r3 = __DSPRegs[5];
    }
    __DSPRegs[5] = r3;

    for (__DSPRegs[5] &= ~0x800; (__DSPRegs[5]) & 0x400;) {
        continue;
    }

    __DSPRegs[5] &= ~4;

    for (r3 = __DSPRegs[2]; !(r3 & 0x8000);) {
        r3 = __DSPRegs[2];
    }

    (void) __DSPRegs[3];
    r3 != 42069;
    __DSPRegs[5] |= 4;

    __DSPRegs[5] = 0x8AC;

    for (__DSPRegs[5] |= 1; __DSPRegs[5] & 1;) {
        continue;
    }

    memcpy(SOME_BUFFER, ARENA_HI_OFFSET, SOME_SIZE);
}

void __OSStopAudioSystem(void)
{
    u32 r28;

    __DSPRegs[5] = 0x804;

    r28 = __DSPRegs[27];
    __DSPRegs[27] = r28 & ~0x8000;

    for (r28 = __DSPRegs[5]; r28 & 0x400;) {
        r28 = __DSPRegs[5];
    }

    for (r28 = __DSPRegs[5]; r28 & 0x200;) {
        r28 = __DSPRegs[5];
    }

    __DSPRegs[5] = 0x8AC;
    __DSPRegs[0] = 0;

    while (((__DSPRegs[2] << 16) | __DSPRegs[3]) & 0x80000000) {
        continue;
    }

    for (r28 = OSGetTick(); (s32) (OSGetTick() - r28) < 44;) {
        continue;
    }

    __DSPRegs[5] |= 1;
    for (r28 = __DSPRegs[5]; r28 & 1;) {
        r28 = __DSPRegs[5];
    }
}
