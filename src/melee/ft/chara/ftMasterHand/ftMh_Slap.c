#include "ftMh_Slap.h"

#include "ftMh_Wait1_2.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"

#include "ftMasterHand/forward.h"

#include "pl/player.h"

#include <dolphin/mtx.h>

void ftMh_Slap_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_Slap_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Slap_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_Slap_Coll(HSD_GObj* gobj) {}

void ftMh_MS_349_80151CA8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_WalkShoot, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);

    /// @todo The code matches, but is this right?
    fp->cur_pos.y = da->x50.x;

    fp->self_vel.x = 0;
}
