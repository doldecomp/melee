#include <platform.h>

#include "ft/forward.h"
#include <baselib/forward.h>

#include "ftCo_CaptureDamageKoopa.h"

#include "ftCo_CaptureKoopa.h"
#include "ftCo_CaptureWaitKoopa.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"

void ftCo_800BC9C8(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageKoopa,
                              fp->x2222_b6 ? Ft_MF_FreezeState : Ft_MF_None, 0,
                              1, 0, fp->victim_gobj);
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
}

static inline void inlineA0(ftCo_GObj* gobj, HSD_GObjEvent cb)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        cb(gobj);
        return;
    }
    /// @todo #ftCo_CaptureWaitKoopa_Anim
    ftCo_800BC458(gobj);
    if (fp->x1A4C <= 0) {
        ftCo_800DA698(fp->victim_gobj, false);
        fp->facing_dir = -fp->facing_dir;
        ftCo_800DC750(gobj);
    } else {
        ftCo_800BC4A8(gobj);
    }
}

void ftCo_CaptureDamageKoopa_Anim(ftCo_GObj* gobj)
{
    inlineA0(gobj, ftCo_800BCC20);
}

void ftCo_CaptureDamageKoopa_IASA(ftCo_GObj* gobj) {}

void ftCo_CaptureDamageKoopa_Phys(ftCo_GObj* gobj) {}

void ftCo_CaptureDamageKoopa_Coll(ftCo_GObj* gobj) {}

/// @todo Shared code with #ftCo_800BC9C8. Simple @c inline doesn't work.
void ftCo_800BCAF4(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureDamageKoopaAir,
                              fp->x2222_b6 ? Ft_MF_FreezeState : Ft_MF_None, 0,
                              1, 0, fp->victim_gobj);
    fp->accessory1_cb = ftCo_800DB464;
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
}

void ftCo_CaptureDamageKoopaAir_Anim(ftCo_GObj* gobj)
{
    inlineA0(gobj, ftCo_800BCD00);
}

void ftCo_CaptureDamageKoopaAir_IASA(ftCo_GObj* gobj) {}

void ftCo_CaptureDamageKoopaAir_Phys(ftCo_GObj* gobj) {}

void ftCo_CaptureDamageKoopaAir_Coll(ftCo_GObj* gobj) {}
