#include "itbombhei.h"

#include "itbombhei.static.h"

#include "math.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "lb/lb_00F9.h"

#define GET_ATTRS(ip)                                                         \
    ((itBombHeiAttributes*) ip->xC4_article_data->x4_specialAttributes)

ItemStateTable it_803F54D8[] = {
    { -1, itBombhei_UnkMotion0_Anim, itBombhei_UnkMotion0_Phys,
      itBombhei_UnkMotion0_Coll },
    { -1, itBombhei_UnkMotion1_Anim, itBombhei_UnkMotion1_Phys,
      itBombhei_UnkMotion1_Coll },
    { 0, itBombhei_UnkMotion2_Anim, itBombhei_UnkMotion2_Phys,
      itBombhei_UnkMotion2_Coll },
    { 0, itBombhei_UnkMotion3_Anim, itBombhei_UnkMotion3_Phys,
      itBombhei_UnkMotion3_Coll },
    { 6, itBombhei_UnkMotion4_Anim, itBombhei_UnkMotion4_Phys,
      itBombhei_UnkMotion4_Coll },
    { 4, itBombhei_UnkMotion5_Anim, itBombhei_UnkMotion5_Phys,
      itBombhei_UnkMotion5_Coll },
    { 4, itBombhei_UnkMotion6_Anim, itBombhei_UnkMotion6_Phys,
      itBombhei_UnkMotion6_Coll },
    { 1, itBombhei_UnkMotion8_Anim, itBombhei_UnkMotion8_Phys, NULL },
    { 4, itBombhei_UnkMotion8_Anim, itBombhei_UnkMotion8_Phys, NULL },
    { 2, itBombhei_UnkMotion10_Anim, itBombhei_UnkMotion10_Phys,
      itBombhei_UnkMotion10_Coll },
    { 5, itBombhei_UnkMotion10_Anim, itBombhei_UnkMotion10_Phys,
      itBombhei_UnkMotion10_Coll },
    { 3, itBombhei_UnkMotion11_Anim, itBombhei_UnkMotion11_Phys,
      itBombhei_UnkMotion11_Coll },
    { -1, itBombhei_UnkMotion12_Anim, itBombhei_UnkMotion12_Phys,
      itBombhei_UnkMotion12_Coll },
};

static inline void itBombhei_UpdateStatePreserveBoneMotion10(Item_GObj* igp,
                                                             int anim_id,
                                                             int flags)
{
    Item* ip = GET_ITEM(igp);
    HSD_JObj* jobj = ip->xBBC_dynamicBoneTable->bones[0xB];
    f32 x;
    f32 y;

    y = HSD_JObjGetTranslationY(jobj);
    x = HSD_JObjGetRotationX(jobj);
    Item_80268E5C(igp, anim_id, flags);
    fake_HSD_JObjSetTranslateY(jobj, y);
    fake_HSD_JObjSetRotationX(jobj, x);
}

static inline void fn_80280974_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBombHeiAttributes* attrs = GET_ATTRS(ip);
    it_8026B3A8(gobj);
    ip->x40_vel.x = attrs->xC * ip->facing_dir;
    ip->xD5C = 0;
    it_80275444(gobj);
}

static inline void itBombhei_UnkMotion1_Setup(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBombHeiAttributes* ap = GET_ATTRS(ip);
    if ((ip->msid == 3) || (ip->msid == 0)) {
        ip->xDC8_word.flags.x19 = 1;
        ip->xDC8_word.flags.x17 = 1;
        it_80274740(gobj);
    }
    if ((s32) ip->msid == 3) {
        ip->xDD4_itemVar.bombhei.xDD4 = (s32) ap->x14;
    }
}

