#include "itcrazyhandbomb.h"

#include "db/db.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <baselib/random.h>
#include <MSL/math.h>

ItemStateTable it_803F93A8[] = {
    { 0, itCrazyhandbomb_UnkMotion0_Anim, itCrazyhandbomb_UnkMotion0_Phys,
      itCrazyhandbomb_UnkMotion0_Coll },
    { 1, itCrazyhandbomb_UnkMotion1_Anim, itCrazyhandbomb_UnkMotion1_Phys,
      itCrazyhandbomb_UnkMotion1_Coll },
};

void it_802F0F6C(Fighter_GObj* owner, Vec3* prev_pos, Vec3* pos, ItemKind kind,
                 f32 facing_dir)
{
    SpawnItem spawnitem;
    Item_GObj* gobj;
    PAD_STACK(12);

    spawnitem.kind = kind;
    spawnitem.prev_pos = *prev_pos;
    spawnitem.pos = *pos;
    spawnitem.facing_dir = facing_dir;
    spawnitem.x3C_damage = 0;
    spawnitem.vel.x = spawnitem.vel.y = spawnitem.vel.z = 0.0F;
    spawnitem.x0_parent_gobj = owner;
    spawnitem.x4_parent_gobj2 = spawnitem.x0_parent_gobj;
    spawnitem.x44_flag.b0 = true;
    spawnitem.x40 = 0;
    gobj = Item_80268B18(&spawnitem);
    it_802F10F8(gobj);
    db_80225DD8(gobj, owner);
    it_802750F8(gobj);
}

void it_802F1030(Item_GObj* gobj)
{
    PAD_STACK(8);
    HSD_JObjSetFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_80273454(gobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_802F1344(gobj);
}

void itCrazyHandBomb_Logic86_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

bool itCrazyHandBomb_Logic86_DmgDealt(Item_GObj* gobj)
{
    it_802F1344(gobj);
    return 1;
}

bool itCrazyHandBomb_Logic86_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

void it_802F10F8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itCrazyHandBombAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    it_802762BC(ip);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->on_accessory = (HSD_GObjEvent) it_802F1340;
    ip->x40_vel.y = attrs->x0;
}

bool itCrazyhandbomb_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itCrazyhandbomb_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itCrazyHandBombAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Quaternion rot;

    it_80272860(gobj, attrs->x4, attrs->x8);
    HSD_JObjGetRotation(jobj, &rot);

    switch (HSD_Randi(3)) {
    case 0:
        rot.x += deg_to_rad * (10.0f * ip->x40_vel.y);
        break;
    case 1:
        rot.y += deg_to_rad * (10.0f * ip->x40_vel.y);
        break;
    case 2:
        rot.z += deg_to_rad * (10.0f * ip->x40_vel.y);
        break;
    }

    HSD_JObjSetRotation(jobj, &rot);
}

bool itCrazyhandbomb_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_8026E71C(gobj, it_802F1030);
    }
    return false;
}

void it_802F1340(void) {}

void it_802F1344(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->on_accessory = it_802F13B0;
}

bool itCrazyhandbomb_UnkMotion1_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itCrazyhandbomb_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itCrazyhandbomb_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802F13B0(HSD_GObj* gobj) {}
