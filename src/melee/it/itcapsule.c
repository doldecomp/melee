#include "itcapsule.h"

#include "it_266F.h"
#include "it_26B1.h"
#include "item.h"

#include <melee/lb/lb_00F9.h>

void it_8026D62C(Item_GObj*, HSD_GObjEvent);
void it_8026E15C(Item_GObj*, HSD_GObjEvent);
void it_8026E414(Item_GObj*, HSD_GObjEvent);
void it_8026F3D4(Item_GObj*, int, bool, int);
bool it_8026F8B4(Item_GObj*, Vec3*, Vec3*, int);
void it_80272860(Item_GObj*, f32, f32);
void it_80272C08();
void it_80273454();
void it_80274658(Item_GObj*, f32);
void it_8027518C();
bool it_802751D8(Item_GObj*);
void it_80275444();
void it_802756D0();
void it_8027D258(Item_GObj*);
void it_8027D2DC();
void it_8026E8C4(Item_GObj*, HSD_GObjEvent, HSD_GObjEvent);
void itColl_BounceOffShield(Item_GObj*);

ItemStateTable it_803F5468[] = {
    {
        -1,
        it_8027D110,
        it_8027D118,
        it_8027D11C,
    },
    {
        -1,
        it_8027D170,
        it_8027D178,
        it_8027D1A8,
    },
    {
        -1,
        it_8027D1FC,
        it_8027D204,
        NULL,
    },
    {
        0,
        it_8027D170,
        it_8027D258,
        it_8027D2A4,
    },
    {
        0,
        it_8027D170,
        it_8027D178,
        it_8027D1A8,
    },
    {
        1,
        it_8027D30C,
        it_8027D32C,
        it_8027D330,
    },
    {
        -1,
        it_8027D478,
        it_8027D480,
        it_8027D484,
    },
};

void it_8027CF30(Item_GObj* gobj)
{
    Vec3 sp18;
    u32 unused[1];

    Item* it = GetItemData(gobj);
    ItCapsuleAttrs* capsule = it->xC4_article_data->x4_specialAttributes;

    sp18.x = sp18.y = sp18.z = 0.0F;
    if (!it_8026F8B4(gobj, &it->pos, &sp18, 0)) {
        if (!HSD_Randi(capsule->x4)) {
            it_8027D2DC(gobj);
            it->xDD4_itemVar.capsule.x0 = false;
        } else {
            it_8026F3D4(gobj, 0, capsule->x0, 0);
            it->xDD4_itemVar.capsule.x0 = true;
        }
    } else {
        it->xDD4_itemVar.capsule.x0 = true;
    }
}

void it_8027CFE8(Item_GObj* item_gobj)
{
    u32 unused1[1];
    HSD_JObj* jobj = (HSD_JObj*) HSD_GObjGetHSDObj(item_gobj);
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);
    Vec3 sp14;

    it_8026B3A8(item_gobj);
    HSD_JObjSetFlagsAll(jobj, 0x10);
    it->x5D0_animFrameSpeed = 1.0F;
    it_80273454(item_gobj);
    it->xDD4_itemVar.capsule.x4 = true;
    it_80272C08(item_gobj);
    it_80275444(item_gobj);
    it_802756D0(item_gobj);
    it_8026BD24(item_gobj);
    it_8027518C(item_gobj);
    sp14 = it->pos;
    lb_800119DC(&sp14, 0x78, 1.0F, 0.02F, 60 * M_PI / 180);
    Item_80268E5C(item_gobj, 5, 2);
}

void it_8027D0B8(Item_GObj* gobj)
{
    Item* it = GetItemData(gobj);
    it_8026B390(gobj);
    it->x40_vel.x = it->x40_vel.y = it->x40_vel.z = 0.0F;
    Item_80268E5C(gobj, 0, 2);
}

bool it_8027D110(Item_GObj* gobj)
{
    return false;
}

void it_8027D118(Item_GObj* gobj) {}

bool it_8027D11C(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8027D148);
    return false;
}

void it_8027D148(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 2);
}

bool it_8027D170(Item_GObj* gobj)
{
    return false;
}

