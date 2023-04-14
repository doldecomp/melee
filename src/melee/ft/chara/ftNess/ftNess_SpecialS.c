#include "ft/chara/ftNess/ftNess.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <MSL/trigf.h>

// https://decomp.me/scratch/apf7Y //
void ftNess_ItemPKFireSpawn(
    HSD_GObj* gobj) //* Ness's PK Fire spawn function, stored as Accessory4
                    // and summoned with Subaction Event 0x60 *//
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    bool FlagResult;
    Vec3 ItemBonePos;
    Vec3 PKFireVelStruct;
    f32 PKFireLaunchNew;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    f32 PKFireRot;
    f32 PKFireLaunch;
    f32 PKFireVel;

    if (fp->x2210_ThrowFlags.b0 != 0) {
        fp->x2210_ThrowFlags.b0 = 0;
        FlagResult = true;
    } else {
        FlagResult = false;
    }

    if (FlagResult != false) {
        lb_8000B1CC(fp->x5E8_fighterBones[42].x0_jobj, NULL, &ItemBonePos);

        ItemBonePos.x += ness_attr->x30_PKFIRE_SPAWN_X * fp->facing_dir;
        ItemBonePos.y += ness_attr->x34_PKFIRE_SPAWN_Y;
        ItemBonePos.z = 0.0f;

        if (fp->xE0_ground_or_air == GA_Air) {
            PKFireLaunch = ness_attr->x20_PKFIRE_AERIAL_LAUNCH_TRAJECTORY;
            PKFireVel = ness_attr->x24_PKFIRE_AERIAL_VELOCITY;
        } else {
            PKFireLaunch = ness_attr->x28_PKFIRE_GROUNDED_LAUNCH_TRAJECTORY;
            PKFireVel = ness_attr->x2C_PKFIRE_GROUNDED_VELOCITY;
        }

        PKFireVelStruct.z = 0.0f;

        PKFireVelStruct.x = PKFireVel * cosf(PKFireLaunch) * fp->facing_dir;

        PKFireLaunchNew = sinf(PKFireLaunch);

        PKFireVelStruct.y = PKFireVel * PKFireLaunchNew;

        PKFireRot = PKFireLaunch * fp->facing_dir;

        it_802AA054(gobj, &ItemBonePos, &PKFireVelStruct, fp->facing_dir,
                    PKFireRot);
    }
}

// 0x80116C94 //
// https://decomp.me/scratch/XdzmF //
void ftNess_SpecialS_StartMotion(
    HSD_GObj* gobj) // Ness's grounded PK Fire Motion State handler //
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->x2210_ThrowFlags.flags = 0; // Set projectile summon flag to 0 //
    fp->x2200_ftcmd_var0 = 0;       // Set ftcmd flag0 to 0; _ in PK Fire? //
    Fighter_ChangeMotionState(gobj, AS_NESS_SPECIALS, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 =
        ftNess_ItemPKFireSpawn; // Store PK Fire spawn function //
}

// 0x80116D04 //
// https://decomp.me/scratch/fnaSW //
void ftNess_SpecialAirS_Action(
    HSD_GObj* gobj) // Ness's aerial PK Fire Motion State handler //
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->x2210_ThrowFlags.flags = 0; // Set projectile summon flag to 0 //
    fp->x2200_ftcmd_var0 = 0;       // Set ftcmd flag0 to 0; _ in PK Fire? //
    Fighter_ChangeMotionState(gobj, AS_NESS_SPECIALAIRS, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftNess_ItemPKFireSpawn;
}

// 0x80116D74 //
// https://decomp.me/scratch/5NxzS //
void ftNess_SpecialS_Anim(
    HSD_GObj* gobj) // Ness's grounded PK Fire Animation callback //
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x80116DB0 //
// https://decomp.me/scratch/iFFHn //
void ftNess_SpecialAirS_Anim(
    HSD_GObj* gobj) // Ness's aerial PK Fire Animation callback //
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

// 0x80116DEC //
// https://decomp.me/scratch/iCZHk //
void ftNess_SpecialS_Phys(
    HSD_GObj* gobj) // Ness's grounded PK Fire Physics callback //
{
    ft_80084F3C(gobj);
}

// 0x80116E0C //
// https://decomp.me/scratch/ATut0 //
void ftNess_SpecialAirS_Phys(
    HSD_GObj* gobj) // Ness's aerial PK Fire Physics callback //
{
    ft_80084EEC(gobj);
}

// 0x80116E2C //
// https://decomp.me/scratch/gi1NE //
void ftNess_SpecialS_Coll(
    HSD_GObj* gobj) // Ness's grounded PK Fire Collision callback //
{
    if (ft_800827A0(gobj) == false) {
        ft_800CC730(gobj);
    }
}

// 0x80116E68 //
// https://decomp.me/scratch/AEWUO //
void ftNess_SpecialAirS_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Fire Collision callback //
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr;

    ness_attr = fp->x2D4_specialAttributes;
    if (ft_80081D0C(gobj) != false) {
        ft_800D5CB0(gobj, 0, ness_attr->x38_PKFIRE_LANDING_LAG);
    }
}
