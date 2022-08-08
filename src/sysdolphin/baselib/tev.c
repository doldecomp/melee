#include <dolphin/gx/GXLight.h>
#include "sysdolphin/baselib/tev.h"

extern void* lbl_80405B98;

HSD_ObjAllocData render_alloc_data;
HSD_ObjAllocData tevreg_alloc_data;
HSD_ObjAllocData chan_alloc_data;

extern s32 lbl_804D7600; // state_num_chans
extern void* lbl_804D7604; // chan_chan
extern void* lbl_804D760C;


void HSD_RenderInitAllocData(void)
{
    HSD_ObjAllocInit(&render_alloc_data, 0x1C, 4);
    HSD_ObjAllocInit(&tevreg_alloc_data, 0x14, 4);
    HSD_ObjAllocInit(&chan_alloc_data, 0x30, 4);
}

HSD_ObjAllocData* HSD_RenderGetAllocData(void)
{
    return &render_alloc_data;
}

HSD_ObjAllocData* HSD_TevRegGetAllocData(void)
{
    return &tevreg_alloc_data;
}

HSD_ObjAllocData* HSD_ChanGetAllocData(void)
{
    return &chan_alloc_data;
}

asm void HSD_SetupChannel(void* ch)
{
    nofralloc
/* 803620A4 0035EC84  7C 08 02 A6 */	mflr r0
/* 803620A8 0035EC88  90 01 00 04 */	stw r0, 4(r1)
/* 803620AC 0035EC8C  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 803620B0 0035EC90  BF 61 00 4C */	stmw r27, 0x4c(r1)
/* 803620B4 0035EC94  7C 7B 1B 79 */	or. r27, r3, r3
/* 803620B8 0035EC98  3C 60 80 40 */	lis r3, lbl_80405B98@ha
/* 803620BC 0035EC9C  3B E3 5B 98 */	addi r31, r3, lbl_80405B98@l
/* 803620C0 0035ECA0  41 82 02 FC */	beq lbl_803623BC
/* 803620C4 0035ECA4  80 7B 00 04 */	lwz r3, 4(r27)
/* 803620C8 0035ECA8  2C 03 00 FF */	cmpwi r3, 0xff
/* 803620CC 0035ECAC  40 82 00 08 */	bne lbl_803620D4
/* 803620D0 0035ECB0  48 00 02 EC */	b lbl_803623BC
lbl_803620D4:
/* 803620D4 0035ECB4  88 1B 00 14 */	lbz r0, 0x14(r27)
/* 803620D8 0035ECB8  3B 83 00 00 */	addi r28, r3, 0
/* 803620DC 0035ECBC  54 7D 07 BE */	clrlwi r29, r3, 0x1e
/* 803620E0 0035ECC0  28 00 00 00 */	cmplwi r0, 0
/* 803620E4 0035ECC4  54 7E 07 FE */	clrlwi r30, r3, 0x1f
/* 803620E8 0035ECC8  41 82 00 F0 */	beq lbl_803621D8
/* 803620EC 0035ECCC  80 1B 00 18 */	lwz r0, 0x18(r27)
/* 803620F0 0035ECD0  2C 00 00 00 */	cmpwi r0, 0
/* 803620F4 0035ECD4  40 82 00 E4 */	bne lbl_803621D8
/* 803620F8 0035ECD8  57 C0 10 3A */	slwi r0, r30, 2
/* 803620FC 0035ECDC  38 6D BF 64 */	addi r3, r13, lbl_804D7604
/* 80362100 0035ECE0  7C 63 02 14 */	add r3, r3, r0
/* 80362104 0035ECE4  80 03 00 00 */	lwz r0, 0(r3)
/* 80362108 0035ECE8  2C 00 00 00 */	cmpwi r0, 0
/* 8036210C 0035ECEC  41 82 00 34 */	beq lbl_80362140
/* 80362110 0035ECF0  38 00 00 00 */	li r0, 0
/* 80362114 0035ECF4  90 03 00 00 */	stw r0, 0(r3)
/* 80362118 0035ECF8  38 81 00 40 */	addi r4, r1, 0x40
/* 8036211C 0035ECFC  38 7E 00 04 */	addi r3, r30, 4
/* 80362120 0035ED00  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 80362124 0035ED04  90 01 00 40 */	stw r0, 0x40(r1)
/* 80362128 0035ED08  4B FD C1 65 */	bl GXSetChanAmbColor
/* 8036212C 0035ED0C  1C 7E 00 30 */	mulli r3, r30, 0x30
/* 80362130 0035ED10  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 80362134 0035ED14  7C 7F 1A 14 */	add r3, r31, r3
/* 80362138 0035ED18  90 03 00 3C */	stw r0, 0x3c(r3)
/* 8036213C 0035ED1C  48 00 00 9C */	b lbl_803621D8
lbl_80362140:
/* 80362140 0035ED20  38 1C FF FC */	addi r0, r28, -4
/* 80362144 0035ED24  28 00 00 01 */	cmplwi r0, 1
/* 80362148 0035ED28  41 81 00 24 */	bgt lbl_8036216C
/* 8036214C 0035ED2C  1C 1E 00 30 */	mulli r0, r30, 0x30
/* 80362150 0035ED30  80 9B 00 0C */	lwz r4, 0xc(r27)
/* 80362154 0035ED34  7C 7F 02 14 */	add r3, r31, r0
/* 80362158 0035ED38  80 03 00 3C */	lwz r0, 0x3c(r3)
/* 8036215C 0035ED3C  7C 04 00 40 */	cmplw r4, r0
/* 80362160 0035ED40  41 82 00 78 */	beq lbl_803621D8
/* 80362164 0035ED44  90 83 00 3C */	stw r4, 0x3c(r3)
/* 80362168 0035ED48  48 00 00 5C */	b lbl_803621C4
lbl_8036216C:
/* 8036216C 0035ED4C  28 1C 00 01 */	cmplwi r28, 1
/* 80362170 0035ED50  41 81 00 34 */	bgt lbl_803621A4
/* 80362174 0035ED54  1C 1E 00 30 */	mulli r0, r30, 0x30
/* 80362178 0035ED58  80 BB 00 0C */	lwz r5, 0xc(r27)
/* 8036217C 0035ED5C  7C 7F 02 14 */	add r3, r31, r0
/* 80362180 0035ED60  38 83 00 3C */	addi r4, r3, 0x3c
/* 80362184 0035ED64  80 63 00 3C */	lwz r3, 0x3c(r3)
/* 80362188 0035ED68  7C A0 1A 78 */	xor r0, r5, r3
/* 8036218C 0035ED6C  54 00 00 2F */	rlwinm. r0, r0, 0, 0, 0x17
/* 80362190 0035ED70  41 82 00 48 */	beq lbl_803621D8
/* 80362194 0035ED74  54 A0 00 2E */	rlwinm r0, r5, 0, 0, 0x17
/* 80362198 0035ED78  50 60 06 3E */	rlwimi r0, r3, 0, 0x18, 0x1f
/* 8036219C 0035ED7C  90 04 00 00 */	stw r0, 0(r4)
/* 803621A0 0035ED80  48 00 00 24 */	b lbl_803621C4
lbl_803621A4:
/* 803621A4 0035ED84  1C 1E 00 30 */	mulli r0, r30, 0x30
/* 803621A8 0035ED88  88 7B 00 0F */	lbz r3, 0xf(r27)
/* 803621AC 0035ED8C  7C 9F 02 14 */	add r4, r31, r0
/* 803621B0 0035ED90  88 04 00 3F */	lbz r0, 0x3f(r4)
/* 803621B4 0035ED94  38 84 00 3F */	addi r4, r4, 0x3f
/* 803621B8 0035ED98  7C 03 00 40 */	cmplw r3, r0
/* 803621BC 0035ED9C  41 82 00 1C */	beq lbl_803621D8
/* 803621C0 0035EDA0  98 64 00 00 */	stb r3, 0(r4)
lbl_803621C4:
/* 803621C4 0035EDA4  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 803621C8 0035EDA8  38 81 00 3C */	addi r4, r1, 0x3c
/* 803621CC 0035EDAC  38 7C 00 00 */	addi r3, r28, 0
/* 803621D0 0035EDB0  90 01 00 3C */	stw r0, 0x3c(r1)
/* 803621D4 0035EDB4  4B FD C0 B9 */	bl GXSetChanAmbColor
lbl_803621D8:
/* 803621D8 0035EDB8  80 1B 00 1C */	lwz r0, 0x1c(r27)
/* 803621DC 0035EDBC  2C 00 00 00 */	cmpwi r0, 0
/* 803621E0 0035EDC0  40 82 00 E4 */	bne lbl_803622C4
/* 803621E4 0035EDC4  57 C0 10 3A */	slwi r0, r30, 2
/* 803621E8 0035EDC8  38 6D BF 6C */	addi r3, r13, lbl_804D760C
/* 803621EC 0035EDCC  7C 63 02 14 */	add r3, r3, r0
/* 803621F0 0035EDD0  80 03 00 00 */	lwz r0, 0(r3)
/* 803621F4 0035EDD4  2C 00 00 00 */	cmpwi r0, 0
/* 803621F8 0035EDD8  41 82 00 34 */	beq lbl_8036222C
/* 803621FC 0035EDDC  38 00 00 00 */	li r0, 0
/* 80362200 0035EDE0  90 03 00 00 */	stw r0, 0(r3)
/* 80362204 0035EDE4  38 81 00 38 */	addi r4, r1, 0x38
/* 80362208 0035EDE8  38 7E 00 04 */	addi r3, r30, 4
/* 8036220C 0035EDEC  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 80362210 0035EDF0  90 01 00 38 */	stw r0, 0x38(r1)
/* 80362214 0035EDF4  4B FD C1 E1 */	bl GXSetChanMatColor
/* 80362218 0035EDF8  1C 7E 00 30 */	mulli r3, r30, 0x30
/* 8036221C 0035EDFC  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 80362220 0035EE00  7C 7F 1A 14 */	add r3, r31, r3
/* 80362224 0035EE04  90 03 00 40 */	stw r0, 0x40(r3)
/* 80362228 0035EE08  48 00 00 9C */	b lbl_803622C4
lbl_8036222C:
/* 8036222C 0035EE0C  38 1C FF FC */	addi r0, r28, -4
/* 80362230 0035EE10  28 00 00 01 */	cmplwi r0, 1
/* 80362234 0035EE14  41 81 00 24 */	bgt lbl_80362258
/* 80362238 0035EE18  1C 1E 00 30 */	mulli r0, r30, 0x30
/* 8036223C 0035EE1C  80 9B 00 10 */	lwz r4, 0x10(r27)
/* 80362240 0035EE20  7C 7F 02 14 */	add r3, r31, r0
/* 80362244 0035EE24  80 03 00 40 */	lwz r0, 0x40(r3)
/* 80362248 0035EE28  7C 04 00 40 */	cmplw r4, r0
/* 8036224C 0035EE2C  41 82 00 78 */	beq lbl_803622C4
/* 80362250 0035EE30  90 83 00 40 */	stw r4, 0x40(r3)
/* 80362254 0035EE34  48 00 00 5C */	b lbl_803622B0
lbl_80362258:
/* 80362258 0035EE38  28 1C 00 01 */	cmplwi r28, 1
/* 8036225C 0035EE3C  41 81 00 34 */	bgt lbl_80362290
/* 80362260 0035EE40  1C 1E 00 30 */	mulli r0, r30, 0x30
/* 80362264 0035EE44  80 BB 00 10 */	lwz r5, 0x10(r27)
/* 80362268 0035EE48  7C 7F 02 14 */	add r3, r31, r0
/* 8036226C 0035EE4C  38 83 00 40 */	addi r4, r3, 0x40
/* 80362270 0035EE50  80 63 00 40 */	lwz r3, 0x40(r3)
/* 80362274 0035EE54  7C A0 1A 78 */	xor r0, r5, r3
/* 80362278 0035EE58  54 00 00 2F */	rlwinm. r0, r0, 0, 0, 0x17
/* 8036227C 0035EE5C  41 82 00 48 */	beq lbl_803622C4
/* 80362280 0035EE60  54 A0 00 2E */	rlwinm r0, r5, 0, 0, 0x17
/* 80362284 0035EE64  50 60 06 3E */	rlwimi r0, r3, 0, 0x18, 0x1f
/* 80362288 0035EE68  90 04 00 00 */	stw r0, 0(r4)
/* 8036228C 0035EE6C  48 00 00 24 */	b lbl_803622B0
lbl_80362290:
/* 80362290 0035EE70  1C 1E 00 30 */	mulli r0, r30, 0x30
/* 80362294 0035EE74  88 7B 00 13 */	lbz r3, 0x13(r27)
/* 80362298 0035EE78  7C 9F 02 14 */	add r4, r31, r0
/* 8036229C 0035EE7C  88 04 00 43 */	lbz r0, 0x43(r4)
/* 803622A0 0035EE80  38 84 00 43 */	addi r4, r4, 0x43
/* 803622A4 0035EE84  7C 03 00 40 */	cmplw r3, r0
/* 803622A8 0035EE88  41 82 00 1C */	beq lbl_803622C4
/* 803622AC 0035EE8C  98 64 00 00 */	stb r3, 0(r4)
lbl_803622B0:
/* 803622B0 0035EE90  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 803622B4 0035EE94  38 81 00 34 */	addi r4, r1, 0x34
/* 803622B8 0035EE98  38 7C 00 00 */	addi r3, r28, 0
/* 803622BC 0035EE9C  90 01 00 34 */	stw r0, 0x34(r1)
/* 803622C0 0035EEA0  4B FD C1 35 */	bl GXSetChanMatColor
lbl_803622C4:
/* 803622C4 0035EEA4  1F DD 00 30 */	mulli r30, r29, 0x30
/* 803622C8 0035EEA8  88 9B 00 14 */	lbz r4, 0x14(r27)
/* 803622CC 0035EEAC  7F BF F2 14 */	add r29, r31, r30
/* 803622D0 0035EEB0  8C 1D 00 44 */	lbzu r0, 0x44(r29)
/* 803622D4 0035EEB4  7C 04 00 40 */	cmplw r4, r0
/* 803622D8 0035EEB8  40 82 00 58 */	bne lbl_80362330
/* 803622DC 0035EEBC  7C BF F2 14 */	add r5, r31, r30
/* 803622E0 0035EEC0  80 7B 00 18 */	lwz r3, 0x18(r27)
/* 803622E4 0035EEC4  80 05 00 48 */	lwz r0, 0x48(r5)
/* 803622E8 0035EEC8  7C 03 00 00 */	cmpw r3, r0
/* 803622EC 0035EECC  40 82 00 44 */	bne lbl_80362330
/* 803622F0 0035EED0  80 7B 00 1C */	lwz r3, 0x1c(r27)
/* 803622F4 0035EED4  80 05 00 4C */	lwz r0, 0x4c(r5)
/* 803622F8 0035EED8  7C 03 00 00 */	cmpw r3, r0
/* 803622FC 0035EEDC  40 82 00 34 */	bne lbl_80362330
/* 80362300 0035EEE0  80 7B 00 20 */	lwz r3, 0x20(r27)
/* 80362304 0035EEE4  80 05 00 50 */	lwz r0, 0x50(r5)
/* 80362308 0035EEE8  7C 03 00 00 */	cmpw r3, r0
/* 8036230C 0035EEEC  40 82 00 24 */	bne lbl_80362330
/* 80362310 0035EEF0  80 7B 00 24 */	lwz r3, 0x24(r27)
/* 80362314 0035EEF4  80 05 00 54 */	lwz r0, 0x54(r5)
/* 80362318 0035EEF8  7C 03 00 00 */	cmpw r3, r0
/* 8036231C 0035EEFC  40 82 00 14 */	bne lbl_80362330
/* 80362320 0035EF00  80 7B 00 28 */	lwz r3, 0x28(r27)
/* 80362324 0035EF04  80 05 00 58 */	lwz r0, 0x58(r5)
/* 80362328 0035EF08  7C 03 00 00 */	cmpw r3, r0
/* 8036232C 0035EF0C  41 82 00 90 */	beq lbl_803623BC
lbl_80362330:
/* 80362330 0035EF10  80 BB 00 18 */	lwz r5, 0x18(r27)
/* 80362334 0035EF14  7F 83 E3 78 */	mr r3, r28
/* 80362338 0035EF18  80 DB 00 1C */	lwz r6, 0x1c(r27)
/* 8036233C 0035EF1C  80 FB 00 20 */	lwz r7, 0x20(r27)
/* 80362340 0035EF20  81 1B 00 24 */	lwz r8, 0x24(r27)
/* 80362344 0035EF24  81 3B 00 28 */	lwz r9, 0x28(r27)
/* 80362348 0035EF28  4B FD C2 61 */	bl GXSetChanCtrl
/* 8036234C 0035EF2C  88 9B 00 14 */	lbz r4, 0x14(r27)
/* 80362350 0035EF30  38 1C FF FC */	addi r0, r28, -4
/* 80362354 0035EF34  7C 7F F2 14 */	add r3, r31, r30
/* 80362358 0035EF38  98 9D 00 00 */	stb r4, 0(r29)
/* 8036235C 0035EF3C  28 00 00 01 */	cmplwi r0, 1
/* 80362360 0035EF40  80 1B 00 18 */	lwz r0, 0x18(r27)
/* 80362364 0035EF44  90 03 00 48 */	stw r0, 0x48(r3)
/* 80362368 0035EF48  80 1B 00 1C */	lwz r0, 0x1c(r27)
/* 8036236C 0035EF4C  90 03 00 4C */	stw r0, 0x4c(r3)
/* 80362370 0035EF50  80 1B 00 20 */	lwz r0, 0x20(r27)
/* 80362374 0035EF54  90 03 00 50 */	stw r0, 0x50(r3)
/* 80362378 0035EF58  80 1B 00 24 */	lwz r0, 0x24(r27)
/* 8036237C 0035EF5C  90 03 00 54 */	stw r0, 0x54(r3)
/* 80362380 0035EF60  80 1B 00 28 */	lwz r0, 0x28(r27)
/* 80362384 0035EF64  90 03 00 58 */	stw r0, 0x58(r3)
/* 80362388 0035EF68  41 81 00 34 */	bgt lbl_803623BC
/* 8036238C 0035EF6C  88 1B 00 14 */	lbz r0, 0x14(r27)
/* 80362390 0035EF70  98 03 00 A4 */	stb r0, 0xa4(r3)
/* 80362394 0035EF74  80 1B 00 18 */	lwz r0, 0x18(r27)
/* 80362398 0035EF78  90 03 00 A8 */	stw r0, 0xa8(r3)
/* 8036239C 0035EF7C  80 1B 00 1C */	lwz r0, 0x1c(r27)
/* 803623A0 0035EF80  90 03 00 AC */	stw r0, 0xac(r3)
/* 803623A4 0035EF84  80 1B 00 20 */	lwz r0, 0x20(r27)
/* 803623A8 0035EF88  90 03 00 B0 */	stw r0, 0xb0(r3)
/* 803623AC 0035EF8C  80 1B 00 24 */	lwz r0, 0x24(r27)
/* 803623B0 0035EF90  90 03 00 B4 */	stw r0, 0xb4(r3)
/* 803623B4 0035EF94  80 1B 00 28 */	lwz r0, 0x28(r27)
/* 803623B8 0035EF98  90 03 00 B8 */	stw r0, 0xb8(r3)
lbl_803623BC:
/* 803623BC 0035EF9C  BB 61 00 4C */	lmw r27, 0x4c(r1)
/* 803623C0 0035EFA0  80 01 00 64 */	lwz r0, 0x64(r1)
/* 803623C4 0035EFA4  38 21 00 60 */	addi r1, r1, 0x60
/* 803623C8 0035EFA8  7C 08 03 A6 */	mtlr r0
/* 803623CC 0035EFAC  4E 80 00 20 */	blr 
}

#pragma push
#pragma peephole on
void HSD_StateSetNumChans(s32 num)
{
    if (lbl_804D7600 != num) {
        GXSetNumChans(num & 0xFF);
    }
}
#pragma pop
