#include "itflipper.h"

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/it_3F14.h"
#include "it/item.h"
#include "it/itgroundcoll.h"
#include "it/ithitbox.h"
#include "lb/lb_00B0.h"
#include "lb/lbcollision.h"
#include "lb/lbvector.h"

#include <math.h>

HSD_GObj* itFlipper_Spawn(HSD_JObj* jobj)
{
    u8 _pad[8];
    SpawnItem spawn;
    Vec3 pos;
    Item_GObj* gobj = NULL;

    if (jobj != NULL) {
        lb_8000B1CC(jobj, NULL, &pos);
        spawn.kind = It_Kind_Flipper;
        spawn.prev_pos = pos;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = 1.0f;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
        spawn.x0_parent_gobj = NULL;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = 0;
        spawn.x40 = 0;
        gobj = Item_80268B18(&spawn);
        if (gobj != NULL) {
            Item* ip = GET_ITEM(gobj);
            ip->xDD4_itemVar.flipper.xDE8_isStageFixed = 1;
            ip->xDD4_itemVar.flipper.xDEC_stageAnchor = jobj;
            itFlipper_Settle(gobj);
        }
    }
    return gobj;
}

void itFlipper_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->xDD4_itemVar.flipper.xDD4_flightTimer = 0;
    ip->xDD4_itemVar.flipper.xDD8_isSettled = 0;
    ip->xDD4_itemVar.flipper.xDDC_hitboxTimer = 0;
    ip->xDD4_itemVar.flipper.xDE0_spinAngle = 0.0f;
    ip->xDD4_itemVar.flipper.xDE4_spinVel = 0.0f;
    ip->xDD4_itemVar.flipper.xDE8_isStageFixed = 0;
    ip->xDD4_itemVar.flipper.xDEC_stageAnchor = 0;
    it_802756D0(gobj);
    itFlipper_EnterFalling(gobj);
}

void itFlipper_UpdateSpin(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = itGetJObjGrandchild(gobj);

    if (ip->xDD4_itemVar.flipper.xDE4_spinVel > 3.1415927f) {
        ip->xDD4_itemVar.flipper.xDE4_spinVel -= 6.2831855f;
    }
    if (ip->xDD4_itemVar.flipper.xDE4_spinVel < -3.1415927f) {
        ip->xDD4_itemVar.flipper.xDE4_spinVel += 6.2831855f;
    }

    {
        Item* ip2 = ip;
        if (ABS(ip2->xDD4_itemVar.flipper.xDE4_spinVel) > 0.0f) {
            if (ABS(ip2->xDD4_itemVar.flipper.xDE4_spinVel) <
                attrs->x20_spinDecay)
            {
                ip->xDD4_itemVar.flipper.xDE4_spinVel = 0.0f;
            } else if (ip2->xDD4_itemVar.flipper.xDE4_spinVel > 0.0f) {
                ip2->xDD4_itemVar.flipper.xDE4_spinVel -= attrs->x20_spinDecay;
            } else {
                ip->xDD4_itemVar.flipper.xDE4_spinVel += attrs->x20_spinDecay;
            }
        }

        ip->xDD4_itemVar.flipper.xDE0_spinAngle +=
            ip2->xDD4_itemVar.flipper.xDE4_spinVel;
        HSD_JObjSetRotationX(jobj, ip2->xDD4_itemVar.flipper.xDE0_spinAngle);
    }
}

void itFlipper_AddSpinImpulse(Item_GObj* gobj, Vec3* pos, f32 vel)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    f32 speed = vel + attrs->x1C_baseSpinOnHit;

    if (pos->x > ip->pos.x) {
        if (pos->y > ip->pos.y) {
            ip->xDD4_itemVar.flipper.xDE4_spinVel += speed;
        } else {
            ip->xDD4_itemVar.flipper.xDE4_spinVel -= speed;
        }
    } else {
        if (pos->y > ip->pos.y) {
            ip->xDD4_itemVar.flipper.xDE4_spinVel -= speed;
        } else {
            ip->xDD4_itemVar.flipper.xDE4_spinVel += speed;
        }
    }

    if (ip->xDD4_itemVar.flipper.xDE4_spinVel > attrs->x24_maxSpinVel) {
        ip->xDD4_itemVar.flipper.xDE4_spinVel = attrs->x24_maxSpinVel;
    }
    if (ip->xDD4_itemVar.flipper.xDE4_spinVel < -attrs->x24_maxSpinVel) {
        ip->xDD4_itemVar.flipper.xDE4_spinVel = -attrs->x24_maxSpinVel;
    }
}

