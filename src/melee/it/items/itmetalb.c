#include "itmetalb.h"

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "pl/plbonuslib.h"

ItemStateTable it_803F62C0[] = {
    { -1, itMetalb_UnkMotion0_Anim, itMetalb_UnkMotion0_Phys,
      itMetalb_UnkMotion0_Coll },
    { -1, itMetalb_UnkMotion3_Anim, itMetalb_UnkMotion1_Phys,
      itMetalb_UnkMotion1_Coll },
    { -1, itMetalb_UnkMotion2_Anim, NULL, NULL },
    { -1, itMetalb_UnkMotion3_Anim, itMetalb_UnkMotion3_Phys,
      itMetalb_UnkMotion3_Coll },
    { -1, itMetalb_UnkMotion4_Anim, itMetalb_UnkMotion4_Phys,
      itMetalb_UnkMotion4_Coll },
};

void itMetalB_Logic32_Spawned(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    it->xDCE_flag.b7 = 0;
    it_80295498(gobj);
}

void it_802953FC(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    it->x40_vel.x = it->x40_vel.y = it->x40_vel.z = 0.0f;

    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itMetalb_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itMetalb_UnkMotion0_Phys(Item_GObj* gobj)
{
    return;
}

bool itMetalb_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80295498);
    it_80276CB8(gobj);

    return false;
}

void it_80295498(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itMetalb_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itMetalb_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                it->xCC_item_attr->x14_fall_speed_max);
}

bool itMetalb_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802953FC);

    return false;
}

void itMetalB_Logic32_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itMetalb_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itMetalB_Logic32_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void itMetalb_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    it_80272860(gobj, it->xCC_item_attr->x10_fall_speed,
                it->xCC_item_attr->x14_fall_speed_max);
}

bool itMetalb_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DA08(gobj)) {
        return true;
    }
    return false;
}

bool itMetalB_Logic32_DmgReceived(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    HSD_GObj* go = it_8027236C(gobj);
    PAD_STACK(8);

    if (go != NULL) {
        if (go->classifier == HSD_GOBJ_CLASS_FIGHTER && it->xDCF_flag.b6) {
            ftLib_800871A8(go, gobj);
            pl_8003E17C(ftLib_80086BE0(go) & 0xFF, ftLib_800874BC(go), gobj);
            return true;
        } else {
            it->xCEC_fighterGObj = NULL;
        }
    }

    return true;
}

void itMetalB_Logic32_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itMetalb_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itMetalb_UnkMotion4_Phys(Item_GObj* gobj)
{
    return;
}

bool itMetalb_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802953FC, it_80295498);

    return false;
}

void itMetalB_Logic32_EvtUnk(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
