.include "macros.inc"

.section .text

.global __AXAuxInit
__AXAuxInit:
/* 80358F90 00355B70  38 E0 00 00 */	li r7, 0
/* 80358F94 00355B74  38 C0 00 01 */	li r6, 1
/* 80358F98 00355B78  90 ED BE 58 */	stw r7, __AXCallbackAuxA@sda21(r13)
/* 80358F9C 00355B7C  38 A0 00 02 */	li r5, 2
/* 80358FA0 00355B80  3C 80 80 4B */	lis r4, __AXBufferAuxA@ha
/* 80358FA4 00355B84  90 ED BE 5C */	stw r7, __AXCallbackAuxB@sda21(r13)
/* 80358FA8 00355B88  38 00 00 1E */	li r0, 0x1e
/* 80358FAC 00355B8C  3C 60 80 4B */	lis r3, __AXBufferAuxB@ha
/* 80358FB0 00355B90  7C 09 03 A6 */	mtctr r0
/* 80358FB4 00355B94  90 ED BE 60 */	stw r7, __AXContextAuxA@sda21(r13)
/* 80358FB8 00355B98  38 84 8E 80 */	addi r4, r4, __AXBufferAuxA@l
/* 80358FBC 00355B9C  38 03 A5 00 */	addi r0, r3, __AXBufferAuxB@l
/* 80358FC0 00355BA0  7C 83 23 78 */	mr r3, r4
/* 80358FC4 00355BA4  90 ED BE 64 */	stw r7, __AXContextAuxB@sda21(r13)
/* 80358FC8 00355BA8  7C 04 03 78 */	mr r4, r0
/* 80358FCC 00355BAC  90 ED BE 78 */	stw r7, __AXAuxDspWritePosition@sda21(r13)
/* 80358FD0 00355BB0  90 CD BE 7C */	stw r6, __AXAuxDspReadPosition@sda21(r13)
/* 80358FD4 00355BB4  90 AD BE 80 */	stw r5, __AXAuxCpuReadWritePosition@sda21(r13)
.L_80358FD8:
/* 80358FD8 00355BB8  38 00 00 00 */	li r0, 0
/* 80358FDC 00355BBC  90 03 00 00 */	stw r0, 0(r3)
/* 80358FE0 00355BC0  90 04 00 00 */	stw r0, 0(r4)
/* 80358FE4 00355BC4  90 03 00 04 */	stw r0, 4(r3)
/* 80358FE8 00355BC8  90 04 00 04 */	stw r0, 4(r4)
/* 80358FEC 00355BCC  90 03 00 08 */	stw r0, 8(r3)
/* 80358FF0 00355BD0  90 04 00 08 */	stw r0, 8(r4)
/* 80358FF4 00355BD4  90 03 00 0C */	stw r0, 0xc(r3)
/* 80358FF8 00355BD8  90 04 00 0C */	stw r0, 0xc(r4)
/* 80358FFC 00355BDC  90 03 00 10 */	stw r0, 0x10(r3)
/* 80359000 00355BE0  90 04 00 10 */	stw r0, 0x10(r4)
/* 80359004 00355BE4  90 03 00 14 */	stw r0, 0x14(r3)
/* 80359008 00355BE8  90 04 00 14 */	stw r0, 0x14(r4)
/* 8035900C 00355BEC  90 03 00 18 */	stw r0, 0x18(r3)
/* 80359010 00355BF0  90 04 00 18 */	stw r0, 0x18(r4)
/* 80359014 00355BF4  90 03 00 1C */	stw r0, 0x1c(r3)
/* 80359018 00355BF8  90 04 00 1C */	stw r0, 0x1c(r4)
/* 8035901C 00355BFC  90 03 00 20 */	stw r0, 0x20(r3)
/* 80359020 00355C00  90 04 00 20 */	stw r0, 0x20(r4)
/* 80359024 00355C04  90 03 00 24 */	stw r0, 0x24(r3)
/* 80359028 00355C08  90 04 00 24 */	stw r0, 0x24(r4)
/* 8035902C 00355C0C  90 03 00 28 */	stw r0, 0x28(r3)
/* 80359030 00355C10  90 04 00 28 */	stw r0, 0x28(r4)
/* 80359034 00355C14  90 03 00 2C */	stw r0, 0x2c(r3)
/* 80359038 00355C18  90 04 00 2C */	stw r0, 0x2c(r4)
/* 8035903C 00355C1C  90 03 00 30 */	stw r0, 0x30(r3)
/* 80359040 00355C20  90 04 00 30 */	stw r0, 0x30(r4)
/* 80359044 00355C24  90 03 00 34 */	stw r0, 0x34(r3)
/* 80359048 00355C28  90 04 00 34 */	stw r0, 0x34(r4)
/* 8035904C 00355C2C  90 03 00 38 */	stw r0, 0x38(r3)
/* 80359050 00355C30  90 04 00 38 */	stw r0, 0x38(r4)
/* 80359054 00355C34  90 03 00 3C */	stw r0, 0x3c(r3)
/* 80359058 00355C38  38 63 00 40 */	addi r3, r3, 0x40
/* 8035905C 00355C3C  90 04 00 3C */	stw r0, 0x3c(r4)
/* 80359060 00355C40  38 84 00 40 */	addi r4, r4, 0x40
/* 80359064 00355C44  42 00 FF 74 */	bdnz .L_80358FD8
/* 80359068 00355C48  4E 80 00 20 */	blr

