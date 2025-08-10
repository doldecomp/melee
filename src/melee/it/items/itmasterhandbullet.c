#include <platform.h>
#include <placeholder.h>

#include "it/forward.h"

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "db/db.h"
#include "dolphin/mtx.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"

void it_802F0F04(HSD_GObj* gobj) {}

void it_802F0D2C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itMasterHandBulletAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    Quaternion quad = { 0 };
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->on_accessory = it_802F0F04;
    ip->xDD4_itemVar.masterhandbullet.x0 = attrs->x0;
    it_80274C60(gobj);
    quad.y = 1.5707963267948966 * ip->facing_dir;
    HSD_JObjSetRotation(jobj, &quad);
}

void it_802F0BE8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itMasterHandBulletAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    Quaternion quad = { 0 };
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->on_accessory = it_802F0F04;
    ip->xDD4_itemVar.masterhandbullet.x0 = attrs->x0;
    it_80274C60(gobj);
    quad.y = 1.5707963267948966 * ip->facing_dir;
    HSD_JObjSetRotation(jobj, &quad);
}

static inline void it_802F0AE0_sub(Item_GObj* gobj, enum_t msid,
                                   Item_GObj* parent_gobj)
{
    if (msid != 0) {
        it_802F0D2C(gobj);
    } else {
        it_802F0BE8(gobj);
    }
    db_80225DD8(gobj, parent_gobj);
    it_802750F8(gobj);
}

void it_802F0AE0(Item_GObj* gobj, Vec3* prev_pos, Vec3* pos, ItemKind kind,
                 s32 msid, f32 facing_dir, f32 vel_x, f32 vel_y)
{
    SpawnItem spawn;
    Item_GObj* spawned;

    spawn.kind = kind;
    spawn.prev_pos = *prev_pos;
    spawn.pos = *pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = vel_x * facing_dir;
    spawn.vel.y = vel_y;
    spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = Item_8026AE60();
    spawned = Item_80268B18(&spawn);
    it_802F0AE0_sub(spawned, msid, gobj);
}

void it_2725_Logic85_EvtUnk(Item_GObj* gobj, Item_GObj* arg1)
{
    it_8026B894(gobj, arg1);
}

bool itMasterhandbullet_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip;
    f32 temp_f1;

    ip = GET_ITEM(gobj);
    efSync_Spawn(0x405, gobj, &ip->pos);
    temp_f1 = ip->xDD4_itemVar.masterhandbullet.x0 - 1.0f;
    ip->xDD4_itemVar.masterhandbullet.x0 = temp_f1;
    if (temp_f1 < 0.0f) {
        return true;
    }
    return false;
}

void itMasterhandbullet_UnkMotion1_Phys(Item_GObj* gobj) {}

void it_802F0F08(Item_GObj* gobj) {}

bool itMasterhandbullet_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802F0F08);
    return false;
}

bool it_2725_Logic83_DmgDealt(Item_GObj* gobj)
{
    return true;
}

bool it_2725_Logic83_Reflected(Item_GObj* gobj)
{
    return it_8027AE34(gobj);
}

bool it_2725_Logic83_Clanked(Item_GObj* gobj)
{
    return true;
}

bool it_2725_Logic83_Absorbed(Item_GObj* gobj)
{
    return true;
}

bool it_2725_Logic83_ShieldBounced(Item_GObj* gobj)
{
    return it_8027AF50(gobj);
}

bool it_2725_Logic83_HitShield(Item_GObj* gobj)
{
    return true;
}
