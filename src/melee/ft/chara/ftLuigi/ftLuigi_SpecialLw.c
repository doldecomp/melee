#include "forward.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftLuigi/ftluigi.h"
#include "melee/ft/inlines.h"

// 0x801445C4
// https://decomp.me/scratch/TTyNT // Luigi Cyclone Rotation Update
void ftLuigi_SpecialLw_UpdateRot(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007592C(fp, 0, 0.0f);
}

static inline void ftLuigi_SpecialLw_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->mv.lg.SpecialLw.groundVelX = (f32) 0.0f;
    fp->mv.lg.SpecialLw.unk = (s32) luigiAttrs->x88_LUIGI_CYCLONE_UNK + 1;
    fp->mv.lg.SpecialLw.isUnkColl = false;
}

static inline void ftLuigi_SpecialLw_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = ftLuigi_SpecialLw_UpdateRot;
    fp->cb.x21E4_callback_OnDeath2 = ftLuigi_SpecialLw_UpdateRot;
}

static inline void ftLuigi_SpecialLw_SetGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* hsd_obj = gobj->hsd_obj;
    ef_Spawn(0x509, gobj, hsd_obj);
    fp->x2219_flag.bits.b0 = 1;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x801445F0
// https://decomp.me/scratch/ // Luigi's grounded Cyclone Action State handler
void ftLuigi_SpecialLw_StartAction(HSD_GObj* gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    Fighter* temp_fp;
    Fighter* fp2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    temp_fp = (fp = GET_FIGHTER(gobj));
    luigiAttrs = temp_fp->x2D4_specialAttributes;
    fp2 = temp_fp;
    GET_FIGHTER(gobj)->x2208_ftcmd_var2 = 0;
    Fighter_ActionStateChange_800693AC(gobj, AS_LUIGI_SPECIALAIRLW, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp2->x80_self_vel.y = (f32) (luigiAttrs->x70_LUIGI_CYCLONE_TAP_MOMENTUM -
                                 luigiAttrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX);
    func_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    ftLuigi_SpecialLw_SetVars(gobj);
    ftLuigi_SpecialLw_SetCall(gobj);
    ftLuigi_SpecialLw_SetGFX(gobj);
    fp2->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp2->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x80144708
// https://decomp.me/scratch/egaIB // Luigi's aerial Cyclone Action State
// handler
void ftLuigi_SpecialAirLw_StartAction(HSD_GObj* gobj)
{
    Fighter* fp;
    ftLuigiAttributes* luigiAttrs;
    Fighter* temp_fp;
    Fighter* fp2;
    f32 cycloneVar;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    temp_fp = (fp = GET_FIGHTER(gobj));
    luigiAttrs = temp_fp->x2D4_specialAttributes;
    fp2 = temp_fp;
    GET_FIGHTER(gobj)->x2208_ftcmd_var2 = 0;
    Fighter_ActionStateChange_800693AC(gobj, AS_LUIGI_SPECIALAIRLW, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    if (fp2->fv.lg.x222C_cycloneCharge != 0) {
        cycloneVar = 0.0f;
    } else
        cycloneVar = luigiAttrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
    fp2->x80_self_vel.y =
        (f32) (luigiAttrs->x70_LUIGI_CYCLONE_TAP_MOMENTUM - cycloneVar);
    func_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    ftLuigi_SpecialLw_SetVars(gobj);
    ftLuigi_SpecialLw_SetCall(gobj);
    ftLuigi_SpecialLw_SetGFX(gobj);
    fp2->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp2->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

static inline void ftLuigi_SpecialLw_SetNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
}

/// Luigi's grounded Cyclone Animation callback
void ftLuigi_SpecialLw_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLuigi_SpecialLw_SetNULL(gobj);
        func_8008A2BC(gobj);
    }
}

/// Luigi's aerial Cyclone Animation callback
void ftLuigi_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* attrs = getFtSpecialAttrsD(fp);

    if (fp->x2204_ftcmd_var1 != 0) {
        fp->x2204_ftcmd_var1 = 0;
        fp->fv.lg.x222C_cycloneCharge = true;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftLuigi_SpecialLw_SetNULL(gobj);
        {
            int landing_lag = attrs->x94_LUIGI_CYCLONE_LANDING_LAG;

            if (landing_lag == 0.0) {
                func_800CC730(gobj);
                return;
            }

            func_80096900(gobj, 1, 0, 1, 1, (f32) landing_lag);
        }
    }
}

/// Luigi's grounded Cyclone IASA callback
void ftLuigi_SpecialLw_IASA(HSD_GObj* gobj) {}

/// Luigi's aerial Cyclone IASA callback
void ftLuigi_SpecialAirLw_IASA(HSD_GObj* gobj) {}

