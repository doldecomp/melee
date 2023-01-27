.include "macros.inc"

.section .text  # 0x80019230 - 0x8001987C

.global func_80019230
func_80019230:
/* 80019230 00015E10  7C 08 02 A6 */	mflr r0
/* 80019234 00015E14  90 01 00 04 */	stw r0, 4(r1)
/* 80019238 00015E18  94 21 FF F8 */	stwu r1, -8(r1)
/* 8001923C 00015E1C  48 32 09 11 */	bl DVDGetDriveStatus
/* 80019240 00015E20  38 03 00 01 */	addi r0, r3, 1
/* 80019244 00015E24  28 00 00 0C */	cmplwi r0, 0xc
/* 80019248 00015E28  41 81 00 4C */	bgt lbl_80019294
/* 8001924C 00015E2C  3C 60 80 3C */	lis r3, jtbl_803BAAA8@ha
/* 80019250 00015E30  38 63 AA A8 */	addi r3, r3, jtbl_803BAAA8@l
/* 80019254 00015E34  54 00 10 3A */	slwi r0, r0, 2
/* 80019258 00015E38  7C 03 00 2E */	lwzx r0, r3, r0
/* 8001925C 00015E3C  7C 09 03 A6 */	mtctr r0
/* 80019260 00015E40  4E 80 04 20 */	bctr

.global lbl_80019264
lbl_80019264:
/* 80019264 00015E44  38 60 00 00 */	li r3, 0
/* 80019268 00015E48  48 00 00 30 */	b lbl_80019298

.global lbl_8001926C
lbl_8001926C:
/* 8001926C 00015E4C  38 60 00 01 */	li r3, 1
/* 80019270 00015E50  48 00 00 28 */	b lbl_80019298

.global lbl_80019274
lbl_80019274:
/* 80019274 00015E54  38 60 00 02 */	li r3, 2
/* 80019278 00015E58  48 00 00 20 */	b lbl_80019298

.global lbl_8001927C
lbl_8001927C:
/* 8001927C 00015E5C  38 60 00 03 */	li r3, 3
/* 80019280 00015E60  48 00 00 18 */	b lbl_80019298

.global lbl_80019284
lbl_80019284:
/* 80019284 00015E64  38 60 00 04 */	li r3, 4
/* 80019288 00015E68  48 00 00 10 */	b lbl_80019298

.global lbl_8001928C
lbl_8001928C:
/* 8001928C 00015E6C  38 60 00 05 */	li r3, 5
/* 80019290 00015E70  48 00 00 08 */	b lbl_80019298

.global lbl_80019294
lbl_80019294:
/* 80019294 00015E74  38 60 FF FF */	li r3, -1
lbl_80019298:
/* 80019298 00015E78  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8001929C 00015E7C  38 21 00 08 */	addi r1, r1, 8
/* 800192A0 00015E80  7C 08 03 A6 */	mtlr r0
/* 800192A4 00015E84  4E 80 00 20 */	blr

