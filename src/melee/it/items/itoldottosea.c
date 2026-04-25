#include "itoldottosea.h"

#include "cm/camera.h"
#include "gm/gm_16AE.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itfreeze.h"
#include "it/items/itwhitebea.h"
#include "lb/lblanguage.h"
#include "mp/mpcoll.h"

#include <baselib/random.h>

ItemStateTable it_803F89C8[] = {
    { 0, itOldottosea_UnkMotion0_Anim, itOldottosea_UnkMotion0_Phys,
      itOldottosea_UnkMotion0_Coll },
    { 0, itOldottosea_UnkMotion2_Anim, itOldottosea_UnkMotion2_Phys,
      itOldottosea_UnkMotion2_Coll },
    { 1, itOldottosea_UnkMotion2_Anim, itOldottosea_UnkMotion2_Phys,
      itOldottosea_UnkMotion2_Coll },
    { 2, itOldottosea_UnkMotion3_Anim, itOldottosea_UnkMotion3_Phys,
      itOldottosea_UnkMotion3_Coll },
    { 0, itOldottosea_UnkMotion4_Anim, itOldottosea_UnkMotion4_Phys,
      itOldottosea_UnkMotion4_Coll },
    { 3, itOldottosea_UnkMotion5_Anim, itOldottosea_UnkMotion5_Phys,
      itOldottosea_UnkMotion5_Coll },
    { 4, itOldottosea_UnkMotion7_Anim, itOldottosea_UnkMotion7_Phys,
      itOldottosea_UnkMotion7_Coll },
    { 5, itOldottosea_UnkMotion7_Anim, itOldottosea_UnkMotion7_Phys,
      itOldottosea_UnkMotion7_Coll },
    { 3, itOldottosea_UnkMotion8_Anim, itOldottosea_UnkMotion8_Phys, NULL },
    { 6, itOldottosea_UnkMotion9_Anim, itOldottosea_UnkMotion9_Phys,
      itOldottosea_UnkMotion9_Coll },
    { 3, itOldottosea_UnkMotion10_Anim, itOldottosea_UnkMotion10_Phys,
      itOldottosea_UnkMotion10_Coll },
    { 3, itOldottosea_UnkMotion11_Anim, itOldottosea_UnkMotion11_Phys,
      itOldottosea_UnkMotion11_Coll },
};

void it_802E2470(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 facing;
    PAD_STACK(8);

    it_8027B730(gobj);
    ip->facing_dir = it_8026B684(&ip->pos);
    it_8027C56C(gobj, ip->facing_dir);
    if (ip->facing_dir == -1.0f) {
        facing = -1;
    } else {
        facing = 1;
    }
    mpCollSetFacingDir(&ip->x378_itemColl, facing);
    ip->xD5C = 0;
    ip->xDCC_flag.b3 = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDC8_word.flags.x19 = 1;
    ip->xDD4_itemVar.oldottosea.x28 = 1;
    ip->xDD4_itemVar.oldottosea.x20 = NULL;
    if (gm_8016AE80() == -1) {
        ip->xDD4_itemVar.oldottosea.x2C = 0;
    } else if (it_8026D324(It_Kind_Freeze) && HSD_Randi(attr->x28) == 0) {
        ip->xDD4_itemVar.oldottosea.x2C = 1;
    } else {
        ip->xDD4_itemVar.oldottosea.x2C = 0;
    }
    it_802E269C(gobj);
}

bool it_2725_Logic8_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(0x10);

    ip->init_facing_dir = ip->facing_dir;
    ip->xC9C += it_8027CBFC(gobj);
    if (ip->xC9C > attr->x0->x0 || ip->msid == 9) {
        if (ip->xDD4_itemVar.oldottosea.x20 != NULL) {
            it_8028ECE0(ip->xDD4_itemVar.oldottosea.x20);
            it_802E37A4(gobj);
        }
        it_8027C9D8(ip);
        it_802756D0(gobj);
        it_80275474(gobj);
        it_8027CE44(gobj);
        Camera_80030E44(2, &ip->pos);
        if (HSD_Randf() < it_804D6D40[2]) {
            it_802E3528(gobj);
        } else {
            it_802E3400(gobj);
        }
    } else {
        it_802E2C80(gobj);
    }
    return false;
}

