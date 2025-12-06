#include "ftCo_StopWall.h"

#include "math.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftKirby/ftKb_Init.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 09EE30 */ static void ftCo_8009EE30(Fighter_GObj* gobj);

bool ftCo_8009EDA4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if ((fp->facing_dir == -1 && coll->env_flags & Collide_RightWallHug) ||
        (fp->facing_dir == +1 && coll->env_flags & Collide_LeftWallHug))
    {
        ftCo_DatAttrs* ca = &fp->co_attrs;
        if (ABS(fp->gr_vel) > ca->walk_max_vel) {
            ftCo_8009EE30(gobj);
            return true;
        }
    }
    return false;
}

void ftCo_8009EE30(Fighter_GObj* gobj)
{
    u8 _[4] = { 0 };
    Fighter* fp = gobj->user_data;
    CollData* coll = &fp->coll_data;
    {
        Vec3 vec;
        u8 _[4] = { 0 };
        if (fp->coll_data.env_flags & Collide_RightWallMask) {
            vec.x = coll->ecb.left.x;
            vec.y = coll->ecb.left.y;
            vec.z = 0.0f;
        } else {
            vec.x = coll->ecb.right.x;
            vec.y = coll->ecb.right.y;
            vec.z = 0.0f;
        }
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        Fighter_ChangeMotionState(gobj, ftCo_MS_StopWall, Ft_MF_None, 0, 1, 0,
                                  NULL);
        fp->cur_pos.x = -(fp->x68C_transNPos.z * -fp->facing_dir -
                          (fp->cur_pos.x + vec.x));
    }
    ft_800843FC(gobj);
    ftCommon_8007E2FC(gobj);
}

void ftCo_StopWall_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_StopWall_IASA(Fighter_GObj* gobj) {}

void ftCo_StopWall_Phys(Fighter_GObj* gobj) {}

void ftCo_StopWall_Coll(Fighter_GObj* gobj)
{
    ft_800843FC(gobj);
}
