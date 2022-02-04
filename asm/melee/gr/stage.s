.include "macros.inc"

.section .text  # 0x80224A54 - 0x80225370

.global func_80225194
func_80225194:
/* 80225194 00221D74  80 6D 93 48 */	lwz r3, lbl_804D49E8@sda21(r13)
/* 80225198 00221D78  4E 80 00 20 */	blr 

.global func_8022519C
func_8022519C:
/* 8022519C 00221D7C  1C 83 00 0C */	mulli r4, r3, 0xc
/* 802251A0 00221D80  3C 60 80 3F */	lis r3, lbl_803E9960@ha
/* 802251A4 00221D84  38 03 99 60 */	addi r0, r3, lbl_803E9960@l
/* 802251A8 00221D88  7C 60 22 14 */	add r3, r0, r4
/* 802251AC 00221D8C  80 63 00 00 */	lwz r3, 0(r3)
/* 802251B0 00221D90  4E 80 00 20 */	blr 

.global func_802251B4
func_802251B4:
/* 802251B4 00221D94  7C 08 02 A6 */	mflr r0
/* 802251B8 00221D98  1C 83 00 0C */	mulli r4, r3, 0xc
/* 802251BC 00221D9C  90 01 00 04 */	stw r0, 4(r1)
/* 802251C0 00221DA0  3C 60 80 3F */	lis r3, lbl_803E9960@ha
/* 802251C4 00221DA4  94 21 FF F8 */	stwu r1, -8(r1)
/* 802251C8 00221DA8  38 03 99 60 */	addi r0, r3, lbl_803E9960@l
/* 802251CC 00221DAC  7C 60 22 14 */	add r3, r0, r4
/* 802251D0 00221DB0  80 63 00 00 */	lwz r3, 0(r3)
/* 802251D4 00221DB4  4B F9 B4 E5 */	bl func_801C06B8
/* 802251D8 00221DB8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802251DC 00221DBC  38 21 00 08 */	addi r1, r1, 8
/* 802251E0 00221DC0  7C 08 03 A6 */	mtlr r0
/* 802251E4 00221DC4  4E 80 00 20 */	blr 

.global func_802251E8
func_802251E8:
/* 802251E8 00221DC8  7C 08 02 A6 */	mflr r0
/* 802251EC 00221DCC  1C 83 00 0C */	mulli r4, r3, 0xc
/* 802251F0 00221DD0  90 01 00 04 */	stw r0, 4(r1)
/* 802251F4 00221DD4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802251F8 00221DD8  38 AD 93 48 */	addi r5, r13, lbl_804D49E8@sda21
/* 802251FC 00221DDC  90 6D 93 48 */	stw r3, lbl_804D49E8@sda21(r13)
/* 80225200 00221DE0  3C 60 80 3F */	lis r3, lbl_803E9960@ha
/* 80225204 00221DE4  38 03 99 60 */	addi r0, r3, lbl_803E9960@l
/* 80225208 00221DE8  7C 00 22 14 */	add r0, r0, r4
/* 8022520C 00221DEC  90 05 00 04 */	stw r0, 4(r5)
/* 80225210 00221DF0  38 61 00 10 */	addi r3, r1, 0x10
/* 80225214 00221DF4  80 0D 93 50 */	lwz r0, lbl_804D49F0@sda21(r13)
/* 80225218 00221DF8  80 8D 93 54 */	lwz r4, lbl_804D49F4@sda21(r13)
/* 8022521C 00221DFC  90 01 00 10 */	stw r0, 0x10(r1)
/* 80225220 00221E00  80 0D 93 48 */	lwz r0, lbl_804D49E8@sda21(r13)
/* 80225224 00221E04  90 81 00 14 */	stw r4, 0x14(r1)
/* 80225228 00221E08  80 85 00 04 */	lwz r4, 4(r5)
/* 8022522C 00221E0C  80 84 00 00 */	lwz r4, 0(r4)
/* 80225230 00221E10  90 81 00 10 */	stw r4, 0x10(r1)
/* 80225234 00221E14  90 01 00 14 */	stw r0, 0x14(r1)
/* 80225238 00221E18  4B F9 B5 1D */	bl func_801C0754
/* 8022523C 00221E1C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80225240 00221E20  38 21 00 18 */	addi r1, r1, 0x18
/* 80225244 00221E24  7C 08 03 A6 */	mtlr r0
/* 80225248 00221E28  4E 80 00 20 */	blr 

