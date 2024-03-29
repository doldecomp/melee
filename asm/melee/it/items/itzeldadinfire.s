.include "macros.inc"

.section .text

.global it_802C3AF0
it_802C3AF0:
/* 802C3AF0 002C06D0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C3AF4 002C06D4  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C3AF8 002C06D8  4E 80 00 20 */	blr

.global it_802C3AFC
it_802C3AFC:
/* 802C3AFC 002C06DC  7C 08 02 A6 */	mflr r0
/* 802C3B00 002C06E0  90 01 00 04 */	stw r0, 4(r1)
/* 802C3B04 002C06E4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802C3B08 002C06E8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802C3B0C 002C06EC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 802C3B10 002C06F0  3B C0 00 00 */	li r30, 0
/* 802C3B14 002C06F4  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 802C3B18 002C06F8  3B A4 00 00 */	addi r29, r4, 0
/* 802C3B1C 002C06FC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802C3B20 002C0700  4B FA 9E E9 */	bl it_8026DA08
/* 802C3B24 002C0704  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 802C3B28 002C0708  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C3B2C 002C070C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802C3B30 002C0710  40 81 00 18 */	ble .L_802C3B48
/* 802C3B34 002C0714  80 1D 01 34 */	lwz r0, 0x134(r29)
/* 802C3B38 002C0718  54 00 04 65 */	rlwinm. r0, r0, 0, 0x11, 0x12
/* 802C3B3C 002C071C  41 82 00 1C */	beq .L_802C3B58
/* 802C3B40 002C0720  3B C0 00 01 */	li r30, 1
/* 802C3B44 002C0724  48 00 00 14 */	b .L_802C3B58
.L_802C3B48:
/* 802C3B48 002C0728  80 1D 01 34 */	lwz r0, 0x134(r29)
/* 802C3B4C 002C072C  54 00 03 E1 */	rlwinm. r0, r0, 0, 0xf, 0x10
/* 802C3B50 002C0730  41 82 00 08 */	beq .L_802C3B58
/* 802C3B54 002C0734  3B C0 00 01 */	li r30, 1
.L_802C3B58:
/* 802C3B58 002C0738  C0 3F 00 40 */	lfs f1, 0x40(r31)
/* 802C3B5C 002C073C  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C3B60 002C0740  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802C3B64 002C0744  40 81 00 18 */	ble .L_802C3B7C
/* 802C3B68 002C0748  80 1D 01 34 */	lwz r0, 0x134(r29)
/* 802C3B6C 002C074C  54 00 06 BF */	clrlwi. r0, r0, 0x1a
/* 802C3B70 002C0750  41 82 00 1C */	beq .L_802C3B8C
/* 802C3B74 002C0754  3B C0 00 01 */	li r30, 1
/* 802C3B78 002C0758  48 00 00 14 */	b .L_802C3B8C
.L_802C3B7C:
/* 802C3B7C 002C075C  80 1D 01 34 */	lwz r0, 0x134(r29)
/* 802C3B80 002C0760  54 00 05 33 */	rlwinm. r0, r0, 0, 0x14, 0x19
/* 802C3B84 002C0764  41 82 00 08 */	beq .L_802C3B8C
/* 802C3B88 002C0768  3B C0 00 01 */	li r30, 1
.L_802C3B8C:
/* 802C3B8C 002C076C  7F C3 F3 78 */	mr r3, r30
/* 802C3B90 002C0770  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802C3B94 002C0774  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802C3B98 002C0778  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802C3B9C 002C077C  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 802C3BA0 002C0780  38 21 00 28 */	addi r1, r1, 0x28
/* 802C3BA4 002C0784  7C 08 03 A6 */	mtlr r0
/* 802C3BA8 002C0788  4E 80 00 20 */	blr

.global it_802C3BAC
it_802C3BAC:
/* 802C3BAC 002C078C  7C 08 02 A6 */	mflr r0
/* 802C3BB0 002C0790  90 01 00 04 */	stw r0, 4(r1)
/* 802C3BB4 002C0794  38 00 00 6C */	li r0, 0x6c
/* 802C3BB8 002C0798  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 802C3BBC 002C079C  DB E1 00 78 */	stfd f31, 0x78(r1)
/* 802C3BC0 002C07A0  FF E0 08 90 */	fmr f31, f1
/* 802C3BC4 002C07A4  93 E1 00 74 */	stw r31, 0x74(r1)
/* 802C3BC8 002C07A8  93 C1 00 70 */	stw r30, 0x70(r1)
/* 802C3BCC 002C07AC  93 A1 00 6C */	stw r29, 0x6c(r1)
/* 802C3BD0 002C07B0  93 81 00 68 */	stw r28, 0x68(r1)
/* 802C3BD4 002C07B4  7C 7C 1B 78 */	mr r28, r3
/* 802C3BD8 002C07B8  90 01 00 24 */	stw r0, 0x24(r1)
/* 802C3BDC 002C07BC  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C3BE0 002C07C0  80 A4 00 00 */	lwz r5, 0(r4)
/* 802C3BE4 002C07C4  80 04 00 04 */	lwz r0, 4(r4)
/* 802C3BE8 002C07C8  90 A1 00 3C */	stw r5, 0x3c(r1)
/* 802C3BEC 002C07CC  90 01 00 40 */	stw r0, 0x40(r1)
/* 802C3BF0 002C07D0  80 04 00 08 */	lwz r0, 8(r4)
/* 802C3BF4 002C07D4  38 81 00 30 */	addi r4, r1, 0x30
/* 802C3BF8 002C07D8  90 01 00 44 */	stw r0, 0x44(r1)
/* 802C3BFC 002C07DC  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 802C3C00 002C07E0  4B FA 7F 69 */	bl it_8026BB68
/* 802C3C04 002C07E4  D3 E1 00 54 */	stfs f31, 0x54(r1)
/* 802C3C08 002C07E8  3B E0 00 00 */	li r31, 0
/* 802C3C0C 002C07EC  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C3C10 002C07F0  38 80 00 01 */	li r4, 1
/* 802C3C14 002C07F4  B3 E1 00 58 */	sth r31, 0x58(r1)
/* 802C3C18 002C07F8  38 61 00 1C */	addi r3, r1, 0x1c
/* 802C3C1C 002C07FC  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 802C3C20 002C0800  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 802C3C24 002C0804  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 802C3C28 002C0808  93 81 00 1C */	stw r28, 0x1c(r1)
/* 802C3C2C 002C080C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802C3C30 002C0810  90 01 00 20 */	stw r0, 0x20(r1)
/* 802C3C34 002C0814  88 01 00 60 */	lbz r0, 0x60(r1)
/* 802C3C38 002C0818  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 802C3C3C 002C081C  98 01 00 60 */	stb r0, 0x60(r1)
/* 802C3C40 002C0820  93 E1 00 5C */	stw r31, 0x5c(r1)
/* 802C3C44 002C0824  4B FA 4E D5 */	bl Item_80268B18
/* 802C3C48 002C0828  7C 7E 1B 79 */	or. r30, r3, r3
/* 802C3C4C 002C082C  41 82 00 48 */	beq .L_802C3C94
/* 802C3C50 002C0830  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 802C3C54 002C0834  7F C3 F3 78 */	mr r3, r30
/* 802C3C58 002C0838  80 9D 00 C4 */	lwz r4, 0xc4(r29)
/* 802C3C5C 002C083C  80 84 00 04 */	lwz r4, 4(r4)
/* 802C3C60 002C0840  93 FD 0D B8 */	stw r31, 0xdb8(r29)
/* 802C3C64 002C0844  93 FD 0D B4 */	stw r31, 0xdb4(r29)
/* 802C3C68 002C0848  93 FD 0D B0 */	stw r31, 0xdb0(r29)
/* 802C3C6C 002C084C  93 FD 0D AC */	stw r31, 0xdac(r29)
/* 802C3C70 002C0850  C0 24 00 00 */	lfs f1, 0(r4)
/* 802C3C74 002C0854  4B FB 14 E5 */	bl it_80275158
/* 802C3C78 002C0858  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C3C7C 002C085C  7F C3 F3 78 */	mr r3, r30
/* 802C3C80 002C0860  D0 1D 0D D8 */	stfs f0, 0xdd8(r29)
/* 802C3C84 002C0864  93 FD 0D DC */	stw r31, 0xddc(r29)
/* 802C3C88 002C0868  93 9D 0D E0 */	stw r28, 0xde0(r29)
/* 802C3C8C 002C086C  93 FD 0D E4 */	stw r31, 0xde4(r29)
/* 802C3C90 002C0870  48 00 00 E5 */	bl it_802C3D74
.L_802C3C94:
/* 802C3C94 002C0874  7F C3 F3 78 */	mr r3, r30
/* 802C3C98 002C0878  80 01 00 84 */	lwz r0, 0x84(r1)
/* 802C3C9C 002C087C  CB E1 00 78 */	lfd f31, 0x78(r1)
/* 802C3CA0 002C0880  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 802C3CA4 002C0884  83 C1 00 70 */	lwz r30, 0x70(r1)
/* 802C3CA8 002C0888  83 A1 00 6C */	lwz r29, 0x6c(r1)
/* 802C3CAC 002C088C  83 81 00 68 */	lwz r28, 0x68(r1)
/* 802C3CB0 002C0890  38 21 00 80 */	addi r1, r1, 0x80
/* 802C3CB4 002C0894  7C 08 03 A6 */	mtlr r0
/* 802C3CB8 002C0898  4E 80 00 20 */	blr

