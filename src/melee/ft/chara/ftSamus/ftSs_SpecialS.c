#include "ftSs_SpecialS.h"

#include "ftSs_SpecialN.h"

#include "ef/eflib.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftSamus/types.h"

#include <dolphin/mtx.h>

static void ftSamus_ClearThrowFlagsUnk(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->throw_flags = 0;
    fp->accessory4_cb = &ftSs_SpecialS_8012A074;
}

void ftSs_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    fp->gr_vel /= samus_attr->x2C;
    fp->self_vel.y = 0.0f;
    if (fp->x673 < samus_attr->x28) {
        Fighter_ChangeMotionState(gobj, 0x15E, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, 0x15D, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
    ftSamus_ClearThrowFlagsUnk(gobj);
}

void ftSs_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    fp->self_vel.x /= samus_attr->x2C;
    if (fp->x673 < samus_attr->x28) {
        Fighter_ChangeMotionState(gobj, 0x160, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, 0x15F, 0, 0.0f, 1.0f, 0.0f, NULL);
        ftAnim_8006EBA4(gobj);
    }
    ftSamus_ClearThrowFlagsUnk(gobj);
}

void ftSs_SpecialS_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialAirS_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
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
    u8 _[24];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    Fighter* fighter2;
    ftCommon_8007D4B8(fp);
    fighter2 = fp;
    ftCommon_8007CE94(fighter2, samus_attr->x30);
}

void ftSs_SpecialS_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftCo_Fall_Enter(gobj);
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
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialAirSSmash_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftSs_SpecialSSmash_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialAirSSmash_IASA(HSD_GObj* gobj) {}

void ftSs_SpecialSSmash_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftSs_SpecialAirSSmash_Phys(HSD_GObj* gobj)
{
    u8 _[40];

    Fighter* fighter2;
    Fighter* fp;
    ftSs_DatAttrs* samus_attr;
    ftSs_DatAttrs* samus_attr2;
    fp = fighter2 = GET_FIGHTER(gobj);
    samus_attr = getFtSpecialAttrs(fp);
    ftCommon_8007D4B8(fp);
    samus_attr2 = samus_attr;
    ftCommon_8007CE94(fp, samus_attr2->x30);
}

void ftSs_SpecialSSmash_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftSs_SpecialAirSSmash_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ft_80082B1C(gobj);
    }
}

void ftSs_SpecialS_8012A640(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    efLib_DestroyAll(gobj);
    fp->fv.ss.x2244 = 0;
}
