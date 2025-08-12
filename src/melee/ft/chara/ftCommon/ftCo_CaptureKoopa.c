#include <platform.h>

#include "ftCo_CaptureKoopa.h"

#include "ftCo_CaptureDamageKoopa.h"
#include "ftCo_Lift.h"
#include "math.h"

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"
#include "ftCommon/types.h"
#include "ftKoopa/ftKp_Init.h"

#include <dolphin/mtx.h>
#include <baselib/jobj.h>

void ftCo_800BC438(Fighter_GObj* gobj)
{
    Fighter_UpdateModelScale(gobj);
}

void ftCo_800BC458(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= ftKp_SpecialS_80132DD0(fp->victim_gobj);
    fp->mv.co.capturekoopa.x0 =
        ftCommon_8007DC08(fp, ftKp_SpecialS_80132DE0(fp->victim_gobj));
}

void ftCo_800BC4A8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ca.specialhi.vel.y) {
        HSD_JObj* jobj =
            fp->parts[ftParts_GetBoneIndex(fp, FtPart_YRotN)].joint;
        float mv_xC = fp->mv.co.capturekoopa.xC;
        float fp_x1A50 = fp->x1A50 * mv_xC;
        float fp_x1A51 = fp->x1A51 * mv_xC;
        if (ABS(fp_x1A50 + HSD_JObjGetTranslationZ(jobj)) <=
            fp->mv.co.capturekoopa.x10)
        {
            HSD_JObjAddTranslationZ(jobj, fp_x1A50);
        }
        if (ABS(fp_x1A51 + HSD_JObjGetTranslationY(jobj)) <=
            fp->mv.co.walk.fast_anim_frame)
        {
            HSD_JObjAddTranslationY(jobj, fp_x1A51);
        }
        fp->mv.co.capturekoopa.x8 -= 1;
        if (fp->mv.ca.specialhi.vel.y <= 0 && !fp->mv.co.capturekoopa.x0) {
            ftAnim_SetAnimRate(gobj, 1);
            fp->mv.co.capturekoopa.x8 = 0;
        }
    }
    if (fp->mv.co.capturekoopa.x8 <= 0 && fp->mv.co.capturekoopa.x0) {
        fp->mv.co.capturekoopa.x8 = ftKp_SpecialS_80132DF0(fp->victim_gobj);
        ftAnim_SetAnimRate(gobj, ftKp_SpecialS_80132E00(fp->victim_gobj));
    }
}

static inline void inlineA0(Fighter_GObj* gobj, Fighter_GObj* vic_gobj,
                            HSD_GObjEvent cb)
{
    Fighter* vic_fp = GET_FIGHTER(vic_gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = vic_gobj;
    fp->victim_gobj = vic_gobj;
    fp->x221B_b5 = false;
    fp->x221B_b7 = false;
    fp->facing_dir = vic_fp->facing_dir;
    ftCommon_InitGrab(fp, 0, ftKp_SpecialS_80132DC0(fp->victim_gobj));
    fp->mv.ca.specialhi.vel.y = 0;
    ftCo_800DB368(vic_fp, fp);
    cb(gobj);
    ftCommon_8007D5D4(fp);
    fp->mv.co.capturekoopa.xC = ftKp_SpecialS_80132E10(fp->victim_gobj);
    fp->mv.co.capturekoopa.x10 = ftKp_SpecialS_80132E20(fp->victim_gobj);
    ftCommon_8007E2FC(gobj);
}

void ftCo_800BC7E0(Fighter_GObj* gobj, Fighter_GObj* vic_gobj)
{
    inlineA0(gobj, vic_gobj, ftCo_800BC9C8);
}

void ftCo_CaptureKoopa_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureKoopa_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureKoopa_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureKoopa_Coll(HSD_GObj* gobj) {}

void ftCo_800BC8D4(Fighter_GObj* gobj, Fighter_GObj* vic_gobj)
{
    inlineA0(gobj, vic_gobj, ftCo_800BCAF4);
}

void ftCo_CaptureKoopaAir_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureKoopaAir_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureKoopaAir_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureKoopaAir_Coll(HSD_GObj* gobj) {}