.global it_802C3CBC
it_802C3CBC:
/* 802C3CBC 002C089C  7C 08 02 A6 */	mflr r0
/* 802C3CC0 002C08A0  90 01 00 04 */	stw r0, 4(r1)
/* 802C3CC4 002C08A4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802C3CC8 002C08A8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802C3CCC 002C08AC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 802C3CD0 002C08B0  7C 7E 1B 78 */	mr r30, r3
/* 802C3CD4 002C08B4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802C3CD8 002C08B8  4B FA E8 FD */	bl it_802725D4
/* 802C3CDC 002C08BC  80 7F 0D E0 */	lwz r3, 0xde0(r31)
/* 802C3CE0 002C08C0  28 03 00 00 */	cmplwi r3, 0
/* 802C3CE4 002C08C4  41 82 00 1C */	beq .L_802C3D00
/* 802C3CE8 002C08C8  80 1F 05 18 */	lwz r0, 0x518(r31)
/* 802C3CEC 002C08CC  7C 00 18 40 */	cmplw r0, r3
/* 802C3CF0 002C08D0  40 82 00 08 */	bne .L_802C3CF8
/* 802C3CF4 002C08D4  4B E7 78 D1 */	bl ftZd_SpecialLw_8013B5C4
.L_802C3CF8:
/* 802C3CF8 002C08D8  38 00 00 00 */	li r0, 0
/* 802C3CFC 002C08DC  90 1F 0D E0 */	stw r0, 0xde0(r31)
.L_802C3D00:
/* 802C3D00 002C08E0  80 1F 0D F4 */	lwz r0, 0xdf4(r31)
/* 802C3D04 002C08E4  28 00 00 00 */	cmplwi r0, 0
/* 802C3D08 002C08E8  41 82 00 14 */	beq .L_802C3D1C
/* 802C3D0C 002C08EC  7F C3 F3 78 */	mr r3, r30
/* 802C3D10 002C08F0  4B D9 7B 71 */	bl efLib_DestroyAll
/* 802C3D14 002C08F4  38 00 00 00 */	li r0, 0
/* 802C3D18 002C08F8  90 1F 0D F4 */	stw r0, 0xdf4(r31)
.L_802C3D1C:
/* 802C3D1C 002C08FC  88 1F 0D CA */	lbz r0, 0xdca(r31)
/* 802C3D20 002C0900  38 60 00 00 */	li r3, 0
/* 802C3D24 002C0904  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 802C3D28 002C0908  98 1F 0D CA */	stb r0, 0xdca(r31)
/* 802C3D2C 002C090C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802C3D30 002C0910  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802C3D34 002C0914  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 802C3D38 002C0918  38 21 00 18 */	addi r1, r1, 0x18
/* 802C3D3C 002C091C  7C 08 03 A6 */	mtlr r0
/* 802C3D40 002C0920  4E 80 00 20 */	blr

.global it_802C3D44
it_802C3D44:
/* 802C3D44 002C0924  28 03 00 00 */	cmplwi r3, 0
/* 802C3D48 002C0928  4D 82 00 20 */	beqlr
/* 802C3D4C 002C092C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802C3D50 002C0930  28 04 00 00 */	cmplwi r4, 0
/* 802C3D54 002C0934  4D 82 00 20 */	beqlr
/* 802C3D58 002C0938  38 60 00 00 */	li r3, 0
/* 802C3D5C 002C093C  90 64 05 18 */	stw r3, 0x518(r4)
/* 802C3D60 002C0940  90 64 0D E0 */	stw r3, 0xde0(r4)
/* 802C3D64 002C0944  88 04 0D CA */	lbz r0, 0xdca(r4)
/* 802C3D68 002C0948  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 802C3D6C 002C094C  98 04 0D CA */	stb r0, 0xdca(r4)
/* 802C3D70 002C0950  4E 80 00 20 */	blr

