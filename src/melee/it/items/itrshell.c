#include "itrshell.h"

#include "m2c_macros.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/jobj.h"
#include "ef/efasync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "MSL/math.h"
#include "it/itcoll.h"
#include "sysdolphin/baselib/random.h"

typedef struct itRShell_Attrs {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    Vec3 x14;
    float x20;
    float x24;
    float x28;
    float x2C;
    char pad30[0x38 - 0x30];
    float x38; // rotation multiplier (gshell x20)
    float x3C;
    char pad40[0x44 - 0x40];
    float x44;
    Vec x48;
    s32 x54;
} itRShell_Attrs;

void it_8028CFE0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itRShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    Vec v;
    HSD_JObj* jobj;
    PAD_STACK(4);
    if (ip->xDD4_itemVar.rshell.xDDC <= 0.0f) {
        jobj = GET_JOBJ(gobj);
        v = attrs->x48;
        v.x *= -ip->facing_dir;
        efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 2, 1029, jobj, &v);
        ip->xDD4_itemVar.rshell.xDDC = attrs->x44;
    } else {
        ip->xDD4_itemVar.rshell.xDDC -= 1.0f;
    }
}

void it_8028D090(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itRShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_80275D5C(gobj, &ip->xC0C);
    it_8028DAE4(gobj);
    ip->x40_vel.x = it_8028D56C(gobj, attrs->x4, ip->facing_dir);
    it_80272980(gobj);
}

void it_8028D100(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itRShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 kind = ip->msid;
    s32 did_hit = 0;
    f32 vel;

    if (kind < 5) {
        if (kind == 2) {
            goto check_speed;
        }
        if (kind >= 2) {
            goto set_vel;
        }
        if (kind >= 0) {
            goto set_vel;
        }
        goto check_speed;
    } else {
        if (kind == 7) {
            goto set_vel;
        }
        if (kind >= 7) {
            goto check_speed;
        }
        goto add_vel;
    }

set_vel:
    did_hit = 1;
    ip->x40_vel.x =
        -ip->xCCC_incDamageDirection * (ip->xCA0 * attrs->x20);
    goto check_speed;

add_vel:
    it_8028D390(gobj);
    ip->x40_vel.x +=
        -ip->xCCC_incDamageDirection * (ip->xCA0 * attrs->x24);
    goto check_speed;

check_speed:
    vel = ip->x40_vel.x;
    if (vel < 0.0f) {
        vel = -vel;
    }
    if (vel > attrs->x10) {
        it_8027236C(gobj);
        if (did_hit != 0) {
            it_802756D0(gobj);
        }
        if (ip->ground_or_air == GA_Air) {
            it_8028E170(gobj);
            return;
        }
        it_8028DAE4(gobj);
        return;
    }
    it_802725D4(gobj);
}

void it_8028D26C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itRShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    s32 kind = ip->msid;
    s32 did_hit = 0;
    f32 vel;

    if (kind < 5) {
        if (kind == 2) {
            goto check_speed;
        }
        if (kind >= 2) {
            goto set_vel;
        }
        if (kind >= 0) {
            goto set_vel;
        }
        goto check_speed;
    } else {
        if (kind == 7) {
            goto set_vel;
        }
        if (kind >= 7) {
            goto check_speed;
        }
        goto add_vel;
    }

set_vel:
    did_hit = 1;
    ip->x40_vel.x = attrs->x28 * -ip->xCD0;
    goto check_speed;

add_vel:
    it_8028D390(gobj);
    ip->x40_vel.x += attrs->x2C * -ip->xCD0;
    goto check_speed;

check_speed:
    vel = ip->x40_vel.x;
    if (vel < 0.0f) {
        vel = -vel;
    }
    if (vel > attrs->x10) {
        it_802723FC(gobj);
        if (did_hit != 0) {
            it_802756D0(gobj);
        }
        if (ip->ground_or_air == GA_Air) {
            it_8028E170(gobj);
            return;
        }
        it_8028DAE4(gobj);
        return;
    }
    it_802725D4(gobj);
}

s32 it_8028D390(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 dec = ip->xDD4_itemVar.rshell.xDEC;

    ip->xDD4_itemVar.rshell.xDEC = dec - 1;
    if (ip->xDD4_itemVar.rshell.xDEC == 0) {
        ip->xDD4_itemVar.rshell.xDF0 = 1;
    }
    return dec;
}

