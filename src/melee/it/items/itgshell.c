#include "itgshell.h"

#include "common_structs.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/jobj.h"
#include "ef/efasync.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "it/items/itgshell.h"

#include <sysdolphin/baselib/random.h>
#include <MSL/math.h>

typedef struct itGShell_Attrs {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    char pad18[0x1C - 0x18];
    float x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    float x30;
    Vec x34;
} itGShell_Attrs;
STATIC_ASSERT(sizeof(itGShell_Attrs) == 64);

ItemStateTable it_803F5BA8[] = {
    { -1, itGshell_UnkMotion0_Anim, itGshell_UnkMotion0_Phys,
      itGshell_UnkMotion0_Coll },
    { -1, itGshell_UnkMotion1_Anim, itGshell_UnkMotion1_Phys,
      itGshell_UnkMotion1_Coll },
    { -1, itGshell_UnkMotion2_Anim, itGshell_UnkMotion2_Phys, NULL },
    { 0, itGshell_UnkMotion3_Anim, itGshell_UnkMotion3_Phys,
      itGshell_UnkMotion3_Coll },
    { 0, itGshell_UnkMotion4_Anim, itGshell_UnkMotion4_Phys,
      itGshell_UnkMotion4_Coll },
    { 0, itGshell_UnkMotion6_Anim, itGshell_UnkMotion6_Phys,
      itGshell_UnkMotion6_Coll },
    { -1, itGshell_UnkMotion6_Anim, itGshell_UnkMotion6_Phys,
      itGshell_UnkMotion6_Coll },
    { 0, itGshell_UnkMotion8_Anim, itGshell_UnkMotion8_Phys,
      itGshell_UnkMotion8_Coll },
    { -1, itGshell_UnkMotion8_Anim, itGshell_UnkMotion8_Phys,
      itGshell_UnkMotion8_Coll },
    { -1, itGshell_UnkMotion9_Anim, itGshell_UnkMotion9_Phys,
      itGshell_UnkMotion9_Coll },
};

void it_8028B8D8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    Vec v;
    HSD_JObj* jobj;
    PAD_STACK(4);
    if (ip->xDD4_itemVar.gshell.xDDC <= 0.0f) {
        jobj = GET_JOBJ(gobj);
        v = attrs->x34;
        v.x *= -ip->facing_dir;
        efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 2, 1029, jobj, &v);
        ip->xDD4_itemVar.gshell.xDDC = attrs->x30;
    } else {
        ip->xDD4_itemVar.gshell.xDDC -= 1.0f;
    }
}

void it_8028B988(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.gshell.xDEC_b1) {
        ip->xDD4_itemVar.gshell.xDE0 -= 1.0f;
        if (ip->xDD4_itemVar.gshell.xDE0 <= 0.0f) {
            ip->xDD4_itemVar.gshell.xDEC_b1 = 0;
            ip->xDD4_itemVar.gshell.xDE0 = attrs->x28;
            it_8027572C(gobj, 0);
            if (ip->xDD4_itemVar.gshell.xDEC_b2) {
                it_802756E0(gobj);
            }
        }
    }
}

void it_8028BA2C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_80275D5C(gobj, &ip->xC0C);
    if (ABS(ip->x40_vel.x) < attrs->x8) {
        ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
        if (!it_80277040(gobj)) {
            it_8028BE54(gobj);
        } else {
            itGShell_Logic14_EnteredAir(gobj);
        }
    } else {
        it_8028C3A8(gobj);
    }
}

void it_8028BAD8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    switch (ip->msid) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 9:
        ip->x40_vel.x = -ip->xCCC_incDamageDirection * (ip->xCA0 * attrs->x14);
        ip->xDD4_itemVar.gshell.xDEC_b2 = 1;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        ip->x40_vel.x +=
            -ip->xCCC_incDamageDirection * (ip->xCA0 * attrs->x14);
        ip->xDD4_itemVar.gshell.xDEC_b2 = 1;
        break;
    default:
        break;
    }
    it_8027236C(gobj);
    it_802756D0(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_8028C898(gobj);
    } else {
        it_8028C3A8(gobj);
    }
    ip->xDD4_itemVar.gshell.xDEC_b1 = 1;
    it_8027570C(gobj, 0);
}

