#include "ftMh_BackCrush_1.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"

#include <baselib/forward.h>

void ftMh_BackCrush_Coll(HSD_GObj* gobj) {}

void ftMh_MS_371_801541C8(HSD_GObj* gobj, HSD_GObjEvent arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_BackDisappear, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x4 = arg1;
}
