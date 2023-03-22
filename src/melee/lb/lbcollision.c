#include "forward.h"

#include "lbcollision.h"

#include "lb_00B0.h"
#include "lbaudio_ax.h"
#include "lbvector.h"

#include <math.h>
#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXDisplayList.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/mtx/mtxvec.h>
#include <dolphin/mtx/types.h>
#include <baselib/baselib_shared_data_003.h>
#include <baselib/mtx.h>
#include <baselib/state.h>
#include <baselib/tev.h>
#include <MetroTRK/intrinsics.h>

/// @todo Toggle for WIP functions
#if 0
#undef MUST_MATCH
#ifdef __MWERKS__
#pragma require_prototypes off
#endif
#endif

int lbl_803B9880[] = {
    0x00083D60, 0x00083D60, 0x00083D60, 0x0000005B, 0x0000005A, 0x00000059,
    0x00000058, 0x00000057, 0x00000056, 0x0000006F, 0x00000070, 0x00000071,
    0x00000054, 0x00000054, 0x00000054, 0x0000005A, 0x00000059, 0x000000DF,
    0x000000E1, 0x000000E1, 0x000000E1, 0x00000062, 0x00000063, 0x00000064,
    0x00000065, 0x00000066, 0x00000067, 0x0004461B, 0x0004461B, 0x0004461B,
    0x000000F1, 0x000000F1, 0x000000F1, 0x0000005E, 0x0000005D, 0x0000005C,
    0x00035BAF, 0x00035BB2, 0x00035BB5, 0x00083D60, 0x00083D60, 0x0000020D,
};

int lbColl_80005BB0(HitCapsule* arg0, int arg1)
{
    uint temp_r0;
    uint temp_r6;

    temp_r0 = arg0->sfx_kind;
    if (temp_r0 == 0xD) {
        temp_r6 = arg0->sfx_severity;
        if (temp_r6 == 2) {
            return func_80024184(*(lbl_803B9880 + (temp_r0 * 3) + (temp_r6)),
                                 127, 64, arg1);
        }
    }

    return func_80024184(
        *(lbl_803B9880 + (temp_r0 * 3) + (arg0->sfx_severity)), 127, 64, -1);
}

f32 const lbl_804D79F0 = 1e-5;
f32 const lbl_804D79F4 = -1e-5;
f32 const lbl_804D79F8 = 0;
f64 const lbl_804D7A00 = 1;
f32 const lbl_804D7A08 = 1;
f64 const lbl_804D7A10 = 0;

#ifdef MUST_MATCH
#pragma push
asm bool lbColl_80005C44(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3,
                         f32 arg8, f32 arg9)
{ // clang-format off
    nofralloc
/* 80005C44 00002824  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80005C48 00002828  EC 41 10 2A */	fadds f2, f1, f2
/* 80005C4C 0000282C  80 E3 00 00 */	lwz r7, 0(r3)
/* 80005C50 00002830  80 03 00 04 */	lwz r0, 4(r3)
/* 80005C54 00002834  90 E1 00 38 */	stw r7, 0x38(r1)
/* 80005C58 00002838  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80005C5C 0000283C  80 03 00 08 */	lwz r0, 8(r3)
/* 80005C60 00002840  90 01 00 40 */	stw r0, 0x40(r1)
/* 80005C64 00002844  80 65 00 00 */	lwz r3, 0(r5)
/* 80005C68 00002848  80 05 00 04 */	lwz r0, 4(r5)
/* 80005C6C 0000284C  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 80005C70 00002850  90 61 00 2C */	stw r3, 0x2c(r1)
/* 80005C74 00002854  90 01 00 30 */	stw r0, 0x30(r1)
/* 80005C78 00002858  80 05 00 08 */	lwz r0, 8(r5)
/* 80005C7C 0000285C  90 01 00 34 */	stw r0, 0x34(r1)
/* 80005C80 00002860  C0 64 00 00 */	lfs f3, 0(r4)
/* 80005C84 00002864  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 80005C88 00002868  40 81 00 30 */	ble lbl_80005CB8
/* 80005C8C 0000286C  EC 00 10 2A */	fadds f0, f0, f2
/* 80005C90 00002870  C0 21 00 2C */	lfs f1, 0x2c(r1)
/* 80005C94 00002874  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80005C98 00002878  40 80 00 0C */	bge lbl_80005CA4
/* 80005C9C 0000287C  38 60 00 00 */	li r3, 0
             /* 80005CA0 00002880  48 00 02 14 */	b lbl_80005EB4
lbl_80005CA4:
/* 80005CA4 00002884  EC 03 10 28 */	fsubs f0, f3, f2
/* 80005CA8 00002888  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80005CAC 0000288C  40 81 00 38 */	ble lbl_80005CE4
/* 80005CB0 00002890  38 60 00 00 */	li r3, 0
/* 80005CB4 00002894  48 00 02 00 */	b lbl_80005EB4
lbl_80005CB8:
/* 80005CB8 00002898  EC 00 10 28 */	fsubs f0, f0, f2
/* 80005CBC 0000289C  C0 21 00 2C */	lfs f1, 0x2c(r1)
/* 80005CC0 000028A0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80005CC4 000028A4  40 81 00 0C */	ble lbl_80005CD0
/* 80005CC8 000028A8  38 60 00 00 */	li r3, 0
/* 80005CCC 000028AC  48 00 01 E8 */	b lbl_80005EB4
lbl_80005CD0:
/* 80005CD0 000028B0  EC 03 10 2A */	fadds f0, f3, f2
/* 80005CD4 000028B4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80005CD8 000028B8  40 80 00 0C */	bge lbl_80005CE4
/* 80005CDC 000028BC  38 60 00 00 */	li r3, 0
/* 80005CE0 000028C0  48 00 01 D4 */	b lbl_80005EB4
lbl_80005CE4:
/* 80005CE4 000028C4  C1 61 00 3C */	lfs f11, 0x3c(r1)
/* 80005CE8 000028C8  C0 24 00 04 */	lfs f1, 4(r4)
/* 80005CEC 000028CC  FC 0B 08 40 */	fcmpo cr0, f11, f1
/* 80005CF0 000028D0  40 81 00 30 */	ble lbl_80005D20
/* 80005CF4 000028D4  EC 0B 10 2A */	fadds f0, f11, f2
/* 80005CF8 000028D8  C0 81 00 30 */	lfs f4, 0x30(r1)
/* 80005CFC 000028DC  FC 00 20 40 */	fcmpo cr0, f0, f4
/* 80005D00 000028E0  40 80 00 0C */	bge lbl_80005D0C
/* 80005D04 000028E4  38 60 00 00 */	li r3, 0
/* 80005D08 000028E8  48 00 01 AC */	b lbl_80005EB4
lbl_80005D0C:
/* 80005D0C 000028EC  EC 01 10 28 */	fsubs f0, f1, f2
/* 80005D10 000028F0  FC 00 20 40 */	fcmpo cr0, f0, f4
/* 80005D14 000028F4  40 81 00 38 */	ble lbl_80005D4C
/* 80005D18 000028F8  38 60 00 00 */	li r3, 0
/* 80005D1C 000028FC  48 00 01 98 */	b lbl_80005EB4
lbl_80005D20:
/* 80005D20 00002900  EC 0B 10 28 */	fsubs f0, f11, f2
/* 80005D24 00002904  C0 81 00 30 */	lfs f4, 0x30(r1)
/* 80005D28 00002908  FC 00 20 40 */	fcmpo cr0, f0, f4
/* 80005D2C 0000290C  40 81 00 0C */	ble lbl_80005D38
/* 80005D30 00002910  38 60 00 00 */	li r3, 0
/* 80005D34 00002914  48 00 01 80 */	b lbl_80005EB4
lbl_80005D38:
/* 80005D38 00002918  EC 01 10 2A */	fadds f0, f1, f2
/* 80005D3C 0000291C  FC 00 20 40 */	fcmpo cr0, f0, f4
/* 80005D40 00002920  40 80 00 0C */	bge lbl_80005D4C
/* 80005D44 00002924  38 60 00 00 */	li r3, 0
/* 80005D48 00002928  48 00 01 6C */	b lbl_80005EB4
lbl_80005D4C:
/* 80005D4C 0000292C  C1 81 00 40 */	lfs f12, 0x40(r1)
/* 80005D50 00002930  C0 84 00 08 */	lfs f4, 8(r4)
/* 80005D54 00002934  FC 0C 20 40 */	fcmpo cr0, f12, f4
/* 80005D58 00002938  40 81 00 30 */	ble lbl_80005D88
/* 80005D5C 0000293C  EC 0C 10 2A */	fadds f0, f12, f2
/* 80005D60 00002940  C0 A1 00 34 */	lfs f5, 0x34(r1)
/* 80005D64 00002944  FC 00 28 40 */	fcmpo cr0, f0, f5
/* 80005D68 00002948  40 80 00 0C */	bge lbl_80005D74
/* 80005D6C 0000294C  38 60 00 00 */	li r3, 0
/* 80005D70 00002950  48 00 01 44 */	b lbl_80005EB4
lbl_80005D74:
/* 80005D74 00002954  EC 04 10 28 */	fsubs f0, f4, f2
/* 80005D78 00002958  FC 00 28 40 */	fcmpo cr0, f0, f5
/* 80005D7C 0000295C  40 81 00 38 */	ble lbl_80005DB4
/* 80005D80 00002960  38 60 00 00 */	li r3, 0
/* 80005D84 00002964  48 00 01 30 */	b lbl_80005EB4
lbl_80005D88:
/* 80005D88 00002968  EC 0C 10 28 */	fsubs f0, f12, f2
/* 80005D8C 0000296C  C0 A1 00 34 */	lfs f5, 0x34(r1)
/* 80005D90 00002970  FC 00 28 40 */	fcmpo cr0, f0, f5
/* 80005D94 00002974  40 81 00 0C */	ble lbl_80005DA0
/* 80005D98 00002978  38 60 00 00 */	li r3, 0
/* 80005D9C 0000297C  48 00 01 18 */	b lbl_80005EB4
lbl_80005DA0:
/* 80005DA0 00002980  EC 04 10 2A */	fadds f0, f4, f2
/* 80005DA4 00002984  FC 00 28 40 */	fcmpo cr0, f0, f5
/* 80005DA8 00002988  40 80 00 0C */	bge lbl_80005DB4
/* 80005DAC 0000298C  38 60 00 00 */	li r3, 0
/* 80005DB0 00002990  48 00 01 04 */	b lbl_80005EB4
lbl_80005DB4:
/* 80005DB4 00002994  ED 21 58 28 */	fsubs f9, f1, f11
/* 80005DB8 00002998  C0 E1 00 38 */	lfs f7, 0x38(r1)
/* 80005DBC 0000299C  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 80005DC0 000029A0  ED 44 60 28 */	fsubs f10, f4, f12
/* 80005DC4 000029A4  C0 A1 00 2C */	lfs f5, 0x2c(r1)
/* 80005DC8 000029A8  ED 03 38 28 */	fsubs f8, f3, f7
/* 80005DCC 000029AC  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 80005DD0 000029B0  EC C9 02 72 */	fmuls f6, f9, f9
/* 80005DD4 000029B4  C0 62 80 10 */	lfs f3, lbl_804D79F0
/* 80005DD8 000029B8  EC 8B 00 28 */	fsubs f4, f11, f0
/* 80005DDC 000029BC  EC C8 32 3A */	fmadds f6, f8, f8, f6
/* 80005DE0 000029C0  EC A7 28 28 */	fsubs f5, f7, f5
/* 80005DE4 000029C4  EC 89 01 32 */	fmuls f4, f9, f4
/* 80005DE8 000029C8  EC EA 32 BA */	fmadds f7, f10, f10, f6
/* 80005DEC 000029CC  EC CC 08 28 */	fsubs f6, f12, f1
/* 80005DF0 000029D0  EC 88 21 7A */	fmadds f4, f8, f5, f4
/* 80005DF4 000029D4  FC 07 18 40 */	fcmpo cr0, f7, f3
/* 80005DF8 000029D8  EC 8A 21 BA */	fmadds f4, f10, f6, f4
/* 80005DFC 000029DC  40 80 00 18 */	bge lbl_80005E14
/* 80005E00 000029E0  C0 62 80 14 */	lfs f3, lbl_804D79F4
/* 80005E04 000029E4  FC 07 18 40 */	fcmpo cr0, f7, f3
/* 80005E08 000029E8  40 81 00 0C */	ble lbl_80005E14
/* 80005E0C 000029EC  38 00 00 01 */	li r0, 1
/* 80005E10 000029F0  48 00 00 08 */	b lbl_80005E18
lbl_80005E14:
/* 80005E14 000029F4  38 00 00 00 */	li r0, 0
lbl_80005E18:
/* 80005E18 000029F8  2C 00 00 00 */	cmpwi r0, 0
/* 80005E1C 000029FC  41 82 00 0C */	beq lbl_80005E28
/* 80005E20 00002A00  C0 C2 80 18 */	lfs f6, lbl_804D79F8
/* 80005E24 00002A04  48 00 00 34 */	b lbl_80005E58
lbl_80005E28:
/* 80005E28 00002A08  FC 80 20 50 */	fneg f4, f4
/* 80005E2C 00002A0C  C8 62 80 20 */	lfd f3, lbl_804D7A00
/* 80005E30 00002A10  EC 84 38 24 */	fdivs f4, f4, f7
/* 80005E34 00002A14  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 80005E38 00002A18  FC C0 20 90 */	fmr f6, f4
/* 80005E3C 00002A1C  40 81 00 0C */	ble lbl_80005E48
/* 80005E40 00002A20  C0 C2 80 28 */	lfs f6, lbl_804D7A08
/* 80005E44 00002A24  48 00 00 14 */	b lbl_80005E58
lbl_80005E48:
/* 80005E48 00002A28  C8 62 80 30 */	lfd f3, lbl_804D7A10
/* 80005E4C 00002A2C  FC 06 18 40 */	fcmpo cr0, f6, f3
/* 80005E50 00002A30  40 80 00 08 */	bge lbl_80005E58
/* 80005E54 00002A34  C0 C2 80 18 */	lfs f6, lbl_804D79F8
lbl_80005E58:
/* 80005E58 00002A38  C0 A1 00 38 */	lfs f5, 0x38(r1)
/* 80005E5C 00002A3C  EC 89 59 BA */	fmadds f4, f9, f6, f11
/* 80005E60 00002A40  EC 6A 61 BA */	fmadds f3, f10, f6, f12
/* 80005E64 00002A44  EC A8 29 BA */	fmadds f5, f8, f6, f5
/* 80005E68 00002A48  EC 42 00 B2 */	fmuls f2, f2, f2
/* 80005E6C 00002A4C  D0 A6 00 00 */	stfs f5, 0(r6)
/* 80005E70 00002A50  D0 86 00 04 */	stfs f4, 4(r6)
/* 80005E74 00002A54  D0 66 00 08 */	stfs f3, 8(r6)
/* 80005E78 00002A58  C0 86 00 04 */	lfs f4, 4(r6)
/* 80005E7C 00002A5C  C0 66 00 08 */	lfs f3, 8(r6)
/* 80005E80 00002A60  EC A4 00 28 */	fsubs f5, f4, f0
/* 80005E84 00002A64  C0 86 00 00 */	lfs f4, 0(r6)
/* 80005E88 00002A68  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80005E8C 00002A6C  EC 63 08 28 */	fsubs f3, f3, f1
/* 80005E90 00002A70  EC 24 00 28 */	fsubs f1, f4, f0
/* 80005E94 00002A74  EC 05 01 72 */	fmuls f0, f5, f5
/* 80005E98 00002A78  EC 01 00 7A */	fmadds f0, f1, f1, f0
/* 80005E9C 00002A7C  EC 03 00 FA */	fmadds f0, f3, f3, f0
/* 80005EA0 00002A80  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80005EA4 00002A84  40 80 00 0C */	bge lbl_80005EB0
/* 80005EA8 00002A88  38 60 00 00 */	li r3, 0
/* 80005EAC 00002A8C  48 00 00 08 */	b lbl_80005EB4
lbl_80005EB0:
/* 80005EB0 00002A90  38 60 00 01 */	li r3, 1
lbl_80005EB4:
/* 80005EB4 00002A94  38 21 00 48 */	addi r1, r1, 0x48
/* 80005EB8 00002A98  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

int lbColl_80005C44(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3, f32 arg8,
                    f32 arg9)
{
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 temp_f10;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f5;
    f32 temp_f7;
    f32 temp_f8;
    f32 temp_f9;
    f32 var_f6;
    int var_r0;

    temp_f2 = arg8 + arg9;
    sp38 = arg0->x;
    sp3C = arg0->y;
    sp40 = arg0->z;
    sp2C = arg2->x;
    sp30 = arg2->y;
    sp34 = arg2->z;
    temp_f3 = arg1->x;
    if (sp38 > temp_f3) {
        if ((sp38 + temp_f2) < sp2C) {
            return 0;
        }
        if ((temp_f3 - temp_f2) > sp2C) {
            return 0;
        }
        goto block_9;
    }
    if ((sp38 - temp_f2) > sp2C) {
        return 0;
    }
    if ((temp_f3 + temp_f2) < sp2C) {
        return 0;
    }
block_9:
    temp_f1 = arg1->y;
    if (sp3C > temp_f1) {
        if ((sp3C + temp_f2) < sp30) {
            return 0;
        }
        if ((temp_f1 - temp_f2) > sp30) {
            return 0;
        }
        goto block_18;
    }
    if ((sp3C - temp_f2) > sp30) {
        return 0;
    }
    if ((temp_f1 + temp_f2) < sp30) {
        return 0;
    }
block_18:
    temp_f4 = arg1->z;
    if (sp40 > temp_f4) {
        if ((sp40 + temp_f2) < sp34) {
            return 0;
        }
        if ((temp_f4 - temp_f2) > sp34) {
            return 0;
        }
        goto block_27;
    }
    if ((sp40 - temp_f2) > sp34) {
        return 0;
    }
    if ((temp_f4 + temp_f2) < sp34) {
        return 0;
    }
block_27:
    temp_f9 = temp_f1 - sp3C;
    temp_f10 = temp_f4 - sp40;
    temp_f8 = temp_f3 - sp38;
    temp_f7 =
        (temp_f10 * temp_f10) + ((temp_f8 * temp_f8) + (temp_f9 * temp_f9));
    if ((temp_f7 < lbl_804D78D0) && (temp_f7 > lbl_804D78D4)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        var_f6 = lbl_804D78D8;
    } else {
        temp_f4_2 =
            -((temp_f10 * (sp40 - sp34)) +
              ((temp_f8 * (sp38 - sp2C)) + (temp_f9 * (sp3C - sp30)))) /
            temp_f7;
        var_f6 = temp_f4_2;
        if (temp_f4_2 > (f32) lbl_804D78E0) {
            var_f6 = lbl_804D78E8;
        } else if (var_f6 < (f32) lbl_804D78F0) {
            var_f6 = lbl_804D78D8;
        }
    }
    arg3->x = (temp_f8 * var_f6) + sp38;
    arg3->y = (temp_f9 * var_f6) + sp3C;
    arg3->z = (temp_f10 * var_f6) + sp40;
    temp_f5 = arg3->y - sp30;
    temp_f3_2 = arg3->z - sp34;
    temp_f1_2 = arg3->x - sp2C;
    if ((temp_f2 * temp_f2) <
        ((temp_f3_2 * temp_f3_2) +
         ((temp_f1_2 * temp_f1_2) + (temp_f5 * temp_f5))))
    {
        return 0;
    }
    return 1;
}
#endif

#ifdef MUST_MATCH
#pragma push
asm f32 lbColl_80005EBC(Vec3*, Vec3*, Vec3*, f32*){
    // clang-format off
    nofralloc
/* 80005EBC 00002A9C  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80005EC0 00002AA0  80 E3 00 00 */	lwz r7, 0(r3)
/* 80005EC4 00002AA4  80 03 00 04 */	lwz r0, 4(r3)
/* 80005EC8 00002AA8  C8 02 80 20 */	lfd f0, lbl_804D7A00(r2)
/* 80005ECC 00002AAC  90 E1 00 50 */	stw r7, 0x50(r1)
/* 80005ED0 00002AB0  90 01 00 54 */	stw r0, 0x54(r1)
/* 80005ED4 00002AB4  80 03 00 08 */	lwz r0, 8(r3)
/* 80005ED8 00002AB8  90 01 00 58 */	stw r0, 0x58(r1)
/* 80005EDC 00002ABC  C0 44 00 00 */	lfs f2, 0(r4)
/* 80005EE0 00002AC0  C0 23 00 00 */	lfs f1, 0(r3)
/* 80005EE4 00002AC4  C0 84 00 04 */	lfs f4, 4(r4)
/* 80005EE8 00002AC8  EC C2 08 28 */	fsubs f6, f2, f1
/* 80005EEC 00002ACC  C0 63 00 04 */	lfs f3, 4(r3)
/* 80005EF0 00002AD0  C0 23 00 08 */	lfs f1, 8(r3)
/* 80005EF4 00002AD4  C0 44 00 08 */	lfs f2, 8(r4)
/* 80005EF8 00002AD8  EC E4 18 28 */	fsubs f7, f4, f3
/* 80005EFC 00002ADC  80 65 00 00 */	lwz r3, 0(r5)
/* 80005F00 00002AE0  ED 02 08 28 */	fsubs f8, f2, f1
/* 80005F04 00002AE4  80 05 00 04 */	lwz r0, 4(r5)
/* 80005F08 00002AE8  EC 27 01 F2 */	fmuls f1, f7, f7
/* 80005F0C 00002AEC  C1 21 00 54 */	lfs f9, 0x54(r1)
/* 80005F10 00002AF0  90 61 00 38 */	stw r3, 0x38(r1)
/* 80005F14 00002AF4  EC 26 09 BA */	fmadds f1, f6, f6, f1
/* 80005F18 00002AF8  C0 81 00 50 */	lfs f4, 0x50(r1)
/* 80005F1C 00002AFC  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80005F20 00002B00  C1 41 00 58 */	lfs f10, 0x58(r1)
/* 80005F24 00002B04  80 05 00 08 */	lwz r0, 8(r5)
/* 80005F28 00002B08  EC 28 0A 3A */	fmadds f1, f8, f8, f1
/* 80005F2C 00002B0C  90 01 00 40 */	stw r0, 0x40(r1)
/* 80005F30 00002B10  C0 41 00 3C */	lfs f2, 0x3c(r1)
/* 80005F34 00002B14  C0 61 00 38 */	lfs f3, 0x38(r1)
/* 80005F38 00002B18  EC 49 10 28 */	fsubs f2, f9, f2
/* 80005F3C 00002B1C  C0 A1 00 40 */	lfs f5, 0x40(r1)
/* 80005F40 00002B20  EC 64 18 28 */	fsubs f3, f4, f3
/* 80005F44 00002B24  EC 8A 28 28 */	fsubs f4, f10, f5
/* 80005F48 00002B28  EC 47 00 B2 */	fmuls f2, f7, f2
/* 80005F4C 00002B2C  EC 46 10 FA */	fmadds f2, f6, f3, f2
/* 80005F50 00002B30  EC 48 11 3A */	fmadds f2, f8, f4, f2
/* 80005F54 00002B34  FC 40 10 50 */	fneg f2, f2
/* 80005F58 00002B38  EC 22 08 24 */	fdivs f1, f2, f1
/* 80005F5C 00002B3C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80005F60 00002B40  FC A0 08 90 */	fmr f5, f1
/* 80005F64 00002B44  40 81 00 0C */	ble lbl_80005F70
/* 80005F68 00002B48  C0 A2 80 28 */	lfs f5, lbl_804D7A08(r2)
/* 80005F6C 00002B4C  48 00 00 14 */	b lbl_80005F80
lbl_80005F70:
/* 80005F70 00002B50  C8 02 80 30 */	lfd f0, lbl_804D7A10(r2)
/* 80005F74 00002B54  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 80005F78 00002B58  40 80 00 08 */	bge lbl_80005F80
/* 80005F7C 00002B5C  C0 A2 80 18 */	lfs f5, lbl_804D79F8(r2)
lbl_80005F80:
/* 80005F80 00002B60  EC 67 49 7A */	fmadds f3, f7, f5, f9
/* 80005F84 00002B64  C0 81 00 50 */	lfs f4, 0x50(r1)
/* 80005F88 00002B68  C0 45 00 04 */	lfs f2, 4(r5)
/* 80005F8C 00002B6C  EC 28 51 7A */	fmadds f1, f8, f5, f10
/* 80005F90 00002B70  C0 05 00 08 */	lfs f0, 8(r5)
/* 80005F94 00002B74  EC E3 10 28 */	fsubs f7, f3, f2
/* 80005F98 00002B78  C0 45 00 00 */	lfs f2, 0(r5)
/* 80005F9C 00002B7C  EC 66 21 7A */	fmadds f3, f6, f5, f4
/* 80005FA0 00002B80  EC 81 00 28 */	fsubs f4, f1, f0
/* 80005FA4 00002B84  D0 A6 00 00 */	stfs f5, 0(r6)
/* 80005FA8 00002B88  EC 23 10 28 */	fsubs f1, f3, f2
/* 80005FAC 00002B8C  EC 07 01 F2 */	fmuls f0, f7, f7
/* 80005FB0 00002B90  EC 01 00 7A */	fmadds f0, f1, f1, f0
/* 80005FB4 00002B94  EC 24 01 3A */	fmadds f1, f4, f4, f0
/* 80005FB8 00002B98  38 21 00 60 */	addi r1, r1, 0x60
/* 80005FBC 00002B9C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

f32 lbColl_80005EBC(Vec3* arg0, Vec3* arg1, Vec3* arg2, f32* arg3)
{
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f8;
    f32 var_f5;

    sp50 = arg0->x;
    sp54 = arg0->y;
    sp58 = arg0->z;
    temp_f6 = arg1->x - arg0->x;
    temp_f7_2 = arg1->y - arg0->y;
    temp_f8 = arg1->z - arg0->z;
    sp38 = arg2->x;
    sp3C = arg2->y;
    sp40 = arg2->z;
    temp_f1_2 = -((temp_f8 * (sp58 - sp40)) +
                  ((temp_f6 * (sp50 - sp38)) + (temp_f7_2 * (sp54 - sp3C)))) /
                ((temp_f8 * temp_f8) +
                 ((temp_f6 * temp_f6) + (temp_f7_2 * temp_f7_2)));
    var_f5 = temp_f1_2;
    if (temp_f1_2 > (f32) lbl_804D78E0) {
        var_f5 = lbl_804D78E8;
    } else if (var_f5 < (f32) lbl_804D78F0) {
        var_f5 = lbl_804D78D8;
    }
    temp_f7 = ((temp_f7_2 * var_f5) + sp54) - arg2->y;
    temp_f4 = ((temp_f8 * var_f5) + sp58) - arg2->z;
    *arg3 = var_f5;
    temp_f1 = ((temp_f6 * var_f5) + sp50) - arg2->x;
    return (temp_f4 * temp_f4) + ((temp_f1 * temp_f1) + (temp_f7 * temp_f7));
}
#endif

#ifdef MUST_MATCH
#pragma push
asm f32 lbColl_80005FC0(Vec3*, Vec3*, Vec3*, f32*){
    // clang-format off
    nofralloc
/* 80005FC0 00002BA0  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80005FC4 00002BA4  80 E3 00 00 */	lwz r7, 0(r3)
/* 80005FC8 00002BA8  80 03 00 04 */	lwz r0, 4(r3)
/* 80005FCC 00002BAC  C8 02 80 20 */	lfd f0, lbl_804D7A00(r2)
/* 80005FD0 00002BB0  90 E1 00 50 */	stw r7, 0x50(r1)
/* 80005FD4 00002BB4  90 01 00 54 */	stw r0, 0x54(r1)
/* 80005FD8 00002BB8  80 03 00 08 */	lwz r0, 8(r3)
/* 80005FDC 00002BBC  90 01 00 58 */	stw r0, 0x58(r1)
/* 80005FE0 00002BC0  C0 84 00 00 */	lfs f4, 0(r4)
/* 80005FE4 00002BC4  C0 63 00 00 */	lfs f3, 0(r3)
/* 80005FE8 00002BC8  C0 23 00 04 */	lfs f1, 4(r3)
/* 80005FEC 00002BCC  C0 44 00 04 */	lfs f2, 4(r4)
/* 80005FF0 00002BD0  EC A4 18 28 */	fsubs f5, f4, f3
/* 80005FF4 00002BD4  80 65 00 00 */	lwz r3, 0(r5)
/* 80005FF8 00002BD8  80 05 00 04 */	lwz r0, 4(r5)
/* 80005FFC 00002BDC  EC C2 08 28 */	fsubs f6, f2, f1
/* 80006000 00002BE0  C0 E1 00 54 */	lfs f7, 0x54(r1)
/* 80006004 00002BE4  90 61 00 38 */	stw r3, 0x38(r1)
/* 80006008 00002BE8  EC 26 01 B2 */	fmuls f1, f6, f6
/* 8000600C 00002BEC  C0 81 00 50 */	lfs f4, 0x50(r1)
/* 80006010 00002BF0  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80006014 00002BF4  80 05 00 08 */	lwz r0, 8(r5)
/* 80006018 00002BF8  EC 25 09 7A */	fmadds f1, f5, f5, f1
/* 8000601C 00002BFC  90 01 00 40 */	stw r0, 0x40(r1)
/* 80006020 00002C00  C0 41 00 3C */	lfs f2, 0x3c(r1)
/* 80006024 00002C04  C0 61 00 38 */	lfs f3, 0x38(r1)
/* 80006028 00002C08  EC 47 10 28 */	fsubs f2, f7, f2
/* 8000602C 00002C0C  EC 64 18 28 */	fsubs f3, f4, f3
/* 80006030 00002C10  EC 46 00 B2 */	fmuls f2, f6, f2
/* 80006034 00002C14  EC 45 10 FA */	fmadds f2, f5, f3, f2
/* 80006038 00002C18  FC 40 10 50 */	fneg f2, f2
/* 8000603C 00002C1C  EC 22 08 24 */	fdivs f1, f2, f1
/* 80006040 00002C20  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80006044 00002C24  FC 80 08 90 */	fmr f4, f1
/* 80006048 00002C28  40 81 00 0C */	ble lbl_80006054
/* 8000604C 00002C2C  C0 82 80 28 */	lfs f4, lbl_804D7A08(r2)
/* 80006050 00002C30  48 00 00 14 */	b lbl_80006064
lbl_80006054:
/* 80006054 00002C34  C8 02 80 30 */	lfd f0, lbl_804D7A10(r2)
/* 80006058 00002C38  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8000605C 00002C3C  40 80 00 08 */	bge lbl_80006064
/* 80006060 00002C40  C0 82 80 18 */	lfs f4, lbl_804D79F8(r2)
lbl_80006064:
/* 80006064 00002C44  EC 26 39 3A */	fmadds f1, f6, f4, f7
/* 80006068 00002C48  C0 61 00 50 */	lfs f3, 0x50(r1)
/* 8000606C 00002C4C  C0 05 00 04 */	lfs f0, 4(r5)
/* 80006070 00002C50  C0 45 00 00 */	lfs f2, 0(r5)
/* 80006074 00002C54  EC 65 19 3A */	fmadds f3, f5, f4, f3
/* 80006078 00002C58  EC 01 00 28 */	fsubs f0, f1, f0
/* 8000607C 00002C5C  D0 86 00 00 */	stfs f4, 0(r6)
/* 80006080 00002C60  EC 23 10 28 */	fsubs f1, f3, f2
/* 80006084 00002C64  EC 00 00 32 */	fmuls f0, f0, f0
/* 80006088 00002C68  EC 21 00 7A */	fmadds f1, f1, f1, f0
/* 8000608C 00002C6C  38 21 00 60 */	addi r1, r1, 0x60
/* 80006090 00002C70  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

f32 lbColl_80005FC0(Vec3* a, Vec3* b, Vec3* c, f32* out)
{
    {
        Vec3 temp_a;
        temp_a.x = a->x;
        temp_a.y = a->y;
        temp_a.z = a->z;
        {
            f32 diff_ba_x = b->x - a->x;
            f32 diff_ba_y = b->y - a->y;

            Vec3 temp_c;
            temp_c.x = c->x;
            temp_c.y = c->y;
            temp_c.z = c->z;
            {
                f32 result0 = -(diff_ba_x * (temp_a.x - temp_c.x) +
                                (diff_ba_y * (temp_a.y - temp_c.y))) /
                              (diff_ba_x * diff_ba_x + diff_ba_y * diff_ba_y);
                {
                    f32 result1 = result0;
                    if (result0 > (f32) 1.0) {
                        result1 = 1.0f;
                    } else if (result1 < (f32) 0.0) {
                        result1 = 0.0f;
                    }
                    {
                        f32 x, y;

                        y = diff_ba_y * result1 + temp_a.y - c->y;
                        *out = result1;
                        x = diff_ba_x * result1 + temp_a.x - c->x;
                        return x * x + y * y;
                    }
                }
            }
        }
    }
}
#endif

f64 const lbl_804D7A18 = 0.5;

#ifdef MUST_MATCH
#pragma push
asm bool lbColl_80006094(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, f32, f32)
{ // clang-format off
    nofralloc
/* 80006094 00002C74  7C 08 02 A6 */	mflr r0
/* 80006098 00002C78  90 01 00 04 */	stw r0, 4(r1)
/* 8000609C 00002C7C  94 21 FE 78 */	stwu r1, -0x188(r1)
/* 800060A0 00002C80  DB E1 01 80 */	stfd f31, 0x180(r1)
/* 800060A4 00002C84  DB C1 01 78 */	stfd f30, 0x178(r1)
/* 800060A8 00002C88  DB A1 01 70 */	stfd f29, 0x170(r1)
/* 800060AC 00002C8C  DB 81 01 68 */	stfd f28, 0x168(r1)
/* 800060B0 00002C90  DB 61 01 60 */	stfd f27, 0x160(r1)
/* 800060B4 00002C94  EF 61 10 2A */	fadds f27, f1, f2
/* 800060B8 00002C98  DB 41 01 58 */	stfd f26, 0x158(r1)
/* 800060BC 00002C9C  DB 21 01 50 */	stfd f25, 0x150(r1)
/* 800060C0 00002CA0  DB 01 01 48 */	stfd f24, 0x148(r1)
/* 800060C4 00002CA4  DA E1 01 40 */	stfd f23, 0x140(r1)
/* 800060C8 00002CA8  DA C1 01 38 */	stfd f22, 0x138(r1)
/* 800060CC 00002CAC  DA A1 01 30 */	stfd f21, 0x130(r1)
/* 800060D0 00002CB0  DA 81 01 28 */	stfd f20, 0x128(r1)
/* 800060D4 00002CB4  DA 61 01 20 */	stfd f19, 0x120(r1)
/* 800060D8 00002CB8  DA 41 01 18 */	stfd f18, 0x118(r1)
/* 800060DC 00002CBC  BF 41 01 00 */	stmw r26, 0x100(r1)
/* 800060E0 00002CC0  7C 7A 1B 78 */	mr r26, r3
/* 800060E4 00002CC4  7C BC 2B 78 */	mr r28, r5
/* 800060E8 00002CC8  7C 9B 23 78 */	mr r27, r4
/* 800060EC 00002CCC  3B A6 00 00 */	addi r29, r6, 0
/* 800060F0 00002CD0  3B C7 00 00 */	addi r30, r7, 0
/* 800060F4 00002CD4  7D 1F 43 78 */	mr r31, r8
/* 800060F8 00002CD8  80 63 00 00 */	lwz r3, 0(r3)
/* 800060FC 00002CDC  80 1A 00 04 */	lwz r0, 4(r26)
/* 80006100 00002CE0  90 61 00 28 */	stw r3, 0x28(r1)
/* 80006104 00002CE4  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80006108 00002CE8  80 1A 00 08 */	lwz r0, 8(r26)
/* 8000610C 00002CEC  90 01 00 30 */	stw r0, 0x30(r1)
/* 80006110 00002CF0  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80006114 00002CF4  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80006118 00002CF8  90 01 00 F0 */	stw r0, 0xf0(r1)
/* 8000611C 00002CFC  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80006120 00002D00  90 61 00 F4 */	stw r3, 0xf4(r1)
/* 80006124 00002D04  90 01 00 F8 */	stw r0, 0xf8(r1)
/* 80006128 00002D08  80 65 00 00 */	lwz r3, 0(r5)
/* 8000612C 00002D0C  80 05 00 04 */	lwz r0, 4(r5)
/* 80006130 00002D10  C0 21 00 F0 */	lfs f1, 0xf0(r1)
/* 80006134 00002D14  90 61 00 34 */	stw r3, 0x34(r1)
/* 80006138 00002D18  90 01 00 38 */	stw r0, 0x38(r1)
/* 8000613C 00002D1C  80 05 00 08 */	lwz r0, 8(r5)
/* 80006140 00002D20  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80006144 00002D24  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80006148 00002D28  80 61 00 38 */	lwz r3, 0x38(r1)
/* 8000614C 00002D2C  90 01 00 E4 */	stw r0, 0xe4(r1)
/* 80006150 00002D30  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80006154 00002D34  90 61 00 E8 */	stw r3, 0xe8(r1)
/* 80006158 00002D38  90 01 00 EC */	stw r0, 0xec(r1)
/* 8000615C 00002D3C  C0 04 00 00 */	lfs f0, 0(r4)
/* 80006160 00002D40  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80006164 00002D44  40 81 00 4C */	ble lbl_800061B0
/* 80006168 00002D48  EC 41 D8 2A */	fadds f2, f1, f27
/* 8000616C 00002D4C  C0 21 00 E4 */	lfs f1, 0xe4(r1)
/* 80006170 00002D50  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006174 00002D54  40 80 00 18 */	bge lbl_8000618C
/* 80006178 00002D58  C0 3D 00 00 */	lfs f1, 0(r29)
/* 8000617C 00002D5C  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006180 00002D60  40 80 00 0C */	bge lbl_8000618C
/* 80006184 00002D64  38 60 00 00 */	li r3, 0
/* 80006188 00002D68  48 00 06 24 */	b lbl_800067AC
lbl_8000618C:
/* 8000618C 00002D6C  EC 40 D8 28 */	fsubs f2, f0, f27
/* 80006190 00002D70  C0 21 00 E4 */	lfs f1, 0xe4(r1)
/* 80006194 00002D74  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006198 00002D78  40 81 00 60 */	ble lbl_800061F8
/* 8000619C 00002D7C  C0 3D 00 00 */	lfs f1, 0(r29)
/* 800061A0 00002D80  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800061A4 00002D84  40 81 00 54 */	ble lbl_800061F8
/* 800061A8 00002D88  38 60 00 00 */	li r3, 0
/* 800061AC 00002D8C  48 00 06 00 */	b lbl_800067AC
lbl_800061B0:
/* 800061B0 00002D90  EC 41 D8 28 */	fsubs f2, f1, f27
/* 800061B4 00002D94  C0 21 00 E4 */	lfs f1, 0xe4(r1)
/* 800061B8 00002D98  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800061BC 00002D9C  40 81 00 18 */	ble lbl_800061D4
/* 800061C0 00002DA0  C0 3D 00 00 */	lfs f1, 0(r29)
/* 800061C4 00002DA4  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800061C8 00002DA8  40 81 00 0C */	ble lbl_800061D4
/* 800061CC 00002DAC  38 60 00 00 */	li r3, 0
/* 800061D0 00002DB0  48 00 05 DC */	b lbl_800067AC
lbl_800061D4:
/* 800061D4 00002DB4  EC 40 D8 2A */	fadds f2, f0, f27
/* 800061D8 00002DB8  C0 21 00 E4 */	lfs f1, 0xe4(r1)
/* 800061DC 00002DBC  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800061E0 00002DC0  40 80 00 18 */	bge lbl_800061F8
/* 800061E4 00002DC4  C0 3D 00 00 */	lfs f1, 0(r29)
/* 800061E8 00002DC8  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800061EC 00002DCC  40 80 00 0C */	bge lbl_800061F8
/* 800061F0 00002DD0  38 60 00 00 */	li r3, 0
/* 800061F4 00002DD4  48 00 05 B8 */	b lbl_800067AC
lbl_800061F8:
/* 800061F8 00002DD8  C3 E1 00 F4 */	lfs f31, 0xf4(r1)
/* 800061FC 00002DDC  C0 3B 00 04 */	lfs f1, 4(r27)
/* 80006200 00002DE0  FC 1F 08 40 */	fcmpo cr0, f31, f1
/* 80006204 00002DE4  40 81 00 48 */	ble lbl_8000624C
/* 80006208 00002DE8  EC 7F D8 2A */	fadds f3, f31, f27
/* 8000620C 00002DEC  C0 81 00 E8 */	lfs f4, 0xe8(r1)
/* 80006210 00002DF0  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 80006214 00002DF4  40 80 00 18 */	bge lbl_8000622C
/* 80006218 00002DF8  C0 5D 00 04 */	lfs f2, 4(r29)
/* 8000621C 00002DFC  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 80006220 00002E00  40 80 00 0C */	bge lbl_8000622C
/* 80006224 00002E04  38 60 00 00 */	li r3, 0
/* 80006228 00002E08  48 00 05 84 */	b lbl_800067AC
lbl_8000622C:
/* 8000622C 00002E0C  EC 61 D8 28 */	fsubs f3, f1, f27
/* 80006230 00002E10  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 80006234 00002E14  40 81 00 5C */	ble lbl_80006290
/* 80006238 00002E18  C0 5D 00 04 */	lfs f2, 4(r29)
/* 8000623C 00002E1C  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 80006240 00002E20  40 81 00 50 */	ble lbl_80006290
/* 80006244 00002E24  38 60 00 00 */	li r3, 0
/* 80006248 00002E28  48 00 05 64 */	b lbl_800067AC
lbl_8000624C:
/* 8000624C 00002E2C  EC 7F D8 28 */	fsubs f3, f31, f27
/* 80006250 00002E30  C0 81 00 E8 */	lfs f4, 0xe8(r1)
/* 80006254 00002E34  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 80006258 00002E38  40 81 00 18 */	ble lbl_80006270
/* 8000625C 00002E3C  C0 5D 00 04 */	lfs f2, 4(r29)
/* 80006260 00002E40  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 80006264 00002E44  40 81 00 0C */	ble lbl_80006270
/* 80006268 00002E48  38 60 00 00 */	li r3, 0
/* 8000626C 00002E4C  48 00 05 40 */	b lbl_800067AC
lbl_80006270:
/* 80006270 00002E50  EC 61 D8 2A */	fadds f3, f1, f27
/* 80006274 00002E54  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 80006278 00002E58  40 80 00 18 */	bge lbl_80006290
/* 8000627C 00002E5C  C0 5D 00 04 */	lfs f2, 4(r29)
/* 80006280 00002E60  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 80006284 00002E64  40 80 00 0C */	bge lbl_80006290
/* 80006288 00002E68  38 60 00 00 */	li r3, 0
/* 8000628C 00002E6C  48 00 05 20 */	b lbl_800067AC
lbl_80006290:
/* 80006290 00002E70  C3 C1 00 F8 */	lfs f30, 0xf8(r1)
/* 80006294 00002E74  C0 5B 00 08 */	lfs f2, 8(r27)
/* 80006298 00002E78  FC 1E 10 40 */	fcmpo cr0, f30, f2
/* 8000629C 00002E7C  40 81 00 48 */	ble lbl_800062E4
/* 800062A0 00002E80  EC 9E D8 2A */	fadds f4, f30, f27
/* 800062A4 00002E84  C0 A1 00 EC */	lfs f5, 0xec(r1)
/* 800062A8 00002E88  FC 04 28 40 */	fcmpo cr0, f4, f5
/* 800062AC 00002E8C  40 80 00 18 */	bge lbl_800062C4
/* 800062B0 00002E90  C0 7D 00 08 */	lfs f3, 8(r29)
/* 800062B4 00002E94  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 800062B8 00002E98  40 80 00 0C */	bge lbl_800062C4
/* 800062BC 00002E9C  38 60 00 00 */	li r3, 0
/* 800062C0 00002EA0  48 00 04 EC */	b lbl_800067AC
lbl_800062C4:
/* 800062C4 00002EA4  EC 82 D8 28 */	fsubs f4, f2, f27
/* 800062C8 00002EA8  FC 04 28 40 */	fcmpo cr0, f4, f5
/* 800062CC 00002EAC  40 81 00 5C */	ble lbl_80006328
/* 800062D0 00002EB0  C0 7D 00 08 */	lfs f3, 8(r29)
/* 800062D4 00002EB4  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 800062D8 00002EB8  40 81 00 50 */	ble lbl_80006328
/* 800062DC 00002EBC  38 60 00 00 */	li r3, 0
/* 800062E0 00002EC0  48 00 04 CC */	b lbl_800067AC
lbl_800062E4:
/* 800062E4 00002EC4  EC 9E D8 28 */	fsubs f4, f30, f27
/* 800062E8 00002EC8  C0 A1 00 EC */	lfs f5, 0xec(r1)
/* 800062EC 00002ECC  FC 04 28 40 */	fcmpo cr0, f4, f5
/* 800062F0 00002ED0  40 81 00 18 */	ble lbl_80006308
/* 800062F4 00002ED4  C0 7D 00 08 */	lfs f3, 8(r29)
/* 800062F8 00002ED8  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 800062FC 00002EDC  40 81 00 0C */	ble lbl_80006308
/* 80006300 00002EE0  38 60 00 00 */	li r3, 0
/* 80006304 00002EE4  48 00 04 A8 */	b lbl_800067AC
lbl_80006308:
/* 80006308 00002EE8  EC 82 D8 2A */	fadds f4, f2, f27
/* 8000630C 00002EEC  FC 04 28 40 */	fcmpo cr0, f4, f5
/* 80006310 00002EF0  40 80 00 18 */	bge lbl_80006328
/* 80006314 00002EF4  C0 7D 00 08 */	lfs f3, 8(r29)
/* 80006318 00002EF8  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 8000631C 00002EFC  40 80 00 0C */	bge lbl_80006328
/* 80006320 00002F00  38 60 00 00 */	li r3, 0
/* 80006324 00002F04  48 00 04 88 */	b lbl_800067AC
lbl_80006328:
/* 80006328 00002F08  C3 A1 00 E8 */	lfs f29, 0xe8(r1)
/* 8000632C 00002F0C  EF 21 F8 28 */	fsubs f25, f1, f31
/* 80006330 00002F10  C0 BD 00 04 */	lfs f5, 4(r29)
/* 80006334 00002F14  EF 02 F0 28 */	fsubs f24, f2, f30
/* 80006338 00002F18  C1 81 00 F0 */	lfs f12, 0xf0(r1)
/* 8000633C 00002F1C  EE C5 E8 28 */	fsubs f22, f5, f29
/* 80006340 00002F20  C1 61 00 E4 */	lfs f11, 0xe4(r1)
/* 80006344 00002F24  ED BF E8 28 */	fsubs f13, f31, f29
/* 80006348 00002F28  C0 9D 00 00 */	lfs f4, 0(r29)
/* 8000634C 00002F2C  EF 40 60 28 */	fsubs f26, f0, f12
/* 80006350 00002F30  C3 81 00 EC */	lfs f28, 0xec(r1)
/* 80006354 00002F34  EE E4 58 28 */	fsubs f23, f4, f11
/* 80006358 00002F38  EC 79 05 B2 */	fmuls f3, f25, f22
/* 8000635C 00002F3C  C0 DD 00 08 */	lfs f6, 8(r29)
/* 80006360 00002F40  EC F6 05 B2 */	fmuls f7, f22, f22
/* 80006364 00002F44  ED 19 06 72 */	fmuls f8, f25, f25
/* 80006368 00002F48  EE A6 E0 28 */	fsubs f21, f6, f28
/* 8000636C 00002F4C  EC 7A 1D FA */	fmadds f3, f26, f23, f3
/* 80006370 00002F50  C1 22 80 10 */	lfs f9, lbl_804D79F0(r2)
/* 80006374 00002F54  EC F7 3D FA */	fmadds f7, f23, f23, f7
/* 80006378 00002F58  ED 5A 46 BA */	fmadds f10, f26, f26, f8
/* 8000637C 00002F5C  ED 18 1D 7A */	fmadds f8, f24, f21, f3
/* 80006380 00002F60  EC F5 3D 7A */	fmadds f7, f21, f21, f7
/* 80006384 00002F64  EE 6C 58 28 */	fsubs f19, f12, f11
/* 80006388 00002F68  ED 96 03 72 */	fmuls f12, f22, f13
/* 8000638C 00002F6C  ED 79 03 72 */	fmuls f11, f25, f13
/* 80006390 00002F70  EC 78 56 3A */	fmadds f3, f24, f24, f10
/* 80006394 00002F74  ED 48 02 32 */	fmuls f10, f8, f8
/* 80006398 00002F78  ED BE E0 28 */	fsubs f13, f30, f28
/* 8000639C 00002F7C  ED 97 64 FA */	fmadds f12, f23, f19, f12
/* 800063A0 00002F80  ED 7A 5C FA */	fmadds f11, f26, f19, f11
/* 800063A4 00002F84  FC 07 48 40 */	fcmpo cr0, f7, f9
/* 800063A8 00002F88  ED 95 63 7A */	fmadds f12, f21, f13, f12
/* 800063AC 00002F8C  ED 78 5B 7A */	fmadds f11, f24, f13, f11
/* 800063B0 00002F90  ED 43 51 F8 */	fmsubs f10, f3, f7, f10
/* 800063B4 00002F94  40 80 00 18 */	bge lbl_800063CC
/* 800063B8 00002F98  C1 22 80 14 */	lfs f9, lbl_804D79F4(r2)
/* 800063BC 00002F9C  FC 07 48 40 */	fcmpo cr0, f7, f9
/* 800063C0 00002FA0  40 81 00 0C */	ble lbl_800063CC
/* 800063C4 00002FA4  38 00 00 01 */	li r0, 1
/* 800063C8 00002FA8  48 00 00 08 */	b lbl_800063D0
lbl_800063CC:
/* 800063CC 00002FAC  38 00 00 00 */	li r0, 0
lbl_800063D0:
/* 800063D0 00002FB0  2C 00 00 00 */	cmpwi r0, 0
/* 800063D4 00002FB4  41 82 00 74 */	beq lbl_80006448
/* 800063D8 00002FB8  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 800063DC 00002FBC  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 800063E0 00002FC0  40 80 00 18 */	bge lbl_800063F8
/* 800063E4 00002FC4  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 800063E8 00002FC8  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 800063EC 00002FCC  40 81 00 0C */	ble lbl_800063F8
/* 800063F0 00002FD0  38 00 00 01 */	li r0, 1
/* 800063F4 00002FD4  48 00 00 08 */	b lbl_800063FC
lbl_800063F8:
/* 800063F8 00002FD8  38 00 00 00 */	li r0, 0
lbl_800063FC:
/* 800063FC 00002FDC  2C 00 00 00 */	cmpwi r0, 0
/* 80006400 00002FE0  41 82 00 10 */	beq lbl_80006410
/* 80006404 00002FE4  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80006408 00002FE8  FE 80 00 90 */	fmr f20, f0
/* 8000640C 00002FEC  48 00 03 20 */	b lbl_8000672C
lbl_80006410:
/* 80006410 00002FF0  FC 20 58 50 */	fneg f1, f11
/* 80006414 00002FF4  C8 02 80 20 */	lfd f0, lbl_804D7A00(r2)
/* 80006418 00002FF8  C2 82 80 18 */	lfs f20, lbl_804D79F8(r2)
/* 8000641C 00002FFC  EC 21 18 24 */	fdivs f1, f1, f3
/* 80006420 00003000  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80006424 00003004  FC 00 08 90 */	fmr f0, f1
/* 80006428 00003008  40 81 00 0C */	ble lbl_80006434
/* 8000642C 0000300C  C0 02 80 28 */	lfs f0, lbl_804D7A08(r2)
/* 80006430 00003010  48 00 02 FC */	b lbl_8000672C
lbl_80006434:
/* 80006434 00003014  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006438 00003018  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8000643C 0000301C  40 80 02 F0 */	bge lbl_8000672C
/* 80006440 00003020  FC 00 A0 90 */	fmr f0, f20
/* 80006444 00003024  48 00 02 E8 */	b lbl_8000672C
lbl_80006448:
/* 80006448 00003028  C1 22 80 10 */	lfs f9, lbl_804D79F0(r2)
/* 8000644C 0000302C  FC 0A 48 40 */	fcmpo cr0, f10, f9
/* 80006450 00003030  40 80 00 18 */	bge lbl_80006468
/* 80006454 00003034  C1 22 80 14 */	lfs f9, lbl_804D79F4(r2)
/* 80006458 00003038  FC 0A 48 40 */	fcmpo cr0, f10, f9
/* 8000645C 0000303C  40 81 00 0C */	ble lbl_80006468
/* 80006460 00003040  38 00 00 01 */	li r0, 1
/* 80006464 00003044  48 00 00 08 */	b lbl_8000646C
lbl_80006468:
/* 80006468 00003048  38 00 00 00 */	li r0, 0
lbl_8000646C:
/* 8000646C 0000304C  2C 00 00 00 */	cmpwi r0, 0
/* 80006470 00003050  41 82 01 D8 */	beq lbl_80006648
/* 80006474 00003054  C9 02 80 38 */	lfd f8, lbl_804D7A18(r2)
/* 80006478 00003058  C0 E1 00 E4 */	lfs f7, 0xe4(r1)
/* 8000647C 0000305C  FD 28 ED BA */	fmadd f9, f8, f22, f29
/* 80006480 00003060  C0 61 00 F0 */	lfs f3, 0xf0(r1)
/* 80006484 00003064  FC E8 3D FA */	fmadd f7, f8, f23, f7
/* 80006488 00003068  FD 20 48 18 */	frsp f9, f9
/* 8000648C 0000306C  FD 08 E5 7A */	fmadd f8, f8, f21, f28
/* 80006490 00003070  FC E0 38 18 */	frsp f7, f7
/* 80006494 00003074  ED 5F 48 28 */	fsubs f10, f31, f9
/* 80006498 00003078  ED 61 48 28 */	fsubs f11, f1, f9
/* 8000649C 0000307C  FD 00 40 18 */	frsp f8, f8
/* 800064A0 00003080  EC 63 38 28 */	fsubs f3, f3, f7
/* 800064A4 00003084  EC 2A 02 B2 */	fmuls f1, f10, f10
/* 800064A8 00003088  ED 20 38 28 */	fsubs f9, f0, f7
/* 800064AC 0000308C  EC 0B 02 F2 */	fmuls f0, f11, f11
/* 800064B0 00003090  EC FE 40 28 */	fsubs f7, f30, f8
/* 800064B4 00003094  EC 23 08 FA */	fmadds f1, f3, f3, f1
/* 800064B8 00003098  EC 42 40 28 */	fsubs f2, f2, f8
/* 800064BC 0000309C  EC 09 02 7A */	fmadds f0, f9, f9, f0
/* 800064C0 000030A0  EC 27 09 FA */	fmadds f1, f7, f7, f1
/* 800064C4 000030A4  EC 02 00 BA */	fmadds f0, f2, f2, f0
/* 800064C8 000030A8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800064CC 000030AC  40 80 00 C0 */	bge lbl_8000658C
/* 800064D0 000030B0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800064D4 000030B4  80 61 00 38 */	lwz r3, 0x38(r1)
/* 800064D8 000030B8  90 01 00 70 */	stw r0, 0x70(r1)
/* 800064DC 000030BC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800064E0 000030C0  90 61 00 74 */	stw r3, 0x74(r1)
/* 800064E4 000030C4  80 81 00 28 */	lwz r4, 0x28(r1)
/* 800064E8 000030C8  90 01 00 78 */	stw r0, 0x78(r1)
/* 800064EC 000030CC  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 800064F0 000030D0  C0 5C 00 00 */	lfs f2, 0(r28)
/* 800064F4 000030D4  C0 1C 00 04 */	lfs f0, 4(r28)
/* 800064F8 000030D8  C0 3C 00 08 */	lfs f1, 8(r28)
/* 800064FC 000030DC  EC E4 10 28 */	fsubs f7, f4, f2
/* 80006500 000030E0  ED 05 00 28 */	fsubs f8, f5, f0
/* 80006504 000030E4  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80006508 000030E8  90 81 00 88 */	stw r4, 0x88(r1)
/* 8000650C 000030EC  ED 26 08 28 */	fsubs f9, f6, f1
/* 80006510 000030F0  90 61 00 8C */	stw r3, 0x8c(r1)
/* 80006514 000030F4  EC 08 02 32 */	fmuls f0, f8, f8
/* 80006518 000030F8  C0 61 00 74 */	lfs f3, 0x74(r1)
/* 8000651C 000030FC  90 01 00 90 */	stw r0, 0x90(r1)
/* 80006520 00003100  C0 A1 00 70 */	lfs f5, 0x70(r1)
/* 80006524 00003104  EC 47 01 FA */	fmadds f2, f7, f7, f0
/* 80006528 00003108  C0 21 00 8C */	lfs f1, 0x8c(r1)
/* 8000652C 0000310C  C0 81 00 88 */	lfs f4, 0x88(r1)
/* 80006530 00003110  EC 03 08 28 */	fsubs f0, f3, f1
/* 80006534 00003114  C0 C1 00 78 */	lfs f6, 0x78(r1)
/* 80006538 00003118  EC 85 20 28 */	fsubs f4, f5, f4
/* 8000653C 0000311C  C0 21 00 90 */	lfs f1, 0x90(r1)
/* 80006540 00003120  EC 49 12 7A */	fmadds f2, f9, f9, f2
/* 80006544 00003124  EC 68 00 32 */	fmuls f3, f8, f0
/* 80006548 00003128  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 8000654C 0000312C  EC A6 08 28 */	fsubs f5, f6, f1
/* 80006550 00003130  C8 22 80 20 */	lfd f1, lbl_804D7A00(r2)
/* 80006554 00003134  EC 67 19 3A */	fmadds f3, f7, f4, f3
/* 80006558 00003138  EC 69 19 7A */	fmadds f3, f9, f5, f3
/* 8000655C 0000313C  FC 60 18 50 */	fneg f3, f3
/* 80006560 00003140  EC 43 10 24 */	fdivs f2, f3, f2
/* 80006564 00003144  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006568 00003148  40 81 00 0C */	ble lbl_80006574
/* 8000656C 0000314C  C0 42 80 28 */	lfs f2, lbl_804D7A08(r2)
/* 80006570 00003150  48 00 00 14 */	b lbl_80006584
lbl_80006574:
/* 80006574 00003154  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006578 00003158  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8000657C 0000315C  40 80 00 08 */	bge lbl_80006584
/* 80006580 00003160  FC 40 00 90 */	fmr f2, f0
lbl_80006584:
/* 80006584 00003164  FE 80 10 90 */	fmr f20, f2
/* 80006588 00003168  48 00 01 A4 */	b lbl_8000672C
lbl_8000658C:
/* 8000658C 0000316C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80006590 00003170  80 61 00 38 */	lwz r3, 0x38(r1)
/* 80006594 00003174  90 01 00 40 */	stw r0, 0x40(r1)
/* 80006598 00003178  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8000659C 0000317C  90 61 00 44 */	stw r3, 0x44(r1)
/* 800065A0 00003180  C8 22 80 20 */	lfd f1, lbl_804D7A00(r2)
/* 800065A4 00003184  90 01 00 48 */	stw r0, 0x48(r1)
/* 800065A8 00003188  C0 02 80 28 */	lfs f0, lbl_804D7A08(r2)
/* 800065AC 0000318C  C0 FC 00 00 */	lfs f7, 0(r28)
/* 800065B0 00003190  C0 5C 00 04 */	lfs f2, 4(r28)
/* 800065B4 00003194  C0 7C 00 08 */	lfs f3, 8(r28)
/* 800065B8 00003198  ED 24 38 28 */	fsubs f9, f4, f7
/* 800065BC 0000319C  80 7B 00 00 */	lwz r3, 0(r27)
/* 800065C0 000031A0  ED 45 10 28 */	fsubs f10, f5, f2
/* 800065C4 000031A4  80 1B 00 04 */	lwz r0, 4(r27)
/* 800065C8 000031A8  C0 81 00 44 */	lfs f4, 0x44(r1)
/* 800065CC 000031AC  90 61 00 58 */	stw r3, 0x58(r1)
/* 800065D0 000031B0  EC 4A 02 B2 */	fmuls f2, f10, f10
/* 800065D4 000031B4  ED 66 18 28 */	fsubs f11, f6, f3
/* 800065D8 000031B8  C0 E1 00 40 */	lfs f7, 0x40(r1)
/* 800065DC 000031BC  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800065E0 000031C0  EC 49 12 7A */	fmadds f2, f9, f9, f2
/* 800065E4 000031C4  80 1B 00 08 */	lwz r0, 8(r27)
/* 800065E8 000031C8  C1 01 00 48 */	lfs f8, 0x48(r1)
/* 800065EC 000031CC  90 01 00 60 */	stw r0, 0x60(r1)
/* 800065F0 000031D0  EC 4B 12 FA */	fmadds f2, f11, f11, f2
/* 800065F4 000031D4  C0 61 00 5C */	lfs f3, 0x5c(r1)
/* 800065F8 000031D8  C0 A1 00 58 */	lfs f5, 0x58(r1)
/* 800065FC 000031DC  EC 64 18 28 */	fsubs f3, f4, f3
/* 80006600 000031E0  C0 C1 00 60 */	lfs f6, 0x60(r1)
/* 80006604 000031E4  EC 87 28 28 */	fsubs f4, f7, f5
/* 80006608 000031E8  EC A8 30 28 */	fsubs f5, f8, f6
/* 8000660C 000031EC  EC 6A 00 F2 */	fmuls f3, f10, f3
/* 80006610 000031F0  EC 69 19 3A */	fmadds f3, f9, f4, f3
/* 80006614 000031F4  EC 6B 19 7A */	fmadds f3, f11, f5, f3
/* 80006618 000031F8  FC 60 18 50 */	fneg f3, f3
/* 8000661C 000031FC  EC 43 10 24 */	fdivs f2, f3, f2
/* 80006620 00003200  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006624 00003204  40 81 00 0C */	ble lbl_80006630
/* 80006628 00003208  FC 40 00 90 */	fmr f2, f0
/* 8000662C 0000320C  48 00 00 14 */	b lbl_80006640
lbl_80006630:
/* 80006630 00003210  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006634 00003214  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006638 00003218  40 80 00 08 */	bge lbl_80006640
/* 8000663C 0000321C  C0 42 80 18 */	lfs f2, lbl_804D79F8(r2)
lbl_80006640:
/* 80006640 00003220  FE 80 10 90 */	fmr f20, f2
/* 80006644 00003224  48 00 00 E8 */	b lbl_8000672C
lbl_80006648:
/* 80006648 00003228  EC 27 02 F2 */	fmuls f1, f7, f11
/* 8000664C 0000322C  C8 42 80 20 */	lfd f2, lbl_804D7A00(r2)
/* 80006650 00003230  EC 08 02 F2 */	fmuls f0, f8, f11
/* 80006654 00003234  EC 28 0B 38 */	fmsubs f1, f8, f12, f1
/* 80006658 00003238  EC 03 03 38 */	fmsubs f0, f3, f12, f0
/* 8000665C 0000323C  EC 21 50 24 */	fdivs f1, f1, f10
/* 80006660 00003240  EE 80 50 24 */	fdivs f20, f0, f10
/* 80006664 00003244  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 80006668 00003248  FC 00 08 90 */	fmr f0, f1
/* 8000666C 0000324C  41 81 00 20 */	bgt lbl_8000668C
/* 80006670 00003250  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006674 00003254  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80006678 00003258  41 80 00 14 */	blt lbl_8000668C
/* 8000667C 0000325C  FC 14 10 40 */	fcmpo cr0, f20, f2
/* 80006680 00003260  41 81 00 0C */	bgt lbl_8000668C
/* 80006684 00003264  FC 14 08 40 */	fcmpo cr0, f20, f1
/* 80006688 00003268  40 80 00 A4 */	bge lbl_8000672C
lbl_8000668C:
/* 8000668C 0000326C  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006690 00003270  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80006694 00003274  40 80 00 24 */	bge lbl_800066B8
/* 80006698 00003278  C2 62 80 18 */	lfs f19, lbl_804D79F8(r2)
/* 8000669C 0000327C  38 7C 00 00 */	addi r3, r28, 0
/* 800066A0 00003280  38 9D 00 00 */	addi r4, r29, 0
/* 800066A4 00003284  38 BA 00 00 */	addi r5, r26, 0
/* 800066A8 00003288  38 C1 00 A4 */	addi r6, r1, 0xa4
/* 800066AC 0000328C  4B FF F8 11 */	bl lbColl_80005EBC
/* 800066B0 00003290  FE 40 08 90 */	fmr f18, f1
/* 800066B4 00003294  48 00 00 20 */	b lbl_800066D4
lbl_800066B8:
/* 800066B8 00003298  C2 62 80 28 */	lfs f19, lbl_804D7A08(r2)
/* 800066BC 0000329C  38 7C 00 00 */	addi r3, r28, 0
/* 800066C0 000032A0  38 9D 00 00 */	addi r4, r29, 0
/* 800066C4 000032A4  38 BB 00 00 */	addi r5, r27, 0
/* 800066C8 000032A8  38 C1 00 A4 */	addi r6, r1, 0xa4
/* 800066CC 000032AC  4B FF F7 F1 */	bl lbColl_80005EBC
/* 800066D0 000032B0  FE 40 08 90 */	fmr f18, f1
lbl_800066D4:
/* 800066D4 000032B4  C8 02 80 30 */	lfd f0, lbl_804D7A10(r2)
/* 800066D8 000032B8  FC 14 00 40 */	fcmpo cr0, f20, f0
/* 800066DC 000032BC  40 80 00 20 */	bge lbl_800066FC
/* 800066E0 000032C0  C2 82 80 18 */	lfs f20, lbl_804D79F8(r2)
/* 800066E4 000032C4  38 7A 00 00 */	addi r3, r26, 0
/* 800066E8 000032C8  38 9B 00 00 */	addi r4, r27, 0
/* 800066EC 000032CC  38 BC 00 00 */	addi r5, r28, 0
/* 800066F0 000032D0  38 C1 00 A0 */	addi r6, r1, 0xa0
/* 800066F4 000032D4  4B FF F7 C9 */	bl lbColl_80005EBC
/* 800066F8 000032D8  48 00 00 1C */	b lbl_80006714
lbl_800066FC:
/* 800066FC 000032DC  C2 82 80 28 */	lfs f20, lbl_804D7A08(r2)
/* 80006700 000032E0  38 7A 00 00 */	addi r3, r26, 0
/* 80006704 000032E4  38 9B 00 00 */	addi r4, r27, 0
/* 80006708 000032E8  38 BD 00 00 */	addi r5, r29, 0
/* 8000670C 000032EC  38 C1 00 A0 */	addi r6, r1, 0xa0
/* 80006710 000032F0  4B FF F7 AD */	bl lbColl_80005EBC
lbl_80006714:
/* 80006714 000032F4  FC 12 08 40 */	fcmpo cr0, f18, f1
/* 80006718 000032F8  40 80 00 10 */	bge lbl_80006728
/* 8000671C 000032FC  FC 00 98 90 */	fmr f0, f19
/* 80006720 00003300  C2 81 00 A4 */	lfs f20, 0xa4(r1)
/* 80006724 00003304  48 00 00 08 */	b lbl_8000672C
lbl_80006728:
/* 80006728 00003308  C0 01 00 A0 */	lfs f0, 0xa0(r1)
lbl_8000672C:
/* 8000672C 0000330C  C0 21 00 F0 */	lfs f1, 0xf0(r1)
/* 80006730 00003310  EC 99 F8 3A */	fmadds f4, f25, f0, f31
/* 80006734 00003314  EC 78 F0 3A */	fmadds f3, f24, f0, f30
/* 80006738 00003318  EC 3A 08 3A */	fmadds f1, f26, f0, f1
/* 8000673C 0000331C  EC 56 ED 3A */	fmadds f2, f22, f20, f29
/* 80006740 00003320  EC 15 E5 3A */	fmadds f0, f21, f20, f28
/* 80006744 00003324  D0 3E 00 00 */	stfs f1, 0(r30)
/* 80006748 00003328  EC 3B 06 F2 */	fmuls f1, f27, f27
/* 8000674C 0000332C  D0 9E 00 04 */	stfs f4, 4(r30)
/* 80006750 00003330  D0 7E 00 08 */	stfs f3, 8(r30)
/* 80006754 00003334  C0 61 00 E4 */	lfs f3, 0xe4(r1)
/* 80006758 00003338  EC 77 1D 3A */	fmadds f3, f23, f20, f3
/* 8000675C 0000333C  D0 7F 00 00 */	stfs f3, 0(r31)
/* 80006760 00003340  D0 5F 00 04 */	stfs f2, 4(r31)
/* 80006764 00003344  D0 1F 00 08 */	stfs f0, 8(r31)
/* 80006768 00003348  C0 5E 00 04 */	lfs f2, 4(r30)
/* 8000676C 0000334C  C0 1F 00 04 */	lfs f0, 4(r31)
/* 80006770 00003350  C0 9E 00 00 */	lfs f4, 0(r30)
/* 80006774 00003354  EC A2 00 28 */	fsubs f5, f2, f0
/* 80006778 00003358  C0 1F 00 00 */	lfs f0, 0(r31)
/* 8000677C 0000335C  C0 7E 00 08 */	lfs f3, 8(r30)
/* 80006780 00003360  EC 84 00 28 */	fsubs f4, f4, f0
/* 80006784 00003364  C0 5F 00 08 */	lfs f2, 8(r31)
/* 80006788 00003368  EC 05 01 72 */	fmuls f0, f5, f5
/* 8000678C 0000336C  EC 43 10 28 */	fsubs f2, f3, f2
/* 80006790 00003370  EC 04 01 3A */	fmadds f0, f4, f4, f0
/* 80006794 00003374  EC 02 00 BA */	fmadds f0, f2, f2, f0
/* 80006798 00003378  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8000679C 0000337C  40 80 00 0C */	bge lbl_800067A8
/* 800067A0 00003380  38 60 00 00 */	li r3, 0
/* 800067A4 00003384  48 00 00 08 */	b lbl_800067AC
lbl_800067A8:
/* 800067A8 00003388  38 60 00 01 */	li r3, 1
lbl_800067AC:
/* 800067AC 0000338C  BB 41 01 00 */	lmw r26, 0x100(r1)
/* 800067B0 00003390  80 01 01 8C */	lwz r0, 0x18c(r1)
/* 800067B4 00003394  CB E1 01 80 */	lfd f31, 0x180(r1)
/* 800067B8 00003398  CB C1 01 78 */	lfd f30, 0x178(r1)
/* 800067BC 0000339C  CB A1 01 70 */	lfd f29, 0x170(r1)
/* 800067C0 000033A0  CB 81 01 68 */	lfd f28, 0x168(r1)
/* 800067C4 000033A4  CB 61 01 60 */	lfd f27, 0x160(r1)
/* 800067C8 000033A8  CB 41 01 58 */	lfd f26, 0x158(r1)
/* 800067CC 000033AC  CB 21 01 50 */	lfd f25, 0x150(r1)
/* 800067D0 000033B0  CB 01 01 48 */	lfd f24, 0x148(r1)
/* 800067D4 000033B4  CA E1 01 40 */	lfd f23, 0x140(r1)
/* 800067D8 000033B8  CA C1 01 38 */	lfd f22, 0x138(r1)
/* 800067DC 000033BC  CA A1 01 30 */	lfd f21, 0x130(r1)
/* 800067E0 000033C0  CA 81 01 28 */	lfd f20, 0x128(r1)
/* 800067E4 000033C4  CA 61 01 20 */	lfd f19, 0x120(r1)
/* 800067E8 000033C8  CA 41 01 18 */	lfd f18, 0x118(r1)
/* 800067EC 000033CC  38 21 01 88 */	addi r1, r1, 0x188
/* 800067F0 000033D0  7C 08 03 A6 */	mtlr r0
/* 800067F4 000033D4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

inline bool end(Vec3* a, Vec3* b, f32 unk_sum)
{
    f32 y = a->y - b->y;
    f32 x = a->x - b->x;
    f32 z = a->z - b->z;

    if (unk_sum * unk_sum < z * z + (x * x + y * y))
        return false;

    return true;
}

int lbColl_80006094(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3, Vec3* arg4,
                    Vec3* arg5, f32 arg6, f32 arg7)
{
    {
        Vec3 vec4;
        f32 sp30;
        f32 sp34;
        f32 sp38;
        Vec3 arg4_offset;
        Vec3 arg5_offset;
        f32 sp3C;
        f32 temp_f1;
        f32 unk_sum = arg6 + arg7;
        vec4.x = arg0->x;
        vec4.y = arg0->y;
        vec4.z = arg0->z;

        sp30 = vec4.z;
        sp34 = arg2->x;
        sp38 = arg2->y;

        arg4_offset.x = vec4.x;
        arg4_offset.y = vec4.y;
        arg4_offset.z = vec4.z;

        {
            f32 temp_r0_2 = arg2->z;
            sp3C = temp_r0_2;

            arg5_offset.x = sp34;
            arg5_offset.y = sp38;
            arg5_offset.z = temp_r0_2;
        }

        {
            f32 arg1_x = arg1->x;
            if (arg4_offset.x > arg1_x) {
                if (!testPlusX(&arg4_offset, &arg5_offset, arg3, unk_sum))
                    return false;

                if (!testMinusX(&arg4_offset, &arg5_offset, arg3, unk_sum))
                    return false;

                goto block_13;
            }
            {
                if (!testMinusX(&arg4_offset, &arg5_offset, arg3, unk_sum))
                    return false;
            }
            {
                f32 x = arg1_x + unk_sum;
                if (x < arg5_offset.x && x < arg3->x)
                    return false;
            }

        block_13 : {
            temp_f1 = arg1->y;
            if (arg4_offset.y > temp_f1) {
                {
                    f32 temp_f3;
                    temp_f3 = arg4_offset.y + unk_sum;

                    if (temp_f3 < arg5_offset.y && temp_f3 < arg3->y)
                        return false;
                }

                {
                    f32 temp_f3_2 = temp_f1 - unk_sum;

                    if (temp_f3_2 > arg5_offset.y && temp_f3_2 > arg3->y)
                        return false;
                }

                goto block_26;
            }

            {
                f32 y = arg4_offset.y - unk_sum;
                if (y > arg5_offset.y && y > arg3->y)
                    return false;
            }

            {
                f32 y = temp_f1 + unk_sum;
                if (y < arg5_offset.y && y < arg3->y)
                    return false;
            }
        }
        block_26 : {
            f32 temp_f2_5 = arg1->z;
            if (arg4_offset.z > temp_f2_5) {
                {
                    f32 temp_f4;
                    temp_f4 = arg4_offset.z + unk_sum;
                    if ((temp_f4 < arg5_offset.z) && (temp_f4 < arg3->z)) {
                        return false;
                    }
                }
                {
                    f32 temp_f4_2;
                    temp_f4_2 = temp_f2_5 - unk_sum;
                    if ((temp_f4_2 > arg5_offset.z) && (temp_f4_2 > arg3->z)) {
                        return false;
                    }
                }
                goto block_39;
            }
            {
                f32 temp_f4_3;
                temp_f4_3 = arg4_offset.z - unk_sum;
                if ((temp_f4_3 > arg5_offset.z) && (temp_f4_3 > arg3->z)) {
                    return false;
                }
            }
            {
                f32 temp_f4_4;
                temp_f4_4 = temp_f2_5 + unk_sum;
                if ((temp_f4_4 < arg5_offset.z) && (temp_f4_4 < arg3->z)) {
                    return false;
                }
            }
        block_39 : {
            f32 arg4_scl;

            f32 temp_f25 = temp_f1 - arg4_offset.y;
            f32 temp_f5 = arg3->y;
            f32 temp_f24 = temp_f2_5 - arg4_offset.z;
            f32 temp_f22 = temp_f5 - arg5_offset.y;
            f32 temp_f13 = arg4_offset.y - arg5_offset.y;
            f32 temp_f4_5 = arg3->x;
            f32 temp_f26 = arg1_x - arg4_offset.x;
            f32 temp_f23 = temp_f4_5 - arg5_offset.x;
            f32 temp_f6 = arg3->z;
            f32 arg5_offset_base = temp_f6 - arg5_offset.z;
            f32 temp_f8 = temp_f24 * arg5_offset_base + temp_f26 * temp_f23 +
                          temp_f25 * temp_f22;
            f32 temp_f7 = arg5_offset_base * arg5_offset_base +
                          temp_f23 * temp_f23 + temp_f22 * temp_f22;
            f32 temp_f19 = arg4_offset.x - arg5_offset.x;
            f32 temp_f3_5 = (temp_f24 * temp_f24) +
                            ((temp_f26 * temp_f26) + (temp_f25 * temp_f25));
            f32 temp_f13_2 = arg4_offset.z - arg5_offset.z;
            f32 temp_f12 = arg5_offset_base * temp_f13_2 +
                           temp_f23 * temp_f19 + temp_f22 * temp_f13;
            f32 temp_f11 = (temp_f24 * temp_f13_2) + temp_f26 * temp_f19 +
                           temp_f25 * temp_f13;
            f32 temp_f10 = temp_f3_5 * temp_f7 - temp_f8 * temp_f8;

            {
                f32 arg5_scl;
                if (approximatelyZero(temp_f7)) {
                    if (approximatelyZero(temp_f3_5)) {
                        arg4_scl = 0.0f;
                        arg5_scl = 0.0f;
                    } else {
                        arg5_scl = 0.0f;
                        {
                            f32 temp_f1_2 = -temp_f11 / temp_f3_5;
                            arg4_scl = temp_f1_2;

                            if (temp_f1_2 > (f32) 1.0)
                                arg4_scl = 1.0f;
                            else if (arg4_scl < (f32) 0.0)
                                arg4_scl = 0.0f;
                        }
                    }
                } else {
                    if (approximatelyZero(temp_f10)) {
                        f32 temp_f9 = (0.5 * temp_f22 + arg5_offset.y);
                        f32 temp_f7_2 = (0.5 * temp_f23 + arg5_offset.x);
                        f32 temp_f10_2 = arg4_offset.y - temp_f9;
                        f32 temp_f11_2 = temp_f1 - temp_f9;
                        f32 temp_f8_2 = 0.5 * arg5_offset_base + arg5_offset.z;
                        f32 temp_f3_6 = arg4_offset.x - temp_f7_2;
                        f32 temp_f9_2 = arg1_x - temp_f7_2;
                        f32 arg4_offset_z = arg4_offset.z - temp_f8_2;
                        f32 temp_f2_6 = temp_f2_5 - temp_f8_2;

                        // lhs and rhs each the same inline
                        if ((arg4_offset_z * arg4_offset_z +
                             ((temp_f3_6 * temp_f3_6) +
                              (temp_f10_2 * temp_f10_2))) <
                            ((temp_f2_6 * temp_f2_6) +
                             ((temp_f9_2 * temp_f9_2) +
                              (temp_f11_2 * temp_f11_2))))
                        {
                            Vec3 vec2;
                            f32 sp90;
                            f32 sp8C;
                            f32 sp88;
                            f32 temp_f7_4;
                            f32 temp_f8_3;
                            f32 temp_f9_3;
                            vec2.x = sp34;
                            vec2.y = sp38;
                            vec2.z = sp3C;
                            temp_f7_4 = temp_f4_5 - arg2->x;
                            temp_f8_3 = temp_f5 - arg2->y;
                            sp88 = vec4.x;
                            temp_f9_3 = temp_f6 - arg2->z;
                            sp8C = vec4.y;
                            sp90 = sp30;
                            arg4_scl = 0.0f;
                            {
                                f32 var_f2 =
                                    -((temp_f9_3 * (vec2.z - sp90)) +
                                      ((temp_f7_4 * (vec2.x - sp88)) +
                                       (temp_f8_3 * (vec2.y - sp8C)))) /
                                    ((temp_f9_3 * temp_f9_3) +
                                     ((temp_f7_4 * temp_f7_4) +
                                      (temp_f8_3 * temp_f8_3)));
                                if (var_f2 > (f32) 1.0) {
                                    var_f2 = 1.0f;
                                } else if (var_f2 < (f32) 0.0) {
                                    var_f2 = 0.0f;
                                }
                                arg5_scl = var_f2;
                            }
                        } else {
                            f32 sp58;
                            f32 sp60;
                            f32 sp48;
                            f32 sp5C;
                            f32 sp44;
                            f32 sp40;
                            f32 temp_f10_3;
                            f32 temp_f11_3;
                            f32 temp_f9_4;
                            sp40 = sp34;
                            sp44 = sp38;
                            sp48 = sp3C;
                            arg4_scl = 1.0f;
                            temp_f9_4 = temp_f4_5 - arg2->x;
                            temp_f10_3 = temp_f5 - arg2->y;
                            sp58 = arg1->x;
                            temp_f11_3 = temp_f6 - arg2->z;
                            sp5C = arg1->y;
                            sp60 = arg1->z;
                            {
                                f32 var_f2_2 =
                                    -temp_f11_3 * (sp48 - sp60) +
                                    temp_f9_4 * sp40 - sp58 +
                                    temp_f10_3 * sp44 -
                                    sp5C / (temp_f11_3 * temp_f11_3) +
                                    temp_f9_4 * temp_f9_4 +
                                    temp_f10_3 * temp_f10_3;

                                if (var_f2_2 > (f32) 1.0)
                                    var_f2_2 = 1.0f;
                                else if (var_f2_2 < (f32) 0.0)
                                    var_f2_2 = 0.0f;

                                arg5_scl = var_f2_2;
                            }
                        }
                    } else {
                        f32 temp_f1_3 =
                            temp_f8 * temp_f12 - temp_f7 * temp_f11 / temp_f10;
                        arg5_scl =
                            ((temp_f3_5 * temp_f12) - (temp_f8 * temp_f11)) /
                            temp_f10;
                        arg4_scl = temp_f1_3;
                        if (temp_f1_3 > (f32) 1.0 || arg4_scl < (f32) 0.0 ||
                            arg5_scl > (f32) 1.0 || arg5_scl < (f32) 0.0)
                        {
                            f32 var_f18;
                            f32 var_f19;
                            f32 var_f1;
                            f32 spA4;

                            if (arg4_scl < (f32) 0.0) {
                                var_f19 = 0.0f;
                                var_f18 =
                                    lbColl_80005EBC(arg2, arg3, arg0, &spA4);
                            } else {
                                var_f19 = 1.0f;
                                var_f18 =
                                    lbColl_80005EBC(arg2, arg3, arg1, &spA4);
                            }

                            {
                                f32 spA0;
                                if (arg5_scl < (f32) 0.0) {
                                    arg5_scl = 0.0f;
                                    var_f1 = lbColl_80005EBC(arg0, arg1, arg2,
                                                             &spA0);
                                } else {
                                    arg5_scl = 1.0f;
                                    var_f1 = lbColl_80005EBC(arg0, arg1, arg3,
                                                             &spA0);
                                }

                                if (var_f18 < var_f1) {
                                    arg4_scl = var_f19;
                                    arg5_scl = spA4;
                                } else {
                                    arg4_scl = spA0;
                                }
                            }
                        }
                    }
                }

                arg4->x = temp_f26 * arg4_scl + arg4_offset.x;
                arg4->y = temp_f25 * arg4_scl + arg4_offset.y;
                arg4->z = temp_f24 * arg4_scl + arg4_offset.z;

                arg5->x = temp_f23 * arg5_scl + arg5_offset.x;
                arg5->y = temp_f22 * arg5_scl + arg5_offset.y;
                arg5->z = arg5_offset_base * arg5_scl + arg5_offset.z;
            }
        }
            return end(arg4, arg5, unk_sum);
        }
        }
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm bool lbColl_800067F8(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, f32, f32,
                         f32)
{
    // clang-format off
    nofralloc
/* 800067F8 000033D8  7C 08 02 A6 */	mflr r0
/* 800067FC 000033DC  90 01 00 04 */	stw r0, 4(r1)
/* 80006800 000033E0  94 21 FE 98 */	stwu r1, -0x168(r1)
/* 80006804 000033E4  DB E1 01 60 */	stfd f31, 0x160(r1)
/* 80006808 000033E8  DB C1 01 58 */	stfd f30, 0x158(r1)
/* 8000680C 000033EC  DB A1 01 50 */	stfd f29, 0x150(r1)
/* 80006810 000033F0  DB 81 01 48 */	stfd f28, 0x148(r1)
/* 80006814 000033F4  DB 61 01 40 */	stfd f27, 0x140(r1)
/* 80006818 000033F8  DB 41 01 38 */	stfd f26, 0x138(r1)
/* 8000681C 000033FC  DB 21 01 30 */	stfd f25, 0x130(r1)
/* 80006820 00003400  EF 21 10 2A */	fadds f25, f1, f2
/* 80006824 00003404  DB 01 01 28 */	stfd f24, 0x128(r1)
/* 80006828 00003408  DA E1 01 20 */	stfd f23, 0x120(r1)
/* 8000682C 0000340C  DA C1 01 18 */	stfd f22, 0x118(r1)
/* 80006830 00003410  BF 41 01 00 */	stmw r26, 0x100(r1)
/* 80006834 00003414  7C 7A 1B 78 */	mr r26, r3
/* 80006838 00003418  7C BC 2B 78 */	mr r28, r5
/* 8000683C 0000341C  7C 9B 23 78 */	mr r27, r4
/* 80006840 00003420  3B A6 00 00 */	addi r29, r6, 0
/* 80006844 00003424  3B C7 00 00 */	addi r30, r7, 0
/* 80006848 00003428  7D 1F 43 78 */	mr r31, r8
/* 8000684C 0000342C  80 63 00 00 */	lwz r3, 0(r3)
/* 80006850 00003430  80 1A 00 04 */	lwz r0, 4(r26)
/* 80006854 00003434  90 61 00 28 */	stw r3, 0x28(r1)
/* 80006858 00003438  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8000685C 0000343C  80 1A 00 08 */	lwz r0, 8(r26)
/* 80006860 00003440  90 01 00 30 */	stw r0, 0x30(r1)
/* 80006864 00003444  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80006868 00003448  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 8000686C 0000344C  90 01 00 F0 */	stw r0, 0xf0(r1)
/* 80006870 00003450  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80006874 00003454  90 61 00 F4 */	stw r3, 0xf4(r1)
/* 80006878 00003458  90 01 00 F8 */	stw r0, 0xf8(r1)
/* 8000687C 0000345C  80 65 00 00 */	lwz r3, 0(r5)
/* 80006880 00003460  80 05 00 04 */	lwz r0, 4(r5)
/* 80006884 00003464  C0 21 00 F0 */	lfs f1, 0xf0(r1)
/* 80006888 00003468  90 61 00 34 */	stw r3, 0x34(r1)
/* 8000688C 0000346C  90 01 00 38 */	stw r0, 0x38(r1)
/* 80006890 00003470  80 05 00 08 */	lwz r0, 8(r5)
/* 80006894 00003474  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80006898 00003478  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8000689C 0000347C  80 61 00 38 */	lwz r3, 0x38(r1)
/* 800068A0 00003480  90 01 00 E4 */	stw r0, 0xe4(r1)
/* 800068A4 00003484  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800068A8 00003488  90 61 00 E8 */	stw r3, 0xe8(r1)
/* 800068AC 0000348C  90 01 00 EC */	stw r0, 0xec(r1)
/* 800068B0 00003490  C0 04 00 00 */	lfs f0, 0(r4)
/* 800068B4 00003494  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800068B8 00003498  40 81 00 4C */	ble lbl_80006904
/* 800068BC 0000349C  EC 41 C8 2A */	fadds f2, f1, f25
/* 800068C0 000034A0  C0 21 00 E4 */	lfs f1, 0xe4(r1)
/* 800068C4 000034A4  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800068C8 000034A8  40 80 00 18 */	bge lbl_800068E0
/* 800068CC 000034AC  C0 3D 00 00 */	lfs f1, 0(r29)
/* 800068D0 000034B0  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800068D4 000034B4  40 80 00 0C */	bge lbl_800068E0
/* 800068D8 000034B8  38 60 00 00 */	li r3, 0
/* 800068DC 000034BC  48 00 05 40 */	b lbl_80006E1C
lbl_800068E0:
/* 800068E0 000034C0  EC 40 C8 28 */	fsubs f2, f0, f25
/* 800068E4 000034C4  C0 21 00 E4 */	lfs f1, 0xe4(r1)
/* 800068E8 000034C8  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800068EC 000034CC  40 81 00 60 */	ble lbl_8000694C
/* 800068F0 000034D0  C0 3D 00 00 */	lfs f1, 0(r29)
/* 800068F4 000034D4  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800068F8 000034D8  40 81 00 54 */	ble lbl_8000694C
/* 800068FC 000034DC  38 60 00 00 */	li r3, 0
/* 80006900 000034E0  48 00 05 1C */	b lbl_80006E1C
lbl_80006904:
/* 80006904 000034E4  EC 41 C8 28 */	fsubs f2, f1, f25
/* 80006908 000034E8  C0 21 00 E4 */	lfs f1, 0xe4(r1)
/* 8000690C 000034EC  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006910 000034F0  40 81 00 18 */	ble lbl_80006928
/* 80006914 000034F4  C0 3D 00 00 */	lfs f1, 0(r29)
/* 80006918 000034F8  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 8000691C 000034FC  40 81 00 0C */	ble lbl_80006928
/* 80006920 00003500  38 60 00 00 */	li r3, 0
/* 80006924 00003504  48 00 04 F8 */	b lbl_80006E1C
lbl_80006928:
/* 80006928 00003508  EC 40 C8 2A */	fadds f2, f0, f25
/* 8000692C 0000350C  C0 21 00 E4 */	lfs f1, 0xe4(r1)
/* 80006930 00003510  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006934 00003514  40 80 00 18 */	bge lbl_8000694C
/* 80006938 00003518  C0 3D 00 00 */	lfs f1, 0(r29)
/* 8000693C 0000351C  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006940 00003520  40 80 00 0C */	bge lbl_8000694C
/* 80006944 00003524  38 60 00 00 */	li r3, 0
/* 80006948 00003528  48 00 04 D4 */	b lbl_80006E1C
lbl_8000694C:
/* 8000694C 0000352C  C3 61 00 F4 */	lfs f27, 0xf4(r1)
/* 80006950 00003530  C0 3B 00 04 */	lfs f1, 4(r27)
/* 80006954 00003534  FC 1B 08 40 */	fcmpo cr0, f27, f1
/* 80006958 00003538  40 81 00 48 */	ble lbl_800069A0
/* 8000695C 0000353C  EC 7B C8 2A */	fadds f3, f27, f25
/* 80006960 00003540  C0 81 00 E8 */	lfs f4, 0xe8(r1)
/* 80006964 00003544  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 80006968 00003548  40 80 00 18 */	bge lbl_80006980
/* 8000696C 0000354C  C0 5D 00 04 */	lfs f2, 4(r29)
/* 80006970 00003550  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 80006974 00003554  40 80 00 0C */	bge lbl_80006980
/* 80006978 00003558  38 60 00 00 */	li r3, 0
/* 8000697C 0000355C  48 00 04 A0 */	b lbl_80006E1C
lbl_80006980:
/* 80006980 00003560  EC 61 C8 28 */	fsubs f3, f1, f25
/* 80006984 00003564  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 80006988 00003568  40 81 00 5C */	ble lbl_800069E4
/* 8000698C 0000356C  C0 5D 00 04 */	lfs f2, 4(r29)
/* 80006990 00003570  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 80006994 00003574  40 81 00 50 */	ble lbl_800069E4
/* 80006998 00003578  38 60 00 00 */	li r3, 0
/* 8000699C 0000357C  48 00 04 80 */	b lbl_80006E1C
lbl_800069A0:
/* 800069A0 00003580  EC 7B C8 28 */	fsubs f3, f27, f25
/* 800069A4 00003584  C0 81 00 E8 */	lfs f4, 0xe8(r1)
/* 800069A8 00003588  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 800069AC 0000358C  40 81 00 18 */	ble lbl_800069C4
/* 800069B0 00003590  C0 5D 00 04 */	lfs f2, 4(r29)
/* 800069B4 00003594  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 800069B8 00003598  40 81 00 0C */	ble lbl_800069C4
/* 800069BC 0000359C  38 60 00 00 */	li r3, 0
/* 800069C0 000035A0  48 00 04 5C */	b lbl_80006E1C
lbl_800069C4:
/* 800069C4 000035A4  EC 61 C8 2A */	fadds f3, f1, f25
/* 800069C8 000035A8  FC 03 20 40 */	fcmpo cr0, f3, f4
/* 800069CC 000035AC  40 80 00 18 */	bge lbl_800069E4
/* 800069D0 000035B0  C0 5D 00 04 */	lfs f2, 4(r29)
/* 800069D4 000035B4  FC 03 10 40 */	fcmpo cr0, f3, f2
/* 800069D8 000035B8  40 80 00 0C */	bge lbl_800069E4
/* 800069DC 000035BC  38 60 00 00 */	li r3, 0
/* 800069E0 000035C0  48 00 04 3C */	b lbl_80006E1C
lbl_800069E4:
/* 800069E4 000035C4  C3 41 00 E8 */	lfs f26, 0xe8(r1)
/* 800069E8 000035C8  EF C1 D8 28 */	fsubs f30, f1, f27
/* 800069EC 000035CC  C0 7D 00 04 */	lfs f3, 4(r29)
/* 800069F0 000035D0  C1 21 00 F0 */	lfs f9, 0xf0(r1)
/* 800069F4 000035D4  ED 5B D0 28 */	fsubs f10, f27, f26
/* 800069F8 000035D8  EF 83 D0 28 */	fsubs f28, f3, f26
/* 800069FC 000035DC  C1 01 00 E4 */	lfs f8, 0xe4(r1)
/* 80006A00 000035E0  EF E0 48 28 */	fsubs f31, f0, f9
/* 80006A04 000035E4  C0 5D 00 00 */	lfs f2, 0(r29)
/* 80006A08 000035E8  EC BE 07 32 */	fmuls f5, f30, f28
/* 80006A0C 000035EC  EF A2 40 28 */	fsubs f29, f2, f8
/* 80006A10 000035F0  C0 82 80 10 */	lfs f4, lbl_804D79F0(r2)
/* 80006A14 000035F4  EC DC 07 32 */	fmuls f6, f28, f28
/* 80006A18 000035F8  EC FE 07 B2 */	fmuls f7, f30, f30
/* 80006A1C 000035FC  ED BF 2F 7A */	fmadds f13, f31, f29, f5
/* 80006A20 00003600  ED 9D 37 7A */	fmadds f12, f29, f29, f6
/* 80006A24 00003604  ED 7F 3F FA */	fmadds f11, f31, f31, f7
/* 80006A28 00003608  EC AD 03 72 */	fmuls f5, f13, f13
/* 80006A2C 0000360C  ED 09 40 28 */	fsubs f8, f9, f8
/* 80006A30 00003610  EC FC 02 B2 */	fmuls f7, f28, f10
/* 80006A34 00003614  EC DE 02 B2 */	fmuls f6, f30, f10
/* 80006A38 00003618  FC 0C 20 40 */	fcmpo cr0, f12, f4
/* 80006A3C 0000361C  EC FD 3A 3A */	fmadds f7, f29, f8, f7
/* 80006A40 00003620  EC DF 32 3A */	fmadds f6, f31, f8, f6
/* 80006A44 00003624  EC AB 2B 38 */	fmsubs f5, f11, f12, f5
/* 80006A48 00003628  40 80 00 18 */	bge lbl_80006A60
/* 80006A4C 0000362C  C0 82 80 14 */	lfs f4, lbl_804D79F4(r2)
/* 80006A50 00003630  FC 0C 20 40 */	fcmpo cr0, f12, f4
/* 80006A54 00003634  40 81 00 0C */	ble lbl_80006A60
/* 80006A58 00003638  38 00 00 01 */	li r0, 1
/* 80006A5C 0000363C  48 00 00 08 */	b lbl_80006A64
lbl_80006A60:
/* 80006A60 00003640  38 00 00 00 */	li r0, 0
lbl_80006A64:
/* 80006A64 00003644  2C 00 00 00 */	cmpwi r0, 0
/* 80006A68 00003648  41 82 00 74 */	beq lbl_80006ADC
/* 80006A6C 0000364C  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80006A70 00003650  FC 0B 00 40 */	fcmpo cr0, f11, f0
/* 80006A74 00003654  40 80 00 18 */	bge lbl_80006A8C
/* 80006A78 00003658  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 80006A7C 0000365C  FC 0B 00 40 */	fcmpo cr0, f11, f0
/* 80006A80 00003660  40 81 00 0C */	ble lbl_80006A8C
/* 80006A84 00003664  38 00 00 01 */	li r0, 1
/* 80006A88 00003668  48 00 00 08 */	b lbl_80006A90
lbl_80006A8C:
/* 80006A8C 0000366C  38 00 00 00 */	li r0, 0
lbl_80006A90:
/* 80006A90 00003670  2C 00 00 00 */	cmpwi r0, 0
/* 80006A94 00003674  41 82 00 10 */	beq lbl_80006AA4
/* 80006A98 00003678  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80006A9C 0000367C  FF 00 00 90 */	fmr f24, f0
/* 80006AA0 00003680  48 00 03 10 */	b lbl_80006DB0
lbl_80006AA4:
/* 80006AA4 00003684  FC 20 30 50 */	fneg f1, f6
/* 80006AA8 00003688  C8 02 80 20 */	lfd f0, lbl_804D7A00(r2)
/* 80006AAC 0000368C  C3 02 80 18 */	lfs f24, lbl_804D79F8(r2)
/* 80006AB0 00003690  EC 21 58 24 */	fdivs f1, f1, f11
/* 80006AB4 00003694  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80006AB8 00003698  FC 00 08 90 */	fmr f0, f1
/* 80006ABC 0000369C  40 81 00 0C */	ble lbl_80006AC8
/* 80006AC0 000036A0  C0 02 80 28 */	lfs f0, lbl_804D7A08(r2)
/* 80006AC4 000036A4  48 00 02 EC */	b lbl_80006DB0
lbl_80006AC8:
/* 80006AC8 000036A8  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006ACC 000036AC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80006AD0 000036B0  40 80 02 E0 */	bge lbl_80006DB0
/* 80006AD4 000036B4  FC 00 C0 90 */	fmr f0, f24
/* 80006AD8 000036B8  48 00 02 D8 */	b lbl_80006DB0
lbl_80006ADC:
/* 80006ADC 000036BC  C0 82 80 10 */	lfs f4, lbl_804D79F0(r2)
/* 80006AE0 000036C0  FC 05 20 40 */	fcmpo cr0, f5, f4
/* 80006AE4 000036C4  40 80 00 18 */	bge lbl_80006AFC
/* 80006AE8 000036C8  C0 82 80 14 */	lfs f4, lbl_804D79F4(r2)
/* 80006AEC 000036CC  FC 05 20 40 */	fcmpo cr0, f5, f4
/* 80006AF0 000036D0  40 81 00 0C */	ble lbl_80006AFC
/* 80006AF4 000036D4  38 00 00 01 */	li r0, 1
/* 80006AF8 000036D8  48 00 00 08 */	b lbl_80006B00
lbl_80006AFC:
/* 80006AFC 000036DC  38 00 00 00 */	li r0, 0
lbl_80006B00:
/* 80006B00 000036E0  2C 00 00 00 */	cmpwi r0, 0
/* 80006B04 000036E4  41 82 01 C8 */	beq lbl_80006CCC
/* 80006B08 000036E8  C8 C2 80 38 */	lfd f6, lbl_804D7A18(r2)
/* 80006B0C 000036EC  C0 A1 00 E4 */	lfs f5, 0xe4(r1)
/* 80006B10 000036F0  FC E6 D7 3A */	fmadd f7, f6, f28, f26
/* 80006B14 000036F4  C0 81 00 F0 */	lfs f4, 0xf0(r1)
/* 80006B18 000036F8  FC A6 2F 7A */	fmadd f5, f6, f29, f5
/* 80006B1C 000036FC  FC E0 38 18 */	frsp f7, f7
/* 80006B20 00003700  FC A0 28 18 */	frsp f5, f5
/* 80006B24 00003704  EC DB 38 28 */	fsubs f6, f27, f7
/* 80006B28 00003708  EC E1 38 28 */	fsubs f7, f1, f7
/* 80006B2C 0000370C  EC 84 28 28 */	fsubs f4, f4, f5
/* 80006B30 00003710  EC 26 01 B2 */	fmuls f1, f6, f6
/* 80006B34 00003714  EC A0 28 28 */	fsubs f5, f0, f5
/* 80006B38 00003718  EC 07 01 F2 */	fmuls f0, f7, f7
/* 80006B3C 0000371C  EC 24 09 3A */	fmadds f1, f4, f4, f1
/* 80006B40 00003720  EC 05 01 7A */	fmadds f0, f5, f5, f0
/* 80006B44 00003724  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80006B48 00003728  40 80 00 C4 */	bge lbl_80006C0C
/* 80006B4C 0000372C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80006B50 00003730  80 61 00 38 */	lwz r3, 0x38(r1)
/* 80006B54 00003734  90 01 00 70 */	stw r0, 0x70(r1)
/* 80006B58 00003738  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80006B5C 0000373C  90 61 00 74 */	stw r3, 0x74(r1)
/* 80006B60 00003740  80 81 00 28 */	lwz r4, 0x28(r1)
/* 80006B64 00003744  90 01 00 78 */	stw r0, 0x78(r1)
/* 80006B68 00003748  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80006B6C 0000374C  C0 3C 00 00 */	lfs f1, 0(r28)
/* 80006B70 00003750  C0 1C 00 04 */	lfs f0, 4(r28)
/* 80006B74 00003754  EC E2 08 28 */	fsubs f7, f2, f1
/* 80006B78 00003758  C0 9D 00 08 */	lfs f4, 8(r29)
/* 80006B7C 0000375C  C0 3C 00 08 */	lfs f1, 8(r28)
/* 80006B80 00003760  ED 03 00 28 */	fsubs f8, f3, f0
/* 80006B84 00003764  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80006B88 00003768  90 81 00 88 */	stw r4, 0x88(r1)
/* 80006B8C 0000376C  EC 08 02 32 */	fmuls f0, f8, f8
/* 80006B90 00003770  ED 24 08 28 */	fsubs f9, f4, f1
/* 80006B94 00003774  C0 61 00 74 */	lfs f3, 0x74(r1)
/* 80006B98 00003778  90 61 00 8C */	stw r3, 0x8c(r1)
/* 80006B9C 0000377C  EC 07 01 FA */	fmadds f0, f7, f7, f0
/* 80006BA0 00003780  90 01 00 90 */	stw r0, 0x90(r1)
/* 80006BA4 00003784  C0 A1 00 70 */	lfs f5, 0x70(r1)
/* 80006BA8 00003788  C0 21 00 8C */	lfs f1, 0x8c(r1)
/* 80006BAC 0000378C  EC 49 02 7A */	fmadds f2, f9, f9, f0
/* 80006BB0 00003790  C0 81 00 88 */	lfs f4, 0x88(r1)
/* 80006BB4 00003794  EC 03 08 28 */	fsubs f0, f3, f1
/* 80006BB8 00003798  C0 C1 00 78 */	lfs f6, 0x78(r1)
/* 80006BBC 0000379C  EC 85 20 28 */	fsubs f4, f5, f4
/* 80006BC0 000037A0  C0 21 00 90 */	lfs f1, 0x90(r1)
/* 80006BC4 000037A4  EC 68 00 32 */	fmuls f3, f8, f0
/* 80006BC8 000037A8  EC A6 08 28 */	fsubs f5, f6, f1
/* 80006BCC 000037AC  C8 22 80 20 */	lfd f1, lbl_804D7A00(r2)
/* 80006BD0 000037B0  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80006BD4 000037B4  EC 67 19 3A */	fmadds f3, f7, f4, f3
/* 80006BD8 000037B8  EC 69 19 7A */	fmadds f3, f9, f5, f3
/* 80006BDC 000037BC  FC 60 18 50 */	fneg f3, f3
/* 80006BE0 000037C0  EC 43 10 24 */	fdivs f2, f3, f2
/* 80006BE4 000037C4  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006BE8 000037C8  40 81 00 0C */	ble lbl_80006BF4
/* 80006BEC 000037CC  C0 42 80 28 */	lfs f2, lbl_804D7A08(r2)
/* 80006BF0 000037D0  48 00 00 14 */	b lbl_80006C04
lbl_80006BF4:
/* 80006BF4 000037D4  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006BF8 000037D8  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006BFC 000037DC  40 80 00 08 */	bge lbl_80006C04
/* 80006C00 000037E0  FC 40 00 90 */	fmr f2, f0
lbl_80006C04:
/* 80006C04 000037E4  FF 00 10 90 */	fmr f24, f2
/* 80006C08 000037E8  48 00 01 A8 */	b lbl_80006DB0
lbl_80006C0C:
/* 80006C0C 000037EC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80006C10 000037F0  80 61 00 38 */	lwz r3, 0x38(r1)
/* 80006C14 000037F4  90 01 00 40 */	stw r0, 0x40(r1)
/* 80006C18 000037F8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80006C1C 000037FC  90 61 00 44 */	stw r3, 0x44(r1)
/* 80006C20 00003800  C8 22 80 20 */	lfd f1, lbl_804D7A00(r2)
/* 80006C24 00003804  90 01 00 48 */	stw r0, 0x48(r1)
/* 80006C28 00003808  C0 02 80 28 */	lfs f0, lbl_804D7A08(r2)
/* 80006C2C 0000380C  C0 BC 00 00 */	lfs f5, 0(r28)
/* 80006C30 00003810  C0 9C 00 04 */	lfs f4, 4(r28)
/* 80006C34 00003814  ED 22 28 28 */	fsubs f9, f2, f5
/* 80006C38 00003818  C0 DD 00 08 */	lfs f6, 8(r29)
/* 80006C3C 0000381C  C0 BC 00 08 */	lfs f5, 8(r28)
/* 80006C40 00003820  ED 43 20 28 */	fsubs f10, f3, f4
/* 80006C44 00003824  80 7B 00 00 */	lwz r3, 0(r27)
/* 80006C48 00003828  80 1B 00 04 */	lwz r0, 4(r27)
/* 80006C4C 0000382C  ED 66 28 28 */	fsubs f11, f6, f5
/* 80006C50 00003830  EC 4A 02 B2 */	fmuls f2, f10, f10
/* 80006C54 00003834  C0 81 00 44 */	lfs f4, 0x44(r1)
/* 80006C58 00003838  90 61 00 58 */	stw r3, 0x58(r1)
/* 80006C5C 0000383C  C0 C1 00 40 */	lfs f6, 0x40(r1)
/* 80006C60 00003840  90 01 00 5C */	stw r0, 0x5c(r1)
/* 80006C64 00003844  EC 49 12 7A */	fmadds f2, f9, f9, f2
/* 80006C68 00003848  C1 01 00 48 */	lfs f8, 0x48(r1)
/* 80006C6C 0000384C  80 1B 00 08 */	lwz r0, 8(r27)
/* 80006C70 00003850  90 01 00 60 */	stw r0, 0x60(r1)
/* 80006C74 00003854  EC 4B 12 FA */	fmadds f2, f11, f11, f2
/* 80006C78 00003858  C0 61 00 5C */	lfs f3, 0x5c(r1)
/* 80006C7C 0000385C  C0 A1 00 58 */	lfs f5, 0x58(r1)
/* 80006C80 00003860  EC 64 18 28 */	fsubs f3, f4, f3
/* 80006C84 00003864  C0 E1 00 60 */	lfs f7, 0x60(r1)
/* 80006C88 00003868  EC 86 28 28 */	fsubs f4, f6, f5
/* 80006C8C 0000386C  EC A8 38 28 */	fsubs f5, f8, f7
/* 80006C90 00003870  EC 6A 00 F2 */	fmuls f3, f10, f3
/* 80006C94 00003874  EC 69 19 3A */	fmadds f3, f9, f4, f3
/* 80006C98 00003878  EC 6B 19 7A */	fmadds f3, f11, f5, f3
/* 80006C9C 0000387C  FC 60 18 50 */	fneg f3, f3
/* 80006CA0 00003880  EC 43 10 24 */	fdivs f2, f3, f2
/* 80006CA4 00003884  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006CA8 00003888  40 81 00 0C */	ble lbl_80006CB4
/* 80006CAC 0000388C  FC 40 00 90 */	fmr f2, f0
/* 80006CB0 00003890  48 00 00 14 */	b lbl_80006CC4
lbl_80006CB4:
/* 80006CB4 00003894  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006CB8 00003898  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006CBC 0000389C  40 80 00 08 */	bge lbl_80006CC4
/* 80006CC0 000038A0  C0 42 80 18 */	lfs f2, lbl_804D79F8(r2)
lbl_80006CC4:
/* 80006CC4 000038A4  FF 00 10 90 */	fmr f24, f2
/* 80006CC8 000038A8  48 00 00 E8 */	b lbl_80006DB0
lbl_80006CCC:
/* 80006CCC 000038AC  EC 2C 01 B2 */	fmuls f1, f12, f6
/* 80006CD0 000038B0  C8 42 80 20 */	lfd f2, lbl_804D7A00(r2)
/* 80006CD4 000038B4  EC 0D 01 B2 */	fmuls f0, f13, f6
/* 80006CD8 000038B8  EC 2D 09 F8 */	fmsubs f1, f13, f7, f1
/* 80006CDC 000038BC  EC 0B 01 F8 */	fmsubs f0, f11, f7, f0
/* 80006CE0 000038C0  EC 21 28 24 */	fdivs f1, f1, f5
/* 80006CE4 000038C4  EF 00 28 24 */	fdivs f24, f0, f5
/* 80006CE8 000038C8  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 80006CEC 000038CC  FC 00 08 90 */	fmr f0, f1
/* 80006CF0 000038D0  41 81 00 20 */	bgt lbl_80006D10
/* 80006CF4 000038D4  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006CF8 000038D8  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80006CFC 000038DC  41 80 00 14 */	blt lbl_80006D10
/* 80006D00 000038E0  FC 18 10 40 */	fcmpo cr0, f24, f2
/* 80006D04 000038E4  41 81 00 0C */	bgt lbl_80006D10
/* 80006D08 000038E8  FC 18 08 40 */	fcmpo cr0, f24, f1
/* 80006D0C 000038EC  40 80 00 A4 */	bge lbl_80006DB0
lbl_80006D10:
/* 80006D10 000038F0  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80006D14 000038F4  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80006D18 000038F8  40 80 00 24 */	bge lbl_80006D3C
/* 80006D1C 000038FC  C2 C2 80 18 */	lfs f22, lbl_804D79F8(r2)
/* 80006D20 00003900  38 7C 00 00 */	addi r3, r28, 0
/* 80006D24 00003904  38 9D 00 00 */	addi r4, r29, 0
/* 80006D28 00003908  38 BA 00 00 */	addi r5, r26, 0
/* 80006D2C 0000390C  38 C1 00 A4 */	addi r6, r1, 0xa4
/* 80006D30 00003910  4B FF F2 91 */	bl lbColl_80005FC0
/* 80006D34 00003914  FE E0 08 90 */	fmr f23, f1
/* 80006D38 00003918  48 00 00 20 */	b lbl_80006D58
lbl_80006D3C:
/* 80006D3C 0000391C  C2 C2 80 28 */	lfs f22, lbl_804D7A08(r2)
/* 80006D40 00003920  38 7C 00 00 */	addi r3, r28, 0
/* 80006D44 00003924  38 9D 00 00 */	addi r4, r29, 0
/* 80006D48 00003928  38 BB 00 00 */	addi r5, r27, 0
/* 80006D4C 0000392C  38 C1 00 A4 */	addi r6, r1, 0xa4
/* 80006D50 00003930  4B FF F2 71 */	bl lbColl_80005FC0
/* 80006D54 00003934  FE E0 08 90 */	fmr f23, f1
lbl_80006D58:
/* 80006D58 00003938  C8 02 80 30 */	lfd f0, lbl_804D7A10(r2)
/* 80006D5C 0000393C  FC 18 00 40 */	fcmpo cr0, f24, f0
/* 80006D60 00003940  40 80 00 20 */	bge lbl_80006D80
/* 80006D64 00003944  C3 02 80 18 */	lfs f24, lbl_804D79F8(r2)
/* 80006D68 00003948  38 7A 00 00 */	addi r3, r26, 0
/* 80006D6C 0000394C  38 9B 00 00 */	addi r4, r27, 0
/* 80006D70 00003950  38 BC 00 00 */	addi r5, r28, 0
/* 80006D74 00003954  38 C1 00 A0 */	addi r6, r1, 0xa0
/* 80006D78 00003958  4B FF F2 49 */	bl lbColl_80005FC0
/* 80006D7C 0000395C  48 00 00 1C */	b lbl_80006D98
lbl_80006D80:
/* 80006D80 00003960  C3 02 80 28 */	lfs f24, lbl_804D7A08(r2)
/* 80006D84 00003964  38 7A 00 00 */	addi r3, r26, 0
/* 80006D88 00003968  38 9B 00 00 */	addi r4, r27, 0
/* 80006D8C 0000396C  38 BD 00 00 */	addi r5, r29, 0
/* 80006D90 00003970  38 C1 00 A0 */	addi r6, r1, 0xa0
/* 80006D94 00003974  4B FF F2 2D */	bl lbColl_80005FC0
lbl_80006D98:
/* 80006D98 00003978  FC 17 08 40 */	fcmpo cr0, f23, f1
/* 80006D9C 0000397C  40 80 00 10 */	bge lbl_80006DAC
/* 80006DA0 00003980  FC 00 B0 90 */	fmr f0, f22
/* 80006DA4 00003984  C3 01 00 A4 */	lfs f24, 0xa4(r1)
/* 80006DA8 00003988  48 00 00 08 */	b lbl_80006DB0
lbl_80006DAC:
/* 80006DAC 0000398C  C0 01 00 A0 */	lfs f0, 0xa0(r1)
lbl_80006DB0:
/* 80006DB0 00003990  C0 21 00 F0 */	lfs f1, 0xf0(r1)
/* 80006DB4 00003994  EC 7E D8 3A */	fmadds f3, f30, f0, f27
/* 80006DB8 00003998  EC 5C D6 3A */	fmadds f2, f28, f24, f26
/* 80006DBC 0000399C  EC 1F 08 3A */	fmadds f0, f31, f0, f1
/* 80006DC0 000039A0  EC 39 06 72 */	fmuls f1, f25, f25
/* 80006DC4 000039A4  D0 1E 00 00 */	stfs f0, 0(r30)
/* 80006DC8 000039A8  D0 7E 00 04 */	stfs f3, 4(r30)
/* 80006DCC 000039AC  C0 62 80 18 */	lfs f3, lbl_804D79F8(r2)
/* 80006DD0 000039B0  D0 7E 00 08 */	stfs f3, 8(r30)
/* 80006DD4 000039B4  C0 01 00 E4 */	lfs f0, 0xe4(r1)
/* 80006DD8 000039B8  EC 1D 06 3A */	fmadds f0, f29, f24, f0
/* 80006DDC 000039BC  D0 1F 00 00 */	stfs f0, 0(r31)
/* 80006DE0 000039C0  D0 5F 00 04 */	stfs f2, 4(r31)
/* 80006DE4 000039C4  D0 7F 00 08 */	stfs f3, 8(r31)
/* 80006DE8 000039C8  C0 5E 00 04 */	lfs f2, 4(r30)
/* 80006DEC 000039CC  C0 1F 00 04 */	lfs f0, 4(r31)
/* 80006DF0 000039D0  C0 7E 00 00 */	lfs f3, 0(r30)
/* 80006DF4 000039D4  EC 82 00 28 */	fsubs f4, f2, f0
/* 80006DF8 000039D8  C0 1F 00 00 */	lfs f0, 0(r31)
/* 80006DFC 000039DC  EC 43 00 28 */	fsubs f2, f3, f0
/* 80006E00 000039E0  EC 04 01 32 */	fmuls f0, f4, f4
/* 80006E04 000039E4  EC 02 00 BA */	fmadds f0, f2, f2, f0
/* 80006E08 000039E8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80006E0C 000039EC  40 80 00 0C */	bge lbl_80006E18
/* 80006E10 000039F0  38 60 00 00 */	li r3, 0
/* 80006E14 000039F4  48 00 00 08 */	b lbl_80006E1C
lbl_80006E18:
/* 80006E18 000039F8  38 60 00 01 */	li r3, 1
lbl_80006E1C:
/* 80006E1C 000039FC  BB 41 01 00 */	lmw r26, 0x100(r1)
/* 80006E20 00003A00  80 01 01 6C */	lwz r0, 0x16c(r1)
/* 80006E24 00003A04  CB E1 01 60 */	lfd f31, 0x160(r1)
/* 80006E28 00003A08  CB C1 01 58 */	lfd f30, 0x158(r1)
/* 80006E2C 00003A0C  CB A1 01 50 */	lfd f29, 0x150(r1)
/* 80006E30 00003A10  CB 81 01 48 */	lfd f28, 0x148(r1)
/* 80006E34 00003A14  CB 61 01 40 */	lfd f27, 0x140(r1)
/* 80006E38 00003A18  CB 41 01 38 */	lfd f26, 0x138(r1)
/* 80006E3C 00003A1C  CB 21 01 30 */	lfd f25, 0x130(r1)
/* 80006E40 00003A20  CB 01 01 28 */	lfd f24, 0x128(r1)
/* 80006E44 00003A24  CA E1 01 20 */	lfd f23, 0x120(r1)
/* 80006E48 00003A28  CA C1 01 18 */	lfd f22, 0x118(r1)
/* 80006E4C 00003A2C  38 21 01 68 */	addi r1, r1, 0x168
/* 80006E50 00003A30  7C 08 03 A6 */	mtlr r0
/* 80006E54 00003A34  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool lbColl_800067F8(Vec3* a, Vec3* b, Vec3* c, Vec3* d, Vec3* e, Vec3* f,
                     f32 p, f32 q, f32 r)
{
    f32 sum_pq = p + q;

    f32 a_z;
    Vec3 a0;
    Vec3 a1;

    a0.x = a->x;
    a0.y = a->y;
    a0.z = a_z = a->z;
    a1.x = a0.x;
    a1.y = a0.y;
    a1.z = a_z;
    {
        Vec3 c0;
        f32 temp_r0_2;

        c0.x = c->x;
        c0.y = c->y;
        c0.z = temp_r0_2 = c->z;

        {
            Vec3 c1;

            c1.x = c0.x;
            c1.y = c0.y;
            c1.z = temp_r0_2;
            {
                f32 b_x = b->x;
                if (a1.x > b_x) {
                    {
                        f32 x = a1.x + sum_pq;
                        if (x < c1.x && x < d->x)
                            return false;
                    }

                    {
                        f32 x = b_x - sum_pq;
                        if ((x > c1.x) && (x > d->x))
                            return false;
                    }

                } else {
                    {
                        f32 x = a1.x - sum_pq;
                        if (x > c1.x && x > d->x)
                            return false;
                    }

                    {
                        f32 temp_f2_4 = b_x + sum_pq;
                        if (temp_f2_4 < c1.x && temp_f2_4 < d->x)
                            return false;
                    }
                }

                {
                    f32 b_y = b->y;
                    if (a1.y > b_y) {
                        {
                            f32 y;
                            y = a1.y + sum_pq;
                            if (y < c1.y && y < d->y)
                                return false;
                        }
                        {
                            f32 y = b_y - sum_pq;
                            if (y > c1.y && y > d->y)
                                return false;
                        }

                    } else {
                        {
                            f32 y = a1.y - sum_pq;
                            if (y > c1.y && y > d->y)
                                return false;
                        }
                        {
                            f32 y = b_y + sum_pq;
                            if (y < c1.y && y < d->y)
                                return false;
                        }
                    }

                    {
                        f32 diff_ba_y = b_y - a1.y;
                        f32 d_y = d->y;
                        f32 diff_ac_y = a1.y - c1.y;
                        f32 diff_dc_y = d_y - c1.y;
                        f32 diff_ba_x = b_x - a1.x;
                        f32 d_x = d->x;
                        f32 diff_dc_x = d_x - c1.x;

                        f32 dot2_diff_ba_dc =
                            diff_ba_x * diff_dc_x + diff_ba_y * diff_dc_y;

                        f32 sqdist2_dc =
                            diff_dc_x * diff_dc_x + diff_dc_y * diff_dc_y;
                        f32 sqdist2_ba =
                            diff_ba_x * diff_ba_x + diff_ba_y * diff_ba_y;
                        f32 diff_ac_x = a1.x - c1.x;

                        f32 dot2_diff_dc_ac =
                            diff_dc_x * diff_ac_x + diff_dc_y * diff_ac_y;

                        f32 dot2_diff_ba_ac =
                            diff_ba_x * diff_ac_x + diff_ba_y * diff_ac_y;

                        f32 determinant = sqdist2_ba * sqdist2_dc -
                                          dot2_diff_ba_dc * dot2_diff_ba_dc;

                        {
                            f32 scl_e;
                            f32 scl_f;
                            if (approximatelyZero(sqdist2_dc)) {
                                if (approximatelyZero(sqdist2_ba)) {
                                    scl_e = 0.0f;
                                    scl_f = 0.0f;
                                } else {
                                    f32 temp_f1_2;
                                    scl_f = 0.0f;
                                    temp_f1_2 = -dot2_diff_ba_ac / sqdist2_ba;
                                    scl_e = temp_f1_2;
                                    if (temp_f1_2 > (f32) 1.0) {
                                        scl_e = 1.0f;
                                    } else if (scl_e < (f32) 0.0) {
                                        scl_e = 0.0f;
                                    }
                                }
                            } else if (approximatelyZero(determinant)) {
                                f32 temp_f7_2 = 0.5 * diff_dc_y + c1.y;
                                f32 temp_f5_2 = 0.5 * diff_dc_x + c1.x;
                                f32 temp_f6_2 = a1.y - temp_f7_2;
                                f32 temp_f7_3 = b_y - temp_f7_2;
                                {
                                    f32 temp_scl_f;
                                    f32 f4 = a1.x - temp_f5_2;
                                    f32 temp_f5_3 = b_x - temp_f5_2;
                                    if ((f4 * f4 + temp_f6_2 * temp_f6_2) <
                                        (temp_f5_3 * temp_f5_3 +
                                         temp_f7_3 * temp_f7_3))
                                    {
                                        f32 diff_dc_x;
                                        f32 temp_f8_2;
                                        Vec3 c3;
                                        c3.x = c0.x;
                                        c3.y = c0.y;
                                        c3.z = c0.z;
                                        diff_dc_x = d_x - c->x;
                                        temp_f8_2 = d_y - c->y;
                                        {
                                            {
                                                Vec3 a2;
                                                f32 diff_dc_z;
                                                a2.x = a0.x;
                                                diff_dc_z = d->z - c->z;
                                                a2.y = a0.y;
                                                a2.z = a0.z;
                                                scl_e = 0.0f;
                                                temp_scl_f =
                                                    -(diff_dc_z *
                                                      (c3.z - a2.z)) +
                                                    ((diff_dc_x *
                                                      (c3.x - a2.x)) +
                                                     (temp_f8_2 *
                                                      (c3.y - a2.y))) /
                                                        ((diff_dc_z *
                                                          diff_dc_z) +
                                                         ((diff_dc_x *
                                                           diff_dc_x) +
                                                          (temp_f8_2 *
                                                           temp_f8_2)));
                                            }
                                        }
                                        if (temp_scl_f > (f32) 1.0) {
                                            temp_scl_f = 1.0f;
                                        } else if (temp_scl_f < (f32) 0.0) {
                                            temp_scl_f = 0.0f;
                                        }
                                        scl_f = temp_scl_f;
                                    } else {
                                        Vec3 c2;

                                        c2.x = c0.x;
                                        c2.y = c0.y;
                                        c2.z = c0.z;
                                        {
                                            f32 diff_dc_x1;
                                            scl_e = 1.0f;
                                            diff_dc_x1 = d_x - c->x;
                                            {
                                                f32 diff_dc_y1;
                                                f32 diff_dc_z1;
                                                diff_dc_y1 = d_y - c->y;
                                                diff_dc_z1 = d->z - c->z;
                                                {
                                                    Vec3 b0;

                                                    b0.x = b->x;
                                                    b0.y = b->y;
                                                    b0.z = b->z;
                                                    {
                                                        f32 var_f2_2 =
                                                            -(diff_dc_z1 *
                                                                  (c2.z -
                                                                   b0.z) +
                                                              ((diff_dc_x1 *
                                                                (c2.x -
                                                                 b0.x)) +
                                                               (diff_dc_y1 *
                                                                (c2.y -
                                                                 b0.y)))) /
                                                            ((diff_dc_z1 *
                                                              diff_dc_z1) +
                                                             ((diff_dc_x1 *
                                                               diff_dc_x1) +
                                                              (diff_dc_y1 *
                                                               diff_dc_y1)));
                                                        if (var_f2_2 >
                                                            (f32) 1.0)
                                                        {
                                                            var_f2_2 = 1.0f;
                                                        } else if (var_f2_2 <
                                                                   (f32) 0.0)
                                                        {
                                                            var_f2_2 = 0.0f;
                                                        }
                                                        scl_f = var_f2_2;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                f32 temp_f1_3 =
                                    ((dot2_diff_ba_dc * dot2_diff_dc_ac) -
                                     (sqdist2_dc * dot2_diff_ba_ac)) /
                                    determinant;
                                scl_f = ((sqdist2_ba * dot2_diff_dc_ac) -
                                         (dot2_diff_ba_dc * dot2_diff_ba_ac)) /
                                        determinant;
                                scl_e = temp_f1_3;
                                if ((temp_f1_3 > (f32) 1.0) ||
                                    (scl_e < (f32) 0.0) ||
                                    (scl_f > (f32) 1.0) || (scl_f < (f32) 0.0))
                                {
                                    f32 out0;
                                    f32 temp_scl_e;
                                    f32 result0;
                                    {
                                        if (scl_e < (f32) 0.0) {
                                            temp_scl_e = 0.0f;
                                            result0 = lbColl_80005FC0(c, d, a,
                                                                      &out0);
                                        } else {
                                            temp_scl_e = 1.0f;
                                            result0 = lbColl_80005FC0(c, d, b,
                                                                      &out0);
                                        }
                                    }
                                    {
                                        f32 result1;
                                        f32 out1;
                                        if (scl_f < (f32) 0.0) {
                                            scl_f = 0.0f;
                                            result1 = lbColl_80005FC0(a, b, c,
                                                                      &out1);
                                        } else {
                                            scl_f = 1.0f;
                                            result1 = lbColl_80005FC0(a, b, d,
                                                                      &out1);
                                        }

                                        if (result0 < result1) {
                                            scl_e = temp_scl_e;
                                            scl_f = out0;
                                        } else {
                                            scl_e = out1;
                                        }
                                    }
                                }
                            }

                            e->x = diff_ba_x * scl_e + a1.x;
                            e->y = diff_ba_y * scl_e + a1.y;
                            e->z = 0.0f;

                            f->x = diff_dc_x * scl_f + c1.x;
                            f->y = diff_dc_y * scl_f + c1.y;
                            f->z = 0.0f;
                        }
                    }
                }
            }
        }
    }
    {
        f32 diff_ef_y;
        f32 diff_ef_x;
        diff_ef_y = e->y - f->y;
        diff_ef_x = e->x - f->x;
        if (sum_pq * sum_pq < diff_ef_x * diff_ef_x + (diff_ef_y * diff_ef_y))
        {
            return false;
        }
        return true;
    }
}
#endif

f64 const lbl_804D7A20 = 3.0;

#ifdef MUST_MATCH
#pragma push
// clang-format off
asm bool lbColl_80006E58(Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Vec3*, Mtx, Vec3*,
                       f32, f32, f32)
{
    nofralloc
/* 80006E58 00003A38  7C 08 02 A6 */	mflr r0
/* 80006E5C 00003A3C  90 01 00 04 */	stw r0, 4(r1)
/* 80006E60 00003A40  94 21 FE 50 */	stwu r1, -0x1b0(r1)
/* 80006E64 00003A44  DB E1 01 A8 */	stfd f31, 0x1a8(r1)
/* 80006E68 00003A48  DB C1 01 A0 */	stfd f30, 0x1a0(r1)
/* 80006E6C 00003A4C  DB A1 01 98 */	stfd f29, 0x198(r1)
/* 80006E70 00003A50  FF A0 10 90 */	fmr f29, f2
/* 80006E74 00003A54  DB 81 01 90 */	stfd f28, 0x190(r1)
/* 80006E78 00003A58  FF 80 08 90 */	fmr f28, f1
/* 80006E7C 00003A5C  DB 61 01 88 */	stfd f27, 0x188(r1)
/* 80006E80 00003A60  EC 7D E0 FA */	fmadds f3, f29, f3, f28
/* 80006E84 00003A64  DB 41 01 80 */	stfd f26, 0x180(r1)
/* 80006E88 00003A68  DB 21 01 78 */	stfd f25, 0x178(r1)
/* 80006E8C 00003A6C  DB 01 01 70 */	stfd f24, 0x170(r1)
/* 80006E90 00003A70  DA E1 01 68 */	stfd f23, 0x168(r1)
/* 80006E94 00003A74  DA C1 01 60 */	stfd f22, 0x160(r1)
/* 80006E98 00003A78  DA A1 01 58 */	stfd f21, 0x158(r1)
/* 80006E9C 00003A7C  DA 81 01 50 */	stfd f20, 0x150(r1)
/* 80006EA0 00003A80  BE E1 01 2C */	stmw r23, 0x12c(r1)
/* 80006EA4 00003A84  7C 78 1B 78 */	mr r24, r3
/* 80006EA8 00003A88  83 E1 01 B8 */	lwz r31, 0x1b8(r1)
/* 80006EAC 00003A8C  7C BA 2B 78 */	mr r26, r5
/* 80006EB0 00003A90  7C 99 23 78 */	mr r25, r4
/* 80006EB4 00003A94  7C D7 33 78 */	mr r23, r6
/* 80006EB8 00003A98  7C FB 3B 78 */	mr r27, r7
/* 80006EBC 00003A9C  3B 88 00 00 */	addi r28, r8, 0
/* 80006EC0 00003AA0  3B A9 00 00 */	addi r29, r9, 0
/* 80006EC4 00003AA4  7D 5E 53 78 */	mr r30, r10
/* 80006EC8 00003AA8  80 63 00 00 */	lwz r3, 0(r3)
/* 80006ECC 00003AAC  80 18 00 04 */	lwz r0, 4(r24)
/* 80006ED0 00003AB0  90 61 01 1C */	stw r3, 0x11c(r1)
/* 80006ED4 00003AB4  90 01 01 20 */	stw r0, 0x120(r1)
/* 80006ED8 00003AB8  80 18 00 08 */	lwz r0, 8(r24)
/* 80006EDC 00003ABC  90 01 01 24 */	stw r0, 0x124(r1)
/* 80006EE0 00003AC0  80 65 00 00 */	lwz r3, 0(r5)
/* 80006EE4 00003AC4  80 05 00 04 */	lwz r0, 4(r5)
/* 80006EE8 00003AC8  C0 01 01 1C */	lfs f0, 0x11c(r1)
/* 80006EEC 00003ACC  90 61 01 10 */	stw r3, 0x110(r1)
/* 80006EF0 00003AD0  90 01 01 14 */	stw r0, 0x114(r1)
/* 80006EF4 00003AD4  80 05 00 08 */	lwz r0, 8(r5)
/* 80006EF8 00003AD8  90 01 01 18 */	stw r0, 0x118(r1)
/* 80006EFC 00003ADC  C0 A4 00 00 */	lfs f5, 0(r4)
/* 80006F00 00003AE0  FC 00 28 40 */	fcmpo cr0, f0, f5
/* 80006F04 00003AE4  40 81 00 4C */	ble lbl_80006F50
/* 80006F08 00003AE8  EC 40 18 2A */	fadds f2, f0, f3
/* 80006F0C 00003AEC  C0 21 01 10 */	lfs f1, 0x110(r1)
/* 80006F10 00003AF0  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006F14 00003AF4  40 80 00 18 */	bge lbl_80006F2C
/* 80006F18 00003AF8  C0 37 00 00 */	lfs f1, 0(r23)
/* 80006F1C 00003AFC  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006F20 00003B00  40 80 00 0C */	bge lbl_80006F2C
/* 80006F24 00003B04  38 60 00 00 */	li r3, 0
/* 80006F28 00003B08  48 00 08 34 */	b lbl_8000775C
lbl_80006F2C:
/* 80006F2C 00003B0C  EC 45 18 28 */	fsubs f2, f5, f3
/* 80006F30 00003B10  C0 21 01 10 */	lfs f1, 0x110(r1)
/* 80006F34 00003B14  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006F38 00003B18  40 81 00 60 */	ble lbl_80006F98
/* 80006F3C 00003B1C  C0 37 00 00 */	lfs f1, 0(r23)
/* 80006F40 00003B20  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006F44 00003B24  40 81 00 54 */	ble lbl_80006F98
/* 80006F48 00003B28  38 60 00 00 */	li r3, 0
/* 80006F4C 00003B2C  48 00 08 10 */	b lbl_8000775C
lbl_80006F50:
/* 80006F50 00003B30  EC 40 18 28 */	fsubs f2, f0, f3
/* 80006F54 00003B34  C0 21 01 10 */	lfs f1, 0x110(r1)
/* 80006F58 00003B38  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006F5C 00003B3C  40 81 00 18 */	ble lbl_80006F74
/* 80006F60 00003B40  C0 37 00 00 */	lfs f1, 0(r23)
/* 80006F64 00003B44  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006F68 00003B48  40 81 00 0C */	ble lbl_80006F74
/* 80006F6C 00003B4C  38 60 00 00 */	li r3, 0
/* 80006F70 00003B50  48 00 07 EC */	b lbl_8000775C
lbl_80006F74:
/* 80006F74 00003B54  EC 45 18 2A */	fadds f2, f5, f3
/* 80006F78 00003B58  C0 21 01 10 */	lfs f1, 0x110(r1)
/* 80006F7C 00003B5C  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006F80 00003B60  40 80 00 18 */	bge lbl_80006F98
/* 80006F84 00003B64  C0 37 00 00 */	lfs f1, 0(r23)
/* 80006F88 00003B68  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80006F8C 00003B6C  40 80 00 0C */	bge lbl_80006F98
/* 80006F90 00003B70  38 60 00 00 */	li r3, 0
/* 80006F94 00003B74  48 00 07 C8 */	b lbl_8000775C
lbl_80006F98:
/* 80006F98 00003B78  C0 21 01 20 */	lfs f1, 0x120(r1)
/* 80006F9C 00003B7C  C0 D9 00 04 */	lfs f6, 4(r25)
/* 80006FA0 00003B80  FC 01 30 40 */	fcmpo cr0, f1, f6
/* 80006FA4 00003B84  40 81 00 48 */	ble lbl_80006FEC
/* 80006FA8 00003B88  EC 81 18 2A */	fadds f4, f1, f3
/* 80006FAC 00003B8C  C0 E1 01 14 */	lfs f7, 0x114(r1)
/* 80006FB0 00003B90  FC 04 38 40 */	fcmpo cr0, f4, f7
/* 80006FB4 00003B94  40 80 00 18 */	bge lbl_80006FCC
/* 80006FB8 00003B98  C0 57 00 04 */	lfs f2, 4(r23)
/* 80006FBC 00003B9C  FC 04 10 40 */	fcmpo cr0, f4, f2
/* 80006FC0 00003BA0  40 80 00 0C */	bge lbl_80006FCC
/* 80006FC4 00003BA4  38 60 00 00 */	li r3, 0
/* 80006FC8 00003BA8  48 00 07 94 */	b lbl_8000775C
lbl_80006FCC:
/* 80006FCC 00003BAC  EC 86 18 28 */	fsubs f4, f6, f3
/* 80006FD0 00003BB0  FC 04 38 40 */	fcmpo cr0, f4, f7
/* 80006FD4 00003BB4  40 81 00 5C */	ble lbl_80007030
/* 80006FD8 00003BB8  C0 57 00 04 */	lfs f2, 4(r23)
/* 80006FDC 00003BBC  FC 04 10 40 */	fcmpo cr0, f4, f2
/* 80006FE0 00003BC0  40 81 00 50 */	ble lbl_80007030
/* 80006FE4 00003BC4  38 60 00 00 */	li r3, 0
/* 80006FE8 00003BC8  48 00 07 74 */	b lbl_8000775C
lbl_80006FEC:
/* 80006FEC 00003BCC  EC 81 18 28 */	fsubs f4, f1, f3
/* 80006FF0 00003BD0  C0 E1 01 14 */	lfs f7, 0x114(r1)
/* 80006FF4 00003BD4  FC 04 38 40 */	fcmpo cr0, f4, f7
/* 80006FF8 00003BD8  40 81 00 18 */	ble lbl_80007010
/* 80006FFC 00003BDC  C0 57 00 04 */	lfs f2, 4(r23)
/* 80007000 00003BE0  FC 04 10 40 */	fcmpo cr0, f4, f2
/* 80007004 00003BE4  40 81 00 0C */	ble lbl_80007010
/* 80007008 00003BE8  38 60 00 00 */	li r3, 0
/* 8000700C 00003BEC  48 00 07 50 */	b lbl_8000775C
lbl_80007010:
/* 80007010 00003BF0  EC 86 18 2A */	fadds f4, f6, f3
/* 80007014 00003BF4  FC 04 38 40 */	fcmpo cr0, f4, f7
/* 80007018 00003BF8  40 80 00 18 */	bge lbl_80007030
/* 8000701C 00003BFC  C0 57 00 04 */	lfs f2, 4(r23)
/* 80007020 00003C00  FC 04 10 40 */	fcmpo cr0, f4, f2
/* 80007024 00003C04  40 80 00 0C */	bge lbl_80007030
/* 80007028 00003C08  38 60 00 00 */	li r3, 0
/* 8000702C 00003C0C  48 00 07 30 */	b lbl_8000775C
lbl_80007030:
/* 80007030 00003C10  C0 41 01 24 */	lfs f2, 0x124(r1)
/* 80007034 00003C14  C0 F9 00 08 */	lfs f7, 8(r25)
/* 80007038 00003C18  FC 02 38 40 */	fcmpo cr0, f2, f7
/* 8000703C 00003C1C  40 81 00 48 */	ble lbl_80007084
/* 80007040 00003C20  EC C2 18 2A */	fadds f6, f2, f3
/* 80007044 00003C24  C1 01 01 18 */	lfs f8, 0x118(r1)
/* 80007048 00003C28  FC 06 40 40 */	fcmpo cr0, f6, f8
/* 8000704C 00003C2C  40 80 00 18 */	bge lbl_80007064
/* 80007050 00003C30  C0 97 00 08 */	lfs f4, 8(r23)
/* 80007054 00003C34  FC 06 20 40 */	fcmpo cr0, f6, f4
/* 80007058 00003C38  40 80 00 0C */	bge lbl_80007064
/* 8000705C 00003C3C  38 60 00 00 */	li r3, 0
/* 80007060 00003C40  48 00 06 FC */	b lbl_8000775C
lbl_80007064:
/* 80007064 00003C44  EC 87 18 28 */	fsubs f4, f7, f3
/* 80007068 00003C48  FC 04 40 40 */	fcmpo cr0, f4, f8
/* 8000706C 00003C4C  40 81 00 5C */	ble lbl_800070C8
/* 80007070 00003C50  C0 77 00 08 */	lfs f3, 8(r23)
/* 80007074 00003C54  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 80007078 00003C58  40 81 00 50 */	ble lbl_800070C8
/* 8000707C 00003C5C  38 60 00 00 */	li r3, 0
/* 80007080 00003C60  48 00 06 DC */	b lbl_8000775C
lbl_80007084:
/* 80007084 00003C64  EC C2 18 28 */	fsubs f6, f2, f3
/* 80007088 00003C68  C1 01 01 18 */	lfs f8, 0x118(r1)
/* 8000708C 00003C6C  FC 06 40 40 */	fcmpo cr0, f6, f8
/* 80007090 00003C70  40 81 00 18 */	ble lbl_800070A8
/* 80007094 00003C74  C0 97 00 08 */	lfs f4, 8(r23)
/* 80007098 00003C78  FC 06 20 40 */	fcmpo cr0, f6, f4
/* 8000709C 00003C7C  40 81 00 0C */	ble lbl_800070A8
/* 800070A0 00003C80  38 60 00 00 */	li r3, 0
/* 800070A4 00003C84  48 00 06 B8 */	b lbl_8000775C
lbl_800070A8:
/* 800070A8 00003C88  EC 87 18 2A */	fadds f4, f7, f3
/* 800070AC 00003C8C  FC 04 40 40 */	fcmpo cr0, f4, f8
/* 800070B0 00003C90  40 80 00 18 */	bge lbl_800070C8
/* 800070B4 00003C94  C0 77 00 08 */	lfs f3, 8(r23)
/* 800070B8 00003C98  FC 04 18 40 */	fcmpo cr0, f4, f3
/* 800070BC 00003C9C  40 80 00 0C */	bge lbl_800070C8
/* 800070C0 00003CA0  38 60 00 00 */	li r3, 0
/* 800070C4 00003CA4  48 00 06 98 */	b lbl_8000775C
lbl_800070C8:
/* 800070C8 00003CA8  EC 65 00 28 */	fsubs f3, f5, f0
/* 800070CC 00003CAC  D0 61 01 04 */	stfs f3, 0x104(r1)
/* 800070D0 00003CB0  C0 79 00 04 */	lfs f3, 4(r25)
/* 800070D4 00003CB4  EC 63 08 28 */	fsubs f3, f3, f1
/* 800070D8 00003CB8  D0 61 01 08 */	stfs f3, 0x108(r1)
/* 800070DC 00003CBC  C0 79 00 08 */	lfs f3, 8(r25)
/* 800070E0 00003CC0  EC 63 10 28 */	fsubs f3, f3, f2
/* 800070E4 00003CC4  D0 61 01 0C */	stfs f3, 0x10c(r1)
/* 800070E8 00003CC8  C3 E1 01 14 */	lfs f31, 0x114(r1)
/* 800070EC 00003CCC  C0 F7 00 04 */	lfs f7, 4(r23)
/* 800070F0 00003CD0  C3 01 01 10 */	lfs f24, 0x110(r1)
/* 800070F4 00003CD4  EE A1 F8 28 */	fsubs f21, f1, f31
/* 800070F8 00003CD8  EF 47 F8 28 */	fsubs f26, f7, f31
/* 800070FC 00003CDC  C2 C1 01 08 */	lfs f22, 0x108(r1)
/* 80007100 00003CE0  C0 D7 00 00 */	lfs f6, 0(r23)
/* 80007104 00003CE4  C0 61 01 04 */	lfs f3, 0x104(r1)
/* 80007108 00003CE8  EF 66 C0 28 */	fsubs f27, f6, f24
/* 8000710C 00003CEC  EC B6 06 B2 */	fmuls f5, f22, f26
/* 80007110 00003CF0  C3 C1 01 18 */	lfs f30, 0x118(r1)
/* 80007114 00003CF4  C1 17 00 08 */	lfs f8, 8(r23)
/* 80007118 00003CF8  ED 3A 06 B2 */	fmuls f9, f26, f26
/* 8000711C 00003CFC  C0 81 01 0C */	lfs f4, 0x10c(r1)
/* 80007120 00003D00  EE 80 C0 28 */	fsubs f20, f0, f24
/* 80007124 00003D04  C1 62 80 10 */	lfs f11, lbl_804D79F0(r2)
/* 80007128 00003D08  EF 1A 05 72 */	fmuls f24, f26, f21
/* 8000712C 00003D0C  EF 28 F0 28 */	fsubs f25, f8, f30
/* 80007130 00003D10  EC A3 2E FA */	fmadds f5, f3, f27, f5
/* 80007134 00003D14  ED 3B 4E FA */	fmadds f9, f27, f27, f9
/* 80007138 00003D18  ED A3 00 F2 */	fmuls f13, f3, f3
/* 8000713C 00003D1C  ED 96 05 B2 */	fmuls f12, f22, f22
/* 80007140 00003D20  ED 44 2E 7A */	fmadds f10, f4, f25, f5
/* 80007144 00003D24  ED 39 4E 7A */	fmadds f9, f25, f25, f9
/* 80007148 00003D28  EC AD 60 2A */	fadds f5, f13, f12
/* 8000714C 00003D2C  ED B6 05 72 */	fmuls f13, f22, f21
/* 80007150 00003D30  EE E4 01 32 */	fmuls f23, f4, f4
/* 80007154 00003D34  ED 8A 02 B2 */	fmuls f12, f10, f10
/* 80007158 00003D38  EE A2 F0 28 */	fsubs f21, f2, f30
/* 8000715C 00003D3C  EC B7 28 2A */	fadds f5, f23, f5
/* 80007160 00003D40  EC 63 6D 3A */	fmadds f3, f3, f20, f13
/* 80007164 00003D44  EF 1B C5 3A */	fmadds f24, f27, f20, f24
/* 80007168 00003D48  FC 09 58 40 */	fcmpo cr0, f9, f11
/* 8000716C 00003D4C  EC 84 1D 7A */	fmadds f4, f4, f21, f3
/* 80007170 00003D50  ED 79 C5 7A */	fmadds f11, f25, f21, f24
/* 80007174 00003D54  ED 85 62 78 */	fmsubs f12, f5, f9, f12
/* 80007178 00003D58  40 80 00 18 */	bge lbl_80007190
/* 8000717C 00003D5C  C0 62 80 14 */	lfs f3, lbl_804D79F4(r2)
/* 80007180 00003D60  FC 09 18 40 */	fcmpo cr0, f9, f3
/* 80007184 00003D64  40 81 00 0C */	ble lbl_80007190
/* 80007188 00003D68  38 00 00 01 */	li r0, 1
/* 8000718C 00003D6C  48 00 00 08 */	b lbl_80007194
lbl_80007190:
/* 80007190 00003D70  38 00 00 00 */	li r0, 0
lbl_80007194:
/* 80007194 00003D74  2C 00 00 00 */	cmpwi r0, 0
/* 80007198 00003D78  41 82 00 74 */	beq lbl_8000720C
/* 8000719C 00003D7C  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 800071A0 00003D80  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 800071A4 00003D84  40 80 00 18 */	bge lbl_800071BC
/* 800071A8 00003D88  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 800071AC 00003D8C  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 800071B0 00003D90  40 81 00 0C */	ble lbl_800071BC
/* 800071B4 00003D94  38 00 00 01 */	li r0, 1
/* 800071B8 00003D98  48 00 00 08 */	b lbl_800071C0
lbl_800071BC:
/* 800071BC 00003D9C  38 00 00 00 */	li r0, 0
lbl_800071C0:
/* 800071C0 00003DA0  2C 00 00 00 */	cmpwi r0, 0
/* 800071C4 00003DA4  41 82 00 10 */	beq lbl_800071D4
/* 800071C8 00003DA8  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 800071CC 00003DAC  FF 00 00 90 */	fmr f24, f0
/* 800071D0 00003DB0  48 00 03 2C */	b lbl_800074FC
lbl_800071D4:
/* 800071D4 00003DB4  FC 20 20 50 */	fneg f1, f4
/* 800071D8 00003DB8  C8 02 80 20 */	lfd f0, lbl_804D7A00(r2)
/* 800071DC 00003DBC  C3 02 80 18 */	lfs f24, lbl_804D79F8(r2)
/* 800071E0 00003DC0  EC 21 28 24 */	fdivs f1, f1, f5
/* 800071E4 00003DC4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800071E8 00003DC8  FC 00 08 90 */	fmr f0, f1
/* 800071EC 00003DCC  40 81 00 0C */	ble lbl_800071F8
/* 800071F0 00003DD0  C0 02 80 28 */	lfs f0, lbl_804D7A08(r2)
/* 800071F4 00003DD4  48 00 03 08 */	b lbl_800074FC
lbl_800071F8:
/* 800071F8 00003DD8  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 800071FC 00003DDC  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80007200 00003DE0  40 80 02 FC */	bge lbl_800074FC
/* 80007204 00003DE4  FC 00 C0 90 */	fmr f0, f24
/* 80007208 00003DE8  48 00 02 F4 */	b lbl_800074FC
lbl_8000720C:
/* 8000720C 00003DEC  C0 62 80 10 */	lfs f3, lbl_804D79F0(r2)
/* 80007210 00003DF0  FC 0C 18 40 */	fcmpo cr0, f12, f3
/* 80007214 00003DF4  40 80 00 18 */	bge lbl_8000722C
/* 80007218 00003DF8  C0 62 80 14 */	lfs f3, lbl_804D79F4(r2)
/* 8000721C 00003DFC  FC 0C 18 40 */	fcmpo cr0, f12, f3
/* 80007220 00003E00  40 81 00 0C */	ble lbl_8000722C
/* 80007224 00003E04  38 00 00 01 */	li r0, 1
/* 80007228 00003E08  48 00 00 08 */	b lbl_80007230
lbl_8000722C:
/* 8000722C 00003E0C  38 00 00 00 */	li r0, 0
lbl_80007230:
/* 80007230 00003E10  2C 00 00 00 */	cmpwi r0, 0
/* 80007234 00003E14  41 82 01 E0 */	beq lbl_80007414
/* 80007238 00003E18  C9 22 80 38 */	lfd f9, lbl_804D7A18(r2)
/* 8000723C 00003E1C  C0 61 01 10 */	lfs f3, 0x110(r1)
/* 80007240 00003E20  FD 69 FE BA */	fmadd f11, f9, f26, f31
/* 80007244 00003E24  C0 99 00 04 */	lfs f4, 4(r25)
/* 80007248 00003E28  C0 B9 00 00 */	lfs f5, 0(r25)
/* 8000724C 00003E2C  FD 49 1E FA */	fmadd f10, f9, f27, f3
/* 80007250 00003E30  C0 79 00 08 */	lfs f3, 8(r25)
/* 80007254 00003E34  FD 60 58 18 */	frsp f11, f11
/* 80007258 00003E38  FD 29 F6 7A */	fmadd f9, f9, f25, f30
/* 8000725C 00003E3C  FD 40 50 18 */	frsp f10, f10
/* 80007260 00003E40  EC 21 58 28 */	fsubs f1, f1, f11
/* 80007264 00003E44  FD 20 48 18 */	frsp f9, f9
/* 80007268 00003E48  ED 64 58 28 */	fsubs f11, f4, f11
/* 8000726C 00003E4C  EC 80 50 28 */	fsubs f4, f0, f10
/* 80007270 00003E50  EC 21 00 72 */	fmuls f1, f1, f1
/* 80007274 00003E54  EC A5 50 28 */	fsubs f5, f5, f10
/* 80007278 00003E58  EC 0B 02 F2 */	fmuls f0, f11, f11
/* 8000727C 00003E5C  EC 42 48 28 */	fsubs f2, f2, f9
/* 80007280 00003E60  EC 24 09 3A */	fmadds f1, f4, f4, f1
/* 80007284 00003E64  EC 63 48 28 */	fsubs f3, f3, f9
/* 80007288 00003E68  EC 05 01 7A */	fmadds f0, f5, f5, f0
/* 8000728C 00003E6C  EC 22 08 BA */	fmadds f1, f2, f2, f1
/* 80007290 00003E70  EC 03 00 FA */	fmadds f0, f3, f3, f0
/* 80007294 00003E74  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80007298 00003E78  40 80 00 C0 */	bge lbl_80007358
/* 8000729C 00003E7C  80 7A 00 00 */	lwz r3, 0(r26)
/* 800072A0 00003E80  80 1A 00 04 */	lwz r0, 4(r26)
/* 800072A4 00003E84  C8 22 80 20 */	lfd f1, lbl_804D7A00(r2)
/* 800072A8 00003E88  90 61 00 6C */	stw r3, 0x6c(r1)
/* 800072AC 00003E8C  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 800072B0 00003E90  90 01 00 70 */	stw r0, 0x70(r1)
/* 800072B4 00003E94  80 1A 00 08 */	lwz r0, 8(r26)
/* 800072B8 00003E98  90 01 00 74 */	stw r0, 0x74(r1)
/* 800072BC 00003E9C  C0 9A 00 00 */	lfs f4, 0(r26)
/* 800072C0 00003EA0  C0 5A 00 04 */	lfs f2, 4(r26)
/* 800072C4 00003EA4  C0 7A 00 08 */	lfs f3, 8(r26)
/* 800072C8 00003EA8  ED 26 20 28 */	fsubs f9, f6, f4
/* 800072CC 00003EAC  80 78 00 00 */	lwz r3, 0(r24)
/* 800072D0 00003EB0  ED 47 10 28 */	fsubs f10, f7, f2
/* 800072D4 00003EB4  80 18 00 04 */	lwz r0, 4(r24)
/* 800072D8 00003EB8  ED 68 18 28 */	fsubs f11, f8, f3
/* 800072DC 00003EBC  90 61 00 84 */	stw r3, 0x84(r1)
/* 800072E0 00003EC0  EC 4A 02 B2 */	fmuls f2, f10, f10
/* 800072E4 00003EC4  C0 81 00 70 */	lfs f4, 0x70(r1)
/* 800072E8 00003EC8  90 01 00 88 */	stw r0, 0x88(r1)
/* 800072EC 00003ECC  EC 49 12 7A */	fmadds f2, f9, f9, f2
/* 800072F0 00003ED0  C0 C1 00 6C */	lfs f6, 0x6c(r1)
/* 800072F4 00003ED4  80 18 00 08 */	lwz r0, 8(r24)
/* 800072F8 00003ED8  C1 01 00 74 */	lfs f8, 0x74(r1)
/* 800072FC 00003EDC  90 01 00 8C */	stw r0, 0x8c(r1)
/* 80007300 00003EE0  EC 4B 12 FA */	fmadds f2, f11, f11, f2
/* 80007304 00003EE4  C0 61 00 88 */	lfs f3, 0x88(r1)
/* 80007308 00003EE8  C0 A1 00 84 */	lfs f5, 0x84(r1)
/* 8000730C 00003EEC  EC 64 18 28 */	fsubs f3, f4, f3
/* 80007310 00003EF0  C0 E1 00 8C */	lfs f7, 0x8c(r1)
/* 80007314 00003EF4  EC 86 28 28 */	fsubs f4, f6, f5
/* 80007318 00003EF8  EC A8 38 28 */	fsubs f5, f8, f7
/* 8000731C 00003EFC  EC 6A 00 F2 */	fmuls f3, f10, f3
/* 80007320 00003F00  EC 69 19 3A */	fmadds f3, f9, f4, f3
/* 80007324 00003F04  EC 6B 19 7A */	fmadds f3, f11, f5, f3
/* 80007328 00003F08  FC 60 18 50 */	fneg f3, f3
/* 8000732C 00003F0C  EC 43 10 24 */	fdivs f2, f3, f2
/* 80007330 00003F10  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80007334 00003F14  40 81 00 0C */	ble lbl_80007340
/* 80007338 00003F18  C0 42 80 28 */	lfs f2, lbl_804D7A08(r2)
/* 8000733C 00003F1C  48 00 00 14 */	b lbl_80007350
lbl_80007340:
/* 80007340 00003F20  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80007344 00003F24  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80007348 00003F28  40 80 00 08 */	bge lbl_80007350
/* 8000734C 00003F2C  FC 40 00 90 */	fmr f2, f0
lbl_80007350:
/* 80007350 00003F30  FF 00 10 90 */	fmr f24, f2
/* 80007354 00003F34  48 00 01 A8 */	b lbl_800074FC
lbl_80007358:
/* 80007358 00003F38  80 7A 00 00 */	lwz r3, 0(r26)
/* 8000735C 00003F3C  80 1A 00 04 */	lwz r0, 4(r26)
/* 80007360 00003F40  C8 22 80 20 */	lfd f1, lbl_804D7A00(r2)
/* 80007364 00003F44  90 61 00 3C */	stw r3, 0x3c(r1)
/* 80007368 00003F48  C0 02 80 28 */	lfs f0, lbl_804D7A08(r2)
/* 8000736C 00003F4C  90 01 00 40 */	stw r0, 0x40(r1)
/* 80007370 00003F50  80 1A 00 08 */	lwz r0, 8(r26)
/* 80007374 00003F54  90 01 00 44 */	stw r0, 0x44(r1)
/* 80007378 00003F58  C0 9A 00 00 */	lfs f4, 0(r26)
/* 8000737C 00003F5C  C0 5A 00 04 */	lfs f2, 4(r26)
/* 80007380 00003F60  C0 7A 00 08 */	lfs f3, 8(r26)
/* 80007384 00003F64  ED 26 20 28 */	fsubs f9, f6, f4
/* 80007388 00003F68  80 79 00 00 */	lwz r3, 0(r25)
/* 8000738C 00003F6C  ED 47 10 28 */	fsubs f10, f7, f2
/* 80007390 00003F70  80 19 00 04 */	lwz r0, 4(r25)
/* 80007394 00003F74  ED 68 18 28 */	fsubs f11, f8, f3
/* 80007398 00003F78  90 61 00 54 */	stw r3, 0x54(r1)
/* 8000739C 00003F7C  EC 4A 02 B2 */	fmuls f2, f10, f10
/* 800073A0 00003F80  C0 81 00 40 */	lfs f4, 0x40(r1)
/* 800073A4 00003F84  90 01 00 58 */	stw r0, 0x58(r1)
/* 800073A8 00003F88  EC 49 12 7A */	fmadds f2, f9, f9, f2
/* 800073AC 00003F8C  C0 C1 00 3C */	lfs f6, 0x3c(r1)
/* 800073B0 00003F90  80 19 00 08 */	lwz r0, 8(r25)
/* 800073B4 00003F94  C1 01 00 44 */	lfs f8, 0x44(r1)
/* 800073B8 00003F98  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800073BC 00003F9C  EC 4B 12 FA */	fmadds f2, f11, f11, f2
/* 800073C0 00003FA0  C0 61 00 58 */	lfs f3, 0x58(r1)
/* 800073C4 00003FA4  C0 A1 00 54 */	lfs f5, 0x54(r1)
/* 800073C8 00003FA8  EC 64 18 28 */	fsubs f3, f4, f3
/* 800073CC 00003FAC  C0 E1 00 5C */	lfs f7, 0x5c(r1)
/* 800073D0 00003FB0  EC 86 28 28 */	fsubs f4, f6, f5
/* 800073D4 00003FB4  EC A8 38 28 */	fsubs f5, f8, f7
/* 800073D8 00003FB8  EC 6A 00 F2 */	fmuls f3, f10, f3
/* 800073DC 00003FBC  EC 69 19 3A */	fmadds f3, f9, f4, f3
/* 800073E0 00003FC0  EC 6B 19 7A */	fmadds f3, f11, f5, f3
/* 800073E4 00003FC4  FC 60 18 50 */	fneg f3, f3
/* 800073E8 00003FC8  EC 43 10 24 */	fdivs f2, f3, f2
/* 800073EC 00003FCC  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800073F0 00003FD0  40 81 00 0C */	ble lbl_800073FC
/* 800073F4 00003FD4  FC 40 00 90 */	fmr f2, f0
/* 800073F8 00003FD8  48 00 00 14 */	b lbl_8000740C
lbl_800073FC:
/* 800073FC 00003FDC  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80007400 00003FE0  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 80007404 00003FE4  40 80 00 08 */	bge lbl_8000740C
/* 80007408 00003FE8  C0 42 80 18 */	lfs f2, lbl_804D79F8(r2)
lbl_8000740C:
/* 8000740C 00003FEC  FF 00 10 90 */	fmr f24, f2
/* 80007410 00003FF0  48 00 00 EC */	b lbl_800074FC
lbl_80007414:
/* 80007414 00003FF4  EC 29 01 32 */	fmuls f1, f9, f4
/* 80007418 00003FF8  C8 42 80 20 */	lfd f2, lbl_804D7A00(r2)
/* 8000741C 00003FFC  EC 0A 01 32 */	fmuls f0, f10, f4
/* 80007420 00004000  EC 2A 0A F8 */	fmsubs f1, f10, f11, f1
/* 80007424 00004004  EC 05 02 F8 */	fmsubs f0, f5, f11, f0
/* 80007428 00004008  EC 21 60 24 */	fdivs f1, f1, f12
/* 8000742C 0000400C  EF 00 60 24 */	fdivs f24, f0, f12
/* 80007430 00004010  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 80007434 00004014  FC 00 08 90 */	fmr f0, f1
/* 80007438 00004018  41 81 00 20 */	bgt lbl_80007458
/* 8000743C 0000401C  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 80007440 00004020  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80007444 00004024  41 80 00 14 */	blt lbl_80007458
/* 80007448 00004028  FC 18 10 40 */	fcmpo cr0, f24, f2
/* 8000744C 0000402C  41 81 00 0C */	bgt lbl_80007458
/* 80007450 00004030  FC 18 08 40 */	fcmpo cr0, f24, f1
/* 80007454 00004034  40 80 00 A8 */	bge lbl_800074FC
lbl_80007458:
/* 80007458 00004038  C8 22 80 30 */	lfd f1, lbl_804D7A10(r2)
/* 8000745C 0000403C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80007460 00004040  40 80 00 24 */	bge lbl_80007484
/* 80007464 00004044  C2 A2 80 18 */	lfs f21, lbl_804D79F8(r2)
/* 80007468 00004048  38 7A 00 00 */	addi r3, r26, 0
/* 8000746C 0000404C  38 97 00 00 */	addi r4, r23, 0
/* 80007470 00004050  38 B8 00 00 */	addi r5, r24, 0
/* 80007474 00004054  38 C1 00 D0 */	addi r6, r1, 0xd0
/* 80007478 00004058  4B FF EA 45 */	bl lbColl_80005EBC
/* 8000747C 0000405C  FE 80 08 90 */	fmr f20, f1
/* 80007480 00004060  48 00 00 20 */	b lbl_800074A0
lbl_80007484:
/* 80007484 00004064  C2 A2 80 28 */	lfs f21, lbl_804D7A08(r2)
/* 80007488 00004068  38 7A 00 00 */	addi r3, r26, 0
/* 8000748C 0000406C  38 97 00 00 */	addi r4, r23, 0
/* 80007490 00004070  38 B9 00 00 */	addi r5, r25, 0
/* 80007494 00004074  38 C1 00 D0 */	addi r6, r1, 0xd0
/* 80007498 00004078  4B FF EA 25 */	bl lbColl_80005EBC
/* 8000749C 0000407C  FE 80 08 90 */	fmr f20, f1
lbl_800074A0:
/* 800074A0 00004080  C8 02 80 30 */	lfd f0, lbl_804D7A10(r2)
/* 800074A4 00004084  FC 18 00 40 */	fcmpo cr0, f24, f0
/* 800074A8 00004088  40 80 00 20 */	bge lbl_800074C8
/* 800074AC 0000408C  C2 C2 80 18 */	lfs f22, lbl_804D79F8(r2)
/* 800074B0 00004090  38 78 00 00 */	addi r3, r24, 0
/* 800074B4 00004094  38 99 00 00 */	addi r4, r25, 0
/* 800074B8 00004098  38 BA 00 00 */	addi r5, r26, 0
/* 800074BC 0000409C  38 C1 00 CC */	addi r6, r1, 0xcc
/* 800074C0 000040A0  4B FF E9 FD */	bl lbColl_80005EBC
/* 800074C4 000040A4  48 00 00 1C */	b lbl_800074E0
lbl_800074C8:
/* 800074C8 000040A8  C2 C2 80 28 */	lfs f22, lbl_804D7A08(r2)
/* 800074CC 000040AC  38 78 00 00 */	addi r3, r24, 0
/* 800074D0 000040B0  38 99 00 00 */	addi r4, r25, 0
/* 800074D4 000040B4  38 B7 00 00 */	addi r5, r23, 0
/* 800074D8 000040B8  38 C1 00 CC */	addi r6, r1, 0xcc
/* 800074DC 000040BC  4B FF E9 E1 */	bl lbColl_80005EBC
lbl_800074E0:
/* 800074E0 000040C0  FC 14 08 40 */	fcmpo cr0, f20, f1
/* 800074E4 000040C4  40 80 00 10 */	bge lbl_800074F4
/* 800074E8 000040C8  FC 00 A8 90 */	fmr f0, f21
/* 800074EC 000040CC  C3 01 00 D0 */	lfs f24, 0xd0(r1)
/* 800074F0 000040D0  48 00 00 0C */	b lbl_800074FC
lbl_800074F4:
/* 800074F4 000040D4  C0 01 00 CC */	lfs f0, 0xcc(r1)
/* 800074F8 000040D8  FF 00 B0 90 */	fmr f24, f22
lbl_800074FC:
/* 800074FC 000040DC  C0 81 01 04 */	lfs f4, 0x104(r1)
/* 80007500 000040E0  EC 5A FE 3A */	fmadds f2, f26, f24, f31
/* 80007504 000040E4  C0 61 01 1C */	lfs f3, 0x11c(r1)
/* 80007508 000040E8  EC 39 F6 3A */	fmadds f1, f25, f24, f30
/* 8000750C 000040EC  EC 64 18 3A */	fmadds f3, f4, f0, f3
/* 80007510 000040F0  D0 7B 00 00 */	stfs f3, 0(r27)
/* 80007514 000040F4  C0 81 01 08 */	lfs f4, 0x108(r1)
/* 80007518 000040F8  C0 61 01 20 */	lfs f3, 0x120(r1)
/* 8000751C 000040FC  EC 64 18 3A */	fmadds f3, f4, f0, f3
/* 80007520 00004100  D0 7B 00 04 */	stfs f3, 4(r27)
/* 80007524 00004104  C0 81 01 0C */	lfs f4, 0x10c(r1)
/* 80007528 00004108  C0 61 01 24 */	lfs f3, 0x124(r1)
/* 8000752C 0000410C  EC 04 18 3A */	fmadds f0, f4, f0, f3
/* 80007530 00004110  D0 1B 00 08 */	stfs f0, 8(r27)
/* 80007534 00004114  C0 01 01 10 */	lfs f0, 0x110(r1)
/* 80007538 00004118  EC 1B 06 3A */	fmadds f0, f27, f24, f0
/* 8000753C 0000411C  D0 1C 00 00 */	stfs f0, 0(r28)
/* 80007540 00004120  D0 5C 00 04 */	stfs f2, 4(r28)
/* 80007544 00004124  D0 3C 00 08 */	stfs f1, 8(r28)
/* 80007548 00004128  C0 3B 00 04 */	lfs f1, 4(r27)
/* 8000754C 0000412C  C0 1C 00 04 */	lfs f0, 4(r28)
/* 80007550 00004130  C0 9B 00 00 */	lfs f4, 0(r27)
/* 80007554 00004134  EC 21 00 28 */	fsubs f1, f1, f0
/* 80007558 00004138  C0 1C 00 00 */	lfs f0, 0(r28)
/* 8000755C 0000413C  C0 7B 00 08 */	lfs f3, 8(r27)
/* 80007560 00004140  C0 5C 00 08 */	lfs f2, 8(r28)
/* 80007564 00004144  EC 84 00 28 */	fsubs f4, f4, f0
/* 80007568 00004148  EC 21 00 72 */	fmuls f1, f1, f1
/* 8000756C 0000414C  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80007570 00004150  EC 43 10 28 */	fsubs f2, f3, f2
/* 80007574 00004154  EC 24 09 3A */	fmadds f1, f4, f4, f1
/* 80007578 00004158  EC 22 08 BA */	fmadds f1, f2, f2, f1
/* 8000757C 0000415C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80007580 00004160  FC 80 08 90 */	fmr f4, f1
/* 80007584 00004164  40 81 00 54 */	ble lbl_800075D8
/* 80007588 00004168  FC 20 20 34 */	frsqrte f1, f4
/* 8000758C 0000416C  C8 62 80 38 */	lfd f3, lbl_804D7A18(r2)
/* 80007590 00004170  C8 42 80 40 */	lfd f2, lbl_804D7A20(r2)
/* 80007594 00004174  FC 01 00 72 */	fmul f0, f1, f1
/* 80007598 00004178  FC 23 00 72 */	fmul f1, f3, f1
/* 8000759C 0000417C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800075A0 00004180  FC 21 00 32 */	fmul f1, f1, f0
/* 800075A4 00004184  FC 01 00 72 */	fmul f0, f1, f1
/* 800075A8 00004188  FC 23 00 72 */	fmul f1, f3, f1
/* 800075AC 0000418C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800075B0 00004190  FC 21 00 32 */	fmul f1, f1, f0
/* 800075B4 00004194  FC 01 00 72 */	fmul f0, f1, f1
/* 800075B8 00004198  FC 23 00 72 */	fmul f1, f3, f1
/* 800075BC 0000419C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800075C0 000041A0  FC 01 00 32 */	fmul f0, f1, f0
/* 800075C4 000041A4  FC 04 00 32 */	fmul f0, f4, f0
/* 800075C8 000041A8  FC 00 00 18 */	frsp f0, f0
/* 800075CC 000041AC  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800075D0 000041B0  C3 C1 00 38 */	lfs f30, 0x38(r1)
/* 800075D4 000041B4  48 00 00 08 */	b lbl_800075DC
lbl_800075D8:
/* 800075D8 000041B8  FF C0 20 90 */	fmr f30, f4
lbl_800075DC:
/* 800075DC 000041BC  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 800075E0 000041C0  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 800075E4 000041C4  40 80 00 18 */	bge lbl_800075FC
/* 800075E8 000041C8  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 800075EC 000041CC  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 800075F0 000041D0  40 81 00 0C */	ble lbl_800075FC
/* 800075F4 000041D4  38 00 00 01 */	li r0, 1
/* 800075F8 000041D8  48 00 00 08 */	b lbl_80007600
lbl_800075FC:
/* 800075FC 000041DC  38 00 00 00 */	li r0, 0
lbl_80007600:
/* 80007600 000041E0  2C 00 00 00 */	cmpwi r0, 0
/* 80007604 000041E4  41 82 00 30 */	beq lbl_80007634
/* 80007608 000041E8  EC 1C E8 2A */	fadds f0, f28, f29
/* 8000760C 000041EC  38 60 00 01 */	li r3, 1
/* 80007610 000041F0  EC 00 F0 28 */	fsubs f0, f0, f30
/* 80007614 000041F4  D0 1F 00 00 */	stfs f0, 0(r31)
/* 80007618 000041F8  80 9B 00 00 */	lwz r4, 0(r27)
/* 8000761C 000041FC  80 1B 00 04 */	lwz r0, 4(r27)
/* 80007620 00004200  90 9E 00 00 */	stw r4, 0(r30)
/* 80007624 00004204  90 1E 00 04 */	stw r0, 4(r30)
/* 80007628 00004208  80 1B 00 08 */	lwz r0, 8(r27)
/* 8000762C 0000420C  90 1E 00 08 */	stw r0, 8(r30)
/* 80007630 00004210  48 00 01 2C */	b lbl_8000775C
lbl_80007634:
/* 80007634 00004214  38 7D 00 00 */	addi r3, r29, 0
/* 80007638 00004218  38 81 00 9C */	addi r4, r1, 0x9c
/* 8000763C 0000421C  48 37 1C D5 */	bl HSD_MtxInverse
/* 80007640 00004220  38 9B 00 00 */	addi r4, r27, 0
/* 80007644 00004224  38 61 00 9C */	addi r3, r1, 0x9c
/* 80007648 00004228  38 A1 01 1C */	addi r5, r1, 0x11c
/* 8000764C 0000422C  48 33 B4 5D */	bl PSMTXMUltiVec
/* 80007650 00004230  38 9C 00 00 */	addi r4, r28, 0
/* 80007654 00004234  38 61 00 9C */	addi r3, r1, 0x9c
/* 80007658 00004238  38 A1 01 04 */	addi r5, r1, 0x104
/* 8000765C 0000423C  48 33 B4 4D */	bl PSMTXMUltiVec
/* 80007660 00004240  C0 21 01 20 */	lfs f1, 0x120(r1)
/* 80007664 00004244  C0 01 01 08 */	lfs f0, 0x108(r1)
/* 80007668 00004248  C0 41 01 1C */	lfs f2, 0x11c(r1)
/* 8000766C 0000424C  EC 21 00 28 */	fsubs f1, f1, f0
/* 80007670 00004250  C0 01 01 04 */	lfs f0, 0x104(r1)
/* 80007674 00004254  C0 61 01 24 */	lfs f3, 0x124(r1)
/* 80007678 00004258  EC 82 00 28 */	fsubs f4, f2, f0
/* 8000767C 0000425C  C0 41 01 0C */	lfs f2, 0x10c(r1)
/* 80007680 00004260  EC 21 00 72 */	fmuls f1, f1, f1
/* 80007684 00004264  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80007688 00004268  EC 43 10 28 */	fsubs f2, f3, f2
/* 8000768C 0000426C  EC 24 09 3A */	fmadds f1, f4, f4, f1
/* 80007690 00004270  EC 22 08 BA */	fmadds f1, f2, f2, f1
/* 80007694 00004274  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80007698 00004278  FC 80 08 90 */	fmr f4, f1
/* 8000769C 0000427C  40 81 00 54 */	ble lbl_800076F0
/* 800076A0 00004280  FC 20 20 34 */	frsqrte f1, f4
/* 800076A4 00004284  C8 62 80 38 */	lfd f3, lbl_804D7A18(r2)
/* 800076A8 00004288  C8 42 80 40 */	lfd f2, lbl_804D7A20(r2)
/* 800076AC 0000428C  FC 01 00 72 */	fmul f0, f1, f1
/* 800076B0 00004290  FC 23 00 72 */	fmul f1, f3, f1
/* 800076B4 00004294  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800076B8 00004298  FC 21 00 32 */	fmul f1, f1, f0
/* 800076BC 0000429C  FC 01 00 72 */	fmul f0, f1, f1
/* 800076C0 000042A0  FC 23 00 72 */	fmul f1, f3, f1
/* 800076C4 000042A4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800076C8 000042A8  FC 21 00 32 */	fmul f1, f1, f0
/* 800076CC 000042AC  FC 01 00 72 */	fmul f0, f1, f1
/* 800076D0 000042B0  FC 23 00 72 */	fmul f1, f3, f1
/* 800076D4 000042B4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800076D8 000042B8  FC 01 00 32 */	fmul f0, f1, f0
/* 800076DC 000042BC  FC 04 00 32 */	fmul f0, f4, f0
/* 800076E0 000042C0  FC 00 00 18 */	frsp f0, f0
/* 800076E4 000042C4  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800076E8 000042C8  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 800076EC 000042CC  48 00 00 08 */	b lbl_800076F4
lbl_800076F0:
/* 800076F0 000042D0  FC 20 20 90 */	fmr f1, f4
lbl_800076F4:
/* 800076F4 000042D4  EC 1D 07 B2 */	fmuls f0, f29, f30
/* 800076F8 000042D8  EC 00 08 24 */	fdivs f0, f0, f1
/* 800076FC 000042DC  EC 40 F0 24 */	fdivs f2, f0, f30
/* 80007700 000042E0  EC 3C 00 2A */	fadds f1, f28, f0
/* 80007704 000042E4  EC 01 F0 28 */	fsubs f0, f1, f30
/* 80007708 000042E8  FC 01 F0 40 */	fcmpo cr0, f1, f30
/* 8000770C 000042EC  D0 1F 00 00 */	stfs f0, 0(r31)
/* 80007710 000042F0  C0 3C 00 00 */	lfs f1, 0(r28)
/* 80007714 000042F4  C0 1B 00 00 */	lfs f0, 0(r27)
/* 80007718 000042F8  EC 00 08 28 */	fsubs f0, f0, f1
/* 8000771C 000042FC  EC 02 08 3A */	fmadds f0, f2, f0, f1
/* 80007720 00004300  D0 1E 00 00 */	stfs f0, 0(r30)
/* 80007724 00004304  C0 3C 00 04 */	lfs f1, 4(r28)
/* 80007728 00004308  C0 1B 00 04 */	lfs f0, 4(r27)
/* 8000772C 0000430C  EC 00 08 28 */	fsubs f0, f0, f1
/* 80007730 00004310  EC 02 08 3A */	fmadds f0, f2, f0, f1
/* 80007734 00004314  D0 1E 00 04 */	stfs f0, 4(r30)
/* 80007738 00004318  C0 3C 00 08 */	lfs f1, 8(r28)
/* 8000773C 0000431C  C0 1B 00 08 */	lfs f0, 8(r27)
/* 80007740 00004320  EC 00 08 28 */	fsubs f0, f0, f1
/* 80007744 00004324  EC 02 08 3A */	fmadds f0, f2, f0, f1
/* 80007748 00004328  D0 1E 00 08 */	stfs f0, 8(r30)
/* 8000774C 0000432C  40 80 00 0C */	bge lbl_80007758
/* 80007750 00004330  38 60 00 00 */	li r3, 0
/* 80007754 00004334  48 00 00 08 */	b lbl_8000775C
lbl_80007758:
/* 80007758 00004338  38 60 00 01 */	li r3, 1
lbl_8000775C:
/* 8000775C 0000433C  BA E1 01 2C */	lmw r23, 0x12c(r1)
/* 80007760 00004340  80 01 01 B4 */	lwz r0, 0x1b4(r1)
/* 80007764 00004344  CB E1 01 A8 */	lfd f31, 0x1a8(r1)
/* 80007768 00004348  CB C1 01 A0 */	lfd f30, 0x1a0(r1)
/* 8000776C 0000434C  CB A1 01 98 */	lfd f29, 0x198(r1)
/* 80007770 00004350  CB 81 01 90 */	lfd f28, 0x190(r1)
/* 80007774 00004354  CB 61 01 88 */	lfd f27, 0x188(r1)
/* 80007778 00004358  CB 41 01 80 */	lfd f26, 0x180(r1)
/* 8000777C 0000435C  CB 21 01 78 */	lfd f25, 0x178(r1)
/* 80007780 00004360  CB 01 01 70 */	lfd f24, 0x170(r1)
/* 80007784 00004364  CA E1 01 68 */	lfd f23, 0x168(r1)
/* 80007788 00004368  CA C1 01 60 */	lfd f22, 0x160(r1)
/* 8000778C 0000436C  CA A1 01 58 */	lfd f21, 0x158(r1)
/* 80007790 00004370  CA 81 01 50 */	lfd f20, 0x150(r1)
/* 80007794 00004374  38 21 01 B0 */	addi r1, r1, 0x1b0
/* 80007798 00004378  7C 08 03 A6 */	mtlr r0
/* 8000779C 0000437C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool lbColl_80006E58(Vec3* arg0, Vec3* arg1, Vec3* arg2, Vec3* arg3,
                     Vec3* arg4, Vec3* arg5, Mtx arg6, Vec3* arg7, f32 arg8,
                     f32 scl, f32 argA)
{
    f32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 spD0;
    f32 spCC;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp44;
    f32 sp40;
    Vec3 vec2;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f10_4;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f11_3;
    f32 temp_f11_4;
    f32 temp_f11_5;
    f32 temp_f12;
    f32 temp_f1;
    f32 temp_f1_10;
    f32 temp_f1_14;
    f32 temp_f1_15;
    f32 temp_f1_16;
    f32 temp_f1_17;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_9;
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f25;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f2_4;
    f32 temp_f2_5;
    f32 temp_f2_6;
    f32 temp_f2_7;
    f32 temp_f2_8;
    f32 temp_f3;
    f32 temp_f3_2;
    f32 temp_f3_3;
    f32 temp_f4;
    f32 temp_f4_10;
    f32 temp_f4_2;
    f32 temp_f4_3;
    f32 temp_f4_4;
    f32 temp_f4_5;
    f32 temp_f4_6;
    f32 temp_f4_7;
    f32 temp_f4_8;
    f32 temp_f4_9;
    f32 temp_f5;
    f32 temp_f5_2;
    f32 temp_f5_3;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f6_3;
    f32 temp_f6_4;
    f32 temp_f7;
    f32 temp_f7_2;
    f32 temp_f8;
    f32 temp_f9;
    f32 temp_f9_2;
    f32 temp_f9_3;
    f32 temp_f9_4;
    f32 var_f0;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f20;
    f32 var_f21;
    f32 var_f22;
    f32 var_f24;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f30;
    f64 temp_f1_11;
    f64 temp_f1_12;
    f64 temp_f1_13;
    f64 temp_f1_6;
    f64 temp_f1_7;
    f64 temp_f1_8;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    Mtx sp9C;

    temp_f3 = (scl * argA) + arg8;
    sp11C = arg0->x;
    sp120 = arg0->y;
    sp124 = arg0->z;
    sp110 = arg2->x;
    sp114 = arg2->y;
    sp118 = arg2->z;
    temp_f5 = arg1->x;
    if (sp11C > temp_f5) {
        temp_f2 = sp11C + temp_f3;
        if ((temp_f2 < sp110) && (temp_f2 < arg3->x)) {
            return 0;
        }
        temp_f2_2 = temp_f5 - temp_f3;
        if ((temp_f2_2 > sp110) && (temp_f2_2 > arg3->x)) {
            return 0;
        }
        goto block_13;
    }
    temp_f2_3 = sp11C - temp_f3;
    if ((temp_f2_3 > sp110) && (temp_f2_3 > arg3->x)) {
        return 0;
    }
    temp_f2_4 = temp_f5 + temp_f3;
    if ((temp_f2_4 < sp110) && (temp_f2_4 < arg3->x)) {
        return 0;
    }
block_13:
    temp_f6 = arg1->y;
    if (sp120 > temp_f6) {
        temp_f4 = sp120 + temp_f3;
        if ((temp_f4 < sp114) && (temp_f4 < arg3->y)) {
            return 0;
        }
        temp_f4_2 = temp_f6 - temp_f3;
        if ((temp_f4_2 > sp114) && (temp_f4_2 > arg3->y)) {
            return 0;
        }
        goto block_26;
    }
    temp_f4_3 = sp120 - temp_f3;
    if ((temp_f4_3 > sp114) && (temp_f4_3 > arg3->y)) {
        return 0;
    }
    temp_f4_4 = temp_f6 + temp_f3;
    if ((temp_f4_4 < sp114) && (temp_f4_4 < arg3->y)) {
        return 0;
    }
block_26:
    temp_f7 = arg1->z;
    if (sp124 > temp_f7) {
        temp_f6_2 = sp124 + temp_f3;
        if ((temp_f6_2 < sp118) && (temp_f6_2 < arg3->z)) {
            return 0;
        }
        temp_f4_5 = temp_f7 - temp_f3;
        if ((temp_f4_5 > sp118) && (temp_f4_5 > arg3->z)) {
            return 0;
        }
        goto block_39;
    }
    temp_f6_3 = sp124 - temp_f3;
    if ((temp_f6_3 > sp118) && (temp_f6_3 > arg3->z)) {
        return 0;
    }
    temp_f4_6 = temp_f7 + temp_f3;
    if ((temp_f4_6 < sp118) && (temp_f4_6 < arg3->z)) {
        return 0;
    }
block_39:
    temp_f3_2 = temp_f5 - sp11C;
    sp104 = temp_f3_2;
    sp108 = arg1->y - sp120;
    sp10C = arg1->z - sp124;
    temp_f7_2 = arg3->y;
    temp_f21 = sp120 - sp114;
    temp_f26 = temp_f7_2 - sp114;
    temp_f6_4 = arg3->x;
    temp_f27 = temp_f6_4 - sp110;
    temp_f8 = arg3->z;
    temp_f20 = sp11C - sp110;
    temp_f25 = temp_f8 - sp118;
    temp_f10 =
        (sp10C * temp_f25) + ((temp_f3_2 * temp_f27) + (sp108 * temp_f26));
    temp_f9 = (temp_f25 * temp_f25) +
              ((temp_f27 * temp_f27) + (temp_f26 * temp_f26));
    temp_f21_2 = sp124 - sp118;
    temp_f5_2 = (sp10C * sp10C) + ((temp_f3_2 * temp_f3_2) + (sp108 * sp108));
    temp_f4_7 =
        (sp10C * temp_f21_2) + ((temp_f3_2 * temp_f20) + (sp108 * temp_f21));
    temp_f11 = (temp_f25 * temp_f21_2) +
               ((temp_f27 * temp_f20) + (temp_f26 * temp_f21));
    temp_f12 = (temp_f5_2 * temp_f9) - (temp_f10 * temp_f10);
    if ((temp_f9 < 0.00001f) && (temp_f9 > -0.00001f)) {
        var_r0 = 1;
    } else {
        var_r0 = 0;
    }
    if (var_r0 != 0) {
        if ((temp_f5_2 < 0.00001f) && (temp_f5_2 > -0.00001f)) {
            var_r0_2 = 1;
        } else {
            var_r0_2 = 0;
        }
        if (var_r0_2 != 0) {
            var_f0 = 0.0f;
            var_f24 = 0.0f;
        } else {
            var_f24 = 0.0f;
            temp_f1 = -temp_f4_7 / temp_f5_2;
            var_f0 = temp_f1;
            if (temp_f1 > (f32) 1.0) {
                var_f0 = 1.0f;
            } else if (var_f0 < (f32) 0.0) {
                var_f0 = 0.0f;
            }
        }
    } else {
        if ((temp_f12 < 0.00001f) && (temp_f12 > -0.00001f)) {
            var_r0_3 = 1;
        } else {
            var_r0_3 = 0;
        }
        if (var_r0_3 != 0) {
            temp_f11_2 = (f32) ((0.5 * (f64) temp_f26) + (f64) sp114);
            temp_f10_2 = (f32) ((0.5 * (f64) temp_f27) + (f64) sp110);
            temp_f1_2 = sp120 - temp_f11_2;
            temp_f9_2 = (f32) ((0.5 * (f64) temp_f25) + (f64) sp118);
            temp_f11_3 = arg1->y - temp_f11_2;
            temp_f4_8 = sp11C - temp_f10_2;
            temp_f5_3 = arg1->x - temp_f10_2;
            temp_f2_5 = sp124 - temp_f9_2;
            temp_f3_3 = arg1->z - temp_f9_2;
            if (((temp_f2_5 * temp_f2_5) +
                 ((temp_f4_8 * temp_f4_8) + (temp_f1_2 * temp_f1_2))) <
                ((temp_f3_3 * temp_f3_3) +
                 ((temp_f5_3 * temp_f5_3) + (temp_f11_3 * temp_f11_3))))
            {
                sp6C = arg2->x;
                var_f0 = 0.0f;
                sp70 = arg2->y;
                sp74 = arg2->z;
                temp_f9_3 = temp_f6_4 - arg2->x;
                temp_f10_3 = temp_f7_2 - arg2->y;
                temp_f11_4 = temp_f8 - arg2->z;
                sp84 = arg0->x;
                sp88 = arg0->y;
                sp8C = arg0->z;
                var_f2 =
                    -((temp_f11_4 * (sp74 - sp8C)) +
                      ((temp_f9_3 * (sp6C - sp84)) +
                       (temp_f10_3 * (sp70 - sp88)))) /
                    ((temp_f11_4 * temp_f11_4) +
                     ((temp_f9_3 * temp_f9_3) + (temp_f10_3 * temp_f10_3)));
                if (var_f2 > (f32) 1.0) {
                    var_f2 = 1.0f;
                } else if (var_f2 < (f32) 0.0) {
                    var_f2 = 0.0f;
                }
                var_f24 = var_f2;
            } else {
                vec2.z = arg2->x;
                var_f0 = 1.0f;
                sp40 = arg2->y;
                sp44 = arg2->z;
                temp_f9_4 = temp_f6_4 - arg2->x;
                temp_f10_4 = temp_f7_2 - arg2->y;
                temp_f11_5 = temp_f8 - arg2->z;
                sp54 = arg1->x;
                sp58 = arg1->y;
                sp5C = arg1->z;
                var_f2_2 =
                    -((temp_f11_5 * (sp44 - sp5C)) +
                      ((temp_f9_4 * (vec2.z - sp54)) +
                       (temp_f10_4 * (sp40 - sp58)))) /
                    ((temp_f11_5 * temp_f11_5) +
                     ((temp_f9_4 * temp_f9_4) + (temp_f10_4 * temp_f10_4)));
                if (var_f2_2 > (f32) 1.0) {
                    var_f2_2 = 1.0f;
                } else if (var_f2_2 < (f32) 0.0) {
                    var_f2_2 = 0.0f;
                }
                var_f24 = var_f2_2;
            }
        } else {
            temp_f1_3 =
                ((temp_f10 * temp_f11) - (temp_f9 * temp_f4_7)) / temp_f12;
            var_f24 =
                ((temp_f5_2 * temp_f11) - (temp_f10 * temp_f4_7)) / temp_f12;
            var_f0 = temp_f1_3;
            if ((temp_f1_3 > (f32) 1.0) || (var_f0 < (f32) 0.0) ||
                (var_f24 > (f32) 1.0) || (var_f24 < (f32) 0.0))
            {
                if (var_f0 < (f32) 0.0) {
                    var_f21 = 0.0f;
                    var_f20 = lbColl_80005EBC(arg2, arg3, arg0, &spD0);
                } else {
                    var_f21 = 1.0f;
                    var_f20 = lbColl_80005EBC(arg2, arg3, arg1, &spD0);
                }
                if (var_f24 < (f32) 0.0) {
                    var_f22 = 0.0f;
                    var_f1 = lbColl_80005EBC(arg0, arg1, arg2, &spCC);
                } else {
                    var_f22 = 1.0f;
                    var_f1 = lbColl_80005EBC(arg0, arg1, arg3, &spCC);
                }
                if (var_f20 < var_f1) {
                    var_f0 = var_f21;
                    var_f24 = spD0;
                } else {
                    var_f0 = spCC;
                    var_f24 = var_f22;
                }
            }
        }
    }
    arg4->x = (sp104 * var_f0) + sp11C;
    arg4->y = (sp108 * var_f0) + sp120;
    arg4->z = (sp10C * var_f0) + sp124;
    arg5->x = (temp_f27 * var_f24) + sp110;
    arg5->y = (temp_f26 * var_f24) + sp114;
    arg5->z = (temp_f25 * var_f24) + sp118;
    temp_f1_4 = arg4->y - arg5->y;
    temp_f4_9 = arg4->x - arg5->x;
    temp_f2_6 = arg4->z - arg5->z;
    temp_f1_5 = (temp_f2_6 * temp_f2_6) +
                ((temp_f4_9 * temp_f4_9) + (temp_f1_4 * temp_f1_4));
    if (temp_f1_5 > 0.0f) {
        temp_f1_6 = __frsqrte(temp_f1_5);
        temp_f1_7 = 0.5 * temp_f1_6 *
                    -(((f64) temp_f1_5 * (temp_f1_6 * temp_f1_6)) - 3.0);
        temp_f1_8 = 0.5 * temp_f1_7 *
                    -(((f64) temp_f1_5 * (temp_f1_7 * temp_f1_7)) - 3.0);
        vec2.y =
            (f32) ((f64) temp_f1_5 *
                   (0.5 * temp_f1_8 *
                    -(((f64) temp_f1_5 * (temp_f1_8 * temp_f1_8)) - 3.0)));
        var_f30 = vec2.y;
    } else {
        var_f30 = temp_f1_5;
    }
    if ((var_f30 < 0.00001f) && (var_f30 > -0.00001f)) {
        var_r0_4 = 1;
    } else {
        var_r0_4 = 0;
    }
    if (var_r0_4 != 0) {
        arg2->x = (arg8 + scl) - var_f30;
        arg7->x = arg4->x;
        arg7->y = arg4->y;
        arg7->z = arg4->z;
        return 1;
    }
    HSD_MtxInverse(arg6, sp9C);
    PSMTXMUltiVec((f32(*)[4]) & sp9C[0], arg4, (Vec3*) &sp11C);
    PSMTXMUltiVec((f32(*)[4]) & sp9C[0], arg5, (Vec3*) &sp104);
    temp_f1_9 = sp120 - sp108;
    temp_f4_10 = sp11C - sp104;
    temp_f2_7 = sp124 - sp10C;
    temp_f1_10 = (temp_f2_7 * temp_f2_7) +
                 ((temp_f4_10 * temp_f4_10) + (temp_f1_9 * temp_f1_9));
    if (temp_f1_10 > 0.0f) {
        temp_f1_11 = __frsqrte(temp_f1_10);
        temp_f1_12 = 0.5 * temp_f1_11 *
                     -(((f64) temp_f1_10 * (temp_f1_11 * temp_f1_11)) - 3.0);
        temp_f1_13 = 0.5 * temp_f1_12 *
                     -(((f64) temp_f1_10 * (temp_f1_12 * temp_f1_12)) - 3.0);
        vec2.x =
            (f32) ((f64) temp_f1_10 *
                   (0.5 * temp_f1_13 *
                    -(((f64) temp_f1_10 * (temp_f1_13 * temp_f1_13)) - 3.0)));
        var_f1_2 = vec2.x;
    } else {
        var_f1_2 = temp_f1_10;
    }
    temp_f0 = (scl * var_f30) / var_f1_2;
    temp_f2_8 = temp_f0 / var_f30;
    temp_f1_14 = arg8 + temp_f0;
    arg2->x = temp_f1_14 - var_f30;
    temp_f1_15 = arg5->x;
    arg7->x = (temp_f2_8 * (arg4->x - temp_f1_15)) + temp_f1_15;
    temp_f1_16 = arg5->y;
    arg7->y = (temp_f2_8 * (arg4->y - temp_f1_16)) + temp_f1_16;
    temp_f1_17 = arg5->z;
    arg7->z = (temp_f2_8 * (arg4->z - temp_f1_17)) + temp_f1_17;
    if (temp_f1_14 < var_f30) {
        return 0;
    }
    return 1;
}
#endif

f32 const lbl_804D7A28 = 2;
f32 const lbl_804D7A2C = 4;
f32 const lbl_804D7A30 = M_PI;

#ifdef MUST_MATCH
#pragma push
asm void lbColl_800077A0(Vec3*, Mtx, Vec3*, Vec3*, Vec3*, Vec3*, f32*, f32,
                         f32)
{
    // clang-format off
    nofralloc
/* 800077A0 00004380  7C 08 02 A6 */	mflr r0
/* 800077A4 00004384  90 01 00 04 */	stw r0, 4(r1)
/* 800077A8 00004388  94 21 FF 60 */	stwu r1, -0xa0(r1)
/* 800077AC 0000438C  DB E1 00 98 */	stfd f31, 0x98(r1)
/* 800077B0 00004390  DB C1 00 90 */	stfd f30, 0x90(r1)
/* 800077B4 00004394  FF C0 10 90 */	fmr f30, f2
/* 800077B8 00004398  BF 41 00 78 */	stmw r26, 0x78(r1)
/* 800077BC 0000439C  7C BC 2B 78 */	mr r28, r5
/* 800077C0 000043A0  7C 7A 1B 78 */	mr r26, r3
/* 800077C4 000043A4  3B 64 00 00 */	addi r27, r4, 0
/* 800077C8 000043A8  3B A7 00 00 */	addi r29, r7, 0
/* 800077CC 000043AC  3B C8 00 00 */	addi r30, r8, 0
/* 800077D0 000043B0  7D 3F 4B 78 */	mr r31, r9
/* 800077D4 000043B4  C0 66 00 00 */	lfs f3, 0(r6)
/* 800077D8 000043B8  C0 05 00 00 */	lfs f0, 0(r5)
/* 800077DC 000043BC  EC 03 00 28 */	fsubs f0, f3, f0
/* 800077E0 000043C0  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 800077E4 000043C4  C0 46 00 04 */	lfs f2, 4(r6)
/* 800077E8 000043C8  C0 05 00 04 */	lfs f0, 4(r5)
/* 800077EC 000043CC  EC 02 00 28 */	fsubs f0, f2, f0
/* 800077F0 000043D0  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 800077F4 000043D4  C0 46 00 08 */	lfs f2, 8(r6)
/* 800077F8 000043D8  C0 05 00 08 */	lfs f0, 8(r5)
/* 800077FC 000043DC  EC 02 00 28 */	fsubs f0, f2, f0
/* 80007800 000043E0  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 80007804 000043E4  C0 01 00 68 */	lfs f0, 0x68(r1)
/* 80007808 000043E8  C0 42 80 18 */	lfs f2, lbl_804D79F8(r2)
/* 8000780C 000043EC  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 80007810 000043F0  40 82 00 1C */	bne lbl_8000782C
/* 80007814 000043F4  C0 01 00 6C */	lfs f0, 0x6c(r1)
/* 80007818 000043F8  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8000781C 000043FC  40 82 00 10 */	bne lbl_8000782C
/* 80007820 00004400  C0 01 00 70 */	lfs f0, 0x70(r1)
/* 80007824 00004404  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 80007828 00004408  41 82 02 A4 */	beq lbl_80007ACC
lbl_8000782C:
/* 8000782C 0000440C  D0 21 00 44 */	stfs f1, 0x44(r1)
/* 80007830 00004410  38 81 00 44 */	addi r4, r1, 0x44
/* 80007834 00004414  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80007838 00004418  38 7B 00 00 */	addi r3, r27, 0
/* 8000783C 0000441C  38 A4 00 00 */	addi r5, r4, 0
/* 80007840 00004420  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 80007844 00004424  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 80007848 00004428  48 33 B2 61 */	bl PSMTXMUltiVec
/* 8000784C 0000442C  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80007850 00004430  38 81 00 38 */	addi r4, r1, 0x38
/* 80007854 00004434  38 7B 00 00 */	addi r3, r27, 0
/* 80007858 00004438  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 8000785C 0000443C  7C 85 23 78 */	mr r5, r4
/* 80007860 00004440  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 80007864 00004444  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 80007868 00004448  48 33 B2 41 */	bl PSMTXMUltiVec
/* 8000786C 0000444C  C0 21 00 48 */	lfs f1, 0x48(r1)
/* 80007870 00004450  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 80007874 00004454  C0 41 00 44 */	lfs f2, 0x44(r1)
/* 80007878 00004458  EC 21 00 28 */	fsubs f1, f1, f0
/* 8000787C 0000445C  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 80007880 00004460  C0 61 00 4C */	lfs f3, 0x4c(r1)
/* 80007884 00004464  EC 82 00 28 */	fsubs f4, f2, f0
/* 80007888 00004468  C0 41 00 40 */	lfs f2, 0x40(r1)
/* 8000788C 0000446C  EC 21 00 72 */	fmuls f1, f1, f1
/* 80007890 00004470  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80007894 00004474  EC 43 10 28 */	fsubs f2, f3, f2
/* 80007898 00004478  EC 24 09 3A */	fmadds f1, f4, f4, f1
/* 8000789C 0000447C  EF E2 08 BA */	fmadds f31, f2, f2, f1
/* 800078A0 00004480  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800078A4 00004484  40 81 00 50 */	ble lbl_800078F4
/* 800078A8 00004488  FC 20 F8 34 */	frsqrte f1, f31
/* 800078AC 0000448C  C8 62 80 38 */	lfd f3, lbl_804D7A18(r2)
/* 800078B0 00004490  C8 42 80 40 */	lfd f2, lbl_804D7A20(r2)
/* 800078B4 00004494  FC 01 00 72 */	fmul f0, f1, f1
/* 800078B8 00004498  FC 23 00 72 */	fmul f1, f3, f1
/* 800078BC 0000449C  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 800078C0 000044A0  FC 21 00 32 */	fmul f1, f1, f0
/* 800078C4 000044A4  FC 01 00 72 */	fmul f0, f1, f1
/* 800078C8 000044A8  FC 23 00 72 */	fmul f1, f3, f1
/* 800078CC 000044AC  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 800078D0 000044B0  FC 21 00 32 */	fmul f1, f1, f0
/* 800078D4 000044B4  FC 01 00 72 */	fmul f0, f1, f1
/* 800078D8 000044B8  FC 23 00 72 */	fmul f1, f3, f1
/* 800078DC 000044BC  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 800078E0 000044C0  FC 01 00 32 */	fmul f0, f1, f0
/* 800078E4 000044C4  FC 1F 00 32 */	fmul f0, f31, f0
/* 800078E8 000044C8  FC 00 00 18 */	frsp f0, f0
/* 800078EC 000044CC  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 800078F0 000044D0  C3 E1 00 30 */	lfs f31, 0x30(r1)
lbl_800078F4:
/* 800078F4 000044D4  C1 81 00 68 */	lfs f12, 0x68(r1)
/* 800078F8 000044D8  EC 3F F0 2A */	fadds f1, f31, f30
/* 800078FC 000044DC  C1 61 00 6C */	lfs f11, 0x6c(r1)
/* 80007900 000044E0  EC 6C 03 32 */	fmuls f3, f12, f12
/* 80007904 000044E4  C1 A1 00 70 */	lfs f13, 0x70(r1)
/* 80007908 000044E8  EC 0B 02 F2 */	fmuls f0, f11, f11
/* 8000790C 000044EC  EC 8D 03 72 */	fmuls f4, f13, f13
/* 80007910 000044F0  C0 42 80 10 */	lfs f2, lbl_804D79F0(r2)
/* 80007914 000044F4  EC 03 00 2A */	fadds f0, f3, f0
/* 80007918 000044F8  C0 FC 00 00 */	lfs f7, 0(r28)
/* 8000791C 000044FC  C0 7A 00 00 */	lfs f3, 0(r26)
/* 80007920 00004500  C0 DC 00 04 */	lfs f6, 4(r28)
/* 80007924 00004504  EC 04 00 2A */	fadds f0, f4, f0
/* 80007928 00004508  C0 BA 00 04 */	lfs f5, 4(r26)
/* 8000792C 0000450C  ED 07 18 28 */	fsubs f8, f7, f3
/* 80007930 00004510  C0 9C 00 08 */	lfs f4, 8(r28)
/* 80007934 00004514  C0 7A 00 08 */	lfs f3, 8(r26)
/* 80007938 00004518  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 8000793C 0000451C  ED 26 28 28 */	fsubs f9, f6, f5
/* 80007940 00004520  ED 44 18 28 */	fsubs f10, f4, f3
/* 80007944 00004524  40 80 00 18 */	bge lbl_8000795C
/* 80007948 00004528  C0 42 80 14 */	lfs f2, lbl_804D79F4(r2)
/* 8000794C 0000452C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 80007950 00004530  40 81 00 0C */	ble lbl_8000795C
/* 80007954 00004534  38 00 00 01 */	li r0, 1
/* 80007958 00004538  48 00 00 08 */	b lbl_80007960
lbl_8000795C:
/* 8000795C 0000453C  38 00 00 00 */	li r0, 0
lbl_80007960:
/* 80007960 00004540  2C 00 00 00 */	cmpwi r0, 0
/* 80007964 00004544  41 82 00 0C */	beq lbl_80007970
/* 80007968 00004548  C0 62 80 18 */	lfs f3, lbl_804D79F8(r2)
/* 8000796C 0000454C  48 00 00 C8 */	b lbl_80007A34
lbl_80007970:
/* 80007970 00004550  EC 69 02 72 */	fmuls f3, f9, f9
/* 80007974 00004554  C0 E2 80 48 */	lfs f7, lbl_804D7A28(r2)
/* 80007978 00004558  C0 82 80 4C */	lfs f4, lbl_804D7A2C(r2)
/* 8000797C 0000455C  EC A7 02 F2 */	fmuls f5, f7, f11
/* 80007980 00004560  C0 42 80 18 */	lfs f2, lbl_804D79F8(r2)
/* 80007984 00004564  EC 68 1A 3A */	fmadds f3, f8, f8, f3
/* 80007988 00004568  EC C7 03 32 */	fmuls f6, f7, f12
/* 8000798C 0000456C  EC A5 02 72 */	fmuls f5, f5, f9
/* 80007990 00004570  EC 6A 1A BA */	fmadds f3, f10, f10, f3
/* 80007994 00004574  EC E7 03 72 */	fmuls f7, f7, f13
/* 80007998 00004578  EC A6 2A 3A */	fmadds f5, f6, f8, f5
/* 8000799C 0000457C  EC 84 00 32 */	fmuls f4, f4, f0
/* 800079A0 00004580  EC 21 18 7C */	fnmsubs f1, f1, f1, f3
/* 800079A4 00004584  EC A7 2A BA */	fmadds f5, f7, f10, f5
/* 800079A8 00004588  EC 24 00 72 */	fmuls f1, f4, f1
/* 800079AC 0000458C  EC 25 09 78 */	fmsubs f1, f5, f5, f1
/* 800079B0 00004590  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 800079B4 00004594  FC C0 08 90 */	fmr f6, f1
/* 800079B8 00004598  40 80 00 08 */	bge lbl_800079C0
/* 800079BC 0000459C  FC C0 10 90 */	fmr f6, f2
lbl_800079C0:
/* 800079C0 000045A0  C0 22 80 18 */	lfs f1, lbl_804D79F8(r2)
/* 800079C4 000045A4  FC 06 08 40 */	fcmpo cr0, f6, f1
/* 800079C8 000045A8  40 81 00 54 */	ble lbl_80007A1C
/* 800079CC 000045AC  FC 40 30 34 */	frsqrte f2, f6
/* 800079D0 000045B0  C8 82 80 38 */	lfd f4, lbl_804D7A18(r2)
/* 800079D4 000045B4  C8 62 80 40 */	lfd f3, lbl_804D7A20(r2)
/* 800079D8 000045B8  FC 22 00 B2 */	fmul f1, f2, f2
/* 800079DC 000045BC  FC 44 00 B2 */	fmul f2, f4, f2
/* 800079E0 000045C0  FC 26 18 7C */	fnmsub f1, f6, f1, f3
/* 800079E4 000045C4  FC 42 00 72 */	fmul f2, f2, f1
/* 800079E8 000045C8  FC 22 00 B2 */	fmul f1, f2, f2
/* 800079EC 000045CC  FC 44 00 B2 */	fmul f2, f4, f2
/* 800079F0 000045D0  FC 26 18 7C */	fnmsub f1, f6, f1, f3
/* 800079F4 000045D4  FC 42 00 72 */	fmul f2, f2, f1
/* 800079F8 000045D8  FC 22 00 B2 */	fmul f1, f2, f2
/* 800079FC 000045DC  FC 44 00 B2 */	fmul f2, f4, f2
/* 80007A00 000045E0  FC 26 18 7C */	fnmsub f1, f6, f1, f3
/* 80007A04 000045E4  FC 22 00 72 */	fmul f1, f2, f1
/* 80007A08 000045E8  FC 26 00 72 */	fmul f1, f6, f1
/* 80007A0C 000045EC  FC 20 08 18 */	frsp f1, f1
/* 80007A10 000045F0  D0 21 00 2C */	stfs f1, 0x2c(r1)
/* 80007A14 000045F4  C0 61 00 2C */	lfs f3, 0x2c(r1)
/* 80007A18 000045F8  48 00 00 08 */	b lbl_80007A20
lbl_80007A1C:
/* 80007A1C 000045FC  FC 60 30 90 */	fmr f3, f6
lbl_80007A20:
/* 80007A20 00004600  FC 40 28 50 */	fneg f2, f5
/* 80007A24 00004604  C0 22 80 48 */	lfs f1, lbl_804D7A28(r2)
/* 80007A28 00004608  EC 01 00 32 */	fmuls f0, f1, f0
/* 80007A2C 0000460C  EC 22 18 28 */	fsubs f1, f2, f3
/* 80007A30 00004610  EC 61 00 24 */	fdivs f3, f1, f0
lbl_80007A34:
/* 80007A34 00004614  C0 41 00 68 */	lfs f2, 0x68(r1)
/* 80007A38 00004618  7F C4 F3 78 */	mr r4, r30
/* 80007A3C 0000461C  C0 3C 00 00 */	lfs f1, 0(r28)
/* 80007A40 00004620  38 61 00 50 */	addi r3, r1, 0x50
/* 80007A44 00004624  C0 1A 00 00 */	lfs f0, 0(r26)
/* 80007A48 00004628  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 80007A4C 0000462C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80007A50 00004630  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 80007A54 00004634  C0 41 00 6C */	lfs f2, 0x6c(r1)
/* 80007A58 00004638  C0 3C 00 04 */	lfs f1, 4(r28)
/* 80007A5C 0000463C  C0 1A 00 04 */	lfs f0, 4(r26)
/* 80007A60 00004640  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 80007A64 00004644  EC 01 00 28 */	fsubs f0, f1, f0
/* 80007A68 00004648  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 80007A6C 0000464C  C0 41 00 70 */	lfs f2, 0x70(r1)
/* 80007A70 00004650  C0 3C 00 08 */	lfs f1, 8(r28)
/* 80007A74 00004654  C0 1A 00 08 */	lfs f0, 8(r26)
/* 80007A78 00004658  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 80007A7C 0000465C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80007A80 00004660  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 80007A84 00004664  48 33 B3 35 */	bl PSVECNormalize
/* 80007A88 00004668  38 7E 00 00 */	addi r3, r30, 0
/* 80007A8C 0000466C  38 81 00 68 */	addi r4, r1, 0x68
/* 80007A90 00004670  48 00 5D 01 */	bl lbvector_AngleXY
/* 80007A94 00004674  D0 3F 00 00 */	stfs f1, 0(r31)
/* 80007A98 00004678  C0 3E 00 00 */	lfs f1, 0(r30)
/* 80007A9C 0000467C  C0 1A 00 00 */	lfs f0, 0(r26)
/* 80007AA0 00004680  EC 1F 00 7A */	fmadds f0, f31, f1, f0
/* 80007AA4 00004684  D0 1D 00 00 */	stfs f0, 0(r29)
/* 80007AA8 00004688  C0 3E 00 04 */	lfs f1, 4(r30)
/* 80007AAC 0000468C  C0 1A 00 04 */	lfs f0, 4(r26)
/* 80007AB0 00004690  EC 1F 00 7A */	fmadds f0, f31, f1, f0
/* 80007AB4 00004694  D0 1D 00 04 */	stfs f0, 4(r29)
/* 80007AB8 00004698  C0 3E 00 08 */	lfs f1, 8(r30)
/* 80007ABC 0000469C  C0 1A 00 08 */	lfs f0, 8(r26)
/* 80007AC0 000046A0  EC 1F 00 7A */	fmadds f0, f31, f1, f0
/* 80007AC4 000046A4  D0 1D 00 08 */	stfs f0, 8(r29)
/* 80007AC8 000046A8  48 00 00 18 */	b lbl_80007AE0
lbl_80007ACC:
/* 80007ACC 000046AC  C0 02 80 50 */	lfs f0, lbl_804D7A30(r2)
/* 80007AD0 000046B0  D0 1F 00 00 */	stfs f0, 0(r31)
/* 80007AD4 000046B4  D0 5E 00 08 */	stfs f2, 8(r30)
/* 80007AD8 000046B8  D0 5E 00 04 */	stfs f2, 4(r30)
/* 80007ADC 000046BC  D0 5E 00 00 */	stfs f2, 0(r30)
lbl_80007AE0:
/* 80007AE0 000046C0  BB 41 00 78 */	lmw r26, 0x78(r1)
/* 80007AE4 000046C4  80 01 00 A4 */	lwz r0, 0xa4(r1)
/* 80007AE8 000046C8  CB E1 00 98 */	lfd f31, 0x98(r1)
/* 80007AEC 000046CC  CB C1 00 90 */	lfd f30, 0x90(r1)
/* 80007AF0 000046D0  38 21 00 A0 */	addi r1, r1, 0xa0
/* 80007AF4 000046D4  7C 08 03 A6 */	mtlr r0
/* 80007AF8 000046D8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

inline f32 sqrDistance(Vec3* a, Vec3* b)
{
    {
        f32 y = a->y - b->y;
        f32 x = a->x - b->x;
        f32 z = a->z - b->z;
        return z * z + x * x + y * y;
    }
}

void lbColl_800077A0(Vec3* a, Mtx arg1, Vec3* b, Vec3* c, Vec3* d, Vec3* e,
                     f32* angle, f32 x, f32 dist_offset)
{
    Vec3 diff_cb;
    f32 diff_cb_x;

    diff_cb.x = diff_cb_x = c->x - b->x;
    diff_cb.y = c->y - b->y;
    diff_cb.z = c->z - b->z;

    if (diff_cb_x != 0.0f || diff_cb.y != 0.0f || diff_cb.z != 0.0f) {
        Vec3 normal_x;
        Vec3 multi_mtx;

        normal_x.x = x;
        normal_x.y = 0.0f;
        normal_x.z = 0.0f;
        PSMTXMUltiVec(arg1, &normal_x, &normal_x);

        multi_mtx.x = 0.0f;
        multi_mtx.y = 0.0f;
        multi_mtx.z = 0.0f;
        PSMTXMUltiVec(arg1, &multi_mtx, &multi_mtx);

        {
            f32 dist = sqrDistance(&normal_x, &multi_mtx);
            dist = sqrtf(dist);

            {
                f32 offset_dist = dist + dist_offset;
                f32 dot_diff_cb = diff_cb.z * diff_cb.z +
                                  diff_cb.x * diff_cb.x +
                                  diff_cb.y * diff_cb.y;

                f32 diff_ba_x = b->x - a->x;
                f32 diff_ba_y = b->y - a->y;
                f32 diff_ba_z = b->z - a->z;

                {
                    f32 scl;

                    if (approximatelyZero(dot_diff_cb)) {
                        scl = 0.0f;
                    } else {
                        f32 n0 = 2.0f * diff_cb.z * diff_ba_z +
                                 2.0f * diff_cb.x * diff_ba_x +
                                 2.0f * diff_cb.y * diff_ba_y;

                        f32 n1 = n0 * n0 - (4.0f * dot_diff_cb *
                                            -(offset_dist * offset_dist -
                                              diff_ba_z * diff_ba_z +
                                              diff_ba_x * diff_ba_x +
                                              diff_ba_y * diff_ba_y));

                        if (n1 < 0.0f)
                            n1 = 0.0f;

                        {
                            f32 n2;
                            if (n1 > 0.0f)
                                n2 = sqrtf(n1);
                            else
                                n2 = n1;

                            scl = (-n0 - n2) / (2.0f * dot_diff_cb);
                        }
                    }

                    {
                        Vec3 normalize_e;
                        normalize_e.x = scl * diff_cb.x + b->x - a->x;
                        normalize_e.y = scl * diff_cb.y + b->y - a->y;
                        normalize_e.z = scl * diff_cb.z + b->z - a->z;
                        PSVECNormalize(&normalize_e, e);
                    }
                }
            }

            *angle = lbvector_AngleXY(e, &diff_cb);
            d->x = dist * e->x + a->x;
            d->y = dist * e->y + a->y;
            d->z = dist * e->z + a->z;
        }
    } else {
        *angle = M_PI;
        e->z = 0.0f;
        e->y = 0.0f;
        e->x = 0.0f;
    }
}
#endif

bool lbColl_80007AFC(HitCapsule* a, HitCapsule* b, f32 x, f32 y)
{
    f32 a_val, b_val;

    if (a->x43_b1)
        a_val = a->scl;
    else
        a_val = a->scl * x;

    if (b->x43_b1)
        b_val = b->scl;
    else
        b_val = b->scl * y;

    return lbColl_80006094(&b->x58, &b->x4C, &a->x58, &a->x4C, &b->x64,
                           &a->x64, b_val, a_val);
}

void lbColl_80007B78(Mtx a, Mtx b, f32 x, f32 y)
{
    /// @todo Eliminate casts.
    lbColl_800067F8((Vec3*) &b[1][1], (Vec3*) &b[0][2], (Vec3*) &a[1][1],
                    (Vec3*) &a[0][2], (Vec3*) &b[1][4], (Vec3*) &a[1][4],
                    b[0][0] * y, a[0][0] * x, x);
}

extern char* lbl_804D3700;
extern char* lbl_804D3708;
f32 const lbl_804D7A34 = 20;

#ifdef MUST_MATCH
#pragma push
asm bool lbColl_80007BCC(HitCapsule*, HitResult* shield_hit, unk_t, s32, f32,
                         f32, f32)
{
    // clang-format off
    nofralloc
/* 80007BCC 000047AC  7C 08 02 A6 */	mflr r0
/* 80007BD0 000047B0  90 01 00 04 */	stw r0, 4(r1)
/* 80007BD4 000047B4  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 80007BD8 000047B8  DB E1 00 A0 */	stfd f31, 0xa0(r1)
/* 80007BDC 000047BC  FF E0 18 90 */	fmr f31, f3
/* 80007BE0 000047C0  DB C1 00 98 */	stfd f30, 0x98(r1)
/* 80007BE4 000047C4  FF C0 10 90 */	fmr f30, f2
/* 80007BE8 000047C8  DB A1 00 90 */	stfd f29, 0x90(r1)
/* 80007BEC 000047CC  FF A0 08 90 */	fmr f29, f1
/* 80007BF0 000047D0  93 E1 00 8C */	stw r31, 0x8c(r1)
/* 80007BF4 000047D4  7C 9F 23 78 */	mr r31, r4
/* 80007BF8 000047D8  93 C1 00 88 */	stw r30, 0x88(r1)
/* 80007BFC 000047DC  3B C3 00 00 */	addi r30, r3, 0
/* 80007C00 000047E0  93 A1 00 84 */	stw r29, 0x84(r1)
/* 80007C04 000047E4  3B A6 00 00 */	addi r29, r6, 0
/* 80007C08 000047E8  93 81 00 80 */	stw r28, 0x80(r1)
/* 80007C0C 000047EC  3B 85 00 00 */	addi r28, r5, 0
/* 80007C10 000047F0  88 04 00 04 */	lbz r0, 4(r4)
/* 80007C14 000047F4  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80007C18 000047F8  40 82 00 30 */	bne lbl_80007C48
/* 80007C1C 000047FC  80 7F 00 00 */	lwz r3, 0(r31)
/* 80007C20 00004800  38 9F 00 14 */	addi r4, r31, 0x14
/* 80007C24 00004804  38 BF 00 08 */	addi r5, r31, 8
/* 80007C28 00004808  48 00 35 A5 */	bl func_8000B1CC
/* 80007C2C 0000480C  28 1C 00 00 */	cmplwi r28, 0
/* 80007C30 00004810  41 82 00 08 */	beq lbl_80007C38
/* 80007C34 00004814  D3 FF 00 10 */	stfs f31, 0x10(r31)
lbl_80007C38:
/* 80007C38 00004818  88 1F 00 04 */	lbz r0, 4(r31)
/* 80007C3C 0000481C  38 60 00 01 */	li r3, 1
/* 80007C40 00004820  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80007C44 00004824  98 1F 00 04 */	stb r0, 4(r31)
lbl_80007C48:
/* 80007C48 00004828  2C 1D 00 00 */	cmpwi r29, 0
/* 80007C4C 0000482C  41 82 00 2C */	beq lbl_80007C78
/* 80007C50 00004830  80 9F 00 08 */	lwz r4, 8(r31)
/* 80007C54 00004834  38 60 00 01 */	li r3, 1
/* 80007C58 00004838  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80007C5C 0000483C  90 9E 00 64 */	stw r4, 0x64(r30)
/* 80007C60 00004840  90 1E 00 68 */	stw r0, 0x68(r30)
/* 80007C64 00004844  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 80007C68 00004848  90 1E 00 6C */	stw r0, 0x6c(r30)
/* 80007C6C 0000484C  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80007C70 00004850  D0 1E 00 70 */	stfs f0, 0x70(r30)
/* 80007C74 00004854  48 00 00 C8 */	b lbl_80007D3C
lbl_80007C78:
/* 80007C78 00004858  28 1C 00 00 */	cmplwi r28, 0
/* 80007C7C 0000485C  41 82 00 38 */	beq lbl_80007CB4
/* 80007C80 00004860  83 BF 00 00 */	lwz r29, 0(r31)
/* 80007C84 00004864  28 1D 00 00 */	cmplwi r29, 0
/* 80007C88 00004868  40 82 00 14 */	bne lbl_80007C9C
/* 80007C8C 0000486C  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80007C90 00004870  38 80 04 78 */	li r4, 0x478
/* 80007C94 00004874  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80007C98 00004878  48 38 05 89 */	bl __assert
lbl_80007C9C:
/* 80007C9C 0000487C  7F A3 EB 78 */	mr r3, r29
/* 80007CA0 00004880  48 00 00 C9 */	bl lbColl_JObjSetupMatrix
/* 80007CA4 00004884  38 9D 00 44 */	addi r4, r29, 0x44
/* 80007CA8 00004888  38 7C 00 00 */	addi r3, r28, 0
/* 80007CAC 0000488C  38 A1 00 38 */	addi r5, r1, 0x38
/* 80007CB0 00004890  48 33 A5 55 */	bl PSMTXConcat
lbl_80007CB4:
/* 80007CB4 00004894  28 1C 00 00 */	cmplwi r28, 0
/* 80007CB8 00004898  41 82 00 0C */	beq lbl_80007CC4
/* 80007CBC 0000489C  39 21 00 38 */	addi r9, r1, 0x38
/* 80007CC0 000048A0  48 00 00 2C */	b lbl_80007CEC
lbl_80007CC4:
/* 80007CC4 000048A4  83 BF 00 00 */	lwz r29, 0(r31)
/* 80007CC8 000048A8  28 1D 00 00 */	cmplwi r29, 0
/* 80007CCC 000048AC  40 82 00 14 */	bne lbl_80007CE0
/* 80007CD0 000048B0  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80007CD4 000048B4  38 80 04 78 */	li r4, 0x478
/* 80007CD8 000048B8  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80007CDC 000048BC  48 38 05 45 */	bl __assert
lbl_80007CE0:
/* 80007CE0 000048C0  7F A3 EB 78 */	mr r3, r29
/* 80007CE4 000048C4  48 00 00 85 */	bl lbColl_JObjSetupMatrix
/* 80007CE8 000048C8  39 3D 00 44 */	addi r9, r29, 0x44
lbl_80007CEC:
/* 80007CEC 000048CC  88 1E 00 43 */	lbz r0, 0x43(r30)
/* 80007CF0 000048D0  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80007CF4 000048D4  41 82 00 0C */	beq lbl_80007D00
/* 80007CF8 000048D8  C0 3E 00 1C */	lfs f1, 0x1c(r30)
/* 80007CFC 000048DC  48 00 00 0C */	b lbl_80007D08
lbl_80007D00:
/* 80007D00 000048E0  C0 1E 00 1C */	lfs f0, 0x1c(r30)
/* 80007D04 000048E4  EC 20 07 72 */	fmuls f1, f0, f29
lbl_80007D08:
/* 80007D08 000048E8  38 1E 00 70 */	addi r0, r30, 0x70
/* 80007D0C 000048EC  90 01 00 08 */	stw r0, 8(r1)
/* 80007D10 000048F0  38 BF 00 08 */	addi r5, r31, 8
/* 80007D14 000048F4  38 C5 00 00 */	addi r6, r5, 0
/* 80007D18 000048F8  C0 02 80 54 */	lfs f0, lbl_804D7A34(r2)
/* 80007D1C 000048FC  38 7E 00 58 */	addi r3, r30, 0x58
/* 80007D20 00004900  C0 5F 00 20 */	lfs f2, 0x20(r31)
/* 80007D24 00004904  38 9E 00 4C */	addi r4, r30, 0x4c
/* 80007D28 00004908  EC 60 07 B2 */	fmuls f3, f0, f30
/* 80007D2C 0000490C  38 E1 00 74 */	addi r7, r1, 0x74
/* 80007D30 00004910  39 01 00 68 */	addi r8, r1, 0x68
/* 80007D34 00004914  39 5E 00 64 */	addi r10, r30, 0x64
/* 80007D38 00004918  4B FF F1 21 */	bl lbColl_80006E58
lbl_80007D3C:
/* 80007D3C 0000491C  80 01 00 AC */	lwz r0, 0xac(r1)
/* 80007D40 00004920  CB E1 00 A0 */	lfd f31, 0xa0(r1)
/* 80007D44 00004924  CB C1 00 98 */	lfd f30, 0x98(r1)
/* 80007D48 00004928  CB A1 00 90 */	lfd f29, 0x90(r1)
/* 80007D4C 0000492C  83 E1 00 8C */	lwz r31, 0x8c(r1)
/* 80007D50 00004930  83 C1 00 88 */	lwz r30, 0x88(r1)
/* 80007D54 00004934  83 A1 00 84 */	lwz r29, 0x84(r1)
/* 80007D58 00004938  83 81 00 80 */	lwz r28, 0x80(r1)
/* 80007D5C 0000493C  38 21 00 A8 */	addi r1, r1, 0xa8
/* 80007D60 00004940  7C 08 03 A6 */	mtlr r0
/* 80007D64 00004944  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool lbColl_80007BCC(HitCapsule* arg0, HitResult* shield_hit, void* arg2,
                     s32 arg3, f32 arg4, f32 arg5, f32 arg6)
{
    Vec3 sp74;
    Vec3 sp68;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r29_2;
    Vec3* temp_r5;
    f32* var_r9;
    f32 var_f1;
    Mtx sp38;

    if (!(((u8) M2C_FIELD(shield_hit, u8*, 4) >> 7U) & 1)) {
        func_8000B1CC(shield_hit->bone, &shield_hit->offset, &shield_hit->pos);
        if (arg2 != NULL) {
            shield_hit->pos.z = arg6;
        }
        M2C_FIELD(shield_hit, u8*, 4) =
            (u8) (M2C_FIELD(shield_hit, u8*, 4) | 0x80);
    }
    if (arg3 != 0) {
        arg0->x64.x = shield_hit->pos.x;
        arg0->x64.y = shield_hit->pos.y;
        arg0->x64.z = shield_hit->pos.z;
        arg0->x70 = 0.0f;
        return 1;
    }
    if (arg2 != NULL) {
        temp_r29 = shield_hit->bone;
        if (temp_r29 == NULL) {
            __assert(lbl_804D3700, 0x478U, lbl_804D3708);
        }
        lbColl_JObjSetupMatrix(temp_r29);
        PSMTXConcat((f32(*)[4]) arg2, (f32(*)[4]) temp_r29->mtx[0], sp38);
    }
    if (arg2 != NULL) {
        var_r9 = sp38[0];
    } else {
        temp_r29_2 = shield_hit->bone;
        if (temp_r29_2 == NULL) {
            __assert(lbl_804D3700, 0x478U, lbl_804D3708);
        }
        lbColl_JObjSetupMatrix(temp_r29_2);
        var_r9 = temp_r29_2->mtx[0];
    }
    if (((u8) arg0->x43 >> 6U) & 1) {
        var_f1 = arg0->scl;
    } else {
        var_f1 = arg0->scl * arg4;
    }

/// @todo Unused assignment.
#ifdef MUST_MATCH
    {
        int* sp8 = &arg0->x70;
    }
#endif

    temp_r5 = &shield_hit->pos;
    return lbColl_80006E58(&arg0->x58, &arg0->x4C, temp_r5, temp_r5, &sp74,
                           &sp68, (f32(*)[4]) var_r9, &arg0->x64, var_f1,
                           shield_hit->size, 20.0f * arg5);
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void lbColl_JObjSetupMatrix(HSD_JObj*)
{ // clang-format off
    nofralloc
/* 80007D68 00004948  7C 08 02 A6 */	mflr r0
/* 80007D6C 0000494C  90 01 00 04 */	stw r0, 4(r1)
/* 80007D70 00004950  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80007D74 00004954  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80007D78 00004958  7C 7F 1B 79 */	or. r31, r3, r3
/* 80007D7C 0000495C  41 82 00 48 */	beq lbl_80007DC4
/* 80007D80 00004960  40 82 00 14 */	bne lbl_80007D94
/* 80007D84 00004964  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80007D88 00004968  38 80 02 34 */	li r4, 0x234
/* 80007D8C 0000496C  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80007D90 00004970  48 38 04 91 */	bl __assert
lbl_80007D94:
/* 80007D94 00004974  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80007D98 00004978  38 60 00 00 */	li r3, 0
/* 80007D9C 0000497C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80007DA0 00004980  40 82 00 10 */	bne lbl_80007DB0
/* 80007DA4 00004984  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80007DA8 00004988  41 82 00 08 */	beq lbl_80007DB0
/* 80007DAC 0000498C  38 60 00 01 */	li r3, 1
lbl_80007DB0:
/* 80007DB0 00004990  2C 03 00 00 */	cmpwi r3, 0
/* 80007DB4 00004994  40 82 00 08 */	bne lbl_80007DBC
/* 80007DB8 00004998  48 00 00 0C */	b lbl_80007DC4
lbl_80007DBC:
/* 80007DBC 0000499C  7F E3 FB 78 */	mr r3, r31
/* 80007DC0 000049A0  48 36 B2 B9 */	bl HSD_JObjSetupMatrixSub
lbl_80007DC4:
/* 80007DC4 000049A4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80007DC8 000049A8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80007DCC 000049AC  38 21 00 18 */	addi r1, r1, 0x18
/* 80007DD0 000049B0  7C 08 03 A6 */	mtlr r0
/* 80007DD4 000049B4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void lbColl_JObjSetupMatrix(HSD_JObj* arg0)
{
    /// @todo Missing branch somehow
    HSD_JObjSetupMatrix(arg0);
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void lbColl_80007DD8(HitCapsule*, HitResult*, Mtx, unk_t, unk_t, f32)
{
    // clang-format off
    nofralloc
/* 80007DD8 000049B8  7C 08 02 A6 */	mflr r0
/* 80007DDC 000049BC  90 01 00 04 */	stw r0, 4(r1)
/* 80007DE0 000049C0  94 21 FF 78 */	stwu r1, -0x88(r1)
/* 80007DE4 000049C4  DB E1 00 80 */	stfd f31, 0x80(r1)
/* 80007DE8 000049C8  FF E0 08 90 */	fmr f31, f1
/* 80007DEC 000049CC  BF 41 00 68 */	stmw r26, 0x68(r1)
/* 80007DF0 000049D0  7C BC 2B 79 */	or. r28, r5, r5
/* 80007DF4 000049D4  3B 43 00 00 */	addi r26, r3, 0
/* 80007DF8 000049D8  3B 64 00 00 */	addi r27, r4, 0
/* 80007DFC 000049DC  3B A6 00 00 */	addi r29, r6, 0
/* 80007E00 000049E0  3B C7 00 00 */	addi r30, r7, 0
/* 80007E04 000049E4  41 82 00 38 */	beq lbl_80007E3C
/* 80007E08 000049E8  83 FB 00 00 */	lwz r31, 0(r27)
/* 80007E0C 000049EC  28 1F 00 00 */	cmplwi r31, 0
/* 80007E10 000049F0  40 82 00 14 */	bne lbl_80007E24
/* 80007E14 000049F4  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80007E18 000049F8  38 80 04 78 */	li r4, 0x478
/* 80007E1C 000049FC  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80007E20 00004A00  48 38 04 01 */	bl __assert
lbl_80007E24:
/* 80007E24 00004A04  7F E3 FB 78 */	mr r3, r31
/* 80007E28 00004A08  4B FF FF 41 */	bl lbColl_JObjSetupMatrix
/* 80007E2C 00004A0C  38 9F 00 44 */	addi r4, r31, 0x44
/* 80007E30 00004A10  38 7C 00 00 */	addi r3, r28, 0
/* 80007E34 00004A14  38 A1 00 2C */	addi r5, r1, 0x2c
/* 80007E38 00004A18  48 33 A3 CD */	bl PSMTXConcat
lbl_80007E3C:
/* 80007E3C 00004A1C  88 1A 00 43 */	lbz r0, 0x43(r26)
/* 80007E40 00004A20  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80007E44 00004A24  41 82 00 0C */	beq lbl_80007E50
/* 80007E48 00004A28  C3 FA 00 1C */	lfs f31, 0x1c(r26)
/* 80007E4C 00004A2C  48 00 00 0C */	b lbl_80007E58
lbl_80007E50:
/* 80007E50 00004A30  C0 1A 00 1C */	lfs f0, 0x1c(r26)
/* 80007E54 00004A34  EF E0 07 F2 */	fmuls f31, f0, f31
lbl_80007E58:
/* 80007E58 00004A38  28 1C 00 00 */	cmplwi r28, 0
/* 80007E5C 00004A3C  41 82 00 0C */	beq lbl_80007E68
/* 80007E60 00004A40  38 81 00 2C */	addi r4, r1, 0x2c
/* 80007E64 00004A44  48 00 00 2C */	b lbl_80007E90
lbl_80007E68:
/* 80007E68 00004A48  83 FB 00 00 */	lwz r31, 0(r27)
/* 80007E6C 00004A4C  28 1F 00 00 */	cmplwi r31, 0
/* 80007E70 00004A50  40 82 00 14 */	bne lbl_80007E84
/* 80007E74 00004A54  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80007E78 00004A58  38 80 04 78 */	li r4, 0x478
/* 80007E7C 00004A5C  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80007E80 00004A60  48 38 03 A1 */	bl __assert
lbl_80007E84:
/* 80007E84 00004A64  7F E3 FB 78 */	mr r3, r31
/* 80007E88 00004A68  4B FF FE E1 */	bl lbColl_JObjSetupMatrix
/* 80007E8C 00004A6C  38 9F 00 44 */	addi r4, r31, 0x44
lbl_80007E90:
/* 80007E90 00004A70  FC 40 F8 90 */	fmr f2, f31
/* 80007E94 00004A74  C0 3B 00 20 */	lfs f1, 0x20(r27)
/* 80007E98 00004A78  39 1D 00 00 */	addi r8, r29, 0
/* 80007E9C 00004A7C  39 3E 00 00 */	addi r9, r30, 0
/* 80007EA0 00004A80  38 7B 00 08 */	addi r3, r27, 8
/* 80007EA4 00004A84  38 BA 00 58 */	addi r5, r26, 0x58
/* 80007EA8 00004A88  38 DA 00 4C */	addi r6, r26, 0x4c
/* 80007EAC 00004A8C  38 E1 00 5C */	addi r7, r1, 0x5c
/* 80007EB0 00004A90  4B FF F8 F1 */	bl lbColl_800077A0
/* 80007EB4 00004A94  BB 41 00 68 */	lmw r26, 0x68(r1)
/* 80007EB8 00004A98  80 01 00 8C */	lwz r0, 0x8c(r1)
/* 80007EBC 00004A9C  CB E1 00 80 */	lfd f31, 0x80(r1)
/* 80007EC0 00004AA0  38 21 00 88 */	addi r1, r1, 0x88
/* 80007EC4 00004AA4  7C 08 03 A6 */	mtlr r0
/* 80007EC8 00004AA8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void lbColl_80007DD8(HitCapsule* arg0, HitResult* arg1, Mtx arg2, unk_t arg3,
                     unk_t arg4, f32 arg5)
{
    unk_t sp5C = NULL;
    HSD_JObj* temp_r31;
    HSD_JObj* temp_r31_2;
    Mtx* var_r4;
    f32 var_f31;
    Mtx sp2C;

    if (arg2 != NULL) {
        temp_r31 = arg1->bone;
        if (temp_r31 == NULL) {
            __assert(lbl_804D3700, 0x478U, lbl_804D3708);
        }
        lbColl_JObjSetupMatrix(temp_r31);
        PSMTXConcat(arg2, (f32(*)[4]) temp_r31->mtx[0], (f32(*)[4]) & sp2C[0]);
    }
    if (((u8) arg0->x43 >> 6U) & 1) {
        var_f31 = arg0->scl;
    } else {
        var_f31 = arg0->scl * arg5;
    }
    if (arg2 != NULL) {
        var_r4 = &sp2C;
    } else {
        temp_r31_2 = arg1->bone;
        if (temp_r31_2 == NULL) {
            __assert(lbl_804D3700, 0x478U, lbl_804D3708);
        }
        lbColl_JObjSetupMatrix(temp_r31_2);
        var_r4 = &temp_r31_2->mtx;
    }
    lbColl_800077A0(&arg1->pos, *var_r4, &arg0->x58, &arg0->x4C, sp5C, arg3,
                    arg4, arg1->size, var_f31);
}
#endif

f32 const lbl_804D7A38 = 3;

#ifdef MUST_MATCH
#pragma push
asm bool lbColl_80007ECC(HitCapsule*, HurtCapsule*, Mtx, f32 hit_scl_y,
                         f32 hurt_scl_y, f32 hurt_pos_z)
{
    // clang-format off
    nofralloc
/* 80007ECC 00004AAC  7C 08 02 A6 */	mflr r0
/* 80007ED0 00004AB0  90 01 00 04 */	stw r0, 4(r1)
/* 80007ED4 00004AB4  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 80007ED8 00004AB8  DB E1 00 A0 */	stfd f31, 0xa0(r1)
/* 80007EDC 00004ABC  FF E0 18 90 */	fmr f31, f3
/* 80007EE0 00004AC0  DB C1 00 98 */	stfd f30, 0x98(r1)
/* 80007EE4 00004AC4  FF C0 10 90 */	fmr f30, f2
/* 80007EE8 00004AC8  DB A1 00 90 */	stfd f29, 0x90(r1)
/* 80007EEC 00004ACC  FF A0 08 90 */	fmr f29, f1
/* 80007EF0 00004AD0  93 E1 00 8C */	stw r31, 0x8c(r1)
/* 80007EF4 00004AD4  93 C1 00 88 */	stw r30, 0x88(r1)
/* 80007EF8 00004AD8  3B C5 00 00 */	addi r30, r5, 0
/* 80007EFC 00004ADC  93 A1 00 84 */	stw r29, 0x84(r1)
/* 80007F00 00004AE0  7C 9D 23 78 */	mr r29, r4
/* 80007F04 00004AE4  93 81 00 80 */	stw r28, 0x80(r1)
/* 80007F08 00004AE8  3B 83 00 00 */	addi r28, r3, 0
/* 80007F0C 00004AEC  80 04 00 00 */	lwz r0, 0(r4)
/* 80007F10 00004AF0  2C 00 00 00 */	cmpwi r0, 0
/* 80007F14 00004AF4  40 82 01 18 */	bne lbl_8000802C
/* 80007F18 00004AF8  88 1D 00 24 */	lbz r0, 0x24(r29)
/* 80007F1C 00004AFC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80007F20 00004B00  40 82 00 44 */	bne lbl_80007F64
/* 80007F24 00004B04  80 7D 00 20 */	lwz r3, 0x20(r29)
/* 80007F28 00004B08  38 9D 00 04 */	addi r4, r29, 4
/* 80007F2C 00004B0C  38 BD 00 28 */	addi r5, r29, 0x28
/* 80007F30 00004B10  48 00 32 9D */	bl func_8000B1CC
/* 80007F34 00004B14  80 7D 00 20 */	lwz r3, 0x20(r29)
/* 80007F38 00004B18  38 9D 00 10 */	addi r4, r29, 0x10
/* 80007F3C 00004B1C  38 BD 00 34 */	addi r5, r29, 0x34
/* 80007F40 00004B20  48 00 32 8D */	bl func_8000B1CC
/* 80007F44 00004B24  28 1E 00 00 */	cmplwi r30, 0
/* 80007F48 00004B28  41 82 00 0C */	beq lbl_80007F54
/* 80007F4C 00004B2C  D3 FD 00 3C */	stfs f31, 0x3c(r29)
/* 80007F50 00004B30  D3 FD 00 30 */	stfs f31, 0x30(r29)
lbl_80007F54:
/* 80007F54 00004B34  88 1D 00 24 */	lbz r0, 0x24(r29)
/* 80007F58 00004B38  38 60 00 01 */	li r3, 1
/* 80007F5C 00004B3C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80007F60 00004B40  98 1D 00 24 */	stb r0, 0x24(r29)
lbl_80007F64:
/* 80007F64 00004B44  28 1E 00 00 */	cmplwi r30, 0
/* 80007F68 00004B48  41 82 00 38 */	beq lbl_80007FA0
/* 80007F6C 00004B4C  83 FD 00 20 */	lwz r31, 0x20(r29)
/* 80007F70 00004B50  28 1F 00 00 */	cmplwi r31, 0
/* 80007F74 00004B54  40 82 00 14 */	bne lbl_80007F88
/* 80007F78 00004B58  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80007F7C 00004B5C  38 80 04 78 */	li r4, 0x478
/* 80007F80 00004B60  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80007F84 00004B64  48 38 02 9D */	bl __assert
lbl_80007F88:
/* 80007F88 00004B68  7F E3 FB 78 */	mr r3, r31
/* 80007F8C 00004B6C  4B FF FD DD */	bl lbColl_JObjSetupMatrix
/* 80007F90 00004B70  38 9F 00 44 */	addi r4, r31, 0x44
/* 80007F94 00004B74  38 7E 00 00 */	addi r3, r30, 0
/* 80007F98 00004B78  38 A1 00 34 */	addi r5, r1, 0x34
/* 80007F9C 00004B7C  48 33 A2 69 */	bl PSMTXConcat
lbl_80007FA0:
/* 80007FA0 00004B80  28 1E 00 00 */	cmplwi r30, 0
/* 80007FA4 00004B84  41 82 00 0C */	beq lbl_80007FB0
/* 80007FA8 00004B88  39 21 00 34 */	addi r9, r1, 0x34
/* 80007FAC 00004B8C  48 00 00 2C */	b lbl_80007FD8
lbl_80007FB0:
/* 80007FB0 00004B90  83 FD 00 20 */	lwz r31, 0x20(r29)
/* 80007FB4 00004B94  28 1F 00 00 */	cmplwi r31, 0
/* 80007FB8 00004B98  40 82 00 14 */	bne lbl_80007FCC
/* 80007FBC 00004B9C  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80007FC0 00004BA0  38 80 04 78 */	li r4, 0x478
/* 80007FC4 00004BA4  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80007FC8 00004BA8  48 38 02 59 */	bl __assert
lbl_80007FCC:
/* 80007FCC 00004BAC  7F E3 FB 78 */	mr r3, r31
/* 80007FD0 00004BB0  4B FF FD 99 */	bl lbColl_JObjSetupMatrix
/* 80007FD4 00004BB4  39 3F 00 44 */	addi r9, r31, 0x44
lbl_80007FD8:
/* 80007FD8 00004BB8  88 1C 00 43 */	lbz r0, 0x43(r28)
/* 80007FDC 00004BBC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80007FE0 00004BC0  41 82 00 0C */	beq lbl_80007FEC
/* 80007FE4 00004BC4  C0 3C 00 1C */	lfs f1, 0x1c(r28)
/* 80007FE8 00004BC8  48 00 00 0C */	b lbl_80007FF4
lbl_80007FEC:
/* 80007FEC 00004BCC  C0 1C 00 1C */	lfs f0, 0x1c(r28)
/* 80007FF0 00004BD0  EC 20 07 72 */	fmuls f1, f0, f29
lbl_80007FF4:
/* 80007FF4 00004BD4  38 1C 00 70 */	addi r0, r28, 0x70
/* 80007FF8 00004BD8  90 01 00 08 */	stw r0, 8(r1)
/* 80007FFC 00004BDC  38 7C 00 58 */	addi r3, r28, 0x58
/* 80008000 00004BE0  38 9C 00 4C */	addi r4, r28, 0x4c
/* 80008004 00004BE4  C0 02 80 58 */	lfs f0, lbl_804D7A38(r2)
/* 80008008 00004BE8  38 BD 00 28 */	addi r5, r29, 0x28
/* 8000800C 00004BEC  C0 5D 00 1C */	lfs f2, 0x1c(r29)
/* 80008010 00004BF0  38 DD 00 34 */	addi r6, r29, 0x34
/* 80008014 00004BF4  EC 60 07 B2 */	fmuls f3, f0, f30
/* 80008018 00004BF8  38 E1 00 70 */	addi r7, r1, 0x70
/* 8000801C 00004BFC  39 01 00 64 */	addi r8, r1, 0x64
/* 80008020 00004C00  39 5C 00 64 */	addi r10, r28, 0x64
/* 80008024 00004C04  4B FF EE 35 */	bl lbColl_80006E58
/* 80008028 00004C08  48 00 00 08 */	b lbl_80008030
lbl_8000802C:
/* 8000802C 00004C0C  38 60 00 00 */	li r3, 0
lbl_80008030:
/* 80008030 00004C10  80 01 00 AC */	lwz r0, 0xac(r1)
/* 80008034 00004C14  CB E1 00 A0 */	lfd f31, 0xa0(r1)
/* 80008038 00004C18  CB C1 00 98 */	lfd f30, 0x98(r1)
/* 8000803C 00004C1C  CB A1 00 90 */	lfd f29, 0x90(r1)
/* 80008040 00004C20  83 E1 00 8C */	lwz r31, 0x8c(r1)
/* 80008044 00004C24  83 C1 00 88 */	lwz r30, 0x88(r1)
/* 80008048 00004C28  83 A1 00 84 */	lwz r29, 0x84(r1)
/* 8000804C 00004C2C  83 81 00 80 */	lwz r28, 0x80(r1)
/* 80008050 00004C30  38 21 00 A8 */	addi r1, r1, 0xa8
/* 80008054 00004C34  7C 08 03 A6 */	mtlr r0
/* 80008058 00004C38  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool lbColl_80007ECC(HitCapsule* arg0, HurtCapsule* arg1, Mtx arg2,
                     f32 hit_scl_y, f32 hurt_scl_y, f32 hurt_pos_z)
{
    Vec3 sp70;
    Vec3 sp64;
    HSD_JObj* temp_r31;
    HSD_JObj* temp_r31_2;
    Mtx* var_r9;
    f32 var_f1;
    Mtx sp34;

    if ((enum Tangibility) arg1->tangibility == Vulnerable) {
        if (!(((u8) M2C_FIELD(arg1, u8*, 0x24) >> 7U) & 1)) {
            func_8000B1CC(arg1->bone, &arg1->a_offset, &arg1->a_pos);
            func_8000B1CC(arg1->bone, &arg1->b_offset, &arg1->b_pos);
            if (arg2 != NULL) {
                arg1->b_pos.z = hurt_pos_z;
                arg1->a_pos.z = hurt_pos_z;
            }
            M2C_FIELD(arg1, u8*, 0x24) =
                (u8) (M2C_FIELD(arg1, u8*, 0x24) | 0x80);
        }
        if (arg2 != NULL) {
            temp_r31 = arg1->bone;
            if (temp_r31 == NULL) {
                __assert(lbl_804D3700, 0x478U, lbl_804D3708);
            }
            lbColl_JObjSetupMatrix(temp_r31);
            PSMTXConcat(arg2, (f32(*)[4]) temp_r31->mtx[0], sp34);
        }
        if (arg2 != NULL) {
            var_r9 = &sp34;
        } else {
            temp_r31_2 = arg1->bone;
            if (temp_r31_2 == NULL) {
                __assert(lbl_804D3700, 0x478U, lbl_804D3708);
            }
            lbColl_JObjSetupMatrix(temp_r31_2);
            var_r9 = &temp_r31_2->mtx;
        }
        if (((u8) arg0->x43 >> 6U) & 1) {
            var_f1 = arg0->scl;
        } else {
            var_f1 = arg0->scl * hit_scl_y;
        }
/// @todo Unused assignment.
#ifdef MUST_MATCH
        {
            int* sp8 = &arg0->x70;
        }
#endif
        return lbColl_80006E58(&arg0->x58, &arg0->x4C, &arg1->a_pos,
                               &arg1->b_pos, &sp70, &sp64, *var_r9, &arg0->x64,
                               var_f1, arg1->scl, 3.0f * hurt_scl_y);
    }
    return 0;
}
#endif

f32 const lbl_804D7A3C = 0.5;
f32 const lbl_804D7A40 = 5;

#ifdef MWERKS_GEKKO
#pragma push
asm bool lbColl_8000805C(HitCapsule*, HurtCapsule*, unk_t, s32, f32, f32, f32)
{
    // clang-format off
    nofralloc
/* 8000805C 00004C3C  7C 08 02 A6 */	mflr r0
/* 80008060 00004C40  90 01 00 04 */	stw r0, 4(r1)
/* 80008064 00004C44  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 80008068 00004C48  DB E1 00 A0 */	stfd f31, 0xa0(r1)
/* 8000806C 00004C4C  FF E0 18 90 */	fmr f31, f3
/* 80008070 00004C50  DB C1 00 98 */	stfd f30, 0x98(r1)
/* 80008074 00004C54  FF C0 10 90 */	fmr f30, f2
/* 80008078 00004C58  DB A1 00 90 */	stfd f29, 0x90(r1)
/* 8000807C 00004C5C  FF A0 08 90 */	fmr f29, f1
/* 80008080 00004C60  93 E1 00 8C */	stw r31, 0x8c(r1)
/* 80008084 00004C64  7C 9F 23 78 */	mr r31, r4
/* 80008088 00004C68  93 C1 00 88 */	stw r30, 0x88(r1)
/* 8000808C 00004C6C  3B C3 00 00 */	addi r30, r3, 0
/* 80008090 00004C70  93 A1 00 84 */	stw r29, 0x84(r1)
/* 80008094 00004C74  3B A6 00 00 */	addi r29, r6, 0
/* 80008098 00004C78  93 81 00 80 */	stw r28, 0x80(r1)
/* 8000809C 00004C7C  3B 85 00 00 */	addi r28, r5, 0
/* 800080A0 00004C80  80 04 00 00 */	lwz r0, 0(r4)
/* 800080A4 00004C84  2C 00 00 02 */	cmpwi r0, 2
/* 800080A8 00004C88  41 82 01 70 */	beq lbl_80008218
/* 800080AC 00004C8C  88 1F 00 24 */	lbz r0, 0x24(r31)
/* 800080B0 00004C90  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800080B4 00004C94  40 82 00 44 */	bne lbl_800080F8
/* 800080B8 00004C98  80 7F 00 20 */	lwz r3, 0x20(r31)
/* 800080BC 00004C9C  38 9F 00 04 */	addi r4, r31, 4
/* 800080C0 00004CA0  38 BF 00 28 */	addi r5, r31, 0x28
/* 800080C4 00004CA4  48 00 31 09 */	bl func_8000B1CC
/* 800080C8 00004CA8  80 7F 00 20 */	lwz r3, 0x20(r31)
/* 800080CC 00004CAC  38 9F 00 10 */	addi r4, r31, 0x10
/* 800080D0 00004CB0  38 BF 00 34 */	addi r5, r31, 0x34
/* 800080D4 00004CB4  48 00 30 F9 */	bl func_8000B1CC
/* 800080D8 00004CB8  28 1C 00 00 */	cmplwi r28, 0
/* 800080DC 00004CBC  41 82 00 0C */	beq lbl_800080E8
/* 800080E0 00004CC0  D3 FF 00 3C */	stfs f31, 0x3c(r31)
/* 800080E4 00004CC4  D3 FF 00 30 */	stfs f31, 0x30(r31)
lbl_800080E8:
/* 800080E8 00004CC8  88 1F 00 24 */	lbz r0, 0x24(r31)
/* 800080EC 00004CCC  38 60 00 01 */	li r3, 1
/* 800080F0 00004CD0  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 800080F4 00004CD4  98 1F 00 24 */	stb r0, 0x24(r31)
lbl_800080F8:
/* 800080F8 00004CD8  2C 1D 00 00 */	cmpwi r29, 0
/* 800080FC 00004CDC  41 82 00 54 */	beq lbl_80008150
/* 80008100 00004CE0  C0 3F 00 28 */	lfs f1, 0x28(r31)
/* 80008104 00004CE4  38 60 00 01 */	li r3, 1
/* 80008108 00004CE8  C0 1F 00 34 */	lfs f0, 0x34(r31)
/* 8000810C 00004CEC  C0 42 80 5C */	lfs f2, lbl_804D7A3C(r2)
/* 80008110 00004CF0  EC 01 00 2A */	fadds f0, f1, f0
/* 80008114 00004CF4  EC 02 00 32 */	fmuls f0, f2, f0
/* 80008118 00004CF8  D0 1E 00 64 */	stfs f0, 0x64(r30)
/* 8000811C 00004CFC  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 80008120 00004D00  C0 1F 00 38 */	lfs f0, 0x38(r31)
/* 80008124 00004D04  EC 01 00 2A */	fadds f0, f1, f0
/* 80008128 00004D08  EC 02 00 32 */	fmuls f0, f2, f0
/* 8000812C 00004D0C  D0 1E 00 68 */	stfs f0, 0x68(r30)
/* 80008130 00004D10  C0 3F 00 30 */	lfs f1, 0x30(r31)
/* 80008134 00004D14  C0 1F 00 3C */	lfs f0, 0x3c(r31)
/* 80008138 00004D18  EC 01 00 2A */	fadds f0, f1, f0
/* 8000813C 00004D1C  EC 02 00 32 */	fmuls f0, f2, f0
/* 80008140 00004D20  D0 1E 00 6C */	stfs f0, 0x6c(r30)
/* 80008144 00004D24  C0 02 80 60 */	lfs f0, lbl_804D7A40(r2)
/* 80008148 00004D28  D0 1E 00 70 */	stfs f0, 0x70(r30)
/* 8000814C 00004D2C  48 00 00 D0 */	b lbl_8000821C
lbl_80008150:
/* 80008150 00004D30  28 1C 00 00 */	cmplwi r28, 0
/* 80008154 00004D34  41 82 00 38 */	beq lbl_8000818C
/* 80008158 00004D38  83 BF 00 20 */	lwz r29, 0x20(r31)
/* 8000815C 00004D3C  28 1D 00 00 */	cmplwi r29, 0
/* 80008160 00004D40  40 82 00 14 */	bne lbl_80008174
/* 80008164 00004D44  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80008168 00004D48  38 80 04 78 */	li r4, 0x478
/* 8000816C 00004D4C  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80008170 00004D50  48 38 00 B1 */	bl __assert
lbl_80008174:
/* 80008174 00004D54  7F A3 EB 78 */	mr r3, r29
/* 80008178 00004D58  4B FF FB F1 */	bl lbColl_JObjSetupMatrix
/* 8000817C 00004D5C  38 9D 00 44 */	addi r4, r29, 0x44
/* 80008180 00004D60  38 7C 00 00 */	addi r3, r28, 0
/* 80008184 00004D64  38 A1 00 38 */	addi r5, r1, 0x38
/* 80008188 00004D68  48 33 A0 7D */	bl PSMTXConcat
lbl_8000818C:
/* 8000818C 00004D6C  28 1C 00 00 */	cmplwi r28, 0
/* 80008190 00004D70  41 82 00 0C */	beq lbl_8000819C
/* 80008194 00004D74  39 21 00 38 */	addi r9, r1, 0x38
/* 80008198 00004D78  48 00 00 2C */	b lbl_800081C4
lbl_8000819C:
/* 8000819C 00004D7C  83 BF 00 20 */	lwz r29, 0x20(r31)
/* 800081A0 00004D80  28 1D 00 00 */	cmplwi r29, 0
/* 800081A4 00004D84  40 82 00 14 */	bne lbl_800081B8
/* 800081A8 00004D88  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 800081AC 00004D8C  38 80 04 78 */	li r4, 0x478
/* 800081B0 00004D90  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 800081B4 00004D94  48 38 00 6D */	bl __assert
lbl_800081B8:
/* 800081B8 00004D98  7F A3 EB 78 */	mr r3, r29
/* 800081BC 00004D9C  4B FF FB AD */	bl lbColl_JObjSetupMatrix
/* 800081C0 00004DA0  39 3D 00 44 */	addi r9, r29, 0x44
lbl_800081C4:
/* 800081C4 00004DA4  88 1E 00 43 */	lbz r0, 0x43(r30)
/* 800081C8 00004DA8  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 800081CC 00004DAC  41 82 00 0C */	beq lbl_800081D8
/* 800081D0 00004DB0  C0 3E 00 1C */	lfs f1, 0x1c(r30)
/* 800081D4 00004DB4  48 00 00 0C */	b lbl_800081E0
lbl_800081D8:
/* 800081D8 00004DB8  C0 1E 00 1C */	lfs f0, 0x1c(r30)
/* 800081DC 00004DBC  EC 20 07 72 */	fmuls f1, f0, f29
lbl_800081E0:
/* 800081E0 00004DC0  38 1E 00 70 */	addi r0, r30, 0x70
/* 800081E4 00004DC4  90 01 00 08 */	stw r0, 8(r1)
/* 800081E8 00004DC8  38 7E 00 58 */	addi r3, r30, 0x58
/* 800081EC 00004DCC  38 9E 00 4C */	addi r4, r30, 0x4c
/* 800081F0 00004DD0  C0 02 80 58 */	lfs f0, lbl_804D7A38(r2)
/* 800081F4 00004DD4  38 BF 00 28 */	addi r5, r31, 0x28
/* 800081F8 00004DD8  C0 5F 00 1C */	lfs f2, 0x1c(r31)
/* 800081FC 00004DDC  38 DF 00 34 */	addi r6, r31, 0x34
/* 80008200 00004DE0  EC 60 07 B2 */	fmuls f3, f0, f30
/* 80008204 00004DE4  38 E1 00 74 */	addi r7, r1, 0x74
/* 80008208 00004DE8  39 01 00 68 */	addi r8, r1, 0x68
/* 8000820C 00004DEC  39 5E 00 64 */	addi r10, r30, 0x64
/* 80008210 00004DF0  4B FF EC 49 */	bl lbColl_80006E58
/* 80008214 00004DF4  48 00 00 08 */	b lbl_8000821C
lbl_80008218:
/* 80008218 00004DF8  38 60 00 00 */	li r3, 0
lbl_8000821C:
/* 8000821C 00004DFC  80 01 00 AC */	lwz r0, 0xac(r1)
/* 80008220 00004E00  CB E1 00 A0 */	lfd f31, 0xa0(r1)
/* 80008224 00004E04  CB C1 00 98 */	lfd f30, 0x98(r1)
/* 80008228 00004E08  CB A1 00 90 */	lfd f29, 0x90(r1)
/* 8000822C 00004E0C  83 E1 00 8C */	lwz r31, 0x8c(r1)
/* 80008230 00004E10  83 C1 00 88 */	lwz r30, 0x88(r1)
/* 80008234 00004E14  83 A1 00 84 */	lwz r29, 0x84(r1)
/* 80008238 00004E18  83 81 00 80 */	lwz r28, 0x80(r1)
/* 8000823C 00004E1C  38 21 00 A8 */	addi r1, r1, 0xa8
/* 80008240 00004E20  7C 08 03 A6 */	mtlr r0
/* 80008244 00004E24  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool lbColl_8000805C(HitCapsule* arg0, HurtCapsule* arg1, UNK_T arg2, s32 arg3,
                     f32 arg4, f32 arg5, f32 arg6)
{
    Vec3 sp74;
    Vec3 sp68;
    f32* sp38 = NULL;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r29_2;
    f32* var_r9;
    f32 var_f1;

    if ((enum Tangibility) arg1->tangibility != Intangible) {
        if (!(((u8) M2C_FIELD(arg1, u8*, 0x24) >> 7U) & 1)) {
            func_8000B1CC(arg1->bone, &arg1->a_offset, &arg1->a_pos);
            func_8000B1CC(arg1->bone, &arg1->b_offset, &arg1->b_pos);
            if (arg2 != NULL) {
                arg1->b_pos.z = arg6;
                arg1->a_pos.z = arg6;
            }
            M2C_FIELD(arg1, u8*, 0x24) =
                (u8) (M2C_FIELD(arg1, u8*, 0x24) | 0x80);
        }
        if (arg3 != 0) {
            arg0->x64.x = 0.5f * (arg1->a_pos.x + arg1->b_pos.x);
            arg0->x64.y = 0.5f * (arg1->a_pos.y + arg1->b_pos.y);
            arg0->x64.z = 0.5f * (arg1->a_pos.z + arg1->b_pos.z);
            arg0->x70 = 5.0f;
            return 1;
        }
        if (arg2 != NULL) {
            temp_r29 = arg1->bone;
            if (temp_r29 == NULL) {
                __assert(lbl_804D3700, 0x478U, lbl_804D3708);
            }
            lbColl_JObjSetupMatrix(temp_r29);
            PSMTXConcat((f32(*)[4]) arg2, (f32(*)[4]) temp_r29->mtx[0],
                        (f32(*)[4]) & sp38[0]);
        }
        if (arg2 != NULL) {
            var_r9 = &sp38[0];
        } else {
            temp_r29_2 = arg1->bone;
            if (temp_r29_2 == NULL) {
                __assert(lbl_804D3700, 0x478U, lbl_804D3708);
            }
            lbColl_JObjSetupMatrix(temp_r29_2);
            var_r9 = temp_r29_2->mtx[0];
        }
        if (((u8) arg0->x43 >> 6U) & 1) {
            var_f1 = arg0->scl;
        } else {
            var_f1 = arg0->scl * arg4;
        }
/// @todo Unused assignment.
#ifdef MUST_MATCH
        {
            int* sp8 = &arg0->x70;
        }
#endif
        return lbColl_80006E58(&arg0->x58, &arg0->x4C, &arg1->a_pos,
                               &arg1->b_pos, &sp74, &sp68, (f32(*)[4]) var_r9,
                               &arg0->x64, var_f1, arg1->scl, 3.0f * arg5);
    }
    return 0;
}
#endif

#ifdef MUST_MATCH
#pragma push
asm bool lbColl_80008248(HitCapsule*, HurtCapsule*, Mtx, f32, f32, f32)
{ // clang-format off
    nofralloc
/* 80008248 00004E28  7C 08 02 A6 */	mflr r0
/* 8000824C 00004E2C  90 01 00 04 */	stw r0, 4(r1)
/* 80008250 00004E30  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 80008254 00004E34  DB E1 00 A0 */	stfd f31, 0xa0(r1)
/* 80008258 00004E38  FF E0 18 90 */	fmr f31, f3
/* 8000825C 00004E3C  DB C1 00 98 */	stfd f30, 0x98(r1)
/* 80008260 00004E40  FF C0 10 90 */	fmr f30, f2
/* 80008264 00004E44  DB A1 00 90 */	stfd f29, 0x90(r1)
/* 80008268 00004E48  FF A0 08 90 */	fmr f29, f1
/* 8000826C 00004E4C  93 E1 00 8C */	stw r31, 0x8c(r1)
/* 80008270 00004E50  93 C1 00 88 */	stw r30, 0x88(r1)
/* 80008274 00004E54  3B C5 00 00 */	addi r30, r5, 0
/* 80008278 00004E58  93 A1 00 84 */	stw r29, 0x84(r1)
/* 8000827C 00004E5C  7C 9D 23 78 */	mr r29, r4
/* 80008280 00004E60  93 81 00 80 */	stw r28, 0x80(r1)
/* 80008284 00004E64  3B 83 00 00 */	addi r28, r3, 0
/* 80008288 00004E68  88 04 00 24 */	lbz r0, 0x24(r4)
/* 8000828C 00004E6C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80008290 00004E70  40 82 00 44 */	bne lbl_800082D4
/* 80008294 00004E74  80 7D 00 20 */	lwz r3, 0x20(r29)
/* 80008298 00004E78  38 9D 00 04 */	addi r4, r29, 4
/* 8000829C 00004E7C  38 BD 00 28 */	addi r5, r29, 0x28
/* 800082A0 00004E80  48 00 2F 2D */	bl func_8000B1CC
/* 800082A4 00004E84  80 7D 00 20 */	lwz r3, 0x20(r29)
/* 800082A8 00004E88  38 9D 00 10 */	addi r4, r29, 0x10
/* 800082AC 00004E8C  38 BD 00 34 */	addi r5, r29, 0x34
/* 800082B0 00004E90  48 00 2F 1D */	bl func_8000B1CC
/* 800082B4 00004E94  28 1E 00 00 */	cmplwi r30, 0
/* 800082B8 00004E98  41 82 00 0C */	beq lbl_800082C4
/* 800082BC 00004E9C  D3 FD 00 3C */	stfs f31, 0x3c(r29)
/* 800082C0 00004EA0  D3 FD 00 30 */	stfs f31, 0x30(r29)
lbl_800082C4:
/* 800082C4 00004EA4  88 1D 00 24 */	lbz r0, 0x24(r29)
/* 800082C8 00004EA8  38 60 00 01 */	li r3, 1
/* 800082CC 00004EAC  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 800082D0 00004EB0  98 1D 00 24 */	stb r0, 0x24(r29)
lbl_800082D4:
/* 800082D4 00004EB4  28 1E 00 00 */	cmplwi r30, 0
/* 800082D8 00004EB8  41 82 00 38 */	beq lbl_80008310
/* 800082DC 00004EBC  83 FD 00 20 */	lwz r31, 0x20(r29)
/* 800082E0 00004EC0  28 1F 00 00 */	cmplwi r31, 0
/* 800082E4 00004EC4  40 82 00 14 */	bne lbl_800082F8
/* 800082E8 00004EC8  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 800082EC 00004ECC  38 80 04 78 */	li r4, 0x478
/* 800082F0 00004ED0  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 800082F4 00004ED4  48 37 FF 2D */	bl __assert
lbl_800082F8:
/* 800082F8 00004ED8  7F E3 FB 78 */	mr r3, r31
/* 800082FC 00004EDC  4B FF FA 6D */	bl lbColl_JObjSetupMatrix
/* 80008300 00004EE0  38 9F 00 44 */	addi r4, r31, 0x44
/* 80008304 00004EE4  38 7E 00 00 */	addi r3, r30, 0
/* 80008308 00004EE8  38 A1 00 34 */	addi r5, r1, 0x34
/* 8000830C 00004EEC  48 33 9E F9 */	bl PSMTXConcat
lbl_80008310:
/* 80008310 00004EF0  28 1E 00 00 */	cmplwi r30, 0
/* 80008314 00004EF4  41 82 00 0C */	beq lbl_80008320
/* 80008318 00004EF8  39 21 00 34 */	addi r9, r1, 0x34
/* 8000831C 00004EFC  48 00 00 2C */	b lbl_80008348
lbl_80008320:
/* 80008320 00004F00  83 FD 00 20 */	lwz r31, 0x20(r29)
/* 80008324 00004F04  28 1F 00 00 */	cmplwi r31, 0
/* 80008328 00004F08  40 82 00 14 */	bne lbl_8000833C
/* 8000832C 00004F0C  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 80008330 00004F10  38 80 04 78 */	li r4, 0x478
/* 80008334 00004F14  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 80008338 00004F18  48 37 FE E9 */	bl __assert
lbl_8000833C:
/* 8000833C 00004F1C  7F E3 FB 78 */	mr r3, r31
/* 80008340 00004F20  4B FF FA 29 */	bl lbColl_JObjSetupMatrix
/* 80008344 00004F24  39 3F 00 44 */	addi r9, r31, 0x44
lbl_80008348:
/* 80008348 00004F28  88 1C 00 43 */	lbz r0, 0x43(r28)
/* 8000834C 00004F2C  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80008350 00004F30  41 82 00 0C */	beq lbl_8000835C
/* 80008354 00004F34  C0 3C 00 1C */	lfs f1, 0x1c(r28)
/* 80008358 00004F38  48 00 00 0C */	b lbl_80008364
lbl_8000835C:
/* 8000835C 00004F3C  C0 1C 00 1C */	lfs f0, 0x1c(r28)
/* 80008360 00004F40  EC 20 07 72 */	fmuls f1, f0, f29
lbl_80008364:
/* 80008364 00004F44  38 1C 00 70 */	addi r0, r28, 0x70
/* 80008368 00004F48  90 01 00 08 */	stw r0, 8(r1)
/* 8000836C 00004F4C  38 7C 00 58 */	addi r3, r28, 0x58
/* 80008370 00004F50  38 9C 00 4C */	addi r4, r28, 0x4c
/* 80008374 00004F54  C0 02 80 58 */	lfs f0, lbl_804D7A38(r2)
/* 80008378 00004F58  38 BD 00 28 */	addi r5, r29, 0x28
/* 8000837C 00004F5C  C0 5D 00 1C */	lfs f2, 0x1c(r29)
/* 80008380 00004F60  38 DD 00 34 */	addi r6, r29, 0x34
/* 80008384 00004F64  EC 60 07 B2 */	fmuls f3, f0, f30
/* 80008388 00004F68  38 E1 00 70 */	addi r7, r1, 0x70
/* 8000838C 00004F6C  39 01 00 64 */	addi r8, r1, 0x64
/* 80008390 00004F70  39 5C 00 64 */	addi r10, r28, 0x64
/* 80008394 00004F74  4B FF EA C5 */	bl lbColl_80006E58
/* 80008398 00004F78  80 01 00 AC */	lwz r0, 0xac(r1)
/* 8000839C 00004F7C  CB E1 00 A0 */	lfd f31, 0xa0(r1)
/* 800083A0 00004F80  CB C1 00 98 */	lfd f30, 0x98(r1)
/* 800083A4 00004F84  CB A1 00 90 */	lfd f29, 0x90(r1)
/* 800083A8 00004F88  83 E1 00 8C */	lwz r31, 0x8c(r1)
/* 800083AC 00004F8C  83 C1 00 88 */	lwz r30, 0x88(r1)
/* 800083B0 00004F90  83 A1 00 84 */	lwz r29, 0x84(r1)
/* 800083B4 00004F94  83 81 00 80 */	lwz r28, 0x80(r1)
/* 800083B8 00004F98  38 21 00 A8 */	addi r1, r1, 0xa8
/* 800083BC 00004F9C  7C 08 03 A6 */	mtlr r0
/* 800083C0 00004FA0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

inline void checkPos(HurtCapsule* hurt, Mtx mtx, f32 arg5)
{
    if (!hurt->skip_update_pos) {
        func_8000B1CC(hurt->bone, &hurt->a_offset, &hurt->a_pos);
        func_8000B1CC(hurt->bone, &hurt->b_offset, &hurt->b_pos);

        if (mtx != NULL) {
            hurt->b_pos.z = arg5;
            hurt->a_pos.z = arg5;
        }

        hurt->skip_update_pos = true;
    }
}

inline void mtxConcat(HurtCapsule* hurt, Mtx mtx)
{
    Mtx sp34;
    if (mtx != NULL) {
        HSD_JObj* temp_r31;
        temp_r31 = hurt->bone;
        HSD_JObjGetMtx(temp_r31);
        PSMTXConcat(mtx, temp_r31->mtx, &sp34[0]);
    }
}

inline Mtx* pickMtx(HurtCapsule* hurt, Mtx mtx)
{
    Mtx* var_r9;
    Mtx sp34;
    if (mtx != NULL) {
        var_r9 = &sp34;
    } else {
        HSD_JObj* temp_r31_2 = hurt->bone;
        HSD_JObjGetMtx(temp_r31_2);
        var_r9 = &temp_r31_2->mtx;
    }
    return var_r9;
}

inline f32 getHit1C(HitCapsule* hit, f32 arg3)
{
    f32 var_f1;
    if (hit->x43_b1)
        var_f1 = hit->scl;
    else
        var_f1 = hit->scl * arg3;
    return var_f1;
}

bool lbColl_80008248(HitCapsule* hit, HurtCapsule* hurt, Mtx mtx, f32 arg3,
                     f32 arg4, f32 arg5)
{
    Vec3* sp70 = NULL;
    Vec3* sp64 = NULL;

    checkPos(hurt, mtx, arg5);
    mtxConcat(hurt, mtx);

    return lbColl_80006E58(&hit->x58, &hit->x4C, &hurt->a_pos, &hurt->b_pos,
                           sp70, sp64, *pickMtx(hurt, mtx), &hit->x64,
                           getHit1C(hit, arg3), hurt->scl, 3.0f * arg4);
}
#endif

void lbColl_800083C4(HurtCapsule* arg0)
{
    if (arg0->skip_update_pos)
        return;

    func_8000B1CC(arg0->bone, &arg0->a_offset, &arg0->a_pos);
    func_8000B1CC(arg0->bone, &arg0->b_offset, &arg0->b_pos);
    arg0->skip_update_pos = true;
}

void lbColl_80008428(HitCapsule* arg0)
{
    arg0->state = HitCapsule_Disabled;
}

void lbColl_80008434(HitCapsule* arg0)
{
    arg0->state = HitCapsule_Enabled;
}

#ifdef MWERKS_GEKKO
#pragma push
asm void lbColl_80008440(HitCapsule*)
{ // clang-format off
    nofralloc
/* 80008440 00005020  38 80 00 00 */	li r4, 0
/* 80008444 00005024  90 83 00 74 */	stw r4, 0x74(r3)
/* 80008448 00005028  38 C0 00 08 */	li r6, 8
/* 8000844C 0000502C  90 83 00 7C */	stw r4, 0x7c(r3)
/* 80008450 00005030  90 83 00 84 */	stw r4, 0x84(r3)
/* 80008454 00005034  90 83 00 8C */	stw r4, 0x8c(r3)
/* 80008458 00005038  90 83 00 94 */	stw r4, 0x94(r3)
/* 8000845C 0000503C  90 83 00 9C */	stw r4, 0x9c(r3)
/* 80008460 00005040  90 83 00 A4 */	stw r4, 0xa4(r3)
/* 80008464 00005044  90 83 00 AC */	stw r4, 0xac(r3)
/* 80008468 00005048  48 00 00 78 */	b lbl_800084E0
lbl_8000846C:
/* 8000846C 0000504C  20 06 00 0C */	subfic r0, r6, 0xc
/* 80008470 00005050  28 06 00 0C */	cmplwi r6, 0xc
/* 80008474 00005054  7C 09 03 A6 */	mtctr r0
/* 80008478 00005058  40 80 00 10 */	bge lbl_80008488
lbl_8000847C:
/* 8000847C 0000505C  90 85 00 74 */	stw r4, 0x74(r5)
/* 80008480 00005060  38 A5 00 08 */	addi r5, r5, 8
/* 80008484 00005064  42 00 FF F8 */	bdnz lbl_8000847C
lbl_80008488:
/* 80008488 00005068  38 80 00 00 */	li r4, 0
/* 8000848C 0000506C  98 83 00 44 */	stb r4, 0x44(r3)
/* 80008490 00005070  38 C0 00 08 */	li r6, 8
/* 80008494 00005074  90 83 00 D4 */	stw r4, 0xd4(r3)
/* 80008498 00005078  90 83 00 DC */	stw r4, 0xdc(r3)
/* 8000849C 0000507C  90 83 00 E4 */	stw r4, 0xe4(r3)
/* 800084A0 00005080  90 83 00 EC */	stw r4, 0xec(r3)
/* 800084A4 00005084  90 83 00 F4 */	stw r4, 0xf4(r3)
/* 800084A8 00005088  90 83 00 FC */	stw r4, 0xfc(r3)
/* 800084AC 0000508C  90 83 01 04 */	stw r4, 0x104(r3)
/* 800084B0 00005090  90 83 01 0C */	stw r4, 0x10c(r3)
/* 800084B4 00005094  48 00 00 38 */	b lbl_800084EC
lbl_800084B8:
/* 800084B8 00005098  20 06 00 0C */	subfic r0, r6, 0xc
/* 800084BC 0000509C  28 06 00 0C */	cmplwi r6, 0xc
/* 800084C0 000050A0  7C 09 03 A6 */	mtctr r0
/* 800084C4 000050A4  40 80 00 10 */	bge lbl_800084D4
lbl_800084C8:
/* 800084C8 000050A8  90 85 00 D4 */	stw r4, 0xd4(r5)
/* 800084CC 000050AC  38 A5 00 08 */	addi r5, r5, 8
/* 800084D0 000050B0  42 00 FF F8 */	bdnz lbl_800084C8
lbl_800084D4:
/* 800084D4 000050B4  38 00 00 00 */	li r0, 0
/* 800084D8 000050B8  98 03 00 45 */	stb r0, 0x45(r3)
/* 800084DC 000050BC  4E 80 00 20 */	blr
lbl_800084E0:
/* 800084E0 000050C0  54 C0 18 38 */	slwi r0, r6, 3
/* 800084E4 000050C4  7C A3 02 14 */	add r5, r3, r0
/* 800084E8 000050C8  4B FF FF 84 */	b lbl_8000846C
lbl_800084EC:
/* 800084EC 000050CC  54 C0 18 38 */	slwi r0, r6, 3
/* 800084F0 000050D0  7C A3 02 14 */	add r5, r3, r0
/* 800084F4 000050D4  4B FF FF C4 */	b lbl_800084B8
/* 800084F8 000050D8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void lbColl_80008440(HitCapsule* arg0)
{
    s32 var_ctr;
    s32 var_ctr_2;
    void* var_r5;
    void* var_r5_2;

    arg0->victims_1[0].victim = NULL;
    arg0->victims_1[1].victim = NULL;
    arg0->victims_1[2].victim = NULL;
    arg0->victims_1[3].victim = NULL;
    arg0->victims_1[4].victim = NULL;
    arg0->victims_1[5].victim = NULL;
    arg0->victims_1[6].victim = NULL;
    arg0->victims_1[7].victim = NULL;
    var_r5 = arg0 + 0x40;
    var_ctr = 0xC - 8U;
    if (8U < 0xCU) {
        do {
            M2C_FIELD(var_r5, Fighter**, 0x74) = NULL;
            var_r5 += 2;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    arg0->x44 = 0;
    arg0->victims_2[0].victim = (Fighter*) 0U;
    arg0->victims_2[1].victim = (Fighter*) 0U;
    arg0->victims_2[2].victim = (Fighter*) 0U;
    arg0->victims_2[3].victim = (Fighter*) 0U;
    arg0->victims_2[4].victim = (Fighter*) 0U;
    arg0->victims_2[5].victim = (Fighter*) 0U;
    arg0->victims_2[6].victim = (Fighter*) 0U;
    arg0->victims_2[7].victim = (Fighter*) 0U;
    var_r5_2 = arg0 + 0x40;
    var_ctr_2 = 0xC - 8U;
    if (8U < 0xCU) {
        do {
            M2C_FIELD(var_r5_2, s32*, 0xD4) = (s32) 0U;
            var_r5_2 += 8;
            var_ctr_2 -= 1;
        } while (var_ctr_2 != 0);
    }
    arg0->x45 = 0;
}
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbColl_CopyHitCapsule(HitCapsule*, HitCapsule*)
{ // clang-format off
    nofralloc
/* 800084FC 000050DC  81 23 00 74 */	lwz r9, 0x74(r3)
/* 80008500 000050E0  38 A3 00 74 */	addi r5, r3, 0x74
/* 80008504 000050E4  80 03 00 78 */	lwz r0, 0x78(r3)
/* 80008508 000050E8  38 C4 00 74 */	addi r6, r4, 0x74
/* 8000850C 000050EC  38 E3 00 D4 */	addi r7, r3, 0xd4
/* 80008510 000050F0  91 24 00 74 */	stw r9, 0x74(r4)
/* 80008514 000050F4  39 04 00 D4 */	addi r8, r4, 0xd4
/* 80008518 000050F8  90 04 00 78 */	stw r0, 0x78(r4)
/* 8000851C 000050FC  38 00 00 08 */	li r0, 8
/* 80008520 00005100  81 43 00 D4 */	lwz r10, 0xd4(r3)
/* 80008524 00005104  81 23 00 D8 */	lwz r9, 0xd8(r3)
/* 80008528 00005108  91 44 00 D4 */	stw r10, 0xd4(r4)
/* 8000852C 0000510C  91 24 00 D8 */	stw r9, 0xd8(r4)
/* 80008530 00005110  81 43 00 7C */	lwz r10, 0x7c(r3)
/* 80008534 00005114  81 23 00 80 */	lwz r9, 0x80(r3)
/* 80008538 00005118  91 44 00 7C */	stw r10, 0x7c(r4)
/* 8000853C 0000511C  91 24 00 80 */	stw r9, 0x80(r4)
/* 80008540 00005120  81 43 00 DC */	lwz r10, 0xdc(r3)
/* 80008544 00005124  81 23 00 E0 */	lwz r9, 0xe0(r3)
/* 80008548 00005128  91 44 00 DC */	stw r10, 0xdc(r4)
/* 8000854C 0000512C  91 24 00 E0 */	stw r9, 0xe0(r4)
/* 80008550 00005130  81 43 00 84 */	lwz r10, 0x84(r3)
/* 80008554 00005134  81 23 00 88 */	lwz r9, 0x88(r3)
/* 80008558 00005138  91 44 00 84 */	stw r10, 0x84(r4)
/* 8000855C 0000513C  91 24 00 88 */	stw r9, 0x88(r4)
/* 80008560 00005140  81 43 00 E4 */	lwz r10, 0xe4(r3)
/* 80008564 00005144  81 23 00 E8 */	lwz r9, 0xe8(r3)
/* 80008568 00005148  91 44 00 E4 */	stw r10, 0xe4(r4)
/* 8000856C 0000514C  91 24 00 E8 */	stw r9, 0xe8(r4)
/* 80008570 00005150  81 43 00 8C */	lwz r10, 0x8c(r3)
/* 80008574 00005154  81 23 00 90 */	lwz r9, 0x90(r3)
/* 80008578 00005158  91 44 00 8C */	stw r10, 0x8c(r4)
/* 8000857C 0000515C  91 24 00 90 */	stw r9, 0x90(r4)
/* 80008580 00005160  81 43 00 EC */	lwz r10, 0xec(r3)
/* 80008584 00005164  81 23 00 F0 */	lwz r9, 0xf0(r3)
/* 80008588 00005168  91 44 00 EC */	stw r10, 0xec(r4)
/* 8000858C 0000516C  91 24 00 F0 */	stw r9, 0xf0(r4)
/* 80008590 00005170  81 43 00 94 */	lwz r10, 0x94(r3)
/* 80008594 00005174  81 23 00 98 */	lwz r9, 0x98(r3)
/* 80008598 00005178  91 44 00 94 */	stw r10, 0x94(r4)
/* 8000859C 0000517C  91 24 00 98 */	stw r9, 0x98(r4)
/* 800085A0 00005180  81 43 00 F4 */	lwz r10, 0xf4(r3)
/* 800085A4 00005184  81 23 00 F8 */	lwz r9, 0xf8(r3)
/* 800085A8 00005188  91 44 00 F4 */	stw r10, 0xf4(r4)
/* 800085AC 0000518C  91 24 00 F8 */	stw r9, 0xf8(r4)
/* 800085B0 00005190  81 43 00 9C */	lwz r10, 0x9c(r3)
/* 800085B4 00005194  81 23 00 A0 */	lwz r9, 0xa0(r3)
/* 800085B8 00005198  91 44 00 9C */	stw r10, 0x9c(r4)
/* 800085BC 0000519C  91 24 00 A0 */	stw r9, 0xa0(r4)
/* 800085C0 000051A0  81 43 00 FC */	lwz r10, 0xfc(r3)
/* 800085C4 000051A4  81 23 01 00 */	lwz r9, 0x100(r3)
/* 800085C8 000051A8  91 44 00 FC */	stw r10, 0xfc(r4)
/* 800085CC 000051AC  91 24 01 00 */	stw r9, 0x100(r4)
/* 800085D0 000051B0  81 43 00 A4 */	lwz r10, 0xa4(r3)
/* 800085D4 000051B4  81 23 00 A8 */	lwz r9, 0xa8(r3)
/* 800085D8 000051B8  91 44 00 A4 */	stw r10, 0xa4(r4)
/* 800085DC 000051BC  91 24 00 A8 */	stw r9, 0xa8(r4)
/* 800085E0 000051C0  81 43 01 04 */	lwz r10, 0x104(r3)
/* 800085E4 000051C4  81 23 01 08 */	lwz r9, 0x108(r3)
/* 800085E8 000051C8  91 44 01 04 */	stw r10, 0x104(r4)
/* 800085EC 000051CC  91 24 01 08 */	stw r9, 0x108(r4)
/* 800085F0 000051D0  81 43 00 AC */	lwz r10, 0xac(r3)
/* 800085F4 000051D4  81 23 00 B0 */	lwz r9, 0xb0(r3)
/* 800085F8 000051D8  91 44 00 AC */	stw r10, 0xac(r4)
/* 800085FC 000051DC  91 24 00 B0 */	stw r9, 0xb0(r4)
/* 80008600 000051E0  81 43 01 0C */	lwz r10, 0x10c(r3)
/* 80008604 000051E4  81 23 01 10 */	lwz r9, 0x110(r3)
/* 80008608 000051E8  91 44 01 0C */	stw r10, 0x10c(r4)
/* 8000860C 000051EC  91 24 01 10 */	stw r9, 0x110(r4)
/* 80008610 000051F0  48 00 00 5C */	b lbl_8000866C
lbl_80008614:
/* 80008614 000051F4  20 A0 00 0C */	subfic r5, r0, 0xc
/* 80008618 000051F8  28 00 00 0C */	cmplwi r0, 0xc
/* 8000861C 000051FC  7C A9 03 A6 */	mtctr r5
/* 80008620 00005200  40 80 00 38 */	bge lbl_80008658
lbl_80008624:
/* 80008624 00005204  80 A9 00 00 */	lwz r5, 0(r9)
/* 80008628 00005208  80 09 00 04 */	lwz r0, 4(r9)
/* 8000862C 0000520C  39 29 00 08 */	addi r9, r9, 8
/* 80008630 00005210  90 A6 00 00 */	stw r5, 0(r6)
/* 80008634 00005214  90 06 00 04 */	stw r0, 4(r6)
/* 80008638 00005218  38 C6 00 08 */	addi r6, r6, 8
/* 8000863C 0000521C  80 A7 00 00 */	lwz r5, 0(r7)
/* 80008640 00005220  80 07 00 04 */	lwz r0, 4(r7)
/* 80008644 00005224  38 E7 00 08 */	addi r7, r7, 8
/* 80008648 00005228  90 A8 00 00 */	stw r5, 0(r8)
/* 8000864C 0000522C  90 08 00 04 */	stw r0, 4(r8)
/* 80008650 00005230  39 08 00 08 */	addi r8, r8, 8
/* 80008654 00005234  42 00 FF D0 */	bdnz lbl_80008624
lbl_80008658:
/* 80008658 00005238  88 03 00 44 */	lbz r0, 0x44(r3)
/* 8000865C 0000523C  98 04 00 44 */	stb r0, 0x44(r4)
/* 80008660 00005240  88 03 00 45 */	lbz r0, 0x45(r3)
/* 80008664 00005244  98 04 00 45 */	stb r0, 0x45(r4)
/* 80008668 00005248  4E 80 00 20 */	blr
lbl_8000866C:
/* 8000866C 0000524C  54 0A 18 38 */	slwi r10, r0, 3
/* 80008670 00005250  7D 25 52 14 */	add r9, r5, r10
/* 80008674 00005254  7C C6 52 14 */	add r6, r6, r10
/* 80008678 00005258  7C E7 52 14 */	add r7, r7, r10
/* 8000867C 0000525C  7D 08 52 14 */	add r8, r8, r10
/* 80008680 00005260  4B FF FF 94 */	b lbl_80008614
/* 80008684 00005264  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void lbColl_CopyHitCapsule(HitCapsule* src, HitCapsule* dst)
{
    Fighter* temp_r5;
    Fighter* temp_r5_2;
    HitVictim* var_r6;
    HitVictim* var_r7;
    HitVictim* var_r8;
    HitVictim* var_r9;
    UNK_T temp_r0;
    UNK_T temp_r0_2;
    s32 var_ctr;

    dst->victims_1[0].victim = src->victims_1[0].victim;
    dst->victims_1[0].x4 = src->victims_1[0].x4;
    dst->victims_2[0].victim = src->victims_2[0].victim;
    dst->victims_2[0].x4 = src->victims_2[0].x4;
    dst->victims_1[1].victim = src->victims_1[1].victim;
    dst->victims_1[1].x4 = src->victims_1[1].x4;
    dst->victims_2[1].victim = src->victims_2[1].victim;
    dst->victims_2[1].x4 = src->victims_2[1].x4;
    dst->victims_1[2].victim = src->victims_1[2].victim;
    dst->victims_1[2].x4 = src->victims_1[2].x4;
    dst->victims_2[2].victim = src->victims_2[2].victim;
    dst->victims_2[2].x4 = src->victims_2[2].x4;
    dst->victims_1[3].victim = src->victims_1[3].victim;
    dst->victims_1[3].x4 = src->victims_1[3].x4;
    dst->victims_2[3].victim = src->victims_2[3].victim;
    dst->victims_2[3].x4 = src->victims_2[3].x4;
    dst->victims_1[4].victim = src->victims_1[4].victim;
    dst->victims_1[4].x4 = src->victims_1[4].x4;
    dst->victims_2[4].victim = src->victims_2[4].victim;
    dst->victims_2[4].x4 = src->victims_2[4].x4;
    dst->victims_1[5].victim = src->victims_1[5].victim;
    dst->victims_1[5].x4 = src->victims_1[5].x4;
    dst->victims_2[5].victim = src->victims_2[5].victim;
    dst->victims_2[5].x4 = src->victims_2[5].x4;
    dst->victims_1[6].victim = src->victims_1[6].victim;
    dst->victims_1[6].x4 = src->victims_1[6].x4;
    dst->victims_2[6].victim = src->victims_2[6].victim;
    dst->victims_2[6].x4 = src->victims_2[6].x4;
    dst->victims_1[7].victim = src->victims_1[7].victim;
    dst->victims_1[7].x4 = src->victims_1[7].x4;
    dst->victims_2[7].victim = src->victims_2[7].victim;
    dst->victims_2[7].x4 = src->victims_2[7].x4;
    var_r9 = src->victims_1 + 0x40;
    var_r6 = dst->victims_1 + 0x40;
    var_r7 = src->victims_2 + 0x40;
    var_r8 = dst->victims_2 + 0x40;
    var_ctr = 0xC - 8U;
    if (8U < 0xCU) {
        do {
            temp_r5 = var_r9->victim;
            temp_r0 = var_r9->x4;
            var_r9 += 8;
            var_r6->victim = temp_r5;
            var_r6->x4 = temp_r0;
            var_r6 += 8;
            temp_r5_2 = var_r7->victim;
            temp_r0_2 = var_r7->x4;
            var_r7 += 8;
            var_r8->victim = temp_r5_2;
            var_r8->x4 = temp_r0_2;
            var_r8 += 8;
            var_ctr -= 1;
        } while (var_ctr != 0);
    }
    dst->x44 = src->x44;
    dst->x45 = src->x45;
}
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm bool lbColl_80008688(HitCapsule*, enum_t, Fighter*)
{ // clang-format off
    nofralloc
/* 80008688 00005268  38 00 00 0C */	li r0, 0xc
/* 8000868C 0000526C  7C 09 03 A6 */	mtctr r0
/* 80008690 00005270  38 C3 00 00 */	addi r6, r3, 0
/* 80008694 00005274  38 E0 00 00 */	li r7, 0
lbl_80008698:
/* 80008698 00005278  80 06 00 74 */	lwz r0, 0x74(r6)
/* 8000869C 0000527C  7C 00 28 40 */	cmplw r0, r5
/* 800086A0 00005280  40 82 00 4C */	bne lbl_800086EC
/* 800086A4 00005284  2C 04 00 06 */	cmpwi r4, 6
/* 800086A8 00005288  41 82 00 3C */	beq lbl_800086E4
/* 800086AC 0000528C  40 80 00 1C */	bge lbl_800086C8
/* 800086B0 00005290  2C 04 00 03 */	cmpwi r4, 3
/* 800086B4 00005294  41 82 00 30 */	beq lbl_800086E4
/* 800086B8 00005298  40 80 00 18 */	bge lbl_800086D0
/* 800086BC 0000529C  2C 04 00 02 */	cmpwi r4, 2
/* 800086C0 000052A0  40 80 00 10 */	bge lbl_800086D0
/* 800086C4 000052A4  48 00 00 20 */	b lbl_800086E4
lbl_800086C8:
/* 800086C8 000052A8  2C 04 00 09 */	cmpwi r4, 9
/* 800086CC 000052AC  40 80 00 18 */	bge lbl_800086E4
lbl_800086D0:
/* 800086D0 000052B0  A0 83 00 40 */	lhz r4, 0x40(r3)
/* 800086D4 000052B4  54 E0 18 38 */	slwi r0, r7, 3
/* 800086D8 000052B8  7C 63 02 14 */	add r3, r3, r0
/* 800086DC 000052BC  54 80 E6 3E */	rlwinm r0, r4, 0x1c, 0x18, 0x1f
/* 800086E0 000052C0  90 03 00 78 */	stw r0, 0x78(r3)
lbl_800086E4:
/* 800086E4 000052C4  38 60 00 00 */	li r3, 0
/* 800086E8 000052C8  4E 80 00 20 */	blr
lbl_800086EC:
/* 800086EC 000052CC  38 C6 00 08 */	addi r6, r6, 8
/* 800086F0 000052D0  38 E7 00 01 */	addi r7, r7, 1
/* 800086F4 000052D4  42 00 FF A4 */	bdnz lbl_80008698
/* 800086F8 000052D8  38 00 00 02 */	li r0, 2
/* 800086FC 000052DC  7C 09 03 A6 */	mtctr r0
/* 80008700 000052E0  38 C3 00 00 */	addi r6, r3, 0
/* 80008704 000052E4  39 00 00 00 */	li r8, 0
lbl_80008708:
/* 80008708 000052E8  80 06 00 74 */	lwz r0, 0x74(r6)
/* 8000870C 000052EC  28 00 00 00 */	cmplwi r0, 0
/* 80008710 000052F0  41 82 00 74 */	beq lbl_80008784
/* 80008714 000052F4  80 06 00 7C */	lwz r0, 0x7c(r6)
/* 80008718 000052F8  38 C6 00 08 */	addi r6, r6, 8
/* 8000871C 000052FC  39 08 00 01 */	addi r8, r8, 1
/* 80008720 00005300  28 00 00 00 */	cmplwi r0, 0
/* 80008724 00005304  41 82 00 60 */	beq lbl_80008784
/* 80008728 00005308  80 06 00 7C */	lwz r0, 0x7c(r6)
/* 8000872C 0000530C  38 C6 00 08 */	addi r6, r6, 8
/* 80008730 00005310  39 08 00 01 */	addi r8, r8, 1
/* 80008734 00005314  28 00 00 00 */	cmplwi r0, 0
/* 80008738 00005318  41 82 00 4C */	beq lbl_80008784
/* 8000873C 0000531C  80 06 00 7C */	lwz r0, 0x7c(r6)
/* 80008740 00005320  38 C6 00 08 */	addi r6, r6, 8
/* 80008744 00005324  39 08 00 01 */	addi r8, r8, 1
/* 80008748 00005328  28 00 00 00 */	cmplwi r0, 0
/* 8000874C 0000532C  41 82 00 38 */	beq lbl_80008784
/* 80008750 00005330  80 06 00 7C */	lwz r0, 0x7c(r6)
/* 80008754 00005334  38 C6 00 08 */	addi r6, r6, 8
/* 80008758 00005338  39 08 00 01 */	addi r8, r8, 1
/* 8000875C 0000533C  28 00 00 00 */	cmplwi r0, 0
/* 80008760 00005340  41 82 00 24 */	beq lbl_80008784
/* 80008764 00005344  80 06 00 7C */	lwz r0, 0x7c(r6)
/* 80008768 00005348  38 C6 00 08 */	addi r6, r6, 8
/* 8000876C 0000534C  39 08 00 01 */	addi r8, r8, 1
/* 80008770 00005350  28 00 00 00 */	cmplwi r0, 0
/* 80008774 00005354  41 82 00 10 */	beq lbl_80008784
/* 80008778 00005358  38 C6 00 08 */	addi r6, r6, 8
/* 8000877C 0000535C  39 08 00 01 */	addi r8, r8, 1
/* 80008780 00005360  42 00 FF 88 */	bdnz lbl_80008708
lbl_80008784:
/* 80008784 00005364  28 08 00 0C */	cmplwi r8, 0xc
/* 80008788 00005368  40 82 00 0C */	bne lbl_80008794
/* 8000878C 0000536C  88 03 00 44 */	lbz r0, 0x44(r3)
/* 80008790 00005370  48 00 00 08 */	b lbl_80008798
lbl_80008794:
/* 80008794 00005374  7D 00 43 78 */	mr r0, r8
lbl_80008798:
/* 80008798 00005378  54 07 18 38 */	slwi r7, r0, 3
/* 8000879C 0000537C  7C C3 3A 14 */	add r6, r3, r7
/* 800087A0 00005380  2C 04 00 06 */	cmpwi r4, 6
/* 800087A4 00005384  90 A6 00 74 */	stw r5, 0x74(r6)
/* 800087A8 00005388  41 82 00 3C */	beq lbl_800087E4
/* 800087AC 0000538C  40 80 00 1C */	bge lbl_800087C8
/* 800087B0 00005390  2C 04 00 03 */	cmpwi r4, 3
/* 800087B4 00005394  41 82 00 30 */	beq lbl_800087E4
/* 800087B8 00005398  40 80 00 18 */	bge lbl_800087D0
/* 800087BC 0000539C  2C 04 00 02 */	cmpwi r4, 2
/* 800087C0 000053A0  40 80 00 10 */	bge lbl_800087D0
/* 800087C4 000053A4  48 00 00 20 */	b lbl_800087E4
lbl_800087C8:
/* 800087C8 000053A8  2C 04 00 09 */	cmpwi r4, 9
/* 800087CC 000053AC  40 80 00 18 */	bge lbl_800087E4
lbl_800087D0:
/* 800087D0 000053B0  A0 03 00 40 */	lhz r0, 0x40(r3)
/* 800087D4 000053B4  7C 83 3A 14 */	add r4, r3, r7
/* 800087D8 000053B8  54 00 E6 3E */	rlwinm r0, r0, 0x1c, 0x18, 0x1f
/* 800087DC 000053BC  90 04 00 78 */	stw r0, 0x78(r4)
/* 800087E0 000053C0  48 00 00 10 */	b lbl_800087F0
lbl_800087E4:
/* 800087E4 000053C4  7C 83 3A 14 */	add r4, r3, r7
/* 800087E8 000053C8  38 00 00 00 */	li r0, 0
/* 800087EC 000053CC  90 04 00 78 */	stw r0, 0x78(r4)
lbl_800087F0:
/* 800087F0 000053D0  28 08 00 0C */	cmplwi r8, 0xc
/* 800087F4 000053D4  40 82 00 24 */	bne lbl_80008818
/* 800087F8 000053D8  88 83 00 44 */	lbz r4, 0x44(r3)
/* 800087FC 000053DC  38 04 00 01 */	addi r0, r4, 1
/* 80008800 000053E0  98 03 00 44 */	stb r0, 0x44(r3)
/* 80008804 000053E4  88 03 00 44 */	lbz r0, 0x44(r3)
/* 80008808 000053E8  28 00 00 0C */	cmplwi r0, 0xc
/* 8000880C 000053EC  41 80 00 0C */	blt lbl_80008818
/* 80008810 000053F0  38 00 00 00 */	li r0, 0
/* 80008814 000053F4  98 03 00 44 */	stb r0, 0x44(r3)
lbl_80008818:
/* 80008818 000053F8  38 60 00 01 */	li r3, 1
/* 8000881C 000053FC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool lbColl_80008688(HitCapsule* arg0, int arg1, Fighter* arg2)
{
    HitCapsule* var_r6;
    HitCapsule* var_r6_2;
    f32* temp_r6;
    f32* temp_r6_2;
    f32* temp_r6_3;
    f32* temp_r6_4;
    int var_ctr;
    int var_ctr_2;
    int var_r7;
    u8 var_r0;
    u8 var_r8;

    var_ctr = 0xC;
    var_r6 = arg0;
    var_r7 = 0;
loop_1:
    if ((Fighter*) var_r6->victims_1[0].victim == arg2) {
        if (arg1 != 6) {
            if (arg1 < 6) {
                if (arg1 != 3) {
                    if ((arg1 < 3) && (arg1 < 2)) {
                    } else {
                        goto block_9;
                    }
                }
            } else if (arg1 < 9) {
            block_9:
                arg0->victims_1[var_r7].x4 =
                    (UNK_T) (M2C_FIELD(arg0, u16*, 0x40) >> 4U);
            }
        }
        return 0;
    }
    var_r6 += 8;
    var_r7 += 1;
    var_ctr -= 1;
    if (var_ctr == 0) {
        var_ctr_2 = 2;
        var_r6_2 = arg0;
        var_r8 = 0;
    loop_13:
        if ((Fighter*) var_r6_2->victims_1[0].victim != NULL) {
            temp_r6 = &var_r6_2->a_offset.y;
            var_r8 += 1;
            if ((Fighter*) var_r6_2->victims_1[1].victim != NULL) {
                temp_r6_2 = temp_r6 + 8;
                var_r8 += 1;
                if ((u32) M2C_FIELD(temp_r6, u32*, 0x7C) != 0U) {
                    temp_r6_3 = temp_r6_2 + 8;
                    var_r8 += 1;
                    if ((u32) M2C_FIELD(temp_r6_2, u32*, 0x7C) != 0U) {
                        temp_r6_4 = temp_r6_3 + 8;
                        var_r8 += 1;
                        if ((u32) M2C_FIELD(temp_r6_3, u32*, 0x7C) != 0U) {
                            var_r8 += 1;
                            if ((u32) M2C_FIELD(temp_r6_4, u32*, 0x7C) != 0U) {
                                var_r6_2 = (HitCapsule*) (temp_r6_4 + 8 + 8);
                                var_r8 += 1;
                                var_ctr_2 -= 1;
                                if (var_ctr_2 != 0) {
                                    goto loop_13;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (var_r8 == 0xC) {
            var_r0 = arg0->x44;
        } else {
            var_r0 = var_r8;
        }
        arg0->victims_1[var_r0].victim = arg2;
        if (arg1 != 6) {
            if (arg1 < 6) {
                if (arg1 != 3) {
                    if ((arg1 < 3) && (arg1 < 2)) {
                        goto block_31;
                    }
                    goto block_30;
                }
                goto block_31;
            }
            if (arg1 < 9) {
            block_30:
                arg0->victims_1[var_r0].x4 =
                    (UNK_T) (M2C_FIELD(arg0, u16*, 0x40) >> 4U);
            } else {
                goto block_31;
            }
        } else {
        block_31:
            arg0->victims_1[var_r0].x4 = 0;
        }
        if (var_r8 == 0xC) {
            arg0->x44 += 1;
            if ((u8) arg0->x44 >= 0xCU) {
                arg0->x44 = 0;
            }
        }
        return 1;
    }
    goto loop_1;
}
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_80008820(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 80008820 00005400  38 00 00 0C */	li r0, 0xc
/* 80008824 00005404  7C 09 03 A6 */	mtctr r0
/* 80008828 00005408  38 C3 00 00 */	addi r6, r3, 0
/* 8000882C 0000540C  38 E0 00 00 */	li r7, 0
lbl_80008830:
/* 80008830 00005410  80 06 00 D4 */	lwz r0, 0xd4(r6)
/* 80008834 00005414  7C 00 28 40 */	cmplw r0, r5
/* 80008838 00005418  40 82 00 4C */	bne lbl_80008884
/* 8000883C 0000541C  2C 04 00 05 */	cmpwi r4, 5
/* 80008840 00005420  41 82 00 28 */	beq lbl_80008868
/* 80008844 00005424  40 80 00 10 */	bge lbl_80008854
/* 80008848 00005428  2C 04 00 02 */	cmpwi r4, 2
/* 8000884C 0000542C  41 82 00 1C */	beq lbl_80008868
/* 80008850 00005430  48 00 00 2C */	b lbl_8000887C
lbl_80008854:
/* 80008854 00005434  2C 04 00 09 */	cmpwi r4, 9
/* 80008858 00005438  40 80 00 24 */	bge lbl_8000887C
/* 8000885C 0000543C  2C 04 00 07 */	cmpwi r4, 7
/* 80008860 00005440  40 80 00 08 */	bge lbl_80008868
/* 80008864 00005444  48 00 00 18 */	b lbl_8000887C
lbl_80008868:
/* 80008868 00005448  A0 83 00 40 */	lhz r4, 0x40(r3)
/* 8000886C 0000544C  54 E0 18 38 */	slwi r0, r7, 3
/* 80008870 00005450  7C 63 02 14 */	add r3, r3, r0
/* 80008874 00005454  54 80 E6 3E */	rlwinm r0, r4, 0x1c, 0x18, 0x1f
/* 80008878 00005458  90 03 00 D8 */	stw r0, 0xd8(r3)
lbl_8000887C:
/* 8000887C 0000545C  38 60 00 00 */	li r3, 0
/* 80008880 00005460  4E 80 00 20 */	blr
lbl_80008884:
/* 80008884 00005464  38 C6 00 08 */	addi r6, r6, 8
/* 80008888 00005468  38 E7 00 01 */	addi r7, r7, 1
/* 8000888C 0000546C  42 00 FF A4 */	bdnz lbl_80008830
/* 80008890 00005470  38 00 00 02 */	li r0, 2
/* 80008894 00005474  7C 09 03 A6 */	mtctr r0
/* 80008898 00005478  38 C3 00 00 */	addi r6, r3, 0
/* 8000889C 0000547C  39 00 00 00 */	li r8, 0
lbl_800088A0:
/* 800088A0 00005480  80 06 00 D4 */	lwz r0, 0xd4(r6)
/* 800088A4 00005484  28 00 00 00 */	cmplwi r0, 0
/* 800088A8 00005488  41 82 00 74 */	beq lbl_8000891C
/* 800088AC 0000548C  80 06 00 DC */	lwz r0, 0xdc(r6)
/* 800088B0 00005490  38 C6 00 08 */	addi r6, r6, 8
/* 800088B4 00005494  39 08 00 01 */	addi r8, r8, 1
/* 800088B8 00005498  28 00 00 00 */	cmplwi r0, 0
/* 800088BC 0000549C  41 82 00 60 */	beq lbl_8000891C
/* 800088C0 000054A0  80 06 00 DC */	lwz r0, 0xdc(r6)
/* 800088C4 000054A4  38 C6 00 08 */	addi r6, r6, 8
/* 800088C8 000054A8  39 08 00 01 */	addi r8, r8, 1
/* 800088CC 000054AC  28 00 00 00 */	cmplwi r0, 0
/* 800088D0 000054B0  41 82 00 4C */	beq lbl_8000891C
/* 800088D4 000054B4  80 06 00 DC */	lwz r0, 0xdc(r6)
/* 800088D8 000054B8  38 C6 00 08 */	addi r6, r6, 8
/* 800088DC 000054BC  39 08 00 01 */	addi r8, r8, 1
/* 800088E0 000054C0  28 00 00 00 */	cmplwi r0, 0
/* 800088E4 000054C4  41 82 00 38 */	beq lbl_8000891C
/* 800088E8 000054C8  80 06 00 DC */	lwz r0, 0xdc(r6)
/* 800088EC 000054CC  38 C6 00 08 */	addi r6, r6, 8
/* 800088F0 000054D0  39 08 00 01 */	addi r8, r8, 1
/* 800088F4 000054D4  28 00 00 00 */	cmplwi r0, 0
/* 800088F8 000054D8  41 82 00 24 */	beq lbl_8000891C
/* 800088FC 000054DC  80 06 00 DC */	lwz r0, 0xdc(r6)
/* 80008900 000054E0  38 C6 00 08 */	addi r6, r6, 8
/* 80008904 000054E4  39 08 00 01 */	addi r8, r8, 1
/* 80008908 000054E8  28 00 00 00 */	cmplwi r0, 0
/* 8000890C 000054EC  41 82 00 10 */	beq lbl_8000891C
/* 80008910 000054F0  38 C6 00 08 */	addi r6, r6, 8
/* 80008914 000054F4  39 08 00 01 */	addi r8, r8, 1
/* 80008918 000054F8  42 00 FF 88 */	bdnz lbl_800088A0
lbl_8000891C:
/* 8000891C 000054FC  28 08 00 0C */	cmplwi r8, 0xc
/* 80008920 00005500  40 82 00 0C */	bne lbl_8000892C
/* 80008924 00005504  88 03 00 45 */	lbz r0, 0x45(r3)
/* 80008928 00005508  48 00 00 08 */	b lbl_80008930
lbl_8000892C:
/* 8000892C 0000550C  7D 00 43 78 */	mr r0, r8
lbl_80008930:
/* 80008930 00005510  54 07 18 38 */	slwi r7, r0, 3
/* 80008934 00005514  7C C3 3A 14 */	add r6, r3, r7
/* 80008938 00005518  2C 04 00 05 */	cmpwi r4, 5
/* 8000893C 0000551C  90 A6 00 D4 */	stw r5, 0xd4(r6)
/* 80008940 00005520  41 82 00 28 */	beq lbl_80008968
/* 80008944 00005524  40 80 00 10 */	bge lbl_80008954
/* 80008948 00005528  2C 04 00 02 */	cmpwi r4, 2
/* 8000894C 0000552C  41 82 00 1C */	beq lbl_80008968
/* 80008950 00005530  48 00 00 2C */	b lbl_8000897C
lbl_80008954:
/* 80008954 00005534  2C 04 00 09 */	cmpwi r4, 9
/* 80008958 00005538  40 80 00 24 */	bge lbl_8000897C
/* 8000895C 0000553C  2C 04 00 07 */	cmpwi r4, 7
/* 80008960 00005540  40 80 00 08 */	bge lbl_80008968
/* 80008964 00005544  48 00 00 18 */	b lbl_8000897C
lbl_80008968:
/* 80008968 00005548  A0 03 00 40 */	lhz r0, 0x40(r3)
/* 8000896C 0000554C  7C 83 3A 14 */	add r4, r3, r7
/* 80008970 00005550  54 00 E6 3E */	rlwinm r0, r0, 0x1c, 0x18, 0x1f
/* 80008974 00005554  90 04 00 D8 */	stw r0, 0xd8(r4)
/* 80008978 00005558  48 00 00 10 */	b lbl_80008988
lbl_8000897C:
/* 8000897C 0000555C  7C 83 3A 14 */	add r4, r3, r7
/* 80008980 00005560  38 00 00 00 */	li r0, 0
/* 80008984 00005564  90 04 00 D8 */	stw r0, 0xd8(r4)
lbl_80008988:
/* 80008988 00005568  28 08 00 0C */	cmplwi r8, 0xc
/* 8000898C 0000556C  40 82 00 24 */	bne lbl_800089B0
/* 80008990 00005570  88 83 00 45 */	lbz r4, 0x45(r3)
/* 80008994 00005574  38 04 00 01 */	addi r0, r4, 1
/* 80008998 00005578  98 03 00 45 */	stb r0, 0x45(r3)
/* 8000899C 0000557C  88 03 00 45 */	lbz r0, 0x45(r3)
/* 800089A0 00005580  28 00 00 0C */	cmplwi r0, 0xc
/* 800089A4 00005584  41 80 00 0C */	blt lbl_800089B0
/* 800089A8 00005588  38 00 00 00 */	li r0, 0
/* 800089AC 0000558C  98 03 00 45 */	stb r0, 0x45(r3)
lbl_800089B0:
/* 800089B0 00005590  38 60 00 01 */	li r3, 1
/* 800089B4 00005594  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_800089B8(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 800089B8 00005598  38 00 00 02 */	li r0, 2
/* 800089BC 0000559C  7C 09 03 A6 */	mtctr r0
/* 800089C0 000055A0  38 C0 00 00 */	li r6, 0
/* 800089C4 000055A4  38 00 00 00 */	li r0, 0
lbl_800089C8:
/* 800089C8 000055A8  80 A3 00 74 */	lwz r5, 0x74(r3)
/* 800089CC 000055AC  7C 05 20 40 */	cmplw r5, r4
/* 800089D0 000055B0  40 82 00 08 */	bne lbl_800089D8
/* 800089D4 000055B4  90 03 00 74 */	stw r0, 0x74(r3)
lbl_800089D8:
/* 800089D8 000055B8  80 A3 00 7C */	lwz r5, 0x7c(r3)
/* 800089DC 000055BC  38 63 00 08 */	addi r3, r3, 8
/* 800089E0 000055C0  7C 05 20 40 */	cmplw r5, r4
/* 800089E4 000055C4  40 82 00 08 */	bne lbl_800089EC
/* 800089E8 000055C8  90 03 00 74 */	stw r0, 0x74(r3)
lbl_800089EC:
/* 800089EC 000055CC  80 A3 00 7C */	lwz r5, 0x7c(r3)
/* 800089F0 000055D0  38 63 00 08 */	addi r3, r3, 8
/* 800089F4 000055D4  38 C6 00 01 */	addi r6, r6, 1
/* 800089F8 000055D8  7C 05 20 40 */	cmplw r5, r4
/* 800089FC 000055DC  40 82 00 08 */	bne lbl_80008A04
/* 80008A00 000055E0  90 03 00 74 */	stw r0, 0x74(r3)
lbl_80008A04:
/* 80008A04 000055E4  80 A3 00 7C */	lwz r5, 0x7c(r3)
/* 80008A08 000055E8  38 63 00 08 */	addi r3, r3, 8
/* 80008A0C 000055EC  38 C6 00 01 */	addi r6, r6, 1
/* 80008A10 000055F0  7C 05 20 40 */	cmplw r5, r4
/* 80008A14 000055F4  40 82 00 08 */	bne lbl_80008A1C
/* 80008A18 000055F8  90 03 00 74 */	stw r0, 0x74(r3)
lbl_80008A1C:
/* 80008A1C 000055FC  80 A3 00 7C */	lwz r5, 0x7c(r3)
/* 80008A20 00005600  38 63 00 08 */	addi r3, r3, 8
/* 80008A24 00005604  38 C6 00 01 */	addi r6, r6, 1
/* 80008A28 00005608  7C 05 20 40 */	cmplw r5, r4
/* 80008A2C 0000560C  40 82 00 08 */	bne lbl_80008A34
/* 80008A30 00005610  90 03 00 74 */	stw r0, 0x74(r3)
lbl_80008A34:
/* 80008A34 00005614  80 A3 00 7C */	lwz r5, 0x7c(r3)
/* 80008A38 00005618  38 63 00 08 */	addi r3, r3, 8
/* 80008A3C 0000561C  38 C6 00 01 */	addi r6, r6, 1
/* 80008A40 00005620  7C 05 20 40 */	cmplw r5, r4
/* 80008A44 00005624  40 82 00 08 */	bne lbl_80008A4C
/* 80008A48 00005628  90 03 00 74 */	stw r0, 0x74(r3)
lbl_80008A4C:
/* 80008A4C 0000562C  38 63 00 08 */	addi r3, r3, 8
/* 80008A50 00005630  38 C6 00 01 */	addi r6, r6, 1
/* 80008A54 00005634  42 00 FF 74 */	bdnz lbl_800089C8
/* 80008A58 00005638  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_80008A5C(UNK_PARAMS){
    // clang-format off
    nofralloc
/* 80008A5C 0000563C  80 03 00 00 */	lwz r0, 0(r3)
/* 80008A60 00005640  2C 00 00 00 */	cmpwi r0, 0
/* 80008A64 00005644  4D 82 00 20 */	beqlr
/* 80008A68 00005648  38 00 00 02 */	li r0, 2
/* 80008A6C 0000564C  7C 09 03 A6 */	mtctr r0
/* 80008A70 00005650  38 A3 00 00 */	addi r5, r3, 0
/* 80008A74 00005654  38 C0 00 00 */	li r6, 0
/* 80008A78 00005658  38 00 00 00 */	li r0, 0
lbl_80008A7C:
/* 80008A7C 0000565C  80 85 00 74 */	lwz r4, 0x74(r5)
/* 80008A80 00005660  28 04 00 00 */	cmplwi r4, 0
/* 80008A84 00005664  41 82 00 28 */	beq lbl_80008AAC
/* 80008A88 00005668  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008A8C 0000566C  28 04 00 00 */	cmplwi r4, 0
/* 80008A90 00005670  41 82 00 1C */	beq lbl_80008AAC
/* 80008A94 00005674  38 84 FF FF */	addi r4, r4, -1
/* 80008A98 00005678  90 85 00 78 */	stw r4, 0x78(r5)
/* 80008A9C 0000567C  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008AA0 00005680  28 04 00 00 */	cmplwi r4, 0
/* 80008AA4 00005684  40 82 00 08 */	bne lbl_80008AAC
/* 80008AA8 00005688  90 05 00 74 */	stw r0, 0x74(r5)
lbl_80008AAC:
/* 80008AAC 0000568C  80 85 00 7C */	lwz r4, 0x7c(r5)
/* 80008AB0 00005690  38 A5 00 08 */	addi r5, r5, 8
/* 80008AB4 00005694  28 04 00 00 */	cmplwi r4, 0
/* 80008AB8 00005698  41 82 00 28 */	beq lbl_80008AE0
/* 80008ABC 0000569C  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008AC0 000056A0  28 04 00 00 */	cmplwi r4, 0
/* 80008AC4 000056A4  41 82 00 1C */	beq lbl_80008AE0
/* 80008AC8 000056A8  38 84 FF FF */	addi r4, r4, -1
/* 80008ACC 000056AC  90 85 00 78 */	stw r4, 0x78(r5)
/* 80008AD0 000056B0  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008AD4 000056B4  28 04 00 00 */	cmplwi r4, 0
/* 80008AD8 000056B8  40 82 00 08 */	bne lbl_80008AE0
/* 80008ADC 000056BC  90 05 00 74 */	stw r0, 0x74(r5)
lbl_80008AE0:
/* 80008AE0 000056C0  80 85 00 7C */	lwz r4, 0x7c(r5)
/* 80008AE4 000056C4  38 A5 00 08 */	addi r5, r5, 8
/* 80008AE8 000056C8  38 C6 00 01 */	addi r6, r6, 1
/* 80008AEC 000056CC  28 04 00 00 */	cmplwi r4, 0
/* 80008AF0 000056D0  41 82 00 28 */	beq lbl_80008B18
/* 80008AF4 000056D4  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008AF8 000056D8  28 04 00 00 */	cmplwi r4, 0
/* 80008AFC 000056DC  41 82 00 1C */	beq lbl_80008B18
/* 80008B00 000056E0  38 84 FF FF */	addi r4, r4, -1
/* 80008B04 000056E4  90 85 00 78 */	stw r4, 0x78(r5)
/* 80008B08 000056E8  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008B0C 000056EC  28 04 00 00 */	cmplwi r4, 0
/* 80008B10 000056F0  40 82 00 08 */	bne lbl_80008B18
/* 80008B14 000056F4  90 05 00 74 */	stw r0, 0x74(r5)
lbl_80008B18:
/* 80008B18 000056F8  80 85 00 7C */	lwz r4, 0x7c(r5)
/* 80008B1C 000056FC  38 A5 00 08 */	addi r5, r5, 8
/* 80008B20 00005700  38 C6 00 01 */	addi r6, r6, 1
/* 80008B24 00005704  28 04 00 00 */	cmplwi r4, 0
/* 80008B28 00005708  41 82 00 28 */	beq lbl_80008B50
/* 80008B2C 0000570C  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008B30 00005710  28 04 00 00 */	cmplwi r4, 0
/* 80008B34 00005714  41 82 00 1C */	beq lbl_80008B50
/* 80008B38 00005718  38 84 FF FF */	addi r4, r4, -1
/* 80008B3C 0000571C  90 85 00 78 */	stw r4, 0x78(r5)
/* 80008B40 00005720  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008B44 00005724  28 04 00 00 */	cmplwi r4, 0
/* 80008B48 00005728  40 82 00 08 */	bne lbl_80008B50
/* 80008B4C 0000572C  90 05 00 74 */	stw r0, 0x74(r5)
lbl_80008B50:
/* 80008B50 00005730  80 85 00 7C */	lwz r4, 0x7c(r5)
/* 80008B54 00005734  38 A5 00 08 */	addi r5, r5, 8
/* 80008B58 00005738  38 C6 00 01 */	addi r6, r6, 1
/* 80008B5C 0000573C  28 04 00 00 */	cmplwi r4, 0
/* 80008B60 00005740  41 82 00 28 */	beq lbl_80008B88
/* 80008B64 00005744  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008B68 00005748  28 04 00 00 */	cmplwi r4, 0
/* 80008B6C 0000574C  41 82 00 1C */	beq lbl_80008B88
/* 80008B70 00005750  38 84 FF FF */	addi r4, r4, -1
/* 80008B74 00005754  90 85 00 78 */	stw r4, 0x78(r5)
/* 80008B78 00005758  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008B7C 0000575C  28 04 00 00 */	cmplwi r4, 0
/* 80008B80 00005760  40 82 00 08 */	bne lbl_80008B88
/* 80008B84 00005764  90 05 00 74 */	stw r0, 0x74(r5)
lbl_80008B88:
/* 80008B88 00005768  80 85 00 7C */	lwz r4, 0x7c(r5)
/* 80008B8C 0000576C  38 A5 00 08 */	addi r5, r5, 8
/* 80008B90 00005770  38 C6 00 01 */	addi r6, r6, 1
/* 80008B94 00005774  28 04 00 00 */	cmplwi r4, 0
/* 80008B98 00005778  41 82 00 28 */	beq lbl_80008BC0
/* 80008B9C 0000577C  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008BA0 00005780  28 04 00 00 */	cmplwi r4, 0
/* 80008BA4 00005784  41 82 00 1C */	beq lbl_80008BC0
/* 80008BA8 00005788  38 84 FF FF */	addi r4, r4, -1
/* 80008BAC 0000578C  90 85 00 78 */	stw r4, 0x78(r5)
/* 80008BB0 00005790  80 85 00 78 */	lwz r4, 0x78(r5)
/* 80008BB4 00005794  28 04 00 00 */	cmplwi r4, 0
/* 80008BB8 00005798  40 82 00 08 */	bne lbl_80008BC0
/* 80008BBC 0000579C  90 05 00 74 */	stw r0, 0x74(r5)
lbl_80008BC0:
/* 80008BC0 000057A0  38 A5 00 08 */	addi r5, r5, 8
/* 80008BC4 000057A4  38 C6 00 01 */	addi r6, r6, 1
/* 80008BC8 000057A8  42 00 FE B4 */	bdnz lbl_80008A7C
/* 80008BCC 000057AC  38 00 00 02 */	li r0, 2
/* 80008BD0 000057B0  38 A0 00 00 */	li r5, 0
/* 80008BD4 000057B4  7C 09 03 A6 */	mtctr r0
/* 80008BD8 000057B8  38 05 00 00 */	addi r0, r5, 0
lbl_80008BDC:
/* 80008BDC 000057BC  80 83 00 D4 */	lwz r4, 0xd4(r3)
/* 80008BE0 000057C0  28 04 00 00 */	cmplwi r4, 0
/* 80008BE4 000057C4  41 82 00 28 */	beq lbl_80008C0C
/* 80008BE8 000057C8  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008BEC 000057CC  28 04 00 00 */	cmplwi r4, 0
/* 80008BF0 000057D0  41 82 00 1C */	beq lbl_80008C0C
/* 80008BF4 000057D4  38 84 FF FF */	addi r4, r4, -1
/* 80008BF8 000057D8  90 83 00 D8 */	stw r4, 0xd8(r3)
/* 80008BFC 000057DC  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008C00 000057E0  28 04 00 00 */	cmplwi r4, 0
/* 80008C04 000057E4  40 82 00 08 */	bne lbl_80008C0C
/* 80008C08 000057E8  90 03 00 D4 */	stw r0, 0xd4(r3)
lbl_80008C0C:
/* 80008C0C 000057EC  80 83 00 DC */	lwz r4, 0xdc(r3)
/* 80008C10 000057F0  38 63 00 08 */	addi r3, r3, 8
/* 80008C14 000057F4  28 04 00 00 */	cmplwi r4, 0
/* 80008C18 000057F8  41 82 00 28 */	beq lbl_80008C40
/* 80008C1C 000057FC  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008C20 00005800  28 04 00 00 */	cmplwi r4, 0
/* 80008C24 00005804  41 82 00 1C */	beq lbl_80008C40
/* 80008C28 00005808  38 84 FF FF */	addi r4, r4, -1
/* 80008C2C 0000580C  90 83 00 D8 */	stw r4, 0xd8(r3)
/* 80008C30 00005810  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008C34 00005814  28 04 00 00 */	cmplwi r4, 0
/* 80008C38 00005818  40 82 00 08 */	bne lbl_80008C40
/* 80008C3C 0000581C  90 03 00 D4 */	stw r0, 0xd4(r3)
lbl_80008C40:
/* 80008C40 00005820  80 83 00 DC */	lwz r4, 0xdc(r3)
/* 80008C44 00005824  38 63 00 08 */	addi r3, r3, 8
/* 80008C48 00005828  38 A5 00 01 */	addi r5, r5, 1
/* 80008C4C 0000582C  28 04 00 00 */	cmplwi r4, 0
/* 80008C50 00005830  41 82 00 28 */	beq lbl_80008C78
/* 80008C54 00005834  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008C58 00005838  28 04 00 00 */	cmplwi r4, 0
/* 80008C5C 0000583C  41 82 00 1C */	beq lbl_80008C78
/* 80008C60 00005840  38 84 FF FF */	addi r4, r4, -1
/* 80008C64 00005844  90 83 00 D8 */	stw r4, 0xd8(r3)
/* 80008C68 00005848  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008C6C 0000584C  28 04 00 00 */	cmplwi r4, 0
/* 80008C70 00005850  40 82 00 08 */	bne lbl_80008C78
/* 80008C74 00005854  90 03 00 D4 */	stw r0, 0xd4(r3)
lbl_80008C78:
/* 80008C78 00005858  80 83 00 DC */	lwz r4, 0xdc(r3)
/* 80008C7C 0000585C  38 63 00 08 */	addi r3, r3, 8
/* 80008C80 00005860  38 A5 00 01 */	addi r5, r5, 1
/* 80008C84 00005864  28 04 00 00 */	cmplwi r4, 0
/* 80008C88 00005868  41 82 00 28 */	beq lbl_80008CB0
/* 80008C8C 0000586C  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008C90 00005870  28 04 00 00 */	cmplwi r4, 0
/* 80008C94 00005874  41 82 00 1C */	beq lbl_80008CB0
/* 80008C98 00005878  38 84 FF FF */	addi r4, r4, -1
/* 80008C9C 0000587C  90 83 00 D8 */	stw r4, 0xd8(r3)
/* 80008CA0 00005880  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008CA4 00005884  28 04 00 00 */	cmplwi r4, 0
/* 80008CA8 00005888  40 82 00 08 */	bne lbl_80008CB0
/* 80008CAC 0000588C  90 03 00 D4 */	stw r0, 0xd4(r3)
lbl_80008CB0:
/* 80008CB0 00005890  80 83 00 DC */	lwz r4, 0xdc(r3)
/* 80008CB4 00005894  38 63 00 08 */	addi r3, r3, 8
/* 80008CB8 00005898  38 A5 00 01 */	addi r5, r5, 1
/* 80008CBC 0000589C  28 04 00 00 */	cmplwi r4, 0
/* 80008CC0 000058A0  41 82 00 28 */	beq lbl_80008CE8
/* 80008CC4 000058A4  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008CC8 000058A8  28 04 00 00 */	cmplwi r4, 0
/* 80008CCC 000058AC  41 82 00 1C */	beq lbl_80008CE8
/* 80008CD0 000058B0  38 84 FF FF */	addi r4, r4, -1
/* 80008CD4 000058B4  90 83 00 D8 */	stw r4, 0xd8(r3)
/* 80008CD8 000058B8  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008CDC 000058BC  28 04 00 00 */	cmplwi r4, 0
/* 80008CE0 000058C0  40 82 00 08 */	bne lbl_80008CE8
/* 80008CE4 000058C4  90 03 00 D4 */	stw r0, 0xd4(r3)
lbl_80008CE8:
/* 80008CE8 000058C8  80 83 00 DC */	lwz r4, 0xdc(r3)
/* 80008CEC 000058CC  38 63 00 08 */	addi r3, r3, 8
/* 80008CF0 000058D0  38 A5 00 01 */	addi r5, r5, 1
/* 80008CF4 000058D4  28 04 00 00 */	cmplwi r4, 0
/* 80008CF8 000058D8  41 82 00 28 */	beq lbl_80008D20
/* 80008CFC 000058DC  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008D00 000058E0  28 04 00 00 */	cmplwi r4, 0
/* 80008D04 000058E4  41 82 00 1C */	beq lbl_80008D20
/* 80008D08 000058E8  38 84 FF FF */	addi r4, r4, -1
/* 80008D0C 000058EC  90 83 00 D8 */	stw r4, 0xd8(r3)
/* 80008D10 000058F0  80 83 00 D8 */	lwz r4, 0xd8(r3)
/* 80008D14 000058F4  28 04 00 00 */	cmplwi r4, 0
/* 80008D18 000058F8  40 82 00 08 */	bne lbl_80008D20
/* 80008D1C 000058FC  90 03 00 D4 */	stw r0, 0xd4(r3)
lbl_80008D20:
/* 80008D20 00005900  38 63 00 08 */	addi r3, r3, 8
/* 80008D24 00005904  38 A5 00 01 */	addi r5, r5, 1
/* 80008D28 00005908  42 00 FE B4 */	bdnz lbl_80008BDC
/* 80008D2C 0000590C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

f64 const lbl_804D7A48 = 4503599627370496;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_80008D30(UNK_PARAMS){
    // clang-format off
    nofralloc
/* 80008D30 00005910  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80008D34 00005914  3C 00 43 30 */	lis r0, 0x4330
/* 80008D38 00005918  80 A4 00 00 */	lwz r5, 0(r4)
/* 80008D3C 0000591C  90 A3 00 00 */	stw r5, 0(r3)
/* 80008D40 00005920  80 A4 00 04 */	lwz r5, 4(r4)
/* 80008D44 00005924  C8 22 80 68 */	lfd f1, lbl_804D7A48(r2)
/* 80008D48 00005928  90 A1 00 14 */	stw r5, 0x14(r1)
/* 80008D4C 0000592C  90 01 00 10 */	stw r0, 0x10(r1)
/* 80008D50 00005930  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 80008D54 00005934  EC 00 08 28 */	fsubs f0, f0, f1
/* 80008D58 00005938  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 80008D5C 0000593C  80 04 00 08 */	lwz r0, 8(r4)
/* 80008D60 00005940  90 03 00 20 */	stw r0, 0x20(r3)
/* 80008D64 00005944  80 04 00 0C */	lwz r0, 0xc(r4)
/* 80008D68 00005948  90 03 00 24 */	stw r0, 0x24(r3)
/* 80008D6C 0000594C  80 04 00 10 */	lwz r0, 0x10(r4)
/* 80008D70 00005950  90 03 00 28 */	stw r0, 0x28(r3)
/* 80008D74 00005954  80 04 00 14 */	lwz r0, 0x14(r4)
/* 80008D78 00005958  90 03 00 2C */	stw r0, 0x2c(r3)
/* 80008D7C 0000595C  80 04 00 18 */	lwz r0, 0x18(r4)
/* 80008D80 00005960  90 03 00 30 */	stw r0, 0x30(r3)
/* 80008D84 00005964  80 04 00 1C */	lwz r0, 0x1c(r4)
/* 80008D88 00005968  90 03 00 38 */	stw r0, 0x38(r3)
/* 80008D8C 0000596C  80 04 00 20 */	lwz r0, 0x20(r4)
/* 80008D90 00005970  90 03 00 3C */	stw r0, 0x3c(r3)
/* 80008D94 00005974  80 04 00 04 */	lwz r0, 4(r4)
/* 80008D98 00005978  90 03 00 08 */	stw r0, 8(r3)
/* 80008D9C 0000597C  38 21 00 18 */	addi r1, r1, 0x18
/* 80008DA0 00005980  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

GXColor const lbl_804D7A50 = { 0 };

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_80008DA4(UNK_PARAMS){
    // clang-format off
    nofralloc
/* 80008DA4 00005984  7C 08 02 A6 */	mflr r0
/* 80008DA8 00005988  90 01 00 04 */	stw r0, 4(r1)
/* 80008DAC 0000598C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80008DB0 00005990  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80008DB4 00005994  3B E4 00 00 */	addi r31, r4, 0
/* 80008DB8 00005998  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80008DBC 0000599C  3B C3 00 00 */	addi r30, r3, 0
/* 80008DC0 000059A0  38 60 00 01 */	li r3, 1
/* 80008DC4 000059A4  80 02 80 70 */	lwz r0, lbl_804D7A50(r2)
/* 80008DC8 000059A8  90 01 00 24 */	stw r0, 0x24(r1)
/* 80008DCC 000059AC  48 33 7F 75 */	bl GXSetColorUpdate
/* 80008DD0 000059B0  38 60 00 00 */	li r3, 0
/* 80008DD4 000059B4  48 33 7F AD */	bl GXSetAlphaUpdate
/* 80008DD8 000059B8  C0 22 80 18 */	lfs f1, lbl_804D79F8(r2)
/* 80008DDC 000059BC  38 81 00 20 */	addi r4, r1, 0x20
/* 80008DE0 000059C0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80008DE4 000059C4  38 60 00 00 */	li r3, 0
/* 80008DE8 000059C8  FC 40 08 90 */	fmr f2, f1
/* 80008DEC 000059CC  FC 60 08 90 */	fmr f3, f1
/* 80008DF0 000059D0  90 01 00 20 */	stw r0, 0x20(r1)
/* 80008DF4 000059D4  FC 80 08 90 */	fmr f4, f1
/* 80008DF8 000059D8  48 33 79 CD */	bl GXSetFog
/* 80008DFC 000059DC  88 1E 00 03 */	lbz r0, 3(r30)
/* 80008E00 000059E0  28 00 00 FF */	cmplwi r0, 0xff
/* 80008E04 000059E4  40 80 00 0C */	bge lbl_80008E10
/* 80008E08 000059E8  38 60 00 01 */	li r3, 1
/* 80008E0C 000059EC  48 00 00 08 */	b lbl_80008E14
lbl_80008E10:
/* 80008E10 000059F0  38 60 00 00 */	li r3, 0
lbl_80008E14:
/* 80008E14 000059F4  38 80 00 04 */	li r4, 4
/* 80008E18 000059F8  38 A0 00 05 */	li r5, 5
/* 80008E1C 000059FC  38 C0 00 05 */	li r6, 5
/* 80008E20 00005A00  48 33 7E 1D */	bl GXSetBlendMode
/* 80008E24 00005A04  38 60 00 04 */	li r3, 4
/* 80008E28 00005A08  38 80 00 00 */	li r4, 0
/* 80008E2C 00005A0C  38 A0 00 00 */	li r5, 0
/* 80008E30 00005A10  38 C0 00 04 */	li r6, 4
/* 80008E34 00005A14  38 E0 00 00 */	li r7, 0
/* 80008E38 00005A18  48 33 76 E5 */	bl GXSetAlphaCompare
/* 80008E3C 00005A1C  88 1E 00 03 */	lbz r0, 3(r30)
/* 80008E40 00005A20  28 00 00 FF */	cmplwi r0, 0xff
/* 80008E44 00005A24  40 80 00 0C */	bge lbl_80008E50
/* 80008E48 00005A28  38 A0 00 00 */	li r5, 0
/* 80008E4C 00005A2C  48 00 00 08 */	b lbl_80008E54
lbl_80008E50:
/* 80008E50 00005A30  38 A0 00 01 */	li r5, 1
lbl_80008E54:
/* 80008E54 00005A34  38 60 00 01 */	li r3, 1
/* 80008E58 00005A38  38 80 00 03 */	li r4, 3
/* 80008E5C 00005A3C  48 33 7F 65 */	bl GXSetZMode
/* 80008E60 00005A40  38 60 00 00 */	li r3, 0
/* 80008E64 00005A44  48 33 7F D5 */	bl GXSetZCompLoc
/* 80008E68 00005A48  38 60 00 00 */	li r3, 0
/* 80008E6C 00005A4C  48 33 3D 0D */	bl GXSetNumTexGens
/* 80008E70 00005A50  38 60 00 00 */	li r3, 0
/* 80008E74 00005A54  38 80 00 00 */	li r4, 0
/* 80008E78 00005A58  48 33 76 A1 */	bl GXSetTevClampMode
/* 80008E7C 00005A5C  38 60 00 01 */	li r3, 1
/* 80008E80 00005A60  48 33 79 11 */	bl GXSetNumTevStages
/* 80008E84 00005A64  38 60 00 00 */	li r3, 0
/* 80008E88 00005A68  38 80 00 FF */	li r4, 0xff
/* 80008E8C 00005A6C  38 A0 00 FF */	li r5, 0xff
/* 80008E90 00005A70  38 C0 00 04 */	li r6, 4
/* 80008E94 00005A74  48 33 77 5D */	bl GXSetTevOrder
/* 80008E98 00005A78  80 1E 00 00 */	lwz r0, 0(r30)
/* 80008E9C 00005A7C  38 81 00 1C */	addi r4, r1, 0x1c
/* 80008EA0 00005A80  38 60 00 01 */	li r3, 1
/* 80008EA4 00005A84  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80008EA8 00005A88  48 33 73 45 */	bl GXSetTevColor
/* 80008EAC 00005A8C  38 60 00 00 */	li r3, 0
/* 80008EB0 00005A90  38 80 00 0F */	li r4, 0xf
/* 80008EB4 00005A94  38 A0 00 0A */	li r5, 0xa
/* 80008EB8 00005A98  38 C0 00 02 */	li r6, 2
/* 80008EBC 00005A9C  38 E0 00 0F */	li r7, 0xf
/* 80008EC0 00005AA0  48 33 70 A9 */	bl GXSetTevColorIn
/* 80008EC4 00005AA4  38 60 00 00 */	li r3, 0
/* 80008EC8 00005AA8  38 80 00 07 */	li r4, 7
/* 80008ECC 00005AAC  38 A0 00 06 */	li r5, 6
/* 80008ED0 00005AB0  38 C0 00 01 */	li r6, 1
/* 80008ED4 00005AB4  38 E0 00 07 */	li r7, 7
/* 80008ED8 00005AB8  48 33 71 11 */	bl GXSetTevAlphaIn
/* 80008EDC 00005ABC  38 60 00 00 */	li r3, 0
/* 80008EE0 00005AC0  38 80 00 00 */	li r4, 0
/* 80008EE4 00005AC4  38 A0 00 00 */	li r5, 0
/* 80008EE8 00005AC8  38 C0 00 00 */	li r6, 0
/* 80008EEC 00005ACC  38 E0 00 01 */	li r7, 1
/* 80008EF0 00005AD0  39 00 00 00 */	li r8, 0
/* 80008EF4 00005AD4  48 33 71 79 */	bl GXSetTevColorOp
/* 80008EF8 00005AD8  38 60 00 00 */	li r3, 0
/* 80008EFC 00005ADC  38 80 00 00 */	li r4, 0
/* 80008F00 00005AE0  38 A0 00 00 */	li r5, 0
/* 80008F04 00005AE4  38 C0 00 00 */	li r6, 0
/* 80008F08 00005AE8  38 E0 00 01 */	li r7, 1
/* 80008F0C 00005AEC  39 00 00 00 */	li r8, 0
/* 80008F10 00005AF0  48 33 72 1D */	bl GXSetTevAlphaOp
/* 80008F14 00005AF4  38 60 00 01 */	li r3, 1
/* 80008F18 00005AF8  48 33 56 45 */	bl GXSetNumChans
/* 80008F1C 00005AFC  80 1F 00 00 */	lwz r0, 0(r31)
/* 80008F20 00005B00  38 81 00 18 */	addi r4, r1, 0x18
/* 80008F24 00005B04  38 60 00 04 */	li r3, 4
/* 80008F28 00005B08  90 01 00 10 */	stw r0, 0x10(r1)
/* 80008F2C 00005B0C  80 01 00 10 */	lwz r0, 0x10(r1)
/* 80008F30 00005B10  90 01 00 18 */	stw r0, 0x18(r1)
/* 80008F34 00005B14  48 33 53 59 */	bl GXSetChanAmbColor
/* 80008F38 00005B18  38 00 00 FF */	li r0, 0xff
/* 80008F3C 00005B1C  98 01 00 10 */	stb r0, 0x10(r1)
/* 80008F40 00005B20  38 81 00 14 */	addi r4, r1, 0x14
/* 80008F44 00005B24  38 60 00 04 */	li r3, 4
/* 80008F48 00005B28  98 01 00 11 */	stb r0, 0x11(r1)
/* 80008F4C 00005B2C  98 01 00 12 */	stb r0, 0x12(r1)
/* 80008F50 00005B30  98 01 00 13 */	stb r0, 0x13(r1)
/* 80008F54 00005B34  80 01 00 10 */	lwz r0, 0x10(r1)
/* 80008F58 00005B38  90 01 00 14 */	stw r0, 0x14(r1)
/* 80008F5C 00005B3C  48 33 54 99 */	bl GXSetChanMatColor
/* 80008F60 00005B40  88 1E 00 03 */	lbz r0, 3(r30)
/* 80008F64 00005B44  28 00 00 FF */	cmplwi r0, 0xff
/* 80008F68 00005B48  40 80 00 28 */	bge lbl_80008F90
/* 80008F6C 00005B4C  38 60 00 04 */	li r3, 4
/* 80008F70 00005B50  38 80 00 00 */	li r4, 0
/* 80008F74 00005B54  38 A0 00 00 */	li r5, 0
/* 80008F78 00005B58  38 C0 00 00 */	li r6, 0
/* 80008F7C 00005B5C  38 E0 00 01 */	li r7, 1
/* 80008F80 00005B60  39 00 00 00 */	li r8, 0
/* 80008F84 00005B64  39 20 00 02 */	li r9, 2
/* 80008F88 00005B68  48 33 56 21 */	bl GXSetChanCtrl
/* 80008F8C 00005B6C  48 00 00 24 */	b lbl_80008FB0
lbl_80008F90:
/* 80008F90 00005B70  38 60 00 04 */	li r3, 4
/* 80008F94 00005B74  38 80 00 01 */	li r4, 1
/* 80008F98 00005B78  38 A0 00 00 */	li r5, 0
/* 80008F9C 00005B7C  38 C0 00 00 */	li r6, 0
/* 80008FA0 00005B80  38 E0 00 01 */	li r7, 1
/* 80008FA4 00005B84  39 00 00 02 */	li r8, 2
/* 80008FA8 00005B88  39 20 00 02 */	li r9, 2
/* 80008FAC 00005B8C  48 33 55 FD */	bl GXSetChanCtrl
lbl_80008FB0:
/* 80008FB0 00005B90  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80008FB4 00005B94  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80008FB8 00005B98  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80008FBC 00005B9C  38 21 00 30 */	addi r1, r1, 0x30
/* 80008FC0 00005BA0  7C 08 03 A6 */	mtlr r0
/* 80008FC4 00005BA4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

f32 const lbl_804D7A54 = -1;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_80008FC8(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 80008FC8 00005BA8  7C 08 02 A6 */	mflr r0
/* 80008FCC 00005BAC  3C E0 80 3C */	lis r7, lbl_803B9880@ha
/* 80008FD0 00005BB0  90 01 00 04 */	stw r0, 4(r1)
/* 80008FD4 00005BB4  94 21 FE A0 */	stwu r1, -0x160(r1)
/* 80008FD8 00005BB8  DB E1 01 58 */	stfd f31, 0x158(r1)
/* 80008FDC 00005BBC  DB C1 01 50 */	stfd f30, 0x150(r1)
/* 80008FE0 00005BC0  FF C0 08 90 */	fmr f30, f1
/* 80008FE4 00005BC4  BF 61 01 3C */	stmw r27, 0x13c(r1)
/* 80008FE8 00005BC8  3B 63 00 00 */	addi r27, r3, 0
/* 80008FEC 00005BCC  3B 84 00 00 */	addi r28, r4, 0
/* 80008FF0 00005BD0  3B A5 00 00 */	addi r29, r5, 0
/* 80008FF4 00005BD4  3B C6 00 00 */	addi r30, r6, 0
/* 80008FF8 00005BD8  3B E7 98 80 */	addi r31, r7, lbl_803B9880@l
/* 80008FFC 00005BDC  38 60 FF FF */	li r3, -1
/* 80009000 00005BE0  48 35 8F C5 */	bl HSD_StateInvalidate
/* 80009004 00005BE4  48 35 94 D5 */	bl HSD_StateInitTev
/* 80009008 00005BE8  38 7D 00 00 */	addi r3, r29, 0
/* 8000900C 00005BEC  38 9E 00 00 */	addi r4, r30, 0
/* 80009010 00005BF0  4B FF FD 95 */	bl lbColl_80008DA4
/* 80009014 00005BF4  48 36 12 75 */	bl HSD_CObjGetCurrent
/* 80009018 00005BF8  38 81 01 04 */	addi r4, r1, 0x104
/* 8000901C 00005BFC  48 36 05 D5 */	bl HSD_CObjGetViewingMtx
/* 80009020 00005C00  FC 20 F0 90 */	fmr f1, f30
/* 80009024 00005C04  38 61 00 A4 */	addi r3, r1, 0xa4
/* 80009028 00005C08  FC 40 F0 90 */	fmr f2, f30
/* 8000902C 00005C0C  FC 60 F0 90 */	fmr f3, f30
/* 80009030 00005C10  48 33 96 39 */	bl PSMTXScale
/* 80009034 00005C14  C0 3B 00 00 */	lfs f1, 0(r27)
/* 80009038 00005C18  C0 1C 00 00 */	lfs f0, 0(r28)
/* 8000903C 00005C1C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80009040 00005C20  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 80009044 00005C24  C0 3B 00 04 */	lfs f1, 4(r27)
/* 80009048 00005C28  C0 1C 00 04 */	lfs f0, 4(r28)
/* 8000904C 00005C2C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80009050 00005C30  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 80009054 00005C34  C0 3B 00 08 */	lfs f1, 8(r27)
/* 80009058 00005C38  C0 1C 00 08 */	lfs f0, 8(r28)
/* 8000905C 00005C3C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80009060 00005C40  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 80009064 00005C44  C0 21 00 38 */	lfs f1, 0x38(r1)
/* 80009068 00005C48  C0 61 00 40 */	lfs f3, 0x40(r1)
/* 8000906C 00005C4C  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 80009070 00005C50  EC 41 00 72 */	fmuls f2, f1, f1
/* 80009074 00005C54  EC 63 00 F2 */	fmuls f3, f3, f3
/* 80009078 00005C58  EC 20 00 32 */	fmuls f1, f0, f0
/* 8000907C 00005C5C  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80009080 00005C60  EC 22 08 2A */	fadds f1, f2, f1
/* 80009084 00005C64  EF E3 08 2A */	fadds f31, f3, f1
/* 80009088 00005C68  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8000908C 00005C6C  40 81 00 50 */	ble lbl_800090DC
/* 80009090 00005C70  FC 20 F8 34 */	frsqrte f1, f31
/* 80009094 00005C74  C8 62 80 38 */	lfd f3, lbl_804D7A18(r2)
/* 80009098 00005C78  C8 42 80 40 */	lfd f2, lbl_804D7A20(r2)
/* 8000909C 00005C7C  FC 01 00 72 */	fmul f0, f1, f1
/* 800090A0 00005C80  FC 23 00 72 */	fmul f1, f3, f1
/* 800090A4 00005C84  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 800090A8 00005C88  FC 21 00 32 */	fmul f1, f1, f0
/* 800090AC 00005C8C  FC 01 00 72 */	fmul f0, f1, f1
/* 800090B0 00005C90  FC 23 00 72 */	fmul f1, f3, f1
/* 800090B4 00005C94  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 800090B8 00005C98  FC 21 00 32 */	fmul f1, f1, f0
/* 800090BC 00005C9C  FC 01 00 72 */	fmul f0, f1, f1
/* 800090C0 00005CA0  FC 23 00 72 */	fmul f1, f3, f1
/* 800090C4 00005CA4  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 800090C8 00005CA8  FC 01 00 32 */	fmul f0, f1, f0
/* 800090CC 00005CAC  FC 1F 00 32 */	fmul f0, f31, f0
/* 800090D0 00005CB0  FC 00 00 18 */	frsp f0, f0
/* 800090D4 00005CB4  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800090D8 00005CB8  C3 E1 00 1C */	lfs f31, 0x1c(r1)
lbl_800090DC:
/* 800090DC 00005CBC  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 800090E0 00005CC0  FC 20 F8 90 */	fmr f1, f31
/* 800090E4 00005CC4  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800090E8 00005CC8  40 80 00 18 */	bge lbl_80009100
/* 800090EC 00005CCC  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 800090F0 00005CD0  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800090F4 00005CD4  40 81 00 0C */	ble lbl_80009100
/* 800090F8 00005CD8  38 00 00 01 */	li r0, 1
/* 800090FC 00005CDC  48 00 00 08 */	b lbl_80009104
lbl_80009100:
/* 80009100 00005CE0  38 00 00 00 */	li r0, 0
lbl_80009104:
/* 80009104 00005CE4  2C 00 00 00 */	cmpwi r0, 0
/* 80009108 00005CE8  40 82 00 94 */	bne lbl_8000919C
/* 8000910C 00005CEC  C0 41 00 38 */	lfs f2, 0x38(r1)
/* 80009110 00005CF0  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009114 00005CF4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009118 00005CF8  40 80 00 18 */	bge lbl_80009130
/* 8000911C 00005CFC  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 80009120 00005D00  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009124 00005D04  40 81 00 0C */	ble lbl_80009130
/* 80009128 00005D08  38 00 00 01 */	li r0, 1
/* 8000912C 00005D0C  48 00 00 08 */	b lbl_80009134
lbl_80009130:
/* 80009130 00005D10  38 00 00 00 */	li r0, 0
lbl_80009134:
/* 80009134 00005D14  2C 00 00 00 */	cmpwi r0, 0
/* 80009138 00005D18  41 82 00 B0 */	beq lbl_800091E8
/* 8000913C 00005D1C  C0 41 00 3C */	lfs f2, 0x3c(r1)
/* 80009140 00005D20  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009144 00005D24  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009148 00005D28  40 80 00 18 */	bge lbl_80009160
/* 8000914C 00005D2C  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 80009150 00005D30  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009154 00005D34  40 81 00 0C */	ble lbl_80009160
/* 80009158 00005D38  38 00 00 01 */	li r0, 1
/* 8000915C 00005D3C  48 00 00 08 */	b lbl_80009164
lbl_80009160:
/* 80009160 00005D40  38 00 00 00 */	li r0, 0
lbl_80009164:
/* 80009164 00005D44  2C 00 00 00 */	cmpwi r0, 0
/* 80009168 00005D48  41 82 00 80 */	beq lbl_800091E8
/* 8000916C 00005D4C  C0 41 00 40 */	lfs f2, 0x40(r1)
/* 80009170 00005D50  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009174 00005D54  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009178 00005D58  40 80 00 18 */	bge lbl_80009190
/* 8000917C 00005D5C  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 80009180 00005D60  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009184 00005D64  40 81 00 0C */	ble lbl_80009190
/* 80009188 00005D68  38 00 00 01 */	li r0, 1
/* 8000918C 00005D6C  48 00 00 08 */	b lbl_80009194
lbl_80009190:
/* 80009190 00005D70  38 00 00 00 */	li r0, 0
lbl_80009194:
/* 80009194 00005D74  2C 00 00 00 */	cmpwi r0, 0
/* 80009198 00005D78  41 82 00 50 */	beq lbl_800091E8
lbl_8000919C:
/* 8000919C 00005D7C  38 61 00 44 */	addi r3, r1, 0x44
/* 800091A0 00005D80  48 33 90 05 */	bl PSMTXIdentity
/* 800091A4 00005D84  C0 42 80 74 */	lfs f2, lbl_804D7A54(r2)
/* 800091A8 00005D88  38 61 00 44 */	addi r3, r1, 0x44
/* 800091AC 00005D8C  C0 22 80 18 */	lfs f1, lbl_804D79F8(r2)
/* 800091B0 00005D90  38 81 00 A4 */	addi r4, r1, 0xa4
/* 800091B4 00005D94  D0 41 00 44 */	stfs f2, 0x44(r1)
/* 800091B8 00005D98  C0 02 80 28 */	lfs f0, lbl_804D7A08(r2)
/* 800091BC 00005D9C  38 A1 00 D4 */	addi r5, r1, 0xd4
/* 800091C0 00005DA0  D0 21 00 54 */	stfs f1, 0x54(r1)
/* 800091C4 00005DA4  D0 21 00 64 */	stfs f1, 0x64(r1)
/* 800091C8 00005DA8  D0 21 00 48 */	stfs f1, 0x48(r1)
/* 800091CC 00005DAC  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 800091D0 00005DB0  D0 21 00 68 */	stfs f1, 0x68(r1)
/* 800091D4 00005DB4  D0 21 00 4C */	stfs f1, 0x4c(r1)
/* 800091D8 00005DB8  D0 21 00 5C */	stfs f1, 0x5c(r1)
/* 800091DC 00005DBC  D0 41 00 6C */	stfs f2, 0x6c(r1)
/* 800091E0 00005DC0  48 33 90 25 */	bl PSMTXConcat
/* 800091E4 00005DC4  48 00 01 AC */	b lbl_80009390
lbl_800091E8:
/* 800091E8 00005DC8  FC 40 F0 90 */	fmr f2, f30
/* 800091EC 00005DCC  38 61 00 74 */	addi r3, r1, 0x74
/* 800091F0 00005DD0  FC 60 F0 90 */	fmr f3, f30
/* 800091F4 00005DD4  48 33 94 75 */	bl PSMTXScale
/* 800091F8 00005DD8  C0 21 00 38 */	lfs f1, 0x38(r1)
/* 800091FC 00005DDC  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009200 00005DE0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80009204 00005DE4  40 80 00 18 */	bge lbl_8000921C
/* 80009208 00005DE8  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 8000920C 00005DEC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80009210 00005DF0  40 81 00 0C */	ble lbl_8000921C
/* 80009214 00005DF4  38 00 00 01 */	li r0, 1
/* 80009218 00005DF8  48 00 00 08 */	b lbl_80009220
lbl_8000921C:
/* 8000921C 00005DFC  38 00 00 00 */	li r0, 0
lbl_80009220:
/* 80009220 00005E00  2C 00 00 00 */	cmpwi r0, 0
/* 80009224 00005E04  41 82 00 4C */	beq lbl_80009270
/* 80009228 00005E08  C0 41 00 3C */	lfs f2, 0x3c(r1)
/* 8000922C 00005E0C  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009230 00005E10  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009234 00005E14  40 80 00 18 */	bge lbl_8000924C
/* 80009238 00005E18  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 8000923C 00005E1C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009240 00005E20  40 81 00 0C */	ble lbl_8000924C
/* 80009244 00005E24  38 00 00 01 */	li r0, 1
/* 80009248 00005E28  48 00 00 08 */	b lbl_80009250
lbl_8000924C:
/* 8000924C 00005E2C  38 00 00 00 */	li r0, 0
lbl_80009250:
/* 80009250 00005E30  2C 00 00 00 */	cmpwi r0, 0
/* 80009254 00005E34  41 82 00 1C */	beq lbl_80009270
/* 80009258 00005E38  C0 21 00 40 */	lfs f1, 0x40(r1)
/* 8000925C 00005E3C  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80009260 00005E40  D0 21 00 2C */	stfs f1, 0x2c(r1)
/* 80009264 00005E44  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80009268 00005E48  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 8000926C 00005E4C  48 00 00 1C */	b lbl_80009288
lbl_80009270:
/* 80009270 00005E50  C0 41 00 3C */	lfs f2, 0x3c(r1)
/* 80009274 00005E54  FC 20 08 50 */	fneg f1, f1
/* 80009278 00005E58  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 8000927C 00005E5C  D0 41 00 2C */	stfs f2, 0x2c(r1)
/* 80009280 00005E60  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 80009284 00005E64  D0 01 00 34 */	stfs f0, 0x34(r1)
lbl_80009288:
/* 80009288 00005E68  38 61 00 38 */	addi r3, r1, 0x38
/* 8000928C 00005E6C  38 83 00 00 */	addi r4, r3, 0
/* 80009290 00005E70  48 33 9B 29 */	bl PSVECNormalize
/* 80009294 00005E74  38 61 00 2C */	addi r3, r1, 0x2c
/* 80009298 00005E78  38 83 00 00 */	addi r4, r3, 0
/* 8000929C 00005E7C  48 33 9B 1D */	bl PSVECNormalize
/* 800092A0 00005E80  38 61 00 38 */	addi r3, r1, 0x38
/* 800092A4 00005E84  38 81 00 2C */	addi r4, r1, 0x2c
/* 800092A8 00005E88  38 A1 00 20 */	addi r5, r1, 0x20
/* 800092AC 00005E8C  48 33 9B AD */	bl PSVECCrossProduct
/* 800092B0 00005E90  38 61 00 44 */	addi r3, r1, 0x44
/* 800092B4 00005E94  48 33 8E F1 */	bl PSMTXIdentity
/* 800092B8 00005E98  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 800092BC 00005E9C  38 61 00 44 */	addi r3, r1, 0x44
/* 800092C0 00005EA0  38 81 00 A4 */	addi r4, r1, 0xa4
/* 800092C4 00005EA4  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 800092C8 00005EA8  38 A1 00 D4 */	addi r5, r1, 0xd4
/* 800092CC 00005EAC  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 800092D0 00005EB0  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 800092D4 00005EB4  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 800092D8 00005EB8  D0 01 00 64 */	stfs f0, 0x64(r1)
/* 800092DC 00005EBC  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 800092E0 00005EC0  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 800092E4 00005EC4  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 800092E8 00005EC8  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 800092EC 00005ECC  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 800092F0 00005ED0  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 800092F4 00005ED4  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 800092F8 00005ED8  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 800092FC 00005EDC  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 80009300 00005EE0  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 80009304 00005EE4  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80009308 00005EE8  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 8000930C 00005EEC  48 33 8E F9 */	bl PSMTXConcat
/* 80009310 00005EF0  38 81 00 74 */	addi r4, r1, 0x74
/* 80009314 00005EF4  38 A4 00 00 */	addi r5, r4, 0
/* 80009318 00005EF8  38 61 00 44 */	addi r3, r1, 0x44
/* 8000931C 00005EFC  48 33 8E E9 */	bl PSMTXConcat
/* 80009320 00005F00  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 80009324 00005F04  38 81 00 A4 */	addi r4, r1, 0xa4
/* 80009328 00005F08  38 A4 00 00 */	addi r5, r4, 0
/* 8000932C 00005F0C  FC 00 00 50 */	fneg f0, f0
/* 80009330 00005F10  38 61 00 44 */	addi r3, r1, 0x44
/* 80009334 00005F14  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 80009338 00005F18  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 8000933C 00005F1C  FC 00 00 50 */	fneg f0, f0
/* 80009340 00005F20  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 80009344 00005F24  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 80009348 00005F28  FC 00 00 50 */	fneg f0, f0
/* 8000934C 00005F2C  D0 01 00 64 */	stfs f0, 0x64(r1)
/* 80009350 00005F30  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80009354 00005F34  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 80009358 00005F38  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 8000935C 00005F3C  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 80009360 00005F40  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 80009364 00005F44  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 80009368 00005F48  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 8000936C 00005F4C  FC 00 00 50 */	fneg f0, f0
/* 80009370 00005F50  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 80009374 00005F54  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 80009378 00005F58  FC 00 00 50 */	fneg f0, f0
/* 8000937C 00005F5C  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 80009380 00005F60  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80009384 00005F64  FC 00 00 50 */	fneg f0, f0
/* 80009388 00005F68  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 8000938C 00005F6C  48 33 8E 79 */	bl PSMTXConcat
lbl_80009390:
/* 80009390 00005F70  C0 3B 00 00 */	lfs f1, 0(r27)
/* 80009394 00005F74  38 61 00 44 */	addi r3, r1, 0x44
/* 80009398 00005F78  C0 5B 00 04 */	lfs f2, 4(r27)
/* 8000939C 00005F7C  C0 7B 00 08 */	lfs f3, 8(r27)
/* 800093A0 00005F80  48 33 92 95 */	bl PSMTXTrans
/* 800093A4 00005F84  38 81 00 D4 */	addi r4, r1, 0xd4
/* 800093A8 00005F88  38 A4 00 00 */	addi r5, r4, 0
/* 800093AC 00005F8C  38 61 00 44 */	addi r3, r1, 0x44
/* 800093B0 00005F90  48 33 8E 55 */	bl PSMTXConcat
/* 800093B4 00005F94  C0 3C 00 00 */	lfs f1, 0(r28)
/* 800093B8 00005F98  38 61 00 44 */	addi r3, r1, 0x44
/* 800093BC 00005F9C  C0 5C 00 04 */	lfs f2, 4(r28)
/* 800093C0 00005FA0  C0 7C 00 08 */	lfs f3, 8(r28)
/* 800093C4 00005FA4  48 33 92 71 */	bl PSMTXTrans
/* 800093C8 00005FA8  38 81 00 A4 */	addi r4, r1, 0xa4
/* 800093CC 00005FAC  38 A4 00 00 */	addi r5, r4, 0
/* 800093D0 00005FB0  38 61 00 44 */	addi r3, r1, 0x44
/* 800093D4 00005FB4  48 33 8E 31 */	bl PSMTXConcat
/* 800093D8 00005FB8  C0 7B 00 00 */	lfs f3, 0(r27)
/* 800093DC 00005FBC  38 61 00 44 */	addi r3, r1, 0x44
/* 800093E0 00005FC0  C0 5C 00 00 */	lfs f2, 0(r28)
/* 800093E4 00005FC4  C0 3B 00 04 */	lfs f1, 4(r27)
/* 800093E8 00005FC8  C0 1C 00 04 */	lfs f0, 4(r28)
/* 800093EC 00005FCC  EC 83 10 2A */	fadds f4, f3, f2
/* 800093F0 00005FD0  C8 A2 80 38 */	lfd f5, lbl_804D7A18(r2)
/* 800093F4 00005FD4  EC 61 00 2A */	fadds f3, f1, f0
/* 800093F8 00005FD8  C0 5B 00 08 */	lfs f2, 8(r27)
/* 800093FC 00005FDC  C0 1C 00 08 */	lfs f0, 8(r28)
/* 80009400 00005FE0  FC 25 01 32 */	fmul f1, f5, f4
/* 80009404 00005FE4  EC 02 00 2A */	fadds f0, f2, f0
/* 80009408 00005FE8  FC 45 00 F2 */	fmul f2, f5, f3
/* 8000940C 00005FEC  FC 65 00 32 */	fmul f3, f5, f0
/* 80009410 00005FF0  FC 20 08 18 */	frsp f1, f1
/* 80009414 00005FF4  FC 40 10 18 */	frsp f2, f2
/* 80009418 00005FF8  FC 60 18 18 */	frsp f3, f3
/* 8000941C 00005FFC  48 33 92 19 */	bl PSMTXTrans
/* 80009420 00006000  38 81 00 74 */	addi r4, r1, 0x74
/* 80009424 00006004  38 A4 00 00 */	addi r5, r4, 0
/* 80009428 00006008  38 61 00 44 */	addi r3, r1, 0x44
/* 8000942C 0000600C  48 33 8D D9 */	bl PSMTXConcat
/* 80009430 00006010  38 60 00 02 */	li r3, 2
/* 80009434 00006014  48 33 3F 1D */	bl GXSetCullMode
/* 80009438 00006018  48 33 2F 91 */	bl GXClearVtxDesc
/* 8000943C 0000601C  38 9F 00 C0 */	addi r4, r31, 0xc0
/* 80009440 00006020  38 60 00 09 */	li r3, 9
/* 80009444 00006024  38 A0 00 06 */	li r5, 6
/* 80009448 00006028  48 33 33 C5 */	bl GXSetArray
/* 8000944C 0000602C  38 9F 02 60 */	addi r4, r31, 0x260
/* 80009450 00006030  38 60 00 0A */	li r3, 0xa
/* 80009454 00006034  38 A0 00 06 */	li r5, 6
/* 80009458 00006038  48 33 33 B5 */	bl GXSetArray
/* 8000945C 0000603C  38 60 00 09 */	li r3, 9
/* 80009460 00006040  38 80 00 02 */	li r4, 2
/* 80009464 00006044  48 33 2A 9D */	bl GXSetVtxDesc
/* 80009468 00006048  38 60 00 00 */	li r3, 0
/* 8000946C 0000604C  38 80 00 09 */	li r4, 9
/* 80009470 00006050  38 A0 00 01 */	li r5, 1
/* 80009474 00006054  38 C0 00 03 */	li r6, 3
/* 80009478 00006058  38 E0 00 0E */	li r7, 0xe
/* 8000947C 0000605C  48 33 2F 99 */	bl GXSetVtxAttrFmt
/* 80009480 00006060  38 60 00 0A */	li r3, 0xa
/* 80009484 00006064  38 80 00 02 */	li r4, 2
/* 80009488 00006068  48 33 2A 79 */	bl GXSetVtxDesc
/* 8000948C 0000606C  38 60 00 00 */	li r3, 0
/* 80009490 00006070  38 80 00 0A */	li r4, 0xa
/* 80009494 00006074  38 A0 00 00 */	li r5, 0
/* 80009498 00006078  38 C0 00 03 */	li r6, 3
/* 8000949C 0000607C  38 E0 00 0E */	li r7, 0xe
/* 800094A0 00006080  48 33 2F 75 */	bl GXSetVtxAttrFmt
/* 800094A4 00006084  38 81 00 D4 */	addi r4, r1, 0xd4
/* 800094A8 00006088  38 A4 00 00 */	addi r5, r4, 0
/* 800094AC 0000608C  38 61 01 04 */	addi r3, r1, 0x104
/* 800094B0 00006090  48 33 8D 55 */	bl PSMTXConcat
/* 800094B4 00006094  38 61 00 D4 */	addi r3, r1, 0xd4
/* 800094B8 00006098  38 80 00 00 */	li r4, 0
/* 800094BC 0000609C  48 33 7F D9 */	bl GXLoadPosMtxImm
/* 800094C0 000060A0  38 61 00 D4 */	addi r3, r1, 0xd4
/* 800094C4 000060A4  38 83 00 00 */	addi r4, r3, 0
/* 800094C8 000060A8  48 36 FE 49 */	bl HSD_MtxInverse
/* 800094CC 000060AC  38 61 00 D4 */	addi r3, r1, 0xd4
/* 800094D0 000060B0  38 83 00 00 */	addi r4, r3, 0
/* 800094D4 000060B4  48 33 8D FD */	bl PSMTXTranspose
/* 800094D8 000060B8  38 61 00 D4 */	addi r3, r1, 0xd4
/* 800094DC 000060BC  38 80 00 00 */	li r4, 0
/* 800094E0 000060C0  48 33 7F F1 */	bl GXLoadNrmMtxImm
/* 800094E4 000060C4  38 7F 04 00 */	addi r3, r31, 0x400
/* 800094E8 000060C8  38 80 01 20 */	li r4, 0x120
/* 800094EC 000060CC  48 33 7B ED */	bl GXCallDisplayList
/* 800094F0 000060D0  48 33 2E D9 */	bl GXClearVtxDesc
/* 800094F4 000060D4  38 9F 00 C0 */	addi r4, r31, 0xc0
/* 800094F8 000060D8  38 60 00 09 */	li r3, 9
/* 800094FC 000060DC  38 A0 00 06 */	li r5, 6
/* 80009500 000060E0  48 33 33 0D */	bl GXSetArray
/* 80009504 000060E4  38 9F 02 60 */	addi r4, r31, 0x260
/* 80009508 000060E8  38 60 00 0A */	li r3, 0xa
/* 8000950C 000060EC  38 A0 00 06 */	li r5, 6
/* 80009510 000060F0  48 33 32 FD */	bl GXSetArray
/* 80009514 000060F4  38 60 00 09 */	li r3, 9
/* 80009518 000060F8  38 80 00 02 */	li r4, 2
/* 8000951C 000060FC  48 33 29 E5 */	bl GXSetVtxDesc
/* 80009520 00006100  38 60 00 00 */	li r3, 0
/* 80009524 00006104  38 80 00 09 */	li r4, 9
/* 80009528 00006108  38 A0 00 01 */	li r5, 1
/* 8000952C 0000610C  38 C0 00 03 */	li r6, 3
/* 80009530 00006110  38 E0 00 0E */	li r7, 0xe
/* 80009534 00006114  48 33 2E E1 */	bl GXSetVtxAttrFmt
/* 80009538 00006118  38 60 00 0A */	li r3, 0xa
/* 8000953C 0000611C  38 80 00 02 */	li r4, 2
/* 80009540 00006120  48 33 29 C1 */	bl GXSetVtxDesc
/* 80009544 00006124  38 60 00 00 */	li r3, 0
/* 80009548 00006128  38 80 00 0A */	li r4, 0xa
/* 8000954C 0000612C  38 A0 00 00 */	li r5, 0
/* 80009550 00006130  38 C0 00 03 */	li r6, 3
/* 80009554 00006134  38 E0 00 0E */	li r7, 0xe
/* 80009558 00006138  48 33 2E BD */	bl GXSetVtxAttrFmt
/* 8000955C 0000613C  38 81 00 A4 */	addi r4, r1, 0xa4
/* 80009560 00006140  38 A4 00 00 */	addi r5, r4, 0
/* 80009564 00006144  38 61 01 04 */	addi r3, r1, 0x104
/* 80009568 00006148  48 33 8C 9D */	bl PSMTXConcat
/* 8000956C 0000614C  38 61 00 A4 */	addi r3, r1, 0xa4
/* 80009570 00006150  38 80 00 00 */	li r4, 0
/* 80009574 00006154  48 33 7F 21 */	bl GXLoadPosMtxImm
/* 80009578 00006158  38 61 00 A4 */	addi r3, r1, 0xa4
/* 8000957C 0000615C  38 83 00 00 */	addi r4, r3, 0
/* 80009580 00006160  48 36 FD 91 */	bl HSD_MtxInverse
/* 80009584 00006164  38 61 00 A4 */	addi r3, r1, 0xa4
/* 80009588 00006168  38 83 00 00 */	addi r4, r3, 0
/* 8000958C 0000616C  48 33 8D 45 */	bl PSMTXTranspose
/* 80009590 00006170  38 61 00 A4 */	addi r3, r1, 0xa4
/* 80009594 00006174  38 80 00 00 */	li r4, 0
/* 80009598 00006178  48 33 7F 39 */	bl GXLoadNrmMtxImm
/* 8000959C 0000617C  38 7F 04 00 */	addi r3, r31, 0x400
/* 800095A0 00006180  38 80 01 20 */	li r4, 0x120
/* 800095A4 00006184  48 33 7B 35 */	bl GXCallDisplayList
/* 800095A8 00006188  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 800095AC 0000618C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800095B0 00006190  40 80 00 18 */	bge lbl_800095C8
/* 800095B4 00006194  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 800095B8 00006198  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800095BC 0000619C  40 81 00 0C */	ble lbl_800095C8
/* 800095C0 000061A0  38 00 00 01 */	li r0, 1
/* 800095C4 000061A4  48 00 00 08 */	b lbl_800095CC
lbl_800095C8:
/* 800095C8 000061A8  38 00 00 00 */	li r0, 0
lbl_800095CC:
/* 800095CC 000061AC  2C 00 00 00 */	cmpwi r0, 0
/* 800095D0 000061B0  40 82 00 BC */	bne lbl_8000968C
/* 800095D4 000061B4  48 33 2D F5 */	bl GXClearVtxDesc
/* 800095D8 000061B8  38 9F 05 20 */	addi r4, r31, 0x520
/* 800095DC 000061BC  38 60 00 09 */	li r3, 9
/* 800095E0 000061C0  38 A0 00 06 */	li r5, 6
/* 800095E4 000061C4  48 33 32 29 */	bl GXSetArray
/* 800095E8 000061C8  38 9F 06 40 */	addi r4, r31, 0x640
/* 800095EC 000061CC  38 60 00 0A */	li r3, 0xa
/* 800095F0 000061D0  38 A0 00 06 */	li r5, 6
/* 800095F4 000061D4  48 33 32 19 */	bl GXSetArray
/* 800095F8 000061D8  38 60 00 09 */	li r3, 9
/* 800095FC 000061DC  38 80 00 02 */	li r4, 2
/* 80009600 000061E0  48 33 29 01 */	bl GXSetVtxDesc
/* 80009604 000061E4  38 60 00 00 */	li r3, 0
/* 80009608 000061E8  38 80 00 09 */	li r4, 9
/* 8000960C 000061EC  38 A0 00 01 */	li r5, 1
/* 80009610 000061F0  38 C0 00 03 */	li r6, 3
/* 80009614 000061F4  38 E0 00 0E */	li r7, 0xe
/* 80009618 000061F8  48 33 2D FD */	bl GXSetVtxAttrFmt
/* 8000961C 000061FC  38 60 00 0A */	li r3, 0xa
/* 80009620 00006200  38 80 00 02 */	li r4, 2
/* 80009624 00006204  48 33 28 DD */	bl GXSetVtxDesc
/* 80009628 00006208  38 60 00 00 */	li r3, 0
/* 8000962C 0000620C  38 80 00 0A */	li r4, 0xa
/* 80009630 00006210  38 A0 00 00 */	li r5, 0
/* 80009634 00006214  38 C0 00 03 */	li r6, 3
/* 80009638 00006218  38 E0 00 06 */	li r7, 6
/* 8000963C 0000621C  48 33 2D D9 */	bl GXSetVtxAttrFmt
/* 80009640 00006220  38 81 00 74 */	addi r4, r1, 0x74
/* 80009644 00006224  38 A4 00 00 */	addi r5, r4, 0
/* 80009648 00006228  38 61 01 04 */	addi r3, r1, 0x104
/* 8000964C 0000622C  48 33 8B B9 */	bl PSMTXConcat
/* 80009650 00006230  38 61 00 74 */	addi r3, r1, 0x74
/* 80009654 00006234  38 80 00 00 */	li r4, 0
/* 80009658 00006238  48 33 7E 3D */	bl GXLoadPosMtxImm
/* 8000965C 0000623C  38 61 00 74 */	addi r3, r1, 0x74
/* 80009660 00006240  38 83 00 00 */	addi r4, r3, 0
/* 80009664 00006244  48 36 FC AD */	bl HSD_MtxInverse
/* 80009668 00006248  38 61 00 74 */	addi r3, r1, 0x74
/* 8000966C 0000624C  38 83 00 00 */	addi r4, r3, 0
/* 80009670 00006250  48 33 8C 61 */	bl PSMTXTranspose
/* 80009674 00006254  38 61 00 74 */	addi r3, r1, 0x74
/* 80009678 00006258  38 80 00 00 */	li r4, 0
/* 8000967C 0000625C  48 33 7E 55 */	bl GXLoadNrmMtxImm
/* 80009680 00006260  38 7F 06 A0 */	addi r3, r31, 0x6a0
/* 80009684 00006264  38 80 00 A0 */	li r4, 0xa0
/* 80009688 00006268  48 33 7A 51 */	bl GXCallDisplayList
lbl_8000968C:
/* 8000968C 0000626C  38 60 FF FF */	li r3, -1
/* 80009690 00006270  48 35 89 35 */	bl HSD_StateInvalidate
/* 80009694 00006274  48 35 8E 45 */	bl HSD_StateInitTev
/* 80009698 00006278  BB 61 01 3C */	lmw r27, 0x13c(r1)
/* 8000969C 0000627C  80 01 01 64 */	lwz r0, 0x164(r1)
/* 800096A0 00006280  CB E1 01 58 */	lfd f31, 0x158(r1)
/* 800096A4 00006284  CB C1 01 50 */	lfd f30, 0x150(r1)
/* 800096A8 00006288  38 21 01 60 */	addi r1, r1, 0x160
/* 800096AC 0000628C  7C 08 03 A6 */	mtlr r0
/* 800096B0 00006290  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void lbColl_800096B4(MtxPtr, UNK_T, UNK_T, UNK_T, UNK_T, f32)
{ // clang-format off
    nofralloc
/* 800096B4 00006294  7C 08 02 A6 */	mflr r0
/* 800096B8 00006298  3D 00 80 3C */	lis r8, lbl_803B9880@ha
/* 800096BC 0000629C  90 01 00 04 */	stw r0, 4(r1)
/* 800096C0 000062A0  94 21 FE A0 */	stwu r1, -0x160(r1)
/* 800096C4 000062A4  DB E1 01 58 */	stfd f31, 0x158(r1)
/* 800096C8 000062A8  DB C1 01 50 */	stfd f30, 0x150(r1)
/* 800096CC 000062AC  FF C0 08 90 */	fmr f30, f1
/* 800096D0 000062B0  BF 41 01 38 */	stmw r26, 0x138(r1)
/* 800096D4 000062B4  3B 43 00 00 */	addi r26, r3, 0
/* 800096D8 000062B8  3B 64 00 00 */	addi r27, r4, 0
/* 800096DC 000062BC  3B 85 00 00 */	addi r28, r5, 0
/* 800096E0 000062C0  3B A6 00 00 */	addi r29, r6, 0
/* 800096E4 000062C4  3B C7 00 00 */	addi r30, r7, 0
/* 800096E8 000062C8  3B E8 98 80 */	addi r31, r8, lbl_803B9880@l
/* 800096EC 000062CC  38 60 FF FF */	li r3, -1
/* 800096F0 000062D0  48 35 88 D5 */	bl HSD_StateInvalidate
/* 800096F4 000062D4  48 35 8D E5 */	bl HSD_StateInitTev
/* 800096F8 000062D8  38 7D 00 00 */	addi r3, r29, 0
/* 800096FC 000062DC  38 9E 00 00 */	addi r4, r30, 0
/* 80009700 000062E0  4B FF F6 A5 */	bl lbColl_80008DA4
/* 80009704 000062E4  48 36 0B 85 */	bl HSD_CObjGetCurrent
/* 80009708 000062E8  38 81 01 08 */	addi r4, r1, 0x108
/* 8000970C 000062EC  48 35 FE E5 */	bl HSD_CObjGetViewingMtx
/* 80009710 000062F0  FC 20 F0 90 */	fmr f1, f30
/* 80009714 000062F4  38 61 00 A8 */	addi r3, r1, 0xa8
/* 80009718 000062F8  FC 40 F0 90 */	fmr f2, f30
/* 8000971C 000062FC  FC 60 F0 90 */	fmr f3, f30
/* 80009720 00006300  48 33 8F 49 */	bl PSMTXScale
/* 80009724 00006304  C0 3B 00 00 */	lfs f1, 0(r27)
/* 80009728 00006308  C0 1C 00 00 */	lfs f0, 0(r28)
/* 8000972C 0000630C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80009730 00006310  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 80009734 00006314  C0 3B 00 04 */	lfs f1, 4(r27)
/* 80009738 00006318  C0 1C 00 04 */	lfs f0, 4(r28)
/* 8000973C 0000631C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80009740 00006320  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 80009744 00006324  C0 3B 00 08 */	lfs f1, 8(r27)
/* 80009748 00006328  C0 1C 00 08 */	lfs f0, 8(r28)
/* 8000974C 0000632C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80009750 00006330  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 80009754 00006334  C0 21 00 3C */	lfs f1, 0x3c(r1)
/* 80009758 00006338  C0 61 00 44 */	lfs f3, 0x44(r1)
/* 8000975C 0000633C  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 80009760 00006340  EC 41 00 72 */	fmuls f2, f1, f1
/* 80009764 00006344  EC 63 00 F2 */	fmuls f3, f3, f3
/* 80009768 00006348  EC 20 00 32 */	fmuls f1, f0, f0
/* 8000976C 0000634C  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80009770 00006350  EC 22 08 2A */	fadds f1, f2, f1
/* 80009774 00006354  EF E3 08 2A */	fadds f31, f3, f1
/* 80009778 00006358  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8000977C 0000635C  40 81 00 50 */	ble lbl_800097CC
/* 80009780 00006360  FC 20 F8 34 */	frsqrte f1, f31
/* 80009784 00006364  C8 62 80 38 */	lfd f3, lbl_804D7A18(r2)
/* 80009788 00006368  C8 42 80 40 */	lfd f2, lbl_804D7A20(r2)
/* 8000978C 0000636C  FC 01 00 72 */	fmul f0, f1, f1
/* 80009790 00006370  FC 23 00 72 */	fmul f1, f3, f1
/* 80009794 00006374  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 80009798 00006378  FC 21 00 32 */	fmul f1, f1, f0
/* 8000979C 0000637C  FC 01 00 72 */	fmul f0, f1, f1
/* 800097A0 00006380  FC 23 00 72 */	fmul f1, f3, f1
/* 800097A4 00006384  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 800097A8 00006388  FC 21 00 32 */	fmul f1, f1, f0
/* 800097AC 0000638C  FC 01 00 72 */	fmul f0, f1, f1
/* 800097B0 00006390  FC 23 00 72 */	fmul f1, f3, f1
/* 800097B4 00006394  FC 1F 10 3C */	fnmsub f0, f31, f0, f2
/* 800097B8 00006398  FC 01 00 32 */	fmul f0, f1, f0
/* 800097BC 0000639C  FC 1F 00 32 */	fmul f0, f31, f0
/* 800097C0 000063A0  FC 00 00 18 */	frsp f0, f0
/* 800097C4 000063A4  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800097C8 000063A8  C3 E1 00 20 */	lfs f31, 0x20(r1)
lbl_800097CC:
/* 800097CC 000063AC  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 800097D0 000063B0  FC 20 F8 90 */	fmr f1, f31
/* 800097D4 000063B4  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800097D8 000063B8  40 80 00 18 */	bge lbl_800097F0
/* 800097DC 000063BC  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 800097E0 000063C0  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800097E4 000063C4  40 81 00 0C */	ble lbl_800097F0
/* 800097E8 000063C8  38 00 00 01 */	li r0, 1
/* 800097EC 000063CC  48 00 00 08 */	b lbl_800097F4
lbl_800097F0:
/* 800097F0 000063D0  38 00 00 00 */	li r0, 0
lbl_800097F4:
/* 800097F4 000063D4  2C 00 00 00 */	cmpwi r0, 0
/* 800097F8 000063D8  40 82 00 94 */	bne lbl_8000988C
/* 800097FC 000063DC  C0 41 00 3C */	lfs f2, 0x3c(r1)
/* 80009800 000063E0  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009804 000063E4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009808 000063E8  40 80 00 18 */	bge lbl_80009820
/* 8000980C 000063EC  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 80009810 000063F0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009814 000063F4  40 81 00 0C */	ble lbl_80009820
/* 80009818 000063F8  38 00 00 01 */	li r0, 1
/* 8000981C 000063FC  48 00 00 08 */	b lbl_80009824
lbl_80009820:
/* 80009820 00006400  38 00 00 00 */	li r0, 0
lbl_80009824:
/* 80009824 00006404  2C 00 00 00 */	cmpwi r0, 0
/* 80009828 00006408  41 82 00 B0 */	beq lbl_800098D8
/* 8000982C 0000640C  C0 41 00 40 */	lfs f2, 0x40(r1)
/* 80009830 00006410  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009834 00006414  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009838 00006418  40 80 00 18 */	bge lbl_80009850
/* 8000983C 0000641C  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 80009840 00006420  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009844 00006424  40 81 00 0C */	ble lbl_80009850
/* 80009848 00006428  38 00 00 01 */	li r0, 1
/* 8000984C 0000642C  48 00 00 08 */	b lbl_80009854
lbl_80009850:
/* 80009850 00006430  38 00 00 00 */	li r0, 0
lbl_80009854:
/* 80009854 00006434  2C 00 00 00 */	cmpwi r0, 0
/* 80009858 00006438  41 82 00 80 */	beq lbl_800098D8
/* 8000985C 0000643C  C0 41 00 44 */	lfs f2, 0x44(r1)
/* 80009860 00006440  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009864 00006444  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009868 00006448  40 80 00 18 */	bge lbl_80009880
/* 8000986C 0000644C  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 80009870 00006450  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009874 00006454  40 81 00 0C */	ble lbl_80009880
/* 80009878 00006458  38 00 00 01 */	li r0, 1
/* 8000987C 0000645C  48 00 00 08 */	b lbl_80009884
lbl_80009880:
/* 80009880 00006460  38 00 00 00 */	li r0, 0
lbl_80009884:
/* 80009884 00006464  2C 00 00 00 */	cmpwi r0, 0
/* 80009888 00006468  41 82 00 50 */	beq lbl_800098D8
lbl_8000988C:
/* 8000988C 0000646C  38 61 00 48 */	addi r3, r1, 0x48
/* 80009890 00006470  48 33 89 15 */	bl PSMTXIdentity
/* 80009894 00006474  C0 42 80 74 */	lfs f2, lbl_804D7A54(r2)
/* 80009898 00006478  38 61 00 48 */	addi r3, r1, 0x48
/* 8000989C 0000647C  C0 22 80 18 */	lfs f1, lbl_804D79F8(r2)
/* 800098A0 00006480  38 81 00 A8 */	addi r4, r1, 0xa8
/* 800098A4 00006484  D0 41 00 48 */	stfs f2, 0x48(r1)
/* 800098A8 00006488  C0 02 80 28 */	lfs f0, lbl_804D7A08(r2)
/* 800098AC 0000648C  38 A1 00 D8 */	addi r5, r1, 0xd8
/* 800098B0 00006490  D0 21 00 58 */	stfs f1, 0x58(r1)
/* 800098B4 00006494  D0 21 00 68 */	stfs f1, 0x68(r1)
/* 800098B8 00006498  D0 21 00 4C */	stfs f1, 0x4c(r1)
/* 800098BC 0000649C  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 800098C0 000064A0  D0 21 00 6C */	stfs f1, 0x6c(r1)
/* 800098C4 000064A4  D0 21 00 50 */	stfs f1, 0x50(r1)
/* 800098C8 000064A8  D0 21 00 60 */	stfs f1, 0x60(r1)
/* 800098CC 000064AC  D0 41 00 70 */	stfs f2, 0x70(r1)
/* 800098D0 000064B0  48 33 89 35 */	bl PSMTXConcat
/* 800098D4 000064B4  48 00 01 AC */	b lbl_80009A80
lbl_800098D8:
/* 800098D8 000064B8  FC 40 F0 90 */	fmr f2, f30
/* 800098DC 000064BC  38 61 00 78 */	addi r3, r1, 0x78
/* 800098E0 000064C0  FC 60 F0 90 */	fmr f3, f30
/* 800098E4 000064C4  48 33 8D 85 */	bl PSMTXScale
/* 800098E8 000064C8  C0 21 00 3C */	lfs f1, 0x3c(r1)
/* 800098EC 000064CC  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 800098F0 000064D0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800098F4 000064D4  40 80 00 18 */	bge lbl_8000990C
/* 800098F8 000064D8  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 800098FC 000064DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80009900 000064E0  40 81 00 0C */	ble lbl_8000990C
/* 80009904 000064E4  38 00 00 01 */	li r0, 1
/* 80009908 000064E8  48 00 00 08 */	b lbl_80009910
lbl_8000990C:
/* 8000990C 000064EC  38 00 00 00 */	li r0, 0
lbl_80009910:
/* 80009910 000064F0  2C 00 00 00 */	cmpwi r0, 0
/* 80009914 000064F4  41 82 00 4C */	beq lbl_80009960
/* 80009918 000064F8  C0 41 00 40 */	lfs f2, 0x40(r1)
/* 8000991C 000064FC  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009920 00006500  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009924 00006504  40 80 00 18 */	bge lbl_8000993C
/* 80009928 00006508  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 8000992C 0000650C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80009930 00006510  40 81 00 0C */	ble lbl_8000993C
/* 80009934 00006514  38 00 00 01 */	li r0, 1
/* 80009938 00006518  48 00 00 08 */	b lbl_80009940
lbl_8000993C:
/* 8000993C 0000651C  38 00 00 00 */	li r0, 0
lbl_80009940:
/* 80009940 00006520  2C 00 00 00 */	cmpwi r0, 0
/* 80009944 00006524  41 82 00 1C */	beq lbl_80009960
/* 80009948 00006528  C0 21 00 44 */	lfs f1, 0x44(r1)
/* 8000994C 0000652C  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 80009950 00006530  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 80009954 00006534  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 80009958 00006538  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 8000995C 0000653C  48 00 00 1C */	b lbl_80009978
lbl_80009960:
/* 80009960 00006540  C0 41 00 40 */	lfs f2, 0x40(r1)
/* 80009964 00006544  FC 20 08 50 */	fneg f1, f1
/* 80009968 00006548  C0 02 80 18 */	lfs f0, lbl_804D79F8(r2)
/* 8000996C 0000654C  D0 41 00 30 */	stfs f2, 0x30(r1)
/* 80009970 00006550  D0 21 00 34 */	stfs f1, 0x34(r1)
/* 80009974 00006554  D0 01 00 38 */	stfs f0, 0x38(r1)
lbl_80009978:
/* 80009978 00006558  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000997C 0000655C  38 83 00 00 */	addi r4, r3, 0
/* 80009980 00006560  48 33 94 39 */	bl PSVECNormalize
/* 80009984 00006564  38 61 00 30 */	addi r3, r1, 0x30
/* 80009988 00006568  38 83 00 00 */	addi r4, r3, 0
/* 8000998C 0000656C  48 33 94 2D */	bl PSVECNormalize
/* 80009990 00006570  38 61 00 3C */	addi r3, r1, 0x3c
/* 80009994 00006574  38 81 00 30 */	addi r4, r1, 0x30
/* 80009998 00006578  38 A1 00 24 */	addi r5, r1, 0x24
/* 8000999C 0000657C  48 33 94 BD */	bl PSVECCrossProduct
/* 800099A0 00006580  38 61 00 48 */	addi r3, r1, 0x48
/* 800099A4 00006584  48 33 88 01 */	bl PSMTXIdentity
/* 800099A8 00006588  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 800099AC 0000658C  38 61 00 48 */	addi r3, r1, 0x48
/* 800099B0 00006590  38 81 00 A8 */	addi r4, r1, 0xa8
/* 800099B4 00006594  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 800099B8 00006598  38 A1 00 D8 */	addi r5, r1, 0xd8
/* 800099BC 0000659C  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 800099C0 000065A0  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 800099C4 000065A4  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 800099C8 000065A8  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 800099CC 000065AC  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 800099D0 000065B0  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 800099D4 000065B4  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 800099D8 000065B8  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 800099DC 000065BC  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 800099E0 000065C0  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 800099E4 000065C4  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 800099E8 000065C8  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 800099EC 000065CC  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 800099F0 000065D0  D0 01 00 60 */	stfs f0, 0x60(r1)
/* 800099F4 000065D4  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 800099F8 000065D8  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 800099FC 000065DC  48 33 88 09 */	bl PSMTXConcat
/* 80009A00 000065E0  38 81 00 78 */	addi r4, r1, 0x78
/* 80009A04 000065E4  38 A4 00 00 */	addi r5, r4, 0
/* 80009A08 000065E8  38 61 00 48 */	addi r3, r1, 0x48
/* 80009A0C 000065EC  48 33 87 F9 */	bl PSMTXConcat
/* 80009A10 000065F0  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 80009A14 000065F4  38 81 00 A8 */	addi r4, r1, 0xa8
/* 80009A18 000065F8  38 A4 00 00 */	addi r5, r4, 0
/* 80009A1C 000065FC  FC 00 00 50 */	fneg f0, f0
/* 80009A20 00006600  38 61 00 48 */	addi r3, r1, 0x48
/* 80009A24 00006604  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 80009A28 00006608  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 80009A2C 0000660C  FC 00 00 50 */	fneg f0, f0
/* 80009A30 00006610  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 80009A34 00006614  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 80009A38 00006618  FC 00 00 50 */	fneg f0, f0
/* 80009A3C 0000661C  D0 01 00 68 */	stfs f0, 0x68(r1)
/* 80009A40 00006620  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 80009A44 00006624  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 80009A48 00006628  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 80009A4C 0000662C  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 80009A50 00006630  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 80009A54 00006634  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 80009A58 00006638  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 80009A5C 0000663C  FC 00 00 50 */	fneg f0, f0
/* 80009A60 00006640  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 80009A64 00006644  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 80009A68 00006648  FC 00 00 50 */	fneg f0, f0
/* 80009A6C 0000664C  D0 01 00 60 */	stfs f0, 0x60(r1)
/* 80009A70 00006650  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 80009A74 00006654  FC 00 00 50 */	fneg f0, f0
/* 80009A78 00006658  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 80009A7C 0000665C  48 33 87 89 */	bl PSMTXConcat
lbl_80009A80:
/* 80009A80 00006660  C0 3B 00 00 */	lfs f1, 0(r27)
/* 80009A84 00006664  38 61 00 48 */	addi r3, r1, 0x48
/* 80009A88 00006668  C0 5B 00 04 */	lfs f2, 4(r27)
/* 80009A8C 0000666C  C0 7B 00 08 */	lfs f3, 8(r27)
/* 80009A90 00006670  48 33 8B A5 */	bl PSMTXTrans
/* 80009A94 00006674  38 81 00 D8 */	addi r4, r1, 0xd8
/* 80009A98 00006678  38 A4 00 00 */	addi r5, r4, 0
/* 80009A9C 0000667C  38 61 00 48 */	addi r3, r1, 0x48
/* 80009AA0 00006680  48 33 87 65 */	bl PSMTXConcat
/* 80009AA4 00006684  C0 3C 00 00 */	lfs f1, 0(r28)
/* 80009AA8 00006688  38 61 00 48 */	addi r3, r1, 0x48
/* 80009AAC 0000668C  C0 5C 00 04 */	lfs f2, 4(r28)
/* 80009AB0 00006690  C0 7C 00 08 */	lfs f3, 8(r28)
/* 80009AB4 00006694  48 33 8B 81 */	bl PSMTXTrans
/* 80009AB8 00006698  38 81 00 A8 */	addi r4, r1, 0xa8
/* 80009ABC 0000669C  38 A4 00 00 */	addi r5, r4, 0
/* 80009AC0 000066A0  38 61 00 48 */	addi r3, r1, 0x48
/* 80009AC4 000066A4  48 33 87 41 */	bl PSMTXConcat
/* 80009AC8 000066A8  C0 7B 00 00 */	lfs f3, 0(r27)
/* 80009ACC 000066AC  38 61 00 48 */	addi r3, r1, 0x48
/* 80009AD0 000066B0  C0 5C 00 00 */	lfs f2, 0(r28)
/* 80009AD4 000066B4  C0 3B 00 04 */	lfs f1, 4(r27)
/* 80009AD8 000066B8  C0 1C 00 04 */	lfs f0, 4(r28)
/* 80009ADC 000066BC  EC 83 10 2A */	fadds f4, f3, f2
/* 80009AE0 000066C0  C8 A2 80 38 */	lfd f5, lbl_804D7A18(r2)
/* 80009AE4 000066C4  EC 61 00 2A */	fadds f3, f1, f0
/* 80009AE8 000066C8  C0 5B 00 08 */	lfs f2, 8(r27)
/* 80009AEC 000066CC  C0 1C 00 08 */	lfs f0, 8(r28)
/* 80009AF0 000066D0  FC 25 01 32 */	fmul f1, f5, f4
/* 80009AF4 000066D4  EC 02 00 2A */	fadds f0, f2, f0
/* 80009AF8 000066D8  FC 45 00 F2 */	fmul f2, f5, f3
/* 80009AFC 000066DC  FC 65 00 32 */	fmul f3, f5, f0
/* 80009B00 000066E0  FC 20 08 18 */	frsp f1, f1
/* 80009B04 000066E4  FC 40 10 18 */	frsp f2, f2
/* 80009B08 000066E8  FC 60 18 18 */	frsp f3, f3
/* 80009B0C 000066EC  48 33 8B 29 */	bl PSMTXTrans
/* 80009B10 000066F0  38 81 00 78 */	addi r4, r1, 0x78
/* 80009B14 000066F4  38 A4 00 00 */	addi r5, r4, 0
/* 80009B18 000066F8  38 61 00 48 */	addi r3, r1, 0x48
/* 80009B1C 000066FC  48 33 86 E9 */	bl PSMTXConcat
/* 80009B20 00006700  38 81 00 D8 */	addi r4, r1, 0xd8
/* 80009B24 00006704  38 7A 00 00 */	addi r3, r26, 0
/* 80009B28 00006708  38 A4 00 00 */	addi r5, r4, 0
/* 80009B2C 0000670C  48 33 86 D9 */	bl PSMTXConcat
/* 80009B30 00006710  38 81 00 A8 */	addi r4, r1, 0xa8
/* 80009B34 00006714  38 7A 00 00 */	addi r3, r26, 0
/* 80009B38 00006718  38 A4 00 00 */	addi r5, r4, 0
/* 80009B3C 0000671C  48 33 86 C9 */	bl PSMTXConcat
/* 80009B40 00006720  38 81 00 78 */	addi r4, r1, 0x78
/* 80009B44 00006724  38 7A 00 00 */	addi r3, r26, 0
/* 80009B48 00006728  38 A4 00 00 */	addi r5, r4, 0
/* 80009B4C 0000672C  48 33 86 B9 */	bl PSMTXConcat
/* 80009B50 00006730  38 60 00 02 */	li r3, 2
/* 80009B54 00006734  48 33 37 FD */	bl GXSetCullMode
/* 80009B58 00006738  48 33 28 71 */	bl GXClearVtxDesc
/* 80009B5C 0000673C  38 9F 00 C0 */	addi r4, r31, 0xc0
/* 80009B60 00006740  38 60 00 09 */	li r3, 9
/* 80009B64 00006744  38 A0 00 06 */	li r5, 6
/* 80009B68 00006748  48 33 2C A5 */	bl GXSetArray
/* 80009B6C 0000674C  38 9F 02 60 */	addi r4, r31, 0x260
/* 80009B70 00006750  38 60 00 0A */	li r3, 0xa
/* 80009B74 00006754  38 A0 00 06 */	li r5, 6
/* 80009B78 00006758  48 33 2C 95 */	bl GXSetArray
/* 80009B7C 0000675C  38 60 00 09 */	li r3, 9
/* 80009B80 00006760  38 80 00 02 */	li r4, 2
/* 80009B84 00006764  48 33 23 7D */	bl GXSetVtxDesc
/* 80009B88 00006768  38 60 00 00 */	li r3, 0
/* 80009B8C 0000676C  38 80 00 09 */	li r4, 9
/* 80009B90 00006770  38 A0 00 01 */	li r5, 1
/* 80009B94 00006774  38 C0 00 03 */	li r6, 3
/* 80009B98 00006778  38 E0 00 0E */	li r7, 0xe
/* 80009B9C 0000677C  48 33 28 79 */	bl GXSetVtxAttrFmt
/* 80009BA0 00006780  38 60 00 0A */	li r3, 0xa
/* 80009BA4 00006784  38 80 00 02 */	li r4, 2
/* 80009BA8 00006788  48 33 23 59 */	bl GXSetVtxDesc
/* 80009BAC 0000678C  38 60 00 00 */	li r3, 0
/* 80009BB0 00006790  38 80 00 0A */	li r4, 0xa
/* 80009BB4 00006794  38 A0 00 00 */	li r5, 0
/* 80009BB8 00006798  38 C0 00 03 */	li r6, 3
/* 80009BBC 0000679C  38 E0 00 0E */	li r7, 0xe
/* 80009BC0 000067A0  48 33 28 55 */	bl GXSetVtxAttrFmt
/* 80009BC4 000067A4  38 81 00 D8 */	addi r4, r1, 0xd8
/* 80009BC8 000067A8  38 A4 00 00 */	addi r5, r4, 0
/* 80009BCC 000067AC  38 61 01 08 */	addi r3, r1, 0x108
/* 80009BD0 000067B0  48 33 86 35 */	bl PSMTXConcat
/* 80009BD4 000067B4  38 61 00 D8 */	addi r3, r1, 0xd8
/* 80009BD8 000067B8  38 80 00 00 */	li r4, 0
/* 80009BDC 000067BC  48 33 78 B9 */	bl GXLoadPosMtxImm
/* 80009BE0 000067C0  38 61 00 D8 */	addi r3, r1, 0xd8
/* 80009BE4 000067C4  38 83 00 00 */	addi r4, r3, 0
/* 80009BE8 000067C8  48 36 F7 29 */	bl HSD_MtxInverse
/* 80009BEC 000067CC  38 61 00 D8 */	addi r3, r1, 0xd8
/* 80009BF0 000067D0  38 83 00 00 */	addi r4, r3, 0
/* 80009BF4 000067D4  48 33 86 DD */	bl PSMTXTranspose
/* 80009BF8 000067D8  38 61 00 D8 */	addi r3, r1, 0xd8
/* 80009BFC 000067DC  38 80 00 00 */	li r4, 0
/* 80009C00 000067E0  48 33 78 D1 */	bl GXLoadNrmMtxImm
/* 80009C04 000067E4  38 7F 04 00 */	addi r3, r31, 0x400
/* 80009C08 000067E8  38 80 01 20 */	li r4, 0x120
/* 80009C0C 000067EC  48 33 74 CD */	bl GXCallDisplayList
/* 80009C10 000067F0  48 33 27 B9 */	bl GXClearVtxDesc
/* 80009C14 000067F4  38 9F 00 C0 */	addi r4, r31, 0xc0
/* 80009C18 000067F8  38 60 00 09 */	li r3, 9
/* 80009C1C 000067FC  38 A0 00 06 */	li r5, 6
/* 80009C20 00006800  48 33 2B ED */	bl GXSetArray
/* 80009C24 00006804  38 9F 02 60 */	addi r4, r31, 0x260
/* 80009C28 00006808  38 60 00 0A */	li r3, 0xa
/* 80009C2C 0000680C  38 A0 00 06 */	li r5, 6
/* 80009C30 00006810  48 33 2B DD */	bl GXSetArray
/* 80009C34 00006814  38 60 00 09 */	li r3, 9
/* 80009C38 00006818  38 80 00 02 */	li r4, 2
/* 80009C3C 0000681C  48 33 22 C5 */	bl GXSetVtxDesc
/* 80009C40 00006820  38 60 00 00 */	li r3, 0
/* 80009C44 00006824  38 80 00 09 */	li r4, 9
/* 80009C48 00006828  38 A0 00 01 */	li r5, 1
/* 80009C4C 0000682C  38 C0 00 03 */	li r6, 3
/* 80009C50 00006830  38 E0 00 0E */	li r7, 0xe
/* 80009C54 00006834  48 33 27 C1 */	bl GXSetVtxAttrFmt
/* 80009C58 00006838  38 60 00 0A */	li r3, 0xa
/* 80009C5C 0000683C  38 80 00 02 */	li r4, 2
/* 80009C60 00006840  48 33 22 A1 */	bl GXSetVtxDesc
/* 80009C64 00006844  38 60 00 00 */	li r3, 0
/* 80009C68 00006848  38 80 00 0A */	li r4, 0xa
/* 80009C6C 0000684C  38 A0 00 00 */	li r5, 0
/* 80009C70 00006850  38 C0 00 03 */	li r6, 3
/* 80009C74 00006854  38 E0 00 0E */	li r7, 0xe
/* 80009C78 00006858  48 33 27 9D */	bl GXSetVtxAttrFmt
/* 80009C7C 0000685C  38 81 00 A8 */	addi r4, r1, 0xa8
/* 80009C80 00006860  38 A4 00 00 */	addi r5, r4, 0
/* 80009C84 00006864  38 61 01 08 */	addi r3, r1, 0x108
/* 80009C88 00006868  48 33 85 7D */	bl PSMTXConcat
/* 80009C8C 0000686C  38 61 00 A8 */	addi r3, r1, 0xa8
/* 80009C90 00006870  38 80 00 00 */	li r4, 0
/* 80009C94 00006874  48 33 78 01 */	bl GXLoadPosMtxImm
/* 80009C98 00006878  38 61 00 A8 */	addi r3, r1, 0xa8
/* 80009C9C 0000687C  38 83 00 00 */	addi r4, r3, 0
/* 80009CA0 00006880  48 36 F6 71 */	bl HSD_MtxInverse
/* 80009CA4 00006884  38 61 00 A8 */	addi r3, r1, 0xa8
/* 80009CA8 00006888  38 83 00 00 */	addi r4, r3, 0
/* 80009CAC 0000688C  48 33 86 25 */	bl PSMTXTranspose
/* 80009CB0 00006890  38 61 00 A8 */	addi r3, r1, 0xa8
/* 80009CB4 00006894  38 80 00 00 */	li r4, 0
/* 80009CB8 00006898  48 33 78 19 */	bl GXLoadNrmMtxImm
/* 80009CBC 0000689C  38 7F 04 00 */	addi r3, r31, 0x400
/* 80009CC0 000068A0  38 80 01 20 */	li r4, 0x120
/* 80009CC4 000068A4  48 33 74 15 */	bl GXCallDisplayList
/* 80009CC8 000068A8  C0 02 80 10 */	lfs f0, lbl_804D79F0(r2)
/* 80009CCC 000068AC  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80009CD0 000068B0  40 80 00 18 */	bge lbl_80009CE8
/* 80009CD4 000068B4  C0 02 80 14 */	lfs f0, lbl_804D79F4(r2)
/* 80009CD8 000068B8  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80009CDC 000068BC  40 81 00 0C */	ble lbl_80009CE8
/* 80009CE0 000068C0  38 00 00 01 */	li r0, 1
/* 80009CE4 000068C4  48 00 00 08 */	b lbl_80009CEC
lbl_80009CE8:
/* 80009CE8 000068C8  38 00 00 00 */	li r0, 0
lbl_80009CEC:
/* 80009CEC 000068CC  2C 00 00 00 */	cmpwi r0, 0
/* 80009CF0 000068D0  40 82 00 BC */	bne lbl_80009DAC
/* 80009CF4 000068D4  48 33 26 D5 */	bl GXClearVtxDesc
/* 80009CF8 000068D8  38 9F 05 20 */	addi r4, r31, 0x520
/* 80009CFC 000068DC  38 60 00 09 */	li r3, 9
/* 80009D00 000068E0  38 A0 00 06 */	li r5, 6
/* 80009D04 000068E4  48 33 2B 09 */	bl GXSetArray
/* 80009D08 000068E8  38 9F 06 40 */	addi r4, r31, 0x640
/* 80009D0C 000068EC  38 60 00 0A */	li r3, 0xa
/* 80009D10 000068F0  38 A0 00 06 */	li r5, 6
/* 80009D14 000068F4  48 33 2A F9 */	bl GXSetArray
/* 80009D18 000068F8  38 60 00 09 */	li r3, 9
/* 80009D1C 000068FC  38 80 00 02 */	li r4, 2
/* 80009D20 00006900  48 33 21 E1 */	bl GXSetVtxDesc
/* 80009D24 00006904  38 60 00 00 */	li r3, 0
/* 80009D28 00006908  38 80 00 09 */	li r4, 9
/* 80009D2C 0000690C  38 A0 00 01 */	li r5, 1
/* 80009D30 00006910  38 C0 00 03 */	li r6, 3
/* 80009D34 00006914  38 E0 00 0E */	li r7, 0xe
/* 80009D38 00006918  48 33 26 DD */	bl GXSetVtxAttrFmt
/* 80009D3C 0000691C  38 60 00 0A */	li r3, 0xa
/* 80009D40 00006920  38 80 00 02 */	li r4, 2
/* 80009D44 00006924  48 33 21 BD */	bl GXSetVtxDesc
/* 80009D48 00006928  38 60 00 00 */	li r3, 0
/* 80009D4C 0000692C  38 80 00 0A */	li r4, 0xa
/* 80009D50 00006930  38 A0 00 00 */	li r5, 0
/* 80009D54 00006934  38 C0 00 03 */	li r6, 3
/* 80009D58 00006938  38 E0 00 06 */	li r7, 6
/* 80009D5C 0000693C  48 33 26 B9 */	bl GXSetVtxAttrFmt
/* 80009D60 00006940  38 81 00 78 */	addi r4, r1, 0x78
/* 80009D64 00006944  38 A4 00 00 */	addi r5, r4, 0
/* 80009D68 00006948  38 61 01 08 */	addi r3, r1, 0x108
/* 80009D6C 0000694C  48 33 84 99 */	bl PSMTXConcat
/* 80009D70 00006950  38 61 00 78 */	addi r3, r1, 0x78
/* 80009D74 00006954  38 80 00 00 */	li r4, 0
/* 80009D78 00006958  48 33 77 1D */	bl GXLoadPosMtxImm
/* 80009D7C 0000695C  38 61 00 78 */	addi r3, r1, 0x78
/* 80009D80 00006960  38 83 00 00 */	addi r4, r3, 0
/* 80009D84 00006964  48 36 F5 8D */	bl HSD_MtxInverse
/* 80009D88 00006968  38 61 00 78 */	addi r3, r1, 0x78
/* 80009D8C 0000696C  38 83 00 00 */	addi r4, r3, 0
/* 80009D90 00006970  48 33 85 41 */	bl PSMTXTranspose
/* 80009D94 00006974  38 61 00 78 */	addi r3, r1, 0x78
/* 80009D98 00006978  38 80 00 00 */	li r4, 0
/* 80009D9C 0000697C  48 33 77 35 */	bl GXLoadNrmMtxImm
/* 80009DA0 00006980  38 7F 06 A0 */	addi r3, r31, 0x6a0
/* 80009DA4 00006984  38 80 00 A0 */	li r4, 0xa0
/* 80009DA8 00006988  48 33 73 31 */	bl GXCallDisplayList
lbl_80009DAC:
/* 80009DAC 0000698C  38 60 FF FF */	li r3, -1
/* 80009DB0 00006990  48 35 82 15 */	bl HSD_StateInvalidate
/* 80009DB4 00006994  48 35 87 25 */	bl HSD_StateInitTev
/* 80009DB8 00006998  BB 41 01 38 */	lmw r26, 0x138(r1)
/* 80009DBC 0000699C  80 01 01 64 */	lwz r0, 0x164(r1)
/* 80009DC0 000069A0  CB E1 01 58 */	lfd f31, 0x158(r1)
/* 80009DC4 000069A4  CB C1 01 50 */	lfd f30, 0x150(r1)
/* 80009DC8 000069A8  38 21 01 60 */	addi r1, r1, 0x160
/* 80009DCC 000069AC  7C 08 03 A6 */	mtlr r0
/* 80009DD0 000069B0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_80009DD4(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 80009DD4 000069B4  7C 08 02 A6 */	mflr r0
/* 80009DD8 000069B8  90 01 00 04 */	stw r0, 4(r1)
/* 80009DDC 000069BC  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 80009DE0 000069C0  93 E1 00 74 */	stw r31, 0x74(r1)
/* 80009DE4 000069C4  3B E5 00 00 */	addi r31, r5, 0
/* 80009DE8 000069C8  93 C1 00 70 */	stw r30, 0x70(r1)
/* 80009DEC 000069CC  3B C4 00 00 */	addi r30, r4, 0
/* 80009DF0 000069D0  93 A1 00 6C */	stw r29, 0x6c(r1)
/* 80009DF4 000069D4  3B A3 00 00 */	addi r29, r3, 0
/* 80009DF8 000069D8  38 60 FF FF */	li r3, -1
/* 80009DFC 000069DC  48 35 81 C9 */	bl HSD_StateInvalidate
/* 80009E00 000069E0  48 35 86 D9 */	bl HSD_StateInitTev
/* 80009E04 000069E4  38 7F 00 00 */	addi r3, r31, 0
/* 80009E08 000069E8  38 9F 00 00 */	addi r4, r31, 0
/* 80009E0C 000069EC  4B FF EF 99 */	bl lbColl_80008DA4
/* 80009E10 000069F0  48 36 24 35 */	bl HSD_ClearVtxDesc
/* 80009E14 000069F4  38 60 00 00 */	li r3, 0
/* 80009E18 000069F8  38 80 00 09 */	li r4, 9
/* 80009E1C 000069FC  38 A0 00 01 */	li r5, 1
/* 80009E20 00006A00  38 C0 00 04 */	li r6, 4
/* 80009E24 00006A04  38 E0 00 00 */	li r7, 0
/* 80009E28 00006A08  48 33 25 ED */	bl GXSetVtxAttrFmt
/* 80009E2C 00006A0C  38 60 00 00 */	li r3, 0
/* 80009E30 00006A10  38 80 00 0B */	li r4, 0xb
/* 80009E34 00006A14  38 A0 00 01 */	li r5, 1
/* 80009E38 00006A18  38 C0 00 05 */	li r6, 5
/* 80009E3C 00006A1C  38 E0 00 00 */	li r7, 0
/* 80009E40 00006A20  48 33 25 D5 */	bl GXSetVtxAttrFmt
/* 80009E44 00006A24  38 60 00 09 */	li r3, 9
/* 80009E48 00006A28  38 80 00 01 */	li r4, 1
/* 80009E4C 00006A2C  48 33 20 B5 */	bl GXSetVtxDesc
/* 80009E50 00006A30  38 60 00 0B */	li r3, 0xb
/* 80009E54 00006A34  38 80 00 01 */	li r4, 1
/* 80009E58 00006A38  48 33 20 A9 */	bl GXSetVtxDesc
/* 80009E5C 00006A3C  38 60 00 00 */	li r3, 0
/* 80009E60 00006A40  48 33 76 B1 */	bl GXSetCurrentMtx
/* 80009E64 00006A44  38 60 00 00 */	li r3, 0
/* 80009E68 00006A48  48 33 34 E9 */	bl GXSetCullMode
/* 80009E6C 00006A4C  48 36 04 1D */	bl HSD_CObjGetCurrent
/* 80009E70 00006A50  38 81 00 34 */	addi r4, r1, 0x34
/* 80009E74 00006A54  48 35 F7 7D */	bl HSD_CObjGetViewingMtx
/* 80009E78 00006A58  38 61 00 34 */	addi r3, r1, 0x34
/* 80009E7C 00006A5C  38 80 00 00 */	li r4, 0
/* 80009E80 00006A60  48 33 76 15 */	bl GXLoadPosMtxImm
/* 80009E84 00006A64  38 60 00 80 */	li r3, 0x80
/* 80009E88 00006A68  38 80 00 00 */	li r4, 0
/* 80009E8C 00006A6C  38 A0 00 04 */	li r5, 4
/* 80009E90 00006A70  48 33 32 4D */	bl GXBegin
/* 80009E94 00006A74  C0 7D 00 08 */	lfs f3, 8(r29)
/* 80009E98 00006A78  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 80009E9C 00006A7C  C0 5D 00 04 */	lfs f2, 4(r29)
/* 80009EA0 00006A80  38 60 FF FF */	li r3, -1
/* 80009EA4 00006A84  C0 3D 00 00 */	lfs f1, 0(r29)
/* 80009EA8 00006A88  D0 24 80 00 */	stfs f1, 0xCC008000@l(r4)
/* 80009EAC 00006A8C  D0 44 80 00 */	stfs f2, -0x8000(r4)
/* 80009EB0 00006A90  D0 64 80 00 */	stfs f3, -0x8000(r4)
/* 80009EB4 00006A94  88 FF 00 03 */	lbz r7, 3(r31)
/* 80009EB8 00006A98  88 DF 00 02 */	lbz r6, 2(r31)
/* 80009EBC 00006A9C  88 BF 00 01 */	lbz r5, 1(r31)
/* 80009EC0 00006AA0  88 1F 00 00 */	lbz r0, 0(r31)
/* 80009EC4 00006AA4  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80009EC8 00006AA8  98 A4 80 00 */	stb r5, -0x8000(r4)
/* 80009ECC 00006AAC  98 C4 80 00 */	stb r6, -0x8000(r4)
/* 80009ED0 00006AB0  98 E4 80 00 */	stb r7, -0x8000(r4)
/* 80009ED4 00006AB4  C0 1E 00 00 */	lfs f0, 0(r30)
/* 80009ED8 00006AB8  D0 04 80 00 */	stfs f0, -0x8000(r4)
/* 80009EDC 00006ABC  D0 44 80 00 */	stfs f2, -0x8000(r4)
/* 80009EE0 00006AC0  D0 64 80 00 */	stfs f3, -0x8000(r4)
/* 80009EE4 00006AC4  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80009EE8 00006AC8  98 A4 80 00 */	stb r5, -0x8000(r4)
/* 80009EEC 00006ACC  98 C4 80 00 */	stb r6, -0x8000(r4)
/* 80009EF0 00006AD0  98 E4 80 00 */	stb r7, -0x8000(r4)
/* 80009EF4 00006AD4  C0 5E 00 04 */	lfs f2, 4(r30)
/* 80009EF8 00006AD8  D0 04 80 00 */	stfs f0, -0x8000(r4)
/* 80009EFC 00006ADC  D0 44 80 00 */	stfs f2, -0x8000(r4)
/* 80009F00 00006AE0  D0 64 80 00 */	stfs f3, -0x8000(r4)
/* 80009F04 00006AE4  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80009F08 00006AE8  98 A4 80 00 */	stb r5, -0x8000(r4)
/* 80009F0C 00006AEC  98 C4 80 00 */	stb r6, -0x8000(r4)
/* 80009F10 00006AF0  98 E4 80 00 */	stb r7, -0x8000(r4)
/* 80009F14 00006AF4  D0 24 80 00 */	stfs f1, -0x8000(r4)
/* 80009F18 00006AF8  D0 44 80 00 */	stfs f2, -0x8000(r4)
/* 80009F1C 00006AFC  D0 64 80 00 */	stfs f3, -0x8000(r4)
/* 80009F20 00006B00  98 04 80 00 */	stb r0, -0x8000(r4)
/* 80009F24 00006B04  98 A4 80 00 */	stb r5, -0x8000(r4)
/* 80009F28 00006B08  98 C4 80 00 */	stb r6, -0x8000(r4)
/* 80009F2C 00006B0C  98 E4 80 00 */	stb r7, -0x8000(r4)
/* 80009F30 00006B10  48 35 80 95 */	bl HSD_StateInvalidate
/* 80009F34 00006B14  48 35 85 A5 */	bl HSD_StateInitTev
/* 80009F38 00006B18  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80009F3C 00006B1C  83 E1 00 74 */	lwz r31, 0x74(r1)
/* 80009F40 00006B20  83 C1 00 70 */	lwz r30, 0x70(r1)
/* 80009F44 00006B24  83 A1 00 6C */	lwz r29, 0x6c(r1)
/* 80009F48 00006B28  38 21 00 78 */	addi r1, r1, 0x78
/* 80009F4C 00006B2C  7C 08 03 A6 */	mtlr r0
/* 80009F50 00006B30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern int lbl_804D36A0;
extern int lbl_804D36A4;
extern int lbl_804D36A8;
extern int lbl_804D36DC;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_80009F54(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 80009F54 00006B34  7C 08 02 A6 */	mflr r0
/* 80009F58 00006B38  90 01 00 04 */	stw r0, 4(r1)
/* 80009F5C 00006B3C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80009F60 00006B40  80 03 00 00 */	lwz r0, 0(r3)
/* 80009F64 00006B44  2C 00 00 00 */	cmpwi r0, 0
/* 80009F68 00006B48  41 82 00 C8 */	beq lbl_8000A030
/* 80009F6C 00006B4C  88 03 00 43 */	lbz r0, 0x43(r3)
/* 80009F70 00006B50  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80009F74 00006B54  40 82 00 BC */	bne lbl_8000A030
/* 80009F78 00006B58  80 03 00 30 */	lwz r0, 0x30(r3)
/* 80009F7C 00006B5C  2C 00 00 0B */	cmpwi r0, 0xb
/* 80009F80 00006B60  41 82 00 1C */	beq lbl_80009F9C
/* 80009F84 00006B64  40 80 00 20 */	bge lbl_80009FA4
/* 80009F88 00006B68  2C 00 00 08 */	cmpwi r0, 8
/* 80009F8C 00006B6C  41 82 00 08 */	beq lbl_80009F94
/* 80009F90 00006B70  48 00 00 14 */	b lbl_80009FA4
lbl_80009F94:
/* 80009F94 00006B74  38 AD 80 04 */	addi r5, r13, lbl_804D36A4
/* 80009F98 00006B78  48 00 00 10 */	b lbl_80009FA8
lbl_80009F9C:
/* 80009F9C 00006B7C  38 AD 80 3C */	addi r5, r13, lbl_804D36DC
/* 80009FA0 00006B80  48 00 00 08 */	b lbl_80009FA8
lbl_80009FA4:
/* 80009FA4 00006B84  38 AD 80 00 */	addi r5, r13, lbl_804D36A0
lbl_80009FA8:
/* 80009FA8 00006B88  88 05 00 03 */	lbz r0, 3(r5)
/* 80009FAC 00006B8C  28 00 00 FF */	cmplwi r0, 0xff
/* 80009FB0 00006B90  40 82 00 0C */	bne lbl_80009FBC
/* 80009FB4 00006B94  38 00 00 00 */	li r0, 0
/* 80009FB8 00006B98  48 00 00 08 */	b lbl_80009FC0
lbl_80009FBC:
/* 80009FBC 00006B9C  38 00 00 02 */	li r0, 2
lbl_80009FC0:
/* 80009FC0 00006BA0  7C 00 20 40 */	cmplw r0, r4
/* 80009FC4 00006BA4  40 82 00 6C */	bne lbl_8000A030
/* 80009FC8 00006BA8  88 03 00 43 */	lbz r0, 0x43(r3)
/* 80009FCC 00006BAC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80009FD0 00006BB0  41 82 00 0C */	beq lbl_80009FDC
/* 80009FD4 00006BB4  C0 23 00 1C */	lfs f1, 0x1c(r3)
/* 80009FD8 00006BB8  48 00 00 0C */	b lbl_80009FE4
lbl_80009FDC:
/* 80009FDC 00006BBC  C0 03 00 1C */	lfs f0, 0x1c(r3)
/* 80009FE0 00006BC0  EC 20 00 72 */	fmuls f1, f0, f1
lbl_80009FE4:
/* 80009FE4 00006BC4  80 C3 00 4C */	lwz r6, 0x4c(r3)
/* 80009FE8 00006BC8  39 01 00 20 */	addi r8, r1, 0x20
/* 80009FEC 00006BCC  80 03 00 50 */	lwz r0, 0x50(r3)
/* 80009FF0 00006BD0  38 81 00 14 */	addi r4, r1, 0x14
/* 80009FF4 00006BD4  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80009FF8 00006BD8  38 CD 80 08 */	addi r6, r13, lbl_804D36A8
/* 80009FFC 00006BDC  90 01 00 18 */	stw r0, 0x18(r1)
/* 8000A000 00006BE0  80 03 00 54 */	lwz r0, 0x54(r3)
/* 8000A004 00006BE4  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8000A008 00006BE8  80 E3 00 58 */	lwz r7, 0x58(r3)
/* 8000A00C 00006BEC  80 03 00 5C */	lwz r0, 0x5c(r3)
/* 8000A010 00006BF0  90 E1 00 20 */	stw r7, 0x20(r1)
/* 8000A014 00006BF4  90 01 00 24 */	stw r0, 0x24(r1)
/* 8000A018 00006BF8  80 03 00 60 */	lwz r0, 0x60(r3)
/* 8000A01C 00006BFC  7D 03 43 78 */	mr r3, r8
/* 8000A020 00006C00  90 01 00 28 */	stw r0, 0x28(r1)
/* 8000A024 00006C04  4B FF EF A5 */	bl lbColl_80008FC8
/* 8000A028 00006C08  38 60 00 01 */	li r3, 1
/* 8000A02C 00006C0C  48 00 00 08 */	b lbl_8000A034
lbl_8000A030:
/* 8000A030 00006C10  38 60 00 00 */	li r3, 0
lbl_8000A034:
/* 8000A034 00006C14  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8000A038 00006C18  38 21 00 30 */	addi r1, r1, 0x30
/* 8000A03C 00006C1C  7C 08 03 A6 */	mtlr r0
/* 8000A040 00006C20  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern int lbl_804D36E8;
extern int lbl_804D36EC;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_8000A044(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 8000A044 00006C24  7C 08 02 A6 */	mflr r0
/* 8000A048 00006C28  90 01 00 04 */	stw r0, 4(r1)
/* 8000A04C 00006C2C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8000A050 00006C30  80 03 00 00 */	lwz r0, 0(r3)
/* 8000A054 00006C34  2C 00 00 00 */	cmpwi r0, 0
/* 8000A058 00006C38  41 82 00 A0 */	beq lbl_8000A0F8
/* 8000A05C 00006C3C  88 03 00 43 */	lbz r0, 0x43(r3)
/* 8000A060 00006C40  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8000A064 00006C44  40 82 00 94 */	bne lbl_8000A0F8
/* 8000A068 00006C48  38 AD 80 48 */	addi r5, r13, lbl_804D36E8
/* 8000A06C 00006C4C  88 05 00 03 */	lbz r0, 3(r5)
/* 8000A070 00006C50  28 00 00 FF */	cmplwi r0, 0xff
/* 8000A074 00006C54  40 82 00 0C */	bne lbl_8000A080
/* 8000A078 00006C58  38 00 00 00 */	li r0, 0
/* 8000A07C 00006C5C  48 00 00 08 */	b lbl_8000A084
lbl_8000A080:
/* 8000A080 00006C60  38 00 00 02 */	li r0, 2
lbl_8000A084:
/* 8000A084 00006C64  7C 00 20 40 */	cmplw r0, r4
/* 8000A088 00006C68  40 82 00 70 */	bne lbl_8000A0F8
/* 8000A08C 00006C6C  88 03 00 43 */	lbz r0, 0x43(r3)
/* 8000A090 00006C70  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8000A094 00006C74  41 82 00 0C */	beq lbl_8000A0A0
/* 8000A098 00006C78  C0 23 00 1C */	lfs f1, 0x1c(r3)
/* 8000A09C 00006C7C  48 00 00 0C */	b lbl_8000A0A8
lbl_8000A0A0:
/* 8000A0A0 00006C80  C0 03 00 1C */	lfs f0, 0x1c(r3)
/* 8000A0A4 00006C84  EC 20 00 72 */	fmuls f1, f0, f1
lbl_8000A0A8:
/* 8000A0A8 00006C88  80 A3 00 4C */	lwz r5, 0x4c(r3)
/* 8000A0AC 00006C8C  39 01 00 20 */	addi r8, r1, 0x20
/* 8000A0B0 00006C90  80 03 00 50 */	lwz r0, 0x50(r3)
/* 8000A0B4 00006C94  38 81 00 14 */	addi r4, r1, 0x14
/* 8000A0B8 00006C98  38 CD 80 4C */	addi r6, r13, lbl_804D36EC
/* 8000A0BC 00006C9C  90 A1 00 14 */	stw r5, 0x14(r1)
/* 8000A0C0 00006CA0  38 AD 80 48 */	addi r5, r13, lbl_804D36E8
/* 8000A0C4 00006CA4  90 01 00 18 */	stw r0, 0x18(r1)
/* 8000A0C8 00006CA8  80 03 00 54 */	lwz r0, 0x54(r3)
/* 8000A0CC 00006CAC  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8000A0D0 00006CB0  80 E3 00 58 */	lwz r7, 0x58(r3)
/* 8000A0D4 00006CB4  80 03 00 5C */	lwz r0, 0x5c(r3)
/* 8000A0D8 00006CB8  90 E1 00 20 */	stw r7, 0x20(r1)
/* 8000A0DC 00006CBC  90 01 00 24 */	stw r0, 0x24(r1)
/* 8000A0E0 00006CC0  80 03 00 60 */	lwz r0, 0x60(r3)
/* 8000A0E4 00006CC4  7D 03 43 78 */	mr r3, r8
/* 8000A0E8 00006CC8  90 01 00 28 */	stw r0, 0x28(r1)
/* 8000A0EC 00006CCC  4B FF EE DD */	bl lbColl_80008FC8
/* 8000A0F0 00006CD0  38 60 00 01 */	li r3, 1
/* 8000A0F4 00006CD4  48 00 00 08 */	b lbl_8000A0FC
lbl_8000A0F8:
/* 8000A0F8 00006CD8  38 60 00 00 */	li r3, 0
lbl_8000A0FC:
/* 8000A0FC 00006CDC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8000A100 00006CE0  38 21 00 30 */	addi r1, r1, 0x30
/* 8000A104 00006CE4  7C 08 03 A6 */	mtlr r0
/* 8000A108 00006CE8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern int lbl_804D36F8;
extern int lbl_804D36FC;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_8000A10C(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 8000A10C 00006CEC  7C 08 02 A6 */	mflr r0
/* 8000A110 00006CF0  38 AD 80 58 */	addi r5, r13, lbl_804D36F8
/* 8000A114 00006CF4  90 01 00 04 */	stw r0, 4(r1)
/* 8000A118 00006CF8  39 03 00 00 */	addi r8, r3, 0
/* 8000A11C 00006CFC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8000A120 00006D00  88 05 00 03 */	lbz r0, 3(r5)
/* 8000A124 00006D04  38 AD 80 58 */	addi r5, r13, lbl_804D36F8
/* 8000A128 00006D08  28 00 00 FF */	cmplwi r0, 0xff
/* 8000A12C 00006D0C  40 82 00 0C */	bne lbl_8000A138
/* 8000A130 00006D10  38 00 00 00 */	li r0, 0
/* 8000A134 00006D14  48 00 00 08 */	b lbl_8000A13C
lbl_8000A138:
/* 8000A138 00006D18  38 00 00 02 */	li r0, 2
lbl_8000A13C:
/* 8000A13C 00006D1C  7C 00 20 40 */	cmplw r0, r4
/* 8000A140 00006D20  40 82 00 54 */	bne lbl_8000A194
/* 8000A144 00006D24  80 C8 00 08 */	lwz r6, 8(r8)
/* 8000A148 00006D28  38 81 00 14 */	addi r4, r1, 0x14
/* 8000A14C 00006D2C  80 08 00 0C */	lwz r0, 0xc(r8)
/* 8000A150 00006D30  38 61 00 20 */	addi r3, r1, 0x20
/* 8000A154 00006D34  90 C1 00 14 */	stw r6, 0x14(r1)
/* 8000A158 00006D38  38 CD 80 5C */	addi r6, r13, lbl_804D36FC
/* 8000A15C 00006D3C  90 01 00 18 */	stw r0, 0x18(r1)
/* 8000A160 00006D40  80 08 00 10 */	lwz r0, 0x10(r8)
/* 8000A164 00006D44  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8000A168 00006D48  80 E8 00 14 */	lwz r7, 0x14(r8)
/* 8000A16C 00006D4C  80 08 00 18 */	lwz r0, 0x18(r8)
/* 8000A170 00006D50  90 E1 00 20 */	stw r7, 0x20(r1)
/* 8000A174 00006D54  90 01 00 24 */	stw r0, 0x24(r1)
/* 8000A178 00006D58  80 08 00 1C */	lwz r0, 0x1c(r8)
/* 8000A17C 00006D5C  90 01 00 28 */	stw r0, 0x28(r1)
/* 8000A180 00006D60  C0 08 00 00 */	lfs f0, 0(r8)
/* 8000A184 00006D64  EC 20 00 72 */	fmuls f1, f0, f1
/* 8000A188 00006D68  4B FF EE 41 */	bl lbColl_80008FC8
/* 8000A18C 00006D6C  38 60 00 01 */	li r3, 1
/* 8000A190 00006D70  48 00 00 08 */	b lbl_8000A198
lbl_8000A194:
/* 8000A194 00006D74  38 60 00 00 */	li r3, 0
lbl_8000A198:
/* 8000A198 00006D78  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8000A19C 00006D7C  38 21 00 30 */	addi r1, r1, 0x30
/* 8000A1A0 00006D80  7C 08 03 A6 */	mtlr r0
/* 8000A1A4 00006D84  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern int lbl_804D36F0;
extern int lbl_804D36F4;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_8000A1A8(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 8000A1A8 00006D88  7C 08 02 A6 */	mflr r0
/* 8000A1AC 00006D8C  38 AD 80 50 */	addi r5, r13, lbl_804D36F0
/* 8000A1B0 00006D90  90 01 00 04 */	stw r0, 4(r1)
/* 8000A1B4 00006D94  39 03 00 00 */	addi r8, r3, 0
/* 8000A1B8 00006D98  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8000A1BC 00006D9C  88 05 00 03 */	lbz r0, 3(r5)
/* 8000A1C0 00006DA0  28 00 00 FF */	cmplwi r0, 0xff
/* 8000A1C4 00006DA4  40 82 00 0C */	bne lbl_8000A1D0
/* 8000A1C8 00006DA8  38 00 00 00 */	li r0, 0
/* 8000A1CC 00006DAC  48 00 00 08 */	b lbl_8000A1D4
lbl_8000A1D0:
/* 8000A1D0 00006DB0  38 00 00 02 */	li r0, 2
lbl_8000A1D4:
/* 8000A1D4 00006DB4  7C 00 20 40 */	cmplw r0, r4
/* 8000A1D8 00006DB8  40 82 00 58 */	bne lbl_8000A230
/* 8000A1DC 00006DBC  80 A8 00 08 */	lwz r5, 8(r8)
/* 8000A1E0 00006DC0  38 81 00 14 */	addi r4, r1, 0x14
/* 8000A1E4 00006DC4  80 08 00 0C */	lwz r0, 0xc(r8)
/* 8000A1E8 00006DC8  38 61 00 20 */	addi r3, r1, 0x20
/* 8000A1EC 00006DCC  38 CD 80 54 */	addi r6, r13, lbl_804D36F4
/* 8000A1F0 00006DD0  90 A1 00 14 */	stw r5, 0x14(r1)
/* 8000A1F4 00006DD4  38 AD 80 50 */	addi r5, r13, lbl_804D36F0
/* 8000A1F8 00006DD8  90 01 00 18 */	stw r0, 0x18(r1)
/* 8000A1FC 00006DDC  80 08 00 10 */	lwz r0, 0x10(r8)
/* 8000A200 00006DE0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8000A204 00006DE4  80 E8 00 14 */	lwz r7, 0x14(r8)
/* 8000A208 00006DE8  80 08 00 18 */	lwz r0, 0x18(r8)
/* 8000A20C 00006DEC  90 E1 00 20 */	stw r7, 0x20(r1)
/* 8000A210 00006DF0  90 01 00 24 */	stw r0, 0x24(r1)
/* 8000A214 00006DF4  80 08 00 1C */	lwz r0, 0x1c(r8)
/* 8000A218 00006DF8  90 01 00 28 */	stw r0, 0x28(r1)
/* 8000A21C 00006DFC  C0 08 00 00 */	lfs f0, 0(r8)
/* 8000A220 00006E00  EC 20 00 72 */	fmuls f1, f0, f1
/* 8000A224 00006E04  4B FF ED A5 */	bl lbColl_80008FC8
/* 8000A228 00006E08  38 60 00 01 */	li r3, 1
/* 8000A22C 00006E0C  48 00 00 08 */	b lbl_8000A234
lbl_8000A230:
/* 8000A230 00006E10  38 60 00 00 */	li r3, 0
lbl_8000A234:
/* 8000A234 00006E14  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8000A238 00006E18  38 21 00 30 */	addi r1, r1, 0x30
/* 8000A23C 00006E1C  7C 08 03 A6 */	mtlr r0
/* 8000A240 00006E20  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_803B9928;

#ifdef MWERKS_GEKKO
#pragma push
asm void lbColl_8000A244(HurtCapsule* arg0, u32 arg1, Mtx arg2, f32 arg3)
{ // clang-format off
    nofralloc
/* 8000A244 00006E24  7C 08 02 A6 */	mflr r0
/* 8000A248 00006E28  90 01 00 04 */	stw r0, 4(r1)
/* 8000A24C 00006E2C  94 21 FF 18 */	stwu r1, -0xe8(r1)
/* 8000A250 00006E30  DB E1 00 E0 */	stfd f31, 0xe0(r1)
/* 8000A254 00006E34  FF E0 08 90 */	fmr f31, f1
/* 8000A258 00006E38  93 E1 00 DC */	stw r31, 0xdc(r1)
/* 8000A25C 00006E3C  93 C1 00 D8 */	stw r30, 0xd8(r1)
/* 8000A260 00006E40  93 A1 00 D4 */	stw r29, 0xd4(r1)
/* 8000A264 00006E44  7C BD 2B 78 */	mr r29, r5
/* 8000A268 00006E48  93 81 00 D0 */	stw r28, 0xd0(r1)
/* 8000A26C 00006E4C  7C 7C 1B 78 */	mr r28, r3
/* 8000A270 00006E50  80 C3 00 00 */	lwz r6, 0(r3)
/* 8000A274 00006E54  3C 60 80 3C */	lis r3, lbl_803B9928@ha
/* 8000A278 00006E58  38 03 99 28 */	addi r0, r3, lbl_803B9928@l
/* 8000A27C 00006E5C  54 C3 18 38 */	slwi r3, r6, 3
/* 8000A280 00006E60  7C 60 1A 14 */	add r3, r0, r3
/* 8000A284 00006E64  80 63 00 00 */	lwz r3, 0(r3)
/* 8000A288 00006E68  88 03 00 03 */	lbz r0, 3(r3)
/* 8000A28C 00006E6C  3B C3 00 00 */	addi r30, r3, 0
/* 8000A290 00006E70  28 00 00 FF */	cmplwi r0, 0xff
/* 8000A294 00006E74  40 82 00 0C */	bne lbl_8000A2A0
/* 8000A298 00006E78  38 00 00 00 */	li r0, 0
/* 8000A29C 00006E7C  48 00 00 08 */	b lbl_8000A2A4
lbl_8000A2A0:
/* 8000A2A0 00006E80  38 00 00 02 */	li r0, 2
lbl_8000A2A4:
/* 8000A2A4 00006E84  7C 00 20 40 */	cmplw r0, r4
/* 8000A2A8 00006E88  40 82 01 90 */	bne lbl_8000A438
/* 8000A2AC 00006E8C  88 1C 00 24 */	lbz r0, 0x24(r28)
/* 8000A2B0 00006E90  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8000A2B4 00006E94  40 82 00 44 */	bne lbl_8000A2F8
/* 8000A2B8 00006E98  80 7C 00 20 */	lwz r3, 0x20(r28)
/* 8000A2BC 00006E9C  38 9C 00 04 */	addi r4, r28, 4
/* 8000A2C0 00006EA0  38 BC 00 28 */	addi r5, r28, 0x28
/* 8000A2C4 00006EA4  48 00 0F 09 */	bl func_8000B1CC
/* 8000A2C8 00006EA8  80 7C 00 20 */	lwz r3, 0x20(r28)
/* 8000A2CC 00006EAC  38 9C 00 10 */	addi r4, r28, 0x10
/* 8000A2D0 00006EB0  38 BC 00 34 */	addi r5, r28, 0x34
/* 8000A2D4 00006EB4  48 00 0E F9 */	bl func_8000B1CC
/* 8000A2D8 00006EB8  28 1D 00 00 */	cmplwi r29, 0
/* 8000A2DC 00006EBC  41 82 00 0C */	beq lbl_8000A2E8
/* 8000A2E0 00006EC0  D3 FC 00 3C */	stfs f31, 0x3c(r28)
/* 8000A2E4 00006EC4  D3 FC 00 30 */	stfs f31, 0x30(r28)
lbl_8000A2E8:
/* 8000A2E8 00006EC8  88 1C 00 24 */	lbz r0, 0x24(r28)
/* 8000A2EC 00006ECC  38 60 00 01 */	li r3, 1
/* 8000A2F0 00006ED0  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8000A2F4 00006ED4  98 1C 00 24 */	stb r0, 0x24(r28)
lbl_8000A2F8:
/* 8000A2F8 00006ED8  28 1D 00 00 */	cmplwi r29, 0
/* 8000A2FC 00006EDC  41 82 00 38 */	beq lbl_8000A334
/* 8000A300 00006EE0  83 FC 00 20 */	lwz r31, 0x20(r28)
/* 8000A304 00006EE4  28 1F 00 00 */	cmplwi r31, 0
/* 8000A308 00006EE8  40 82 00 14 */	bne lbl_8000A31C
/* 8000A30C 00006EEC  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A310 00006EF0  38 80 04 78 */	li r4, 0x478
/* 8000A314 00006EF4  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000A318 00006EF8  48 37 DF 09 */	bl __assert
lbl_8000A31C:
/* 8000A31C 00006EFC  7F E3 FB 78 */	mr r3, r31
/* 8000A320 00006F00  4B FF DA 49 */	bl lbColl_JObjSetupMatrix
/* 8000A324 00006F04  38 9F 00 44 */	addi r4, r31, 0x44
/* 8000A328 00006F08  38 7D 00 00 */	addi r3, r29, 0
/* 8000A32C 00006F0C  38 A1 00 9C */	addi r5, r1, 0x9c
/* 8000A330 00006F10  48 33 7E D5 */	bl PSMTXConcat
lbl_8000A334:
/* 8000A334 00006F14  80 1C 00 00 */	lwz r0, 0(r28)
/* 8000A338 00006F18  3C 60 80 3C */	lis r3, lbl_803B9928@ha
/* 8000A33C 00006F1C  38 63 99 28 */	addi r3, r3, lbl_803B9928@l
/* 8000A340 00006F20  C3 FC 00 1C */	lfs f31, 0x1c(r28)
/* 8000A344 00006F24  54 00 18 38 */	slwi r0, r0, 3
/* 8000A348 00006F28  7C 83 02 14 */	add r4, r3, r0
/* 8000A34C 00006F2C  80 7C 00 34 */	lwz r3, 0x34(r28)
/* 8000A350 00006F30  83 E4 00 04 */	lwz r31, 4(r4)
/* 8000A354 00006F34  28 1D 00 00 */	cmplwi r29, 0
/* 8000A358 00006F38  80 1C 00 38 */	lwz r0, 0x38(r28)
/* 8000A35C 00006F3C  90 61 00 84 */	stw r3, 0x84(r1)
/* 8000A360 00006F40  90 01 00 88 */	stw r0, 0x88(r1)
/* 8000A364 00006F44  80 1C 00 3C */	lwz r0, 0x3c(r28)
/* 8000A368 00006F48  90 01 00 8C */	stw r0, 0x8c(r1)
/* 8000A36C 00006F4C  80 7C 00 28 */	lwz r3, 0x28(r28)
/* 8000A370 00006F50  80 1C 00 2C */	lwz r0, 0x2c(r28)
/* 8000A374 00006F54  90 61 00 90 */	stw r3, 0x90(r1)
/* 8000A378 00006F58  90 01 00 94 */	stw r0, 0x94(r1)
/* 8000A37C 00006F5C  80 1C 00 30 */	lwz r0, 0x30(r28)
/* 8000A380 00006F60  90 01 00 98 */	stw r0, 0x98(r1)
/* 8000A384 00006F64  41 82 00 0C */	beq lbl_8000A390
/* 8000A388 00006F68  3B 81 00 9C */	addi r28, r1, 0x9c
/* 8000A38C 00006F6C  48 00 00 2C */	b lbl_8000A3B8
lbl_8000A390:
/* 8000A390 00006F70  83 9C 00 20 */	lwz r28, 0x20(r28)
/* 8000A394 00006F74  28 1C 00 00 */	cmplwi r28, 0
/* 8000A398 00006F78  40 82 00 14 */	bne lbl_8000A3AC
/* 8000A39C 00006F7C  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A3A0 00006F80  38 80 04 78 */	li r4, 0x478
/* 8000A3A4 00006F84  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000A3A8 00006F88  48 37 DE 79 */	bl __assert
lbl_8000A3AC:
/* 8000A3AC 00006F8C  7F 83 E3 78 */	mr r3, r28
/* 8000A3B0 00006F90  4B FF D9 B9 */	bl lbColl_JObjSetupMatrix
/* 8000A3B4 00006F94  3B 9C 00 44 */	addi r28, r28, 0x44
lbl_8000A3B8:
/* 8000A3B8 00006F98  38 7C 00 00 */	addi r3, r28, 0
/* 8000A3BC 00006F9C  38 81 00 3C */	addi r4, r1, 0x3c
/* 8000A3C0 00006FA0  48 36 EF 51 */	bl HSD_MtxInverse
/* 8000A3C4 00006FA4  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000A3C8 00006FA8  38 81 00 90 */	addi r4, r1, 0x90
/* 8000A3CC 00006FAC  38 A1 00 24 */	addi r5, r1, 0x24
/* 8000A3D0 00006FB0  48 33 86 D9 */	bl PSMTXMUltiVec
/* 8000A3D4 00006FB4  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000A3D8 00006FB8  38 81 00 84 */	addi r4, r1, 0x84
/* 8000A3DC 00006FBC  38 A1 00 30 */	addi r5, r1, 0x30
/* 8000A3E0 00006FC0  48 33 86 C9 */	bl PSMTXMUltiVec
/* 8000A3E4 00006FC4  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8000A3E8 00006FC8  FC 20 F8 90 */	fmr f1, f31
/* 8000A3EC 00006FCC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8000A3F0 00006FD0  38 A1 00 78 */	addi r5, r1, 0x78
/* 8000A3F4 00006FD4  90 61 00 78 */	stw r3, 0x78(r1)
/* 8000A3F8 00006FD8  80 C1 00 34 */	lwz r6, 0x34(r1)
/* 8000A3FC 00006FDC  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8000A400 00006FE0  38 81 00 6C */	addi r4, r1, 0x6c
/* 8000A404 00006FE4  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8000A408 00006FE8  7F 83 E3 78 */	mr r3, r28
/* 8000A40C 00006FEC  90 C1 00 7C */	stw r6, 0x7c(r1)
/* 8000A410 00006FF0  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8000A414 00006FF4  38 FF 00 00 */	addi r7, r31, 0
/* 8000A418 00006FF8  90 01 00 70 */	stw r0, 0x70(r1)
/* 8000A41C 00006FFC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8000A420 00007000  90 C1 00 80 */	stw r6, 0x80(r1)
/* 8000A424 00007004  38 DE 00 00 */	addi r6, r30, 0
/* 8000A428 00007008  90 01 00 74 */	stw r0, 0x74(r1)
/* 8000A42C 0000700C  4B FF F2 89 */	bl lbColl_800096B4
/* 8000A430 00007010  38 60 00 01 */	li r3, 1
/* 8000A434 00007014  48 00 00 08 */	b lbl_8000A43C
lbl_8000A438:
/* 8000A438 00007018  38 60 00 00 */	li r3, 0
lbl_8000A43C:
/* 8000A43C 0000701C  80 01 00 EC */	lwz r0, 0xec(r1)
/* 8000A440 00007020  CB E1 00 E0 */	lfd f31, 0xe0(r1)
/* 8000A444 00007024  83 E1 00 DC */	lwz r31, 0xdc(r1)
/* 8000A448 00007028  83 C1 00 D8 */	lwz r30, 0xd8(r1)
/* 8000A44C 0000702C  83 A1 00 D4 */	lwz r29, 0xd4(r1)
/* 8000A450 00007030  83 81 00 D0 */	lwz r28, 0xd0(r1)
/* 8000A454 00007034  38 21 00 E8 */	addi r1, r1, 0xe8
/* 8000A458 00007038  7C 08 03 A6 */	mtlr r0
/* 8000A45C 0000703C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern int lbl_804D36E0;
extern int lbl_804D36E4;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_8000A460(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 8000A460 00007040  7C 08 02 A6 */	mflr r0
/* 8000A464 00007044  38 AD 80 40 */	addi r5, r13, lbl_804D36E0
/* 8000A468 00007048  90 01 00 04 */	stw r0, 4(r1)
/* 8000A46C 0000704C  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8000A470 00007050  BF 41 00 30 */	stmw r26, 0x30(r1)
/* 8000A474 00007054  3B A3 00 00 */	addi r29, r3, 0
/* 8000A478 00007058  3B ED 80 40 */	addi r31, r13, lbl_804D36E0
/* 8000A47C 0000705C  3B CD 80 44 */	addi r30, r13, lbl_804D36E4
/* 8000A480 00007060  88 05 00 03 */	lbz r0, 3(r5)
/* 8000A484 00007064  28 00 00 FF */	cmplwi r0, 0xff
/* 8000A488 00007068  40 82 00 0C */	bne lbl_8000A494
/* 8000A48C 0000706C  38 00 00 00 */	li r0, 0
/* 8000A490 00007070  48 00 00 08 */	b lbl_8000A498
lbl_8000A494:
/* 8000A494 00007074  38 00 00 02 */	li r0, 2
lbl_8000A498:
/* 8000A498 00007078  7C 00 20 40 */	cmplw r0, r4
/* 8000A49C 0000707C  40 82 00 D0 */	bne lbl_8000A56C
/* 8000A4A0 00007080  83 7D 00 10 */	lwz r27, 0x10(r29)
/* 8000A4A4 00007084  28 1B 00 00 */	cmplwi r27, 0
/* 8000A4A8 00007088  41 82 00 44 */	beq lbl_8000A4EC
/* 8000A4AC 0000708C  40 82 00 14 */	bne lbl_8000A4C0
/* 8000A4B0 00007090  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A4B4 00007094  38 80 02 34 */	li r4, 0x234
/* 8000A4B8 00007098  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000A4BC 0000709C  48 37 DD 65 */	bl __assert
lbl_8000A4C0:
/* 8000A4C0 000070A0  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 8000A4C4 000070A4  38 60 00 00 */	li r3, 0
/* 8000A4C8 000070A8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8000A4CC 000070AC  40 82 00 10 */	bne lbl_8000A4DC
/* 8000A4D0 000070B0  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8000A4D4 000070B4  41 82 00 08 */	beq lbl_8000A4DC
/* 8000A4D8 000070B8  38 60 00 01 */	li r3, 1
lbl_8000A4DC:
/* 8000A4DC 000070BC  2C 03 00 00 */	cmpwi r3, 0
/* 8000A4E0 000070C0  41 82 00 0C */	beq lbl_8000A4EC
/* 8000A4E4 000070C4  7F 63 DB 78 */	mr r3, r27
/* 8000A4E8 000070C8  48 36 8B 91 */	bl HSD_JObjSetupMatrixSub
lbl_8000A4EC:
/* 8000A4EC 000070CC  80 7D 00 00 */	lwz r3, 0(r29)
/* 8000A4F0 000070D0  3B 81 00 14 */	addi r28, r1, 0x14
/* 8000A4F4 000070D4  80 1D 00 04 */	lwz r0, 4(r29)
/* 8000A4F8 000070D8  3B 61 00 20 */	addi r27, r1, 0x20
/* 8000A4FC 000070DC  90 61 00 14 */	stw r3, 0x14(r1)
/* 8000A500 000070E0  90 01 00 18 */	stw r0, 0x18(r1)
/* 8000A504 000070E4  80 1D 00 08 */	lwz r0, 8(r29)
/* 8000A508 000070E8  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8000A50C 000070EC  80 7D 00 00 */	lwz r3, 0(r29)
/* 8000A510 000070F0  80 1D 00 04 */	lwz r0, 4(r29)
/* 8000A514 000070F4  90 61 00 20 */	stw r3, 0x20(r1)
/* 8000A518 000070F8  90 01 00 24 */	stw r0, 0x24(r1)
/* 8000A51C 000070FC  80 1D 00 08 */	lwz r0, 8(r29)
/* 8000A520 00007100  90 01 00 28 */	stw r0, 0x28(r1)
/* 8000A524 00007104  83 5D 00 10 */	lwz r26, 0x10(r29)
/* 8000A528 00007108  28 1A 00 00 */	cmplwi r26, 0
/* 8000A52C 0000710C  40 82 00 14 */	bne lbl_8000A540
/* 8000A530 00007110  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A534 00007114  38 80 04 78 */	li r4, 0x478
/* 8000A538 00007118  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000A53C 0000711C  48 37 DC E5 */	bl __assert
lbl_8000A540:
/* 8000A540 00007120  7F 43 D3 78 */	mr r3, r26
/* 8000A544 00007124  4B FF D8 25 */	bl lbColl_JObjSetupMatrix
/* 8000A548 00007128  C0 3D 00 0C */	lfs f1, 0xc(r29)
/* 8000A54C 0000712C  38 7A 00 44 */	addi r3, r26, 0x44
/* 8000A550 00007130  38 9B 00 00 */	addi r4, r27, 0
/* 8000A554 00007134  38 BC 00 00 */	addi r5, r28, 0
/* 8000A558 00007138  38 DF 00 00 */	addi r6, r31, 0
/* 8000A55C 0000713C  38 FE 00 00 */	addi r7, r30, 0
/* 8000A560 00007140  4B FF F1 55 */	bl lbColl_800096B4
/* 8000A564 00007144  38 60 00 01 */	li r3, 1
/* 8000A568 00007148  48 00 00 08 */	b lbl_8000A570
lbl_8000A56C:
/* 8000A56C 0000714C  38 60 00 00 */	li r3, 0
lbl_8000A570:
/* 8000A570 00007150  BB 41 00 30 */	lmw r26, 0x30(r1)
/* 8000A574 00007154  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8000A578 00007158  38 21 00 48 */	addi r1, r1, 0x48
/* 8000A57C 0000715C  7C 08 03 A6 */	mtlr r0
/* 8000A580 00007160  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_8000A584(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 8000A584 00007164  7C 08 02 A6 */	mflr r0
/* 8000A588 00007168  90 01 00 04 */	stw r0, 4(r1)
/* 8000A58C 0000716C  94 21 FF 08 */	stwu r1, -0xf8(r1)
/* 8000A590 00007170  DB E1 00 F0 */	stfd f31, 0xf0(r1)
/* 8000A594 00007174  FF E0 08 90 */	fmr f31, f1
/* 8000A598 00007178  BF 61 00 DC */	stmw r27, 0xdc(r1)
/* 8000A59C 0000717C  7C 7C 1B 78 */	mr r28, r3
/* 8000A5A0 00007180  3B A6 00 00 */	addi r29, r6, 0
/* 8000A5A4 00007184  80 03 00 00 */	lwz r0, 0(r3)
/* 8000A5A8 00007188  2C 00 00 02 */	cmpwi r0, 2
/* 8000A5AC 0000718C  40 82 00 08 */	bne lbl_8000A5B4
/* 8000A5B0 00007190  38 80 00 02 */	li r4, 2
lbl_8000A5B4:
/* 8000A5B4 00007194  3C 60 80 3C */	lis r3, lbl_803B9928@ha
/* 8000A5B8 00007198  54 9F 18 38 */	slwi r31, r4, 3
/* 8000A5BC 0000719C  38 03 99 28 */	addi r0, r3, lbl_803B9928@l
/* 8000A5C0 000071A0  7C 60 FA 14 */	add r3, r0, r31
/* 8000A5C4 000071A4  80 63 00 00 */	lwz r3, 0(r3)
/* 8000A5C8 000071A8  88 03 00 03 */	lbz r0, 3(r3)
/* 8000A5CC 000071AC  3B C3 00 00 */	addi r30, r3, 0
/* 8000A5D0 000071B0  28 00 00 FF */	cmplwi r0, 0xff
/* 8000A5D4 000071B4  40 82 00 0C */	bne lbl_8000A5E0
/* 8000A5D8 000071B8  38 00 00 00 */	li r0, 0
/* 8000A5DC 000071BC  48 00 00 08 */	b lbl_8000A5E4
lbl_8000A5E0:
/* 8000A5E0 000071C0  38 00 00 02 */	li r0, 2
lbl_8000A5E4:
/* 8000A5E4 000071C4  7C 00 28 40 */	cmplw r0, r5
/* 8000A5E8 000071C8  40 82 01 88 */	bne lbl_8000A770
/* 8000A5EC 000071CC  88 1C 00 24 */	lbz r0, 0x24(r28)
/* 8000A5F0 000071D0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8000A5F4 000071D4  40 82 00 44 */	bne lbl_8000A638
/* 8000A5F8 000071D8  80 7C 00 20 */	lwz r3, 0x20(r28)
/* 8000A5FC 000071DC  38 9C 00 04 */	addi r4, r28, 4
/* 8000A600 000071E0  38 BC 00 28 */	addi r5, r28, 0x28
/* 8000A604 000071E4  48 00 0B C9 */	bl func_8000B1CC
/* 8000A608 000071E8  80 7C 00 20 */	lwz r3, 0x20(r28)
/* 8000A60C 000071EC  38 9C 00 10 */	addi r4, r28, 0x10
/* 8000A610 000071F0  38 BC 00 34 */	addi r5, r28, 0x34
/* 8000A614 000071F4  48 00 0B B9 */	bl func_8000B1CC
/* 8000A618 000071F8  28 1D 00 00 */	cmplwi r29, 0
/* 8000A61C 000071FC  41 82 00 0C */	beq lbl_8000A628
/* 8000A620 00007200  D3 FC 00 3C */	stfs f31, 0x3c(r28)
/* 8000A624 00007204  D3 FC 00 30 */	stfs f31, 0x30(r28)
lbl_8000A628:
/* 8000A628 00007208  88 1C 00 24 */	lbz r0, 0x24(r28)
/* 8000A62C 0000720C  38 60 00 01 */	li r3, 1
/* 8000A630 00007210  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8000A634 00007214  98 1C 00 24 */	stb r0, 0x24(r28)
lbl_8000A638:
/* 8000A638 00007218  28 1D 00 00 */	cmplwi r29, 0
/* 8000A63C 0000721C  41 82 00 38 */	beq lbl_8000A674
/* 8000A640 00007220  83 7C 00 20 */	lwz r27, 0x20(r28)
/* 8000A644 00007224  28 1B 00 00 */	cmplwi r27, 0
/* 8000A648 00007228  40 82 00 14 */	bne lbl_8000A65C
/* 8000A64C 0000722C  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A650 00007230  38 80 04 78 */	li r4, 0x478
/* 8000A654 00007234  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000A658 00007238  48 37 DB C9 */	bl __assert
lbl_8000A65C:
/* 8000A65C 0000723C  7F 63 DB 78 */	mr r3, r27
/* 8000A660 00007240  4B FF D7 09 */	bl lbColl_JObjSetupMatrix
/* 8000A664 00007244  38 9B 00 44 */	addi r4, r27, 0x44
/* 8000A668 00007248  38 7D 00 00 */	addi r3, r29, 0
/* 8000A66C 0000724C  38 A1 00 A0 */	addi r5, r1, 0xa0
/* 8000A670 00007250  48 33 7B 95 */	bl PSMTXConcat
lbl_8000A674:
/* 8000A674 00007254  3C 60 80 3C */	lis r3, lbl_803B9928@ha
/* 8000A678 00007258  C3 FC 00 1C */	lfs f31, 0x1c(r28)
/* 8000A67C 0000725C  38 03 99 28 */	addi r0, r3, lbl_803B9928@l
/* 8000A680 00007260  80 7C 00 34 */	lwz r3, 0x34(r28)
/* 8000A684 00007264  7C 80 FA 14 */	add r4, r0, r31
/* 8000A688 00007268  80 1C 00 38 */	lwz r0, 0x38(r28)
/* 8000A68C 0000726C  83 E4 00 04 */	lwz r31, 4(r4)
/* 8000A690 00007270  28 1D 00 00 */	cmplwi r29, 0
/* 8000A694 00007274  90 61 00 88 */	stw r3, 0x88(r1)
/* 8000A698 00007278  90 01 00 8C */	stw r0, 0x8c(r1)
/* 8000A69C 0000727C  80 1C 00 3C */	lwz r0, 0x3c(r28)
/* 8000A6A0 00007280  90 01 00 90 */	stw r0, 0x90(r1)
/* 8000A6A4 00007284  80 7C 00 28 */	lwz r3, 0x28(r28)
/* 8000A6A8 00007288  80 1C 00 2C */	lwz r0, 0x2c(r28)
/* 8000A6AC 0000728C  90 61 00 94 */	stw r3, 0x94(r1)
/* 8000A6B0 00007290  90 01 00 98 */	stw r0, 0x98(r1)
/* 8000A6B4 00007294  80 1C 00 30 */	lwz r0, 0x30(r28)
/* 8000A6B8 00007298  90 01 00 9C */	stw r0, 0x9c(r1)
/* 8000A6BC 0000729C  41 82 00 0C */	beq lbl_8000A6C8
/* 8000A6C0 000072A0  3B 81 00 A0 */	addi r28, r1, 0xa0
/* 8000A6C4 000072A4  48 00 00 2C */	b lbl_8000A6F0
lbl_8000A6C8:
/* 8000A6C8 000072A8  83 7C 00 20 */	lwz r27, 0x20(r28)
/* 8000A6CC 000072AC  28 1B 00 00 */	cmplwi r27, 0
/* 8000A6D0 000072B0  40 82 00 14 */	bne lbl_8000A6E4
/* 8000A6D4 000072B4  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A6D8 000072B8  38 80 04 78 */	li r4, 0x478
/* 8000A6DC 000072BC  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000A6E0 000072C0  48 37 DB 41 */	bl __assert
lbl_8000A6E4:
/* 8000A6E4 000072C4  7F 63 DB 78 */	mr r3, r27
/* 8000A6E8 000072C8  4B FF D6 81 */	bl lbColl_JObjSetupMatrix
/* 8000A6EC 000072CC  3B 9B 00 44 */	addi r28, r27, 0x44
lbl_8000A6F0:
/* 8000A6F0 000072D0  38 7C 00 00 */	addi r3, r28, 0
/* 8000A6F4 000072D4  38 81 00 40 */	addi r4, r1, 0x40
/* 8000A6F8 000072D8  48 36 EC 19 */	bl HSD_MtxInverse
/* 8000A6FC 000072DC  38 61 00 40 */	addi r3, r1, 0x40
/* 8000A700 000072E0  38 81 00 94 */	addi r4, r1, 0x94
/* 8000A704 000072E4  38 A1 00 28 */	addi r5, r1, 0x28
/* 8000A708 000072E8  48 33 83 A1 */	bl PSMTXMUltiVec
/* 8000A70C 000072EC  38 61 00 40 */	addi r3, r1, 0x40
/* 8000A710 000072F0  38 81 00 88 */	addi r4, r1, 0x88
/* 8000A714 000072F4  38 A1 00 34 */	addi r5, r1, 0x34
/* 8000A718 000072F8  48 33 83 91 */	bl PSMTXMUltiVec
/* 8000A71C 000072FC  80 61 00 34 */	lwz r3, 0x34(r1)
/* 8000A720 00007300  FC 20 F8 90 */	fmr f1, f31
/* 8000A724 00007304  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8000A728 00007308  38 A1 00 7C */	addi r5, r1, 0x7c
/* 8000A72C 0000730C  90 61 00 7C */	stw r3, 0x7c(r1)
/* 8000A730 00007310  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8000A734 00007314  90 01 00 70 */	stw r0, 0x70(r1)
/* 8000A738 00007318  38 81 00 70 */	addi r4, r1, 0x70
/* 8000A73C 0000731C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8000A740 00007320  7F 83 E3 78 */	mr r3, r28
/* 8000A744 00007324  90 C1 00 80 */	stw r6, 0x80(r1)
/* 8000A748 00007328  80 C1 00 3C */	lwz r6, 0x3c(r1)
/* 8000A74C 0000732C  38 FF 00 00 */	addi r7, r31, 0
/* 8000A750 00007330  90 01 00 74 */	stw r0, 0x74(r1)
/* 8000A754 00007334  80 01 00 30 */	lwz r0, 0x30(r1)
/* 8000A758 00007338  90 C1 00 84 */	stw r6, 0x84(r1)
/* 8000A75C 0000733C  38 DE 00 00 */	addi r6, r30, 0
/* 8000A760 00007340  90 01 00 78 */	stw r0, 0x78(r1)
/* 8000A764 00007344  4B FF EF 51 */	bl lbColl_800096B4
/* 8000A768 00007348  38 60 00 01 */	li r3, 1
/* 8000A76C 0000734C  48 00 00 08 */	b lbl_8000A774
lbl_8000A770:
/* 8000A770 00007350  38 60 00 00 */	li r3, 0
lbl_8000A774:
/* 8000A774 00007354  BB 61 00 DC */	lmw r27, 0xdc(r1)
/* 8000A778 00007358  80 01 00 FC */	lwz r0, 0xfc(r1)
/* 8000A77C 0000735C  CB E1 00 F0 */	lfd f31, 0xf0(r1)
/* 8000A780 00007360  38 21 00 F8 */	addi r1, r1, 0xf8
/* 8000A784 00007364  7C 08 03 A6 */	mtlr r0
/* 8000A788 00007368  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern int lbl_804D36C4;
extern int lbl_804D36C8;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_8000A78C(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 8000A78C 0000736C  7C 08 02 A6 */	mflr r0
/* 8000A790 00007370  38 CD 80 24 */	addi r6, r13, lbl_804D36C4
/* 8000A794 00007374  90 01 00 04 */	stw r0, 4(r1)
/* 8000A798 00007378  94 21 FF 18 */	stwu r1, -0xe8(r1)
/* 8000A79C 0000737C  DB E1 00 E0 */	stfd f31, 0xe0(r1)
/* 8000A7A0 00007380  FF E0 08 90 */	fmr f31, f1
/* 8000A7A4 00007384  93 E1 00 DC */	stw r31, 0xdc(r1)
/* 8000A7A8 00007388  93 C1 00 D8 */	stw r30, 0xd8(r1)
/* 8000A7AC 0000738C  3B C5 00 00 */	addi r30, r5, 0
/* 8000A7B0 00007390  93 A1 00 D4 */	stw r29, 0xd4(r1)
/* 8000A7B4 00007394  3B A3 00 00 */	addi r29, r3, 0
/* 8000A7B8 00007398  88 06 00 03 */	lbz r0, 3(r6)
/* 8000A7BC 0000739C  28 00 00 FF */	cmplwi r0, 0xff
/* 8000A7C0 000073A0  40 82 00 0C */	bne lbl_8000A7CC
/* 8000A7C4 000073A4  38 00 00 00 */	li r0, 0
/* 8000A7C8 000073A8  48 00 00 08 */	b lbl_8000A7D0
lbl_8000A7CC:
/* 8000A7CC 000073AC  38 00 00 02 */	li r0, 2
lbl_8000A7D0:
/* 8000A7D0 000073B0  7C 00 20 40 */	cmplw r0, r4
/* 8000A7D4 000073B4  40 82 01 64 */	bne lbl_8000A938
/* 8000A7D8 000073B8  88 1D 00 04 */	lbz r0, 4(r29)
/* 8000A7DC 000073BC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8000A7E0 000073C0  40 82 00 30 */	bne lbl_8000A810
/* 8000A7E4 000073C4  80 7D 00 00 */	lwz r3, 0(r29)
/* 8000A7E8 000073C8  38 9D 00 14 */	addi r4, r29, 0x14
/* 8000A7EC 000073CC  38 BD 00 08 */	addi r5, r29, 8
/* 8000A7F0 000073D0  48 00 09 DD */	bl func_8000B1CC
/* 8000A7F4 000073D4  28 1E 00 00 */	cmplwi r30, 0
/* 8000A7F8 000073D8  41 82 00 08 */	beq lbl_8000A800
/* 8000A7FC 000073DC  D3 FD 00 10 */	stfs f31, 0x10(r29)
lbl_8000A800:
/* 8000A800 000073E0  88 1D 00 04 */	lbz r0, 4(r29)
/* 8000A804 000073E4  38 60 00 01 */	li r3, 1
/* 8000A808 000073E8  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8000A80C 000073EC  98 1D 00 04 */	stb r0, 4(r29)
lbl_8000A810:
/* 8000A810 000073F0  28 1E 00 00 */	cmplwi r30, 0
/* 8000A814 000073F4  41 82 00 38 */	beq lbl_8000A84C
/* 8000A818 000073F8  83 FD 00 00 */	lwz r31, 0(r29)
/* 8000A81C 000073FC  28 1F 00 00 */	cmplwi r31, 0
/* 8000A820 00007400  40 82 00 14 */	bne lbl_8000A834
/* 8000A824 00007404  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A828 00007408  38 80 04 78 */	li r4, 0x478
/* 8000A82C 0000740C  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000A830 00007410  48 37 D9 F1 */	bl __assert
lbl_8000A834:
/* 8000A834 00007414  7F E3 FB 78 */	mr r3, r31
/* 8000A838 00007418  4B FF D5 31 */	bl lbColl_JObjSetupMatrix
/* 8000A83C 0000741C  38 9F 00 44 */	addi r4, r31, 0x44
/* 8000A840 00007420  38 7E 00 00 */	addi r3, r30, 0
/* 8000A844 00007424  38 A1 00 9C */	addi r5, r1, 0x9c
/* 8000A848 00007428  48 33 79 BD */	bl PSMTXConcat
lbl_8000A84C:
/* 8000A84C 0000742C  C3 FD 00 20 */	lfs f31, 0x20(r29)
/* 8000A850 00007430  28 1E 00 00 */	cmplwi r30, 0
/* 8000A854 00007434  80 7D 00 08 */	lwz r3, 8(r29)
/* 8000A858 00007438  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8000A85C 0000743C  90 61 00 84 */	stw r3, 0x84(r1)
/* 8000A860 00007440  90 01 00 88 */	stw r0, 0x88(r1)
/* 8000A864 00007444  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8000A868 00007448  90 01 00 8C */	stw r0, 0x8c(r1)
/* 8000A86C 0000744C  80 7D 00 08 */	lwz r3, 8(r29)
/* 8000A870 00007450  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8000A874 00007454  90 61 00 90 */	stw r3, 0x90(r1)
/* 8000A878 00007458  90 01 00 94 */	stw r0, 0x94(r1)
/* 8000A87C 0000745C  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8000A880 00007460  90 01 00 98 */	stw r0, 0x98(r1)
/* 8000A884 00007464  41 82 00 0C */	beq lbl_8000A890
/* 8000A888 00007468  3B E1 00 9C */	addi r31, r1, 0x9c
/* 8000A88C 0000746C  48 00 00 2C */	b lbl_8000A8B8
lbl_8000A890:
/* 8000A890 00007470  83 FD 00 00 */	lwz r31, 0(r29)
/* 8000A894 00007474  28 1F 00 00 */	cmplwi r31, 0
/* 8000A898 00007478  40 82 00 14 */	bne lbl_8000A8AC
/* 8000A89C 0000747C  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A8A0 00007480  38 80 04 78 */	li r4, 0x478
/* 8000A8A4 00007484  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000A8A8 00007488  48 37 D9 79 */	bl __assert
lbl_8000A8AC:
/* 8000A8AC 0000748C  7F E3 FB 78 */	mr r3, r31
/* 8000A8B0 00007490  4B FF D4 B9 */	bl lbColl_JObjSetupMatrix
/* 8000A8B4 00007494  3B FF 00 44 */	addi r31, r31, 0x44
lbl_8000A8B8:
/* 8000A8B8 00007498  38 7F 00 00 */	addi r3, r31, 0
/* 8000A8BC 0000749C  38 81 00 3C */	addi r4, r1, 0x3c
/* 8000A8C0 000074A0  48 36 EA 51 */	bl HSD_MtxInverse
/* 8000A8C4 000074A4  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000A8C8 000074A8  38 81 00 90 */	addi r4, r1, 0x90
/* 8000A8CC 000074AC  38 A1 00 24 */	addi r5, r1, 0x24
/* 8000A8D0 000074B0  48 33 81 D9 */	bl PSMTXMUltiVec
/* 8000A8D4 000074B4  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000A8D8 000074B8  38 81 00 84 */	addi r4, r1, 0x84
/* 8000A8DC 000074BC  38 A1 00 30 */	addi r5, r1, 0x30
/* 8000A8E0 000074C0  48 33 81 C9 */	bl PSMTXMUltiVec
/* 8000A8E4 000074C4  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8000A8E8 000074C8  FC 20 F8 90 */	fmr f1, f31
/* 8000A8EC 000074CC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8000A8F0 000074D0  38 A1 00 78 */	addi r5, r1, 0x78
/* 8000A8F4 000074D4  90 61 00 78 */	stw r3, 0x78(r1)
/* 8000A8F8 000074D8  80 C1 00 34 */	lwz r6, 0x34(r1)
/* 8000A8FC 000074DC  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8000A900 000074E0  38 81 00 6C */	addi r4, r1, 0x6c
/* 8000A904 000074E4  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8000A908 000074E8  7F E3 FB 78 */	mr r3, r31
/* 8000A90C 000074EC  90 C1 00 7C */	stw r6, 0x7c(r1)
/* 8000A910 000074F0  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8000A914 000074F4  38 ED 80 28 */	addi r7, r13, lbl_804D36C8
/* 8000A918 000074F8  90 01 00 70 */	stw r0, 0x70(r1)
/* 8000A91C 000074FC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8000A920 00007500  90 C1 00 80 */	stw r6, 0x80(r1)
/* 8000A924 00007504  38 CD 80 24 */	addi r6, r13, lbl_804D36C4
/* 8000A928 00007508  90 01 00 74 */	stw r0, 0x74(r1)
/* 8000A92C 0000750C  4B FF ED 89 */	bl lbColl_800096B4
/* 8000A930 00007510  38 60 00 01 */	li r3, 1
/* 8000A934 00007514  48 00 00 08 */	b lbl_8000A93C
lbl_8000A938:
/* 8000A938 00007518  38 60 00 00 */	li r3, 0
lbl_8000A93C:
/* 8000A93C 0000751C  80 01 00 EC */	lwz r0, 0xec(r1)
/* 8000A940 00007520  CB E1 00 E0 */	lfd f31, 0xe0(r1)
/* 8000A944 00007524  83 E1 00 DC */	lwz r31, 0xdc(r1)
/* 8000A948 00007528  83 C1 00 D8 */	lwz r30, 0xd8(r1)
/* 8000A94C 0000752C  83 A1 00 D4 */	lwz r29, 0xd4(r1)
/* 8000A950 00007530  38 21 00 E8 */	addi r1, r1, 0xe8
/* 8000A954 00007534  7C 08 03 A6 */	mtlr r0
/* 8000A958 00007538  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern int lbl_804D36CC;
extern int lbl_804D36D0;

#ifdef MWERKS_GEKKO
#pragma push
asm bool lbColl_8000A95C(HitResult*, unk_t, Mtx*, f32)
{ // clang-format off
    nofralloc
/* 8000A95C 0000753C  7C 08 02 A6 */	mflr r0
/* 8000A960 00007540  38 CD 80 2C */	addi r6, r13, lbl_804D36CC
/* 8000A964 00007544  90 01 00 04 */	stw r0, 4(r1)
/* 8000A968 00007548  94 21 FF 18 */	stwu r1, -0xe8(r1)
/* 8000A96C 0000754C  DB E1 00 E0 */	stfd f31, 0xe0(r1)
/* 8000A970 00007550  FF E0 08 90 */	fmr f31, f1
/* 8000A974 00007554  93 E1 00 DC */	stw r31, 0xdc(r1)
/* 8000A978 00007558  93 C1 00 D8 */	stw r30, 0xd8(r1)
/* 8000A97C 0000755C  3B C5 00 00 */	addi r30, r5, 0
/* 8000A980 00007560  93 A1 00 D4 */	stw r29, 0xd4(r1)
/* 8000A984 00007564  3B A3 00 00 */	addi r29, r3, 0
/* 8000A988 00007568  88 06 00 03 */	lbz r0, 3(r6)
/* 8000A98C 0000756C  28 00 00 FF */	cmplwi r0, 0xff
/* 8000A990 00007570  40 82 00 0C */	bne lbl_8000A99C
/* 8000A994 00007574  38 00 00 00 */	li r0, 0
/* 8000A998 00007578  48 00 00 08 */	b lbl_8000A9A0
lbl_8000A99C:
/* 8000A99C 0000757C  38 00 00 02 */	li r0, 2
lbl_8000A9A0:
/* 8000A9A0 00007580  7C 00 20 40 */	cmplw r0, r4
/* 8000A9A4 00007584  40 82 01 64 */	bne lbl_8000AB08
/* 8000A9A8 00007588  88 1D 00 04 */	lbz r0, 4(r29)
/* 8000A9AC 0000758C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8000A9B0 00007590  40 82 00 30 */	bne lbl_8000A9E0
/* 8000A9B4 00007594  80 7D 00 00 */	lwz r3, 0(r29)
/* 8000A9B8 00007598  38 9D 00 14 */	addi r4, r29, 0x14
/* 8000A9BC 0000759C  38 BD 00 08 */	addi r5, r29, 8
/* 8000A9C0 000075A0  48 00 08 0D */	bl func_8000B1CC
/* 8000A9C4 000075A4  28 1E 00 00 */	cmplwi r30, 0
/* 8000A9C8 000075A8  41 82 00 08 */	beq lbl_8000A9D0
/* 8000A9CC 000075AC  D3 FD 00 10 */	stfs f31, 0x10(r29)
lbl_8000A9D0:
/* 8000A9D0 000075B0  88 1D 00 04 */	lbz r0, 4(r29)
/* 8000A9D4 000075B4  38 60 00 01 */	li r3, 1
/* 8000A9D8 000075B8  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8000A9DC 000075BC  98 1D 00 04 */	stb r0, 4(r29)
lbl_8000A9E0:
/* 8000A9E0 000075C0  28 1E 00 00 */	cmplwi r30, 0
/* 8000A9E4 000075C4  41 82 00 38 */	beq lbl_8000AA1C
/* 8000A9E8 000075C8  83 FD 00 00 */	lwz r31, 0(r29)
/* 8000A9EC 000075CC  28 1F 00 00 */	cmplwi r31, 0
/* 8000A9F0 000075D0  40 82 00 14 */	bne lbl_8000AA04
/* 8000A9F4 000075D4  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000A9F8 000075D8  38 80 04 78 */	li r4, 0x478
/* 8000A9FC 000075DC  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000AA00 000075E0  48 37 D8 21 */	bl __assert
lbl_8000AA04:
/* 8000AA04 000075E4  7F E3 FB 78 */	mr r3, r31
/* 8000AA08 000075E8  4B FF D3 61 */	bl lbColl_JObjSetupMatrix
/* 8000AA0C 000075EC  38 9F 00 44 */	addi r4, r31, 0x44
/* 8000AA10 000075F0  38 7E 00 00 */	addi r3, r30, 0
/* 8000AA14 000075F4  38 A1 00 9C */	addi r5, r1, 0x9c
/* 8000AA18 000075F8  48 33 77 ED */	bl PSMTXConcat
lbl_8000AA1C:
/* 8000AA1C 000075FC  C3 FD 00 20 */	lfs f31, 0x20(r29)
/* 8000AA20 00007600  28 1E 00 00 */	cmplwi r30, 0
/* 8000AA24 00007604  80 7D 00 08 */	lwz r3, 8(r29)
/* 8000AA28 00007608  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8000AA2C 0000760C  90 61 00 84 */	stw r3, 0x84(r1)
/* 8000AA30 00007610  90 01 00 88 */	stw r0, 0x88(r1)
/* 8000AA34 00007614  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8000AA38 00007618  90 01 00 8C */	stw r0, 0x8c(r1)
/* 8000AA3C 0000761C  80 7D 00 08 */	lwz r3, 8(r29)
/* 8000AA40 00007620  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8000AA44 00007624  90 61 00 90 */	stw r3, 0x90(r1)
/* 8000AA48 00007628  90 01 00 94 */	stw r0, 0x94(r1)
/* 8000AA4C 0000762C  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8000AA50 00007630  90 01 00 98 */	stw r0, 0x98(r1)
/* 8000AA54 00007634  41 82 00 0C */	beq lbl_8000AA60
/* 8000AA58 00007638  3B E1 00 9C */	addi r31, r1, 0x9c
/* 8000AA5C 0000763C  48 00 00 2C */	b lbl_8000AA88
lbl_8000AA60:
/* 8000AA60 00007640  83 FD 00 00 */	lwz r31, 0(r29)
/* 8000AA64 00007644  28 1F 00 00 */	cmplwi r31, 0
/* 8000AA68 00007648  40 82 00 14 */	bne lbl_8000AA7C
/* 8000AA6C 0000764C  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000AA70 00007650  38 80 04 78 */	li r4, 0x478
/* 8000AA74 00007654  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000AA78 00007658  48 37 D7 A9 */	bl __assert
lbl_8000AA7C:
/* 8000AA7C 0000765C  7F E3 FB 78 */	mr r3, r31
/* 8000AA80 00007660  4B FF D2 E9 */	bl lbColl_JObjSetupMatrix
/* 8000AA84 00007664  3B FF 00 44 */	addi r31, r31, 0x44
lbl_8000AA88:
/* 8000AA88 00007668  38 7F 00 00 */	addi r3, r31, 0
/* 8000AA8C 0000766C  38 81 00 3C */	addi r4, r1, 0x3c
/* 8000AA90 00007670  48 36 E8 81 */	bl HSD_MtxInverse
/* 8000AA94 00007674  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000AA98 00007678  38 81 00 90 */	addi r4, r1, 0x90
/* 8000AA9C 0000767C  38 A1 00 24 */	addi r5, r1, 0x24
/* 8000AAA0 00007680  48 33 80 09 */	bl PSMTXMUltiVec
/* 8000AAA4 00007684  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000AAA8 00007688  38 81 00 84 */	addi r4, r1, 0x84
/* 8000AAAC 0000768C  38 A1 00 30 */	addi r5, r1, 0x30
/* 8000AAB0 00007690  48 33 7F F9 */	bl PSMTXMUltiVec
/* 8000AAB4 00007694  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8000AAB8 00007698  FC 20 F8 90 */	fmr f1, f31
/* 8000AABC 0000769C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8000AAC0 000076A0  38 A1 00 78 */	addi r5, r1, 0x78
/* 8000AAC4 000076A4  90 61 00 78 */	stw r3, 0x78(r1)
/* 8000AAC8 000076A8  80 C1 00 34 */	lwz r6, 0x34(r1)
/* 8000AACC 000076AC  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8000AAD0 000076B0  38 81 00 6C */	addi r4, r1, 0x6c
/* 8000AAD4 000076B4  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8000AAD8 000076B8  7F E3 FB 78 */	mr r3, r31
/* 8000AADC 000076BC  90 C1 00 7C */	stw r6, 0x7c(r1)
/* 8000AAE0 000076C0  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8000AAE4 000076C4  38 ED 80 30 */	addi r7, r13, lbl_804D36D0
/* 8000AAE8 000076C8  90 01 00 70 */	stw r0, 0x70(r1)
/* 8000AAEC 000076CC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8000AAF0 000076D0  90 C1 00 80 */	stw r6, 0x80(r1)
/* 8000AAF4 000076D4  38 CD 80 2C */	addi r6, r13, lbl_804D36CC
/* 8000AAF8 000076D8  90 01 00 74 */	stw r0, 0x74(r1)
/* 8000AAFC 000076DC  4B FF EB B9 */	bl lbColl_800096B4
/* 8000AB00 000076E0  38 60 00 01 */	li r3, 1
/* 8000AB04 000076E4  48 00 00 08 */	b lbl_8000AB0C
lbl_8000AB08:
/* 8000AB08 000076E8  38 60 00 00 */	li r3, 0
lbl_8000AB0C:
/* 8000AB0C 000076EC  80 01 00 EC */	lwz r0, 0xec(r1)
/* 8000AB10 000076F0  CB E1 00 E0 */	lfd f31, 0xe0(r1)
/* 8000AB14 000076F4  83 E1 00 DC */	lwz r31, 0xdc(r1)
/* 8000AB18 000076F8  83 C1 00 D8 */	lwz r30, 0xd8(r1)
/* 8000AB1C 000076FC  83 A1 00 D4 */	lwz r29, 0xd4(r1)
/* 8000AB20 00007700  38 21 00 E8 */	addi r1, r1, 0xe8
/* 8000AB24 00007704  7C 08 03 A6 */	mtlr r0
/* 8000AB28 00007708  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else
bool lbColl_8000A95C(HitResult* arg0, void* arg1, Mtx* arg2, f32 pos_z)
{
/// @todo Combine these into #Vec3 instances.
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    s32 sp78;
    f32 sp74;
    f32 sp70;
    s32 sp6C;
    f32 sp3C;
#ifdef __clang__
#pragma clang diagnostic pop
#endif

    Vec3 sp30;
    Vec3 sp24;
    HSD_JObj* temp_r31;
    HSD_JObj* temp_r31_2;
    f32* var_r31;
    f32 temp_f31;
    u32 var_r0;

    if ((u8) M2C_FIELD(&lbl_804D36CC, u8*, 3) == 0xFF) {
        var_r0 = 0U;
    } else {
        var_r0 = 2U;
    }
    if (var_r0 == (u32) arg1) {
        if (!(((u8) M2C_FIELD(arg0, u8*, 4) >> 7U) & 1)) {
            func_8000B1CC(arg0->bone, &arg0->offset, &arg0->pos);
            if (arg2 != NULL) {
                arg0->pos.z = pos_z;
            }
            M2C_FIELD(arg0, u8*, 4) = (u8) (M2C_FIELD(arg0, u8*, 4) | 0x80);
        }
        if (arg2 != NULL) {
            temp_r31 = arg0->bone;
            if (temp_r31 == NULL) {
                __assert(lbl_804D3700, 0x478U, lbl_804D3708);
            }
            lbColl_JObjSetupMatrix(temp_r31);
            PSMTXConcat((f32(*)[4]) arg2, (f32(*)[4]) temp_r31->mtx[0],
                        (f32(*)[4]) & sp9C);
        }
        temp_f31 = arg0->size;
        sp84 = arg0->pos.x;
        sp88 = arg0->pos.y;
        sp8C = arg0->pos.z;
        sp90 = arg0->pos.x;
        sp94 = arg0->pos.y;
        sp98 = arg0->pos.z;
        if (arg2 != NULL) {
            var_r31 = &sp9C;
        } else {
            temp_r31_2 = arg0->bone;
            if (temp_r31_2 == NULL) {
                __assert(lbl_804D3700, 0x478U, lbl_804D3708);
            }
            lbColl_JObjSetupMatrix(temp_r31_2);
            var_r31 = temp_r31_2->mtx[0];
        }
        HSD_MtxInverse((f32(*)[4]) var_r31, (f32(*)[4]) & sp3C);
        PSMTXMUltiVec((f32(*)[4]) & sp3C, (Vec3*) &sp90, &sp24);
        PSMTXMUltiVec((f32(*)[4]) & sp3C, (Vec3*) &sp84, &sp30);
        sp78 = (s32) sp30.x;
        sp6C = (s32) sp24.x;
        sp7C = sp30.y;
        sp70 = sp24.y;
        sp80 = sp30.z;
        sp74 = sp24.z;
        lbColl_800096B4((f32(*)[4]) var_r31, &sp6C, &sp78, &lbl_804D36CC,
                        &lbl_804D36D0, temp_f31);
        return true;
    }

    return false;
}

#endif

extern int lbl_804D36D4;
extern int lbl_804D36D8;

#ifdef MWERKS_GEKKO
#pragma push
asm UNK_RET lbColl_8000AB2C(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 8000AB2C 0000770C  7C 08 02 A6 */	mflr r0
/* 8000AB30 00007710  38 CD 80 34 */	addi r6, r13, lbl_804D36D4
/* 8000AB34 00007714  90 01 00 04 */	stw r0, 4(r1)
/* 8000AB38 00007718  94 21 FF 18 */	stwu r1, -0xe8(r1)
/* 8000AB3C 0000771C  DB E1 00 E0 */	stfd f31, 0xe0(r1)
/* 8000AB40 00007720  FF E0 08 90 */	fmr f31, f1
/* 8000AB44 00007724  93 E1 00 DC */	stw r31, 0xdc(r1)
/* 8000AB48 00007728  93 C1 00 D8 */	stw r30, 0xd8(r1)
/* 8000AB4C 0000772C  3B C5 00 00 */	addi r30, r5, 0
/* 8000AB50 00007730  93 A1 00 D4 */	stw r29, 0xd4(r1)
/* 8000AB54 00007734  3B A3 00 00 */	addi r29, r3, 0
/* 8000AB58 00007738  88 06 00 03 */	lbz r0, 3(r6)
/* 8000AB5C 0000773C  28 00 00 FF */	cmplwi r0, 0xff
/* 8000AB60 00007740  40 82 00 0C */	bne lbl_8000AB6C
/* 8000AB64 00007744  38 00 00 00 */	li r0, 0
/* 8000AB68 00007748  48 00 00 08 */	b lbl_8000AB70
lbl_8000AB6C:
/* 8000AB6C 0000774C  38 00 00 02 */	li r0, 2
lbl_8000AB70:
/* 8000AB70 00007750  7C 00 20 40 */	cmplw r0, r4
/* 8000AB74 00007754  40 82 01 64 */	bne lbl_8000ACD8
/* 8000AB78 00007758  88 1D 00 04 */	lbz r0, 4(r29)
/* 8000AB7C 0000775C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8000AB80 00007760  40 82 00 30 */	bne lbl_8000ABB0
/* 8000AB84 00007764  80 7D 00 00 */	lwz r3, 0(r29)
/* 8000AB88 00007768  38 9D 00 14 */	addi r4, r29, 0x14
/* 8000AB8C 0000776C  38 BD 00 08 */	addi r5, r29, 8
/* 8000AB90 00007770  48 00 06 3D */	bl func_8000B1CC
/* 8000AB94 00007774  28 1E 00 00 */	cmplwi r30, 0
/* 8000AB98 00007778  41 82 00 08 */	beq lbl_8000ABA0
/* 8000AB9C 0000777C  D3 FD 00 10 */	stfs f31, 0x10(r29)
lbl_8000ABA0:
/* 8000ABA0 00007780  88 1D 00 04 */	lbz r0, 4(r29)
/* 8000ABA4 00007784  38 60 00 01 */	li r3, 1
/* 8000ABA8 00007788  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8000ABAC 0000778C  98 1D 00 04 */	stb r0, 4(r29)
lbl_8000ABB0:
/* 8000ABB0 00007790  28 1E 00 00 */	cmplwi r30, 0
/* 8000ABB4 00007794  41 82 00 38 */	beq lbl_8000ABEC
/* 8000ABB8 00007798  83 FD 00 00 */	lwz r31, 0(r29)
/* 8000ABBC 0000779C  28 1F 00 00 */	cmplwi r31, 0
/* 8000ABC0 000077A0  40 82 00 14 */	bne lbl_8000ABD4
/* 8000ABC4 000077A4  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000ABC8 000077A8  38 80 04 78 */	li r4, 0x478
/* 8000ABCC 000077AC  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000ABD0 000077B0  48 37 D6 51 */	bl __assert
lbl_8000ABD4:
/* 8000ABD4 000077B4  7F E3 FB 78 */	mr r3, r31
/* 8000ABD8 000077B8  4B FF D1 91 */	bl lbColl_JObjSetupMatrix
/* 8000ABDC 000077BC  38 9F 00 44 */	addi r4, r31, 0x44
/* 8000ABE0 000077C0  38 7E 00 00 */	addi r3, r30, 0
/* 8000ABE4 000077C4  38 A1 00 9C */	addi r5, r1, 0x9c
/* 8000ABE8 000077C8  48 33 76 1D */	bl PSMTXConcat
lbl_8000ABEC:
/* 8000ABEC 000077CC  C3 FD 00 20 */	lfs f31, 0x20(r29)
/* 8000ABF0 000077D0  28 1E 00 00 */	cmplwi r30, 0
/* 8000ABF4 000077D4  80 7D 00 08 */	lwz r3, 8(r29)
/* 8000ABF8 000077D8  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8000ABFC 000077DC  90 61 00 84 */	stw r3, 0x84(r1)
/* 8000AC00 000077E0  90 01 00 88 */	stw r0, 0x88(r1)
/* 8000AC04 000077E4  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8000AC08 000077E8  90 01 00 8C */	stw r0, 0x8c(r1)
/* 8000AC0C 000077EC  80 7D 00 08 */	lwz r3, 8(r29)
/* 8000AC10 000077F0  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 8000AC14 000077F4  90 61 00 90 */	stw r3, 0x90(r1)
/* 8000AC18 000077F8  90 01 00 94 */	stw r0, 0x94(r1)
/* 8000AC1C 000077FC  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8000AC20 00007800  90 01 00 98 */	stw r0, 0x98(r1)
/* 8000AC24 00007804  41 82 00 0C */	beq lbl_8000AC30
/* 8000AC28 00007808  3B E1 00 9C */	addi r31, r1, 0x9c
/* 8000AC2C 0000780C  48 00 00 2C */	b lbl_8000AC58
lbl_8000AC30:
/* 8000AC30 00007810  83 FD 00 00 */	lwz r31, 0(r29)
/* 8000AC34 00007814  28 1F 00 00 */	cmplwi r31, 0
/* 8000AC38 00007818  40 82 00 14 */	bne lbl_8000AC4C
/* 8000AC3C 0000781C  38 6D 80 60 */	addi r3, r13, lbl_804D3700
/* 8000AC40 00007820  38 80 04 78 */	li r4, 0x478
/* 8000AC44 00007824  38 AD 80 68 */	addi r5, r13, lbl_804D3708
/* 8000AC48 00007828  48 37 D5 D9 */	bl __assert
lbl_8000AC4C:
/* 8000AC4C 0000782C  7F E3 FB 78 */	mr r3, r31
/* 8000AC50 00007830  4B FF D1 19 */	bl lbColl_JObjSetupMatrix
/* 8000AC54 00007834  3B FF 00 44 */	addi r31, r31, 0x44
lbl_8000AC58:
/* 8000AC58 00007838  38 7F 00 00 */	addi r3, r31, 0
/* 8000AC5C 0000783C  38 81 00 3C */	addi r4, r1, 0x3c
/* 8000AC60 00007840  48 36 E6 B1 */	bl HSD_MtxInverse
/* 8000AC64 00007844  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000AC68 00007848  38 81 00 90 */	addi r4, r1, 0x90
/* 8000AC6C 0000784C  38 A1 00 24 */	addi r5, r1, 0x24
/* 8000AC70 00007850  48 33 7E 39 */	bl PSMTXMUltiVec
/* 8000AC74 00007854  38 61 00 3C */	addi r3, r1, 0x3c
/* 8000AC78 00007858  38 81 00 84 */	addi r4, r1, 0x84
/* 8000AC7C 0000785C  38 A1 00 30 */	addi r5, r1, 0x30
/* 8000AC80 00007860  48 33 7E 29 */	bl PSMTXMUltiVec
/* 8000AC84 00007864  80 61 00 30 */	lwz r3, 0x30(r1)
/* 8000AC88 00007868  FC 20 F8 90 */	fmr f1, f31
/* 8000AC8C 0000786C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8000AC90 00007870  38 A1 00 78 */	addi r5, r1, 0x78
/* 8000AC94 00007874  90 61 00 78 */	stw r3, 0x78(r1)
/* 8000AC98 00007878  80 C1 00 34 */	lwz r6, 0x34(r1)
/* 8000AC9C 0000787C  90 01 00 6C */	stw r0, 0x6c(r1)
/* 8000ACA0 00007880  38 81 00 6C */	addi r4, r1, 0x6c
/* 8000ACA4 00007884  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8000ACA8 00007888  7F E3 FB 78 */	mr r3, r31
/* 8000ACAC 0000788C  90 C1 00 7C */	stw r6, 0x7c(r1)
/* 8000ACB0 00007890  80 C1 00 38 */	lwz r6, 0x38(r1)
/* 8000ACB4 00007894  38 ED 80 38 */	addi r7, r13, lbl_804D36D8
/* 8000ACB8 00007898  90 01 00 70 */	stw r0, 0x70(r1)
/* 8000ACBC 0000789C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8000ACC0 000078A0  90 C1 00 80 */	stw r6, 0x80(r1)
/* 8000ACC4 000078A4  38 CD 80 34 */	addi r6, r13, lbl_804D36D4
/* 8000ACC8 000078A8  90 01 00 74 */	stw r0, 0x74(r1)
/* 8000ACCC 000078AC  4B FF E9 E9 */	bl lbColl_800096B4
/* 8000ACD0 000078B0  38 60 00 01 */	li r3, 1
/* 8000ACD4 000078B4  48 00 00 08 */	b lbl_8000ACDC
lbl_8000ACD8:
/* 8000ACD8 000078B8  38 60 00 00 */	li r3, 0
lbl_8000ACDC:
/* 8000ACDC 000078BC  80 01 00 EC */	lwz r0, 0xec(r1)
/* 8000ACE0 000078C0  CB E1 00 E0 */	lfd f31, 0xe0(r1)
/* 8000ACE4 000078C4  83 E1 00 DC */	lwz r31, 0xdc(r1)
/* 8000ACE8 000078C8  83 C1 00 D8 */	lwz r30, 0xd8(r1)
/* 8000ACEC 000078CC  83 A1 00 D4 */	lwz r29, 0xd4(r1)
/* 8000ACF0 000078D0  38 21 00 E8 */	addi r1, r1, 0xe8
/* 8000ACF4 000078D4  7C 08 03 A6 */	mtlr r0
/* 8000ACF8 000078D8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

bool lbColl_8000ACFC(UNK_T victim, HitCapsule* hitbox)
{
    HitVictim* victims = hitbox->victims_1;
    size_t const count = ARRAY_SIZE(hitbox->victims_1);
    size_t i;

    for (i = 0; i < count; i++) {
        if (victims[i].victim == victim)
            break;
    }

    return i == count ? false : true;
}
