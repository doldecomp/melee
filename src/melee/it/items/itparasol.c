#include "itparasol.h"

#include "math.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/item.h"

// externs
void it_8026D62C(Item_GObj*, HSD_GObjEvent);
void it_8026E15C(Item_GObj*, HSD_GObjEvent);
void it_8026E8C4(Item_GObj*, HSD_GObjEvent, HSD_GObjEvent);

ItemStateTable it_803F5AB0[] = {
    {
        -1,
        it_8028B144,
        it_8028B14C,
        it_8028B150,
    },
    {
        4,
        it_8028B1A4,
        it_8028B2EC,
        it_8028B394,
    },
    {
        0,
        it_8028B1A4,
        it_8028B42C,
        it_8028B394,
    },
    {
        -1,
        it_8028B5A8,
        it_8028B5B0,
        it_8028B5B4,
    },
    {
        1,
        it_8028B60C,
        it_8028B614,
        NULL,
    },
    {
        2,
        it_8028B60C,
        it_8028B614,
        NULL,
    },
    {
        3,
        it_8028B60C,
        it_8028B614,
        NULL,
    },
    {
        4,
        it_8028B60C,
        it_8028B614,
        NULL,
    },
    {
        5,
        it_8028B60C,
        it_8028B614,
        NULL,
    },
    {
        6,
        it_8028B60C,
        it_8028B614,
        NULL,
    },
    {
        7,
        it_8028B60C,
        it_8028B614,
        NULL,
    },
};

int it_8028B08C(Item_GObj* item_gobj, int statenum)
{
    static int it_803F5B60[] = {
        20, 16, 45, 2, 20, 30, 40, 16,
    };
    return it_803F5B60[it_803F5AB0[statenum].anim_id];
}

void it_8028B0B8(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->xDCE_flag.bits.b7 = false;
    it_8028B17C(item_gobj);
}

void it_8028B0EC(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    it_8026B390(item_gobj);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0F;
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_8028B144(Item_GObj* item_gobj)
{
    return false;
}

void it_8028B14C(Item_GObj* item_gobj) {}

bool it_8028B150(Item_GObj* item_gobj)
{
    it_8026D62C(item_gobj, it_8028B17C);
    return false;
}

void it_8028B17C(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
}

static inline f32 fabsf(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return +x;
    }
}

static inline HSD_JObj* jobj_child(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    } else {
        return jobj->child;
    }
}

#ifdef MUST_MATCH