.global it_802C3D74
it_802C3D74:
/* 802C3D74 002C0954  7C 08 02 A6 */	mflr r0
/* 802C3D78 002C0958  90 01 00 04 */	stw r0, 4(r1)
/* 802C3D7C 002C095C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802C3D80 002C0960  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 802C3D84 002C0964  7C 7B 1B 78 */	mr r27, r3
/* 802C3D88 002C0968  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 802C3D8C 002C096C  83 9B 00 28 */	lwz r28, 0x28(r27)
/* 802C3D90 002C0970  80 9E 00 C4 */	lwz r4, 0xc4(r30)
/* 802C3D94 002C0974  83 A4 00 04 */	lwz r29, 4(r4)
/* 802C3D98 002C0978  4B FA 76 11 */	bl it_8026B3A8
/* 802C3D9C 002C097C  88 1E 0D CA */	lbz r0, 0xdca(r30)
/* 802C3DA0 002C0980  3B E0 00 00 */	li r31, 0
/* 802C3DA4 002C0984  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 802C3DA8 002C0988  98 1E 0D CA */	stb r0, 0xdca(r30)
/* 802C3DAC 002C098C  7F 63 DB 78 */	mr r3, r27
/* 802C3DB0 002C0990  4B FA EB 91 */	bl it_80272940
/* 802C3DB4 002C0994  38 7B 00 00 */	addi r3, r27, 0
/* 802C3DB8 002C0998  38 80 00 00 */	li r4, 0
/* 802C3DBC 002C099C  38 A0 00 02 */	li r5, 2
/* 802C3DC0 002C09A0  4B FA 50 9D */	bl Item_80268E5C
/* 802C3DC4 002C09A4  7F 63 DB 78 */	mr r3, r27
/* 802C3DC8 002C09A8  C0 3D 00 00 */	lfs f1, 0(r29)
/* 802C3DCC 002C09AC  4B FB 13 8D */	bl it_80275158
/* 802C3DD0 002C09B0  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C3DD4 002C09B4  D0 1E 0D D8 */	stfs f0, 0xdd8(r30)
/* 802C3DD8 002C09B8  93 FE 0D DC */	stw r31, 0xddc(r30)
/* 802C3DDC 002C09BC  C0 3D 00 10 */	lfs f1, 0x10(r29)
/* 802C3DE0 002C09C0  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 802C3DE4 002C09C4  EC 01 00 32 */	fmuls f0, f1, f0
/* 802C3DE8 002C09C8  D0 1E 0D E8 */	stfs f0, 0xde8(r30)
/* 802C3DEC 002C09CC  C0 22 D8 3C */	lfs f1, it_804DD21C@sda21(r2)
/* 802C3DF0 002C09D0  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 802C3DF4 002C09D4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 802C3DF8 002C09D8  40 82 00 0C */	bne .L_802C3E04
/* 802C3DFC 002C09DC  C8 02 D8 40 */	lfd f0, it_804DD220@sda21(r2)
/* 802C3E00 002C09E0  48 00 00 08 */	b .L_802C3E08
.L_802C3E04:
/* 802C3E04 002C09E4  C8 02 D8 48 */	lfd f0, it_804DD228@sda21(r2)
.L_802C3E08:
/* 802C3E08 002C09E8  FC 00 00 18 */	frsp f0, f0
/* 802C3E0C 002C09EC  38 9B 00 00 */	addi r4, r27, 0
/* 802C3E10 002C09F0  38 BC 00 00 */	addi r5, r28, 0
/* 802C3E14 002C09F4  4C C6 31 82 */	crclr 6
/* 802C3E18 002C09F8  38 60 04 F8 */	li r3, 0x4f8
/* 802C3E1C 002C09FC  D0 1E 0D EC */	stfs f0, 0xdec(r30)
/* 802C3E20 002C0A00  C0 1D 00 14 */	lfs f0, 0x14(r29)
/* 802C3E24 002C0A04  D0 1E 0D F0 */	stfs f0, 0xdf0(r30)
/* 802C3E28 002C0A08  4B D9 BF B5 */	bl efSync_Spawn
/* 802C3E2C 002C0A0C  38 00 00 01 */	li r0, 1
/* 802C3E30 002C0A10  90 1E 0D F4 */	stw r0, 0xdf4(r30)
/* 802C3E34 002C0A14  C0 3E 0D EC */	lfs f1, 0xdec(r30)
/* 802C3E38 002C0A18  C0 1E 0D E8 */	lfs f0, 0xde8(r30)
/* 802C3E3C 002C0A1C  EC 21 00 2A */	fadds f1, f1, f0
/* 802C3E40 002C0A20  48 06 24 01 */	bl cosf
/* 802C3E44 002C0A24  C0 1E 0D F0 */	lfs f0, 0xdf0(r30)
/* 802C3E48 002C0A28  EC 00 00 72 */	fmuls f0, f0, f1
/* 802C3E4C 002C0A2C  D0 1E 00 40 */	stfs f0, 0x40(r30)
/* 802C3E50 002C0A30  C0 3E 0D EC */	lfs f1, 0xdec(r30)
/* 802C3E54 002C0A34  C0 1E 0D E8 */	lfs f0, 0xde8(r30)
/* 802C3E58 002C0A38  EC 21 00 2A */	fadds f1, f1, f0
/* 802C3E5C 002C0A3C  48 06 25 79 */	bl sinf
/* 802C3E60 002C0A40  C0 1E 0D F0 */	lfs f0, 0xdf0(r30)
/* 802C3E64 002C0A44  7F 63 DB 78 */	mr r3, r27
/* 802C3E68 002C0A48  EC 00 00 72 */	fmuls f0, f0, f1
/* 802C3E6C 002C0A4C  D0 1E 00 44 */	stfs f0, 0x44(r30)
/* 802C3E70 002C0A50  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C3E74 002C0A54  D0 1E 00 48 */	stfs f0, 0x48(r30)
/* 802C3E78 002C0A58  80 9E 05 18 */	lwz r4, 0x518(r30)
/* 802C3E7C 002C0A5C  4B F6 1F 5D */	bl db_80225DD8
/* 802C3E80 002C0A60  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 802C3E84 002C0A64  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802C3E88 002C0A68  38 21 00 30 */	addi r1, r1, 0x30
/* 802C3E8C 002C0A6C  7C 08 03 A6 */	mtlr r0
/* 802C3E90 002C0A70  4E 80 00 20 */	blr

