#include "ftMasterHand_10.h"

#include "ftMasterHand_03.h"
#include "ftMasterHand_09.h"

#include "ft/code_80081B38.h"
#include "ft/ftbosslib.h"

// 80152138 14ED18
// https://decomp.me/scratch/NAMEj
void lbl_80152138(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        func_80151018(arg0);
    }
}

// 80152174 14ED54
// https://decomp.me/scratch/6NWxd
void lbl_80152174(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0)
        func_8015BD20(gobj);
}

// 801521B8 14ED98
// https://decomp.me/scratch/yyAcs
void lbl_801521B8(HSD_GObj* gobj)
{
    func_80085134(gobj);
}

void lbl_801521D8(HSD_GObj* arg0) {}

// 801521DC 14EDBC
// https://decomp.me/scratch/0Dq4d
void lbl_801521DC(HSD_GObj* arg0)
{
    Fighter* temp_r31 = GET_FIGHTER(arg0);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ChangeMotionState(arg0, 0x162, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
    temp_r31->mv.mh.unk0.x0 = 107.0f;
}

// 8015223C 14EE1C
// https://decomp.me/scratch/sZYJl
void lbl_8015223C(HSD_GObj* arg0)
{
    if (!ftAnim_IsFramesRemaining(arg0)) {
        func_80151018(arg0);
    }
}

// 80152278 14EE58
// https://decomp.me/scratch/KNhTn
void lbl_80152278(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}

// 801522BC 14EE9C
// https://decomp.me/scratch/hAUig
void lbl_801522BC(HSD_GObj* gobj)
{
    Fighter* r31_fp;
    ftData* r4_ftData;
    ftMasterHand_SpecialAttrs* r30_attributes;

    r31_fp = gobj->user_data;
    r4_ftData = r31_fp->ft_data;
    r30_attributes = r4_ftData->ext_attr;
    func_80085134(gobj);

    if ((--r31_fp->mv.mh.unk0.x0 > r30_attributes->x84) ||
        (r31_fp->mv.mh.unk0.x0 < 0.0f))
    {
        r31_fp->x80_self_vel.x = 0.0f;
    } else {
        func_8015C010(gobj, r30_attributes->x80);
    }
    func_8015C190(gobj);
}
