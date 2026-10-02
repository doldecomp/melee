/**
 * @file ftpopospecialhi.c
 * @brief Up-B: Belay (Tether recovery & partner throw)
 * @details Implements grounded and aerial Belay move logic for Ice Climbers
 * (Popo/Nana). In partnered mode, Popo throws Nana into the air, and Nana then
 * yanks Popo up with the rope tether, propelling Popo into a high recovery
 * rise. If Nana is missing or out of range, Popo performs a solo hop with
 * minimal height and enters helpless fall. Module prefix: ftPp
 */

#include "ftpopospecialhi.h"

#include <melee/ft/forward.h>

#include "ftpopo.h"
#include "ftpopospecials.h"
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/kinds/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/kinds/ftCommon/ftCo_Landing.h>
#include <melee/ft/kinds/ftCommon/inlines.h>
#include <melee/ft/kinds/ftNana/ftnana.h>
#include <melee/it/kinds/itclimbersstring.h>
#include <melee/it/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbvector.h>
#include <melee/pl/player.h>

#ifdef MUST_MATCH
static void sdata2_order(void)
{
    (void) 0.0f;
    (void) 0.5;
    (void) 3.0;
    (void) 3.0f;
    (void) 5.0f;
    (void) 1.0f;
    (void) -1.0f;
    (void) 1.5707963267948966;
}
#endif

/**
 * @brief Fast square root using PowerPC reciprocal square root estimate
 * @details Uses __frsqrte with 3 Newton-Raphson refinement iterations:
 * guess = 0.5 * guess * (3.0 - guess * guess * x)
 * @param x Input float
 * @param y Output float pointer
 * @return Square root of x
 */
static inline float my_sqrtf(float x, volatile float* y)
{
    if (x > 0) {
        double guess = __frsqrte(x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        *y = (x * guess);
        return *y;
    }
    return x;
}

/**
 * @brief Calculate Popo's impulse launch vector toward Nana during Belay pull
 * @details Normalizes the directional offset to Nana, then scales by base
 * impulse da->x94 plus distance scaled by da->x98.
 * @param gobj Fighter game object
 */
void ftPp_SpecialS_80120E68(Fighter_GObj* gobj)
{
    u8 _pad[4];
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    Fighter_GObj* nana_gobj = Player_GetEntityAtIndex(fp->player_idx, 1);
    volatile float y;
    PAD_STACK(8);

    if (nana_gobj != NULL) {
        Fighter* nana_fp = GET_FIGHTER(nana_gobj);
        f32 dx, dy;
        f32 dist;
        fp->self_vel.x = nana_fp->cur_pos.x - fp->cur_pos.x;
        fp->self_vel.y = nana_fp->cur_pos.y - fp->cur_pos.y;
        fp->self_vel.z = 0.0F;
        fp->self_vel.x = -(3.0F * nana_fp->facing_dir - fp->self_vel.x);
        fp->self_vel.y += 5.0F;
        lbVector_Normalize(&fp->self_vel);
        dx = SQ(fp->cur_pos.x - nana_fp->cur_pos.x);
        dy = SQ(fp->cur_pos.y - nana_fp->cur_pos.y);
        dist = my_sqrtf(dx + dy, &y) / da->x98;
        fp->self_vel.x *= da->x94 + dist;
        fp->self_vel.y *= da->x94 + dist;
        if (fp->self_vel.x > 0.0F) {
            fp->facing_dir = +1.0F;
        } else {
            fp->facing_dir = -1.0F;
        }
    }
}

/**
 * @brief Advance Belay rope string event progression on keyframes
 * @details Spawns string item at frame 8, triggers string animation events
 * at article keyframes ev0, ev1, ev2, and despawns at frame 0x53 (frame 83).
 * @param gobj Fighter game object
 * @return True if string failed to spawn
 */
bool ftPp_SpecialS_80120FE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 cmd = fp->mv.pp.speciallw.x0;
    PAD_STACK(16);

    if (cmd > 8 && cmd <= 0x53) {
        Item_GObj* item_gobj;
        if ((item_gobj = fp->u.pp.x2238) != NULL) {
            Item_GObj* rope_gobj = item_gobj;
            Item* ip = item_gobj->user_data;
            itClimbersStringAttributes* sa =
                ip->xC4_article_data->x4_specialAttributes;
            s32 ev0 = sa->x18;
            s32 ev1 = sa->x1C;
            s32 ev2 = sa->x20;
            if (cmd == ev0) {
                it_802C3950(rope_gobj);
            } else if (cmd == ev1) {
                it_802C3810(rope_gobj);
            } else if (cmd == ev2) {
                it_802C3864(rope_gobj);
            }
            if (fp->mv.pp.speciallw.x0 == 0x53) {
                it_802C2750(fp->u.pp.x2238);
            }
        } else {
            goto end;
        }
    } else if (fp->mv.pp.speciallw.x0 == 8) {
        ftPp_SpecialS_801210C8(gobj);
        if (fp->u.pp.x2238 == NULL) {
            ft_8008A2BC(gobj);
            return true;
        }
    }
    return false;
end: {
    // original code returns without a value
}
}

