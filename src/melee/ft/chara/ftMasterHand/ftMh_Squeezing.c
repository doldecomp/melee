#include "ftMh_Squeezing.h"

#include "ftMh_BackDisappear.h"
#include "ftMh_Squeeze.h"
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
#include "ftMasterHand/types.h"
#include "pl/player.h"

void ftMh_Squeezing_Anim(HSD_GObj* gobj)
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

void ftMh_Squeezing_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Squeezing_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;

    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x2C,
                       da->x28);
}

void ftMh_Squeezing_Coll(HSD_GObj* gobj) {}

void ftMh_MS_376_80154E78(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_Throw, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->cmd_vars[0] = 0;
}

void ftMh_Throw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        ftMh_CaptureWaitMasterHand_80155D6C(fp->victim_gobj,
                                            ftCo_MS_ThrownMasterHand);
        if (fp->victim_gobj != 0) {
            HSD_GObj* victim = fp->victim_gobj;
            Fighter* victim_fp = GET_FIGHTER(victim);
            ftCommon_8007E2F4(fp, 0);
            ftCo_800DE2A8(gobj, victim);
            victim_fp->dmg.facing_dir_1 *= -1;
            ftCo_800DE7C0(victim, 0, 0);
        }
        fp->mv.mh.unk0.x20 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}
