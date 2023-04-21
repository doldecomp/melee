#include "ftMr_SpecialLw.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftparts.h"
#include "ftMario/ftmario.h"

#include <baselib/random.h>

// 0x800E2050
// https://decomp.me/scratch/8zo4V
void updateRot(HSD_GObj* gobj)
{
    Fighter* fp;
    fp = GET_FIGHTER(gobj);

    ftParts_8007592C(fp, 0, 0.0f);
}

void ftMario_SpecialLw_SetGFX(HSD_GObj* gobj)
{
    void* hsd_obj_ptr;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    hsd_obj_ptr = gobj->hsd_obj;

    efSync_Spawn(0x47C, gobj, hsd_obj_ptr);
    fp->x2219_flag.bits.b0 = 1;
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

void ftMario_SpecialLw_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = &updateRot;
    fp->cb.x21E4_callback_OnDeath2 = &updateRot;
}

void _ftMario_800E207C_800E2194_helper(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMarioAttributes* sa;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = GET_FIGHTER(gobj);
    sa = (ftMarioAttributes*) fp->x2D4_specialAttributes;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->sv.mr.SpecialLw.groundVelX = (f32) 0.0f;
    fp->sv.mr.SpecialLw.unk = (s32) (sa->x50_MARIO_TORNADO_UNK + 1);
    fp->sv.mr.SpecialLw.isUnkColl = 0;
    ftMario_SpecialLw_SetCall(gobj);
    ftMario_SpecialLw_SetGFX(gobj);
}

void ftMario_SpecialLw_SetVar(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x2208_ftcmd_var2 = 0;
}

void ftMr_SpecialLw_Enter(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMarioAttributes* sa = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    ftMario_SpecialLw_SetVar(gobj);
    Fighter_ChangeMotionState(gobj, AS_MARIO_SPECIALAIRLW, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
    fp->x80_self_vel.y = (f32) (sa->x38_MARIO_TORNADO_GROUND_VEL_Y -
                                sa->x54_MARIO_TORNADO_TAP_Y_VEL_MAX);
    ftCommon_8007D440(fp, sa->x40_MARIO_TORNADO_MOMENTUM_X_AIR);
    _ftMario_800E207C_800E2194_helper(gobj);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

void ftMr_SpecialAirLw_Enter(HSD_GObj* gobj)
{
    f32 sub_val;
    Fighter* fp = gobj->user_data;
    ftMarioAttributes* sa = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    ftMario_SpecialLw_SetVar(gobj);
    Fighter_ChangeMotionState(gobj, AS_MARIO_SPECIALAIRLW, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);
    if ((s32) fp->ev.mr.x2234_tornadoCharge != 0) {
        sub_val = 0.0f;
    } else {
        sub_val = sa->x54_MARIO_TORNADO_TAP_Y_VEL_MAX;
    }
    fp->x80_self_vel.y = (f32) (sa->x38_MARIO_TORNADO_GROUND_VEL_Y - sub_val);
    ftCommon_8007D440(fp, sa->x40_MARIO_TORNADO_MOMENTUM_X_AIR);
    _ftMario_800E207C_800E2194_helper(gobj);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

void ftMario_SpecialLw_SetNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cb.x21DC_callback_OnTakeDamage = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
}

// 0x800E22BC
// https://decomp.me/scratch/FT3Fl
void ftMr_SpecialLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMario_SpecialLw_SetNULL(gobj);
        ft_8008A2BC(gobj);
    }
}

// 0x800E2308
// https://decomp.me/scratch/QF5fb
void ftMr_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMarioAttributes* sa = (ftMarioAttributes*) fp->x2D4_specialAttributes;

    if ((u32) fp->x2204_ftcmd_var1 != 0U) {
        fp->x2204_ftcmd_var1 = 0U;
        fp->ev.mr.x2234_tornadoCharge = 1;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMario_SpecialLw_SetNULL(gobj);
        if (0.0 == (f64) sa->x5C_MARIO_TORNADO_LANDING_LAG) {
            ft_800CC730(gobj);
            return;
        }
        ft_80096900(gobj, 1, 0, true, 1.0f,
                    (f32) sa->x5C_MARIO_TORNADO_LANDING_LAG);
    }
}

// 0x800E23DC
void ftMr_SpecialLw_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E23E0
void ftMr_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    return;
}

