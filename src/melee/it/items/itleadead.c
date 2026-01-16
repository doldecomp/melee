#include "itleadead.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "ft/ft_0C31.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"
#include "sysdolphin/baselib/random.h"

#include <baselib/jobj.h>
#include <MSL/math.h>
#include <MSL/trigf.h>

ItemStateTable it_803F8EB0[] = {
    {
        0,
        NULL,
        NULL,
        NULL,
    },
    {
        -1,
        itLeadead_UnkMotion1_Anim,
        itLeadead_UnkMotion1_Phys,
        itLeadead_UnkMotion1_Coll,
    },
    {
        1,
        itLeadead_UnkMotion2_Anim,
        itLeadead_UnkMotion2_Phys,
        itLeadead_UnkMotion2_Coll,
    },
    {
        2,
        itLeadead_UnkMotion3_Anim,
        itLeadead_UnkMotion3_Phys,
        itLeadead_UnkMotion3_Coll,
    },
    {
        3,
        itLeadead_UnkMotion4_Anim,
        itLeadead_UnkMotion4_Phys,
        itLeadead_UnkMotion4_Coll,
    },
    {
        4,
        itLeadead_UnkMotion5_Anim,
        itLeadead_UnkMotion5_Phys,
        itLeadead_UnkMotion5_Coll,
    },
    {
        5,
        itLeadead_UnkMotion6_Anim,
        itLeadead_UnkMotion6_Phys,
        itLeadead_UnkMotion6_Coll,
    },
    {
        6,
        itLeadead_UnkMotion7_Anim,
        itLeadead_UnkMotion7_Phys,
        itLeadead_UnkMotion7_Coll,
    },
    {
        -1,
        itLeadead_UnkMotion8_Anim,
        itLeadead_UnkMotion8_Phys,
        itLeadead_UnkMotion8_Coll,
    },
    {
        7,
        itLeadead_UnkMotion9_Anim,
        itLeadead_UnkMotion9_Phys,
        itLeadead_UnkMotion9_Coll,
    },
    {
        1,
        itLeadead_UnkMotion10_Anim,
        itLeadead_UnkMotion10_Phys,
        itLeadead_UnkMotion10_Coll,
    },
    {
        -1,
        itLeadead_UnkMotion11_Anim,
        itLeadead_UnkMotion12_Phys,
        itLeadead_UnkMotion12_Coll,
    },
    {
        -1,
        itLeadead_UnkMotion12_Anim,
        itLeadead_UnkMotion12_Phys,
        itLeadead_UnkMotion12_Coll,
    },
    {
        8,
        itLeadead_UnkMotion13_Anim,
        itLeadead_UnkMotion13_Phys,
        NULL,
    },
    {
        9,
        itLeadead_UnkMotion14_Anim,
        itLeadead_UnkMotion14_Phys,
        itLeadead_UnkMotion14_Coll,
    },
    {
        -1,
        itLeadead_UnkMotion15_Anim,
        itLeadead_UnkMotion15_Phys,
        itLeadead_UnkMotion15_Coll,
    },
    {
        -1,
        itLeadead_UnkMotion16_Anim,
        itLeadead_UnkMotion16_Phys,
        itLeadead_UnkMotion16_Coll,
    },
    {
        -1,
        itLeadead_UnkMotion17_Anim,
        itLeadead_UnkMotion17_Phys,
        itLeadead_UnkMotion17_Coll,
    },
};

void it_802E8BCC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 facing;

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
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDC8_word.flags.x19 = 1;
    ip->xDD4_itemVar.leadead.x48 = 0;
    ip->xDD4_itemVar.leadead.x50 = 0;
    ip->xDD4_itemVar.leadead.x4C = attr->x1C;
    it_80271590(gobj, 0, (HurtCapsule*) &ip->xDD4_itemVar.leadead.xE30_state);
    ip->xDD4_itemVar.leadead.xE50 = ip->xC1C;
    ip->xDD4_itemVar.leadead.x38 = NULL;
    it_802E9308(gobj);
}

