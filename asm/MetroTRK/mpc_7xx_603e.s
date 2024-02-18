.include "macros.inc"
.file "mpc_7xx_603e.c"

# 0x8032A868 - 0x8032ABE0
.text
.balign 4

.fn TRKSaveExtended1Block, global
/* 8032A868 00327448  3C 40 80 4A */	lis r2, gTRKCPUState@h
/* 8032A86C 0032744C  60 42 4C 98 */	ori r2, r2, gTRKCPUState@l
/* 8032A870 00327450  7E 00 04 A6 */	mfsr r16, 0
/* 8032A874 00327454  7E 21 04 A6 */	mfsr r17, 1
/* 8032A878 00327458  7E 42 04 A6 */	mfsr r18, 2
/* 8032A87C 0032745C  7E 63 04 A6 */	mfsr r19, 3
/* 8032A880 00327460  7E 84 04 A6 */	mfsr r20, 4
/* 8032A884 00327464  7E A5 04 A6 */	mfsr r21, 5
/* 8032A888 00327468  7E C6 04 A6 */	mfsr r22, 6
/* 8032A88C 0032746C  7E E7 04 A6 */	mfsr r23, 7
/* 8032A890 00327470  7F 08 04 A6 */	mfsr r24, 8
/* 8032A894 00327474  7F 29 04 A6 */	mfsr r25, 9
/* 8032A898 00327478  7F 4A 04 A6 */	mfsr r26, 10
/* 8032A89C 0032747C  7F 6B 04 A6 */	mfsr r27, 11
/* 8032A8A0 00327480  7F 8C 04 A6 */	mfsr r28, 12
/* 8032A8A4 00327484  7F AD 04 A6 */	mfsr r29, 13
/* 8032A8A8 00327488  7F CE 04 A6 */	mfsr r30, 14
/* 8032A8AC 0032748C  7F EF 04 A6 */	mfsr r31, 15
/* 8032A8B0 00327490  BE 02 01 A8 */	stmw r16, 0x1a8(r2)
/* 8032A8B4 00327494  7D 4C 42 E6 */	.4byte 0x7D4C42E6
/* 8032A8B8 00327498  7D 6D 42 E6 */	.4byte 0x7D6D42E6
/* 8032A8BC 0032749C  7D 90 FA A6 */	mfspr r12, HID0
/* 8032A8C0 003274A0  7D B1 FA A6 */	mfspr r13, HID1
/* 8032A8C4 003274A4  7D DB 02 A6 */	mfsrr1 r14
/* 8032A8C8 003274A8  7D FF 42 A6 */	mfspr r15, PVR
/* 8032A8CC 003274AC  7E 10 82 A6 */	mfibatu r16, 0
/* 8032A8D0 003274B0  7E 31 82 A6 */	mfibatl r17, 0
/* 8032A8D4 003274B4  7E 52 82 A6 */	mfibatu r18, 1
/* 8032A8D8 003274B8  7E 73 82 A6 */	mfibatl r19, 1
/* 8032A8DC 003274BC  7E 94 82 A6 */	mfibatu r20, 2
/* 8032A8E0 003274C0  7E B5 82 A6 */	mfibatl r21, 2
/* 8032A8E4 003274C4  7E D6 82 A6 */	mfibatu r22, 3
/* 8032A8E8 003274C8  7E F7 82 A6 */	mfibatl r23, 3
/* 8032A8EC 003274CC  7F 18 82 A6 */	mfdbatu r24, 0
/* 8032A8F0 003274D0  7F 39 82 A6 */	mfdbatl r25, 0
/* 8032A8F4 003274D4  7F 5A 82 A6 */	mfdbatu r26, 1
/* 8032A8F8 003274D8  7F 7B 82 A6 */	mfdbatl r27, 1
/* 8032A8FC 003274DC  7F 9C 82 A6 */	mfdbatu r28, 2
/* 8032A900 003274E0  7F BD 82 A6 */	mfdbatl r29, 2
/* 8032A904 003274E4  7F DE 82 A6 */	mfdbatu r30, 3
/* 8032A908 003274E8  7F FF 82 A6 */	mfdbatl r31, 3
/* 8032A90C 003274EC  BD 42 01 E8 */	stmw r10, 0x1e8(r2)
/* 8032A910 003274F0  7E D9 02 A6 */	mfsdr1 r22
/* 8032A914 003274F4  7E F3 02 A6 */	mfdar r23
/* 8032A918 003274F8  7F 12 02 A6 */	mfdsisr r24
/* 8032A91C 003274FC  7F 30 42 A6 */	mfsprg r25, 0
/* 8032A920 00327500  7F 51 42 A6 */	mfsprg r26, 1
/* 8032A924 00327504  7F 72 42 A6 */	mfsprg r27, 2
/* 8032A928 00327508  7F 93 42 A6 */	mfsprg r28, 3
/* 8032A92C 0032750C  3B A0 00 00 */	li r29, 0x0
/* 8032A930 00327510  7F D2 FA A6 */	mfspr r30, IABR
/* 8032A934 00327514  7F FA 42 A6 */	mfear r31
/* 8032A938 00327518  BE C2 02 5C */	stmw r22, 0x25c(r2)
/* 8032A93C 0032751C  7E 90 E2 A6 */	mfspr r20, GQR0
/* 8032A940 00327520  7E B1 E2 A6 */	mfspr r21, GQR1
/* 8032A944 00327524  7E D2 E2 A6 */	mfspr r22, GQR2
/* 8032A948 00327528  7E F3 E2 A6 */	mfspr r23, GQR3
/* 8032A94C 0032752C  7F 14 E2 A6 */	mfspr r24, GQR4
/* 8032A950 00327530  7F 35 E2 A6 */	mfspr r25, GQR5
/* 8032A954 00327534  7F 56 E2 A6 */	mfspr r26, GQR6
/* 8032A958 00327538  7F 77 E2 A6 */	mfspr r27, GQR7
/* 8032A95C 0032753C  7F 98 E2 A6 */	mfspr r28, HID2
/* 8032A960 00327540  7F B9 E2 A6 */	mfspr r29, WPAR
/* 8032A964 00327544  7F DA E2 A6 */	mfspr r30, DMA_U
/* 8032A968 00327548  7F FB E2 A6 */	mfspr r31, DMA_L
/* 8032A96C 0032754C  BE 82 02 FC */	stmw r20, 0x2fc(r2)
/* 8032A970 00327550  48 00 00 48 */	b .L_8032A9B8
/* 8032A974 00327554  7E 00 EA A6 */	mfspr r16, 928
/* 8032A978 00327558  7E 27 EA A6 */	mfspr r17, 935
/* 8032A97C 0032755C  7E 48 EA A6 */	mfspr r18, UMMCR0
/* 8032A980 00327560  7E 69 EA A6 */	mfspr r19, UPMC1
/* 8032A984 00327564  7E 8A EA A6 */	mfspr r20, UPMC2
/* 8032A988 00327568  7E AB EA A6 */	mfspr r21, USIA
/* 8032A98C 0032756C  7E CC EA A6 */	mfspr r22, UMMCR1
/* 8032A990 00327570  7E ED EA A6 */	mfspr r23, UPMC3
/* 8032A994 00327574  7F 0E EA A6 */	mfspr r24, UPMC4
/* 8032A998 00327578  7F 2F EA A6 */	mfspr r25, USDA
/* 8032A99C 0032757C  7F 50 EA A6 */	mfspr r26, 944
/* 8032A9A0 00327580  7F 77 EA A6 */	mfspr r27, 951
/* 8032A9A4 00327584  7F 9F EA A6 */	mfspr r28, SDA
/* 8032A9A8 00327588  7F B6 FA A6 */	mfspr r29, 1014
/* 8032A9AC 0032758C  7F D7 FA A6 */	mfspr r30, 1015
/* 8032A9B0 00327590  7F FF FA A6 */	mfspr r31, 1023
/* 8032A9B4 00327594  BE 02 02 B8 */	stmw r16, 0x2b8(r2)
.L_8032A9B8:
/* 8032A9B8 00327598  7E 75 FA A6 */	mfspr r19, DABR
/* 8032A9BC 0032759C  7E 99 EA A6 */	mfspr r20, PMC1
/* 8032A9C0 003275A0  7E BA EA A6 */	mfspr r21, PMC2
/* 8032A9C4 003275A4  7E DD EA A6 */	mfspr r22, PMC3
/* 8032A9C8 003275A8  7E FE EA A6 */	mfspr r23, PMC4
/* 8032A9CC 003275AC  7F 1B EA A6 */	mfspr r24, SIA
/* 8032A9D0 003275B0  7F 38 EA A6 */	mfspr r25, MMCR0
/* 8032A9D4 003275B4  7F 5C EA A6 */	mfspr r26, MMCR1
/* 8032A9D8 003275B8  7F 7C FA A6 */	mfspr r27, THRM1
/* 8032A9DC 003275BC  7F 9D FA A6 */	mfspr r28, THRM2
/* 8032A9E0 003275C0  7F BE FA A6 */	mfspr r29, THRM3
/* 8032A9E4 003275C4  7F DB FA A6 */	mfspr r30, ICTC
/* 8032A9E8 003275C8  7F F9 FA A6 */	mfspr r31, L2CR
/* 8032A9EC 003275CC  BE 62 02 84 */	stmw r19, 0x284(r2)
/* 8032A9F0 003275D0  48 00 00 2C */	b .L_8032AA1C
/* 8032A9F4 003275D4  7F 30 F2 A6 */	mfspr r25, 976
/* 8032A9F8 003275D8  7F 51 F2 A6 */	mfspr r26, 977
/* 8032A9FC 003275DC  7F 72 F2 A6 */	mfspr r27, 978
/* 8032AA00 003275E0  7F 93 F2 A6 */	mfspr r28, 979
/* 8032AA04 003275E4  7F B4 F2 A6 */	mfspr r29, 980
/* 8032AA08 003275E8  7F D5 F2 A6 */	mfspr r30, 981
/* 8032AA0C 003275EC  7F F6 F2 A6 */	mfspr r31, 982
/* 8032AA10 003275F0  BF 22 02 40 */	stmw r25, 0x240(r2)
/* 8032AA14 003275F4  7F F6 02 A6 */	mfdec r31
/* 8032AA18 003275F8  93 E2 02 78 */	stw r31, 0x278(r2)
.L_8032AA1C:
/* 8032AA1C 003275FC  4E 80 00 20 */	blr
.endfn TRKSaveExtended1Block

