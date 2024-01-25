#include <platform.h>
#include <dolphin/gx/forward.h>

#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXEnum.h>

#ifdef MUST_MATCH
#include "dolphin/gx/GXTransform.h"

#include <placeholder.h>
#endif

#ifdef MUST_MATCH
static u32 GXAttr_804D5BB0 = 0x00040102;
static u32 GXAttr_804D5BB4 = 0x00080102;
static u64 GXAttr_804D5BB8 = 0x000C010200000000;
#endif

void GXAttr_8033CA6C(void);
void GXAttr_8033CA8C(void);
void GXAttr_8033CAAC(void);
void GXAttr_8033CACC(void);
void GXAttr_8033CAEC(void);
void GXAttr_8033CB04(void);
void GXAttr_8033CB24(void);

void GXAttr_8033C8E0(void);
void GXAttr_8033C8EC(void);
void GXAttr_8033C8F8(void);
void GXAttr_8033C904(void);
void GXAttr_8033C920(void);
void GXAttr_8033C928(void);
void GXAttr_8033C930(void);
void GXAttr_8033C938(void);
void GXAttr_8033C940(void);
void GXAttr_8033C948(void);
void GXAttr_8033C950(void);
void GXAttr_8033C958(void);
void GXAttr_8033C95C(void);
void GXAttr_8033C910(void);
void GXAttr_8033C918(void);

#ifdef MUST_MATCH

