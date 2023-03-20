#include "ftMasterHand_11.h"

#include "ftMasterHand.h"

#include "ft/code_80081B38.h"
#include "ft/ftbosslib.h"

void lbl_8015236C(HSD_GObj* arg0) {}

// 80152370 14EF50
// https://decomp.me/scratch/ehsMv
void lbl_80152370(HSD_GObj* arg0)
{
    Fighter_ActionStateChange_800693AC(arg0, 0x163, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(arg0);
}

// 801523BC 14EF9C
// https://decomp.me/scratch/4nWVy
void lbl_801523BC(HSD_GObj* gobj)
{
    Fighter* r31_fp;
    MasterHandAttributes* r30_attributes;

    if (ftAnim_IsFramesRemaining(gobj))
        return;

    r31_fp = gobj->user_data;
    r30_attributes = r31_fp->x10C_ftData->ext_attr;
    func_8015247C(gobj);
    r31_fp->masterhandVars.x2348 = r30_attributes->xA0;
}

// 80152414 14EFF4
// https://decomp.me/scratch/u6Ii5
void lbl_80152414(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}

// 80152458 14F038
// https://decomp.me/scratch/Oin6U
void lbl_80152458(HSD_GObj* arg0)
{
    func_80085134(arg0);
}

// 80152478 14F058
void lbl_80152478(HSD_GObj* gobj)
{
    return;
}

// 8015247C 14F05C
// https://decomp.me/scratch/uyDVJ
void func_8015247C(HSD_GObj* gobj)
{
    Fighter_ActionStateChange_800693AC(gobj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 801524C8 14F0A8
// https://decomp.me/scratch/zoAeT
void lbl_801524C8(HSD_GObj* gobj)
{
    Fighter* temp_r4 = GET_FIGHTER(gobj);

    if (!--temp_r4->masterhandVars.x2348) {
        func_801525E0(gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter_ActionStateChange_800693AC(gobj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(gobj);
    }
}

// 80152544 14F124
// https://decomp.me/scratch/nlkfy
void lbl_80152544(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        func_8015BD20(gobj);
    }
}

// 80152588 14F168
// https://decomp.me/scratch/2eorR
void lbl_80152588(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftData* r4_ftData = fp->x10C_ftData;
    MasterHandAttributes* r31_attributes = r4_ftData->ext_attr;

    func_80085134(gobj);
    func_8015C010(gobj, r31_attributes->xA4);
    func_8015C190(gobj);
}

// 801525DC 14F1BC
void lbl_801525DC(HSD_GObj* gobj)
{
    return;
}

// 801525E0 14F1C0
// https://decomp.me/scratch/WHp9s
void func_801525E0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x80_self_vel.x = 0.0f;
    Fighter_ActionStateChange_800693AC(gobj, 0x165, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}
