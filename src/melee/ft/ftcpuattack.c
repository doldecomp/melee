#include "ftcpuattack.h"

#include "ftcmdscript.h"

#include <melee/ft/chara/ftDonkey/forward.h>
#include <melee/ft/chara/ftKoopa/forward.h>
#include <melee/ft/chara/ftSamus/forward.h>
#include <melee/ft/chara/ftYoshi/forward.h>
#include <melee/ft/chara/ftZelda/forward.h>

#include <math.h>
#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/chara/ftCommon/ftCo_09F7.h>
#include <melee/ft/chara/ftCommon/ftCo_0A01.h>
#include <melee/ft/fighter.h>
#include <melee/ft/inlines.h>
#include <melee/gr/ground.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/lb/lb_00CE.h>
#include <melee/lb/lbcollision.h>
#include <melee/mp/mpisland.h>
#include <melee/mp/mplib.h>
#include <melee/mp/types.h>

/// #ftCo_800B4AB0

/// #ftCo_800B52AC

/// #ftCo_800B5AB0

/// #ftCo_800B6208

/// Return true if the fighter is currently in any attacking motion state
bool ftCo_800B630C(Fighter* fp)
{
    // Any common attack
    if (fp->motion_id >= ftCo_MS_Attack11 &&
        fp->motion_id <= ftCo_MS_AttackAirLw)
    {
        return true;
    }
    // Swinging an item or shooting with it
    if (ftCo_800A5A90(fp)) {
        return true;
    }
    if (fp->kind == FTKIND_DONKEY) {
        // Any of DK's common moves, or cargo carry / throw
        if (fp->motion_id <= ftDk_MS_ThrowAirFLw) {
            return false;
        }
    } else if (fp->kind == FTKIND_KIRBY) {
        // Any of Kirby's common moves, or air jump / dash attack?
        if (fp->motion_id <= ftKb_MS_AttackDashAir) {
            return false;
        }
    } else if (fp->kind == FTKIND_PEACH) {
        // Any of Peach's common moves, or float fall
        if (fp->motion_id <= ftPe_MS_FloatFallB) {
            return false;
        }
    } else {
        // Are we in any other common motion state?
        if (fp->motion_id < ftCo_MS_Count) {
            return false;
        }
    }
    return true;
}

/**
 * Tells the fighter to wait for a random amount of time, based on the CPU
 * level. Lower CPU levels wait for longer. Level 9 doesn't wait at all.
 */
void ftCo_800B63D8(Fighter* fp)
{
    f32 temp_f1 = HSD_Randf();
    switch (fp->x1A88.level) {
    case 0:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (40 * temp_f1) + 5);
        break;
    case 1:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (35 * temp_f1) + 5);
        break;
    case 2:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (30 * temp_f1) + 5);
        break;
    case 3:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (25 * temp_f1) + 5);
        break;
    case 4:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (25 * temp_f1));
        break;
    case 5:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (20 * temp_f1));
        break;
    case 6:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (15 * temp_f1));
        break;
    case 7:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (10 * temp_f1));
        break;
    case 8:
        ftCo_800B46B8(fp, CpuCmd_WaitFor, (int) (5 * temp_f1));
        break;
    }
}

void ftCo_800B658C(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;
    Fighter* temp_r0 = fp->x1A88.x44;

    if (temp_r0 == NULL) {
        temp_r31->x44 = NULL;
        temp_r31->x18 = temp_r31->x1C;
        ftCo_800A0C8C(fp);
        return;
    }

    if (temp_r31->xF8_b6 && fp->ground_or_air == GA_Ground &&
        HSD_Randf() < 0.05F * temp_r31->level)
    {
        temp_r31->xF8_b6 = false;
        if (ftCo_800BA2E8(fp, temp_r0)) {
            return;
        }
    }

    if (fp->kind == FTKIND_NESS) {
        if (fp->motion_id >= ftNs_MS_SpecialNStart &&
            fp->motion_id <= ftNs_MS_SpecialNEnd)
        {
            ftCo_800B920C(fp);
            return;
        }
        if (fp->motion_id >= ftNs_MS_SpecialHiStart &&
            fp->motion_id <= ftNs_MS_SpecialAirHiRebound)
        {
            ftCo_800B92D4(fp);
            return;
        }
    } else if (fp->kind == FTKIND_YOSHI) {
        if (fp->motion_id >= ftYs_MS_SpecialAirSStart_0 &&
            fp->motion_id <= ftYs_MS_SpecialAirSEnd)
        {
            ftCo_800B9340(fp);
            return;
        }
    } else if (fp->kind == FTKIND_SAMUS) {
        if (fp->motion_id == ftSs_MS_SpecialNHold) {
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
        }
    } else if (fp->kind == FTKIND_DONKEY) {
        if (fp->motion_id == ftDk_MS_SpecialNLoop) {
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
        }
    } else if (fp->kind == FTKIND_ZELDA) {
        if (fp->motion_id >= ftZd_MS_SpecialSLoop &&
            fp->motion_id <= ftZd_MS_SpecialAirSEnd)
        {
            ftCo_800B9504(fp);
            return;
        }
    }

    if (ftCo_800B630C(fp)) {
        ftCo_800A0C8C(fp);
        temp_r31->xA4 = 0;
        return;
    }
    if (temp_r31->xA4 == 0) {
        if (fp->ground_or_air == GA_Ground && !ftCo_800A2C08(fp)) {
            ftCo_800A0098(fp);
            return;
        }
        if (!ftCo_800B8A9C(fp)) {
            fp->x1A88.x44 = NULL;
            fp->x1A88.x18 = fp->x1A88.x1C;
            ftCo_800A0C8C(fp);
            return;
        }
    }
    ftCo_800B63D8(fp);
    ftCo_800B4880(fp, temp_r31->xA4);
    temp_r31->xA4 = 0;
}

