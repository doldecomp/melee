#include "ftFx_SpecialHi.h"

#include "math.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftFox/types.h"
#include "lb/lbrefract.h"
#include "lb/lbvector.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

#define FTFOX_SPECIALHI_COLL_FLAG                                             \
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_UpdateCmd | Ft_MF_SkipColAnim | \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

/// @todo Move elsewhere.
#define HALF_PI32 (1.5707963705062866f)

/// @todo Move elsewhere.
#define DOUBLE_PI32 (6.2831854820251465f)

void ftFx_SpecialHi_CreateLaunchGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        efSync_Spawn(1164, gobj,
                     fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].joint);

        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftFx_SpecialHi_CreateChargeGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        efSync_Spawn(1163, gobj,
                     fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN)].joint);

        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

void ftFx_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp;
    ftFox_DatAttrs* da;

    fp = GET_FIGHTER(gobj);
    da = getFtSpecialAttrs(fp);

    fp->mv.fx.SpecialHi.gravityDelay = da->x54_FOX_FIREFOX_GRAVITY_DELAY;
    fp->gr_vel /= da->x58_FOX_FIREFOX_VEL_X;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiHold, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);

    fp->accessory4_cb = ftFx_SpecialHi_CreateChargeGFX;
}

void ftFx_SpecialAirHiStart_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    fp->mv.fx.SpecialHi.gravityDelay = da->x54_FOX_FIREFOX_GRAVITY_DELAY;
    fp->self_vel.x /= da->x58_FOX_FIREFOX_VEL_X;
    fp->self_vel.y = 0.0f;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiHoldAir, 0, 0.0f, 1.0f,
                              0.0f, NULL);

    ftAnim_8006EBA4(gobj);

    fp->accessory4_cb = ftFx_SpecialHi_CreateChargeGFX;
}

static void ftFox_SpecialHi_RotateModel(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_8007592C(fp, ftParts_GetBoneIndex(fp, FtPart_XRotN),
                     2 * (float) M_PI - fp->mv.fx.SpecialHi.rotateModel);
}

void ftFx_SpecialHiHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialAirHi_Enter(gobj);
            return;
        }

        ftFx_SpecialAirHi_AirToGround(gobj);
    }
}

void ftFx_SpecialHiHoldAir_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialAirHi_Enter(gobj);
            return;
        }
        ftFx_SpecialAirHi_AirToGround(gobj);
    }
}

void ftFx_SpecialHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFx_SpecialHiHoldAir_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFx_SpecialHiHold_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftFx_SpecialHiHoldAir_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;
    ftCo_DatAttrs* ca = &fp->co_attrs;

    u8 _[8];

    if (fp->mv.fx.SpecialHi.gravityDelay != 0) {
        fp->mv.fx.SpecialHi.gravityDelay -= 1;
    } else {
        ftCommon_Fall(fp, da->x60_FOX_FIREFOX_FALL_ACCEL, ca->terminal_vel);
    }

    ftCommon_ApplyFrictionAir(fp, da->x5C_FOX_FIREFOX_AIR_MOMENTUM_PRESERVE_X);
}

void ftFx_SpecialHiHold_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == false) {
        ftFx_SpecialHiHold_GroundToAir(gobj);
    }
}

void ftFx_SpecialHiHoldAir_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facingDir;

    /// @todo Ternary operator should be possible here somehow.
    if (fp->facing_dir < 0.0f) {
        facingDir = -1;
    } else {
        facingDir = 1;
    }

    if (ft_CheckGroundAndLedge(gobj, facingDir)) {
        ftFx_SpecialHiHoldAir_AirToGround(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

void ftFx_SpecialHiHold_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiHoldAir,
                              FTFOX_SPECIALHI_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);

    fp->accessory4_cb = ftFx_SpecialHi_CreateChargeGFX;
}

void ftFx_SpecialHiHoldAir_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiHold,
                              FTFOX_SPECIALHI_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);

    fp->accessory4_cb = ftFx_SpecialHi_CreateChargeGFX;

    ftCommon_ClampAirDrift(fp);
}

