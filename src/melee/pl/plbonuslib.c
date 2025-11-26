#include "plbonuslib.h"

#include "inlines.h"
#include "pl_040D.h"
#include "placeholder.h"
#include "player.h"
#include "plbonus.h"
#include "plbonusinline.h"

#include <platform.h>

#include <ft/ft_0877.h>
#include <ft/ft_0892.h>
#include <ft/ftlib.h>
#include <gm/gm_16F1.h>
#include <gr/stage.h>
#include <if/ifmagnify.h>
#include <it/it_26B1.h>
#include <MetroTRK/intrinsics.h>
#include <MSL/math.h>
#include <MSL/math_ppc.h>

/// @todo Lots of 6s in here
// pl_8004049C seems to indicate it might have actually been `Gm_Player_NumMax`

/* 03D514 */ static void plBonusLib_8003D514(int);

void plBonusLib_8003D514(int arg0)
{
    Vec3 sp18;
    Vec3 spC;
    HSD_GObj* temp_r31 = Player_GetEntity(arg0);
    HSD_GObj* temp_r30;
    f32 temp_f1;
    int var_r29;
    pl_StaleMoveTableExt_t* temp_r31_2;

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

bool pl_8003D60C(int arg0)
{
    if (((arg0 >= 0xA0) && (arg0 < 0xA1)) ||
        ((arg0 >= 0xEA) && (arg0 < 0xEE)) || (arg0 == 0xE1))
    {
        return true;
    } else {
        return false;
    }
}

inline bool unk_cond(int arg0, int temp_r23)
{
    if (temp_r23 == 6 || temp_r23 == arg0 ||
        pl_CheckIfSameTeam(arg0, temp_r23))
    {
        return true;
    } else {
        return false;
    }
}

inline bool between_A1_D0(int x)
{
    if (x >= 0xA1 && x < 0xD0) {
        return true;
    } else {
        return false;
    }
}

void pl_8003D644(int arg0, int arg1, int arg2, int arg3)
{
    Fighter_GObj* temp_r3;
    ft_800898B4_t* temp_r31;
    pl_StaleMoveTableExt_t* temp_r26;
    pl_StaleMoveTableExt_t* temp_r3_2;
    pl_StaleMoveTableExt_t* temp_r3_3;
    pl_StaleMoveTableExt_t* temp_r3_4;
    struct UnkPlBonusBits* temp_r30;
    int temp_r29;
    int temp_r28;
    int temp_r27;
    u16 temp_r24;
    int temp_r23;
    int temp_r22;
    int temp_r20_3;
    int temp_r20_2;
    int temp_r20;

    temp_r26 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r3 = Player_GetEntityAtIndex(arg0, arg1);
    temp_r27 = ftLib_80086C0C(temp_r3);
    temp_r28 = ftLib_800876F4(temp_r3);
    temp_r29 = ftLib_80087700(temp_r3);
    temp_r30 = ft_80089890(temp_r3);
    temp_r24 = ft_8008989C(temp_r3);
    temp_r31 = ft_800898B4(temp_r3);
    temp_r23 = ftLib_80087300(temp_r3);
    temp_r22 = ftLib_8008730C(temp_r3);

    if (arg1 != 1) {
        temp_r26->x0_staleMoveTable.xCB8 = temp_r23;
        temp_r26->x0_staleMoveTable.xCBC = *temp_r30;
        temp_r26->x0_staleMoveTable.xCC0 = *temp_r31;
        temp_r26->x0_staleMoveTable.xCD4 = temp_r24;
        pl_8003FED0(arg0, arg1);
        if (ftLib_800873A4(temp_r3) != 0) {
            pl_80038824(arg0, 0x81);
        }
        if (ftLib_8008737C(temp_r3) != 0) {
            temp_r26->x0_staleMoveTable.xC94++;
        }
        if (ftLib_80087354(temp_r3) != 0) {
            temp_r26->xDD1.bit2 = true;
        }
        if (temp_r27 == 0) {
            temp_r26->xDD1.bit3 = true;
        }
        if (temp_r27 == 2) {
            temp_r26->xDD1.bit0 = true;
        }
        if (temp_r27 == 1) {
            temp_r26->xDD1.bit1 = true;
        }
        if (ft_80087858(temp_r3) != 0) {
            pl_80038788(arg0, 0x83, 1);
        }
        if (ft_80087878(temp_r3, arg2) != 0) {
            pl_80038824(arg0, 0x84);
        }
        plBonusLib_8003D514(arg0);
        if ((u32) arg3 == 0x5FU) {
            pl_80038788(arg0, 0x9C, 1);
        }

        switch (temp_r28) {
        case 1:
        case 2:
            if (temp_r31->x4 <= pl_804D6470->x128 &&
                temp_r31->x0 >= pl_804D6470->x12C)
            {
                pl_80038824(arg0, 0x85);
            }
            if (temp_r28 == 2) {
                if (pl_8003D60C(temp_r29)) {
                    pl_80038788(arg0, 0x88, 1);
                } else if (temp_r23 == arg0) {
                    pl_80038788(arg0, 0x9C, 1);
                }
                if (temp_r29 == 0xEA) {
                    temp_r26->xD00 += 1;
                }
            }
            break;
        case 3:
            switch (temp_r29) {
            case 1:
                pl_80038788(arg0, 0x87, 1);
                break;
            default:
                pl_80038788(arg0, 0x88, 1);
                break;
            }
            break;
        }

        if (temp_r23 == 6 && temp_r28 == 2 && temp_r29 == 6) {
            pl_80038788(arg0, 0xC7, 1);
        }
        if (temp_r28 != 2 || !between_A1_D0(temp_r29)) {
            if (unk_cond(arg0, temp_r23)) {
                if (temp_r23 == arg0) {
                    pl_80041744(temp_r23, temp_r22, temp_r24);
                }
            } else {
                pl_80041720(temp_r23, temp_r22, temp_r24);
            }
        }

        if (unk_cond(arg0, temp_r23)) {
            temp_r26->xD60 = 0;
            temp_r26->xD64 = 6;
        } else {
            temp_r3_2 = Player_GetStaleMoveTableIndexPtr2(temp_r23);
            if (((u32) temp_r3_2->xD60 != 0) &&
                ((s32) temp_r3_2->xD64 == arg0))
            {
                pl_80038824(temp_r23, 0x79);
                temp_r3_2->xD60 = 0;
                temp_r3_2->xD64 = 6;
            }
            temp_r26->xD60 = 0;
            temp_r26->xD64 = temp_r23;
        }

        if (!unk_cond(arg0, temp_r23)) {
            if (ftLib_8008737C(temp_r3) != 0) {
                pl_80038824(temp_r23, 0x6D);
            }
            if (temp_r27 == 3) {
                temp_r3_3 = Player_GetStaleMoveTableIndexPtr2(temp_r23);
                temp_r3_3->x0_staleMoveTable.xCB4 += 1;
            }
            if (pl_804D6470->x120 == Player_GetDamage(arg0)) {
                pl_80038824(temp_r23, 0x76);
            }

            switch (temp_r28) {
            case 1:
            case 2:
                if (temp_r30->x3 >= 1 && temp_r30->x3 <= 3) {
                    pl_80038824(temp_r23, 0x6E);
                }
                if (temp_r30->x3 >= 0x40 && temp_r30->x3 <= 0x43) {
                    pl_80038824(temp_r23, 0xC0);
                }
                if (temp_r30->x3 == 0x46) {
                    pl_80038824(temp_r23, 0xC1);
                }
                if (temp_r30->x3 == 0x5F) {
                    pl_80038824(temp_r23, 0xAD);
                }
                if (temp_r30->x3 == 0x63) {
                    pl_80038824(temp_r23, 0x70);
                }
                if (temp_r30->x3 == 0x61) {
                    pl_80038824(temp_r23, 0xC6);
                }
                if (temp_r30->x2_b7) {
                    pl_80038824(temp_r23, 0x6F);
                }
                if (temp_r28 == 2 && temp_r30->x2_b3) {
                    pl_80038824(temp_r23, 0x72);
                }
                if (temp_r31->x11_b0) {
                    pl_80038824(temp_r23, 0x71);
                }
                if (temp_r31->x10_b0) {
                    pl_80038824(temp_r23, 6);
                }
                if (temp_r31->kb_applied1 >= pl_804D6470->x11C) {
                    pl_80038824(temp_r23, 0x74);
                }
                if (temp_r31->x11_b2) {
                    pl_80038824(temp_r23, 0x75);
                }
                if (temp_r31->x11_b1) {
                    pl_80038824(temp_r23, 0x77);
                }
                if (temp_r31->x10_b1) {
                    pl_80038824(temp_r23, 0xB0);
                }
                if (temp_r31->x10_b2) {
                    pl_80038824(temp_r23, 0xBB);
                }
                if (temp_r31->x10_b3) {
                    pl_80038824(temp_r23, 0xBF);
                }
                if (temp_r31->x10_b4) {
                    pl_80038824(temp_r23, 0xBA);
                }
                if (temp_r31->x10_b5) {
                    pl_80038824(temp_r23, 0xB7);
                }
                if (temp_r31->x10_b6) {
                    pl_80038824(temp_r23, 0xB8);
                }
                if (temp_r31->x11_b3) {
                    pl_80038824(temp_r23, 0xB);
                }
                if (temp_r31->x11_b4) {
                    pl_80038824(temp_r23, 0x7E);
                }
                if (!gm_8016B204() && !gm_8016B110() &&
                    gm_8016AEEC() + 1 <= pl_804D6470->x118)
                {
                    pl_80038824(temp_r23, 0x73);
                }
                if (temp_r28 == 2) {
                    if (temp_r30->x3 == 0x62) {
                        switch (temp_r29) {
                        case 0:
                        case 3:
                            pl_80038824(temp_r23, 0x97);
                            break;
                        case 1:
                        case 2:
                        case 4:
                            pl_80038824(temp_r23, 0x98);
                            break;
                        case 30:
                            pl_80038824(temp_r23, 0xAC);
                            break;
                        case 20:
                            pl_80038824(temp_r23, 0xB2);
                            break;
                        case 17:
                            pl_80038824(temp_r23, 0xB1);
                            break;
                        }
                    }
                    if (between_A1_D0(temp_r29)) {
                        pl_80038824(temp_r23, 0xCB);
                    }
                    if (pl_8003D60C(temp_r29)) {
                        pl_80038824(temp_r23, 0x80);
                    }
                    if (temp_r29 == 0xEA) {
                        temp_r3_4 =
                            Player_GetStaleMoveTableIndexPtr2(temp_r23);
                        temp_r3_4->xCFC += 1;
                    }
                }
                break;
            case 3:
                switch (temp_r29) {
                case 1:
                    pl_80038824(temp_r23, 0x7F);
                    break;
                default:
                    pl_80038824(temp_r23, 0x80);
                    break;
                }
                break;
            }
        }
    }
}

void pl_8003DF44(int arg0, int arg1)
{
    int temp_r3 = ftLib_80087300(Player_GetEntityAtIndex(arg0, arg1));
    pl_StaleMoveTableExt_t* smte;

    bool var_r0_2;
    if ((temp_r3 == 6) || (temp_r3 == arg0) ||
        pl_CheckIfSameTeam(arg0, temp_r3))
    {
        var_r0_2 = true;
    } else {
        var_r0_2 = false;
    }
    RETURN_IF(var_r0_2);

    smte = Player_GetStaleMoveTableIndexPtr2(temp_r3);
    smte->xD54 = pl_804D6470->xB4;
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
    pl_StaleMoveTableExt_t* stale_moves =
        Player_GetStaleMoveTableIndexPtr2(slot);

    stale_moves->x0_staleMoveTable.xCD8 += 1;
}

void pl_8003E17C(int player_id, int arg1,
                 Item_GObj* item_gobj) // arg1 is fp->x221F_b4 from item owner
{
    pl_StaleMoveTableExt_t* temp_r31 =
        Player_GetStaleMoveTableIndexPtr2(player_id);
    ItemKind kind = itGetKind(item_gobj);
    ItemKind kind2;

    if ((kind >= It_Kind_Capsule) && (kind < It_Kind_L_Gun_Ray)) {
        kind2 = kind;
    } else { // Not one of the common items
        switch (kind) {
        case Pokemon_Lucky_Egg:
            kind2 = It_Kind_L_Gun_Ray;
            break;
        case It_Kind_WhispyApple:
            kind2 = It_Kind_StarRod_Star;
            break;
        case It_Kind_WhispyHealApple:
            kind2 = It_Kind_LipStick_Spore;
            break;
        case It_Kind_Hammer_Head:
            kind2 = It_Kind_S_Scope_Beam;
            break;
        default:
            kind2 = -1;
            break;
        }
    }

    // If item kind is one of the reassigned types from the switch statement
    // above (aka not a common item)
    if (kind2 != -1 &&
        (kind2 == It_Kind_L_Gun_Ray || kind2 == It_Kind_Egg ||
         kind2 == It_Kind_S_Scope_Beam || it_8026B7E8(item_gobj) == 1))
    {
        int cnt;

        if (!it_8026B774(item_gobj, player_id)) {
            temp_r31->x0_staleMoveTable.x674[kind2] += 1;
        }

        for (cnt = 0; cnt < 6; cnt++) {
            if (it_8026B774(item_gobj, cnt)) {
                return;
            }
        }

        temp_r31->x0_staleMoveTable.x710[kind2] += 1;
    }
}

u32 pl_8003E2CC(int arg0, int pl_itemlog_kind)
{
    HSD_ASSERTMSG(555, pl_itemlog_kind < 39,
                  "pl_itemlog_kind < Pl_ItemLog_Terminate");

    return Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.x674[pl_itemlog_kind];
}

u32 pl_8003E334(int arg0, int pl_itemlog_kind)
{
    HSD_ASSERTMSG(564, pl_itemlog_kind < 39,
                  "pl_itemlog_kind < Pl_ItemLog_Terminate");

    return Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.x710[pl_itemlog_kind];
}

int pl_8003E39C(int arg0)
{
    int sum = 0;
    int pl_itemlog_kind;

    for (pl_itemlog_kind = 0; pl_itemlog_kind < 39; pl_itemlog_kind++) {
        HSD_ASSERTMSG(555, pl_itemlog_kind < 39,
                      "pl_itemlog_kind < Pl_ItemLog_Terminate");

        sum += Player_GetStaleMoveTableIndexPtr2(arg0)
                   ->x0_staleMoveTable.x674[pl_itemlog_kind];
    }

    return sum;
}

u32 pl_8003E420(int arg0)
{
    int sum = 0;
    int pl_itemlog_kind;

    for (pl_itemlog_kind = 0; pl_itemlog_kind < 39; pl_itemlog_kind++) {
        HSD_ASSERTMSG(564, pl_itemlog_kind < 39,
                      "pl_itemlog_kind < Pl_ItemLog_Terminate");

        sum += Player_GetStaleMoveTableIndexPtr2(arg0)
                   ->x0_staleMoveTable.x710[pl_itemlog_kind];
    }
    return sum;
}

// pl_8003E4A4

void pl_8003E70C(Item_GObj* igobj)
{
    pl_StaleMoveTableExt_t* temp_r31;
    s32 temp_r3;

    HSD_GObj* temp_r30 = it_8026BC78(igobj);

    HSD_ASSERTMSG(634, 0xA1 <= itGetKind(igobj) && itGetKind(igobj) < 0xBF,
                  "It_PKind_Start <= itGetKind(igobj) && itGetKind(igobj) < "
                  "It_PKind_Terminate");
    RETURN_IF(!ftLib_80086960(temp_r30));

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(ftLib_80086BE0(temp_r30));
    temp_r3 = itGetKind(igobj);
    temp_r31->x0_staleMoveTable.total_attack_count_struct.x598[temp_r3] += 1;
}

u32 pl_8003E7D4(int arg0, int kind)
{
    HSD_ASSERTMSG(649, 0xA1 <= kind && kind < 0xBF,
                  "It_PKind_Start <= kind && kind < It_PKind_Terminate");

    return Player_GetStaleMoveTableIndexPtr2(arg0)
        ->x0_staleMoveTable.total_attack_count_struct.x598[kind];
}

void pl_8003E854(int arg0, int arg1, Item_GObj* arg2)
{
    HSD_GObj* temp_r31 = Player_GetEntityAtIndex(arg0, arg1);
    HSD_GObj* temp_r3 = it_8026BC78(arg2);
    u8 temp_r31_2;

    if ((temp_r31 != temp_r3) && (it_8026B7BC(arg2) != 0)) {
        pl_80038824(arg0, 0x9A);

        if (itGetKind(arg2) == It_Kind_Dosei) {
            pl_80038788(arg0, 0xB6, 1);
        }

        if ((arg1 == 0) && ftLib_80086960(temp_r3) &&
            (ftLib_800874BC(temp_r3) == 0))
        {
            temp_r31_2 = ftLib_80086BE0(temp_r3);
            Player_GetStaleMoveTableIndexPtr2(arg0)->xD6C = (s32) temp_r31_2;
        }
    }

    if (itGetKind(arg2) == It_Kind_BombHei) {
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
    /// @todo Not actually sure what the second argument should be
    fn_8003E998(slot, fp_x221F_b4);
}

void fn_8003E998(int arg0, int index)
{
    pl_StaleMoveTableExt_t* temp_r31;
    temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    if (index == 0 && temp_r31->xD6C != 6) {
        Fighter_GObj* gobj = Player_GetEntityAtIndex(arg0, index);
        ft_800898A8(gobj)->x207C.y = temp_r31->xD6C;
    }
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
    pl_StaleMoveTableExt_t* temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);

    if ((arg1 == 0) && (arg2 == 0x59)) {
        temp_r31->x0_staleMoveTable.xCA8 += 1;

        if (temp_r31->x0_staleMoveTable.xCA8 == it_8026C1D4()) {
            pl_80038788(arg0, 0xC2, 1);
        }
    }
}

void pl_8003EB30(float arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    pl_StaleMoveTableExt_t* temp_r31;
    pl_StaleMoveTableExt_t* var_r3;
    PAD_STACK(4);

    if (arg1 != 6 && arg1 != arg3) {
        temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg1);
        if (arg3 != 6) {
            var_r3 = Player_GetStaleMoveTableIndexPtr2(arg3);
        } else {
            var_r3 = NULL;
        }
        temp_r31->x0_staleMoveTable.xC6C += arg0;
        if (arg5 == 0x34) {
            temp_r31->x0_staleMoveTable.xC70 += arg0;
        }
        if (arg5 - 0x5C <= 1U) {
            temp_r31->x0_staleMoveTable.xC74 += arg0;
        }
        if (arg3 != 6) {
            if (arg4 == 0) {
                var_r3->x0_staleMoveTable.xC78[arg1] += arg0;
            }
            pl_80040ED4(arg1, arg2, arg3, arg4, arg5, arg0);
        }
        {
            pl_StaleMoveTableExt_t* tmp;
            tmp = Player_GetStaleMoveTableIndexPtr2(arg1);
            tmp->xD08 = 0;
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
    }
}

void pl_8003EC9C(int arg0, int arg1, float arg2, float arg3)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    RETURN_IF(arg1);

    temp_r3->x0_staleMoveTable.xC60 += arg3;
    if (temp_r3->x0_staleMoveTable.xC64 < arg2) {
        temp_r3->x0_staleMoveTable.xC64 = arg2;
    }
    temp_r3->xD10 = 0;
}

