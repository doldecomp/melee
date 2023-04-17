#include "ftsamus4.h"

#include "ftsamus.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"

void ftSamus_ClearThrowFlagsUnk(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2210_ThrowFlags.flags = 0;
    fp->cb.x21BC_callback_Accessory4 = &ftSs_SpecialS_8012A074;
}

void ftSs_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->gr_vel /= samus_attr->x2C;
    fp->x80_self_vel.y = 0.0f;
    if (fp->x673 < samus_attr->x28) {
        Fighter_ChangeMotionState(gobj, 0x15E, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftAnim_8006EBA4(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, 0x15D, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftAnim_8006EBA4(gobj);
    }
    ftSamus_ClearThrowFlagsUnk(gobj);
}

void ftSs_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    fp->x80_self_vel.x /= samus_attr->x2C;
    if (fp->x673 < samus_attr->x28) {
        Fighter_ChangeMotionState(gobj, 0x160, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftAnim_8006EBA4(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, 0x15F, 0, NULL, 0.0f, 1.0f, 0.0f);
        ftAnim_8006EBA4(gobj);
    }
    ftSamus_ClearThrowFlagsUnk(gobj);
}

void ftSs_SpecialS_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialAirS_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftSs_SpecialS_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialAirS_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialAirS_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);
    Fighter* fighter2;
    ftCommon_8007D4B8(fp);
    fighter2 = fp;
    ftCommon_8007CE94(fighter2, samus_attr->x30);
}

void ftSs_SpecialS_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftSs_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ft_80082B1C(gobj);
    }
}

void ftSs_SpecialSSmash_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialAirSmash_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftSs_SpecialSSmash_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialAirSmash_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialSSmash_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialAirSmash_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[40];
#endif

    Fighter* fighter2;
    Fighter* fp;
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;
    fp = fighter2 = GET_FIGHTER(gobj);
    samus_attr = getFtSpecialAttrs(fp);
    ftCommon_8007D4B8(fp);
    samus_attr2 = samus_attr;
    ftCommon_8007CE94(fp, samus_attr2->x30);
}

void ftSs_SpecialSSmash_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftSs_SpecialAirSmash_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ft_80082B1C(gobj);
    }
}

void ftSs_SpecialS_8012A640(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    efLib_DestroyAll(gobj);
    fp->fv.ss.x2244 = 0;
}
