#include "plbonus.h"

#include "inlines.h"
#include "pl_040D.h"
#include "plattack.h"
#include "player.h"
#include "plbonuslib.h"
#include "plstale.h"
#include "pltrick.h"
#include "types.h"

#include <sysdolphin/baselib/debug.h>
#include <melee/cm/camera.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftlib.h>
#include <melee/gm/gm_unsplit.h>

enum {
    Gm_Player_Other = 6,
};

/// Sets a bonus flag boolean to true
static void setFlag(int player, int kind)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(player);
    HSD_ASSERT(0x38, player != Gm_Player_Other);
    HSD_ASSERT(0x39, gmDecisionGetType(kind) == Gm_DecType_Flag);
    table->x0_staleMoveTable.x904[kind] = true;
}

/// Sets a bonus value to a specified number of points
static inline void setPointValue(int player, int kind, unsigned int val)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(player);
    HSD_ASSERT(0x50, player != Gm_Player_Other);
    HSD_ASSERT(0x51, gmDecisionGetType(kind) == Gm_DecType_Point);
    table->x0_staleMoveTable.x904[kind] = val;
}

#pragma push
#pragma dont_inline on
unsigned int pl_800386D8(plActionStats* arg0, ssize_t arg1)
{
    return arg0->by_attack_hi[arg1];
}
#pragma pop

int pl_800386E8(pl_800386E8_arg0_t* arg0)
{
    int temp = arg0->unk_190 + arg0->unk_5AC;
    return temp + arg0->unk_5B0;
}

#pragma push
#pragma dont_inline on
int fn_80038700(int* arg0, int arg1, int arg2)
{
    int sum = 0;
    int i;

    for (i = arg1; i <= arg2; i++) {
        sum += arg0[i + 1];
    }
    return sum;
}
#pragma pop

void pl_80038788(int player, int kind, int arg2)
{
    setPointValue(player, kind, arg2);
}

void pl_80038824(int player, int kind)
{
    pl_StaleMoveTableExt_t* temp_r31 =
        Player_GetStaleMoveTableIndexPtr2(player);

    HSD_ASSERT(92, gmDecisionGetType(kind) == Gm_DecType_Point);
    temp_r31->x0_staleMoveTable.x904[kind] += 1;
}

void pl_80038898(int player, int kind)
{
    unsigned int currentValue;
    pl_StaleMoveTableExt_t* temp_r31 =
        Player_GetStaleMoveTableIndexPtr2(player);
    HSD_ASSERT(103, gmDecisionGetType(kind) == Gm_DecType_Point);
    currentValue = temp_r31->x0_staleMoveTable.x904[kind];
    RETURN_IF(currentValue == 0);
    temp_r31->x0_staleMoveTable.x904[kind] = currentValue - 1;
}

pl_804D6470_t* pl_80038914(void)
{
    return pl_804D6470;
}

