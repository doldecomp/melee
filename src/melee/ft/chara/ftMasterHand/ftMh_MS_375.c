#include "ftMh_MS_375.h"

// 80154C78 151858
// https://decomp.me/scratch/j7foW
void ftMh_MS_375_80154C78(HSD_GObj* arg0)
{
    Fighter* temp_r31;
    ftMasterHand_SpecialAttrs* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->ft_data->ext_attr;
    Fighter_ChangeMotionState(arg0, 0x178, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
    temp_r31->mv.mh.unk0.xC.x = temp_r30->x118_pos.x;
    temp_r31->mv.mh.unk0.xC.y = temp_r30->x118_pos.y;
    temp_r31->mv.mh.unk0.xC.z = 0.0f;
}

// 80154CF8 1518D8
// https://decomp.me/scratch/XwAlv
void ftMh_MS_378_80154CF8(HSD_GObj* gobj, Fighter* fp)
{
    Fighter* temp_r31;
    ftMasterHand_SpecialAttrs* temp_r30;

    temp_r31 = gobj->user_data;
    temp_r30 = temp_r31->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x179, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    temp_r31->mv.mh.unk0.xC.x = temp_r30->x30_pos2.x;
    temp_r31->mv.mh.unk0.xC.y = temp_r30->x30_pos2.y;
    temp_r31->mv.mh.unk0.xC.z = 0.0f;
}
