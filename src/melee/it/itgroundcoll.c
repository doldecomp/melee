#include "it/itgroundcoll.h"

#include "inlines.h"

#include "it/it_2725.h"
#include "it/it_3F14.h"
#include "it/item.h"
#include "it/itmaplib.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <math.h>
#include <baselib/random.h>

bool it_8026D564(Item_GObj* item_gobj)
{
    bool test;
    Item* ip = GET_ITEM(item_gobj);
    CollData* coll = &ip->x378_itemColl;
    PAD_STACK(4);

    it_80276214(item_gobj);
    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;
    if (test) {
        ip->xC30 = coll->floor.index;
    }
    return test;
}

bool it_8026D5CC(Item_GObj* item_gobj)
{
    Item* ip = GET_ITEM(item_gobj);
    CollData* coll = &ip->x378_itemColl;

    it_80276214(item_gobj);
    return mpColl_8004B108(coll);
}

bool it_8026D604(Item_GObj* item_gobj)
{
    Item* ip = GET_ITEM(item_gobj);

    return mpLib_80054ED8(ip->xC30);
}

void it_8026D62C(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (test != false) {
        ip->xC30 = (u32) coll->floor.index;
    }
    if (test == false) {
        it_802762BC(ip);
        arg1(gobj);
        return;
    }
    if ((it_80277544(gobj) != 0) && !ip->xDCD_flag.b3) {
        Item_8026ADC0(gobj);
    }
}

void it_8026D6F4(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (test != false) {
        ip->xC30 = coll->floor.index;
    }
    if (test == false) {
        arg1(gobj);
    }
}

void it_8026D78C(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (test != false) {
        ip->xC30 = coll->floor.index;
    }
    if (test == false) {
        arg1(gobj);
        it_802762BC(ip);
    }
}

void it_8026D82C(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(5 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_8004B108(coll);
    ip->pos = coll->cur_pos;

    if (test) {
        ip->xC30 = coll->floor.index;
    }
    if (!test) {
        it_802762BC(ip);
    }
}

bool it_8026D8A4(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    bool test;
    PAD_STACK(8 * 4);

    it_80276214(gobj);

    {
        CollData* coll;
        Item* ip = GET_ITEM(gobj);
        coll = &ip->x378_itemColl;

        it_80276214(gobj);

        test = mpColl_8004B2DC(coll);
        ip->pos = coll->cur_pos;

        if (test != false) {
            ip->xC30 = coll->floor.index;
        }
    }
    if (it_802762D8(gobj) != false) {
        arg1(gobj);
    }
    return test;
}

void it_8026D938(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    Item* ip = GET_ITEM(gobj);
    if (mpLib_80054ED8(ip->xC30) == false) {
        ip->xC30 = -1;
        arg1(gobj);
    }
}

bool it_8026D9A0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    CollData* coll_data = &item->x378_itemColl;
    it_80276214(gobj);
    {
        u8 _[4];
        bool temp = mpColl_800477E0(coll_data);
        item->pos = coll_data->cur_pos;
        if (temp) {
            item->xC30 = coll_data->floor.index;
        }
        return temp;
    }
}

bool it_8026DA08(Item_GObj* gobj)
{
    Item* ip;
    CollData* coll;
    bool test;
    PAD_STACK(3 * 4);

    ip = gobj->user_data;
    coll = &ip->x378_itemColl;

    it_80276214(gobj);

    test = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;

    if (test) {
        ip->xC30 = coll->floor.index;
    }
    return test;
}

bool it_8026DA70(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    CollData* coll = &item->x378_itemColl;

    it_80276214(gobj);
    return mpColl_800471F8(coll);
}

s32 it_8026DAA8(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    s32 test;
    PAD_STACK(12);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);

    test = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (test != 0) {
        ip->xC30 = coll->floor.index;
    }
    test |= it_80276308(gobj);
    test |= it_802763E0(gobj);
    return test;
}

bool it_8026DB40(Item_GObj* gobj)
{
    CollData* coll;
    Item* ip;
    bool test;
    PAD_STACK(12);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);

    test = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (test != false) {
        ip->xC30 = coll->floor.index;
    }
    return test |= it_80276308(gobj);
}

bool it_8026DBC8(Item_GObj* gobj)
{
    if (it_8026DDFC(gobj) && it_8026DC24(gobj)) {
        it_802725D4(gobj);
        return it_8026DD5C(gobj);
    }
    return false;
}

bool it_8026DC24(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attr = ip->xCC_item_attr;

    if (ip->xD50_landNum <= 1) {
        it_80274658(gobj, it_804D6D28->x74_float);
        it_80275DFC(gobj);
    }
    if (ABS(ip->x40_vel.x) <= 0.00001f) {
        ip->x40_vel.x = 0.0f;
    }
    if (ABS(ip->x40_vel.y) <= 0.00001f) {
        ip->x40_vel.y = 0.0f;
    }
    if (ABS(ip->x40_vel.x) <= attr->x5c) {
        if ((ABS(ip->x40_vel.y) <= attr->x5c)) {
            goto block_18a8;
        }
    }
    if (ip->xDCD_flag.b4 || !attr->x58) {
    block_18a8:
        itResetVelocity(ip);
        return true;
    }
    return false;
}

