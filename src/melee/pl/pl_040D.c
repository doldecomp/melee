#include "pl_040D.h"

#include "player.h"
#include "plbonus.h"
#include "plbonusinline.h"

#include <melee/gm/gm_unsplit.h>

void pl_80040DDC(int slot)
{
    struct pl_x5EC_t* temp_r3;
    int i;

    temp_r3 = Player_GetUnk6A8Ptr(slot);
    temp_r3->x0 = 0;
    temp_r3->x4 = 0.0F;
    temp_r3->x8 = 0;
    temp_r3->xC = 0;

    for (i = 0; i < ARRAY_SIZE(temp_r3->x10); i++) {
        temp_r3->x10[i].x0 = 0.0F;
        temp_r3->x10[i].x4 = 0;
        temp_r3->x10[i].x8 = 0;
        temp_r3->x10[i].xC = 0;
        temp_r3->x10[i].x10 = 0;
        temp_r3->x10[i].x12_b0 = false;
    }
}

void pl_80040ED4(int slot, int arg1, int arg2, int arg3, int arg4, f32 arg5)
{
    bool var_r0;
    struct pl_x5EC_t* temp_r31 = Player_GetUnk6A8Ptr(slot);
    struct pl_x5EC_t* temp_r3 = Player_GetUnk6A8Ptr(arg2);
    if (arg3 != 1) {
        if (arg4 != 0x4C && arg4 != 0x5A && arg4 != 0x5B && arg4 != 0x5C &&
            arg4 != 0x60)
        {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
        if (var_r0) {
            temp_r31->x8++;
            if (temp_r3->x10[slot].x4 == 0) {
                temp_r31->xC++;
            }
            temp_r3->x10[slot].x4++;
        }
        temp_r31->x0 = arg2;
        temp_r31->x4 = arg5;
        temp_r3->x10[slot].x0 += arg5;
    }
}

void pl_80040FBC(int slot, UNK_T unused, int arg2, int arg3, int arg4)
{
    pl_StaleMoveTableExt_t* temp_r3;
    bool var_r0;
    bool var_r0_2;
    struct pl_x5EC_t* temp_r29;

    Player_GetUnk6A8Ptr(slot);
    temp_r29 = Player_GetUnk6A8Ptr(arg2);
    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg2);
    if (arg3 != 1) {
        if (arg4 == 1 && temp_r3->xD50 != 0) {
            temp_r29->x10[slot].x12_b0 = true;
        }
        if (arg4 != 0x4C && arg4 != 0x5A && arg4 != 0x5B && arg4 != 0x5C &&
            arg4 != 0x60)
        {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
        if (var_r0) {
            temp_r29->x10[slot].x10++;
        }
        if (temp_r29->x10[slot].x10 >= pl_804D6470->x4) {
            if (gm_8016B168() && Player_GetTeam(slot) == Player_GetTeam(arg2))
            {
                var_r0_2 = true;
            } else {
                var_r0_2 = false;
            }
            if (!var_r0_2) {
                pl_80038788(slot, 2, 1);
            }
        }
    }
}

void pl_800410F4(int slot, UNK_T unused, int arg2, int arg3, int arg4)
{
    struct pl_x5EC_t* temp_r3;

    Player_GetUnk6A8Ptr(slot);
    temp_r3 = Player_GetUnk6A8Ptr(arg2);
    if (arg3 != 1) {
        if (temp_r3->x10[slot].xC != 0 && temp_r3->x10[slot].xC == arg4) {
            temp_r3->x10[slot].x8++;
            if (temp_r3->x10[slot].xC == 0x5A &&
                temp_r3->x10[slot].x8 >= pl_804D6470->x17C)
            {
                pl_80038788(slot, 0xC3, 1);
            }
        } else {
            temp_r3->x10[slot].x8 = 1;
            temp_r3->x10[slot].xC = arg4;
        }
    }
}

void pl_800411C4(int slot, int arg1)
{
    struct pl_x5EC_t* var_r30 = Player_GetUnk6A8Ptr(slot);
    int i;

    if (arg1 != 1) {
        fn_8004138C(slot, arg1);
        for (i = 0; i < (int) ARRAY_SIZE(var_r30->x10); i++) {
            if (var_r30->x10[i].x12_b0 && var_r30->x10[i].x4 == 1) {
                pl_80038824(i, 0x4C);
            }
            var_r30->x10[i].x0 = 0.0f;
            var_r30->x10[i].x4 = 0;
            var_r30->x10[i].x8 = 0;
            var_r30->x10[i].xC = 0;
            var_r30->x10[i].x12_b0 = false;
        }
    }
}

void pl_80041280(int slot, int arg1)
{
    struct pl_x5EC_t* temp_r3 = Player_GetUnk6A8Ptr(slot);
    int i;
    if (arg1 != 1) {
        for (i = 0; i < (int) ARRAY_SIZE(temp_r3->x10); i++) {
            temp_r3->x10[i].x10 = 0;
        }
    }
}

int pl_800412D0(int slot)
{
    return Player_GetUnk6A8Ptr(slot)->x4;
}

int pl_80041300(int slot)
{
    struct pl_x5EC_t* tmp = Player_GetUnk6A8Ptr(Player_GetUnk6A8Ptr(slot)->x0);
    return tmp->x10[slot].x0;
}

int pl_8004134C(int slot)
{
    struct pl_x5EC_t* tmp = Player_GetUnk6A8Ptr(Player_GetUnk6A8Ptr(slot)->x0);
    return tmp->x10[slot].x4;
}

void fn_8004138C(int arg0, int arg1)
{
    struct pl_x5EC_t* temp_r3 = Player_GetUnk6A8Ptr(arg0);
    int i;

    f32 total = 0.0F;
    f32 best = 0.0F;

    PAD_STACK(0x8);

    if (arg1 != 1) {
        for (i = 0; i < ARRAY_SIZE(temp_r3->x10); i++) {
            if (best < temp_r3->x10[i].x0) {
                best = temp_r3->x10[i].x0;
            }
            total += temp_r3->x10[i].x0;
        }
        if (total != 0.0F) {
            if (pl_CalculateAverage(total - best, total) >= pl_804D6470->xD4) {
                pl_80038788(arg0, 0x58, 1);
            }
        }
    }
}

float pl_800414C0(int arg0)
{
    struct pl_x5EC_t* temp_r3 = Player_GetUnk6A8Ptr(arg0);
    if (temp_r3->xC != 0) {
        return (f32) temp_r3->x8 / temp_r3->xC;
    }
    return 0.0F;
}

void pl_80041524(int arg0)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    struct pl_x8C0_t* temp_r3_2 = &temp_r3->x0_staleMoveTable.x8C0;
    int i;

    temp_r3_2->x0 = 0;

    for (i = 0; i < ARRAY_SIZE(temp_r3_2->x4); i++) {
        temp_r3_2->x4[i].x0 = 0;
        temp_r3_2->x4[i].x2 = 0;
        temp_r3_2->x4[i].x3_b0 = false;
    }
}