bool it_802E8CD8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(24);

    if (ip->xDD4_itemVar.leadead.x38 != NULL) {
        Fighter_GObj* fobj = ip->xDD4_itemVar.leadead.x38;
        it_802EAC8C(gobj);
        ftCo_800C7800(fobj);
    }
    ip->xDD4_itemVar.leadead.x48 = 0;
    ip->xDD4_itemVar.leadead.x4C = attr->x1C;
    ip->init_facing_dir = ip->facing_dir;
    if ((ip->msid == 7) || (ip->msid == 0xC)) {
        return false;
    }
    ip->xC9C += it_8027CBFC(gobj);
    if ((ip->xC9C > attr->x0->x0) || (ip->msid == 0xE)) {
        it_8027C9D8(ip);
        it_802756D0(gobj);
        it_8027CE44(gobj);
        Camera_80030E44(2, &ip->pos);
        if (HSD_Randf() < it_804D6D40[2]) {
            it_802EA334(gobj);
        } else if (ip->msid == 8) {
            it_802EA2A0(gobj);
        } else {
            it_802EA2A0(gobj);
        }
    } else if (ip->msid == 8) {
        it_802E9494(gobj);
    } else if (ip->xC9C > (attr->x0->x0 * attr->x8)) {
        if (it_802EA804(gobj, 15.0f) != 0) {
            it_802E9738(gobj);
        } else if ((ip->xDD4_itemVar.leadead.x50 > 1) && (HSD_Randi(2) == 0)) {
            if (HSD_Randf() < it_804D6D40[2]) {
                it_802EA334(gobj);
            } else {
                it_802EA2A0(gobj);
            }
        } else {
            ip->x40_vel.x *= 1.5f;
            ip->xDD4_itemVar.leadead.x50 += 1;
            it_802E93C8(gobj);
        }
    } else {
        it_802E93C8(gobj);
    }
    return false;
}

static inline void it_802E8F24_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CAD8(gobj);
    ip->xDC8_word.flags.x1A = true;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

void it_802E8F24(Item_GObj* gobj)
{
    it_802E8F24_inline(gobj);
}

bool itLeadead_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.leadead.x48 == 0) {
        it_8027C56C(gobj, ip->facing_dir);
        it_802E9038(gobj);
        return;
    }
    it_8027C0F0(gobj, NULL, ip->facing_dir, 2.0f);
    ip->xDD4_itemVar.leadead.x48--;
}

bool itLeadead_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E9308);
    return it_8027C794(gobj);
}

void it_802E9038(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = ip->facing_dir * attr->x0->x4;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    it_8027C56C(gobj, ip->facing_dir);
    it_802756E0(gobj);
    ip->xDD4_itemVar.leadead.x44 = 0;
    if (ip->xDD4_itemVar.leadead.x48 == 0) {
        ip->xDD4_itemVar.leadead.x48 = attr->x18;
    }
    it_802EA478(gobj, 0, 0);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

static inline void itLeadead_UnkMotion2_Anim_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = ip->facing_dir * attr->x0->x4;
    ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    it_8027C56C(gobj, ip->facing_dir);
    it_802756E0(gobj);
    ip->xDD4_itemVar.leadead.x44 = 0;
    if (ip->xDD4_itemVar.leadead.x48 == 0) {
        ip->xDD4_itemVar.leadead.x48 = attr->x18;
    }
    it_802EA478(gobj, 0, 0);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itLeadead_UnkMotion2_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        itLeadead_UnkMotion2_Anim_inline(gobj);
    }
    return false;
}

void itLeadead_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 r3 = it_802EA674(gobj);
    s32 x48 = ip->xDD4_itemVar.leadead.x48;
    if (x48 == 0) {
        if (r3 != 0) {
            it_802E9BA0(gobj);
        } else {
            ip->xDD4_itemVar.leadead.x48 = attr->x18;
        }
    } else {
        ip->xDD4_itemVar.leadead.x48 = x48 - 1;
        if ((r3 == 0) && (it_802EA6F4(gobj) != 0)) {
            it_802E9D50(gobj);
        }
    }
    ip->xDD4_itemVar.leadead.x44 += 1;
    {
        f32 facing = ip->facing_dir;
        if (((facing > 0.0f) && (ip->x70_nudge.x < 0.0f)) ||
            ((facing < 0.0f) && (ip->x70_nudge.x > 0.0f)))
        {
            it_802E9BA0(gobj);
        }
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
}

