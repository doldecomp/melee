#include "ftCh_BackAirplane3.h"

#include "ftCh_Init.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Thrown.h"
#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "ftCrazyHand/ftCh_ThrownCrazyHand.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

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
