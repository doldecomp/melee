#include <melee/if/ifstatus.h>

#include <dolphin/os/os.h>
#include <melee/gm/code_801601C4.h>
#include <melee/lb/lbunknown_001.h>
#include <sysdolphin/baselib/random.h>

HudIndex* func_802F4910(void)
{
    return &lbl_804A10C8;
}

extern char* lbl_804D57B8;
extern f32 lbl_804DDA74;
extern f32 lbl_804DDA78;
extern f32 lbl_804DDA7C;
extern f32 lbl_804DDA80;
extern f32 lbl_804DDA6C;
extern f32 lbl_804DDA8C;
extern f32 lbl_804DDA90;
extern char* lbl_804D57B0;
extern f64 lbl_804DDA58;
extern f32 lbl_804DDA84;
extern f32 lbl_804DDA88;
extern f32 lbl_804DDA8C;
extern f32 lbl_804DDA90;
extern f32 lbl_804DDA94;
extern f32 lbl_804DDA48;
extern f32 lbl_804DDA4C;
extern f32 lbl_804DDA50;

// "jobj.h" @ lbl_804D57B0
// "jobj" @ lbl_804D57B8
#define ASSERT_NOT_NULL(value, line)      \
    if (value == NULL) {                  \
        __assert("jobj.h", line, "jobj"); \
    }

extern s8 lbl_804D6D61;

typedef struct _FlagsX {
    u32 b80 : 1;
    u32 b40 : 1;
    u32 b20 : 1;
    u32 b10 : 1;
    u32 b8 : 1;
    u32 b4 : 2;
    u32 b1 : 1;
    u8 x;
    u16 y;
} FlagsX;

typedef struct _Vec4 {
    f32 x, y, z, w;
} Vec4;

typedef struct _UnkX {
    u8 filler1[0x10];
    FlagsX x10_flags;
    u8 filler2[0x34 - 0x14];
    Vec4 x34_vec; // or f32[4] instead of Vec4
    Vec4 x44_vec;
    HSD_JObj* x54_jobj[4];
} UnkX; // HudIndex

#if NON_MATCHING

inline f32 foo(f32 a, f32 b)
{
    f32 result;
    if (lbl_804D6D61 != 0) {
        result = -a - b;
        lbl_804D6D61 = 0;
    } else {
        result = a + b;
        lbl_804D6D61 = 1;
    }
    return result;
}