void pl_8003ED0C(int arg0, int arg1, int r5, float arg2)
{
    float total;
    float temp_f30;
    pl_StaleMoveTableExt_t* temp_r3;
    s32 temp_r4;
    PAD_STACK(8);

    RETURN_IF(arg0 == r5);
    RETURN_IF(pl_CheckIfSameTeam(r5, arg0));

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r3->x0_staleMoveTable.xCA4++;
    temp_r4 = temp_r3->x0_staleMoveTable.xCA4;
    temp_f30 = temp_r3->x0_staleMoveTable.xCA0 * (temp_r4 - 1) + arg2;

    total = temp_r4;
    temp_r3->x0_staleMoveTable.xCA0 = pl_CalculateAverage(temp_f30, total);
}

inline int match_item_kind(int kind)
{
    if (kind >= 0 && kind < 0x23) {
        return kind;
    } else {
        switch (kind) {
        case 0xCD:
            return 0x23;
        case 0xE1:
            return 0x24;
        case 0xE2:
            return 0x25;
        case 0x28:
            return 0x26;
        default:
            return -1;
        }
    }
}

void fn_8003EE2C(int arg0, int arg1)
{
    pl_StaleMoveTableExt_t* temp_r31;
    Fighter_GObj* temp_r30;
    int temp_r3_3;
    int temp_r28;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r30 = Player_GetEntityAtIndex(arg0, arg1);
    RETURN_IF(arg1 == 1);
    RETURN_IF(!pl_Verify_gm_8016AEDC());

    temp_r31->xD08++;
    if (temp_r31->xD08 > temp_r31->xD04) {
        temp_r31->xD04 = temp_r31->xD08;
    }
    temp_r31->xD10++;
    if (temp_r31->xD10 > temp_r31->xD0C) {
        temp_r31->xD0C = temp_r31->xD10;
    }
    if (ftLib_800865CC(temp_r30) == GA_Air) {
        temp_r31->xD20++;
    } else {
        temp_r31->xD24++;
    }
    temp_r28 = ft_80089884(temp_r30)->x2073;
    if (ft_80089884(temp_r30)->x2072_b1) {
        temp_r31->xD18++;
        if (temp_r31->xD18 >= pl_804D6470->x64) {
            temp_r31->xD14++;
        }
    } else {
        temp_r31->xD18 = 0;
    }
    if (temp_r28 == 0x68) {
        temp_r31->xD1C++;
    }
    if (ftLib_800865CC(temp_r30) == GA_Ground) {
        float var_f1;
        if (ftLib_8008777C(temp_r30) < 0.0f) {
            var_f1 = -ftLib_8008777C(temp_r30);
        } else {
            var_f1 = ftLib_8008777C(temp_r30);
        }
        if (var_f1 >= pl_804D6470->x58) {
            temp_r31->xD28++;
        }
    }
    if (ftLib_800877D4(temp_r30)) {
        temp_r31->xD2C++;
    }
    temp_r3_3 = ifMagnify_802FB6E8(arg0);
    if (temp_r3_3 != 0) {
        temp_r31->xD30++;
        temp_r31->xDD0.bit7 = true;
    } else {
        temp_r31->xDD0.bit7 = false;
    }
    switch (temp_r3_3) {
    case 1:
        temp_r31->xDD0.bit5 = true;
        break;
    case 2:
        temp_r31->xDD0.bit4 = true;
        break;
    case 3:
        temp_r31->xDD0.bit6 = true;
        break;
    case 4:
        temp_r31->xDD0.bit3 = true;
        break;
    }
    if (ft_800878BC(temp_r30)) {
        temp_r31->xD34++;
    }
    if (ft_80087900(temp_r30)) {
        temp_r31->xD38++;
    }
    if (ft_80087944(temp_r30)) {
        temp_r31->xD3C++;
    }

    {
        Item_GObj* item_gobj = ftLib_80086794(temp_r30);
        if (item_gobj != NULL) {
            if (match_item_kind(itGetKind(item_gobj)) != -1 &&
                it_8026B30C(item_gobj) != 5)
            {
                temp_r31->xD44++;
                if (temp_r31->xD44 > temp_r31->xD40) {
                    temp_r31->xD40 = temp_r31->xD44;
                }
            }
        } else {
            if (temp_r31->xD44 != 0) {
                if (temp_r31->xD44 < temp_r31->xD48 || temp_r31->xD48 == 0) {
                    temp_r31->xD48 = temp_r31->xD44;
                }
                temp_r31->xD44 = 0;
            }
        }
    }

    if (temp_r31->xD4C != 0) {
        temp_r31->xD4C--;
    }
    if (temp_r31->xD50 != 0) {
        temp_r31->xD50--;
    }
    if (temp_r31->xD54 != 0) {
        temp_r31->xD54--;
    }
    temp_r31->xD58++;
    if (temp_r31->xD60 != 0) {
        temp_r31->xD60--;
    }
    if (ft_80087AEC(temp_r30)) {
        temp_r31->xD68++;
    }
}

