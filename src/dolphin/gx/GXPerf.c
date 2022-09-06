#include <dolphin/gx/__GXInit.h>

void lbl_80341E70(void);
void lbl_80341E8C(void);
void lbl_80341EA8(void);
void lbl_80341EC4(void);
void lbl_80341EE0(void);
void lbl_80341EFC(void);
void lbl_80341F18(void);
void lbl_80341F34(void);
void lbl_80341F50(void);
void lbl_80341F6C(void);
void lbl_80341FA4(void);
void lbl_80341FDC(void);
void lbl_80342014(void);
void lbl_8034204C(void);
void lbl_80342084(void);
void lbl_803420BC(void);
void lbl_803420F4(void);
void lbl_8034212C(void);
void lbl_8034213C(void);
void lbl_8034214C(void);
void lbl_8034215C(void);
void lbl_8034216C(void);
void lbl_80342184(void);
void lbl_80341A40(void);
void lbl_80341A60(void);
void lbl_80341A80(void);
void lbl_80341AA0(void);
void lbl_80341AC0(void);
void lbl_80341AE0(void);
void lbl_80341B00(void);
void lbl_80341B20(void);
void lbl_80341B40(void);
void lbl_80341B60(void);
void lbl_80341B9C(void);
void lbl_80341B80(void);
void lbl_80341BBC(void);
void lbl_80341BD8(void);
void lbl_80341BF4(void);
void lbl_80341C10(void);
void lbl_80341C2C(void);
void lbl_80341C48(void);
void lbl_80341C64(void);
void lbl_80341C80(void);
void lbl_80341C9C(void);
void lbl_80341CB8(void);
void lbl_80341CD4(void);
void lbl_80341CF0(void);
void lbl_80341D0C(void);
void lbl_80341D28(void);
void lbl_80341D44(void);
void lbl_80341D60(void);
void lbl_80341D7C(void);
void lbl_80341D98(void);
void lbl_80341DB4(void);
void lbl_80341DD0(void);
void lbl_80341DEC(void);
void lbl_80341E08(void);
void lbl_80341E24(void);
void lbl_80341E40(void);

static jtbl_t jtbl_80401528 = {
    &lbl_80341E70, &lbl_80341E8C, &lbl_80341EA8, &lbl_80341EC4,
    &lbl_80341EE0, &lbl_80341EFC, &lbl_80341F18, &lbl_80341F34,
    &lbl_80341F50, &lbl_80341F6C, &lbl_80341FA4, &lbl_80341FDC,
    &lbl_80342014, &lbl_8034204C, &lbl_80342084, &lbl_803420BC,
    &lbl_803420F4, &lbl_8034212C, &lbl_8034213C, &lbl_8034214C,
    &lbl_8034215C, &lbl_8034216C, &lbl_80342184
};

static jtbl_t jtbl_80401584 = {
    &lbl_80341A40, &lbl_80341A60, &lbl_80341A80, &lbl_80341AA0,
    &lbl_80341AC0, &lbl_80341AE0, &lbl_80341B00, &lbl_80341B20,
    &lbl_80341B40, &lbl_80341B60, &lbl_80341B9C, &lbl_80341B80,
    &lbl_80341BBC, &lbl_80341BD8, &lbl_80341BF4, &lbl_80341C10,
    &lbl_80341C2C, &lbl_80341C48, &lbl_80341C64, &lbl_80341C80,
    &lbl_80341C9C, &lbl_80341CB8, &lbl_80341CD4, &lbl_80341CF0,
    &lbl_80341D0C, &lbl_80341D28, &lbl_80341D44, &lbl_80341D60,
    &lbl_80341D7C, &lbl_80341D98, &lbl_80341DB4, &lbl_80341DD0,
    &lbl_80341DEC, &lbl_80341E08, &lbl_80341E24, &lbl_80341E40
};

