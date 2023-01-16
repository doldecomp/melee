#include <dolphin/base/PPCArch.h>
#include <dolphin/os/os.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSTime.h>
#include <stdio.h>

void OSReport(char* msg, ...)
{
    va_list args;

    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
}

void OSPanic(char* file, int line, char* msg, ...)
{
    va_list args;
    u32 i;
    u32* sp;

    OSDisableInterrupts();

    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);
    OSReport(" in \"%s\" on line %d.\n", file, line);

    // Print stack trace
    OSReport("\nAddress:      Back Chain    LR Save\n");
    i = 0;
    sp = (u32*) OSGetStackPointer();
    while (sp != NULL && (u32) sp != 0xFFFFFFFF && i++ < 16) {
        OSReport("0x%08x:   0x%08x    0x%08x\n", (u32) sp, sp[0], sp[1]);
        sp = (u32*) sp[0];
    }
    PPCHalt();
}

OSErrorHandler __OSErrorTable[16];

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler)
{
    OSErrorHandler prevHandler = __OSErrorTable[error];

    __OSErrorTable[error] = handler;
    return prevHandler;
}

#ifdef MUST_MATCH

/* static */ extern char* lbl_80401FF8;
/* static */ extern jtbl_t jtbl_804022D4;
/* static */ extern char* lbl_804D5C18;

static void lbl_803459C0(void);
static void lbl_803459D8(void);
static void lbl_80345A3C(void);
static void lbl_803459F0(void);
static void lbl_80345994(void);
static void lbl_803459AC(void);