.global __AXGetAuxAInput
__AXGetAuxAInput:
/* 8035906C 00355C4C  80 0D BE 58 */	lwz r0, __AXCallbackAuxA@sda21(r13)
/* 80359070 00355C50  28 00 00 00 */	cmplwi r0, 0
/* 80359074 00355C54  41 82 00 20 */	beq .L_80359094
/* 80359078 00355C58  80 AD BE 78 */	lwz r5, __AXAuxDspWritePosition@sda21(r13)
/* 8035907C 00355C5C  3C 80 80 4B */	lis r4, __AXBufferAuxA@ha
/* 80359080 00355C60  38 04 8E 80 */	addi r0, r4, __AXBufferAuxA@l
/* 80359084 00355C64  1C 85 07 80 */	mulli r4, r5, 0x780
/* 80359088 00355C68  7C 00 22 14 */	add r0, r0, r4
/* 8035908C 00355C6C  90 03 00 00 */	stw r0, 0(r3)
/* 80359090 00355C70  4E 80 00 20 */	blr
.L_80359094:
/* 80359094 00355C74  38 00 00 00 */	li r0, 0
/* 80359098 00355C78  90 03 00 00 */	stw r0, 0(r3)
/* 8035909C 00355C7C  4E 80 00 20 */	blr

.global __AXGetAuxAOutput
__AXGetAuxAOutput:
/* 803590A0 00355C80  80 AD BE 7C */	lwz r5, __AXAuxDspReadPosition@sda21(r13)
/* 803590A4 00355C84  3C 80 80 4B */	lis r4, __AXBufferAuxA@ha
/* 803590A8 00355C88  38 04 8E 80 */	addi r0, r4, __AXBufferAuxA@l
/* 803590AC 00355C8C  1C 85 07 80 */	mulli r4, r5, 0x780
/* 803590B0 00355C90  7C 00 22 14 */	add r0, r0, r4
/* 803590B4 00355C94  90 03 00 00 */	stw r0, 0(r3)
/* 803590B8 00355C98  4E 80 00 20 */	blr

.global __AXGetAuxBInput
__AXGetAuxBInput:
/* 803590BC 00355C9C  80 0D BE 58 */	lwz r0, __AXCallbackAuxA@sda21(r13)
/* 803590C0 00355CA0  28 00 00 00 */	cmplwi r0, 0
/* 803590C4 00355CA4  41 82 00 20 */	beq .L_803590E4
/* 803590C8 00355CA8  80 AD BE 78 */	lwz r5, __AXAuxDspWritePosition@sda21(r13)
/* 803590CC 00355CAC  3C 80 80 4B */	lis r4, __AXBufferAuxB@ha
/* 803590D0 00355CB0  38 04 A5 00 */	addi r0, r4, __AXBufferAuxB@l
/* 803590D4 00355CB4  1C 85 07 80 */	mulli r4, r5, 0x780
/* 803590D8 00355CB8  7C 00 22 14 */	add r0, r0, r4
/* 803590DC 00355CBC  90 03 00 00 */	stw r0, 0(r3)
/* 803590E0 00355CC0  4E 80 00 20 */	blr
.L_803590E4:
/* 803590E4 00355CC4  38 00 00 00 */	li r0, 0
/* 803590E8 00355CC8  90 03 00 00 */	stw r0, 0(r3)
/* 803590EC 00355CCC  4E 80 00 20 */	blr

