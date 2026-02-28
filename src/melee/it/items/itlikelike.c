#include "itlikelike.h"

#include "math.h"

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
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "mp/mpcoll.h"

#include <baselib/random.h>

#define GET_ATTRS(ip)                                                         \
    ((itLikelikeAttributes*) ip->xC4_article_data->x4_specialAttributes)

bool it_802D9A2C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    HSD_GObj* temp_r3;
    s32 var_r28;
    Vec3 sp10;
    f32 var_f1;
    f32 var_f2;

    ip->xDD4_itemVar.likelike.x3C = 0;
    if (ip->msid == 7) {
        var_r28 = (s32) attr->x20;
    } else {
        var_r28 = (s32) attr->x1C;
    }
    temp_r3 = ftLib_8008627C(&ip->pos, NULL);
    if (temp_r3 != NULL) {
        if (it_8027CA7C(temp_r3) != 0) {
            return ip->xDD4_itemVar.likelike.x3C;
        }
        ftLib_80086644(temp_r3, &sp10);
        var_f2 = ABS(sp10.x - ip->pos.x);
        if (var_f2 < (f32) var_r28) {
            var_f1 = sp10.y - ip->pos.y;
            if (var_f1 < 0.0f) {
                var_f1 = -var_f1;
            }
            if (var_f1 < attr->x24) {
                ip->xDD4_itemVar.likelike.x50 = temp_r3;
                if (sp10.x < ip->pos.x) {
                    ip->xDD4_itemVar.likelike.x3C = -1;
                } else {
                    ip->xDD4_itemVar.likelike.x3C = 1;
                }
            }
        }
    }
    return ip->xDD4_itemVar.likelike.x3C;
}

void it_802D9B78(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attrs = GET_ATTRS(ip);
    ip->facing_dir = -ip->facing_dir;
    ip->x40_vel.x = ip->facing_dir * attrs->x0->y;
}

void it_802D9BA8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(8);

    it_8027B730(gobj);
    ip->facing_dir = it_8026B684(&ip->pos);
    it_8027C56C(gobj, 0.0f);
    ip->xD5C = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDD4_itemVar.likelike.x44 = 1;
    ip->xDD4_itemVar.likelike.x4C = 0;
    ip->xDD4_itemVar.likelike.x50 = NULL;
    it_80271590(gobj, 0, (HurtCapsule*) &ip->xDD4_itemVar.likelike.x54);
    ip->xDD4_itemVar.likelike.x20 = ip->pos;
    ip->xDD4_itemVar.likelike.x38 = HSD_Randi(2);
    ip->pos.y -= 40.0f;
    ip->xDD4_itemVar.likelike.x4C = attr->x8 + HSD_Randi(attr->xC - attr->x8);
    if (ip->xDD4_itemVar.likelike.x38 == 0) {
        it_802DA960(gobj);
        return;
    }
    it_802DAD18((HSD_GObj* ) gobj);
}


// What is this? Where do i put it? I see there's others in other places too,
// but there it's a f32* and we add +4 to it
Vec3* it_804D6D40;
bool it_2725_Logic5_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(16);

    it_802DBAF0(gobj, 0, 1);
    ip->init_facing_dir = ip->facing_dir;
    ip->xC9C = ip->xC9C + it_8027CBFC(gobj);
    if ((ip->xC9C > attr->x4) || (ip->msid == 0x13)) {
        it_8027C9D8(ip);
        it_802756D0(gobj);
        it_80275474(gobj);
        it_8027CE44(gobj);
        Camera_80030E44(2, &ip->pos);
        if (HSD_Randf() < it_804D6D40->z) {
            it_802DC3DC(gobj);
        } else {
            it_802DC310(gobj);
        }
    } else {
        it_802DC0AC(gobj);
    }
    return false;
}


void it_802D9DDC(Item_GObj* gobj)
{
    PAD_STACK(16);
    it_8027CAD8(gobj);
    it_8026D5CC(gobj);
    it_8027C0A8(gobj, 0.0f, 5.0f);
    it_80275270(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itLikelike_UnkMotion0_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itLikelike_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = HSD_GObjGetUserData(gobj);
    s32 timer = ip->xDD4_itemVar.likelike.x4C;
    if (!timer) {
        if (ip->xDD4_itemVar.likelike.x38 == 1) {
            it_802DA4C0(gobj);
        } else {
            it_802DA104(gobj);
        }
    } else {
        ip->xDD4_itemVar.likelike.x4C = timer - 1;
    }
    it_8027C0A8(gobj, 0.0f, 5.0f);
}

bool itLikelike_UnkMotion0_Coll(Item_GObj* gobj)
{
    CollData* temp_r31;
    s32 temp_cr0_eq;
    Item* ip = ip = GET_ITEM(gobj);
    PAD_STACK(0x20);

    if (ip->xDD4_itemVar.likelike.x38 == 1) {
        temp_r31 = &ip->x378_itemColl;
        it_80276214(gobj);
        temp_cr0_eq = mpColl_8004C750(temp_r31);
        ip->pos = temp_r31->cur_pos;
        if (temp_cr0_eq != 0) {
            ip->xC30 = temp_r31->ceiling.index;
        }
        it_802762D8(gobj);
    } else {
        it_8026D6F4(gobj, (void (*)(HSD_GObj*)) it_802DAA10);
    }
    return it_8027C794(gobj);
}


bool itLikelike_UnkMotion7_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        it_802DA104(gobj);
    }
    return false;
}