Item_GObj* it_8027D670(Vec3* pos)
{
    SpawnItem data;
    Item_GObj* igp = NULL;

    data.kind = It_Kind_BombHei;
    data.pos = data.prev_pos = *pos;
    data.facing_dir = it_8026B684(&data.prev_pos);
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

void itBombhei_Logic6_Spawned(Item_GObj* igp)
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
    itBombhei_UpdateStatePreserveBone(igp, 0, ITEM_ANIM_UPDATE);
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

    itBombhei_UpdateStatePreserveBone(igp, 1, ITEM_ANIM_UPDATE);
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

void itBombhei_Logic6_PickedUp(Item_GObj* igp)
{
    Item* ip = GET_ITEM(igp);
    itBombHeiAttributes* ap = ip->xC4_article_data->x4_specialAttributes;

    ip->xDC8_word.flags.x19 = 1;
    ip->xDC8_word.flags.x17 = 1;

    if (ip->xDD4_itemVar.bombhei.xDE0 == 0) {
        ip->x5D0_animFrameSpeed = ap->x0;
        itBombhei_UpdateStatePreserveBone(igp, 7, ITEM_ANIM_UPDATE);
    } else {
        ip->x5D0_animFrameSpeed = 1.0f;
        itBombhei_UpdateStatePreserveBone(igp, 8, ITEM_UNK_0x1);
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

void it_3F14_Logic6_Dropped(Item_GObj* arg0)
{
    Item* ip;
    itBombHeiAttributes* attrs;
    ip = GET_ITEM(arg0);
    attrs = GET_ATTRS(ip);
    ip->xDC8_word.flags.x19 = 1;
    ip->xDC8_word.flags.x17 = 1;
    if (ip->xDD4_itemVar.bombhei.xDE0 == 0) {
        ip->x5D0_animFrameSpeed = attrs->x0;
        itBombhei_UpdateStatePreserveBone(arg0, 9, 6);
    } else {
        ip->x5D0_animFrameSpeed = 1.0f;
        itBombhei_UpdateStatePreserveBone(arg0, 0xA, 5);
    }
}

void it_8027E978(Item_GObj* arg0)
{
    Item* ip;
    itBombHeiAttributes* attrs;

    ip = GET_ITEM(arg0);
    attrs = GET_ATTRS(ip);
    it_802762B0(ip);
    ip->xDD4_itemVar.bombhei.xDD4 = (s32) attrs->x4;
    ip->xDD4_itemVar.bombhei.xE04 = ((M_PI / 2 * (f64) ip->facing_dir) /
                                     (f64) ip->xDD4_itemVar.bombhei.xDD4);
    ip->xDD4_itemVar.bombhei.xDE4 = 1;

    itBombhei_UpdateStatePreserveBone(arg0, 3, ITEM_ANIM_UPDATE);
}

bool itBombhei_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;

    HSD_JObjAddRotationY(jobj, ip->xDD4_itemVar.bombhei.xE04);
    ip->xDD4_itemVar.bombhei.xDD4 -= 1;
    ip->xDD4_itemVar.bombhei.xDEC -= 1.0f;
    if (ip->xDD4_itemVar.bombhei.xDD4 <= 0) {
        itBombHeiAttributes* attr = GET_ATTRS(ip);
        ip->xDC8_word.flags.x19 = 1;
        ip->xDD4_itemVar.bombhei.xDD4 = attr->x14;
        it_8027EE04(gobj);
        Item_8026AE84(ip, 0xF0, 0x7FU, 0x40U);
    }
    inline2_UnkMotion0_Anim(gobj);

    return false;
}

void itBombhei_UnkMotion3_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion3_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, it_8027DE18);
    it_80276CB8(gobj);
    return false;
}

void it_8027EE04(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBombHeiAttributes* attrs = GET_ATTRS(ip);
    it_8026B3A8(gobj);
    ip->x40_vel.x = attrs->xC * ip->facing_dir;
    ip->xD5C = 0;
    it_80275444(gobj);
    itBombhei_UpdateStatePreserveBone(gobj, 2, 0x1A);
}

