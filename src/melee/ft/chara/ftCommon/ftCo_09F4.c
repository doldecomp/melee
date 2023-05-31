#include <platform.h>

#include "ftCo_09F4.h"

#include "ft/ft_08A4.h"
#include "gr/ground.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"

#include <math.h>
#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <MSL/trigf.h>

#ifdef MWERKS_GEKKO
#ifdef WIP
#pragma force_active on
#endif
static float const ftCo_804D87B0 = 0;
static float const ftCo_804D87B4 = deg_to_rad;
static double const ftCo_804D87B8 = M_PI_2;
extern UNK_T ftCo_804D6568;
extern UNK_T ftCo_804D656C;
extern UNK_T ftCo_804D3B50;
extern char* ftCo_804D3B58;
extern char* ftCo_804D3B60;

static char ftDynamics_assert_msg_0[] =
    "fp->dynamics_num < Ft_Dynamics_NumMax";
static float ftDynamics_803C5780[] = { 0, 0.57, 0.57, 0.57, 0 };

struct {
    int zero1;
    int zero2;
    u32 flags;
    int neg1;
    f32* floats;
    int zero3;
    int zero4;
} ftDynamics_803C5794 = {
    0, 0, 0x00050000, -1, ftDynamics_803C5780, 0, 0,
};

#endif

void ftCo_8009F480(ftCo_GObj* gobj)
{
    HSD_LObjAnimAll(gobj->hsd_obj);
}

