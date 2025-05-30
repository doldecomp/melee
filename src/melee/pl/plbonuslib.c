#include <platform.h>

#include "plbonuslib.h"

#include "ft/ft_0877.h"
#include "gm/gm_1601.h"
#include "if/ifmagnify.h"
#include "it/it_26B1.h"
#include "melee/ft/ft_0892.h"
#include "melee/ft/ftlib.h"
#include "pl/player.h"
#include "pl/plbonus.h"

/* 03D514 */ static void plBonusLib_8003D514(int);

void plBonusLib_8003D514(int arg0)
{
    Vec3 sp18;
    Vec3 spC;
    HSD_GObj* temp_r31;
    HSD_GObj* temp_r30;
    f32 temp_f1;
    int var_r29;
    pl_StaleMoveTableExt_t* temp_r31_2;

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
                    ((UnkFlagStruct*) ((u8*) &temp_r31_2->x0_staleMoveTable +
                                       0xdd1))
                        ->b6 = 1;
                    if ((temp_f1 * sp18.x) > (temp_f1 * spC.x)) {
                        ((UnkFlagStruct*) ((u8*) &temp_r31_2
                                               ->x0_staleMoveTable +
                                           0xdd1))
                            ->b7 = 1;
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
    pl_StaleMoveTableExt_t* stale_moves;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    stale_moves->x0_staleMoveTable.xCD8 += 1;
}

void pl_8003EAAC(s32 arg0, s32 arg1, s32 arg2)
{
    pl_StaleMoveTableExt_t* temp_r31;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    if ((arg1 == 0) && (arg2 == 0x59)) {
        temp_r31->x0_staleMoveTable.xCA8 += 1;
        if (temp_r31->x0_staleMoveTable.xCA8 == it_8026C1D4()) {
            pl_80038788(arg0, 0xC2, 1);
        }
    }
}

void pl_8003EC30(int slot, int arg1, int arg2, float arg3)
{
    pl_StaleMoveTableExt_t* stale_moves;

    if (arg1 != 0) {
        return;
    }

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    switch (arg2) {
    case 1:
    case 3:
        stale_moves->x0_staleMoveTable.xC98 += arg3;
        break;
    }
}

void pl_8003EC9C(s32 arg0, s32 arg1, f32 arg2, f32 arg3)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    if (arg1 == 0) {
        temp_r3->x0_staleMoveTable.xC60 += arg3;
        if (temp_r3->x0_staleMoveTable.xC64 < arg2) {
            temp_r3->x0_staleMoveTable.xC64 = arg2;
        }
        temp_r3->xD10 = 0;
    }
}

