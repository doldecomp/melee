#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcollision.h>

int lbl_803B9880[] = {
    0x00083D60, 0x00083D60, 0x00083D60, 0x0000005B, 0x0000005A, 0x00000059,
    0x00000058, 0x00000057, 0x00000056, 0x0000006F, 0x00000070, 0x00000071,
    0x00000054, 0x00000054, 0x00000054, 0x0000005A, 0x00000059, 0x000000DF,
    0x000000E1, 0x000000E1, 0x000000E1, 0x00000062, 0x00000063, 0x00000064,
    0x00000065, 0x00000066, 0x00000067, 0x0004461B, 0x0004461B, 0x0004461B,
    0x000000F1, 0x000000F1, 0x000000F1, 0x0000005E, 0x0000005D, 0x0000005C,
    0x00035BAF, 0x00035BB2, 0x00035BB5, 0x00083D60, 0x00083D60, 0x0000020D,
};

int func_80005BB0(Hitbox* arg0, int arg1)
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

    return func_80024184(*(lbl_803B9880 + (temp_r0 * 3) + (arg0->sfx_severity)),
                         127, 64, -1);
}

f32 const lbl_804D79F0 = 1e-5;
f32 const lbl_804D79F4 = -1e-5;
f32 const lbl_804D79F8 = 0;
f64 const lbl_804D7A00 = 1;
f32 const lbl_804D7A08 = 1;
f64 const lbl_804D7A10 = 0;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80005C44(void)
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
#endif
