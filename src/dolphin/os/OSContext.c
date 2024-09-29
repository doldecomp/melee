#include <placeholder.h>

#include <dolphin/db/db.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSException.h>
#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSInterrupt.h>

#ifdef MWERKS_GEKKO
asm void __OSLoadFPUContext(u32 _, register OSContext* fpuctx)
{ // clang-format off
    nofralloc
    lhz r5, fpuctx->state
    clrlwi. r5, r5, 31
    beq done

    lfd f0, fpuctx->fpscr
    mtfsf 0xff, f0
    mfspr r5, 0x398
    rlwinm. r5, r5, 3, 31, 31
    beq regular_fprs
    psq_l f0, 456(r4), 0, qr0
    psq_l f1, 464(r4), 0, qr0
    psq_l f2, 472(r4), 0, qr0
    psq_l f3, 480(r4), 0, qr0
    psq_l f4, 488(r4), 0, qr0
    psq_l f5, 496(r4), 0, qr0
    psq_l f6, 504(r4), 0, qr0
    psq_l f7, 512(r4), 0, qr0
    psq_l f8, 520(r4), 0, qr0
    psq_l f9, 528(r4), 0, qr0
    psq_l f10, 536(r4), 0, qr0
    psq_l f11, 544(r4), 0, qr0
    psq_l f12, 552(r4), 0, qr0
    psq_l f13, 560(r4), 0, qr0
    psq_l f14, 568(r4), 0, qr0
    psq_l f15, 576(r4), 0, qr0
    psq_l f16, 584(r4), 0, qr0
    psq_l f17, 592(r4), 0, qr0
    psq_l f18, 600(r4), 0, qr0
    psq_l f19, 608(r4), 0, qr0
    psq_l f20, 616(r4), 0, qr0
    psq_l f21, 624(r4), 0, qr0
    psq_l f22, 632(r4), 0, qr0
    psq_l f23, 640(r4), 0, qr0
    psq_l f24, 648(r4), 0, qr0
    psq_l f25, 656(r4), 0, qr0
    psq_l f26, 664(r4), 0, qr0
    psq_l f27, 672(r4), 0, qr0
    psq_l f28, 680(r4), 0, qr0
    psq_l f29, 688(r4), 0, qr0
    psq_l f30, 696(r4), 0, qr0
    psq_l f31, 704(r4), 0, qr0

regular_fprs:
    lfd f0,  fpuctx->fprs[0]
    lfd f1,  fpuctx->fprs[1]
    lfd f2,  fpuctx->fprs[2]
    lfd f3,  fpuctx->fprs[3]
    lfd f4,  fpuctx->fprs[4]
    lfd f5,  fpuctx->fprs[5]
    lfd f6,  fpuctx->fprs[6]
    lfd f7,  fpuctx->fprs[7]
    lfd f8,  fpuctx->fprs[8]
    lfd f9,  fpuctx->fprs[9]
    lfd f10, fpuctx->fprs[10]
    lfd f11, fpuctx->fprs[11]
    lfd f12, fpuctx->fprs[12]
    lfd f13, fpuctx->fprs[13]
    lfd f14, fpuctx->fprs[14]
    lfd f15, fpuctx->fprs[15]
    lfd f16, fpuctx->fprs[16]
    lfd f17, fpuctx->fprs[17]
    lfd f18, fpuctx->fprs[18]
    lfd f19, fpuctx->fprs[19]
    lfd f20, fpuctx->fprs[20]
    lfd f21, fpuctx->fprs[21]
    lfd f22, fpuctx->fprs[22]
    lfd f23, fpuctx->fprs[23]
    lfd f24, fpuctx->fprs[24]
    lfd f25, fpuctx->fprs[25]
    lfd f26, fpuctx->fprs[26]
    lfd f27, fpuctx->fprs[27]
    lfd f28, fpuctx->fprs[28]
    lfd f29, fpuctx->fprs[29]
    lfd f30, fpuctx->fprs[30]
    lfd f31, fpuctx->fprs[31]
done:
    blr
} // clang-format on
#else
void __OSLoadFPUContext(u32 _, OSContext* fpuctx)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void __OSSaveFPUContext(u32 unused1, u32 unused2,
                            register OSContext* fpuctx)
{ // clang-format off
    nofralloc

    lhz r3, 0x1a2(fpuctx)
    ori r3, r3, 1
    sth r3, 0x1a2(fpuctx)

    stfd f0,  fpuctx->fprs[0]
    stfd f1,  fpuctx->fprs[1]
    stfd f2,  fpuctx->fprs[2]
    stfd f3,  fpuctx->fprs[3]
    stfd f4,  fpuctx->fprs[4]
    stfd f5,  fpuctx->fprs[5]
    stfd f6,  fpuctx->fprs[6]
    stfd f7,  fpuctx->fprs[7]
    stfd f8,  fpuctx->fprs[8]
    stfd f9,  fpuctx->fprs[9]
    stfd f10, fpuctx->fprs[10]
    stfd f11, fpuctx->fprs[11]
    stfd f12, fpuctx->fprs[12]
    stfd f13, fpuctx->fprs[13]
    stfd f14, fpuctx->fprs[14]
    stfd f15, fpuctx->fprs[15]
    stfd f16, fpuctx->fprs[16]
    stfd f17, fpuctx->fprs[17]
    stfd f18, fpuctx->fprs[18]
    stfd f19, fpuctx->fprs[19]
    stfd f20, fpuctx->fprs[20]
    stfd f21, fpuctx->fprs[21]
    stfd f22, fpuctx->fprs[22]
    stfd f23, fpuctx->fprs[23]
    stfd f24, fpuctx->fprs[24]
    stfd f25, fpuctx->fprs[25]
    stfd f26, fpuctx->fprs[26]
    stfd f27, fpuctx->fprs[27]
    stfd f28, fpuctx->fprs[28]
    stfd f29, fpuctx->fprs[29]
    stfd f30, fpuctx->fprs[30]
    stfd f31, fpuctx->fprs[31]

    mffs f0
    stfd f0, fpuctx->fpscr

    lfd f0, fpuctx->fprs[0]

    mfspr r3, 0x398
    rlwinm. r3, r3, 3, 31, 31
    beq done

    psq_st f0, 456(fpuctx), 0, qr0
    psq_st f1, 464(fpuctx), 0, qr0
    psq_st f2, 472(fpuctx), 0, qr0
    psq_st f3, 480(fpuctx), 0, qr0
    psq_st f4, 488(fpuctx), 0, qr0
    psq_st f5, 496(fpuctx), 0, qr0
    psq_st f6, 504(fpuctx), 0, qr0
    psq_st f7, 512(fpuctx), 0, qr0
    psq_st f8, 520(fpuctx), 0, qr0
    psq_st f9, 528(fpuctx), 0, qr0
    psq_st f10, 536(fpuctx), 0, qr0
    psq_st f11, 544(fpuctx), 0, qr0
    psq_st f12, 552(fpuctx), 0, qr0
    psq_st f13, 560(fpuctx), 0, qr0
    psq_st f14, 568(fpuctx), 0, qr0
    psq_st f15, 576(fpuctx), 0, qr0
    psq_st f16, 584(fpuctx), 0, qr0
    psq_st f17, 592(fpuctx), 0, qr0
    psq_st f18, 600(fpuctx), 0, qr0
    psq_st f19, 608(fpuctx), 0, qr0
    psq_st f20, 616(fpuctx), 0, qr0
    psq_st f21, 624(fpuctx), 0, qr0
    psq_st f22, 632(fpuctx), 0, qr0
    psq_st f23, 640(fpuctx), 0, qr0
    psq_st f24, 648(fpuctx), 0, qr0
    psq_st f25, 656(fpuctx), 0, qr0
    psq_st f26, 664(fpuctx), 0, qr0
    psq_st f27, 672(fpuctx), 0, qr0
    psq_st f28, 680(fpuctx), 0, qr0
    psq_st f29, 688(fpuctx), 0, qr0
    psq_st f30, 696(fpuctx), 0, qr0
    psq_st f31, 704(fpuctx), 0, qr0
done:
    blr
} // clang-format on
#else
void __OSSaveFPUContext(u32 unused1, u32 unused2, OSContext* fpuctx)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void OSLoadFPUContext(register OSContext* fpuctx)
{ // clang-format off
    nofralloc
    addi r4, fpuctx, 0
    b __OSLoadFPUContext
} // clang-format on
#else
void OSLoadFPUContext(OSContext* fpuctx)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void OSSaveFPUContext(register OSContext* fpuctx)
{ // clang-format off
    nofralloc
    addi r5, fpuctx, 0
    b __OSSaveFPUContext
} // clang-format on
#else
void OSSaveFPUContext(OSContext* fpuctx)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void OSSetCurrentContext(register OSContext* ctx)
{ // clang-format off
    nofralloc

    lis r4, 0x800000D4@ha
    stw r3, 0x800000D4@l(r4)
    clrlwi r5, ctx, 2
    stw r5, 0xC0(r4)
    lwz r5, 0xD8(r4)
    cmpw r5, ctx
    bne disable_fpu

    lwz r6, ctx->srr1
    ori r6, r6, 0x2000
    stw r6, ctx->srr1
    mfmsr r6
    ori r6, r6, 2
    mtmsr r6
    blr

disable_fpu:
    lwz r6, ctx->srr1
    rlwinm r6, r6, 0, 19, 17
    stw r6, ctx->srr1
    mfmsr r6
    rlwinm r6, r6, 0, 19, 17
    ori r6, r6, 2
    mtmsr r6
    isync
    blr
} // clang-format on
#else
void OSSetCurrentContext(OSContext* ctx)
{
    NOT_IMPLEMENTED;
}
#endif

