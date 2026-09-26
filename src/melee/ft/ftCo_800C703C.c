#include "ftCo_800C703C.h"

#include "fighter.h"
#include "types.h"

void ftCo_800C703C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->xA4_unk_vel.x = fp->self_vel.x;
    fp->xA4_unk_vel.y = p_ftCommonData->x6D0;
    fp->xA4_unk_vel.z = 0;
    fp->dmg.x1948 = fp->dmg.x194C = p_ftCommonData->x6CC;
}
