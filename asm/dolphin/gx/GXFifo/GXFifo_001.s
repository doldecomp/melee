.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

# https://decomp.me/scratch/1a1Bv // 2800 (0%)
.global GXInitFifoPtrs
GXInitFifoPtrs:
/* 8033B930 00338510  7C 08 02 A6 */	mflr r0
/* 8033B934 00338514  90 01 00 04 */	stw r0, 4(r1)
/* 8033B938 00338518  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8033B93C 0033851C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8033B940 00338520  3B E5 00 00 */	addi r31, r5, 0
/* 8033B944 00338524  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8033B948 00338528  3B C4 00 00 */	addi r30, r4, 0
/* 8033B94C 0033852C  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8033B950 00338530  3B A3 00 00 */	addi r29, r3, 0
/* 8033B954 00338534  48 00 BA 11 */	bl OSDisableInterrupts
/* 8033B958 00338538  93 DD 00 14 */	stw r30, 0x14(r29)
/* 8033B95C 0033853C  7C 1E F8 50 */	subf r0, r30, r31
/* 8033B960 00338540  93 FD 00 18 */	stw r31, 0x18(r29)
/* 8033B964 00338544  90 1D 00 1C */	stw r0, 0x1c(r29)
/* 8033B968 00338548  80 9D 00 1C */	lwz r4, 0x1c(r29)
/* 8033B96C 0033854C  2C 04 00 00 */	cmpwi r4, 0
/* 8033B970 00338550  40 80 00 10 */	bge lbl_8033B980
/* 8033B974 00338554  80 1D 00 08 */	lwz r0, 8(r29)
/* 8033B978 00338558  7C 04 02 14 */	add r0, r4, r0
/* 8033B97C 0033855C  90 1D 00 1C */	stw r0, 0x1c(r29)
lbl_8033B980:
/* 8033B980 00338560  48 00 BA 0D */	bl OSRestoreInterrupts
/* 8033B984 00338564  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8033B988 00338568  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8033B98C 0033856C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8033B990 00338570  7C 08 03 A6 */	mtlr r0
/* 8033B994 00338574  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8033B998 00338578  38 21 00 28 */	addi r1, r1, 0x28
/* 8033B99C 0033857C  4E 80 00 20 */	blr 

# https://decomp.me/scratch/Yb9o0 // 300 (0%)
.global GXInitFifoLimits
GXInitFifoLimits:
/* 8033B9A0 00338580  90 83 00 0C */	stw r4, 0xc(r3)
/* 8033B9A4 00338584  90 A3 00 10 */	stw r5, 0x10(r3)
/* 8033B9A8 00338588  4E 80 00 20 */	blr 

