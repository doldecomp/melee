/**
 * @file ftseakspecialhi.c
 * @brief Sheik's Up-B move: Vanish.
 * @details Implements Sheik's grounded and aerial Up-B recovery move (Vanish),
 * including initial blast explosion attack, intangibility, directional analog
 * stick steering, invisible travel, ledge snap detection, reappearance, and
 * landing lag. Module prefix: ftSk (Fighter: Sheik)
 */

#include "ftseakspecialhi.h"

#include <melee/ft/forward.h>

#include <math.h>
#include <placeholder.h>

#include "forward.h"
#include <melee/ef/efsync.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>
#include <melee/ft/kinds/ftCommon/ftCo_Pass.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itseakvanish.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbvector.h>
#include <sysdolphin/baselib/gobj.h>

static MotionFlags const ftSk_MF_SpecialHi_Coll =
    ftCommon_GroundAirColl_MF | Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus |
    Ft_MF_SkipHit;

/* 112ED8 */ static void fn_80112ED8(Fighter_GObj* gobj);
/* 112F48 */ static void ftSk_SpecialHi_80112F48(Fighter_GObj* gobj);
/* 112FA8 */ static void ftSk_SpecialHi_80112FA8(Fighter_GObj* gobj);
/* 113038 */ static void fn_80113038(Fighter_GObj* gobj);
/* 113324 */ static void ftSk_SpecialHi_80113324(Fighter_GObj* gobj);
/* 113390 */ static void ftSk_SpecialHi_80113390(Fighter_GObj* gobj);
/* 11374C */ static void ftSk_SpecialHi_8011374C(Fighter_GObj* gobj);
/* 1137C8 */ static void ftSk_SpecialHi_801137C8(Fighter_GObj* gobj);
/* 113838 */ static void ftSk_SpecialHi_80113838(Fighter_GObj* gobj);
/* 113A30 */ static void ftSk_SpecialHi_80113A30(Fighter_GObj* gobj);
/* 113E40 */ static void ftSk_SpecialHi_80113E40(Fighter_GObj* gobj);
/* 113EAC */ static void ftSk_SpecialHi_80113EAC(Fighter_GObj* gobj);
/* 113F68 */ static void ftSk_SpecialHi_80113F68(Fighter_GObj* gobj);

/**
 * @brief Accessory callback spawning the Vanish explosion hitbox and GFX.
 * @param gobj Fighter game object
 */
void fn_80112ED8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2219_b0) {
        ftSk_SpecialHi_80112F48(gobj);   // Spawn explosion hitbox item
        ftSk_SpecialHi_80112FA8(gobj);   // Spawn explosion particle effect
        ft_PlaySFX(fp, 115, 0x7F, 0x40); // Play explosion sound effect
    }
    fp->accessory4_cb = NULL;
}

/**
 * @brief Spawns the Vanish explosion item entity at Sheik's hip joint.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80112F48(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[4];
    {
        Vec3 pos;
        u8 _[4];
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, NULL, &pos);
        pos.z = 0;
        it_802B1C60(gobj, &pos, fp->facing_dir);
    }
}

/**
 * @brief Spawns the Vanish explosion visual particle effect (GFX ID 1284).
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80112FA8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    lb_8000B1CC(fp->parts[FtPart_HipN].joint, NULL, &pos);
    if (!fp->x2219_b0) {
        efSync_Spawn(1284, gobj, &pos);
        fp->x2219_b0 = true;
    }
    Fighter_SetEffectHitlagCallbacks(fp);
}

/**
 * @brief Accessory callback spawning the Vanish reappearance particle effect
 * (GFX ID 1285).
 * @param gobj Fighter game object
 */
void fn_80113038(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    if (!fp->x2219_b0) {
        lb_8000B1CC(fp->parts[FtPart_HipN].joint, NULL, &pos);
        efSync_Spawn(1285, gobj, &pos);
        fp->x2219_b0 = true;
    }
    Fighter_SetEffectHitlagCallbacks(fp);
    fp->accessory4_cb = NULL;
}

