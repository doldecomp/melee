#include "ftCo_ItemParasolOpen.h"

#include "ftCo_ItemParasolFall.h"
#include "math.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AirCatch.h"
#include "ftCommon/ftCo_AttackAir.h"
#include "ftCommon/ftCo_ItemParasolFallSpecial.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftCommon/inlines.h"

#include "ftPeach/forward.h"

bool ftCo_800CEE70(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2221_b5) {
        return false;
    }
    if ((fp->x2221_b7 ||
         fp->input.lstick.y >= p_ftCommonData->open_parasol_threshold) &&
        fp->self_vel.y <= 0.0f && (ftGetParasolStatus(gobj) == 6))
    {
        ft_800CEF08(gobj);
        return true;
    }
    return false;
}

static inline void ft_800CEF08_inline1(Fighter* fp, int x2104)
{
    fp->x2221_b7 = false;
    fp->x2221_b4 = true;
    if (fp->x2221_b6) {
        fp->x2104 = x2104;
        fp->x2221_b6 = false;
    }
}

void ft_800CEF08(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.parasol_open.prev_msid = fp->motion_id;
    Fighter_ChangeMotionState(
        gobj,
        ftCo_ItemParasolGetFallMotionId(gobj, ftPe_MS_ItemParasolOpen,
                                        ftCo_MS_ItemParasolOpen),
        0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ft_800CEF08_inline1(fp, p_ftCommonData->x59C);
}

/// @@todo What is this copypasta...
void ftCo_800CEFE0(Fighter_GObj* gobj, int arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.parasol_open.prev_msid = fp->motion_id;
    Fighter_ChangeMotionState(
        gobj,
        ftCo_ItemParasolGetFallMotionId(gobj, ftPe_MS_ItemParasolOpen,
                                        ftCo_MS_ItemParasolOpen),
        0, 0.0f, 1.0f, 10.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ft_800CEF08_inline1(fp, p_ftCommonData->x59C);
}

void ftCo_ItemParasolOpen_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.co.parasol_open.prev_msid == ftCo_MS_FallSpecial) {
            ftCo_800CF3C8(gobj);
        } else {
            ftCo_800CF280(gobj);
        }
    }
}

void ftCo_ItemParasolOpen_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.parasol_open.prev_msid != ftCo_MS_FallSpecial) {
        RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
        RETURN_IF(ftCo_80095328(gobj, NULL));
        RETURN_IF(ftCo_800C3B10(gobj));
        RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
    }
    RETURN_IF(ftCo_800CB870(gobj));
}

void ftCo_ItemParasolOpen_Phys(Fighter_GObj* gobj)
{
    ftCo_DatAttrs* ca;
    Fighter* fp = GET_FIGHTER(gobj);
    ca = &fp->co_attrs;

    {
        float mul = p_ftCommonData->x590;
        float grav = ca->grav * mul;
        float terminal_vel = ca->terminal_vel * mul;
        ftCommon_Fall(fp, grav, terminal_vel);
        {
            float drift, target_vel;
            if (ABS(fp->input.lstick.x) >= p_ftCommonData->x258) {
                drift = p_ftCommonData->x58C *
                        (fp->input.lstick.x * ca->air_drift_stick_mul);
                target_vel = p_ftCommonData->x58C *
                             (fp->input.lstick.x * ca->air_drift_max);
            } else {
                target_vel = 0.0F;
                drift = 0.0F;
            }
            ftCommon_8007D140(fp, drift, target_vel, ca->aerial_friction);
        }
    }
}

void ftCo_ItemParasolOpen_Coll(Fighter_GObj* gobj)
{
    ft_8008370C(gobj, ftCo_Landing_Enter_Basic);
}
