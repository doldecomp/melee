#include "ftcrazyhandbackairplane1.h"

#include "ftcrazyhandbackairplane2.h"
#include "ftcrazyhandbackairplane3.h"
#include "ftcrazyhandcapturedamagecrazyhand.h"
#include "types.h"

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/ft/types.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>

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
        if (fp->u.mh.x2250 == 0x170) {
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
