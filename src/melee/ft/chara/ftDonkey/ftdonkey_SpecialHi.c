#include "ftdonkey_SpecialHi.h"

#include "ftdonkey.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcliffcommon.h"
#include "ft/inlines.h"

void ftDonkey_SetCallbacks_SpecialHi(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = &ftDonkey_8010D774;
    fp->cb.x21E4_callback_OnDeath2 = &ftDonkey_8010D774;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDonkey_SpecialHi_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    Fighter_ChangeMotionState(gobj, 0x17D, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_SetCallbacks_SpecialHi(gobj);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftCommon_8007CC78(fp,
                      donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fp->x80_self_vel.x = fp->gr_vel;
    fp->x80_self_vel.y = 0.0f;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(0x4CA, gobj, fp->ft_bones[0].x0_jobj);
}

void ftDonkey_SpecialAirHi_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, 0x17E, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftDonkey_SetCallbacks_SpecialHi(gobj);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    ftCommon_8007D440(fp,
                      donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fp->x80_self_vel.y = donkey_attr->SpecialHi.x4C_AERIAL_VERTICAL_VELOCITY;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(0x4CA, gobj, fp->ft_bones[0].x0_jobj);
}

void ftDonkey_8010FCD4(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDonkey_8010FD10(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);
        if (donkey_attr->SpecialHi.x64_LANDING_LAG == 0.0f) {
            ft_800CC730(gobj);
        } else {
            ft_80096900(gobj, 1, 0, 1, 1.0f,
                        donkey_attr->SpecialHi.x64_LANDING_LAG);
        }
    }
}

void ftDonkey_8010FD9C(HSD_GObj* gobj) {}

void ftDonkey_8010FDA0(HSD_GObj* gobj) {}

void ftDonkey_8010FDA4(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    ftCommon_8007CADC(fp, 0.0f, donkey_attr->SpecialHi.x5C_GROUNDED_MOBILITY,
                      donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    ftCommon_8007CB74(gobj);
}

void ftDonkey_8010FDEC(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    f32 gravity_scalar;

    if (fp->x2200_ftcmd_var0) {
        gravity_scalar = 1.0f;
    } else {
        gravity_scalar = donkey_attr->SpecialHi.x50_AERIAL_GRAVITY;
    }
    ftCommon_8007D494(fp, gravity_scalar * fp->x110_attr.x16C_Gravity,
                      fp->x110_attr.x170_TerminalVelocity);
    ftCommon_8007D344(fp, 0.0f, donkey_attr->SpecialHi.x60_AERIAL_MOBILITY,
                      donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
}

void ftDonkey_8010FE60(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    if (!ft_80082708(gobj)) {
        ftCommon_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, 0x17E, 0x0C4C5080, NULL,
                                  fp->x894_currentAnimFrame, 1.0f, 0.0f);
        ftDonkey_SetCallbacks_SpecialHi(gobj);
        ftCommon_8007D440(
            fp, donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
    }
}

void ftDonkey_8010FF14(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x80_self_vel.y >= 0.0f) {
        if (ft_80081D0C(gobj)) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, 0x17D, 0x0C4C5080, NULL,
                                      fp->x894_currentAnimFrame, 1.0f, 0.0f);
            ftDonkey_SetCallbacks_SpecialHi(gobj);
            ftCommon_8007CC78(
                fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        }
    } else {
        if (ft_CheckGroundAndLedge(gobj, 0)) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, 0x17D, 0x0C4C5080, NULL,
                                      fp->x894_currentAnimFrame, 1.0f, 0.0f);
            ftDonkey_SetCallbacks_SpecialHi(gobj);
            ftCommon_8007CC78(
                fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        } else if (ftCliffCommon_80081298(gobj)) {
            ftCliffCommon_80081370(gobj);
        }
    }
}

void ftDonkey_DestroyAllEffects_SpecialHi(HSD_GObj* gobj)
{
    efLib_DestroyAll(gobj);
}
