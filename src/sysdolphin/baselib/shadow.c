#include <sysdolphin/baselib/shadow.h>

#include <string.h>

extern HSD_ObjAllocData shadow_alloc_data;

extern const f32 lbl_804DE768;
extern const f32 lbl_804DE76C;
extern const f32 lbl_804DE770;
extern const f32 lbl_804DE774;


HSD_ObjAllocData* HSD_ShadowGetAllocData(void)
{
  return &shadow_alloc_data;
}

void HSD_ShadowInitAllocData(void)
{
  HSD_ObjAllocInit(&shadow_alloc_data, sizeof(HSD_Shadow), 4);
}

#ifdef NON_MATCHING
HSD_Shadow* HSD_ShadowAlloc(void)
{
  HSD_Shadow *shadow;

  shadow = HSD_ObjAlloc(&shadow_alloc_data);
  memset(shadow, 0, sizeof(HSD_Shadow));
  shadow->camera = HSD_CObjAlloc();
  shadow->texture = allocShadowTObj();
  shadow->texture->imagedesc = HSD_ImageDescAlloc();

  shadow->scaleS = 0.5F;
  shadow->scaleT = -0.5F;
  shadow->transS = 0.5F;
  shadow->transT = 0.5F;
  shadow->intensity = 0;

  shadow->texture->imagedesc->format = 0;
  shadow->texture->imagedesc->width = 256;
  shadow->texture->imagedesc->height = 256;

  HSD_CObjSetViewportfx4(shadow->camera, 0, 256, 0, 256);
  HSD_CObjSetScissorx4(shadow->camera, 0, 256, 0, 256);

  return shadow;
}
#else
asm HSD_Shadow* HSD_ShadowAlloc(void)
{
    nofralloc
/* 8037F280 0037BE60  7C 08 02 A6 */	mflr r0
/* 8037F284 0037BE64  3C 60 80 4C */	lis r3, shadow_alloc_data@ha
/* 8037F288 0037BE68  90 01 00 04 */	stw r0, 4(r1)
/* 8037F28C 0037BE6C  38 63 25 D8 */	addi r3, r3, shadow_alloc_data@l
/* 8037F290 0037BE70  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8037F294 0037BE74  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8037F298 0037BE78  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8037F29C 0037BE7C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8037F2A0 0037BE80  4B FF B9 29 */	bl HSD_ObjAlloc
/* 8037F2A4 0037BE84  3B A3 00 00 */	addi r29, r3, 0
/* 8037F2A8 0037BE88  38 80 00 00 */	li r4, 0
/* 8037F2AC 0037BE8C  38 A0 00 28 */	li r5, 0x28
/* 8037F2B0 0037BE90  4B C8 3E 51 */	bl memset
/* 8037F2B4 0037BE94  4B FE AF DD */	bl HSD_CObjAlloc
/* 8037F2B8 0037BE98  90 7D 00 04 */	stw r3, 4(r29)
/* 8037F2BC 0037BE9C  4B FE 1E D1 */	bl allocShadowTObj
/* 8037F2C0 0037BEA0  3B C3 00 00 */	addi r30, r3, 0
/* 8037F2C4 0037BEA4  3B E0 00 00 */	li r31, 0
/* 8037F2C8 0037BEA8  93 E3 00 10 */	stw r31, 0x10(r3)
/* 8037F2CC 0037BEAC  3C 60 00 54 */	lis r3, 0x00540103@ha
/* 8037F2D0 0037BEB0  38 03 01 03 */	addi r0, r3, 0x00540103@l
/* 8037F2D4 0037BEB4  93 FE 00 40 */	stw r31, 0x40(r30)
/* 8037F2D8 0037BEB8  93 FE 00 44 */	stw r31, 0x44(r30)
/* 8037F2DC 0037BEBC  90 1E 00 4C */	stw r0, 0x4c(r30)
/* 8037F2E0 0037BEC0  4B FE 20 19 */	bl HSD_ImageDescAlloc
/* 8037F2E4 0037BEC4  90 7E 00 58 */	stw r3, 0x58(r30)
/* 8037F2E8 0037BEC8  38 00 01 00 */	li r0, 0x100
/* 8037F2EC 0037BECC  93 DD 00 08 */	stw r30, 8(r29)
/* 8037F2F0 0037BED0  C0 22 ED 88 */	lfs f1, lbl_804DE768(r2)
/* 8037F2F4 0037BED4  D0 3D 00 0C */	stfs f1, 0xc(r29)
/* 8037F2F8 0037BED8  C0 02 ED 8C */	lfs f0, lbl_804DE76C(r2)
/* 8037F2FC 0037BEDC  D0 1D 00 10 */	stfs f0, 0x10(r29)
/* 8037F300 0037BEE0  D0 3D 00 14 */	stfs f1, 0x14(r29)
/* 8037F304 0037BEE4  D0 3D 00 18 */	stfs f1, 0x18(r29)
/* 8037F308 0037BEE8  9B FD 00 20 */	stb r31, 0x20(r29)
/* 8037F30C 0037BEEC  80 7D 00 08 */	lwz r3, 8(r29)
/* 8037F310 0037BEF0  80 63 00 58 */	lwz r3, 0x58(r3)
/* 8037F314 0037BEF4  93 E3 00 08 */	stw r31, 8(r3)
/* 8037F318 0037BEF8  80 7D 00 08 */	lwz r3, 8(r29)
/* 8037F31C 0037BEFC  80 63 00 58 */	lwz r3, 0x58(r3)
/* 8037F320 0037BF00  B0 03 00 04 */	sth r0, 4(r3)
/* 8037F324 0037BF04  80 7D 00 08 */	lwz r3, 8(r29)
/* 8037F328 0037BF08  80 63 00 58 */	lwz r3, 0x58(r3)
/* 8037F32C 0037BF0C  B0 03 00 06 */	sth r0, 6(r3)
/* 8037F330 0037BF10  C0 22 ED 90 */	lfs f1, lbl_804DE770(r2)
/* 8037F334 0037BF14  C0 42 ED 94 */	lfs f2, lbl_804DE774(r2)
/* 8037F338 0037BF18  FC 60 08 90 */	fmr f3, f1
/* 8037F33C 0037BF1C  80 7D 00 04 */	lwz r3, 4(r29)
/* 8037F340 0037BF20  FC 80 10 90 */	fmr f4, f2
/* 8037F344 0037BF24  4B FE AD CD */	bl HSD_CObjSetViewportfx4
/* 8037F348 0037BF28  80 7D 00 04 */	lwz r3, 4(r29)
/* 8037F34C 0037BF2C  38 80 00 00 */	li r4, 0
/* 8037F350 0037BF30  38 A0 01 00 */	li r5, 0x100
/* 8037F354 0037BF34  38 C0 00 00 */	li r6, 0
/* 8037F358 0037BF38  38 E0 01 00 */	li r7, 0x100
/* 8037F35C 0037BF3C  4B FE AC B5 */	bl HSD_CObjSetScissorx4
/* 8037F360 0037BF40  7F A3 EB 78 */	mr r3, r29
/* 8037F364 0037BF44  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8037F368 0037BF48  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8037F36C 0037BF4C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8037F370 0037BF50  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8037F374 0037BF54  38 21 00 20 */	addi r1, r1, 0x20
/* 8037F378 0037BF58  7C 08 03 A6 */	mtlr r0
/* 8037F37C 0037BF5C  4E 80 00 20 */	blr 
}
#endif
