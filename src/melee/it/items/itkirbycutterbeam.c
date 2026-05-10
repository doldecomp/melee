#include "itkirbycutterbeam.h"

#include "db/db.h"
#include "ft/chara/ftKirby/ftKb_Init.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <math.h>
#include <MSL/trigf.h>

ItemStateTable it_803F6798[] = {
    NULL,
    itKirbycutterbeam_UnkMotion0_Anim,
    itKirbycutterbeam_UnkMotion0_Phys,
    itKirbycutterbeam_UnkMotion0_Coll,
};

void it_8029BAB8(HSD_GObj* gobj, Vec3* pos, float facing_dir)
{
    Item_GObj* spawned_gobj;

    SpawnItem spawn;
    pos->z = 0.0f;
    spawn.kind = It_Kind_Kirby_CBeam;
    spawn.prev_pos = *pos;
    it_8026BB68(gobj, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    spawned_gobj = Item_80268B18(&spawn);
    if (spawned_gobj != NULL) {
        it_8029BB90(spawned_gobj, gobj);
        db_80225DD8(spawned_gobj, gobj);
        it_802750F8(spawned_gobj);
    }
}

void it_8029BB90(Item_GObj* gobj, HSD_GObj* owner)
{
    Item* ip = GET_ITEM(gobj);
    itKirbyCutterBeamAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);

    ip->xDD4_itemVar.kirbycutterbeam.angle =
        ftKb_AttackDashAir_800F21C0(owner);
    ip->xDD4_itemVar.kirbycutterbeam.speed = attr->x0_speed;
    ip->x40_vel.x =
        ip->facing_dir * (ip->xDD4_itemVar.kirbycutterbeam.speed *
                          cosf(ip->xDD4_itemVar.kirbycutterbeam.angle));
    ip->x40_vel.y = -ip->xDD4_itemVar.kirbycutterbeam.speed *
                    sinf(ip->xDD4_itemVar.kirbycutterbeam.angle);
    ip->x40_vel.z = 0.0F;
    it_80275158(gobj, attr->x8_lifetime);
    Item_80268E5C(gobj, 0, 2);
    it_802762B0(ip);
    ip->xDD4_itemVar.kirbycutterbeam.dir.x =
        ip->facing_dir * sinf(ip->xDD4_itemVar.kirbycutterbeam.angle);
    ip->xDD4_itemVar.kirbycutterbeam.dir.y =
        cosf(ip->xDD4_itemVar.kirbycutterbeam.angle);
    ip->xDD4_itemVar.kirbycutterbeam.dir.z = 0.0F;
    ip->xDD4_itemVar.kirbycutterbeam.init_pos = ip->pos;
}

bool itKirbycutterbeam_UnkMotion0_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

void itKirbycutterbeam_UnkMotion0_Phys(Item_GObj* gobj)
{
    itKirbyCutterBeamAttributes* attr;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(GET_JOBJ(gobj));
    PAD_STACK(8);
    attr = ip->xC4_article_data->x4_specialAttributes;

    ip->xDD4_itemVar.kirbycutterbeam.init_pos = ip->pos;
    ip->x40_vel.x =
        ip->facing_dir * (ip->xDD4_itemVar.kirbycutterbeam.speed *
                          cosf(ip->xDD4_itemVar.kirbycutterbeam.angle));
    ip->x40_vel.y = -ip->xDD4_itemVar.kirbycutterbeam.speed *
                    sinf(ip->xDD4_itemVar.kirbycutterbeam.angle);
    if (ip->ground_or_air == GA_Ground) {
        if (ip->x40_vel.y < 0.0f) {
            ip->x40_vel.y += (0.05f * ip->x40_vel.y);
        }
    }
    ip->x40_vel.z = 0.0f;
    ip->xDD4_itemVar.kirbycutterbeam.speed -= attr->xC_decel;
    if (ip->xDD4_itemVar.kirbycutterbeam.speed < 0.01f) {
        ip->xDD4_itemVar.kirbycutterbeam.speed = 0.01f;
    }
    if (ip->xD44_lifeTimer <= 5.0f) {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    }
}

