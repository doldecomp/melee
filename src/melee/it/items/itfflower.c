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

HSD_GObj* it_80292D48(Vec3* arg0)
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

    PAD_STACK(4);

    ip->xD4C = *(s32*) ip->xC4_article_data->x4_specialAttributes;
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

void it_80292EAC(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    enum_t msid = ip->msid;

    if (msid == 5 || msid >= 5 || msid == 2 || msid < 2) {
        return;
    } else {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
}

void it_80292EF8(void* arg1)
{
    M2C_FIELD(arg1, f32*, 0) = it_804DCB00;
    M2C_FIELD(arg1, f32*, 4) = it_804DCB08;
    M2C_FIELD(arg1, f32*, 8) = it_804DCB0C;
}

void it_80292F14(void* arg0, s32 arg1, f32 arg8)
{
    s32 temp_r4;
    u32 temp_r3;
    void* temp_r31;

    temp_r31 = M2C_FIELD(arg0, void**, 0x2C);
    if (M2C_FIELD(temp_r31, s32*, 0xD4C) > 0) {
        if (M2C_FIELD(temp_r31, u32*, 0xDD8) == 0) {
            efSync_Spawn(
                0x473, arg0,
                M2C_FIELD(M2C_FIELD(temp_r31, void**, 0xBBC), s32*, 0x10));
            M2C_FIELD(temp_r31, u32*, 0xDD8) = 1;
        }
        M2C_FIELD(temp_r31, s32*, 0xD4C) =
            M2C_ERROR(/* unknown instruction: subi $r0, $r3, 0x1 */);
        it_802996D0(M2C_FIELD(temp_r31, s32*, 0x518), arg1,
                    M2C_FIELD(temp_r31, u32*, 0xAC4), arg8);
        M2C_FIELD(temp_r31, s32*, 0xDD4) =
            M2C_FIELD(temp_r31, s32*, 0xDD4) + 1;
        temp_r4 = M2C_FIELD(temp_r31, s32*, 0xDD4);
        temp_r3 = temp_r4;
        // temp_r3 = MULT_HI(
        //     M2C_ERROR(/* unknown instruction: subi $r0, $r3, 0x5555 */),
        //     temp_r4);
        M2C_FIELD(temp_r31, s32*, 0xDD4) =
            temp_r4 - ((temp_r3 + (temp_r3 >> 0x1F)) * 6);
        if (M2C_FIELD(temp_r31, s32*, 0xDD4) == 0) {
            M2C_FIELD(temp_r31, u32*, 0xAC4) = Item_8026AE60();
        }
    }
}

void it_80292FF0(Item_GObj* arg0)
{
    Item* temp_r4;

    temp_r4 = arg0->user_data;
    temp_r4->x40_vel.z = it_804DCB00;
    temp_r4->x40_vel.y = it_804DCB00;
    temp_r4->x40_vel.x = it_804DCB00;
    it_8026B390(arg0);
    Item_80268E5C(arg0, 0, ITEM_ANIM_UPDATE);
}

bool it_80293040(HSD_GObj* arg0)
{
    s32 temp_r0;
    s32 temp_r31_2;
    void* temp_r31;

    temp_r31 = arg0->user_data;
    temp_r0 = M2C_FIELD(temp_r31, s32*, 0x24);
    if (temp_r0 != 4) {
        if (temp_r0 < 4) {
            if (temp_r0 < 0) {
            } else {
                goto block_5;
            }
        } else if (temp_r0 < 8) {
        block_5:
            efLib_DestroyAll(arg0);
            M2C_FIELD(temp_r31, s32*, 0xDD8) = 0;
        }
    } else if (M2C_FIELD(temp_r31, s32*, 0xD4C) <= 0) {
        efLib_DestroyAll(arg0);
        M2C_FIELD(temp_r31, s32*, 0xDD8) = 0;
    }
    temp_r31_2 = (M2C_FIELD(temp_r31, u8*, 0xDC8) >> 5) & 1;
    if (it_80272C6C(arg0) == 0) {
        Item_80268E5C(arg0, 0, ITEM_ANIM_UPDATE);
        if (temp_r31_2 != 0) {
            it_80274F10(arg0);
            it_8026BE28(arg0);
        }
    }
    return 0;
}

void it_8029310C(Item_GObj* gobj) {}

bool it_80293110(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8029313C);
    return false;
}

