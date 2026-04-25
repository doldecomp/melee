#include "it/itcoll.h"

#include "inlines.h"
#include "placeholder.h"
#include "types.h"

#include <platform.h>

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

/* 271830 */ static void it_80271830(Item* item, f32 arg_angle);
/* 271B60 */ static void it_80271B60(Item_GObj* item_gobj);
/* 271D2C */ static void it_80271D2C(Item_GObj* arg_item_gobj);
/* 271F78 */ static void it_80271F78(Item_GObj* arg_item_gobj);

// return true if (pos_x, pos_y), expanded by the sum of two ECBs, encloses
// target.
static inline bool itColl_chkECBOverlap(f32 pos_x, f32 pos_y, itECB* ecb_a,
                                        itECB* ecb_b, Vec3* target)
{
    f32 top = pos_y + (ecb_a->top + ecb_b->top);
    f32 bottom = pos_y + (ecb_a->bottom + ecb_b->bottom);
    f32 right = pos_x + (ecb_a->right + ecb_b->right);
    f32 left = pos_x + (ecb_a->left + ecb_b->left);
    if (top >= target->y && bottom <= target->y && right <= target->x &&
        left >= target->x)
    {
        return true;
    } else {
        return false;
    }
}

extern u8 it_804D6D1C[4];

extern DamageLogEntry it_804A0E70[15];

extern Quaternion it_803B8560;

void it_8026F9AC(s32 arg0, void* fighter, HitCapsule* hit, Item* arg_item,
                 HurtCapsule* hurt)
{
    const int log_size = ARRAY_SIZE(it_804A0E70);
    if (it_804D6D18 < log_size) {
        it_804A0E70[it_804D6D18].x0 = arg0;
        it_804A0E70[it_804D6D18].x4 = fighter;
        it_804A0E70[it_804D6D18].x8 = hit;
        it_804A0E70[it_804D6D18].xC = hurt;
        it_804D6D18++;
        return;
    }
    OSReport("damage log over %d!!\n", log_size);
    HSD_ASSERT(105, 0);
}

// EF IDs spawned on hit, indexed by HitElement (-1 = no effect)
static s32 it_803F1384[17] = {
    /* [HitElement_Normal]   */ 1000,
    /* [HitElement_Fire]     */ 1002,
    /* [HitElement_Electric] */ 1001,
    /* [HitElement_Slash]    */ 1004,
    /* [HitElement_Coin]     */ 1145,
    /* [HitElement_Ice]      */ 1005,
    /* [HitElement_Nap]      */ -1,
    /* [HitElement_Sleep]    */ -1,
    /* [HitElement_Catch]    */ -1,
    /* [HitElement_Ground]   */ 1000,
    /* [HitElement_Cape]     */ 1000,
    /* [HitElement_Inert]    */ -1,
    /* [HitElement_Disable]  */ -1,
    /* [HitElement_Dark]     */ 1046,
    /* [HitElement_Scball]   */ -1,
    /* [HitElement_Lipstick] */ -1,
    /* [HitElement_Leadead]  */ 0,
};

static inline void it_8026FA2C_inline(Item* arg_item0, HitCapsule* arg_hit,
                                      s32 arg2, Item* arg_item3, bool arg_chk)
{
    HitCapsule* hit;
    int i;

    for (i = 0; i < ARRAY_SIZE(arg_item0->x5D4_hitboxes); i++) {
        hit = &arg_item0->x5D4_hitboxes[i].hit;
        if (hit->state != HitCapsule_Disabled && hit->x4 == arg_hit->x4 &&
            lbColl_80008688(hit, arg2, arg_item3) && arg_chk)
        {
            it_804D6D1C[i] = 0;
        }
    }
}

void it_8026FA2C(Item* arg_item0, HitCapsule* arg_hit, s32 arg2,
                 Item* arg_item3, bool arg_chk)
{
    HitCapsule* hit;
    int i;

    for (i = 0; i < ARRAY_SIZE(arg_item0->x5D4_hitboxes); i++) {
        hit = &arg_item0->x5D4_hitboxes[i].hit;
        if (hit->state != HitCapsule_Disabled && hit->x4 == arg_hit->x4 &&
            lbColl_80008688(hit, arg2, arg_item3) && arg_chk)
        {
            it_804D6D1C[i] = 0;
        }
    }
}