void itLikelike_UnkMotion7_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attrs = GET_ATTRS(ip);

    if (ip->xDD4_itemVar.likelike.x4C <= 0) {
        if (it_802D9A2C(gobj) != 0) {
            it_802DB074(gobj);
            return;
        }
        ip->xDD4_itemVar.likelike.x4C = attrs->x18;
        return;
    }
    ip->xDD4_itemVar.likelike.x4C = ip->xDD4_itemVar.likelike.x4C - 1;
}

bool itLikelike_UnkMotion7_Coll(Item_GObj* gobj)
{
    CollData* temp_r31;
    Item* ip = ip = GET_ITEM(gobj);
    s32 temp_cr0_eq;
    PAD_STACK(0x20);

    if (ip->xDD4_itemVar.likelike.x38 == 1) {
        temp_r31 = &ip->x378_itemColl;
        it_80276214(gobj);
        temp_cr0_eq = mpColl_8004C750(temp_r31);
        ip->pos = temp_r31->cur_pos;
        if (temp_cr0_eq != 0) {
            ip->xC30 = temp_r31->ceiling.index;
        }
        it_802762D8(gobj);
    } else {
        it_8026D6F4(gobj, (void (*)(HSD_GObj*)) it_802DAA10);
    }
    return it_8027C794(gobj);
}


void it_802DA104(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(16);

    ip->x40_vel.x = ip->facing_dir * attr->x0->y;
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    it_802756E0(gobj);
    ip->xDD4_itemVar.likelike.x4C = attr->x18;
    ip->xDD4_itemVar.likelike.x44 = 0x3C;
    ip->xDD4_itemVar.likelike.x48 = 0;
    Item_80268E5C(gobj, 1, 1);
}


bool itLikelike_UnkMotion1_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE | ITEM_HIT_PRESERVE);
    }
    return false;
}

void itLikelike_UnkMotion1_Phys(Item_GObj* gobj)
{
    itLikelikeAttributes* attr;
    Item* ip;
    Item* ip2;
    f32 temp_f2;
    s32 temp_r3;
    Article* article;
    s32 temp_r3_2;
    itLikelikeAttributes* attr2;
    PAD_STACK(8);

    ip = GET_ITEM(gobj);
    attr = (article = ip->xC4_article_data)->x4_specialAttributes;

    temp_r3 = ip->xDD4_itemVar.likelike.x44;
    if (temp_r3 == 0) {
        if (HSD_Randi(attr->x3C) != 0) {
            ip->xDD4_itemVar.likelike.x44 = 0x3c;
            goto block_5;
        }
        ip2 = GET_ITEM(gobj);
        attr2 = GET_ATTRS(ip2);
        it_80273454(gobj);
        ip2->xDD4_itemVar.likelike.x4C = attr2->x18;
        Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
        return;
    }
    ip->xDD4_itemVar.likelike.x44 = temp_r3 - 1;
block_5:
    temp_r3_2 = ip->xDD4_itemVar.likelike.x4C;
    if (temp_r3_2 == 0) {
        if (it_802D9A2C(gobj) != 0) {
            it_802DB074(gobj);
            return;
        }
        if (HSD_Randi(3) != 0) {
            ip->xDD4_itemVar.likelike.x4C = attr->x18;
            goto block_12;
        }
        it_802DAE6C(gobj);
        return;
    }
    ip->xDD4_itemVar.likelike.x4C = temp_r3_2 - 1;
block_12:
    temp_f2 = ip->facing_dir;
    if (((temp_f2 > 0.0f) && (ip->x70_nudge.x < 0.0f)) ||
        ((temp_f2 < 0.0f) && (ip->x70_nudge.x > 0.0f)))
    {
        ip->facing_dir = -temp_f2;
        ip->x40_vel.x *= -1.0f;
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, 0.0f, 5.0f);
}

bool itLikelike_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item* ip2;
    itLikelikeAttributes* attrs = GET_ATTRS(ip);
    f32 temp_f3;
    s32 temp_r3;
    f32 var_f1;
    f32 var_f2;

    if (it_8026D8A4(gobj, (void (*)(HSD_GObj*)) it_802D9B78) != 0) {
        if (it_80276308(gobj) != 0) {
            // TODO: Is this flip maybe an inline function?
            ip2 = GET_ITEM(gobj);
            ip2->facing_dir = -ip2->facing_dir;
            ip2->x40_vel.x = ip2->facing_dir * attrs->x0->y;
        } else {
            var_f2 = ABS(ip->xDD4_itemVar.likelike.x20.x - ip->pos.x);
            temp_f3 = attrs->x0->y * 0.5f;
            if (var_f2 < temp_f3) {
                var_f1 = ABS(ip->xDD4_itemVar.likelike.x20.y - ip->pos.y);
                if (var_f1 < temp_f3) {
                    temp_r3 = ip->xDD4_itemVar.likelike.x48;
                    if (temp_r3 >= 4) {
                        ip2 = GET_ITEM(gobj);
                        ip2->facing_dir = -ip2->facing_dir;
                        ip2->x40_vel.x = ip2->facing_dir * attrs->x0->y;
                        ip2->xDD4_itemVar.likelike.x48 = 0;
                    } else {
                        ip->xDD4_itemVar.likelike.x48 = temp_r3 + 1;
                    }
                } else {
                    ip->xDD4_itemVar.likelike.x48 = 0;
                }
            } else {
                ip->xDD4_itemVar.likelike.x48 = 0;
            }
        }
    } else {
        it_802DAA10(gobj);
    }

    ip->xDD4_itemVar.likelike.x20 = ip->pos;
    return it_8027C794(gobj);
}

