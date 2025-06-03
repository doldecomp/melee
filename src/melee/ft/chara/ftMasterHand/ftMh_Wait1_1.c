#include "ftMh_Wait1_1.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"

#include <dolphin/mtx.h>

void ftMh_MS_375_80154C78(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Squeezing0, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.xC.x = da->x118_pos.x;
    fp->mv.mh.unk0.xC.y = da->x118_pos.y;
    fp->mv.mh.unk0.xC.z = 0;
}

void ftMh_MS_378_80154CF8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, ftMh_MS_Squeezing1, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.xC.x = da->x30_pos2.x;
    fp->mv.mh.unk0.xC.y = da->x30_pos2.y;
    fp->mv.mh.unk0.xC.z = 0;
}
