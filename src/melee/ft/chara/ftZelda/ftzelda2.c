#include "ftzelda2.h"

#include "ftzelda.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/fighter.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "lb/lbunknown_001.h"
#include "lb/lbunknown_003.h"
#include "lb/lbvector.h"

#include <math.h>
#include <trigf.h>
#include <dolphin/mtx/types.h>

void ftZelda_801396AC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZelda_801396E0(gobj);
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

void ftZelda_801396E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_flag.bits.b0) {
        Vec3 vec;
        func_8000B1CC(fp->x5E8_fighterBones[4].x0_jobj, NULL, &vec);

        if (fp->ground_or_air == GA_Ground)
            ef_Spawn(0x4F6, gobj, fp->x5E8_fighterBones->x0_jobj);
        else
            ef_Spawn(0x4F7, gobj, fp->x5E8_fighterBones->x0_jobj);

        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftZelda_8013979C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    {
        Vec3 vec;
        func_8000B1CC(fp->x5E8_fighterBones[4].x0_jobj, NULL, &vec);

        if (!fp->x2219_flag.bits.b0) {
            ef_Spawn(0x505, gobj, &vec);
            fp->x2219_flag.bits.b0 = true;
        }
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

void ftZelda_SpecialHi_StartAction_Helper(Fighter* fp)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
    _[0] = 0;
#endif

    {
        ssize_t boneIndex = func_8007500C(fp, 4);
        HSD_JObj* jObj = fp->x5E8_fighterBones[boneIndex].x0_jobj;

        {
            Vec3 vec;
            func_8000B1CC(jObj, NULL, &vec);

            func_800119DC(&vec, 0x78, 1.5f, 0.02, 60 * (f32) M_PI / 180);
        }
    }
}

void ftZelda_SpecialHi_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = getFighterPlus(gobj);

    fp->xEC_ground_vel = 0;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = 0;

    Fighter_ActionStateChange_800693AC(gobj, 349, 0, NULL, 0, 1, 0);
    func_8006EBA4(gobj);

    fp = getFighterPlus(gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->mv.zd.specialhi.xC = 0;

    ftZelda_SpecialHi_StartAction_Helper(fp);

    fp->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

void ftZelda_SpecialAirHi_StartAction(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftZeldaAttributes* attributes = fp->x2D4_specialAttributes;

        fp->x80_self_vel.x = fp->x80_self_vel.x / attributes->x38;
        fp->x80_self_vel.y = fp->x80_self_vel.y / attributes->x3C;

        Fighter_ActionStateChange_800693AC(gobj, 352, 0, NULL, 0, 1, 0);
        func_8006EBA4(gobj);
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.zd.specialhi.xC = 0;

        {
            Vec3 vec;

            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[20];
#endif

            ssize_t boneIndex = func_8007500C(fp, 4);
            HSD_JObj* jObj = fp->x5E8_fighterBones[boneIndex].x0_jobj;

            func_8000B1CC(jObj, NULL, &vec);
            func_800119DC(&vec, 120, 1.5, 0.02, 60 * (f32) M_PI / 180);
        }

        fp->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
    }
}

void ftZelda_801399B4(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftZelda_8013A058(gobj);
    }
}

void ftZelda_801399F0(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        ftZelda_8013A244(gobj);
}

void ftZelda_80139A2C(HSD_GObj* gobj) {}

void ftZelda_80139A30(HSD_GObj* gobj) {}

void ftZelda_80139A34(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftZelda_80139A54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZeldaAttributes* attributes = fp->x2D4_specialAttributes;
    Vec2 vec;

    vec.x = attributes->x40;
    vec.y = attributes->x44;

    func_8007D494(fp, vec.x, vec.y);
    func_8007CEF4(fp);
}

void ftZelda_80139A98(HSD_GObj* gobj)
{
    if (!func_80082708(gobj))
        ftZelda_80139B44(gobj);
}

void ftZelda_80139AD4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 facing_dir = fp->facing_dir;
    int ledge_grab_dir;

    if (facing_dir < 0)
        ledge_grab_dir = -1;
    else
        ledge_grab_dir = +1;

    if (EnvColl_CheckGroundAndLedge(gobj, ledge_grab_dir))
        ftZelda_80139BB0(gobj);
    else if (!func_80081298(gobj))
        return;
}