void it_8029313C(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_80293164(HSD_GObj* arg0)
{
    s32 temp_r0;
    void* temp_r31;

    temp_r31 = arg0->user_data;
    temp_r0 = M2C_FIELD(temp_r31, s32*, 0x24);
    if (temp_r0 != 4) {
        if (temp_r0 < 4) {
            if (temp_r0 < 0) {
            } else {
                goto block_5;
            }
        } else if (temp_r0 < 8) {
        block_5:
            efLib_DestroyAll(arg0);
            M2C_FIELD(temp_r31, s32*, 0xDD8) = 0;
        }
    } else if (M2C_FIELD(temp_r31, s32*, 0xD4C) <= 0) {
        efLib_DestroyAll(arg0);
        M2C_FIELD(temp_r31, s32*, 0xDD8) = 0;
    }
    if (it_80272C6C(arg0) == 0) {
        Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
    }
    return 0;
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
        return 0;
    }
    return it_8026DF34();
}

void it_80293284(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_802932AC(HSD_GObj* arg0)
{
    s32 temp_r0;
    s32 temp_r0_2;
    void* temp_r31;

    temp_r31 = arg0->user_data;
    temp_r0 = M2C_FIELD(temp_r31, s32*, 0x24);
    if (temp_r0 != 4) {
        if (temp_r0 < 4) {
            if (temp_r0 < 0) {
            } else {
                goto block_5;
            }
        } else if (temp_r0 < 8) {
        block_5:
            efLib_DestroyAll(arg0);
            M2C_FIELD(temp_r31, s32*, 0xDD8) = 0;
        }
    } else if (M2C_FIELD(temp_r31, s32*, 0xD4C) <= 0) {
        efLib_DestroyAll(arg0);
        M2C_FIELD(temp_r31, s32*, 0xDD8) = 0;
    }
    temp_r0_2 = M2C_FIELD(temp_r31, s32*, 0x24);
    switch (temp_r0_2) { /* irregular */
    case 2:
        if (it_80272C6C(arg0) == 0) {
            Item_80268E5C(arg0, 2, ITEM_ANIM_UPDATE);
        }
        break;
    default:
        if (it_80272C6C(arg0) == 0) {
            Item_80268E5C(arg0, 4, ITEM_ANIM_UPDATE);
        }
        break;
    case 5:
        if (it_80272C6C(arg0) == 0) {
            Item_80268E5C(arg0, 2, ITEM_ANIM_UPDATE);
        }
        break;
    }
    return 0;
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

bool it_8029355C(HSD_GObj* arg0)
{
    s32 temp_r0;
    void* temp_r31;

    temp_r31 = arg0->user_data;
    temp_r0 = M2C_FIELD(temp_r31, s32*, 0x24);
    if (temp_r0 != 4) {
        if (temp_r0 < 4) {
            if (temp_r0 < 0) {
            } else {
                goto block_5;
            }
        } else if (temp_r0 < 8) {
        block_5:
            efLib_DestroyAll(arg0);
            M2C_FIELD(temp_r31, s32*, 0xDD8) = 0;
        }
    } else if (M2C_FIELD(temp_r31, s32*, 0xD4C) <= 0) {
        efLib_DestroyAll(arg0);
        M2C_FIELD(temp_r31, s32*, 0xDD8) = 0;
    }
    if (it_80272C6C(arg0) == 0) {
        Item_80268E5C(arg0, 7, ITEM_ANIM_UPDATE);
    }
    return 0;
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