bool itLeadead_UnkMotion2_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (it_8026D8A4(gobj, it_802E9BA0) != 0) {
        if (it_80276308(gobj) != 0) {
            it_802E9BA0(gobj);
        }
    } else {
        it_802E9308(gobj);
    }
    return it_8027C794(gobj);
}

static inline void it_802E9308_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.leadead.x48 = 0;
    ip->x40_vel.x *= attr->xC;
    Item_80268E5C(gobj, 0xA, ITEM_ANIM_UPDATE);
}

void it_802E9308(Item_GObj* gobj)
{
    it_802E9308_inline(gobj);
}

bool itLeadead_UnkMotion10_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion10_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itLeadead_UnkMotion10_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, it_802E8F24);
    return it_8027C794(gobj);
}

void it_802E93C8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 facing;
    if (it_8027B798(gobj, &ip->x40_vel) != 0) {
        if (ip->x40_vel.y <= 0.2f) {
            ip->x40_vel.y = 0.2f;
        }
        it_802762BC(ip);
    } else {
        it_802762B0(ip);
    }
    ip->facing_dir = ip->init_facing_dir;
    if (ip->facing_dir == -1.0f) {
        facing = -1;
    } else {
        facing = 1;
    }
    mpCollSetFacingDir(&ip->x378_itemColl, facing);
    ip->xDD4_itemVar.leadead.x48 = attr->x4;
    ip->xDD4_itemVar.leadead.x4C = attr->x1C;
    Item_80268E5C(gobj, 0xB, ITEM_UNK_0x1);
}

void it_802E9494(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    f32 fall_speed;
    if (it_8027B798(gobj, &ip->x40_vel) != 0) {
        if (ip->x40_vel.y <= 0.2f) {
            ip->x40_vel.y = 0.2f;
        }
        it_802762BC(ip);
    } else {
        it_802762B0(ip);
    }
    ip->x40_vel.x = 0.0f;
    ip->x40_vel.y = 0.3f * ip->x40_vel.y;
    fall_speed = ip->xCC_item_attr->x10_fall_speed;
    if (ip->x40_vel.y <= fall_speed) {
        ip->x40_vel.y = fall_speed + 0.1f;
    }
    ip->xDD4_itemVar.leadead.x44 = 1;
    ip->facing_dir = ip->init_facing_dir;
    mpCollSetFacingDir(&ip->x378_itemColl, ip->facing_dir == -1.0f ? -1 : 1);
    ip->xDD4_itemVar.leadead.x48 = attr->x4;
    ip->xDD4_itemVar.leadead.x4C = attr->x1C;
    Item_80268E5C(gobj, 0xC, ITEM_UNK_0x1);
}

bool itLeadead_UnkMotion11_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    if (ip->xDD4_itemVar.leadead.x48 == 0) {
        if (ip->ground_or_air == GA_Ground) {
            it_8027CAD8(gobj);
            ip->xDC8_word.flags.x1A = true;
            Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        }
    } else if (ip->xDD4_itemVar.leadead.x48 > 0) {
        ip->xDD4_itemVar.leadead.x48--;
    }
    return false;
}

bool itLeadead_UnkMotion12_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.leadead.x48 == 0) {
        if (ip->ground_or_air == GA_Ground) {
            it_802E98E0(gobj);
        }
    } else if (ip->xDD4_itemVar.leadead.x48 > 0) {
        ip->xDD4_itemVar.leadead.x48--;
    }
    return false;
}

void itLeadead_UnkMotion12_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

bool itLeadead_UnkMotion12_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        s32 coll = it_8026DB40(gobj);
        if (coll & 0xC) {
            it_8027781C(gobj);
        }
        if (coll & 1) {
            it_802762B0(ip);
            itResetVelocity(ip);
        }
    } else {
        it_8026D82C(gobj);
    }
    return it_8027C794(gobj);
}

