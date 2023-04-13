#include "ftmewtwo.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

// 0x80146198
// https://decomp.me/scratch/QML6g // Reset Disable Stall flag
void ftMewtwo_SpecialLw_ClearDisableGObj(HSD_GObj* gobj)
{
    GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj = NULL;
}

// 0x801461A8
// https://decomp.me/scratch/d5gF6 // Remove Disable projectile
void ftMewtwo_SpecialLw_RemoveDisable(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj != NULL) {
        it_802C49E0(GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj);
        GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj = NULL;
    }
}

// 0x801461F0
// https://decomp.me/scratch/WnODY // Mewtwo's grounded Disable Action State
// handler
void ftMewtwo_SpecialLw_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->ev.mt.x222C_disableGObj = NULL;

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALLW, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    ftAnim_8006EBA4(gobj);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialLw_CreateDisable;
}

// 0x80146264
// https://decomp.me/scratch/fX4aP // Mewtwo's aerial Disable Action State
// handler
void ftMewtwo_SpecialAirLw_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->ev.mt.x222C_disableGObj = NULL;
    fp->x80_self_vel.y = 0.0f;

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALAIRLW, 0, NULL, 0.0f,
                              1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialLw_CreateDisable;
}

// 0x801462DC
//  https://decomp.me/scratch/2no6L // Mewtwo's grounded Disable Animation
//  callback
void ftMewtwo_SpecialLw_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj != NULL) {
            it_802C49E0(GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj);
            GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj = NULL;
        }

        ft_8008A2BC(gobj);
    }
}

// 0x80146338 - Mewtwo's aerial Disable Animation callback
void ftMewtwo_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj != NULL) {
            it_802C49E0(GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj);
            GET_FIGHTER(gobj)->ev.mt.x222C_disableGObj = NULL;
        }
        ft_800CC730(gobj);
    }
}

// 0x80146394 - Mewtwo's grounded Disable IASA callback
void ftMewtwo_SpecialLw_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x80146398 - Mewtwo's aerial Disable IASA callback
void ftMewtwo_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014639C - Mewtwo's grounded Disable Physics callback
void ftMewtwo_SpecialLw_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x801463BC
// https://decomp.me/scratch/haV3L // Mewtwo's aerial Disable Physics callback
void ftMewtwo_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftMewtwoAttributes* mewtwoAttrs = getFtSpecialAttrsD(fp);
    attr* ftAttrs = getFtAttrs(fp);

    ftCommon_8007D494(fp, mewtwoAttrs->x78_MEWTWO_DISABLE_GRAVITY,
                      mewtwoAttrs->x7C_MEWTWO_DISABLE_TERMINAL_VELOCITY);
    ftCommon_8007CE94(fp, ftAttrs->x180_AerialFriction);
}

inline void ftMewtwo_SpecialLw_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ev.mt.x222C_disableGObj != NULL) {
        fp->cb.x21E4_callback_OnDeath2 = ftMewtwo_OnDeath2;
        fp->cb.x21DC_callback_OnTakeDamage = ftMewtwo_OnTakeDamage;
    }
}

// 0x80146410
// https://decomp.me/scratch/ktqvT // Mewtwo's ground -> air Disable Action
// State handler
void ftMewtwo_SpecialLw_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);

    fp->x80_self_vel.y = 0.0f;

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALAIRLW,
                              FTMEWTWO_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialLw_CreateDisable;

    ftMewtwo_SpecialLw_SetCall(gobj);

    ftCommon_8007D468(fp);
}

// 0x801464B0
// https://decomp.me/scratch/xNFhq // Mewtwo's air -> ground Disable Action
// State handler
void ftMewtwo_SpecialAirLw_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, AS_MEWTWO_SPECIALLW,
                              FTMEWTWO_SPECIALLW_COLL_FLAG, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftMewtwo_SpecialLw_CreateDisable;

    ftMewtwo_SpecialLw_SetCall(gobj);
}

// 0x80146544 - Mewtwo's grounded Disable Collision callback
void ftMewtwo_SpecialLw_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, ftMewtwo_SpecialLw_GroundToAir);
}

// 0x8014656C - Mewtwo's aerial Disable Collision callback
void ftMewtwo_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    ft_80082C74(gobj, ftMewtwo_SpecialAirLw_AirToGround);
}

// 0x80146594
// https://decomp.me/scratch/rAoIe // Create Disable projectile
void ftMewtwo_SpecialLw_CreateDisable(HSD_GObj* gobj)
{
    Vec3 sp18;
    Fighter* fp = getFighter(gobj);
    ftMewtwoAttributes* mewtwoAttrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        mewtwoAttrs = getFtSpecialAttrsD(fp);

        lb_8000B1CC(fp->x5E8_fighterBones[0x1B].x0_jobj, NULL, &sp18);

        sp18.x += (mewtwoAttrs->x80_MEWTWO_DISABLE_OFFSET_X * fp->facing_dir);
        sp18.y += mewtwoAttrs->x84_MEWTWO_DISABLE_OFFSET_Y;

        fp->ev.mt.x222C_disableGObj = it_802C4A40(gobj, &sp18, fp->facing_dir);

        ftMewtwo_SpecialLw_SetCall(gobj);

        fp->x2200_ftcmd_var0 = 0U;
    }
}
