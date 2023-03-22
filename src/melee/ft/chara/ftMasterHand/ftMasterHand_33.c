#include "ftMasterHand/ftMasterHand_33.h"

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"

// 80155C88 152868
void ftMasterHand_80155C88(HSD_GObj* gobj)
{
    return;
}

// 80155C8C 15286C
void ftMasterHand_80155C8C(HSD_GObj* gobj)
{
    return;
}

// 80155C90 152870
void ftMasterHand_80155C90(HSD_GObj* gobj)
{
    return;
}

// 80155C94 152874
// https://decomp.me/scratch/8Kpd7
void ftMasterHand_80155C94(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x149, 0, 0, 0.0f, 1.0f, 0.0f);
    fp->x221E_flag.bits.b0 = true;
    func_8007E2F4(fp, 0x1FF);
    fp->x2220_flag.bits.b3 = true;
    ftAnim_8006EBA4(gobj);
}
