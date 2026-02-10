#include "ftGw_SpecialN.h"

#include "types.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "it/items/itgamewatchchef.h"
#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <baselib/random.h>

static void ftGw_SpecialN_CreateSausage(HSD_GObj* gobj)
{
    Vec3 vec0;
    Vec3 vec1;

    u8 _[4] = { 0 };

    {
        ftGameWatchChef chefStruct;
        u8 _[4] = { 0 };
        int i;
        int* pSausage;
        {
            u8 _[8] = { 0 };

            Fighter* fp1;
            {
                Fighter* fp = GET_FIGHTER(gobj);
                ftGameWatchAttributes* gawAttrs = fp->dat_attrs;
                if (fp->cmd_vars[0] != 0) {
                    int var_r28;
                    fp->cmd_vars[0] = var_r28 = 0;

                    if (fp->mv.gw.SpecialN.maxSausage <
                        gawAttrs->x1C_GAMEWATCH_CHEF_MAX)
                    {
                        fp->mv.gw.SpecialN.maxSausage++;

                        vec1.x = 2.5f;
                        vec1.y = 6.5f;
                        vec1.z = 0.0f;

                        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(
                                                  fp, FtPart_LThumbNb)]
                                        .joint,
                                    &vec1, &vec0);

                        {
                            fp1 = gobj->user_data;
                            pSausage = chefStruct.sausageCount;
                            for (i = 5, i -= 5; i < 5; i++) {
                                if (i != fp1->fv.gw.x2240_chefVar1 &&
                                    i != fp1->fv.gw.x2244_chefVar2)
                                {
                                    *pSausage++ = i;
                                    var_r28++;
                                }
                            }
                            {
                                int temp_r5 =
                                    chefStruct
                                        .sausageCount[HSD_Randi(var_r28)];
                                int var_r6;
                                fp1->fv.gw.x2244_chefVar2 =
                                    fp1->fv.gw.x2240_chefVar1;
                                var_r6 = temp_r5;
                                fp1->fv.gw.x2240_chefVar1 = temp_r5;
                                it_802C837C(gobj, &vec0, 122, var_r6,
                                            fp->facing_dir);
                            }
                        }
                    }
                    fp->accessory4_cb = NULL;
                }
            }
        }
    }
}

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

/// 0x8014E644
/// https://decomp.me/scratch/VyJIm // Mr. Game & Watch's grounded Chef Action
/// State handler
void ftGw_SpecialN_Enter(HSD_GObj* gobj)
{
    GET_FIGHTER(gobj)->self_vel.y = 0.0f;
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialN, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftGameWatch_SpecialN_SetVars(gobj);
}

/// 0x8014E6C0
/// https://decomp.me/scratch/VyJIm // Mr. Game & Watch's aerial Chef Action
/// State handler
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
        if (((float) fp->mv.gw.SpecialN.maxSausage <
             gawAttrs->x1C_GAMEWATCH_CHEF_MAX) &&
            ((s32) fp->mv.gw.SpecialN.isChefLoopDisable == false))
        {
            ftGw_SpecialN_Loop(gobj, gawAttrs->x18_GAMEWATCH_CHEF_LOOPFRAME);
        }
    }
}

/// 0x8014E73C
/// https://decomp.me/scratch/thHUb // Mr. Game & Watch's grounded Chef
/// Animation callback
void ftGw_SpecialN_Anim(HSD_GObj* gobj)
{
    u8 _[20];

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
            ((float) fp->mv.gw.SpecialN.maxSausage <
             gawAttrs->x1C_GAMEWATCH_CHEF_MAX))
        {
            ftGw_SpecialAirN_Loop(gobj,
                                  gawAttrs->x18_GAMEWATCH_CHEF_LOOPFRAME);
        }
    }
}