.global it_802C3E94
it_802C3E94:
/* 802C3E94 002C0A74  7C 08 02 A6 */	mflr r0
/* 802C3E98 002C0A78  90 01 00 04 */	stw r0, 4(r1)
/* 802C3E9C 002C0A7C  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 802C3EA0 002C0A80  BF 21 00 34 */	stmw r25, 0x34(r1)
/* 802C3EA4 002C0A84  7C 7E 1B 78 */	mr r30, r3
/* 802C3EA8 002C0A88  83 43 00 2C */	lwz r26, 0x2c(r3)
/* 802C3EAC 002C0A8C  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 802C3EB0 002C0A90  80 1A 0D DC */	lwz r0, 0xddc(r26)
/* 802C3EB4 002C0A94  80 7A 00 C4 */	lwz r3, 0xc4(r26)
/* 802C3EB8 002C0A98  2C 00 00 00 */	cmpwi r0, 0
/* 802C3EBC 002C0A9C  83 23 00 04 */	lwz r25, 4(r3)
/* 802C3EC0 002C0AA0  40 82 00 B0 */	bne .L_802C3F70
/* 802C3EC4 002C0AA4  C0 3A 0D D8 */	lfs f1, 0xdd8(r26)
/* 802C3EC8 002C0AA8  C0 02 D8 3C */	lfs f0, it_804DD21C@sda21(r2)
/* 802C3ECC 002C0AAC  EC 01 00 2A */	fadds f0, f1, f0
/* 802C3ED0 002C0AB0  D0 1A 0D D8 */	stfs f0, 0xdd8(r26)
/* 802C3ED4 002C0AB4  C0 1A 0D D8 */	lfs f0, 0xdd8(r26)
/* 802C3ED8 002C0AB8  C0 39 00 04 */	lfs f1, 4(r25)
/* 802C3EDC 002C0ABC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 802C3EE0 002C0AC0  4C 41 13 82 */	cror 2, 1, 2
/* 802C3EE4 002C0AC4  40 82 00 08 */	bne .L_802C3EEC
/* 802C3EE8 002C0AC8  D0 3A 0D D8 */	stfs f1, 0xdd8(r26)
.L_802C3EEC:
/* 802C3EEC 002C0ACC  80 7A 0D E0 */	lwz r3, 0xde0(r26)
/* 802C3EF0 002C0AD0  28 03 00 00 */	cmplwi r3, 0
/* 802C3EF4 002C0AD4  41 82 00 7C */	beq .L_802C3F70
/* 802C3EF8 002C0AD8  80 1A 05 18 */	lwz r0, 0x518(r26)
/* 802C3EFC 002C0ADC  7C 00 18 40 */	cmplw r0, r3
/* 802C3F00 002C0AE0  40 82 00 70 */	bne .L_802C3F70
/* 802C3F04 002C0AE4  4B E7 76 71 */	bl ftZd_SpecialLw_8013B574
/* 802C3F08 002C0AE8  2C 03 00 01 */	cmpwi r3, 1
/* 802C3F0C 002C0AEC  40 82 00 64 */	bne .L_802C3F70
/* 802C3F10 002C0AF0  83 7E 00 2C */	lwz r27, 0x2c(r30)
/* 802C3F14 002C0AF4  83 BE 00 28 */	lwz r29, 0x28(r30)
/* 802C3F18 002C0AF8  80 1B 0D F4 */	lwz r0, 0xdf4(r27)
/* 802C3F1C 002C0AFC  80 7B 00 C4 */	lwz r3, 0xc4(r27)
/* 802C3F20 002C0B00  28 00 00 00 */	cmplwi r0, 0
/* 802C3F24 002C0B04  83 83 00 04 */	lwz r28, 4(r3)
/* 802C3F28 002C0B08  41 82 00 14 */	beq .L_802C3F3C
/* 802C3F2C 002C0B0C  7F C3 F3 78 */	mr r3, r30
/* 802C3F30 002C0B10  4B D9 79 51 */	bl efLib_DestroyAll
/* 802C3F34 002C0B14  38 00 00 00 */	li r0, 0
/* 802C3F38 002C0B18  90 1B 0D F4 */	stw r0, 0xdf4(r27)
.L_802C3F3C:
/* 802C3F3C 002C0B1C  38 7E 00 00 */	addi r3, r30, 0
/* 802C3F40 002C0B20  38 80 00 01 */	li r4, 1
/* 802C3F44 002C0B24  38 A0 00 02 */	li r5, 2
/* 802C3F48 002C0B28  4B FA 4F 15 */	bl Item_80268E5C
/* 802C3F4C 002C0B2C  38 9E 00 00 */	addi r4, r30, 0
/* 802C3F50 002C0B30  4C C6 31 82 */	crclr 6
/* 802C3F54 002C0B34  38 BD 00 00 */	addi r5, r29, 0
/* 802C3F58 002C0B38  38 60 04 F9 */	li r3, 0x4f9
/* 802C3F5C 002C0B3C  4B D9 BE 81 */	bl efSync_Spawn
/* 802C3F60 002C0B40  38 00 00 01 */	li r0, 1
/* 802C3F64 002C0B44  90 1B 0D F4 */	stw r0, 0xdf4(r27)
/* 802C3F68 002C0B48  C0 1C 00 2C */	lfs f0, 0x2c(r28)
/* 802C3F6C 002C0B4C  D0 1B 0D 44 */	stfs f0, 0xd44(r27)
.L_802C3F70:
/* 802C3F70 002C0B50  C0 79 00 08 */	lfs f3, 8(r25)
/* 802C3F74 002C0B54  28 1F 00 00 */	cmplwi r31, 0
/* 802C3F78 002C0B58  C0 39 00 0C */	lfs f1, 0xc(r25)
/* 802C3F7C 002C0B5C  C0 19 00 04 */	lfs f0, 4(r25)
/* 802C3F80 002C0B60  EC 21 18 28 */	fsubs f1, f1, f3
/* 802C3F84 002C0B64  C0 5A 0D D8 */	lfs f2, 0xdd8(r26)
/* 802C3F88 002C0B68  EC 01 00 24 */	fdivs f0, f1, f0
/* 802C3F8C 002C0B6C  EC 02 18 3A */	fmadds f0, f2, f0, f3
/* 802C3F90 002C0B70  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 802C3F94 002C0B74  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 802C3F98 002C0B78  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 802C3F9C 002C0B7C  40 82 00 14 */	bne .L_802C3FB0
/* 802C3FA0 002C0B80  38 6D 9E B0 */	addi r3, r13, it_804D5550@sda21
/* 802C3FA4 002C0B84  38 80 02 F8 */	li r4, 0x2f8
/* 802C3FA8 002C0B88  38 AD 9E B8 */	addi r5, r13, it_804D5558@sda21
/* 802C3FAC 002C0B8C  48 0C 42 75 */	bl __assert
.L_802C3FB0:
/* 802C3FB0 002C0B90  80 61 00 24 */	lwz r3, 0x24(r1)
/* 802C3FB4 002C0B94  80 01 00 28 */	lwz r0, 0x28(r1)
/* 802C3FB8 002C0B98  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 802C3FBC 002C0B9C  90 1F 00 30 */	stw r0, 0x30(r31)
/* 802C3FC0 002C0BA0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802C3FC4 002C0BA4  90 1F 00 34 */	stw r0, 0x34(r31)
/* 802C3FC8 002C0BA8  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 802C3FCC 002C0BAC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802C3FD0 002C0BB0  40 82 00 4C */	bne .L_802C401C
/* 802C3FD4 002C0BB4  28 1F 00 00 */	cmplwi r31, 0
/* 802C3FD8 002C0BB8  41 82 00 44 */	beq .L_802C401C
/* 802C3FDC 002C0BBC  40 82 00 14 */	bne .L_802C3FF0
/* 802C3FE0 002C0BC0  38 6D 9E B0 */	addi r3, r13, it_804D5550@sda21
/* 802C3FE4 002C0BC4  38 80 02 34 */	li r4, 0x234
/* 802C3FE8 002C0BC8  38 AD 9E B8 */	addi r5, r13, it_804D5558@sda21
/* 802C3FEC 002C0BCC  48 0C 42 35 */	bl __assert
.L_802C3FF0:
/* 802C3FF0 002C0BD0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802C3FF4 002C0BD4  38 60 00 00 */	li r3, 0
/* 802C3FF8 002C0BD8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802C3FFC 002C0BDC  40 82 00 10 */	bne .L_802C400C
/* 802C4000 002C0BE0  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802C4004 002C0BE4  41 82 00 08 */	beq .L_802C400C
/* 802C4008 002C0BE8  38 60 00 01 */	li r3, 1
.L_802C400C:
/* 802C400C 002C0BEC  2C 03 00 00 */	cmpwi r3, 0
/* 802C4010 002C0BF0  40 82 00 0C */	bne .L_802C401C
/* 802C4014 002C0BF4  7F E3 FB 78 */	mr r3, r31
/* 802C4018 002C0BF8  48 0A F2 D1 */	bl HSD_JObjSetMtxDirtySub
.L_802C401C:
/* 802C401C 002C0BFC  7F C3 F3 78 */	mr r3, r30
/* 802C4020 002C0C00  4B FA F1 11 */	bl it_80273130
/* 802C4024 002C0C04  2C 03 00 01 */	cmpwi r3, 1
/* 802C4028 002C0C08  40 82 00 64 */	bne .L_802C408C
/* 802C402C 002C0C0C  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 802C4030 002C0C10  83 7E 00 28 */	lwz r27, 0x28(r30)
/* 802C4034 002C0C14  80 1D 0D F4 */	lwz r0, 0xdf4(r29)
/* 802C4038 002C0C18  80 7D 00 C4 */	lwz r3, 0xc4(r29)
/* 802C403C 002C0C1C  28 00 00 00 */	cmplwi r0, 0
/* 802C4040 002C0C20  83 83 00 04 */	lwz r28, 4(r3)
/* 802C4044 002C0C24  41 82 00 14 */	beq .L_802C4058
/* 802C4048 002C0C28  7F C3 F3 78 */	mr r3, r30
/* 802C404C 002C0C2C  4B D9 78 35 */	bl efLib_DestroyAll
/* 802C4050 002C0C30  38 00 00 00 */	li r0, 0
/* 802C4054 002C0C34  90 1D 0D F4 */	stw r0, 0xdf4(r29)
.L_802C4058:
/* 802C4058 002C0C38  38 7E 00 00 */	addi r3, r30, 0
/* 802C405C 002C0C3C  38 80 00 01 */	li r4, 1
/* 802C4060 002C0C40  38 A0 00 02 */	li r5, 2
/* 802C4064 002C0C44  4B FA 4D F9 */	bl Item_80268E5C
/* 802C4068 002C0C48  38 9E 00 00 */	addi r4, r30, 0
/* 802C406C 002C0C4C  4C C6 31 82 */	crclr 6
/* 802C4070 002C0C50  38 BB 00 00 */	addi r5, r27, 0
/* 802C4074 002C0C54  38 60 04 F9 */	li r3, 0x4f9
/* 802C4078 002C0C58  4B D9 BD 65 */	bl efSync_Spawn
/* 802C407C 002C0C5C  38 00 00 01 */	li r0, 1
/* 802C4080 002C0C60  90 1D 0D F4 */	stw r0, 0xdf4(r29)
/* 802C4084 002C0C64  C0 1C 00 2C */	lfs f0, 0x2c(r28)
/* 802C4088 002C0C68  D0 1D 0D 44 */	stfs f0, 0xd44(r29)
.L_802C408C:
/* 802C408C 002C0C6C  BB 21 00 34 */	lmw r25, 0x34(r1)
/* 802C4090 002C0C70  38 60 00 00 */	li r3, 0
/* 802C4094 002C0C74  80 01 00 54 */	lwz r0, 0x54(r1)
/* 802C4098 002C0C78  38 21 00 50 */	addi r1, r1, 0x50
/* 802C409C 002C0C7C  7C 08 03 A6 */	mtlr r0
/* 802C40A0 002C0C80  4E 80 00 20 */	blr

