#include "ftMh_MS_378.h"

#include "ftMh_CaptureMasterHand_1.h"
#include "ftMh_MS_376.h"
#include "ftMh_MS_379.h"
#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"

// 80154A78 151658
// https://decomp.me/scratch/ci0xf
void ftMh_MS_378_80154A78(HSD_GObj* gobj)
{
    Fighter* fp;
    ftMasterHand_SpecialAttrs* attr;

    fp = gobj->user_data;
    attr = fp->x10C_ftData->ext_attr;
    fp->x2204_ftcmd_var1 = 0;
    Fighter_ChangeMotionState(gobj, 0x17A, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    fp->x2222_flag.bits.b2 = 1;
    ftCommon_8007E2F4(fp, 0x1FFU);
    ftCommon_8007E2FC(gobj);
    ftMh_CaptureMasterHand_80155B80(fp->x1A58_interactedFighter);
    fp->sv.mh.unk0.xC.x = attr->x118_pos.x;
    fp->sv.mh.unk0.xC.y = attr->x118_pos.y;
    fp->sv.mh.unk0.xC.z = 0.0f;
}

// 80154B2C 15170C
// https://decomp.me/scratch/6WD6p
void ftMh_MS_378_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2204_ftcmd_var1 != 0) {
        ftBossLib_8015C5F8(gobj);
        fp->x2204_ftcmd_var1 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->ev.mh.x2250 == 0x17B) {
            ftMh_MS_376_80154E78(gobj);
        } else {
            ftMh_MS_379_80155014(gobj);
        }
    }
}

// 80154BB0 151790
void ftMh_MS_378_IASA(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 80154BF4 1517D4
// https://decomp.me/scratch/D7Kd4
void ftMh_MS_378_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->x10C_ftData->ext_attr;
    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->sv.mh.unk0.xC, &fp->sv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

// 80154C54 151834
// https://decomp.me/scratch/Pp9nI
void ftMh_MS_378_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->sv.mh.unk0.x18 == 0) {
        fp->x80_self_vel.z = 0;
        fp->x80_self_vel.y = 0;
        fp->x80_self_vel.x = 0;
    }
}
