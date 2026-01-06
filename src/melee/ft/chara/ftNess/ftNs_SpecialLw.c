#include "ftNs_SpecialLw.h"

#include "ftNs_Init.h"

#include <platform.h>

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftNess/types.h"
#include "pl/pl_040D.h"
#include "pl/player.h"
#include "pl/plbonuslib.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

// SpecialLw (PSI Magnet)
#define FTNESS_SPECIALLW_COLL_FLAG                                            \
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd | \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

#define FTNESS_SPECIALLW_END_FLAG                                             \
    Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |                 \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

// 0x80119E14
// https://decomp.me/scratch/LwTKg
void ftNs_SpecialLwStart_Enter(HSD_GObj* gobj) // Ness's grounded PSI Magnet
                                               // Start Motion State handler
{
    ftNessAttributes* ness_attr;
    Fighter* temp_fp;

    u8 _[20];

    temp_fp = GET_FIGHTER(gobj);
    ness_attr = temp_fp->dat_attrs;
    temp_fp->mv.ns.speciallw.releaseLag =
        (s32) ness_attr->x74_PSI_MAGNET_RELEASE_LAG;
    temp_fp->mv.ns.speciallw.isRelease = 0;
    temp_fp->mv.ns.speciallw.gravityDelay =
        (s32) ness_attr->x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    temp_fp->mv.ns.speciallw.x10 = 0;
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialLwStart, 0, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
}