void ftFx_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Common inline with #ftFx_SpecialAirHi_Anim.
    fp->mv.fx.SpecialHi.travelFrames--;

    if (fp->mv.fx.SpecialHi.travelFrames <= 0) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialHiLanding_GroundToAir(gobj);
            return;
        }

        ftFx_SpecialHiFall_AirToGround(gobj);
    }
}

void ftFx_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.fx.SpecialHi.travelFrames--;

    if (fp->mv.fx.SpecialHi.travelFrames <= 0) {
        if (fp->ground_or_air == GA_Air) {
            ftFx_SpecialHiLanding_GroundToAir(gobj);
            return;
        }

        ftFx_SpecialHiFall_AirToGround(gobj);
    }
}

void ftFx_SpecialHi_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFx_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFx_SpecialHi_Phys(HSD_GObj* gobj)
{
    /// @todo Possibly common inline with #ftFx_SpecialAirHi_Phys.
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    fp->mv.fx.SpecialHi.unk++;

    if (fp->mv.fx.SpecialHi.unk >= da->x70_FOX_FIREFOX_DURATION_END) {
        ftCommon_ApplyFrictionGround(fp, da->x78_FOX_FIREFOX_REVERSE_ACCEL);
    }

    ftCommon_ApplyGroundMovement(gobj);
}

void ftFx_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFox_DatAttrs* da = da = getFtSpecialAttrs(fp);

    fp->mv.fx.SpecialHi.unk++;

    if (fp->mv.fx.SpecialHi.unk >= da->x70_FOX_FIREFOX_DURATION_END) {
        fp->self_vel.x =
            -((fp->facing_dir * (da->x78_FOX_FIREFOX_REVERSE_ACCEL *
                                 cosf(fp->mv.fx.SpecialHi.rotateModel))) -
              fp->self_vel.x);
        fp->self_vel.y = -((da->x78_FOX_FIREFOX_REVERSE_ACCEL *
                            sinf(fp->mv.fx.SpecialHi.rotateModel)) -
                           fp->self_vel.y);
    }
}

void ftFx_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->coll_data;

    fp->mv.fx.SpecialHi.unk2 += 1;

    if (ft_80082708(gobj) == false) {
        ftFx_SpecialHi_GroundToAir(gobj);
        return;
    }

    if (collData->env_flags & Collide_FloorMask) {
        fp->mv.fx.SpecialHi.rotateModel =
            atan2f(-collData->floor.normal.x * fp->facing_dir,
                   collData->floor.normal.y);
        ftFox_SpecialHi_RotateModel(gobj);
    }
}

static inline bool ftFox_SpecialHi_IsBound(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    if (fp->mv.fx.SpecialHi.unk2 >= da->x6C_FOX_FIREFOX_BOUNCE_VAR) {
        return true;
    } else if (ftCo_8009A134(gobj)) {
        return false;
    } else {
        return true;
    }
}

/// @todo Rework this entire match.
void ftFx_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    float facingDir;

    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = da = getFtSpecialAttrs(fp);
    CollData* collData = collData = getFtColl(fp);

    if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_BOTH)) {
        if (ftFox_SpecialHi_IsBound(gobj)) {
            if (!(collData->env_flags & Collide_FloorMask) ||
                (!(lbVector_AngleXY(&collData->floor.normal, &fp->self_vel) <
                   (0.01745329238474369f *
                    (90.0f + da->x94_FOX_FIREFOX_BOUND_ANGLE)))))
            {
                ftFx_SpecialHiBound_Enter(gobj);
                return;
            } else {
                goto facingDir;
            }
        }
    }

    /** @remarks Not a single line of this entire function makes the slightest
     * sliver of sense but it matches so whatever :D
     * @todo This match is definitely fake.
     */
    if (ftCliffCommon_80081298(gobj) == false) {
        s32 envFlags = collData->env_flags;
        float var;
        do {
            if (envFlags & Collide_CeilingMask) {
                var =
                    lbVector_AngleXY(&collData->ceiling.normal, &fp->self_vel);
            } else if (envFlags & Collide_LeftWallMask) {
                var = lbVector_AngleXY(&collData->left_facing_wall.normal,
                                       &fp->self_vel);
            } else if (envFlags & Collide_RightWallMask) {
                var = lbVector_AngleXY(&collData->right_facing_wall.normal,
                                       &fp->self_vel);
            } else {
                if (((!fp->self_vel.x) && (!fp->self_vel.x)) &&
                    (!fp->self_vel.x)) // ??????
                {
                }
                break;
            }

            if (var < (0.01745329238474369f *
                       (90.0f + da->x94_FOX_FIREFOX_BOUND_ANGLE)))
            {
                goto facingDir;
            } else {
                continue;
            }

        } while (false); // What?

        return;

        {
        facingDir:
            if (fp->self_vel.x >= 0.0f) {
                facingDir = 1.0f;
            } else {
                facingDir = -1.0f;
            }

            fp->facing_dir = facingDir;
            fp->mv.fx.SpecialHi.rotateModel =
                atan2f(fp->self_vel.y, fp->self_vel.x * fp->facing_dir);
            ftFox_SpecialHi_RotateModel(gobj);
        }
    }
}

