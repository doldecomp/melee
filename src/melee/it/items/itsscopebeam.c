#include "itsscopebeam.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "db/db.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

typedef struct BeamFloats {
    float velocity;
    float scale;
    float lifetime;
} BeamFloats;

typedef struct ScopeBeamAttrs {
    BeamFloats floats[9];
} ScopeBeamAttrs;

void it_80298DEC(Fighter_GObj* gobj, Vec* vec, int arg2, float arg3)
{
    HSD_GObj* n;
    SpawnItem si;
    si.kind = It_Kind_S_Scope_Beam;
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
        ip->xDD4_itemVar.scopebeam.x0 = arg2;
        it_80298ED0(n, gobj);
        db_80225DD8(n, gobj);
    }
}

void it_80298ED0(HSD_GObj* projectile, HSD_GObj* owner)
{
    Item* it = GET_ITEM(projectile);
    BeamFloats* data;
    HSD_JObj* jobj = GET_JOBJ(projectile);
    ScopeBeamAttrs* attrs = it->xC4_article_data->x4_specialAttributes;
    Vec3 scale;

    it->owner = owner;
    data = &attrs->floats[it->xDD4_itemVar.scopebeam.x0];
    it_8026B3A8(projectile);
    switch (it->xDD4_itemVar.scopebeam.x0) {
    case 0:
        Item_80268E5C(projectile, 0, ITEM_ANIM_UPDATE);
        break;
    case 1:
        Item_80268E5C(projectile, 1, ITEM_ANIM_UPDATE);
        break;
    case 2:
        Item_80268E5C(projectile, 2, ITEM_ANIM_UPDATE);
        break;
    case 3:
        Item_80268E5C(projectile, 3, ITEM_ANIM_UPDATE);
        break;
    case 4:
        Item_80268E5C(projectile, 4, ITEM_ANIM_UPDATE);
        break;
    case 5:
        Item_80268E5C(projectile, 5, ITEM_ANIM_UPDATE);
        break;
    case 6:
        Item_80268E5C(projectile, 6, ITEM_ANIM_UPDATE);
        break;
    case 7:
        Item_80268E5C(projectile, 7, ITEM_ANIM_UPDATE);
        break;
    case 8:
        Item_80268E5C(projectile, 8, ITEM_ANIM_UPDATE);
        break;
    case 9:
        Item_80268E5C(projectile, 9, ITEM_ANIM_UPDATE);
        break;
    }

    it->x40_vel.x = data->velocity * it->facing_dir;
    scale.x = scale.y = scale.z = data->scale;
    HSD_JObjSetScale(jobj, &scale);
    it_80275158(projectile, data->lifetime);
}

bool itSscopebeam_UnkMotion9_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 index = ip->xDD4_itemVar.scopebeam.x0;
    ScopeBeamAttrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    BeamFloats* data = &attrs->floats[index];

    if (ip->xD44_lifeTimer == data->lifetime) {
        if (ip->x5D4_hitboxes[0].hit.state >= 1) {
            ip->x5D4_hitboxes[0].hit.scale =
                ip->x5D4_hitboxes[0].hit.scale * data->scale;
        }
    }

    ip->xD44_lifeTimer = ip->xD44_lifeTimer - 1.0f;

    if (ip->xD44_lifeTimer <= 0.0f) {
        ip->xD44_lifeTimer = 0.0f;
        return true;
    }

    return false;
}

void itSscopebeam_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itSscopebeam_UnkMotion9_Coll

bool itSScopeBeam_Logic38_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itSScopeBeam_Logic38_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itSScopeBeam_Logic38_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itSScopeBeam_Logic38_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itSScopeBeam_Logic38_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool itSScopeBeam_Logic38_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

void itSScopeBeam_Logic38_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
