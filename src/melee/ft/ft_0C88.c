#include <placeholder.h>

#include "ft/fighter.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include <baselib/gobj.h>

/// #ftCo_800C884C

/// #ftCo_800C88A0

/// #ftCo_800C88D4

/// #ftCo_800C89A0

/// #ftCo_800C8A64

/// #ftCo_800C8AF0

void fn_800C8B1C(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->smash_attrs.x2134_vibrateFrame = 0;
}

/// #ftCo_800C8B2C

void ftCo_800C8B60(Fighter* fp, s32 arg1, s8 arg2)
{
    fp->x2226_b5 = arg1;
    fp->smash_attrs.x2134_vibrateFrame = arg2;
}

/// #ftCo_800C8B74

/// #ftCo_DownSpot_Anim

void ftCo_DownSpot_IASA(Fighter_GObj* gobj) {}

/// #ftCo_DownSpot_Phys

/// #ftCo_DownSpot_Coll

/// #ftCo_800C8C84

/// #ftCo_800C8D00

/// #fn_800C8E40

/// #fn_800C8E74

/// #ftCo_800C8F6C

/// #ftCo_800C8FC4

/// #ftCo_800C9034

/// #fn_800C9058

/// #ftCo_800C9078

/// #fn_800C9198

/// #ftCo_Barrel_Anim

/// #ftCo_Barrel_IASA

void ftCo_Barrel_Phys(Fighter_GObj* gobj) {}

void ftCo_Barrel_Coll(Fighter_GObj* gobj) {}

/// #fn_800C9264

/// #fn_800C9290

/// #ftCo_800C92E4

/// #ftCo_Walk_CheckInput

/// #ftCo_800C94B4

/// #fn_800C9528

/// #ftCo_Walk_Anim

/// #ftCo_Walk_IASA

/// #ftCo_Walk_Phys

/// #ftCo_Walk_Coll

/// #ftCo_800C97A8

/// #ftCo_Turn_CheckInput

/// #ftCo_800C9840

/// #fn_800C98AC

/// #ftCo_800C9924

/// #ftCo_Turn_Anim

/// #ftCo_Turn_IASA

/// #ftCo_Turn_Phys

/// #ftCo_Turn_Coll

/// #fn_800C9C2C

/// #fn_800C9C74

/// #fn_800C9CEC

/// #fn_800C9D40

/// #fn_800C9D94

static inline void getAccelAndTarget(Fighter* fp, float* accel,
                                     float* target_vel)
{
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    *accel = fp->input.lstick.x * fp->co_attrs.dash_run_acceleration_a;
    *accel += fp->input.lstick.x > 0 ? +co_attrs->dash_run_acceleration_b
                                     : -co_attrs->dash_run_acceleration_b;
    *target_vel = fp->input.lstick.x * co_attrs->dash_run_terminal_velocity;
}

/// #ftCo_TurnRun_Anim

/// #ftCo_TurnRun_IASA

void ftCo_TurnRun_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co_attrs = &fp->co_attrs;
    float accel, target_vel;
    getAccelAndTarget(fp, &accel, &target_vel);

    if (!target_vel) {
        ftCommon_8007C930(fp, co_attrs->gr_friction *
                                  p_ftCommonData->x60_someFrictionMul);
    } else if (fp->mv.co.turnrun.accel_mul * accel < 0) {
        if (accel > 0) {
            if (fp->gr_vel + accel > target_vel) {
                accel -= co_attrs->gr_friction *
                         p_ftCommonData->x60_someFrictionMul;
                if (fp->gr_vel + accel < target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
            }
        } else {
            if (fp->gr_vel + accel < target_vel) {
                accel += co_attrs->gr_friction *
                         p_ftCommonData->x60_someFrictionMul;
                if (fp->gr_vel + accel > target_vel) {
                    accel = target_vel - fp->gr_vel;
                }
            }
        }
        fp->xE4_ground_accel_1 = accel;
    } else {
        ftCommon_8007C930(fp, co_attrs->gr_friction *
                                  p_ftCommonData->x60_someFrictionMul);
    }
    ftCommon_8007CB74(gobj);
}

/// #ftCo_TurnRun_Coll

/// #ftCo_Dash_CheckInput

