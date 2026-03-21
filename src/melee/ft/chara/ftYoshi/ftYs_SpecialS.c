#include "ftYs_SpecialS.h"

#include "ftYs_Init.h"
#include "ftYs_SpecialHi.h"
#include "math.h"
#include "placeholder.h"

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Fall.h"
#include "ft/chara/ftCommon/ftCo_FallSpecial.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftYoshi/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "mp/mplib.h"
#include "MSL/trigf.h"

#include <dolphin/mtx.h>
#include <baselib/gobj.h>

extern bool ftYs_Unk3_803CED48[];

/* 3CED84 */ static Vec4 ftYs_Unk3_803CED84 = { 0.65, 0.7, 0.8, 1 };
/* 3CED94 */ static Vec4 ftYs_Unk3_803CED94 = { 1.1, 1.35, 1.3, 1.2 };
/* 3CEDA4 */ static ftCollisionBox ftYs_Unk3_803CEDA4 = {
    12, 0, -6, 6, 6, 6,
};

static inline void ftYoshi_SpecialS_SetCall(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death2_cb = fn_8012EC7C;
    fp->take_dmg_cb = fn_8012EDE8;
    fp->deal_dmg_cb = fn_8012EFF4;
    fp->x21F8 = fn_8013295C;
}

static inline void ftYs_SpecialS_SpawnWallBounceEffect(Fighter_GObj* gobj,
                                                       CollData* cd,
                                                       bool facing_right)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 angle;
    Vec3 pos = fp->cur_pos;
    if (facing_right) {
        angle = atan2f(-cd->left_facing_wall.normal.x,
                       cd->left_facing_wall.normal.y);
        pos.x += ABS(fp->coll_data.ecb.right.x);
    } else {
        angle = atan2f(-cd->right_facing_wall.normal.x,
                       cd->right_facing_wall.normal.y);
        pos.x -= ABS(fp->coll_data.ecb.left.x);
    }
    pos.y += 0.5F * ABS(fp->coll_data.ecb.top.y + fp->coll_data.ecb.bottom.y);
    efSync_Spawn(0x406, gobj, &pos, &angle);
    Camera_80030E44(3, &pos);
    ftCommon_8007EBAC(fp, 0xC, 0xA);
}

void ftYs_SpecialS_8012EB48(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    switch (fp->cmd_vars[0]) {
    case 1:
        fp->mv.ys.specials.x4++;
        break;
    case 2:
        fp->mv.ys.specials.x4 = 0;
        fp->cmd_vars[1]++;
        break;
    }

    if (fp->mv.ys.specials.x4 >= 0 && fp->mv.ys.specials.x4 < 14) {
        ftParts_80074B0C(gobj, 0, ftYs_Unk3_803CED48[fp->mv.ys.specials.x4]);
        if (ftYs_Unk3_803CED48[fp->mv.ys.specials.x4] == 1) {
            ftYs_Init_8012B918(gobj);
            ftCommon_8007F5CC(gobj, 0);
            fp->x221E_b4 = 0;
        } else {
            ftCommon_8007F5CC(gobj, 1);
            fp->x221E_b4 = 1;
        }
        if (fp->cmd_vars[0] == 2U) {
            fp->mv.ys.specials.x4 = -1;
            fp->cmd_vars[0] = 0;
        }
    } else {
        fp->cmd_vars[0] = 0;
    }
}

static inline void fn_8012EC7C_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    FtMotionId motion = fp->motion_id;
    if ((motion != 0x16B) && ((motion >= 0x16B) || (motion != 0x167))) {
        ftParts_80074B0C(gobj, 0, 0);
    }
    HSD_JObjSetScale(jobj, &fp->fv.ys.x222C);
    ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
    ftPartSetRotZ(fp, 2, 0.0F);
    if (fp->mv.ys.specials.x24 != 0.0F) {
        fp->facing_dir = fp->mv.ys.specials.x24;
    }
    fp->mv.ys.specials.x24 = 0.0F;
    ftCommon_8007F5CC(gobj, 1);
    fp->x221E_b4 = 1;
}

static inline void ftYs_SpecialS_UpdateScale(Fighter_GObj* gobj, Vec3* scale)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (fp->mv.ys.specials.x8 >= 0 && fp->mv.ys.specials.x8 < 4) {
        scale->x = fp->fv.ys.x222C.x;
        scale->y = fp->fv.ys.x222C.y *
                   ((f32*) &ftYs_Unk3_803CED84)[fp->mv.ys.specials.x8];
        scale->z = fp->fv.ys.x222C.z *
                   ((f32*) &ftYs_Unk3_803CED94)[fp->mv.ys.specials.x8];
        HSD_JObjSetScale(jobj, scale);
        fp->mv.ys.specials.x8++;
    } else {
        HSD_JObjSetScale(jobj, &fp->fv.ys.x222C);
    }
}

static inline void ftYs_SpecialS_WrapAndSetRotX(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    while (fp->mv.ys.specials.x14 < 0.0F) {
        fp->mv.ys.specials.x14 += 2 * M_PI;
    }
    while (fp->mv.ys.specials.x14 > 2 * M_PI) {
        fp->mv.ys.specials.x14 -= 2 * M_PI;
    }
    ftPartSetRotX(fp, 3, fp->mv.ys.specials.x14);
}

static inline s32 ftYs_SpecialS_CheckButtonPressure(Fighter_GObj* gobj)
{
    s32 result = 0;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attrs = fp->dat_attrs;
    if ((u8) fp->x673 < attrs->x98) {
        result = 1;
    }
    fp->x673 = 0;
    return result;
}

