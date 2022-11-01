#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void lbl_80154FAC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(fighter_gobj);
    }
}

void lbl_80154FF0(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void lbl_80155010(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155014(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17C, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
}