void pl_8003891C(int player)
{
    int i;
    pl_StaleMoveTableExt_t* temp_r31;
    /// @todo This aint it
    volatile int temp_zero;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(player);
    plStale_ResetStaleMoveTableForPlayer(player);
    plAttack_8003759C(player);
    pl_80040DDC(player);
    pl_80041524(player);
    pl_800418F4(player);

    for (i = 0; i < 39; ++i) {
        temp_r31->x0_staleMoveTable.x674[i] = 0;
    }
    for (i = 0; i < 39; ++i) {
        temp_r31->x0_staleMoveTable.x710[i] = 0;
    }
    for (i = 0; i < 39; ++i) {
        temp_r31->x0_staleMoveTable.x7AC[i] = 0;
    }
    for (i = 0; i < 30; ++i) {
        temp_r31->x0_staleMoveTable.x848[i] = 0;
    }

    fn_80038FB8(player);
    temp_r31->x0_staleMoveTable.xC60 = 0.0f;
    temp_r31->x0_staleMoveTable.xC64 = 0.0f;
    temp_r31->x0_staleMoveTable.xC68 = 0;
    temp_r31->x0_staleMoveTable.xC6C = 0.0f;
    temp_r31->x0_staleMoveTable.xC70 = 0.0f;
    temp_r31->x0_staleMoveTable.xC74 = 0.0f;
    for (i = 0; i < 6; ++i) {
        temp_r31->x0_staleMoveTable.xC78[i] = 0.0f;
    }
    temp_r31->x0_staleMoveTable.xC90 = 0;
    temp_r31->x0_staleMoveTable.xC94 = 0;
    temp_r31->x0_staleMoveTable.xC98 = 0.0f;
    temp_r31->x0_staleMoveTable.xC9C = 0.0f;
    temp_r31->x0_staleMoveTable.xCA0 = 0.0f;
    temp_r31->x0_staleMoveTable.xCA4 = 0;
    temp_r31->x0_staleMoveTable.xCAC = 6;
    temp_r31->x0_staleMoveTable.xCB4 = 0;

    /// @todo What?
    {
        temp_zero = 0;
        temp_r31->x0_staleMoveTable.xCB8 = 6;
        *(int*) (&temp_r31->x0_staleMoveTable.xCBC.x0) = temp_zero;
    }

    temp_r31->x0_staleMoveTable.xCC0.x0 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x4 = 0;
    temp_r31->x0_staleMoveTable.xCC0.kb_applied1 = 0.0f;
    temp_r31->x0_staleMoveTable.xCC0.xC = 6;
    temp_r31->x0_staleMoveTable.xCC0.x10_b0 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b3 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b1 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b2 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b3 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b4 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b5 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b6 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x10_b7 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b0 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b1 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b2 = 0;
    temp_r31->x0_staleMoveTable.xCC0.x11_b4 = 0;
    temp_r31->x0_staleMoveTable.xCD4 = 0;
    temp_r31->x0_staleMoveTable.xCD8 = 0;
    temp_r31->x0_staleMoveTable.xCE0 = 0.0f;
    temp_r31->x0_staleMoveTable.xCDC = 0.0f;
    temp_r31->x0_staleMoveTable.xCE4 = 0;
    temp_r31->x0_staleMoveTable.xCE8 = 0;
    temp_r31->x0_staleMoveTable.xCEC = 0;
    temp_r31->x0_staleMoveTable.xCF0 = 0;
    temp_r31->xCF4 = 0;
    temp_r31->xCF8 = 0.0f;
    temp_r31->x0_staleMoveTable.xCA8 = 0;
    temp_r31->xD04 = 0;
    temp_r31->xD08 = 0;
    temp_r31->xD0C = 0;
    temp_r31->xD10 = 0;
    temp_r31->xD14 = 0;
    temp_r31->xD18 = 0;
    temp_r31->xD1C = 0;
    temp_r31->xD20 = 0;
    temp_r31->xD24 = 0;
    temp_r31->xD28 = 0;
    temp_r31->xD2C = 0;
    temp_r31->xD30 = 0;
    temp_r31->xD34 = 0;
    temp_r31->xD38 = 0;
    temp_r31->xD3C = 0;
    temp_r31->xD40 = 0;
    temp_r31->xD44 = 0;
    temp_r31->xD48 = 0;
    temp_r31->xD4C = 0;
    temp_r31->xD50 = 0;
    temp_r31->xD54 = 0;
    temp_r31->xDC0 = 0.0f;
    temp_r31->xD58 = 0;
    temp_r31->xD5C = -1U;
    temp_r31->xD60 = 0;
    temp_r31->xD64 = 6;
    temp_r31->xD68 = 0;
    temp_r31->xD6C = 6;
    temp_r31->xCFC = 0;
    temp_r31->xD00 = 0;
    temp_r31->xD70 = 0;
    temp_r31->xD74 = 0.0f;
    temp_r31->xD78 = 0.0f;
    temp_r31->xD7C = 0.0f;
    temp_r31->xD80 = 0.0f;
    temp_r31->xD84 = 0.0f;
    temp_r31->xD88 = 0.0f;
    temp_r31->xD94 = 0.0f;
    temp_r31->xD98 = 0;
    temp_r31->xD8C = 0.0f;
    temp_r31->xD90 = 0;
    temp_r31->xD9C = 0;
    temp_r31->xDA0 = 0;
    temp_r31->xDA4 = 0;
    temp_r31->xDA8 = 0;
    temp_r31->xDAC = 0;
    temp_r31->xDB4 = 0;
    temp_r31->xDBC = 0;
    temp_r31->xDC4 = 0;
    temp_r31->xDC8 = 0;
    temp_r31->xDCC = 0;
    temp_r31->xDD0.bit0 = 0;
    temp_r31->xDD0.bit1 = 0;
    temp_r31->xDD0.bit2 = 0;
    temp_r31->xDD0.bit3 = 0;
    temp_r31->xDD0.bit4 = 0;
    temp_r31->xDD0.bit5 = 0;
    temp_r31->xDD0.bit6 = 0;
    temp_r31->xDD0.bit7 = 0;
    temp_r31->xDD1.bit0 = 0;
    temp_r31->xDD1.bit1 = 0;
    temp_r31->xDD1.bit2 = 0;
    temp_r31->xDD1.bit3 = 0;
    temp_r31->xDB8 = 0;
    temp_r31->xDD1.bit4 = 0;
    temp_r31->xDD1.bit5 = 0;
    temp_r31->xDD1.bit6 = 0;
    temp_r31->xDD1.bit7 = 0;
}

void pl_80038F10(int player)
{
    pl_StaleMoveTableExt_t* temp_r3_2;
    int i;

    pl_StaleMoveTableExt_t* temp_r3 =
        Player_GetStaleMoveTableIndexPtr2(player);
    temp_r3->xD50 = 0;
    temp_r3->xD54 = 0;
    temp_r3->xD60 = 0;
    temp_r3->xD64 = 6;

    for (i = 0; i < 6; ++i) {
        temp_r3_2 = Player_GetStaleMoveTableIndexPtr2(i);

        if (player == temp_r3_2->xD64) {
            temp_r3_2->xD60 = 0;
            temp_r3_2->xD64 = 6;
        }

        if (player == temp_r3_2->x0_staleMoveTable.xCAC) {
            temp_r3_2->x0_staleMoveTable.xCAC = 6;
        }

        if (player == temp_r3_2->xD6C) {
            temp_r3_2->xD6C = 6;
        }
    }
}