void ftFx_SpecialHi_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    ftCommon_8007D60C(fp);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirHi,
                              (Ft_MF_SkipHit | FTFOX_SPECIALHI_COLL_FLAG),
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);

    fp->x2223_b4 = true;
    fp->accessory4_cb = ftFx_SpecialHi_CreateLaunchGFX;
}

void ftFx_SpecialAirHi_AirToGround(HSD_GObj* gobj)
{
    Vec3 sp20;
    ftFox_DatAttrs* da;
    Fighter* fp;
    CollData* collData;
    ftFox_DatAttrs* tempAttrs;
    float temp_stick;
    float stick_x;
    float stick_y;

    fp = GET_FIGHTER(gobj);
    stick_y = fp->input.lstick.y;

    collData = getFtColl(fp);
    da = fp->dat_attrs;

    if (stick_y < 0.0f) {
        stick_y = -stick_y;
    }
    temp_stick = fp->input.lstick.x;
    stick_x = stickGetDir(fp->input.lstick.x, 0.0f);

    if (!((stick_x + stick_y) < da->x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN))
    {
        sp20.x = temp_stick;
        sp20.y = fp->input.lstick.y;
        sp20.z = 0.0f;

        if (!(lbVector_AngleXY(&collData->floor.normal, &sp20) < HALF_PI32) &&
            (ftCo_8009A134(gobj) == false))
        {
            ftCommon_UpdateFacing(fp);

            Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHi, 0, 0.0f, 1.0f,
                                      0.0f, NULL);

            tempAttrs = fp->dat_attrs;
            fp->x2223_b4 = 1;

            fp->mv.fx.SpecialHi.travelFrames =
                tempAttrs->x68_FOX_FIREFOX_DURATION;

            fp->mv.fx.SpecialHi.unk = 0.0f;
            fp->mv.fx.SpecialHi.unk2 = 0.0f;

            fp->gr_vel = da->x74_FOX_FIREFOX_SPEED * fp->facing_dir;

            fp->mv.fx.SpecialHi.rotateModel =
                atan2f(-collData->floor.normal.x * fp->facing_dir,
                       collData->floor.normal.y);

            ftFox_SpecialHi_RotateModel(gobj);
            fp->accessory4_cb = ftFx_SpecialHi_CreateLaunchGFX;
            fp->x21F8 = ftCommon_8007F76C;
            return;
        }
    }
    ftCommon_8007D60C(fp);
    ftFx_SpecialAirHi_Enter(gobj);
}

