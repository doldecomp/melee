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

#include <stddef.h>
#include <baselib/random.h>

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

static void doStartAction(HSD_GObj* gobj)
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
    doStartAction(gobj);
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
    doStartAction(gobj);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

void ftMario_SpecialLw_SetNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cb.x21DC_callback_OnTakeDamage = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
}

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

void ftMario_SpecialLw_IASA(HSD_GObj* gobj) {}

void ftMario_SpecialAirLw_IASA(HSD_GObj* gobj) {}

static usize_t const transition_flags =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateHit |
    FtStateChange_SkipUpdateMatAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

static void doPhys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftMario_DatAttrs* sa = GetMarioAttr(fp);
    fp->x2208_ftcmd_var2 = 0;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, ftMario_AS_SpecialAirLw,
                                       transition_flags, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftComm_ClampFallSpeed(fp, sa->x58_MARIO_TORNADO_TAP_GRAVITY);
    func_8007D440(fp, sa->x40_MARIO_TORNADO_MOMENTUM_X_AIR);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

void ftMario_SpecialLw_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp0 = GET_FIGHTER(gobj);
    ftMario_DatAttrs* sa = GetMarioAttr(fp0);
    f32 vel_y = sa->x3C_MARIO_TORNADO_MOMENTUM_X_GROUND;

    if (fp0->x2200_ftcmd_var0 != 0) {
        fp0->sv.mr.SpecialLw.groundVelX = fp0->sv.mr.SpecialLw.groundVelX -
                                          sa->x4C_MARIO_TORNADO_FRICTION_END;
        vel_y += fp0->sv.mr.SpecialLw.groundVelX;
        if (vel_y < 0.0f)
            vel_y = 0.0f;
    }

    {
        Fighter* fp1 = fp0;
        func_8007CADC(fp1, 0.0f, sa->x44_MARIO_TORNADO_MOMENTUM_X_MUL_GROUND,
                      vel_y);
        func_8007CB74(gobj);
        if (fp0->x2208_ftcmd_var2 != 0 && (fp0->input.x668 & HSD_BUTTON_B)) {
            vel_y = fp0->x80_self_vel.y;
            fp0->x80_self_vel.y = vel_y + sa->x54_MARIO_TORNADO_TAP_Y_VEL_MAX;
            doPhys(gobj);
        }
    }
}

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

static void doColl(HSD_GObj* gobj)
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

static ftCollisionBox coll_box = { 12, 0, { -6, +6 }, { 6, 6 } };

void ftMario_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    if (fp->xE0_ground_or_air == GA_Ground) {
        if (func_80082888(gobj, &coll_box) == false) {
            doPhys(gobj);
            fp->sv.mr.SpecialLw.isUnkColl = false;
        } else {
            fp->sv.mr.SpecialLw.isUnkColl = true;
        }
    } else {
        if (func_800824A0(gobj, &coll_box) == false) {
            doPhys(gobj);
            fp->sv.mr.SpecialLw.isUnkColl = false;
        } else {
            fp->sv.mr.SpecialLw.isUnkColl = true;
        }
    }

    doColl(gobj);
}

static void doAirCollIfUnk(HSD_GObj* gobj)
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
                                       transition_flags, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007CC78(ft_tmp = fp, sa->x3C_MARIO_TORNADO_MOMENTUM_X_GROUND);
    fp->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

void ftMario_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    if (func_800824A0(gobj, &coll_box) != 0) {
        doAirCollIfUnk(gobj);
        fp->sv.mr.SpecialLw.isUnkColl = 1;
    } else {
        fp->sv.mr.SpecialLw.isUnkColl = 0;
    }

    doColl(gobj);
}
