#include "ftsamus2.h"

#include "ftsamus.h"
#include "ftsamus6.h"
#include "types.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"

#include <trigf.h>

void ftSs_Init_80128944(HSD_GObj* gobj, f32 farg1, f32 farg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* attr = fp->x2D4_specialAttributes;
    f32 float_result = ftSs_Init_80128AC8(gobj, farg1, farg2);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftColl_8007B868(gobj)) {
        switch (fp->x2070.x2071_b0_3) {
        case 0:
        case 2:
        case 3:
        case 4:
            if ((fp->x2070.x2073 == 0x14) || ((fp->x2070.x2071_b5) == 0)) {
                if (fp->x5F5 == 2) {
                    ftSs_Init_80128B1C(gobj, float_result, attr->x0, 1.0f);
                } else {
                    ftSs_Init_80128B1C(gobj, float_result, 0.0f, 1.0f);
                }
            }
        }
    }
}

bool ftSs_Init_80128A1C(HSD_GObj* gobj, unk_t arg1, f32 farg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int i;

    for (i = 0; i < fp->x119E_hurtboxNum; i++) {
        if (lbColl_80008248(arg1, &fp->x11A0_fighterHurtbox[i],
                            *ftCommon_8007F804(fp), farg1, fp->x34_scale.y,
                            fp->cur_pos.z))
        {
            return true;
        }
    }

    return false;
}

f32 ftSs_Init_80128AC8(HSD_GObj* gobj, f32 farg1, f32 farg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* attr = getFtSpecialAttrs(fp);
    f32 value = (fp->cur_pos.x - farg1) / farg2;
    if (value >= 1.0f) {
        value = 1.0f;
    }
    if (value <= -1.0f) {
        value = -1.0f;
    }
    return (-attr->x4 * value) + 1.5707963705062866f;
}

inline void ftSamus_80128B1C_inner(HSD_GObj* gobj, f32 angle)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct attr* ftAttr = &fp->x110_attr;
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);

    fp = GET_FIGHTER(gobj);
    fp->x80_self_vel.x = samus_attr->x8 * cosf(angle);
    fp->x80_self_vel.y = samus_attr->x8 * sinf(angle);
    ftCommon_8007D440(fp, ftAttr->x17C_AerialDriftMax * samus_attr->x10);
}

void ftSs_Init_80128B1C(HSD_GObj* gobj, f32 angle, f32 arg9, f32 argA)
{
    Fighter* fp;
    Fighter* fighter2;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = fighter2 = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftSamus_80128B1C_inner(gobj, angle);
    fp->x2200_ftcmd_var0 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->sv.ss.unk2.x0 = 0;
    if (fp->xE0_ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fighter2);
    }
    Fighter_ChangeMotionState(gobj, 0x156, 0, 0, arg9, argA, 0.0f);
    ftAnim_8006EBA4(gobj);
}