// fn_8003F294

void fn_8003F53C(int arg0, int arg1)
{
    pl_StaleMoveTableExt_t* temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    Fighter_GObj* temp_r30 = Player_GetEntityAtIndex(arg0, arg1);
    unsigned int temp_r3;

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

void pl_8003FAA8(int slot, int index, Vec3* pos, Vec3* prevPos)
{
    float temp_f30;
    pl_StaleMoveTableExt_t* temp_r30;
    int temp_r31;
    PAD_STACK(8);

    temp_r30 = Player_GetStaleMoveTableIndexPtr2(slot);
    fn_8003EE2C(slot, index);
    fn_8003F294(slot, index);
    fn_8003F53C(slot, index);
    fn_8003F654(slot, index, pos, prevPos);

    if (pl_Verify_gm_8016AEDC() && index == 0) {
        temp_r31 = ftLib_80087120(Player_GetEntityAtIndex(slot, index));
        temp_f30 =
            temp_r30->x0_staleMoveTable.xC9C * (gm_8016AEDC() - 1) + temp_r31;

        temp_r30->x0_staleMoveTable.xC9C =
            pl_CalculateAverage(temp_f30, gm_8016AEDC());
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
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    RETURN_IF(arg1 != 0);
    temp_r3->xDD0.bit0 = 1;
}

void pl_8003FC88(int arg0, int arg1, int arg2)
{
    pl_StaleMoveTableExt_t* stale_moves =
        Player_GetStaleMoveTableIndexPtr2(arg0);
    bool var_r4 = false;
    unsigned int temp_r0;

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
    } else {
        stale_moves->x0_staleMoveTable.xC90 = 0U;
    }
}

void pl_8003FDA0(int arg0)
{
    pl_80038788(arg0, 0x5B, 1);
}

void pl_8003FDC8(int arg0)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
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
    RETURN_IF(var_r31 != 6);
    pl_80038788(arg0, 0x1A, 1);
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
    RETURN_IF(var_r31 != 6);
    pl_80038788(arg0, 0x82, 1);
}

