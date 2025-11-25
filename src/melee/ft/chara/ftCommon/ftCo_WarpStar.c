#include "ftCo_WarpStar.h"

#include "stdbool.h"

#include <platform.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/types.h"
#include "gr/stage.h"
#include "it/item.h"
#include "it/items/itwstar.h"
#include "lb/lbrefract.h"
#include "mp/mpcoll.h"

#include <math.h>
#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

#pragma force_active on

/* 0C4858 */ static void ftCo_800C4858(Fighter_GObj* gobj);
/* 0C48AC */ static void ftCo_800C48AC(Fighter_GObj* gobj);
/* 0C4A38 */ static void ftCo_800C4A38(Fighter_GObj* gobj);
/* 0C4C60 */ static void ftCo_800C4C60(Fighter_GObj* gobj);

/* literal */ float const ftCo_804D8D48 = 0;
/* literal */ float const ftCo_804D8D4C = 1;
/* literal */ float const ftCo_804D8D50 = M_PI_2;
/* literal */ SDATA char ftCo_804D3C58[] = "jobj.h";
/* literal */ SDATA char ftCo_804D3C60[] = "jobj";

void ftCo_800C4724(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    it_80294430(fp->item_gobj, fp->co_attrs.x164, fp->x2C4.y);
    fp->mv.co.warpstar.facing_dir = fp->facing_dir;
    fp->facing_dir = 0;
    fp->mv.co.warpstar.x1C = 120;
    fp->mv.co.warpstar.cur_pos = fp->cur_pos;
    fp->mv.co.warpstar.self_vel.x = fp->mv.co.warpstar.self_vel.y =
        fp->mv.co.warpstar.self_vel.z = 0;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_WarpStarJump, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftColl_8007B6A0(gobj);
    fp->take_dmg_cb = ftCo_800C4858;
    fp->death2_cb = ftCo_800C48AC;
    fp->x2219_b2 = true;
    fp->x2222_b7 = true;
    fp->x221E_b2 = true;
    ftCommon_8007E2FC(gobj);
    HSD_JObjAddAnim(jobj, it_80294364(fp->item_gobj), NULL, NULL);
    ftAnim_80070734(jobj, 0);
    HSD_JObjAnim(jobj);
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    ftColl_8007B6EC(gobj);
    fp->facing_dir = fp->mv.co.warpstar.facing_dir;
    pos.x = pos.y = pos.z = 0;
    Item_8026ABD8(fp->item_gobj, &pos, 1);
}

void ftCo_800C4858(Fighter_GObj* gobj)
{
    inlineA0(gobj);
}

void ftCo_800C48AC(Fighter_GObj* gobj)
{
    inlineA0(gobj);
}

void ftCo_WarpStarJump_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    --fp->mv.co.warpstar.x1C;
    if (fp->cur_pos.y > Stage_GetBlastZoneTopOffset() ||
        fp->mv.co.warpstar.x1C == 0)
    {
        ftCo_800C4A38(gobj);
    }
}

void ftCo_WarpStarJump_IASA(Fighter_GObj* gobj) {}

void ftCo_WarpStarJump_Phys(Fighter_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 self_vel;
    HSD_JObjGetTranslation(jobj, &self_vel);
    fp->self_vel.x = self_vel.x - fp->mv.co.warpstar.self_vel.x;
    fp->self_vel.y = self_vel.y - fp->mv.co.warpstar.self_vel.y;
    fp->self_vel.z = self_vel.z - fp->mv.co.warpstar.self_vel.z;
    fp->mv.co.warpstar.self_vel = self_vel;
}

void ftCo_WarpStarJump_Coll(Fighter_GObj* gobj) {}

void ftCo_WarpStarJump_Cam(Fighter_GObj* gobj)
{
    ftCamera_800762F4(gobj);
}