void it_802E9738(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    ip->xDD4_itemVar.leadead.x44 = 0;
    ip->xDD4_itemVar.leadead.x50 = 0;
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itLeadead_UnkMotion7_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.leadead.x44 < 0x1B) {
        it_802EA478(gobj, 1, 0);
    } else if (ip->xDD4_itemVar.leadead.x44 < 0x2A) {
        it_802EA478(gobj, 1, 1);
    } else if (ip->xDD4_itemVar.leadead.x44 < 0x42) {
        it_802EA478(gobj, 1, 2);
    } else if (ip->xDD4_itemVar.leadead.x44 < 0x51) {
        it_802EA478(gobj, 1, 3);
    } else {
        it_802EA478(gobj, 2, 0);
        it_802E98E0(gobj);
    }
    ip->xDD4_itemVar.leadead.x44++;
    return false;
}

void itLeadead_UnkMotion7_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, ip->facing_dir, 5.0F);
}

bool itLeadead_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026D6F4(gobj, it_802E9308);
    return it_8027C794(gobj);
}

void it_802E98E0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    itResetVelocity(ip);
    ip->xDC8_word.flags.x1A = false;
    ip->xDD4_itemVar.leadead.x48 = ip->xC9C * attr->x1A;
    ip->xDD4_itemVar.leadead.x44 = 0;
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
}

bool itLeadead_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 x48 = ip->xDD4_itemVar.leadead.x48;
    if (x48 == 0) {
        it_802E9A00(gobj);
    } else {
        ip->xDD4_itemVar.leadead.x48 = x48 - 1;
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, ip->facing_dir, 5.0f);
}

bool itLeadead_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026D6F4(gobj, it_802E9308);
    return it_8027C794(gobj);
}

void it_802E9A00(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.leadead.x48 = 0;
    ip->xDD4_itemVar.leadead.x44 = 0;
    Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
}

bool itLeadead_UnkMotion9_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.leadead.x44 < 0x2E) {
        it_802EA478(gobj, 2, 0);
    } else if (ip->xDD4_itemVar.leadead.x44 < 0x57) {
        it_802EA478(gobj, 3, 1);
    } else if (ip->xDD4_itemVar.leadead.x44 < 0x82) {
        it_802EA478(gobj, 3, 2);
    } else if (ip->xDD4_itemVar.leadead.x44 < 0xAA) {
        it_802EA478(gobj, 3, 3);
    } else if (ip->xDD4_itemVar.leadead.x44 < 0x105) {
        it_802EA478(gobj, 3, 4);
    } else {
        it_802EA478(gobj, 0, 0);
    }
    ip->xDD4_itemVar.leadead.x44++;
    if (it_80272C6C(gobj) == 0) {
        ip->xDD4_itemVar.leadead.x48 = 0xA;
        it_802E8F24_inline(gobj);
    }
    return false;
}

void itLeadead_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itLeadead_UnkMotion9_Coll(Item_GObj* gobj)
{
    it_8026D6F4(gobj, it_802E9308);
    return it_8027C794(gobj);
}

void it_802E9BA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    ip->xDD4_itemVar.leadead.x48 = 0x8C;
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

static inline void itLeadead_UnkMotion3_Anim_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.leadead.x48 = attr->x18 * 3;
}

bool itLeadead_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.leadead.x48 == 0) {
        s32 facing;
        ip->facing_dir = -ip->facing_dir;
        if (ip->facing_dir == -1.0f) {
            facing = -1;
        } else {
            facing = 1;
        }
        mpCollSetFacingDir(&ip->x378_itemColl, facing);
    }
    ip->xDD4_itemVar.leadead.x48--;
    if (it_80272C6C(gobj) == 0) {
        itLeadead_UnkMotion3_Anim_inline(gobj);
        itLeadead_UnkMotion2_Anim_inline(gobj);
    }
    return false;
}

void itLeadead_UnkMotion3_Phys(Item_GObj* gobj) {}

bool itLeadead_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E9308);
    return it_8027C794(gobj);
}

void it_802E9D50(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.leadead.x48 = 0;
    itResetVelocity(ip);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itLeadead_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.leadead.x48 > 0x24) {
        ip->x40_vel.x = attr->x14 * ip->facing_dir;
    }
    if (ip->xDD4_itemVar.leadead.x48 > 0x71) {
        ip->x40_vel.x = 0.0f;
    }
    ip->xDD4_itemVar.leadead.x48++;
}

