#include <melee/ft/chara/ftMasterHand/__ftMasterHand.h>

void ftMasterHand_80155D1C(HSD_GObj* interacted_fighter_gobj)
{
    Fighter* fp = interacted_fighter_gobj->user_data;
    fp->x221E_flag.bits.b0 = FALSE;
    fp->x2C_facing_direction = -fp->x2C_facing_direction;
    func_800DC750(interacted_fighter_gobj);
}

void ftMasterHand_80155D5C(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155D60(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155D64(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155D68(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155D6C(HSD_GObj* interacted_fighter_gobj, s32 unused_arg)
{
    Fighter* fp = interacted_fighter_gobj->user_data;
    s32 unused_stack[6];

    fp->x2C_facing_direction = ((Fighter*) fp->x1A58_interactedFighter->user_data)->x2C_facing_direction;
    fp->x2340_stateVar1 = FALSE;
    Fighter_ActionStateChange_800693AC(interacted_fighter_gobj, 0x14A, 0, 0, 0.0F, 1.0F, 0.0F);
    fp->x221E_flag.bits.b0 = FALSE;
    fp->cb.x21B0_callback_Accessory1 = &func_800DE508;
    func_8007E2F4(fp, 0x1FFU);
    func_8006EBA4(interacted_fighter_gobj);
}

void ftMasterHand_80155E08(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155E0C(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155E10(HSD_GObj* fighter_gobj)
{
    return;
}

void ftMasterHand_80155E14(HSD_GObj* fighter_gobj)
{
    return;
}
