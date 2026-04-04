#include "pltrick.h"

#include "ft/ft_0892.h"
#include "ft/ftdata.h"
#include "ft/inlines.h"
#include "if/ifmagnify.h"
#include "pl/player.h"
#include "pl/plbonus.h"
#include "pl/plbonuslib.h"
#include "pl/pl_040D.h"

#include <sysdolphin/baselib/debug.h>

/* 037F00 */ static void fn_80037F00(HSD_GObj**, Fighter*, ft_800898B4_t*, s32,
                                     s32);

int pl_803BCE70[16] = {
    -1, 0x2F, 0x30, 0x31, -1, -1, -1, -1,
    -1, -1,   -1,   -1,   -1, -1, -1, -1,
};

int pl_80037B2C(struct plActionStats* arg0, int h_player, int idx)
{
    HSD_ASSERT(0x89, 0 <= h_player && h_player < 8);
    if (idx < 0x64) {
        return arg0->x504[idx] & (1 << (u8) h_player);
    }
}

void pl_80037BC0(struct plAttackStats* stats, union Struct2070* ev)
{
    stats->total++;
    stats->by_attack_counts[ev->x2073]++;
    if (ev->count_thrown_items) {
        stats->thrown_item_count++;
    }
    if (ev->count_aerials) {
        stats->aerials_count++;
    }
    if (ev->count_specials) {
        stats->specials_count++;
    }
    if (ev->count_x1A0) {
        stats->x1A0_count++;
    }
    if (ev->count_x1A4) {
        stats->x1A4_count++;
    }
}

static inline void pl_80037BC0_inline(struct plAttackStats* stats,
                                      union Struct2070* ev)
{
    pl_80037BC0(stats, ev);
}

void pl_80037C60(Fighter_GObj* fgp, s32 prev2070_int)
{
    /// @todo stack is still misaligned for this volatile hack...
    // maybe an inline somewhere? idk
    Fighter* fp;
    plActionStats* acp;
    u8 attack_id;
    volatile s32 prev2070_word;
    union Struct2070 prev_union;
    union Struct2070 ev;

    prev2070_word = prev2070_int;
    fp = GET_FIGHTER(fgp);
    acp = Player_GetActionStats(fp->player_id);
    prev_union.x2070_int = (s32) prev2070_word;

    if ((int) fp->x2070.x2072_b2) {
        acp->x5BC_b0 = 1;
    }
    if (fp->x2070.x2072_b1) {
        acp->x5BC_b1 = 1;
    }
    attack_id = 1;
    if (fp->x2070.x2072_b0) {
        acp->x5BC_b2 = attack_id;
    }
    if (fp->x2070.x2071_b7) {
        acp->x5BC_b3 = attack_id;
    }
    attack_id = fp->x2070.x2073;
    if ((attack_id != 0) && (attack_id != prev_union.x2073)) {
        if (attack_id >= StatsAttack_Count) {
            if (!fp->x221F_b4) {
                acp->by_attack_hi[attack_id]++;
            }
        } else {
            ev.x2070_int = fp->x2070.x2070_int;
            acp->attacks.total++;
            acp->attacks.by_attack_counts[ev.x2073]++;
            if (ev.count_thrown_items) {
                acp->attacks.thrown_item_count++;
            }
            if (ev.count_aerials) {
                acp->attacks.aerials_count++;
            }
            if (ev.count_specials) {
                acp->attacks.specials_count++;
            }
            if (ev.count_x1A0) {
                acp->attacks.x1A0_count++;
            }
            if (ev.count_x1A4) {
                acp->attacks.x1A4_count++;
            }
        }
    }
}

void pl_80037DF4(HSD_GObj* gobj, union Struct2070* ev)
{
    Fighter* ft = GET_FIGHTER(gobj);
    union Struct2070 local_ev;
    plActionStats* acp = Player_GetActionStats(ft->player_id);
    local_ev = *ev;
    acp->attacks.total++;
    acp->attacks.by_attack_counts[local_ev.x2073]++;
    if (local_ev.count_thrown_items) {
        acp->attacks.thrown_item_count++;
    }
    if (local_ev.count_aerials) {
        acp->attacks.aerials_count++;
    }
    if (local_ev.count_specials) {
        acp->attacks.specials_count++;
    }
    if (local_ev.count_x1A0) {
        acp->attacks.x1A0_count++;
    }
    if (local_ev.count_x1A4) {
        acp->attacks.x1A4_count++;
    }
}

void pl_80037ECC(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    plActionStats* acp = Player_GetActionStats(ft->player_id);
    acp->attacks.x1A8++;
}

