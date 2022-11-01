#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80154D78(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fp = fighter_gobj->user_data;
        s32 unused[2];

        if (fp->x2360 == TRUE)
            ftMasterHand_80154A78(fighter_gobj);
        else
            ftMasterHand_801546D8(fighter_gobj);
    }
}

void ftMasterHand_80154DD0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(fighter_gobj);
    }
}

void ftMasterHand_80154E14(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    MasterHandAttributes* ext_attr = fp->x10C_ftData->ext_attr;

    func_80085134(fighter_gobj);
    func_8015BE40(fighter_gobj, &fp->x234C_pos, &fp->x2358_stateVar7, ext_attr->x2C, ext_attr->x28);
}

void ftMasterHand_80154E74(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80154E78(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x17B, 0, 0, 0.0F, 1.0F, 0.0F);
    func_8006EBA4(fighter_gobj);
    fp->x2200_ftcmd_var0 = FALSE;
}

void ftMasterHand_80154ED8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    HSD_GObj* gobj_2;
    Fighter* ft_2;
    s32 unused[2];

    if (fp->x2200_ftcmd_var0) {
        fp->x2200_ftcmd_var0 = FALSE;
        ftMasterHand_80155D6C(fp->x1A58_interactedFighter, 0x14A);
        if (fp->x1A58_interactedFighter != NULL) {
            gobj_2 = fp->x1A58_interactedFighter;
            ft_2 = gobj_2->user_data;
            func_8007E2F4(fp, 0);
            func_800DE2A8(fighter_gobj, gobj_2);
            ft_2->dmg.x1844_direction *= -1.0F;
            func_800DE7C0(gobj_2, 0, 0);
        }
        fp->x2360 = FALSE;
    }

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ftMasterHand_80151018(fighter_gobj);
}