void it_8028D3B8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(0x10);

    ip->xDD4_itemVar.rshell.xDEC -= 1;
    if (ip->xDD4_itemVar.rshell.xDEC == 0) {
        ip->xDD4_itemVar.rshell.xDF0 = 1;
    }
    if (ip->xDD4_itemVar.rshell.xDF0 == 0) {
        it_802756E0(gobj);
        it_80275444(gobj);
        ip->x40_vel.x =
            it_8028D56C(gobj, ip->x40_vel.x, ip->xCB8_outDamageDirection);
        it_80272980(gobj);
        if (ip->xDD4_itemVar.rshell.xDF4_b0) {
            u8 rand_max = it_804D6D28->x48_byte;
            rand_max &= 0xF;
            ip->xDD4_itemVar.rshell.xDE8 = HSD_Randi(rand_max);
        } else {
            ip->xDD4_itemVar.rshell.xDF4_b0 = 1;
        }
        if (ip->msid != 6 && ip->msid != 5) {
            if (ip->ground_or_air == GA_Air) {
                it_8028E170(gobj);
                return;
            }
            it_8028DAE4(gobj);
        }
    }
}

void fn_8028D4A8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = -ip->x40_vel.x;
    ip->xDD4_itemVar.rshell.xDE0 = -ip->xDD4_itemVar.rshell.xDE0;
    it_80272980(gobj);
}

void it_8028D4E4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 vel;
    itRShell_Attrs* attrs;
    f32 abs_vel;

    vel = ip->x40_vel.x;
    attrs = ip->xC4_article_data->x4_specialAttributes;

    if (vel < 0.0f) {
        abs_vel = -vel;
    } else {
        abs_vel = vel;
    }

    if (abs_vel > attrs->xC) {
        s32 sign;
        if (vel < 0.0f) {
            sign = -1;
        } else {
            sign = 1;
        }
        ip->x40_vel.x = (f32) sign;
        ip->x40_vel.x *= attrs->xC;
    }
}

f32 it_8028D56C(Item_GObj* gobj, f32 f1, f32 f2)
{
    itRshellAttributes* attrs =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    f32 f = (f1 * -attrs->x14.x) + (-attrs->x14.y * f2);
    return f * attrs->x14.z;
}

void it_3F14_Logic15_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itRShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.rshell.xDD4 = attrs->x0;
    it_80275174(gobj, ip->xDD4_itemVar.rshell.xDD4);
    ip->xDD4_itemVar.rshell.xDEC = attrs->x54;
    ip->xDD4_itemVar.rshell.xDF0 = 0;
    ip->xDD4_itemVar.rshell.xDD8 = attrs->x3C;
    ip->xDD4_itemVar.rshell.xDE8 = 1;
    ip->xDD4_itemVar.rshell.xDF4_b0 = 0;
    ip->xDD4_itemVar.rshell.xDE0 = 0.0f;
    it_8028D7F0(gobj);
}

void it_8028D62C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itRShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8026B390(gobj);
    it_80275414(gobj);
    it_802756E0(gobj);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xDD4_itemVar.rshell.xDD8 = attrs->x3C;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_80274CAC(gobj);
    ip->jumped_on = it_8028E6C0;
}

bool itRshell_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itRshell_UnkMotion0_Coll(Item_GObj* gobj)
{
    itRShell_Attrs* attrs;
    Item* ip;
    HSD_JObj* jobj;
    it_8026D62C(gobj, it_8028D7F0);
    ip = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->ground_or_air == GA_Ground) {
        it_80276CB8(gobj);
        jobj = HSD_JObjGetChild(jobj);
        HSD_JObjAddRotationY(jobj, attrs->x38 * ABS(ip->x40_vel.x));
    }
    return false;
}

void it_8028D7F0(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itRshell_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itRshell_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.rshell.xDE8 != 0) {
        it_8026E32C(gobj, it_8028D62C);
    } else {
        return it_8026DF34(gobj);
    }
    return false;
}

