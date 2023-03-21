#include "ftNess/ftNess_SpecialN.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftNess/ftNess.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>

/// Ness PK Flash Charge ASID check
bool ftNess_CheckSpecialNHold(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp != NULL && fp->ev.ns.x2240_flashGObj != NULL) {
            enum_t asid = fp->action_id;
            if (asid == AS_NESS_SPECIALN_HOLD ||
                asid == AS_NESS_SPECIALAIRN_HOLD)
            {
                return true;
            }
        }
    }

    return false;
}

/// Clear Ness's callbacks and PK Flash's item GObj pointer
void ftNess_SpecialNSetNULL(HSD_GObj* gobj)
{
    if (gobj == NULL)
        return;

    {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp == NULL)
            return;

        if (fp->ev.ns.x2240_flashGObj != NULL)
            fp->ev.ns.x2240_flashGObj = NULL;

        fp->cb.x21E4_callback_OnDeath2 = NULL;
        fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }
}

/// Clear PK Flash's owner GObj pointer, Ness's pointer to PK Flash's item
/// GObj, and reset callbacks
void ftNess_ItemPKFlushSetNULL(HSD_GObj* gobj)
{
    if (gobj == NULL)
        return;

    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp == NULL)
            return;

        if (fp->ev.ns.x2240_flashGObj != NULL) {
            func_802AAA50(fp->ev.ns.x2240_flashGObj);
            fp->ev.ns.x2240_flashGObj = NULL;
        }

        fp->cb.x21E4_callback_OnDeath2 = NULL;
        fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }
}

/// @todo Float order hack.
f32 return_void(void)
{
    return 0.0f;
}

/// @todo Float order hack.
f32 return_void2(void)
{
    return 3.0f;
}

/// @todo Float order hack.
f32 return_void3(void)
{
    return 1.0f;
}

/// Ness's grounded PK Flash Start Action State handler
void ftNess_SpecialNStart_Action(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    {
        Fighter* fp0;
        fp0 = GET_FIGHTER(gobj);

        Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALN_START, 0,
                                           NULL, 0, 1, 0);

        fp0->x220C_ftcmd_var3 = 0;
        fp0->x2208_ftcmd_var2 = 0;
        fp0->x2204_ftcmd_var1 = 0;
        fp0->x2200_ftcmd_var0 = 0;
    }

    {
        Fighter* fp1 = GET_FIGHTER(gobj);
        ftNessAttributes* sa = getFtSpecialAttrs(fp1);

        fp1->sv.ns.specialn.flashTimerLoop1 = sa->x0_PKFLASH_TIMER1_LOOPFRAMES;
        fp1->sv.ns.specialn.flashTimerLoop2 = sa->x4_PKFLASH_TIMER2_LOOPFRAMES;
        fp1->sv.ns.specialn.gravityDelay = sa->x8_PKFLASH_GRAVITY_DELAY;

        fp1->ev.ns.x2240_flashGObj = NULL;
        fp1->sv.ns.specialn.flashTimerMin = sa->xC_PKFLASH_MINCHARGEFRAMES;
        fp1->cb.x21E4_callback_OnDeath2 = NULL;
        fp1->cb.x21DC_callback_OnTakeDamage = NULL;
    }

    func_8006EBA4(gobj);
}

/// Ness's aerial PK Flash Start Action State handler
void ftNess_SpecialAirNStart_Action(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALAIRN_START, 0,
                                       NULL, 0, 1, 0);

    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x80_self_vel.y = 0;

    {
        Fighter* temp_fp = GET_FIGHTER(gobj);
        ftNessAttributes* ness_attr = getFtSpecialAttrs(temp_fp);

        temp_fp->sv.ns.specialn.flashTimerLoop1 =
            ness_attr->x0_PKFLASH_TIMER1_LOOPFRAMES;
        temp_fp->sv.ns.specialn.flashTimerLoop2 =
            ness_attr->x4_PKFLASH_TIMER2_LOOPFRAMES;
        temp_fp->sv.ns.specialn.gravityDelay =
            ness_attr->x8_PKFLASH_GRAVITY_DELAY;

        temp_fp->ev.ns.x2240_flashGObj = NULL;

        temp_fp->sv.ns.specialn.flashTimerMin =
            ness_attr->xC_PKFLASH_MINCHARGEFRAMES;

        temp_fp->cb.x21E4_callback_OnDeath2 = NULL;
        temp_fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }

    func_8006EBA4(gobj);
}

