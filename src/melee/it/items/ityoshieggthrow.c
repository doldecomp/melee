#include "ityoshieggthrow.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "ef/efasync.h"

void it_802B2890(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->owner = NULL;
    ip->xDC8_word.flags.x13 = false;
    Item_8026A8EC(gobj);
}

void itYoshiEggThrow_Logic43_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

Item_GObj* it_802B2A10(Fighter_GObj* parent, Vec3* pos, s32 part,
                        f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    PAD_STACK(8);

    spawn.kind = It_Kind_Yoshi_EggThrow;
    spawn.prev_pos = *pos;
    it_8026BB68(parent, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0f;
    spawn.vel.y = 0.0f;
    spawn.vel.x = 0.0f;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        Item_8026AB54(gobj, parent, part);
    }
    return gobj;
}

void it_802B2B08(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM((HSD_GObj*) item_gobj);
    f32* unkc4_unk4 = item->xC4_article_data->x4_specialAttributes;
    Item_80268E5C((HSD_GObj*) item_gobj, 1, ITEM_ANIM_UPDATE);
    it_80275158(item_gobj, *unkc4_unk4);
}

bool itYoshieggthrow_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32* base = (f32*) ip;

    if (base[0xD44 / 4] <= 0.0f) {
        it_802B2C38(gobj);
    } else {
        base[0xD44 / 4] -= 1.0f;
    }

    return false;
}

bool itYoshieggthrow_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E5A0(gobj, it_802B2C38);
    return 0;
}

void it_802B2FA8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itYoshieggthrow_UnkMotion2_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

bool it_802B2E5C(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802B2F88(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void itYoshieggthrow_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool it_802B2C04(Item_GObj* gobj)
{
    if (((Item*) gobj->user_data)->msid != 2) {
        it_802B2C38(gobj);
    }
    return false;
}

void it_802B2C38(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32* attrs = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 scale;
    PAD_STACK(12);
    Item_80268E5C(gobj, 2, 0x12);
    it_8026BB44(gobj);
    it_80273598(gobj, 0xC, 0xA);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_80273454(gobj);
    ip->xD44_lifeTimer = attrs[1];
    efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 1, 0x4CE, jobj);
    scale = 1.0f;
    efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 4, 0x4CF, jobj, &scale);
    Item_8026AE84(ip, 0x44618, 0x7F, 0x40);
}

/// #it_802B2D50

/// #it_802B2E7C