// 0x800E7C98
// https://decomp.me/scratch/k5tbJ // Fox & Falco's aerial Firefox/Firebird
// Launch Motion State handler
void ftFx_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    ftFox_DatAttrs* da;
    ftCo_DatAttrs* ca;
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* tempAttrs;
    float stick_x;
    float stick_y;
    float temp_stick;

    ca = &fp->co_attrs;
    da = fp->dat_attrs;

    stick_y = stickGetDir(fp->input.lstick.y, 0.0f);

    temp_stick = fp->input.lstick.x;

    stick_x = stickGetDir(temp_stick, 0.0f);

    if ((stick_x + stick_y) >= da->x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN) {
        if (temp_stick < 0.0f) {
            temp_stick = -temp_stick;
        }
        if (temp_stick > da->x88_FOX_FIREFOX_FACING_STICK_RANGE_MIN) {
            ftCommon_UpdateFacing(fp);
        }
        fp->mv.fx.SpecialHi.rotateModel =
            atan2f(fp->input.lstick.y, fp->input.lstick.x * fp->facing_dir);
    } else {
        fp->mv.fx.SpecialHi.rotateModel = HALF_PI32;
    }

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialAirHi, 0, 0.0f, 1.0f, 0.0f,
                              NULL);

    tempAttrs = fp->dat_attrs;
    fp->x2223_b4 = 1;

    fp->mv.fx.SpecialHi.travelFrames = tempAttrs->x68_FOX_FIREFOX_DURATION;
    fp->mv.fx.SpecialHi.unk = 0;
    fp->mv.fx.SpecialHi.unk2 = 0;

    fp->self_vel.x = fp->facing_dir * (da->x74_FOX_FIREFOX_SPEED *
                                       cosf(fp->mv.fx.SpecialHi.rotateModel));
    fp->self_vel.y =
        da->x74_FOX_FIREFOX_SPEED * sinf(fp->mv.fx.SpecialHi.rotateModel);
    ftFox_SpecialHi_RotateModel(gobj);
    fp->x21F8 = ftCommon_8007F76C;
    fp->accessory4_cb = ftFx_SpecialHi_CreateLaunchGFX;
    fp->x1968_jumpsUsed = ca->max_jumps;
}

// 0x800E7E3C
// https://decomp.me/scratch/FiAfN // Fox & Falco's grounded Firefox/Firebird
// End Animation callback
void ftFx_SpecialHiLanding_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x800E7E78
// https://decomp.me/scratch/COhLZ // Fox & Falco's aerial Firefox/Firebird End
// Animation callback
void ftFx_SpecialHiFall_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 1, 0, true, da->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      da->x90_FOX_FIREFOX_LANDING_LAG);
    }
}

// 0x800E7ED8 - Fox & Falco's grounded Firefox/Firebird End IASA callback
void ftFx_SpecialHiLanding_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E7EDC - Fox & Falco's aerial Firefox/Firebird End IASA callback
void ftFx_SpecialHiFall_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E7EE0
// https://decomp.me/scratch/eHUMt // Fox & Falco's grounded Firefox/Firebird
// End Physics callback
void ftFx_SpecialHiLanding_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFox_DatAttrs* da = getFtSpecialAttrs(fp);

    ftCommon_ApplyFrictionGround(fp, da->x7C_FOX_FIREFOX_GROUND_MOMENTUM_END);
    ftCommon_ApplyGroundMovement(gobj);
}

// 0x800E7F20 - Fox & Falco's aerial Firefox/Firebird End Physics callback
void ftFx_SpecialHiFall_Phys(HSD_GObj* gobj)
{
    ft_80084DB0(gobj);
}

// 0x800E7F40
// https://decomp.me/scratch/JEGS6 // Fox & Falco's grounded Firefox/Firebird
// End Collision callback
void ftFx_SpecialHiLanding_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    if (ft_80082708(gobj) == false) {
        ftCo_80096900(gobj, 1, 0, true, da->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      da->x90_FOX_FIREFOX_LANDING_LAG);
    }
}

// 0x800E7FA0
// https://decomp.me/scratch/0Veb7 // Fox & Falco's aerial Firefox/Firebird End
// Collision callback
void ftFx_SpecialHiFall_Coll(HSD_GObj* gobj)
{
    u8 _[8];

    if (ft_CheckGroundAndLedge(gobj, CLIFFCATCH_BOTH)) {
        ftFx_SpecialHiFall_Enter(gobj);
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

// 0x800E7FF0
// https://decomp.me/scratch/IQ1YX // Fox & Falco's aerial Firefox/Firebird End
// Motion State handler
void ftFx_SpecialHiFall_Enter(HSD_GObj* gobj)
{
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiLanding,
                              (Ft_MF_SkipColAnim | Ft_MF_UpdateCmd), 13.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

// 0x800E8048
// https://decomp.me/scratch/rGuhz // Fox & Falco's ground -> air
// Firefox/Firebird End Motion State handler
void ftFx_SpecialHiFall_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007DB24(gobj);
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiLanding, 0, 0.0f, 1.0f,
                              0.0f, NULL);
    fp->x21F8 = ftCommon_8007F76C;
}

// 0x800E80C0
// https://decomp.me/scratch/YjAsa // Fox & Falco's Firefox/Firebird End ->
// Rebound Collision thing
void ftFx_SpecialHiLanding_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007DB24(gobj);

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiFall, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    fp->x21F8 = ftCommon_8007F76C;
}