void fn_8012EC7C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    FtMotionId motion = fp->motion_id;
    if ((motion != 0x16B) && ((motion >= 0x16B) || (motion != 0x167))) {
        ftParts_80074B0C(gobj, 0, 0);
    }
    HSD_JObjSetScale(jobj, &fp->fv.ys.x222C);
    ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
    ftPartSetRotZ(fp, 2, 0.0F);
    if (fp->mv.ys.specials.x24 != 0.0F) {
        fp->facing_dir = fp->mv.ys.specials.x24;
    }
    fp->mv.ys.specials.x24 = 0.0F;
    ftCommon_8007F5CC(gobj, 1);
    fp->x221E_b4 = 1;
}

void fn_8012EDE8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId motion = fp->motion_id;
    Vec3 v;
    if ((motion != 0x16B) && ((motion >= 0x16B) || (motion != 0x167))) {
        lb_8000B1CC(fp->parts[4].joint, NULL, &v);
        efSync_Spawn(0x4CF, gobj, &v, &fp->co_attrs.xBC);
        ft_PlaySFX(fp, 0x44618, 0x7FU, 0x40U);
    }
    fn_8012EC7C_inline(gobj);
}

void fn_8012EFC0(Fighter_GObj* gobj)
{
    ft_80089824(gobj);
    ft_800892A0(gobj);
}

void fn_8012EFF4(Fighter_GObj* gobj)
{
    f32 temp_f2;
    FtMotionId motion;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.xC = 0;
    motion = fp->motion_id;
    if ((motion != 0x16a)) {
        if (motion >= 0x16a) {
            return;
        }
        if (motion != 0x165) {
            return;
        }
    }
    fp->mv.ys.specials.x0 -= attributes->x50;
    temp_f2 = fp->ground_or_air == 1 ? attributes->x8C : attributes->x7C;
    if ((fp->mv.ys.specials.x1C < 0.0F ? -fp->mv.ys.specials.x1C
                                       : +fp->mv.ys.specials.x1C) > temp_f2)
    {
        if (fp->mv.ys.specials.x1C > 0.0F) {
            fp->mv.ys.specials.x1C -= attributes->xCC;
            if (!(fp->mv.ys.specials.x1C < temp_f2)) {
                return;
            }
            fp->mv.ys.specials.x1C = temp_f2;
            return;
        }
        temp_f2 = -temp_f2;
        fp->mv.ys.specials.x1C += attributes->xCC;
        if (!(fp->mv.ys.specials.x1C > temp_f2)) {
            return;
        }
        fp->mv.ys.specials.x1C = temp_f2;
        return;
    }
    if (0.0F != fp->mv.ys.specials.x1C) {
        return;
    }
    fp->mv.ys.specials.x1C = fp->facing_dir * temp_f2;
}

void ftYs_SpecialS_8012F0DC(Fighter_GObj* gobj, s32 arg1, s32 arg2, f32 arg3)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    PAD_STACK(8);

    ftColl_8007AFF8(gobj);

    if (arg1 == 0) {
        Fighter_ChangeMotionState(gobj, 0x167, arg2, arg3, 1.0F, 0.0F, NULL);
        fp->gr_vel *= attributes->xD0;
        fp->x74_anim_vel.y = 0.0F;
        fp->self_vel.y = 0.0F;
    } else {
        Fighter_ChangeMotionState(gobj, 0x16B, arg2, arg3, 1.0F, 0.0F, NULL);
        fp->self_vel.x *= attributes->xD0;
        fp->self_vel.y *= attributes->xD4;
        fp->xE4_ground_accel_1 = 0.0F;
        fp->gr_vel = 0.0F;
    }

    ftYoshi_SpecialS_SetCall(gobj);
    fn_8012EC7C_inline(gobj);

    fp->mv.ys.specials.x24 = 0.0F;
    ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
    ftPartSetRotZ(fp, 2, 0.0F);
}

void ftYs_SpecialS_8012F35C(Fighter_GObj* gobj)
{
    f32 var_f0;
    s32 var_r5;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    PAD_STACK(16);

    HSD_JObjGetScale(jobj, &fp->fv.ys.x222C);

    if (fp->ground_or_air == GA_Ground) {
        var_f0 = attributes->x54;
    } else {
        var_f0 = attributes->x58;
    }
    fp->mv.ys.specials.x1C = var_f0;

    {
        s32 var_r5 = 0;
        Fighter* fp2 = GET_FIGHTER(gobj);
        ftYoshiAttributes* attrs2 = fp2->dat_attrs;
        if ((u8) fp2->x673 < attrs2->x98) {
            var_r5 = 1;
        }
        fp2->x673 = 0;
        if (var_r5 == 1) {
            fp->mv.ys.specials.x1C *= attributes->x68;
        }
    }

    fp->mv.ys.specials.x0 = attributes->x48;
    fp->mv.ys.specials.x4 = -1;
    fp->mv.ys.specials.x8 = -1;
    fp->mv.ys.specials.xC = 0;
    fp->mv.ys.specials.x14 = 0.0F;
    fp->mv.ys.specials.x18 = 0.0F;
    fp->mv.ys.specials.x24 = 0.0F;
    fp->mv.ys.specials.x28 = 0;
    fp->mv.ys.specials.x2C = 0;
    fp->mv.ys.specials.x30 = 0;
    fp->deal_dmg_cb = fn_8012EFF4;
    fp->x21F8 = fn_8013295C;
}

void ftYs_SpecialS_Enter(Fighter_GObj* gobj)
{
    int i;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    PAD_STACK(16);
    fp->facing_dir = fp->input.lstick.x > 0.0F ? 1.0F : -1.0F;
    Fighter_ChangeMotionState(gobj, 0x168, 0U, 0.0F, 1.0F, 0.0F, NULL);
    for (i = 3; i >= 0; i--) {
        fp->cmd_vars[i] = 0;
    }
    ftCommon_8007D5D4(fp);
    ftAnim_8006EBA4(gobj);
    ftYs_SpecialS_8012F35C(gobj);
    fp->self_vel.x = fp->mv.ys.specials.x1C * fp->facing_dir;
    fp->x74_anim_vel.x = 0.0F;
    fp->self_vel.y = attributes->x5C;
    fp->x74_anim_vel.y = attributes->specials_start_gravity;
}