void pl_8003FF44(int arg0, int arg1, int arg2)
{
    pl_StaleMoveTableExt_t* temp_r31 = Player_GetStaleMoveTableIndexPtr2(arg0);
    Fighter_GObj* temp_r3 = Player_GetEntityAtIndex(arg0, arg1);
    if ((arg1 == 0) && (arg2 >= 1) && (arg2 <= 0x10) &&
        (ft_80087A8C(temp_r3) > pl_804D6470->x38))
    {
        temp_r31->xDD1.bit4 = 1;
    }
}

void pl_8003FFDC(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    Fighter_GObj* temp_r3 = Player_GetEntityAtIndex(arg2, arg3);
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
    pl_StaleMoveTableExt_t* temp_r30 = Player_GetStaleMoveTableIndexPtr2(arg0);
    int var_r29;

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
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);

    temp_r3->x0_staleMoveTable.xCDC += ABS(arg2);
    temp_r3->x0_staleMoveTable.xCE0 += ABS(arg3);
}

void pl_80040270(int arg0, int arg1, float arg2)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
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
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
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
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    if ((arg3 == 0) && (arg4 >= 0x54) && (arg4 <= 0x57)) {
        temp_r3->x0_staleMoveTable.xCAC = arg0;
    }
}

void pl_80040460(int slot, int arg1)
{
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
    RETURN_IF(arg1 != 0);
    temp_r3->x0_staleMoveTable.xCAC = 6;
}

