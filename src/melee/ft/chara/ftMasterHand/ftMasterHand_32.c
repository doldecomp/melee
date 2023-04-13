#include "ftMasterHand_32.h"

#include "ftMasterHand_22.h"
#include "ftMasterHand_33.h"

#include "ft/ft_0877.h"
#include "ft/ftcommon.h"

// 80155B70 152750
void ftMasterHand_80155B70(HSD_GObj* gobj)
{
    return;
}

// 80155B74 152754
void ftMasterHand_80155B74(HSD_GObj* gobj)
{
    return;
}

// 80155B78 152758
void ftMasterHand_80155B78(HSD_GObj* gobj)
{
    return;
}

// 80155B7C 15275C
void ftMasterHand_80155B7C(HSD_GObj* gobj)
{
    return;
}

// 80155B80 152760
// https://decomp.me/scratch/BFD9X
void ftMasterHand_80155B80(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x148, 0, 0, 0.0f, 1.0f, 0.0f);
    fp->x221E_flag.bits.b0 = 1;
    fp->x2220_flag.bits.b3 = 1;
    fp->cb.x21B0_callback_Accessory1 = &ft_800DB464;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x2220_flag.bits.b3 = 1;
    ftAnim_8006EBA4(gobj);
}

void ftMasterHand_80155C20(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    ftCommon_8007DC08(fp, p_ftCommonData->x3A8);
    if (fp->x1A4C <= 0.0f) {
        ftMasterHand_80155C94(gobj);
        ftMasterHand_8015483C(fp->x1A58_interactedFighter);
    }
}