void ftYs_SpecialAirS_Enter(Fighter_GObj* gobj)
{
    int i;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    PAD_STACK(16);
    fp->facing_dir = fp->input.lstick.x > 0.0F ? 1.0F : -1.0F;
    Fighter_ChangeMotionState(gobj, 0x168, 0U, 0.0F, 1.0F, 0.0F, NULL);
    for (i = 3; i >= 0; i--) {
        fp->cmd_vars[i] = 0;
    }
    ftAnim_8006EBA4(gobj);
    ftYs_SpecialS_8012F35C(gobj);
    fp->self_vel.x = fp->mv.ys.specials.x1C * fp->facing_dir;
    fp->x74_anim_vel.x = 0.0F;
    fp->self_vel.y = attributes->x5C;
    fp->x74_anim_vel.y = attributes->specials_start_gravity;
}

void ftYs_SpecialAirSStart_0_Anim(Fighter_GObj* gobj)
{
    f32 temp_f0;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.x24 = 0.0F;
    ftYs_SpecialS_8012EB48(gobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x169, 0x440012U, 0.0F, 0.0F, 0.0F,
                                  NULL);
        ftYoshi_SpecialS_SetCall(gobj);
        fp->cur_anim_frame = 0.0F;
        ftAnim_SetAnimRate(gobj, 0.0F);
        temp_f0 = fp->mv.ys.specials.x1C * fp->facing_dir;
        fp->self_vel.x = temp_f0;
        fp->gr_vel = temp_f0;
        fp->x74_anim_vel.x = 0.0F;
        fp->xE4_ground_accel_1 = 0.0F;
        fp->self_vel.y = attributes->x5C;
        fp->x74_anim_vel.y = attributes->specials_start_gravity;
    }
}

void ftYs_SpecialAirSLoop_0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    Vec3 scale;
    PAD_STACK(28);

    fp->mv.ys.specials.x24 = 0.0F;
    ftYs_SpecialS_8012EB48(gobj);
    ftYs_SpecialS_UpdateScale(gobj, &scale);

    {
        Fighter* fp4 = GET_FIGHTER(gobj);
        ftYoshiAttributes* attrs4 = fp4->dat_attrs;
        fp4->mv.ys.specials.xC++;
        if (fp4->mv.ys.specials.xC >= attrs4->xDC &&
            fp4->x914[0].state != HitCapsule_Disabled)
        {
            fp4->x914[0].x4 = (fp4->x914[0].x4 + 1) & 1;
            fp4->mv.ys.specials.xC = 0;
        }
    }

    {
        ftYoshiAttributes* attrs5;
        Fighter* fp5 = GET_FIGHTER(gobj);
        attrs5 = fp5->dat_attrs;
        if (fp5->x914[0].state != HitCapsule_Disabled) {
            s32 rate;
            if (fp5->ground_or_air == GA_Air) {
                f32 vel;
                if ((vel = fp5->self_vel.x) < 0.0F) {
                    vel = -vel;
                }
                rate = (s32) (attrs5->xC4 * (attrs5->xC0 + vel));
            } else {
                f32 vel;
                if ((vel = fp5->gr_vel) < 0.0F) {
                    vel = -vel;
                }
                rate = (s32) (attrs5->xC4 * (attrs5->xC0 + vel));
            }
            if (rate < 1) {
                rate = 1;
            }
            ftColl_8007ABD0(&fp5->x914[0], rate, gobj);
        }
    }

    {
        f32 abs_speed = fp->mv.ys.specials.x1C;
        if (abs_speed < 0.0F) {
            abs_speed = -abs_speed;
        }
        fp->mv.ys.specials.x14 =
            (f32) ((f64) (2.0 * M_PI / 25.0) * (attributes->xD8 * abs_speed) +
                   (f64) fp->mv.ys.specials.x14);
    }

    ftYs_SpecialS_WrapAndSetRotX(gobj);

    fp->mv.ys.specials.x0--;
    if (fp->mv.ys.specials.x0 <= 0) {
        fp->mv.ys.specials.x0 = 0;
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x440012, 0.0F);
    }
}

static inline f32 perm_vel_inline(Fighter* fp)
{
    return fp->gr_vel;
}

