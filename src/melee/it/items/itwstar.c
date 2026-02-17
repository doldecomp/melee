#include "itwstar.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lb_00F9.h"

#include <baselib/jobj.h>
#include <baselib/random.h>

HSD_AnimJoint* it_80294364(Item_GObj* gobj)
{
    s32 candidates[8];
    s32 i;
    Item* ip;
    s32 last;
    itWstarAttributes* attr;
    s32 count;
    s32 total;
    s32* p;
    s32 picked;

    i = 0;
    p = candidates;
    ip = GET_ITEM(gobj);
    last = it_804D6D00;
    attr = ip->xC4_article_data->x4_specialAttributes;
    count = 0;
    total = attr->x24_count;

    for (; i < total; i++) {
        if (i != last) {
            *p++ = i;
            count++;
        }
    }

    picked = candidates[HSD_Randi(count)];
    it_804D6D00 = (s8) picked;
    ip->xDD4_itemVar.wstar.xDDC = picked;
    Item_8026AE84(ip, attr->x28_entries[ip->xDD4_itemVar.wstar.xDDC].x4_sfx,
                  0x7f, 0x40);
    return attr->x28_entries[picked].x0_anim_joint;
}

void it_80294430(Item_GObj* gobj, f32 arg1, f32 arg2)
{
    Item* ip = GET_ITEM(gobj);
    itWstarAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = it_80272C90(gobj);
    f32 speed = attr->x8 * (arg1 / attr->x4);
    speed *= ip->xCC_item_attr->x60_scale;
    ip->xDD4_itemVar.wstar.xDD4 = speed;
    it_80272F7C(jobj, speed);
    ip->xDD4_itemVar.wstar.xDD8 = arg2;
}

void it_802944AC(Item_GObj* gobj, ftCollisionBox* box)
{
    Item* ip = GET_ITEM(gobj);
    itWstarAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    box->top = attr->xC * ip->xDD4_itemVar.wstar.xDD4;
    box->bottom = attr->x10 * ip->xDD4_itemVar.wstar.xDD4;
    box->left.x = attr->x14 * ip->xDD4_itemVar.wstar.xDD4;
    box->left.y = attr->x18 * ip->xDD4_itemVar.wstar.xDD4;
    box->right.x = attr->x1C * ip->xDD4_itemVar.wstar.xDD4;
    box->right.y = attr->x20 * ip->xDD4_itemVar.wstar.xDD4;
}

void itWStar_Logic29_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCE_flag.b7 = 0;
    ip->xDD4_itemVar.wstar.xDD8 = 0.0F;
    ip->xDD4_itemVar.wstar.xDD4 = 0.0F;
    it_80294364(gobj);
}

void it_8029455C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itWstar_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itWstar_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itWstarAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    it_80274658(gobj, attr->x0);
    it_80274A64(gobj);
}

bool itWstar_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80294624);
    return false;
}

void it_80294624(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itWstar_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itWstar_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itWstar_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_8029455C);
    return false;
}

void it_802946B0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj;
    Item_80268E5C(gobj, 3, 2);
    jobj = it_80272C90(gobj);
    it_80272F7C(jobj, ip->xDD4_itemVar.wstar.xDD4);
    it_802755C0(gobj, ip->xDD4_itemVar.wstar.xDD8);
    it_8027B288(gobj, 0x0044005F);
    it_8027B330(gobj, 0x5E);
}

void it_3F14_Logic29_PickedUp(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    PAD_STACK(16);
    Item_80268E5C(gobj, 2, 2);
    jobj = it_80272CC0(gobj, 3);
    efAsync_Spawn((HSD_GObj*) gobj, &GET_ITEM(gobj)->xBC0, 0U, 0x43d, jobj);
}

bool itWstar_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itWStar_Logic29_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 6);
    efLib_DestroyAll(gobj);
}

void it_802947CC(Item_GObj* gobj, Vec3* pos)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    union Struct2070 saved_xD90;
    Vec2 saved_xD94;
    S32Vec2 saved_xD9C;
    u32 saved_xDA4;
    u16 saved_xDA8;
    Vec3 item_pos;

    itResetVelocity(ip);
    ip->xDAC_itcmd_var0 = 0;
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    saved_xD90 = ip->xD90;
    saved_xD94 = ip->xD94;
    saved_xD9C = ip->xD9C;
    saved_xDA4 = ip->xDA4_word;
    saved_xDA8 = ip->xDA8_short;
    it_8027429C(gobj, &ip->x40_vel);
    ip->xD90 = saved_xD90;
    ip->xD94 = saved_xD94;
    ip->xD9C = saved_xD9C;
    ip->xDA4_word = saved_xDA4;
    ip->xDA8_short = saved_xDA8;
    it_8026B3A8(gobj);
    ip->pos = *pos;
    HSD_JObjSetTranslate(jobj, &ip->pos);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    efLib_DestroyAll(gobj);
    item_pos = ip->pos;
    lb_800119DC(&item_pos, 0x78, 1.0f, 0.02f, 1.0471976f);
    it_80272C08(gobj);
    it_802755C0(gobj, ip->xDD4_itemVar.wstar.xDD8);
}

bool itWstar_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDAC_itcmd_var0 != 0) {
        it_802755C0(gobj, ip->xDD4_itemVar.wstar.xDD8);
        ip->xDAC_itcmd_var0 = 0;
    }
    return it_802751D8(gobj);
}

void itWstar_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itWstar_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

void itWStar_Logic29_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itWstar_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itWstar_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itWstar_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8029455C, it_80294624);
    return false;
}

void itWStar_Logic30_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
