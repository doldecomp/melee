#include "itpikachuthunder.h"

#include "ft/chara/ftPikachu/ftPk_SpecialLw.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/gobj.h>
#include <placeholder.h>

int it_802B1DEC(Item_GObj* arg0)
{
    return GET_ITEM(arg0)->xDD4_itemVar.capsule.x4;
}

/// #it_802B1DF8

s32 it_802B1FC8(Item_GObj* gobj)
{
    return it_802B22B8(gobj);
}

void it_802B1FE8(Item_GObj* gobj, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    f32 scale = ip->xDD4_itemVar.pikachuthunder.x18;
    f32 offset = -attrs->x8;

    offset *= scale;
    *pos = ip->pos;
    pos->y += offset;
}

void it_2725_Logic39_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x0 == 0 &&
        ip->xDD4_itemVar.pikachuthunder.x38 != NULL &&
        !ftPk_SpecialLw_CheckProperty(ip->xDD4_itemVar.pikachuthunder.x38))
    {
        ftPk_SpecialLw_SetState_Unk0(ip->xDD4_itemVar.pikachuthunder.x38);
    }
}

void it_802B2080(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attrs->x0);
    it_8026BB44(gobj);
}

bool itPikachuthunder_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x8 <= 0) {
        it_802B211C(gobj);
    } else {
        ip->xDD4_itemVar.pikachuthunder.x8--;
    }
    return false;
}

void it_802B211C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPikachuthunderAttributes* attrs =
        ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_80275158(gobj, attrs->x0);
    ip->x40_vel = ip->xDD4_itemVar.pikachuthunder.x1C;
    ip->xDCC_flag.b3 = 1;
    it_8026BB20(gobj);
}

bool itPikachuthunder_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xD44_lifeTimer--;
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

/// #itPikachuthunder_UnkMotion1_Coll

s32 it_802B22B8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 2, ITEM_UNK_0x1 | ITEM_HIT_PRESERVE);
    ip->xD44_lifeTimer = ip->xDD4_itemVar.pikachuthunder.x14;
    ip->xDD4_itemVar.pikachuthunder.x4 = 1;
    {
        Item* ip2 = GET_ITEM(gobj);
        Item_GObj* child = ip2->xDD4_itemVar.pikachuthunder.x34;
        if (child != NULL) {
            Item* child_ip = GET_ITEM(child);
            if (child_ip != NULL) {
                child_ip->xDD4_itemVar.pikachuthunder.x28 = ip2->pos;
                child_ip->xDD4_itemVar.pikachuthunder.x4 = 1;
            }
        }
    }
    PAD_STACK(8);
}

/// #itPikachuthunder_UnkMotion2_Anim

bool itPikachuThunder_Logic39_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_HitShield(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_Clanked(Item_GObj* arg0)
{
    return false;
}

bool itPikachuThunder_Logic39_Absorbed(Item_GObj* arg0)
{
    return false;
}

void itPikachuThunder_Logic39_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachuthunder.x38 == ref_gobj) {
        ip->xDD4_itemVar.pikachuthunder.x38 = NULL;
    }
    it_8026B894(gobj, ref_gobj);
}
