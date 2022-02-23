#include "ftness.h"

void ftNess_OnDeath(HSD_GObj* gobj, s32 arg1)
{
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->x2240 = 0;
    ft->x2244 = 0;
    ft->x2248 = 0;
    ft->x222C = 0;
    ft->x224C = 0;
}

asm void ftNess_OnLoad(HSD_GObj* gobj)
{
    nofralloc
/* 8011480C 001113EC  7C 08 02 A6 */	mflr r0
/* 80114810 001113F0  90 01 00 04 */	stw r0, 4(r1)
/* 80114814 001113F4  38 00 00 1B */	li r0, 0x1b
/* 80114818 001113F8  7C 09 03 A6 */	mtctr r0
/* 8011481C 001113FC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80114820 00111400  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80114824 00111404  80 E3 00 2C */	lwz r7, 0x2c(r3)
/* 80114828 00111408  80 87 01 0C */	lwz r4, 0x10c(r7)
/* 8011482C 0011140C  80 C7 02 D8 */	lwz r6, 0x2d8(r7)
/* 80114830 00111410  80 64 00 04 */	lwz r3, 4(r4)
/* 80114834 00111414  83 E4 00 48 */	lwz r31, 0x48(r4)
/* 80114838 00111418  38 A6 FF F8 */	addi r5, r6, -8
/* 8011483C 0011141C  38 83 FF F8 */	addi r4, r3, -8
lbl_80114840:
/* 80114840 00111420  84 64 00 08 */	lwzu r3, 8(r4)
/* 80114844 00111424  80 04 00 04 */	lwz r0, 4(r4)
/* 80114848 00111428  94 65 00 08 */	stwu r3, 8(r5)
/* 8011484C 0011142C  90 05 00 04 */	stw r0, 4(r5)
/* 80114850 00111430  42 00 FF F0 */	bdnz lbl_80114840
/* 80114854 00111434  80 04 00 08 */	lwz r0, 8(r4)
/* 80114858 00111438  38 80 00 42 */	li r4, 0x42
/* 8011485C 0011143C  90 05 00 08 */	stw r0, 8(r5)
/* 80114860 00111440  90 C7 02 D4 */	stw r6, 0x2d4(r7)
/* 80114864 00111444  80 7F 00 00 */	lwz r3, 0(r31)
/* 80114868 00111448  48 15 6B 91 */	bl func_8026B3F8
/* 8011486C 0011144C  80 7F 00 04 */	lwz r3, 4(r31)
/* 80114870 00111450  38 80 00 43 */	li r4, 0x43
/* 80114874 00111454  48 15 6B 85 */	bl func_8026B3F8
/* 80114878 00111458  80 7F 00 08 */	lwz r3, 8(r31)
/* 8011487C 0011145C  38 80 00 44 */	li r4, 0x44
/* 80114880 00111460  48 15 6B 79 */	bl func_8026B3F8
/* 80114884 00111464  80 7F 00 20 */	lwz r3, 0x20(r31)
/* 80114888 00111468  38 80 00 4E */	li r4, 0x4e
/* 8011488C 0011146C  48 15 6B 6D */	bl func_8026B3F8
/* 80114890 00111470  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 80114894 00111474  38 80 00 45 */	li r4, 0x45
/* 80114898 00111478  48 15 6B 61 */	bl func_8026B3F8
/* 8011489C 0011147C  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 801148A0 00111480  38 80 00 46 */	li r4, 0x46
/* 801148A4 00111484  48 15 6B 55 */	bl func_8026B3F8
/* 801148A8 00111488  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 801148AC 0011148C  38 80 00 47 */	li r4, 0x47
/* 801148B0 00111490  48 15 6B 49 */	bl func_8026B3F8
/* 801148B4 00111494  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 801148B8 00111498  38 80 00 48 */	li r4, 0x48
/* 801148BC 0011149C  48 15 6B 3D */	bl func_8026B3F8
/* 801148C0 001114A0  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 801148C4 001114A4  38 80 00 49 */	li r4, 0x49
/* 801148C8 001114A8  48 15 6B 31 */	bl func_8026B3F8
/* 801148CC 001114AC  80 7F 00 24 */	lwz r3, 0x24(r31)
/* 801148D0 001114B0  38 80 00 65 */	li r4, 0x65
/* 801148D4 001114B4  48 15 6B 25 */	bl func_8026B3F8
/* 801148D8 001114B8  80 7F 00 28 */	lwz r3, 0x28(r31)
/* 801148DC 001114BC  38 80 00 66 */	li r4, 0x66
/* 801148E0 001114C0  48 15 6B 19 */	bl func_8026B3F8
/* 801148E4 001114C4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801148E8 001114C8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801148EC 001114CC  38 21 00 20 */	addi r1, r1, 0x20
/* 801148F0 001114D0  7C 08 03 A6 */	mtlr r0
/* 801148F4 001114D4  4E 80 00 20 */	blr 
}

#pragma push
#pragma peephole on
void func_801148F8(HSD_GObj* gobj)
{
    func_80115AF8(gobj);
    func_80116F38(gobj);
    func_80117E60(gobj);
    func_80114CF4(gobj);
}

void func_8011493C(HSD_GObj* gobj)
{
    func_8011B0F8(gobj);
}

f32 func_8011495C(Fighter* ft)
{
    return ((ftNessAttributes*)ft->x2D4_specialAttributes)->unk94;
}

void func_80114968(HSD_GObj* gobj, s32 arg1)
{
    s32 result, switched_res, unused;

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

void func_80114A48(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_80114A90(HSD_GObj* gobj)
{
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_80114AD8(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_80114B2C(HSD_GObj* gobj) 
{
    Fighter* ft = gobj->user_data;
    
    ftNessAttributes* sA2 = (ftNessAttributes*)ft->x2D4_specialAttributes;
    ftNessAttributes* ext_attr = (ftNessAttributes*)ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
}

void func_80114B6C(HSD_GObj* gobj)
{
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}
#pragma pop