void fn_800415B0(int slot, int unused, u16 arg2, u32 arg3)
{
    struct pl_x8C0_t* temp_r31;
    int i;

    temp_r31 =
        &Player_GetStaleMoveTableIndexPtr2(slot)->x0_staleMoveTable.x8C0;
    if (arg2 != 0) {
        for (i = 0; i < ARRAY_SIZE(temp_r31->x4); i++) {
            if (arg2 == temp_r31->x4[i].x0) {
                if (arg3) {
                    temp_r31->x4[i].x3_b0 = true;
                } else {
                    temp_r31->x4[i].x2++;
                }
                return;
            }
        }
        fn_80041770(slot, temp_r31->x4[temp_r31->x0].x2,
                    temp_r31->x4[temp_r31->x0].x3_b0);
        temp_r31->x4[temp_r31->x0].x0 = arg2;
        temp_r31->x4[temp_r31->x0].x2 = 0;
        temp_r31->x4[temp_r31->x0].x3_b0 = false;
        if (arg3) {
            temp_r31->x4[temp_r31->x0].x3_b0 = arg3;
        } else {
            temp_r31->x4[temp_r31->x0].x2 = 1;
        }
        temp_r31->x0 = temp_r31->x0 == 4 ? 0 : temp_r31->x0 + 1;
    }
}

