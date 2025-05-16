#include <platform.h>

#include "plbonuslib.h"

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

// void pl_8003E70C(Item_GObj*);

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

// void pl_8003EC30(int, int, int, float);

// void pl_8003FDF4(u8, int);

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

// void pl_8004049C(s32, ItemKind);
