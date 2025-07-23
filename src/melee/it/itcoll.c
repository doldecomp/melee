#include <platform.h>

#include "it/itcoll.h"

#include "inlines.h"
#include "types.h"

#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_0881.h"
#include "ft/ftchangeparam.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ftCommon/ftCo_DownAttack.h"
#include "gm/gm_unsplit.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbcollision.h"
#include "lb/lbvector.h"

#include <math.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/random.h>
#include <baselib/state.h>
#include <baselib/tev.h>

// static s8 it_803F1360[0x16] = "damage log over %d!!\n";
// static s8 it_803F1378[9] = "itcoll.c";
static u32 it_803F1384[20] = {
    /* unable to generate initializer: unknown type */
    1000, // .4byte 0x000003E8
    1002, // .4byte 0x000003EA
    1001, // .4byte 0x000003E9
    1004, // .4byte 0x000003EC
    1145, // .4byte 0x00000479
    1005, // .4byte 0x000003ED
    0,    // .4byte 0xFFFFFFFF
    0,    // .4byte 0xFFFFFFFF
    0,    // .4byte 0xFFFFFFFF
    1000, // .4byte 0x000003E8
    1000, // .4byte 0x000003E8
    0,    // .4byte 0xFFFFFFFF
    0,    // .4byte 0xFFFFFFFF
    1046, // .4byte 0x00000416
    0,    // .4byte 0xFFFFFFFF
    0,    // .4byte 0xFFFFFFFF
    0,    // .4byte NULL
    // "item hit num over!\n", // .asciz "item hit num over!\n"
    // // .balign 4
    // "item can't init hit!\n", // .asciz "item can't init hit!\n"
    // // .balign 4
    // "item dynamics hit num over!\n", // .asciz "item dynamics hit num
    // over!\n"
};

// static s8 it_804D5170 = "0";
// static s8 it_804D5174[7] = "jobj.h";
// static s8 it_804D517C[5] = "jobj";
// extern u32 it_804D6D18;
extern u8 it_804D6D1C;
// static f32 it_804DC6C8 = 0.0;
// static f32 it_804DC6D0[2] = { 176.0, -0.0 };
// static f32 it_804DC6D8 = 0.5;
// static f32 it_804DC6DC = -1.0;
// static f32 it_804DC6E0 = 1.0;
// static f32 it_804DC6E4 = 0x7F7FFFFF;
// static f32 it_804DC6E8 = 0.01;
// static f32 it_804DC6F0[2] = { 176.0, 0.0 };
// static f32 it_804DC6F8 = 2 * M_PI;
// static f32 it_804DC700 = 0.001;
// static f32 it_804DC704 = 0.999;

// struct LogEntry {
//     s32 x0, x4, x8, xC;
// };
// static const int n_log_entries = 15;
// static const int it_804A0E70_entries = 15;
// extern struct LogEntry it_804A0E70[n_log_entries];
extern struct HSD_ObjAllocUnk7 it_804A0E70[15];

void it_8026F9AC(s32 arg0, void* fighter, HitCapsule* hit, HurtCapsule* hurt)
{
    if (it_804D6D18 < 15U) {
        // if (it_804D6D18 < HitElement_Lipstick) { // related?
        it_804A0E70[it_804D6D18].x0 = arg0;
        it_804A0E70[it_804D6D18].x4 = fighter;
        it_804A0E70[it_804D6D18].x8 = hit;
        it_804A0E70[it_804D6D18].xC = hurt;
        it_804D6D18++;
        return;
    }
    OSReport("damage log over %d!!\n", 15U);
    __assert("itcoll.c", 105U, "0");
}

void it_8026FA2C(Item* arg_item0, HitCapsule* arg_hit, s32 arg2,
                 Item* arg_item3, bool arg_chk)
{
    HitCapsule* hit;
    u32 index;
    u8* cnt;

    index = 0U;
    cnt = &it_804D6D1C;
    while (index < 4U) {
        hit = &arg_item0->x5D4_hitboxes[index].hit;
        if ((hit->state != HitCapsule_Disabled) && (hit->x4 == arg_hit->x4) &&
            lbColl_80008688(hit, arg2, arg_item3) && (arg_chk))
        {
            *cnt = 0U;
        }
        index++;
        cnt++;
    }
}

void it_8026FAC4(Item* arg_item0, HitCapsule* arg_hit, s32 arg2, void* arg3,
                 bool chk)
{
    HSD_GObj* item_gobj;
    HitCapsule* hit;
    u32 index;
    u8* cnt;
    Item* item;
    PAD_STACK(4);

    if (arg_item0->xAC4_ignoreItemID != 0) {
        item_gobj = HSD_GObj_Entities->items;
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item0->xAC4_ignoreItemID) {
                index = 0U;
                // var_r24 = item;
                cnt = &it_804D6D1C;
                while (index < 4U) {
                    hit = &item->x5D4_hitboxes[index].hit;
                    if ((hit->state != HitCapsule_Disabled) &&
                        (hit->x4 == arg_hit->x4) &&
                        lbColl_80008688(hit, arg2, arg3) && chk)
                    {
                        *cnt = 0U;
                    }
                    index++;
                    cnt++;
                }
            }
            item_gobj = item_gobj->next;
        }
        return;
    }
    index = 0U;
    cnt = &it_804D6D1C;
    while (index < 4U) {
        hit = &arg_item0->x5D4_hitboxes[index].hit;
        if ((hit->state != HitCapsule_Disabled) && (hit->x4 == arg_hit->x4) &&
            lbColl_80008688(hit, arg2, arg3) && chk)
        {
            *cnt = 0U;
        }
        index++;
        cnt++;
    }
}

void it_8026FC00(Item* arg_item, HitCapsule* arg_hit, s32 arg2, Fighter* arg3)
{
    HSD_GObj* item_gobj;
    HitCapsule* hit;
    u32 index;
    Item* item;
    PAD_STACK(8);

    if (arg_item->xAC4_ignoreItemID != 0U) {
        item_gobj = HSD_GObj_Entities->items;
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item->xAC4_ignoreItemID) {
                index = 0U;
                while (index < 4U) {
                    hit = &item->x5D4_hitboxes[index].hit;
                    if ((hit->state != HitCapsule_Disabled) &&
                        (hit->x4 == arg_hit->x4))
                    {
                        lbColl_80008820(hit, arg2, arg3);
                    }
                    index++;
                }
            }
            item_gobj = item_gobj->next;
        }
        return;
    }
    index = 0U;
    while (index < 4U) {
        hit = &arg_item->x5D4_hitboxes[index].hit;
        if ((hit->state != HitCapsule_Disabled) && (hit->x4 == arg_hit->x4)) {
            lbColl_80008820(hit, arg2, arg3);
        }
        index++;
    }
}

void it_8026FCF8(Item* arg_item, HitCapsule* arg_hit)
{
    HSD_GObj* item_gobj;
    HitCapsule* hit;
    bool chk;
    u32 index;
    Item* item;
    PAD_STACK(4);

#if 0
    if (arg_item->xAC4_ignoreItemID != 0U) {
        item_gobj = HSD_GObj_Entities->items;
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item->xAC4_ignoreItemID) {
                index = 0U;
                chk = false;
                while (!chk && index < 4U) {
                    hit = &item->x5D4_hitboxes[index].hit;
                    if ((hit != arg_hit) && (hit->state != HitCapsule_Disabled) && (hit->x4 == arg_hit->x4)) {
                        lbColl_CopyHitCapsule(hit, arg_hit);
                        chk = true;
                        return;
                    }
                    index++;
                }
                if (chk) {
                    return;
                }
            }
            item_gobj = item_gobj->next;
        }
    }
    lbColl_80008440(arg_hit);
    return;
#elif 0
    if (arg_item->xAC4_ignoreItemID != 0U) {
        item_gobj = HSD_GObj_Entities->items;
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item->xAC4_ignoreItemID) {
                chk = false;
                for (index = 0U; index < 4U; index++) {
                    hit = &item->x5D4_hitboxes[index].hit;
                    if ((hit != arg_hit) &&
                        (hit->state != HitCapsule_Disabled) &&
                        (hit->x4 == arg_hit->x4))
                    {
                        lbColl_CopyHitCapsule(hit, arg_hit);
                        return;
                    }
                }
            }
            item_gobj = item_gobj->next;
        }
    }
    lbColl_80008440(arg_hit);
    return;