# https://decomp.me/scratch/NxAWt // 120 (98.24%)
.global GXSetCPUFifo
GXSetCPUFifo:
/* 8033B9AC 0033858C  7C 08 02 A6 */	mflr r0
/* 8033B9B0 00338590  90 01 00 04 */	stw r0, 4(r1)
/* 8033B9B4 00338594  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033B9B8 00338598  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8033B9BC 0033859C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8033B9C0 003385A0  7C 7E 1B 78 */	mr r30, r3
/* 8033B9C4 003385A4  48 00 B9 A1 */	bl OSDisableInterrupts
/* 8033B9C8 003385A8  80 0D BC 64 */	lwz r0, lbl_804D7304@sda21(r13)
/* 8033B9CC 003385AC  3B E3 00 00 */	addi r31, r3, 0
/* 8033B9D0 003385B0  93 CD BC 60 */	stw r30, lbl_804D7300@sda21(r13)
/* 8033B9D4 003385B4  7C 1E 00 40 */	cmplw r30, r0
/* 8033B9D8 003385B8  40 82 00 64 */	bne lbl_8033BA3C
/* 8033B9DC 003385BC  80 BE 00 00 */	lwz r5, 0(r30)
/* 8033B9E0 003385C0  38 00 00 01 */	li r0, 1
/* 8033B9E4 003385C4  80 8D BC 50 */	lwz r4, lbl_804D72F0@sda21(r13)
/* 8033B9E8 003385C8  38 60 00 01 */	li r3, 1
/* 8033B9EC 003385CC  54 A5 00 BE */	clrlwi r5, r5, 2
/* 8033B9F0 003385D0  90 A4 00 0C */	stw r5, 0xc(r4)
/* 8033B9F4 003385D4  38 80 00 01 */	li r4, 1
/* 8033B9F8 003385D8  80 DE 00 04 */	lwz r6, 4(r30)
/* 8033B9FC 003385DC  80 AD BC 50 */	lwz r5, lbl_804D72F0@sda21(r13)
/* 8033BA00 003385E0  54 C6 00 BE */	clrlwi r6, r6, 2
/* 8033BA04 003385E4  90 C5 00 10 */	stw r6, 0x10(r5)
/* 8033BA08 003385E8  80 DE 00 18 */	lwz r6, 0x18(r30)
/* 8033BA0C 003385EC  80 AD BC 50 */	lwz r5, lbl_804D72F0@sda21(r13)
/* 8033BA10 003385F0  54 C6 00 B4 */	rlwinm r6, r6, 0, 2, 0x1a
/* 8033BA14 003385F4  54 C6 01 88 */	rlwinm r6, r6, 0, 6, 4
/* 8033BA18 003385F8  90 C5 00 14 */	stw r6, 0x14(r5)
/* 8033BA1C 003385FC  98 0D BC 6C */	stb r0, lbl_804D730C@sda21(r13)
/* 8033BA20 00338600  48 00 03 3D */	bl __GXWriteFifoIntReset
/* 8033BA24 00338604  38 60 00 01 */	li r3, 1
/* 8033BA28 00338608  38 80 00 00 */	li r4, 0
/* 8033BA2C 0033860C  48 00 02 E5 */	bl __GXWriteFifoIntEnable
/* 8033BA30 00338610  38 60 00 01 */	li r3, 1
/* 8033BA34 00338614  48 00 02 99 */	bl __GXFifoLink
/* 8033BA38 00338618  48 00 00 60 */	b lbl_8033BA98
lbl_8033BA3C:
/* 8033BA3C 0033861C  88 0D BC 6C */	lbz r0, lbl_804D730C@sda21(r13)
/* 8033BA40 00338620  28 00 00 00 */	cmplwi r0, 0
/* 8033BA44 00338624  41 82 00 14 */	beq lbl_8033BA58
/* 8033BA48 00338628  38 60 00 00 */	li r3, 0
/* 8033BA4C 0033862C  48 00 02 81 */	bl __GXFifoLink
/* 8033BA50 00338630  38 00 00 00 */	li r0, 0
/* 8033BA54 00338634  98 0D BC 6C */	stb r0, lbl_804D730C@sda21(r13)
lbl_8033BA58:
/* 8033BA58 00338638  38 60 00 00 */	li r3, 0
/* 8033BA5C 0033863C  38 80 00 00 */	li r4, 0
/* 8033BA60 00338640  48 00 02 B1 */	bl __GXWriteFifoIntEnable
/* 8033BA64 00338644  80 1E 00 00 */	lwz r0, 0(r30)
/* 8033BA68 00338648  80 6D BC 50 */	lwz r3, lbl_804D72F0@sda21(r13)
/* 8033BA6C 0033864C  54 00 00 BE */	clrlwi r0, r0, 2
/* 8033BA70 00338650  90 03 00 0C */	stw r0, 0xc(r3)
/* 8033BA74 00338654  80 1E 00 04 */	lwz r0, 4(r30)
/* 8033BA78 00338658  80 6D BC 50 */	lwz r3, lbl_804D72F0@sda21(r13)
/* 8033BA7C 0033865C  54 00 00 BE */	clrlwi r0, r0, 2
/* 8033BA80 00338660  90 03 00 10 */	stw r0, 0x10(r3)
/* 8033BA84 00338664  80 1E 00 18 */	lwz r0, 0x18(r30)
/* 8033BA88 00338668  80 6D BC 50 */	lwz r3, lbl_804D72F0@sda21(r13)
/* 8033BA8C 0033866C  54 00 00 B4 */	rlwinm r0, r0, 0, 2, 0x1a
/* 8033BA90 00338670  54 00 01 88 */	rlwinm r0, r0, 0, 6, 4
/* 8033BA94 00338674  90 03 00 14 */	stw r0, 0x14(r3)
lbl_8033BA98:
/* 8033BA98 00338678  7C 00 04 AC */	sync 0
/* 8033BA9C 0033867C  7F E3 FB 78 */	mr r3, r31
/* 8033BAA0 00338680  48 00 B8 ED */	bl OSRestoreInterrupts
/* 8033BAA4 00338684  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8033BAA8 00338688  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8033BAAC 0033868C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8033BAB0 00338690  7C 08 03 A6 */	mtlr r0
/* 8033BAB4 00338694  38 21 00 18 */	addi r1, r1, 0x18
/* 8033BAB8 00338698  4E 80 00 20 */	blr 

