#include <baselib/forward.h>

#include "ftCaptain_SpecialS.h"

#include "ftCaptain_Init.h"
#include "types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/types.h"

#include <dolphin/mtx/types.h>

void ftCa_SpecialS_RemoveGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    efLib_DestroyAll(gobj);

    fp->ev.ca.during_specials = false;
    fp->ev.ca.during_specials_start = false;
}

static void setCallbacks(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cb.x21DC_callback_OnTakeDamage = ftCa_Init_800E28C8;
    fp->cb.x21E4_callback_OnDeath2 = ftCa_Init_800E28C8;
}

static void resetCmdVarsGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u32* vars = (u32*) &fp->x2200_ftcmd_var0;
    vars[0] = vars[1] = vars[2] = vars[3] = 0;
    ftCommon_8007D7FC(fp);
}

void ftCa_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    resetCmdVarsGround(gobj);

    Fighter_ChangeMotionState(gobj, ftCaptain_AS_SpecialS_Start, 0, NULL, 0, 1,
                              0);

    setCallbacks(gobj);
    ftAnim_8006EBA4(gobj);

    switch (ftLib_800872A4(gobj)) {
    case FTKIND_CAPTAIN:
        efSync_Spawn(1169, gobj, fp->x5E8_fighterBones[HeadN].x0_jobj);
        fp->ev.ca.during_specials_start = true;
        break;

    case FTKIND_GANON:
        efSync_Spawn(1293, gobj, fp->x5E8_fighterBones[L2ndNb].x0_jobj);
        fp->ev.ca.during_specials_start = true;
        break;
    }

    fp->ev.ca.during_specials = false;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21F4_callback = ftCa_SpecialS_OnDetect;

    {
        Vec3* vel = &fp->x80_self_vel;
        vel->x = vel->y = vel->z = 0;
    }

    fp->xEC_ground_vel = 0;
}

static inline void setupAirStart(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    {
        u32* vars = &fp->x2200_ftcmd_var0;
        vars[0] = vars[1] = vars[2] = vars[3] = 0;
    }

    Fighter_ChangeMotionState(gobj, ftCaptain_AS_SpecialAirS_Start, 0, NULL, 0,
                              1, 0);

    setCallbacks(gobj);
    ftAnim_8006EBA4(gobj);

    switch (ftLib_800872A4(gobj)) {
    case FTKIND_CAPTAIN:
        efSync_Spawn(1169, gobj, fp->x5E8_fighterBones[HeadN].x0_jobj);
        fp->ev.ca.during_specials_start = true;
        break;
    case FTKIND_GANON:
        efSync_Spawn(1293, gobj, fp->x5E8_fighterBones[L2ndNb].x0_jobj);
        fp->ev.ca.during_specials_start = true;
        break;
    }

    fp->ev.ca.during_specials = false;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21F4_callback = ftCa_SpecialS_OnDetect;

    {
        Vec3* vel = &fp->x80_self_vel;
        vel->x = vel->y = vel->z = 0;
    }
}

void ftCa_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    setupAirStart(gobj);
    fp->sv.ca.specials.grav = 0;
    ftCommon_8007D60C(fp);
}

static Fighter_MotionStateChangeFlags const transition_flags =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag |
    FtStateChange_Unk_27;

static void onDetectGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptainAttributes* sa = getFtSpecialAttrsD(fp);

    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftCaptain_AS_SpecialS, transition_flags,
                              NULL, 0, 1, 0);
    setCallbacks(gobj);

    {
        Vec3* vel = &fp->x80_self_vel;
        vel->y = vel->z = 0;
    }

    fp->xEC_ground_vel *= sa->specials_gr_vel_x;
}

static void onDetectAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCaptain_AS_SpecialAirS, transition_flags,
                              NULL, 0, 1, 0);
    setCallbacks(gobj);
    fp->x80_self_vel.z = 0;
}

void ftCa_SpecialS_OnDetect(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 == 0) {
        return;
    }

    {
        HSD_GObj* detected_gobj = fp->x20AC;

        if (fp->x20AC->classifier == HSD_GOBJ_CLASS_FIGHTER) {
            switch (fp->action_id) {
            case ftCaptain_AS_SpecialS_Start: {
                onDetectGround(gobj);
                break;
            }

            case ftCaptain_AS_SpecialAirS_Start:
                onDetectAir(gobj);
                break;
            }
        } else if (fp->x20AC->classifier == HSD_GOBJ_CLASS_ITEM) {
            if (itGetKind(detected_gobj) < It_Kind_BombHei) {
                switch (fp->action_id) {
                case ftCaptain_AS_SpecialS_Start:
                    onDetectGround(gobj);
                    break;

                case ftCaptain_AS_SpecialAirS_Start:
                    onDetectAir(gobj);
                    break;
                }
            } else if ((itGetKind(detected_gobj) >= It_Kind_Kuriboh &&
                        itGetKind(detected_gobj) < It_Kind_Octarock_Stone) ||
                       (itGetKind(detected_gobj) >= It_Kind_Old_Kuri &&
                        itGetKind(detected_gobj) < It_Kind_Arwing_Laser) ||
                       itGetKind(detected_gobj) == Pokemon_Random)
            {
                switch (fp->action_id) {
                case ftCaptain_AS_SpecialS_Start:
                    onDetectGround(gobj);
                    break;

                case ftCaptain_AS_SpecialAirS_Start:
                    onDetectAir(gobj);
                    break;
                }
            }
        }
    }
}

