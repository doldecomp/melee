#include "ftDonkey/ftdonkey_SpecialS.h"

#include "ef/eflib.h"
#include "ft/ft_81B.h"
#include "ft/ft_877.h"
#include "ft/inlines.h"
#include "ftDonkey/ftdonkey.h"

void ftDonkey_SpecialS_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(gobj, 0x17B, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    Fighter_UnsetCmdVar0(gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftDonkey_8010E0CC;
}

void ftDonkey_SpecialAirS_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftDonkeyAttributes* donkey_attr = fp->x2D4_specialAttributes;
    fp->x80_self_vel.x /= donkey_attr->SpecialS.x3C_MIN_STICK_X_MOMENTUM;
    fp->x80_self_vel.y = 0.0f;
    Fighter_ChangeMotionState(gobj, 0x17C, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    Fighter_UnsetCmdVar0(gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftDonkey_8010E148;
}

void ftDonkey_8010E2BC(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void ftDonkey_8010E2F8(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_800CC730(gobj);
    }
}

void ftDonkey_8010E334(HSD_GObj* gobj) {}

void ftDonkey_8010E338(HSD_GObj* gobj) {}

void ftDonkey_8010E33C(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftDonkey_8010E35C(HSD_GObj* gobj)
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

void ftDonkey_8010E3BC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2200_ftcmd_var0) {
        if (!func_800827A0(gobj)) {
            ftDonkey_8010E464(gobj);
        }
    } else if (!func_80082708(gobj)) {
        ftDonkey_8010E464(gobj);
    }
}

void ftDonkey_8010E428(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj)) {
        ftDonkey_8010E4EC(gobj);
    }
}

void ftDonkey_8010E464(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x17C, 0x0C4C508A, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    if (fp->x2219_flag.bits.b0 == 1) {
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}

void ftDonkey_8010E4EC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x17B, 0x0C4C508A, NULL,
                              fp->x894_currentAnimFrame, 1.0f, 0.0f);
    if (fp->x2219_flag.bits.b0 == 1) {
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}
