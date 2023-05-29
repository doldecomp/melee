#include "forward.h"

#include "ftNess/ftNs_SpecialN.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftNess/ftNs_Init.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"

// SpecialN/SpecialAirN (PK Flash)
#define FTNESS_SPECIALN_COLL_FLAG                                             \
    Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd |                 \
        Ft_MF_SkipItemVis | Ft_MF_Unk19 | Ft_MF_SkipModelPartVis |            \
        Ft_MF_SkipModelFlags | Ft_MF_Unk27

/// Ness PK Flash Charge msid check
bool ftNs_SpecialN_CheckSpecialNHold(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->fv.ns.pkflash_gobj != NULL) {
            enum_t msid = fp->motion_id;
            if (msid == ftNs_MS_SpecialNHold ||
                msid == ftNs_MS_SpecialAirNHold)
            {
                return true;
            }
        }
    }

    return false;
}

/// Clear Ness's callbacks and PK Flash's item GObj pointer
void ftNs_SpecialN_SetNULL(HSD_GObj* gobj)
{
    if (gobj == NULL) {
        return;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp == NULL) {
            return;
        }

        if (fp->fv.ns.pkflash_gobj != NULL) {
            fp->fv.ns.pkflash_gobj = NULL;
        }

        fp->cb.x21E4_callback_OnDeath2 = NULL;
        fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }
}

/// Clear PK Flash's owner GObj pointer, Ness's pointer to PK Flash's item
/// GObj, and reset callbacks
void ftNs_SpecialN_ItemPKFlushSetNULL(HSD_GObj* gobj)
{
    if (gobj == NULL) {
        return;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp == NULL) {
            return;
        }

        if (fp->fv.ns.pkflash_gobj != NULL) {
            it_802AAA50(fp->fv.ns.pkflash_gobj);
            fp->fv.ns.pkflash_gobj = NULL;
        }

        fp->cb.x21E4_callback_OnDeath2 = NULL;
        fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }
}

/// @todo Float order hack.
static f32 return_void(void)
{
    return 0.0f;
}

/// @todo Float order hack.
static f32 return_void2(void)
{
    return 3.0f;
}

/// @todo Float order hack.
static f32 return_void3(void)
{
    return 1.0f;
}

/// Ness's grounded PK Flash Start Motion State handler
void ftNs_SpecialNStart_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    {
        Fighter* fp0;
        fp0 = GET_FIGHTER(gobj);

        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialNStart, 0, NULL, 0, 1,
                                  0);

        fp0->cmd_vars[3] = 0;
        fp0->cmd_vars[2] = 0;
        fp0->cmd_vars[1] = 0;
        fp0->cmd_vars[0] = 0;
    }

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        ftNessAttributes* sa = getFtSpecialAttrs(fp1);

        fp1->mv.ns.specialn.flashTimerLoop1 = sa->x0_PKFLASH_TIMER1_LOOPFRAMES;
        fp1->mv.ns.specialn.flashTimerLoop2 = sa->x4_PKFLASH_TIMER2_LOOPFRAMES;
        fp1->mv.ns.specialn.gravityDelay = sa->x8_PKFLASH_GRAVITY_DELAY;

        fp1->fv.ns.pkflash_gobj = NULL;
        fp1->mv.ns.specialn.flashTimerMin = sa->xC_PKFLASH_MINCHARGEFRAMES;
        fp1->cb.x21E4_callback_OnDeath2 = NULL;
        fp1->cb.x21DC_callback_OnTakeDamage = NULL;
    }

    ftAnim_8006EBA4(gobj);
}

/// Ness's aerial PK Flash Start Motion State handler
void ftNs_SpecialAirNStart_Enter(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirNStart, 0, NULL, 0, 1,
                              0);

    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->self_vel.y = 0;

    {
        Fighter* temp_fp = GET_FIGHTER(gobj);
        ftNessAttributes* ness_attr = getFtSpecialAttrs(temp_fp);

        temp_fp->mv.ns.specialn.flashTimerLoop1 =
            ness_attr->x0_PKFLASH_TIMER1_LOOPFRAMES;
        temp_fp->mv.ns.specialn.flashTimerLoop2 =
            ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
        temp_fp->mv.ns.specialn.gravityDelay =
            ness_attr->x8_PKFLASH_GRAVITY_DELAY;

        temp_fp->fv.ns.pkflash_gobj = NULL;

        temp_fp->mv.ns.specialn.flashTimerMin =
            ness_attr->xC_PKFLASH_MINCHARGEFRAMES;

        temp_fp->cb.x21E4_callback_OnDeath2 = NULL;
        temp_fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }

    ftAnim_8006EBA4(gobj);
}

