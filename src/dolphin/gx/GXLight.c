#include <functions.h> // todo
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/GX_unknown_001/__GX_unknown_001.h>
#include <dolphin/gx/__GXLight.h>

extern const f64 lbl_804DE260;

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

#ifdef NON_MATCHING

#else

#endif

// https://decomp.me/scratch/Dk5Fr // 135 (86.50%)
asm void GXInitLightColor(GXLightObj *, GXColor *)
{ // clang-format off
    nofralloc
/* 8033E11C 0033ACFC  88 04 00 01 */	lbz r0, 1(r4)
/* 8033E120 0033AD00  88 A4 00 00 */	lbz r5, 0(r4)
/* 8033E124 0033AD04  88 C4 00 02 */	lbz r6, 2(r4)
/* 8033E128 0033AD08  54 00 80 1E */	slwi r0, r0, 0x10
/* 8033E12C 0033AD0C  50 A0 C0 0E */	rlwimi r0, r5, 0x18, 0, 7
/* 8033E130 0033AD10  88 84 00 03 */	lbz r4, 3(r4)
/* 8033E134 0033AD14  50 C0 44 2E */	rlwimi r0, r6, 8, 0x10, 0x17
/* 8033E138 0033AD18  7C 80 03 78 */	or r0, r4, r0
/* 8033E13C 0033AD1C  90 03 00 0C */	stw r0, 0xc(r3)
/* 8033E140 0033AD20  4E 80 00 20 */	blr 
} // clang-format on
#pragma peephole on

