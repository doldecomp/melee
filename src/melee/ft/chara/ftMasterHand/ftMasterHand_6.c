#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 801517B0 14E390
// https://decomp.me/scratch/ayfDz
void lbl_801517B0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (!Player_GetPlayerSlotType(fp->xC_playerID)) {
        func_8015BD20(gobj);
    }
}



// 801517F4 14E3D4
// https://decomp.me/scratch/TjBLH
void lbl_801517F4(HSD_GObj* gobj) {
    MasterHandAttributes* r3_attributes;
    Fighter* r4_fp;

    r4_fp = gobj->user_data;
    r3_attributes = r4_fp->x10C_ftData->ext_attr;
    r4_fp->x80_self_vel.y += r3_attributes->x150;
    r4_fp->x80_self_vel.z += r3_attributes->x158;
}



// 80151824 14E404
// https://decomp.me/scratch/xfY30
void lbl_80151824(void) {

}



// 80151828 14E408
// https://decomp.me/scratch/rsfpE
void lbl_80151828(HSD_GObj* arg0) {
    Fighter_ActionStateChange_800693AC(arg0, 0x15A, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
}

// 80151874 14E454
// https://decomp.me/scratch/AmIC0
void lbl_80151874(HSD_GObj* arg0) {
    if (!ftAnim_IsFramesRemaining(arg0)) {
        func_80151918(arg0);
    }
}



// 801518B0 14E490
// https://decomp.me/scratch/x8MEh
void lbl_801518B0(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (!Player_GetPlayerSlotType(fp->xC_playerID)) {
        func_8015BD20(gobj);
    }
}



// 801518F4 14E4D4
// https://decomp.me/scratch/Gtp0Z
void lbl_801518F4(HSD_GObj* arg0) {
    func_80085134(arg0);
}



// 80151914 14E4F4
// https://decomp.me/scratch/BYVIT
void lbl_80151914(void) {

}



// 80151918 14E4F8
// https://decomp.me/scratch/uyxzl
void func_80151918(HSD_GObj* gobj) {
    Fighter* r8_fp;
    MasterHandAttributes* r7_attributes;

    r8_fp = gobj->user_data;
    r7_attributes = r8_fp->x10C_ftData->ext_attr;
    r8_fp->x234C_pos.x = (r8_fp->xB0_pos.x - r7_attributes->x3C);
    r8_fp->x234C_pos.y = r7_attributes->x38;
    r8_fp->x234C_pos.z = 0.0f;

    Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}



// 8015198C 14E56C
// https://decomp.me/scratch/9npQJ
void lbl_8015198C(HSD_GObj* gobj) {
    MasterHandAttributes* temp_r7;
    Fighter* temp_r31;
    Fighter* temp_r8;
    Vec3 sp14;
    u32 unk[2];

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        temp_r31 = gobj->user_data;
        func_80054158(0, &sp14);
        if (temp_r31->xB0_pos.x < sp14.x) {
            func_80151AC8(gobj);
            return;
        }
        temp_r8 = gobj->user_data;
        temp_r7 = temp_r8->x10C_ftData->ext_attr;
        temp_r8->x234C_pos.x = temp_r8->xB0_pos.x - temp_r7->x3C;
        temp_r8->x234C_pos.y = temp_r7->x38;
        temp_r8->x234C_pos.z = 0.0f;
        Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
}



// 80151A44 14E624
// https://decomp.me/scratch/RccD3
void lbl_80151A44(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}



// 80151A88 14E668
// https://decomp.me/scratch/3ONNP
void lbl_80151A88(HSD_GObj* gobj) {
    Fighter* r5_fp;
    MasterHandAttributes* r6_attributes;

    r5_fp = gobj->user_data;
    r6_attributes = r5_fp->x10C_ftData->ext_attr;
    func_8015BE40(gobj, &r5_fp->x234C_pos, &r5_fp->x2358_stateVar7, r6_attributes->x2C, r6_attributes->x28);
}



// 80151AC4 14E6A4
// https://decomp.me/scratch/edLn0
void lbl_80151AC4(void) {
    return;
}



// 80151AC8 14E6A8
// https://decomp.me/scratch/AimoS
void func_80151AC8(HSD_GObj* gobj) {
    Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}