static inline f32 itFlipper_SpinSpeedFromFighter(Item_GObj* gobj,
                                                 HSD_GObj* fighter, Vec3* pos,
                                                 Vec3* vel)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    ftLib_800866DC(fighter, pos);
    ftLib_80086BEC(fighter, vel);
    return attrs->x18_spinMultiplier *
           sqrtf__Ff(vel->x * vel->x + vel->y * vel->y);
}

static inline void itFlipper_SpinFromFighter_inline(Item_GObj* gobj, Vec3* vel,
                                                    Vec3* pos, f32 speed)
{
    Item* ip = GET_ITEM(gobj);
    *pos = ip->pos;

    if (ip->xCF4_fighterGObjUnk != NULL) {
        HSD_GObj* fighter = ip->xCF4_fighterGObjUnk;
        if (ftLib_80086960(fighter)) {
            speed = itFlipper_SpinSpeedFromFighter(gobj, fighter, pos, vel);
        }
        ip->xCF4_fighterGObjUnk = NULL;
    }
    itFlipper_AddSpinImpulse(gobj, pos, deg_to_rad * speed);
}

void itFlipper_SpinFromFighter(Item_GObj* gobj)
{
    u8 _pad[4];
    Item* ip = GET_ITEM(gobj);
    f32 speed = 10.0f;
    Vec3 pos;
    Vec3 vel;
    PAD_STACK(4);
    pos = ip->pos;

    if (ip->xCF4_fighterGObjUnk != NULL) {
        HSD_GObj* fighter = ip->xCF4_fighterGObjUnk;
        if (ftLib_80086960(fighter)) {
            speed = itFlipper_SpinSpeedFromFighter(gobj, fighter, &pos, &vel);
        }
        ip->xCF4_fighterGObjUnk = NULL;
    }
    itFlipper_AddSpinImpulse(gobj, &pos, deg_to_rad * speed);
}

static inline void itFlipper_Repel_inline(Item_GObj* gobj, s32 kind, Vec3* pos,
                                          Vec3* vec)
{
    Item* ip = GET_ITEM(gobj);
    vec->x = vec->y = vec->z = 0.0f;

    if (kind == 0x14) {
        vec->x = ip->pos.x - pos->x;
        vec->y = ip->pos.y - pos->y;
        lbVector_NormalizeXY(vec);
        vec->x *= 0.2f;
        vec->y *= 0.2f;
        ip->x40_vel.x += vec->x;
        ip->x40_vel.y += vec->y;
    }
}

void itFlipper_Repel(Item_GObj* gobj, s32 kind, Vec3* pos)
{
    Vec3 vec;
    itFlipper_Repel_inline(gobj, kind, pos, &vec);
}

void itFlipper_EnterResting(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    it_8026B390(gobj);
    Item_80268E5C(gobj, FLIPPER_MS_RESTING, ITEM_ANIM_UPDATE);
}

bool itFlipper_Resting_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_Resting_Phys(Item_GObj* gobj) {}

bool itFlipper_Resting_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, itFlipper_EnterFalling);
    return false;
}

void itFlipper_EnterFalling(Item_GObj* gobj)
{
    Item_80268E5C(gobj, FLIPPER_MS_FALLING, ITEM_ANIM_UPDATE);
}

bool itFlipper_Falling_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_Falling_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFlipper_Falling_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, itFlipper_EnterResting);
    return false;
}

void itFlipper_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, FLIPPER_MS_HELD, ITEM_ANIM_UPDATE);
}

bool itFlipper_Held_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_Held_Phys(Item_GObj* gobj) {}

void itFlipper_Dropped(Item_GObj* gobj)
{
    itFlipper_Thrown(gobj);
}

void itFlipper_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->owner != NULL) {
        if (ftLib_80087284(ip->owner)) {
            ip->xDD4_itemVar.flipper.xDD4_flightTimer =
                attrs->x4_smashThrowDuration;
        } else {
            ip->xDD4_itemVar.flipper.xDD4_flightTimer =
                attrs->x0_throwDuration;
        }
    }
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, FLIPPER_MS_INFLIGHT,
                  ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

bool itFlipper_Inflight_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.flipper.xDD4_flightTimer--;
    if (ip->xDD4_itemVar.flipper.xDD4_flightTimer <= 0) {
        itFlipper_Settle(gobj);
    }
    return false;
}

