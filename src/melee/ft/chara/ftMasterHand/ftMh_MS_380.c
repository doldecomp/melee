#include "ftMh_MS_380.h"

#include "ftMh_CaptureWaitMasterHand.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ftCrazyHand/ftCh_Init.h"

void ftMh_Slam_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        ftMh_CaptureWaitMasterHand_80155D6C(fp->x1A58_interactedFighter,
                                            ftCo_MS_ThrownMasterHand);
        if (fp->x1A58_interactedFighter != NULL) {
            HSD_GObj* victim = fp->x1A58_interactedFighter;
            ftCommon_8007E2F4(fp, 0);
            ft_800DE2A8(gobj, victim);
            ft_800DE7C0(victim, 0, 0);
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
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
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
    Fighter_ChangeMotionState(gobj, ftMh_MS_TagCrush, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
}
