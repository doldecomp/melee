#include "ftMs_SpecialHi.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "ftCommon/ftCo_Landing.h"
#include "ftMars/types.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

// 80138208 00134DE8
// https://decomp.me/scratch/lrV6F
void ftMs_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    // MotionStateChange
    Fighter_ChangeMotionState(gobj, 0x16F, 0, 0.0f, 1.0f, 0.0f, NULL);
    // MS_AnimationFrameUpdate&More
    ftAnim_8006EBA4(gobj);
}

// 8013826C 00134E4C
// https://decomp.me/scratch/PuVdx
void ftMs_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;

    u8 _[8];

    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    fp->self_vel.y = 0.0f;
    fp->self_vel.x *= da->x3C;
    // MotionStateChange
    Fighter_ChangeMotionState(gobj, 0x170, 0, 0.0f, 1.0f, 0.0f, NULL);
    // MS_AnimationFrameUpdate&More
    ftAnim_8006EBA4(gobj);
}

// 801382E8 00134EC8
// https://decomp.me/scratch/56Ycw
void ftMs_SpecialHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;

    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        // MS_035_FallSpecial
        ftCo_80096900(gobj, 0, 1, 0, da->x28, da->x2C);
    }
}

// 80138348 00134F28
// https://decomp.me/scratch/WdpFi
void ftMs_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;

    u8 _[8];

    // FrameTimerCheck
    if (!ftAnim_IsFramesRemaining(gobj)) {
        // MS_035_FallSpecial
        ftCo_80096900(gobj, 0, 1, 0, da->x28, da->x2C);
    }
}

#define DEGREES_TO_RADIANS (3.14159265359f / 180.0f)
#define HALF_PI 1.5707963267948966
#define abs(x) (x < 0.0f ? -x : x)

void ftMs_SpecialHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;
    float abs_lstick_x = abs(fp->input.lstick.x);
    if (fp->cmd_vars[0] == 0 && abs_lstick_x > da->x34) {
        float temp_f1 =
            da->x38 * ((abs_lstick_x - da->x34) / (1.0 /*d*/ - da->x34));
        temp_f1 = (fp->input.lstick.x > 0.0f) ? -(DEGREES_TO_RADIANS * temp_f1)
                                              : (DEGREES_TO_RADIANS * temp_f1);
        if (abs(temp_f1) > abs(fp->lstick_angle)) {
            fp->lstick_angle = temp_f1;
        }
    }
    if (ftCheckThrowB3(fp)) {
        if (abs(fp->input.lstick.x) > da->x30) {
            ftCommon_UpdateFacing(fp);
            ftPartSetRotY(fp, 0, (float) (HALF_PI * fp->facing_dir));
        }
    }
}

// 801384F0 001350D0
// https://decomp.me/scratch/2yXhH
void ftMs_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;
    float abs_lstick_x = abs(fp->input.lstick.x);
    u8 _[16];
    if (fp->cmd_vars[0] == 0 && abs_lstick_x > da->x34) {
        float temp_f1 =
            da->x38 * ((abs_lstick_x - da->x34) / (1.0 /*d*/ - da->x34));
        temp_f1 = (fp->input.lstick.x > 0.0f) ? -(DEGREES_TO_RADIANS * temp_f1)
                                              : (DEGREES_TO_RADIANS * temp_f1);
        if (abs(temp_f1) > abs(fp->lstick_angle)) {
            fp->lstick_angle = temp_f1;
        }
    }
    if (ftCheckThrowB3(fp)) {
        if (abs(fp->input.lstick.x) > da->x30) {
            ftCommon_UpdateFacing(fp);
            ftPartSetRotY(fp, 0, (float) (HALF_PI * fp->facing_dir));
        }
    }
}

// 80138638 00135218
// https://decomp.me/scratch/Wx1iY
void ftMs_SpecialHi_Phys(HSD_GObj* gobj)
{
    struct ftCo_DatAttrs* attr2;
    MarsAttributes* da;
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[32];

    s32 num;

    // this is required, dunno why
    fp->ground_or_air;

    if (fp->ground_or_air == GA_Air) {
        if (fp->cmd_vars[2] == 0) {
            ft_80085154(gobj);
            if (fp->self_vel.x < 0.0f) {
                num = -1;
            } else {
                num = 1;
            }
            if (fp->facing_dir != num) {
                fp->self_vel.x *= -1.0f;
            }
            if (fp->x6A4_transNOffset.y < 0.0f) {
                fp->cmd_vars[2] = 1;
            }
        } else {
            da = fp->dat_attrs;
            attr2 = &fp->co_attrs;
            ftCommon_Fall(fp, da->x44, da->x48);
            ftCommon_8007D344(fp, 0.0f, attr2->air_drift_stick_mul * da->x28,
                              attr2->air_drift_max * da->x28);
        }
    } else {
        ft_80084FA8(gobj);
    }
}

// 8013873C 0013531C
// https://decomp.me/scratch/9gz2V
void ftMs_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    MarsAttributes* da = fp->dat_attrs;
    struct ftCo_DatAttrs* attr2 = &fp->co_attrs;
    s32 num;

    u8 _[40];

    if (fp->cmd_vars[0] != 0) {
        if (fp->cmd_vars[2] == 0) {
            ft_80085154(gobj);
            fp->self_vel.x *= da->x40;
            fp->self_vel.y *= da->x40;
            fp->self_vel.z *= da->x40;
            if (fp->self_vel.x < 0.0f) {
                num = -1;
            } else {
                num = 1;
            }
            if (fp->facing_dir != num) {
                fp->self_vel.x *= -1.0f;
            }
            if (fp->x6A4_transNOffset.y < 0.0f) {
                fp->cmd_vars[2] = 1;
            }
        } else {
            ftCommon_Fall(fp, da->x44, da->x48);
            ftCommon_8007D344(fp, 0.0f, attr2->air_drift_stick_mul * da->x28,
                              attr2->air_drift_max * da->x28);
        }
    } else {
        ftCommon_Fall(fp, attr2->grav, attr2->terminal_vel);
        ftCommon_8007CF58(fp);
    }
}

// 80138884 00135464
// https://decomp.me/scratch/NTb4a
void ftMs_SpecialHi_80138884(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    MarsAttributes* da = fp->dat_attrs;
    ftCo_LandingFallSpecial_Enter(gobj, false, da->x2C);
}

// 801388B4 00135494
// https://decomp.me/scratch/3MMkJ
void ftMs_SpecialHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (fp->cmd_vars[0] == 0 || fp->self_vel.y >= 0.0f) {
            ft_80083B68(gobj);
        } else if (fp->cmd_vars[1] == 0) {
            fp->cmd_vars[1] = 1;
            ft_80083B68(gobj);
        } else {
            ft_800831CC(gobj, &ftCo_80096CC8, &ftMs_SpecialHi_80138884);
        }
    } else {
        ft_80084104(gobj);
    }
}

// 80138940 00135520
// https://decomp.me/scratch/QEKrM
void ftMs_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        if (fp->cmd_vars[0] == 0 || fp->self_vel.y >= 0.0f) {
            ft_80083B68(gobj);
        } else if (fp->cmd_vars[1] == 0) {
            fp->cmd_vars[1] = 1;
            ft_80083B68(gobj);
        } else {
            ft_800831CC(gobj, &ftCo_80096CC8, &ftMs_SpecialHi_80138884);
        }
    } else {
        ft_80084104(gobj);
    }
}
