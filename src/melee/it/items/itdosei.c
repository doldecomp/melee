#include "itdosei.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/item.h"
#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "lb/lb_00B0.h"

#include <baselib/random.h>

extern const f32 it_804DC874;
extern const f32 it_804DC870;
extern const f32 it_804DC878;
extern s32 it_803F56B8[];

/// #it_3F14_Logic7_Spawned

void fn_80281390(Item_GObj* gobj)
{
    f32 frame_speed;
    HSD_JObj* jobj;
    Item* ip = gobj->user_data;

    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    Item_80268E5C(gobj, 0, 3);
    frame_speed = 1.0f;
    jobj = gobj->hsd_obj;
    ip->x5D0_animFrameSpeed = frame_speed;
    lb_8000BA0C(jobj, frame_speed);
    ip->owner = NULL;
}

/// #itDosei_UnkMotion0_Anim

void itDosei_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion0_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, (HSD_GObjEvent) it_80282074);
    it_80276CB8(gobj);
    return false;
}

/// #fn_80281734

/// #it_802817A0

bool itDosei_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip2;
    Item* ip;
    f32 frame_speed;
    HSD_JObj* jobj;
    PAD_STACK(16);

    ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    ip2 = gobj->user_data;
    frame_speed = it_804DC874 * (M2C_FIELD(ip2, f32*, 0x4CC) * ip2->facing_dir) + it_804DC870;
    jobj = gobj->hsd_obj;
    ip->x5D0_animFrameSpeed = frame_speed;
    lb_8000BA0C(jobj, frame_speed);
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itDosei_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    f32* ap = ip->xC4_article_data->x4_specialAttributes;
    f32 vel = ap[2] * ip->x5D0_animFrameSpeed;
    if (vel < 0.0f) {
        vel = -vel;
    }
    ip->x40_vel.x = ip->facing_dir * vel;
}

/// #itDosei_UnkMotion1_Coll

void it_80281C6C(Item_GObj* gobj)
{
    s32 zero = 0;
    f32 frame_speed;
    Item* ip = gobj->user_data;

    ip->xDD4_itemVar.dosei.xDD8 = zero;
    ip->pos = ip->xDD4_itemVar.dosei.xDE4;
    M2C_FIELD(ip, f32*, 0xDDC) = it_804DC878;
    ip->x40_vel.x = it_804DC878;
    it_802762B0(ip);
    Item_80268E5C(gobj, 2, 3);
    frame_speed = it_804DC870;
    ip->x5D0_animFrameSpeed = frame_speed;
    lb_8000BA0C(gobj->hsd_obj, frame_speed);
    M2C_FIELD(ip, s32*, 0x518) = zero;
}

/// #itDosei_UnkMotion2_Anim

void itDosei_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion2_Coll

void it_80282074(Item_GObj* gobj)
{
    f32 frame_speed;
    Item* ip = gobj->user_data;

    Item_80268E5C(gobj, 3, 3);
    frame_speed = it_804DC870;
    ip->x5D0_animFrameSpeed = frame_speed;
    lb_8000BA0C(gobj->hsd_obj, frame_speed);
    M2C_FIELD(ip, s32*, 0x518) = 0;
}

bool itDosei_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itDosei_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802817A0);
    return false;
}

/// #it_3F14_Logic7_PickedUp

/// #itDosei_UnkMotion4_Anim

void itDosei_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic7_Dropped

/// #it_3F14_Logic7_Thrown

bool itDosei_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itDosei_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

/// #it_3F14_Logic7_EnteredAir

bool itDosei_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

void itDosei_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDF8 = ip->x378_itemColl.floor.normal;
    it_8026E8C4(gobj, (HSD_GObjEvent) fn_80281734, (HSD_GObjEvent) it_80282074);
    return false;
}

void it_80282BFC(Item_GObj* gobj)
{
    f32 frame_speed;
    Item* ip = gobj->user_data;

    Item_80268E5C(gobj, 8, 3);
    frame_speed = it_804DC870;
    ip->x5D0_animFrameSpeed = frame_speed;
    lb_8000BA0C(gobj->hsd_obj, frame_speed);
    M2C_FIELD(ip, s32*, 0x518) = 0;
}

bool itDosei_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    return false;
}

void itDosei_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80282CD4);
    return false;
}

void fn_80282CD4(Item_GObj* gobj)
{
    f32 frame_speed;
    Item* ip = gobj->user_data;

    ip->x40_vel.z = it_804DC878;
    ip->x40_vel.y = it_804DC878;
    ip->x40_vel.x = it_804DC878;
    it_802762B0(ip);
    Item_80268E5C(gobj, 7, 3);
    frame_speed = it_804DC870;
    ip->x5D0_animFrameSpeed = frame_speed;
    lb_8000BA0C(gobj->hsd_obj, frame_speed);
    M2C_FIELD(ip, s32*, 0x518) = 0;
}

bool itDosei_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    s32 timer;
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    timer = ip->xDD4_itemVar.dosei.xDD4;
    if (timer > 0) {
        ip->xDD4_itemVar.dosei.xDD4 = timer - 1;
    } else {
        it_80282DE4(gobj);
    }
    return false;
}

void itDosei_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80282BFC);
    it_80276CB8(gobj);
    return false;
}

/// #it_80282DE4

/// #itDosei_UnkMotion9_Anim

void itDosei_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itDosei_UnkMotion9_Coll

bool itDosei_UnkMotion10_Anim(Item_GObj* gobj)
{
    f32 speed;
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    speed = 1.0f;
    ip->x5D0_animFrameSpeed = speed;
    lb_8000BA0C(gobj->hsd_obj, speed);
    return false;
}

void itDosei_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itDosei_UnkMotion10_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, fn_80282CD4, it_80282BFC);
    return false;
}

/// #it_3F14_Logic7_DmgReceived

bool itDosei_UnkMotion11_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.dosei.xDE4 = ip->pos;
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 11, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itDosei_UnkMotion11_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itDosei_UnkMotion11_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, fn_80281390);
    return false;
}

bool it_3F14_Logic7_DmgDealt(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    s32 rand = HSD_Randi(3);
    s32 sfx_id = it_803F56B8[rand];

    Item_8026AF0C(ip, sfx_id, 0x7F, 0x40);
    if (ip->msid == 5) {
        itColl_BounceOffVictim(gobj);
        it_802725D4(gobj);
    }
    return false;
}

bool it_3F14_Logic7_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic7_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic7_HitShield(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic7_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_3F14_Logic7_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
