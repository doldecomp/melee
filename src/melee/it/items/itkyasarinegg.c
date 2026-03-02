#include "itkyasarinegg.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "ef/efsync.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include <baselib/random.h>

ItemStateTable it_803F9328[] = {
    { 0, 0, 0,
      itKyasarinegg_UnkMotion0_Coll },
    { -1, 0, itKyasarinegg_UnkMotion1_Phys,
      itKyasarinegg_UnkMotion1_Coll },
    { -1, 0, 0,
      0 },
    { 1, 0, itKyasarinegg_UnkMotion3_Phys,
      itKyasarinegg_UnkMotion3_Coll },
    { 2, itKyasarinegg_UnkMotion4_Anim, 0,
      0 },
};

void it_802EFA44(Item_GObj* catherine,Vec* pos,float dir) {
    Item_GObj* egg;
    s32 direction;
    Item* eggData;
    PAD_STACK(0x50);
    if (catherine != NULL) {
        egg = it_8027B5B0(0xEC,pos,0,0,1);
        if (egg != NULL) {
            eggData = GET_ITEM((HSD_GObj*)egg);
            eggData->facing_dir = dir;
            if (eggData->facing_dir == -1.0f) {
                direction = -1;
            } else {
                direction = 1;
            }
            mpCollSetFacingDir(&eggData->x378_itemColl,direction);
            eggData->xDD0_flag.b6 = 0;
            eggData->xD40 = 0.0f;
            eggData->xDD4_itemVar.kyasarinEgg.x20 = 0;
            it_80279BBC(eggData);
            if (eggData->xDD0_flag.b7 == 0) {
                it_802756E0(egg);
            }
            it_802EFB0C(egg);
        }
    }
}
void it_802EFB0C(Item_GObj* egg_gobj) {
    Item* egg = GET_ITEM(egg_gobj);
    itKyasarinEggAttributes* ap = egg->xC4_article_data->x4_specialAttributes;
    it_8026B390(egg_gobj);
    egg->x40_vel.x = ap->x4 * egg->facing_dir;
    egg->x40_vel.z = 0.0f;
    egg->x40_vel.y = 0.0f;
    Item_80268E5C(egg_gobj,0,2);
}

bool itKyasarinegg_UnkMotion0_Coll(Item_GObj* gobj)
{
    if (it_8026DAA8(gobj) & 0xF) {
        it_802EFCC0(gobj);
    }
    return false;
}

void itKyasarinEgg_Logic28_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 2, ITEM_ANIM_UPDATE);
}

void itKyasarinEgg_Logic28_Dropped(Item_GObj* gobj)
{
    itKyasarinEgg_Logic28_Thrown(gobj);
}

void itKyasarinEgg_Logic28_Thrown(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
}

void itKyasarinegg_UnkMotion3_Phys(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

int itKyasarinegg_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DA08(gobj) != 0) {
        return it_2725_Logic28_DmgDealt(gobj);
    }
    return 0;
}

void it_802EFCC0(Item_GObj* gobj)
{
    Item* egg = GET_ITEM(gobj);
    itKyasarinEggAttributes* ap = egg->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj,1,2);
    egg->x40_vel.x = -egg->x40_vel.x;
    egg->x40_vel.y = ap->x8;
}

void itKyasarinegg_UnkMotion1_Phys(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

int itKyasarinegg_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026DFB0(gobj);
}

void it_802EFD84(Item_GObj* gobj)
{
    Item* egg = GET_ITEM(gobj);
    it_8026BB44(gobj);
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_8026B3A8(gobj);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    egg->x40_vel.x = 0.0f;
    egg->x40_vel.y = 0.0f;
    egg->xDD4_itemVar.kyasarinEgg.x20 = 1;
    Item_80268E5C(gobj,4,2);
}

bool itKyasarinegg_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_802751D8(gobj);
}

inline bool it_damage_inline(Item_GObj* gobj)
{
    Item* egg = GET_ITEM(gobj);
    itKyasarinEggAttributes* ap;
    if (egg->xDD4_itemVar.kyasarinEgg.x20 != 0) {
        return false;
    }
    if (egg->msid != 3) {
        ap = egg->xC4_article_data->x4_specialAttributes;
        Item_80268E5C(gobj,1,2);
        egg->x40_vel.x = -egg->x40_vel.x;
        egg->x40_vel.y = ap->x8;
        return false;
    } else {
        efSync_Spawn(0x4d0,gobj,&egg->pos);
        Item_8026AE84(egg,0xf4,0x7f,0x40); //why is this being inlined?
        ap = GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
        if(HSD_Randi(ap->x10) == 0) {
            it_802EFD84(gobj);
            return false;
        } else {
            it_8026F3D4(gobj,0,ap->xC,0);
            return true;
        }
    }
    return false;
}

bool it_2725_Logic28_DmgDealt(Item_GObj* gobj)
{
    PAD_STACK(0x8);
    return it_damage_inline(gobj);
}

bool it_2725_Logic28_Clanked(Item_GObj* gobj)
{
    PAD_STACK(0x8);
    return it_damage_inline(gobj);
}

bool it_2725_Logic28_HitShield(Item_GObj* gobj)
{
    PAD_STACK(0x8);
    return it_damage_inline(gobj);
}

bool it_2725_Logic28_Reflected(Item_GObj* gobj)
{
    PAD_STACK(0x8);
    return it_damage_inline(gobj);
}

bool itKyasarinEgg_Logic28_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3) {
        itColl_BounceOffShield(gobj);
    }
    return false;
}

bool it_802F022C(Item_GObj* gobj)
{
    PAD_STACK(0x8);
    return it_damage_inline(gobj);
}

void it_802F0320(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