void it_8028BC2C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    switch (ip->msid) {
    case 5:
    case 6:
    case 7:
    case 8:
        it_802756D0(gobj);
        it_80275444(gobj);
        ip->x40_vel.x = -ip->x40_vel.x * attrs->xC * HSD_Randf();
        ip->x40_vel.y = attrs->x10;
        if (ip->xDD4_itemVar.gshell.xDEC_b0) {
            ip->xDD4_itemVar.gshell.xDE8 =
                HSD_Randi(it_804D6D28->x48_byte & 0xF);
        } else {
            ip->xDD4_itemVar.gshell.xDEC_b0 = 1;
        }
        it_802762BC(ip);
        it_8028C018(gobj);
        ip->xDD4_itemVar.gshell.xDEC_b3 = 1;
        ip->xDD4_itemVar.gshell.xDE4 = attrs->x2C;
        ip->xDD4_itemVar.gshell.xDEC_b2 = 1;
        break;
    case 0:
    case 1:
    case 3:
    case 4:
    case 9:
        ip->x40_vel.x = attrs->x1C * -ip->xCD0;
        it_802723FC(gobj);
        ip->xDD4_itemVar.gshell.xDEC_b2 = 1;
        if (ip->ground_or_air == GA_Air) {
            it_8028C898(gobj);
        } else {
            it_8028C3A8(gobj);
        }
        break;
    default:
        break;
    }
    it_802756D0(gobj);
    ip->xDD4_itemVar.gshell.xDEC_b1 = 1;
    it_8027570C(gobj, 0);
}

void itGShell_Logic14_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.gshell.xDD4 = attrs->x0;
    it_80275174(gobj, ip->xDD4_itemVar.gshell.xDD4);
    ip->xDD4_itemVar.gshell.xDE8 = 1;
    ip->xDD4_itemVar.gshell.xDEC_b0 = 0;
    ip->xDD4_itemVar.gshell.xDEC_b1 = 0;
    ip->xDD4_itemVar.gshell.xDE0 = attrs->x28;
    ip->xDD4_itemVar.gshell.xDEC_b3 = 0;
    ip->xDD4_itemVar.gshell.xDE4 = attrs->x2C;
    ip->xDD4_itemVar.gshell.xDEC_b2 = 1;
    it_8028C018(gobj);
}

void it_8028BE54(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    it_8026B390(gobj);
    it_80275444(gobj);
    it_802754D4(gobj);
    it_802756E0(gobj);
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->xDD4_itemVar.gshell.xDEC_b3 = 0;
    it_80274CAC(gobj);
    ip->jumped_on = it_8028CF68;
}

bool itGshell_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itGshell_UnkMotion0_Phys(Item_GObj* gobj)
{
    return;
}

bool itGshell_UnkMotion0_Coll(Item_GObj* gobj)
{
    itGShell_Attrs* attrs;
    Item* ip;
    HSD_JObj* jobj;
    it_8026D62C(gobj, it_8028C018);
    ip = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->ground_or_air == GA_Ground) {
        it_80276CB8(gobj);
        jobj = HSD_JObjGetChild(jobj);
        HSD_JObjAddRotationY(jobj, attrs->x20 * ABS(ip->x40_vel.x));
    }
    return false;
}

void it_8028C018(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_80274C88(gobj);
}

bool itGshell_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.gshell.xDEC_b3 && ip->xDD0_flag.b0 != 1) {
        if (ip->xDD4_itemVar.gshell.xDE4 <= 0.0f) {
            it_80274CAC(gobj);
            ip->jumped_on = it_8028CF68;
        } else {
            ip->xDD4_itemVar.gshell.xDE4 -= 1;
        }
    }
    return false;
}

void itGshell_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itGshell_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.gshell.xDE8 != 0) {
        it_8026E32C(gobj, it_8028BE54);
    } else {
        return it_8026DF34(gobj);
    }
    return false;
}

void itGShell_Logic14_PickedUp(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80275474(gobj);
    ip->xDD4_itemVar.gshell.xDEC_b3 = 0;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itGshell_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itGshell_UnkMotion2_Phys(Item_GObj* gobj)
{
    return;
}

void itGShell_Logic14_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.gshell.xDE8 = 1;
    Item_80268E5C(gobj, 3, 6);
    Item_8026AE84(ip, 242, 127, 64);
}

