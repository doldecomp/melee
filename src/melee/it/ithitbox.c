#include "ithitbox.h"

#include "it_2725.h"
#include "it_3F14.h"
#include "itmaplib.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itcoll.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

void it_802753DC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xC34_damageDealt = 0;
    item->xC40 = 1.0f;
    item->xC44 = 1.0f;
    item->xC3C = 1.0f;
    item->xC48 = 0;
    item->xC4C = 0;
    item->xC50 = 0;
    item->xDCE_flag.b6 = 0;
}

void it_80275414(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.b7 = 1;
}

void it_8027542C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.b7 = 0;
}

void it_80275444(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.b5 = 1;
    item->xDCD_flag.b7 = 1;
    item->xDCD_flag.b6 = 1;
}

void it_80275474(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCD_flag.b5 = 0;
    item->xDCD_flag.b7 = 0;
    item->xDCD_flag.b6 = 0;
}

void it_802754A4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.b2 = 1;
}

void it_802754BC(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.b2 = 0;
}

void it_802754D4(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.b0 = 1;
    item->xDCE_flag.b2 = 1;
    item->xDCE_flag.b1 = 1;
}

void it_80275504(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDCE_flag.b0 = 0;
    item->xDCE_flag.b2 = 0;
    item->xDCE_flag.b1 = 0;
}

void it_80275534(Item_GObj* item_gobj, f32 scale)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;

    item = item_gobj->user_data;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->scale = scale;
        }
    }
}

void it_80275594(Item_GObj* item_gobj, s32 idx, f32 mult)
{
    Item* item;
    HitCapsule* hitcapsule;

    item = item_gobj->user_data;
    hitcapsule = &item->x5D4_hitboxes[idx].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->scale *= mult;
    }
}

void it_802755C0(Item_GObj* item_gobj, f32 scale)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;

    item = item_gobj->user_data;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->scale *= scale;
        }
    }
}

void it_80275640(Item_GObj* item_gobj, f32 arg1)
{
    Item* item = GET_ITEM(item_gobj);
    u32 i;

    for (i = 0; i < 4; i++) {
        HitCapsule* hitcapsule = &item->x5D4_hitboxes[i].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            it_80272460(hitcapsule, hitcapsule->damage * arg1, item_gobj);
        }
    }
}

void it_802756D0(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->xD0C = 2;
}

void it_802756E0(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->xD0C = 0;
    it_802714C0(item_gobj);
}

void it_8027570C(Item_GObj* item_gobj, s32 idx)
{
    Item* item;

    item = item_gobj->user_data;
    item->x5D4_hitboxes[idx].hit.x40_b0 = 0;
}

void it_8027572C(Item_GObj* item_gobj, s32 idx)
{
    Item* item;

    item = item_gobj->user_data;
    item->x5D4_hitboxes[idx].hit.x40_b0 = 1;
}

#pragma push
#pragma dont_inline on

void it_8027574C(Item_GObj* item_gobj)
{
    Item* item = item_gobj->user_data;
    it_80274D04(item_gobj, &item->xB54);
    it_80274D6C(item_gobj);
}

#pragma pop

void it_80275788(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 state;
    u32 var_ctr;

    item = item_gobj->user_data;
    state = 4;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = (0, &item->x5D4_hitboxes[var_ctr].hit);
        if (hitcapsule->state != HitCapsule_Disabled) {
            hitcapsule->state = state;
            item->xDAA_flag.b2 = 1;
        }
    }
}

void it_80275820(Item_GObj* item_gobj, Vec3* arg1, Vec3* arg2, s32 idx)
{
    Item* item;
    HitCapsule* hitcapsule;

    item = item_gobj->user_data;
    hitcapsule = &item->x5D4_hitboxes[idx].hit;
    if (hitcapsule->state != HitCapsule_Disabled) {
        hitcapsule->x58 = *arg2;
        hitcapsule->x4C = *arg1;
    }
}

bool it_80275870(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;

    item = item_gobj->user_data;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            return true;
        }
    }
    return false;
}

f32 it_802758D4(Item_GObj* item_gobj)
{
    Item* item;
    HitCapsule* hitcapsule;
    u32 var_ctr;
    f32 damage;
    bool disable_chk;

    item = item_gobj->user_data;
    damage = 0.0f;
    for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
        hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
        if (hitcapsule->state != HitCapsule_Disabled) {
            disable_chk = true;
            break;
        } else {
            disable_chk = false;
        }
    }

    if (disable_chk) {
        for (var_ctr = 0U; var_ctr < 4U; var_ctr++) {
            hitcapsule = &item->x5D4_hitboxes[var_ctr].hit;
            if (hitcapsule->state != HitCapsule_Disabled) {
                if (damage <= hitcapsule->damage) {
                    damage = hitcapsule->damage;
                }
            }
        }
    }
    return damage;
}
