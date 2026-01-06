#include "itbombhei.h"

#include "itbombhei.static.h"
#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

Item_GObj* it_8027D670(Vec3* pos)
{
    SpawnItem data;
    Item_GObj* igp = NULL;

    data.kind = It_Kind_BombHei;
    data.pos = data.prev_pos = *pos;
    data.facing_dir = it_8026B684(&data.pos);
    data.x3C_damage = 0;
    data.vel.x = data.vel.y = data.vel.z = 0.0f;
    data.x0_parent_gobj = NULL;
    data.x4_parent_gobj2 = data.x0_parent_gobj;
    data.x44_flag.b0 = true;
    data.x40 = 0;
    igp = Item_80268B18(&data);

    if (igp != NULL) {
        it_8027F8E0(igp);
    }

    return igp;
}

void it_8027D730(Item_GObj* igp)
{
    Item* ip = GET_ITEM(igp);

    if (ip->xDC8_word.flags.x13 == 0 && ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(igp);
    }
}

void it_3F14_Logic6_Spawned(Item_GObj* igp)
{
    Item* ip = GET_ITEM(igp);
    f32 temp_f2;
    itBombHeiAttributes* ap = ip->xC4_article_data->x4_specialAttributes;

    ip->xDD4_itemVar.bombhei.xDDC = 0;
    ip->xDD4_itemVar.bombhei.xDD4 = ap->x10;
    ip->xDD4_itemVar.bombhei.xDEC = ap->x8 + (ap->x4 + (ap->x10 + ap->x14));
    ip->xDD4_itemVar.bombhei.xDE0 = 0;
    ip->xDD4_itemVar.bombhei.xDE4 = 0;
    temp_f2 = ap->x4 + (ap->x10 + ap->x14);
    ip->xDD4_itemVar.bombhei.xDF8 = (-1.5999999f / temp_f2) * ip->scl;
    ip->xDD4_itemVar.bombhei.xDFC = (-0.2617994f / temp_f2) * ip->scl;
    ip->xDD4_itemVar.bombhei.xDE8 = 1.0f;
    it_8027DE18(igp);
}

void it_8027D820(Item_GObj* igp)
{
    Item* ip = GET_ITEM(igp);
    HSD_JObj* jobj = GET_JOBJ(igp);
    f32 temp_f30;
    f32 scale;
    itBombHeiAttributes* ap;

    ap = ip->xC4_article_data->x4_specialAttributes;
    temp_f30 = ap->x1C;
    ip->xDD4_itemVar.bombhei.xDD4 -= 1;

    scale = temp_f30 * ip->xDD4_itemVar.bombhei.xDD8;
    HSD_JObjAddScaleX(jobj, scale);

    scale = temp_f30 * ip->xDD4_itemVar.bombhei.xDD8;
    HSD_JObjAddScaleY(jobj, scale);

    scale = temp_f30 * ip->xDD4_itemVar.bombhei.xDD8;
    HSD_JObjAddScaleZ(jobj, scale);

    if (ip->xDD4_itemVar.bombhei.xDD4 <= 0) {
        ip->xDD4_itemVar.bombhei.xDD4 = ap->x18;
        ip->xDD4_itemVar.bombhei.xDD8 = -ip->xDD4_itemVar.bombhei.xDD8;
    }

    ip->xDD4_itemVar.bombhei.xDF0 = ip->xDD4_itemVar.bombhei.xDF0 - 1.0f;
    ip->xDD4_itemVar.bombhei.xDEC -= 1.0f;

    if (ip->xDD4_itemVar.bombhei.xDF0 <= 0.0f) {
        it_80280DC0(igp);
    }
}

void fn_8027DAC8(Item_GObj* igp)
{
    Item* ip = GET_ITEM(igp);
    /// @todo cant figure out the correct inline for this.
    PAD_STACK(8);

    it_8026B390(igp);
    itResetVelocity(ip);
    itBombhei_UpdateStatePreserveBone(igp, 0);
}

bool itBombhei_UnkMotion0_Anim(Item_GObj* igp)
{
    inline1_UnkMotion0_Anim(igp);
    inline2_UnkMotion0_Anim(igp);

    return false;
}

void itBombhei_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8027DE18);
    return false;
}