bool itGshell_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.gshell.xDEC_b1) {
        ip->xDD4_itemVar.gshell.xDE0 -= 1.0f;
        if (ip->xDD4_itemVar.gshell.xDE0 <= 0.0f) {
            ip->xDD4_itemVar.gshell.xDEC_b1 = 0;
            ip->xDD4_itemVar.gshell.xDE0 = attrs->x28;
            it_8027572C(gobj, 0);
            if (ip->xDD4_itemVar.gshell.xDEC_b2) {
                it_802756E0(gobj);
            }
        }
    }
    return false;
}

void itGshell_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itGshell_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028BA2C);
    return false;
}

void itGShell_Logic14_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

#pragma push
#pragma dont_inline on
bool itGshell_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_8028B988(gobj);
    return false;
}
#pragma pop

void itGshell_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itGshell_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028BA2C);
    return false;
}

void it_8028C3A8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    it_8026B3A8(gobj);
    it_80275474(gobj);
    it_80275414(gobj);
    it_80275158(gobj, it_804D6D28->x30);
    ip->xD5C = 0;
    ip->xDD4_itemVar.gshell.xDD8 = attrs->x24;
    ip->xDD4_itemVar.gshell.xDDC = attrs->x30;
    ip->xDD4_itemVar.gshell.xDEC_b3 = 0;
    if (ABS(ip->x40_vel.x) > attrs->x4) {
        int dir;
        if (ip->x40_vel.x < 0) {
            dir = -1;
        } else {
            dir = 1;
        }
        ip->x40_vel.x = dir;
        ip->x40_vel.x *= attrs->x4;
    }
    it_80272980(gobj);
    if (ABS(ip->x40_vel.x) < attrs->x8) {
        Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
        it_8026B390(gobj);
        it_802754D4(gobj);
    } else {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
    it_80274CAC(gobj);
    ip->jumped_on = it_8028CF68;
}

bool itGshell_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.gshell.xDD8 <= 0.0f) {
        if (!ip->xDCD_flag.b5) {
            it_80275444(gobj);
        }
    } else {
        ip->xDD4_itemVar.gshell.xDD8 -= 1.0f;
    }
    it_8028B988(gobj); // inlined
    if (ip->msid == 6 || ip->msid == 5) {
        it_8028B8D8(gobj); // inlined
    }
    if (ip->xDD4_itemVar.gshell.xDD4 <= 0.0f) {
        return true;
    }
    ip->xDD4_itemVar.gshell.xDD4 -= 1.0f;
    return false;
}

void itGshell_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ABS(ip->x40_vel.x) < attrs->x8 && !ip->xDC8_word.flags.x15) {
        it_8026B390(gobj);
        it_802725D4(gobj);
        it_802754D4(gobj);
    }
}

bool itGshell_UnkMotion6_Coll(Item_GObj* gobj)
{
    itGShell_Attrs* attrs;
    Item* ip;
    HSD_JObj* jobj;
    PAD_STACK(8);
    it_8026D62C(gobj, it_8028C898);
    ip = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->ground_or_air == GA_Ground) {
        it_80276CB8(gobj);
        jobj = HSD_JObjGetChild(jobj);
        HSD_JObjAddRotationY(jobj, attrs->x20 * ABS(ip->x40_vel.x));
    }
    if (it_8027770C(gobj)) {
        it_80272980(gobj);
    }
    return false;
}

void it_8028C898(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    it_8026B3A8(gobj);
    it_80275474(gobj);
    it_80275414(gobj);
    it_80275158(gobj, it_804D6D28->x30);
    ip->xD5C = 0;
    ip->xDD4_itemVar.gshell.xDD8 = attrs->x24;
    ip->xDD4_itemVar.gshell.xDDC = attrs->x30;
    ip->xDD4_itemVar.gshell.xDEC_b3 = 0;
    if (ABS(ip->x40_vel.x) > attrs->x4) {
        int dir;
        if (ip->x40_vel.x < 0) {
            dir = -1;
        } else {
            dir = 1;
        }
        ip->x40_vel.x = dir;
        ip->x40_vel.x *= attrs->x4;
    }
    it_80272980(gobj);
    if (ABS(ip->x40_vel.x) < attrs->x8) {
        Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
        it_8026B390(gobj);
    } else {
        Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
    }
    it_80274CAC(gobj);
    ip->jumped_on = it_8028CF68;
}

