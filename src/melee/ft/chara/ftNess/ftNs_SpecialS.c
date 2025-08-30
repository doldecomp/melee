#include "ftNess/ftNs_SpecialS.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftNess/types.h"
#include "it/items/itnesspkfire.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MSL/trigf.h>

// https://decomp.me/scratch/apf7Y
void ftNs_SpecialS_ItemPKFireSpawn(
    HSD_GObj* gobj) //* Ness's PK Fire spawn function, stored as Accessory4
                    // and summoned with Subaction Event 0x60 *//
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr = fp->dat_attrs;
    bool FlagResult;
    Vec3 ItemBonePos;
    Vec3 PKFireVelStruct;
    float PKFireLaunchNew;

    u8 _[4];

    float PKFireRot;
    float PKFireLaunch;
    float PKFireVel;

    if (fp->throw_flags_b0 != 0) {
        fp->throw_flags_b0 = 0;
        FlagResult = true;
    } else {
        FlagResult = false;
    }

    if (FlagResult != false) {
        lb_8000B1CC(fp->parts[FtPart_R2ndNa].joint, NULL, &ItemBonePos);

        ItemBonePos.x += ness_attr->x30_PKFIRE_SPAWN_X * fp->facing_dir;
        ItemBonePos.y += ness_attr->x34_PKFIRE_SPAWN_Y;
        ItemBonePos.z = 0.0f;

        if (fp->ground_or_air == GA_Air) {
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

// 0x80116C94
// https://decomp.me/scratch/XdzmF
void ftNs_SpecialS_Enter(
    HSD_GObj* gobj) // Ness's grounded PK Fire Motion State handler
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->throw_flags = 0; // Set projectile summon flag to 0
    fp->cmd_vars[0] = 0; // Set ftcmd flag0 to 0; _ in PK Fire?
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialS, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb =
        ftNs_SpecialS_ItemPKFireSpawn; // Store PK Fire spawn function
}

// 0x80116D04
// https://decomp.me/scratch/fnaSW
void ftNs_SpecialAirS_Enter(
    HSD_GObj* gobj) // Ness's aerial PK Fire Motion State handler
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    fp->throw_flags = 0; // Set projectile summon flag to 0
    fp->cmd_vars[0] = 0; // Set ftcmd flag0 to 0; _ in PK Fire?
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirS, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = ftNs_SpecialS_ItemPKFireSpawn;
}

// 0x80116D74
// https://decomp.me/scratch/5NxzS
void ftNs_SpecialS_Anim(
    HSD_GObj* gobj) // Ness's grounded PK Fire Animation callback
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x80116DB0
// https://decomp.me/scratch/iFFHn
void ftNs_SpecialAirS_Anim(
    HSD_GObj* gobj) // Ness's aerial PK Fire Animation callback
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

// 0x80116DEC
// https://decomp.me/scratch/iCZHk
void ftNs_SpecialS_Phys(
    HSD_GObj* gobj) // Ness's grounded PK Fire Physics callback
{
    ft_80084F3C(gobj);
}

// 0x80116E0C
// https://decomp.me/scratch/ATut0
void ftNs_SpecialAirS_Phys(
    HSD_GObj* gobj) // Ness's aerial PK Fire Physics callback
{
    ft_80084EEC(gobj);
}

// 0x80116E2C
// https://decomp.me/scratch/gi1NE
void ftNs_SpecialS_Coll(
    HSD_GObj* gobj) // Ness's grounded PK Fire Collision callback
{
    if (ft_800827A0(gobj) == false) {
        ftCo_Fall_Enter(gobj);
    }
}

// 0x80116E68
// https://decomp.me/scratch/AEWUO
void ftNs_SpecialAirS_Coll(
    HSD_GObj* gobj) // Ness's aerial PK Fire Collision callback
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr;

    ness_attr = fp->dat_attrs;
    if (ft_80081D0C(gobj) != false) {
        ftCo_LandingFallSpecial_Enter(gobj, false, ness_attr->x38_PKFIRE_LANDING_LAG);
    }
}
