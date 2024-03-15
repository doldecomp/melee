#include "it/forward.h"

#include "itcoin.h"

#include "cm/camera.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A36.h"
#include "gr/grfigureget.h"
#include "gr/ground.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "ty/tydisplay.h"

#include <baselib/gobj.h>
#include <baselib/gobjobject.h>
#include <baselib/jobj.h>

/* 2F1588 */ static void it_802F1588(Item_GObj* gobj);
/* 2F15B0 */ static bool it_802F15B0(Item_GObj* gobj);
/* 2F15B8 */ static void it_802F15B8(Item_GObj* gobj);
/* 2F1604 */ static bool it_802F1604(Item_GObj* gobj);
/* 2F1630 */ static void it_802F1630(Item_GObj* gobj);
/* 2F1850 */ static bool it_802F1850(Item_GObj* gobj);
/* 2F1858 */ static void it_802F1858(Item_GObj* gobj);
/* 2F185C */ static bool it_802F185C(Item_GObj* gobj);
/* 2F18E4 */ static bool it_802F18E4(Item_GObj* gobj);
/* 2F18EC */ static void it_802F18EC(Item_GObj* gobj);
/* 2F1C68 */ static bool it_802F1C68(Item_GObj* gobj);
/* 2F1C70 */ static void it_802F1C70(Item_GObj* gobj);
/* 2F1CB4 */ static bool it_802F1CB4(Item_GObj* gobj);
/* 2F1EE4 */ static bool it_802F1EE4(Item_GObj* gobj);
/* 2F1EEC */ static void it_802F1EEC(Item_GObj* gobj);
/* 2F1F1C */ static bool it_802F1F1C(Item_GObj* gobj);
/* 2F1FD4 */ static bool it_802F1FD4(Item_GObj* gobj);
/* 2F1FDC */ static void it_802F1FDC(Item_GObj* gobj);
/* 2F1FE0 */ static bool it_802F1FE0(Item_GObj* gobj);

ItemStateTable it_803F93C8[] = {
    { -1, it_802F15B0, it_802F15B8, it_802F1604 },
    { -1, it_802F1850, it_802F1858, it_802F185C },
    { -1, it_802F18E4, it_802F18EC, NULL },
    { -1, it_802F1C68, it_802F1C70, it_802F1CB4 },
    { -1, it_802F1EE4, it_802F1EEC, it_802F1F1C },
    { -1, it_802F1FD4, it_802F1FDC, it_802F1FE0 },
};

void it_802F13B4(Item_GObj* gobj, int arg1)
{
    Item* ip = GET_ITEM(gobj);
    itCoinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(gobj)->child;

    if (ip->xDD4_itemVar.coin.x4 != 0) {
        if (((gm_801A45E8(1) != false) &&
             (grFigureGet_80219C50(ip->xDD4_itemVar.coin.x14) == 0)) ||
            ((Camera_80031144() < attr->x48) &&
             (grFigureGet_80219C50(ip->xDD4_itemVar.coin.x14) == 0)))
        {
            HSD_JObjSetFlagsAll(jobj, 0x10);
            HSD_JObjClearFlagsAll(jobj->next, 0x10);
        } else {
            HSD_JObjSetFlagsAll(jobj->next, 0x10);
            HSD_JObjClearFlagsAll(jobj, 0x10);
        }
    } else if (((gm_801A45E8(1) != 0) && (Ground_801C1D84() == 0)) ||
               (Camera_80031144() < attr->x48))
    {
        HSD_JObjSetFlagsAll(jobj, 0x10);
        HSD_JObjClearFlagsAll(jobj->next, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj->next, 0x10);
        HSD_JObjClearFlagsAll(jobj, 0x10);
    }
    it_8026EECC(gobj, arg1);
}

void it_802F14E4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xDD4_itemVar.coin.x4 = 0;
    ip->xDD4_itemVar.coin.x0 = 0;
    ip->xDD4_itemVar.coin.x10 = 0;
    it_802F1588(gobj);
}

void it_802F1518(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.coin.x4 != 0) {
        grFigureGet_80219C34(ip->xDD4_itemVar.coin.x14);
    } else if (ip->xDC8_word.flags.x13 != false) {
        gm_8017E280(ip->xDD4_itemVar.coin.x0, 1);
        it_8027CE44(gobj);
    }
    it_8027C8B0(gobj);
}

void it_802F1588(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_UNK_0x1);
}

