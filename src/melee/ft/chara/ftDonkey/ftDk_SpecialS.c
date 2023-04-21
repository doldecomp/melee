#include "forward.h"

#include "ftDonkey/ftDk_SpecialS.h"

#include "ftDk_SpecialLw.h"

#include "ef/eflib.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftDk_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialS, 0, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    Fighter_UnsetCmdVar0(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftDk_SpecialLw_8010E0CC;
}

void ftDk_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    fp->x80_self_vel.x /= donkey_attr->SpecialS.x3C_MIN_STICK_X_MOMENTUM;
    fp->x80_self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirS, 0, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    Fighter_UnsetCmdVar0(gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftDk_SpecialLw_8010E148;
}

void ftDk_SpecialS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftDk_SpecialAirS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftDk_SpecialS_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialAirS_IASA(HSD_GObj* gobj) {}

void ftDk_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftDk_SpecialAirS_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    attr* ft_attr = &fp->x110_attr;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs(fp);
    if (fp->x2200_ftcmd_var0) {
        ftCommon_8007D494(fp, donkey_attr->SpecialS.x44_AERIAL_GRAVITY,
                          ft_attr->x170_TerminalVelocity);
    }
    ftCommon_8007CE94(fp,
                      donkey_attr->SpecialS.x40_MOMENTUM_TRANSITION_MODIFIER);
    if (fp->x2200_ftcmd_var0 != 0) {
        /// @todo Fix control flow.
    }
}

static void doAirTransition(HSD_GObj* gobj);

void ftDk_SpecialS_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0) {
        if (!ft_800827A0(gobj)) {
            doAirTransition(gobj);
        }
    } else if (!ft_80082708(gobj)) {
        doAirTransition(gobj);
    }
}

static void doGroundTransition(HSD_GObj* gobj);

void ftDk_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        doGroundTransition(gobj);
    }
}

void doAirTransition(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialAirS, 0x0C4C508A, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
    if (fp->x2219_flag.bits.b0 == true) {
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}

static void doGroundTransition(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftDk_MS_SpecialS, 0x0C4C508A, NULL,
                              fp->x894_currentAnimFrame, 1, 0);
    if (fp->x2219_flag.bits.b0 == true) {
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}