.global func_800192A8
func_800192A8:
/* 800192A8 00015E88  7C 08 02 A6 */	mflr r0
/* 800192AC 00015E8C  3C 80 80 3C */	lis r4, lbl_803BA708@ha
/* 800192B0 00015E90  90 01 00 04 */	stw r0, 4(r1)
/* 800192B4 00015E94  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800192B8 00015E98  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 800192BC 00015E9C  3B C3 00 00 */	addi r30, r3, 0
/* 800192C0 00015EA0  3B 84 A7 08 */	addi r28, r4, lbl_803BA708@l
/* 800192C4 00015EA4  3B E0 FF FF */	li r31, -1
/* 800192C8 00015EA8  4B FF FF 69 */	bl func_80019230
/* 800192CC 00015EAC  3B 63 00 00 */	addi r27, r3, 0
/* 800192D0 00015EB0  2C 1B FF FF */	cmpwi r27, -1
/* 800192D4 00015EB4  41 82 02 74 */	beq lbl_80019548
/* 800192D8 00015EB8  2C 1B 00 05 */	cmpwi r27, 5
/* 800192DC 00015EBC  41 82 02 6C */	beq lbl_80019548
/* 800192E0 00015EC0  48 00 BC 29 */	bl func_80024F08
/* 800192E4 00015EC4  38 60 00 01 */	li r3, 1
/* 800192E8 00015EC8  48 35 F2 3D */	bl func_80378524
/* 800192EC 00015ECC  38 60 00 00 */	li r3, 0
/* 800192F0 00015ED0  38 80 FF FF */	li r4, -1
/* 800192F4 00015ED4  48 38 D4 61 */	bl func_803A6754
/* 800192F8 00015ED8  90 6D AD 30 */	stw r3, lbl_804D63D0@sda21(r13)
/* 800192FC 00015EDC  4B FF 1B 5D */	bl lbLang_IsSavedLanguageJP
/* 80019300 00015EE0  2C 03 00 00 */	cmpwi r3, 0
/* 80019304 00015EE4  41 82 00 1C */	beq lbl_80019320
/* 80019308 00015EE8  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 8001930C 00015EEC  C0 02 82 A0 */	lfs f0, lbl_804D7C80@sda21(r2)
/* 80019310 00015EF0  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 80019314 00015EF4  C0 02 82 A4 */	lfs f0, lbl_804D7C84@sda21(r2)
/* 80019318 00015EF8  D0 03 00 28 */	stfs f0, 0x28(r3)
/* 8001931C 00015EFC  48 00 00 18 */	b lbl_80019334
lbl_80019320:
/* 80019320 00015F00  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 80019324 00015F04  C0 02 82 A8 */	lfs f0, lbl_804D7C88@sda21(r2)
/* 80019328 00015F08  D0 03 00 24 */	stfs f0, 0x24(r3)
/* 8001932C 00015F0C  C0 02 82 AC */	lfs f0, lbl_804D7C8C@sda21(r2)
/* 80019330 00015F10  D0 03 00 28 */	stfs f0, 0x28(r3)
lbl_80019334:
/* 80019334 00015F14  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 80019338 00015F18  38 00 00 01 */	li r0, 1
/* 8001933C 00015F1C  98 03 00 4A */	stb r0, 0x4a(r3)
/* 80019340 00015F20  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 80019344 00015F24  98 03 00 49 */	stb r0, 0x49(r3)
/* 80019348 00015F28  4B FF 1B 11 */	bl lbLang_IsSavedLanguageJP
/* 8001934C 00015F2C  2C 03 00 00 */	cmpwi r3, 0
/* 80019350 00015F30  41 82 00 64 */	beq lbl_800193B4
/* 80019354 00015F34  1C 1B 00 0C */	mulli r0, r27, 0xc
/* 80019358 00015F38  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 8001935C 00015F3C  C0 22 82 B0 */	lfs f1, lbl_804D7C90@sda21(r2)
/* 80019360 00015F40  4C C6 32 42 */	crset 6
/* 80019364 00015F44  C0 42 82 B4 */	lfs f2, lbl_804D7C94@sda21(r2)
/* 80019368 00015F48  7F BC 02 14 */	add r29, r28, r0
/* 8001936C 00015F4C  80 BD 01 88 */	lwz r5, 0x188(r29)
/* 80019370 00015F50  38 8D 81 64 */	addi r4, r13, lbl_804D3804@sda21
/* 80019374 00015F54  48 38 D8 25 */	bl func_803A6B98
/* 80019378 00015F58  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 8001937C 00015F5C  4C C6 32 42 */	crset 6
/* 80019380 00015F60  C0 22 82 B0 */	lfs f1, lbl_804D7C90@sda21(r2)
/* 80019384 00015F64  38 8D 81 64 */	addi r4, r13, lbl_804D3804@sda21
/* 80019388 00015F68  C0 42 82 B8 */	lfs f2, lbl_804D7C98@sda21(r2)
/* 8001938C 00015F6C  80 BD 01 8C */	lwz r5, 0x18c(r29)
/* 80019390 00015F70  48 38 D8 09 */	bl func_803A6B98
/* 80019394 00015F74  C0 22 82 B0 */	lfs f1, lbl_804D7C90@sda21(r2)
/* 80019398 00015F78  4C C6 32 42 */	crset 6
/* 8001939C 00015F7C  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 800193A0 00015F80  38 8D 81 64 */	addi r4, r13, lbl_804D3804@sda21
/* 800193A4 00015F84  FC 40 08 90 */	fmr f2, f1
/* 800193A8 00015F88  80 BD 01 90 */	lwz r5, 0x190(r29)
/* 800193AC 00015F8C  48 38 D7 ED */	bl func_803A6B98
/* 800193B0 00015F90  48 00 00 60 */	b lbl_80019410
lbl_800193B4:
/* 800193B4 00015F94  1C 1B 00 0C */	mulli r0, r27, 0xc
/* 800193B8 00015F98  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 800193BC 00015F9C  C0 22 82 B0 */	lfs f1, lbl_804D7C90@sda21(r2)
/* 800193C0 00015FA0  4C C6 32 42 */	crset 6
/* 800193C4 00015FA4  C0 42 82 B4 */	lfs f2, lbl_804D7C94@sda21(r2)
/* 800193C8 00015FA8  7F BC 02 14 */	add r29, r28, r0
/* 800193CC 00015FAC  80 BD 03 58 */	lwz r5, 0x358(r29)
/* 800193D0 00015FB0  38 8D 81 64 */	addi r4, r13, lbl_804D3804@sda21
/* 800193D4 00015FB4  48 38 D7 C5 */	bl func_803A6B98
/* 800193D8 00015FB8  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 800193DC 00015FBC  4C C6 32 42 */	crset 6
/* 800193E0 00015FC0  C0 22 82 B0 */	lfs f1, lbl_804D7C90@sda21(r2)
/* 800193E4 00015FC4  38 8D 81 64 */	addi r4, r13, lbl_804D3804@sda21
/* 800193E8 00015FC8  C0 42 82 B8 */	lfs f2, lbl_804D7C98@sda21(r2)
/* 800193EC 00015FCC  80 BD 03 5C */	lwz r5, 0x35c(r29)
/* 800193F0 00015FD0  48 38 D7 A9 */	bl func_803A6B98
/* 800193F4 00015FD4  C0 22 82 B0 */	lfs f1, lbl_804D7C90@sda21(r2)
/* 800193F8 00015FD8  4C C6 32 42 */	crset 6
/* 800193FC 00015FDC  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 80019400 00015FE0  38 8D 81 64 */	addi r4, r13, lbl_804D3804@sda21
/* 80019404 00015FE4  FC 40 08 90 */	fmr f2, f1
/* 80019408 00015FE8  80 BD 03 60 */	lwz r5, 0x360(r29)
/* 8001940C 00015FEC  48 38 D7 8D */	bl func_803A6B98
lbl_80019410:
/* 80019410 00015FF0  7C 1B F8 00 */	cmpw r27, r31
/* 80019414 00015FF4  41 82 00 C0 */	beq lbl_800194D4
/* 80019418 00015FF8  2C 1B FF FF */	cmpwi r27, -1
/* 8001941C 00015FFC  3B FB 00 00 */	addi r31, r27, 0
/* 80019420 00016000  41 82 00 B4 */	beq lbl_800194D4
/* 80019424 00016004  4B FF 1A 35 */	bl lbLang_IsSavedLanguageJP
/* 80019428 00016008  2C 03 00 00 */	cmpwi r3, 0
/* 8001942C 0001600C  41 82 00 58 */	beq lbl_80019484
/* 80019430 00016010  1C 1B 00 0C */	mulli r0, r27, 0xc
/* 80019434 00016014  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 80019438 00016018  4C C6 31 82 */	crclr 6
/* 8001943C 0001601C  7F BC 02 14 */	add r29, r28, r0
/* 80019440 00016020  84 DD 01 88 */	lwzu r6, 0x188(r29)
/* 80019444 00016024  38 80 00 00 */	li r4, 0
/* 80019448 00016028  38 AD 81 64 */	addi r5, r13, lbl_804D3804@sda21
/* 8001944C 0001602C  48 38 DC 55 */	bl func_803A70A0
/* 80019450 00016030  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 80019454 00016034  4C C6 31 82 */	crclr 6
/* 80019458 00016038  80 DD 00 04 */	lwz r6, 4(r29)
/* 8001945C 0001603C  38 80 00 01 */	li r4, 1
/* 80019460 00016040  38 AD 81 64 */	addi r5, r13, lbl_804D3804@sda21
/* 80019464 00016044  48 38 DC 3D */	bl func_803A70A0
/* 80019468 00016048  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 8001946C 0001604C  4C C6 31 82 */	crclr 6
/* 80019470 00016050  80 DD 00 08 */	lwz r6, 8(r29)
/* 80019474 00016054  38 80 00 02 */	li r4, 2
/* 80019478 00016058  38 AD 81 64 */	addi r5, r13, lbl_804D3804@sda21
/* 8001947C 0001605C  48 38 DC 25 */	bl func_803A70A0
/* 80019480 00016060  48 00 00 54 */	b lbl_800194D4
lbl_80019484:
/* 80019484 00016064  1C 1B 00 0C */	mulli r0, r27, 0xc
/* 80019488 00016068  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 8001948C 0001606C  4C C6 31 82 */	crclr 6
/* 80019490 00016070  7F BC 02 14 */	add r29, r28, r0
/* 80019494 00016074  84 DD 03 58 */	lwzu r6, 0x358(r29)
/* 80019498 00016078  38 80 00 00 */	li r4, 0
/* 8001949C 0001607C  38 AD 81 64 */	addi r5, r13, lbl_804D3804@sda21
/* 800194A0 00016080  48 38 DC 01 */	bl func_803A70A0
/* 800194A4 00016084  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 800194A8 00016088  4C C6 31 82 */	crclr 6
/* 800194AC 0001608C  80 DD 00 04 */	lwz r6, 4(r29)
/* 800194B0 00016090  38 80 00 01 */	li r4, 1
/* 800194B4 00016094  38 AD 81 64 */	addi r5, r13, lbl_804D3804@sda21
/* 800194B8 00016098  48 38 DB E9 */	bl func_803A70A0
/* 800194BC 0001609C  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 800194C0 000160A0  4C C6 31 82 */	crclr 6
/* 800194C4 000160A4  80 DD 00 08 */	lwz r6, 8(r29)
/* 800194C8 000160A8  38 80 00 02 */	li r4, 2
/* 800194CC 000160AC  38 AD 81 64 */	addi r5, r13, lbl_804D3804@sda21
/* 800194D0 000160B0  48 38 DB D1 */	bl func_803A70A0
lbl_800194D4:
/* 800194D4 000160B4  48 32 33 C5 */	bl GXInvalidateVtxCache
/* 800194D8 000160B8  48 32 5D 99 */	bl GXInvalidateTexAll
/* 800194DC 000160BC  38 60 00 00 */	li r3, 0
/* 800194E0 000160C0  48 35 C0 59 */	bl HSD_StartRender
/* 800194E4 000160C4  38 60 00 00 */	li r3, 0
/* 800194E8 000160C8  80 8D AD 30 */	lwz r4, lbl_804D63D0@sda21(r13)
/* 800194EC 000160CC  48 38 EF D1 */	bl func_803A84BC
/* 800194F0 000160D0  48 35 C0 B9 */	bl func_803755A8
/* 800194F4 000160D4  38 60 00 00 */	li r3, 0
/* 800194F8 000160D8  48 35 CC C9 */	bl HSD_VICopyXFB
/* 800194FC 000160DC  28 1E 00 00 */	cmplwi r30, 0
/* 80019500 000160E0  41 82 00 10 */	beq lbl_80019510
/* 80019504 000160E4  39 9E 00 00 */	addi r12, r30, 0
/* 80019508 000160E8  7D 88 03 A6 */	mtlr r12
/* 8001950C 000160EC  4E 80 00 21 */	blrl
lbl_80019510:
/* 80019510 000160F0  2C 1B FF FF */	cmpwi r27, -1
/* 80019514 000160F4  41 82 00 10 */	beq lbl_80019524
/* 80019518 000160F8  4B FF FD 19 */	bl func_80019230
/* 8001951C 000160FC  7C 7B 1B 78 */	mr r27, r3
/* 80019520 00016100  4B FF FE F0 */	b lbl_80019410
lbl_80019524:
/* 80019524 00016104  48 00 BA 49 */	bl func_80024F6C
/* 80019528 00016108  38 60 00 00 */	li r3, 0
/* 8001952C 0001610C  48 35 EF F9 */	bl func_80378524
/* 80019530 00016110  80 6D AD 30 */	lwz r3, lbl_804D63D0@sda21(r13)
/* 80019534 00016114  48 38 C7 91 */	bl func_803A5CC4
/* 80019538 00016118  3C 60 80 47 */	lis r3, lbl_8046B0F0@ha
/* 8001953C 0001611C  38 63 B0 F0 */	addi r3, r3, lbl_8046B0F0@l
/* 80019540 00016120  38 00 00 01 */	li r0, 1
/* 80019544 00016124  90 03 00 0C */	stw r0, 0xc(r3)
lbl_80019548:
/* 80019548 00016128  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 8001954C 0001612C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80019550 00016130  38 21 00 30 */	addi r1, r1, 0x30
/* 80019554 00016134  7C 08 03 A6 */	mtlr r0
/* 80019558 00016138  4E 80 00 20 */	blr
lbl_8001955C:
/* 8001955C 0001613C  7C 08 02 A6 */	mflr r0
/* 80019560 00016140  90 01 00 04 */	stw r0, 4(r1)
/* 80019564 00016144  94 21 FF F8 */	stwu r1, -8(r1)
/* 80019568 00016148  48 35 D4 71 */	bl HSD_PadGetResetSwitch
/* 8001956C 0001614C  2C 03 00 00 */	cmpwi r3, 0
/* 80019570 00016150  41 82 00 48 */	beq lbl_800195B8
/* 80019574 00016154  48 00 E8 49 */	bl func_80027DBC
lbl_80019578:
/* 80019578 00016158  48 00 21 81 */	bl func_8001B6F8
/* 8001957C 0001615C  2C 03 00 0B */	cmpwi r3, 0xb
/* 80019580 00016160  41 82 FF F8 */	beq lbl_80019578
/* 80019584 00016164  38 60 00 00 */	li r3, 0
/* 80019588 00016168  48 33 56 49 */	bl VISetPostRetraceCallback
/* 8001958C 0001616C  38 60 00 00 */	li r3, 0
/* 80019590 00016170  48 33 55 FD */	bl VISetPreRetraceCallback
/* 80019594 00016174  38 60 00 01 */	li r3, 1
/* 80019598 00016178  48 33 6B 69 */	bl VISetBlack
/* 8001959C 0001617C  48 33 69 DD */	bl VIFlush
/* 800195A0 00016180  48 33 5D 75 */	bl VIWaitForRetrace
/* 800195A4 00016184  48 33 5D 71 */	bl VIWaitForRetrace
/* 800195A8 00016188  38 60 00 00 */	li r3, 0
/* 800195AC 0001618C  38 80 00 00 */	li r4, 0
/* 800195B0 00016190  38 A0 00 00 */	li r5, 0
/* 800195B4 00016194  48 32 EE 99 */	bl OSResetSystem
lbl_800195B8:
/* 800195B8 00016198  48 00 21 41 */	bl func_8001B6F8
/* 800195BC 0001619C  48 00 36 C9 */	bl func_8001CC84
/* 800195C0 000161A0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800195C4 000161A4  38 21 00 08 */	addi r1, r1, 8
/* 800195C8 000161A8  7C 08 03 A6 */	mtlr r0
/* 800195CC 000161AC  4E 80 00 20 */	blr