// 0x800E8124
// https://decomp.me/scratch/SSvDi // Fox & Falco's Firefox/Firebird Rebound
// Animation callback
void ftFx_SpecialHiBound_Anim(HSD_GObj* gobj)
{
    ftCo_DatAttrs* ca;
    Fighter* fp;
    ftFox_DatAttrs* da;

    u8 _[4];

    fp = GET_FIGHTER(gobj);
    ca = &fp->co_attrs;
    da = fp->dat_attrs;

    if (fp->cmd_vars[0] != 0 && fp->ground_or_air == GA_Air) {
        ftCo_80096900(gobj, 1, 0, true, da->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      da->x90_FOX_FIREFOX_LANDING_LAG);
        fp->x1968_jumpsUsed = (u8) ca->max_jumps;
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->ground_or_air == GA_Air) {
            ftCo_80096900(gobj, 1, 0, true,
                          da->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                          da->x90_FOX_FIREFOX_LANDING_LAG);
            fp->x1968_jumpsUsed = (u8) ca->max_jumps;
            return;
        }
        ft_8008A2BC(gobj);
    }
}

// 0x800E81FC - Fox & Falco's Firefox/Firebird Rebound IASA callback
void ftFx_SpecialHiBound_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E8200
// https://decomp.me/scratch/nIsRU // Fox & Falco's Firefox/Firebird Rebound
// Physics callback
void ftFx_SpecialHiBound_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool ground_or_air = ftGetGroundAir(fp);

    if (ground_or_air == GA_Air) {
        ft_800851C0(gobj);
        ftCommon_8007CF58(fp);
        return;
    }
    ft_80084F3C(gobj);
}

// 0x800E824C
// https://decomp.me/scratch/iGtSK // Fox & Falco's Firefox/Firebird Rebound
// Collision callback
void ftFx_SpecialHiBound_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 cliffCatchDir;

    if (fp->ground_or_air == GA_Air) {
        if (fp->facing_dir < 0.0f) {
            cliffCatchDir = -1;
        } else {
            cliffCatchDir = 1;
        }

        if (ft_CheckGroundAndLedge(gobj, cliffCatchDir)) {
            ftCommon_8007D7FC(fp);
            return;
        }

        if (ftCliffCommon_80081298(gobj)) {
            return;
        }
    }

    else
    {
        ft_80084104(gobj);
    }
}

inline void ftFox_SpecialHiBound_SetVars(HSD_GObj* gobj)
{
    vf32 f; // I have a feeling this is a Vec3 struct however
    Fighter* fp = fp = gobj->user_data;
    CollData* collData = collData = getFtColl(fp);

    if (fp->coll_data.env_flags & Collide_FloorMask) {
        f = -atan2f(collData->floor.normal.x, collData->floor.normal.y);
    } else {
        f = 0.0f;
    }
    efSync_Spawn(1030, gobj, &fp->cur_pos, &f);
    fp->x2219_b0 = true;
    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

// 0x800E82E4
// https://decomp.me/scratch/ckSnm // Fox & Falco's Firefox/Firebird Rebound
// Motion State handler
void ftFx_SpecialHiBound_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFox_DatAttrs* da = fp->dat_attrs;

    Fighter_ChangeMotionState(gobj, ftFx_MS_SpecialHiBound, 0, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->x21F8 = ftCommon_8007F76C;
    fp->self_vel.x *= da->x84_FOX_FIREFOX_BOUND_VEL_X;
    fp->cmd_vars[0] = 0;
    ftFox_SpecialHiBound_SetVars(gobj);
}
