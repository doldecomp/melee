#include "ftkoopa.h"

extern void* func_800BC7E0(struct HSD_GObj*);
extern void* func_801330E4(struct HSD_GObj*);
extern void* func_800BC8D4(struct HSD_GObj*);
extern void* func_80134D78(struct HSD_GObj*);
extern void* func_800DE7C0();
extern void* func_800DE2A8();
extern void* func_8007E2F4();

extern const f32 lbl_804D9AC8; //3.0
extern const f32 lbl_804D9ACC; //0.0
extern const f32 lbl_804D9ADC; //1.0
extern const f32 lbl_804D9AD8; //0.0

asm void ftKoopa_OnDeath(HSD_GObj* gobj) {
    nofralloc
/* 80132A0C 0012F5EC  7C 08 02 A6 */	mflr r0
/* 80132A10 0012F5F0  38 80 00 00 */	li r4, 0
/* 80132A14 0012F5F4  90 01 00 04 */	stw r0, 4(r1)
/* 80132A18 0012F5F8  38 A0 00 00 */	li r5, 0
/* 80132A1C 0012F5FC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80132A20 0012F600  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80132A24 0012F604  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80132A28 0012F608  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80132A2C 0012F60C  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 80132A30 0012F610  4B F4 20 1D */	bl func_80074A4C
/* 80132A34 0012F614  C0 1E 00 00 */	lfs f0, 0(r30)
/* 80132A38 0012F618  D0 1F 18 B0 */	stfs f0, 0x18b0(r31)
/* 80132A3C 0012F61C  C0 1E 00 10 */	lfs f0, 0x10(r30)
/* 80132A40 0012F620  D0 1F 22 2C */	stfs f0, 0x222c(r31)
/* 80132A44 0012F624  C0 1E 00 18 */	lfs f0, 0x18(r30)
/* 80132A48 0012F628  D0 1F 22 30 */	stfs f0, 0x2230(r31)
/* 80132A4C 0012F62C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80132A50 0012F630  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80132A54 0012F634  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80132A58 0012F638  38 21 00 20 */	addi r1, r1, 0x20
/* 80132A5C 0012F63C  7C 08 03 A6 */	mtlr r0
/* 80132A60 0012F640  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_80132A64(HSD_GObj* gobj) {
    nofralloc
/* 80132A64 0012F644  7C 08 02 A6 */	mflr r0
/* 80132A68 0012F648  90 01 00 04 */	stw r0, 4(r1)
/* 80132A6C 0012F64C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80132A70 0012F650  48 00 23 09 */	bl func_80134D78
/* 80132A74 0012F654  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80132A78 0012F658  38 21 00 08 */	addi r1, r1, 8
/* 80132A7C 0012F65C  7C 08 03 A6 */	mtlr r0
/* 80132A80 0012F660  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_80132A84(Fighter* fighter) {
    nofralloc
/* 80132A84 0012F664  80 83 01 0C */	lwz r4, 0x10c(r3)
/* 80132A88 0012F668  38 00 00 14 */	li r0, 0x14
/* 80132A8C 0012F66C  80 E3 02 D8 */	lwz r7, 0x2d8(r3)
/* 80132A90 0012F670  7C 09 03 A6 */	mtctr r0
/* 80132A94 0012F674  80 84 00 04 */	lwz r4, 4(r4)
/* 80132A98 0012F678  38 C7 FF F8 */	addi r6, r7, -8
/* 80132A9C 0012F67C  38 A4 FF F8 */	addi r5, r4, -8
lbl_80132AA0:
/* 80132AA0 0012F680  84 85 00 08 */	lwzu r4, 8(r5)
/* 80132AA4 0012F684  80 05 00 04 */	lwz r0, 4(r5)
/* 80132AA8 0012F688  94 86 00 08 */	stwu r4, 8(r6)
/* 80132AAC 0012F68C  90 06 00 04 */	stw r0, 4(r6)
/* 80132AB0 0012F690  42 00 FF F0 */	bdnz lbl_80132AA0
/* 80132AB4 0012F694  90 E3 02 D4 */	stw r7, 0x2d4(r3)
/* 80132AB8 0012F698  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void ftKoopa_OnLoad(HSD_GObj* gobj) {
    nofralloc
/* 80132ABC 0012F69C  7C 08 02 A6 */	mflr r0
/* 80132AC0 0012F6A0  90 01 00 04 */	stw r0, 4(r1)
/* 80132AC4 0012F6A4  38 00 00 14 */	li r0, 0x14
/* 80132AC8 0012F6A8  7C 09 03 A6 */	mtctr r0
/* 80132ACC 0012F6AC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80132AD0 0012F6B0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80132AD4 0012F6B4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80132AD8 0012F6B8  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80132ADC 0012F6BC  80 DF 02 D8 */	lwz r6, 0x2d8(r31)
/* 80132AE0 0012F6C0  80 64 00 04 */	lwz r3, 4(r4)
/* 80132AE4 0012F6C4  80 E4 00 48 */	lwz r7, 0x48(r4)
/* 80132AE8 0012F6C8  38 A6 FF F8 */	addi r5, r6, -8
/* 80132AEC 0012F6CC  38 83 FF F8 */	addi r4, r3, -8
lbl_80132AF0:
/* 80132AF0 0012F6D0  84 64 00 08 */	lwzu r3, 8(r4)
/* 80132AF4 0012F6D4  80 04 00 04 */	lwz r0, 4(r4)
/* 80132AF8 0012F6D8  94 65 00 08 */	stwu r3, 8(r5)
/* 80132AFC 0012F6DC  90 05 00 04 */	stw r0, 4(r5)
/* 80132B00 0012F6E0  42 00 FF F0 */	bdnz lbl_80132AF0
/* 80132B04 0012F6E4  90 DF 02 D4 */	stw r6, 0x2d4(r31)
/* 80132B08 0012F6E8  38 80 00 64 */	li r4, 0x64
/* 80132B0C 0012F6EC  80 67 00 00 */	lwz r3, 0(r7)
/* 80132B10 0012F6F0  48 13 88 E9 */	bl func_8026B3F8
/* 80132B14 0012F6F4  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 80132B18 0012F6F8  38 60 00 01 */	li r3, 1
/* 80132B1C 0012F6FC  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 80132B20 0012F700  98 1F 22 26 */	stb r0, 0x2226(r31)
/* 80132B24 0012F704  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80132B28 0012F708  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80132B2C 0012F70C  38 21 00 20 */	addi r1, r1, 0x20
/* 80132B30 0012F710  7C 08 03 A6 */	mtlr r0
/* 80132B34 0012F714  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_80132B38() {
    nofralloc
    /* 80132B38 0012F718  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_80132B3C() {
    nofralloc
/* 80132B3C 0012F71C  7C 08 02 A6 */	mflr r0
/* 80132B40 0012F720  90 01 00 04 */	stw r0, 4(r1)
/* 80132B44 0012F724  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80132B48 0012F728  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80132B4C 0012F72C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80132B50 0012F730  7C 9E 23 78 */	mr r30, r4
/* 80132B54 0012F734  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80132B58 0012F738  7C 7D 1B 78 */	mr r29, r3
/* 80132B5C 0012F73C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80132B60 0012F740  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80132B64 0012F744  48 13 87 51 */	bl func_8026B2B4
/* 80132B68 0012F748  2C 03 00 00 */	cmpwi r3, 0
/* 80132B6C 0012F74C  40 82 00 94 */	bne lbl_80132C00
/* 80132B70 0012F750  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 80132B74 0012F754  48 13 87 AD */	bl func_8026B320
/* 80132B78 0012F758  2C 03 00 03 */	cmpwi r3, 3
/* 80132B7C 0012F75C  41 82 00 4C */	beq lbl_80132BC8
/* 80132B80 0012F760  40 80 00 14 */	bge lbl_80132B94
/* 80132B84 0012F764  2C 03 00 01 */	cmpwi r3, 1
/* 80132B88 0012F768  41 82 00 18 */	beq lbl_80132BA0
/* 80132B8C 0012F76C  40 80 00 28 */	bge lbl_80132BB4
/* 80132B90 0012F770  48 00 00 5C */	b lbl_80132BEC
lbl_80132B94:
/* 80132B94 0012F774  2C 03 00 05 */	cmpwi r3, 5
/* 80132B98 0012F778  40 80 00 54 */	bge lbl_80132BEC
/* 80132B9C 0012F77C  48 00 00 40 */	b lbl_80132BDC
lbl_80132BA0:
/* 80132BA0 0012F780  38 7D 00 00 */	addi r3, r29, 0
/* 80132BA4 0012F784  38 80 00 01 */	li r4, 1
/* 80132BA8 0012F788  38 A0 00 01 */	li r5, 1
/* 80132BAC 0012F78C  4B F3 E4 09 */	bl func_80070FB4
/* 80132BB0 0012F790  48 00 00 3C */	b lbl_80132BEC
lbl_80132BB4:
/* 80132BB4 0012F794  38 7D 00 00 */	addi r3, r29, 0
/* 80132BB8 0012F798  38 80 00 01 */	li r4, 1
/* 80132BBC 0012F79C  38 A0 00 00 */	li r5, 0
/* 80132BC0 0012F7A0  4B F3 E3 F5 */	bl func_80070FB4
/* 80132BC4 0012F7A4  48 00 00 28 */	b lbl_80132BEC
lbl_80132BC8:
/* 80132BC8 0012F7A8  38 7D 00 00 */	addi r3, r29, 0
/* 80132BCC 0012F7AC  38 80 00 01 */	li r4, 1
/* 80132BD0 0012F7B0  38 A0 00 02 */	li r5, 2
/* 80132BD4 0012F7B4  4B F3 E3 E1 */	bl func_80070FB4
/* 80132BD8 0012F7B8  48 00 00 14 */	b lbl_80132BEC
lbl_80132BDC:
/* 80132BDC 0012F7BC  38 7D 00 00 */	addi r3, r29, 0
/* 80132BE0 0012F7C0  38 80 00 01 */	li r4, 1
/* 80132BE4 0012F7C4  38 A0 00 03 */	li r5, 3
/* 80132BE8 0012F7C8  4B F3 E3 CD */	bl func_80070FB4
lbl_80132BEC:
/* 80132BEC 0012F7CC  2C 1E 00 00 */	cmpwi r30, 0
/* 80132BF0 0012F7D0  41 82 00 10 */	beq lbl_80132C00
/* 80132BF4 0012F7D4  38 7D 00 00 */	addi r3, r29, 0
/* 80132BF8 0012F7D8  38 80 00 01 */	li r4, 1
/* 80132BFC 0012F7DC  4B F3 E0 4D */	bl func_80070C48
lbl_80132C00:
/* 80132C00 0012F7E0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80132C04 0012F7E4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80132C08 0012F7E8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80132C0C 0012F7EC  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80132C10 0012F7F0  38 21 00 28 */	addi r1, r1, 0x28
/* 80132C14 0012F7F4  7C 08 03 A6 */	mtlr r0
/* 80132C18 0012F7F8  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_80132C1C() {
    nofralloc
/* 80132C1C 0012F7FC  7C 08 02 A6 */	mflr r0
/* 80132C20 0012F800  90 01 00 04 */	stw r0, 4(r1)
/* 80132C24 0012F804  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80132C28 0012F808  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80132C2C 0012F80C  7C 7F 1B 78 */	mr r31, r3
/* 80132C30 0012F810  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80132C34 0012F814  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 80132C38 0012F818  48 13 86 7D */	bl func_8026B2B4
/* 80132C3C 0012F81C  2C 03 00 00 */	cmpwi r3, 0
/* 80132C40 0012F820  40 82 00 10 */	bne lbl_80132C50
/* 80132C44 0012F824  38 7F 00 00 */	addi r3, r31, 0
/* 80132C48 0012F828  38 80 00 01 */	li r4, 1
/* 80132C4C 0012F82C  4B F3 E0 79 */	bl func_80070CC4
lbl_80132C50:
/* 80132C50 0012F830  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80132C54 0012F834  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80132C58 0012F838  38 21 00 18 */	addi r1, r1, 0x18
/* 80132C5C 0012F83C  7C 08 03 A6 */	mtlr r0
/* 80132C60 0012F840  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_80132C64() {
    nofralloc
/* 80132C64 0012F844  7C 08 02 A6 */	mflr r0
/* 80132C68 0012F848  90 01 00 04 */	stw r0, 4(r1)
/* 80132C6C 0012F84C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80132C70 0012F850  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80132C74 0012F854  7C 7F 1B 78 */	mr r31, r3
/* 80132C78 0012F858  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80132C7C 0012F85C  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 80132C80 0012F860  48 13 86 35 */	bl func_8026B2B4
/* 80132C84 0012F864  2C 03 00 00 */	cmpwi r3, 0
/* 80132C88 0012F868  40 82 00 10 */	bne lbl_80132C98
/* 80132C8C 0012F86C  38 7F 00 00 */	addi r3, r31, 0
/* 80132C90 0012F870  38 80 00 01 */	li r4, 1
/* 80132C94 0012F874  4B F3 DF B5 */	bl func_80070C48
lbl_80132C98:
/* 80132C98 0012F878  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80132C9C 0012F87C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80132CA0 0012F880  38 21 00 18 */	addi r1, r1, 0x18
/* 80132CA4 0012F884  7C 08 03 A6 */	mtlr r0
/* 80132CA8 0012F888  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_80132CAC() {
    nofralloc
/* 80132CAC 0012F88C  7C 08 02 A6 */	mflr r0
/* 80132CB0 0012F890  38 A0 FF FF */	li r5, -1
/* 80132CB4 0012F894  90 01 00 04 */	stw r0, 4(r1)
/* 80132CB8 0012F898  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80132CBC 0012F89C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80132CC0 0012F8A0  3B E4 00 00 */	addi r31, r4, 0
/* 80132CC4 0012F8A4  38 80 00 01 */	li r4, 1
/* 80132CC8 0012F8A8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80132CCC 0012F8AC  3B C3 00 00 */	addi r30, r3, 0
/* 80132CD0 0012F8B0  4B F3 E2 E5 */	bl func_80070FB4
/* 80132CD4 0012F8B4  2C 1F 00 00 */	cmpwi r31, 0
/* 80132CD8 0012F8B8  41 82 00 10 */	beq lbl_80132CE8
/* 80132CDC 0012F8BC  38 7E 00 00 */	addi r3, r30, 0
/* 80132CE0 0012F8C0  38 80 00 01 */	li r4, 1
/* 80132CE4 0012F8C4  4B F3 DF E1 */	bl func_80070CC4
lbl_80132CE8:
/* 80132CE8 0012F8C8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80132CEC 0012F8CC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80132CF0 0012F8D0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80132CF4 0012F8D4  38 21 00 18 */	addi r1, r1, 0x18
/* 80132CF8 0012F8D8  7C 08 03 A6 */	mtlr r0
/* 80132CFC 0012F8DC  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_80132D00() {
    nofralloc
/* 80132D00 0012F8E0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80132D04 0012F8E4  38 00 00 14 */	li r0, 0x14
/* 80132D08 0012F8E8  7C 09 03 A6 */	mtctr r0
/* 80132D0C 0012F8EC  80 83 01 0C */	lwz r4, 0x10c(r3)
/* 80132D10 0012F8F0  80 63 02 D4 */	lwz r3, 0x2d4(r3)
/* 80132D14 0012F8F4  80 84 00 04 */	lwz r4, 4(r4)
/* 80132D18 0012F8F8  38 A3 FF F8 */	addi r5, r3, -8
/* 80132D1C 0012F8FC  38 84 FF F8 */	addi r4, r4, -8
lbl_80132D20:
/* 80132D20 0012F900  84 64 00 08 */	lwzu r3, 8(r4)
/* 80132D24 0012F904  80 04 00 04 */	lwz r0, 4(r4)
/* 80132D28 0012F908  94 65 00 08 */	stwu r3, 8(r5)
/* 80132D2C 0012F90C  90 05 00 04 */	stw r0, 4(r5)
/* 80132D30 0012F910  42 00 FF F0 */	bdnz lbl_80132D20
/* 80132D34 0012F914  4E 80 00 20 */	blr 
}
#pragma peephole on

