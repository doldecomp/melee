#include "ftMh_MS_367.h"

#include "ftMh_MS_368.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"

#include <dolphin/mtx/types.h>

static void doAnim(HSD_GObj* gobj);

void ftMh_MS_367_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        doAnim(gobj);
    }
}

void ftMh_MS_367_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_367_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_367_Coll(HSD_GObj* gobj) {}

static void doAnim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;

    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk368, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);

    {
        Vec3 pos;
        ftBossLib_8015C208(gobj, &pos);
        fp->cur_pos.x = pos.x;
    }

    fp->cur_pos.y = attr->x5C;
    fp->x80_self_vel.x = fp->x80_self_vel.y = fp->x80_self_vel.z = 0;
}

void ftMh_MS_368_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x80_self_vel.x = 0;
        ftMh_MS_368_80153A64(gobj);
    }
}
