#include "ftCh_BackDisappear.h"

#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void fn_80159908(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Vec3 pos;
    Fighter_ChangeMotionState(gobj, 0x174, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.x0 = da->xF0;
    ftBossLib_8015C208(gobj, &pos);
    fp->cur_pos.x = pos.x;
    fp->cur_pos.y = da->xEC;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
}

void ftCh_BackDisappear_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0.0f;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}
void ftCh_BackDisappear_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackDisappear_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (--fp->mv.ch.unk0.x0 > 0) {
        ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
        ftBossLib_8015BF74(gobj, da->xDC);
    } else {
        fp->self_vel.x = 0;
    }
}

void ftCh_BackDisappear_Coll(HSD_GObj* gobj) {}
