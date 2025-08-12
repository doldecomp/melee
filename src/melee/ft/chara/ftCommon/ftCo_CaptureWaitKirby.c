#include "ftCo_CaptureWaitKirby.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/types.h"
#include "ftKirby/ftKb_Init.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

static float const ftCo_804D8BB8 = 0;
static float const ftCo_804D8BBC = 1;
static double const ftCo_804D8BC0 = U32_TO_F32;
static double const ftCo_804D8BC8 = S32_TO_F32;

void ftCo_800BD620(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(fp->victim_gobj);
    fp->x2226_b2 = false;
    ftCo_800DB368(victim_fp, fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitKirby,
                              Ft_MF_SkipModel | Ft_MF_SkipMatAnim, 0, 1, 0,
                              NULL);
    Fighter_UpdateModelScale(gobj);
    fp->accessory1_cb = ftCo_800DB464;
    fp->x221E_b0 = true;
    ftColl_8007B62C(gobj, 2);
    ftCommon_8007D5D4(fp);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2FC(gobj);
}

static inline void inlineA0(Fighter* fp, int arg1)
{
    fp->x671_timer_lstick_tilt_y = 254;
    ftKb_SpecialN_800F598C(fp->victim_gobj, arg1);
}

void ftCo_CaptureWaitKirby_Anim(Fighter_GObj* gobj) {}
#pragma push
#pragma force_active on
void ftCo_800BD6EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->x74)
    {
        inlineA0(fp, +1);
        return;
    }
    if (fp->input.lstick.y <= p_ftCommonData->x464 &&
        fp->x671_timer_lstick_tilt_y < p_ftCommonData->x468 &&
        ftKb_SpecialN_800F597C(fp->victim_gobj))
    {
        inlineA0(fp, -1);
        ftKb_SpecialN_800F5954(fp->victim_gobj);
    }
}
#pragma pop

static inline void inlineB0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float lstick_x = fp->input.lstick.x;
    if (lstick_x < 0) {
        lstick_x = -lstick_x;
    }
    if (lstick_x >= p_ftCommonData->x3C &&
        fp->x670_timer_lstick_tilt_x <
            p_ftCommonData->x40 + p_ftCommonData->x44)
    {
        fp->x670_timer_lstick_tilt_x = 254;
        if (fp->input.lstick.x < 0) {
            ftKb_SpecialN_800F5A04(fp->victim_gobj);
        }
    }
}

void ftCo_CaptureWaitKirby_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (ftKb_SpecialN_800F5A38(fp->victim_gobj, fp)) {
        inlineB0(gobj);
        ftCo_800BD6EC(gobj);
    }
    fp->grab_timer -= ftKb_SpecialN_800F5B00(fp->victim_gobj);
    fp->mv.co.capturekirby.x18 =
        ftCommon_8007DC08(fp, ftKb_SpecialN_800F5B10(fp->victim_gobj));
    if (fp->grab_timer <= 0) {
        Fighter_GObj* victim_gobj = fp->victim_gobj;
        fp->facing_dir = ftKb_SpecialN_800F5A60(victim_gobj);
        HSD_JObjSetScale(jobj, &jobj->scale);
        ftCo_800DC750(gobj);
        ftCo_800DA698(victim_gobj, 0);
    }
}

void ftCo_CaptureWaitKirby_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureWaitKirby_Coll(Fighter_GObj* gobj) {}
