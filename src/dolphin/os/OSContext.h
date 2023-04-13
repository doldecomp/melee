#ifndef DOLPHIN_OS_OSCONTEXT_H
#define DOLPHIN_OS_OSCONTEXT_H

#include <platform.h>
#include <dolphin/os/forward.h>

struct OSContext {
    u32 gprs[32]; // at 0x0
    u32 cr;       // at 0x80
    u32 lr;       // at 0x84
    u32 ctr;      // at 0x88
    u32 xer;      // at 0x8C
    f64 fprs[32]; // at 0x90
    f64 fpscr;    // at 0x190
    u32 srr0;     // at 0x198
    u32 srr1;     // at 0x19C
    u16 mode;     // at 0x1A0
    u16 state;    // at 0x1A2
    u32 gqrs[8];  // at 0x1A4
    f64 psfs[32]; // at 0x1C8
};

extern OSContext* OS_CURRENT_CONTEXT AT_ADDRESS(0x800000D4);
extern OSContext* OS_CURRENT_FPU_CONTEXT AT_ADDRESS(0x800000D8);

void OSSaveFPUContext(OSContext*);
void OSSetCurrentContext(OSContext*);
OSContext* OSGetCurrentContext(void);
bool OSSaveContext(OSContext*);
void OSLoadContext(OSContext*);
any_t OSGetStackPointer(void);
void OSSwitchFiber(void*, void*);
void OSSwitchFiberEx(u32, u32, u32, u32, void*, void*);
void OSClearContext(OSContext*);
void OSInitContext(OSContext* ctx, u32 pc, u32 newsp);
void OSDumpContext(const OSContext*);
void __OSContextInit(void);
void __OSLoadFPUContext(u32 _, OSContext* fpuctx);
void OSLoadFPUContext(OSContext* fpuctx);
void OSSwitchFPUContext(OSException _, OSContext* ctx);
void __OSSaveFPUContext(u32 unused1, u32 unused2, OSContext* fpuctx);

#endif
