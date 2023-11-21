#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_DownBound.h"

#include "ftCo_09F7.h"
#include "ftCo_Down.h"
#include "ftCo_DownAttack.h"
#include "ftCo_DownStand.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0C88.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftSandbag/ftSb_Init.h"

#include <common_structs.h>
#include <math.h>
#include <placeholder.h>
#include <baselib/jobj.h>

#ifdef MWERKS_GEKKO
float const ftCo_804D85F8 = 0;
double const ftCo_804D8600 = 0.5;
double const ftCo_804D8608 = 3;
float const ftCo_804D8610 = 1;
extern char* ftCo_804D3B18; // = "jobj.h"
extern char* ftCo_804D3B20; // = "jobj"
#endif

enum_t ftCo_DownBound_SfxIds[] = { 9, 10, 11, 12 };

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm bool ftCo_80097570(ftCo_GObj* gobj)
{
    // clang-format off
    nofralloc
/* 80097570 00094150  7C 08 02 A6 */	mflr r0
/* 80097574 00094154  38 80 00 04 */	li r4, 4
/* 80097578 00094158  90 01 00 04 */	stw r0, 4(r1)
/* 8009757C 0009415C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80097580 00094160  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80097584 00094164  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80097588 00094168  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009758C 0009416C  38 7F 00 00 */	addi r3, r31, 0
/* 80097590 00094170  4B FD DA 7D */	bl ftParts_8007500C
/* 80097594 00094174  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80097598 00094178  54 60 20 36 */	slwi r0, r3, 4
/* 8009759C 0009417C  7F C4 00 2E */	lwzx r30, r4, r0
/* 800975A0 00094180  28 1E 00 00 */	cmplwi r30, 0
/* 800975A4 00094184  41 82 00 44 */	beq lbl_800975E8
/* 800975A8 00094188  40 82 00 14 */	bne lbl_800975BC
/* 800975AC 0009418C  38 6D 84 78 */	addi r3, r13, ftCo_804D3B18
/* 800975B0 00094190  38 80 02 34 */	li r4, 0x234
/* 800975B4 00094194  38 AD 84 80 */	addi r5, r13, ftCo_804D3B20
/* 800975B8 00094198  48 2F 0C 69 */	bl __assert
lbl_800975BC:
/* 800975BC 0009419C  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 800975C0 000941A0  38 60 00 00 */	li r3, 0
/* 800975C4 000941A4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800975C8 000941A8  40 82 00 10 */	bne lbl_800975D8
/* 800975CC 000941AC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800975D0 000941B0  41 82 00 08 */	beq lbl_800975D8
/* 800975D4 000941B4  38 60 00 01 */	li r3, 1
lbl_800975D8:
/* 800975D8 000941B8  2C 03 00 00 */	cmpwi r3, 0
/* 800975DC 000941BC  41 82 00 0C */	beq lbl_800975E8
/* 800975E0 000941C0  7F C3 F3 78 */	mr r3, r30
/* 800975E4 000941C4  48 2D BA 95 */	bl HSD_JObjSetupMatrixSub
lbl_800975E8:
/* 800975E8 000941C8  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 800975EC 000941CC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800975F0 000941D0  41 82 00 0C */	beq lbl_800975FC
/* 800975F4 000941D4  C0 3E 00 5C */	lfs f1, 0x5c(r30)
/* 800975F8 000941D8  48 00 00 08 */	b lbl_80097600
lbl_800975FC:
/* 800975FC 000941DC  C0 3E 00 58 */	lfs f1, 0x58(r30)
lbl_80097600:
/* 80097600 000941E0  C0 02 8C 18 */	lfs f0, ftCo_804D85F8
/* 80097604 000941E4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80097608 000941E8  40 81 00 0C */	ble lbl_80097614
/* 8009760C 000941EC  38 60 00 01 */	li r3, 1
/* 80097610 000941F0  48 00 00 08 */	b lbl_80097618
lbl_80097614:
/* 80097614 000941F4  38 60 00 00 */	li r3, 0
lbl_80097618:
/* 80097618 000941F8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009761C 000941FC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80097620 00094200  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80097624 00094204  38 21 00 18 */	addi r1, r1, 0x18
/* 80097628 00094208  7C 08 03 A6 */	mtlr r0
/* 8009762C 0009420C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool ftCo_80097570(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    HSD_JObj* jobj = fp->parts[ftParts_8007500C(fp, FtPart_HipN)].joint;
    HSD_JObjSetupMatrix(jobj);
    {
        float f = fp->x2226_b0 ? jobj->mtx[1][2] : jobj->mtx[1][1];
        if (f > 0) {
            return true;
        }
        return false;
    }
}
#endif

void ftCo_80097630(Fighter* fp, enum_t* sfx_ids, float threshold)
{
    ft_80088148(fp,
                threshold >= p_ftCommonData->x1F0   ? sfx_ids[0]
                : threshold >= p_ftCommonData->x1F4 ? sfx_ids[1]
                : threshold >= p_ftCommonData->x1F4 ? sfx_ids[2]
                                                    : sfx_ids[3],
                127, 64);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_800976A4(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 800976A4 00094284  7C 08 02 A6 */	mflr r0
/* 800976A8 00094288  90 01 00 04 */	stw r0, 4(r1)
/* 800976AC 0009428C  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 800976B0 00094290  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 800976B4 00094294  93 E1 00 54 */	stw r31, 0x54(r1)
/* 800976B8 00094298  93 C1 00 50 */	stw r30, 0x50(r1)
/* 800976BC 0009429C  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 800976C0 000942A0  93 81 00 48 */	stw r28, 0x48(r1)
/* 800976C4 000942A4  7C 7C 1B 78 */	mr r28, r3
/* 800976C8 000942A8  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800976CC 000942AC  3C 60 80 3C */	lis r3, ftCo_DownBound_SfxIds@ha
/* 800976D0 000942B0  C0 02 8C 18 */	lfs f0, ftCo_804D85F8
/* 800976D4 000942B4  3B E3 57 00 */	addi r31, r3, ftCo_DownBound_SfxIds@l
/* 800976D8 000942B8  C0 5E 00 84 */	lfs f2, 0x84(r30)
/* 800976DC 000942BC  C0 3E 00 90 */	lfs f1, 0x90(r30)
/* 800976E0 000942C0  C0 7E 00 80 */	lfs f3, 0x80(r30)
/* 800976E4 000942C4  EC 82 08 2A */	fadds f4, f2, f1
/* 800976E8 000942C8  C0 3E 00 8C */	lfs f1, 0x8c(r30)
/* 800976EC 000942CC  EC 43 08 2A */	fadds f2, f3, f1
/* 800976F0 000942D0  EC 24 01 32 */	fmuls f1, f4, f4
/* 800976F4 000942D4  EC 82 08 BA */	fmadds f4, f2, f2, f1
/* 800976F8 000942D8  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800976FC 000942DC  40 81 00 50 */	ble lbl_8009774C
/* 80097700 000942E0  FC 20 20 34 */	frsqrte f1, f4
/* 80097704 000942E4  C8 62 8C 20 */	lfd f3, ftCo_804D8600
/* 80097708 000942E8  C8 42 8C 28 */	lfd f2, ftCo_804D8608
/* 8009770C 000942EC  FC 01 00 72 */	fmul f0, f1, f1
/* 80097710 000942F0  FC 23 00 72 */	fmul f1, f3, f1
/* 80097714 000942F4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80097718 000942F8  FC 21 00 32 */	fmul f1, f1, f0
/* 8009771C 000942FC  FC 01 00 72 */	fmul f0, f1, f1
/* 80097720 00094300  FC 23 00 72 */	fmul f1, f3, f1
/* 80097724 00094304  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80097728 00094308  FC 21 00 32 */	fmul f1, f1, f0
/* 8009772C 0009430C  FC 01 00 72 */	fmul f0, f1, f1
/* 80097730 00094310  FC 23 00 72 */	fmul f1, f3, f1
/* 80097734 00094314  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80097738 00094318  FC 01 00 32 */	fmul f0, f1, f0
/* 8009773C 0009431C  FC 04 00 32 */	fmul f0, f4, f0
/* 80097740 00094320  FC 00 00 18 */	frsp f0, f0
/* 80097744 00094324  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80097748 00094328  C0 81 00 14 */	lfs f4, 0x14(r1)
lbl_8009774C:
/* 8009774C 0009432C  C0 1E 01 98 */	lfs f0, 0x198(r30)
/* 80097750 00094330  38 00 00 01 */	li r0, 1
/* 80097754 00094334  38 7C 00 00 */	addi r3, r28, 0
/* 80097758 00094338  EF E4 00 32 */	fmuls f31, f4, f0
/* 8009775C 0009433C  90 01 00 34 */	stw r0, 0x34(r1)
/* 80097760 00094340  38 81 00 38 */	addi r4, r1, 0x38
/* 80097764 00094344  38 A1 00 34 */	addi r5, r1, 0x34
/* 80097768 00094348  38 C1 00 30 */	addi r6, r1, 0x30
/* 8009776C 0009434C  3B A0 04 07 */	li r29, 0x407
/* 80097770 00094350  4B FE D5 05 */	bl ft_80084C74
/* 80097774 00094354  2C 03 00 00 */	cmpwi r3, 0
/* 80097778 00094358  41 82 00 78 */	beq lbl_800977F0
/* 8009777C 0009435C  80 81 00 38 */	lwz r4, 0x38(r1)
/* 80097780 00094360  2C 04 FF FF */	cmpwi r4, -1
/* 80097784 00094364  41 82 00 5C */	beq lbl_800977E0
/* 80097788 00094368  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009778C 0009436C  C0 03 01 F0 */	lfs f0, 0x1f0(r3)
/* 80097790 00094370  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80097794 00094374  4C 41 13 82 */	cror 2, 1, 2
/* 80097798 00094378  40 82 00 08 */	bne lbl_800977A0
/* 8009779C 0009437C  48 00 00 34 */	b lbl_800977D0
lbl_800977A0:
/* 800977A0 00094380  C0 03 01 F4 */	lfs f0, 0x1f4(r3)
/* 800977A4 00094384  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800977A8 00094388  4C 41 13 82 */	cror 2, 1, 2
/* 800977AC 0009438C  40 82 00 0C */	bne lbl_800977B8
/* 800977B0 00094390  80 81 00 3C */	lwz r4, 0x3c(r1)
/* 800977B4 00094394  48 00 00 1C */	b lbl_800977D0
lbl_800977B8:
/* 800977B8 00094398  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 800977BC 0009439C  4C 41 13 82 */	cror 2, 1, 2
/* 800977C0 000943A0  40 82 00 0C */	bne lbl_800977CC
/* 800977C4 000943A4  80 81 00 40 */	lwz r4, 0x40(r1)
/* 800977C8 000943A8  48 00 00 08 */	b lbl_800977D0
lbl_800977CC:
/* 800977CC 000943AC  80 81 00 44 */	lwz r4, 0x44(r1)
lbl_800977D0:
/* 800977D0 000943B0  38 7E 00 00 */	addi r3, r30, 0
/* 800977D4 000943B4  38 A0 00 7F */	li r5, 0x7f
/* 800977D8 000943B8  38 C0 00 40 */	li r6, 0x40
/* 800977DC 000943BC  4B FF 09 6D */	bl ft_80088148
lbl_800977E0:
/* 800977E0 000943C0  80 01 00 30 */	lwz r0, 0x30(r1)
/* 800977E4 000943C4  2C 00 FF FF */	cmpwi r0, -1
/* 800977E8 000943C8  41 82 00 08 */	beq lbl_800977F0
/* 800977EC 000943CC  7C 1D 03 78 */	mr r29, r0
lbl_800977F0:
/* 800977F0 000943D0  C0 22 8C 18 */	lfs f1, ftCo_804D85F8
/* 800977F4 000943D4  38 7C 00 00 */	addi r3, r28, 0
/* 800977F8 000943D8  38 9D 00 00 */	addi r4, r29, 0
/* 800977FC 000943DC  D0 21 00 2C */	stfs f1, 0x2c(r1)
/* 80097800 000943E0  39 01 00 24 */	addi r8, r1, 0x24
/* 80097804 000943E4  39 21 00 18 */	addi r9, r1, 0x18
/* 80097808 000943E8  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 8009780C 000943EC  38 A0 00 00 */	li r5, 0
/* 80097810 000943F0  38 C0 00 00 */	li r6, 0
/* 80097814 000943F4  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 80097818 000943F8  38 E0 00 00 */	li r7, 0
/* 8009781C 000943FC  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 80097820 00094400  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 80097824 00094404  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80097828 00094408  48 00 80 0D */	bl ftCo_8009F834
/* 8009782C 0009440C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80097830 00094410  2C 00 00 00 */	cmpwi r0, 0
/* 80097834 00094414  41 82 00 60 */	beq lbl_80097894
/* 80097838 00094418  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009783C 0009441C  C0 03 01 F0 */	lfs f0, 0x1f0(r3)
/* 80097840 00094420  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80097844 00094424  4C 41 13 82 */	cror 2, 1, 2
/* 80097848 00094428  40 82 00 0C */	bne lbl_80097854
/* 8009784C 0009442C  80 9F 00 00 */	lwz r4, 0(r31)
/* 80097850 00094430  48 00 00 34 */	b lbl_80097884
lbl_80097854:
/* 80097854 00094434  C0 03 01 F4 */	lfs f0, 0x1f4(r3)
/* 80097858 00094438  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8009785C 0009443C  4C 41 13 82 */	cror 2, 1, 2
/* 80097860 00094440  40 82 00 0C */	bne lbl_8009786C
/* 80097864 00094444  80 9F 00 04 */	lwz r4, 4(r31)
/* 80097868 00094448  48 00 00 1C */	b lbl_80097884
lbl_8009786C:
/* 8009786C 0009444C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80097870 00094450  4C 41 13 82 */	cror 2, 1, 2
/* 80097874 00094454  40 82 00 0C */	bne lbl_80097880
/* 80097878 00094458  80 9F 00 08 */	lwz r4, 8(r31)
/* 8009787C 0009445C  48 00 00 08 */	b lbl_80097884
lbl_80097880:
/* 80097880 00094460  80 9F 00 0C */	lwz r4, 0xc(r31)
lbl_80097884:
/* 80097884 00094464  38 7E 00 00 */	addi r3, r30, 0
/* 80097888 00094468  38 A0 00 7F */	li r5, 0x7f
/* 8009788C 0009446C  38 C0 00 40 */	li r6, 0x40
/* 80097890 00094470  4B FF 08 B9 */	bl ft_80088148
lbl_80097894:
/* 80097894 00094474  38 60 00 04 */	li r3, 4
/* 80097898 00094478  38 9E 00 B0 */	addi r4, r30, 0xb0
/* 8009789C 0009447C  4B F9 95 A9 */	bl Camera_80030E44
/* 800978A0 00094480  38 7E 00 00 */	addi r3, r30, 0
/* 800978A4 00094484  38 80 00 09 */	li r4, 9
/* 800978A8 00094488  38 A0 00 00 */	li r5, 0
/* 800978AC 0009448C  4B FE 73 01 */	bl ftCommon_8007EBAC
/* 800978B0 00094490  80 01 00 64 */	lwz r0, 0x64(r1)
/* 800978B4 00094494  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 800978B8 00094498  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 800978BC 0009449C  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 800978C0 000944A0  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 800978C4 000944A4  83 81 00 48 */	lwz r28, 0x48(r1)
/* 800978C8 000944A8  38 21 00 60 */	addi r1, r1, 0x60
/* 800978CC 000944AC  7C 08 03 A6 */	mtlr r0
/* 800978D0 000944B0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_800976A4(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    float vel_x = fp->self_vel.x + fp->x8c_kb_vel.x;
    float vel_y = fp->self_vel.y + fp->x8c_kb_vel.y;
    float dist = sqrtf(SQ(vel_x) + SQ(vel_y)) * fp->co_attrs.weight;
    enum_t ef_id = 1031;
    IntVec3 ivec;
    Vec3 vec1;
    Vec3 vec0;
    ivec.y = 1;
    if (ft_80084C74(gobj, &ivec.z, &ivec.y, &ivec.x)) {
        if (ivec.z != -1) {
            ftCo_80097630(fp, ftCo_DownBound_SfxIds, dist);
        }
        if (ivec.x != -1) {
            ef_id = ivec.x;
        }
    }
    vec0.x = vec1.x = 0;
    vec0.y = vec1.y = 0;
    vec0.z = vec1.z = 0;
    ftCo_8009F834(gobj, ef_id, 0, 0, 0, &vec1, &vec0, 0);
    if (ivec.y != 0) {
        ftCo_80097630(fp, ftCo_DownBound_SfxIds, dist);
    }
    Camera_80030E44(4, &fp->cur_pos);
    ftCommon_8007EBAC(fp, 9, 0);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_800978D4(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 800978D4 000944B4  7C 08 02 A6 */	mflr r0
/* 800978D8 000944B8  90 01 00 04 */	stw r0, 4(r1)
/* 800978DC 000944BC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800978E0 000944C0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800978E4 000944C4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800978E8 000944C8  7C 7E 1B 78 */	mr r30, r3
/* 800978EC 000944CC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800978F0 000944D0  C0 1F 08 44 */	lfs f0, 0x844(r31)
/* 800978F4 000944D4  C0 5F 08 48 */	lfs f2, 0x848(r31)
/* 800978F8 000944D8  FC 20 00 50 */	fneg f1, f0
/* 800978FC 000944DC  4B F8 B3 35 */	bl atan2f
/* 80097900 000944E0  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80097904 000944E4  38 7E 00 00 */	addi r3, r30, 0
/* 80097908 000944E8  39 01 00 18 */	addi r8, r1, 0x18
/* 8009790C 000944EC  4C C6 31 82 */	crclr 6
/* 80097910 000944F0  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80097914 000944F4  81 3E 00 2C */	lwz r9, 0x2c(r30)
/* 80097918 000944F8  38 A0 00 04 */	li r5, 4
/* 8009791C 000944FC  80 E4 00 00 */	lwz r7, 0(r4)
/* 80097920 00094500  38 C0 04 06 */	li r6, 0x406
/* 80097924 00094504  38 89 06 0C */	addi r4, r9, 0x60c
/* 80097928 00094508  4B FC FD C9 */	bl efAsync_Spawn
/* 8009792C 0009450C  7F C3 F3 78 */	mr r3, r30
/* 80097930 00094510  4B FF FD 75 */	bl ftCo_800976A4
/* 80097934 00094514  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80097938 00094518  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8009793C 0009451C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80097940 00094520  38 21 00 28 */	addi r1, r1, 0x28
/* 80097944 00094524  7C 08 03 A6 */	mtlr r0
/* 80097948 00094528  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo This is a common inline. Needs to be solved and placed in a header.
///       Could also be a real library function.
static inline void inlineA0(ftCo_GObj* gobj, enum_t arg1, enum_t arg2,
                            Fighter_Part part, float* param)
{
    ftCo_Fighter* fp = gobj->user_data;
    void* fp_x60C = &fp->x60C;
    HSD_JObj* jobj = fp->parts[part].joint;
    efAsync_Spawn(gobj, fp_x60C, arg1, arg2, jobj, &param);
}

void ftCo_800978D4(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    float param =
        atan2f(-fp->coll_data.floor.normal.x, fp->coll_data.floor.normal.y);
    inlineA0(gobj, 4, 1030, FtPart_TopN, &param);
    ftCo_800976A4(gobj);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_8009794C(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8009794C 0009452C  7C 08 02 A6 */	mflr r0
/* 80097950 00094530  90 01 00 04 */	stw r0, 4(r1)
/* 80097954 00094534  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80097958 00094538  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8009795C 0009453C  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80097960 00094540  7C 7E 1B 78 */	mr r30, r3
/* 80097964 00094544  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80097968 00094548  93 81 00 30 */	stw r28, 0x30(r1)
/* 8009796C 0009454C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80097970 00094550  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 80097974 00094554  3B E3 00 00 */	addi r31, r3, 0
/* 80097978 00094558  2C 00 00 01 */	cmpwi r0, 1
/* 8009797C 0009455C  40 82 00 0C */	bne lbl_80097988
/* 80097980 00094560  7F E3 FB 78 */	mr r3, r31
/* 80097984 00094564  4B FE 5E 79 */	bl ftCommon_8007D7FC
lbl_80097988:
/* 80097988 00094568  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 8009798C 0009456C  38 80 00 04 */	li r4, 4
/* 80097990 00094570  38 7D 00 00 */	addi r3, r29, 0
/* 80097994 00094574  4B FD D6 79 */	bl ftParts_8007500C
/* 80097998 00094578  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 8009799C 0009457C  54 60 20 36 */	slwi r0, r3, 4
/* 800979A0 00094580  7F 84 00 2E */	lwzx r28, r4, r0
/* 800979A4 00094584  28 1C 00 00 */	cmplwi r28, 0
/* 800979A8 00094588  41 82 00 44 */	beq lbl_800979EC
/* 800979AC 0009458C  40 82 00 14 */	bne lbl_800979C0
/* 800979B0 00094590  38 6D 84 78 */	addi r3, r13, ftCo_804D3B18
/* 800979B4 00094594  38 80 02 34 */	li r4, 0x234
/* 800979B8 00094598  38 AD 84 80 */	addi r5, r13, ftCo_804D3B20
/* 800979BC 0009459C  48 2F 08 65 */	bl __assert
lbl_800979C0:
/* 800979C0 000945A0  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 800979C4 000945A4  38 60 00 00 */	li r3, 0
/* 800979C8 000945A8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800979CC 000945AC  40 82 00 10 */	bne lbl_800979DC
/* 800979D0 000945B0  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800979D4 000945B4  41 82 00 08 */	beq lbl_800979DC
/* 800979D8 000945B8  38 60 00 01 */	li r3, 1
lbl_800979DC:
/* 800979DC 000945BC  2C 03 00 00 */	cmpwi r3, 0
/* 800979E0 000945C0  41 82 00 0C */	beq lbl_800979EC
/* 800979E4 000945C4  7F 83 E3 78 */	mr r3, r28
/* 800979E8 000945C8  48 2D B6 91 */	bl HSD_JObjSetupMatrixSub
lbl_800979EC:
/* 800979EC 000945CC  88 1D 22 26 */	lbz r0, 0x2226(r29)
/* 800979F0 000945D0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800979F4 000945D4  41 82 00 0C */	beq lbl_80097A00
/* 800979F8 000945D8  C0 3C 00 5C */	lfs f1, 0x5c(r28)
/* 800979FC 000945DC  48 00 00 08 */	b lbl_80097A04
lbl_80097A00:
/* 80097A00 000945E0  C0 3C 00 58 */	lfs f1, 0x58(r28)
lbl_80097A04:
/* 80097A04 000945E4  C0 02 8C 18 */	lfs f0, ftCo_804D85F8
/* 80097A08 000945E8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80097A0C 000945EC  40 81 00 0C */	ble lbl_80097A18
/* 80097A10 000945F0  38 60 00 01 */	li r3, 1
/* 80097A14 000945F4  48 00 00 08 */	b lbl_80097A1C
lbl_80097A18:
/* 80097A18 000945F8  38 60 00 00 */	li r3, 0
lbl_80097A1C:
/* 80097A1C 000945FC  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 80097A20 00094600  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80097A24 00094604  41 82 00 10 */	beq lbl_80097A34
/* 80097A28 00094608  7C 60 00 34 */	cntlzw r0, r3
/* 80097A2C 0009460C  54 00 D9 7E */	srwi r0, r0, 5
/* 80097A30 00094610  7C 03 03 78 */	mr r3, r0
lbl_80097A34:
/* 80097A34 00094614  2C 03 00 00 */	cmpwi r3, 0
/* 80097A38 00094618  41 82 00 0C */	beq lbl_80097A44
/* 80097A3C 0009461C  38 00 00 B7 */	li r0, 0xb7
/* 80097A40 00094620  48 00 00 08 */	b lbl_80097A48
lbl_80097A44:
/* 80097A44 00094624  38 00 00 BF */	li r0, 0xbf
lbl_80097A48:
/* 80097A48 00094628  C0 22 8C 18 */	lfs f1, ftCo_804D85F8
/* 80097A4C 0009462C  3C A0 00 02 */	lis r5, 0x00018000@ha
/* 80097A50 00094630  C0 42 8C 30 */	lfs f2, ftCo_804D8610
/* 80097A54 00094634  7C 04 03 78 */	mr r4, r0
/* 80097A58 00094638  FC 60 08 90 */	fmr f3, f1
/* 80097A5C 0009463C  38 7E 00 00 */	addi r3, r30, 0
/* 80097A60 00094640  38 A5 80 00 */	addi r5, r5, 0x00018000@l
/* 80097A64 00094644  38 C0 00 00 */	li r6, 0
/* 80097A68 00094648  4B FD 19 45 */	bl Fighter_ChangeMotionState
/* 80097A6C 0009464C  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80097A70 00094650  C0 1D 08 44 */	lfs f0, 0x844(r29)
/* 80097A74 00094654  C0 5D 08 48 */	lfs f2, 0x848(r29)
/* 80097A78 00094658  FC 20 00 50 */	fneg f1, f0
/* 80097A7C 0009465C  4B F8 B1 B5 */	bl atan2f
/* 80097A80 00094660  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 80097A84 00094664  38 7E 00 00 */	addi r3, r30, 0
/* 80097A88 00094668  39 01 00 28 */	addi r8, r1, 0x28
/* 80097A8C 0009466C  4C C6 31 82 */	crclr 6
/* 80097A90 00094670  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80097A94 00094674  81 3E 00 2C */	lwz r9, 0x2c(r30)
/* 80097A98 00094678  38 A0 00 04 */	li r5, 4
/* 80097A9C 0009467C  80 E4 00 00 */	lwz r7, 0(r4)
/* 80097AA0 00094680  38 C0 04 06 */	li r6, 0x406
/* 80097AA4 00094684  38 89 06 0C */	addi r4, r9, 0x60c
/* 80097AA8 00094688  4B FC FC 49 */	bl efAsync_Spawn
/* 80097AAC 0009468C  7F C3 F3 78 */	mr r3, r30
/* 80097AB0 00094690  4B FF FB F5 */	bl ftCo_800976A4
/* 80097AB4 00094694  38 00 00 FF */	li r0, 0xff
/* 80097AB8 00094698  98 1F 06 7C */	stb r0, 0x67c(r31)
/* 80097ABC 0009469C  38 7F 00 00 */	addi r3, r31, 0
/* 80097AC0 000946A0  38 80 01 FF */	li r4, 0x1ff
/* 80097AC4 000946A4  98 1F 06 7D */	stb r0, 0x67d(r31)
/* 80097AC8 000946A8  4B FE 68 2D */	bl ftCommon_8007E2F4
/* 80097ACC 000946AC  7F E3 FB 78 */	mr r3, r31
/* 80097AD0 000946B0  4B FE 52 19 */	bl ftCommon_8007CCE8
/* 80097AD4 000946B4  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80097AD8 000946B8  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80097ADC 000946BC  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80097AE0 000946C0  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80097AE4 000946C4  83 81 00 30 */	lwz r28, 0x30(r1)
/* 80097AE8 000946C8  38 21 00 40 */	addi r1, r1, 0x40
/* 80097AEC 000946CC  7C 08 03 A6 */	mtlr r0
/* 80097AF0 000946D0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_8009794C(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    {
        bool b = ftCo_80097570(gobj);
        if (fp->x2226_b1) {
            b = !b;
        }
        Fighter_ChangeMotionState(
            gobj, b ? ftCo_MS_DownBoundU : ftCo_MS_DownBoundD,
            Ft_MF_SkipNametagVis | Ft_MF_KeepColAnimPartHitStatus, 0, 1, 0,
            NULL);
        ftCo_800978D4(gobj);
        ftCo_800976A4(gobj);
        fp->x67C = 255;
        fp->x67D = 255;
        ftCommon_8007E2F4(fp, 511);
        ftCommon_8007CCE8(fp);
    }
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80097AF4(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80097AF4 000946D4  7C 08 02 A6 */	mflr r0
/* 80097AF8 000946D8  38 80 00 04 */	li r4, 4
/* 80097AFC 000946DC  90 01 00 04 */	stw r0, 4(r1)
/* 80097B00 000946E0  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 80097B04 000946E4  DB E1 00 60 */	stfd f31, 0x60(r1)
/* 80097B08 000946E8  93 E1 00 5C */	stw r31, 0x5c(r1)
/* 80097B0C 000946EC  93 C1 00 58 */	stw r30, 0x58(r1)
/* 80097B10 000946F0  7C 7E 1B 78 */	mr r30, r3
/* 80097B14 000946F4  93 A1 00 54 */	stw r29, 0x54(r1)
/* 80097B18 000946F8  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80097B1C 000946FC  38 7D 00 00 */	addi r3, r29, 0
/* 80097B20 00094700  4B FD D4 ED */	bl ftParts_8007500C
/* 80097B24 00094704  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80097B28 00094708  54 60 20 36 */	slwi r0, r3, 4
/* 80097B2C 0009470C  7F E4 00 2E */	lwzx r31, r4, r0
/* 80097B30 00094710  28 1F 00 00 */	cmplwi r31, 0
/* 80097B34 00094714  41 82 00 44 */	beq lbl_80097B78
/* 80097B38 00094718  40 82 00 14 */	bne lbl_80097B4C
/* 80097B3C 0009471C  38 6D 84 78 */	addi r3, r13, ftCo_804D3B18
/* 80097B40 00094720  38 80 02 34 */	li r4, 0x234
/* 80097B44 00094724  38 AD 84 80 */	addi r5, r13, ftCo_804D3B20
/* 80097B48 00094728  48 2F 06 D9 */	bl __assert
lbl_80097B4C:
/* 80097B4C 0009472C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80097B50 00094730  38 60 00 00 */	li r3, 0
/* 80097B54 00094734  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80097B58 00094738  40 82 00 10 */	bne lbl_80097B68
/* 80097B5C 0009473C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80097B60 00094740  41 82 00 08 */	beq lbl_80097B68
/* 80097B64 00094744  38 60 00 01 */	li r3, 1
lbl_80097B68:
/* 80097B68 00094748  2C 03 00 00 */	cmpwi r3, 0
/* 80097B6C 0009474C  41 82 00 0C */	beq lbl_80097B78
/* 80097B70 00094750  7F E3 FB 78 */	mr r3, r31
/* 80097B74 00094754  48 2D B5 05 */	bl HSD_JObjSetupMatrixSub
lbl_80097B78:
/* 80097B78 00094758  88 1D 22 26 */	lbz r0, 0x2226(r29)
/* 80097B7C 0009475C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80097B80 00094760  41 82 00 10 */	beq lbl_80097B90
/* 80097B84 00094764  C3 FF 00 4C */	lfs f31, 0x4c(r31)
/* 80097B88 00094768  C0 3F 00 5C */	lfs f1, 0x5c(r31)
/* 80097B8C 0009476C  48 00 00 0C */	b lbl_80097B98
lbl_80097B90:
/* 80097B90 00094770  C3 FF 00 48 */	lfs f31, 0x48(r31)
/* 80097B94 00094774  C0 3F 00 58 */	lfs f1, 0x58(r31)
lbl_80097B98:
/* 80097B98 00094778  C0 02 8C 18 */	lfs f0, ftCo_804D85F8
/* 80097B9C 0009477C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80097BA0 00094780  40 80 00 08 */	bge lbl_80097BA8
/* 80097BA4 00094784  FC 20 08 50 */	fneg f1, f1
lbl_80097BA8:
/* 80097BA8 00094788  C0 02 8C 18 */	lfs f0, ftCo_804D85F8
/* 80097BAC 0009478C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80097BB0 00094790  40 80 00 0C */	bge lbl_80097BBC
/* 80097BB4 00094794  FC 00 F8 50 */	fneg f0, f31
/* 80097BB8 00094798  48 00 00 08 */	b lbl_80097BC0
lbl_80097BBC:
/* 80097BBC 0009479C  FC 00 F8 90 */	fmr f0, f31
lbl_80097BC0:
/* 80097BC0 000947A0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80097BC4 000947A4  40 80 00 D8 */	bge lbl_80097C9C
/* 80097BC8 000947A8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80097BCC 000947AC  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 80097BD0 000947B0  2C 00 00 01 */	cmpwi r0, 1
/* 80097BD4 000947B4  40 82 00 0C */	bne lbl_80097BE0
/* 80097BD8 000947B8  7F E3 FB 78 */	mr r3, r31
/* 80097BDC 000947BC  4B FE 5C 21 */	bl ftCommon_8007D7FC
lbl_80097BE0:
/* 80097BE0 000947C0  7F C3 F3 78 */	mr r3, r30
/* 80097BE4 000947C4  4B FF F9 8D */	bl ftCo_80097570
/* 80097BE8 000947C8  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 80097BEC 000947CC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80097BF0 000947D0  41 82 00 0C */	beq lbl_80097BFC
/* 80097BF4 000947D4  7C 60 00 34 */	cntlzw r0, r3
/* 80097BF8 000947D8  54 03 D9 7E */	srwi r3, r0, 5
lbl_80097BFC:
/* 80097BFC 000947DC  2C 03 00 00 */	cmpwi r3, 0
/* 80097C00 000947E0  41 82 00 0C */	beq lbl_80097C0C
/* 80097C04 000947E4  38 80 00 B7 */	li r4, 0xb7
/* 80097C08 000947E8  48 00 00 08 */	b lbl_80097C10
lbl_80097C0C:
/* 80097C0C 000947EC  38 80 00 BF */	li r4, 0xbf
lbl_80097C10:
/* 80097C10 000947F0  C0 22 8C 18 */	lfs f1, ftCo_804D85F8
/* 80097C14 000947F4  3C A0 00 02 */	lis r5, 0x00018000@ha
/* 80097C18 000947F8  C0 42 8C 30 */	lfs f2, ftCo_804D8610
/* 80097C1C 000947FC  38 7E 00 00 */	addi r3, r30, 0
/* 80097C20 00094800  FC 60 08 90 */	fmr f3, f1
/* 80097C24 00094804  38 A5 80 00 */	addi r5, r5, 0x00018000@l
/* 80097C28 00094808  38 C0 00 00 */	li r6, 0
/* 80097C2C 0009480C  4B FD 17 81 */	bl Fighter_ChangeMotionState
/* 80097C30 00094810  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80097C34 00094814  C0 1D 08 44 */	lfs f0, 0x844(r29)
/* 80097C38 00094818  C0 5D 08 48 */	lfs f2, 0x848(r29)
/* 80097C3C 0009481C  FC 20 00 50 */	fneg f1, f0
/* 80097C40 00094820  4B F8 AF F1 */	bl atan2f
/* 80097C44 00094824  D0 21 00 44 */	stfs f1, 0x44(r1)
/* 80097C48 00094828  38 7E 00 00 */	addi r3, r30, 0
/* 80097C4C 0009482C  39 01 00 44 */	addi r8, r1, 0x44
/* 80097C50 00094830  4C C6 31 82 */	crclr 6
/* 80097C54 00094834  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80097C58 00094838  81 3E 00 2C */	lwz r9, 0x2c(r30)
/* 80097C5C 0009483C  38 A0 00 04 */	li r5, 4
/* 80097C60 00094840  80 E4 00 00 */	lwz r7, 0(r4)
/* 80097C64 00094844  38 C0 04 06 */	li r6, 0x406
/* 80097C68 00094848  38 89 06 0C */	addi r4, r9, 0x60c
/* 80097C6C 0009484C  4B FC FA 85 */	bl efAsync_Spawn
/* 80097C70 00094850  7F C3 F3 78 */	mr r3, r30
/* 80097C74 00094854  4B FF FA 31 */	bl ftCo_800976A4
/* 80097C78 00094858  38 00 00 FF */	li r0, 0xff
/* 80097C7C 0009485C  98 1F 06 7C */	stb r0, 0x67c(r31)
/* 80097C80 00094860  38 7F 00 00 */	addi r3, r31, 0
/* 80097C84 00094864  38 80 01 FF */	li r4, 0x1ff
/* 80097C88 00094868  98 1F 06 7D */	stb r0, 0x67d(r31)
/* 80097C8C 0009486C  4B FE 66 69 */	bl ftCommon_8007E2F4
/* 80097C90 00094870  7F E3 FB 78 */	mr r3, r31
/* 80097C94 00094874  4B FE 50 55 */	bl ftCommon_8007CCE8
/* 80097C98 00094878  48 00 00 88 */	b lbl_80097D20
lbl_80097C9C:
/* 80097C9C 0009487C  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80097CA0 00094880  C0 1F 08 44 */	lfs f0, 0x844(r31)
/* 80097CA4 00094884  C0 5F 08 48 */	lfs f2, 0x848(r31)
/* 80097CA8 00094888  FC 20 00 50 */	fneg f1, f0
/* 80097CAC 0009488C  4B F8 AF 85 */	bl atan2f
/* 80097CB0 00094890  D0 21 00 48 */	stfs f1, 0x48(r1)
/* 80097CB4 00094894  38 7E 00 00 */	addi r3, r30, 0
/* 80097CB8 00094898  39 01 00 48 */	addi r8, r1, 0x48
/* 80097CBC 0009489C  4C C6 31 82 */	crclr 6
/* 80097CC0 000948A0  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80097CC4 000948A4  81 3E 00 2C */	lwz r9, 0x2c(r30)
/* 80097CC8 000948A8  38 A0 00 04 */	li r5, 4
/* 80097CCC 000948AC  80 E4 00 00 */	lwz r7, 0(r4)
/* 80097CD0 000948B0  38 C0 04 06 */	li r6, 0x406
/* 80097CD4 000948B4  38 89 06 0C */	addi r4, r9, 0x60c
/* 80097CD8 000948B8  4B FC FA 19 */	bl efAsync_Spawn
/* 80097CDC 000948BC  7F C3 F3 78 */	mr r3, r30
/* 80097CE0 000948C0  4B FF F9 C5 */	bl ftCo_800976A4
/* 80097CE4 000948C4  38 60 00 04 */	li r3, 4
/* 80097CE8 000948C8  38 9D 00 B0 */	addi r4, r29, 0xb0
/* 80097CEC 000948CC  4B F9 91 59 */	bl Camera_80030E44
/* 80097CF0 000948D0  C0 3D 00 2C */	lfs f1, 0x2c(r29)
/* 80097CF4 000948D4  C0 02 8C 18 */	lfs f0, ftCo_804D85F8
/* 80097CF8 000948D8  EC 21 07 F2 */	fmuls f1, f1, f31
/* 80097CFC 000948DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80097D00 000948E0  40 81 00 10 */	ble lbl_80097D10
/* 80097D04 000948E4  7F C3 F3 78 */	mr r3, r30
/* 80097D08 000948E8  4B FF 25 B5 */	bl ft_8008A2BC
/* 80097D0C 000948EC  48 00 00 0C */	b lbl_80097D18
lbl_80097D10:
/* 80097D10 000948F0  7F C3 F3 78 */	mr r3, r30
/* 80097D14 000948F4  48 0B 7E 91 */	bl ftSb_Init_8014FBA4
lbl_80097D18:
/* 80097D18 000948F8  7F A3 EB 78 */	mr r3, r29
/* 80097D1C 000948FC  4B FE 4F CD */	bl ftCommon_8007CCE8
lbl_80097D20:
/* 80097D20 00094900  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 80097D24 00094904  CB E1 00 60 */	lfd f31, 0x60(r1)
/* 80097D28 00094908  83 E1 00 5C */	lwz r31, 0x5c(r1)
/* 80097D2C 0009490C  83 C1 00 58 */	lwz r30, 0x58(r1)
/* 80097D30 00094910  83 A1 00 54 */	lwz r29, 0x54(r1)
/* 80097D34 00094914  38 21 00 68 */	addi r1, r1, 0x68
/* 80097D38 00094918  7C 08 03 A6 */	mtlr r0
/* 80097D3C 0009491C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80097AF4(ftCo_GObj* gobj)
{
    // ftCo_80097570
    ftCo_Fighter* fp = gobj->user_data;
    HSD_JObj* jobj = fp->parts[ftParts_8007500C(fp, FtPart_HipN)].joint;
    float rot0, rot1;
    HSD_JObjSetupMatrix(jobj);
    if (fp->x2226_b0) {
        rot0 = jobj->mtx[0][2];
        rot1 = jobj->mtx[1][2];
    } else {
        rot0 = jobj->mtx[0][1];
        rot1 = jobj->mtx[1][1];
    }
    if (ABS(rot0) < ABS(rot1)) {
        ftCo_8009794C(gobj);
    } else {
        // ftCo_800978D4
        ftCo_Fighter* fp = gobj->user_data;
        float param = atan2f(-fp->self_vel.y, fp->self_vel.x);
        HSD_JObj* jobj = fp->parts[FtPart_TopN].joint;
        {
            ftCo_Fighter* fp = gobj->user_data;
            efAsync_Spawn(gobj, &fp->x60C, 4, 1030, jobj, &param);
            ftCo_800976A4(gobj);
        }
        Camera_80030E44(4, &fp->cur_pos);
        if (fp->facing_dir * rot0 > 0) {
            ft_8008A2BC(gobj);
        } else {
            ftSb_Init_8014FBA4(gobj);
        }
        ftCommon_8007CCE8(fp);
    }
}
#endif

#define SOLUTION 1
void ftCo_80097D40(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
#if SOLUTION == 0
    ftCo_80097D88(gobj);
#else
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    if (fp->x2228_b2) {
        ftCo_80097AF4(gobj);
    } else {
        ftCo_8009794C(gobj);
    }
#endif
    M2C_FIELD(fp, s8*, 0x2344) = 0;
}
#undef SOLUTION

void ftCo_80097D88(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->x2228_b2) {
        ftCo_80097AF4(gobj);
    } else {
        ftCo_8009794C(gobj);
    }
}

void ftCo_DownBound_Anim(ftCo_GObj* gobj)
{
    RETURN_IF(ftAnim_IsFramesRemaining(gobj));
    RETURN_IF(ftCo_80098400(gobj));
    RETURN_IF(ftCo_Down_CheckInput(gobj));
    ftCo_80097E8C(gobj);
}

void ftCo_DownBound_IASA(ftCo_GObj* gobj) {}

void ftCo_DownBound_Phys(ftCo_GObj* arg0)
{
    ft_80084F3C(arg0);
}

void ftCo_DownBound_Coll(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    if (ft_80082708(gobj) == GA_Ground) {
        ftCo_800CC730(gobj);
    } else {
        RETURN_IF(ftCo_800C7CA0(gobj));
    }
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80097E8C(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80097E8C 00094A6C  7C 08 02 A6 */	mflr r0
/* 80097E90 00094A70  90 01 00 04 */	stw r0, 4(r1)
/* 80097E94 00094A74  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80097E98 00094A78  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80097E9C 00094A7C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80097EA0 00094A80  7C 7E 1B 78 */	mr r30, r3
/* 80097EA4 00094A84  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80097EA8 00094A88  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 80097EAC 00094A8C  3B E3 00 00 */	addi r31, r3, 0
/* 80097EB0 00094A90  2C 00 00 01 */	cmpwi r0, 1
/* 80097EB4 00094A94  40 82 00 0C */	bne lbl_80097EC0
/* 80097EB8 00094A98  7F E3 FB 78 */	mr r3, r31
/* 80097EBC 00094A9C  4B FE 59 41 */	bl ftCommon_8007D7FC
lbl_80097EC0:
/* 80097EC0 00094AA0  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 80097EC4 00094AA4  2C 00 00 B7 */	cmpwi r0, 0xb7
/* 80097EC8 00094AA8  41 82 00 0C */	beq lbl_80097ED4
/* 80097ECC 00094AAC  2C 00 00 BE */	cmpwi r0, 0xbe
/* 80097ED0 00094AB0  40 82 00 0C */	bne lbl_80097EDC
lbl_80097ED4:
/* 80097ED4 00094AB4  38 80 00 B8 */	li r4, 0xb8
/* 80097ED8 00094AB8  48 00 00 08 */	b lbl_80097EE0
lbl_80097EDC:
/* 80097EDC 00094ABC  38 80 00 C0 */	li r4, 0xc0
lbl_80097EE0:
/* 80097EE0 00094AC0  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 80097EE4 00094AC4  3C A0 00 02 */	lis r5, 0x00018090@ha
/* 80097EE8 00094AC8  38 7E 00 00 */	addi r3, r30, 0
/* 80097EEC 00094ACC  C0 06 04 24 */	lfs f0, 0x424(r6)
/* 80097EF0 00094AD0  38 A5 80 90 */	addi r5, r5, 0x00018090@l
/* 80097EF4 00094AD4  38 C0 00 00 */	li r6, 0
/* 80097EF8 00094AD8  D0 1F 23 40 */	stfs f0, 0x2340(r31)
/* 80097EFC 00094ADC  C0 22 8C 18 */	lfs f1, ftCo_804D85F8
/* 80097F00 00094AE0  C0 42 8C 30 */	lfs f2, ftCo_804D8610
/* 80097F04 00094AE4  FC 60 08 90 */	fmr f3, f1
/* 80097F08 00094AE8  4B FD 14 A5 */	bl Fighter_ChangeMotionState
/* 80097F0C 00094AEC  7F C3 F3 78 */	mr r3, r30
/* 80097F10 00094AF0  4B FD 6C 95 */	bl ftAnim_8006EBA4
/* 80097F14 00094AF4  38 7F 00 00 */	addi r3, r31, 0
/* 80097F18 00094AF8  38 80 00 01 */	li r4, 1
/* 80097F1C 00094AFC  4B FE 63 D9 */	bl ftCommon_8007E2F4
/* 80097F20 00094B00  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80097F24 00094B04  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80097F28 00094B08  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80097F2C 00094B0C  38 21 00 18 */	addi r1, r1, 0x18
/* 80097F30 00094B10  7C 08 03 A6 */	mtlr r0
/* 80097F34 00094B14  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80097E8C(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007D7FC(fp);
    }
    {
        FtMotionId msid;
        if (fp->motion_id == ftCo_MS_DownBoundU ||
            fp->motion_id == ftCo_MS_DownSpotU)
        {
            msid = ftCo_MS_DownWaitU;
        } else {
            msid = ftCo_MS_DownWaitD;
        }
        fp->mv.co.downwait.x0 = p_ftCommonData->x424;
        Fighter_ChangeMotionState(gobj, msid,
                                  Ft_MF_SkipModel | Ft_MF_SkipMatAnim |
                                      Ft_MF_SkipNametagVis |
                                      Ft_MF_KeepColAnimPartHitStatus,
                                  0, 1, 0, NULL);
    }
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, true);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80097F38(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80097F38 00094B18  7C 08 02 A6 */	mflr r0
/* 80097F3C 00094B1C  90 01 00 04 */	stw r0, 4(r1)
/* 80097F40 00094B20  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80097F44 00094B24  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80097F48 00094B28  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80097F4C 00094B2C  7C 7E 1B 78 */	mr r30, r3
/* 80097F50 00094B30  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80097F54 00094B34  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80097F58 00094B38  3B E3 00 00 */	addi r31, r3, 0
/* 80097F5C 00094B3C  2C 00 00 B9 */	cmpwi r0, 0xb9
/* 80097F60 00094B40  40 82 00 0C */	bne lbl_80097F6C
/* 80097F64 00094B44  38 00 00 B8 */	li r0, 0xb8
/* 80097F68 00094B48  48 00 00 08 */	b lbl_80097F70
lbl_80097F6C:
/* 80097F6C 00094B4C  38 00 00 C0 */	li r0, 0xc0
lbl_80097F70:
/* 80097F70 00094B50  C0 22 8C 18 */	lfs f1, ftCo_804D85F8
/* 80097F74 00094B54  3C A0 00 02 */	lis r5, 0x00018090@ha
/* 80097F78 00094B58  C0 42 8C 30 */	lfs f2, ftCo_804D8610
/* 80097F7C 00094B5C  7C 04 03 78 */	mr r4, r0
/* 80097F80 00094B60  FC 60 08 90 */	fmr f3, f1
/* 80097F84 00094B64  38 7E 00 00 */	addi r3, r30, 0
/* 80097F88 00094B68  38 A5 80 90 */	addi r5, r5, 0x00018090@l
/* 80097F8C 00094B6C  38 C0 00 00 */	li r6, 0
/* 80097F90 00094B70  4B FD 14 1D */	bl Fighter_ChangeMotionState
/* 80097F94 00094B74  7F C3 F3 78 */	mr r3, r30
/* 80097F98 00094B78  4B FD 6C 0D */	bl ftAnim_8006EBA4
/* 80097F9C 00094B7C  38 7F 00 00 */	addi r3, r31, 0
/* 80097FA0 00094B80  38 80 00 01 */	li r4, 1
/* 80097FA4 00094B84  4B FE 63 51 */	bl ftCommon_8007E2F4
/* 80097FA8 00094B88  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80097FAC 00094B8C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80097FB0 00094B90  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80097FB4 00094B94  38 21 00 18 */	addi r1, r1, 0x18
/* 80097FB8 00094B98  7C 08 03 A6 */	mtlr r0
/* 80097FBC 00094B9C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80097F38(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(
        gobj,
        fp->motion_id == ftCo_MS_DownDamageU ? ftCo_MS_DownWaitU
                                             : ftCo_MS_DownWaitD,
        Ft_MF_SkipModel | Ft_MF_SkipMatAnim | Ft_MF_SkipNametagVis |
            Ft_MF_KeepColAnimPartHitStatus,
        0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 1);
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_DownWait_Anim(ftCo_GObj*)
{
    // clang-format off
    nofralloc
/* 80097FC0 00094BA0  7C 08 02 A6 */	mflr r0
/* 80097FC4 00094BA4  90 01 00 04 */	stw r0, 4(r1)
/* 80097FC8 00094BA8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80097FCC 00094BAC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80097FD0 00094BB0  88 04 22 24 */	lbz r0, 0x2224(r4)
/* 80097FD4 00094BB4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80097FD8 00094BB8  40 82 00 14 */	bne lbl_80097FEC
/* 80097FDC 00094BBC  C0 24 23 40 */	lfs f1, 0x2340(r4)
/* 80097FE0 00094BC0  C0 02 8C 30 */	lfs f0, ftCo_804D8610
/* 80097FE4 00094BC4  EC 01 00 28 */	fsubs f0, f1, f0
/* 80097FE8 00094BC8  D0 04 23 40 */	stfs f0, 0x2340(r4)
lbl_80097FEC:
/* 80097FEC 00094BCC  C0 24 23 40 */	lfs f1, 0x2340(r4)
/* 80097FF0 00094BD0  C0 02 8C 18 */	lfs f0, ftCo_804D85F8
/* 80097FF4 00094BD4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80097FF8 00094BD8  4C 40 13 82 */	cror 2, 0, 2
/* 80097FFC 00094BDC  40 82 00 20 */	bne lbl_8009801C
/* 80098000 00094BE0  80 04 00 10 */	lwz r0, 0x10(r4)
/* 80098004 00094BE4  2C 00 00 B8 */	cmpwi r0, 0xb8
/* 80098008 00094BE8  40 82 00 0C */	bne lbl_80098014
/* 8009800C 00094BEC  38 80 00 BA */	li r4, 0xba
/* 80098010 00094BF0  48 00 00 08 */	b lbl_80098018
lbl_80098014:
/* 80098014 00094BF4  38 80 00 C2 */	li r4, 0xc2
lbl_80098018:
/* 80098018 00094BF8  48 00 01 49 */	bl ftCo_80098160
lbl_8009801C:
/* 8009801C 00094BFC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80098020 00094C00  38 21 00 08 */	addi r1, r1, 8
/* 80098024 00094C04  7C 08 03 A6 */	mtlr r0
/* 80098028 00094C08  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_DownWait_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!fp->x2224_b2) {
        fp->mv.co.downwait.x0 -= 1;
    }
    if (fp->mv.co.downwait.x0 <= 0) {
        ftCo_80098160(gobj, fp->motion_id == ftCo_MS_DownWaitU
                                ? ftCo_MS_DownStandU
                                : ftCo_MS_DownStandD);
    }
}
#endif

void ftCo_DownWait_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(ftCo_800984D4(gobj));
    RETURN_IF(ftCo_Down_CheckInput(gobj));
    RETURN_IF(ftCo_800980BC(gobj));
}

void ftCo_DownWait_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DownWait_Coll(ftCo_GObj* gobj)
{
    ft_80083F88(gobj);
}
