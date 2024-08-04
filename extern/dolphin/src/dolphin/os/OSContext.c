#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

#define HID2 920

volatile OSContext* __OSCurrentContext : (OS_BASE_CACHED | 0x00D4);
volatile OSContext* __OSFPUContext : (OS_BASE_CACHED | 0x00D8);

static asm void __OSLoadFPUContext(register u32, register OSContext* fpuContext) {
  // clang-format off
  nofralloc
  lhz r5, fpuContext->state;
  clrlwi. r5, r5, 31
  beq _return

  lfd fp0, OS_CONTEXT_FPSCR(fpuContext)
  mtfsf 0xFF, fp0
  mfspr r5, HID2
  rlwinm. r5, r5, 3, 31, 31
  beq _regular_FPRs
  
  psq_l fp0, OS_CONTEXT_PSF0(fpuContext), 0, 0
  psq_l fp1, OS_CONTEXT_PSF1(fpuContext), 0, 0
  psq_l fp2, OS_CONTEXT_PSF2(fpuContext), 0, 0
  psq_l fp3, OS_CONTEXT_PSF3(fpuContext), 0, 0
  psq_l fp4, OS_CONTEXT_PSF4(fpuContext), 0, 0
  psq_l fp5, OS_CONTEXT_PSF5(fpuContext), 0, 0
  psq_l fp6, OS_CONTEXT_PSF6(fpuContext), 0, 0
  psq_l fp7, OS_CONTEXT_PSF7(fpuContext), 0, 0
  psq_l fp8, OS_CONTEXT_PSF8(fpuContext), 0, 0
  psq_l fp9, OS_CONTEXT_PSF9(fpuContext), 0, 0
  psq_l fp10, OS_CONTEXT_PSF10(fpuContext), 0, 0
  psq_l fp11, OS_CONTEXT_PSF11(fpuContext), 0, 0
  psq_l fp12, OS_CONTEXT_PSF12(fpuContext), 0, 0
  psq_l fp13, OS_CONTEXT_PSF13(fpuContext), 0, 0
  psq_l fp14, OS_CONTEXT_PSF14(fpuContext), 0, 0
  psq_l fp15, OS_CONTEXT_PSF15(fpuContext), 0, 0
  psq_l fp16, OS_CONTEXT_PSF16(fpuContext), 0, 0
  psq_l fp17, OS_CONTEXT_PSF17(fpuContext), 0, 0
  psq_l fp18, OS_CONTEXT_PSF18(fpuContext), 0, 0
  psq_l fp19, OS_CONTEXT_PSF19(fpuContext), 0, 0
  psq_l fp20, OS_CONTEXT_PSF20(fpuContext), 0, 0
  psq_l fp21, OS_CONTEXT_PSF21(fpuContext), 0, 0
  psq_l fp22, OS_CONTEXT_PSF22(fpuContext), 0, 0
  psq_l fp23, OS_CONTEXT_PSF23(fpuContext), 0, 0
  psq_l fp24, OS_CONTEXT_PSF24(fpuContext), 0, 0
  psq_l fp25, OS_CONTEXT_PSF25(fpuContext), 0, 0
  psq_l fp26, OS_CONTEXT_PSF26(fpuContext), 0, 0
  psq_l fp27, OS_CONTEXT_PSF27(fpuContext), 0, 0
  psq_l fp28, OS_CONTEXT_PSF28(fpuContext), 0, 0
  psq_l fp29, OS_CONTEXT_PSF29(fpuContext), 0, 0
  psq_l fp30, OS_CONTEXT_PSF30(fpuContext), 0, 0
  psq_l fp31, OS_CONTEXT_PSF31(fpuContext), 0, 0

_regular_FPRs:
  lfd fp0,  fpuContext->fpr[0]
  lfd fp1,  fpuContext->fpr[1]
  lfd fp2,  fpuContext->fpr[2]
  lfd fp3,  fpuContext->fpr[3]
  lfd fp4,  fpuContext->fpr[4]
  lfd fp5,  fpuContext->fpr[5]
  lfd fp6,  fpuContext->fpr[6]
  lfd fp7,  fpuContext->fpr[7]
  lfd fp8,  fpuContext->fpr[8]
  lfd fp9,  fpuContext->fpr[9]
  lfd fp10, fpuContext->fpr[10]
  lfd fp11, fpuContext->fpr[11]
  lfd fp12, fpuContext->fpr[12]
  lfd fp13, fpuContext->fpr[13]
  lfd fp14, fpuContext->fpr[14]
  lfd fp15, fpuContext->fpr[15]
  lfd fp16, fpuContext->fpr[16]
  lfd fp17, fpuContext->fpr[17]
  lfd fp18, fpuContext->fpr[18]
  lfd fp19, fpuContext->fpr[19]
  lfd fp20, fpuContext->fpr[20]
  lfd fp21, fpuContext->fpr[21]
  lfd fp22, fpuContext->fpr[22]
  lfd fp23, fpuContext->fpr[23]
  lfd fp24, fpuContext->fpr[24]
  lfd fp25, fpuContext->fpr[25]
  lfd fp26, fpuContext->fpr[26]
  lfd fp27, fpuContext->fpr[27]
  lfd fp28, fpuContext->fpr[28]
  lfd fp29, fpuContext->fpr[29]
  lfd fp30, fpuContext->fpr[30]
  lfd fp31, fpuContext->fpr[31]
_return:
  blr
  // clang-format on
}


