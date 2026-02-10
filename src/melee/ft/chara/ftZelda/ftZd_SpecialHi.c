#include "ftZd_SpecialHi.h"

#include <platform.h>

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftZelda/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"

#include <common_structs.h>
#include <math.h>
#include <trigf.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftZd_SpecialHi_801396AC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZd_SpecialHi_801396E0(gobj);
    fp->accessory4_cb = NULL;
}

void ftZd_SpecialHi_801396E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        Vec3 vec;
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, NULL, &vec);

        if (fp->ground_or_air == GA_Ground) {
            efSync_Spawn(1270, gobj, fp->parts->joint);
        } else {
            efSync_Spawn(1271, gobj, fp->parts->joint);
        }

        fp->x2219_b0 = true;
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
}

void ftZd_SpecialHi_8013979C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    {
        Vec3 vec;
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, NULL, &vec);

        if (!fp->x2219_b0) {
            efSync_Spawn(1285, gobj, &vec);
            fp->x2219_b0 = true;
        }
    }

    fp->pre_hitlag_cb = efLib_PauseAll;
    fp->post_hitlag_cb = efLib_ResumeAll;
    fp->accessory4_cb = NULL;
}

static void ftZelda_SpecialHi_StartAction_Helper(Fighter* fp)
{
    u8 _[4];
    _[0] = 0;

    {
        ssize_t boneIndex = ftParts_GetBoneIndex(fp, 4);
        HSD_JObj* jObj = fp->parts[boneIndex].joint;

        {
            Vec3 vec;
            lb_8000B1CC(jObj, NULL, &vec);

            lb_800119DC(&vec, 120, 1.5f, 0.02, 60 * (float) M_PI / 180);
        }
    }
}

void ftZd_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = getFighterPlus(gobj);

    fp->gr_vel = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;

    Fighter_ChangeMotionState(gobj, 349, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    fp = getFighterPlus(gobj);
    fp->cmd_vars[0] = 0;
    fp->mv.zd.specialhi.xC = 0;

    ftZelda_SpecialHi_StartAction_Helper(fp);

    fp->accessory4_cb = &ftZd_SpecialHi_801396AC;
}

void ftZd_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftZelda_DatAttrs* attributes = fp->dat_attrs;

        fp->self_vel.x = fp->self_vel.x / attributes->x38;
        fp->self_vel.y = fp->self_vel.y / attributes->x3C;

        Fighter_ChangeMotionState(gobj, 352, 0, 0, 1, 0, NULL);
        ftAnim_8006EBA4(gobj);
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cmd_vars[0] = 0;
        fp->mv.zd.specialhi.xC = 0;

        {
            Vec3 vec;

            u8 _[20];

            ssize_t boneIndex = ftParts_GetBoneIndex(fp, 4);
            HSD_JObj* jObj = fp->parts[boneIndex].joint;

            lb_8000B1CC(jObj, NULL, &vec);
            lb_800119DC(&vec, 120, 1.5, 0.02, 60 * (float) M_PI / 180);
        }

        fp->accessory4_cb = &ftZd_SpecialHi_801396AC;
    }
}

void ftZd_SpecialHiStart_0_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftZd_SpecialHi_8013A058(gobj);
    }
}

void ftZd_SpecialAirHiStart_0_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftZd_SpecialHi_8013A244(gobj);
    }
}

void ftZd_SpecialHiStart_0_IASA(HSD_GObj* gobj) {}

void ftZd_SpecialAirHiStart_0_IASA(HSD_GObj* gobj) {}

void ftZd_SpecialHiStart_0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftZd_SpecialAirHiStart_0_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* attributes = fp->dat_attrs;
    Vec2 vec;

    vec.x = attributes->x40;
    vec.y = attributes->x44;

    ftCommon_Fall(fp, vec.x, vec.y);
    ftCommon_8007CEF4(fp);
}

void ftZd_SpecialHiStart_0_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftZd_SpecialHi_80139B44(gobj);
    }
}

void ftZd_SpecialAirHiStart_0_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float facing_dir = fp->facing_dir;
    int ledge_grab_dir;

    if (facing_dir < 0) {
        ledge_grab_dir = -1;
    } else {
        ledge_grab_dir = +1;
    }

    if (ft_CheckGroundAndLedge(gobj, ledge_grab_dir)) {
        ftZd_SpecialHi_80139BB0(gobj);
    } else if (!ftCliffCommon_80081298(gobj)) {
        return;
    }
}

static u32 const transition_flags0 =
    Ft_MF_KeepGfx | Ft_MF_SkipHit | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
    Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

static u32 const transition_flags1 =
    transition_flags0 | Ft_MF_KeepColAnimHitStatus;