#else
    if (arg_item->xAC4_ignoreItemID != 0U) {
        item_gobj = HSD_GObj_Entities->items;
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item->xAC4_ignoreItemID) {
                index = 0U;
                hit = &item->x5D4_hitboxes[index].hit;
                if ((hit != arg_hit) && (hit->state != HitCapsule_Disabled) &&
                    (hit->x4 == arg_hit->x4))
                {
                    lbColl_CopyHitCapsule(hit, arg_hit);
                    chk = true;
                } else {
                    index++;
                    hit = &item->x5D4_hitboxes[index].hit;
                    if ((hit != arg_hit) &&
                        (hit->state != HitCapsule_Disabled) &&
                        (hit->x4 == arg_hit->x4))
                    {
                        lbColl_CopyHitCapsule(hit, arg_hit);
                        chk = true;
                    } else {
                        index++;
                        hit = &item->x5D4_hitboxes[index].hit;
                        if ((hit != arg_hit) &&
                            (hit->state != HitCapsule_Disabled) &&
                            (hit->x4 == arg_hit->x4))
                        {
                            lbColl_CopyHitCapsule(hit, arg_hit);
                            chk = true;
                        } else {
                            index++;
                            hit = &item->x5D4_hitboxes[index].hit;
                            if ((hit != arg_hit) &&
                                (hit->state != HitCapsule_Disabled) &&
                                (hit->x4 == arg_hit->x4))
                            {
                                lbColl_CopyHitCapsule(hit, arg_hit);
                                chk = true;
                            } else {
                                chk = false;
                            }
                        }
                    }
                }
                if (chk) {
                    return;
                }
            }
            item_gobj = item_gobj->next;
        }
    }
    lbColl_80008440(arg_hit);
    return;
#endif
}

void it_8026FE68(Item* arg_item0, HitCapsule* hit1, Item* arg_item2,
                 HitCapsule* hit3)
{
    Vec3 sp48;
    s32 var_r26;
    HSD_GObj* item_gobj;
    f32 dmg3;
    f32 dmg1;
    f32 vel_x;
    f32 vel_x_mag;
    f32 pos_x = 0.0f;
    f32 dir;
    s32 dmg3_int;
    s32 dmg1_int;
    Item* item;
    PAD_STACK(16);

    sp48.x = 0.5f * (hit1->hurt_coll_pos.x + hit3->hurt_coll_pos.x);
    sp48.y = 0.5f * (hit1->hurt_coll_pos.y + hit3->hurt_coll_pos.y);
    sp48.z = 0.5f * (hit1->hurt_coll_pos.z + hit3->hurt_coll_pos.z);
    dmg3 = hit3->damage;
    if (((s32) dmg3 - it_804D6D28->xB4) < (s32) hit1->damage) {
        dmg3_int = dmg3;
        if (hit3->x41_b5) {
            var_r26 = 4;
        } else {
            var_r26 = 3;
        }
        if (arg_item2->xAC4_ignoreItemID != 0U) {
            item_gobj = HSD_GObj_Entities->items;
            while (item_gobj != NULL) {
                item = GET_ITEM(item_gobj);
                if (item->xAC4_ignoreItemID == arg_item2->xAC4_ignoreItemID) {
                    it_8026FA2C(item, hit3, var_r26, arg_item0, true);
                }
                item_gobj = item_gobj->next;
            }
        } else {
            it_8026FA2C(arg_item2, hit3, var_r26, arg_item0, true);
        }
        if (dmg3_int > arg_item2->xC48) {
            arg_item2->xC48 = dmg3_int;
            arg_item2->xCF4_fighterGObjUnk = NULL;
            arg_item2->xC38 = arg_item2->kind;
            arg_item2->xCD4 = arg_item2->pos;
            vel_x = arg_item2->x40_vel.x;
            if (vel_x < 0.0f) {
                vel_x_mag = -vel_x;
            } else {
                vel_x_mag = vel_x;
            }
            if (vel_x_mag < it_804D6D28->xD4) {
                pos_x = arg_item2->pos.x;
                if (pos_x > arg_item0->pos.x) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
            } else if (vel_x < 0.0f) {
                dir = -1.0f;
            } else {
                dir = 1.0f;
            }
            arg_item2->xCB8_outDamageDirection = dir;
        }
        // efSync_Spawn(0x41C, arg_item2->entity, &sp48, pos_x);
        efSync_Spawn(0x41C, arg_item2->entity, &sp48, arg_item0);
    }
    dmg1 = hit1->damage;
    if (((s32) dmg1 - it_804D6D28->xB4) < (s32) hit3->damage) {
        dmg1_int = dmg1;
        if (hit3->x41_b5) {
            var_r26 = 4;
        } else {
            var_r26 = 3;
        }
        if (arg_item0->xAC4_ignoreItemID != 0U) {
            item_gobj = HSD_GObj_Entities->items;
            while (item_gobj != NULL) {
                item = GET_ITEM(item_gobj);
                if (item->xAC4_ignoreItemID == arg_item0->xAC4_ignoreItemID) {
                    it_8026FA2C(item_gobj->user_data, hit1, var_r26, arg_item2,
                                false);
                }
                item_gobj = item_gobj->next;
            }
        } else {
            it_8026FA2C(arg_item0, hit1, var_r26, arg_item2, false);
        }
        if (dmg1_int > arg_item0->xC48) {
            arg_item0->xC48 = dmg1_int;
            arg_item0->xCF4_fighterGObjUnk = NULL;
            arg_item0->xC38 = arg_item2->kind;
            arg_item0->xCD4 = arg_item2->pos;
            vel_x = arg_item0->x40_vel.x;
            if (vel_x < 0.0f) {
                vel_x_mag = -vel_x;
            } else {
                vel_x_mag = vel_x;
            }
            if (vel_x_mag < it_804D6D28->xD4) {
                pos_x = arg_item0->pos.x;
                if (pos_x > arg_item2->pos.x) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
            } else if (vel_x < 0.0f) {
                dir = -1.0f;
            } else {
                dir = 1.0f;
            }
            arg_item0->xCB8_outDamageDirection = dir;
        }
        // efSync_Spawn(0x41C, arg_item2->entity, &sp48, pos_x);
        efSync_Spawn(0x41C, arg_item2->entity, &sp48, arg_item0);
    }
}

void it_802701BC(Item_GObj* arg_item_gobj)
{
    HSD_GObj* fighter_gobj;
    HitCapsule* arg_hit;
    HurtCapsule* hurt;
    f32 pos_x;
    Fighter* fighter;
    Item* arg_item;
    u32 it_hit_index;
    u32 ft_hit_index;
    // Vec2* str;
    PAD_STACK(4);

    arg_item = GET_ITEM((HSD_GObj*) arg_item_gobj);
    arg_item->grab_victim = 0;
    arg_item->xD10 = 3.4028235e38f;
    fighter_gobj = HSD_GObj_Entities->fighters;
    while (fighter_gobj != NULL) {
        fighter = GET_FIGHTER((HSD_GObj*) fighter_gobj);
        if ((!ftLib_80086FD4(fighter_gobj, arg_item->owner) ||
             arg_item->xDCD_flag.b5) &&
            (!gm_8016B168() || gm_8016B0D4() || arg_item->xDCD_flag.b6 ||
             (arg_item->x20_team_id != fighter->team)) &&
            !fighter->x2219_b1 && !fighter->x222A_flag.b0 &&
            (fighter->x1988 == 0) && (fighter->x198C == 0) &&
            !fighter->x221D_b6 && !(fighter->x1A6A & arg_item->xD08))
        {
            it_hit_index = 0U;
            while (it_hit_index < 4U) {
                arg_hit = &arg_item->x5D4_hitboxes[it_hit_index].hit;
                // str = (Vec2*) &arg_item->x5D4_hitboxes[it_hit_index];
                // arg_hit = (HitCapsule*) &str->x;
                if ((arg_hit->state != HitCapsule_Disabled) &&
                    (arg_hit->element == HitElement_Catch) &&
                    ((arg_hit->x40_b2 && (fighter->ground_or_air == GA_Air)) ||
                     (arg_hit->x40_b3 &&
                      (fighter->ground_or_air == GA_Ground))) &&
                    !lbColl_8000ACFC(fighter, arg_hit))
                {
                    ft_hit_index = 0U;
                    while (ft_hit_index < fighter->hurt_capsules_len) {
                        hurt = &fighter->hurt_capsules[ft_hit_index];
                        if (hurt->is_grabbable &&
                            lbColl_80007ECC(
                                arg_hit, &fighter->hurt_capsules[ft_hit_index],
                                ftCommon_8007F804(fighter), arg_item->scl,
                                fighter->x34_scale.y, fighter->cur_pos.z))
                        {
                            it_8026FAC4(arg_item, arg_hit, 0, fighter, 0);
                            pos_x = fighter->cur_pos.x - arg_item->pos.x;
                            if (pos_x < 0.0f) {
                                pos_x = -pos_x;
                            }
                            if (pos_x < arg_item->xD10) {
                                arg_item->grab_victim = arg_item->atk_victim =
                                    fighter->gobj;
                                arg_item->xDD0_flag.b1 = 1;
                                arg_item->xD10 = pos_x;
                            }
                            return;
                        }
                        ft_hit_index++;
                    }
                }
                it_hit_index++;
            }
        }
        fighter_gobj = fighter_gobj->next;
    }
}