static asm void __OSSaveFPUContext(register u32, register u32, register OSContext* fpuContext) {
  // clang-format off
  nofralloc

  lhz     r3,   fpuContext->state
  ori     r3,   r3, 1
  sth     r3,   fpuContext->state

  stfd    fp0,  fpuContext->fpr[0]
  stfd    fp1,  fpuContext->fpr[1]
  stfd    fp2,  fpuContext->fpr[2]
  stfd    fp3,  fpuContext->fpr[3]
  stfd    fp4,  fpuContext->fpr[4]
  stfd    fp5,  fpuContext->fpr[5]
  stfd    fp6,  fpuContext->fpr[6]
  stfd    fp7,  fpuContext->fpr[7]
  stfd    fp8,  fpuContext->fpr[8]
  stfd    fp9,  fpuContext->fpr[9]
  stfd    fp10, fpuContext->fpr[10]
  stfd    fp11, fpuContext->fpr[11]
  stfd    fp12, fpuContext->fpr[12]
  stfd    fp13, fpuContext->fpr[13]
  stfd    fp14, fpuContext->fpr[14]
  stfd    fp15, fpuContext->fpr[15]
  stfd    fp16, fpuContext->fpr[16]
  stfd    fp17, fpuContext->fpr[17]
  stfd    fp18, fpuContext->fpr[18]
  stfd    fp19, fpuContext->fpr[19]
  stfd    fp20, fpuContext->fpr[20]
  stfd    fp21, fpuContext->fpr[21]
  stfd    fp22, fpuContext->fpr[22]
  stfd    fp23, fpuContext->fpr[23]
  stfd    fp24, fpuContext->fpr[24]
  stfd    fp25, fpuContext->fpr[25]
  stfd    fp26, fpuContext->fpr[26]
  stfd    fp27, fpuContext->fpr[27]
  stfd    fp28, fpuContext->fpr[28]
  stfd    fp29, fpuContext->fpr[29]
  stfd    fp30, fpuContext->fpr[30]
  stfd    fp31, fpuContext->fpr[31]

  mffs    fp0
  stfd    fp0,  OS_CONTEXT_FPSCR(fpuContext)

  lfd     fp0,  fpuContext->fpr[0]

  mfspr   r3, HID2
  rlwinm. r3, r3, 3, 31, 31
  bc      12, 2, _return

  psq_st  fp0, OS_CONTEXT_PSF0(fpuContext), 0, 0
  psq_st  fp1, OS_CONTEXT_PSF1(fpuContext), 0, 0
  psq_st  fp2, OS_CONTEXT_PSF2(fpuContext), 0, 0
  psq_st  fp3, OS_CONTEXT_PSF3(fpuContext), 0, 0
  psq_st  fp4, OS_CONTEXT_PSF4(fpuContext), 0, 0
  psq_st  fp5, OS_CONTEXT_PSF5(fpuContext), 0, 0
  psq_st  fp6, OS_CONTEXT_PSF6(fpuContext), 0, 0
  psq_st  fp7, OS_CONTEXT_PSF7(fpuContext), 0, 0
  psq_st  fp8, OS_CONTEXT_PSF8(fpuContext), 0, 0
  psq_st  fp9, OS_CONTEXT_PSF9(fpuContext), 0, 0
  psq_st  fp10, OS_CONTEXT_PSF10(fpuContext), 0, 0
  psq_st  fp11, OS_CONTEXT_PSF11(fpuContext), 0, 0
  psq_st  fp12, OS_CONTEXT_PSF12(fpuContext), 0, 0
  psq_st  fp13, OS_CONTEXT_PSF13(fpuContext), 0, 0
  psq_st  fp14, OS_CONTEXT_PSF14(fpuContext), 0, 0
  psq_st  fp15, OS_CONTEXT_PSF15(fpuContext), 0, 0
  psq_st  fp16, OS_CONTEXT_PSF16(fpuContext), 0, 0
  psq_st  fp17, OS_CONTEXT_PSF17(fpuContext), 0, 0
  psq_st  fp18, OS_CONTEXT_PSF18(fpuContext), 0, 0
  psq_st  fp19, OS_CONTEXT_PSF19(fpuContext), 0, 0
  psq_st  fp20, OS_CONTEXT_PSF20(fpuContext), 0, 0
  psq_st  fp21, OS_CONTEXT_PSF21(fpuContext), 0, 0
  psq_st  fp22, OS_CONTEXT_PSF22(fpuContext), 0, 0
  psq_st  fp23, OS_CONTEXT_PSF23(fpuContext), 0, 0
  psq_st  fp24, OS_CONTEXT_PSF24(fpuContext), 0, 0
  psq_st  fp25, OS_CONTEXT_PSF25(fpuContext), 0, 0
  psq_st  fp26, OS_CONTEXT_PSF26(fpuContext), 0, 0
  psq_st  fp27, OS_CONTEXT_PSF27(fpuContext), 0, 0
  psq_st  fp28, OS_CONTEXT_PSF28(fpuContext), 0, 0
  psq_st  fp29, OS_CONTEXT_PSF29(fpuContext), 0, 0
  psq_st  fp30, OS_CONTEXT_PSF30(fpuContext), 0, 0
  psq_st  fp31, OS_CONTEXT_PSF31(fpuContext), 0, 0

_return:
    blr
  // clang-format on
}

