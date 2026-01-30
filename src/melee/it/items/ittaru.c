#include "ittaru.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

/// #it_3F14_Logic2_Spawned

/// #it_802874F0

/// #it_80287690

bool itTaru_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 1.0F) {
        it_802787B4(gobj, 0x421);
    }
    return false;
}

void itTaru_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itTaru_UnkMotion0_Coll

void it_80287D0C(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itTaru_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itTaru_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itTaru_UnkMotion1_Coll

void it_3F14_Logic2_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDB0_itcmd_var1 = 1;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itTaru_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itTaru_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic2_Dropped(Item_GObj* gobj)
{
    it_80287F20(gobj);
}

void it_3F14_Logic2_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    lb_8000B804(gobj->hsd_obj, ip->xC4_article_data->x10_modelDesc->x0_joint);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void it_80287F20(Item_GObj* gobj)
{
    PAD_STACK(16);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3,
                  ITEM_HIT_PRESERVE | ITEM_DROP_UPDATE | ITEM_UNK_0x1);
}

/// #itTaru_UnkMotion3_Anim

/// #itTaru_UnkMotion3_Phys

/// #itTaru_UnkMotion3_Coll

void it_80288194(Item_GObj* gobj)
{
    it_802881FC(gobj);
}

/// #it_802881B4

/// #it_802881FC

/// #itTaru_UnkMotion5_Anim

void itTaru_UnkMotion5_Phys(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_802874F0(gobj);
    it_80287690(gobj);
}

/// #itTaru_UnkMotion5_Coll

/// #itTaru_UnkMotion4_Anim

/// #itTaru_UnkMotion4_Phys

bool itTaru_UnkMotion4_Coll(Item_GObj* gobj)
{
    return itTaru_UnkMotion5_Coll(gobj);
}

void it_802885C8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;

    it_8026BB44(gobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);

    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->xDCF_flag.b2 = 1;
    ip->xDD4_itemVar.taru.xDD4 = 1;
    ip->xDD4_itemVar.taru.xDD8 = 40;

    it_80275444(gobj);

    pos = ip->pos;
    lb_800119DC(&pos, 0x78, 1.0F, 0.02F, 1.0471976F);

    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool itTaru_UnkMotion6_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itTaru_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itTaru_UnkMotion6_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802886C4

bool itTaru_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.taru.xDD8 -= 1;
    if (ip->xDD4_itemVar.taru.xDD8 > 0) {
        return false;
    }
    return true;
}

void itTaru_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itTaru_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic2_DmgDealt

/// #it_3F14_Logic2_Clanked

/// #it_3F14_Logic2_HitShield

/// #it_3F14_Logic2_Reflected

/// #it_3F14_Logic2_DmgReceived

void it_3F14_Logic2_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
