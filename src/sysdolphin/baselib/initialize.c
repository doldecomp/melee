#include "sysdolphin/baselib/initialize.h"

#include "sysdolphin/baselib/leak.h"
#include "sysdolphin/baselib/video.h"

extern void* FrameBuffer[HSD_VI_XFB_MAX]; //FrameBuffer

extern HSD_MemReport memReport; //memReport

extern GXRenderModeObj* rmode; //rmode

extern u32 iparam_fifo_size; //iparam_fifo_size

extern GXFifoObj* DefaultFifoObj; //DefaultFifoObj

extern s32 init_done; //init_done

// Matching but won't actually match until FrameBuffer is declared in the file
#ifdef NON_MATCHING
void HSD_InitComponent(void) {
    HSD_OSInit();
    {
        HSD_VIStatus vi_status;
        GXColor black = { 0, 0, 0, 0 };

        vi_status.rmode = *rmode;
        vi_status.black = GX_TRUE;
        vi_status.vf = GX_TRUE;
        vi_status.gamma = GX_GM_1_0;
        vi_status.clear_clr = black;
        vi_status.clear_z = GX_MAX_Z24;
        vi_status.update_clr = GX_ENABLE;
        vi_status.update_alpha = GX_ENABLE;
        vi_status.update_z = GX_ENABLE;

        HSD_VIInit(&vi_status, FrameBuffer[0], FrameBuffer[1], FrameBuffer[2]);
    }

    HSD_GXInit();
    HSD_DVDInit();
    HSD_IDSetup();
    VIWaitForRetrace();
    HSD_ObjInit();
    func_803881E4();
    init_done = TRUE;
}
#else
static const GXColor black = {0, 0, 0, 0}; //black