void ftYs_SpecialAirSLoop_1_Anim(Fighter_GObj* gobj)
{
    f32 angle;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    Vec3 scale;

    ftYs_SpecialS_8012EB48(gobj);
    ftYs_SpecialS_UpdateScale(gobj, &scale);

    fp->mv.ys.specials.x14 =
        ((2.0 * M_PI / 25.0) * attributes->xA0 + fp->mv.ys.specials.x14);

    ftYs_SpecialS_WrapAndSetRotX(gobj);

    {
        f32 x10 = fp->mv.ys.specials.x10;
        f32 abs_x10 = ABS(x10);
        f32 gr_vel = fp->gr_vel;
        f32 abs_vel = ABS(gr_vel);
        f32 xE4 = attributes->xE4;
        f32 abs_xE4 = ABS(xE4);

        if (x10 > 0.0F) {
            if (perm_vel_inline(fp) > 0.0F) {
                fp->mv.ys.specials.x18 = abs_xE4 * (abs_vel / abs_x10) + -xE4;
            } else {
                fp->mv.ys.specials.x18 =
                    abs_xE4 * (abs_vel / (abs_x10 * 0.7F)) + -xE4;
            }
        } else {
            if (perm_vel_inline(fp) < 0.0F) {
                fp->mv.ys.specials.x18 = abs_xE4 * (abs_vel / abs_x10) + -xE4;
            } else {
                fp->mv.ys.specials.x18 =
                    abs_xE4 * (abs_vel / (abs_x10 * 0.7F)) + -xE4;
            }
        }
    }

    ftPartSetRotZ(fp, 2, fp->mv.ys.specials.x18);

    {
        f32 x10 = fp->mv.ys.specials.x10;
        f32 abs_x10 = ABS(x10);
        f32 abs_x10_2 = ABS(x10);
        f32 total = 0.7F * abs_x10 + abs_x10_2;

        if (x10 > 0.0F) {
            f32 vel = perm_vel_inline(fp);
            f32 delta;
            if (vel > 0.0F) {
                delta = ABS(x10) - ABS(vel);
            } else {
                delta = ABS(x10) + ABS(vel);
            }
            angle = (M_PI * (delta / total) + M_PI_2);
        } else {
            f32 vel = perm_vel_inline(fp);
            f32 delta;
            if (vel < 0.0F) {
                delta = ABS(x10) - ABS(vel);
            } else {
                delta = ABS(x10) + ABS(vel);
            }
            angle = (M_PI * (delta / total) + (3.0 * M_PI / 2.0));
        }
    }

    while (angle < 0.0F) {
        angle += 2 * M_PI;
    }
    while (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    ftPartSetRotY(fp, 0, angle);

    fp->mv.ys.specials.x0--;
    if (fp->mv.ys.specials.x0 <= 0) {
        fp->mv.ys.specials.x0 = 0;
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x440012, 0.0F);
        return;
    }

    if (fp->mv.ys.specials.x28 % attributes->xA4 == 0) {
        Vec3* floor_normal = &fp->coll_data.floor.normal;
        f32 dir;
        if (perm_vel_inline(fp) < 0.0F) {
            dir = -1.0F;
        } else {
            dir = 1.0F;
        }
        angle = atan2f(-floor_normal->x, floor_normal->y);
        efSync_Spawn(0x3FF, gobj, &fp->cur_pos, &dir, &angle);
    }
    fp->mv.ys.specials.x28++;
}

void ftYs_SpecialAirSEnd_Anim(Fighter_GObj* gobj)
{
    Vec3 sp2C;
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 scale;

    fp->mv.ys.specials.x24 = 0.0F;

    if (fp->cmd_vars[1] == 1) {
        fp->cmd_vars[1]++;
        lb_8000B1CC(fp->parts[4].joint, NULL, &sp2C);
        efSync_Spawn(0x4CF, gobj, &sp2C, &fp->co_attrs.xBC);
    }

    ftYs_SpecialS_8012EB48(gobj);
    ftYs_SpecialS_UpdateScale(gobj, &scale);

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fn_8012EC7C_inline(gobj);
        ft_8008A2BC(gobj);
    }
}

void ftYs_SpecialAirSStart_1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ys.specials.x24 = 0.0F;
    fp->mv.ys.specials.x30 = 0;
    PAD_STACK(8);
    ftYs_SpecialS_8012EB48(gobj);
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        Fighter_ChangeMotionState(gobj, 0x169, 0x440012U, 0.0F, 0.0F, 0.0F,
                                  NULL);
        ftYoshi_SpecialS_SetCall(gobj);
        fp->cur_anim_frame = 0.0F;
        ftAnim_SetAnimRate(gobj, 0.0F);
    }
}

void ftYs_SpecialAirSLoop_2_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    Vec3 scale;
    PAD_STACK(4);

    fp->mv.ys.specials.x24 = 0.0F;
    fp->mv.ys.specials.x30 = 0;
    ftYs_SpecialS_8012EB48(gobj);
    ftYs_SpecialS_UpdateScale(gobj, &scale);

    fp->mv.ys.specials.x14 = (f32) ((f64) (M_PI / 30.0) * attributes->x60 +
                                    (f64) fp->mv.ys.specials.x14);

    ftYs_SpecialS_WrapAndSetRotX(gobj);

    fp->mv.ys.specials.x0--;
    if (fp->mv.ys.specials.x0 <= 0) {
        fp->mv.ys.specials.x0 = 0;
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, 0.0F);
    }
}

void ftYs_SpecialAirSLoop_3_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    Vec3 scale;
    PAD_STACK(28);

    fp->mv.ys.specials.x24 = 0.0F;
    fp->mv.ys.specials.x30 = 0;
    ftYs_SpecialS_8012EB48(gobj);
    ftYs_SpecialS_UpdateScale(gobj, &scale);

    {
        Fighter* fp4 = GET_FIGHTER(gobj);
        ftYoshiAttributes* attrs4 = fp4->dat_attrs;
        fp4->mv.ys.specials.xC++;
        if (fp4->mv.ys.specials.xC >= attrs4->xDC &&
            fp4->x914[0].state != HitCapsule_Disabled)
        {
            fp4->x914[0].x4 = (fp4->x914[0].x4 + 1) & 1;
            fp4->mv.ys.specials.xC = 0;
        }
    }

    {
        ftYoshiAttributes* attrs5;
        Fighter* fp5 = GET_FIGHTER(gobj);
        attrs5 = fp5->dat_attrs;
        if (fp5->x914[0].state != HitCapsule_Disabled) {
            s32 rate;
            if (fp5->ground_or_air == GA_Air) {
                f32 vel;
                if ((vel = fp5->self_vel.x) < 0.0F) {
                    vel = -vel;
                }
                rate = (s32) (attrs5->xC4 * (attrs5->xC0 + vel));
            } else {
                f32 vel;
                if ((vel = fp5->gr_vel) < 0.0F) {
                    vel = -vel;
                }
                rate = (s32) (attrs5->xC4 * (attrs5->xC0 + vel));
            }
            if (rate < 1) {
                rate = 1;
            }
            ftColl_8007ABD0(&fp5->x914[0], rate, gobj);
        }
    }

    {
        f32 abs_speed = fp->mv.ys.specials.x1C;
        if (abs_speed < 0.0F) {
            abs_speed = -abs_speed;
        }
        fp->mv.ys.specials.x14 =
            (f32) ((f64) (2.0 * M_PI / 25.0) * (attributes->xD8 * abs_speed) +
                   (f64) fp->mv.ys.specials.x14);
    }

    ftYs_SpecialS_WrapAndSetRotX(gobj);

    fp->mv.ys.specials.x0--;
    if (fp->mv.ys.specials.x0 <= 0) {
        fp->mv.ys.specials.x0 = 0;
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, 0.0F);
    }
}

