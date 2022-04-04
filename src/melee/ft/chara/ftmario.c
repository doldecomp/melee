#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

extern void func_800E1368(void);
extern void func_8008A4D4(HSD_GObj*);
extern void func_800E0EE0(HSD_GObj*);
extern void func_80084F3C(void);
extern unsigned char func_8007500C(struct _Fighter *, long);
extern void func_8000B1CC(void *, void *, Vec*);
extern void func_8029B6F8(f32,HSD_GObj*,Vec*,u8);
extern void func_802C0510(HSD_GObj*,Vec*,int,u8,f32);
extern void ef_Spawn(...);
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

void func_800E0D1C(HSD_GObj* gobj) {

    Fighter* ft = gobj->user_data;
    
    u32 arr[9];
    
    u32* r4_ptr;
    int r3, r5, unused; 

    r5 = r3 = 0;
    r4_ptr = arr+1;

    while(r5 < 9) {
        if(((r5 != (int)ft->x222C) && (r5 != (int)ft->x2230))) {
            *r4_ptr++ = r5;
            r3 += 1;
        }
        r5 += 1;

        
    }

    r3 = (int)arr[HSD_Randi(r3)+1];
    ft->x2230 = ft->x222C;
    ft->x222C = r3;

    return;
}

void func_800E0DA8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    func_800693AC(gobj,0x157,0,0,lbl_804D9198,lbl_804D919C,lbl_804D9198);
    func_8006EBA4(gobj);
    ft->x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E0E18(HSD_GObj* gobj) {
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

void func_800E0EA4(HSD_GObj* gobj) {
    int res;

    res = func_80082708(gobj);
    if (res == 0) {
        func_800E1178(gobj);
    }
}

//https://decomp.me/scratch/yJ6cV
asm void func_800E0EE0(HSD_GObj* gobj) {
nofralloc
/* 800E0EE0 000DDAC0  7C 08 02 A6 */	mflr r0
/* 800E0EE4 000DDAC4  90 01 00 04 */	stw r0, 4(r1)
/* 800E0EE8 000DDAC8  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800E0EEC 000DDACC  93 E1 00 5C */	stw r31, 0x5c(r1)
/* 800E0EF0 000DDAD0  93 C1 00 58 */	stw r30, 0x58(r1)
/* 800E0EF4 000DDAD4  7C 7E 1B 78 */	mr r30, r3
/* 800E0EF8 000DDAD8  93 A1 00 54 */	stw r29, 0x54(r1)
/* 800E0EFC 000DDADC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800E0F00 000DDAE0  88 64 22 10 */	lbz r3, 0x2210(r4)
/* 800E0F04 000DDAE4  3B E4 00 00 */	addi r31, r4, 0
/* 800E0F08 000DDAE8  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 800E0F0C 000DDAEC  41 82 00 18 */	beq lbl_800E0F24
/* 800E0F10 000DDAF0  38 00 00 00 */	li r0, 0
/* 800E0F14 000DDAF4  50 03 3E 30 */	rlwimi r3, r0, 7, 0x18, 0x18
/* 800E0F18 000DDAF8  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 800E0F1C 000DDAFC  38 00 00 01 */	li r0, 1
/* 800E0F20 000DDB00  48 00 00 08 */	b lbl_800E0F28
lbl_800E0F24:
/* 800E0F24 000DDB04  38 00 00 00 */	li r0, 0
lbl_800E0F28:
/* 800E0F28 000DDB08  2C 00 00 00 */	cmpwi r0, 0
/* 800E0F2C 000DDB0C  41 82 00 F8 */	beq lbl_800E1024
/* 800E0F30 000DDB10  38 7F 00 00 */	addi r3, r31, 0
/* 800E0F34 000DDB14  38 80 00 17 */	li r4, 0x17
/* 800E0F38 000DDB18  4B F9 40 D5 */	bl func_8007500C
/* 800E0F3C 000DDB1C  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800E0F40 000DDB20  54 60 20 36 */	slwi r0, r3, 4
/* 800E0F44 000DDB24  38 A1 00 44 */	addi r5, r1, 0x44
/* 800E0F48 000DDB28  7C 64 00 2E */	lwzx r3, r4, r0
/* 800E0F4C 000DDB2C  38 80 00 00 */	li r4, 0
/* 800E0F50 000DDB30  4B F2 A2 7D */	bl func_8000B1CC
/* 800E0F54 000DDB34  80 1F 00 04 */	lwz r0, 4(r31)
/* 800E0F58 000DDB38  2C 00 00 00 */	cmpwi r0, 0
/* 800E0F5C 000DDB3C  40 82 00 48 */	bne lbl_800E0FA4
/* 800E0F60 000DDB40  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800E0F64 000DDB44  38 7E 00 00 */	addi r3, r30, 0
/* 800E0F68 000DDB48  38 81 00 44 */	addi r4, r1, 0x44
/* 800E0F6C 000DDB4C  38 A0 00 30 */	li r5, 0x30
/* 800E0F70 000DDB50  48 1B A7 89 */	bl func_8029B6F8
/* 800E0F74 000DDB54  38 7F 00 00 */	addi r3, r31, 0
/* 800E0F78 000DDB58  38 80 00 17 */	li r4, 0x17
/* 800E0F7C 000DDB5C  4B F9 40 91 */	bl func_8007500C
/* 800E0F80 000DDB60  80 BF 05 E8 */	lwz r5, 0x5e8(r31)
/* 800E0F84 000DDB64  54 60 20 36 */	slwi r0, r3, 4
/* 800E0F88 000DDB68  38 9E 00 00 */	addi r4, r30, 0
/* 800E0F8C 000DDB6C  4C C6 31 82 */	crclr 6
/* 800E0F90 000DDB70  7C A5 00 2E */	lwzx r5, r5, r0
/* 800E0F94 000DDB74  38 DF 00 2C */	addi r6, r31, 0x2c
/* 800E0F98 000DDB78  38 60 04 7A */	li r3, 0x47a
/* 800E0F9C 000DDB7C  4B F7 EE 41 */	bl ef_Spawn
/* 800E0FA0 000DDB80  48 00 00 84 */	b lbl_800E1024
lbl_800E0FA4:
/* 800E0FA4 000DDB84  38 80 00 00 */	li r4, 0
/* 800E0FA8 000DDB88  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 800E0FAC 000DDB8C  20 04 00 09 */	subfic r0, r4, 9
/* 800E0FB0 000DDB90  2C 04 00 09 */	cmpwi r4, 9
/* 800E0FB4 000DDB94  7C 09 03 A6 */	mtctr r0
/* 800E0FB8 000DDB98  38 A1 00 18 */	addi r5, r1, 0x18
/* 800E0FBC 000DDB9C  38 60 00 00 */	li r3, 0
/* 800E0FC0 000DDBA0  40 80 00 30 */	bge lbl_800E0FF0
lbl_800E0FC4:
/* 800E0FC4 000DDBA4  80 1D 22 2C */	lwz r0, 0x222c(r29)
/* 800E0FC8 000DDBA8  7C 04 00 00 */	cmpw r4, r0
/* 800E0FCC 000DDBAC  41 82 00 1C */	beq lbl_800E0FE8
/* 800E0FD0 000DDBB0  80 1D 22 30 */	lwz r0, 0x2230(r29)
/* 800E0FD4 000DDBB4  7C 04 00 00 */	cmpw r4, r0
/* 800E0FD8 000DDBB8  41 82 00 10 */	beq lbl_800E0FE8
/* 800E0FDC 000DDBBC  90 85 00 00 */	stw r4, 0(r5)
/* 800E0FE0 000DDBC0  38 A5 00 04 */	addi r5, r5, 4
/* 800E0FE4 000DDBC4  38 63 00 01 */	addi r3, r3, 1
lbl_800E0FE8:
/* 800E0FE8 000DDBC8  38 84 00 01 */	addi r4, r4, 1
/* 800E0FEC 000DDBCC  42 00 FF D8 */	bdnz lbl_800E0FC4
lbl_800E0FF0:
/* 800E0FF0 000DDBD0  48 29 F5 91 */	bl HSD_Randi
/* 800E0FF4 000DDBD4  54 64 10 3A */	slwi r4, r3, 2
/* 800E0FF8 000DDBD8  80 1D 22 2C */	lwz r0, 0x222c(r29)
/* 800E0FFC 000DDBDC  38 61 00 18 */	addi r3, r1, 0x18
/* 800E1000 000DDBE0  7C C3 20 2E */	lwzx r6, r3, r4
/* 800E1004 000DDBE4  38 7E 00 00 */	addi r3, r30, 0
/* 800E1008 000DDBE8  38 81 00 44 */	addi r4, r1, 0x44
/* 800E100C 000DDBEC  90 1D 22 30 */	stw r0, 0x2230(r29)
/* 800E1010 000DDBF0  7C C5 33 78 */	mr r5, r6
/* 800E1014 000DDBF4  90 DD 22 2C */	stw r6, 0x222c(r29)
/* 800E1018 000DDBF8  38 C0 00 31 */	li r6, 0x31
/* 800E101C 000DDBFC  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800E1020 000DDC00  48 1D F4 F1 */	bl func_802C0510
lbl_800E1024:
/* 800E1024 000DDC04  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800E1028 000DDC08  83 E1 00 5C */	lwz r31, 0x5c(r1)
/* 800E102C 000DDC0C  83 C1 00 58 */	lwz r30, 0x58(r1)
/* 800E1030 000DDC10  83 A1 00 54 */	lwz r29, 0x54(r1)
/* 800E1034 000DDC14  38 21 00 60 */	addi r1, r1, 0x60
/* 800E1038 000DDC18  7C 08 03 A6 */	mtlr r0
/* 800E103C 000DDC1C  4E 80 00 20 */	blr 
}
#pragma push
#pragma peephole on

void func_800E1040(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    func_800693AC(gobj,0x158,0,0,lbl_804D9198,lbl_804D919C,lbl_804D9198);
    func_8006EBA4(gobj);
    ft->x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E10B0(HSD_GObj* gobj) {
    int res;

    res = func_8006F238(gobj);
    if (res == 0) {
        func_800CC730(gobj);
    }
}

void func_800E10EC(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    if (ft->x2200_ftcmd_var0 != 0) {
        func_800CCAAC(gobj);
    }
}