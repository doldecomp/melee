#include "ftcliffcommon.h"
#include "variables.h"
#include <dolphin/types.h>

BOOL func_80081298(HSD_GObj* gobj) {
    Fighter* other_fighter;
    HSD_GObj* other_gobj;
    s32 unused1, unused2;

    Fighter* fighter = gobj->user_data;
    if (fighter->input.x624_lstick_y <= -p_ftCommonData->x480) {
        return FALSE;
    }
    if (((fighter->x6F0_collData.x134_envFlags & 0x03000000) != 0)
        && (((fighter->x2228_flag.bits.b2 & 1) == 0))) {
        other_gobj = func_80082E3C(gobj);
        if (other_gobj == NULL) {
            func_80040048(fighter->xC_playerID, fighter->x221F_flag.bits.b4);
            func_80081370(gobj);
            return TRUE;
        }
        other_fighter = other_gobj->user_data;
        func_8003FFDC(other_fighter->xC_playerID, other_fighter->x221F_flag.bits.b4, fighter->xC_playerID, fighter->x221F_flag.bits.b4, other_fighter->x2340_stateVar1);
        fighter->x213C = other_fighter->x2340_stateVar1;
        return FALSE;
    }
    return FALSE;
}

typedef struct _UnkParameterStruct {
    u8 data_filler_0[0x10];
    f32 x10[2];
    u8 data_filler_1[0x1];
} UnkParameterStruct;

void func_80081370(HSD_GObj* gobj) {
    f32 facingDirection;
    f32 ledgeDirection;

    Fighter* fighter = gobj->user_data;
    UnkParameterStruct unkParam;

    if ((fighter->x6F0_collData.x134_envFlags & 0x01000000) != 0) {
        ledgeDirection = 1.0f;
    } else {
        ledgeDirection = -1.0f;
    }
    facingDirection = fighter->x2C_facing_direction;
    if (facingDirection != ledgeDirection) {
        fighter->x2C_facing_direction = -facingDirection;
    }
    func_8007D780(fighter);
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(gobj, 0xFC, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    func_8007D5D4(fighter);
    func_8007EFC0(fighter, p_ftCommonData->x5F0);
    func_8007E2FC(gobj);
    fighter->x221D_flag.bits.b7 = 1;
    if (fighter->x2C_facing_direction > 0.0f) {
        fighter->x2340_stateVar1 = fighter->x6F0_collData.x44;
    } else {
        fighter->x2340_stateVar1 = fighter->x6F0_collData.x40;
    }
    func_80081544(gobj);
    func_800881D8(fighter, fighter->x10C_ftData->x4C_collisionData->x28, 0x7F, 0x40);
    func_8007E2F4(fighter, 0x1FF);
    func_8007EBAC(fighter, 0xC, 0);

    if (fighter->x2C_facing_direction > 0.0f) {
        func_80053ECC(fighter->x2340_stateVar1, unkParam.x10);
    }
    else
    {
        func_80053DA4(fighter->x2340_stateVar1, unkParam.x10);
    }
    efAsync_Spawn(gobj, (void*) ((u32) gobj->user_data + 0x60C), 2, 0x41C, 0, &unkParam.x10);
    func_80088148(fighter, 4, 0x7F, 0x40);
}

void func_80081504(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0)
    {
        func_8009A804(gobj);
    }
}

void func_80081540() {}

void func_80081544(HSD_GObj* gobj) {
    s32 dummy1[1];
    f32 sp10[2];
    s32 dummy2[1];

    Fighter* fighter = gobj->user_data;
    if (func_80054ED8(fighter->x2340_stateVar1) != 0) {
        if (fighter->x2C_facing_direction > 0.0f) {
            func_80053ECC(fighter->x2340_stateVar1, sp10);
        } else {
            func_80053DA4(fighter->x2340_stateVar1, sp10);
        }
        fighter->xB0_pos.x = (f32) ((fighter->x68C_transNPos.z * fighter->x2C_facing_direction) + sp10[0]);
        fighter->xB0_pos.y = (f32) (sp10[1] + fighter->x68C_transNPos.y);
        return;
    }
    func_800CC730(gobj);
}

void func_800815E4(HSD_GObj* gobj) {
    Fighter* fighter;
    s32 unused1, unused2;
    if (func_800821DC() != 0) {
        func_80082B1C(gobj);
        return;
    }
    if (func_8009EF68(gobj) != 0) {
        fighter = gobj->user_data;
        fighter->x2064_ledgeCooldown = p_ftCommonData->x498_ledgeCooldownTime;
    }
}

void func_80081644(HSD_GObj* gobj)
{
    Fighter* fighter = gobj->user_data;
    func_800761C8();
    if ((s32) fighter->xE0_ground_or_air == GA_Air)
    {
        func_8005811C(&fighter->x6F0_collData, fighter->x2340_stateVar1);
        fighter->x890_cameraBox->xC_flag.bits.b0 = 1;
    }
}