# https://decomp.me/scratch/dvPQL // 9400 (0%)
.global GXSetGPFifo
GXSetGPFifo:
/* 8033BABC 0033869C  7C 08 02 A6 */	mflr r0
/* 8033BAC0 003386A0  90 01 00 04 */	stw r0, 4(r1)
/* 8033BAC4 003386A4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033BAC8 003386A8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8033BACC 003386AC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8033BAD0 003386B0  7C 7E 1B 78 */	mr r30, r3
/* 8033BAD4 003386B4  48 00 B8 91 */	bl OSDisableInterrupts
/* 8033BAD8 003386B8  7C 7F 1B 78 */	mr r31, r3
/* 8033BADC 003386BC  48 00 01 CD */	bl __GXFifoReadDisable
/* 8033BAE0 003386C0  38 60 00 00 */	li r3, 0
/* 8033BAE4 003386C4  38 80 00 00 */	li r4, 0
/* 8033BAE8 003386C8  48 00 02 29 */	bl __GXWriteFifoIntEnable
/* 8033BAEC 003386CC  93 CD BC 64 */	stw r30, lbl_804D7304@sda21(r13)
/* 8033BAF0 003386D0  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BAF4 003386D4  80 1E 00 00 */	lwz r0, 0(r30)
/* 8033BAF8 003386D8  B0 03 00 20 */	sth r0, 0x20(r3)
/* 8033BAFC 003386DC  80 1E 00 04 */	lwz r0, 4(r30)
/* 8033BB00 003386E0  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB04 003386E4  B0 03 00 24 */	sth r0, 0x24(r3)
/* 8033BB08 003386E8  80 1E 00 1C */	lwz r0, 0x1c(r30)
/* 8033BB0C 003386EC  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB10 003386F0  B0 03 00 30 */	sth r0, 0x30(r3)
/* 8033BB14 003386F4  80 1E 00 18 */	lwz r0, 0x18(r30)
/* 8033BB18 003386F8  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB1C 003386FC  B0 03 00 34 */	sth r0, 0x34(r3)
/* 8033BB20 00338700  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8033BB24 00338704  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB28 00338708  B0 03 00 38 */	sth r0, 0x38(r3)
/* 8033BB2C 0033870C  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 8033BB30 00338710  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB34 00338714  B0 03 00 28 */	sth r0, 0x28(r3)
/* 8033BB38 00338718  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8033BB3C 0033871C  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB40 00338720  B0 03 00 2C */	sth r0, 0x2c(r3)
/* 8033BB44 00338724  80 1E 00 00 */	lwz r0, 0(r30)
/* 8033BB48 00338728  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB4C 0033872C  54 00 84 BE */	rlwinm r0, r0, 0x10, 0x12, 0x1f
/* 8033BB50 00338730  B0 03 00 22 */	sth r0, 0x22(r3)
/* 8033BB54 00338734  80 1E 00 04 */	lwz r0, 4(r30)
/* 8033BB58 00338738  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB5C 0033873C  54 00 84 BE */	rlwinm r0, r0, 0x10, 0x12, 0x1f
/* 8033BB60 00338740  B0 03 00 26 */	sth r0, 0x26(r3)
/* 8033BB64 00338744  80 1E 00 1C */	lwz r0, 0x1c(r30)
/* 8033BB68 00338748  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB6C 0033874C  7C 00 86 70 */	srawi r0, r0, 0x10
/* 8033BB70 00338750  B0 03 00 32 */	sth r0, 0x32(r3)
/* 8033BB74 00338754  80 1E 00 18 */	lwz r0, 0x18(r30)
/* 8033BB78 00338758  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB7C 0033875C  54 00 84 BE */	rlwinm r0, r0, 0x10, 0x12, 0x1f
/* 8033BB80 00338760  B0 03 00 36 */	sth r0, 0x36(r3)
/* 8033BB84 00338764  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8033BB88 00338768  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB8C 0033876C  54 00 84 BE */	rlwinm r0, r0, 0x10, 0x12, 0x1f
/* 8033BB90 00338770  B0 03 00 3A */	sth r0, 0x3a(r3)
/* 8033BB94 00338774  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 8033BB98 00338778  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BB9C 0033877C  54 00 84 3E */	srwi r0, r0, 0x10
/* 8033BBA0 00338780  B0 03 00 2A */	sth r0, 0x2a(r3)
/* 8033BBA4 00338784  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8033BBA8 00338788  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BBAC 0033878C  54 00 84 3E */	srwi r0, r0, 0x10
/* 8033BBB0 00338790  B0 03 00 2E */	sth r0, 0x2e(r3)
/* 8033BBB4 00338794  7C 00 04 AC */	sync 0
/* 8033BBB8 00338798  80 6D BC 60 */	lwz r3, lbl_804D7300@sda21(r13)
/* 8033BBBC 0033879C  80 0D BC 64 */	lwz r0, lbl_804D7304@sda21(r13)
/* 8033BBC0 003387A0  7C 03 00 40 */	cmplw r3, r0
/* 8033BBC4 003387A4  40 82 00 24 */	bne lbl_8033BBE8
/* 8033BBC8 003387A8  38 00 00 01 */	li r0, 1
/* 8033BBCC 003387AC  98 0D BC 6C */	stb r0, lbl_804D730C@sda21(r13)
/* 8033BBD0 003387B0  38 60 00 01 */	li r3, 1
/* 8033BBD4 003387B4  38 80 00 00 */	li r4, 0
/* 8033BBD8 003387B8  48 00 01 39 */	bl __GXWriteFifoIntEnable
/* 8033BBDC 003387BC  38 60 00 01 */	li r3, 1
/* 8033BBE0 003387C0  48 00 00 ED */	bl __GXFifoLink
/* 8033BBE4 003387C4  48 00 00 20 */	b lbl_8033BC04
lbl_8033BBE8:
/* 8033BBE8 003387C8  38 00 00 00 */	li r0, 0
/* 8033BBEC 003387CC  98 0D BC 6C */	stb r0, lbl_804D730C@sda21(r13)
/* 8033BBF0 003387D0  38 60 00 00 */	li r3, 0
/* 8033BBF4 003387D4  38 80 00 00 */	li r4, 0
/* 8033BBF8 003387D8  48 00 01 19 */	bl __GXWriteFifoIntEnable
/* 8033BBFC 003387DC  38 60 00 00 */	li r3, 0
/* 8033BC00 003387E0  48 00 00 CD */	bl __GXFifoLink
lbl_8033BC04:
/* 8033BC04 003387E4  38 60 00 01 */	li r3, 1
/* 8033BC08 003387E8  38 80 00 01 */	li r4, 1
/* 8033BC0C 003387EC  48 00 01 51 */	bl __GXWriteFifoIntReset
/* 8033BC10 003387F0  48 00 00 71 */	bl __GXFifoReadEnable
/* 8033BC14 003387F4  7F E3 FB 78 */	mr r3, r31
/* 8033BC18 003387F8  48 00 B7 75 */	bl OSRestoreInterrupts
/* 8033BC1C 003387FC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8033BC20 00338800  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8033BC24 00338804  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8033BC28 00338808  7C 08 03 A6 */	mtlr r0
/* 8033BC2C 0033880C  38 21 00 18 */	addi r1, r1, 0x18
/* 8033BC30 00338810  4E 80 00 20 */	blr 