asm void OSLoadFPUContext(register OSContext* fpuContext) {
  // clang-format off
  nofralloc
  addi    r4, fpuContext, 0
  b       __OSLoadFPUContext
  // clang-format on
}

asm void OSSaveFPUContext(register OSContext* fpuContext) {
  // clang-format off
  nofralloc
  addi    r5, fpuContext, 0
  b       __OSSaveFPUContext
  // clang-format on
}

asm void OSSetCurrentContext(register OSContext* context){
  // clang-format off
  nofralloc

  addis   r4, r0, OS_CACHED_REGION_PREFIX

  stw     context, 0x00D4(r4)

  clrlwi  r5, context, 2
  stw     r5, 0x00C0(r4)

  lwz     r5, 0x00D8(r4)
  cmpw    r5, context
  bne     _disableFPU

  lwz     r6, context->srr1
  ori     r6, r6, 0x2000
  stw     r6, context->srr1
  mfmsr   r6
  ori     r6, r6, 2
  mtmsr   r6
  blr

_disableFPU:
  lwz     r6, context->srr1
  rlwinm  r6, r6, 0, 19, 17
  stw     r6, context->srr1
  mfmsr   r6
  rlwinm  r6, r6, 0, 19, 17
  ori     r6, r6, 2
  mtmsr   r6
  isync
  blr
  // clang-format on
}

