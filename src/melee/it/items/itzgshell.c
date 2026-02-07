#include "itzgshell.h"

#include "baselib/jobj.h"
#include "ef/efasync.h"
#include "gr/grzakogenerator.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "MSL/math.h"

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

typedef struct itZGShell_Attrs {
    char pad0[0x38];
    float x38;
    Vec x3C;
} itZGShell_Attrs;

/* 2DFFA0 */ static void it_802DFFA0(Item_GObj* gobj);

void it_802DDB38(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itZGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    Vec v;
    HSD_JObj* jobj;
    PAD_STACK(4);
    if (ip->xDD4_itemVar.zgshell.xDF8 <= 0.0f) {
        jobj = GET_JOBJ(gobj);
        v = attrs->x3C;
        v.x *= -ip->facing_dir;
        efAsync_Spawn(gobj, &GET_ITEM(gobj)->xBC0, 2, 1029, jobj, &v);
        ip->xDD4_itemVar.zgshell.xDF8 = attrs->x38;
    } else {
        ip->xDD4_itemVar.zgshell.xDF8 -= 1.0f;
    }
}

void it_802DDBE8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.zgshell.xE08_b0) {
        ip->xDD4_itemVar.zgshell.xDFC -= 1.0f;
        if (ip->xDD4_itemVar.zgshell.xDFC <= 0.0f) {
            ip->xDD4_itemVar.zgshell.xE08_b0 = 0;
            ip->xDD4_itemVar.zgshell.xDFC = attrs->x28;
            it_8027572C(gobj, 0);
            if (ip->xDD4_itemVar.zgshell.xE08_b1) {
                it_802756E0(gobj);
            }
        }
    }
}

void fn_802DDC8C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_80275D5C(gobj, &ip->xC0C);
    if (ABS(ip->x40_vel.x) < attrs->x8) {
        ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
        if (!it_80277040(gobj)) {
            it_802DE0F0(gobj);
        } else {
            it_2725_Logic11_EnteredAir(gobj);
        }
    } else {
        it_802DE6F0(gobj);
    }
}

/// #it_802DDD38

/// #it_802DDEB4

/// #it_802DE040

/// #it_802DE0F0

bool itZrshell_UnkMotion0_Anim(Item_GObj* arg0)
{
    return false;
}

/// #itZrshell_UnkMotion0_Phys

bool itZrshell_UnkMotion0_Coll(Item_GObj* gobj)
{
    itGShell_Attrs* attrs;
    Item* ip;
    HSD_JObj* jobj;
    it_8026D62C(gobj, it_802DE320);
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

void it_802DE320(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 1, ITEM_ANIM_UPDATE);
    it_80274C88(gobj);
}

bool itZrshell_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->xDD4_itemVar.zgshell.xE1C_b0 && ip->xDD0_flag.b0 != 1) {
        if (ip->xDD4_itemVar.zgshell.xE04 <= 0.0f) {
            it_80274CAC(gobj);
            ip->jumped_on = fn_802DFE7C;
        } else {
            ip->xDD4_itemVar.zgshell.xE04 -= 1;
        }
    }
    return false;
}

void itZrshell_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itZrshell_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E32C(gobj, it_802DE0F0);
    return false;
}

/// #it_2725_Logic11_PickedUp

bool itZrshell_UnkMotion2_Anim(Item_GObj* arg0)
{
    return false;
}

/// #itZrshell_UnkMotion2_Phys

void itZGShell_Logic11_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
    Item_8026AE84(ip, 0xF2, 0x7FU, 0x40U);
}

bool itZrshell_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    itGShell_Attrs* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (ip->xDD4_itemVar.zgshell.xE08_b0) {
        ip->xDD4_itemVar.zgshell.xDFC -= 1.0f;
        if (ip->xDD4_itemVar.zgshell.xDFC <= 0.0f) {
            ip->xDD4_itemVar.zgshell.xE08_b0 = 0;
            ip->xDD4_itemVar.zgshell.xDFC = attrs->x28;
            it_8027572C(gobj, 0);
            if (ip->xDD4_itemVar.zgshell.xE08_b1) {
                it_802756E0(gobj);
            }
        }
    }
    return false;
}

void itZrshell_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itZrshell_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, fn_802DDC8C);
    return false;
}