void ftCo_800C4A38(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Quaternion rot;
    it_802944AC(fp->item_gobj, &fp->mv.co.warpstar.ecb);
    Fighter_ChangeMotionState(gobj, ftCo_MS_WarpStarFall, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->x2222_b7 = true;
    fp->take_dmg_cb = ftCo_800C4858;
    fp->death2_cb = ftCo_800C48AC;
    fp->x221E_b2 = true;
    ftCommon_8007E2FC(gobj);
    fp->cur_pos.x = fp->mv.co.warpstar.cur_pos.x;
    fp->cur_pos.y = Stage_GetBlastZoneTopOffset();
    fp->cur_pos.z = 0;
    rot.x = M_PI_2;
    rot.w = 0;
    rot.z = 0;
    rot.y = 0;
    HSD_JObjSetRotation(GET_JOBJ(gobj), &rot);
    it_802946B0(fp->item_gobj);
    mpColl_80043680(&fp->coll_data, &fp->cur_pos);
}

void ftCo_WarpStarFall_Anim(Fighter_GObj* gobj) {}

void ftCo_WarpStarFall_IASA(Fighter_GObj* gobj) {}

void ftCo_WarpStarFall_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_Fall(fp, p_ftCommonData->x694, p_ftCommonData->x698);
    {
        float accel_scaling =
            fp->input.lstick.x * p_ftCommonData->warpstarfall_drift_scaling;
        float accel_flat = fp->input.lstick.x > 0
                               ? p_ftCommonData->warpstarfall_drift_flat
                               : -p_ftCommonData->warpstarfall_drift_flat;
        float accel = accel_scaling + accel_flat;
        float target_vel =
            fp->input.lstick.x * p_ftCommonData->warpstarfall_drift_max;
        ftCommon_8007D174(fp, fp->self_vel.x, accel, target_vel,
                          p_ftCommonData->x6A8);
    }
}

void ftCo_WarpStarFall_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ft_80083E64(gobj, &fp->mv.co.warpstar.ecb, ftCo_800C4C60);
}

void ftCo_800C4C60(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->facing_dir = fp->mv.co.warpstar.facing_dir;
    Fighter_ChangeMotionState(gobj, ftCo_MS_JumpB, Ft_MF_None, 0, 1, 0, NULL);
    ftColl_8007B6EC(gobj);
    fp->mv.co.jump.x0 = fp->mv.co.jump.x4 = false;
    fp->mv.co.jump.jump_mul = 1;
    fp->self_vel.x *= fp->co_attrs.ground_to_air_jump_momentum_multiplier *
                      fp->mv.co.jump.jump_mul;
    fp->self_vel.y *= p_ftCommonData->x438;
    fp->self_vel.z = 0;
    fp->self_vel.y =
        fp->co_attrs.jump_v_initial_velocity * fp->mv.co.jump.jump_mul;
    {
        float n0 = -fp->facing_dir * p_ftCommonData->x78;
        float n1 = fp->co_attrs.jump_h_initial_velocity * n0;
        float n2 = fp->mv.co.jump.jump_mul * n1;
        float n3 = fp->self_vel.x + n2;
        float n4 = fp->co_attrs.jump_h_max_velocity * fp->mv.co.jump.jump_mul;
        if (ABS(n3) > n4) {
            if (n3 < 0) {
                n3 = -n4;
            } else {
                n3 = n4;
            }
        }
        fp->self_vel.x = n3;
    }
    it_802947CC(fp->item_gobj, &fp->cur_pos);
    {
        Vec3 vec;
        vec.x = 0;
        vec.y = fp->coll_data.ecb.bottom.y;
        vec.z = 0;
        vec.x += fp->cur_pos.x;
        vec.y += fp->cur_pos.y;
        vec.z = 0 + fp->cur_pos.z;
        {
            float param = atan2f(-fp->coll_data.floor.normal.x,
                                 fp->coll_data.floor.normal.y);
            efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, 1030, NULL, &vec,
                          &param);
        }
        Camera_80030E44(4, &vec);
    }
    ftCommon_8007EBAC(fp, 14, 0);
}

void ftCo_WarpStarFall_Cam(Fighter_GObj* gobj)
{
    ftCamera_800762F4(gobj);
}