OSContext* OSGetCurrentContext(void)
{
    return OS_CURRENT_CONTEXT;
}

#ifdef MWERKS_GEKKO
asm bool OSSaveContext(register OSContext* ctx)
{ // clang-format off
    nofralloc
    stmw r13, ctx->gprs[13]
    mfspr r0, GQR1
    stw r0, ctx->gqrs[1]
    mfspr r0, GQR2
    stw r0, ctx->gqrs[2]
    mfspr r0, GQR3
    stw r0, ctx->gqrs[3]
    mfspr r0, GQR4
    stw r0, ctx->gqrs[4]
    mfspr r0, GQR5
    stw r0, ctx->gqrs[5]
    mfspr r0, GQR6
    stw r0, ctx->gqrs[6]
    mfspr r0, GQR7
    stw r0, ctx->gqrs[7]
    mfcr r0
    stw r0, ctx->cr
    mflr r0
    stw r0, ctx->lr
    stw r0, ctx->srr0
    mfmsr r0
    stw r0, ctx->srr1
    mfctr r0
    stw r0, ctx->ctr
    mfxer r0
    stw r0, ctx->xer;
    stw r1, ctx->gprs[1]
    stw r2, ctx->gprs[2]
    li r0, 1
    stw r0, ctx->gprs[3]
    li r3, 0
    blr
} // clang-format on
#else
bool OSSaveContext(OSContext* ctx)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void OSLoadContext(register OSContext* ctx)
{ // clang-format off
    nofralloc
    lis r4, __RAS_OSDisableInterrupts_begin@ha
    lwz r6, ctx->srr0
    addi r5, r4, __RAS_OSDisableInterrupts_begin@l
    cmplw r6, r5
    blt not_in_ras
    lis r4, __RAS_OSDisableInterrupts_end@ha
    addi r0, r4, __RAS_OSDisableInterrupts_end@l
    cmplw r6, r0
    bgt not_in_ras
    stw r5, ctx->srr0

not_in_ras:

    lwz r0, ctx->gprs[0]
    lwz r1, ctx->gprs[1]
    lwz r2, ctx->gprs[2]
    lhz r4, ctx->state
    rlwinm. r5, r4, 0, 30, 30
    beq not_exc
    rlwinm r4, r4, 0, 31, 29
    sth r4, ctx->state
    lmw r5, ctx->gprs[5]
    b misc
not_exc:
    lmw r13, 0x34(ctx)
misc:

    lwz r4, ctx->gqrs[1]
    mtspr GQR1, r4
    lwz r4, ctx->gqrs[2]
    mtspr GQR2, r4
    lwz r4, ctx->gqrs[3]
    mtspr GQR3, r4
    lwz r4, ctx->gqrs[4]
    mtspr GQR4, r4
    lwz r4, ctx->gqrs[5]
    mtspr GQR5, r4
    lwz r4, ctx->gqrs[6]
    mtspr GQR6, r4
    lwz r4, ctx->gqrs[7]
    mtspr GQR7, r4

    lwz r4, ctx->cr
    mtcr r4
    lwz r4, ctx->lr
    mtlr r4
    lwz r4, ctx->ctr
    mtctr r4
    lwz r4, ctx->xer
    mtxer r4

    mfmsr r4
    rlwinm r4, r4, 0, 17, 15
    rlwinm r4, r4, 0, 31, 29
    mtmsr r4

    lwz r4, ctx->srr0
    mtsrr0 r4
    lwz r4, ctx->srr1
    mtsrr1 r4

    lwz r4, ctx->gprs[4]
    lwz r3, ctx->gprs[3]
    rfi
} // clang-format on
#else
void OSLoadContext(OSContext* ctx)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
void* OSGetStackPointer(void)
{
    register void* result;
    asm { mr result, r1 }
    return result;
}
#else
void* OSGetStackPointer(void)
{
    NOT_IMPLEMENTED;
}
#endif

