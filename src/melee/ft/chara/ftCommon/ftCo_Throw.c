#include "ftCo_Throw.h"

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

#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Throw.h"

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

/// #ftCo_800DD100

/// #ftCo_800DD168

/// #ftCo_800DD1E4

/// #ftCo_800DD398

/// #ftCo_800DD4B0

/// #fn_800DD568

/// #fn_800DD5EC

/// #fn_800DD684

/// #fn_800DD6E4

/// #ftCo_800DD724

/// #ftCo_ThrowF_Anim

void ftCo_ThrowF_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ThrowF_Phys

/// #ftCo_ThrowF_Coll

/// #ftCo_ThrowB_Anim

void ftCo_ThrowB_IASA(Fighter_GObj* gobj) {}

void ftCo_ThrowB_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Air) {
        if (fp->mv.co.fighterthrow.x4 != 0) {
            fp->self_vel.x =
                fp->mv.co.fighterthrow.self_vel_x * fp->facing_dir;
            fp->self_vel.y = fp->mv.co.fighterthrow.self_vel_y;
        } else {
            ft_80085134(gobj);
        }
    } else {
        ft_80085004(gobj);
    }
}

/// #ftCo_ThrowB_Coll

/// #ftCo_ThrowHi_Anim

void ftCo_ThrowHi_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ThrowHi_Phys

/// #ftCo_ThrowHi_Coll

/// #ftCo_ThrowHi_Cam

/// #ftCo_ThrowLw_Anim

void ftCo_ThrowLw_IASA(Fighter_GObj* gobj) {}

/// #ftCo_ThrowLw_Phys

/// #ftCo_ThrowLw_Coll

/// #ftCo_800DDDE4

/// #ftCo_800DE2A8

/// #ftCo_800DE2CC

/// #ftCo_800DE2F0