/// #fn_800CA120

/// #ftCo_Dash_Anim

/// #ftCo_Dash_IASA

void ftCo_Dash_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(1);

    if (fp->mv.co.dash.x0) {
        fp->mv.co.dash.x0 = 0;
    } else {
        ftCo_DatAttrs* attrs = &fp->co_attrs;
        float accel, target_vel;
        getAccelAndTarget(fp, &accel, &target_vel);
        ftCommon_8007C98C(fp, accel, target_vel,
                          attrs->gr_friction *
                              p_ftCommonData->x60_someFrictionMul);
    }
    ftCommon_8007CB74(gobj);
}

/// #ftCo_Dash_Coll

/// #fn_800CA5F0

/// #fn_800CA644

/// #fn_800CA698

/// #fn_800CA6F4

/// #fn_800CA71C

/// #ftCo_Run_Anim

/// #ftCo_Run_IASA

void ftCo_Run_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* attrs = &fp->co_attrs;
    float accel, target_vel;
    getAccelAndTarget(fp, &accel, &target_vel);
    if (target_vel) {
        f32 gr_frac = fp->gr_vel / target_vel;
        if ((gr_frac > 0.0F) && (gr_frac < 1.0F)) {
            accel *= (1.0F - gr_frac) * p_ftCommonData->x5C;
        }
    }
    fp->mv.co.run.x4 = target_vel * p_ftCommonData->x440;
    ftCommon_8007C98C(fp, accel, target_vel,
                      attrs->gr_friction *
                          p_ftCommonData->x60_someFrictionMul);
    ftCommon_8007CB74(gobj);
}

/// #ftCo_Run_Coll

/// #ftCo_RunDirect_Anim

/// #ftCo_RunDirect_IASA

#pragma push
#pragma dont_inline on
void ftCo_RunDirect_Phys(Fighter_GObj* gobj)
{
    ftCo_Run_Phys(gobj);
}
#pragma pop

/// #ftCo_RunDirect_Coll

/// #fn_800CABC4

/// #fn_800CAC18

/// #ftCo_RunBrake_Anim

/// #ftCo_RunBrake_IASA

void ftCo_RunBrake_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007C930(fp, p_ftCommonData->x60_someFrictionMul *
                              fp->co_attrs.gr_friction);
    ftCommon_8007CB74(gobj);
}

/// #ftCo_RunBrake_Coll

/// #ftCo_800CAE80

/// #ftCo_Jump_CheckInput

/// #fn_800CAF78

/// #ftCo_800CB024

/// #ftCo_800CB110

/// #fn_800CB250

/// #ftCo_Jump_Anim

/// #ftCo_Jump_IASA

/// #ftCo_800CB438

/// #ftCo_Jump_Phys

/// #ftCo_Jump_Coll

/// #fn_800CB4E0

/// #ftCo_KneeBend_Anim

/// #ftCo_800CB59C

/// #ftCo_KneeBend_IASA

/// #ftCo_KneeBend_Phys

/// #ftCo_KneeBend_Coll

/// #ft_800CB6EC

/// #ft_800CB804

/// #ftCo_800CB870

/// #ftCo_800CB8E0

/// #ftCo_800CB950

/// #ftCo_800CBAC4

/// #ftCo_800CBBC0

/// #ftCo_800CBD18

/// #ftCo_800CBE98

/// #ftCo_800CC0E8

/// #ftCo_800CC238

/// #ftCo_JumpAerial_Anim

/// #fn_800CC3C4

/// #ftCo_JumpAerial_IASA

/// #ftCo_JumpAerial_Phys

/// #fn_800CC654

/// #ftCo_800CC6C8

/// #ftCo_JumpAerial_Coll

/// #ftCo_800CC730

/// #ftCo_800CC830

/// #ftCo_800CC8DC

/// #ftCo_800CC988

/// #ftCo_Fall_Anim

/// #ftCo_800CCAAC

/// #ftCo_800CCBE0

/// #ftCo_Fall_IASA

/// #ftCo_Fall_Phys

/// #ftCo_Fall_Coll

/// #ftCo_800CCDA8

/// #ftCo_FallAerial_Anim

/// #ftCo_FallAerial_IASA

/// #ftCo_FallAerial_Phys
