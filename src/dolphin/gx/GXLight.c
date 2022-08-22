#include <dolphin/gx/GXLight.h>
#include <dolphin/gx/__GXInit.h>
#include <functions.h> // todo
#include <dolphin/gx/GX_unknown_001/__GX_unknown_001.h>

void GXInitLightAttn(GXLightObj *light, f32 aa, f32 ab, f32 ac, f32 ka, f32 kb, f32 kc)
{
    light->aa = aa;
    light->ab = ab;
    light->ac = ac;
    light->ka = ka;
    light->kb = kb;
    light->kc = kc;
}

void GXInitLightSpot(GXLightObj *light, f32 angle, GXSpotFn fn)
{
    f32 rad, temp;
    f32 a, b, c;

    if (angle <= 0.0f || angle > 90.0f)
        fn = GX_SP_OFF;

    rad = cosf((3.1415927410125732f * angle) / 180.0f);

    switch (fn)
    {
    case GX_SP_FLAT:
        a = -1000.0f * rad;
        b = 1000.0f;
        c = 0.0f;
        break;
    case GX_SP_COS:
        c = 0.0f;
        a = -rad / (1.0f - rad);
        b = 1.0f / (1.0f - rad);
        break;
    case GX_SP_COS2:
        a = 0.0f;
        b = -rad / (1.0f - rad);
        c = 1.0f / (1.0f - rad);
        break;
    case GX_SP_SHARP:
        temp = 1.0f - rad;
        temp *= temp;
        b = 2.0f / temp;
        a = (rad * (rad - 2.0f)) / temp;
        c = -1.0f / temp;
        break;
    case GX_SP_RING1:
        temp = 1.0f - rad;
        temp *= temp;
        a = (-4.0f * rad) / temp;
        b = (4.0f * (1.0f + rad)) / temp;
        c = -4.0f / temp;
        break;
    case GX_SP_RING2:
        temp = 1.0f - rad;
        temp *= temp;
        a = 1.0f - ((2.0f * rad * rad) / temp);
        b = (4.0f * rad) / temp;
        c = -2.0f / temp;
        break;
    case GX_SP_OFF:
    default:
        b = 0.0f;
        a = 1.0f;
        c = 0.0f;
        break;
    }

    light->aa = a;
    light->ab = b;
    light->ac = c;
}

static void GXInitLightAttnK(GXLightObj *light, f32 ka, f32 kb, f32 kc)
{
    light->ka = ka;
    light->kb = kb;
    light->kc = kc;
}

void GXInitLightDistAttn(GXLightObj *light, f32 ref_distance, f32 ref_brightness, GXDistAttnFn dist_fn)
{
    f32 ka, kb, kc;

    if (ref_distance < 0.0f)
        dist_fn = GX_DA_OFF;

    if (ref_brightness <= 0.0f || ref_brightness >= 1.0f)
        dist_fn = GX_DA_OFF;

    switch (dist_fn)
    {
    case GX_DA_GENTLE:
        ka = 1.0f;
        kb = (1.0f - ref_brightness) / (ref_brightness * ref_distance);
        kc = 0.0f;
        break;
    case GX_DA_MEDIUM:
        ka = 1.0f;
        kb = (0.5f * (1.0f - ref_brightness)) / (ref_brightness * ref_distance);
        kc = (0.5f * (1.0f - ref_brightness)) / (ref_brightness * ref_distance * ref_distance);
        break;
    case GX_DA_STEEP:
        ka = 1.0f;
        kb = 0.0f;
        kc = (1.0f - ref_brightness) / (ref_brightness * ref_distance * ref_distance);
        break;
    case GX_DA_OFF:
    default:
        ka = 1.0f;
        kb = 0.0f;
        kc = 0.0f;
        break;
    }

    GXInitLightAttnK(light, ka, kb, kc);
}

void GXInitLightPos(GXLightObj *light, f32 x, f32 y, f32 z)
{
    light->pos.x = x;
    light->pos.y = y;
    light->pos.z = z;
}

void GXInitLightDir(GXLightObj *light, f32 x, f32 y, f32 z)
{
    light->dir.x = -x;
    light->dir.y = -y;
    light->dir.z = -z;
}

void GXInitLightColor(GXLightObj *light, GXColor *color)
{
    *(u32 *)&light->color = (color->r << 24) | (color->g << 16) | (color->b << 8) | color->a;
}