void fn_80038FB8(int player)
{
    int var_ctr;
    pl_StaleMoveTableExt_t* temp_r3 =
        Player_GetStaleMoveTableIndexPtr2(player);

    for (var_ctr = 0; var_ctr < 215; ++var_ctr) {
        temp_r3->x0_staleMoveTable.x904[var_ctr] = 0;
    }
}

int pl_8003906C(int player, int kind, unsigned int* arg2, unsigned int arg3,
                unsigned int arg4, unsigned int arg5, int* arg6)
{
    unsigned int var_r3;

    if (pl_Verify_gm_8016AEDC()) {
        if (gm_8016AEDC() <= arg3) {
            if (arg5 >= arg4) {
                if (kind != -1) {
                    setPointValue(player, kind, 1U);
                } else {
                    *arg2 = 1U;
                }
            }

            if (arg3 == gm_8016AEDC()) {
                *arg6 = (int) arg5;
                return 1;
            }
        } else if ((gm_8016AEDC() % arg3) == 0) {
            if (kind != -1) {
                var_r3 = pl_80039418(player, kind);
            } else {
                var_r3 = *arg2;
            }

            if (((int) var_r3 != 0) && (arg5 - (unsigned int) *arg6 < arg4)) {
                if (kind != -1) {
                    setPointValue(player, kind, 0U);
                } else {
                    *arg2 = 0U;
                }
            }

            *arg6 = (int) arg5;
            return 1;
        }
    }
    return 0;
}

bool pl_80039238(int player, int kind, int* arg2, unsigned int arg3, f32* arg4,
                 f32 arg6, f32 arg7)
{
    bool var_r0;
    int var_r3;

    if (gm_8016AEDC() != 0 && gm_8016AEDC() != -2) {
        var_r0 = true;
    } else {
        var_r0 = false;
    }
    if (var_r0) {
        if (gm_8016AEDC() <= arg3) {
            if (arg7 >= arg6) {
                if (kind != -1) {
                    setPointValue(player, kind, 1);
                } else {
                    *arg2 = 1;
                }
            }
            if (arg3 == gm_8016AEDC()) {
                *arg4 = arg7;
                return true;
            }
        } else if (gm_8016AEDC() % arg3 == 0) {
            if (kind != -1) {
                var_r3 = pl_80039418(player, kind);
            } else {
                var_r3 = *arg2;
            }
            if (var_r3 != 0 && arg7 - *arg4 < arg6) {
                if (kind != -1) {
                    setPointValue(player, kind, 0);
                } else {
                    *arg2 = 0;
                }
            }
            *arg4 = arg7;
            return true;
        }
    }
    return false;
}

unsigned int pl_80039418(int player, int kind)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(player);
    return table->x0_staleMoveTable.x904[kind];
}

static inline void resetBonuses(int player)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(player);
    int i;
    for (i = 0; i < 215; ++i) {
        if (gmDecisionGetType(i) == Gm_DecType_Flag) {
            table->x0_staleMoveTable.x904[i] = 0;
        }
    }
}

void pl_80039450(int player)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(player);

    resetBonuses(player);

    fn_80039618(player);
    fn_8003B044(player);
    fn_8003B9A4(player);
    fn_8003BD60(player);
    fn_8003C340(player);
    fn_8003CC84(player);
    fn_8003D2EC(player);

    if (!table->xDD0.bit1) {
        setFlag(player, 0x4F);
    }

    if (!gm_8016B0FC() && !table->xDD0.bit2) {
        setFlag(player, 0x55);
    }

    if (table->xDCC != 0U && table->xDD1.bit5) {
        setFlag(player, 0x4E);
    }
}

