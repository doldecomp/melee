#include "ftMh_Squeeze.h"

#include "ftMh_CaptureMasterHand.h"
#include "ftMh_Squeezing.h"
#include "ftMh_Throw.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <dolphin/mtx.h>

void ftMh_MS_378_80154A78(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    fp->cmd_vars[1] = 0;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Squeeze, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->x2222_b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    ftMh_CaptureMasterHand_80155B80(fp->victim_gobj);
    fp->mv.mh.unk0.xC.x = da->x118_pos.x;
    fp->mv.mh.unk0.xC.y = da->x118_pos.y;
    fp->mv.mh.unk0.xC.z = 0;
}

void ftMh_Squeeze_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[1] != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->cmd_vars[1] = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.mh.x2250 == ftMh_MS_Throw) {
            ftMh_MS_376_80154E78(gobj);
        } else {
            ftMh_MS_379_80155014(gobj);
        }
    }
}

void ftMh_Squeeze_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Squeeze_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x2C,
                       da->x28);
}

void ftMh_Squeeze_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.mh.unk0.x18 == 0) {
        fp->self_vel.z = 0;
        fp->self_vel.y = 0;
        fp->self_vel.x = 0;
    }
}