void itFlipper_Inflight_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* item_attr = ip->xCC_item_attr;
    it_80272860(gobj, item_attr->x10_fall_speed,
                item_attr->x14_fall_speed_max);
    if (ip->xDD4_itemVar.flipper.xDD4_flightTimer <= 0xA) {
        ip->x40_vel.x *= ip->xDD4_itemVar.flipper.xDD4_flightTimer /
                         (1.0f + ip->xDD4_itemVar.flipper.xDD4_flightTimer);
        ip->x40_vel.y *= ip->xDD4_itemVar.flipper.xDD4_flightTimer /
                         (1.0f + ip->xDD4_itemVar.flipper.xDD4_flightTimer);
    }
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itFlipper_Inflight_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 coll = it_8026DAA8(gobj);
    if (coll != 0) {
        if (coll & 0xC) {
            ip->x40_vel.x *= -attrs->xC_wallBounce;
        }
        ip->x40_vel.y *= attrs->xC_wallBounce;
        if (coll & 2) {
            ip->x40_vel.x *= attrs->xC_wallBounce;
        }
        ip->x40_vel.y *= -attrs->xC_wallBounce;
        if (coll & 1) {
            ip->x40_vel.x *= attrs->x10_floorBounce;
        }
        ip->x40_vel.y *= -attrs->x10_floorBounce;
    }
    return false;
}

void itFlipper_Settle(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xD5C = 0;
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->xDD1_flag.b1 = 1;
    ip->xDD4_itemVar.flipper.xDD8_isSettled = 1;
    it_80275444(gobj);
    it_802725D4(gobj);
    if (ip->xDD4_itemVar.flipper.xDE8_isStageFixed != 0) {
        it_8027542C(gobj);
    }
    ip->xD44_lifeTimer = attrs->x8_lifetime;
    it_8026B3A8(gobj);
    it_802756E0(gobj);
    itFlipper_EnterActive(gobj);
}

void itFlipper_EnterActive(Item_GObj* gobj)
{
    Item_80268E5C(gobj, FLIPPER_MS_ACTIVE, 0x12);
}

static inline void itFlipper_RefreshHitboxes(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80272674(gobj, 0);
    it_80272674(gobj, 1);
    lbColl_80008440(&ip->x5D4_hitboxes[0].hit);
    lbColl_80008440(&ip->x5D4_hitboxes[1].hit);
    it_802756E0(gobj);
}

bool itFlipper_UpdateActive(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    itFlipper_UpdateSpin(gobj);

    if (ABS(ip->x40_vel.x) >= 0.01f) {
        ip->x40_vel.x *= 0.9f;
    } else {
        ip->x40_vel.x = 0.0f;
    }

    if (ABS(ip->x40_vel.y) >= 0.01f) {
        ip->x40_vel.y *= 0.9f;
    } else {
        ip->x40_vel.y = 0.0f;
    }

    {
        s32 timer = ip->xDD4_itemVar.flipper.xDDC_hitboxTimer;
        if (timer > 0) {
            ip->xDD4_itemVar.flipper.xDDC_hitboxTimer = timer - 1;
            if (ip->xDD4_itemVar.flipper.xDDC_hitboxTimer == 0) {
                itFlipper_RefreshHitboxes(gobj);
            }
        }
    }

    if (!ip->xDD4_itemVar.flipper.xDE8_isStageFixed) {
        ip->xD44_lifeTimer -= 1.0f;
        if (ip->xD44_lifeTimer <= 0.0f) {
            return true;
        }
        if (ip->xD44_lifeTimer <= it_804D6D28->x34) {
            it_802728C8(gobj);
        }
    }
    return false;
}

bool itFlipper_Active_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.flipper.xDE4_spinVel != 0.0f) {
        Item_80268E5C(gobj, FLIPPER_MS_SPINNING, 0x12);
    }
    return itFlipper_UpdateActive(gobj);
}

bool itFlipper_Spinning_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.flipper.xDE4_spinVel == 0.0F) {
        Item_80268E5C(gobj, FLIPPER_MS_ACTIVE, 0x12);
    }
    return itFlipper_UpdateActive(gobj);
}

void itFlipper_Spinning_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.flipper.xDE8_isStageFixed != 0) {
        if (ip->xDD4_itemVar.flipper.xDEC_stageAnchor != NULL) {
            lb_8000B1CC(ip->xDD4_itemVar.flipper.xDEC_stageAnchor, 0,
                        &ip->pos);
        }
    }
}

bool itFlipper_Spinning_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (!ip->xDD4_itemVar.flipper.xDE8_isStageFixed) {
        it_8026E0F4(gobj);
    }
    return false;
}

