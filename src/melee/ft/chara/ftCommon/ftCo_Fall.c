#include "ftCo_Fall.h"

#include "math.h"

#include <placeholder.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0CEE.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_EscapeAir.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_HammerFall.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftMasterHand/ftMh_Wait1_2.h"
#include "ftPeach/ftPe_Float.h"

static inline bool ftCo_Fall_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2224_b2) {
        ftCo_80090780(gobj);
        return true;
    }

    if (ftCo_800C5240(gobj)) {
        ftCo_800C5D34(gobj);
        return true;
    }

    return false;
}

void ftCo_Fall_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftLib_800872A4(gobj) == FTKIND_MASTERH) {
        ftMh_MS_389_80151018(gobj);
        return;
    }

    if (ftLib_800872A4(gobj) == FTKIND_CREZYH) {
        ftCh_GrabUnk1_8015BC88(gobj);
        return;
    }

    if (!ftCo_Fall_inline(gobj)) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Fall, Ft_MF_KeepFastFall, 0.0F,
                                  1.0F, 0.0F, NULL);
        ftCommon_8007D468(fp);
        fp->mv.co.fall.smid = ftCo_SM_Fall;
        fp->mv.co.fall.x4 = 0.0F;
        if (fp->ground_or_air == GA_Ground) {
            ftCommon_8007D5D4(fp);
        }
    }
}

void ftCo_Fall_Enter_YoshiEgg(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftCo_Fall_inline(gobj)) {
        Fighter_ChangeMotionState(gobj, ftCo_MS_Fall, Ft_MF_Unk06, 0.0F, 1.0F,
                                  -1.0F, NULL);
        fp->mv.co.fall.smid = ftCo_SM_Fall;
        fp->mv.co.fall.x4 = 0.0F;
    }
}

void ftCo_Fall_Enter_YoshiEgg_Kirby(Fighter_GObj* gobj)
{
    ftCo_Fall_Enter_YoshiEgg(gobj);
}

void ftCo_800CC988(Fighter_GObj* gobj, f32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (arg1) {
        HSD_JObjAnimAll(fp->x8AC_animSkeleton);
        if (arg1 != 1.0F) {
            ftAnim_8006FE9C(fp, 1, arg1, 1.0F - arg1);
        } else {
            ftAnim_8006FF74(fp, 1);
        }
    }
}

void ftCo_Fall_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2228_b2) {
        ftCo_Fall_Anim_Inner(gobj, &fp->mv.co.fall.x4, ftCo_SM_Fall,
                             ftCo_SM_FallF, ftCo_SM_FallB);
        ftCo_800CC988(gobj, fp->mv.co.fall.x4);
    }
}

bool ftCo_Fall_IASA_Inner(Fighter_GObj* gobj)
{
    if (ftCo_SpecialAir_CheckInput(gobj)) {
        return true;
    }
    if (ftCo_80095328(gobj, NULL)) {
        return true;
    }
    if (ftCo_800D7100(gobj)) {
        return true;
    }
    if (ftCo_800C3B10(gobj)) {
        return true;
    }
    if (ftCo_80099A58(gobj)) {
        return true;
    }
    if (ftCo_AttackAir_CheckItemThrowInput(gobj)) {
        return true;
    }
    if (ftCo_800D705C(gobj)) {
        return true;
    }
    if (ftCo_800CEE70(gobj)) {
        return true;
    }
    if (ftPe_8011BA54(gobj)) {
        return true;
    }
    if (ftCo_800CB870(gobj)) {
        return true;
    }
    if (ftPe_8011BAD8(gobj)) {
        return true;
    }

    return false;
}

void ftCo_Fall_Anim_Inner(Fighter_GObj* gobj, f32* mv_x4,
                          FtMotionId neutral_smid, FtMotionId forwards_smid,
                          FtMotionId backwards_smid)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 var_f0;
    f32 air_drift_frac = fp->self_vel.x / fp->co_attrs.air_drift_max;
    f32 air_drift_frac_abs;
    FtMotionId smid;
    PAD_STACK(8);

    // limits air drift to +/- air_drift_max
    if (air_drift_frac > 1.0F) {
        air_drift_frac = 1.0F;
    } else if (air_drift_frac < -1.0F) {
        air_drift_frac = -1.0F;
    }

    air_drift_frac_abs = ABS(air_drift_frac);
    if (air_drift_frac_abs > p_ftCommonData->x444) {
        if (air_drift_frac * fp->facing_dir > 0.0F) {
            smid = forwards_smid;
        } else {
            smid = backwards_smid;
        }
        var_f0 = (air_drift_frac_abs - p_ftCommonData->x444) /
                 (1.0F - p_ftCommonData->x444);
    } else {
        smid = neutral_smid;
        var_f0 = 0.0F;
    }

    *mv_x4 += p_ftCommonData->x448 * (var_f0 - *mv_x4);
    if (*mv_x4 && smid != fp->mv.co.fall.smid) {
        ftAnim_8006EDD0(fp, smid, fp->cur_anim_frame, 1.0F);
        HSD_JObjAnimAll(fp->x8AC_animSkeleton);
        if (*mv_x4 != 1.0F) {
            ftAnim_8006FE9C(fp, 1, *mv_x4, 1.0F - *mv_x4);
        } else {
            ftAnim_8006FF74(fp, 1);
        }
        fp->mv.co.fall.smid = smid;
    }
}

void ftCo_Fall_IASA(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_Fall_IASA_Inner(gobj));
}

void ftCo_Fall_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_Fall_Coll(Fighter_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, (HSD_GObjEvent) ft_80082B1C);
}
