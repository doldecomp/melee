#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

extern void func_800E1368(void);
extern void func_8008A4D4(HSD_GObj*);
extern void func_800E0EE0(HSD_GObj*);
extern void func_80084F3C(void);
extern const f32 lbl_804D9198;
extern const f32 lbl_804D919C;
extern s32 lbl_803C5A20[];

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

void func_800E0A00(void)
{
    func_800E1368();
}

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

void func_800E0B00(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_800E0B48(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_800E0B90(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_800E0BE4(HSD_GObj* gobj) {
    Fighter* ft;
    ftData* ftDataInfo;
    ftMarioAttributes *sA, *ext_attr;

    ft = gobj->user_data;
    ftDataInfo = ft->x10C_ftData;
    
    ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    *sA = *ext_attr;
    
}

void func_800E0C24(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_800E0C68(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void func_800E0CAC(s32 arg0, u32* arg1, u32* arg2) {
    if (arg0 != 10) {
        if (arg0 >= 10)
            return;
        if (arg0 < 9)
            return;
        *arg2 = 0xe;
        *arg1 = 0xe;
    } else {
        *arg2 = 0xf;
        *arg1 = 0xf;
    }
}

s32 func_800E0CE0(s32 arg0) {
    int offset;
    
    switch (arg0) {
        case 9:
            offset = 0xe;
            break;
        case 10:
            offset = 0xf;
    }

    return lbl_803C5A20[offset - 0xe];
}

/*
// Progress - Close-ish but not matching. Can't get compiler to use CTR
void func_800E0D1C(HSD_GObj* gobj) {
    //int i;
    //s32 temp_r3;
    Fighter* ft = gobj->user_data;
    
    u32 arr[9];
    
    s32 phi_ctr;
    u32* r4_ptr;
    int r3, r5; 

    int i;
    r5 = 0;
    r4_ptr = arr+1;
    r3 = 0;
    i = 9 - r5;
    
    //For loop I had (that was not unrolling - note if using decrementing instead of incrementing, the loop unrolls):
    for(i = 0; i != 9 - r5; i++) {
        if(((r5 != (int)ft->x222C) && (r5 != (int)ft->x2230))) {
            *r4_ptr++ = r5;
            r3 += 1;
        }
        r5 += 1;
        
    }

    r5 = (int)arr[HSD_Randi(r3)+1];
    ft->x2230 = ft->x222C;
    ft->x222C = r5;
}*/
asm void func_800E0D1C(HSD_GObj* gobj)
{
    nofralloc
/* 800E0D1C 000DD8FC  7C 08 02 A6 */	mflr r0
/* 800E0D20 000DD900  38 A0 00 00 */	li r5, 0
/* 800E0D24 000DD904  90 01 00 04 */	stw r0, 4(r1)
/* 800E0D28 000DD908  20 05 00 09 */	subfic r0, r5, 9
/* 800E0D2C 000DD90C  2C 05 00 09 */	cmpwi r5, 9
/* 800E0D30 000DD910  7C 09 03 A6 */	mtctr r0
/* 800E0D34 000DD914  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800E0D38 000DD918  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800E0D3C 000DD91C  38 81 00 14 */	addi r4, r1, 0x14
/* 800E0D40 000DD920  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E0D44 000DD924  38 60 00 00 */	li r3, 0
/* 800E0D48 000DD928  40 80 00 30 */	bge lbl_800E0D78
lbl_800E0D4C:
/* 800E0D4C 000DD92C  80 1F 22 2C */	lwz r0, 0x222c(r31)
/* 800E0D50 000DD930  7C 05 00 00 */	cmpw r5, r0
/* 800E0D54 000DD934  41 82 00 1C */	beq lbl_800E0D70
/* 800E0D58 000DD938  80 1F 22 30 */	lwz r0, 0x2230(r31)
/* 800E0D5C 000DD93C  7C 05 00 00 */	cmpw r5, r0
/* 800E0D60 000DD940  41 82 00 10 */	beq lbl_800E0D70
/* 800E0D64 000DD944  90 A4 00 00 */	stw r5, 0(r4)
/* 800E0D68 000DD948  38 84 00 04 */	addi r4, r4, 4
/* 800E0D6C 000DD94C  38 63 00 01 */	addi r3, r3, 1
lbl_800E0D70:
/* 800E0D70 000DD950  38 A5 00 01 */	addi r5, r5, 1
/* 800E0D74 000DD954  42 00 FF D8 */	bdnz lbl_800E0D4C
lbl_800E0D78:
/* 800E0D78 000DD958  48 29 F8 09 */	bl HSD_Randi
/* 800E0D7C 000DD95C  54 64 10 3A */	slwi r4, r3, 2
/* 800E0D80 000DD960  80 1F 22 2C */	lwz r0, 0x222c(r31)
/* 800E0D84 000DD964  38 61 00 14 */	addi r3, r1, 0x14
/* 800E0D88 000DD968  7C 63 20 2E */	lwzx r3, r3, r4
/* 800E0D8C 000DD96C  90 1F 22 30 */	stw r0, 0x2230(r31)
/* 800E0D90 000DD970  90 7F 22 2C */	stw r3, 0x222c(r31)
/* 800E0D94 000DD974  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800E0D98 000DD978  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800E0D9C 000DD97C  38 21 00 40 */	addi r1, r1, 0x40
/* 800E0DA0 000DD980  7C 08 03 A6 */	mtlr r0
/* 800E0DA4 000DD984  4E 80 00 20 */	blr 
}

#pragma push
#pragma peephole on

void func_800E0DA8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    func_800693AC(gobj,0x157,0,0,lbl_804D9198,lbl_804D919C,lbl_804D9198);
    func_8006EBA4(gobj);
    ft->x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E0E18(HSD_GObj* gobj){
    int res;

    res = func_8006F238(gobj);
    if (res == 0) {
        func_8008A2BC(gobj);
    }
}

void func_800E0E54(HSD_GObj* gobj) {
    Fighter* ft;
    ft = gobj->user_data;
    if(ft->x2200_ftcmd_var0 != 0) {
        func_8008A4D4(gobj);
    }
}

void func_800E0E84() {
    func_80084F3C();
}