void ftCo_800B683C(Fighter* fp)
{
    u8 _[0xC];
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;
    bool var_r30;

    Vec3 sp78;
    Vec3 sp6C;

    u8 _2[0x18];

    Fighter* var_r3;
    f32 temp_f31;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f2;

    f32 var_f2_2;
    mp_UnkStruct0* temp_r3_2;
    mp_UnkStruct0* temp_r3_3;
    s32 temp_r0;
    s32 temp_r0_2;

    Vec3 sp30;
    Vec3 sp24;

    if (fp->victim_gobj == NULL) {
        temp_r31->x44 = 0;
        temp_r31->x18 = temp_r31->x1C;
        ftCo_800A0C8C(fp);
        return;
    }
    var_r30 = false;
    if (fp->kind == FTKIND_DONKEY && fp->motion_id >= 0x15F &&
        fp->motion_id <= 0x164)
    {
        temp_r3_2 = mpIsland_8005AC14(&fp->cur_pos, -10.0f);
        if (temp_r3_2 == NULL) {
            ftCo_800B463C(fp, CpuCmd_Done);
            return;
        }
        mpIsland_8005ACE8(temp_r3_2, &sp6C, &sp78);
        var_f2 = ABS(fp->cur_pos.x - sp78.x);
        var_f1 = ABS(fp->cur_pos.x - sp6C.x);
        if (var_f2 < var_f1) {
            if (var_f2 > 10.0) {
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x7F);
                ftCo_800B463C(fp, CpuCmd_Done);
            } else {
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x7F);
                ftCo_800B463C(fp, CpuCmd_PressA);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B463C(fp, CpuCmd_ReleaseA);
                ftCo_800B463C(fp, CpuCmd_Done);
            }
        } else if (var_f1 > 10.0) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x81);
            ftCo_800B463C(fp, CpuCmd_Done);
        } else {
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x81);
            ftCo_800B463C(fp, CpuCmd_PressA);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B463C(fp, CpuCmd_ReleaseA);
            ftCo_800B463C(fp, CpuCmd_Done);
        }
        return;
    } else if ((fp->kind == FTKIND_KOOPA || fp->kind == FTKIND_GKOOPS) &&
               fp->motion_id == 0x15E)
    {
        var_r30 = true;
    } else if (fp->kind == FTKIND_KIRBY && fp->motion_id >= 0x164 &&
               fp->motion_id <= 0x17E)
    {
        if (fp->victim_gobj != NULL) {
            var_r3 = GET_FIGHTER(fp->victim_gobj);
        } else {
            var_r3 = NULL;
        }
        if (var_r3 != NULL && var_r3->kind == FTKIND_KIRBY) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_PressA);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseA);
            ftCo_800B463C(fp, CpuCmd_Done);
        } else {
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, -0x7F);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B463C(fp, CpuCmd_Done);
        }
        return;
    } else if (fp->kind == FTKIND_POPO) {
        if (temp_r31->x94 == 0 && temp_r31->level > 4 &&
            HSD_Randf() < 0.05f * temp_r31->level)
        {
            ftCo_800B4880(fp, 0x3B);
            return;
        }
    } else if (fp->kind == FTKIND_MARIO) {
        if (temp_r31->x94 == 0 && temp_r31->level < 5 &&
            HSD_Randf() < 0.05f * temp_r31->level)
        {
            ftCo_800B4880(fp, 0x35);
            return;
        }
    } else if (fp->kind == FTKIND_FOX) {
        if (temp_r31->x94 == 0 && temp_r31->level > 4 &&
            HSD_Randf() < 0.05f * temp_r31->level)
        {
            ftCo_800B4880(fp, 0x3D);
            return;
        }
    } else if (fp->kind == FTKIND_CAPTAIN) {
        if (temp_r31->x94 == 0 && temp_r31->level > 4 &&
            HSD_Randf() < 0.05f * temp_r31->level)
        {
            if (GET_FIGHTER(fp->victim_gobj)->dmg.x1830_percent < 100.0f) {
                ftCo_800B4880(fp, 0x39);
                return;
            }
            ftCo_800B4880(fp, 0x3A);
            return;
        }
    }
    if (ftCo_IsGrabbing(fp) != 0) {
        float tmp = HSD_Randf();
        if ((f32) (tmp * (1.0 + temp_r31->x94)) < 0.5f) {
            if (var_r30) {
                ftCo_800B4880(fp, 0x11);
            } else {
                ftCo_800B4880(fp, 2);
            }
            temp_r31->x94++;
            return;
        }
        temp_r3_3 = mpIsland_8005AC14(&fp->cur_pos, -10.0f);
        if (temp_r3_3 != NULL) {
            mpIsland_8005ACE8(temp_r3_3, &sp24, &sp30);
            var_f2_2 = ABS(fp->cur_pos.x - sp30.x);
            var_f1_2 = ABS(fp->cur_pos.x - sp24.x);
            if (var_f2_2 > var_f1_2) {
                if (var_f1_2 < 30.0) {
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, -0x50);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, -0x7F);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                    ftCo_800B463C(fp, CpuCmd_Done);
                    return;
                }
            } else {
                if (var_f2_2 < 30.0) {
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x50);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x7F);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                    ftCo_800B463C(fp, CpuCmd_Done);
                    return;
                }
            }
        }
        temp_f31 = HSD_Randf();
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        if (temp_f31 < 0.25) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x50);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
        } else if (temp_f31 < 0.5) {
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0xB0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x81);
        } else if (temp_f31 < 0.75) {
            ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x50);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x7F);
        } else {
            ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0xB0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B46B8(fp, CpuCmd_LstickXForward, 0x81);
        }
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800A0C8C(fp);
    }
}