void it_802E269C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CAD8(gobj);
    it_8027C0A8(gobj, ip->facing_dir, 1.0f);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itOldottosea_UnkMotion0_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itOldottosea_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.oldottosea.x28 == 0) {
        it_802E27B4(gobj);
        return;
    }
    ip->xDD4_itemVar.oldottosea.x28 -= 1;
}

bool itOldottosea_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E2BC0);
    return it_802E35CC(gobj);
}

void it_802E27B4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    Vec3 pos;
    int int_dir;

    itResetVelocity(ip);
    ip->xDD4_itemVar.oldottosea.x24 = 0;

    if (-1.0f == ip->facing_dir) {
        int_dir = -1;
    } else {
        int_dir = 1;
    }
    mpCollSetFacingDir(&ip->x378_itemColl, int_dir);

    it_802756E0(gobj);

    if (ip->xDD4_itemVar.oldottosea.x2C != 0) {
        pos = ip->pos;
        pos.x += attr->x14 * ip->facing_dir;
        ip->xDD4_itemVar.oldottosea.x20 =
            it_8028EB88(gobj, &pos, ip->facing_dir, attr->x24);
        if (ip->xDD4_itemVar.oldottosea.x20 != NULL) {
            it_8028EC98(ip->xDD4_itemVar.oldottosea.x20,
                        ip->x40_vel.x * attr->x1C);
        }
        ip->xDD4_itemVar.oldottosea.x2C = 0;
    }

    if ((u32) ip->xDD4_itemVar.oldottosea.x20 != 0) {
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
}

bool itOldottosea_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 threshold;
    PAD_STACK(0x10);

    if (lbLang_IsSettingUS()) {
        if (lbLang_IsSettingJP()) {
            threshold = 0x2A;
        } else {
            threshold = 0x50;
        }
        if (ip->xDD4_itemVar.oldottosea.x24 >= threshold) {
            if (HSD_Randi(attr->x10) == 0) {
                it_802E2E30(gobj);
            } else {
                ip->x40_vel.x = 0.0f;
                ip->xDD4_itemVar.oldottosea.x28 = 0;
                ip->xDD4_itemVar.oldottosea.x24 = 0;
                if (!it_80272C6C(gobj)) {
                    if (ip->xDD4_itemVar.oldottosea.x20 != NULL) {
                        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
                    } else {
                        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
                    }
                }
            }
        }
    } else {
        if (lbLang_IsSettingJP()) {
            threshold = 0x2A;
        } else {
            threshold = 0x50;
        }
        if (ip->xDD4_itemVar.oldottosea.x24 >= threshold) {
            if (HSD_Randi(attr->x10) == 0) {
                it_802E2E30(gobj);
            } else {
                ip->x40_vel.x = 0.0f;
                ip->xDD4_itemVar.oldottosea.x28 = 0;
                ip->xDD4_itemVar.oldottosea.x24 = 0;
                if (ip->xDD4_itemVar.oldottosea.x20 != NULL) {
                    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
                } else {
                    Item_80268E5C(gobj, 1, 0x12);
                }
            }
        }
    }
    return false;
}

void itOldottosea_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 jp_offset;

    if (lbLang_IsSettingJP()) {
        jp_offset = 10;
    } else {
        jp_offset = 0;
    }

    if (ip->xDD4_itemVar.oldottosea.x24 == jp_offset) {
        ip->x40_vel.x = ip->facing_dir * attr->x0->x4;
    }

    ip->xDD4_itemVar.oldottosea.x24++;

    if (ip->x40_vel.x) {
        if (ip->xDD4_itemVar.oldottosea.x20 == NULL) {
            if (it_802750E8(gobj, 2)) {
                it_802E3098(gobj);
            }
        }
    }

    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, ip->facing_dir, 5.0f);
}

bool itOldottosea_UnkMotion2_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (it_8026D8A4(gobj, it_802E3098)) {
        if (ip->x40_vel.x) {
            if (it_80276308(gobj) != 0) {
                it_802E3098(gobj);
            }
        }
    } else {
        it_802E2BC0(gobj);
    }
    return it_802E35CC(gobj);
}