void func_80132D38(HSD_GObj *gobj) {
    func_800704F0(gobj, 1, lbl_804D9AC8);
    func_800704F0(gobj, 0, lbl_804D9AC8);
    return;
}

void func_80132D7C(HSD_GObj *gobj) {
    func_800704F0(gobj, 1, lbl_804D9ACC);
    func_800704F0(gobj, 0, lbl_804D9ACC);
    return;
}

f32 func_80132DC0(HSD_GObj *gobj) {
    Fighter *ft = gobj->user_data;
    return ((ftKoopaAttributes*)ft->x2D4_specialAttributes)->unk4C;
}

f32 func_80132DD0(HSD_GObj *gobj) {
    Fighter *ft = gobj->user_data;
    return ((ftKoopaAttributes*)ft->x2D4_specialAttributes)->unk48;
}

f32 func_80132DE0(HSD_GObj *gobj) {
    Fighter *ft = gobj->user_data;
    return ((ftKoopaAttributes*)ft->x2D4_specialAttributes)->unk44;
}

f32 func_80132DF0(HSD_GObj *gobj) {
    Fighter *ft = gobj->user_data;
    return ((ftKoopaAttributes*)ft->x2D4_specialAttributes)->unk40;
}

f32 func_80132E00(HSD_GObj *gobj) {
    Fighter *ft = gobj->user_data;
    return ((ftKoopaAttributes*)ft->x2D4_specialAttributes)->unk3C;
}

