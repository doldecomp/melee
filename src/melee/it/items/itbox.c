#include "itbox.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/jobj.h"
#include "baselib/random.h"
#include "cm/camera.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00F9.h"

/// #it_80286088

/// Initialize box item state when spawned
void it_3F14_Logic1_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCE_flag.b7 = 0;
    ip->xDD4_itemVar.box.opened = 0;
    ip->xDD4_itemVar.box.spawned_gobj = NULL;
    it_8028655C(gobj);
}

/// Cleanup box item when destroyed - destroys any spawned effect
void it_3F14_Logic1_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.box.spawned_gobj != NULL) {
        efLib_DestroyAll(ip->xDD4_itemVar.box.spawned_gobj);
        ip->xDD4_itemVar.box.spawned_gobj = NULL;
    }
}

/// #it_80286248

#pragma push
#pragma dont_inline on
bool it_80286340(Item_GObj* gobj, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 sum1 = arg1 + arg2;
    s32 sum2 = arg3 + sum1;
    s32 rand = HSD_Randi(arg4 + sum2);
    if (rand < arg1) {
        return true;
    }
    if (rand < sum1) {
        return true;
    }
    if (rand < sum2) {
        return true;
    }
    return false;
}
#pragma pop

/// #it_802863BC

void fn_80286480(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    PAD_STACK(12);
    it_8026B390(gobj);
    it->x40_vel.x = it->x40_vel.y = it->x40_vel.z = 0.0F;
    Item_80268E5C(gobj, 0, 2);
}

/// #itBox_UnkMotion0_Anim

void itBox_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, (HSD_GObjEvent) it_8028655C);
    it_80276CB8(gobj);
    return false;
}

void it_8028655C(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itBox_UnkMotion1_Phys

bool itBox_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80286480);
    return false;
}

void it_3F14_Logic1_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itBox_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic1_Thrown(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void itBox_UnkMotion4_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = ((Item*) gobj->user_data)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

/// #itBox_UnkMotion3_Coll

void it_3F14_Logic1_Dropped(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

/// #itBox_UnkMotion4_Coll

/// Box/Crate item attributes for spawn behavior
typedef struct itBoxAttributes {
    /* +00 */ s32 spawn_weight_0;     ///< Weight for item spawn outcome 1
    /* +04 */ s32 spawn_weight_1;     ///< Weight for item spawn outcome 2
    /* +08 */ s32 spawn_weight_2;     ///< Weight for item spawn outcome 3
    /* +0C */ s32 empty_weight;       ///< Weight for empty box (no items)
    /* +10 */ s32 x10;                ///< Used when spawning items
    /* +14 */ f32 damage_threshold;   ///< Damage needed to break the box
} itBoxAttributes;

/// Box opens empty (no items spawned). Clears velocity, sets opened flag,
/// spawns smoke effect (0x78), and transitions to state 6.
void it_80286AA4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;

    it_8026BB44(gobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);

    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.b2 = 1;
    ip->xDD4_itemVar.box.opened = 1;
    ip->xDD4_itemVar.box.despawn_timer = 40;

    it_80275444(gobj);

    pos = ip->pos;
    lb_800119DC(&pos, 0x78, 1.0F, 0.02F, 1.0471976F);

    Item_80268E5C(gobj, 6, 2);
}

bool itBox_UnkMotion6_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itBox_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion6_Coll(Item_GObj* gobj)
{
    return false;
}

/// Box opens and spawns items. Plays sound, triggers camera, spawns items,
/// sets opened flag, and transitions to state 7.
void it_80286BA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBoxAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    Item_8026AE84(ip, 0xF6, 0x7F, 0x40);
    Camera_80030E44(2, &ip->pos);
    it_80286248(gobj, attr->spawn_weight_0, attr->spawn_weight_1,
                attr->spawn_weight_2, attr->x10);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    it_802756D0(gobj);

    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.b2 = 1;
    ip->xDD4_itemVar.box.opened = 1;
    ip->xDD4_itemVar.box.despawn_timer = 40;

    it_8026B3A8(gobj);

    Item_80268E5C(gobj, 7, 2);
}

bool itBox_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.box.despawn_timer -= 1;
    if (ip->xDD4_itemVar.box.despawn_timer > 0) {
        return false;
    }
    return true;
}

void itBox_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

/// Inline helper: spawn break effect and roll for item spawn.
/// Used by DmgDealt, Clanked, HitShield, and Reflected callbacks.
static inline void itBox_TryOpen_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBoxAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    efSync_Spawn(0x427, gobj, &ip->pos);
    if (it_80286340(gobj, attr->spawn_weight_0, attr->spawn_weight_1,
                   attr->spawn_weight_2, attr->empty_weight))
    {
        it_80286BA0(gobj);
    } else {
        it_80286AA4(gobj);
    }
}

/// Box dealt damage to something - try to open
bool it_3F14_Logic1_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.box.opened == 0) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

/// Box clanked with another hitbox - try to open
bool it_3F14_Logic1_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.box.opened == 0) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

/// Box hit a shield - try to open
bool it_3F14_Logic1_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.box.opened == 0) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

/// Box was reflected - try to open
bool it_3F14_Logic1_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.box.opened == 0) {
        itBox_TryOpen_inline(gobj);
    }
    return false;
}

/// Handle damage received by box. When accumulated damage reaches threshold,
/// box breaks open. Weighted random roll determines if items spawn or box is
/// empty. Effect 0x427 is the box breaking visual effect.
bool it_3F14_Logic1_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBoxAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(16);
    if (ip->xDD4_itemVar.box.opened == 0) {
        if (ip->xC9C >= attr->damage_threshold) {
            efSync_Spawn(0x427, gobj, &ip->pos);
            if (it_80286340(gobj, attr->spawn_weight_0, attr->spawn_weight_1,
                           attr->spawn_weight_2, attr->empty_weight))
            {
                it_80286BA0(gobj);
            } else {
                it_80286AA4(gobj);
            }
        }
    }
    return false;
}

void it_3F14_Logic1_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itBox_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80286480, it_8028655C);
    return false;
}

void it_3F14_Logic1_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// Transition box to state 8 and set accessory callback
void it_802870A4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762B0(ip);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    ip->on_accessory = (HSD_GObjEvent) it_8028733C;
}

bool itBox_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itBox_UnkMotion8_Phys

bool itBox_UnkMotion8_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_8028733C