.global it_802C40A4
it_802C40A4:
/* 802C40A4 002C0C84  7C 08 02 A6 */	mflr r0
/* 802C40A8 002C0C88  90 01 00 04 */	stw r0, 4(r1)
/* 802C40AC 002C0C8C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802C40B0 002C0C90  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802C40B4 002C0C94  7C 7F 1B 78 */	mr r31, r3
/* 802C40B8 002C0C98  93 C1 00 28 */	stw r30, 0x28(r1)
/* 802C40BC 002C0C9C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 802C40C0 002C0CA0  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 802C40C4 002C0CA4  80 03 00 28 */	lwz r0, 0x28(r3)
/* 802C40C8 002C0CA8  80 7E 00 C4 */	lwz r3, 0xc4(r30)
/* 802C40CC 002C0CAC  C0 5E 0D D8 */	lfs f2, 0xdd8(r30)
/* 802C40D0 002C0CB0  28 00 00 00 */	cmplwi r0, 0
/* 802C40D4 002C0CB4  80 63 00 04 */	lwz r3, 4(r3)
/* 802C40D8 002C0CB8  7C 1D 03 78 */	mr r29, r0
/* 802C40DC 002C0CBC  C0 63 00 08 */	lfs f3, 8(r3)
/* 802C40E0 002C0CC0  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 802C40E4 002C0CC4  C0 03 00 04 */	lfs f0, 4(r3)
/* 802C40E8 002C0CC8  EC 21 18 28 */	fsubs f1, f1, f3
/* 802C40EC 002C0CCC  EC 01 00 24 */	fdivs f0, f1, f0
/* 802C40F0 002C0CD0  EC 02 18 3A */	fmadds f0, f2, f0, f3
/* 802C40F4 002C0CD4  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 802C40F8 002C0CD8  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 802C40FC 002C0CDC  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 802C4100 002C0CE0  40 82 00 14 */	bne .L_802C4114
/* 802C4104 002C0CE4  38 6D 9E B0 */	addi r3, r13, it_804D5550@sda21
/* 802C4108 002C0CE8  38 80 02 F8 */	li r4, 0x2f8
/* 802C410C 002C0CEC  38 AD 9E B8 */	addi r5, r13, it_804D5558@sda21
/* 802C4110 002C0CF0  48 0C 41 11 */	bl __assert
.L_802C4114:
/* 802C4114 002C0CF4  80 61 00 14 */	lwz r3, 0x14(r1)
/* 802C4118 002C0CF8  80 01 00 18 */	lwz r0, 0x18(r1)
/* 802C411C 002C0CFC  90 7D 00 2C */	stw r3, 0x2c(r29)
/* 802C4120 002C0D00  90 1D 00 30 */	stw r0, 0x30(r29)
/* 802C4124 002C0D04  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802C4128 002C0D08  90 1D 00 34 */	stw r0, 0x34(r29)
/* 802C412C 002C0D0C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 802C4130 002C0D10  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802C4134 002C0D14  40 82 00 4C */	bne .L_802C4180
/* 802C4138 002C0D18  28 1D 00 00 */	cmplwi r29, 0
/* 802C413C 002C0D1C  41 82 00 44 */	beq .L_802C4180
/* 802C4140 002C0D20  40 82 00 14 */	bne .L_802C4154
/* 802C4144 002C0D24  38 6D 9E B0 */	addi r3, r13, it_804D5550@sda21
/* 802C4148 002C0D28  38 80 02 34 */	li r4, 0x234
/* 802C414C 002C0D2C  38 AD 9E B8 */	addi r5, r13, it_804D5558@sda21
/* 802C4150 002C0D30  48 0C 40 D1 */	bl __assert
.L_802C4154:
/* 802C4154 002C0D34  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 802C4158 002C0D38  38 60 00 00 */	li r3, 0
/* 802C415C 002C0D3C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802C4160 002C0D40  40 82 00 10 */	bne .L_802C4170
/* 802C4164 002C0D44  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802C4168 002C0D48  41 82 00 08 */	beq .L_802C4170
/* 802C416C 002C0D4C  38 60 00 01 */	li r3, 1
.L_802C4170:
/* 802C4170 002C0D50  2C 03 00 00 */	cmpwi r3, 0
/* 802C4174 002C0D54  40 82 00 0C */	bne .L_802C4180
/* 802C4178 002C0D58  7F A3 EB 78 */	mr r3, r29
/* 802C417C 002C0D5C  48 0A F1 6D */	bl HSD_JObjSetMtxDirtySub
.L_802C4180:
/* 802C4180 002C0D60  7F E3 FB 78 */	mr r3, r31
/* 802C4184 002C0D64  4B FA EF AD */	bl it_80273130
/* 802C4188 002C0D68  2C 03 00 01 */	cmpwi r3, 1
/* 802C418C 002C0D6C  40 82 00 5C */	bne .L_802C41E8
/* 802C4190 002C0D70  80 1E 0D F4 */	lwz r0, 0xdf4(r30)
/* 802C4194 002C0D74  28 00 00 00 */	cmplwi r0, 0
/* 802C4198 002C0D78  41 82 00 14 */	beq .L_802C41AC
/* 802C419C 002C0D7C  7F E3 FB 78 */	mr r3, r31
/* 802C41A0 002C0D80  4B D9 76 E1 */	bl efLib_DestroyAll
/* 802C41A4 002C0D84  38 00 00 00 */	li r0, 0
/* 802C41A8 002C0D88  90 1E 0D F4 */	stw r0, 0xdf4(r30)
.L_802C41AC:
/* 802C41AC 002C0D8C  80 1E 0D E0 */	lwz r0, 0xde0(r30)
/* 802C41B0 002C0D90  28 00 00 00 */	cmplwi r0, 0
/* 802C41B4 002C0D94  41 82 00 2C */	beq .L_802C41E0
/* 802C41B8 002C0D98  80 7E 05 18 */	lwz r3, 0x518(r30)
/* 802C41BC 002C0D9C  7C 00 18 40 */	cmplw r0, r3
/* 802C41C0 002C0DA0  40 82 00 20 */	bne .L_802C41E0
/* 802C41C4 002C0DA4  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 802C41C8 002C0DA8  38 9F 00 00 */	addi r4, r31, 0
/* 802C41CC 002C0DAC  C0 5E 0D D8 */	lfs f2, 0xdd8(r30)
/* 802C41D0 002C0DB0  38 BE 00 4C */	addi r5, r30, 0x4c
/* 802C41D4 002C0DB4  48 00 03 AD */	bl it_802C4580
/* 802C41D8 002C0DB8  80 7E 0D E0 */	lwz r3, 0xde0(r30)
/* 802C41DC 002C0DBC  4B E7 73 E9 */	bl ftZd_SpecialLw_8013B5C4
.L_802C41E0:
/* 802C41E0 002C0DC0  38 60 00 01 */	li r3, 1
/* 802C41E4 002C0DC4  48 00 00 08 */	b .L_802C41EC
.L_802C41E8:
/* 802C41E8 002C0DC8  38 60 00 00 */	li r3, 0
.L_802C41EC:
/* 802C41EC 002C0DCC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802C41F0 002C0DD0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802C41F4 002C0DD4  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 802C41F8 002C0DD8  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 802C41FC 002C0DDC  38 21 00 30 */	addi r1, r1, 0x30
/* 802C4200 002C0DE0  7C 08 03 A6 */	mtlr r0
/* 802C4204 002C0DE4  4E 80 00 20 */	blr

