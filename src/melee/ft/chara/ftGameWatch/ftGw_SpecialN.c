#include "forward.h"
#include "ft/forward.h"

#include "ftGw_SpecialN.h"

#include "ftGw_Init.h"
#include "types.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0C88.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx/types.h>

static float setFloatOrder0(void)
{
    return 2.5f;
}

static float setFloatOrder1(void)
{
    return 6.5f;
}

static float setFloatOrder2(void)
{
    return 0.0f;
}

#ifdef MUST_MATCH

#pragma push
static asm void ftGw_SpecialN_CreateSausage(HSD_GObj* gobj)
{ // clang-format off
    nofralloc
/* 8014E4F0 0014B0D0  7C 08 02 A6 */	mflr r0
/* 8014E4F4 0014B0D4  90 01 00 04 */	stw r0, 4(r1)
/* 8014E4F8 0014B0D8  94 21 FF 98 */	stwu r1, -104(r1)
/* 8014E4FC 0014B0DC  93 E1 00 64 */	stw r31, 100(r1)
/* 8014E500 0014B0E0  93 C1 00 60 */	stw r30, 96(r1)
/* 8014E504 0014B0E4  7C 7E 1B 78 */	mr r30, r3
/* 8014E508 0014B0E8  93 A1 00 5C */	stw r29, 92(r1)
/* 8014E50C 0014B0EC  93 81 00 58 */	stw r28, 88(r1)
/* 8014E510 0014B0F0  83 E3 00 2C */	lwz r31, 44(r3)
/* 8014E514 0014B0F4  80 1F 22 00 */	lwz r0, 8704(r31)
/* 8014E518 0014B0F8  80 BF 02 D4 */	lwz r5, 724(r31)
/* 8014E51C 0014B0FC  28 00 00 00 */	cmplwi r0, 0
/* 8014E520 0014B100  41 82 01 04 */	beq lbl_8014E624
/* 8014E524 0014B104  3B 80 00 00 */	li r28, 0
/* 8014E528 0014B108  93 9F 22 00 */	stw r28, 8704(r31)
/* 8014E52C 0014B10C  3C 00 43 30 */	lis r0, 17200
/* 8014E530 0014B110  80 9F 23 44 */	lwz r4, 9028(r31)
/* 8014E534 0014B114  C8 42 A4 68 */	lfd f2, 4503601774854144.0
/* 8014E538 0014B118  6C 83 80 00 */	xoris r3, r4, 32768
/* 8014E53C 0014B11C  C0 05 00 1C */	lfs f0, 28(r5)
/* 8014E540 0014B120  90 61 00 54 */	stw r3, 84(r1)
/* 8014E544 0014B124  90 01 00 50 */	stw r0, 80(r1)
/* 8014E548 0014B128  C8 21 00 50 */	lfd f1, 80(r1)
/* 8014E54C 0014B12C  EC 21 10 28 */	fsubs f1, f1, f2
/* 8014E550 0014B130  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8014E554 0014B134  40 80 00 C8 */	bge lbl_8014E61C
/* 8014E558 0014B138  38 04 00 01 */	addi r0, r4, 1
/* 8014E55C 0014B13C  90 1F 23 44 */	stw r0, 9028(r31)
/* 8014E560 0014B140  38 7F 00 00 */	addi r3, r31, 0
/* 8014E564 0014B144  38 80 00 1F */	li r4, 31
/* 8014E568 0014B148  C0 02 A4 58 */	lfs f0, 2.5f
/* 8014E56C 0014B14C  C0 22 A4 5C */	lfs f1, 6.5f
/* 8014E570 0014B150  D0 01 00 38 */	stfs f0, 56(r1)
/* 8014E574 0014B154  C0 02 A4 60 */	lfs f0, 0.0f
/* 8014E578 0014B158  D0 21 00 3C */	stfs f1, 60(r1)
/* 8014E57C 0014B15C  D0 01 00 40 */	stfs f0, 64(r1)
/* 8014E580 0014B160  4B F2 6A 8D */	bl ftParts_8007500C
/* 8014E584 0014B164  80 BF 05 E8 */	lwz r5, 1512(r31)
/* 8014E588 0014B168  54 60 20 36 */	slwi r0, r3, 4
/* 8014E58C 0014B16C  38 81 00 38 */	addi r4, r1, 56
/* 8014E590 0014B170  7C 65 00 2E */	lwzx r3, r5, r0
/* 8014E594 0014B174  38 A1 00 44 */	addi r5, r1, 68
/* 8014E598 0014B178  4B EB CC 35 */	bl lb_8000B1CC
/* 8014E59C 0014B17C  38 60 00 00 */	li r3, 0
/* 8014E5A0 0014B180  83 BE 00 2C */	lwz r29, 44(r30)
/* 8014E5A4 0014B184  20 03 00 05 */	subfic r0, r3, 5
/* 8014E5A8 0014B188  2C 03 00 05 */	cmpwi r3, 5
/* 8014E5AC 0014B18C  7C 09 03 A6 */	mtctr r0
/* 8014E5B0 0014B190  38 81 00 1C */	addi r4, r1, 28
/* 8014E5B4 0014B194  40 80 00 30 */	bge lbl_8014E5E4
lbl_8014E5B8:
/* 8014E5B8 0014B198  80 1D 22 40 */    lwz r0, 8768(r29)
/* 8014E5BC 0014B19C  7C 03 00 00 */	cmpw r3, r0
/* 8014E5C0 0014B1A0  41 82 00 1C */	beq lbl_8014E5DC
/* 8014E5C4 0014B1A4  80 1D 22 44 */	lwz r0, 8772(r29)
/* 8014E5C8 0014B1A8  7C 03 00 00 */	cmpw r3, r0
/* 8014E5CC 0014B1AC  41 82 00 10 */	beq lbl_8014E5DC
/* 8014E5D0 0014B1B0  90 64 00 00 */	stw r3, 0(r4)
/* 8014E5D4 0014B1B4  38 84 00 04 */	addi r4, r4, 4
/* 8014E5D8 0014B1B8  3B 9C 00 01 */	addi r28, r28, 1
lbl_8014E5DC:
/* 8014E5DC 0014B1BC  38 63 00 01 */	addi r3, r3, 1
/* 8014E5E0 0014B1C0  42 00 FF D8 */	bdnz lbl_8014E5B8
lbl_8014E5E4:
/* 8014E5E4 0014B1C4  7F 83 E3 78 */	mr r3, r28
/* 8014E5E8 0014B1C8  48 23 1F 99 */	bl HSD_Randi
/* 8014E5EC 0014B1CC  54 64 10 3A */	slwi r4, r3, 2
/* 8014E5F0 0014B1D0  80 1D 22 40 */	lwz r0, 8768(r29)
/* 8014E5F4 0014B1D4  38 61 00 1C */	addi r3, r1, 28
/* 8014E5F8 0014B1D8  7C A3 20 2E */	lwzx r5, r3, r4
/* 8014E5FC 0014B1DC  38 7E 00 00 */	addi r3, r30, 0
/* 8014E600 0014B1E0  38 81 00 44 */	addi r4, r1, 68
/* 8014E604 0014B1E4  90 1D 22 44 */	stw r0, 8772(r29)
/* 8014E608 0014B1E8  7C A6 2B 78 */	mr r6, r5
/* 8014E60C 0014B1EC  90 BD 22 40 */	stw r5, 8768(r29)
/* 8014E610 0014B1F0  38 A0 00 7A */	li r5, 122
/* 8014E614 0014B1F4  C0 3F 00 2C */	lfs f1, 44(r31)
/* 8014E618 0014B1F8  48 17 9D 65 */	bl it_802C837C
lbl_8014E61C:
/* 8014E61C 0014B1FC  38 00 00 00 */	li r0, 0
/* 8014E620 0014B200  90 1F 21 BC */	stw r0, 8636(r31)
lbl_8014E624:
/* 8014E624 0014B204  80 01 00 6C */	lwz r0, 108(r1)
/* 8014E628 0014B208  83 E1 00 64 */	lwz r31, 100(r1)
/* 8014E62C 0014B20C  83 C1 00 60 */	lwz r30, 96(r1)
/* 8014E630 0014B210  83 A1 00 5C */	lwz r29, 92(r1)
/* 8014E634 0014B214  83 81 00 58 */	lwz r28, 88(r1)
/* 8014E638 0014B218  38 21 00 68 */	addi r1, r1, 104
/* 8014E63C 0014B21C  7C 08 03 A6 */	mtlr r0
/* 8014E640 0014B220  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/**
 * @author VetriTheRetri
 * @remarks https://decomp.me/scratch/P7Z9j - terrifying code
 * @remarks https://decomp.me/scratch/kFkx6 - closer match, but just what is
 *          going on in this one? temp_fp suggests there is an inline somewhere
 *          in the function, but an inline depth of 2 causes the compiler to
 *          start using branch link; no combination of inlines / lack thereof I
 *          have tried fully match
 */
static void ftGw_SpecialN_CreateSausage(HSD_GObj* gobj)
{
    Vec3 sp44;
    Vec3 sp38;
    Fighter* fp;
    Fighter* temp_fp;
    s32 temp_r5;
    s32 temp_r6;
    s32 randomInt;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    s32 sausageCount[5];
    ftGameWatchAttributes* gawAttrs;

    fp = GET_FIGHTER(gobj);
    gawAttrs = getFtSpecialAttrs(fp);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = randomInt = 0;
        if (((f32) fp->mv.gw.SpecialN.maxSausage) <
            gawAttrs->x1C_GAMEWATCH_CHEF_MAX)
        {
            fp->mv.gw.SpecialN.maxSausage++;
            sp38.x = 2.5f;
            sp38.y = 6.5f;
            sp38.z = 0.0f;
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].joint,
                        &sp38, &sp44);
            temp_fp = GET_FIGHTER(gobj);
            {
                int const len = (signed) ARRAY_SIZE(sausageCount);
                int i = len;
                for (i -= len; i < len; i++) {
                    if (i != temp_fp->fv.gw.x2240_chefVar1 &&
                        i != temp_fp->fv.gw.x2244_chefVar2)
                    {
                        sausageCount[randomInt] = i;
                        randomInt++;
                    }
                }
            }
            temp_r5 = sausageCount[HSD_Randi(randomInt)];
            temp_fp->fv.gw.x2244_chefVar2 = temp_fp->fv.gw.x2240_chefVar1;
            temp_r6 = temp_r5;
            temp_fp->fv.gw.x2240_chefVar1 = temp_r5;
            it_802C837C(gobj, &sp44, 122, temp_r6, fp->facing_dir);
        }
        fp->accessory4_cb = NULL;
    }
}

