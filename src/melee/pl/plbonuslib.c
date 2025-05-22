#include <platform.h>

#include "plbonuslib.h"

#include "gm/gm_1601.h"
#include "it/it_26B1.h"
#include "melee/ft/ftlib.h"
#include "pl/player.h"

/* 03D514 */ static void plBonusLib_8003D514(int);

void plBonusLib_8003D514(int arg0)
{
    Vec3 sp18;
    Vec3 spC;
    HSD_GObj* temp_r31;
    HSD_GObj* temp_r30;
    f32 temp_f1;
    int var_r29;
    StaleMoveTable* temp_r31_2;

    temp_r31 = Player_GetEntity(arg0);
    if (ftLib_80087354(temp_r31) == 0) {
        ftLib_80086644(temp_r31, &sp18);
        var_r29 = 0;
        do {
            if (var_r29 != arg0) {
                temp_r30 = Player_GetEntity(var_r29);
                if (Player_8003221C(var_r29) && !ftLib_8008732C(temp_r30)) {
                    temp_r31_2 = Player_GetStaleMoveTableIndexPtr2(var_r29);
                    ftLib_80086644(temp_r30, &spC);
                    temp_f1 = ftLib_800865C0(temp_r30);
                    ((UnkFlagStruct*) ((u8*) temp_r31_2 + 0xdd1))->b6 = 1;
                    if ((temp_f1 * sp18.x) > (temp_f1 * spC.x)) {
                        ((UnkFlagStruct*) ((u8*) temp_r31_2 + 0xdd1))->b7 = 1;
                    }
                }
            }
            var_r29 += 1;
        } while (var_r29 < 6);
    }
}

void pl_8003E058(int arg0, s32 arg1, int arg2, s32 arg3)
{
    int arg2_player_team;
    bool same_team;

    pl_80038824(arg2, 0x3F);
    if (arg0 == 6) {
        return;
    }

    if (gm_8016B168() && (arg2_player_team = Player_GetTeam(arg2),
                          /// @todo: Swap order of registers
                          Player_GetTeam(arg0) == arg2_player_team))
    {
        same_team = true;
    } else {
        same_team = false;
    }
    if (!same_team) {
        pl_80038824(arg0, 0x3E);
    }
}

void pl_8003E150(s32 slot, s32 arg1)
{
    StaleMoveTable* stale_moves;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    stale_moves->xCD8 += 1;
}

void pl_8003EAAC(s32 arg0, s32 arg1, s32 arg2)
{
    StaleMoveTable* temp_r31;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    if ((arg1 == 0) && (arg2 == 0x59)) {
        temp_r31->xCA8 += 1;
        if (temp_r31->xCA8 == it_8026C1D4()) {
            pl_80038788(arg0, 0xC2, 1);
        }
    }
}

void pl_8003EC30(int slot, int arg1, int arg2, float arg3)
{
    StaleMoveTable* stale_moves;

    if (arg1 != 0) {
        return;
    }

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    switch (arg2) {
    case 1:
    case 3:
        stale_moves->xC98 += arg3;
        break;
    }
}

void pl_8003FC88(s32 arg0, s32 arg1, s32 arg2)
{
    StaleMoveTable* stale_moves;
    u32 temp_r0;
    bool var_r4;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(arg0);
    var_r4 = false;
    if (arg1 != 1) {
        temp_r0 = stale_moves->xC90;
        switch (temp_r0) {
        case 0U:
            if ((arg2 >= 1) && (arg2 <= 3)) {
                var_r4 = true;
            }
            break;
        case 1U:
            if ((arg2 >= 6) && (arg2 <= 8)) {
                var_r4 = true;
            }
            break;
        case 2U:
            if ((arg2 >= 9) && (arg2 <= 11)) {
                var_r4 = true;
            }
            break;
        case 3U:
            if ((arg2 >= 17) && (arg2 <= 48)) {
                var_r4 = true;
            }
            break;
        }
        if (var_r4) {
            if (temp_r0 == 3U) {
                stale_moves->xC90 = 0U;
                pl_80038824(arg0, 0x56);
            } else {
                stale_moves->xC90 += 1U;
            }
            return;
        }
        stale_moves->xC90 = 0U;
    }
}

void pl_8003FE64(s32 arg0)
{
    s32 var_r31;

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (pl_80039418(var_r31, 0x1A) != 0U) {
            break;
        }
    }
    if (var_r31 == 6) {
        pl_80038788(arg0, 0x1A, 1);
    }
}

void pl_8003FED0(s32 arg0, s32 arg1)
{
    s32 var_r31;

    if (arg1 != 0) {
        return;
    }

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (pl_80039418(var_r31, 0x82) != 0U) {
            break;
        }
    }
    if (var_r31 == 6) {
        pl_80038788(arg0, 0x82, 1);
    }
}

void pl_800401F0(s32 arg0, s32 arg1, f32 arg2, f32 arg3)
{
    StaleMoveTable* temp_r3;
    f32 var_f1;
    f32 var_f1_2;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);

    if (arg2 < 0.0f) {
        var_f1 = -arg2;
    } else {
        var_f1 = arg2;
    }
    temp_r3->xCDC += var_f1;

    if (arg3 < 0.0f) {
        var_f1_2 = -arg3;
    } else {
        var_f1_2 = arg3;
    }
    temp_r3->xCE0 += var_f1_2;
}

void pl_800402D0(int slot, bool arg1, bool arg2)
{
    StaleMoveTable* stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    RETURN_IF(arg1);
    ++stale_moves->xCEC;
    RETURN_IF(!arg2);
    ++stale_moves->xCF0;
}

void pl_800403C0(int arg0, int arg1)
{
    PAD_STACK(8);
    Player_GetStaleMoveTableIndexPtr2(arg0);
    pl_80038788(arg0, 0xC5, 1);
}

void pl_80040460(s32 slot, s32 arg1)
{
    StaleMoveTable* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    if (arg1 == 0) {
        temp_r3->xCAC = 6;
    }
}

s32 pl_800408DC(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xCB4;
}

void pl_80040AF0(s32 arg0)
{
    pl_800386D8(Player_GetTotalAttackCountPtr(arg0), 0x70);
}

u32 pl_80040B3C(s32 arg0)
{
    return (u32) Player_GetStaleMoveTableIndexPtr2(arg0)->xC6C;
}

void pl_80040D8C(int slot)
{
    StaleMoveTable* stale_moves;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    stale_moves->xCB0 += 1;
}

s32 pl_80040DB8(int slot)
{
    return Player_GetStaleMoveTableIndexPtr2(slot)->xCB0;
}