void it_8027D178(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    ItemAttr* attr = it->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_8027D1A8(Item_GObj* gobj)
{
    it_8026E15C(gobj, &it_8027D0B8);
    return 0;
}

void it_8027D1D4(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, 2);
}

bool it_8027D1FC(Item_GObj* gobj)
{
    return false;
}

void it_8027D204(Item_GObj* gobj) {}

void it_8027D208(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

void it_8027D230(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void it_8027D258(Item_GObj* item_gobj)
{
    it_8027D178(item_gobj);
    it_80274658(item_gobj, it_804D6D28->x68_float);
}

bool it_8027D2A4(Item_GObj* item_gobj)
{
    Item* it = item_gobj->user_data;
    it_8026E414(item_gobj, it_8027CF30);
    return it->xDD4_itemVar.capsule.x0;
}

void it_8027D2DC(Item_GObj* item_gobj)
{
    Item* it = item_gobj->user_data;
    if (!it->xDD4_itemVar.capsule.x4) {
        it_8027CFE8(item_gobj);
    }
}

bool it_8027D30C(Item_GObj* item_gobj)
{
    return it_802751D8(item_gobj);
}

void it_8027D32C(Item_GObj*) {}

bool it_8027D330(Item_GObj*)
{
    return false;
}

#ifndef MUST_MATCH
// Incorrect stack offsets for inlined it_8027CF30
bool it_8027D338(HSD_GObj* item_gobj)
{
    Item* it = (Item*) HSD_GObjGetUserData(item_gobj);
    u32 unused[1];

    if (it->msid != 5) {
        it_8027CF30(item_gobj);
    }
    return it->xDD4_itemVar.capsule.x0;
}
#else
#pragma push
asm bool it_8027D338(Item_GObj*)
{ // clang-format off
    nofralloc
/* 8027D338 00279F18  7C 08 02 A6 */	mflr r0
/* 8027D33C 00279F1C  90 01 00 04 */	stw r0, 4(r1)
/* 8027D340 00279F20  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8027D344 00279F24  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8027D348 00279F28  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8027D34C 00279F2C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8027D350 00279F30  7C 7D 1B 78 */	mr r29, r3
/* 8027D354 00279F34  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8027D358 00279F38  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 8027D35C 00279F3C  2C 00 00 05 */	cmpwi r0, 5
/* 8027D360 00279F40  41 82 00 94 */	beq lbl_8027D3F4
/* 8027D364 00279F44  80 BE 00 C4 */	lwz r5, 0xc4(r30)
/* 8027D368 00279F48  7F A3 EB 78 */	mr r3, r29
/* 8027D36C 00279F4C  C0 02 CE 50 */	lfs f0, 0.0F
/* 8027D370 00279F50  38 9E 00 4C */	addi r4, r30, 0x4c
/* 8027D374 00279F54  83 E5 00 04 */	lwz r31, 4(r5)
/* 8027D378 00279F58  38 A1 00 20 */	addi r5, r1, 0x20
/* 8027D37C 00279F5C  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8027D380 00279F60  38 C0 00 00 */	li r6, 0
/* 8027D384 00279F64  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8027D388 00279F68  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8027D38C 00279F6C  4B FF 25 29 */	bl it_8026F8B4
/* 8027D390 00279F70  2C 03 00 00 */	cmpwi r3, 0
/* 8027D394 00279F74  40 82 00 58 */	bne lbl_8027D3EC
/* 8027D398 00279F78  80 7F 00 04 */	lwz r3, 4(r31)
/* 8027D39C 00279F7C  48 10 31 E5 */	bl HSD_Randi
/* 8027D3A0 00279F80  2C 03 00 00 */	cmpwi r3, 0
/* 8027D3A4 00279F84  40 82 00 28 */	bne lbl_8027D3CC
/* 8027D3A8 00279F88  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8027D3AC 00279F8C  80 03 0D D8 */	lwz r0, 0xdd8(r3)
/* 8027D3B0 00279F90  2C 00 00 00 */	cmpwi r0, 0
/* 8027D3B4 00279F94  40 82 00 0C */	bne lbl_8027D3C0
/* 8027D3B8 00279F98  7F A3 EB 78 */	mr r3, r29
/* 8027D3BC 00279F9C  4B FF FC 2D */	bl it_8027CFE8
lbl_8027D3C0:
/* 8027D3C0 00279FA0  38 00 00 00 */	li r0, 0
/* 8027D3C4 00279FA4  90 1E 0D D4 */	stw r0, 0xdd4(r30)
/* 8027D3C8 00279FA8  48 00 00 2C */	b lbl_8027D3F4
lbl_8027D3CC:
/* 8027D3CC 00279FAC  80 BF 00 00 */	lwz r5, 0(r31)
/* 8027D3D0 00279FB0  38 7D 00 00 */	addi r3, r29, 0
/* 8027D3D4 00279FB4  38 80 00 00 */	li r4, 0
/* 8027D3D8 00279FB8  38 C0 00 00 */	li r6, 0
/* 8027D3DC 00279FBC  4B FF 1F F9 */	bl it_8026F3D4
/* 8027D3E0 00279FC0  38 00 00 01 */	li r0, 1
/* 8027D3E4 00279FC4  90 1E 0D D4 */	stw r0, 0xdd4(r30)
/* 8027D3E8 00279FC8  48 00 00 0C */	b lbl_8027D3F4
lbl_8027D3EC:
/* 8027D3EC 00279FCC  38 00 00 01 */	li r0, 1
/* 8027D3F0 00279FD0  90 1E 0D D4 */	stw r0, 0xdd4(r30)
lbl_8027D3F4:
/* 8027D3F4 00279FD4  80 7E 0D D4 */	lwz r3, 0xdd4(r30)
/* 8027D3F8 00279FD8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8027D3FC 00279FDC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8027D400 00279FE0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8027D404 00279FE4  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8027D408 00279FE8  38 21 00 40 */	addi r1, r1, 0x40
/* 8027D40C 00279FEC  7C 08 03 A6 */	mtlr r0
/* 8027D410 00279FF0  4E 80 00 20 */	blr
} // clang-format off
#pragma pop
#endif

bool it_8027D338_autoinlined(Item_GObj* item_gobj);

bool it_8027D338_autoinlined(Item_GObj* item_gobj)
{
    Item* it = item_gobj->user_data;
    if (it->msid != 5) {
        it_8027CF30(item_gobj);
    }
    return it->xDD4_itemVar.capsule.x0;
}

bool it_8027D414(Item_GObj* item_gobj) {
    return it_8027D338_autoinlined(item_gobj);
}

void it_8027D450(Item_GObj* item_gobj) {
    Item_80268E5C(item_gobj, 6, ITEM_ANIM_UPDATE);
}

bool it_8027D478(Item_GObj*)
{
    return false;
}

void it_8027D480(Item_GObj*)
{
}

bool it_8027D484(Item_GObj* item_gobj)
{
    it_8026E8C4(item_gobj, it_8027D0B8, it_8027D148);
    return false;
}

bool it_8027D4B8(Item_GObj* item_gobj)
{
    return it_8027D338_autoinlined(item_gobj);
}

bool it_8027D4F4(Item_GObj* item_gobj)
{
    return it_8027D338_autoinlined(item_gobj);
}

#pragma push
asm bool it_8027D530(Item_GObj* item_gobj)
{ // clang-format off
    nofralloc
/* 8027D530 0027A110  7C 08 02 A6 */	mflr r0
/* 8027D534 0027A114  90 01 00 04 */	stw r0, 4(r1)
/* 8027D538 0027A118  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8027D53C 0027A11C  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8027D540 0027A120  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8027D544 0027A124  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8027D548 0027A128  7C 7D 1B 78 */	mr r29, r3
/* 8027D54C 0027A12C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8027D550 0027A130  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 8027D554 0027A134  2C 00 00 03 */	cmpwi r0, 3
/* 8027D558 0027A138  40 82 00 9C */	bne lbl_8027D5F4
/* 8027D55C 0027A13C  80 BE 00 C4 */	lwz r5, 0xc4(r30)
/* 8027D560 0027A140  7F A3 EB 78 */	mr r3, r29
/* 8027D564 0027A144  C0 02 CE 50 */	lfs f0, 0.0F
/* 8027D568 0027A148  38 9E 00 4C */	addi r4, r30, 0x4c
/* 8027D56C 0027A14C  83 E5 00 04 */	lwz r31, 4(r5)
/* 8027D570 0027A150  38 A1 00 20 */	addi r5, r1, 0x20
/* 8027D574 0027A154  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8027D578 0027A158  38 C0 00 00 */	li r6, 0
/* 8027D57C 0027A15C  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 8027D580 0027A160  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8027D584 0027A164  4B FF 23 31 */	bl it_8026F8B4
/* 8027D588 0027A168  2C 03 00 00 */	cmpwi r3, 0
/* 8027D58C 0027A16C  40 82 00 58 */	bne lbl_8027D5E4
/* 8027D590 0027A170  80 7F 00 04 */	lwz r3, 4(r31)
/* 8027D594 0027A174  48 10 2F ED */	bl HSD_Randi
/* 8027D598 0027A178  2C 03 00 00 */	cmpwi r3, 0
/* 8027D59C 0027A17C  40 82 00 28 */	bne lbl_8027D5C4
/* 8027D5A0 0027A180  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8027D5A4 0027A184  80 03 0D D8 */	lwz r0, 0xdd8(r3)
/* 8027D5A8 0027A188  2C 00 00 00 */	cmpwi r0, 0
/* 8027D5AC 0027A18C  40 82 00 0C */	bne lbl_8027D5B8
/* 8027D5B0 0027A190  7F A3 EB 78 */	mr r3, r29
/* 8027D5B4 0027A194  4B FF FA 35 */	bl it_8027CFE8
lbl_8027D5B8:
/* 8027D5B8 0027A198  38 00 00 00 */	li r0, 0
/* 8027D5BC 0027A19C  90 1E 0D D4 */	stw r0, 0xdd4(r30)
/* 8027D5C0 0027A1A0  48 00 00 2C */	b lbl_8027D5EC
lbl_8027D5C4:
/* 8027D5C4 0027A1A4  80 BF 00 00 */	lwz r5, 0(r31)
/* 8027D5C8 0027A1A8  38 7D 00 00 */	addi r3, r29, 0
/* 8027D5CC 0027A1AC  38 80 00 00 */	li r4, 0
/* 8027D5D0 0027A1B0  38 C0 00 00 */	li r6, 0
/* 8027D5D4 0027A1B4  4B FF 1E 01 */	bl it_8026F3D4
/* 8027D5D8 0027A1B8  38 00 00 01 */	li r0, 1
/* 8027D5DC 0027A1BC  90 1E 0D D4 */	stw r0, 0xdd4(r30)
/* 8027D5E0 0027A1C0  48 00 00 0C */	b lbl_8027D5EC
lbl_8027D5E4:
/* 8027D5E4 0027A1C4  38 00 00 01 */	li r0, 1
/* 8027D5E8 0027A1C8  90 1E 0D D4 */	stw r0, 0xdd4(r30)
lbl_8027D5EC:
/* 8027D5EC 0027A1CC  80 7E 0D D4 */	lwz r3, 0xdd4(r30)
/* 8027D5F0 0027A1D0  48 00 00 08 */	b lbl_8027D5F8
lbl_8027D5F4:
/* 8027D5F4 0027A1D4  38 60 00 00 */	li r3, 0
lbl_8027D5F8:
/* 8027D5F8 0027A1D8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8027D5FC 0027A1DC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8027D600 0027A1E0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8027D604 0027A1E4  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8027D608 0027A1E8  38 21 00 40 */	addi r1, r1, 0x40
/* 8027D60C 0027A1EC  7C 08 03 A6 */	mtlr r0
/* 8027D610 0027A1F0  4E 80 00 20 */	blr
} // clang-format off
#pragma pop

bool it_8027D614(Item_GObj* item_gobj)
{
    Item* it = item_gobj->user_data;
    if (it->msid == 3 || it->msid == 4) {
        itColl_BounceOffShield(item_gobj);
    }
    return 0;
}

void it_8027D650(Item_GObj* item_gobj, HSD_GObj* ref)
{
    it_8026B894(item_gobj, ref);
}