bool it_802F15B0(Item_GObj* gobj)
{
    return false;
}

void it_802F15B8(Item_GObj* gobj)
{
    ItemAttr* attr;
    Item* ip = GET_ITEM(gobj);

    if (ip->xDD4_itemVar.coin.x4 == 0) {
        attr = ip->xCC_item_attr;
        it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
        return;
    }
    it_80272860(gobj, ip->xDD4_itemVar.coin.x8, ip->xDD4_itemVar.coin.xC);
}

bool it_802F1604(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802F1630);
    return false;
}

void it_802F1630(Item_GObj* gobj)
{
    Item* ip;
    HSD_JObj* jobj;

    PAD_STACK(16);

    ip = GET_ITEM(gobj);
    ip->x40_vel.z = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->x40_vel.x = 0.0F;
    jobj = GET_JOBJ(gobj);

    HSD_JObjSetRotationX(jobj, 0.0F);
    HSD_JObjSetRotationY(jobj, 0.0F);
    HSD_JObjSetRotationZ(jobj, 0.0F);

    Item_80268E5C(gobj, 1, ITEM_UNK_0x1);
    it_802756D0(gobj);
}

bool it_802F1850(Item_GObj* gobj)
{
    return false;
}

void it_802F1858(Item_GObj* gobj) {}

bool it_802F185C(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802F1588);
    return false;
}

void it_802F1888(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);

    HSD_JObjClearFlagsAll(child, 0x10);
    Item_80268E5C(gobj, 2, ITEM_UNK_0x1);
}

bool it_802F18E4(Item_GObj* gobj)
{
    return false;
}

void it_802F18EC(Item_GObj* gobj) {}

void it_802F18F0(Item_GObj* gobj, Item_GObj* ref)
{
    it_8026B894(gobj, ref);
}

bool it_802F1910(Item_GObj* gobj)
{
    Item* ip;
    itCoinAttributes* attr;

    PAD_STACK(20);

    ip = GET_ITEM(gobj);
    attr = ip->xC4_article_data->x4_specialAttributes;
    it_802762BC(ip);
    ip->xC9C = ip->xC9C + it_8027CBFC(gobj);
    it_8027B798(gobj, &ip->x40_vel);
    if ((ip->x40_vel.x == 0.0F) && (ip->x40_vel.y == 0.0F)) {
        ip->x40_vel.x = 0.1F * -ip->xCCC_incDamageDirection;
        ip->x40_vel.y = 0.1F;
    }
    lbVector_Normalize(&ip->x40_vel);
    if ((ip->pos.x > 0.0F) && (-1 == ip->xCCC_incDamageDirection)) {
        ip->x40_vel.x *= -1;
    }
    if ((ip->pos.x < 0.0F) && (1 == ip->xCCC_incDamageDirection)) {
        ip->x40_vel.x *= -1;
    }
    if (ip->pos.x > 0.0F) {
        if (ip->xCCC_incDamageDirection == -1) {
            ip->x40_vel.x *= attr->x30 * (attr->x24 + ip->xC9C);
        } else {
            ip->x40_vel.x *= attr->x2C * (attr->x24 + ip->xC9C);
        }
        if (ip->x40_vel.x <= -attr->x3C) {
            ip->x40_vel.x = -attr->x3C;
        }
    } else {
        if (-1 == ip->xCCC_incDamageDirection) {
            ip->x40_vel.x *= attr->x2C * (attr->x24 + ip->xC9C);
        } else {
            ip->x40_vel.x *= attr->x30 * (attr->x24 + ip->xC9C);
        }
        if (ip->x40_vel.x >= attr->x3C) {
            ip->x40_vel.x = attr->x3C;
        }
    }
    ip->x40_vel.y *= attr->x38 * (attr->x28 + ip->xC9C);
    if (ip->x40_vel.y >= attr->x40) {
        ip->x40_vel.y = attr->x40;
    }
    ip->x40_vel.z = 0.0F;
    ip->xC9C = 0;
    switch (ip->xDD4_itemVar.coin.x4) {
    case 2:
        ip->xDD4_itemVar.coin.x8 += attr->x14;
        break;
    case 3:
        ip->xDD4_itemVar.coin.x8 += attr->x20;
        break;
    default:
        ip->xDD4_itemVar.coin.x8 += attr->x8;
        break;
    }
    Item_80268E5C(gobj, 3, ITEM_UNK_0x1);
    return false;
}

bool it_802F1C68(Item_GObj* gobj)
{
    return false;
}