void pl_8004049C(int player, ItemKind arg1)
{
    int var_r30 = -1;
    s32 var_r0;

    RETURN_IF(player == 6);

    var_r0 = 0;
    if ((player >= 0) && (player < 6)) {
        var_r0 = 1;
    }
    if (var_r0 == 0) {
        OSReport("zako ko player illegal ! :%d\n", player);
        __assert("plbonuslib.c", 1559,
                 "0 <= player && player < Gm_Player_NumMax");
    }

    switch (arg1) {
    case It_Kind_Old_Kuri:
    case It_Kind_Kuriboh:
        var_r30 = 0xCE;
        break;
    case It_Kind_Heiho:
        var_r30 = 0xD6;
        break;
    case It_Kind_Nokonoko:
        var_r30 = 0xCF;
        break;
    case It_Kind_Patapata:
        var_r30 = 0xD0;
        break;
    case It_Kind_Likelike:
        var_r30 = 0xD2;
        break;
    case It_Kind_Old_Lead:
    case It_Kind_Leadead:
        var_r30 = 0xD1;
        break;
    case It_Kind_Old_Octa:
    case It_Kind_Octarock:
        var_r30 = 0xD3;
        break;
    case It_Kind_Old_Otto:
    case It_Kind_Ottosea:
        var_r30 = 0xD4;
        break;
    case It_Kind_Whitebea:
        var_r30 = 0xD5;
        break;
    default:
        break;
    }

    RETURN_IF(var_r30 == -1);
    gm_8016B6E8(player, gm_8016F2F8(var_r30, player));
    pl_80038824(player, var_r30);
}

