#include "ftCo_BarrelWait.h"

#include "ftCo_CaptureCut.h"
#include "ftCo_Damage.h"
#include "ftCo_Lift.h"
#include "ftCo_Throw.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdynamics.h"
#include "ft/types.h"
#include "ftCommon/inlines.h"
#include "gr/ground.h"

#include "lb/forward.h"

#include "lb/lbcollision.h"
#include "mp/mpcoll.h"

#include <common_structs.h>

/* 09EC44 */ static void ftCo_8009EC44(Fighter_GObj* gobj);

static inline void setCamData(ftCommonData* cd, CameraBox* cam)
{
    cam->x40 = cd->x4DC;
    cam->x48 = cd->x4E4;
}

void ftCo_8009EB18(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4);

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_BarrelWait, Ft_MF_None, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->death2_cb = ftCo_8009EAF8;
    fp->accessory1_cb = ftCo_8009EC44;
    ftCommon_8007E2FC(gobj);
    fp->x1988 = 2;
    fp->invisible = true;
    ftCommon_8007E2F4(fp, 0x1FF);
    setCamData(p_ftCommonData, fp->x890_cameraBox);
    ftCommon_8007EFC0(fp, 1);
}

void ftCo_BarrelWait_Anim(Fighter_GObj* gobj) {}

void ftCo_BarrelWait_IASA(Fighter_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->input.x668 & HSD_PAD_AB) {
        Ground_801C4DD0();
    }
}

void ftCo_BarrelWait_Phys(Fighter_GObj* gobj) {}

void ftCo_BarrelWait_Coll(Fighter_GObj* gobj) {}

void ftCo_8009EC44(Fighter_GObj* gobj)
{
    float param;
    PAD_STACK(4);
    Ground_801C4DA0(&GET_FIGHTER(gobj)->cur_pos, &param);
}

void ftCo_8009EC70(Fighter_GObj* gobj, Vec3* pos, UNK_T arg2, float kb_angle)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->bury_timer_2 = p_ftCommonData->bury_timer_unk2;
    fp->cur_pos = *pos;
    mpColl_80043680(&fp->coll_data, pos);
    ftCamera_80076064(fp);
    {
        struct SmallerHitCapsule hit;
        lbColl_80008D30((HitCapsule*) &hit, arg2);
        ftColl_800788D4(gobj);
        ftCo_Barrel_ApplyKnockback(fp, kb_angle, (HitCapsule*) &hit);
        Fighter_UnkTakeDamage_8006CC30(fp, hit.damage);
    }
    ftCo_8008DCE0(gobj, 91, 0);
}
