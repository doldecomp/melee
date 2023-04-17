#include "ftMasterHand_08.h"

#include "ftMasterHand_03.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"

// 80151C04 14E7E4
// https://decomp.me/scratch/ODVZ4
void ftMh_MS_349_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_389_80151018(arg0);
    }
}

// 80151C40 14E820
// https://decomp.me/scratch/QJiom
void ftMh_MS_349_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

// 80151C84 14E864
// https://decomp.me/scratch/P5GL1
void ftMh_MS_349_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_349_Coll(HSD_GObj* arg0) {}

// 80151CA8 14E888
// https://decomp.me/scratch/nRy1R
void ftMh_MS_349_80151CA8(HSD_GObj* gobj)
{
    Fighter* temp_r31;
    ftMasterHand_SpecialAttrs* temp_r30;

    temp_r31 = gobj->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x161, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    temp_r31->cur_pos.y =
        temp_r30->x50.x; // TODO: The code matches, but is this right?
    temp_r31->x80_self_vel.x = 0.0f;
}