/// Ness's grounded PK Flash Start Animation callback
void ftNs_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj)) {
        return;
    }

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialNHold, 0, NULL, 0, 1, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->fv.ns.pkflash_gobj == NULL) {
            /// @todo Can't move below @c _.
            Vec3 vec;

            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[20];
#endif

            lb_8000B1CC(fp->parts[FtPart_L2ndNa].joint, NULL, &vec);
            vec.z = 0;
            vec.y += 3 * fp->x34_scale.y;

            {
                HSD_GObj* pk_flash = it_802AA8C0(
                    gobj, &vec, It_Kind_Ness_PKFlush, fp->facing_dir);

                fp->fv.ns.pkflash_gobj = pk_flash;

                if (pk_flash != NULL) {
                    fp->cb.x21E4_callback_OnDeath2 = ftNs_Init_OnDamage;
                    fp->cb.x21DC_callback_OnTakeDamage = ftNs_Init_OnDamage;
                }
            }
        }
    }

    fp->x1968_jumpsUsed = (u8) fp->co_attrs.max_jumps;
}

/// Ness's grounded PK Flash Charge Animation callback
void ftNs_SpecialNRelease_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.ns.specialn.flashTimerLoop1 != 0) {
        fp->mv.ns.specialn.flashTimerLoop1--;
    }

    if (fp->fv.ns.pkflash_gobj == NULL &&
        fp->mv.ns.specialn.flashTimerLoop2 != 0)
    {
        fp->mv.ns.specialn.flashTimerLoop2--;
    }

    if (fp->fv.ns.pkflash_gobj == NULL) {
        if (fp->mv.ns.specialn.flashTimerLoop1 <= 0 &&
            fp->mv.ns.specialn.flashTimerLoop2 <= 0)
        {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialNEnd, 0, NULL, 0, 1,
                                      0);

            return;
        }

        if (fp->motion_id != ftNs_MS_SpecialNRelease) {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialNRelease, 0, NULL,
                                      fp->cur_anim_frame, 1, 0);
        }

        return;
    }

    if (it_802AA7E4(fp->fv.ns.pkflash_gobj) != gobj) {
        fp->fv.ns.pkflash_gobj = NULL;
        return;
    }

    if (it_802AA7F0(fp->fv.ns.pkflash_gobj) == true &&
        fp->motion_id != ftNs_MS_SpecialNRelease)
    {
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialNRelease, 0, NULL,
                                  fp->cur_anim_frame, 1, 0);
    }
}

/// Inline to set all variables and match ASM register data
inline void SetPKFlashAttr(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->dat_attrs;

    fp->mv.ns.specialn.flashTimerLoop1 = sa->x0_PKFLASH_TIMER1_LOOPFRAMES;
    fp->mv.ns.specialn.flashTimerLoop2 = sa->x4_PKFLASH_TIMER2_LOOPFRAMES;
    fp->mv.ns.specialn.gravityDelay = sa->x8_PKFLASH_GRAVITY_DELAY;
    fp->fv.ns.pkflash_gobj = NULL;
    fp->mv.ns.specialn.flashTimerMin = sa->xC_PKFLASH_MINCHARGEFRAMES;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

/// Ness's grounded PK Flash Release Animation callback
void ftNs_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    SetPKFlashAttr(gobj);
    ftParts_8007592C(fp, 0, 0);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// Ness's aerial PK Flash Start Animation callback
void ftNs_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj)) {
        return;
    }

    {
        Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirNHold, 0, NULL, 0, 1,
                                  0);
        {
            Fighter* fighter_data2 = GET_FIGHTER(gobj);

            if (fighter_data2->fv.ns.pkflash_gobj == NULL) {
                Vec3 vec;

                /// @todo Unused stack.
#ifdef MUST_MATCH
                u8 _[20];
#endif

                lb_8000B1CC(fighter_data2->parts[FtPart_L2ndNa].joint, NULL,
                            &vec);
                vec.z = 0;
                vec.y += 3 * fighter_data2->x34_scale.y;

                {
                    HSD_GObj* flash_GObj =
                        it_802AA8C0(gobj, &vec, It_Kind_Ness_PKFlush,
                                    fighter_data2->facing_dir);
                    fighter_data2->fv.ns.pkflash_gobj = flash_GObj;
                    if (flash_GObj != NULL) {
                        fighter_data2->cb.x21E4_callback_OnDeath2 =
                            ftNs_Init_OnDamage;
                        fighter_data2->cb.x21DC_callback_OnTakeDamage =
                            ftNs_Init_OnDamage;
                    }
                }
            }
        }

        fp->x1968_jumpsUsed = fp->co_attrs.max_jumps;
    }
}

