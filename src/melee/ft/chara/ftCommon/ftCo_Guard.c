#include <platform.h>
#include "ft/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ftCo_Guard.h"

#include "ftCo_0C35.h"
#include "ftCo_Attack1.h"
#include "ftCo_AttackHi3.h"
#include "ftCo_AttackHi4.h"
#include "ftCo_AttackLw3.h"
#include "ftCo_AttackLw4.h"
#include "ftCo_AttackS3.h"
#include "ftCo_AttackS4.h"
#include "ftCo_Escape.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_Pass.h"
#include "ftCo_ShieldBreakFly.h"
#include "ftCo_SpecialS.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C88.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/types.h"
#include "ftYoshi/ftYs_Guard.h"
#include "ftYoshi/ftYs_Init.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00CE.h"
#include "pl/pl_0371.h"
#include "pl/player.h"

#include <common_structs.h>
#include <m2c_macros.h>
#include <math.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

#ifdef MUST_MATCH
float const ftCo_804D8538 = 0;
float const ftCo_804D853C = 2 * M_PI;
float const ftCo_804D8540 = rad_to_deg;
float const ftCo_804D8544 = 359;
float const ftCo_804D8548 = 10;
float const ftCo_804D854C = 180;
float const ftCo_804D8550 = 360;
float const ftCo_804D8554 = -180;
double const ftCo_804D8558 = 0.5;
double const ftCo_804D8560 = 3;

float const ftCo_804D8568 = 1;
float const ftCo_804D856C = 255;
double const ftCo_804D8570 = 4503601774854144;
float const ftCo_804D8578 = 0.1;

extern char* ftCo_804D3AF8; // = "jobj.h"
extern char* ftCo_804D3B00; // = "jobj"
#endif

/* 091BC4 */ static void ftCo_80091BC4(ftCo_Fighter* fp);
/* 091E78 */ static void ftCo_80091E78(ftCo_GObj* gobj, float);
/* 092158 */ static void ftCo_80092158(ftCo_GObj* gobj, int arg1,
                                       HSD_JObj* arg2);
/* 0921DC */ static void ftCo_800921DC(ftCo_GObj* gobj);
/* 0923B4 */ static void ftCo_800923B4(ftCo_GObj* gobj);
/* 0924C0 */ static void ftCo_800924C0(HSD_GObj* gobj);
/* 092908 */ static void ftCo_80092908(ftCo_GObj* gobj);
/* 092C54 */ static void ftCo_80092C54(ftCo_GObj* gobj);
/* 092E50 */ static void ftCo_80092E50(ftCo_GObj* gobj);
/* 092F2C */ static void ftCo_80092F2C(ftCo_GObj* gobj, bool);
/* 093790 */ static void ftCo_80093790(ftCo_GObj* gobj);
/* 093850 */ static void ftCo_80093850(ftCo_GObj* gobj);
/* 09388C */ static void ftCo_8009388C(ftCo_GObj* gobj);
/* 0939B4 */ static void ftCo_800939B4(ftCo_GObj* gobj);
/* 093A50 */ static void ftCo_80093A50(ftCo_GObj* gobj);

bool ftCo_80091A2C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    return fp->input.held_inputs & HSD_PAD_LR ? true : false;
}