void it_802F1C70(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itCoinAttributes* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->x40_vel.x *= attr->x34;
    it_80272860(gobj, ip->xDD4_itemVar.coin.x8, ip->xDD4_itemVar.coin.xC);
}

bool it_802F1CB4(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802F1630);
    return false;
}

void it_802F1CE0(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    PAD_STACK(24);

    HSD_JObjSetRotationX(jobj, 0.0F);
    HSD_JObjSetRotationY(jobj, 0.0F);
    HSD_JObjSetRotationZ(jobj, 0.0F);

    Item_80268E5C(gobj, 4, ITEM_UNK_0x1);
}

bool it_802F1EE4(Item_GObj* gobj)
{
    return false;
}

void it_802F1EEC(Item_GObj* gobj)
{
    ItemAttr* attr = GET_ITEM(gobj)->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_802F1F1C(Item_GObj* gobj)
{
    it_8026E414(gobj, it_802F1630);
    return false;
}

void it_802F1F48(Item_GObj* gobj)
{
    Item* ip;
    f32 item_dir;
    int coll_dir;

    ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);

    if (ip->x40_vel.x + ip->x7C + ip->x88 >= 0.0F) {
        item_dir = 1;
    } else {
        item_dir = -1;
    }

    ip->facing_dir = item_dir;
    if (ip->facing_dir == -1) {
        coll_dir = -1;
    } else {
        coll_dir = 1;
    }
    mpColl_800436D8(&ip->x378_itemColl, coll_dir);
}

bool it_802F1FD4(Item_GObj* gobj)
{
    return false;
}

void it_802F1FDC(Item_GObj* gobj) {}

bool it_802F1FE0(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802F1630, it_802F1588);
    return false;
}

void it_802F2014(Item_GObj* gobj, int arg1)
{
    GET_ITEM(gobj)->x378_itemColl.x4C = arg1;
}

int it_802F2020(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    return ip->xDD4_itemVar.coin.x0;
}

void it_802F202C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    lbAudioAx_800237A8(0xAA, 0x7F, 0x40);
    ip->x40_vel.x = 0.0F;
    if (ip->x40_vel.y < -1.5F) {
        ip->x40_vel.y = -1.5F;
    }
    it_802756D0(gobj);
}

Item_GObj* it_802F2094(int arg0, Vec3* pos, int arg2, int arg3)
{
    SpawnItem spawn;
    Item_GObj* gobj;
    itCoinAttributes* attr;
    Item* ip;
    void* var_r29;

    spawn.kind = It_Kind_Coin;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = 0.0F;
    spawn.vel.z = 0.0F;
    spawn.vel.y = 0.0F;
    spawn.vel.x = 0.0F;
    spawn.x3C_damage = 0;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = NULL;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0.0F;

    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        attr = ip->xC4_article_data->x4_specialAttributes;
        ip->xDD4_itemVar.coin.x0 = arg2;
        ip->xDD4_itemVar.coin.x4 = arg3;
        ip->xDD4_itemVar.coin.x14 = arg0;
        if (ip->xDD4_itemVar.coin.x4 != 0) {
            it_802756E0(gobj);
            it_8026B3A8(gobj);
            switch (arg3) {
            case 2:
                ip->xDD4_itemVar.coin.x8 = attr->xC;
                ip->xDD4_itemVar.coin.xC = attr->x10;
                break;
            case 3:
                ip->xDD4_itemVar.coin.x8 = attr->x18;
                ip->xDD4_itemVar.coin.xC = attr->x1C;
                break;
            default:
                ip->xDD4_itemVar.coin.x8 = attr->x0;
                ip->xDD4_itemVar.coin.xC = attr->x4;
                break;
            }
            var_r29 = un_8031C5E4(arg2);
        } else {
            Item_80267454(gobj);
            it_802756D0(gobj);
            it_8026B390(gobj);
            ip->xD5C = 0;
            var_r29 = un_8031C5E4(arg2);
        }
        HSD_GObjObject_80390B0C(gobj);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, var_r29);
        it_8027163C(gobj);
        ip->scl = Ground_801C0498();
        ip->scl *= attr->x44;

        HSD_JObjSetScaleX(gobj->hsd_obj, ip->scl);
        HSD_JObjSetScaleY(gobj->hsd_obj, ip->scl);
        HSD_JObjSetScaleZ(gobj->hsd_obj, ip->scl);
    }
    return gobj;
}