void it_802703E8(Item_GObj* arg_item_gobj)
{
    // HSD_GObj* thrown_hitbox_owner_gobj;
    HSD_GObj* fighter_gobj;
    HitCapsule* hit;
    HurtCapsule* hurt;
    // s32 temp_r0_2;
    // s32 temp_r0_3;
    s32 dmg;
    ItemKind kind;
    HSD_GObj* arg_item_owner_gobj;
    u32 hurt_index;
    u32 hit_index;
    u8 ft_team;
    Item* arg_item;
    Fighter* fighter;

    arg_item = arg_item_gobj->user_data;
    if (arg_item->xAC8_hurtboxNum != 0) {
        fighter_gobj = HSD_GObj_Entities->fighters;
        while (fighter_gobj != NULL) {
            arg_item_owner_gobj = arg_item->owner;
            fighter = fighter_gobj->user_data;
            // thrown_hitbox_owner_gobj = fighter->x1064_thrownHitbox.owner;
            if (((arg_item_owner_gobj != fighter_gobj) ||
                 arg_item->xDCE_flag.b0) &&
                ((fighter->x1064_thrownHitbox.owner != NULL) ||
                 (fighter->x1064_thrownHitbox.owner != arg_item_owner_gobj) ||
                 arg_item->xDCE_flag.b0))
            {
                // thrown_hitbox_owner_gobj =
                // fighter->x1064_thrownHitbox.owner;
                if (fighter->x1064_thrownHitbox.owner != NULL) {
                    ft_team =
                        ftLib_80086EB4(fighter->x1064_thrownHitbox.owner);
                } else {
                    ft_team = fighter->team;
                }
                if (!gm_8016B168() || gm_8016B0D4() ||
                    arg_item->xDCE_flag.b1 ||
                    (ft_team != arg_item->x20_team_id))
                {
                    hit_index = 0U;
                    // var_r31 = fighter;
                    while (hit_index < 4U) {
                        hit = &fighter->x914[hit_index];
                        if ((hit->state != HitCapsule_Disabled) &&
                            (hit->element != HitElement_Catch) &&
                            (hit->x42_b7 == 1) &&
                            ((hit->x40_b2 &&
                              (arg_item->ground_or_air == GA_Air)) ||
                             (hit->x40_b3 &&
                              (arg_item->ground_or_air == GA_Ground))) &&
                            !lbColl_8000ACFC(arg_item, hit) &&
                            (arg_item->xD0C != 2))
                        {
                            hurt_index = 0;
                            // var_r21_2 = arg_item + (0 * 0x44);
                            while (hurt_index < arg_item->xAC8_hurtboxNum) {
                                hurt = &arg_item->xACC_itemHurtbox[hurt_index];
                                if (lbColl_8000805C(hit, hurt, NULL, 0,
                                                    fighter->x34_scale.y,
                                                    arg_item->scl, 0.0f))
                                {
                                    if (hit->element != HitElement_Inert) {
                                        ftColl_80076808(fighter, hit, 0,
                                                        arg_item, 0);
                                        dmg = hit->damage;
                                        fighter->dmg.x1914 = dmg;
                                        arg_item->xCA0 += dmg;
                                        if (dmg > arg_item->xCA4) {
                                            arg_item->xCA4 = dmg;
                                        }
                                        // it_8026F9AC(1, fighter, hit,
                                        // arg_item, hurt);
                                        it_8026F9AC(1, fighter, hit, hurt);
                                        it_8027B378(
                                            (Fighter_GObj*) fighter->gobj,
                                            (Item_GObj*) arg_item->entity,
                                            (f32) dmg);
                                        kind = arg_item->kind;
                                        if ((kind == Pokemon_Random) &&
                                            (arg_item->xDD4_itemVar.pokemon
                                                 .x0 == 7) &&
                                            ((hit->sfx_kind == 1U) ||
                                             (hit->sfx_kind == 2U)))
                                        {
                                            lbAudioAx_800237A8(0x61A87, 0x7FU,
                                                               0x40U);
                                        } else if ((kind != Pokemon_Random) ||
                                                   (arg_item->xDD4_itemVar
                                                        .pokemon.x0 != 8) ||
                                                   ((hit->sfx_kind != 1U) &&
                                                    (hit->sfx_kind != 2U)))
                                        {
                                            lbColl_80005BB0(hit, -1);
                                        }
                                    } else {
                                        fighter->unk_gobj =
                                            (HSD_GObj*) arg_item_gobj;
                                    }
                                    goto block_cf0;
                                } else {
                                    // var_r21_2 += 0x44;
                                    hurt_index++;
                                }
                            }
                        }
                    block_cf0:
                        hit_index++;
                        // var_r31 += 0x138;
                    }
                }
            }
            fighter_gobj = fighter_gobj->next;
        }
    }
}

