#include "fighter.h"
#include "ft_0CD1.h"
#include "ftswing.h"

#include "ft/chara/ftCommon/ftCo_Fall.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "it/items/itharisen.h"

void ftCo_800CD350(Fighter_GObj* gobj, int arg1, int arg2, float arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800CD140(gobj, arg1, 0, arg2, arg3);
    fp->take_dmg_cb = ft_800CD31C;
}

void ftCo_SwordSwing_Anim(Fighter_GObj* gobj)
{
    ftCo_800CD1BC(gobj);
}

void ftCo_SwordSwing_IASA(Fighter_GObj* gobj)
{
    ftCo_800CD204(gobj);
}

void ftCo_SwordSwing_Phys(Fighter_GObj* gobj)
{
    ftCo_800CD278(gobj);
}

void ftCo_SwordSwing_Coll(Fighter_GObj* gobj)
{
    ftCo_800CD2C4(gobj, ft_800CD31C);
}

void ftCo_800CD418(Fighter_GObj* gobj, int arg1, int arg2, float arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800CD140(gobj, arg1, 0, arg2, arg3);
    fp->take_dmg_cb = ft_800CD31C;
}

void ftCo_BatSwing_Anim(Fighter_GObj* gobj)
{
    ftCo_800CD1BC(gobj);
}

void ftCo_BatSwing_IASA(Fighter_GObj* gobj)
{
    ftCo_800CD204(gobj);
}

void ftCo_BatSwing_Phys(Fighter_GObj* gobj)
{
    ftCo_800CD278(gobj);
}

void ftCo_BatSwing_Coll(Fighter_GObj* gobj)
{
    ftCo_800CD2C4(gobj, ft_800CD31C);
}

void ftCo_800CD4E0(Fighter_GObj* gobj, int arg1, int arg2, float arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800CD140(gobj, arg1, 0x400, arg2, arg3);
    fp->take_dmg_cb = ft_800CD31C;
}

void ftCo_ParasolSwing_Anim(Fighter_GObj* gobj)
{
    ftCo_800CD1BC(gobj);
}

void ftCo_ParasolSwing_IASA(Fighter_GObj* gobj)
{
    ftCo_800CD204(gobj);
}

void ftCo_ParasolSwing_Phys(Fighter_GObj* gobj)
{
    ftCo_800CD278(gobj);
}

void ftCo_ParasolSwing_Coll(Fighter_GObj* gobj)
{
    ftCo_800CD2C4(gobj, ft_800CD31C);
}

void ftCo_800CD5A8(Fighter_GObj* gobj, int arg1, int arg2, float arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->mv.co.swing.x8 = 0.0f;
    ftCo_800CD140(gobj, arg1, 0, arg2, arg3);
    fp->deal_dmg_cb = ft_800CD65C;
    fp->take_dmg_cb = ft_800CD604;
}

void ft_800CD604(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL) {
        it_8029282C(fp->item_gobj);
        it_80292A28(fp->item_gobj);
        ftCommon_8007E7E4(gobj, 1);
    }
}

void ft_800CD65C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL) {
        it_802927E8(fp->item_gobj);
        fp->mv.co.swing.x8 = p_ftCommonData->x5A0;
    }
}

void ftCo_HarisenSwing_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->item_gobj != NULL) {
        if (fp->mv.co.swing.x8 > 0.0f) {
            fp->mv.co.swing.x8 -= 1.0f;
            if (fp->mv.co.swing.x8 <= 0.0f ||
                ftAnim_IsFramesRemaining(gobj) == 0)
            {
                it_8029282C(fp->item_gobj);
            }
        }
        if (fp->cmd_vars[0] == 1) {
            switch (fp->mv.co.swing.x4) {
            case 0:
                it_80292998(fp->item_gobj, fp->frame_speed_mul);
                break;
            case 1:
                it_802929C8(fp->item_gobj, fp->frame_speed_mul);
                break;
            case 2:
            case 3:
                it_802929F8(fp->item_gobj, fp->frame_speed_mul);
                break;
            case 4:
                it_802929C8(fp->item_gobj, fp->frame_speed_mul);
                break;
            }
            fp->cmd_vars[0] = 0;
        }
        if (fp->cmd_vars[0] == 2) {
            it_80292A28(fp->item_gobj);
            fp->cmd_vars[0] = 0;
        }
    }
    ftCo_800CD1BC(gobj);
}

void ftCo_HarisenSwing_IASA(Fighter_GObj* gobj)
{
    ftCo_800CD204(gobj);
}

void ftCo_HarisenSwing_Phys(Fighter_GObj* gobj)
{
    ftCo_800CD278(gobj);
}

void ftCo_HarisenSwing_Coll(Fighter_GObj* gobj)
{
    ftCo_800CD2C4(gobj, ft_800CD604);
}