#endif

static inline void ftGameWatch_SpecialN_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.gw.SpecialN.isChefLoopDisable = false;
    fp->mv.gw.SpecialN.maxSausage = 0;
    fp->accessory4_cb = ftGw_SpecialN_CreateSausage;
}

// 0x8014E644
// https://decomp.me/scratch/VyJIm // Mr. Game & Watch's grounded Chef Action
// State handler
void ftGw_SpecialN_Enter(HSD_GObj* gobj)
{
    GET_FIGHTER(gobj)->self_vel.y = 0.0f;
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftGameWatch_SpecialN_SetVars(gobj);
}

// 0x8014E6C0
// https://decomp.me/scratch/VyJIm // Mr. Game & Watch's aerial Chef Action
// State handler
void ftGw_SpecialAirN_Enter(HSD_GObj* gobj)
{
    GET_FIGHTER(gobj)->self_vel.y = 0.0f;
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftGameWatch_SpecialN_SetVars(gobj);
}

static inline void ftGameWatch_SpecialN_ChefLoop(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrsD(fp);

    if ((u32) fp->cmd_vars[2] != 0U) {
        fp->cmd_vars[2] = 0U;
        if (((f32) fp->mv.gw.SpecialN.maxSausage <
             gawAttrs->x1C_GAMEWATCH_CHEF_MAX) &&
            ((s32) fp->mv.gw.SpecialN.isChefLoopDisable == false))
        {
            ftGw_SpecialN_Loop(gobj, gawAttrs->x18_GAMEWATCH_CHEF_LOOPFRAME);
        }
    }
}