static Fighter_ActionStateChangeFlags const transition_flags0 =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

static Fighter_ActionStateChangeFlags const transition_flags1 =
    transition_flags0 | FtStateChange_PreserveColAnimHitStatus;

void ftZelda_80139B44(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D60C(fp);

    Fighter_ActionStateChange_800693AC(gobj, 352, transition_flags1, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);

    fp->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

void ftZelda_80139BB0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, 349, transition_flags1, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);

    fp->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

void ftZelda_80139C1C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.zd.specialhi.x0 -= 1;

    if (fp->mv.zd.specialhi.x0 <= 0)
        ftZelda_8013A6A8(gobj);
}

void ftZelda_80139C58(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.zd.specialhi.x0 -= 1;

    if (fp->mv.zd.specialhi.x0 <= 0)
        ftZelda_8013A764(gobj);
}

void ftZelda_80139C94(HSD_GObj* gobj) {}

void ftZelda_80139C98(HSD_GObj* gobj) {}

void ftZelda_80139C9C(HSD_GObj* gobj)
{
    func_8007CB74(gobj);
}

void ftZelda_80139CBC(HSD_GObj* gobj) {}

void ftZelda_80139CC0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->x6F0_collData;
    u32 env_flags;

    if (func_80082708(gobj) == 0) {
        env_flags = collData->x134_envFlags;
        if ((env_flags & MPCOLL_RIGHTWALL) != 0 ||
            (env_flags & MPCOLL_LEFTWALL) != 0)
        {
            func_8007D60C(fp);
            ftZelda_8013A764(gobj);
            return;
        }

        ftZelda_80139F6C(gobj);
    } else {
        env_flags = collData->x134_envFlags;
        if ((env_flags & MPCOLL_RIGHTWALL) != 0 ||
            (env_flags & MPCOLL_LEFTWALL) != 0)
            ftZelda_8013A6A8(gobj);
    }
}

bool ftZelda_80139D60_Helper(HSD_GObj* gobj)
{
    bool result;
    Fighter* fighter2;
    ftZeldaAttributes* attributes2;

    fighter2 = getFighter(gobj);
    attributes2 = fighter2->x2D4_specialAttributes;

    if (fighter2->mv.zd.specialhi.xC >= attributes2->x4C)
        result = true;
    else if (func_8009A134(gobj))
        result = false;
    else
        result = true;

    return result;
}

void ftZelda_80139D60(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo @c sa can't move below @c coll_data,
    ///       which suggests a function boundary.
    ftZeldaAttributes* sa;
    CollData* coll_data = &fp->x6F0_collData;
    sa = fp->x2D4_specialAttributes;

    fp->mv.zd.specialhi.xC++;

    {
        int ledge_grab_dir;

        if (fp->facing_dir < 0)
            ledge_grab_dir = -1;
        else
            ledge_grab_dir = +1;

        if (EnvColl_CheckGroundAndLedge(gobj, ledge_grab_dir)) {
            if (ftZelda_80139D60_Helper(gobj)) {
                ftZelda_80139FE8(gobj);
                return;
            }
        }
    }

    if (!func_80081298(gobj)) {
        if ((coll_data->x134_envFlags & MPCOLL_CEIL) != 0) {
            f32 angle = lbvector_AngleXY(&coll_data->x188_ceiling.normal,
                                         &fp->x80_self_vel);
            if (angle > DEG_TO_RAD * (90.0F + sa->x60))
                ftZelda_8013A764(gobj);
        }

        if ((coll_data->x134_envFlags & MPCOLL_RIGHTWALL) != 0) {
            f32 angle = lbvector_AngleXY(&coll_data->x160_rightwall.normal,
                                         &fp->x80_self_vel);
            if (angle > (DEG_TO_RAD * (90.0F + sa->x60)))
                ftZelda_8013A764(gobj);
        }
        if ((coll_data->x134_envFlags & MPCOLL_LEFTWALL) != 0) {
            f32 angle = lbvector_AngleXY(&coll_data->x174_leftwall.normal,
                                         &fp->x80_self_vel);
            if (angle > (DEG_TO_RAD * (90.0F + sa->x60)))
                ftZelda_8013A764(gobj);
        }
    }
}