void itRShell_Logic15_PickedUp(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_80275474(gobj);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itRshell_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic15_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itRShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.rshell.xDE8 = 1;
    ip->xDD4_itemVar.rshell.xDD8 = attrs->x3C;
    Item_80268E5C(gobj, 3, 6);
    Item_8026AE84(ip, 0xF2, 0x7F, 0x40);
}

bool itRshell_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.rshell.xDD8 <= 0.0f) {
        if (!ip->xDCD_flag.b5) {
            it_80275444(gobj);
        }
    } else {
        ip->xDD4_itemVar.rshell.xDD8 -= 1.0f;
    }
    return false;
}

void itRshell_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itRshell_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028D090);
    return false;
}

void it_3F14_Logic15_Dropped(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itRShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.rshell.xDD8 = attrs->x3C;
    Item_80268E5C(gobj, 4, 6);
}

bool itRshell_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.rshell.xDD8 <= 0.0f) {
        if (!ip->xDCD_flag.b5) {
            it_80275444(gobj);
        }
    } else {
        ip->xDD4_itemVar.rshell.xDD8 -= 1.0f;
    }
    return false;
}

void itRshell_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itRshell_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028D090);
    return false;
}

/// #it_8028DAE4

/// #itRshell_UnkMotion5_Anim

/// #itRshell_UnkMotion5_Phys

/// #itRshell_UnkMotion5_Coll

/// #it_8028E170

#pragma push
#pragma dont_inline on
bool itRshell_UnkMotion6_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (!(ip->xDD4_itemVar.rshell.xDD4 <= 0.0f)) {
        ip->xDD4_itemVar.rshell.xDD4 -= 1.0f;
        if (ip->xDD4_itemVar.rshell.xDD8 <= 0.0f) {
            if (!ip->xDCD_flag.b5) {
                it_80275444(gobj);
            }
        } else {
            ip->xDD4_itemVar.rshell.xDD8 -= 1.0f;
        }
        if (ip->msid == 5) {
            it_8028CFE0(gobj);
        }
    }
    return false;
}
#pragma pop

void itRshell_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itRshell_UnkMotion6_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028D090);
    return false;
}

void it_3F14_Logic15_EnteredAir(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDC8_word.flags.x1F = 1;
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool itRshell_UnkMotion7_Anim(Item_GObj* gobj)
{
    return false;
}

void itRshell_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itRshell_UnkMotion7_Coll(Item_GObj* gobj)
{
    itRShell_Attrs* attrs;
    Item* ip;
    HSD_JObj* jobj;
    PAD_STACK(8);
    it_8026E8C4(gobj, it_8028D62C, it_8028D7F0);
    ip = GET_ITEM(gobj);
    jobj = GET_JOBJ(gobj);
    attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->ground_or_air == GA_Ground) {
        it_80276CB8(gobj);
        jobj = HSD_JObjGetChild(jobj);
        HSD_JObjAddRotationY(jobj, attrs->x38 * ABS(ip->x40_vel.x));
    }
    return false;
}

bool it_3F14_Logic15_DmgDealt(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    it_80272940(gobj);
    it_8028D3B8(gobj);
    return ip->xDD4_itemVar.rshell.xDF0;
}

bool it_3F14_Logic15_DmgReceived(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    it_80272940(gobj);
    it_8028D100(gobj);
    return ip->xDD4_itemVar.rshell.xDF0;
}

bool itRShell_Logic15_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80273030(gobj);
    ip->xDD4_itemVar.rshell.xDD4 = ip->xD48_halfLifeTimer;
    return false;
}

bool itRShell_Logic15_Clanked(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_3F14_Logic15_HitShield(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    s32 kind = ip->msid;
    if (kind == 3) {
        goto bounce;
    }
    if (kind != 4) {
        goto check_other;
    }
bounce:
    itColl_BounceOffVictim(gobj);
    goto out;
check_other:
    if ((u32) (kind - 5) <= 1U) {
        it_8028D3B8(gobj);
        return ip->xDD4_itemVar.rshell.xDF0;
    }
out:
    return false;
}

bool itRShell_Logic15_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffShield(gobj);
    }
    return false;
}

bool it_8028E6C0(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    it_80272940(gobj);
    it_8028D26C(gobj);
    Item_8026AE84(ip, 0xF1, 0x7F, 0x40);
    return ip->xDD4_itemVar.rshell.xDF0;
}

void itRShell_Logic15_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
