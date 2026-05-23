#include "ftCh_Cancel.h"

#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_Squeezing_0.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_Init_8015A030(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x177, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    {
        Vec3 pos;
        ftBossLib_8015C208(gobj, &pos);
        fp->cur_pos.x = pos.x;
    }
    fp->cur_pos.y = da->xE0;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
}

void ftCh_Cancel_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0.0f;
        ftCh_Init_8015A184(gobj);
    }
}
void ftCh_Cancel_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Cancel_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ftBossLib_8015BF74(gobj, da->xDC);
}

void ftCh_Cancel_Coll(HSD_GObj* gobj) {}