void _ftMario_800E23E4_800E25C4_helper_0(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMarioAttributes* sa = GetMarioAttr(fp);
    fp->x2208_ftcmd_var2 = 0;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, AS_MARIO_SPECIALAIRLW,
                              FTMARIO_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftCommon_ClampFallSpeed(fp, sa->x58_MARIO_TORNADO_TAP_GRAVITY);
    ftCommon_8007D440(fp, sa->x40_MARIO_TORNADO_MOMENTUM_X_AIR);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

// 0x800E23E4
// https://decomp.me/scratch/aJPK4
void ftMr_SpecialLw_Phys(HSD_GObj* gobj)
{
    f32 flt_var;
    ftMarioAttributes* sa;
    Fighter* fp;
    Fighter* ft_tmp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = GET_FIGHTER(gobj);
    sa = GetMarioAttr(fp);

    flt_var = sa->x3C_MARIO_TORNADO_MOMENTUM_X_GROUND;
    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        fp->sv.mr.SpecialLw.groundVelX =
            (f32) (fp->sv.mr.SpecialLw.groundVelX -
                   sa->x4C_MARIO_TORNADO_FRICTION_END);
        flt_var += fp->sv.mr.SpecialLw.groundVelX;
        if (flt_var < 0.0f) {
            flt_var = 0.0f;
        }
    }

    ft_tmp = fp;
    ftCommon_8007CADC(ft_tmp, 0.0f,
                      sa->x44_MARIO_TORNADO_MOMENTUM_X_MUL_GROUND, flt_var);
    ftCommon_8007CB74(gobj);
    if (((u32) fp->x2208_ftcmd_var2 != 0U) &&
        ((fp->input.x668 & HSD_BUTTON_B) != 0))
    {
        flt_var = fp->x80_self_vel.y;
        fp->x80_self_vel.y =
            (f32) (flt_var + sa->x54_MARIO_TORNADO_TAP_Y_VEL_MAX);
        _ftMario_800E23E4_800E25C4_helper_0(gobj);
    }
}

// 0x800E2508
// https://decomp.me/scratch/sjB2k
void ftMr_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    f32 flt_var;
    ftMarioAttributes* sa;
    ftMarioAttributes* sa_2;
    Fighter* fp;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = getFighter(gobj);
    sa = fp->x2D4_specialAttributes;

    if (((s32) fp->ev.mr.x2234_tornadoCharge == false) &&
        ((u32) fp->x2208_ftcmd_var2 != 0U) &&
        ((fp->input.x668 & HSD_BUTTON_B) != 0))
    {
        ftCommon_8007D508(fp, sa->x54_MARIO_TORNADO_TAP_Y_VEL_MAX,
                          sa->x58_MARIO_TORNADO_TAP_GRAVITY);
    }
    ftCommon_8007D4B8(fp);
    flt_var = sa->x40_MARIO_TORNADO_MOMENTUM_X_AIR;
    sa_2 = fp->x2D4_specialAttributes;
    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        fp->sv.mr.SpecialLw.groundVelX =
            (f32) (fp->sv.mr.SpecialLw.groundVelX -
                   sa_2->x4C_MARIO_TORNADO_FRICTION_END);
        flt_var += fp->sv.mr.SpecialLw.groundVelX;
        if (flt_var < 0.0f) {
            flt_var = 0.0f;
        }
    }
    ftCommon_8007D3A8(fp, 0.0f, sa->x48_MARIO_TORNADO_MOMENTUM_X_MUL_AIR,
                      flt_var);
}

void _ftMario_800E25C4_800E2778_helper(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    if ((fp->x220C_ftcmd_var3 != 0U) &&
        ((s32) (fp->sv.mr.SpecialLw.isUnkColl) != 0))
    {
        ftParts_8007592C(fp, 0,
                         fp->facing_dir *
                             atan2f(fp->x6F0_collData.x14C_ground.normal.x,
                                    fp->x6F0_collData.x14C_ground.normal.y));
    } else {
        ftParts_8007592C(fp, 0, 0.0f);
    }
}

static ftCollisionBox coll_box = {
    12.0F, 0.0F, { -6.0F, 6.0F }, { 6.0F, 6.0F }
};

// 0x800E25C4
// https://decomp.me/scratch/ykJHP
void ftMr_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    if (fp->xE0_ground_or_air == GA_Ground) {
        if (ft_80082888(gobj, &coll_box) == false) {
            _ftMario_800E23E4_800E25C4_helper_0(gobj);
            fp->sv.mr.SpecialLw.isUnkColl = false;
        } else {
            fp->sv.mr.SpecialLw.isUnkColl = true;
        }
    } else {
        if (ft_800824A0(gobj, &coll_box) == false) {
            _ftMario_800E23E4_800E25C4_helper_0(gobj);
            fp->sv.mr.SpecialLw.isUnkColl = false;
        } else {
            fp->sv.mr.SpecialLw.isUnkColl = true;
        }
    }

    _ftMario_800E25C4_800E2778_helper(gobj);
}

void _ftMario_800E2778_helper(HSD_GObj* gobj)
{
    Fighter* ft_tmp;
    Fighter* fp;
    ftMarioAttributes* sa;
    fp = getFighter(gobj);
    sa = GetMarioAttr(fp);
    fp->x2208_ftcmd_var2 = 0;
    ftCommon_8007D7FC(fp);
    fp->x80_self_vel.y = 0.0f;
    fp->ev.mr.x2234_tornadoCharge = 0;
    Fighter_ChangeMotionState(gobj, AS_MARIO_SPECIALLW,
                              FTMARIO_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftCommon_8007CC78(ft_tmp = fp, sa->x3C_MARIO_TORNADO_MOMENTUM_X_GROUND);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

// 0x800E2778
// https://decomp.me/scratch/v3srn
void ftMr_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_800824A0(gobj, &coll_box) != 0) {
        _ftMario_800E2778_helper(gobj);
        fp->sv.mr.SpecialLw.isUnkColl = 1;
    } else {
        fp->sv.mr.SpecialLw.isUnkColl = 0;
    }

    _ftMario_800E25C4_800E2778_helper(gobj);
}
