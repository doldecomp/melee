#include "ftcrazyhandbackairplane3.h"

#include <Runtime/platform.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_Throw.h>
#include <melee/ft/kinds/ftCommon/ftCo_Thrown.h>
#include <melee/ft/types.h>
#include "ftcrazyhandtagcancel.h"
#include "ftcrazyhandthrowncrazyhand.h"
#include <melee/ft/kinds/ftMasterHand/types.h>
#include <melee/pl/player.h>

#include <sysdolphin/baselib/forward.h>

void ftCh_Init_80159670(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x171, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->cmd_vars[0] = 0;
}

void ftCh_BackAirplane3_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        ftCh_GrabUnk1_8015B850(fp->victim_gobj, 0x153);
        if (fp->victim_gobj != NULL) {
            HSD_GObj* victim = fp->victim_gobj;
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victim);
            ftCo_800DE7C0(victim, 0, 0);
        }
        fp->mv.ch.unk0.x20 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_BackAirplane3_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_BackAirplane3_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_BackAirplane3_Coll(HSD_GObj* gobj) {}
