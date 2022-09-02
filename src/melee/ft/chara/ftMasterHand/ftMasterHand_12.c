#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80152634 14F214
// https://decomp.me/scratch/ZAr9B
void lbl_80152634(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80151018(arg0);
    }
}



// 80152670 14F250
// https://decomp.me/scratch/8k9M0
void lbl_80152670(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 801526B4 14F294
// https://decomp.me/scratch/SGiGG
void lbl_801526B4(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 801526D4 14F2B4
void lbl_801526D4(HSD_GObj* gobj) {
    return;
}



// 801526D8 14F2B8
// https://decomp.me/scratch/woLuT
void lbl_801526D8(HSD_GObj* arg0) {
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    Fighter_ActionStateChange_800693AC(arg0, 0x166, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    temp_r31->x2340_f32 = 0.0f;
}



// 80152738 14F318
// https://decomp.me/scratch/JppLT
void lbl_80152738(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80151018(arg0);
    }
}



// 80152774 14F354
// https://decomp.me/scratch/FCaLx
void lbl_80152774(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 801527B8 14F398
// https://decomp.me/scratch/lzl13
void lbl_801527B8(HSD_GObj* gobj) {
    Fighter* r31_fp;
    MasterHandAttributes* r30_attributes;
    f32 tmp;

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->x10C_ftData->ext_attr;

    func_80085134(gobj);

    tmp = ++r31_fp->x2340_f32;
    if (tmp                        > r30_attributes->xB0 && 
        r31_fp->x2340_f32 < r30_attributes->xB4
    ) {
        func_8015C010(gobj, r30_attributes->xB8);
    } else {
        r31_fp->x80_self_vel.x = 0.0f;
    }
    func_8015C190(gobj);
}
