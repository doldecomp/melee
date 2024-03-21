#include "itfflower.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/gobj.h>

const f32 it_804DCB00 = 0.0F;
const f32 it_804DCB04 = -1.0F;
const f32 it_804DCB08 = 5.5F;
const f32 it_804DCB0C = 2.5F;

void it_80292FF0(Item_GObj*); /* static */
void it_8029313C(Item_GObj*); /* static */

M2C_UNK it_802996D0(s32, s32, u32, f32); /* extern */

static inline void msid_check(enum_t msid, Item_GObj* gobj, Item* ip)
{
    if (msid != 4) {
        if (msid < 4) {
            if (msid >= 0) {
                goto block_5;
            }
        } else if (msid < 8) {
        block_5:
            efLib_DestroyAll(gobj);
            ip->xDD4_itemVar.fflower.x4 = 0;
        }
    } else if (ip->xD4C <= 0) {
        efLib_DestroyAll(gobj);
        ip->xDD4_itemVar.fflower.x4 = 0;
    }
}

Item_GObj* it_80292D48(Vec3* arg0)
{
    u8 sp50;
    s32 sp4C;
    s16 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    s32 sp14;
    Item_GObj* sp10;
    SpawnItem* spC;
    Item_GObj* temp_r3;
    f32 temp_r0;
    f32 temp_r6;

    sp14 = 0x19;
    temp_r6 = arg0->x;
    temp_r0 = arg0->y;
    sp2C = temp_r6;
    sp30 = temp_r0;
    sp34 = arg0->z;
    sp34 = it_804DCB00;
    sp20 = temp_r6;
    sp24 = temp_r0;
    sp28 = sp34;
    sp44 = it_804DCB04;
    sp48 = 0;
    sp40 = it_804DCB00;
    sp3C = it_804DCB00;
    sp38 = it_804DCB00;
    spC = 0;
    // sp10 = spC;
    // sp50 |= 0x80;
    sp4C = 0;
    temp_r3 = Item_80268B18(spC);
    if (temp_r3 != NULL) {
        it_80292FF0(temp_r3);
    }
    return temp_r3;
}

void it_80292E04(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    FFlowerVars* attr = ip->xC4_article_data->x4_specialAttributes;

    ip->xD4C = attr->x0;
    ip->xAC4_ignoreItemID = Item_8026AE60();
    ip->xDD4_itemVar.capsule.x0 = 0;
    ip->xDD4_itemVar.capsule.x4 = 0;
    it_8029313C(gobj);
}

void it_80292E64(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    enum_t msid = ip->msid;

    if (msid != 5 && (msid >= 5 || msid != 2)) {
        return;
    } else {
        Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    }
}

void it_80292EAC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    enum_t msid = ip->msid;

    if (msid == 5 || msid >= 5 || msid == 2 || msid < 2) {
        return;
    } else {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
}

void it_80292EF8(Vec3* vec)
{
    vec->x = it_804DCB00;
    vec->y = it_804DCB08;
    vec->z = it_804DCB0C;
}

void it_80292F14(Item_GObj* gobj, s32 arg1, f32 arg8)
{
    s32 temp_r4;
    u32 temp_r3;
    Item* ip = GET_ITEM(gobj);

    if (ip->xD4C > 0) {
        if (ip->xDD4_itemVar.fflower.x4 == 0) {
            efSync_Spawn(0x473, gobj, ip->xBBC_dynamicBoneTable->bones[4]);
            ip->xDD4_itemVar.fflower.x4 = 1;
        }
        ip->xD4C -= 1;

        it_802996D0(*(s32*) &ip->owner, arg1, ip->xAC4_ignoreItemID, arg8);

        temp_r3 = ip->xDD4_itemVar.fflower.x0;
        ip->xDD4_itemVar.fflower.x0 = (0x2aab0000 - 0x5555);
        temp_r4 = temp_r3 + 1;
        temp_r3 = ip->xDD4_itemVar.fflower.x0;

        ip->xDD4_itemVar.fflower.x0 =
            temp_r4 - ((temp_r3 + (temp_r3 >> 0x1F)) * 6);
        if (ip->xDD4_itemVar.fflower.x0 == 0) {
            ip->xAC4_ignoreItemID = Item_8026AE60();
        }
    }
}

void it_80292FF0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->x40_vel.z = it_804DCB00;
    ip->x40_vel.y = it_804DCB00;
    ip->x40_vel.x = it_804DCB00;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_80293040(Item_GObj* gobj)
{
    s32 temp_r31_2;
    Item* ip = GET_ITEM(gobj);
    s32 msid = ip->msid;

    PAD_STACK(4);

    msid_check(msid, gobj, ip);

    temp_r31_2 = ip->xDC8_word.flags.x2;
    if (it_80272C6C(gobj) == false) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        if (temp_r31_2 != 0) {
            it_80274F10(gobj);
            it_8026BE28(gobj);
        }
    }
    return false;
}

void it_8029310C(Item_GObj* gobj) {}

bool it_80293110(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8029313C);
    return false;
}

void it_8029313C(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_80293164(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    enum_t msid = ip->msid;

    msid_check(msid, gobj, ip);

    if (it_80272C6C(gobj) == false) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    }
    return false;
}

void it_80293210(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_80293240(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xD4C != 0) {
        it_8026E15C(gobj, it_80292FF0);
        return false;
    }
    return it_8026DF34();
}

void it_80293284(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_802932AC(Item_GObj* gobj)
{
    enum_t msid2;
    Item* ip = GET_ITEM(gobj);
    enum_t msid = ip->msid;

    msid_check(msid, gobj, ip);

    msid2 = ip->msid;

    switch (msid2) {
    case 2:
        if (it_80272C6C(gobj) == false) {
            Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
        }
        break;
    case 5:
        if (it_80272C6C(gobj) == false) {
            Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        }
        break;
    default:
        if (it_80272C6C(gobj) == false) {
            Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
        }
        break;
    }

    return false;
}

void it_802933C0(Item_GObj* gobj) {}

void it_802933C4(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

void it_802933EC(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

void it_80293414(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_80293444(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xD4C != 0) {
        it_8026E15C(gobj, it_80292FF0);
        return 0;
    }
    return it_8026DF34();
}

bool it_80293488(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802934AC(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802934D0(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802934F4(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_80293514(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_80293534(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

bool it_8029355C(Item_GObj* gobj)
{
    enum_t msid;
    Item* ip;

    ip = GET_ITEM(gobj);
    msid = ip->msid;

    msid_check(msid, gobj, ip);

    if (it_80272C6C(gobj) == false) {
        Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
    }
    return false;
}

void it_80293608(Item_GObj* gobj) {}

bool it_8029360C(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80292FF0, it_8029313C);
    return false;
}

void it_80293640(Item_GObj* gobj, Item_GObj* ref)
{
    it_8026B894(gobj, ref);
}

ItemStateTable it_803F6090[] = {
    { 0, it_80293040, it_8029310C, it_80293110 },
    { 0, it_80293164, it_80293210, it_80293240 },
    { 0, it_802932AC, it_802933C0, NULL },
    { 1, it_802932AC, it_802933C0, NULL },
    { 2, it_802932AC, it_802933C0, NULL },
    { 3, it_802932AC, it_802933C0, NULL },
    { 4, it_80293164, it_80293414, it_80293444 },
    { 0, it_8029355C, it_80293608, it_8029360C },
};
