#include "ftMh_CaptureMasterHand.h"

#include "ftMh_CaptureDamageMasterHand.h"
#include "ftMh_BackDisappear.h"

#include "ft/ft_0877.h"
#include "ft/ftcommon.h"

void ftMh_CaptureMasterHand_Anim(HSD_GObj* gobj) {}

void ftMh_CaptureMasterHand_IASA(HSD_GObj* gobj) {}

void ftMh_CaptureMasterHand_Phys(HSD_GObj* gobj) {}

void ftMh_CaptureMasterHand_Coll(HSD_GObj* gobj) {}

void ftMh_CaptureMasterHand_80155B80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageMasterHand, 0, 0, 0,
                              1, 0);
    fp->x221E_flag.bits.b0 = true;
    fp->x2220_flag.bits.b3 = true;
    fp->cb.x21B0_callback_Accessory1 = ft_800DB464;
    ftCommon_8007E2F4(fp, 511);
    fp->x2220_flag.bits.b3 = true;
    ftAnim_8006EBA4(gobj);
}

void ftMh_CaptureDamageMasterHand_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DC08(fp, p_ftCommonData->x3A8);
    if (fp->x1A4C <= 0) {
        ftMh_CaptureDamageMasterHand_80155C94(gobj);
        ftMh_MS_381_8015483C(fp->x1A58_interactedFighter);
    }
}
