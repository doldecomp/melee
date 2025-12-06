#include "ftCo_StopCeil.h"

#include "ftCo_FallSpecial.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftKirby/ftKb_Init.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 09CAD4 */ static void ftCo_8009EFA4(Fighter_GObj* gobj);

bool ftCo_8009EF68(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->coll_data.env_flags & Collide_CeilingHug) {
        ftCo_8009EFA4(gobj);
        return true;
    }
    return false;
}

void ftCo_8009EFA4(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->throw_flags = 0;
    {
        Vec3 vec;
        vec.x = 0;
        vec.y = fp->coll_data.ecb.top.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        Fighter_ChangeMotionState(gobj, ftCo_MS_StopCeil, Ft_MF_None, 0, 1, 0,
                                  NULL);
        {
            float pos_y = fp->cur_pos.y;
            float transn_y = fp->x68C_transNPos.y;
            fp->cur_pos.y = transn_y + (pos_y + vec.y);
            ft_80082D40(gobj, pos_y);
            fp->self_vel.y = fp->self_vel.z = 0;
        }
    }
}

void ftCo_StopCeil_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCheckThrowB3(fp) || !ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_StopCeil_IASA(Fighter_GObj* gobj) {}

void ftCo_StopCeil_Phys(Fighter_GObj* gobj) {}

void ftCo_StopCeil_Coll(Fighter_GObj* gobj)
{
    ft_80083464(gobj, ftCo_80096CC8, ft_80082B1C);
}
