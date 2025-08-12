#include "ftMh_BackAirplane1.h"

#include "ftMh_BackAirplane2.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"

#include "ftMasterHand/forward.h"

#include "pl/player.h"

#include <dolphin/mtx.h>

static void doAnim(HSD_GObj* gobj);

void ftMh_BackAirplane1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        doAnim(gobj);
    }
}

void ftMh_BackAirplane1_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_BackAirplane1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_BackAirplane1_Coll(HSD_GObj* gobj) {}

static void doAnim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;

    Fighter_ChangeMotionState(gobj, ftMh_MS_BackAirplane2, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);

    {
        Vec3 pos;
        ftBossLib_8015C208(gobj, &pos);
        fp->cur_pos.x = pos.x;
    }

    fp->cur_pos.y = da->x5C;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
}

void ftMh_BackAirplane2_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0;
        ftMh_MS_368_80153A64(gobj);
    }
}