void it_802DA4C0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(0x10);

    ip->x40_vel.x = ip->facing_dir * attr->x0->y;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.z = 0.0f;
    it_802756E0(gobj);
    ip->xDD4_itemVar.likelike.x4C = attr->x18;
    ip->xDD4_itemVar.likelike.x44 = 0x3c;
    ip->xDD4_itemVar.likelike.x48 = 0;
    Item_80268E5C((HSD_GObj* ) gobj, 2, ITEM_UNK_0x1);
}


bool itLikelike_UnkMotion2_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE | ITEM_HIT_PRESERVE);
    }
    return false;
}

void itLikelike_UnkMotion2_Phys(Item_GObj* gobj)
{
    bool var_r31;
    Vec3 sp14;
    HSD_GObj* temp_r3_2;
    Item* ip;
    f32 temp_f2;
    f32 var_f1;
    itLikelikeAttributes* attr;

    ip = GET_ITEM(gobj);
    attr = GET_ATTRS(ip);
    if (ip->xDD4_itemVar.likelike.x4C == 0) {
        var_r31 = false;
        temp_r3_2 = ftLib_8008627C(&ip->pos, NULL);
        if (temp_r3_2 != NULL) {
            ftLib_80086644(temp_r3_2, &sp14);
            var_f1 = ABS(sp14.x - ip->pos.x);
            if (var_f1 < attr->x28) {
                var_f1 = ABS(sp14.y - ip->pos.y);
                if (var_f1 < attr->x2C) {
                    var_r31 = true;
                }
            }
        }
        if (var_r31) {
            ip->xDD4_itemVar.likelike.x3C = 1;
            it_802DAA10(gobj);
            return;
        }
        if (HSD_Randi(3) != 0) {
            ip->xDD4_itemVar.likelike.x4C = attr->x18;
            goto block_15;
        }
        it_802DAE6C(gobj);
        return;
    }
    ip->xDD4_itemVar.likelike.x4C = ip->xDD4_itemVar.likelike.x4C - 1;
block_15:
    ip->x40_vel.x = ip->facing_dir * attr->x0->y;
    temp_f2 = ip->facing_dir;
    if (((temp_f2 > 0.0f) && (ip->x70_nudge.x < 0.0f)) ||
        ((temp_f2 < 0.0f) && (ip->x70_nudge.x > 0.0f)))
    {
        ip->facing_dir = -temp_f2;
        ip->x40_vel.x *= -1.0f;
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0CC(gobj, 0.0f, 5.0f);
}

bool itLikelike_UnkMotion2_Coll(Item_GObj* gobj)
{
    CollData* temp_r31;
    Item* ip = GET_ITEM(gobj);
    f32 temp_f3;
    s32 temp_r3;
    f32 var_f1;
    f32 var_f2;
    s32 coll_result;
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(24);

    temp_r31 = &ip->x378_itemColl;
    it_80276214(gobj);
    coll_result = mpColl_8004C750(temp_r31);
    ip->pos = temp_r31->cur_pos;
    if (coll_result != 0) {
        ip->xC30 = temp_r31->ceiling.index;
    }
    if (it_802762D8(gobj) != 0) {
        ip->facing_dir = -ip->facing_dir;
        ip->x40_vel.x *= -1.0f;
    } else if (it_80276308(gobj) != 0) {
        ip->facing_dir = -ip->facing_dir;
        ip->x40_vel.x *= -1.0f;
    } else {
        var_f2 = ABS(ip->xDD4_itemVar.likelike.x20.x - ip->pos.x);
        temp_f3 = 0.5f;
        temp_f3 = attr->x0->y * temp_f3;
        if (var_f2 < temp_f3) {
            var_f1 = ABS(ip->xDD4_itemVar.likelike.x20.y - ip->pos.y);
            if (var_f1 < temp_f3) {
                temp_r3 = ip->xDD4_itemVar.likelike.x48;
                if (temp_r3 >= 4) {
                    ip->facing_dir = -ip->facing_dir;
                    ip->x40_vel.x = ip->facing_dir * attr->x0->y;
                    ip->xDD4_itemVar.likelike.x48 = 0;
                } else {
                    ip->xDD4_itemVar.likelike.x48 = temp_r3 + 1;
                }
            } else {
                goto block_15;
            }
        } else {
block_15:
    ip->xDD4_itemVar.likelike.x48 = 0;
        }
    }
    ip->xDD4_itemVar.likelike.x20 = ip->pos;
    return it_8027C794(gobj);
}

void it_802DA8D8(Item_GObj* gobj)
{
    Item* ip;
    unsigned char _[8];
    itECB ecb;

    ip = GET_ITEM(gobj);
    it_802762B0(ip);
    ecb = ip->xC1C;
    ecb.bottom = ecb.top;
    ecb.top = ip->xC1C.bottom;
    it_80275D5C(gobj, &ecb);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}


void it_802DA960(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itECB ecb;
    PAD_STACK(0x10);

    it_802762BC(ip);
    if (ip->xDD4_itemVar.likelike.x38 == 1) {
        ecb = ip->xC1C;
        ecb.top = ecb.bottom;
        ecb.bottom = ip->xC1C.bottom;
        it_80275D5C(gobj, &ecb);
        it_8027C56C(gobj, 0.0f);
    }
    ip->xDD4_itemVar.likelike.x38 = 0;
    it_80273454(gobj);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}


void it_802DAA10(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    unsigned char _[8];
    itECB ecb;
    PAD_STACK(8);
    it_802DBAF0(gobj, 1, 1);
    it_802762BC(ip);
    if (ip->xDD4_itemVar.likelike.x38 == 1) {
        ecb = ip->xC1C;
        ecb.bottom = ecb.top;
        ecb.top = ip->xC1C.bottom;
        it_80275D5C(gobj, &ecb);
    }
    it_8027C56C(gobj, 0.0f);
    ip->xDD4_itemVar.likelike.x38 = 0;
    ip->xDD4_itemVar.likelike.x4C = 0;
    it_80273454(gobj);
    Item_80268E5C((HSD_GObj* ) gobj, 5, ITEM_ANIM_UPDATE);
}


bool itLikelike_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itLikelike_UnkMotion5_Phys(Item_GObj* gobj)
{

    Item* ip = GET_ITEM(gobj);
    ItemAttr* temp_r4;
    PAD_STACK(8);

    if (((s32) ip->msid == 5) && (it_802D9A2C(gobj) != 0)) {
        it_802DB398(gobj);
        return;
    }
    temp_r4 = ip->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}



bool itLikelike_UnkMotion4_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, it_802D9DDC);
    return it_8027C794(gobj);
}

