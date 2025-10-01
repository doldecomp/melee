#include "ftGw_SpecialS.h"

#include "ftGw_Init.h"
#include "types.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "it/items/it_27CF.h"
#include "it/items/itfoods.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>
#include <baselib/random.h>

static void ftGw_SpecialS_ItemJudgementExitHitlag(HSD_GObj* gobj);
static void ftGw_SpecialS_ItemJudgementEnterHitlag(HSD_GObj* gobj);

// 0x8014C46C
// https://decomp.me/scratch/ohXu0 // Create Judgement item
void ftGw_SpecialS_ItemJudgementSetup(HSD_GObj* gobj)
{
    Vec3 sp20;
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);

    if (GET_FIGHTER(gobj)->cmd_vars[1] != 0U) {
        fp->cmd_vars[1] = 0;
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_RThumbNb)].joint,
                    NULL, &sp20);
        fp->fv.gw.x2264_judgementGObj =
            it_802C7774(fp->facing_dir, gobj, &sp20,
                        ftParts_GetBoneIndex(fp, FtPart_RThumbNb),
                        fp->fv.gw.x222C_judgeVar1);
        if ((s32) fp->fv.gw.x222C_judgeVar1 == 6) {
            sp14.z = 0.0f;
            sp14.x = 0.0f;
            sp14.y = 5.0f;
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_LThumbNb)].joint,
                &sp14, &sp20);
            it_8028FAF4(gobj, &sp20);
        }
        if (fp->fv.gw.x2264_judgementGObj != NULL) {
            fp->death2_cb = ftGw_Init_OnDamage;
            fp->take_dmg_cb = ftGw_Init_OnDamage;
        }
        fp->pre_hitlag_cb = ftGw_SpecialS_ItemJudgementEnterHitlag;
        fp->post_hitlag_cb = ftGw_SpecialS_ItemJudgementExitHitlag;
        fp->accessory4_cb = NULL;
    }
}

// 0x8014C590
// https://decomp.me/scratch/KIUEJ // Set Judgement flags + clear pointers
void ftGw_SpecialS_ItemJudgementSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_SpecialS_ItemJudgementExitHitlag(gobj);
    fp->fv.gw.x2264_judgementGObj = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

// 0x8014C5CC
// https://decomp.me/scratch/jU9ji // Remove Judgement item
void ftGw_SpecialS_ItemJudgementRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2264_judgementGObj != NULL) {
        it_802C7A84(fp->fv.gw.x2264_judgementGObj);
        ftGw_SpecialS_ItemJudgementSetFlag(gobj);
    }
}

// 0x8014C62C
// https://decomp.me/scratch/vFist // Apply hitlag to Judgement item
static void ftGw_SpecialS_ItemJudgementEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x2264_judgementGObj != NULL) {
        it_802C7AD0(fp->fv.gw.x2264_judgementGObj);
    }
}

// 0x8014C65C - Remove hitlag for Judgement item
static void ftGw_SpecialS_ItemJudgementExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x2264_judgementGObj != NULL) {
        it_802C7AF0(fp->fv.gw.x2264_judgementGObj);
    }
}

// 0x8014C68C
// https://decomp.me/scratch/MTdOC // Check if Mr. Game & Watch is in any of
// his SpecialS Motion States
bool ftGw_SpecialS_ItemCheckJudgementRemove(HSD_GObj* gobj)
{
    /// @todo @c enum
    enum_t msid = GET_FIGHTER(gobj)->motion_id;

    if (msid >= ftGw_MS_SpecialS1 && msid <= ftGw_MS_SpecialAirS9) {
        return false;
    }

    return true;
}

int ftGw_SpecialS_GetRandomInt(HSD_GObj* gobj)
{
    /// @todo #getFighter can be factored out somehow.
    Fighter* fp = getFighter(gobj);
    ftGameWatchAttributes* sa = getFtSpecialAttrs(fp);

    ftGameWatchJudge gw_judge0;
    ftGameWatchJudge gw_judge1;
    size_t i;
    int rand;

    {
        int const judge_max = 9;
        int judge = judge_max;

        for (judge -= judge_max, i = 0, rand = 0; judge < judge_max; judge++) {
            if (judge != fp->fv.gw.x222C_judgeVar1 &&
                judge != fp->fv.gw.x2230_judgeVar2)
            {
                gw_judge0.rollVar[i] = judge;
                rand += sa->x34_GAMEWATCH_JUDGE_ROLL[judge];
                gw_judge1.rollVar[i] = rand;
                i++;
            }
        }
    }

    rand = HSD_Randi(rand);

    {
        int result;
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsometimes-uninitialized"
#endif
        for (i = 0; i < ARRAY_SIZE(gw_judge1.rollVar); i++) {
#ifdef __clang__
#pragma clang diagnostic pop
#endif
            /// @remarks If this condition is never hit, @c result is
            ///          uninitialized and its value is undefined.
            if (rand < gw_judge1.rollVar[i]) {
                result = gw_judge0.rollVar[i];
                break;
            }
        }

        fp->fv.gw.x2230_judgeVar2 = fp->fv.gw.x222C_judgeVar1;
        fp->fv.gw.x222C_judgeVar1 = result;
        return result;
    }
}

static inline void ftGameWatch_SpecialS_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->accessory4_cb = ftGw_SpecialS_ItemJudgementSetup;
}

