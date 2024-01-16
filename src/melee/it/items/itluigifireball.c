#include "itluigifireball.h"

#include "db/db_2253.h"
#include "ef/efasync.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "lb/lbvector.h"

#include <dolphin/mtx/vec.h>

/* 2C027C */ static void it_802C027C(Item_GObj* gobj);
/* 2C02E4 */ static bool it_802C02E4(Item_GObj* gobj);
/* 2C031C */ static void it_802C031C(Item_GObj* gobj);
/* 2C0368 */ static bool it_802C0368(Item_GObj* gobj);

ItemStateTable it_803F75C0[] = {
    { 0, it_802C02E4, it_802C031C, it_802C0368 },
};

void it_802C01AC(Item_GObj* gobj, Vec3* pos, ItemKind kind, float facing_dir)
{
    SpawnItem spawn_item;
    spawn_item.kind = kind;
    spawn_item.prev_pos = *pos;
    spawn_item.prev_pos.z = 0;
    it_8026BB68(gobj, &spawn_item.pos);
    spawn_item.facing_dir = facing_dir;
    spawn_item.x3C_damage = 0;
    spawn_item.vel.x = spawn_item.vel.y = spawn_item.vel.z = 0;
    spawn_item.x0_parent_gobj = gobj;
    spawn_item.x4_parent_gobj2 = spawn_item.x0_parent_gobj;
    spawn_item.x44_flag.bits.b0 = true;
    spawn_item.x40 = 0;
    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[8] = { 0 };
#endif
        Item_GObj* spawned_gobj = Item_80268B18(&spawn_item);
        if (spawned_gobj != NULL) {
            it_802C027C(spawned_gobj);
            db_80225DD8(spawned_gobj, gobj);
            it_802750F8(spawned_gobj);
        }
    }
}

void it_802C027C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itUnkAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = attrs->x0_float * ip->facing_dir;
    ip->x40_vel.y = ip->x40_vel.z = 0;
    it_80275158(gobj, attrs->x4_float);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_802C02E4(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    --item->xD44_lifeTimer;
    return item->xD44_lifeTimer <= 0 ? true : false;
}