bool itLikelike_UnkMotion5_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, it_802DABC0);
    return it_8027C794(gobj);
}

void it_802DABC0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(24);
    ip->xDD4_itemVar.likelike.x38 = 0;
    ip->xDD4_itemVar.likelike.x4C = 0;
    ip->xDD4_itemVar.likelike.x3C = 0;
    it_80273454(gobj);
    it_802762B0(ip);
    Item_80268E5C(gobj, 0x11, ITEM_ANIM_UPDATE);
}

bool itLikelike_UnkMotion17_Anim(Item_GObj* gobj)
{
    PAD_STACK(16);
    if (it_80272C6C(gobj) == 0) {
        it_8026D5CC(gobj);
        it_8027CAD8(gobj);
        it_8026D5CC(gobj);
        it_8027C0A8(gobj, 0.0f, 5.0f);
        it_80275270(gobj);
        Item_80268E5C((HSD_GObj* ) gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}


void itLikelike_UnkMotion17_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, 0.0F, 5.0F);
}

bool itLikelike_UnkMotion17_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D564(gobj);
    return it_8027C794(gobj);
}

void it_802DAD18(HSD_GObj* gobj)
{
    HSD_JObj* temp_r31 = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(0x20);

    HSD_JObjSetRotationZ(temp_r31, M_PI);
    ip->xDCE_flag.b7 = 1;
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}


bool itLikelike_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itLikelike_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y += ip->xCC_item_attr->x10_fall_speed;
}

bool itLikelike_UnkMotion3_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E71C(gobj, it_802DA8D8);
    return it_8027C794(gobj);
}

void it_802DAE6C(Item_GObj* gobj)
{
    PAD_STACK(16);
    it_80273454(gobj);
    Item_80268E5C(gobj, 0x10, ITEM_ANIM_UPDATE);
}


bool itLikelike_UnkMotion16_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item* ip2;
    Item* ip3;
    itLikelikeAttributes* attr;
    itLikelikeAttributes* attr2;
    PAD_STACK(0x10);

    if (it_80272C6C(gobj) == 0) {
        ip->facing_dir = it_8026B684(&ip->pos);
        if (ip->xDD4_itemVar.likelike.x38 == 0) {
            ip2 = GET_ITEM(gobj);
            attr2 = GET_ATTRS(ip2);
            ip2->x40_vel.x = ip2->facing_dir * attr2->x0->y;
            ip2->x40_vel.z = 0.0f;
            ip2->x40_vel.y = 0.0f;
            it_802756E0(gobj);
            ip2->xDD4_itemVar.likelike.x4C = attr2->x18;
            ip2->xDD4_itemVar.likelike.x44 = 0x3C;
            ip2->xDD4_itemVar.likelike.x48 = 0;
            Item_80268E5C(gobj, 1, ITEM_UNK_0x1);
        } else {
            ip3 = GET_ITEM(gobj);
            attr = GET_ATTRS(ip3);
            // This line is to get 100%
            if (attr->x0->y && attr->x0->y) {
            };
            ip3->x40_vel.x = ip3->facing_dir * attr->x0->y;
            ip3->x40_vel.y = 0;
            ip3->x40_vel.z = 0;
            it_802756E0(gobj);
            ip3->xDD4_itemVar.likelike.x4C = attr->x18;
            ip3->xDD4_itemVar.likelike.x44 = 0x3C;
            ip3->xDD4_itemVar.likelike.x48 = 0;
            Item_80268E5C( gobj, 2, ITEM_UNK_0x1);
        }
    }
    return false;
}


