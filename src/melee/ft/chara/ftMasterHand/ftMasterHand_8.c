#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>

// 80151C04 14E7E4
// https://decomp.me/scratch/ODVZ4
void lbl_80151C04(HSD_GObj* arg0)
{
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        ftMasterHand_80151018(arg0);
    }
}

// 80151C40 14E820
// https://decomp.me/scratch/QJiom
void lbl_80151C40(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}

void lbl_80151C84(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void lbl_80151CA4(void)
{
    return;
}

void ftMasterHand_80151CA8(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    MasterHandAttributes* ext_attr;

    fp = fighter_gobj->user_data;
    ext_attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x161, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp->xB0_pos.y = ext_attr->x50.x; // TODO: The code matches, but is this right?
    fp->x80_self_vel.x = 0.0f;
}