void it_802C031C(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

ASM bool it_802C0368(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    it_8026D9A0(gobj);
    if (it_8027781C(gobj)) {
        Item* ip = GET_ITEM(gobj);
        HSD_JObj* jobj = GET_JOBJ(gobj);
        itUnkAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[12] = { 0 };
#endif
        if (sqrtf_accurate(VEC2_SQ_LEN(ip->x40_vel)) < attrs->xC) {
            return true;
        }
        /// @todo Missing #efAsync_Spawn param?
        if (ip->kind == It_Kind_Luigi_Fire) {
            efAsync_Spawn(gobj, &(GET_ITEM(gobj)->xBC0), 1, 1288, jobj);
        } else {
            efAsync_Spawn(gobj, &(GET_ITEM(gobj)->xBC0), 1, 1202, jobj);
        }
    }
    return false;
}

#else /* clang-format off */
{ nofralloc
/* 802C0368 002BCF48  7C 08 02 A6 */	mflr r0
/* 802C036C 002BCF4C  90 01 00 04 */	stw r0, 4(r1)
/* 802C0370 002BCF50  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802C0374 002BCF54  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802C0378 002BCF58  7C 7F 1B 78 */	mr r31, r3
/* 802C037C 002BCF5C  4B FA D6 25 */	bl it_8026D9A0
/* 802C0380 002BCF60  7F E3 FB 78 */	mr r3, r31
/* 802C0384 002BCF64  4B FB 74 99 */	bl it_8027781C
/* 802C0388 002BCF68  2C 03 00 00 */	cmpwi r3, 0
/* 802C038C 002BCF6C  41 82 00 EC */	beq lbl_802C0478
/* 802C0390 002BCF70  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 802C0394 002BCF74  C0 02 D7 A8 */	lfs f0, 0.0f
/* 802C0398 002BCF78  C0 44 00 40 */	lfs f2, 0x40(r4)
/* 802C039C 002BCF7C  C0 24 00 44 */	lfs f1, 0x44(r4)
/* 802C03A0 002BCF80  EC 42 00 B2 */	fmuls f2, f2, f2
/* 802C03A4 002BCF84  80 64 00 C4 */	lwz r3, 0xc4(r4)
/* 802C03A8 002BCF88  EC 21 00 72 */	fmuls f1, f1, f1
/* 802C03AC 002BCF8C  80 FF 00 28 */	lwz r7, 0x28(r31)
/* 802C03B0 002BCF90  80 63 00 04 */	lwz r3, 4(r3)
/* 802C03B4 002BCF94  EC 82 08 2A */	fadds f4, f2, f1
/* 802C03B8 002BCF98  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 802C03BC 002BCF9C  40 81 00 60 */	ble lbl_802C041C
/* 802C03C0 002BCFA0  FC 20 20 34 */	frsqrte f1, f4
/* 802C03C4 002BCFA4  C8 62 D7 B0 */	lfd f3, 0.5
/* 802C03C8 002BCFA8  C8 42 D7 B8 */	lfd f2, 3.0
/* 802C03CC 002BCFAC  FC 01 00 72 */	fmul f0, f1, f1
/* 802C03D0 002BCFB0  FC 23 00 72 */	fmul f1, f3, f1
/* 802C03D4 002BCFB4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 802C03D8 002BCFB8  FC 21 00 32 */	fmul f1, f1, f0
/* 802C03DC 002BCFBC  FC 01 00 72 */	fmul f0, f1, f1
/* 802C03E0 002BCFC0  FC 23 00 72 */	fmul f1, f3, f1
/* 802C03E4 002BCFC4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 802C03E8 002BCFC8  FC 21 00 32 */	fmul f1, f1, f0
/* 802C03EC 002BCFCC  FC 01 00 72 */	fmul f0, f1, f1
/* 802C03F0 002BCFD0  FC 23 00 72 */	fmul f1, f3, f1
/* 802C03F4 002BCFD4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 802C03F8 002BCFD8  FC 21 00 32 */	fmul f1, f1, f0
/* 802C03FC 002BCFDC  FC 01 00 72 */	fmul f0, f1, f1
/* 802C0400 002BCFE0  FC 23 00 72 */	fmul f1, f3, f1
/* 802C0404 002BCFE4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 802C0408 002BCFE8  FC 01 00 32 */	fmul f0, f1, f0
/* 802C040C 002BCFEC  FC 04 00 32 */	fmul f0, f4, f0
/* 802C0410 002BCFF0  FC 00 00 18 */	frsp f0, f0
/* 802C0414 002BCFF4  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 802C0418 002BCFF8  C0 81 00 20 */	lfs f4, 0x20(r1)
lbl_802C041C:
/* 802C041C 002BCFFC  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 802C0420 002BD000  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 802C0424 002BD004  40 80 00 0C */	bge lbl_802C0430
/* 802C0428 002BD008  38 60 00 01 */	li r3, 1
/* 802C042C 002BD00C  48 00 00 50 */	b lbl_802C047C
lbl_802C0430:
/* 802C0430 002BD010  80 04 00 10 */	lwz r0, 0x10(r4)
/* 802C0434 002BD014  2C 00 00 69 */	cmpwi r0, 0x69
/* 802C0438 002BD018  40 82 00 24 */	bne lbl_802C045C
/* 802C043C 002BD01C  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 802C0440 002BD020  38 7F 00 00 */	addi r3, r31, 0
/* 802C0444 002BD024  4C C6 31 82 */	crclr 6
/* 802C0448 002BD028  38 A0 00 01 */	li r5, 1
/* 802C044C 002BD02C  38 84 0B C0 */	addi r4, r4, 0xbc0
/* 802C0450 002BD030  38 C0 05 08 */	li r6, 0x508
/* 802C0454 002BD034  4B DA 72 9D */	bl efAsync_Spawn
/* 802C0458 002BD038  48 00 00 20 */	b lbl_802C0478
lbl_802C045C:
/* 802C045C 002BD03C  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 802C0460 002BD040  38 7F 00 00 */	addi r3, r31, 0
/* 802C0464 002BD044  4C C6 31 82 */	crclr 6
/* 802C0468 002BD048  38 A0 00 01 */	li r5, 1
/* 802C046C 002BD04C  38 84 0B C0 */	addi r4, r4, 0xbc0
/* 802C0470 002BD050  38 C0 04 B2 */	li r6, 0x4b2
/* 802C0474 002BD054  4B DA 72 7D */	bl efAsync_Spawn
lbl_802C0478:
/* 802C0478 002BD058  38 60 00 00 */	li r3, 0
lbl_802C047C:
/* 802C047C 002BD05C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802C0480 002BD060  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802C0484 002BD064  38 21 00 30 */	addi r1, r1, 0x30
/* 802C0488 002BD068  7C 08 03 A6 */	mtlr r0
/* 802C048C 002BD06C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

bool it_802C0490(Item_GObj* gobj)
{
    return true;
}

bool it_802C0498(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802C04B8(Item_GObj* gobj)
{
    return true;
}

bool it_802C04C0(Item_GObj* gobj)
{
    return true;
}

bool it_802C04C8(Item_GObj* gobj)
{
    return true;
}

bool it_802C04D0(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_802C04F0(Item_GObj* gobj, HSD_GObj* referenced_gobj)
{
    it_8026B894(gobj, referenced_gobj);
}
