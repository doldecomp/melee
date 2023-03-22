#include "ftsamus4.h"

#include "ftsamus.h"

#include "ft/ft_81B.h"
#include "ft/ft_877.h"

void ftSamus_ClearThrowFlagsUnk(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2210_ThrowFlags.flags = 0;
    fp->cb.x21BC_callback_Accessory4 = &ftSamus_8012A074;
}

void ftSamus_SpecialS_StartMotion(HSD_GObj* gobj)
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

void ftSamus_SpecialAirS_StartMotion(HSD_GObj* gobj)
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

void ftSamus_8012A380(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void ftSamus_8012A3BC(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

void ftSamus_8012A3F8(HSD_GObj* gobj) {}

void ftSamus_8012A3FC(HSD_GObj* gobj) {}

void ftSamus_8012A400(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftSamus_8012A420(HSD_GObj* gobj)
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

void ftSamus_8012A468(HSD_GObj* gobj)
{
    if (!func_800827A0(gobj)) {
        func_800CC730(gobj);
    }
}

void ftSamus_8012A4A4(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj))
        func_80082B1C(gobj);
}

void ftSamus_8012A4E0(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void ftSamus_8012A51C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

void ftSamus_8012A558(HSD_GObj* gobj) {}

void ftSamus_8012A55C(HSD_GObj* gobj) {}

void ftSamus_8012A560(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftSamus_8012A580(HSD_GObj* gobj)
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

void ftSamus_8012A5C8(HSD_GObj* gobj)
{
    if (!func_80082708(gobj)) {
        func_800CC730(gobj);
    }
}

void ftSamus_8012A604(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj)) {
        func_80082B1C(gobj);
    }
}

void ftSamus_8012A640(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    efLib_DestroyAll(gobj);
    fp->fv.ss.x2244 = 0;
}
