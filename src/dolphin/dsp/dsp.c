#include <dolphin/dsp/dsp.h>

extern BOOL __DSP_init_flag;

extern void* __DSP_curr_task;
extern void* __DSP_first_task;
extern void* __DSP_last_task;
extern void* __DSP_tmp_task;

void __DSPHandler();

extern char lbl_80400C08[]; //"DSPInit(): Build Date: %s %s\n"

u32 DSPCheckMailToDSP(void)
{
	return (HW_REG(0xCC005000, u16) >> 15) & 1;
}

u32 DSPCheckMailFromDSP(void)
{
	return (HW_REG(0xCC005004, u16) >> 15) & 1;;
}

u32 DSPReadMailFromDSP(void)
{
	return (__DSPRegs[2] << 16) | __DSPRegs[3];
}

void DSPSendMailToDSP(u32 mail)
{
	__DSPRegs[0] = (u16)((mail >> 16) & 0xffff);
	__DSPRegs[1] = (u16)(mail & 0xffff);
}

// Non-matching due to externs
// https://decomp.me/scratch/zzu2Y
#ifdef NON_MATCHING
void DSPInit(void)
{
    BOOL intr;
    u16 tmp;

    __DSP_debug_printf(lbl_80400C08, __DATE__, __TIME__);

    if (TRUE == __DSP_init_flag) {
        return;
    }

    intr = OSDisableInterrupts();

    __OSSetInterruptHandler(7, __DSPHandler);
    __OSUnmaskInterrupts(0x80000000u>>7);

    tmp = __DSPRegs[5];
    tmp = (u16)((tmp & ~(0xA8)) | 0x0800);
    __DSPRegs[5] = tmp;

    tmp = __DSPRegs[5];
    tmp = (u16)(tmp & ~(0xAC));
    __DSPRegs[5] = tmp;

    __DSP_first_task = __DSP_last_task = __DSP_curr_task = __DSP_tmp_task = NULL;

    __DSP_init_flag = TRUE;

    OSRestoreInterrupts(intr);
}
#else
asm void DSPInit(void)
{
    nofralloc
/* 80336014 00332BF4  7C 08 02 A6 */	mflr r0
/* 80336018 00332BF8  3C 60 80 40 */	lis r3, lbl_80400C08@ha
/* 8033601C 00332BFC  90 01 00 04 */	stw r0, 4(r1)
/* 80336020 00332C00  38 63 0C 08 */	addi r3, r3, lbl_80400C08@l
/* 80336024 00332C04  4C C6 31 82 */	crclr 6
/* 80336028 00332C08  38 83 00 20 */	addi r4, r3, 0x20
/* 8033602C 00332C0C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80336030 00332C10  38 A3 00 2C */	addi r5, r3, 0x2c
/* 80336034 00332C14  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80336038 00332C18  48 00 01 D5 */	bl __DSP_debug_printf
/* 8033603C 00332C1C  80 0D BB 70 */	lwz r0, __DSP_init_flag(r13)
/* 80336040 00332C20  2C 00 00 01 */	cmpwi r0, 1
/* 80336044 00332C24  41 82 00 74 */	beq lbl_803360B8
/* 80336048 00332C28  48 01 13 1D */	bl OSDisableInterrupts
/* 8033604C 00332C2C  3C 80 80 33 */	lis r4, __DSPHandler@ha
/* 80336050 00332C30  3B E3 00 00 */	addi r31, r3, 0
/* 80336054 00332C34  38 84 62 5C */	addi r4, r4, __DSPHandler@l
/* 80336058 00332C38  38 60 00 07 */	li r3, 7
/* 8033605C 00332C3C  48 01 13 55 */	bl __OSSetInterruptHandler
/* 80336060 00332C40  3C 60 01 00 */	lis r3, 0x100
/* 80336064 00332C44  48 01 17 51 */	bl __OSUnmaskInterrupts
/* 80336068 00332C48  3C 60 CC 00 */	lis r3, 0xCC005000@ha
/* 8033606C 00332C4C  38 C3 50 00 */	addi r6, r3, 0xCC005000@l
/* 80336070 00332C50  A0 63 50 0A */	lhz r3, 0x500a(r3)
/* 80336074 00332C54  38 00 FF 57 */	li r0, -169
/* 80336078 00332C58  7C 60 00 38 */	and r0, r3, r0
/* 8033607C 00332C5C  60 00 08 00 */	ori r0, r0, 0x800
/* 80336080 00332C60  B0 06 00 0A */	sth r0, 0xa(r6)
/* 80336084 00332C64  38 A0 FF 53 */	li r5, -173
/* 80336088 00332C68  38 80 00 00 */	li r4, 0
/* 8033608C 00332C6C  A0 E6 00 0A */	lhz r7, 0xa(r6)
/* 80336090 00332C70  38 00 00 01 */	li r0, 1
/* 80336094 00332C74  38 7F 00 00 */	addi r3, r31, 0
/* 80336098 00332C78  7C E5 28 38 */	and r5, r7, r5
/* 8033609C 00332C7C  B0 A6 00 0A */	sth r5, 0xa(r6)
/* 803360A0 00332C80  90 8D BB 80 */	stw r4, __DSP_tmp_task(r13)
/* 803360A4 00332C84  90 8D BB 8C */	stw r4, __DSP_curr_task(r13)
/* 803360A8 00332C88  90 8D BB 84 */	stw r4, __DSP_last_task(r13)
/* 803360AC 00332C8C  90 8D BB 88 */	stw r4, __DSP_first_task(r13)
/* 803360B0 00332C90  90 0D BB 70 */	stw r0, __DSP_init_flag(r13)
/* 803360B4 00332C94  48 01 12 D9 */	bl OSRestoreInterrupts
lbl_803360B8:
/* 803360B8 00332C98  80 01 00 14 */	lwz r0, 0x14(r1)
/* 803360BC 00332C9C  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 803360C0 00332CA0  38 21 00 10 */	addi r1, r1, 0x10
/* 803360C4 00332CA4  7C 08 03 A6 */	mtlr r0
/* 803360C8 00332CA8  4E 80 00 20 */	blr 
}
#endif

BOOL DSPCheckInit(void)
{
    return(__DSP_init_flag);
}