void ftCo_800B7180(Fighter* fp)
{
    Fighter* temp_r30;
    s32 temp_r0;
    struct Fighter_x1A88_t* temp_r31;

    temp_r31 = &fp->x1A88;
    temp_r30 = fp->x1A88.x44;
    if (temp_r30 == NULL) {
        temp_r31->x18 = temp_r31->x1C;
        temp_r31->xF8_b34 = 0;
        ftCo_800B463C(fp, CpuCmd_Done);
    }
    switch (temp_r31->xF8_b34) {
    case 1:
        ftCo_800A05F4(fp);
        temp_r31->xF8_b34 = 3;
        break;
    case 2:
        ftCo_800A0798(fp);
        temp_r31->xF8_b34 = 3;
        break;
    case 3:
        if (fp->ground_or_air == GA_Air) {
            if (fp->pos_delta.y > 0.0) {
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_LstickXTowardFighter, 0x7F);
                ftCo_800B463C(fp, CpuCmd_Done);
            } else if (temp_r30->cur_pos.y > fp->cur_pos.y) {
                ftCo_800A05F4(fp);
            } else {
                temp_r31->x18 = temp_r31->x1C;
                temp_r31->xF8_b34 = 0;
                ftCo_800B463C(fp, CpuCmd_Done);
            }
        } else {
            temp_r31->x18 = temp_r31->x1C;
            temp_r31->xF8_b34 = 0;
            ftCo_800B463C(fp, CpuCmd_Done);
        }
        break;
    default:
        temp_r31->x18 = temp_r31->x1C;
        temp_r31->xF8_b34 = 0;
        ftCo_800B463C(fp, CpuCmd_Done);
        break;
    }
}

int ftCo_800B732C(Fighter* fp)
{
    Vec3 sp20;
    Vec3 sp14;
    int sp10;
    u32 spC;
    f32 temp_f1;
    f32 temp_f31;
    f32 temp_f31_2;
    struct Fighter_x1A88_t* temp_r29 = &fp->x1A88;
    Fighter* temp_r0 = fp->x1A88.x44;

    if (temp_r0 == NULL) {
        return 0;
    }
    if (fp->ground_or_air == GA_Air) {
        return 0;
    }
    if (ftCo_800A3200(temp_r0) != 0) {
        if (temp_r0->cur_pos.y < fp->cur_pos.y) {
            return 0;
        }
        if (mpCheckCeiling(fp->cur_pos.x, fp->cur_pos.y, temp_r0->cur_pos.x,
                           temp_r0->cur_pos.y, &sp20, &sp10, &spC, &sp14, -1,
                           -1))
        {
            return 0;
        }
        ftCo_800A1AB4(fp, temp_r0);
        if (lb_8000D008(temp_r0->cur_pos.y - fp->cur_pos.y,
                        ABS(temp_r0->cur_pos.x - fp->cur_pos.x)) > 1.3089969f)
        {
            return 1;
        }
        return 0;
    }
    if (!temp_r29->xF9_b3) {
        return 0;
    }
    if (temp_r29->xC == 0x10) {
        return ftCo_800B7638(fp);
    }
    if (ftCo_800A2BD4(fp) == 0) {
        return 0;
    }
    if (temp_r29->level < 4) {
        return 0;
    }
    if (ftCo_800A28D0(fp, 4.0f) != 0) {
        return 0;
    }
    if (temp_r0->ground_or_air == GA_Air) {
        if (temp_r0->cur_pos.y < fp->cur_pos.y) {
            return 0;
        }
        if (mpCheckCeiling(fp->cur_pos.x, fp->cur_pos.y, temp_r0->cur_pos.x,
                           temp_r0->cur_pos.y, &sp20, &sp10, &spC, &sp14, -1,
                           -1))
        {
            return 0;
        }
        temp_f31 = ftCo_800A1AB4(fp, temp_r0);
        if (lb_8000D008(temp_r0->cur_pos.y - fp->cur_pos.y,
                        ABS(temp_r0->cur_pos.x - fp->cur_pos.x)) >
                0.7853981573134661 &&
            temp_f31 < 30.0)
        {
            return 1;
        }
    } else {
        if (temp_r29->x7C % 60 != 0) {
            return 0;
        }
        if (HSD_Randf() > 0.1) {
            return 0;
        }
        temp_f31_2 = ftCo_800A1AB4(fp, temp_r0);
        temp_f1 = lb_8000D008(temp_r0->cur_pos.y - fp->cur_pos.y,
                              ABS(temp_r0->cur_pos.x - fp->cur_pos.x));
        if (temp_f31_2 > 30.0 && temp_f31_2 < 40.0 &&
            temp_f1 > -0.08726646192371845 && temp_f1 < 0.08726646192371845)
        {
            return 2;
        }
    }
    return 0;
}

int ftCo_800B7638(Fighter* fp)
{
    Fighter* target;
    f32 angle;
    f32 dist;

    u8 _[4];

    Vec3 sp24;
    Vec3 sp18;
    int sp14;
    u32 sp10;

    PAD_STACK(4);

    target = fp->x1A88.x44;
    if (target == NULL) {
        return 0;
    }
    if (fp->ground_or_air == GA_Air) {
        if (fp->co_attrs.max_jumps <= fp->x1968_jumpsUsed) {
            return 0;
        }
        if (fp->pos_delta.y > 0.0) {
            return 0;
        }
    }
    if (target->cur_pos.y - fp->cur_pos.y < 0.0) {
        return 0;
    }
    if (target->ground_or_air == GA_Air) {
        if (mpCheckCeiling(fp->cur_pos.x, fp->cur_pos.y, target->cur_pos.x,
                           target->cur_pos.y, &sp24, &sp14, &sp10, &sp18, -1,
                           -1))
        {
            return 0;
        }
        dist = ftCo_800A1AB4(fp, target);
        if (lb_8000D008(target->cur_pos.y - fp->cur_pos.y,
                        ABS(target->cur_pos.x - fp->cur_pos.x)) >
            0.7853981573134661)
        {
            return 1;
        }
    } else {
        dist = ftCo_800A1AB4(fp, target);
        angle = lb_8000D008(target->cur_pos.y - fp->cur_pos.y,
                            ABS(target->cur_pos.x - fp->cur_pos.x));
        if (dist > 30.0 && dist < 40.0 && angle > -0.08726646192371845 &&
            angle < 0.08726646192371845)
        {
            return 2;
        }
    }
    return 0;
}

/// #ftCo_800B77E8

