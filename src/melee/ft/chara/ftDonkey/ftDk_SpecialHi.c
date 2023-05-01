#include "forward.h"

#include "ftDk_SpecialHi.h"

#include "ftDk_Init.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

static void setCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = ftDk_Init_8010D774;
    fp->cb.x21E4_callback_OnDeath2 = ftDk_Init_8010D774;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

void ftDk_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialHi, 0, NULL, 0, 1, 0);
    setCallbacks(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftCommon_8007CC78(fp,
                      donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fp->self_vel.x = fp->gr_vel;
    fp->self_vel.y = 0;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(1226, gobj, fp->parts[FtPart_TopN].x0_jobj);
}

void ftDk_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirHi, 0, NULL, 0, 1, 0);
    setCallbacks(gobj);
    fp->cmd_vars[0] = fp->cmd_vars[1] = fp->cmd_vars[2] = fp->cmd_vars[3] = 0;
    ftCommon_8007D440(fp,
                      donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    fp->self_vel.y = donkey_attr->SpecialHi.x4C_AERIAL_VERTICAL_VELOCITY;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    ftAnim_8006EBA4(gobj);
    efSync_Spawn(1226, gobj, fp->parts[FtPart_TopN].x0_jobj);
}

void ftDk_SpecialHi_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);
        if (donkey_attr->SpecialHi.x64_LANDING_LAG == 0) {
            ft_800CC730(gobj);
        } else {
            ft_80096900(gobj, 1, 0, 1, 1,
                        donkey_attr->SpecialHi.x64_LANDING_LAG);
        }
    }
}

void ftDk_SpecialHi_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialAirHi_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    ftCommon_8007CADC(fp, 0, donkey_attr->SpecialHi.x5C_GROUNDED_MOBILITY,
                      donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
    ftCommon_8007CB74(gobj);
}

void ftDk_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    f32 grav_mul;
    if (fp->cmd_vars[0]) {
        grav_mul = 1;
    } else {
        grav_mul = donkey_attr->SpecialHi.x50_AERIAL_GRAVITY;
    }
    ftCommon_8007D494(fp, grav_mul * fp->x110_attr.x16C_Gravity,
                      fp->x110_attr.x170_TerminalVelocity);
    ftCommon_8007D344(fp, 0, donkey_attr->SpecialHi.x60_AERIAL_MOBILITY,
                      donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
}

void ftDk_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;

    if (!ft_80082708(gobj)) {
        ftCommon_8007D60C(fp);
        Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirHi, 0x0C4C5080, NULL,
                                  fp->cur_anim_frame, 1, 0);
        setCallbacks(gobj);
        ftCommon_8007D440(
            fp, donkey_attr->SpecialHi.x58_AERIAL_HORIZONTAL_VELOCITY);
    }
}

void ftDk_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->dat_attrs;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    if (fp->self_vel.y >= 0) {
        if (ft_80081D0C(gobj)) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialHi, 0x0C4C5080,
                                      NULL, fp->cur_anim_frame, 1, 0);
            setCallbacks(gobj);
            ftCommon_8007CC78(
                fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        }
    } else {
        if (ft_CheckGroundAndLedge(gobj, 0)) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialHi, 0x0C4C5080,
                                      NULL, fp->cur_anim_frame, 1, 0);
            setCallbacks(gobj);
            ftCommon_8007CC78(
                fp, donkey_attr->SpecialHi.x54_GROUNDED_HORIZONTAL_VELOCITY);
        } else if (ftCliffCommon_80081298(gobj)) {
            ftCliffCommon_80081370(gobj);
        }
    }
}

void ftDk_SpecialHi_DestroyAllEffects(HSD_GObj* gobj)
{
    efLib_DestroyAll(gobj);
}