// https://decomp.me/scratch/gAvJm // 3230 (94.13%)
#pragma push
asm unk_t GXSetGPMetric()
{ // clang-format off
    nofralloc
/* 803418FC 0033E4DC  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 80341900 0033E4E0  80 05 04 E0 */	lwz r0, 0x4e0(r5)
/* 80341904 0033E4E4  2C 00 00 22 */	cmpwi r0, 0x22
/* 80341908 0033E4E8  41 82 00 2C */	beq lbl_80341934
/* 8034190C 0033E4EC  40 80 00 74 */	bge lbl_80341980
/* 80341910 0033E4F0  2C 00 00 0B */	cmpwi r0, 0xb
/* 80341914 0033E4F4  40 80 00 10 */	bge lbl_80341924
/* 80341918 0033E4F8  2C 00 00 00 */	cmpwi r0, 0
/* 8034191C 0033E4FC  40 80 00 18 */	bge lbl_80341934
/* 80341920 0033E500  48 00 00 60 */	b lbl_80341980
lbl_80341924:
/* 80341924 0033E504  2C 00 00 1B */	cmpwi r0, 0x1b
/* 80341928 0033E508  40 80 00 44 */	bge lbl_8034196C
/* 8034192C 0033E50C  48 00 00 28 */	b lbl_80341954
/* 80341930 0033E510  48 00 00 50 */	b lbl_80341980
lbl_80341934:
/* 80341934 0033E514  38 00 00 10 */	li r0, 0x10
/* 80341938 0033E518  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8034193C 0033E51C  98 06 80 00 */	stb r0, 0xCC008000@l(r6)
/* 80341940 0033E520  38 A0 10 06 */	li r5, 0x1006
/* 80341944 0033E524  38 00 00 00 */	li r0, 0
/* 80341948 0033E528  90 A6 80 00 */	stw r5, -0x8000(r6)
/* 8034194C 0033E52C  90 06 80 00 */	stw r0, -0x8000(r6)
/* 80341950 0033E530  48 00 00 30 */	b lbl_80341980
lbl_80341954:
/* 80341954 0033E534  38 00 00 61 */	li r0, 0x61
/* 80341958 0033E538  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8034195C 0033E53C  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341960 0033E540  3C 00 23 00 */	lis r0, 0x2300
/* 80341964 0033E544  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341968 0033E548  48 00 00 18 */	b lbl_80341980
lbl_8034196C:
/* 8034196C 0033E54C  38 00 00 61 */	li r0, 0x61
/* 80341970 0033E550  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341974 0033E554  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341978 0033E558  3C 00 24 00 */	lis r0, 0x2400
/* 8034197C 0033E55C  90 05 80 00 */	stw r0, -0x8000(r5)
lbl_80341980:
/* 80341980 0033E560  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 80341984 0033E564  80 05 04 E4 */	lwz r0, 0x4e4(r5)
/* 80341988 0033E568  2C 00 00 15 */	cmpwi r0, 0x15
/* 8034198C 0033E56C  41 82 00 2C */	beq lbl_803419B8
/* 80341990 0033E570  40 80 00 80 */	bge lbl_80341A10
/* 80341994 0033E574  2C 00 00 09 */	cmpwi r0, 9
/* 80341998 0033E578  40 80 00 10 */	bge lbl_803419A8
/* 8034199C 0033E57C  2C 00 00 00 */	cmpwi r0, 0
/* 803419A0 0033E580  40 80 00 18 */	bge lbl_803419B8
/* 803419A4 0033E584  48 00 00 6C */	b lbl_80341A10
lbl_803419A8:
/* 803419A8 0033E588  2C 00 00 11 */	cmpwi r0, 0x11
/* 803419AC 0033E58C  40 80 00 58 */	bge lbl_80341A04
/* 803419B0 0033E590  48 00 00 20 */	b lbl_803419D0
/* 803419B4 0033E594  48 00 00 5C */	b lbl_80341A10
lbl_803419B8:
/* 803419B8 0033E598  38 00 00 61 */	li r0, 0x61
/* 803419BC 0033E59C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 803419C0 0033E5A0  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 803419C4 0033E5A4  3C 00 67 00 */	lis r0, 0x6700
/* 803419C8 0033E5A8  90 05 80 00 */	stw r0, -0x8000(r5)
/* 803419CC 0033E5AC  48 00 00 44 */	b lbl_80341A10
lbl_803419D0:
/* 803419D0 0033E5B0  38 E5 04 E8 */	addi r7, r5, 0x4e8
/* 803419D4 0033E5B4  80 05 04 E8 */	lwz r0, 0x4e8(r5)
/* 803419D8 0033E5B8  38 A0 00 08 */	li r5, 8
/* 803419DC 0033E5BC  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 803419E0 0033E5C0  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 803419E4 0033E5C4  90 07 00 00 */	stw r0, 0(r7)
/* 803419E8 0033E5C8  38 00 00 20 */	li r0, 0x20
/* 803419EC 0033E5CC  98 A6 80 00 */	stb r5, 0xCC008000@l(r6)
/* 803419F0 0033E5D0  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 803419F4 0033E5D4  98 06 80 00 */	stb r0, -0x8000(r6)
/* 803419F8 0033E5D8  80 05 04 E8 */	lwz r0, 0x4e8(r5)
/* 803419FC 0033E5DC  90 06 80 00 */	stw r0, -0x8000(r6)
/* 80341A00 0033E5E0  48 00 00 10 */	b lbl_80341A10
lbl_80341A04:
/* 80341A04 0033E5E4  80 AD BC 54 */	lwz r5, __cpReg(r13)
/* 80341A08 0033E5E8  38 00 00 00 */	li r0, 0
/* 80341A0C 0033E5EC  B0 05 00 06 */	sth r0, 6(r5)
lbl_80341A10:
/* 80341A10 0033E5F0  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 80341A14 0033E5F4  90 65 04 E0 */	stw r3, 0x4e0(r5)
/* 80341A18 0033E5F8  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341A1C 0033E5FC  80 03 04 E0 */	lwz r0, 0x4e0(r3)
/* 80341A20 0033E600  28 00 00 23 */	cmplwi r0, 0x23
/* 80341A24 0033E604  41 81 04 1C */	bgt lbl_80341E40
/* 80341A28 0033E608  3C 60 80 40 */	lis r3, jtbl_80401584@ha
/* 80341A2C 0033E60C  38 63 15 84 */	addi r3, r3, jtbl_80401584@l
/* 80341A30 0033E610  54 00 10 3A */	slwi r0, r0, 2
/* 80341A34 0033E614  7C 03 00 2E */	lwzx r0, r3, r0
/* 80341A38 0033E618  7C 09 03 A6 */	mtctr r0
/* 80341A3C 0033E61C  4E 80 04 20 */	bctr 
entry lbl_80341A40
/* 80341A40 0033E620  38 00 00 10 */	li r0, 0x10
/* 80341A44 0033E624  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341A48 0033E628  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341A4C 0033E62C  38 60 10 06 */	li r3, 0x1006
/* 80341A50 0033E630  38 00 02 73 */	li r0, 0x273
/* 80341A54 0033E634  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341A58 0033E638  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341A5C 0033E63C  48 00 03 E4 */	b lbl_80341E40
entry lbl_80341A60
/* 80341A60 0033E640  38 00 00 10 */	li r0, 0x10
/* 80341A64 0033E644  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341A68 0033E648  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341A6C 0033E64C  38 60 10 06 */	li r3, 0x1006
/* 80341A70 0033E650  38 00 01 4A */	li r0, 0x14a
/* 80341A74 0033E654  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341A78 0033E658  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341A7C 0033E65C  48 00 03 C4 */	b lbl_80341E40
entry lbl_80341A80
/* 80341A80 0033E660  38 00 00 10 */	li r0, 0x10
/* 80341A84 0033E664  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341A88 0033E668  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341A8C 0033E66C  38 60 10 06 */	li r3, 0x1006
/* 80341A90 0033E670  38 00 01 6B */	li r0, 0x16b
/* 80341A94 0033E674  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341A98 0033E678  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341A9C 0033E67C  48 00 03 A4 */	b lbl_80341E40
entry lbl_80341AA0
/* 80341AA0 0033E680  38 00 00 10 */	li r0, 0x10
/* 80341AA4 0033E684  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341AA8 0033E688  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341AAC 0033E68C  38 60 10 06 */	li r3, 0x1006
/* 80341AB0 0033E690  38 00 00 84 */	li r0, 0x84
/* 80341AB4 0033E694  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341AB8 0033E698  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341ABC 0033E69C  48 00 03 84 */	b lbl_80341E40
entry lbl_80341AC0
/* 80341AC0 0033E6A0  38 00 00 10 */	li r0, 0x10
/* 80341AC4 0033E6A4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341AC8 0033E6A8  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341ACC 0033E6AC  38 60 10 06 */	li r3, 0x1006
/* 80341AD0 0033E6B0  38 00 00 C6 */	li r0, 0xc6
/* 80341AD4 0033E6B4  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341AD8 0033E6B8  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341ADC 0033E6BC  48 00 03 64 */	b lbl_80341E40
entry lbl_80341AE0
/* 80341AE0 0033E6C0  38 00 00 10 */	li r0, 0x10
/* 80341AE4 0033E6C4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341AE8 0033E6C8  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341AEC 0033E6CC  38 60 10 06 */	li r3, 0x1006
/* 80341AF0 0033E6D0  38 00 02 10 */	li r0, 0x210
/* 80341AF4 0033E6D4  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341AF8 0033E6D8  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341AFC 0033E6DC  48 00 03 44 */	b lbl_80341E40
entry lbl_80341B00
/* 80341B00 0033E6E0  38 00 00 10 */	li r0, 0x10
/* 80341B04 0033E6E4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341B08 0033E6E8  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341B0C 0033E6EC  38 60 10 06 */	li r3, 0x1006
/* 80341B10 0033E6F0  38 00 02 52 */	li r0, 0x252
/* 80341B14 0033E6F4  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341B18 0033E6F8  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341B1C 0033E6FC  48 00 03 24 */	b lbl_80341E40
entry lbl_80341B20
/* 80341B20 0033E700  38 00 00 10 */	li r0, 0x10
/* 80341B24 0033E704  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341B28 0033E708  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341B2C 0033E70C  38 60 10 06 */	li r3, 0x1006
/* 80341B30 0033E710  38 00 02 31 */	li r0, 0x231
/* 80341B34 0033E714  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341B38 0033E718  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341B3C 0033E71C  48 00 03 04 */	b lbl_80341E40
entry lbl_80341B40
/* 80341B40 0033E720  38 00 00 10 */	li r0, 0x10
/* 80341B44 0033E724  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341B48 0033E728  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341B4C 0033E72C  38 60 10 06 */	li r3, 0x1006
/* 80341B50 0033E730  38 00 01 AD */	li r0, 0x1ad
/* 80341B54 0033E734  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341B58 0033E738  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341B5C 0033E73C  48 00 02 E4 */	b lbl_80341E40
entry lbl_80341B60
/* 80341B60 0033E740  38 00 00 10 */	li r0, 0x10
/* 80341B64 0033E744  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341B68 0033E748  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341B6C 0033E74C  38 60 10 06 */	li r3, 0x1006
/* 80341B70 0033E750  38 00 01 CE */	li r0, 0x1ce
/* 80341B74 0033E754  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341B78 0033E758  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341B7C 0033E75C  48 00 02 C4 */	b lbl_80341E40
entry lbl_80341B80
/* 80341B80 0033E760  38 00 00 61 */	li r0, 0x61
/* 80341B84 0033E764  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341B88 0033E768  3C 60 23 04 */	lis r3, 0x2303AE7F@ha
/* 80341B8C 0033E76C  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341B90 0033E770  38 03 AE 7F */	addi r0, r3, 0x2303AE7F@l
/* 80341B94 0033E774  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341B98 0033E778  48 00 02 A8 */	b lbl_80341E40
entry lbl_80341B9C
/* 80341B9C 0033E77C  38 00 00 10 */	li r0, 0x10
/* 80341BA0 0033E780  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341BA4 0033E784  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341BA8 0033E788  38 60 10 06 */	li r3, 0x1006
/* 80341BAC 0033E78C  38 00 01 53 */	li r0, 0x153
/* 80341BB0 0033E790  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341BB4 0033E794  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341BB8 0033E798  48 00 02 88 */	b lbl_80341E40
entry lbl_80341BBC
/* 80341BBC 0033E79C  38 00 00 61 */	li r0, 0x61
/* 80341BC0 0033E7A0  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341BC4 0033E7A4  3C 60 23 04 */	lis r3, 0x23038E7F@ha
/* 80341BC8 0033E7A8  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341BCC 0033E7AC  38 03 8E 7F */	addi r0, r3, 0x23038E7F@l
/* 80341BD0 0033E7B0  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341BD4 0033E7B4  48 00 02 6C */	b lbl_80341E40
entry lbl_80341BD8
/* 80341BD8 0033E7B8  38 00 00 61 */	li r0, 0x61
/* 80341BDC 0033E7BC  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341BE0 0033E7C0  3C 60 23 04 */	lis r3, 0x23039E7F@ha
/* 80341BE4 0033E7C4  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341BE8 0033E7C8  38 03 9E 7F */	addi r0, r3, 0x23039E7F@l
/* 80341BEC 0033E7CC  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341BF0 0033E7D0  48 00 02 50 */	b lbl_80341E40
entry lbl_80341BF4
/* 80341BF4 0033E7D4  38 00 00 61 */	li r0, 0x61
/* 80341BF8 0033E7D8  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341BFC 0033E7DC  3C 60 23 03 */	lis r3, 0x23031E7F@ha
/* 80341C00 0033E7E0  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341C04 0033E7E4  38 03 1E 7F */	addi r0, r3, 0x23031E7F@l
/* 80341C08 0033E7E8  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341C0C 0033E7EC  48 00 02 34 */	b lbl_80341E40
entry lbl_80341C10
/* 80341C10 0033E7F0  38 00 00 61 */	li r0, 0x61
/* 80341C14 0033E7F4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341C18 0033E7F8  3C 60 23 04 */	lis r3, 0x2303AC3F@ha
/* 80341C1C 0033E7FC  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341C20 0033E800  38 03 AC 3F */	addi r0, r3, 0x2303AC3F@l
/* 80341C24 0033E804  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341C28 0033E808  48 00 02 18 */	b lbl_80341E40
entry lbl_80341C2C
/* 80341C2C 0033E80C  38 00 00 61 */	li r0, 0x61
/* 80341C30 0033E810  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341C34 0033E814  3C 60 23 04 */	lis r3, 0x2303AC7F@ha
/* 80341C38 0033E818  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341C3C 0033E81C  38 03 AC 7F */	addi r0, r3, 0x2303AC7F@l
/* 80341C40 0033E820  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341C44 0033E824  48 00 01 FC */	b lbl_80341E40
entry lbl_80341C48
/* 80341C48 0033E828  38 00 00 61 */	li r0, 0x61
/* 80341C4C 0033E82C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341C50 0033E830  3C 60 23 04 */	lis r3, 0x2303ACBF@ha
/* 80341C54 0033E834  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341C58 0033E838  38 03 AC BF */	addi r0, r3, 0x2303ACBF@l
/* 80341C5C 0033E83C  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341C60 0033E840  48 00 01 E0 */	b lbl_80341E40
entry lbl_80341C64
/* 80341C64 0033E844  38 00 00 61 */	li r0, 0x61
/* 80341C68 0033E848  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341C6C 0033E84C  3C 60 23 04 */	lis r3, 0x2303ACFF@ha
/* 80341C70 0033E850  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341C74 0033E854  38 03 AC FF */	addi r0, r3, 0x2303ACFF@l
/* 80341C78 0033E858  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341C7C 0033E85C  48 00 01 C4 */	b lbl_80341E40
entry lbl_80341C80
/* 80341C80 0033E860  38 00 00 61 */	li r0, 0x61
/* 80341C84 0033E864  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341C88 0033E868  3C 60 23 04 */	lis r3, 0x2303AD3F@ha
/* 80341C8C 0033E86C  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341C90 0033E870  38 03 AD 3F */	addi r0, r3, 0x2303AD3F@l
/* 80341C94 0033E874  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341C98 0033E878  48 00 01 A8 */	b lbl_80341E40
entry lbl_80341C9C
/* 80341C9C 0033E87C  38 00 00 61 */	li r0, 0x61
/* 80341CA0 0033E880  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341CA4 0033E884  3C 60 23 04 */	lis r3, 0x2303AD7F@ha
/* 80341CA8 0033E888  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341CAC 0033E88C  38 03 AD 7F */	addi r0, r3, 0x2303AD7F@l
/* 80341CB0 0033E890  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341CB4 0033E894  48 00 01 8C */	b lbl_80341E40
entry lbl_80341CB8
/* 80341CB8 0033E898  38 00 00 61 */	li r0, 0x61
/* 80341CBC 0033E89C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341CC0 0033E8A0  3C 60 23 04 */	lis r3, 0x2303ADBF@ha
/* 80341CC4 0033E8A4  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341CC8 0033E8A8  38 03 AD BF */	addi r0, r3, 0x2303ADBF@l
/* 80341CCC 0033E8AC  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341CD0 0033E8B0  48 00 01 70 */	b lbl_80341E40
entry lbl_80341CD4
/* 80341CD4 0033E8B4  38 00 00 61 */	li r0, 0x61
/* 80341CD8 0033E8B8  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341CDC 0033E8BC  3C 60 23 04 */	lis r3, 0x2303ADFF@ha
/* 80341CE0 0033E8C0  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341CE4 0033E8C4  38 03 AD FF */	addi r0, r3, 0x2303ADFF@l
/* 80341CE8 0033E8C8  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341CEC 0033E8CC  48 00 01 54 */	b lbl_80341E40
entry lbl_80341CF0
/* 80341CF0 0033E8D0  38 00 00 61 */	li r0, 0x61
/* 80341CF4 0033E8D4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341CF8 0033E8D8  3C 60 23 04 */	lis r3, 0x2303AE3F@ha
/* 80341CFC 0033E8DC  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341D00 0033E8E0  38 03 AE 3F */	addi r0, r3, 0x2303AE3F@l
/* 80341D04 0033E8E4  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341D08 0033E8E8  48 00 01 38 */	b lbl_80341E40
entry lbl_80341D0C
/* 80341D0C 0033E8EC  38 00 00 61 */	li r0, 0x61
/* 80341D10 0033E8F0  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341D14 0033E8F4  3C 60 23 04 */	lis r3, 0x2303A27F@ha
/* 80341D18 0033E8F8  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341D1C 0033E8FC  38 03 A2 7F */	addi r0, r3, 0x2303A27F@l
/* 80341D20 0033E900  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341D24 0033E904  48 00 01 1C */	b lbl_80341E40
entry lbl_80341D28
/* 80341D28 0033E908  38 00 00 61 */	li r0, 0x61
/* 80341D2C 0033E90C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341D30 0033E910  3C 60 23 04 */	lis r3, 0x2303A67F@ha
/* 80341D34 0033E914  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341D38 0033E918  38 03 A6 7F */	addi r0, r3, 0x2303A67F@l
/* 80341D3C 0033E91C  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341D40 0033E920  48 00 01 00 */	b lbl_80341E40
entry lbl_80341D44
/* 80341D44 0033E924  38 00 00 61 */	li r0, 0x61
/* 80341D48 0033E928  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341D4C 0033E92C  3C 60 23 04 */	lis r3, 0x2303AA7F@ha
/* 80341D50 0033E930  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341D54 0033E934  38 03 AA 7F */	addi r0, r3, 0x2303AA7F@l
/* 80341D58 0033E938  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341D5C 0033E93C  48 00 00 E4 */	b lbl_80341E40
entry lbl_80341D60
/* 80341D60 0033E940  38 00 00 61 */	li r0, 0x61
/* 80341D64 0033E944  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341D68 0033E948  3C 60 24 03 */	lis r3, 0x2402C0C6@ha
/* 80341D6C 0033E94C  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341D70 0033E950  38 03 C0 C6 */	addi r0, r3, 0x2402C0C6@l
/* 80341D74 0033E954  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341D78 0033E958  48 00 00 C8 */	b lbl_80341E40
entry lbl_80341D7C
/* 80341D7C 0033E95C  38 00 00 61 */	li r0, 0x61
/* 80341D80 0033E960  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341D84 0033E964  3C 60 24 03 */	lis r3, 0x2402C16B@ha
/* 80341D88 0033E968  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341D8C 0033E96C  38 03 C1 6B */	addi r0, r3, 0x2402C16B@l
/* 80341D90 0033E970  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341D94 0033E974  48 00 00 AC */	b lbl_80341E40
entry lbl_80341D98
/* 80341D98 0033E978  38 00 00 61 */	li r0, 0x61
/* 80341D9C 0033E97C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341DA0 0033E980  3C 60 24 03 */	lis r3, 0x2402C0E7@ha
/* 80341DA4 0033E984  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341DA8 0033E988  38 03 C0 E7 */	addi r0, r3, 0x2402C0E7@l
/* 80341DAC 0033E98C  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341DB0 0033E990  48 00 00 90 */	b lbl_80341E40
entry lbl_80341DB4
/* 80341DB4 0033E994  38 00 00 61 */	li r0, 0x61
/* 80341DB8 0033E998  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341DBC 0033E99C  3C 60 24 03 */	lis r3, 0x2402C108@ha
/* 80341DC0 0033E9A0  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341DC4 0033E9A4  38 03 C1 08 */	addi r0, r3, 0x2402C108@l
/* 80341DC8 0033E9A8  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341DCC 0033E9AC  48 00 00 74 */	b lbl_80341E40
entry lbl_80341DD0
/* 80341DD0 0033E9B0  38 00 00 61 */	li r0, 0x61
/* 80341DD4 0033E9B4  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341DD8 0033E9B8  3C 60 24 03 */	lis r3, 0x2402C129@ha
/* 80341DDC 0033E9BC  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341DE0 0033E9C0  38 03 C1 29 */	addi r0, r3, 0x2402C129@l
/* 80341DE4 0033E9C4  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341DE8 0033E9C8  48 00 00 58 */	b lbl_80341E40
entry lbl_80341DEC
/* 80341DEC 0033E9CC  38 00 00 61 */	li r0, 0x61
/* 80341DF0 0033E9D0  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341DF4 0033E9D4  3C 60 24 03 */	lis r3, 0x2402C14A@ha
/* 80341DF8 0033E9D8  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341DFC 0033E9DC  38 03 C1 4A */	addi r0, r3, 0x2402C14A@l
/* 80341E00 0033E9E0  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341E04 0033E9E4  48 00 00 3C */	b lbl_80341E40
entry lbl_80341E08
/* 80341E08 0033E9E8  38 00 00 61 */	li r0, 0x61
/* 80341E0C 0033E9EC  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341E10 0033E9F0  3C 60 24 03 */	lis r3, 0x2402C1AD@ha
/* 80341E14 0033E9F4  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341E18 0033E9F8  38 03 C1 AD */	addi r0, r3, 0x2402C1AD@l
/* 80341E1C 0033E9FC  90 05 80 00 */	stw r0, -0x8000(r5)
/* 80341E20 0033EA00  48 00 00 20 */	b lbl_80341E40
entry lbl_80341E24
/* 80341E24 0033EA04  38 00 00 10 */	li r0, 0x10
/* 80341E28 0033EA08  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 80341E2C 0033EA0C  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 80341E30 0033EA10  38 60 10 06 */	li r3, 0x1006
/* 80341E34 0033EA14  38 00 00 21 */	li r0, 0x21
/* 80341E38 0033EA18  90 65 80 00 */	stw r3, -0x8000(r5)
/* 80341E3C 0033EA1C  90 05 80 00 */	stw r0, -0x8000(r5)
entry lbl_80341E40
/* 80341E40 0033EA20  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341E44 0033EA24  90 83 04 E4 */	stw r4, 0x4e4(r3)
/* 80341E48 0033EA28  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 80341E4C 0033EA2C  80 04 04 E4 */	lwz r0, 0x4e4(r4)
/* 80341E50 0033EA30  28 00 00 16 */	cmplwi r0, 0x16
/* 80341E54 0033EA34  41 81 03 30 */	bgt lbl_80342184
/* 80341E58 0033EA38  3C 60 80 40 */	lis r3, jtbl_80401528@ha
/* 80341E5C 0033EA3C  38 63 15 28 */	addi r3, r3, jtbl_80401528@l
/* 80341E60 0033EA40  54 00 10 3A */	slwi r0, r0, 2
/* 80341E64 0033EA44  7C 03 00 2E */	lwzx r0, r3, r0
/* 80341E68 0033EA48  7C 09 03 A6 */	mtctr r0
/* 80341E6C 0033EA4C  4E 80 04 20 */	bctr 
entry lbl_80341E70
/* 80341E70 0033EA50  38 00 00 61 */	li r0, 0x61
/* 80341E74 0033EA54  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341E78 0033EA58  3C 60 67 00 */	lis r3, 0x67000042@ha
/* 80341E7C 0033EA5C  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341E80 0033EA60  38 03 00 42 */	addi r0, r3, 0x67000042@l
/* 80341E84 0033EA64  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341E88 0033EA68  48 00 02 FC */	b lbl_80342184
entry lbl_80341E8C
/* 80341E8C 0033EA6C  38 00 00 61 */	li r0, 0x61
/* 80341E90 0033EA70  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341E94 0033EA74  3C 60 67 00 */	lis r3, 0x67000084@ha
/* 80341E98 0033EA78  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341E9C 0033EA7C  38 03 00 84 */	addi r0, r3, 0x67000084@l
/* 80341EA0 0033EA80  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341EA4 0033EA84  48 00 02 E0 */	b lbl_80342184
entry lbl_80341EA8
/* 80341EA8 0033EA88  38 00 00 61 */	li r0, 0x61
/* 80341EAC 0033EA8C  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341EB0 0033EA90  3C 60 67 00 */	lis r3, 0x67000063@ha
/* 80341EB4 0033EA94  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341EB8 0033EA98  38 03 00 63 */	addi r0, r3, 0x67000063@l
/* 80341EBC 0033EA9C  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341EC0 0033EAA0  48 00 02 C4 */	b lbl_80342184
entry lbl_80341EC4
/* 80341EC4 0033EAA4  38 00 00 61 */	li r0, 0x61
/* 80341EC8 0033EAA8  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341ECC 0033EAAC  3C 60 67 00 */	lis r3, 0x67000129@ha
/* 80341ED0 0033EAB0  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341ED4 0033EAB4  38 03 01 29 */	addi r0, r3, 0x67000129@l
/* 80341ED8 0033EAB8  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341EDC 0033EABC  48 00 02 A8 */	b lbl_80342184
entry lbl_80341EE0
/* 80341EE0 0033EAC0  38 00 00 61 */	li r0, 0x61
/* 80341EE4 0033EAC4  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341EE8 0033EAC8  3C 60 67 00 */	lis r3, 0x6700014B@ha
/* 80341EEC 0033EACC  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341EF0 0033EAD0  38 03 01 4B */	addi r0, r3, 0x6700014B@l
/* 80341EF4 0033EAD4  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341EF8 0033EAD8  48 00 02 8C */	b lbl_80342184
entry lbl_80341EFC
/* 80341EFC 0033EADC  38 00 00 61 */	li r0, 0x61
/* 80341F00 0033EAE0  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341F04 0033EAE4  3C 60 67 00 */	lis r3, 0x6700018D@ha
/* 80341F08 0033EAE8  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341F0C 0033EAEC  38 03 01 8D */	addi r0, r3, 0x6700018D@l
/* 80341F10 0033EAF0  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341F14 0033EAF4  48 00 02 70 */	b lbl_80342184
entry lbl_80341F18
/* 80341F18 0033EAF8  38 00 00 61 */	li r0, 0x61
/* 80341F1C 0033EAFC  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341F20 0033EB00  3C 60 67 00 */	lis r3, 0x670001CF@ha
/* 80341F24 0033EB04  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341F28 0033EB08  38 03 01 CF */	addi r0, r3, 0x670001CF@l
/* 80341F2C 0033EB0C  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341F30 0033EB10  48 00 02 54 */	b lbl_80342184
entry lbl_80341F34
/* 80341F34 0033EB14  38 00 00 61 */	li r0, 0x61
/* 80341F38 0033EB18  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341F3C 0033EB1C  3C 60 67 00 */	lis r3, 0x67000211@ha
/* 80341F40 0033EB20  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341F44 0033EB24  38 03 02 11 */	addi r0, r3, 0x67000211@l
/* 80341F48 0033EB28  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341F4C 0033EB2C  48 00 02 38 */	b lbl_80342184
entry lbl_80341F50
/* 80341F50 0033EB30  38 00 00 61 */	li r0, 0x61
/* 80341F54 0033EB34  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341F58 0033EB38  3C 60 67 00 */	lis r3, 0x67000252@ha
/* 80341F5C 0033EB3C  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 80341F60 0033EB40  38 03 02 52 */	addi r0, r3, 0x67000252@l
/* 80341F64 0033EB44  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341F68 0033EB48  48 00 02 1C */	b lbl_80342184
entry lbl_80341F6C
/* 80341F6C 0033EB4C  38 A4 04 E8 */	addi r5, r4, 0x4e8
/* 80341F70 0033EB50  80 04 04 E8 */	lwz r0, 0x4e8(r4)
/* 80341F74 0033EB54  38 60 00 08 */	li r3, 8
/* 80341F78 0033EB58  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341F7C 0033EB5C  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 80341F80 0033EB60  60 00 00 20 */	ori r0, r0, 0x20
/* 80341F84 0033EB64  90 05 00 00 */	stw r0, 0(r5)
/* 80341F88 0033EB68  38 00 00 20 */	li r0, 0x20
/* 80341F8C 0033EB6C  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 80341F90 0033EB70  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341F94 0033EB74  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80341F98 0033EB78  80 03 04 E8 */	lwz r0, 0x4e8(r3)
/* 80341F9C 0033EB7C  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341FA0 0033EB80  48 00 01 E4 */	b lbl_80342184
entry lbl_80341FA4
/* 80341FA4 0033EB84  38 A4 04 E8 */	addi r5, r4, 0x4e8
/* 80341FA8 0033EB88  80 04 04 E8 */	lwz r0, 0x4e8(r4)
/* 80341FAC 0033EB8C  38 60 00 08 */	li r3, 8
/* 80341FB0 0033EB90  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341FB4 0033EB94  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 80341FB8 0033EB98  60 00 00 30 */	ori r0, r0, 0x30
/* 80341FBC 0033EB9C  90 05 00 00 */	stw r0, 0(r5)
/* 80341FC0 0033EBA0  38 00 00 20 */	li r0, 0x20
/* 80341FC4 0033EBA4  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 80341FC8 0033EBA8  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80341FCC 0033EBAC  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80341FD0 0033EBB0  80 03 04 E8 */	lwz r0, 0x4e8(r3)
/* 80341FD4 0033EBB4  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80341FD8 0033EBB8  48 00 01 AC */	b lbl_80342184
entry lbl_80341FDC
/* 80341FDC 0033EBBC  38 A4 04 E8 */	addi r5, r4, 0x4e8
/* 80341FE0 0033EBC0  80 04 04 E8 */	lwz r0, 0x4e8(r4)
/* 80341FE4 0033EBC4  38 60 00 08 */	li r3, 8
/* 80341FE8 0033EBC8  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80341FEC 0033EBCC  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 80341FF0 0033EBD0  60 00 00 40 */	ori r0, r0, 0x40
/* 80341FF4 0033EBD4  90 05 00 00 */	stw r0, 0(r5)
/* 80341FF8 0033EBD8  38 00 00 20 */	li r0, 0x20
/* 80341FFC 0033EBDC  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 80342000 0033EBE0  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80342004 0033EBE4  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80342008 0033EBE8  80 03 04 E8 */	lwz r0, 0x4e8(r3)
/* 8034200C 0033EBEC  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80342010 0033EBF0  48 00 01 74 */	b lbl_80342184
entry lbl_80342014
/* 80342014 0033EBF4  38 A4 04 E8 */	addi r5, r4, 0x4e8
/* 80342018 0033EBF8  80 04 04 E8 */	lwz r0, 0x4e8(r4)
/* 8034201C 0033EBFC  38 60 00 08 */	li r3, 8
/* 80342020 0033EC00  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80342024 0033EC04  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 80342028 0033EC08  60 00 00 50 */	ori r0, r0, 0x50
/* 8034202C 0033EC0C  90 05 00 00 */	stw r0, 0(r5)
/* 80342030 0033EC10  38 00 00 20 */	li r0, 0x20
/* 80342034 0033EC14  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 80342038 0033EC18  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8034203C 0033EC1C  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80342040 0033EC20  80 03 04 E8 */	lwz r0, 0x4e8(r3)
/* 80342044 0033EC24  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80342048 0033EC28  48 00 01 3C */	b lbl_80342184
entry lbl_8034204C
/* 8034204C 0033EC2C  38 A4 04 E8 */	addi r5, r4, 0x4e8
/* 80342050 0033EC30  80 04 04 E8 */	lwz r0, 0x4e8(r4)
/* 80342054 0033EC34  38 60 00 08 */	li r3, 8
/* 80342058 0033EC38  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8034205C 0033EC3C  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 80342060 0033EC40  60 00 00 60 */	ori r0, r0, 0x60
/* 80342064 0033EC44  90 05 00 00 */	stw r0, 0(r5)
/* 80342068 0033EC48  38 00 00 20 */	li r0, 0x20
/* 8034206C 0033EC4C  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 80342070 0033EC50  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80342074 0033EC54  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80342078 0033EC58  80 03 04 E8 */	lwz r0, 0x4e8(r3)
/* 8034207C 0033EC5C  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80342080 0033EC60  48 00 01 04 */	b lbl_80342184
entry lbl_80342084
/* 80342084 0033EC64  38 A4 04 E8 */	addi r5, r4, 0x4e8
/* 80342088 0033EC68  80 04 04 E8 */	lwz r0, 0x4e8(r4)
/* 8034208C 0033EC6C  38 60 00 08 */	li r3, 8
/* 80342090 0033EC70  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80342094 0033EC74  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 80342098 0033EC78  60 00 00 70 */	ori r0, r0, 0x70
/* 8034209C 0033EC7C  90 05 00 00 */	stw r0, 0(r5)
/* 803420A0 0033EC80  38 00 00 20 */	li r0, 0x20
/* 803420A4 0033EC84  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 803420A8 0033EC88  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 803420AC 0033EC8C  98 04 80 00 */	stb r0, -0x8000(r4)
/* 803420B0 0033EC90  80 03 04 E8 */	lwz r0, 0x4e8(r3)
/* 803420B4 0033EC94  90 04 80 00 */	stw r0, -0x8000(r4)
/* 803420B8 0033EC98  48 00 00 CC */	b lbl_80342184
entry lbl_803420BC
/* 803420BC 0033EC9C  38 A4 04 E8 */	addi r5, r4, 0x4e8
/* 803420C0 0033ECA0  80 04 04 E8 */	lwz r0, 0x4e8(r4)
/* 803420C4 0033ECA4  38 60 00 08 */	li r3, 8
/* 803420C8 0033ECA8  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 803420CC 0033ECAC  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 803420D0 0033ECB0  60 00 00 90 */	ori r0, r0, 0x90
/* 803420D4 0033ECB4  90 05 00 00 */	stw r0, 0(r5)
/* 803420D8 0033ECB8  38 00 00 20 */	li r0, 0x20
/* 803420DC 0033ECBC  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 803420E0 0033ECC0  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 803420E4 0033ECC4  98 04 80 00 */	stb r0, -0x8000(r4)
/* 803420E8 0033ECC8  80 03 04 E8 */	lwz r0, 0x4e8(r3)
/* 803420EC 0033ECCC  90 04 80 00 */	stw r0, -0x8000(r4)
/* 803420F0 0033ECD0  48 00 00 94 */	b lbl_80342184
entry lbl_803420F4
/* 803420F4 0033ECD4  38 A4 04 E8 */	addi r5, r4, 0x4e8
/* 803420F8 0033ECD8  80 04 04 E8 */	lwz r0, 0x4e8(r4)
/* 803420FC 0033ECDC  38 60 00 08 */	li r3, 8
/* 80342100 0033ECE0  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80342104 0033ECE4  54 00 07 2E */	rlwinm r0, r0, 0, 0x1c, 0x17
/* 80342108 0033ECE8  60 00 00 80 */	ori r0, r0, 0x80
/* 8034210C 0033ECEC  90 05 00 00 */	stw r0, 0(r5)
/* 80342110 0033ECF0  38 00 00 20 */	li r0, 0x20
/* 80342114 0033ECF4  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 80342118 0033ECF8  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8034211C 0033ECFC  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80342120 0033ED00  80 03 04 E8 */	lwz r0, 0x4e8(r3)
/* 80342124 0033ED04  90 04 80 00 */	stw r0, -0x8000(r4)
/* 80342128 0033ED08  48 00 00 5C */	b lbl_80342184
entry lbl_8034212C
/* 8034212C 0033ED0C  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 80342130 0033ED10  38 00 00 02 */	li r0, 2
/* 80342134 0033ED14  B0 03 00 06 */	sth r0, 6(r3)
/* 80342138 0033ED18  48 00 00 4C */	b lbl_80342184
entry lbl_8034213C
/* 8034213C 0033ED1C  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 80342140 0033ED20  38 00 00 03 */	li r0, 3
/* 80342144 0033ED24  B0 03 00 06 */	sth r0, 6(r3)
/* 80342148 0033ED28  48 00 00 3C */	b lbl_80342184
entry lbl_8034214C
/* 8034214C 0033ED2C  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 80342150 0033ED30  38 00 00 04 */	li r0, 4
/* 80342154 0033ED34  B0 03 00 06 */	sth r0, 6(r3)
/* 80342158 0033ED38  48 00 00 2C */	b lbl_80342184
entry lbl_8034215C
/* 8034215C 0033ED3C  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 80342160 0033ED40  38 00 00 05 */	li r0, 5
/* 80342164 0033ED44  B0 03 00 06 */	sth r0, 6(r3)
/* 80342168 0033ED48  48 00 00 1C */	b lbl_80342184
entry lbl_8034216C
/* 8034216C 0033ED4C  38 00 00 61 */	li r0, 0x61
/* 80342170 0033ED50  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80342174 0033ED54  3C 60 67 00 */	lis r3, 0x67000021@ha
/* 80342178 0033ED58  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 8034217C 0033ED5C  38 03 00 21 */	addi r0, r3, 0x67000021@l
/* 80342180 0033ED60  90 04 80 00 */	stw r0, -0x8000(r4)
entry lbl_80342184
/* 80342184 0033ED64  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 80342188 0033ED68  38 00 00 00 */	li r0, 0
/* 8034218C 0033ED6C  B0 03 00 02 */	sth r0, 2(r3)
/* 80342190 0033ED70  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void GXClearGPMetric(void)
{
    __cpReg[2] = 4;
}
