#ifndef DOLPHIN_OS_OSCONTEXT_H
#define DOLPHIN_OS_OSCONTEXT_H

#include <platform.h>

#define __OS_CONTEXT_FRAME 768

#define OS_CONTEXT_R0 0
#define OS_CONTEXT_R1 4
#define OS_CONTEXT_R2 8
#define OS_CONTEXT_R3 12
#define OS_CONTEXT_R4 16
#define OS_CONTEXT_R5 20
#define OS_CONTEXT_R6 24
#define OS_CONTEXT_R7 28
#define OS_CONTEXT_R8 32
#define OS_CONTEXT_R9 36
#define OS_CONTEXT_R10 40
#define OS_CONTEXT_R11 44
#define OS_CONTEXT_R12 48
#define OS_CONTEXT_R13 52
#define OS_CONTEXT_R14 56
#define OS_CONTEXT_R15 60
#define OS_CONTEXT_R16 64
#define OS_CONTEXT_R17 68
#define OS_CONTEXT_R18 72
#define OS_CONTEXT_R19 76
#define OS_CONTEXT_R20 80
#define OS_CONTEXT_R21 84
#define OS_CONTEXT_R22 88
#define OS_CONTEXT_R23 92
#define OS_CONTEXT_R24 96
#define OS_CONTEXT_R25 100
#define OS_CONTEXT_R26 104
#define OS_CONTEXT_R27 108
#define OS_CONTEXT_R28 112
#define OS_CONTEXT_R29 116
#define OS_CONTEXT_R30 120
#define OS_CONTEXT_R31 124

#define OS_CONTEXT_CR 128
#define OS_CONTEXT_LR 132
#define OS_CONTEXT_CTR 136
#define OS_CONTEXT_XER 140

#define OS_CONTEXT_FPR0 144
#define OS_CONTEXT_FPR1 152
#define OS_CONTEXT_FPR2 160
#define OS_CONTEXT_FPR3 168
#define OS_CONTEXT_FPR4 176
#define OS_CONTEXT_FPR5 184
#define OS_CONTEXT_FPR6 192
#define OS_CONTEXT_FPR7 200
#define OS_CONTEXT_FPR8 208
#define OS_CONTEXT_FPR9 216
#define OS_CONTEXT_FPR10 224
#define OS_CONTEXT_FPR11 232
#define OS_CONTEXT_FPR12 240
#define OS_CONTEXT_FPR13 248
#define OS_CONTEXT_FPR14 256
#define OS_CONTEXT_FPR15 264
#define OS_CONTEXT_FPR16 272
#define OS_CONTEXT_FPR17 280
#define OS_CONTEXT_FPR18 288
#define OS_CONTEXT_FPR19 296
#define OS_CONTEXT_FPR20 304
#define OS_CONTEXT_FPR21 312
#define OS_CONTEXT_FPR22 320
#define OS_CONTEXT_FPR23 328
#define OS_CONTEXT_FPR24 336
#define OS_CONTEXT_FPR25 344
#define OS_CONTEXT_FPR26 352
#define OS_CONTEXT_FPR27 360
#define OS_CONTEXT_FPR28 368
#define OS_CONTEXT_FPR29 376
#define OS_CONTEXT_FPR30 384
#define OS_CONTEXT_FPR31 392

#define OS_CONTEXT_FPSCR 400

#define OS_CONTEXT_SRR0 408
#define OS_CONTEXT_SRR1 412

#define OS_CONTEXT_MODE 416
#define OS_CONTEXT_STATE 418

#define OS_CONTEXT_GQR0 420
#define OS_CONTEXT_GQR1 424
#define OS_CONTEXT_GQR2 428
#define OS_CONTEXT_GQR3 432
#define OS_CONTEXT_GQR4 436
#define OS_CONTEXT_GQR5 440
#define OS_CONTEXT_GQR6 444
#define OS_CONTEXT_GQR7 448
#define __OSCONTEXT_PADDING 452

#define OS_CONTEXT_PSF0 456
#define OS_CONTEXT_PSF1 464
#define OS_CONTEXT_PSF2 472
#define OS_CONTEXT_PSF3 480
#define OS_CONTEXT_PSF4 488
#define OS_CONTEXT_PSF5 496
#define OS_CONTEXT_PSF6 504
#define OS_CONTEXT_PSF7 512
#define OS_CONTEXT_PSF8 520
#define OS_CONTEXT_PSF9 528
#define OS_CONTEXT_PSF10 536
#define OS_CONTEXT_PSF11 544
#define OS_CONTEXT_PSF12 552
#define OS_CONTEXT_PSF13 560
#define OS_CONTEXT_PSF14 568
#define OS_CONTEXT_PSF15 576
#define OS_CONTEXT_PSF16 584
#define OS_CONTEXT_PSF17 592
#define OS_CONTEXT_PSF18 600
#define OS_CONTEXT_PSF19 608
#define OS_CONTEXT_PSF20 616
#define OS_CONTEXT_PSF21 624
#define OS_CONTEXT_PSF22 632
#define OS_CONTEXT_PSF23 640
#define OS_CONTEXT_PSF24 648
#define OS_CONTEXT_PSF25 656
#define OS_CONTEXT_PSF26 664
#define OS_CONTEXT_PSF27 672
#define OS_CONTEXT_PSF28 680
#define OS_CONTEXT_PSF29 688
#define OS_CONTEXT_PSF30 696
#define OS_CONTEXT_PSF31 704
#define OS_CONTEXT_STATE_EXC 0x02u

#define OS_CONTEXT_STATE_FPSAVED 0x01u

typedef struct OSContext {
    u32 gprs[32];  // at 0x0
    u32 cr;        // at 0x80
    u32 lr;        // at 0x84
    u32 ctr;       // at 0x88
    u32 xer;       // at 0x8C
    f64 fprs[32];  // at 0x90
    u32 fpscr_pad; // at 0x190
    u32 fpscr;     // at 0x194
    u32 srr0;      // at 0x198
    u32 srr1;      // at 0x19C
    u16 mode;      // at 0x1A0
    u16 state;     // at 0x1A2
    u32 gqrs[8];   // at 0x1A4
    f64 psfs[32];  // at 0x1C8
} OSContext;

extern OSContext* OS_CURRENT_CONTEXT AT_ADDRESS(0x800000D4);
extern OSContext* OS_CURRENT_FPU_CONTEXT AT_ADDRESS(0x800000D8);

void OSSaveFPUContext(OSContext*);
void OSSetCurrentContext(OSContext*);
OSContext* OSGetCurrentContext(void);
bool OSSaveContext(OSContext*);
void OSLoadContext(OSContext*);
void* OSGetStackPointer(void);
void OSSwitchFiber(void*, void*);
void OSSwitchFiberEx(u32, u32, u32, u32, void*, void*);
void OSClearContext(OSContext*);
void OSInitContext(OSContext* ctx, u32 pc, u32 newsp);
void OSDumpContext(const OSContext*);
void __OSContextInit(void);
void __OSLoadFPUContext(u32 _, OSContext* fpuctx);
void OSLoadFPUContext(OSContext* fpuctx);
void __OSSaveFPUContext(u32 unused1, u32 unused2, OSContext* fpuctx);

#endif