void pl_80040614(int arg0, bool arg1, float arg8)
{
    RETURN_IF(!arg8);

    if (arg8 <= pl_804D6470->x4C) {
        pl_80038788(arg0, 0x2D, 1);
    }
}

void pl_8004065C(int arg0, int arg1)
{
    RETURN_IF(arg1 != 0);
    pl_80038824(arg0, 0x78);
}

void pl_80040688(int arg0, int arg1, int arg2)
{
    pl_StaleMoveTableExt_t* temp_r3;
    UnkPlBonusBits* bits;
    ft_800898B4_t* xCC0;
    u8 temp_r0_2;
    int temp_r0;

    if (gm_8016AEDC() <= pl_804D6470->xEC) {
        pl_80038788(arg0, 0x5F, 1);
    }

    if (arg2 != 0 && arg1 != 6) {
        temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg1);

        temp_r0 = temp_r3->x0_staleMoveTable.xCB8;
        bits = &temp_r3->x0_staleMoveTable.xCBC;
        xCC0 = &temp_r3->x0_staleMoveTable.xCC0;

        if (!unk_cond(arg1, arg2)) {
            temp_r0_2 = bits->x3;
            if (temp_r0_2 >= 0x33 && temp_r0_2 <= 0x3D) {
                pl_80038788(temp_r0, 0x2A, 1);
            }
            if (xCC0->x10_b0) {
                pl_80038788(temp_r0, 7, 1);
                pl_80038898(temp_r0, 6);
            }
        }
    }
}

