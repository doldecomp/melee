#include <melee/ft/chara/ftPurin/ftpurin.h>

extern struct UnkCostumeList CostumeListsForeachCharacter[33];
extern char* lbl_803D05B4[1000];  /// not correct length
extern HSD_ObjAllocData lbl_80459080;
extern HSD_Joint* lbl_8045A1E0[1000]; /// not correct length

void func_8013C2F8() {
    lbl_8045A1E0[0] = 0;
    lbl_8045A1E0[1] = 0;
    lbl_8045A1E0[2] = 0;
    lbl_8045A1E0[3] = 0;
    lbl_8045A1E0[4] = 0;
}

void ftPurin_OnDeath(HSD_GObj* fighter_gobj) {
    func_80074A4C(fighter_gobj, 0, 0);
}

void ftPurin_OnUserDataRemove(HSD_GObj* fighter_gobj) {
    func_8013C494(fighter_gobj);
}

void func_8013C360(HSD_GObj* fighter_gobj) {

    s32 unused;

    HSD_Joint** joint_list = lbl_8045A1E0;
    Fighter* fp = fighter_gobj->user_data;
    
    if (lbl_803D05B4[fp->x619_costume_id]) {
        void** item_list = fp->x10C_ftData->x48_items;
        void** item_list_shifted = item_list[1];
        if (!joint_list[fp->x619_costume_id]) {
            UnkCostumeStruct* costume_list = CostumeListsForeachCharacter[fp->x4_fighterKind].costume_list;
            joint_list[fp->x619_costume_id] = HSD_ArchiveGetPublicAddress(costume_list[fp->x619_costume_id].x14_archive, lbl_803D05B4[fp->x619_costume_id]);
        }

        fp->sa.purin.x2244 = HSD_ObjAlloc(&lbl_80459080);
        func_80074148();
        fp->sa.purin.x223C = HSD_JObjLoadJoint(joint_list[fp->x619_costume_id]);
        fp->x2225_flag.bits.b2 = 1;
        func_80074170();
        func_80075650(fighter_gobj, fp->sa.purin.x223C, &fp->sa.purin.x2240);

        func_8007487C(&item_list_shifted[1], &fp->sa.purin.x2248, fp->x619_costume_id, &fp->sa.purin.x2240, &fp->sa.purin.x2240);
        func_8009DC54(fp);
        return;
    }
    fp->sa.purin.x223C = 0;
}

void func_8013C494(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    HSD_JObj* jobj = fp->sa.purin.x223C;
    
    if (jobj) {
        HSD_JObjRemoveAll(fp->sa.purin.x223C);
        fp->sa.purin.x223C = NULL;
        HSD_ObjFree(&lbl_80459080, fp->sa.purin.x2244);
        fp->sa.purin.x2244 = NULL;
    }
}

void func_8013C4F0(HSD_GObj* fighter_gobj, s32 arg1, s32 arg2) {
  s32 unused[2];

  Fighter *fp = fighter_gobj->user_data;
    
    if (fp->sa.purin.x223C && fp->x2225_flag.bits.b2) {
    
        Mtx *mtx;
        HSD_JObj *jobj;
        HSD_JObj* bone_jobj = fp->x5E8_fighterBones[6].x0_jobj;
        HSD_JObjGetMtx(fp->x5E8_fighterBones[6].x0_jobj);
        mtx = (0, &bone_jobj->mtx);
        jobj = fp->sa.purin.x223C;
        HSD_JObjCopyMtx(fp->sa.purin.x223C, *mtx);
        jobj->flags |= 0x03800000;
        HSD_JObjSetMtxDirty(jobj);
          
        HSD_JObjDispAll(fp->sa.purin.x223C, arg2, func_80390EB8(arg1), 0);
    }

}


void func_8013C614(Fighter* fp, s32 arg1, s32 arg2) {
    if (fp->sa.purin.x223C) {
        if (arg2) {
            func_80074CA0(&fp->sa.purin.x2248, arg1, &fp->sa.purin.x2240);
            return;
        }
        func_80074D7C(&fp->sa.purin.x2248, arg1, &fp->sa.purin.x2240);
    }
}

void* func_8013C664(HSD_GObj* fighter_gobj) {
    Fighter *fp = fighter_gobj->user_data;
    if (fp->sa.purin.x223C) {
        return fp->sa.purin.x223C;
    }
    return fighter_gobj;
}

void ftPurin_OnLoad(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    PUSH_ATTRS(fp, ftPurinAttributes);
    fp->x2222_flag.bits.b1 = 1;
    fp->x2D0 = fp->x2D4_specialAttributes;
    func_8013C360(fighter_gobj);
}

void ftPurin_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter *fp = getFighter(fighter_gobj);            
    if (!func_8026B2B4(fp->x1974_heldItem)) {        
        switch (func_8026B320(fp->x1974_heldItem)) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                func_80070FB4(fighter_gobj, 0, 0);
                break;
            case 4:
                func_80070FB4(fighter_gobj, 0, 1);
                break;
        }   
        if (bool) {                                       
           func_80070C48(fighter_gobj, 0);            
        }  
    }   
}

void ftPurin_OnItemInvisible(HSD_GObj *fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x1974_heldItem) {
        if (!func_8026B2B4(fp->x1974_heldItem)) {
            func_80070CC4(fighter_gobj, 0);
        }
    }
}

void ftPurin_OnItemVisible(HSD_GObj *fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x1974_heldItem) {
        if (!func_8026B2B4(fp->x1974_heldItem)) {
            func_80070C48(fighter_gobj, 0);
        }
    }
}

void ftPurin_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 0, 0);
}

void ftPurin_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftPurinAttributes);
}

void ftPurin_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftPurin_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}
