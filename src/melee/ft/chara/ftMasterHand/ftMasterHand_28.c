#include <melee/ft/chara/ftCrazyHand/ftcrazyhand.h>
#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_8015521C(HSD_GObj* fighter_gobj)
{
    if (func_8015C31C() || func_8015C3A0() || !ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;
        Fighter_UnkSetFlag_8006CFBC(fighter_gobj);
        fp->x1A5C = NULL;
        ftMasterHand_80151018(fighter_gobj);
    }
}

void ftMasterHand_80155290(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_801552D4(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_801552F4(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_801552F8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* gobj_2;

    fp->x2204_ftcmd_var1 = FALSE;
    gobj_2 = ftbosslib_8015C3E8(0x1CU);

    if (!func_8015C31C())
        ftCrazyHand_8015A3F4(gobj_2);

    fp->x1A5C = gobj_2;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17F, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}
