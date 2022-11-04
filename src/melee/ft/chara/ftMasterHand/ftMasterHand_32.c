#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80155B70(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155B74(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155B78(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155B7C(HSD_GObj* fighter_gobj)
{
    return;
}

#include <melee/ft/ftanim.h>

void ftMasterHand_80155B80(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 328, 0, 0, 0.0F, 1.0F, 0.0F);

    fp->x221E_flag.bits.b0 = TRUE;
    fp->x2220_flag.bits.b3 = TRUE;

    fp->cb.x21B0_callback_Accessory1 = &func_800DB464;
    func_8007E2F4(fp, 511);
    fp->x2220_flag.bits.b3 = TRUE;
    func_8006EBA4(fighter_gobj);
}

void ftMasterHand_80155C20(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    func_8007DC08(fp, p_ftCommonData->x3A8);

    if (fp->x1A4C <= 0.0F) {
        ftMasterHand_80155C94(fighter_gobj);
        ftMasterHand_8015483C(fp->x1A58_interactedFighter);
    }
}
