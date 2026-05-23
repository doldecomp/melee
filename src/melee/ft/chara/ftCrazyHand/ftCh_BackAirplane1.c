#include "ftCh_BackAirplane1.h"

#include "ftCh_Init.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_BackAirplane2.h"
#include "ftCrazyHand/ftCh_BackAirplane3.h"
#include "ftCrazyHand/ftCh_CaptureDamageCrazyHand.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void ftCh_Init_801592D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    fp->cmd_vars[1] = 0;
    Fighter_ChangeMotionState(gobj, 0x16F, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    ftCh_GrabUnk1_8015B670(fp->victim_gobj);
    fp->mv.ch.unk0.xC.x = da->xCC_pos.y;
    fp->mv.ch.unk0.xC.y = da->xD4;
    fp->mv.ch.unk0.xC.z = 0;
}

void ftCh_BackAirplane1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.mh.x2250 == 0x170) {
            ftCh_Init_801594D4(gobj);
        } else {
            ftCh_Init_80159670(gobj);
        }
    }
}

void ftCh_BackAirplane1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackAirplane1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.ch.unk0.xC, &fp->mv.ch.unk0.x18, da->x14,
                       da->x10);
}

void ftCh_BackAirplane1_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ch.unk0.x18 == 0) {
        fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    }
}
