#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSMemory.h>

extern volatile u32 Mem_Size : 0x80000028;
extern volatile u32 Simulated_Mem : 0x800000F0;

u32 OSGetPhysicalMemSize(void)
{
    return Mem_Size;
}

u32 OSGetConsoleSimulatedMemSize(void)
{
    return Simulated_Mem;
}

extern volatile u16 hwRegs[] : 0xCC004000;

int OSOnReset(int p1)
{
    if (p1 != 0) {
        hwRegs[8] = 0xFF;
        __OSMaskInterrupts(0xF0000000);
    }
    return 1;
}

extern OSErrorHandler __OSErrorTable[];
extern unk_t __OSUnhandledException();

#pragma push
asm void MEMIntrruptHandler(u8, OSContext*)
{ // clang-format off
    nofralloc
/* 80347C38 00344818  7C 08 02 A6 */	mflr r0
/* 80347C3C 0034481C  3C 60 CC 00 */	lis r3, 0xCC004000@ha
/* 80347C40 00344820  90 01 00 04 */	stw r0, 4(r1)
/* 80347C44 00344824  39 03 40 00 */	addi r8, r3, 0xCC004000@l
/* 80347C48 00344828  38 00 00 00 */	li r0, 0
/* 80347C4C 0034482C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80347C50 00344830  A0 E3 40 24 */	lhz r7, 0x4024(r3)
/* 80347C54 00344834  3C 60 80 4A */	lis r3, __OSErrorTable@ha
/* 80347C58 00344838  A0 C8 00 22 */	lhz r6, 0x22(r8)
/* 80347C5C 0034483C  38 63 7C 40 */	addi r3, r3, __OSErrorTable@l
/* 80347C60 00344840  A0 A8 00 1E */	lhz r5, 0x1e(r8)
/* 80347C64 00344844  50 E6 81 9E */	rlwimi r6, r7, 0x10, 6, 0xf
/* 80347C68 00344848  B0 08 00 20 */	sth r0, 0x20(r8)
/* 80347C6C 0034484C  81 83 00 3C */	lwz r12, 0x3c(r3)
/* 80347C70 00344850  28 0C 00 00 */	cmplwi r12, 0
/* 80347C74 00344854  41 82 00 18 */	beq lbl_80347C8C
/* 80347C78 00344858  7D 88 03 A6 */	mtlr r12
/* 80347C7C 0034485C  38 60 00 0F */	li r3, 0xf
/* 80347C80 00344860  4C C6 31 82 */	crclr 6
/* 80347C84 00344864  4E 80 00 21 */	blrl 
/* 80347C88 00344868  48 00 00 0C */	b lbl_80347C94
lbl_80347C8C:
/* 80347C8C 0034486C  38 60 00 0F */	li r3, 0xf
/* 80347C90 00344870  4B FF DB E1 */	bl __OSUnhandledException
lbl_80347C94:
/* 80347C94 00344874  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80347C98 00344878  38 21 00 08 */	addi r1, r1, 8
/* 80347C9C 0034487C  7C 08 03 A6 */	mtlr r0
/* 80347CA0 00344880  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void Config24MB(void)
{ // clang-format off
    nofralloc
/* 80347CA4 00344884  38 E0 00 00 */	li r7, 0
/* 80347CA8 00344888  3C 80 00 00 */	lis r4, 0x00000002@ha
/* 80347CAC 0034488C  38 84 00 02 */	addi r4, r4, 0x00000002@l
/* 80347CB0 00344890  3C 60 80 00 */	lis r3, 0x800001FF@ha
/* 80347CB4 00344894  38 63 01 FF */	addi r3, r3, 0x800001FF@l
/* 80347CB8 00344898  3C C0 01 00 */	lis r6, 0x01000002@ha
/* 80347CBC 0034489C  38 C6 00 02 */	addi r6, r6, 0x01000002@l
/* 80347CC0 003448A0  3C A0 81 00 */	lis r5, 0x810000FF@ha
/* 80347CC4 003448A4  38 A5 00 FF */	addi r5, r5, 0x810000FF@l
/* 80347CC8 003448A8  4C 00 01 2C */	isync 
/* 80347CCC 003448AC  7C F8 83 A6 */	mtdbatu 0, r7
/* 80347CD0 003448B0  7C 99 83 A6 */	mtdbatl 0, r4
/* 80347CD4 003448B4  7C 78 83 A6 */	mtdbatu 0, r3
/* 80347CD8 003448B8  4C 00 01 2C */	isync 
/* 80347CDC 003448BC  7C F0 83 A6 */	mtibatu 0, r7
/* 80347CE0 003448C0  7C 91 83 A6 */	mtibatl 0, r4
/* 80347CE4 003448C4  7C 70 83 A6 */	mtibatu 0, r3
/* 80347CE8 003448C8  4C 00 01 2C */	isync 
/* 80347CEC 003448CC  7C FC 83 A6 */	mtdbatu 2, r7
/* 80347CF0 003448D0  7C DD 83 A6 */	mtdbatl 2, r6
/* 80347CF4 003448D4  7C BC 83 A6 */	mtdbatu 2, r5
/* 80347CF8 003448D8  4C 00 01 2C */	isync 
/* 80347CFC 003448DC  7C F4 83 A6 */	mtibatu 2, r7
/* 80347D00 003448E0  7C D5 83 A6 */	mtibatl 2, r6
/* 80347D04 003448E4  7C B4 83 A6 */	mtibatu 2, r5
/* 80347D08 003448E8  4C 00 01 2C */	isync 
/* 80347D0C 003448EC  7C 60 00 A6 */	mfmsr r3
/* 80347D10 003448F0  60 63 00 30 */	ori r3, r3, 0x30
/* 80347D14 003448F4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80347D18 003448F8  7C 68 02 A6 */	mflr r3
/* 80347D1C 003448FC  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80347D20 00344900  4C 00 00 64 */	rfi 
} // clang-format on
#pragma pop

