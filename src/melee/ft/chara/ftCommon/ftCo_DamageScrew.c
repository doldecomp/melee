#include "ftCo_DamageScrew.h"

#include "platform.h"
#include "stdbool.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureCut.h"
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

bool ftCo_800D2FA4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->dmg.x1860_element == 0xE) {
        int x = fp->x2070.x2071_b0_3;
        switch (x) {
        case 11:
        case 12:
            return 0;
        }
        ftCo_800D3004(gobj);
        return 1;
    }
    return 0;
}

void ftCo_800D3004(Fighter_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->cmd_vars[0] = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCo_MS_DamageScrew, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_DamageScrewAir, 0, 0.0F, 1.0F,
                                  0.0F, NULL);
    }
    fp->self_vel.x = 0.0F;
    fp->self_vel.y = fp->co_attrs.x140;
    fp->self_vel.z = 0.0F;
}

void ftCo_DamageScrew_Anim(Fighter_GObj* gobj)
{
    u8 _[8];
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800968C8(gobj);
    }
}

void ftCo_DamageScrew_IASA(Fighter_GObj* gobj) {}

void ftCo_DamageScrew_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_DamageScrew_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->cmd_vars[0]) {
        ftCo_AirCatchHit_Coll(gobj);
        return;
    }
    ft_80083B68(gobj);
}