bool itKirbycutterbeam_UnkMotion0_Coll(Item_GObj* gobj)
{
    Vec3 normal;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(16);

    if (ip->ground_or_air == GA_Ground) {
        normal = ip->x378_itemColl.floor.normal;
        if (it_8026D564(gobj)) {
            atan2f(normal.x, normal.y);
            ip->xDD4_itemVar.kirbycutterbeam.angle =
                ip->facing_dir * atan2f(ip->x378_itemColl.floor.normal.x,
                                        ip->x378_itemColl.floor.normal.y);
        } else {
            it_802762BC(ip);
            ip->pos.y += 0.001f;
            ip->x378_itemColl.last_pos.y += 0.001f;
        }
    } else if (it_8026DA08(gobj)) {
        it_802762B0(ip);
        ip->xDD4_itemVar.kirbycutterbeam.angle =
            ip->facing_dir * atan2f(ip->x378_itemColl.floor.normal.x,
                                    ip->x378_itemColl.floor.normal.y);
    }

    HSD_JObjSetRotationX(jobj, ip->xDD4_itemVar.kirbycutterbeam.angle);

    if (ip->x40_vel.x == 0.0f) {
        s32 flags = ip->x378_itemColl.env_flags;
        if ((flags & Collide_LeftWallMask) || (flags & Collide_RightWallMask))
        {
            return true;
        }
    } else if (ip->x40_vel.x > 0.0f) {
        if (ip->x378_itemColl.env_flags & Collide_LeftWallMask) {
            return true;
        }
    } else {
        if (ip->x378_itemColl.env_flags & Collide_RightWallMask) {
            return true;
        }
    }
    return false;
}

bool itKirbyCutterBeam_Logic7_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool itKirbyCutterBeam_Logic7_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itKirbyCutterBeam_Logic7_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic7_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;

    ip->facing_dir = -ip->facing_dir;
    ip->x40_vel.x = -ip->x40_vel.x;
    ip->x40_vel.y = -ip->x40_vel.y;

    if (ip->ground_or_air == GA_Ground) {
        ip->xDD4_itemVar.kirbycutterbeam.angle =
            ip->facing_dir * atan2f(ip->x378_itemColl.floor.normal.x,
                                    ip->x378_itemColl.floor.normal.y);
    } else {
        ip->xDD4_itemVar.kirbycutterbeam.angle =
            ((ip->facing_dir == 1.0f) ? 0.0 : M_PI) +
            atan2f(ip->x40_vel.y, ip->x40_vel.x);
    }

    while (ip->xDD4_itemVar.kirbycutterbeam.angle < 0.0f) {
        ip->xDD4_itemVar.kirbycutterbeam.angle += M_TAU;
    }
    while (ip->xDD4_itemVar.kirbycutterbeam.angle > M_TAU) {
        ip->xDD4_itemVar.kirbycutterbeam.angle -= M_TAU;
    }

    HSD_JObjSetRotationX(jobj, ip->xDD4_itemVar.kirbycutterbeam.angle);
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);
    return false;
}

bool it_2725_Logic7_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;

    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->xDD4_itemVar.kirbycutterbeam.angle =
        atan2f(ip->x40_vel.y, ip->x40_vel.x);

    while (ip->xDD4_itemVar.kirbycutterbeam.angle < 0.0f) {
        ip->xDD4_itemVar.kirbycutterbeam.angle += M_TAU;
    }
    while (ip->xDD4_itemVar.kirbycutterbeam.angle > M_TAU) {
        ip->xDD4_itemVar.kirbycutterbeam.angle -= M_TAU;
    }

    ip->facing_dir = (ip->x40_vel.x >= 0.0f) ? 1.0f : -1.0f;

    if (ip->ground_or_air == GA_Ground) {
        ip->xDD4_itemVar.kirbycutterbeam.angle =
            ip->facing_dir * atan2f(ip->x378_itemColl.floor.normal.x,
                                    ip->x378_itemColl.floor.normal.y);
    } else {
        ip->xDD4_itemVar.kirbycutterbeam.angle =
            (((ip->facing_dir == 1.0f) ? 0.0 : M_PI) +
             atan2f(ip->x40_vel.y, ip->x40_vel.x));
    }

    while (ip->xDD4_itemVar.kirbycutterbeam.angle < 0.0f) {
        ip->xDD4_itemVar.kirbycutterbeam.angle += M_TAU;
    }
    while (ip->xDD4_itemVar.kirbycutterbeam.angle > M_TAU) {
        ip->xDD4_itemVar.kirbycutterbeam.angle -= M_TAU;
    }

    HSD_JObjSetRotationX(jobj, ip->xDD4_itemVar.kirbycutterbeam.angle);
    HSD_JObjSetRotationY(jobj, (M_PI_2 * ip->facing_dir));
    return false;
}

bool itKirbyCutterBeam_Logic7_HitShield(Item_GObj* arg0)
{
    return true;
}

void it_8029C4B4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