void itLikelike_UnkMotion16_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion16_Coll(Item_GObj* gobj)
{
    CollData* temp_r31;
    Item* ip = ip = GET_ITEM(gobj);
    s32 temp_cr0_eq;
    PAD_STACK(0x20);

    if (ip->xDD4_itemVar.likelike.x38 == 0) {
        it_8026D6F4(gobj, (void (*)(HSD_GObj*)) it_802DAA10);
    } else {
        temp_r31 = &ip->x378_itemColl;
        it_80276214(gobj);
        temp_cr0_eq = mpColl_8004C750(temp_r31);
        ip->pos = temp_r31->cur_pos;
        if (temp_cr0_eq != 0) {
            ip->xC30 = temp_r31->ceiling.index;
        }
        it_802762D8(gobj);
    }
    return it_8027C794(gobj);
}


void it_802DB074(HSD_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(8);
    ip->facing_dir = ip->xDD4_itemVar.likelike.x3C;
    ip->x40_vel.x = ip->facing_dir * attr->x0->y * 2.0f;
    ip->xDD4_itemVar.likelike.x4C = 0x1E;
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
}


bool itLikelike_UnkMotion8_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itLikelike_UnkMotion8_Phys(Item_GObj* gobj)
{
    Vec3 sp30;
    Item* temp_r31;
    s32 temp_r3;
    HSD_GObj* temp_r3_2;
    f32 var_f1;
    PAD_STACK(0x18);

    temp_r31 = gobj->user_data;
    temp_r3 = temp_r31->xDD4_itemVar.likelike.x4C;
    if (temp_r3 == 0) {
        temp_r31->xDD4_itemVar.likelike.x50 = 0;
        it_8027CAD8(gobj);
        it_8026D5CC(gobj);
        it_8027C0A8(gobj, 0.0f, 5.0f);
        it_80275270(gobj);
        Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
        return;
    }
    temp_r31->xDD4_itemVar.likelike.x4C = temp_r3 - 1;
    temp_r3_2 = temp_r31->xDD4_itemVar.likelike.x50;
    // permuter slop for 100%
    if (!GET_ITEM(gobj) && !GET_ITEM(gobj)) {
    }
    if (temp_r3_2 != NULL) {
        ftLib_80086644(temp_r3_2, &sp30);
        var_f1 = ABS(temp_r31->pos.x - sp30.x);
        if (var_f1 < 15.0f) {
            it_80275258(gobj);
            if ((f32) temp_r31->xDD4_itemVar.likelike.x3C == 1.0f) {
                it_802DB5F0(gobj);
                return;
            }
            it_802DB74C(gobj);
            return;
        }
    } else {
        temp_r31->xDD4_itemVar.likelike.x4C = 0x78;
        it_8027CAD8(gobj);
        it_8026D5CC(gobj);
        it_8027C0A8(gobj, 0.0f, 5.0f);
        it_80275270(gobj);
        Item_80268E5C((HSD_GObj*) gobj, 0, ITEM_ANIM_UPDATE);
        return;
    }
    it_8027C8D0(&temp_r31->x40_vel, &temp_r31->x378_itemColl.floor.normal,
                temp_r31->facing_dir);
    it_8027C0CC(gobj, 0.0f, 5.0f);
}

bool itLikelike_UnkMotion8_Coll(Item_GObj* gobj)
{
    CollData* temp_r31;
    Item* ip = ip = GET_ITEM(gobj);
    s32 temp_cr0_eq;
    PAD_STACK(0x20);

    if (ip->xDD4_itemVar.likelike.x38 == 1) {
        temp_r31 = &ip->x378_itemColl;
        it_80276214(gobj);
        temp_cr0_eq = mpColl_8004C750(temp_r31);
        ip->pos = temp_r31->cur_pos;
        if (temp_cr0_eq != 0) {
            ip->xC30 = temp_r31->ceiling.index;
        }
        it_802762D8(gobj);
    } else {
        it_8026D6F4(gobj, (void (*)(HSD_GObj*)) it_802DAA10);
    }
    return it_8027C794(gobj);
}


void it_802DB358(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.likelike.x50 = ip->grab_victim;
    ip->xDD0_flag.b5 = false;
    it_80274ECC(gobj, true);
}