void it_802706D0(Item_GObj* arg_item_gobj)
{
    HSD_GObj* item_gobj;
    HitCapsule* hit;
    HitCapsule* arg_hit;
    // HitCapsule* temp_r4;
    f32 pos_x;
    f32 dir;
    f32 pos_x_mag;
    // s32 sfx_kind;
    // s32 temp_r0_2;
    s32 dmg;
    ItemKind kind;
    bool chk2; // r17
    s32 var_r28;
    bool chk;
    s32 var_r5;
    // u32 temp_r3_2;
    // u32 hit_index; r18
    u32 arg_hurt_index;
    u32 arg_hit_index;
    u32 hit_index;
    // u32 var_r22_3;
    u8* cnt;
    // u8* var_r22_2;
    Item* item;
    Item* arg_item;
    // void* var_r16;
    HurtCapsule* arg_hurt;
    // void* var_r21;
    // void* var_r23;
    // void* var_r23_2;

    // var_r28 = saved_reg_r28;
    chk = false;
    arg_item = GET_ITEM((HSD_GObj*) arg_item_gobj);
    item_gobj = HSD_GObj_Entities->items;
    // loop_97:
    while (item_gobj != NULL) {
        item = item_gobj->user_data;
        if ((HSD_GObj*) arg_item_gobj == item_gobj) {
            chk = true;
        } else if (((arg_item->owner != NULL) || (item->owner != NULL) ||
                    item->xDCD_flag.b7 || arg_item->xDCE_flag.b2) &&
                   (!ftLib_80086960(item->owner) ||
                    !ftLib_80086960(arg_item->owner) ||
                    !ftLib_80086FD4(arg_item->owner, item->owner) ||
                    item->xDCD_flag.b7 || arg_item->xDCE_flag.b2) &&
                   (!gm_8016B168() || gm_8016B0D4() || item->xDCD_flag.b6 ||
                    arg_item->xDCE_flag.b1 ||
                    (item->x20_team_id != arg_item->x20_team_id)))
        {
            if (chk && !arg_item->xDD0_flag.b1) {
                // var_r23 = arg_item;
                var_r28 = 0;
                arg_hit_index = 0U;
                cnt = &it_804D6D1C;
                while (arg_hit_index < 4U) {
                    arg_hit = &arg_item->x5D4_hitboxes[arg_hit_index].hit;
                    if ((arg_hit->state != HitCapsule_Disabled) &&
                        (arg_hit->element != HitElement_Catch) &&
                        ((arg_hit->x40_b2 &&
                          (item->ground_or_air == GA_Air)) ||
                         (arg_hit->x40_b3 &&
                          (item->ground_or_air == GA_Ground))) &&
                        !lbColl_8000ACFC(item, arg_hit))
                    {
                        *cnt = 1;
                        var_r28++;
                    } else {
                        *cnt = 0;
                    }
                    arg_hit_index++;
                    // arg_item += 0x13C;
                    cnt++;
                }
            }
            hit_index = 0U;
            // var_r21 = item;
            while (hit_index < 4U) {
                hit = &item->x5D4_hitboxes[hit_index].hit;
                if ((hit->state != HitCapsule_Disabled) &&
                    (hit->x42_b7 == 1) &&
                    ((hit->x40_b2 && (arg_item->ground_or_air == GA_Air)) ||
                     (hit->x40_b3 &&
                      (arg_item->ground_or_air == GA_Ground))) &&
                    !lbColl_8000ACFC(arg_item, hit))
                {
                    if (chk && !arg_item->xDD0_flag.b1 && (var_r28 != 0)) {
                        // var_r23_2 = arg_item;
                        chk2 = false;
                        arg_hit_index = 0U;
                        cnt = &it_804D6D1C;
                        // loop_42:
                        while (arg_hit_index < 4U) {
                            if (*cnt != 0) {
                                // temp_r3_2 = hit->element;
                                arg_hit =
                                    &arg_item->x5D4_hitboxes[arg_hit_index]
                                         .hit;
                                if ((hit->element == HitElement_Inert) ||
                                    (arg_hit->element == HitElement_Inert))
                                {
                                    if ((hit->element != arg_hit->element) &&
                                        lbColl_80007AFC(hit, arg_hit,
                                                        item->scl,
                                                        arg_item->scl))
                                    {
                                        if (hit->element == HitElement_Inert) {
                                            item->xDCE_flag.b6 = 1;
                                            item->toucher =
                                                (HSD_GObj*) arg_item_gobj;
                                        } else {
                                            item->xDCE_flag.b6 = 1;
                                            arg_item->toucher = item->entity;
                                        }
                                        chk2 = true;
                                        goto block_1080;
                                        // } else {
                                        //     goto block_55;
                                    }
                                } else if ((hit->x40_b0 == 1) &&
                                           (arg_hit->x40_b0 == 1) &&
                                           lbColl_80007AFC(hit, arg_hit,
                                                           item->scl,
                                                           arg_item->scl))
                                {
                                    it_8026FE68(item, hit, arg_item, arg_hit);
                                    chk2 = true;
                                    goto block_1080;
                                    // } else {
                                    //     goto block_55;
                                }
                                // } else {
                                // block_55:
                            }
                            arg_hit_index++;
                            cnt++;
                            // arg_item += 0x13C;
                        }
                        // goto loop_42;
                        // }
                        // }
                    block_1080:
                        if (!chk2) {
                            goto block_57;
                        }
                    } else {
                    block_57:
                        if (arg_item->xAC8_hurtboxNum != 0) {
                            if (hit->element == HitElement_Inert) {
                                arg_hurt_index = 0U;
                                // loop_63:
                                while (arg_hurt_index <
                                       arg_item->xAC8_hurtboxNum)
                                {
                                    arg_hurt = &arg_item->xACC_itemHurtbox
                                                    [arg_hurt_index];
                                    if (lbColl_80008248(hit, arg_hurt, NULL,
                                                        item->scl,
                                                        arg_item->scl, 0.0f))
                                    {
                                        item->xDCE_flag.b6 = 1;
                                        item->toucher =
                                            (HSD_GObj*) arg_item_gobj;
                                    }
                                    // arg_hurt += 0x44;
                                    arg_hurt_index++;
                                    // goto loop_63;
                                }
                            } else if (arg_item->xD0C != 2) {
                                arg_hurt_index = 0;
                                // var_r16 = arg_item + (0 * 0x44);
                                // loop_94:
                                while (arg_hurt_index <
                                       arg_item->xAC8_hurtboxNum)
                                {
                                    arg_hurt = &arg_item->xACC_itemHurtbox
                                                    [arg_hurt_index];
                                    if (lbColl_8000805C(hit, arg_hurt, NULL, 0,
                                                        item->scl,
                                                        arg_item->scl, 0.0f))
                                    {
                                        if (hit->x41_b4) {
                                            var_r5 = 8;
                                        } else {
                                            var_r5 = 0;
                                        }
                                        it_8026FAC4(item, hit, var_r5,
                                                    arg_item, 0);
                                        pos_x = item->x40_vel.x;
                                        if (pos_x < 0.0f) {
                                            pos_x_mag = -pos_x;
                                        } else {
                                            pos_x_mag = pos_x;
                                        }
                                        if (pos_x_mag < it_804D6D28->xD4) {
                                            if (item->pos.x > arg_item->pos.x)
                                            {
                                                dir = -1.0f;
                                            } else {
                                                dir = 1.0f;
                                            }
                                        } else if (pos_x < 0.0f) {
                                            dir = -1.0f;
                                        } else {
                                            dir = 1.0f;
                                        }
                                        item->xCB8_outDamageDirection = dir;
                                        dmg = hit->damage;
                                        item->xC34_damageDealt = dmg;
                                        item->xCF4_fighterGObjUnk = NULL;
                                        item->xC38 = arg_item->kind;
                                        item->xCD4 = arg_item->pos;
                                        arg_item->xCA0 = arg_item->xCA0 + dmg;
                                        if (dmg > arg_item->xCA4) {
                                            arg_item->xCA4 = dmg;
                                        }
                                        // it_8026F9AC(2, item, hit, arg_item,
                                        // arg_hurt);
                                        it_8026F9AC(2, item, hit, arg_hurt);
                                        it_8027B408(
                                            (Item_GObj*) item->entity,
                                            (Item_GObj*) arg_item->entity,
                                            dmg);
                                        kind = arg_item->kind;
                                        // sfx_kind = hit->sfx_kind;
                                        if ((kind == Pokemon_Random) &&
                                            (arg_item->xDD4_itemVar.pokemon
                                                 .x0 == 7) &&
                                            ((hit->sfx_kind == 1U) ||
                                             (hit->sfx_kind == 2U)))
                                        {
                                            lbAudioAx_800237A8(0x61A87, 0x7FU,
                                                               0x40U);
                                        } else if ((kind != Pokemon_Random) ||
                                                   (arg_item->xDD4_itemVar
                                                        .pokemon.x0 != 8) ||
                                                   ((hit->sfx_kind != 1U) &&
                                                    (hit->sfx_kind != 2U)))
                                        {
                                            lbColl_80005BB0(hit, -1);
                                        }
                                        goto block_12f4;
                                    } else {
                                        // arg_hurt += 0x44;
                                        arg_hurt_index++;
                                        // goto loop_94;
                                    }
                                    // goto block_12f4;
                                }
                            }
                        }
                    }
                }
            block_12f4:
                hit_index++;
                // item += 0x13C;
            }
        }
        item_gobj = item_gobj->next;
        // goto loop_97;
    }
}

