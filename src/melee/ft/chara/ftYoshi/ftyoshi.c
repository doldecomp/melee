#include <melee/ft/chara/ftYoshi/ftyoshi.h>
#include <melee/it/itkind.h>

///https://decomp.me/scratch/ufrFK
void func_8012B6E8(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg) {

    s32 filler[5];

    struct S_UNK_YOSHI1 *unk_struct1;
    s32 *ptr2EndIndex;
    ftYoshiAttributes *attr_r26;
    u8 *index;
    s32 i;
    f32 zero_float;
    
    attr_r26 = fp->x10C_ftData->ext_attr;
    index = (unk_struct1 = unk_struct_arg)->unk_struct->xC_start_index;
    ptr2EndIndex = (s32 *) (&unk_struct1->unk_struct->x8_end_index);
    zero_float = 0.0f;
    
    for (i = 0; i < *ptr2EndIndex; i++) {

        HSD_DObj* dobj_r3 = fp->x5F0[index[i]];
        HSD_MObj *mobj_r3;
        HSD_AObj *aobj_r24;

        
        if (dobj_r3) {
            mobj_r3 = dobj_r3->mobj;
        } else {
            mobj_r3 = 0;
        }

        aobj_r24 = mobj_r3->aobj;
        HSD_AObjSetRate(aobj_r24, 0.0f);

        if (zero_float == attr_r26->xC) {
            attr_r26->xC = HSD_AObjGetEndFrame(aobj_r24);
        } else {
            if (attr_r26->xC != HSD_AObjGetEndFrame(aobj_r24)) {
                OSReport("yoshi matanim frame not same\n");
                __assert(__FILE__, 0x61, "0");
            }
        }

    }
}

void func_8012B804(Fighter* fp, struct S_UNK_YOSHI1* unk_struct_arg, f32 start_frame) {

    s32 filler[2];

    if (unk_struct_arg) {
        
        struct S_UNK_YOSHI2* unk_struct = unk_struct_arg->unk_struct;
        s32 *ptr2EndIndex;
        u8 *index;
        s32 i;

        index = unk_struct->xC_start_index;
        ptr2EndIndex = (s32*) &unk_struct->x8_end_index;
        
        for (i = 0; i < *ptr2EndIndex; i++) {

            HSD_DObj* dobj_r3 = fp->x5F0[index[i]];
            HSD_MObj* mobj_r3;
            HSD_MObj* mobj;

        
            if (dobj_r3) {
                mobj_r3 = dobj_r3->mobj;
            } else {
                mobj_r3 = 0;
            }

            mobj = mobj_r3;
            HSD_MObjReqAnim(mobj, start_frame);
            HSD_MObjAnim(mobj);
        }
    }
}


void func_8012B8A4(HSD_GObj* fighter_gobj) {
    s32 unused[4];
    Fighter* fp = fighter_gobj->user_data;
    ftYoshiAttributes *attr = fp->x2D4_specialAttributes;
    f32 tempf = attr->xC * (1.0f - (fp->x1998_shieldHealth / p_ftCommonData->x260_startShieldHealth));
    func_8012B804(fp, (struct S_UNK_YOSHI1*)fp->x5B8, tempf);
    func_8012B804(fp, (struct S_UNK_YOSHI1*)fp->x5BC, tempf);
}


void func_8012B918(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;

    func_8012B804(fp, (struct S_UNK_YOSHI1*)fp->x5B8, 0.0f);
    func_8012B804(fp, (struct S_UNK_YOSHI1*)fp->x5BC, 0.0f);
}

void ftYoshi_OnDeath(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    func_80074A4C(fighter_gobj, 0, 0);
    fp->sa.yoshi.x2238 = 0;
}


//https://decomp.me/scratch/5TPxg
void ftYoshi_OnLoad(HSD_GObj* fighter_gobj) {
    void **item_list;
    ftYoshiAttributes *other_attr;
    struct S_UNK_YOSHI1* temp_r28;
    struct S_UNK_YOSHI1* temp;
    ftData *ft;
    struct S_UNK_YOSHI1* temp_r27;
    Fighter *fp;
    
    fp = fighter_gobj->user_data;
    temp = temp_r27 = (struct S_UNK_YOSHI1*) fp->x5B8;
    ft = fp->x10C_ftData;
    temp_r28 = (struct S_UNK_YOSHI1*)fp->x5BC;
    item_list = ft->x48_items;
    other_attr = ft->ext_attr;
    
    if (!temp)
    {
        OSReport("yoshi parts_model NULL!!\n");
        __assert(__FILE__, 0x71U, "0");
    }

    other_attr->xC = 0.0f;
    func_8012B6E8(fp, temp_r27);
    func_8012B6E8(fp, temp_r28);
    PUSH_ATTRS(fp, ftYoshiAttributes);
    func_8026B3F8(item_list[0], It_Kind_Yoshi_EggThrow);
    func_8026B3F8(item_list[1], It_Kind_Yoshi_Star);
    func_8026B3F8(item_list[2], It_Kind_Yoshi_EggLay);
    fp->x2226_flag.bits.b1 = 1;
  
}

