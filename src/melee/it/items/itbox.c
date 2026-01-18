#include "itbox.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/random.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_80286088

/// #it_3F14_Logic1_Spawned

/// #it_3F14_Logic1_Destroyed

/// #it_80286248

bool it_80286340(Item_GObj* gobj, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 sum1 = arg1 + arg2;
    s32 sum2 = arg3 + sum1;
    s32 rand = HSD_Randi(arg4 + sum2);
    if (rand < arg1) {
        return true;
    }
    if (rand < sum1) {
        return true;
    }
    if (rand < sum2) {
        return true;
    }
    return false;
}

/// #it_802863BC

/// #fn_80286480

/// #itBox_UnkMotion0_Anim

void itBox_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, (HSD_GObjEvent) it_8028655C);
    it_80276CB8(gobj);
    return false;
}

void it_8028655C(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itBox_UnkMotion1_Phys

bool itBox_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80286480);
    return false;
}

void it_3F14_Logic1_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itBox_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic1_Thrown(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void itBox_UnkMotion4_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = ((Item*) gobj->user_data)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

/// #itBox_UnkMotion3_Coll

void it_3F14_Logic1_Dropped(Item_GObj* gobj)
{
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

/// #itBox_UnkMotion4_Coll

/// #it_80286AA4

bool itBox_UnkMotion6_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itBox_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion6_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_80286BA0

bool itBox_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.box.xDD8 -= 1;
    if (ip->xDD4_itemVar.box.xDD8 > 0) {
        return false;
    }
    return true;
}

void itBox_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion7_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic1_DmgDealt

/// #it_3F14_Logic1_Clanked

/// #it_3F14_Logic1_HitShield

/// #it_3F14_Logic1_Reflected

/// #it_3F14_Logic1_DmgReceived

void it_3F14_Logic1_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itBox_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itBox_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itBox_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80286480, it_8028655C);
    return false;
}

void it_3F14_Logic1_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802870A4

bool itBox_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itBox_UnkMotion8_Phys

bool itBox_UnkMotion8_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_8028733C
