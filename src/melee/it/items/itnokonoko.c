#include "it/items/itnokonoko.h"

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itzgshell.h"
#include "it/items/itzrshell.h"
#include "mp/mpcoll.h"

ItemStateTable it_803F85F0[] = {
    { 0, NULL, NULL, NULL },
    { -1, it_802DC910, it_802DC918, it_802DC954 },
    { 1, it_802DCA5C, it_802DCAA4, it_802DCB34 },
    { 2, it_802DD328, it_802DD468, it_802DD46C },
    { 1, it_802DCC58, it_802DCC60, it_802DCC90 },
    { 3, it_802DD0A0, it_802DD1B4, it_802DD1DC },
    { 3, it_802DD25C, it_802DD264, it_802DCC90 },
    { 4, it_802DCD54, it_802DCD9C, it_802DCDC4 },
    { 4, it_802DCD54, it_802DCE74, it_802DCDC4 },
    { 4, it_802DD53C, it_802DD598, NULL },
    { 5, it_802DD6D4, it_802DD71C, it_802DD74C },
};

void static inline coll_inline(Item* ip)
{
    mpColl_800436D8(&ip->x378_itemColl, (ip->facing_dir == -1.0f) ? -1 : 1);
}

void it_802DC69C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027B730(gobj);
    it_8027C56C(gobj, ip->facing_dir);
    coll_inline(ip);
    ip->xD5C = 0;

    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDC8_word.flags.x19 = 1;
    ip->xDD4_itemVar.nokonoko.x28 = 0;
    ip->xDD4_itemVar.nokonoko.x40 = 0;
    ip->xDD4_itemVar.nokonoko.x20 = 0;
    ip->xDD4_itemVar.nokonoko.x74 = ip->xC1C;
    it_802DCB9C(gobj);
}

static void zero_pad(Item* ip)
{
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
}

bool it_802DC774(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itNokoNoko_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    PAD_STACK(4);
    ip->init_facing_dir = ip->facing_dir;
    ip->xC9C = (s32) ((f32) ip->xC9C + it_8027CBFC(gobj));
    if (ip->msid == 0xA) {
        it_802DD78C(gobj);
    } else if (ip->xC9C > da->x0->x0) {
        it_802DCFBC(gobj);
    } else {
        it_802DCCCC(gobj);
    }
    return 0;
}

bool it_802DC83C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->init_facing_dir = ip->facing_dir;
    it_80274C88(gobj);
    it_802DCFBC(gobj);
    Camera_80030E44(2, &ip->pos);
    Item_8026AE84(ip, 0x12E, 0x7F, 0x40);
    ftLib_80086D40(ip->xCFC, 0xC, 0);
    return 0;
}

void fn_802DC8B8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CAD8(gobj);
    it_8027C0A8(gobj, ip->facing_dir, 5.0f);
    it_802DD4A8(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_802DC910(Item_GObj* gobj)
{
    return 0;
}

void it_802DC918(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.nokonoko.x28 <= 0) {
        it_802DC990(gobj);
        return;
    }
    ip->xDD4_itemVar.nokonoko.x28 -= 1;
}

int it_802DC954(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802DCB9C);
    return it_8027C794(gobj);
}

void it_802DC990(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itNokoNoko_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = ip->facing_dir * da->x0->x4;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    coll_inline(ip);
    it_802756E0(gobj);
    if ((s32) ip->xDD4_itemVar.nokonoko.x20 == 0) {
        ip->xDD4_itemVar.nokonoko.x20 = (s32) (da->x8 / da->x0->x4);
    }
    it_802DD4A8(gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_802DCA5C(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (it_80272C6C(gobj) == 0) {
        it_802DD4A8(gobj, 2, 0x12);
    }
    return 0;
}

void it_802DCAA4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.nokonoko.x20 == 0) {
        it_802DD290(gobj);
    } else {
        ip->xDD4_itemVar.nokonoko.x20 -= 1;
    }
    if (it_802750E8(gobj, 2) != 0) {
        it_802DD290(gobj);
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, ip->facing_dir, 5.0f);
}

int it_802DCB34(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (it_8026D8A4(gobj, it_802DD290) != 0) {
        if (it_80276308(gobj) != 0) {
            it_802DD290(gobj);
        }
    } else {
        it_802DCB9C(gobj);
    }
    return it_8027C794(gobj);
}

void it_802DCB9C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itNokoNoko_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x *= da->x4;
    ip->xDD4_itemVar.nokonoko.x28 = 0.0f;
    if (((ip->facing_dir > 0.0f) && (ip->x70_nudge.x < 0.0f)) ||
        ((ip->facing_dir < 0.0f) && (ip->x70_nudge.x > 0.0f)))
    {
        s32 var_r4;
        ip->facing_dir = -ip->facing_dir;
        coll_inline(ip);
    }
    it_802DD4A8(gobj, 4, ITEM_ANIM_UPDATE);
}

