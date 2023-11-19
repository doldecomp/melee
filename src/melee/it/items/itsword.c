/// @file
/// @todo A lot of duplicate code here, can maybe be cleaned up with inlines.
#include "it/forward.h"
#include "it/items/forward.h"

#include "itsword.h"

#include "types.h"

#include "ft/ftlib.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <placeholder.h>
#include <baselib/jobj.h>

LITERAL float const it_804DC8D0 = 0;
LITERAL float const it_804DC8D4 = -1;
LITERAL float const it_804DC8D8 = 0.3;
LITERAL float const it_804DC8DC = 1.5;
LITERAL float const it_804DC8E0 = 1;
LITERAL double const it_804DC8E8 = S32_TO_F32;
LITERAL float const it_804DC8F0 = 10.03;
LITERAL float const it_804DC8F4 = 2;
LITERAL float const it_804DC8F8 = 0.25;

/* literal */ extern char* const it_804D5220;
/* literal */ extern char* const it_804D5228;

/* 284E30 */ static void it_80284E30(Item_GObj* gobj);
/* 285084 */ static void it_80285084(Item_GObj* gobj);
/* 285140 */ static void it_80285140(Item_GObj* gobj);
/* 2851FC */ static void it_802851FC(Item_GObj* gobj);
/* 285424 */ static void it_80285424(Item_GObj* gobj);
/* 285580 */ static bool it_80285580(Item_GObj* gobj);
/* 2855C8 */ static void it_802855C8(Item_GObj* gobj);
/* 2855CC */ static bool it_802855CC(Item_GObj* gobj);
/* 2855F8 */ static void it_802855F8(Item_GObj* gobj);
/* 285744 */ static bool it_80285744(Item_GObj* gobj);
/* 28578C */ static void it_8028578C(Item_GObj* gobj);
/* 2857D8 */ static bool it_802857D8(Item_GObj* gobj);
/* 285920 */ static bool it_80285920(Item_GObj* gobj);
/* 285AF4 */ static void it_80285AF4(Item_GObj* gobj);
/* 285AF8 */ static bool it_80285AF8(Item_GObj* gobj);
/* 285F2C */ static bool it_80285F2C(Item_GObj* gobj);
/* 285F74 */ static void it_80285F74(Item_GObj* gobj);
/* 285F78 */ static bool it_80285F78(Item_GObj* gobj);

ItemStateTable it_803F5800[] = {
    { 0, it_80285580, it_802855C8, it_802855CC },
    { 0, it_80285744, it_8028578C, it_802857D8 },
    { 0, it_80285920, it_80285AF4, it_80285AF8 },
    { 1, it_80285744, it_8028578C, it_802857D8 },
    { 0, it_80285F2C, it_80285F74, it_80285F78 },
};

ASM Item_GObj* itSword_Spawn(Vec3* pos)
#if !defined(MUST_MATCH) || defined(WIP)
{
    SpawnItem spawn;
    spawn.kind = It_Kind_Sword;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0;
    spawn.pos = spawn.prev_pos;
    spawn.pos.y = pos->y;
    spawn.pos.z = spawn.prev_pos.z;
    spawn.facing_dir = -1;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0;
    {
        Item_GObj* gobj = Item_80268B5C(&spawn);
        if (gobj != NULL) {
            it_80285424(gobj);
        }
        return gobj;
    }
}