void ftZd_SpecialHi_80139B44(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);

    Fighter_ChangeMotionState(gobj, 352, transition_flags1, fp->cur_anim_frame,
                              1, 0, NULL);

    fp->accessory4_cb = &ftZd_SpecialHi_801396AC;
}

void ftZd_SpecialHi_80139BB0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 349, transition_flags1, fp->cur_anim_frame,
                              1, 0, NULL);

    fp->accessory4_cb = &ftZd_SpecialHi_801396AC;
}

void ftZd_SpecialHiStart_1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.zd.specialhi.x0 -= 1;

    if (fp->mv.zd.specialhi.x0 <= 0) {
        ftZd_SpecialHi_8013A6A8(gobj);
    }
}

void ftZd_SpecialAirHiStart_1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.zd.specialhi.x0 -= 1;

    if (fp->mv.zd.specialhi.x0 <= 0) {
        ftZd_SpecialHi_8013A764(gobj);
    }
}

void ftZd_SpecialHiStart_1_IASA(HSD_GObj* gobj) {}

void ftZd_SpecialAirHiStart_1_IASA(HSD_GObj* gobj) {}

void ftZd_SpecialHiStart_1_Phys(HSD_GObj* gobj)
{
    ftCommon_ApplyGroundMovement(gobj);
}

void ftZd_SpecialAirHiStart_1_Phys(HSD_GObj* gobj) {}

void ftZd_SpecialHiStart_1_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->coll_data;
    u32 env_flags;

    if (ft_80082708(gobj) == 0) {
        env_flags = collData->env_flags;
        if ((env_flags & Collide_LeftWallMask) != 0 ||
            (env_flags & Collide_RightWallMask) != 0)
        {
            ftCommon_8007D60C(fp);
            ftZd_SpecialHi_8013A764(gobj);
            return;
        }

        ftZd_SpecialHi_80139F6C(gobj);
    } else {
        env_flags = collData->env_flags;
        if ((env_flags & Collide_LeftWallMask) != 0 ||
            (env_flags & Collide_RightWallMask) != 0)
        {
            ftZd_SpecialHi_8013A6A8(gobj);
        }
    }
}

static bool ftZelda_80139D60_Helper(HSD_GObj* gobj)
{
    bool result;
    Fighter* fighter2;
    ftZelda_DatAttrs* attributes2;

    fighter2 = getFighter(gobj);
    attributes2 = fighter2->dat_attrs;

    if (fighter2->mv.zd.specialhi.xC >= attributes2->x4C) {
        result = true;
    } else if (ftCo_8009A134(gobj)) {
        result = false;
    } else {
        result = true;
    }

    return result;
}

void ftZd_SpecialAirHiStart_1_Coll(HSD_GObj* gobj)
{
    u8 _[12];

    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo @c sa can't move below @c coll_data,
    ///       which suggests a function boundary.
    ftZelda_DatAttrs* sa;
    CollData* coll_data = &fp->coll_data;
    sa = fp->dat_attrs;

    fp->mv.zd.specialhi.xC++;

    {
        int ledge_grab_dir;

        if (fp->facing_dir < 0) {
            ledge_grab_dir = -1;
        } else {
            ledge_grab_dir = +1;
        }

        if (ft_CheckGroundAndLedge(gobj, ledge_grab_dir)) {
            if (ftZelda_80139D60_Helper(gobj)) {
                ftZd_SpecialHi_80139FE8(gobj);
                return;
            }
        }
    }

    if (!ftCliffCommon_80081298(gobj)) {
        if ((coll_data->env_flags & Collide_CeilingMask) != 0) {
            float angle =
                lbVector_AngleXY(&coll_data->ceiling.normal, &fp->self_vel);
            if (angle > deg_to_rad * (90.0F + sa->x60)) {
                ftZd_SpecialHi_8013A764(gobj);
            }
        }

        if ((coll_data->env_flags & Collide_LeftWallMask) != 0) {
            float angle = lbVector_AngleXY(&coll_data->left_facing_wall.normal,
                                           &fp->self_vel);
            if (angle > (deg_to_rad * (90.0F + sa->x60))) {
                ftZd_SpecialHi_8013A764(gobj);
            }
        }
        if ((coll_data->env_flags & Collide_RightWallMask) != 0) {
            float angle = lbVector_AngleXY(
                &coll_data->right_facing_wall.normal, &fp->self_vel);
            if (angle > (deg_to_rad * (90.0F + sa->x60))) {
                ftZd_SpecialHi_8013A764(gobj);
            }
        }
    }
}

void ftZd_SpecialHi_80139F6C(HSD_GObj* gobj)
{
    u8 unused8;

    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);

    Fighter_ChangeMotionState(gobj, 353, transition_flags1, fp->cur_anim_frame,
                              0, 0, NULL);

    fp->x2223_b4 = true;
    fp->invisible = true;
}

