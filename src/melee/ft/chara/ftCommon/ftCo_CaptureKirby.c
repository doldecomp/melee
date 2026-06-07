#include "ftCo_CaptureKirby.h"

#include "ftCo_Lift.h"

#include "ft/chara/ftKirby/ftkirby.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftCommon/types.h"

#include <math.h>

float ftCo_800BD19C(Fighter_GObj* gobj, Vec3* pos)
{
    Fighter* fp = gobj->user_data;
    return SQ(fp->cur_pos.x - pos->x) + SQ(fp->cur_pos.y - pos->y) +
           SQ(fp->cur_pos.z - pos->z);
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 vec0;
    Vec2 vec1;
    Vec3* scale;
    fp->mv.co.capturekirby.x8.x = ftKb_SpecialN_800F5B4C(fp->victim_gobj);
    fp->mv.co.capturekirby.x8.y = ftKb_SpecialN_800F5B3C(fp->victim_gobj);
    ftKb_SpecialN_800F5B5C(fp->victim_gobj, &vec0);
    fp->mv.co.capturekirby.pos_offset.x = fp->cur_pos.x - vec0.x;
    fp->mv.co.capturekirby.pos_offset.y = fp->cur_pos.y - vec0.y;
    ftKb_SpecialN_800F5B20(fp->victim_gobj, &vec1);
    fp->mv.co.capturekirby.x10.x = vec1.x;
    fp->mv.co.capturekirby.x10.y = vec1.y;
    HSD_JObjGetScale(jobj, &fp->mv.co.capturekirby.scale);
    fp->x2226_b2 = true;
}

void ftCo_800BD1DC(Fighter_GObj* gobj, Fighter_GObj* victim_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(victim_gobj);
    PAD_STACK(4);
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
    ftCommon_InitGrab(fp, 0, ftKb_SpecialN_800F5AF0(fp->victim_gobj));
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
    HSD_JObj* jobj = GET_JOBJ(gobj);
    float dist = sqrtf__Ff(SQ(pos->x) + SQ(pos->y) + SQ(pos->z));
    float mv_x8_x = fp->mv.co.capturekirby.x8.x;
    if (dist < mv_x8_x) {
        struct {
            u8 pad[8];
            Vec3 scale;
        } scale_pad;
        float f;

        f = dist / mv_x8_x;
        dist = fp->mv.co.capturekirby.x8.y;
        f *= dist;
        scale_pad.scale.x = scale_pad.scale.y = scale_pad.scale.z =
            (1.0f - dist) + f;
        scale_pad.scale.x = scale_pad.scale.x * fp->mv.co.guard.x2C;
        scale_pad.scale.y *= fp->mv.co.capturekirby.scale.y;
        scale_pad.scale.z *= fp->mv.co.capturekirby.scale.z;
        HSD_JObjSetScale(jobj, &scale_pad.scale);
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
    ftKb_SpecialN_800F5B5C(fp->victim_gobj, pos);
    fp->cur_pos.x = pos->x + fp->mv.co.capturekirby.pos_offset.x;
    fp->cur_pos.y = pos->y + fp->mv.co.capturekirby.pos_offset.y;
    fp->cur_pos.z = pos->z;
}

void ftCo_800BD39C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    PAD_STACK(4);

    pos.x = fp->mv.co.capturekirby.pos_offset.x;
    pos.y = fp->mv.co.capturekirby.pos_offset.y;
    pos.z = 0;
    inlineB0(gobj, &pos);
    inlineB1(gobj, &pos);
}
