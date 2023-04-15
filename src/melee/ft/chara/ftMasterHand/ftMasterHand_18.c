#include "ftMasterHand_18.h"

#include "types.h"

#include "ft/fighter.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"

void ftMh_Unk18_801539EC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Unk18_80153A30(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* sa = fp->ft_data->ext_attr;

    ftBossLib_8015BF74(gobj, sa->x58);
}

void ftMh_Unk18_80153A60(HSD_GObj* gobj) {}

void ftMh_Unk18_80153A64(HSD_GObj* gobj)
{
    Fighter* temp_r31;
    ftMasterHand_SpecialAttrs* temp_r30;

    temp_r31 = gobj->user_data;
    temp_r30 = temp_r31->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x171, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    temp_r31->cur_pos.x = temp_r30->x60;
    temp_r31->cur_pos.y = temp_r30->x64;
    temp_r31->x80_self_vel.z = 0.0f;
    temp_r31->x80_self_vel.y = 0.0f;
    temp_r31->x80_self_vel.x = 0.0f;
}