extern volatile OSContext* __OSFPUContext AT_ADDRESS(OS_BASE_CACHED | 0xD8);

void OSClearContext(register OSContext* context)
{
    context->mode = 0;
    context->state = 0;
    if (context == __OSFPUContext) {
        __OSFPUContext = NULL;
    }
}

#ifdef MWERKS_GEKKO
asm void OSInitContext(register OSContext* ctx, register u32 pc,
                       register u32 newsp)
{ // clang-format off
    nofralloc
    stw pc, ctx->srr0
    stw newsp, ctx->gprs[1]
    li r11, 0
    ori r11, r11, 0x9032
    stw r11, ctx->srr1
    li r0, 0
    stw r0, ctx->cr
    stw r0, ctx->xer

    stw r2, ctx->gprs[2]
    stw r13, ctx->gprs[13]

    stw r0, ctx->gprs[3]
    stw r0, ctx->gprs[4]
    stw r0, ctx->gprs[5]
    stw r0, ctx->gprs[6]
    stw r0, ctx->gprs[7]
    stw r0, ctx->gprs[8]
    stw r0, ctx->gprs[9]
    stw r0, ctx->gprs[10]
    stw r0, ctx->gprs[11]
    stw r0, ctx->gprs[12]

    stw r0, ctx->gprs[14]
    stw r0, ctx->gprs[15]
    stw r0, ctx->gprs[16]
    stw r0, ctx->gprs[17]
    stw r0, ctx->gprs[18]
    stw r0, ctx->gprs[19]
    stw r0, ctx->gprs[20]
    stw r0, ctx->gprs[21]
    stw r0, ctx->gprs[22]
    stw r0, ctx->gprs[23]
    stw r0, ctx->gprs[24]
    stw r0, ctx->gprs[25]
    stw r0, ctx->gprs[26]
    stw r0, ctx->gprs[27]
    stw r0, ctx->gprs[28]
    stw r0, ctx->gprs[29]
    stw r0, ctx->gprs[30]
    stw r0, ctx->gprs[31]
    stw r0, ctx->gqrs[0]
    stw r0, ctx->gqrs[1]
    stw r0, ctx->gqrs[2]
    stw r0, ctx->gqrs[3]
    stw r0, ctx->gqrs[4]
    stw r0, ctx->gqrs[5]
    stw r0, ctx->gqrs[6]
    stw r0, ctx->gqrs[7]
    b OSClearContext
} // clang-format on
#else
void OSInitContext(OSContext* ctx, u32 pc, u32 newsp)
{
    NOT_IMPLEMENTED;
}
#endif