void ftYs_SpecialAirSLanding_Anim(Fighter_GObj* gobj)
{
    Vec3 sp30;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    Vec3 scale;
    u8 pad[4];

    fp->mv.ys.specials.x24 = 0.0F;
    fp->mv.ys.specials.x30 = 0;

    if (fp->cmd_vars[1] == 1) {
        fp->cmd_vars[1]++;
        lb_8000B1CC(fp->parts[4].joint, NULL, &sp30);
        efSync_Spawn(0x4CF, gobj, &sp30, &fp->co_attrs.xBC);
    }

    ftYs_SpecialS_8012EB48(gobj);
    ftYs_SpecialS_UpdateScale(gobj, &scale);

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        fn_8012EC7C_inline(gobj);

        if (attributes->xE8 == 0.0F) {
            ftCo_Fall_Enter(gobj);
        } else {
            ftCo_80096900(gobj, 1, 0, 1, 1.0F, 0.0F);
        }
    }
}

void ftYs_SpecialAirSStart_0_IASA(Fighter_GObj* gobj) {}

void ftYs_SpecialAirSLoop_0_IASA(Fighter_GObj* gobj)
{
    f32 abs_x;
    f32 stick_x;
    f32 var_f31;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    PAD_STACK(8);

    if (fp->mv.ys.specials.x30 != 0) {
        if ((stick_x = fp->input.lstick.x) < 0.0F) {
            abs_x = -stick_x;
        } else {
            abs_x = stick_x;
        }
        if (abs_x > attributes->x9C) {
            if (stick_x > 0.0F) {
                var_f31 = 1.0F;
            } else {
                var_f31 = -1.0F;
            }
            if (fp->facing_dir != var_f31) {
                ftColl_8007AFF8(gobj);
                fp->mv.ys.specials.x24 = var_f31;
                Fighter_ChangeMotionState(gobj, 0x166, 0x4C4892,
                                          fp->cur_anim_frame, 0.0F, 0.0F,
                                          NULL);
                {
                    Fighter* fp2 = GET_FIGHTER(gobj);
                    fp2->death2_cb = fn_8012EC7C;
                    fp2->take_dmg_cb = fn_8012EDE8;
                    fp2->deal_dmg_cb = fn_8012EFF4;
                    fp2->x21F8 = fn_8013295C;
                }
                fp->mv.ys.specials.x10 = fp->gr_vel;
                fp->mv.ys.specials.x18 = 0.0F;
                fp->mv.ys.specials.x20 = -0.05f * fp->gr_vel;
                fp->mv.ys.specials.x28 = 0;
                {
                    Fighter* fp3 = GET_FIGHTER(gobj);
                    while (fp3->mv.ys.specials.x14 < 0.0F) {
                        fp3->mv.ys.specials.x14 += 2 * M_PI;
                    }
                    while (fp3->mv.ys.specials.x14 > 2 * M_PI) {
                        fp3->mv.ys.specials.x14 -= 2 * M_PI;
                    }
                    ftPartSetRotX(fp3, 3, fp3->mv.ys.specials.x14);
                }
            }
        }
    }
    if ((fp->mv.ys.specials.x0 < (attributes->x48 - attributes->x4C)) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        fp->mv.ys.specials.x24 = 0.0F;
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x440012, 0.0F);
    }
}

void ftYs_SpecialAirSLoop_1_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    s32 x48 = attributes->x48;
    s32 x4C = attributes->x4C;
    s32 difference = x48 - x4C;

    if ((fp->mv.ys.specials.x0 < difference) && (fp->input.x668 & HSD_PAD_B)) {
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x440012, 0.0F);
    }
}

void ftYs_SpecialAirSEnd_IASA(Fighter_GObj* gobj) {}

void ftYs_SpecialAirSStart_1_IASA(Fighter_GObj* gobj)
{
    M2C_FIELD(gobj->user_data, s32*, 0x2370) = 0;
}

void ftYs_SpecialAirSLoop_2_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    if ((fp->mv.ys.specials.x0 < attributes->x48 - attributes->x4C) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, 0.0F);
    }
}

void ftYs_SpecialAirSLoop_3_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.x30 = 0;

    if ((fp->mv.ys.specials.x0 < (attributes->x48 - attributes->x4C)) &&
        (fp->input.x668 & HSD_PAD_B))
    {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x440012, 0.0F);
    }
}

void ftYs_SpecialAirSLanding_IASA(Fighter_GObj* gobj)
{
    GET_FIGHTER(gobj)->mv.ys.specials.x30 = 0;
}

void ftYs_SpecialAirSStart_0_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->xE4_ground_accel_1 = 0.0F;
    fp->gr_vel = 0.0F;
    fp->self_vel.y = 0.0F;
    fp->self_vel.x = 0.0F;
    fp->x74_anim_vel.y = 0.0F;
    fp->x74_anim_vel.x = 0.0F;
}

