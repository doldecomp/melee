#include "ftCaptain_SpecialS.h"

#include "ftCaptain.h"
#include "types.h"

#include "ft/types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "it/itkind.h"

// 0x800E3278
// https://decomp.me/scratch/yi9xr // Remove all GFX and set GFX flags to false
void ftCaptain_SpecialS_RemoveGFX(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    efLib_DestroyAll(fighter_gobj);

    fp->sa.captain.x2230_isSpecialSGFX = false;
    fp->sa.captain.x222C_isSpecialSStartGFX = false;
}

inline void ftCaptain_SpecialS_SetCall(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    fp->cb.x21DC_callback_OnTakeDamage = &ftCaptain_800E28C8;
    fp->cb.x21E4_callback_OnDeath2 = &ftCaptain_800E28C8;
}

// 0x800E32B0
// https://decomp.me/scratch/uyovM // Captain Falcon & Ganondorf's grounded
// Raptor Boost/Gerudo Dragon Start Action State handler
void ftCaptain_SpecialS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 ftKind;

    fp = GET_FIGHTER(fighter_gobj);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_CAPTAIN_SPECIALS_START,
                                       0, NULL, 0.0f, 1.0f, 0.0f);
    ftCaptain_SpecialS_SetCall(fighter_gobj);
    func_8006EBA4(fighter_gobj);

    ftKind = func_800872A4(fighter_gobj);
    switch (ftKind) {
    case FTKIND_CAPTAIN:
        ef_Spawn(0x491, fighter_gobj, fp->x5E8_fighterBones[0x22].x0_jobj);
        fp->sa.captain.x222C_isSpecialSStartGFX = true;
        break;

    case FTKIND_GANON:
        ef_Spawn(0x50D, fighter_gobj, fp->x5E8_fighterBones[0x19].x0_jobj);
        fp->sa.captain.x222C_isSpecialSStartGFX = true;
        break;
    }

    fp->sa.captain.x2230_isSpecialSGFX = false;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21F4_callback = ftCaptain_SpecialS_OnDetect;

    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
    fp->xEC_ground_vel = 0.0f;
}

// 0x800E350C
// https://decomp.me/scratch/EYc4a // Captain Falcon & Ganondorf's aerial Raptor
// Boost/Gerudo Dragon Start Action State handler
void ftCaptain_SpecialAirS_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 ftKind;

    fp = GET_FIGHTER(fighter_gobj);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    Fighter_ActionStateChange_800693AC(
        fighter_gobj, AS_CAPTAIN_SPECIALAIRS_START, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftCaptain_SpecialS_SetCall(fighter_gobj);
    func_8006EBA4(fighter_gobj);
    ftKind = func_800872A4(fighter_gobj);
    switch (ftKind) {
    case FTKIND_CAPTAIN:
        ef_Spawn(0x491, fighter_gobj, fp->x5E8_fighterBones[0x22].x0_jobj);
        fp->sa.captain.x222C_isSpecialSStartGFX = true;
        break;
    case FTKIND_GANON:
        ef_Spawn(0x50D, fighter_gobj, fp->x5E8_fighterBones[0x19].x0_jobj);
        fp->sa.captain.x222C_isSpecialSStartGFX = true;
        break;
    }
    fp->sa.captain.x2230_isSpecialSGFX = 0;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21F4_callback = ftCaptain_SpecialS_OnDetect;
    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;
    fp->captainVars.SpecialS.gravity = 0.0f;
    func_8007D60C(fp);
}

static Fighter_ActionStateChangeFlags const transition_flags =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_UpdateCmd | FtStateChange_SkipUpdateColAnim |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag |
    FtStateChange_Unk_27;

inline void ftCaptain_SpecialS_Switch0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = getFtSpecialAttrsD(fp);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_CAPTAIN_SPECIALS,
                                       transition_flags, NULL, 0.0f, 1.0f,
                                       0.0f);
    ftCaptain_SpecialS_SetCall(fighter_gobj);
    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->xEC_ground_vel *= captainAttrs->specials_gr_vel_x;
}

