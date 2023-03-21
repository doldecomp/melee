#include "ftfox.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftparts.h"

#include <trigf.h>
#include <baselib/gobjproc.h>

/// @todo Move elsewhere.
#define HALF_PI32 (1.5707963705062866f)

/// @todo Move elsewhere.
#define DOUBLE_PI32 (6.2831854820251465f)

void ftFox_SpecialHi_CreateLaunchGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2219_flag.bits.b0 == false) {
        ef_Spawn(0x48C, gobj,
                 fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj);

        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

void ftFox_SpecialHi_CreateChargeGFX(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2219_flag.bits.b0 == false) {
        ef_Spawn(0x48B, gobj,
                 fp->x5E8_fighterBones[func_8007500C(fp, 1)].x0_jobj);

        fp->x2219_flag.bits.b0 = true;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

void ftFox_SpecialHi_StartAction(HSD_GObj* gobj)
{
    Fighter* fp;
    ftFoxAttributes* foxAttrs;

    fp = GET_FIGHTER(gobj);
    foxAttrs = getFtSpecialAttrs(fp);

    fp->sv.fx.SpecialHi.gravityDelay =
        (s32) foxAttrs->x54_FOX_FIREFOX_GRAVITY_DELAY;
    fp->xEC_ground_vel /= foxAttrs->x58_FOX_FIREFOX_VEL_X;

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALHI_HOLD, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);

    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialHi_CreateChargeGFX;
}

void ftFox_SpecialAirHi_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    fp->sv.fx.SpecialHi.gravityDelay =
        (s32) foxAttrs->x54_FOX_FIREFOX_GRAVITY_DELAY;
    fp->x80_self_vel.x /= foxAttrs->x58_FOX_FIREFOX_VEL_X;
    fp->x80_self_vel.y = 0.0f;

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALHI_HOLDAIR, 0, NULL,
                                       0.0f, 1.0f, 0.0f);

    func_8006EBA4(gobj);

    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialHi_CreateChargeGFX;
}

void ftFox_SpecialHi_RotateModel(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007592C(fp, func_8007500C(fp, 2),
                  DOUBLE_PI32 - fp->sv.fx.SpecialHi.rotateModel);
}

void ftFox_SpecialHiHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((s32) fp->ground_or_air == GA_Air) {
            ftFox_SpecialAirHi_Action(gobj);
            return;
        }

        ftFox_SpecialAirHi_AirToGround(gobj);
    }
}

void ftFox_SpecialHiHoldAir_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((s32) fp->ground_or_air == GA_Air) {
            ftFox_SpecialAirHi_Action(gobj);
            return;
        }
        ftFox_SpecialAirHi_AirToGround(gobj);
    }
}

void ftFox_SpecialHiHold_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFox_SpecialHiHoldAir_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFox_SpecialHiHold_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void ftFox_SpecialHiHoldAir_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;
    attr* ftAttrs = &fp->x110_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->sv.fx.SpecialHi.gravityDelay != 0) {
        fp->sv.fx.SpecialHi.gravityDelay -= 1;
    } else {
        func_8007D494(fp, foxAttrs->x60_FOX_FIREFOX_FALL_ACCEL,
                      ftAttrs->x170_TerminalVelocity);
    }

    func_8007CE94(fp, foxAttrs->x5C_FOX_FIREFOX_AIR_MOMENTUM_PRESERVE_X);
}

void ftFox_SpecialHiHold_Coll(HSD_GObj* gobj)
{
    if (func_80082708(gobj) == false) {
        ftFox_SpecialHiHold_GroundToAir(gobj);
    }
}

void ftFox_SpecialHiHoldAir_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 facingDir;

    /// @todo Ternary operator should be possible here somehow.
    if (fp->facing_dir < 0.0f)
        facingDir = -1;
    else
        facingDir = 1;

    if (EnvColl_CheckGroundAndLedge(gobj, facingDir) != false) {
        ftFox_SpecialHiHoldAir_AirToGround(gobj);
        return;
    }

    if (func_80081298(gobj))
        return;
}

void ftFox_SpecialHiHold_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALHI_HOLDAIR,
                                       FTFOX_SPECIALHI_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialHi_CreateChargeGFX;
}

void ftFox_SpecialHiHoldAir_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALHI_HOLD,
                                       FTFOX_SPECIALHI_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialHi_CreateChargeGFX;

    func_8007D468(fp);
}

