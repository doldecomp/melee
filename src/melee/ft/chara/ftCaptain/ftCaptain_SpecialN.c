#include "ftCaptain_SpecialN.h"

#include "ftCaptain_Init.h"
#include "types.h"

#include "ef/eflib.h"
#include "ef/efsync.h"
#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/types.h"
#include "lb/lbunknown_003.h"

#include <trigf.h>

/// Create Aesthetic Wind Effect for Warlock Punch
void ftCaptain_SpecialN_CreateWindEffect(HSD_GObj* gobj)
{
    s32 currentAnimFrame;
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ftKind;

    currentAnimFrame = (s32) fp->x894_currentAnimFrame;

    ftKind = func_800872A4(gobj);
    switch (ftKind) {
    case FTKIND_CAPTAIN:
        break;
    case FTKIND_GANON:
        if (currentAnimFrame & 1) {
            if ((currentAnimFrame >= 16) && (currentAnimFrame <= 50)) {
                func_800119DC(&fp->cur_pos, 2, 2.0f, 2.0f, 0.0f);
            } else if ((currentAnimFrame >= 51) && (currentAnimFrame <= 68)) {
                func_800119DC(&fp->cur_pos, 2, 4.0f, 4.0f, 0.0f);
            }
        }
        break;
    }
}

/// Calculate angle from control stick input - inline
f32 ftCaptain_SpecialN_GetAngleVel(Fighter* fp)
{
    ftCaptain_DatAttrs* tempAttrs = fp->x2D4_specialAttributes;

    f32 stickRangeMinPos;
    f32 stickRangeMinNeg;
    f32 stick_y;
    f32 floatVar = 0.01745329238474369f;

    stick_y = stickGetDir(fp->input.x624_lstick_y, 0.0f);

    stickRangeMinPos = tempAttrs->specialn_stick_range_y_pos;
    if (stick_y > stickRangeMinPos) {
        stick_y = stickRangeMinPos;
    }

    stickRangeMinNeg = tempAttrs->specialn_stick_range_y_neg;
    stick_y -= stickRangeMinNeg;

    if (stick_y < 0.0f) {
        stick_y = 0.0f;
    }
    if (fp->input.x624_lstick_y < 0.0f) {
        stick_y = -stick_y;
    }
    return floatVar * ((stick_y * tempAttrs->specialn_angle_diff) /
                       (stickRangeMinPos - stickRangeMinNeg));
}

void ftCaptain_SpecialN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialN, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8006EBA4(gobj);
}

void ftCaptain_SpecialAirN_StartMotion(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirN, 0, NULL, 0.0f, 1.0f,
                              0.0f);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8006EBA4(gobj);
}

void ftCaptain_SpecialN_Anim(HSD_GObj* gobj)
{
    ftCaptain_SpecialN_CreateWindEffect(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8008A2BC(gobj);
    }
}

void ftCaptain_SpecialAirN_Anim(HSD_GObj* gobj)
{
    ftCaptain_SpecialN_CreateWindEffect(gobj);

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_800CC730(gobj);
    }
}

void ftCaptain_SpecialN_IASA(HSD_GObj* gobj)
{
    return;
}

void ftCaptain_SpecialAirN_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* captainAttrs = captainAttrs = getFtSpecialAttrs(fp);

    f32 vel;

    if ((u32) fp->x2200_ftcmd_var0 != 0U) {
        fp->x2200_ftcmd_var0 = 0U;
        vel = ftCaptain_SpecialN_GetAngleVel(fp);
        fp->x80_self_vel.y = (f32) (captainAttrs->specialn_vel_x * sinf(vel));
        fp->x80_self_vel.x = (f32) (captainAttrs->specialn_vel_x *
                                    (fp->facing_dir * cosf(vel)));
    }
}

void ftCaptain_SpecialN_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ftKind;
    s32 flag;

    fp = GET_FIGHTER(gobj);
    if (fp->x2210_ThrowFlags.b1 != 0) {
        fp->x2210_ThrowFlags.b1 = 0;
        flag = true;
    } else {
        flag = false;
    }
    if (flag != false) {
        if (fp->x2219_flag.bits.b0 == 0) {
            ftKind = func_800872A4(gobj);
            switch (ftKind) {
            case 2:
                ef_Spawn(0x48F, gobj, fp->x5E8_fighterBones[0].x0_jobj,
                         fp->x5E8_fighterBones[0x39].x0_jobj);
                break;
            case 25:
                ef_Spawn(0x50B, gobj, fp->x5E8_fighterBones[0].x0_jobj,
                         fp->x5E8_fighterBones[0x4E].x0_jobj);
                break;
            }
            fp->x2219_flag.bits.b0 = 1;
        } else {
            func_8007DB24(gobj);
        }
    }
    func_80084FA8(gobj);
}

void ftCaptain_SpecialAirN_Phys(HSD_GObj* gobj)
{
    Fighter* fp = fp = GET_FIGHTER(gobj);
    ftCaptain_DatAttrs* captainAttrs = captainAttrs = getFtSpecialAttrs(fp);
    s32 ftKind;
    s32 flag;

    if (fp->x2210_ThrowFlags.b1 != 0) {
        fp->x2210_ThrowFlags.b1 = 0;
        flag = true;
    } else {
        flag = false;
    }
    if (flag != false) {
        if (fp->x2219_flag.bits.b0 == 0) {
            ftKind = func_800872A4(gobj);
            switch (ftKind) {
            case 2:
                ef_Spawn(0x48F, gobj, fp->x5E8_fighterBones[0].x0_jobj,
                         fp->x5E8_fighterBones[0x39].x0_jobj);
                break;
            case 25:
                ef_Spawn(0x50B, gobj, fp->x5E8_fighterBones[0].x0_jobj,
                         fp->x5E8_fighterBones[0x4E].x0_jobj);
                break;
            }
            fp->x2219_flag.bits.b0 = 1;
        } else {
            func_8007DB24(gobj);
        }
    }
    switch (fp->x2204_ftcmd_var1) {
    case 0:
        func_80084EEC(gobj);
        break;

    case 1:
        fp->x80_self_vel.y *= captainAttrs->specialn_vel_mul;
        fp->x80_self_vel.x *= captainAttrs->specialn_vel_mul;
        break;

    case 2:
        func_80084DB0(gobj);
    }
}

static Fighter_MotionStateChangeFlags const transition_flags =
    FtStateChange_PreserveGfx | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_SkipUpdateRumble | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateColAnim | FtStateChange_SkipUpdateItemVis |
    FtStateChange_Unk_19 | FtStateChange_SkipUpdateModelPartVis |
    FtStateChange_SkipUpdateModelFlag | FtStateChange_Unk_27;

void ftCaptain_SpecialN_Coll(HSD_GObj* gobj)
{
    if (func_800827A0(gobj) == false) {
        Fighter* fp = GET_FIGHTER(gobj);
        func_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialAirN, transition_flags,
                                  NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
        func_8007D468(fp);
    }
}

void ftCaptain_SpecialAirN_Coll(HSD_GObj* gobj)
{
    if (func_80081D0C(gobj) != false) {
        Fighter* fp = GET_FIGHTER(gobj);
        func_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, ftCa_MS_SpecialN, transition_flags,
                                  NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
        fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    }
}
