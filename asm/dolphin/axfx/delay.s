.include "macros.inc"

.section .text

.global AXFXDelayCallback
AXFXDelayCallback:
/* 8035D890 0035A470  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8035D894 0035A474  38 00 00 50 */	li r0, 0x50
/* 8035D898 0035A478  7C 09 03 A6 */	mtctr r0
/* 8035D89C 0035A47C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8035D8A0 0035A480  80 C4 00 0C */	lwz r6, 0xc(r4)
/* 8035D8A4 0035A484  80 A4 00 10 */	lwz r5, 0x10(r4)
/* 8035D8A8 0035A488  80 04 00 14 */	lwz r0, 0x14(r4)
/* 8035D8AC 0035A48C  1D 66 02 80 */	mulli r11, r6, 0x280
/* 8035D8B0 0035A490  81 84 00 30 */	lwz r12, 0x30(r4)
/* 8035D8B4 0035A494  81 44 00 34 */	lwz r10, 0x34(r4)
/* 8035D8B8 0035A498  1C A5 02 80 */	mulli r5, r5, 0x280
/* 8035D8BC 0035A49C  80 C4 00 38 */	lwz r6, 0x38(r4)
/* 8035D8C0 0035A4A0  80 E3 00 00 */	lwz r7, 0(r3)
/* 8035D8C4 0035A4A4  81 03 00 04 */	lwz r8, 4(r3)
/* 8035D8C8 0035A4A8  1C 00 02 80 */	mulli r0, r0, 0x280
/* 8035D8CC 0035A4AC  81 23 00 08 */	lwz r9, 8(r3)
/* 8035D8D0 0035A4B0  7C 6C 5A 14 */	add r3, r12, r11
/* 8035D8D4 0035A4B4  7C AA 2A 14 */	add r5, r10, r5
/* 8035D8D8 0035A4B8  7C C6 02 14 */	add r6, r6, r0
.L_8035D8DC:
/* 8035D8DC 0035A4BC  81 83 00 00 */	lwz r12, 0(r3)
/* 8035D8E0 0035A4C0  80 04 00 18 */	lwz r0, 0x18(r4)
/* 8035D8E4 0035A4C4  81 67 00 00 */	lwz r11, 0(r7)
/* 8035D8E8 0035A4C8  7D 4C 01 D6 */	mullw r10, r12, r0
/* 8035D8EC 0035A4CC  83 E5 00 00 */	lwz r31, 0(r5)
/* 8035D8F0 0035A4D0  80 06 00 00 */	lwz r0, 0(r6)
/* 8035D8F4 0035A4D4  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D8F8 0035A4D8  7D 4B 52 14 */	add r10, r11, r10
/* 8035D8FC 0035A4DC  91 43 00 00 */	stw r10, 0(r3)
/* 8035D900 0035A4E0  81 44 00 1C */	lwz r10, 0x1c(r4)
/* 8035D904 0035A4E4  81 68 00 00 */	lwz r11, 0(r8)
/* 8035D908 0035A4E8  7D 5F 51 D6 */	mullw r10, r31, r10
/* 8035D90C 0035A4EC  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D910 0035A4F0  7D 4B 52 14 */	add r10, r11, r10
/* 8035D914 0035A4F4  91 45 00 00 */	stw r10, 0(r5)
/* 8035D918 0035A4F8  81 44 00 20 */	lwz r10, 0x20(r4)
/* 8035D91C 0035A4FC  81 69 00 00 */	lwz r11, 0(r9)
/* 8035D920 0035A500  7D 40 51 D6 */	mullw r10, r0, r10
/* 8035D924 0035A504  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D928 0035A508  7D 4B 52 14 */	add r10, r11, r10
/* 8035D92C 0035A50C  91 46 00 00 */	stw r10, 0(r6)
/* 8035D930 0035A510  81 44 00 24 */	lwz r10, 0x24(r4)
/* 8035D934 0035A514  7D 4C 51 D6 */	mullw r10, r12, r10
/* 8035D938 0035A518  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D93C 0035A51C  91 47 00 00 */	stw r10, 0(r7)
/* 8035D940 0035A520  81 44 00 28 */	lwz r10, 0x28(r4)
/* 8035D944 0035A524  7D 5F 51 D6 */	mullw r10, r31, r10
/* 8035D948 0035A528  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D94C 0035A52C  91 48 00 00 */	stw r10, 0(r8)
/* 8035D950 0035A530  81 44 00 2C */	lwz r10, 0x2c(r4)
/* 8035D954 0035A534  7C 00 51 D6 */	mullw r0, r0, r10
/* 8035D958 0035A538  7C 00 3E 70 */	srawi r0, r0, 7
/* 8035D95C 0035A53C  90 09 00 00 */	stw r0, 0(r9)
/* 8035D960 0035A540  81 83 00 04 */	lwz r12, 4(r3)
/* 8035D964 0035A544  80 04 00 18 */	lwz r0, 0x18(r4)
/* 8035D968 0035A548  81 67 00 04 */	lwz r11, 4(r7)
/* 8035D96C 0035A54C  7D 4C 01 D6 */	mullw r10, r12, r0
/* 8035D970 0035A550  83 E5 00 04 */	lwz r31, 4(r5)
/* 8035D974 0035A554  80 06 00 04 */	lwz r0, 4(r6)
/* 8035D978 0035A558  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D97C 0035A55C  7D 4B 52 14 */	add r10, r11, r10
/* 8035D980 0035A560  91 43 00 04 */	stw r10, 4(r3)
/* 8035D984 0035A564  38 63 00 08 */	addi r3, r3, 8
/* 8035D988 0035A568  81 44 00 1C */	lwz r10, 0x1c(r4)
/* 8035D98C 0035A56C  81 68 00 04 */	lwz r11, 4(r8)
/* 8035D990 0035A570  7D 5F 51 D6 */	mullw r10, r31, r10
/* 8035D994 0035A574  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D998 0035A578  7D 4B 52 14 */	add r10, r11, r10
/* 8035D99C 0035A57C  91 45 00 04 */	stw r10, 4(r5)
/* 8035D9A0 0035A580  38 A5 00 08 */	addi r5, r5, 8
/* 8035D9A4 0035A584  81 44 00 20 */	lwz r10, 0x20(r4)
/* 8035D9A8 0035A588  81 69 00 04 */	lwz r11, 4(r9)
/* 8035D9AC 0035A58C  7D 40 51 D6 */	mullw r10, r0, r10
/* 8035D9B0 0035A590  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D9B4 0035A594  7D 4B 52 14 */	add r10, r11, r10
/* 8035D9B8 0035A598  91 46 00 04 */	stw r10, 4(r6)
/* 8035D9BC 0035A59C  38 C6 00 08 */	addi r6, r6, 8
/* 8035D9C0 0035A5A0  81 44 00 24 */	lwz r10, 0x24(r4)
/* 8035D9C4 0035A5A4  7D 4C 51 D6 */	mullw r10, r12, r10
/* 8035D9C8 0035A5A8  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D9CC 0035A5AC  91 47 00 04 */	stw r10, 4(r7)
/* 8035D9D0 0035A5B0  38 E7 00 08 */	addi r7, r7, 8
/* 8035D9D4 0035A5B4  81 44 00 28 */	lwz r10, 0x28(r4)
/* 8035D9D8 0035A5B8  7D 5F 51 D6 */	mullw r10, r31, r10
/* 8035D9DC 0035A5BC  7D 4A 3E 70 */	srawi r10, r10, 7
/* 8035D9E0 0035A5C0  91 48 00 04 */	stw r10, 4(r8)
/* 8035D9E4 0035A5C4  39 08 00 08 */	addi r8, r8, 8
/* 8035D9E8 0035A5C8  81 44 00 2C */	lwz r10, 0x2c(r4)
/* 8035D9EC 0035A5CC  7C 00 51 D6 */	mullw r0, r0, r10
/* 8035D9F0 0035A5D0  7C 00 3E 70 */	srawi r0, r0, 7
/* 8035D9F4 0035A5D4  90 09 00 04 */	stw r0, 4(r9)
/* 8035D9F8 0035A5D8  39 29 00 08 */	addi r9, r9, 8
/* 8035D9FC 0035A5DC  42 00 FE E0 */	bdnz .L_8035D8DC
/* 8035DA00 0035A5E0  80 A4 00 0C */	lwz r5, 0xc(r4)
/* 8035DA04 0035A5E4  80 64 00 00 */	lwz r3, 0(r4)
/* 8035DA08 0035A5E8  38 A5 00 01 */	addi r5, r5, 1
/* 8035DA0C 0035A5EC  7C 05 1B 96 */	divwu r0, r5, r3
/* 8035DA10 0035A5F0  7C 00 19 D6 */	mullw r0, r0, r3
/* 8035DA14 0035A5F4  7C 00 28 50 */	subf r0, r0, r5
/* 8035DA18 0035A5F8  90 04 00 0C */	stw r0, 0xc(r4)
/* 8035DA1C 0035A5FC  80 A4 00 10 */	lwz r5, 0x10(r4)
/* 8035DA20 0035A600  80 64 00 04 */	lwz r3, 4(r4)
/* 8035DA24 0035A604  38 A5 00 01 */	addi r5, r5, 1
/* 8035DA28 0035A608  7C 05 1B 96 */	divwu r0, r5, r3
/* 8035DA2C 0035A60C  7C 00 19 D6 */	mullw r0, r0, r3
/* 8035DA30 0035A610  7C 00 28 50 */	subf r0, r0, r5
/* 8035DA34 0035A614  90 04 00 10 */	stw r0, 0x10(r4)
/* 8035DA38 0035A618  80 A4 00 14 */	lwz r5, 0x14(r4)
/* 8035DA3C 0035A61C  80 64 00 08 */	lwz r3, 8(r4)
/* 8035DA40 0035A620  38 A5 00 01 */	addi r5, r5, 1
/* 8035DA44 0035A624  7C 05 1B 96 */	divwu r0, r5, r3
/* 8035DA48 0035A628  7C 00 19 D6 */	mullw r0, r0, r3
/* 8035DA4C 0035A62C  7C 00 28 50 */	subf r0, r0, r5
/* 8035DA50 0035A630  90 04 00 14 */	stw r0, 0x14(r4)
/* 8035DA54 0035A634  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8035DA58 0035A638  38 21 00 18 */	addi r1, r1, 0x18
/* 8035DA5C 0035A63C  4E 80 00 20 */	blr