#else /* clang-format off */
{ nofralloc
/* 80284D54 00281934  7C 08 02 A6 */	mflr r0
/* 80284D58 00281938  38 A0 00 00 */	li r5, 0
/* 80284D5C 0028193C  90 01 00 04 */	stw r0, 4(r1)
/* 80284D60 00281940  38 00 00 0C */	li r0, 0xc
/* 80284D64 00281944  38 80 00 01 */	li r4, 1
/* 80284D68 00281948  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80284D6C 0028194C  93 E1 00 5C */	stw r31, 0x5c(r1)
/* 80284D70 00281950  90 01 00 14 */	stw r0, 0x14(r1)
/* 80284D74 00281954  80 C3 00 00 */	lwz r6, 0(r3)
/* 80284D78 00281958  80 03 00 04 */	lwz r0, 4(r3)
/* 80284D7C 0028195C  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 80284D80 00281960  90 01 00 30 */	stw r0, 0x30(r1)
/* 80284D84 00281964  80 03 00 08 */	lwz r0, 8(r3)
/* 80284D88 00281968  38 61 00 0C */	addi r3, r1, 0xc
/* 80284D8C 0028196C  90 01 00 34 */	stw r0, 0x34(r1)
/* 80284D90 00281970  C0 22 CE F0 */	lfs f1, it_804DC8D0
/* 80284D94 00281974  C0 02 CE F4 */	lfs f0, it_804DC8D4
/* 80284D98 00281978  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 80284D9C 0028197C  80 C1 00 2C */	lwz r6, 0x2c(r1)
/* 80284DA0 00281980  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80284DA4 00281984  90 C1 00 20 */	stw r6, 0x20(r1)
/* 80284DA8 00281988  90 01 00 24 */	stw r0, 0x24(r1)
/* 80284DAC 0028198C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80284DB0 00281990  90 01 00 28 */	stw r0, 0x28(r1)
/* 80284DB4 00281994  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 80284DB8 00281998  B0 A1 00 48 */	sth r5, 0x48(r1)
/* 80284DBC 0028199C  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 80284DC0 002819A0  D0 21 00 3C */	stfs f1, 0x3c(r1)
/* 80284DC4 002819A4  D0 21 00 38 */	stfs f1, 0x38(r1)
/* 80284DC8 002819A8  90 A1 00 0C */	stw r5, 0xc(r1)
/* 80284DCC 002819AC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80284DD0 002819B0  90 01 00 10 */	stw r0, 0x10(r1)
/* 80284DD4 002819B4  88 01 00 50 */	lbz r0, 0x50(r1)
/* 80284DD8 002819B8  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 80284DDC 002819BC  98 01 00 50 */	stb r0, 0x50(r1)
/* 80284DE0 002819C0  90 A1 00 4C */	stw r5, 0x4c(r1)
/* 80284DE4 002819C4  4B FE 3D 79 */	bl Item_80268B5C
/* 80284DE8 002819C8  7C 7F 1B 79 */	or. r31, r3, r3
/* 80284DEC 002819CC  41 82 00 0C */	beq lbl_80284DF8
/* 80284DF0 002819D0  7F E3 FB 78 */	mr r3, r31
/* 80284DF4 002819D4  48 00 06 31 */	bl it_80285424
lbl_80284DF8:
/* 80284DF8 002819D8  7F E3 FB 78 */	mr r3, r31
/* 80284DFC 002819DC  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80284E00 002819E0  83 E1 00 5C */	lwz r31, 0x5c(r1)
/* 80284E04 002819E4  38 21 00 60 */	addi r1, r1, 0x60
/* 80284E08 002819E8  7C 08 03 A6 */	mtlr r0
/* 80284E0C 002819EC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void it_80284E10(HSD_GObj* gobj, int arg1)
{
    it_8026EECC(gobj, arg1);
}

ASM void it_80284E30(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item* ip = GET_ITEM(gobj);
    float scale_y =
        it_804DC8D8 *
        (ip->xDD4_itemVar.sword.x28 *
         (ip->xDD4_itemVar.sword.x4C * ip->xDD4_itemVar.sword.x10));
    HSD_JObjSetScaleY(ip->xBBC_dynamicBoneTable->bones[6], scale_y);
    {
        Vec3 scale;
        if (ip->msid == 2) {
            float temp_scale =
                it_804DC8DC * ip->xDD4_itemVar.sword.x40 + scale_y;
            scale.x = temp_scale;
            scale.y = scale_y + ip->xDD4_itemVar.sword.x40;
            scale.z = temp_scale;
        } else {
            scale.x = it_804DC8E0;
            scale.y = scale_y;
            scale.z = it_804DC8E0;
        }
        HSD_JObjSetScale(ip->xBBC_dynamicBoneTable->bones[3], &scale);
    }
}

#else /* clang-format off */
{ nofralloc
/* 80284E30 00281A10  7C 08 02 A6 */	mflr r0
/* 80284E34 00281A14  90 01 00 04 */	stw r0, 4(r1)
/* 80284E38 00281A18  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80284E3C 00281A1C  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 80284E40 00281A20  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80284E44 00281A24  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80284E48 00281A28  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80284E4C 00281A2C  C0 42 CE F8 */	lfs f2, it_804DC8D8
/* 80284E50 00281A30  C0 3E 0E 20 */	lfs f1, 0xe20(r30)
/* 80284E54 00281A34  C0 1E 0D E4 */	lfs f0, 0xde4(r30)
/* 80284E58 00281A38  80 7E 0B BC */	lwz r3, 0xbbc(r30)
/* 80284E5C 00281A3C  EC 01 00 32 */	fmuls f0, f1, f0
/* 80284E60 00281A40  C0 3E 0D FC */	lfs f1, 0xdfc(r30)
/* 80284E64 00281A44  83 E3 00 18 */	lwz r31, 0x18(r3)
/* 80284E68 00281A48  EC 01 00 32 */	fmuls f0, f1, f0
/* 80284E6C 00281A4C  28 1F 00 00 */	cmplwi r31, 0
/* 80284E70 00281A50  EF E2 00 32 */	fmuls f31, f2, f0
/* 80284E74 00281A54  40 82 00 14 */	bne lbl_80284E88
/* 80284E78 00281A58  38 6D 9B 80 */	addi r3, r13, it_804D5220
/* 80284E7C 00281A5C  38 80 03 17 */	li r4, 0x317
/* 80284E80 00281A60  38 AD 9B 88 */	addi r5, r13, it_804D5228
/* 80284E84 00281A64  48 10 33 9D */	bl __assert
lbl_80284E88:
/* 80284E88 00281A68  D3 FF 00 30 */	stfs f31, 0x30(r31)
/* 80284E8C 00281A6C  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80284E90 00281A70  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80284E94 00281A74  40 82 00 4C */	bne lbl_80284EE0
/* 80284E98 00281A78  28 1F 00 00 */	cmplwi r31, 0
/* 80284E9C 00281A7C  41 82 00 44 */	beq lbl_80284EE0
/* 80284EA0 00281A80  40 82 00 14 */	bne lbl_80284EB4
/* 80284EA4 00281A84  38 6D 9B 80 */	addi r3, r13, it_804D5220
/* 80284EA8 00281A88  38 80 02 34 */	li r4, 0x234
/* 80284EAC 00281A8C  38 AD 9B 88 */	addi r5, r13, it_804D5228
/* 80284EB0 00281A90  48 10 33 71 */	bl __assert
lbl_80284EB4:
/* 80284EB4 00281A94  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80284EB8 00281A98  38 60 00 00 */	li r3, 0
/* 80284EBC 00281A9C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80284EC0 00281AA0  40 82 00 10 */	bne lbl_80284ED0
/* 80284EC4 00281AA4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80284EC8 00281AA8  41 82 00 08 */	beq lbl_80284ED0
/* 80284ECC 00281AAC  38 60 00 01 */	li r3, 1
lbl_80284ED0:
/* 80284ED0 00281AB0  2C 03 00 00 */	cmpwi r3, 0
/* 80284ED4 00281AB4  40 82 00 0C */	bne lbl_80284EE0
/* 80284ED8 00281AB8  7F E3 FB 78 */	mr r3, r31
/* 80284EDC 00281ABC  48 0E E4 0D */	bl HSD_JObjSetMtxDirtySub
lbl_80284EE0:
/* 80284EE0 00281AC0  80 1E 00 24 */	lwz r0, 0x24(r30)
/* 80284EE4 00281AC4  2C 00 00 02 */	cmpwi r0, 2
/* 80284EE8 00281AC8  40 82 00 24 */	bne lbl_80284F0C
/* 80284EEC 00281ACC  C0 5E 0E 14 */	lfs f2, 0xe14(r30)
/* 80284EF0 00281AD0  C0 22 CE FC */	lfs f1, it_804DC8DC
/* 80284EF4 00281AD4  EC 1F 10 2A */	fadds f0, f31, f2
/* 80284EF8 00281AD8  EC 21 F8 BA */	fmadds f1, f1, f2, f31
/* 80284EFC 00281ADC  D0 21 00 10 */	stfs f1, 0x10(r1)
/* 80284F00 00281AE0  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80284F04 00281AE4  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80284F08 00281AE8  48 00 00 14 */	b lbl_80284F1C
lbl_80284F0C:
/* 80284F0C 00281AEC  C0 02 CF 00 */	lfs f0, it_804DC8E0
/* 80284F10 00281AF0  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 80284F14 00281AF4  D3 E1 00 14 */	stfs f31, 0x14(r1)
/* 80284F18 00281AF8  D0 01 00 18 */	stfs f0, 0x18(r1)
lbl_80284F1C:
/* 80284F1C 00281AFC  80 7E 0B BC */	lwz r3, 0xbbc(r30)
/* 80284F20 00281B00  83 E3 00 0C */	lwz r31, 0xc(r3)
/* 80284F24 00281B04  28 1F 00 00 */	cmplwi r31, 0
/* 80284F28 00281B08  40 82 00 14 */	bne lbl_80284F3C
/* 80284F2C 00281B0C  38 6D 9B 80 */	addi r3, r13, it_804D5220
/* 80284F30 00281B10  38 80 02 F8 */	li r4, 0x2f8
/* 80284F34 00281B14  38 AD 9B 88 */	addi r5, r13, it_804D5228
/* 80284F38 00281B18  48 10 32 E9 */	bl __assert
lbl_80284F3C:
/* 80284F3C 00281B1C  80 61 00 10 */	lwz r3, 0x10(r1)
/* 80284F40 00281B20  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80284F44 00281B24  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 80284F48 00281B28  90 1F 00 30 */	stw r0, 0x30(r31)
/* 80284F4C 00281B2C  80 01 00 18 */	lwz r0, 0x18(r1)
/* 80284F50 00281B30  90 1F 00 34 */	stw r0, 0x34(r31)
/* 80284F54 00281B34  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80284F58 00281B38  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80284F5C 00281B3C  40 82 00 4C */	bne lbl_80284FA8
/* 80284F60 00281B40  28 1F 00 00 */	cmplwi r31, 0
/* 80284F64 00281B44  41 82 00 44 */	beq lbl_80284FA8
/* 80284F68 00281B48  40 82 00 14 */	bne lbl_80284F7C
/* 80284F6C 00281B4C  38 6D 9B 80 */	addi r3, r13, it_804D5220
/* 80284F70 00281B50  38 80 02 34 */	li r4, 0x234
/* 80284F74 00281B54  38 AD 9B 88 */	addi r5, r13, it_804D5228
/* 80284F78 00281B58  48 10 32 A9 */	bl __assert
lbl_80284F7C:
/* 80284F7C 00281B5C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80284F80 00281B60  38 60 00 00 */	li r3, 0
/* 80284F84 00281B64  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80284F88 00281B68  40 82 00 10 */	bne lbl_80284F98
/* 80284F8C 00281B6C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80284F90 00281B70  41 82 00 08 */	beq lbl_80284F98
/* 80284F94 00281B74  38 60 00 01 */	li r3, 1
lbl_80284F98:
/* 80284F98 00281B78  2C 03 00 00 */	cmpwi r3, 0
/* 80284F9C 00281B7C  40 82 00 0C */	bne lbl_80284FA8
/* 80284FA0 00281B80  7F E3 FB 78 */	mr r3, r31
/* 80284FA4 00281B84  48 0E E3 45 */	bl HSD_JObjSetMtxDirtySub
lbl_80284FA8:
/* 80284FA8 00281B88  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80284FAC 00281B8C  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 80284FB0 00281B90  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80284FB4 00281B94  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80284FB8 00281B98  38 21 00 30 */	addi r1, r1, 0x30
/* 80284FBC 00281B9C  7C 08 03 A6 */	mtlr r0
/* 80284FC0 00281BA0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void it_80284FC4(Item_GObj* gobj, int arg1, float arg2)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x4 = 0;
    ip->xDD4_itemVar.sword.x8 = arg1;
    ip->xDD4_itemVar.sword.xC = 1;
    ip->xDD4_itemVar.sword.x10 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x14 = arg2;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) / arg1;
}

#else /* clang-format off */
{ nofralloc
/* 80284FC4 00281BA4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80284FC8 00281BA8  38 00 00 00 */	li r0, 0
/* 80284FCC 00281BAC  38 A0 00 01 */	li r5, 1
/* 80284FD0 00281BB0  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80284FD4 00281BB4  6C 83 80 00 */	xoris r3, r4, 0x8000
/* 80284FD8 00281BB8  90 61 00 1C */	stw r3, 0x1c(r1)
/* 80284FDC 00281BBC  90 06 0D D8 */	stw r0, 0xdd8(r6)
/* 80284FE0 00281BC0  3C 00 43 30 */	lis r0, 0x4330
/* 80284FE4 00281BC4  90 86 0D DC */	stw r4, 0xddc(r6)
/* 80284FE8 00281BC8  90 A6 0D E0 */	stw r5, 0xde0(r6)
/* 80284FEC 00281BCC  C0 02 CF 00 */	lfs f0, it_804DC8E0
/* 80284FF0 00281BD0  90 01 00 18 */	stw r0, 0x18(r1)
/* 80284FF4 00281BD4  D0 06 0D E4 */	stfs f0, 0xde4(r6)
/* 80284FF8 00281BD8  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80284FFC 00281BDC  D0 26 0D E8 */	stfs f1, 0xde8(r6)
/* 80285000 00281BE0  C8 22 CF 08 */	lfd f1, it_804DC8E8
/* 80285004 00281BE4  C0 66 0D E8 */	lfs f3, 0xde8(r6)
/* 80285008 00281BE8  C0 46 0D E4 */	lfs f2, 0xde4(r6)
/* 8028500C 00281BEC  EC 00 08 28 */	fsubs f0, f0, f1
/* 80285010 00281BF0  EC 43 10 28 */	fsubs f2, f3, f2
/* 80285014 00281BF4  EC 02 00 24 */	fdivs f0, f2, f0
/* 80285018 00281BF8  D0 06 0D EC */	stfs f0, 0xdec(r6)
/* 8028501C 00281BFC  38 21 00 20 */	addi r1, r1, 0x20
/* 80285020 00281C00  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void it_80285024(Item_GObj* gobj, int arg1)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x4 = arg1;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) /
        ip->xDD4_itemVar.sword.x4;
}

#else /* clang-format off */
{ nofralloc
/* 80285024 00281C04  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80285028 00281C08  38 A0 00 00 */	li r5, 0
/* 8028502C 00281C0C  3C 00 43 30 */	lis r0, 0x4330
/* 80285030 00281C10  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80285034 00281C14  38 60 FF FF */	li r3, -1
/* 80285038 00281C18  90 86 0D D8 */	stw r4, 0xdd8(r6)
/* 8028503C 00281C1C  90 A6 0D DC */	stw r5, 0xddc(r6)
/* 80285040 00281C20  90 66 0D E0 */	stw r3, 0xde0(r6)
/* 80285044 00281C24  C0 02 CF 00 */	lfs f0, it_804DC8E0
/* 80285048 00281C28  D0 06 0D E8 */	stfs f0, 0xde8(r6)
/* 8028504C 00281C2C  80 66 0D D8 */	lwz r3, 0xdd8(r6)
/* 80285050 00281C30  C0 46 0D E8 */	lfs f2, 0xde8(r6)
/* 80285054 00281C34  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80285058 00281C38  C0 06 0D E4 */	lfs f0, 0xde4(r6)
/* 8028505C 00281C3C  90 61 00 1C */	stw r3, 0x1c(r1)
/* 80285060 00281C40  C8 22 CF 08 */	lfd f1, it_804DC8E8
/* 80285064 00281C44  EC 42 00 28 */	fsubs f2, f2, f0
/* 80285068 00281C48  90 01 00 18 */	stw r0, 0x18(r1)
/* 8028506C 00281C4C  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80285070 00281C50  EC 00 08 28 */	fsubs f0, f0, f1
/* 80285074 00281C54  EC 02 00 24 */	fdivs f0, f2, f0
/* 80285078 00281C58  D0 06 0D EC */	stfs f0, 0xdec(r6)
/* 8028507C 00281C5C  38 21 00 20 */	addi r1, r1, 0x20
/* 80285080 00281C60  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

/// @todo Shared code with #it_802851FC.
ASM void it_80285084(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x4 += ip->xDD4_itemVar.sword.xC;
    if (ip->xDD4_itemVar.sword.xC > 0) {
        if (ip->xDD4_itemVar.sword.x4 > ip->xDD4_itemVar.sword.x8) {
            ip->xDD4_itemVar.sword.x4 = ip->xDD4_itemVar.sword.x8;
            ip->xDD4_itemVar.sword.xC = 0;
        }
    } else if (ip->xDD4_itemVar.sword.xC < 0) {
        if (ip->xDD4_itemVar.sword.x4 < ip->xDD4_itemVar.sword.x8) {
            ip->xDD4_itemVar.sword.x4 = ip->xDD4_itemVar.sword.x8;
            ip->xDD4_itemVar.sword.xC = 0;
        }
    }
    ip->xDD4_itemVar.sword.x10 += ip->xDD4_itemVar.sword.x18;
    if (ip->xDD4_itemVar.sword.x18 > 0) {
        if (ip->xDD4_itemVar.sword.x10 > ip->xDD4_itemVar.sword.x14) {
            ip->xDD4_itemVar.sword.x10 = ip->xDD4_itemVar.sword.x14;
            ip->xDD4_itemVar.sword.x18 = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x48 < 0) {
        if (ip->xDD4_itemVar.sword.x40 < ip->xDD4_itemVar.sword.x44) {
            ip->xDD4_itemVar.sword.x40 = ip->xDD4_itemVar.sword.x44;
            ip->xDD4_itemVar.sword.x48 = 0;
        }
    }
}

#else /* clang-format off */
{ nofralloc
/* 80285084 00281C64  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80285088 00281C68  80 64 0D D8 */	lwz r3, 0xdd8(r4)
/* 8028508C 00281C6C  80 04 0D E0 */	lwz r0, 0xde0(r4)
/* 80285090 00281C70  7C 03 02 14 */	add r0, r3, r0
/* 80285094 00281C74  90 04 0D D8 */	stw r0, 0xdd8(r4)
/* 80285098 00281C78  80 04 0D E0 */	lwz r0, 0xde0(r4)
/* 8028509C 00281C7C  2C 00 00 00 */	cmpwi r0, 0
/* 802850A0 00281C80  40 81 00 24 */	ble lbl_802850C4
/* 802850A4 00281C84  80 04 0D D8 */	lwz r0, 0xdd8(r4)
/* 802850A8 00281C88  80 64 0D DC */	lwz r3, 0xddc(r4)
/* 802850AC 00281C8C  7C 00 18 00 */	cmpw r0, r3
/* 802850B0 00281C90  40 81 00 34 */	ble lbl_802850E4
/* 802850B4 00281C94  90 64 0D D8 */	stw r3, 0xdd8(r4)
/* 802850B8 00281C98  38 00 00 00 */	li r0, 0
/* 802850BC 00281C9C  90 04 0D E0 */	stw r0, 0xde0(r4)
/* 802850C0 00281CA0  48 00 00 24 */	b lbl_802850E4
lbl_802850C4:
/* 802850C4 00281CA4  40 80 00 20 */	bge lbl_802850E4
/* 802850C8 00281CA8  80 04 0D D8 */	lwz r0, 0xdd8(r4)
/* 802850CC 00281CAC  80 64 0D DC */	lwz r3, 0xddc(r4)
/* 802850D0 00281CB0  7C 00 18 00 */	cmpw r0, r3
/* 802850D4 00281CB4  40 80 00 10 */	bge lbl_802850E4
/* 802850D8 00281CB8  90 64 0D D8 */	stw r3, 0xdd8(r4)
/* 802850DC 00281CBC  38 00 00 00 */	li r0, 0
/* 802850E0 00281CC0  90 04 0D E0 */	stw r0, 0xde0(r4)
lbl_802850E4:
/* 802850E4 00281CC4  C0 24 0D E4 */	lfs f1, 0xde4(r4)
/* 802850E8 00281CC8  C0 04 0D EC */	lfs f0, 0xdec(r4)
/* 802850EC 00281CCC  EC 01 00 2A */	fadds f0, f1, f0
/* 802850F0 00281CD0  D0 04 0D E4 */	stfs f0, 0xde4(r4)
/* 802850F4 00281CD4  C0 04 0D EC */	lfs f0, 0xdec(r4)
/* 802850F8 00281CD8  C0 22 CE F0 */	lfs f1, it_804DC8D0
/* 802850FC 00281CDC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80285100 00281CE0  40 81 00 20 */	ble lbl_80285120
/* 80285104 00281CE4  C0 04 0D E4 */	lfs f0, 0xde4(r4)
/* 80285108 00281CE8  C0 44 0D E8 */	lfs f2, 0xde8(r4)
/* 8028510C 00281CEC  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 80285110 00281CF0  4C 81 00 20 */	blelr
/* 80285114 00281CF4  D0 44 0D E4 */	stfs f2, 0xde4(r4)
/* 80285118 00281CF8  D0 24 0D EC */	stfs f1, 0xdec(r4)
/* 8028511C 00281CFC  4E 80 00 20 */	blr
lbl_80285120:
/* 80285120 00281D00  4C 80 00 20 */	bgelr
/* 80285124 00281D04  C0 04 0D E4 */	lfs f0, 0xde4(r4)
/* 80285128 00281D08  C0 44 0D E8 */	lfs f2, 0xde8(r4)
/* 8028512C 00281D0C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 80285130 00281D10  4C 80 00 20 */	bgelr
/* 80285134 00281D14  D0 44 0D E4 */	stfs f2, 0xde4(r4)
/* 80285138 00281D18  D0 24 0D EC */	stfs f1, 0xdec(r4)
/* 8028513C 00281D1C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

/// @todo Shared code with #it_802851FC.
ASM void it_80285140(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C += ip->xDD4_itemVar.sword.x24;
    if (ip->xDD4_itemVar.sword.x24 > 0) {
        if (ip->xDD4_itemVar.sword.x1C > ip->xDD4_itemVar.sword.x20) {
            ip->xDD4_itemVar.sword.x1C = ip->xDD4_itemVar.sword.x20;
            ip->xDD4_itemVar.sword.x24 = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x24 < 0) {
        if (ip->xDD4_itemVar.sword.x1C < ip->xDD4_itemVar.sword.x20) {
            ip->xDD4_itemVar.sword.x1C = ip->xDD4_itemVar.sword.x20;
            ip->xDD4_itemVar.sword.x24 = 0;
        }
    }
    ip->xDD4_itemVar.sword.x28 += ip->xDD4_itemVar.sword.x30;
    if (ip->xDD4_itemVar.sword.x30 > 0) {
        if (ip->xDD4_itemVar.sword.x28 > ip->xDD4_itemVar.sword.x2C) {
            ip->xDD4_itemVar.sword.x28 = ip->xDD4_itemVar.sword.x2C;
            ip->xDD4_itemVar.sword.x30 = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x48 < 0) {
        if (ip->xDD4_itemVar.sword.x40 < ip->xDD4_itemVar.sword.x44) {
            ip->xDD4_itemVar.sword.x40 = ip->xDD4_itemVar.sword.x44;
            ip->xDD4_itemVar.sword.x48 = 0;
        }
    }
}

#else /* clang-format off */
{ nofralloc
/* 80285140 00281D20  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80285144 00281D24  80 64 0D F0 */	lwz r3, 0xdf0(r4)
/* 80285148 00281D28  80 04 0D F8 */	lwz r0, 0xdf8(r4)
/* 8028514C 00281D2C  7C 03 02 14 */	add r0, r3, r0
/* 80285150 00281D30  90 04 0D F0 */	stw r0, 0xdf0(r4)
/* 80285154 00281D34  80 04 0D F8 */	lwz r0, 0xdf8(r4)
/* 80285158 00281D38  2C 00 00 00 */	cmpwi r0, 0
/* 8028515C 00281D3C  40 81 00 24 */	ble lbl_80285180
/* 80285160 00281D40  80 04 0D F0 */	lwz r0, 0xdf0(r4)
/* 80285164 00281D44  80 64 0D F4 */	lwz r3, 0xdf4(r4)
/* 80285168 00281D48  7C 00 18 00 */	cmpw r0, r3
/* 8028516C 00281D4C  40 81 00 34 */	ble lbl_802851A0
/* 80285170 00281D50  90 64 0D F0 */	stw r3, 0xdf0(r4)
/* 80285174 00281D54  38 00 00 00 */	li r0, 0
/* 80285178 00281D58  90 04 0D F8 */	stw r0, 0xdf8(r4)
/* 8028517C 00281D5C  48 00 00 24 */	b lbl_802851A0
lbl_80285180:
/* 80285180 00281D60  40 80 00 20 */	bge lbl_802851A0
/* 80285184 00281D64  80 04 0D F0 */	lwz r0, 0xdf0(r4)
/* 80285188 00281D68  80 64 0D F4 */	lwz r3, 0xdf4(r4)
/* 8028518C 00281D6C  7C 00 18 00 */	cmpw r0, r3
/* 80285190 00281D70  40 80 00 10 */	bge lbl_802851A0
/* 80285194 00281D74  90 64 0D F0 */	stw r3, 0xdf0(r4)
/* 80285198 00281D78  38 00 00 00 */	li r0, 0
/* 8028519C 00281D7C  90 04 0D F8 */	stw r0, 0xdf8(r4)
lbl_802851A0:
/* 802851A0 00281D80  C0 24 0D FC */	lfs f1, 0xdfc(r4)
/* 802851A4 00281D84  C0 04 0E 04 */	lfs f0, 0xe04(r4)
/* 802851A8 00281D88  EC 01 00 2A */	fadds f0, f1, f0
/* 802851AC 00281D8C  D0 04 0D FC */	stfs f0, 0xdfc(r4)
/* 802851B0 00281D90  C0 04 0E 04 */	lfs f0, 0xe04(r4)
/* 802851B4 00281D94  C0 22 CE F0 */	lfs f1, it_804DC8D0
/* 802851B8 00281D98  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 802851BC 00281D9C  40 81 00 20 */	ble lbl_802851DC
/* 802851C0 00281DA0  C0 04 0D FC */	lfs f0, 0xdfc(r4)
/* 802851C4 00281DA4  C0 44 0E 00 */	lfs f2, 0xe00(r4)
/* 802851C8 00281DA8  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 802851CC 00281DAC  4C 81 00 20 */	blelr
/* 802851D0 00281DB0  D0 44 0D FC */	stfs f2, 0xdfc(r4)
/* 802851D4 00281DB4  D0 24 0E 04 */	stfs f1, 0xe04(r4)
/* 802851D8 00281DB8  4E 80 00 20 */	blr
lbl_802851DC:
/* 802851DC 00281DBC  4C 80 00 20 */	bgelr
/* 802851E0 00281DC0  C0 04 0D FC */	lfs f0, 0xdfc(r4)
/* 802851E4 00281DC4  C0 44 0E 00 */	lfs f2, 0xe00(r4)
/* 802851E8 00281DC8  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 802851EC 00281DCC  4C 80 00 20 */	bgelr
/* 802851F0 00281DD0  D0 44 0D FC */	stfs f2, 0xdfc(r4)
/* 802851F4 00281DD4  D0 24 0E 04 */	stfs f1, 0xe04(r4)
/* 802851F8 00281DD8  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void it_802851FC(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x34 += ip->xDD4_itemVar.sword.x3C;
    if (ip->xDD4_itemVar.sword.x3C > 0) {
        if (ip->xDD4_itemVar.sword.x34 > ip->xDD4_itemVar.sword.x38) {
            ip->xDD4_itemVar.sword.x34 = ip->xDD4_itemVar.sword.x38;
            ip->xDD4_itemVar.sword.x3C = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x3C < 0) {
        if (ip->xDD4_itemVar.sword.x34 < ip->xDD4_itemVar.sword.x38) {
            ip->xDD4_itemVar.sword.x34 = ip->xDD4_itemVar.sword.x38;
            ip->xDD4_itemVar.sword.x3C = 0;
        }
    }
    ip->xDD4_itemVar.sword.x40 += ip->xDD4_itemVar.sword.x48;
    if (ip->xDD4_itemVar.sword.x48 > 0) {
        if (ip->xDD4_itemVar.sword.x40 > ip->xDD4_itemVar.sword.x44) {
            ip->xDD4_itemVar.sword.x40 = ip->xDD4_itemVar.sword.x44;
            ip->xDD4_itemVar.sword.x48 = 0;
        }
    } else if (ip->xDD4_itemVar.sword.x48 < 0) {
        if (ip->xDD4_itemVar.sword.x40 < ip->xDD4_itemVar.sword.x44) {
            ip->xDD4_itemVar.sword.x40 = ip->xDD4_itemVar.sword.x44;
            ip->xDD4_itemVar.sword.x48 = 0;
        }
    }
}

#else /* clang-format off */
{ nofralloc
/* 802851FC 00281DDC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80285200 00281DE0  80 64 0E 08 */	lwz r3, 0xe08(r4)
/* 80285204 00281DE4  80 04 0E 10 */	lwz r0, 0xe10(r4)
/* 80285208 00281DE8  7C 03 02 14 */	add r0, r3, r0
/* 8028520C 00281DEC  90 04 0E 08 */	stw r0, 0xe08(r4)
/* 80285210 00281DF0  80 04 0E 10 */	lwz r0, 0xe10(r4)
/* 80285214 00281DF4  2C 00 00 00 */	cmpwi r0, 0
/* 80285218 00281DF8  40 81 00 24 */	ble lbl_8028523C
/* 8028521C 00281DFC  80 04 0E 08 */	lwz r0, 0xe08(r4)
/* 80285220 00281E00  80 64 0E 0C */	lwz r3, 0xe0c(r4)
/* 80285224 00281E04  7C 00 18 00 */	cmpw r0, r3
/* 80285228 00281E08  40 81 00 34 */	ble lbl_8028525C
/* 8028522C 00281E0C  90 64 0E 08 */	stw r3, 0xe08(r4)
/* 80285230 00281E10  38 00 00 00 */	li r0, 0
/* 80285234 00281E14  90 04 0E 10 */	stw r0, 0xe10(r4)
/* 80285238 00281E18  48 00 00 24 */	b lbl_8028525C
lbl_8028523C:
/* 8028523C 00281E1C  40 80 00 20 */	bge lbl_8028525C
/* 80285240 00281E20  80 04 0E 08 */	lwz r0, 0xe08(r4)
/* 80285244 00281E24  80 64 0E 0C */	lwz r3, 0xe0c(r4)
/* 80285248 00281E28  7C 00 18 00 */	cmpw r0, r3
/* 8028524C 00281E2C  40 80 00 10 */	bge lbl_8028525C
/* 80285250 00281E30  90 64 0E 08 */	stw r3, 0xe08(r4)
/* 80285254 00281E34  38 00 00 00 */	li r0, 0
/* 80285258 00281E38  90 04 0E 10 */	stw r0, 0xe10(r4)
lbl_8028525C:
/* 8028525C 00281E3C  C0 24 0E 14 */	lfs f1, 0xe14(r4)
/* 80285260 00281E40  C0 04 0E 1C */	lfs f0, 0xe1c(r4)
/* 80285264 00281E44  EC 01 00 2A */	fadds f0, f1, f0
/* 80285268 00281E48  D0 04 0E 14 */	stfs f0, 0xe14(r4)
/* 8028526C 00281E4C  C0 04 0E 1C */	lfs f0, 0xe1c(r4)
/* 80285270 00281E50  C0 22 CE F0 */	lfs f1, it_804DC8D0
/* 80285274 00281E54  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80285278 00281E58  40 81 00 20 */	ble lbl_80285298
/* 8028527C 00281E5C  C0 04 0E 14 */	lfs f0, 0xe14(r4)
/* 80285280 00281E60  C0 44 0E 18 */	lfs f2, 0xe18(r4)
/* 80285284 00281E64  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 80285288 00281E68  4C 81 00 20 */	blelr
/* 8028528C 00281E6C  D0 44 0E 14 */	stfs f2, 0xe14(r4)
/* 80285290 00281E70  D0 24 0E 1C */	stfs f1, 0xe1c(r4)
/* 80285294 00281E74  4E 80 00 20 */	blr
lbl_80285298:
/* 80285298 00281E78  4C 80 00 20 */	bgelr
/* 8028529C 00281E7C  C0 04 0E 14 */	lfs f0, 0xe14(r4)
/* 802852A0 00281E80  C0 44 0E 18 */	lfs f2, 0xe18(r4)
/* 802852A4 00281E84  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 802852A8 00281E88  4C 80 00 20 */	bgelr
/* 802852AC 00281E8C  D0 44 0E 14 */	stfs f2, 0xe14(r4)
/* 802852B0 00281E90  D0 24 0E 1C */	stfs f1, 0xe1c(r4)
/* 802852B4 00281E94  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void it_802852B8(Item_GObj* gobj, float* arg1, float* arg2)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item* ip = GET_ITEM(gobj);
    if (arg1 != NULL) {
        *arg1 = it_804DC8D0;
    }
    if (arg2 != NULL) {
        float temp1 =
            (ip->xDD4_itemVar.sword.x28 *
             (ip->xDD4_itemVar.sword.x4C * ip->xDD4_itemVar.sword.x10));
        float temp2 = it_804DC8D8 * temp1;
        *arg2 = it_804DC8F0 * temp2;
    }
}

#else /* clang-format off */
{ nofralloc
/* 802852B8 00281E98  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802852BC 00281E9C  28 04 00 00 */	cmplwi r4, 0
/* 802852C0 00281EA0  C0 62 CE F8 */	lfs f3, it_804DC8D8
/* 802852C4 00281EA4  C0 23 0E 20 */	lfs f1, 0xe20(r3)
/* 802852C8 00281EA8  C0 03 0D E4 */	lfs f0, 0xde4(r3)
/* 802852CC 00281EAC  C0 43 0D FC */	lfs f2, 0xdfc(r3)
/* 802852D0 00281EB0  EC 01 00 32 */	fmuls f0, f1, f0
/* 802852D4 00281EB4  EC 02 00 32 */	fmuls f0, f2, f0
/* 802852D8 00281EB8  EC 23 00 32 */	fmuls f1, f3, f0
/* 802852DC 00281EBC  41 82 00 0C */	beq lbl_802852E8
/* 802852E0 00281EC0  C0 02 CE F0 */	lfs f0, it_804DC8D0
/* 802852E4 00281EC4  D0 04 00 00 */	stfs f0, 0(r4)
lbl_802852E8:
/* 802852E8 00281EC8  28 05 00 00 */	cmplwi r5, 0
/* 802852EC 00281ECC  4D 82 00 20 */	beqlr
/* 802852F0 00281ED0  C0 02 CF 10 */	lfs f0, it_804DC8F0
/* 802852F4 00281ED4  EC 00 00 72 */	fmuls f0, f0, f1
/* 802852F8 00281ED8  D0 05 00 00 */	stfs f0, 0(r5)
/* 802852FC 00281EDC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

itSword_UnkBytes* it_80285300(Item_GObj* gobj)
{
    itSword_UnkArticle1* attrs =
        GET_ITEM(gobj)->xC4_article_data->x4_specialAttributes;
    return &attrs->x1C;
}

void it_80285314(Item_GObj* gobj)
{
    it_80272CC0(gobj, 5);
}

ASM void it_80285338(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    it_8026B390(gobj);
    ip->x40_vel.x = it_804DC8D0;
    ip->x40_vel.y = attrs->xC;
    ip->x40_vel.z = it_804DC8D0;
    ip->xDD4_itemVar.capsule.x0 = 0;
    ip->xDD4_itemVar.capsule.x4 = 0;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = 0;
    ip->xDD4_itemVar.sword.x10 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x14 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x18 = it_804DC8D0;
    ip->xDD4_itemVar.sword.x1C = 0;
    ip->xDD4_itemVar.sword.x20 = 0;
    ip->xDD4_itemVar.sword.x24 = 0;
    ip->xDD4_itemVar.sword.x28 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x2C = it_804DC8E0;
    ip->xDD4_itemVar.sword.x30 = it_804DC8D0;
    ip->xDD4_itemVar.sword.x34 = 0;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = 0;
    ip->xDD4_itemVar.sword.x40 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x44 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x48 = it_804DC8D0;
    ip->xDD4_itemVar.sword.x50 = it_804DC8D0;
    ip->xDD4_itemVar.sword.x4C =
        HSD_JObjGetScaleY(ip->xBBC_dynamicBoneTable->bones[6]);
    ip->xDD4_itemVar.sword.x54 = 0;
    it_802855F8(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 80285338 00281F18  7C 08 02 A6 */	mflr r0
/* 8028533C 00281F1C  90 01 00 04 */	stw r0, 4(r1)
/* 80285340 00281F20  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80285344 00281F24  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80285348 00281F28  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8028534C 00281F2C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80285350 00281F30  7C 7D 1B 78 */	mr r29, r3
/* 80285354 00281F34  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80285358 00281F38  80 9E 00 C4 */	lwz r4, 0xc4(r30)
/* 8028535C 00281F3C  83 E4 00 04 */	lwz r31, 4(r4)
/* 80285360 00281F40  4B FE 60 31 */	bl it_8026B390
/* 80285364 00281F44  C0 22 CE F0 */	lfs f1, it_804DC8D0
/* 80285368 00281F48  38 00 00 00 */	li r0, 0
/* 8028536C 00281F4C  D0 3E 00 40 */	stfs f1, 0x40(r30)
/* 80285370 00281F50  C0 1F 00 0C */	lfs f0, 0xc(r31)
/* 80285374 00281F54  D0 1E 00 44 */	stfs f0, 0x44(r30)
/* 80285378 00281F58  D0 3E 00 48 */	stfs f1, 0x48(r30)
/* 8028537C 00281F5C  90 1E 0D D4 */	stw r0, 0xdd4(r30)
/* 80285380 00281F60  90 1E 0D D8 */	stw r0, 0xdd8(r30)
/* 80285384 00281F64  90 1E 0D DC */	stw r0, 0xddc(r30)
/* 80285388 00281F68  90 1E 0D E0 */	stw r0, 0xde0(r30)
/* 8028538C 00281F6C  C0 02 CF 00 */	lfs f0, it_804DC8E0
/* 80285390 00281F70  D0 1E 0D E4 */	stfs f0, 0xde4(r30)
/* 80285394 00281F74  D0 1E 0D E8 */	stfs f0, 0xde8(r30)
/* 80285398 00281F78  D0 3E 0D EC */	stfs f1, 0xdec(r30)
/* 8028539C 00281F7C  90 1E 0D F0 */	stw r0, 0xdf0(r30)
/* 802853A0 00281F80  90 1E 0D F4 */	stw r0, 0xdf4(r30)
/* 802853A4 00281F84  90 1E 0D F8 */	stw r0, 0xdf8(r30)
/* 802853A8 00281F88  D0 1E 0D FC */	stfs f0, 0xdfc(r30)
/* 802853AC 00281F8C  D0 1E 0E 00 */	stfs f0, 0xe00(r30)
/* 802853B0 00281F90  D0 3E 0E 04 */	stfs f1, 0xe04(r30)
/* 802853B4 00281F94  90 1E 0E 08 */	stw r0, 0xe08(r30)
/* 802853B8 00281F98  90 1E 0E 0C */	stw r0, 0xe0c(r30)
/* 802853BC 00281F9C  90 1E 0E 10 */	stw r0, 0xe10(r30)
/* 802853C0 00281FA0  D0 1E 0E 14 */	stfs f0, 0xe14(r30)
/* 802853C4 00281FA4  D0 1E 0E 18 */	stfs f0, 0xe18(r30)
/* 802853C8 00281FA8  D0 3E 0E 1C */	stfs f1, 0xe1c(r30)
/* 802853CC 00281FAC  D0 3E 0E 24 */	stfs f1, 0xe24(r30)
/* 802853D0 00281FB0  80 7E 0B BC */	lwz r3, 0xbbc(r30)
/* 802853D4 00281FB4  83 E3 00 18 */	lwz r31, 0x18(r3)
/* 802853D8 00281FB8  28 1F 00 00 */	cmplwi r31, 0
/* 802853DC 00281FBC  40 82 00 14 */	bne lbl_802853F0
/* 802853E0 00281FC0  38 6D 9B 80 */	addi r3, r13, it_804D5220
/* 802853E4 00281FC4  38 80 03 78 */	li r4, 0x378
/* 802853E8 00281FC8  38 AD 9B 88 */	addi r5, r13, it_804D5228
/* 802853EC 00281FCC  48 10 2E 35 */	bl __assert
lbl_802853F0:
/* 802853F0 00281FD0  C0 1F 00 30 */	lfs f0, 0x30(r31)
/* 802853F4 00281FD4  38 00 00 00 */	li r0, 0
/* 802853F8 00281FD8  38 7D 00 00 */	addi r3, r29, 0
/* 802853FC 00281FDC  D0 1E 0E 20 */	stfs f0, 0xe20(r30)
/* 80285400 00281FE0  90 1E 0E 28 */	stw r0, 0xe28(r30)
/* 80285404 00281FE4  48 00 01 F5 */	bl it_802855F8
/* 80285408 00281FE8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8028540C 00281FEC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80285410 00281FF0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80285414 00281FF4  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80285418 00281FF8  38 21 00 30 */	addi r1, r1, 0x30
/* 8028541C 00281FFC  7C 08 03 A6 */	mtlr r0
/* 80285420 00282000  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline void inlineA0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = it_804DC8D0;
    ip->xD50_landNum = 0;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

static inline void inlineA1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.capsule.x4 = 4;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) /
        ip->xDD4_itemVar.sword.x4;
}

static inline void inlineA2(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C = 4;
    ip->xDD4_itemVar.sword.x20 = 0;
    ip->xDD4_itemVar.sword.x24 = -1;
    ip->xDD4_itemVar.sword.x2C = it_804DC8E0;
    ip->xDD4_itemVar.sword.x30 =
        (ip->xDD4_itemVar.sword.x2C - ip->xDD4_itemVar.sword.x28) /
        ip->xDD4_itemVar.sword.x1C;
}

static inline void inlineA3(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = attrs->x18;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = -1;
    ip->xDD4_itemVar.sword.x44 = attrs->x10;
    ip->xDD4_itemVar.sword.x48 =
        (attrs->x10 - ip->xDD4_itemVar.sword.x40) / attrs->x18;
}

static inline void inlineA4(Item_GObj* gobj)
{
    it_80285084(gobj);
    it_80285140(gobj);
    it_802851FC(gobj);
    it_80284E30(gobj);
}

ASM void it_80285424(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    inlineA0(gobj);
    inlineA1(gobj);
    inlineA2(gobj);
    inlineA3(gobj);
    inlineA4(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 80285424 00282004  7C 08 02 A6 */	mflr r0
/* 80285428 00282008  38 80 00 00 */	li r4, 0
/* 8028542C 0028200C  90 01 00 04 */	stw r0, 4(r1)
/* 80285430 00282010  38 A0 00 02 */	li r5, 2
/* 80285434 00282014  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80285438 00282018  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8028543C 0028201C  7C 7F 1B 78 */	mr r31, r3
/* 80285440 00282020  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80285444 00282024  3B C0 00 00 */	li r30, 0
/* 80285448 00282028  C0 02 CE F0 */	lfs f0, it_804DC8D0
/* 8028544C 0028202C  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80285450 00282030  D0 06 00 48 */	stfs f0, 0x48(r6)
/* 80285454 00282034  D0 06 00 44 */	stfs f0, 0x44(r6)
/* 80285458 00282038  D0 06 00 40 */	stfs f0, 0x40(r6)
/* 8028545C 0028203C  93 C6 0D 50 */	stw r30, 0xd50(r6)
/* 80285460 00282040  4B FE 39 FD */	bl Item_80268E5C
/* 80285464 00282044  80 FF 00 2C */	lwz r7, 0x2c(r31)
/* 80285468 00282048  38 80 00 04 */	li r4, 4
/* 8028546C 0028204C  38 C0 FF FF */	li r6, -1
/* 80285470 00282050  90 87 0D D8 */	stw r4, 0xdd8(r7)
/* 80285474 00282054  3C A0 43 30 */	lis r5, 0x4330
/* 80285478 00282058  38 7F 00 00 */	addi r3, r31, 0
/* 8028547C 0028205C  93 C7 0D DC */	stw r30, 0xddc(r7)
/* 80285480 00282060  90 C7 0D E0 */	stw r6, 0xde0(r7)
/* 80285484 00282064  C0 62 CF 00 */	lfs f3, it_804DC8E0
/* 80285488 00282068  D0 67 0D E8 */	stfs f3, 0xde8(r7)
/* 8028548C 0028206C  80 07 0D D8 */	lwz r0, 0xdd8(r7)
/* 80285490 00282070  C0 27 0D E8 */	lfs f1, 0xde8(r7)
/* 80285494 00282074  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285498 00282078  C0 07 0D E4 */	lfs f0, 0xde4(r7)
/* 8028549C 0028207C  90 01 00 34 */	stw r0, 0x34(r1)
/* 802854A0 00282080  C8 42 CF 08 */	lfd f2, it_804DC8E8
/* 802854A4 00282084  EC 21 00 28 */	fsubs f1, f1, f0
/* 802854A8 00282088  90 A1 00 30 */	stw r5, 0x30(r1)
/* 802854AC 0028208C  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 802854B0 00282090  EC 00 10 28 */	fsubs f0, f0, f2
/* 802854B4 00282094  EC 01 00 24 */	fdivs f0, f1, f0
/* 802854B8 00282098  D0 07 0D EC */	stfs f0, 0xdec(r7)
/* 802854BC 0028209C  80 FF 00 2C */	lwz r7, 0x2c(r31)
/* 802854C0 002820A0  90 87 0D F0 */	stw r4, 0xdf0(r7)
/* 802854C4 002820A4  93 C7 0D F4 */	stw r30, 0xdf4(r7)
/* 802854C8 002820A8  90 C7 0D F8 */	stw r6, 0xdf8(r7)
/* 802854CC 002820AC  D0 67 0E 00 */	stfs f3, 0xe00(r7)
/* 802854D0 002820B0  80 07 0D F0 */	lwz r0, 0xdf0(r7)
/* 802854D4 002820B4  C0 27 0E 00 */	lfs f1, 0xe00(r7)
/* 802854D8 002820B8  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 802854DC 002820BC  C0 07 0D FC */	lfs f0, 0xdfc(r7)
/* 802854E0 002820C0  90 01 00 2C */	stw r0, 0x2c(r1)
/* 802854E4 002820C4  EC 21 00 28 */	fsubs f1, f1, f0
/* 802854E8 002820C8  90 A1 00 28 */	stw r5, 0x28(r1)
/* 802854EC 002820CC  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 802854F0 002820D0  EC 00 10 28 */	fsubs f0, f0, f2
/* 802854F4 002820D4  EC 01 00 24 */	fdivs f0, f1, f0
/* 802854F8 002820D8  D0 07 0E 04 */	stfs f0, 0xe04(r7)
/* 802854FC 002820DC  80 FF 00 2C */	lwz r7, 0x2c(r31)
/* 80285500 002820E0  80 87 00 C4 */	lwz r4, 0xc4(r7)
/* 80285504 002820E4  80 84 00 04 */	lwz r4, 4(r4)
/* 80285508 002820E8  80 04 00 18 */	lwz r0, 0x18(r4)
/* 8028550C 002820EC  90 07 0E 08 */	stw r0, 0xe08(r7)
/* 80285510 002820F0  93 C7 0E 0C */	stw r30, 0xe0c(r7)
/* 80285514 002820F4  90 C7 0E 10 */	stw r6, 0xe10(r7)
/* 80285518 002820F8  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 8028551C 002820FC  D0 07 0E 18 */	stfs f0, 0xe18(r7)
/* 80285520 00282100  80 04 00 18 */	lwz r0, 0x18(r4)
/* 80285524 00282104  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 80285528 00282108  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8028552C 0028210C  C0 07 0E 14 */	lfs f0, 0xe14(r7)
/* 80285530 00282110  90 01 00 24 */	stw r0, 0x24(r1)
/* 80285534 00282114  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285538 00282118  90 A1 00 20 */	stw r5, 0x20(r1)
/* 8028553C 0028211C  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80285540 00282120  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285544 00282124  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285548 00282128  D0 07 0E 1C */	stfs f0, 0xe1c(r7)
/* 8028554C 0028212C  4B FF FB 39 */	bl it_80285084
/* 80285550 00282130  7F E3 FB 78 */	mr r3, r31
/* 80285554 00282134  4B FF FB ED */	bl it_80285140
/* 80285558 00282138  7F E3 FB 78 */	mr r3, r31
/* 8028555C 0028213C  4B FF FC A1 */	bl it_802851FC
/* 80285560 00282140  7F E3 FB 78 */	mr r3, r31
/* 80285564 00282144  4B FF F8 CD */	bl it_80284E30
/* 80285568 00282148  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8028556C 0028214C  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80285570 00282150  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80285574 00282154  38 21 00 40 */	addi r1, r1, 0x40
/* 80285578 00282158  7C 08 03 A6 */	mtlr r0
/* 8028557C 0028215C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

bool it_80285580(Item_GObj* gobj)
{
    inlineA4(gobj);
    return false;
}

void it_802855C8(Item_GObj* gobj) {}

bool it_802855CC(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802855F8);
    return false;
}

static inline void inlineB0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    ip->xD50_landNum = 0;
}

static inline void inlineB1(Item_GObj* gobj)
{
    {
        Item* ip = GET_ITEM(gobj);
        ip->xDD4_itemVar.capsule.x4 = 4;
        ip->xDD4_itemVar.sword.x8 = 0;
        ip->xDD4_itemVar.sword.xC = -1;
        ip->xDD4_itemVar.star.yvel = it_804DC8E0;
        ip->xDD4_itemVar.sword.x18 =
            (ip->xDD4_itemVar.star.yvel - ip->xDD4_itemVar.star.xvel) /
            (float) ip->xDD4_itemVar.capsule.x4;
    }
}

static inline void inlineB2(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C = 4;
    ip->xDD4_itemVar.sword.x20 = 0;
    ip->xDD4_itemVar.sword.x24 = -1;
    ip->xDD4_itemVar.sword.x2C = it_804DC8E0;
    ip->xDD4_itemVar.sword.x30 =
        (ip->xDD4_itemVar.sword.x2C - ip->xDD4_itemVar.sword.x28) /
        (float) ip->xDD4_itemVar.sword.x1C;
}

static inline void inlineB3(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = attrs->x18;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = -1;
    ip->xDD4_itemVar.sword.x44 = attrs->x10;
    ip->xDD4_itemVar.sword.x48 =
        (attrs->x10 - ip->xDD4_itemVar.sword.x40) / attrs->x18;
}

ASM void it_802855F8(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    inlineB0(gobj);
    inlineB1(gobj);
    inlineB2(gobj);
    inlineB3(gobj);
    inlineA4(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 802855F8 002821D8  7C 08 02 A6 */	mflr r0
/* 802855FC 002821DC  38 80 00 01 */	li r4, 1
/* 80285600 002821E0  90 01 00 04 */	stw r0, 4(r1)
/* 80285604 002821E4  38 A0 00 02 */	li r5, 2
/* 80285608 002821E8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8028560C 002821EC  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80285610 002821F0  7C 7F 1B 78 */	mr r31, r3
/* 80285614 002821F4  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80285618 002821F8  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8028561C 002821FC  4B FE 38 41 */	bl Item_80268E5C
/* 80285620 00282200  38 E0 00 00 */	li r7, 0
/* 80285624 00282204  90 FE 0D 50 */	stw r7, 0xd50(r30)
/* 80285628 00282208  38 80 00 04 */	li r4, 4
/* 8028562C 0028220C  38 C0 FF FF */	li r6, -1
/* 80285630 00282210  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285634 00282214  3C A0 43 30 */	lis r5, 0x4330
/* 80285638 00282218  38 7F 00 00 */	addi r3, r31, 0
/* 8028563C 0028221C  90 88 0D D8 */	stw r4, 0xdd8(r8)
/* 80285640 00282220  90 E8 0D DC */	stw r7, 0xddc(r8)
/* 80285644 00282224  90 C8 0D E0 */	stw r6, 0xde0(r8)
/* 80285648 00282228  C0 62 CF 00 */	lfs f3, it_804DC8E0
/* 8028564C 0028222C  D0 68 0D E8 */	stfs f3, 0xde8(r8)
/* 80285650 00282230  80 08 0D D8 */	lwz r0, 0xdd8(r8)
/* 80285654 00282234  C0 28 0D E8 */	lfs f1, 0xde8(r8)
/* 80285658 00282238  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8028565C 0028223C  C0 08 0D E4 */	lfs f0, 0xde4(r8)
/* 80285660 00282240  90 01 00 34 */	stw r0, 0x34(r1)
/* 80285664 00282244  C8 42 CF 08 */	lfd f2, it_804DC8E8
/* 80285668 00282248  EC 21 00 28 */	fsubs f1, f1, f0
/* 8028566C 0028224C  90 A1 00 30 */	stw r5, 0x30(r1)
/* 80285670 00282250  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80285674 00282254  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285678 00282258  EC 01 00 24 */	fdivs f0, f1, f0
/* 8028567C 0028225C  D0 08 0D EC */	stfs f0, 0xdec(r8)
/* 80285680 00282260  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285684 00282264  90 88 0D F0 */	stw r4, 0xdf0(r8)
/* 80285688 00282268  90 E8 0D F4 */	stw r7, 0xdf4(r8)
/* 8028568C 0028226C  90 C8 0D F8 */	stw r6, 0xdf8(r8)
/* 80285690 00282270  D0 68 0E 00 */	stfs f3, 0xe00(r8)
/* 80285694 00282274  80 08 0D F0 */	lwz r0, 0xdf0(r8)
/* 80285698 00282278  C0 28 0E 00 */	lfs f1, 0xe00(r8)
/* 8028569C 0028227C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 802856A0 00282280  C0 08 0D FC */	lfs f0, 0xdfc(r8)
/* 802856A4 00282284  90 01 00 2C */	stw r0, 0x2c(r1)
/* 802856A8 00282288  EC 21 00 28 */	fsubs f1, f1, f0
/* 802856AC 0028228C  90 A1 00 28 */	stw r5, 0x28(r1)
/* 802856B0 00282290  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 802856B4 00282294  EC 00 10 28 */	fsubs f0, f0, f2
/* 802856B8 00282298  EC 01 00 24 */	fdivs f0, f1, f0
/* 802856BC 0028229C  D0 08 0E 04 */	stfs f0, 0xe04(r8)
/* 802856C0 002822A0  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 802856C4 002822A4  80 88 00 C4 */	lwz r4, 0xc4(r8)
/* 802856C8 002822A8  80 84 00 04 */	lwz r4, 4(r4)
/* 802856CC 002822AC  80 04 00 18 */	lwz r0, 0x18(r4)
/* 802856D0 002822B0  90 08 0E 08 */	stw r0, 0xe08(r8)
/* 802856D4 002822B4  90 E8 0E 0C */	stw r7, 0xe0c(r8)
/* 802856D8 002822B8  90 C8 0E 10 */	stw r6, 0xe10(r8)
/* 802856DC 002822BC  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 802856E0 002822C0  D0 08 0E 18 */	stfs f0, 0xe18(r8)
/* 802856E4 002822C4  80 04 00 18 */	lwz r0, 0x18(r4)
/* 802856E8 002822C8  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 802856EC 002822CC  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 802856F0 002822D0  C0 08 0E 14 */	lfs f0, 0xe14(r8)
/* 802856F4 002822D4  90 01 00 24 */	stw r0, 0x24(r1)
/* 802856F8 002822D8  EC 21 00 28 */	fsubs f1, f1, f0
/* 802856FC 002822DC  90 A1 00 20 */	stw r5, 0x20(r1)
/* 80285700 002822E0  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80285704 002822E4  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285708 002822E8  EC 01 00 24 */	fdivs f0, f1, f0
/* 8028570C 002822EC  D0 08 0E 1C */	stfs f0, 0xe1c(r8)
/* 80285710 002822F0  4B FF F9 75 */	bl it_80285084
/* 80285714 002822F4  7F E3 FB 78 */	mr r3, r31
/* 80285718 002822F8  4B FF FA 29 */	bl it_80285140
/* 8028571C 002822FC  7F E3 FB 78 */	mr r3, r31
/* 80285720 00282300  4B FF FA DD */	bl it_802851FC
/* 80285724 00282304  7F E3 FB 78 */	mr r3, r31
/* 80285728 00282308  4B FF F7 09 */	bl it_80284E30
/* 8028572C 0028230C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80285730 00282310  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80285734 00282314  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80285738 00282318  38 21 00 40 */	addi r1, r1, 0x40
/* 8028573C 0028231C  7C 08 03 A6 */	mtlr r0
/* 80285740 00282320  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

bool it_80285744(Item_GObj* gobj)
{
    inlineA4(gobj);
    return false;
}

void it_8028578C(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool it_802857D8(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_80285424);
    return false;
}

static inline void inlineC0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.capsule.x4 = 4;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.star.yvel - ip->xDD4_itemVar.star.xvel) /
        (float) ip->xDD4_itemVar.capsule.x4;
}

static inline void inlineC1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C = 0;
    ip->xDD4_itemVar.sword.x20 = 4;
    ip->xDD4_itemVar.sword.x24 = 1;
    ip->xDD4_itemVar.sword.x28 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x2C = it_804DC8F4;
    ip->xDD4_itemVar.sword.x30 =
        (ip->xDD4_itemVar.sword.x2C - ip->xDD4_itemVar.sword.x28) *
        it_804DC8F8;
}

ASM void it_80285804(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    ip->xD50_landNum = 0;
    inlineC0(gobj);
    inlineC1(gobj);
    inlineA4(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 80285804 002823E4  7C 08 02 A6 */	mflr r0
/* 80285808 002823E8  90 01 00 04 */	stw r0, 4(r1)
/* 8028580C 002823EC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80285810 002823F0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80285814 002823F4  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80285818 002823F8  7C 7E 1B 78 */	mr r30, r3
/* 8028581C 002823FC  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80285820 00282400  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80285824 00282404  28 03 00 00 */	cmplwi r3, 0
/* 80285828 00282408  40 82 00 0C */	bne lbl_80285834
/* 8028582C 0028240C  38 00 00 00 */	li r0, 0
/* 80285830 00282410  48 00 00 08 */	b lbl_80285838
lbl_80285834:
/* 80285834 00282414  80 03 00 10 */	lwz r0, 0x10(r3)
lbl_80285838:
/* 80285838 00282418  7C 03 03 78 */	mr r3, r0
/* 8028583C 0028241C  38 80 00 10 */	li r4, 0x10
/* 80285840 00282420  48 0E C7 5D */	bl HSD_JObjClearFlagsAll
/* 80285844 00282424  38 7E 00 00 */	addi r3, r30, 0
/* 80285848 00282428  38 80 00 02 */	li r4, 2
/* 8028584C 0028242C  38 A0 00 02 */	li r5, 2
/* 80285850 00282430  4B FE 36 0D */	bl Item_80268E5C
/* 80285854 00282434  38 E0 00 00 */	li r7, 0
/* 80285858 00282438  90 FF 0D 50 */	stw r7, 0xd50(r31)
/* 8028585C 0028243C  38 C0 00 04 */	li r6, 4
/* 80285860 00282440  38 A0 FF FF */	li r5, -1
/* 80285864 00282444  81 1E 00 2C */	lwz r8, 0x2c(r30)
/* 80285868 00282448  3C 80 43 30 */	lis r4, 0x4330
/* 8028586C 0028244C  38 00 00 01 */	li r0, 1
/* 80285870 00282450  90 C8 0D D8 */	stw r6, 0xdd8(r8)
/* 80285874 00282454  7F C3 F3 78 */	mr r3, r30
/* 80285878 00282458  90 E8 0D DC */	stw r7, 0xddc(r8)
/* 8028587C 0028245C  90 A8 0D E0 */	stw r5, 0xde0(r8)
/* 80285880 00282460  C0 62 CF 00 */	lfs f3, it_804DC8E0
/* 80285884 00282464  D0 68 0D E8 */	stfs f3, 0xde8(r8)
/* 80285888 00282468  80 A8 0D D8 */	lwz r5, 0xdd8(r8)
/* 8028588C 0028246C  C0 48 0D E8 */	lfs f2, 0xde8(r8)
/* 80285890 00282470  6C A5 80 00 */	xoris r5, r5, 0x8000
/* 80285894 00282474  C0 08 0D E4 */	lfs f0, 0xde4(r8)
/* 80285898 00282478  90 A1 00 24 */	stw r5, 0x24(r1)
/* 8028589C 0028247C  C8 22 CF 08 */	lfd f1, it_804DC8E8
/* 802858A0 00282480  EC 42 00 28 */	fsubs f2, f2, f0
/* 802858A4 00282484  90 81 00 20 */	stw r4, 0x20(r1)
/* 802858A8 00282488  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 802858AC 0028248C  EC 00 08 28 */	fsubs f0, f0, f1
/* 802858B0 00282490  EC 02 00 24 */	fdivs f0, f2, f0
/* 802858B4 00282494  D0 08 0D EC */	stfs f0, 0xdec(r8)
/* 802858B8 00282498  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 802858BC 0028249C  90 E4 0D F0 */	stw r7, 0xdf0(r4)
/* 802858C0 002824A0  90 C4 0D F4 */	stw r6, 0xdf4(r4)
/* 802858C4 002824A4  90 04 0D F8 */	stw r0, 0xdf8(r4)
/* 802858C8 002824A8  D0 64 0D FC */	stfs f3, 0xdfc(r4)
/* 802858CC 002824AC  C0 02 CF 14 */	lfs f0, it_804DC8F4
/* 802858D0 002824B0  D0 04 0E 00 */	stfs f0, 0xe00(r4)
/* 802858D4 002824B4  C0 44 0E 00 */	lfs f2, 0xe00(r4)
/* 802858D8 002824B8  C0 24 0D FC */	lfs f1, 0xdfc(r4)
/* 802858DC 002824BC  C0 02 CF 18 */	lfs f0, it_804DC8F8
/* 802858E0 002824C0  EC 22 08 28 */	fsubs f1, f2, f1
/* 802858E4 002824C4  EC 01 00 32 */	fmuls f0, f1, f0
/* 802858E8 002824C8  D0 04 0E 04 */	stfs f0, 0xe04(r4)
/* 802858EC 002824CC  4B FF F7 99 */	bl it_80285084
/* 802858F0 002824D0  7F C3 F3 78 */	mr r3, r30
/* 802858F4 002824D4  4B FF F8 4D */	bl it_80285140
/* 802858F8 002824D8  7F C3 F3 78 */	mr r3, r30
/* 802858FC 002824DC  4B FF F9 01 */	bl it_802851FC
/* 80285900 002824E0  7F C3 F3 78 */	mr r3, r30
/* 80285904 002824E4  4B FF F5 2D */	bl it_80284E30
/* 80285908 002824E8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8028590C 002824EC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80285910 002824F0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80285914 002824F4  38 21 00 30 */	addi r1, r1, 0x30
/* 80285918 002824F8  7C 08 03 A6 */	mtlr r0
/* 8028591C 002824FC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline void inlineD0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x4 = 4;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) /
        ip->xDD4_itemVar.sword.x4;
}

static inline void inlineD1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = 0;
    ip->xDD4_itemVar.sword.x38 = attrs->x18;
    ip->xDD4_itemVar.sword.x3C = 1;
    ip->xDD4_itemVar.sword.x40 = attrs->x10;
    ip->xDD4_itemVar.sword.x44 = attrs->x14;
    ip->xDD4_itemVar.sword.x48 = (attrs->x14 - attrs->x10) / attrs->x18;
}

static inline void inlineD2(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = attrs->x18;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = -1;
    ip->xDD4_itemVar.sword.x44 = attrs->x10;
    ip->xDD4_itemVar.sword.x48 =
        (attrs->x10 - ip->xDD4_itemVar.sword.x40) / attrs->x18;
}

static inline void inlineD3(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_GObj* owner = ip->owner;
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    if (owner != NULL && ftLib_80086FA8(owner) != 1) {
        inlineD0(gobj);
    }
    if (ip->xDD4_itemVar.sword.x3C == 0) {
        if (ip->xDD4_itemVar.sword.x34 == ip->xDD4_itemVar.sword.x38) {
            if (ip->xDD4_itemVar.sword.x38 == 0) {
                inlineD1(gobj);
            } else if (ip->xDD4_itemVar.sword.x38 == attrs->x18) {
                inlineD2(gobj);
            }
        }
    }
}

ASM bool it_80285920(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    inlineD3(gobj);
    inlineA4(gobj);
    return false;
}

#else /* clang-format off */
{ nofralloc
/* 80285920 00282500  7C 08 02 A6 */	mflr r0
/* 80285924 00282504  90 01 00 04 */	stw r0, 4(r1)
/* 80285928 00282508  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8028592C 0028250C  93 E1 00 34 */	stw r31, 0x34(r1)
/* 80285930 00282510  7C 7F 1B 78 */	mr r31, r3
/* 80285934 00282514  93 C1 00 30 */	stw r30, 0x30(r1)
/* 80285938 00282518  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8028593C 0028251C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80285940 00282520  80 7E 05 18 */	lwz r3, 0x518(r30)
/* 80285944 00282524  80 9E 00 C4 */	lwz r4, 0xc4(r30)
/* 80285948 00282528  28 03 00 00 */	cmplwi r3, 0
/* 8028594C 0028252C  83 A4 00 04 */	lwz r29, 4(r4)
/* 80285950 00282530  41 82 00 68 */	beq lbl_802859B8
/* 80285954 00282534  4B E0 16 55 */	bl ftLib_80086FA8
/* 80285958 00282538  2C 03 00 01 */	cmpwi r3, 1
/* 8028595C 0028253C  41 82 00 5C */	beq lbl_802859B8
/* 80285960 00282540  80 BF 00 2C */	lwz r5, 0x2c(r31)
/* 80285964 00282544  38 00 00 04 */	li r0, 4
/* 80285968 00282548  38 80 00 00 */	li r4, 0
/* 8028596C 0028254C  90 05 0D D8 */	stw r0, 0xdd8(r5)
/* 80285970 00282550  38 60 FF FF */	li r3, -1
/* 80285974 00282554  3C 00 43 30 */	lis r0, 0x4330
/* 80285978 00282558  90 85 0D DC */	stw r4, 0xddc(r5)
/* 8028597C 0028255C  90 65 0D E0 */	stw r3, 0xde0(r5)
/* 80285980 00282560  C0 02 CF 00 */	lfs f0, it_804DC8E0
/* 80285984 00282564  D0 05 0D E8 */	stfs f0, 0xde8(r5)
/* 80285988 00282568  80 65 0D D8 */	lwz r3, 0xdd8(r5)
/* 8028598C 0028256C  C0 45 0D E8 */	lfs f2, 0xde8(r5)
/* 80285990 00282570  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80285994 00282574  C0 05 0D E4 */	lfs f0, 0xde4(r5)
/* 80285998 00282578  90 61 00 24 */	stw r3, 0x24(r1)
/* 8028599C 0028257C  C8 22 CF 08 */	lfd f1, it_804DC8E8
/* 802859A0 00282580  EC 42 00 28 */	fsubs f2, f2, f0
/* 802859A4 00282584  90 01 00 20 */	stw r0, 0x20(r1)
/* 802859A8 00282588  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 802859AC 0028258C  EC 00 08 28 */	fsubs f0, f0, f1
/* 802859B0 00282590  EC 02 00 24 */	fdivs f0, f2, f0
/* 802859B4 00282594  D0 05 0D EC */	stfs f0, 0xdec(r5)
lbl_802859B8:
/* 802859B8 00282598  80 1E 0E 10 */	lwz r0, 0xe10(r30)
/* 802859BC 0028259C  2C 00 00 00 */	cmpwi r0, 0
/* 802859C0 002825A0  40 82 00 F4 */	bne lbl_80285AB4
/* 802859C4 002825A4  80 1E 0E 08 */	lwz r0, 0xe08(r30)
/* 802859C8 002825A8  80 7E 0E 0C */	lwz r3, 0xe0c(r30)
/* 802859CC 002825AC  7C 00 18 00 */	cmpw r0, r3
/* 802859D0 002825B0  40 82 00 E4 */	bne lbl_80285AB4
/* 802859D4 002825B4  2C 03 00 00 */	cmpwi r3, 0
/* 802859D8 002825B8  40 82 00 70 */	bne lbl_80285A48
/* 802859DC 002825BC  80 DF 00 2C */	lwz r6, 0x2c(r31)
/* 802859E0 002825C0  38 80 00 00 */	li r4, 0
/* 802859E4 002825C4  38 60 00 01 */	li r3, 1
/* 802859E8 002825C8  80 A6 00 C4 */	lwz r5, 0xc4(r6)
/* 802859EC 002825CC  3C 00 43 30 */	lis r0, 0x4330
/* 802859F0 002825D0  80 A5 00 04 */	lwz r5, 4(r5)
/* 802859F4 002825D4  90 86 0E 08 */	stw r4, 0xe08(r6)
/* 802859F8 002825D8  80 85 00 18 */	lwz r4, 0x18(r5)
/* 802859FC 002825DC  90 86 0E 0C */	stw r4, 0xe0c(r6)
/* 80285A00 002825E0  90 66 0E 10 */	stw r3, 0xe10(r6)
/* 80285A04 002825E4  C0 05 00 10 */	lfs f0, 0x10(r5)
/* 80285A08 002825E8  D0 06 0E 14 */	stfs f0, 0xe14(r6)
/* 80285A0C 002825EC  C0 05 00 14 */	lfs f0, 0x14(r5)
/* 80285A10 002825F0  D0 06 0E 18 */	stfs f0, 0xe18(r6)
/* 80285A14 002825F4  80 65 00 18 */	lwz r3, 0x18(r5)
/* 80285A18 002825F8  C0 45 00 14 */	lfs f2, 0x14(r5)
/* 80285A1C 002825FC  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80285A20 00282600  C0 05 00 10 */	lfs f0, 0x10(r5)
/* 80285A24 00282604  90 61 00 24 */	stw r3, 0x24(r1)
/* 80285A28 00282608  C8 22 CF 08 */	lfd f1, it_804DC8E8
/* 80285A2C 0028260C  EC 42 00 28 */	fsubs f2, f2, f0
/* 80285A30 00282610  90 01 00 20 */	stw r0, 0x20(r1)
/* 80285A34 00282614  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80285A38 00282618  EC 00 08 28 */	fsubs f0, f0, f1
/* 80285A3C 0028261C  EC 02 00 24 */	fdivs f0, f2, f0
/* 80285A40 00282620  D0 06 0E 1C */	stfs f0, 0xe1c(r6)
/* 80285A44 00282624  48 00 00 70 */	b lbl_80285AB4
lbl_80285A48:
/* 80285A48 00282628  80 1D 00 18 */	lwz r0, 0x18(r29)
/* 80285A4C 0028262C  7C 03 00 00 */	cmpw r3, r0
/* 80285A50 00282630  40 82 00 64 */	bne lbl_80285AB4
/* 80285A54 00282634  80 FF 00 2C */	lwz r7, 0x2c(r31)
/* 80285A58 00282638  38 80 00 00 */	li r4, 0
/* 80285A5C 0028263C  38 60 FF FF */	li r3, -1
/* 80285A60 00282640  80 A7 00 C4 */	lwz r5, 0xc4(r7)
/* 80285A64 00282644  3C 00 43 30 */	lis r0, 0x4330
/* 80285A68 00282648  80 C5 00 04 */	lwz r6, 4(r5)
/* 80285A6C 0028264C  80 A6 00 18 */	lwz r5, 0x18(r6)
/* 80285A70 00282650  90 A7 0E 08 */	stw r5, 0xe08(r7)
/* 80285A74 00282654  90 87 0E 0C */	stw r4, 0xe0c(r7)
/* 80285A78 00282658  90 67 0E 10 */	stw r3, 0xe10(r7)
/* 80285A7C 0028265C  C0 06 00 10 */	lfs f0, 0x10(r6)
/* 80285A80 00282660  D0 07 0E 18 */	stfs f0, 0xe18(r7)
/* 80285A84 00282664  80 66 00 18 */	lwz r3, 0x18(r6)
/* 80285A88 00282668  C0 46 00 10 */	lfs f2, 0x10(r6)
/* 80285A8C 0028266C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80285A90 00282670  C0 07 0E 14 */	lfs f0, 0xe14(r7)
/* 80285A94 00282674  90 61 00 24 */	stw r3, 0x24(r1)
/* 80285A98 00282678  C8 22 CF 08 */	lfd f1, it_804DC8E8
/* 80285A9C 0028267C  EC 42 00 28 */	fsubs f2, f2, f0
/* 80285AA0 00282680  90 01 00 20 */	stw r0, 0x20(r1)
/* 80285AA4 00282684  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80285AA8 00282688  EC 00 08 28 */	fsubs f0, f0, f1
/* 80285AAC 0028268C  EC 02 00 24 */	fdivs f0, f2, f0
/* 80285AB0 00282690  D0 07 0E 1C */	stfs f0, 0xe1c(r7)
lbl_80285AB4:
/* 80285AB4 00282694  7F E3 FB 78 */	mr r3, r31
/* 80285AB8 00282698  4B FF F5 CD */	bl it_80285084
/* 80285ABC 0028269C  7F E3 FB 78 */	mr r3, r31
/* 80285AC0 002826A0  4B FF F6 81 */	bl it_80285140
/* 80285AC4 002826A4  7F E3 FB 78 */	mr r3, r31
/* 80285AC8 002826A8  4B FF F7 35 */	bl it_802851FC
/* 80285ACC 002826AC  7F E3 FB 78 */	mr r3, r31
/* 80285AD0 002826B0  4B FF F3 61 */	bl it_80284E30
/* 80285AD4 002826B4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80285AD8 002826B8  38 60 00 00 */	li r3, 0
/* 80285ADC 002826BC  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80285AE0 002826C0  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80285AE4 002826C4  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80285AE8 002826C8  38 21 00 38 */	addi r1, r1, 0x38
/* 80285AEC 002826CC  7C 08 03 A6 */	mtlr r0
/* 80285AF0 002826D0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void it_80285AF4(Item_GObj* gobj) {}

bool it_80285AF8(Item_GObj* gobj)
{
    return false;
}

static inline void inlineE0(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    Item_80268E5C(gobj, 3, 6);
}

static inline void inlineE1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.capsule.x4 = 4;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) /
        ip->xDD4_itemVar.sword.x4;
}

static inline void inlineE2(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C = 4;
    ip->xDD4_itemVar.sword.x20 = 0;
    ip->xDD4_itemVar.sword.x24 = -1;
    ip->xDD4_itemVar.sword.x2C = it_804DC8E0;
    ip->xDD4_itemVar.sword.x30 =
        (ip->xDD4_itemVar.sword.x2C - ip->xDD4_itemVar.sword.x28) /
        (float) ip->xDD4_itemVar.sword.x1C;
}

static inline void inlineE3(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = attrs->x18;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = -1;
    ip->xDD4_itemVar.sword.x44 = attrs->x10;
    ip->xDD4_itemVar.sword.x48 =
        (attrs->x10 - ip->xDD4_itemVar.sword.x40) / (float) attrs->x18;
}

ASM void it_80285B00(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    inlineE0(gobj);
    inlineE1(gobj);
    inlineE2(gobj);
    inlineE3(gobj);
    inlineA4(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 80285B00 002826E0  7C 08 02 A6 */	mflr r0
/* 80285B04 002826E4  90 01 00 04 */	stw r0, 4(r1)
/* 80285B08 002826E8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80285B0C 002826EC  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80285B10 002826F0  7C 7F 1B 78 */	mr r31, r3
/* 80285B14 002826F4  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80285B18 002826F8  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80285B1C 002826FC  28 03 00 00 */	cmplwi r3, 0
/* 80285B20 00282700  40 82 00 0C */	bne lbl_80285B2C
/* 80285B24 00282704  38 00 00 00 */	li r0, 0
/* 80285B28 00282708  48 00 00 08 */	b lbl_80285B30
lbl_80285B2C:
/* 80285B2C 0028270C  80 03 00 10 */	lwz r0, 0x10(r3)
lbl_80285B30:
/* 80285B30 00282710  7C 1E 03 78 */	mr r30, r0
/* 80285B34 00282714  38 7F 00 00 */	addi r3, r31, 0
/* 80285B38 00282718  4B FE 58 59 */	bl it_8026B390
/* 80285B3C 0028271C  38 7E 00 00 */	addi r3, r30, 0
/* 80285B40 00282720  38 80 00 10 */	li r4, 0x10
/* 80285B44 00282724  48 0E C4 59 */	bl HSD_JObjClearFlagsAll
/* 80285B48 00282728  38 7F 00 00 */	addi r3, r31, 0
/* 80285B4C 0028272C  38 80 00 03 */	li r4, 3
/* 80285B50 00282730  38 A0 00 06 */	li r5, 6
/* 80285B54 00282734  4B FE 33 09 */	bl Item_80268E5C
/* 80285B58 00282738  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285B5C 0028273C  38 80 00 04 */	li r4, 4
/* 80285B60 00282740  38 E0 00 00 */	li r7, 0
/* 80285B64 00282744  90 88 0D D8 */	stw r4, 0xdd8(r8)
/* 80285B68 00282748  38 C0 FF FF */	li r6, -1
/* 80285B6C 0028274C  3C A0 43 30 */	lis r5, 0x4330
/* 80285B70 00282750  90 E8 0D DC */	stw r7, 0xddc(r8)
/* 80285B74 00282754  7F E3 FB 78 */	mr r3, r31
/* 80285B78 00282758  90 C8 0D E0 */	stw r6, 0xde0(r8)
/* 80285B7C 0028275C  C0 62 CF 00 */	lfs f3, it_804DC8E0
/* 80285B80 00282760  D0 68 0D E8 */	stfs f3, 0xde8(r8)
/* 80285B84 00282764  80 08 0D D8 */	lwz r0, 0xdd8(r8)
/* 80285B88 00282768  C0 28 0D E8 */	lfs f1, 0xde8(r8)
/* 80285B8C 0028276C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285B90 00282770  C0 08 0D E4 */	lfs f0, 0xde4(r8)
/* 80285B94 00282774  90 01 00 34 */	stw r0, 0x34(r1)
/* 80285B98 00282778  C8 42 CF 08 */	lfd f2, it_804DC8E8
/* 80285B9C 0028277C  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285BA0 00282780  90 A1 00 30 */	stw r5, 0x30(r1)
/* 80285BA4 00282784  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80285BA8 00282788  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285BAC 0028278C  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285BB0 00282790  D0 08 0D EC */	stfs f0, 0xdec(r8)
/* 80285BB4 00282794  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285BB8 00282798  90 88 0D F0 */	stw r4, 0xdf0(r8)
/* 80285BBC 0028279C  90 E8 0D F4 */	stw r7, 0xdf4(r8)
/* 80285BC0 002827A0  90 C8 0D F8 */	stw r6, 0xdf8(r8)
/* 80285BC4 002827A4  D0 68 0E 00 */	stfs f3, 0xe00(r8)
/* 80285BC8 002827A8  80 08 0D F0 */	lwz r0, 0xdf0(r8)
/* 80285BCC 002827AC  C0 28 0E 00 */	lfs f1, 0xe00(r8)
/* 80285BD0 002827B0  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285BD4 002827B4  C0 08 0D FC */	lfs f0, 0xdfc(r8)
/* 80285BD8 002827B8  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80285BDC 002827BC  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285BE0 002827C0  90 A1 00 28 */	stw r5, 0x28(r1)
/* 80285BE4 002827C4  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 80285BE8 002827C8  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285BEC 002827CC  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285BF0 002827D0  D0 08 0E 04 */	stfs f0, 0xe04(r8)
/* 80285BF4 002827D4  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285BF8 002827D8  80 88 00 C4 */	lwz r4, 0xc4(r8)
/* 80285BFC 002827DC  80 84 00 04 */	lwz r4, 4(r4)
/* 80285C00 002827E0  80 04 00 18 */	lwz r0, 0x18(r4)
/* 80285C04 002827E4  90 08 0E 08 */	stw r0, 0xe08(r8)
/* 80285C08 002827E8  90 E8 0E 0C */	stw r7, 0xe0c(r8)
/* 80285C0C 002827EC  90 C8 0E 10 */	stw r6, 0xe10(r8)
/* 80285C10 002827F0  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 80285C14 002827F4  D0 08 0E 18 */	stfs f0, 0xe18(r8)
/* 80285C18 002827F8  80 04 00 18 */	lwz r0, 0x18(r4)
/* 80285C1C 002827FC  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 80285C20 00282800  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285C24 00282804  C0 08 0E 14 */	lfs f0, 0xe14(r8)
/* 80285C28 00282808  90 01 00 24 */	stw r0, 0x24(r1)
/* 80285C2C 0028280C  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285C30 00282810  90 A1 00 20 */	stw r5, 0x20(r1)
/* 80285C34 00282814  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80285C38 00282818  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285C3C 0028281C  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285C40 00282820  D0 08 0E 1C */	stfs f0, 0xe1c(r8)
/* 80285C44 00282824  4B FF F4 41 */	bl it_80285084
/* 80285C48 00282828  7F E3 FB 78 */	mr r3, r31
/* 80285C4C 0028282C  4B FF F4 F5 */	bl it_80285140
/* 80285C50 00282830  7F E3 FB 78 */	mr r3, r31
/* 80285C54 00282834  4B FF F5 A9 */	bl it_802851FC
/* 80285C58 00282838  7F E3 FB 78 */	mr r3, r31
/* 80285C5C 0028283C  4B FF F1 D5 */	bl it_80284E30
/* 80285C60 00282840  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80285C64 00282844  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80285C68 00282848  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80285C6C 0028284C  38 21 00 40 */	addi r1, r1, 0x40
/* 80285C70 00282850  7C 08 03 A6 */	mtlr r0
/* 80285C74 00282854  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline void inlineF0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.capsule.x4 = 4;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) /
        ip->xDD4_itemVar.sword.x4;
}

static inline void inlineF1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C = 4;
    ip->xDD4_itemVar.sword.x20 = 0;
    ip->xDD4_itemVar.sword.x24 = -1;
    ip->xDD4_itemVar.sword.x2C = it_804DC8E0;
    ip->xDD4_itemVar.sword.x30 =
        (ip->xDD4_itemVar.sword.x2C - ip->xDD4_itemVar.sword.x28) /
        (float) ip->xDD4_itemVar.sword.x1C;
}

static inline void inlineF2(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = attrs->x18;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = -1;
    ip->xDD4_itemVar.sword.x44 = attrs->x10;
    ip->xDD4_itemVar.sword.x48 =
        (attrs->x10 - ip->xDD4_itemVar.sword.x40) / attrs->x18;
}

ASM void it_80285C78(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo #inlineE0
    {
        HSD_JObj* jobj = GET_JOBJ(gobj);
        HSD_JObj* child = HSD_JObjGetChild(jobj);
        it_8026B390(gobj);
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
        Item_80268E5C(gobj, 3, 6);
    }
    inlineF0(gobj);
    inlineF1(gobj);
    inlineF2(gobj);
    inlineA4(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 80285C78 00282858  7C 08 02 A6 */	mflr r0
/* 80285C7C 0028285C  90 01 00 04 */	stw r0, 4(r1)
/* 80285C80 00282860  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80285C84 00282864  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80285C88 00282868  7C 7F 1B 78 */	mr r31, r3
/* 80285C8C 0028286C  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80285C90 00282870  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80285C94 00282874  28 03 00 00 */	cmplwi r3, 0
/* 80285C98 00282878  40 82 00 0C */	bne lbl_80285CA4
/* 80285C9C 0028287C  38 00 00 00 */	li r0, 0
/* 80285CA0 00282880  48 00 00 08 */	b lbl_80285CA8
lbl_80285CA4:
/* 80285CA4 00282884  80 03 00 10 */	lwz r0, 0x10(r3)
lbl_80285CA8:
/* 80285CA8 00282888  7C 1E 03 78 */	mr r30, r0
/* 80285CAC 0028288C  38 7F 00 00 */	addi r3, r31, 0
/* 80285CB0 00282890  4B FE 56 E1 */	bl it_8026B390
/* 80285CB4 00282894  38 7E 00 00 */	addi r3, r30, 0
/* 80285CB8 00282898  38 80 00 10 */	li r4, 0x10
/* 80285CBC 0028289C  48 0E C2 E1 */	bl HSD_JObjClearFlagsAll
/* 80285CC0 002828A0  38 7F 00 00 */	addi r3, r31, 0
/* 80285CC4 002828A4  38 80 00 03 */	li r4, 3
/* 80285CC8 002828A8  38 A0 00 06 */	li r5, 6
/* 80285CCC 002828AC  4B FE 31 91 */	bl Item_80268E5C
/* 80285CD0 002828B0  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285CD4 002828B4  38 80 00 04 */	li r4, 4
/* 80285CD8 002828B8  38 E0 00 00 */	li r7, 0
/* 80285CDC 002828BC  90 88 0D D8 */	stw r4, 0xdd8(r8)
/* 80285CE0 002828C0  38 C0 FF FF */	li r6, -1
/* 80285CE4 002828C4  3C A0 43 30 */	lis r5, 0x4330
/* 80285CE8 002828C8  90 E8 0D DC */	stw r7, 0xddc(r8)
/* 80285CEC 002828CC  7F E3 FB 78 */	mr r3, r31
/* 80285CF0 002828D0  90 C8 0D E0 */	stw r6, 0xde0(r8)
/* 80285CF4 002828D4  C0 62 CF 00 */	lfs f3, it_804DC8E0
/* 80285CF8 002828D8  D0 68 0D E8 */	stfs f3, 0xde8(r8)
/* 80285CFC 002828DC  80 08 0D D8 */	lwz r0, 0xdd8(r8)
/* 80285D00 002828E0  C0 28 0D E8 */	lfs f1, 0xde8(r8)
/* 80285D04 002828E4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285D08 002828E8  C0 08 0D E4 */	lfs f0, 0xde4(r8)
/* 80285D0C 002828EC  90 01 00 34 */	stw r0, 0x34(r1)
/* 80285D10 002828F0  C8 42 CF 08 */	lfd f2, it_804DC8E8
/* 80285D14 002828F4  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285D18 002828F8  90 A1 00 30 */	stw r5, 0x30(r1)
/* 80285D1C 002828FC  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80285D20 00282900  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285D24 00282904  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285D28 00282908  D0 08 0D EC */	stfs f0, 0xdec(r8)
/* 80285D2C 0028290C  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285D30 00282910  90 88 0D F0 */	stw r4, 0xdf0(r8)
/* 80285D34 00282914  90 E8 0D F4 */	stw r7, 0xdf4(r8)
/* 80285D38 00282918  90 C8 0D F8 */	stw r6, 0xdf8(r8)
/* 80285D3C 0028291C  D0 68 0E 00 */	stfs f3, 0xe00(r8)
/* 80285D40 00282920  80 08 0D F0 */	lwz r0, 0xdf0(r8)
/* 80285D44 00282924  C0 28 0E 00 */	lfs f1, 0xe00(r8)
/* 80285D48 00282928  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285D4C 0028292C  C0 08 0D FC */	lfs f0, 0xdfc(r8)
/* 80285D50 00282930  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80285D54 00282934  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285D58 00282938  90 A1 00 28 */	stw r5, 0x28(r1)
/* 80285D5C 0028293C  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 80285D60 00282940  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285D64 00282944  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285D68 00282948  D0 08 0E 04 */	stfs f0, 0xe04(r8)
/* 80285D6C 0028294C  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285D70 00282950  80 88 00 C4 */	lwz r4, 0xc4(r8)
/* 80285D74 00282954  80 84 00 04 */	lwz r4, 4(r4)
/* 80285D78 00282958  80 04 00 18 */	lwz r0, 0x18(r4)
/* 80285D7C 0028295C  90 08 0E 08 */	stw r0, 0xe08(r8)
/* 80285D80 00282960  90 E8 0E 0C */	stw r7, 0xe0c(r8)
/* 80285D84 00282964  90 C8 0E 10 */	stw r6, 0xe10(r8)
/* 80285D88 00282968  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 80285D8C 0028296C  D0 08 0E 18 */	stfs f0, 0xe18(r8)
/* 80285D90 00282970  80 04 00 18 */	lwz r0, 0x18(r4)
/* 80285D94 00282974  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 80285D98 00282978  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285D9C 0028297C  C0 08 0E 14 */	lfs f0, 0xe14(r8)
/* 80285DA0 00282980  90 01 00 24 */	stw r0, 0x24(r1)
/* 80285DA4 00282984  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285DA8 00282988  90 A1 00 20 */	stw r5, 0x20(r1)
/* 80285DAC 0028298C  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80285DB0 00282990  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285DB4 00282994  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285DB8 00282998  D0 08 0E 1C */	stfs f0, 0xe1c(r8)
/* 80285DBC 0028299C  4B FF F2 C9 */	bl it_80285084
/* 80285DC0 002829A0  7F E3 FB 78 */	mr r3, r31
/* 80285DC4 002829A4  4B FF F3 7D */	bl it_80285140
/* 80285DC8 002829A8  7F E3 FB 78 */	mr r3, r31
/* 80285DCC 002829AC  4B FF F4 31 */	bl it_802851FC
/* 80285DD0 002829B0  7F E3 FB 78 */	mr r3, r31
/* 80285DD4 002829B4  4B FF F0 5D */	bl it_80284E30
/* 80285DD8 002829B8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80285DDC 002829BC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80285DE0 002829C0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80285DE4 002829C4  38 21 00 40 */	addi r1, r1, 0x40
/* 80285DE8 002829C8  7C 08 03 A6 */	mtlr r0
/* 80285DEC 002829CC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline void inlineG0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.capsule.x4 = 4;
    ip->xDD4_itemVar.sword.x8 = 0;
    ip->xDD4_itemVar.sword.xC = -1;
    ip->xDD4_itemVar.sword.x14 = it_804DC8E0;
    ip->xDD4_itemVar.sword.x18 =
        (ip->xDD4_itemVar.sword.x14 - ip->xDD4_itemVar.sword.x10) /
        ip->xDD4_itemVar.sword.x4;
}

static inline void inlineG1(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sword.x1C = 4;
    ip->xDD4_itemVar.sword.x20 = 0;
    ip->xDD4_itemVar.sword.x24 = -1;
    ip->xDD4_itemVar.sword.x2C = it_804DC8E0;
    ip->xDD4_itemVar.sword.x30 =
        (ip->xDD4_itemVar.sword.x2C - ip->xDD4_itemVar.sword.x28) /
        ip->xDD4_itemVar.sword.x1C;
}

static inline void inlineG2(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSword_UnkArticle1* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->xDD4_itemVar.sword.x34 = attrs->x18;
    ip->xDD4_itemVar.sword.x38 = 0;
    ip->xDD4_itemVar.sword.x3C = -1;
    ip->xDD4_itemVar.sword.x44 = attrs->x10;
    ip->xDD4_itemVar.sword.x48 =
        (attrs->x10 - ip->xDD4_itemVar.sword.x40) / attrs->x18;
}

ASM void it_80285DF0(Item_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    inlineG0(gobj);
    inlineG1(gobj);
    inlineG2(gobj);
    inlineA4(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 80285DF0 002829D0  7C 08 02 A6 */	mflr r0
/* 80285DF4 002829D4  38 80 00 04 */	li r4, 4
/* 80285DF8 002829D8  90 01 00 04 */	stw r0, 4(r1)
/* 80285DFC 002829DC  38 A0 00 02 */	li r5, 2
/* 80285E00 002829E0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80285E04 002829E4  93 E1 00 34 */	stw r31, 0x34(r1)
/* 80285E08 002829E8  3B E3 00 00 */	addi r31, r3, 0
/* 80285E0C 002829EC  4B FE 30 51 */	bl Item_80268E5C
/* 80285E10 002829F0  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285E14 002829F4  38 80 00 04 */	li r4, 4
/* 80285E18 002829F8  38 E0 00 00 */	li r7, 0
/* 80285E1C 002829FC  90 88 0D D8 */	stw r4, 0xdd8(r8)
/* 80285E20 00282A00  38 C0 FF FF */	li r6, -1
/* 80285E24 00282A04  3C A0 43 30 */	lis r5, 0x4330
/* 80285E28 00282A08  90 E8 0D DC */	stw r7, 0xddc(r8)
/* 80285E2C 00282A0C  7F E3 FB 78 */	mr r3, r31
/* 80285E30 00282A10  90 C8 0D E0 */	stw r6, 0xde0(r8)
/* 80285E34 00282A14  C0 62 CF 00 */	lfs f3, it_804DC8E0
/* 80285E38 00282A18  D0 68 0D E8 */	stfs f3, 0xde8(r8)
/* 80285E3C 00282A1C  80 08 0D D8 */	lwz r0, 0xdd8(r8)
/* 80285E40 00282A20  C0 28 0D E8 */	lfs f1, 0xde8(r8)
/* 80285E44 00282A24  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285E48 00282A28  C0 08 0D E4 */	lfs f0, 0xde4(r8)
/* 80285E4C 00282A2C  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80285E50 00282A30  C8 42 CF 08 */	lfd f2, it_804DC8E8
/* 80285E54 00282A34  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285E58 00282A38  90 A1 00 28 */	stw r5, 0x28(r1)
/* 80285E5C 00282A3C  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 80285E60 00282A40  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285E64 00282A44  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285E68 00282A48  D0 08 0D EC */	stfs f0, 0xdec(r8)
/* 80285E6C 00282A4C  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285E70 00282A50  90 88 0D F0 */	stw r4, 0xdf0(r8)
/* 80285E74 00282A54  90 E8 0D F4 */	stw r7, 0xdf4(r8)
/* 80285E78 00282A58  90 C8 0D F8 */	stw r6, 0xdf8(r8)
/* 80285E7C 00282A5C  D0 68 0E 00 */	stfs f3, 0xe00(r8)
/* 80285E80 00282A60  80 08 0D F0 */	lwz r0, 0xdf0(r8)
/* 80285E84 00282A64  C0 28 0E 00 */	lfs f1, 0xe00(r8)
/* 80285E88 00282A68  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285E8C 00282A6C  C0 08 0D FC */	lfs f0, 0xdfc(r8)
/* 80285E90 00282A70  90 01 00 24 */	stw r0, 0x24(r1)
/* 80285E94 00282A74  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285E98 00282A78  90 A1 00 20 */	stw r5, 0x20(r1)
/* 80285E9C 00282A7C  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 80285EA0 00282A80  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285EA4 00282A84  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285EA8 00282A88  D0 08 0E 04 */	stfs f0, 0xe04(r8)
/* 80285EAC 00282A8C  81 1F 00 2C */	lwz r8, 0x2c(r31)
/* 80285EB0 00282A90  80 88 00 C4 */	lwz r4, 0xc4(r8)
/* 80285EB4 00282A94  80 84 00 04 */	lwz r4, 4(r4)
/* 80285EB8 00282A98  80 04 00 18 */	lwz r0, 0x18(r4)
/* 80285EBC 00282A9C  90 08 0E 08 */	stw r0, 0xe08(r8)
/* 80285EC0 00282AA0  90 E8 0E 0C */	stw r7, 0xe0c(r8)
/* 80285EC4 00282AA4  90 C8 0E 10 */	stw r6, 0xe10(r8)
/* 80285EC8 00282AA8  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 80285ECC 00282AAC  D0 08 0E 18 */	stfs f0, 0xe18(r8)
/* 80285ED0 00282AB0  80 04 00 18 */	lwz r0, 0x18(r4)
/* 80285ED4 00282AB4  C0 24 00 10 */	lfs f1, 0x10(r4)
/* 80285ED8 00282AB8  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 80285EDC 00282ABC  C0 08 0E 14 */	lfs f0, 0xe14(r8)
/* 80285EE0 00282AC0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80285EE4 00282AC4  EC 21 00 28 */	fsubs f1, f1, f0
/* 80285EE8 00282AC8  90 A1 00 18 */	stw r5, 0x18(r1)
/* 80285EEC 00282ACC  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 80285EF0 00282AD0  EC 00 10 28 */	fsubs f0, f0, f2
/* 80285EF4 00282AD4  EC 01 00 24 */	fdivs f0, f1, f0
/* 80285EF8 00282AD8  D0 08 0E 1C */	stfs f0, 0xe1c(r8)
/* 80285EFC 00282ADC  4B FF F1 89 */	bl it_80285084
/* 80285F00 00282AE0  7F E3 FB 78 */	mr r3, r31
/* 80285F04 00282AE4  4B FF F2 3D */	bl it_80285140
/* 80285F08 00282AE8  7F E3 FB 78 */	mr r3, r31
/* 80285F0C 00282AEC  4B FF F2 F1 */	bl it_802851FC
/* 80285F10 00282AF0  7F E3 FB 78 */	mr r3, r31
/* 80285F14 00282AF4  4B FF EF 1D */	bl it_80284E30
/* 80285F18 00282AF8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80285F1C 00282AFC  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80285F20 00282B00  38 21 00 38 */	addi r1, r1, 0x38
/* 80285F24 00282B04  7C 08 03 A6 */	mtlr r0
/* 80285F28 00282B08  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

bool it_80285F2C(Item_GObj* gobj)
{
    inlineA4(gobj);
    return false;
}

void it_80285F74(Item_GObj* gobj) {}

bool it_80285F78(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_80285424, it_802855F8);
    return false;
}

bool it_80285FAC(Item_GObj* gobj)
{
    if (GET_ITEM(gobj)->msid == 3) {
        itColl_BounceOffVictim(gobj);
    }
    return false;
}

bool it_80285FE0(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_80286000(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_80286024(Item_GObj* gobj)
{
    itColl_BounceOffVictim(gobj);
    return false;
}

bool itSword_BounceOffShield(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_80286068(Item_GObj* gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
