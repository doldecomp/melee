#include "ftMasterHand_08.h"

#include "ftMasterHand_03.h"

#include "ft/code_80081B38.h"
#include "ft/ftbosslib.h"

// 80151C04 14E7E4
// https://decomp.me/scratch/ODVZ4
void lbl_80151C04(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0))
        func_80151018(arg0);
}

// 80151C40 14E820
// https://decomp.me/scratch/QJiom
void lbl_80151C40(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(gobj);
}

// 80151C84 14E864
// https://decomp.me/scratch/P5GL1
void lbl_80151C84(HSD_GObj* gobj)
{
    func_80085134(gobj);
}

void lbl_80151CA4(HSD_GObj* arg0) {}

// 80151CA8 14E888
// https://decomp.me/scratch/nRy1R
void func_80151CA8(HSD_GObj* gobj)
{
    Fighter* temp_r31;
    ftMasterHand_SpecialAttrs* temp_r30;

    temp_r31 = gobj->user_data;
    temp_r30 = temp_r31->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(gobj, 0x161, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    temp_r31->xB0_pos.y =
        temp_r30->x50.x; // TODO: The code matches, but is this right?
    temp_r31->x80_self_vel.x = 0.0f;
}