# https://decomp.me/scratch/BIDoG // 0 (100%)
.global __GXFifoInit
__GXFifoInit:
/* 8033BC34 00338814  7C 08 02 A6 */	mflr r0
/* 8033BC38 00338818  3C 60 80 34 */	lis r3, GXCPInterruptHandler@ha
/* 8033BC3C 0033881C  90 01 00 04 */	stw r0, 4(r1)
/* 8033BC40 00338820  38 83 B7 88 */	addi r4, r3, GXCPInterruptHandler@l
/* 8033BC44 00338824  38 60 00 11 */	li r3, 0x11
/* 8033BC48 00338828  94 21 FF F8 */	stwu r1, -8(r1)
/* 8033BC4C 0033882C  48 00 B7 65 */	bl __OSSetInterruptHandler
/* 8033BC50 00338830  38 60 40 00 */	li r3, 0x4000
/* 8033BC54 00338834  48 00 BB 61 */	bl __OSUnmaskInterrupts
/* 8033BC58 00338838  48 00 F0 E5 */	bl OSGetCurrentThread
/* 8033BC5C 0033883C  38 00 00 00 */	li r0, 0
/* 8033BC60 00338840  90 6D BC 68 */	stw r3, __GXCurrentThread@sda21(r13)
/* 8033BC64 00338844  90 0D BC 70 */	stw r0, GXOverflowSuspendInProgress@sda21(r13)
/* 8033BC68 00338848  90 0D BC 60 */	stw r0, lbl_804D7300@sda21(r13)
/* 8033BC6C 0033884C  90 0D BC 64 */	stw r0, lbl_804D7304@sda21(r13)
/* 8033BC70 00338850  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8033BC74 00338854  38 21 00 08 */	addi r1, r1, 8
/* 8033BC78 00338858  7C 08 03 A6 */	mtlr r0
/* 8033BC7C 0033885C  4E 80 00 20 */	blr 

