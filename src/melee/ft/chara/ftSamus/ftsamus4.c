#include "ftsamus4.h"

#include "ftsamus.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"

void ftSamus_ClearThrowFlagsUnk(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->x2210_ThrowFlags.flags = 0;
    fp->cb.x21BC_callback_Accessory4 = &ftSamus_8012A074;
}

void ftSamus_SpecialS_StartMotion(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->xEC_ground_vel /= samus_attr->x2C;
    fp->x80_self_vel.y = 0.0f;
    if (fp->x673 < samus_attr->x28) {
        Fighter_ChangeMotionState(fighter_gobj, 0x15E, 0, NULL, 0.0f, 1.0f,
                                  0.0f);
        ftAnim_8006EBA4(fighter_gobj);
    } else {
        Fighter_ChangeMotionState(fighter_gobj, 0x15D, 0, NULL, 0.0f, 1.0f,
                                  0.0f);
        ftAnim_8006EBA4(fighter_gobj);
    }
    ftSamus_ClearThrowFlagsUnk(fighter_gobj);
}

void ftSamus_SpecialAirS_StartMotion(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->x80_self_vel.x /= samus_attr->x2C;
    if (fp->x673 < samus_attr->x28) {
        Fighter_ChangeMotionState(fighter_gobj, 0x160, 0, NULL, 0.0f, 1.0f,
                                  0.0f);
        ftAnim_8006EBA4(fighter_gobj);
    } else {
        Fighter_ChangeMotionState(fighter_gobj, 0x15F, 0, NULL, 0.0f, 1.0f,
                                  0.0f);
        ftAnim_8006EBA4(fighter_gobj);
    }
    ftSamus_ClearThrowFlagsUnk(fighter_gobj);
}

void ftSamus_8012A380(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ft_8008A2BC(fighter_gobj);
}

void ftSamus_8012A3BC(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ft_800CC730(fighter_gobj);
}

void ftSamus_8012A3F8(HSD_GObj* fighter_gobj) {}

void ftSamus_8012A3FC(HSD_GObj* fighter_gobj) {}

void ftSamus_8012A400(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSamus_8012A420(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    Fighter* fighter2;
    ftCommon_8007D4B8(fp);
    fighter2 = fp;
    ftCommon_8007CE94(fighter2, samus_attr->x30);
}

void ftSamus_8012A468(HSD_GObj* fighter_gobj)
{
    if (!ft_800827A0(fighter_gobj)) {
        ft_800CC730(fighter_gobj);
    }
}

void ftSamus_8012A4A4(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj))
        ft_80082B1C(fighter_gobj);
}

void ftSamus_8012A4E0(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ft_8008A2BC(fighter_gobj);
}

void ftSamus_8012A51C(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        ft_800CC730(fighter_gobj);
}

void ftSamus_8012A558(HSD_GObj* fighter_gobj) {}

void ftSamus_8012A55C(HSD_GObj* fighter_gobj) {}

void ftSamus_8012A560(HSD_GObj* fighter_gobj)
{
    ft_80084F3C(fighter_gobj);
}

void ftSamus_8012A580(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[40];
#endif

    Fighter* fighter2;
    Fighter* fp;
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;
    fp = fighter2 = GET_FIGHTER(fighter_gobj);
    samus_attr = getFtSpecialAttrs(fp);
    ftCommon_8007D4B8(fp);
    samus_attr2 = samus_attr;
    ftCommon_8007CE94(fp, samus_attr2->x30);
}

void ftSamus_8012A5C8(HSD_GObj* fighter_gobj)
{
    if (!ft_80082708(fighter_gobj)) {
        ft_800CC730(fighter_gobj);
    }
}

void ftSamus_8012A604(HSD_GObj* fighter_gobj)
{
    if (ft_80081D0C(fighter_gobj)) {
        ft_80082B1C(fighter_gobj);
    }
}

void ftSamus_8012A640(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    efLib_DestroyAll(fighter_gobj);
    fp->ev.ss.x2244 = 0;
}
