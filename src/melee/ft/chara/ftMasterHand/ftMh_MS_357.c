#include "ftMh_MS_357.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"

// 80152634 14F214
// https://decomp.me/scratch/ZAr9B
void ftMh_MS_357_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_389_80151018(arg0);
    }
}

// 80152670 14F250
// https://decomp.me/scratch/8k9M0
void ftMh_MS_357_IASA(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 801526B4 14F294
// https://decomp.me/scratch/SGiGG
void ftMh_MS_357_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

// 801526D4 14F2B4
void ftMh_MS_357_Coll(HSD_GObj* gobj)
{
    return;
}

// 801526D8 14F2B8
// https://decomp.me/scratch/woLuT
void ftMh_MS_357_801526D8(HSD_GObj* arg0)
{
    Fighter* temp_r31;

    temp_r31 = arg0->user_data;
    Fighter_ChangeMotionState(arg0, 0x166, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
    temp_r31->mv.mh.unk0.x0 = 0.0f;
}

// 80152738 14F318
// https://decomp.me/scratch/JppLT
void ftMh_MS_358_Anim(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        ftMh_MS_389_80151018(arg0);
    }
}

// 80152774 14F354
// https://decomp.me/scratch/FCaLx
void ftMh_MS_358_IASA(HSD_GObj* arg0)
{
    Fighter* fp = arg0->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(arg0);
    }
}

// 801527B8 14F398
// https://decomp.me/scratch/lzl13
void ftMh_MS_358_Phys(HSD_GObj* gobj)
{
    Fighter* r31_fp;
    ftMasterHand_SpecialAttrs* r30_attributes;
    f32 tmp;

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->ft_data->ext_attr;

    ft_80085134(gobj);

    tmp = ++r31_fp->mv.mh.unk0.x0;
    if (tmp > r30_attributes->xB0 &&
        r31_fp->mv.mh.unk0.x0 < r30_attributes->xB4)
    {
        ftBossLib_8015C010(gobj, r30_attributes->xB8);
    } else {
        r31_fp->x80_self_vel.x = 0.0f;
    }
    ftBossLib_8015C190(gobj);
}