static void itLeadead_UnkMotion4_Coll_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = ip->facing_dir * attr->x0->x4;
    ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    it_8027C56C(gobj, ip->facing_dir);
    it_802756E0(gobj);
    ip->xDD4_itemVar.leadead.x44 = 0;
    if (ip->xDD4_itemVar.leadead.x48 == 0) {
        ip->xDD4_itemVar.leadead.x48 = attr->x18;
    }
    it_802EA478(gobj, 0, 0);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itLeadead_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    it_8026D62C(gobj, it_802E9308);
    if (it_80272C6C(gobj) == 0) {
        if (it_80276308(gobj) != 0) {
            it_802E9BA0(gobj);
        } else {
            ip->xDD4_itemVar.leadead.x48 = 1;
            itLeadead_UnkMotion4_Coll_inline(gobj);
        }
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    return it_8027C794(gobj);
}

bool itLeadead_UnkMotion5_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_80272C6C(gobj) == 0) {
        HSD_JObj* jobj;
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE | ITEM_HIT_PRESERVE);
        jobj = it_80272CC0(gobj, 1);
        HSD_JObjSetTranslateZ(jobj, ip->xDD4_itemVar.leadead.x3C);
    }
    return false;
}

void itLeadead_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itLeadead_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

bool itLeadead_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    if (it_80272C6C(gobj) == 0) {
        ip->xDD4_itemVar.leadead.x4C = attr->x1C;
        ip->xDD4_itemVar.leadead.x48 = 0;
        it_802E8F24_inline(gobj);
    }
    return false;
}

void itLeadead_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itLeadead_UnkMotion6_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E9308);
    return it_8027C794(gobj);
}

void it_2725_Logic1_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0xD, ITEM_ANIM_UPDATE);
}

bool itLeadead_UnkMotion13_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 0xD, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itLeadead_UnkMotion13_Phys(Item_GObj* gobj) {}

void it_2725_Logic1_Dropped(Item_GObj* gobj)
{
    it_8027CBA4(gobj);
    it_802E9308_inline(gobj);
}

void it_2725_Logic1_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CB3C(gobj);
    ip->xDD4_itemVar.leadead.x48 = 0;
    Item_80268E5C(gobj, 0xE, ITEM_ANIM_UPDATE);
}

bool itLeadead_UnkMotion14_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 0xE, 0x12);
    }
    return false;
}

void itLeadead_UnkMotion14_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itLeadead_UnkMotion14_Coll(Item_GObj* gobj)
{
    return it_8027C824(gobj, NULL);
}

void it_802EA2A0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027B964(gobj, 0);
    ip->facing_dir = ip->init_facing_dir;
    ip->xDD4_itemVar.leadead.xDEC = 0;
    Item_80268E5C(gobj, 0xF, 3);
}

bool itLeadead_UnkMotion15_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion15_Phys(Item_GObj* gobj) {}

bool itLeadead_UnkMotion15_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

void it_802EA334(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027BA54(gobj, &ip->x40_vel);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0x10, 3);
}

bool itLeadead_UnkMotion16_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion16_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itLeadead_UnkMotion16_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

bool itLeadead_UnkMotion17_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion17_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itLeadead_UnkMotion17_Coll(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}

void it_2725_Logic1_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.leadead.x38 != NULL) {
        Fighter_GObj* fobj = ip->xDD4_itemVar.leadead.x38;
        it_802EAC8C(gobj);
        ftCo_800C7800(fobj);
    }
    it_2725_Logic9_Destroyed(gobj);
}