void ftYoshi_8012BA8C(HSD_GObj* fighter_gobj) {
    func_8012E270(fighter_gobj);
    func_8012DF18(fighter_gobj);
}

f32 ftYoshi_8012BAC0(Fighter* fp) {
    ftYoshiAttributes *attr = fp->x2D4_specialAttributes;
    return attr->x120;
}

void ftYoshi_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftYoshi_OnItemInvisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftYoshi_OnItemVisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftYoshi_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 1, 1);
}

void ftYoshi_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftYoshiAttributes);
}

void ftYoshi_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
    ftAnim_ApplyPartAnim(fighter_gobj, 3, 3, 0.0f);
    ftAnim_ApplyPartAnim(fighter_gobj, 4, 3, 0.0f); 
}

void ftYoshi_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
    ftAnim_ApplyPartAnim(fighter_gobj, 3, 2, 0.0f);
    ftAnim_ApplyPartAnim(fighter_gobj, 4, 2, 0.0f); 
}

extern f32 lbl_804D9A28;
void func_8007B5AC(void* arg0, void* arg1, void* arg2);

extern u8 lbl_803B75C0[];

#pragma push
asm unk_t func_8012BDA0()
{ // clang-format off
    nofralloc
func_8012BDA0:
/* 8012BDA0 00128980  7C 08 02 A6 */	mflr r0
/* 8012BDA4 00128984  38 80 00 02 */	li r4, 2
/* 8012BDA8 00128988  90 01 00 04 */	stw r0, 4(r1)
/* 8012BDAC 0012898C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8012BDB0 00128990  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8012BDB4 00128994  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8012BDB8 00128998  4B F4 F3 09 */	bl func_8007B0C0
/* 8012BDBC 0012899C  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 8012BDC0 001289A0  3C 60 80 3B */	lis r3, lbl_803B75C0@ha
/* 8012BDC4 001289A4  38 00 00 01 */	li r0, 1
/* 8012BDC8 001289A8  C0 02 A0 48 */	lfs f0, lbl_804D9A28
/* 8012BDCC 001289AC  80 84 00 08 */	lwz r4, 8(r4)
/* 8012BDD0 001289B0  38 E3 75 C0 */	addi r7, r3, lbl_803B75C0@l
/* 8012BDD4 001289B4  88 A4 00 11 */	lbz r5, 0x11(r4)
/* 8012BDD8 001289B8  38 7F 00 00 */	addi r3, r31, 0
/* 8012BDDC 001289BC  38 9F 11 A0 */	addi r4, r31, 0x11a0
/* 8012BDE0 001289C0  90 A1 00 20 */	stw r5, 0x20(r1)
/* 8012BDE4 001289C4  38 A1 00 20 */	addi r5, r1, 0x20
/* 8012BDE8 001289C8  90 01 00 24 */	stw r0, 0x24(r1)
/* 8012BDEC 001289CC  90 01 00 28 */	stw r0, 0x28(r1)
/* 8012BDF0 001289D0  80 C7 00 00 */	lwz r6, 0(r7)
/* 8012BDF4 001289D4  80 07 00 04 */	lwz r0, 4(r7)
/* 8012BDF8 001289D8  90 C1 00 38 */	stw r6, 0x38(r1)
/* 8012BDFC 001289DC  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8012BE00 001289E0  80 07 00 08 */	lwz r0, 8(r7)
/* 8012BE04 001289E4  90 01 00 40 */	stw r0, 0x40(r1)
/* 8012BE08 001289E8  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8012BE0C 001289EC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8012BE10 001289F0  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 8012BE14 001289F4  90 01 00 30 */	stw r0, 0x30(r1)
/* 8012BE18 001289F8  80 01 00 40 */	lwz r0, 0x40(r1)
/* 8012BE1C 001289FC  90 01 00 34 */	stw r0, 0x34(r1)
/* 8012BE20 00128A00  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8012BE24 00128A04  4B F4 F7 89 */	bl func_8007B5AC
/* 8012BE28 00128A08  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8012BE2C 00128A0C  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 8012BE30 00128A10  38 21 00 58 */	addi r1, r1, 0x58
/* 8012BE34 00128A14  7C 08 03 A6 */	mtlr r0
/* 8012BE38 00128A18  4E 80 00 20 */	blr 
}
#pragma pop