inline void jobj_flagCheckSetMtxDirtySub(HSD_JObj* jobj) // jobj @ r30 when inlined
{
    //@12c
    if (!(jobj->flags & 0x02000000) && jobj) {
        //@140
        ASSERT_NOT_NULL(jobj, 0x234);
        //@154
        if ((!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) == 0) {
            //@178
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

inline void jobj_translate_x(HSD_JObj* jobj, f32 dx);
inline void jobj_translate_y(HSD_JObj* jobj, f32 dy);

inline void jobj_unk_x(UnkX* value, s32 i)
{
    HSD_JObj* jobj_r30 = value->x54_jobj[i];
    //@c8
    ASSERT_NOT_NULL(jobj_r30, 993);
    //@e0
    if (fabsf_bitwise(jobj_r30->translate.x) < 100.0f) { // 100.0f @ lbl_804DDA6C
        //@100
        jobj_r30 = value->x54_jobj[i];
        //@108
        jobj_translate_x(jobj_r30, (&value->x34_vec.x)[i]);
        //@12c
        jobj_flagCheckSetMtxDirtySub(jobj_r30);
    }
}

inline void jobj_unk_y(UnkX* value, s32 i)
{
    HSD_JObj* jobj_r30 = value->x54_jobj[i];
    //@184
    ASSERT_NOT_NULL(jobj_r30, 1006);
    //@19c
    if (jobj_r30->translate.y > -100.0f) { // -100.0f @ lbl_804DDA8C
        //@1a8
        jobj_r30 = value->x54_jobj[i];
        //@1b0
        jobj_translate_y(jobj_r30, (&value->x44_vec.x)[i]);

        //@1d4
        jobj_flagCheckSetMtxDirtySub(jobj_r30);
        //@228
        (&value->x44_vec.x)[i] -= 0.2028f; // gravity that makes percent tokens fall down? @ lbl_804DDA90
    }
}

inline void jobj_translate_x(HSD_JObj* jobj, f32 dx)
{
    //@108
    ASSERT_NOT_NULL(jobj, 1102);
    //@120
    jobj->translate.x += dx;
}

inline void jobj_translate_y(HSD_JObj* jobj, f32 dy)
{
    //@1b0
    ASSERT_NOT_NULL(jobj, 1114);
    //@1c8
    jobj->translate.y += dy;
}

inline void jobj_unk(UnkX* value)
{
    //@b0
    s32 i;
    for (i = 0; i < 4; i++) // i@r31
    {
        jobj_unk_x(value, i);
        jobj_unk_y(value, i);
        //@234 loop increment
    }
}

inline void* jobj_get(HSD_JObj* jobj_r30, UnkX* value, s32 i)
{
    return value->x54_jobj[i];
}

// HUD_PercentOnDeathAnimationThink
void func_802F491C(UnkX* value, s32, s32)
{
    s32 i;

    if (value->x10_flags.b40) {
        for (i = 0; i < 4; i++) // i@r28
        {
            (&value->x34_vec.x)[i] = foo(0.6083f * HSD_Randf(), 0.3041f); // var_f0;
            (&value->x44_vec.x)[i] = 0.811f * HSD_Randf() + 1.2165f;
        }
        value->x10_flags.b40 = 0;
        return;
    }

    for (i = 0; i < 4; i++) // i@r31
    {
        HSD_JObj* jobj_r30 = value->x54_jobj[i];
        ASSERT_NOT_NULL(jobj_r30, 993);
        if (fabsf_bitwise(jobj_r30->translate.x) < 100.0f) { // 100.0f @ lbl_804DDA6C
            f32 f = (&value->x34_vec.x)[i];
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            ASSERT_NOT_NULL(jobj_r30, 1102);
            jobj_r30->translate.x += f;
            jobj_flagCheckSetMtxDirtySub(jobj_r30);
        }
        jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
        ASSERT_NOT_NULL(jobj_r30, 1006);

        if (jobj_r30->translate.y > -100.0f) {
            f32 f = (&value->x44_vec.x)[i];
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            jobj_r30 = (void*) jobj_get(jobj_r30, value, i);
            ASSERT_NOT_NULL(jobj_r30, 1114);
            jobj_r30->translate.y += f;
            jobj_flagCheckSetMtxDirtySub(jobj_r30);
            (&value->x44_vec.x)[i] -= 0.2028f; // @ lbl_804DDA90
        }
    }
}

#else

#pragma push
asm void func_802F491C(UnkX* value, s32, s32)
{ // clang-format off
    nofralloc
/* 802F491C 002F14FC  7C 08 02 A6 */	mflr r0
/* 802F4920 002F1500  90 01 00 04 */	stw r0, 4(r1)
/* 802F4924 002F1504  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 802F4928 002F1508  DB E1 00 68 */	stfd f31, 0x68(r1)
/* 802F492C 002F150C  DB C1 00 60 */	stfd f30, 0x60(r1)
/* 802F4930 002F1510  DB A1 00 58 */	stfd f29, 0x58(r1)
/* 802F4934 002F1514  DB 81 00 50 */	stfd f28, 0x50(r1)
/* 802F4938 002F1518  BF 61 00 3C */	stmw r27, 0x3c(r1)
/* 802F493C 002F151C  7C 7B 1B 78 */	mr r27, r3
/* 802F4940 002F1520  88 03 00 10 */	lbz r0, 0x10(r3)
/* 802F4944 002F1524  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 802F4948 002F1528  41 82 00 84 */	beq lbl_802F49CC
/* 802F494C 002F152C  C3 82 E0 94 */	lfs f28, lbl_804DDA74(r2)
/* 802F4950 002F1530  7F 7D DB 78 */	mr r29, r27
/* 802F4954 002F1534  C3 E2 E0 98 */	lfs f31, lbl_804DDA78(r2)
/* 802F4958 002F1538  3B 80 00 00 */	li r28, 0
/* 802F495C 002F153C  C3 C2 E0 A0 */	lfs f30, lbl_804DDA80(r2)
/* 802F4960 002F1540  C3 A2 E0 9C */	lfs f29, lbl_804DDA7C(r2)
/* 802F4964 002F1544  3B E0 00 01 */	li r31, 1
/* 802F4968 002F1548  3B C0 00 00 */	li r30, 0
lbl_802F496C:
/* 802F496C 002F154C  48 08 BB BD */	bl HSD_Randf
/* 802F4970 002F1550  88 0D B6 C1 */	lbz r0, lbl_804D6D61(r13)
/* 802F4974 002F1554  EC 1C 00 72 */	fmuls f0, f28, f1
/* 802F4978 002F1558  7C 00 07 75 */	extsb. r0, r0
/* 802F497C 002F155C  41 82 00 14 */	beq lbl_802F4990
/* 802F4980 002F1560  FC 00 00 50 */	fneg f0, f0
/* 802F4984 002F1564  9B CD B6 C1 */	stb r30, lbl_804D6D61(r13)
/* 802F4988 002F1568  EC 00 F8 28 */	fsubs f0, f0, f31
/* 802F498C 002F156C  48 00 00 0C */	b lbl_802F4998
lbl_802F4990:
/* 802F4990 002F1570  EC 00 F8 2A */	fadds f0, f0, f31
/* 802F4994 002F1574  9B ED B6 C1 */	stb r31, lbl_804D6D61(r13)
lbl_802F4998:
/* 802F4998 002F1578  D0 1D 00 34 */	stfs f0, 0x34(r29)
/* 802F499C 002F157C  48 08 BB 8D */	bl HSD_Randf
/* 802F49A0 002F1580  EC 1E E8 7A */	fmadds f0, f30, f1, f29
/* 802F49A4 002F1584  3B 9C 00 01 */	addi r28, r28, 1
/* 802F49A8 002F1588  2C 1C 00 04 */	cmpwi r28, 4
/* 802F49AC 002F158C  D0 1D 00 44 */	stfs f0, 0x44(r29)
/* 802F49B0 002F1590  3B BD 00 04 */	addi r29, r29, 4
/* 802F49B4 002F1594  41 80 FF B8 */	blt lbl_802F496C
/* 802F49B8 002F1598  88 1B 00 10 */	lbz r0, 0x10(r27)
/* 802F49BC 002F159C  38 60 00 00 */	li r3, 0
/* 802F49C0 002F15A0  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 802F49C4 002F15A4  98 1B 00 10 */	stb r0, 0x10(r27)
/* 802F49C8 002F15A8  48 00 01 98 */	b lbl_802F4B60
lbl_802F49CC:
/* 802F49CC 002F15AC  C3 A2 E0 8C */	lfs f29, lbl_804DDA6C(r2)
/* 802F49D0 002F15B0  7F 7D DB 78 */	mr r29, r27
/* 802F49D4 002F15B4  C3 C2 E0 AC */	lfs f30, lbl_804DDA8C(r2)
/* 802F49D8 002F15B8  3B E0 00 00 */	li r31, 0
/* 802F49DC 002F15BC  C3 E2 E0 B0 */	lfs f31, lbl_804DDA90(r2)
lbl_802F49E0:
/* 802F49E0 002F15C0  83 DD 00 54 */	lwz r30, 0x54(r29)
/* 802F49E4 002F15C4  28 1E 00 00 */	cmplwi r30, 0
/* 802F49E8 002F15C8  40 82 00 14 */	bne lbl_802F49FC
/* 802F49EC 002F15CC  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F49F0 002F15D0  38 80 03 E1 */	li r4, 0x3e1
/* 802F49F4 002F15D4  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F49F8 002F15D8  48 09 38 29 */	bl __assert
lbl_802F49FC:
/* 802F49FC 002F15DC  C0 1E 00 38 */	lfs f0, 0x38(r30)
/* 802F4A00 002F15E0  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 802F4A04 002F15E4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802F4A08 002F15E8  54 00 00 7E */	clrlwi r0, r0, 1
/* 802F4A0C 002F15EC  90 01 00 2C */	stw r0, 0x2c(r1)
/* 802F4A10 002F15F0  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 802F4A14 002F15F4  FC 00 E8 40 */	fcmpo cr0, f0, f29
/* 802F4A18 002F15F8  40 80 00 84 */	bge lbl_802F4A9C
/* 802F4A1C 002F15FC  83 DD 00 54 */	lwz r30, 0x54(r29)
/* 802F4A20 002F1600  C3 9D 00 34 */	lfs f28, 0x34(r29)
/* 802F4A24 002F1604  28 1E 00 00 */	cmplwi r30, 0
/* 802F4A28 002F1608  40 82 00 14 */	bne lbl_802F4A3C
/* 802F4A2C 002F160C  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4A30 002F1610  38 80 04 4E */	li r4, 0x44e
/* 802F4A34 002F1614  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4A38 002F1618  48 09 37 E9 */	bl __assert
lbl_802F4A3C:
/* 802F4A3C 002F161C  C0 1E 00 38 */	lfs f0, 0x38(r30)
/* 802F4A40 002F1620  EC 00 E0 2A */	fadds f0, f0, f28
/* 802F4A44 002F1624  D0 1E 00 38 */	stfs f0, 0x38(r30)
/* 802F4A48 002F1628  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802F4A4C 002F162C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F4A50 002F1630  40 82 00 4C */	bne lbl_802F4A9C
/* 802F4A54 002F1634  28 1E 00 00 */	cmplwi r30, 0
/* 802F4A58 002F1638  41 82 00 44 */	beq lbl_802F4A9C
/* 802F4A5C 002F163C  40 82 00 14 */	bne lbl_802F4A70
/* 802F4A60 002F1640  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4A64 002F1644  38 80 02 34 */	li r4, 0x234
/* 802F4A68 002F1648  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4A6C 002F164C  48 09 37 B5 */	bl __assert
lbl_802F4A70:
/* 802F4A70 002F1650  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802F4A74 002F1654  38 60 00 00 */	li r3, 0
/* 802F4A78 002F1658  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F4A7C 002F165C  40 82 00 10 */	bne lbl_802F4A8C
/* 802F4A80 002F1660  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F4A84 002F1664  41 82 00 08 */	beq lbl_802F4A8C
/* 802F4A88 002F1668  38 60 00 01 */	li r3, 1
lbl_802F4A8C:
/* 802F4A8C 002F166C  2C 03 00 00 */	cmpwi r3, 0
/* 802F4A90 002F1670  40 82 00 0C */	bne lbl_802F4A9C
/* 802F4A94 002F1674  7F C3 F3 78 */	mr r3, r30
/* 802F4A98 002F1678  48 07 E8 51 */	bl HSD_JObjSetMtxDirtySub
lbl_802F4A9C:
/* 802F4A9C 002F167C  83 DD 00 54 */	lwz r30, 0x54(r29)
/* 802F4AA0 002F1680  28 1E 00 00 */	cmplwi r30, 0
/* 802F4AA4 002F1684  40 82 00 14 */	bne lbl_802F4AB8
/* 802F4AA8 002F1688  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4AAC 002F168C  38 80 03 EE */	li r4, 0x3ee
/* 802F4AB0 002F1690  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4AB4 002F1694  48 09 37 6D */	bl __assert
lbl_802F4AB8:
/* 802F4AB8 002F1698  C0 1E 00 3C */	lfs f0, 0x3c(r30)
/* 802F4ABC 002F169C  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 802F4AC0 002F16A0  40 81 00 90 */	ble lbl_802F4B50
/* 802F4AC4 002F16A4  83 DD 00 54 */	lwz r30, 0x54(r29)
/* 802F4AC8 002F16A8  C3 9D 00 44 */	lfs f28, 0x44(r29)
/* 802F4ACC 002F16AC  28 1E 00 00 */	cmplwi r30, 0
/* 802F4AD0 002F16B0  40 82 00 14 */	bne lbl_802F4AE4
/* 802F4AD4 002F16B4  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4AD8 002F16B8  38 80 04 5A */	li r4, 0x45a
/* 802F4ADC 002F16BC  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4AE0 002F16C0  48 09 37 41 */	bl __assert
lbl_802F4AE4:
/* 802F4AE4 002F16C4  C0 1E 00 3C */	lfs f0, 0x3c(r30)
/* 802F4AE8 002F16C8  EC 00 E0 2A */	fadds f0, f0, f28
/* 802F4AEC 002F16CC  D0 1E 00 3C */	stfs f0, 0x3c(r30)
/* 802F4AF0 002F16D0  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802F4AF4 002F16D4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F4AF8 002F16D8  40 82 00 4C */	bne lbl_802F4B44
/* 802F4AFC 002F16DC  28 1E 00 00 */	cmplwi r30, 0
/* 802F4B00 002F16E0  41 82 00 44 */	beq lbl_802F4B44
/* 802F4B04 002F16E4  40 82 00 14 */	bne lbl_802F4B18
/* 802F4B08 002F16E8  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4B0C 002F16EC  38 80 02 34 */	li r4, 0x234
/* 802F4B10 002F16F0  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4B14 002F16F4  48 09 37 0D */	bl __assert
lbl_802F4B18:
/* 802F4B18 002F16F8  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802F4B1C 002F16FC  38 60 00 00 */	li r3, 0
/* 802F4B20 002F1700  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F4B24 002F1704  40 82 00 10 */	bne lbl_802F4B34
/* 802F4B28 002F1708  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F4B2C 002F170C  41 82 00 08 */	beq lbl_802F4B34
/* 802F4B30 002F1710  38 60 00 01 */	li r3, 1
lbl_802F4B34:
/* 802F4B34 002F1714  2C 03 00 00 */	cmpwi r3, 0
/* 802F4B38 002F1718  40 82 00 0C */	bne lbl_802F4B44
/* 802F4B3C 002F171C  7F C3 F3 78 */	mr r3, r30
/* 802F4B40 002F1720  48 07 E7 A9 */	bl HSD_JObjSetMtxDirtySub
lbl_802F4B44:
/* 802F4B44 002F1724  C0 1D 00 44 */	lfs f0, 0x44(r29)
/* 802F4B48 002F1728  EC 00 F8 28 */	fsubs f0, f0, f31
/* 802F4B4C 002F172C  D0 1D 00 44 */	stfs f0, 0x44(r29)
lbl_802F4B50:
/* 802F4B50 002F1730  3B FF 00 01 */	addi r31, r31, 1
/* 802F4B54 002F1734  2C 1F 00 04 */	cmpwi r31, 4
/* 802F4B58 002F1738  3B BD 00 04 */	addi r29, r29, 4
/* 802F4B5C 002F173C  41 80 FE 84 */	blt lbl_802F49E0
lbl_802F4B60:
/* 802F4B60 002F1740  BB 61 00 3C */	lmw r27, 0x3c(r1)
/* 802F4B64 002F1744  80 01 00 74 */	lwz r0, 0x74(r1)
/* 802F4B68 002F1748  CB E1 00 68 */	lfd f31, 0x68(r1)
/* 802F4B6C 002F174C  CB C1 00 60 */	lfd f30, 0x60(r1)
/* 802F4B70 002F1750  CB A1 00 58 */	lfd f29, 0x58(r1)
/* 802F4B74 002F1754  CB 81 00 50 */	lfd f28, 0x50(r1)
/* 802F4B78 002F1758  38 21 00 70 */	addi r1, r1, 0x70
/* 802F4B7C 002F175C  7C 08 03 A6 */	mtlr r0
/* 802F4B80 002F1760  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif

extern f32 lbl_804DDA4C;

#pragma push
asm unk_t func_802F4B84()
{ // clang-format off
    nofralloc
/* 802F4B84 002F1764  7C 08 02 A6 */	mflr r0
/* 802F4B88 002F1768  90 01 00 04 */	stw r0, 4(r1)
/* 802F4B8C 002F176C  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 802F4B90 002F1770  DB E1 00 60 */	stfd f31, 0x60(r1)
/* 802F4B94 002F1774  DB C1 00 58 */	stfd f30, 0x58(r1)
/* 802F4B98 002F1778  DB A1 00 50 */	stfd f29, 0x50(r1)
/* 802F4B9C 002F177C  DB 81 00 48 */	stfd f28, 0x48(r1)
/* 802F4BA0 002F1780  DB 61 00 40 */	stfd f27, 0x40(r1)
/* 802F4BA4 002F1784  DB 41 00 38 */	stfd f26, 0x38(r1)
/* 802F4BA8 002F1788  DB 21 00 30 */	stfd f25, 0x30(r1)
/* 802F4BAC 002F178C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802F4BB0 002F1790  93 C1 00 28 */	stw r30, 0x28(r1)
/* 802F4BB4 002F1794  7C 7E 1B 78 */	mr r30, r3
/* 802F4BB8 002F1798  93 A1 00 24 */	stw r29, 0x24(r1)
/* 802F4BBC 002F179C  93 81 00 20 */	stw r28, 0x20(r1)
/* 802F4BC0 002F17A0  88 03 00 0F */	lbz r0, 0xf(r3)
/* 802F4BC4 002F17A4  28 00 00 00 */	cmplwi r0, 0
/* 802F4BC8 002F17A8  41 82 02 D8 */	beq lbl_802F4EA0
/* 802F4BCC 002F17AC  28 00 00 01 */	cmplwi r0, 1
/* 802F4BD0 002F17B0  40 82 01 18 */	bne lbl_802F4CE8
/* 802F4BD4 002F17B4  3B E0 00 00 */	li r31, 0
/* 802F4BD8 002F17B8  3B BE 00 00 */	addi r29, r30, 0
lbl_802F4BDC:
/* 802F4BDC 002F17BC  83 9D 00 54 */	lwz r28, 0x54(r29)
/* 802F4BE0 002F17C0  C3 9D 00 14 */	lfs f28, 0x14(r29)
/* 802F4BE4 002F17C4  28 1C 00 00 */	cmplwi r28, 0
/* 802F4BE8 002F17C8  40 82 00 14 */	bne lbl_802F4BFC
/* 802F4BEC 002F17CC  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4BF0 002F17D0  38 80 03 A4 */	li r4, 0x3a4
/* 802F4BF4 002F17D4  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4BF8 002F17D8  48 09 36 29 */	bl __assert
lbl_802F4BFC:
/* 802F4BFC 002F17DC  D3 9C 00 38 */	stfs f28, 0x38(r28)
/* 802F4C00 002F17E0  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 802F4C04 002F17E4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F4C08 002F17E8  40 82 00 4C */	bne lbl_802F4C54
/* 802F4C0C 002F17EC  28 1C 00 00 */	cmplwi r28, 0
/* 802F4C10 002F17F0  41 82 00 44 */	beq lbl_802F4C54
/* 802F4C14 002F17F4  40 82 00 14 */	bne lbl_802F4C28
/* 802F4C18 002F17F8  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4C1C 002F17FC  38 80 02 34 */	li r4, 0x234
/* 802F4C20 002F1800  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4C24 002F1804  48 09 35 FD */	bl __assert
lbl_802F4C28:
/* 802F4C28 002F1808  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 802F4C2C 002F180C  38 60 00 00 */	li r3, 0
/* 802F4C30 002F1810  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F4C34 002F1814  40 82 00 10 */	bne lbl_802F4C44
/* 802F4C38 002F1818  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F4C3C 002F181C  41 82 00 08 */	beq lbl_802F4C44
/* 802F4C40 002F1820  38 60 00 01 */	li r3, 1
lbl_802F4C44:
/* 802F4C44 002F1824  2C 03 00 00 */	cmpwi r3, 0
/* 802F4C48 002F1828  40 82 00 0C */	bne lbl_802F4C54
/* 802F4C4C 002F182C  7F 83 E3 78 */	mr r3, r28
/* 802F4C50 002F1830  48 07 E6 99 */	bl HSD_JObjSetMtxDirtySub
lbl_802F4C54:
/* 802F4C54 002F1834  83 9D 00 54 */	lwz r28, 0x54(r29)
/* 802F4C58 002F1838  C3 9D 00 24 */	lfs f28, 0x24(r29)
/* 802F4C5C 002F183C  28 1C 00 00 */	cmplwi r28, 0
/* 802F4C60 002F1840  40 82 00 14 */	bne lbl_802F4C74
/* 802F4C64 002F1844  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4C68 002F1848  38 80 03 B3 */	li r4, 0x3b3
/* 802F4C6C 002F184C  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4C70 002F1850  48 09 35 B1 */	bl __assert
lbl_802F4C74:
/* 802F4C74 002F1854  D3 9C 00 3C */	stfs f28, 0x3c(r28)
/* 802F4C78 002F1858  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 802F4C7C 002F185C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F4C80 002F1860  40 82 00 4C */	bne lbl_802F4CCC
/* 802F4C84 002F1864  28 1C 00 00 */	cmplwi r28, 0
/* 802F4C88 002F1868  41 82 00 44 */	beq lbl_802F4CCC
/* 802F4C8C 002F186C  40 82 00 14 */	bne lbl_802F4CA0
/* 802F4C90 002F1870  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4C94 002F1874  38 80 02 34 */	li r4, 0x234
/* 802F4C98 002F1878  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4C9C 002F187C  48 09 35 85 */	bl __assert
lbl_802F4CA0:
/* 802F4CA0 002F1880  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 802F4CA4 002F1884  38 60 00 00 */	li r3, 0
/* 802F4CA8 002F1888  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F4CAC 002F188C  40 82 00 10 */	bne lbl_802F4CBC
/* 802F4CB0 002F1890  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F4CB4 002F1894  41 82 00 08 */	beq lbl_802F4CBC
/* 802F4CB8 002F1898  38 60 00 01 */	li r3, 1
lbl_802F4CBC:
/* 802F4CBC 002F189C  2C 03 00 00 */	cmpwi r3, 0
/* 802F4CC0 002F18A0  40 82 00 0C */	bne lbl_802F4CCC
/* 802F4CC4 002F18A4  7F 83 E3 78 */	mr r3, r28
/* 802F4CC8 002F18A8  48 07 E6 21 */	bl HSD_JObjSetMtxDirtySub
lbl_802F4CCC:
/* 802F4CCC 002F18AC  3B FF 00 01 */	addi r31, r31, 1
/* 802F4CD0 002F18B0  2C 1F 00 04 */	cmpwi r31, 4
/* 802F4CD4 002F18B4  3B BD 00 04 */	addi r29, r29, 4
/* 802F4CD8 002F18B8  41 80 FF 04 */	blt lbl_802F4BDC
/* 802F4CDC 002F18BC  38 00 00 00 */	li r0, 0
/* 802F4CE0 002F18C0  98 1E 00 0F */	stb r0, 0xf(r30)
/* 802F4CE4 002F18C4  48 00 01 BC */	b lbl_802F4EA0
lbl_802F4CE8:
/* 802F4CE8 002F18C8  88 7E 00 0E */	lbz r3, 0xe(r30)
/* 802F4CEC 002F18CC  3C 00 43 30 */	lis r0, 0x4330
/* 802F4CF0 002F18D0  C8 22 E0 78 */	lfd f1, lbl_804DDA58(r2)
/* 802F4CF4 002F18D4  90 61 00 1C */	stw r3, 0x1c(r1)
/* 802F4CF8 002F18D8  C0 42 E0 A4 */	lfs f2, lbl_804DDA84(r2)
/* 802F4CFC 002F18DC  90 01 00 18 */	stw r0, 0x18(r1)
/* 802F4D00 002F18E0  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 802F4D04 002F18E4  EC 00 08 28 */	fsubs f0, f0, f1
/* 802F4D08 002F18E8  EF 42 00 32 */	fmuls f26, f2, f0
/* 802F4D0C 002F18EC  FC 1A 10 40 */	fcmpo cr0, f26, f2
/* 802F4D10 002F18F0  40 80 00 0C */	bge lbl_802F4D1C
/* 802F4D14 002F18F4  FF 40 10 90 */	fmr f26, f2
/* 802F4D18 002F18F8  48 00 00 14 */	b lbl_802F4D2C
lbl_802F4D1C:
/* 802F4D1C 002F18FC  C0 02 E0 A8 */	lfs f0, lbl_804DDA88(r2)
/* 802F4D20 002F1900  FC 1A 00 40 */	fcmpo cr0, f26, f0
/* 802F4D24 002F1904  40 81 00 08 */	ble lbl_802F4D2C
/* 802F4D28 002F1908  FF 40 00 90 */	fmr f26, f0
lbl_802F4D2C:
/* 802F4D2C 002F190C  C3 82 E0 B4 */	lfs f28, lbl_804DDA94(r2)
/* 802F4D30 002F1910  7F DD F3 78 */	mr r29, r30
/* 802F4D34 002F1914  C3 A2 E0 70 */	lfs f29, lbl_804DDA50(r2)
/* 802F4D38 002F1918  3B E0 00 00 */	li r31, 0
/* 802F4D3C 002F191C  C3 C2 E0 6C */	lfs f30, lbl_804DDA4C(r2)
/* 802F4D40 002F1920  C3 E2 E0 B0 */	lfs f31, lbl_804DDA90(r2)
lbl_802F4D44:
/* 802F4D44 002F1924  48 08 B7 E5 */	bl HSD_Randf
/* 802F4D48 002F1928  EC 01 E0 28 */	fsubs f0, f1, f28
/* 802F4D4C 002F192C  EC 1D 00 32 */	fmuls f0, f29, f0
/* 802F4D50 002F1930  EF 7A 00 32 */	fmuls f27, f26, f0
/* 802F4D54 002F1934  48 08 B7 D5 */	bl HSD_Randf
/* 802F4D58 002F1938  EC 01 E0 28 */	fsubs f0, f1, f28
/* 802F4D5C 002F193C  FC 1B F0 40 */	fcmpo cr0, f27, f30
/* 802F4D60 002F1940  EC 1D 00 32 */	fmuls f0, f29, f0
/* 802F4D64 002F1944  EF 3A 00 32 */	fmuls f25, f26, f0
/* 802F4D68 002F1948  40 80 00 0C */	bge lbl_802F4D74
/* 802F4D6C 002F194C  EC 3B F8 28 */	fsubs f1, f27, f31
/* 802F4D70 002F1950  48 00 00 08 */	b lbl_802F4D78
lbl_802F4D74:
/* 802F4D74 002F1954  EC 3B F8 2A */	fadds f1, f27, f31
lbl_802F4D78:
/* 802F4D78 002F1958  FC 19 F0 40 */	fcmpo cr0, f25, f30
/* 802F4D7C 002F195C  40 80 00 0C */	bge lbl_802F4D88
/* 802F4D80 002F1960  EF 39 F8 28 */	fsubs f25, f25, f31
/* 802F4D84 002F1964  48 00 00 08 */	b lbl_802F4D8C
lbl_802F4D88:
/* 802F4D88 002F1968  EF 39 F8 2A */	fadds f25, f25, f31
lbl_802F4D8C:
/* 802F4D8C 002F196C  83 9D 00 54 */	lwz r28, 0x54(r29)
/* 802F4D90 002F1970  C0 1D 00 14 */	lfs f0, 0x14(r29)
/* 802F4D94 002F1974  28 1C 00 00 */	cmplwi r28, 0
/* 802F4D98 002F1978  EF 60 08 2A */	fadds f27, f0, f1
/* 802F4D9C 002F197C  40 82 00 14 */	bne lbl_802F4DB0
/* 802F4DA0 002F1980  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4DA4 002F1984  38 80 03 A4 */	li r4, 0x3a4
/* 802F4DA8 002F1988  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4DAC 002F198C  48 09 34 75 */	bl __assert
lbl_802F4DB0:
/* 802F4DB0 002F1990  D3 7C 00 38 */	stfs f27, 0x38(r28)
/* 802F4DB4 002F1994  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 802F4DB8 002F1998  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F4DBC 002F199C  40 82 00 4C */	bne lbl_802F4E08
/* 802F4DC0 002F19A0  28 1C 00 00 */	cmplwi r28, 0
/* 802F4DC4 002F19A4  41 82 00 44 */	beq lbl_802F4E08
/* 802F4DC8 002F19A8  40 82 00 14 */	bne lbl_802F4DDC
/* 802F4DCC 002F19AC  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4DD0 002F19B0  38 80 02 34 */	li r4, 0x234
/* 802F4DD4 002F19B4  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4DD8 002F19B8  48 09 34 49 */	bl __assert
lbl_802F4DDC:
/* 802F4DDC 002F19BC  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 802F4DE0 002F19C0  38 60 00 00 */	li r3, 0
/* 802F4DE4 002F19C4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F4DE8 002F19C8  40 82 00 10 */	bne lbl_802F4DF8
/* 802F4DEC 002F19CC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F4DF0 002F19D0  41 82 00 08 */	beq lbl_802F4DF8
/* 802F4DF4 002F19D4  38 60 00 01 */	li r3, 1
lbl_802F4DF8:
/* 802F4DF8 002F19D8  2C 03 00 00 */	cmpwi r3, 0
/* 802F4DFC 002F19DC  40 82 00 0C */	bne lbl_802F4E08
/* 802F4E00 002F19E0  7F 83 E3 78 */	mr r3, r28
/* 802F4E04 002F19E4  48 07 E4 E5 */	bl HSD_JObjSetMtxDirtySub
lbl_802F4E08:
/* 802F4E08 002F19E8  83 9D 00 54 */	lwz r28, 0x54(r29)
/* 802F4E0C 002F19EC  C0 1D 00 24 */	lfs f0, 0x24(r29)
/* 802F4E10 002F19F0  28 1C 00 00 */	cmplwi r28, 0
/* 802F4E14 002F19F4  EF 60 C8 2A */	fadds f27, f0, f25
/* 802F4E18 002F19F8  40 82 00 14 */	bne lbl_802F4E2C
/* 802F4E1C 002F19FC  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4E20 002F1A00  38 80 03 B3 */	li r4, 0x3b3
/* 802F4E24 002F1A04  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4E28 002F1A08  48 09 33 F9 */	bl __assert
lbl_802F4E2C:
/* 802F4E2C 002F1A0C  D3 7C 00 3C */	stfs f27, 0x3c(r28)
/* 802F4E30 002F1A10  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 802F4E34 002F1A14  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F4E38 002F1A18  40 82 00 4C */	bne lbl_802F4E84
/* 802F4E3C 002F1A1C  28 1C 00 00 */	cmplwi r28, 0
/* 802F4E40 002F1A20  41 82 00 44 */	beq lbl_802F4E84
/* 802F4E44 002F1A24  40 82 00 14 */	bne lbl_802F4E58
/* 802F4E48 002F1A28  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F4E4C 002F1A2C  38 80 02 34 */	li r4, 0x234
/* 802F4E50 002F1A30  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F4E54 002F1A34  48 09 33 CD */	bl __assert
lbl_802F4E58:
/* 802F4E58 002F1A38  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 802F4E5C 002F1A3C  38 60 00 00 */	li r3, 0
/* 802F4E60 002F1A40  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F4E64 002F1A44  40 82 00 10 */	bne lbl_802F4E74
/* 802F4E68 002F1A48  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F4E6C 002F1A4C  41 82 00 08 */	beq lbl_802F4E74
/* 802F4E70 002F1A50  38 60 00 01 */	li r3, 1
lbl_802F4E74:
/* 802F4E74 002F1A54  2C 03 00 00 */	cmpwi r3, 0
/* 802F4E78 002F1A58  40 82 00 0C */	bne lbl_802F4E84
/* 802F4E7C 002F1A5C  7F 83 E3 78 */	mr r3, r28
/* 802F4E80 002F1A60  48 07 E4 69 */	bl HSD_JObjSetMtxDirtySub
lbl_802F4E84:
/* 802F4E84 002F1A64  3B FF 00 01 */	addi r31, r31, 1
/* 802F4E88 002F1A68  2C 1F 00 04 */	cmpwi r31, 4
/* 802F4E8C 002F1A6C  3B BD 00 04 */	addi r29, r29, 4
/* 802F4E90 002F1A70  41 80 FE B4 */	blt lbl_802F4D44
/* 802F4E94 002F1A74  88 7E 00 0F */	lbz r3, 0xf(r30)
/* 802F4E98 002F1A78  38 03 FF FF */	addi r0, r3, -1
/* 802F4E9C 002F1A7C  98 1E 00 0F */	stb r0, 0xf(r30)
lbl_802F4EA0:
/* 802F4EA0 002F1A80  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 802F4EA4 002F1A84  CB E1 00 60 */	lfd f31, 0x60(r1)
/* 802F4EA8 002F1A88  CB C1 00 58 */	lfd f30, 0x58(r1)
/* 802F4EAC 002F1A8C  CB A1 00 50 */	lfd f29, 0x50(r1)
/* 802F4EB0 002F1A90  CB 81 00 48 */	lfd f28, 0x48(r1)
/* 802F4EB4 002F1A94  CB 61 00 40 */	lfd f27, 0x40(r1)
/* 802F4EB8 002F1A98  CB 41 00 38 */	lfd f26, 0x38(r1)
/* 802F4EBC 002F1A9C  CB 21 00 30 */	lfd f25, 0x30(r1)
/* 802F4EC0 002F1AA0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802F4EC4 002F1AA4  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 802F4EC8 002F1AA8  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 802F4ECC 002F1AAC  83 81 00 20 */	lwz r28, 0x20(r1)
/* 802F4ED0 002F1AB0  38 21 00 68 */	addi r1, r1, 0x68
/* 802F4ED4 002F1AB4  7C 08 03 A6 */	mtlr r0
/* 802F4ED8 002F1AB8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern s32 lbl_804D57A8;
extern unk_t lbl_804D57AC;
extern f64 lbl_804DDA60;
extern f32 lbl_804DDA68;
extern f32 lbl_804DDA6C;
extern f32 lbl_804DDA70;
extern s8 lbl_804D6D60;
extern f32 lbl_804DDA98;
extern unk_t func_8022F3D8();
extern unk_t HSD_JObjRemoveAnim();

#pragma push
asm unk_t func_802F4EDC()
{ // clang-format off
    nofralloc
/* 802F4EDC 002F1ABC  7C 08 02 A6 */	mflr r0
/* 802F4EE0 002F1AC0  3C 80 80 4A */	lis r4, lbl_804A10C8@ha
/* 802F4EE4 002F1AC4  90 01 00 04 */	stw r0, 4(r1)
/* 802F4EE8 002F1AC8  38 00 00 06 */	li r0, 6
/* 802F4EEC 002F1ACC  7C 09 03 A6 */	mtctr r0
/* 802F4EF0 002F1AD0  94 21 FF 08 */	stwu r1, -0xf8(r1)
/* 802F4EF4 002F1AD4  DB E1 00 F0 */	stfd f31, 0xf0(r1)
/* 802F4EF8 002F1AD8  DB C1 00 E8 */	stfd f30, 0xe8(r1)
/* 802F4EFC 002F1ADC  DB A1 00 E0 */	stfd f29, 0xe0(r1)
/* 802F4F00 002F1AE0  BE E1 00 BC */	stmw r23, 0xbc(r1)
/* 802F4F04 002F1AE4  3B 24 10 C8 */	addi r25, r4, lbl_804A10C8@l
/* 802F4F08 002F1AE8  38 B9 00 00 */	addi r5, r25, 0
/* 802F4F0C 002F1AEC  38 80 00 00 */	li r4, 0
/* 802F4F10 002F1AF0  83 C3 00 28 */	lwz r30, 0x28(r3)
lbl_802F4F14:
/* 802F4F14 002F1AF4  80 05 00 00 */	lwz r0, 0(r5)
/* 802F4F18 002F1AF8  7C 00 18 40 */	cmplw r0, r3
/* 802F4F1C 002F1AFC  40 82 00 10 */	bne lbl_802F4F2C
/* 802F4F20 002F1B00  1C 04 00 64 */	mulli r0, r4, 0x64
/* 802F4F24 002F1B04  7F F9 02 14 */	add r31, r25, r0
/* 802F4F28 002F1B08  48 00 00 14 */	b lbl_802F4F3C
lbl_802F4F2C:
/* 802F4F2C 002F1B0C  38 A5 00 64 */	addi r5, r5, 0x64
/* 802F4F30 002F1B10  38 84 00 01 */	addi r4, r4, 1
/* 802F4F34 002F1B14  42 00 FF E0 */	bdnz lbl_802F4F14
/* 802F4F38 002F1B18  3B E0 00 00 */	li r31, 0
lbl_802F4F3C:
/* 802F4F3C 002F1B1C  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F4F40 002F1B20  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 802F4F44 002F1B24  41 82 00 10 */	beq lbl_802F4F54
/* 802F4F48 002F1B28  7F E3 FB 78 */	mr r3, r31
/* 802F4F4C 002F1B2C  4B FF F9 D1 */	bl func_802F491C
/* 802F4F50 002F1B30  48 00 0B D8 */	b lbl_802F5B28
lbl_802F4F54:
/* 802F4F54 002F1B34  7F C3 F3 78 */	mr r3, r30
/* 802F4F58 002F1B38  4B D1 61 45 */	bl func_8000B09C
/* 802F4F5C 002F1B3C  88 9F 00 10 */	lbz r4, 0x10(r31)
/* 802F4F60 002F1B40  3B A3 00 00 */	addi r29, r3, 0
/* 802F4F64 002F1B44  54 80 E7 FF */	rlwinm. r0, r4, 0x1c, 0x1f, 0x1f
/* 802F4F68 002F1B48  41 82 02 CC */	beq lbl_802F5234
/* 802F4F6C 002F1B4C  54 80 FF BE */	rlwinm r0, r4, 0x1f, 0x1e, 0x1f
/* 802F4F70 002F1B50  28 00 00 01 */	cmplwi r0, 1
/* 802F4F74 002F1B54  40 82 00 0C */	bne lbl_802F4F80
/* 802F4F78 002F1B58  2C 1D 00 00 */	cmpwi r29, 0
/* 802F4F7C 002F1B5C  40 82 02 B8 */	bne lbl_802F5234
lbl_802F4F80:
/* 802F4F80 002F1B60  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F4F84 002F1B64  38 60 00 01 */	li r3, 1
/* 802F4F88 002F1B68  50 60 0F 7C */	rlwimi r0, r3, 1, 0x1d, 0x1e
/* 802F4F8C 002F1B6C  98 1F 00 10 */	stb r0, 0x10(r31)
/* 802F4F90 002F1B70  7F C3 F3 78 */	mr r3, r30
/* 802F4F94 002F1B74  48 07 A6 B1 */	bl HSD_JObjRemoveAnim
/* 802F4F98 002F1B78  3A F9 02 60 */	addi r23, r25, 0x260
/* 802F4F9C 002F1B7C  80 B9 02 5C */	lwz r5, 0x25c(r25)
/* 802F4FA0 002F1B80  80 D9 02 60 */	lwz r6, 0x260(r25)
/* 802F4FA4 002F1B84  7F C3 F3 78 */	mr r3, r30
/* 802F4FA8 002F1B88  80 F9 02 64 */	lwz r7, 0x264(r25)
/* 802F4FAC 002F1B8C  38 80 00 01 */	li r4, 1
/* 802F4FB0 002F1B90  4B D1 70 CD */	bl func_8000C07C
/* 802F4FB4 002F1B94  7F C3 F3 78 */	mr r3, r30
/* 802F4FB8 002F1B98  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F4FBC 002F1B9C  48 07 A9 01 */	bl HSD_JObjReqAnimAll
/* 802F4FC0 002F1BA0  80 9F 00 60 */	lwz r4, 0x60(r31)
/* 802F4FC4 002F1BA4  28 04 00 00 */	cmplwi r4, 0
/* 802F4FC8 002F1BA8  41 82 00 7C */	beq lbl_802F5044
/* 802F4FCC 002F1BAC  80 77 00 00 */	lwz r3, 0(r23)
/* 802F4FD0 002F1BB0  80 84 00 18 */	lwz r4, 0x18(r4)
/* 802F4FD4 002F1BB4  80 63 00 00 */	lwz r3, 0(r3)
/* 802F4FD8 002F1BB8  80 84 00 08 */	lwz r4, 8(r4)
/* 802F4FDC 002F1BBC  80 63 00 00 */	lwz r3, 0(r3)
/* 802F4FE0 002F1BC0  83 04 00 08 */	lwz r24, 8(r4)
/* 802F4FE4 002F1BC4  80 83 00 04 */	lwz r4, 4(r3)
/* 802F4FE8 002F1BC8  7F 03 C3 78 */	mr r3, r24
/* 802F4FEC 002F1BCC  80 84 00 04 */	lwz r4, 4(r4)
/* 802F4FF0 002F1BD0  80 84 00 04 */	lwz r4, 4(r4)
/* 802F4FF4 002F1BD4  80 84 00 08 */	lwz r4, 8(r4)
/* 802F4FF8 002F1BD8  80 84 00 08 */	lwz r4, 8(r4)
/* 802F4FFC 002F1BDC  48 06 97 0D */	bl HSD_TObjAddAnimAll
/* 802F5000 002F1BE0  88 7F 00 08 */	lbz r3, 8(r31)
/* 802F5004 002F1BE4  7C 63 07 74 */	extsb r3, r3
/* 802F5008 002F1BE8  4B D3 F6 2D */	bl Player_GetMoreFlagsBit2
/* 802F500C 002F1BEC  2C 03 00 00 */	cmpwi r3, 0
/* 802F5010 002F1BF0  41 82 00 14 */	beq lbl_802F5024
/* 802F5014 002F1BF4  7F 03 C3 78 */	mr r3, r24
/* 802F5018 002F1BF8  C0 22 E0 68 */	lfs f1, lbl_804DDA48(r2)
/* 802F501C 002F1BFC  48 06 97 E5 */	bl HSD_TObjReqAnimAll
/* 802F5020 002F1C00  48 00 00 10 */	b lbl_802F5030
lbl_802F5024:
/* 802F5024 002F1C04  7F 03 C3 78 */	mr r3, r24
/* 802F5028 002F1C08  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F502C 002F1C0C  48 06 97 D5 */	bl HSD_TObjReqAnimAll
lbl_802F5030:
/* 802F5030 002F1C10  80 78 00 64 */	lwz r3, 0x64(r24)
/* 802F5034 002F1C14  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F5038 002F1C18  48 07 02 D5 */	bl HSD_AObjSetRate
/* 802F503C 002F1C1C  7F 03 C3 78 */	mr r3, r24
/* 802F5040 002F1C20  48 06 9B 2D */	bl HSD_TObjAnim
lbl_802F5044:
/* 802F5044 002F1C24  38 7E 00 00 */	addi r3, r30, 0
/* 802F5048 002F1C28  38 80 00 01 */	li r4, 1
/* 802F504C 002F1C2C  38 A0 04 00 */	li r5, 0x400
/* 802F5050 002F1C30  4B F3 A3 89 */	bl func_8022F3D8
/* 802F5054 002F1C34  3C 60 66 66 */	lis r3, 0x66666667@ha
/* 802F5058 002F1C38  A8 FF 00 0A */	lha r7, 0xa(r31)
/* 802F505C 002F1C3C  3B 83 66 67 */	addi r28, r3, 0x66666667@l
/* 802F5060 002F1C40  80 77 00 00 */	lwz r3, 0(r23)
/* 802F5064 002F1C44  7C 1C 38 96 */	mulhw r0, r28, r7
/* 802F5068 002F1C48  83 5F 00 5C */	lwz r26, 0x5c(r31)
/* 802F506C 002F1C4C  80 63 00 00 */	lwz r3, 0(r3)
/* 802F5070 002F1C50  80 9A 00 18 */	lwz r4, 0x18(r26)
/* 802F5074 002F1C54  80 63 00 00 */	lwz r3, 0(r3)
/* 802F5078 002F1C58  7C 00 16 70 */	srawi r0, r0, 2
/* 802F507C 002F1C5C  80 A4 00 08 */	lwz r5, 8(r4)
/* 802F5080 002F1C60  54 06 0F FE */	srwi r6, r0, 0x1f
/* 802F5084 002F1C64  80 83 00 08 */	lwz r4, 8(r3)
/* 802F5088 002F1C68  7C 00 32 14 */	add r0, r0, r6
/* 802F508C 002F1C6C  80 65 00 08 */	lwz r3, 8(r5)
/* 802F5090 002F1C70  1C 00 00 0A */	mulli r0, r0, 0xa
/* 802F5094 002F1C74  80 84 00 08 */	lwz r4, 8(r4)
/* 802F5098 002F1C78  7C 00 38 50 */	subf r0, r0, r7
/* 802F509C 002F1C7C  54 18 06 3E */	clrlwi r24, r0, 0x18
/* 802F50A0 002F1C80  48 06 96 69 */	bl HSD_TObjAddAnimAll
/* 802F50A4 002F1C84  93 01 00 B4 */	stw r24, 0xb4(r1)
/* 802F50A8 002F1C88  3F 60 43 30 */	lis r27, 0x4330
/* 802F50AC 002F1C8C  80 7A 00 18 */	lwz r3, 0x18(r26)
/* 802F50B0 002F1C90  93 61 00 B0 */	stw r27, 0xb0(r1)
/* 802F50B4 002F1C94  80 63 00 08 */	lwz r3, 8(r3)
/* 802F50B8 002F1C98  C8 22 E0 78 */	lfd f1, lbl_804DDA58(r2)
/* 802F50BC 002F1C9C  C8 01 00 B0 */	lfd f0, 0xb0(r1)
/* 802F50C0 002F1CA0  C0 42 E0 70 */	lfs f2, lbl_804DDA50(r2)
/* 802F50C4 002F1CA4  EC 00 08 28 */	fsubs f0, f0, f1
/* 802F50C8 002F1CA8  80 63 00 08 */	lwz r3, 8(r3)
/* 802F50CC 002F1CAC  EC 22 00 32 */	fmuls f1, f2, f0
/* 802F50D0 002F1CB0  48 06 97 31 */	bl HSD_TObjReqAnimAll
/* 802F50D4 002F1CB4  80 7A 00 18 */	lwz r3, 0x18(r26)
/* 802F50D8 002F1CB8  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F50DC 002F1CBC  80 63 00 08 */	lwz r3, 8(r3)
/* 802F50E0 002F1CC0  80 63 00 08 */	lwz r3, 8(r3)
/* 802F50E4 002F1CC4  80 63 00 64 */	lwz r3, 0x64(r3)
/* 802F50E8 002F1CC8  48 07 02 25 */	bl HSD_AObjSetRate
/* 802F50EC 002F1CCC  3C 60 51 EC */	lis r3, 0x51EB851F@ha
/* 802F50F0 002F1CD0  A8 FF 00 0A */	lha r7, 0xa(r31)
/* 802F50F4 002F1CD4  3B 43 85 1F */	addi r26, r3, 0x51EB851F@l
/* 802F50F8 002F1CD8  80 77 00 00 */	lwz r3, 0(r23)
/* 802F50FC 002F1CDC  7C 1A 38 96 */	mulhw r0, r26, r7
/* 802F5100 002F1CE0  83 1F 00 58 */	lwz r24, 0x58(r31)
/* 802F5104 002F1CE4  80 63 00 00 */	lwz r3, 0(r3)
/* 802F5108 002F1CE8  80 98 00 18 */	lwz r4, 0x18(r24)
/* 802F510C 002F1CEC  80 63 00 00 */	lwz r3, 0(r3)
/* 802F5110 002F1CF0  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F5114 002F1CF4  80 A4 00 08 */	lwz r5, 8(r4)
/* 802F5118 002F1CF8  54 06 0F FE */	srwi r6, r0, 0x1f
/* 802F511C 002F1CFC  80 83 00 08 */	lwz r4, 8(r3)
/* 802F5120 002F1D00  7C 00 32 14 */	add r0, r0, r6
/* 802F5124 002F1D04  80 65 00 08 */	lwz r3, 8(r5)
/* 802F5128 002F1D08  1C 00 00 64 */	mulli r0, r0, 0x64
/* 802F512C 002F1D0C  80 84 00 08 */	lwz r4, 8(r4)
/* 802F5130 002F1D10  7C 00 38 50 */	subf r0, r0, r7
/* 802F5134 002F1D14  7C 1C 00 96 */	mulhw r0, r28, r0
/* 802F5138 002F1D18  7C 00 16 70 */	srawi r0, r0, 2
/* 802F513C 002F1D1C  54 05 0F FE */	srwi r5, r0, 0x1f
/* 802F5140 002F1D20  7C 00 2A 14 */	add r0, r0, r5
/* 802F5144 002F1D24  54 1C 06 3E */	clrlwi r28, r0, 0x18
/* 802F5148 002F1D28  48 06 95 C1 */	bl HSD_TObjAddAnimAll
/* 802F514C 002F1D2C  93 81 00 AC */	stw r28, 0xac(r1)
/* 802F5150 002F1D30  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F5154 002F1D34  93 61 00 A8 */	stw r27, 0xa8(r1)
/* 802F5158 002F1D38  80 63 00 08 */	lwz r3, 8(r3)
/* 802F515C 002F1D3C  C8 22 E0 78 */	lfd f1, lbl_804DDA58(r2)
/* 802F5160 002F1D40  C8 01 00 A8 */	lfd f0, 0xa8(r1)
/* 802F5164 002F1D44  C0 42 E0 70 */	lfs f2, lbl_804DDA50(r2)
/* 802F5168 002F1D48  EC 00 08 28 */	fsubs f0, f0, f1
/* 802F516C 002F1D4C  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5170 002F1D50  EC 22 00 32 */	fmuls f1, f2, f0
/* 802F5174 002F1D54  48 06 96 8D */	bl HSD_TObjReqAnimAll
/* 802F5178 002F1D58  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F517C 002F1D5C  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F5180 002F1D60  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5184 002F1D64  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5188 002F1D68  80 63 00 64 */	lwz r3, 0x64(r3)
/* 802F518C 002F1D6C  48 07 01 81 */	bl HSD_AObjSetRate
/* 802F5190 002F1D70  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 802F5194 002F1D74  A8 FF 00 0A */	lha r7, 0xa(r31)
/* 802F5198 002F1D78  38 03 4D D3 */	addi r0, r3, 0x10624DD3@l
/* 802F519C 002F1D7C  80 77 00 00 */	lwz r3, 0(r23)
/* 802F51A0 002F1D80  7C 00 38 96 */	mulhw r0, r0, r7
/* 802F51A4 002F1D84  83 1F 00 54 */	lwz r24, 0x54(r31)
/* 802F51A8 002F1D88  80 63 00 00 */	lwz r3, 0(r3)
/* 802F51AC 002F1D8C  80 98 00 18 */	lwz r4, 0x18(r24)
/* 802F51B0 002F1D90  80 63 00 00 */	lwz r3, 0(r3)
/* 802F51B4 002F1D94  7C 00 36 70 */	srawi r0, r0, 6
/* 802F51B8 002F1D98  80 A4 00 08 */	lwz r5, 8(r4)
/* 802F51BC 002F1D9C  54 06 0F FE */	srwi r6, r0, 0x1f
/* 802F51C0 002F1DA0  80 83 00 08 */	lwz r4, 8(r3)
/* 802F51C4 002F1DA4  7C 00 32 14 */	add r0, r0, r6
/* 802F51C8 002F1DA8  80 65 00 08 */	lwz r3, 8(r5)
/* 802F51CC 002F1DAC  1C 00 03 E8 */	mulli r0, r0, 0x3e8
/* 802F51D0 002F1DB0  80 84 00 08 */	lwz r4, 8(r4)
/* 802F51D4 002F1DB4  7C 00 38 50 */	subf r0, r0, r7
/* 802F51D8 002F1DB8  7C 1A 00 96 */	mulhw r0, r26, r0
/* 802F51DC 002F1DBC  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F51E0 002F1DC0  54 05 0F FE */	srwi r5, r0, 0x1f
/* 802F51E4 002F1DC4  7C 00 2A 14 */	add r0, r0, r5
/* 802F51E8 002F1DC8  54 17 06 3E */	clrlwi r23, r0, 0x18
/* 802F51EC 002F1DCC  48 06 95 1D */	bl HSD_TObjAddAnimAll
/* 802F51F0 002F1DD0  92 E1 00 A4 */	stw r23, 0xa4(r1)
/* 802F51F4 002F1DD4  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F51F8 002F1DD8  93 61 00 A0 */	stw r27, 0xa0(r1)
/* 802F51FC 002F1DDC  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5200 002F1DE0  C8 22 E0 78 */	lfd f1, lbl_804DDA58(r2)
/* 802F5204 002F1DE4  C8 01 00 A0 */	lfd f0, 0xa0(r1)
/* 802F5208 002F1DE8  C0 42 E0 70 */	lfs f2, lbl_804DDA50(r2)
/* 802F520C 002F1DEC  EC 00 08 28 */	fsubs f0, f0, f1
/* 802F5210 002F1DF0  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5214 002F1DF4  EC 22 00 32 */	fmuls f1, f2, f0
/* 802F5218 002F1DF8  48 06 95 E9 */	bl HSD_TObjReqAnimAll
/* 802F521C 002F1DFC  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F5220 002F1E00  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F5224 002F1E04  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5228 002F1E08  80 63 00 08 */	lwz r3, 8(r3)
/* 802F522C 002F1E0C  80 63 00 64 */	lwz r3, 0x64(r3)
/* 802F5230 002F1E10  48 07 00 DD */	bl HSD_AObjSetRate
lbl_802F5234:
/* 802F5234 002F1E14  7F C3 F3 78 */	mr r3, r30
/* 802F5238 002F1E18  48 07 B6 F1 */	bl HSD_JObjAnimAll
/* 802F523C 002F1E1C  3C 60 66 66 */	lis r3, 0x66666667@ha
/* 802F5240 002F1E20  A8 DF 00 0A */	lha r6, 0xa(r31)
/* 802F5244 002F1E24  3B 43 66 67 */	addi r26, r3, 0x66666667@l
/* 802F5248 002F1E28  83 1F 00 5C */	lwz r24, 0x5c(r31)
/* 802F524C 002F1E2C  7C 1A 30 96 */	mulhw r0, r26, r6
/* 802F5250 002F1E30  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F5254 002F1E34  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5258 002F1E38  3A F9 02 60 */	addi r23, r25, 0x260
/* 802F525C 002F1E3C  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5260 002F1E40  80 99 02 60 */	lwz r4, 0x260(r25)
/* 802F5264 002F1E44  7C 00 16 70 */	srawi r0, r0, 2
/* 802F5268 002F1E48  54 05 0F FE */	srwi r5, r0, 0x1f
/* 802F526C 002F1E4C  80 84 00 00 */	lwz r4, 0(r4)
/* 802F5270 002F1E50  7C 00 2A 14 */	add r0, r0, r5
/* 802F5274 002F1E54  1C 00 00 0A */	mulli r0, r0, 0xa
/* 802F5278 002F1E58  80 84 00 00 */	lwz r4, 0(r4)
/* 802F527C 002F1E5C  80 84 00 08 */	lwz r4, 8(r4)
/* 802F5280 002F1E60  7C 00 30 50 */	subf r0, r0, r6
/* 802F5284 002F1E64  54 19 06 3E */	clrlwi r25, r0, 0x18
/* 802F5288 002F1E68  80 84 00 08 */	lwz r4, 8(r4)
/* 802F528C 002F1E6C  48 06 94 7D */	bl HSD_TObjAddAnimAll
/* 802F5290 002F1E70  93 21 00 A4 */	stw r25, 0xa4(r1)
/* 802F5294 002F1E74  3F 80 43 30 */	lis r28, 0x4330
/* 802F5298 002F1E78  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F529C 002F1E7C  93 81 00 A0 */	stw r28, 0xa0(r1)
/* 802F52A0 002F1E80  80 63 00 08 */	lwz r3, 8(r3)
/* 802F52A4 002F1E84  C8 22 E0 78 */	lfd f1, lbl_804DDA58(r2)
/* 802F52A8 002F1E88  C8 01 00 A0 */	lfd f0, 0xa0(r1)
/* 802F52AC 002F1E8C  C0 42 E0 70 */	lfs f2, lbl_804DDA50(r2)
/* 802F52B0 002F1E90  EC 00 08 28 */	fsubs f0, f0, f1
/* 802F52B4 002F1E94  80 63 00 08 */	lwz r3, 8(r3)
/* 802F52B8 002F1E98  EC 22 00 32 */	fmuls f1, f2, f0
/* 802F52BC 002F1E9C  48 06 95 45 */	bl HSD_TObjReqAnimAll
/* 802F52C0 002F1EA0  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F52C4 002F1EA4  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F52C8 002F1EA8  80 63 00 08 */	lwz r3, 8(r3)
/* 802F52CC 002F1EAC  80 63 00 08 */	lwz r3, 8(r3)
/* 802F52D0 002F1EB0  80 63 00 64 */	lwz r3, 0x64(r3)
/* 802F52D4 002F1EB4  48 07 00 39 */	bl HSD_AObjSetRate
/* 802F52D8 002F1EB8  3C 60 51 EC */	lis r3, 0x51EB851F@ha
/* 802F52DC 002F1EBC  A8 FF 00 0A */	lha r7, 0xa(r31)
/* 802F52E0 002F1EC0  3B 63 85 1F */	addi r27, r3, 0x51EB851F@l
/* 802F52E4 002F1EC4  80 77 00 00 */	lwz r3, 0(r23)
/* 802F52E8 002F1EC8  7C 1B 38 96 */	mulhw r0, r27, r7
/* 802F52EC 002F1ECC  83 1F 00 58 */	lwz r24, 0x58(r31)
/* 802F52F0 002F1ED0  80 63 00 00 */	lwz r3, 0(r3)
/* 802F52F4 002F1ED4  80 98 00 18 */	lwz r4, 0x18(r24)
/* 802F52F8 002F1ED8  80 63 00 00 */	lwz r3, 0(r3)
/* 802F52FC 002F1EDC  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F5300 002F1EE0  80 A4 00 08 */	lwz r5, 8(r4)
/* 802F5304 002F1EE4  54 06 0F FE */	srwi r6, r0, 0x1f
/* 802F5308 002F1EE8  80 83 00 08 */	lwz r4, 8(r3)
/* 802F530C 002F1EEC  7C 00 32 14 */	add r0, r0, r6
/* 802F5310 002F1EF0  80 65 00 08 */	lwz r3, 8(r5)
/* 802F5314 002F1EF4  1C 00 00 64 */	mulli r0, r0, 0x64
/* 802F5318 002F1EF8  80 84 00 08 */	lwz r4, 8(r4)
/* 802F531C 002F1EFC  7C 00 38 50 */	subf r0, r0, r7
/* 802F5320 002F1F00  7C 1A 00 96 */	mulhw r0, r26, r0
/* 802F5324 002F1F04  7C 00 16 70 */	srawi r0, r0, 2
/* 802F5328 002F1F08  54 05 0F FE */	srwi r5, r0, 0x1f
/* 802F532C 002F1F0C  7C 00 2A 14 */	add r0, r0, r5
/* 802F5330 002F1F10  54 19 06 3E */	clrlwi r25, r0, 0x18
/* 802F5334 002F1F14  48 06 93 D5 */	bl HSD_TObjAddAnimAll
/* 802F5338 002F1F18  93 21 00 AC */	stw r25, 0xac(r1)
/* 802F533C 002F1F1C  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F5340 002F1F20  93 81 00 A8 */	stw r28, 0xa8(r1)
/* 802F5344 002F1F24  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5348 002F1F28  C8 22 E0 78 */	lfd f1, lbl_804DDA58(r2)
/* 802F534C 002F1F2C  C8 01 00 A8 */	lfd f0, 0xa8(r1)
/* 802F5350 002F1F30  C0 42 E0 70 */	lfs f2, lbl_804DDA50(r2)
/* 802F5354 002F1F34  EC 00 08 28 */	fsubs f0, f0, f1
/* 802F5358 002F1F38  80 63 00 08 */	lwz r3, 8(r3)
/* 802F535C 002F1F3C  EC 22 00 32 */	fmuls f1, f2, f0
/* 802F5360 002F1F40  48 06 94 A1 */	bl HSD_TObjReqAnimAll
/* 802F5364 002F1F44  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F5368 002F1F48  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F536C 002F1F4C  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5370 002F1F50  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5374 002F1F54  80 63 00 64 */	lwz r3, 0x64(r3)
/* 802F5378 002F1F58  48 06 FF 95 */	bl HSD_AObjSetRate
/* 802F537C 002F1F5C  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 802F5380 002F1F60  A8 9F 00 0A */	lha r4, 0xa(r31)
/* 802F5384 002F1F64  38 03 4D D3 */	addi r0, r3, 0x10624DD3@l
/* 802F5388 002F1F68  7C 00 20 96 */	mulhw r0, r0, r4
/* 802F538C 002F1F6C  7C 00 36 70 */	srawi r0, r0, 6
/* 802F5390 002F1F70  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F5394 002F1F74  7C 00 1A 14 */	add r0, r0, r3
/* 802F5398 002F1F78  1C 00 03 E8 */	mulli r0, r0, 0x3e8
/* 802F539C 002F1F7C  7C 00 20 50 */	subf r0, r0, r4
/* 802F53A0 002F1F80  7C 1B 00 96 */	mulhw r0, r27, r0
/* 802F53A4 002F1F84  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F53A8 002F1F88  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F53AC 002F1F8C  7C 00 1A 15 */	add. r0, r0, r3
/* 802F53B0 002F1F90  40 82 00 40 */	bne lbl_802F53F0
/* 802F53B4 002F1F94  7C 1B 20 96 */	mulhw r0, r27, r4
/* 802F53B8 002F1F98  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F53BC 002F1F9C  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F53C0 002F1FA0  7C 00 1A 14 */	add r0, r0, r3
/* 802F53C4 002F1FA4  1C 00 00 64 */	mulli r0, r0, 0x64
/* 802F53C8 002F1FA8  7C 00 20 50 */	subf r0, r0, r4
/* 802F53CC 002F1FAC  7C 1A 00 96 */	mulhw r0, r26, r0
/* 802F53D0 002F1FB0  7C 00 16 70 */	srawi r0, r0, 2
/* 802F53D4 002F1FB4  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F53D8 002F1FB8  7C 00 1A 15 */	add. r0, r0, r3
/* 802F53DC 002F1FBC  40 82 00 14 */	bne lbl_802F53F0
/* 802F53E0 002F1FC0  80 7F 00 58 */	lwz r3, 0x58(r31)
/* 802F53E4 002F1FC4  38 80 00 10 */	li r4, 0x10
/* 802F53E8 002F1FC8  48 07 C9 B5 */	bl HSD_JObjSetFlagsAll
/* 802F53EC 002F1FCC  48 00 00 10 */	b lbl_802F53FC
lbl_802F53F0:
/* 802F53F0 002F1FD0  80 7F 00 58 */	lwz r3, 0x58(r31)
/* 802F53F4 002F1FD4  38 80 00 10 */	li r4, 0x10
/* 802F53F8 002F1FD8  48 07 CB A5 */	bl HSD_JObjClearFlagsAll
lbl_802F53FC:
/* 802F53FC 002F1FDC  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 802F5400 002F1FE0  A8 FF 00 0A */	lha r7, 0xa(r31)
/* 802F5404 002F1FE4  3B 83 4D D3 */	addi r28, r3, 0x10624DD3@l
/* 802F5408 002F1FE8  80 77 00 00 */	lwz r3, 0(r23)
/* 802F540C 002F1FEC  7C 1C 38 96 */	mulhw r0, r28, r7
/* 802F5410 002F1FF0  83 1F 00 54 */	lwz r24, 0x54(r31)
/* 802F5414 002F1FF4  80 63 00 00 */	lwz r3, 0(r3)
/* 802F5418 002F1FF8  80 98 00 18 */	lwz r4, 0x18(r24)
/* 802F541C 002F1FFC  80 63 00 00 */	lwz r3, 0(r3)
/* 802F5420 002F2000  7C 00 36 70 */	srawi r0, r0, 6
/* 802F5424 002F2004  80 A4 00 08 */	lwz r5, 8(r4)
/* 802F5428 002F2008  54 06 0F FE */	srwi r6, r0, 0x1f
/* 802F542C 002F200C  80 83 00 08 */	lwz r4, 8(r3)
/* 802F5430 002F2010  7C 00 32 14 */	add r0, r0, r6
/* 802F5434 002F2014  80 65 00 08 */	lwz r3, 8(r5)
/* 802F5438 002F2018  1C 00 03 E8 */	mulli r0, r0, 0x3e8
/* 802F543C 002F201C  80 84 00 08 */	lwz r4, 8(r4)
/* 802F5440 002F2020  3C A0 51 EC */	lis r5, 0x51EB851F@ha
/* 802F5444 002F2024  7C 00 38 50 */	subf r0, r0, r7
/* 802F5448 002F2028  3B 65 85 1F */	addi r27, r5, 0x51EB851F@l
/* 802F544C 002F202C  7C 1B 00 96 */	mulhw r0, r27, r0
/* 802F5450 002F2030  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F5454 002F2034  54 05 0F FE */	srwi r5, r0, 0x1f
/* 802F5458 002F2038  7C 00 2A 14 */	add r0, r0, r5
/* 802F545C 002F203C  54 17 06 3E */	clrlwi r23, r0, 0x18
/* 802F5460 002F2040  48 06 92 A9 */	bl HSD_TObjAddAnimAll
/* 802F5464 002F2044  92 E1 00 A4 */	stw r23, 0xa4(r1)
/* 802F5468 002F2048  3C 00 43 30 */	lis r0, 0x4330
/* 802F546C 002F204C  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F5470 002F2050  90 01 00 A0 */	stw r0, 0xa0(r1)
/* 802F5474 002F2054  80 63 00 08 */	lwz r3, 8(r3)
/* 802F5478 002F2058  C8 22 E0 78 */	lfd f1, lbl_804DDA58(r2)
/* 802F547C 002F205C  C8 01 00 A0 */	lfd f0, 0xa0(r1)
/* 802F5480 002F2060  C0 42 E0 70 */	lfs f2, lbl_804DDA50(r2)
/* 802F5484 002F2064  EC 00 08 28 */	fsubs f0, f0, f1
/* 802F5488 002F2068  80 63 00 08 */	lwz r3, 8(r3)
/* 802F548C 002F206C  EC 22 00 32 */	fmuls f1, f2, f0
/* 802F5490 002F2070  48 06 93 71 */	bl HSD_TObjReqAnimAll
/* 802F5494 002F2074  80 78 00 18 */	lwz r3, 0x18(r24)
/* 802F5498 002F2078  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F549C 002F207C  80 63 00 08 */	lwz r3, 8(r3)
/* 802F54A0 002F2080  80 63 00 08 */	lwz r3, 8(r3)
/* 802F54A4 002F2084  80 63 00 64 */	lwz r3, 0x64(r3)
/* 802F54A8 002F2088  48 06 FE 65 */	bl HSD_AObjSetRate
/* 802F54AC 002F208C  A8 9F 00 0A */	lha r4, 0xa(r31)
/* 802F54B0 002F2090  7C 1C 20 96 */	mulhw r0, r28, r4
/* 802F54B4 002F2094  7C 00 36 70 */	srawi r0, r0, 6
/* 802F54B8 002F2098  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F54BC 002F209C  7C 00 1A 14 */	add r0, r0, r3
/* 802F54C0 002F20A0  1C 00 03 E8 */	mulli r0, r0, 0x3e8
/* 802F54C4 002F20A4  7C 00 20 50 */	subf r0, r0, r4
/* 802F54C8 002F20A8  7C 1B 00 96 */	mulhw r0, r27, r0
/* 802F54CC 002F20AC  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F54D0 002F20B0  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F54D4 002F20B4  7C 00 1A 15 */	add. r0, r0, r3
/* 802F54D8 002F20B8  40 82 00 14 */	bne lbl_802F54EC
/* 802F54DC 002F20BC  80 7F 00 54 */	lwz r3, 0x54(r31)
/* 802F54E0 002F20C0  38 80 00 10 */	li r4, 0x10
/* 802F54E4 002F20C4  48 07 C8 B9 */	bl HSD_JObjSetFlagsAll
/* 802F54E8 002F20C8  48 00 00 10 */	b lbl_802F54F8
lbl_802F54EC:
/* 802F54EC 002F20CC  80 7F 00 54 */	lwz r3, 0x54(r31)
/* 802F54F0 002F20D0  38 80 00 10 */	li r4, 0x10
/* 802F54F4 002F20D4  48 07 CA A9 */	bl HSD_JObjClearFlagsAll
lbl_802F54F8:
/* 802F54F8 002F20D8  A8 7F 00 0C */	lha r3, 0xc(r31)
/* 802F54FC 002F20DC  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 802F5500 002F20E0  7C 03 00 00 */	cmpw r3, r0
/* 802F5504 002F20E4  41 82 03 2C */	beq lbl_802F5830
/* 802F5508 002F20E8  88 7F 00 08 */	lbz r3, 8(r31)
/* 802F550C 002F20EC  7C 63 07 74 */	extsb r3, r3
/* 802F5510 002F20F0  4B D3 F1 25 */	bl Player_GetMoreFlagsBit2
/* 802F5514 002F20F4  2C 03 00 00 */	cmpwi r3, 0
/* 802F5518 002F20F8  41 82 01 40 */	beq lbl_802F5658
/* 802F551C 002F20FC  A8 7F 00 0A */	lha r3, 0xa(r31)
/* 802F5520 002F2100  2C 03 00 64 */	cmpwi r3, 0x64
/* 802F5524 002F2104  40 81 00 0C */	ble lbl_802F5530
/* 802F5528 002F2108  38 60 00 64 */	li r3, 0x64
/* 802F552C 002F210C  48 00 00 10 */	b lbl_802F553C
lbl_802F5530:
/* 802F5530 002F2110  7C 60 07 35 */	extsh. r0, r3
/* 802F5534 002F2114  40 80 00 08 */	bge lbl_802F553C
/* 802F5538 002F2118  38 60 00 00 */	li r3, 0
lbl_802F553C:
/* 802F553C 002F211C  7C 60 07 34 */	extsh r0, r3
/* 802F5540 002F2120  88 ED A1 08 */	lbz r7, lbl_804D57A8(r13)
/* 802F5544 002F2124  6C 03 80 00 */	xoris r3, r0, 0x8000
/* 802F5548 002F2128  88 0D A1 0C */	lbz r0, lbl_804D57AC(r13)
/* 802F554C 002F212C  90 61 00 A4 */	stw r3, 0xa4(r1)
/* 802F5550 002F2130  3C C0 43 30 */	lis r6, 0x4330
/* 802F5554 002F2134  7C 07 00 50 */	subf r0, r7, r0
/* 802F5558 002F2138  C8 82 E0 80 */	lfd f4, lbl_804DDA60(r2)
/* 802F555C 002F213C  90 C1 00 A0 */	stw r6, 0xa0(r1)
/* 802F5560 002F2140  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 802F5564 002F2144  C0 02 E0 8C */	lfs f0, lbl_804DDA6C(r2)
/* 802F5568 002F2148  C8 21 00 A0 */	lfd f1, 0xa0(r1)
/* 802F556C 002F214C  38 AD A1 08 */	addi r5, r13, lbl_804D57A8
/* 802F5570 002F2150  90 01 00 AC */	stw r0, 0xac(r1)
/* 802F5574 002F2154  38 8D A1 0C */	addi r4, r13, lbl_804D57AC
/* 802F5578 002F2158  EC 21 20 28 */	fsubs f1, f1, f4
/* 802F557C 002F215C  90 E1 00 B4 */	stw r7, 0xb4(r1)
/* 802F5580 002F2160  38 00 00 FF */	li r0, 0xff
/* 802F5584 002F2164  C0 A2 E0 68 */	lfs f5, lbl_804DDA48(r2)
/* 802F5588 002F2168  EC 61 00 24 */	fdivs f3, f1, f0
/* 802F558C 002F216C  90 C1 00 A8 */	stw r6, 0xa8(r1)
/* 802F5590 002F2170  C8 42 E0 78 */	lfd f2, lbl_804DDA58(r2)
/* 802F5594 002F2174  90 C1 00 B0 */	stw r6, 0xb0(r1)
/* 802F5598 002F2178  C8 21 00 A8 */	lfd f1, 0xa8(r1)
/* 802F559C 002F217C  C8 01 00 B0 */	lfd f0, 0xb0(r1)
/* 802F55A0 002F2180  EC 65 18 28 */	fsubs f3, f5, f3
/* 802F55A4 002F2184  EC 21 20 28 */	fsubs f1, f1, f4
/* 802F55A8 002F2188  EC 00 10 28 */	fsubs f0, f0, f2
/* 802F55AC 002F218C  EC 03 00 7A */	fmadds f0, f3, f1, f0
/* 802F55B0 002F2190  FC 00 00 1E */	fctiwz f0, f0
/* 802F55B4 002F2194  D8 01 00 98 */	stfd f0, 0x98(r1)
/* 802F55B8 002F2198  80 61 00 9C */	lwz r3, 0x9c(r1)
/* 802F55BC 002F219C  98 61 00 40 */	stb r3, 0x40(r1)
/* 802F55C0 002F21A0  88 E5 00 01 */	lbz r7, 1(r5)
/* 802F55C4 002F21A4  88 64 00 01 */	lbz r3, 1(r4)
/* 802F55C8 002F21A8  90 E1 00 8C */	stw r7, 0x8c(r1)
/* 802F55CC 002F21AC  7C 67 18 50 */	subf r3, r7, r3
/* 802F55D0 002F21B0  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 802F55D4 002F21B4  90 C1 00 88 */	stw r6, 0x88(r1)
/* 802F55D8 002F21B8  90 61 00 94 */	stw r3, 0x94(r1)
/* 802F55DC 002F21BC  C8 01 00 88 */	lfd f0, 0x88(r1)
/* 802F55E0 002F21C0  90 C1 00 90 */	stw r6, 0x90(r1)
/* 802F55E4 002F21C4  EC 00 10 28 */	fsubs f0, f0, f2
/* 802F55E8 002F21C8  C8 21 00 90 */	lfd f1, 0x90(r1)
/* 802F55EC 002F21CC  EC 21 20 28 */	fsubs f1, f1, f4
/* 802F55F0 002F21D0  EC 03 00 7A */	fmadds f0, f3, f1, f0
/* 802F55F4 002F21D4  FC 00 00 1E */	fctiwz f0, f0
/* 802F55F8 002F21D8  D8 01 00 80 */	stfd f0, 0x80(r1)
/* 802F55FC 002F21DC  80 61 00 84 */	lwz r3, 0x84(r1)
/* 802F5600 002F21E0  98 61 00 41 */	stb r3, 0x41(r1)
/* 802F5604 002F21E4  88 A5 00 02 */	lbz r5, 2(r5)
/* 802F5608 002F21E8  88 64 00 02 */	lbz r3, 2(r4)
/* 802F560C 002F21EC  90 A1 00 74 */	stw r5, 0x74(r1)
/* 802F5610 002F21F0  7C 65 18 50 */	subf r3, r5, r3
/* 802F5614 002F21F4  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 802F5618 002F21F8  90 C1 00 70 */	stw r6, 0x70(r1)
/* 802F561C 002F21FC  90 61 00 7C */	stw r3, 0x7c(r1)
/* 802F5620 002F2200  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 802F5624 002F2204  90 C1 00 78 */	stw r6, 0x78(r1)
/* 802F5628 002F2208  EC 00 10 28 */	fsubs f0, f0, f2
/* 802F562C 002F220C  C8 21 00 78 */	lfd f1, 0x78(r1)
/* 802F5630 002F2210  EC 21 20 28 */	fsubs f1, f1, f4
/* 802F5634 002F2214  EC 03 00 7A */	fmadds f0, f3, f1, f0
/* 802F5638 002F2218  FC 00 00 1E */	fctiwz f0, f0
/* 802F563C 002F221C  D8 01 00 68 */	stfd f0, 0x68(r1)
/* 802F5640 002F2220  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 802F5644 002F2224  98 61 00 42 */	stb r3, 0x42(r1)
/* 802F5648 002F2228  98 01 00 43 */	stb r0, 0x43(r1)
/* 802F564C 002F222C  80 01 00 40 */	lwz r0, 0x40(r1)
/* 802F5650 002F2230  90 01 00 60 */	stw r0, 0x60(r1)
/* 802F5654 002F2234  48 00 01 34 */	b lbl_802F5788
lbl_802F5658:
/* 802F5658 002F2238  A8 7F 00 0A */	lha r3, 0xa(r31)
/* 802F565C 002F223C  2C 03 01 2C */	cmpwi r3, 0x12c
/* 802F5660 002F2240  40 81 00 0C */	ble lbl_802F566C
/* 802F5664 002F2244  38 60 01 2C */	li r3, 0x12c
/* 802F5668 002F2248  48 00 00 10 */	b lbl_802F5678
lbl_802F566C:
/* 802F566C 002F224C  7C 60 07 35 */	extsh. r0, r3
/* 802F5670 002F2250  40 80 00 08 */	bge lbl_802F5678
/* 802F5674 002F2254  38 60 00 00 */	li r3, 0
lbl_802F5678:
/* 802F5678 002F2258  7C 60 07 34 */	extsh r0, r3
/* 802F567C 002F225C  88 ED A1 08 */	lbz r7, lbl_804D57A8(r13)
/* 802F5680 002F2260  6C 03 80 00 */	xoris r3, r0, 0x8000
/* 802F5684 002F2264  88 0D A1 0C */	lbz r0, lbl_804D57AC(r13)
/* 802F5688 002F2268  90 61 00 6C */	stw r3, 0x6c(r1)
/* 802F568C 002F226C  3C C0 43 30 */	lis r6, 0x4330
/* 802F5690 002F2270  7C 07 00 50 */	subf r0, r7, r0
/* 802F5694 002F2274  C8 62 E0 80 */	lfd f3, lbl_804DDA60(r2)
/* 802F5698 002F2278  90 C1 00 68 */	stw r6, 0x68(r1)
/* 802F569C 002F227C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 802F56A0 002F2280  C0 02 E0 88 */	lfs f0, lbl_804DDA68(r2)
/* 802F56A4 002F2284  C8 21 00 68 */	lfd f1, 0x68(r1)
/* 802F56A8 002F2288  38 AD A1 08 */	addi r5, r13, lbl_804D57A8
/* 802F56AC 002F228C  90 01 00 74 */	stw r0, 0x74(r1)
/* 802F56B0 002F2290  38 8D A1 0C */	addi r4, r13, lbl_804D57AC
/* 802F56B4 002F2294  EC 21 18 28 */	fsubs f1, f1, f3
/* 802F56B8 002F2298  90 E1 00 7C */	stw r7, 0x7c(r1)
/* 802F56BC 002F229C  38 00 00 FF */	li r0, 0xff
/* 802F56C0 002F22A0  C8 42 E0 78 */	lfd f2, lbl_804DDA58(r2)
/* 802F56C4 002F22A4  EC 81 00 24 */	fdivs f4, f1, f0
/* 802F56C8 002F22A8  90 C1 00 70 */	stw r6, 0x70(r1)
/* 802F56CC 002F22AC  90 C1 00 78 */	stw r6, 0x78(r1)
/* 802F56D0 002F22B0  C8 21 00 70 */	lfd f1, 0x70(r1)
/* 802F56D4 002F22B4  C8 01 00 78 */	lfd f0, 0x78(r1)
/* 802F56D8 002F22B8  EC 21 18 28 */	fsubs f1, f1, f3
/* 802F56DC 002F22BC  EC 00 10 28 */	fsubs f0, f0, f2
/* 802F56E0 002F22C0  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 802F56E4 002F22C4  FC 00 00 1E */	fctiwz f0, f0
/* 802F56E8 002F22C8  D8 01 00 80 */	stfd f0, 0x80(r1)
/* 802F56EC 002F22CC  80 61 00 84 */	lwz r3, 0x84(r1)
/* 802F56F0 002F22D0  98 61 00 38 */	stb r3, 0x38(r1)
/* 802F56F4 002F22D4  88 E5 00 01 */	lbz r7, 1(r5)
/* 802F56F8 002F22D8  88 64 00 01 */	lbz r3, 1(r4)
/* 802F56FC 002F22DC  90 E1 00 94 */	stw r7, 0x94(r1)
/* 802F5700 002F22E0  7C 67 18 50 */	subf r3, r7, r3
/* 802F5704 002F22E4  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 802F5708 002F22E8  90 C1 00 90 */	stw r6, 0x90(r1)
/* 802F570C 002F22EC  90 61 00 8C */	stw r3, 0x8c(r1)
/* 802F5710 002F22F0  C8 01 00 90 */	lfd f0, 0x90(r1)
/* 802F5714 002F22F4  90 C1 00 88 */	stw r6, 0x88(r1)
/* 802F5718 002F22F8  EC 00 10 28 */	fsubs f0, f0, f2
/* 802F571C 002F22FC  C8 21 00 88 */	lfd f1, 0x88(r1)
/* 802F5720 002F2300  EC 21 18 28 */	fsubs f1, f1, f3
/* 802F5724 002F2304  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 802F5728 002F2308  FC 00 00 1E */	fctiwz f0, f0
/* 802F572C 002F230C  D8 01 00 98 */	stfd f0, 0x98(r1)
/* 802F5730 002F2310  80 61 00 9C */	lwz r3, 0x9c(r1)
/* 802F5734 002F2314  98 61 00 39 */	stb r3, 0x39(r1)
/* 802F5738 002F2318  88 A5 00 02 */	lbz r5, 2(r5)
/* 802F573C 002F231C  88 64 00 02 */	lbz r3, 2(r4)
/* 802F5740 002F2320  90 A1 00 AC */	stw r5, 0xac(r1)
/* 802F5744 002F2324  7C 65 18 50 */	subf r3, r5, r3
/* 802F5748 002F2328  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 802F574C 002F232C  90 C1 00 A8 */	stw r6, 0xa8(r1)
/* 802F5750 002F2330  90 61 00 A4 */	stw r3, 0xa4(r1)
/* 802F5754 002F2334  C8 01 00 A8 */	lfd f0, 0xa8(r1)
/* 802F5758 002F2338  90 C1 00 A0 */	stw r6, 0xa0(r1)
/* 802F575C 002F233C  EC 00 10 28 */	fsubs f0, f0, f2
/* 802F5760 002F2340  C8 21 00 A0 */	lfd f1, 0xa0(r1)
/* 802F5764 002F2344  EC 21 18 28 */	fsubs f1, f1, f3
/* 802F5768 002F2348  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 802F576C 002F234C  FC 00 00 1E */	fctiwz f0, f0
/* 802F5770 002F2350  D8 01 00 B0 */	stfd f0, 0xb0(r1)
/* 802F5774 002F2354  80 61 00 B4 */	lwz r3, 0xb4(r1)
/* 802F5778 002F2358  98 61 00 3A */	stb r3, 0x3a(r1)
/* 802F577C 002F235C  98 01 00 3B */	stb r0, 0x3b(r1)
/* 802F5780 002F2360  80 01 00 38 */	lwz r0, 0x38(r1)
/* 802F5784 002F2364  90 01 00 60 */	stw r0, 0x60(r1)
lbl_802F5788:
/* 802F5788 002F2368  80 7F 00 54 */	lwz r3, 0x54(r31)
/* 802F578C 002F236C  88 01 00 60 */	lbz r0, 0x60(r1)
/* 802F5790 002F2370  80 63 00 18 */	lwz r3, 0x18(r3)
/* 802F5794 002F2374  80 83 00 08 */	lwz r4, 8(r3)
/* 802F5798 002F2378  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F579C 002F237C  98 03 00 04 */	stb r0, 4(r3)
/* 802F57A0 002F2380  88 A1 00 61 */	lbz r5, 0x61(r1)
/* 802F57A4 002F2384  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F57A8 002F2388  98 A3 00 05 */	stb r5, 5(r3)
/* 802F57AC 002F238C  88 C1 00 62 */	lbz r6, 0x62(r1)
/* 802F57B0 002F2390  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F57B4 002F2394  98 C3 00 06 */	stb r6, 6(r3)
/* 802F57B8 002F2398  80 7F 00 58 */	lwz r3, 0x58(r31)
/* 802F57BC 002F239C  88 01 00 60 */	lbz r0, 0x60(r1)
/* 802F57C0 002F23A0  80 63 00 18 */	lwz r3, 0x18(r3)
/* 802F57C4 002F23A4  80 83 00 08 */	lwz r4, 8(r3)
/* 802F57C8 002F23A8  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F57CC 002F23AC  98 03 00 04 */	stb r0, 4(r3)
/* 802F57D0 002F23B0  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F57D4 002F23B4  98 A3 00 05 */	stb r5, 5(r3)
/* 802F57D8 002F23B8  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F57DC 002F23BC  98 C3 00 06 */	stb r6, 6(r3)
/* 802F57E0 002F23C0  80 7F 00 5C */	lwz r3, 0x5c(r31)
/* 802F57E4 002F23C4  88 01 00 60 */	lbz r0, 0x60(r1)
/* 802F57E8 002F23C8  80 63 00 18 */	lwz r3, 0x18(r3)
/* 802F57EC 002F23CC  80 83 00 08 */	lwz r4, 8(r3)
/* 802F57F0 002F23D0  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F57F4 002F23D4  98 03 00 04 */	stb r0, 4(r3)
/* 802F57F8 002F23D8  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F57FC 002F23DC  98 A3 00 05 */	stb r5, 5(r3)
/* 802F5800 002F23E0  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F5804 002F23E4  98 C3 00 06 */	stb r6, 6(r3)
/* 802F5808 002F23E8  80 7F 00 60 */	lwz r3, 0x60(r31)
/* 802F580C 002F23EC  88 01 00 60 */	lbz r0, 0x60(r1)
/* 802F5810 002F23F0  80 63 00 18 */	lwz r3, 0x18(r3)
/* 802F5814 002F23F4  80 83 00 08 */	lwz r4, 8(r3)
/* 802F5818 002F23F8  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F581C 002F23FC  98 03 00 04 */	stb r0, 4(r3)
/* 802F5820 002F2400  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F5824 002F2404  98 A3 00 05 */	stb r5, 5(r3)
/* 802F5828 002F2408  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F582C 002F240C  98 C3 00 06 */	stb r6, 6(r3)
lbl_802F5830:
/* 802F5830 002F2410  7F C3 F3 78 */	mr r3, r30
/* 802F5834 002F2414  4B D1 58 69 */	bl func_8000B09C
/* 802F5838 002F2418  2C 03 00 00 */	cmpwi r3, 0
/* 802F583C 002F241C  41 82 00 64 */	beq lbl_802F58A0
/* 802F5840 002F2420  3A E0 00 00 */	li r23, 0
/* 802F5844 002F2424  3B 1F 00 00 */	addi r24, r31, 0
lbl_802F5848:
/* 802F5848 002F2428  83 38 00 54 */	lwz r25, 0x54(r24)
/* 802F584C 002F242C  28 19 00 00 */	cmplwi r25, 0
/* 802F5850 002F2430  40 82 00 14 */	bne lbl_802F5864
/* 802F5854 002F2434  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F5858 002F2438  38 80 03 E1 */	li r4, 0x3e1
/* 802F585C 002F243C  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F5860 002F2440  48 09 29 C1 */	bl __assert
lbl_802F5864:
/* 802F5864 002F2444  C0 19 00 38 */	lfs f0, 0x38(r25)
/* 802F5868 002F2448  D0 18 00 14 */	stfs f0, 0x14(r24)
/* 802F586C 002F244C  83 38 00 54 */	lwz r25, 0x54(r24)
/* 802F5870 002F2450  28 19 00 00 */	cmplwi r25, 0
/* 802F5874 002F2454  40 82 00 14 */	bne lbl_802F5888
/* 802F5878 002F2458  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F587C 002F245C  38 80 03 EE */	li r4, 0x3ee
/* 802F5880 002F2460  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F5884 002F2464  48 09 29 9D */	bl __assert
lbl_802F5888:
/* 802F5888 002F2468  C0 19 00 3C */	lfs f0, 0x3c(r25)
/* 802F588C 002F246C  3A F7 00 01 */	addi r23, r23, 1
/* 802F5890 002F2470  2C 17 00 04 */	cmpwi r23, 4
/* 802F5894 002F2474  D0 18 00 24 */	stfs f0, 0x24(r24)
/* 802F5898 002F2478  3B 18 00 04 */	addi r24, r24, 4
/* 802F589C 002F247C  41 80 FF AC */	blt lbl_802F5848
lbl_802F58A0:
/* 802F58A0 002F2480  3C 60 66 66 */	lis r3, 0x66666667@ha
/* 802F58A4 002F2484  A8 9F 00 0A */	lha r4, 0xa(r31)
/* 802F58A8 002F2488  38 03 66 67 */	addi r0, r3, 0x66666667@l
/* 802F58AC 002F248C  7C 00 20 96 */	mulhw r0, r0, r4
/* 802F58B0 002F2490  7C 00 16 70 */	srawi r0, r0, 2
/* 802F58B4 002F2494  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F58B8 002F2498  7C 00 1A 14 */	add r0, r0, r3
/* 802F58BC 002F249C  1C 00 00 0A */	mulli r0, r0, 0xa
/* 802F58C0 002F24A0  7C 00 20 50 */	subf r0, r0, r4
/* 802F58C4 002F24A4  2C 00 00 01 */	cmpwi r0, 1
/* 802F58C8 002F24A8  40 82 00 0C */	bne lbl_802F58D4
/* 802F58CC 002F24AC  C3 E2 E0 90 */	lfs f31, lbl_804DDA70(r2)
/* 802F58D0 002F24B0  48 00 00 08 */	b lbl_802F58D8
lbl_802F58D4:
/* 802F58D4 002F24B4  C3 E2 E0 6C */	lfs f31, lbl_804DDA4C(r2)
lbl_802F58D8:
/* 802F58D8 002F24B8  3C 60 51 EC */	lis r3, 0x51EB851F@ha
/* 802F58DC 002F24BC  38 03 85 1F */	addi r0, r3, 0x51EB851F@l
/* 802F58E0 002F24C0  7C 00 20 96 */	mulhw r0, r0, r4
/* 802F58E4 002F24C4  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F58E8 002F24C8  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F58EC 002F24CC  7C 00 1A 14 */	add r0, r0, r3
/* 802F58F0 002F24D0  1C 00 00 64 */	mulli r0, r0, 0x64
/* 802F58F4 002F24D4  3C 60 66 66 */	lis r3, 0x66666667@ha
/* 802F58F8 002F24D8  7C 00 20 50 */	subf r0, r0, r4
/* 802F58FC 002F24DC  38 63 66 67 */	addi r3, r3, 0x66666667@l
/* 802F5900 002F24E0  7C 03 00 96 */	mulhw r0, r3, r0
/* 802F5904 002F24E4  7C 00 16 70 */	srawi r0, r0, 2
/* 802F5908 002F24E8  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F590C 002F24EC  7C 00 1A 14 */	add r0, r0, r3
/* 802F5910 002F24F0  2C 00 00 01 */	cmpwi r0, 1
/* 802F5914 002F24F4  40 82 00 0C */	bne lbl_802F5920
/* 802F5918 002F24F8  C3 C2 E0 90 */	lfs f30, lbl_804DDA70(r2)
/* 802F591C 002F24FC  48 00 00 08 */	b lbl_802F5924
lbl_802F5920:
/* 802F5920 002F2500  C3 C2 E0 6C */	lfs f30, lbl_804DDA4C(r2)
lbl_802F5924:
/* 802F5924 002F2504  82 FF 00 60 */	lwz r23, 0x60(r31)
/* 802F5928 002F2508  C0 1F 00 20 */	lfs f0, 0x20(r31)
/* 802F592C 002F250C  28 17 00 00 */	cmplwi r23, 0
/* 802F5930 002F2510  EF A0 F8 28 */	fsubs f29, f0, f31
/* 802F5934 002F2514  40 82 00 14 */	bne lbl_802F5948
/* 802F5938 002F2518  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F593C 002F251C  38 80 03 A4 */	li r4, 0x3a4
/* 802F5940 002F2520  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F5944 002F2524  48 09 28 DD */	bl __assert
lbl_802F5948:
/* 802F5948 002F2528  D3 B7 00 38 */	stfs f29, 0x38(r23)
/* 802F594C 002F252C  80 17 00 14 */	lwz r0, 0x14(r23)
/* 802F5950 002F2530  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F5954 002F2534  40 82 00 4C */	bne lbl_802F59A0
/* 802F5958 002F2538  28 17 00 00 */	cmplwi r23, 0
/* 802F595C 002F253C  41 82 00 44 */	beq lbl_802F59A0
/* 802F5960 002F2540  40 82 00 14 */	bne lbl_802F5974
/* 802F5964 002F2544  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F5968 002F2548  38 80 02 34 */	li r4, 0x234
/* 802F596C 002F254C  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F5970 002F2550  48 09 28 B1 */	bl __assert
lbl_802F5974:
/* 802F5974 002F2554  80 97 00 14 */	lwz r4, 0x14(r23)
/* 802F5978 002F2558  38 60 00 00 */	li r3, 0
/* 802F597C 002F255C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F5980 002F2560  40 82 00 10 */	bne lbl_802F5990
/* 802F5984 002F2564  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F5988 002F2568  41 82 00 08 */	beq lbl_802F5990
/* 802F598C 002F256C  38 60 00 01 */	li r3, 1
lbl_802F5990:
/* 802F5990 002F2570  2C 03 00 00 */	cmpwi r3, 0
/* 802F5994 002F2574  40 82 00 0C */	bne lbl_802F59A0
/* 802F5998 002F2578  7E E3 BB 78 */	mr r3, r23
/* 802F599C 002F257C  48 07 D9 4D */	bl HSD_JObjSetMtxDirtySub
lbl_802F59A0:
/* 802F59A0 002F2580  EF FF F0 2A */	fadds f31, f31, f30
/* 802F59A4 002F2584  82 FF 00 58 */	lwz r23, 0x58(r31)
/* 802F59A8 002F2588  C0 1F 00 18 */	lfs f0, 0x18(r31)
/* 802F59AC 002F258C  28 17 00 00 */	cmplwi r23, 0
/* 802F59B0 002F2590  EF A0 F8 2A */	fadds f29, f0, f31
/* 802F59B4 002F2594  40 82 00 14 */	bne lbl_802F59C8
/* 802F59B8 002F2598  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F59BC 002F259C  38 80 03 A4 */	li r4, 0x3a4
/* 802F59C0 002F25A0  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F59C4 002F25A4  48 09 28 5D */	bl __assert
lbl_802F59C8:
/* 802F59C8 002F25A8  D3 B7 00 38 */	stfs f29, 0x38(r23)
/* 802F59CC 002F25AC  80 17 00 14 */	lwz r0, 0x14(r23)
/* 802F59D0 002F25B0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F59D4 002F25B4  40 82 00 4C */	bne lbl_802F5A20
/* 802F59D8 002F25B8  28 17 00 00 */	cmplwi r23, 0
/* 802F59DC 002F25BC  41 82 00 44 */	beq lbl_802F5A20
/* 802F59E0 002F25C0  40 82 00 14 */	bne lbl_802F59F4
/* 802F59E4 002F25C4  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F59E8 002F25C8  38 80 02 34 */	li r4, 0x234
/* 802F59EC 002F25CC  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F59F0 002F25D0  48 09 28 31 */	bl __assert
lbl_802F59F4:
/* 802F59F4 002F25D4  80 97 00 14 */	lwz r4, 0x14(r23)
/* 802F59F8 002F25D8  38 60 00 00 */	li r3, 0
/* 802F59FC 002F25DC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F5A00 002F25E0  40 82 00 10 */	bne lbl_802F5A10
/* 802F5A04 002F25E4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F5A08 002F25E8  41 82 00 08 */	beq lbl_802F5A10
/* 802F5A0C 002F25EC  38 60 00 01 */	li r3, 1
lbl_802F5A10:
/* 802F5A10 002F25F0  2C 03 00 00 */	cmpwi r3, 0
/* 802F5A14 002F25F4  40 82 00 0C */	bne lbl_802F5A20
/* 802F5A18 002F25F8  7E E3 BB 78 */	mr r3, r23
/* 802F5A1C 002F25FC  48 07 D8 CD */	bl HSD_JObjSetMtxDirtySub
lbl_802F5A20:
/* 802F5A20 002F2600  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 802F5A24 002F2604  A8 9F 00 0A */	lha r4, 0xa(r31)
/* 802F5A28 002F2608  38 03 4D D3 */	addi r0, r3, 0x10624DD3@l
/* 802F5A2C 002F260C  7C 00 20 96 */	mulhw r0, r0, r4
/* 802F5A30 002F2610  7C 00 36 70 */	srawi r0, r0, 6
/* 802F5A34 002F2614  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F5A38 002F2618  7C 00 1A 14 */	add r0, r0, r3
/* 802F5A3C 002F261C  1C 00 03 E8 */	mulli r0, r0, 0x3e8
/* 802F5A40 002F2620  3C 60 51 EC */	lis r3, 0x51EB851F@ha
/* 802F5A44 002F2624  7C 00 20 50 */	subf r0, r0, r4
/* 802F5A48 002F2628  38 63 85 1F */	addi r3, r3, 0x51EB851F@l
/* 802F5A4C 002F262C  7C 03 00 96 */	mulhw r0, r3, r0
/* 802F5A50 002F2630  7C 00 2E 70 */	srawi r0, r0, 5
/* 802F5A54 002F2634  54 03 0F FE */	srwi r3, r0, 0x1f
/* 802F5A58 002F2638  7C 00 1A 14 */	add r0, r0, r3
/* 802F5A5C 002F263C  2C 00 00 01 */	cmpwi r0, 1
/* 802F5A60 002F2640  40 82 00 0C */	bne lbl_802F5A6C
/* 802F5A64 002F2644  C0 02 E0 90 */	lfs f0, lbl_804DDA70(r2)
/* 802F5A68 002F2648  48 00 00 08 */	b lbl_802F5A70
lbl_802F5A6C:
/* 802F5A6C 002F264C  C0 02 E0 6C */	lfs f0, lbl_804DDA4C(r2)
lbl_802F5A70:
/* 802F5A70 002F2650  EC 3E 00 2A */	fadds f1, f30, f0
/* 802F5A74 002F2654  82 FF 00 54 */	lwz r23, 0x54(r31)
/* 802F5A78 002F2658  C0 1F 00 14 */	lfs f0, 0x14(r31)
/* 802F5A7C 002F265C  28 17 00 00 */	cmplwi r23, 0
/* 802F5A80 002F2660  EF FF 08 2A */	fadds f31, f31, f1
/* 802F5A84 002F2664  EF A0 F8 2A */	fadds f29, f0, f31
/* 802F5A88 002F2668  40 82 00 14 */	bne lbl_802F5A9C
/* 802F5A8C 002F266C  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F5A90 002F2670  38 80 03 A4 */	li r4, 0x3a4
/* 802F5A94 002F2674  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F5A98 002F2678  48 09 27 89 */	bl __assert
lbl_802F5A9C:
/* 802F5A9C 002F267C  D3 B7 00 38 */	stfs f29, 0x38(r23)
/* 802F5AA0 002F2680  80 17 00 14 */	lwz r0, 0x14(r23)
/* 802F5AA4 002F2684  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F5AA8 002F2688  40 82 00 4C */	bne lbl_802F5AF4
/* 802F5AAC 002F268C  28 17 00 00 */	cmplwi r23, 0
/* 802F5AB0 002F2690  41 82 00 44 */	beq lbl_802F5AF4
/* 802F5AB4 002F2694  40 82 00 14 */	bne lbl_802F5AC8
/* 802F5AB8 002F2698  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F5ABC 002F269C  38 80 02 34 */	li r4, 0x234
/* 802F5AC0 002F26A0  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F5AC4 002F26A4  48 09 27 5D */	bl __assert
lbl_802F5AC8:
/* 802F5AC8 002F26A8  80 97 00 14 */	lwz r4, 0x14(r23)
/* 802F5ACC 002F26AC  38 60 00 00 */	li r3, 0
/* 802F5AD0 002F26B0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F5AD4 002F26B4  40 82 00 10 */	bne lbl_802F5AE4
/* 802F5AD8 002F26B8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F5ADC 002F26BC  41 82 00 08 */	beq lbl_802F5AE4
/* 802F5AE0 002F26C0  38 60 00 01 */	li r3, 1
lbl_802F5AE4:
/* 802F5AE4 002F26C4  2C 03 00 00 */	cmpwi r3, 0
/* 802F5AE8 002F26C8  40 82 00 0C */	bne lbl_802F5AF4
/* 802F5AEC 002F26CC  7E E3 BB 78 */	mr r3, r23
/* 802F5AF0 002F26D0  48 07 D7 F9 */	bl HSD_JObjSetMtxDirtySub
lbl_802F5AF4:
/* 802F5AF4 002F26D4  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5AF8 002F26D8  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 802F5AFC 002F26DC  41 82 00 0C */	beq lbl_802F5B08
/* 802F5B00 002F26E0  38 00 00 0A */	li r0, 0xa
/* 802F5B04 002F26E4  98 1F 00 0F */	stb r0, 0xf(r31)
lbl_802F5B08:
/* 802F5B08 002F26E8  38 7F 00 00 */	addi r3, r31, 0
/* 802F5B0C 002F26EC  38 9D 00 00 */	addi r4, r29, 0
/* 802F5B10 002F26F0  4B FF F0 75 */	bl func_802F4B84
/* 802F5B14 002F26F4  88 0D B6 C0 */	lbz r0, lbl_804D6D60(r13)
/* 802F5B18 002F26F8  28 00 00 05 */	cmplwi r0, 5
/* 802F5B1C 002F26FC  41 80 00 0C */	blt lbl_802F5B28
/* 802F5B20 002F2700  C0 02 E0 B8 */	lfs f0, lbl_804DDA98(r2)
/* 802F5B24 002F2704  D0 1E 00 2C */	stfs f0, 0x2c(r30)
lbl_802F5B28:
/* 802F5B28 002F2708  BA E1 00 BC */	lmw r23, 0xbc(r1)
/* 802F5B2C 002F270C  80 01 00 FC */	lwz r0, 0xfc(r1)
/* 802F5B30 002F2710  CB E1 00 F0 */	lfd f31, 0xf0(r1)
/* 802F5B34 002F2714  CB C1 00 E8 */	lfd f30, 0xe8(r1)
/* 802F5B38 002F2718  CB A1 00 E0 */	lfd f29, 0xe0(r1)
/* 802F5B3C 002F271C  38 21 00 F8 */	addi r1, r1, 0xf8
/* 802F5B40 002F2720  7C 08 03 A6 */	mtlr r0
/* 802F5B44 002F2724  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80391070();
extern unk_t func_8016AE44();
extern u8 lbl_804D7849;
extern char* lbl_803F95C0;

#pragma push
asm unk_t func_802F5B48()
{ // clang-format off
    nofralloc
/* 802F5B48 002F2728  7C 08 02 A6 */	mflr r0
/* 802F5B4C 002F272C  3C 80 80 4A */	lis r4, lbl_804A10C8@ha
/* 802F5B50 002F2730  90 01 00 04 */	stw r0, 4(r1)
/* 802F5B54 002F2734  38 00 00 06 */	li r0, 6
/* 802F5B58 002F2738  38 A4 10 C8 */	addi r5, r4, lbl_804A10C8@l
/* 802F5B5C 002F273C  7C 09 03 A6 */	mtctr r0
/* 802F5B60 002F2740  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F5B64 002F2744  38 80 00 00 */	li r4, 0
/* 802F5B68 002F2748  93 E1 00 14 */	stw r31, 0x14(r1)
lbl_802F5B6C:
/* 802F5B6C 002F274C  80 05 00 00 */	lwz r0, 0(r5)
/* 802F5B70 002F2750  7C 00 18 40 */	cmplw r0, r3
/* 802F5B74 002F2754  40 82 00 18 */	bne lbl_802F5B8C
/* 802F5B78 002F2758  1C 84 00 64 */	mulli r4, r4, 0x64
/* 802F5B7C 002F275C  3C 60 80 4A */	lis r3, lbl_804A10C8@ha
/* 802F5B80 002F2760  38 03 10 C8 */	addi r0, r3, lbl_804A10C8@l
/* 802F5B84 002F2764  7F E0 22 14 */	add r31, r0, r4
/* 802F5B88 002F2768  48 00 00 14 */	b lbl_802F5B9C
lbl_802F5B8C:
/* 802F5B8C 002F276C  38 A5 00 64 */	addi r5, r5, 0x64
/* 802F5B90 002F2770  38 84 00 01 */	addi r4, r4, 1
/* 802F5B94 002F2774  42 00 FF D8 */	bdnz lbl_802F5B6C
/* 802F5B98 002F2778  3B E0 00 00 */	li r31, 0
lbl_802F5B9C:
/* 802F5B9C 002F277C  88 7F 00 09 */	lbz r3, 9(r31)
/* 802F5BA0 002F2780  28 03 00 00 */	cmplwi r3, 0
/* 802F5BA4 002F2784  41 82 00 24 */	beq lbl_802F5BC8
/* 802F5BA8 002F2788  38 63 00 01 */	addi r3, r3, 1
/* 802F5BAC 002F278C  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 802F5BB0 002F2790  98 7F 00 09 */	stb r3, 9(r31)
/* 802F5BB4 002F2794  28 00 00 C8 */	cmplwi r0, 0xc8
/* 802F5BB8 002F2798  40 81 00 10 */	ble lbl_802F5BC8
/* 802F5BBC 002F279C  88 7F 00 08 */	lbz r3, 8(r31)
/* 802F5BC0 002F27A0  48 00 0B C9 */	bl func_802F6788
/* 802F5BC4 002F27A4  48 00 02 08 */	b lbl_802F5DCC
lbl_802F5BC8:
/* 802F5BC8 002F27A8  88 7F 00 08 */	lbz r3, 8(r31)
/* 802F5BCC 002F27AC  7C 63 07 74 */	extsb r3, r3
/* 802F5BD0 002F27B0  4B D3 E5 41 */	bl Player_GetEntity
/* 802F5BD4 002F27B4  28 03 00 00 */	cmplwi r3, 0
/* 802F5BD8 002F27B8  41 82 01 F4 */	beq lbl_802F5DCC
/* 802F5BDC 002F27BC  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 802F5BE0 002F27C0  B0 1F 00 0C */	sth r0, 0xc(r31)
/* 802F5BE4 002F27C4  88 7F 00 08 */	lbz r3, 8(r31)
/* 802F5BE8 002F27C8  7C 63 07 74 */	extsb r3, r3
/* 802F5BEC 002F27CC  4B D3 EA 49 */	bl Player_GetMoreFlagsBit2
/* 802F5BF0 002F27D0  2C 03 00 00 */	cmpwi r3, 0
/* 802F5BF4 002F27D4  41 82 01 0C */	beq lbl_802F5D00
/* 802F5BF8 002F27D8  88 7F 00 08 */	lbz r3, 8(r31)
/* 802F5BFC 002F27DC  7C 63 07 74 */	extsb r3, r3
/* 802F5C00 002F27E0  4B D3 E9 A5 */	bl Player_GetRemainingHP
/* 802F5C04 002F27E4  7C 60 07 34 */	extsh r0, r3
/* 802F5C08 002F27E8  B0 1F 00 0A */	sth r0, 0xa(r31)
/* 802F5C0C 002F27EC  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 802F5C10 002F27F0  2C 00 03 E7 */	cmpwi r0, 0x3e7
/* 802F5C14 002F27F4  40 81 00 10 */	ble lbl_802F5C24
/* 802F5C18 002F27F8  38 00 03 E7 */	li r0, 0x3e7
/* 802F5C1C 002F27FC  B0 1F 00 0A */	sth r0, 0xa(r31)
/* 802F5C20 002F2800  48 00 00 14 */	b lbl_802F5C34
lbl_802F5C24:
/* 802F5C24 002F2804  7C 00 07 35 */	extsh. r0, r0
/* 802F5C28 002F2808  40 80 00 0C */	bge lbl_802F5C34
/* 802F5C2C 002F280C  38 00 00 00 */	li r0, 0
/* 802F5C30 002F2810  B0 1F 00 0A */	sth r0, 0xa(r31)
lbl_802F5C34:
/* 802F5C34 002F2814  A8 7F 00 0C */	lha r3, 0xc(r31)
/* 802F5C38 002F2818  2C 03 FF FF */	cmpwi r3, -1
/* 802F5C3C 002F281C  41 82 00 3C */	beq lbl_802F5C78
/* 802F5C40 002F2820  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 802F5C44 002F2824  7C 00 18 00 */	cmpw r0, r3
/* 802F5C48 002F2828  40 80 00 30 */	bge lbl_802F5C78
/* 802F5C4C 002F282C  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5C50 002F2830  38 60 00 01 */	li r3, 1
/* 802F5C54 002F2834  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 802F5C58 002F2838  98 1F 00 10 */	stb r0, 0x10(r31)
/* 802F5C5C 002F283C  A8 7F 00 0A */	lha r3, 0xa(r31)
/* 802F5C60 002F2840  A8 1F 00 0C */	lha r0, 0xc(r31)
/* 802F5C64 002F2844  7C 03 00 51 */	subf. r0, r3, r0
/* 802F5C68 002F2848  40 80 00 08 */	bge lbl_802F5C70
/* 802F5C6C 002F284C  7C 00 00 D0 */	neg r0, r0
lbl_802F5C70:
/* 802F5C70 002F2850  98 1F 00 0E */	stb r0, 0xe(r31)
/* 802F5C74 002F2854  48 00 00 14 */	b lbl_802F5C88
lbl_802F5C78:
/* 802F5C78 002F2858  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5C7C 002F285C  38 60 00 00 */	li r3, 0
/* 802F5C80 002F2860  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 802F5C84 002F2864  98 1F 00 10 */	stb r0, 0x10(r31)
lbl_802F5C88:
/* 802F5C88 002F2868  A8 7F 00 0C */	lha r3, 0xc(r31)
/* 802F5C8C 002F286C  2C 03 FF FF */	cmpwi r3, -1
/* 802F5C90 002F2870  41 82 00 24 */	beq lbl_802F5CB4
/* 802F5C94 002F2874  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 802F5C98 002F2878  7C 00 18 00 */	cmpw r0, r3
/* 802F5C9C 002F287C  40 81 00 18 */	ble lbl_802F5CB4
/* 802F5CA0 002F2880  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5CA4 002F2884  38 60 00 01 */	li r3, 1
/* 802F5CA8 002F2888  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 802F5CAC 002F288C  98 1F 00 10 */	stb r0, 0x10(r31)
/* 802F5CB0 002F2890  48 00 00 14 */	b lbl_802F5CC4
lbl_802F5CB4:
/* 802F5CB4 002F2894  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5CB8 002F2898  38 60 00 00 */	li r3, 0
/* 802F5CBC 002F289C  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 802F5CC0 002F28A0  98 1F 00 10 */	stb r0, 0x10(r31)
lbl_802F5CC4:
/* 802F5CC4 002F28A4  A8 1F 00 0C */	lha r0, 0xc(r31)
/* 802F5CC8 002F28A8  2C 00 00 00 */	cmpwi r0, 0
/* 802F5CCC 002F28AC  40 82 01 00 */	bne lbl_802F5DCC
/* 802F5CD0 002F28B0  4B E7 51 75 */	bl func_8016AE44
/* 802F5CD4 002F28B4  88 BF 00 08 */	lbz r5, 8(r31)
/* 802F5CD8 002F28B8  7C A0 07 74 */	extsb r0, r5
/* 802F5CDC 002F28BC  1C 80 00 0E */	mulli r4, r0, 0xe
/* 802F5CE0 002F28C0  38 04 00 3C */	addi r0, r4, 0x3c
/* 802F5CE4 002F28C4  7C 03 00 AE */	lbzx r0, r3, r0
/* 802F5CE8 002F28C8  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 802F5CEC 002F28CC  41 82 00 E0 */	beq lbl_802F5DCC
/* 802F5CF0 002F28D0  38 65 00 00 */	addi r3, r5, 0
/* 802F5CF4 002F28D4  7C 63 07 74 */	extsb r3, r3
/* 802F5CF8 002F28D8  48 00 0C 51 */	bl func_802F6948
/* 802F5CFC 002F28DC  48 00 00 D0 */	b lbl_802F5DCC
lbl_802F5D00:
/* 802F5D00 002F28E0  88 7F 00 08 */	lbz r3, 8(r31)
/* 802F5D04 002F28E4  7C 63 07 74 */	extsb r3, r3
/* 802F5D08 002F28E8  4B D3 E5 AD */	bl Player_GetDamage
/* 802F5D0C 002F28EC  7C 60 07 34 */	extsh r0, r3
/* 802F5D10 002F28F0  B0 1F 00 0A */	sth r0, 0xa(r31)
/* 802F5D14 002F28F4  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 802F5D18 002F28F8  2C 00 03 E7 */	cmpwi r0, 0x3e7
/* 802F5D1C 002F28FC  40 81 00 10 */	ble lbl_802F5D2C
/* 802F5D20 002F2900  38 00 03 E7 */	li r0, 0x3e7
/* 802F5D24 002F2904  B0 1F 00 0A */	sth r0, 0xa(r31)
/* 802F5D28 002F2908  48 00 00 14 */	b lbl_802F5D3C
lbl_802F5D2C:
/* 802F5D2C 002F290C  7C 00 07 35 */	extsh. r0, r0
/* 802F5D30 002F2910  40 80 00 0C */	bge lbl_802F5D3C
/* 802F5D34 002F2914  38 00 00 00 */	li r0, 0
/* 802F5D38 002F2918  B0 1F 00 0A */	sth r0, 0xa(r31)
lbl_802F5D3C:
/* 802F5D3C 002F291C  A8 7F 00 0C */	lha r3, 0xc(r31)
/* 802F5D40 002F2920  2C 03 FF FF */	cmpwi r3, -1
/* 802F5D44 002F2924  41 82 00 24 */	beq lbl_802F5D68
/* 802F5D48 002F2928  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 802F5D4C 002F292C  7C 00 18 00 */	cmpw r0, r3
/* 802F5D50 002F2930  40 80 00 18 */	bge lbl_802F5D68
/* 802F5D54 002F2934  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5D58 002F2938  38 60 00 01 */	li r3, 1
/* 802F5D5C 002F293C  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 802F5D60 002F2940  98 1F 00 10 */	stb r0, 0x10(r31)
/* 802F5D64 002F2944  48 00 00 14 */	b lbl_802F5D78
lbl_802F5D68:
/* 802F5D68 002F2948  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5D6C 002F294C  38 60 00 00 */	li r3, 0
/* 802F5D70 002F2950  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 802F5D74 002F2954  98 1F 00 10 */	stb r0, 0x10(r31)
lbl_802F5D78:
/* 802F5D78 002F2958  A8 7F 00 0C */	lha r3, 0xc(r31)
/* 802F5D7C 002F295C  2C 03 FF FF */	cmpwi r3, -1
/* 802F5D80 002F2960  41 82 00 3C */	beq lbl_802F5DBC
/* 802F5D84 002F2964  A8 1F 00 0A */	lha r0, 0xa(r31)
/* 802F5D88 002F2968  7C 00 18 00 */	cmpw r0, r3
/* 802F5D8C 002F296C  40 81 00 30 */	ble lbl_802F5DBC
/* 802F5D90 002F2970  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5D94 002F2974  38 60 00 01 */	li r3, 1
/* 802F5D98 002F2978  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 802F5D9C 002F297C  98 1F 00 10 */	stb r0, 0x10(r31)
/* 802F5DA0 002F2980  A8 7F 00 0A */	lha r3, 0xa(r31)
/* 802F5DA4 002F2984  A8 1F 00 0C */	lha r0, 0xc(r31)
/* 802F5DA8 002F2988  7C 03 00 51 */	subf. r0, r3, r0
/* 802F5DAC 002F298C  40 80 00 08 */	bge lbl_802F5DB4
/* 802F5DB0 002F2990  7C 00 00 D0 */	neg r0, r0
lbl_802F5DB4:
/* 802F5DB4 002F2994  98 1F 00 0E */	stb r0, 0xe(r31)
/* 802F5DB8 002F2998  48 00 00 14 */	b lbl_802F5DCC
lbl_802F5DBC:
/* 802F5DBC 002F299C  88 1F 00 10 */	lbz r0, 0x10(r31)
/* 802F5DC0 002F29A0  38 60 00 00 */	li r3, 0
/* 802F5DC4 002F29A4  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 802F5DC8 002F29A8  98 1F 00 10 */	stb r0, 0x10(r31)
lbl_802F5DCC:
/* 802F5DCC 002F29AC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F5DD0 002F29B0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F5DD4 002F29B4  38 21 00 18 */	addi r1, r1, 0x18
/* 802F5DD8 002F29B8  7C 08 03 A6 */	mtlr r0
/* 802F5DDC 002F29BC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

inline IfDamageState* getPlayerByHUDParent(HSD_GObj* parent)
{
    s32 var_ctr;
    for (var_ctr = 0; var_ctr < 6; var_ctr++) {
        if (lbl_804A10C8.players[var_ctr].HUD_parent_entity == parent) {
            return &lbl_804A10C8.players[var_ctr];
        }
    }
    return NULL;
}

void lbl_802F5DE0(HSD_GObj* player, void* unk)
{
    if (!getPlayerByHUDParent(player)->flags.hide_all_digits) {
        func_80391070(player, unk);
    }
}

#pragma push
asm unk_t lbl_802F5E50()
{ // clang-format off
    nofralloc
/* 802F5E50 002F2A30  7C 08 02 A6 */	mflr r0
/* 802F5E54 002F2A34  3C A0 80 4A */	lis r5, lbl_804A10C8@ha
/* 802F5E58 002F2A38  90 01 00 04 */	stw r0, 4(r1)
/* 802F5E5C 002F2A3C  38 00 00 06 */	li r0, 6
/* 802F5E60 002F2A40  38 C5 10 C8 */	addi r6, r5, lbl_804A10C8@l
/* 802F5E64 002F2A44  7C 09 03 A6 */	mtctr r0
/* 802F5E68 002F2A48  94 21 FF F8 */	stwu r1, -8(r1)
/* 802F5E6C 002F2A4C  38 A0 00 00 */	li r5, 0
lbl_802F5E70:
/* 802F5E70 002F2A50  80 06 00 04 */	lwz r0, 4(r6)
/* 802F5E74 002F2A54  7C 00 18 40 */	cmplw r0, r3
/* 802F5E78 002F2A58  40 82 00 18 */	bne lbl_802F5E90
/* 802F5E7C 002F2A5C  1C C5 00 64 */	mulli r6, r5, 0x64
/* 802F5E80 002F2A60  3C A0 80 4A */	lis r5, lbl_804A10C8@ha
/* 802F5E84 002F2A64  38 05 10 C8 */	addi r0, r5, lbl_804A10C8@l
/* 802F5E88 002F2A68  7C A0 32 14 */	add r5, r0, r6
/* 802F5E8C 002F2A6C  48 00 00 14 */	b lbl_802F5EA0
lbl_802F5E90:
/* 802F5E90 002F2A70  38 C6 00 64 */	addi r6, r6, 0x64
/* 802F5E94 002F2A74  38 A5 00 01 */	addi r5, r5, 1
/* 802F5E98 002F2A78  42 00 FF D8 */	bdnz lbl_802F5E70
/* 802F5E9C 002F2A7C  38 A0 00 00 */	li r5, 0
lbl_802F5EA0:
/* 802F5EA0 002F2A80  88 05 00 10 */	lbz r0, 0x10(r5)
/* 802F5EA4 002F2A84  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 802F5EA8 002F2A88  40 82 00 08 */	bne lbl_802F5EB0
/* 802F5EAC 002F2A8C  48 09 B1 C5 */	bl func_80391070
lbl_802F5EB0:
/* 802F5EB0 002F2A90  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802F5EB4 002F2A94  38 21 00 08 */	addi r1, r1, 8
/* 802F5EB8 002F2A98  7C 08 03 A6 */	mtlr r0
/* 802F5EBC 002F2A9C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_802F3424();

#pragma push
asm unk_t func_802F5EC0()
{ // clang-format off
    nofralloc
/* 802F5EC0 002F2AA0  7C 08 02 A6 */	mflr r0
/* 802F5EC4 002F2AA4  90 01 00 04 */	stw r0, 4(r1)
/* 802F5EC8 002F2AA8  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 802F5ECC 002F2AAC  BF 41 00 38 */	stmw r26, 0x38(r1)
/* 802F5ED0 002F2AB0  7C 7C 1B 78 */	mr r28, r3
/* 802F5ED4 002F2AB4  3B A4 00 00 */	addi r29, r4, 0
/* 802F5ED8 002F2AB8  80 A3 00 00 */	lwz r5, 0(r3)
/* 802F5EDC 002F2ABC  3C 60 80 4A */	lis r3, lbl_804A10C8@ha
/* 802F5EE0 002F2AC0  3B 63 10 C8 */	addi r27, r3, lbl_804A10C8@l
/* 802F5EE4 002F2AC4  28 05 00 00 */	cmplwi r5, 0
/* 802F5EE8 002F2AC8  40 82 00 80 */	bne lbl_802F5F68
/* 802F5EEC 002F2ACC  38 60 00 0E */	li r3, 0xe
/* 802F5EF0 002F2AD0  38 80 00 0F */	li r4, 0xf
/* 802F5EF4 002F2AD4  38 A0 00 00 */	li r5, 0
/* 802F5EF8 002F2AD8  48 09 A2 F9 */	bl func_803901F0
/* 802F5EFC 002F2ADC  7C 60 1B 78 */	mr r0, r3
/* 802F5F00 002F2AE0  80 7B 02 58 */	lwz r3, 0x258(r27)
/* 802F5F04 002F2AE4  7C 1F 03 78 */	mr r31, r0
/* 802F5F08 002F2AE8  48 07 AF 3D */	bl HSD_JObjLoadJoint
/* 802F5F0C 002F2AEC  3B C3 00 00 */	addi r30, r3, 0
/* 802F5F10 002F2AF0  88 8D C1 A9 */	lbz r4, lbl_804D7849(r13)
/* 802F5F14 002F2AF4  38 7F 00 00 */	addi r3, r31, 0
/* 802F5F18 002F2AF8  38 BE 00 00 */	addi r5, r30, 0
/* 802F5F1C 002F2AFC  48 09 AB 55 */	bl func_80390A70
/* 802F5F20 002F2B00  3C 60 80 2F */	lis r3, lbl_802F5DE0@ha
/* 802F5F24 002F2B04  38 83 5D E0 */	addi r4, r3, lbl_802F5DE0@l
/* 802F5F28 002F2B08  38 7F 00 00 */	addi r3, r31, 0
/* 802F5F2C 002F2B0C  38 A0 00 0B */	li r5, 0xb
/* 802F5F30 002F2B10  38 C0 00 00 */	li r6, 0
/* 802F5F34 002F2B14  48 09 A7 69 */	bl GObj_SetupGXLink
/* 802F5F38 002F2B18  3C 60 80 2F */	lis r3, func_802F5B48@ha
/* 802F5F3C 002F2B1C  38 83 5B 48 */	addi r4, r3, func_802F5B48@l
/* 802F5F40 002F2B20  38 7F 00 00 */	addi r3, r31, 0
/* 802F5F44 002F2B24  38 A0 00 11 */	li r5, 0x11
/* 802F5F48 002F2B28  48 09 9E 0D */	bl func_8038FD54
/* 802F5F4C 002F2B2C  3C 60 80 2F */	lis r3, func_802F4EDC@ha
/* 802F5F50 002F2B30  38 83 4E DC */	addi r4, r3, func_802F4EDC@l
/* 802F5F54 002F2B34  38 7F 00 00 */	addi r3, r31, 0
/* 802F5F58 002F2B38  38 A0 00 11 */	li r5, 0x11
/* 802F5F5C 002F2B3C  48 09 9D F9 */	bl func_8038FD54
/* 802F5F60 002F2B40  93 FC 00 00 */	stw r31, 0(r28)
/* 802F5F64 002F2B44  48 00 00 08 */	b lbl_802F5F6C
lbl_802F5F68:
/* 802F5F68 002F2B48  83 C5 00 28 */	lwz r30, 0x28(r5)
lbl_802F5F6C:
/* 802F5F6C 002F2B4C  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F5F70 002F2B50  38 60 00 00 */	li r3, 0
/* 802F5F74 002F2B54  50 60 0F 7C */	rlwimi r0, r3, 1, 0x1d, 0x1e
/* 802F5F78 002F2B58  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F5F7C 002F2B5C  7F C3 F3 78 */	mr r3, r30
/* 802F5F80 002F2B60  48 07 96 C5 */	bl HSD_JObjRemoveAnim
/* 802F5F84 002F2B64  3B FB 02 60 */	addi r31, r27, 0x260
/* 802F5F88 002F2B68  80 BB 02 5C */	lwz r5, 0x25c(r27)
/* 802F5F8C 002F2B6C  80 DB 02 60 */	lwz r6, 0x260(r27)
/* 802F5F90 002F2B70  7F C3 F3 78 */	mr r3, r30
/* 802F5F94 002F2B74  80 FB 02 64 */	lwz r7, 0x264(r27)
/* 802F5F98 002F2B78  38 80 00 00 */	li r4, 0
/* 802F5F9C 002F2B7C  4B D1 60 E1 */	bl func_8000C07C
/* 802F5FA0 002F2B80  7F C3 F3 78 */	mr r3, r30
/* 802F5FA4 002F2B84  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F5FA8 002F2B88  48 07 99 15 */	bl HSD_JObjReqAnimAll
/* 802F5FAC 002F2B8C  7F C3 F3 78 */	mr r3, r30
/* 802F5FB0 002F2B90  48 07 A9 79 */	bl HSD_JObjAnimAll
/* 802F5FB4 002F2B94  57 A3 06 3E */	clrlwi r3, r29, 0x18
/* 802F5FB8 002F2B98  4B FF D4 6D */	bl func_802F3424
/* 802F5FBC 002F2B9C  28 1E 00 00 */	cmplwi r30, 0
/* 802F5FC0 002F2BA0  3B A3 00 00 */	addi r29, r3, 0
/* 802F5FC4 002F2BA4  40 82 00 14 */	bne lbl_802F5FD8
/* 802F5FC8 002F2BA8  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F5FCC 002F2BAC  38 80 03 94 */	li r4, 0x394
/* 802F5FD0 002F2BB0  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F5FD4 002F2BB4  48 09 22 4D */	bl __assert
lbl_802F5FD8:
/* 802F5FD8 002F2BB8  28 1D 00 00 */	cmplwi r29, 0
/* 802F5FDC 002F2BBC  40 82 00 18 */	bne lbl_802F5FF4
/* 802F5FE0 002F2BC0  3C 60 80 40 */	lis r3, lbl_803F95C0@ha
/* 802F5FE4 002F2BC4  38 A3 95 C0 */	addi r5, r3, lbl_803F95C0@l
/* 802F5FE8 002F2BC8  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F5FEC 002F2BCC  38 80 03 95 */	li r4, 0x395
/* 802F5FF0 002F2BD0  48 09 22 31 */	bl __assert
lbl_802F5FF4:
/* 802F5FF4 002F2BD4  80 7D 00 00 */	lwz r3, 0(r29)
/* 802F5FF8 002F2BD8  80 1D 00 04 */	lwz r0, 4(r29)
/* 802F5FFC 002F2BDC  90 7E 00 38 */	stw r3, 0x38(r30)
/* 802F6000 002F2BE0  90 1E 00 3C */	stw r0, 0x3c(r30)
/* 802F6004 002F2BE4  80 1D 00 08 */	lwz r0, 8(r29)
/* 802F6008 002F2BE8  90 1E 00 40 */	stw r0, 0x40(r30)
/* 802F600C 002F2BEC  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802F6010 002F2BF0  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F6014 002F2BF4  40 82 00 4C */	bne lbl_802F6060
/* 802F6018 002F2BF8  28 1E 00 00 */	cmplwi r30, 0
/* 802F601C 002F2BFC  41 82 00 44 */	beq lbl_802F6060
/* 802F6020 002F2C00  40 82 00 14 */	bne lbl_802F6034
/* 802F6024 002F2C04  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F6028 002F2C08  38 80 02 34 */	li r4, 0x234
/* 802F602C 002F2C0C  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F6030 002F2C10  48 09 21 F1 */	bl __assert
lbl_802F6034:
/* 802F6034 002F2C14  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802F6038 002F2C18  38 60 00 00 */	li r3, 0
/* 802F603C 002F2C1C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F6040 002F2C20  40 82 00 10 */	bne lbl_802F6050
/* 802F6044 002F2C24  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F6048 002F2C28  41 82 00 08 */	beq lbl_802F6050
/* 802F604C 002F2C2C  38 60 00 01 */	li r3, 1
lbl_802F6050:
/* 802F6050 002F2C30  2C 03 00 00 */	cmpwi r3, 0
/* 802F6054 002F2C34  40 82 00 0C */	bne lbl_802F6060
/* 802F6058 002F2C38  7F C3 F3 78 */	mr r3, r30
/* 802F605C 002F2C3C  48 07 D2 8D */	bl HSD_JObjSetMtxDirtySub
lbl_802F6060:
/* 802F6060 002F2C40  3B BC 00 00 */	addi r29, r28, 0
/* 802F6064 002F2C44  3B 7E 00 00 */	addi r27, r30, 0
/* 802F6068 002F2C48  3B 40 00 00 */	li r26, 0
lbl_802F606C:
/* 802F606C 002F2C4C  38 7B 00 00 */	addi r3, r27, 0
/* 802F6070 002F2C50  38 9A 00 00 */	addi r4, r26, 0
/* 802F6074 002F2C54  48 00 01 21 */	bl func_802F6194
/* 802F6078 002F2C58  90 7D 00 54 */	stw r3, 0x54(r29)
/* 802F607C 002F2C5C  83 DD 00 54 */	lwz r30, 0x54(r29)
/* 802F6080 002F2C60  28 1E 00 00 */	cmplwi r30, 0
/* 802F6084 002F2C64  40 82 00 14 */	bne lbl_802F6098
/* 802F6088 002F2C68  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F608C 002F2C6C  38 80 03 E1 */	li r4, 0x3e1
/* 802F6090 002F2C70  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F6094 002F2C74  48 09 21 8D */	bl __assert
lbl_802F6098:
/* 802F6098 002F2C78  C0 1E 00 38 */	lfs f0, 0x38(r30)
/* 802F609C 002F2C7C  D0 1D 00 14 */	stfs f0, 0x14(r29)
/* 802F60A0 002F2C80  83 DD 00 54 */	lwz r30, 0x54(r29)
/* 802F60A4 002F2C84  28 1E 00 00 */	cmplwi r30, 0
/* 802F60A8 002F2C88  40 82 00 14 */	bne lbl_802F60BC
/* 802F60AC 002F2C8C  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F60B0 002F2C90  38 80 03 EE */	li r4, 0x3ee
/* 802F60B4 002F2C94  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F60B8 002F2C98  48 09 21 69 */	bl __assert
lbl_802F60BC:
/* 802F60BC 002F2C9C  C0 1E 00 3C */	lfs f0, 0x3c(r30)
/* 802F60C0 002F2CA0  3B 5A 00 01 */	addi r26, r26, 1
/* 802F60C4 002F2CA4  2C 1A 00 04 */	cmpwi r26, 4
/* 802F60C8 002F2CA8  D0 1D 00 24 */	stfs f0, 0x24(r29)
/* 802F60CC 002F2CAC  3B BD 00 04 */	addi r29, r29, 4
/* 802F60D0 002F2CB0  41 80 FF 9C */	blt lbl_802F606C
/* 802F60D4 002F2CB4  80 9C 00 60 */	lwz r4, 0x60(r28)
/* 802F60D8 002F2CB8  28 04 00 00 */	cmplwi r4, 0
/* 802F60DC 002F2CBC  41 82 00 7C */	beq lbl_802F6158
/* 802F60E0 002F2CC0  80 7F 00 00 */	lwz r3, 0(r31)
/* 802F60E4 002F2CC4  80 84 00 18 */	lwz r4, 0x18(r4)
/* 802F60E8 002F2CC8  80 63 00 00 */	lwz r3, 0(r3)
/* 802F60EC 002F2CCC  80 84 00 08 */	lwz r4, 8(r4)
/* 802F60F0 002F2CD0  80 63 00 00 */	lwz r3, 0(r3)
/* 802F60F4 002F2CD4  83 64 00 08 */	lwz r27, 8(r4)
/* 802F60F8 002F2CD8  80 83 00 04 */	lwz r4, 4(r3)
/* 802F60FC 002F2CDC  7F 63 DB 78 */	mr r3, r27
/* 802F6100 002F2CE0  80 84 00 04 */	lwz r4, 4(r4)
/* 802F6104 002F2CE4  80 84 00 04 */	lwz r4, 4(r4)
/* 802F6108 002F2CE8  80 84 00 08 */	lwz r4, 8(r4)
/* 802F610C 002F2CEC  80 84 00 08 */	lwz r4, 8(r4)
/* 802F6110 002F2CF0  48 06 85 F9 */	bl HSD_TObjAddAnimAll
/* 802F6114 002F2CF4  88 7C 00 08 */	lbz r3, 8(r28)
/* 802F6118 002F2CF8  7C 63 07 74 */	extsb r3, r3
/* 802F611C 002F2CFC  4B D3 E5 19 */	bl Player_GetMoreFlagsBit2
/* 802F6120 002F2D00  2C 03 00 00 */	cmpwi r3, 0
/* 802F6124 002F2D04  41 82 00 14 */	beq lbl_802F6138
/* 802F6128 002F2D08  7F 63 DB 78 */	mr r3, r27
/* 802F612C 002F2D0C  C0 22 E0 68 */	lfs f1, lbl_804DDA48(r2)
/* 802F6130 002F2D10  48 06 86 D1 */	bl HSD_TObjReqAnimAll
/* 802F6134 002F2D14  48 00 00 10 */	b lbl_802F6144
lbl_802F6138:
/* 802F6138 002F2D18  7F 63 DB 78 */	mr r3, r27
/* 802F613C 002F2D1C  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F6140 002F2D20  48 06 86 C1 */	bl HSD_TObjReqAnimAll
lbl_802F6144:
/* 802F6144 002F2D24  80 7B 00 64 */	lwz r3, 0x64(r27)
/* 802F6148 002F2D28  C0 22 E0 6C */	lfs f1, lbl_804DDA4C(r2)
/* 802F614C 002F2D2C  48 06 F1 C1 */	bl HSD_AObjSetRate
/* 802F6150 002F2D30  7F 63 DB 78 */	mr r3, r27
/* 802F6154 002F2D34  48 06 8A 19 */	bl HSD_TObjAnim
lbl_802F6158:
/* 802F6158 002F2D38  80 7C 00 00 */	lwz r3, 0(r28)
/* 802F615C 002F2D3C  4B FF F9 ED */	bl func_802F5B48
/* 802F6160 002F2D40  A8 1C 00 0A */	lha r0, 0xa(r28)
/* 802F6164 002F2D44  7C 00 00 34 */	cntlzw r0, r0
/* 802F6168 002F2D48  54 00 D9 7E */	srwi r0, r0, 5
/* 802F616C 002F2D4C  7C 00 07 34 */	extsh r0, r0
/* 802F6170 002F2D50  B0 1C 00 0C */	sth r0, 0xc(r28)
/* 802F6174 002F2D54  80 7C 00 00 */	lwz r3, 0(r28)
/* 802F6178 002F2D58  4B FF ED 65 */	bl func_802F4EDC
/* 802F617C 002F2D5C  80 7C 00 00 */	lwz r3, 0(r28)
/* 802F6180 002F2D60  BB 41 00 38 */	lmw r26, 0x38(r1)
/* 802F6184 002F2D64  80 01 00 54 */	lwz r0, 0x54(r1)
/* 802F6188 002F2D68  38 21 00 50 */	addi r1, r1, 0x50
/* 802F618C 002F2D6C  7C 08 03 A6 */	mtlr r0
/* 802F6190 002F2D70  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#ifdef NON_MATCHING

inline HSD_GObj* nth_node(HSD_GObj* node, s32 n)
{
    s32 i;
    HSD_GObj* cur = node;
    for (i = 0; i < n && node; i++) {
        if (cur == NULL) { // if (node == NULL)
            cur = NULL;
        } else {
            cur = node->next;
        }
        node = cur;
    }
    return node;
}

// 99.81% match
// https://decomp.me/scratch/XGFpw
HSD_GObj* func_802F6194(HSD_GObj* node, s32 n)
{
    HSD_GObj* gx;

    if ((node == NULL) || (n < 0)) {
        return NULL;
    }
    if (node == NULL) {
        gx = NULL;
    } else {
        gx = node->next_gx;
    }
    gx = nth_node(gx, n);
    return gx;
}

#else

#pragma push
asm HSD_GObj* func_802F6194(HSD_GObj*, s32)
{ // clang-format off
    nofralloc
/* 802F6194 002F2D74  28 03 00 00 */	cmplwi r3, 0
/* 802F6198 002F2D78  41 82 00 0C */	beq lbl_802F61A4
/* 802F619C 002F2D7C  2C 04 00 00 */	cmpwi r4, 0
/* 802F61A0 002F2D80  40 80 00 0C */	bge lbl_802F61AC
lbl_802F61A4:
/* 802F61A4 002F2D84  38 60 00 00 */	li r3, 0
/* 802F61A8 002F2D88  4E 80 00 20 */	blr 
lbl_802F61AC:
/* 802F61AC 002F2D8C  28 03 00 00 */	cmplwi r3, 0
/* 802F61B0 002F2D90  40 82 00 0C */	bne lbl_802F61BC
/* 802F61B4 002F2D94  38 00 00 00 */	li r0, 0
/* 802F61B8 002F2D98  48 00 00 08 */	b lbl_802F61C0
lbl_802F61BC:
/* 802F61BC 002F2D9C  80 03 00 10 */	lwz r0, 0x10(r3)
lbl_802F61C0:
/* 802F61C0 002F2DA0  7C 03 03 78 */	mr r3, r0
/* 802F61C4 002F2DA4  38 A0 00 00 */	li r5, 0
/* 802F61C8 002F2DA8  48 00 00 20 */	b lbl_802F61E8
lbl_802F61CC:
/* 802F61CC 002F2DAC  28 03 00 00 */	cmplwi r3, 0
/* 802F61D0 002F2DB0  40 82 00 0C */	bne lbl_802F61DC
/* 802F61D4 002F2DB4  38 00 00 00 */	li r0, 0
/* 802F61D8 002F2DB8  48 00 00 08 */	b lbl_802F61E0
lbl_802F61DC:
/* 802F61DC 002F2DBC  80 03 00 08 */	lwz r0, 8(r3)
lbl_802F61E0:
/* 802F61E0 002F2DC0  7C 03 03 78 */	mr r3, r0
/* 802F61E4 002F2DC4  38 A5 00 01 */	addi r5, r5, 1
lbl_802F61E8:
/* 802F61E8 002F2DC8  7C 05 20 00 */	cmpw r5, r4
/* 802F61EC 002F2DCC  4C 80 00 20 */	bgelr 
/* 802F61F0 002F2DD0  28 03 00 00 */	cmplwi r3, 0
/* 802F61F4 002F2DD4  40 82 FF D8 */	bne lbl_802F61CC
/* 802F61F8 002F2DD8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif

extern char* lbl_803F9598;
extern char* lbl_804D57C0;
extern f32 lbl_804DDA9C;
extern f64 lbl_804DDAA0;
extern unk_t func_80160968();
extern unk_t func_80160854();
extern unk_t func_80168B34();
extern unk_t func_802F3690();
extern unk_t func_802F98E8();
extern unk_t func_802FF364();

#pragma push
asm unk_t func_802F61FC()
{ // clang-format off
    nofralloc
/* 802F61FC 002F2DDC  7C 08 02 A6 */	mflr r0
/* 802F6200 002F2DE0  3C C0 80 40 */	lis r6, lbl_803F9598@ha
/* 802F6204 002F2DE4  90 01 00 04 */	stw r0, 4(r1)
/* 802F6208 002F2DE8  3C A0 80 4A */	lis r5, lbl_804A10C8@ha
/* 802F620C 002F2DEC  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 802F6210 002F2DF0  BF 21 00 2C */	stmw r25, 0x2c(r1)
/* 802F6214 002F2DF4  54 9F 06 3E */	clrlwi r31, r4, 0x18
/* 802F6218 002F2DF8  3B A3 00 00 */	addi r29, r3, 0
/* 802F621C 002F2DFC  38 7F 00 00 */	addi r3, r31, 0
/* 802F6220 002F2E00  3B 66 95 98 */	addi r27, r6, lbl_803F9598@l
/* 802F6224 002F2E04  3B 45 10 C8 */	addi r26, r5, lbl_804A10C8@l
/* 802F6228 002F2E08  4B D3 C1 09 */	bl Player_GetPlayerCharacter
/* 802F622C 002F2E0C  80 9D 00 04 */	lwz r4, 4(r29)
/* 802F6230 002F2E10  3B 83 00 00 */	addi r28, r3, 0
/* 802F6234 002F2E14  28 04 00 00 */	cmplwi r4, 0
/* 802F6238 002F2E18  40 82 00 98 */	bne lbl_802F62D0
/* 802F623C 002F2E1C  4B FF D4 55 */	bl func_802F3690
/* 802F6240 002F2E20  38 60 00 0E */	li r3, 0xe
/* 802F6244 002F2E24  38 80 00 0F */	li r4, 0xf
/* 802F6248 002F2E28  38 A0 00 00 */	li r5, 0
/* 802F624C 002F2E2C  48 09 9F A5 */	bl func_803901F0
/* 802F6250 002F2E30  7C 79 1B 79 */	or. r25, r3, r3
/* 802F6254 002F2E34  40 82 00 20 */	bne lbl_802F6274
/* 802F6258 002F2E38  38 7B 00 34 */	addi r3, r27, 0x34
/* 802F625C 002F2E3C  4C C6 31 82 */	crclr 6
/* 802F6260 002F2E40  48 04 F4 49 */	bl OSReport
/* 802F6264 002F2E44  38 7B 00 5C */	addi r3, r27, 0x5c
/* 802F6268 002F2E48  38 80 03 0A */	li r4, 0x30a
/* 802F626C 002F2E4C  38 AD A1 20 */	addi r5, r13, lbl_804D57C0
/* 802F6270 002F2E50  48 09 1F B1 */	bl __assert
lbl_802F6274:
/* 802F6274 002F2E54  80 7A 02 68 */	lwz r3, 0x268(r26)
/* 802F6278 002F2E58  48 07 AB CD */	bl HSD_JObjLoadJoint
/* 802F627C 002F2E5C  7C 7E 1B 79 */	or. r30, r3, r3
/* 802F6280 002F2E60  40 82 00 20 */	bne lbl_802F62A0
/* 802F6284 002F2E64  38 7B 00 68 */	addi r3, r27, 0x68
/* 802F6288 002F2E68  4C C6 31 82 */	crclr 6
/* 802F628C 002F2E6C  48 04 F4 1D */	bl OSReport
/* 802F6290 002F2E70  38 7B 00 5C */	addi r3, r27, 0x5c
/* 802F6294 002F2E74  38 80 03 0E */	li r4, 0x30e
/* 802F6298 002F2E78  38 AD A1 20 */	addi r5, r13, lbl_804D57C0
/* 802F629C 002F2E7C  48 09 1F 85 */	bl __assert
lbl_802F62A0:
/* 802F62A0 002F2E80  88 8D C1 A9 */	lbz r4, lbl_804D7849(r13)
/* 802F62A4 002F2E84  38 79 00 00 */	addi r3, r25, 0
/* 802F62A8 002F2E88  38 BE 00 00 */	addi r5, r30, 0
/* 802F62AC 002F2E8C  48 09 A7 C5 */	bl func_80390A70
/* 802F62B0 002F2E90  3C 60 80 2F */	lis r3, lbl_802F5E50@ha
/* 802F62B4 002F2E94  38 83 5E 50 */	addi r4, r3, lbl_802F5E50@l
/* 802F62B8 002F2E98  38 79 00 00 */	addi r3, r25, 0
/* 802F62BC 002F2E9C  38 A0 00 0B */	li r5, 0xb
/* 802F62C0 002F2EA0  38 C0 00 00 */	li r6, 0
/* 802F62C4 002F2EA4  48 09 A3 D9 */	bl GObj_SetupGXLink
/* 802F62C8 002F2EA8  93 3D 00 04 */	stw r25, 4(r29)
/* 802F62CC 002F2EAC  48 00 00 08 */	b lbl_802F62D4
lbl_802F62D0:
/* 802F62D0 002F2EB0  83 C4 00 28 */	lwz r30, 0x28(r4)
lbl_802F62D4:
/* 802F62D4 002F2EB4  80 DE 00 10 */	lwz r6, 0x10(r30)
/* 802F62D8 002F2EB8  7F C3 F3 78 */	mr r3, r30
/* 802F62DC 002F2EBC  80 BA 02 6C */	lwz r5, 0x26c(r26)
/* 802F62E0 002F2EC0  38 80 00 00 */	li r4, 0
/* 802F62E4 002F2EC4  80 E6 00 18 */	lwz r7, 0x18(r6)
/* 802F62E8 002F2EC8  80 DA 02 70 */	lwz r6, 0x270(r26)
/* 802F62EC 002F2ECC  81 07 00 08 */	lwz r8, 8(r7)
/* 802F62F0 002F2ED0  80 FA 02 74 */	lwz r7, 0x274(r26)
/* 802F62F4 002F2ED4  83 48 00 08 */	lwz r26, 8(r8)
/* 802F62F8 002F2ED8  4B D1 5D 85 */	bl func_8000C07C
/* 802F62FC 002F2EDC  2C 1C 00 1A */	cmpwi r28, 0x1a
/* 802F6300 002F2EE0  41 82 00 10 */	beq lbl_802F6310
/* 802F6304 002F2EE4  38 1C FF E3 */	addi r0, r28, -29
/* 802F6308 002F2EE8  28 00 00 01 */	cmplwi r0, 1
/* 802F630C 002F2EEC  41 81 00 08 */	bgt lbl_802F6314
lbl_802F6310:
/* 802F6310 002F2EF0  3B 80 00 1B */	li r28, 0x1b
lbl_802F6314:
/* 802F6314 002F2EF4  38 7C 00 00 */	addi r3, r28, 0
/* 802F6318 002F2EF8  38 80 00 00 */	li r4, 0
/* 802F631C 002F2EFC  38 A0 00 00 */	li r5, 0
/* 802F6320 002F2F00  4B E7 28 15 */	bl func_80168B34
/* 802F6324 002F2F04  C0 02 E0 B4 */	lfs f0, lbl_804DDA94(r2)
/* 802F6328 002F2F08  7F 43 D3 78 */	mr r3, r26
/* 802F632C 002F2F0C  EC 20 08 2A */	fadds f1, f0, f1
/* 802F6330 002F2F10  48 06 84 D1 */	bl HSD_TObjReqAnimAll
/* 802F6334 002F2F14  80 7A 00 64 */	lwz r3, 0x64(r26)
/* 802F6338 002F2F18  C0 22 E0 BC */	lfs f1, lbl_804DDA9C(r2)
/* 802F633C 002F2F1C  48 06 EF D1 */	bl HSD_AObjSetRate
/* 802F6340 002F2F20  7F 43 D3 78 */	mr r3, r26
/* 802F6344 002F2F24  48 06 88 29 */	bl HSD_TObjAnim
/* 802F6348 002F2F28  7F E3 FB 78 */	mr r3, r31
/* 802F634C 002F2F2C  4B FF D0 D9 */	bl func_802F3424
/* 802F6350 002F2F30  28 1E 00 00 */	cmplwi r30, 0
/* 802F6354 002F2F34  3B 43 00 00 */	addi r26, r3, 0
/* 802F6358 002F2F38  40 82 00 14 */	bne lbl_802F636C
/* 802F635C 002F2F3C  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F6360 002F2F40  38 80 03 94 */	li r4, 0x394
/* 802F6364 002F2F44  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F6368 002F2F48  48 09 1E B9 */	bl __assert
lbl_802F636C:
/* 802F636C 002F2F4C  28 1A 00 00 */	cmplwi r26, 0
/* 802F6370 002F2F50  40 82 00 14 */	bne lbl_802F6384
/* 802F6374 002F2F54  38 BB 00 28 */	addi r5, r27, 0x28
/* 802F6378 002F2F58  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F637C 002F2F5C  38 80 03 95 */	li r4, 0x395
/* 802F6380 002F2F60  48 09 1E A1 */	bl __assert
lbl_802F6384:
/* 802F6384 002F2F64  80 7A 00 00 */	lwz r3, 0(r26)
/* 802F6388 002F2F68  80 1A 00 04 */	lwz r0, 4(r26)
/* 802F638C 002F2F6C  90 7E 00 38 */	stw r3, 0x38(r30)
/* 802F6390 002F2F70  90 1E 00 3C */	stw r0, 0x3c(r30)
/* 802F6394 002F2F74  80 1A 00 08 */	lwz r0, 8(r26)
/* 802F6398 002F2F78  90 1E 00 40 */	stw r0, 0x40(r30)
/* 802F639C 002F2F7C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802F63A0 002F2F80  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F63A4 002F2F84  40 82 00 4C */	bne lbl_802F63F0
/* 802F63A8 002F2F88  28 1E 00 00 */	cmplwi r30, 0
/* 802F63AC 002F2F8C  41 82 00 44 */	beq lbl_802F63F0
/* 802F63B0 002F2F90  40 82 00 14 */	bne lbl_802F63C4
/* 802F63B4 002F2F94  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F63B8 002F2F98  38 80 02 34 */	li r4, 0x234
/* 802F63BC 002F2F9C  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F63C0 002F2FA0  48 09 1E 61 */	bl __assert
lbl_802F63C4:
/* 802F63C4 002F2FA4  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802F63C8 002F2FA8  38 60 00 00 */	li r3, 0
/* 802F63CC 002F2FAC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F63D0 002F2FB0  40 82 00 10 */	bne lbl_802F63E0
/* 802F63D4 002F2FB4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F63D8 002F2FB8  41 82 00 08 */	beq lbl_802F63E0
/* 802F63DC 002F2FBC  38 60 00 01 */	li r3, 1
lbl_802F63E0:
/* 802F63E0 002F2FC0  2C 03 00 00 */	cmpwi r3, 0
/* 802F63E4 002F2FC4  40 82 00 0C */	bne lbl_802F63F0
/* 802F63E8 002F2FC8  7F C3 F3 78 */	mr r3, r30
/* 802F63EC 002F2FCC  48 07 CE FD */	bl HSD_JObjSetMtxDirtySub
lbl_802F63F0:
/* 802F63F0 002F2FD0  28 1E 00 00 */	cmplwi r30, 0
/* 802F63F4 002F2FD4  40 82 00 14 */	bne lbl_802F6408
/* 802F63F8 002F2FD8  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F63FC 002F2FDC  38 80 04 4E */	li r4, 0x44e
/* 802F6400 002F2FE0  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F6404 002F2FE4  48 09 1E 1D */	bl __assert
lbl_802F6408:
/* 802F6408 002F2FE8  C0 3E 00 38 */	lfs f1, 0x38(r30)
/* 802F640C 002F2FEC  C0 02 E0 C0 */	lfs f0, lbl_804DDAA0(r2)
/* 802F6410 002F2FF0  EC 01 00 2A */	fadds f0, f1, f0
/* 802F6414 002F2FF4  D0 1E 00 38 */	stfs f0, 0x38(r30)
/* 802F6418 002F2FF8  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 802F641C 002F2FFC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 802F6420 002F3000  40 82 00 4C */	bne lbl_802F646C
/* 802F6424 002F3004  28 1E 00 00 */	cmplwi r30, 0
/* 802F6428 002F3008  41 82 00 44 */	beq lbl_802F646C
/* 802F642C 002F300C  40 82 00 14 */	bne lbl_802F6440
/* 802F6430 002F3010  38 6D A1 10 */	addi r3, r13, lbl_804D57B0
/* 802F6434 002F3014  38 80 02 34 */	li r4, 0x234
/* 802F6438 002F3018  38 AD A1 18 */	addi r5, r13, lbl_804D57B8
/* 802F643C 002F301C  48 09 1D E5 */	bl __assert
lbl_802F6440:
/* 802F6440 002F3020  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 802F6444 002F3024  38 60 00 00 */	li r3, 0
/* 802F6448 002F3028  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 802F644C 002F302C  40 82 00 10 */	bne lbl_802F645C
/* 802F6450 002F3030  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 802F6454 002F3034  41 82 00 08 */	beq lbl_802F645C
/* 802F6458 002F3038  38 60 00 01 */	li r3, 1
lbl_802F645C:
/* 802F645C 002F303C  2C 03 00 00 */	cmpwi r3, 0
/* 802F6460 002F3040  40 82 00 0C */	bne lbl_802F646C
/* 802F6464 002F3044  7F C3 F3 78 */	mr r3, r30
/* 802F6468 002F3048  48 07 CE 81 */	bl HSD_JObjSetMtxDirtySub
lbl_802F646C:
/* 802F646C 002F304C  7F E3 FB 78 */	mr r3, r31
/* 802F6470 002F3050  4B D3 BF AD */	bl Player_GetPlayerSlotType
/* 802F6474 002F3054  54 7A 06 3E */	clrlwi r26, r3, 0x18
/* 802F6478 002F3058  4B E7 4C F1 */	bl func_8016B168
/* 802F647C 002F305C  54 7B 06 3E */	clrlwi r27, r3, 0x18
/* 802F6480 002F3060  38 7F 00 00 */	addi r3, r31, 0
/* 802F6484 002F3064  4B D3 CE ED */	bl Player_GetTeam
/* 802F6488 002F3068  54 7C 06 3E */	clrlwi r28, r3, 0x18
/* 802F648C 002F306C  38 7F 00 00 */	addi r3, r31, 0
/* 802F6490 002F3070  4B D3 CF CD */	bl Player_GetPlayerId
/* 802F6494 002F3074  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 802F6498 002F3078  38 9C 00 00 */	addi r4, r28, 0
/* 802F649C 002F307C  38 BB 00 00 */	addi r5, r27, 0
/* 802F64A0 002F3080  38 DA 00 00 */	addi r6, r26, 0
/* 802F64A4 002F3084  4B E6 A3 B1 */	bl func_80160854
/* 802F64A8 002F3088  4B E6 A4 C1 */	bl func_80160968
/* 802F64AC 002F308C  28 1E 00 00 */	cmplwi r30, 0
/* 802F64B0 002F3090  90 61 00 20 */	stw r3, 0x20(r1)
/* 802F64B4 002F3094  40 82 00 0C */	bne lbl_802F64C0
/* 802F64B8 002F3098  38 60 00 00 */	li r3, 0
/* 802F64BC 002F309C  48 00 00 08 */	b lbl_802F64C4
lbl_802F64C0:
/* 802F64C0 002F30A0  80 7E 00 10 */	lwz r3, 0x10(r30)
lbl_802F64C4:
/* 802F64C4 002F30A4  80 63 00 18 */	lwz r3, 0x18(r3)
/* 802F64C8 002F30A8  88 01 00 20 */	lbz r0, 0x20(r1)
/* 802F64CC 002F30AC  80 83 00 08 */	lwz r4, 8(r3)
/* 802F64D0 002F30B0  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F64D4 002F30B4  98 03 00 04 */	stb r0, 4(r3)
/* 802F64D8 002F30B8  88 01 00 21 */	lbz r0, 0x21(r1)
/* 802F64DC 002F30BC  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F64E0 002F30C0  98 03 00 05 */	stb r0, 5(r3)
/* 802F64E4 002F30C4  88 01 00 22 */	lbz r0, 0x22(r1)
/* 802F64E8 002F30C8  80 64 00 0C */	lwz r3, 0xc(r4)
/* 802F64EC 002F30CC  98 03 00 06 */	stb r0, 6(r3)
/* 802F64F0 002F30D0  80 7D 00 04 */	lwz r3, 4(r29)
/* 802F64F4 002F30D4  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 802F64F8 002F30D8  BB 21 00 2C */	lmw r25, 0x2c(r1)
/* 802F64FC 002F30DC  38 21 00 48 */	addi r1, r1, 0x48
/* 802F6500 002F30E0  7C 08 03 A6 */	mtlr r0
/* 802F6504 002F30E4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_802F6508(s32)
{ // clang-format off
    nofralloc
/* 802F6508 002F30E8  7C 08 02 A6 */	mflr r0
/* 802F650C 002F30EC  90 01 00 04 */	stw r0, 4(r1)
/* 802F6510 002F30F0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802F6514 002F30F4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802F6518 002F30F8  7C 7F 1B 78 */	mr r31, r3
/* 802F651C 002F30FC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802F6520 002F3100  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802F6524 002F3104  93 81 00 10 */	stw r28, 0x10(r1)
/* 802F6528 002F3108  4B D3 BE F5 */	bl Player_GetPlayerSlotType
/* 802F652C 002F310C  2C 03 00 03 */	cmpwi r3, 3
/* 802F6530 002F3110  41 82 01 0C */	beq lbl_802F663C
/* 802F6534 002F3114  88 0D B6 C0 */	lbz r0, lbl_804D6D60(r13)
/* 802F6538 002F3118  7C 00 F8 00 */	cmpw r0, r31
/* 802F653C 002F311C  40 81 01 00 */	ble lbl_802F663C
/* 802F6540 002F3120  4B E7 49 11 */	bl func_8016AE50
/* 802F6544 002F3124  88 03 00 02 */	lbz r0, 2(r3)
/* 802F6548 002F3128  7C 7D 1B 78 */	mr r29, r3
/* 802F654C 002F312C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 802F6550 002F3130  41 82 00 EC */	beq lbl_802F663C
/* 802F6554 002F3134  57 FE 06 3E */	clrlwi r30, r31, 0x18
/* 802F6558 002F3138  1C 9E 00 64 */	mulli r4, r30, 0x64
/* 802F655C 002F313C  3C 60 80 4A */	lis r3, lbl_804A10C8@ha
/* 802F6560 002F3140  38 03 10 C8 */	addi r0, r3, lbl_804A10C8@l
/* 802F6564 002F3144  7F 80 22 14 */	add r28, r0, r4
/* 802F6568 002F3148  38 00 FF FF */	li r0, -1
/* 802F656C 002F314C  B0 1C 00 0A */	sth r0, 0xa(r28)
/* 802F6570 002F3150  38 A0 00 00 */	li r5, 0
/* 802F6574 002F3154  38 7C 00 00 */	addi r3, r28, 0
/* 802F6578 002F3158  B0 1C 00 0C */	sth r0, 0xc(r28)
/* 802F657C 002F315C  7F C4 F3 78 */	mr r4, r30
/* 802F6580 002F3160  98 BC 00 0F */	stb r5, 0xf(r28)
/* 802F6584 002F3164  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F6588 002F3168  50 A0 3E 30 */	rlwimi r0, r5, 7, 0x18, 0x18
/* 802F658C 002F316C  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F6590 002F3170  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F6594 002F3174  50 A0 36 72 */	rlwimi r0, r5, 6, 0x19, 0x19
/* 802F6598 002F3178  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F659C 002F317C  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F65A0 002F3180  50 A0 2E B4 */	rlwimi r0, r5, 5, 0x1a, 0x1a
/* 802F65A4 002F3184  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F65A8 002F3188  88 1C 00 10 */	lbz r0, 0x10(r28)
/* 802F65AC 002F318C  50 A0 26 F6 */	rlwimi r0, r5, 4, 0x1b, 0x1b
/* 802F65B0 002F3190  98 1C 00 10 */	stb r0, 0x10(r28)
/* 802F65B4 002F3194  9B FC 00 08 */	stb r31, 8(r28)
/* 802F65B8 002F3198  98 BC 00 09 */	stb r5, 9(r28)
/* 802F65BC 002F319C  4B FF FC 41 */	bl func_802F61FC
/* 802F65C0 002F31A0  38 7C 00 00 */	addi r3, r28, 0
/* 802F65C4 002F31A4  38 9E 00 00 */	addi r4, r30, 0
/* 802F65C8 002F31A8  4B FF F8 F9 */	bl func_802F5EC0
/* 802F65CC 002F31AC  88 1D 00 03 */	lbz r0, 3(r29)
/* 802F65D0 002F31B0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 802F65D4 002F31B4  41 82 00 18 */	beq lbl_802F65EC
/* 802F65D8 002F31B8  4B E7 4C 61 */	bl func_8016B238
/* 802F65DC 002F31BC  2C 03 00 00 */	cmpwi r3, 0
/* 802F65E0 002F31C0  40 82 00 0C */	bne lbl_802F65EC
/* 802F65E4 002F31C4  7F E3 FB 78 */	mr r3, r31
/* 802F65E8 002F31C8  48 00 8D 7D */	bl func_802FF364
lbl_802F65EC:
/* 802F65EC 002F31CC  88 7D 00 00 */	lbz r3, 0(r29)
/* 802F65F0 002F31D0  54 63 DF 7E */	rlwinm r3, r3, 0x1b, 0x1d, 0x1f
/* 802F65F4 002F31D4  28 03 00 01 */	cmplwi r3, 1
/* 802F65F8 002F31D8  41 82 00 10 */	beq lbl_802F6608
/* 802F65FC 002F31DC  88 1D 00 04 */	lbz r0, 4(r29)
/* 802F6600 002F31E0  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 802F6604 002F31E4  41 82 00 14 */	beq lbl_802F6618
lbl_802F6608:
/* 802F6608 002F31E8  57 E3 06 3E */	clrlwi r3, r31, 0x18
/* 802F660C 002F31EC  38 80 00 00 */	li r4, 0
/* 802F6610 002F31F0  48 00 32 D9 */	bl func_802F98E8
/* 802F6614 002F31F4  48 00 00 28 */	b lbl_802F663C
lbl_802F6618:
/* 802F6618 002F31F8  28 03 00 02 */	cmplwi r3, 2
/* 802F661C 002F31FC  40 82 00 14 */	bne lbl_802F6630
/* 802F6620 002F3200  57 E3 06 3E */	clrlwi r3, r31, 0x18
/* 802F6624 002F3204  38 80 00 02 */	li r4, 2
/* 802F6628 002F3208  48 00 32 C1 */	bl func_802F98E8
/* 802F662C 002F320C  48 00 00 10 */	b lbl_802F663C
lbl_802F6630:
/* 802F6630 002F3210  57 E3 06 3E */	clrlwi r3, r31, 0x18
/* 802F6634 002F3214  38 80 00 01 */	li r4, 1
/* 802F6638 002F3218  48 00 32 B1 */	bl func_802F98E8
lbl_802F663C:
/* 802F663C 002F321C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802F6640 002F3220  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802F6644 002F3224  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802F6648 002F3228  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802F664C 002F322C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802F6650 002F3230  38 21 00 20 */	addi r1, r1, 0x20
/* 802F6654 002F3234  7C 08 03 A6 */	mtlr r0
/* 802F6658 002F3238  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern s8 lbl_804D6D60;

void func_802F665C(s8 arg0)
{
    s32 i;

    func_802F343C();
    lbl_804D6D60 = arg0;
    for (i = 0; i < 6; i++) {
        func_802F6508(i);
    }
}

extern char* lbl_803F95AC;
extern unk_t func_80016AF0();

#pragma push
asm unk_t func_802F66A4()
{ // clang-format off
    nofralloc
/* 802F66A4 002F3284  7C 08 02 A6 */	mflr r0
/* 802F66A8 002F3288  3C 60 80 4A */	lis r3, lbl_804A10C8@ha
/* 802F66AC 002F328C  90 01 00 04 */	stw r0, 4(r1)
/* 802F66B0 002F3290  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802F66B4 002F3294  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802F66B8 002F3298  3B E3 10 C8 */	addi r31, r3, lbl_804A10C8@l
/* 802F66BC 002F329C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802F66C0 002F32A0  4B FF CF D1 */	bl func_802F3690
/* 802F66C4 002F32A4  3C A0 80 40 */	lis r5, lbl_803F9598@ha
/* 802F66C8 002F32A8  80 63 00 00 */	lwz r3, 0(r3)
/* 802F66CC 002F32AC  3C 80 80 40 */	lis r4, lbl_803F95AC@ha
/* 802F66D0 002F32B0  4C C6 31 82 */	crclr 6
/* 802F66D4 002F32B4  38 E4 95 AC */	addi r7, r4, lbl_803F95AC@l
/* 802F66D8 002F32B8  38 A5 95 98 */	addi r5, r5, lbl_803F9598@l
/* 802F66DC 002F32BC  38 81 00 08 */	addi r4, r1, 8
/* 802F66E0 002F32C0  38 C1 00 0C */	addi r6, r1, 0xc
/* 802F66E4 002F32C4  39 00 00 00 */	li r8, 0
/* 802F66E8 002F32C8  4B D2 04 09 */	bl func_80016AF0
/* 802F66EC 002F32CC  80 81 00 08 */	lwz r4, 8(r1)
/* 802F66F0 002F32D0  2C 1E 00 00 */	cmpwi r30, 0
/* 802F66F4 002F32D4  80 64 00 00 */	lwz r3, 0(r4)
/* 802F66F8 002F32D8  80 03 00 00 */	lwz r0, 0(r3)
/* 802F66FC 002F32DC  90 1F 02 58 */	stw r0, 0x258(r31)
/* 802F6700 002F32E0  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6704 002F32E4  80 03 00 04 */	lwz r0, 4(r3)
/* 802F6708 002F32E8  90 1F 02 5C */	stw r0, 0x25c(r31)
/* 802F670C 002F32EC  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6710 002F32F0  80 03 00 08 */	lwz r0, 8(r3)
/* 802F6714 002F32F4  90 1F 02 60 */	stw r0, 0x260(r31)
/* 802F6718 002F32F8  80 64 00 00 */	lwz r3, 0(r4)
/* 802F671C 002F32FC  80 03 00 0C */	lwz r0, 0xc(r3)
/* 802F6720 002F3300  90 1F 02 64 */	stw r0, 0x264(r31)
/* 802F6724 002F3304  80 81 00 0C */	lwz r4, 0xc(r1)
/* 802F6728 002F3308  80 64 00 00 */	lwz r3, 0(r4)
/* 802F672C 002F330C  80 03 00 00 */	lwz r0, 0(r3)
/* 802F6730 002F3310  90 1F 02 68 */	stw r0, 0x268(r31)
/* 802F6734 002F3314  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6738 002F3318  80 03 00 04 */	lwz r0, 4(r3)
/* 802F673C 002F331C  90 1F 02 6C */	stw r0, 0x26c(r31)
/* 802F6740 002F3320  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6744 002F3324  80 03 00 08 */	lwz r0, 8(r3)
/* 802F6748 002F3328  90 1F 02 70 */	stw r0, 0x270(r31)
/* 802F674C 002F332C  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6750 002F3330  80 03 00 0C */	lwz r0, 0xc(r3)
/* 802F6754 002F3334  90 1F 02 74 */	stw r0, 0x274(r31)
/* 802F6758 002F3338  41 82 00 18 */	beq lbl_802F6770
/* 802F675C 002F333C  38 00 00 00 */	li r0, 0
/* 802F6760 002F3340  98 0D B6 C0 */	stb r0, lbl_804D6D60(r13)
/* 802F6764 002F3344  38 7F 00 00 */	addi r3, r31, 0
/* 802F6768 002F3348  38 80 02 58 */	li r4, 0x258
/* 802F676C 002F334C  4B D1 59 F5 */	bl func_8000C160
lbl_802F6770:
/* 802F6770 002F3350  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802F6774 002F3354  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802F6778 002F3358  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802F677C 002F335C  38 21 00 20 */	addi r1, r1, 0x20
/* 802F6780 002F3360  7C 08 03 A6 */	mtlr r0
/* 802F6784 002F3364  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void func_802F6788(s32 player_idx)
{
    IfDamageState* player_hud;
    s8 p_idx = (u8) player_idx;
    player_hud = &lbl_804A10C8.players[p_idx & 0xFF];
    if (player_hud->HUD_parent_entity != NULL) {
        func_80390228(player_hud->HUD_parent_entity);
        player_hud->HUD_parent_entity = NULL;
    }
    if (player_hud->next != NULL) {
        func_80390228(player_hud->next);
        player_hud->next = NULL;
    }
    func_802FB650(player_idx & 0xFF);
}

void func_802F6804(void)
{
    s32 i;
    IfDamageState* v;

    i = 0;
    do {
        v = &lbl_804A10C8.players[i & 0xFF];
        if (v->HUD_parent_entity != NULL) {
            func_80390228(v->HUD_parent_entity);
            v->HUD_parent_entity = NULL;
        }
        if (v->next != NULL) {
            func_80390228(v->next);
            v->next = NULL;
        }
        func_802FB650((s8) i & 0xFF);
        i++;
    } while (i < 6);
}

// Hide Percentage Digits
void func_802F6898()
{
    s32 i;
    HudIndex* v = &lbl_804A10C8;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 1;
    }
}

// Show All Percentage Digits
void func_802F68F0(void)
{
    s32 i;
    HudIndex* v = &lbl_804A10C8;
    for (i = 0; i < 6; i++) {
        v->players[i].flags.hide_all_digits = 0;
    }
}

void func_802F6948(s32 player_idx)
{
    Placeholder_8016AE50_ret_val* small_thing = func_8016AE50();
    IfDamageState* hud_player = &lbl_804A10C8.players[player_idx];
    IfDamageFlags* hud_player_flags = &hud_player->flags;

    if (hud_player_flags->explode_animation != TRUE) {
        hud_player_flags->explode_animation = TRUE;
        hud_player_flags->randomize_velocity = TRUE;

        if (small_thing->flags.unk1)
            hud_player->unk9 = TRUE;
    }
}

void func_802F69C0(s32 player_idx, s32 arg1)
{
    IfDamageState* hud_player;
    IfDamageFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = func_8016AE38();
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0)) {
        func_802F7C30(arg1);
    }

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7BB4 != NULL)) {
        func_802F7BB4(player_idx);
    }
}

void func_802F6AF8(s32 player_idx)
{
    IfDamageState* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    IfDamageFlags* hud_player_flags;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7AF8 != NULL)) {
        func_802F7AF8(player_idx);
    }
}

void func_802F6C04(s32 player_idx)
{
    IfDamageState* hud_player;
    IfDamageFlags* hud_player_flags;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7C30 != NULL)) {
        func_802F7C30(player_idx);
    }
}

void func_802F6D10(s32 player_idx)
{
    IfDamageState* hud_player;
    Placeholder_8016AE38_ret_val* big_thing;
    Placeholder_8016AE50_ret_val* small_thing;
    IfDamageFlags* hud_player_flags;

    big_thing = func_8016AE38();
    big_thing->unkD = player_idx;
    small_thing = func_8016AE50();
    hud_player = &lbl_804A10C8.players[player_idx];
    hud_player_flags = &hud_player->flags;
    if (hud_player_flags->explode_animation != 1) {
        hud_player_flags->explode_animation = 1;
        hud_player_flags->randomize_velocity = 1;
        if (small_thing->flags.unk1 != 0) {
            hud_player->unk9 = 1;
        }
    }
    if ((big_thing->unk24CA.unk80 != 0) && ((Player_GetPlayerSlotType(player_idx) == 0) || (Player_GetPlayerSlotType(player_idx) == 1)) && (Player_GetStocks(player_idx) == 0)) {
        func_8016B8D4(player_idx, Player_GetPlayerSlotType(player_idx) & 0xFF);
    }
    if ((big_thing->unk24C8.top3 != 1U) && (big_thing->unk24CA.unk4 != 0) && (func_802F7D08 != NULL)) {
        func_802F7D08(player_idx);
    }
}

void func_802F6E1C(s32 player_num)
{
    func_802F6508(player_num);
}

void func_802F6E3C(s32 player_num)
{
    IfDamageState* player;

    player = &lbl_804A10C8.players[player_num];
    if (player->HUD_parent_entity != NULL) {
        func_80390CAC(player->HUD_parent_entity);
    }
    if (player->next != NULL) {
        func_80390CAC(player->next);
    }
    func_802FB6AC(player_num);
}

extern Thing_803F9628 lbl_803F9628;
extern f64 lbl_804DDAA8;
extern unk_t func_80011C18();

#pragma push
asm unk_t func_802F6EA4()
{ // clang-format off
    nofralloc
/* 802F6EA4 002F3A84  7C 08 02 A6 */	mflr r0
/* 802F6EA8 002F3A88  2C 03 00 08 */	cmpwi r3, 8
/* 802F6EAC 002F3A8C  90 01 00 04 */	stw r0, 4(r1)
/* 802F6EB0 002F3A90  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 802F6EB4 002F3A94  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 802F6EB8 002F3A98  3B A4 00 00 */	addi r29, r4, 0
/* 802F6EBC 002F3A9C  3B 85 00 00 */	addi r28, r5, 0
/* 802F6EC0 002F3AA0  3B C7 00 00 */	addi r30, r7, 0
/* 802F6EC4 002F3AA4  3B E8 00 00 */	addi r31, r8, 0
/* 802F6EC8 002F3AA8  40 82 00 68 */	bne lbl_802F6F30
/* 802F6ECC 002F3AAC  28 1E 00 00 */	cmplwi r30, 0
/* 802F6ED0 002F3AB0  41 82 00 14 */	beq lbl_802F6EE4
/* 802F6ED4 002F3AB4  39 9E 00 00 */	addi r12, r30, 0
/* 802F6ED8 002F3AB8  7D 88 03 A6 */	mtlr r12
/* 802F6EDC 002F3ABC  38 60 FF FF */	li r3, -1
/* 802F6EE0 002F3AC0  4E 80 00 21 */	blrl 
lbl_802F6EE4:
/* 802F6EE4 002F3AC4  28 1F 00 00 */	cmplwi r31, 0
/* 802F6EE8 002F3AC8  41 82 00 14 */	beq lbl_802F6EFC
/* 802F6EEC 002F3ACC  39 9F 00 00 */	addi r12, r31, 0
/* 802F6EF0 002F3AD0  7D 88 03 A6 */	mtlr r12
/* 802F6EF4 002F3AD4  38 60 FF FF */	li r3, -1
/* 802F6EF8 002F3AD8  4E 80 00 21 */	blrl 
lbl_802F6EFC:
/* 802F6EFC 002F3ADC  2C 1D 00 00 */	cmpwi r29, 0
/* 802F6F00 002F3AE0  41 80 00 14 */	blt lbl_802F6F14
/* 802F6F04 002F3AE4  38 7D 00 00 */	addi r3, r29, 0
/* 802F6F08 002F3AE8  38 80 00 7F */	li r4, 0x7f
/* 802F6F0C 002F3AEC  38 A0 00 40 */	li r5, 0x40
/* 802F6F10 002F3AF0  4B D2 C8 99 */	bl func_800237A8
lbl_802F6F14:
/* 802F6F14 002F3AF4  2C 1D 00 00 */	cmpwi r29, 0
/* 802F6F18 002F3AF8  41 80 01 08 */	blt lbl_802F7020
/* 802F6F1C 002F3AFC  38 7C 00 00 */	addi r3, r28, 0
/* 802F6F20 002F3B00  38 80 00 7F */	li r4, 0x7f
/* 802F6F24 002F3B04  38 A0 00 40 */	li r5, 0x40
/* 802F6F28 002F3B08  4B D2 C8 81 */	bl func_800237A8
/* 802F6F2C 002F3B0C  48 00 00 F4 */	b lbl_802F7020
lbl_802F6F30:
/* 802F6F30 002F3B10  1C 83 00 28 */	mulli r4, r3, 0x28
/* 802F6F34 002F3B14  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F6F38 002F3B18  38 03 96 28 */	addi r0, r3, lbl_803F9628@l
/* 802F6F3C 002F3B1C  7F 60 22 14 */	add r27, r0, r4
/* 802F6F40 002F3B20  93 BB 00 20 */	stw r29, 0x20(r27)
/* 802F6F44 002F3B24  93 9B 00 24 */	stw r28, 0x24(r27)
/* 802F6F48 002F3B28  98 DB 00 11 */	stb r6, 0x11(r27)
/* 802F6F4C 002F3B2C  80 7B 00 00 */	lwz r3, 0(r27)
/* 802F6F50 002F3B30  28 03 00 00 */	cmplwi r3, 0
/* 802F6F54 002F3B34  41 82 00 08 */	beq lbl_802F6F5C
/* 802F6F58 002F3B38  48 09 92 D1 */	bl func_80390228
lbl_802F6F5C:
/* 802F6F5C 002F3B3C  38 60 00 0E */	li r3, 0xe
/* 802F6F60 002F3B40  38 80 00 0E */	li r4, 0xe
/* 802F6F64 002F3B44  38 A0 00 00 */	li r5, 0
/* 802F6F68 002F3B48  48 09 92 89 */	bl func_803901F0
/* 802F6F6C 002F3B4C  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 802F6F70 002F3B50  7C 7D 1B 78 */	mr r29, r3
/* 802F6F74 002F3B54  80 64 00 00 */	lwz r3, 0(r4)
/* 802F6F78 002F3B58  48 07 9E CD */	bl HSD_JObjLoadJoint
/* 802F6F7C 002F3B5C  3B 83 00 00 */	addi r28, r3, 0
/* 802F6F80 002F3B60  3C 80 08 00 */	lis r4, 0x800
/* 802F6F84 002F3B64  4B D1 AC 95 */	bl func_80011C18
/* 802F6F88 002F3B68  88 8D C1 A9 */	lbz r4, lbl_804D7849(r13)
/* 802F6F8C 002F3B6C  38 7D 00 00 */	addi r3, r29, 0
/* 802F6F90 002F3B70  38 BC 00 00 */	addi r5, r28, 0
/* 802F6F94 002F3B74  48 09 9A DD */	bl func_80390A70
/* 802F6F98 002F3B78  3C 60 80 39 */	lis r3, func_80391070@ha
/* 802F6F9C 002F3B7C  38 83 10 70 */	addi r4, r3, func_80391070@l
/* 802F6FA0 002F3B80  38 7D 00 00 */	addi r3, r29, 0
/* 802F6FA4 002F3B84  38 A0 00 0B */	li r5, 0xb
/* 802F6FA8 002F3B88  38 C0 00 00 */	li r6, 0
/* 802F6FAC 002F3B8C  48 09 96 F1 */	bl GObj_SetupGXLink
/* 802F6FB0 002F3B90  80 9B 00 08 */	lwz r4, 8(r27)
/* 802F6FB4 002F3B94  28 04 00 00 */	cmplwi r4, 0
/* 802F6FB8 002F3B98  41 82 00 10 */	beq lbl_802F6FC8
/* 802F6FBC 002F3B9C  38 7D 00 00 */	addi r3, r29, 0
/* 802F6FC0 002F3BA0  38 A0 00 00 */	li r5, 0
/* 802F6FC4 002F3BA4  48 09 8D 91 */	bl func_8038FD54
lbl_802F6FC8:
/* 802F6FC8 002F3BA8  80 BB 00 14 */	lwz r5, 0x14(r27)
/* 802F6FCC 002F3BAC  38 7C 00 00 */	addi r3, r28, 0
/* 802F6FD0 002F3BB0  38 80 00 00 */	li r4, 0
/* 802F6FD4 002F3BB4  4B D1 51 15 */	bl func_8000C0E8
/* 802F6FD8 002F3BB8  7F 83 E3 78 */	mr r3, r28
/* 802F6FDC 002F3BBC  C0 22 E0 C8 */	lfs f1, lbl_804DDAA8(r2)
/* 802F6FE0 002F3BC0  48 07 88 DD */	bl HSD_JObjReqAnimAll
/* 802F6FE4 002F3BC4  7F 83 E3 78 */	mr r3, r28
/* 802F6FE8 002F3BC8  48 07 99 41 */	bl HSD_JObjAnimAll
/* 802F6FEC 002F3BCC  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F6FF0 002F3BD0  38 60 00 00 */	li r3, 0
/* 802F6FF4 002F3BD4  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 802F6FF8 002F3BD8  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F6FFC 002F3BDC  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F7000 002F3BE0  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 802F7004 002F3BE4  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F7008 002F3BE8  88 1B 00 12 */	lbz r0, 0x12(r27)
/* 802F700C 002F3BEC  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 802F7010 002F3BF0  98 1B 00 12 */	stb r0, 0x12(r27)
/* 802F7014 002F3BF4  93 BB 00 00 */	stw r29, 0(r27)
/* 802F7018 002F3BF8  93 DB 00 18 */	stw r30, 0x18(r27)
/* 802F701C 002F3BFC  93 FB 00 1C */	stw r31, 0x1c(r27)
lbl_802F7020:
/* 802F7020 002F3C00  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 802F7024 002F3C04  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 802F7028 002F3C08  38 21 00 38 */	addi r1, r1, 0x38
/* 802F702C 002F3C0C  7C 08 03 A6 */	mtlr r0
/* 802F7030 002F3C10  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_802F7034()
{ // clang-format off
    nofralloc
/* 802F7034 002F3C14  7C 08 02 A6 */	mflr r0
/* 802F7038 002F3C18  90 01 00 04 */	stw r0, 4(r1)
/* 802F703C 002F3C1C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 802F7040 002F3C20  93 E1 00 14 */	stw r31, 0x14(r1)
/* 802F7044 002F3C24  7C 7F 1B 78 */	mr r31, r3
/* 802F7048 002F3C28  4B E7 3D F1 */	bl func_8016AE38
/* 802F704C 002F3C2C  80 83 00 10 */	lwz r4, 0x10(r3)
/* 802F7050 002F3C30  2C 04 00 00 */	cmpwi r4, 0
/* 802F7054 002F3C34  41 82 00 0C */	beq lbl_802F7060
/* 802F7058 002F3C38  38 84 FF FF */	addi r4, r4, -1
/* 802F705C 002F3C3C  48 00 00 08 */	b lbl_802F7064
lbl_802F7060:
/* 802F7060 002F3C40  38 80 FF FF */	li r4, -1
lbl_802F7064:
/* 802F7064 002F3C44  80 A3 00 14 */	lwz r5, 0x14(r3)
/* 802F7068 002F3C48  2C 05 00 00 */	cmpwi r5, 0
/* 802F706C 002F3C4C  41 82 00 0C */	beq lbl_802F7078
/* 802F7070 002F3C50  38 A5 FF FF */	addi r5, r5, -1
/* 802F7074 002F3C54  48 00 00 08 */	b lbl_802F707C
lbl_802F7078:
/* 802F7078 002F3C58  38 A0 FF FF */	li r5, -1
lbl_802F707C:
/* 802F707C 002F3C5C  88 03 00 18 */	lbz r0, 0x18(r3)
/* 802F7080 002F3C60  28 00 00 00 */	cmplwi r0, 0
/* 802F7084 002F3C64  41 82 00 0C */	beq lbl_802F7090
/* 802F7088 002F3C68  7C 06 03 78 */	mr r6, r0
/* 802F708C 002F3C6C  48 00 00 08 */	b lbl_802F7094
lbl_802F7090:
/* 802F7090 002F3C70  38 C0 00 00 */	li r6, 0
lbl_802F7094:
/* 802F7094 002F3C74  89 03 00 0B */	lbz r8, 0xb(r3)
/* 802F7098 002F3C78  28 08 00 00 */	cmplwi r8, 0
/* 802F709C 002F3C7C  41 82 00 18 */	beq lbl_802F70B4
/* 802F70A0 002F3C80  38 68 FF FF */	addi r3, r8, -1
/* 802F70A4 002F3C84  38 FF 00 00 */	addi r7, r31, 0
/* 802F70A8 002F3C88  39 00 00 00 */	li r8, 0
/* 802F70AC 002F3C8C  4B FF FD F9 */	bl func_802F6EA4
/* 802F70B0 002F3C90  48 00 00 70 */	b lbl_802F7120
lbl_802F70B4:
/* 802F70B4 002F3C94  88 E3 00 08 */	lbz r7, 8(r3)
/* 802F70B8 002F3C98  28 07 00 01 */	cmplwi r7, 1
/* 802F70BC 002F3C9C  40 82 00 18 */	bne lbl_802F70D4
/* 802F70C0 002F3CA0  38 FF 00 00 */	addi r7, r31, 0
/* 802F70C4 002F3CA4  38 60 00 00 */	li r3, 0
/* 802F70C8 002F3CA8  39 00 00 00 */	li r8, 0
/* 802F70CC 002F3CAC  4B FF FD D9 */	bl func_802F6EA4
/* 802F70D0 002F3CB0  48 00 00 50 */	b lbl_802F7120
lbl_802F70D4:
/* 802F70D4 002F3CB4  88 03 24 CD */	lbz r0, 0x24cd(r3)
/* 802F70D8 002F3CB8  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 802F70DC 002F3CBC  41 82 00 34 */	beq lbl_802F7110
/* 802F70E0 002F3CC0  28 07 00 06 */	cmplwi r7, 6
/* 802F70E4 002F3CC4  40 82 00 18 */	bne lbl_802F70FC
/* 802F70E8 002F3CC8  38 FF 00 00 */	addi r7, r31, 0
/* 802F70EC 002F3CCC  38 60 00 07 */	li r3, 7
/* 802F70F0 002F3CD0  39 00 00 00 */	li r8, 0
/* 802F70F4 002F3CD4  4B FF FD B1 */	bl func_802F6EA4
/* 802F70F8 002F3CD8  48 00 00 28 */	b lbl_802F7120
lbl_802F70FC:
/* 802F70FC 002F3CDC  38 FF 00 00 */	addi r7, r31, 0
/* 802F7100 002F3CE0  38 60 00 06 */	li r3, 6
/* 802F7104 002F3CE4  39 00 00 00 */	li r8, 0
/* 802F7108 002F3CE8  4B FF FD 9D */	bl func_802F6EA4
/* 802F710C 002F3CEC  48 00 00 14 */	b lbl_802F7120
lbl_802F7110:
/* 802F7110 002F3CF0  38 FF 00 00 */	addi r7, r31, 0
/* 802F7114 002F3CF4  38 60 00 05 */	li r3, 5
/* 802F7118 002F3CF8  39 00 00 00 */	li r8, 0
/* 802F711C 002F3CFC  4B FF FD 89 */	bl func_802F6EA4
lbl_802F7120:
/* 802F7120 002F3D00  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 802F7124 002F3D04  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 802F7128 002F3D08  38 21 00 18 */	addi r1, r1, 0x18
/* 802F712C 002F3D0C  7C 08 03 A6 */	mtlr r0
/* 802F7130 002F3D10  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_802F7134()
{ // clang-format off
    nofralloc
/* 802F7134 002F3D14  7C 08 02 A6 */	mflr r0
/* 802F7138 002F3D18  3C 60 80 40 */	lis r3, lbl_803F9628@ha
/* 802F713C 002F3D1C  90 01 00 04 */	stw r0, 4(r1)
/* 802F7140 002F3D20  38 00 00 00 */	li r0, 0
/* 802F7144 002F3D24  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802F7148 002F3D28  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802F714C 002F3D2C  3B E3 96 28 */	addi r31, r3, lbl_803F9628@l
/* 802F7150 002F3D30  90 1F 00 00 */	stw r0, 0(r31)
/* 802F7154 002F3D34  90 1F 00 04 */	stw r0, 4(r31)
/* 802F7158 002F3D38  90 1F 00 28 */	stw r0, 0x28(r31)
/* 802F715C 002F3D3C  90 1F 00 2C */	stw r0, 0x2c(r31)
/* 802F7160 002F3D40  90 1F 00 50 */	stw r0, 0x50(r31)
/* 802F7164 002F3D44  90 1F 00 54 */	stw r0, 0x54(r31)
/* 802F7168 002F3D48  90 1F 00 78 */	stw r0, 0x78(r31)
/* 802F716C 002F3D4C  90 1F 00 7C */	stw r0, 0x7c(r31)
/* 802F7170 002F3D50  90 1F 00 A0 */	stw r0, 0xa0(r31)
/* 802F7174 002F3D54  90 1F 00 A4 */	stw r0, 0xa4(r31)
/* 802F7178 002F3D58  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 802F717C 002F3D5C  90 1F 00 CC */	stw r0, 0xcc(r31)
/* 802F7180 002F3D60  90 1F 00 F0 */	stw r0, 0xf0(r31)
/* 802F7184 002F3D64  90 1F 00 F4 */	stw r0, 0xf4(r31)
/* 802F7188 002F3D68  90 1F 01 18 */	stw r0, 0x118(r31)
/* 802F718C 002F3D6C  90 1F 01 1C */	stw r0, 0x11c(r31)
/* 802F7190 002F3D70  4B FF C5 01 */	bl func_802F3690
/* 802F7194 002F3D74  80 63 00 00 */	lwz r3, 0(r3)
/* 802F7198 002F3D78  38 81 00 1C */	addi r4, r1, 0x1c
/* 802F719C 002F3D7C  38 BF 01 40 */	addi r5, r31, 0x140
/* 802F71A0 002F3D80  4C C6 31 82 */	crclr 6
/* 802F71A4 002F3D84  38 C0 00 00 */	li r6, 0
/* 802F71A8 002F3D88  4B D1 F9 49 */	bl func_80016AF0
/* 802F71AC 002F3D8C  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71B0 002F3D90  80 03 00 00 */	lwz r0, 0(r3)
/* 802F71B4 002F3D94  90 1F 00 14 */	stw r0, 0x14(r31)
/* 802F71B8 002F3D98  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71BC 002F3D9C  80 03 00 04 */	lwz r0, 4(r3)
/* 802F71C0 002F3DA0  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 802F71C4 002F3DA4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71C8 002F3DA8  80 03 00 08 */	lwz r0, 8(r3)
/* 802F71CC 002F3DAC  90 1F 00 64 */	stw r0, 0x64(r31)
/* 802F71D0 002F3DB0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71D4 002F3DB4  80 03 00 0C */	lwz r0, 0xc(r3)
/* 802F71D8 002F3DB8  90 1F 00 8C */	stw r0, 0x8c(r31)
/* 802F71DC 002F3DBC  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71E0 002F3DC0  80 03 00 10 */	lwz r0, 0x10(r3)
/* 802F71E4 002F3DC4  90 1F 00 B4 */	stw r0, 0xb4(r31)
/* 802F71E8 002F3DC8  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71EC 002F3DCC  80 03 00 14 */	lwz r0, 0x14(r3)
/* 802F71F0 002F3DD0  90 1F 00 DC */	stw r0, 0xdc(r31)
/* 802F71F4 002F3DD4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F71F8 002F3DD8  80 03 00 18 */	lwz r0, 0x18(r3)
/* 802F71FC 002F3DDC  90 1F 01 04 */	stw r0, 0x104(r31)
/* 802F7200 002F3DE0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 802F7204 002F3DE4  80 03 00 1C */	lwz r0, 0x1c(r3)
/* 802F7208 002F3DE8  90 1F 01 2C */	stw r0, 0x12c(r31)
/* 802F720C 002F3DEC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802F7210 002F3DF0  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802F7214 002F3DF4  38 21 00 30 */	addi r1, r1, 0x30
/* 802F7218 002F3DF8  7C 08 03 A6 */	mtlr r0
/* 802F721C 002F3DFC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// free
void func_802F7220(void)
{
    s32 i;
    for (i = 0; i < 8; i++) {
        if (lbl_803F9628.things[i].unk0 != NULL) {
            func_80390228(lbl_803F9628.things[i].unk0);
            lbl_803F9628.things[i].unk0 = NULL;
        }
    }
}