bool it_8026DD5C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xD50_landNum = 0;
    it_802762B0(ip);
    if (!it_80277040(gobj) || ip->xDCD_flag.b3) {
        it_80274740(gobj);
        it_80276CEC(gobj);
    } else {
        if (ip->xB8_itemLogicTable->entered_air != NULL) {
            Item_8026ADC0(gobj);
            return false;
        }
        it_802734B4(gobj);
    }
    return true;
}

bool it_8026DDFC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    ip->xD50_landNum += 1;
    if (ip->xD50_landNum == 1) {
        if (ip->xD54_throwNum != 0) {
            u8* tmp = &it_804D6D28->x48_byte;
            if ((ip->xD54_throwNum == ((*tmp >> 4) & 0xF)) ||
                (HSD_Randi(*tmp & 0xF) == 0))
            {
                ip->destroy_type = 1;
                Item_8026A8EC(gobj);
                return false;
            }
        }
    }
    return true;
}

bool it_8026DE98(Item_GObj* gobj)
{
    return it_8026DDFC(gobj);
}

bool it_8026DF34(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(12);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
    if (cond) {
        return true;
    }
    return false;
}

bool it_8026DFB0(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(26);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
    cond |= it_80276308(gobj);
    cond |= it_802763E0(gobj);
    if (cond & 0xF) {
        return true;
    }
    return false;
}

bool it_8026E058(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(26);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
    cond |= it_80276308(gobj);
    if (cond & 0xD) {
        return true;
    }
    return false;
}

void it_8026E0F4(Item_GObj* gobj)
{
    bool cond;
    CollData* coll;
    Item* ip;
    PAD_STACK(16);

    ip = GET_ITEM(gobj);
    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800477E0(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
}

inline bool it_8026E_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    bool cond;
    CollData* coll;
    bool cond2;
    PAD_STACK(24);

    coll = &ip->x378_itemColl;
    it_80276214(gobj);
    cond = mpColl_800471F8(coll);
    ip->pos = coll->cur_pos;
    if (cond) {
        ip->xC30 = coll->floor.index;
    }
    cond2 = cond;
    cond2 |= it_80276308(gobj);
    cond2 |= it_802763E0(gobj);
    cond = cond2;
    return cond;
}

bool it_8026E15C_inline1(Item_GObj* gobj)
{
    return it_8026DDFC(gobj);
}
bool it_8026E15C_inline2(Item_GObj* gobj)
{
    return it_8026DD5C(gobj);
}

void it_8026E15C(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    bool res2;
    bool res = it_8026E_inline(gobj);
    u8 _[22];

    if (res & 0xF) {
        it_80276FC4(gobj, res);
        if (res & 1) {
            if (it_8026E15C_inline1(gobj) && it_8026DC24(gobj)) {
                it_802725D4(gobj);
                res2 = it_8026E15C_inline2(gobj);
            } else {
                res2 = false;
            }
            if (res2 != false) {
                arg1(gobj);
            }
        }
    }
}

bool it_8026E248_inline(Item_GObj* gobj)
{
    return it_8026DD5C(gobj);
}

// lol
static bool it_8026DE98_outline(Item_GObj* gobj)
{
    return it_8026DE98(gobj);
}

static bool it_8026DE98_outline2(Item_GObj* gobj)
{
    return it_8026DE98_outline(gobj);
}

static bool it_8026DE98_outline3(Item_GObj* gobj)
{
    return it_8026DE98_outline2(gobj);
}

static bool it_8026DE98_outline4(Item_GObj* gobj)
{
    return it_8026DE98_outline3(gobj);
}

void it_8026E248(Item_GObj* gobj, HSD_GObjEvent arg1)
{
    bool res2;
    bool res = it_8026E_inline(gobj);
    PAD_STACK(18);

    if (res & 0xF) {
        it_80276FC4(gobj, res);
        if (res & 1) {
            if (it_8026DE98_outline4(gobj) && it_8026DC24(gobj)) {
                res2 = it_8026E248_inline(gobj);
            } else {
                res2 = false;
            }
            if (res2 != false) {
                arg1(gobj);
            }
        }
    }
}

bool it_8026E32C_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xD50_landNum += 1;
    if (it_8026DC24(gobj)) {
        return it_8026DD5C(gobj);
    }
    return false;
}

s32 it_8026E32C(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    bool res = it_8026E_inline(item_gobj);
    PAD_STACK(32);

    if (res & 0xF) {
        it_80276FC4(item_gobj, res);
        if (res & 1) {
            if (it_8026E32C_inline(item_gobj)) {
                arg1(item_gobj);
            }
        }
    }
    return res;
}

