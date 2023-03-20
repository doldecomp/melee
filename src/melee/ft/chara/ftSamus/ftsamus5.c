#include <melee/ft/chara/ftSamus/ftsamus5.h>

#include <melee/ef/eflib.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftSamus/ftsamus.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcliffcommon.h>
#include <melee/ft/ftparts.h>

void ftSamus_SpecialHi_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x161, 0, NULL, 0.0f, 1.0f,
                                       0.0f);
    ftSamus_updateDamageDeathCBs(fighter_gobj);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8007D7FC(fp);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->sv.ss.unk5.x0 = 0;
    func_8006EBA4(fighter_gobj);
    ef_Spawn(0x482, fighter_gobj, fp->x5E8_fighterBones[3].x0_jobj);
    fp->ev.ss.x2244 = 1;
}

void ftSamus_SpecialAirHi_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x162, 0, NULL, 0.0f, 1.0f,
                                       0.0f);
    ftSamus_updateDamageDeathCBs(fighter_gobj);
    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    func_8007D60C(fp);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->sv.ss.unk5.x0 = 0;
    fp->x80_self_vel.y = samus_attr->x44;
    func_8007D440(fp, samus_attr->x40);
    func_8006EBA4(fighter_gobj);
    ef_Spawn(0x482, fighter_gobj, fp->x5E8_fighterBones[3].x0_jobj);
    fp->ev.ss.x2244 = 1;
}

void ftSamus_DestroyAllUnsetx2444(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    efLib_DestroyAll(fighter_gobj);
    fp->ev.ss.x2244 = 0;
}

void ftSamus_8012A81C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;
    samus_attr = samus_attr2 = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fighter2 = fp;
        ftSamus_DestroyAllUnsetx2444(fighter_gobj);
        func_8007D60C(fighter2);
        if (samus_attr->x50 == 0.0f) {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}

void ftSamus_8012A8C4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr;
    ftSamusAttributes* samus_attr2;
    samus_attr = samus_attr2 = fp->x2D4_specialAttributes;

    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        Fighter* fighter2 = fp;
        ftSamus_DestroyAllUnsetx2444(fighter_gobj);
        func_8007D60C(fighter2);
        if (samus_attr->x50 == 0.0f) {
            func_800CC730(fighter_gobj);
            return;
        }
        func_80096900(fighter_gobj, 1, 1, 0, samus_attr->x48, samus_attr->x50);
    }
}

void ftSamus_8012A96C(HSD_GObj* fighter_gobj)
{
    f32 mag;
    f32 lstick_x;
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if ((!fp->x2204_ftcmd_var1) && (!fp->sv.ss.unk5.x0)) {
        if ((lstick_x = fp->input.x620_lstick_x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        if (mag > samus_attr->x4C) {
            if (((fp->facing_dir == 1.0f) && (lstick_x < 0.0f)) ||
                ((fp->facing_dir == -1.0f) && (lstick_x > 0.0f)))
            {
                fp->x2204_ftcmd_var1 = 1;
                fp->sv.ss.unk5.x0 = 1;
                func_8007D9FC(fp);
                func_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

void ftSamus_8012AA3C(HSD_GObj* fighter_gobj)
{
    f32 mag;
    f32 lstick_x;
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if ((!fp->x2204_ftcmd_var1) && (!fp->sv.ss.unk5.x0)) {
        if ((lstick_x = fp->input.x620_lstick_x) < 0.0f) {
            mag = -lstick_x;
        } else {
            mag = lstick_x;
        }
        if (mag > samus_attr->x4C) {
            if (((fp->facing_dir == 1.0f) && (lstick_x < 0.0f)) ||
                ((fp->facing_dir == -1.0f) && (lstick_x > 0.0f)))
            {
                fp->x2204_ftcmd_var1 = 1;
                fp->sv.ss.unk5.x0 = 1;
                func_8007D9FC(fp);
                func_80075AF0(fp, 0, M_PI_2 * fp->facing_dir);
            }
        }
    }
}

void ftSamus_8012AB0C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = getFtSpecialAttrs(fp);

    if (fp->x2200_ftcmd_var0) {
        func_8007D60C(fp);
        fp->x2200_ftcmd_var0 = 0;
        fp->x80_self_vel.x = samus_attr->x38 * fp->facing_dir;
    }
    if (fp->xE0_ground_or_air == 1) {
        func_800851C0(fighter_gobj);
        func_8007D344(fp, 0.0f, samus_attr->x3C, samus_attr->x40);
        func_8007D268(fp);
        return;
    }
    func_80084F3C(fighter_gobj);
}

void ftSamus_8012ABB4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    func_80084DB0(fighter_gobj);
    func_8007D344(fp, 0.0f, samus_attr->x3C, samus_attr->x40);
}

void ftSamus_8012AC00(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (fp->xE0_ground_or_air == GA_Air) {
        int direction;

        if (fp->x80_self_vel.y >= 0.0f) {
            func_80081D0C(fighter_gobj);
            return;
        }
        if (fp->facing_dir == 1.0f) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (EnvColl_CheckGroundAndLedge(fighter_gobj, direction)) {
            ftSamus_DestroyAllUnsetx2444(fighter_gobj);
            func_800D5CB0(fighter_gobj, 0, samus_attr->x50);
            return;
        }
        if (func_80081298(fighter_gobj)) {
            ftSamus_DestroyAllUnsetx2444(fighter_gobj);
            func_80081370(fighter_gobj);
        }
    } else {
        func_80084104(fighter_gobj);
    }
}

void ftSamus_8012ACF8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftSamusAttributes* samus_attr = fp->x2D4_specialAttributes;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->xE0_ground_or_air == GA_Air) {
        int direction;

        if (fp->x80_self_vel.y >= 0.0f) {
            func_80081D0C(fighter_gobj);
            return;
        }
        if (fp->facing_dir == 1.0f) {
            direction = 1;
        } else {
            direction = -1;
        }
        if (EnvColl_CheckGroundAndLedge(fighter_gobj, direction)) {
            ftSamus_DestroyAllUnsetx2444(fighter_gobj);
            func_800D5CB0(fighter_gobj, 0, samus_attr->x50);
            return;
        }
        if (func_80081298(fighter_gobj)) {
            ftSamus_DestroyAllUnsetx2444(fighter_gobj);
            func_80081370(fighter_gobj);
        }
    } else {
        func_80084104(fighter_gobj);
    }
}
