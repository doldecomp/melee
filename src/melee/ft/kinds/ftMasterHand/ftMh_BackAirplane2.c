#include "ftMh_BackAirplane2.h"

#include "types.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "pl/player.h"

#include <dolphin/mtx.h>

void ftMh_BackAirplane2_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_BackAirplane2_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ftBossLib_8015BF74(gobj, da->x58);
}

void ftMh_BackAirplane2_Coll(HSD_GObj* gobj) {}

void ftMh_MS_368_80153A64(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_BackAirplane3, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->cur_pos.x = da->x60;
    fp->cur_pos.y = da->x64;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
}