ASM UNK_RET ftCo_8009F4A4(UNK_PARAMS)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 8009F4A4 0009C084  7C 08 02 A6 */	mflr r0
/* 8009F4A8 0009C088  38 60 00 0C */	li r3, 0xc
/* 8009F4AC 0009C08C  90 01 00 04 */	stw r0, 4(r1)
/* 8009F4B0 0009C090  38 80 00 03 */	li r4, 3
/* 8009F4B4 0009C094  38 A0 00 00 */	li r5, 0
/* 8009F4B8 0009C098  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8009F4BC 0009C09C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8009F4C0 0009C0A0  93 C1 00 08 */	stw r30, 8(r1)
/* 8009F4C4 0009C0A4  48 2F 0D 2D */	bl GObj_Create
/* 8009F4C8 0009C0A8  7C 7F 1B 78 */	mr r31, r3
/* 8009F4CC 0009C0AC  48 12 54 E9 */	bl Ground_801C49B4
/* 8009F4D0 0009C0B0  4B F7 25 F5 */	bl lb_80011AC4
/* 8009F4D4 0009C0B4  7C 7E 1B 78 */	mr r30, r3
/* 8009F4D8 0009C0B8  93 CD AE C8 */	stw r30, ftCo_804D6568
/* 8009F4DC 0009C0BC  4B F6 D8 E5 */	bl lb_8000CDC0
/* 8009F4E0 0009C0C0  90 6D AE CC */	stw r3, ftCo_804D656C
/* 8009F4E4 0009C0C4  7F C3 F3 78 */	mr r3, r30
/* 8009F4E8 0009C0C8  48 12 2E 8D */	bl Ground_801C2374
/* 8009F4EC 0009C0CC  88 8D C1 AA */	lbz r4, HSD_GObj_804D784A
/* 8009F4F0 0009C0D0  38 7F 00 00 */	addi r3, r31, 0
/* 8009F4F4 0009C0D4  38 BE 00 00 */	addi r5, r30, 0
/* 8009F4F8 0009C0D8  48 2F 15 79 */	bl HSD_GObjObjet_80390A70
/* 8009F4FC 0009C0DC  3C 60 80 0A */	lis r3, ftCo_8009F54C@ha
/* 8009F500 0009C0E0  38 83 F5 4C */	addi r4, r3, ftCo_8009F54C@l
/* 8009F504 0009C0E4  38 7F 00 00 */	addi r3, r31, 0
/* 8009F508 0009C0E8  38 A0 00 04 */	li r5, 4
/* 8009F50C 0009C0EC  38 C0 00 00 */	li r6, 0
/* 8009F510 0009C0F0  48 2F 11 8D */	bl GObj_SetupGXLink
/* 8009F514 0009C0F4  7F C3 F3 78 */	mr r3, r30
/* 8009F518 0009C0F8  C0 22 8D D0 */	lfs f1, ftCo_804D87B0
/* 8009F51C 0009C0FC  48 2C 61 DD */	bl HSD_LObjReqAnimAll
/* 8009F520 0009C100  3C 60 80 0A */	lis r3, ftCo_8009F480@ha
/* 8009F524 0009C104  38 83 F4 80 */	addi r4, r3, ftCo_8009F480@l
/* 8009F528 0009C108  38 7F 00 00 */	addi r3, r31, 0
/* 8009F52C 0009C10C  38 A0 00 01 */	li r5, 1
/* 8009F530 0009C110  48 2F 08 25 */	bl HSD_GObjProc_8038FD54
/* 8009F534 0009C114  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8009F538 0009C118  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8009F53C 0009C11C  83 C1 00 08 */	lwz r30, 8(r1)
/* 8009F540 0009C120  38 21 00 10 */	addi r1, r1, 0x10
/* 8009F544 0009C124  7C 08 03 A6 */	mtlr r0
/* 8009F548 0009C128  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM UNK_RET ftCo_8009F54C(UNK_PARAMS)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 8009F54C 0009C12C  7C 08 02 A6 */	mflr r0
/* 8009F550 0009C130  90 01 00 04 */	stw r0, 4(r1)
/* 8009F554 0009C134  94 21 FF F8 */	stwu r1, -8(r1)
/* 8009F558 0009C138  80 63 00 28 */	lwz r3, 0x28(r3)
/* 8009F55C 0009C13C  48 2C 73 91 */	bl HSD_LObj_803668EC
/* 8009F560 0009C140  48 2C AD 29 */	bl HSD_CObjGetCurrent
/* 8009F564 0009C144  48 2C 69 C5 */	bl HSD_LObjSetupInit
/* 8009F568 0009C148  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8009F56C 0009C14C  38 21 00 08 */	addi r1, r1, 8
/* 8009F570 0009C150  7C 08 03 A6 */	mtlr r0
/* 8009F574 0009C154  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_8009F578(ftCo_Fighter* fp)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 8009F578 0009C158  7C 08 02 A6 */	mflr r0
/* 8009F57C 0009C15C  90 01 00 04 */	stw r0, 4(r1)
/* 8009F580 0009C160  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8009F584 0009C164  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8009F588 0009C168  3B E3 00 00 */	addi r31, r3, 0
/* 8009F58C 0009C16C  38 6D 84 B0 */	addi r3, r13, ftCo_804D3B50
/* 8009F590 0009C170  4B F7 25 35 */	bl lb_80011AC4
/* 8009F594 0009C174  90 7F 05 88 */	stw r3, 0x588(r31)
/* 8009F598 0009C178  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009F59C 0009C17C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8009F5A0 0009C180  38 21 00 18 */	addi r1, r1, 0x18
/* 8009F5A4 0009C184  7C 08 03 A6 */	mtlr r0
/* 8009F5A8 0009C188  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM UNK_RET ftCo_8009F5AC(UNK_PARAMS)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 8009F5AC 0009C18C  7C 08 02 A6 */	mflr r0
/* 8009F5B0 0009C190  90 01 00 04 */	stw r0, 4(r1)
/* 8009F5B4 0009C194  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8009F5B8 0009C198  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 8009F5BC 0009C19C  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 8009F5C0 0009C1A0  93 E1 00 44 */	stw r31, 0x44(r1)
/* 8009F5C4 0009C1A4  93 C1 00 40 */	stw r30, 0x40(r1)
/* 8009F5C8 0009C1A8  7C 7E 1B 78 */	mr r30, r3
/* 8009F5CC 0009C1AC  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 8009F5D0 0009C1B0  48 02 10 89 */	bl ftCo_800C0658
/* 8009F5D4 0009C1B4  88 03 00 7C */	lbz r0, 0x7c(r3)
/* 8009F5D8 0009C1B8  7C 7F 1B 78 */	mr r31, r3
/* 8009F5DC 0009C1BC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8009F5E0 0009C1C0  41 82 01 58 */	beq lbl_8009F738
/* 8009F5E4 0009C1C4  88 1E 22 21 */	lbz r0, 0x2221(r30)
/* 8009F5E8 0009C1C8  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8009F5EC 0009C1CC  41 82 01 1C */	beq lbl_8009F708
/* 8009F5F0 0009C1D0  80 7E 00 00 */	lwz r3, 0(r30)
/* 8009F5F4 0009C1D4  C0 22 8D D4 */	lfs f1, ftCo_804D87B4
/* 8009F5F8 0009C1D8  C0 1F 00 78 */	lfs f0, 0x78(r31)
/* 8009F5FC 0009C1DC  83 A3 00 28 */	lwz r29, 0x28(r3)
/* 8009F600 0009C1E0  EF E1 00 32 */	fmuls f31, f1, f0
/* 8009F604 0009C1E4  28 1D 00 00 */	cmplwi r29, 0
/* 8009F608 0009C1E8  40 82 00 14 */	bne lbl_8009F61C
/* 8009F60C 0009C1EC  38 6D 84 B8 */	addi r3, r13, ftCo_804D3B58
/* 8009F610 0009C1F0  38 80 02 DA */	li r4, 0x2da
/* 8009F614 0009C1F4  38 AD 84 C0 */	addi r5, r13, ftCo_804D3B60
/* 8009F618 0009C1F8  48 2E 8C 09 */	bl __assert
lbl_8009F61C:
/* 8009F61C 0009C1FC  C0 22 8D D4 */	lfs f1, ftCo_804D87B4
/* 8009F620 0009C200  FF E0 F8 50 */	fneg f31, f31
/* 8009F624 0009C204  C0 1F 00 74 */	lfs f0, 0x74(r31)
/* 8009F628 0009C208  C0 5D 00 20 */	lfs f2, 0x20(r29)
/* 8009F62C 0009C20C  EC 61 00 32 */	fmuls f3, f1, f0
/* 8009F630 0009C210  C8 02 8D D8 */	lfd f0, ftCo_804D87B8
/* 8009F634 0009C214  FC 20 F8 90 */	fmr f1, f31
/* 8009F638 0009C218  EC 43 00 B2 */	fmuls f2, f3, f2
/* 8009F63C 0009C21C  FF C2 00 24 */	fdiv f30, f2, f0
/* 8009F640 0009C220  FF C0 F0 18 */	frsp f30, f30
/* 8009F644 0009C224  48 28 6D 91 */	bl sinf
/* 8009F648 0009C228  FC 00 08 50 */	fneg f0, f1
/* 8009F64C 0009C22C  FC 20 F8 90 */	fmr f1, f31
/* 8009F650 0009C230  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 8009F654 0009C234  48 28 6B ED */	bl cosf
/* 8009F658 0009C238  D0 21 00 30 */	stfs f1, 0x30(r1)
/* 8009F65C 0009C23C  FC 20 F0 90 */	fmr f1, f30
/* 8009F660 0009C240  48 28 6D 75 */	bl sinf
/* 8009F664 0009C244  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 8009F668 0009C248  EC 00 00 72 */	fmuls f0, f0, f1
/* 8009F66C 0009C24C  FC 20 F0 90 */	fmr f1, f30
/* 8009F670 0009C250  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8009F674 0009C254  48 28 6B CD */	bl cosf
/* 8009F678 0009C258  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 8009F67C 0009C25C  38 81 00 28 */	addi r4, r1, 0x28
/* 8009F680 0009C260  EC 00 00 72 */	fmuls f0, f0, f1
/* 8009F684 0009C264  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 8009F688 0009C268  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F68C 0009C26C  48 2C 76 5D */	bl HSD_LObjSetPosition
/* 8009F690 0009C270  88 1F 00 7C */	lbz r0, 0x7c(r31)
/* 8009F694 0009C274  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8009F698 0009C278  41 82 00 40 */	beq lbl_8009F6D8
/* 8009F69C 0009C27C  3C 60 80 3C */	lis r3, ftDynamics_803C5794@ha
/* 8009F6A0 0009C280  38 63 57 94 */	addi r3, r3, ftDynamics_803C5794@l
/* 8009F6A4 0009C284  80 03 00 0C */	lwz r0, 0xc(r3)
/* 8009F6A8 0009C288  38 81 00 20 */	addi r4, r1, 0x20
/* 8009F6AC 0009C28C  90 01 00 24 */	stw r0, 0x24(r1)
/* 8009F6B0 0009C290  88 1F 00 53 */	lbz r0, 0x53(r31)
/* 8009F6B4 0009C294  98 01 00 27 */	stb r0, 0x27(r1)
/* 8009F6B8 0009C298  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8009F6BC 0009C29C  90 01 00 20 */	stw r0, 0x20(r1)
/* 8009F6C0 0009C2A0  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F6C4 0009C2A4  48 2C 75 E1 */	bl HSD_LObj_80366CA4
/* 8009F6C8 0009C2A8  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F6CC 0009C2AC  38 80 00 10 */	li r4, 0x10
/* 8009F6D0 0009C2B0  48 2C 5C E5 */	bl HSD_LObjSetFlags
/* 8009F6D4 0009C2B4  48 00 00 24 */	b lbl_8009F6F8
lbl_8009F6D8:
/* 8009F6D8 0009C2B8  80 1F 00 50 */	lwz r0, 0x50(r31)
/* 8009F6DC 0009C2BC  38 81 00 1C */	addi r4, r1, 0x1c
/* 8009F6E0 0009C2C0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8009F6E4 0009C2C4  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F6E8 0009C2C8  48 2C 75 BD */	bl HSD_LObj_80366CA4
/* 8009F6EC 0009C2CC  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F6F0 0009C2D0  38 80 00 10 */	li r4, 0x10
/* 8009F6F4 0009C2D4  48 2C 5C D9 */	bl HSD_LObjClearFlags
lbl_8009F6F8:
/* 8009F6F8 0009C2D8  88 1E 22 21 */	lbz r0, 0x2221(r30)
/* 8009F6FC 0009C2DC  38 60 00 00 */	li r3, 0
/* 8009F700 0009C2E0  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 8009F704 0009C2E4  98 1E 22 21 */	stb r0, 0x2221(r30)
lbl_8009F708:
/* 8009F708 0009C2E8  88 1F 00 7C */	lbz r0, 0x7c(r31)
/* 8009F70C 0009C2EC  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8009F710 0009C2F0  41 82 00 10 */	beq lbl_8009F720
/* 8009F714 0009C2F4  80 6D AE C8 */	lwz r3, ftCo_804D6568
/* 8009F718 0009C2F8  48 2C 71 D5 */	bl HSD_LObj_803668EC
/* 8009F71C 0009C2FC  48 00 00 0C */	b lbl_8009F728
lbl_8009F720:
/* 8009F720 0009C300  80 6D AE CC */	lwz r3, ftCo_804D656C
/* 8009F724 0009C304  48 2C 70 85 */	bl HSD_LObjSetCurrentAll
lbl_8009F728:
/* 8009F728 0009C308  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F72C 0009C30C  48 2C 6C 89 */	bl HSD_LObjAddCurrent
/* 8009F730 0009C310  48 2C AB 59 */	bl HSD_CObjGetCurrent
/* 8009F734 0009C314  48 2C 67 F5 */	bl HSD_LObjSetupInit
lbl_8009F738:
/* 8009F738 0009C318  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8009F73C 0009C31C  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 8009F740 0009C320  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 8009F744 0009C324  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 8009F748 0009C328  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 8009F74C 0009C32C  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 8009F750 0009C330  38 21 00 58 */	addi r1, r1, 0x58
/* 8009F754 0009C334  7C 08 03 A6 */	mtlr r0
/* 8009F758 0009C338  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM UNK_RET ftCo_8009F75C(UNK_PARAMS)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 8009F75C 0009C33C  7C 08 02 A6 */	mflr r0
/* 8009F760 0009C340  90 01 00 04 */	stw r0, 4(r1)
/* 8009F764 0009C344  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8009F768 0009C348  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8009F76C 0009C34C  3B E4 00 00 */	addi r31, r4, 0
/* 8009F770 0009C350  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8009F774 0009C354  3B C3 00 00 */	addi r30, r3, 0
/* 8009F778 0009C358  48 02 0E E1 */	bl ftCo_800C0658
/* 8009F77C 0009C35C  88 63 00 7C */	lbz r3, 0x7c(r3)
/* 8009F780 0009C360  54 60 D7 FF */	rlwinm. r0, r3, 0x1a, 0x1f, 0x1f
/* 8009F784 0009C364  41 82 00 5C */	beq lbl_8009F7E0
/* 8009F788 0009C368  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8009F78C 0009C36C  41 82 00 54 */	beq lbl_8009F7E0
/* 8009F790 0009C370  2C 1F 00 00 */	cmpwi r31, 0
/* 8009F794 0009C374  41 82 00 14 */	beq lbl_8009F7A8
/* 8009F798 0009C378  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F79C 0009C37C  38 80 00 10 */	li r4, 0x10
/* 8009F7A0 0009C380  48 2C 5C 15 */	bl HSD_LObjSetFlags
/* 8009F7A4 0009C384  48 00 00 10 */	b lbl_8009F7B4
lbl_8009F7A8:
/* 8009F7A8 0009C388  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F7AC 0009C38C  38 80 00 10 */	li r4, 0x10
/* 8009F7B0 0009C390  48 2C 5C 1D */	bl HSD_LObjClearFlags
lbl_8009F7B4:
/* 8009F7B4 0009C394  2C 1F 00 00 */	cmpwi r31, 0
/* 8009F7B8 0009C398  41 82 00 10 */	beq lbl_8009F7C8
/* 8009F7BC 0009C39C  80 6D AE C8 */	lwz r3, ftCo_804D6568
/* 8009F7C0 0009C3A0  48 2C 71 2D */	bl HSD_LObj_803668EC
/* 8009F7C4 0009C3A4  48 00 00 0C */	b lbl_8009F7D0
lbl_8009F7C8:
/* 8009F7C8 0009C3A8  80 6D AE CC */	lwz r3, ftCo_804D656C
/* 8009F7CC 0009C3AC  48 2C 6F DD */	bl HSD_LObjSetCurrentAll
lbl_8009F7D0:
/* 8009F7D0 0009C3B0  80 7E 05 88 */	lwz r3, 0x588(r30)
/* 8009F7D4 0009C3B4  48 2C 6B E1 */	bl HSD_LObjAddCurrent
/* 8009F7D8 0009C3B8  48 2C AA B1 */	bl HSD_CObjGetCurrent
/* 8009F7DC 0009C3BC  48 2C 67 4D */	bl HSD_LObjSetupInit
lbl_8009F7E0:
/* 8009F7E0 0009C3C0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009F7E4 0009C3C4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8009F7E8 0009C3C8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8009F7EC 0009C3CC  38 21 00 18 */	addi r1, r1, 0x18
/* 8009F7F0 0009C3D0  7C 08 03 A6 */	mtlr r0
/* 8009F7F4 0009C3D4  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM UNK_RET ftCo_8009F7F8(UNK_PARAMS)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 8009F7F8 0009C3D8  7C 08 02 A6 */	mflr r0
/* 8009F7FC 0009C3DC  90 01 00 04 */	stw r0, 4(r1)
/* 8009F800 0009C3E0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8009F804 0009C3E4  48 02 0E 55 */	bl ftCo_800C0658
/* 8009F808 0009C3E8  88 03 00 7C */	lbz r0, 0x7c(r3)
/* 8009F80C 0009C3EC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8009F810 0009C3F0  41 82 00 14 */	beq lbl_8009F824
/* 8009F814 0009C3F4  80 6D AE C8 */	lwz r3, ftCo_804D6568
/* 8009F818 0009C3F8  48 2C 70 D5 */	bl HSD_LObj_803668EC
/* 8009F81C 0009C3FC  48 2C AA 6D */	bl HSD_CObjGetCurrent
/* 8009F820 0009C400  48 2C 67 09 */	bl HSD_LObjSetupInit
lbl_8009F824:
/* 8009F824 0009C404  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8009F828 0009C408  38 21 00 08 */	addi r1, r1, 8
/* 8009F82C 0009C40C  7C 08 03 A6 */	mtlr r0
/* 8009F830 0009C410  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