OSContext* OSGetCurrentContext(void) {
  return (OSContext*)__OSCurrentContext;
}

asm u32 OSSaveContext(register OSContext* context) {
  // clang-format off
  nofralloc
  stmw    r13, context->gpr[13]
  mfspr   r0, GQR1
  stw     r0, context->gqr[1]
  mfspr   r0, GQR2
  stw     r0, context->gqr[2]
  mfspr   r0, GQR3
  stw     r0, context->gqr[3]
  mfspr   r0, GQR4
  stw     r0, context->gqr[4]
  mfspr   r0, GQR5
  stw     r0, context->gqr[5]
  mfspr   r0, GQR6
  stw     r0, context->gqr[6]
  mfspr   r0, GQR7
  stw     r0, context->gqr[7]
  mfcr    r0
  stw     r0, context->cr
  mflr    r0
  stw     r0, context->lr
  stw     r0, context->srr0
  mfmsr   r0
  stw     r0, context->srr1
  mfctr   r0
  stw     r0, context->ctr
  mfxer   r0
  stw     r0, context->xer
  stw     r1, context->gpr[1]
  stw     r2, context->gpr[2]
  li      r0, 0x1
  stw     r0, context->gpr[3]
  li      r3, 0
  blr
  // clang-format on
}

extern void __RAS_OSDisableInterrupts_begin();
extern void __RAS_OSDisableInterrupts_end();

asm void OSLoadContext(register OSContext* context) {
  // clang-format off
  nofralloc

  lis      r4,__RAS_OSDisableInterrupts_begin@ha
  lwz      r6,context->srr0
  addi     r5,r4,__RAS_OSDisableInterrupts_begin@l
  cmplw    r6,r5
  blt      _notInRAS
  lis      r4,__RAS_OSDisableInterrupts_end@ha
  addi     r0,r4,__RAS_OSDisableInterrupts_end@l
  cmplw    r6,r0
  bgt      _notInRAS
  stw      r5,context->srr0

_notInRAS:

  lwz     r0, context->gpr[0]
  lwz     r1, context->gpr[1]
  lwz     r2, context->gpr[2]

  lhz     r4, context->state
  rlwinm. r5, r4, 0, 30, 30
  beq     notexc
  rlwinm  r4, r4, 0, 31, 29
  sth     r4, context->state
  lmw     r5, context->gpr[5]
  b       misc
notexc:
  lmw    r13, context->gpr[13]
misc:

  lwz     r4, context->gqr[1]
  mtspr   GQR1, r4
  lwz     r4, context->gqr[2]
  mtspr   GQR2, r4
  lwz     r4, context->gqr[3]
  mtspr   GQR3, r4
  lwz     r4, context->gqr[4]
  mtspr   GQR4, r4
  lwz     r4, context->gqr[5]
  mtspr   GQR5, r4
  lwz     r4, context->gqr[6]
  mtspr   GQR6, r4
  lwz     r4, context->gqr[7]
  mtspr   GQR7, r4

  lwz     r4, context->cr
  mtcr    r4
  lwz     r4, context->lr
  mtlr    r4
  lwz     r4, context->ctr
  mtctr   r4
  lwz     r4, context->xer
  mtxer   r4

  mfmsr   r4
  rlwinm  r4, r4, 0, 17, 15
  rlwinm  r4, r4, 0, 31, 29
  mtmsr   r4

  lwz     r4, context->srr0
  mtsrr0  r4
  lwz     r4, context->srr1
  mtsrr1  r4

  lwz     r4, context->gpr[4]
  lwz     r3, context->gpr[3]

  rfi
  // clang-format on
}

asm u32 OSGetStackPointer() {
  // clang-format off
  nofralloc 
  mr r3, r1 
  blr
  // clang-format on
}

asm u32 OSSwitchStack(register u32 newsp) {
  // clang-format off
  nofralloc
  mr  r5, r1
  mr  r1, newsp
  mr  r3, r5
  blr
  // clang-format on
}