.global __AXGetAuxBOutput
__AXGetAuxBOutput:
/* 803590F0 00355CD0  80 AD BE 7C */	lwz r5, __AXAuxDspReadPosition@sda21(r13)
/* 803590F4 00355CD4  3C 80 80 4B */	lis r4, __AXBufferAuxB@ha
/* 803590F8 00355CD8  38 04 A5 00 */	addi r0, r4, __AXBufferAuxB@l
/* 803590FC 00355CDC  1C 85 07 80 */	mulli r4, r5, 0x780
/* 80359100 00355CE0  7C 00 22 14 */	add r0, r0, r4
/* 80359104 00355CE4  90 03 00 00 */	stw r0, 0(r3)
/* 80359108 00355CE8  4E 80 00 20 */	blr

.global __AXProcessAux
__AXProcessAux:
/* 8035910C 00355CEC  7C 08 02 A6 */	mflr r0
/* 80359110 00355CF0  3C 80 80 4B */	lis r4, __AXBufferAuxA@ha
/* 80359114 00355CF4  90 01 00 04 */	stw r0, 4(r1)
/* 80359118 00355CF8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8035911C 00355CFC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80359120 00355D00  3B E4 8E 80 */	addi r31, r4, __AXBufferAuxA@l
/* 80359124 00355D04  80 0D BE 78 */	lwz r0, __AXAuxDspWritePosition@sda21(r13)
/* 80359128 00355D08  80 6D BE 7C */	lwz r3, __AXAuxDspReadPosition@sda21(r13)
/* 8035912C 00355D0C  1C 80 07 80 */	mulli r4, r0, 0x780
/* 80359130 00355D10  80 0D BE 58 */	lwz r0, __AXCallbackAuxA@sda21(r13)
/* 80359134 00355D14  1C 63 07 80 */	mulli r3, r3, 0x780
/* 80359138 00355D18  7C 9F 22 14 */	add r4, r31, r4
/* 8035913C 00355D1C  7C 7F 1A 14 */	add r3, r31, r3
/* 80359140 00355D20  90 8D BE 68 */	stw r4, __AXAuxADspWrite@sda21(r13)
/* 80359144 00355D24  38 84 16 80 */	addi r4, r4, 0x1680
/* 80359148 00355D28  90 6D BE 6C */	stw r3, __AXAuxADspRead@sda21(r13)
/* 8035914C 00355D2C  38 63 16 80 */	addi r3, r3, 0x1680
/* 80359150 00355D30  28 00 00 00 */	cmplwi r0, 0
/* 80359154 00355D34  90 8D BE 70 */	stw r4, __AXAuxBDspWrite@sda21(r13)
/* 80359158 00355D38  90 6D BE 74 */	stw r3, __AXAuxBDspRead@sda21(r13)
/* 8035915C 00355D3C  41 82 00 50 */	beq .L_803591AC
/* 80359160 00355D40  80 0D BE 80 */	lwz r0, __AXAuxCpuReadWritePosition@sda21(r13)
/* 80359164 00355D44  38 80 07 80 */	li r4, 0x780
/* 80359168 00355D48  1C 00 07 80 */	mulli r0, r0, 0x780
/* 8035916C 00355D4C  7C BF 02 14 */	add r5, r31, r0
/* 80359170 00355D50  90 A1 00 08 */	stw r5, 8(r1)
/* 80359174 00355D54  38 65 02 80 */	addi r3, r5, 0x280
/* 80359178 00355D58  38 05 05 00 */	addi r0, r5, 0x500
/* 8035917C 00355D5C  90 61 00 0C */	stw r3, 0xc(r1)
/* 80359180 00355D60  90 01 00 10 */	stw r0, 0x10(r1)
/* 80359184 00355D64  80 61 00 08 */	lwz r3, 8(r1)
/* 80359188 00355D68  4B FE B6 55 */	bl DCInvalidateRange
/* 8035918C 00355D6C  81 8D BE 58 */	lwz r12, __AXCallbackAuxA@sda21(r13)
/* 80359190 00355D70  38 61 00 08 */	addi r3, r1, 8
/* 80359194 00355D74  80 8D BE 60 */	lwz r4, __AXContextAuxA@sda21(r13)
/* 80359198 00355D78  7D 88 03 A6 */	mtlr r12
/* 8035919C 00355D7C  4E 80 00 21 */	blrl
/* 803591A0 00355D80  80 61 00 08 */	lwz r3, 8(r1)
/* 803591A4 00355D84  38 80 07 80 */	li r4, 0x780
/* 803591A8 00355D88  4B FE B6 CD */	bl DCFlushRangeNoSync
.L_803591AC:
/* 803591AC 00355D8C  80 0D BE 5C */	lwz r0, __AXCallbackAuxB@sda21(r13)
/* 803591B0 00355D90  28 00 00 00 */	cmplwi r0, 0
/* 803591B4 00355D94  41 82 00 60 */	beq .L_80359214
/* 803591B8 00355D98  80 0D BE 94 */	lwz r0, __AXClMode@sda21(r13)
/* 803591BC 00355D9C  28 00 00 04 */	cmplwi r0, 4
/* 803591C0 00355DA0  41 82 00 54 */	beq .L_80359214
/* 803591C4 00355DA4  80 0D BE 80 */	lwz r0, __AXAuxCpuReadWritePosition@sda21(r13)
/* 803591C8 00355DA8  38 80 07 80 */	li r4, 0x780
/* 803591CC 00355DAC  1C 00 07 80 */	mulli r0, r0, 0x780
/* 803591D0 00355DB0  7C BF 02 14 */	add r5, r31, r0
/* 803591D4 00355DB4  38 A5 16 80 */	addi r5, r5, 0x1680
/* 803591D8 00355DB8  90 A1 00 08 */	stw r5, 8(r1)
/* 803591DC 00355DBC  38 65 02 80 */	addi r3, r5, 0x280
/* 803591E0 00355DC0  38 05 05 00 */	addi r0, r5, 0x500
/* 803591E4 00355DC4  90 61 00 0C */	stw r3, 0xc(r1)
/* 803591E8 00355DC8  90 01 00 10 */	stw r0, 0x10(r1)
/* 803591EC 00355DCC  80 61 00 08 */	lwz r3, 8(r1)
/* 803591F0 00355DD0  4B FE B5 ED */	bl DCInvalidateRange
/* 803591F4 00355DD4  81 8D BE 5C */	lwz r12, __AXCallbackAuxB@sda21(r13)
/* 803591F8 00355DD8  38 61 00 08 */	addi r3, r1, 8
/* 803591FC 00355DDC  80 8D BE 64 */	lwz r4, __AXContextAuxB@sda21(r13)
/* 80359200 00355DE0  7D 88 03 A6 */	mtlr r12
/* 80359204 00355DE4  4E 80 00 21 */	blrl
/* 80359208 00355DE8  80 61 00 08 */	lwz r3, 8(r1)
/* 8035920C 00355DEC  38 80 07 80 */	li r4, 0x780
/* 80359210 00355DF0  4B FE B6 65 */	bl DCFlushRangeNoSync
.L_80359214:
/* 80359214 00355DF4  80 AD BE 78 */	lwz r5, __AXAuxDspWritePosition@sda21(r13)
/* 80359218 00355DF8  3C 60 AA AB */	lis r3, 0xAAAAAAAB@ha
/* 8035921C 00355DFC  80 8D BE 7C */	lwz r4, __AXAuxDspReadPosition@sda21(r13)
/* 80359220 00355E00  38 C3 AA AB */	addi r6, r3, 0xAAAAAAAB@l
/* 80359224 00355E04  80 6D BE 80 */	lwz r3, __AXAuxCpuReadWritePosition@sda21(r13)
/* 80359228 00355E08  38 05 00 01 */	addi r0, r5, 1
/* 8035922C 00355E0C  38 84 00 01 */	addi r4, r4, 1
/* 80359230 00355E10  90 0D BE 78 */	stw r0, __AXAuxDspWritePosition@sda21(r13)
/* 80359234 00355E14  38 03 00 01 */	addi r0, r3, 1
/* 80359238 00355E18  90 8D BE 7C */	stw r4, __AXAuxDspReadPosition@sda21(r13)
/* 8035923C 00355E1C  81 0D BE 78 */	lwz r8, __AXAuxDspWritePosition@sda21(r13)
/* 80359240 00355E20  90 0D BE 80 */	stw r0, __AXAuxCpuReadWritePosition@sda21(r13)
/* 80359244 00355E24  80 AD BE 7C */	lwz r5, __AXAuxDspReadPosition@sda21(r13)
/* 80359248 00355E28  7C E6 40 16 */	mulhwu r7, r6, r8
/* 8035924C 00355E2C  80 6D BE 80 */	lwz r3, __AXAuxCpuReadWritePosition@sda21(r13)
/* 80359250 00355E30  7C 86 28 16 */	mulhwu r4, r6, r5
/* 80359254 00355E34  7C 06 18 16 */	mulhwu r0, r6, r3
/* 80359258 00355E38  54 E7 F8 7E */	srwi r7, r7, 1
/* 8035925C 00355E3C  54 84 F8 7E */	srwi r4, r4, 1
/* 80359260 00355E40  54 00 F8 7E */	srwi r0, r0, 1
/* 80359264 00355E44  1C C7 00 03 */	mulli r6, r7, 3
/* 80359268 00355E48  1C 84 00 03 */	mulli r4, r4, 3
/* 8035926C 00355E4C  1C 00 00 03 */	mulli r0, r0, 3
/* 80359270 00355E50  7C C6 40 50 */	subf r6, r6, r8
/* 80359274 00355E54  7C 84 28 50 */	subf r4, r4, r5
/* 80359278 00355E58  90 CD BE 78 */	stw r6, __AXAuxDspWritePosition@sda21(r13)
/* 8035927C 00355E5C  7C 00 18 50 */	subf r0, r0, r3
/* 80359280 00355E60  90 8D BE 7C */	stw r4, __AXAuxDspReadPosition@sda21(r13)
/* 80359284 00355E64  90 0D BE 80 */	stw r0, __AXAuxCpuReadWritePosition@sda21(r13)
/* 80359288 00355E68  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8035928C 00355E6C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80359290 00355E70  38 21 00 20 */	addi r1, r1, 0x20
/* 80359294 00355E74  7C 08 03 A6 */	mtlr r0
/* 80359298 00355E78  4E 80 00 20 */	blr

