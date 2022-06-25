#include "ftNess.h"

extern void func_802AA054(HSD_GObj*, Vec3*, Vec3*, f32, f32);

// 0x80116B70 //
// https://decomp.me/scratch/apf7Y //
void lbl_80116B70(HSD_GObj* fighter_gobj) //* Ness's PK Fire spawn function, stored as Accessory4 and summoned with Subaction Event 0x60 *//
{
    Fighter* fighter_data = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    BOOL FlagResult;
    Vec3 ItemBonePos;
    Vec3 PKFireVelStruct;
    f32 PKFireLaunchNew;
    f32 PKFireLaunchAgain;
    f32 PKFire_Dir_x_Vel;
    f32 PKFireRot;
    f32 PKFireLaunch;
    f32 PKFireVel;


    if (fighter_data->x2210_ThrowFlags.b0 != 0)
    {
        fighter_data->x2210_ThrowFlags.b0 = 0;
        FlagResult = TRUE;
    }
    else
    {
        FlagResult = FALSE;
    }

    if (FlagResult != FALSE)
    {
        func_8000B1CC(fighter_data->x5E8_fighterBones[42].x0_jobj, 0, &ItemBonePos);

        ItemBonePos.x += ness_attr->x30_PKFIRE_SPAWN_X * fighter_data->x2C_facing_direction;
        ItemBonePos.y += ness_attr->x34_PKFIRE_SPAWN_Y;
        ItemBonePos.z = 0.0f;

        if (fighter_data->xE0_ground_or_air == 1)
        {
            PKFireLaunch = ness_attr->x20_PKFIRE_AERIAL_LAUNCH_TRAJECTORY;
            PKFireVel = ness_attr->x24_PKFIRE_AERIAL_VELOCITY;
        }
        else
        {
            PKFireLaunch = ness_attr->x28_PKFIRE_GROUNDED_LAUNCH_TRAJECTORY;
            PKFireVel = ness_attr->x2C_PKFIRE_GROUNDED_VELOCITY;
        }

        PKFireVelStruct.z = 0.0f;

        PKFireVelStruct.x = PKFireVel * cosf(PKFireLaunch) * fighter_data->x2C_facing_direction;

        PKFireLaunchNew = sinf(PKFireLaunch);

        PKFireVelStruct.y = PKFireVel * PKFireLaunchNew;

        PKFireRot = PKFireLaunch * fighter_data->x2C_facing_direction;

        func_802AA054(fighter_gobj, &ItemBonePos, &PKFireVelStruct, fighter_data->x2C_facing_direction, PKFireRot);
    }
}

// 0x80116C94 //
// https://decomp.me/scratch/XdzmF //
void func_80116C94(HSD_GObj* fighter_gobj)  // Ness's grounded PK Fire Action State handler //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x2210_ThrowFlags.flags = 0; // Set projectile summon flag to 0 //
    fighter_data->x2200_ftcmd_var0 = 0; // Set ftcmd flag0 to 0; unused in PK Fire? //
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALS, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fighter_data->cb.x21BC_callback_Accessory4 = lbl_80116B70; // Store PK Fire spawn function //
}

// 0x80116D04 //
// https://decomp.me/scratch/fnaSW //
void func_80116D04(HSD_GObj* fighter_gobj)  // Ness's aerial PK Fire Action State handler //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x2210_ThrowFlags.flags = 0; // Set projectile summon flag to 0 //
    fighter_data->x2200_ftcmd_var0 = 0; // Set ftcmd flag0 to 0; unused in PK Fire? //
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_NESS_SPECIALAIRS, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fighter_data->cb.x21BC_callback_Accessory4 = lbl_80116B70;
}

// 0x80116D74 //
// https://decomp.me/scratch/5NxzS //
void lbl_80116D74(HSD_GObj* fighter_gobj) // Ness's grounded PK Fire Animation callback //
{
    if (func_8006F238(fighter_gobj) == 0)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x80116DB0 //
// https://decomp.me/scratch/iFFHn //
void lbl_80116DB0(HSD_GObj* fighter_gobj) // Ness's aerial PK Fire Animation callback //
{
    if (func_8006F238(fighter_gobj) == 0)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x80116DEC //
// https://decomp.me/scratch/iCZHk //
void lbl_80116DEC(HSD_GObj* fighter_gobj) // Ness's grounded PK Fire Physics callback //
{
    func_80084F3C(fighter_gobj);
}

// 0x80116E0C //
// https://decomp.me/scratch/ATut0 //
void lbl_80116E0C(HSD_GObj* fighter_gobj) // Ness's aerial PK Fire Physics callback //
{
    func_80084EEC(fighter_gobj);
}

// 0x80116E2C //
// https://decomp.me/scratch/gi1NE //
void lbl_80116E2C(HSD_GObj* fighter_gobj) // Ness's grounded PK Fire Collision callback //
{
    if (func_800827A0(fighter_gobj) == 0)
    {
        func_800CC730(fighter_gobj);
    }
}

// 0x80116E68 //
// https://decomp.me/scratch/AEWUO //
void lbl_80116E68(HSD_GObj* fighter_gobj) // Ness's aerial PK Fire Collision callback //
{
    Fighter* fighter_data = getFighter(fighter_gobj);
    ftNessAttributes* ness_attr;

    ness_attr = fighter_data->x2D4_specialAttributes;
    if (func_80081D0C(fighter_gobj) != 0)
    {
        func_800D5CB0(fighter_gobj, 0, ness_attr->x38_PKFIRE_LANDING_LAG);
    }
}