#ifdef MUST_MATCH
#pragma push
asm bool ftCo_80091A4C(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80091A4C 0008E62C  7C 08 02 A6 */	mflr r0
/* 80091A50 0008E630  90 01 00 04 */	stw r0, 4(r1)
/* 80091A54 0008E634  94 21 FF F8 */	stwu r1, -8(r1)
/* 80091A58 0008E638  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80091A5C 0008E63C  80 06 06 68 */	lwz r0, 0x668(r6)
/* 80091A60 0008E640  54 00 06 75 */	rlwinm. r0, r0, 0, 0x19, 0x1a
/* 80091A64 0008E644  41 82 00 24 */	beq lbl_80091A88
/* 80091A68 0008E648  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80091A6C 0008E64C  88 A6 06 72 */	lbz r5, 0x672(r6)
/* 80091A70 0008E650  80 04 02 A0 */	lwz r0, 0x2a0(r4)
/* 80091A74 0008E654  7C 05 00 00 */	cmpw r5, r0
/* 80091A78 0008E658  40 80 00 10 */	bge lbl_80091A88
/* 80091A7C 0008E65C  48 00 1F 39 */	bl ftCo_800939B4
/* 80091A80 0008E660  38 60 00 01 */	li r3, 1
/* 80091A84 0008E664  48 00 00 44 */	b lbl_80091AC8
lbl_80091A88:
/* 80091A88 0008E668  80 06 06 5C */	lwz r0, 0x65c(r6)
/* 80091A8C 0008E66C  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 80091A90 0008E670  41 82 00 0C */	beq lbl_80091A9C
/* 80091A94 0008E674  38 00 00 01 */	li r0, 1
/* 80091A98 0008E678  48 00 00 08 */	b lbl_80091AA0
lbl_80091A9C:
/* 80091A9C 0008E67C  38 00 00 00 */	li r0, 0
lbl_80091AA0:
/* 80091AA0 0008E680  2C 00 00 00 */	cmpwi r0, 0
/* 80091AA4 0008E684  41 82 00 20 */	beq lbl_80091AC4
/* 80091AA8 0008E688  C0 26 19 98 */	lfs f1, 0x1998(r6)
/* 80091AAC 0008E68C  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80091AB0 0008E690  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80091AB4 0008E694  41 82 00 10 */	beq lbl_80091AC4
/* 80091AB8 0008E698  48 00 08 FD */	bl ftCo_800923B4
/* 80091ABC 0008E69C  38 60 00 01 */	li r3, 1
/* 80091AC0 0008E6A0  48 00 00 08 */	b lbl_80091AC8
lbl_80091AC4:
/* 80091AC4 0008E6A4  38 60 00 00 */	li r3, 0
lbl_80091AC8:
/* 80091AC8 0008E6A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80091ACC 0008E6AC  38 21 00 08 */	addi r1, r1, 8
/* 80091AD0 0008E6B0  7C 08 03 A6 */	mtlr r0
/* 80091AD4 0008E6B4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline bool inlineA0(ftCo_Fighter* fp)
{
    return fp->input.held_inputs & HSD_PAD_LR ? true : false;
}

int ftCo_80091A4C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.x668 & (HSD_PAD_R | HSD_PAD_L) &&
        fp->x672_input_timer_counter < p_ftCommonData->x2A0)
    {
        ftCo_800939B4(gobj);
        return true;
    }
    if (inlineA0(fp) && fp->shield_health) {
        ftCo_800923B4(gobj);
        return true;
    }
    return false;
}
#endif

#ifdef MUST_MATCH
#pragma push
asm bool ftCo_80091AD8(ftCo_GObj* gobj, int mv_x20)
{ // clang-format off
    nofralloc
/* 80091AD8 0008E6B8  7C 08 02 A6 */	mflr r0
/* 80091ADC 0008E6BC  90 01 00 04 */	stw r0, 4(r1)
/* 80091AE0 0008E6C0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80091AE4 0008E6C4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80091AE8 0008E6C8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80091AEC 0008E6CC  7C 9E 23 78 */	mr r30, r4
/* 80091AF0 0008E6D0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80091AF4 0008E6D4  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 80091AF8 0008E6D8  54 00 06 75 */	rlwinm. r0, r0, 0, 0x19, 0x1a
/* 80091AFC 0008E6DC  41 82 00 24 */	beq lbl_80091B20
/* 80091B00 0008E6E0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80091B04 0008E6E4  88 BF 06 72 */	lbz r5, 0x672(r31)
/* 80091B08 0008E6E8  80 04 02 A0 */	lwz r0, 0x2a0(r4)
/* 80091B0C 0008E6EC  7C 05 00 00 */	cmpw r5, r0
/* 80091B10 0008E6F0  40 80 00 10 */	bge lbl_80091B20
/* 80091B14 0008E6F4  48 00 1E A1 */	bl ftCo_800939B4
/* 80091B18 0008E6F8  38 00 00 01 */	li r0, 1
/* 80091B1C 0008E6FC  48 00 00 44 */	b lbl_80091B60
lbl_80091B20:
/* 80091B20 0008E700  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 80091B24 0008E704  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 80091B28 0008E708  41 82 00 0C */	beq lbl_80091B34
/* 80091B2C 0008E70C  38 00 00 01 */	li r0, 1
/* 80091B30 0008E710  48 00 00 08 */	b lbl_80091B38
lbl_80091B34:
/* 80091B34 0008E714  38 00 00 00 */	li r0, 0
lbl_80091B38:
/* 80091B38 0008E718  2C 00 00 00 */	cmpwi r0, 0
/* 80091B3C 0008E71C  41 82 00 20 */	beq lbl_80091B5C
/* 80091B40 0008E720  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 80091B44 0008E724  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80091B48 0008E728  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80091B4C 0008E72C  41 82 00 10 */	beq lbl_80091B5C
/* 80091B50 0008E730  48 00 08 65 */	bl ftCo_800923B4
/* 80091B54 0008E734  38 00 00 01 */	li r0, 1
/* 80091B58 0008E738  48 00 00 08 */	b lbl_80091B60
lbl_80091B5C:
/* 80091B5C 0008E73C  38 00 00 00 */	li r0, 0
lbl_80091B60:
/* 80091B60 0008E740  2C 00 00 00 */	cmpwi r0, 0
/* 80091B64 0008E744  41 82 00 10 */	beq lbl_80091B74
/* 80091B68 0008E748  93 DF 23 60 */	stw r30, 0x2360(r31)
/* 80091B6C 0008E74C  38 60 00 01 */	li r3, 1
/* 80091B70 0008E750  48 00 00 08 */	b lbl_80091B78
lbl_80091B74:
/* 80091B74 0008E754  38 60 00 00 */	li r3, 0
lbl_80091B78:
/* 80091B78 0008E758  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80091B7C 0008E75C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80091B80 0008E760  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80091B84 0008E764  38 21 00 28 */	addi r1, r1, 0x28
/* 80091B88 0008E768  7C 08 03 A6 */	mtlr r0
/* 80091B8C 0008E76C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo @c inline of #ftCo_80091A4C and something else.
bool ftCo_80091AD8(ftCo_GObj* gobj, int mv_x20)
{
    u8 _[16] = { 0 };
    bool ret0;
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.x668 & (HSD_PAD_R | HSD_PAD_L) &&
        fp->x672_input_timer_counter < p_ftCommonData->x2A0)
    {
        ftCo_800939B4(gobj);
        ret0 = true;
    } else {
        bool ret1;
        if (fp->input.held_inputs & HSD_PAD_LR) {
            ret1 = true;
        } else {
            ret1 = false;
        }
        if (ret1 && fp->shield_health) {
            ftCo_800923B4(gobj);
            ret0 = true;
        } else {
            ret0 = false;
        }
    }
    if (ret0 != false) {
        fp->mv.co.guard.x20 = mv_x20;
        return true;
    }
    return false;
}
#endif

void ftCo_80091B90(ftCo_GObj* gobj, int mv_x20)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x20 = mv_x20;
}

void ftCo_80091B9C(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x24 = p_ftCommonData->x68;
}

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80091BC4(Fighter* fp)
{ // clang-format off
    nofralloc
/* 80091BC4 0008E7A4  7C 08 02 A6 */	mflr r0
/* 80091BC8 0008E7A8  90 01 00 04 */	stw r0, 4(r1)
/* 80091BCC 0008E7AC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80091BD0 0008E7B0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80091BD4 0008E7B4  7C 7F 1B 78 */	mr r31, r3
/* 80091BD8 0008E7B8  C0 43 06 20 */	lfs f2, 0x620(r3)
/* 80091BDC 0008E7BC  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 80091BE0 0008E7C0  C0 23 06 24 */	lfs f1, 0x624(r3)
/* 80091BE4 0008E7C4  EC 42 00 32 */	fmuls f2, f2, f0
/* 80091BE8 0008E7C8  4B F7 B4 21 */	bl lb_8000D008
/* 80091BEC 0008E7CC  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80091BF0 0008E7D0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80091BF4 0008E7D4  40 80 00 0C */	bge lbl_80091C00
/* 80091BF8 0008E7D8  C0 02 8B 5C */	lfs f0, ftCo_804D853C
/* 80091BFC 0008E7DC  EC 21 00 2A */	fadds f1, f1, f0
lbl_80091C00:
/* 80091C00 0008E7E0  C0 42 8B 60 */	lfs f2, ftCo_804D8540
/* 80091C04 0008E7E4  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80091C08 0008E7E8  EC 22 00 72 */	fmuls f1, f2, f1
/* 80091C0C 0008E7EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80091C10 0008E7F0  FC 60 08 90 */	fmr f3, f1
/* 80091C14 0008E7F4  40 80 00 08 */	bge lbl_80091C1C
/* 80091C18 0008E7F8  FC 60 00 90 */	fmr f3, f0
lbl_80091C1C:
/* 80091C1C 0008E7FC  C0 02 8B 64 */	lfs f0, ftCo_804D8544
/* 80091C20 0008E800  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 80091C24 0008E804  40 81 00 08 */	ble lbl_80091C2C
/* 80091C28 0008E808  FC 60 00 90 */	fmr f3, f0
lbl_80091C2C:
/* 80091C2C 0008E80C  C0 5F 23 48 */	lfs f2, 0x2348(r31)
/* 80091C30 0008E810  C0 22 8B 68 */	lfs f1, ftCo_804D8548
/* 80091C34 0008E814  C0 02 8B 6C */	lfs f0, ftCo_804D854C
/* 80091C38 0008E818  EC 42 08 28 */	fsubs f2, f2, f1
/* 80091C3C 0008E81C  EC 23 10 28 */	fsubs f1, f3, f2
/* 80091C40 0008E820  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80091C44 0008E824  FC 60 08 90 */	fmr f3, f1
/* 80091C48 0008E828  40 81 00 10 */	ble lbl_80091C58
/* 80091C4C 0008E82C  C0 02 8B 70 */	lfs f0, ftCo_804D8550
/* 80091C50 0008E830  EC 63 00 28 */	fsubs f3, f3, f0
/* 80091C54 0008E834  48 00 00 18 */	b lbl_80091C6C
lbl_80091C58:
/* 80091C58 0008E838  C0 02 8B 74 */	lfs f0, ftCo_804D8554
/* 80091C5C 0008E83C  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 80091C60 0008E840  40 80 00 0C */	bge lbl_80091C6C
/* 80091C64 0008E844  C0 02 8B 70 */	lfs f0, ftCo_804D8550
/* 80091C68 0008E848  EC 63 00 2A */	fadds f3, f3, f0
lbl_80091C6C:
/* 80091C6C 0008E84C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80091C70 0008E850  C0 22 8B 70 */	lfs f1, ftCo_804D8550
/* 80091C74 0008E854  C0 03 04 4C */	lfs f0, 0x44c(r3)
/* 80091C78 0008E858  EC 03 10 3A */	fmadds f0, f3, f0, f2
/* 80091C7C 0008E85C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80091C80 0008E860  FC 40 00 90 */	fmr f2, f0
/* 80091C84 0008E864  40 81 00 0C */	ble lbl_80091C90
/* 80091C88 0008E868  EC 42 08 28 */	fsubs f2, f2, f1
/* 80091C8C 0008E86C  48 00 00 14 */	b lbl_80091CA0
lbl_80091C90:
/* 80091C90 0008E870  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80091C94 0008E874  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80091C98 0008E878  40 80 00 08 */	bge lbl_80091CA0
/* 80091C9C 0008E87C  EC 42 08 2A */	fadds f2, f2, f1
lbl_80091CA0:
/* 80091CA0 0008E880  C0 02 8B 68 */	lfs f0, ftCo_804D8548
/* 80091CA4 0008E884  EC 00 10 2A */	fadds f0, f0, f2
/* 80091CA8 0008E888  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 80091CAC 0008E88C  C0 1F 06 20 */	lfs f0, 0x620(r31)
/* 80091CB0 0008E890  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 80091CB4 0008E894  EC 40 00 32 */	fmuls f2, f0, f0
/* 80091CB8 0008E898  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80091CBC 0008E89C  EC 21 00 72 */	fmuls f1, f1, f1
/* 80091CC0 0008E8A0  EC 82 08 2A */	fadds f4, f2, f1
/* 80091CC4 0008E8A4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80091CC8 0008E8A8  40 81 00 50 */	ble lbl_80091D18
/* 80091CCC 0008E8AC  FC 20 20 34 */	frsqrte f1, f4
/* 80091CD0 0008E8B0  C8 62 8B 78 */	lfd f3, ftCo_804D8558
/* 80091CD4 0008E8B4  C8 42 8B 80 */	lfd f2, ftCo_804D8560
/* 80091CD8 0008E8B8  FC 01 00 72 */	fmul f0, f1, f1
/* 80091CDC 0008E8BC  FC 23 00 72 */	fmul f1, f3, f1
/* 80091CE0 0008E8C0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091CE4 0008E8C4  FC 21 00 32 */	fmul f1, f1, f0
/* 80091CE8 0008E8C8  FC 01 00 72 */	fmul f0, f1, f1
/* 80091CEC 0008E8CC  FC 23 00 72 */	fmul f1, f3, f1
/* 80091CF0 0008E8D0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091CF4 0008E8D4  FC 21 00 32 */	fmul f1, f1, f0
/* 80091CF8 0008E8D8  FC 01 00 72 */	fmul f0, f1, f1
/* 80091CFC 0008E8DC  FC 23 00 72 */	fmul f1, f3, f1
/* 80091D00 0008E8E0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091D04 0008E8E4  FC 01 00 32 */	fmul f0, f1, f0
/* 80091D08 0008E8E8  FC 04 00 32 */	fmul f0, f4, f0
/* 80091D0C 0008E8EC  FC 00 00 18 */	frsp f0, f0
/* 80091D10 0008E8F0  D0 01 00 0C */	stfs f0, 0xc(r1)
/* 80091D14 0008E8F4  C0 81 00 0C */	lfs f4, 0xc(r1)
lbl_80091D18:
/* 80091D18 0008E8F8  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80091D1C 0008E8FC  FC 40 20 90 */	fmr f2, f4
/* 80091D20 0008E900  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80091D24 0008E904  40 81 00 08 */	ble lbl_80091D2C
/* 80091D28 0008E908  FC 40 00 90 */	fmr f2, f0
lbl_80091D2C:
/* 80091D2C 0008E90C  C0 3F 23 44 */	lfs f1, 0x2344(r31)
/* 80091D30 0008E910  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80091D34 0008E914  EC 02 08 28 */	fsubs f0, f2, f1
/* 80091D38 0008E918  C0 43 04 4C */	lfs f2, 0x44c(r3)
/* 80091D3C 0008E91C  EC 02 08 3A */	fmadds f0, f2, f0, f1
/* 80091D40 0008E920  D0 1F 23 44 */	stfs f0, 0x2344(r31)
/* 80091D44 0008E924  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80091D48 0008E928  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80091D4C 0008E92C  38 21 00 18 */	addi r1, r1, 0x18
/* 80091D50 0008E930  7C 08 03 A6 */	mtlr r0
/* 80091D54 0008E934  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline float normalizeAngle180(float deg)
{
    if (deg > 180) {
        deg -= 360;
    } else if (deg < -180) {
        deg += 360;
    }
    return deg;
}

static inline float normalizeAngle0(float deg)
{
    if (deg > 360) {
        deg -= 360;
    } else if (deg < 0) {
        deg += 360;
    }
    return deg;
}

void ftCo_80091BC4(Fighter* fp)
{
    float lstick_x = fp->input.lstick.x * fp->facing_dir;
    float lstick_rad = lb_8000D008(fp->input.lstick.y, lstick_x);
    if (lstick_rad < 0) {
        lstick_rad += 2 * (float) M_PI;
    }
    {
        float lstick_deg = rad_to_deg * lstick_rad;
        if (lstick_deg < 0) {
            lstick_deg = 0;
        }
        if (lstick_deg > 359) {
            lstick_deg = 359;
        }
        {
            Fighter* fp0;
            float offset = (fp0 = fp)->mv.co.guard.x8 - 10;
            float deg = lstick_deg - offset;
            lstick_x = normalizeAngle180(deg);
            fp->mv.co.guard.x8 =
                10 + normalizeAngle0(lstick_x * p_ftCommonData->x44C + offset);
            {
                float lstick_mag =
                    sqrtf(SQ(fp0->input.lstick.x) + SQ(fp0->input.lstick.y));
                if (lstick_mag > 1) {
                    lstick_mag = 1;
                }
                fp->mv.co.guard.x4 = (lstick_rad = p_ftCommonData->x44C) *
                                         (lstick_mag - fp->mv.co.guard.x4) +
                                     fp->mv.co.guard.x4;
            }
        }
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80091D58(ftCo_Fighter* fp)
{ // clang-format off
    nofralloc
/* 80091D58 0008E938  7C 08 02 A6 */	mflr r0
/* 80091D5C 0008E93C  90 01 00 04 */	stw r0, 4(r1)
/* 80091D60 0008E940  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80091D64 0008E944  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80091D68 0008E948  80 03 00 04 */	lwz r0, 4(r3)
/* 80091D6C 0008E94C  2C 00 00 0E */	cmpwi r0, 0xe
/* 80091D70 0008E950  40 82 00 0C */	bne lbl_80091D7C
/* 80091D74 0008E954  C0 03 01 A0 */	lfs f0, 0x1a0(r3)
/* 80091D78 0008E958  48 00 00 44 */	b lbl_80091DBC
lbl_80091D7C:
/* 80091D7C 0008E95C  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80091D80 0008E960  C0 23 19 98 */	lfs f1, 0x1998(r3)
/* 80091D84 0008E964  C0 04 02 60 */	lfs f0, 0x260(r4)
/* 80091D88 0008E968  C0 A4 02 D4 */	lfs f5, 0x2d4(r4)
/* 80091D8C 0008E96C  EC 61 00 24 */	fdivs f3, f1, f0
/* 80091D90 0008E970  C0 04 02 D8 */	lfs f0, 0x2d8(r4)
/* 80091D94 0008E974  C0 43 19 9C */	lfs f2, 0x199c(r3)
/* 80091D98 0008E978  C0 C4 02 64 */	lfs f6, 0x264(r4)
/* 80091D9C 0008E97C  C0 82 8B 88 */	lfs f4, ftCo_804D8568
/* 80091DA0 0008E980  EC 20 28 28 */	fsubs f1, f0, f5
/* 80091DA4 0008E984  C0 03 01 A0 */	lfs f0, 0x1a0(r3)
/* 80091DA8 0008E988  EC 84 30 28 */	fsubs f4, f4, f6
/* 80091DAC 0008E98C  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80091DB0 0008E990  EC 23 00 72 */	fmuls f1, f3, f1
/* 80091DB4 0008E994  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 80091DB8 0008E998  EC 01 00 32 */	fmuls f0, f1, f0
lbl_80091DBC:
/* 80091DBC 0008E99C  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80091DC0 0008E9A0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80091DC4 0008E9A4  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80091DC8 0008E9A8  80 83 01 0C */	lwz r4, 0x10c(r3)
/* 80091DCC 0008E9AC  80 A3 05 E8 */	lwz r5, 0x5e8(r3)
/* 80091DD0 0008E9B0  80 64 00 08 */	lwz r3, 8(r4)
/* 80091DD4 0008E9B4  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80091DD8 0008E9B8  54 00 20 36 */	slwi r0, r0, 4
/* 80091DDC 0008E9BC  7F E5 00 2E */	lwzx r31, r5, r0
/* 80091DE0 0008E9C0  28 1F 00 00 */	cmplwi r31, 0
/* 80091DE4 0008E9C4  40 82 00 14 */	bne lbl_80091DF8
/* 80091DE8 0008E9C8  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 80091DEC 0008E9CC  38 80 02 F8 */	li r4, 0x2f8
/* 80091DF0 0008E9D0  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 80091DF4 0008E9D4  48 2F 64 2D */	bl __assert
lbl_80091DF8:
/* 80091DF8 0008E9D8  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80091DFC 0008E9DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80091E00 0008E9E0  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 80091E04 0008E9E4  90 1F 00 30 */	stw r0, 0x30(r31)
/* 80091E08 0008E9E8  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80091E0C 0008E9EC  90 1F 00 34 */	stw r0, 0x34(r31)
/* 80091E10 0008E9F0  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80091E14 0008E9F4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80091E18 0008E9F8  40 82 00 4C */	bne lbl_80091E64
/* 80091E1C 0008E9FC  28 1F 00 00 */	cmplwi r31, 0
/* 80091E20 0008EA00  41 82 00 44 */	beq lbl_80091E64
/* 80091E24 0008EA04  40 82 00 14 */	bne lbl_80091E38
/* 80091E28 0008EA08  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 80091E2C 0008EA0C  38 80 02 34 */	li r4, 0x234
/* 80091E30 0008EA10  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 80091E34 0008EA14  48 2F 63 ED */	bl __assert
lbl_80091E38:
/* 80091E38 0008EA18  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80091E3C 0008EA1C  38 60 00 00 */	li r3, 0
/* 80091E40 0008EA20  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80091E44 0008EA24  40 82 00 10 */	bne lbl_80091E54
/* 80091E48 0008EA28  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80091E4C 0008EA2C  41 82 00 08 */	beq lbl_80091E54
/* 80091E50 0008EA30  38 60 00 01 */	li r3, 1
lbl_80091E54:
/* 80091E54 0008EA34  2C 03 00 00 */	cmpwi r3, 0
/* 80091E58 0008EA38  40 82 00 0C */	bne lbl_80091E64
/* 80091E5C 0008EA3C  7F E3 FB 78 */	mr r3, r31
/* 80091E60 0008EA40  48 2E 14 89 */	bl HSD_JObjSetMtxDirtySub
lbl_80091E64:
/* 80091E64 0008EA44  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80091E68 0008EA48  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80091E6C 0008EA4C  38 21 00 30 */	addi r1, r1, 0x30
/* 80091E70 0008EA50  7C 08 03 A6 */	mtlr r0
/* 80091E74 0008EA54  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline float inlineB0(ftCo_Fighter* fp)
{
    if (fp->kind == FTKIND_YOSHI) {
        return fp->co_attrs.initial_shield_size;
    } else {
        float n1 =
            (fp->shield_health / p_ftCommonData->x260_startShieldHealth) *
            (fp->lightshield_amount *
                 (p_ftCommonData->x2D8 - p_ftCommonData->x2D4) +
             p_ftCommonData->x2D4);
        float n2 = 1 - p_ftCommonData->x264;
        float n3 = n2 * n1 + p_ftCommonData->x264;
        return n3 * fp->co_attrs.initial_shield_size;
    }
}

void ftCo_80091D58(Fighter* fp)
{
    Vec3 scl;
    scl.x = scl.y = scl.z = inlineB0(fp);
    HSD_JObjSetScale(fp->parts[fp->ft_data->x8->unk11].joint, &scl);
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80091E78(ftCo_GObj* gobj, float)
{ // clang-format off
    nofralloc
/* 80091E78 0008EA58  7C 08 02 A6 */	mflr r0
/* 80091E7C 0008EA5C  90 01 00 04 */	stw r0, 4(r1)
/* 80091E80 0008EA60  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80091E84 0008EA64  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 80091E88 0008EA68  FF E0 08 90 */	fmr f31, f1
/* 80091E8C 0008EA6C  93 E1 00 54 */	stw r31, 0x54(r1)
/* 80091E90 0008EA70  93 C1 00 50 */	stw r30, 0x50(r1)
/* 80091E94 0008EA74  7C 7E 1B 78 */	mr r30, r3
/* 80091E98 0008EA78  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 80091E9C 0008EA7C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80091EA0 0008EA80  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 80091EA4 0008EA84  3B E3 00 00 */	addi r31, r3, 0
/* 80091EA8 0008EA88  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80091EAC 0008EA8C  40 82 00 10 */	bne lbl_80091EBC
/* 80091EB0 0008EA90  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 80091EB4 0008EA94  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80091EB8 0008EA98  41 82 02 80 */	beq lbl_80092138
lbl_80091EBC:
/* 80091EBC 0008EA9C  7F E3 FB 78 */	mr r3, r31
/* 80091EC0 0008EAA0  4B FF FD 05 */	bl ftCo_80091BC4
/* 80091EC4 0008EAA4  C0 3F 23 44 */	lfs f1, 0x2344(r31)
/* 80091EC8 0008EAA8  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80091ECC 0008EAAC  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80091ED0 0008EAB0  41 82 00 B0 */	beq lbl_80091F80
/* 80091ED4 0008EAB4  83 BF 08 AC */	lwz r29, 0x8ac(r31)
/* 80091ED8 0008EAB8  38 7F 00 00 */	addi r3, r31, 0
/* 80091EDC 0008EABC  38 80 00 26 */	li r4, 0x26
/* 80091EE0 0008EAC0  4B FF 3F 71 */	bl ftData_80085E50
/* 80091EE4 0008EAC4  38 A3 00 00 */	addi r5, r3, 0
/* 80091EE8 0008EAC8  38 7F 00 00 */	addi r3, r31, 0
/* 80091EEC 0008EACC  38 80 00 01 */	li r4, 1
/* 80091EF0 0008EAD0  4B FD D5 D9 */	bl ftAnim_8006F4C8
/* 80091EF4 0008EAD4  7F A3 EB 78 */	mr r3, r29
/* 80091EF8 0008EAD8  C0 3F 23 48 */	lfs f1, 0x2348(r31)
/* 80091EFC 0008EADC  4B FD E8 15 */	bl ftAnim_80070710
/* 80091F00 0008EAE0  80 BF 01 08 */	lwz r5, 0x108(r31)
/* 80091F04 0008EAE4  38 7F 00 00 */	addi r3, r31, 0
/* 80091F08 0008EAE8  38 80 00 01 */	li r4, 1
/* 80091F0C 0008EAEC  80 A5 00 08 */	lwz r5, 8(r5)
/* 80091F10 0008EAF0  4B FD DC 79 */	bl ftAnim_8006FB88
/* 80091F14 0008EAF4  7F A3 EB 78 */	mr r3, r29
/* 80091F18 0008EAF8  48 2D EA 11 */	bl HSD_JObjAnimAll
/* 80091F1C 0008EAFC  C0 5F 23 44 */	lfs f2, 0x2344(r31)
/* 80091F20 0008EB00  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80091F24 0008EB04  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80091F28 0008EB08  40 80 00 24 */	bge lbl_80091F4C
/* 80091F2C 0008EB0C  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80091F30 0008EB10  EC 20 10 28 */	fsubs f1, f0, f2
/* 80091F34 0008EB14  7F E3 FB 78 */	mr r3, r31
/* 80091F38 0008EB18  80 A4 00 20 */	lwz r5, 0x20(r4)
/* 80091F3C 0008EB1C  38 80 00 01 */	li r4, 1
/* 80091F40 0008EB20  80 A5 00 00 */	lwz r5, 0(r5)
/* 80091F44 0008EB24  80 A5 00 08 */	lwz r5, 8(r5)
/* 80091F48 0008EB28  4B FD E1 C1 */	bl ftAnim_80070108
lbl_80091F4C:
/* 80091F4C 0008EB2C  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80091F50 0008EB30  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80091F54 0008EB34  40 80 00 1C */	bge lbl_80091F70
/* 80091F58 0008EB38  FC 20 F8 90 */	fmr f1, f31
/* 80091F5C 0008EB3C  7F E3 FB 78 */	mr r3, r31
/* 80091F60 0008EB40  EC 40 F8 28 */	fsubs f2, f0, f31
/* 80091F64 0008EB44  38 80 00 01 */	li r4, 1
/* 80091F68 0008EB48  4B FD DF 35 */	bl ftAnim_8006FE9C
/* 80091F6C 0008EB4C  48 00 00 64 */	b lbl_80091FD0
lbl_80091F70:
/* 80091F70 0008EB50  38 7F 00 00 */	addi r3, r31, 0
/* 80091F74 0008EB54  38 80 00 01 */	li r4, 1
/* 80091F78 0008EB58  4B FD DF FD */	bl ftAnim_8006FF74
/* 80091F7C 0008EB5C  48 00 00 54 */	b lbl_80091FD0
lbl_80091F80:
/* 80091F80 0008EB60  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80091F84 0008EB64  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80091F88 0008EB68  40 80 00 2C */	bge lbl_80091FB4
/* 80091F8C 0008EB6C  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80091F90 0008EB70  FC 20 F8 90 */	fmr f1, f31
/* 80091F94 0008EB74  EC 40 F8 28 */	fsubs f2, f0, f31
/* 80091F98 0008EB78  7F E3 FB 78 */	mr r3, r31
/* 80091F9C 0008EB7C  80 A4 00 20 */	lwz r5, 0x20(r4)
/* 80091FA0 0008EB80  38 80 00 01 */	li r4, 1
/* 80091FA4 0008EB84  80 A5 00 00 */	lwz r5, 0(r5)
/* 80091FA8 0008EB88  80 A5 00 08 */	lwz r5, 8(r5)
/* 80091FAC 0008EB8C  4B FD E0 65 */	bl ftAnim_80070010
/* 80091FB0 0008EB90  48 00 00 20 */	b lbl_80091FD0
lbl_80091FB4:
/* 80091FB4 0008EB94  80 BF 01 0C */	lwz r5, 0x10c(r31)
/* 80091FB8 0008EB98  38 7F 00 00 */	addi r3, r31, 0
/* 80091FBC 0008EB9C  38 80 00 01 */	li r4, 1
/* 80091FC0 0008EBA0  80 A5 00 20 */	lwz r5, 0x20(r5)
/* 80091FC4 0008EBA4  80 A5 00 00 */	lwz r5, 0(r5)
/* 80091FC8 0008EBA8  80 A5 00 08 */	lwz r5, 8(r5)
/* 80091FCC 0008EBAC  4B FD DA 8D */	bl ftAnim_8006FA58
lbl_80091FD0:
/* 80091FD0 0008EBB0  80 1F 00 04 */	lwz r0, 4(r31)
/* 80091FD4 0008EBB4  2C 00 00 0E */	cmpwi r0, 0xe
/* 80091FD8 0008EBB8  40 82 00 0C */	bne lbl_80091FE4
/* 80091FDC 0008EBBC  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80091FE0 0008EBC0  48 00 00 44 */	b lbl_80092024
lbl_80091FE4:
/* 80091FE4 0008EBC4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80091FE8 0008EBC8  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 80091FEC 0008EBCC  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 80091FF0 0008EBD0  C0 A3 02 D4 */	lfs f5, 0x2d4(r3)
/* 80091FF4 0008EBD4  EC 61 00 24 */	fdivs f3, f1, f0
/* 80091FF8 0008EBD8  C0 03 02 D8 */	lfs f0, 0x2d8(r3)
/* 80091FFC 0008EBDC  C0 5F 19 9C */	lfs f2, 0x199c(r31)
/* 80092000 0008EBE0  C0 C3 02 64 */	lfs f6, 0x264(r3)
/* 80092004 0008EBE4  C0 82 8B 88 */	lfs f4, ftCo_804D8568
/* 80092008 0008EBE8  EC 20 28 28 */	fsubs f1, f0, f5
/* 8009200C 0008EBEC  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80092010 0008EBF0  EC 84 30 28 */	fsubs f4, f4, f6
/* 80092014 0008EBF4  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80092018 0008EBF8  EC 23 00 72 */	fmuls f1, f3, f1
/* 8009201C 0008EBFC  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 80092020 0008EC00  EC 01 00 32 */	fmuls f0, f1, f0
lbl_80092024:
/* 80092024 0008EC04  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80092028 0008EC08  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8009202C 0008EC0C  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80092030 0008EC10  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80092034 0008EC14  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80092038 0008EC18  80 63 00 08 */	lwz r3, 8(r3)
/* 8009203C 0008EC1C  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80092040 0008EC20  54 00 20 36 */	slwi r0, r0, 4
/* 80092044 0008EC24  7F E4 00 2E */	lwzx r31, r4, r0
/* 80092048 0008EC28  28 1F 00 00 */	cmplwi r31, 0
/* 8009204C 0008EC2C  40 82 00 14 */	bne lbl_80092060
/* 80092050 0008EC30  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 80092054 0008EC34  38 80 02 F8 */	li r4, 0x2f8
/* 80092058 0008EC38  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 8009205C 0008EC3C  48 2F 61 C5 */	bl __assert
lbl_80092060:
/* 80092060 0008EC40  80 61 00 24 */	lwz r3, 0x24(r1)
/* 80092064 0008EC44  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80092068 0008EC48  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8009206C 0008EC4C  90 1F 00 30 */	stw r0, 0x30(r31)
/* 80092070 0008EC50  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80092074 0008EC54  90 1F 00 34 */	stw r0, 0x34(r31)
/* 80092078 0008EC58  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8009207C 0008EC5C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80092080 0008EC60  40 82 00 4C */	bne lbl_800920CC
/* 80092084 0008EC64  28 1F 00 00 */	cmplwi r31, 0
/* 80092088 0008EC68  41 82 00 44 */	beq lbl_800920CC
/* 8009208C 0008EC6C  40 82 00 14 */	bne lbl_800920A0
/* 80092090 0008EC70  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 80092094 0008EC74  38 80 02 34 */	li r4, 0x234
/* 80092098 0008EC78  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 8009209C 0008EC7C  48 2F 61 85 */	bl __assert
lbl_800920A0:
/* 800920A0 0008EC80  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 800920A4 0008EC84  38 60 00 00 */	li r3, 0
/* 800920A8 0008EC88  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800920AC 0008EC8C  40 82 00 10 */	bne lbl_800920BC
/* 800920B0 0008EC90  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800920B4 0008EC94  41 82 00 08 */	beq lbl_800920BC
/* 800920B8 0008EC98  38 60 00 01 */	li r3, 1
lbl_800920BC:
/* 800920BC 0008EC9C  2C 03 00 00 */	cmpwi r3, 0
/* 800920C0 0008ECA0  40 82 00 0C */	bne lbl_800920CC
/* 800920C4 0008ECA4  7F E3 FB 78 */	mr r3, r31
/* 800920C8 0008ECA8  48 2E 12 21 */	bl HSD_JObjSetMtxDirtySub
lbl_800920CC:
/* 800920CC 0008ECAC  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 800920D0 0008ECB0  80 05 00 04 */	lwz r0, 4(r5)
/* 800920D4 0008ECB4  2C 00 00 0E */	cmpwi r0, 0xe
/* 800920D8 0008ECB8  41 82 00 60 */	beq lbl_80092138
/* 800920DC 0008ECBC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800920E0 0008ECC0  3C 00 43 30 */	lis r0, 0x4330
/* 800920E4 0008ECC4  C0 02 8B 8C */	lfs f0, ftCo_804D856C
/* 800920E8 0008ECC8  7F C3 F3 78 */	mr r3, r30
/* 800920EC 0008ECCC  C0 64 02 F4 */	lfs f3, 0x2f4(r4)
/* 800920F0 0008ECD0  C0 45 19 9C */	lfs f2, 0x199c(r5)
/* 800920F4 0008ECD4  EC 00 18 28 */	fsubs f0, f0, f3
/* 800920F8 0008ECD8  C8 22 8B 90 */	lfd f1, ftCo_804D8570
/* 800920FC 0008ECDC  EC 02 00 32 */	fmuls f0, f2, f0
/* 80092100 0008ECE0  FC 00 00 1E */	fctiwz f0, f0
/* 80092104 0008ECE4  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 80092108 0008ECE8  80 81 00 44 */	lwz r4, 0x44(r1)
/* 8009210C 0008ECEC  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 80092110 0008ECF0  90 81 00 3C */	stw r4, 0x3c(r1)
/* 80092114 0008ECF4  90 01 00 38 */	stw r0, 0x38(r1)
/* 80092118 0008ECF8  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 8009211C 0008ECFC  EC 00 08 28 */	fsubs f0, f0, f1
/* 80092120 0008ED00  EC 03 00 2A */	fadds f0, f3, f0
/* 80092124 0008ED04  FC 00 00 1E */	fctiwz f0, f0
/* 80092128 0008ED08  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 8009212C 0008ED0C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80092130 0008ED10  54 04 06 3E */	clrlwi r4, r0, 0x18
/* 80092134 0008ED14  4B FC D7 31 */	bl efLib_8005F864
lbl_80092138:
/* 80092138 0008ED18  80 01 00 64 */	lwz r0, 0x64(r1)
/* 8009213C 0008ED1C  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 80092140 0008ED20  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 80092144 0008ED24  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 80092148 0008ED28  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 8009214C 0008ED2C  38 21 00 60 */	addi r1, r1, 0x60
/* 80092150 0008ED30  7C 08 03 A6 */	mtlr r0
/* 80092154 0008ED34  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline void inlineD0(ftCo_GObj* gobj)
{
    float temp_f2_2;
    float temp_f3;
    ftCo_Fighter* fp = gobj->user_data;
    if ((int) M2C_FIELD(fp, int*, 4) != 0xE) {
        temp_f3 = M2C_FIELD(p_ftCommonData, float*, 0x2F4);
        temp_f2_2 = M2C_FIELD(fp, float*, 0x199C);
        efLib_8005F864(
            gobj, (s8) (temp_f3 + (float) (int) (temp_f2_2 * (255 - temp_f3))),
            temp_f2_2, temp_f3);
    }
}

void ftCo_80091E78(HSD_GObj* gobj, float arg1)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x2218_b3 || fp->x221B_b0) {
        ftCo_80091BC4(fp);
        if (fp->mv.co.guard.x4) {
            HSD_JObj* jobj = fp->x8AC_animSkeleton;
            ftAnim_8006F4C8(fp, 1, ftData_80085E50(fp, 38));
            ftAnim_80070710(jobj, fp->mv.co.guard.x8);
            ftAnim_8006FB88(fp, 1, fp->x108_costume_joint->child);
            HSD_JObjAnimAll(jobj);
            if (fp->mv.co.guard.x4 < 1) {
                ftAnim_80070108(fp, 1, fp->ft_data->x20->x8,
                                1 - fp->mv.co.guard.x4, fp->mv.co.guard.x4);
            }
            if (arg1 < 1) {
                ftAnim_8006FE9C(fp, 1, arg1, 1 - arg1);
            } else {
                ftAnim_8006FF74(fp, 1);
            }
        } else if (arg1 < 1) {
            ftAnim_80070010(fp, 1, fp->ft_data->x20->x8, arg1, 1 - arg1);
        } else {
            ftAnim_8006FA58(fp, 1, fp->ft_data->x20->x8);
        }
        ftCo_80091D58(fp);
        inlineD0(gobj);
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80092158(ftCo_GObj* gobj, int arg1, HSD_JObj* arg2)
{ // clang-format off
    nofralloc
/* 80092158 0008ED38  7C 08 02 A6 */	mflr r0
/* 8009215C 0008ED3C  90 01 00 04 */	stw r0, 4(r1)
/* 80092160 0008ED40  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80092164 0008ED44  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80092168 0008ED48  3B E5 00 00 */	addi r31, r5, 0
/* 8009216C 0008ED4C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80092170 0008ED50  3B C4 00 00 */	addi r30, r4, 0
/* 80092174 0008ED54  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80092178 0008ED58  7C 7D 1B 78 */	mr r29, r3
/* 8009217C 0008ED5C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80092180 0008ED60  88 63 00 0C */	lbz r3, 0xc(r3)
/* 80092184 0008ED64  4B FA 43 B5 */	bl Player_GetUnk45
/* 80092188 0008ED68  80 0D AE 6C */	lwz r0, Fighter_804D650C
/* 8009218C 0008ED6C  54 64 10 3A */	slwi r4, r3, 2
/* 80092190 0008ED70  38 7E 00 00 */	addi r3, r30, 0
/* 80092194 0008ED74  4C C6 31 82 */	crclr 6
/* 80092198 0008ED78  7C E0 22 14 */	add r7, r0, r4
/* 8009219C 0008ED7C  88 07 00 01 */	lbz r0, 1(r7)
/* 800921A0 0008ED80  7F A4 EB 78 */	mr r4, r29
/* 800921A4 0008ED84  88 C7 00 00 */	lbz r6, 0(r7)
/* 800921A8 0008ED88  38 BF 00 00 */	addi r5, r31, 0
/* 800921AC 0008ED8C  54 00 40 2E */	slwi r0, r0, 8
/* 800921B0 0008ED90  88 E7 00 02 */	lbz r7, 2(r7)
/* 800921B4 0008ED94  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 800921B8 0008ED98  7C E6 03 78 */	or r6, r7, r0
/* 800921BC 0008ED9C  4B FC DC 21 */	bl efSync_Spawn
/* 800921C0 0008EDA0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800921C4 0008EDA4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800921C8 0008EDA8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800921CC 0008EDAC  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800921D0 0008EDB0  38 21 00 28 */	addi r1, r1, 0x28
/* 800921D4 0008EDB4  7C 08 03 A6 */	mtlr r0
/* 800921D8 0008EDB8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif
void ftCo_80092158(ftCo_GObj* gobj, int arg1, HSD_JObj* arg2)
{
    u8 temp_ret = Player_GetUnk45(GET_FIGHTER(gobj)->player_id);
    int* temp_r7 = &Fighter_804D650C[temp_ret];
    u8 temp_r7_2 = M2C_FIELD(temp_r7, u8*, 2);
    efSync_Spawn(arg1, gobj, arg2,
                 temp_r7_2 |
                     (((M2C_FIELD(temp_r7, u8*, 1) << 8) & ~0xFF0000) |
                      ((M2C_FIELD(temp_r7, u8*, 0) << 0x10) & 0xFF0000)),
                 temp_r7_2, M2C_BITWISE(float, temp_ret));
}
#ifdef MUST_MATCH
#pragma pop
#endif
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_800921DC(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 800921DC 0008EDBC  7C 08 02 A6 */	mflr r0
/* 800921E0 0008EDC0  90 01 00 04 */	stw r0, 4(r1)
/* 800921E4 0008EDC4  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800921E8 0008EDC8  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800921EC 0008EDCC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800921F0 0008EDD0  7C 7E 1B 78 */	mr r30, r3
/* 800921F4 0008EDD4  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 800921F8 0008EDD8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800921FC 0008EDDC  7C 7F 1B 78 */	mr r31, r3
/* 80092200 0008EDE0  88 63 00 0C */	lbz r3, 0xc(r3)
/* 80092204 0008EDE4  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80092208 0008EDE8  80 BF 05 E8 */	lwz r5, 0x5e8(r31)
/* 8009220C 0008EDEC  80 84 00 08 */	lwz r4, 8(r4)
/* 80092210 0008EDF0  88 04 00 11 */	lbz r0, 0x11(r4)
/* 80092214 0008EDF4  54 00 20 36 */	slwi r0, r0, 4
/* 80092218 0008EDF8  7F A5 00 2E */	lwzx r29, r5, r0
/* 8009221C 0008EDFC  4B FA 43 1D */	bl Player_GetUnk45
/* 80092220 0008EE00  80 0D AE 6C */	lwz r0, Fighter_804D650C
/* 80092224 0008EE04  54 63 10 3A */	slwi r3, r3, 2
/* 80092228 0008EE08  38 9E 00 00 */	addi r4, r30, 0
/* 8009222C 0008EE0C  4C C6 31 82 */	crclr 6
/* 80092230 0008EE10  7C E0 1A 14 */	add r7, r0, r3
/* 80092234 0008EE14  88 07 00 01 */	lbz r0, 1(r7)
/* 80092238 0008EE18  7F A5 EB 78 */	mr r5, r29
/* 8009223C 0008EE1C  88 C7 00 00 */	lbz r6, 0(r7)
/* 80092240 0008EE20  38 60 04 17 */	li r3, 0x417
/* 80092244 0008EE24  54 00 40 2E */	slwi r0, r0, 8
/* 80092248 0008EE28  88 E7 00 02 */	lbz r7, 2(r7)
/* 8009224C 0008EE2C  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80092250 0008EE30  7C E6 03 78 */	or r6, r7, r0
/* 80092254 0008EE34  4B FC DB 89 */	bl efSync_Spawn
/* 80092258 0008EE38  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8009225C 0008EE3C  38 60 00 01 */	li r3, 1
/* 80092260 0008EE40  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80092264 0008EE44  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 80092268 0008EE48  38 00 00 00 */	li r0, 0
/* 8009226C 0008EE4C  90 1F 23 4C */	stw r0, 0x234c(r31)
/* 80092270 0008EE50  C0 42 8B 58 */	lfs f2, ftCo_804D8538
/* 80092274 0008EE54  D0 5F 23 40 */	stfs f2, 0x2340(r31)
/* 80092278 0008EE58  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009227C 0008EE5C  C0 03 02 68 */	lfs f0, 0x268(r3)
/* 80092280 0008EE60  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 80092284 0008EE64  C0 02 8B 68 */	lfs f0, ftCo_804D8548
/* 80092288 0008EE68  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 8009228C 0008EE6C  D0 5F 23 44 */	stfs f2, 0x2344(r31)
/* 80092290 0008EE70  D0 5F 23 6C */	stfs f2, 0x236c(r31)
/* 80092294 0008EE74  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80092298 0008EE78  C0 3F 06 50 */	lfs f1, 0x650(r31)
/* 8009229C 0008EE7C  C0 63 00 10 */	lfs f3, 0x10(r3)
/* 800922A0 0008EE80  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 800922A4 0008EE84  EC 21 18 28 */	fsubs f1, f1, f3
/* 800922A8 0008EE88  EC 00 18 28 */	fsubs f0, f0, f3
/* 800922AC 0008EE8C  EC 01 00 24 */	fdivs f0, f1, f0
/* 800922B0 0008EE90  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800922B4 0008EE94  40 80 00 08 */	bge lbl_800922BC
/* 800922B8 0008EE98  C0 1F 23 6C */	lfs f0, 0x236c(r31)
lbl_800922BC:
/* 800922BC 0008EE9C  D0 1F 19 9C */	stfs f0, 0x199c(r31)
/* 800922C0 0008EEA0  38 00 00 00 */	li r0, 0
/* 800922C4 0008EEA4  90 1F 23 64 */	stw r0, 0x2364(r31)
/* 800922C8 0008EEA8  90 1F 23 60 */	stw r0, 0x2360(r31)
/* 800922CC 0008EEAC  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 800922D0 0008EEB0  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800922D4 0008EEB4  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800922D8 0008EEB8  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800922DC 0008EEBC  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 800922E0 0008EEC0  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800922E4 0008EEC4  80 63 00 08 */	lwz r3, 8(r3)
/* 800922E8 0008EEC8  88 03 00 11 */	lbz r0, 0x11(r3)
/* 800922EC 0008EECC  54 00 20 36 */	slwi r0, r0, 4
/* 800922F0 0008EED0  7F A4 00 2E */	lwzx r29, r4, r0
/* 800922F4 0008EED4  28 1D 00 00 */	cmplwi r29, 0
/* 800922F8 0008EED8  40 82 00 14 */	bne lbl_8009230C
/* 800922FC 0008EEDC  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 80092300 0008EEE0  38 80 03 94 */	li r4, 0x394
/* 80092304 0008EEE4  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 80092308 0008EEE8  48 2F 5F 19 */	bl __assert
lbl_8009230C:
/* 8009230C 0008EEEC  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80092310 0008EEF0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092314 0008EEF4  90 7D 00 38 */	stw r3, 0x38(r29)
/* 80092318 0008EEF8  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 8009231C 0008EEFC  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80092320 0008EF00  90 1D 00 40 */	stw r0, 0x40(r29)
/* 80092324 0008EF04  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80092328 0008EF08  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8009232C 0008EF0C  40 82 00 4C */	bne lbl_80092378
/* 80092330 0008EF10  28 1D 00 00 */	cmplwi r29, 0
/* 80092334 0008EF14  41 82 00 44 */	beq lbl_80092378
/* 80092338 0008EF18  40 82 00 14 */	bne lbl_8009234C
/* 8009233C 0008EF1C  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 80092340 0008EF20  38 80 02 34 */	li r4, 0x234
/* 80092344 0008EF24  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 80092348 0008EF28  48 2F 5E D9 */	bl __assert
lbl_8009234C:
/* 8009234C 0008EF2C  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80092350 0008EF30  38 60 00 00 */	li r3, 0
/* 80092354 0008EF34  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80092358 0008EF38  40 82 00 10 */	bne lbl_80092368
/* 8009235C 0008EF3C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80092360 0008EF40  41 82 00 08 */	beq lbl_80092368
/* 80092364 0008EF44  38 60 00 01 */	li r3, 1
lbl_80092368:
/* 80092368 0008EF48  2C 03 00 00 */	cmpwi r3, 0
/* 8009236C 0008EF4C  40 82 00 0C */	bne lbl_80092378
/* 80092370 0008EF50  7F A3 EB 78 */	mr r3, r29
/* 80092374 0008EF54  48 2E 0F 75 */	bl HSD_JObjSetMtxDirtySub
lbl_80092378:
/* 80092378 0008EF58  7F C3 F3 78 */	mr r3, r30
/* 8009237C 0008EF5C  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80092380 0008EF60  4B FF FA F9 */	bl ftCo_80091E78
/* 80092384 0008EF64  38 7F 00 00 */	addi r3, r31, 0
/* 80092388 0008EF68  38 80 00 6E */	li r4, 0x6e
/* 8009238C 0008EF6C  38 A0 00 7F */	li r5, 0x7f
/* 80092390 0008EF70  38 C0 00 40 */	li r6, 0x40
/* 80092394 0008EF74  4B FF 5D B5 */	bl ft_80088148
/* 80092398 0008EF78  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8009239C 0008EF7C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800923A0 0008EF80  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800923A4 0008EF84  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 800923A8 0008EF88  38 21 00 38 */	addi r1, r1, 0x38
/* 800923AC 0008EF8C  7C 08 03 A6 */	mtlr r0
/* 800923B0 0008EF90  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_800921DC(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_80092158(gobj, 1047, fp->parts[fp->ft_data->x8->unk11].joint);
    fp->x2219_b0 = true;
    fp->mv.co.guard.xC = false;
    fp->mv.co.guard.x0 = 0;
    fp->mv.co.guard.x10 = p_ftCommonData->x268;
    fp->mv.co.guard.x8 = 10;
    fp->mv.co.guard.x4 = 0;
    fp->mv.co.guard.x2C = 0;
    {
        float lightshield_amount = fp->input.x650 / (1 - p_ftCommonData->x10);
        if (lightshield_amount < 0) {
            lightshield_amount = fp->mv.co.guard.x2C;
        }
        fp->lightshield_amount = lightshield_amount;
    }
    fp->mv.co.guard.x20 = fp->mv.co.guard.x24 = 0;
    {
        Vec3 trans;
        trans.x = trans.y = trans.z = 0;
        HSD_JObjSetTranslate(fp->parts[fp->ft_data->x8->unk11].joint, &trans);
    }
    ftCo_80091E78(gobj, 0);
    ft_80088148(fp, 110, 127, 64);
}
#endif

void ftCo_800923B4(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Init_8012BECC(gobj);
        return;
    case FTKIND_MARS:
        ftCo_800924C0(gobj);
        ftParts_80074B0C(gobj, 1, 1);
        ft_80088148(fp, 190115, 127, 64);
        return;
    default:
        ftCo_800924C0(gobj);
        return;
    }
}

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80092450(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80092450 0008F030  7C 08 02 A6 */	mflr r0
/* 80092454 0008F034  3C 80 80 09 */	lis r4, ftCo_80092E50@ha
/* 80092458 0008F038  90 01 00 04 */	stw r0, 4(r1)
/* 8009245C 0008F03C  38 A4 2E 50 */	addi r5, r4, ftCo_80092E50@l
/* 80092460 0008F040  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80092464 0008F044  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80092468 0008F048  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009246C 0008F04C  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 80092470 0008F050  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80092474 0008F054  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80092478 0008F058  80 C4 00 08 */	lwz r6, 8(r4)
/* 8009247C 0008F05C  38 81 00 10 */	addi r4, r1, 0x10
/* 80092480 0008F060  88 06 00 11 */	lbz r0, 0x11(r6)
/* 80092484 0008F064  90 01 00 10 */	stw r0, 0x10(r1)
/* 80092488 0008F068  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 8009248C 0008F06C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80092490 0008F070  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80092494 0008F074  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80092498 0008F078  4B FE 8D 21 */	bl ftColl_8007B1B8
/* 8009249C 0008F07C  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800924A0 0008F080  38 60 00 01 */	li r3, 1
/* 800924A4 0008F084  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 800924A8 0008F088  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 800924AC 0008F08C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800924B0 0008F090  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800924B4 0008F094  38 21 00 30 */	addi r1, r1, 0x30
/* 800924B8 0008F098  7C 08 03 A6 */	mtlr r0
/* 800924BC 0008F09C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80092450(ftCo_GObj* gobj)
{
    AbsorbDesc absorb;
    u8 _[4] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    absorb.x0_bone_id = fp->ft_data->x8->unk11;
    absorb.x10_size = 1;
    absorb.x4_offset.x = absorb.x4_offset.y = absorb.x4_offset.z = 0.0f;
    ftColl_8007B1B8(gobj, (ShieldDesc*) &absorb, ftCo_80092E50);
    fp->x221A_b7 = true;
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_800924C0(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 800924C0 0008F0A0  7C 08 02 A6 */	mflr r0
/* 800924C4 0008F0A4  38 80 00 B2 */	li r4, 0xb2
/* 800924C8 0008F0A8  90 01 00 04 */	stw r0, 4(r1)
/* 800924CC 0008F0AC  3C A0 20 00 */	lis r5, 0x2000
/* 800924D0 0008F0B0  38 C0 00 00 */	li r6, 0
/* 800924D4 0008F0B4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800924D8 0008F0B8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800924DC 0008F0BC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800924E0 0008F0C0  7C 7E 1B 78 */	mr r30, r3
/* 800924E4 0008F0C4  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 800924E8 0008F0C8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800924EC 0008F0CC  FC 60 08 90 */	fmr f3, f1
/* 800924F0 0008F0D0  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 800924F4 0008F0D4  4B FD 6E B9 */	bl Fighter_ChangeMotionState
/* 800924F8 0008F0D8  7F C3 F3 78 */	mr r3, r30
/* 800924FC 0008F0DC  4B FD C6 A9 */	bl ftAnim_8006EBA4
/* 80092500 0008F0E0  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80092504 0008F0E4  38 C0 00 00 */	li r6, 0
/* 80092508 0008F0E8  50 C0 26 F6 */	rlwimi r0, r6, 4, 0x1b, 0x1b
/* 8009250C 0008F0EC  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80092510 0008F0F0  3C 60 80 09 */	lis r3, ftCo_80092E50@ha
/* 80092514 0008F0F4  38 A3 2E 50 */	addi r5, r3, ftCo_80092E50@l
/* 80092518 0008F0F8  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8009251C 0008F0FC  50 C0 36 72 */	rlwimi r0, r6, 6, 0x19, 0x19
/* 80092520 0008F100  38 7E 00 00 */	addi r3, r30, 0
/* 80092524 0008F104  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80092528 0008F108  38 81 00 14 */	addi r4, r1, 0x14
/* 8009252C 0008F10C  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80092530 0008F110  50 C0 2E B4 */	rlwimi r0, r6, 5, 0x1a, 0x1a
/* 80092534 0008F114  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80092538 0008F118  90 DF 23 5C */	stw r6, 0x235c(r31)
/* 8009253C 0008F11C  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80092540 0008F120  D0 3F 23 54 */	stfs f1, 0x2354(r31)
/* 80092544 0008F124  D0 3F 23 58 */	stfs f1, 0x2358(r31)
/* 80092548 0008F128  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8009254C 0008F12C  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80092550 0008F130  80 DF 01 0C */	lwz r6, 0x10c(r31)
/* 80092554 0008F134  80 C6 00 08 */	lwz r6, 8(r6)
/* 80092558 0008F138  88 06 00 11 */	lbz r0, 0x11(r6)
/* 8009255C 0008F13C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80092560 0008F140  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80092564 0008F144  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 80092568 0008F148  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8009256C 0008F14C  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80092570 0008F150  4B FE 8C 49 */	bl ftColl_8007B1B8
/* 80092574 0008F154  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 80092578 0008F158  38 60 00 01 */	li r3, 1
/* 8009257C 0008F15C  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 80092580 0008F160  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 80092584 0008F164  7F C3 F3 78 */	mr r3, r30
/* 80092588 0008F168  4B FF FC 55 */	bl ftCo_800921DC
/* 8009258C 0008F16C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80092590 0008F170  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80092594 0008F174  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80092598 0008F178  38 21 00 30 */	addi r1, r1, 0x30
/* 8009259C 0008F17C  7C 08 03 A6 */	mtlr r0
/* 800925A0 0008F180  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif

void ftCo_800924C0(ftCo_GObj* gobj)
{
    float sp24;
    float sp20;
    Vec3 sp14;
    void* fp;

    fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_GuardOn, Ft_MF_SkipAnim, 0, 1, 0,
                              NULL);
    ftAnim_8006EBA4(gobj);
    M2C_FIELD(fp, u8*, 0x221C) = (u8) (M2C_FIELD(fp, u8*, 0x221C) & ~0x10);
    M2C_FIELD(fp, u8*, 0x221C) = (u8) (M2C_FIELD(fp, u8*, 0x221C) & ~0x40);
    M2C_FIELD(fp, u8*, 0x221C) = (u8) (M2C_FIELD(fp, u8*, 0x221C) & ~0x20);
    M2C_FIELD(fp, int*, 0x235C) = 0;
    M2C_FIELD(fp, float*, 0x2354) = 0.0f;
    M2C_FIELD(fp, float*, 0x2358) = 0.0f;
    {
        ftCo_Fighter* fp = gobj->user_data;
        // sp14.x = M2C_BITWISE(
        //     float, M2C_FIELD(M2C_FIELD(M2C_FIELD(fp, void**, 0x10C), void**,
        //     8),
        //                    u8*, 0x11));
        sp14.x = M2C_BITWISE(
            float,
            M2C_FIELD(M2C_FIELD(M2C_FIELD(fp, void**, 0x10C), void**, 8), u8*,
                      0x11));
        sp24 = 1.0f;
        sp20 = 0.0f;
        sp14.y = 0.0f;
        sp14.z = 0.0f;
        // ftColl_8007B1B8(gobj, &sp14, ftCo_80092E50);
        fp->x221A_b0 = true;
    }
    ftCo_800921DC(gobj);
}

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#endif

#ifdef MUST_MATCH
#pragma push
asm bool ftCo_800925A4(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 800925A4 0008F184  7C 08 02 A6 */	mflr r0
/* 800925A8 0008F188  90 01 00 04 */	stw r0, 4(r1)
/* 800925AC 0008F18C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800925B0 0008F190  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800925B4 0008F194  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800925B8 0008F198  7C 7E 1B 78 */	mr r30, r3
/* 800925BC 0008F19C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800925C0 0008F1A0  88 03 22 1B */	lbz r0, 0x221b(r3)
/* 800925C4 0008F1A4  3B E3 00 00 */	addi r31, r3, 0
/* 800925C8 0008F1A8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800925CC 0008F1AC  41 82 00 F4 */	beq lbl_800926C0
/* 800925D0 0008F1B0  C0 1F 19 9C */	lfs f0, 0x199c(r31)
/* 800925D4 0008F1B4  D0 1F 23 6C */	stfs f0, 0x236c(r31)
/* 800925D8 0008F1B8  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800925DC 0008F1BC  C0 1F 06 50 */	lfs f0, 0x650(r31)
/* 800925E0 0008F1C0  C0 63 00 10 */	lfs f3, 0x10(r3)
/* 800925E4 0008F1C4  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 800925E8 0008F1C8  EC 40 18 28 */	fsubs f2, f0, f3
/* 800925EC 0008F1CC  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 800925F0 0008F1D0  EC 21 18 28 */	fsubs f1, f1, f3
/* 800925F4 0008F1D4  EC 22 08 24 */	fdivs f1, f2, f1
/* 800925F8 0008F1D8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800925FC 0008F1DC  40 80 00 08 */	bge lbl_80092604
/* 80092600 0008F1E0  C0 3F 23 6C */	lfs f1, 0x236c(r31)
lbl_80092604:
/* 80092604 0008F1E4  D0 3F 19 9C */	stfs f1, 0x199c(r31)
/* 80092608 0008F1E8  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009260C 0008F1EC  C0 3F 19 9C */	lfs f1, 0x199c(r31)
/* 80092610 0008F1F0  C0 83 02 EC */	lfs f4, 0x2ec(r3)
/* 80092614 0008F1F4  C0 03 02 F0 */	lfs f0, 0x2f0(r3)
/* 80092618 0008F1F8  C0 43 02 78 */	lfs f2, 0x278(r3)
/* 8009261C 0008F1FC  EC 00 20 28 */	fsubs f0, f0, f4
/* 80092620 0008F200  C0 7F 19 98 */	lfs f3, 0x1998(r31)
/* 80092624 0008F204  EC 01 20 3A */	fmadds f0, f1, f0, f4
/* 80092628 0008F208  EC 02 00 32 */	fmuls f0, f2, f0
/* 8009262C 0008F20C  EC 03 00 28 */	fsubs f0, f3, f0
/* 80092630 0008F210  D0 1F 19 98 */	stfs f0, 0x1998(r31)
/* 80092634 0008F214  C0 1F 19 98 */	lfs f0, 0x1998(r31)
/* 80092638 0008F218  C0 42 8B 58 */	lfs f2, ftCo_804D8538
/* 8009263C 0008F21C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 80092640 0008F220  40 80 00 58 */	bge lbl_80092698
/* 80092644 0008F224  D0 5F 19 98 */	stfs f2, 0x1998(r31)
/* 80092648 0008F228  38 60 00 00 */	li r3, 0
/* 8009264C 0008F22C  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 80092650 0008F230  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 80092654 0008F234  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 80092658 0008F238  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 8009265C 0008F23C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80092660 0008F240  98 1F 22 1B */	stb r0, 0x221b(r31)
/* 80092664 0008F244  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80092668 0008F248  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8009266C 0008F24C  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80092670 0008F250  4B FA BA 79 */	bl pl_8003E0E8
/* 80092674 0008F254  7F C3 F3 78 */	mr r3, r30
/* 80092678 0008F258  48 00 64 A9 */	bl ftCo_80098B20
/* 8009267C 0008F25C  38 7F 00 00 */	addi r3, r31, 0
/* 80092680 0008F260  38 80 00 81 */	li r4, 0x81
/* 80092684 0008F264  38 A0 00 7F */	li r5, 0x7f
/* 80092688 0008F268  38 C0 00 40 */	li r6, 0x40
/* 8009268C 0008F26C  4B FF 5A BD */	bl ft_80088148
/* 80092690 0008F270  38 60 00 01 */	li r3, 1
/* 80092694 0008F274  48 00 00 30 */	b lbl_800926C4
lbl_80092698:
/* 80092698 0008F278  C0 3F 23 50 */	lfs f1, 0x2350(r31)
/* 8009269C 0008F27C  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 800926A0 0008F280  40 81 00 20 */	ble lbl_800926C0
/* 800926A4 0008F284  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 800926A8 0008F288  EC 01 00 28 */	fsubs f0, f1, f0
/* 800926AC 0008F28C  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 800926B0 0008F290  C0 1F 23 50 */	lfs f0, 0x2350(r31)
/* 800926B4 0008F294  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800926B8 0008F298  40 80 00 08 */	bge lbl_800926C0
/* 800926BC 0008F29C  D0 5F 23 50 */	stfs f2, 0x2350(r31)
lbl_800926C0:
/* 800926C0 0008F2A0  38 60 00 00 */	li r3, 0
lbl_800926C4:
/* 800926C4 0008F2A4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800926C8 0008F2A8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800926CC 0008F2AC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800926D0 0008F2B0  38 21 00 20 */	addi r1, r1, 0x20
/* 800926D4 0008F2B4  7C 08 03 A6 */	mtlr r0
/* 800926D8 0008F2B8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool ftCo_800925A4(HSD_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x221B_b0) {
        fp->mv.co.guard.x2C = fp->lightshield_amount;
        {
            fp->lightshield_amount =
                (fp->input.x650 - p_ftCommonData->x10) /
                            (1 - p_ftCommonData->x10) <
                        0
                    ? fp->mv.co.guard.x2C
                    : (fp->input.x650 - p_ftCommonData->x10) /
                          (1 - p_ftCommonData->x10);
        }
        fp->shield_health -= p_ftCommonData->x278 *
                             ((fp->lightshield_amount *
                               (p_ftCommonData->x2F0 - p_ftCommonData->x2EC)) +
                              p_ftCommonData->x2EC);
        if (fp->shield_health < 0) {
            fp->shield_health = 0;
            fp->x221A_b7 = false;
            fp->x221B_b0 = false;
            pl_8003E0E8(fp->player_id, fp->x221F_b4);
            ftCo_80098B20(gobj);
            ft_80088148(fp, 129, 127, 64);
            return true;
        }
        if (fp->mv.co.guard.x10 > 0) {
            fp->mv.co.guard.x10 -= 1;
            if (fp->mv.co.guard.x10 < 0) {
                fp->mv.co.guard.x10 = 0;
            }
        }
    }
    return false;
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_GuardOn_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 800926DC 0008F2BC  7C 08 02 A6 */	mflr r0
/* 800926E0 0008F2C0  90 01 00 04 */	stw r0, 4(r1)
/* 800926E4 0008F2C4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800926E8 0008F2C8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800926EC 0008F2CC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800926F0 0008F2D0  7C 7E 1B 78 */	mr r30, r3
/* 800926F4 0008F2D4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800926F8 0008F2D8  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 800926FC 0008F2DC  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 80092700 0008F2E0  EC 01 00 2A */	fadds f0, f1, f0
/* 80092704 0008F2E4  D0 1F 23 40 */	stfs f0, 0x2340(r31)
/* 80092708 0008F2E8  4B FF FE 9D */	bl ftCo_800925A4
/* 8009270C 0008F2EC  2C 03 00 00 */	cmpwi r3, 0
/* 80092710 0008F2F0  40 82 00 30 */	bne lbl_80092740
/* 80092714 0008F2F4  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 80092718 0008F2F8  C0 1F 02 E8 */	lfs f0, 0x2e8(r31)
/* 8009271C 0008F2FC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80092720 0008F300  4C 41 13 82 */	cror 2, 1, 2
/* 80092724 0008F304  40 82 00 10 */	bne lbl_80092734
/* 80092728 0008F308  7F C3 F3 78 */	mr r3, r30
/* 8009272C 0008F30C  48 00 01 A1 */	bl ftCo_800928CC
/* 80092730 0008F310  48 00 00 10 */	b lbl_80092740
lbl_80092734:
/* 80092734 0008F314  7F C3 F3 78 */	mr r3, r30
/* 80092738 0008F318  EC 21 00 24 */	fdivs f1, f1, f0
/* 8009273C 0008F31C  4B FF F7 3D */	bl ftCo_80091E78
lbl_80092740:
/* 80092740 0008F320  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092744 0008F324  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092748 0008F328  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8009274C 0008F32C  38 21 00 18 */	addi r1, r1, 0x18
/* 80092750 0008F330  7C 08 03 A6 */	mtlr r0
/* 80092754 0008F334  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_GuardOn_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x0 += 1;
    if (ftCo_800925A4(gobj) == 0) {
        if (fp->mv.co.guard.x0 >= fp->x2E8) {
            ftCo_800928CC(gobj);
        } else {
            ftCo_80091E78(gobj, fp->mv.co.guard.x0 / fp->x2E8);
        }
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_GuardOn_IASA(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80092758 0008F338  7C 08 02 A6 */	mflr r0
/* 8009275C 0008F33C  90 01 00 04 */	stw r0, 4(r1)
/* 80092760 0008F340  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092764 0008F344  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092768 0008F348  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8009276C 0008F34C  7C 7E 1B 78 */	mr r30, r3
/* 80092770 0008F350  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092774 0008F354  48 00 04 59 */	bl ftCo_80092BCC
/* 80092778 0008F358  80 1F 23 4C */	lwz r0, 0x234c(r31)
/* 8009277C 0008F35C  2C 00 00 00 */	cmpwi r0, 0
/* 80092780 0008F360  41 82 00 14 */	beq lbl_80092794
/* 80092784 0008F364  C0 3F 23 50 */	lfs f1, 0x2350(r31)
/* 80092788 0008F368  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 8009278C 0008F36C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80092790 0008F370  41 82 00 1C */	beq lbl_800927AC
lbl_80092794:
/* 80092794 0008F374  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 80092798 0008F378  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8009279C 0008F37C  40 82 00 20 */	bne lbl_800927BC
/* 800927A0 0008F380  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 800927A4 0008F384  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800927A8 0008F388  40 82 00 14 */	bne lbl_800927BC
lbl_800927AC:
/* 800927AC 0008F38C  7F C3 F3 78 */	mr r3, r30
/* 800927B0 0008F390  48 00 04 39 */	bl ftCo_80092BE8
/* 800927B4 0008F394  38 00 00 01 */	li r0, 1
/* 800927B8 0008F398  48 00 00 1C */	b lbl_800927D4
lbl_800927BC:
/* 800927BC 0008F39C  80 7F 23 5C */	lwz r3, 0x235c(r31)
/* 800927C0 0008F3A0  2C 03 00 00 */	cmpwi r3, 0
/* 800927C4 0008F3A4  41 82 00 0C */	beq lbl_800927D0
/* 800927C8 0008F3A8  38 03 FF FF */	addi r0, r3, -1
/* 800927CC 0008F3AC  90 1F 23 5C */	stw r0, 0x235c(r31)
lbl_800927D0:
/* 800927D0 0008F3B0  38 00 00 00 */	li r0, 0
lbl_800927D4:
/* 800927D4 0008F3B4  2C 00 00 00 */	cmpwi r0, 0
/* 800927D8 0008F3B8  40 82 00 80 */	bne lbl_80092858
/* 800927DC 0008F3BC  7F C3 F3 78 */	mr r3, r30
/* 800927E0 0008F3C0  48 00 0E B5 */	bl ftCo_80093694
/* 800927E4 0008F3C4  2C 03 00 00 */	cmpwi r3, 0
/* 800927E8 0008F3C8  40 82 00 70 */	bne lbl_80092858
/* 800927EC 0008F3CC  7F C3 F3 78 */	mr r3, r30
/* 800927F0 0008F3D0  48 00 29 6D */	bl ftCo_8009515C
/* 800927F4 0008F3D4  2C 03 00 00 */	cmpwi r3, 0
/* 800927F8 0008F3D8  40 82 00 60 */	bne lbl_80092858
/* 800927FC 0008F3DC  7F C3 F3 78 */	mr r3, r30
/* 80092800 0008F3E0  48 00 70 0D */	bl ftCo_8009980C
/* 80092804 0008F3E4  2C 03 00 00 */	cmpwi r3, 0
/* 80092808 0008F3E8  40 82 00 50 */	bne lbl_80092858
/* 8009280C 0008F3EC  7F C3 F3 78 */	mr r3, r30
/* 80092810 0008F3F0  48 00 69 6D */	bl ftCo_8009917C
/* 80092814 0008F3F4  2C 03 00 00 */	cmpwi r3, 0
/* 80092818 0008F3F8  40 82 00 40 */	bne lbl_80092858
/* 8009281C 0008F3FC  7F C3 F3 78 */	mr r3, r30
/* 80092820 0008F400  48 04 63 7D */	bl ftCo_800D8B9C
/* 80092824 0008F404  2C 03 00 00 */	cmpwi r3, 0
/* 80092828 0008F408  40 82 00 30 */	bne lbl_80092858
/* 8009282C 0008F40C  7F C3 F3 78 */	mr r3, r30
/* 80092830 0008F410  48 04 61 61 */	bl ftCo_Catch_CheckInput
/* 80092834 0008F414  2C 03 00 00 */	cmpwi r3, 0
/* 80092838 0008F418  40 82 00 20 */	bne lbl_80092858
/* 8009283C 0008F41C  7F C3 F3 78 */	mr r3, r30
/* 80092840 0008F420  48 03 87 E5 */	bl ftCo_800CB024
/* 80092844 0008F424  2C 03 00 00 */	cmpwi r3, 0
/* 80092848 0008F428  40 82 00 10 */	bne lbl_80092858
/* 8009284C 0008F42C  7F C3 F3 78 */	mr r3, r30
/* 80092850 0008F430  48 00 78 31 */	bl ftCo_8009A080
/* 80092854 0008F434  2C 03 00 00 */	cmpwi r3, 0
lbl_80092858:
/* 80092858 0008F438  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009285C 0008F43C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092860 0008F440  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80092864 0008F444  38 21 00 18 */	addi r1, r1, 0x18
/* 80092868 0008F448  7C 08 03 A6 */	mtlr r0
/* 8009286C 0008F44C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline bool inlineC0(ftCo_GObj* gobj, HSD_GObjEvent cb)
{
    ftCo_Fighter* fp = gobj->user_data;
    if ((fp->mv.co.guard.xC && !fp->mv.co.guard.x10) ||
        (!fp->x221B_b0 && !fp->x2218_b3))
    {
        cb(gobj);
        return true;
    }
    if (fp->mv.co.guard.x1C != 0) {
        --fp->mv.co.guard.x1C;
    }
    return false;
}

void ftCo_GuardOn_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(inlineC0(gobj, ftCo_80092BE8));
    RETURN_IF(ftCo_80093694(gobj));
    RETURN_IF(ftCo_8009515C(gobj));
    RETURN_IF(ftCo_8009980C(gobj));
    RETURN_IF(ftCo_8009917C(gobj));
    RETURN_IF(ftCo_800D8B9C(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_800CB024(gobj));
    RETURN_IF(ftCo_8009A080(gobj));
}
#endif

void ftCo_GuardOn_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
    ftColl_8007AEF8(gobj);
}

void ftCo_GuardOn_Coll(ftCo_GObj* gobj)
{
    ft_800845B4(gobj);
}

void ftCo_800928CC(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C1D4(gobj);
        return;
    default:
        ftCo_80092908(gobj);
        return;
    }
}

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80092908(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80092908 0008F4E8  7C 08 02 A6 */	mflr r0
/* 8009290C 0008F4EC  38 80 00 B3 */	li r4, 0xb3
/* 80092910 0008F4F0  90 01 00 04 */	stw r0, 4(r1)
/* 80092914 0008F4F4  3C A0 20 00 */	lis r5, 0x2000
/* 80092918 0008F4F8  38 C0 00 00 */	li r6, 0
/* 8009291C 0008F4FC  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80092920 0008F500  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80092924 0008F504  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80092928 0008F508  7C 7E 1B 78 */	mr r30, r3
/* 8009292C 0008F50C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80092930 0008F510  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80092934 0008F514  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092938 0008F518  FC 60 08 90 */	fmr f3, f1
/* 8009293C 0008F51C  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80092940 0008F520  4B FD 6A 6D */	bl Fighter_ChangeMotionState
/* 80092944 0008F524  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80092948 0008F528  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8009294C 0008F52C  80 63 00 08 */	lwz r3, 8(r3)
/* 80092950 0008F530  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80092954 0008F534  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80092958 0008F538  88 65 00 0C */	lbz r3, 0xc(r5)
/* 8009295C 0008F53C  54 00 20 36 */	slwi r0, r0, 4
/* 80092960 0008F540  7F A4 00 2E */	lwzx r29, r4, r0
/* 80092964 0008F544  4B FA 3B D5 */	bl Player_GetUnk45
/* 80092968 0008F548  80 0D AE 6C */	lwz r0, Fighter_804D650C
/* 8009296C 0008F54C  54 63 10 3A */	slwi r3, r3, 2
/* 80092970 0008F550  38 9E 00 00 */	addi r4, r30, 0
/* 80092974 0008F554  4C C6 31 82 */	crclr 6
/* 80092978 0008F558  7C E0 1A 14 */	add r7, r0, r3
/* 8009297C 0008F55C  88 07 00 01 */	lbz r0, 1(r7)
/* 80092980 0008F560  7F A5 EB 78 */	mr r5, r29
/* 80092984 0008F564  88 C7 00 00 */	lbz r6, 0(r7)
/* 80092988 0008F568  38 60 04 18 */	li r3, 0x418
/* 8009298C 0008F56C  54 00 40 2E */	slwi r0, r0, 8
/* 80092990 0008F570  88 E7 00 02 */	lbz r7, 2(r7)
/* 80092994 0008F574  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80092998 0008F578  7C E6 03 78 */	or r6, r7, r0
/* 8009299C 0008F57C  4B FC D4 41 */	bl efSync_Spawn
/* 800929A0 0008F580  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800929A4 0008F584  3B A0 00 01 */	li r29, 1
/* 800929A8 0008F588  53 A0 3E 30 */	rlwimi r0, r29, 7, 0x18, 0x18
/* 800929AC 0008F58C  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800929B0 0008F590  3C 60 80 09 */	lis r3, ftCo_80092E50@ha
/* 800929B4 0008F594  38 A3 2E 50 */	addi r5, r3, ftCo_80092E50@l
/* 800929B8 0008F598  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800929BC 0008F59C  7F C3 F3 78 */	mr r3, r30
/* 800929C0 0008F5A0  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 800929C4 0008F5A4  38 81 00 18 */	addi r4, r1, 0x18
/* 800929C8 0008F5A8  80 DF 01 0C */	lwz r6, 0x10c(r31)
/* 800929CC 0008F5AC  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 800929D0 0008F5B0  80 C6 00 08 */	lwz r6, 8(r6)
/* 800929D4 0008F5B4  88 06 00 11 */	lbz r0, 0x11(r6)
/* 800929D8 0008F5B8  90 01 00 18 */	stw r0, 0x18(r1)
/* 800929DC 0008F5BC  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 800929E0 0008F5C0  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800929E4 0008F5C4  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800929E8 0008F5C8  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800929EC 0008F5CC  4B FE 87 CD */	bl ftColl_8007B1B8
/* 800929F0 0008F5D0  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800929F4 0008F5D4  53 A0 07 FE */	rlwimi r0, r29, 0, 0x1f, 0x1f
/* 800929F8 0008F5D8  38 7E 00 00 */	addi r3, r30, 0
/* 800929FC 0008F5DC  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 80092A00 0008F5E0  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 80092A04 0008F5E4  4B FF F4 75 */	bl ftCo_80091E78
/* 80092A08 0008F5E8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80092A0C 0008F5EC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80092A10 0008F5F0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80092A14 0008F5F4  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80092A18 0008F5F8  38 21 00 40 */	addi r1, r1, 0x40
/* 80092A1C 0008F5FC  7C 08 03 A6 */	mtlr r0
/* 80092A20 0008F600  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80092908(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_Guard, Ft_MF_SkipAnim, 0, 1, 0,
                              NULL);
    {
        HSD_JObj* jobj = fp->parts[fp->ft_data->x8->unk11].joint;
        ftCo_80092158(gobj, 1048, jobj);
        fp->x2219_b0 = true;
        ftCo_80092450(gobj);
        ftCo_80091E78(gobj, 1);
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_Guard_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80092A24 0008F604  7C 08 02 A6 */	mflr r0
/* 80092A28 0008F608  90 01 00 04 */	stw r0, 4(r1)
/* 80092A2C 0008F60C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80092A30 0008F610  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80092A34 0008F614  7C 7F 1B 78 */	mr r31, r3
/* 80092A38 0008F618  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80092A3C 0008F61C  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80092A40 0008F620  C0 24 23 40 */	lfs f1, 0x2340(r4)
/* 80092A44 0008F624  EC 01 00 2A */	fadds f0, f1, f0
/* 80092A48 0008F628  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 80092A4C 0008F62C  4B FF FB 59 */	bl ftCo_800925A4
/* 80092A50 0008F630  2C 03 00 00 */	cmpwi r3, 0
/* 80092A54 0008F634  40 82 00 10 */	bne lbl_80092A64
/* 80092A58 0008F638  7F E3 FB 78 */	mr r3, r31
/* 80092A5C 0008F63C  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 80092A60 0008F640  4B FF F4 19 */	bl ftCo_80091E78
lbl_80092A64:
/* 80092A64 0008F644  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80092A68 0008F648  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80092A6C 0008F64C  38 21 00 20 */	addi r1, r1, 0x20
/* 80092A70 0008F650  7C 08 03 A6 */	mtlr r0
/* 80092A74 0008F654  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_Guard_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x0 += 1;
    if (!ftCo_800925A4(gobj)) {
        ftCo_80091E78(gobj, 1);
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_Guard_IASA(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80092A78 0008F658  7C 08 02 A6 */	mflr r0
/* 80092A7C 0008F65C  90 01 00 04 */	stw r0, 4(r1)
/* 80092A80 0008F660  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092A84 0008F664  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092A88 0008F668  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80092A8C 0008F66C  7C 7E 1B 78 */	mr r30, r3
/* 80092A90 0008F670  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092A94 0008F674  48 00 01 39 */	bl ftCo_80092BCC
/* 80092A98 0008F678  80 1F 23 4C */	lwz r0, 0x234c(r31)
/* 80092A9C 0008F67C  2C 00 00 00 */	cmpwi r0, 0
/* 80092AA0 0008F680  41 82 00 14 */	beq lbl_80092AB4
/* 80092AA4 0008F684  C0 3F 23 50 */	lfs f1, 0x2350(r31)
/* 80092AA8 0008F688  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80092AAC 0008F68C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80092AB0 0008F690  41 82 00 1C */	beq lbl_80092ACC
lbl_80092AB4:
/* 80092AB4 0008F694  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 80092AB8 0008F698  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80092ABC 0008F69C  40 82 00 20 */	bne lbl_80092ADC
/* 80092AC0 0008F6A0  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 80092AC4 0008F6A4  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80092AC8 0008F6A8  40 82 00 14 */	bne lbl_80092ADC
lbl_80092ACC:
/* 80092ACC 0008F6AC  7F C3 F3 78 */	mr r3, r30
/* 80092AD0 0008F6B0  48 00 01 19 */	bl ftCo_80092BE8
/* 80092AD4 0008F6B4  38 00 00 01 */	li r0, 1
/* 80092AD8 0008F6B8  48 00 00 1C */	b lbl_80092AF4
lbl_80092ADC:
/* 80092ADC 0008F6BC  80 7F 23 5C */	lwz r3, 0x235c(r31)
/* 80092AE0 0008F6C0  2C 03 00 00 */	cmpwi r3, 0
/* 80092AE4 0008F6C4  41 82 00 0C */	beq lbl_80092AF0
/* 80092AE8 0008F6C8  38 03 FF FF */	addi r0, r3, -1
/* 80092AEC 0008F6CC  90 1F 23 5C */	stw r0, 0x235c(r31)
lbl_80092AF0:
/* 80092AF0 0008F6D0  38 00 00 00 */	li r0, 0
lbl_80092AF4:
/* 80092AF4 0008F6D4  2C 00 00 00 */	cmpwi r0, 0
/* 80092AF8 0008F6D8  40 82 00 60 */	bne lbl_80092B58
/* 80092AFC 0008F6DC  7F C3 F3 78 */	mr r3, r30
/* 80092B00 0008F6E0  48 00 26 5D */	bl ftCo_8009515C
/* 80092B04 0008F6E4  2C 03 00 00 */	cmpwi r3, 0
/* 80092B08 0008F6E8  40 82 00 50 */	bne lbl_80092B58
/* 80092B0C 0008F6EC  7F C3 F3 78 */	mr r3, r30
/* 80092B10 0008F6F0  48 00 6C FD */	bl ftCo_8009980C
/* 80092B14 0008F6F4  2C 03 00 00 */	cmpwi r3, 0
/* 80092B18 0008F6F8  40 82 00 40 */	bne lbl_80092B58
/* 80092B1C 0008F6FC  7F C3 F3 78 */	mr r3, r30
/* 80092B20 0008F700  48 00 66 5D */	bl ftCo_8009917C
/* 80092B24 0008F704  2C 03 00 00 */	cmpwi r3, 0
/* 80092B28 0008F708  40 82 00 30 */	bne lbl_80092B58
/* 80092B2C 0008F70C  7F C3 F3 78 */	mr r3, r30
/* 80092B30 0008F710  48 04 5E 61 */	bl ftCo_Catch_CheckInput
/* 80092B34 0008F714  2C 03 00 00 */	cmpwi r3, 0
/* 80092B38 0008F718  40 82 00 20 */	bne lbl_80092B58
/* 80092B3C 0008F71C  7F C3 F3 78 */	mr r3, r30
/* 80092B40 0008F720  48 03 84 E5 */	bl ftCo_800CB024
/* 80092B44 0008F724  2C 03 00 00 */	cmpwi r3, 0
/* 80092B48 0008F728  40 82 00 10 */	bne lbl_80092B58
/* 80092B4C 0008F72C  7F C3 F3 78 */	mr r3, r30
/* 80092B50 0008F730  48 00 75 31 */	bl ftCo_8009A080
/* 80092B54 0008F734  2C 03 00 00 */	cmpwi r3, 0
lbl_80092B58:
/* 80092B58 0008F738  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092B5C 0008F73C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092B60 0008F740  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80092B64 0008F744  38 21 00 18 */	addi r1, r1, 0x18
/* 80092B68 0008F748  7C 08 03 A6 */	mtlr r0
/* 80092B6C 0008F74C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_Guard_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(inlineC0(gobj, ftCo_80092BE8));
    RETURN_IF(ftCo_8009515C(gobj));
    RETURN_IF(ftCo_8009980C(gobj));
    RETURN_IF(ftCo_8009917C(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_800CB024(gobj));
    RETURN_IF(ftCo_8009A080(gobj));
}
#endif

void ftCo_Guard_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
    ftColl_8007AEF8(gobj);
}

void ftCo_Guard_Coll(ftCo_GObj* gobj)
{
    ft_800845B4(gobj);
}

void ftCo_80092BCC(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!(fp->input.held_inputs & HSD_PAD_LR)) {
        fp->mv.co.guard.xC = true;
    }
}

void ftCo_80092BE8(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    pl_8003E114(fp->player_id, fp->x221F_b4, fp->shield_health);
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C49C(gobj);
        return;
    default:
        ftCo_80092C54(gobj);
        return;
    }
}

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80092C54(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80092C54 0008F834  7C 08 02 A6 */	mflr r0
/* 80092C58 0008F838  38 80 00 B4 */	li r4, 0xb4
/* 80092C5C 0008F83C  90 01 00 04 */	stw r0, 4(r1)
/* 80092C60 0008F840  38 A0 00 00 */	li r5, 0
/* 80092C64 0008F844  38 C0 00 00 */	li r6, 0
/* 80092C68 0008F848  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092C6C 0008F84C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092C70 0008F850  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80092C74 0008F854  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092C78 0008F858  FC 60 08 90 */	fmr f3, f1
/* 80092C7C 0008F85C  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80092C80 0008F860  4B FD 67 2D */	bl Fighter_ChangeMotionState
/* 80092C84 0008F864  38 7F 00 00 */	addi r3, r31, 0
/* 80092C88 0008F868  38 80 00 7F */	li r4, 0x7f
/* 80092C8C 0008F86C  38 A0 00 7F */	li r5, 0x7f
/* 80092C90 0008F870  38 C0 00 40 */	li r6, 0x40
/* 80092C94 0008F874  4B FF 54 B5 */	bl ft_80088148
/* 80092C98 0008F878  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092C9C 0008F87C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092CA0 0008F880  38 21 00 18 */	addi r1, r1, 0x18
/* 80092CA4 0008F884  7C 08 03 A6 */	mtlr r0
/* 80092CA8 0008F888  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80092C54(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_GuardOff, Ft_MF_None, 0, 1, 0,
                              NULL);
    ft_80088148(fp, 127, 127, 64);
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_GuardOff_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80092CAC 0008F88C  7C 08 02 A6 */	mflr r0
/* 80092CB0 0008F890  90 01 00 04 */	stw r0, 4(r1)
/* 80092CB4 0008F894  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80092CB8 0008F898  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80092CBC 0008F89C  7C 7F 1B 78 */	mr r31, r3
/* 80092CC0 0008F8A0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80092CC4 0008F8A4  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80092CC8 0008F8A8  C0 24 23 40 */	lfs f1, 0x2340(r4)
/* 80092CCC 0008F8AC  EC 01 00 2A */	fadds f0, f1, f0
/* 80092CD0 0008F8B0  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 80092CD4 0008F8B4  4B FD C5 65 */	bl ftAnim_IsFramesRemaining
/* 80092CD8 0008F8B8  2C 03 00 00 */	cmpwi r3, 0
/* 80092CDC 0008F8BC  40 82 00 0C */	bne lbl_80092CE8
/* 80092CE0 0008F8C0  7F E3 FB 78 */	mr r3, r31
/* 80092CE4 0008F8C4  4B FF 75 D9 */	bl ft_8008A2BC
lbl_80092CE8:
/* 80092CE8 0008F8C8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80092CEC 0008F8CC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80092CF0 0008F8D0  38 21 00 20 */	addi r1, r1, 0x20
/* 80092CF4 0008F8D4  7C 08 03 A6 */	mtlr r0
/* 80092CF8 0008F8D8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_GuardOff_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->mv.co.guard.x0 += 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}
#endif

void ftCo_GuardOff_IASA(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    /// @todo #RETURN_IF chain
    if (!fp->mv.co.guard.x1C ||
        (!ftCo_SpecialS_CheckInput(gobj) && !ftCo_Attack100_CheckInput(gobj) &&
         !ftCo_800D6824(gobj) && !ftCo_800D68C0(gobj) &&
         !ftCo_Catch_CheckInput(gobj) && !ftCo_AttackS4_CheckInput(gobj) &&
         !ftCo_AttackHi4_CheckInput(gobj) &&
         !ftCo_AttackLw4_CheckInput(gobj) && !ftCo_AttackS3_CheckInput(gobj) &&
         !ftCo_AttackHi3_CheckInput(gobj) &&
         !ftCo_AttackLw3_CheckInput(gobj) && !ftCo_Attack1_CheckInput(gobj)))
    {
        RETURN_IF(ftCo_8009980C(gobj));
        RETURN_IF(!ftCo_800CB024(gobj));
    }
}

void ftCo_GuardOff_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_GuardOff_Coll(ftCo_GObj* gobj)
{
    ft_800845B4(gobj);
}

void ftCo_80092E50(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    bool b;
    if (fp->x19B0 == 10U) {
        b = true;
    } else {
        b = false;
    }
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C600(gobj, b);
        break;
    default:
        ftCo_80092F2C(gobj, b);
        break;
    }
    if (b) {
        ftCo_800C36DC(gobj);
    }
}

#ifdef MUST_MATCH
#pragma push
asm float ftCo_80092ED8(int arg0, float arg2)
{ // clang-format off
    nofralloc
/* 80092ED8 0008FAB8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092EDC 0008FABC  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 80092EE0 0008FAC0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80092EE4 0008FAC4  90 01 00 14 */	stw r0, 0x14(r1)
/* 80092EE8 0008FAC8  3C 00 43 30 */	lis r0, 0x4330
/* 80092EEC 0008FACC  C0 A4 02 E4 */	lfs f5, 0x2e4(r4)
/* 80092EF0 0008FAD0  C0 04 02 E8 */	lfs f0, 0x2e8(r4)
/* 80092EF4 0008FAD4  90 01 00 10 */	stw r0, 0x10(r1)
/* 80092EF8 0008FAD8  EC 00 28 28 */	fsubs f0, f0, f5
/* 80092EFC 0008FADC  C8 82 8B 90 */	lfd f4, ftCo_804D8570
/* 80092F00 0008FAE0  C8 61 00 10 */	lfd f3, 0x10(r1)
/* 80092F04 0008FAE4  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80092F08 0008FAE8  EC 21 28 3A */	fmadds f1, f1, f0, f5
/* 80092F0C 0008FAEC  EC 63 20 28 */	fsubs f3, f3, f4
/* 80092F10 0008FAF0  C0 84 02 8C */	lfs f4, 0x28c(r4)
/* 80092F14 0008FAF4  C0 04 02 90 */	lfs f0, 0x290(r4)
/* 80092F18 0008FAF8  EC 22 08 28 */	fsubs f1, f2, f1
/* 80092F1C 0008FAFC  EC 23 00 72 */	fmuls f1, f3, f1
/* 80092F20 0008FB00  EC 24 00 7A */	fmadds f1, f4, f1, f0
/* 80092F24 0008FB04  38 21 00 18 */	addi r1, r1, 0x18
/* 80092F28 0008FB08  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

float ftCo_80092ED8(int arg0, float arg1)
{
    return p_ftCommonData->x28C *
               (arg0 *
                (1 - (arg1 * (p_ftCommonData->x2E8 - p_ftCommonData->x2E4) +
                      p_ftCommonData->x2E4))) +
           p_ftCommonData->x290;
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80092F2C(ftCo_GObj* gobj, bool)
{ // clang-format off
    nofralloc
/* 80092F2C 0008FB0C  7C 08 02 A6 */	mflr r0
/* 80092F30 0008FB10  38 A0 00 00 */	li r5, 0
/* 80092F34 0008FB14  90 01 00 04 */	stw r0, 4(r1)
/* 80092F38 0008FB18  38 C0 00 00 */	li r6, 0
/* 80092F3C 0008FB1C  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 80092F40 0008FB20  DB E1 00 70 */	stfd f31, 0x70(r1)
/* 80092F44 0008FB24  93 E1 00 6C */	stw r31, 0x6c(r1)
/* 80092F48 0008FB28  93 C1 00 68 */	stw r30, 0x68(r1)
/* 80092F4C 0008FB2C  3B C4 00 00 */	addi r30, r4, 0
/* 80092F50 0008FB30  38 80 00 B5 */	li r4, 0xb5
/* 80092F54 0008FB34  93 A1 00 64 */	stw r29, 0x64(r1)
/* 80092F58 0008FB38  3B A3 00 00 */	addi r29, r3, 0
/* 80092F5C 0008FB3C  93 81 00 60 */	stw r28, 0x60(r1)
/* 80092F60 0008FB40  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80092F64 0008FB44  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092F68 0008FB48  FC 60 08 90 */	fmr f3, f1
/* 80092F6C 0008FB4C  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80092F70 0008FB50  4B FD 64 3D */	bl Fighter_ChangeMotionState
/* 80092F74 0008FB54  3C 60 80 09 */	lis r3, ftCo_80093240@ha
/* 80092F78 0008FB58  38 03 32 40 */	addi r0, r3, ftCo_80093240@l
/* 80092F7C 0008FB5C  90 1F 21 D0 */	stw r0, 0x21d0(r31)
/* 80092F80 0008FB60  38 00 00 FE */	li r0, 0xfe
/* 80092F84 0008FB64  3C 60 80 09 */	lis r3, ftCo_800932DC@ha
/* 80092F88 0008FB68  98 1F 06 70 */	stb r0, 0x670(r31)
/* 80092F8C 0008FB6C  38 03 32 DC */	addi r0, r3, ftCo_800932DC@l
/* 80092F90 0008FB70  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 80092F94 0008FB74  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80092F98 0008FB78  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80092F9C 0008FB7C  40 82 00 70 */	bne lbl_8009300C
/* 80092FA0 0008FB80  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80092FA4 0008FB84  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 80092FA8 0008FB88  80 63 00 08 */	lwz r3, 8(r3)
/* 80092FAC 0008FB8C  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80092FB0 0008FB90  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80092FB4 0008FB94  88 65 00 0C */	lbz r3, 0xc(r5)
/* 80092FB8 0008FB98  54 00 20 36 */	slwi r0, r0, 4
/* 80092FBC 0008FB9C  7F 84 00 2E */	lwzx r28, r4, r0
/* 80092FC0 0008FBA0  4B FA 35 79 */	bl Player_GetUnk45
/* 80092FC4 0008FBA4  80 0D AE 6C */	lwz r0, Fighter_804D650C
/* 80092FC8 0008FBA8  54 63 10 3A */	slwi r3, r3, 2
/* 80092FCC 0008FBAC  38 9D 00 00 */	addi r4, r29, 0
/* 80092FD0 0008FBB0  4C C6 31 82 */	crclr 6
/* 80092FD4 0008FBB4  7C E0 1A 14 */	add r7, r0, r3
/* 80092FD8 0008FBB8  88 07 00 01 */	lbz r0, 1(r7)
/* 80092FDC 0008FBBC  7F 85 E3 78 */	mr r5, r28
/* 80092FE0 0008FBC0  88 C7 00 00 */	lbz r6, 0(r7)
/* 80092FE4 0008FBC4  38 60 04 19 */	li r3, 0x419
/* 80092FE8 0008FBC8  54 00 40 2E */	slwi r0, r0, 8
/* 80092FEC 0008FBCC  88 E7 00 02 */	lbz r7, 2(r7)
/* 80092FF0 0008FBD0  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80092FF4 0008FBD4  7C E6 03 78 */	or r6, r7, r0
/* 80092FF8 0008FBD8  4B FC CD E5 */	bl efSync_Spawn
/* 80092FFC 0008FBDC  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 80093000 0008FBE0  38 60 00 01 */	li r3, 1
/* 80093004 0008FBE4  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80093008 0008FBE8  98 1F 22 19 */	stb r0, 0x2219(r31)
lbl_8009300C:
/* 8009300C 0008FBEC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80093010 0008FBF0  3C 00 43 30 */	lis r0, 0x4330
/* 80093014 0008FBF4  80 7F 19 A4 */	lwz r3, 0x19a4(r31)
/* 80093018 0008FBF8  C0 44 02 E4 */	lfs f2, 0x2e4(r4)
/* 8009301C 0008FBFC  C0 04 02 E8 */	lfs f0, 0x2e8(r4)
/* 80093020 0008FC00  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80093024 0008FC04  90 61 00 5C */	stw r3, 0x5c(r1)
/* 80093028 0008FC08  EC 00 10 28 */	fsubs f0, f0, f2
/* 8009302C 0008FC0C  C0 3F 19 9C */	lfs f1, 0x199c(r31)
/* 80093030 0008FC10  90 01 00 58 */	stw r0, 0x58(r1)
/* 80093034 0008FC14  C8 62 8B 90 */	lfd f3, ftCo_804D8570
/* 80093038 0008FC18  EC 01 10 3A */	fmadds f0, f1, f0, f2
/* 8009303C 0008FC1C  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 80093040 0008FC20  C8 41 00 58 */	lfd f2, 0x58(r1)
/* 80093044 0008FC24  EC 21 00 28 */	fsubs f1, f1, f0
/* 80093048 0008FC28  C0 84 02 8C */	lfs f4, 0x28c(r4)
/* 8009304C 0008FC2C  EC 42 18 28 */	fsubs f2, f2, f3
/* 80093050 0008FC30  C0 04 02 90 */	lfs f0, 0x290(r4)
/* 80093054 0008FC34  80 7D 00 28 */	lwz r3, 0x28(r29)
/* 80093058 0008FC38  EC 22 00 72 */	fmuls f1, f2, f1
/* 8009305C 0008FC3C  EF E4 00 7A */	fmadds f31, f4, f1, f0
/* 80093060 0008FC40  4B F7 8D E1 */	bl lb_8000BE40
/* 80093064 0008FC44  C0 02 8B 98 */	lfs f0, ftCo_804D8578
/* 80093068 0008FC48  7F A3 EB 78 */	mr r3, r29
/* 8009306C 0008FC4C  EC 00 08 2A */	fadds f0, f0, f1
/* 80093070 0008FC50  EC 20 F8 24 */	fdivs f1, f0, f31
/* 80093074 0008FC54  4B FD C1 1D */	bl ftAnim_SetAnimRate
/* 80093078 0008FC58  2C 1E 00 00 */	cmpwi r30, 0
/* 8009307C 0008FC5C  40 82 00 54 */	bne lbl_800930D0
/* 80093080 0008FC60  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80093084 0008FC64  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093088 0008FC68  C0 03 02 94 */	lfs f0, 0x294(r3)
/* 8009308C 0008FC6C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80093090 0008FC70  EC 5F 00 32 */	fmuls f2, f31, f0
/* 80093094 0008FC74  40 82 00 0C */	bne lbl_800930A0
/* 80093098 0008FC78  C0 03 02 BC */	lfs f0, 0x2bc(r3)
/* 8009309C 0008FC7C  EC 42 00 32 */	fmuls f2, f2, f0
lbl_800930A0:
/* 800930A0 0008FC80  C0 03 02 98 */	lfs f0, 0x298(r3)
/* 800930A4 0008FC84  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800930A8 0008FC88  40 81 00 08 */	ble lbl_800930B0
/* 800930AC 0008FC8C  FC 40 00 90 */	fmr f2, f0
lbl_800930B0:
/* 800930B0 0008FC90  C0 3F 19 AC */	lfs f1, 0x19ac(r31)
/* 800930B4 0008FC94  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 800930B8 0008FC98  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800930BC 0008FC9C  40 80 00 0C */	bge lbl_800930C8
/* 800930C0 0008FCA0  FC 00 10 90 */	fmr f0, f2
/* 800930C4 0008FCA4  48 00 00 08 */	b lbl_800930CC
lbl_800930C8:
/* 800930C8 0008FCA8  FC 00 10 50 */	fneg f0, f2
lbl_800930CC:
/* 800930CC 0008FCAC  D0 1F 00 EC */	stfs f0, 0xec(r31)
lbl_800930D0:
/* 800930D0 0008FCB0  83 9D 00 2C */	lwz r28, 0x2c(r29)
/* 800930D4 0008FCB4  3C 60 80 09 */	lis r3, ftCo_80092E50@ha
/* 800930D8 0008FCB8  38 A3 2E 50 */	addi r5, r3, ftCo_80092E50@l
/* 800930DC 0008FCBC  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 800930E0 0008FCC0  80 9C 01 0C */	lwz r4, 0x10c(r28)
/* 800930E4 0008FCC4  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 800930E8 0008FCC8  7F A3 EB 78 */	mr r3, r29
/* 800930EC 0008FCCC  80 C4 00 08 */	lwz r6, 8(r4)
/* 800930F0 0008FCD0  38 81 00 38 */	addi r4, r1, 0x38
/* 800930F4 0008FCD4  88 06 00 11 */	lbz r0, 0x11(r6)
/* 800930F8 0008FCD8  90 01 00 38 */	stw r0, 0x38(r1)
/* 800930FC 0008FCDC  D0 21 00 48 */	stfs f1, 0x48(r1)
/* 80093100 0008FCE0  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 80093104 0008FCE4  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 80093108 0008FCE8  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 8009310C 0008FCEC  4B FE 80 AD */	bl ftColl_8007B1B8
/* 80093110 0008FCF0  88 1C 22 1A */	lbz r0, 0x221a(r28)
/* 80093114 0008FCF4  38 60 00 01 */	li r3, 1
/* 80093118 0008FCF8  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8009311C 0008FCFC  98 1C 22 1A */	stb r0, 0x221a(r28)
/* 80093120 0008FD00  80 1F 00 04 */	lwz r0, 4(r31)
/* 80093124 0008FD04  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093128 0008FD08  40 82 00 0C */	bne lbl_80093134
/* 8009312C 0008FD0C  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80093130 0008FD10  48 00 00 44 */	b lbl_80093174
lbl_80093134:
/* 80093134 0008FD14  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80093138 0008FD18  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 8009313C 0008FD1C  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 80093140 0008FD20  C0 A3 02 D4 */	lfs f5, 0x2d4(r3)
/* 80093144 0008FD24  EC 61 00 24 */	fdivs f3, f1, f0
/* 80093148 0008FD28  C0 03 02 D8 */	lfs f0, 0x2d8(r3)
/* 8009314C 0008FD2C  C0 5F 19 9C */	lfs f2, 0x199c(r31)
/* 80093150 0008FD30  C0 C3 02 64 */	lfs f6, 0x264(r3)
/* 80093154 0008FD34  C0 82 8B 88 */	lfs f4, ftCo_804D8568
/* 80093158 0008FD38  EC 20 28 28 */	fsubs f1, f0, f5
/* 8009315C 0008FD3C  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80093160 0008FD40  EC 84 30 28 */	fsubs f4, f4, f6
/* 80093164 0008FD44  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80093168 0008FD48  EC 23 00 72 */	fmuls f1, f3, f1
/* 8009316C 0008FD4C  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 80093170 0008FD50  EC 01 00 32 */	fmuls f0, f1, f0
lbl_80093174:
/* 80093174 0008FD54  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 80093178 0008FD58  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 8009317C 0008FD5C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80093180 0008FD60  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80093184 0008FD64  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80093188 0008FD68  80 63 00 08 */	lwz r3, 8(r3)
/* 8009318C 0008FD6C  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80093190 0008FD70  54 00 20 36 */	slwi r0, r0, 4
/* 80093194 0008FD74  7F 84 00 2E */	lwzx r28, r4, r0
/* 80093198 0008FD78  28 1C 00 00 */	cmplwi r28, 0
/* 8009319C 0008FD7C  40 82 00 14 */	bne lbl_800931B0
/* 800931A0 0008FD80  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 800931A4 0008FD84  38 80 02 F8 */	li r4, 0x2f8
/* 800931A8 0008FD88  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 800931AC 0008FD8C  48 2F 50 75 */	bl __assert
lbl_800931B0:
/* 800931B0 0008FD90  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 800931B4 0008FD94  80 01 00 30 */	lwz r0, 0x30(r1)
/* 800931B8 0008FD98  90 7C 00 2C */	stw r3, 0x2c(r28)
/* 800931BC 0008FD9C  90 1C 00 30 */	stw r0, 0x30(r28)
/* 800931C0 0008FDA0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800931C4 0008FDA4  90 1C 00 34 */	stw r0, 0x34(r28)
/* 800931C8 0008FDA8  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 800931CC 0008FDAC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800931D0 0008FDB0  40 82 00 4C */	bne lbl_8009321C
/* 800931D4 0008FDB4  28 1C 00 00 */	cmplwi r28, 0
/* 800931D8 0008FDB8  41 82 00 44 */	beq lbl_8009321C
/* 800931DC 0008FDBC  40 82 00 14 */	bne lbl_800931F0
/* 800931E0 0008FDC0  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 800931E4 0008FDC4  38 80 02 34 */	li r4, 0x234
/* 800931E8 0008FDC8  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 800931EC 0008FDCC  48 2F 50 35 */	bl __assert
lbl_800931F0:
/* 800931F0 0008FDD0  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 800931F4 0008FDD4  38 60 00 00 */	li r3, 0
/* 800931F8 0008FDD8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800931FC 0008FDDC  40 82 00 10 */	bne lbl_8009320C
/* 80093200 0008FDE0  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80093204 0008FDE4  41 82 00 08 */	beq lbl_8009320C
/* 80093208 0008FDE8  38 60 00 01 */	li r3, 1
lbl_8009320C:
/* 8009320C 0008FDEC  2C 03 00 00 */	cmpwi r3, 0
/* 80093210 0008FDF0  40 82 00 0C */	bne lbl_8009321C
/* 80093214 0008FDF4  7F 83 E3 78 */	mr r3, r28
/* 80093218 0008FDF8  48 2E 00 D1 */	bl HSD_JObjSetMtxDirtySub
lbl_8009321C:
/* 8009321C 0008FDFC  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80093220 0008FE00  CB E1 00 70 */	lfd f31, 0x70(r1)
/* 80093224 0008FE04  83 E1 00 6C */	lwz r31, 0x6c(r1)
/* 80093228 0008FE08  83 C1 00 68 */	lwz r30, 0x68(r1)
/* 8009322C 0008FE0C  83 A1 00 64 */	lwz r29, 0x64(r1)
/* 80093230 0008FE10  83 81 00 60 */	lwz r28, 0x60(r1)
/* 80093234 0008FE14  38 21 00 78 */	addi r1, r1, 0x78
/* 80093238 0008FE18  7C 08 03 A6 */	mtlr r0
/* 8009323C 0008FE1C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80092F2C(HSD_GObj* gobj, bool arg1)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_GuardSetOff, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->hitlag_cb = ftCo_80093240;
    fp->x670_timer_lstick_tilt_x = -2;
    fp->post_hitlag_cb = ftCo_800932DC;
    if (!fp->x221C_b2) {
        ftCo_80092158(gobj, 1049, fp->parts[fp->ft_data->x8->unk11].joint);
        fp->x2219_b0 = true;
    }
    {
        float f = (p_ftCommonData->x28C *
                   (fp->x19A4 *
                    (1.0f - ((fp->lightshield_amount *
                              (p_ftCommonData->x2E8 - p_ftCommonData->x2E4)) +
                             p_ftCommonData->x2E4)))) +
                  p_ftCommonData->x290;
        ftAnim_SetAnimRate(gobj, (0.1f + lb_8000BE40(GET_JOBJ(gobj))) / f);
        if (!arg1) {
            float var_f2 = f * p_ftCommonData->x294;
            if (!fp->x221C_b2) {
                var_f2 *= p_ftCommonData->x2BC;
            }
            {
                /// @todo What happens to this value?
                float temp_f0 = p_ftCommonData->x298;
                if (var_f2 > temp_f0) {
                    var_f2 = temp_f0;
                }
            }
            fp->gr_vel = ABS(fp->specialn_facing_dir);
        }
    }
    ftCo_80092450(gobj);
    ftCo_80091D58(fp);
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80093240(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80093240 0008FE20  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80093244 0008FE24  88 04 22 1A */	lbz r0, 0x221a(r4)
/* 80093248 0008FE28  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8009324C 0008FE2C  4D 82 00 20 */	beqlr
/* 80093250 0008FE30  80 04 00 E0 */	lwz r0, 0xe0(r4)
/* 80093254 0008FE34  2C 00 00 00 */	cmpwi r0, 0
/* 80093258 0008FE38  4C 82 00 20 */	bnelr
/* 8009325C 0008FE3C  C0 44 06 20 */	lfs f2, 0x620(r4)
/* 80093260 0008FE40  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093264 0008FE44  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80093268 0008FE48  40 80 00 0C */	bge lbl_80093274
/* 8009326C 0008FE4C  FC 20 10 50 */	fneg f1, f2
/* 80093270 0008FE50  48 00 00 08 */	b lbl_80093278
lbl_80093274:
/* 80093274 0008FE54  FC 20 10 90 */	fmr f1, f2
lbl_80093278:
/* 80093278 0008FE58  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 8009327C 0008FE5C  C0 05 04 B0 */	lfs f0, 0x4b0(r5)
/* 80093280 0008FE60  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093284 0008FE64  4C 41 13 82 */	cror 2, 1, 2
/* 80093288 0008FE68  4C 82 00 20 */	bnelr
/* 8009328C 0008FE6C  88 64 06 70 */	lbz r3, 0x670(r4)
/* 80093290 0008FE70  80 05 04 B4 */	lwz r0, 0x4b4(r5)
/* 80093294 0008FE74  7C 03 00 00 */	cmpw r3, r0
/* 80093298 0008FE78  4C 80 00 20 */	bgelr
/* 8009329C 0008FE7C  C0 05 04 B8 */	lfs f0, 0x4b8(r5)
/* 800932A0 0008FE80  38 00 00 FE */	li r0, 0xfe
/* 800932A4 0008FE84  C0 65 04 C0 */	lfs f3, 0x4c0(r5)
/* 800932A8 0008FE88  EC 42 00 32 */	fmuls f2, f2, f0
/* 800932AC 0008FE8C  C0 24 08 48 */	lfs f1, 0x848(r4)
/* 800932B0 0008FE90  C0 04 00 B0 */	lfs f0, 0xb0(r4)
/* 800932B4 0008FE94  EC 43 00 B2 */	fmuls f2, f3, f2
/* 800932B8 0008FE98  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 800932BC 0008FE9C  D0 04 00 B0 */	stfs f0, 0xb0(r4)
/* 800932C0 0008FEA0  C0 24 08 44 */	lfs f1, 0x844(r4)
/* 800932C4 0008FEA4  C0 04 00 B4 */	lfs f0, 0xb4(r4)
/* 800932C8 0008FEA8  FC 20 08 50 */	fneg f1, f1
/* 800932CC 0008FEAC  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 800932D0 0008FEB0  D0 04 00 B4 */	stfs f0, 0xb4(r4)
/* 800932D4 0008FEB4  98 04 06 70 */	stb r0, 0x670(r4)
/* 800932D8 0008FEB8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80093240(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x221A_b2 && fp->ground_or_air == GA_Ground) {
        if ((fp->input.lstick.x < 0
                 ? -fp->input.lstick.x
                 : fp->input.lstick.x) >= p_ftCommonData->x4B0 &&
            fp->x670_timer_lstick_tilt_x < p_ftCommonData->x4B4)
        {
            float scl = p_ftCommonData->x4C0 *
                        (fp->input.lstick.x * p_ftCommonData->x4B8);
            fp->cur_pos.x += fp->coll_data.floor.normal.y * scl;
            fp->cur_pos.y += -fp->coll_data.floor.normal.x * scl;
            fp->x670_timer_lstick_tilt_x = 254;
        }
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_800932DC(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 800932DC 0008FEBC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800932E0 0008FEC0  80 04 00 E0 */	lwz r0, 0xe0(r4)
/* 800932E4 0008FEC4  2C 00 00 00 */	cmpwi r0, 0
/* 800932E8 0008FEC8  4C 82 00 20 */	bnelr
/* 800932EC 0008FECC  C0 44 06 20 */	lfs f2, 0x620(r4)
/* 800932F0 0008FED0  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 800932F4 0008FED4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800932F8 0008FED8  40 80 00 0C */	bge lbl_80093304
/* 800932FC 0008FEDC  FC 20 10 50 */	fneg f1, f2
/* 80093300 0008FEE0  48 00 00 08 */	b lbl_80093308
lbl_80093304:
/* 80093304 0008FEE4  FC 20 10 90 */	fmr f1, f2
lbl_80093308:
/* 80093308 0008FEE8  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 8009330C 0008FEEC  C0 05 04 B0 */	lfs f0, 0x4b0(r5)
/* 80093310 0008FEF0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093314 0008FEF4  4C 41 13 82 */	cror 2, 1, 2
/* 80093318 0008FEF8  4C 82 00 20 */	bnelr
/* 8009331C 0008FEFC  C0 05 04 BC */	lfs f0, 0x4bc(r5)
/* 80093320 0008FF00  C0 65 04 C0 */	lfs f3, 0x4c0(r5)
/* 80093324 0008FF04  EC 42 00 32 */	fmuls f2, f2, f0
/* 80093328 0008FF08  C0 24 08 48 */	lfs f1, 0x848(r4)
/* 8009332C 0008FF0C  C0 04 00 B0 */	lfs f0, 0xb0(r4)
/* 80093330 0008FF10  EC 43 00 B2 */	fmuls f2, f3, f2
/* 80093334 0008FF14  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 80093338 0008FF18  D0 04 00 B0 */	stfs f0, 0xb0(r4)
/* 8009333C 0008FF1C  C0 24 08 44 */	lfs f1, 0x844(r4)
/* 80093340 0008FF20  C0 04 00 B4 */	lfs f0, 0xb4(r4)
/* 80093344 0008FF24  FC 20 08 50 */	fneg f1, f1
/* 80093348 0008FF28  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 8009334C 0008FF2C  D0 04 00 B4 */	stfs f0, 0xb4(r4)
/* 80093350 0008FF30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_800932DC(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Ground) {
        if ((fp->input.lstick.x < 0
                 ? -fp->input.lstick.x
                 : fp->input.lstick.x) >= p_ftCommonData->x4B0)
        {
            float scl = p_ftCommonData->x4C0 *
                        (fp->input.lstick.x * p_ftCommonData->x4BC);
            fp->cur_pos.x += fp->coll_data.floor.normal.y * scl;
            fp->cur_pos.y += -fp->coll_data.floor.normal.x * scl;

            /// @todo Fake.
            !gobj;
        }
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_GuardSetOff_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80093354 0008FF34  7C 08 02 A6 */	mflr r0
/* 80093358 0008FF38  90 01 00 04 */	stw r0, 4(r1)
/* 8009335C 0008FF3C  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 80093360 0008FF40  93 E1 00 64 */	stw r31, 0x64(r1)
/* 80093364 0008FF44  93 C1 00 60 */	stw r30, 0x60(r1)
/* 80093368 0008FF48  7C 7E 1B 78 */	mr r30, r3
/* 8009336C 0008FF4C  93 A1 00 5C */	stw r29, 0x5c(r1)
/* 80093370 0008FF50  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80093374 0008FF54  48 00 08 4D */	bl ftCo_80093BC0
/* 80093378 0008FF58  7F C3 F3 78 */	mr r3, r30
/* 8009337C 0008FF5C  4B FD BE BD */	bl ftAnim_IsFramesRemaining
/* 80093380 0008FF60  2C 03 00 00 */	cmpwi r3, 0
/* 80093384 0008FF64  40 82 01 88 */	bne lbl_8009350C
/* 80093388 0008FF68  80 1D 23 4C */	lwz r0, 0x234c(r29)
/* 8009338C 0008FF6C  2C 00 00 00 */	cmpwi r0, 0
/* 80093390 0008FF70  41 82 00 74 */	beq lbl_80093404
/* 80093394 0008FF74  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80093398 0008FF78  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 8009339C 0008FF7C  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 800933A0 0008FF80  C0 3D 19 98 */	lfs f1, 0x1998(r29)
/* 800933A4 0008FF84  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800933A8 0008FF88  4B FA AD 6D */	bl pl_8003E114
/* 800933AC 0008FF8C  80 1D 00 04 */	lwz r0, 4(r29)
/* 800933B0 0008FF90  2C 00 00 0E */	cmpwi r0, 0xe
/* 800933B4 0008FF94  41 82 00 08 */	beq lbl_800933BC
/* 800933B8 0008FF98  48 00 00 10 */	b lbl_800933C8
lbl_800933BC:
/* 800933BC 0008FF9C  7F C3 F3 78 */	mr r3, r30
/* 800933C0 0008FFA0  48 09 90 DD */	bl ftYs_Shield_8012C49C
/* 800933C4 0008FFA4  48 00 02 44 */	b lbl_80093608
lbl_800933C8:
/* 800933C8 0008FFA8  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 800933CC 0008FFAC  7F C3 F3 78 */	mr r3, r30
/* 800933D0 0008FFB0  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 800933D4 0008FFB4  38 80 00 B4 */	li r4, 0xb4
/* 800933D8 0008FFB8  FC 60 08 90 */	fmr f3, f1
/* 800933DC 0008FFBC  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 800933E0 0008FFC0  38 A0 00 00 */	li r5, 0
/* 800933E4 0008FFC4  38 C0 00 00 */	li r6, 0
/* 800933E8 0008FFC8  4B FD 5F C5 */	bl Fighter_ChangeMotionState
/* 800933EC 0008FFCC  38 7D 00 00 */	addi r3, r29, 0
/* 800933F0 0008FFD0  38 80 00 7F */	li r4, 0x7f
/* 800933F4 0008FFD4  38 A0 00 7F */	li r5, 0x7f
/* 800933F8 0008FFD8  38 C0 00 40 */	li r6, 0x40
/* 800933FC 0008FFDC  4B FF 4D 4D */	bl ft_80088148
/* 80093400 0008FFE0  48 00 02 08 */	b lbl_80093608
lbl_80093404:
/* 80093404 0008FFE4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80093408 0008FFE8  80 1F 00 04 */	lwz r0, 4(r31)
/* 8009340C 0008FFEC  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093410 0008FFF0  41 82 00 08 */	beq lbl_80093418
/* 80093414 0008FFF4  48 00 00 10 */	b lbl_80093424
lbl_80093418:
/* 80093418 0008FFF8  7F C3 F3 78 */	mr r3, r30
/* 8009341C 0008FFFC  48 09 8D B9 */	bl ftYs_Shield_8012C1D4
/* 80093420 00090000  48 00 01 E8 */	b lbl_80093608
lbl_80093424:
/* 80093424 00090004  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80093428 00090008  7F C3 F3 78 */	mr r3, r30
/* 8009342C 0009000C  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80093430 00090010  38 80 00 B3 */	li r4, 0xb3
/* 80093434 00090014  FC 60 08 90 */	fmr f3, f1
/* 80093438 00090018  3C A0 20 00 */	lis r5, 0x2000
/* 8009343C 0009001C  38 C0 00 00 */	li r6, 0
/* 80093440 00090020  4B FD 5F 6D */	bl Fighter_ChangeMotionState
/* 80093444 00090024  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80093448 00090028  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8009344C 0009002C  80 63 00 08 */	lwz r3, 8(r3)
/* 80093450 00090030  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80093454 00090034  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80093458 00090038  88 65 00 0C */	lbz r3, 0xc(r5)
/* 8009345C 0009003C  54 00 20 36 */	slwi r0, r0, 4
/* 80093460 00090040  7F A4 00 2E */	lwzx r29, r4, r0
/* 80093464 00090044  4B FA 30 D5 */	bl Player_GetUnk45
/* 80093468 00090048  80 0D AE 6C */	lwz r0, Fighter_804D650C
/* 8009346C 0009004C  54 63 10 3A */	slwi r3, r3, 2
/* 80093470 00090050  38 9E 00 00 */	addi r4, r30, 0
/* 80093474 00090054  4C C6 31 82 */	crclr 6
/* 80093478 00090058  7C E0 1A 14 */	add r7, r0, r3
/* 8009347C 0009005C  88 07 00 01 */	lbz r0, 1(r7)
/* 80093480 00090060  7F A5 EB 78 */	mr r5, r29
/* 80093484 00090064  88 C7 00 00 */	lbz r6, 0(r7)
/* 80093488 00090068  38 60 04 18 */	li r3, 0x418
/* 8009348C 0009006C  54 00 40 2E */	slwi r0, r0, 8
/* 80093490 00090070  88 E7 00 02 */	lbz r7, 2(r7)
/* 80093494 00090074  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80093498 00090078  7C E6 03 78 */	or r6, r7, r0
/* 8009349C 0009007C  4B FC C9 41 */	bl efSync_Spawn
/* 800934A0 00090080  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800934A4 00090084  3B A0 00 01 */	li r29, 1
/* 800934A8 00090088  53 A0 3E 30 */	rlwimi r0, r29, 7, 0x18, 0x18
/* 800934AC 0009008C  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800934B0 00090090  3C 60 80 09 */	lis r3, ftCo_80092E50@ha
/* 800934B4 00090094  38 A3 2E 50 */	addi r5, r3, ftCo_80092E50@l
/* 800934B8 00090098  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800934BC 0009009C  7F C3 F3 78 */	mr r3, r30
/* 800934C0 000900A0  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 800934C4 000900A4  38 81 00 30 */	addi r4, r1, 0x30
/* 800934C8 000900A8  80 DF 01 0C */	lwz r6, 0x10c(r31)
/* 800934CC 000900AC  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 800934D0 000900B0  80 C6 00 08 */	lwz r6, 8(r6)
/* 800934D4 000900B4  88 06 00 11 */	lbz r0, 0x11(r6)
/* 800934D8 000900B8  90 01 00 30 */	stw r0, 0x30(r1)
/* 800934DC 000900BC  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 800934E0 000900C0  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 800934E4 000900C4  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800934E8 000900C8  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800934EC 000900CC  4B FE 7C CD */	bl ftColl_8007B1B8
/* 800934F0 000900D0  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800934F4 000900D4  53 A0 07 FE */	rlwimi r0, r29, 0, 0x1f, 0x1f
/* 800934F8 000900D8  38 7E 00 00 */	addi r3, r30, 0
/* 800934FC 000900DC  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 80093500 000900E0  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 80093504 000900E4  4B FF E9 75 */	bl ftCo_80091E78
/* 80093508 000900E8  48 00 01 00 */	b lbl_80093608
lbl_8009350C:
/* 8009350C 000900EC  80 1D 00 04 */	lwz r0, 4(r29)
/* 80093510 000900F0  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093514 000900F4  40 82 00 0C */	bne lbl_80093520
/* 80093518 000900F8  C0 1D 01 A0 */	lfs f0, 0x1a0(r29)
/* 8009351C 000900FC  48 00 00 44 */	b lbl_80093560
lbl_80093520:
/* 80093520 00090100  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80093524 00090104  C0 3D 19 98 */	lfs f1, 0x1998(r29)
/* 80093528 00090108  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 8009352C 0009010C  C0 A3 02 D4 */	lfs f5, 0x2d4(r3)
/* 80093530 00090110  EC 61 00 24 */	fdivs f3, f1, f0
/* 80093534 00090114  C0 03 02 D8 */	lfs f0, 0x2d8(r3)
/* 80093538 00090118  C0 5D 19 9C */	lfs f2, 0x199c(r29)
/* 8009353C 0009011C  C0 C3 02 64 */	lfs f6, 0x264(r3)
/* 80093540 00090120  C0 82 8B 88 */	lfs f4, ftCo_804D8568
/* 80093544 00090124  EC 20 28 28 */	fsubs f1, f0, f5
/* 80093548 00090128  C0 1D 01 A0 */	lfs f0, 0x1a0(r29)
/* 8009354C 0009012C  EC 84 30 28 */	fsubs f4, f4, f6
/* 80093550 00090130  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80093554 00090134  EC 23 00 72 */	fmuls f1, f3, f1
/* 80093558 00090138  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 8009355C 0009013C  EC 01 00 32 */	fmuls f0, f1, f0
lbl_80093560:
/* 80093560 00090140  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 80093564 00090144  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 80093568 00090148  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 8009356C 0009014C  80 7D 01 0C */	lwz r3, 0x10c(r29)
/* 80093570 00090150  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80093574 00090154  80 63 00 08 */	lwz r3, 8(r3)
/* 80093578 00090158  88 03 00 11 */	lbz r0, 0x11(r3)
/* 8009357C 0009015C  54 00 20 36 */	slwi r0, r0, 4
/* 80093580 00090160  7F A4 00 2E */	lwzx r29, r4, r0
/* 80093584 00090164  28 1D 00 00 */	cmplwi r29, 0
/* 80093588 00090168  40 82 00 14 */	bne lbl_8009359C
/* 8009358C 0009016C  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 80093590 00090170  38 80 02 F8 */	li r4, 0x2f8
/* 80093594 00090174  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 80093598 00090178  48 2F 4C 89 */	bl __assert
lbl_8009359C:
/* 8009359C 0009017C  80 61 00 48 */	lwz r3, 0x48(r1)
/* 800935A0 00090180  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800935A4 00090184  90 7D 00 2C */	stw r3, 0x2c(r29)
/* 800935A8 00090188  90 1D 00 30 */	stw r0, 0x30(r29)
/* 800935AC 0009018C  80 01 00 50 */	lwz r0, 0x50(r1)
/* 800935B0 00090190  90 1D 00 34 */	stw r0, 0x34(r29)
/* 800935B4 00090194  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 800935B8 00090198  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800935BC 0009019C  40 82 00 4C */	bne lbl_80093608
/* 800935C0 000901A0  28 1D 00 00 */	cmplwi r29, 0
/* 800935C4 000901A4  41 82 00 44 */	beq lbl_80093608
/* 800935C8 000901A8  40 82 00 14 */	bne lbl_800935DC
/* 800935CC 000901AC  38 6D 84 58 */	addi r3, r13, ftCo_804D3AF8
/* 800935D0 000901B0  38 80 02 34 */	li r4, 0x234
/* 800935D4 000901B4  38 AD 84 60 */	addi r5, r13, ftCo_804D3B00
/* 800935D8 000901B8  48 2F 4C 49 */	bl __assert
lbl_800935DC:
/* 800935DC 000901BC  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 800935E0 000901C0  38 60 00 00 */	li r3, 0
/* 800935E4 000901C4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800935E8 000901C8  40 82 00 10 */	bne lbl_800935F8
/* 800935EC 000901CC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800935F0 000901D0  41 82 00 08 */	beq lbl_800935F8
/* 800935F4 000901D4  38 60 00 01 */	li r3, 1
lbl_800935F8:
/* 800935F8 000901D8  2C 03 00 00 */	cmpwi r3, 0
/* 800935FC 000901DC  40 82 00 0C */	bne lbl_80093608
/* 80093600 000901E0  7F A3 EB 78 */	mr r3, r29
/* 80093604 000901E4  48 2D FC E5 */	bl HSD_JObjSetMtxDirtySub
lbl_80093608:
/* 80093608 000901E8  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8009360C 000901EC  83 E1 00 64 */	lwz r31, 0x64(r1)
/* 80093610 000901F0  83 C1 00 60 */	lwz r30, 0x60(r1)
/* 80093614 000901F4  83 A1 00 5C */	lwz r29, 0x5c(r1)
/* 80093618 000901F8  38 21 00 68 */	addi r1, r1, 0x68
/* 8009361C 000901FC  7C 08 03 A6 */	mtlr r0
/* 80093620 00090200  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_GuardSetOff_Anim(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_80093BC0(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.co.guard.xC) {
            ftCo_80092BE8(gobj);
        } else {
            ftCo_800928CC(gobj);
        }
    } else {
        ftCo_80091D58(fp);
    }
}
#endif

void ftCo_GuardSetOff_IASA(ftCo_GObj* gobj) {}

void ftCo_GuardSetOff_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
}

void ftCo_GuardSetOff_Coll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!(fp->x221A_b2)) {
        ft_800845B4(gobj);
    } else {
        ft_80084104(gobj);
    }
}

#ifdef MUST_MATCH
#pragma push
asm bool ftCo_80093694(ftCo_GObj* gobj)
{
    // clang-format off
    nofralloc
/* 80093694 00090274  7C 08 02 A6 */	mflr r0
/* 80093698 00090278  90 01 00 04 */	stw r0, 4(r1)
/* 8009369C 0009027C  3C 00 43 30 */	lis r0, 0x4330
/* 800936A0 00090280  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800936A4 00090284  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800936A8 00090288  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 800936AC 0009028C  80 C4 02 A0 */	lwz r6, 0x2a0(r4)
/* 800936B0 00090290  C8 22 8B 90 */	lfd f1, ftCo_804D8570
/* 800936B4 00090294  6C C4 80 00 */	xoris r4, r6, 0x8000
/* 800936B8 00090298  C0 45 23 40 */	lfs f2, 0x2340(r5)
/* 800936BC 0009029C  90 81 00 14 */	stw r4, 0x14(r1)
/* 800936C0 000902A0  90 01 00 10 */	stw r0, 0x10(r1)
/* 800936C4 000902A4  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800936C8 000902A8  EC 00 08 28 */	fsubs f0, f0, f1
/* 800936CC 000902AC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800936D0 000902B0  40 80 00 28 */	bge lbl_800936F8
/* 800936D4 000902B4  80 05 06 68 */	lwz r0, 0x668(r5)
/* 800936D8 000902B8  54 00 06 75 */	rlwinm. r0, r0, 0, 0x19, 0x1a
/* 800936DC 000902BC  41 82 00 1C */	beq lbl_800936F8
/* 800936E0 000902C0  88 05 06 72 */	lbz r0, 0x672(r5)
/* 800936E4 000902C4  7C 00 30 00 */	cmpw r0, r6
/* 800936E8 000902C8  40 80 00 10 */	bge lbl_800936F8
/* 800936EC 000902CC  48 00 01 65 */	bl ftCo_80093850
/* 800936F0 000902D0  38 60 00 01 */	li r3, 1
/* 800936F4 000902D4  48 00 00 08 */	b lbl_800936FC
lbl_800936F8:
/* 800936F8 000902D8  38 60 00 00 */	li r3, 0
lbl_800936FC:
/* 800936FC 000902DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80093700 000902E0  38 21 00 18 */	addi r1, r1, 0x18
/* 80093704 000902E4  7C 08 03 A6 */	mtlr r0
/* 80093708 000902E8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool ftCo_80093694(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.guard.x0 < p_ftCommonData->x2A0 &&
        fp->input.x668 & (HSD_PAD_R | HSD_PAD_L) &&
        fp->x672_input_timer_counter < p_ftCommonData->x2A0)
    {
        ftCo_80093850(gobj);
        return true;
    }
    return false;
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_8009370C(ftCo_GObj*, HSD_GObjEvent)
{ // clang-format off
    nofralloc
/* 8009370C 000902EC  7C 08 02 A6 */	mflr r0
/* 80093710 000902F0  90 01 00 04 */	stw r0, 4(r1)
/* 80093714 000902F4  38 00 00 01 */	li r0, 1
/* 80093718 000902F8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8009371C 000902FC  81 03 00 2C */	lwz r8, 0x2c(r3)
/* 80093720 00090300  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093724 00090304  80 A8 01 0C */	lwz r5, 0x10c(r8)
/* 80093728 00090308  80 ED AE B4 */	lwz r7, p_ftCommonData
/* 8009372C 0009030C  80 C5 00 08 */	lwz r6, 8(r5)
/* 80093730 00090310  38 A4 00 00 */	addi r5, r4, 0
/* 80093734 00090314  38 81 00 14 */	addi r4, r1, 0x14
/* 80093738 00090318  88 C6 00 11 */	lbz r6, 0x11(r6)
/* 8009373C 0009031C  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80093740 00090320  C0 28 19 98 */	lfs f1, 0x1998(r8)
/* 80093744 00090324  FC 20 08 1E */	fctiwz f1, f1
/* 80093748 00090328  D8 21 00 38 */	stfd f1, 0x38(r1)
/* 8009374C 0009032C  80 C1 00 3C */	lwz r6, 0x3c(r1)
/* 80093750 00090330  90 C1 00 18 */	stw r6, 0x18(r1)
/* 80093754 00090334  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80093758 00090338  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8009375C 0009033C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80093760 00090340  C0 07 02 A8 */	lfs f0, 0x2a8(r7)
/* 80093764 00090344  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80093768 00090348  C0 07 02 AC */	lfs f0, 0x2ac(r7)
/* 8009376C 0009034C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80093770 00090350  C0 07 02 B0 */	lfs f0, 0x2b0(r7)
/* 80093774 00090354  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80093778 00090358  98 01 00 34 */	stb r0, 0x34(r1)
/* 8009377C 0009035C  4B FE 7A C1 */	bl ftColl_CreateReflectHit
/* 80093780 00090360  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80093784 00090364  38 21 00 40 */	addi r1, r1, 0x40
/* 80093788 00090368  7C 08 03 A6 */	mtlr r0
/* 8009378C 0009036C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_8009370C(ftCo_GObj* gobj, HSD_GObjEvent on_reflect)
{
    u8 _[8] = { 0 };
    ReflectDesc reflect;
    ftCo_Fighter* fp = gobj->user_data;
    reflect.x0_bone_id = fp->ft_data->x8->unk11;
    reflect.x4_max_damage = fp->shield_health;
    reflect.x8_offset.x = reflect.x8_offset.y = reflect.x8_offset.z = 0;
    reflect.x14_size = p_ftCommonData->x2A8;
    reflect.x18_damage_mul = p_ftCommonData->x2AC;
    reflect.x1C_speed_mul = p_ftCommonData->x2B0;
    reflect.x20_behavior = 1;
    ftColl_CreateReflectHit(gobj, &reflect, on_reflect);
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80093790(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80093790 00090370  7C 08 02 A6 */	mflr r0
/* 80093794 00090374  90 01 00 04 */	stw r0, 0x4(r1)
/* 80093798 00090378  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8009379C 0009037C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800937A0 00090380  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800937A4 00090384  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800937A8 00090388  7C 7D 1B 78 */	mr r29, r3
/* 800937AC 0009038C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800937B0 00090390  4B FE A3 75 */	bl ftCommon_8007DB24
/* 800937B4 00090394  80 7E 01 0C */	lwz r3, 0x10c(r30)
/* 800937B8 00090398  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 800937BC 0009039C  80 63 00 08 */	lwz r3, 0x8(r3)
/* 800937C0 000903A0  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 800937C4 000903A4  88 03 00 11 */	lbz r0, 0x11(r3)
/* 800937C8 000903A8  88 65 00 0C */	lbz r3, 0xc(r5)
/* 800937CC 000903AC  54 00 20 36 */	slwi r0, r0, 4
/* 800937D0 000903B0  7F E4 00 2E */	lwzx r31, r4, r0
/* 800937D4 000903B4  4B FA 2D 65 */	bl Player_GetUnk45
/* 800937D8 000903B8  80 0D AE 6C */	lwz r0, Fighter_804D650C
/* 800937DC 000903BC  54 63 10 3A */	slwi r3, r3, 2
/* 800937E0 000903C0  38 9D 00 00 */	addi r4, r29, 0x0
/* 800937E4 000903C4  4C C6 31 82 */	crclr 4*cr1+eq
/* 800937E8 000903C8  7C E0 1A 14 */	add r7, r0, r3
/* 800937EC 000903CC  88 07 00 01 */	lbz r0, 0x1(r7)
/* 800937F0 000903D0  7F E5 FB 78 */	mr r5, r31
/* 800937F4 000903D4  88 C7 00 00 */	lbz r6, 0x0(r7)
/* 800937F8 000903D8  38 60 04 1A */	li r3, 0x41a
/* 800937FC 000903DC  54 00 40 2E */	slwi r0, r0, 8
/* 80093800 000903E0  88 E7 00 02 */	lbz r7, 0x2(r7)
/* 80093804 000903E4  50 C0 82 1E */	rlwimi r0, r6, 16, 8, 15
/* 80093808 000903E8  7C E6 03 78 */	or r6, r7, r0
/* 8009380C 000903EC  4B FC C5 D1 */	bl efSync_Spawn
/* 80093810 000903F0  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 80093814 000903F4  38 60 00 01 */	li r3, 0x1
/* 80093818 000903F8  50 60 3E 30 */	rlwimi r0, r3, 7, 24, 24
/* 8009381C 000903FC  98 1E 22 19 */	stb r0, 0x2219(r30)
/* 80093820 00090400  38 7E 00 00 */	addi r3, r30, 0x0
/* 80093824 00090404  38 80 00 80 */	li r4, 0x80
/* 80093828 00090408  38 A0 00 7F */	li r5, 0x7f
/* 8009382C 0009040C  38 C0 00 40 */	li r6, 0x40
/* 80093830 00090410  4B FF 49 19 */	bl ft_80088148
/* 80093834 00090414  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80093838 00090418  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8009383C 0009041C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80093840 00090420  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80093844 00090424  38 21 00 28 */	addi r1, r1, 0x28
/* 80093848 00090428  7C 08 03 A6 */	mtlr r0
/* 8009384C 0009042C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80093790(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007DB24(gobj);
    {
        HSD_JObj* jobj = fp->parts[fp->ft_data->x8->unk11].joint;
        ftCo_80092158(gobj, 1050, jobj);
        fp->x2219_b0 = true;
        ft_80088148(fp, 128, 127, 64);
    }
}
#endif

void ftCo_80093850(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C850(gobj);
        return;
    default:
        ftCo_8009388C(gobj);
        return;
    }
}

#ifdef MUST_MATCH
#pragma push
asm void ftCo_8009388C(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 8009388C 0009046C  7C 08 02 A6 */	mflr r0
/* 80093890 00090470  3C 80 20 00 */	lis r4, 0x20000002@ha
/* 80093894 00090474  90 01 00 04 */	stw r0, 4(r1)
/* 80093898 00090478  38 A4 00 02 */	addi r5, r4, 0x20000002@l
/* 8009389C 0009047C  38 80 00 B6 */	li r4, 0xb6
/* 800938A0 00090480  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 800938A4 00090484  38 C0 00 00 */	li r6, 0
/* 800938A8 00090488  93 E1 00 44 */	stw r31, 0x44(r1)
/* 800938AC 0009048C  93 C1 00 40 */	stw r30, 0x40(r1)
/* 800938B0 00090490  7C 7E 1B 78 */	mr r30, r3
/* 800938B4 00090494  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800938B8 00090498  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 800938BC 0009049C  C0 62 8B 58 */	lfs f3, ftCo_804D8538
/* 800938C0 000904A0  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800938C4 000904A4  4B FD 5A E9 */	bl Fighter_ChangeMotionState
/* 800938C8 000904A8  38 00 00 FE */	li r0, 0xfe
/* 800938CC 000904AC  98 1F 06 72 */	stb r0, 0x672(r31)
/* 800938D0 000904B0  3C 60 80 09 */	lis r3, ftCo_80093790@ha
/* 800938D4 000904B4  38 A3 37 90 */	addi r5, r3, ftCo_80093790@l
/* 800938D8 000904B8  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800938DC 000904BC  38 C0 00 00 */	li r6, 0
/* 800938E0 000904C0  50 C0 07 FE */	rlwimi r0, r6, 0, 0x1f, 0x1f
/* 800938E4 000904C4  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 800938E8 000904C8  38 E0 00 01 */	li r7, 1
/* 800938EC 000904CC  38 7E 00 00 */	addi r3, r30, 0
/* 800938F0 000904D0  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 800938F4 000904D4  50 C0 3E 30 */	rlwimi r0, r6, 7, 0x18, 0x18
/* 800938F8 000904D8  38 81 00 14 */	addi r4, r1, 0x14
/* 800938FC 000904DC  98 1F 22 1B */	stb r0, 0x221b(r31)
/* 80093900 000904E0  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093904 000904E4  50 E0 26 F6 */	rlwimi r0, r7, 4, 0x1b, 0x1b
/* 80093908 000904E8  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 8009390C 000904EC  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093910 000904F0  50 E0 36 72 */	rlwimi r0, r7, 6, 0x19, 0x19
/* 80093914 000904F4  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80093918 000904F8  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8009391C 000904FC  50 E0 2E B4 */	rlwimi r0, r7, 5, 0x1a, 0x1a
/* 80093920 00090500  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80093924 00090504  90 DF 23 5C */	stw r6, 0x235c(r31)
/* 80093928 00090508  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 8009392C 0009050C  C0 06 02 A4 */	lfs f0, 0x2a4(r6)
/* 80093930 00090510  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 80093934 00090514  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 80093938 00090518  C0 06 02 B4 */	lfs f0, 0x2b4(r6)
/* 8009393C 0009051C  D0 1F 23 58 */	stfs f0, 0x2358(r31)
/* 80093940 00090520  81 1E 00 2C */	lwz r8, 0x2c(r30)
/* 80093944 00090524  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093948 00090528  80 C8 01 0C */	lwz r6, 0x10c(r8)
/* 8009394C 0009052C  81 2D AE B4 */	lwz r9, p_ftCommonData
/* 80093950 00090530  80 C6 00 08 */	lwz r6, 8(r6)
/* 80093954 00090534  88 06 00 11 */	lbz r0, 0x11(r6)
/* 80093958 00090538  90 01 00 14 */	stw r0, 0x14(r1)
/* 8009395C 0009053C  C0 28 19 98 */	lfs f1, 0x1998(r8)
/* 80093960 00090540  FC 20 08 1E */	fctiwz f1, f1
/* 80093964 00090544  D8 21 00 38 */	stfd f1, 0x38(r1)
/* 80093968 00090548  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8009396C 0009054C  90 01 00 18 */	stw r0, 0x18(r1)
/* 80093970 00090550  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80093974 00090554  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80093978 00090558  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8009397C 0009055C  C0 09 02 A8 */	lfs f0, 0x2a8(r9)
/* 80093980 00090560  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80093984 00090564  C0 09 02 AC */	lfs f0, 0x2ac(r9)
/* 80093988 00090568  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 8009398C 0009056C  C0 09 02 B0 */	lfs f0, 0x2b0(r9)
/* 80093990 00090570  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80093994 00090574  98 E1 00 34 */	stb r7, 0x34(r1)
/* 80093998 00090578  4B FE 78 A5 */	bl ftColl_CreateReflectHit
/* 8009399C 0009057C  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800939A0 00090580  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 800939A4 00090584  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 800939A8 00090588  38 21 00 48 */	addi r1, r1, 0x48
/* 800939AC 0009058C  7C 08 03 A6 */	mtlr r0
/* 800939B0 00090590  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_8009388C(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, ftCo_MS_GuardReflect,
                              Ft_MF_SkipAnim | Ft_MF_KeepGfx,
                              fp->cur_anim_frame, 1, 0, NULL);
    fp->x672_input_timer_counter = 0xFE;
    fp->x221A_b7 = false;
    fp->x221B_b0 = false;
    fp->x221C_b3 = true;
    fp->x221C_b1 = true;
    fp->x221C_b2 = true;
    fp->mv.co.guard.x1C = 0;
    fp->mv.co.guard.x14 = p_ftCommonData->x2A4;
    fp->mv.co.guard.x18 = p_ftCommonData->x2B4;
    ftCo_8009370C(gobj, ftCo_80093790);
}
#endif

/// @todo Shares a lot of code with #ftCo_800923B4
void ftCo_800939B4(ftCo_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    switch (fp->kind) {
    case FTKIND_YOSHI:
        ftYs_Shield_8012C914(gobj);
        return;
    case FTKIND_MARS:
        ftCo_80093A50(gobj);
        ftParts_80074B0C(gobj, 1, 1);
        ft_80088148(fp, 190115, 127, 64);
        return;
    default:
        ftCo_80093A50(gobj);
        return;
    }
    ftCo_800923B4(gobj);
}

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80093A50(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80093A50 00090630  7C 08 02 A6 */	mflr r0
/* 80093A54 00090634  38 80 00 B6 */	li r4, 0xb6
/* 80093A58 00090638  90 01 00 04 */	stw r0, 4(r1)
/* 80093A5C 0009063C  3C A0 20 00 */	lis r5, 0x2000
/* 80093A60 00090640  38 C0 00 00 */	li r6, 0
/* 80093A64 00090644  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 80093A68 00090648  93 E1 00 64 */	stw r31, 0x64(r1)
/* 80093A6C 0009064C  93 C1 00 60 */	stw r30, 0x60(r1)
/* 80093A70 00090650  7C 7E 1B 78 */	mr r30, r3
/* 80093A74 00090654  93 A1 00 5C */	stw r29, 0x5c(r1)
/* 80093A78 00090658  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80093A7C 0009065C  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80093A80 00090660  FC 60 08 90 */	fmr f3, f1
/* 80093A84 00090664  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80093A88 00090668  4B FD 59 25 */	bl Fighter_ChangeMotionState
/* 80093A8C 0009066C  7F C3 F3 78 */	mr r3, r30
/* 80093A90 00090670  4B FD B1 15 */	bl ftAnim_8006EBA4
/* 80093A94 00090674  38 00 00 FE */	li r0, 0xfe
/* 80093A98 00090678  98 1D 06 72 */	stb r0, 0x672(r29)
/* 80093A9C 0009067C  3C 60 80 09 */	lis r3, ftCo_80092E50@ha
/* 80093AA0 00090680  38 A3 2E 50 */	addi r5, r3, ftCo_80092E50@l
/* 80093AA4 00090684  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 80093AA8 00090688  3B E0 00 01 */	li r31, 1
/* 80093AAC 0009068C  53 E0 26 F6 */	rlwimi r0, r31, 4, 0x1b, 0x1b
/* 80093AB0 00090690  98 1D 22 1C */	stb r0, 0x221c(r29)
/* 80093AB4 00090694  38 00 00 00 */	li r0, 0
/* 80093AB8 00090698  38 7E 00 00 */	addi r3, r30, 0
/* 80093ABC 0009069C  88 9D 22 1C */	lbz r4, 0x221c(r29)
/* 80093AC0 000906A0  53 E4 36 72 */	rlwimi r4, r31, 6, 0x19, 0x19
/* 80093AC4 000906A4  98 9D 22 1C */	stb r4, 0x221c(r29)
/* 80093AC8 000906A8  38 81 00 3C */	addi r4, r1, 0x3c
/* 80093ACC 000906AC  88 DD 22 1C */	lbz r6, 0x221c(r29)
/* 80093AD0 000906B0  53 E6 2E B4 */	rlwimi r6, r31, 5, 0x1a, 0x1a
/* 80093AD4 000906B4  98 DD 22 1C */	stb r6, 0x221c(r29)
/* 80093AD8 000906B8  90 1D 23 5C */	stw r0, 0x235c(r29)
/* 80093ADC 000906BC  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 80093AE0 000906C0  C0 06 02 A4 */	lfs f0, 0x2a4(r6)
/* 80093AE4 000906C4  D0 1D 23 54 */	stfs f0, 0x2354(r29)
/* 80093AE8 000906C8  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 80093AEC 000906CC  C0 06 02 B4 */	lfs f0, 0x2b4(r6)
/* 80093AF0 000906D0  D0 1D 23 58 */	stfs f0, 0x2358(r29)
/* 80093AF4 000906D4  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80093AF8 000906D8  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 80093AFC 000906DC  80 DD 01 0C */	lwz r6, 0x10c(r29)
/* 80093B00 000906E0  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093B04 000906E4  80 C6 00 08 */	lwz r6, 8(r6)
/* 80093B08 000906E8  88 06 00 11 */	lbz r0, 0x11(r6)
/* 80093B0C 000906EC  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80093B10 000906F0  D0 21 00 4C */	stfs f1, 0x4c(r1)
/* 80093B14 000906F4  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 80093B18 000906F8  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 80093B1C 000906FC  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 80093B20 00090700  4B FE 76 99 */	bl ftColl_8007B1B8
/* 80093B24 00090704  88 1D 22 1A */	lbz r0, 0x221a(r29)
/* 80093B28 00090708  53 E0 07 FE */	rlwimi r0, r31, 0, 0x1f, 0x1f
/* 80093B2C 0009070C  3C 60 80 09 */	lis r3, ftCo_80093790@ha
/* 80093B30 00090710  98 1D 22 1A */	stb r0, 0x221a(r29)
/* 80093B34 00090714  38 A3 37 90 */	addi r5, r3, ftCo_80093790@l
/* 80093B38 00090718  38 7E 00 00 */	addi r3, r30, 0
/* 80093B3C 0009071C  80 FE 00 2C */	lwz r7, 0x2c(r30)
/* 80093B40 00090720  38 81 00 18 */	addi r4, r1, 0x18
/* 80093B44 00090724  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093B48 00090728  80 C7 01 0C */	lwz r6, 0x10c(r7)
/* 80093B4C 0009072C  81 0D AE B4 */	lwz r8, p_ftCommonData
/* 80093B50 00090730  80 C6 00 08 */	lwz r6, 8(r6)
/* 80093B54 00090734  88 06 00 11 */	lbz r0, 0x11(r6)
/* 80093B58 00090738  90 01 00 18 */	stw r0, 0x18(r1)
/* 80093B5C 0009073C  C0 27 19 98 */	lfs f1, 0x1998(r7)
/* 80093B60 00090740  FC 20 08 1E */	fctiwz f1, f1
/* 80093B64 00090744  D8 21 00 50 */	stfd f1, 0x50(r1)
/* 80093B68 00090748  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80093B6C 0009074C  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80093B70 00090750  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80093B74 00090754  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80093B78 00090758  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80093B7C 0009075C  C0 08 02 A8 */	lfs f0, 0x2a8(r8)
/* 80093B80 00090760  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80093B84 00090764  C0 08 02 AC */	lfs f0, 0x2ac(r8)
/* 80093B88 00090768  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80093B8C 0009076C  C0 08 02 B0 */	lfs f0, 0x2b0(r8)
/* 80093B90 00090770  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 80093B94 00090774  9B E1 00 38 */	stb r31, 0x38(r1)
/* 80093B98 00090778  4B FE 76 A5 */	bl ftColl_CreateReflectHit
/* 80093B9C 0009077C  7F C3 F3 78 */	mr r3, r30
/* 80093BA0 00090780  4B FF E6 3D */	bl ftCo_800921DC
/* 80093BA4 00090784  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 80093BA8 00090788  83 E1 00 64 */	lwz r31, 0x64(r1)
/* 80093BAC 0009078C  83 C1 00 60 */	lwz r30, 0x60(r1)
/* 80093BB0 00090790  83 A1 00 5C */	lwz r29, 0x5c(r1)
/* 80093BB4 00090794  38 21 00 68 */	addi r1, r1, 0x68
/* 80093BB8 00090798  7C 08 03 A6 */	mtlr r0
/* 80093BBC 0009079C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo Shared code with #ftCo_8009388C.
void ftCo_80093A50(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, 182, Ft_MF_SkipAnim, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    fp->x672_input_timer_counter = 0xFE;
    fp->x221C_b3 = true;
    fp->x221C_b1 = true;
    fp->x221C_b2 = true;
    fp->mv.co.guard.x1C = 0;
    fp->mv.co.guard.x14 = p_ftCommonData->x2A4;
    fp->mv.co.guard.x18 = p_ftCommonData->x2B4;
    ftCo_80092450(gobj);
    ftCo_8009370C(gobj, ftCo_80093790);
    ftCo_800921DC(gobj);
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_80093BC0(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80093BC0 000907A0  7C 08 02 A6 */	mflr r0
/* 80093BC4 000907A4  90 01 00 04 */	stw r0, 4(r1)
/* 80093BC8 000907A8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80093BCC 000907AC  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80093BD0 000907B0  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80093BD4 000907B4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80093BD8 000907B8  88 9F 22 1C */	lbz r4, 0x221c(r31)
/* 80093BDC 000907BC  54 80 E7 FF */	rlwinm. r0, r4, 0x1c, 0x1f, 0x1f
/* 80093BE0 000907C0  41 82 00 10 */	beq lbl_80093BF0
/* 80093BE4 000907C4  38 00 00 00 */	li r0, 0
/* 80093BE8 000907C8  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 80093BEC 000907CC  98 9F 22 1C */	stb r4, 0x221c(r31)
lbl_80093BF0:
/* 80093BF0 000907D0  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093BF4 000907D4  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80093BF8 000907D8  41 82 00 84 */	beq lbl_80093C7C
/* 80093BFC 000907DC  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 80093C00 000907E0  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80093C04 000907E4  EC 00 10 28 */	fsubs f0, f0, f2
/* 80093C08 000907E8  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 80093C0C 000907EC  C0 3F 23 54 */	lfs f1, 0x2354(r31)
/* 80093C10 000907F0  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093C14 000907F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093C18 000907F8  40 80 00 64 */	bge lbl_80093C7C
/* 80093C1C 000907FC  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093C20 00090800  38 C0 00 00 */	li r6, 0
/* 80093C24 00090804  50 C0 36 72 */	rlwimi r0, r6, 6, 0x19, 0x19
/* 80093C28 00090808  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80093C2C 0009080C  3C 80 80 09 */	lis r4, ftCo_80092E50@ha
/* 80093C30 00090810  38 A4 2E 50 */	addi r5, r4, ftCo_80092E50@l
/* 80093C34 00090814  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 80093C38 00090818  50 C0 26 F6 */	rlwimi r0, r6, 4, 0x1b, 0x1b
/* 80093C3C 0009081C  38 81 00 14 */	addi r4, r1, 0x14
/* 80093C40 00090820  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 80093C44 00090824  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80093C48 00090828  80 DE 01 0C */	lwz r6, 0x10c(r30)
/* 80093C4C 0009082C  80 C6 00 08 */	lwz r6, 8(r6)
/* 80093C50 00090830  88 06 00 11 */	lbz r0, 0x11(r6)
/* 80093C54 00090834  90 01 00 14 */	stw r0, 0x14(r1)
/* 80093C58 00090838  D0 41 00 24 */	stfs f2, 0x24(r1)
/* 80093C5C 0009083C  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80093C60 00090840  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80093C64 00090844  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80093C68 00090848  4B FE 75 51 */	bl ftColl_8007B1B8
/* 80093C6C 0009084C  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 80093C70 00090850  38 60 00 01 */	li r3, 1
/* 80093C74 00090854  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 80093C78 00090858  98 1E 22 1A */	stb r0, 0x221a(r30)
lbl_80093C7C:
/* 80093C7C 0009085C  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093C80 00090860  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80093C84 00090864  41 82 00 34 */	beq lbl_80093CB8
/* 80093C88 00090868  C0 3F 23 58 */	lfs f1, 0x2358(r31)
/* 80093C8C 0009086C  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80093C90 00090870  EC 01 00 28 */	fsubs f0, f1, f0
/* 80093C94 00090874  D0 1F 23 58 */	stfs f0, 0x2358(r31)
/* 80093C98 00090878  C0 3F 23 58 */	lfs f1, 0x2358(r31)
/* 80093C9C 0009087C  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093CA0 00090880  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093CA4 00090884  40 80 00 14 */	bge lbl_80093CB8
/* 80093CA8 00090888  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093CAC 0009088C  38 60 00 00 */	li r3, 0
/* 80093CB0 00090890  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80093CB4 00090894  98 1F 22 1C */	stb r0, 0x221c(r31)
lbl_80093CB8:
/* 80093CB8 00090898  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80093CBC 0009089C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80093CC0 000908A0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80093CC4 000908A4  38 21 00 30 */	addi r1, r1, 0x30
/* 80093CC8 000908A8  7C 08 03 A6 */	mtlr r0
/* 80093CCC 000908AC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80093BC0(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x221C_b3) {
        fp->x221C_b3 = false;
    }
    if (fp->x221C_b1) {
        fp->mv.co.guard.x14 -= 1;
        if (fp->mv.co.guard.x14 < 0) {
            fp->x221C_b1 = false;
            fp->x2218_b3 = false;
            ftCo_80092450(gobj);
        }
    }
    if (fp->x221C_b2) {
        fp->mv.co.guard.x18 -= 1;
        if (fp->mv.co.guard.x18 < 0) {
            fp->x221C_b2 = false;
        }
    }
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_GuardReflect_Anim(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80093CD0 000908B0  7C 08 02 A6 */	mflr r0
/* 80093CD4 000908B4  90 01 00 04 */	stw r0, 4(r1)
/* 80093CD8 000908B8  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80093CDC 000908BC  93 E1 00 44 */	stw r31, 0x44(r1)
/* 80093CE0 000908C0  93 C1 00 40 */	stw r30, 0x40(r1)
/* 80093CE4 000908C4  7C 7E 1B 78 */	mr r30, r3
/* 80093CE8 000908C8  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 80093CEC 000908CC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80093CF0 000908D0  88 7F 22 1C */	lbz r3, 0x221c(r31)
/* 80093CF4 000908D4  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 80093CF8 000908D8  41 82 00 10 */	beq lbl_80093D08
/* 80093CFC 000908DC  38 00 00 00 */	li r0, 0
/* 80093D00 000908E0  50 03 26 F6 */	rlwimi r3, r0, 4, 0x1b, 0x1b
/* 80093D04 000908E4  98 7F 22 1C */	stb r3, 0x221c(r31)
lbl_80093D08:
/* 80093D08 000908E8  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093D0C 000908EC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80093D10 000908F0  41 82 00 88 */	beq lbl_80093D98
/* 80093D14 000908F4  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 80093D18 000908F8  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80093D1C 000908FC  EC 00 10 28 */	fsubs f0, f0, f2
/* 80093D20 00090900  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 80093D24 00090904  C0 3F 23 54 */	lfs f1, 0x2354(r31)
/* 80093D28 00090908  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093D2C 0009090C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093D30 00090910  40 80 00 68 */	bge lbl_80093D98
/* 80093D34 00090914  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093D38 00090918  38 80 00 00 */	li r4, 0
/* 80093D3C 0009091C  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 80093D40 00090920  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80093D44 00090924  3C 60 80 09 */	lis r3, ftCo_80092E50@ha
/* 80093D48 00090928  38 A3 2E 50 */	addi r5, r3, ftCo_80092E50@l
/* 80093D4C 0009092C  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 80093D50 00090930  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 80093D54 00090934  38 7E 00 00 */	addi r3, r30, 0
/* 80093D58 00090938  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 80093D5C 0009093C  38 81 00 24 */	addi r4, r1, 0x24
/* 80093D60 00090940  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80093D64 00090944  80 DD 01 0C */	lwz r6, 0x10c(r29)
/* 80093D68 00090948  80 C6 00 08 */	lwz r6, 8(r6)
/* 80093D6C 0009094C  88 06 00 11 */	lbz r0, 0x11(r6)
/* 80093D70 00090950  90 01 00 24 */	stw r0, 0x24(r1)
/* 80093D74 00090954  D0 41 00 34 */	stfs f2, 0x34(r1)
/* 80093D78 00090958  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80093D7C 0009095C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80093D80 00090960  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80093D84 00090964  4B FE 74 35 */	bl ftColl_8007B1B8
/* 80093D88 00090968  88 1D 22 1A */	lbz r0, 0x221a(r29)
/* 80093D8C 0009096C  38 60 00 01 */	li r3, 1
/* 80093D90 00090970  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 80093D94 00090974  98 1D 22 1A */	stb r0, 0x221a(r29)
lbl_80093D98:
/* 80093D98 00090978  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093D9C 0009097C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80093DA0 00090980  41 82 00 34 */	beq lbl_80093DD4
/* 80093DA4 00090984  C0 3F 23 58 */	lfs f1, 0x2358(r31)
/* 80093DA8 00090988  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80093DAC 0009098C  EC 01 00 28 */	fsubs f0, f1, f0
/* 80093DB0 00090990  D0 1F 23 58 */	stfs f0, 0x2358(r31)
/* 80093DB4 00090994  C0 3F 23 58 */	lfs f1, 0x2358(r31)
/* 80093DB8 00090998  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093DBC 0009099C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093DC0 000909A0  40 80 00 14 */	bge lbl_80093DD4
/* 80093DC4 000909A4  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093DC8 000909A8  38 60 00 00 */	li r3, 0
/* 80093DCC 000909AC  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80093DD0 000909B0  98 1F 22 1C */	stb r0, 0x221c(r31)
lbl_80093DD4:
/* 80093DD4 000909B4  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80093DD8 000909B8  7F C3 F3 78 */	mr r3, r30
/* 80093DDC 000909BC  C0 02 8B 88 */	lfs f0, ftCo_804D8568
/* 80093DE0 000909C0  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 80093DE4 000909C4  EC 01 00 2A */	fadds f0, f1, f0
/* 80093DE8 000909C8  D0 1D 23 40 */	stfs f0, 0x2340(r29)
/* 80093DEC 000909CC  4B FF E7 B9 */	bl ftCo_800925A4
/* 80093DF0 000909D0  2C 03 00 00 */	cmpwi r3, 0
/* 80093DF4 000909D4  40 82 00 B0 */	bne lbl_80093EA4
/* 80093DF8 000909D8  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 80093DFC 000909DC  C0 1D 02 E8 */	lfs f0, 0x2e8(r29)
/* 80093E00 000909E0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093E04 000909E4  4C 41 13 82 */	cror 2, 1, 2
/* 80093E08 000909E8  40 82 00 90 */	bne lbl_80093E98
/* 80093E0C 000909EC  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80093E10 000909F0  80 1D 00 04 */	lwz r0, 4(r29)
/* 80093E14 000909F4  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093E18 000909F8  41 82 00 08 */	beq lbl_80093E20
/* 80093E1C 000909FC  48 00 00 10 */	b lbl_80093E2C
lbl_80093E20:
/* 80093E20 00090A00  7F C3 F3 78 */	mr r3, r30
/* 80093E24 00090A04  48 09 83 B1 */	bl ftYs_Shield_8012C1D4
/* 80093E28 00090A08  48 00 00 7C */	b lbl_80093EA4
lbl_80093E2C:
/* 80093E2C 00090A0C  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80093E30 00090A10  7F C3 F3 78 */	mr r3, r30
/* 80093E34 00090A14  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80093E38 00090A18  38 80 00 B3 */	li r4, 0xb3
/* 80093E3C 00090A1C  FC 60 08 90 */	fmr f3, f1
/* 80093E40 00090A20  3C A0 20 00 */	lis r5, 0x2000
/* 80093E44 00090A24  38 C0 00 00 */	li r6, 0
/* 80093E48 00090A28  4B FD 55 65 */	bl Fighter_ChangeMotionState
/* 80093E4C 00090A2C  80 BD 01 0C */	lwz r5, 0x10c(r29)
/* 80093E50 00090A30  7F C3 F3 78 */	mr r3, r30
/* 80093E54 00090A34  80 DD 05 E8 */	lwz r6, 0x5e8(r29)
/* 80093E58 00090A38  38 80 04 18 */	li r4, 0x418
/* 80093E5C 00090A3C  80 A5 00 08 */	lwz r5, 8(r5)
/* 80093E60 00090A40  88 05 00 11 */	lbz r0, 0x11(r5)
/* 80093E64 00090A44  54 00 20 36 */	slwi r0, r0, 4
/* 80093E68 00090A48  7C A6 00 2E */	lwzx r5, r6, r0
/* 80093E6C 00090A4C  4B FF E2 ED */	bl ftCo_80092158
/* 80093E70 00090A50  88 1D 22 19 */	lbz r0, 0x2219(r29)
/* 80093E74 00090A54  38 60 00 01 */	li r3, 1
/* 80093E78 00090A58  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80093E7C 00090A5C  98 1D 22 19 */	stb r0, 0x2219(r29)
/* 80093E80 00090A60  7F C3 F3 78 */	mr r3, r30
/* 80093E84 00090A64  4B FF E5 CD */	bl ftCo_80092450
/* 80093E88 00090A68  7F C3 F3 78 */	mr r3, r30
/* 80093E8C 00090A6C  C0 22 8B 88 */	lfs f1, ftCo_804D8568
/* 80093E90 00090A70  4B FF DF E9 */	bl ftCo_80091E78
/* 80093E94 00090A74  48 00 00 10 */	b lbl_80093EA4
lbl_80093E98:
/* 80093E98 00090A78  7F C3 F3 78 */	mr r3, r30
/* 80093E9C 00090A7C  EC 21 00 24 */	fdivs f1, f1, f0
/* 80093EA0 00090A80  4B FF DF D9 */	bl ftCo_80091E78
lbl_80093EA4:
/* 80093EA4 00090A84  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80093EA8 00090A88  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 80093EAC 00090A8C  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 80093EB0 00090A90  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 80093EB4 00090A94  38 21 00 48 */	addi r1, r1, 0x48
/* 80093EB8 00090A98  7C 08 03 A6 */	mtlr r0
/* 80093EBC 00090A9C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_GuardReflect_Anim(HSD_GObj* gobj)
{
    ftCo_80093BC0(gobj);
    ftCo_GuardOn_Anim(gobj);
}
#endif

#ifdef MUST_MATCH
#pragma push
asm void ftCo_GuardReflect_IASA(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80093EC0 00090AA0  7C 08 02 A6 */	mflr r0
/* 80093EC4 00090AA4  90 01 00 04 */	stw r0, 4(r1)
/* 80093EC8 00090AA8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80093ECC 00090AAC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80093ED0 00090AB0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80093ED4 00090AB4  7C 7E 1B 78 */	mr r30, r3
/* 80093ED8 00090AB8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80093EDC 00090ABC  80 04 06 5C */	lwz r0, 0x65c(r4)
/* 80093EE0 00090AC0  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 80093EE4 00090AC4  40 82 00 0C */	bne lbl_80093EF0
/* 80093EE8 00090AC8  38 00 00 01 */	li r0, 1
/* 80093EEC 00090ACC  90 04 23 4C */	stw r0, 0x234c(r4)
lbl_80093EF0:
/* 80093EF0 00090AD0  80 04 23 4C */	lwz r0, 0x234c(r4)
/* 80093EF4 00090AD4  2C 00 00 00 */	cmpwi r0, 0
/* 80093EF8 00090AD8  41 82 00 14 */	beq lbl_80093F0C
/* 80093EFC 00090ADC  C0 24 23 50 */	lfs f1, 0x2350(r4)
/* 80093F00 00090AE0  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80093F04 00090AE4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80093F08 00090AE8  41 82 00 1C */	beq lbl_80093F24
lbl_80093F0C:
/* 80093F0C 00090AEC  88 04 22 1B */	lbz r0, 0x221b(r4)
/* 80093F10 00090AF0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80093F14 00090AF4  40 82 00 84 */	bne lbl_80093F98
/* 80093F18 00090AF8  88 04 22 18 */	lbz r0, 0x2218(r4)
/* 80093F1C 00090AFC  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80093F20 00090B00  40 82 00 78 */	bne lbl_80093F98
lbl_80093F24:
/* 80093F24 00090B04  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80093F28 00090B08  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80093F2C 00090B0C  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80093F30 00090B10  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 80093F34 00090B14  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80093F38 00090B18  4B FA A1 DD */	bl pl_8003E114
/* 80093F3C 00090B1C  80 1F 00 04 */	lwz r0, 4(r31)
/* 80093F40 00090B20  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093F44 00090B24  41 82 00 08 */	beq lbl_80093F4C
/* 80093F48 00090B28  48 00 00 10 */	b lbl_80093F58
lbl_80093F4C:
/* 80093F4C 00090B2C  7F C3 F3 78 */	mr r3, r30
/* 80093F50 00090B30  48 09 85 4D */	bl ftYs_Shield_8012C49C
/* 80093F54 00090B34  48 00 00 3C */	b lbl_80093F90
lbl_80093F58:
/* 80093F58 00090B38  C0 22 8B 58 */	lfs f1, ftCo_804D8538
/* 80093F5C 00090B3C  7F C3 F3 78 */	mr r3, r30
/* 80093F60 00090B40  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80093F64 00090B44  38 80 00 B4 */	li r4, 0xb4
/* 80093F68 00090B48  FC 60 08 90 */	fmr f3, f1
/* 80093F6C 00090B4C  C0 42 8B 88 */	lfs f2, ftCo_804D8568
/* 80093F70 00090B50  38 A0 00 00 */	li r5, 0
/* 80093F74 00090B54  38 C0 00 00 */	li r6, 0
/* 80093F78 00090B58  4B FD 54 35 */	bl Fighter_ChangeMotionState
/* 80093F7C 00090B5C  38 7F 00 00 */	addi r3, r31, 0
/* 80093F80 00090B60  38 80 00 7F */	li r4, 0x7f
/* 80093F84 00090B64  38 A0 00 7F */	li r5, 0x7f
/* 80093F88 00090B68  38 C0 00 40 */	li r6, 0x40
/* 80093F8C 00090B6C  4B FF 41 BD */	bl ft_80088148
lbl_80093F90:
/* 80093F90 00090B70  38 00 00 01 */	li r0, 1
/* 80093F94 00090B74  48 00 00 1C */	b lbl_80093FB0
lbl_80093F98:
/* 80093F98 00090B78  80 64 23 5C */	lwz r3, 0x235c(r4)
/* 80093F9C 00090B7C  2C 03 00 00 */	cmpwi r3, 0
/* 80093FA0 00090B80  41 82 00 0C */	beq lbl_80093FAC
/* 80093FA4 00090B84  38 03 FF FF */	addi r0, r3, -1
/* 80093FA8 00090B88  90 04 23 5C */	stw r0, 0x235c(r4)
lbl_80093FAC:
/* 80093FAC 00090B8C  38 00 00 00 */	li r0, 0
lbl_80093FB0:
/* 80093FB0 00090B90  2C 00 00 00 */	cmpwi r0, 0
/* 80093FB4 00090B94  40 82 00 70 */	bne lbl_80094024
/* 80093FB8 00090B98  7F C3 F3 78 */	mr r3, r30
/* 80093FBC 00090B9C  48 00 11 A1 */	bl ftCo_8009515C
/* 80093FC0 00090BA0  2C 03 00 00 */	cmpwi r3, 0
/* 80093FC4 00090BA4  40 82 00 60 */	bne lbl_80094024
/* 80093FC8 00090BA8  7F C3 F3 78 */	mr r3, r30
/* 80093FCC 00090BAC  48 00 58 41 */	bl ftCo_8009980C
/* 80093FD0 00090BB0  2C 03 00 00 */	cmpwi r3, 0
/* 80093FD4 00090BB4  40 82 00 50 */	bne lbl_80094024
/* 80093FD8 00090BB8  7F C3 F3 78 */	mr r3, r30
/* 80093FDC 00090BBC  48 00 51 A1 */	bl ftCo_8009917C
/* 80093FE0 00090BC0  2C 03 00 00 */	cmpwi r3, 0
/* 80093FE4 00090BC4  40 82 00 40 */	bne lbl_80094024
/* 80093FE8 00090BC8  7F C3 F3 78 */	mr r3, r30
/* 80093FEC 00090BCC  48 04 4B B1 */	bl ftCo_800D8B9C
/* 80093FF0 00090BD0  2C 03 00 00 */	cmpwi r3, 0
/* 80093FF4 00090BD4  40 82 00 30 */	bne lbl_80094024
/* 80093FF8 00090BD8  7F C3 F3 78 */	mr r3, r30
/* 80093FFC 00090BDC  48 04 49 95 */	bl ftCo_Catch_CheckInput
/* 80094000 00090BE0  2C 03 00 00 */	cmpwi r3, 0
/* 80094004 00090BE4  40 82 00 20 */	bne lbl_80094024
/* 80094008 00090BE8  7F C3 F3 78 */	mr r3, r30
/* 8009400C 00090BEC  48 03 70 19 */	bl ftCo_800CB024
/* 80094010 00090BF0  2C 03 00 00 */	cmpwi r3, 0
/* 80094014 00090BF4  40 82 00 10 */	bne lbl_80094024
/* 80094018 00090BF8  7F C3 F3 78 */	mr r3, r30
/* 8009401C 00090BFC  48 00 60 65 */	bl ftCo_8009A080
/* 80094020 00090C00  2C 03 00 00 */	cmpwi r3, 0
lbl_80094024:
/* 80094024 00090C04  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80094028 00090C08  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8009402C 00090C0C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80094030 00090C10  38 21 00 28 */	addi r1, r1, 0x28
/* 80094034 00090C14  7C 08 03 A6 */	mtlr r0
/* 80094038 00090C18  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_GuardReflect_IASA(HSD_GObj* gobj)
{
    u8 _[16] = { 0 };
    /// @todo Inline depth.
    RETURN_IF(inlineC0(gobj, ftCo_80092BE8));
    RETURN_IF(ftCo_8009515C(gobj));
    RETURN_IF(ftCo_8009980C(gobj));
    RETURN_IF(ftCo_8009917C(gobj));
    RETURN_IF(ftCo_800D8B9C(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_800CB024(gobj));
    RETURN_IF(ftCo_8009A080(gobj));
}
#endif

void ftCo_GuardReflect_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
    ftColl_8007AEE0(gobj);
    ftColl_8007AEF8(gobj);
}

void ftCo_GuardReflect_Coll(ftCo_GObj* gobj)
{
    ft_800845B4(gobj);
}

#ifdef MUST_MATCH
#pragma push
asm UNK_RET ftCo_80094098(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 80094098 00090C78  7C 08 02 A6 */	mflr r0
/* 8009409C 00090C7C  7C 85 23 78 */	mr r5, r4
/* 800940A0 00090C80  90 01 00 04 */	stw r0, 4(r1)
/* 800940A4 00090C84  38 80 00 00 */	li r4, 0
/* 800940A8 00090C88  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800940AC 00090C8C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800940B0 00090C90  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800940B4 00090C94  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 800940B8 00090C98  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 800940BC 00090C9C  80 63 00 08 */	lwz r3, 8(r3)
/* 800940C0 00090CA0  88 03 00 11 */	lbz r0, 0x11(r3)
/* 800940C4 00090CA4  54 00 20 36 */	slwi r0, r0, 4
/* 800940C8 00090CA8  7C 66 00 2E */	lwzx r3, r6, r0
/* 800940CC 00090CAC  4B F7 71 01 */	bl lb_8000B1CC
/* 800940D0 00090CB0  80 1F 00 04 */	lwz r0, 4(r31)
/* 800940D4 00090CB4  2C 00 00 0E */	cmpwi r0, 0xe
/* 800940D8 00090CB8  40 82 00 0C */	bne lbl_800940E4
/* 800940DC 00090CBC  C0 3F 01 A0 */	lfs f1, 0x1a0(r31)
/* 800940E0 00090CC0  48 00 00 44 */	b lbl_80094124
lbl_800940E4:
/* 800940E4 00090CC4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800940E8 00090CC8  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 800940EC 00090CCC  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 800940F0 00090CD0  C0 A3 02 D4 */	lfs f5, 0x2d4(r3)
/* 800940F4 00090CD4  EC 61 00 24 */	fdivs f3, f1, f0
/* 800940F8 00090CD8  C0 03 02 D8 */	lfs f0, 0x2d8(r3)
/* 800940FC 00090CDC  C0 5F 19 9C */	lfs f2, 0x199c(r31)
/* 80094100 00090CE0  C0 C3 02 64 */	lfs f6, 0x264(r3)
/* 80094104 00090CE4  C0 82 8B 88 */	lfs f4, ftCo_804D8568
/* 80094108 00090CE8  EC 20 28 28 */	fsubs f1, f0, f5
/* 8009410C 00090CEC  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80094110 00090CF0  EC 84 30 28 */	fsubs f4, f4, f6
/* 80094114 00090CF4  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80094118 00090CF8  EC 23 00 72 */	fmuls f1, f3, f1
/* 8009411C 00090CFC  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 80094120 00090D00  EC 21 00 32 */	fmuls f1, f1, f0
lbl_80094124:
/* 80094124 00090D04  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80094128 00090D08  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8009412C 00090D0C  38 21 00 28 */	addi r1, r1, 0x28
/* 80094130 00090D10  7C 08 03 A6 */	mtlr r0
/* 80094134 00090D14  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
asm UNK_RET ftCo_80094138(UNK_PARAMS)
{ // clang-format off
    nofralloc
/* 80094138 00090D18  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8009413C 00090D1C  80 04 02 B8 */	lwz r0, 0x2b8(r4)
/* 80094140 00090D20  90 03 23 5C */	stw r0, 0x235c(r3)
/* 80094144 00090D24  C0 02 8B 58 */	lfs f0, ftCo_804D8538
/* 80094148 00090D28  D0 03 23 50 */	stfs f0, 0x2350(r3)
/* 8009414C 00090D2C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