void ftSs_SpecialLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->x2200_ftcmd_var0) && (!fp->sv.ss.unk2.x0)) {
        ftSs_SpecialLw_8012AEBC(gobj);
        fp->sv.ss.unk2.x0 = 1;
    }
    if ((!fp->x2200_ftcmd_var0) && (fp->sv.ss.unk2.x0)) {
        ftSs_SpecialLw_8012AF38(gobj);
        fp->sv.ss.unk2.x0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftSs_SpecialAirLw_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if ((fp->x2200_ftcmd_var0) && (!fp->sv.ss.unk2.x0)) {
        ftSs_SpecialLw_8012AEBC(gobj);
        fp->sv.ss.unk2.x0 = 1;
    }
    if ((!fp->x2200_ftcmd_var0) && (fp->sv.ss.unk2.x0)) {
        ftSs_SpecialLw_8012AF38(gobj);
        fp->sv.ss.unk2.x0 = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftSs_SpecialLw_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if ((fp->x2204_ftcmd_var1) && (fp->input.x624_lstick_y < samus_attr->x14))
    {
        fp->x2204_ftcmd_var1 = 0;
        ft_800D638C(gobj);
        return;
    }

    if (ft_80096540(gobj)) {
        return;
    }
    if (ft_800D695C(gobj)) {
        return;
    }
    if (ft_800D6824(gobj)) {
        return;
    }
    if (ft_800D68C0(gobj)) {
        return;
    }
    if (ft_800D8990(gobj)) {
        return;
    }
    if (ft_8008BFC4(gobj)) {
        return;
    }
    if (ft_8008C830(gobj)) {
        return;
    }
    if (ft_8008CB44(gobj)) {
        return;
    }
    if (ft_8008B658(gobj)) {
        return;
    }
    if (ft_8008B980(gobj)) {
        return;
    }
    if (ft_8008BB44(gobj)) {
        return;
    }
    if (ft_8008A9F8(gobj)) {
        return;
    }
    if (ft_80099794(gobj)) {
        return;
    }
}

void ftSs_SpecialAirLw_IASA(HSD_GObj* gobj)
{
    ft_800CCAAC(gobj);
}

void ftSs_SpecialLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    struct attr* ftAttr = &fp->x110_attr;

    if (fp->x2200_ftcmd_var0) {
        f32 samus_attr_xC = samus_attr->xC;
        ftCommon_8007CADC(fp, 0.0f,
                          ftAttr->x110_WalkInitialVelocity * samus_attr_xC,
                          ftAttr->x118_WalkMaximumVelocity * samus_attr_xC);
        ftCommon_8007CB74(gobj);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftSs_SpecialAirLw_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;
    struct attr* ftAttr = &fp->x110_attr;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftCommon_8007D4B8(fp);
    ftCommon_8007D344(fp, 0.0f,
                      ftAttr->x154_GroundToAirJumpMomentumMultiplier *
                          samus_attr->x10,
                      ftAttr->x158_JumpHMaxVelocity * samus_attr->x10);
}

void ftSs_SpecialLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2200_ftcmd_var0) {
        /// @todo Remove cast.
        if (!ft_80082888(gobj,
                         (ftCollisionBox*) &samus_attr->height_attributes))
        {
            ftSs_SpecialLw_80129048(gobj);
        }
    } else if (!ft_800827A0(gobj)) {
        ftSs_SpecialLw_80129048(gobj);
    }
}

void ftSs_SpecialAirLw_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->x2200_ftcmd_var0) {
        if (ft_800824A0(gobj,
                        (ftCollisionBox*) &samus_attr->height_attributes))
        {
            ftSs_SpecialLw_801290A4(gobj);
        }
    } else if (ft_80081D0C(gobj)) {
        ftSs_SpecialLw_801290A4(gobj);
    }
}

void ftSs_SpecialLw_80129048(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 0x156, 0x10, 0, fp->x894_currentAnimFrame,
                              fp->x89C_frameSpeedMul, 0.0f);
}

void ftSs_SpecialLw_801290A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 0x155, 0x10, 0, fp->x894_currentAnimFrame,
                              fp->x89C_frameSpeedMul, 0.0f);
}

int ftSs_SpecialLw_80129100(HSD_GObj* gobj, s32* arg1, s32* arg2)
{
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4];
#endif

        if (!fp->ev.ss.x222C) {
            return -1;
        }

        *arg1 = fp->ev.ss.x2230;
        *arg2 = samus_attr->x18;
        return 0;
    }

    return -1;
}

s32 ftSs_SpecialLw_80129158(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        s32 action_state_index = fp->action_id;
        switch (action_state_index) {
        case 0x157:
        case 0x158:
        case 0x159:
        case 0x15A:
        case 0x15B:
        case 0x15C:
            if (fp->x2070.x2071_b6) {
                return 1;
            }
            return 0;
        }

        return 1;
    }
    return 1;
}

s32 ftSs_SpecialN_801291A8(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        s32 action_state_index = fp->action_id;

        switch (action_state_index) {
        case 0x157:
        case 0x158:
        case 0x15A:
        case 0x15B:
        case 0x15C:
            return 0;
        }

        return 1;
    }
    return 1;
}