void ftZelda_80139F6C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused8;
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D60C(fp);

    Fighter_ActionStateChange_800693AC(gobj, 353, transition_flags1, NULL,
                                       fp->x894_currentAnimFrame, 0, 0);

    fp->x2223_flag.bits.b4 = true;
    fp->x221E_flag.bits.b0 = true;
}

void ftZelda_80139FE8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, 350, transition_flags1, NULL,
                                       fp->x894_currentAnimFrame, 0, 0);

    fp->x221E_flag.bits.b0 = true;
}

void ftZelda_8013A058(HSD_GObj* gobj)
{
    Vec3 inputVector;
    Vec3* groundVector;
    volatile float y;
    f64 _three;
    f64 _half;
    Fighter* fp;                   // r30
    ftZeldaAttributes* attributes; // r31
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f31;
    f32 var_f4;
    f32 temp_f5;
    f32 temp_f6;
    CollData* collData;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);
    attributes = fp->x2D4_specialAttributes;
    collData = &fp->x6F0_collData;
    temp_f2 = fp->input.x620_lstick_x;
    temp_f1 = fp->input.x624_lstick_y;
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
        groundVector = &collData->x14C_ground.normal;
        inputVector.x = fp->input.x620_lstick_x;
        inputVector.y = fp->input.x624_lstick_y;
        inputVector.z = 0;

        if (!(lbvector_AngleXY(groundVector, (Vec3*) &inputVector.x) <
              (f32) M_PI_2))
        {
            if (func_8009A134(gobj) == 0) {
                func_8007D9FC(fp);

                temp_f5 = atan2f(fp->input.x624_lstick_y,
                                 fp->input.x620_lstick_x * fp->facing_dir);

                fp->mv.zd.specialhi.x4.x = inputVector.x;
                fp->mv.zd.specialhi.x4.y = inputVector.y;

                // Update ground velocity
                temp_f6 = ((attributes->x54 * var_f31) + attributes->x58) *
                          cosf(temp_f5);
                fp->xEC_ground_vel = fp->facing_dir * temp_f6;

                Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0, NULL, 35.0,
                                                   1.0, 0);
                func_8006EBA4(gobj);
                ftAnim_SetAnimRate(gobj, 0);

                fp = GET_FIGHTER(gobj);
                attributes = fp->x2D4_specialAttributes;
                fp->mv.zd.specialhi.x0 = attributes->x48;
                fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
                fp->x2223_flag.bits.b4 = 1;

                func_8007B62C(gobj, 2);
                fp->x221E_flag.bits.b0 = 1;
                return;
            }
        }
    }
    func_8007D60C(fp);
    ftZelda_8013A244(gobj);
}

void ftZelda_8013A244(HSD_GObj* gobj)
{
    volatile float y;
    Fighter* fp;                   // r30
    ftZeldaAttributes* attributes; // r31
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f4;
    f32 var_f5;
    f32 var_f30;
    f32 var_f31;
    f32 temp_f0;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    f64 _half;
    f64 _three;
    f64 guess;

    fp = GET_FIGHTER(gobj);
    temp_f2 = fp->input.x620_lstick_x;
    temp_f1 = fp->input.x624_lstick_y;
    attributes = fp->x2D4_specialAttributes;
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
        temp_f1 = fp->input.x620_lstick_x;
        if (temp_f1 < 0) {
            temp_f1 = -temp_f1;
        }
        if (temp_f1 > 0.001f) {
            func_8007D9FC(fp);
        }
        var_f30 = atan2f(fp->input.x624_lstick_y,
                         fp->input.x620_lstick_x * fp->facing_dir);
        fp->mv.zd.specialhi.x4.x = fp->input.x620_lstick_x;
        fp->mv.zd.specialhi.x4.y = fp->input.x624_lstick_y;
    } else {
        func_8007DA24(fp);
        var_f30 = (f32) M_PI_2;
        fp->mv.zd.specialhi.x4.x = 0;
        var_f31 = fp->mv.zd.specialhi.x4.y = 1.0;
    }

    fp->x80_self_vel.x =
        fp->facing_dir *
        (((attributes->x54 * var_f31) + attributes->x58) * cosf(var_f30));
    fp->x80_self_vel.y =
        ((attributes->x54 * var_f31) + attributes->x58) * sinf(var_f30);

    Fighter_ActionStateChange_800693AC(gobj, 0x161, 0, NULL, 35.0, 1.0, 0);
    func_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0);

    fp = GET_FIGHTER(gobj);
    attributes = fp->x2D4_specialAttributes;
    fp->mv.zd.specialhi.x0 = attributes->x48;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    fp->x2223_flag.bits.b4 = 1;

    func_8007B62C(gobj, 2);

    fp->x221E_flag.bits.b0 = 1;
}