void ftFox_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Common inline with #ftFox_SpecialAirHi_Anim.
    fp->sv.fx.SpecialHi.travelFrames--;

    if (fp->sv.fx.SpecialHi.travelFrames <= 0) {
        if (fp->ground_or_air == GA_Air) {
            ftFox_SpecialHiLanding_GroundToAir(gobj);
            return;
        }

        ftFox_SpecialHiFall_AirToGround(gobj);
    }
}

void ftFox_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->sv.fx.SpecialHi.travelFrames--;

    if (fp->sv.fx.SpecialHi.travelFrames <= 0) {
        if (fp->ground_or_air == GA_Air) {
            ftFox_SpecialHiLanding_GroundToAir(gobj);
            return;
        }

        ftFox_SpecialHiFall_AirToGround(gobj);
    }
}

void ftFox_SpecialHi_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFox_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    return;
}

void ftFox_SpecialHi_Phys(HSD_GObj* gobj)
{
    /// @todo Possibly common inline with #ftFox_SpecialAirHi_Phys.
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    fp->sv.fx.SpecialHi.unk++;

    if (fp->sv.fx.SpecialHi.unk >= foxAttrs->x70_FOX_FIREFOX_DURATION_END)
        func_8007C930(fp, foxAttrs->x78_FOX_FIREFOX_REVERSE_ACCEL);

    func_8007CB74(gobj);
}

void ftFox_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFoxAttributes* foxAttrs = foxAttrs = getFtSpecialAttrs(fp);

    fp->sv.fx.SpecialHi.unk++;

    if (fp->sv.fx.SpecialHi.unk >= foxAttrs->x70_FOX_FIREFOX_DURATION_END) {
        fp->x80_self_vel.x =
            -((fp->facing_dir * (foxAttrs->x78_FOX_FIREFOX_REVERSE_ACCEL *
                                 cosf(fp->sv.fx.SpecialHi.rotateModel))) -
              fp->x80_self_vel.x);
        fp->x80_self_vel.y = -((foxAttrs->x78_FOX_FIREFOX_REVERSE_ACCEL *
                                sinf(fp->sv.fx.SpecialHi.rotateModel)) -
                               fp->x80_self_vel.y);
    }
}

void ftFox_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->x6F0_collData;

    fp->sv.fx.SpecialHi.unk2 += 1;

    if (func_80082708(gobj) == false) {
        ftFox_SpecialHi_GroundToAir(gobj);
        return;
    }

    if (collData->x134_envFlags & 0x18000) {
        fp->sv.fx.SpecialHi.rotateModel =
            atan2f(-collData->x14C_ground.normal.x * fp->facing_dir,
                   collData->x14C_ground.normal.y);
        ftFox_SpecialHi_RotateModel(gobj);
    }
}

static inline bool ftFox_SpecialHi_IsBound(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    if (fp->sv.fx.SpecialHi.unk2 >= foxAttrs->x6C_FOX_FIREFOX_BOUNCE_VAR)
        return true;
    else if (func_8009A134(gobj) != false)
        return false;
    else
        return true;
}

/// @todo Rework this entire match.
void ftFox_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    f32 facingDir;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = foxAttrs = getFtSpecialAttrs(fp);
    CollData* collData = collData = getFtColl(fp);

    if (EnvColl_CheckGroundAndLedge(gobj, CLIFFCATCH_BOTH) != false) {
        if (ftFox_SpecialHi_IsBound(gobj) != false) {
            if ((!(collData->x134_envFlags & 0x18000)) ||
                (!(lbvector_AngleXY(&collData->x14C_ground.normal,
                                    &fp->x80_self_vel) <
                   (0.01745329238474369f *
                    (90.0f + foxAttrs->x94_FOX_FIREFOX_BOUND_ANGLE)))))
            {
                ftFox_SpecialHiBound_Action(gobj);
                return;
            } else {
                goto facingDir;
            }
        }
    }

    /** @remarks Not a single line of this entire function makes the slightest
     * sliver of sense but it matches so whatever :D
     * @todo This match is definitely fake.
     */
    if (func_80081298(gobj) == false) {
        s32 envFlags = collData->x134_envFlags;
        f32 var;
        do {
            if (envFlags & 0x6000) {
                var = lbvector_AngleXY(&collData->x188_ceiling.normal,
                                       &fp->x80_self_vel);
            } else if (envFlags & 0x3F) {
                var = lbvector_AngleXY(&collData->x160_rightwall.normal,
                                       &fp->x80_self_vel);
            } else if (envFlags & 0xFC0) {
                var = lbvector_AngleXY(&collData->x174_leftwall.normal,
                                       &fp->x80_self_vel);
            } else {
                if (((!fp->x80_self_vel.x) && (!fp->x80_self_vel.x)) &&
                    (!fp->x80_self_vel.x)) // ??????
                {
                }
                break;
            }

            if (var < (0.01745329238474369f *
                       (90.0f + foxAttrs->x94_FOX_FIREFOX_BOUND_ANGLE)))

                goto facingDir;
            else
                continue;

        } while (false); // What?

        return;

        {
        facingDir:
            if (fp->x80_self_vel.x >= 0.0f)
                facingDir = 1.0f;
            else
                facingDir = -1.0f;

            fp->facing_dir = facingDir;
            fp->sv.fx.SpecialHi.rotateModel = atan2f(
                fp->x80_self_vel.y, fp->x80_self_vel.x * fp->facing_dir);
            ftFox_SpecialHi_RotateModel(gobj);
        }
    }
}

