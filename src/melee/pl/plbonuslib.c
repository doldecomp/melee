#include <platform.h>

#include "plbonuslib.h"

#include "inlines.h"
#include "pl_040D.h"
#include "placeholder.h"
#include "player.h"
#include "plbonus.h"

#include <ft/ft_0877.h>
#include <ft/ft_0892.h>
#include <ft/ftlib.h>
#include <gm/gm_1601.h>
#include <gr/stage.h>
#include <if/ifmagnify.h>
#include <it/it_26B1.h>
#include <MetroTRK/intrinsics.h>

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

    RETURN_IF(ftLib_80087354(temp_r31) != 0);
    ftLib_80086644(temp_r31, &sp18);
    for (var_r29 = 0; var_r29 < 6; var_r29++) {
        if (var_r29 == arg0) {
            continue;
        }
        temp_r30 = Player_GetEntity(var_r29);
        if (!Player_8003221C(var_r29) || ftLib_8008732C(temp_r30)) {
            continue;
        }
        temp_r31_2 = Player_GetStaleMoveTableIndexPtr2(var_r29);
        ftLib_80086644(temp_r30, &spC);
        temp_f1 = ftLib_800865C0(temp_r30);
        temp_r31_2->xDD1.bit6 = 1;
        if ((temp_f1 * sp18.x) > (temp_f1 * spC.x)) {
            temp_r31_2->xDD1.bit7 = 1;
        }
    }
}

int pl_8003D60C(int arg0)
{
    if (((arg0 >= 0xA0) && (arg0 < 0xA1)) ||
        ((arg0 >= 0xEA) && (arg0 < 0xEE)) || (arg0 == 0xE1))
    {
        return 1;
    } else {
        return 0;
    }
}

void pl_8003DF44(int arg0, int arg1)
{
    int temp_r3;
    bool var_r0_2;

    temp_r3 = ftLib_80087300(Player_GetEntityAtIndex(arg0, arg1));

    if ((temp_r3 == 6) || (temp_r3 == arg0) ||
        pl_CheckIfSameTeam(arg0, temp_r3))
    {
        var_r0_2 = true;
    } else {
        var_r0_2 = false;
    }
    if (var_r0_2 == false) {
        pl_StaleMoveTableExt_t* smte =
            Player_GetStaleMoveTableIndexPtr2(temp_r3);
        smte->xD54 = pl_804D6470->xB4;
    }
}

void pl_8003DFF4(int arg0, int arg1, int arg2)
{
    pl_8003FC88(arg0, arg1, arg2);
    pl_8003FF44(arg0, arg1, arg2);
    pl_8003EAAC(arg0, arg1, arg2);
}

void pl_8003E058(int arg0, int arg1, int arg2, int arg3)
{
    pl_80038824(arg2, 0x3F);

    RETURN_IF(arg0 == 6);
    RETURN_IF(pl_CheckIfSameTeam(arg2, arg0));

    pl_80038824(arg0, 0x3E);
}

void pl_8003E0E8(int arg0, int arg1)
{
    RETURN_IF(arg1 != 0);
    pl_80038824(arg0, 0x40);
}

void pl_8003E114(int arg0, int arg1, float arg2)
{
    if (arg2 <= pl_804D6470->x84) {
        pl_80038788(arg0, 0x41, 1);
    }
}

void pl_8003E150(int slot, int arg1)
{
    pl_StaleMoveTableExt_t* stale_moves;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    stale_moves->x0_staleMoveTable.xCD8 += 1;
}

int pl_8003E2CC(int arg0, int pl_itemlog_kind)
{
    HSD_ASSERTMSG(555, pl_itemlog_kind < 39,
                 "pl_itemlog_kind < Pl_ItemLog_Terminate");

    return Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.x674[pl_itemlog_kind];
}

int pl_8003E334(int arg0, int pl_itemlog_kind)
{
    HSD_ASSERTMSG(564, pl_itemlog_kind < 39,
                 "pl_itemlog_kind < Pl_ItemLog_Terminate");

    return Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.x710[pl_itemlog_kind];
}