// 0x80119E90
// https://decomp.me/scratch/ckNxx
void ftNs_SpecialAirLwStart_Enter(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Start Motion State handler
{
    Fighter* temp_fp;
    ftNessAttributes* ness_attr;

    u8 _[20];

    temp_fp = GET_FIGHTER(gobj);
    ness_attr = temp_fp->dat_attrs;
    temp_fp->mv.ns.speciallw.releaseLag =
        (s32) ness_attr->x74_PSI_MAGNET_RELEASE_LAG;
    temp_fp->mv.ns.speciallw.isRelease = 0;
    temp_fp->mv.ns.speciallw.gravityDelay =
        (s32) ness_attr->x84_PSI_MAGNET_FRAMES_BEFORE_GRAVITY;
    temp_fp->mv.ns.speciallw.x10 = 0;
    temp_fp->self_vel.y = 0.0f;
    temp_fp->self_vel.x /= ness_attr->x88_PSI_MAGNET_MOMENTUM_PRESERVATION;
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirLwStart, 0, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

// 0x80119F20
// https://decomp.me/scratch/frKYd
void ftNs_SpecialLwStart_Anim(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Start Animation callback
{
    Fighter* fp;
    Fighter* fighter_data2;

    fighter_data2 = GET_FIGHTER(gobj);

    if (!(fighter_data2->input.held_inputs & HSD_PAD_B)) {
        fighter_data2->mv.ns.speciallw.isRelease = 1;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp = GET_FIGHTER(gobj);

        if (!fp->x2219_b0) {
            efAsync_Spawn(gobj, &fp->x60C, 0U, 1264,
                          fp->parts[FtPart_L1stNb].joint);
            fp->x2219_b0 = true;
        }
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        fighter_data2->mv.ns.speciallw.x10 = 0;
        if ((s32) fighter_data2->ground_or_air == GA_Ground) {
            ftNs_SpecialLwHold_Enter(gobj);
            return;
        }
        ftNs_SpecialAirLwHold_Enter(gobj);
    }
}

// 0x8011A000
// https://decomp.me/scratch/psrOE
void ftNs_SpecialAirLwStart_Anim(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Start Animation callback
{
    Fighter* fighter_data2;
    Fighter* fp;

    u8 _[8];

    fighter_data2 = fp = GET_FIGHTER(gobj);

    if ((fighter_data2->input.held_inputs & HSD_PAD_B) == false) {
        fighter_data2->mv.ns.speciallw.isRelease = 1;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp = GET_FIGHTER(gobj);

        if (!fp->x2219_b0) {
            efAsync_Spawn(gobj, &fp->x60C, 0U, 1264,
                          fp->parts[FtPart_L1stNb].joint);
            fp->x2219_b0 = true;
        }
        fp->pre_hitlag_cb = efLib_PauseAll;
        fp->post_hitlag_cb = efLib_ResumeAll;
        fighter_data2->mv.ns.speciallw.x10 = 0;
        if ((s32) fighter_data2->ground_or_air == GA_Ground) {
            ftNs_SpecialLwHold_Enter(gobj);
            return;
        }
        ftNs_SpecialAirLwHold_Enter(gobj);
    }
}

// 0x8011A0E0
void ftNs_SpecialLwStart_IASA(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Start IASA callback
{
    return;
}

// 0x8011A0E4
void ftNs_SpecialAirLwStart_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Start IASA callback
{
    return;
}

/// Ness's grounded PSI Magnet Start Physics callback
void ftNs_SpecialLwStart_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Ness's aerial PSI Magnet Start Physics callback
void ftNs_SpecialAirLwStart_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* da = &fp->co_attrs;
    ftNessAttributes* ness_attr = fp->dat_attrs;
    int gravity_timer = fp->mv.ns.speciallw.gravityDelay;

    if (gravity_timer != 0) {
        fp->mv.ns.speciallw.gravityDelay = gravity_timer - 1;
    } else {
        ftCommon_Fall(fp, ness_attr->x8C_PSI_MAGNET_FALL_ACCEL,
                      da->terminal_vel);
    }

    ftCommon_8007CF58(fp);
}

// 0x8011A168
// https://decomp.me/scratch/S8g3b
void ftNs_SpecialLwStart_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Start Collision callback
{
    if (ft_80082708(gobj) == false) {
        ftNs_SpecialLwStart_GroundToAir(gobj);
    }
}

// 0x8011A1A4
// https://decomp.me/scratch/eNYIn
void ftNs_SpecialAirLwStart_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Start Collision callback
{
    if (ft_80081D0C(gobj) != false) {
        ftNs_SpecialAirLwStart_AirToGround(gobj);
    }
}

// 0x8011A1E0
// https://decomp.me/scratch/erSzB
void ftNs_SpecialLwStart_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet Start Motion State
                    // handler
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirLwStart,
                              FTNESS_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

// 0x8011A240
// https://decomp.me/scratch/153K2
void ftNs_SpecialAirLwStart_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet Start Motion State
                    // handler
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialLwStart,
                              FTNESS_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
}

// 0x8011A2A8
// https://decomp.me/scratch/Wlutx
void ftNs_SpecialLwHold_Anim(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold Animation callback
{
    Fighter* temp_r31;
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
        fp->mv.ns.speciallw.isRelease = 1;
    }

    if (fp->mv.ns.speciallw.releaseLag > 0) {
        fp->mv.ns.speciallw.releaseLag--;
    }
    if (((s32) fp->mv.ns.speciallw.releaseLag <= 0) &&
        ((s32) fp->mv.ns.speciallw.isRelease != 0))
    {
        if ((s32) fp->ground_or_air == GA_Ground) {
            ftNs_SpecialLwEnd_Enter(gobj);
        } else {
            ftNs_SpecialAirLwEnd_Enter(gobj);
        }
    }
    temp_r31 = GET_FIGHTER(gobj);

    temp_r31->mv.ns.speciallw.x10--;

    if ((s32) temp_r31->mv.ns.speciallw.x10 <= 0) {
        ft_80088478(temp_r31, 210081, 127, 64);
        temp_r31->mv.ns.speciallw.x10 = 40;
    }
}

// 0x8011A370
// https://decomp.me/scratch/UbQAr
void ftNs_SpecialAirLwHold_Anim(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Hold Animation callback
{
    Fighter* temp_r31;
    Fighter* fp;

    u8 _[8];

    fp = GET_FIGHTER(gobj);
    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
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
            ftNs_SpecialLwEnd_Enter(gobj);
        } else {
            ftNs_SpecialAirLwEnd_Enter(gobj);
        }
    }
    temp_r31 = GET_FIGHTER(gobj);

    temp_r31->mv.ns.speciallw.x10 = (s32) (temp_r31->mv.ns.speciallw.x10 - 1);

    if ((s32) temp_r31->mv.ns.speciallw.x10 <= 0) {
        ft_80088478(temp_r31, 210081, 127, 64);
        temp_r31->mv.ns.speciallw.x10 = 40;
    }
}

// 0x8011A438
void ftNs_SpecialLwHold_IASA(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold IASA callback
{
    return;
}

// 0x8011A43C
void ftNs_SpecialAirLwHold_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Hold IASA callback
{
    return;
}

// 0x8011A440
// https://decomp.me/scratch/knaIL
void ftNs_SpecialLwHold_Phys(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold Physics callback
{
    ft_80084F3C(gobj);
    ftColl_8007AF10(gobj);
}

/// Ness's aerial PSI Magnet Hold Physics callback
void ftNs_SpecialAirLwHold_Phys(HSD_GObj* gobj)
{
    u8 _[24];

    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* ness_attr = fp->dat_attrs;
    ftCo_DatAttrs* da = &fp->co_attrs;

    {
        int gravity_timer = fp->mv.ns.speciallw.gravityDelay;

        if (gravity_timer != 0) {
            fp->mv.ns.speciallw.gravityDelay = gravity_timer - 1;
        } else {
            ftCommon_Fall(fp, ness_attr->x8C_PSI_MAGNET_FALL_ACCEL,
                          da->terminal_vel);
        }

        ftCommon_8007CF58(fp);
        ftColl_8007AF10(gobj);
    }
}

// 0x8011A4E8
// https://decomp.me/scratch/SNaVN
void ftNs_SpecialLwHold_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold Collision callback
{
    if (ft_80082708(gobj) == false) {
        ftNs_SpecialLwHold_GroundToAir(gobj);
    }
}

// 0x8011A524
// https://decomp.me/scratch/dS3Sn
void ftNs_SpecialAirLwHold_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Hold Collision callback
{
    if (ft_80081D0C(gobj) != false) {
        ftNs_SpecialAirLwHold_AirToGround(gobj);
    }
}

// 0x8011A560
// https://decomp.me/scratch/noqpv
void ftNs_SpecialLwHold_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet Hold Motion State
                    // handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    u8 _[16];

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirLwHold,
                              FTNESS_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011A5D4
// https://decomp.me/scratch/PCAft
void ftNs_SpecialAirLwHold_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet Hold Motion State
                    // handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    u8 _[16];

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialLwHold,
                              FTNESS_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011A650
// https://decomp.me/scratch/YoMqy
void ftNs_SpecialLwHold_Enter(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Hold Motion State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    u8 _[8];

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialLwHold, Ft_MF_KeepGfx, 0.0f,
                              1.0f, 0.0f, NULL);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011A6A8
// https://decomp.me/scratch/TjjOK
void ftNs_SpecialAirLwHold_Enter(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Hold Motion State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    u8 _[8];

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirLwHold, Ft_MF_KeepGfx,
                              0.0f, 1.0f, 0.0f, NULL);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

static inline float returnStateVar(s32 stateVar)
{
    return (float) stateVar;
}

static inline void getAttrStuff(HSD_GObj* arg0)
{
    Fighter* temp_r30 = arg0->user_data;
    ftNessAttributes* temp_r31 = temp_r30->dat_attrs;
    temp_r30->mv.ns.speciallw.turnFrames += -1;

    if (((u32) temp_r30->cmd_vars[0] == 0U) &&
        ((returnStateVar(temp_r30->mv.ns.speciallw.turnFrames)) <=
         temp_r31->x78_PSI_MAGNET_UNK1))
    {
        temp_r30->cmd_vars[0] = 1;
        temp_r30->facing_dir = -temp_r30->facing_dir;
    }
    ftParts_80075AF0(
        temp_r30, 0,
        -((0.01745329238474369f * (180.0f / temp_r31->x78_PSI_MAGNET_UNK1)) -
          ftParts_80075F48(temp_r30, 0)));
}

/// Ness's grounded PSI Magnet Turnaround Animation callback - _
void ftNs_SpecialLwTurn_Anim(HSD_GObj* arg0)
{
    u8 _[4];

    Fighter* fp0 = arg0->user_data;

    {
        Fighter* fp1 = fp0;

        if (!(fp1->input.held_inputs & HSD_PAD_B)) {
            fp1->mv.ns.speciallw.isRelease = true;
        }

        if (fp1->mv.ns.speciallw.releaseLag > 0) {
            fp1->mv.ns.speciallw.releaseLag =
                fp1->mv.ns.speciallw.releaseLag - 1;
        }

        getAttrStuff(arg0);

        if ((signed) fp1->mv.ns.speciallw.turnFrames <= 0) {
            ftNs_SpecialLwHold_GroundOrAir(arg0);
        }
    }
}

/// Ness's aerial PSI Magnet Turnaround Animation callback - _
void ftNs_SpecialAirLwTurn_Anim(HSD_GObj* arg0)
{
    u8 _[8];

    Fighter* fp0 = arg0->user_data;

    {
        Fighter* fp1 = fp0;

        if (!(fp1->input.held_inputs & HSD_PAD_B)) {
            fp1->mv.ns.speciallw.isRelease = true;
        }

        if (fp1->mv.ns.speciallw.releaseLag > 0) {
            fp1->mv.ns.speciallw.releaseLag =
                fp1->mv.ns.speciallw.releaseLag - 1;
        }

        getAttrStuff(arg0);

        if ((signed) fp1->mv.ns.speciallw.turnFrames <= 0) {
            ftNs_SpecialLwHold_GroundOrAir(arg0);
        }
    }
}

// 0x8011A920
void ftNs_SpecialLwTurn_IASA(HSD_GObj* gobj) // Ness's grounded PSI Magnet
                                             // Turnaround IASA callback - _
{
    return;
}

// 0x8011A924
void ftNs_SpecialAirLwTurn_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Turnaround IASA callback
                    // - _
{
    return;
}

// 0x8011A928
void ftNs_SpecialLwTurn_Phys(HSD_GObj* gobj) // Ness's grounded PSI Magnet
                                             // Turnaround Physics callback - _
{
    ft_80084F3C(gobj);
    ftColl_8007AF10(gobj);
}

// 0x8011A95C
void ftNs_SpecialAirLwTurn_Phys(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Turnaround Physics
                    // callback - _
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[24];

    s32 magnetTimer;
    ftNessAttributes* ness_attr = fp->dat_attrs;
    ftCo_DatAttrs* da = &fp->co_attrs;

    magnetTimer = fp->mv.ns.speciallw.gravityDelay;

    if (magnetTimer != 0) {
        fp->mv.ns.speciallw.gravityDelay = magnetTimer - 1;
    } else {
        ftCommon_Fall(fp, ness_attr->x8C_PSI_MAGNET_FALL_ACCEL,
                      da->terminal_vel);
    }

    ftCommon_8007CF58(fp);
    ftColl_8007AF10(gobj);
}

// 0x8011A9D0
// https://decomp.me/scratch/E3jqW
void ftNs_SpecialLwTurn_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Turnaround Collision
                    // callback - _
{
    if (ft_80082708(gobj) == false) {
        ftNs_SpecialLwTurn_GroundToAir(gobj);
    }
}

// 0x8011AA0C
// https://decomp.me/scratch/qkeXm
void ftNs_SpecialAirLwTurn_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Turnaround Collision
                    // callback - _
{
    if (ft_80081D0C(gobj) != false) {
        ftNs_SpecialAirLwTurn_AirToGround(gobj);
    }
}

// 0x8011AA48
// https://decomp.me/scratch/Myul8
void ftNs_SpecialLwTurn_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet Turnaround Action
                    // State handler - _
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirLwTurn,
                              FTNESS_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

// 0x8011AAA8
// https://decomp.me/scratch/rfuLo
void ftNs_SpecialAirLwTurn_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet Turnaround Action
                    // State handler - _
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialLwTurn,
                              FTNESS_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
}

// 0x8011AB10
// https://decomp.me/scratch/HzpAw
bool ftNs_SpecialLwHold_GroundOrAir(
    HSD_GObj* arg0) // Decide grounded or aerial PSI Magnet Hold
{
    u8 _[24];

    Fighter* fp = GET_FIGHTER(arg0);

    if (fp->mv.ns.speciallw.releaseLag <= 0 && fp->mv.ns.speciallw.isRelease) {
        if (fp->ground_or_air == GA_Ground) {
            ftNs_SpecialLwEnd_Enter(arg0);
        } else {
            ftNs_SpecialAirLwEnd_Enter(arg0);
        }

        return false;
    }
    if ((s32) fp->ground_or_air == GA_Ground) {
        Fighter_ChangeMotionState(arg0, ftNs_MS_SpecialLwHold, Ft_MF_KeepGfx,
                                  0.0f, 1.0f, 0.0f, NULL);

        {
            Fighter* fp = GET_FIGHTER(arg0);
            ftNessAttributes* sa = fp->dat_attrs;
            ftColl_CreateAbsorbHit(arg0, &sa->x98_PSI_MAGNET_ABSORPTION);
        }
    } else {
        Fighter_ChangeMotionState(arg0, ftNs_MS_SpecialAirLwHold,
                                  Ft_MF_KeepGfx, 0.0f, 1.0f, 0.0f, NULL);

        {
            Fighter* fp = GET_FIGHTER(arg0);
            ftNessAttributes* sa = fp->dat_attrs;
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
        ft_80088478(fp, 210081, 127, 64);
        fp->mv.ns.speciallw.x10 = 40;
    }
}

// 0x8011ABF8
// https://decomp.me/scratch/jbsQw
void ftNs_SpecialLwHit_Anim(
    HSD_GObj* arg0) // Ness's grounded PSI Magnet Absorb Animation callback
{
    Fighter* temp_r30;
    Fighter* temp_r3_2;
    Fighter* temp_r4;

    u8 _[44];

    s32 phi_r0;

    Fighter* temp_e1;
    Fighter* temp_e2;
    ftNessAttributes* da;

    temp_r4 = arg0->user_data;
    if (!(temp_r4->input.held_inputs & HSD_PAD_B)) {
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
                ftNs_SpecialLwEnd_Enter(arg0);
            } else {
                ftNs_SpecialAirLwEnd_Enter(arg0);
            }
            phi_r0 = 0;
        } else {
            if ((s32) temp_r3_2->ground_or_air == GA_Ground) {
                Fighter_ChangeMotionState(arg0, ftNs_MS_SpecialLwHold,
                                          Ft_MF_KeepGfx, 0.0f, 1.0f, 0.0f,
                                          NULL);

                temp_e1 = arg0->user_data;
                da = temp_e1->dat_attrs;
                ftColl_CreateAbsorbHit(arg0, &da->x98_PSI_MAGNET_ABSORPTION);
            } else {
                Fighter_ChangeMotionState(arg0, ftNs_MS_SpecialAirLwHold,
                                          Ft_MF_KeepGfx, 0.0f, 1.0f, 0.0f,
                                          NULL);
                temp_e2 = arg0->user_data;
                da = temp_e2->dat_attrs;
                ftColl_CreateAbsorbHit(arg0, &da->x98_PSI_MAGNET_ABSORPTION);
            }
            phi_r0 = 1;
        }
        if (phi_r0 != 0) {
            ftCommon_8007DB24(arg0);
            temp_r30 = arg0->user_data;
            if (!temp_r30->x2219_b0) {
                efAsync_Spawn(arg0, &temp_r30->x60C, 0U, 1264,
                              temp_r30->parts[FtPart_L1stNb].joint);
                temp_r30->x2219_b0 = true;
            }
            temp_r30->pre_hitlag_cb = efLib_PauseAll;
            temp_r30->post_hitlag_cb = efLib_ResumeAll;
        }
    }

    MagnetStateVarCalc(arg0);
}

// 0x8011ADC8
// https://decomp.me/scratch/VSNzs
void ftNs_SpecialAirLwHit_Anim(
    HSD_GObj* arg0) // Ness's aerial PSI Magnet Absorb Animation callback
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(arg0);

    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        fp->mv.ns.speciallw.isRelease = true;
    }

    if (fp->mv.ns.speciallw.releaseLag > 0) {
        fp->mv.ns.speciallw.releaseLag = fp->mv.ns.speciallw.releaseLag - 1;
    }

    if (!ftAnim_IsFramesRemaining(arg0) &&
        ftNs_SpecialLwHold_GroundOrAir(arg0))
    {
        ftCommon_8007DB24(arg0);
        {
            Fighter* fp = GET_FIGHTER(arg0);
            if (!fp->x2219_b0) {
                efAsync_Spawn(arg0, &fp->x60C, 0U, 1264,
                              fp->parts[FtPart_L1stNb].joint);
                fp->x2219_b0 = true;
            }
            fp->pre_hitlag_cb = efLib_PauseAll;
            fp->post_hitlag_cb = efLib_ResumeAll;
        }
    }

    {
        Fighter* fp = GET_FIGHTER(arg0);
        fp->mv.ns.speciallw.x10 = fp->mv.ns.speciallw.x10 - 1;
        if ((signed) fp->mv.ns.speciallw.x10 <= 0) {
            ft_80088478(fp, 210081, 127, 64);
            fp->mv.ns.speciallw.x10 = 40;
        }
    }
}