void OSDumpContext(const OSContext* context)
{
    u32 i;
    u32* p;

    OSReport(
        "------------------------- Context 0x%08x -------------------------\n",
        context);

    for (i = 0; i < 16; ++i) {
        OSReport("r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n", i,
                 context->gprs[i], context->gprs[i], i + 16,
                 context->gprs[i + 16], context->gprs[i + 16]);
    }

    OSReport("LR   = 0x%08x                   CR   = 0x%08x\n", context->lr,
             context->cr);
    OSReport("SRR0 = 0x%08x                   SRR1 = 0x%08x\n", context->srr0,
             context->srr1);

    OSReport("\nGQRs----------\n");
    for (i = 0; i < 4; ++i) {
        OSReport("gqr%d = 0x%08x \t gqr%d = 0x%08x\n", i, context->gqrs[i],
                 i + 4, context->gqrs[i + 4]);
    }

    if (context->state & OS_CONTEXT_STATE_FPSAVED) {
        OSContext* currentContext;
        OSContext fpuContext;
        bool enabled;

        enabled = OSDisableInterrupts();
        currentContext = OSGetCurrentContext();
        OSClearContext(&fpuContext);
        OSSetCurrentContext(&fpuContext);

        OSReport("\n\nFPRs----------\n");
        for (i = 0; i < 32; i += 2) {
            OSReport("fr%d \t= %d \t fr%d \t= %d\n", i, (u32) context->fprs[i],
                     i + 1, (u32) context->fprs[i + 1]);
        }
        OSReport("\n\nPSFs----------\n");
        for (i = 0; i < 32; i += 2) {
            OSReport("ps%d \t= 0x%x \t ps%d \t= 0x%x\n", i,
                     (u32) context->psfs[i], i + 1,
                     (u32) context->psfs[i + 1]);
        }

        OSClearContext(&fpuContext);
        OSSetCurrentContext(currentContext);
        OSRestoreInterrupts(enabled);
    }

    OSReport("\nAddress:      Back Chain    LR Save\n");
    for (i = 0, p = (u32*) context->gprs[1];
         p && (u32) p != 0xffffffff && i++ < 16; p = (u32*) *p)
    {
        OSReport("0x%08x:   0x%08x    0x%08x\n", p, p[0], p[1]);
    }
}

#ifdef MWERKS_GEKKO
static asm void OSSwitchFPUContext(register __OSException exception,
                                   register OSContext* context)
{
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
#else
static void OSSwitchFPUContext(register __OSException exception,
                               register OSContext* context)
{
    NOT_IMPLEMENTED;
}
#endif

void __OSContextInit(void)
{
    __OSSetExceptionHandler(OS_EXCEPTION_FLOATING_POINT, OSSwitchFPUContext);
    __OSFPUContext = NULL;
    DBPrintf("FPU-unavailable handler installed\n");
}