void it_802E2BC0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.oldottosea.x28 = 0;
    ip->x40_vel.x *= attr->x4;
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itOldottosea_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itOldottosea_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itOldottosea_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802E269C);
    return it_802E35CC(gobj);
}

void it_802E2C80(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_802762BC(ip);

    if (it_8027B798(gobj, &ip->x40_vel) != 0) {
        it_802762BC(ip);
    } else {
        it_802762B0(ip);
    }

    ip->facing_dir = ip->init_facing_dir;
    Item_80268E5C(gobj, 5, 2);
}

bool itOldottosea_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (!it_80272C6C(gobj)) {
        if (ip->ground_or_air == GA_Air) {
            Item_80268E5C(gobj, 5, 2);
        } else {
            it_802E2DF4(gobj);
        }
    }
    return false;
}

void itOldottosea_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

bool itOldottosea_UnkMotion5_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_8026E664(gobj, it_802E2DF4);
    } else {
        it_8026D62C(gobj, it_802E2BC0);
    }
    return it_802E35CC(gobj);
}

void it_802E2DF4(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->xCCC_incDamageDirection == ip->facing_dir) {
        it_802E3098(gobj);
        return;
    }
    it_802E27B4(gobj);
}

void it_802E2E30(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xDD4_itemVar.oldottosea.x24 = 0;
    if ((u32) ip->xDD4_itemVar.oldottosea.x20 != 0) {
        Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    }
}

bool itOldottosea_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        ip->xDD4_itemVar.oldottosea.x28 = 0;
        ip = gobj->user_data;
        it_8027CAD8(gobj);
        it_8027C0A8(gobj, ip->facing_dir, 1.0f);
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itOldottosea_UnkMotion7_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 threshold;

    if (lbLang_IsSettingJP()) {
        threshold = 0x19;
    } else {
        threshold = 0x19;
    }
    if (ip->xDD4_itemVar.oldottosea.x24 == threshold) {
        ip->x40_vel.x = ip->facing_dir * attr->x8;
    } else {
        if (lbLang_IsSettingJP()) {
            threshold = 0x19;
        } else {
            threshold = 0x19;
        }
        if (ip->xDD4_itemVar.oldottosea.x24 > threshold) {
            ip->x40_vel.x += -ip->facing_dir * attr->xC;
        }
    }
    ip->xDD4_itemVar.oldottosea.x24++;
    if (ip->x40_vel.x && ip->xDD4_itemVar.oldottosea.x20 == NULL &&
        it_802750E8(gobj, 2))
    {
        it_802E3098(gobj);
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, ip->facing_dir, 5.0f);
}

bool itOldottosea_UnkMotion7_Coll(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    PAD_STACK(8);
    it_8026D62C(gobj, it_802E2BC0);
    if (ip->x40_vel.x) {
        if (it_80276308(gobj) != 0) {
            it_802E3098(gobj);
        }
    }
    return it_802E35CC(gobj);
}

void it_802E3098(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 val;

    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;

    if (lbLang_IsSettingJP()) {
        val = 0x37;
    } else {
        val = 0x28;
    }
    ip->xDD4_itemVar.oldottosea.x28 = val;

    Item_80268E5C(gobj, 3, 2);
    it_8026BDB4(gobj);
}

bool itOldottosea_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.oldottosea.x28 == 0) {
        int int_dir;
        ip->facing_dir = -ip->facing_dir;
        if (-1.0f == ip->facing_dir) {
            int_dir = -1;
        } else {
            int_dir = 1;
        }
        mpCollSetFacingDir(&ip->x378_itemColl, int_dir);
    }
    ip->xDD4_itemVar.oldottosea.x28--;
    if (!it_80272C6C(gobj)) {
        ip->xDD4_itemVar.oldottosea.x28 = 0;
        it_8026BD9C(gobj);
        it_802E27B4(gobj);
    }
    return false;
}

void itOldottosea_UnkMotion3_Phys(Item_GObj* gobj) {}

bool itOldottosea_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E2BC0);
    return it_802E35CC(gobj);
}