void fn_80039618(int player)
{
    pl_StaleMoveTableExt_t* table = Player_GetStaleMoveTableIndexPtr2(player);
    plActionStats* stats = Player_GetActionStats(player);
    HSD_GObj* gobj = Player_GetEntity(player);
    u32 aerials = stats->hits.aerials_count;
    u32 atk_thrown = stats->attacks.thrown_item_count;
    u32* atk_counts = stats->attacks.by_attack_counts;
    u32 atk_x1A8 = stats->attacks.x1A8;
    u32* hit_counts = stats->hits.by_attack_counts;
    u32 hit_thrown = stats->hits.thrown_item_count;
    u32* x358_counts = stats->x358_hits.by_attack_counts;
    u32 hit_specials = stats->hits.specials_count;
    u32 hit_x1A0 = stats->hits.x1A0_count;
    u32 hit_x1A8 = stats->hits.x1A8;
    u32 x358_x1A8 = stats->x358_hits.x1A8;
    u32 attacks_total = stats->attacks.total;
    u32 hits_total = stats->hits.total;
    u32 x358_total = stats->x358_hits.total;
    int i;
    int j;
    int k;

    if (aerials != 0 && aerials == hits_total) {
        setFlag(player, 0);
    }
    if (hit_specials != 0 && hit_specials == hits_total) {
        setFlag(player, 0x21);
    }
    if (hit_x1A0 != 0 && hit_x1A0 == hits_total) {
        setFlag(player, 0x22);
    }
    if (hits_total != 0) {
        for (i = 1; i < 100; i++) {
            if (!((i >= 0x33 && i <= 0x3D) || hit_counts[i] == 0)) {
                goto skip_only_low_moves;
            }
        }
        setFlag(player, 0x24);
    skip_only_low_moves:;
    }
    {
        u32 sum = 0;
        u32 sub_sum = 0;
        for (i = 0x40; i <= 0x62; i++) {
            u32 count = hit_counts[i];
            sum += count;
            switch (i) {
            case 0x42:
            case 0x46:
            case 0x4A:
            case 0x4E:
            case 0x56:
                sub_sum += count;
                break;
            }
        }
        if (sum != 0) {
            if (hits_total == hit_counts[0x62]) {
                setFlag(player, 0x95);
            } else if (hits_total == sub_sum) {
                setFlag(player, 0x96);
            } else if (hits_total == sum) {
                setFlag(player, 0x94);
            }
        }
    }
    for (j = 0; j < 6; j++) {
        for (k = 1; k <= 0x10; k++) {
            if (!(pl_80037B2C(stats, j, k) != 0 || pl_80038628(gobj, k) == 0))
            {
                break;
            }
        }
        if (k == 0x11) {
            setFlag(player, 0x11);
            break;
        }
    }
    if (Player_GetStaleMoveTableIndexPtr2(player)
            ->x0_staleMoveTable.x904[0x11] == 0)
    {
        int found_low = 0;
        int found_high = 0;
        for (k = 1; k <= 0xB; k++) {
            if (!(hit_counts[k] != 0 || pl_80038628(gobj, k) == 0)) {
                break;
            }
        }
        if (k == 0xC) {
            found_low = 1;
        }
        for (k = 0xC; k <= 0x10; k++) {
            if (!(hit_counts[k] != 0 || pl_80038628(gobj, k) == 0)) {
                break;
            }
        }
        if (k == 0x11) {
            found_high = 1;
        }
        if (found_low != 0 && found_high != 0) {
            setFlag(player, 0x10);
        } else if (found_low != 0) {
            setFlag(player, 0xE);
        } else if (found_high != 0) {
            setFlag(player, 0xF);
        }
    }
    {
        u32* p = &x358_counts[1];
        s32 max;
        s32 min;
        int count;
        count = 0;
        min = 0;
        max = 0;
        for (i = 99; i != 0; i--) {
            u32 c = *p;
            if (c != 0) {
                count++;
                if (c > (u32) max) {
                    max = c;
                }
                if (min == 0 || c < (u32) min) {
                    min = c;
                }
            }
            if (max != 0 && min != 0 &&
                (f32) (max - min) >= (f32) max * pl_804D6470->x28)
            {
                goto skip_combo_count;
            }
            p++;
        }
        if (count >= (s32) pl_804D6470->x24) {
            setFlag(player, 0x12);
        }
    skip_combo_count:;
    }
    if (hits_total != 0) {
        if (hit_thrown == hits_total) {
            setFlag(player, 0x15);
        } else if (pl_CalculateAverage(hit_thrown, hits_total) >=
                   pl_804D6470->x34)
        {
            setFlag(player, 0x14);
        }
    }
    if (atk_thrown == 0) {
        setFlag(player, 0x16);
    }
    {
        int hit_count = 0;
        for (i = 1; i < 100; i++) {
            if (hit_counts[i] != 0) {
                if (i < 0x11 || i > 0x30) {
                    goto skip_hit_count;
                }
                hit_count++;
            }
        }
        if (hit_count != 0) {
            if (hit_count == 1) {
                setFlag(player, 0x18);
            } else {
                setFlag(player, 0x17);
            }
        }
    skip_hit_count:;
    }
    if (hits_total != 0) {
        if (pl_CalculateAverage(stats->x56C, hits_total) >= pl_804D6470->x8) {
            setFlag(player, 3);
        }
    }
    if (hits_total != 0 && stats->x574 == hits_total) {
        setFlag(player, 5);
    } else if (hits_total >= pl_804D6470->xC) {
        if (pl_CalculateAverage(stats->x574, hits_total) >= pl_804D6470->x10) {
            setFlag(player, 4);
        }
    }
    if (attacks_total == 0 && table->x0_staleMoveTable.xC60 == 0.0f) {
        setFlag(player, 0x64);
    } else {
        if (attacks_total == 0) {
            setFlag(player, 0x60);
        } else if (table->xD04 >= pl_804D6470->x54) {
            setFlag(player, 0x2F);
        } else if (table->xD04 >= pl_804D6470->x50) {
            setFlag(player, 0x2E);
        }
        if (table->x0_staleMoveTable.xC60 == 0.0f) {
            setFlag(player, 0x62);
        } else if (table->xD0C >= pl_804D6470->xF0) {
            setFlag(player, 0x61);
        }
    }
    {
        u32 falls = Player_GetFalls(player) + gm_80172140();
        if (falls == 0) {
            setFlag(player, 0x63);
        } else if (falls == (u32) table->x0_staleMoveTable.xC94) {
            setFlag(player, 0x66);
        }
    }
    if (table->xDD1.bit0 && table->xDD1.bit1 && table->xDD1.bit2 &&
        table->xDD1.bit3)
    {
        setFlag(player, 0x86);
    }
    if (atk_x1A8 != 0 && atk_x1A8 == x358_x1A8 &&
        hit_x1A8 == (u32) Player_GetStaleMoveTableIndexPtr2(player)
                        ->x0_staleMoveTable.x904[6])
    {
        setFlag(player, 8);
    }
    if (gm_801720B4() == 0) {
        s32 dmg = (s32) table->x0_staleMoveTable.xC64;
        if ((f32) dmg >= 400.0f) {
            setFlag(player, 0x20);
        } else if ((f32) dmg >= 350.0f) {
            setFlag(player, 0x1F);
        } else if ((f32) dmg >= 300.0f) {
            if (gm_8016B3A0() == 0) {
                setFlag(player, 0x1E);
            }
        } else if ((f32) dmg >= 250.0f) {
            setFlag(player, 0x1D);
        } else if ((f32) dmg >= 200.0f) {
            setFlag(player, 0x1C);
        } else if ((f32) dmg >= 150.0f) {
            setFlag(player, 0x1B);
        }
    }
    if ((u32) table->xDC8 != 0) {
        if (x358_total == attacks_total) {
            setFlag(player, 0xD);
        } else if (pl_CalculateAverage(x358_total, attacks_total) >=
                   pl_804D6470->x20)
        {
            setFlag(player, 0xC);
        }
    }
    {
        u32 sum_attacks = fn_80038700((int*) stats, 1, 0x10);
        u32 sum_x358 = fn_80038700((int*) &stats->x358_hits, 1, 0x10);
        if (sum_x358 != 0 && sum_attacks == sum_x358 && !table->xDD1.bit4) {
            setFlag(player, 0x23);
        }
    }
    if (table->x0_staleMoveTable.xC74 >= pl_804D6470->x160) {
        setFlag(player, 0xAA);
    }
    if (pl_800414C0(player) >= pl_804D6470->x0) {
        setFlag(player, 1);
    }
    if (pl_80038628(gobj, 2) != 0) {
        u32 atk1 = atk_counts[1];
        if (atk1 != 0 && atk1 == atk_counts[2]) {
            u32 hit1 = x358_counts[1];
            if (hit1 == x358_counts[2] && atk1 == hit1) {
                if (pl_80038628(gobj, 3) != 0) {
                    u32 atk1b = atk_counts[1];
                    if (atk1b == atk_counts[3] && atk1b == x358_counts[3]) {
                        setFlag(player, 0x19);
                    }
                } else {
                    setFlag(player, 0x19);
                }
            }
        }
    }
    {
        f32 max_ratio = 0.0f;
        f32 sum_ratio = 0.0f;
        for (i = 0; i < 6; i++) {
            if (i != player) {
                f32 val = Player_GetStaleMoveTableIndexPtr2(i)
                              ->x0_staleMoveTable.xC78[player];
                if (max_ratio < val) {
                    max_ratio = val;
                }
                sum_ratio += val;
            }
        }
        if (sum_ratio != 0.0f) {
            if (gm_8016B558() == 3 &&
                pl_CalculateAverage(max_ratio, sum_ratio) >= pl_804D6470->xF8)
            {
                setFlag(player, 0x67);
            } else if (gm_8016B558() >= 4 &&
                       pl_CalculateAverage(max_ratio, sum_ratio) >=
                           pl_804D6470->xFC)
            {
                setFlag(player, 0x67);
            }
        }
    }
    if (gm_8016B558() >= 3) {
        int streak = 0;
        for (i = 0; i < 6; i++) {
            if (i != player) {
                s32 kos = Player_GetKOsByPlayerIndex(player, i);
                if (kos != 0) {
                    if ((f32) kos >= pl_804D6470->x100 && streak == 0) {
                        streak = 1;
                    } else {
                        streak = 0;
                        break;
                    }
                }
            }
        }
        if (streak != 0) {
            setFlag(player, 0x68);
        }
    }
    PAD_STACK(20);
}