// 0x8014C7A0
// https://decomp.me/scratch/PnafK
void ftGw_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[4];

    GET_FIGHTER(gobj)->self_vel.y = 0.0f;

    /// @todo Shared @c inline with #ftGw_SpecialAirS_Enter.
    ftGw_SpecialS_GetRandomInt(gobj);
    Fighter_ChangeMotionState(gobj,
                              fp->fv.gw.x222C_judgeVar1 + ftGw_MS_SpecialS1, 0,
                              0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftGameWatch_SpecialS_SetVars(gobj);
}

// 0x8014C828
// https://decomp.me/scratch/IzXqX
void ftGw_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = fp->dat_attrs;

    u8 _[4];

    GET_FIGHTER(gobj)->self_vel.x /=
        gawAttrs->x20_GAMEWATCH_JUDGE_MOMENTUM_PRESERVE;

    ftGw_SpecialS_GetRandomInt(gobj);
    Fighter_ChangeMotionState(gobj,
                              fp->fv.gw.x222C_judgeVar1 + ftGw_MS_SpecialAirS1,
                              0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftGameWatch_SpecialS_SetVars(gobj);
}

// 0x8014C8BC
// https://decomp.me/scratch/xcOet // Mr. Game & Watch's Grounded Judgement
// Animation callback
void ftGw_SpecialS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

// 0x8014C8F8 - Mr. Game & Watch's Aerial Judgement Animation callback
void ftGw_SpecialAirS_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

// 0x8014C934 - Mr. Game & Watch's Grounded Judgement IASA callback
void ftGw_SpecialS_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014C938 - Mr. Game & Watch's Aerial Judgement IASA callback
void ftGw_SpecialAirS_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x8014C93C
// https://decomp.me/scratch/ulBEx // Mr. Game & Watch's Grounded Judgement
// Physics callback
void ftGw_SpecialS_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((u32) fp->cmd_vars[0] == 1U) {
        fp->cmd_vars[0] = 2U;
    }

    ft_80084F3C(gobj);
}

// 0x8014C974
// https://decomp.me/scratch/kDevS // Mr. Game & Watch's Aerial Judgement
// Physics callback
void ftGw_SpecialAirS_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 ftcmd_var = fp->cmd_vars[0];
    ftGameWatchAttributes* gawAttrs = fp->dat_attrs;

    u8 _[16];

    if (ftcmd_var >= 1U) {
        if (ftcmd_var == 1) {
            fp->cmd_vars[0] = 2;
            if ((s32) fp->fv.gw.x2234 == 0) {
                fp->fv.gw.x2234 = 1;
                fp->self_vel.y = gawAttrs->x28_GAMEWATCH_JUDGE_VEL_Y;
            } else {
                fp->self_vel.y = 0.0f;
            }
        }
        ftCommon_Fall(fp, gawAttrs->x2C_GAMEWATCH_JUDGE_FRICTION1,
                          gawAttrs->x30_GAMEWATCH_JUDGE_FRICTION2);
    } else {
        ftCommon_FallBasic(fp);
    }
    ftCommon_ApplyFrictionAir(fp, gawAttrs->x24_GAMEWATCH_JUDGE_MOMENTUM_MUL);
}

static void ftGw_SpecialS_GroundToAir(HSD_GObj*);
static void ftGw_SpecialAirS_AirToGround(HSD_GObj*);

// 0x8014CA10
// https://decomp.me/scratch/G9OvA // Mr. Game & Watch's Grounded Judgement
// Collision callback
void ftGw_SpecialS_Coll(HSD_GObj* gobj)
{
    if (ft_800827A0(gobj) == false) {
        ftGw_SpecialS_GroundToAir(gobj);
    }
}

// 0x8014CA4C - Mr. Game & Watch's Aerial Judgement Collision callback
void ftGw_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj) != false) {
        ftGw_SpecialAirS_AirToGround(gobj);
    }
}

static inline void ftGameWatch_SpecialS_SetCall(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x2264_judgementGObj != NULL) {
        fp->death2_cb = ftGw_Init_OnDamage;
        fp->take_dmg_cb = ftGw_Init_OnDamage;
    }

    fp->pre_hitlag_cb = ftGw_SpecialS_ItemJudgementEnterHitlag;
    fp->post_hitlag_cb = ftGw_SpecialS_ItemJudgementExitHitlag;
    fp->accessory4_cb = ftGw_SpecialS_ItemJudgementSetup;
}

static u32 const transition_flags =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit | Ft_MF_SkipModel |
    Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |
    Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |
    Ft_MF_SkipModelFlags | Ft_MF_Unk27;

/// Mr. Game & Watch's ground -> air Judgement Motion State handler
static void ftGw_SpecialS_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[4];

    ftCommon_8007D5D4(fp);
    !gobj;
    Fighter_ChangeMotionState(
        gobj, fp->fv.gw.x222C_judgeVar1 + ftGw_MS_SpecialAirS1,
        transition_flags, fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    if ((u32) fp->cmd_vars[0] == 1) {
        fp->cmd_vars[0] = 2;
    }
    ftGameWatch_SpecialS_SetCall(gobj);
}

// 0x8014CB44 - Mr. Game & Watch's air -> ground Judgement Motion State Handler
static void ftGw_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[4];

    fp->fv.gw.x2234 = 0;
    ftCommon_8007D7FC(fp);
    !gobj;
    Fighter_ChangeMotionState(
        gobj, fp->fv.gw.x222C_judgeVar1 + ftGw_MS_SpecialS1, transition_flags,
        fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    ftGameWatch_SpecialS_SetCall(gobj);
}
