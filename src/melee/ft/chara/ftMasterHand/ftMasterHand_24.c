#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80154C78(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x178, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    fp->x234C_pos.x = ext_attr->x118_pos.x;
    fp->x234C_pos.y = ext_attr->x118_pos.y;
    fp->x234C_pos.z = 0.0F;
}

// todo: fp_1 is part of an inline
void ftMasterHand_80154CF8(HSD_GObj* fighter_gobj, Fighter* fp)
{
    Fighter* fp_1 = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp_1->x10C_ftData->ext_attr;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x179, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);

    /* second inline */ {
        fp_1->x234C_pos.x = ext_attr->x30_pos2.x;
        fp_1->x234C_pos.y = ext_attr->x30_pos2.y;
        fp_1->x234C_pos.z = 0.0F;
    }
}