void fn_8003B044(int player)
{
    pl_StaleMoveTableExt_t* temp_r31;
    int var_r27;

    f32 var_f30;
    plActionStats* temp_r3;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(player);
    temp_r3 = Player_GetActionStats(player);
    if (!temp_r3->x5BC_b0) {
        setFlag(player, 0x31);
    }
    if (pl_800386D8(temp_r3, 0x65) == 0) {
        setFlag(player, 0x32);
    }
    if (temp_r31->xD14 == 0U) {
        setFlag(player, 0x33);
    }
    if ((pl_800386D8(temp_r3, 0x68) == 0) && (pl_800386D8(temp_r3, 0x67) == 0))
    {
        setFlag(player, 0x35);
    }
    if (!temp_r3->x5BC_b2) {
        if (temp_r3->x5BC_b3) {
            setFlag(player, 0x38);
        } else {
            setFlag(player, 0x3A);
        }
    }
    if (!temp_r31->xDD0.bit0 && temp_r3->x5BC_b3) {
        setFlag(player, 0x39);
    }
    if ((pl_800386D8(temp_r3, 0x6C) != 0) && (pl_800386D8(temp_r3, 0x6D) == 0))
    {
        setFlag(player, 0x51);
    }
    if ((pl_800386D8(temp_r3, 0x6C) == 0) && (pl_800386D8(temp_r3, 0x6D) != 0))
    {
        setFlag(player, 0x52);
    }
    if ((pl_800386D8(temp_r3, 0x6C) == 0) && (pl_800386D8(temp_r3, 0x6D) == 0))
    {
        setFlag(player, 0x50);
        if (pl_800386D8(temp_r3, 0x6E) != 0) {
            setFlag(player, 0x53);
        }
    }
    if (temp_r31->x0_staleMoveTable.xCE4 != 0) {
        if (pl_CalculateAverage(temp_r31->x0_staleMoveTable.xCE8,
                                temp_r31->x0_staleMoveTable.xCE4) >=
            pl_804D6470->x9C)
        {
            setFlag(player, 0x47);
        }
    }
    if (temp_r31->x0_staleMoveTable.xC60 >= pl_804D6470->xD0) {
        if (pl_CalculateAverage(temp_r31->x0_staleMoveTable.xC98,
                                temp_r31->x0_staleMoveTable.xC60) >=
            pl_804D6470->xCC)
        {
            setFlag(player, 0x57);
        }
    }
    if (gm_801720B4() == 0 && temp_r31->xD2C == 0) {
        setFlag(player, 0x6B);
    }
    if (!gm_8016B3A0() && gm_8016B558() >= 3) {
        int i;
        var_f30 = 0.0f;
        var_r27 = 0;
        for (i = 0; i < 6; i++) {
            if (Player_8003221C(i)) {
                var_f30 += Player_GetStaleMoveTableIndexPtr2(i)
                               ->x0_staleMoveTable.xC9C;
                var_r27++;
            }
        }
        if (var_f30 != 0.0F && var_r27 != 0) {
            float tmp = pl_CalculateAverage(var_f30, var_r27);
            if (temp_r31->x0_staleMoveTable.xCA0 >= tmp * pl_804D6470->xF4) {
                setFlag(player, 0x65);
            }
        }
    }
    if (gm_8016AEDC() >= pl_804D6470->x108) {
        float tmp = 0.5F * Camera_80030E10();
        if (temp_r31->xD8C >= pl_804D6470->x104 * tmp) {
            setFlag(player, 0x69);
        }
    }
    if (gm_8016AEDC() >= pl_804D6470->x110 &&
        temp_r31->xD8C < pl_804D6470->x10C)
    {
        setFlag(player, 0x6A);
    }
    {
        float tmp = 0.5F * Camera_80030E10();
        if (temp_r31->xD94 <= pl_804D6470->x114 * tmp) {
            setFlag(player, 0x6C);
        }
    }
    if (temp_r31->xDD1.bit6 && !temp_r31->xDD1.bit7) {
        setFlag(player, 0x5A);
    }
}