/**
 * @brief Enters grounded Up-B (Vanish) startup.
 * @details Changes motion state to ftSk_MS_SpecialHiStart_0 (state 355).
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[20];
    fp->cmd_vars[0] = 0;
    fp->mv.sk.specialhi.xC = 0;
    Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialHiStart_0, Ft_MF_None, 0.0f,
                              1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Enters aerial Up-B (Vanish) startup.
 * @details Applies initial vertical velocity boost (da->self_vel_y) and
 * changes motion state to ftSk_MS_SpecialAirHiStart_0 (state 358).
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* da = fp->dat_attrs;
    u8 _[20];
    fp->cmd_vars[0] = 0;
    fp->mv.sk.specialhi.xC = 0;
    fp->self_vel.y = da->self_vel_y;
    Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialAirHiStart_0, Ft_MF_None, 0,
                              1, 0, NULL);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Animation update for grounded Up-B startup.
 * @details On animation completion, transitions to teleport direction
 * calculation.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHiStart_0_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftSk_SpecialHi_80113838(gobj);
    }
}

/**
 * @brief Animation update for aerial Up-B startup.
 * @details On animation completion, transitions to aerial teleport direction
 * calculation.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHiStart_0_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftSk_SpecialHi_80113A30(gobj);
    }
}

/**
 * @brief Interrupt check for grounded Up-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHiStart_0_IASA(HSD_GObj* gobj) {}

/**
 * @brief Interrupt check for aerial Up-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHiStart_0_IASA(HSD_GObj* gobj) {}

/**
 * @brief Physics update for grounded Up-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHiStart_0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for aerial Up-B startup.
 * @details Applies special fall gravity and aerial drift.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHiStart_0_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;
    struct ftCo_DatAttrs* attributes2 = &fp->co_attrs;
    Vec2 vec;

    vec.x = attributes->x30;
    vec.y = attributes->x34;

    ftCommon_Fall(fp, vec.x, vec.y);
    ftCommon_CalcSelfAccel_Drift(fp);
}

/**
 * @brief Collision update for grounded Up-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHiStart_0_Coll(HSD_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftSk_SpecialHi_80113324(gobj);
    }
}

/**
 * @brief Collision update for aerial Up-B startup.
 * @details Checks for landing or ledge grab during startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHiStart_0_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool groundOrLedge = ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp));

    if (groundOrLedge) {
        ftSk_SpecialHi_80113390(gobj);
    } else {
        RETURN_IF(ftCliffCommon_80081298(gobj));
    }
}

/**
 * @brief State transition: Grounded -> Aerial for Up-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80113324(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x166, 0x0C4C508EU, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    fp->accessory4_cb = fn_80112ED8;
}

/**
 * @brief State transition: Aerial -> Grounded for Up-B startup.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80113390(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    ftCommon_AirToGroundStateChange(gobj, fp, 0x163, ftSk_MF_SpecialHi_Coll);
    fp->accessory4_cb = fn_80112ED8;
}

/**
 * @brief Animation update for grounded Up-B invisible travel phase.
 * @details Decrements invisible travel timer until 0, then enters
 * reappearance.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHiStart_1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->mv.sk.specialn.x0 -= 1;

    if (0 >= fp->mv.sk.specialn.x0) {
        ftSk_SpecialHi_80113EAC(gobj); // Enter grounded reappearance
    }
}

/**
 * @brief Animation update for aerial Up-B invisible travel phase.
 * @details Decrements invisible travel timer until 0, then enters aerial
 * reappearance.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHiStart_1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.sk.specialhi.x0 -= 1;

    if (fp->mv.sk.specialhi.x0 <= 0) {
        ftSk_SpecialHi_80113F68(gobj); // Enter aerial reappearance
    }
}

/**
 * @brief Interrupt check for grounded Up-B invisible travel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHiStart_1_IASA(HSD_GObj* gobj) {}

/**
 * @brief Interrupt check for aerial Up-B invisible travel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHiStart_1_IASA(HSD_GObj* gobj) {}

/**
 * @brief Physics update for grounded Up-B invisible travel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHiStart_1_Phys(HSD_GObj* gobj)
{
    ftCommon_SetSelfMovementFromGroundedMovement(gobj);
}

/**
 * @brief Physics update for aerial Up-B invisible travel.
 * @details Position is updated directly via teleport trajectory.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHiStart_1_Phys(HSD_GObj* gobj) {}

/**
 * @brief Collision update for grounded Up-B invisible travel.
 * @details Checks for wall collisions (bounces/transitions to reappearance) or
 * edge transitions.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHiStart_1_Coll(HSD_GObj* gobj)
{
    s32 env_flags;
    s32 env_flags_air;
    Fighter* fp;
    CollData* collData;

    fp = gobj->user_data;
    collData = &fp->coll_data;

    if (ft_80082708(gobj) == GA_Ground) {
        env_flags = collData->env_flags;

        // Wall collision triggers early reappearance
        if (env_flags & Collide_LeftWallMask ||
            env_flags & Collide_RightWallMask)
        {
            ftCommon_8007D60C(fp);
            ftSk_SpecialHi_80113F68(gobj);
            return;
        }
        ftSk_SpecialHi_8011374C(gobj);
        return;
    }
    env_flags_air = collData->env_flags;

    if (env_flags_air & Collide_LeftWallMask ||
        env_flags_air & Collide_RightWallMask)
    {
        ftSk_SpecialHi_80113EAC(gobj);
    }
}

/**
 * @brief Collision update for aerial Up-B invisible travel.
 * @details Handles ledge grabbing, landing detection, and teleport collision
 * resolution.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHiStart_1_Coll(HSD_GObj* gobj)
{
    s32 should_land;
    Fighter* fp;
    Fighter* fp2;
    ftSeakAttributes* attr;
    ftSeakAttributes* attr2;
    CollData* collData;
    s32 unused[6];

    fp = gobj->user_data;
    collData = &fp->coll_data;
    attr = fp->dat_attrs;
    ++fp->mv.sk.specialhi.xC;

    // Check if eligible to grab ledge or land on floor
    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp)) != 0) {
        fp2 = gobj->user_data;
        attr2 = fp2->dat_attrs;
        // Check if elapsed frames meet ledge grab threshold
        if ((f32) fp2->mv.sk.specialhi.xC >= attr2->x3C) {
            should_land = 1;
        } else if (ftCo_8009A134(gobj) != 0) {
            should_land = 0;
        } else {
            should_land = 1;
        }
        if (should_land != 0) {
            ftSk_SpecialHi_801137C8(gobj); // Enter landing state
            return;
        }
    }

    if (!ftCliffCommon_80081298(gobj)) {
        /// @todo float hack
        (void) 0.0f;
        (void) 1.0f;
        (void) S32_TO_F32;
        (void) MTXDegToRad(1);
        ftCommon_HandleTeleportCollisions(gobj, fp, collData, &attr->x50,
                                          ftSk_SpecialHi_80113F68);
    }
}

/**
 * @brief State transition: Grounded -> Aerial during invisible travel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_8011374C(Fighter_GObj* gobj)
{
    u32 fighterFlags;
    Fighter* fp = getFighterPlus(gobj);

    ftCommon_8007D60C(fp);

    fighterFlags =
        // 0xC4C
        Ft_MF_SkipModelPartVis | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
        Ft_MF_SkipModelFlags | Ft_MF_Unk27;

    fighterFlags =
        fighterFlags +
        // 0x508E
        (Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit |
         Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd);

    Fighter_ChangeMotionState(gobj, 0x167, fighterFlags, fp->cur_anim_frame,
                              0.0f, 0.0f, 0);

    fp->x2223_b4 = true;
    fp->invisible = true;
}

/**
 * @brief State transition: Aerial -> Grounded landing during invisible travel.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_801137C8(Fighter_GObj* gobj)
{
    u32 fighterFlags;
    Fighter* fp = gobj->user_data;

    ftCommon_8007D7FC(fp);

    fighterFlags =
        // 0xC4C
        Ft_MF_SkipModelPartVis | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
        Ft_MF_SkipModelFlags | Ft_MF_Unk27;

    fighterFlags =
        fighterFlags +
        // 0x508E
        (Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit |
         Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd);

    Fighter_ChangeMotionState(gobj, 0x164, fighterFlags, fp->cur_anim_frame,
                              0.0, 0.0, NULL);
    fp->invisible = true;
}

/**
 * @brief Helper initializing invisible travel state.
 * @details Sets travel timer (attributes->x38), consumes double jumps, sets
 * intangibility, makes model invisible, and sets explosion callback.
 * @param gobj Fighter game object
 */