f32 it_80270CD8(Item* arg_item, HitCapsule* arg_hit)
{
    // f32 temp_f0;
    // f32 temp_f2;
    f32 temp_f4;
    f32 ret_val;
    ItemAttr* attr;
    PAD_STACK(8);

    attr = arg_item->xCC_item_attr;
    if (arg_hit->x28 != 0) {
        // temp_f2 = it_804D6D28->x80_float[10];
        ret_val =
            (0.01f * arg_hit->x24 *
             ((it_804D6D28->x80_float[11] *
               (attr->x1C_damage_mul *
                ((it_804D6D28->x80_float[10] * it_804D6D28->x80_float[8]) +
                 (it_804D6D28->x80_float[9] *
                  (it_804D6D28->x80_float[10] * arg_hit->x28))))) +
              it_804D6D28->x80_float[12])) +
            arg_hit->x2C;
    } else {
        temp_f4 = arg_item->xC9C + (f32) arg_item->xCA0;
        ret_val =
            (0.01f * arg_hit->x24 *
             ((it_804D6D28->x80_float[11] *
               (attr->x1C_damage_mul *
                ((it_804D6D28->x80_float[8] * temp_f4) +
                 (it_804D6D28->x80_float[9] * (arg_hit->damage * temp_f4))))) +
              it_804D6D28->x80_float[12])) +
            arg_hit->x2C;
    }
    // temp_f0 = it_804D6D28->x80_float[7];
    if (ret_val >= it_804D6D28->x80_float[7]) {
        ret_val = it_804D6D28->x80_float[7];
    }
    return ret_val;
}

void it_80270E30(Item_GObj* arg_item_gobj)
{
    Vec3 sp2C;
    f32 sp18;
    HSD_ObjAllocUnk7* var_r29;
    HSD_GObj* item_owner_gobj;
    f32 temp_f0;
    // f32 temp_f2;
    f32 vel_x;
    f32 temp_f7;
    f32 dir;
    f32 var_f1;
    f32 vel_x_mag;
    f32 var_f27;
    f32 var_f28;
    f32 var_f2;
    f32 var_f3;
    f32 var_f4;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 element;
    // u32 temp_r0;
    u32 index2;
    u32 index;
    Item* item;
    Item* arg_item;
    HSD_ObjAllocUnk7* temp_r29;
    HitCapsule* hit2;
    ItemAttr* attr;
    Vec3* hurt_coll_pos;
    Fighter* fighter;
    HitCapsule* hit;
    Item* arg_item2;
    PAD_STACK(24);

    // var_r26 = saved_reg_r26;
    if (it_804D6D18 != 0U) {
        arg_item = arg_item_gobj->user_data;
        var_f28 = -1.0f;
        index = 0;
        var_r29 = &it_804A0E70[index];
        while (index < it_804D6D18) {
            hit = var_r29->x8;
            attr = arg_item->xCC_item_attr;
            // temp_r0 = hit->x28;
            if (hit->x28 != 0) {
                // temp_f2 = it_804D6D28->x80_float[10];
                var_f2 =
                    attr->x1C_damage_mul *
                    ((it_804D6D28->x80_float[10] * it_804D6D28->x80_float[8]) +
                     (it_804D6D28->x80_float[9] *
                      (it_804D6D28->x80_float[10] * hit->x28)));
                var_f3 = it_804D6D28->x80_float[11];
                var_f4 = 0.01f * hit->x24;
                var_f1 = (var_f3 * var_f2) + it_804D6D28->x80_float[0xC];
                var_f27 = (var_f4 * var_f1) + hit->x2C;
            } else {
                temp_f7 = arg_item->xC9C + (f32) arg_item->xCA0;
                var_f3 = it_804D6D28->x80_float[8];
                var_f4 = attr->x1C_damage_mul;
                var_f2 =
                    var_f4 * ((var_f3 * temp_f7) + (it_804D6D28->x80_float[9] *
                                                    (hit->damage * temp_f7)));
                var_f1 = (it_804D6D28->x80_float[11] * var_f2) +
                         it_804D6D28->x80_float[12];
                var_f27 = (0.01f * hit->x24 * var_f1) + hit->x2C;
            }
            temp_f0 = it_804D6D28->x80_float[7];
            if (var_f27 >= temp_f0) {
                var_f27 = temp_f0;
            }
            if (!arg_item->xDCF_flag.b1) {
                // temp_r0_2 = arg_item->hold_kind;
                if ((arg_item->hold_kind == 4) || (arg_item->hold_kind == 6)) {
                    sp18 = hit->damage;
                    hit2 = var_r29->x8;
                    arg_item2 = arg_item_gobj->user_data;
                    hurt_coll_pos = &hit2->hurt_coll_pos;
                    element = *(&it_803F1384[hit2->element]);
                    switch (element) { /* irregular */
                    case 0x3ED:
                        efSync_Spawn(element, arg_item_gobj, hurt_coll_pos,
                                     arg_item2->facing_dir, var_f1, var_f2,
                                     var_f3, var_f4);
                        break;
                    case 0x3E8:
                        efSync_Spawn(0x3E8, arg_item_gobj, hurt_coll_pos,
                                     &sp18, var_f1, var_f2, var_f3, var_f4);
                        break;
                    case 0x479:
                    case 0x416:
                    case 0x3EB:
                        efSync_Spawn(element, arg_item_gobj, hurt_coll_pos,
                                     arg_item2, var_f1, var_f2, var_f3,
                                     var_f4);
                        break;
                    }
                } else {
                    sp2C = hit->hurt_coll_pos;
                    efSync_Spawn(0x3E8, arg_item_gobj, &sp2C,
                                 var_r29->x8->damage, var_f1, var_f2, var_f3,
                                 var_f4);
                }
            }
            if (var_f27 > var_f28) {
                var_f28 = var_f27;
                index2 = index;
            }
            // var_r29 += 0x10;
            index++;
        }
        temp_r29 = &it_804A0E70[index2];
        switch (temp_r29->x0) { /* switch 1; irregular */
        case 1:
            fighter = temp_r29->x4;
            arg_item->xCB0_source_ply = (s32) fighter->player_id;
            arg_item->xCEC_fighterGObj = fighter->gobj;
            arg_item->xCF0_itemGObj = NULL;
            if (arg_item->pos.x > fighter->cur_pos.x) {
                dir = -1.0f;
            } else {
                dir = 1.0f;
            }
            arg_item->xCCC_incDamageDirection = dir;
            it_8027B4A4((Fighter_GObj*) fighter->gobj, arg_item_gobj);
            break;
        case 2:
            item = temp_r29->x4;
            item_owner_gobj = item->owner;
            if ((item_owner_gobj != NULL) && ftLib_80086960(item_owner_gobj)) {
                arg_item->xCB0_source_ply =
                    (s32) ((Fighter*) item_owner_gobj->user_data)->player_id;
                arg_item->xCEC_fighterGObj = NULL;
                arg_item->xCF0_itemGObj = item_owner_gobj;
            } else {
                arg_item->xCB0_source_ply = 6;
                arg_item->xCEC_fighterGObj = NULL;
                arg_item->xCF0_itemGObj = NULL;
            }
            arg_item->xCB4 = item->kind;
            arg_item->xCE0 = item->pos;
            vel_x = item->x40_vel.x;
            if (vel_x < 0.0f) {
                vel_x_mag = -vel_x;
            } else {
                vel_x_mag = vel_x;
            }
            if (vel_x_mag < it_804D6D28->x78_float) {
                if (arg_item->pos.x > item->pos.x) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
            } else if (vel_x < 0.0f) {
                dir = 1.0f;
            } else {
                dir = -1.0f;
            }
            arg_item->xCCC_incDamageDirection = dir;
            it_8027B508((Item_GObj*) item->entity, arg_item_gobj);
            break;
        }
        arg_item->xCAC_angle = ((HitCapsule*) temp_r29->x8)->kb_angle;
        arg_item->xCC8_knockback = var_f28;
        arg_item->xCC4 = ((HitCapsule*) temp_r29->x8)->element;
        arg_item->xDCF_flag.b6 = ((HitCapsule*) temp_r29->x8)->x43_b0;
    }
}

void it_8027129C(Item_GObj* arg_item_gobj, s32 index)
{
    s32 state;
    HitCapsule* hit;
    Item* item;

    item = arg_item_gobj->user_data;
    hit = &item->x5D4_hitboxes[index].hit;
    state = hit->state;
    switch (state) {
    case HitCapsule_Enabled:
        lb_8000B1CC(hit->jobj, &hit->b_offset, &hit->x4C);
        hit->x58 = hit->x4C;
        hit->state = HitCapsule_Unk2;
        item->xDAA_flag.b2 = 1;
        return;
    case HitCapsule_Unk2:
        hit->state = HitCapsule_Unk3;
        /* fallthrough */
    case HitCapsule_Unk3:
        hit->x58 = hit->x4C;
        lb_8000B1CC(hit->jobj, &hit->b_offset, &hit->x4C);
        /* fallthrough */
    case 4: // HitCapsule_Max:
    case HitCapsule_Disabled:
        return;
    }
}