void fn_8003B9A4(int player)
{
    pl_StaleMoveTableExt_t* temp_r31;
    int i;
    u32* attack_counts;
    u32* hit_counts;
    plActionStats* action_stats;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(player);
    action_stats = Player_GetActionStats(player);
    attack_counts = action_stats->attacks.by_attack_counts;
    hit_counts = action_stats->hits.by_attack_counts;

    if (attack_counts[StatsAttack_Catch] != 0) {
        if (attack_counts[StatsAttack_Catch] >= pl_804D6470->x3C &&
            hit_counts[StatsAttack_Catch] == 0)
        {
            setFlag(player, 0x26);
        } else if (pl_CalculateAverage(hit_counts[StatsAttack_Catch],
                                       attack_counts[StatsAttack_Catch]) <=
                   pl_804D6470->x44)
        {
            setFlag(player, 0x25);
        }
    }
    if (hit_counts[StatsAttack_Catch] != 0) {
        for (i = StatsAttack_Catch; i < StatsAttack_LedgeAttackSlow; i++) {
            if (!(i == StatsAttack_Catch || i == StatsAttack_CatchAttack ||
                  attack_counts[i] == 0))
            {
                break;
            }
        }
        if (i == StatsAttack_LedgeAttackSlow) {
            if (hit_counts[StatsAttack_CatchAttack] == 0) {
                if (hit_counts[StatsAttack_Catch] >= pl_804D6470->x40) {
                    setFlag(player, 0x27);
                }
            } else {
                setFlag(player, 0x2C);
            }
        }
    }

    for (i = StatsAttack_ThrowF; i < StatsAttack_CargoThrowF; i++) {
        if (attack_counts[i] == StatsAttack_None) {
            break;
        }
    }

    if (i == StatsAttack_CargoThrowF) {
        setFlag(player, 0x28);
    }
    if (temp_r31->x0_staleMoveTable.xC6C > 0.0F) {
        if (pl_CalculateAverage(temp_r31->x0_staleMoveTable.xC70,
                                temp_r31->x0_staleMoveTable.xC6C) >=
            pl_804D6470->x48)
        {
            setFlag(player, 0x2B);
        }
    }
}

