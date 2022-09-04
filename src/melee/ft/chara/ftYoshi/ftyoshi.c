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