# https://decomp.me/scratch/ifETw // 100 (90%)
__GXFifoReadEnable:
/* 8033BC80 00338860  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033BC84 00338864  84 03 00 08 */	lwzu r0, 8(r3)
/* 8033BC88 00338868  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 8033BC8C 0033886C  60 00 00 01 */	ori r0, r0, 1
/* 8033BC90 00338870  90 03 00 00 */	stw r0, 0(r3)
/* 8033BC94 00338874  80 8D A5 08 */	lwz r4, __GXContexts@sda21(r13)
/* 8033BC98 00338878  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BC9C 0033887C  80 04 00 08 */	lwz r0, 8(r4)
/* 8033BCA0 00338880  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BCA4 00338884  4E 80 00 20 */	blr 

# https://decomp.me/scratch/bL9CQ // 100 (88.89%)
__GXFifoReadDisable:
/* 8033BCA8 00338888  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033BCAC 0033888C  84 03 00 08 */	lwzu r0, 8(r3)
/* 8033BCB0 00338890  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 8033BCB4 00338894  90 03 00 00 */	stw r0, 0(r3)
/* 8033BCB8 00338898  80 8D A5 08 */	lwz r4, __GXContexts@sda21(r13)
/* 8033BCBC 0033889C  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BCC0 003388A0  80 04 00 08 */	lwz r0, 8(r4)
/* 8033BCC4 003388A4  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BCC8 003388A8  4E 80 00 20 */	blr 

# https://decomp.me/scratch/cTeYY // 300 (82.35%)
__GXFifoLink:
/* 8033BCCC 003388AC  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8033BCD0 003388B0  41 82 00 0C */	beq lbl_8033BCDC
/* 8033BCD4 003388B4  38 00 00 01 */	li r0, 1
/* 8033BCD8 003388B8  48 00 00 08 */	b lbl_8033BCE0
lbl_8033BCDC:
/* 8033BCDC 003388BC  38 00 00 00 */	li r0, 0
lbl_8033BCE0:
/* 8033BCE0 003388C0  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033BCE4 003388C4  54 00 20 36 */	slwi r0, r0, 4
/* 8033BCE8 003388C8  38 83 00 08 */	addi r4, r3, 8
/* 8033BCEC 003388CC  80 63 00 08 */	lwz r3, 8(r3)
/* 8033BCF0 003388D0  54 63 07 34 */	rlwinm r3, r3, 0, 0x1c, 0x1a
/* 8033BCF4 003388D4  7C 60 03 78 */	or r0, r3, r0
/* 8033BCF8 003388D8  90 04 00 00 */	stw r0, 0(r4)
/* 8033BCFC 003388DC  80 8D A5 08 */	lwz r4, __GXContexts@sda21(r13)
/* 8033BD00 003388E0  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BD04 003388E4  80 04 00 08 */	lwz r0, 8(r4)
/* 8033BD08 003388E8  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BD0C 003388EC  4E 80 00 20 */	blr 