bool ftCo_800B885C(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r4 = &fp->x1A88;
    switch (fp->x1A88.level) {
    case 0:
        if (temp_r4->x80 % 300 > 240) {
            return false;
        }
        return true;
    case 1:
        if (temp_r4->x80 % 300 > 180) {
            return false;
        }
        return true;
    case 2:
        if (temp_r4->x80 % 300 > 120) {
            return false;
        }
        return true;
    case 3:
        if (temp_r4->x80 % 240 > 120) {
            return false;
        }
        return true;
    case 4:
        if (temp_r4->x80 % 240 > 60) {
            return false;
        }
        return true;
    }
    return false;
}

bool ftCo_800B89CC(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;
    Fighter* tmp = fp->x1A88.x44;

    PAD_STACK(8);

    if (stage_info.internal_stage_id == KONGO &&
        (fp->cur_pos.x > 25.0F || fp->cur_pos.x < -25.0F))
    {
        return false;
    }
    if (ftCo_800A3200(tmp)) {
        return true;
    }
    if (!temp_r31->xF9_b4) {
        return false;
    }
    if (!temp_r31->xFA_b5 && fp->kind == FTKIND_KOOPA) {
        return false;
    }
    if (temp_r31->level < 4) {
        return false;
    }
    return true;
}

/// #ftCo_800B8A9C

void ftCo_800B9020(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;
    PAD_STACK(8);

    if (fp->x1A88.x44 == NULL) {
        temp_r31->x44 = 0;
        temp_r31->x18 = temp_r31->x1C;
        ftCo_800A0C8C(fp);
        return;
    }

    if (fp->kind == FTKIND_NESS) {
        if (fp->motion_id >= ftNs_MS_SpecialNStart &&
            fp->motion_id <= ftNs_MS_SpecialNEnd)
        {
            ftCo_800B920C(fp);
            temp_r31->x90++;
            return;
        }
        if (fp->motion_id >= ftNs_MS_SpecialHiStart &&
            fp->motion_id <= ftNs_MS_SpecialAirHiRebound)
        {
            ftCo_800B92D4(fp);
            temp_r31->x90++;
            return;
        }
    } else if (fp->kind == FTKIND_YOSHI) {
        if (fp->motion_id >= ftYs_MS_SpecialAirSStart_0 &&
            fp->motion_id <= ftYs_MS_SpecialAirSEnd)
        {
            ftCo_800B9340(fp);
            temp_r31->x90++;
            return;
        }
    } else if (fp->kind == FTKIND_ZELDA) {
        if (fp->motion_id >= ftZd_MS_SpecialSLoop &&
            fp->motion_id <= ftZd_MS_SpecialAirSEnd)
        {
            ftCo_800B9504(fp);
            return;
        }
    }

    if (ftCo_800B630C(fp)) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800A0C8C(fp);
        temp_r31->xA4 = 0;
    } else if (temp_r31->xA4 != 0) {
        ftCo_800B4880(fp, temp_r31->xA4);
        temp_r31->xA4 = 0;
    } else if (ftCo_800B9CBC(fp) != 0) {
        if (temp_r31->xA4 != 0) {
            ftCo_800B4880(fp, temp_r31->xA4);
            temp_r31->xA4 = 0;
            temp_r31->x90++;
        } else {
            fp->x1A88.x44 = NULL;
            fp->x1A88.x18 = fp->x1A88.x1C;
            ftCo_800A0C8C(fp);
        }
    } else {
        fp->x1A88.x44 = NULL;
        fp->x1A88.x18 = fp->x1A88.x1C;
        ftCo_800A0C8C(fp);
    }
}