bool itBombhei_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip;

    ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.bombhei.xDD4 -= 1;
    ip->xDD4_itemVar.bombhei.xDEC -= 1.0f;
    if ((s32) ip->xDD4_itemVar.bombhei.xDD4 <= 0) {
        it_8027F8E0(gobj);
    }
    if (it_80272C6C(gobj) == 0) {
        fn_80280974_inline(gobj);
        itBombhei_UpdateStatePreserveBoneFake(gobj, 2, 0x1A);
    }
    inline2_UnkMotion0_Anim(gobj);
    return false;
}

void itBombhei_UnkMotion2_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion2_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);

    if (it_8026D8A4(gobj, (void (*)(HSD_GObj*)) it_8027F42C) != 0) {
        if (it_80276308(gobj) != 0) {
            it_8027F42C(gobj);
        }
        it_80276CB8(gobj);
    } else {
        itBombhei_UnkMotion1_Setup(gobj);
        itBombhei_UpdateStatePreserveBoneFake(gobj, 1, ITEM_ANIM_UPDATE);
    }
    return false;
}

void it_8027F42C(Item_GObj* arg0)
{
    HSD_JObj* temp_r30;
    Item* temp_r31;
    PAD_STACK(8);

    temp_r31 = arg0->user_data;
    it_802762B0(temp_r31);
    itBombhei_UpdateStatePreserveBone(arg0, 4, 0x12);
    temp_r31->x40_vel.x = 0.0f;
    temp_r31->xDD4_itemVar.bombhei.xDF4 = -temp_r31->facing_dir;
}

bool itBombhei_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip;

    ip = GET_ITEM(gobj);
    if (it_80272C6C(gobj) == 0) {
        ip->facing_dir = -ip->facing_dir;
        fn_80280974_inline(gobj);
        itBombhei_UpdateStatePreserveBoneFake(gobj, 2, 0x1A);
    }
    ip->xDD4_itemVar.bombhei.xDD4 -= 1;
    ip->xDD4_itemVar.bombhei.xDEC -= 1.0f;
    if (ip->xDD4_itemVar.bombhei.xDD4 <= 0) {
        ip->facing_dir = ip->xDD4_itemVar.bombhei.xDF4;
        it_8027F8E0(gobj);
    }
    inline2_UnkMotion0_Anim(gobj);
    return false;
}

void itBombhei_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion4_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D62C(gobj, it_8027DE18);
    it_80276CB8(gobj);
    return false;
}

void it_8027F8E0(Item_GObj* arg0)
{
    Item* ip;
    itBombHeiAttributes* attr;

    ip = GET_ITEM(arg0);
    attr = GET_ATTRS(ip);
    ip->x40_vel.x = 0.0f;
    it_8026B390(arg0);
    if (ip->xDD4_itemVar.bombhei.xDE0 == 0) {
        ip->xDD4_itemVar.bombhei.xDD4 = attr->x18;
        ip->xDD4_itemVar.bombhei.xDD8 = 1;
        ip->xD44_lifeTimer = (f32) it_804D6D28->x30_lifetime;
        ip->xDD4_itemVar.bombhei.xDF0 = attr->x8;
        ip->xDD4_itemVar.bombhei.xDE0 = 1;
        itBombhei_UpdateStatePreserveBone(arg0, 5, ITEM_ANIM_UPDATE);
    } else {
        itBombhei_UpdateStatePreserveBone(arg0, 5, ITEM_UNK_0x1);
    }
}

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

void fn_8027FCA8(Item_GObj* arg0)
{
    Item* ip;
    itBombHeiAttributes* attrs;

    ip = GET_ITEM(arg0);
    attrs = GET_ATTRS(ip);
    ip->x40_vel.x = 0.0f;
    it_8026B390(arg0);
    if (ip->xDD4_itemVar.bombhei.xDE0 == 0) {
        ip->xDD4_itemVar.bombhei.xDD4 = attrs->x18;
        ip->xDD4_itemVar.bombhei.xDD8 = 1;
        ip->xD44_lifeTimer = (f32) it_804D6D28->x30_lifetime;
        ip->xDD4_itemVar.bombhei.xDF0 = attrs->x8;
        ip->xDD4_itemVar.bombhei.xDE0 = 1;
        itBombhei_UpdateStatePreserveBone(arg0, 6, ITEM_ANIM_UPDATE);
    } else {
        itBombhei_UpdateStatePreserveBone(arg0, 6, ITEM_UNK_0x1);
    }
}