# https://decomp.me/scratch/mJZcx // 635 (66.58%)
.global __GXWriteFifoIntEnable
__GXWriteFifoIntEnable:
/* 8033BD10 003388F0  80 AD A5 08 */	lwz r5, __GXContexts@sda21(r13)
/* 8033BD14 003388F4  54 63 15 BA */	rlwinm r3, r3, 2, 0x16, 0x1d
/* 8033BD18 003388F8  54 80 1D 78 */	rlwinm r0, r4, 3, 0x15, 0x1c
/* 8033BD1C 003388FC  38 C5 00 08 */	addi r6, r5, 8
/* 8033BD20 00338900  80 A5 00 08 */	lwz r5, 8(r5)
/* 8033BD24 00338904  54 A4 07 B8 */	rlwinm r4, r5, 0, 0x1e, 0x1c
/* 8033BD28 00338908  7C 83 1B 78 */	or r3, r4, r3
/* 8033BD2C 0033890C  90 66 00 00 */	stw r3, 0(r6)
/* 8033BD30 00338910  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033BD34 00338914  38 83 00 08 */	addi r4, r3, 8
/* 8033BD38 00338918  80 63 00 08 */	lwz r3, 8(r3)
/* 8033BD3C 0033891C  54 63 07 76 */	rlwinm r3, r3, 0, 0x1d, 0x1b
/* 8033BD40 00338920  7C 60 03 78 */	or r0, r3, r0
/* 8033BD44 00338924  90 04 00 00 */	stw r0, 0(r4)
/* 8033BD48 00338928  80 8D A5 08 */	lwz r4, __GXContexts@sda21(r13)
/* 8033BD4C 0033892C  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BD50 00338930  80 04 00 08 */	lwz r0, 8(r4)
/* 8033BD54 00338934  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BD58 00338938  4E 80 00 20 */	blr 

# https://decomp.me/scratch/7EFEP // 610 (67.89%)
.global __GXWriteFifoIntReset
__GXWriteFifoIntReset:
/* 8033BD5C 0033893C  80 AD A5 08 */	lwz r5, __GXContexts@sda21(r13)
/* 8033BD60 00338940  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 8033BD64 00338944  54 80 0D FC */	rlwinm r0, r4, 1, 0x17, 0x1e
/* 8033BD68 00338948  38 C5 00 10 */	addi r6, r5, 0x10
/* 8033BD6C 0033894C  80 A5 00 10 */	lwz r5, 0x10(r5)
/* 8033BD70 00338950  54 A4 00 3C */	rlwinm r4, r5, 0, 0, 0x1e
/* 8033BD74 00338954  7C 83 1B 78 */	or r3, r4, r3
/* 8033BD78 00338958  90 66 00 00 */	stw r3, 0(r6)
/* 8033BD7C 0033895C  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033BD80 00338960  38 83 00 10 */	addi r4, r3, 0x10
/* 8033BD84 00338964  80 63 00 10 */	lwz r3, 0x10(r3)
/* 8033BD88 00338968  54 63 07 FA */	rlwinm r3, r3, 0, 0x1f, 0x1d
/* 8033BD8C 0033896C  7C 60 03 78 */	or r0, r3, r0
/* 8033BD90 00338970  90 04 00 00 */	stw r0, 0(r4)
/* 8033BD94 00338974  80 8D A5 08 */	lwz r4, __GXContexts@sda21(r13)
/* 8033BD98 00338978  80 6D BC 54 */	lwz r3, __cpReg@sda21(r13)
/* 8033BD9C 0033897C  80 04 00 10 */	lwz r0, 0x10(r4)
/* 8033BDA0 00338980  B0 03 00 04 */	sth r0, 4(r3)
/* 8033BDA4 00338984  4E 80 00 20 */	blr 

.section .sbss
    .balign 8

.global lbl_804D72F0
lbl_804D72F0:
	.skip 0x4

.global __cpReg
__cpReg:
	.skip 0x4

.global __peReg
__peReg:
	.skip 0x4

.global lbl_804D72FC
lbl_804D72FC:
	.skip 0x4

lbl_804D7300:
	.skip 0x4

lbl_804D7304:
	.skip 0x4

.global __GXCurrentThread
__GXCurrentThread:
	.skip 0x4

lbl_804D730C:
	.skip 0x4

.global GXOverflowSuspendInProgress
GXOverflowSuspendInProgress:
	.skip 0x4

.global BreakPointCB
BreakPointCB:
	.skip 0x4

.global __GXOverflowCount
__GXOverflowCount:
	.skip 0x4