void ftYs_SpecialAirSLoop_0_Phys(Fighter_GObj* gobj)
{
    f32 dir;
    f32 floor_nx;
    f32 max_speed, target_speed, accel, accel2;
    f32 f5, f6;
    f32 delta;
    f32 f31;
    f32 vel;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    PAD_STACK(8);

    floor_nx = fp->coll_data.floor.normal.x;

    if (floor_nx > 0.0F) {
        dir = 1.0F;
    } else {
        dir = -1.0F;
    }

    vel = fp->gr_vel;

    if (vel > 0.0F) {
        if (floor_nx > 0.0F) {
            f32 slope = 1.0F - fp->coll_data.floor.normal.y;
            f5 = slope * (dir * attributes->x94) + 1.0F;
            f6 = -(slope * dir - 1.0F);
        } else {
            f32 temp = (1.0F - fp->coll_data.floor.normal.y) * dir;
            f5 = 1.0F + temp;
            f6 = 1.0F - temp;
        }
    } else {
        if (floor_nx < 0.0F) {
            f32 neg_dir = -dir;
            f32 slope = 1.0F - fp->coll_data.floor.normal.y;
            f5 = slope * (neg_dir * attributes->x94) + 1.0F;
            f6 = -(slope * neg_dir - 1.0F);
        } else {
            f32 temp = (1.0F - fp->coll_data.floor.normal.y) * -dir;
            f5 = 1.0F + temp;
            f6 = 1.0F - temp;
        }
    }

    f31 = attributes->x80 * f5;
    target_speed = attributes->x7C * f5;
    accel = attributes->x74 * f5;
    accel2 = attributes->x78 * f6;

    {
        f32 abs_vel = ABS(vel);
        if (abs_vel >= target_speed) {
            delta = -accel2;
            if (abs_vel + delta < target_speed) {
                delta = abs_vel - target_speed;
            }
        } else {
            delta = accel;
            if (abs_vel + accel > target_speed) {
                delta = target_speed - abs_vel;
            }
        }
    }

    if (vel < 0.0F) {
        delta = -delta;
    }

    fp->gr_vel += delta * mpLib_800569EC(fp->coll_data.floor.flags);
    if (ABS(fp->gr_vel) > f31) {
        fp->gr_vel = (fp->gr_vel < 0.0F) ? -f31 : f31;
    }
    fp->mv.ys.specials.x1C = ABS(fp->gr_vel);

    fp->x74_anim_vel.y = 0.0F;
    fp->self_vel.y = 0.0F;
    ftCommon_ApplyGroundMovement(gobj);
}

void ftYs_SpecialAirSLoop_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);
    fp->gr_vel +=
        fp->mv.ys.specials.x20 * mpLib_800569EC(fp->coll_data.floor.flags);
    fp->x74_anim_vel.y = 0.0F;
    fp->self_vel.y = 0.0F;
    ftCommon_ApplyGroundMovement(gobj);

    if (fp->mv.ys.specials.x10 > 0.0F) {
        if (fp->gr_vel < 0.0F) {
            if (ABS(fp->gr_vel) > 0.7F * ABS(fp->mv.ys.specials.x10)) {
                fp->x21EC = fn_8012EFC0;
                Fighter_ChangeMotionState(gobj, 0x165, 0x02440812,
                                          fp->cur_anim_frame, 0.0F, 0.0F,
                                          NULL);
                ft_PlaySFX(GET_FIGHTER(gobj), 0x44621, 0x7F, 0x40);
                ftYoshi_SpecialS_SetCall(gobj);

                if (fp->mv.ys.specials.x24 != 0.0F) {
                    fp->facing_dir = fp->mv.ys.specials.x24;
                }
                fp->mv.ys.specials.x24 = 0.0F;
                fp->mv.ys.specials.xC = 0;
                ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
                ftPartSetRotZ(fp, 2, 0.0F);
                ftYs_SpecialS_WrapAndSetRotX(gobj);
            }
        }
    } else {
        if (fp->gr_vel > 0.0F) {
            if (ABS(fp->gr_vel) > 0.7F * ABS(fp->mv.ys.specials.x10)) {
                fp->x21EC = fn_8012EFC0;
                Fighter_ChangeMotionState(gobj, 0x165, 0x02440812,
                                          fp->cur_anim_frame, 0.0F, 0.0F,
                                          NULL);
                ft_PlaySFX(GET_FIGHTER(gobj), 0x44621, 0x7F, 0x40);
                ftYoshi_SpecialS_SetCall(gobj);

                if (fp->mv.ys.specials.x24 != 0.0F) {
                    fp->facing_dir = fp->mv.ys.specials.x24;
                }
                fp->mv.ys.specials.x24 = 0.0F;
                fp->mv.ys.specials.xC = 0;
                ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
                ftPartSetRotZ(fp, 2, 0.0F);
                ftYs_SpecialS_WrapAndSetRotX(gobj);
            }
        }
    }
}

void ftYs_SpecialAirSEnd_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_ApplyFrictionGround(fp, fp->co_attrs.gr_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftYs_SpecialAirSStart_1_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_Fall(fp, attributes->specials_start_gravity,
                  attributes->specials_start_terminal_vel);
}

void ftYs_SpecialAirSLoop_2_Phys(Fighter_GObj* gobj)
{
    f32 var_f0;
    f32 var_f2;
    f32 temp;

    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    temp = fp->input.lstick.x * attributes->xE0;
    fp->self_vel.x += temp;
    var_f0 = fp->self_vel.x < 0.0F ? -fp->self_vel.x : fp->self_vel.x;
    var_f2 = attributes->x90;
    if (var_f0 > var_f2) {
        if (fp->self_vel.x < 0.0F) {
            var_f2 = -var_f2;
        }
        fp->self_vel.x = var_f2;
    }
    ftCommon_Fall(fp, attributes->specials_start_gravity,
                  attributes->specials_start_terminal_vel);
}

void ftYs_SpecialAirSLoop_3_Phys(Fighter_GObj* gobj)
{
    f32 var_f0;
    f32 var_f2;
    f32 temp;

    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    fp->mv.ys.specials.x30 = 0;
    temp = fp->input.lstick.x * attributes->xE0;
    fp->self_vel.x += temp;
    var_f0 = fp->self_vel.x < 0.0F ? -fp->self_vel.x : fp->self_vel.x;
    var_f2 = attributes->x90;
    if (var_f0 > var_f2) {
        if (fp->self_vel.x < 0.0F) {
            var_f2 = -var_f2;
        }
        fp->self_vel.x = var_f2;
    }
    ftCommon_Fall(fp, attributes->specials_start_gravity,
                  attributes->specials_start_terminal_vel);
}