bool itBombhei_UnkMotion6_Anim(Item_GObj* gobj)
{
    it_8027D820(gobj);
    return false;
}

void itBombhei_UnkMotion6_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = ((Item*) gobj->user_data)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

static inline void fn_8028007C_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBombHeiAttributes* attr = GET_ATTRS(ip);
    ip->x40_vel.x = 0.0f;
    it_8026B390(gobj);
    if (ip->xDD4_itemVar.bombhei.xDE0 == 0) {
        ip->xDD4_itemVar.bombhei.xDD4 = attr->x18;
        ip->xDD4_itemVar.bombhei.xDD8 = 1;
        ip->xD44_lifeTimer = it_804D6D28->x30_lifetime;
        ip->xDD4_itemVar.bombhei.xDF0 = attr->x8;
        ip->xDD4_itemVar.bombhei.xDE0 = 1;
        itBombhei_UpdateStatePreserveBoneFake(gobj, 5, ITEM_ANIM_UPDATE);
    } else {
        itBombhei_UpdateStatePreserveBoneFake(gobj, 5, ITEM_UNK_0x1);
    }
}

void fn_8028007C(Item_GObj* arg0)
{
    Item* ip = GET_ITEM(arg0);
    itBombHeiAttributes* attr = GET_ATTRS(ip);
    if (ABS(ip->xDD4_itemVar.bombhei.xE0C.x) > attr->x20.x ||
        ABS(ip->xDD4_itemVar.bombhei.xE0C.y) > attr->x20.y)
    {
        it_80280DC0(arg0);
        return;
    }
    fn_8028007C_inline(arg0);
}

bool itBombhei_UnkMotion6_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.bombhei.xE0C = ip->x40_vel;
    it_8026E414(gobj, fn_8028007C);
    return false;
}

void it_3F14_Logic6_Thrown(Item_GObj* arg0)
{
    Item* ip;
    itBombHeiAttributes* temp_r3;
    HSD_JObj* temp_r29;
    PAD_STACK(8);

    ip = GET_ITEM(arg0);
    temp_r29 = arg0->hsd_obj;
    temp_r3 = GET_ATTRS(ip);
    if (ip->xDD4_itemVar.bombhei.xDE0 == 0) {
        ip->x5D0_animFrameSpeed = temp_r3->x0;
        itBombhei_UpdateStatePreserveBone(arg0, 9, 6);
    } else {
        ip->x5D0_animFrameSpeed = 1.0f;
        itBombhei_UpdateStatePreserveBone(arg0, 0xA, 0x104);
    }

    it_80275474(arg0);
    if (ip->xDD4_itemVar.bombhei.xDE8 != 1.0f) {
        it_80274484(arg0, temp_r29, ip->xDD4_itemVar.bombhei.xDE8);
    }
}

bool itBombhei_UnkMotion10_Anim(Item_GObj* gobj)
{
    HSD_JObj* temp_r31;
    Item* temp_r30;
    Item* temp_r29;
    itBombHeiAttributes* attr;

    temp_r29 = GET_ITEM(gobj);
    if (it_80272C6C(gobj) == 0) {
        temp_r30 = GET_ITEM(gobj);
        temp_r31 = gobj->hsd_obj;
        attr = GET_ATTRS(temp_r30);
        if (temp_r30->xDD4_itemVar.bombhei.xDE0 == 0) {
            temp_r30->x5D0_animFrameSpeed = attr->x0;
            itBombhei_UpdateStatePreserveBoneMotion10(gobj, 9, 0x6);
        } else {
            temp_r30->x5D0_animFrameSpeed = 1.0f;
            itBombhei_UpdateStatePreserveBoneMotion10(gobj, 0xA, 0x104);
        }
        it_80275474(gobj);
        if (temp_r30->xDD4_itemVar.bombhei.xDE8 != 1.0f) {
            it_80274484(gobj, temp_r31, temp_r30->xDD4_itemVar.bombhei.xDE8);
        }
    }
    if (temp_r29->xDD4_itemVar.bombhei.xDE0 != 0) {
        it_8027D820(gobj);
    }
    return false;
}

