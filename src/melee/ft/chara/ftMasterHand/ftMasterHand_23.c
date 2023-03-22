#include "ftMasterHand_23.h"

#include "ftMasterHand_03.h"
#include "ftMasterHand_25.h"
#include "ftMasterHand_26.h"
#include "ftMasterHand_32.h"

#include "ft/ft_81B.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"

// 80154A78 151658
// https://decomp.me/scratch/ci0xf
void ftMasterHand_80154A78(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMasterHand_SpecialAttrs* attr;

    fp = gobj->user_data;
    attr = fp->ft_data->ext_attr;
    fp->x2204_ftcmd_var1 = 0;
    Fighter_ChangeMotionState(gobj, 0x17A, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    fp->x2222_flag.bits.b2 = 1;
    ftCommon_8007E2F4(fp, 0x1FFU);
    ftCommon_8007E2FC(gobj);
    ftMasterHand_80155B80(fp->x1A58_interactedFighter);
    fp->mv.mh.unk0.xC.x = attr->x118_pos.x;
    fp->mv.mh.unk0.xC.y = attr->x118_pos.y;
    fp->mv.mh.unk0.xC.z = 0.0f;
}

// 80154B2C 15170C
// https://decomp.me/scratch/6WD6p
void ftMasterHand_80154B2C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2204_ftcmd_var1 != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->x2204_ftcmd_var1 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.mh.x2250 == 0x17B)
            ftMasterHand_80154E78(gobj);
        else
            ftMasterHand_80155014(gobj);
    }
}

// 80154BB0 151790
void ftMasterHand_80154BB0(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        ftBossLib_8015BD20(arg0);
}

// 80154BF4 1517D4
// https://decomp.me/scratch/D7Kd4
void ftMasterHand_80154BF4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

// 80154C54 151834
// https://decomp.me/scratch/Pp9nI
void ftMasterHand_80154C54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.mh.unk0.x18 == 0) {
        fp->x80_self_vel.z = 0;
        fp->x80_self_vel.y = 0;
        fp->x80_self_vel.x = 0;
    }
}
