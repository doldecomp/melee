#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_ThrownKoopa.h"

#include "inlines.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/types.h"

void ftCo_800BCDE0(ftCo_GObj* gobj, FtMotionId msid)
{
    u8 _[8] = { 0 };
    ftCo_Thrown_Enter(gobj, msid, Ft_MF_None, 0);
    ftAnim_8006EBA4(gobj);
}

void ftCo_800BCE64(ftCo_GObj* gobj, FtMotionId msid)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    const MotionFlags mf = Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim |
                           Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
                           Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags |
                           Ft_MF_Unk27;
/// @todo Use #ftCo_Thrown_Enter.
#define SOLUTION 1
#if SOLUTION == 0
    ftCo_Thrown_Enter(gobj, msid, mf, fp->cur_anim_frame);
#elif SOLUTION == 1
    u8 _[8] = { 0 };
    fp->facing_dir = GET_FIGHTER(fp->victim_gobj)->facing_dir;
    fp->mv.co.capturekoopa.x0 = false;
    Fighter_ChangeMotionState(gobj, msid, mf, fp->cur_anim_frame, 1, 0,
                              fp->victim_gobj);
    fp->accessory1_cb = ftCo_800DE508;
    ftCommon_8007E2F4(fp, 0x1FF);
#endif
#undef SOLUTION
}

void ftCo_ThrownKoopaF_Anim(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaF_IASA(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaF_Phys(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaF_Coll(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaB_Anim(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaB_IASA(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaB_Phys(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaB_Coll(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaAirF_Anim(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaAirF_IASA(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaAirF_Phys(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaAirF_Coll(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaAirB_Anim(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaAirB_IASA(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaAirB_Phys(ftCo_GObj* gobj) {}

void ftCo_ThrownKoopaAirB_Coll(ftCo_GObj* gobj) {}