void ftZd_SpecialHi_80139FE8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 350, transition_flags1, fp->cur_anim_frame,
                              0, 0, NULL);

    fp->invisible = true;
}

void ftZd_SpecialHi_8013A058(HSD_GObj* gobj)
{
    Vec3 inputVector;
    Vec3* groundVector;
    volatile float y;
    f64 _three;
    f64 _half;
    Fighter* fp;                  // r30
    ftZelda_DatAttrs* attributes; // r31
    float temp_f0;
    float temp_f1;
    float temp_f2;
    float var_f31;
    float var_f4;
    float temp_f5;
    float temp_f6;
    CollData* collData;

    u8 _[16];

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;
    collData = &fp->coll_data;
    temp_f2 = fp->input.lstick.x;
    temp_f1 = fp->input.lstick.y;
    temp_f2 = temp_f2 * temp_f2;
    temp_f1 = temp_f1 * temp_f1;
    temp_f5 = temp_f2 + temp_f1;
    var_f4 = temp_f5;

    // Essentially performing a square root operation
    // (Avoiding sqrtf to preserve stack alignment.)
    if (var_f4 > 0.0f) {
        f64 guess = __frsqrte(var_f4);
        _half = .5F;
        _three = 3.0F;
        guess = _half * guess * (_three - guess * guess * var_f4);
        guess = _half * guess * (_three - guess * guess * var_f4);
        guess = _half * guess * (_three - guess * guess * var_f4);
        y = (float) (var_f4 * guess);
        temp_f5 = y;
    }

    temp_f0 = 1.0;
    var_f31 = temp_f5;
    if (temp_f5 > temp_f0) {
        var_f31 = temp_f0;
    }

    if (!(var_f31 < attributes->x50)) {
        groundVector = &collData->floor.normal;
        inputVector.x = fp->input.lstick.x;
        inputVector.y = fp->input.lstick.y;
        inputVector.z = 0;

        if (!(lbVector_AngleXY(groundVector, (Vec3*) &inputVector.x) <
              (float) M_PI_2))
        {
            if (ftCo_8009A134(gobj) == 0) {
                ftCommon_UpdateFacing(fp);

                temp_f5 = atan2f(fp->input.lstick.y,
                                 fp->input.lstick.x * fp->facing_dir);

                fp->mv.zd.specialhi.x4.x = inputVector.x;
                fp->mv.zd.specialhi.x4.y = inputVector.y;

                // Update ground velocity
                temp_f6 = ((attributes->x54 * var_f31) + attributes->x58) *
                          cosf(temp_f5);
                fp->gr_vel = fp->facing_dir * temp_f6;

                Fighter_ChangeMotionState(gobj, 350, 0, 35.0, 1.0, 0, NULL);
                ftAnim_8006EBA4(gobj);
                ftAnim_SetAnimRate(gobj, 0);

                fp = GET_FIGHTER(gobj);
                attributes = fp->dat_attrs;
                fp->mv.zd.specialhi.x0 = attributes->x48;
                fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
                fp->x2223_b4 = 1;

                ftColl_8007B62C(gobj, 2);
                fp->invisible = true;
                return;
            }
        }
    }
    ftCommon_8007D60C(fp);
    ftZd_SpecialHi_8013A244(gobj);
}

void ftZd_SpecialHi_8013A244(HSD_GObj* gobj)
{
    volatile float y;
    Fighter* fp;                  // r30
    ftZelda_DatAttrs* attributes; // r31
    float temp_f1;
    float temp_f2;
    float var_f4;
    float var_f5;
    float var_f30;
    float var_f31;
    float temp_f0;

    u8 _[12];

    f64 _half;
    f64 _three;
    f64 guess;

    fp = GET_FIGHTER(gobj);
    temp_f2 = fp->input.lstick.x;
    temp_f1 = fp->input.lstick.y;
    attributes = fp->dat_attrs;
    temp_f1 = temp_f1 * temp_f1;
    temp_f2 = temp_f2 * temp_f2;
    var_f5 = temp_f2 + temp_f1;
    var_f4 = var_f5;

    // Essentially performing a square root operation
    // (Avoiding sqrtf to preserve stack alignment.)
    if (var_f4 > 0) {
        guess = __frsqrte(var_f4);
        _half = .5F;
        _three = 3.0F;
        guess = _half * guess * (_three - guess * guess * var_f4);
        guess = _half * guess * (_three - guess * guess * var_f4);
        guess = _half * guess * (_three - guess * guess * var_f4);
        y = (var_f4 * guess);
        var_f5 = y;
    }

    temp_f0 = 1.0;
    var_f31 = var_f5;
    if (var_f5 > temp_f0) {
        var_f31 = temp_f0;
    }

    if (var_f31 > attributes->x50) {
        temp_f1 = fp->input.lstick.x;
        if (temp_f1 < 0) {
            temp_f1 = -temp_f1;
        }
        if (temp_f1 > 0.001f) {
            ftCommon_UpdateFacing(fp);
        }
        var_f30 =
            atan2f(fp->input.lstick.y, fp->input.lstick.x * fp->facing_dir);
        fp->mv.zd.specialhi.x4.x = fp->input.lstick.x;
        fp->mv.zd.specialhi.x4.y = fp->input.lstick.y;
    } else {
        ftCommon_8007DA24(fp);
        var_f30 = (float) M_PI_2;
        fp->mv.zd.specialhi.x4.x = 0;
        var_f31 = fp->mv.zd.specialhi.x4.y = 1.0;
    }

    fp->self_vel.x =
        fp->facing_dir *
        (((attributes->x54 * var_f31) + attributes->x58) * cosf(var_f30));
    fp->self_vel.y =
        ((attributes->x54 * var_f31) + attributes->x58) * sinf(var_f30);

    Fighter_ChangeMotionState(gobj, 353, 0, 35.0, 1.0, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0);

    fp = GET_FIGHTER(gobj);
    attributes = fp->dat_attrs;
    fp->mv.zd.specialhi.x0 = attributes->x48;
    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    fp->x2223_b4 = 1;

    ftColl_8007B62C(gobj, 2);

    fp->invisible = true;
}