// 0x8011AEE0
void ftNs_SpecialLwHit_IASA(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Absorb IASA callback
{
}

// 0x8011AEE4
void ftNs_SpecialAirLwHit_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Absorb IASA callback
{
}

// 0x8011AEE8
// https://decomp.me/scratch/wKRWI
void ftNs_SpecialLwHit_Phys(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Absorb Physics callback
{
    ft_80084F3C(gobj);
    ftColl_8007AF10(gobj);
}

// 0x8011AF1C
// https://decomp.me/scratch/SfvyO
void ftNs_SpecialAirLwHit_Phys(
    HSD_GObj* arg0) // Ness's aerial PSI Magnet Absorb Physics callback
{
    u8 _[24];

    s32 temp_r3;

    Fighter* fp = GET_FIGHTER(arg0);
    ftNessAttributes* attrs = fp->dat_attrs;
    ftCo_DatAttrs* attributes = &fp->co_attrs;

    temp_r3 = fp->mv.ns.speciallw.gravityDelay;
    if (temp_r3 != 0) {
        fp->mv.ns.speciallw.gravityDelay = temp_r3 - 1;
    } else {
        ftCommon_Fall(fp, attrs->x8C_PSI_MAGNET_FALL_ACCEL,
                      attributes->terminal_vel);
    }

    ftCommon_8007CF58(fp);
    ftColl_8007AF10(arg0);
}

// 0x8011AF90
// https://decomp.me/scratch/XSIRp
void ftNs_SpecialLwHit_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet Absorb Collision callback
{
    if (ft_80082708(gobj) == false) {
        ftNs_SpecialLwHit_GroundToAir(gobj);
    }
}

// 0x8011AFCC
// https://decomp.me/scratch/Lq3zN
void ftNs_SpecialAirLwHit_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet Absorb Collision callback
{
    if (ft_80081D0C(gobj) != false) {
        ftNs_SpecialAirLwHit_AirToGround(gobj);
    }
}

// 0x8011B008
// https://decomp.me/scratch/LkmRj
void ftNs_SpecialLwHit_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet Absorb Action
                    // State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    u8 _[16];

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirLwHit,
                              FTNESS_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011B07C
// https://decomp.me/scratch/uVIed
void ftNs_SpecialAirLwHit_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet Absorb Action
                    // State handler
{
    Fighter* fp;
    ftNessAttributes* ness_attr;

    u8 _[16];

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialLwHit,
                              FTNESS_SPECIALLW_COLL_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(fp);
    fp = GET_FIGHTER(gobj);
    ness_attr = fp->dat_attrs;
    ftColl_CreateAbsorbHit(gobj, &ness_attr->x98_PSI_MAGNET_ABSORPTION);
}

// 0x8011B0F8
// https://decomp.me/scratch/H0osU
void ftNs_AbsorbThink_DecideAction(
    HSD_GObj* gobj) // Ness's PSI Magnet OnAbsorb hook
{
    u8 _[8];

    enum_t msid;
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->dat_attrs;

    {
        float heal_amount = (int) (fp->AbsorbAttr.x1A44_damageTaken *
                                   ftNs_Init_GetAbsorbHeal(fp));

        fp->dmg.x1830_percent -= heal_amount;

        {
            float cur_percent = fp->dmg.x1830_percent;

            if (fp->dmg.x1830_percent < 0) {
                heal_amount = cur_percent + heal_amount;
                fp->dmg.x1830_percent = 0;
            }
        }

        Player_SetHPByIndex(fp->player_id, fp->x221F_b4,
                            fp->dmg.x1830_percent);
        pl_80040B8C(fp->player_id, fp->x221F_b4, heal_amount);
    }

    fp->facing_dir = (float) fp->AbsorbAttr.x1A40_absorbHitDirection;
    msid = fp->motion_id;

    if ((msid != ftNs_MS_SpecialLwHit && msid != ftNs_MS_SpecialAirLwHit) ||
        !(fp->cur_anim_frame <= sa->x7C_PSI_MAGNET_UNK2))
    {
        enum_t msid;
        if (fp->ground_or_air == GA_Ground) {
            msid = ftNs_MS_SpecialLwHit;
        } else {
            msid = ftNs_MS_SpecialAirLwHit;
        }

        Fighter_ChangeMotionState(gobj, msid, 2, 0, 1, 0, NULL);
        ftColl_CreateAbsorbHit(gobj, &sa->x98_PSI_MAGNET_ABSORPTION);
    }
}

// 0x8011B25C
// https://decomp.me/scratch/H32Eg
void ftNs_SpecialLwEnd_Anim(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End Animation callback
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007DB24(gobj);
        ftCommon_8007D92C(gobj);
    }
}

// 0x8011B2A0
// https://decomp.me/scratch/uLilE
void ftNs_SpecialAirLwEnd_Anim(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet End Animation callback
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007DB24(gobj);
        ftCommon_8007D92C(gobj);
    }
}