void GXLoadLightObjImm(GXLightObj *light, GXLightID light_id)
{
    u32 ordinal_id;

    switch (light_id)
    {
    case GX_LIGHT0:
        ordinal_id = 0;
        break;
    case GX_LIGHT1:
        ordinal_id = 1;
        break;
    case GX_LIGHT2:
        ordinal_id = 2;
        break;
    case GX_LIGHT3:
        ordinal_id = 3;
        break;
    case GX_LIGHT4:
        ordinal_id = 4;
        break;
    case GX_LIGHT5:
        ordinal_id = 5;
        break;
    case GX_LIGHT6:
        ordinal_id = 6;
        break;
    case GX_LIGHT7:
        ordinal_id = 7;
        break;
    default:
        ordinal_id = 0;
        break;
    }

    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = ((ordinal_id << 4) + 0x600) | 0xF0000;
    WGPIPE.u32 = 0;
    WGPIPE.u32 = 0;
    WGPIPE.u32 = 0;
    GX_WRITE_U32(light->color);
    GX_WRITE_F32(light->aa);
    GX_WRITE_F32(light->ab);
    GX_WRITE_F32(light->ac);
    GX_WRITE_F32(light->ka);
    GX_WRITE_F32(light->kb);
    GX_WRITE_F32(light->kc);
    GX_WRITE_F32(light->pos.x);
    GX_WRITE_F32(light->pos.y);
    GX_WRITE_F32(light->pos.z);
    GX_WRITE_F32(light->dir.x);
    GX_WRITE_F32(light->dir.y);
    GX_WRITE_F32(light->dir.z);

    set_x2(GX_TRUE);
}

#pragma push