static void fn_80037F00(HSD_GObj** gp, Fighter* fp, ft_800898B4_t* ev,
                        s32 arg3, s32 arg4)
{
    f32 prev_kb;
    pl_804D6470_t* table;
    PAD_STACK(8);

    if (fp->x221C_b6) {
        prev_kb = fp->dmg.x18d8.kb_applied1;
    } else {
        prev_kb = 0.0f;
    }

    if (ev != NULL) {
        fp->dmg.x18d8 = *ev;
    } else {
        fp->dmg.x18d8.x0 = 0;
        fp->dmg.x18d8.x4 = 0;
        fp->dmg.x18d8.kb_applied1 = 0.0f;
        fp->dmg.x18d8.xC = 6;
        fp->dmg.x18d8.x10_b0 = 0;
        fp->dmg.x18d8.x11_b3 = 0;
        fp->dmg.x18d8.x10_b1 = 0;
        fp->dmg.x18d8.x10_b2 = 0;
        fp->dmg.x18d8.x10_b3 = 0;
        fp->dmg.x18d8.x10_b4 = 0;
        fp->dmg.x18d8.x10_b5 = 0;
        fp->dmg.x18d8.x10_b6 = 0;
        fp->dmg.x18d8.x10_b7 = 0;
        fp->dmg.x18d8.x11_b0 = 0;
        fp->dmg.x18d8.x11_b1 = 0;
        fp->dmg.x18d8.x11_b2 = 0;
        fp->dmg.x18d8.x11_b4 = 0;
    }

    fp->dmg.x18d8.x4 = (int) fp->dmg.x1830_percent;

    fp->dmg.x18d8.x11_b0 = arg3;

    if (ifMagnify_802FB6E8(fp->player_id) != 0) {
        fp->dmg.x18d8.x11_b1 = 1;
    }

    if (fp->motion_id == 0xFD) {
        fp->dmg.x18d8.x11_b2 = 1;
    }

    if (fp->dmg.x18c4_source_ply != arg4 && fp->dmg.x18d8.x10_b0) {
        table = pl_80038914();
        if (prev_kb >= table->x14) {
            fp->dmg.x18d8.x11_b3 = 1;
        }
    }

    if (gp != NULL) {
        if (ft_80089914(*gp, fp->dmg.x18d4.x3) != 0 &&
            (fp->victim_gobj == NULL || *gp != fp->victim_gobj))
        {
            fp->dmg.x18d8.x11_b4 = 1;
        }
        ev->x10_b7 = 1;
    }
}

void pl_80038144(HSD_GObj* attacker_gobj, HSD_GObj* victim_gobj,
                 s32 x18d4_int, ft_800898B4_t* ev_data,
                 u16 attack_instance, s32 arg5, s32 source_ply)
{
    Fighter* attacker_fp;
    Fighter* victim_fp;
    Fighter* attacker_fp2;
    plActionStats* acp;
    plActionStats* acp2;
    s32 attacked_from_behind;
    u8 attack_id;
    u8 attack_id2;
    s32 h_player;
    s32 x18d4_x3;
    s32 var_r0;
    union Struct2070 ev;
    union Struct2070 ev_reload;
    union Struct2070 ev_best;
    union Struct2070 ev_hits;
    PAD_STACK(16);

    if (attacker_gobj != NULL) {
        attacker_fp = GET_FIGHTER(attacker_gobj);
    } else {
        attacker_fp = NULL;
    }

    victim_fp = GET_FIGHTER(victim_gobj);
    attacked_from_behind = 0;
    ev.x2070_int = x18d4_int;

    if (attacker_fp != NULL && ev.x2073 != 0) {
        f32 facing_dir = victim_fp->facing_dir;

        if (facing_dir * attacker_fp->cur_pos.x <
            facing_dir * victim_fp->cur_pos.x)
        {
            if ((int) ev.x2073 == 0x60 || (int) ev.x2073 == 0x61 ||
                ((int) ev.x2073 >= 0x33 && (int) ev.x2073 <= 0x3D))
            {
                var_r0 = 0;
            } else {
                var_r0 = 1;
            }
            if (var_r0 != 0) {
                attacked_from_behind = 1;
            }
        }

        pl_800410F4(attacker_fp->player_id, attacker_fp->x221F_b4,
                     victim_fp->player_id, victim_fp->x221F_b4, ev.x2073);
    }

    if (attack_instance == 0 ||
        victim_fp->dmg.x18ec_instancehitby != attack_instance)
    {
        *(s32*) &victim_fp->dmg.x18d4 = ev.x2070_int;
        victim_fp->dmg.x18ec_instancehitby = attack_instance;

        if (attacker_fp != NULL && victim_fp->dmg.x18d4.x3 != 0) {
            if (gm_8016B168() && gm_8016B0D4() &&
                attacker_fp->team == victim_fp->team)
            {
                pl_80040D8C(attacker_fp->player_id, attacker_fp->x221F_b4);
            }

            attack_id = ev.x2073;
            if (attack_id < 0x64) {
                struct plAttackStats* temp;

                acp = Player_GetActionStats(attacker_fp->player_id);
                ev_reload.x2070_int = *(s32*) &victim_fp->dmg.x18d4;
                attacker_fp2 = GET_FIGHTER(attacker_gobj);
                acp2 = Player_GetActionStats(attacker_fp2->player_id);
                ev_hits.x2070_int = ev_reload.x2070_int;
                pl_80037BC0_inline(&acp2->hits, &ev_hits);

                if (ev_data != NULL) {
                    temp = &acp2->hits;
                    if (ev_data->x10_b0) {
                        temp->x1A8++;
                    }
                }

                attack_id2 = ev_reload.x2073;
                if (attack_id2 == 0x63) {
                    pl_8003FE40(attacker_fp2->player_id,
                                attacker_fp2->x221F_b4);
                }

                if (!ev_data->x10_b7 &&
                    acp2->attacks.by_attack_counts[attack_id2] >
                        acp2->x358_hits.by_attack_counts[attack_id2])
                {
                    ev_best.x2070_int = ev_reload.x2070_int;
                    pl_80037BC0_inline(&acp2->x358_hits, &ev_best);

                    if (ev_data != NULL) {
                        temp = &acp2->x358_hits;
                        if (ev_data->x10_b0) {
                            temp->x1A8++;
                        }
                    }

                    pl_8003DFF4(attacker_fp2->player_id,
                                attacker_fp2->x221F_b4, attack_id2);
                }

                if (attacked_from_behind) {
                    acp->x56C++;
                } else {
                    acp->x568++;
                }

                if (attack_id == 8 || attack_id == 0xB) {
                    acp->x574++;
                } else {
                    acp->x570++;
                }

                h_player = victim_fp->player_id;
                x18d4_x3 = victim_fp->dmg.x18d4.x3;
                HSD_ASSERT(0x7E, 0 <= h_player && h_player < 8);
                if (x18d4_x3 < 0x64) {
                    acp->x504[x18d4_x3] |= 1 << (u8) h_player;
                }

                pl_8003FE64(attacker_fp->player_id, attacker_fp->x221F_b4);
                pl_8003ED0C(attacker_fp->player_id, attacker_fp->x221F_b4,
                            victim_fp->player_id, victim_fp->x221F_b4,
                            victim_fp->dmg.x1830_percent);
                pl_8003EA40(attacker_fp->player_id, attacker_fp->x221F_b4,
                            victim_fp->player_id, victim_fp->x221F_b4,
                            ev_data->xC);
                pl_800403FC(attacker_fp->player_id, attacker_fp->x221F_b4,
                            victim_fp->player_id, victim_fp->x221F_b4,
                            victim_fp->dmg.x18d4.x3);
                pl_80040FBC(attacker_fp->player_id, attacker_fp->x221F_b4,
                            victim_fp->player_id, victim_fp->x221F_b4,
                            victim_fp->dmg.x18d4.x3);
            }
        }
    }

    fn_80037F00((HSD_GObj**) attacker_fp, victim_fp, ev_data,
                attacked_from_behind, source_ply);
}