asm int OSSwitchFiber(register u32 pc, register u32 newsp) {
  // clang-format off
  nofralloc
  mflr    r0
  mr      r5, r1
  stwu    r5, -8(newsp)
  mr      r1, newsp
  stw     r0, 4(r5)
  mtlr    pc
  blrl
  lwz     r5, 0(r1)
  lwz     r0, 4(r5)
  mtlr    r0
  mr      r1, r5
  blr
  // clang-format on
}

void OSClearContext(register OSContext* context) {
  context->mode = 0;
  context->state = 0;
  if (context == __OSFPUContext)
    __OSFPUContext = NULL;
}

asm void OSInitContext(register OSContext* context, register u32 pc, register u32 newsp) {
  // clang-format off
    nofralloc

    stw     pc,  OS_CONTEXT_SRR0(context)
    stw     newsp,  OS_CONTEXT_R1(context)
    li      r11, 0
    ori     r11, r11, 0x00008000 | 0x00000020 | 0x00000010 | 0x00000002 | 0x00001000
    stw     r11, OS_CONTEXT_SRR1(context)
    li      r0,  0x0
    stw     r0,  OS_CONTEXT_CR(context)
    stw     r0,  OS_CONTEXT_XER(context)


    stw     r2,  OS_CONTEXT_R2(context)
    stw     r13, OS_CONTEXT_R13(context)

    stw     r0,  OS_CONTEXT_R3(context)
    stw     r0,  OS_CONTEXT_R4(context)
    stw     r0,  OS_CONTEXT_R5(context)
    stw     r0,  OS_CONTEXT_R6(context)
    stw     r0,  OS_CONTEXT_R7(context)
    stw     r0,  OS_CONTEXT_R8(context)
    stw     r0,  OS_CONTEXT_R9(context)
    stw     r0,  OS_CONTEXT_R10(context)
    stw     r0,  OS_CONTEXT_R11(context)
    stw     r0,  OS_CONTEXT_R12(context)

    stw     r0,  OS_CONTEXT_R14(context)
    stw     r0,  OS_CONTEXT_R15(context)
    stw     r0,  OS_CONTEXT_R16(context)
    stw     r0,  OS_CONTEXT_R17(context)
    stw     r0,  OS_CONTEXT_R18(context)
    stw     r0,  OS_CONTEXT_R19(context)
    stw     r0,  OS_CONTEXT_R20(context)
    stw     r0,  OS_CONTEXT_R21(context)
    stw     r0,  OS_CONTEXT_R22(context)
    stw     r0,  OS_CONTEXT_R23(context)
    stw     r0,  OS_CONTEXT_R24(context)
    stw     r0,  OS_CONTEXT_R25(context)
    stw     r0,  OS_CONTEXT_R26(context)
    stw     r0,  OS_CONTEXT_R27(context)
    stw     r0,  OS_CONTEXT_R28(context)
    stw     r0,  OS_CONTEXT_R29(context)
    stw     r0,  OS_CONTEXT_R30(context)
    stw     r0,  OS_CONTEXT_R31(context)

    stw     r0,  OS_CONTEXT_GQR0(context)
    stw     r0,  OS_CONTEXT_GQR1(context)
    stw     r0,  OS_CONTEXT_GQR2(context)
    stw     r0,  OS_CONTEXT_GQR3(context)
    stw     r0,  OS_CONTEXT_GQR4(context)
    stw     r0,  OS_CONTEXT_GQR5(context)
    stw     r0,  OS_CONTEXT_GQR6(context)
    stw     r0,  OS_CONTEXT_GQR7(context)

    b       OSClearContext
  // clang-format on
}