void ftCo_800B920C(Fighter* fp)
{
    Fighter* temp_r3 = fp->x1A88.x44;
    PAD_STACK(0x10);

    if (temp_r3 == NULL) {
        fp->x1A88.x44 = NULL;
        fp->x1A88.x18 = fp->x1A88.x1C;
        ftCo_800A0C8C(fp);
    } else if (ABS(temp_r3->cur_pos.y - fp->cur_pos.y) < 25.0) {
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B463C(fp, CpuCmd_Done);
        fp->x1A88.x44 = NULL;
        fp->x1A88.x18 = fp->x1A88.x1C;
        ftCo_800A0C8C(fp);
    } else {
        ftCo_800B46B8(fp, CpuCmd_LstickTowardFighter, 0x7F);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800B92D4(Fighter* fp)
{
    PAD_STACK(4 * 4);
    if (fp->x1A88.x44 == NULL) {
        fp->x1A88.x44 = NULL;
        fp->x1A88.x18 = fp->x1A88.x1C;
        ftCo_800A0C8C(fp);
    } else {
        ftCo_800B46B8(fp, 0x94, 0x7F);
        ftCo_800B463C(fp, 0x7F);
    }
}

void ftCo_800B9340(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r30 = &fp->x1A88;
    Fighter* temp_r29 = fp->x1A88.x44;
    mp_UnkStruct0* temp_r3 = mpIsland_8005AC14(&fp->cur_pos, -100.0F);

    if (temp_r3 == NULL || temp_r29 == NULL ||
        temp_r3 != mpIsland_8005AC14(&temp_r29->cur_pos, -100.0F))
    {
        temp_r30->x44 = NULL;
        temp_r30->x18 = temp_r30->x1C;
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_PressB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (ABS(temp_r3->x14.x - fp->cur_pos.x) < 10.0) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, -0x7F);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else if (ABS(temp_r3->x8.x - fp->cur_pos.x) < 10.0) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x7F);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B46B8(fp, CpuCmd_LstickXTowardFighter, 0x7F);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800B9504(Fighter* fp)
{
    f32 var_f1;
    f32 var_f2;
    Fighter* temp_r3_2;
    HSD_GObj* gobj = fp->fv.zd.x222C;
    u8 _[8];
    Vec3 sp14;
    PAD_STACK(4);

    if (gobj != NULL) {
        HSD_JObjGetTranslation(GET_JOBJ(gobj), &sp14);
    } else {
        ftCo_800A0C8C(fp);
        return;
    }

    temp_r3_2 = ftCo_800A4E8C(fp, &sp14);
    if (temp_r3_2 == NULL) {
        fp->x1A88.x44 = NULL;
        fp->x1A88.x18 = fp->x1A88.x1C;
        ftCo_800A0C8C(fp);
    } else {
        var_f1 = ABS(temp_r3_2->cur_pos.x - fp->cur_pos.x);
        var_f2 = ABS(sp14.x - fp->cur_pos.x);
        if (var_f2 > var_f1) {
            ftCo_800B463C(fp, CpuCmd_ReleaseB);
            ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
            ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        } else {
            if (ABS(sp14.x - temp_r3_2->cur_pos.x) < 15.0 &&
                ABS(15.0 + temp_r3_2->cur_pos.y - sp14.y) < 15.0)
            {
                ftCo_800B463C(fp, CpuCmd_ReleaseB);
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            } else {
                if (15.0f + temp_r3_2->cur_pos.y > sp14.y) {
                    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x7F);
                } else {
                    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0x81);
                }
            }
        }
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800B9704(Fighter* fp)
{
    struct Fighter_x1A88_t* cpu = &fp->x1A88;
    float rand = HSD_Randf();
    cpu->x34 = (10 - cpu->level) * (rand * 15.0F + 15.0F) + 10.0F;
    if (cpu->xC == 7) {
        cpu->x34 /= 2;
    }
}

bool ftCo_800B9790(Fighter* fp, f32 arg1, f32 arg2)
{
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;
    Fighter* temp_r30 = fp->x1A88.x44;

    if (fp->ground_or_air == GA_Air) {
        if (arg1 < -0.6981316953897476 && arg1 > -0.8726646192371845 &&
            arg2 < 53.0 && ftCo_800A2C08(fp))
        {
            temp_r31->xA4 = 0x1B;
            return true;
        }
        return false;
    }
    if (arg1 < 0.08726646192371845 && arg1 > -0.08726646192371845 &&
        arg2 < 53.0 && ftCo_800A2C08(fp))
    {
        temp_r31->xA4 = 0x1B;
        return true;
    }
    if (fp->cur_pos.y >= temp_r30->cur_pos.y) {
        return false;
    }
    if (arg1 > 1.0471975430846214) {
        temp_r31->xA4 = 0x14;
    } else if (HSD_Randf() < 0.1) {
        temp_r31->xA4 = 0x1F;
    }
    return true;
}

bool ftCo_800B98C8(Fighter* fp, f32 arg1, f32 arg2)
{
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;
    Fighter* temp_r30 = fp->x1A88.x44;

    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    if (!ftCo_800A2C08(fp)) {
        return false;
    }
    if (arg2 > 80.0) {
        return false;
    }
    if (arg1 < 0.08726646192371845 && arg1 > -0.08726646192371845) {
        if (temp_r30->ground_or_air == GA_Air) {
            return false;
        }
        if (!ftCo_800A2170(fp, temp_r30)) {
            return false;
        }
        temp_r31->xA4 = 0x1B;
    } else {
        if (arg1 < 0.7853981573134661) {
            return false;
        }
        if (arg1 < 1.0471975430846214) {
            temp_r31->xA4 = 0x31;
        } else if (arg1 < 1.3089969288557768) {
            temp_r31->xA4 = 0x32;
        } else {
            temp_r31->xA4 = 0x33;
        }
    }
    return true;
}

bool ftCo_800B9A04(Fighter* fp, Item* arg1, f32 arg2, f32 arg3)
{
    f32 temp_f1;
    f32 temp_f1_2;
    bool var_r0;
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;

    PAD_STACK(4);

    if (ftCo_800A5908(arg1)) {
        return false;
    }
    if (ftCo_800A5A90(fp)) {
        return false;
    }
    temp_f1 = it_8026B960(fp->item_gobj);
    if (temp_f1 < 60.0 && temp_f1 > 0.0) {
        temp_r31->xA4 = 2;
        return true;
    }
    if (ftCo_800A59C0(arg1) != 0) {
        temp_f1_2 = it_8026B924(fp->item_gobj);
        if (temp_f1_2 < 0.00001F && temp_f1_2 > -0.00001F) {
            var_r0 = true;
        } else {
            var_r0 = false;
        }
        if (var_r0 != 0) {
            temp_r31->xA4 = 0x28;
            return true;
        }
        if (ftCo_800A2C08(fp) == 0) {
            return false;
        }
        if (arg2 < 0.08726646192371845 && arg2 > -0.08726646192371845 &&
            arg3 > 30.0)
        {
            if (arg1->kind == It_Kind_StarRod) {
                temp_r31->xA4 = 0xF;
            } else {
                temp_r31->xA4 = 2;
            }
            return true;
        }
        temp_r31->xA4 = 0x2A;
        return true;
    }
    if (ftCo_800A5A5C(arg1) != 0) {
        temp_r31->xA4 = 2;
        return true;
    }
    if (ftCo_800A5A28(arg1) != 0) {
        if (arg2 > 1.3089969288557768) {
            temp_r31->xA4 = 0xD;
            return true;
        }
        if (arg2 < -1.3089969288557768) {
            temp_r31->xA4 = 0xE;
            return true;
        }
        if (ftCo_800A2C08(fp) == 0) {
            return false;
        }
        if (arg2 < 0.26179938577115536 && arg2 > -0.26179938577115536) {
            temp_r31->xA4 = 0xF;
            return true;
        }
        if (arg1->kind == It_Kind_M_Ball) {
            temp_r31->xA4 = 0xE;
            return true;
        }
    } else {
        if (ftCo_800A59E4(arg1)) {
            return false;
        }
        if (arg3 > 30.0 && arg2 < 0.26179938577115536 &&
            arg2 > -0.26179938577115536)
        {
            temp_r31->xA4 = 0x2A;
            return true;
        } else {
            return false;
        }
    }
    return false;
}

bool ftCo_800B9CBC(Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r31;
    Fighter* temp_r29;
    f32 temp_f31;
    f32 temp_f30;

    struct Fighter_x1A88_t* temp_r3;
    bool var_r3;
    f32 var_f2;

    PAD_STACK(8);

    temp_r31 = &fp->x1A88;
    temp_r29 = temp_r31->x44;
    temp_r31->xA4 = 0;
    if (temp_r29 == NULL) {
        return false;
    }
    if (!temp_r31->xF9_b5) {
        return false;
    }
    if (temp_r31->x34 > 0) {
        temp_r31->x34--;
        return false;
    }

    ftCo_800B9704(fp);

    if (ftCo_800A1BA8(fp)) {
        return false;
    }
    temp_f30 = ftCo_800A1AB4(fp, temp_r29);
    var_f2 = ABS(temp_r29->cur_pos.x - fp->cur_pos.x);
    temp_f31 = lb_8000D008(temp_r29->cur_pos.y - fp->cur_pos.y, var_f2);
    if (fp->item_gobj != NULL) {
        return ftCo_800B9A04(fp, GET_ITEM(fp->item_gobj), temp_f31, temp_f30);
    }
    if (HSD_Randf() > 0.75) {
        return false;
    }
    if (temp_f30 < 30.0) {
        return false;
    }
    switch (fp->kind) {
    case FTKIND_NESS:
        var_r3 = ftCo_800B9790(fp, temp_f31, temp_f30);
        break;
    case FTKIND_YOSHI:
        var_r3 = ftCo_800B98C8(fp, temp_f31, temp_f30);
        break;
    case FTKIND_SAMUS:
        temp_r3 = &fp->x1A88;
        if (fp->ground_or_air == GA_Ground) {
            var_r3 = false;
        } else if (temp_f31 < -0.7853981573134661) {
            temp_r3->xA4 = 0x26;
            var_r3 = true;
        } else {
            var_r3 = false;
        }
        break;
    default:
        var_r3 = false;
        break;
    }
    if (var_r3) {
        return true;
    }
    if (!ftCo_800A2C08(fp)) {
        return false;
    }
    if (temp_f31 < 0.08726646192371845 && temp_f31 > -0.08726646192371845) {
        temp_r31->xA4 = ftCo_800B6208(Fighter_804D64FC->xC[fp->kind]);
        if (temp_r31->xA4 != 0) {
            return true;
        }
        return false;
    }
    return false;
}

bool ftCo_800B9F6C(Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_GuardOn || fp->motion_id == ftCo_MS_Guard) {
        return true;
    }
    return false;
}

void ftCo_800B9F90(Fighter* fp)
{
    struct Fighter_x1A88_t* cpu = &fp->x1A88;
    int temp_r31;

    if (fp->motion_id == ftCo_MS_Guard) {
        temp_r31 = 9 - cpu->level;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_PressR);
        if (temp_r31 != 0) {
            ftCo_800B46B8(fp, CpuCmd_WaitFor,
                          temp_r31 * ((int) (4 * HSD_Randf()) + 4));
        }
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_PressR);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

void ftCo_800BA080(Fighter* fp)
{
    if (fp->motion_id >= 0x16F && fp->motion_id <= 0x178) {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_Done);
    } else {
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, -0x7F);
        ftCo_800B463C(fp, CpuCmd_PressB);
        ftCo_800B463C(fp, CpuCmd_Done);
    }
}

