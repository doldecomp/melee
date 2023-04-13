#include "ftMasterHand_21.h"

#include "ft/fighter.h"
#include "ft/inlines.h"

// 801541C4 150DA4
void ftMasterHand_801541C4(HSD_GObj* gobj) {}

// 801541C8 150DA8
// https://decomp.me/scratch/WhlXG
void ftMasterHand_801541C8(HSD_GObj* gobj, void* arg1)
{
    Fighter* r31_fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x174, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    r31_fp->sv.mh.unk0.x4 = arg1;
}