void it_802DB398(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(0x18);

    ip->facing_dir = ip->xDD4_itemVar.likelike.x3C;
    ip->xDD4_itemVar.likelike.x50 = NULL;
    Item_8026AE84(ip, 0x139, 0x7FU, 0x40U);
    it_80275258(gobj);
    if (ip->facing_dir == 1.0f) {
        Item_80268E5C(gobj, 0xB, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(gobj, 0xC, ITEM_ANIM_UPDATE);
    }
    it_80274F28(ip, 1, (void (*)(HSD_GObj*)) it_802DB358, (void (*)(HSD_GObj*, HSD_GObj*)) ftCo_800C78B0);
}


bool itLikelike_UnkMotion12_Anim(Item_GObj* gobj)
{
    Item* ip;
    PAD_STACK(16);

    ip = GET_ITEM(gobj);
    if (it_80272C6C(gobj) == 0) {
        it_8026D5CC(gobj);
        if (ip->xDD4_itemVar.likelike.x50 != NULL) {
            it_802DB8A8(gobj);
        } else {
            it_8027CAD8(gobj);
            it_8026D5CC(gobj);
            it_8027C0A8(gobj, 0.0f, 5.0f);
            it_80275270(gobj);
            Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
        }
    }
    return false;
}

void itLikelike_UnkMotion12_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* temp_r4_2;

    if ((enum GroundOrAir) ip->ground_or_air == GA_Air) {
        temp_r4_2 = ip->xCC_item_attr;
        it_80272860(gobj, temp_r4_2->x10_fall_speed, temp_r4_2->x14_fall_speed_max);
        return;
    }
    it_8027C8D0(&ip->x40_vel, &ip->x378_itemColl.floor.normal, ip->facing_dir);
    it_8027C0A8(gobj, 0.0f, 5.0f);
}



bool itLikelike_UnkMotion12_Coll(Item_GObj* gobj)
{
    Item* temp_r3;

    temp_r3 = GET_ITEM(gobj);

    if ((enum GroundOrAir) temp_r3->ground_or_air == GA_Air) {
        if (it_8026DA08(gobj) != 0) {
            it_802762B0(temp_r3);
            it_80273454(gobj);
        }
    } else {
        it_8026D6F4(gobj, (void (*)(HSD_GObj*)) it_802DAA10);
    }
    return it_8027C794(gobj);
}

void it_802DB5F0(Item_GObj* gobj)
{
    Item* temp_r31;
    PAD_STACK(8);

    temp_r31 = GET_ITEM(gobj);
    it_80273454(gobj);
    Item_80268E5C((HSD_GObj*) gobj, 9, ITEM_ANIM_UPDATE);
    Item_8026AE84(temp_r31, 0x139, 0x7FU, 0x40U);
    it_80274F28(temp_r31, 1, (void (*)(HSD_GObj*)) it_802DB358, (void (*)(HSD_GObj*, HSD_GObj*)) ftCo_800C78B0);
    temp_r31->xDD4_itemVar.likelike.x50 = NULL;
}

bool itLikelike_UnkMotion9_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);

    if (it_80272C6C(gobj) == 0) {
        it_8026D5CC(gobj);
        if (ip->xDD4_itemVar.likelike.x50 != 0U) {
            it_802DB8A8(gobj);
        } else {
            it_8027CAD8(gobj);
            it_8026D5CC(gobj);
            it_8027C0A8(gobj, 0.0f, 5.0f);
            it_80275270(gobj);
            Item_80268E5C((HSD_GObj* ) gobj, 0, ITEM_ANIM_UPDATE);
        }
    }
    return false;
}


void itLikelike_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion9_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

void it_802DB74C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);

    it_80273454(gobj);
    Item_80268E5C((HSD_GObj* ) gobj, 0xA, ITEM_ANIM_UPDATE);
    Item_8026AE84(ip, 0x139, 0x7FU, 0x40U);
    it_80274F28(ip, 1, (void (*)(HSD_GObj*)) it_802DB358, (void (*)(HSD_GObj*, HSD_GObj*)) ftCo_800C78B0);
    ip->xDD4_itemVar.likelike.x50 = NULL;
}

bool itLikelike_UnkMotion10_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);

    if (it_80272C6C(gobj) == 0) {
        it_8026D5CC(gobj);
        if (ip->xDD4_itemVar.likelike.x50 != 0U) {
            it_802DB8A8(gobj);
        } else {
            it_8027CAD8(gobj);
            it_8026D5CC(gobj);
            it_8027C0A8(gobj, 0.0f, 5.0f);
            it_80275270(gobj);
            Item_80268E5C((HSD_GObj* ) gobj, 0, ITEM_ANIM_UPDATE);
        }
    }
    return false;
}

void itLikelike_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion10_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

void it_802DB8A8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    it_80273454(gobj);
    ip->xDD4_itemVar.likelike.x4C = 0.0f;
    Item_8026AE84(ip, 0x13B, 0x7FU, 0x40U);
    it_80275258(gobj);
    Item_80268E5C( gobj, 0xD, ITEM_ANIM_UPDATE);
}


bool itLikelike_UnkMotion13_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0xD, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itLikelike_UnkMotion13_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(8);
    if (ip->xDD4_itemVar.likelike.x4C == 0) {
        ip->xDD4_itemVar.likelike.x4C =
            attr->x3D_reset_timer;

        ftCo_800C7C60(
            (Fighter_GObj*)ip->grab_victim,
            attr->x3E_damage_amount
        );
    } else {
        ip->xDD4_itemVar.likelike.x4C = ip->xDD4_itemVar.likelike.x4C - 1;
    }
}


