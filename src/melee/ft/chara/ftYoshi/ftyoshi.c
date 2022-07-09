#include "ftyoshi.h"


/// TODO remove these
extern f32 lbl_804D9A18;
extern f32 lbl_804D9A1C;

///https://decomp.me/scratch/ufrFK
void func_8012B6E8(Fighter* fighter, struct S_UNK_YOSHI1* unk_struct_arg) {

    s32 filler[5];

    struct S_UNK_YOSHI1 *unk_struct1;
    s32 *ptr2EndIndex;
    ftYoshiAttributes *attr_r26;
    u8 *index;
    s32 i;
    f32 zero_float;
    
    attr_r26 = fighter->x10C_ftData->ext_attr;
    index = (unk_struct1 = unk_struct_arg)->unk_struct->xC_start_index;
    ptr2EndIndex = (s32 *) (&unk_struct1->unk_struct->x8_end_index);
    zero_float = lbl_804D9A18;
    
    for (i = 0; i < *ptr2EndIndex; i++) {

        HSD_DObj* dobj_r3 = fighter->x5F0[index[i]];
        HSD_MObj *mobj_r3;
        HSD_AObj *aobj_r24;

        
        if (dobj_r3) {
            mobj_r3 = dobj_r3->mobj;
        } else {
            mobj_r3 = 0;
        }

        aobj_r24 = mobj_r3->aobj;
        HSD_AObjSetRate(aobj_r24, lbl_804D9A18);

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

void func_8012B804(Fighter* fighter, struct S_UNK_YOSHI1* unk_struct_arg, f32 start_frame) {

    s32 filler[2];

    if (unk_struct_arg) {
        
        struct S_UNK_YOSHI2* unk_struct = unk_struct_arg->unk_struct;
        s32 *ptr2EndIndex;
        u8 *index;
        s32 i;

        index = unk_struct->xC_start_index;
        ptr2EndIndex = (s32*) &unk_struct->x8_end_index;
        
        for (i = 0; i < *ptr2EndIndex; i++) {

            HSD_DObj* dobj_r3 = fighter->x5F0[index[i]];
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


void func_8012B8A4(HSD_GObj* fighterObj) {
    s32 unused[4];
    Fighter* fighter = fighterObj->user_data;
    ftYoshiAttributes *attr = fighter->x2D4_specialAttributes;
    f32 tempf = attr->xC * (lbl_804D9A1C - (fighter->x1998_shieldHealth / p_ftCommonData->x260_startShieldHealth));
    func_8012B804(fighter, (struct S_UNK_YOSHI1*)fighter->x5B8, tempf);
    func_8012B804(fighter, (struct S_UNK_YOSHI1*)fighter->x5BC, tempf);
}


void func_8012B918(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    func_8012B804(fighter, (struct S_UNK_YOSHI1*)fighter->x5B8, lbl_804D9A18);
    func_8012B804(fighter, (struct S_UNK_YOSHI1*)fighter->x5BC, lbl_804D9A18);
}

void ftYoshi_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    fighter->sa.yoshi.x2238 = 0;
}


//https://decomp.me/scratch/5TPxg
void ftYoshi_OnLoad(HSD_GObj* fighterObj) {
    void **item_list;
    ftYoshiAttributes *other_attr;
    struct S_UNK_YOSHI1* temp_r28;
    struct S_UNK_YOSHI1* temp;
    ftData *fighter_data;
    struct S_UNK_YOSHI1* temp_r27;
    Fighter *fighter;
    
    fighter = fighterObj->user_data;
    temp = temp_r27 = (struct S_UNK_YOSHI1*) fighter->x5B8;
    fighter_data = fighter->x10C_ftData;
    temp_r28 = (struct S_UNK_YOSHI1*)fighter->x5BC;
    item_list = fighter_data->x48_items;
    other_attr = fighter_data->ext_attr;
    
    if (!temp)
    {
        OSReport("yoshi parts_model NULL!!\n");
        __assert("ftyoshi.c", 0x71U, "0");
    }

    other_attr->xC = lbl_804D9A18;
    func_8012B6E8(fighter, temp_r27);
    func_8012B6E8(fighter, temp_r28);
    PUSH_ATTRS(fighter, ftYoshiAttributes);
    func_8026B3F8(item_list[0], 0x56U);
    func_8026B3F8(item_list[1], 0x58U);
    func_8026B3F8(item_list[2], 0x57U);
    fighter->x2226_flag.bits.b1 = 1;
  
}

void ftYoshi_8012BA8C(HSD_GObj* fighterObj) {
    func_8012E270(fighterObj);
    func_8012DF18(fighterObj);
}

f32 ftYoshi_8012BAC0(Fighter* fighter) {
    ftYoshiAttributes *attr = fighter->x2D4_specialAttributes;
    return attr->x120;
}

void ftYoshi_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftYoshi_OnItemInvisible(HSD_GObj *fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftYoshi_OnItemVisible(HSD_GObj *fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftYoshi_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 1, 1);
}
