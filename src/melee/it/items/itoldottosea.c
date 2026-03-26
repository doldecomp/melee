#include "itoldottosea.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/random.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "it/items/itwhitebea.h"
#include "lb/lblanguage.h"
#include "mp/mpcoll.h"

s32 gm_8016AE80(void);

typedef struct itOldottoseaInitAttrs {
    u8 pad[0x28];
    s8 x28;
} itOldottoseaInitAttrs;

void it_802E2470(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaInitAttrs* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 facing;
    u8 _[4];

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
    ip->xDCC_flag.b3 = false;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDC8_word.flags.x19 = true;
    ip->xDD4_itemVar.oldottosea.x28 = 1;
    ip->xDD4_itemVar.oldottosea.x20 = NULL;
    if (gm_8016AE80() == -1) {
        ip->xDD4_itemVar.oldottosea.x2C = 0;
    } else {
        if (it_8026D324(0x11) != 0 && HSD_Randi(attr->x28) == 0) {
            ip->xDD4_itemVar.oldottosea.x2C = 1;
        } else {
            ip->xDD4_itemVar.oldottosea.x2C = 0;
        }
    }
    it_802E269C(gobj);
}

/// #it_2725_Logic8_DmgReceived

void it_802E269C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CAD8(gobj);
    it_8027C0A8(gobj, ip->facing_dir, 1.0f);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

typedef struct itOldottoseaMotionAttrs {
    /* +00 */ s32* x0;
    /* +04 */ f32 x4;
    /* +08 */ f32 x8;
    /* +0C */ f32 xC;
    /* +10 */ s8 x10;
} itOldottoseaMotionAttrs;

/// #it_2725_Logic8_DmgReceived

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

/// #it_802E27B4

bool itOldottosea_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itOldottoseaMotionAttrs* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 limit;
    u8 _[0x10];

    if (lbLang_IsSettingUS()) {
        if (lbLang_IsSettingJP()) {
            limit = 0x2A;
        } else {
            limit = 0x50;
        }
        if (ip->xDD4_itemVar.oldottosea.x24 >= limit) {
            if (HSD_Randi(attr->x10) == 0) {
                it_802E2E30(gobj);
            } else {
                ip->x40_vel.x = 0.0f;
                ip->xDD4_itemVar.oldottosea.x28 = 0;
                ip->xDD4_itemVar.oldottosea.x24 = 0;
                if (!it_80272C6C(gobj)) {
                    if ((u32) ip->xDD4_itemVar.oldottosea.x20 != 0U) {
                        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
                    } else {
                        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
                    }
                }
            }
        }
    } else {
        if (lbLang_IsSettingJP()) {
            limit = 0x2A;
        } else {
            limit = 0x50;
        }
        if (ip->xDD4_itemVar.oldottosea.x24 >= limit) {
            if (HSD_Randi(attr->x10) == 0) {
                it_802E2E30(gobj);
            } else {
                ip->x40_vel.x = 0.0f;
                ip->xDD4_itemVar.oldottosea.x28 = 0;
                ip->xDD4_itemVar.oldottosea.x24 = 0;
                if ((u32) ip->xDD4_itemVar.oldottosea.x20 != 0U) {
                    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
                } else {
                    Item_80268E5C(gobj, 1, 0x12);
                }
            }
        }
    }
    return false;
}

/// #itOldottosea_UnkMotion2_Phys

/// #itOldottosea_UnkMotion2_Coll

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
    Item* ip = GET_ITEM(gobj);

    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xDD4_itemVar.oldottosea.x24 = 0;
    if ((u32) ip->xDD4_itemVar.oldottosea.x20 != 0U) {
        Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    }
}

bool itOldottosea_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (!it_80272C6C(gobj)) {
        ip->xDD4_itemVar.oldottosea.x28 = 0;
        ip = GET_ITEM(gobj);
        it_8027CAD8(gobj);
        it_8027C0A8(gobj, ip->facing_dir, 1.0f);
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

/// #itOldottosea_UnkMotion7_Phys

/// #itOldottosea_UnkMotion7_Coll

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
