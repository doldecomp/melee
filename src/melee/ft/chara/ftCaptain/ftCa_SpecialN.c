#include "ft/forward.h"

#include "ftCa_SpecialN.h"

#include "ftCa_Init.h"
#include "types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "lb/lb_00F9.h"

#include <trigf.h>

/// Create Aesthetic Wind Effect for Warlock Punch
static void ftCaptain_SpecialN_CreateWindEffect(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    int cur_frame = fp->cur_anim_frame;
    FighterKind kind = ftLib_800872A4(gobj);

    switch (kind) {
    case FTKIND_CAPTAIN:
        return;
    case FTKIND_GANON:
        if (cur_frame & 1) {
            if (cur_frame >= 16 && cur_frame <= 50) {
                lb_800119DC(&fp->cur_pos, 2, 2, 2, 0);
            } else if (cur_frame >= 51 && cur_frame <= 68) {
                lb_800119DC(&fp->cur_pos, 2, 4, 4, 0);
            }
        }
        return;
    }
}

/// Calculate angle from control stick input - inline
static f32 ftCaptain_SpecialN_GetAngleVel(Fighter* fp)
{
    ftCaptain_DatAttrs* da = fp->dat_attrs;
    {
        /// @todo Join declarations and assignments somehow.
        f32 max;
        f32 stick_y = stickGetDir(fp->input.x624_lstick_y, 0);
        f32 min;
        max = da->specialn_stick_range_y_pos;
        if (stick_y > max) {
            stick_y = max;
        }
        min = da->specialn_stick_range_y_neg;
        stick_y -= min;
        if (stick_y < 0) {
            stick_y = 0;
        }
        if (fp->input.x624_lstick_y < 0) {
            stick_y = -stick_y;
        }
        {
            /// @todo Eliminate @c f.
            f32 f = DEG_TO_RAD;
            return f * (stick_y * da->specialn_angle_diff / (max - min));
        }
    }
}

void ftCa_SpecialN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
/// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialN, 0, NULL, 0, 1, 0);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    ftAnim_8006EBA4(gobj);
}

void ftCa_SpecialAirN_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirN, 0, NULL, 0, 1, 0);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    ftAnim_8006EBA4(gobj);
}

void ftCa_SpecialN_Anim(HSD_GObj* gobj)
{
    ftCaptain_SpecialN_CreateWindEffect(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCa_SpecialAirN_Anim(HSD_GObj* gobj)
{
    ftCaptain_SpecialN_CreateWindEffect(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

void ftCa_SpecialN_IASA(HSD_GObj* gobj) {}

void ftCa_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// @todo Fake double assignment.
    ftCaptain_DatAttrs* da = da = getFtSpecialAttrs(fp);
    if (fp->cmd_vars[0] != 0) {
        fp->cmd_vars[0] = 0;
        {
            f32 vel = ftCaptain_SpecialN_GetAngleVel(fp);
            fp->self_vel.y = da->specialn_vel_x * sinf(vel);
            fp->self_vel.x = da->specialn_vel_x * (fp->facing_dir * cosf(vel));
        }
    }
}

static inline void doPhys(HSD_GObj* gobj)
{
    bool throw_b1;
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->throw_flags.b1) {
        fp->throw_flags.b1 = false;
        throw_b1 = true;
    } else {
        throw_b1 = false;
    }
    if (throw_b1) {
        if (!fp->x2219_b0) {
            FighterKind kind = ftLib_800872A4(gobj);
            switch (kind) {
            case FTKIND_CAPTAIN:
                efSync_Spawn(1167, gobj, fp->parts[FtPart_TopN].x0_jobj,
                             fp->parts[57].x0_jobj);
                break;
            case FTKIND_GANON:
                efSync_Spawn(1291, gobj, fp->parts[FtPart_TopN].x0_jobj,
                             fp->parts[78].x0_jobj);
                break;
            }
            fp->x2219_b0 = true;
        } else {
            ftCommon_8007DB24(gobj);
        }
    }
}

void ftCa_SpecialN_Phys(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    doPhys(gobj);
    ft_80084FA8(gobj);
}

void ftCa_SpecialAirN_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    /// @todo Fake double assignment.
    ftCaptain_DatAttrs* da = da = getFtSpecialAttrs(fp);
    doPhys(gobj);
    switch (fp->cmd_vars[1]) {
    case 0: {
        ft_80084EEC(gobj);
        return;
    }
    case 1: {
        fp->self_vel.y *= da->specialn_vel_mul;
        fp->self_vel.x *= da->specialn_vel_mul;
        return;
    }
    case 2: {
        ft_80084DB0(gobj);
        return;
    }
    default:
        return;
    }
}

/// @todo Share with #ftCa_Init_MotionStateTable
static u32 const transition_flags =
    Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipRumble | Ft_MF_UpdateCmd |
    Ft_MF_SkipColAnim | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftCa_SpecialN_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirN, transition_flags,
                                  NULL, fp->cur_anim_frame, 1, 0);
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        ftCommon_8007D468(fp);
    }
}

void ftCa_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialN, transition_flags,
                                  NULL, fp->cur_anim_frame, 1, 0);
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}