.global func_8022524C
func_8022524C:
/* 8022524C 00221E2C  7C 08 02 A6 */	mflr r0
/* 80225250 00221E30  38 8D 93 48 */	addi r4, r13, lbl_804D49E8@sda21
/* 80225254 00221E34  90 01 00 04 */	stw r0, 4(r1)
/* 80225258 00221E38  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8022525C 00221E3C  80 0D 93 50 */	lwz r0, lbl_804D49F0@sda21(r13)
/* 80225260 00221E40  38 61 00 08 */	addi r3, r1, 8
/* 80225264 00221E44  80 AD 93 54 */	lwz r5, lbl_804D49F4@sda21(r13)
/* 80225268 00221E48  90 01 00 08 */	stw r0, 8(r1)
/* 8022526C 00221E4C  80 0D 93 48 */	lwz r0, lbl_804D49E8@sda21(r13)
/* 80225270 00221E50  90 A1 00 0C */	stw r5, 0xc(r1)
/* 80225274 00221E54  80 84 00 04 */	lwz r4, 4(r4)
/* 80225278 00221E58  80 84 00 00 */	lwz r4, 0(r4)
/* 8022527C 00221E5C  90 81 00 08 */	stw r4, 8(r1)
/* 80225280 00221E60  90 01 00 0C */	stw r0, 0xc(r1)
/* 80225284 00221E64  4B F9 B5 7D */	bl func_801C0800
/* 80225288 00221E68  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8022528C 00221E6C  38 21 00 10 */	addi r1, r1, 0x10
/* 80225290 00221E70  7C 08 03 A6 */	mtlr r0
/* 80225294 00221E74  4E 80 00 20 */	blr 

.global func_80225298
func_80225298:
/* 80225298 00221E78  7C 08 02 A6 */	mflr r0
/* 8022529C 00221E7C  38 8D 93 48 */	addi r4, r13, lbl_804D49E8@sda21
/* 802252A0 00221E80  90 01 00 04 */	stw r0, 4(r1)
/* 802252A4 00221E84  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 802252A8 00221E88  80 0D 93 50 */	lwz r0, lbl_804D49F0@sda21(r13)
/* 802252AC 00221E8C  38 61 00 08 */	addi r3, r1, 8
/* 802252B0 00221E90  80 AD 93 54 */	lwz r5, lbl_804D49F4@sda21(r13)
/* 802252B4 00221E94  90 01 00 08 */	stw r0, 8(r1)
/* 802252B8 00221E98  80 0D 93 48 */	lwz r0, lbl_804D49E8@sda21(r13)
/* 802252BC 00221E9C  90 A1 00 0C */	stw r5, 0xc(r1)
/* 802252C0 00221EA0  80 84 00 04 */	lwz r4, 4(r4)
/* 802252C4 00221EA4  80 84 00 00 */	lwz r4, 0(r4)
/* 802252C8 00221EA8  90 81 00 08 */	stw r4, 8(r1)
/* 802252CC 00221EAC  90 01 00 0C */	stw r0, 0xc(r1)
/* 802252D0 00221EB0  4B F9 BC A9 */	bl func_801C0F78
/* 802252D4 00221EB4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 802252D8 00221EB8  38 21 00 10 */	addi r1, r1, 0x10
/* 802252DC 00221EBC  7C 08 03 A6 */	mtlr r0
/* 802252E0 00221EC0  4E 80 00 20 */	blr 

.global func_802252E4
func_802252E4:
/* 802252E4 00221EC4  7C 08 02 A6 */	mflr r0
/* 802252E8 00221EC8  38 8D 93 48 */	addi r4, r13, lbl_804D49E8@sda21
/* 802252EC 00221ECC  90 01 00 04 */	stw r0, 4(r1)
/* 802252F0 00221ED0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802252F4 00221ED4  80 AD 93 50 */	lwz r5, lbl_804D49F0@sda21(r13)
/* 802252F8 00221ED8  80 0D 93 54 */	lwz r0, lbl_804D49F4@sda21(r13)
/* 802252FC 00221EDC  90 A1 00 10 */	stw r5, 0x10(r1)
/* 80225300 00221EE0  90 01 00 14 */	stw r0, 0x14(r1)
/* 80225304 00221EE4  80 84 00 04 */	lwz r4, 4(r4)
/* 80225308 00221EE8  80 04 00 00 */	lwz r0, 0(r4)
/* 8022530C 00221EEC  90 01 00 10 */	stw r0, 0x10(r1)
/* 80225310 00221EF0  90 61 00 14 */	stw r3, 0x14(r1)
/* 80225314 00221EF4  38 61 00 10 */	addi r3, r1, 0x10
/* 80225318 00221EF8  4B F9 BC A1 */	bl func_801C0FB8
/* 8022531C 00221EFC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80225320 00221F00  38 21 00 18 */	addi r1, r1, 0x18
/* 80225324 00221F04  7C 08 03 A6 */	mtlr r0
/* 80225328 00221F08  4E 80 00 20 */	blr 

