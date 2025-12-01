#include "ftCo_DownDamage.h"

#include "ftCo_Damage.h"
#include "ftCo_DamageFall.h"
#include "ftCo_DownBound.h"
#include "ftCo_DownStand.h"
#include "ftCo_FlyReflect.h"
#include "ftCo_PassiveWall.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0C31.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/types.h"

#include <common_structs.h>

/* 09F184 */ static void ftCo_8009F184(Fighter_GObj* gobj);

bool ftCo_8009F0F0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if ((fp->motion_id == ftCo_MS_DownBoundU ||
         fp->motion_id == ftCo_MS_DownWaitU ||
         fp->motion_id == ftCo_MS_DownDamageU ||
         fp->motion_id == ftCo_MS_DownBoundD ||
         fp->motion_id == ftCo_MS_DownWaitD ||
         fp->motion_id == ftCo_MS_DownDamageD) &&
        (fp->x2224_b2 || fp->dmg.x1838_percentTemp < p_ftCommonData->x428))
    {
        ftCo_8009F184(gobj);
        return true;
    }
    return false;
}

void ftCo_8009F184(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    FtMotionId msid = fp->motion_id == ftCo_MS_DownWaitU ? ftCo_MS_DownDamageU
                                                         : ftCo_MS_DownDamageD;
    ftCo_8008DCE0(gobj, msid, fp->facing_dir);
    ftCommon_8007E2F4(fp, 1);
}

void ftCo_DownDamage_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2224_b2) {
        fp->mv.co.downdamage.x0 -= 1;
    }
    RETURN_IF(ftAnim_IsFramesRemaining(gobj));
    if (fp->ground_or_air == GA_Air) {
        if (fp->x2224_b2) {
            ftCo_80090780(gobj);
        } else {
            ftCo_Fall_Enter(gobj);
        }
    } else {
        if (fp->mv.co.downdamage.x0 <= 0) {
            ftCo_80098160(gobj, fp->motion_id == ftCo_MS_DownDamageU
                                    ? ftCo_MS_DownStandU
                                    : ftCo_MS_DownStandD);
        } else {
            ftCo_80097F38(gobj);
        }
    }
}

void ftCo_DownDamage_IASA(Fighter_GObj* gobj) {}

void ftCo_DownDamage_Phys(Fighter_GObj* gobj)
{
    ftCo_Damage_Phys(gobj);
}

void ftCo_DownDamage_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        if (ft_80082708(gobj) == GA_Ground) {
            ftCo_8008FC94(gobj);
        } else {
            RETURN_IF(ftCo_800C7CA0(gobj));
        }
    } else {
        if (ft_80081DD4(gobj)) {
            ftCommon_8007D7FC(fp);
        } else {
            CollData* coll = &fp->coll_data;
            if (coll->env_flags & Collide_RightWallHug ||
                coll->env_flags & Collide_LeftWallHug)
            {
                RETURN_IF(ftCo_800C1D38(gobj));
                RETURN_IF(ftCo_800C17CC(gobj));
            }
        }
    }
}