.global AXFXDelaySettings
AXFXDelaySettings:
/* 8035DA60 0035A640  7C 08 02 A6 */	mflr r0
/* 8035DA64 0035A644  90 01 00 04 */	stw r0, 4(r1)
/* 8035DA68 0035A648  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8035DA6C 0035A64C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8035DA70 0035A650  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8035DA74 0035A654  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8035DA78 0035A658  7C 7D 1B 78 */	mr r29, r3
/* 8035DA7C 0035A65C  48 00 02 31 */	bl AXFXDelayShutdown
/* 8035DA80 0035A660  4B FE 98 E5 */	bl OSDisableInterrupts
/* 8035DA84 0035A664  80 DD 00 3C */	lwz r6, 0x3c(r29)
/* 8035DA88 0035A668  3C 80 CC CD */	lis r4, 0xCCCCCCCD@ha
/* 8035DA8C 0035A66C  38 84 CC CD */	addi r4, r4, 0xCCCCCCCD@l
/* 8035DA90 0035A670  38 06 FF FB */	addi r0, r6, -5
/* 8035DA94 0035A674  54 06 28 34 */	slwi r6, r0, 5
/* 8035DA98 0035A678  38 06 00 9F */	addi r0, r6, 0x9f
/* 8035DA9C 0035A67C  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8035DAA0 0035A680  54 00 C9 FE */	srwi r0, r0, 7
/* 8035DAA4 0035A684  90 1D 00 00 */	stw r0, 0(r29)
/* 8035DAA8 0035A688  3B E0 00 00 */	li r31, 0
/* 8035DAAC 0035A68C  3C A0 51 EC */	lis r5, 0x51EB851F@ha
/* 8035DAB0 0035A690  93 FD 00 0C */	stw r31, 0xc(r29)
/* 8035DAB4 0035A694  3B C3 00 00 */	addi r30, r3, 0
/* 8035DAB8 0035A698  38 05 85 1F */	addi r0, r5, 0x51EB851F@l
/* 8035DABC 0035A69C  80 7D 00 48 */	lwz r3, 0x48(r29)
/* 8035DAC0 0035A6A0  54 63 38 30 */	slwi r3, r3, 7
/* 8035DAC4 0035A6A4  7C 60 18 16 */	mulhwu r3, r0, r3
/* 8035DAC8 0035A6A8  54 63 D9 7E */	srwi r3, r3, 5
/* 8035DACC 0035A6AC  90 7D 00 18 */	stw r3, 0x18(r29)
/* 8035DAD0 0035A6B0  80 7D 00 54 */	lwz r3, 0x54(r29)
/* 8035DAD4 0035A6B4  54 63 38 30 */	slwi r3, r3, 7
/* 8035DAD8 0035A6B8  7C 60 18 16 */	mulhwu r3, r0, r3
/* 8035DADC 0035A6BC  54 63 D9 7E */	srwi r3, r3, 5
/* 8035DAE0 0035A6C0  90 7D 00 24 */	stw r3, 0x24(r29)
/* 8035DAE4 0035A6C4  80 7D 00 40 */	lwz r3, 0x40(r29)
/* 8035DAE8 0035A6C8  38 63 FF FB */	addi r3, r3, -5
/* 8035DAEC 0035A6CC  54 63 28 34 */	slwi r3, r3, 5
/* 8035DAF0 0035A6D0  38 63 00 9F */	addi r3, r3, 0x9f
/* 8035DAF4 0035A6D4  7C 64 18 16 */	mulhwu r3, r4, r3
/* 8035DAF8 0035A6D8  54 63 C9 FE */	srwi r3, r3, 7
/* 8035DAFC 0035A6DC  90 7D 00 04 */	stw r3, 4(r29)
/* 8035DB00 0035A6E0  93 FD 00 10 */	stw r31, 0x10(r29)
/* 8035DB04 0035A6E4  80 7D 00 4C */	lwz r3, 0x4c(r29)
/* 8035DB08 0035A6E8  54 63 38 30 */	slwi r3, r3, 7
/* 8035DB0C 0035A6EC  7C 60 18 16 */	mulhwu r3, r0, r3
/* 8035DB10 0035A6F0  54 63 D9 7E */	srwi r3, r3, 5
/* 8035DB14 0035A6F4  90 7D 00 1C */	stw r3, 0x1c(r29)
/* 8035DB18 0035A6F8  80 7D 00 58 */	lwz r3, 0x58(r29)
/* 8035DB1C 0035A6FC  54 63 38 30 */	slwi r3, r3, 7
/* 8035DB20 0035A700  7C 60 18 16 */	mulhwu r3, r0, r3
/* 8035DB24 0035A704  54 63 D9 7E */	srwi r3, r3, 5
/* 8035DB28 0035A708  90 7D 00 28 */	stw r3, 0x28(r29)
/* 8035DB2C 0035A70C  80 7D 00 44 */	lwz r3, 0x44(r29)
/* 8035DB30 0035A710  38 63 FF FB */	addi r3, r3, -5
/* 8035DB34 0035A714  54 63 28 34 */	slwi r3, r3, 5
/* 8035DB38 0035A718  38 63 00 9F */	addi r3, r3, 0x9f
/* 8035DB3C 0035A71C  7C 64 18 16 */	mulhwu r3, r4, r3
/* 8035DB40 0035A720  54 63 C9 FE */	srwi r3, r3, 7
/* 8035DB44 0035A724  90 7D 00 08 */	stw r3, 8(r29)
/* 8035DB48 0035A728  93 FD 00 14 */	stw r31, 0x14(r29)
/* 8035DB4C 0035A72C  80 7D 00 50 */	lwz r3, 0x50(r29)
/* 8035DB50 0035A730  54 63 38 30 */	slwi r3, r3, 7
/* 8035DB54 0035A734  7C 60 18 16 */	mulhwu r3, r0, r3
/* 8035DB58 0035A738  54 63 D9 7E */	srwi r3, r3, 5
/* 8035DB5C 0035A73C  90 7D 00 20 */	stw r3, 0x20(r29)
/* 8035DB60 0035A740  80 7D 00 5C */	lwz r3, 0x5c(r29)
/* 8035DB64 0035A744  54 63 38 30 */	slwi r3, r3, 7
/* 8035DB68 0035A748  7C 00 18 16 */	mulhwu r0, r0, r3
/* 8035DB6C 0035A74C  54 00 D9 7E */	srwi r0, r0, 5
/* 8035DB70 0035A750  90 1D 00 2C */	stw r0, 0x2c(r29)
/* 8035DB74 0035A754  80 1D 00 00 */	lwz r0, 0(r29)
/* 8035DB78 0035A758  81 8D A5 D0 */	lwz r12, __AXFXAlloc@sda21(r13)
/* 8035DB7C 0035A75C  1C 60 02 80 */	mulli r3, r0, 0x280
/* 8035DB80 0035A760  7D 88 03 A6 */	mtlr r12
/* 8035DB84 0035A764  4E 80 00 21 */	blrl
/* 8035DB88 0035A768  90 7D 00 30 */	stw r3, 0x30(r29)
/* 8035DB8C 0035A76C  80 1D 00 04 */	lwz r0, 4(r29)
/* 8035DB90 0035A770  81 8D A5 D0 */	lwz r12, __AXFXAlloc@sda21(r13)
/* 8035DB94 0035A774  1C 60 02 80 */	mulli r3, r0, 0x280
/* 8035DB98 0035A778  7D 88 03 A6 */	mtlr r12
/* 8035DB9C 0035A77C  4E 80 00 21 */	blrl
/* 8035DBA0 0035A780  90 7D 00 34 */	stw r3, 0x34(r29)
/* 8035DBA4 0035A784  80 1D 00 08 */	lwz r0, 8(r29)
/* 8035DBA8 0035A788  81 8D A5 D0 */	lwz r12, __AXFXAlloc@sda21(r13)
/* 8035DBAC 0035A78C  1C 60 02 80 */	mulli r3, r0, 0x280
/* 8035DBB0 0035A790  7D 88 03 A6 */	mtlr r12
/* 8035DBB4 0035A794  4E 80 00 21 */	blrl
/* 8035DBB8 0035A798  90 7D 00 38 */	stw r3, 0x38(r29)
/* 8035DBBC 0035A79C  38 60 00 00 */	li r3, 0
/* 8035DBC0 0035A7A0  80 9D 00 30 */	lwz r4, 0x30(r29)
/* 8035DBC4 0035A7A4  80 BD 00 34 */	lwz r5, 0x34(r29)
/* 8035DBC8 0035A7A8  80 DD 00 38 */	lwz r6, 0x38(r29)
/* 8035DBCC 0035A7AC  48 00 00 10 */	b .L_8035DBDC
.L_8035DBD0:
/* 8035DBD0 0035A7B0  93 E4 00 00 */	stw r31, 0(r4)
/* 8035DBD4 0035A7B4  38 84 00 04 */	addi r4, r4, 4
/* 8035DBD8 0035A7B8  38 63 00 01 */	addi r3, r3, 1
.L_8035DBDC:
/* 8035DBDC 0035A7BC  80 1D 00 00 */	lwz r0, 0(r29)
/* 8035DBE0 0035A7C0  1C 00 00 A0 */	mulli r0, r0, 0xa0
/* 8035DBE4 0035A7C4  7C 03 00 40 */	cmplw r3, r0
/* 8035DBE8 0035A7C8  41 80 FF E8 */	blt .L_8035DBD0
/* 8035DBEC 0035A7CC  38 80 00 00 */	li r4, 0
/* 8035DBF0 0035A7D0  38 64 00 00 */	addi r3, r4, 0
/* 8035DBF4 0035A7D4  48 00 00 10 */	b .L_8035DC04
.L_8035DBF8:
/* 8035DBF8 0035A7D8  90 65 00 00 */	stw r3, 0(r5)
/* 8035DBFC 0035A7DC  38 A5 00 04 */	addi r5, r5, 4
/* 8035DC00 0035A7E0  38 84 00 01 */	addi r4, r4, 1
.L_8035DC04:
/* 8035DC04 0035A7E4  80 1D 00 04 */	lwz r0, 4(r29)
/* 8035DC08 0035A7E8  1C 00 00 A0 */	mulli r0, r0, 0xa0
/* 8035DC0C 0035A7EC  7C 04 00 40 */	cmplw r4, r0
/* 8035DC10 0035A7F0  41 80 FF E8 */	blt .L_8035DBF8
/* 8035DC14 0035A7F4  38 80 00 00 */	li r4, 0
/* 8035DC18 0035A7F8  38 64 00 00 */	addi r3, r4, 0
/* 8035DC1C 0035A7FC  48 00 00 10 */	b .L_8035DC2C
.L_8035DC20:
/* 8035DC20 0035A800  90 66 00 00 */	stw r3, 0(r6)
/* 8035DC24 0035A804  38 C6 00 04 */	addi r6, r6, 4
/* 8035DC28 0035A808  38 84 00 01 */	addi r4, r4, 1
.L_8035DC2C:
/* 8035DC2C 0035A80C  80 1D 00 08 */	lwz r0, 8(r29)
/* 8035DC30 0035A810  1C 00 00 A0 */	mulli r0, r0, 0xa0
/* 8035DC34 0035A814  7C 04 00 40 */	cmplw r4, r0
/* 8035DC38 0035A818  41 80 FF E8 */	blt .L_8035DC20
/* 8035DC3C 0035A81C  7F C3 F3 78 */	mr r3, r30
/* 8035DC40 0035A820  4B FE 97 4D */	bl OSRestoreInterrupts
/* 8035DC44 0035A824  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8035DC48 0035A828  38 60 00 01 */	li r3, 1
/* 8035DC4C 0035A82C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8035DC50 0035A830  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8035DC54 0035A834  7C 08 03 A6 */	mtlr r0
/* 8035DC58 0035A838  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8035DC5C 0035A83C  38 21 00 28 */	addi r1, r1, 0x28
/* 8035DC60 0035A840  4E 80 00 20 */	blr