.global func_800195D0
func_800195D0:
/* 800195D0 000161B0  7C 08 02 A6 */	mflr r0
/* 800195D4 000161B4  3C 60 80 02 */	lis r3, lbl_8001955C@ha
/* 800195D8 000161B8  90 01 00 04 */	stw r0, 4(r1)
/* 800195DC 000161BC  38 63 95 5C */	addi r3, r3, lbl_8001955C@l
/* 800195E0 000161C0  94 21 FF F8 */	stwu r1, -8(r1)
/* 800195E4 000161C4  4B FF FC C5 */	bl func_800192A8
/* 800195E8 000161C8  48 00 36 9D */	bl func_8001CC84
/* 800195EC 000161CC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800195F0 000161D0  38 21 00 08 */	addi r1, r1, 8
/* 800195F4 000161D4  7C 08 03 A6 */	mtlr r0
/* 800195F8 000161D8  4E 80 00 20 */	blr
lbl_800195FC:
/* 800195FC 000161DC  7C 08 02 A6 */	mflr r0
/* 80019600 000161E0  38 60 00 00 */	li r3, 0
/* 80019604 000161E4  90 01 00 04 */	stw r0, 4(r1)
/* 80019608 000161E8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8001960C 000161EC  48 35 D3 F1 */	bl func_803769FC
/* 80019610 000161F0  48 00 2F F1 */	bl func_8001C600
/* 80019614 000161F4  48 00 3C A9 */	bl func_8001D2BC
/* 80019618 000161F8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8001961C 000161FC  38 21 00 08 */	addi r1, r1, 8
/* 80019620 00016200  7C 08 03 A6 */	mtlr r0
/* 80019624 00016204  4E 80 00 20 */	blr