.global func_8022532C
func_8022532C:
/* 8022532C 00221F0C  7C 08 02 A6 */	mflr r0
/* 80225330 00221F10  38 AD 93 48 */	addi r5, r13, lbl_804D49E8@sda21
/* 80225334 00221F14  90 01 00 04 */	stw r0, 4(r1)
/* 80225338 00221F18  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8022533C 00221F1C  80 CD 93 50 */	lwz r6, lbl_804D49F0@sda21(r13)
/* 80225340 00221F20  80 0D 93 54 */	lwz r0, lbl_804D49F4@sda21(r13)
/* 80225344 00221F24  90 C1 00 10 */	stw r6, 0x10(r1)
/* 80225348 00221F28  90 01 00 14 */	stw r0, 0x14(r1)
/* 8022534C 00221F2C  80 A5 00 04 */	lwz r5, 4(r5)
/* 80225350 00221F30  80 05 00 00 */	lwz r0, 0(r5)
/* 80225354 00221F34  90 01 00 10 */	stw r0, 0x10(r1)
/* 80225358 00221F38  90 61 00 14 */	stw r3, 0x14(r1)
/* 8022535C 00221F3C  38 61 00 10 */	addi r3, r1, 0x10
/* 80225360 00221F40  4B F9 BD 15 */	bl func_801C1074
/* 80225364 00221F44  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80225368 00221F48  38 21 00 18 */	addi r1, r1, 0x18
/* 8022536C 00221F4C  7C 08 03 A6 */	mtlr r0
/* 80225370 00221F50  4E 80 00 20 */	blr 


.section .rodata

.global lbl_803B84C8
lbl_803B84C8:
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0xC2C80000
    .4byte 0x00000000


.section .data

.global lbl_803E9940
lbl_803E9940:
    .asciz "no!=St_Player_InitPos_None"
    .balign 4
    .4byte NULL