static inline void it_8026FAC4_inline(Item* arg_item0, HitCapsule* arg_hit,
                                      s32 arg2, Item* arg3, bool chk)
{
    HSD_GObj* item_gobj;
    Item* item;

    if (arg_item0->xAC4_ignoreItemID != 0) {
        item_gobj = HSD_GObj_Entities->items;
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item0->xAC4_ignoreItemID) {
                it_8026FA2C_inline(item, arg_hit, arg2, arg3, chk);
            }
            item_gobj = item_gobj->next;
        }
    } else {
        it_8026FA2C_inline(arg_item0, arg_hit, arg2, arg3, chk);
    }
}

void it_8026FAC4(Item* arg_item0, HitCapsule* arg_hit, s32 arg2, void* arg3,
                 bool chk)
{
    HSD_GObj* item_gobj;
    Item* item;
    PAD_STACK(4);

    if (arg_item0->xAC4_ignoreItemID != 0) {
        item_gobj = HSD_GObj_Entities->items;
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item0->xAC4_ignoreItemID) {
                it_8026FA2C(item, arg_hit, arg2, arg3, chk);
            }
            item_gobj = item_gobj->next;
        }
    } else {
        it_8026FA2C(arg_item0, arg_hit, arg2, arg3, chk);
    }
}

static inline void it_8026FC00_inline(Item* arg_item, HitCapsule* arg_hit,
                                      int arg2, Fighter* arg3)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(arg_item->x5D4_hitboxes); i++) {
        HitCapsule* hit = &arg_item->x5D4_hitboxes[i].hit;
        if (hit->state != HitCapsule_Disabled && hit->x4 == arg_hit->x4) {
            lbColl_80008820(hit, arg2, arg3);
        }
    }
}

void it_8026FC00(Item* arg_item, HitCapsule* arg_hit, s32 arg2, Fighter* arg3)
{
    PAD_STACK(8);

    if (arg_item->xAC4_ignoreItemID != 0) {
        HSD_GObj* item_gobj = HSD_GObj_Entities->items;
        if (item_gobj->next) {
        }
        while (item_gobj != NULL) {
            Item* item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item->xAC4_ignoreItemID) {
                it_8026FC00_inline(item, arg_hit, arg2, arg3);
            }
            item_gobj = item_gobj->next;
        }
    } else {
        it_8026FC00_inline(arg_item, arg_hit, arg2, arg3);
    }
}

void it_8026FCF8(Item* arg_item, HitCapsule* arg_hit)
{
    HSD_GObj* item_gobj;
    HitCapsule* hit;
    bool chk;
    Item* item;
    PAD_STACK(8);

    if (arg_item->xAC4_ignoreItemID != 0U) {
        item_gobj = HSD_GObj_Entities->items;
        while (item_gobj != NULL) {
            item = GET_ITEM(item_gobj);
            if (item->xAC4_ignoreItemID == arg_item->xAC4_ignoreItemID) {
                u32 i;

                chk = false;
                for (i = 0; i < ARRAY_SIZE(item->x5D4_hitboxes); i++) {
                    hit = &item->x5D4_hitboxes[i].hit;
                    if ((hit != arg_hit) &&
                        (hit->state != HitCapsule_Disabled) &&
                        (hit->x4 == arg_hit->x4))
                    {
                        lbColl_CopyHitCapsule(hit, arg_hit);
                        chk = true;
                        break;
                    }
                    chk = false;
                }

                if (chk) {
                    return;
                }
            }
            item_gobj = item_gobj->next;
        }
    }
    lbColl_80008440(arg_hit);
}

