#include "ftgigakoopa.h"

asm void ftGKoopa_OnDeath()
{
    nofralloc
/* 8014F640 0014C220  7C 08 02 A6 */	mflr r0
/* 8014F644 0014C224  38 80 00 00 */	li r4, 0
/* 8014F648 0014C228  90 01 00 04 */	stw r0, 4(r1)
/* 8014F64C 0014C22C  38 A0 00 00 */	li r5, 0
/* 8014F650 0014C230  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8014F654 0014C234  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8014F658 0014C238  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8014F65C 0014C23C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8014F660 0014C240  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8014F664 0014C244  4B F2 53 E9 */	bl func_80074A4C
/* 8014F668 0014C248  C0 1E 00 00 */	lfs f0, 0(r30)
/* 8014F66C 0014C24C  D0 1F 18 B0 */	stfs f0, 0x18b0(r31)
/* 8014F670 0014C250  C0 1E 00 10 */	lfs f0, 0x10(r30)
/* 8014F674 0014C254  D0 1F 22 2C */	stfs f0, 0x222c(r31)
/* 8014F678 0014C258  C0 1E 00 18 */	lfs f0, 0x18(r30)
/* 8014F67C 0014C25C  D0 1F 22 30 */	stfs f0, 0x2230(r31)
/* 8014F680 0014C260  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8014F684 0014C264  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8014F688 0014C268  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8014F68C 0014C26C  38 21 00 20 */	addi r1, r1, 0x20
/* 8014F690 0014C270  7C 08 03 A6 */	mtlr r0
/* 8014F694 0014C274  4E 80 00 20 */	blr
}

#pragma peephole on

void func_8014F698(HSD_GObj* gobj)
{
    func_80132A64(gobj);
}

void ftGKoopa_OnLoad(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    ftData* ftdata = ft->x10C_ftData;
    void** items = ftdata->x48_items;

    func_80132A84(ft);
    func_8026B3F8(items[0], 0x64);

    ft->x2226_flag.bits.b1 = 1;
    ft->x222A_flag.bits.b0 = 1;
}

void func_8014F720(HSD_GObj* gobj, s32 arg1)
{
    s32 switched_res, result, unused;

    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);

    if (result == 0) {
        switched_res = func_8026B320(ft->x1974_heldItem);
        switch (switched_res) {
        case 1:
            func_80070FB4(gobj, 1, 1);
            break;
        case 2:
            func_80070FB4(gobj, 1, 0);
            break;
        case 3:
            func_80070FB4(gobj, 1, 2);
            break;
        case 4:
            func_80070FB4(gobj, 1, 3);
            break;
        }

        if (arg1 != 0) {
            func_80070C48(gobj, 1);
        }
    }
}

void func_8014F800(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_8014F848(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;
    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_8014F890(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_8014F8E4(HSD_GObj* gobj)
{
    func_80132D00(gobj);
}

void func_8014F904(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_8014F948(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void func_8014F98C(s32 arg0, s32* arg1, s32* arg2)
{
    if (arg0 == 0xF) {
        *arg2 = 0xE;
        *arg1 = 0xE;
    }
}

// UB warning: this function may use offset uninitialized
s32 func_8014F9A4(s32 arg0)
{
    int offset;
    const s32* ret;

    switch (arg0) {
        case 0xf:
            offset = 0xe;
    }

    return lbl_803D3984[offset - 0xe];
}
