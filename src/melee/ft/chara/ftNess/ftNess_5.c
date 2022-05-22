#include "ftNess.h"

extern void func_802AA054(float, float, HSD_GObj*, Vec3*, Vec3*);

// 0x80116B70 //
// https://decomp.me/scratch/apf7Y //
void lbl_80116B70(HSD_GObj* fighter_gobj) //* Ness's PK Fire spawn function, stored as Accessory4 and summoned with Subaction Event 0x60 *//
{
    Fighter* fighter_data = fighter_gobj->user_data;
    ftNessAttributes* ness_attr = fighter_data->x2D4_specialAttributes;
    int FlagResult;
    Vec3 ItemBonePos;
    Vec3 PKFireVelStruct;
    float PKFireLaunchNew;
    float PKFireLaunchAgain;
    float PKFire_Dir_x_Vel;
    float PKFireRot;
    float PKFireLaunch;
    float PKFireVel;


    if (fighter_data->x2210_ThrowFlags.b0 != 0)
    {
        fighter_data->x2210_ThrowFlags.b0 = 0;
        FlagResult = 1;
    }
    else
    {
        FlagResult = 0;
    }

    if (FlagResult != 0)
    {
        func_8000B1CC(fighter_data->x5E8_fighterBones[42].x0_jobj, 0, &ItemBonePos);

        ItemBonePos.x += ness_attr->x30_PKFIRE_SPAWN_X * fighter_data->x2C_facing_direction;
        ItemBonePos.y += ness_attr->x34_PKFIRE_SPAWN_Y;
        ItemBonePos.z = 0.0f;

        if (fighter_data->xE0_ground_or_air == 1)
        {
            PKFireLaunch = ness_attr->x20_AERIAL_LAUNCH_TRAJECTORY;
            PKFireVel = ness_attr->x24_AERIAL_VELOCITY;
        }
        else
        {
            PKFireLaunch = ness_attr->x28_GROUNDED_LAUNCH_TRAJECTORY;
            PKFireVel = ness_attr->x2C_GROUNDED_VELOCITY;
        }

        PKFireVelStruct.z = 0.0f;

        PKFireVelStruct.x = PKFireVel * cosf(PKFireLaunch) * fighter_data->x2C_facing_direction;

        PKFireLaunchNew = sinf(PKFireLaunch);

        PKFireVelStruct.y = PKFireVel * PKFireLaunchNew;

        PKFireRot = PKFireLaunch * fighter_data->x2C_facing_direction;

        func_802AA054(fighter_data->x2C_facing_direction, PKFireRot, fighter_gobj, &ItemBonePos, &PKFireVelStruct);
    }
}

// 0x80116C94 //
// https://decomp.me/scratch/XdzmF //
void func_80116C94(HSD_GObj* fighter_gobj)  // Ness's grounded PK Fire Action State handler //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x2210_ThrowFlags.flags = 0;
    fighter_data->x2200_ftcmd_var0 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fighter_data->cb.x21BC_callback_Accessory4 = lbl_80116B70;
}

// 0x80116D04 //
// https://decomp.me/scratch/fnaSW //
void func_80116D04(HSD_GObj* fighter_gobj)  // Ness's aerial PK Fire Action State handler //
{
    Fighter* fighter_data;

    fighter_data = fighter_gobj->user_data;
    fighter_data->x2210_ThrowFlags.flags = 0;
    fighter_data->x2200_ftcmd_var0 = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x165, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fighter_data->cb.x21BC_callback_Accessory4 = lbl_80116B70;
}