#include "itheart.h"

#include "gm/gm_1601.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"
#include "it/types.h"

#include <baselib/gobj.h>

extern f32 it_804DC8A8;
extern f32 it_804DC8AC;
extern s8 it_803F5718;
void it_80283DD4(HSD_GObj* gobj); /* static */
// M2C_UNK it_80283DD4(M2C_UNK, void*, Item*, f32); /* static */
void it_80283C7C(HSD_GObj* gobj); /* static */

HSD_GObj* it_80283AE4(s32 arg0, Vec3* arg1, s32 arg2)
{
    u8 sp5C;
    s32 sp58;
    s16 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    Item* temp_r5;
    Item_GObj* var_r31;
    f32 temp_r0;

    var_r31 = NULL;
    if ((u32) arg0 != 0U) {
        sp20 = 8;
        temp_r0 = arg1->y;
        sp38 = arg1->x;
        sp3C = temp_r0;
        sp40 = arg1->z;
        sp40 = it_804DC8A8;
        sp2C = sp38;
        sp30 = temp_r0;
        sp34 = sp40;
        sp50 = it_804DC8AC;
        sp54 = 0;
        sp4C = it_804DC8A8;
        sp48 = it_804DC8A8;
        sp44 = it_804DC8A8;
        sp18 = 0;
        sp1C = sp18;
        // sp5C |= 0x80;
        sp58 = 0;
        var_r31 = Item_80268B18((SpawnItem*) &sp18);
    }
    if (var_r31 != NULL) {
        temp_r5 = var_r31->user_data;
        temp_r5->xDD4_itemVar.pokemon.padding[4] |= 0x80;
        temp_r5->xDD4_itemVar.star.x8 = M2C_BITWISE(f32, arg2);
        Item_80267454((HSD_GObj*) var_r31);
    }
    return (HSD_GObj*) var_r31;
}

void it_80283BD4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HeartContainerVars* vars = ip->xC4_article_data->x4_specialAttributes;

    ip->xDD4_itemVar.capsule.x0 = vars->xDD8.flags;
}

void it_80283BEC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HeartContainerVars* vars = ip->xC4_article_data->x4_specialAttributes;

    ip->x40_vel.x = 0;
    ip->x40_vel.y = vars->xDE8_float;
    ip->x40_vel.z = 0;
    ip->xDD4_itemVar.HeartContainer.xDD4_heal = vars->xDD4_heal;
    ip->xDD4_itemVar.HeartContainer.xDD8.bits.b0 = 0;
    ip->xDD4_itemVar.HeartContainer.xDDC = 0;
    it_80283DD4(gobj);
}

void it_80283C48(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if ((s8) ((s32) ((ip->xDD4_itemVar.HeartContainer.xDD8.flags << 0x18) &
                     0xC0000000) >>
              0x1F) != 0)
    {
        M2C_FIELD((&gm_80473A18 + ip->xDD4_itemVar.HeartContainer.xDDC), s8*,
                  0x90) = 0;
    }
}

void it_80283C7C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    it_8026B390(gobj);
    ip->x40_vel.x = 0.0F;
    ip->x40_vel.y = 0.0F;
    ip->x40_vel.z = 0.0F;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_80283CD4(Item_GObj* gobj)
{
    HSD_JObj* child;
    f32 rotation_increment;
    bool var_r3;
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    rotation_increment =
        ((f32*) GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes)[6];
    if (child == NULL) {
        __assert("jobj.h", 0x411U, "jobj");
    }
    child->rotate.y += rotation_increment;
    if (!(child->flags & JOBJ_MTX_INDEP_SRT)) {
        if (child != NULL) {
            if (child == NULL) {
                __assert("jobj.h", 0x234U, "jobj");
            }
            var_r3 = false;
            if (!(child->flags & JOBJ_USER_DEF_MTX) &&
                (child->flags & JOBJ_MTX_DIRTY))
            {
                var_r3 = true;
            }
            if (var_r3 == false) {
                HSD_JObjSetMtxDirtySub(child);
            }
        }
    }
    return false;
}

void it_80283DA4(Item_GObj* gobj) {}

bool it_80283DA8(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80283DD4);
    return false;
}

