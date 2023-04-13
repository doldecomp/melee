#include "ftMasterHand_25.h"

#include "ftMasterHand_03.h"
#include "ftMasterHand_22.h"
#include "ftMasterHand_23.h"
#include "ftMasterHand_34.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"

// 80154D78 151958
// https://decomp.me/scratch/DzZiN
void ftMasterHand_80154D78(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp->sv.mh.unk0.x20 == 1) {
            ftMasterHand_80154A78(gobj);
        } else {
            ftMasterHand_801546D8(gobj);
        }
    }
}

// 80154DD0 1519B0
// https://decomp.me/scratch/5olg2
void ftMasterHand_80154DD0(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 80154E14 1519F4
// https://decomp.me/scratch/2yMnG
void ftMasterHand_80154E14(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attr = fp->x10C_ftData->ext_attr;

    ft_80085134(gobj);
    ftBossLib_8015BE40(gobj, &fp->sv.mh.unk0.xC, &fp->sv.mh.unk0.x18,
                       attr->x2C, attr->x28);
}

// 80154E74 151A54
// https://decomp.me/scratch/0wwnm
void ftMasterHand_80154E74(HSD_GObj* gobj)
{
    return;
}

// 80154E78 151A58
// https://decomp.me/scratch/lmtfb
void ftMasterHand_80154E78(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x17B, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    fp->x2200_ftcmd_var0 = 0;
}

// 80154ED8 151AB8
// https://decomp.me/scratch/6H8xW
void ftMasterHand_80154ED8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        ftMasterHand_80155D6C(fp->x1A58_interactedFighter, 0x14A);
        if (fp->x1A58_interactedFighter != 0) {
            HSD_GObj* victim = fp->x1A58_interactedFighter;
            Fighter* victim_fp = GET_FIGHTER(victim);
            ftCommon_8007E2F4(fp, 0);
            ft_800DE2A8(gobj, victim);
            victim_fp->dmg.x1844_direction *= -1.0f;
            ft_800DE7C0(victim, 0, 0);
        }
        fp->sv.mh.unk0.x20 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMasterHand_80151018(gobj);
    }
}
