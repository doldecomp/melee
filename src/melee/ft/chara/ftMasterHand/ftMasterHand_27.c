#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void lbl_80155074(HSD_GObj* fighter_gobj)
{
    s32 unused[2];
    Fighter* fp = fighter_gobj->user_data;
    if (fp->x2200_ftcmd_var0) {
        fp->x2200_ftcmd_var0 = FALSE;
        ftMasterHand_80155D6C(fp->x1A58_interactedFighter, 0x14A);
        if (fp->x1A58_interactedFighter != NULL) {
            HSD_GObj* gobj_2 = fp->x1A58_interactedFighter;
            func_8007E2F4(fp, 0);
            func_800DE2A8(fighter_gobj, gobj_2);
            func_800DE7C0(gobj_2, 0, 0);
        }
        fp->x2360 = FALSE;
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void lbl_8015512C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(fighter_gobj);
}

void lbl_80155170(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void lbl_80155190(HSD_GObj* fighter_gobj)
{
    return;
}

void lbl_80155194(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* gobj_2 = func_8015C3E8(0x1C);

    if (!func_8015C31C())
        func_8015A2B0(gobj_2);

    fp->x1A5C = gobj_2;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17E, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
}