void it_8026E414(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool new_var;
    PAD_STACK(28);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    new_var = chk;
    if (new_var & 0xE) {
        it_80276FC4(item_gobj, new_var);
    }
    if (new_var & 1) {
        it_80275DFC(item_gobj);
        it_802762B0(item);
        arg1(item_gobj);
    }
}

void it_8026E4D0(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    HSD_JObj* item_jobj;
    Item* item;
    bool chk;
    bool new_var;
    PAD_STACK(34);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    new_var = chk;
    if (new_var & 0xE) {
        it_80276FC4(item_gobj, new_var);
    }
    if (new_var & 1) {
        item_jobj = item_gobj->hsd_obj;
        it_80275DFC(item_gobj);
        it_802762B0(item);
        arg1(item_gobj);
        it_80272F7C(item_jobj, item->xCC_item_attr->x60_scale);
    }
}

void it_8026E5A0(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool new_val;
    PAD_STACK(28);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    new_val = chk;
    if (new_val & 0xF) {
        if (new_val & 0xE) {
            it_80276FC4(item_gobj, new_val);
        }
        if (new_val & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item);
        }
        arg1(item_gobj);
    }
}

void it_8026E664(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool new_var;

    PAD_STACK(28);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    new_var = chk;
    if (new_var & 0xD) {
        if (new_var & 0xC) {
            it_80276FC4(item_gobj, new_var);
        }
        if (new_var & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item);
        }
        arg1(item_gobj);
    }
}

void it_8026E71C(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool new_var;
    PAD_STACK(28);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    new_var = chk;
    if (new_var & 0xF) {
        if (new_var & 0xC) {
            it_80276D9C(item_gobj, new_var);
        }
        if (new_var & 1) {
            it_80275DFC(item_gobj);
            it_802762B0(item);
        }
        arg1(item_gobj);
    }
}

#pragma push
#pragma dont_inline on
void it_8026E7E0(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    CollData* coll;
    Item* item;
    bool chk;
    bool chk2;
    bool new_var;
    PAD_STACK(30);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_800471F8(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    chk = chk | it_80276308(item_gobj);
    chk = chk | it_802763E0(item_gobj);
    new_var = chk;
    if (new_var & 0xC) {
        it_80276D9C(item_gobj, new_var);
    }
    if (new_var & 1) {
        if (it_8026DE98(item_gobj) && it_8026DC24(item_gobj)) {
            new_var = it_8026DD5C(item_gobj);
        } else {
            new_var = false;
        }
        if (new_var) {
            arg1(item_gobj);
        }
    }
}
#pragma pop

void it_8026E8C4(Item_GObj* item_gobj, HSD_GObjEvent arg1, HSD_GObjEvent arg2)
{
    CollData* coll;
    Item* item;
    bool chk;
    PAD_STACK(14);

    item = item_gobj->user_data;
    coll = &item->x378_itemColl;
    it_80276214(item_gobj);
    chk = mpColl_8004B108(coll);
    item->pos = coll->cur_pos;
    if (chk) {
        item->xC30 = coll->floor.index;
    }
    if (chk == false) {
        it_802762BC(item);
        arg2(item_gobj);
        return;
    }
    it_80277040(item_gobj);
    if (it_80276308(item_gobj)) {
        item->xD5C = 0;
    }
    if (!(item->xDC8_word.flags.x1F & 1) || (item->xD5C == 0U)) {
        it_80276CEC(item_gobj);
        arg1(item_gobj);
    }
}

bool it_8026E9A4(HSD_GObj* gobj, Vec3* arg1, Vec3* arg2, Vec3* arg3)
{
    u8 _[4];
    Vec3 p;
    PAD_STACK(4);

    if (mpCheckAllRemap(&p, NULL, NULL, arg3, -1, -1, arg1->x, arg1->y,
                        arg2->x, arg2->y) == true)
    {
        *arg2 = p;
        return true;
    }
    return false;
}

bool it_8026EA20(HSD_GObj* gobj, Vec3* arg1, Vec3* arg2, Vec3* arg3, int* arg4,
                 u32* flags_out)
{
    UNUSED int _;
    Vec3 p;
    PAD_STACK(4);

    if (mpCheckAllRemap(&p, arg4, flags_out, arg3, -1, -1, arg1->x, arg1->y,
                        arg2->x, arg2->y) == true)
    {
        *arg2 = p;
        return true;
    }
    return false;
}

bool it_8026EA9C(HSD_GObj* gobj, Vec3* arg1, Vec3* arg2, Vec3* arg3, int* arg4,
                 u32* flags_out, s32 arg6)
{
    Vec3 p;
    PAD_STACK(4);

    if (mpCheckAllRemap(&p, arg4, flags_out, arg3, -1, arg6, arg1->x, arg1->y,
                        arg2->x, arg2->y) == true)
    {
        *arg2 = p;
        return true;
    }
    return false;
}