void fn_8003BD60(int player)
{
    pl_StaleMoveTableExt_t* temp_r31 =
        Player_GetStaleMoveTableIndexPtr2(player);
    if (gm_8016AEDC() != 0) {
        if (pl_CalculateAverage(temp_r31->xD14, gm_8016AEDC()) >=
            pl_804D6470->x60)
        {
            setFlag(player, 0x34);
        }
        if (pl_CalculateAverage(temp_r31->xD1C, gm_8016AEDC()) >=
            pl_804D6470->x68)
        {
            setFlag(player, 0x36);
        }
        if (pl_CalculateAverage(temp_r31->xD20, gm_8016AEDC()) >=
            pl_804D6470->x6C)
        {
            setFlag(player, 0x37);
        }
        if (temp_r31->xD24 != 0 &&
            pl_CalculateAverage(temp_r31->xD28, temp_r31->xD24) >=
                pl_804D6470->x5C)
        {
            setFlag(player, 0x30);
        }
        if (gm_801720B4() == 0 &&
            pl_CalculateAverage(temp_r31->xD2C, gm_8016AEDC()) >=
                pl_804D6470->x78)
        {
            setFlag(player, 0x3C);
        }
        if (pl_CalculateAverage(temp_r31->xD30, gm_8016AEDC()) >=
            pl_804D6470->xE8)
        {
            setFlag(player, 0x5D);
        }
    }
    if (temp_r31->xDD0.bit3 && temp_r31->xDD0.bit4 && temp_r31->xDD0.bit5 &&
        temp_r31->xDD0.bit6)
    {
        setFlag(player, 0x5E);
    }
    if (temp_r31->xD38 >= pl_804D6470->x164) {
        setFlag(player, 0xAB);
    }
    if (temp_r31->xD3C >= pl_804D6470->x16C) {
        setFlag(player, 0xB4);
    }
}

void fn_8003C340(int player)
{
    int i;

    u32 var_r30;
    u32 var_r29;
    u32 var_r28;
    u32 var_r27;
    u32 var_r26;
    u32 var_r25;
    u32 var_r24;
    u32 count;

    s32 temp_r3;
    s32 temp_r3_2;
    u32 temp_r3_3;

    temp_r3 = pl_8003E39C(player);
    if (temp_r3 == 0) {
        setFlag(player, 0x93);
        return;
    }
    if (temp_r3 == pl_8003E2CC(player, 7)) {
        setFlag(player, 0xB3);
    }
    if (pl_8003E420(player) == it_8026B7D8()) {
        setFlag(player, 0x9F);
    }

    temp_r3_2 = it_8026B7E0();
    if (temp_r3_2 != 0 && temp_r3_2 == pl_8003E334(player, 0x12)) {
        setFlag(player, 0xA0);
    }

    count = 0;
    for (i = 0; i < 0x27; i++) {
        if (i >= 6 && i != 0x12 && pl_8003E2CC(player, i) != 0) {
            count++;
        }
    }
    if (count >= pl_804D6470->x144) {
        setFlag(player, 0x9E);
    }

    var_r24 = 0;
    var_r25 = 0;
    var_r26 = 0;
    var_r27 = 0;
    var_r28 = 0;
    var_r29 = 0;
    var_r30 = 0;

    for (i = 0; i < 0x27; i++) {
        temp_r3_3 = pl_8003E2CC(player, i);
        switch (i) {
        case 11:
        case 12:
        case 13:
        case 22:
        case 23:
        case 24:
        case 28:
            var_r30 += temp_r3_3;
            break;
        case 16:
        case 21:
        case 25:
            var_r29 += temp_r3_3;
            break;
        case 8:
        case 9:
        case 35:
        case 37:
            var_r28 += temp_r3_3;
            break;
        case 18:
            var_r27 += temp_r3_3;
            break;
        case 26:
        case 27:
        case 31:
        case 32:
        case 33:
            var_r26 += temp_r3_3;
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 14:
        case 15:
        case 17:
        case 19:
        case 20:
        case 30:
        case 34:
        case 36:
        case 38:
            var_r25 += temp_r3_3;
            break;
        case 10:
        case 29:
            var_r24 += temp_r3_3;
            break;
        }
    }

    if (var_r30 >= pl_804D6470->x148 && var_r29 == 0 && var_r28 == 0 &&
        var_r27 == 0 && var_r26 == 0 && var_r25 == 0 && var_r24 == 0)
    {
        setFlag(player, 0xA2);
    }
    if (var_r30 == 0 && var_r29 >= pl_804D6470->x14C && var_r28 == 0 &&
        var_r27 == 0 && var_r26 == 0 && var_r25 == 0 && var_r24 == 0)
    {
        setFlag(player, 0xA3);
    }
    if (var_r30 == 0 && var_r29 == 0 && var_r28 >= pl_804D6470->x150 &&
        var_r27 == 0 && var_r26 == 0 && var_r25 == 0 && var_r24 == 0)
    {
        setFlag(player, 0xA4);
    }
    if (var_r30 == 0 && var_r29 == 0 && var_r28 == 0 &&
        var_r27 >= pl_804D6470->x154 && var_r26 == 0 && var_r25 == 0 &&
        var_r24 == 0)
    {
        setFlag(player, 0xA1);
    }
    if (var_r30 == 0 && var_r29 == 0 && var_r28 == 0 && var_r27 == 0 &&
        var_r26 >= pl_804D6470->x158 && var_r25 == 0 && var_r24 == 0)
    {
        setFlag(player, 0xA5);
    }
    if (var_r30 == 0 && var_r29 == 0 && var_r28 == 0 && var_r27 == 0 &&
        var_r26 == 0 && var_r25 >= pl_804D6470->x15C && var_r24 == 0)
    {
        setFlag(player, 0xA6);
    }
    if (pl_8003E2CC(player, 0x1A) + pl_8003E2CC(player, 0x1B) >=
        pl_804D6470->x168)
    {
        setFlag(player, 0xAE);
    }

    for (i = 0; i < 0x27; i++) {
        switch (i) {
        case 0xA:
        case 0x19:
        case 0x1A:
            if (pl_8003E2CC(player, i) == 0) {
                goto skip;
            }
            break;
        default:
            if (pl_8003E2CC(player, i) != 0) {
                goto skip;
            }
            break;
        }
    }
    setFlag(player, 0xAF);
skip:

    if (pl_8003E2CC(player, 7) >= pl_804D6470->x170) {
        setFlag(player, 0xB5);
    }
    if (pl_8003E2CC(player, 9) >= pl_804D6470->x174) {
        setFlag(player, 0xBC);
    }
    if (pl_8003E2CC(player, 8) >= pl_804D6470->x178) {
        setFlag(player, 0xBD);
    }
    if (pl_8003E7D4(player, 0xB7) != 0) {
        setFlag(player, 0xCC);
    }
    if (pl_8003E7D4(player, 0xB8) != 0) {
        setFlag(player, 0xCD);
    }
}

