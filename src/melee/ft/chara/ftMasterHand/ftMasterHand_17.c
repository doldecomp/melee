#include "ftMasterHand_17.h"

#include "ftMasterHand_18.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"

#include <dolphin/mtx/types.h>

static void doAnim(HSD_GObj*);

// 8015386C 15044C
// https://decomp.me/scratch/dCvLa
void ftMh_MS_367_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        doAnim(arg0);
    }
}

// 801538A8 150488
void ftMh_MS_367_IASA(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 801538EC 1504CC
void ftMh_MS_367_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 8015390C 1504EC
void ftMh_MS_367_Coll(HSD_GObj* gobj)
{
    return;
}

// 80153910 1504F0
// https://decomp.me/scratch/AYDbj
static void doAnim(HSD_GObj* arg0)
{
    Fighter* fp = GET_FIGHTER(arg0);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    Vec3 sp10;

    Fighter_ChangeMotionState(arg0, 0x170, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
    ftBossLib_8015C208(arg0, &sp10);
    fp->cur_pos.x = sp10.x;
    fp->cur_pos.y = attr->x5C;
    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
}

// 801539A4 150584
// https://decomp.me/scratch/DVyVs
void ftMh_MS_368_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        Fighter* temp_r4 = GET_FIGHTER(arg0);
        temp_r4->x80_self_vel.x = 0.0f;
        ftMh_MS_368_80153A64(arg0);
    }
}
