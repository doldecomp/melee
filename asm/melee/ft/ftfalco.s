.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80149ACC
func_80149ACC:
/* 80149ACC 001466AC  7C 08 02 A6 */	mflr r0
/* 80149AD0 001466B0  38 A0 00 00 */	li r5, 0
/* 80149AD4 001466B4  90 01 00 04 */	stw r0, 4(r1)
/* 80149AD8 001466B8  38 00 00 00 */	li r0, 0
/* 80149ADC 001466BC  94 21 FF F8 */	stwu r1, -8(r1)
/* 80149AE0 001466C0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80149AE4 001466C4  90 04 22 2C */	stw r0, 0x222c(r4)
/* 80149AE8 001466C8  38 80 00 00 */	li r4, 0
/* 80149AEC 001466CC  4B F2 AF 61 */	bl func_80074A4C
/* 80149AF0 001466D0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80149AF4 001466D4  38 21 00 08 */	addi r1, r1, 8
/* 80149AF8 001466D8  7C 08 03 A6 */	mtlr r0
/* 80149AFC 001466DC  4E 80 00 20 */	blr 

.global func_80149B00
func_80149B00:
/* 80149B00 001466E0  7C 08 02 A6 */	mflr r0
/* 80149B04 001466E4  90 01 00 04 */	stw r0, 4(r1)
/* 80149B08 001466E8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80149B0C 001466EC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80149B10 001466F0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80149B14 001466F4  7C 9E 23 78 */	mr r30, r4
/* 80149B18 001466F8  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80149B1C 001466FC  7C 7D 1B 78 */	mr r29, r3
/* 80149B20 00146700  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80149B24 00146704  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80149B28 00146708  48 12 17 8D */	bl func_8026B2B4
/* 80149B2C 0014670C  2C 03 00 00 */	cmpwi r3, 0
/* 80149B30 00146710  40 82 00 94 */	bne lbl_80149BC4
/* 80149B34 00146714  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80149B38 00146718  48 12 17 E9 */	bl func_8026B320
/* 80149B3C 0014671C  2C 03 00 03 */	cmpwi r3, 3
/* 80149B40 00146720  41 82 00 4C */	beq lbl_80149B8C
/* 80149B44 00146724  40 80 00 14 */	bge lbl_80149B58
/* 80149B48 00146728  2C 03 00 01 */	cmpwi r3, 1
/* 80149B4C 0014672C  41 82 00 18 */	beq lbl_80149B64
/* 80149B50 00146730  40 80 00 28 */	bge lbl_80149B78
/* 80149B54 00146734  48 00 00 5C */	b lbl_80149BB0
lbl_80149B58:
/* 80149B58 00146738  2C 03 00 05 */	cmpwi r3, 5
/* 80149B5C 0014673C  40 80 00 54 */	bge lbl_80149BB0
/* 80149B60 00146740  48 00 00 40 */	b lbl_80149BA0
lbl_80149B64:
/* 80149B64 00146744  38 7D 00 00 */	addi r3, r29, 0
/* 80149B68 00146748  38 80 00 01 */	li r4, 1
/* 80149B6C 0014674C  38 A0 00 01 */	li r5, 1
/* 80149B70 00146750  4B F2 74 45 */	bl func_80070FB4
/* 80149B74 00146754  48 00 00 3C */	b lbl_80149BB0
lbl_80149B78:
/* 80149B78 00146758  38 7D 00 00 */	addi r3, r29, 0
/* 80149B7C 0014675C  38 80 00 01 */	li r4, 1
/* 80149B80 00146760  38 A0 00 00 */	li r5, 0
/* 80149B84 00146764  4B F2 74 31 */	bl func_80070FB4
/* 80149B88 00146768  48 00 00 28 */	b lbl_80149BB0
lbl_80149B8C:
/* 80149B8C 0014676C  38 7D 00 00 */	addi r3, r29, 0
/* 80149B90 00146770  38 80 00 01 */	li r4, 1
/* 80149B94 00146774  38 A0 00 02 */	li r5, 2
/* 80149B98 00146778  4B F2 74 1D */	bl func_80070FB4
/* 80149B9C 0014677C  48 00 00 14 */	b lbl_80149BB0
lbl_80149BA0:
/* 80149BA0 00146780  38 7D 00 00 */	addi r3, r29, 0
/* 80149BA4 00146784  38 80 00 01 */	li r4, 1
/* 80149BA8 00146788  38 A0 00 03 */	li r5, 3
/* 80149BAC 0014678C  4B F2 74 09 */	bl func_80070FB4
lbl_80149BB0:
/* 80149BB0 00146790  2C 1E 00 00 */	cmpwi r30, 0
/* 80149BB4 00146794  41 82 00 10 */	beq lbl_80149BC4
/* 80149BB8 00146798  38 7D 00 00 */	addi r3, r29, 0
/* 80149BBC 0014679C  38 80 00 01 */	li r4, 1
/* 80149BC0 001467A0  4B F2 70 89 */	bl func_80070C48
lbl_80149BC4:
/* 80149BC4 001467A4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80149BC8 001467A8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80149BCC 001467AC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80149BD0 001467B0  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80149BD4 001467B4  38 21 00 28 */	addi r1, r1, 0x28
/* 80149BD8 001467B8  7C 08 03 A6 */	mtlr r0
/* 80149BDC 001467BC  4E 80 00 20 */	blr 

