#include "ityoshieggthrow.h"

#include "ef/efasync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

ItemStateTable it_803F7118[] = {
    {
        -1,
        NULL,
        NULL,
        NULL,
    },
    {
        0,
        itYoshieggthrow_UnkMotion1_Anim,
        itYoshieggthrow_UnkMotion1_Phys,
        itYoshieggthrow_UnkMotion1_Coll,
    },
    {
        1,
        itYoshieggthrow_UnkMotion2_Anim,
        NULL,
        NULL,
    },
};

void it_802B2890(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->owner = NULL;
    ip->xDC8_word.flags.x13 = false;
    Item_8026A8EC(gobj);
}

void it_802B28C8(Item_GObj* gobj, Vec3* pos, Vec3* offset, f32 facing_dir,
                 f32 unused)
{
    Item* ip = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;

    it_802B2B08(gobj);
    it_8027429C(gobj, pos);
    ip->xDC8_word.flags.x14 = 0;
    it_8026B3A8(gobj);
    ip->pos.x += offset->x;
    ip->pos.y += offset->y;
    ip->pos.z += offset->z;
    HSD_JObjSetTranslate(jobj, &ip->pos);
    it_80274658(gobj, facing_dir);
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

void itYoshiEggThrow_Logic43_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

void it_802B2B08(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itYoshiEggThrowAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attrs->x0);
}

bool itYoshieggthrow_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xD44_lifeTimer <= 0.0f) {
        it_802B2C38(gobj);
    } else {
        ip->xD44_lifeTimer -= 1.0f;
    }

    return false;
}

void itYoshieggthrow_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itYoshieggthrow_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E5A0(gobj, it_802B2C38);
    return 0;
}

bool it_802B2C04(Item_GObj* gobj)
{
    if (((Item*) gobj->user_data)->msid != 2) {
        it_802B2C38(gobj);
    }
    return false;
}

static inline void spawn1(HSD_GObj* gobj, HSD_JObj* jobj)
{
    Item* ip = GET_ITEM(gobj);
    efAsync_Spawn(gobj, &ip->xBC0, 1, 0x4CE, jobj);
}

static inline void spawn2(HSD_GObj* gobj, HSD_JObj* jobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 scale;
    scale = 1.0f;
    efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 4, 0x4CF, jobj, &scale);
}

void it_802B2C38(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itYoshiEggThrowAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = gobj->hsd_obj;
    Item_80268E5C(gobj, 2, 0x12);
    it_8026BB44(gobj);
    it_80273598(gobj, 0xC, 0xA);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_80273454(gobj);
    ip->xD44_lifeTimer = attrs->x4;
    spawn1(gobj, jobj);
    spawn2(gobj, jobj);
    Item_8026AE84(ip, 0x44618, 0x7F, 0x40);
}

bool itYoshieggthrow_UnkMotion2_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

bool it_2725_Logic43_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid != 2) {
        it_802B2C38(gobj);
    }
    return false;
}

bool it_802B2E5C(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802B2E7C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid != 2) {
        it_802B2C38(gobj);
    }
    return false;
}

bool it_802B2F88(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_802B2FA8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
