#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80155C88(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155C8C(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155C90(HSD_GObj* fighter_gobj)
{
    return;
}

#include <melee/ft/ftanim.h>

void ftMasterHand_80155C94(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 329, 0, 0, 0.0F, 1.0F, 0.0F);

    fp->x221E_flag.bits.b0 = TRUE;
    func_8007E2F4(fp, 511);

    fp->x2220_flag.bits.b3 = TRUE;
    func_8006EBA4(fighter_gobj);
}