void ftYs_SpecialAirSLanding_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;

    fp->mv.ys.specials.x30 = 0;
    ftCommon_Fall(fp, attributes->specials_start_gravity,
                  attributes->specials_start_terminal_vel);
}

void ftYs_SpecialAirSStart_0_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj) == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 360, 0x0C4C5092U, fp->cur_anim_frame,
                                  1.0F, 0.0F, NULL);
        ftYoshi_SpecialS_SetCall(gobj);
    }
}

// permuter-generated helpers, almost certainly fake
static inline f32 perm_neg_inline(f32 x)
{
    return -x;
}

static inline f32 perm_mul_inline(f32 a, f32 b)
{
    return a * b;
}

static inline f32 perm_vel_x_inline(Fighter* fp)
{
    return fp->self_vel.x;
}

void ftYs_SpecialAirSLoop_0_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    s32 coll_result = ft_80082888(gobj, &ftYs_Unk3_803CEDA4);
    bool wall_hit;

    if (fp->facing_dir == 1.0F) {
        if ((wall_hit = fp->coll_data.env_flags & 0x3F)) {
            ftYs_SpecialS_SpawnWallBounceEffect(gobj, &fp->coll_data, true);
        }
    } else {
        if ((wall_hit = fp->coll_data.env_flags & 0xFC0)) {
            ftYs_SpecialS_SpawnWallBounceEffect(gobj, &fp->coll_data, false);
        }
    }

    if (wall_hit) {
        ftCommon_8007D5D4(fp);
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x4C4092, 0.0F);
        fp->self_vel.x *= perm_neg_inline(attributes->xAC);
        fp->self_vel.y = attributes->xB0;
    } else if (coll_result == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x16A, 0x0C4C509AU, fp->cur_anim_frame,
                                  0.0F, 0.0F, NULL);
        ftYoshi_SpecialS_SetCall(gobj);
        ftYs_SpecialS_WrapAndSetRotX(gobj);
    }

    fp->mv.ys.specials.x30++;
}

void ftYs_SpecialAirSLoop_1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    s32 coll_result;
    bool wall_hit;

    if (ABS(fp->gr_vel) > attributes->xA8) {
        coll_result = ft_80082888(gobj, &ftYs_Unk3_803CEDA4);
    } else {
        coll_result = ft_80082978(gobj, &ftYs_Unk3_803CEDA4);
    }

    if (perm_vel_x_inline(fp) > 0.0F) {
        if ((wall_hit = fp->coll_data.env_flags & 0x3F)) {
            ftYs_SpecialS_SpawnWallBounceEffect(gobj, &fp->coll_data, true);
        }
    } else {
        if ((wall_hit = fp->coll_data.env_flags & 0xFC0)) {
            ftYs_SpecialS_SpawnWallBounceEffect(gobj, &fp->coll_data, false);
        }
    }

    if (wall_hit) {
        ftCommon_8007D5D4(fp);
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x4C4092, 0.0F);
        fp->self_vel.x *= -attributes->xAC;
        fp->self_vel.y = attributes->xB0;
    } else if (coll_result == 0) {
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, 0x16A, 0x0C4C5892U, fp->cur_anim_frame,
                                  0.0F, 0.0F, NULL);
        ftYoshi_SpecialS_SetCall(gobj);

        if (fp->mv.ys.specials.x24 != 0.0F) {
            fp->facing_dir = fp->mv.ys.specials.x24;
            fp->mv.ys.specials.x1C = (perm_vel_x_inline(fp) < 0)
                                         ? (-perm_vel_x_inline(fp))
                                         : (fp->self_vel.x);
        }
        fp->mv.ys.specials.x24 = 0.0F;
        ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
        ftPartSetRotZ(fp, 2, 0.0F);
    }
}

void ftYs_SpecialAirSEnd_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80082708(gobj) == GA_Ground) {
        ftCommon_8007D5D4(fp);
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x4C4092, fp->cur_anim_frame);
    }
}

void ftYs_SpecialAirSStart_1_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ys.specials.x30 = 0;

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        Fighter_ChangeMotionState(gobj, 356, 0x0C4C5092U, fp->cur_anim_frame,
                                  1.0F, 0.0F, NULL);
        ftYoshi_SpecialS_SetCall(gobj);
    }
}