.global AXRegisterAuxACallback
AXRegisterAuxACallback:
/* 8035929C 00355E7C  90 6D BE 58 */	stw r3, __AXCallbackAuxA@sda21(r13)
/* 803592A0 00355E80  90 8D BE 60 */	stw r4, __AXContextAuxA@sda21(r13)
/* 803592A4 00355E84  4E 80 00 20 */	blr

.global AXRegisterAuxBCallback
AXRegisterAuxBCallback:
/* 803592A8 00355E88  90 6D BE 5C */	stw r3, __AXCallbackAuxB@sda21(r13)
/* 803592AC 00355E8C  90 8D BE 64 */	stw r4, __AXContextAuxB@sda21(r13)
/* 803592B0 00355E90  4E 80 00 20 */	blr


.section .bss
    .balign 8

    .balign 32
.global __AXBufferAuxA
__AXBufferAuxA:
    .skip 0x1680

    .balign 32
.global __AXBufferAuxB
__AXBufferAuxB:
    .skip 0x1680


.section .sbss
    .balign 8
.global __AXCallbackAuxA
__AXCallbackAuxA:
    .skip 0x4
.global __AXCallbackAuxB
__AXCallbackAuxB:
    .skip 0x4
.global __AXContextAuxA
__AXContextAuxA:
    .skip 0x4
.global __AXContextAuxB
__AXContextAuxB:
    .skip 0x4
.global __AXAuxADspWrite
__AXAuxADspWrite:
    .skip 0x4
.global __AXAuxADspRead
__AXAuxADspRead:
    .skip 0x4
.global __AXAuxBDspWrite
__AXAuxBDspWrite:
    .skip 0x4
.global __AXAuxBDspRead
__AXAuxBDspRead:
    .skip 0x4
.global __AXAuxDspWritePosition
__AXAuxDspWritePosition:
    .skip 0x4
.global __AXAuxDspReadPosition
__AXAuxDspReadPosition:
    .skip 0x4
.global __AXAuxCpuReadWritePosition
__AXAuxCpuReadWritePosition:
    .skip 0x4