void ftZelda_8013A448(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void ftZelda_8013A484(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftZeldaAttributes* attributes = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        f32 x, y;
        x = attributes->x68;
        y = attributes->x6C;
        func_80096900(gobj, 1, 0, 1, x, y);
    }
}

void ftZelda_8013A4E4(HSD_GObj* gobj) {}

void ftZelda_8013A4E8(HSD_GObj* gobj) {}

void ftZelda_8013A4EC(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftZelda_8013A50C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftZeldaAttributes* attributes = fp->x2D4_specialAttributes;

    if (fp->x2200_ftcmd_var0 != 0) {
        func_8007D4B8(fp);
        func_8007D440(fp, attributes->x5C * fp->x110_attr.x17C_AerialDriftMax);
        return;
    }

    {
        f32 vel_y = fp->x80_self_vel.y;
        fp->x80_self_vel.y = vel_y - vel_y / 10;
    }

    func_8007CEF4(fp);
}

void ftZelda_8013A588(HSD_GObj* gobj)
{
    if (func_800827A0(gobj) == 0)
        ftZelda_8013A648(gobj);
}

void ftZelda_8013A5C4(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftZeldaAttributes* attributes = fp->x2D4_specialAttributes;

    {
        int ledge_grab_dir;

        if (fp->facing_dir < 0)
            ledge_grab_dir = -1;
        else
            ledge_grab_dir = +1;

        if (EnvColl_CheckGroundAndLedge(gobj, ledge_grab_dir) != 0) {
            func_800D5CB0(gobj, 0, attributes->x6C);
            return;
        }
    }

    if (!func_80081298(gobj))
        return;
}

void ftZelda_8013A648(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(gobj, 354, transition_flags0, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}

void ftZelda_8013A6A8(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    ftZeldaAttributes* attributes = fp0->x2D4_specialAttributes;

    Fighter_ActionStateChange_800693AC(gobj, 351, 0, NULL, 0, 1, 0);
    func_8006EBA4(gobj);

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        fp1->mv.zd.specialhi.x10.x = fp1->x80_self_vel.x;
        fp1->mv.zd.specialhi.x10.y = fp1->x80_self_vel.y;
        fp1->mv.zd.specialhi.x18 = fp1->xEC_ground_vel;
        fp1->x80_self_vel.y = 0;
        fp1->x80_self_vel.x = 0;
        fp1->xEC_ground_vel = 0;
        fp1->x221E_flag.bits.b0 = false;
        fp1->cb.x21BC_callback_Accessory4 = &ftZelda_8013979C;
    }

    fp0->xEC_ground_vel = fp0->mv.zd.specialhi.x18 * attributes->x64;
}

void ftZelda_8013A764(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);
    ftZeldaAttributes* sa = fp0->x2D4_specialAttributes;

    Fighter_ActionStateChange_800693AC(gobj, 354, 0, NULL, 0, 1, 0);
    func_8006EBA4(gobj);

    {
        Fighter* fp1;
        fp1 = GET_FIGHTER(gobj);
        fp1->mv.zd.specialhi.x10.x = fp1->x80_self_vel.x;
        fp1->mv.zd.specialhi.x10.y = fp1->x80_self_vel.y;
        fp1->mv.zd.specialhi.x18 = fp1->xEC_ground_vel;
        fp1->x80_self_vel.y = 0;
        fp1->x80_self_vel.x = 0;
        fp1->xEC_ground_vel = 0;
        fp1->x221E_flag.bits.b0 = false;
        fp1->cb.x21BC_callback_Accessory4 = &ftZelda_8013979C;
    }

    fp0->x80_self_vel.x = fp0->mv.zd.specialhi.x10.x * sa->x64;
    fp0->x80_self_vel.y = fp0->mv.zd.specialhi.x10.y * sa->x64;
}