.global AXFXDelayInit
AXFXDelayInit:
/* 8035DC64 0035A844  7C 08 02 A6 */	mflr r0
/* 8035DC68 0035A848  90 01 00 04 */	stw r0, 4(r1)
/* 8035DC6C 0035A84C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8035DC70 0035A850  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8035DC74 0035A854  7C 7F 1B 78 */	mr r31, r3
/* 8035DC78 0035A858  4B FE 96 ED */	bl OSDisableInterrupts
/* 8035DC7C 0035A85C  38 00 00 00 */	li r0, 0
/* 8035DC80 0035A860  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8035DC84 0035A864  90 1F 00 34 */	stw r0, 0x34(r31)
/* 8035DC88 0035A868  90 1F 00 38 */	stw r0, 0x38(r31)
/* 8035DC8C 0035A86C  4B FE 97 01 */	bl OSRestoreInterrupts
/* 8035DC90 0035A870  7F E3 FB 78 */	mr r3, r31
/* 8035DC94 0035A874  4B FF FD CD */	bl AXFXDelaySettings
/* 8035DC98 0035A878  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8035DC9C 0035A87C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8035DCA0 0035A880  38 21 00 18 */	addi r1, r1, 0x18
/* 8035DCA4 0035A884  7C 08 03 A6 */	mtlr r0
/* 8035DCA8 0035A888  4E 80 00 20 */	blr