// https://decomp.me/scratch/d4i4k // 95 (98.90%)
#pragma push
asm void __GXXfVtxSpecs(void)
{ // clang-format off
    nofralloc
/* 8033BDA8 00338988  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033BDAC 0033898C  80 85 00 14 */	lwz r4, 0x14(r5)
/* 8033BDB0 00338990  54 80 9F BF */	rlwinm. r0, r4, 0x13, 0x1e, 0x1f
/* 8033BDB4 00338994  41 82 00 0C */	beq lbl_8033BDC0
/* 8033BDB8 00338998  38 60 00 01 */	li r3, 1
/* 8033BDBC 0033899C  48 00 00 08 */	b lbl_8033BDC4
lbl_8033BDC0:
/* 8033BDC0 003389A0  38 60 00 00 */	li r3, 0
lbl_8033BDC4:
/* 8033BDC4 003389A4  54 80 8F BF */	rlwinm. r0, r4, 0x11, 0x1e, 0x1f
/* 8033BDC8 003389A8  41 82 00 0C */	beq lbl_8033BDD4
/* 8033BDCC 003389AC  38 80 00 01 */	li r4, 1
/* 8033BDD0 003389B0  48 00 00 08 */	b lbl_8033BDD8
lbl_8033BDD4:
/* 8033BDD4 003389B4  38 80 00 00 */	li r4, 0
lbl_8033BDD8:
/* 8033BDD8 003389B8  88 05 04 1D */	lbz r0, 0x41d(r5)
/* 8033BDDC 003389BC  7C E3 22 14 */	add r7, r3, r4
/* 8033BDE0 003389C0  28 00 00 00 */	cmplwi r0, 0
/* 8033BDE4 003389C4  41 82 00 0C */	beq lbl_8033BDF0
/* 8033BDE8 003389C8  38 80 00 02 */	li r4, 2
/* 8033BDEC 003389CC  48 00 00 1C */	b lbl_8033BE08
lbl_8033BDF0:
/* 8033BDF0 003389D0  88 05 04 1C */	lbz r0, 0x41c(r5)
/* 8033BDF4 003389D4  28 00 00 00 */	cmplwi r0, 0
/* 8033BDF8 003389D8  41 82 00 0C */	beq lbl_8033BE04
/* 8033BDFC 003389DC  38 80 00 01 */	li r4, 1
/* 8033BE00 003389E0  48 00 00 08 */	b lbl_8033BE08
lbl_8033BE04:
/* 8033BE04 003389E4  38 80 00 00 */	li r4, 0
lbl_8033BE08:
/* 8033BE08 003389E8  80 C5 00 18 */	lwz r6, 0x18(r5)
/* 8033BE0C 003389EC  54 C0 07 BF */	clrlwi. r0, r6, 0x1e
/* 8033BE10 003389F0  41 82 00 0C */	beq lbl_8033BE1C
/* 8033BE14 003389F4  38 60 00 01 */	li r3, 1
/* 8033BE18 003389F8  48 00 00 08 */	b lbl_8033BE20
lbl_8033BE1C:
/* 8033BE1C 003389FC  38 60 00 00 */	li r3, 0
lbl_8033BE20:
/* 8033BE20 00338A00  54 C0 F7 BF */	rlwinm. r0, r6, 0x1e, 0x1e, 0x1f
/* 8033BE24 00338A04  41 82 00 0C */	beq lbl_8033BE30
/* 8033BE28 00338A08  38 A0 00 01 */	li r5, 1
/* 8033BE2C 00338A0C  48 00 00 08 */	b lbl_8033BE34
lbl_8033BE30:
/* 8033BE30 00338A10  38 A0 00 00 */	li r5, 0
lbl_8033BE34:
/* 8033BE34 00338A14  54 C0 E7 BF */	rlwinm. r0, r6, 0x1c, 0x1e, 0x1f
/* 8033BE38 00338A18  7D 03 2A 14 */	add r8, r3, r5
/* 8033BE3C 00338A1C  41 82 00 0C */	beq lbl_8033BE48
/* 8033BE40 00338A20  38 60 00 01 */	li r3, 1
/* 8033BE44 00338A24  48 00 00 08 */	b lbl_8033BE4C
lbl_8033BE48:
/* 8033BE48 00338A28  38 60 00 00 */	li r3, 0
lbl_8033BE4C:
/* 8033BE4C 00338A2C  54 C0 D7 BF */	rlwinm. r0, r6, 0x1a, 0x1e, 0x1f
/* 8033BE50 00338A30  7D 08 1A 14 */	add r8, r8, r3
/* 8033BE54 00338A34  41 82 00 0C */	beq lbl_8033BE60
/* 8033BE58 00338A38  38 60 00 01 */	li r3, 1
/* 8033BE5C 00338A3C  48 00 00 08 */	b lbl_8033BE64
lbl_8033BE60:
/* 8033BE60 00338A40  38 60 00 00 */	li r3, 0
lbl_8033BE64:
/* 8033BE64 00338A44  54 C0 C7 BF */	rlwinm. r0, r6, 0x18, 0x1e, 0x1f
/* 8033BE68 00338A48  7D 08 1A 14 */	add r8, r8, r3
/* 8033BE6C 00338A4C  41 82 00 0C */	beq lbl_8033BE78
/* 8033BE70 00338A50  38 60 00 01 */	li r3, 1
/* 8033BE74 00338A54  48 00 00 08 */	b lbl_8033BE7C
lbl_8033BE78:
/* 8033BE78 00338A58  38 60 00 00 */	li r3, 0
lbl_8033BE7C:
/* 8033BE7C 00338A5C  54 C0 B7 BF */	rlwinm. r0, r6, 0x16, 0x1e, 0x1f
/* 8033BE80 00338A60  7D 08 1A 14 */	add r8, r8, r3
/* 8033BE84 00338A64  41 82 00 0C */	beq lbl_8033BE90
/* 8033BE88 00338A68  38 60 00 01 */	li r3, 1
/* 8033BE8C 00338A6C  48 00 00 08 */	b lbl_8033BE94
lbl_8033BE90:
/* 8033BE90 00338A70  38 60 00 00 */	li r3, 0
lbl_8033BE94:
/* 8033BE94 00338A74  54 C0 A7 BF */	rlwinm. r0, r6, 0x14, 0x1e, 0x1f
/* 8033BE98 00338A78  7D 08 1A 14 */	add r8, r8, r3
/* 8033BE9C 00338A7C  41 82 00 0C */	beq lbl_8033BEA8
/* 8033BEA0 00338A80  38 60 00 01 */	li r3, 1
/* 8033BEA4 00338A84  48 00 00 08 */	b lbl_8033BEAC
lbl_8033BEA8:
/* 8033BEA8 00338A88  38 60 00 00 */	li r3, 0
lbl_8033BEAC:
/* 8033BEAC 00338A8C  54 C0 97 BF */	rlwinm. r0, r6, 0x12, 0x1e, 0x1f
/* 8033BEB0 00338A90  7D 08 1A 14 */	add r8, r8, r3
/* 8033BEB4 00338A94  41 82 00 0C */	beq lbl_8033BEC0
/* 8033BEB8 00338A98  38 C0 00 01 */	li r6, 1
/* 8033BEBC 00338A9C  48 00 00 08 */	b lbl_8033BEC4
lbl_8033BEC0:
/* 8033BEC0 00338AA0  38 C0 00 00 */	li r6, 0
lbl_8033BEC4:
/* 8033BEC4 00338AA4  38 00 00 10 */	li r0, 0x10
/* 8033BEC8 00338AA8  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033BECC 00338AAC  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033BED0 00338AB0  7D 08 32 14 */	add r8, r8, r6
/* 8033BED4 00338AB4  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8033BED8 00338AB8  54 80 10 3A */	slwi r0, r4, 2
/* 8033BEDC 00338ABC  38 80 10 08 */	li r4, 0x1008
/* 8033BEE0 00338AC0  90 85 80 00 */	stw r4, -0x8000(r5)
/* 8033BEE4 00338AC4  55 04 20 36 */	slwi r4, r8, 4
/* 8033BEE8 00338AC8  7C E0 03 78 */	or r0, r7, r0
/* 8033BEEC 00338ACC  7C 80 03 78 */	or r0, r4, r0
/* 8033BEF0 00338AD0  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8033BEF4 00338AD4  38 00 00 01 */	li r0, 1
/* 8033BEF8 00338AD8  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BEFC 00338ADC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

/**
 * Sets the type of a single attribute (@p attr) in the current vertex
 * descriptor.
 *
 * The current vertex descriptor defines which attributes are present in a
 * vertex and how each attribute is referenced. It is used by the Graphics
 * Processor (GP) to interpret the graphics command stream produced by the GX
 * API. In particular, the current vertex descriptor is used to parse the
 * vertex data that is present in the command stream.
 *
 * @param attr The name of the attribute. Enabled attribute data must be sent
 *             in ascending order.
 * @param type The reference type of the attribute. Accepted values are
 *             #GX_NONE, #GX_DIRECT, #GX_INDEX8, and #GX_INDEX16.
 */
void GXSetVtxDesc(GXAttr attr, s32 type)
{
    switch (attr) {
    case GX_VA_PNMTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 0);
        break;
    case GX_VA_TEX0MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 1);
        break;
    case GX_VA_TEX1MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 2);
        break;
    case GX_VA_TEX2MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 3);
        break;
    case GX_VA_TEX3MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 4);
        break;
    case GX_VA_TEX4MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 5);
        break;
    case GX_VA_TEX5MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 6);
        break;
    case GX_VA_TEX6MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 7);
        break;
    case GX_VA_TEX7MTXIDX:
        INSERT_FIELD(__GXContexts.main->x14, type, 1, 8);
        break;
    case GX_VA_POS:
        INSERT_FIELD(__GXContexts.main->x14, type, 2, 9);
        break;
    case GX_VA_NRM:
        if (type != 0) {
            __GXContexts.main->x41C = 1;
            __GXContexts.main->x41D = 0;
            __GXContexts.main->x418 = type;
        } else {
            __GXContexts.main->x41C = 0;
        }
        break;
    case GX_VA_NBT:
        if (type != 0) {
            __GXContexts.main->x41D = 1;
            __GXContexts.main->x41C = 0;
            __GXContexts.main->x418 = type;
        } else {
            __GXContexts.main->x41D = 0;
        }
        break;
    case GX_VA_CLR0:
        INSERT_FIELD(__GXContexts.main->x14, type, 2, 13);
        break;
    case GX_VA_CLR1:
        INSERT_FIELD(__GXContexts.main->x14, type, 2, 15);
        break;
    case GX_VA_TEX0:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 0);
        break;
    case GX_VA_TEX1:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 2);
        break;
    case GX_VA_TEX2:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 4);
        break;
    case GX_VA_TEX3:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 6);
        break;
    case GX_VA_TEX4:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 8);
        break;
    case GX_VA_TEX5:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 10);
        break;
    case GX_VA_TEX6:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 12);
        break;
    case GX_VA_TEX7:
        INSERT_FIELD(__GXContexts.main->x18, type, 2, 14);
        break;
    }
    if (__GXContexts.main->x41C || __GXContexts.main->x41D) {
        INSERT_FIELD(__GXContexts.main->x14, __GXContexts.main->x418, 2, 11);
    } else {
        INSERT_FIELD(__GXContexts.main->x14, 0, 2, 11);
    }
    __GXContexts.main->x4F0_flags |= 8;
}