/// Ness's aerial PK Flash Charge Animation callback
void ftNs_SpecialAirNRelease_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.ns.specialn.flashTimerLoop1 != 0) {
        fp->mv.ns.specialn.flashTimerLoop1--;
    }

    if (fp->fv.ns.pkflash_gobj == NULL &&
        fp->mv.ns.specialn.flashTimerLoop2 != 0)
    {
        fp->mv.ns.specialn.flashTimerLoop2--;
    }

    if (fp->fv.ns.pkflash_gobj == NULL) {
        if (fp->mv.ns.specialn.flashTimerLoop1 <= 0 &&
            fp->mv.ns.specialn.flashTimerLoop2 <= 0)
        {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirNEnd, 0, NULL, 0,
                                      1, 0);
            return;
        }

        if (fp->motion_id != ftNs_MS_SpecialAirNRelease) {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirNRelease, 0,
                                      NULL, fp->cur_anim_frame, 1, 0);
        }
    } else {
        if (it_802AA7E4(fp->fv.ns.pkflash_gobj) != gobj) {
            fp->fv.ns.pkflash_gobj = NULL;
            return;
        }

        if (it_802AA7F0(fp->fv.ns.pkflash_gobj) == true &&
            fp->motion_id != ftNs_MS_SpecialAirNRelease)
        {
            Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirNRelease, 0,
                                      NULL, fp->cur_anim_frame, 1, 0);
        }
    }
}

/// Ness's aerial PK Flash Release Animation callback
void ftNs_SpecialAirNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = getFtSpecialAttrs(fp);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    SetPKFlashAttr(gobj);
    ftParts_8007592C(fp, 0, 0);

    if (ftAnim_IsFramesRemaining(gobj)) {
        return;
    }

    {
        f32 landing_lag = sa->x1C_PKFLASH_LANDING_LAG;

        if (landing_lag == 0) {
            ftCo_800CC730(gobj);
            return;
        }

        ftCo_80096900(gobj, 1, 0, true, 1, sa->x1C_PKFLASH_LANDING_LAG);
    }
}

/// Ness's grounded PK Flash Start IASA callback
void ftNs_SpecialNStart_IASA(HSD_GObj* gobj) {}

/// Ness's grounded PK Flash Charge IASA callback
void ftNs_SpecialNRelease_IASA(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.ns.specialn.flashTimerMin--;

        {
            /// @todo Nested return value
            bool result;
            if (fp->mv.ns.specialn.flashTimerMin <= 0) {
                fp->mv.ns.specialn.flashTimerMin = 0;
                result = true;
            } else {
                result = false;
            }

            if (result != true) {
                return;
            }
        }

        if (fp->input.held_inputs & HSD_PAD_B) {
            return;
        }
    }

    if (gobj == NULL) {
        return;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp == NULL) {
            return;
        }

        if (fp->fv.ns.pkflash_gobj != NULL) {
            fp->fv.ns.pkflash_gobj = NULL;
        }

        fp->cb.x21E4_callback_OnDeath2 = NULL;
        fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }
}

/// Ness's grounded PK Flash Release IASA callback
void ftNs_SpecialNEnd_IASA(HSD_GObj* gobj) {}

/// Ness's aerial PK Flash Start IASA callback
void ftNs_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

/// Ness's aerial PK Flash Charge IASA callback
void ftNs_SpecialAirNRelease_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.ns.specialn.flashTimerMin = fp->mv.ns.specialn.flashTimerMin - 1;

    {
        /// @todo Nested return value
        bool result;

        if (fp->mv.ns.specialn.flashTimerMin <= 0) {
            fp->mv.ns.specialn.flashTimerMin = 0;
            result = true;
        } else {
            result = false;
        }

        if (result != true) {
            return;
        }
    }

    if (fp->input.held_inputs & HSD_PAD_B) {
        return;
    }

    if (gobj == NULL) {
        return;
    }

    {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp == NULL) {
            return;
        }

        if (fp->fv.ns.pkflash_gobj != NULL) {
            fp->fv.ns.pkflash_gobj = NULL;
        }

        fp->cb.x21E4_callback_OnDeath2 = NULL;
        fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }
}

