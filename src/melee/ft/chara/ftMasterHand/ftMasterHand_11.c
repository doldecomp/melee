#include "ftMasterHand_11.h"

#include "ft/ft_81B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"

void ftMasterHand_8015236C(HSD_GObj* arg0) {}

// 80152370 14EF50
// https://decomp.me/scratch/ehsMv
void ftMasterHand_80152370(HSD_GObj* arg0)
{
    Fighter_ChangeMotionState(arg0, 0x163, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(arg0);
}

// 801523BC 14EF9C
// https://decomp.me/scratch/4nWVy
void ftMasterHand_801523BC(HSD_GObj* gobj)
{
    Fighter* r31_fp;
    ftMasterHand_SpecialAttrs* r30_attributes;

    if (ftAnim_IsFramesRemaining(gobj))
        return;

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->ft_data->ext_attr;
    ftMasterHand_8015247C(gobj);
    r31_fp->mv.mh.unk0.x8 = r30_attributes->xA0;
}

// 80152414 14EFF4
// https://decomp.me/scratch/u6Ii5
void ftMasterHand_80152414(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}

// 80152458 14F038
// https://decomp.me/scratch/Oin6U
void ftMasterHand_80152458(HSD_GObj* arg0)
{
    ft_80085134(arg0);
}

// 80152478 14F058
void ftMasterHand_80152478(HSD_GObj* gobj)
{
    return;
}

// 8015247C 14F05C
// https://decomp.me/scratch/uyDVJ
void ftMasterHand_8015247C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}

// 801524C8 14F0A8
// https://decomp.me/scratch/zoAeT
void ftMasterHand_801524C8(HSD_GObj* gobj)
{
    Fighter* temp_r4 = GET_FIGHTER(gobj);

    if (!--temp_r4->mv.mh.unk0.x8) {
        ftMasterHand_801525E0(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ChangeMotionState(gobj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
        ftAnim_8006EBA4(gobj);
    }
}

// 80152544 14F124
// https://decomp.me/scratch/nlkfy
void ftMasterHand_80152544(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}

// 80152588 14F168
// https://decomp.me/scratch/2eorR
void ftMasterHand_80152588(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* r4_ftData = fp->ft_data;
    ftMasterHand_SpecialAttrs* r31_attributes = r4_ftData->ext_attr;

    ft_80085134(gobj);
    func_8015C010(gobj, r31_attributes->xA4);
    func_8015C190(gobj);
}

// 801525DC 14F1BC
void ftMasterHand_801525DC(HSD_GObj* gobj)
{
    return;
}

// 801525E0 14F1C0
// https://decomp.me/scratch/WHp9s
void ftMasterHand_801525E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x80_self_vel.x = 0.0f;
    Fighter_ChangeMotionState(gobj, 0x165, 0, 0, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
}