// https://decomp.me/scratch/DOTYM // 9765 (0%)
asm void GXSetChanAmbColor(GXChannelID chan, GXColor *color)
{ // clang-format off
    nofralloc
/* 8033E28C 0033AE6C  2C 03 00 03 */	cmpwi r3, 3
/* 8033E290 0033AE70  41 82 00 B0 */	beq lbl_8033E340
/* 8033E294 0033AE74  40 80 00 1C */	bge lbl_8033E2B0
/* 8033E298 0033AE78  2C 03 00 01 */	cmpwi r3, 1
/* 8033E29C 0033AE7C  41 82 00 58 */	beq lbl_8033E2F4
/* 8033E2A0 0033AE80  40 80 00 88 */	bge lbl_8033E328
/* 8033E2A4 0033AE84  2C 03 00 00 */	cmpwi r3, 0
/* 8033E2A8 0033AE88  40 80 00 18 */	bge lbl_8033E2C0
/* 8033E2AC 0033AE8C  4E 80 00 20 */	blr 
lbl_8033E2B0:
/* 8033E2B0 0033AE90  2C 03 00 05 */	cmpwi r3, 5
/* 8033E2B4 0033AE94  41 82 00 D4 */	beq lbl_8033E388
/* 8033E2B8 0033AE98  4C 80 00 20 */	bgelr 
/* 8033E2BC 0033AE9C  48 00 00 9C */	b lbl_8033E358
lbl_8033E2C0:
/* 8033E2C0 0033AEA0  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033E2C4 0033AEA4  38 60 00 00 */	li r3, 0
/* 8033E2C8 0033AEA8  88 C4 00 02 */	lbz r6, 2(r4)
/* 8033E2CC 0033AEAC  80 E5 00 A8 */	lwz r7, 0xa8(r5)
/* 8033E2D0 0033AEB0  88 A4 00 01 */	lbz r5, 1(r4)
/* 8033E2D4 0033AEB4  88 04 00 00 */	lbz r0, 0(r4)
/* 8033E2D8 0033AEB8  54 E7 06 3E */	clrlwi r7, r7, 0x18
/* 8033E2DC 0033AEBC  50 C7 44 2E */	rlwimi r7, r6, 8, 0x10, 0x17
/* 8033E2E0 0033AEC0  54 A4 80 1E */	slwi r4, r5, 0x10
/* 8033E2E4 0033AEC4  50 E4 04 3E */	rlwimi r4, r7, 0, 0x10, 0x1f
/* 8033E2E8 0033AEC8  54 07 C0 0E */	slwi r7, r0, 0x18
/* 8033E2EC 0033AECC  50 87 02 3E */	rlwimi r7, r4, 0, 8, 0x1f
/* 8033E2F0 0033AED0  48 00 00 CC */	b lbl_8033E3BC
lbl_8033E2F4:
/* 8033E2F4 0033AED4  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033E2F8 0033AED8  38 60 00 01 */	li r3, 1
/* 8033E2FC 0033AEDC  88 C4 00 02 */	lbz r6, 2(r4)
/* 8033E300 0033AEE0  80 E5 00 AC */	lwz r7, 0xac(r5)
/* 8033E304 0033AEE4  88 A4 00 01 */	lbz r5, 1(r4)
/* 8033E308 0033AEE8  88 04 00 00 */	lbz r0, 0(r4)
/* 8033E30C 0033AEEC  54 E7 06 3E */	clrlwi r7, r7, 0x18
/* 8033E310 0033AEF0  50 C7 44 2E */	rlwimi r7, r6, 8, 0x10, 0x17
/* 8033E314 0033AEF4  54 A4 80 1E */	slwi r4, r5, 0x10
/* 8033E318 0033AEF8  50 E4 04 3E */	rlwimi r4, r7, 0, 0x10, 0x1f
/* 8033E31C 0033AEFC  54 07 C0 0E */	slwi r7, r0, 0x18
/* 8033E320 0033AF00  50 87 02 3E */	rlwimi r7, r4, 0, 8, 0x1f
/* 8033E324 0033AF04  48 00 00 98 */	b lbl_8033E3BC
lbl_8033E328:
/* 8033E328 0033AF08  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033E32C 0033AF0C  38 60 00 00 */	li r3, 0
/* 8033E330 0033AF10  88 E4 00 03 */	lbz r7, 3(r4)
/* 8033E334 0033AF14  80 05 00 A8 */	lwz r0, 0xa8(r5)
/* 8033E338 0033AF18  50 07 00 2E */	rlwimi r7, r0, 0, 0, 0x17
/* 8033E33C 0033AF1C  48 00 00 80 */	b lbl_8033E3BC
lbl_8033E340:
/* 8033E340 0033AF20  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033E344 0033AF24  38 60 00 01 */	li r3, 1
/* 8033E348 0033AF28  88 E4 00 03 */	lbz r7, 3(r4)
/* 8033E34C 0033AF2C  80 05 00 AC */	lwz r0, 0xac(r5)
/* 8033E350 0033AF30  50 07 00 2E */	rlwimi r7, r0, 0, 0, 0x17
/* 8033E354 0033AF34  48 00 00 68 */	b lbl_8033E3BC
lbl_8033E358:
/* 8033E358 0033AF38  88 04 00 02 */	lbz r0, 2(r4)
/* 8033E35C 0033AF3C  38 60 00 00 */	li r3, 0
/* 8033E360 0033AF40  88 E4 00 03 */	lbz r7, 3(r4)
/* 8033E364 0033AF44  54 06 40 2E */	slwi r6, r0, 8
/* 8033E368 0033AF48  88 A4 00 01 */	lbz r5, 1(r4)
/* 8033E36C 0033AF4C  88 04 00 00 */	lbz r0, 0(r4)
/* 8033E370 0033AF50  50 E6 06 3E */	rlwimi r6, r7, 0, 0x18, 0x1f
/* 8033E374 0033AF54  54 A4 80 1E */	slwi r4, r5, 0x10
/* 8033E378 0033AF58  50 C4 04 3E */	rlwimi r4, r6, 0, 0x10, 0x1f
/* 8033E37C 0033AF5C  54 07 C0 0E */	slwi r7, r0, 0x18
/* 8033E380 0033AF60  50 87 02 3E */	rlwimi r7, r4, 0, 8, 0x1f
/* 8033E384 0033AF64  48 00 00 38 */	b lbl_8033E3BC
lbl_8033E388:
/* 8033E388 0033AF68  88 04 00 02 */	lbz r0, 2(r4)
/* 8033E38C 0033AF6C  38 60 00 01 */	li r3, 1
/* 8033E390 0033AF70  88 E4 00 03 */	lbz r7, 3(r4)
/* 8033E394 0033AF74  54 06 40 2E */	slwi r6, r0, 8
/* 8033E398 0033AF78  88 A4 00 01 */	lbz r5, 1(r4)
/* 8033E39C 0033AF7C  88 04 00 00 */	lbz r0, 0(r4)
/* 8033E3A0 0033AF80  50 E6 06 3E */	rlwimi r6, r7, 0, 0x18, 0x1f
/* 8033E3A4 0033AF84  54 A4 80 1E */	slwi r4, r5, 0x10
/* 8033E3A8 0033AF88  50 C4 04 3E */	rlwimi r4, r6, 0, 0x10, 0x1f
/* 8033E3AC 0033AF8C  54 07 C0 0E */	slwi r7, r0, 0x18
/* 8033E3B0 0033AF90  50 87 02 3E */	rlwimi r7, r4, 0, 8, 0x1f
/* 8033E3B4 0033AF94  48 00 00 08 */	b lbl_8033E3BC
/* 8033E3B8 0033AF98  4E 80 00 20 */	blr 
lbl_8033E3BC:
/* 8033E3BC 0033AF9C  38 00 00 10 */	li r0, 0x10
/* 8033E3C0 0033AFA0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033E3C4 0033AFA4  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8033E3C8 0033AFA8  98 06 80 00 */	stb r0, 0xCC008000@l(r6)
/* 8033E3CC 0033AFAC  38 03 10 0A */	addi r0, r3, 0x100a
/* 8033E3D0 0033AFB0  38 A0 00 01 */	li r5, 1
/* 8033E3D4 0033AFB4  90 06 80 00 */	stw r0, -0x8000(r6)
/* 8033E3D8 0033AFB8  54 60 10 3A */	slwi r0, r3, 2
/* 8033E3DC 0033AFBC  90 E6 80 00 */	stw r7, -0x8000(r6)
/* 8033E3E0 0033AFC0  B0 A4 00 02 */	sth r5, 2(r4)
/* 8033E3E4 0033AFC4  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033E3E8 0033AFC8  7C 63 02 14 */	add r3, r3, r0
/* 8033E3EC 0033AFCC  90 E3 00 A8 */	stw r7, 0xa8(r3)
/* 8033E3F0 0033AFD0  4E 80 00 20 */	blr 
} // clang-format on