.global func_80149BE0
func_80149BE0:
/* 80149BE0 001467C0  7C 08 02 A6 */	mflr r0
/* 80149BE4 001467C4  90 01 00 04 */	stw r0, 4(r1)
/* 80149BE8 001467C8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80149BEC 001467CC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80149BF0 001467D0  7C 7F 1B 78 */	mr r31, r3
/* 80149BF4 001467D4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80149BF8 001467D8  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 80149BFC 001467DC  48 12 16 B9 */	bl func_8026B2B4
/* 80149C00 001467E0  2C 03 00 00 */	cmpwi r3, 0
/* 80149C04 001467E4  40 82 00 10 */	bne lbl_80149C14
/* 80149C08 001467E8  38 7F 00 00 */	addi r3, r31, 0
/* 80149C0C 001467EC  38 80 00 01 */	li r4, 1
/* 80149C10 001467F0  4B F2 70 B5 */	bl func_80070CC4
lbl_80149C14:
/* 80149C14 001467F4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80149C18 001467F8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80149C1C 001467FC  38 21 00 18 */	addi r1, r1, 0x18
/* 80149C20 00146800  7C 08 03 A6 */	mtlr r0
/* 80149C24 00146804  4E 80 00 20 */	blr 

.global func_80149C28
func_80149C28:
/* 80149C28 00146808  7C 08 02 A6 */	mflr r0
/* 80149C2C 0014680C  90 01 00 04 */	stw r0, 4(r1)
/* 80149C30 00146810  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80149C34 00146814  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80149C38 00146818  7C 7F 1B 78 */	mr r31, r3
/* 80149C3C 0014681C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80149C40 00146820  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 80149C44 00146824  48 12 16 71 */	bl func_8026B2B4
/* 80149C48 00146828  2C 03 00 00 */	cmpwi r3, 0
/* 80149C4C 0014682C  40 82 00 10 */	bne lbl_80149C5C
/* 80149C50 00146830  38 7F 00 00 */	addi r3, r31, 0
/* 80149C54 00146834  38 80 00 01 */	li r4, 1
/* 80149C58 00146838  4B F2 6F F1 */	bl func_80070C48
lbl_80149C5C:
/* 80149C5C 0014683C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80149C60 00146840  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80149C64 00146844  38 21 00 18 */	addi r1, r1, 0x18
/* 80149C68 00146848  7C 08 03 A6 */	mtlr r0
/* 80149C6C 0014684C  4E 80 00 20 */	blr 