int pl_8003E39C(int arg0)
{
    int var_r28;
    int pl_itemlog_kind;

    var_r28 = 0;
    for (pl_itemlog_kind = 0; pl_itemlog_kind < 39; pl_itemlog_kind++) {
        HSD_ASSERTMSG(555, pl_itemlog_kind < 39,
                     "pl_itemlog_kind < Pl_ItemLog_Terminate");

        var_r28 += Player_GetStaleMoveTableIndexPtr2(arg0)
                       ->x0_staleMoveTable.x674[pl_itemlog_kind];
    }
    return var_r28;
}

int pl_8003E420(int arg0)
{
    int var_r28;
    int pl_itemlog_kind;

    var_r28 = 0;
    pl_itemlog_kind = 0;
    for (pl_itemlog_kind = 0; pl_itemlog_kind < 39; pl_itemlog_kind++) {
        HSD_ASSERTMSG(564, pl_itemlog_kind < 39,
                     "pl_itemlog_kind < Pl_ItemLog_Terminate");

        var_r28 += Player_GetStaleMoveTableIndexPtr2(arg0)
                       ->x0_staleMoveTable.x710[pl_itemlog_kind];
    }
    return var_r28;
}

void pl_8003E70C(Item_GObj* igobj)
{
    HSD_GObj* temp_r30;
    pl_StaleMoveTableExt_t* temp_r31;
    s32 temp_r3;

    temp_r30 = it_8026BC78(igobj);

    HSD_ASSERTMSG(634, 0xA1 <= itGetKind(igobj) && itGetKind(igobj) < 0xBF,
                 "It_PKind_Start <= itGetKind(igobj) && itGetKind(igobj) < "
                 "It_PKind_Terminate");

    RETURN_IF(!ftLib_80086960(temp_r30));
    temp_r31 = Player_GetStaleMoveTableIndexPtr2(ftLib_80086BE0(temp_r30));
    temp_r3 = itGetKind(igobj);
    temp_r31->x0_staleMoveTable.x5C4[temp_r3] += 1;
}

int pl_8003E7D4(int arg0, int kind)
{
    HSD_ASSERTMSG(649, 0xA1 <= kind && kind < 0xBF,
                 "It_PKind_Start <= kind && kind < It_PKind_Terminate");

    return Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.x5C4[kind];
}

void pl_8003E854(int arg0, int arg1, Item_GObj* arg2)
{
    HSD_GObj* temp_r31;
    HSD_GObj* temp_r3;
    u8 temp_r31_2;

    temp_r31 = Player_GetEntityAtIndex(arg0, arg1);
    temp_r3 = it_8026BC78(arg2);
    if ((temp_r31 != temp_r3) && (it_8026B7BC(arg2) != 0)) {
        pl_80038824(arg0, 0x9A);
        if (itGetKind(arg2) == 7) {
            pl_80038788(arg0, 0xB6, 1);
        }
        if ((arg1 == 0) && ftLib_80086960(temp_r3) &&
            (ftLib_800874BC(temp_r3) == 0))
        {
            temp_r31_2 = ftLib_80086BE0(temp_r3);
            Player_GetStaleMoveTableIndexPtr2(arg0)->xD6C = (s32) temp_r31_2;
        }
    }
    if (itGetKind(arg2) == 6) {
        if (it_8026B960(arg2) <= pl_804D6470->x180) {
            pl_800419AC(arg0, arg1, (u16) it_8026B7CC(arg2));
        }
    }
    RETURN_IF(arg1 != 0);
    Player_GetStaleMoveTableIndexPtr2(arg0)->x0_staleMoveTable.xCA8 = 0;
}

void pl_8003E978(int slot, bool fp_x221F_b4, Item_GObj* item_gobj, float y0,
                 float arg4, float arg5, float arg6, float x1, float y1,
                 float frame_speed_mul)
{
    fn_8003E998(slot, fp_x221F_b4);
}

void pl_8003EA08(int slot, int arg1)
{
    RETURN_IF(arg1);
    Player_GetStaleMoveTableIndexPtr2(slot)->xD6C = 6;
}

void pl_8003EA40(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    RETURN_IF(arg3);
    RETURN_IF(arg2 != arg4);
    pl_80038824(arg0, 0x9B);
}

