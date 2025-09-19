#include "itzeldadinfireexplode.h"

#include "placeholder.h"

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "cm/camera.h"
#include "db/db.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/itcoll.h"
#include "it/item.h"

/* 2C4998 */ bool itZeldadinfireexplode_UnkMotion0_Coll(Item_GObj* gobj);

ItemStateTable it_803F7740[] = { { 0, itZeldadinfireexplode_UnkMotion0_Anim,
                                   itZeldadinfireexplode_UnkMotion0_Phys,
                                   itZeldadinfireexplode_UnkMotion0_Coll } };

Item_GObj* it_802C4580(Item_GObj* parent_gobj, HSD_GObj* arg1, Point3d* pos,
                       f32 facing_dir, f32 scale)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    PAD_STACK(4);

    spawn.kind = It_Kind_Zelda_DinFire_Explode;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent_gobj;
    spawn.x4_parent_gobj2 = arg1;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        ip->xDD4_itemVar.zeldadinfireexplode.xDD4 = scale;
        ip->xDD4_itemVar.zeldadinfireexplode.xDDC = parent_gobj;
        it_802C46C4(gobj, ip);
    }
    return gobj;
}

void it_2725_Logic66_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802725D4(gobj);
    ip->owner = NULL;
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.zeldadinfireexplode.xDE0 = 0;
}

void it_802C46C4(Item_GObj* gobj, Item* arg1)
{
    Item* ip;
    itZeldaDinFireExplodeAttributes* attrs;
    HSD_JObj* jobj;
    f32 temp_f1;

    ip = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = 0;
    it_80272940(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, 60.0f);
    ip->xDD4_itemVar.zeldadinfireexplode.xDD8 = 0.0f;
    efSync_Spawn(0x4FA, gobj, jobj);
    ip->xDD4_itemVar.zeldadinfireexplode.xDE0 = 1;
    Item_802694CC(gobj);
    itZeldadinfireexplode_UnkMotion0_Anim(gobj);
    temp_f1 = ip->xDD4_itemVar.zeldadinfireexplode.xDD4 / attrs->x0;
    if (temp_f1 < 0.4375f) {
        it_80273598(gobj, 0xB, 0xA);
    } else if (temp_f1 < 0.625f) {
        it_80273598(gobj, 0xC, 0xA);
    } else if (temp_f1 < 0.8125f) {
        it_80273598(gobj, 0xD, 0xF);
        Camera_80030E44(2, &ip->pos);
    } else {
        it_80273598(gobj, 0xE, 0x14);
        Camera_80030E44(3, &ip->pos);
    }
    db_80225DD8(gobj, ip->owner);
}

bool itZeldadinfireexplode_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itZeldaDinFireExplodeAttributes* attrs;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 temp_f1;
    Vec3 scale;

    attrs = ip->xC4_article_data->x4_specialAttributes;

    temp_f1 = (attrs->x8 - attrs->x4) / attrs->x0;
    scale.x = scale.y = scale.z =
        ip->xDD4_itemVar.zeldadinfireexplode.xDD4 * temp_f1 + attrs->x4;
    HSD_JObjSetScale(jobj, &scale);

    if (ip->x5D4_hitboxes[0].hit.state != HitCapsule_Disabled) {
        temp_f1 = (ip->xDD4_itemVar.zeldadinfireexplode.xDD4 * attrs->x10 +
                   attrs->xC);
        it_80272460(&ip->x5D4_hitboxes[0].hit, temp_f1, gobj);

        if (ip->xDD4_itemVar.zeldadinfireexplode.xDD8 == 0.0f) {
            ip->xDD4_itemVar.zeldadinfireexplode.xDD8 =
                ip->x5D4_hitboxes[0].hit.scale;
        }

        ip->x5D4_hitboxes[0].hit.scale =
            ip->xDD4_itemVar.zeldadinfireexplode.xDD8 * scale.x;
    }

    return it_80273130(gobj);
}

void itZeldadinfireexplode_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
#ifndef BUGFIX
    ip->x40_vel.z = ip->x40_vel.y = ip->x40_vel.z = 0.0F;
#else
    itResetVelocity(ip);
#endif
}

bool itZeldadinfireexplode_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_2725_Logic66_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic66_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic66_ShieldBounced(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic66_HitShield(Item_GObj* arg0)
{
    return true;
}

void it_2725_Logic66_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