bool itFlipper_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos;
    u8 _pad[8];
    Vec3 pos2;
    Vec3 vel;
    PAD_STACK(8);
    if (!ip->xDD4_itemVar.flipper.xDD8_isSettled) {
        if (ip->xDD4_itemVar.flipper.xDD4_flightTimer >= 6) {
            itColl_BounceOffVictim(gobj);
        } else {
            ip->x40_vel.x = -1.0f * ip->x40_vel.x;
            ip->x40_vel.y = -1.0f * ip->x40_vel.y + it_804D6D28->x60_float;
        }
    } else {
        ip->xDD4_itemVar.flipper.xDDC_hitboxTimer = attrs->x14_hitboxInterval;
        itFlipper_SpinFromFighter_inline(gobj, &vel, &pos, 10.0f);
        it_80272560(gobj, 0);
        it_80272560(gobj, 1);
        it_802756D0(gobj);
        if (!ip->xDD4_itemVar.flipper.xDE8_isStageFixed) {
            itFlipper_Repel_inline(gobj, ip->xC38, &ip->xCD4, &pos2);
        }
    }
    return false;
}

#pragma dont_inline on
bool itFlipper_Clanked(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    if (!ip->xDD4_itemVar.flipper.xDD8_isSettled) {
        if (ip->xDD4_itemVar.flipper.xDD4_flightTimer >= 6) {
            itColl_BounceOffVictim(gobj);
        } else {
            ip->x40_vel.x = -1.0f * ip->x40_vel.x;
            ip->x40_vel.y = -1.0f * ip->x40_vel.y + it_804D6D28->x60_float;
        }
    } else {
        ip->xDD4_itemVar.flipper.xDDC_hitboxTimer = attrs->x14_hitboxInterval;
        itFlipper_SpinFromFighter(gobj);
        it_80272560(gobj, 0);
        it_80272560(gobj, 1);
        it_802756D0(gobj);
        if (!ip->xDD4_itemVar.flipper.xDE8_isStageFixed) {
            itFlipper_Repel(gobj, ip->xC38, &ip->xCD4);
        }
    }
    return false;
}

bool itFlipper_HitShield(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    if (ip->xDD4_itemVar.flipper.xDD8_isSettled == 0) {
        if (ip->xDD4_itemVar.flipper.xDD4_flightTimer >= 6) {
            itColl_BounceOffVictim(gobj);
        } else {
            ip->x40_vel.x = -1.0f * ip->x40_vel.x;
            ip->x40_vel.y = -1.0f * ip->x40_vel.y + it_804D6D28->x60_float;
        }
    } else {
        ip->xDD4_itemVar.flipper.xDDC_hitboxTimer = attrs->x14_hitboxInterval;
        itFlipper_SpinFromFighter(gobj);
        it_80272560(gobj, 0);
        it_80272560(gobj, 1);
        it_802756D0(gobj);
        if (!ip->xDD4_itemVar.flipper.xDE8_isStageFixed) {
            itFlipper_Repel(gobj, ip->xC38, &ip->xCD4);
        }
    }
    return false;
}

#pragma dont_inline reset
bool itFlipper_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itFlipper_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

static inline void itFlipper_SpinFromFighterRecv(Item_GObj* gobj, Vec3* vel,
                                                 Vec3* pos, f32 speed)
{
    Item* ip = GET_ITEM(gobj);
    *pos = ip->pos;

    if (ip->xCEC_fighterGObj != NULL) {
        HSD_GObj* fighter = ip->xCEC_fighterGObj;
        if (ftLib_80086960(fighter)) {
            speed = itFlipper_SpinSpeedFromFighter(gobj, fighter, pos, vel);
        }
        ip->xCEC_fighterGObj = NULL;
    }
    itFlipper_AddSpinImpulse(gobj, pos, deg_to_rad * speed);
}

bool itFlipper_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlipper_DatAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos;
    u8 _pad[8];
    Vec3 vec;
    Vec3 vel;
    PAD_STACK(8);
    if (ip->xDD4_itemVar.flipper.xDD8_isSettled != 0) {
        ip->xDD4_itemVar.flipper.xDDC_hitboxTimer = attrs->x14_hitboxInterval;
        itFlipper_SpinFromFighterRecv(gobj, &vel, &pos, 10.0f);
        it_80272560(gobj, 0);
        it_80272560(gobj, 1);
        it_802756D0(gobj);
        if (!ip->xDD4_itemVar.flipper.xDE8_isStageFixed) {
            itFlipper_Repel_inline(gobj, ip->xCB4, &ip->xCE0, &vec);
        }
    }
    return false;
}

void itFlipper_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, FLIPPER_MS_AIRBORNE, ITEM_ANIM_UPDATE);
}

bool itFlipper_Airborne_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_Airborne_Phys(Item_GObj* gobj) {}

bool itFlipper_Airborne_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, itFlipper_EnterResting, itFlipper_EnterFalling);
    return false;
}

void itFlipper_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
