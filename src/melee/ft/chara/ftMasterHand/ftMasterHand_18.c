#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 801539EC 1505CC
void lbl_801539EC(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80153A30 150610
// https://decomp.me/scratch/oph8G
void lbl_80153A30(HSD_GObj* gobj) {
    Fighter* fp = gobj->user_data;
    MasterHandAttributes* r4_attributes = fp->x10C_ftData->ext_attr;

    func_8015BF74(gobj, r4_attributes->x58);
}



// 80153A60 150640
void lbl_80153A60(HSD_GObj* gobj) {
    return;
}



// 80153A64 150644
// https://decomp.me/scratch/K5X6I
void func_80153A64(HSD_GObj* arg0) {
    Fighter* temp_r31;
    MasterHandAttributes* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(arg0, 0x171, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    temp_r31->xB0_pos.x = temp_r30->x60;
    temp_r31->xB0_pos.y = temp_r30->x64;
    temp_r31->x80_self_vel.z = 0.0f;
    temp_r31->x80_self_vel.y = 0.0f;
    temp_r31->x80_self_vel.x = 0.0f;
}