void ftZd_SpecialHi_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftZd_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* attributes = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        float x, y;
        x = attributes->x68;
        y = attributes->x6C;
        ftCo_80096900(gobj, 1, 0, 1, x, y);
    }
}

void ftZd_SpecialHi_IASA(HSD_GObj* gobj) {}

void ftZd_SpecialAirHi_IASA(HSD_GObj* gobj) {}

void ftZd_SpecialHi_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftZd_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* attributes = fp->dat_attrs;

    if (fp->cmd_vars[0] != 0) {
        ftCommon_FallBasic(fp);
        ftCommon_ClampSelfVelX(fp,
                               attributes->x5C * fp->co_attrs.air_drift_max);
        return;
    }

    {
        float vel_y = fp->self_vel.y;
        fp->self_vel.y = vel_y - vel_y / 10;
    }

    ftCommon_8007CEF4(fp);
}

void ftZd_SpecialHi_Coll(HSD_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftZd_SpecialHi_8013A648(gobj);
    }
}

void ftZd_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* attributes = fp->dat_attrs;

    {
        int ledge_grab_dir;

        if (fp->facing_dir < 0) {
            ledge_grab_dir = -1;
        } else {
            ledge_grab_dir = +1;
        }

        if (ft_CheckGroundAndLedge(gobj, ledge_grab_dir) != 0) {
            ftCo_LandingFallSpecial_Enter(gobj, false, attributes->x6C);
            return;
        }
    }

    if (!ftCliffCommon_80081298(gobj)) {
        return;
    }
}

void ftZd_SpecialHi_8013A648(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 354, transition_flags0, fp->cur_anim_frame,
                              1, 0, NULL);
}

void ftZd_SpecialHi_8013A6A8(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* attributes = fp0->dat_attrs;

    Fighter_ChangeMotionState(gobj, 351, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        fp1->mv.zd.specialhi.x10.x = fp1->self_vel.x;
        fp1->mv.zd.specialhi.x10.y = fp1->self_vel.y;
        fp1->mv.zd.specialhi.x18 = fp1->gr_vel;
        fp1->self_vel.y = 0;
        fp1->self_vel.x = 0;
        fp1->gr_vel = 0;
        fp1->invisible = false;
        fp1->accessory4_cb = &ftZd_SpecialHi_8013979C;
    }

    fp0->gr_vel = fp0->mv.zd.specialhi.x18 * attributes->x64;
}

void ftZd_SpecialHi_8013A764(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    ftZelda_DatAttrs* sa = fp0->dat_attrs;

    Fighter_ChangeMotionState(gobj, 354, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp1;
        fp1 = GET_FIGHTER(gobj);
        fp1->mv.zd.specialhi.x10.x = fp1->self_vel.x;
        fp1->mv.zd.specialhi.x10.y = fp1->self_vel.y;
        fp1->mv.zd.specialhi.x18 = fp1->gr_vel;
        fp1->self_vel.y = 0;
        fp1->self_vel.x = 0;
        fp1->gr_vel = 0;
        fp1->invisible = false;
        fp1->accessory4_cb = &ftZd_SpecialHi_8013979C;
    }

    fp0->self_vel.x = fp0->mv.zd.specialhi.x10.x * sa->x64;
    fp0->self_vel.y = fp0->mv.zd.specialhi.x10.y * sa->x64;
}