asm void GXSetChanMatColor(GXChannelID chan, GXColor *color)
{ // clang-format off
    nofralloc
/* 8033E3F4 0033AFD4  2C 03 00 03 */	cmpwi r3, 3
/* 8033E3F8 0033AFD8  41 82 00 B0 */	beq lbl_8033E4A8
/* 8033E3FC 0033AFDC  40 80 00 1C */	bge lbl_8033E418
/* 8033E400 0033AFE0  2C 03 00 01 */	cmpwi r3, 1
/* 8033E404 0033AFE4  41 82 00 58 */	beq lbl_8033E45C
/* 8033E408 0033AFE8  40 80 00 88 */	bge lbl_8033E490
/* 8033E40C 0033AFEC  2C 03 00 00 */	cmpwi r3, 0
/* 8033E410 0033AFF0  40 80 00 18 */	bge lbl_8033E428
/* 8033E414 0033AFF4  4E 80 00 20 */	blr 
lbl_8033E418:
/* 8033E418 0033AFF8  2C 03 00 05 */	cmpwi r3, 5
/* 8033E41C 0033AFFC  41 82 00 D4 */	beq lbl_8033E4F0
/* 8033E420 0033B000  4C 80 00 20 */	bgelr 
/* 8033E424 0033B004  48 00 00 9C */	b lbl_8033E4C0
lbl_8033E428:
/* 8033E428 0033B008  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033E42C 0033B00C  38 60 00 00 */	li r3, 0
/* 8033E430 0033B010  88 C4 00 02 */	lbz r6, 2(r4)
/* 8033E434 0033B014  80 E5 00 B0 */	lwz r7, 0xb0(r5)
/* 8033E438 0033B018  88 A4 00 01 */	lbz r5, 1(r4)
/* 8033E43C 0033B01C  88 04 00 00 */	lbz r0, 0(r4)
/* 8033E440 0033B020  54 E7 06 3E */	clrlwi r7, r7, 0x18
/* 8033E444 0033B024  50 C7 44 2E */	rlwimi r7, r6, 8, 0x10, 0x17
/* 8033E448 0033B028  54 A4 80 1E */	slwi r4, r5, 0x10
/* 8033E44C 0033B02C  50 E4 04 3E */	rlwimi r4, r7, 0, 0x10, 0x1f
/* 8033E450 0033B030  54 07 C0 0E */	slwi r7, r0, 0x18
/* 8033E454 0033B034  50 87 02 3E */	rlwimi r7, r4, 0, 8, 0x1f
/* 8033E458 0033B038  48 00 00 CC */	b lbl_8033E524
lbl_8033E45C:
/* 8033E45C 0033B03C  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033E460 0033B040  38 60 00 01 */	li r3, 1
/* 8033E464 0033B044  88 C4 00 02 */	lbz r6, 2(r4)
/* 8033E468 0033B048  80 E5 00 B4 */	lwz r7, 0xb4(r5)
/* 8033E46C 0033B04C  88 A4 00 01 */	lbz r5, 1(r4)
/* 8033E470 0033B050  88 04 00 00 */	lbz r0, 0(r4)
/* 8033E474 0033B054  54 E7 06 3E */	clrlwi r7, r7, 0x18
/* 8033E478 0033B058  50 C7 44 2E */	rlwimi r7, r6, 8, 0x10, 0x17
/* 8033E47C 0033B05C  54 A4 80 1E */	slwi r4, r5, 0x10
/* 8033E480 0033B060  50 E4 04 3E */	rlwimi r4, r7, 0, 0x10, 0x1f
/* 8033E484 0033B064  54 07 C0 0E */	slwi r7, r0, 0x18
/* 8033E488 0033B068  50 87 02 3E */	rlwimi r7, r4, 0, 8, 0x1f
/* 8033E48C 0033B06C  48 00 00 98 */	b lbl_8033E524
lbl_8033E490:
/* 8033E490 0033B070  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033E494 0033B074  38 60 00 00 */	li r3, 0
/* 8033E498 0033B078  88 E4 00 03 */	lbz r7, 3(r4)
/* 8033E49C 0033B07C  80 05 00 B0 */	lwz r0, 0xb0(r5)
/* 8033E4A0 0033B080  50 07 00 2E */	rlwimi r7, r0, 0, 0, 0x17
/* 8033E4A4 0033B084  48 00 00 80 */	b lbl_8033E524
lbl_8033E4A8:
/* 8033E4A8 0033B088  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033E4AC 0033B08C  38 60 00 01 */	li r3, 1
/* 8033E4B0 0033B090  88 E4 00 03 */	lbz r7, 3(r4)
/* 8033E4B4 0033B094  80 05 00 B4 */	lwz r0, 0xb4(r5)
/* 8033E4B8 0033B098  50 07 00 2E */	rlwimi r7, r0, 0, 0, 0x17
/* 8033E4BC 0033B09C  48 00 00 68 */	b lbl_8033E524
lbl_8033E4C0:
/* 8033E4C0 0033B0A0  88 04 00 02 */	lbz r0, 2(r4)
/* 8033E4C4 0033B0A4  38 60 00 00 */	li r3, 0
/* 8033E4C8 0033B0A8  88 E4 00 03 */	lbz r7, 3(r4)
/* 8033E4CC 0033B0AC  54 06 40 2E */	slwi r6, r0, 8
/* 8033E4D0 0033B0B0  88 A4 00 01 */	lbz r5, 1(r4)
/* 8033E4D4 0033B0B4  88 04 00 00 */	lbz r0, 0(r4)
/* 8033E4D8 0033B0B8  50 E6 06 3E */	rlwimi r6, r7, 0, 0x18, 0x1f
/* 8033E4DC 0033B0BC  54 A4 80 1E */	slwi r4, r5, 0x10
/* 8033E4E0 0033B0C0  50 C4 04 3E */	rlwimi r4, r6, 0, 0x10, 0x1f
/* 8033E4E4 0033B0C4  54 07 C0 0E */	slwi r7, r0, 0x18
/* 8033E4E8 0033B0C8  50 87 02 3E */	rlwimi r7, r4, 0, 8, 0x1f
/* 8033E4EC 0033B0CC  48 00 00 38 */	b lbl_8033E524
lbl_8033E4F0:
/* 8033E4F0 0033B0D0  88 04 00 02 */	lbz r0, 2(r4)
/* 8033E4F4 0033B0D4  38 60 00 01 */	li r3, 1
/* 8033E4F8 0033B0D8  88 E4 00 03 */	lbz r7, 3(r4)
/* 8033E4FC 0033B0DC  54 06 40 2E */	slwi r6, r0, 8
/* 8033E500 0033B0E0  88 A4 00 01 */	lbz r5, 1(r4)
/* 8033E504 0033B0E4  88 04 00 00 */	lbz r0, 0(r4)
/* 8033E508 0033B0E8  50 E6 06 3E */	rlwimi r6, r7, 0, 0x18, 0x1f
/* 8033E50C 0033B0EC  54 A4 80 1E */	slwi r4, r5, 0x10
/* 8033E510 0033B0F0  50 C4 04 3E */	rlwimi r4, r6, 0, 0x10, 0x1f
/* 8033E514 0033B0F4  54 07 C0 0E */	slwi r7, r0, 0x18
/* 8033E518 0033B0F8  50 87 02 3E */	rlwimi r7, r4, 0, 8, 0x1f
/* 8033E51C 0033B0FC  48 00 00 08 */	b lbl_8033E524
/* 8033E520 0033B100  4E 80 00 20 */	blr 
lbl_8033E524:
/* 8033E524 0033B104  38 00 00 10 */	li r0, 0x10
/* 8033E528 0033B108  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033E52C 0033B10C  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8033E530 0033B110  98 06 80 00 */	stb r0, 0xCC008000@l(r6)
/* 8033E534 0033B114  38 03 10 0C */	addi r0, r3, 0x100c
/* 8033E538 0033B118  38 A0 00 01 */	li r5, 1
/* 8033E53C 0033B11C  90 06 80 00 */	stw r0, -0x8000(r6)
/* 8033E540 0033B120  54 60 10 3A */	slwi r0, r3, 2
/* 8033E544 0033B124  90 E6 80 00 */	stw r7, -0x8000(r6)
/* 8033E548 0033B128  B0 A4 00 02 */	sth r5, 2(r4)
/* 8033E54C 0033B12C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033E550 0033B130  7C 63 02 14 */	add r3, r3, r0
/* 8033E554 0033B134  90 E3 00 B0 */	stw r7, 0xb0(r3)
/* 8033E558 0033B138  4E 80 00 20 */	blr 
} // clang-format on