f32 func_80132E10(HSD_GObj *gobj) {
    Fighter *ft = gobj->user_data;
    return ((ftKoopaAttributes*)ft->x2D4_specialAttributes)->unk34;
}

f32 func_80132E20(HSD_GObj *gobj) {
    Fighter *ft = gobj->user_data;
    return ((ftKoopaAttributes*)ft->x2D4_specialAttributes)->unk38;
}

asm void func_80132E30() {
    nofralloc
/* 80132E30 0012FA10  7C 08 02 A6 */	mflr r0
/* 80132E34 0012FA14  90 01 00 04 */	stw r0, 4(r1)
/* 80132E38 0012FA18  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80132E3C 0012FA1C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80132E40 0012FA20  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80132E44 0012FA24  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80132E48 0012FA28  7C 7D 1B 78 */	mr r29, r3
/* 80132E4C 0012FA2C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80132E50 0012FA30  88 64 22 10 */	lbz r3, 0x2210(r4)
/* 80132E54 0012FA34  3B E4 00 00 */	addi r31, r4, 0
/* 80132E58 0012FA38  54 60 EF FF */	rlwinm. r0, r3, 0x1d, 0x1f, 0x1f
/* 80132E5C 0012FA3C  41 82 00 18 */	beq lbl_80132E74
/* 80132E60 0012FA40  38 00 00 00 */	li r0, 0
/* 80132E64 0012FA44  50 03 1F 38 */	rlwimi r3, r0, 3, 0x1c, 0x1c
/* 80132E68 0012FA48  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 80132E6C 0012FA4C  38 00 00 01 */	li r0, 1
/* 80132E70 0012FA50  48 00 00 08 */	b lbl_80132E78
lbl_80132E74:
/* 80132E74 0012FA54  38 00 00 00 */	li r0, 0
lbl_80132E78:
/* 80132E78 0012FA58  2C 00 00 00 */	cmpwi r0, 0
/* 80132E7C 0012FA5C  41 82 00 18 */	beq lbl_80132E94
/* 80132E80 0012FA60  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80132E84 0012FA64  38 00 00 01 */	li r0, 1
/* 80132E88 0012FA68  FC 00 00 50 */	fneg f0, f0
/* 80132E8C 0012FA6C  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 80132E90 0012FA70  90 1F 23 4C */	stw r0, 0x234c(r31)
lbl_80132E94:
/* 80132E94 0012FA74  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 80132E98 0012FA78  28 00 00 00 */	cmplwi r0, 0
/* 80132E9C 0012FA7C  41 82 00 44 */	beq lbl_80132EE0
/* 80132EA0 0012FA80  80 1F 1A 58 */	lwz r0, 0x1a58(r31)
/* 80132EA4 0012FA84  28 00 00 00 */	cmplwi r0, 0
/* 80132EA8 0012FA88  41 82 00 38 */	beq lbl_80132EE0
/* 80132EAC 0012FA8C  7C 1E 03 78 */	mr r30, r0
/* 80132EB0 0012FA90  38 7F 00 00 */	addi r3, r31, 0
/* 80132EB4 0012FA94  38 80 00 00 */	li r4, 0
/* 80132EB8 0012FA98  4B F4 B4 3D */	bl func_8007E2F4
/* 80132EBC 0012FA9C  38 7D 00 00 */	addi r3, r29, 0
/* 80132EC0 0012FAA0  38 9E 00 00 */	addi r4, r30, 0
/* 80132EC4 0012FAA4  4B FA B3 E5 */	bl func_800DE2A8
/* 80132EC8 0012FAA8  38 7E 00 00 */	addi r3, r30, 0
/* 80132ECC 0012FAAC  38 80 00 00 */	li r4, 0
/* 80132ED0 0012FAB0  38 A0 00 00 */	li r5, 0
/* 80132ED4 0012FAB4  4B FA B8 ED */	bl func_800DE7C0
/* 80132ED8 0012FAB8  38 00 00 00 */	li r0, 0
/* 80132EDC 0012FABC  90 1F 22 00 */	stw r0, 0x2200(r31)
lbl_80132EE0:
/* 80132EE0 0012FAC0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80132EE4 0012FAC4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80132EE8 0012FAC8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80132EEC 0012FACC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80132EF0 0012FAD0  38 21 00 20 */	addi r1, r1, 0x20
/* 80132EF4 0012FAD4  7C 08 03 A6 */	mtlr r0
/* 80132EF8 0012FAD8  4E 80 00 20 */	blr 
}
#pragma peephole on