void pl_8003EA74(int arg0, int arg1)
{
    RETURN_IF(arg1);
    Player_GetStaleMoveTableIndexPtr2(arg0)->xD44 = 0;
}

void pl_8003EAAC(int arg0, int arg1, int arg2)
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

    RETURN_IF(arg1);

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    switch (arg2) {
    case 1:
    case 3:
        stale_moves->x0_staleMoveTable.xC98 += arg3;
        break;
    }
}

void pl_8003EC9C(int arg0, int arg1, float arg2, float arg3)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    RETURN_IF(arg1);

    temp_r3->x0_staleMoveTable.xC60 += arg3;
    if (temp_r3->x0_staleMoveTable.xC64 < arg2) {
        temp_r3->x0_staleMoveTable.xC64 = arg2;
    }
    temp_r3->xD10 = 0;
}

void fn_8003EE2C(int arg0, int arg1)
{
    Fighter_GObj* temp_r30;
    HSD_GObj* temp_r3_4;
    float var_f1;
    pl_StaleMoveTableExt_t* temp_r31;
    int temp_r3_2;
    s32 temp_r3_3;
    bool var_r0;
    s32 var_r3;
    unsigned int temp_r0;
    unsigned int temp_r3;
    unsigned long temp_r3_10;
    unsigned int temp_r3_5;
    unsigned int temp_r3_6;
    unsigned int temp_r3_7;
    unsigned int temp_r3_8;
    unsigned int temp_r3_9;
    u8 temp_r28;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r30 = Player_GetEntityAtIndex(arg0, arg1);
    RETURN_IF(arg1 == true);

    if ((gm_8016AEDC() != 0U) && (gm_8016AEDC() != -2U)) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    RETURN_IF(!var_r0);

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
    if (ft_80089884(temp_r30)->x2072_b1) {
        temp_r31->xD18 += 1U;
        if ((f32) temp_r31->xD18 >= pl_804D6470->x64) {
            temp_r31->xD14 += 1;
        }
    } else {
        temp_r31->xD18 = 0U;
    }
    if ((s32) temp_r28 == 0x68) {
        temp_r31->xD1C += 1;
    }
    if (ftLib_800865CC(temp_r30) == 0) {
        if (ftLib_8008777C(temp_r30) < 0.0f) {
            var_f1 = -ftLib_8008777C(temp_r30);
        } else {
            var_f1 = ftLib_8008777C(temp_r30);
        }
        if (var_f1 >= pl_804D6470->x58) {
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
        if ((var_r3 != -1) && (it_8026B30C((Item_GObj*) temp_r3_4) != 5)) {
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

void fn_8003F53C(int arg0, int arg1)
{
    Fighter_GObj* temp_r30;
    pl_StaleMoveTableExt_t* temp_r31;
    unsigned int temp_r3;

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
            if (temp_r3 < temp_r31->xD5C) {
                temp_r31->xD5C = temp_r3;
            }
            temp_r31->xD58 = 0U;
        }
    }
}

int pl_8003FBFC(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xCFC;
}

int pl_8003FC20(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD00;
}

void pl_8003FC44(int slot, int arg1)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    RETURN_IF(arg1 != 0);
    temp_r3->xDD0.bit0 = 1;
}

void pl_8003FC88(int arg0, int arg1, int arg2)
{
    pl_StaleMoveTableExt_t* stale_moves;
    unsigned int temp_r0;
    bool var_r4;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(arg0);
    var_r4 = false;

    RETURN_IF(arg1 == 1);
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

void pl_8003FDA0(int arg0)
{
    pl_80038788(arg0, 0x5B, 1);
}

void pl_8003FDC8(int arg0)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r3->xD70 += 1;
}

void pl_8003FDF4(int arg0, int arg1)
{
    pl_80038788(arg0, 0xC4, 1);
}

void pl_8003FE1C(int slot, int arg1)
{
    pl_80038824(slot, 0xA);
}

void pl_8003FE40(int arg0)
{
    pl_80038824(arg0, 0x4B);
}

void pl_8003FE64(int arg0)
{
    int var_r31;

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (pl_80039418(var_r31, 0x1A) != 0U) {
            break;
        }
    }
    if (var_r31 == 6) {
        pl_80038788(arg0, 0x1A, 1);
    }
}