static inline void ftCo_800BA080_dontinline(Fighter* fp)
{
    ftCo_800BA080(fp);
}

void ftCo_800BA160(Fighter* fp)
{
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B463C(fp, CpuCmd_ReleaseR);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0x7F);
    ftCo_800B463C(fp, CpuCmd_PressR);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 2);
    ftCo_800B463C(fp, CpuCmd_ReleaseR);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B463C(fp, CpuCmd_Done);
}

void ftCo_800BA224(Fighter* fp)
{
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
    ftCo_800B463C(fp, CpuCmd_ReleaseR);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, -0x7F);
    ftCo_800B463C(fp, CpuCmd_PressR);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 2);
    ftCo_800B463C(fp, CpuCmd_ReleaseR);
    ftCo_800B46B8(fp, CpuCmd_WaitFor, 5);
    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
    ftCo_800B463C(fp, CpuCmd_Done);
}

bool ftCo_800BA2E8(Fighter* fp, Fighter* arg1)
{
    PAD_STACK(0x10);

    if (fp->cur_pos.x - arg1->cur_pos.x > 0.0) {
        if (ftCo_800A2A70(fp, false) > Fighter_804D64FC->x20[fp->kind]) {
            ftCo_800BA160(fp);
            return true;
        }
        if (ftCo_800A2A70(fp, true) > Fighter_804D64FC->x20[fp->kind]) {
            ftCo_800BA224(fp);
            return true;
        }
        return false;
    } else {
        if (ftCo_800A2A70(fp, true) > Fighter_804D64FC->x20[fp->kind]) {
            ftCo_800BA224(fp);
            return true;
        }
        if (ftCo_800A2A70(fp, false) > Fighter_804D64FC->x20[fp->kind]) {
            ftCo_800BA160(fp);
            return true;
        }
        return false;
    }
}

void ftCo_800BA674(Fighter* fp, Fighter* arg1)
{
    PAD_STACK(0x10);

    if (fp->cur_pos.x - arg1->cur_pos.x > 0.0) {
        if (ftCo_800A2A70(fp, false) > 2.0 * Fighter_804D64FC->x20[fp->kind]) {
            ftCo_800BA160(fp);
        } else {
            ftCo_800BA224(fp);
        }
    } else {
        if (ftCo_800A2A70(fp, true) > 2.0 * Fighter_804D64FC->x20[fp->kind]) {
            ftCo_800BA224(fp);
        } else {
            ftCo_800BA160(fp);
        }
    }
}

static inline void inline0(Fighter* fp, Item* temp_r30_3)
{
    if (ftCo_800A2998(fp, 1.0f) != 0) {
        ftCo_800B9F90(fp);
    } else if (fp->cur_pos.x - temp_r30_3->pos.x > 0.0) {
        ftCo_800BA160(fp);
    } else {
        ftCo_800BA224(fp);
    }
}