bool it_802DCC58(Item_GObj* gobj)
{
    return 0;
}

void it_802DCC60(Item_GObj* gobj)
{
    ItemAttr* temp_r4 = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_802DCC90(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, (void (*)(HSD_GObj*)) fn_802DC8B8);
    return it_8027C794(gobj);
}

void it_802DCCCC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.nokonoko.x28 = 0.0f;
    it_80275474(gobj);
    it_8027B798(gobj, &ip->x40_vel);
    if (ip->x40_vel.y <= 0.2) {
        ip->x40_vel.y = 0.2;
    }
    it_802762BC(ip);
    ip->facing_dir = ip->init_facing_dir;
    it_802DD4A8(gobj, 7, ITEM_ANIM_UPDATE);
}

bool it_802DCD54(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (it_80272C6C(gobj) == 0) {
        it_802DD4A8(gobj, 7, ITEM_ANIM_UPDATE);
    }
    return 0;
}

void it_802DCD9C(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == 1) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

int it_802DCDC4(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, it_802DCEC4);
    return it_8027C794(gobj);
}

void it_802DCE00(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    ip->xDD4_itemVar.nokonoko.x28 = 10;
    it_802756D0(gobj);
    ip->xCC8_knockback = ip->xDD4_itemVar.nokonoko.x34;
    ip->xCAC_angle = ip->xDD4_itemVar.nokonoko.x3C;
    ip->xCCC_incDamageDirection = ip->xDD4_itemVar.nokonoko.x38;
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
}

void it_802DCE74(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    if (ip->xDD4_itemVar.nokonoko.x28 == 0) {
        it_802756E0(gobj);
        return;
    }
    ip->xDD4_itemVar.nokonoko.x28 -= 1;
}

void it_802DCEC4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.nokonoko.x28 = 0;
    it_802756E0(gobj);
    if (ip->xCCC_incDamageDirection == ip->facing_dir) {
        it_802DD2DC(gobj);
        return;
    }
    it_802DC990(gobj);
}

void it_802DCFBC(Item_GObj* gobj)
{
    ECB box;
    Item* ip = GET_ITEM(gobj);
    it_802756D0(gobj);
    if (it_8027B798(gobj, &ip->x40_vel) != 0) {
        it_802762BC(ip);
    } else {
        it_802762B0(ip);
    }
    ip->facing_dir = ip->init_facing_dir;
    coll_inline(ip);
    ip->xDD4_itemVar.nokonoko.x28 = 0.0f;
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    box = ip->xC1C;
    box.top = 4.5f;
    box.right = 3.0f;
    box.left = 3.0f;
    it_80275D5C(gobj, &box);
}

f32 static inline lt_zero(f32 val)
{
    if (val < 0.0f) {
        return -1.0f;
    } else {
        return 1.0f;
    }
}

bool it_802DD0A0(Item_GObj* gobj)
{
    Vec3 pos;
    f32 var_f2;
    Item_GObj* ip_2;
    Item* ip = GET_ITEM(gobj);
    if ((it_80272C6C(gobj) == 0) && ((s32) ip->ground_or_air == GA_Ground)) {
        HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
        var_f2 = lt_zero(57.29578f * HSD_JObjGetRotationY(jobj));
        pos = ip->pos;
        pos.y += 0.1f;
        if (ip->xDD4_itemVar.nokonoko.x40 < 2) {
            ip_2 = it_802E0100(ip->xDD4_itemVar.nokonoko.x40, &pos, var_f2);
        } else {
            ip_2 = it_802E0488(ip->xDD4_itemVar.nokonoko.x40, &pos, var_f2);
        }
        if (ip_2 != NULL) {
            GET_ITEM(ip_2)->xDD4_itemVar.nokonoko.x4 =
                ip->xDD4_itemVar.nokonoko.x4;
            ip->xDD4_itemVar.nokonoko.x4 = -1;
        }
        return 1;
    }
    return 0;
}

void it_802DD1B4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

int it_802DD1DC(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    PAD_STACK(12);
    if (ip->ground_or_air == GA_Air) {
        if (it_8026DB40(gobj) & 1) {
            it_802762B0(ip);
            ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
        }
    } else {
        it_8026D82C(gobj);
    }
    return it_8027C794(gobj);
}

int it_802DD25C(HSD_GObj* gobj)
{
    return 0;
}

void it_802DD264(Item_GObj* gobj)
{
    it_8027C0A8(gobj, GET_ITEM(gobj)->facing_dir, 0.0f);
}

void static inline it_802DD290_inline(Item_GObj* gobj, s32 val)
{
    Item* ip = gobj->user_data;
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    ip->xDD4_itemVar.nokonoko.x20 = 0;
    ip->xDD4_itemVar.nokonoko.x28 = 0x26;
    it_802DD4A8(gobj, 0x3, val);
}

void it_802DD290(Item_GObj* gobj)
{
    it_802DD290_inline(gobj, 0x12);
}