bool itLikelike_UnkMotion13_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

void it_802DB9F4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    it_80273454(gobj);
    ip->xDD4_itemVar.likelike.x4C = 0.0f;
    if (HSD_Randi(2) != 0) {
        Item_80268E5C(gobj, 0xE, ITEM_ANIM_UPDATE);
        return;
    }
    Item_80268E5C(gobj, 0xF, ITEM_ANIM_UPDATE);
}


void it_802DBA68(Item_GObj* gobj)
{
    Item* ip;
    PAD_STACK(24);

    ip = GET_ITEM(gobj);
    it_80273454(gobj);
    it_802DBAF0(gobj, 0, 1);
    ip->xDD4_itemVar.likelike.x4C = 0x78;
    it_8027CAD8(gobj);
    it_8026D5CC(gobj);
    it_8027C0A8(gobj, 0.0f, 5.0f);
    it_80275270(gobj);
    Item_80268E5C((HSD_GObj* ) gobj, 0, ITEM_ANIM_UPDATE);
}


void it_802DBAF0(Item_GObj* arg0, s32 arg1, s32 arg2)
{
    Vec3 vec;
    Vec3 sp18;
    HSD_GObj* temp_r4;
    Item* ip;
    itLikelikeAttributes* attr;
    f32 fval;

    ip = GET_ITEM(arg0);
    attr = GET_ATTRS(ip);
    if ((s32) ip->msid != 8) {
        temp_r4 = ip->grab_victim;
        if ((temp_r4 != NULL) && (temp_r4 == ip->xDD4_itemVar.likelike.x50)) {
            vec.x = 0.0f;
            vec.y = 0.5f * (ip->x378_itemColl.ecb.top.y + ip->x378_itemColl.ecb.bottom.y);
            vec.z = 0.0f;
            vec.x += ip->pos.x;
            vec.y += ip->pos.y;
            vec.z += ip->pos.z;
            lb_8000B1CC(it_80272CC0(arg0, 8), NULL, &sp18);
            if (arg1 == 0) {
                fval = 0.0f;
            } else if ((f32) arg1 == -1.0f) {
                fval = attr->x30;
            } else {
                fval = attr->x34;
            }

            // TODO: fix pointer hacks
            if (arg2 != 0) {
                ftCo_800C7B0C(ip->grab_victim, &sp18, &vec,
                              (lbColl_80008D30_arg1*) ((u8*) attr + 0x64),
                              fval);
            } else {
                ftCo_800C7B0C(ip->grab_victim, &sp18, &vec,
                              (lbColl_80008D30_arg1*) ((u8*) attr + 0x40),
                              fval);
            }
            ip->xDD4_itemVar.likelike.x50 = NULL;
            ip->atk_victim = NULL;
            ip->grab_victim = NULL;
            Item_8026AE84(ip, 0x13A, 0x7FU, 0x40U);
        }
    }
}

bool itLikelike_UnkMotion14_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 temp_r3;
    PAD_STACK(0x18);
    if (ip->xDD4_itemVar.likelike.x4C == GET_ATTRS(ip)->x38) {
        it_802DBAF0(gobj, 1, 0);
    }
    temp_r3 = ip->xDD4_itemVar.likelike.x4C;
    if (temp_r3 >= 0x28) {
        ip->xDD4_itemVar.likelike.x4C = 0x78;
        it_8027CAD8(gobj);
        it_8026D5CC(gobj);
        it_8027C0A8(gobj, 0.0f, 5.0f);
        it_80275270(gobj);
        Item_80268E5C((HSD_GObj* ) gobj, 0, ITEM_ANIM_UPDATE);
    } else {
        ip->xDD4_itemVar.likelike.x4C = temp_r3 + 1;
    }
    return false;
}

void itLikelike_UnkMotion14_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion14_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

bool itLikelike_UnkMotion15_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 temp_r3;
    PAD_STACK(0x18);
    if (ip->xDD4_itemVar.likelike.x4C == GET_ATTRS(ip)->x38) {
        it_802DBAF0(gobj, -1, 0);
    }
    temp_r3 = ip->xDD4_itemVar.likelike.x4C;
    if (temp_r3 >= 0x28) {
        ip->xDD4_itemVar.likelike.x4C = 0x78;
        it_8027CAD8(gobj);
        it_8026D5CC(gobj);
        it_8027C0A8(gobj, 0.0f, 5.0f);
        it_80275270(gobj);
        Item_80268E5C((HSD_GObj* ) gobj, 0, ITEM_ANIM_UPDATE);
    } else {
        ip->xDD4_itemVar.likelike.x4C = temp_r3 + 1;
    }
    return false;
}


void itLikelike_UnkMotion15_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion15_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

void itLikeLike_Logic5_PickedUp(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_802DBAF0(gobj, 0, 1);
    Item_80268E5C(gobj, 0x12, ITEM_ANIM_UPDATE);
}

