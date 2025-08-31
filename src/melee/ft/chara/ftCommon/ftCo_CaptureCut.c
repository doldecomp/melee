#include "ftCo_CaptureCut.h"

#include "ftCo_Throw.h"
#include "placeholder.h"
#include "platform.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

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

void ftCo_CaptureCut_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_800DC920(fp->victim_gobj, gobj);
    if (fp->ground_or_air == GA_Ground) {
        fp->gr_vel = -fp->facing_dir * p_ftCommonData->x370;
    } else {
        fp->self_vel.x = -fp->facing_dir * p_ftCommonData->x370;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureCut, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
}

void ftCo_CaptureCut_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CaptureCut_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureCut_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);

    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007C930(fp, p_ftCommonData->x36C * fp->co_attrs.gr_friction);
        ftCommon_8007CB74(gobj);
        return;
    }

    ft_80084DB0(gobj);
}

void ftCo_CaptureCut_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ft_800841B8(gobj, fn_800DC8D8);
        return;
    }
    ft_80083910(gobj, fn_800DC8FC);
}

void fn_800DC8D8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
}

void fn_800DC8FC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
}

void ftCo_800DC920(Fighter_GObj* gobj0, Fighter_GObj* gobj1)
{
    NOT_IMPLEMENTED;
}

/// #ftCo_800DCE34

/// #ftCo_800DCFD4
