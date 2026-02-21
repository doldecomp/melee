#include "itsamusbomb.h"

#include "math_ppc.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/mtx.h"
#include "db/db.h"
#include "ftSamus/ftSs_Init.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

Item_GObj* it_802B4AC8(Fighter_GObj* gobj, Vec3* pos, f32 facing_dir)
{
    HSD_GObj* n;
    SpawnItem si;
    si.kind = It_Kind_Samus_Bomb;
    si.prev_pos = *pos;
    si.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &si.pos);
    si.facing_dir = facing_dir;
    si.x3C_damage = 0;
    si.vel.x = si.vel.y = si.vel.z = 0.0f;
    si.x0_parent_gobj = gobj;
    si.x4_parent_gobj2 = si.x0_parent_gobj;
    si.x44_flag.b0 = true;
    si.x40 = 0;
    n = Item_80268B18(&si);
    if (n != NULL) {
        it_802B4BA0(n);
        db_80225DD8(n, gobj);
        return n;
    } else {
        return NULL;
    }
}

void it_802B4BA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusBombAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->x40_vel.y = ip->xCC_item_attr->x18;
    ip->xDB4_itcmd_var2 = 0;
    ip->xDD4_itemVar.bombhei.xDD8 = (long) ip->owner;
    it_80275158(gobj, attr->x0);
    it_8026B3A8(gobj);
    Item_80268E5C((HSD_GObj*) gobj, 1, ITEM_ANIM_UPDATE);
}

void it_802B4C10(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, 0x11);
}

bool itSamusbomb_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    itSamusBombAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    if (ip->xD44_lifeTimer <= attr->x4) {
        lb_8000BA0C(jobj, attr->x8);
    }

    if (ip->xD44_lifeTimer <= 0.0f) {
        it_802B53CC(gobj);
    } else {
        --ip->xD44_lifeTimer;
    }
    return false;
}

void itSamusbomb_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSamusbomb_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802B4CF4);
    return false;
}

void it_802B4CF4(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 0x11);
}

/// #itSamusbomb_UnkMotion1_Anim

void itSamusbomb_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itSamusbomb_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E248(gobj, it_802B4C10);
    return false;
}

void itSamusBomb_Logic50_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, 0x11);
}

/// #itSamusbomb_UnkMotion2_Anim

/// NOTE: 4 iterations instead of the usual 3
static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;

    volatile float y;

    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

void itSamusbomb_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSamusBombAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (my_sqrtf(VEC2_SQ_LEN(ip->x7C)) > attr->xC) {
        f32 mult;
        {
            lbVector_NormalizeXY(&ip->x7C);
            mult = attr->xC;
            ip->x7C.x *= mult;
            ip->x7C.y *= mult;
        }
    }
}

bool itSamusbomb_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802B4C10, it_802B4CF4);
    return false;
}

bool itSamusBomb_Logic50_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid != 3) {
        it_802B53CC(gobj);
    }
    return false;
}

bool itSamusBomb_Logic50_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid != 3) {
        it_802B53CC(gobj);
    }
    return false;
}

bool itSamusBomb_Logic50_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid != 3) {
        it_802B53CC(gobj);
    }
    return false;
}

bool itSamusBomb_Logic50_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool it_2725_Logic50_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 yvel;

    it_80273030(gobj);
    yvel = ip->x40_vel.y;
    if (yvel < 0.0f) {
        ip->x40_vel.y = -yvel * ip->xC70;
    }
    ip->xDD4_itemVar.bombhei.xDD8 = 0;
    return false;
}

void it_802B53CC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    ip->x5D0_animFrameSpeed = 1.0f;
    it_80273454(gobj);
    it_8026BB44(gobj);
    it_80272B40(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    ip->on_accessory = it_802B5478;
    ip->xDD4_itemVar.bombhei.xDD4 = 1;
}

bool itSamusbomb_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void it_802B5478(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.bombhei.xDD4 != 0) {
        ip->xDD4_itemVar.bombhei.xDD4 = 0;

        if (ip->xDD4_itemVar.bombhei.xDD8 != NULL &&
            ftSs_Init_80128A1C(gobj, ip->x5D4_hitboxes, ip->scl))
        {
            ftSs_Init_80128944((HSD_GObj*) ip->xDD4_itemVar.bombhei.xDD8,
                               ip->pos.x, ip->x5D4_hitboxes[0].hit.scale);
        }
    }
}

void itSamusBomb_Logic50_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B894(gobj, ref_gobj);
    ip->xDD4_itemVar.samusbomb.xDD8 = 0;
}
