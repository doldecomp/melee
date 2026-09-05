#include "ftmasterhandslam.h"

#include "ftmasterhandthrownmasterhand.h"
#include "ftmasterhandwait12.h"
#include "types.h"

#include <melee/ft/kinds/ftCommon/forward.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_Throw.h>
#include <melee/ft/kinds/ftCommon/ftCo_Thrown.h>
#include <melee/ft/kinds/ftCrazyHand/ftcrazyhandsqueezing1.h>
#include <melee/ft/types.h>
#include <melee/pl/player.h>
#include <Runtime/platform.h>

void ftMh_Slam_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[8];
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        ftMh_CaptureWaitMasterHand_80155D6C(fp->victim_gobj,
                                            ftCo_MS_ThrownMasterHand);
        if (fp->victim_gobj != NULL) {
            HSD_GObj* victim = fp->victim_gobj;
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victim);
            ftCo_800DE7C0(victim, 0, 0);
        }
        fp->mv.mh.unk0.x20 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_Slam_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Slam_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_Slam_Coll(HSD_GObj* gobj) {}

void ftMh_MS_380_80155194(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* gobj1 = ftBossLib_8015C3E8(FTKIND_CREZYH);
    if (!ftBossLib_8015C31C()) {
        ftCh_Init_8015A2B0(gobj1);
    }
    fp->x1A5C = gobj1;
    Fighter_ChangeMotionState(gobj, ftMh_MS_TagCrush, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}
