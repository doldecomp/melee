#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80154A78(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* attr = fp->x10C_ftData->ext_attr;
    fp->x2204_ftcmd_var1 = FALSE;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17A, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp->x2222_flag.bits.b2 = 1;
    func_8007E2F4(fp, 0x1FFU);
    func_8007E2FC(fighter_gobj);
    ftMasterHand_80155B80(fp->x1A58_interactedFighter);
    fp->x234C_pos.x = attr->x118_pos.x;
    fp->x234C_pos.y = attr->x118_pos.y;
    fp->x234C_pos.z = 0.0f;
}

void ftMasterHand_80154B2C(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    s32 unused[2];

    fp = getFighter(fighter_gobj);
    if (fp->x2204_ftcmd_var1 != 0) {
        func_8015C5F8(fighter_gobj);
        fp->x2204_ftcmd_var1 = 0;
    }
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE) {
        if (((Fighter*) fighter_gobj->user_data)->sa.masterhand.x2250 == 0x17B) {
            ftMasterHand_80154E78(fighter_gobj);
        } else {
            ftMasterHand_80155014(fighter_gobj);
        }
    }
}

// 80154BB0 151790
void lbl_80154BB0(HSD_GObj* arg0) {
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(arg0);
    }
}



// 80154BF4 1517D4
// https://decomp.me/scratch/D7Kd4
void lbl_80154BF4(HSD_GObj* gobj) {
    Fighter* fp;
    MasterHandAttributes* attr;

    fp = gobj->user_data;
    attr = fp->x10C_ftData->ext_attr;
    func_80085134(gobj);
    func_8015BE40(gobj, &fp->x234C_pos, &fp->x2358_stateVar7, attr->x2C, attr->x28);
}



// 80154C54 151834
// https://decomp.me/scratch/Pp9nI
void lbl_80154C54(HSD_GObj* gobj) {
    f32 temp_f1;
    Fighter* fp;

    fp = gobj->user_data;
    if (fp->x2358_stateVar7 == 0.0f) {
        fp->x80_self_vel.z = 0.0f;
        fp->x80_self_vel.y = 0.0f;
        fp->x80_self_vel.x = 0.0f;
    }
}