void func_80132EFC(HSD_GObj *gobj)
{
    Fighter *ft = gobj->user_data;

    f64 unk = 0.0;

    ft->x2210_ThrowFlags.flags = 0;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2344_stateVar2 = 0;
    ft->x234C_stateVar4 = 0;

    func_800693AC(gobj, 0x15B, 0, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);

    func_8006EBA4(gobj);

    ft = gobj->user_data;

    func_8007E2D0(ft, 8, func_8013302C, 0, func_800BC7E0);

    ft->x2340_stateVar1 = 0;
    ft->x2348_stateVar3 = 0;

    return;
}

void func_80132F94(HSD_GObj *gobj)
{
    Fighter *ft = gobj->user_data;

    f64 unk = 0.0;

    ft->x2210_ThrowFlags.flags = 0;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2344_stateVar2 = 0;
    ft->x234C_stateVar4 = 0;

    func_800693AC(gobj, 0x161, 0, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);

    func_8006EBA4(gobj);

    ft = gobj->user_data;

    func_8007E2D0(ft, 8, func_801330E4, 0, func_800BC8D4);

    ft->x2340_stateVar1 = 0;
    ft->x2348_stateVar3 = 0;

    return;
}

// void func_8013302C(HSD_GObj *gobj)
// {
//     Fighter *ft = gobj->user_data;

//     if(ft->x2344_stateVar2 != 0) {
//         func_800693AC(gobj, 349, 0x80, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
//     } else {
//         func_800693AC(gobj, 348, 0x0, 0, lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
//     }
//     ft->x2222_flag.bits.b0 = 1;
//     func_8007E2F4(ft, 0x1FF);
//     func_8007E2FC(gobj);
//     ft->x2340_stateVar1 = 0;
//     ft->x2200_ftcmd_var.x0_flag0 = 0;
//     return;
// }