void pl_800384DC(HSD_GObj* gobj, int arg1, void* arg2)
{
    Fighter* fp;
    plActionStats* acp;
    u8 attack_id;
    ft_800898B4_t* ev_data;
    union Struct2070 ev;
    union Struct2070 ev2;
    union Struct2070 ev3;
    union Struct2070 ev4;
    PAD_STACK(16);

    fp = GET_FIGHTER(gobj);
    ev_data = arg2;
    ev.x2070_int = arg1;

    if (ev.x2073 != 0 && ev.x2073 < 0x64) {
        struct plAttackStats* temp;

        ev2.x2070_int = ev.x2070_int;
        acp = Player_GetActionStats(fp->player_id);
        ev3.x2070_int = ev.x2070_int;
        pl_80037BC0_inline(&acp->hits, &ev3);

        if (ev_data != NULL) {
            temp = &acp->hits;
            if (ev_data->x10_b0) {
                temp->x1A8++;
            }
        }

        attack_id = ev2.x2073;
        if (attack_id == 0x63) {
            pl_8003FE40(fp->player_id, fp->x221F_b4);
        }

        if (!ev_data->x10_b7 &&
            acp->attacks.by_attack_counts[attack_id] >
                acp->x358_hits.by_attack_counts[attack_id])
        {
            ev4.x2070_int = ev.x2070_int;
            pl_80037BC0_inline(&acp->x358_hits, &ev4);

            if (ev_data != NULL) {
                temp = &acp->x358_hits;
                if (ev_data->x10_b0) {
                    temp->x1A8++;
                }
            }

            pl_8003DFF4(fp->player_id, fp->x221F_b4, attack_id);
        }
    }

    fp->x2074.x2084_b7 = 1;
}

bool pl_80038628(HSD_GObj* gobj, int kind)
{
    Fighter* fp;

    HSD_ASSERT(0x1A1, kind >= 1 && kind <= 0x10);
    fp = GET_FIGHTER(gobj);
    if (pl_803BCE70[kind - 1] == -1) {
        return true;
    }
    if (ftData_80085FD4(fp, pl_803BCE70[kind - 1])->x8 != 0) {
        return true;
    }
    return false;
}
