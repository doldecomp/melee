#include "ftlipstickswing.h"

#include "ef/efasync.h"
#include "ft/ft_0877.h"
#include "ft/ft_0CD1.h"
#include "ft/inlines.h"

#include "it/forward.h"

#include "it/items/itlipstick.h"
#include "it/items/itstarrod.h"
#include "lb/lb_00B0.h"

#include <baselib/gobj.h>

void ftCo_800CDAB4(Fighter_GObj* gobj, int arg1, int arg2, float arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 540000;
    fp->cmd_vars[1] = 0;
    ftCo_800CD140(gobj, arg1, 0, arg2, arg3);
    fp->accessory4_cb = ft_800CDB9C;
    fp->take_dmg_cb = ft_800CD31C;
}

void ftCo_LipstickSwing_Anim(HSD_GObj* gobj)
{
    ftCo_800CD1BC(gobj);
}

void ftCo_LipstickSwing_IASA(HSD_GObj* gobj)
{
    ftCo_800CD204(gobj);
}

void ftCo_LipstickSwing_Phys(HSD_GObj* gobj)
{
    ftCo_800CD278(gobj);
}

void ftCo_LipstickSwing_Coll(HSD_GObj* gobj)
{
    ftCo_800CD2C4(gobj, ft_800CD31C);
}

void ft_800CDB9C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int y;
    int x = fp->ft_data->x8->x10;
    Vec v2;
    Vec v;
    float f;
    int q;
    HSD_ASSERT(99, itGetKind(fp->item_gobj) == It_Kind_LipStick);
    if (fp->item_gobj != NULL) {
        if (fp->cmd_vars[0] != 540000) {
            if (it_8026B594(fp->item_gobj) == 0) {
                ft_PlaySFX(fp, fp->cmd_vars[0], 127, 64);
            } else {
                ft_PlaySFX(fp, 288, 127, 64);
            }
            fp->cmd_vars[0] = 540000;
        }
        if (fp->throw_flags_b0) {
            fp->throw_flags_b0 = 0;
            y = 1;
        } else {
            y = 0;
        }
        if (y) {
            it_80295748(fp->item_gobj, &v);
            lb_8000B1CC(fp->parts[x].joint, &v, &v2);
            if (it_8026B594(fp->item_gobj) == false) {
                it_80295770(fp->item_gobj, &v2, fp->facing_dir,
                            fp->cmd_vars[1]);
            } else {
                f = 0.0f;
                efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, 1032, NULL,
                              &v2, &f);
            }
        }
    }
}
