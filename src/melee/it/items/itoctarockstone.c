#include "itoctarockstone.h"

#include "ft/ftlib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/random.h>

ItemStateTable it_803F8E90[] = {
    { 0, itOctarockstone_UnkMotion0_Anim, itOctarockstone_UnkMotion0_Phys,
      itOctarockstone_UnkMotion0_Coll },
    { 0, itOctarockstone_UnkMotion1_Anim, itOctarockstone_UnkMotion1_Phys,
      itOctarockstone_UnkMotion1_Coll }
};

void itOctarockstone_802E878C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD5C = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_80275474(gobj);
    itOctarockstone_802E883C(gobj);
}

bool itOctarockstone_Logic4_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itOctarockstone_Logic4_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itOctarockstone_Logic4_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itOctarockstone_Logic4_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itOctarockstone_Logic4_Reflected(Item_GObj* gobj)
{
    it_80273030(gobj);
    return false;
}

bool itOctarockstone_Logic4_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void itOctarockstone_802E883C(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itOctarockstone_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    return false;
}

void itOctarockstone_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itOctarockstone_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 coll;

    coll = it_8026DAA8(gobj);
    if (coll & 0xF) {
        it_8027781C(gobj);
        if (coll & 0x1) {
            it_802762B0(ip);
        }
        itOctarockstone_802E890C(gobj);
    }
    return false;
}

void itOctarockstone_802E890C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    Item_8026AE84(ip, 0x138, 0x7F, 0x40);
}

bool itOctarockstone_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itOctarockstone_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itOctarockstone_UnkMotion1_Coll(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}

void itOctarockstone_802E89B0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

static inline f32 getX(f32 x1, f32 x2)
{
    f32 res = x1 - x2;
    if (res < 0.0f) {
        return -res;
    }
    return res;
}

void it_802E89D0(Item_GObj* gobj, f32 horiz_speed, f32 min_vy, f32 max_vy)
{
    HSD_GObj* gp;
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;
    f32 x;
    f32 speed;
    float new_var;

    ip->x40_vel.x = horiz_speed * ip->facing_dir;
    ip->x40_vel.z = 0.0f;

    gp = ftLib_8008627C(&ip->pos, NULL);
    if (gp != NULL) {
        ftLib_800866DC(gp, &pos);
        x = getX(ip->pos.x, pos.x);
        speed = x / horiz_speed;
        x = (new_var = ip->xCC_item_attr->x10_fall_speed * (speed * speed));
        x *= 0.5f;
        ip->x40_vel.y = x / speed;
        ip->x40_vel.y =
            HSD_Randf() * ((pos.y - ip->pos.y) / 10.0f) + ip->x40_vel.y;

        if (ip->x40_vel.y > max_vy) {
            ip->x40_vel.y = max_vy;
        }
        if (ip->x40_vel.y < min_vy) {
            ip->x40_vel.y = min_vy;
        }
        return;
    }
    ip->x40_vel.y = 0.0f;
}

/// @brief Spawn an Octarock stone projectile.
/// @param gobj The parent Octarock gobj.
/// @param pos The spawn position.
/// @param dir The facing direction (-1 or 1).
/// @param horiz_speed Horizontal speed for the stone.
/// @param min_vy Minimum vertical velocity.
/// @param max_vy Maximum vertical velocity.
void it_802E8ADC(Item_GObj* gobj, Vec3* pos, s32 dir, f32 horiz_speed,
                 f32 min_vy, f32 max_vy)
{
    SpawnItem spawn;
    Item_GObj* stone_gobj;

    spawn.kind = It_Kind_Octarock_Stone;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0F;
    it_8026BB88(gobj, &spawn.pos);
    spawn.facing_dir = (f32) dir;
    spawn.x3C_damage = 0;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    stone_gobj = Item_80268B18(&spawn);
    if (stone_gobj != NULL) {
        it_802E89D0(stone_gobj, horiz_speed, min_vy, max_vy);
    }
}
