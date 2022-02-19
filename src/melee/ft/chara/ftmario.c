#include "ftmario.h"

extern void func_800E1368(void);

void ftMario_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->x222C = 9;
    ft->x2230 = 9;
    ft->x2234 = 0;
    ft->x2238 = 0;
    ft->x223C = 0;
    ft->x2240 = 0;
}

void func_800E0920(Fighter* ft) {
    ftMarioAttributes* sA2 = (ftMarioAttributes*)ft->x2D8_specialAttributes2;
    ftMarioAttributes* ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
    ft->x2D4_specialAttributes = sA2;
}

void ftMario_OnLoad(HSD_GObj* gobj) {
    ftData* ftDataInfo;
    void** items;
    ftMarioAttributes *sA, *sA2, *ext_attr;
    Fighter* ft;
    
    ft = (Fighter*)gobj->user_data;
    ftDataInfo = ft->x10C_ftData;
    items = ftDataInfo->x48_items;

    ft->x2224_flag.bits.b7 = 1;
   
    sA2 = (ftMarioAttributes*)ft->x2D8_specialAttributes2;
    ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;

    *sA2 = *ext_attr;

    (ftMarioAttributes*)ft->x2D4_specialAttributes = sA2;

    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;    

    func_8026B3F8(items[0], 0x30);
    func_8026B3F8(items[2], sA->x14);
}

asm void lbl_800E0A00(void)
{
    nofralloc
/* 800E0A00 000DD5E0  7C 08 02 A6 */	mflr r0
/* 800E0A04 000DD5E4  90 01 00 04 */	stw r0, 4(r1)
/* 800E0A08 000DD5E8  94 21 FF F8 */	stwu r1, -8(r1)
/* 800E0A0C 000DD5EC  48 00 09 5D */	bl func_800E1368
/* 800E0A10 000DD5F0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800E0A14 000DD5F4  38 21 00 08 */	addi r1, r1, 8
/* 800E0A18 000DD5F8  7C 08 03 A6 */	mtlr r0
/* 800E0A1C 000DD5FC  4E 80 00 20 */	blr 
}

#pragma push
#pragma peephole on
void func_800E0A20(HSD_GObj* gobj, s32 arg1) {
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
#pragma pop
