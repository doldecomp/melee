#include "itmsbomb.h"

#include "common_structs.h"

#include "baselib/jobj.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "mp/mpcoll.h"

typedef struct {
    float x0;
    float x4;
    itECB x8;
} itMsBomb_Attrs;
STATIC_ASSERT(sizeof(itMsBomb_Attrs) == 24);

ItemStateTable ItemStateTable_MsBomb[] = {
    { -1, NULL, NULL, itMsbomb_UnkMotion0_Coll },
    { -1, NULL, itMsbomb_UnkMotion1_Phys, itMsbomb_UnkMotion1_Coll },
    { -1, NULL, NULL, NULL },
    { 1, NULL, itMsbomb_UnkMotion3_Phys, itMsbomb_UnkMotion3_Coll },
    { 0, NULL, NULL, itMsbomb_UnkMotion4_Coll },
    { 0, NULL, itMsbomb_UnkMotion5_Phys, itMsbomb_UnkMotion5_Coll },
    { 2, itMsbomb_UnkMotion6_Anim, NULL, NULL },
    { -1, NULL, NULL, itMsbomb_UnkMotion7_Coll },
};

void it_8028FE90(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (!ip->xDC8_word.flags.x13) {
        if (ip->msid == 4 || ip->msid == 5) {
            it_802905D8(gobj);
        }
    }
}

void it_3F14_Logic19_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.msbomb.xDD4_b0 = 0;
    it_802756D0(gobj);
    it_8028FF8C(gobj);
}

void it_8028FF1C(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026B390(gobj);
    it_80273454(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itMsbomb_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8028FF8C);
    return false;
}

void it_8028FF8C(Item_GObj* gobj)
{
    itMsBomb_Attrs* attrs;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    HSD_JObjSetRotationX(jobj, attrs->x0);
}

void itMsbomb_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itMsbomb_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_8028FF1C);
    return false;
}

void it_3F14_Logic19_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

void it_3F14_Logic19_Dropped(Item_GObj* gobj)
{
    it_3F14_Logic19_Thrown(gobj);
}

void it_3F14_Logic19_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itMsBomb_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    itECB ecb;
    Item_80268E5C(gobj, 3, 6);
    ip->xBFC = ecb = attrs->x8;
    it_80275D5C(gobj, &ecb);
    ip->xDCE_flag.b7 = 0;
}

void itMsbomb_UnkMotion3_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itMsbomb_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_80290314);
    return false;
}

void it_80290238(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itMsBomb_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(0x18);
    ip->xDCE_flag.b3 = 1;
    if (it_802763B8(gobj) != 1) {
        if (it_802763E0(gobj) == 2) {
            ip->pos.y += ip->scl * (attrs->x8.top - attrs->x8.bottom);
        } else {
            int x = it_80276308(gobj);
            if (x == 8) {
                ip->pos.x += attrs->x4;
            }
            if (x == 4) {
                ip->pos.x -= attrs->x4;
            }
        }
    }
    Item_8026AE84(ip, 243, 127, 64);
}

static inline void it_80290314_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80273454(gobj);
    if (ip->ground_or_air == GA_Ground) {
        it_80274740(gobj);
        it_802765BC(gobj, 0);
        it_80290238(gobj);
    }
    it_8026B3A8(gobj);
    ip->touched = it_802908D8;
    ip->xDC8_word.flags.x1A = 0;
    it_802756E0(gobj);
    it_80275444(gobj);
    it_802754D4(gobj);
    ip->xDD4_itemVar.msbomb.xDD4_b0 = 1;
}

void it_80290314(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.msbomb.xDD4_b0) {
        Item_80268E5C(gobj, 4, 0x11);
    } else {
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    }
    it_802762B0(ip);
    it_80290314_inline(gobj);
}

bool itMsbomb_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    CollData* cd = &ip->x378_itemColl;
    if (it_8026D604(gobj) != 0) {
        mpColl_80043558(cd, ip->xC30);
        it_80276934(gobj, 0);
    }
    it_8026D938(gobj, it_8029047C);
    return 0;
}

void it_8029047C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 5, 0x11);
    it_802762BC(ip);
    it_80290314_inline(gobj);
    ip->xDCE_flag.b3 = 0;
}

void itMsbomb_UnkMotion5_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itMsbomb_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E71C(gobj, it_80290314);
    return false;
}

void it_802905D8(Item_GObj* gobj)
{
    PAD_STACK(8);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    it_80290614(gobj);
}

void it_80290614(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    int pad;
    Vec v;
    HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    it_8027B288(gobj, 0x440061);
    it_8027B564(gobj);
    v = ip->pos;
    lb_800119DC(&v, 120, 1.0f, 0.02f, 1.0471976f);
    it_80272C08(gobj);
    it_80275444(gobj);
    it_802756D0(gobj);
}

bool itMsbomb_UnkMotion6_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

bool it_3F14_Logic19_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3) {
        itColl_BounceOffVictim(gobj);
        it_8026B3A8(gobj);
        it_802725D4(gobj);
    }
    return false;
}

static inline void it_3F14_Logic19_DmgReceived_inline(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    it_80290614(gobj);
}

bool it_3F14_Logic19_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(0x10);
    if (ip->msid == 4 || ip->msid == 5) {
        it_3F14_Logic19_DmgReceived_inline(gobj);
    }
    return false;
}

void it_3F14_Logic19_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itMsbomb_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8028FF1C, it_8028FF8C);
    return false;
}

bool it_3F14_Logic19_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    it_8026B3A8(gobj);
    it_802725D4(gobj);
    return false;
}

bool it_3F14_Logic19_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic19_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3) {
        itColl_BounceOffVictim(gobj);
        it_8026B3A8(gobj);
        it_802725D4(gobj);
    }
    return false;
}

bool it_3F14_Logic19_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3) {
        itColl_BounceOffShield(gobj);
    }
    return false;
}

static inline void it_802908D8_inline(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    it_80290614(gobj);
}

bool it_802908D8(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_802908D8_inline(gobj);
    return false;
}

void it_3F14_Logic19_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
