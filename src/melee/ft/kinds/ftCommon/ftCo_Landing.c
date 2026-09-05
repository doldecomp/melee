#include "ftCo_Landing.h"

#include "ftCo_AppealS.h"
#include "ftCo_Attack1.h"
#include "ftCo_Attack100.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackLw4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"
#include "ftCo_Dash.h"
#include "ftCo_Guard.h"
#include "ftCo_HammerLanding.h"
#include "ftCo_HammerWait.h"
#include "ftCo_Jump.h"
#include "ftCo_SpecialS.h"
#include "ftCo_SquatWait.h"
#include "ftCo_Turn.h"
#include "ftCo_Walk.h"

#include <placeholder.h>

#include "forward.h"
#include <melee/ft/forward.h>

#include <stdbool.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftPeach/ftpeachspecialhi.h>
#include <melee/ft/types.h>
#include <Runtime/platform.h>

void ftCo_Landing_Enter(Fighter_GObj* gobj, FtMotionId msid,
                        bool allow_interrupt, MotionFlags flags,
                        float anim_start, float anim_speed)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, msid, flags, anim_start, anim_speed, 0.0F,
                              NULL);
    fp->mv.co.landing.allow_interrupt = allow_interrupt;
    switch (fp->kind) {
    case FTKIND_MARIO:
    case FTKIND_DRMARIO:
        fp->u.mr.x2234_tornadoCharge = false;
        fp->u.mr.x2238_isCapeBoost = false;
        break;
    case FTKIND_PEACH:
        fp->u.pe.specialairn_used = false;
        if (allow_interrupt == true) {
            ftPe_8011D598(gobj);
        }
    default:
        break;
    case FTKIND_MARS:
    case FTKIND_EMBLEM:
        fp->u.ms.x222C = 0;
        break;
    case FTKIND_GAMEWATCH:
        fp->u.gw.x2234 = 0;
        break;
    case FTKIND_POPO:
    case FTKIND_NANA:
        fp->u.pp.x224C = 0;
        break;
    case FTKIND_KIRBY:
        fp->u.kb.xCC = false;
        fp->u.kb.xC4 = false;
        fp->u.kb.x64 = false;
        break;
    case FTKIND_MEWTWO:
        fp->u.mt.x223C_isConfusionBoost = false;
        break;
    }
}

void ftCo_Landing_Enter_Basic(Fighter_GObj* gobj)
{
    if (ftCo_800C5240(gobj)) {
        ftCo_HammerLanding_Enter(gobj);
    } else {
        ftCo_Landing_Enter(gobj, ftCo_MS_Landing, true, Ft_MF_None, 0.0F,
                           1.0F);
    }
}

void ftCo_LandingFallSpecial_Enter_Basic(Fighter_GObj* gobj)
{
    if (ftCo_800C5240(gobj)) {
        ftCo_HammerLanding_Enter(gobj);
    } else {
        ftCo_Landing_Enter(gobj, ftCo_MS_LandingFallSpecial, false, Ft_MF_None,
                           0.0F, 1.0F);
    }
}

void ftCo_LandingFallSpecial_Enter(Fighter_GObj* gobj, bool allow_interrupt,
                                   float landing_lag)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCo_800C5240(gobj)) {
        ftCo_HammerLanding_Enter(gobj);
    } else {
        ftCo_Landing_Enter(gobj, ftCo_MS_LandingFallSpecial, allow_interrupt,
                           Ft_MF_None, 0.0F, (0.1F + fp->x2EC) / landing_lag);
    }
}

void ftCo_Landing_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Landing_IASA(Fighter_GObj* gobj)
{
    float* landing_lag;
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    landing_lag = &fp->co_attrs.normal_landing_lag;
    RETURN_IF(fp->cur_anim_frame < *landing_lag);
    RETURN_IF(!fp->mv.co.landing.allow_interrupt);
    RETURN_IF(ftCo_SpecialS_CheckInput(gobj));
    RETURN_IF(ftCo_Attack100_CheckInput(gobj));
    RETURN_IF(ftCo_800D6824(gobj));
    RETURN_IF(ftCo_800D68C0(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw4_CheckInput(gobj));
    RETURN_IF(ftCo_AttackS3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackHi3_CheckInput(gobj));
    RETURN_IF(ftCo_AttackLw3_CheckInput(gobj));
    RETURN_IF(ftCo_Attack1_CheckInput(gobj));
    RETURN_IF(ftCo_80091A4C(gobj));
    RETURN_IF(ftCo_800DE9D8(gobj));
    RETURN_IF(ftCo_Jump_CheckInput(gobj));
    RETURN_IF(ftCo_Dash_CheckInput(gobj));
    RETURN_IF((fp->cur_anim_frame < (fp->frame_speed_mul + *landing_lag)) &&
              ftCo_SquatWait_CheckInput(gobj));
    RETURN_IF(ftCo_Turn_CheckInput(gobj));
    RETURN_IF(ftCo_Walk_CheckInput(gobj));
}

void ftCo_Landing_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_Landing_Coll(Fighter_GObj* gobj)
{
    ft_80084280(gobj);
}