static inline void ftLuigi_SpecialLw_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftLuigiAttributes* luigiAttrs = getFtSpecialAttrs(fp);
    fp->x2208_ftcmd_var2 = 0;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x166, 0x0C4C508A, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftComm_ClampFallSpeed(fp, luigiAttrs->x90_LUIGI_CYCLONE_TAP_GRAVITY);
    func_8007D440(fp, luigiAttrs->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x80144958
// https://decomp.me/scratch/pXs3o // Luigi's grounded Cyclone Physics callback
void ftLuigi_SpecialLw_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* attrs = getFtSpecialAttrs(fp);

    {
        f32 var2 = attrs->x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND;

        if (fp->x2200_ftcmd_var0 != 0) {
            fp->mv.lg.SpecialLw.groundVelX -=
                attrs->x84_LUIGI_CYCLONE_FRICTION_END;
            var2 += fp->mv.lg.SpecialLw.groundVelX;

            if (var2 < 0)
                var2 = 0;
        }

        func_8007CADC(fp, 0, attrs->x7C_LUIGI_CYCLONE_MOMENTUM_X_MUL_GROUND,
                      var2);
    }

    func_8007CB74(gobj);

    if (fp->x2208_ftcmd_var2 != 0 && (fp->input.x668 & HSD_BUTTON_B)) {
        fp->x80_self_vel.y += attrs->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
        ftLuigi_SpecialLw_GroundToAir(gobj);
    }
}

// 0x80144A74C
// https://decomp.me/scratch/85hbq // Luigi's aerial Cyclone Physics callback
void ftLuigi_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* attrs0 = fp->x2D4_specialAttributes;

    if (!fp->fv.lg.x222C_cycloneCharge && fp->x2208_ftcmd_var2 != 0 &&
        (fp->input.x668 & HSD_BUTTON_B))
    {
        func_8007D508(fp, attrs0->x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX,
                      attrs0->x90_LUIGI_CYCLONE_TAP_GRAVITY);
    }

    func_8007D4B8(fp);

    {
        f32 spd_x = attrs0->x78_LUIGI_CYCLONE_MOMENTUM_X_AIR;

        {
            ftLuigiAttributes* attrs1 = fp->x2D4_specialAttributes;

            if (fp->x2200_ftcmd_var0 != 0) {
                fp->mv.lg.SpecialLw.groundVelX -=
                    attrs1->x84_LUIGI_CYCLONE_FRICTION_END;
                spd_x += fp->mv.lg.SpecialLw.groundVelX;

                if (spd_x < 0)
                    spd_x = 0;
            }
        }

        func_8007D3A8(fp, 0, attrs0->x80_LUIGI_CYCLONE_MOMENTUM_X_MUL_AIR,
                      spd_x);
    }
}

static ftCollisionBox ftLuigi_SpecialLw_CollisionBox = {
    12, 0, { -6, +6 }, { +6, +6 }
};

static inline void ftLuigi_SpecialLw_UnkAngle(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (((u32) fp->x220C_ftcmd_var3 != 0U) &&
        ((s32) fp->mv.lg.SpecialLw.isUnkColl != false))
    {
        func_8007592C(fp, 0,
                      fp->facing_dir *
                          atan2f(fp->x6F0_collData.x14C_ground.normal.x,
                                 fp->x6F0_collData.x14C_ground.normal.y));
        return;
    }
    func_8007592C(fp, 0, 0.0f);
}

/// Luigi's grounded Cyclone Collision callback
void ftLuigi_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    if (fp->ground_or_air == GA_Ground) {
        if (!func_80082888(gobj, &ftLuigi_SpecialLw_CollisionBox)) {
            ftLuigi_SpecialLw_GroundToAir(gobj);
            fp->mv.lg.SpecialLw.isUnkColl = false;
        } else {
            fp->mv.lg.SpecialLw.isUnkColl = true;
        }
    } else if (func_800824A0(gobj, &ftLuigi_SpecialLw_CollisionBox) == false) {
        ftLuigi_SpecialLw_GroundToAir(gobj);
        fp->mv.lg.SpecialLw.isUnkColl = false;
    } else {
        fp->mv.lg.SpecialLw.isUnkColl = true;
    }

    ftLuigi_SpecialLw_UnkAngle(gobj);
}

static inline void ftLuigi_SpecialAirLw_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftLuigiAttributes* luigiAttrs = fp->x2D4_specialAttributes;
    fp->x2208_ftcmd_var2 = 0;
    func_8007D7FC(fp);
    fp->x80_self_vel.y = 0.0f;
    fp->fv.lg.x222C_cycloneCharge = false;
    Fighter_ActionStateChange_800693AC(gobj, AS_LUIGI_SPECIALLW,
                                       FTLUIGI_SPECIALLW_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);
    func_8007CC78(fp, luigiAttrs->x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x80144CEC
// https://decomp.me/scratch/fdQ4f // Luigi's aerial Cyclone Collision callback
void ftLuigi_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    if (func_800824A0(gobj, &ftLuigi_SpecialLw_CollisionBox) != false) {
        ftLuigi_SpecialAirLw_AirToGround(gobj);
        fp->mv.lg.SpecialLw.isUnkColl = true;
    } else {
        fp->mv.lg.SpecialLw.isUnkColl = false;
    }
    ftLuigi_SpecialLw_UnkAngle(gobj);
}