void OSDumpContext(OSContext* context) {
  u32 i;
  u32* p;

  OSReport("------------------------- Context 0x%08x -------------------------\n", context);

  for (i = 0; i < 16; ++i) {
    OSReport("r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n", i, context->gpr[i],
             context->gpr[i], i + 16, context->gpr[i + 16], context->gpr[i + 16]);
  }

  OSReport("LR   = 0x%08x                   CR   = 0x%08x\n", context->lr, context->cr);
  OSReport("SRR0 = 0x%08x                   SRR1 = 0x%08x\n", context->srr0, context->srr1);

  OSReport("\nGQRs----------\n");
  for (i = 0; i < 4; ++i) {
    OSReport("gqr%d = 0x%08x \t gqr%d = 0x%08x\n", i, context->gqr[i], i + 4, context->gqr[i + 4]);
  }

  if (context->state & OS_CONTEXT_STATE_FPSAVED) {
    OSContext* currentContext;
    OSContext fpuContext;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    currentContext = OSGetCurrentContext();
    OSClearContext(&fpuContext);
    OSSetCurrentContext(&fpuContext);

    OSReport("\n\nFPRs----------\n");
    for (i = 0; i < 32; i += 2) {
      OSReport("fr%d \t= %d \t fr%d \t= %d\n", i, (u32)context->fpr[i], i + 1,
               (u32)context->fpr[i + 1]);
    }
    OSReport("\n\nPSFs----------\n");
    for (i = 0; i < 32; i += 2) {
      OSReport("ps%d \t= 0x%x \t ps%d \t= 0x%x\n", i, (u32)context->psf[i], i + 1,
               (u32)context->psf[i + 1]);
    }

    OSClearContext(&fpuContext);
    OSSetCurrentContext(currentContext);
    OSRestoreInterrupts(enabled);
  }

  OSReport("\nAddress:      Back Chain    LR Save\n");
  for (i = 0, p = (u32*)context->gpr[1]; p && (u32)p != 0xffffffff && i++ < 16; p = (u32*)*p) {
    OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
  }
}

static asm void OSSwitchFPUContext(register __OSException exception, register OSContext* context) {
  // clang-format off
  nofralloc
  mfmsr   r5
  ori     r5, r5, 0x2000
  mtmsr   r5
  isync
  lwz     r5, OS_CONTEXT_SRR1(context)
  ori     r5, r5, 0x2000
  mtsrr1  r5
  addis   r3, r0, OS_CACHED_REGION_PREFIX
  lwz     r5, 0x00D8(r3) 
  stw     context, 0x00D8(r3)
  cmpw    r5, r4
  beq     _restoreAndExit
  cmpwi   r5, 0x0
  beq     _loadNewFPUContext
  bl      __OSSaveFPUContext
_loadNewFPUContext:
  bl      __OSLoadFPUContext
_restoreAndExit:
  lwz     r3, OS_CONTEXT_CR(context)
  mtcr    r3
  lwz     r3, OS_CONTEXT_LR(context)
  mtlr    r3
  lwz     r3, OS_CONTEXT_SRR0(context)
  mtsrr0  r3
  lwz     r3, OS_CONTEXT_CTR(context)
  mtctr   r3
  lwz     r3, OS_CONTEXT_XER(context)
  mtxer   r3
  lhz     r3, context->state
  rlwinm  r3, r3, 0, 31, 29
  sth     r3, context->state
  lwz     r5, OS_CONTEXT_R5(context)
  lwz     r3, OS_CONTEXT_R3(context)
  lwz     r4, OS_CONTEXT_R4(context)
  rfi
  // clang-format on
}

extern void DBPrintf(char*, ...);

void __OSContextInit(void) {
  __OSSetExceptionHandler(__OS_EXCEPTION_FLOATING_POINT, OSSwitchFPUContext);
  __OSFPUContext = NULL;
  DBPrintf("FPU-unavailable handler installed\n");
}

