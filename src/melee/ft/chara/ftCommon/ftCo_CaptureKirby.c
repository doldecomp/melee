#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"

#include "ftCo_CaptureKirby.h"

#include "ftCo_Lift.h"

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "ft/fighter.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/types.h"

#include <math.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <MetroTRK/intrinsics.h>

float ftCo_800BD19C(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = gobj->user_data;
    return SQ(fp->cur_pos.x - pos->x) + SQ(fp->cur_pos.y - pos->y) +
           SQ(fp->cur_pos.z - pos->z);
}

float const ftCo_804D8BA8 = 0;
float const ftCo_804D8BAC = 1;
double const ftCo_804D8BB0 = S32_TO_F32;

static inline void foo(Fighter_GObj* gobj, float arg1) {}
static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 vec0;
    Vec2 vec1;
    {
        fp->mv.co.capturekirby.x8.x = ftKb_SpecialN_800F5B4C(fp->victim_gobj);
        fp->mv.co.capturekirby.x8.y = ftKb_SpecialN_800F5B3C(fp->victim_gobj);
        ftKb_SpecialN_800F5B5C(fp->victim_gobj);
        {
            fp->mv.co.capturekirby.pos_offset.x = fp->cur_pos.x - vec0.x;
            fp->mv.co.capturekirby.pos_offset.y = fp->cur_pos.y - vec0.y;
        }
        ftKb_SpecialN_800F5B20(fp->victim_gobj);
        {
            Vec3* scale = &fp->mv.co.capturekirby.scale;
            fp->mv.co.capturekirby.x10.x = vec1.x;
            fp->mv.co.capturekirby.x10.y = vec1.y;
            HSD_JObjGetScale(jobj, scale);
        }
        fp->x2226_b2 = true;
        ftCommon_InitGrab(fp, 0, ftKb_SpecialN_800F5AF0(fp->victim_gobj));
    }
}

void ftCo_800BD1DC(Fighter_GObj* gobj, Fighter_GObj* victim_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(victim_gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x1A5C = victim_gobj;
    fp->victim_gobj = victim_gobj;
    fp->x221B_b5 = false;
    fp->x221B_b7 = false;
    fp->facing_dir = -victim_fp->facing_dir;
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureKirby, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007D5D4(fp);
    inlineA0(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007EBAC(fp, 1, 0);
    ftCommon_8007E2FC(gobj);
    fp->accessory1_cb = ftCo_800BD39C;
}

void ftCo_CaptureKirby_Anim(HSD_GObj* gobj) {}

void ftCo_CaptureKirby_IASA(HSD_GObj* gobj) {}

void ftCo_CaptureKirby_Phys(HSD_GObj* gobj) {}

void ftCo_CaptureKirby_Coll(HSD_GObj* gobj) {}

static inline void inlineB0(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float pos_x = pos->x;
    float pos_y = pos->y;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    float dist = sqrtf__Ff(SQ(pos_x) + SQ(pos_y) + SQ(pos->z));
    float mv_x8_x = fp->mv.co.capturekirby.x8.x;
    if (dist < mv_x8_x) {
        float mv_x8_y = fp->mv.co.capturekirby.x8.y;
        Vec3 scale;
        scale.x = scale.y = scale.z = 1 - mv_x8_y + dist / mv_x8_x * mv_x8_y;
        scale.x = scale.x * fp->mv.co.guard.x2C;
        scale.y *= fp->mv.co.capturekirby.scale.y;
        scale.z *= fp->mv.co.capturekirby.scale.z;
        HSD_JObjSetScale(jobj, &scale);
    }
}

static inline void inlineB1(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ABS(pos->x) > fp->mv.co.capturekirby.x10.x) {
        pos->x = fp->mv.co.capturekirby.x10.x * (pos->x < 0 ? -1 : +1);
    }
    if (ABS(pos->y) > fp->mv.co.capturekirby.x10.y) {
        pos->y = fp->mv.co.capturekirby.x10.y * (pos->y < 0 ? -1 : +1);
    }
    fp->mv.co.capturekirby.pos_offset.x -= pos->x;
    fp->mv.co.capturekirby.pos_offset.y -= pos->y;
    ftKb_SpecialN_800F5B5C(fp->victim_gobj);
    fp->cur_pos.x = pos->x + fp->mv.co.capturekirby.pos_offset.x;
    fp->cur_pos.y = pos->y + fp->mv.co.capturekirby.pos_offset.y;
    fp->cur_pos.z = pos->z;
}

void ftCo_800BD39C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    pos.x = fp->mv.co.capturekirby.pos_offset.x;
    pos.y = fp->mv.co.capturekirby.pos_offset.y;
    pos.z = 0;
    inlineB0(gobj, &pos);
    inlineB1(gobj, &pos);
}