void it_802EA478(Item_GObj* gobj, s32 arg1, s32 arg2)
{
    itECB ecb;
    Item* ip = GET_ITEM(gobj);
    s32 facing;

    if (arg2 == 0) {
        ecb = ip->xDD4_itemVar.leadead.xE50;
    } else {
        ecb = ip->xC1C;
    }
    switch (arg1) {
    case 1:
        if (arg2 == 1) {
            ecb.top -= 0.3f;
        } else if (arg2 == 2) {
            ecb.top -= 0.1f;
            ecb.right += 0.1f;
        } else if (arg2 == 3) {
            ecb.top -= 0.4f;
            ecb.right += 0.5f;
        }
        break;
    case 2:
        ecb.right = 0.9f * ecb.top;
        ecb.top = 3.0f;
        ecb.left *= 2.0f;
        break;
    case 3:
        if (arg2 == 1) {
            ecb.top += 0.1f;
            ecb.right -= 0.05f;
            ecb.left = 0.0f;
        } else if (arg2 == 2) {
            ecb.top += 0.1f;
        } else if (arg2 == 3) {
            ecb.top += 0.2f;
            ecb.right -= 0.1f;
        } else if (arg2 == 4) {
            ecb.left = ip->xDD4_itemVar.leadead.xE50.left;
            ecb.right -= 0.1f;
        }
        break;
    }
    it_80275D5C(gobj, &ecb);
    if (ip->facing_dir == -1.0f) {
        facing = -1;
    } else {
        facing = 1;
    }
    mpCollSetFacingDir(&ip->x378_itemColl, facing);
}

s32 it_802EA674(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 result = 0;
    HSD_GObj* fighter = ftLib_8008627C(&ip->pos, NULL);
    PAD_STACK(4);
    if (fighter != NULL) {
        Vec3 v;
        f32 facing;
        PAD_STACK(4);
        ftLib_80086644(fighter, &v);
        if (ip->pos.x < v.x) {
            facing = 1.0f;
        } else {
            facing = -1.0f;
        }
        if (facing != ip->facing_dir) {
            result = 1;
        }
    }
    return result;
}

s32 it_802EA6F4(Item_GObj* gobj)
{
    Vec3 sp18;
    Item* ip;
    itLeadeadAttributes* attr;
    s32 result = 0;
    PAD_STACK(8);
    ip = GET_ITEM(gobj);
    attr = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.leadead.x4C == 0) {
        if (HSD_Randi(attr->x1E) == 0) {
            HSD_GObj* fighter = ftLib_8008627C(&ip->pos, NULL);
            if (fighter != NULL) {
                f32 dx, dy;
                if (it_8027CA7C(fighter) != 0) {
                    return 0;
                }
                ftLib_80086644(fighter, &sp18);
                dx = sp18.x - ip->pos.x;
                if (dx < 0.0f) {
                    dx = -dx;
                }
                if (dx <= attr->x10) {
                    dy = sp18.y - ip->pos.y;
                    if (dy < 0.0f) {
                        dy = -dy;
                    }
                    if (dy <= 5.0f) {
                        result = 1;
                    }
                }
            }
        }
    } else {
        ip->xDD4_itemVar.leadead.x4C--;
    }
    return result;
}

static inline f32 neg_dot(Vec3* a, Vec3* b)
{
    return -(a->x * b->x) - (a->y * b->y) - (a->z * b->z);
}

bool it_802EA804(Item_GObj* gobj, f32 range)
{
    Item* ip = GET_ITEM(gobj);
    CollData* cd = &ip->x378_itemColl;
    Vec3 v1, v2, v3;
    bool ret;
    PAD_STACK(16);

    mpLib_80056C54(cd->floor.index, &ip->pos, NULL, NULL, NULL, &v1, 0.0f,
                   0.0f);
    ret = mpLib_80056C54(cd->floor.index, &ip->pos, NULL, &v3, NULL, &v2,
                         ip->facing_dir * range, 0.0f);
    if (ret) {
        f32 deg1 = 57.29578f * atan2f(v1.y, v1.x);
        f32 deg2 = 57.29578f * atan2f(v2.y, v2.x);
        f32 dot1 = neg_dot(&ip->pos, &v1);
        f32 dot2 = neg_dot(&v3, &v2);
        if (ABS(deg2 - deg1) > 30.0f) {
            ret = false;
        } else if (ABS(dot1 - dot2) > 3.0f) {
            ret = false;
        }
    } else {
        ret = it_802EA988(gobj, ip->facing_dir * range, 0.0f);
    }
    return ret;
}