void it_8027137C(Item_GObj* arg_item_gobj)
{
    u32 index;
    HitCapsule* hit;
    Item* arg_item;

    index = 0U;
    while (index < 4U) {
        arg_item = arg_item_gobj->user_data;
        hit = &arg_item->x5D4_hitboxes[index].hit;
        switch (hit->state) {
        case 4: // HitCapsule_Max:
        case HitCapsule_Disabled:
            break;
        case HitCapsule_Enabled:
            lb_8000B1CC(hit->jobj, &hit->b_offset, &hit->x4C);
            hit->x58 = hit->x4C;
            hit->state = HitCapsule_Unk2;
            arg_item->xDAA_flag.b2 = 1;
            break;
        case HitCapsule_Unk2:
            hit->state = HitCapsule_Unk3;
            /* fallthrough */
        case HitCapsule_Unk3:
            hit->x58 = hit->x4C;
            lb_8000B1CC(hit->jobj, &hit->b_offset, &hit->x4C);
            break;
        }
        index++;
    }
}

void it_8027146C(Item_GObj* item_gobj)
{
    u32 index;
    Item* item;
    HitCapsule* hit;

    item = item_gobj->user_data;
    index = 0U;
    while (index < 4U) {
        hit = &item->x5D4_hitboxes[index].hit;
        lbColl_80008A5C(hit);
        index++;
    }
}

void it_802714C0(Item_GObj* item_gobj)
{
    u32 index;
    Item* item;
    HurtCapsule* hurt;

    item = item_gobj->user_data;
    index = 0U;
    while (index < item->xAC8_hurtboxNum) {
        hurt = &item->xACC_itemHurtbox[index];
        hurt->skip_update_pos = 0;
        index++;
    }
    item->xDAA_flag.b1 = 1;
}

void it_80271508(Item_GObj* item_gobj, HurtCapsuleState state)
{
    u32 index;
    Item* item;
    HurtCapsule* hurt;

    item = item_gobj->user_data;
    index = 0U;
    while (index < item->xAC8_hurtboxNum) {
        hurt = &item->xACC_itemHurtbox[index];
        hurt->state = state;
        index++;
    }
}

void it_80271534(Item_GObj* item_gobj, s32 index, HurtCapsule* arg_hurt)
{
    HurtCapsule* hurt;
    Item* item;

    item = item_gobj->user_data;
    if (item->xC4_article_data->x8_hurtbox != 0U) {
        hurt = &item->xACC_itemHurtbox[index];
        hurt->a_offset = arg_hurt->a_offset;
        hurt->b_offset = arg_hurt->b_offset;
        hurt->scale = arg_hurt->scale;
    }
}

void it_80271590(Item_GObj* item_gobj, s32 index, HurtCapsule* arg_hurt)
{
    Vec3 sp18;
    HurtCapsule* hurt;
    Item* item;
    // PAD_STACK(8);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (item->xC4_article_data->x8_hurtbox != 0U) {
        hurt = &item->xACC_itemHurtbox[index];
        arg_hurt->a_offset = hurt->a_offset;
        arg_hurt->b_offset = hurt->b_offset;
        arg_hurt->scale = hurt->scale;
        return;
    }
    sp18.x = sp18.y = sp18.z = 0.0f;
    arg_hurt->a_offset = sp18;
    arg_hurt->b_offset = sp18;
    arg_hurt->scale = 0.0f;
}

void it_8027163C(Item_GObj* item_gobj)
{
    s32 bone_id;
    // s32 var_r29;
    s32 index;
    BoneDynamicsDesc* bone_dyn_desc;
    char* temp_r3;
    u32 cnt;
    // u32 var_r6;
    // DynamicsDesc* dyn_desc;
    HurtCapsule* hurt;
    ItemDynamics* it_dynams;
    ItemDynamics* it_hurtbox;
    Article* article;
    Item* item;
    // void* var_r30;
    // void* var_r4;

    item = item_gobj->user_data;
    temp_r3 = "damage log over %d!!\n";
    article = item->xC4_article_data;
    it_hurtbox = (ItemDynamics*) article->x8_hurtbox;
    it_dynams = article->x14_dynamics;
    if (it_hurtbox != NULL) {
        if (it_hurtbox->count > 2) {
            // OSReport(temp_r3 + 0x68, item);
            OSReport(temp_r3 + 0x68, item_gobj->user_data);
            __assert(temp_r3 + 0x18, 0x3F4U, "0");
        }
        // var_r30 = item;
        cnt = 0U;
        item->xAC8_hurtboxNum = it_hurtbox->count;
        // var_r29 = 0;
        index = 0;
        // loop_10:
        while (cnt < (u32) it_hurtbox->count) {
            hurt = &item->xACC_itemHurtbox[index];
            // var_r30->unkACC = 0;
            item->xACC_itemHurtbox[index].state = HurtCapsule_Enabled;
            // item->xACC_itemHurtbox[0] = NULL;
            // temp_r23 = it_hurtbox->unk4 + var_r29;
            bone_dyn_desc =
                &it_hurtbox
                     ->dyn_descs[index]; // Code indicates that a larger struct
                                         // is being iterated instead (size 32
                                         // bytes instead of 24)
            if (bone_dyn_desc->bone_id != 0) {
                if (item->xBBC_dynamicBoneTable == NULL) {
                    OSReport(temp_r3 + 0x7C);
                    __assert(temp_r3 + 0x18, 0x402U, "0");
                }
                hurt->bone =
                    item->xBBC_dynamicBoneTable->bones[bone_dyn_desc->bone_id];
            } else {
                hurt->bone = item_gobj->hsd_obj;
            }
            // var_r30 += 0x44;
            index++;
            // var_r29 += 0x20;
            cnt++;
            // hurt->a_offset = (s32) bone_dyn_desc->unk4;
            // hurt->a_offset = (Vec3) ((u8) &bone_dyn_desc->dyn_desc.data->_4
            // + 0x0);
            hurt->a_offset =
                ((HurtCapsule*) bone_dyn_desc->dyn_desc.data)->a_offset;
            // hurt->unk8 = (s32) bone_dyn_desc->unk8;
            // hurt->unkC = (s32) bone_dyn_desc->unkC;
            // hurt->b_offset = (s32) bone_dyn_desc->unk10;
            hurt->b_offset =
                ((HurtCapsule*) bone_dyn_desc->dyn_desc.data)->b_offset;
            // hurt->unk14 = (s32) bone_dyn_desc->unk14;
            // hurt->unk18 = (s32) bone_dyn_desc->unk18;
            // hurt->scale = (f32) bone_dyn_desc->unk1C;
            hurt->scale = ((HurtCapsule*) bone_dyn_desc->dyn_desc.data)->scale;
            // goto loop_10;
        }
    } else {
        item->xAC8_hurtboxNum = 0;
    }
    if (it_dynams != NULL) {
        // if ((s32) it_dynams->unk8 > 2) { // ItemDynamics is only 8 bytes
        // long?
        if ((s32) it_dynams->count > 2) {
            OSReport(temp_r3 + 0x94);
            __assert(temp_r3 + 0x18, 0x415U, "0");
        }
        cnt = 0U;
        // var_r4 = item;
        // item->xB68 = (s8) it_dynams->unk8;
        item->xB68 = (s8) it_dynams->count;
        index = 0;
        // loop_18:
        // if (cnt < (u32) it_dynams->unk8) {
        while (cnt < (u32) it_dynams->count) {
            cnt++;
            // bone_dyn_desc = it_dynams->unkC + index;
            bone_dyn_desc = &it_dynams->dyn_descs[index];
            bone_id = bone_dyn_desc->bone_id;
            // index += 0x14;
            index++;
            item->xB6C_vars[cnt].xB90 = bone_id;
            item->xB6C_vars[cnt].xB7C =
                item->xBBC_dynamicBoneTable->bones[bone_id];
            item->xB6C_vars[cnt].xB6C =
                ((AbsorbDesc*) bone_dyn_desc->dyn_desc.data)->x4_offset;
            // item->xB6C_vars[cnt].xB70 = (s32) bone_dyn_desc->dyn_desc.count;
            // var_r4->unkB74 = (s32) bone_dyn_desc->unkC;
            // item->xB6C_vars[cnt].xB74 = (s32) bone_dyn_desc->dyn_desc.pos.x;
            // var_r4->unkB78 = (f32) bone_dyn_desc->unk10;
            item->xB6C_vars[cnt].xB78 =
                ((AbsorbDesc*) bone_dyn_desc->dyn_desc.data)->x10_size;
            // var_r4 += 0x28;
            // goto loop_18;
        }
    }
}