static char it_804D5260[8] = "jobj.h";
static char it_804D5268[8] = "jobj";
static char it_803F5B80[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";

#pragma push
asm bool it_8028B1A4(Item_GObj* item_gobj)
{ // clang-format off
    nofralloc
/* 8028B1A4 00287D84  7C 08 02 A6 */	mflr r0
/* 8028B1A8 00287D88  90 01 00 04 */	stw r0, 4(r1)
/* 8028B1AC 00287D8C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8028B1B0 00287D90  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8028B1B4 00287D94  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8028B1B8 00287D98  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8028B1BC 00287D9C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8028B1C0 00287DA0  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8028B1C4 00287DA4  80 83 00 28 */	lwz r4, 0x28(r3)
/* 8028B1C8 00287DA8  80 7E 00 C4 */	lwz r3, 0xc4(r30)
/* 8028B1CC 00287DAC  28 04 00 00 */	cmplwi r4, 0
/* 8028B1D0 00287DB0  83 A3 00 04 */	lwz r29, 4(r3)
/* 8028B1D4 00287DB4  41 82 00 F4 */	beq lbl_8028B2C8
/* 8028B1D8 00287DB8  40 82 00 0C */	bne lbl_8028B1E4
/* 8028B1DC 00287DBC  3B E0 00 00 */	li r31, 0
/* 8028B1E0 00287DC0  48 00 00 08 */	b lbl_8028B1E8
lbl_8028B1E4:
/* 8028B1E4 00287DC4  83 E4 00 10 */	lwz r31, 0x10(r4)
lbl_8028B1E8:
/* 8028B1E8 00287DC8  28 1F 00 00 */	cmplwi r31, 0
/* 8028B1EC 00287DCC  40 82 00 14 */	bne lbl_8028B200
/* 8028B1F0 00287DD0  38 6D 9B C0 */	addi r3, r13, it_804D5260
/* 8028B1F4 00287DD4  38 80 02 DA */	li r4, 0x2da
/* 8028B1F8 00287DD8  38 AD 9B C8 */	addi r5, r13, it_804D5268
/* 8028B1FC 00287DDC  48 0F D0 25 */	bl __assert
lbl_8028B200:
/* 8028B200 00287DE0  C0 5E 00 44 */	lfs f2, 0x44(r30)
/* 8028B204 00287DE4  C0 3D 00 0C */	lfs f1, 0xc(r29)
/* 8028B208 00287DE8  C0 02 D0 48 */	lfs f0, 0.0F
/* 8028B20C 00287DEC  EC 42 00 72 */	fmuls f2, f2, f1
/* 8028B210 00287DF0  C3 FF 00 20 */	lfs f31, 0x20(r31)
/* 8028B214 00287DF4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8028B218 00287DF8  40 80 00 08 */	bge lbl_8028B220
/* 8028B21C 00287DFC  FC 40 10 50 */	fneg f2, f2
lbl_8028B220:
/* 8028B220 00287E00  C0 1D 00 08 */	lfs f0, 8(r29)
/* 8028B224 00287E04  28 1F 00 00 */	cmplwi r31, 0
/* 8028B228 00287E08  C0 3E 00 2C */	lfs f1, 0x2c(r30)
/* 8028B22C 00287E0C  EC 40 10 2A */	fadds f2, f0, f2
/* 8028B230 00287E10  C0 02 D0 4C */	lfs f0, deg_to_rad
/* 8028B234 00287E14  EC 42 00 72 */	fmuls f2, f2, f1
/* 8028B238 00287E18  EF E0 F8 BA */	fmadds f31, f0, f2, f31
/* 8028B23C 00287E1C  40 82 00 14 */	bne lbl_8028B250
/* 8028B240 00287E20  38 6D 9B C0 */	addi r3, r13, it_804D5260
/* 8028B244 00287E24  38 80 02 94 */	li r4, 0x294
/* 8028B248 00287E28  38 AD 9B C8 */	addi r5, r13, it_804D5268
/* 8028B24C 00287E2C  48 0F CF D5 */	bl __assert
lbl_8028B250:
/* 8028B250 00287E30  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8028B254 00287E34  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 8028B258 00287E38  41 82 00 18 */	beq lbl_8028B270
/* 8028B25C 00287E3C  3C 60 80 3F */	lis r3, it_803F5B80@ha
/* 8028B260 00287E40  38 A3 5B 80 */	addi r5, r3, it_803F5B80@l
/* 8028B264 00287E44  38 6D 9B C0 */	addi r3, r13, it_804D5260
/* 8028B268 00287E48  38 80 02 95 */	li r4, 0x295
/* 8028B26C 00287E4C  48 0F CF B5 */	bl __assert
lbl_8028B270:
/* 8028B270 00287E50  D3 FF 00 20 */	stfs f31, 0x20(r31)
/* 8028B274 00287E54  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8028B278 00287E58  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8028B27C 00287E5C  40 82 00 4C */	bne lbl_8028B2C8
/* 8028B280 00287E60  28 1F 00 00 */	cmplwi r31, 0
/* 8028B284 00287E64  41 82 00 44 */	beq lbl_8028B2C8
/* 8028B288 00287E68  40 82 00 14 */	bne lbl_8028B29C
/* 8028B28C 00287E6C  38 6D 9B C0 */	addi r3, r13, it_804D5260
/* 8028B290 00287E70  38 80 02 34 */	li r4, 0x234
/* 8028B294 00287E74  38 AD 9B C8 */	addi r5, r13, it_804D5268
/* 8028B298 00287E78  48 0F CF 89 */	bl __assert
lbl_8028B29C:
/* 8028B29C 00287E7C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8028B2A0 00287E80  38 60 00 00 */	li r3, 0
/* 8028B2A4 00287E84  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8028B2A8 00287E88  40 82 00 10 */	bne lbl_8028B2B8
/* 8028B2AC 00287E8C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8028B2B0 00287E90  41 82 00 08 */	beq lbl_8028B2B8
/* 8028B2B4 00287E94  38 60 00 01 */	li r3, 1
lbl_8028B2B8:
/* 8028B2B8 00287E98  2C 03 00 00 */	cmpwi r3, 0
/* 8028B2BC 00287E9C  40 82 00 0C */	bne lbl_8028B2C8
/* 8028B2C0 00287EA0  7F E3 FB 78 */	mr r3, r31
/* 8028B2C4 00287EA4  48 0E 80 25 */	bl HSD_JObjSetMtxDirtySub
lbl_8028B2C8:
/* 8028B2C8 00287EA8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8028B2CC 00287EAC  38 60 00 00 */	li r3, 0
/* 8028B2D0 00287EB0  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 8028B2D4 00287EB4  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8028B2D8 00287EB8  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8028B2DC 00287EBC  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8028B2E0 00287EC0  38 21 00 38 */	addi r1, r1, 0x38
/* 8028B2E4 00287EC4  7C 08 03 A6 */	mtlr r0
/* 8028B2E8 00287EC8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

bool it_8028B1A4(Item_GObj* item_gobj)
{
    Item* item = item = GET_ITEM(item_gobj);
    f32* attrs = item->xC4_article_data->x4_specialAttributes;
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    if (jobj != NULL) {
        f32 ry;
        f32 var_f2;
        jobj = jobj_child(jobj);
        ry = HSD_JObjGetRotationY(jobj);
        var_f2 = fabsf(item->x40_vel.y * attrs[3]);
        ry += deg_to_rad * ((attrs[2] + var_f2) * item->facing_dir);
        HSD_JObjSetRotationY(jobj, ry);
    }
    return false;
}

#endif

inline void decelerateItemX(Item* item, f32 decel_x)
{
    if (fabsf(item->x40_vel.x) > decel_x) {
        if (item->x40_vel.x > decel_x) {
            item->x40_vel.x -= decel_x;
        }
        if (item->x40_vel.x < -decel_x) {
            item->x40_vel.x += decel_x;
        }
    } else {
        item->x40_vel.x = 0.0F;
    }
}

void it_8028B2EC(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    ItemAttr* attr = item->xCC_item_attr;
    f32* attrs = item->xC4_article_data->x4_specialAttributes;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    decelerateItemX(item, attrs[0]);
}

bool it_8028B394(Item_GObj* item_gobj)
{
    it_8026E15C(item_gobj, it_8028B0EC);
    return false;
}

void it_8028B3C0(Item_GObj* item_gobj)
{
    it_8028B3E0(item_gobj);
}

void it_8028B3E0(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    Item_8026AE84(item, 0xF7, 0x7F, 0x40);
    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void it_8028B42C(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    ItemAttr* attr = item->xCC_item_attr;
    f32* attrs = item->xC4_article_data->x4_specialAttributes;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    decelerateItemX(item, attrs[1]);
}

bool it_8028B4D4(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return false;
}

bool it_8028B4F8(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return false;
}

bool it_8028B51C(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return false;
}

bool it_8028B540(Item_GObj* item_gobj)
{
    return it_80273030(item_gobj);
}

bool it_8028B560(Item_GObj* item_gobj)
{
    return itColl_BounceOffShield(item_gobj);
}

void it_8028B580(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 3, ITEM_ANIM_UPDATE);
}

bool it_8028B5A8(Item_GObj* item_gobj)
{
    return false;
}

void it_8028B5B0(Item_GObj* item_gobj) {}

bool it_8028B5B4(Item_GObj* item_gobj)
{
    it_8026E8C4(item_gobj, it_8028B0EC, it_8028B17C);
    return false;
}

void it_8028B5E8(Item_GObj* item_gobj)
{
    it_8028B618(item_gobj, 1.0F);
}

bool it_8028B60C(Item_GObj* item_gobj)
{
    return false;
}

void it_8028B614(Item_GObj* item_gobj) {}

static inline void animSpeed(Item_GObj* item_gobj, f32 speed, int statenum)
{
    Item* item = GET_ITEM(item_gobj);
    if (statenum > 4) {
        Item_8026AE84(item, 0xF7, 0x7F, 0x40);
    }
    item->x5D0_animFrameSpeed = speed;
    Item_80268E5C(item_gobj, statenum, ITEM_ANIM_UPDATE);
}

void it_8028B618(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 4);
}

void it_8028B648(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 5);
}

void it_8028B6B0(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 6);
}

void it_8028B718(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 7);
}

void it_8028B780(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 8);
}

void it_8028B7E8(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 9);
}

void it_8028B850(Item_GObj* item_gobj, f32 speed)
{
    animSpeed(item_gobj, speed, 10);
}

void it_8028B8B8(Item_GObj* item_gobj, HSD_GObj* arg1)
{
    it_8026B894(item_gobj, arg1);
}