#ifdef MUST_MATCH
// https://decomp.me/scratch/NAwYO // 4529 (49.68%)
#pragma push
asm void __GXSetVCD(void)
{ // clang-format off
    nofralloc
/* 8033C260 00338E40  7C 08 02 A6 */	mflr r0
/* 8033C264 00338E44  38 C0 00 08 */	li r6, 8
/* 8033C268 00338E48  90 01 00 04 */	stw r0, 4(r1)
/* 8033C26C 00338E4C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033C270 00338E50  38 60 00 50 */	li r3, 0x50
/* 8033C274 00338E54  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8033C278 00338E58  38 00 00 60 */	li r0, 0x60
/* 8033C27C 00338E5C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8033C280 00338E60  98 C5 80 00 */	stb r6, 0xCC008000@l(r5)
/* 8033C284 00338E64  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033C288 00338E68  98 65 80 00 */	stb r3, -0x8000(r5)
/* 8033C28C 00338E6C  80 64 00 14 */	lwz r3, 0x14(r4)
/* 8033C290 00338E70  90 65 80 00 */	stw r3, -0x8000(r5)
/* 8033C294 00338E74  98 C5 80 00 */	stb r6, -0x8000(r5)
/* 8033C298 00338E78  98 05 80 00 */	stb r0, -0x8000(r5)
/* 8033C29C 00338E7C  80 04 00 18 */	lwz r0, 0x18(r4)
/* 8033C2A0 00338E80  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8033C2A4 00338E84  4B FF FB 05 */	bl __GXXfVtxSpecs
/* 8033C2A8 00338E88  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033C2AC 00338E8C  A0 03 00 04 */	lhz r0, 4(r3)
/* 8033C2B0 00338E90  28 00 00 00 */	cmplwi r0, 0
/* 8033C2B4 00338E94  41 82 01 00 */	beq lbl_8033C3B4
/* 8033C2B8 00338E98  88 A3 04 1D */	lbz r5, 0x41d(r3)
/* 8033C2BC 00338E9C  39 2D A5 18 */	addi r9, r13, GXAttr_804D5BB8
/* 8033C2C0 00338EA0  83 E3 00 14 */	lwz r31, 0x14(r3)
/* 8033C2C4 00338EA4  38 ED A5 10 */	addi r7, r13, GXAttr_804D5BB0
/* 8033C2C8 00338EA8  54 A5 08 3C */	slwi r5, r5, 1
/* 8033C2CC 00338EAC  39 05 00 01 */	addi r8, r5, 1
/* 8033C2D0 00338EB0  80 83 00 18 */	lwz r4, 0x18(r3)
/* 8033C2D4 00338EB4  57 E6 AF BE */	rlwinm r6, r31, 0x15, 0x1e, 0x1f
/* 8033C2D8 00338EB8  7D 49 30 AE */	lbzx r10, r9, r6
/* 8033C2DC 00338EBC  57 E0 07 FE */	clrlwi r0, r31, 0x1f
/* 8033C2E0 00338EC0  57 EB FF FE */	rlwinm r11, r31, 0x1f, 0x1f, 0x1f
/* 8033C2E4 00338EC4  57 E6 9F BE */	rlwinm r6, r31, 0x13, 0x1e, 0x1f
/* 8033C2E8 00338EC8  57 E5 BF BE */	rlwinm r5, r31, 0x17, 0x1e, 0x1f
/* 8033C2EC 00338ECC  7C C7 30 AE */	lbzx r6, r7, r6
/* 8033C2F0 00338ED0  7C 00 5A 14 */	add r0, r0, r11
/* 8033C2F4 00338ED4  7D 69 28 AE */	lbzx r11, r9, r5
/* 8033C2F8 00338ED8  57 EC F7 FE */	rlwinm r12, r31, 0x1e, 0x1f, 0x1f
/* 8033C2FC 00338EDC  57 E5 8F BE */	rlwinm r5, r31, 0x11, 0x1e, 0x1f
/* 8033C300 00338EE0  7D 27 28 AE */	lbzx r9, r7, r5
/* 8033C304 00338EE4  7C 00 62 14 */	add r0, r0, r12
/* 8033C308 00338EE8  57 E5 EF FE */	rlwinm r5, r31, 0x1d, 0x1f, 0x1f
/* 8033C30C 00338EEC  7C 00 2A 14 */	add r0, r0, r5
/* 8033C310 00338EF0  57 E5 E7 FE */	rlwinm r5, r31, 0x1c, 0x1f, 0x1f
/* 8033C314 00338EF4  7C 00 2A 14 */	add r0, r0, r5
/* 8033C318 00338EF8  57 E5 DF FE */	rlwinm r5, r31, 0x1b, 0x1f, 0x1f
/* 8033C31C 00338EFC  7C 00 2A 14 */	add r0, r0, r5
/* 8033C320 00338F00  57 E7 D7 FE */	rlwinm r7, r31, 0x1a, 0x1f, 0x1f
/* 8033C324 00338F04  7C AA 41 D6 */	mullw r5, r10, r8
/* 8033C328 00338F08  7C 00 3A 14 */	add r0, r0, r7
/* 8033C32C 00338F0C  57 E7 CF FE */	rlwinm r7, r31, 0x19, 0x1f, 0x1f
/* 8033C330 00338F10  7C 00 3A 14 */	add r0, r0, r7
/* 8033C334 00338F14  57 E7 C7 FE */	rlwinm r7, r31, 0x18, 0x1f, 0x1f
/* 8033C338 00338F18  7C 00 3A 14 */	add r0, r0, r7
/* 8033C33C 00338F1C  7C 00 5A 14 */	add r0, r0, r11
/* 8033C340 00338F20  7C 00 2A 14 */	add r0, r0, r5
/* 8033C344 00338F24  7C 00 32 14 */	add r0, r0, r6
/* 8033C348 00338F28  54 86 07 BE */	clrlwi r6, r4, 0x1e
/* 8033C34C 00338F2C  39 0D A5 14 */	addi r8, r13, GXAttr_804D5BB4
/* 8033C350 00338F30  54 85 F7 BE */	rlwinm r5, r4, 0x1e, 0x1e, 0x1f
/* 8033C354 00338F34  7C E8 30 AE */	lbzx r7, r8, r6
/* 8033C358 00338F38  7C 00 4A 14 */	add r0, r0, r9
/* 8033C35C 00338F3C  7C C8 28 AE */	lbzx r6, r8, r5
/* 8033C360 00338F40  7C 00 3A 14 */	add r0, r0, r7
/* 8033C364 00338F44  54 85 E7 BE */	rlwinm r5, r4, 0x1c, 0x1e, 0x1f
/* 8033C368 00338F48  7C E8 28 AE */	lbzx r7, r8, r5
/* 8033C36C 00338F4C  7C 00 32 14 */	add r0, r0, r6
/* 8033C370 00338F50  54 85 D7 BE */	rlwinm r5, r4, 0x1a, 0x1e, 0x1f
/* 8033C374 00338F54  7C C8 28 AE */	lbzx r6, r8, r5
/* 8033C378 00338F58  7C 00 3A 14 */	add r0, r0, r7
/* 8033C37C 00338F5C  54 85 C7 BE */	rlwinm r5, r4, 0x18, 0x1e, 0x1f
/* 8033C380 00338F60  7C E8 28 AE */	lbzx r7, r8, r5
/* 8033C384 00338F64  7C 00 32 14 */	add r0, r0, r6
/* 8033C388 00338F68  54 85 B7 BE */	rlwinm r5, r4, 0x16, 0x1e, 0x1f
/* 8033C38C 00338F6C  7C C8 28 AE */	lbzx r6, r8, r5
/* 8033C390 00338F70  54 85 A7 BE */	rlwinm r5, r4, 0x14, 0x1e, 0x1f
/* 8033C394 00338F74  7C 00 3A 14 */	add r0, r0, r7
/* 8033C398 00338F78  7C A8 28 AE */	lbzx r5, r8, r5
/* 8033C39C 00338F7C  54 84 97 BE */	rlwinm r4, r4, 0x12, 0x1e, 0x1f
/* 8033C3A0 00338F80  7C 00 32 14 */	add r0, r0, r6
/* 8033C3A4 00338F84  7C 88 20 AE */	lbzx r4, r8, r4
/* 8033C3A8 00338F88  7C 00 2A 14 */	add r0, r0, r5
/* 8033C3AC 00338F8C  7C 00 22 14 */	add r0, r0, r4
/* 8033C3B0 00338F90  B0 03 00 06 */	sth r0, 6(r3)
lbl_8033C3B4:
/* 8033C3B4 00338F94  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8033C3B8 00338F98  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8033C3BC 00338F9C  38 21 00 20 */	addi r1, r1, 0x20
/* 8033C3C0 00338FA0  7C 08 03 A6 */	mtlr r0
/* 8033C3C4 00338FA4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

void GXClearVtxDesc(void)
{
    GXContext* temp_r3;
    GXContext* temp_r3_2;
    __GXContexts.main->x14 = 0;
    temp_r3 = __GXContexts.main;
    temp_r3->x14 = (temp_r3->x14 & 0xFFFFF9FF) | 0x200;
    __GXContexts.main->x18 = 0;
    __GXContexts.main->x41C = GX_FALSE;
    __GXContexts.main->x41D = GX_FALSE;
    temp_r3_2 = __GXContexts.main;
    temp_r3_2->x4F0_flags |= 8;
}

/**
 * Sets the attribute format (@p attr) for a single attribute in the Vertex
 * Attribute Format Table (VAT).
 *
 * Each attribute format describes the data type, number of elements
 * (@p count), and fixed point format (@p frac), if required. The are eight
 * vertex formats available in the VAT. The vertex format describes the format
 * of all attributes in a vertex. The application can pre-program all eight
 * vertex formats, and then select one of them during the actual drawing of
 * geometry (see #GXBegin). Note that all vertices used to draw a particular
 * graphics primitive will have the same format. The vertex format set using
 * #GXSetVtxAttrFmt, along with the current vertex descriptor set using
 * #GXSetVtxDesc, completely define the vertex data format.
 *
 * The vertex format allows data to be sent to the graphics processor in its
 * most quantized format. The graphics hardware will inverse-quantize the
 * data (into floating point format) before it is used. The vertex attribute
 * format is used to communicate the data quantization format to the hardware.
 *
 * Note that #GX_VA_NRM and #GX_VA_NBT attributes share the same type. Also,
 * the @p frac for these attributes is fixed according to the type. The
 * component count (@p count) for #GX_VA_NRM must be set to #GX_NRM_XYZ. The
 * component count for #GX_VA_NBT must be set to #GX_NRM_NBT (see exception for
 * HW2 below).
 *
 * Note also that a HW1 bug means that for a component type of #u8 or #s8, the
 * fixed-point fraction is ignored and assumed to be zero.
 *
 * @param vtxfmt The vertex format number.
 * @param attr   The attribute name.
 * @param count  May be one of several different enumerations, depending
 *               on the attribute name; one of #GXCompCnt, #GXPosCompCnt,
 *               #GXNrmCompCnt, #GXClrCompCnt, or #GXTexCompCnt. Ultimately
 *               aids in determining the number of dimensions for this
 *               attribute. For example, 4 for an RGBA color, or 3 for
 *               vertex position data.
 * @param type   May be one of several different enumerations, depending
 *               on the attribute name. Specifies the data format for
 *               a single value in a dimension, such as #u8, #s16, or #f32.
 * @param frac   Specifies the number of fractional bits in a fixed point
 *               number, where <tt>0 <= frac <= 31</tt>. @p frac is ignored for
 *               floating-point types and color types.
 * @see          GXBegin
 * @see          GXSetVtxAttrFmt
 * @see          GXSetVtxDesc
 */
void GXSetVtxAttrFmt(size_t vtxfmt, GXAttr attr, enum_t count, GXAttrType type,
                     u8 frac)
{
    s32* temp_r4 = &__GXContexts.main->x1C_data[vtxfmt];
    s32* temp_r8 = &__GXContexts.main->x3C_data[vtxfmt];
    s32* temp_r9 = &__GXContexts.main->x5C_data[vtxfmt];

    switch (attr) {
    case GX_VA_POS:
        INSERT_FIELD(*temp_r4, count, 1, 0);
        INSERT_FIELD(*temp_r4, type, 3, 1);
        INSERT_FIELD(*temp_r4, frac, 5, 4);
        break;
    case GX_VA_NRM:
    case GX_VA_NBT:
        INSERT_FIELD(*temp_r4, type, 3, 10);
        if (count == 2) {
            INSERT_FIELD(*temp_r4, 1, 1, 9);
            INSERT_FIELD(*temp_r4, 1, 1, 31);
        } else {
            INSERT_FIELD(*temp_r4, count, 1, 9);
            INSERT_FIELD(*temp_r4, 0, 1, 31);
        }
        break;
    case GX_VA_CLR0:
        INSERT_FIELD(*temp_r4, count, 1, 13);
        INSERT_FIELD(*temp_r4, type, 3, 14);
        break;
    case GX_VA_CLR1:
        INSERT_FIELD(*temp_r4, count, 1, 17);
        INSERT_FIELD(*temp_r4, type, 3, 18);
        break;
    case GX_VA_TEX0:
        INSERT_FIELD(*temp_r4, count, 1, 21);
        INSERT_FIELD(*temp_r4, type, 3, 22);
        INSERT_FIELD(*temp_r4, frac, 5, 25);
        break;
    case GX_VA_TEX1:
        INSERT_FIELD(*temp_r8, count, 1, 0);
        INSERT_FIELD(*temp_r8, type, 3, 1);
        INSERT_FIELD(*temp_r8, frac, 5, 4);
        break;
    case GX_VA_TEX2:
        INSERT_FIELD(*temp_r8, count, 1, 9);
        INSERT_FIELD(*temp_r8, type, 3, 10);
        INSERT_FIELD(*temp_r8, frac, 5, 13);
        break;
    case GX_VA_TEX3:
        INSERT_FIELD(*temp_r8, count, 1, 18);
        INSERT_FIELD(*temp_r8, type, 3, 19);
        INSERT_FIELD(*temp_r8, frac, 5, 22);
        break;
    case GX_VA_TEX4:
        INSERT_FIELD(*temp_r8, count, 1, 27);
        INSERT_FIELD(*temp_r8, type, 3, 28);
        INSERT_FIELD(*temp_r9, frac, 5, 0);
        break;
    case GX_VA_TEX5:
        INSERT_FIELD(*temp_r9, count, 1, 5);
        INSERT_FIELD(*temp_r9, type, 3, 6);
        INSERT_FIELD(*temp_r9, frac, 5, 9);
        break;
    case GX_VA_TEX6:
        INSERT_FIELD(*temp_r9, count, 1, 14);
        INSERT_FIELD(*temp_r9, type, 3, 15);
        INSERT_FIELD(*temp_r9, frac, 5, 18);
        break;
    case GX_VA_TEX7:
        INSERT_FIELD(*temp_r9, count, 1, 23);
        INSERT_FIELD(*temp_r9, type, 3, 24);
        INSERT_FIELD(*temp_r9, frac, 5, 27);
        break;
    }
    __GXContexts.main->x4F0_flags |= 0x10;
    __GXContexts.main->x4EE |= (u8) (1 << (u8) vtxfmt);
}

#ifdef MUST_MATCH
static jtbl_t jtbl_804010F4 = { &GXAttr_8033CA6C, &GXAttr_8033CA8C,
                                &GXAttr_8033CAAC, &GXAttr_8033CACC,
                                &GXAttr_8033CAEC, &GXAttr_8033CB04,
                                &GXAttr_8033CB24 };

static jtbl_t jtbl_80401110 = {
    &GXAttr_8033C8E0, &GXAttr_8033C8EC, &GXAttr_8033C8F8, &GXAttr_8033C904,
    &GXAttr_8033C920, &GXAttr_8033C928, &GXAttr_8033C930, &GXAttr_8033C938,
    &GXAttr_8033C940, &GXAttr_8033C948, &GXAttr_8033C950, &GXAttr_8033C958,
    &GXAttr_8033C95C, &GXAttr_8033C95C, &GXAttr_8033C95C, &GXAttr_8033C95C,
    &GXAttr_8033C95C, &GXAttr_8033C95C, &GXAttr_8033C95C, &GXAttr_8033C910,
    &GXAttr_8033C918
};
#endif

void __GXSetVAT(void)
{
    u8 i;
    for (i = 0; i < 8; i++) {
        if (__GXContexts.main->x4EE & (1 << (u32) i)) {
            WGPIPE.u8 = GX_LOAD_CP_REG;
            WGPIPE.u8 = i | 0x70;
            WGPIPE.u32 = __GXContexts.main->x1C_data[i];
            WGPIPE.u8 = GX_LOAD_CP_REG;
            WGPIPE.u8 = i | 0x80;
            WGPIPE.u32 = __GXContexts.main->x3C_data[i];
            WGPIPE.u8 = GX_LOAD_CP_REG;
            WGPIPE.u8 = i | 0x90;
            WGPIPE.u32 = __GXContexts.main->x5C_data[i];
        }
    }
    __GXContexts.main->x4EE = 0;
}

/**
 * Sets the array base pointer and stride for a single attribute.
 *
 * The array base and stride are used to compute the address of indexed
 * attribute data using the equation:
 *
 * @code{c}
 *      attr_addr = base_ptr + attr_idx * stride
 * @endcode
 *
 * When drawing a graphics primitive that has been enabled to use indexed
 * attributes (see #GXSetVtxDesc), @p attr_idx is supplied in the vertex data.
 * The format and size of the data in the array must also be described
 * using #GXSetVtxAttrFmt.
 *
 * You can also index other data, such as matrices (see #GXLoadPosMtxIndx,
 * #GXLoadNrmMtxIndx3x3, and #GXLoadTexMtxIndx), and light objects (see
 * #GXLoadLightObjIndx). In the case of matrices and light objects, the
 * size and format of the data to be loaded is implied by the function call.
 *
 * There is a base pointer, @p base_ptr, for each type of attribute as well as
 * for light data and matrices. Each attribute can be stored in its own
 * array for maximum data compression (i.e., removal of redundant attribute
 * data). The stride is in byte units and is the distance between
 * attributes in the array.
 *
 * Indexed data is loaded into a vertex cache in the graphics processor.
 * The vertex cache fetches 32 bytes of data for each cache miss; therefore,
 * there is a small performance benefit to aligning attribute arrays to
 * 32 bytes, and possibly for arranging vertex data so that it doesn't span
 * 32-byte boundaries. Conveniently enough, #OSAlloc returns 32-byte aligned
 * pointers. For static data arrays, you can use the #ATTRIBUTE_ALIGN macro
 * (specific to the MetroWerks compiler) to align the @p base_ptr to 32 bytes,
 * as in:
 *
 * @code{c}
 *      u32 mydata[] ATTRIBUTE_ALIGN(32) = {
 *          // initialize data
 *      };
 * @endcode
 *
 * @param attr      The attribute array name.
 * @param base_ptr  Pointer to first element in attribute data array.
 * @param stride    Stride in bytes between attribute data elements.
 */
void GXSetArray(GXAttr attr, s32 base_ptr, u8 stride)
{
    s32 idx;
    s32 temp_r6;
    s32 var_r3;

    var_r3 = attr;
    if (var_r3 == GX_VA_NBT) {
        var_r3 = GX_VA_NRM;
    }
    temp_r6 = var_r3 - 9;

    WGPIPE.u8 = GX_LOAD_CP_REG;
    WGPIPE.u8 = temp_r6 | 0xA0;
    WGPIPE.u32 = base_ptr & 0x3FFFFFFF;
    idx = temp_r6 - 0xC;
    if (idx >= 0 && idx < 4) {
        __GXContexts.main->x88_data[idx] = base_ptr & 0x3FFFFFFF;
    }
    WGPIPE.u8 = GX_LOAD_CP_REG;
    WGPIPE.u8 = (s8) (temp_r6 | 0xB0);
    WGPIPE.u32 = stride;
    idx = temp_r6 - 0xC;
    if (idx >= 0 && idx < 4) {
        __GXContexts.main->x98_data[idx] = stride;
    }
}

/**
 * Called by #GXInit and invalidates the vertex cache tags.
 *
 * This function should be used whenever you relocate or modify data that
 * is read by, or may be cached by, the vertex cache. The invalidate is
 * very fast, taking only two Graphics Processor (GP) clock cycles to complete.
 *
 * The vertex cache is used to cache indexed attribute data. Any attribute
 * that is set to #GX_INDEX8 or #GX_INDEX16 in the current vertex descriptor
 * (see #GXSetVtxDesc) is indexed. Direct data bypasses the vertex cache.
 * Direct data is any attribute that is set to #GX_DIRECT in the current
 * vertex descriptor.
 *
 * @see GXInit
 * @see GXSetVtxDesc
 */
void GXInvalidateVtxCache(void)
{
    WGPIPE.u8 = GX_CMD_INVL_VC;
}

#ifdef MUST_MATCH
// https://decomp.me/scratch/9TphI // 640 (96.44%)
#pragma push
asm void GXSetTexCoordGen2(u32, s32, u32, s32, s32, s32)
{ // clang-format off
    nofralloc
/* 8033C8A8 00339488  7C 08 02 A6 */	mflr r0
/* 8033C8AC 0033948C  28 05 00 14 */	cmplwi r5, 0x14
/* 8033C8B0 00339490  90 01 00 04 */	stw r0, 4(r1)
/* 8033C8B4 00339494  39 60 00 00 */	li r11, 0
/* 8033C8B8 00339498  39 80 00 00 */	li r12, 0
/* 8033C8BC 0033949C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8033C8C0 003394A0  39 40 00 05 */	li r10, 5
/* 8033C8C4 003394A4  41 81 00 98 */	bgt GXAttr_8033C95C
/* 8033C8C8 003394A8  3D 20 80 40 */	lis r9, jtbl_80401110@ha
/* 8033C8CC 003394AC  39 29 11 10 */	addi r9, r9, jtbl_80401110@l
/* 8033C8D0 003394B0  54 A0 10 3A */	slwi r0, r5, 2
/* 8033C8D4 003394B4  7C 09 00 2E */	lwzx r0, r9, r0
/* 8033C8D8 003394B8  7C 09 03 A6 */	mtctr r0
/* 8033C8DC 003394BC  4E 80 04 20 */	bctr
entry GXAttr_8033C8E0
/* 8033C8E0 003394C0  39 40 00 00 */	li r10, 0
/* 8033C8E4 003394C4  39 80 00 01 */	li r12, 1
/* 8033C8E8 003394C8  48 00 00 74 */	b GXAttr_8033C95C
entry GXAttr_8033C8EC
/* 8033C8EC 003394CC  39 40 00 01 */	li r10, 1
/* 8033C8F0 003394D0  39 80 00 01 */	li r12, 1
/* 8033C8F4 003394D4  48 00 00 68 */	b GXAttr_8033C95C
entry GXAttr_8033C8F8
/* 8033C8F8 003394D8  39 40 00 03 */	li r10, 3
/* 8033C8FC 003394DC  39 80 00 01 */	li r12, 1
/* 8033C900 003394E0  48 00 00 5C */	b GXAttr_8033C95C
entry GXAttr_8033C904
/* 8033C904 003394E4  39 40 00 04 */	li r10, 4
/* 8033C908 003394E8  39 80 00 01 */	li r12, 1
/* 8033C90C 003394EC  48 00 00 50 */	b GXAttr_8033C95C
entry GXAttr_8033C910
/* 8033C910 003394F0  39 40 00 02 */	li r10, 2
/* 8033C914 003394F4  48 00 00 48 */	b GXAttr_8033C95C
entry GXAttr_8033C918
/* 8033C918 003394F8  39 40 00 02 */	li r10, 2
/* 8033C91C 003394FC  48 00 00 40 */	b GXAttr_8033C95C
entry GXAttr_8033C920
/* 8033C920 00339500  39 40 00 05 */	li r10, 5
/* 8033C924 00339504  48 00 00 38 */	b GXAttr_8033C95C
entry GXAttr_8033C928
/* 8033C928 00339508  39 40 00 06 */	li r10, 6
/* 8033C92C 0033950C  48 00 00 30 */	b GXAttr_8033C95C
entry GXAttr_8033C930
/* 8033C930 00339510  39 40 00 07 */	li r10, 7
/* 8033C934 00339514  48 00 00 28 */	b GXAttr_8033C95C
entry GXAttr_8033C938
/* 8033C938 00339518  39 40 00 08 */	li r10, 8
/* 8033C93C 0033951C  48 00 00 20 */	b GXAttr_8033C95C
entry GXAttr_8033C940
/* 8033C940 00339520  39 40 00 09 */	li r10, 9
/* 8033C944 00339524  48 00 00 18 */	b GXAttr_8033C95C
entry GXAttr_8033C948
/* 8033C948 00339528  39 40 00 0A */	li r10, 0xa
/* 8033C94C 0033952C  48 00 00 10 */	b GXAttr_8033C95C
entry GXAttr_8033C950
/* 8033C950 00339530  39 40 00 0B */	li r10, 0xb
/* 8033C954 00339534  48 00 00 08 */	b GXAttr_8033C95C
entry GXAttr_8033C958
/* 8033C958 00339538  39 40 00 0C */	li r10, 0xc
entry GXAttr_8033C95C
/* 8033C95C 0033953C  2C 04 00 01 */	cmpwi r4, 1
/* 8033C960 00339540  41 82 00 24 */	beq lbl_8033C984
/* 8033C964 00339544  40 80 00 10 */	bge lbl_8033C974
/* 8033C968 00339548  2C 04 00 00 */	cmpwi r4, 0
/* 8033C96C 0033954C  40 80 00 2C */	bge lbl_8033C998
/* 8033C970 00339550  48 00 00 A4 */	b lbl_8033CA14
lbl_8033C974:
/* 8033C974 00339554  2C 04 00 0A */	cmpwi r4, 0xa
/* 8033C978 00339558  41 82 00 74 */	beq lbl_8033C9EC
/* 8033C97C 0033955C  40 80 00 98 */	bge lbl_8033CA14
/* 8033C980 00339560  48 00 00 30 */	b lbl_8033C9B0
lbl_8033C984:
/* 8033C984 00339564  55 80 10 3A */	slwi r0, r12, 2
/* 8033C988 00339568  54 04 07 26 */	rlwinm r4, r0, 0, 0x1c, 0x13
/* 8033C98C 0033956C  55 40 38 30 */	slwi r0, r10, 7
/* 8033C990 00339570  7C 8B 03 78 */	or r11, r4, r0
/* 8033C994 00339574  48 00 00 80 */	b lbl_8033CA14
lbl_8033C998:
/* 8033C998 00339578  55 80 10 3A */	slwi r0, r12, 2
/* 8033C99C 0033957C  60 00 00 02 */	ori r0, r0, 2
/* 8033C9A0 00339580  54 04 07 26 */	rlwinm r4, r0, 0, 0x1c, 0x13
/* 8033C9A4 00339584  55 40 38 30 */	slwi r0, r10, 7
/* 8033C9A8 00339588  7C 8B 03 78 */	or r11, r4, r0
/* 8033C9AC 0033958C  48 00 00 68 */	b lbl_8033CA14
lbl_8033C9B0:
/* 8033C9B0 00339590  55 80 10 3A */	slwi r0, r12, 2
/* 8033C9B4 00339594  54 00 07 30 */	rlwinm r0, r0, 0, 0x1c, 0x18
/* 8033C9B8 00339598  60 00 00 10 */	ori r0, r0, 0x10
/* 8033C9BC 0033959C  54 09 06 66 */	rlwinm r9, r0, 0, 0x19, 0x13
/* 8033C9C0 003395A0  55 40 38 30 */	slwi r0, r10, 7
/* 8033C9C4 003395A4  7D 29 03 78 */	or r9, r9, r0
/* 8033C9C8 003395A8  38 A5 FF F4 */	addi r5, r5, -12
/* 8033C9CC 003395AC  38 04 FF FE */	addi r0, r4, -2
/* 8033C9D0 003395B0  55 29 05 20 */	rlwinm r9, r9, 0, 0x14, 0x10
/* 8033C9D4 003395B4  54 A4 60 26 */	slwi r4, r5, 0xc
/* 8033C9D8 003395B8  7D 24 23 78 */	or r4, r9, r4
/* 8033C9DC 003395BC  54 84 04 5A */	rlwinm r4, r4, 0, 0x11, 0xd
/* 8033C9E0 003395C0  54 00 78 20 */	slwi r0, r0, 0xf
/* 8033C9E4 003395C4  7C 8B 03 78 */	or r11, r4, r0
/* 8033C9E8 003395C8  48 00 00 2C */	b lbl_8033CA14
lbl_8033C9EC:
/* 8033C9EC 003395CC  2C 05 00 13 */	cmpwi r5, 0x13
/* 8033C9F0 003395D0  55 80 10 3A */	slwi r0, r12, 2
/* 8033C9F4 003395D4  40 82 00 10 */	bne lbl_8033CA04
/* 8033C9F8 003395D8  54 00 07 30 */	rlwinm r0, r0, 0, 0x1c, 0x18
/* 8033C9FC 003395DC  60 00 00 20 */	ori r0, r0, 0x20
/* 8033CA00 003395E0  48 00 00 0C */	b lbl_8033CA0C
lbl_8033CA04:
/* 8033CA04 003395E4  54 00 07 30 */	rlwinm r0, r0, 0, 0x1c, 0x18
/* 8033CA08 003395E8  60 00 00 30 */	ori r0, r0, 0x30
lbl_8033CA0C:
/* 8033CA0C 003395EC  54 00 06 66 */	rlwinm r0, r0, 0, 0x19, 0x13
/* 8033CA10 003395F0  60 0B 01 00 */	ori r11, r0, 0x100
lbl_8033CA14:
/* 8033CA14 003395F4  39 40 00 10 */	li r10, 0x10
/* 8033CA18 003395F8  3D 20 CC 01 */	lis r9, 0xCC008000@ha
/* 8033CA1C 003395FC  99 49 80 00 */	stb r10, 0xCC008000@l(r9)
/* 8033CA20 00339600  38 03 10 40 */	addi r0, r3, 0x1040
/* 8033CA24 00339604  38 88 FF C0 */	addi r4, r8, -64
/* 8033CA28 00339608  90 09 80 00 */	stw r0, -0x8000(r9)
/* 8033CA2C 0033960C  54 85 06 2C */	rlwinm r5, r4, 0, 0x18, 0x16
/* 8033CA30 00339610  54 E4 44 2E */	rlwinm r4, r7, 8, 0x10, 0x17
/* 8033CA34 00339614  91 69 80 00 */	stw r11, -0x8000(r9)
/* 8033CA38 00339618  38 03 10 50 */	addi r0, r3, 0x1050
/* 8033CA3C 0033961C  28 03 00 06 */	cmplwi r3, 6
/* 8033CA40 00339620  99 49 80 00 */	stb r10, -0x8000(r9)
/* 8033CA44 00339624  7C A4 23 78 */	or r4, r5, r4
/* 8033CA48 00339628  90 09 80 00 */	stw r0, -0x8000(r9)
/* 8033CA4C 0033962C  90 89 80 00 */	stw r4, -0x8000(r9)
/* 8033CA50 00339630  41 81 00 F4 */	bgt lbl_8033CB44
/* 8033CA54 00339634  3C 80 80 40 */	lis r4, jtbl_804010F4@ha
/* 8033CA58 00339638  38 84 10 F4 */	addi r4, r4, jtbl_804010F4@l
/* 8033CA5C 0033963C  54 60 10 3A */	slwi r0, r3, 2
/* 8033CA60 00339640  7C 04 00 2E */	lwzx r0, r4, r0
/* 8033CA64 00339644  7C 09 03 A6 */	mtctr r0
/* 8033CA68 00339648  4E 80 04 20 */	bctr
entry GXAttr_8033CA6C
/* 8033CA6C 0033964C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033CA70 00339650  54 C0 30 32 */	slwi r0, r6, 6
/* 8033CA74 00339654  38 A4 00 80 */	addi r5, r4, 0x80
/* 8033CA78 00339658  80 84 00 80 */	lwz r4, 0x80(r4)
/* 8033CA7C 0033965C  54 84 06 A6 */	rlwinm r4, r4, 0, 0x1a, 0x13
/* 8033CA80 00339660  7C 80 03 78 */	or r0, r4, r0
/* 8033CA84 00339664  90 05 00 00 */	stw r0, 0(r5)
/* 8033CA88 00339668  48 00 00 D8 */	b lbl_8033CB60
entry GXAttr_8033CA8C
/* 8033CA8C 0033966C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033CA90 00339670  54 C0 60 26 */	slwi r0, r6, 0xc
/* 8033CA94 00339674  38 A4 00 80 */	addi r5, r4, 0x80
/* 8033CA98 00339678  80 84 00 80 */	lwz r4, 0x80(r4)
/* 8033CA9C 0033967C  54 84 05 1A */	rlwinm r4, r4, 0, 0x14, 0xd
/* 8033CAA0 00339680  7C 80 03 78 */	or r0, r4, r0
/* 8033CAA4 00339684  90 05 00 00 */	stw r0, 0(r5)
/* 8033CAA8 00339688  48 00 00 B8 */	b lbl_8033CB60
entry GXAttr_8033CAAC
/* 8033CAAC 0033968C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033CAB0 00339690  54 C0 90 1A */	slwi r0, r6, 0x12
/* 8033CAB4 00339694  38 A4 00 80 */	addi r5, r4, 0x80
/* 8033CAB8 00339698  80 84 00 80 */	lwz r4, 0x80(r4)
/* 8033CABC 0033969C  54 84 03 8E */	rlwinm r4, r4, 0, 0xe, 7
/* 8033CAC0 003396A0  7C 80 03 78 */	or r0, r4, r0
/* 8033CAC4 003396A4  90 05 00 00 */	stw r0, 0(r5)
/* 8033CAC8 003396A8  48 00 00 98 */	b lbl_8033CB60
entry GXAttr_8033CACC
/* 8033CACC 003396AC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033CAD0 003396B0  54 C0 C0 0E */	slwi r0, r6, 0x18
/* 8033CAD4 003396B4  38 A4 00 80 */	addi r5, r4, 0x80
/* 8033CAD8 003396B8  80 84 00 80 */	lwz r4, 0x80(r4)
/* 8033CADC 003396BC  54 84 02 02 */	rlwinm r4, r4, 0, 8, 1
/* 8033CAE0 003396C0  7C 80 03 78 */	or r0, r4, r0
/* 8033CAE4 003396C4  90 05 00 00 */	stw r0, 0(r5)
/* 8033CAE8 003396C8  48 00 00 78 */	b lbl_8033CB60
entry GXAttr_8033CAEC
/* 8033CAEC 003396CC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033CAF0 003396D0  84 04 00 84 */	lwzu r0, 0x84(r4)
/* 8033CAF4 003396D4  54 00 00 32 */	rlwinm r0, r0, 0, 0, 0x19
/* 8033CAF8 003396D8  7C 00 33 78 */	or r0, r0, r6
/* 8033CAFC 003396DC  90 04 00 00 */	stw r0, 0(r4)
/* 8033CB00 003396E0  48 00 00 60 */	b lbl_8033CB60
entry GXAttr_8033CB04
/* 8033CB04 003396E4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033CB08 003396E8  54 C0 30 32 */	slwi r0, r6, 6
/* 8033CB0C 003396EC  38 A4 00 84 */	addi r5, r4, 0x84
/* 8033CB10 003396F0  80 84 00 84 */	lwz r4, 0x84(r4)
/* 8033CB14 003396F4  54 84 06 A6 */	rlwinm r4, r4, 0, 0x1a, 0x13
/* 8033CB18 003396F8  7C 80 03 78 */	or r0, r4, r0
/* 8033CB1C 003396FC  90 05 00 00 */	stw r0, 0(r5)
/* 8033CB20 00339700  48 00 00 40 */	b lbl_8033CB60
entry GXAttr_8033CB24
/* 8033CB24 00339704  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033CB28 00339708  54 C0 60 26 */	slwi r0, r6, 0xc
/* 8033CB2C 0033970C  38 A4 00 84 */	addi r5, r4, 0x84
/* 8033CB30 00339710  80 84 00 84 */	lwz r4, 0x84(r4)
/* 8033CB34 00339714  54 84 05 1A */	rlwinm r4, r4, 0, 0x14, 0xd
/* 8033CB38 00339718  7C 80 03 78 */	or r0, r4, r0
/* 8033CB3C 0033971C  90 05 00 00 */	stw r0, 0(r5)
/* 8033CB40 00339720  48 00 00 20 */	b lbl_8033CB60
lbl_8033CB44:
/* 8033CB44 00339724  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033CB48 00339728  54 C0 90 1A */	slwi r0, r6, 0x12
/* 8033CB4C 0033972C  38 A4 00 84 */	addi r5, r4, 0x84
/* 8033CB50 00339730  80 84 00 84 */	lwz r4, 0x84(r4)
/* 8033CB54 00339734  54 84 03 8E */	rlwinm r4, r4, 0, 0xe, 7
/* 8033CB58 00339738  7C 80 03 78 */	or r0, r4, r0
/* 8033CB5C 0033973C  90 05 00 00 */	stw r0, 0(r5)
lbl_8033CB60:
/* 8033CB60 00339740  38 63 00 01 */	addi r3, r3, 1
/* 8033CB64 00339744  48 00 4D 15 */	bl __GXSetMatrixIndex
/* 8033CB68 00339748  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8033CB6C 0033974C  38 21 00 08 */	addi r1, r1, 8
/* 8033CB70 00339750  7C 08 03 A6 */	mtlr r0
/* 8033CB74 00339754  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

/**
 * Sets the number of texture coordinates that are generated and available for
 * use in the Texture Environment (TEV) stages.
 *
 * Texture coordinates are generated from input data as described by
 * #GXSetTexCoordGen. The generated texture coordinates are linked to specific
 * textures and specific Texture Environment (TEV) stages using #GXSetTevOrder.
 *
 * A consecutive number of texture coordinates may be generated, starting
 * at #GX_TEXCOORD0. A maximum of 8 texture coordinates may be generated.
 * If @p num is set to 0, no texture coordinates will be generated. In
 * this case, at least one color channel must be output, see #GXSetNumChans.
 *
 * @param num Number of texture coordinates to generate. Minimum value is 0,
 *            maximum value is 8.
 * @see       GXSetNumChans
 */
void GXSetNumTexGens(u8 num)
{
    INSERT_FIELD(__GXContexts.main->x204, num, 4, 0);
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x103F;
    WGPIPE.u32 = num;
    __GXContexts.main->x4F0_flags |= 4;
}
