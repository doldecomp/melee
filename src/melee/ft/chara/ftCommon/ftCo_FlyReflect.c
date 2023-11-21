#include "ftCommon/forward.h"

#include "ftCo_FlyReflect.h"

#include "ftCo_Damage.h"
#include "ftCo_DownBound.h"
#include "ftCo_PassiveCeil.h"
#include "ftCo_PassiveWall.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0C31.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftKirby/ftKb_Init.h"
#include "lb/lbvector.h"

#include <math.h>
#include <placeholder.h>

/* literal */ extern float const ftCo_804D8C40;  // = 0
/* literal */ extern float const ftCo_804D8C44;  // = -1
/* literal */ extern float const ftCo_804D8C48;  // = +1
/* literal */ extern double const ftCo_804D8C50; // = 0.5
/* literal */ extern double const ftCo_804D8C58; // = 3

#ifdef WIP
#pragma force_active on
#endif

bool ftCo_800C15F4(ftCo_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    float threshold = p_ftCommonData->x1B0;
    float kb_vel_x = fp->x8c_kb_vel.x;
    if (kb_vel_x < -threshold && coll->env_flags & MPCOLL_FLAGS_B11 &&
        fp->mv.co.damage.x19 != ftCo_Surface_LeftWall)
    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[8] = { 0 };
#endif
        vec.x = coll->xA4_ecbCurrCorrect.left.x;
        vec.y = coll->xA4_ecbCurrCorrect.left.y;
        vec.z = ftCo_804D8C40;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        {
            Vec3* normal = &coll->left_wall.normal;
            ftCo_800C18A8(gobj, ftCo_MS_FlyReflectWall, normal, &vec);
        }
        fp->mv.co.damage.x19 = ftCo_Surface_LeftWall;
        return true;
    }
    if (kb_vel_x > threshold && coll->env_flags & MPCOLL_FLAGS_B05 &&
        fp->mv.co.damage.x19 != ftCo_Surface_RightWall)
    {
        vec.x = coll->xA4_ecbCurrCorrect.right.x;
        vec.y = coll->xA4_ecbCurrCorrect.right.y;
        vec.z = ftCo_804D8C40;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        {
            Vec3* normal = &coll->right_wall.normal;
            ftCo_800C18A8(gobj, ftCo_MS_FlyReflectWall, normal, &vec);
        }
        fp->mv.co.damage.x19 = ftCo_Surface_RightWall;
        return true;
    }
    return false;
}

bool ftCo_800C1718(ftCo_GObj* gobj)
{
    Vec3 vec;
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if (fp->x8c_kb_vel.y > p_ftCommonData->x1B0 &&
        coll->env_flags & MPCOLL_FLAGS_B14 &&
        fp->mv.co.damage.x19 != ftCo_Surface_Ceiling)
    {
        vec.x = ftCo_804D8C40;
        vec.y = coll->xA4_ecbCurrCorrect.top.y;
        vec.z = ftCo_804D8C40;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        {
            Vec3* normal = &coll->ceiling.normal;
            ftCo_800C18A8(gobj, ftCo_MS_FlyReflectCeil, normal, &vec);
        }
        fp->mv.co.damage.x19 = ftCo_Surface_Ceiling;
        return true;
    }
    return false;
}

ASM bool ftCo_800C17CC(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    if (ftCo_800C15F4(gobj)) {
        return true;
    }
    if (ftCo_800C1718(gobj)) {
        return true;
    }
    return false;
}