#pragma push
asm void Config48MB(void)
{ // clang-format off
    nofralloc
/* 80347D24 00344904  38 E0 00 00 */	li r7, 0
/* 80347D28 00344908  3C 80 00 00 */	lis r4, 0x00000002@ha
/* 80347D2C 0034490C  38 84 00 02 */	addi r4, r4, 0x00000002@l
/* 80347D30 00344910  3C 60 80 00 */	lis r3, 0x800003FF@ha
/* 80347D34 00344914  38 63 03 FF */	addi r3, r3, 0x800003FF@l
/* 80347D38 00344918  3C C0 02 00 */	lis r6, 0x02000002@ha
/* 80347D3C 0034491C  38 C6 00 02 */	addi r6, r6, 0x02000002@l
/* 80347D40 00344920  3C A0 82 00 */	lis r5, 0x820001FF@ha
/* 80347D44 00344924  38 A5 01 FF */	addi r5, r5, 0x820001FF@l
/* 80347D48 00344928  4C 00 01 2C */	isync 
/* 80347D4C 0034492C  7C F8 83 A6 */	mtdbatu 0, r7
/* 80347D50 00344930  7C 99 83 A6 */	mtdbatl 0, r4
/* 80347D54 00344934  7C 78 83 A6 */	mtdbatu 0, r3
/* 80347D58 00344938  4C 00 01 2C */	isync 
/* 80347D5C 0034493C  7C F0 83 A6 */	mtibatu 0, r7
/* 80347D60 00344940  7C 91 83 A6 */	mtibatl 0, r4
/* 80347D64 00344944  7C 70 83 A6 */	mtibatu 0, r3
/* 80347D68 00344948  4C 00 01 2C */	isync 
/* 80347D6C 0034494C  7C FC 83 A6 */	mtdbatu 2, r7
/* 80347D70 00344950  7C DD 83 A6 */	mtdbatl 2, r6
/* 80347D74 00344954  7C BC 83 A6 */	mtdbatu 2, r5
/* 80347D78 00344958  4C 00 01 2C */	isync 
/* 80347D7C 0034495C  7C F4 83 A6 */	mtibatu 2, r7
/* 80347D80 00344960  7C D5 83 A6 */	mtibatl 2, r6
/* 80347D84 00344964  7C B4 83 A6 */	mtibatu 2, r5
/* 80347D88 00344968  4C 00 01 2C */	isync 
/* 80347D8C 0034496C  7C 60 00 A6 */	mfmsr r3
/* 80347D90 00344970  60 63 00 30 */	ori r3, r3, 0x30
/* 80347D94 00344974  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80347D98 00344978  7C 68 02 A6 */	mflr r3
/* 80347D9C 0034497C  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80347DA0 00344980  4C 00 00 64 */	rfi 
} // clang-format on
#pragma pop

asm void RealMode(register void (*)(void))
{
    nofralloc
    clrlwi r3, r3, 2
    mtspr 0x1a, r3
    mfmsr r3
    rlwinm r3, r3, 0, 0x1c, 0x19
    mtspr 0x1b, r3
    rfi
}

extern unk_t lbl_80402348[];
extern unk_t OSRegisterResetFunction();

void __OSInitMemoryProtection(void)
{
    u32 unused[10];
    size_t simulated_mem = OSGetConsoleSimulatedMemSize();
    BOOL intr = OSDisableInterrupts();
    if (simulated_mem <= 24 * 1024 * 1024) {
        RealMode(Config24MB);
    } else if (simulated_mem <= 48 * 1024 * 1024) {
        RealMode(Config48MB);
    }
    hwRegs[16] = 0;
    hwRegs[8] = 0xFF;
    __OSMaskInterrupts(0xF0000000);
    __OSSetInterruptHandler(0, MEMIntrruptHandler);
    __OSSetInterruptHandler(1, MEMIntrruptHandler);
    __OSSetInterruptHandler(2, MEMIntrruptHandler);
    __OSSetInterruptHandler(3, MEMIntrruptHandler);
    __OSSetInterruptHandler(4, MEMIntrruptHandler);
    OSRegisterResetFunction(lbl_80402348);
    simulated_mem = OSGetConsoleSimulatedMemSize();
    if (simulated_mem < Mem_Size && simulated_mem == 24 * 1024 * 1024) {
        hwRegs[20] = 2;
    }
    __OSUnmaskInterrupts(0x08000000);
    OSRestoreInterrupts(intr);
}