void it_8026FE68(Item* arg_item0, HitCapsule* hit1, Item* arg_item2,
                 HitCapsule* hit3)
{
    Vec3 sp48;
    f32 dmg3;
    s32 var_r26;
    f32 dmg1;
    f32 vel_x;
    f32 vel_x_mag;
    f32 pos_x;
    f32 dir;
    s32 dmg_int;
    PAD_STACK(28);

    sp48.x = 0.5f * (hit1->hurt_coll_pos.x + hit3->hurt_coll_pos.x);
    sp48.y = 0.5f * (hit1->hurt_coll_pos.y + hit3->hurt_coll_pos.y);
    sp48.z = 0.5f * (hit1->hurt_coll_pos.z + hit3->hurt_coll_pos.z);
    dmg3 = hit3->damage;
    if (((s32) dmg3 - it_804D6D28->xB4) < (s32) hit1->damage) {
        dmg_int = dmg3;
        if (hit3->x41_b5) {
            var_r26 = 4;
        } else {
            var_r26 = 3;
        }
        it_8026FAC4_inline(arg_item2, hit3, var_r26, arg_item0, true);
        if (dmg_int > arg_item2->xC48) {
            arg_item2->xC48 = dmg_int;
            arg_item2->xCF4_fighterGObjUnk = NULL;
            arg_item2->xC38 = arg_item0->kind;
            arg_item2->xCD4 = arg_item0->pos;
            vel_x_mag = arg_item2->x40_vel.x;
            vel_x = vel_x_mag;
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
        efSync_Spawn(0x41C, arg_item2->entity, &sp48);
    }
    dmg1 = hit1->damage;
    if (((s32) dmg1 - it_804D6D28->xB4) < (s32) hit3->damage) {
        dmg_int = dmg1;
        if (hit1->x41_b5) {
            var_r26 = 4;
        } else {
            var_r26 = 3;
        }
        it_8026FAC4_inline(arg_item0, hit1, var_r26, arg_item2, false);
        if (dmg_int > arg_item0->xC48) {
            arg_item0->xC48 = dmg_int;
            arg_item0->xCF4_fighterGObjUnk = NULL;
            arg_item0->xC38 = arg_item2->kind;
            arg_item0->xCD4 = arg_item2->pos;
            vel_x_mag = arg_item0->x40_vel.x;
            vel_x = vel_x_mag;
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
        efSync_Spawn(0x41C, arg_item0->entity, &sp48);
    }
}

static inline void it_8026FAC4_outline(Item* ip, HitCapsule* hit, s32 arg2,
                                       void* arg3, bool chk)
{
    it_8026FAC4(ip, hit, arg2, arg3, chk);
}

void it_802701BC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Fighter_GObj* fighter_gobj;
    PAD_STACK(4);

    ip->grab_victim = 0;
    ip->xD10 = 3.4028235e38f;
    fighter_gobj = HSD_GObj_Entities->fighters;
    while (fighter_gobj != NULL) {
        Fighter* fp = GET_FIGHTER(fighter_gobj);
        if ((!ftLib_80086FD4(fighter_gobj, ip->owner) || ip->xDCD_flag.b5) &&
            (!gm_8016B168() || gm_8016B0D4() || ip->xDCD_flag.b6 ||
             (ip->x20_team_id != fp->team)) &&
            !fp->x2219_b1 && !fp->x222A_b0 && (fp->x1988 == 0) &&
            (fp->x198C == 0) && !fp->x221D_b6 && !(fp->x1A6A & ip->xD08))
        {
            u32 it_hit_index = 0U;
            while (it_hit_index < 4U) {
                HitCapsule* arg_hit = &ip->x5D4_hitboxes[it_hit_index].hit;
                HitCapsule* new_var = arg_hit;
                if ((new_var->state != HitCapsule_Disabled) &&
                    (new_var->element == HitElement_Catch) &&
                    ((new_var->x40_b2 && (fp->ground_or_air == GA_Air)) ||
                     (new_var->x40_b3 && (fp->ground_or_air == GA_Ground))) &&
                    !lbColl_8000ACFC(fp, new_var))
                {
                    u32 ft_hit_index = 0U;
                    while (ft_hit_index < fp->hurt_capsules_len) {
                        if (fp->hurt_capsules[ft_hit_index].is_grabbable &&
                            lbColl_80007ECC(
                                new_var,
                                &fp->hurt_capsules[ft_hit_index].capsule,
                                ftCommon_8007F804(fp), ip->scl,
                                fp->x34_scale.y, fp->cur_pos.z))
                        {
                            f32 pos_x;
                            it_8026FAC4_outline(ip, new_var, 0, fp, 0);
                            pos_x = ABS(fp->cur_pos.x - ip->pos.x);
                            if (pos_x < ip->xD10) {
                                ip->grab_victim = ip->atk_victim = fp->gobj;
                                ip->xDD0_flag.b1 = 1;
                                ip->xD10 = pos_x;
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

static inline void it_8026F9AC_outline(s32 arg0, void* fighter,
                                       HitCapsule* hit, Item* arg_item,
                                       HurtCapsule* hurt)
{
    it_8026F9AC(arg0, fighter, hit, arg_item, hurt);
}

void it_802703E8(Item_GObj* arg_item_gobj)
{
    HSD_GObj* fighter_gobj;
    HitCapsule* hit;
    HurtCapsule* hurt;
    s32 dmg;
    ItemKind kind;
    HSD_GObj* arg_item_owner_gobj;
    u32 hurt_index;
    u32 hit_index;
    u8 ft_team;
    Item* arg_item;
    Fighter* fighter;
    PAD_STACK(16);

    arg_item = arg_item_gobj->user_data;
    if (arg_item->xAC8_hurtboxNum != 0) {
        fighter_gobj = HSD_GObj_Entities->fighters;
        while (fighter_gobj != NULL) {
            arg_item_owner_gobj = arg_item->owner;
            fighter = fighter_gobj->user_data;
            if (((arg_item_owner_gobj != fighter_gobj) ||
                 arg_item->xDCE_flag.b0) &&
                ((fighter->x1064_thrownHitbox.owner != NULL) ||
                 (fighter->x1064_thrownHitbox.owner != arg_item_owner_gobj) ||
                 arg_item->xDCE_flag.b0))
            {
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
                    hit_index = 0;
                    while (hit_index < 4) {
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
                                        it_8026F9AC_outline(1, fighter, hit,
                                                            arg_item, hurt);
                                        it_8027B378(fighter->gobj,
                                                    arg_item->entity,
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
                                        fighter->unk_gobj = arg_item_gobj;
                                    }
                                    goto block_cf0;
                                } else {
                                    hurt_index++;
                                }
                            }
                        }
                    block_cf0:
                        hit_index++;
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
    f32 pos_x;
    f32 dir;
    f32 pos_x_mag;
    s32 dmg;
    ItemKind kind;
    bool chk2;
    s32 var_r28;
    bool chk;
    s32 var_r5;
    u32 arg_hurt_index;
    u32 arg_hit_index;
    u32 hit_index;
    u8* cnt;
    Item* item;
    Item* arg_item;
    HurtCapsule* arg_hurt;
    PAD_STACK(16);

    chk = false;
    arg_item = GET_ITEM(arg_item_gobj);
    item_gobj = HSD_GObj_Entities->items;
    while (item_gobj != NULL) {
        item = item_gobj->user_data;
        if (arg_item_gobj == item_gobj) {
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
                var_r28 = 0;
                arg_hit_index = 0U;
                cnt = it_804D6D1C;
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
                    cnt++;
                }
            }
            hit_index = 0U;
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
                        chk2 = false;
                        arg_hit_index = 0U;
                        cnt = it_804D6D1C;
                        while (arg_hit_index < 4U) {
                            if (*cnt != 0) {
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
                                            item->toucher = arg_item_gobj;
                                        } else {
                                            item->xDCE_flag.b6 = 1;
                                            arg_item->toucher = item->entity;
                                        }
                                        chk2 = true;
                                        goto block_1080;
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
                                }
                            }
                            arg_hit_index++;
                            cnt++;
                        }
                    block_1080:
                        if (!chk2) {
                            goto block_57;
                        }
                    } else {
                    block_57:
                        if (arg_item->xAC8_hurtboxNum != 0) {
                            if (hit->element == HitElement_Inert) {
                                arg_hurt_index = 0U;
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
                                        item->toucher = arg_item_gobj;
                                    }
                                    arg_hurt_index++;
                                }
                            } else if (arg_item->xD0C != 2) {
                                arg_hurt_index = 0;
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
                                        it_8026FAC4_outline(item, hit, var_r5,
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
                                        it_8026F9AC_outline(
                                            2, item, hit, arg_item, arg_hurt);
                                        it_8027B408(item->entity,
                                                    arg_item->entity, dmg);
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
                                        arg_hurt_index++;
                                    }
                                }
                            }
                        }
                    }
                }
            block_12f4:
                hit_index++;
            }
        }
        item_gobj = item_gobj->next;
    }
}

