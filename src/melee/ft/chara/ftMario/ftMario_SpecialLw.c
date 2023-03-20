#include "ftMario_SpecialLw.h"

#include "forward.h"
#include "ftmario.h"
#include "inlines.h"
#include "types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "it/itkind.h"

#include <baselib/random.h>

// 0x800E2050
// https://decomp.me/scratch/8zo4V
void ftMario_SpecialLw_UpdateRot(HSD_GObj* gobj)
{
    Fighter* fp;
    fp = GET_FIGHTER(gobj);

    func_8007592C(fp, 0, 0.0f);
}

void ftMario_SpecialLw_SetGFX(HSD_GObj* gobj)
{
    void* hsd_obj_ptr;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    hsd_obj_ptr = gobj->hsd_obj;

    ef_Spawn(0x47C, gobj, hsd_obj_ptr);
    fp->x2219_flag.bits.b0 = 1;
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

void ftMario_SpecialLw_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = &ftMario_SpecialLw_UpdateRot;
    fp->cb.x21E4_callback_OnDeath2 = &ftMario_SpecialLw_UpdateRot;
}

void _ftMario_800E207C_800E2194_helper(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMario_DatAttrs* sa;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = GET_FIGHTER(gobj);
    sa = (ftMario_DatAttrs*) fp->x2D4_specialAttributes;
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

void ftMario_SpecialLw_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMario_DatAttrs* sa = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    ftMario_SpecialLw_SetVar(gobj);
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialAirLw, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp->x80_self_vel.y = (f32) (sa->x38_MARIO_TORNADO_GROUND_VEL_Y -
                                sa->x54_MARIO_TORNADO_TAP_Y_VEL_MAX);
    func_8007D440(fp, sa->x40_MARIO_TORNADO_MOMENTUM_X_AIR);
    _ftMario_800E207C_800E2194_helper(gobj);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

void ftMario_SpecialAirLw_StartAction(HSD_GObj* gobj)
{
    f32 sub_val;
    Fighter* fp = gobj->user_data;
    ftMario_DatAttrs* sa = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28];
#endif

    ftMario_SpecialLw_SetVar(gobj);
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialAirLw, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    if ((s32) fp->ev.mr.x2234_tornadoCharge != 0) {
        sub_val = 0.0f;
    } else {
        sub_val = sa->x54_MARIO_TORNADO_TAP_Y_VEL_MAX;
    }
    fp->x80_self_vel.y = (f32) (sa->x38_MARIO_TORNADO_GROUND_VEL_Y - sub_val);
    func_8007D440(fp, sa->x40_MARIO_TORNADO_MOMENTUM_X_AIR);
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
void ftMario_SpecialLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMario_SpecialLw_SetNULL(gobj);
        func_8008A2BC(gobj);
    }
}

// 0x800E2308
// https://decomp.me/scratch/QF5fb
void ftMario_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = (ftMario_DatAttrs*) fp->x2D4_specialAttributes;

    if ((u32) fp->x2204_ftcmd_var1 != 0U) {
        fp->x2204_ftcmd_var1 = 0U;
        fp->ev.mr.x2234_tornadoCharge = 1;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMario_SpecialLw_SetNULL(gobj);
        if (0.0 == (f64) sa->x5C_MARIO_TORNADO_LANDING_LAG) {
            func_800CC730(gobj);
            return;
        }
        func_80096900(gobj, 1, 0, true, 1.0f,
                      (f32) sa->x5C_MARIO_TORNADO_LANDING_LAG);
    }
}

// 0x800E23DC
void ftMario_SpecialLw_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E23E0
void ftMario_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    return;
}

void _ftMario_800E23E4_800E25C4_helper_0(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMario_DatAttrs* sa = GetMarioAttr(fp);
    fp->x2208_ftcmd_var2 = 0;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialAirLw,
                                       FTMARIO_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftComm_ClampFallSpeed(fp, sa->x58_MARIO_TORNADO_TAP_GRAVITY);
    func_8007D440(fp, sa->x40_MARIO_TORNADO_MOMENTUM_X_AIR);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

// 0x800E23E4
// https://decomp.me/scratch/aJPK4
void ftMario_SpecialLw_Phys(HSD_GObj* gobj)
{
    f32 flt_var;
    ftMario_DatAttrs* sa;
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
    func_8007CADC(ft_tmp, 0.0f, sa->x44_MARIO_TORNADO_MOMENTUM_X_MUL_GROUND,
                  flt_var);
    func_8007CB74(gobj);
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
void ftMario_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    f32 flt_var;
    ftMario_DatAttrs* sa;
    ftMario_DatAttrs* sa_2;
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
        func_8007D508(fp, sa->x54_MARIO_TORNADO_TAP_Y_VEL_MAX,
                      sa->x58_MARIO_TORNADO_TAP_GRAVITY);
    }
    func_8007D4B8(fp);
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
    func_8007D3A8(fp, 0.0f, sa->x48_MARIO_TORNADO_MOMENTUM_X_MUL_AIR, flt_var);
}

void _ftMario_800E25C4_800E2778_helper(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);

    if ((fp->x220C_ftcmd_var3 != 0U) &&
        ((s32) (fp->sv.mr.SpecialLw.isUnkColl) != 0))
    {
        func_8007592C(fp, 0,
                      fp->facing_dir *
                          atan2f(fp->x6F0_collData.x14C_ground.normal.x,
                                 fp->x6F0_collData.x14C_ground.normal.y));
    } else {
        func_8007592C(fp, 0, 0.0f);
    }
}

static ftCollisionBox ftMario_SpecialLw_CollisionBox = {
    12.0F, 0.0F, { -6.0F, 6.0F }, { 6.0F, 6.0F }
};

// 0x800E25C4
// https://decomp.me/scratch/ykJHP
void ftMario_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    if (fp->xE0_ground_or_air == GA_Ground) {
        if (func_80082888(gobj, &ftMario_SpecialLw_CollisionBox) == false) {
            _ftMario_800E23E4_800E25C4_helper_0(gobj);
            fp->sv.mr.SpecialLw.isUnkColl = false;
        } else {
            fp->sv.mr.SpecialLw.isUnkColl = true;
        }
    } else {
        if (func_800824A0(gobj, &ftMario_SpecialLw_CollisionBox) == false) {
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
    ftMario_DatAttrs* sa;
    fp = getFighter(gobj);
    sa = GetMarioAttr(fp);
    fp->x2208_ftcmd_var2 = 0;
    func_8007D7FC(fp);
    fp->x80_self_vel.y = 0.0f;
    fp->ev.mr.x2234_tornadoCharge = 0;
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialLw,
                                       FTMARIO_SPECIALLW_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007CC78(ft_tmp = fp, sa->x3C_MARIO_TORNADO_MOMENTUM_X_GROUND);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

// 0x800E2778
// https://decomp.me/scratch/v3srn
void ftMario_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    if (func_800824A0(gobj, &ftMario_SpecialLw_CollisionBox) != 0) {
        _ftMario_800E2778_helper(gobj);
        fp->sv.mr.SpecialLw.isUnkColl = 1;
    } else {
        fp->sv.mr.SpecialLw.isUnkColl = 0;
    }

    _ftMario_800E25C4_800E2778_helper(gobj);
}