/// Ness's aerial PK Flash Release IASA callback
void ftNs_SpecialAirNEnd_IASA(HSD_GObj* gobj) {}

/// Inline to set remaining frames of gravity delay
inline void GravityDelay(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->mv.ns.specialn.gravityDelay != 0) {
        fp->mv.ns.specialn.gravityDelay--;
    }
}

/// Ness's grounded PK Flash Start Physics callback
void ftNs_SpecialNStart_Phys(HSD_GObj* gobj)
{
    GravityDelay(gobj);
    ft_80084F3C(gobj);
}

/// Ness's grounded PK Flash Charge Physics callback
void ftNs_SpecialNRelease_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Ness's grounded PK Flash Release Physics callback
void ftNs_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/// Ness's aerial PK Flash Start Physics callback
void ftNs_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->dat_attrs;

    if (fp->mv.ns.specialn.gravityDelay != 0) {
        fp->mv.ns.specialn.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, sa->x14_PKFLASH_FALL_ACCEL,
                          fp->co_attrs.terminal_vel);
    }

    {
        f32 airFriction = fp->co_attrs.aerial_friction;
        ftCommon_8007CE94(fp, airFriction);
    }
}

/// Ness's aerial PK Flash Charge Physics callback
void ftNs_SpecialAirNRelease_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->dat_attrs;

    if (fp->mv.ns.specialn.gravityDelay != 0) {
        fp->mv.ns.specialn.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, sa->x14_PKFLASH_FALL_ACCEL,
                          fp->co_attrs.terminal_vel);
    }

    {
        f32 airFriction = fp->co_attrs.aerial_friction;
        ftCommon_8007CE94(fp, airFriction);
    }
}

/// Ness's aerial PK Flash Release Physics callback
void ftNs_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->dat_attrs;

    if (fp->mv.ns.specialn.gravityDelay != 0) {
        fp->mv.ns.specialn.gravityDelay--;
    } else {
        ftCommon_8007D494(fp, sa->x14_PKFLASH_FALL_ACCEL,
                          fp->co_attrs.terminal_vel);
    }

    {
        f32 airFriction = fp->co_attrs.aerial_friction;
        ftCommon_8007CE94(fp, airFriction);
    }
}

/// Ness's grounded PK Flash Start Collision callback
void ftNs_SpecialNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj)) {
        return;
    }

    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirNStart,
                              FTNESS_SPECIALN_COLL_FLAG, NULL,
                              fp->cur_anim_frame, 1, 0);
}

/// Ness's grounded PK Flash Charge Collision callback
void ftNs_SpecialNRelease_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj)) {
        return;
    }

    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirNHold,
                              FTNESS_SPECIALN_COLL_FLAG, NULL,
                              fp->cur_anim_frame, 1, 0);
}

/// Ness's grounded PK Flash Release Collision callback
void ftNs_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj)) {
        return;
    }

    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialAirNEnd,
                              FTNESS_SPECIALN_COLL_FLAG, NULL,
                              fp->cur_anim_frame, 1, 0);
}

/// Ness's aerial PK Flash Start Collision callback
void ftNs_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80081D0C(gobj)) {
        return;
    }

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialNStart,
                              FTNESS_SPECIALN_COLL_FLAG, NULL,
                              fp->cur_anim_frame, 1, 0);
}

/// Ness's aerial PK Flash Charge Collision callback
void ftNs_SpecialAirNRelease_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80081D0C(gobj)) {
        return;
    }

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialNHold,
                              FTNESS_SPECIALN_COLL_FLAG, NULL,
                              fp->cur_anim_frame, 1, 0);
}

/// Ness's aerial PK Flash Release Collision callback
void ftNs_SpecialAirNEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!ft_80081D0C(gobj)) {
        return;
    }

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, ftNs_MS_SpecialNEnd,
                              FTNESS_SPECIALN_COLL_FLAG, NULL,
                              fp->cur_anim_frame, 1, 0);
}