void it_80271830(Item* item, f32 arg_angle)
{
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    Vec3 sp20;
    f32 left_pos;
    f32 top_pos;
    f32 right_pos;
    f32 bottom_pos;
    f32 angle;
    PAD_STACK(40);

    angle = arg_angle;
    sp20.x = 0.0f;
    sp20.y = 0.0f;
    sp20.z = 1.0f;
    while (angle < 0.0f) {
        // angle = (f32) ((f64) angle + 6.283185307179586);
        angle += 2 * M_PI;
    }
    // while (angle > (f32) 6.283185307179586) {
    while (angle > (2 * M_PI)) {
        // angle = (f32) ((f64) angle - 6.283185307179586);
        angle -= 2 * M_PI;
    }
    sp68.y = item->xBEC.top;
    sp68.z = 0.0f;
    sp68.x = 0.0f;
    lbVector_RotateAboutUnitAxis(&sp68, &sp20, angle);
    sp5C.y = item->xBEC.bottom;
    sp5C.z = 0.0f;
    sp5C.x = 0.0f;
    lbVector_RotateAboutUnitAxis(&sp5C, &sp20, angle);
    sp50.x = item->xBEC.right;
    sp50.z = 0.0f;
    sp50.y = 0.0f;
    lbVector_RotateAboutUnitAxis(&sp50, &sp20, angle);
    sp44.x = item->xBEC.left;
    sp44.z = 0.0f;
    sp44.y = 0.0f;
    lbVector_RotateAboutUnitAxis(&sp44, &sp20, angle);
    left_pos = sp68.x;
    if (left_pos > sp5C.x) {
    } else {
        left_pos = sp5C.x;
    }
    if (left_pos > sp50.x) {
    } else {
        left_pos = sp50.x;
    }
    if (left_pos > sp44.x) {
    } else {
        left_pos = sp44.x;
    }
    item->xBEC.left = left_pos;
    top_pos = sp68.y;
    if (top_pos > sp5C.y) {
    } else {
        top_pos = sp5C.y;
    }
    if (top_pos > sp50.y) {
    } else {
        top_pos = sp50.y;
    }
    if (top_pos > sp44.y) {
    } else {
        top_pos = sp44.y;
    }
    item->xBEC.top = top_pos;
    right_pos = sp68.x;
    if (right_pos < sp5C.x) {
    } else {
        right_pos = sp5C.x;
    }
    if (right_pos < sp50.x) {
    } else {
        right_pos = sp50.x;
    }
    if (right_pos < sp44.x) {
    } else {
        right_pos = sp44.x;
    }
    item->xBEC.right = right_pos;
    bottom_pos = sp68.y;
    if (bottom_pos < sp5C.y) {
    } else {
        bottom_pos = sp5C.y;
    }
    if (bottom_pos < sp50.y) {
    } else {
        bottom_pos = sp50.y;
    }
    if (bottom_pos < sp44.y) {
    } else {
        bottom_pos = sp44.y;
    }
    item->xBEC.bottom = bottom_pos;
}

void it_80271A58(Item_GObj* item_gobj)
{
    f32 rotate;
    Item* item;
    HSD_JObj* jobj;

    item = item_gobj->user_data;
    item->xBEC = item->xBDC;
    if ((item->facing_dir == 1.0f) && (item->xDC8_word.flags.x19 == 1)) {
        item->xBEC.left = -item->xBEC.left;
        item->xBEC.right = -item->xBEC.right;
    }
    jobj = it_802746F8(item_gobj);
    if (item->xDC8_word.flags.x17 == 0) {
        rotate = HSD_JObjGetRotationZ(jobj);
    } else if (item->xDC8_word.flags.x17 == 1) {
        rotate = HSD_JObjGetRotationX(jobj);
    } else {
        rotate = HSD_JObjGetRotationY(jobj);
    }
    it_80271830(item, rotate);
}

void it_80271B60(Item_GObj* item_gobj)
{
    // s32 sp2C;
    // f32 sp28;
    Vec3 sp24;
    HSD_ObjAllocUnk2* var_r29;
    HSD_ObjAllocUnk2* var_r30;
    f32 x_float;
    f32 x_pos;
    f32 y_pos;
    f32 x_float_mag;
    f32 dir;
    bool chk;
    u32 cnt;
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(20);

    item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
    item = GET_ITEM((HSD_GObj*) item_gobj);
    if (Item_804A0CCC.x154.b0 != 1) {
        HSD_JObjGetTranslation(item_jobj, &sp24);
        var_r30 = &Item_804A0CCC;
        var_r29 = &Item_804A0CCC;
        cnt = 0U;

        while (cnt < Item_804A0CCC.x150) {
            y_pos = var_r29->xC0_vec3_arr[cnt].y;
            x_pos = var_r29->xC0_vec3_arr[cnt].x;
            // M2C_ERROR(/* unknown instruction: cror 0x2, 0x1, 0x2 */);
            if (((y_pos + (item->xBEC.top + var_r30->ecb_arr[cnt].top)) >=
                 sp24.y) &&
                ((y_pos + (item->xBEC.bottom +
                           var_r30->ecb_arr[cnt].bottom)) <= sp24.y) &&
                ((x_pos + (item->xBEC.right + var_r30->ecb_arr[cnt].right)) <=
                 sp24.x) &&
                ((x_pos + (item->xBEC.left + var_r30->ecb_arr[cnt].left)) >=
                 sp24.x))
            {
                chk = true;
            } else {
                chk = false;
            }
            if (chk) {
                x_float = sp24.x - x_pos;
                if (x_float < 0.0f) {
                    x_float_mag = -x_float;
                } else {
                    x_float_mag = x_float;
                }
                if (x_float_mag < 0.001f) {
                    if (HSD_Randi(2) != 0) {
                        dir = 1.0f;
                    } else {
                        dir = -1.0f;
                    }
                } else if (x_float < 0.0f) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
                item->x70_nudge.x = it_804D6D28->x7C_float * dir;
                item->xDC0.word |= 1;
            }
            cnt++;
        }
    }
}

void it_80271D2C(Item_GObj* arg_item_gobj)
{
    Vec3 sp34;
    Vec3 sp28;
    HSD_GObj* item_gobj;
    f32 x_float;
    f32 x_float_mag;
    f32 dir;
    bool chk;
    HSD_JObj* item_jobj;
    Item* item;
    HSD_JObj* arg_item_jobj;
    Item* arg_item;
    PAD_STACK(24);

    arg_item_jobj = GET_JOBJ((HSD_GObj*) arg_item_gobj);
    arg_item = GET_ITEM((HSD_GObj*) arg_item_gobj);
    HSD_JObjGetTranslation(arg_item_jobj, &sp34);
    item_gobj = HSD_GObj_Entities->items;

    while (item_gobj != NULL) {
        item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
        item = GET_ITEM((HSD_GObj*) item_gobj);
        if (((HSD_GObj*) arg_item_gobj != item_gobj) &&
            !item->xDC8_word.flags.x13 && (item->ground_or_air == GA_Ground) &&
            !item->xDD1_flag.b0 &&
            ((item->hold_kind != 3) ||
             ((item->hold_kind == 3) &&
              item->xDC8_word.flags
                  .x1E)) // hold_kind 3 is open palm, facing down(?)
        )
        {
            HSD_JObjGetTranslation(item_jobj, &sp28);
            if ((sp28.y + (arg_item->xBEC.top + item->xBEC.top) >= sp34.y) &&
                (sp28.y + (arg_item->xBEC.bottom + item->xBEC.bottom) <=
                 sp34.y) &&
                (sp28.x + (arg_item->xBEC.right + item->xBEC.right) <=
                 sp34.x) &&
                (sp28.x + (arg_item->xBEC.left + item->xBEC.left) >= sp34.x))
            {
                chk = true;
            } else {
                chk = false;
            }
            if (chk) {
                x_float = sp34.x - sp28.x;
                if (x_float < 0.0f) {
                    x_float_mag = -x_float;
                } else {
                    x_float_mag = x_float;
                }
                if (x_float_mag < 0.001f) {
                    if (!item->xDC8_word.flags.x1B) {
                        if (item->x70_nudge.x < 0.0f) {
                            dir = 1.0f;
                        } else {
                            dir = -1.0f;
                        }
                    } else if (HSD_Randi(2) != 0) {
                        dir = 1.0f;
                    } else {
                        dir = -1.0f;
                    }
                } else if (x_float < 0.0f) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
                arg_item->x70_nudge.x = it_804D6D28->x7C_float * dir;
                arg_item->xDC0.word |= 2;
            }
        }
        item_gobj = item_gobj->next;
    }
}