void pl_8003EE2C(s32 arg0, s32 arg1)
{
    Fighter_GObj* temp_r30;
    HSD_GObj* temp_r3_4;
    pl_StaleMoveTableExt_t* temp_r31;
    s32 temp_r3_2;
    s32 temp_r3_3;
    bool var_r0;
    s32 var_r3;
    u32 temp_r0;
    u32 temp_r3;
    u32 temp_r3_10;
    u32 temp_r3_5;
    u32 temp_r3_6;
    u32 temp_r3_7;
    u32 temp_r3_8;
    u32 temp_r3_9;
    u8 temp_r28;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r30 = Player_GetEntityAtIndex(arg0, arg1);
    if (arg1 != 1) {
        if ((gm_8016AEDC() != 0U) && (gm_8016AEDC() != -2U)) {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
        if (var_r0) {
            temp_r31->xD08 += 1U;
            temp_r3 = temp_r31->xD08;
            if (temp_r3 > temp_r31->xD04) {
                temp_r31->xD04 = temp_r3;
            }
            temp_r31->xD10 += 1;
            temp_r3_2 = temp_r31->xD10;
            if ((u32) temp_r3_2 > temp_r31->xD0C) {
                temp_r31->xD0C = (u32) temp_r3_2;
            }
            if (ftLib_800865CC(temp_r30) == 1) {
                temp_r31->xD20 += 1;
            } else {
                temp_r31->xD24 += 1;
            }
            temp_r28 = ft_80089884(temp_r30)->x2073;
            /// @todo This is obviously not right, but it matches
            if (((s32) * ((u8*) ft_80089884(temp_r30) + 2) >> 6U) & 1) {
                temp_r31->xD18 += 1U;

                /// @todo uses fcmpu instead of fcmpo
                if ((f32) temp_r31->xD18 == pl_804D6470->x64) {
                    temp_r31->xD14 += 1;
                }
            } else {
                temp_r31->xD18 = 0U;
            }
            if ((s32) temp_r28 == 0x68) {
                temp_r31->xD1C += 1;
            }
            if (ftLib_800865CC(temp_r30) == 0) {
                ftLib_8008777C(temp_r30);
                if (M2C_ERROR(/* Read from unset register $f1 */) < 0.0f) {
                    ftLib_8008777C(temp_r30);
                } else {
                    ftLib_8008777C(temp_r30);
                }
                M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
                if (M2C_ERROR(/* Read from unset register $f1 */) ==
                    pl_804D6470->x58)
                {
                    temp_r31->xD28 += 1;
                }
            }
            if (ftLib_800877D4(temp_r30)) {
                temp_r31->xD2C += 1;
            }
            temp_r3_3 = ifMagnify_802FB6E8(arg0);
            if (temp_r3_3 != 0) {
                temp_r31->xD30 += 1;
                temp_r31->xDD0.bit7 = 1;
            } else {
                temp_r31->xDD0.bit7 = 0;
            }
            switch (temp_r3_3) {
            case 1:
                temp_r31->xDD0.bit5 = 1;
                break;
            case 2:
                temp_r31->xDD0.bit4 = 1;
                break;
            case 3:
                temp_r31->xDD0.bit6 = 1;
                break;
            case 4:
                temp_r31->xDD0.bit3 = 1;
                break;
            }
            if (ft_800878BC(temp_r30)) {
                temp_r31->xD34 += 1;
            }
            if (ft_80087900(temp_r30)) {
                temp_r31->xD38 += 1;
            }
            if (ft_80087944(temp_r30)) {
                temp_r31->xD3C += 1;
            }
            temp_r3_4 = ftLib_80086794(temp_r30);
            if (temp_r3_4 != NULL) {
                var_r3 = itGetKind((Item_GObj*) temp_r3_4);
                if ((var_r3 >= 0) && (var_r3 < 0x23)) {
                    // Empty if
                } else {
                    switch (var_r3) {
                    case 0xCD:
                        var_r3 = 0x23;
                        break;
                    case 0xE1:
                        var_r3 = 0x24;
                        break;
                    case 0xE2:
                        var_r3 = 0x25;
                        break;
                    case 0x28:
                        var_r3 = 0x26;
                        break;
                    default:
                        var_r3 = -1;
                        break;
                    }
                }
                if ((var_r3 != -1) &&
                    (it_8026B30C((Item_GObj*) temp_r3_4) != 5))
                {
                    temp_r31->xD44 += 1U;
                    temp_r3_5 = temp_r31->xD44;
                    if (temp_r3_5 > temp_r31->xD40) {
                        temp_r31->xD40 = temp_r3_5;
                    }
                }
            } else {
                temp_r0 = temp_r31->xD44;
                if (temp_r0 != 0U) {
                    temp_r3_6 = temp_r31->xD48;
                    if ((temp_r0 < temp_r3_6) || (temp_r3_6 == 0U)) {
                        temp_r31->xD48 = temp_r0;
                    }
                    temp_r31->xD44 = 0U;
                }
            }
            temp_r3_7 = temp_r31->xD4C;
            if (temp_r3_7 != 0U) {
                temp_r31->xD4C = temp_r3_7 - 1U;
            }
            temp_r3_8 = temp_r31->xD50;
            if (temp_r3_8 != 0U) {
                temp_r31->xD50 = temp_r3_8 - 1U;
            }
            temp_r3_9 = temp_r31->xD54;
            if (temp_r3_9 != 0U) {
                temp_r31->xD54 = temp_r3_9 - 1U;
            }
            temp_r31->xD58 += 1;
            temp_r3_10 = temp_r31->xD60;
            if (temp_r3_10 != 0U) {
                temp_r31->xD60 -= 1U;
            }
            if (ft_80087AEC(temp_r30)) {
                temp_r31->xD68 += 1;
            }
        }
    }
}

void pl_8003F53C(s32 arg0, s32 arg1)
{
    Fighter_GObj* temp_r30;
    pl_StaleMoveTableExt_t* temp_r31;
    s32 temp_r3;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r30 = Player_GetEntityAtIndex(arg0, arg1);
    if ((arg1 != 1) && (ftLib_800867D8(temp_r30) == false)) {
        if ((ft_800877F8(temp_r30, 0x100) == 0) &&
            (ft_800877F8(temp_r30, 0x200) == 0))
        {
            temp_r31->xDD0.bit1 = 1;
        }
        if (ft_800877F8(temp_r30, 0x80000000) != 0) {
            temp_r31->xDD0.bit2 = 1;
        }
        if ((ft_80087818(temp_r30, 0x100) != 0) ||
            (ft_80087818(temp_r30, 0x200) != 0))
        {
            temp_r31->xCF4 += 1;
            temp_r3 = temp_r31->xD58;
            if ((u32) temp_r3 < temp_r31->xD5C) {
                temp_r31->xD5C = (u32) temp_r3;
            }
            temp_r31->xD58 = 0;
        }
    }
}

s32 pl_8003FBFC(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xCFC;
}

s32 pl_8003FC20(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD00;
}

void pl_8003FC44(s32 slot, bool arg1)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    if (!arg1) {
        temp_r3->xDD0.bit0 = 1;
    }
}

