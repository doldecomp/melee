#include "itcoin.h"

#include "cm/camera.h"
#include "gm/gm_1A36.h"
#include "gr/ground.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

extern f32 it_804DD9B8;
extern f32 it_804DD9BC;
extern f32 it_804DD9C0;
extern f32 it_804DD9C4;
extern f32 it_804DD9D0;

s32 grFigureGet_80219C50(s32);                       /* extern */
M2C_UNK gm_8017E280(u16, M2C_UNK);                   /* extern */
M2C_UNK grFigureGet_80219C34(s32);                   /* extern */
M2C_UNK HSD_GObjObjet_80390A70(Item_GObj*, u8, s32); /* extern */
M2C_UNK HSD_GObjObjet_80390B0C(Item_GObj*);          /* extern */
M2C_UNK it_8027B798(Item_GObj*, Vec3*);              /* extern */
f32 it_8027CBFC(Item_GObj*);                         /* extern */
s32 un_8031C5E4(s32);                                /* static */

void it_802F1630(HSD_GObj* gobj); /* static */
void it_802F1588(HSD_GObj* gobj); /* static */

void it_802F13B4(HSD_GObj* arg0, s32 arg1)
{
    HSD_JObj* temp_r29;
    void* temp_r30;
    void* temp_r31;

    temp_r31 = arg0->user_data;
    temp_r29 = M2C_FIELD(arg0->hsd_obj, HSD_JObj**, 0x10);
    temp_r30 = M2C_FIELD(M2C_FIELD(temp_r31, void**, 0xC4), void**, 4);
    if (M2C_FIELD(temp_r31, s32*, 0xDD8) != 0) {
        if (((gm_801A45E8(1) != 0) &&
             (grFigureGet_80219C50(M2C_FIELD(temp_r31, s32*, 0xDE8)) == 0)) ||
            ((Camera_80031144() < M2C_FIELD(temp_r30, f32*, 0x48)) &&
             (grFigureGet_80219C50(M2C_FIELD(temp_r31, s32*, 0xDE8)) == 0)))
        {
            HSD_JObjSetFlagsAll(temp_r29, 0x10);
            HSD_JObjClearFlagsAll(temp_r29->next, 0x10);
        } else {
            HSD_JObjSetFlagsAll(temp_r29->next, 0x10);
            HSD_JObjClearFlagsAll(temp_r29, 0x10);
        }
    } else if (((gm_801A45E8(1) != 0) && (Ground_801C1D84() == 0)) ||
               (Camera_80031144() < M2C_FIELD(temp_r30, f32*, 0x48)))
    {
        HSD_JObjSetFlagsAll(temp_r29, 0x10);
        HSD_JObjClearFlagsAll(temp_r29->next, 0x10);
    } else {
        HSD_JObjSetFlagsAll(temp_r29->next, 0x10);
        HSD_JObjClearFlagsAll(temp_r29, 0x10);
    }
    it_8026EECC(arg0, arg1);
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

void it_802F1630(HSD_GObj* arg0)
{
    HSD_JObj* temp_r30;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    s32 temp_cr0_eq_3;
    s32 temp_r31;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u32 temp_r4_4;
    void* temp_r4;

    temp_r4 = arg0->user_data;
    temp_r31 =
        M2C_ERROR(/* unknown instruction: subi $r31, $r3, %l(it_803F93C8) */);
    M2C_FIELD(temp_r4, f32*, 0x48) = it_804DD9B8;
    M2C_FIELD(temp_r4, f32*, 0x44) = it_804DD9B8;
    M2C_FIELD(temp_r4, f32*, 0x40) = it_804DD9B8;
    temp_r30 = arg0->hsd_obj;
    if (temp_r30 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x27F, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
    }
    if (temp_r30->flags & 0x20000) {
        //        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13,
        //        %sda21(it_804D5758) */), 0x280, temp_r31 + 0x60);
    }
    temp_r30->rotate.x = it_804DD9B8;
    if (!(temp_r30->flags & 0x02000000)) {
        temp_cr0_eq = temp_r30 == NULL;
        if (temp_cr0_eq == 0) {
            if (temp_cr0_eq != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
            }
            temp_r4_2 = temp_r30->flags;
            var_r3 = 0;
            if (!(temp_r4_2 & 0x800000) && (temp_r4_2 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(temp_r30);
            }
        }
    }
    if (temp_r30 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x294, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
    }
    if (temp_r30->flags & 0x20000) {
        //__assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13,
        //%sda21(it_804D5758) */), 0x295, temp_r31 + 0x60);
    }
    temp_r30->rotate.y = it_804DD9B8;
    if (!(temp_r30->flags & 0x02000000)) {
        temp_cr0_eq_2 = temp_r30 == NULL;
        if (temp_cr0_eq_2 == 0) {
            if (temp_cr0_eq_2 != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
            }
            temp_r4_3 = temp_r30->flags;
            var_r3_2 = 0;
            if (!(temp_r4_3 & 0x800000) && (temp_r4_3 & 0x40)) {
                var_r3_2 = 1;
            }
            if (var_r3_2 == 0) {
                HSD_JObjSetMtxDirtySub(temp_r30);
            }
        }
    }
    if (temp_r30 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x2A9, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
    }
    if (temp_r30->flags & 0x20000) {
        //__assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13,
        //%sda21(it_804D5758) */), 0x2AA, temp_r31 + 0x60);
    }
    temp_r30->rotate.z = it_804DD9B8;
    if (!(temp_r30->flags & 0x02000000)) {
        temp_cr0_eq_3 = temp_r30 == NULL;
        if (temp_cr0_eq_3 == 0) {
            if (temp_cr0_eq_3 != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
            }
            temp_r4_4 = temp_r30->flags;
            var_r3_3 = 0;
            if (!(temp_r4_4 & 0x800000) && (temp_r4_4 & 0x40)) {
                var_r3_3 = 1;
            }
            if (var_r3_3 == 0) {
                HSD_JObjSetMtxDirtySub(temp_r30);
            }
        }
    }
    Item_80268E5C(arg0, 1, ITEM_UNK_0x1);
    it_802756D0(arg0);
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

void it_802F1888(Item_GObj* arg0)
{
    HSD_JObj* temp_r3;
    HSD_JObj* var_r0;

    temp_r3 = arg0->hsd_obj;
    if (temp_r3 == NULL) {
        var_r0 = NULL;
    } else {
        var_r0 = temp_r3->child;
    }
    HSD_JObjClearFlagsAll(var_r0, 0x10);
    Item_80268E5C(arg0, 2, ITEM_UNK_0x1);
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

bool it_802F1910(Item_GObj* arg0)
{
    Item* temp_r31;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_2;
    s32 temp_r0;
    void* temp_r30;

    temp_r31 = arg0->user_data;
    temp_r30 = temp_r31->xC4_article_data->x4_specialAttributes;
    it_802762BC(temp_r31);
    temp_r31->xC9C = temp_r31->xC9C + it_8027CBFC(arg0);
    it_8027B798(arg0, &temp_r31->x40_vel);
    if ((temp_r31->x40_vel.x == it_804DD9B8) &&
        (temp_r31->x40_vel.y == it_804DD9B8))
    {
        temp_r31->x40_vel.x = it_804DD9BC * -temp_r31->xCCC_incDamageDirection;
        temp_r31->x40_vel.y = it_804DD9BC;
    }
    lbVector_Normalize(&temp_r31->x40_vel);
    if ((temp_r31->pos.x > it_804DD9B8) &&
        (it_804DD9C0 == temp_r31->xCCC_incDamageDirection))
    {
        temp_r31->x40_vel.x *= it_804DD9C0;
    }
    if ((temp_r31->pos.x < it_804DD9B8) &&
        (it_804DD9C4 == temp_r31->xCCC_incDamageDirection))
    {
        temp_r31->x40_vel.x *= it_804DD9C0;
    }
    if (temp_r31->pos.x > it_804DD9B8) {
        if (it_804DD9C0 == temp_r31->xCCC_incDamageDirection) {
            temp_r31->x40_vel.x *=
                M2C_FIELD(temp_r30, f32*, 0x30) *
                (M2C_FIELD(temp_r30, f32*, 0x24) + temp_r31->xC9C);
        } else {
            temp_r31->x40_vel.x *=
                M2C_FIELD(temp_r30, f32*, 0x2C) *
                (M2C_FIELD(temp_r30, f32*, 0x24) + temp_r31->xC9C);
        }
        temp_f0 = -M2C_FIELD(temp_r30, f32*, 0x3C);
        M2C_ERROR(/* unknown instruction: cror eq, lt, eq */);
        if (temp_r31->x40_vel.x == temp_f0) {
            temp_r31->x40_vel.x = temp_f0;
        }
    } else {
        if (it_804DD9C0 == temp_r31->xCCC_incDamageDirection) {
            temp_r31->x40_vel.x *=
                M2C_FIELD(temp_r30, f32*, 0x2C) *
                (M2C_FIELD(temp_r30, f32*, 0x24) + temp_r31->xC9C);
        } else {
            temp_r31->x40_vel.x *=
                M2C_FIELD(temp_r30, f32*, 0x30) *
                (M2C_FIELD(temp_r30, f32*, 0x24) + temp_r31->xC9C);
        }
        temp_f1 = M2C_FIELD(temp_r30, f32*, 0x3C);
        M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
        if (temp_r31->x40_vel.x == temp_f1) {
            temp_r31->x40_vel.x = temp_f1;
        }
    }
    temp_r31->x40_vel.y *= M2C_FIELD(temp_r30, f32*, 0x38) *
                           (M2C_FIELD(temp_r30, f32*, 0x28) + temp_r31->xC9C);
    temp_f1_2 = M2C_FIELD(temp_r30, f32*, 0x40);
    M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
    if (temp_r31->x40_vel.y == temp_f1_2) {
        temp_r31->x40_vel.y = temp_f1_2;
    }
    temp_r31->x40_vel.z = it_804DD9B8;
    temp_r31->xC9C = 0;
    temp_r0 = temp_r31->xDD4_itemVar.capsule.x4;
    switch (temp_r0) { /* irregular */
    case 2:
        temp_r31->xDD4_itemVar.star.x8 += M2C_FIELD(temp_r30, f32*, 0x14);
        break;
    case 3:
        temp_r31->xDD4_itemVar.star.x8 += M2C_FIELD(temp_r30, f32*, 0x20);
        break;
    default:
        temp_r31->xDD4_itemVar.star.x8 += M2C_FIELD(temp_r30, f32*, 8);
        break;
    }
    Item_80268E5C(arg0, 3, ITEM_UNK_0x1);
    return 0;
}

bool it_802F1C68(Item_GObj* gobj)
{
    return false;
}

void it_802F1C70(Item_GObj* arg0)
{
    Item* temp_r5;

    temp_r5 = arg0->user_data;
    temp_r5->x40_vel.x *=
        M2C_FIELD(temp_r5->xC4_article_data->x4_specialAttributes, f32*, 0x34);
    // it_80272860(arg0, temp_r5->xDD4_itemVar.star.x8,
    //             temp_r5->xDD4_itemVar.star.xC);
}

bool it_802F1CB4(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802F1630);
    return false;
}

extern f32 it_804DD9B8;

void it_802F1CE0(Item_GObj* arg0)
{
    HSD_JObj* temp_r30;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    s32 temp_cr0_eq_3;
    s32 temp_r31;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_3;

    temp_r30 = arg0->hsd_obj;
    temp_r31 =
        M2C_ERROR(/* unknown instruction: subi $r31, $r3, %l(it_803F93C8) */);
    if (temp_r30 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x27F, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
    }
    if (temp_r30->flags & 0x20000) {
        //__assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13,
        //%sda21(it_804D5758) */), 0x280, temp_r31 + 0x60);
    }
    temp_r30->rotate.x = it_804DD9B8;
    if (!(temp_r30->flags & 0x02000000)) {
        temp_cr0_eq = temp_r30 == NULL;
        if (temp_cr0_eq == 0) {
            if (temp_cr0_eq != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
            }
            temp_r4 = temp_r30->flags;
            var_r3 = 0;
            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(temp_r30);
            }
        }
    }
    if (temp_r30 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x294, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
    }
    if (temp_r30->flags & 0x20000) {
        //__assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13,
        //%sda21(it_804D5758) */), 0x295, temp_r31 + 0x60);
    }
    temp_r30->rotate.y = it_804DD9B8;
    if (!(temp_r30->flags & 0x02000000)) {
        temp_cr0_eq_2 = temp_r30 == NULL;
        if (temp_cr0_eq_2 == 0) {
            if (temp_cr0_eq_2 != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
            }
            temp_r4_2 = temp_r30->flags;
            var_r3_2 = 0;
            if (!(temp_r4_2 & 0x800000) && (temp_r4_2 & 0x40)) {
                var_r3_2 = 1;
            }
            if (var_r3_2 == 0) {
                HSD_JObjSetMtxDirtySub(temp_r30);
            }
        }
    }
    if (temp_r30 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x2A9, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
    }
    if (temp_r30->flags & 0x20000) {
        //__assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13,
        //%sda21(it_804D5758) */), 0x2AA, temp_r31 + 0x60);
    }
    temp_r30->rotate.z = it_804DD9B8;
    if (!(temp_r30->flags & 0x02000000)) {
        temp_cr0_eq_3 = temp_r30 == NULL;
        if (temp_cr0_eq_3 == 0) {
            if (temp_cr0_eq_3 != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
            }
            temp_r4_3 = temp_r30->flags;
            var_r3_3 = 0;
            if (!(temp_r4_3 & 0x800000) && (temp_r4_3 & 0x40)) {
                var_r3_3 = 1;
            }
            if (var_r3_3 == 0) {
                HSD_JObjSetMtxDirtySub(temp_r30);
            }
        }
    }
    Item_80268E5C(arg0, 4, ITEM_UNK_0x1);
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

void it_802F1F48(Item_GObj* arg0)
{
    Item* temp_r31;
    f32 var_f0;
    s32 var_r4;

    temp_r31 = arg0->user_data;
    Item_80268E5C(arg0, 5, ITEM_ANIM_UPDATE);
    M2C_ERROR(/* unknown instruction: cror eq, gt, eq */);
    if ((M2C_FIELD(temp_r31, f32*, 0x88) +
         (temp_r31->x40_vel.x + M2C_FIELD(temp_r31, f32*, 0x7C))) ==
        it_804DD9B8)
    {
        var_f0 = it_804DD9C4;
    } else {
        var_f0 = it_804DD9C0;
    }
    temp_r31->facing_dir = var_f0;
    if (it_804DD9C0 == temp_r31->facing_dir) {
        var_r4 = -1;
    } else {
        var_r4 = 1;
    }
    mpColl_800436D8(&temp_r31->x378_itemColl, var_r4);
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

void it_802F2014(Item_GObj* gobj, s32 arg1)
{
    GET_ITEM(gobj)->x378_itemColl.x4C = arg1;
}

void* it_802F2020(Item_GObj* gobj)
{
    return &GET_ITEM(gobj)->xDD4_itemVar;
}

void it_802F202C(HSD_GObj* arg0)
{
    void* temp_r31;

    temp_r31 = arg0->user_data;
    lbAudioAx_800237A8(0xAA, 0x7F, 0x40);
    M2C_FIELD(temp_r31, f32*, 0x40) = it_804DD9B8;
    if (M2C_FIELD(temp_r31, f32*, 0x44) < it_804DD9D0) {
        M2C_FIELD(temp_r31, f32*, 0x44) = it_804DD9D0;
    }
    it_802756D0(arg0);
}

void* it_802F2094(s32 arg0, Vec3* arg1, s32 arg2, s32 arg3)
{
    u8 sp60;
    s32 sp5C;
    s16 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r29_2;
    HSD_JObj* temp_r29_3;
    Item* temp_r30;
    Item_GObj* temp_r3;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f31_3;
    f32 temp_r0;
    f32 temp_r0_2;
    s32 temp_cr0_eq;
    s32 temp_cr0_eq_2;
    s32 temp_cr0_eq_3;
    s32 var_r29;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    void* temp_r28;

    sp24 = 0x9F;
    temp_r0 = arg1->y;
    sp3C = arg1->x;
    sp40 = temp_r0;
    temp_r0_2 = arg1->z;
    sp44 = temp_r0_2;
    sp30 = sp3C;
    sp34 = temp_r0;
    sp38 = temp_r0_2;
    sp54 = it_804DD9B8;
    sp50 = it_804DD9B8;
    sp4C = it_804DD9B8;
    sp48 = it_804DD9B8;
    sp58 = 0;
    sp1C = 0;
    sp20 = 0;
    // sp60 |= 0x80;
    sp5C = 0;
    // temp_r3 = Item_80268B18(&sp1C);
    temp_r3 = NULL;
    if (temp_r3 != NULL) {
        temp_r30 = temp_r3->user_data;
        temp_r28 = temp_r30->xC4_article_data->x4_specialAttributes;
        temp_r30->xDD4_itemVar.capsule.x0 = arg2;
        temp_r30->xDD4_itemVar.capsule.x4 = arg3;
        temp_r30->xDD4_itemVar.star.yvel = M2C_BITWISE(f32, arg0);
        if (temp_r30->xDD4_itemVar.capsule.x4 != 0) {
            it_802756E0(temp_r3);
            it_8026B3A8(temp_r3);
            switch (arg3) { /* irregular */
            case 2:
                temp_r30->xDD4_itemVar.star.x8 =
                    M2C_FIELD(temp_r28, f32*, 0xC);
                temp_r30->xDD4_itemVar.star.xC =
                    M2C_FIELD(temp_r28, f32*, 0x10);
                break;
            case 3:
                temp_r30->xDD4_itemVar.star.x8 =
                    M2C_FIELD(temp_r28, f32*, 0x18);
                temp_r30->xDD4_itemVar.star.xC =
                    M2C_FIELD(temp_r28, f32*, 0x1C);
                break;
            default:
                temp_r30->xDD4_itemVar.star.x8 = M2C_FIELD(temp_r28, f32*, 0);
                temp_r30->xDD4_itemVar.star.xC = M2C_FIELD(temp_r28, f32*, 4);
                break;
            }
            var_r29 = un_8031C5E4(arg2);
        } else {
            Item_80267454(temp_r3);
            it_802756D0(temp_r3);
            it_8026B390(temp_r3);
            temp_r30->xD5C = 0;
            var_r29 = un_8031C5E4(arg2);
        }
        HSD_GObjObjet_80390B0C(temp_r3);
        HSD_GObjObjet_80390A70(temp_r3, HSD_GObj_804D7849, var_r29);
        it_8027163C(temp_r3);
        temp_r30->scl = Ground_801C0498();
        temp_r30->scl *= M2C_FIELD(temp_r28, f32*, 0x44);
        temp_r29 = temp_r3->hsd_obj;
        temp_f31 = temp_r30->scl;
        if (temp_r29 == NULL) {
            __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x308, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
        }
        temp_r29->scale.x = temp_f31;
        if (!(temp_r29->flags & 0x02000000)) {
            temp_cr0_eq = temp_r29 == NULL;
            if (temp_cr0_eq == 0) {
                if (temp_cr0_eq != 0) {
                    __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
                }
                temp_r4 = temp_r29->flags;
                var_r3 = 0;
                if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                    var_r3 = 1;
                }
                if (var_r3 == 0) {
                    HSD_JObjSetMtxDirtySub(temp_r29);
                }
            }
        }
        temp_r29_2 = temp_r3->hsd_obj;
        temp_f31_2 = temp_r30->scl;
        if (temp_r29_2 == NULL) {
            __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x317, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
        }
        temp_r29_2->scale.y = temp_f31_2;
        if (!(temp_r29_2->flags & 0x02000000)) {
            temp_cr0_eq_2 = temp_r29_2 == NULL;
            if (temp_cr0_eq_2 == 0) {
                if (temp_cr0_eq_2 != 0) {
                    __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
                }
                temp_r4_2 = temp_r29_2->flags;
                var_r3_2 = 0;
                if (!(temp_r4_2 & 0x800000) && (temp_r4_2 & 0x40)) {
                    var_r3_2 = 1;
                }
                if (var_r3_2 == 0) {
                    HSD_JObjSetMtxDirtySub(temp_r29_2);
                }
            }
        }
        temp_r29_3 = temp_r3->hsd_obj;
        temp_f31_3 = temp_r30->scl;
        if (temp_r29_3 == NULL) {
            __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x326, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
        }
        temp_r29_3->scale.z = temp_f31_3;
        if (!(temp_r29_3->flags & 0x02000000)) {
            temp_cr0_eq_3 = temp_r29_3 == NULL;
            if (temp_cr0_eq_3 == 0) {
                if (temp_cr0_eq_3 != 0) {
                    __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5758) */), 0x234, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5760) */));
                }
                temp_r4_3 = temp_r29_3->flags;
                var_r3_3 = 0;
                if (!(temp_r4_3 & 0x800000) && (temp_r4_3 & 0x40)) {
                    var_r3_3 = 1;
                }
                if (var_r3_3 == 0) {
                    HSD_JObjSetMtxDirtySub(temp_r29_3);
                }
            }
        }
    }
    return temp_r3;
}

ItemStateTable it_803F93C8[] = {
    { -1, it_802F15B0, it_802F15B8, it_802F1604 },
    { -1, it_802F1850, it_802F1858, it_802F185C },
    { -1, it_802F18E4, it_802F18EC, NULL },
    { -1, it_802F1C68, it_802F1C70, it_802F1CB4 },
    { -1, it_802F1EE4, it_802F1EEC, it_802F1F1C },
    { -1, it_802F1FD4, it_802F1FDC, it_802F1FE0 },
};
