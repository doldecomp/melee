#include "ftCo_Landing.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_AppealS.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftCo_AttackHi3.h"
#include "ftCommon/ftCo_AttackHi4.h"
#include "ftCommon/ftCo_AttackLw3.h"
#include "ftCommon/ftCo_AttackLw4.h"
#include "ftCommon/ftCo_AttackS3.h"
#include "ftCommon/ftCo_AttackS4.h"
#include "ftCommon/ftCo_Dash.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_HammerLanding.h"
#include "ftCommon/ftCo_HammerWait.h"
#include "ftCommon/ftCo_Jump.h"
#include "ftCommon/ftCo_SpecialS.h"
#include "ftCommon/ftCo_Squat.h"
#include "ftCommon/ftCo_SquatWait.h"
#include "ftCommon/ftCo_Turn.h"
#include "ftCommon/ftCo_Walk.h"
#include "ftPeach/ftPe_SpecialHi.h"

#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

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
        fp->fv.mr.x2234_tornadoCharge = false;
        fp->fv.mr.x2238_isCapeBoost = false;
        break;
    case FTKIND_PEACH:
        fp->fv.pe.specialairn_used = false;
        if (allow_interrupt == true) {
            ftPe_8011D598(gobj);
        }
    default:
        break;
    case FTKIND_MARS:
    case FTKIND_EMBLEM:
        fp->fv.ms.x222C = 0;
        break;
    case FTKIND_GAMEWATCH:
        fp->fv.gw.x2234 = 0;
        break;
    case FTKIND_POPO:
    case FTKIND_NANA:
        fp->fv.pp.x224C = 0;
        break;
    case FTKIND_KIRBY:
        fp->fv.kb.xCC = false;
        fp->fv.kb.xC4 = false;
        fp->fv.kb.x64 = false;
        break;
    case FTKIND_MEWTWO:
        fp->fv.mt.x223C_isConfusionBoost = false;
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