float pl_800407C8(int arg0)
{
    f32 temp_f31;
    pl_StaleMoveTableExt_t* temp_r3;
    u32 temp_r5;

    temp_r3 = Player_GetStaleMoveTableIndexPtr2(arg0);
    temp_r5 = temp_r3->x0_staleMoveTable.xCEC;
    if (temp_r5 != 0) {
        float tmp = temp_r3->x0_staleMoveTable.xCEC;
        temp_f31 = temp_r3->x0_staleMoveTable.xCF0;
        return pl_CalculateAverage(temp_f31, tmp);
    }
    return 0.0f;
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
    return Player_GetActionStats(arg0)->x358_hits.total;
}

int pl_80040924(int arg0)
{
    return Player_GetActionStats(arg0)->attacks.total;
}

float pl_80040948(int arg0)
{
    unsigned int total;
    unsigned int temp_r30;
    PAD_STACK(0x10);

    total = Player_GetActionStats(arg0)->attacks.total;
    temp_r30 = Player_GetActionStats(arg0)->x358_hits.total;
    if (total != 0) {
        return pl_CalculateAverage(temp_r30, total);
    }
    return 0.0F;
}

int pl_80040A04(int arg0)
{
    plActionStats* temp_r3 = Player_GetActionStats(arg0);
    return temp_r3->attacks.total - temp_r3->attacks.aerials_count;
}

