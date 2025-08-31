#include "ftMh_Slam.h"

#include "ftMh_ThrownMasterHand.h"
#include "ftMh_Wait1_2.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Thrown.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

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
    HSD_GObj* gobj1 = ftBossLib_8015C3E8(28);
    if (!ftBossLib_8015C31C()) {
        ftCh_Init_8015A2B0(gobj1);
    }
    fp->x1A5C = gobj1;
    Fighter_ChangeMotionState(gobj, ftMh_MS_TagCrush, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}