#else /* clang-format off */
{ nofralloc
/* 800C17CC 000BE3AC  7C 08 02 A6 */	mflr r0
/* 800C17D0 000BE3B0  90 01 00 04 */	stw r0, 4(r1)
/* 800C17D4 000BE3B4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C17D8 000BE3B8  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800C17DC 000BE3BC  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800C17E0 000BE3C0  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800C17E4 000BE3C4  7C 7D 1B 78 */	mr r29, r3
/* 800C17E8 000BE3C8  4B FF FE 0D */	bl ftCo_800C15F4
/* 800C17EC 000BE3CC  2C 03 00 00 */	cmpwi r3, 0
/* 800C17F0 000BE3D0  41 82 00 0C */	beq lbl_800C17FC
/* 800C17F4 000BE3D4  38 60 00 01 */	li r3, 1
/* 800C17F8 000BE3D8  48 00 00 94 */	b lbl_800C188C
lbl_800C17FC:
/* 800C17FC 000BE3DC  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 800C1800 000BE3E0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C1804 000BE3E4  C0 3E 00 90 */	lfs f1, 0x90(r30)
/* 800C1808 000BE3E8  3B FE 06 F0 */	addi r31, r30, 0x6f0
/* 800C180C 000BE3EC  C0 03 01 B0 */	lfs f0, 0x1b0(r3)
/* 800C1810 000BE3F0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C1814 000BE3F4  40 81 00 60 */	ble lbl_800C1874
/* 800C1818 000BE3F8  80 1F 01 34 */	lwz r0, 0x134(r31)
/* 800C181C 000BE3FC  54 00 04 63 */	rlwinm. r0, r0, 0, 0x11, 0x11
/* 800C1820 000BE400  41 82 00 54 */	beq lbl_800C1874
/* 800C1824 000BE404  88 1E 23 59 */	lbz r0, 0x2359(r30)
/* 800C1828 000BE408  28 00 00 03 */	cmplwi r0, 3
/* 800C182C 000BE40C  41 82 00 48 */	beq lbl_800C1874
/* 800C1830 000BE410  C0 22 92 60 */	lfs f1, ftCo_804D8C40
/* 800C1834 000BE414  38 7D 00 00 */	addi r3, r29, 0
/* 800C1838 000BE418  38 81 00 24 */	addi r4, r1, 0x24
/* 800C183C 000BE41C  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 800C1840 000BE420  C0 1F 00 A8 */	lfs f0, 0xa8(r31)
/* 800C1844 000BE424  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800C1848 000BE428  D0 21 00 2C */	stfs f1, 0x2c(r1)
/* 800C184C 000BE42C  48 03 06 D1 */	bl ftKb_SpecialN_800F1F1C
/* 800C1850 000BE430  38 BF 01 90 */	addi r5, r31, 0x190
/* 800C1854 000BE434  38 7D 00 00 */	addi r3, r29, 0
/* 800C1858 000BE438  38 C1 00 24 */	addi r6, r1, 0x24
/* 800C185C 000BE43C  38 80 00 F8 */	li r4, 0xf8
/* 800C1860 000BE440  48 00 00 49 */	bl ftCo_800C18A8
/* 800C1864 000BE444  38 00 00 03 */	li r0, 3
/* 800C1868 000BE448  98 1E 23 59 */	stb r0, 0x2359(r30)
/* 800C186C 000BE44C  38 00 00 01 */	li r0, 1
/* 800C1870 000BE450  48 00 00 08 */	b lbl_800C1878
lbl_800C1874:
/* 800C1874 000BE454  38 00 00 00 */	li r0, 0
lbl_800C1878:
/* 800C1878 000BE458  2C 00 00 00 */	cmpwi r0, 0
/* 800C187C 000BE45C  41 82 00 0C */	beq lbl_800C1888
/* 800C1880 000BE460  38 60 00 01 */	li r3, 1
/* 800C1884 000BE464  48 00 00 08 */	b lbl_800C188C
lbl_800C1888:
/* 800C1888 000BE468  38 60 00 00 */	li r3, 0
lbl_800C188C:
/* 800C188C 000BE46C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C1890 000BE470  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 800C1894 000BE474  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 800C1898 000BE478  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 800C189C 000BE47C  38 21 00 40 */	addi r1, r1, 0x40
/* 800C18A0 000BE480  7C 08 03 A6 */	mtlr r0
/* 800C18A4 000BE484  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800C18A8(ftCo_GObj* gobj, ftCommon_MotionState msid,
                       Vec3* normal, Vec3* offset)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Vec3 vec1;
    Vec3 vec0;
    float param;

    Fighter* fp = GET_FIGHTER(gobj);
    vec0.x = fp->cur_pos.x + offset->x;
    vec0.y = fp->cur_pos.y + offset->y;
    vec0.z = fp->cur_pos.z + offset->z;
    param = atan2f(-normal->x, normal->y);
    efAsync_Spawn(gobj, &fp->x60C, 5, (1 << 1) | (1 << 2) | (1 << 10), NULL,
                  &vec0, &param);
    Camera_80030E44(2, &vec0);
    vec1 = fp->self_vel;
    lbVector_Add_xy(&vec1, &fp->x8c_kb_vel);
    lbVector_Mirror(&vec1, normal);
    {
        float co_x1BC;
        co_x1BC = p_ftCommonData->x1BC;
        vec1.x *= co_x1BC;
        vec1.y *= co_x1BC;
    }
    fp->x8c_kb_vel = vec1;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = ftCo_804D8C40;
    fp->facing_dir =
        fp->x8c_kb_vel.x < ftCo_804D8C40 ? ftCo_804D8C44 : ftCo_804D8C48;
    Fighter_ChangeMotionState(
        gobj, msid,
        Ft_MF_Unk06 | Ft_MF_SkipNametagVis | Ft_MF_KeepColAnimPartHitStatus |
            Ft_MF_SkipHitStun,
        ftCo_804D8C40, ftCo_804D8C48, ftCo_804D8C40, NULL);
    if (msid == ftCo_MS_FlyReflectWall) {
        fp->cur_pos.x = -(fp->x68C_transNPos.z * -fp->facing_dir -
                          (fp->cur_pos.x + offset->x));
        ft_80081F2C(gobj);
    } else {
        fp->cur_pos.y = fp->x68C_transNPos.y + (fp->cur_pos.y + offset->y);
        ft_80082084(gobj);
    }
    fp->mv.co.damage.x18 = p_ftCommonData->x1C0;
    ftCommon_8007EBAC(fp, 7, 0);
    ftColl_8007B760(gobj, p_ftCommonData->x1B8);
    {
        float vel_x = fp->self_vel.x + fp->x8c_kb_vel.x;
        float vel_y = fp->self_vel.y + fp->x8c_kb_vel.y;
        float mag = sqrtf(SQ(vel_x) + SQ(vel_y));
        ftCo_80097630(fp, ftCo_DownBound_SfxIds, mag * fp->co_attrs.weight);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C18A8 000BE488  7C 08 02 A6 */	mflr r0
/* 800C18AC 000BE48C  90 01 00 04 */	stw r0, 4(r1)
/* 800C18B0 000BE490  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 800C18B4 000BE494  BF 61 00 54 */	stmw r27, 0x54(r1)
/* 800C18B8 000BE498  7C 7B 1B 78 */	mr r27, r3
/* 800C18BC 000BE49C  7C DE 33 78 */	mr r30, r6
/* 800C18C0 000BE4A0  7C BD 2B 78 */	mr r29, r5
/* 800C18C4 000BE4A4  7C 9C 23 78 */	mr r28, r4
/* 800C18C8 000BE4A8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C18CC 000BE4AC  C0 06 00 00 */	lfs f0, 0(r6)
/* 800C18D0 000BE4B0  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 800C18D4 000BE4B4  EC 01 00 2A */	fadds f0, f1, f0
/* 800C18D8 000BE4B8  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800C18DC 000BE4BC  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 800C18E0 000BE4C0  C0 06 00 04 */	lfs f0, 4(r6)
/* 800C18E4 000BE4C4  EC 01 00 2A */	fadds f0, f1, f0
/* 800C18E8 000BE4C8  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 800C18EC 000BE4CC  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 800C18F0 000BE4D0  C0 06 00 08 */	lfs f0, 8(r6)
/* 800C18F4 000BE4D4  EC 01 00 2A */	fadds f0, f1, f0
/* 800C18F8 000BE4D8  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800C18FC 000BE4DC  C0 05 00 00 */	lfs f0, 0(r5)
/* 800C1900 000BE4E0  C0 45 00 04 */	lfs f2, 4(r5)
/* 800C1904 000BE4E4  FC 20 00 50 */	fneg f1, f0
/* 800C1908 000BE4E8  4B F6 13 29 */	bl atan2f
/* 800C190C 000BE4EC  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 800C1910 000BE4F0  38 7B 00 00 */	addi r3, r27, 0
/* 800C1914 000BE4F4  39 01 00 2C */	addi r8, r1, 0x2c
/* 800C1918 000BE4F8  4C C6 31 82 */	crclr 6
/* 800C191C 000BE4FC  80 9B 00 2C */	lwz r4, 0x2c(r27)
/* 800C1920 000BE500  39 21 00 28 */	addi r9, r1, 0x28
/* 800C1924 000BE504  38 84 06 0C */	addi r4, r4, 0x60c
/* 800C1928 000BE508  38 A0 00 05 */	li r5, 5
/* 800C192C 000BE50C  38 C0 04 06 */	li r6, 0x406
/* 800C1930 000BE510  38 E0 00 00 */	li r7, 0
/* 800C1934 000BE514  4B FA 5D BD */	bl efAsync_Spawn
/* 800C1938 000BE518  38 60 00 02 */	li r3, 2
/* 800C193C 000BE51C  38 81 00 2C */	addi r4, r1, 0x2c
/* 800C1940 000BE520  4B F6 F5 05 */	bl Camera_80030E44
/* 800C1944 000BE524  80 BF 00 80 */	lwz r5, 0x80(r31)
/* 800C1948 000BE528  38 61 00 38 */	addi r3, r1, 0x38
/* 800C194C 000BE52C  80 1F 00 84 */	lwz r0, 0x84(r31)
/* 800C1950 000BE530  38 9F 00 8C */	addi r4, r31, 0x8c
/* 800C1954 000BE534  90 A1 00 38 */	stw r5, 0x38(r1)
/* 800C1958 000BE538  90 01 00 3C */	stw r0, 0x3c(r1)
/* 800C195C 000BE53C  80 1F 00 88 */	lwz r0, 0x88(r31)
/* 800C1960 000BE540  90 01 00 40 */	stw r0, 0x40(r1)
/* 800C1964 000BE544  4B F4 BB 3D */	bl lbVector_Add_xy
/* 800C1968 000BE548  38 61 00 38 */	addi r3, r1, 0x38
/* 800C196C 000BE54C  38 9D 00 00 */	addi r4, r29, 0
/* 800C1970 000BE550  4B F4 C2 FD */	bl lbVector_Mirror
/* 800C1974 000BE554  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C1978 000BE558  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 800C197C 000BE55C  C0 23 01 BC */	lfs f1, 0x1bc(r3)
/* 800C1980 000BE560  EC 00 00 72 */	fmuls f0, f0, f1
/* 800C1984 000BE564  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800C1988 000BE568  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 800C198C 000BE56C  EC 00 00 72 */	fmuls f0, f0, f1
/* 800C1990 000BE570  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 800C1994 000BE574  80 61 00 38 */	lwz r3, 0x38(r1)
/* 800C1998 000BE578  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800C199C 000BE57C  90 7F 00 8C */	stw r3, 0x8c(r31)
/* 800C19A0 000BE580  90 1F 00 90 */	stw r0, 0x90(r31)
/* 800C19A4 000BE584  80 01 00 40 */	lwz r0, 0x40(r1)
/* 800C19A8 000BE588  90 1F 00 94 */	stw r0, 0x94(r31)
/* 800C19AC 000BE58C  C0 22 92 60 */	lfs f1, ftCo_804D8C40
/* 800C19B0 000BE590  D0 3F 00 88 */	stfs f1, 0x88(r31)
/* 800C19B4 000BE594  D0 3F 00 84 */	stfs f1, 0x84(r31)
/* 800C19B8 000BE598  D0 3F 00 80 */	stfs f1, 0x80(r31)
/* 800C19BC 000BE59C  C0 1F 00 8C */	lfs f0, 0x8c(r31)
/* 800C19C0 000BE5A0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 800C19C4 000BE5A4  40 80 00 0C */	bge lbl_800C19D0
/* 800C19C8 000BE5A8  C0 02 92 64 */	lfs f0, ftCo_804D8C44
/* 800C19CC 000BE5AC  48 00 00 08 */	b lbl_800C19D4
lbl_800C19D0:
/* 800C19D0 000BE5B0  C0 02 92 68 */	lfs f0, ftCo_804D8C48
lbl_800C19D4:
/* 800C19D4 000BE5B4  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800C19D8 000BE5B8  3C A0 10 02 */	lis r5, 0x10018040@ha
/* 800C19DC 000BE5BC  38 7B 00 00 */	addi r3, r27, 0
/* 800C19E0 000BE5C0  C0 22 92 60 */	lfs f1, ftCo_804D8C40
/* 800C19E4 000BE5C4  7F 84 E3 78 */	mr r4, r28
/* 800C19E8 000BE5C8  C0 42 92 68 */	lfs f2, ftCo_804D8C48
/* 800C19EC 000BE5CC  38 A5 80 40 */	addi r5, r5, 0x10018040@l
/* 800C19F0 000BE5D0  FC 60 08 90 */	fmr f3, f1
/* 800C19F4 000BE5D4  38 C0 00 00 */	li r6, 0
/* 800C19F8 000BE5D8  4B FA 79 B5 */	bl Fighter_ChangeMotionState
/* 800C19FC 000BE5DC  2C 1C 00 F7 */	cmpwi r28, 0xf7
/* 800C1A00 000BE5E0  40 82 00 30 */	bne lbl_800C1A30
/* 800C1A04 000BE5E4  C0 5F 00 2C */	lfs f2, 0x2c(r31)
/* 800C1A08 000BE5E8  7F 63 DB 78 */	mr r3, r27
/* 800C1A0C 000BE5EC  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 800C1A10 000BE5F0  C0 1E 00 00 */	lfs f0, 0(r30)
/* 800C1A14 000BE5F4  FC 40 10 50 */	fneg f2, f2
/* 800C1A18 000BE5F8  C0 7F 06 94 */	lfs f3, 0x694(r31)
/* 800C1A1C 000BE5FC  EC 01 00 2A */	fadds f0, f1, f0
/* 800C1A20 000BE600  EC 03 00 BC */	fnmsubs f0, f3, f2, f0
/* 800C1A24 000BE604  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 800C1A28 000BE608  4B FC 05 05 */	bl ft_80081F2C
/* 800C1A2C 000BE60C  48 00 00 24 */	b lbl_800C1A50
lbl_800C1A30:
/* 800C1A30 000BE610  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 800C1A34 000BE614  7F 63 DB 78 */	mr r3, r27
/* 800C1A38 000BE618  C0 1E 00 04 */	lfs f0, 4(r30)
/* 800C1A3C 000BE61C  C0 5F 06 90 */	lfs f2, 0x690(r31)
/* 800C1A40 000BE620  EC 01 00 2A */	fadds f0, f1, f0
/* 800C1A44 000BE624  EC 02 00 2A */	fadds f0, f2, f0
/* 800C1A48 000BE628  D0 1F 00 B4 */	stfs f0, 0xb4(r31)
/* 800C1A4C 000BE62C  4B FC 06 39 */	bl ft_80082084
lbl_800C1A50:
/* 800C1A50 000BE630  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 800C1A54 000BE634  38 7F 00 00 */	addi r3, r31, 0
/* 800C1A58 000BE638  38 80 00 07 */	li r4, 7
/* 800C1A5C 000BE63C  C0 05 01 C0 */	lfs f0, 0x1c0(r5)
/* 800C1A60 000BE640  38 A0 00 00 */	li r5, 0
/* 800C1A64 000BE644  FC 00 00 1E */	fctiwz f0, f0
/* 800C1A68 000BE648  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 800C1A6C 000BE64C  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800C1A70 000BE650  98 1F 23 58 */	stb r0, 0x2358(r31)
/* 800C1A74 000BE654  4B FB D1 39 */	bl ftCommon_8007EBAC
/* 800C1A78 000BE658  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C1A7C 000BE65C  7F 63 DB 78 */	mr r3, r27
/* 800C1A80 000BE660  80 84 01 B8 */	lwz r4, 0x1b8(r4)
/* 800C1A84 000BE664  4B FB 9C DD */	bl ftColl_8007B760
/* 800C1A88 000BE668  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 800C1A8C 000BE66C  C0 1F 00 90 */	lfs f0, 0x90(r31)
/* 800C1A90 000BE670  C0 5F 00 80 */	lfs f2, 0x80(r31)
/* 800C1A94 000BE674  EC 61 00 2A */	fadds f3, f1, f0
/* 800C1A98 000BE678  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 800C1A9C 000BE67C  C0 02 92 60 */	lfs f0, ftCo_804D8C40
/* 800C1AA0 000BE680  EC 42 08 2A */	fadds f2, f2, f1
/* 800C1AA4 000BE684  EC 23 00 F2 */	fmuls f1, f3, f3
/* 800C1AA8 000BE688  EC 82 08 BA */	fmadds f4, f2, f2, f1
/* 800C1AAC 000BE68C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800C1AB0 000BE690  40 81 00 50 */	ble lbl_800C1B00
/* 800C1AB4 000BE694  FC 20 20 34 */	frsqrte f1, f4
/* 800C1AB8 000BE698  C8 62 92 70 */	lfd f3, ftCo_804D8C50
/* 800C1ABC 000BE69C  C8 42 92 78 */	lfd f2, ftCo_804D8C58
/* 800C1AC0 000BE6A0  FC 01 00 72 */	fmul f0, f1, f1
/* 800C1AC4 000BE6A4  FC 23 00 72 */	fmul f1, f3, f1
/* 800C1AC8 000BE6A8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800C1ACC 000BE6AC  FC 21 00 32 */	fmul f1, f1, f0
/* 800C1AD0 000BE6B0  FC 01 00 72 */	fmul f0, f1, f1
/* 800C1AD4 000BE6B4  FC 23 00 72 */	fmul f1, f3, f1
/* 800C1AD8 000BE6B8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800C1ADC 000BE6BC  FC 21 00 32 */	fmul f1, f1, f0
/* 800C1AE0 000BE6C0  FC 01 00 72 */	fmul f0, f1, f1
/* 800C1AE4 000BE6C4  FC 23 00 72 */	fmul f1, f3, f1
/* 800C1AE8 000BE6C8  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800C1AEC 000BE6CC  FC 01 00 32 */	fmul f0, f1, f0
/* 800C1AF0 000BE6D0  FC 04 00 32 */	fmul f0, f4, f0
/* 800C1AF4 000BE6D4  FC 00 00 18 */	frsp f0, f0
/* 800C1AF8 000BE6D8  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800C1AFC 000BE6DC  C0 81 00 24 */	lfs f4, 0x24(r1)
lbl_800C1B00:
/* 800C1B00 000BE6E0  C0 1F 01 98 */	lfs f0, 0x198(r31)
/* 800C1B04 000BE6E4  3C 60 80 3C */	lis r3, ftCo_DownBound_SfxIds@ha
/* 800C1B08 000BE6E8  38 83 57 00 */	addi r4, r3, ftCo_DownBound_SfxIds@l
/* 800C1B0C 000BE6EC  EC 24 00 32 */	fmuls f1, f4, f0
/* 800C1B10 000BE6F0  7F E3 FB 78 */	mr r3, r31
/* 800C1B14 000BE6F4  4B FD 5B 1D */	bl ftCo_80097630
/* 800C1B18 000BE6F8  BB 61 00 54 */	lmw r27, 0x54(r1)
/* 800C1B1C 000BE6FC  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 800C1B20 000BE700  38 21 00 68 */	addi r1, r1, 0x68
/* 800C1B24 000BE704  7C 08 03 A6 */	mtlr r0
/* 800C1B28 000BE708  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_FlyReflect_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.damage.x18 != 0) {
        --fp->mv.co.damage.x18;
    }
    ftCo_DamageFly_Anim(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 800C1B2C 000BE70C  7C 08 02 A6 */	mflr r0
/* 800C1B30 000BE710  90 01 00 04 */	stw r0, 4(r1)
/* 800C1B34 000BE714  94 21 FF F8 */	stwu r1, -8(r1)
/* 800C1B38 000BE718  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 800C1B3C 000BE71C  88 85 23 58 */	lbz r4, 0x2358(r5)
/* 800C1B40 000BE720  28 04 00 00 */	cmplwi r4, 0
/* 800C1B44 000BE724  41 82 00 0C */	beq lbl_800C1B50
/* 800C1B48 000BE728  38 04 FF FF */	addi r0, r4, -1
/* 800C1B4C 000BE72C  98 05 23 58 */	stb r0, 0x2358(r5)
lbl_800C1B50:
/* 800C1B50 000BE730  4B FC E2 49 */	bl ftCo_DamageFly_Anim
/* 800C1B54 000BE734  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800C1B58 000BE738  38 21 00 08 */	addi r1, r1, 8
/* 800C1B5C 000BE73C  7C 08 03 A6 */	mtlr r0
/* 800C1B60 000BE740  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_FlyReflect_IASA(Fighter_GObj* gobj)
{
    ftCo_DamageFly_IASA(gobj);
}

void ftCo_FlyReflect_Phys(ftCo_GObj* gobj)
{
    ft_80084DB0(gobj);
}

ASM void ftCo_FlyReflect_Coll(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id == ftCo_MS_FlyReflectWall) {
        if (ft_80081F2C(gobj)) {
            ftCo_80090184(gobj);
            return;
        }
        RETURN_IF(ftCo_800C23A0(gobj));
        RETURN_IF(ftCo_800C1718(gobj));
        if (fp->mv.co.damage.x18 == 0) {
            RETURN_IF(ftCo_800C1D38(gobj));
            RETURN_IF(ftCo_800C17CC(gobj));
        }
    } else {
        if (ft_80082084(gobj)) {
            ftCo_80090184(gobj);
            return;
        }
        RETURN_IF(ftCo_800C1D38(gobj));
        RETURN_IF(ftCo_800C15F4(gobj));
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C1BA4 000BE784  7C 08 02 A6 */	mflr r0
/* 800C1BA8 000BE788  90 01 00 04 */	stw r0, 4(r1)
/* 800C1BAC 000BE78C  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 800C1BB0 000BE790  93 E1 00 44 */	stw r31, 0x44(r1)
/* 800C1BB4 000BE794  93 C1 00 40 */	stw r30, 0x40(r1)
/* 800C1BB8 000BE798  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 800C1BBC 000BE79C  93 81 00 38 */	stw r28, 0x38(r1)
/* 800C1BC0 000BE7A0  7C 7C 1B 78 */	mr r28, r3
/* 800C1BC4 000BE7A4  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 800C1BC8 000BE7A8  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 800C1BCC 000BE7AC  2C 00 00 F7 */	cmpwi r0, 0xf7
/* 800C1BD0 000BE7B0  40 82 01 10 */	bne lbl_800C1CE0
/* 800C1BD4 000BE7B4  7F 83 E3 78 */	mr r3, r28
/* 800C1BD8 000BE7B8  4B FC 03 55 */	bl ft_80081F2C
/* 800C1BDC 000BE7BC  2C 03 00 00 */	cmpwi r3, 0
/* 800C1BE0 000BE7C0  41 82 00 10 */	beq lbl_800C1BF0
/* 800C1BE4 000BE7C4  7F 83 E3 78 */	mr r3, r28
/* 800C1BE8 000BE7C8  4B FC E5 9D */	bl ftCo_80090184
/* 800C1BEC 000BE7CC  48 00 01 2C */	b lbl_800C1D18
lbl_800C1BF0:
/* 800C1BF0 000BE7D0  7F 83 E3 78 */	mr r3, r28
/* 800C1BF4 000BE7D4  48 00 07 AD */	bl ftCo_800C23A0
/* 800C1BF8 000BE7D8  2C 03 00 00 */	cmpwi r3, 0
/* 800C1BFC 000BE7DC  40 82 01 1C */	bne lbl_800C1D18
/* 800C1C00 000BE7E0  83 DC 00 2C */	lwz r30, 0x2c(r28)
/* 800C1C04 000BE7E4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C1C08 000BE7E8  C0 3E 00 90 */	lfs f1, 0x90(r30)
/* 800C1C0C 000BE7EC  3B FE 06 F0 */	addi r31, r30, 0x6f0
/* 800C1C10 000BE7F0  C0 03 01 B0 */	lfs f0, 0x1b0(r3)
/* 800C1C14 000BE7F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C1C18 000BE7F8  40 81 00 60 */	ble lbl_800C1C78
/* 800C1C1C 000BE7FC  80 1F 01 34 */	lwz r0, 0x134(r31)
/* 800C1C20 000BE800  54 00 04 63 */	rlwinm. r0, r0, 0, 0x11, 0x11
/* 800C1C24 000BE804  41 82 00 54 */	beq lbl_800C1C78
/* 800C1C28 000BE808  88 1E 23 59 */	lbz r0, 0x2359(r30)
/* 800C1C2C 000BE80C  28 00 00 03 */	cmplwi r0, 3
/* 800C1C30 000BE810  41 82 00 48 */	beq lbl_800C1C78
/* 800C1C34 000BE814  C0 22 92 60 */	lfs f1, ftCo_804D8C40
/* 800C1C38 000BE818  38 7C 00 00 */	addi r3, r28, 0
/* 800C1C3C 000BE81C  38 81 00 28 */	addi r4, r1, 0x28
/* 800C1C40 000BE820  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 800C1C44 000BE824  C0 1F 00 A8 */	lfs f0, 0xa8(r31)
/* 800C1C48 000BE828  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800C1C4C 000BE82C  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 800C1C50 000BE830  48 03 02 CD */	bl ftKb_SpecialN_800F1F1C
/* 800C1C54 000BE834  38 BF 01 90 */	addi r5, r31, 0x190
/* 800C1C58 000BE838  38 7C 00 00 */	addi r3, r28, 0
/* 800C1C5C 000BE83C  38 C1 00 28 */	addi r6, r1, 0x28
/* 800C1C60 000BE840  38 80 00 F8 */	li r4, 0xf8
/* 800C1C64 000BE844  4B FF FC 45 */	bl ftCo_800C18A8
/* 800C1C68 000BE848  38 00 00 03 */	li r0, 3
/* 800C1C6C 000BE84C  98 1E 23 59 */	stb r0, 0x2359(r30)
/* 800C1C70 000BE850  38 00 00 01 */	li r0, 1
/* 800C1C74 000BE854  48 00 00 08 */	b lbl_800C1C7C
lbl_800C1C78:
/* 800C1C78 000BE858  38 00 00 00 */	li r0, 0
lbl_800C1C7C:
/* 800C1C7C 000BE85C  2C 00 00 00 */	cmpwi r0, 0
/* 800C1C80 000BE860  40 82 00 98 */	bne lbl_800C1D18
/* 800C1C84 000BE864  88 1D 23 58 */	lbz r0, 0x2358(r29)
/* 800C1C88 000BE868  28 00 00 00 */	cmplwi r0, 0
/* 800C1C8C 000BE86C  40 82 00 8C */	bne lbl_800C1D18
/* 800C1C90 000BE870  7F 83 E3 78 */	mr r3, r28
/* 800C1C94 000BE874  48 00 00 A5 */	bl ftCo_800C1D38
/* 800C1C98 000BE878  2C 03 00 00 */	cmpwi r3, 0
/* 800C1C9C 000BE87C  40 82 00 7C */	bne lbl_800C1D18
/* 800C1CA0 000BE880  7F 83 E3 78 */	mr r3, r28
/* 800C1CA4 000BE884  4B FF F9 51 */	bl ftCo_800C15F4
/* 800C1CA8 000BE888  2C 03 00 00 */	cmpwi r3, 0
/* 800C1CAC 000BE88C  41 82 00 0C */	beq lbl_800C1CB8
/* 800C1CB0 000BE890  38 00 00 01 */	li r0, 1
/* 800C1CB4 000BE894  48 00 00 20 */	b lbl_800C1CD4
lbl_800C1CB8:
/* 800C1CB8 000BE898  7F 83 E3 78 */	mr r3, r28
/* 800C1CBC 000BE89C  4B FF FA 5D */	bl ftCo_800C1718
/* 800C1CC0 000BE8A0  2C 03 00 00 */	cmpwi r3, 0
/* 800C1CC4 000BE8A4  41 82 00 0C */	beq lbl_800C1CD0
/* 800C1CC8 000BE8A8  38 00 00 01 */	li r0, 1
/* 800C1CCC 000BE8AC  48 00 00 08 */	b lbl_800C1CD4
lbl_800C1CD0:
/* 800C1CD0 000BE8B0  38 00 00 00 */	li r0, 0
lbl_800C1CD4:
/* 800C1CD4 000BE8B4  2C 00 00 00 */	cmpwi r0, 0
/* 800C1CD8 000BE8B8  41 82 00 40 */	beq lbl_800C1D18
/* 800C1CDC 000BE8BC  48 00 00 3C */	b lbl_800C1D18
lbl_800C1CE0:
/* 800C1CE0 000BE8C0  7F 83 E3 78 */	mr r3, r28
/* 800C1CE4 000BE8C4  4B FC 03 A1 */	bl ft_80082084
/* 800C1CE8 000BE8C8  2C 03 00 00 */	cmpwi r3, 0
/* 800C1CEC 000BE8CC  41 82 00 10 */	beq lbl_800C1CFC
/* 800C1CF0 000BE8D0  7F 83 E3 78 */	mr r3, r28
/* 800C1CF4 000BE8D4  4B FC E4 91 */	bl ftCo_80090184
/* 800C1CF8 000BE8D8  48 00 00 20 */	b lbl_800C1D18
lbl_800C1CFC:
/* 800C1CFC 000BE8DC  7F 83 E3 78 */	mr r3, r28
/* 800C1D00 000BE8E0  48 00 00 39 */	bl ftCo_800C1D38
/* 800C1D04 000BE8E4  2C 03 00 00 */	cmpwi r3, 0
/* 800C1D08 000BE8E8  40 82 00 10 */	bne lbl_800C1D18
/* 800C1D0C 000BE8EC  7F 83 E3 78 */	mr r3, r28
/* 800C1D10 000BE8F0  4B FF F8 E5 */	bl ftCo_800C15F4
/* 800C1D14 000BE8F4  2C 03 00 00 */	cmpwi r3, 0
lbl_800C1D18:
/* 800C1D18 000BE8F8  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800C1D1C 000BE8FC  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 800C1D20 000BE900  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 800C1D24 000BE904  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 800C1D28 000BE908  83 81 00 38 */	lwz r28, 0x38(r1)
/* 800C1D2C 000BE90C  38 21 00 48 */	addi r1, r1, 0x48
/* 800C1D30 000BE910  7C 08 03 A6 */	mtlr r0
/* 800C1D34 000BE914  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