// https://decomp.me/scratch/dLcp8 // 0 (100%)
asm void GXLoadLightObjImm(GXLightObj *, u32)
{ // clang-format off
    nofralloc
/* 8033E144 0033AD24  2C 04 00 10 */	cmpwi r4, 0x10
/* 8033E148 0033AD28  41 82 00 7C */	beq lbl_8033E1C4
/* 8033E14C 0033AD2C  40 80 00 34 */	bge lbl_8033E180
/* 8033E150 0033AD30  2C 04 00 04 */	cmpwi r4, 4
/* 8033E154 0033AD34  41 82 00 60 */	beq lbl_8033E1B4
/* 8033E158 0033AD38  40 80 00 1C */	bge lbl_8033E174
/* 8033E15C 0033AD3C  2C 04 00 02 */	cmpwi r4, 2
/* 8033E160 0033AD40  41 82 00 4C */	beq lbl_8033E1AC
/* 8033E164 0033AD44  40 80 00 80 */	bge lbl_8033E1E4
/* 8033E168 0033AD48  2C 04 00 01 */	cmpwi r4, 1
/* 8033E16C 0033AD4C  40 80 00 38 */	bge lbl_8033E1A4
/* 8033E170 0033AD50  48 00 00 74 */	b lbl_8033E1E4
lbl_8033E174:
/* 8033E174 0033AD54  2C 04 00 08 */	cmpwi r4, 8
/* 8033E178 0033AD58  41 82 00 44 */	beq lbl_8033E1BC
/* 8033E17C 0033AD5C  48 00 00 68 */	b lbl_8033E1E4
lbl_8033E180:
/* 8033E180 0033AD60  2C 04 00 40 */	cmpwi r4, 0x40
/* 8033E184 0033AD64  41 82 00 50 */	beq lbl_8033E1D4
/* 8033E188 0033AD68  40 80 00 10 */	bge lbl_8033E198
/* 8033E18C 0033AD6C  2C 04 00 20 */	cmpwi r4, 0x20
/* 8033E190 0033AD70  41 82 00 3C */	beq lbl_8033E1CC
/* 8033E194 0033AD74  48 00 00 50 */	b lbl_8033E1E4
lbl_8033E198:
/* 8033E198 0033AD78  2C 04 00 80 */	cmpwi r4, 0x80
/* 8033E19C 0033AD7C  41 82 00 40 */	beq lbl_8033E1DC
/* 8033E1A0 0033AD80  48 00 00 44 */	b lbl_8033E1E4
lbl_8033E1A4:
/* 8033E1A4 0033AD84  38 00 00 00 */	li r0, 0
/* 8033E1A8 0033AD88  48 00 00 40 */	b lbl_8033E1E8
lbl_8033E1AC:
/* 8033E1AC 0033AD8C  38 00 00 01 */	li r0, 1
/* 8033E1B0 0033AD90  48 00 00 38 */	b lbl_8033E1E8
lbl_8033E1B4:
/* 8033E1B4 0033AD94  38 00 00 02 */	li r0, 2
/* 8033E1B8 0033AD98  48 00 00 30 */	b lbl_8033E1E8
lbl_8033E1BC:
/* 8033E1BC 0033AD9C  38 00 00 03 */	li r0, 3
/* 8033E1C0 0033ADA0  48 00 00 28 */	b lbl_8033E1E8
lbl_8033E1C4:
/* 8033E1C4 0033ADA4  38 00 00 04 */	li r0, 4
/* 8033E1C8 0033ADA8  48 00 00 20 */	b lbl_8033E1E8
lbl_8033E1CC:
/* 8033E1CC 0033ADAC  38 00 00 05 */	li r0, 5
/* 8033E1D0 0033ADB0  48 00 00 18 */	b lbl_8033E1E8
lbl_8033E1D4:
/* 8033E1D4 0033ADB4  38 00 00 06 */	li r0, 6
/* 8033E1D8 0033ADB8  48 00 00 10 */	b lbl_8033E1E8
lbl_8033E1DC:
/* 8033E1DC 0033ADBC  38 00 00 07 */	li r0, 7
/* 8033E1E0 0033ADC0  48 00 00 08 */	b lbl_8033E1E8
lbl_8033E1E4:
/* 8033E1E4 0033ADC4  38 00 00 00 */	li r0, 0
lbl_8033E1E8:
/* 8033E1E8 0033ADC8  54 05 20 36 */	slwi r5, r0, 4
/* 8033E1EC 0033ADCC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033E1F0 0033ADD0  38 05 06 00 */	addi r0, r5, 0x600
/* 8033E1F4 0033ADD4  38 A0 00 10 */	li r5, 0x10
/* 8033E1F8 0033ADD8  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8033E1FC 0033ADDC  98 A6 80 00 */	stb r5, 0xCC008000@l(r6)
/* 8033E200 0033ADE0  64 00 00 0F */	oris r0, r0, 0xf
/* 8033E204 0033ADE4  38 A0 00 00 */	li r5, 0
/* 8033E208 0033ADE8  90 06 80 00 */	stw r0, -0x8000(r6)
/* 8033E20C 0033ADEC  38 00 00 01 */	li r0, 1
/* 8033E210 0033ADF0  90 A6 80 00 */	stw r5, -0x8000(r6)
/* 8033E214 0033ADF4  90 A6 80 00 */	stw r5, -0x8000(r6)
/* 8033E218 0033ADF8  90 A6 80 00 */	stw r5, -0x8000(r6)
/* 8033E21C 0033ADFC  80 A3 00 0C */	lwz r5, 0xc(r3)
/* 8033E220 0033AE00  90 A6 80 00 */	stw r5, -0x8000(r6)
/* 8033E224 0033AE04  C0 03 00 10 */	lfs f0, 0x10(r3)
/* 8033E228 0033AE08  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E22C 0033AE0C  C0 03 00 14 */	lfs f0, 0x14(r3)
/* 8033E230 0033AE10  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E234 0033AE14  C0 03 00 18 */	lfs f0, 0x18(r3)
/* 8033E238 0033AE18  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E23C 0033AE1C  C0 03 00 1C */	lfs f0, 0x1c(r3)
/* 8033E240 0033AE20  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E244 0033AE24  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 8033E248 0033AE28  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E24C 0033AE2C  C0 03 00 24 */	lfs f0, 0x24(r3)
/* 8033E250 0033AE30  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E254 0033AE34  C0 03 00 28 */	lfs f0, 0x28(r3)
/* 8033E258 0033AE38  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E25C 0033AE3C  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 8033E260 0033AE40  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E264 0033AE44  C0 03 00 30 */	lfs f0, 0x30(r3)
/* 8033E268 0033AE48  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E26C 0033AE4C  C0 03 00 34 */	lfs f0, 0x34(r3)
/* 8033E270 0033AE50  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E274 0033AE54  C0 03 00 38 */	lfs f0, 0x38(r3)
/* 8033E278 0033AE58  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E27C 0033AE5C  C0 03 00 3C */	lfs f0, 0x3c(r3)
/* 8033E280 0033AE60  D0 06 80 00 */	stfs f0, -0x8000(r6)
/* 8033E284 0033AE64  B0 04 00 02 */	sth r0, 2(r4)
/* 8033E288 0033AE68  4E 80 00 20 */	blr 
} // clang-format on
#pragma peephole on

// https://decomp.me/scratch/DOTYM // 9765 (0%)
asm void GXSetChanAmbColor(GXChannelID, GXColor *)
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
#pragma peephole on