void fn_8003CC84(int player)
{
    Fighter_GObj* temp_r29;
    pl_StaleMoveTableExt_t* temp_r31;
    int temp_r0;
    int temp_ret;
    int i;
    int temp_r3_3;
    int temp_r5;

    temp_r31 = Player_GetStaleMoveTableIndexPtr2(player);
    Player_GetActionStats(player);
    temp_r29 = Player_GetEntity(player);
    if (!gm_8016B1EC()) {
        pl_8004182C(player);
        pl_80041524(player);
        pl_80041BFC(player);
        pl_800418F4(player);
        if (Player_8003221C(player) != 0) {
            switch (ftLib_80086C0C(temp_r29)) {
            case 0xC:
            case 0xD:
                setFlag(player, 0x89);
                break;
            case 0:
            case 1:
            case 2:
                if ((gm_8016B3D8() != 0) || (gm_801720F8() == 0)) {
                    setFlag(player, 0x8C);
                }
                break;
            case 4:
                if ((gm_8016B3D8() != 0) || (gm_801720F8() == 0)) {
                    setFlag(player, 0x8D);
                }
                break;
            }
            if ((gm_8016B204() == 0) && (gm_8016B110() == 0)) {
                switch (gm_8016AEEC()) {
                case 0x0:
                    setFlag(player, 0x8F);
                    break;
                case 0x7:
                    setFlag(player, 0x8E);
                    break;
                case 0xD5:
                    setFlag(player, 0x90);
                    break;
                }
            }
            if (ftLib_8008732C(temp_r29) == 0) {
                if (ft_800898C0(temp_r29) != 0) {
                    setFlag(player, 0x8B);
                }
                if (temp_r31->xDD0.xDD0_value & 1) {
                    setFlag(player, 0x8A);
                }
                if (ft_80087988(temp_r29) != 0) {
                    setFlag(player, 0xA7);
                }
                for (i = 0; i < 6; i++) {
                    if (player == Player_GetStaleMoveTableIndexPtr2(i)
                                      ->x0_staleMoveTable.xCAC)
                    {
                        setFlag(player, 0xA8);
                    }
                }
                if (ft_800879D8(temp_r29) != 0) {
                    setFlag(player, 0xA9);
                }
                if (ft_800879F8(temp_r29) != 0) {
                    setFlag(player, 0xBE);
                }
                temp_ret = Player_GetDamage(player);
                if (temp_ret == 0) {
                    setFlag(player, 0x92);
                }
                {
                    temp_r5 = temp_ret / 100;
                    temp_r3_3 = (temp_ret - (temp_r5 * 100)) / 10;
                    temp_r0 = (temp_ret - (temp_r5 * 100)) - (temp_r3_3 * 10);
                }
                if ((temp_r5 != 0 && temp_r5 == temp_r3_3 &&
                     temp_r3_3 == temp_r0) ||
                    (temp_r5 == 0 && temp_r3_3 != 0 && temp_r3_3 == temp_r0))
                {
                    setFlag(player, 0x91);
                }
            }
        }
    }
}

void fn_8003D2EC(int player)
{
    u32 temp_r30;
    u32* temp_r27;
    plActionStats* temp_r3;
    int i;

    temp_r3 = Player_GetActionStats(player);
    temp_r27 = temp_r3->attacks.by_attack_counts;
    temp_r30 = temp_r3->attacks.total;

    if (gm_8016B0FC() ||
        Player_GetStaleMoveTableIndexPtr2(player)->x0_staleMoveTable.x904[0] !=
            0 ||
        Player_GetStaleMoveTableIndexPtr2(player)->x0_staleMoveTable.x904[5] !=
            0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x15] != 0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x17] != 0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x18] != 0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x21] != 0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x22] != 0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x24] != 0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x96] != 0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x95] != 0 ||
        Player_GetStaleMoveTableIndexPtr2(player)
                ->x0_staleMoveTable.x904[0x94] != 0)
    {
        return;
    }

    if (temp_r30 >= pl_804D6470->xDC) {
        for (i = 1; i < 100; i++) {
            if (pl_CalculateAverage(temp_r27[i], temp_r30) >= pl_804D6470->xD8)
            {
                setFlag(player, 0x59);
                break;
            }
        }
    }
}