.global it_802C4208
it_802C4208:
/* 802C4208 002C0DE8  7C 08 02 A6 */	mflr r0
/* 802C420C 002C0DEC  90 01 00 04 */	stw r0, 4(r1)
/* 802C4210 002C0DF0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802C4214 002C0DF4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802C4218 002C0DF8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 802C421C 002C0DFC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802C4220 002C0E00  80 1F 0D DC */	lwz r0, 0xddc(r31)
/* 802C4224 002C0E04  80 7F 00 C4 */	lwz r3, 0xc4(r31)
/* 802C4228 002C0E08  2C 00 00 00 */	cmpwi r0, 0
/* 802C422C 002C0E0C  83 C3 00 04 */	lwz r30, 4(r3)
/* 802C4230 002C0E10  40 82 01 1C */	bne .L_802C434C
/* 802C4234 002C0E14  80 7F 0D E0 */	lwz r3, 0xde0(r31)
/* 802C4238 002C0E18  28 03 00 00 */	cmplwi r3, 0
/* 802C423C 002C0E1C  41 82 01 10 */	beq .L_802C434C
/* 802C4240 002C0E20  80 1F 05 18 */	lwz r0, 0x518(r31)
/* 802C4244 002C0E24  7C 00 18 40 */	cmplw r0, r3
/* 802C4248 002C0E28  40 82 01 04 */	bne .L_802C434C
/* 802C424C 002C0E2C  4B E7 72 F5 */	bl ftZd_SpecialLw_8013B540
/* 802C4250 002C0E30  2C 03 00 01 */	cmpwi r3, 1
/* 802C4254 002C0E34  40 82 00 F8 */	bne .L_802C434C
/* 802C4258 002C0E38  80 7F 0D E0 */	lwz r3, 0xde0(r31)
/* 802C425C 002C0E3C  38 A1 00 14 */	addi r5, r1, 0x14
/* 802C4260 002C0E40  38 81 00 10 */	addi r4, r1, 0x10
/* 802C4264 002C0E44  4B DC 23 75 */	bl ftLib_800865D8
/* 802C4268 002C0E48  C0 61 00 14 */	lfs f3, 0x14(r1)
/* 802C426C 002C0E4C  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C4270 002C0E50  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 802C4274 002C0E54  40 80 00 0C */	bge .L_802C4280
/* 802C4278 002C0E58  FC 20 18 50 */	fneg f1, f3
/* 802C427C 002C0E5C  48 00 00 08 */	b .L_802C4284
.L_802C4280:
/* 802C4280 002C0E60  FC 20 18 90 */	fmr f1, f3
.L_802C4284:
/* 802C4284 002C0E64  C0 1E 00 20 */	lfs f0, 0x20(r30)
/* 802C4288 002C0E68  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802C428C 002C0E6C  40 81 00 5C */	ble .L_802C42E8
/* 802C4290 002C0E70  C0 1E 00 24 */	lfs f0, 0x24(r30)
/* 802C4294 002C0E74  C0 5F 00 2C */	lfs f2, 0x2c(r31)
/* 802C4298 002C0E78  EC 20 00 F2 */	fmuls f1, f0, f3
/* 802C429C 002C0E7C  C0 1F 0D E8 */	lfs f0, 0xde8(r31)
/* 802C42A0 002C0E80  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 802C42A4 002C0E84  D0 1F 0D E8 */	stfs f0, 0xde8(r31)
/* 802C42A8 002C0E88  C0 3F 0D E8 */	lfs f1, 0xde8(r31)
/* 802C42AC 002C0E8C  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C42B0 002C0E90  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802C42B4 002C0E94  40 80 00 0C */	bge .L_802C42C0
/* 802C42B8 002C0E98  FC 00 08 50 */	fneg f0, f1
/* 802C42BC 002C0E9C  48 00 00 08 */	b .L_802C42C4
.L_802C42C0:
/* 802C42C0 002C0EA0  FC 00 08 90 */	fmr f0, f1
.L_802C42C4:
/* 802C42C4 002C0EA4  C0 5E 00 28 */	lfs f2, 0x28(r30)
/* 802C42C8 002C0EA8  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 802C42CC 002C0EAC  40 81 00 1C */	ble .L_802C42E8
/* 802C42D0 002C0EB0  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C42D4 002C0EB4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 802C42D8 002C0EB8  40 81 00 08 */	ble .L_802C42E0
/* 802C42DC 002C0EBC  48 00 00 08 */	b .L_802C42E4
.L_802C42E0:
/* 802C42E0 002C0EC0  FC 40 10 50 */	fneg f2, f2
.L_802C42E4:
/* 802C42E4 002C0EC4  D0 5F 0D E8 */	stfs f2, 0xde8(r31)
.L_802C42E8:
/* 802C42E8 002C0EC8  C0 3F 0D F0 */	lfs f1, 0xdf0(r31)
/* 802C42EC 002C0ECC  C0 1E 00 18 */	lfs f0, 0x18(r30)
/* 802C42F0 002C0ED0  EC 01 00 2A */	fadds f0, f1, f0
/* 802C42F4 002C0ED4  D0 1F 0D F0 */	stfs f0, 0xdf0(r31)
/* 802C42F8 002C0ED8  C0 1F 0D F0 */	lfs f0, 0xdf0(r31)
/* 802C42FC 002C0EDC  C0 3E 00 1C */	lfs f1, 0x1c(r30)
/* 802C4300 002C0EE0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 802C4304 002C0EE4  40 81 00 08 */	ble .L_802C430C
/* 802C4308 002C0EE8  D0 3F 0D F0 */	stfs f1, 0xdf0(r31)
.L_802C430C:
/* 802C430C 002C0EEC  C0 3F 0D EC */	lfs f1, 0xdec(r31)
/* 802C4310 002C0EF0  C0 1F 0D E8 */	lfs f0, 0xde8(r31)
/* 802C4314 002C0EF4  EC 21 00 2A */	fadds f1, f1, f0
/* 802C4318 002C0EF8  48 06 1F 29 */	bl cosf
/* 802C431C 002C0EFC  C0 1F 0D F0 */	lfs f0, 0xdf0(r31)
/* 802C4320 002C0F00  EC 00 00 72 */	fmuls f0, f0, f1
/* 802C4324 002C0F04  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 802C4328 002C0F08  C0 3F 0D EC */	lfs f1, 0xdec(r31)
/* 802C432C 002C0F0C  C0 1F 0D E8 */	lfs f0, 0xde8(r31)
/* 802C4330 002C0F10  EC 21 00 2A */	fadds f1, f1, f0
/* 802C4334 002C0F14  48 06 20 A1 */	bl sinf
/* 802C4338 002C0F18  C0 1F 0D F0 */	lfs f0, 0xdf0(r31)
/* 802C433C 002C0F1C  EC 00 00 72 */	fmuls f0, f0, f1
/* 802C4340 002C0F20  D0 1F 00 44 */	stfs f0, 0x44(r31)
/* 802C4344 002C0F24  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C4348 002C0F28  D0 1F 00 48 */	stfs f0, 0x48(r31)
.L_802C434C:
/* 802C434C 002C0F2C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802C4350 002C0F30  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802C4354 002C0F34  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802C4358 002C0F38  38 21 00 28 */	addi r1, r1, 0x28
/* 802C435C 002C0F3C  7C 08 03 A6 */	mtlr r0
/* 802C4360 002C0F40  4E 80 00 20 */	blr