/// 0x8014E7DC
/// https://decomp.me/scratch/DA54p // Mr. Game & Watch's aerial Chef Animation
/// callback
void ftGw_SpecialAirN_Anim(HSD_GObj* gobj)
{
    u8 _[20];

    ftGameWatch_SpecialAirN_ChefLoop(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

/// 0x8014E87C
/// https://decomp.me/scratch/bwVYE // Mr. Game & Watch's grounded Chef IASA
/// callback
void ftGw_SpecialN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = gawAttrs = getFtSpecialAttrsD(fp);

    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
        fp->mv.gw.SpecialN.isChefLoopDisable = true;
    }
    if (fp->cmd_vars[1] != 0 && (fp->input.x668 & HSD_PAD_B) &&
        fp->mv.gw.SpecialN.maxSausage < gawAttrs->x1C_GAMEWATCH_CHEF_MAX)
    {
        ftGw_SpecialN_Loop(gobj, gawAttrs->x18_GAMEWATCH_CHEF_LOOPFRAME);
    }
}

/// 0x8014E900
/// https://decomp.me/scratch/jOJ8s // Mr. Game & Watch's aerial Chef IASA
/// callback
void ftGw_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = gawAttrs = getFtSpecialAttrsD(fp);

    if ((fp->input.held_inputs & HSD_PAD_B) == false) {
        fp->mv.gw.SpecialN.isChefLoopDisable = true;
    }
    if (fp->cmd_vars[1] != 0 && (fp->input.x668 & HSD_PAD_B) &&
        fp->mv.gw.SpecialN.maxSausage < gawAttrs->x1C_GAMEWATCH_CHEF_MAX)
    {
        ftGw_SpecialAirN_Loop(gobj, gawAttrs->x18_GAMEWATCH_CHEF_LOOPFRAME);
    }
}

/// 0x8014E984 - Mr. Game & Watch's grounded Chef Physics callback
void ftGw_SpecialN_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// 0x8014E9A4 - Mr. Game & Watch's aerial Chef Physics callback
void ftGw_SpecialAirN_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

/// 0x8014E9C4
/// https://decomp.me/scratch/SfsYX // Mr. Game & Watch's grounded Chef
/// Collision callback
void ftGw_SpecialN_Coll(HSD_GObj* gobj)
{
    if (ft_800827A0(gobj) == false) {
        ftGw_SpecialN_GroundToAir(gobj);
    }
}

/// 0x8014EA00
/// https://decomp.me/scratch/3uVog // Mr. Game & Watch's aerial Chef Collision
/// callback
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

/// 0x8014EA3C
/// https://decomp.me/scratch/mtcx1 // Mr. Game & Watch's ground -> air Chef
/// Motion State handler
void ftGw_SpecialN_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirN, transition_flags,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    GET_FIGHTER(gobj)->accessory4_cb = &ftGw_SpecialN_CreateSausage;
}

/// 0x8014EAAC
/// https://decomp.me/scratch/SLxV6 // Mr. Game & Watch's air -> ground Chef
/// Motion State handler
void ftGw_SpecialAirN_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialN, transition_flags,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    GET_FIGHTER(gobj)->accessory4_cb = &ftGw_SpecialN_CreateSausage;
}

/// 0x8014EB1C
/// https://decomp.me/scratch/KLilJ // Mr. Game & Watch's grounded Chef Loop
/// Motion State handler
void ftGw_SpecialN_Loop(HSD_GObj* gobj, float anim_frame)
{
    /// @@todo Shared @c inline with #ftGw_SpecialAirN_Loop.
    Fighter* fp = fp = GET_FIGHTER(gobj);

    u8 _[4];

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialN, transition_flags,
                              anim_frame - 1.0f, 1.0f, 0.0f, NULL);

    ftAnim_8006EBA4(gobj);

    fp = fp = GET_FIGHTER(gobj);

    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.gw.SpecialN.isChefLoopDisable = false;
    fp->accessory4_cb = ftGw_SpecialN_CreateSausage;
}

/// 0x8014EB8C
/// https://decomp.me/scratch/KLilJ // Mr. Game & Watch's aerial Chef Loop
/// Motion State handler
void ftGw_SpecialAirN_Loop(HSD_GObj* gobj, float anim_frame)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);

    u8 _[4];

    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirN, transition_flags,
                              anim_frame - 1.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);

    fp = fp = GET_FIGHTER(gobj);

    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->mv.gw.SpecialN.isChefLoopDisable = false;
    fp->accessory4_cb = ftGw_SpecialN_CreateSausage;
}