asm void GXSetChanMatColor(GXChannelID, GXColor *)
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
#pragma peephole on

// https://decomp.me/scratch/MXbI8 // 290 (84.74%)
asm void GXSetNumChans(u8)
{ // clang-format off
    nofralloc
/* 8033E55C 0033B13C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033E560 0033B140  54 67 06 3E */	clrlwi r7, r3, 0x18
/* 8033E564 0033B144  54 60 25 36 */	rlwinm r0, r3, 4, 0x14, 0x1b
/* 8033E568 0033B148  38 C4 02 04 */	addi r6, r4, 0x204
/* 8033E56C 0033B14C  80 A4 02 04 */	lwz r5, 0x204(r4)
/* 8033E570 0033B150  38 60 00 10 */	li r3, 0x10
/* 8033E574 0033B154  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8033E578 0033B158  54 A5 07 30 */	rlwinm r5, r5, 0, 0x1c, 0x18
/* 8033E57C 0033B15C  7C A0 03 78 */	or r0, r5, r0
/* 8033E580 0033B160  90 06 00 00 */	stw r0, 0(r6)
/* 8033E584 0033B164  38 00 10 09 */	li r0, 0x1009
/* 8033E588 0033B168  98 64 80 00 */	stb r3, 0xCC008000@l(r4)
/* 8033E58C 0033B16C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033E590 0033B170  90 04 80 00 */	stw r0, -0x8000(r4)
/* 8033E594 0033B174  90 E4 80 00 */	stw r7, -0x8000(r4)
/* 8033E598 0033B178  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 8033E59C 0033B17C  60 00 00 04 */	ori r0, r0, 4
/* 8033E5A0 0033B180  90 03 04 F0 */	stw r0, 0x4f0(r3)
/* 8033E5A4 0033B184  4E 80 00 20 */	blr 
} // clang-format on
#pragma peephole on