s32 it_802EA988(Item_GObj* gobj, f32 x_offset, f32 y_offset)
{
    Item* ip = GET_ITEM(gobj);
    CollData cd = ip->x378_itemColl;
    s32 ret = 0;
    cd.cur_pos.x += x_offset;
    cd.cur_pos.y += y_offset;
    if (cd.env_flags & Collide_LeftWallMask) {
        ret = 8;
    }
    if (cd.env_flags & Collide_RightWallMask) {
        ret = 4;
    }
    return ret;
}

Item_GObj* it_802EA9FC(Vec3* pos, s32 facing_dir)
{
    Item_GObj* gobj;
    PAD_STACK(16);
    gobj = it_8027B5B0(It_Kind_Leadead, pos, NULL, NULL, true);
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        s32 coll_facing;
        ip->facing_dir = facing_dir;
        if (ip->facing_dir == -1.0f) {
            coll_facing = -1;
        } else {
            coll_facing = 1;
        }
        mpCollSetFacingDir(&ip->x378_itemColl, coll_facing);
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        HSD_JObjAnimAll(gobj->hsd_obj);
        it_802762BC(ip);
        it_802E9308_inline(gobj);
    }
    return gobj;
}

void it_802EAAEC(Item_GObj* gobj, Fighter_GObj* fobj, int part, f32 val)
{
    Vec3 sp24;
    Item* ip2;
    Item* ip;
    HSD_JObj* jobj;
    s32 facing;
    PAD_STACK(4);

    ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.leadead.x3C = -12.0f;
    it_8026BD54(gobj);
    ip2 = GET_ITEM(gobj);
    ip2->x40_vel.x = ip2->x40_vel.y = ip2->x40_vel.z = 0.0f;
    it_80275258(gobj);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    jobj = it_80272CC0(gobj, 1);
    HSD_JObjSetTranslateZ(jobj, ip2->xDD4_itemVar.leadead.x3C);
    it_80274ECC(gobj, 1);
    Item_8026AE84(ip, 0x135, 0x7F, 0x40);
    ftLib_80086644(fobj, &sp24);
    if (ip->pos.x < sp24.x) {
        ip->facing_dir = 1.0f;
    } else {
        ip->facing_dir = -1.0f;
    }
    if (ip->facing_dir == -1.0f) {
        facing = -1;
    } else {
        facing = 1;
    }
    mpCollSetFacingDir(&ip->x378_itemColl, facing);
    it_8027C56C(gobj, ip->facing_dir);
    it_8026D564(gobj);
    it_80274FDC(gobj, 0, fobj, part);
    ip->xDD4_itemVar.leadead.x38 = fobj;
    ip->xDD4_itemVar.leadead.xE14 = part;
}

void it_802EAC8C(Item_GObj* gobj)
{
    Vec3 sp1C;
    Vec3 offset;
    Item* ip = GET_ITEM(gobj);
    itLeadeadAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj;

    it_80275070(gobj, 0);
    offset.z = -ip->xDD4_itemVar.leadead.x3C;
    offset.y = 0.0f;
    offset.x = 0.0f;
    lb_8000B1CC(ftLib_80086630(ip->xDD4_itemVar.leadead.x38,
                               ip->xDD4_itemVar.leadead.xE14),
                &offset, &sp1C);
    ip->pos = sp1C;
    it_802759DC(gobj, ip->xDD4_itemVar.leadead.x38);
    ip->xDD4_itemVar.leadead.x38 = NULL;
    ip->xDD4_itemVar.leadead.xE14 = FtPart_TopN;
    jobj = it_80272CC0(gobj, 1);
    HSD_JObjSetTranslateZ(jobj, 0.0f);
    ip->xDD4_itemVar.leadead.x4C = attr->x1C;
    ip->xDD4_itemVar.leadead.x48 = 0;
    it_8026BD3C(gobj);
}

void it_802EADD8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    it_802EAC8C(gobj);
    if (ip->ground_or_air == GA_Ground) {
        it_802E8F24_inline(gobj);
    } else {
        it_802E9308_inline(gobj);
    }
}

static inline void it_802EAE80_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
    it_80275258(gobj);
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

void it_802EAE80(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802EAC8C(gobj);
    if (ip->ground_or_air == GA_Ground) {
        it_802EAE80_inline(gobj);
    } else {
        it_802E9308_inline(gobj);
    }
}
