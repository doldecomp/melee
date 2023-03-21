#include "ftNess_SpecialLw.h"

#include "ftNess.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "pl/pl_unknown_001.h"

// 0x80119E14
// https://decomp.me/scratch/LwTKg
void ftNess_SpecialLwStart_Action(HSD_GObj* gobj) // Ness's grounded PSI Magnet
                                                  // Start Motion State handler
{
    ftNessAttributes* ness_attr;
    Fighter* temp_fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    temp_fp = GET_FIGHTER(gobj);
    ness_attr = temp_fp->x2D4_specialAttributes;
    temp_fp->mv.ns.speciallw.releaseLag =
        (s32) ness_attr->x74_PSI_MAGNET_RELEASE_LAG;
    temp_fp->mv.ns.speciallw.isRelease = 0;
    temp_fp->mv.ns.speciallw.gravityDelay =
        (s32) ness_attr->x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    temp_fp->mv.ns.speciallw.x10 = 0;
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALLW_START, 0, NULL, 0, 1, 0);
    func_8006EBA4(gobj);
}

// 0x80119E90
// https://decomp.me/scratch/ckNxx
void ftNess_SpecialAirLwStart_Action(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Start Motion State handler
{
    Fighter* temp_fp;
    ftNessAttributes* ness_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    temp_fp = GET_FIGHTER(gobj);
    ness_attr = temp_fp->x2D4_specialAttributes;
    temp_fp->mv.ns.speciallw.releaseLag =
        (s32) ness_attr->x74_PSI_MAGNET_RELEASE_LAG;
    temp_fp->mv.ns.speciallw.isRelease = 0;
    temp_fp->mv.ns.speciallw.gravityDelay =
        (s32) ness_attr->x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    temp_fp->mv.ns.speciallw.x10 = 0;
    temp_fp->x80_self_vel.y = 0.0f;
    temp_fp->x80_self_vel.x /= ness_attr->x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRLW_START, 0, NULL, 0.0f,
                              1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 0x80119F20
// https://decomp.me/scratch/frKYd
void ftNess_SpecialLwStart_Anim(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Start Animation callback
{
    Fighter* fp;
    Fighter* fighter_data2;

    fighter_data2 = GET_FIGHTER(gobj);

    if (!(fighter_data2->input.x65C_heldInputs & HSD_BUTTON_B)) {
        fighter_data2->mv.ns.speciallw.isRelease = 1;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp = GET_FIGHTER(gobj);

        if (fp->x2219_flag.bits.b0 == 0) {
            efAsync_Spawn(gobj, &fp->x60C, 0U, 0x4F0U,
                          fp->x5E8_fighterBones[23].x0_jobj);
            fp->x2219_flag.bits.b0 = 1;
        }
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        fighter_data2->mv.ns.speciallw.x10 = 0;
        if ((s32) fighter_data2->ground_or_air == GA_Ground) {
            ftNess_SpecialLwHold_Action(gobj);
            return;
        }
        ftNess_SpecialAirLwHold_Action(gobj);
    }
}

// 0x8011A000
// https://decomp.me/scratch/psrOE
void ftNess_SpecialAirLwStart_Anim(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Start Animation callback
{
    Fighter* fighter_data2;
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fighter_data2 = fp = GET_FIGHTER(gobj);

    if ((fighter_data2->input.x65C_heldInputs & HSD_BUTTON_B) == false) {
        fighter_data2->mv.ns.speciallw.isRelease = 1;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp = GET_FIGHTER(gobj);

        if (fp->x2219_flag.bits.b0 == 0) {
            efAsync_Spawn(gobj, &fp->x60C, 0U, 0x4F0U,
                          fp->x5E8_fighterBones[23].x0_jobj);
            fp->x2219_flag.bits.b0 = 1;
        }
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        fighter_data2->mv.ns.speciallw.x10 = 0;
        if ((s32) fighter_data2->ground_or_air == GA_Ground) {
            ftNess_SpecialLwHold_Action(gobj);
            return;
        }
        ftNess_SpecialAirLwHold_Action(gobj);
    }
}

// 0x8011A0E0
void ftNess_SpecialLwStart_IASA(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Start IASA callback
{
    return;
}

// 0x8011A0E4
void ftNess_SpecialAirLwStart_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Start IASA callback
{
    return;
}

/// Ness's grounded PSI Magnet Start Physics callback
void ftNess_SpecialLwStart_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

/// Ness's aerial PSI Magnet Start Physics callback
void ftNess_SpecialAirLwStart_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    attr* attr = &fp->x110_attr;
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    int gravity_timer = fp->mv.ns.speciallw.gravityDelay;

    if (gravity_timer != 0) {
        fp->mv.ns.speciallw.gravityDelay = gravity_timer - 1;
    } else {
        func_8007D494(fp, ness_attr->x8C_PSI_MAGNET_FALL_ACCEL,
                      attr->x170_TerminalVelocity);
    }

    func_8007CF58(fp);
}

// 0x8011A168
// https://decomp.me/scratch/S8g3b
void ftNess_SpecialLwStart_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Start Collision callback
{
    if (func_80082708(gobj) == false) {
        ftNess_SpecialLwStart_GroundToAir(gobj);
    }
}

// 0x8011A1A4
// https://decomp.me/scratch/eNYIn
void ftNess_SpecialAirLwStart_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Start Collision callback
{
    if (func_80081D0C(gobj) != false) {
        ftNess_SpecialAirLwStart_AirToGround(gobj);
    }
}

// 0x8011A1E0
// https://decomp.me/scratch/erSzB
void ftNess_SpecialLwStart_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet Start Motion State
                    // handler
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRLW_START,
                              FTNESS_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x8011A240
// https://decomp.me/scratch/153K2
void ftNess_SpecialAirLwStart_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet Start Motion State
                    // handler
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALLW_START,
                              FTNESS_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
}

// 0x8011A2A8
// https://decomp.me/scratch/Wlutx
void ftNess_SpecialLwHold_Anim(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold Animation callback
{
    Fighter* temp_r31;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false) {
        fp->mv.ns.speciallw.isRelease = 1;
    }

    if (fp->mv.ns.speciallw.releaseLag > 0) {
        fp->mv.ns.speciallw.releaseLag--;
    }
    if (((s32) fp->mv.ns.speciallw.releaseLag <= 0) &&
        ((s32) fp->mv.ns.speciallw.isRelease != 0))
    {
        if ((s32) fp->ground_or_air == GA_Ground) {
            ftNess_SpecialLwEnd_Action(gobj);
        } else {
            ftNess_SpecialAirLwEnd_Action(gobj);
        }
    }
    temp_r31 = GET_FIGHTER(gobj);

    temp_r31->mv.ns.speciallw.x10--;

    if ((s32) temp_r31->mv.ns.speciallw.x10 <= 0) {
        func_80088478(temp_r31, 0x334A1, 0x7F, 0x40);
        temp_r31->mv.ns.speciallw.x10 = 0x28;
    }
}

// 0x8011A370
// https://decomp.me/scratch/UbQAr
void ftNess_SpecialAirLwHold_Anim(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Hold Animation callback
{
    Fighter* temp_r31;
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = GET_FIGHTER(gobj);
    if ((fp->input.x65C_heldInputs & HSD_BUTTON_B) == false) {
        fp->mv.ns.speciallw.isRelease = 1;
    }

    if (fp->mv.ns.speciallw.releaseLag > 0) {
        fp->mv.ns.speciallw.releaseLag =
            (s32) (fp->mv.ns.speciallw.releaseLag - 1);
    }
    if (((s32) fp->mv.ns.speciallw.releaseLag <= 0) &&
        ((s32) fp->mv.ns.speciallw.isRelease != 0))
    {
        if ((s32) fp->ground_or_air == GA_Ground) {
            ftNess_SpecialLwEnd_Action(gobj);
        } else {
            ftNess_SpecialAirLwEnd_Action(gobj);
        }
    }
    temp_r31 = GET_FIGHTER(gobj);

    temp_r31->mv.ns.speciallw.x10 = (s32) (temp_r31->mv.ns.speciallw.x10 - 1);

    if ((s32) temp_r31->mv.ns.speciallw.x10 <= 0) {
        func_80088478(temp_r31, 0x334A1, 0x7F, 0x40);
        temp_r31->mv.ns.speciallw.x10 = 0x28;
    }
}

// 0x8011A438
void ftNess_SpecialLwHold_IASA(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold IASA callback
{
    return;
}

// 0x8011A43C
void ftNess_SpecialAirLwHold_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Hold IASA callback
{
    return;
}

// 0x8011A440
// https://decomp.me/scratch/knaIL
void ftNess_SpecialLwHold_Phys(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold Physics callback
{
    func_80084F3C(gobj);
    func_8007AF10(gobj);
}

/// Ness's aerial PSI Magnet Hold Physics callback
void ftNess_SpecialAirLwHold_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    attr* attr = &fp->x110_attr;

    {
        int gravity_timer = fp->mv.ns.speciallw.gravityDelay;

        if (gravity_timer != 0) {
            fp->mv.ns.speciallw.gravityDelay = gravity_timer - 1;
        } else {
            func_8007D494(fp, ness_attr->x8C_PSI_MAGNET_FALL_ACCEL,
                          attr->x170_TerminalVelocity);
        }

        func_8007CF58(fp);
        func_8007AF10(gobj);
    }
}

// 0x8011A4E8
// https://decomp.me/scratch/SNaVN
void ftNess_SpecialLwHold_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold Collision callback
{
    if (func_80082708(gobj) == false) {
        ftNess_SpecialLwHold_GroundToAir(gobj);
    }
}

// 0x8011A524
// https://decomp.me/scratch/dS3Sn
void ftNess_SpecialAirLwHold_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Hold Collision callback
{
    if (func_80081D0C(gobj) != false) {
        ftNess_SpecialAirLwHold_AirToGround(gobj);
    }
}

// 0x8011A560
// https://decomp.me/scratch/noqpv
void ftNess_SpecialLwHold_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet Hold Motion State
                    // handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRLW_HOLD,
                              FTNESS_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011A5D4
// https://decomp.me/scratch/PCAft
void ftNess_SpecialAirLwHold_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet Hold Motion State
                    // handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALLW_HOLD,
                              FTNESS_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011A650
// https://decomp.me/scratch/YoMqy
void ftNess_SpecialLwHold_Action(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold Motion State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALLW_HOLD,
                              FtStateChange_PreserveGfx, NULL, 0.0f, 1.0f,
                              0.0f);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011A6A8
// https://decomp.me/scratch/TjjOK
void ftNess_SpecialAirLwHold_Action(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Hold Motion State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRLW_HOLD,
                              FtStateChange_PreserveGfx, NULL, 0.0f, 1.0f,
                              0.0f);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

static inline f32 returnStateVar(s32 stateVar)
{
    return (f32) stateVar;
}

static inline void getAttrStuff(HSD_GObj* arg0)
{
    Fighter* temp_r30 = arg0->user_data;
    ftNessAttributes* temp_r31 = temp_r30->x2D4_specialAttributes;
    temp_r30->mv.ns.speciallw.turnFrames += -1;

    if (((u32) temp_r30->x2200_ftcmd_var0 == 0U) &&
        ((returnStateVar(temp_r30->mv.ns.speciallw.turnFrames)) <=
         temp_r31->x78_PSI_MAGNET_UNK1))
    {
        temp_r30->x2200_ftcmd_var0 = 1;
        temp_r30->facing_dir = -temp_r30->facing_dir;
    }
    func_80075AF0(
        temp_r30, 0,
        -((0.01745329238474369f * (180.0f / temp_r31->x78_PSI_MAGNET_UNK1)) -
          func_80075F48(temp_r30, 0)));
}

/// Ness's grounded PSI Magnet Turnaround Animation callback - _
void ftNess_SpecialLwTurn_Anim(HSD_GObj* arg0)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp0 = arg0->user_data;

    {
        Fighter* fp1 = fp0;

        if (!(fp1->input.x65C_heldInputs & HSD_BUTTON_B))
            fp1->mv.ns.speciallw.isRelease = true;

        if (fp1->mv.ns.speciallw.releaseLag > 0) {
            fp1->mv.ns.speciallw.releaseLag =
                fp1->mv.ns.speciallw.releaseLag - 1;
        }

        getAttrStuff(arg0);

        if ((signed) fp1->mv.ns.speciallw.turnFrames <= 0) {
            ftNess_SpecialLwHold_GroundOrAir(arg0);
        }
    }
}

/// Ness's aerial PSI Magnet Turnaround Animation callback - _
void ftNess_SpecialAirLwTurn_Anim(HSD_GObj* arg0)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp0 = arg0->user_data;

    {
        Fighter* fp1 = fp0;

        if (!(fp1->input.x65C_heldInputs & HSD_BUTTON_B))
            fp1->mv.ns.speciallw.isRelease = true;

        if (fp1->mv.ns.speciallw.releaseLag > 0) {
            fp1->mv.ns.speciallw.releaseLag =
                fp1->mv.ns.speciallw.releaseLag - 1;
        }

        getAttrStuff(arg0);

        if ((signed) fp1->mv.ns.speciallw.turnFrames <= 0)
            ftNess_SpecialLwHold_GroundOrAir(arg0);
    }
}

// 0x8011A920
void ftNess_SpecialLwTurn_IASA(HSD_GObj* gobj) // Ness's grounded PSI Magnet
                                               // Turnaround IASA callback - _
{
    return;
}

// 0x8011A924
void ftNess_SpecialAirLwTurn_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Turnaround IASA callback
                    // - _
{
    return;
}

// 0x8011A928
void ftNess_SpecialLwTurn_Phys(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Turnaround Physics
                    // callback - _
{
    func_80084F3C(gobj);
    func_8007AF10(gobj);
}

// 0x8011A95C
void ftNess_SpecialAirLwTurn_Phys(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Turnaround Physics
                    // callback - _
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    s32 magnetTimer;
    ftNessAttributes* ness_attr = fp->x2D4_specialAttributes;
    attr* attr = &fp->x110_attr;

    magnetTimer = fp->mv.ns.speciallw.gravityDelay;

    if (magnetTimer != 0) {
        fp->mv.ns.speciallw.gravityDelay = magnetTimer - 1;
    } else {
        func_8007D494(fp, ness_attr->x8C_PSI_MAGNET_FALL_ACCEL,
                      attr->x170_TerminalVelocity);
    }

    func_8007CF58(fp);
    func_8007AF10(gobj);
}

// 0x8011A9D0
// https://decomp.me/scratch/E3jqW
void ftNess_SpecialLwTurn_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Turnaround Collision
                    // callback - _
{
    if (func_80082708(gobj) == false) {
        ftNess_SpecialLwTurn_GroundToAir(gobj);
    }
}

// 0x8011AA0C
// https://decomp.me/scratch/qkeXm
void ftNess_SpecialAirLwTurn_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Turnaround Collision
                    // callback - _
{
    if (func_80081D0C(gobj) != false) {
        ftNess_SpecialAirLwTurn_AirToGround(gobj);
    }
}

// 0x8011AA48
// https://decomp.me/scratch/Myul8
void ftNess_SpecialLwTurn_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet Turnaround Action
                    // State handler - _
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRLW_TURN,
                              FTNESS_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x8011AAA8
// https://decomp.me/scratch/rfuLo
void ftNess_SpecialAirLwTurn_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet Turnaround Action
                    // State handler - _
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALLW_TURN,
                              FTNESS_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
}

// 0x8011AB10
// https://decomp.me/scratch/HzpAw
bool ftNess_SpecialLwHold_GroundOrAir(
    HSD_GObj* arg0) // Decide grounded or aerial PSI Magnet Hold
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    Fighter* fp = GET_FIGHTER(arg0);

    if (fp->mv.ns.speciallw.releaseLag <= 0 && fp->mv.ns.speciallw.isRelease) {
        if (fp->ground_or_air == GA_Ground) {
            ftNess_SpecialLwEnd_Action(arg0);
        } else {
            ftNess_SpecialAirLwEnd_Action(arg0);
        }

        return false;
    }
    if ((s32) fp->ground_or_air == GA_Ground) {
        Fighter_ChangeMotionState(arg0, MS_NESS_SPECIALLW_HOLD,
                                  FtStateChange_PreserveGfx, NULL, 0.0f, 1.0f,
                                  0.0f);

        {
            Fighter* fp = GET_FIGHTER(arg0);
            ftNessAttributes* sa = fp->x2D4_specialAttributes;
            ftColl_CreateAbsorbHit(arg0, &sa->x98_PSI_MAGNET_ABSORPTION);
        }
    } else {
        Fighter_ChangeMotionState(arg0, MS_NESS_SPECIALAIRLW_HOLD,
                                  FtStateChange_PreserveGfx, NULL, 0.0f, 1.0f,
                                  0.0f);

        {
            Fighter* fp = GET_FIGHTER(arg0);
            ftNessAttributes* sa = fp->x2D4_specialAttributes;
            ftColl_CreateAbsorbHit(arg0, &sa->x98_PSI_MAGNET_ABSORPTION);
        }
    }

    return true;
}

inline void MagnetStateVarCalc(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ns.speciallw.x10 = fp->mv.ns.speciallw.x10 - 1;
    if ((s32) fp->mv.ns.speciallw.x10 <= 0) {
        func_80088478(fp, 0x334A1, 0x7F, 0x40);
        fp->mv.ns.speciallw.x10 = 0x28;
    }
}

// 0x8011ABF8
// https://decomp.me/scratch/jbsQw
void ftNess_SpecialLwHit_Anim(
    HSD_GObj* arg0) // Ness's grounded PSI Magnet Absorb Animation callback
{
    Fighter* temp_r30;
    Fighter* temp_r3_2;
    Fighter* temp_r4;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[44];
#endif

    s32 phi_r0;

    Fighter* temp_e1;
    Fighter* temp_e2;
    ftNessAttributes* attr;

    temp_r4 = arg0->user_data;
    if (!(temp_r4->input.x65C_heldInputs & HSD_BUTTON_B)) {
        temp_r4->mv.ns.speciallw.isRelease = 1;
    }

    if (temp_r4->mv.ns.speciallw.releaseLag > 0) {
        temp_r4->mv.ns.speciallw.releaseLag =
            (s32) (temp_r4->mv.ns.speciallw.releaseLag - 1);
    }
    if (!ftAnim_IsFramesRemaining(arg0)) {
        temp_r3_2 = arg0->user_data;
        if (((s32) temp_r3_2->mv.ns.speciallw.releaseLag <= 0) &&
            ((s32) temp_r3_2->mv.ns.speciallw.isRelease != 0))
        {
            if ((s32) temp_r3_2->ground_or_air == GA_Ground) {
                ftNess_SpecialLwEnd_Action(arg0);
            } else {
                ftNess_SpecialAirLwEnd_Action(arg0);
            }
            phi_r0 = 0;
        } else {
            if ((s32) temp_r3_2->ground_or_air == GA_Ground) {
                Fighter_ChangeMotionState(arg0, MS_NESS_SPECIALLW_HOLD,
                                          FtStateChange_PreserveGfx, NULL,
                                          0.0f, 1.0f, 0.0f);

                temp_e1 = arg0->user_data;
                attr = temp_e1->x2D4_specialAttributes;
                ftColl_CreateAbsorbHit(arg0, &attr->x98_PSI_MAGNET_ABSORPTION);
            } else {
                Fighter_ChangeMotionState(arg0, MS_NESS_SPECIALAIRLW_HOLD,
                                          FtStateChange_PreserveGfx, NULL,
                                          0.0f, 1.0f, 0.0f);
                temp_e2 = arg0->user_data;
                attr = temp_e2->x2D4_specialAttributes;
                ftColl_CreateAbsorbHit(arg0, &attr->x98_PSI_MAGNET_ABSORPTION);
            }
            phi_r0 = 1;
        }
        if (phi_r0 != 0) {
            func_8007DB24(arg0);
            temp_r30 = arg0->user_data;
            if (temp_r30->x2219_flag.bits.b0 == 0) {
                efAsync_Spawn(arg0, &temp_r30->x60C, 0U, 0x4F0U,
                              temp_r30->x5E8_fighterBones[23].x0_jobj);
                temp_r30->x2219_flag.bits.b0 = 1;
            }
            temp_r30->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
            temp_r30->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        }
    }

    MagnetStateVarCalc(arg0);
}

// 0x8011ADC8
// https://decomp.me/scratch/VSNzs
void ftNess_SpecialAirLwHit_Anim(
    HSD_GObj* arg0) // Ness's aerial PSI Magnet Absorb Animation callback
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(arg0);

    if (!(fp->input.x65C_heldInputs & HSD_BUTTON_B))
        fp->mv.ns.speciallw.isRelease = true;

    if (fp->mv.ns.speciallw.releaseLag > 0) {
        fp->mv.ns.speciallw.releaseLag = fp->mv.ns.speciallw.releaseLag - 1;
    }

    if (!ftAnim_IsFramesRemaining(arg0) &&
        ftNess_SpecialLwHold_GroundOrAir(arg0))
    {
        func_8007DB24(arg0);
        {
            Fighter* fp = GET_FIGHTER(arg0);
            if (!fp->x2219_flag.bits.b0) {
                efAsync_Spawn(arg0, &fp->x60C, 0U, 0x4F0U,
                              fp->x5E8_fighterBones[23].x0_jobj);
                fp->x2219_flag.bits.b0 = true;
            }
            fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
            fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        }
    }

    {
        Fighter* fp = GET_FIGHTER(arg0);
        fp->mv.ns.speciallw.x10 = fp->mv.ns.speciallw.x10 - 1;
        if ((signed) fp->mv.ns.speciallw.x10 <= 0) {
            func_80088478(fp, 0x334A1, 0x7F, 0x40);
            fp->mv.ns.speciallw.x10 = 0x28;
        }
    }
}

// 0x8011AEE0
void ftNess_SpecialLwHit_IASA(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Absorb IASA callback
{
}

// 0x8011AEE4
void ftNess_SpecialAirLwHit_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Absorb IASA callback
{
}

// 0x8011AEE8
// https://decomp.me/scratch/wKRWI
void ftNess_SpecialLwHit_Phys(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Absorb Physics callback
{
    func_80084F3C(gobj);
    func_8007AF10(gobj);
}

// 0x8011AF1C
// https://decomp.me/scratch/SfvyO
void ftNess_SpecialAirLwHit_Phys(
    HSD_GObj* arg0) // Ness's aerial PSI Magnet Absorb Physics callback
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    s32 temp_r3;

    Fighter* fp = GET_FIGHTER(arg0);
    ftNessAttributes* attrs = fp->x2D4_specialAttributes;
    attr* attributes = &fp->x110_attr;

    temp_r3 = fp->mv.ns.speciallw.gravityDelay;
    if (temp_r3 != 0) {
        fp->mv.ns.speciallw.gravityDelay = temp_r3 - 1;
    } else {
        func_8007D494(fp, attrs->x8C_PSI_MAGNET_FALL_ACCEL,
                      attributes->x170_TerminalVelocity);
    }

    func_8007CF58(fp);
    func_8007AF10(arg0);
}

// 0x8011AF90
// https://decomp.me/scratch/XSIRp
void ftNess_SpecialLwHit_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Absorb Collision callback
{
    if (func_80082708(gobj) == false) {
        ftNess_SpecialLwHit_GroundToAir(gobj);
    }
}

// 0x8011AFCC
// https://decomp.me/scratch/Lq3zN
void ftNess_SpecialAirLwHit_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Absorb Collision callback
{
    if (func_80081D0C(gobj) != false) {
        ftNess_SpecialAirLwHit_AirToGround(gobj);
    }
}

// 0x8011B008
// https://decomp.me/scratch/LkmRj
void ftNess_SpecialLwHit_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet Absorb Action
                    // State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRLW_HIT,
                              FTNESS_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011B07C
// https://decomp.me/scratch/uVIed
void ftNess_SpecialAirLwHit_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet Absorb Action
                    // State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp = GET_FIGHTER(gobj);
    func_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALLW_HIT,
                              FTNESS_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(fp);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->x2D4_specialAttributes;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011B0F8
// https://decomp.me/scratch/H0osU
void ftNess_AbsorbThink_DecideAction(
    HSD_GObj* gobj) // Ness's PSI Magnet OnAbsorb hook
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    enum_t msid;
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->x2D4_specialAttributes;

    {
        f32 heal_amount = (int) (fp->AbsorbAttr.x1A44_damageTaken *
                                 ftNess_GetAbsorbHeal(fp));

        fp->dmg.x1830_percent -= heal_amount;

        {
            f32 cur_percent = fp->dmg.x1830_percent;

            if (fp->dmg.x1830_percent < 0) {
                heal_amount = cur_percent + heal_amount;
                fp->dmg.x1830_percent = 0;
            }
        }

        Player_SetHPByIndex(fp->xC_playerID, fp->x221F_flag.bits.b4,
                            fp->dmg.x1830_percent);
        func_80040B8C(fp->xC_playerID, fp->x221F_flag.bits.b4, heal_amount);
    }

    fp->facing_dir = (f32) fp->AbsorbAttr.x1A40_absorbHitDirection;
    msid = fp->motion_id;

    if ((msid != MS_NESS_SPECIALLW_HIT && msid != MS_NESS_SPECIALAIRLW_HIT) ||
        !(fp->x894_currentAnimFrame <= sa->x7C_PSI_MAGNET_UNK2))
    {
        enum_t msid;
        if (fp->ground_or_air == GA_Ground)
            msid = MS_NESS_SPECIALLW_HIT;
        else
            msid = MS_NESS_SPECIALAIRLW_HIT;

        Fighter_ChangeMotionState(gobj, msid, 2, NULL, 0, 1, 0);
        ftColl_CreateAbsorbHit(gobj, &sa->x98_PSI_MAGNET_ABSORPTION);
    }
}

// 0x8011B25C
// https://decomp.me/scratch/H32Eg
void ftNess_SpecialLwEnd_Anim(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End Animation callback
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8007DB24(gobj);
        func_8007D92C(gobj);
    }
}