void pl_8003FED0(int arg0, int arg1)
{
    int var_r31;
    RETURN_IF(arg1 != 0);

    for (var_r31 = 0; var_r31 < 6; var_r31++) {
        if (pl_80039418(var_r31, 0x82) != 0U) {
            break;
        }
    }
    if (var_r31 == 6) {
        pl_80038788(arg0, 0x82, 1);
    }
}

void pl_8003FF44(int arg0, int arg1, int arg2)
{
    Fighter_GObj* temp_r3;
    pl_StaleMoveTableExt_t* temp_r31;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r3 = Player_GetEntityAtIndex(arg0, arg1);
    if ((arg1 == 0) && (arg2 >= 1) && (arg2 <= 0x10) &&
        (ft_80087A8C(temp_r3) > pl_804D6470->x38))
    {
        temp_r31->xDD1.bit4 = 1;
    }
}

void pl_8003FFDC(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    Fighter_GObj* temp_r3;

    temp_r3 = Player_GetEntityAtIndex(arg2, arg3);
    if ((arg0 != arg2) && (arg4 != ft_80087A98(temp_r3))) {
        pl_80038824(arg0, 0x46);
    }
}

void pl_80040048(int arg0, int arg1)
{
    Fighter_GObj* temp_r3;
    float temp_f31;
    pl_StaleMoveTableExt_t* temp_r3_3;
    int temp_r3_2;
    PAD_STACK(8);

    temp_r3 = Player_GetEntityAtIndex(arg0, arg1);
    temp_r3_2 = ftLib_80087300(temp_r3);
    RETURN_IF(arg1);
    RETURN_IF(temp_r3_2 == 6);
    temp_f31 = ft_800898B4(temp_r3)->kb_applied1;
    temp_r3_3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    if (temp_f31 >= pl_804D6470->x98) {
        temp_r3_3->x0_staleMoveTable.xCE8 += 1;
    }
    if ((temp_f31 >= pl_804D6470->xA0) && (ft_80087AA4(temp_r3) == 0) &&
        (ft_80087AB4(temp_r3) <= 1U))
    {
        pl_80038824(arg0, 0x48);
    }
}

void pl_80040120(int arg0, int arg1)
{
    pl_StaleMoveTableExt_t* temp_r30;
    int var_r29;

    temp_r30 = Player_GetStaleMoveTableIndexPtr2(arg0);
    RETURN_IF(arg1 == 1);

    if (temp_r30->xD4C != 0U) {
        pl_80038824(arg0, 0x4A);
    }
    if (temp_r30->xD54 != 0U) {
        pl_80038824(arg0, 0x4D);
    }

    for (var_r29 = 0; var_r29 < 6; ++var_r29) {
        if (!Player_8003221C(var_r29)) {
            continue;
        }

        if (var_r29 == arg0) {
            temp_r30->xD50 = pl_804D6470->xB0;
        } else {
            Player_GetStaleMoveTableIndexPtr2(var_r29)->xD4C =
                pl_804D6470->xA4;
        }
    }
}

void pl_800401F0(int arg0, int arg1, float arg2, float arg3)
{
    pl_StaleMoveTableExt_t* temp_r3;
    float var_f1;
    float var_f1_2;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);

    if (arg2 < 0.0F) {
        var_f1 = -arg2;
    } else {
        var_f1 = arg2;
    }
    temp_r3->x0_staleMoveTable.xCDC += var_f1;

    if (arg3 < 0.0F) {
        var_f1_2 = -arg3;
    } else {
        var_f1_2 = arg3;
    }
    temp_r3->x0_staleMoveTable.xCE0 += var_f1_2;
}

void pl_80040270(int arg0, int arg1, float arg2)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    RETURN_IF(arg1 != 0);

    if (arg2 >= pl_804D6470->x98) {
        temp_r3->x0_staleMoveTable.xCE4 += 1;
    }
}

