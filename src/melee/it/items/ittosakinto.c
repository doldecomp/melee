#include "ittosakinto.h"

#include "platform.h"

#include "baselib/random.h"
#include "gr/stage.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lbaudio_ax.h"

#define GET_ATTRS(it)                                                         \
    ((itTosakinto_Attrs*) (it)->xC4_article_data->x4_specialAttributes)

ItemStateTable it_803F7A48[] = {
    { 0, itTosakinto_UnkMotion2_Anim, itTosakinto_UnkMotion2_Phys,
      itTosakinto_UnkMotion2_Coll },
    { 1, itTosakinto_UnkMotion2_Anim, itTosakinto_UnkMotion2_Phys,
      itTosakinto_UnkMotion2_Coll },
    { 2, itTosakinto_UnkMotion2_Anim, itTosakinto_UnkMotion2_Phys,
      itTosakinto_UnkMotion2_Coll },
    { -1, NULL, itTosakinto_UnkMotion3_Phys, itTosakinto_UnkMotion3_Coll },
    { -1, itTosakinto_UnkMotion4_Anim, itTosakinto_UnkMotion4_Phys,
      itTosakinto_UnkMotion4_Coll },
};

void it_802C8F4C(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    itTosakinto_Attrs* attrs;

    attrs = GET_ATTRS(it);
    it->xDD4_itemVar.tosakinto.x60_msid = 0;
    it->xD44_lifeTimer = attrs->x4_life_timer;
    it->xDD4_itemVar.tosakinto.x68_sfx_id = SFX_NONE;
    it_80279CDC(gobj, attrs->x0_scale);
    Item_8026AE84(it, 0x272E, 0x7FU, 0x40U);
    it_802C93BC(gobj);
}

void it_802C8FC4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_802C8FE4(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    Vec3 scale_vec;
    float scale;
    HSD_JObj* jobj;
    HSD_JObj* child;

    jobj = GET_JOBJ(gobj);
    child = HSD_JObjGetChild(jobj);
    scale = it->xCC_item_attr->x60_scale;
    scale_vec.z = scale;
    scale_vec.y = scale;
    scale_vec.x = scale;
    HSD_JObjSetScale(child, &scale_vec);
    it_80273454(gobj);
    it_802C90E8(gobj);
    it->xDD4_itemVar.tosakinto.x68_sfx_id = it->xD6C;
}

void it_802C90E8(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    itTosakinto_Attrs* attrs = GET_ATTRS(it);
    enum_t msid;
    PAD_STACK(0x8);

    it_8027ADEC(0x46E, gobj, GET_JOBJ(gobj), 2.0F);
    it_802762BC(it);
    msid = it->xDD4_itemVar.tosakinto.x60_msid;
    if (msid >= 3) {
        msid = 0;
    }
    it->xDD4_itemVar.tosakinto.x60_msid = msid;
    Item_80268E5C(gobj, it->xDD4_itemVar.tosakinto.x60_msid, ITEM_ANIM_UPDATE);
    it->xDD4_itemVar.tosakinto.x64_vel_x = attrs->x8_vel_x;
    if (HSD_Randi(2) != 0) {
        it->xDD4_itemVar.tosakinto.x64_vel_x =
            -it->xDD4_itemVar.tosakinto.x64_vel_x;
    }
}

bool itTosakinto_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    it_8027A160(HSD_JObjGetChild(jobj), it);
    if (it->xD44_lifeTimer <= 0.0F) {
        return true;
    }
    it->xD44_lifeTimer -= 1.0F;
    return false;
}

void itTosakinto_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    it_8027A344(gobj);
    it->x40_vel.x += it->xDD4_itemVar.tosakinto.x64_vel_x;
}

bool itTosakinto_UnkMotion2_Coll(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    bool temp;
    PAD_STACK(0x8);

    temp = it_8026DA08(gobj);
    if (!it_80272C6C(gobj)) {
        if (temp) {
            it->xDD4_itemVar.tosakinto.x60_msid += 1;
            it_802C90E8(gobj);
        } else {
            it->xDD4_itemVar.tosakinto.x60_msid += 1;
            it_802C9468(gobj);
        }
    } else if (temp) {
        it->xDD4_itemVar.tosakinto.x60_msid += 1;
        it_802C90E8(gobj);
    }
    return false;
}

void it_802C93BC(Item_GObj* gobj)
{
    it_802762BC(GET_ITEM(gobj));
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itTosakinto_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itTosakinto_UnkMotion4_Phys(Item_GObj* gobj)
{
    it_8027A09C(gobj);
}

bool itTosakinto_UnkMotion4_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, it_802C8FE4);
}

void it_802C9468(Item_GObj* gobj)
{
    it_802762BC(GET_ITEM(gobj));
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

void itTosakinto_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itTosakinto_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802C90E8);
    return false;
}

void it_2725_Logic0_Destroyed(Item_GObj* gobj)
{
    Item* it_r31 = GET_ITEM(gobj);
    if (it_r31->pos.y - 50.0F < Stage_GetBlastZoneBottomOffset()) {
        lbAudioAx_800263E8(3.0F, gobj, 9, 0x272E, 0x7F, 0x7F, 0x7F, 0, 0x3C, 0,
                           it_r31->xDD4_itemVar.tosakinto.x68_sfx_id);
    }
}