static inline void inline1(Fighter* fp, Item* temp_r30_3)
{
    if (fp->cur_pos.x - temp_r30_3->pos.x > 0.0) {
        ftCo_800BA224(fp);
    } else {
        ftCo_800BA160(fp);
    }
}

static inline void inline2(Fighter* fp, Fighter* temp_r4_2)
{
    float var_f1;
    float temp_f2 = fp->cur_pos.x - temp_r4_2->cur_pos.x;
    if (temp_f2 < 0.0f) {
        var_f1 = -temp_f2;
    } else {
        var_f1 = temp_f2;
    }
    if (var_f1 > 30.0) {
        if (temp_f2 > 0.0) {
            ftCo_800BA160(fp);
        } else {
            ftCo_800BA224(fp);
        }
    } else {
        if (temp_f2 > 0.0) {
            ftCo_800BA224(fp);
        } else {
            ftCo_800BA160(fp);
        }
    }
}

static inline bool escape(ftCommon_MotionState id)
{
    if (id == ftCo_MS_EscapeF || id == ftCo_MS_EscapeB ||
        id == ftCo_MS_EscapeAir)
    {
        return true;
    }
    return false;
}

static inline bool escapen(ftCommon_MotionState id)
{
    if (id == ftCo_MS_EscapeN) {
        return true;
    }
    return false;
}

void ftCo_800BA9A0(Fighter* fp)
{
    Item* temp_r30_3;
    f32 temp_f2;
    f32 var_f1;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r30_4;
    s32 temp_r30_5;
    s32 temp_r3;
    struct Fighter_x1A88_t* temp_r5;
    u32 temp_r4;

    temp_r5 = &fp->x1A88;
    temp_r3 = fp->motion_id;
    if (escape(temp_r3) || escapen(temp_r3)) {
        ftCo_800A0C8C(fp);
        return;
    }
    if (temp_r3 == 0xB2) {
        ftCo_800B9F90(fp);
        return;
    }
    temp_r4 = temp_r5->xF8_b12;
    if (temp_r4 == 0) {
        temp_r5->x18 = temp_r5->x1C;
        ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
        ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
        ftCo_800B463C(fp, CpuCmd_ReleaseR);
        ftCo_800B463C(fp, CpuCmd_ReleaseB);
        ftCo_800A0C8C(fp);
        return;
    }
    if (fp->ground_or_air == GA_Air) {
        if (fp->kind == FTKIND_FOX || fp->kind == FTKIND_FALCO) {
            if (temp_r4 == 2) {
                temp_r30_2 = 9 - fp->x1A88.level;
                ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, -0x50);
                ftCo_800B463C(fp, CpuCmd_PressB);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                if (temp_r30_2 != 0) {
                    ftCo_800B46B8(fp, CpuCmd_WaitFor,
                                  temp_r30_2 *
                                      ((int) (4.0f * HSD_Randf()) + 4));
                }
                ftCo_800B463C(fp, CpuCmd_Done);
            } else {
                ftCo_800B463C(fp, CpuCmd_ReleaseR);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_PressR);
                ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                ftCo_800B463C(fp, CpuCmd_ReleaseR);
                ftCo_800B463C(fp, CpuCmd_Done);
            }
        } else if (temp_r4 == 3) {
            ftCo_800BA080_dontinline(fp);
        } else {
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_PressR);
            ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
            ftCo_800B463C(fp, CpuCmd_ReleaseR);
            ftCo_800B463C(fp, CpuCmd_Done);
        }
    } else if (temp_r4 == 2) {
        temp_r30_3 = temp_r5->xF4;
        if (temp_r30_3->kind == It_Kind_Flipper ||
            temp_r30_3->kind == It_Kind_TaruCann)
        {
            inline0(fp, temp_r30_3);
        } else if (temp_r30_3->kind == It_Kind_DKinoko) {
            inline1(fp, temp_r30_3);
        } else {
            if (fp->kind == FTKIND_FOX || fp->kind == FTKIND_FALCO) {
                if (HSD_Randf() > 0.5) {
                    temp_r30_4 = 9 - fp->x1A88.level;
                    ftCo_800B46B8(fp, CpuCmd_SetLstickX, 0);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickY, -0x50);
                    ftCo_800B463C(fp, CpuCmd_PressB);
                    ftCo_800B46B8(fp, CpuCmd_WaitFor, 1);
                    ftCo_800B46B8(fp, CpuCmd_SetLstickY, 0);
                    if (temp_r30_4 != 0) {
                        ftCo_800B46B8(fp, CpuCmd_WaitFor,
                                      temp_r30_4 *
                                          ((int) (4.0f * HSD_Randf()) + 4));
                    }
                    ftCo_800B463C(fp, CpuCmd_Done);
                } else {
                    ftCo_800B9F90(fp);
                }
            } else {
                ftCo_800B9F90(fp);
            }
        }
    } else {
        if (temp_r4 == 3) {
            ftCo_800BA080_dontinline(fp);
        } else if (temp_r5->xF0 == NULL) {
            ftCo_800B9F90(fp);
        } else {
            inline2(fp, temp_r5->xF0);
        }
    }
}

bool ftCo_800BB104(Fighter* fp, Fighter* arg1, Point3d* arg2, f32 arg3)
{
    Point3d sp40;
    Point3d sp34;
    Vec3 sp28;

    int i;
    HitCapsule* temp_r29;

    HitCapsuleState temp_r0;

    PAD_STACK(0xC);

    for (i = 0; i < 4; i++) {
        temp_r0 = arg1->x914[i].state;
        temp_r29 = &arg1->x914[i];
        if (temp_r0 != HitCapsule_Disabled && temp_r0 != HitCapsule_Enabled &&
            !temp_r29->x43_b2 && temp_r29->element != 8 &&
            !lbColl_8000ACFC(fp, temp_r29))
        {
            float dx = temp_r29->x4C.x - temp_r29->x58.x;
            float dy = temp_r29->x4C.y - temp_r29->x58.y;
            float dz = temp_r29->x4C.z - temp_r29->x58.z;
            sp28.x = 3.0f * dx + temp_r29->x4C.x;
            sp28.y = 3.0f * dy + temp_r29->x4C.y;
            sp28.z = 3.0f * dz + temp_r29->x4C.z;
            if (lbColl_80006094(&temp_r29->x4C, &sp28, arg2, arg2, &sp40,
                                &sp34, temp_r29->scale, arg3) != 0)
            {
                return true;
            }
        }
    }
    return false;
}