// 0x8011B2A0
// https://decomp.me/scratch/uLilE
void ftNess_SpecialAirLwEnd_Anim(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet End Animation callback
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8007DB24(gobj);
        func_8007D92C(gobj);
    }
}

// 0x8011B2E4
void ftNess_SpecialLwEnd_IASA(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End IASA callback
{
    return;
}

// 0x8011B2E8
void ftNess_SpecialAirLwEnd_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet End IASA callback
{
    return;
}

// 0x8011B2EC
// https://decomp.me/scratch/ccQxd
void ftNess_SpecialLwEnd_Phys(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End Physics callback
{
    func_80084F3C(gobj);
}

// 0x8011B30C
// https://decomp.me/scratch/EkqUN
void ftNess_SpecialAirLwEnd_Phys(
    HSD_GObj* arg0) // Ness's aerial PSI Magnet End Physics callback
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    Fighter* fp = GET_FIGHTER(arg0);
    ftNessAttributes* attrs = fp->x2D4_specialAttributes;
    attr* attributes = &fp->x110_attr;
    int gravity_timer = fp->mv.ns.speciallw.gravityDelay;

    if (gravity_timer != 0) {
        fp->mv.ns.speciallw.gravityDelay = gravity_timer - 1;
    } else {
        func_8007D494(fp, attrs->x8C_PSI_MAGNET_FALL_ACCEL,
                      attributes->x170_TerminalVelocity);
    }

    func_8007CF58(fp);
}

// 0x8011B36C
// https://decomp.me/scratch/5ROxm
void ftNess_SpecialLwEnd_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End Collision callback
{
    if (!func_80082708(gobj))
        ftNess_SpecialLwEnd_GroundToAir(gobj);
}

// 0x8011B3A8
// https://decomp.me/scratch/phduU
void ftNess_SpecialAirLwEnd_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet End Collision callback
{
    if (func_80081D0C(gobj) != false) {
        ftNess_SpecialAirLwEnd_AirToGround(gobj);
    }
}

// 0x8011B3E4
// https://decomp.me/scratch/9ihkO
void ftNess_SpecialLwEnd_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet End Motion State
                    // handler
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRLW_END,
                              FTNESS_SPECIALLW_END_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
}

// 0x8011B444
// https://decomp.me/scratch/uJw37
void ftNess_SpecialAirLwEnd_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet End Motion State
                    // handler
{
    Fighter* temp_r31;

    temp_r31 = GET_FIGHTER(gobj);
    func_8007D7FC(temp_r31);
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALLW_END,
                              FTNESS_SPECIALLW_END_FLAG, NULL,
                              temp_r31->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007D468(temp_r31);
}

// 0x8011B4AC
// https://decomp.me/scratch/6wpwg
void ftNess_SpecialLwEnd_Action(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End Motion State handler
{
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALLW_END, 0, NULL, 0.0f, 1.0f,
                              0.0f);
}

// 0x8011B4E4
// https://decomp.me/scratch/sbrLt
void ftNess_SpecialAirLwEnd_Action(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet End Motion State handler
{
    Fighter_ChangeMotionState(gobj, MS_NESS_SPECIALAIRLW_END, 0, NULL, 0.0f,
                              1.0f, 0.0f);
}