/**
 * @brief Spawn Belay rope string article item
 * @param gobj Fighter game object
 */
void ftPp_SpecialS_801210C8(Fighter_GObj* gobj)
{
    Vec3 spawn_pos;
    Fighter* fp = GET_FIGHTER(gobj);
    float dir;
    lb_8000B1CC(fp->parts[FtPart_L4thNb].joint, NULL, &spawn_pos);
    dir = fp->facing_dir;
    fp->u.pp.x2238 = it_802C27D4(gobj, &spawn_pos, fp->motion_id, dir);
    fp->x1984_heldItemSpec = fp->u.pp.x2238;
    if (fp->u.pp.x2238 != NULL) {
        fp->death3_cb = ftPp_Init_8011F060;
        fp->take_dmg_cb = ftPp_Init_8011F060;
    }
}

/**
 * @brief Clear Belay rope string reference and callbacks
 * @param gobj Fighter game object
 */
void ftPp_SpecialS_8012114C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->u.pp.x2238 = NULL;
    fp->death3_cb = NULL;
    fp->take_dmg_cb = NULL;
}

/**
 * @brief Despawn Belay rope string item
 * @param gobj Fighter game object
 */
void ftPp_SpecialS_80121164(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->u.pp.x2238 != NULL) {
        it_802C2750(fp->u.pp.x2238);
        ftPp_SpecialS_8012114C(gobj);
    }
}

/**
 * @brief Enter grounded Up-B: Belay
 * @details Divides ground velocity by da->x84 and initializes Belay motion
 * vars.
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;

    fp->gr_vel /= da->x84;

    ftPp_SpecialHi_801218AC(gobj);

    fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp = GET_FIGHTER(gobj);
    fp->mv.pp.unk_80123954.x0 = 1;
    fp->u.pp.x223C = 0;
    fp->u.pp.x2240.z = 0.0f;
    fp->u.pp.x2240.y = 0.0f;
    fp->u.pp.x2240.x = 0.0f;
}

/**
 * @brief Enter aerial Up-B: Belay
 * @details Divides self velocity by da->x84 (X) and da->x88 (Y), sets max
 * jumps used.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHi_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(16);

    fp->self_vel.x /= da->x84;
    fp->self_vel.y /= da->x88;

    ftPp_SpecialHi_801218F8(gobj);

    fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;

    fp = GET_FIGHTER(gobj);
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp = GET_FIGHTER(gobj);
    fp->mv.pp.unk_80123954.x0 = 1;
    fp->u.pp.x223C = 0;
    fp->u.pp.x2240.z = 0.0f;
    fp->u.pp.x2240.y = 0.0f;
    fp->u.pp.x2240.x = 0.0f;
}

/**
 * @brief Check if partner Nana is alive, available, and within Belay range
 * @details Verifies distance is less than threshold da->x7C and Nana can
 * perform Belay.
 * @param gobj Fighter game object
 * @return True if Nana is available to partner
 */