void ftYs_SpecialAirSLoop_2_Coll(Fighter_GObj* gobj)
{
    s32 coll_result;
    s32 wall_hit;
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    u8 pad[28];

    fp->mv.ys.specials.x30 = 0;
    coll_result = ft_800824A0(gobj, &ftYs_Unk3_803CEDA4);

    if (fp->facing_dir == 1.0F) {
        if ((wall_hit = fp->coll_data.env_flags & 0x3F) != 0) {
            ftYs_SpecialS_SpawnWallBounceEffect(gobj, &fp->coll_data, true);
        }
    } else {
        if ((wall_hit = fp->coll_data.env_flags & 0xFC0) != 0) {
            ftYs_SpecialS_SpawnWallBounceEffect(gobj, &fp->coll_data, false);
        }
    }

    if (wall_hit) {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x4C4092, 0.0F);
        fp->self_vel.x *= -attributes->xAC;
        fp->self_vel.y = attributes->xB0;
        return;
    }

    if (coll_result) {
        f32 vel_y = ABS(fp->self_vel.y * attributes->xB4);
        fp->self_vel.y = vel_y;
        if (vel_y < attributes->xB8) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, 0x165, 0x440012,
                                      fp->cur_anim_frame, 0.0F, 0.0F, NULL);
            ft_PlaySFX(GET_FIGHTER(gobj), 0x44621, 0x7F, 0x40);
            ftYoshi_SpecialS_SetCall(gobj);

            fp->self_vel.z = 0.0F;
            fp->self_vel.y = 0.0F;
            if (ABS(fp->self_vel.x) < 0.01F) {
                fp->self_vel.x = 0.01F * fp->facing_dir;
            }

            fp->mv.ys.specials.x1C = ABS(fp->gr_vel = fp->self_vel.x);

            {
            }

            {
                if (ABS(fp->input.lstick.x) > attributes->x9C) {
                    fp->facing_dir =
                        (fp->input.lstick.x > 0.0F) ? 1.0F : -1.0F;
                    fp->mv.ys.specials.x1C =
                        attributes->xBC * ABS(fp->input.lstick.x);
                    fp->self_vel.x = fp->gr_vel =
                        fp->mv.ys.specials.x1C * fp->facing_dir;
                }
            }
            ftCommon_8007EBAC(fp, 1, 0);
        } else {
            Fighter_ChangeMotionState(gobj, 0x16A, 0x440012,
                                      fp->cur_anim_frame, 0.0F, 0.0F, NULL);
            ftYoshi_SpecialS_SetCall(gobj);
            ftYs_SpecialS_WrapAndSetRotX(gobj);
        }

        {
            fp->mv.ys.specials.x1C = attributes->x64;
            if (ftYs_SpecialS_CheckButtonPressure(gobj) == 1) {
                fp->mv.ys.specials.x1C *= attributes->x68;
            }
            fp->self_vel.x = fp->mv.ys.specials.x1C * fp->facing_dir;
            fp->mv.ys.specials.x8 = 0;
        }
    }
}

void ftYs_SpecialAirSLoop_3_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftYoshiAttributes* attributes = fp->dat_attrs;
    s32 coll_result;
    s32 wall_hit;

    fp->mv.ys.specials.x30 = 0;
    coll_result = ft_800824A0(gobj, &ftYs_Unk3_803CEDA4);

    if (fp->facing_dir == 1.0F) {
        if ((wall_hit = fp->coll_data.env_flags & 0x3F) != 0) {
            ftYs_SpecialS_SpawnWallBounceEffect(gobj, &fp->coll_data, true);
        }
    } else {
        if ((wall_hit = fp->coll_data.env_flags & 0xFC0) != 0) {
            ftYs_SpecialS_SpawnWallBounceEffect(gobj, &fp->coll_data, false);
        }
    }

    if (wall_hit != 0) {
        ftYs_SpecialS_8012F0DC(gobj, 1, 0x4C4092, 0.0F);
        fp->self_vel.x *= -attributes->xAC;
        fp->self_vel.y = attributes->xB0;
        return;
    }

    if (coll_result != 0) {
        f32 abs_y = ABS(fp->self_vel.y * attributes->xB4);
        fp->self_vel.y = abs_y;
        if (abs_y < attributes->xB8) {
            ftCommon_8007D7FC(fp);
            Fighter_ChangeMotionState(gobj, 0x165, 0x0C4C509AU,
                                      fp->cur_anim_frame, 0.0F, 0.0F, NULL);
            ft_PlaySFX(GET_FIGHTER(gobj), 0x44621, 0x7F, 0x40);
            ftYoshi_SpecialS_SetCall(gobj);

            if (ABS(fp->mv.ys.specials.x1C) < 0.01F) {
                fp->mv.ys.specials.x1C = 0.01F;
            }
            fp->self_vel.x = fp->gr_vel =
                fp->mv.ys.specials.x1C * fp->facing_dir;
            ;
            fp->self_vel.z = 0.0F;
            fp->self_vel.y = 0.0F;
            fp->mv.ys.specials.x14 =
                ((2.0 * M_PI / 25.0) *
                     perm_mul_inline(attributes->xD8,
                                     ABS(fp->mv.ys.specials.x1C)) +
                 fp->mv.ys.specials.x14);
            ftYs_SpecialS_WrapAndSetRotX(gobj);
            ftCommon_8007EBAC(fp, 1, 0);
        } else {
            if (ABS(fp->input.lstick.x) > attributes->x9C) {
                fp->facing_dir = (fp->input.lstick.x > 0.0F) ? 1.0F : -1.0F;
                fp->mv.ys.specials.x1C =
                    attributes->xBC * ABS(fp->input.lstick.x);
                fp->self_vel.x = fp->gr_vel =
                    fp->mv.ys.specials.x1C * fp->facing_dir;
                ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
            }
            ftYs_SpecialS_WrapAndSetRotX(gobj);
        }

        fp->mv.ys.specials.x8 = 0;
    }
}

void ftYs_SpecialAirSLanding_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ys.specials.x30 = 0;

    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCommon_8007D7FC(fp);
        ftYs_SpecialS_8012F0DC(gobj, 0, 0x4C4092, fp->cur_anim_frame);
    }
}

void fn_8013295C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4);

    ftPartSetRotY(fp, 0, M_PI_2 * fp->facing_dir);
    fp->self_vel.x = -fp->self_vel.x;
    fp->gr_vel = -fp->gr_vel;
    fp->xE4_ground_accel_1 = -fp->xE4_ground_accel_1;
    fp->mv.ys.specials.x10 = -fp->mv.ys.specials.x10;
    fp->mv.ys.specials.x14 = -fp->mv.ys.specials.x14;
    fp->mv.ys.specials.x18 = -fp->mv.ys.specials.x18;
    fp->mv.ys.specials.x1C = -fp->mv.ys.specials.x1C;
    fp->mv.ys.specials.x20 = -fp->mv.ys.specials.x20;
    fp->mv.ys.specials.x24 = -fp->mv.ys.specials.x24;
}