asm void OSFillFPUContext(register OSContext * context) {
  // clang-format off
  nofralloc
  mfmsr   r5
  ori     r5, r5, 0x2000
  mtmsr   r5
  isync

  stfd    fp0,  context->fpr[0]
  stfd    fp1,  context->fpr[1]
  stfd    fp2,  context->fpr[2]
  stfd    fp3,  context->fpr[3]
  stfd    fp4,  context->fpr[4]
  stfd    fp5,  context->fpr[5]
  stfd    fp6,  context->fpr[6]
  stfd    fp7,  context->fpr[7]
  stfd    fp8,  context->fpr[8]
  stfd    fp9,  context->fpr[9]
  stfd    fp10, context->fpr[10]
  stfd    fp11, context->fpr[11]
  stfd    fp12, context->fpr[12]
  stfd    fp13, context->fpr[13]
  stfd    fp14, context->fpr[14]
  stfd    fp15, context->fpr[15]
  stfd    fp16, context->fpr[16]
  stfd    fp17, context->fpr[17]
  stfd    fp18, context->fpr[18]
  stfd    fp19, context->fpr[19]
  stfd    fp20, context->fpr[20]
  stfd    fp21, context->fpr[21]
  stfd    fp22, context->fpr[22]
  stfd    fp23, context->fpr[23]
  stfd    fp24, context->fpr[24]
  stfd    fp25, context->fpr[25]
  stfd    fp26, context->fpr[26]
  stfd    fp27, context->fpr[27]
  stfd    fp28, context->fpr[28]
  stfd    fp29, context->fpr[29]
  stfd    fp30, context->fpr[30]
  stfd    fp31, context->fpr[31]

  mffs    fp0
  stfd    fp0,  OS_CONTEXT_FPSCR(context)

  lfd     fp0,  context->fpr[0]

  mfspr   r5, HID2
  rlwinm. r5, r5, 3, 31, 31
  bc      12, 2, _return

  psq_st  fp0, OS_CONTEXT_PSF0(context), 0, 0
  psq_st  fp1, OS_CONTEXT_PSF1(context), 0, 0
  psq_st  fp2, OS_CONTEXT_PSF2(context), 0, 0
  psq_st  fp3, OS_CONTEXT_PSF3(context), 0, 0
  psq_st  fp4, OS_CONTEXT_PSF4(context), 0, 0
  psq_st  fp5, OS_CONTEXT_PSF5(context), 0, 0
  psq_st  fp6, OS_CONTEXT_PSF6(context), 0, 0
  psq_st  fp7, OS_CONTEXT_PSF7(context), 0, 0
  psq_st  fp8, OS_CONTEXT_PSF8(context), 0, 0
  psq_st  fp9, OS_CONTEXT_PSF9(context), 0, 0
  psq_st  fp10, OS_CONTEXT_PSF10(context), 0, 0
  psq_st  fp11, OS_CONTEXT_PSF11(context), 0, 0
  psq_st  fp12, OS_CONTEXT_PSF12(context), 0, 0
  psq_st  fp13, OS_CONTEXT_PSF13(context), 0, 0
  psq_st  fp14, OS_CONTEXT_PSF14(context), 0, 0
  psq_st  fp15, OS_CONTEXT_PSF15(context), 0, 0
  psq_st  fp16, OS_CONTEXT_PSF16(context), 0, 0
  psq_st  fp17, OS_CONTEXT_PSF17(context), 0, 0
  psq_st  fp18, OS_CONTEXT_PSF18(context), 0, 0
  psq_st  fp19, OS_CONTEXT_PSF19(context), 0, 0
  psq_st  fp20, OS_CONTEXT_PSF20(context), 0, 0
  psq_st  fp21, OS_CONTEXT_PSF21(context), 0, 0
  psq_st  fp22, OS_CONTEXT_PSF22(context), 0, 0
  psq_st  fp23, OS_CONTEXT_PSF23(context), 0, 0
  psq_st  fp24, OS_CONTEXT_PSF24(context), 0, 0
  psq_st  fp25, OS_CONTEXT_PSF25(context), 0, 0
  psq_st  fp26, OS_CONTEXT_PSF26(context), 0, 0
  psq_st  fp27, OS_CONTEXT_PSF27(context), 0, 0
  psq_st  fp28, OS_CONTEXT_PSF28(context), 0, 0
  psq_st  fp29, OS_CONTEXT_PSF29(context), 0, 0
  psq_st  fp30, OS_CONTEXT_PSF30(context), 0, 0
  psq_st  fp31, OS_CONTEXT_PSF31(context), 0, 0

_return:
    blr
  // clang-format on
}