void ftFox_SpecialHi_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_8007D60C(fp);

    Fighter_ActionStateChange_800693AC(
        gobj, AS_FOX_SPECIALAIRHI,
        (FtStateChange_SkipUpdateHit | FTFOX_SPECIALHI_COLL_FLAG), NULL,
        fp->x894_currentAnimFrame, 1.0f, 0.0f);

    fp->x2223_flag.bits.b4 = true;
    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialHi_CreateLaunchGFX;
}

void ftFox_SpecialAirHi_AirToGround(HSD_GObj* gobj)
{
    Vec3 sp20;
    ftFoxAttributes* foxAttrs;
    Fighter* fp;
    CollData* collData;
    ftFoxAttributes* tempAttrs;
    f32 temp_stick;
    f32 stick_x;
    f32 stick_y;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = getFighter(gobj);
    stick_y = fp->input.x624_lstick_y;

    collData = getFtColl(fp);
    foxAttrs = fp->x2D4_specialAttributes;

    if (stick_y < 0.0f) {
        stick_y = -stick_y;
    }
    temp_stick = fp->input.x620_lstick_x;
    stick_x = stickGetDir(fp->input.x620_lstick_x, 0.0f);

    if (!((stick_x + stick_y) <
          foxAttrs->x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN))
    {
        sp20.x = temp_stick;
        sp20.y = fp->input.x624_lstick_y;
        sp20.z = 0.0f;

        if (!(lbvector_AngleXY(&collData->x14C_ground.normal, &sp20) <
              HALF_PI32) &&
            (func_8009A134(gobj) == false))
        {
            func_8007D9FC(fp);

            Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALHI, 0, NULL,
                                               0.0f, 1.0f, 0.0f);

            tempAttrs = fp->x2D4_specialAttributes;
            fp->x2223_flag.bits.b4 = 1;

            fp->sv.fx.SpecialHi.travelFrames =
                (u32) (s32) tempAttrs->x68_FOX_FIREFOX_DURATION;

            fp->sv.fx.SpecialHi.unk = 0.0f;
            fp->sv.fx.SpecialHi.unk2 = 0.0f;

            fp->xEC_ground_vel =
                foxAttrs->x74_FOX_FIREFOX_SPEED * fp->facing_dir;

            fp->sv.fx.SpecialHi.rotateModel =
                atan2f(-collData->x14C_ground.normal.x * fp->facing_dir,
                       collData->x14C_ground.normal.y);

            ftFox_SpecialHi_RotateModel(gobj);
            fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialHi_CreateLaunchGFX;
            fp->cb.x21F8_callback = func_8007F76C;
            return;
        }
    }
    func_8007D60C(fp);
    ftFox_SpecialAirHi_Action(gobj);
}