asm void HSD_InitComponent(void)
{
    nofralloc
/* 80374E48 00371A28  7C 08 02 A6 */	mflr r0
/* 80374E4C 00371A2C  3C 60 80 4C */	lis r3, FrameBuffer@ha
/* 80374E50 00371A30  90 01 00 04 */	stw r0, 4(r1)
/* 80374E54 00371A34  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 80374E58 00371A38  93 E1 00 64 */	stw r31, 0x64(r1)
/* 80374E5C 00371A3C  3B E3 09 48 */	addi r31, r3, FrameBuffer@l
/* 80374E60 00371A40  93 C1 00 60 */	stw r30, 0x60(r1)
/* 80374E64 00371A44  48 00 04 A1 */	bl HSD_OSInit
/* 80374E68 00371A48  81 0D A7 64 */	lwz r8, rmode(r13)
/* 80374E6C 00371A4C  3C 60 01 00 */	lis r3, 0x00FFFFFF@ha
/* 80374E70 00371A50  3B C0 00 01 */	li r30, 1
/* 80374E74 00371A54  80 82 EB B0 */	lwz r4, black(r2)
/* 80374E78 00371A58  80 E8 00 00 */	lwz r7, 0(r8)
/* 80374E7C 00371A5C  80 C8 00 04 */	lwz r6, 4(r8)
/* 80374E80 00371A60  38 A0 00 00 */	li r5, 0
/* 80374E84 00371A64  38 03 FF FF */	addi r0, r3, 0x00FFFFFF@l
/* 80374E88 00371A68  90 E1 00 0C */	stw r7, 0xc(r1)
/* 80374E8C 00371A6C  38 61 00 0C */	addi r3, r1, 0xc
/* 80374E90 00371A70  90 C1 00 10 */	stw r6, 0x10(r1)
/* 80374E94 00371A74  80 E8 00 08 */	lwz r7, 8(r8)
/* 80374E98 00371A78  80 C8 00 0C */	lwz r6, 0xc(r8)
/* 80374E9C 00371A7C  90 E1 00 14 */	stw r7, 0x14(r1)
/* 80374EA0 00371A80  90 C1 00 18 */	stw r6, 0x18(r1)
/* 80374EA4 00371A84  80 E8 00 10 */	lwz r7, 0x10(r8)
/* 80374EA8 00371A88  80 C8 00 14 */	lwz r6, 0x14(r8)
/* 80374EAC 00371A8C  90 E1 00 1C */	stw r7, 0x1c(r1)
/* 80374EB0 00371A90  90 C1 00 20 */	stw r6, 0x20(r1)
/* 80374EB4 00371A94  80 E8 00 18 */	lwz r7, 0x18(r8)
/* 80374EB8 00371A98  80 C8 00 1C */	lwz r6, 0x1c(r8)
/* 80374EBC 00371A9C  90 E1 00 24 */	stw r7, 0x24(r1)
/* 80374EC0 00371AA0  90 C1 00 28 */	stw r6, 0x28(r1)
/* 80374EC4 00371AA4  80 E8 00 20 */	lwz r7, 0x20(r8)
/* 80374EC8 00371AA8  80 C8 00 24 */	lwz r6, 0x24(r8)
/* 80374ECC 00371AAC  90 E1 00 2C */	stw r7, 0x2c(r1)
/* 80374ED0 00371AB0  90 C1 00 30 */	stw r6, 0x30(r1)
/* 80374ED4 00371AB4  80 E8 00 28 */	lwz r7, 0x28(r8)
/* 80374ED8 00371AB8  80 C8 00 2C */	lwz r6, 0x2c(r8)
/* 80374EDC 00371ABC  90 E1 00 34 */	stw r7, 0x34(r1)
/* 80374EE0 00371AC0  90 C1 00 38 */	stw r6, 0x38(r1)
/* 80374EE4 00371AC4  80 E8 00 30 */	lwz r7, 0x30(r8)
/* 80374EE8 00371AC8  80 C8 00 34 */	lwz r6, 0x34(r8)
/* 80374EEC 00371ACC  90 E1 00 3C */	stw r7, 0x3c(r1)
/* 80374EF0 00371AD0  90 C1 00 40 */	stw r6, 0x40(r1)
/* 80374EF4 00371AD4  80 C8 00 38 */	lwz r6, 0x38(r8)
/* 80374EF8 00371AD8  90 C1 00 44 */	stw r6, 0x44(r1)
/* 80374EFC 00371ADC  93 C1 00 48 */	stw r30, 0x48(r1)
/* 80374F00 00371AE0  9B C1 00 4C */	stb r30, 0x4c(r1)
/* 80374F04 00371AE4  90 A1 00 50 */	stw r5, 0x50(r1)
/* 80374F08 00371AE8  90 81 00 54 */	stw r4, 0x54(r1)
/* 80374F0C 00371AEC  90 01 00 58 */	stw r0, 0x58(r1)
/* 80374F10 00371AF0  9B C1 00 5C */	stb r30, 0x5c(r1)
/* 80374F14 00371AF4  9B C1 00 5D */	stb r30, 0x5d(r1)
/* 80374F18 00371AF8  9B C1 00 5E */	stb r30, 0x5e(r1)
/* 80374F1C 00371AFC  80 9F 00 00 */	lwz r4, 0(r31)
/* 80374F20 00371B00  80 BF 00 04 */	lwz r5, 4(r31)
/* 80374F24 00371B04  80 DF 00 08 */	lwz r6, 8(r31)
/* 80374F28 00371B08  48 00 18 91 */	bl HSD_VIInit
/* 80374F2C 00371B0C  48 00 03 2D */	bl HSD_GXInit
/* 80374F30 00371B10  48 00 00 49 */	bl HSD_DVDInit
/* 80374F34 00371B14  48 00 7E 89 */	bl HSD_IDSetup
/* 80374F38 00371B18  4B FD A3 DD */	bl VIWaitForRetrace
/* 80374F3C 00371B1C  48 00 06 79 */	bl HSD_ObjInit
/* 80374F40 00371B20  48 01 32 A5 */	bl func_803881E4
/* 80374F44 00371B24  93 CD C0 2C */	stw r30, init_done(r13)
/* 80374F48 00371B28  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 80374F4C 00371B2C  83 E1 00 64 */	lwz r31, 0x64(r1)
/* 80374F50 00371B30  83 C1 00 60 */	lwz r30, 0x60(r1)
/* 80374F54 00371B34  38 21 00 68 */	addi r1, r1, 0x68
/* 80374F58 00371B38  7C 08 03 A6 */	mtlr r0
/* 80374F5C 00371B3C  4E 80 00 20 */	blr 
}
#endif

void HSD_GXSetFifoObj(GXFifoObj* fifo) 
{
    memReport.gxfifo = iparam_fifo_size;
    DefaultFifoObj = fifo;
}

void HSD_DVDInit(void)
{
    return;
}