void it_8027DE18(Item_GObj* igp)
{
    Item* ip;
    itBombHeiAttributes* ap;

    ip = GET_ITEM(igp);
    ap = ip->xC4_article_data->x4_specialAttributes;

    if ((ip->msid == 3) || (ip->msid == 0)) {
        ip->xDC8_word.flags.x19 = 1;
        ip->xDC8_word.flags.x17 = 1;
        it_80274740(igp);
    }

    if ((s32) ip->msid == 3) {
        ip->xDD4_itemVar.bombhei.xDD4 = (s32) ap->x14;
    }

    itBombhei_UpdateStatePreserveBone(igp, 1);
}

bool itBombhei_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itBombhei_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itBombhei_UnkMotion1_Coll(Item_GObj* igp)
{
    Item* ip = GET_ITEM(igp);

    if (ip->xDD4_itemVar.bombhei.xDE4 != 0) {
        ip->xDD4_itemVar.bombhei.xE0C = ip->x40_vel;
        it_8026E414(igp, fn_80280974);
    } else {
        it_8026E15C(igp, fn_8027DAC8);
    }

    return false;
}

void it_3F14_Logic6_PickedUp(Item_GObj* igp)
{
    Item* ip = GET_ITEM(igp);
    itBombHeiAttributes* ap = ip->xC4_article_data->x4_specialAttributes;

    ip->xDC8_word.flags.x19 = 1;
    ip->xDC8_word.flags.x17 = 1;

    if (ip->xDD4_itemVar.bombhei.xDE0 == 0) {
        ip->x5D0_animFrameSpeed = ap->x0;
        itBombhei_UpdateStatePreserveBone(igp, 7);
    } else {
        ip->x5D0_animFrameSpeed = 1.0f;
        itBombhei_UpdateStatePreserveBone2(igp, 8);
    }
}

bool itBombhei_UnkMotion8_Anim(Item_GObj* igp)
{
    Item* ip = GET_ITEM(igp);

    /// @todo this inline is incorrect
    inline_UnkMotion8_Anim(igp);

    if (ip->xDD4_itemVar.bombhei.xDE0 != 0) {
        it_8027D820(igp);
    }

    return false;
}

void itBombhei_UnkMotion8_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic6_Dropped

/// #it_8027E978

/// #itBombhei_UnkMotion3_Anim

void itBombhei_UnkMotion3_Phys(Item_GObj* gobj) {}

/// #itBombhei_UnkMotion3_Coll

/// #it_8027EE04

/// #itBombhei_UnkMotion2_Anim

void itBombhei_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itBombhei_UnkMotion2_Coll

/// #it_8027F42C

/// #itBombhei_UnkMotion4_Anim

void itBombhei_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #itBombhei_UnkMotion4_Coll

/// #it_8027F8E0

bool itBombhei_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.bombhei.xDE0 != 0) {
        it_8027D820(gobj);
    }
    return false;
}

void itBombhei_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, fn_8027FCA8);
    return false;
}

/// #fn_8027FCA8

bool itBombhei_UnkMotion6_Anim(Item_GObj* gobj)
{
    it_8027D820(gobj);
    return false;
}

/// #itBombhei_UnkMotion6_Phys

/// #fn_8028007C

/// #itBombhei_UnkMotion6_Coll

/// #it_3F14_Logic6_Thrown

/// #itBombhei_UnkMotion10_Anim

/// #itBombhei_UnkMotion10_Phys

/// #fn_80280974

/// #itBombhei_UnkMotion10_Coll

/// #it_80280B60

void it_80280DC0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
}

/// #it_3F14_Logic6_DmgDealt

/// #it_3F14_Logic6_DmgReceived

bool itBombhei_UnkMotion11_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itBombhei_UnkMotion11_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion11_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic6_EnteredAir

bool itBombhei_UnkMotion12_Anim(Item_GObj* gobj)
{
    return false;
}

void itBombhei_UnkMotion12_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion12_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_8027DAC8, it_8027DE18);
    return false;
}

bool it_3F14_Logic6_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
    return false;
}

bool it_3F14_Logic6_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_3F14_Logic6_HitShield

/// #it_3F14_Logic6_ShieldBounced

void it_3F14_Logic6_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