inline void ftCaptain_SpecialS_Switch1(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = getFtSpecialAttrsD(fp);
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_CAPTAIN_SPECIALS,
                                       transition_flags, NULL, 0.0f, 1.0f,
                                       0.0f);
    ftCaptain_SpecialS_SetCall(fighter_gobj);
    fp->x80_self_vel.z = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->xEC_ground_vel *= captainAttrs->specials_gr_vel_x;
}

inline void ftCaptain_SpecialS_Switch2(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_CAPTAIN_SPECIALAIRS,
                                       transition_flags, NULL, 0.0f, 1.0f,
                                       0.0f);
    ftCaptain_SpecialS_SetCall(fighter_gobj);
    fp->x80_self_vel.z = 0.0f;
}

// 0x800E350C
// https://decomp.me/scratch/8YN1Z // Captain Falcon & Ganondorf's Raptor Boost
// / Gerudo Dragon Detect function
void ftCaptain_SpecialS_OnDetect(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs;
    HSD_GObj* detectGObj;
    s32 ASID;
    u16 entityClass;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[20];
#endif

    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        detectGObj = fp->x20AC;
        entityClass = detectGObj->classifier;
        if (entityClass == HSD_GOBJ_CLASS_FIGHTER) {
            ASID = fp->action_id;
            switch (ASID) {
            case AS_CAPTAIN_SPECIALS_START:
                captainAttrs = getFtSpecialAttrsD(fp);
                func_8007D7FC(fp);
                Fighter_ActionStateChange_800693AC(
                    fighter_gobj, AS_CAPTAIN_SPECIALS, transition_flags, NULL,
                    0.0f, 1.0f, 0.0f);
                ftCaptain_SpecialS_SetCall(fighter_gobj);
                fp->x80_self_vel.z = 0.0f;
                fp->x80_self_vel.y = 0.0f;
                fp->xEC_ground_vel *= captainAttrs->specials_gr_vel_x;
                return;

            case AS_CAPTAIN_SPECIALAIRS_START:
                Fighter_ActionStateChange_800693AC(
                    fighter_gobj, AS_CAPTAIN_SPECIALAIRS, transition_flags,
                    NULL, 0.0f, 1.0f, 0.0f);
                ftCaptain_SpecialS_SetCall(fighter_gobj);
                fp->x80_self_vel.z = 0.0f;
                return;
            }
        } else if (entityClass == HSD_GOBJ_CLASS_ITEM) {
            if (itGetKind(detectGObj) < It_Kind_BombHei) {
                ASID = fp->action_id;
                switch (ASID) {
                case AS_CAPTAIN_SPECIALS_START:
                    ftCaptain_SpecialS_Switch1(fighter_gobj);
                    return;

                case AS_CAPTAIN_SPECIALAIRS_START:
                    ftCaptain_SpecialS_Switch2(fighter_gobj);
                    return;
                }
            } else if ((((itGetKind(detectGObj) >= It_Kind_Kuriboh) &&
                         (itGetKind(detectGObj) < It_Kind_Octarock_Stone)) ||
                        ((itGetKind(detectGObj) >= It_Kind_Old_Kuri) &&
                         (itGetKind(detectGObj) < It_Kind_Arwing_Laser)) ||
                        (itGetKind(detectGObj) == Pokemon_Random)))
            {
                switch (ASID = fp->action_id) {
                case AS_CAPTAIN_SPECIALS_START:
                    ftCaptain_SpecialS_Switch0(fighter_gobj);
                    return;

                case AS_CAPTAIN_SPECIALAIRS_START:
                    ftCaptain_SpecialS_Switch2(fighter_gobj);
                    return;

                default:
                    return;
                }
            }
        }
    }
}