.global func_80019628
func_80019628:
/* 80019628 00016208  7C 08 02 A6 */	mflr r0
/* 8001962C 0001620C  3C 60 80 43 */	lis r3, lbl_804329F0@ha
/* 80019630 00016210  90 01 00 04 */	stw r0, 4(r1)
/* 80019634 00016214  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80019638 00016218  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 8001963C 0001621C  3B E3 29 F0 */	addi r31, r3, lbl_804329F0@l
/* 80019640 00016220  80 9F 00 38 */	lwz r4, 0x38(r31)
/* 80019644 00016224  80 1F 00 00 */	lwz r0, 0(r31)
/* 80019648 00016228  80 BF 00 3C */	lwz r5, 0x3c(r31)
/* 8001964C 0001622C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80019650 00016230  7C 80 02 78 */	xor r0, r4, r0
/* 80019654 00016234  7C A3 1A 78 */	xor r3, r5, r3
/* 80019658 00016238  7C 60 03 79 */	or. r0, r3, r0
/* 8001965C 0001623C  41 82 02 10 */	beq lbl_8001986C
/* 80019660 00016240  90 BF 00 04 */	stw r5, 4(r31)
/* 80019664 00016244  90 9F 00 00 */	stw r4, 0(r31)
/* 80019668 00016248  80 7F 00 08 */	lwz r3, 8(r31)
/* 8001966C 0001624C  80 1F 00 00 */	lwz r0, 0(r31)
/* 80019670 00016250  6C 64 80 00 */	xoris r4, r3, 0x8000
/* 80019674 00016254  80 DF 00 0C */	lwz r6, 0xc(r31)
/* 80019678 00016258  80 BF 00 04 */	lwz r5, 4(r31)
/* 8001967C 0001625C  6C 03 80 00 */	xoris r3, r0, 0x8000
/* 80019680 00016260  7C 05 30 10 */	subfc r0, r5, r6
/* 80019684 00016264  7C 63 21 10 */	subfe r3, r3, r4
/* 80019688 00016268  7C 64 21 10 */	subfe r3, r4, r4
/* 8001968C 0001626C  7C 63 00 D1 */	neg. r3, r3
/* 80019690 00016270  40 82 00 10 */	bne lbl_800196A0
/* 80019694 00016274  38 00 00 00 */	li r0, 0
/* 80019698 00016278  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8001969C 0001627C  90 1F 00 08 */	stw r0, 8(r31)
lbl_800196A0:
/* 800196A0 00016280  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 800196A4 00016284  C8 22 82 C8 */	lfd f1, lbl_804D7CA8@sda21(r2)
/* 800196A8 00016288  80 63 00 F8 */	lwz r3, 0x800000F8@l(r3)
/* 800196AC 0001628C  3C 00 43 30 */	lis r0, 0x4330
/* 800196B0 00016290  54 63 F0 BE */	srwi r3, r3, 2
/* 800196B4 00016294  90 61 00 0C */	stw r3, 0xc(r1)
/* 800196B8 00016298  90 01 00 08 */	stw r0, 8(r1)
/* 800196BC 0001629C  C8 01 00 08 */	lfd f0, 8(r1)
/* 800196C0 000162A0  EC 20 08 28 */	fsubs f1, f0, f1
/* 800196C4 000162A4  48 30 97 91 */	bl __cvt_dbl_usll
/* 800196C8 000162A8  80 DF 00 00 */	lwz r6, 0(r31)
/* 800196CC 000162AC  3B 84 00 00 */	addi r28, r4, 0
/* 800196D0 000162B0  80 FF 00 04 */	lwz r7, 4(r31)
/* 800196D4 000162B4  3B A3 00 00 */	addi r29, r3, 0
/* 800196D8 000162B8  6C C4 80 00 */	xoris r4, r6, 0x8000
/* 800196DC 000162BC  6F A3 80 00 */	xoris r3, r29, 0x8000
/* 800196E0 000162C0  7C 1C 38 10 */	subfc r0, r28, r7
/* 800196E4 000162C4  7C 63 21 10 */	subfe r3, r3, r4
/* 800196E8 000162C8  7C 64 21 10 */	subfe r3, r4, r4
/* 800196EC 000162CC  7C 63 00 D1 */	neg. r3, r3
/* 800196F0 000162D0  41 82 00 0C */	beq lbl_800196FC
/* 800196F4 000162D4  3B 87 00 00 */	addi r28, r7, 0
/* 800196F8 000162D8  3B A6 00 00 */	addi r29, r6, 0
lbl_800196FC:
/* 800196FC 000162DC  80 DF 00 18 */	lwz r6, 0x18(r31)
/* 80019700 000162E0  6F A3 80 00 */	xoris r3, r29, 0x8000
/* 80019704 000162E4  80 FF 00 1C */	lwz r7, 0x1c(r31)
/* 80019708 000162E8  6C C4 80 00 */	xoris r4, r6, 0x8000
/* 8001970C 000162EC  7C 1C 38 10 */	subfc r0, r28, r7
/* 80019710 000162F0  7C 63 21 10 */	subfe r3, r3, r4
/* 80019714 000162F4  7C 64 21 10 */	subfe r3, r4, r4
/* 80019718 000162F8  7C 63 00 D1 */	neg. r3, r3
/* 8001971C 000162FC  41 82 00 0C */	beq lbl_80019728
/* 80019720 00016300  3B 87 00 00 */	addi r28, r7, 0
/* 80019724 00016304  3B A6 00 00 */	addi r29, r6, 0
lbl_80019728:
/* 80019728 00016308  3F 60 80 00 */	lis r27, 0x800000F8@ha
/* 8001972C 0001630C  C8 22 82 C8 */	lfd f1, lbl_804D7CA8@sda21(r2)
/* 80019730 00016310  80 1B 00 F8 */	lwz r0, 0x800000F8@l(r27)
/* 80019734 00016314  3F C0 43 30 */	lis r30, 0x4330
/* 80019738 00016318  C0 42 82 C0 */	lfs f2, lbl_804D7CA0@sda21(r2)
/* 8001973C 0001631C  54 00 F0 BE */	srwi r0, r0, 2
/* 80019740 00016320  90 01 00 0C */	stw r0, 0xc(r1)
/* 80019744 00016324  93 C1 00 08 */	stw r30, 8(r1)
/* 80019748 00016328  C8 01 00 08 */	lfd f0, 8(r1)
/* 8001974C 0001632C  EC 00 08 28 */	fsubs f0, f0, f1
/* 80019750 00016330  EC 22 00 32 */	fmuls f1, f2, f0
/* 80019754 00016334  48 30 97 01 */	bl __cvt_dbl_usll
/* 80019758 00016338  6F A5 80 00 */	xoris r5, r29, 0x8000
/* 8001975C 0001633C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80019760 00016340  7C 04 E0 10 */	subfc r0, r4, r28
/* 80019764 00016344  7C 63 29 10 */	subfe r3, r3, r5
/* 80019768 00016348  7C 65 29 10 */	subfe r3, r5, r5
/* 8001976C 0001634C  7C 63 00 D1 */	neg. r3, r3
/* 80019770 00016350  40 82 00 34 */	bne lbl_800197A4
/* 80019774 00016354  80 1B 00 F8 */	lwz r0, 0xf8(r27)
/* 80019778 00016358  C8 22 82 C8 */	lfd f1, lbl_804D7CA8@sda21(r2)
/* 8001977C 0001635C  54 00 F0 BE */	srwi r0, r0, 2
/* 80019780 00016360  C0 42 82 C0 */	lfs f2, lbl_804D7CA0@sda21(r2)
/* 80019784 00016364  90 01 00 0C */	stw r0, 0xc(r1)
/* 80019788 00016368  93 C1 00 08 */	stw r30, 8(r1)
/* 8001978C 0001636C  C8 01 00 08 */	lfd f0, 8(r1)
/* 80019790 00016370  EC 00 08 28 */	fsubs f0, f0, f1
/* 80019794 00016374  EC 22 00 32 */	fmuls f1, f2, f0
/* 80019798 00016378  48 30 96 BD */	bl __cvt_dbl_usll
/* 8001979C 0001637C  3B 84 00 00 */	addi r28, r4, 0
/* 800197A0 00016380  3B A3 00 00 */	addi r29, r3, 0
lbl_800197A4:
/* 800197A4 00016384  80 1F 00 40 */	lwz r0, 0x40(r31)
/* 800197A8 00016388  3B DF 00 40 */	addi r30, r31, 0x40
/* 800197AC 0001638C  80 7F 00 44 */	lwz r3, 0x44(r31)
/* 800197B0 00016390  7C 00 EA 78 */	xor r0, r0, r29
/* 800197B4 00016394  7C 63 E2 78 */	xor r3, r3, r28
/* 800197B8 00016398  7C 60 03 79 */	or. r0, r3, r0
/* 800197BC 0001639C  41 82 00 B0 */	beq lbl_8001986C
/* 800197C0 000163A0  93 9E 00 04 */	stw r28, 4(r30)
/* 800197C4 000163A4  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 800197C8 000163A8  3C 80 80 00 */	lis r4, 0x800000F8@ha
/* 800197CC 000163AC  93 BE 00 00 */	stw r29, 0(r30)
/* 800197D0 000163B0  38 C3 4D D3 */	addi r6, r3, 0x10624DD3@l
/* 800197D4 000163B4  38 A0 00 00 */	li r5, 0
/* 800197D8 000163B8  80 04 00 F8 */	lwz r0, 0x800000F8@l(r4)
/* 800197DC 000163BC  80 7E 00 00 */	lwz r3, 0(r30)
/* 800197E0 000163C0  54 00 F0 BE */	srwi r0, r0, 2
/* 800197E4 000163C4  80 9E 00 04 */	lwz r4, 4(r30)
/* 800197E8 000163C8  7C 06 00 16 */	mulhwu r0, r6, r0
/* 800197EC 000163CC  54 06 D1 BE */	srwi r6, r0, 6
/* 800197F0 000163D0  48 30 92 19 */	bl __div2i
/* 800197F4 000163D4  3B 84 00 00 */	addi r28, r4, 0
/* 800197F8 000163D8  28 1C 00 0B */	cmplwi r28, 0xb
/* 800197FC 000163DC  40 81 00 08 */	ble lbl_80019804
/* 80019800 000163E0  3B 80 00 0B */	li r28, 0xb
lbl_80019804:
/* 80019804 000163E4  3B 7F 00 30 */	addi r27, r31, 0x30
/* 80019808 000163E8  80 1F 00 30 */	lwz r0, 0x30(r31)
/* 8001980C 000163EC  7C 00 E0 40 */	cmplw r0, r28
/* 80019810 000163F0  41 82 00 10 */	beq lbl_80019820
/* 80019814 000163F4  7F 83 E3 78 */	mr r3, r28
/* 80019818 000163F8  48 33 45 95 */	bl SISetSamplingRate
/* 8001981C 000163FC  93 9B 00 00 */	stw r28, 0(r27)
lbl_80019820:
/* 80019820 00016400  3B 9F 00 48 */	addi r28, r31, 0x48
/* 80019824 00016404  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 80019828 00016408  2C 00 00 00 */	cmpwi r0, 0
/* 8001982C 0001640C  41 82 00 0C */	beq lbl_80019838
/* 80019830 00016410  38 7F 00 50 */	addi r3, r31, 0x50
/* 80019834 00016414  48 32 A2 79 */	bl OSCancelAlarm
lbl_80019838:
/* 80019838 00016418  3B 7F 00 50 */	addi r27, r31, 0x50
/* 8001983C 0001641C  38 7B 00 00 */	addi r3, r27, 0
/* 80019840 00016420  48 32 9F 2D */	bl OSCreateAlarm
/* 80019844 00016424  80 BE 00 00 */	lwz r5, 0(r30)
/* 80019848 00016428  3C 60 80 02 */	lis r3, lbl_800195FC@ha
/* 8001984C 0001642C  80 DE 00 04 */	lwz r6, 4(r30)
/* 80019850 00016430  39 23 95 FC */	addi r9, r3, lbl_800195FC@l
/* 80019854 00016434  38 7B 00 00 */	addi r3, r27, 0
/* 80019858 00016438  39 06 00 00 */	addi r8, r6, 0
/* 8001985C 0001643C  38 E5 00 00 */	addi r7, r5, 0
/* 80019860 00016440  48 32 A1 D1 */	bl OSSetPeriodicAlarm
/* 80019864 00016444  38 00 00 01 */	li r0, 1
/* 80019868 00016448  90 1C 00 00 */	stw r0, 0(r28)
lbl_8001986C:
/* 8001986C 0001644C  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 80019870 00016450  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80019874 00016454  38 21 00 28 */	addi r1, r1, 0x28
/* 80019878 00016458  7C 08 03 A6 */	mtlr r0
/* 8001987C 0001645C  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_803BA708
lbl_803BA708:
    .4byte 0x83668342
    .4byte 0x8358834E
    .4byte 0x834A836F
    .4byte 0x815B82F0
    .4byte 0x95C282DF
    .4byte 0x82C482AD
    .4byte 0x82BE82B3
    .4byte 0x82A28142
    .4byte NULL

.global lbl_803BA72C
lbl_803BA72C:
    .4byte 0x8358837D
    .4byte 0x83628356
    .4byte 0x83858375
    .4byte 0x83898355
    .4byte 0x815B8359
    .4byte 0x82638277
    .4byte 0x82CC8366
    .4byte 0x83428358
    .4byte 0x834E82F0
    .4byte 0x835A8362
    .4byte 0x836782B5
    .4byte 0x82C482AD
    .4byte 0x82BE82B3
    .4byte 0x82A28142
    .4byte NULL

.global lbl_803BA768
lbl_803BA768:
    .4byte 0x82B182CC
    .4byte 0x83668342
    .4byte 0x8358834E
    .4byte 0x82CD0000

.global lbl_803BA778
lbl_803BA778:
    .4byte 0x8358837D
    .4byte 0x83628356
    .4byte 0x83858375
    .4byte 0x83898355
    .4byte 0x815B8359
    .4byte 0x82638277
    .4byte 0x82CC8366
    .4byte 0x83428358
    .4byte 0x834E82C5
    .4byte 0x82CD82A0
    .4byte 0x82E882DC
    .4byte 0x82B982F1
    .4byte 0x81420000

.global lbl_803BA7AC
lbl_803BA7AC:
    .4byte 0x83668342
    .4byte 0x8358834E
    .4byte 0x82F093C7
    .4byte 0x82DF82DC
    .4byte 0x82B982F1
    .4byte 0x82C582B5
    .4byte 0x82BD8142
    .4byte NULL

.global lbl_803BA7CC
lbl_803BA7CC:
    .4byte 0x8FDA82B5
    .4byte 0x82AD82CD
    .4byte 0x967B91CC
    .4byte 0x82CC8EE6
    .4byte 0x88B590E0
    .4byte 0x96BE8F91
    .4byte 0x82F082A8
    .4byte 0x93C782DD
    .4byte 0x82AD82BE
    .4byte 0x82B382A2
    .4byte 0x81420000

.global lbl_803BA7F8
lbl_803BA7F8:
    .4byte 0x83478389
    .4byte 0x815B82AA
    .4byte 0x94AD90B6
    .4byte 0x82B582DC
    .4byte 0x82B582BD
    .4byte 0x81420000

.global lbl_803BA810
lbl_803BA810:
    .4byte 0x967B91CC
    .4byte 0x82CC8370
    .4byte 0x838F815B
    .4byte 0x837B835E
    .4byte 0x839382F0
    .4byte 0x899F82B5
    .4byte 0x82C49364
    .4byte 0x8CB982F0
    .4byte 0x826E8265
    .4byte 0x826582C9
    .4byte 0x82B58141
    .4byte NULL

.global lbl_803BA840
lbl_803BA840:
    .4byte 0x967B91CC
    .4byte 0x82CC8EE6
    .4byte 0x88B590E0
    .4byte 0x96BE8F91
    .4byte 0x82CC8E77
    .4byte 0x8EA682C9
    .4byte 0x82B582BD
    .4byte 0x82AA82C1
    .4byte 0x82C482AD
    .4byte 0x82BE82B3
    .4byte 0x82A28142
    .4byte NULL

.global lbl_803BA870
lbl_803BA870:
    .4byte 0x83668342
    .4byte 0x8358834E
    .4byte 0x82F093C7
    .4byte 0x82DD8D9E
    .4byte 0x82F182C5
    .4byte 0x82A282DC
    .4byte 0x82B78142
    .4byte NULL
    .4byte lbl_804D3800
    .4byte lbl_803BA708
    .4byte lbl_804D3800
    .4byte lbl_804D3800
    .4byte lbl_803BA72C
    .4byte lbl_804D3800
    .4byte lbl_803BA768
    .4byte lbl_803BA778
    .4byte lbl_803BA72C
    .4byte lbl_803BA7AC
    .4byte lbl_803BA7CC
    .4byte lbl_804D3800
    .4byte lbl_803BA7F8
    .4byte lbl_803BA810
    .4byte lbl_803BA840
    .4byte lbl_804D3800
    .4byte lbl_803BA870
    .4byte lbl_804D3800

.global lbl_803BA8D8
lbl_803BA8D8:
    .asciz "Close the Disc Cover."
    .balign 4

.global lbl_803BA8F0
lbl_803BA8F0:
    .asciz "Insert the Super Smash Bros. Melee Game Disc."
    .balign 4

.global lbl_803BA920
lbl_803BA920:
    .asciz "The inserted Game Disc is not"
    .balign 4

.global lbl_803BA940
lbl_803BA940:
    .asciz "Super Smash Bros. Melee."
    .balign 4

.global lbl_803BA95C
lbl_803BA95C:
    .asciz "The Game Disc could not be read."
    .balign 4

.global lbl_803BA980
lbl_803BA980:
    .asciz "Read the NINTENDO GAMECUBE Instruction Booklet"
    .balign 4

.global lbl_803BA9B0
lbl_803BA9B0:
    .asciz "for more information."
    .balign 4

.global lbl_803BA9C8
lbl_803BA9C8:
    .asciz "An error has occurred. Turn the power OFF and"
    .balign 4

.global lbl_803BA9F8
lbl_803BA9F8:
    .asciz "check the NINTENDO GAMECUBE Instruction Booklet"
    .balign 4

.global lbl_803BAA28
lbl_803BAA28:
    .asciz "for further instructions."
    .balign 4

.global lbl_803BAA44
lbl_803BAA44:
    .asciz "Reading the Game Disc..."
    .balign 4
    .4byte lbl_804D3800
    .4byte lbl_803BA8D8
    .4byte lbl_804D3800
    .4byte lbl_804D3800
    .4byte lbl_803BA8F0
    .4byte lbl_804D3800
    .4byte lbl_803BA920
    .4byte lbl_803BA940
    .4byte lbl_803BA8F0
    .4byte lbl_803BA95C
    .4byte lbl_803BA980
    .4byte lbl_803BA9B0
    .4byte lbl_803BA9C8
    .4byte lbl_803BA9F8
    .4byte lbl_803BAA28
    .4byte lbl_804D3800
    .4byte lbl_803BAA44
    .4byte lbl_804D3800


.section .sdata
    .balign 8
.global lbl_804D3800
lbl_804D3800:
    .4byte 0x00000000