.fn TRKRestoreExtended1Block, global
/* 8032AA20 00327600  3C 40 80 4A */	lis r2, gTRKCPUState@h
/* 8032AA24 00327604  60 42 4C 98 */	ori r2, r2, gTRKCPUState@l
/* 8032AA28 00327608  3C A0 80 40 */	lis r5, gTRKRestoreFlags@h
/* 8032AA2C 0032760C  60 A5 08 48 */	ori r5, r5, gTRKRestoreFlags@l
/* 8032AA30 00327610  88 65 00 00 */	lbz r3, 0x0(r5)
/* 8032AA34 00327614  88 C5 00 01 */	lbz r6, 0x1(r5)
/* 8032AA38 00327618  38 00 00 00 */	li r0, 0x0
/* 8032AA3C 0032761C  98 05 00 00 */	stb r0, 0x0(r5)
/* 8032AA40 00327620  98 05 00 01 */	stb r0, 0x1(r5)
/* 8032AA44 00327624  2C 03 00 00 */	cmpwi r3, 0x0
/* 8032AA48 00327628  41 82 00 14 */	beq .L_8032AA5C
/* 8032AA4C 0032762C  83 02 01 E8 */	lwz r24, 0x1e8(r2)
/* 8032AA50 00327630  83 22 01 EC */	lwz r25, 0x1ec(r2)
/* 8032AA54 00327634  7F 1C 43 A6 */	mttbl r24
/* 8032AA58 00327638  7F 3D 43 A6 */	mttbu r25
.L_8032AA5C:
/* 8032AA5C 0032763C  BA 82 02 FC */	lmw r20, 0x2fc(r2)
/* 8032AA60 00327640  7E 90 E3 A6 */	mtspr GQR0, r20
/* 8032AA64 00327644  7E B1 E3 A6 */	mtspr GQR1, r21
/* 8032AA68 00327648  7E D2 E3 A6 */	mtspr GQR2, r22
/* 8032AA6C 0032764C  7E F3 E3 A6 */	mtspr GQR3, r23
/* 8032AA70 00327650  7F 14 E3 A6 */	mtspr GQR4, r24
/* 8032AA74 00327654  7F 35 E3 A6 */	mtspr GQR5, r25
/* 8032AA78 00327658  7F 56 E3 A6 */	mtspr GQR6, r26
/* 8032AA7C 0032765C  7F 77 E3 A6 */	mtspr GQR7, r27
/* 8032AA80 00327660  7F 98 E3 A6 */	mtspr HID2, r28
/* 8032AA84 00327664  7F DA E3 A6 */	mtspr DMA_U, r30
/* 8032AA88 00327668  7F FB E3 A6 */	mtspr DMA_L, r31
/* 8032AA8C 0032766C  48 00 00 1C */	b .L_8032AAA8
/* 8032AA90 00327670  BB 42 02 E0 */	lmw r26, 0x2e0(r2)
/* 8032AA94 00327674  7F 50 EB A6 */	mtspr 944, r26
/* 8032AA98 00327678  7F 77 EB A6 */	mtspr 951, r27
/* 8032AA9C 0032767C  7F B6 FB A6 */	mtspr 1014, r29
/* 8032AAA0 00327680  7F D7 FB A6 */	mtspr 1015, r30
/* 8032AAA4 00327684  7F FF FB A6 */	mtspr 1023, r31
.L_8032AAA8:
/* 8032AAA8 00327688  BA 62 02 84 */	lmw r19, 0x284(r2)
/* 8032AAAC 0032768C  7E 75 FB A6 */	mtspr DABR, r19
/* 8032AAB0 00327690  7E 99 EB A6 */	mtspr PMC1, r20
/* 8032AAB4 00327694  7E BA EB A6 */	mtspr PMC2, r21
/* 8032AAB8 00327698  7E DD EB A6 */	mtspr PMC3, r22
/* 8032AABC 0032769C  7E FE EB A6 */	mtspr PMC4, r23
/* 8032AAC0 003276A0  7F 1B EB A6 */	mtspr SIA, r24
/* 8032AAC4 003276A4  7F 38 EB A6 */	mtspr MMCR0, r25
/* 8032AAC8 003276A8  7F 5C EB A6 */	mtspr MMCR1, r26
/* 8032AACC 003276AC  7F 7C FB A6 */	mtspr THRM1, r27
/* 8032AAD0 003276B0  7F 9D FB A6 */	mtspr THRM2, r28
/* 8032AAD4 003276B4  7F BE FB A6 */	mtspr THRM3, r29
/* 8032AAD8 003276B8  7F DB FB A6 */	mtspr ICTC, r30
/* 8032AADC 003276BC  7F F9 FB A6 */	mtspr L2CR, r31
/* 8032AAE0 003276C0  48 00 00 34 */	b .L_8032AB14
/* 8032AAE4 003276C4  2C 06 00 00 */	cmpwi r6, 0x0
/* 8032AAE8 003276C8  41 82 00 0C */	beq .L_8032AAF4
/* 8032AAEC 003276CC  83 42 02 78 */	lwz r26, 0x278(r2)
/* 8032AAF0 003276D0  7F 56 03 A6 */	mtdec r26
.L_8032AAF4:
/* 8032AAF4 003276D4  BB 22 02 40 */	lmw r25, 0x240(r2)
/* 8032AAF8 003276D8  7F 30 F3 A6 */	mtspr 976, r25
/* 8032AAFC 003276DC  7F 51 F3 A6 */	mtspr 977, r26
/* 8032AB00 003276E0  7F 72 F3 A6 */	mtspr 978, r27
/* 8032AB04 003276E4  7F 93 F3 A6 */	mtspr 979, r28
/* 8032AB08 003276E8  7F B4 F3 A6 */	mtspr 980, r29
/* 8032AB0C 003276EC  7F D5 F3 A6 */	mtspr 981, r30
/* 8032AB10 003276F0  7F F6 F3 A6 */	mtspr 982, r31
.L_8032AB14:
/* 8032AB14 003276F4  BA 02 01 A8 */	lmw r16, 0x1a8(r2)
/* 8032AB18 003276F8  7E 00 01 A4 */	mtsr 0, r16
/* 8032AB1C 003276FC  7E 21 01 A4 */	mtsr 1, r17
/* 8032AB20 00327700  7E 42 01 A4 */	mtsr 2, r18
/* 8032AB24 00327704  7E 63 01 A4 */	mtsr 3, r19
/* 8032AB28 00327708  7E 84 01 A4 */	mtsr 4, r20
/* 8032AB2C 0032770C  7E A5 01 A4 */	mtsr 5, r21
/* 8032AB30 00327710  7E C6 01 A4 */	mtsr 6, r22
/* 8032AB34 00327714  7E E7 01 A4 */	mtsr 7, r23
/* 8032AB38 00327718  7F 08 01 A4 */	mtsr 8, r24
/* 8032AB3C 0032771C  7F 29 01 A4 */	mtsr 9, r25
/* 8032AB40 00327720  7F 4A 01 A4 */	mtsr 10, r26
/* 8032AB44 00327724  7F 6B 01 A4 */	mtsr 11, r27
/* 8032AB48 00327728  7F 8C 01 A4 */	mtsr 12, r28
/* 8032AB4C 0032772C  7F AD 01 A4 */	mtsr 13, r29
/* 8032AB50 00327730  7F CE 01 A4 */	mtsr 14, r30
/* 8032AB54 00327734  7F EF 01 A4 */	mtsr 15, r31
/* 8032AB58 00327738  B9 82 01 F0 */	lmw r12, 0x1f0(r2)
/* 8032AB5C 0032773C  7D 90 FB A6 */	mtspr HID0, r12
/* 8032AB60 00327740  7D B1 FB A6 */	mtspr HID1, r13
/* 8032AB64 00327744  7D DB 03 A6 */	mtsrr1 r14
/* 8032AB68 00327748  7D FF 43 A6 */	mtspr PVR, r15
/* 8032AB6C 0032774C  7E 10 83 A6 */	mtibatu 0, r16
/* 8032AB70 00327750  7E 31 83 A6 */	mtibatl 0, r17
/* 8032AB74 00327754  7E 52 83 A6 */	mtibatu 1, r18
/* 8032AB78 00327758  7E 73 83 A6 */	mtibatl 1, r19
/* 8032AB7C 0032775C  7E 94 83 A6 */	mtibatu 2, r20
/* 8032AB80 00327760  7E B5 83 A6 */	mtibatl 2, r21
/* 8032AB84 00327764  7E D6 83 A6 */	mtibatu 3, r22
/* 8032AB88 00327768  7E F7 83 A6 */	mtibatl 3, r23
/* 8032AB8C 0032776C  7F 18 83 A6 */	mtdbatu 0, r24
/* 8032AB90 00327770  7F 39 83 A6 */	mtdbatl 0, r25
/* 8032AB94 00327774  7F 5A 83 A6 */	mtdbatu 1, r26
/* 8032AB98 00327778  7F 7B 83 A6 */	mtdbatl 1, r27
/* 8032AB9C 0032777C  7F 9C 83 A6 */	mtdbatu 2, r28
/* 8032ABA0 00327780  7F BD 83 A6 */	mtdbatl 2, r29
/* 8032ABA4 00327784  7F DE 83 A6 */	mtdbatu 3, r30
/* 8032ABA8 00327788  7F FF 83 A6 */	mtdbatl 3, r31
/* 8032ABAC 0032778C  BA C2 02 5C */	lmw r22, 0x25c(r2)
/* 8032ABB0 00327790  7E D9 03 A6 */	mtsdr1 r22
/* 8032ABB4 00327794  7E F3 03 A6 */	mtdar r23
/* 8032ABB8 00327798  7F 12 03 A6 */	mtdsisr r24
/* 8032ABBC 0032779C  7F 30 43 A6 */	mtsprg 0, r25
/* 8032ABC0 003277A0  7F 51 43 A6 */	mtsprg 1, r26
/* 8032ABC4 003277A4  7F 72 43 A6 */	mtsprg 2, r27
/* 8032ABC8 003277A8  7F 93 43 A6 */	mtsprg 3, r28
/* 8032ABCC 003277AC  7F D2 FB A6 */	mtspr IABR, r30
/* 8032ABD0 003277B0  7F FA 43 A6 */	mtear r31
/* 8032ABD4 003277B4  4E 80 00 20 */	blr
.endfn TRKRestoreExtended1Block

.fn TRKTargetCPUMinorType, global
/* 8032ABD8 003277B8  38 60 00 54 */	li r3, 0x54
/* 8032ABDC 003277BC  4E 80 00 20 */	blr
.endfn TRKTargetCPUMinorType