// 0x8011B2E4
void ftNs_SpecialLwEnd_IASA(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End IASA callback
{
    return;
}

// 0x8011B2E8
void ftNs_SpecialAirLwEnd_IASA(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet End IASA callback
{
    return;
}

// 0x8011B2EC
// https://decomp.me/scratch/ccQxd
void ftNs_SpecialLwEnd_Phys(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End Physics callback
{
    ft_80084F3C(gobj);
}

// 0x8011B30C
// https://decomp.me/scratch/EkqUN
void ftNs_SpecialAirLwEnd_Phys(
    HSD_GObj* arg0) // Ness's aerial PSI Magnet End Physics callback
{
    u8 _[24];

    Fighter* fp = GET_FIGHTER(arg0);
    ftNessAttributes* attrs = fp->dat_attrs;
    ftCo_DatAttrs* attributes = &fp->co_attrs;
    int gravity_timer = fp->mv.ns.speciallw.gravityDelay;

    if (gravity_timer != 0) {
        fp->mv.ns.speciallw.gravityDelay = gravity_timer - 1;
    } else {
        ftCommon_Fall(fp, attrs->x8C_PSI_MAGNET_FALL_ACCEL,
                      attributes->terminal_vel);
    }

    ftCommon_8007CF58(fp);
}

// 0x8011B36C
// https://decomp.me/scratch/5ROxm
void ftNs_SpecialLwEnd_Coll(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End Collision callback
{
    if (!ft_80082708(gobj)) {
        ftNs_SpecialLwEnd_GroundToAir(gobj);
    }
}

// 0x8011B3A8
// https://decomp.me/scratch/phduU
void ftNs_SpecialAirLwEnd_Coll(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet End Collision callback
{
    if (ft_80081D0C(gobj) != false) {
        ftNs_SpecialAirLwEnd_AirToGround(gobj);
    }
}

// 0x8011B3E4
// https://decomp.me/scratch/9ihkO
void ftNs_SpecialLwEnd_GroundToAir(
    HSD_GObj* gobj) // Ness's ground->air PSI Magnet End Motion State
                    // handler
{
    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirLwEnd,
                              FTNESS_SPECIALLW_END_FLAG, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

// 0x8011B444
// https://decomp.me/scratch/uJw37
void ftNs_SpecialAirLwEnd_AirToGround(
    HSD_GObj* gobj) // Ness's air->ground PSI Magnet End Motion State
                    // handler
{
    Fighter* temp_r31;

    temp_r31 = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(temp_r31);
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialLwEnd,
                              FTNESS_SPECIALLW_END_FLAG,
                              temp_r31->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftCommon_ClampAirDrift(temp_r31);
}

// 0x8011B4AC
// https://decomp.me/scratch/6wpwg
void ftNs_SpecialLwEnd_Enter(
    HSD_GObj* gobj) // Ness's grounded PSI Magnet End Motion State handler
{
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialLwEnd, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
}

// 0x8011B4E4
// https://decomp.me/scratch/sbrLt
void ftNs_SpecialAirLwEnd_Enter(
    HSD_GObj* gobj) // Ness's aerial PSI Magnet End Motion State handler
{
    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirLwEnd, 0, 0.0f, 1.0f,
                              0.0f, NULL);
}