void itBombhei_UnkMotion10_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = ((Item*) gobj->user_data)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

void fn_80280974(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itBombHeiAttributes* attr = GET_ATTRS(ip);
    if (ABS(ip->xDD4_itemVar.bombhei.xE0C.x) > attr->x20.x ||
        ABS(ip->xDD4_itemVar.bombhei.xE0C.y) > attr->x20.y)
    {
        it_80280DC0(gobj);
        return;
    }
    fn_80280974_inline(gobj);
    itBombhei_UpdateStatePreserveBoneMotion10(gobj, 2, 0x1A);
}

bool itBombhei_UnkMotion10_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.bombhei.xE0C = ip->x40_vel;
    it_8026E414(gobj, fn_80280974);
    return false;
}
const Vec3 it_803B8600 = { 0 };
void it_80280B60(Item_GObj* gobj)
{
    Vec sp48;
    Vec3 sp3C;
    HSD_JObj* temp_r29;
    Item* temp_r30;
    PAD_STACK(8);

    temp_r30 = gobj->user_data;
    temp_r29 = gobj->hsd_obj;
    if (temp_r30->xDC8_word.flags.x13) {
        sp3C = it_803B8600;
        it_8027429C(gobj, &sp3C);
    }
    it_8026B3A8(gobj);
    HSD_JObjSetFlagsAll(temp_r29, 0x10U);
    it_8026BD24(gobj);
    it_8027518C(gobj);
    temp_r30->x5D0_animFrameSpeed = 1.0f;
    it_80273454(gobj);
    temp_r30->xDD4_itemVar.bombhei.xDDC = 1;
    it_80272C08(gobj);
    it_802756D0(gobj);
    it_80275444(gobj);
    sp48 = temp_r30->pos;
    lb_800119DC(&sp48, 0x78, 1.0f, 0.02f, 1.0471976f);
    itBombhei_UpdateStatePreserveBone(gobj, 0xB, 0x12);
}

void it_80280DC0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
}

bool it_3F14_Logic6_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid != 7 && ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
    return false;
}

void it_80280B60(Item_GObj*);

bool it_3F14_Logic6_DmgReceived(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->msid != 7 && ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
    return false;
}

bool itBombhei_UnkMotion11_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

void itBombhei_UnkMotion11_Phys(Item_GObj* gobj) {}

bool itBombhei_UnkMotion11_Coll(Item_GObj* gobj)
{
    return false;
}

void it_3F14_Logic6_EnteredAir(Item_GObj* arg0)
{
    HSD_JObj* temp_r31;
    f32 temp_f30;
    f32 temp_f31;
    DynamicBoneTable* new_var;
    PAD_STACK(0x18);

    temp_r31 = (new_var = GET_ITEM(arg0)->xBBC_dynamicBoneTable)->bones[0xB];
    temp_f31 = HSD_JObjGetTranslationY(temp_r31);
    temp_f30 = HSD_JObjGetRotationX(temp_r31);
    Item_80268E5C((HSD_GObj*) arg0, 0xC, ITEM_ANIM_UPDATE);
    HSD_JObjSetTranslateY(temp_r31, temp_f31);
    HSD_JObjSetRotationX(temp_r31, temp_f30);
}

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

bool itBombhei_Logic6_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
    return false;
}

bool itBombhei_Logic6_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic6_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 9 && ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
    return false;
}

bool it_3F14_Logic6_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 9 && ip->xDD4_itemVar.bombhei.xDDC == 0) {
        it_80280B60(gobj);
    }
    return false;
}

void itBombhei_Logic6_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