void it_80271F78(Item_GObj* arg_item_gobj)
{
    Vec3 sp34;
    Vec3 sp28;
    HSD_GObj* item_gobj;
    f32 x_float;
    f32 x_float_mag;
    f32 dir;
    bool chk;
    HSD_JObj* item_jobj;
    HSD_JObj* arg_item_jobj;
    Item* item;
    Item* arg_item;
    PAD_STACK(24);

    arg_item_jobj = GET_JOBJ((HSD_GObj*) arg_item_gobj);
    arg_item = GET_ITEM((HSD_GObj*) arg_item_gobj);
    HSD_JObjGetTranslation(arg_item_jobj, &sp34);
    item_gobj = HSD_GObj_Entities->items;

    while (item_gobj != NULL) {
        item_jobj = GET_JOBJ((HSD_GObj*) item_gobj);
        item = GET_ITEM((HSD_GObj*) item_gobj);
        if (((HSD_GObj*) arg_item_gobj != item_gobj) &&
            !item->xDC8_word.flags.x13 && (item->ground_or_air == GA_Ground) &&
            !item->xDD1_flag.b0 && (it_8026B2B4((Item_GObj*) item_gobj) == 1))
        {
            HSD_JObjGetTranslation(item_jobj, &sp28);
            if ((sp28.y + (arg_item->xBEC.top + item->xBEC.top) == sp34.y) &&
                (sp28.y + (arg_item->xBEC.bottom + item->xBEC.bottom) <=
                 sp34.y) &&
                (sp28.x + (arg_item->xBEC.right + item->xBEC.right) <=
                 sp34.x) &&
                (sp28.x + (arg_item->xBEC.left + item->xBEC.left) >= sp34.x))
            {
                chk = true;
            } else {
                chk = false;
            }
            if (chk) {
                x_float = sp34.x - sp28.x;
                if (x_float < 0.0f) {
                    x_float_mag = -x_float;
                } else {
                    x_float_mag = x_float;
                }
                if (x_float_mag < 0.001f) {
                    if (!item->xDC8_word.flags.x1C) {
                        if (item->x70_nudge.x < 0.0f) {
                            dir = 1.0f;
                        } else {
                            dir = -1.0f;
                        }
                    } else if (HSD_Randi(2) != 0) {
                        dir = 1.0f;
                    } else {
                        dir = -1.0f;
                    }
                } else if (x_float < 0.0f) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
                arg_item->x70_nudge.x = it_804D6D28->x7C_float * dir;
                arg_item->xDC0.word |= 2;
            }
        }
        item_gobj = item_gobj->next;
    }
}

void it_802721B8(Item_GObj* item_gobj)
{
    u8 temp_r3;
    Item* item;

    item = item_gobj->user_data;
    item->x70_nudge.z = 0.0f;
    item->x70_nudge.y = 0.0f;
    item->x70_nudge.x = 0.0f;
    item->xDC0.word = 0;
    if (!item->xDC8_word.flags.x13) {
        // temp_r3 = item->unkDCB;
        if ((item->xDC8_word.flags.x1A == 1) &&
            (item->ground_or_air == GA_Ground))
        {
            if (item->xDC8_word.flags.x1C) {
                it_80271B60(item_gobj);
            }
            if (item->xDC8_word.flags.x1D) {
                it_80271D2C(item_gobj);
            }
        }
    }
    if (!item->xDC8_word.flags.x13 && (item->ground_or_air == GA_Ground) &&
        (it_8026B2B4(item_gobj) == 1))
    {
        it_80271F78(item_gobj);
    }
}

void it_80272280(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1B = 0;
}

void it_80272298(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDC8_word.flags.x1B = 1;
}

void it_802722B0(Item_GObj* item_gobj)
{
    if ((HSD_GObj*) item_gobj == HSD_GObj_Entities->items) {
        ftCo_80098634(&Item_804A0CCC);
        Item_804A0CCC.x154.b0 = 0;
    }
}

void it_80272304(Item_GObj* item_gobj)
{
    // void* temp_r4;
    u32 cnt;
    Item* item;
    // void* vars;

    cnt = 0U;
    item = item_gobj->user_data;
    // vars = temp_r30;
    while (cnt < item->xB68) {
        // vars = vars + 0xB6C;
        // vars = item->xB6C_vars[cnt];
        lb_8000B1CC(item->xB6C_vars[cnt].xB7C, &item->xB6C_vars[cnt].xB6C,
                    &item->xB6C_vars[cnt].xB84);
        // vars += 0x28;
        cnt++;
    }
}

HSD_GObj* it_8027236C(Item_GObj* arg_item_gobj)
{
    HSD_GObj* fighter_gobj;
    HSD_GObj* unk_owner_gobj;
    Item* arg_item;

    arg_item = arg_item_gobj->user_data;
    fighter_gobj = arg_item->xCEC_fighterGObj;
    if (fighter_gobj != NULL) {
        arg_item->owner = fighter_gobj;
        arg_item->x20_team_id = ftLib_80086EB4(arg_item->xCEC_fighterGObj);
    } else {
        unk_owner_gobj = arg_item->xCF0_itemGObj;
        if (unk_owner_gobj != NULL) {
            arg_item->owner = unk_owner_gobj;
            arg_item->x20_team_id = ftLib_80086EB4(arg_item->xCF0_itemGObj);
        } else {
            arg_item->owner = NULL;
            arg_item->x20_team_id = U8_MAX;
        }
    }
    it_8027B1F4(arg_item_gobj);
    return arg_item->owner;
}

HSD_GObj* it_802723FC(Item_GObj* arg_item_gobj)
{
    Item* arg_item;

    arg_item = arg_item_gobj->user_data;
    if (ftLib_80086960(arg_item->xCFC)) {
        arg_item->owner = arg_item->xCFC;
        arg_item->x20_team_id = ftLib_80086EB4(arg_item->owner);
    } else {
        arg_item->owner = NULL;
        arg_item->x20_team_id = U8_MAX;
    }
    return arg_item->owner;
}

void it_80272460(HitCapsule* hitbox, u32 damage, Item_GObj* arg_item_gobj)
{
    HSD_GObj* owner_gobj;
    u32 dmg;
    Item* arg_item;
    Fighter* owner;

    dmg = damage;
    arg_item = GET_ITEM((HSD_GObj*) arg_item_gobj);
    owner_gobj = arg_item->owner;
    if (ftLib_80086960(owner_gobj)) {
        owner = GET_FIGHTER((HSD_GObj*) owner_gobj);
        if (owner->x34_scale.y != 1.0f) {
            dmg = (0.999f + ftCo_CalcYScaledKnockback(
                                Fighter_804D6524, dmg, owner->x34_scale.y,
                                ((Vec3*) Fighter_804D6524)->y));
        }
        hitbox->unk_count = dmg;
        hitbox->damage =
            ft_80089228(owner, arg_item->xD88_attackID,
                        arg_item->xD8C_attack_instance, hitbox->unk_count);
        return;
    }
    hitbox->unk_count = dmg;
    hitbox->damage = dmg;
}