// 0x8014E73C
// https://decomp.me/scratch/thHUb // Mr. Game & Watch's grounded Chef
// Animation callback
void ftGw_SpecialN_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    ftGameWatch_SpecialN_ChefLoop(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

static inline void ftGameWatch_SpecialAirN_ChefLoop(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrsD(fp);

    if ((u32) fp->cmd_vars[2] != 0U) {
        fp->cmd_vars[2] = 0U;
        if (((s32) fp->mv.gw.SpecialN.isChefLoopDisable == false) &&
            ((f32) fp->mv.gw.SpecialN.maxSausage <
             gawAttrs->x1C_GAMEWATCH_CHEF_MAX))
        {
            ftGw_SpecialAirN_Loop(gobj,
                                  gawAttrs->x18_GAMEWATCH_CHEF_LOOPFRAME);
        }
    }
}

// 0x8014E7DC
// https://decomp.me/scratch/DA54p // Mr. Game & Watch's aerial Chef Animation
// callback
void ftGw_SpecialAirN_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    ftGameWatch_SpecialAirN_ChefLoop(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800CC730(gobj);
    }
}

// 0x8014E87C
// https://decomp.me/scratch/bwVYE // Mr. Game & Watch's grounded Chef IASA
// callback
void ftGw_SpecialN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = gawAttrs = getFtSpecialAttrsD(fp);

    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
        fp->mv.gw.SpecialN.isChefLoopDisable = true;
    }
    if (((u32) fp->cmd_vars[1] != 0U) && (fp->input.x668 & HSD_PAD_B) &&
        ((f32) fp->mv.gw.SpecialN.maxSausage <
         gawAttrs->x1C_GAMEWATCH_CHEF_MAX))
    {
        ftGw_SpecialN_Loop(gobj, gawAttrs->x18_GAMEWATCH_CHEF_LOOPFRAME);
    }
}

