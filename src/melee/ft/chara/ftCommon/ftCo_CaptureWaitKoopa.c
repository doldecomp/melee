#include "ftCo_CaptureWaitKoopa.h"

#include "ftCo_CaptureKoopa.h"

#include <platform.h>

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftcommon.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_Throw.h"

void ftCo_800BCC20(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitKoopa, Ft_MF_None, 0, 1,
                              0, NULL);
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftCo_CaptureWaitKoopa_Anim(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_800BC458(gobj);
    if (fp->grab_timer <= 0) {
        ftCo_800DA698(fp->victim_gobj, 0);
        fp->facing_dir = -fp->facing_dir;
        ftCo_CaptureCut_Enter(gobj);
    } else {
        ftCo_800BC4A8(gobj);
    }
}

void ftCo_CaptureWaitKoopa_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureWaitKoopa_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureWaitKoopa_Coll(Fighter_GObj* gobj) {}

void ftCo_800BCD00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitKoopaAir, Ft_MF_None, 0,
                              1, 0, NULL);
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftCo_CaptureWaitKoopaAir_Anim(Fighter_GObj* gobj)
{
    ftCo_CaptureWaitKoopa_Anim(gobj);
}

void ftCo_CaptureWaitKoopaAir_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureWaitKoopaAir_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureWaitKoopaAir_Coll(Fighter_GObj* gobj) {}
