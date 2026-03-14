#include "itnesspkflushexplode.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "db/db.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"

#include <baselib/jobj.h>

/* 2AFD44 */ static bool itNesspkflushexplode_UnkMotion0_Coll(Item_GObj* gobj);

Item_GObj* it_802AF940(Item_GObj* owner, Item_GObj* flash, Vec3* pos,
                       ItemKind kind, f32 facing_dir, f32 charge)
{
    SpawnItem spawn;
    Item_GObj* explode;
    PAD_STACK(4);

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = flash;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    explode = Item_80268B18(&spawn);
    if (explode != NULL) {
        Item* ip = GET_ITEM(explode);
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        ip->xDD4_itemVar.pkflushexplode.xDD4 = charge;
        ip->xDD4_itemVar.pkflushexplode.xDDC = owner;
        it_802AFA70(explode);
    }
    return explode;
}

void it_2725_Logic103_Destroyed(Item_GObj* item_gobj)
{
    if (item_gobj != NULL) {
        Item* item = GET_ITEM(item_gobj);
        if (item != NULL) {
            it_802725D4(item_gobj);
            item->owner = NULL;
        }
    }
}

void it_802AFA70(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlashExplAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 ratio;
    PAD_STACK(8);

    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = 0;
    it_80272940(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, 1024.0f);
    ip->xDD4_itemVar.pkflushexplode.xDD8 = 0.0f;
    Item_802694CC(gobj);
    itNesspkflushexplode_UnkMotion0_Anim(gobj);

    ratio = ip->xDD4_itemVar.pkflushexplode.xDD4 /
            attr->x0_FLASH_EXPL_HITBOX_SIZE_MUL;
    if (ratio > 0.84999996f) {
        Camera_80030E44(3, &ip->pos);
        it_80273598(gobj, 0xE, 0x14);
    } else if (ratio > 0.65f) {
        Camera_80030E44(2, &ip->pos);
        it_80273598(gobj, 0xD, 0xF);
    } else if (ratio > 0.45f) {
        it_80273598(gobj, 0xC, 0xA);
    } else {
        it_80273598(gobj, 0xB, 5);
    }
    db_80225DD8(gobj, ip->owner);
}

bool itNesspkflushexplode_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFlashExplAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 scale;
    scale.x = scale.y = scale.z = (ip->xDD4_itemVar.pkflushexplode.xDD4 *
                                   ((attr->x8_FLASH_EXPL_GRAPHIC_SIZE_GROWTH -
                                     attr->x4_FLASH_EXPL_GRAPHIC_SIZE_INIT) /
                                    attr->x0_FLASH_EXPL_HITBOX_SIZE_MUL)) +
                                  attr->x4_FLASH_EXPL_GRAPHIC_SIZE_INIT;
    HSD_JObjSetScale(jobj, &scale);

    if (ip->xDB4_itcmd_var2 == 0 &&
        ip->x5D4_hitboxes[0].hit.state != HitCapsule_Disabled)
    {
        it_80272460(&ip->x5D4_hitboxes[0].hit,
                    (ip->xDD4_itemVar.pkflushexplode.xDD4 *
                     attr->x10_FLASH_EXPL_DAMAGE_MUL) +
                        attr->xC_FLASH_EXPL_BASE_DAMAGE,
                    gobj);
        ip->xDB4_itcmd_var2 = 1;
    }

    if (ip->xDD4_itemVar.pkflushexplode.xDD8 == 0.0f) {
        ip->xDD4_itemVar.pkflushexplode.xDD8 = ip->x5D4_hitboxes[0].hit.scale;
    }
    ip->x5D4_hitboxes[0].hit.scale =
        ip->xDD4_itemVar.pkflushexplode.xDD8 * scale.x;

    if (it_80272C6C(gobj) == false) {
        return true;
    }
    return false;
}

void itNesspkflushexplode_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    it->x40_vel.z = it->x40_vel.y = it->x40_vel.z = 0;
}

bool itNesspkflushexplode_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

bool itNessPKFlushExplode_Logic103_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itNessPKFlushExplode_Logic103_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itNessPKFlushExplode_Logic103_ShieldBounced(Item_GObj* arg0)
{
    return true;
}

bool itNessPKFlushExplode_Logic103_HitShield(Item_GObj* arg0)
{
    return true;
}

void itNessPKFlushExplode_Logic103_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
