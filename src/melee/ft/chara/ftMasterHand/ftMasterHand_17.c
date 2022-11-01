#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

static void func_80153910(HSD_GObj* fighter_gobj);

void lbl_8015386C(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        func_80153910(fighter_gobj);
    }
}

void lbl_801538A8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftbosslib_8015BD20(fighter_gobj);
    }
}

void lbl_801538EC(HSD_GObj* gobj)
{
    func_80085134(gobj);
}

void lbl_8015390C(HSD_GObj* gobj)
{
    return;
}

static void func_80153910(HSD_GObj* arg0)
{
    Fighter* fp;
    MasterHandAttributes* attr;
    Vec3 sp10;
    s32 unk;

    fp = arg0->user_data;
    attr = fp->x10C_ftData->ext_attr;
    Fighter_ActionStateChange_800693AC(arg0, 0x170, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(arg0);
    ftbosslib_8015C208(arg0, &sp10);
    fp->xB0_pos.x = sp10.x;
    fp->xB0_pos.y = attr->x5C;
    fp->x80_self_vel.z = 0.0F;
    fp->x80_self_vel.y = 0.0F;
    fp->x80_self_vel.x = 0.0F;
}

void lbl_801539A4(HSD_GObj* fighter_gobj)
{
    Fighter* temp_r4;
    s32 unk;

    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        temp_r4 = fighter_gobj->user_data;
        temp_r4->x80_self_vel.x = 0.0F;
        ftMasterHand_80153A64(fighter_gobj);
    }
}