void pl_800402D0(int slot, int arg1, int arg2)
{
    pl_StaleMoveTableExt_t* stale_moves =
        Player_GetStaleMoveTableIndexPtr2(slot);
    RETURN_IF(arg1 != 0);
    ++stale_moves->x0_staleMoveTable.xCEC;
    RETURN_IF(arg2 == 0);
    ++stale_moves->x0_staleMoveTable.xCF0;
}

void pl_80040330(int slot, int arg1, float arg2)
{
    pl_StaleMoveTableExt_t* temp_r3;

    RETURN_IF(arg1 != 0);

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    if (arg2 < temp_r3->xCF8) {
        temp_r3->xCF8 = arg2;
    }
}

void pl_80040374(int arg0, int arg1)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    if ((arg1 == 0) && (temp_r3->xD64 != 6)) {
        temp_r3->xD60 = pl_804D6470->x124;
    }
}

void pl_800403C0(int arg0, int arg1)
{
    PAD_STACK(8);

    Player_GetStaleMoveTableIndexPtr2(arg0);
    pl_80038788(arg0, 0xC5, 1);
}

void pl_800403FC(int arg0, int arg1, int slot, int arg3, int arg4)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    if ((arg3 == 0) && (arg4 >= 0x54) && (arg4 <= 0x57)) {
        temp_r3->x0_staleMoveTable.xCAC = arg0;
    }
}

void pl_80040460(int slot, int arg1)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    RETURN_IF(arg1 != 0);
    temp_r3->x0_staleMoveTable.xCAC = 6;
}

void pl_8004065C(int arg0, int arg1)
{
    RETURN_IF(arg1 != 0);
    pl_80038824(arg0, 0x78);
}

float pl_80040870(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xCF8;
}

unsigned int pl_80040894(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD40;
}

unsigned int pl_800408B8(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD48;
}

int pl_800408DC(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->x0_staleMoveTable.xCB4;
}

int pl_80040900(int arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->x358;
}

int pl_80040924(int arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->total_attack_count;
}

int pl_80040A04(int arg0)
{
    pl_800386D8_t* temp_r3;

    temp_r3 = Player_GetTotalAttackCountPtr(arg0);
    return temp_r3->total_attack_count - temp_r3->x198;
}

int pl_80040A30(int arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->x198;
}

int pl_80040A54(int arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->x194;
}

int pl_80040A78(int arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->xD0;
}

void pl_80040AF0(int arg0)
{
    pl_800386D8(Player_GetTotalAttackCountPtr(arg0), 0x70);
}

int pl_80040B18(int arg0)
{
    return Player_GetTotalAttackCountPtr(arg0)->x19C;
}

unsigned int pl_80040B3C(int arg0)
{
    return (unsigned int) Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.xC6C;
}

unsigned int pl_80040B64(int arg0)
{
    return (unsigned int) Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.xC60;
}

void pl_80040B8C(int slot, int arg1, int arg2)
{
    pl_StaleMoveTableExt_t* temp_r3;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    RETURN_IF(arg1 != 0);
    temp_r3->x0_staleMoveTable.xC68 += arg2;
}

int pl_80040BD8(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->x0_staleMoveTable.xC68;
}

unsigned int pl_80040BFC(int arg0)
{
    return (unsigned int) Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.xC64;
}

float pl_80040C24(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD74;
}

float pl_80040C48(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD78;
}

float pl_80040C6C(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD7C;
}

float pl_80040C90(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD80;
}

int pl_80040CB4(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD24;
}

int pl_80040CD8(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD20;
}

unsigned int pl_80040CFC(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD04;
}

int pl_80040D20(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD68;
}

float pl_80040D44(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD84;
}

float pl_80040D68(int arg0)
{
    return Player_GetStaleMoveTableIndexPtr2(arg0)->xD88;
}

void pl_80040D8C(int slot)
{
    pl_StaleMoveTableExt_t* stale_moves;

    stale_moves = Player_GetStaleMoveTableIndexPtr2(slot);
    stale_moves->x0_staleMoveTable.xCB0 += 1;
}

int pl_80040DB8(int slot)
{
    return Player_GetStaleMoveTableIndexPtr2(slot)->x0_staleMoveTable.xCB0;
}