asm void GXSetChanCtrl(GXChannelID, u8, GXColorSrc, GXColorSrc, GXLightID, GXDiffuseFn, GXAttnFn)
{ // clang-format off
    nofralloc
/* 8033E5A8 0033B188  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8033E5AC 0033B18C  2C 03 00 04 */	cmpwi r3, 4
/* 8033E5B0 0033B190  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8033E5B4 0033B194  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8033E5B8 0033B198  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8033E5BC 0033B19C  93 81 00 28 */	stw r28, 0x28(r1)
/* 8033E5C0 0033B1A0  40 82 00 0C */	bne lbl_8033E5CC
/* 8033E5C4 0033B1A4  39 60 00 00 */	li r11, 0
/* 8033E5C8 0033B1A8  48 00 00 18 */	b lbl_8033E5E0
lbl_8033E5CC:
/* 8033E5CC 0033B1AC  2C 03 00 05 */	cmpwi r3, 5
/* 8033E5D0 0033B1B0  40 82 00 0C */	bne lbl_8033E5DC
/* 8033E5D4 0033B1B4  39 60 00 01 */	li r11, 1
/* 8033E5D8 0033B1B8  48 00 00 08 */	b lbl_8033E5E0
lbl_8033E5DC:
/* 8033E5DC 0033B1BC  7C 6B 1B 78 */	mr r11, r3
lbl_8033E5E0:
/* 8033E5E0 0033B1C0  54 84 0D FC */	rlwinm r4, r4, 1, 0x17, 0x1e
/* 8033E5E4 0033B1C4  7C 8A 33 78 */	or r10, r4, r6
/* 8033E5E8 0033B1C8  54 E0 07 FE */	clrlwi r0, r7, 0x1f
/* 8033E5EC 0033B1CC  7C C0 00 D0 */	neg r6, r0
/* 8033E5F0 0033B1D0  30 86 FF FF */	addic r4, r6, -1
/* 8033E5F4 0033B1D4  54 E0 07 BC */	rlwinm r0, r7, 0, 0x1e, 0x1e
/* 8033E5F8 0033B1D8  7D 80 00 D0 */	neg r12, r0
/* 8033E5FC 0033B1DC  7C C4 31 10 */	subfe r6, r4, r6
/* 8033E600 0033B1E0  30 8C FF FF */	addic r4, r12, -1
/* 8033E604 0033B1E4  7C 84 61 10 */	subfe r4, r4, r12
/* 8033E608 0033B1E8  54 E0 07 7A */	rlwinm r0, r7, 0, 0x1d, 0x1d
/* 8033E60C 0033B1EC  7F 80 00 D0 */	neg r28, r0
/* 8033E610 0033B1F0  30 1C FF FF */	addic r0, r28, -1
/* 8033E614 0033B1F4  54 EC 07 38 */	rlwinm r12, r7, 0, 0x1c, 0x1c
/* 8033E618 0033B1F8  7C 00 E1 10 */	subfe r0, r0, r28
/* 8033E61C 0033B1FC  7F AC 00 D0 */	neg r29, r12
/* 8033E620 0033B200  33 9D FF FF */	addic r28, r29, -1
/* 8033E624 0033B204  54 EC 06 F6 */	rlwinm r12, r7, 0, 0x1b, 0x1b
/* 8033E628 0033B208  7F CC 00 D0 */	neg r30, r12
/* 8033E62C 0033B20C  7F 9C E9 10 */	subfe r28, r28, r29
/* 8033E630 0033B210  33 BE FF FF */	addic r29, r30, -1
/* 8033E634 0033B214  54 EC 06 B4 */	rlwinm r12, r7, 0, 0x1a, 0x1a
/* 8033E638 0033B218  7F EC 00 D0 */	neg r31, r12
/* 8033E63C 0033B21C  7F BD F1 10 */	subfe r29, r29, r30
/* 8033E640 0033B220  33 DF FF FF */	addic r30, r31, -1
/* 8033E644 0033B224  54 EC 06 72 */	rlwinm r12, r7, 0, 0x19, 0x19
/* 8033E648 0033B228  7F DE F9 10 */	subfe r30, r30, r31
/* 8033E64C 0033B22C  7F EC 00 D0 */	neg r31, r12
/* 8033E650 0033B230  31 9F FF FF */	addic r12, r31, -1
/* 8033E654 0033B234  55 4A 06 B0 */	rlwinm r10, r10, 0, 0x1a, 0x18
/* 8033E658 0033B238  54 A5 30 32 */	slwi r5, r5, 6
/* 8033E65C 0033B23C  7D 45 2B 78 */	or r5, r10, r5
/* 8033E660 0033B240  54 AA 07 B8 */	rlwinm r10, r5, 0, 0x1e, 0x1c
/* 8033E664 0033B244  54 C5 10 3A */	slwi r5, r6, 2
/* 8033E668 0033B248  7D 45 2B 78 */	or r5, r10, r5
/* 8033E66C 0033B24C  54 A5 07 76 */	rlwinm r5, r5, 0, 0x1d, 0x1b
/* 8033E670 0033B250  54 84 18 38 */	slwi r4, r4, 3
/* 8033E674 0033B254  7C A4 23 78 */	or r4, r5, r4
/* 8033E678 0033B258  54 84 07 34 */	rlwinm r4, r4, 0, 0x1c, 0x1a
/* 8033E67C 0033B25C  54 00 20 36 */	slwi r0, r0, 4
/* 8033E680 0033B260  7C 80 03 78 */	or r0, r4, r0
/* 8033E684 0033B264  54 04 06 F2 */	rlwinm r4, r0, 0, 0x1b, 0x19
/* 8033E688 0033B268  57 80 28 34 */	slwi r0, r28, 5
/* 8033E68C 0033B26C  7C 80 03 78 */	or r0, r4, r0
/* 8033E690 0033B270  54 04 05 66 */	rlwinm r4, r0, 0, 0x15, 0x13
/* 8033E694 0033B274  57 A0 58 28 */	slwi r0, r29, 0xb
/* 8033E698 0033B278  7C 80 03 78 */	or r0, r4, r0
/* 8033E69C 0033B27C  54 04 05 24 */	rlwinm r4, r0, 0, 0x14, 0x12
/* 8033E6A0 0033B280  57 C0 60 26 */	slwi r0, r30, 0xc
/* 8033E6A4 0033B284  7C 80 03 78 */	or r0, r4, r0
/* 8033E6A8 0033B288  54 E7 06 30 */	rlwinm r7, r7, 0, 0x18, 0x18
/* 8033E6AC 0033B28C  7F EC F9 10 */	subfe r31, r12, r31
/* 8033E6B0 0033B290  7D 87 00 D0 */	neg r12, r7
/* 8033E6B4 0033B294  30 EC FF FF */	addic r7, r12, -1
/* 8033E6B8 0033B298  54 04 04 E2 */	rlwinm r4, r0, 0, 0x13, 0x11
/* 8033E6BC 0033B29C  57 E0 68 24 */	slwi r0, r31, 0xd
/* 8033E6C0 0033B2A0  7C 80 03 78 */	or r0, r4, r0
/* 8033E6C4 0033B2A4  7C E7 61 10 */	subfe r7, r7, r12
/* 8033E6C8 0033B2A8  54 04 04 A0 */	rlwinm r4, r0, 0, 0x12, 0x10
/* 8033E6CC 0033B2AC  54 E0 70 22 */	slwi r0, r7, 0xe
/* 8033E6D0 0033B2B0  2C 09 00 00 */	cmpwi r9, 0
/* 8033E6D4 0033B2B4  7C 86 03 78 */	or r6, r4, r0
/* 8033E6D8 0033B2B8  40 82 00 08 */	bne lbl_8033E6E0
/* 8033E6DC 0033B2BC  39 00 00 00 */	li r8, 0
lbl_8033E6E0:
/* 8033E6E0 0033B2C0  20 A9 00 02 */	subfic r5, r9, 2
/* 8033E6E4 0033B2C4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033E6E8 0033B2C8  30 05 FF FF */	addic r0, r5, -1
/* 8033E6EC 0033B2CC  7D 40 29 10 */	subfe r10, r0, r5
/* 8033E6F0 0033B2D0  7C A9 00 D0 */	neg r5, r9
/* 8033E6F4 0033B2D4  30 05 FF FF */	addic r0, r5, -1
/* 8033E6F8 0033B2D8  7C E0 29 10 */	subfe r7, r0, r5
/* 8033E6FC 0033B2DC  54 C5 06 6C */	rlwinm r5, r6, 0, 0x19, 0x16
/* 8033E700 0033B2E0  55 00 38 30 */	slwi r0, r8, 7
/* 8033E704 0033B2E4  7C A8 03 78 */	or r8, r5, r0
/* 8033E708 0033B2E8  38 C0 00 10 */	li r6, 0x10
/* 8033E70C 0033B2EC  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033E710 0033B2F0  98 C5 80 00 */	stb r6, 0xCC008000@l(r5)
/* 8033E714 0033B2F4  38 0B 10 0E */	addi r0, r11, 0x100e
/* 8033E718 0033B2F8  55 09 05 EA */	rlwinm r9, r8, 0, 0x17, 0x15
/* 8033E71C 0033B2FC  55 48 48 2C */	slwi r8, r10, 9
/* 8033E720 0033B300  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8033E724 0033B304  7D 20 43 78 */	or r0, r9, r8
/* 8033E728 0033B308  54 08 05 A8 */	rlwinm r8, r0, 0, 0x16, 0x14
/* 8033E72C 0033B30C  54 E0 50 2A */	slwi r0, r7, 0xa
/* 8033E730 0033B310  7D 07 03 78 */	or r7, r8, r0
/* 8033E734 0033B314  90 E5 80 00 */	stw r7, -0x8000(r5)
/* 8033E738 0033B318  38 00 00 01 */	li r0, 1
/* 8033E73C 0033B31C  2C 03 00 04 */	cmpwi r3, 4
/* 8033E740 0033B320  B0 04 00 02 */	sth r0, 2(r4)
/* 8033E744 0033B324  40 82 00 18 */	bne lbl_8033E75C
/* 8033E748 0033B328  98 C5 80 00 */	stb r6, -0x8000(r5)
/* 8033E74C 0033B32C  38 00 10 10 */	li r0, 0x1010
/* 8033E750 0033B330  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8033E754 0033B334  90 E5 80 00 */	stw r7, -0x8000(r5)
/* 8033E758 0033B338  48 00 00 1C */	b lbl_8033E774
lbl_8033E75C:
/* 8033E75C 0033B33C  2C 03 00 05 */	cmpwi r3, 5
/* 8033E760 0033B340  40 82 00 14 */	bne lbl_8033E774
/* 8033E764 0033B344  98 C5 80 00 */	stb r6, -0x8000(r5)
/* 8033E768 0033B348  38 00 10 11 */	li r0, 0x1011
/* 8033E76C 0033B34C  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8033E770 0033B350  90 E5 80 00 */	stw r7, -0x8000(r5)
lbl_8033E774:
/* 8033E774 0033B354  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8033E778 0033B358  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8033E77C 0033B35C  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8033E780 0033B360  83 81 00 28 */	lwz r28, 0x28(r1)
/* 8033E784 0033B364  38 21 00 38 */	addi r1, r1, 0x38
/* 8033E788 0033B368  4E 80 00 20 */	blr
} // clang-format on
#pragma peephole on