/// Ness's grounded PK Flash Start Animation callback
void ftNess_SpecialNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj))
        return;

    Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALN_HOLD, 0, NULL, 0,
                                       1, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->ev.ns.x2240_flashGObj == NULL) {
            /// @todo Can't move below @c _.
            Vec3 vec;

            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[20];
#endif

            func_8000B1CC(fp->x5E8_fighterBones[L2ndNa].x0_jobj, NULL, &vec);
            vec.z = 0;
            vec.y += 3 * fp->x34_scale.y;

            {
                HSD_GObj* pk_flash = func_802AA8C0(
                    gobj, &vec, It_Kind_Ness_PKFlush, fp->facing_dir);

                fp->ev.ns.x2240_flashGObj = pk_flash;

                if (pk_flash != NULL) {
                    fp->cb.x21E4_callback_OnDeath2 = ftNess_OnDamage;
                    fp->cb.x21DC_callback_OnTakeDamage = ftNess_OnDamage;
                }
            }
        }
    }

    fp->x1968_jumpsUsed = (u8) fp->x110_attr.x168_MaxJumps;
}

/// Ness's grounded PK Flash Charge Animation callback
void ftNess_SpecialNHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->sv.ns.specialn.flashTimerLoop1 != 0)
        fp->sv.ns.specialn.flashTimerLoop1--;

    if (fp->ev.ns.x2240_flashGObj == NULL &&
        fp->sv.ns.specialn.flashTimerLoop2 != 0)
    {
        fp->sv.ns.specialn.flashTimerLoop2--;
    }

    if (fp->ev.ns.x2240_flashGObj == NULL) {
        if (fp->sv.ns.specialn.flashTimerLoop1 <= 0 &&
            fp->sv.ns.specialn.flashTimerLoop2 <= 0)
        {
            Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALN_END, 0,
                                               NULL, 0, 1, 0);

            return;
        }

        if (fp->action_id != AS_NESS_SPECIALN_HOLD_RELEASE) {
            Fighter_ActionStateChange_800693AC(
                gobj, AS_NESS_SPECIALN_HOLD_RELEASE, 0, NULL,
                fp->x894_currentAnimFrame, 1, 0);
        }

        return;
    }

    if (func_802AA7E4(fp->ev.ns.x2240_flashGObj) != gobj) {
        fp->ev.ns.x2240_flashGObj = NULL;
        return;
    }

    if (func_802AA7F0(fp->ev.ns.x2240_flashGObj) == true &&
        fp->action_id != AS_NESS_SPECIALN_HOLD_RELEASE)
    {
        Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALN_HOLD_RELEASE,
                                           0, NULL, fp->x894_currentAnimFrame,
                                           1, 0);
    }
}

/// Inline to set all variables and match ASM register data
inline void SetPKFlashAttr(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->x2D4_specialAttributes;

    fp->sv.ns.specialn.flashTimerLoop1 = sa->x0_PKFLASH_TIMER1_LOOPFRAMES;
    fp->sv.ns.specialn.flashTimerLoop2 = sa->x4_PKFLASH_TIMER2_LOOPFRAMES;
    fp->sv.ns.specialn.gravityDelay = sa->x8_PKFLASH_GRAVITY_DELAY;
    fp->ev.ns.x2240_flashGObj = NULL;
    fp->sv.ns.specialn.flashTimerMin = sa->xC_PKFLASH_MINCHARGEFRAMES;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

/// Ness's grounded PK Flash Release Animation callback
void ftNess_SpecialNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    SetPKFlashAttr(gobj);
    func_8007592C(fp, 0, 0);

    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

/// Ness's aerial PK Flash Start Animation callback
void ftNess_SpecialAirNStart_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftAnim_IsFramesRemaining(gobj))
        return;

    {
        Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALAIRN_HOLD, 0,
                                           NULL, 0, 1, 0);
        {
            Fighter* fighter_data2 = GET_FIGHTER(gobj);

            if (fighter_data2->ev.ns.x2240_flashGObj == NULL) {
                Vec3 vec;

                /// @todo Unused stack.
#ifdef MUST_MATCH
                u8 _[20];
#endif

                func_8000B1CC(fighter_data2->x5E8_fighterBones[L2ndNa].x0_jobj,
                              NULL, &vec);
                vec.z = 0;
                vec.y += 3 * fighter_data2->x34_scale.y;

                {
                    HSD_GObj* flash_GObj =
                        func_802AA8C0(gobj, &vec, It_Kind_Ness_PKFlush,
                                      fighter_data2->facing_dir);
                    fighter_data2->ev.ns.x2240_flashGObj = flash_GObj;
                    if (flash_GObj != NULL) {
                        fighter_data2->cb.x21E4_callback_OnDeath2 =
                            ftNess_OnDamage;
                        fighter_data2->cb.x21DC_callback_OnTakeDamage =
                            ftNess_OnDamage;
                    }
                }
            }
        }

        fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    }
}