void it_80283DD4(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_80283DFC(Item_GObj* arg0)
{
    HSD_JObj* var_r31;
    f32 temp_f31;
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4_2;
    void* temp_r4;

    temp_r4 = M2C_FIELD(arg0, void**, 0x28);
    if (temp_r4 == NULL) {
        var_r31 = NULL;
    } else {
        var_r31 = M2C_FIELD(temp_r4, HSD_JObj**, 0x10);
    }
    temp_f31 = M2C_FIELD(
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void**, 0x2C), void**, 0xC4),
                  void**, 4),
        f32*, 0x18);
    if (var_r31 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5210) */), 0x411U, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5218) */));
    }
    var_r31->rotate.y += temp_f31;
    if (!(var_r31->flags & 0x02000000)) {
        temp_cr0_eq = var_r31 == NULL;
        if (temp_cr0_eq == 0) {
            if (temp_cr0_eq != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5210) */), 0x234U, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5218) */));
            }
            temp_r4_2 = var_r31->flags;
            var_r3 = 0;
            if (!(temp_r4_2 & 0x800000) && (temp_r4_2 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(var_r31);
            }
        }
    }
    return 0;
}

void it_80283ECC(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_80283EFC(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80283C7C);
    return false;
}

void it_80283F28(Item_GObj* arg0)
{
    HSD_JObj* temp_r3;
    HSD_JObj* var_r31;
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;

    temp_r3 = arg0->hsd_obj;
    if (temp_r3 == NULL) {
        var_r31 = NULL;
    } else {
        var_r31 = temp_r3->child;
    }
    HSD_JObjClearFlagsAll(var_r31, 0x10U);
    if (var_r31 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5210) */), 0x294U, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5218) */));
    }
    if (var_r31->flags & 0x20000) {
        //__assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13,
        //%sda21(it_804D5210) */), 0x295U, &it_803F5718);
    }
    var_r31->rotate.y = it_804DC8A8;
    if (!(var_r31->flags & 0x02000000)) {
        temp_cr0_eq = var_r31 == NULL;
        if (temp_cr0_eq == 0) {
            if (temp_cr0_eq != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5210) */), 0x234U, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5218) */));
            }
            temp_r4 = var_r31->flags;
            var_r3 = 0;
            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(var_r31);
            }
        }
    }
    Item_80268E5C((HSD_GObj*) arg0, 2, ITEM_ANIM_UPDATE);
}

bool it_80284020(Item_GObj* gobj)
{
    return false;
}

void it_80284028(Item_GObj* gobj) {}

void it_8028402C(Item_GObj* arg0)
{
    HSD_JObj* temp_r3;
    HSD_JObj* var_r31;
    s32 temp_cr0_eq;
    s32 var_r3;
    u32 temp_r4;

    temp_r3 = arg0->hsd_obj;
    if (temp_r3 == NULL) {
        var_r31 = NULL;
    } else {
        var_r31 = temp_r3->child;
    }
    it_8026B390(arg0);
    HSD_JObjClearFlagsAll(var_r31, 0x10U);
    if (var_r31 == NULL) {
        __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5210) */), 0x294U, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5218) */));
    }
    if (var_r31->flags & 0x20000) {
        //__assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13,
        //%sda21(it_804D5210) */), 0x295U, &it_803F5718);
    }
    var_r31->rotate.y = it_804DC8A8;
    if (!(var_r31->flags & 0x02000000)) {
        temp_cr0_eq = var_r31 == NULL;
        if (temp_cr0_eq == 0) {
            if (temp_cr0_eq != 0) {
                __assert(M2C_ERROR(/* unknown instruction: subi $r3, $r13, %sda21(it_804D5210) */), 0x234U, M2C_ERROR(/* unknown instruction: subi $r5, $r13, %sda21(it_804D5218) */));
            }
            temp_r4 = var_r31->flags;
            var_r3 = 0;
            if (!(temp_r4 & 0x800000) && (temp_r4 & 0x40)) {
                var_r3 = 1;
            }
            if (var_r3 == 0) {
                HSD_JObjSetMtxDirtySub(var_r31);
            }
        }
    }
    Item_80268E5C((HSD_GObj*) arg0, 3, 6);
}

void it_8028412C(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool it_80284154(Item_GObj* gobj)
{
    return false;
}

void it_8028415C(Item_GObj* gobj) {}

bool it_80284160(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80283C7C, it_80283DD4);
    return false;
}

void it_80284194(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

ItemStateTable it_803F56C8[] = {
    { 0xFFFFFFFF, it_80283CD4, it_80283DA4, it_80283DA8 },
    { 0xFFFFFFFF, it_80283DFC, it_80283ECC, it_80283EFC },
    { 0xFFFFFFFF, it_80284020, it_80284028, NULL },
    { 0xFFFFFFFF, it_80283DFC, it_80283ECC, it_80283EFC },
    { 0xFFFFFFFF, it_80284154, it_8028415C, it_80284160 },
};