void it_802DD2DC(HSD_GObj* gobj)
{
    it_802DD290_inline(gobj, 2);
}

int it_802DD328(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.nokonoko.x28 == 0) {
        ip->facing_dir = -ip->facing_dir;
        coll_inline(ip);
    }
    ip->xDD4_itemVar.nokonoko.x28 -= 1;
    if (it_80272C6C(gobj) == 0) {
        Item* ip = GET_ITEM(gobj);
        it_8026D5CC(gobj);
        ip->xDD4_itemVar.nokonoko.x28 = 0.0f;
        it_802DC990(gobj);
    }
    return 0;
}

void it_802DD468(HSD_GObj* gobj) {}

int it_802DD46C(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802DCB9C);
    return it_8027C794(gobj);
}

void it_802DD4A8(HSD_GObj* gobj, s32 arg1, enum Item_StateChangeFlags arg2)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, arg1, arg2);
    it_80274CAC(gobj);
    ip->jumped_on = it_802DC83C;
}

void it_802DD4F4(Item_GObj* gobj)
{
    PAD_STACK(16);
    GET_ITEM(gobj)->xDD4_itemVar.nokonoko.x28 = 0.0f;
    it_80274740(gobj);
    Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
}

int it_802DD53C(Item_GObj* gobj)
{
    PAD_STACK(24);
    if (it_80272C6C(gobj) == 0) {
        it_802DD4F4(gobj);
    }
    return 0;
}

void it_802DD598(HSD_GObj* gobj) {}

static void it_802DD59C_inline(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itNokoNoko_DatAttrs* da = ip->xC4_article_data->x4_specialAttributes;
    f32 temp_f2;
    ip->x40_vel.x *= da->x4;
    ip->xDD4_itemVar.nokonoko.x28 = 0.0f;
    temp_f2 = ip->facing_dir;
    if (((temp_f2 > 0.0f) && (ip->x70_nudge.x < 0.0f)) ||
        ((temp_f2 < 0.0f) && (ip->x70_nudge.x > 0.0f)))
    {
        ip->facing_dir = -temp_f2;
        coll_inline(ip);
    }
    it_802DD4A8(gobj, 4, ITEM_ANIM_UPDATE);
}

void it_802DD59C(Item_GObj* gobj)
{
    it_8027CBA4(gobj);
    it_802DD59C_inline(gobj);
}

void it_802DD67C(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    it_8027CB3C(gobj);
    it_80274C88(gobj);
    ip->xDD4_itemVar.nokonoko.x28 = 0.0f;
    Item_80268E5C(gobj, 0xA, ITEM_ANIM_UPDATE);
}

int it_802DD6D4(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        Item_80268E5C(gobj, 0xA, ITEM_ANIM_UPDATE);
    }
    return 0;
}

void it_802DD71C(Item_GObj* gobj)
{
    ItemAttr* temp_r4 = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_802DD74C(Item_GObj* gobj)
{
    if (it_8026DAA8(gobj) & 0xF) {
        it_802DD78C(gobj);
    }
    return 0;
}

void it_802DD78C(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8027327C(gobj, 0x444, 0x130);
    it_8027CE44(gobj);
    Item_8026A8EC(gobj);
}

void it_802DD7D0(Item_GObj* gobj, HSD_GObj* arg1)
{
    it_8026B894(gobj, arg1);
}

Item_GObj* it_802DD7F0(s32 arg0, Vec3* arg1, Vec3* arg2, s32 arg3)
{
    Item_GObj* gobj = it_8027B5B0(0xD3, arg1, NULL, arg2, 1);
    f32 temp_f31;
    PAD_STACK(8);
    if (gobj != NULL) {
        HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
        Item* ip = GET_ITEM(gobj);
        ip->facing_dir = (f32) arg3;
        coll_inline(ip);
        temp_f31 = ip->facing_dir * 1.5707963267948966;
        HSD_JObjSetRotationY(jobj, temp_f31);
        ip->xDD4_itemVar.nokonoko.x40 = arg0;
        if (ip->xDD4_itemVar.nokonoko.x40 == 2) {
            Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
            HSD_JObjAnimAll(gobj->hsd_obj);
        }
        if (it_802DDA84(gobj) != 0) {
            it_802762B0(ip);
            fn_802DC8B8(gobj);
        } else {
            it_802762BC(ip);
            it_802DD59C_inline(gobj);
        }
    }
    return gobj;
}

int it_802DDA84(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    CollData* col = &ip->x378_itemColl;
    bool cond;
    ip->x378_itemColl.cur_topn = ip->pos;
    ip->x378_itemColl.prev_topn = ip->x378_itemColl.cur_topn;
    ip->x378_itemColl.prev_topn.y += 10.0f;
    ip->x378_itemColl.cur_topn.y -= 10.0f;
    cond = mpColl_800471F8(col);
    ip->pos = col->cur_topn;
    if (cond) {
        return 1;
    }
    return 0;
}