#pragma push
asm void __OSUnhandledException(u8 error, OSContext* context, u32 dsisr,
                                u32 dar)
{ // clang-format off
    nofralloc
/* 80345870 00342450  7C 08 02 A6 */	mflr r0
/* 80345874 00342454  90 01 00 04 */	stw r0, 4(r1)
/* 80345878 00342458  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8034587C 0034245C  BF 21 00 1C */	stmw r25, 0x1c(r1)
/* 80345880 00342460  7C 9F 23 78 */	mr r31, r4
/* 80345884 00342464  3B 23 00 00 */	addi r25, r3, 0
/* 80345888 00342468  3B 45 00 00 */	addi r26, r5, 0
/* 8034588C 0034246C  3B 66 00 00 */	addi r27, r6, 0
/* 80345890 00342470  80 04 01 9C */	lwz r0, 0x19c(r4)
/* 80345894 00342474  3C 80 80 40 */	lis r4, lbl_80401FF8@ha
/* 80345898 00342478  3B A4 1F F8 */	addi r29, r4, lbl_80401FF8@l
/* 8034589C 0034247C  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 803458A0 00342480  40 82 00 18 */	bne lbl_803458B8
/* 803458A4 00342484  38 7D 00 5C */	addi r3, r29, 0x5c
/* 803458A8 00342488  4C C6 31 82 */	crclr 6
/* 803458AC 0034248C  57 24 06 3E */	clrlwi r4, r25, 0x18
/* 803458B0 00342490  4B FF FD F9 */	bl OSReport
/* 803458B4 00342494  48 00 00 7C */	b lbl_80345930
lbl_803458B8:
/* 803458B8 00342498  57 3E 06 3E */	clrlwi r30, r25, 0x18
/* 803458BC 0034249C  3C 60 80 4A */	lis r3, __OSErrorTable@ha
/* 803458C0 003424A0  57 24 15 BA */	rlwinm r4, r25, 2, 0x16, 0x1d
/* 803458C4 003424A4  38 03 7C 40 */	addi r0, r3, __OSErrorTable@l
/* 803458C8 003424A8  7F 80 22 14 */	add r28, r0, r4
/* 803458CC 003424AC  80 1C 00 00 */	lwz r0, 0(r28)
/* 803458D0 003424B0  28 00 00 00 */	cmplwi r0, 0
/* 803458D4 003424B4  41 82 00 38 */	beq lbl_8034590C
/* 803458D8 003424B8  48 00 54 71 */	bl OSDisableScheduler
/* 803458DC 003424BC  81 9C 00 00 */	lwz r12, 0(r28)
/* 803458E0 003424C0  38 7E 00 00 */	addi r3, r30, 0
/* 803458E4 003424C4  38 9F 00 00 */	addi r4, r31, 0
/* 803458E8 003424C8  4C C6 31 82 */	crclr 6
/* 803458EC 003424CC  7D 88 03 A6 */	mtlr r12
/* 803458F0 003424D0  38 BA 00 00 */	addi r5, r26, 0
/* 803458F4 003424D4  38 DB 00 00 */	addi r6, r27, 0
/* 803458F8 003424D8  4E 80 00 21 */	blrl
/* 803458FC 003424DC  48 00 54 8D */	bl OSEnableScheduler
/* 80345900 003424E0  48 00 59 2D */	bl __OSReschedule
/* 80345904 003424E4  7F E3 FB 78 */	mr r3, r31
/* 80345908 003424E8  4B FF F8 6D */	bl OSLoadContext
lbl_8034590C:
/* 8034590C 003424EC  57 20 06 3E */	clrlwi r0, r25, 0x18
/* 80345910 003424F0  28 00 00 08 */	cmplwi r0, 8
/* 80345914 003424F4  40 82 00 0C */	bne lbl_80345920
/* 80345918 003424F8  7F E3 FB 78 */	mr r3, r31
/* 8034591C 003424FC  4B FF F8 59 */	bl OSLoadContext
lbl_80345920:
/* 80345920 00342500  38 7D 00 7C */	addi r3, r29, 0x7c
/* 80345924 00342504  4C C6 31 82 */	crclr 6
/* 80345928 00342508  57 24 06 3E */	clrlwi r4, r25, 0x18
/* 8034592C 0034250C  4B FF FD 7D */	bl OSReport
lbl_80345930:
/* 80345930 00342510  38 6D A5 78 */	addi r3, r13, lbl_804D5C18
/* 80345934 00342514  4C C6 31 82 */	crclr 6
/* 80345938 00342518  4B FF FD 71 */	bl OSReport
/* 8034593C 0034251C  7F E3 FB 78 */	mr r3, r31
/* 80345940 00342520  4B FF F9 F5 */	bl OSDumpContext
/* 80345944 00342524  38 9A 00 00 */	addi r4, r26, 0
/* 80345948 00342528  4C C6 31 82 */	crclr 6
/* 8034594C 0034252C  38 BB 00 00 */	addi r5, r27, 0
/* 80345950 00342530  38 7D 00 94 */	addi r3, r29, 0x94
/* 80345954 00342534  4B FF FD 55 */	bl OSReport
/* 80345958 00342538  48 00 6A 99 */	bl OSGetTime
/* 8034595C 0034253C  38 A3 00 00 */	addi r5, r3, 0
/* 80345960 00342540  4C C6 31 82 */	crclr 6
/* 80345964 00342544  38 C4 00 00 */	addi r6, r4, 0
/* 80345968 00342548  38 7D 00 C8 */	addi r3, r29, 0xc8
/* 8034596C 0034254C  4B FF FD 3D */	bl OSReport
/* 80345970 00342550  57 20 06 3E */	clrlwi r0, r25, 0x18
/* 80345974 00342554  28 00 00 0F */	cmplwi r0, 0xf
/* 80345978 00342558  41 81 00 C4 */	bgt lbl_80345A3C
/* 8034597C 0034255C  3C 60 80 40 */	lis r3, jtbl_804022D4@ha
/* 80345980 00342560  38 63 22 D4 */	addi r3, r3, jtbl_804022D4@l
/* 80345984 00342564  54 00 10 3A */	slwi r0, r0, 2
/* 80345988 00342568  7C 03 00 2E */	lwzx r0, r3, r0
/* 8034598C 0034256C  7C 09 03 A6 */	mtctr r0
/* 80345990 00342570  4E 80 04 20 */	bctr
entry lbl_80345994
lbl_80345994:
/* 80345994 00342574  80 9F 01 98 */	lwz r4, 0x198(r31)
/* 80345998 00342578  38 BB 00 00 */	addi r5, r27, 0
/* 8034599C 0034257C  38 7D 00 D8 */	addi r3, r29, 0xd8
/* 803459A0 00342580  4C C6 31 82 */	crclr 6
/* 803459A4 00342584  4B FF FD 05 */	bl OSReport
/* 803459A8 00342588  48 00 00 94 */	b lbl_80345A3C
entry lbl_803459AC
lbl_803459AC:
/* 803459AC 0034258C  80 9F 01 98 */	lwz r4, 0x198(r31)
/* 803459B0 00342590  38 7D 01 38 */	addi r3, r29, 0x138
/* 803459B4 00342594  4C C6 31 82 */	crclr 6
/* 803459B8 00342598  4B FF FC F1 */	bl OSReport
/* 803459BC 0034259C  48 00 00 80 */	b lbl_80345A3C
entry lbl_803459C0
lbl_803459C0:
/* 803459C0 003425A0  80 9F 01 98 */	lwz r4, 0x198(r31)
/* 803459C4 003425A4  38 BB 00 00 */	addi r5, r27, 0
/* 803459C8 003425A8  38 7D 01 84 */	addi r3, r29, 0x184
/* 803459CC 003425AC  4C C6 31 82 */	crclr 6
/* 803459D0 003425B0  4B FF FC D9 */	bl OSReport
/* 803459D4 003425B4  48 00 00 68 */	b lbl_80345A3C
entry lbl_803459D8
lbl_803459D8:
/* 803459D8 003425B8  80 9F 01 98 */	lwz r4, 0x198(r31)
/* 803459DC 003425BC  38 BB 00 00 */	addi r5, r27, 0
/* 803459E0 003425C0  38 7D 01 E8 */	addi r3, r29, 0x1e8
/* 803459E4 003425C4  4C C6 31 82 */	crclr 6
/* 803459E8 003425C8  4B FF FC C1 */	bl OSReport
/* 803459EC 003425CC  48 00 00 50 */	b lbl_80345A3C
entry lbl_803459F0
lbl_803459F0:
/* 803459F0 003425D0  38 6D A5 78 */	addi r3, r13, lbl_804D5C18
/* 803459F4 003425D4  4C C6 31 82 */	crclr 6
/* 803459F8 003425D8  4B FF FC B1 */	bl OSReport
/* 803459FC 003425DC  3F C0 CC 00 */	lis r30, 0xCC005000@ha
/* 80345A00 003425E0  4C C6 31 82 */	crclr 6
/* 80345A04 003425E4  3B FE 50 00 */	addi r31, r30, 0xCC005000@l
/* 80345A08 003425E8  A0 9E 50 30 */	lhz r4, 0x5030(r30)
/* 80345A0C 003425EC  38 7D 02 48 */	addi r3, r29, 0x248
/* 80345A10 003425F0  A0 BE 50 32 */	lhz r5, 0x5032(r30)
/* 80345A14 003425F4  4B FF FC 95 */	bl OSReport
/* 80345A18 003425F8  A0 9F 00 20 */	lhz r4, 0x20(r31)
/* 80345A1C 003425FC  38 7D 02 68 */	addi r3, r29, 0x268
/* 80345A20 00342600  A0 BF 00 22 */	lhz r5, 0x22(r31)
/* 80345A24 00342604  4C C6 31 82 */	crclr 6
/* 80345A28 00342608  4B FF FC 81 */	bl OSReport
/* 80345A2C 0034260C  80 9E 60 14 */	lwz r4, 0x6014(r30)
/* 80345A30 00342610  4C C6 31 82 */	crclr 6
/* 80345A34 00342614  38 7D 02 88 */	addi r3, r29, 0x288
/* 80345A38 00342618  4B FF FC 71 */	bl OSReport
entry lbl_80345A3C
lbl_80345A3C:
/* 80345A3C 0034261C  A8 8D BC E0 */	lha r4, __OSLastInterrupt(r13)
/* 80345A40 00342620  38 7D 02 A4 */	addi r3, r29, 0x2a4
/* 80345A44 00342624  4C C6 31 82 */	crclr 6
/* 80345A48 00342628  80 AD BC DC */	lwz r5, __OSLastInterruptSrr0(r13)
/* 80345A4C 0034262C  80 ED BC E8 */	lwz r7, __OSLastInterruptTime(r13)
/* 80345A50 00342630  81 0D BC EC */	lwz r8, __OSLastInterruptTime+4(r13)
/* 80345A54 00342634  4B FF FC 55 */	bl OSReport
/* 80345A58 00342638  4B FF 04 3D */	bl PPCHalt
/* 80345A5C 0034263C  BB 21 00 1C */	lmw r25, 0x1c(r1)
/* 80345A60 00342640  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80345A64 00342644  38 21 00 38 */	addi r1, r1, 0x38
/* 80345A68 00342648  7C 08 03 A6 */	mtlr r0
/* 80345A6C 0034264C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void __OSUnhandledException(u8 error, OSContext* context, u32 dsisr, u32 dar)
{
    if (!(context->srr1 & (1 << 1)))
        OSReport("Non-recoverable Exception %d", error);
    else {
        if (__OSErrorTable[error] != NULL) {
            OSDisableScheduler();
            __OSErrorTable[error](error, context, dsisr, dar);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
        if (error == OS_ERROR_DECREMENTER)
            OSLoadContext(context);
        OSReport("Unhandled Exception %d", error);
    }

    OSReport("\n");
    OSDumpContext(context);
    OSReport("\nDSISR= 0x%08x                   DAR  = 0x%08x\n", dsisr, dar);
    {
        u64 time = OSGetTime();
        OSReport("", time, (u32) time);
    }
    switch (error) {
    case OS_ERROR_DSI:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                 "invalid address 0x%x (read from DAR)\n",
                 context->srr0, dar);
        break;
    case OS_ERROR_ISI:
        OSReport("\nAttempted to fetch instruction from invalid address 0x%x "
                 "(read from SRR0)\n",
                 context->srr0);
        break;
    case OS_ERROR_ALIGNMENT:
        OSReport("\nInstruction at 0x%x (read from SRR0) attempted to access "
                 "unaligned address 0x%x (read from DAR)\n",
                 context->srr0, dar);
        break;
    case OS_ERROR_PROGRAM:
        OSReport("\nProgram exception : Possible illegal instruction/operation "
                 "at or around 0x%x (read from SRR0)\n",
                 context->srr0, dar);
        break;
    case 15:
        OSReport("\n");
        OSReport("AI DMA Address =   0x%04x%04x\n", *(u16*) 0xCC005030,
                 *(u16*) 0xCC005032);
        OSReport("ARAM DMA Address = 0x%04x%04x\n",
                 (*(u16*) ((s8*) ((void*) 0xCC005000) + (0x20))),
                 (*(u16*) ((s8*) ((void*) 0xCC005000) + (0x22))));
        OSReport("DI DMA Address =   0x%08x\n", *(u16*) 0xCC006014);
        break;
    }
    OSReport("\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n",
             __OSLastInterrupt, __OSLastInterruptSrr0);
    PPCHalt();
}
#endif
