#include "ftMh_MS_376.h"

#include "ftMh_CaptureWaitMasterHand.h"
#include "ftMh_MS_372.h"
#include "ftMh_MS_378.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftMh_MS_376_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp->mv.mh.unk0.x20 == 1) {
            ftMh_MS_378_80154A78(gobj);
        } else {
            ftMh_MS_374_801546D8(gobj);
        }
    }
}

void ftMh_MS_376_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_376_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;

    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

void ftMh_MS_376_Coll(HSD_GObj* gobj) {}

void ftMh_MS_376_80154E78(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Throw, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->x2200_ftcmd_var0 = 0;
}

void ftMh_MS_379_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        ftMh_CaptureWaitMasterHand_80155D6C(fp->x1A58_interactedFighter,
                                            ftCo_MS_ThrownMasterHand);
        if (fp->x1A58_interactedFighter != 0) {
            HSD_GObj* victim = fp->x1A58_interactedFighter;
            Fighter* victim_fp = GET_FIGHTER(victim);
            ftCommon_8007E2F4(fp, 0);
            ft_800DE2A8(gobj, victim);
            victim_fp->dmg.x1844_direction *= -1;
            ft_800DE7C0(victim, 0, 0);
        }
        fp->mv.mh.unk0.x20 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}