static inline bool checkNanaInRange(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    Fighter_GObj* nana_gobj = Player_GetEntityAtIndex(fp->player_idx, 1);
    if (nana_gobj != NULL) {
        Vec3* nana_pos = &GET_FIGHTER(nana_gobj)->cur_pos;
        f32 dx = SQ(fp->cur_pos.x - nana_pos->x);
        f32 dy = SQ(fp->cur_pos.y - nana_pos->y);
        if (sqrtf__Ff(dx + dy) < da->x7C &&
            ftNn_Init_8012300C(nana_gobj) == true)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Advance frame step counter and check rope event progression
 * @param gobj Fighter game object
 */
static inline void incrementMvAndCheck(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.pp.unk_80123954.x0++;
    ftPp_SpecialS_80120FE0(gobj);
}

/**
 * @brief Animation callback for grounded partnered Belay start
 * @details Verifies partner Nana is within range. If missing, branches to solo
 * fail (SpecialHiStart_1).
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiStart_0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(24);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (!checkNanaInRange(gobj)) {
            ftPp_SpecialHi_80122098(gobj);
            return;
        }
        fp->x2222_b2 = true;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPp_SpecialHi_80121DA0(gobj);
    } else {
        incrementMvAndCheck(gobj);
    }
}

/**
 * @brief Animation callback for aerial partnered Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiStart_0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(24);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        if (!checkNanaInRange(gobj)) {
            ftPp_SpecialHi_801220D4(gobj);
            return;
        }
        fp->x2222_b2 = true;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPp_SpecialHi_80121DD8(gobj);
        return;
    }
    incrementMvAndCheck(gobj);
}

/**
 * @brief IASA turnaround callback for grounded partnered Belay start
 * @details Turns fighter around if stick X exceeds deadzone da->x80.
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiStart_0_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        if (ABS(fp->input.lstick[0].x) > da->x80) {
            ftCommon_UpdateFacing(fp);
            ftPartSetRotY(fp, 0, (float) (M_PI_2 * fp->facing_dir));
        }
    }
}

/**
 * @brief IASA turnaround callback for aerial partnered Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiStart_0_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(16);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        if (ABS(fp->input.lstick[0].x) > da->x80) {
            ftCommon_UpdateFacing(fp);
            ftPartSetRotY(fp, 0, (float) (M_PI_2 * fp->facing_dir));
        }
    }
}

/**
 * @brief Physics callback for grounded partnered Belay start
 * @details Tracks Nana's anchor joint position in fp->u.pp.x2240.
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiStart_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    Vec3 sp;
    PAD_STACK(8);

    ft_80084F3C(gobj);
    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_idx, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->u.pp.x2240 = sp;
}

/**
 * @brief Physics callback for aerial partnered Belay start
 * @details Applies fall gravity da->x8C and terminal velocity da->x90.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiStart_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    Vec3 sp;
    PAD_STACK(16);

    ftCommon_Fall(fp, da->x8C, da->x90);
    ftCommon_CalcSelfAccel_DeaccelAir(fp);

    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_idx, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->u.pp.x2240 = sp;
}

/**
 * @brief Collision callback for grounded partnered Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiStart_0_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftPp_SpecialHi_801217EC(gobj);
    }
}

/**
 * @brief Collision callback for aerial partnered Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiStart_0_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        ftPp_SpecialHi_8012184C(gobj);
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/**
 * @brief Transition from grounded to aerial partnered Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_801217EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x160, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

/**
 * @brief Transition from aerial to grounded partnered Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_8012184C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_AirToGroundStateChange(gobj, fp, 0x15B, ftPp_MF_SpecialHi_Coll);
}

/**
 * @brief Initialize grounded partnered Belay start motion state (347)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_801218AC(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x15B, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Initialize aerial partnered Belay start motion state (352)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_801218F8(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, 0x160, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
}

/**
 * @brief Animation callback for grounded partnered Belay throw
 * @details Checks if partner Nana reached peak and triggered Popo's upward
 * yank.
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow_0_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(40);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }

    {
        Fighter* fp = gobj->user_data;
        if (fp->cmd_vars[1] != 0) {
            fp->cmd_vars[1] = 0;
            {
                int found;
                Fighter_GObj* nn_gobj =
                    Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_idx, 1);
                if (nn_gobj != NULL && ftNn_Init_8012309C(nn_gobj) == 1) {
                    found = 1;
                } else {
                    found = 0;
                }
                if (found == 1) {
                    ftPp_SpecialHi_8012280C(gobj);
                    return;
                }
            }
        }
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        ++fp->mv.pp.unk_80123954.x0;
        ftPp_SpecialS_80120FE0(gobj);
    }
}

/**
 * @brief Animation callback for aerial partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow_0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(48);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, false, da->x74, da->x78);
    }

    {
        Fighter* fp = gobj->user_data;
        if (fp->cmd_vars[1] != 0) {
            fp->cmd_vars[1] = 0;
            {
                int found;
                Fighter_GObj* nn_gobj =
                    Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_idx, 1);
                if (nn_gobj != NULL && ftNn_Init_8012309C(nn_gobj) == 1) {
                    found = 1;
                } else {
                    found = 0;
                }
                if (found == 1) {
                    ftPp_SpecialHi_8012280C(gobj);
                    return;
                }
            }
        }
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        ++fp->mv.pp.unk_80123954.x0;
        ftPp_SpecialS_80120FE0(gobj);
    }
}

/**
 * @brief IASA callback for grounded partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow_0_IASA(Fighter_GObj* gobj) {}

/**
 * @brief IASA callback for aerial partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow_0_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics callback for grounded partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    Vec3 sp;
    PAD_STACK(8);

    ft_80084F3C(gobj);
    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_idx, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->u.pp.x2240 = sp;
}

/**
 * @brief Apply aerial fall physics for partnered Belay throw
 * @param gobj Fighter game object
 */
static inline void doFallPhys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    ftCommon_Fall(fp, da->x8C, da->x90);
    ftCommon_CalcSelfAccel_DeaccelAir(fp);
}

/**
 * @brief Physics callback for aerial partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    Vec3 sp;
    PAD_STACK(12);

    doFallPhys(gobj);
    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_idx, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->u.pp.x2240 = sp;
}

/**
 * @brief Collision callback for grounded partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow_0_Coll(Fighter_GObj* gobj)
{
    if (ft_800827A0(gobj) == 0) {
        ftPp_SpecialHi_80121CE0(gobj);
    }
}

/**
 * @brief Collision callback for aerial partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow_0_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        ftPp_SpecialHi_80121D40(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/**
 * @brief Ground-to-air transition for partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80121CE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x161, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

/**
 * @brief Air-to-ground transition for partnered Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80121D40(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, 0x15C, ftPp_MF_SpecialHi_Coll);
}

/**
 * @brief Enter grounded partnered Belay throw state (348)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80121DA0(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x15C, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
}

/**
 * @brief Enter aerial partnered Belay throw state (353)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80121DD8(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x161, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
}

/**
 * @brief Animation callback for grounded solo Belay start (failure)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiStart_1_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPp_SpecialHi_80122348(gobj);
    }
}

/**
 * @brief Animation callback for aerial solo Belay start (failure)
 * @details Applies small initial upward velocity da->xA4 on cmd_vars[2].
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiStart_1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    if (fp->cmd_vars[2] != 0) {
        fp->cmd_vars[2] = 0;
        fp->self_vel.y = da->xA4;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPp_SpecialHi_80122380(gobj);
    }
}

/**
 * @brief IASA callback for grounded solo Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiStart_1_IASA(Fighter_GObj* gobj) {}

/**
 * @brief IASA callback for aerial solo Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiStart_1_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics callback for grounded solo Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiStart_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for aerial solo Belay start
 * @details Applies solo failure gravity da->xA8 and terminal velocity da->xAC.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiStart_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    ftCommon_Fall(fp, da->xA8, da->xAC);
    if (fp->self_vel.y < 0.0f) {
        ftCommon_CalcSelfAccel_DeaccelAir(fp);
    }
}

/**
 * @brief Collision callback for grounded solo Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiStart_1_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPp_SpecialHi_80121FD8(gobj);
    }
}

/**
 * @brief Collision callback for aerial solo Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiStart_1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        ftPp_SpecialHi_80122038(gobj);
        return;
    }

    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/**
 * @brief Ground-to-air transition for solo Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80121FD8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x163, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

/**
 * @brief Air-to-ground transition for solo Belay start
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80122038(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, 0x15E, ftPp_MF_SpecialHi_Coll);
}

/**
 * @brief Enter grounded solo Belay failure start state (350)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80122098(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x15E, Ft_MF_None, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

/**
 * @brief Enter aerial solo Belay failure start state (355)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_801220D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x163, Ft_MF_None, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

/**
 * @brief Animation callback for grounded solo Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow_1_Anim(Fighter_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

/**
 * @brief Animation callback for aerial solo Belay throw
 * @details Transitions into Special Fall upon animation completion.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow_1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, false, da->x74, da->x78);
    }
}

/**
 * @brief IASA callback for grounded solo Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow_1_IASA(Fighter_GObj* gobj) {}

/**
 * @brief IASA callback for aerial solo Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow_1_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics callback for grounded solo Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow_1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Physics callback for aerial solo Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(8);
    ftCommon_Fall(fp, da->xA8, da->xAC);
    if (fp->self_vel.y < 0.0f) {
        ftCommon_CalcSelfAccel_DeaccelAir(fp);
    }
}

/**
 * @brief Collision callback for grounded solo Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow_1_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPp_SpecialHi_801222E8(gobj);
    }
}

/**
 * @brief Collision callback for aerial solo Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow_1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    PAD_STACK(4);
    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        ftCo_LandingFallSpecial_Enter(gobj, false, da->x78);
        return;
    }
    if (ftCliffCommon_80081298(gobj)) {
        return;
    }
}

/**
 * @brief Ground-to-air transition for solo Belay throw
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_801222E8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x164, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

/**
 * @brief Transition to grounded solo Belay throw state (351)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80122348(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x15F, 0U, 0.0f, 1.0f, 0.0f, NULL);
}

/**
 * @brief Transition to aerial solo Belay throw state (356)
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_80122380(Fighter_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 0x164, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
}

/**
 * @brief Animation callback for grounded Popo rising Belay state
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow2_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    } else {
        Fighter* fp = GET_FIGHTER(gobj);
        ++fp->mv.pp.unk_80123954.x0;
        ftPp_SpecialS_80120FE0(gobj);
    }
}

/**
 * @brief Animation callback for aerial Popo rising Belay state
 * @details Ends upward recovery boost and transitions into Special Fall.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp;
    ftIceClimberAttributes* da;

    fp = GET_FIGHTER(gobj);
    da = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80096900(gobj, 0, 1, 0, da->x74, da->x78);
    } else {
        Fighter* fp2 = GET_FIGHTER(gobj);
        ++fp2->mv.pp.unk_80123954.x0;
        ftPp_SpecialS_80120FE0(gobj);
    }
}

/**
 * @brief IASA callback for grounded Popo rising Belay state
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow2_IASA(Fighter_GObj* gobj) {}

/**
 * @brief IASA callback for aerial Popo rising Belay state
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow2_IASA(Fighter_GObj* gobj) {}

/**
 * @brief Physics callback for grounded Popo rising Belay state
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp;
    Vec3 sp;
    PAD_STACK(8);

    ft_80084F3C(gobj);
    fp = GET_FIGHTER(gobj);
    sp.x = sp.y = sp.z = 0.0f;

    {
        Fighter_GObj* nn_gobj =
            Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_idx, 1);
        if (nn_gobj != NULL) {
            Fighter* nn_fp = GET_FIGHTER(nn_gobj);
            if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
                nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
            {
                lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, &sp);
            }
        }
    }

    fp->u.pp.x2240 = sp;
}

/**
 * @brief Update anchor joint coordinates from partner Nana's hand joint
 * @param gobj Fighter game object
 * @param sp Position output vector pointer
 */
static inline void ftPp_SpecialAirHiThrow2_Phys_inline(Fighter_GObj* gobj,
                                                       Vec3* sp)
{
    Fighter_GObj* nn_gobj =
        Player_GetEntityAtIndex(GET_FIGHTER(gobj)->player_idx, 1);
    if (nn_gobj != NULL) {
        Fighter* nn_fp = GET_FIGHTER(nn_gobj);
        if (nn_fp->motion_id >= ftPp_MS_SpecialHi_0 &&
            nn_fp->motion_id <= ftPp_MS_SpecialHi_5)
        {
            lb_8000B1CC(nn_fp->parts[FtPart_L4thNb].joint, NULL, sp);
        }
    }
}

/**
 * @brief Physics callback for aerial Popo rising Belay state
 * @details Applies rising gravity da->x9C, terminal velocity da->xA0,
 * analog stick air drift (da->xB0 / da->xB4), and tracks rope anchor joint.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow2_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 sp;
    ftIceClimberAttributes* da = fp->dat_attrs;
    ftCo_DatAttrs* co = &fp->co_attrs;
    PAD_STACK(12);

    ftCommon_Fall(fp, da->x9C, da->xA0);
    // Aerial drift steering
    if (ABS(fp->input.lstick[0].x) > da->x80) {
        ftCommon_CalcSelfAccel_DriftSimple(fp, 0.0f,
                                           co->air_drift_stick_mul * da->xB0,
                                           co->air_drift_max * da->xB4);
    } else if (fp->self_vel.y < 0.0f) {
        ftCommon_CalcSelfAccel_DeaccelAir(fp);
    }
    {
        fp = GET_FIGHTER(gobj);
        sp.x = sp.y = sp.z = 0.0f;
        ftPp_SpecialAirHiThrow2_Phys_inline(gobj, &sp);
        fp->u.pp.x2240 = sp;
    }
}

/**
 * @brief Collision callback for grounded Popo rising Belay state
 * @param gobj Fighter game object
 */
void ftPp_SpecialHiThrow2_Coll(Fighter_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftPp_SpecialHi_801227AC(gobj);
    }
}

