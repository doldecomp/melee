#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

#include <melee/ft/chara/ftCrazyHand/ftcrazyhand.h>

void ftMasterHand_80155074(HSD_GObj* fighter_gobj, unk_t, unk_t)
{
    Fighter* fp = fighter_gobj->user_data;

    if (fp->x2200_ftcmd_var0) {
        fp->x2200_ftcmd_var0 = FALSE;
        ftMasterHand_80155D6C(fp->x1A58_interactedFighter, 0x14A);

        if (fp->x1A58_interactedFighter != NULL) {
            HSD_GObj* other_gobj = fp->x1A58_interactedFighter;
            func_8007E2F4(fp, 0);
            func_800DE2A8(fighter_gobj, other_gobj);
            func_800DE7C0(other_gobj, 0, 0);
        }

        fp->x2360 = FALSE;
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}

void ftMasterHand_8015512C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftbosslib_8015BD20(fighter_gobj);
}

void ftMasterHand_80155170(HSD_GObj* fighter_gobj)
{
    func_80085134(fighter_gobj);
}

void ftMasterHand_80155190(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155194(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* other_gobj = ftbosslib_8015C3E8(FTKIND_CREZYH);

    if (!ftbosslib_8015C31C())
        ftCrazyHand_8015A2B0(other_gobj);

    fp->x1A5C = other_gobj;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17E, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
}
