#include "ftMh_MS_378.h"

#include "ftMh_CaptureMasterHand_1.h"
#include "ftMh_MS_376.h"
#include "ftMh_MS_379.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

void ftMh_MS_378_80154A78(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    fp->x2204_ftcmd_var1 = 0;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Unk378, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->x2222_flag.bits.b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    ftMh_CaptureMasterHand_80155B80(fp->x1A58_interactedFighter);
    fp->mv.mh.unk0.xC.x = attr->x118_pos.x;
    fp->mv.mh.unk0.xC.y = attr->x118_pos.y;
    fp->mv.mh.unk0.xC.z = 0;
}

void ftMh_MS_378_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2204_ftcmd_var1 != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->x2204_ftcmd_var1 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.mh.x2250 == ftMh_MS_Grab_Unk0_MotionStart) {
            ftMh_MS_376_80154E78(gobj);
        } else {
            ftMh_MS_379_80155014(gobj);
        }
    }
}

void ftMh_MS_378_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_378_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

void ftMh_MS_378_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.mh.unk0.x18 == 0) {
        fp->x80_self_vel.z = 0;
        fp->x80_self_vel.y = 0;
        fp->x80_self_vel.x = 0;
    }
}