bool itLikelike_UnkMotion18_Anim(Item_GObj* gobj)
{
    PAD_STACK(16);
    if (!it_80272C6C(gobj)) {
        it_802DBAF0(gobj, 0, 1);
        Item_80268E5C(gobj, 0x12, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itLikelike_UnkMotion18_Phys(Item_GObj* gobj) {}

void it_2725_Logic5_Dropped(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itECB ebc;
    Item* ip2;
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(8);

    it_8027CBA4(gobj);
    ip->xDD4_itemVar.likelike.x4C = attr->x4;
    ip2 = GET_ITEM(gobj);
    it_802762BC(ip2);
    if (ip2->xDD4_itemVar.likelike.x38 == 1) {
        ebc = ip2->xC1C;
        ebc.top = ip2->xC1C.bottom;
        ebc.top = ip2->xC1C.bottom;
        it_80275D5C(gobj, &ebc);
        it_8027C56C(gobj, 0.0f);
    }
    ip2->xDD4_itemVar.likelike.x38 = 0;
    it_80273454(gobj);
    Item_80268E5C((HSD_GObj* ) gobj, 4, ITEM_ANIM_UPDATE);
}


void itLikeLike_Logic5_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CB3C(gobj);
    ip->xDD4_itemVar.likelike.x4C = 0;
    Item_80268E5C(gobj, 0x13, ITEM_ANIM_UPDATE);
}

bool itLikelike_UnkMotion19_Anim(Item_GObj* gobj)
{
    return false;
}

void itLikelike_UnkMotion19_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itLikelike_UnkMotion19_Coll(Item_GObj* gobj)
{
    return it_8027C824(gobj, NULL);
}

void it_802DC0AC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attr = GET_ATTRS(ip);
    PAD_STACK(8);
    it_80273454(gobj);
    ip->xDD4_itemVar.likelike.x4C = attr->x4;
    ip->xDD4_itemVar.likelike.x3C = 0;
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}


bool itLikelike_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

void itLikelike_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 temp_r3;
    itLikelikeAttributes* attr;
    itECB ecb;
    PAD_STACK(0x20);

    temp_r3 = ip->xDD4_itemVar.likelike.x4C;
    if (temp_r3 == 0) {
        if (ip->xDD4_itemVar.likelike.x38 == 0) {
            attr = GET_ATTRS(ip);
            ip->x40_vel.x = ip->facing_dir * attr->x0->y;
            ip->x40_vel.z = 0.0f;
            ip->x40_vel.y = 0.0f;
            it_802756E0(gobj);
            ip->xDD4_itemVar.likelike.x44 = 0x3C;
            ip->xDD4_itemVar.likelike.x48 = 0;
            ip->xDD4_itemVar.likelike.x4C = attr->x18;
            Item_80268E5C((HSD_GObj*) gobj, 1, ITEM_UNK_0x1);
            return;
        }
        it_802DBAF0(gobj, 1, 1);
        it_802762BC(ip);
        if (ip->xDD4_itemVar.likelike.x38 == 1) {
            ecb = ip->xC1C;
            // TODO: change once stack issues fixed
            ecb.top = ip->xC1C.bottom;
            ecb.top = ip->xC1C.bottom;
            it_80275D5C(gobj, &ecb);
        }
        it_8027C56C(gobj, 0.0f);
        ip->xDD4_itemVar.likelike.x38 = 0;
        ip->xDD4_itemVar.likelike.x4C = 0;
        it_80273454(gobj);
        Item_80268E5C((HSD_GObj*) gobj, 5, ITEM_ANIM_UPDATE);
        return;
    }
    ip->xDD4_itemVar.likelike.x4C = temp_r3 - 1;
}

bool itLikelike_UnkMotion6_Coll(Item_GObj* gobj)
{
    CollData* temp_r31;
    Item* ip = ip = GET_ITEM(gobj);
    s32 temp_cr0_eq;
    PAD_STACK(0x20);

    if (ip->xDD4_itemVar.likelike.x38 == 1) {
        temp_r31 = &ip->x378_itemColl;
        it_80276214(gobj);
        temp_cr0_eq = mpColl_8004C750(temp_r31);
        ip->pos = temp_r31->cur_pos;
        if (temp_cr0_eq != 0) {
            ip->xC30 = temp_r31->ceiling.index;
        }
        it_802762D8(gobj);
    } else {
        it_8026D6F4(gobj, (void (*)(HSD_GObj*)) it_802DAA10);
    }
    return it_8027C794(gobj);
}


void it_802DC310(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027B964(gobj, 0);
    ip->xDD4_itemVar.likelike.x18 = 0;
    Item_80268E5C(gobj, 0x14, ITEM_ANIM_UPDATE);
}

bool itLikelike_UnkMotion20_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0x14, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itLikelike_UnkMotion20_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion20_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

void it_802DC3DC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027BA54(gobj, &ip->x40_vel);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0x15, 3);
}

bool itLikelike_UnkMotion21_Anim(Item_GObj* gobj)
{
    return false;
}

void itLikelike_UnkMotion21_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itLikelike_UnkMotion21_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

void itLikeLike_Logic5_Destroyed(Item_GObj* gobj)
{
    it_802DBAF0(gobj, 0, 1);
    it_2725_Logic9_Destroyed(gobj);
}

/// #it_802DC4BC