/// Ness's aerial PK Flash Charge Animation callback
void ftNess_SpecialAirNHold_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->sv.ns.specialn.flashTimerLoop1 != 0)
        fp->sv.ns.specialn.flashTimerLoop1--;

    if (fp->ev.ns.x2240_flashGObj == NULL &&
        fp->sv.ns.specialn.flashTimerLoop2 != 0)
    {
        fp->sv.ns.specialn.flashTimerLoop2--;
    }

    if (fp->ev.ns.x2240_flashGObj == NULL) {
        if (fp->sv.ns.specialn.flashTimerLoop1 <= 0 &&
            fp->sv.ns.specialn.flashTimerLoop2 <= 0)
        {
            Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALAIRN_END,
                                               0, NULL, 0, 1, 0);
            return;
        }

        if (fp->action_id != AS_NESS_SPECIALAIRN_HOLD_RELEASE) {
            Fighter_ActionStateChange_800693AC(
                gobj, AS_NESS_SPECIALAIRN_HOLD_RELEASE, 0, NULL,
                fp->x894_currentAnimFrame, 1, 0);
        }
    } else {
        if (func_802AA7E4(fp->ev.ns.x2240_flashGObj) != gobj) {
            fp->ev.ns.x2240_flashGObj = NULL;
            return;
        }

        if (func_802AA7F0(fp->ev.ns.x2240_flashGObj) == true &&
            fp->action_id != AS_NESS_SPECIALAIRN_HOLD_RELEASE)
        {
            Fighter_ActionStateChange_800693AC(
                gobj, AS_NESS_SPECIALAIRN_HOLD_RELEASE, 0, NULL,
                fp->x894_currentAnimFrame, 1, 0);
        }
    }
}

/// Ness's aerial PK Flash Release Animation callback
void ftNess_SpecialAirNEnd_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = getFtSpecialAttrs(fp);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    SetPKFlashAttr(gobj);
    func_8007592C(fp, 0, 0);

    if (ftAnim_IsFramesRemaining(gobj))
        return;

    {
        f32 landing_lag = sa->x1C_PKFLASH_LANDING_LAG;

        if (landing_lag == 0) {
            func_800CC730(gobj);
            return;
        }

        func_80096900(gobj, 1, 0, true, 1, sa->x1C_PKFLASH_LANDING_LAG);
    }
}

/// Ness's grounded PK Flash Start IASA callback
void ftNess_SpecialNStart_IASA(HSD_GObj* gobj) {}

/// Ness's grounded PK Flash Charge IASA callback
void ftNess_SpecialNHold_IASA(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->sv.ns.specialn.flashTimerMin--;

        {
            /// @todo Nested return value
            bool result;
            if (fp->sv.ns.specialn.flashTimerMin <= 0) {
                fp->sv.ns.specialn.flashTimerMin = 0;
                result = true;
            } else {
                result = false;
            }

            if (result != true)
                return;
        }

        if (fp->input.x65C_heldInputs & HSD_BUTTON_B)
            return;
    }

    if (gobj == NULL)
        return;

    {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp == NULL)
            return;

        if (fp->ev.ns.x2240_flashGObj != NULL)
            fp->ev.ns.x2240_flashGObj = NULL;

        fp->cb.x21E4_callback_OnDeath2 = NULL;
        fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }
}

/// Ness's grounded PK Flash Release IASA callback
void ftNess_SpecialNEnd_IASA(HSD_GObj* gobj) {}

/// Ness's aerial PK Flash Start IASA callback
void ftNess_SpecialAirNStart_IASA(HSD_GObj* gobj) {}