void pl_8003FC88(s32 arg0, s32 arg1, s32 arg2)
{
    pl_StaleMoveTableExt_t* stale_moves;
    u32 temp_r0;
    bool var_r4;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(arg0);
    var_r4 = false;
    if (arg1 != 1) {
        temp_r0 = stale_moves->x0_staleMoveTable.xC90;
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
                stale_moves->x0_staleMoveTable.xC90 = 0U;
                pl_80038824(arg0, 0x56);
            } else {
                stale_moves->x0_staleMoveTable.xC90 += 1U;
            }
            return;
        }
        stale_moves->x0_staleMoveTable.xC90 = 0U;
    }
}

void pl_8003FDA0(s32 arg0)
{
    pl_80038788(arg0, 0x5B, 1);
}

void pl_8003FDC8(s32 arg0)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r3->xD70 += 1;
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
    pl_StaleMoveTableExt_t* temp_r3;
    f32 var_f1;
    f32 var_f1_2;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);

    if (arg2 < 0.0f) {
        var_f1 = -arg2;
    } else {
        var_f1 = arg2;
    }
    temp_r3->x0_staleMoveTable.xCDC += var_f1;

    if (arg3 < 0.0f) {
        var_f1_2 = -arg3;
    } else {
        var_f1_2 = arg3;
    }
    temp_r3->x0_staleMoveTable.xCE0 += var_f1_2;
}

void pl_80040270(s32 arg0, bool arg1, f32 arg2)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    if (arg1) {
        return;
    }
    M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
    if (arg2 == pl_804D6470->x98) {
        temp_r3->x0_staleMoveTable.xCE4 += 1;
    }
}

void pl_800402D0(int slot, bool arg1, bool arg2)
{
    pl_StaleMoveTableExt_t* stale_moves =
        Player_GetStaleMoveTableIndexPtr2(slot);
    RETURN_IF(arg1);
    ++stale_moves->x0_staleMoveTable.xCEC;
    RETURN_IF(!arg2);
    ++stale_moves->x0_staleMoveTable.xCF0;
}

void pl_800403C0(int arg0, int arg1)
{
    PAD_STACK(8);
    Player_GetStaleMoveTableIndexPtr2(arg0);
    pl_80038788(arg0, 0xC5, 1);
}

void pl_80040460(s32 slot, s32 arg1)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    if (arg1 == 0) {
        temp_r3->x0_staleMoveTable.xCAC = 6;
    }
}

s32 pl_800408DC(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->x0_staleMoveTable.xCB4;
}

s32 pl_80040900(s32 arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->x358;
}

s32 pl_80040A04(s32 arg0)
{
    pl_800386D8_t* temp_r3;

    temp_r3 = Player_GetTotalAttackCountPtr(arg0);
    return temp_r3->x0 - temp_r3->x198;
}

s32 pl_80040A30(s32 arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->x198;
}

s32 pl_80040A54(s32 arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->x194;
}

void pl_80040AF0(s32 arg0)
{
    pl_800386D8(Player_GetTotalAttackCountPtr(arg0), 0x70);
}

s32 pl_80040B18(s32 arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->x19C;
}

u32 pl_80040B3C(s32 arg0)
{
    return (u32) Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.xC6C;
}

void pl_80040B8C(s32 slot, bool arg1, s32 arg2)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    if (!arg1) {
        temp_r3->x0_staleMoveTable.xC68 += arg2;
    }
}

u32 pl_80040B64(s32 arg0)
{
    return (u32) Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.xC60;
}

s32 pl_80040BD8(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->x0_staleMoveTable.xC68;
}

u32 pl_80040BFC(s32 arg0)
{
    return (u32) Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.xC64;
}

f32 pl_80040C24(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD74;
}

f32 pl_80040C48(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD78;
}

f32 pl_80040C6C(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD7C;
}

f32 pl_80040C90(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD80;
}

s32 pl_80040CB4(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD24;
}

s32 pl_80040CD8(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD20;
}

u32 pl_80040CFC(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD04;
}

s32 pl_80040D20(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD68;
}

f32 pl_80040D44(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD84;
}

f32 pl_80040D68(s32 arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD88;
}

void pl_80040D8C(int slot)
{
    pl_StaleMoveTableExt_t* stale_moves;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    stale_moves->x0_staleMoveTable.xCB0 += 1;
}

s32 pl_80040DB8(int slot)
{
    return Player_GetStaleMoveTableIndexPtr2(slot)->x0_staleMoveTable.xCB0;
}