.global it_802C4364
it_802C4364:
/* 802C4364 002C0F44  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C4368 002C0F48  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C436C 002C0F4C  D0 03 00 48 */	stfs f0, 0x48(r3)
/* 802C4370 002C0F50  D0 03 00 44 */	stfs f0, 0x44(r3)
/* 802C4374 002C0F54  D0 03 00 40 */	stfs f0, 0x40(r3)
/* 802C4378 002C0F58  4E 80 00 20 */	blr

.global it_802C437C
it_802C437C:
/* 802C437C 002C0F5C  7C 08 02 A6 */	mflr r0
/* 802C4380 002C0F60  90 01 00 04 */	stw r0, 4(r1)
/* 802C4384 002C0F64  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802C4388 002C0F68  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802C438C 002C0F6C  93 C1 00 28 */	stw r30, 0x28(r1)
/* 802C4390 002C0F70  93 A1 00 24 */	stw r29, 0x24(r1)
/* 802C4394 002C0F74  93 81 00 20 */	stw r28, 0x20(r1)
/* 802C4398 002C0F78  7C 7C 1B 78 */	mr r28, r3
/* 802C439C 002C0F7C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802C43A0 002C0F80  38 84 03 78 */	addi r4, r4, 0x378
/* 802C43A4 002C0F84  4B FF F7 59 */	bl it_802C3AFC
/* 802C43A8 002C0F88  2C 03 00 00 */	cmpwi r3, 0
/* 802C43AC 002C0F8C  41 82 00 64 */	beq .L_802C4410
/* 802C43B0 002C0F90  83 BC 00 2C */	lwz r29, 0x2c(r28)
/* 802C43B4 002C0F94  83 FC 00 28 */	lwz r31, 0x28(r28)
/* 802C43B8 002C0F98  80 1D 0D F4 */	lwz r0, 0xdf4(r29)
/* 802C43BC 002C0F9C  80 7D 00 C4 */	lwz r3, 0xc4(r29)
/* 802C43C0 002C0FA0  28 00 00 00 */	cmplwi r0, 0
/* 802C43C4 002C0FA4  83 C3 00 04 */	lwz r30, 4(r3)
/* 802C43C8 002C0FA8  41 82 00 14 */	beq .L_802C43DC
/* 802C43CC 002C0FAC  7F 83 E3 78 */	mr r3, r28
/* 802C43D0 002C0FB0  4B D9 74 B1 */	bl efLib_DestroyAll
/* 802C43D4 002C0FB4  38 00 00 00 */	li r0, 0
/* 802C43D8 002C0FB8  90 1D 0D F4 */	stw r0, 0xdf4(r29)
.L_802C43DC:
/* 802C43DC 002C0FBC  38 7C 00 00 */	addi r3, r28, 0
/* 802C43E0 002C0FC0  38 80 00 01 */	li r4, 1
/* 802C43E4 002C0FC4  38 A0 00 02 */	li r5, 2
/* 802C43E8 002C0FC8  4B FA 4A 75 */	bl Item_80268E5C
/* 802C43EC 002C0FCC  38 9C 00 00 */	addi r4, r28, 0
/* 802C43F0 002C0FD0  4C C6 31 82 */	crclr 6
/* 802C43F4 002C0FD4  38 BF 00 00 */	addi r5, r31, 0
/* 802C43F8 002C0FD8  38 60 04 F9 */	li r3, 0x4f9
/* 802C43FC 002C0FDC  4B D9 B9 E1 */	bl efSync_Spawn
/* 802C4400 002C0FE0  38 00 00 01 */	li r0, 1
/* 802C4404 002C0FE4  90 1D 0D F4 */	stw r0, 0xdf4(r29)
/* 802C4408 002C0FE8  C0 1E 00 2C */	lfs f0, 0x2c(r30)
/* 802C440C 002C0FEC  D0 1D 0D 44 */	stfs f0, 0xd44(r29)
.L_802C4410:
/* 802C4410 002C0FF0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802C4414 002C0FF4  38 60 00 00 */	li r3, 0
/* 802C4418 002C0FF8  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802C441C 002C0FFC  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 802C4420 002C1000  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 802C4424 002C1004  83 81 00 20 */	lwz r28, 0x20(r1)
/* 802C4428 002C1008  38 21 00 30 */	addi r1, r1, 0x30
/* 802C442C 002C100C  7C 08 03 A6 */	mtlr r0
/* 802C4430 002C1010  4E 80 00 20 */	blr