// 0x800E384C
// https://decomp.me/scratch/F314k // Captain Falcon & Ganondorf's grounded
// Raptor Boost / Gerudo Dragon Start Animation callback
void ftCaptain_SpecialSStart_Anim(HSD_GObj* fighter_gobj)
{
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x800E3888
// https://decomp.me/scratch/mN21O // Captain Falcon & Ganondorf's grounded
// Raptor Boost / Gerudo Dragon Hit Animation callback
void ftCaptain_SpecialS_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    s32 ftKind;

    if ((u32) fp->sa.captain.x2230_isSpecialSGFX == false) {
        ftKind = func_800872A4(fighter_gobj);
        switch (ftKind) {
        case FTKIND_CAPTAIN:
            ef_Spawn(0x492, fighter_gobj, fp->x5E8_fighterBones[0x1].x0_jobj,
                     &fp->facing_dir);
            fp->sa.captain.x2230_isSpecialSGFX = true;
            break;

        case FTKIND_GANON:
            ef_Spawn(0x50E, fighter_gobj, fp->x5E8_fighterBones[0x1].x0_jobj,
                     &fp->facing_dir);
            fp->sa.captain.x2230_isSpecialSGFX = true;
            break;
        }
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x800E3964
// https://decomp.me/scratch/eEnc3 // Captain Falcon & Ganondorf's aerial Raptor
// Boost / Gerudo Dragon Start Animation callback
void ftCaptain_SpecialAirSStart_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp;
    Fighter* temp_fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = temp_fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = temp_fp;
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8007D60C(fp);
        if (0.0f == captainAttrs->specials_miss_landing_lag) {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 1, 0, 1.0f,
                      captainAttrs->specials_miss_landing_lag);
    }
}

// 0x800E39F0
// https://decomp.me/scratch/uEQaS // Captain Falcon & Ganondorf's aerial Raptor
// Boost / Gerudo Dragon Hit Animation callback
void ftCaptain_SpecialAirS_Anim(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;
    s32 ftKind;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if ((u32) fp->sa.captain.x2230_isSpecialSGFX == false) {
        ftKind = func_800872A4(fighter_gobj);
        switch (ftKind) {
        case FTKIND_CAPTAIN:
            ef_Spawn(0x493, fighter_gobj, fp->x5E8_fighterBones[0x1].x0_jobj,
                     &fp->facing_dir);
            fp->sa.captain.x2230_isSpecialSGFX = true;
            break;

        case FTKIND_GANON:
            ef_Spawn(0x50F, fighter_gobj, fp->x5E8_fighterBones[0x1].x0_jobj,
                     &fp->facing_dir);
            fp->sa.captain.x2230_isSpecialSGFX = true;
            break;
        }
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        func_8007D60C(fp);
        if (0.0f == captainAttrs->specials_hit_landing_lag) {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 1, 0, 1.0f,
                      captainAttrs->specials_hit_landing_lag);
    }
}

// Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start IASA
// callback
void ftCaptain_SpecialSStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit IASA
// callback
void ftCaptain_SpecialS_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Start IASA
// callback
void ftCaptain_SpecialAirSStart_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// Captain Falcon & Ganondorf's aerial Raptor Boost / Gerudo Dragon Hit IASA
// callback
void ftCaptain_SpecialAirS_IASA(HSD_GObj* fighter_gobj)
{
    return;
}

// Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Start
// Physics callback
void ftCaptain_SpecialSStart_Phys(HSD_GObj* fighter_gobj)
{
    func_80084FA8(fighter_gobj);
}

// Captain Falcon & Ganondorf's grounded Raptor Boost / Gerudo Dragon Hit
// Physics callback
void ftCaptain_SpecialS_Phys(HSD_GObj* fighter_gobj)
{
    func_80084FA8(fighter_gobj);
}

// 0x800E3B5C
// https://decomp.me/scratch/83Sca // Captain Falcon & Ganondorf's aerial Raptor
// Boost / Gerudo Dragon Start Physics callback
void ftCaptain_SpecialAirSStart_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_80085134(fighter_gobj);
    if ((u32) fp->x2204_ftcmd_var1 == 1U) {
        fp->captainVars.SpecialS.gravity -= captainAttrs->specials_grav;
        if (fp->captainVars.SpecialS.gravity <
            -captainAttrs->specials_terminal_vel)
        {
            fp->captainVars.SpecialS.gravity =
                -captainAttrs->specials_terminal_vel;
        }
        fp->x80_self_vel.y = fp->captainVars.SpecialS.gravity;
    }
}

