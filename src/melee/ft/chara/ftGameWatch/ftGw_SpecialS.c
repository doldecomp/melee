#include "forward.h"
#include "ft/forward.h"

#include "ftGw_SpecialS.h"

#include "ftGw_Init.h"
#include "types.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx/types.h>

static void ftGw_SpecialS_ItemJudgementExitHitlag(HSD_GObj* gobj);
static void ftGw_SpecialS_ItemJudgementEnterHitlag(HSD_GObj* gobj);

// 0x8014C46C
// https://decomp.me/scratch/ohXu0 // Create Judgement item
void ftGw_SpecialS_ItemJudgementSetup(HSD_GObj* gobj)
{
    Vec3 sp20;
    Vec3 sp14;
    Fighter* fp = GET_FIGHTER(gobj);

    if (GET_FIGHTER(gobj)->x2204_ftcmd_var1 != 0U) {
        fp->x2204_ftcmd_var1 = 0;
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].x0_jobj,
                    NULL, &sp20);
        fp->fv.gw.x2264_judgementGObj = it_802C7774(
            fp->facing_dir, gobj, &sp20, ftParts_8007500C(fp, FtPart_RThumbNb),
            fp->fv.gw.x222C_judgeVar1);
        if ((s32) fp->fv.gw.x222C_judgeVar1 == 6) {
            sp14.z = 0.0f;
            sp14.x = 0.0f;
            sp14.y = 5.0f;
            lb_8000B1CC(
                fp->parts[ftParts_8007500C(fp, FtPart_LThumbNb)].x0_jobj,
                &sp14, &sp20);
            it_8028FAF4(gobj, &sp20);
        }
        if (fp->fv.gw.x2264_judgementGObj != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGw_Init_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGw_Init_OnDamage;
        }
        fp->cb.x21D4_callback_EnterHitlag =
            ftGw_SpecialS_ItemJudgementEnterHitlag;
        fp->cb.x21D8_callback_ExitHitlag =
            ftGw_SpecialS_ItemJudgementExitHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014C590
// https://decomp.me/scratch/KIUEJ // Set Judgement flags + clear pointers
void ftGw_SpecialS_ItemJudgementSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_SpecialS_ItemJudgementExitHitlag(gobj);
    fp->fv.gw.x2264_judgementGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
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
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21BC_callback_Accessory4 = ftGw_SpecialS_ItemJudgementSetup;
}

// 0x8014C7A0
// https://decomp.me/scratch/PnafK
void ftGw_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    GET_FIGHTER(gobj)->x80_self_vel.y = 0.0f;

    /// @todo Shared @c inline with #ftGw_SpecialAirS_Enter.
    ftGw_SpecialS_GetRandomInt(gobj);
    Fighter_ChangeMotionState(gobj,
                              fp->fv.gw.x222C_judgeVar1 + ftGw_MS_SpecialS1, 0,
                              NULL, 0.0f, 1.0f, 0.0f);
    ftAnim_8006EBA4(gobj);
    ftGameWatch_SpecialS_SetVars(gobj);
}

// 0x8014C828
// https://decomp.me/scratch/IzXqX
void ftGw_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    GET_FIGHTER(gobj)->x80_self_vel.x /=
        gawAttrs->x20_GAMEWATCH_JUDGE_MOMENTUM_PRESERVE;

    ftGw_SpecialS_GetRandomInt(gobj);
    Fighter_ChangeMotionState(gobj,
                              fp->fv.gw.x222C_judgeVar1 + ftGw_MS_SpecialAirS1,
                              0, NULL, 0.0f, 1.0f, 0.0f);
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
        ft_800CC730(gobj);
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

    if ((u32) fp->x2200_ftcmd_var0 == 1U) {
        fp->x2200_ftcmd_var0 = 2U;
    }

    ft_80084F3C(gobj);
}

// 0x8014C974
// https://decomp.me/scratch/kDevS // Mr. Game & Watch's Aerial Judgement
// Physics callback
void ftGw_SpecialAirS_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32 ftcmd_var = fp->x2200_ftcmd_var0;
    ftGameWatchAttributes* gawAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    if (ftcmd_var >= 1U) {
        if (ftcmd_var == 1) {
            fp->x2200_ftcmd_var0 = 2;
            if ((s32) fp->fv.gw.x2234 == 0) {
                fp->fv.gw.x2234 = 1;
                fp->x80_self_vel.y = gawAttrs->x28_GAMEWATCH_JUDGE_VEL_Y;
            } else {
                fp->x80_self_vel.y = 0.0f;
            }
        }
        ftCommon_8007D494(fp, gawAttrs->x2C_GAMEWATCH_JUDGE_FRICTION1,
                          gawAttrs->x30_GAMEWATCH_JUDGE_FRICTION2);
    } else {
        ftCommon_8007D4B8(fp);
    }
    ftCommon_8007CE94(fp, gawAttrs->x24_GAMEWATCH_JUDGE_MOMENTUM_MUL);
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
        fp->cb.x21E4_callback_OnDeath2 = ftGw_Init_OnDamage;
        fp->cb.x21DC_callback_OnTakeDamage = ftGw_Init_OnDamage;
    }

    fp->cb.x21D4_callback_EnterHitlag = ftGw_SpecialS_ItemJudgementEnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftGw_SpecialS_ItemJudgementExitHitlag;
    fp->cb.x21BC_callback_Accessory4 = ftGw_SpecialS_ItemJudgementSetup;
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

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ftCommon_8007D5D4(fp);
    !gobj;
    Fighter_ChangeMotionState(
        gobj, fp->fv.gw.x222C_judgeVar1 + ftGw_MS_SpecialAirS1,
        transition_flags, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    if ((u32) fp->x2200_ftcmd_var0 == 1) {
        fp->x2200_ftcmd_var0 = 2;
    }
    ftGameWatch_SpecialS_SetCall(gobj);
}

// 0x8014CB44 - Mr. Game & Watch's air -> ground Judgement Motion State Handler
static void ftGw_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp->fv.gw.x2234 = 0;
    ftCommon_8007D7FC(fp);
    !gobj;
    Fighter_ChangeMotionState(
        gobj, fp->fv.gw.x222C_judgeVar1 + ftGw_MS_SpecialS1, transition_flags,
        NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
    ftGameWatch_SpecialS_SetCall(gobj);
}