static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes;
    attributes = fp->dat_attrs;
    fp->mv.sk.specialhi.x0 = attributes->x38;
    fp->x1968_jumpsUsed = (u8) fp->co_attrs.max_jumps;
    fp->x2223_b4 = 1;
    ftColl_8007B62C(gobj, 2); // Set intangible hurtbox state
    fp->invisible = 1;
    fp->accessory4_cb = fn_80112ED8;
}

/**
 * @brief PowerPC Newton-Raphson fast inverse square root helper.
 * @param x Input float
 * @return float Square root of x
 */
static inline float my_sqrtf(float x)
{
    FORCE_PAD_STACK_32;
    {
        volatile float y;

        if (x > 0.0f) {
            double guess = __frsqrte(x);
            guess = 0.5 * guess * (3.0 - guess * guess * x);
            guess = 0.5 * guess * (3.0 - guess * guess * x);
            guess = 0.5 * guess * (3.0 - guess * guess * x);
            y = (float) (x * guess);
            return y;
        }
        return x;
    }
}

/**
 * @brief Calculates grounded Vanish teleport steering from analog stick.
 * @details Reads stick angle and magnitude. If aimed down into ground,
 * converts to grounded sliding teleport; otherwise initiates aerial teleport
 * trajectory.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80113838(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;
    CollData* coll = &fp->coll_data;
    f32 stick_mag;
    f32 stick_y, stick_x;
    stick_x = fp->input.lstick[0].x;
    stick_y = fp->input.lstick[0].y;
    stick_x = stick_x * stick_x;
    stick_y = stick_y * stick_y;

    stick_mag = my_sqrtf(stick_x + stick_y);

    if (stick_mag > 1.0f) {
        stick_mag = 1.0f;
    }

    // Check stick deadzone threshold (attributes->x40)
    if (!(stick_mag < attributes->x40)) {
        Vec3* normal = &coll->floor.normal;
        {
            Vec3 lstick;
            lstick.x = fp->input.lstick[0].x;
            lstick.y = fp->input.lstick[0].y;
            lstick.z = 0.0f;
            // Angle between floor normal and stick direction < 90 deg
            if (!(lbVector_AngleXY(normal, &lstick) < (float) M_PI_2)) {
                if (ftCo_8009A134(gobj) == 0) {
                    f32 stick_angle;
                    ftCommon_UpdateFacing(fp);
                    stick_angle =
                        atan2f(fp->input.lstick[0].y,
                               fp->input.lstick[0].x * fp->facing_dir);
                    fp->mv.sk.specialhi.vel.x = lstick.x;
                    fp->mv.sk.specialhi.vel.y = lstick.y;
                    {
                        f32 speed;
                        // Velocity = (scale * stick_mag + base) * cos(angle)
                        speed =
                            ((attributes->x44 * stick_mag) + attributes->x48) *
                            cosf(stick_angle);
                        fp->gr_vel = fp->facing_dir * speed;
                    }
                    Fighter_ChangeMotionState(gobj, 0x164, Ft_MF_None, 35.0f,
                                              1.0f, 0.0f, NULL);
                    ftAnim_8006EBA4(gobj);
                    ftAnim_SetAnimRate(gobj, 0.0f);
                    inlineA0(gobj);
                    return;
                }
            }
        }
    }
    ftCommon_8007D60C(fp);
    ftSk_SpecialHi_80113A30(gobj);
}

/**
 * @brief Calculates aerial Vanish teleport trajectory from analog stick input.
 * @details Reads stick angle & magnitude, computes self velocities:
 * vel = (attributes->x44 * stick_mag + attributes->x48) * (cos/sin),
 * updates facing direction, and enters invisible travel state 0x167.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80113A30(Fighter_GObj* gobj)
{
    f32 stick_y;
    f32 stick_x;
    f32 stick_abs_x;
    f32 travel_angle;
    f32 clamped_stick_mag;
    f32 stick_y_sq;
    f32 stick_mag;
    Fighter* fp = gobj->user_data;
    ftSeakAttributes* attributes = fp->dat_attrs;

    stick_x = fp->input.lstick[0].x;
    stick_y = fp->input.lstick[0].y;
    stick_x = stick_x * stick_x;
    stick_y_sq = stick_y * stick_y;
    stick_mag = my_sqrtf(stick_x + stick_y_sq);

    clamped_stick_mag = stick_mag;
    if (stick_mag > 1.0f) {
        clamped_stick_mag = 1.0f;
    }
    if (clamped_stick_mag > attributes->x40) {
        stick_abs_x = fp->input.lstick[0].x;
        if (stick_abs_x < 0.0f) {
            stick_abs_x = -stick_abs_x;
        }
        if (stick_abs_x > 0.001f) {
            ftCommon_UpdateFacing(fp);
        }
        travel_angle = atan2f(fp->input.lstick[0].y,
                              fp->input.lstick[0].x * fp->facing_dir);
        fp->mv.sk.specialhi.vel.x = fp->input.lstick[0].x;
        fp->mv.sk.specialhi.vel.y = fp->input.lstick[0].y;
    } else {
        // Default trajectory: straight up (pi/2)
        ftCommon_8007DA24(fp);
        travel_angle = M_PI / 2;
        fp->mv.sk.specialhi.vel.x = 0.0f;
        fp->mv.sk.specialhi.vel.y = 1.0f;
        clamped_stick_mag = 1.0f;
    }
    fp->self_vel.x =
        fp->facing_dir *
        (((attributes->x44 * clamped_stick_mag) + attributes->x48) *
         cosf(travel_angle));
    fp->self_vel.y =
        ((attributes->x44 * clamped_stick_mag) + attributes->x48) *
        sinf(travel_angle);
    Fighter_ChangeMotionState(gobj, 0x167, 0U, 35.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftAnim_SetAnimRate(gobj, 0.0f);
    inlineA0(gobj);
}

/**
 * @brief Animation update for grounded Up-B reappearance.
 * @details On animation completion, transitions to Wait (idle).
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_Anim(HSD_GObj* gobj)
{
    FORCE_PAD_STACK_8;

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj); // Enter Wait / Idle
    }
}

/**
 * @brief Animation update for aerial Up-B reappearance.
 * @details On animation completion, enters FallSpecial (freefall) with landing
 * lag parameters.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        float x, y;
        x = attributes->x58; // Freefall landing lag
        y = attributes->x5C;
        ftCo_80096900(gobj, 1, 0, 1, x, y);
    }
}

/**
 * @brief Interrupt check for grounded Up-B reappearance.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_IASA(HSD_GObj* gobj) {}

/**
 * @brief Interrupt check for aerial Up-B reappearance.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHi_IASA(HSD_GObj* gobj) {}

/**
 * @brief Physics update for grounded Up-B reappearance.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics update for aerial Up-B reappearance.
 * @details Decelerates vertical velocity, applies fall and drift clamps when
 * cmd_vars set.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    if (fp->cmd_vars[0] != 0) {
        ftCommon_FallBasic(fp);
        ftCommon_ClampSelfVelX(fp,
                               attributes->x4C * fp->co_attrs.air_drift_max);
        // UPDATE x4c TO F32!
        return;
    } else {
        float vel_y = fp->self_vel.y;
        fp->self_vel.y = vel_y - (vel_y / 10.0f); // Exponential deceleration
    }
    ftCommon_CalcSelfAccel_DeaccelAir(fp);
}

/**
 * @brief Collision update for grounded Up-B reappearance.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_Coll(HSD_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftSk_SpecialHi_80113E40(gobj);
    }
}

/**
 * @brief Collision update for aerial Up-B reappearance.
 * @details Checks for landing into FallSpecial landing lag or ledge grab.
 * @param gobj Fighter game object
 */
