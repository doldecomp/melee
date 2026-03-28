#include "itclimbersice.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/chara/ftPopo/ftPp_Init.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "MSL/math.h"
#include "it/itcoll.h"

/* 2C23D4 */ static bool itClimbersBlizzard_UnkMotion0_Coll(Item_GObj* gobj);

/// #it_802C1590

/// #it_802C16F8

void it_802C17DC(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

void it_2725_Logic90_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.climbersice.x0 != NULL) {
        if (ip->kind == 0x6A) {
            ftPp_Init_8011F16C(ip->xDD4_itemVar.climbersice.x0, gobj);
        } else {
            ftKb_SpecialNIc_80108CE8(ip->xDD4_itemVar.climbersice.x0, gobj);
        }
    }
    ip->xDD4_itemVar.climbersice.x0 = NULL;
}

bool it_802C1854(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    bool result = false;
    CollData* coll = &ip->x378_itemColl;
    itClimbersIceAttributes* sa = ip->xC4_article_data->x4_specialAttributes;

    if (coll->env_flags & 0x18000) {
        f32 normal_x = coll->floor.normal.x;
        s32 sign_normal;
        s32 sign_vel;
        f32 accel;

        if (normal_x < 0.0f) {
            sign_normal = -1;
        } else {
            sign_normal = 1;
        }

        if (ip->x40_vel.x < 0.0f) {
            sign_vel = -1;
        } else {
            sign_vel = 1;
        }

        if (sign_vel != sign_normal) {
            accel = sa->x1C * (normal_x * sa->x14);
        } else {
            accel = sa->x18 * (normal_x * sa->x14);
        }

        ip->x40_vel.x += accel;

        {
            f32 abs_vel = ip->x40_vel.x;
            if (abs_vel < 0.0f) {
                abs_vel = -abs_vel;
            }
            if (abs_vel < sa->x24) {
                it_8026BD84(gobj);
                it_8026BD6C(gobj);
                it_802C1950(gobj);
                efLib_DestroyAll(gobj);
                result = true;
            }
        }
    }

    return result;
}

void it_802C1950(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itClimbersice_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    itClimbersIceAttributes* sa = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* child;
    PAD_STACK(8);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    if (ip->xDD4_itemVar.climbersice.x8_b0) {
        ip->xDD4_itemVar.climbersice.x4 *= sa->x28;
        it_80272F7C(child, ip->xDD4_itemVar.climbersice.x4);
        if (ip->xDD4_itemVar.climbersice.x4 < 0.01F) {
            return true;
        }
    }
    return false;
}

void itClimbersice_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itClimbersice_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, (HSD_GObjEvent) it_802C1A58);
    it_80276CB8(gobj);
    return false;
}

void it_802C1A58(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itClimbersice_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itClimbersice_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itClimbersice_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802C1950);
    return false;
}

void it_802C1AE4(Item_GObj* gobj)
{
    HSD_JObj* child;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(16);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    {
        Item* ip = GET_ITEM(gobj);

        if (ip->kind == 0x6A) {
            f32* facing = &ip->facing_dir;
            efAsync_Spawn(gobj, &ip->xBC0, 3, 0x4EB, child, facing);
        } else {
            f32* facing = &ip->facing_dir;
            efAsync_Spawn(gobj, &ip->xBC0, 3, 0x4B0, child, facing);
        }
    }

    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itClimbersice_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void itClimbersice_UnkMotion2_Phys(Item_GObj* gobj)
{
    if (it_802C1854(gobj)) {
        Item* ip = GET_ITEM(gobj);
        itClimbersIceAttributes* sa =
            ip->xC4_article_data->x4_specialAttributes;
        u32 dmg = (u32) ABS(ip->x40_vel.x * sa->x30) + sa->x2C;
        it_80272460(&ip->x5D4_hitboxes[0].hit, dmg, gobj);
    }
}

bool itClimbersice_UnkMotion2_Coll(Item_GObj* gobj)
{
    Item* ip;
    itClimbersIceAttributes* sa;

    it_8026D62C(gobj, (HSD_GObjEvent) fn_802C1D44);
    it_80276CB8(gobj);

    ip = GET_ITEM(gobj);
    sa = ip->xC4_article_data->x4_specialAttributes;

    if (it_80276308(gobj) != 0) {
        f32 vel_x = ip->x40_vel.x;
        if (vel_x < 0.0f) {
            vel_x = -vel_x;
        }
        if (vel_x <= sa->xC) {
            it_8027770C(gobj);
            it_80272980(gobj);
            ip = GET_ITEM(gobj);
            sa = ip->xC4_article_data->x4_specialAttributes;
            ip->xD44_lifeTimer -= sa->x4;
        } else {
            return true;
        }
    }
    return false;
}

void fn_802C1D44(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    efLib_DestroyAll(gobj);
}

bool itClimbersice_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #itClimbersice_UnkMotion3_Phys

/// #itClimbersice_UnkMotion3_Coll

bool itClimbersIce_Logic90_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itClimbersIce_Logic90_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itClimbersIce_Logic90_Clanked(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic90_HitShield

bool itClimbersIce_Logic90_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itClimbersIce_Logic90_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void itClimbersIce_Logic90_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.climbersice.x0 == ref_gobj) {
        ip->xDD4_itemVar.climbersice.x0 = NULL;
    }
    it_8026B894(gobj, ref_gobj);
}