f32 it_80270CD8(Item* ip, HitCapsule* hit)
{
    ItemAttr* attr = ip->xCC_item_attr;
    f32 f0;
    f32 f1;
    PAD_STACK(8);

    if (hit->x28 != 0) {
        f1 = (0.01f * hit->x24 *
              ((it_804D6D28->x80_float[11] *
                (attr->x1C_damage_mul *
                 ((it_804D6D28->x80_float[10] * it_804D6D28->x80_float[8]) +
                  (it_804D6D28->x80_float[9] *
                   (it_804D6D28->x80_float[10] * hit->x28))))) +
               it_804D6D28->x80_float[12])) +
             hit->x2C;
    } else {
        f0 = ip->xC9C + (f32) ip->xCA0;
        f1 = (0.01f * hit->x24 *
              ((it_804D6D28->x80_float[11] *
                (attr->x1C_damage_mul *
                 ((it_804D6D28->x80_float[8] * f0) +
                  (it_804D6D28->x80_float[9] * (hit->damage * f0))))) +
               it_804D6D28->x80_float[12])) +
             hit->x2C;
    }
    if (f1 >= it_804D6D28->x80_float[7]) {
        f1 = it_804D6D28->x80_float[7];
    }
    return f1;
}

void it_80270E30(Item_GObj* arg_item_gobj)
{
    Vec3 sp2C;
    f32 sp18;
    DamageLogEntry* var_r29;
    HSD_GObj* item_owner_gobj;
    f32 temp_f0;
    f32 temp_f7;
    f32 dir;
    f32 var_f1;
    f32 var_f27;
    f32 var_f28;
    f32 var_f2;
    f32 var_f3;
    f32 var_f4;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 element;
    u32 index;
    Item* item;
    Item* arg_item;
    DamageLogEntry* temp_r29;
    u32 index2;
    HitCapsule* hit2;
    ItemAttr* attr;
    Vec3* hurt_coll_pos;
    Fighter* fighter;
    HitCapsule* hit;
    Item* arg_item2;
    PAD_STACK(8);

    if (it_804D6D18 != 0U) {
        arg_item = arg_item_gobj->user_data;
        var_f28 = -1.0f;
        index = 0;
        var_r29 = &it_804A0E70[index];
        while (index < it_804D6D18) {
            hit = var_r29->x8;
            attr = arg_item->xCC_item_attr;
            if (hit->x28 != 0) {
                var_f2 =
                    attr->x1C_damage_mul *
                    ((it_804D6D28->x80_float[10] * it_804D6D28->x80_float[8]) +
                     (it_804D6D28->x80_float[9] *
                      (it_804D6D28->x80_float[10] * hit->x28)));
                var_f3 = it_804D6D28->x80_float[11];
                var_f4 = hit->x24;
                var_f4 = 0.01f * var_f4;
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
                if ((arg_item->hold_kind == 4) || (arg_item->hold_kind == 6)) {
                    sp18 = hit->damage;
                    hit2 = var_r29->x8;
                    arg_item2 = arg_item_gobj->user_data;
                    hurt_coll_pos = &hit2->hurt_coll_pos;
                    element = *(&it_803F1384[hit2->element]);
                    switch (element) {
                    case 0x3ED:
                        efSync_Spawn(it_803F1384[hit2->element], arg_item_gobj,
                                     hurt_coll_pos, &arg_item2->facing_dir);
                        break;
                    case 0x3E8:
                        efSync_Spawn(0x3E8, arg_item_gobj, hurt_coll_pos,
                                     &sp18);
                        break;
                    case 0x479:
                    case 0x416:
                    case 0x3EB:
                        efSync_Spawn(it_803F1384[hit2->element], arg_item_gobj,
                                     hurt_coll_pos, arg_item2);
                        break;
                    }
                } else {
                    Vec3* sp2C_ref = &sp2C;
                    *sp2C_ref = hit->hurt_coll_pos;
                    efSync_Spawn(0x3E8, arg_item_gobj, sp2C_ref,
                                 &var_r29->x8->damage);
                }
            }
            if (var_f27 > var_f28) {
                var_f28 = var_f27;
                index2 = index;
            }
            index++;
        }
        temp_r29 = &it_804A0E70[index2];
        switch (temp_r29->x0) {
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
            it_8027B4A4(fighter->gobj, arg_item_gobj);
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
            if (ABS(item->x40_vel.x) < it_804D6D28->x78_float) {
                if (arg_item->pos.x > item->pos.x) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
            } else if (item->x40_vel.x < 0.0f) {
                dir = 1.0f;
            } else {
                dir = -1.0f;
            }
            arg_item->xCCC_incDamageDirection = dir;
            it_8027B508(item->entity, arg_item_gobj);
            break;
        }
        arg_item->xCAC_angle = temp_r29->x8->kb_angle;
        arg_item->xCC8_knockback = var_f28;
        arg_item->xCC4 = temp_r29->x8->element;
        arg_item->xDCF_flag.b6 = temp_r29->x8->x43_b0;
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
    int i;
    Item* item = GET_ITEM(item_gobj);
    for (i = 0; i < ARRAY_SIZE(item->x5D4_hitboxes); i++) {
        lbColl_80008A5C(&item->x5D4_hitboxes[i].hit);
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
    if (item->xC4_article_data->x8_hurtbones != NULL) {
        hurt = &item->xACC_itemHurtbox[index];
        hurt->a_offset = arg_hurt->a_offset;
        hurt->b_offset = arg_hurt->b_offset;
        hurt->scale = arg_hurt->scale;
    }
}

void it_80271590(Item_GObj* item_gobj, s32 index, HurtCapsule* arg_hurt)
{
    u8 _[8];
    Vec3 sp18;
    HurtCapsule* hurt;
    Item* item;

    item = GET_ITEM(item_gobj);
    if (item->xC4_article_data->x8_hurtbones != NULL) {
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
    Item* item;
    Article* article;
    ItHurtBoneList* it_hurtbox;
    ItemDynamics* it_dynams;
    HurtCapsule* hurt;
    u32 cnt;
    ItHurtBoneDesc* hurt_dyn_desc;
    BoneDynamicsDesc* bone_dyn_desc;
    s32 index;
    s32 bone_id;
    PAD_STACK(16);

    item = item_gobj->user_data;
    article = item->xC4_article_data;
    it_hurtbox = article->x8_hurtbones;
    it_dynams = article->x14_dynamics;
    if (it_hurtbox != NULL) {
        if (it_hurtbox->count > 2) {
            OSReport("item hit num over!\n");
            __assert("itcoll.c", 0x3F4, "0");
        }
        cnt = 0U;
        item->xAC8_hurtboxNum = it_hurtbox->count;
        index = 0;
        while (cnt < (u32) it_hurtbox->count) {
            hurt = &item->xACC_itemHurtbox[index];
            hurt_dyn_desc = &it_hurtbox->descs[index];
            item->xACC_itemHurtbox[index].state = HurtCapsule_Enabled;
            if (hurt_dyn_desc->bone_id != 0) {
                if (item->xBBC_dynamicBoneTable == NULL) {
                    OSReport("item can't init hit!\n");
                    __assert("itcoll.c", 0x402, "0");
                }
                hurt->bone =
                    item->xBBC_dynamicBoneTable->bones[hurt_dyn_desc->bone_id];
            } else {
                hurt->bone = item_gobj->hsd_obj;
            }
            index++;
            cnt++;
            hurt->a_offset = hurt_dyn_desc->a_offset;
            hurt->b_offset = hurt_dyn_desc->b_offset;
            hurt->scale = hurt_dyn_desc->scale;
        }
    } else {
        item->xAC8_hurtboxNum = 0;
    }
    if (it_dynams != NULL) {
        if ((s32) it_dynams->count > 2) {
            OSReport("item dynamics hit num over!\n");
            __assert("itcoll.c", 0x415, "0");
        }
        cnt = 0U;
        item->xB68 = it_dynams->count;
        index = 0;
        while (cnt < (u32) it_dynams->count) {
            bone_dyn_desc = &it_dynams->dyn_descs[index];
            bone_id = bone_dyn_desc->bone_id;
            item->xB6C_vars[cnt].xB90 = bone_id;
            item->xB6C_vars[cnt].xB7C =
                item->xBBC_dynamicBoneTable->bones[bone_id];
            item->xB6C_vars[cnt].xB6C =
                bone_dyn_desc->dyn_desc.data->desc.absorb.x4_offset;
            item->xB6C_vars[cnt].xB78 =
                bone_dyn_desc->dyn_desc.data->desc.absorb.x10_size;
            index++;
            cnt++;
        }
    }
}

void it_80271830(Item* item, f32 arg_angle)
{
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    Vec3 sp44;
    UNUSED unsigned char _pad[24];
    Vec3 sp20 = *(Vec3*) &it_803B8560;
    f32 left_pos;
    f32 top_pos;
    f32 right_pos;
    f32 bottom_pos;
    f32 angle = arg_angle;
    PAD_STACK(16);

    while (angle < 0.0f) {
        angle += M_TAU;
    }
    while (angle > (M_TAU)) {
        angle -= M_TAU;
    }
    sp68.y = item->xBEC.top;
    sp68.x = sp68.z = 0.0f;
    lbVector_RotateAboutUnitAxis(&sp68, &sp20, angle);
    sp5C.y = item->xBEC.bottom;
    sp5C.x = sp5C.z = 0.0f;
    lbVector_RotateAboutUnitAxis(&sp5C, &sp20, angle);
    sp50.x = item->xBEC.right;
    sp50.y = sp50.z = 0.0f;
    lbVector_RotateAboutUnitAxis(&sp50, &sp20, angle);
    sp44.x = item->xBEC.left;
    sp44.y = sp44.z = 0.0f;
    lbVector_RotateAboutUnitAxis(&sp44, &sp20, angle);
    if (sp68.x > sp5C.x) {
        left_pos = sp5C.x;
    } else {
        left_pos = sp68.x;
    }
    if (left_pos > sp50.x) {
        left_pos = sp50.x;
    } else {
        // silence self-assignment warning
        left_pos = (true) ? left_pos : left_pos;
    }
    left_pos = (left_pos > sp44.x) ? sp44.x : left_pos;
    item->xBEC.left = left_pos;
    if (sp68.y > sp5C.y) {
        top_pos = sp5C.y;
    } else {
        top_pos = sp68.y;
    }
    if (top_pos > sp50.y) {
        top_pos = sp50.y;
    } else {
        top_pos = (true) ? top_pos : top_pos;
    }
    top_pos = (top_pos > sp44.y) ? sp44.y : top_pos;
    item->xBEC.top = top_pos;
    if (sp68.x < sp5C.x) {
        right_pos = sp5C.x;
    } else {
        right_pos = sp68.x;
    }
    if (right_pos < sp50.x) {
        right_pos = sp50.x;
    } else {
        right_pos = (true) ? right_pos : right_pos;
    }
    right_pos = (right_pos < sp44.x) ? sp44.x : right_pos;
    item->xBEC.right = right_pos;
    if (sp68.y < sp5C.y) {
        bottom_pos = sp5C.y;
    } else {
        bottom_pos = sp68.y;
    }
    if (bottom_pos < sp50.y) {
        bottom_pos = sp50.y;
    } else {
        bottom_pos = (true) ? bottom_pos : bottom_pos;
    }
    bottom_pos = (bottom_pos < sp44.y) ? sp44.y : bottom_pos;
    item->xBEC.bottom = bottom_pos;
}

void it_80271A58(Item_GObj* item_gobj)
{
    f32 rotate;
    Item* item;
    HSD_JObj* jobj;

    item = GET_ITEM(item_gobj);
    item->xBEC = item->xBDC;
    if ((item->facing_dir == 1.0f) && (item->xDC8_word.flags.x19 == 1)) {
        f32 temp = -item->xBEC.right;
        item->xBEC.right = -item->xBEC.left;
        item->xBEC.left = temp;
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
    Vec3 sp24;
    Item_FtTrack* var_r29;
    Item_FtTrack* var_r30;
    f32 x_float;
    f32 x_pos;
    f32 y_pos;
    f32 x_float_mag;
    f32 dir;
    u32 cnt;
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(12);

    item_jobj = GET_JOBJ(item_gobj);
    item = GET_ITEM(item_gobj);
    if (Item_804A0CCC.x154.b0 != 1) {
        HSD_JObjGetTranslation(item_jobj, &sp24);
        var_r30 = &Item_804A0CCC;
        var_r29 = &Item_804A0CCC;
        cnt = 0U;

        while (cnt < Item_804A0CCC.x150_count) {
            y_pos = var_r29->xC0_pos_arr[cnt].y;
            x_pos = var_r29->xC0_pos_arr[cnt].x;
            if (itColl_chkECBOverlap(x_pos, y_pos, &item->xBEC,
                                     &var_r30->x0_ecb_arr[cnt], &sp24))
            {
                if (ABS(sp24.x - x_pos) < 0.001f) {
                    if (HSD_Randi(2) != 0) {
                        dir = 1.0f;
                    } else {
                        dir = -1.0f;
                    }
                } else {
                    if (sp24.x - x_pos < 0.0f) {
                        dir = -1.0f;
                    } else {
                        dir = 1.0f;
                    }
                }
                item->x70_nudge.x = it_804D6D28->x7C_float * dir;
                item->xDC0 |= 1;
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
    HSD_JObj* item_jobj;
    Item* item;
    HSD_JObj* arg_item_jobj;
    Item* arg_item;
    PAD_STACK(16);

    arg_item_jobj = GET_JOBJ(arg_item_gobj);
    arg_item = GET_ITEM(arg_item_gobj);
    HSD_JObjGetTranslation(arg_item_jobj, &sp34);
    item_gobj = HSD_GObj_Entities->items;

    while (item_gobj != NULL) {
        item_jobj = GET_JOBJ(item_gobj);
        item = GET_ITEM(item_gobj);
        if ((arg_item_gobj != item_gobj) && !item->xDC8_word.flags.x13 &&
            (item->ground_or_air == GA_Ground) && !item->xDD1_flag.b0 &&
            ((item->hold_kind != 3) ||
             ((item->hold_kind == 3) &&
              item->xDC8_word.flags
                  .x1E)) // hold_kind 3 is open palm, facing down(?)
        )
        {
            HSD_JObjGetTranslation(item_jobj, &sp28);
            if (itColl_chkECBOverlap(sp28.x, sp28.y, &arg_item->xBEC,
                                     &item->xBEC, &sp34))
            {
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
                arg_item->xDC0 |= 2;
            }
        }
        item_gobj = item_gobj->next;
    }
}

void it_80271F78(Item_GObj* gobj)
{
    u8 _pad[12];
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* arg_item = GET_ITEM(gobj);
    Vec3 sp34;
    Vec3 sp28;
    HSD_GObj* item_gobj;
    f32 dir;
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(4);

    HSD_JObjGetTranslation(jobj, &sp34);
    item_gobj = HSD_GObj_Entities->items;

    while (item_gobj != NULL) {
        item_jobj = GET_JOBJ(item_gobj);
        item = GET_ITEM(item_gobj);
        if ((gobj != item_gobj) && !item->xDC8_word.flags.x13 &&
            (item->ground_or_air == GA_Ground) && !item->xDD1_flag.b0 &&
            (it_8026B2B4(item_gobj) == 1))
        {
            HSD_JObjGetTranslation(item_jobj, &sp28);
            if (itColl_chkECBOverlap(sp28.x, sp28.y, &arg_item->xBEC,
                                     &item->xBEC, &sp34))
            {
                if (ABS(sp34.x - sp28.x) < 0.001f) {
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
                } else if (sp34.x - sp28.x < 0.0f) {
                    dir = -1.0f;
                } else {
                    dir = 1.0f;
                }
                arg_item->x70_nudge.x = it_804D6D28->x7C_float * dir;
                arg_item->xDC0 |= 2;
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
    item->xDC0 = 0;
    if (!item->xDC8_word.flags.x13) {
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
    if (item_gobj == HSD_GObj_Entities->items) {
        ftCo_80098634(&Item_804A0CCC);
        Item_804A0CCC.x154.b0 = 0;
    }
}

void it_80272304(Item_GObj* item_gobj)
{
    u32 i;
    Item* item = GET_ITEM(item_gobj);
    for (i = 0; i < item->xB68; i++) {
        struct xB6C_t* tmp = &item->xB6C_vars[i];
        lb_8000B1CC(tmp->xB7C, &tmp->xB6C, &tmp->xB84);
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
    arg_item = GET_ITEM(arg_item_gobj);
    owner_gobj = arg_item->owner;
    if (ftLib_80086960(owner_gobj)) {
        owner = GET_FIGHTER(owner_gobj);
        if (owner->x34_scale.y != 1.0f) {
            dmg = 0.999f + ftCo_CalcYScaledKnockback(dmg, owner->x34_scale.y,
                                                     Fighter_804D6524->x4);
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