void pl_80041720(int slot, int arg1, u16 arg2)
{
    fn_800415B0(slot, arg1, arg2, 0);
}

void pl_80041744(int arg0, int arg1, u16 arg2)
{
    if (arg1 == 0) {
        fn_800415B0(arg0, arg1, arg2, 1);
    }
}

void fn_80041770(int slot, u8 arg1, u32 arg2)
{
    if (arg1 >= 5) {
        pl_80038824(slot, 0x7D);
    } else if (arg1 >= 4) {
        pl_80038824(slot, 0x7C);
    } else if (arg1 >= 3) {
        pl_80038824(slot, 0x7B);
    } else if (arg1 >= 2) {
        pl_80038824(slot, 0x7A);
    }
    if (arg2 != 0 && arg1 != 0) {
        pl_80038824(slot, 0x78);
    }
}

void pl_8004182C(int slot)
{
    pl_StaleMoveTableExt_t* tmp = Player_GetStaleMoveTableIndexPtr2(slot);
    struct pl_x8C0_t* var_r30 = &tmp->x0_staleMoveTable.x8C0;
    int i;

    for (i = 0; i < (int) ARRAY_SIZE(var_r30->x4); i++) {
        fn_80041770(slot, var_r30->x4[i].x2, var_r30->x4[i].x3_b0);
    }
}

void pl_800418F4(int slot)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    struct pl_x8D8_t* tmp = &temp_r3->x0_staleMoveTable.x8D8;
    int i;

    temp_r3->x0_staleMoveTable.x8D8.x0 = 0;
    for (i = 0; i < (int) ARRAY_SIZE(tmp->x4); i++) {
        tmp->x4[i].x0 = 0;
        tmp->x4[i].x4_b0 = 0;
        tmp->x4[i].x4_b1 = 0;
    }
}

void pl_800419AC(int arg0, int arg1, u16 arg2)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    struct pl_x8D8_t* temp_r31 = &temp_r3->x0_staleMoveTable.x8D8;
    int i;

    for (i = 0; i < ARRAY_SIZE(temp_r31->x4); i++) {
        if (temp_r31->x4[i].x4_b1 && arg2 == temp_r31->x4[i].x0) {
            return;
        }
    }

    fn_80041BC8(arg0, temp_r31->x4[temp_r31->x0].x4_b0,
                temp_r31->x4[temp_r31->x0].x4_b1);
    temp_r31->x4[temp_r31->x0].x0 = arg2;
    temp_r31->x4[temp_r31->x0].x4_b0 = false;
    temp_r31->x4[temp_r31->x0].x4_b1 = true;

    temp_r31->x0 = temp_r31->x0 == 4 ? 0 : temp_r31->x0 + 1;
}

void pl_80041B08(int arg0, UNK_T unused, u16 arg2)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    struct pl_x8D8_t* temp_r4 = &temp_r3->x0_staleMoveTable.x8D8;
    int i;

    for (i = 0; i < ARRAY_SIZE(temp_r4->x4); i++) {
        if (arg2 == temp_r4->x4[i].x0) {
            temp_r4->x4[i].x4_b0 = true;
        }
    }
}

void fn_80041BC8(int arg0, u32 arg1, u32 arg2)
{
    if (arg2 && !arg1) {
        pl_80038824(arg0, 0xC8);
    }
}

void pl_80041BFC(int slot)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    struct pl_x8D8_t* var_r31 = &temp_r3->x0_staleMoveTable.x8D8;
    int i;

    for (i = 0; i < (int) ARRAY_SIZE(var_r31->x4); i++) {
        fn_80041BC8(slot, var_r31->x4[i].x4_b0, var_r31->x4[i].x4_b1);
    }
}