#pragma push
#pragma dont_inline on
bool itGshell_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data; // GET_ITEM(gobj);
    if (ip->xDD4_itemVar.gshell.xDD8 <= 0.0f) {
        if (!ip->xDCD_flag.b5) {
            it_80275444(gobj);
        }
    } else {
        ip->xDD4_itemVar.gshell.xDD8 -= 1.0f;
    }
    it_8028B988(gobj);
    if (ip->msid == 6 || ip->msid == 5) {
        it_8028B8D8(gobj);
    }
    if (ip->xDD4_itemVar.gshell.xDD4 <= 0.0f) {
        ;
    } else {
        ip->xDD4_itemVar.gshell.xDD4 -= 1.0f;
    }
    return false;
}
#pragma pop

void itGshell_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itGshell_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028BA2C);
    return false;
}

void itGShell_Logic14_EnteredAir(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDC8_word.flags.x1F = 1;
    ip->xDD4_itemVar.gshell.xDEC_b3 = 0;
    Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
}

bool itGshell_UnkMotion9_Anim(Item_GObj* gobj)
{
    return false;
}

void itGshell_UnkMotion9_Phys(Item_GObj* gobj)
{
    return;
}

bool itGshell_UnkMotion9_Coll(Item_GObj* gobj)
{
    itGShell_Attrs* attrs;
    Item* ip;
    HSD_JObj* jobj;
    PAD_STACK(8);
    it_8026E8C4(gobj, it_8028BE54, it_8028C018);
    ip = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->ground_or_air == GA_Ground) {
        it_80276CB8(gobj);
        jobj = HSD_JObjGetChild(jobj);
        HSD_JObjAddRotationY(jobj, attrs->x20 * ABS(ip->x40_vel.x));
    }
    return false;
}

bool itGShell_Logic14_DmgDealt(Item_GObj* gobj)
{
    it_80272940(gobj);
    return false;
}

bool itGShell_Logic14_DmgReceived(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_80272940(gobj);
    it_8028BAD8(gobj);
    return false;
}

bool itGShell_Logic14_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80273030(gobj);
    ip->xDD4_itemVar.gshell.xDD4 = ip->xD48_halfLifeTimer;
    return false;
}

bool itGShell_Logic14_Clanked(Item_GObj* gobj)
{
    itGShell_Attrs* attrs;
    Item* ip = GET_ITEM(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(8);
    it_802756D0(gobj);
    it_80275444(gobj);
    ip->x40_vel.x = -ip->x40_vel.x * attrs->xC * HSD_Randf();
    ip->x40_vel.y = attrs->x10;
    if (ip->xDD4_itemVar.gshell.xDEC_b0) {
        ip->xDD4_itemVar.gshell.xDE8 = HSD_Randi(it_804D6D28->x48_byte & 0xF);
    } else {
        ip->xDD4_itemVar.gshell.xDEC_b0 = 1;
    }
    it_802762BC(ip);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_80274C88(gobj);
    ip->xDD4_itemVar.gshell.xDEC_b3 = 1;
    ip->xDD4_itemVar.gshell.xDE4 = attrs->x2C;
    return false;
}

bool itGShell_Logic14_HitShield(Item_GObj* gobj)
{
    itGShell_Attrs* attrs;
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffVictim(gobj);
    } else if (ip->msid - 5u <= 3) {
        attrs = ip->xC4_article_data->x4_specialAttributes;
        it_802756D0(gobj);
        it_80275444(gobj);
        ip->x40_vel.x = -ip->x40_vel.x * attrs->xC * HSD_Randf();
        ip->x40_vel.y = attrs->x10;
        if (ip->xDD4_itemVar.gshell.xDEC_b0) {
            ip->xDD4_itemVar.gshell.xDE8 =
                HSD_Randi(it_804D6D28->x48_byte & 0xF);
        } else {
            ip->xDD4_itemVar.gshell.xDEC_b0 = 1;
        }
        it_802762BC(ip);
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        it_80274C88(gobj);
        ip->xDD4_itemVar.gshell.xDEC_b3 = 1;
        ip->xDD4_itemVar.gshell.xDE4 = attrs->x2C;
    }
    return false;
}

bool itGShell_Logic14_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffShield(gobj);
    }
    return false;
}

bool it_8028CF68(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80272940(gobj);
    it_8028BC2C(gobj);
    Item_8026AE84(ip, 241, 127, 64);
    return false;
}

void itGShell_Logic14_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