int pl_80040A30(int arg0)
{
    return Player_GetActionStats(arg0)->attacks.aerials_count;
}

int pl_80040A54(int arg0)
{
    return Player_GetActionStats(arg0)->attacks.thrown_item_count;
}

int pl_80040A78(int arg0)
{
    return Player_GetActionStats(arg0)->attacks.by_attack_counts[StatsAttack_Catch];
}

int pl_80040A9C(int arg0)
{
    u32* val = &Player_GetActionStats(arg0)->attacks.by_attack_counts[StatsAttack_DownAttackD];
    int sum = 0;
    unsigned int cursor_i = 51;
    int ctr;

    for (ctr = 11; ctr > 0; --ctr) {
        if (cursor_i - 51 > 1) {
            sum += *(val + 1);
        }
        val += 1;
        cursor_i += 1;
    }

    return sum;
}

void pl_80040AF0(int arg0)
{
    pl_800386D8(Player_GetActionStats(arg0), 0x70);
}

int pl_80040B18(int arg0)
{
    return Player_GetActionStats(arg0)->attacks.specials_count;
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
    pl_StaleMoveTableExt_t* temp_r3 = Player_GetStaleMoveTableIndexPtr2(slot);
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
    pl_StaleMoveTableExt_t* stale_moves =
        Player_GetStaleMoveTableIndexPtr2(slot);
    stale_moves->x0_staleMoveTable.xCB0 += 1;
}

int pl_80040DB8(int slot)
{
    return Player_GetStaleMoveTableIndexPtr2(slot)->x0_staleMoveTable.xCB0;
}