/// Ness's aerial PK Flash Charge IASA callback
void ftNess_SpecialAirNHold_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->sv.ns.specialn.flashTimerMin = fp->sv.ns.specialn.flashTimerMin - 1;

    {
        /// @todo Nested return value
        bool result;

        if (fp->sv.ns.specialn.flashTimerMin <= 0) {
            fp->sv.ns.specialn.flashTimerMin = 0;
            result = true;
        } else {
            result = false;
        }

        if (result != true)
            return;
    }

    if (fp->input.x65C_heldInputs & HSD_BUTTON_B)
        return;

    if (gobj == NULL)
        return;

    {
        Fighter* fp = GET_FIGHTER(gobj);

        if (fp == NULL)
            return;

        if (fp->ev.ns.x2240_flashGObj != NULL)
            fp->ev.ns.x2240_flashGObj = NULL;

        fp->cb.x21E4_callback_OnDeath2 = NULL;
        fp->cb.x21DC_callback_OnTakeDamage = NULL;
    }
}

/// Ness's aerial PK Flash Release IASA callback
void ftNess_SpecialAirNEnd_IASA(HSD_GObj* gobj) {}

/// Inline to set remaining frames of gravity delay
inline void GravityDelay(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->sv.ns.specialn.gravityDelay != 0)
        fp->sv.ns.specialn.gravityDelay--;
}

/// Ness's grounded PK Flash Start Physics callback
void ftNess_SpecialNStart_Phys(HSD_GObj* gobj)
{
    GravityDelay(gobj);
    func_80084F3C(gobj);
}

/// Ness's grounded PK Flash Charge Physics callback
void ftNess_SpecialNHold_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

/// Ness's grounded PK Flash Release Physics callback
void ftNess_SpecialNEnd_Phys(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

/// Ness's aerial PK Flash Start Physics callback
void ftNess_SpecialAirNStart_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->sv.ns.specialn.gravityDelay != 0) {
        fp->sv.ns.specialn.gravityDelay--;
    } else
        func_8007D494(fp, sa->x14_PKFLASH_FALL_ACCEL,
                      fp->x110_attr.x170_TerminalVelocity);

    {
        f32 airFriction = fp->x110_attr.x180_AerialFriction;
        func_8007CE94(fp, airFriction);
    }
}

/// Ness's aerial PK Flash Charge Physics callback
void ftNess_SpecialAirNHold_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->sv.ns.specialn.gravityDelay != 0) {
        fp->sv.ns.specialn.gravityDelay--;
    } else {
        func_8007D494(fp, sa->x14_PKFLASH_FALL_ACCEL,
                      fp->x110_attr.x170_TerminalVelocity);
    }

    {
        f32 airFriction = fp->x110_attr.x180_AerialFriction;
        func_8007CE94(fp, airFriction);
    }
}

/// Ness's aerial PK Flash Release Physics callback
void ftNess_SpecialAirNEnd_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftNessAttributes* sa = fp->x2D4_specialAttributes;

    if (fp->sv.ns.specialn.gravityDelay != 0) {
        fp->sv.ns.specialn.gravityDelay--;
    } else {
        func_8007D494(fp, sa->x14_PKFLASH_FALL_ACCEL,
                      fp->x110_attr.x170_TerminalVelocity);
    }

    {
        f32 airFriction = fp->x110_attr.x180_AerialFriction;
        func_8007CE94(fp, airFriction);
    }
}

/// Ness's grounded PK Flash Start Collision callback
void ftNess_SpecialNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (func_80082708(gobj))
        return;

    func_8007D5D4(fp);

    Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALAIRN_START,
                                       FTNESS_SPECIALN_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}

/// Ness's grounded PK Flash Charge Collision callback
void ftNess_SpecialNHold_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (func_80082708(gobj))
        return;

    func_8007D5D4(fp);

    Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALAIRN_HOLD,
                                       FTNESS_SPECIALN_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}

/// Ness's grounded PK Flash Release Collision callback
void ftNess_SpecialNEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (func_80082708(gobj))
        return;

    func_8007D5D4(fp);

    Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALAIRN_END,
                                       FTNESS_SPECIALN_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}

/// Ness's aerial PK Flash Start Collision callback
void ftNess_SpecialAirNStart_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!func_80081D0C(gobj))
        return;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALN_START,
                                       FTNESS_SPECIALN_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}

/// Ness's aerial PK Flash Charge Collision callback
void ftNess_SpecialAirNHold_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!func_80081D0C(gobj))
        return;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALN_HOLD,
                                       FTNESS_SPECIALN_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}

/// Ness's aerial PK Flash Release Collision callback
void ftNess_SpecialAirNEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!func_80081D0C(gobj))
        return;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, AS_NESS_SPECIALN_END,
                                       FTNESS_SPECIALN_COLL_FLAG, NULL,
                                       fp->x894_currentAnimFrame, 1, 0);
}