// 0x800E7C98
// https://decomp.me/scratch/k5tbJ // Fox & Falco's aerial Firefox/Firebird
// Launch Action State handler
void ftFox_SpecialAirHi_Action(HSD_GObj* gobj)
{
    ftFoxAttributes* foxAttrs;
    attr* ftAttrs;
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* tempAttrs;
    f32 stick_x;
    f32 stick_y;
    f32 temp_stick;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    ftAttrs = &fp->x110_attr;
    foxAttrs = fp->x2D4_specialAttributes;

    stick_y = stickGetDir(fp->input.x624_lstick_y, 0.0f);

    temp_stick = fp->input.x620_lstick_x;

    stick_x = stickGetDir(temp_stick, 0.0f);

    if ((stick_x + stick_y) >=
        foxAttrs->x64_FOX_FIREFOX_DIRECTION_STICK_RANGE_MIN)
    {
        if (temp_stick < 0.0f) {
            temp_stick = -temp_stick;
        }
        if (temp_stick > foxAttrs->x88_FOX_FIREFOX_FACING_STICK_RANGE_MIN) {
            func_8007D9FC(fp);
        }
        fp->sv.fx.SpecialHi.rotateModel = atan2f(
            fp->input.x624_lstick_y, fp->input.x620_lstick_x * fp->facing_dir);
    } else {
        fp->sv.fx.SpecialHi.rotateModel = HALF_PI32;
    }

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALAIRHI, 0, NULL,
                                       0.0f, 1.0f, 0.0f);

    tempAttrs = fp->x2D4_specialAttributes;
    fp->x2223_flag.bits.b4 = 1;

    fp->sv.fx.SpecialHi.travelFrames =
        (u32) (s32) tempAttrs->x68_FOX_FIREFOX_DURATION;
    fp->sv.fx.SpecialHi.unk = 0;
    fp->sv.fx.SpecialHi.unk2 = 0;

    fp->x80_self_vel.x =
        fp->facing_dir * (foxAttrs->x74_FOX_FIREFOX_SPEED *
                          cosf(fp->sv.fx.SpecialHi.rotateModel));
    fp->x80_self_vel.y = foxAttrs->x74_FOX_FIREFOX_SPEED *
                         sinf(fp->sv.fx.SpecialHi.rotateModel);
    ftFox_SpecialHi_RotateModel(gobj);
    fp->cb.x21F8_callback = func_8007F76C;
    fp->cb.x21BC_callback_Accessory4 = ftFox_SpecialHi_CreateLaunchGFX;
    fp->x1968_jumpsUsed = ftAttrs->x168_MaxJumps;
}

// 0x800E7E3C
// https://decomp.me/scratch/FiAfN // Fox & Falco's grounded Firefox/Firebird
// End Animation callback
void ftFox_SpecialHiLanding_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

// 0x800E7E78
// https://decomp.me/scratch/COhLZ // Fox & Falco's aerial Firefox/Firebird End
// Animation callback
void ftFox_SpecialHiFall_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_80096900(gobj, 1, 0, true,
                      foxAttrs->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      foxAttrs->x90_FOX_FIREFOX_LANDING_LAG);
    }
}

// 0x800E7ED8 - Fox & Falco's grounded Firefox/Firebird End IASA callback
void ftFox_SpecialHiLanding_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E7EDC - Fox & Falco's aerial Firefox/Firebird End IASA callback
void ftFox_SpecialHiFall_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E7EE0
// https://decomp.me/scratch/eHUMt // Fox & Falco's grounded Firefox/Firebird
// End Physics callback
void ftFox_SpecialHiLanding_Phys(HSD_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftFoxAttributes* foxAttrs = getFtSpecialAttrs(fp);

    func_8007C930(fp, foxAttrs->x7C_FOX_FIREFOX_GROUND_MOMENTUM_END);
    func_8007CB74(gobj);
}

// 0x800E7F20 - Fox & Falco's aerial Firefox/Firebird End Physics callback
void ftFox_SpecialHiFall_Phys(HSD_GObj* gobj)
{
    func_80084DB0(gobj);
}

// 0x800E7F40
// https://decomp.me/scratch/JEGS6 // Fox & Falco's grounded Firefox/Firebird
// End Collision callback
void ftFox_SpecialHiLanding_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    if (func_80082708(gobj) == false) {
        func_80096900(gobj, 1, 0, true,
                      foxAttrs->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      foxAttrs->x90_FOX_FIREFOX_LANDING_LAG);
    }
}

// 0x800E7FA0
// https://decomp.me/scratch/0Veb7 // Fox & Falco's aerial Firefox/Firebird End
// Collision callback
void ftFox_SpecialHiFall_Coll(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (EnvColl_CheckGroundAndLedge(gobj, CLIFFCATCH_BOTH) != false) {
        ftFox_SpecialHiFall_Action(gobj);
        return;
    }
    if (func_80081298(gobj))
        return;
}

// 0x800E7FF0
// https://decomp.me/scratch/IQ1YX // Fox & Falco's aerial Firefox/Firebird End
// Action State handler
void ftFox_SpecialHiFall_Action(HSD_GObj* gobj)
{
    func_8007D7FC(GET_FIGHTER(gobj));
    Fighter_ActionStateChange_800693AC(
        gobj, AS_FOX_SPECIALHI_LANDING,
        (FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd), NULL,
        13.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
}

// 0x800E8048
// https://decomp.me/scratch/rGuhz // Fox & Falco's ground -> air
// Firefox/Firebird End Action State handler
void ftFox_SpecialHiFall_AirToGround(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007DB24(gobj);
    if ((s32) fp->ground_or_air == GA_Air) {
        func_8007D7FC(fp);
    }
    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALHI_LANDING, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    fp->cb.x21F8_callback = func_8007F76C;
}

// 0x800E80C0
// https://decomp.me/scratch/YjAsa // Fox & Falco's Firefox/Firebird End ->
// Rebound Collision thing
void ftFox_SpecialHiLanding_GroundToAir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007DB24(gobj);

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALHI_FALL, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    fp->cb.x21F8_callback = func_8007F76C;
}