.global func_80149C70
func_80149C70:
/* 80149C70 00146850  7C 08 02 A6 */	mflr r0
/* 80149C74 00146854  38 A0 FF FF */	li r5, -1
/* 80149C78 00146858  90 01 00 04 */	stw r0, 4(r1)
/* 80149C7C 0014685C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80149C80 00146860  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80149C84 00146864  3B E4 00 00 */	addi r31, r4, 0
/* 80149C88 00146868  38 80 00 01 */	li r4, 1
/* 80149C8C 0014686C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80149C90 00146870  3B C3 00 00 */	addi r30, r3, 0
/* 80149C94 00146874  4B F2 73 21 */	bl func_80070FB4
/* 80149C98 00146878  2C 1F 00 00 */	cmpwi r31, 0
/* 80149C9C 0014687C  41 82 00 10 */	beq lbl_80149CAC
/* 80149CA0 00146880  38 7E 00 00 */	addi r3, r30, 0
/* 80149CA4 00146884  38 80 00 01 */	li r4, 1
/* 80149CA8 00146888  4B F2 70 1D */	bl func_80070CC4
lbl_80149CAC:
/* 80149CAC 0014688C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80149CB0 00146890  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80149CB4 00146894  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80149CB8 00146898  38 21 00 18 */	addi r1, r1, 0x18
/* 80149CBC 0014689C  7C 08 03 A6 */	mtlr r0
/* 80149CC0 001468A0  4E 80 00 20 */	blr 

.global ftFalco_OnLoad
ftFalco_OnLoad:
/* 80149CC4 001468A4  7C 08 02 A6 */	mflr r0
/* 80149CC8 001468A8  38 80 00 01 */	li r4, 1
/* 80149CCC 001468AC  90 01 00 04 */	stw r0, 4(r1)
/* 80149CD0 001468B0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80149CD4 001468B4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80149CD8 001468B8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80149CDC 001468BC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80149CE0 001468C0  80 BF 01 0C */	lwz r5, 0x10c(r31)
/* 80149CE4 001468C4  7F E3 FB 78 */	mr r3, r31
/* 80149CE8 001468C8  88 1F 22 24 */	lbz r0, 0x2224(r31)
/* 80149CEC 001468CC  50 80 07 FE */	rlwimi r0, r4, 0, 0x1f, 0x1f
/* 80149CF0 001468D0  83 C5 00 48 */	lwz r30, 0x48(r5)
/* 80149CF4 001468D4  98 1F 22 24 */	stb r0, 0x2224(r31)
/* 80149CF8 001468D8  4B F9 BA 75 */	bl func_800E576C
/* 80149CFC 001468DC  83 FF 02 D4 */	lwz r31, 0x2d4(r31)
/* 80149D00 001468E0  80 7E 00 00 */	lwz r3, 0(r30)
/* 80149D04 001468E4  80 9F 00 1C */	lwz r4, 0x1c(r31)
/* 80149D08 001468E8  48 12 16 F1 */	bl func_8026B3F8
/* 80149D0C 001468EC  80 7E 00 04 */	lwz r3, 4(r30)
/* 80149D10 001468F0  80 9F 00 20 */	lwz r4, 0x20(r31)
/* 80149D14 001468F4  48 12 16 E5 */	bl func_8026B3F8
/* 80149D18 001468F8  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 80149D1C 001468FC  38 80 00 39 */	li r4, 0x39
/* 80149D20 00146900  48 12 16 D9 */	bl func_8026B3F8
/* 80149D24 00146904  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80149D28 00146908  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80149D2C 0014690C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80149D30 00146910  38 21 00 20 */	addi r1, r1, 0x20
/* 80149D34 00146914  7C 08 03 A6 */	mtlr r0
/* 80149D38 00146918  4E 80 00 20 */	blr 

.global func_80149D3C
func_80149D3C:
/* 80149D3C 0014691C  7C 08 02 A6 */	mflr r0
/* 80149D40 00146920  90 01 00 04 */	stw r0, 4(r1)
/* 80149D44 00146924  94 21 FF F8 */	stwu r1, -8(r1)
/* 80149D48 00146928  4B F9 BB 11 */	bl func_800E5858
/* 80149D4C 0014692C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80149D50 00146930  38 21 00 08 */	addi r1, r1, 8
/* 80149D54 00146934  7C 08 03 A6 */	mtlr r0
/* 80149D58 00146938  4E 80 00 20 */	blr 

