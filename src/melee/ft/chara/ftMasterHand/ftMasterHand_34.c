#include "ftMasterHand_34.h"

#include "ft/ft_0877.h"
#include "ft/ftcommon.h"

// 80155D1C 1528FC
// https://decomp.me/scratch/YDeLe
void ftMasterHand_80155D1C(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    fp->x221E_flag.bits.b0 = 0;
    fp->facing_dir = -fp->facing_dir;
    ft_800DC750(gobj);
}

// 80155D5C 15293C
void ftMasterHand_80155D5C(HSD_GObj* gobj)
{
    return;
}

// 80155D60 152940
void ftMasterHand_80155D60(HSD_GObj* gobj)
{
    return;
}

// 80155D64 152944
void ftMasterHand_80155D64(HSD_GObj* gobj)
{
    return;
}

// 80155D68 152948
void ftMasterHand_80155D68(HSD_GObj* gobj)
{
    return;
}

// 80155D6C 15294C
// https://decomp.me/scratch/y3wmm
void ftMasterHand_80155D6C(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(fp->x1A58_interactedFighter);

    fp->facing_dir = victim_fp->facing_dir;
    fp->sv.mh.unk4.x0 = 0;
    Fighter_ChangeMotionState(gobj, 0x14A, 0, 0, 0.0f, 1.0f, 0.0f);
    fp->x221E_flag.bits.b0 = 0;
    fp->cb.x21B0_callback_Accessory1 = &ft_800DE508;
    ftCommon_8007E2F4(fp, 0x1FFU);
    ftAnim_8006EBA4(gobj);
}

// 80155E08 1529E8
void ftMasterHand_80155E08(HSD_GObj* gobj)
{
    return;
}

// 80155E0C 1529EC
void ftMasterHand_80155E0C(HSD_GObj* gobj)
{
    return;
}

// 80155E10 1529F0
void ftMasterHand_80155E10(HSD_GObj* gobj)
{
    return;
}

// 80155E14 1529F4
void ftMasterHand_80155E14(HSD_GObj* gobj)
{
    return;
}