void itZGShell_Logic11_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

#pragma dont_inline on
bool itZrshell_UnkMotion4_Anim(Item_GObj* gobj)
{
    it_802DDBE8(gobj);
    return false;
}
#pragma dont_inline reset

void itZrshell_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itZrshell_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, fn_802DDC8C);
    return false;
}

/// #it_802DE6F0

/// #itZrshell_UnkMotion6_Anim

/// #itZrshell_UnkMotion6_Phys

bool itZrshell_UnkMotion6_Coll(Item_GObj* gobj)
{
    itGShell_Attrs* attrs;
    Item* ip;
    HSD_JObj* jobj;
    PAD_STACK(8);
    it_8026D62C(gobj, it_802DEC80);
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

/// #it_802DEC80

#pragma dont_inline on
bool itZrshell_UnkMotion8_Anim(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->xDD4_itemVar.zgshell.xDF4 <= 0.0f) {
        if (!ip->xDCD_flag.b5) {
            it_80275444(gobj);
        }
    } else {
        ip->xDD4_itemVar.zgshell.xDF4 -= 1.0f;
    }
    it_802DDBE8(gobj);
    if (ip->msid == 6 || ip->msid == 5) {
        it_802DDB38(gobj);
    }
    return false;
}
#pragma dont_inline reset

void itZrshell_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itZrshell_UnkMotion8_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, fn_802DDC8C);
    return false;
}

/// #it_2725_Logic11_EnteredAir

bool itZrshell_UnkMotion9_Anim(Item_GObj* arg0)
{
    return false;
}

/// #itZrshell_UnkMotion9_Phys

bool itZrshell_UnkMotion9_Coll(Item_GObj* gobj)
{
    itGShell_Attrs* attrs;
    Item* ip;
    HSD_JObj* jobj;
    PAD_STACK(8);
    it_8026E8C4(gobj, it_802DE0F0, it_802DE320);
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

/// #it_802DF230

/// #itZrshell_UnkMotion11_Anim

void itZrshell_UnkMotion11_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->x40_vel.y > 0.0f) {
        it_802762BC(ip);
    }
}

/// #itZrshell_UnkMotion11_Coll

/// #it_802DF9F8

/// #itZrshell_UnkMotion10_Anim

void itZrshell_UnkMotion10_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

/// #itZrshell_UnkMotion10_Coll

bool itZGShell_Logic11_DmgDealt(Item_GObj* gobj)
{
    it_80272940(gobj);
    return false;
}

bool itZGShell_Logic11_DmgReceived(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_80272940(gobj);
    it_802DDD38(gobj);
    return false;
}

bool itZGShell_Logic11_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_2725_Logic11_Clanked

/// #it_2725_Logic11_HitShield

bool itZGShell_Logic11_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffShield(gobj);
    }
    return false;
}

int fn_802DFE7C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80272940(gobj);
    it_802DDEB4(gobj);
    Item_8026AE84(ip, 0xF1, 0x7FU, 0x40U);
    return 0;
}

void it_802DFED4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void itZGShell_Logic11_Destroyed(Item_GObj* gobj)
{
    grZakoGenerator_801CACB8((Ground_GObj*) gobj);
}

/// #it_802DFF14

void it_802DFFA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.zgshell.vel.x = 0.0f;
    ip->xDD4_itemVar.zgshell.vel.y = 0.0f;
    ip->xDD4_itemVar.zgshell.vel.z = 0.0F;
}

void it_802DFFB8(HSD_JObj* jobj, Item* ip)
{
    Vec3 vec;
    Vec3 vec2;
    if (jobj != NULL) {
        vec.x = vec.y = vec.z = 0.0F;
        HSD_JObjGetTranslation(jobj, &vec2);
        ip->x40_vel.x =
            ip->facing_dir * (vec2.z - ip->xDD4_itemVar.zgshell.vel.z);
        ip->x40_vel.y = vec2.y - ip->xDD4_itemVar.zgshell.vel.y;
        ip->x40_vel.z = vec2.x - ip->xDD4_itemVar.zgshell.vel.x;
        ip->xDD4_itemVar.zgshell.vel = vec2;
        HSD_JObjSetTranslate(jobj, &vec);
    }
}

/// #it_802E0100