.global func_80149D5C
func_80149D5C:
/* 80149D5C 0014693C  7C 08 02 A6 */	mflr r0
/* 80149D60 00146940  38 80 00 01 */	li r4, 1
/* 80149D64 00146944  90 01 00 04 */	stw r0, 4(r1)
/* 80149D68 00146948  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80149D6C 0014694C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80149D70 00146950  7C 7F 1B 78 */	mr r31, r3
/* 80149D74 00146954  C0 22 A3 D0 */	lfs f1, lbl_804D9DB0@sda21(r2)
/* 80149D78 00146958  4B F2 67 79 */	bl func_800704F0
/* 80149D7C 0014695C  C0 22 A3 D0 */	lfs f1, lbl_804D9DB0@sda21(r2)
/* 80149D80 00146960  38 7F 00 00 */	addi r3, r31, 0
/* 80149D84 00146964  38 80 00 00 */	li r4, 0
/* 80149D88 00146968  4B F2 67 69 */	bl func_800704F0
/* 80149D8C 0014696C  C0 22 A3 D4 */	lfs f1, lbl_804D9DB4@sda21(r2)
/* 80149D90 00146970  38 7F 00 00 */	addi r3, r31, 0
/* 80149D94 00146974  38 80 00 03 */	li r4, 3
/* 80149D98 00146978  38 A0 00 03 */	li r5, 3
/* 80149D9C 0014697C  4B F2 6D ED */	bl ftAnim_ApplyPartAnim
/* 80149DA0 00146980  C0 22 A3 D4 */	lfs f1, lbl_804D9DB4@sda21(r2)
/* 80149DA4 00146984  38 7F 00 00 */	addi r3, r31, 0
/* 80149DA8 00146988  38 80 00 04 */	li r4, 4
/* 80149DAC 0014698C  38 A0 00 03 */	li r5, 3
/* 80149DB0 00146990  4B F2 6D D9 */	bl ftAnim_ApplyPartAnim
/* 80149DB4 00146994  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80149DB8 00146998  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80149DBC 0014699C  38 21 00 18 */	addi r1, r1, 0x18
/* 80149DC0 001469A0  7C 08 03 A6 */	mtlr r0
/* 80149DC4 001469A4  4E 80 00 20 */	blr 

.global func_80149DC8
func_80149DC8:
/* 80149DC8 001469A8  7C 08 02 A6 */	mflr r0
/* 80149DCC 001469AC  38 80 00 01 */	li r4, 1
/* 80149DD0 001469B0  90 01 00 04 */	stw r0, 4(r1)
/* 80149DD4 001469B4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80149DD8 001469B8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80149DDC 001469BC  7C 7F 1B 78 */	mr r31, r3
/* 80149DE0 001469C0  C0 22 A3 D4 */	lfs f1, lbl_804D9DB4@sda21(r2)
/* 80149DE4 001469C4  4B F2 67 0D */	bl func_800704F0
/* 80149DE8 001469C8  C0 22 A3 D4 */	lfs f1, lbl_804D9DB4@sda21(r2)
/* 80149DEC 001469CC  38 7F 00 00 */	addi r3, r31, 0
/* 80149DF0 001469D0  38 80 00 00 */	li r4, 0
/* 80149DF4 001469D4  4B F2 66 FD */	bl func_800704F0
/* 80149DF8 001469D8  C0 22 A3 D4 */	lfs f1, lbl_804D9DB4@sda21(r2)
/* 80149DFC 001469DC  38 7F 00 00 */	addi r3, r31, 0
/* 80149E00 001469E0  38 80 00 03 */	li r4, 3
/* 80149E04 001469E4  38 A0 00 02 */	li r5, 2
/* 80149E08 001469E8  4B F2 6D 81 */	bl ftAnim_ApplyPartAnim
/* 80149E0C 001469EC  C0 22 A3 D4 */	lfs f1, lbl_804D9DB4@sda21(r2)
/* 80149E10 001469F0  38 7F 00 00 */	addi r3, r31, 0
/* 80149E14 001469F4  38 80 00 04 */	li r4, 4
/* 80149E18 001469F8  38 A0 00 02 */	li r5, 2
/* 80149E1C 001469FC  4B F2 6D 6D */	bl ftAnim_ApplyPartAnim
/* 80149E20 00146A00  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80149E24 00146A04  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80149E28 00146A08  38 21 00 18 */	addi r1, r1, 0x18
/* 80149E2C 00146A0C  7C 08 03 A6 */	mtlr r0
/* 80149E30 00146A10  4E 80 00 20 */	blr 


.section .sdata2

.global lbl_804D9DB0
lbl_804D9DB0:
	.4byte 0x40400000
.global lbl_804D9DB4
lbl_804D9DB4:
	.4byte 0x00000000