.global AXFXDelayShutdown
AXFXDelayShutdown:
/* 8035DCAC 0035A88C  7C 08 02 A6 */	mflr r0
/* 8035DCB0 0035A890  90 01 00 04 */	stw r0, 4(r1)
/* 8035DCB4 0035A894  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8035DCB8 0035A898  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8035DCBC 0035A89C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8035DCC0 0035A8A0  7C 7E 1B 78 */	mr r30, r3
/* 8035DCC4 0035A8A4  4B FE 96 A1 */	bl OSDisableInterrupts
/* 8035DCC8 0035A8A8  80 1E 00 30 */	lwz r0, 0x30(r30)
/* 8035DCCC 0035A8AC  3B E3 00 00 */	addi r31, r3, 0
/* 8035DCD0 0035A8B0  28 00 00 00 */	cmplwi r0, 0
/* 8035DCD4 0035A8B4  41 82 00 14 */	beq .L_8035DCE8
/* 8035DCD8 0035A8B8  81 8D A5 D4 */	lwz r12, __AXFXFree@sda21(r13)
/* 8035DCDC 0035A8BC  7C 03 03 78 */	mr r3, r0
/* 8035DCE0 0035A8C0  7D 88 03 A6 */	mtlr r12
/* 8035DCE4 0035A8C4  4E 80 00 21 */	blrl
.L_8035DCE8:
/* 8035DCE8 0035A8C8  80 7E 00 34 */	lwz r3, 0x34(r30)
/* 8035DCEC 0035A8CC  28 03 00 00 */	cmplwi r3, 0
/* 8035DCF0 0035A8D0  41 82 00 10 */	beq .L_8035DD00
/* 8035DCF4 0035A8D4  81 8D A5 D4 */	lwz r12, __AXFXFree@sda21(r13)
/* 8035DCF8 0035A8D8  7D 88 03 A6 */	mtlr r12
/* 8035DCFC 0035A8DC  4E 80 00 21 */	blrl
.L_8035DD00:
/* 8035DD00 0035A8E0  80 7E 00 38 */	lwz r3, 0x38(r30)
/* 8035DD04 0035A8E4  28 03 00 00 */	cmplwi r3, 0
/* 8035DD08 0035A8E8  41 82 00 10 */	beq .L_8035DD18
/* 8035DD0C 0035A8EC  81 8D A5 D4 */	lwz r12, __AXFXFree@sda21(r13)
/* 8035DD10 0035A8F0  7D 88 03 A6 */	mtlr r12
/* 8035DD14 0035A8F4  4E 80 00 21 */	blrl
.L_8035DD18:
/* 8035DD18 0035A8F8  7F E3 FB 78 */	mr r3, r31
/* 8035DD1C 0035A8FC  4B FE 96 71 */	bl OSRestoreInterrupts
/* 8035DD20 0035A900  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8035DD24 0035A904  38 60 00 01 */	li r3, 1
/* 8035DD28 0035A908  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8035DD2C 0035A90C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8035DD30 0035A910  7C 08 03 A6 */	mtlr r0
/* 8035DD34 0035A914  38 21 00 18 */	addi r1, r1, 0x18
/* 8035DD38 0035A918  4E 80 00 20 */	blr
