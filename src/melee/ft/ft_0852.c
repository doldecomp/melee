#include "ft_0852.h"

#include "ft/inlines.h"
#include "ft/types.h"
#include "ft/forward.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

void ft_8008521C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 pos;

    HSD_JObjGetTranslation(jobj, &pos);
    fp->self_vel.x = pos.x - fp->cur_pos.x;
    fp->self_vel.y = pos.y - fp->cur_pos.y;
    fp->self_vel.z = pos.z - fp->cur_pos.z;
}

void ft_8008549C(void)
{
    int i;
    for (i = 0; i < 33; ++i) {
        ft_8045996C[i] = 0;
    }
}