// 0x800E8124
// https://decomp.me/scratch/SSvDi // Fox & Falco's Firefox/Firebird Rebound
// Animation callback
void ftFox_SpecialHiBound_Anim(HSD_GObj* gobj)
{
    attr* ftAttrs;
    Fighter* fp;
    ftFoxAttributes* foxAttrs;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp = GET_FIGHTER(gobj);
    ftAttrs = &fp->x110_attr;
    foxAttrs = fp->x2D4_specialAttributes;

    if (((u32) fp->x2200_ftcmd_var0 != 0U) &&
        ((s32) fp->ground_or_air == GA_Air))
    {
        func_80096900(gobj, 1, 0, true,
                      foxAttrs->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                      foxAttrs->x90_FOX_FIREFOX_LANDING_LAG);
        fp->x1968_jumpsUsed = (u8) ftAttrs->x168_MaxJumps;
        return;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((s32) fp->ground_or_air == GA_Air) {
            func_80096900(gobj, 1, 0, true,
                          foxAttrs->x8C_FOX_FIREFOX_FREEFALL_MOBILITY,
                          foxAttrs->x90_FOX_FIREFOX_LANDING_LAG);
            fp->x1968_jumpsUsed = (u8) ftAttrs->x168_MaxJumps;
            return;
        }
        func_8008A2BC(gobj);
    }
}

// 0x800E81FC - Fox & Falco's Firefox/Firebird Rebound IASA callback
void ftFox_SpecialHiBound_IASA(HSD_GObj* gobj)
{
    return;
}

// 0x800E8200
// https://decomp.me/scratch/nIsRU // Fox & Falco's Firefox/Firebird Rebound
// Physics callback
void ftFox_SpecialHiBound_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool ground_or_air = ftGetGroundAir(fp);

    if (ground_or_air == GA_Air) {
        func_800851C0(gobj);
        func_8007CF58(fp);
        return;
    }
    func_80084F3C(gobj);
}

// 0x800E824C
// https://decomp.me/scratch/iGtSK // Fox & Falco's Firefox/Firebird Rebound
// Collision callback
void ftFox_SpecialHiBound_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 cliffCatchDir;

    if ((s32) fp->ground_or_air == GA_Air) {
        if (fp->facing_dir < 0.0f) {
            cliffCatchDir = -1;
        } else {
            cliffCatchDir = 1;
        }

        if (EnvColl_CheckGroundAndLedge(gobj, cliffCatchDir) != false) {
            func_8007D7FC(fp);
            return;
        }

        if (func_80081298(gobj) != false) {
            return;
        }
    }

    else
    {
        func_80084104(gobj);
    }
}

inline void ftFox_SpecialHiBound_SetVars(HSD_GObj* gobj)
{
    vf32 f; // I have a feeling this is a Vec3 struct however
    Fighter* fp = fp = gobj->user_data;
    CollData* collData = collData = getFtColl(fp);

    if (fp->x6F0_collData.x134_envFlags & 0x18000) {
        f = -atan2f(collData->x14C_ground.normal.x,
                    collData->x14C_ground.normal.y);
    } else {
        f = 0.0f;
    }
    ef_Spawn(0x406, gobj, &fp->xB0_pos, &f);
    fp->x2219_flag.bits.b0 = true;
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 0x800E82E4
// https://decomp.me/scratch/ckSnm // Fox & Falco's Firefox/Firebird Rebound
// Action State handler
void ftFox_SpecialHiBound_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftFoxAttributes* foxAttrs = fp->x2D4_specialAttributes;

    Fighter_ActionStateChange_800693AC(gobj, AS_FOX_SPECIALHI_BOUND, 0, NULL,
                                       0.0f, 1.0f, 0.0f);
    func_8006EBA4(gobj);
    fp->cb.x21F8_callback = func_8007F76C;
    fp->x80_self_vel.x *= foxAttrs->x84_FOX_FIREFOX_BOUND_VEL_X;
    fp->x2200_ftcmd_var0 = 0;
    ftFox_SpecialHiBound_SetVars(gobj);
}