/// #ftCo_800BB220

bool ftCo_800BB768(Fighter* fp, Fighter* arg1)
{
    Vec3 sp24;
    Vec3 sp18;
    int sp14;
    u32 sp10;
    f32 temp_f1;
    f32 temp_f2;
    f32 temp_f3;
    f32 temp_f4;
    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;

    switch (arg1->kind) {
    case FTKIND_GKOOPS:
    case FTKIND_KOOPA:
        if (arg1->motion_id == ftKp_MS_SpecialLw ||
            arg1->motion_id == ftKp_MS_SpecialAirLw)
        {
            if (ftCo_800A0FB0(&sp24, &sp14, &sp10, &sp18, -1, -1, -1,
                              arg1->cur_pos.x, arg1->cur_pos.y, fp->cur_pos.x,
                              5.0 + fp->cur_pos.y, 0.0F))
            {
                return false;
            }
            temp_f2 = arg1->cur_pos.x;
            temp_f1 = arg1->x1A88.x564;
            temp_f3 = temp_r31->x564;
            temp_f4 = fp->cur_pos.x;
            if (temp_f2 + temp_f1 + temp_f3 > temp_f4 &&
                temp_f2 - temp_f1 - temp_f3 < temp_f4)
            {
                return true;
            }
        } else if (arg1->motion_id == ftCo_MS_AttackHi4) {
            temp_f2 = arg1->cur_pos.x;
            temp_f1 = arg1->x1A88.x564;
            temp_f3 = temp_r31->x564;
            temp_f4 = fp->cur_pos.x;
            if (temp_f2 + temp_f1 + temp_f3 > temp_f4 &&
                temp_f2 - temp_f1 - temp_f3 < temp_f4)
            {
                if (arg1->cur_pos.y < fp->cur_pos.y &&
                    fp->cur_pos.y - arg1->cur_pos.y < 35.0F)
                {
                    return true;
                }
            }
        }
        break;
    case FTKIND_YOSHI:
        if (arg1->motion_id == ftYs_MS_SpecialLw ||
            arg1->motion_id == ftYs_MS_SpecialAirLw)
        {
            if (ftCo_800A0FB0(&sp24, &sp14, &sp10, &sp18, -1, -1, -1,
                              arg1->cur_pos.x, arg1->cur_pos.y, fp->cur_pos.x,
                              5.0 + fp->cur_pos.y, 0.0F))
            {
                return false;
            }
            temp_f2 = arg1->cur_pos.x;
            temp_f1 = arg1->x1A88.x564;
            temp_f3 = temp_r31->x564;
            temp_f4 = fp->cur_pos.x;
            if (temp_f2 + temp_f1 + temp_f3 > temp_f4 &&
                temp_f2 - temp_f1 - temp_f3 < temp_f4)
            {
                return true;
            }
        }
        break;
    case FTKIND_SAMUS:
        if (arg1->motion_id == ftSs_MS_SpecialHi &&
            arg1->cur_pos.y < fp->cur_pos.y && ftCo_800A1AB4(fp, arg1) < 30.0)
        {
            return true;
        }
        break;
    }
    return false;
}

int ftCo_800BB9B4(Fighter* fp)
{
    Vec3 sp24;

    struct Fighter_x1A88_t* temp_r31 = &fp->x1A88;
    Fighter_GObj* var_r29;
    Item_GObj* var_r29_2;
    Item* temp_r28;
    Fighter* temp_r28_2;
    f32 temp_f31;

    PAD_STACK(0x10);

    temp_r31->xF8_b12 = false;
    temp_r31->xF0 = NULL;
    temp_r31->xF4 = NULL;

    if (ftCo_800A1C44(fp)) {
        return temp_r31->xF8_b12;
    }
    if (fp->kind == FTKIND_GKOOPS) {
        return temp_r31->xF8_b12;
    }

    temp_f31 = 0.5F * temp_r31->x568;
    sp24.x = fp->cur_pos.x;
    sp24.y = fp->cur_pos.y + temp_f31;
    sp24.z = fp->cur_pos.z;

    for (var_r29 = HSD_GObj_Entities->fighters; var_r29 != NULL;
         var_r29 = var_r29->next)
    {
        if (fp->gobj == var_r29) {
            continue;
        }

        temp_r28_2 = GET_FIGHTER(var_r29);
        if (ftCo_IsAlly(fp, temp_r28_2)) {
            continue;
        }

        temp_r31->xF8_b12 = ftCo_800BB104(fp, temp_r28_2, &sp24, temp_f31);
        if (temp_r31->xF8_b12 != 0) {
            temp_r31->xF0 = temp_r28_2;
            return temp_r31->xF8_b12;
        }

        temp_r31->xF8_b12 = ftCo_800BB768(fp, temp_r28_2);
        if (temp_r31->xF8_b12) {
            temp_r31->xF0 = temp_r28_2;
            return temp_r31->xF8_b12;
        }
    }

    var_r29_2 = HSD_GObj_Entities->items;
    while (var_r29_2 != NULL) {
        temp_r28 = GET_ITEM(var_r29_2);
        if (it_8026C1B4(var_r29_2)) {
            temp_r31->xF8_b12 = ftCo_800BB220(fp, temp_r28, &sp24, temp_f31);
            if (temp_r31->xF8_b12 != 0) {
                temp_r31->xF4 = temp_r28;
                return temp_r31->xF8_b12;
            }
        }
        var_r29_2 = var_r29_2->next;
    }

    return temp_r31->xF8_b12;
}