// 0x800E3BD0
// https://decomp.me/scratch/Ud6Is // Captain Falcon & Ganondorf's aerial Raptor
// Boost / Gerudo Dragon Hit Physics callback
void ftCaptain_SpecialAirS_Phys(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_80085134(fighter_gobj);
    fp->captainVars.SpecialS.gravity -= captainAttrs->specials_grav;
    if (fp->captainVars.SpecialS.gravity < -captainAttrs->specials_terminal_vel)
    {
        fp->captainVars.SpecialS.gravity = -captainAttrs->specials_terminal_vel;
    }
    fp->x80_self_vel.y = fp->captainVars.SpecialS.gravity;
}

// 0x800E3C38
// https://decomp.me/scratch/wfD9m // Captain Falcon & Ganondorf's grounded
// Raptor Boost / Gerudo Dragon Start Collision callback
void ftCaptain_SpecialSStart_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = captainAttrs = getFtSpecialAttrs(fp);

    if ((u32) fp->x2208_ftcmd_var2 == 0U) {
        func_80084104(fighter_gobj);
        return;
    }
    if (func_80082708(fighter_gobj) == false) {
        efLib_DestroyAll(fighter_gobj);
        func_8007D60C(fp);
        if (0.0f == captainAttrs->specials_miss_landing_lag) {
            func_800CC730(fighter_gobj);
            return;
        }
        func_8007D468(fp);
        func_80096900(fighter_gobj, 1, 1, 0, 1.0f,
                      captainAttrs->specials_miss_landing_lag);
        return;
    }
    if (fp->x2200_ftcmd_var0 == 1) {
/// @todo Unused assignment.
#ifdef MUST_MATCH
        f32 facingDir = fp->facing_dir;
#endif

        if ((fp->facing_dir == +1 &&
             (fp->x6F0_collData.x134_envFlags & MPCOLL_RIGHTWALL)) ||
            (fp->facing_dir == -1 &&
             fp->x6F0_collData.x134_envFlags & MPCOLL_LEFTWALL))
        {
            efLib_DestroyAll(fighter_gobj);
            func_8008A2BC(fighter_gobj);
        }
    }
}

// 0x800E3D44
// https://decomp.me/scratch/FWGAL // Captain Falcon & Ganondorf's grounded
// Raptor Boost / Gerudo Dragon Hit Collision callback
void ftCaptain_SpecialS_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* temp_fp = GET_FIGHTER(fighter_gobj);
    Fighter* fp;
    ftCaptainAttributes* captainAttrs = temp_fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = temp_fp;
    if (func_80082708(fighter_gobj) == false) {
        efLib_DestroyAll(fighter_gobj);
        func_8007D60C(fp);
        if (0.0f == captainAttrs->specials_hit_landing_lag) {
            func_800CC730(fighter_gobj);
            return;
        }
        func_8007D468(fp);
        func_80096900(fighter_gobj, 1, 1, 0, 1.0f,
                      captainAttrs->specials_hit_landing_lag);
    }
}

// 0x800E3DE4
// https://decomp.me/scratch/laAkn // Captain Falcon & Ganondorf's aerial Raptor
// Boost / Gerudo Dragon Start Collision callback
void ftCaptain_SpecialAirSStart_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = fp->x2D4_specialAttributes;

    if (func_80081D0C(fighter_gobj) == true) {
        efLib_DestroyAll(fighter_gobj);
        func_800D5CB0(fighter_gobj, 0, captainAttrs->specials_miss_landing_lag);
    }
}

// 0x800E3E40
// https://decomp.me/scratch/3um8A // Captain Falcon & Ganondorf's aerial Raptor
// Boost / Gerudo Dragon Hit Collision callback
void ftCaptain_SpecialAirS_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftCaptainAttributes* captainAttrs = getFtSpecialAttrsD(fp);

    if (func_80081D0C(fighter_gobj) == true) {
        fp->xEC_ground_vel = fp->x80_self_vel.x;
        efLib_DestroyAll(fighter_gobj);
        func_800D5CB0(fighter_gobj, 0, captainAttrs->specials_hit_landing_lag);
    }
}