void ftCa_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCa_SpecialS_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->ev.ca.during_specials) {
        switch (ftLib_800872A4(gobj)) {
        case FTKIND_CAPTAIN:
            efSync_Spawn(1170, gobj, fp->x5E8_fighterBones[TransN].x0_jobj,
                         &fp->facing_dir);
            fp->ev.ca.during_specials = true;
            break;

        case FTKIND_GANON:
            efSync_Spawn(1294, gobj, fp->x5E8_fighterBones[TransN].x0_jobj,
                         &fp->facing_dir);
            fp->ev.ca.during_specials = true;
            break;
        }

        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCa_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);
        if (captainAttrs->specials_miss_landing_lag == 0) {
            ft_800CC730(gobj);
        } else {
            ft_80096900(gobj, 1, 1, 0, 1,
                        captainAttrs->specials_miss_landing_lag);
        }
    }
}

void ftCa_SpecialAirS_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!fp->ev.ca.during_specials) {
        switch (ftLib_800872A4(gobj)) {
        case FTKIND_CAPTAIN:
            efSync_Spawn(1171, gobj, fp->x5E8_fighterBones[TransN].x0_jobj,
                         &fp->facing_dir);
            fp->ev.ca.during_specials = true;
            break;

        case FTKIND_GANON:
            efSync_Spawn(1295, gobj, fp->x5E8_fighterBones[TransN].x0_jobj,
                         &fp->facing_dir);
            fp->ev.ca.during_specials = true;
            break;
        }

        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D60C(fp);

        if (captainAttrs->specials_hit_landing_lag == 0) {
            ft_800CC730(gobj);
        } else {
            ft_80096900(gobj, 1, 1, 0, 1,
                        captainAttrs->specials_hit_landing_lag);
        }
    }
}

void ftCa_SpecialSStart_IASA(HSD_GObj* gobj) {}

void ftCa_SpecialS_IASA(HSD_GObj* gobj) {}

void ftCa_SpecialAirSStart_IASA(HSD_GObj* gobj) {}

void ftCa_SpecialAirS_IASA(HSD_GObj* gobj) {}

void ftCa_SpecialSStart_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCa_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCa_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ft_80085134(gobj);
    if (fp->x2204_ftcmd_var1 == 1) {
        fp->sv.ca.specials.grav -= captainAttrs->specials_grav;

        if (fp->sv.ca.specials.grav < -captainAttrs->specials_terminal_vel) {
            fp->sv.ca.specials.grav = -captainAttrs->specials_terminal_vel;
        }

        fp->x80_self_vel.y = fp->sv.ca.specials.grav;
    }
}

void ftCa_SpecialAirS_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ft_80085134(gobj);
    fp->sv.ca.specials.grav -= captainAttrs->specials_grav;

    if (fp->sv.ca.specials.grav < -captainAttrs->specials_terminal_vel) {
        fp->sv.ca.specials.grav = -captainAttrs->specials_terminal_vel;
    }

    fp->x80_self_vel.y = fp->sv.ca.specials.grav;
}

// Captain Falcon & Ganondorf's grounded
// Raptor Boost / Gerudo Dragon Start Collision callback
void ftCa_SpecialSStart_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptainAttributes* sa = sa = fp->x2D4_specialAttributes;

    if (fp->x2208_ftcmd_var2 == 0) {
        ft_80084104(gobj);
        return;
    }

    if (ft_80082708(gobj) == false) {
        efLib_DestroyAll(gobj);
        ftCommon_8007D60C(fp);
        if (sa->specials_miss_landing_lag == 0) {
            ft_800CC730(gobj);
            return;
        }
        ftCommon_8007D468(fp);
        ft_80096900(gobj, 1, 1, 0, 1, sa->specials_miss_landing_lag);
        return;
    }

    if (fp->x2200_ftcmd_var0 == 1) {
        /// @todo Unused assignment.
#ifdef MUST_MATCH
        f32 _ = fp->facing_dir;
#endif

        if ((fp->facing_dir == +1 &&
             (fp->x6F0_collData.x134_envFlags & MPCOLL_RIGHTWALL)) ||
            (fp->facing_dir == -1 &&
             fp->x6F0_collData.x134_envFlags & MPCOLL_LEFTWALL))
        {
            efLib_DestroyAll(gobj);
            ft_8008A2BC(gobj);
        }
    }
}

void ftCa_SpecialS_Coll(HSD_GObj* gobj)
{
    Fighter* temp_fp = GET_FIGHTER(gobj);
    Fighter* fp;
    ftCaptainAttributes* captainAttrs = temp_fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = temp_fp;
    if (ft_80082708(gobj) == false) {
        efLib_DestroyAll(gobj);
        ftCommon_8007D60C(fp);
        if (0 == captainAttrs->specials_hit_landing_lag) {
            ft_800CC730(gobj);
            return;
        }
        ftCommon_8007D468(fp);
        ft_80096900(gobj, 1, 1, 0, 1, captainAttrs->specials_hit_landing_lag);
    }
}

void ftCa_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;

    if (ft_80081D0C(gobj) == true) {
        efLib_DestroyAll(gobj);
        ft_800D5CB0(gobj, 0, captainAttrs->specials_miss_landing_lag);
    }
}

// Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit
// Collision callback
void ftCa_SpecialAirS_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptainAttributes* captainAttrs = getFtSpecialAttrsD(fp);

    if (ft_80081D0C(gobj) == true) {
        fp->xEC_ground_vel = fp->x80_self_vel.x;
        efLib_DestroyAll(gobj);
        ft_800D5CB0(gobj, 0, captainAttrs->specials_hit_landing_lag);
    }
}