/**
 * @brief Collision callback for aerial Popo rising Belay state
 * @details Handles ceiling collision (cancels vertical velocity, forces
 * Special Fall), wall friction, and landing into LandingFallSpecial with
 * landing lag da->x78.
 * @param gobj Fighter game object
 */
void ftPp_SpecialAirHiThrow2_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftIceClimberAttributes* da = fp->dat_attrs;
    CollData* cd = &fp->coll_data;
    PAD_STACK(8);
    if (ft_CheckGroundAndLedge(gobj, ftGetFacingDirInt(fp))) {
        ftCo_LandingFallSpecial_Enter(gobj, false, da->x78);
    } else if (!ftCliffCommon_80081298(gobj)) {
        // Left wall collision
        if ((cd->env_flags & 0x3F) && fp->self_vel.x > 0.0f) {
            fp->self_vel.x = 0.0f;
            // Right wall collision
        } else if ((cd->env_flags & 0xFC0) && fp->self_vel.x < 0.0f) {
            fp->self_vel.x = 0.0f;
            // Ceiling collision: stop vertical climb and enter Special Fall
        } else if (cd->env_flags & 0x6000) {
            fp->self_vel.y = 0.0f;
            ftCo_80096900(gobj, 0, 1, false, da->x74, da->x78);
        }
    }
}

/**
 * @brief Ground-to-air transition for Popo rising Belay state
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_801227AC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, 0x162, 0x0C4C508A, fp->cur_anim_frame,
                              1.0f, 0.0f, NULL);
}

/**
 * @brief Enter Popo rising Belay state when yanked up by Nana
 * @details Calculates launch vector towards Nana, enters motion state 0x162
 * (ftPp_MS_SpecialAirHiThrow2), and sets double jump exhausted.
 * @param gobj Fighter game object
 */
void ftPp_SpecialHi_8012280C(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* co = &fp->co_attrs;
    PAD_STACK(8);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(fp);
    } else {
        fp->x1968_jumpsUsed = co->max_jumps;
    }
    ftPp_SpecialS_80120E68(gobj);
    Fighter_ChangeMotionState(gobj, 0x162, Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    fp->x21F8 = ftCommon_8007F76C;
}