.global lbl_803E9960
lbl_803E9960:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte 0x00000008
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000A
    .4byte NULL
    .4byte NULL
    .4byte 0x00000014
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x00000003
    .4byte NULL
    .4byte NULL
    .4byte 0x00000005
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000009
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000B
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x00000015
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001A
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000F
    .4byte NULL
    .4byte NULL
    .4byte 0x00000011
    .4byte NULL
    .4byte NULL
    .4byte 0x00000013
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001B
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001C
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001E
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000028
    .4byte NULL
    .4byte NULL
    .4byte 0x00000029
    .4byte NULL
    .4byte NULL
    .4byte 0x0000002A
    .4byte NULL
    .4byte NULL
    .4byte 0x0000002B
    .4byte NULL
    .4byte NULL
    .4byte 0x0000002C
    .4byte NULL
    .4byte NULL
    .4byte 0x0000002D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000002E
    .4byte NULL
    .4byte NULL
    .4byte 0x0000002F
    .4byte NULL
    .4byte NULL
    .4byte 0x00000030
    .4byte NULL
    .4byte NULL
    .4byte 0x00000031
    .4byte NULL
    .4byte NULL
    .4byte 0x00000032
    .4byte NULL
    .4byte NULL
    .4byte 0x00000033
    .4byte NULL
    .4byte NULL
    .4byte 0x00000034
    .4byte NULL
    .4byte NULL
    .4byte 0x00000035
    .4byte NULL
    .4byte NULL
    .4byte 0x00000036
    .4byte NULL
    .4byte NULL
    .4byte 0x00000037
    .4byte NULL
    .4byte NULL
    .4byte 0x00000038
    .4byte NULL
    .4byte NULL
    .4byte 0x00000039
    .4byte NULL
    .4byte NULL
    .4byte 0x0000003A
    .4byte NULL
    .4byte NULL
    .4byte 0x0000003B
    .4byte NULL
    .4byte NULL
    .4byte 0x0000003C
    .4byte NULL
    .4byte NULL
    .4byte 0x0000003D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000003E
    .4byte NULL
    .4byte NULL
    .4byte 0x0000003F
    .4byte NULL
    .4byte NULL
    .4byte 0x00000040
    .4byte NULL
    .4byte NULL
    .4byte 0x00000041
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001F
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte 0x00000005
    .4byte NULL
    .4byte NULL
    .4byte 0x00000020
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000008
    .4byte NULL
    .4byte NULL
    .4byte 0x00000021
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000022
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x00000014
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000027
    .4byte NULL
    .4byte NULL
    .4byte 0x00000026
    .4byte NULL
    .4byte NULL
    .4byte 0x00000043
    .4byte NULL
    .4byte NULL
    .4byte 0x00000042
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000003
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte 0x00000005
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000008
    .4byte NULL
    .4byte NULL
    .4byte 0x00000009
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000A
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000B
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000F
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x00000013
    .4byte NULL
    .4byte NULL
    .4byte 0x00000014
    .4byte NULL
    .4byte NULL
    .4byte 0x00000015
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000F
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000013
    .4byte NULL
    .4byte NULL
    .4byte 0x00000008
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000A
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000B
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x00000014
    .4byte NULL
    .4byte NULL
    .4byte 0x00000015
    .4byte NULL
    .4byte NULL
    .4byte 0x00000013
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000A
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000003
    .4byte NULL
    .4byte NULL
    .4byte 0x00000005
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000014
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001B
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000003
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000008
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000A
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x00000014
    .4byte NULL
    .4byte NULL
    .4byte 0x00000011
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000B
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000005
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000F
    .4byte NULL
    .4byte NULL
    .4byte 0x00000015
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001B
    .4byte NULL
    .4byte NULL
    .4byte 0x00000009
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000A
    .4byte NULL
    .4byte NULL
    .4byte 0x00000014
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000008
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000B
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x00000003
    .4byte NULL
    .4byte NULL
    .4byte 0x00000044
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x00000005
    .4byte NULL
    .4byte NULL
    .4byte 0x00000004
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000008
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000009
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000B
    .4byte NULL
    .4byte NULL
    .4byte 0x00000015
    .4byte NULL
    .4byte NULL
    .4byte 0x00000045
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000F
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000D
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x00000022
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001C
    .4byte NULL
    .4byte NULL
    .4byte 0x00000015
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000011
    .4byte NULL
    .4byte NULL
    .4byte 0x00000013
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001B
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000046
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000A
    .4byte NULL
    .4byte NULL
    .4byte 0x00000018
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000005
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000A
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000003
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000012
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000E
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000014
    .4byte NULL
    .4byte NULL
    .4byte 0x00000016
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x00000011
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001B
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000F
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000019
    .4byte NULL
    .4byte NULL
    .4byte 0x0000000C
    .4byte NULL
    .4byte NULL
    .4byte 0x0000001B
    .4byte NULL
    .4byte NULL
    .4byte 0x00000002
    .4byte NULL
    .4byte NULL
    .4byte 0x00000025
    .4byte NULL
    .4byte NULL
    .4byte 0x00000006
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL
    .4byte 0x00000010
    .4byte NULL
    .4byte NULL
    .4byte 0x00000007
    .4byte NULL
    .4byte NULL
    .4byte 0x00000024
    .4byte NULL
    .4byte NULL


.section .sdata

.global lbl_804D49E8
lbl_804D49E8:
    .4byte 0x00000002
    .4byte 0x00000000
.global lbl_804D49F0
lbl_804D49F0:
    .4byte 0x0000000C
.global lbl_804D49F4
lbl_804D49F4:
    .4byte 0x00000002
.global lbl_804D49F8
lbl_804D49F8:
    .asciz "stage.c"
    .balign 4
.global lbl_804D4A00
lbl_804D4A00:
    .asciz "0"
    .balign 4
    .4byte NULL


.section .sdata2

.global degrees_2_radians
degrees_2_radians:
	.4byte 0x3C8EFA35
.global unk_one_half_const_804DBCD8
unk_one_half_const_804DBCD8:
	.4byte 0x3F000000
.global unk_zero_const_804DBCD8
unk_zero_const_804DBCD8:
	.4byte 0x00000000
.global lbl_804DBCDC
lbl_804DBCDC:
	.4byte 0xC1200000
.global lbl_804DBCE0
lbl_804DBCE0:
	.4byte 0x41200000
.global lbl_804DBCE4
lbl_804DBCE4:
	.4byte 0x42C80000
.global lbl_804DBCE8
lbl_804DBCE8:
	.4byte 0xC2C80000
	.4byte 0x00000000
