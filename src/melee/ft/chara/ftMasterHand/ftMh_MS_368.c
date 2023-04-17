#include "ftMh_MS_368.h"

#include "ft/ftbosslib.h"

// 801539EC 1505CC
void ftMh_MS_368_IASA(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 80153A30 150610
// https://decomp.me/scratch/oph8G
void ftMh_MS_368_Phys(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* r4_attributes = fp->x10C_ftData->ext_attr;

    ftBossLib_8015BF74(gobj, r4_attributes->x58);
}

// 80153A60 150640
void ftMh_MS_368_Coll(HSD_GObj* gobj)
{
    return;
}

// 80153A64 150644
// https://decomp.me/scratch/K5X6I
void ftMh_MS_368_80153A64(HSD_GObj* arg0)
{
    Fighter* temp_r31;
    ftMasterHand_SpecialAttrs* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    Fighter_ChangeMotionState(arg0, 0x171, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
    temp_r31->cur_pos.x = temp_r30->x60;
    temp_r31->cur_pos.y = temp_r30->x64;
    temp_r31->x80_self_vel.z = 0.0f;
    temp_r31->x80_self_vel.y = 0.0f;
    temp_r31->x80_self_vel.x = 0.0f;
}