// 0x8014E900
// https://decomp.me/scratch/jOJ8s // Mr. Game & Watch's aerial Chef IASA
// callback
void ftGw_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = gawAttrs = getFtSpecialAttrsD(fp);

    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
        fp->mv.gw.SpecialN.isChefLoopDisable = true;
    }
    if (((u32) fp->cmd_vars[1] != 0U) && (fp->input.x668 & HSD_PAD_B) &&
        ((f32) fp->mv.gw.SpecialN.maxSausage <
         gawAttrs->x1C_GAMEWATCH_CHEF_MAX))
    {
        ftGw_SpecialAirN_Loop(gobj, gawAttrs->x18_GAMEWATCH_CHEF_LOOPFRAME);
    }
}

// 0x8014E984 - Mr. Game & Watch's grounded Chef Physics callback
void ftGw_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x8014E9A4 - Mr. Game & Watch's aerial Chef Physics callback
void ftGw_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

// 0x8014E9C4
// https://decomp.me/scratch/SfsYX // Mr. Game & Watch's grounded Chef
// Collision callback
void ftGw_SpecialN_Coll(HSD_GObj* gobj)
{
    if (ft_800827A0(gobj) == false) {
        ftGw_SpecialN_GroundToAir(gobj);
    }
}

// 0x8014EA00
// https://decomp.me/scratch/3uVog // Mr. Game & Watch's aerial Chef Collision
// callback
void ftGw_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != false) {
        ftGw_SpecialAirN_AirToGround(gobj);
    }
}

static u32 const transition_flags =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit | Ft_MF_SkipModel |
    Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

// 0x8014EA3C
// https://decomp.me/scratch/mtcx1 // Mr. Game & Watch's ground -> air Chef
// Motion State handler
void ftGw_SpecialN_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirN, transition_flags,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    GET_FIGHTER(gobj)->accessory4_cb = &ftGw_SpecialN_CreateSausage;
}

// 0x8014EAAC
// https://decomp.me/scratch/SLxV6 // Mr. Game & Watch's air -> ground Chef
// Motion State handler
void ftGw_SpecialAirN_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialN, transition_flags,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    GET_FIGHTER(gobj)->accessory4_cb = &ftGw_SpecialN_CreateSausage;
}

// 0x8014EB1C
// https://decomp.me/scratch/KLilJ // Mr. Game & Watch's grounded Chef Loop
// Motion State handler
void ftGw_SpecialN_Loop(HSD_GObj* gobj, f32 anim_frame)
{
    /// @todo Shared @c inline with #ftGw_SpecialAirN_Loop.
    Fighter* fp = fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialN, transition_flags,
                              anim_frame - 1.0f, 1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);

#ifdef MUST_MATCH
    /// @todo Repeated assignment
    fp = fp = GET_FIGHTER(gobj);
#else
    fp = GET_FIGHTER(gobj);
#endif

    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.gw.SpecialN.isChefLoopDisable = false;
    fp->accessory4_cb = ftGw_SpecialN_CreateSausage;
}

// 0x8014EB8C
// https://decomp.me/scratch/KLilJ // Mr. Game & Watch's aerial Chef Loop
// Motion State handler
void ftGw_SpecialAirN_Loop(HSD_GObj* gobj, f32 anim_frame)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirN, transition_flags,
                              anim_frame - 1.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);

#ifdef MUST_MATCH
    fp = fp = GET_FIGHTER(gobj);
#else
    fp = GET_FIGHTER(gobj);
#endif

    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.gw.SpecialN.isChefLoopDisable = false;
    fp->accessory4_cb = ftGw_SpecialN_CreateSausage;
}
