#include "ftMasterHand_25.h"

#include "ftMasterHand_03.h"
#include "ftMasterHand_22.h"
#include "ftMasterHand_23.h"
#include "ftMasterHand_34.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftbosslib.h"
#include "ft/ftcommon.h"

// 80154D78 151958
// https://decomp.me/scratch/DzZiN
void lbl_80154D78(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp->mv.mh.unk0.x20 == 1)
            func_80154A78(gobj);
        else
            func_801546D8(gobj);
    }
}

// 80154DD0 1519B0
// https://decomp.me/scratch/5olg2
void lbl_80154DD0(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(arg0);
}

// 80154E14 1519F4
// https://decomp.me/scratch/2yMnG
void lbl_80154E14(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;

    func_80085134(gobj);
    func_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, attr->x2C,
                  attr->x28);
}

// 80154E74 151A54
// https://decomp.me/scratch/0wwnm
void lbl_80154E74(HSD_GObj* gobj)
{
    return;
}

// 80154E78 151A58
// https://decomp.me/scratch/lmtfb
void func_80154E78(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 0x17B, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp->x2200_ftcmd_var0 = 0;
}

// 80154ED8 151AB8
// https://decomp.me/scratch/6H8xW
void lbl_80154ED8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 != 0) {
        fp->x2200_ftcmd_var0 = 0;
        func_80155D6C(fp->x1A58_interactedFighter, 0x14A);
        if (fp->x1A58_interactedFighter != 0) {
            HSD_GObj* victim = fp->x1A58_interactedFighter;
            Fighter* victim_fp = GET_FIGHTER(victim);
            func_8007E2F4(fp, 0);
            func_800DE2A8(gobj, victim);
            victim_fp->dmg.x1844_direction *= -1.0f;
            func_800DE7C0(victim, 0, 0);
        }
        fp->mv.mh.unk0.x20 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_80151018(gobj);
    }
}
