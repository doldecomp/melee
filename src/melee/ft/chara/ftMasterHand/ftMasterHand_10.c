#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80152138 14ED18
// https://decomp.me/scratch/NAMEj
void lbl_80152138(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80151018(arg0);
    }
}



// 80152174 14ED54
// https://decomp.me/scratch/6NWxd
void lbl_80152174(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 801521B8 14ED98
// https://decomp.me/scratch/yyAcs
void lbl_801521B8(HSD_GObj* gobj) {
    func_80085134(gobj);
}



// 801521D8 14EDB8
// https://decomp.me/scratch/8JwVv
void lbl_801521D8(void) {
    return;
}



// 801521DC 14EDBC
// https://decomp.me/scratch/0Dq4d
void lbl_801521DC(HSD_GObj* arg0) {
    Fighter* temp_r31;
    s32 unk[2];

    temp_r31 = arg0->user_data;
    Fighter_ActionStateChange_800693AC(arg0, 0x162, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    temp_r31->x2340_f32 = 107.0f;
}



// 8015223C 14EE1C
// https://decomp.me/scratch/sZYJl
void lbl_8015223C(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_80151018(arg0);
    }
}



// 80152278 14EE58
// https://decomp.me/scratch/KNhTn
void lbl_80152278(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 801522BC 14EE9C
// https://decomp.me/scratch/hAUig
void lbl_801522BC(HSD_GObj* gobj) {
    Fighter* r31_fp;
    ftData* r4_ftData;
    MasterHandAttributes* r30_attributes;

    r31_fp = gobj->user_data;
    r4_ftData = r31_fp->x10C_ftData;
    r30_attributes = r4_ftData->ext_attr;
    func_80085134(gobj);

    if ((--r31_fp->x2340_f32 > r30_attributes->x84) || (r31_fp->x2340_f32 < 0.0f)) {
        r31_fp->x80_self_vel.x = 0.0f;
    } else {
        func_8015C010(gobj, r30_attributes->x80);
    }
    func_8015C190(gobj);
}

