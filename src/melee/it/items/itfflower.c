#include "itfflower.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/gobj.h>

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

Item_GObj* it_80292D48(Vec3* vec)
{
    Item_GObj* gobj;
    SpawnItem spawn;

    spawn.kind = It_Kind_F_Flower;
    spawn.prev_pos = *vec;
    spawn.prev_pos.z = -1.0F;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = 0.0F;
    spawn.x3C_damage = 0;
    spawn.vel.z = -1.0F;
    spawn.vel.y = -1.0F;
    spawn.vel.x = -1.0F;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0.0F;

    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        it_80292FF0(gobj);
    }
    return gobj;
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
    vec->x = 0.0F;
    vec->y = 5.5F;
    vec->z = 2.5F;
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

    ip->x40_vel.z = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->x40_vel.x = 0.0F;
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