#pragma pop

void GXSetNumChans(u8 num_chans)
{
    INSERT_FIELD(__GXContexts.main->x204, num_chans, 3, 4);
    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x1009;
    WGPIPE.u32 = num_chans;
    __GXContexts.main->x4F0_flags |= 4;
}

void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src,
                   u32 light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn)
{
    u32 reg;
    int r26;

    if (chan == 4)
        r26 = 0;
    else if (chan == 5)
        r26 = 1;
    else
        r26 = chan;

    reg = 0;
    INSERT_FIELD(reg, enable, 1, 1);
    INSERT_FIELD(reg, mat_src, 1, 0);
    INSERT_FIELD(reg, amb_src, 1, 6);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT0) != 0, 1, 2);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT1) != 0, 1, 3);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT2) != 0, 1, 4);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT3) != 0, 1, 5);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT4) != 0, 1, 11);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT5) != 0, 1, 12);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT6) != 0, 1, 13);
    INSERT_FIELD(reg, (light_mask & GX_LIGHT7) != 0, 1, 14);
    INSERT_FIELD(reg, (attn_fn == 0) ? 0 : diff_fn, 2, 7);
    INSERT_FIELD(reg, (attn_fn != 2), 1, 9);
    INSERT_FIELD(reg, (attn_fn != 0), 1, 10);

    WGPIPE.u8 = GX_LOAD_XF_REG;
    WGPIPE.u32 = 0x1000 + (r26 + 14);
    WGPIPE.u32 = reg;
    set_x2(GX_TRUE);
    if (chan == GX_COLOR0A0)
    {
        WGPIPE.u8 = GX_LOAD_XF_REG;
        WGPIPE.u32 = 0x1000 + 16;
        WGPIPE.u32 = reg;
    }
    else if (chan == GX_COLOR1A1)
    {
        WGPIPE.u8 = GX_LOAD_XF_REG;
        WGPIPE.u32 = 0x1000 + 17;
        WGPIPE.u32 = reg;
    }
}