void ftSk_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;

    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        ftCo_LandingFallSpecial_Enter(gobj, false, attributes->x5C);
        return;
    }
    if (!ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/**
 * @brief State transition: Grounded -> Aerial for Up-B reappearance.
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80113E40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x168, 0x0C4C508AU, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
    fp->accessory4_cb = fn_80113038;
}

/**
 * @brief Helper resetting velocities and making Sheik visible upon
 * reappearance.
 * @param gobj Fighter game object
 */
static void ftSk_SpecialHi_80113EAC_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.walk.fast_anim_frame = fp->self_vel.x;
    fp->mv.co.common.x14 = fp->self_vel.y;
    fp->mv.co.common.x18 = fp->gr_vel;
    fp->gr_vel = fp->self_vel.x = fp->self_vel.y = 0.0f;
    fp->invisible = false;
    fp->accessory4_cb = fn_80113038;
}

/**
 * @brief Enters grounded Up-B reappearance state (state 0x165).
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80113EAC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;
    Fighter_ChangeMotionState(gobj, 0x165, 0U, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    ftSk_SpecialHi_80113EAC_inline(gobj);
    fp->gr_vel = fp->mv.co.common.x18 * attributes->x54;
}

/**
 * @brief Helper resetting velocities and making Sheik visible upon aerial
 * reappearance.
 * @param gobj Fighter game object
 */
static void ftSk_SpecialHi_80113F68_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.walk.fast_anim_frame = fp->self_vel.x;
    fp->mv.co.common.x14 = fp->self_vel.y;
    fp->mv.co.common.x18 = fp->gr_vel;
    fp->gr_vel = fp->self_vel.x = fp->self_vel.y = 0.0f;
    fp->invisible = false;
    fp->accessory4_cb = fn_80113038;
}

/**
 * @brief Enters aerial Up-B reappearance state (ftSk_MS_SpecialAirHi).
 * @param gobj Fighter game object
 */
void ftSk_SpecialHi_80113F68(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSeakAttributes* attributes = fp->dat_attrs;
    Fighter_ChangeMotionState(gobj, ftSk_MS_SpecialAirHi, 0U, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftSk_SpecialHi_80113F68_inline(gobj);
    fp->self_vel.x = fp->mv.co.walk.fast_anim_frame * attributes->x54;
    fp->self_vel.y = fp->mv.co.common.x14 * attributes->x54;
}
