#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80154C78 151858
// https://decomp.me/scratch/j7foW
void func_80154C78(HSD_GObj* arg0) {
    Fighter* temp_r31;
    MasterHandAttributes* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(arg0, 0x178, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    temp_r31->x234C_pos.x = temp_r30->x118_pos.x;
    temp_r31->x234C_pos.y = temp_r30->x118_pos.y;
    temp_r31->x234C_pos.z = 0.0f;
}



// 80154CF8 1518D8
// https://decomp.me/scratch/XwAlv
void func_80154CF8(HSD_GObj* gobj, Fighter* fp) {
    Fighter* temp_r31;
    MasterHandAttributes* temp_r30;

    temp_r31 = gobj->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(gobj, 0x179, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    temp_r31->x234C_pos.x = temp_r30->x30_pos2.x;
    temp_r31->x234C_pos.y = temp_r30->x30_pos2.y;
    temp_r31->x234C_pos.z = 0.0f;
}