.global it_802C4434
it_802C4434:
/* 802C4434 002C1014  38 60 00 00 */	li r3, 0
/* 802C4438 002C1018  4E 80 00 20 */	blr

.global it_802C443C
it_802C443C:
/* 802C443C 002C101C  7C 08 02 A6 */	mflr r0
/* 802C4440 002C1020  90 01 00 04 */	stw r0, 4(r1)
/* 802C4444 002C1024  38 00 00 01 */	li r0, 1
/* 802C4448 002C1028  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802C444C 002C102C  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 802C4450 002C1030  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802C4454 002C1034  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802C4458 002C1038  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 802C445C 002C103C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802C4460 002C1040  28 1E 00 00 */	cmplwi r30, 0
/* 802C4464 002C1044  90 1F 0D DC */	stw r0, 0xddc(r31)
/* 802C4468 002C1048  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 802C446C 002C104C  FC 00 00 50 */	fneg f0, f0
/* 802C4470 002C1050  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 802C4474 002C1054  C8 22 D8 50 */	lfd f1, it_804DD230@sda21(r2)
/* 802C4478 002C1058  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 802C447C 002C105C  FF E1 00 32 */	fmul f31, f1, f0
/* 802C4480 002C1060  FF E0 F8 18 */	frsp f31, f31
/* 802C4484 002C1064  40 82 00 14 */	bne .L_802C4498
/* 802C4488 002C1068  38 6D 9E B0 */	addi r3, r13, it_804D5550@sda21
/* 802C448C 002C106C  38 80 02 94 */	li r4, 0x294
/* 802C4490 002C1070  38 AD 9E B8 */	addi r5, r13, it_804D5558@sda21
/* 802C4494 002C1074  48 0C 3D 8D */	bl __assert
.L_802C4498:
/* 802C4498 002C1078  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802C449C 002C107C  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 802C44A0 002C1080  41 82 00 18 */	beq .L_802C44B8
/* 802C44A4 002C1084  3C 60 80 3F */	lis r3, it_803F7718@ha
/* 802C44A8 002C1088  38 A3 77 18 */	addi r5, r3, it_803F7718@l
/* 802C44AC 002C108C  38 6D 9E B0 */	addi r3, r13, it_804D5550@sda21
/* 802C44B0 002C1090  38 80 02 95 */	li r4, 0x295
/* 802C44B4 002C1094  48 0C 3D 6D */	bl __assert
.L_802C44B8:
/* 802C44B8 002C1098  D3 FE 00 20 */	stfs f31, 0x20(r30)
/* 802C44BC 002C109C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802C44C0 002C10A0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802C44C4 002C10A4  40 82 00 4C */	bne .L_802C4510
/* 802C44C8 002C10A8  28 1E 00 00 */	cmplwi r30, 0
/* 802C44CC 002C10AC  41 82 00 44 */	beq .L_802C4510
/* 802C44D0 002C10B0  40 82 00 14 */	bne .L_802C44E4
/* 802C44D4 002C10B4  38 6D 9E B0 */	addi r3, r13, it_804D5550@sda21
/* 802C44D8 002C10B8  38 80 02 34 */	li r4, 0x234
/* 802C44DC 002C10BC  38 AD 9E B8 */	addi r5, r13, it_804D5558@sda21
/* 802C44E0 002C10C0  48 0C 3D 41 */	bl __assert
.L_802C44E4:
/* 802C44E4 002C10C4  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802C44E8 002C10C8  38 60 00 00 */	li r3, 0
/* 802C44EC 002C10CC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802C44F0 002C10D0  40 82 00 10 */	bne .L_802C4500
/* 802C44F4 002C10D4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802C44F8 002C10D8  41 82 00 08 */	beq .L_802C4500
/* 802C44FC 002C10DC  38 60 00 01 */	li r3, 1
.L_802C4500:
/* 802C4500 002C10E0  2C 03 00 00 */	cmpwi r3, 0
/* 802C4504 002C10E4  40 82 00 0C */	bne .L_802C4510
/* 802C4508 002C10E8  7F C3 F3 78 */	mr r3, r30
/* 802C450C 002C10EC  48 0A ED DD */	bl HSD_JObjSetMtxDirtySub
.L_802C4510:
/* 802C4510 002C10F0  C0 1F 00 40 */	lfs f0, 0x40(r31)
/* 802C4514 002C10F4  38 60 00 00 */	li r3, 0
/* 802C4518 002C10F8  FC 00 00 50 */	fneg f0, f0
/* 802C451C 002C10FC  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 802C4520 002C1100  C0 1F 00 44 */	lfs f0, 0x44(r31)
/* 802C4524 002C1104  FC 00 00 50 */	fneg f0, f0
/* 802C4528 002C1108  D0 1F 00 44 */	stfs f0, 0x44(r31)
/* 802C452C 002C110C  C0 02 D8 38 */	lfs f0, it_804DD218@sda21(r2)
/* 802C4530 002C1110  D0 1F 00 48 */	stfs f0, 0x48(r31)
/* 802C4534 002C1114  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802C4538 002C1118  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 802C453C 002C111C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802C4540 002C1120  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802C4544 002C1124  38 21 00 28 */	addi r1, r1, 0x28
/* 802C4548 002C1128  7C 08 03 A6 */	mtlr r0
/* 802C454C 002C112C  4E 80 00 20 */	blr

.global it_802C4550
it_802C4550:
/* 802C4550 002C1130  38 60 00 01 */	li r3, 1
/* 802C4554 002C1134  4E 80 00 20 */	blr

.global it_802C4558
it_802C4558:
/* 802C4558 002C1138  38 60 00 01 */	li r3, 1
/* 802C455C 002C113C  4E 80 00 20 */	blr

.global it_802C4560
it_802C4560:
/* 802C4560 002C1140  7C 08 02 A6 */	mflr r0
/* 802C4564 002C1144  90 01 00 04 */	stw r0, 4(r1)
/* 802C4568 002C1148  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C456C 002C114C  4B FA 73 29 */	bl it_8026B894
/* 802C4570 002C1150  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C4574 002C1154  38 21 00 08 */	addi r1, r1, 8
/* 802C4578 002C1158  7C 08 03 A6 */	mtlr r0
/* 802C457C 002C115C  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F76F8
it_803F76F8:
    .4byte 0
    .4byte it_802C3E94
    .4byte it_802C4208
    .4byte it_802C437C
    .4byte 1
    .4byte it_802C40A4
    .4byte it_802C4364
    .4byte it_802C4434
.global it_803F7718
it_803F7718:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"


.section .sdata
    .balign 8
.global it_804D5550
it_804D5550:
    .asciz "jobj.h"
    .balign 4
.global it_804D5558
it_804D5558:
    .asciz "jobj"


.section .sdata2
    .balign 8
.global it_804DD218
it_804DD218:
    .4byte 0x00000000
.global it_804DD21C
it_804DD21C:
    .4byte 0x3F800000
.global it_804DD220
it_804DD220:
    .4byte 0x00000000
    .4byte 0x00000000
.global it_804DD228
it_804DD228:
    .4byte 0x400921FB
    .4byte 0x54442D18
.global it_804DD230
it_804DD230:
    .4byte 0x3FF921FB
    .4byte 0x54442D18
