#include "itstarrodstar.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/jobj.h"
#include "db/db.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "it/types.h"

#include "lb/forward.h"

#include <MSL/trigf.h>

ItemStateTable it_803F6530[] = { { 0, itStarrodstar_UnkMotion0_Anim,
                                   itStarrodstar_UnkMotion0_Phys,
                                   itStarrodstar_UnkMotion0_Coll } };

typedef struct StarRodStarAttrs {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    int x14;
    int x18;
    float x1C;
} StarRodStarAttrs;

void it_802988E4(Fighter_GObj* gobj, Vec* vec, int arg2, float arg3)
{
    HSD_GObj* n;
    SpawnItem si;
    si.kind = It_Kind_StarRod_Star;
    si.prev_pos = *vec;
    si.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &si.pos);
    si.facing_dir = arg3;
    si.x3C_damage = 0;
    si.vel.x = si.vel.y = si.vel.z = 0.0f;
    si.x0_parent_gobj = gobj;
    si.x4_parent_gobj2 = si.x0_parent_gobj;
    si.x44_flag.b0 = 1;
    si.x40 = 0;
    n = Item_80268B18(&si);
    if (n != NULL) {
        Item* ip = GET_ITEM(n);
        ip->xDD4_itemVar.starrodstar.x0 = arg2;
        it_802989C8(n, gobj);
        db_80225DD8(n, gobj);
    }
}

void it_802989C8(Item_GObj* ig, Fighter_GObj* fg)
{
    Item* ip = GET_ITEM(ig);
    StarRodStarAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    HitCapsule* hit;
    it_8026B3A8(ig);
    it_80274740(ig);
    Item_80268E5C(ig, 0, ITEM_ANIM_UPDATE);
    hit = &ip->x5D4_hitboxes[0].hit;
    if (ip->xDD4_itemVar.starrodstar.x0 != 0) {
        it_80275158(ig, attrs->x10);
        ip->x40_vel.x = ip->facing_dir * (attrs->x0 * attrs->x8);
        it_80272460(hit, attrs->x18, ig);
    } else {
        it_80275158(ig, attrs->xC);
        ip->x40_vel.x = ip->facing_dir * (attrs->x0 * attrs->x4);
        it_80272460(hit, attrs->x14, ig);
    }
    ip->xDD4_itemVar.starrodstar.x4 = attrs->x1C * ip->facing_dir;
    ip->xDCE_flag.b7 = 0;
}

bool itStarrodstar_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);
    ip->xD44_lifeTimer -= 1.0f;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    HSD_JObjAddRotationZ(jobj, ip->xDD4_itemVar.starrodstar.x4);
    return false;
}

void itStarrodstar_UnkMotion0_Phys(Item_GObj* gobj)
{
    return;
}

bool itStarrodstar_UnkMotion0_Coll(Item_GObj* gobj)
{
    if (it_8026DFB0(gobj) != 0) {
        return true;
    }
    return false;
}

bool itStarRodStar_Logic36_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itStarRodStar_Logic36_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itStarRodStar_Logic36_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itStarRodStar_Logic36_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itStarRodStar_Logic36_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);
    it_80273030(gobj);
    HSD_JObjSetRotationZ(jobj, atan2f(ip->x40_vel.y, ip->x40_vel.x));
    return false;
}

bool itStarRodStar_Logic36_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);
    itColl_BounceOffShield(gobj);
    HSD_JObjSetRotationZ(jobj, atan2f(ip->x40_vel.y, ip->x40_vel.x));
    return false;
}

void itStarRodStar_Logic36_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
