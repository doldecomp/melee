#include "ftCo_DamageIce.h"

#include "ftCo_DownAttack.h"
#include "ftCo_DownBound.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_HammerJump.h"
#include "ftCo_HammerWait.h"
#include "ftCo_Lift.h"
#include "ftCo_PassiveStand.h"

#include <placeholder.h>
#include <platform.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_DamageFall.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftCommon/types.h"
#include "ftKirby/ftKb_Init.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <baselib/forward.h>

#include <common_structs.h>
#include <math_ppc.h>
#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>
#include <baselib/random.h>

/* 0909D0 */ static void ftCo_800909D0(Fighter* fp);
/* 090B48 */ static void ftCo_DamageIce_OnHit(Fighter_GObj* gobj);
/* 091274 */ static void ftCo_DamageIce_OnHit2(Fighter_GObj* gobj);
/* 091620 */ static void ftCo_DamageIce_Collide(HSD_GObj* gobj, Vec3* normal,
                                                Vec3* vec);

static Vec3 const ftCo_DamageIce_HurtboxOffset = { 0 };
static Vec3 const ftCo_803B74BC = { 0 };
float atan2f(float, float);

void ftCo_80090984(Fighter_GObj* gobj)
{
    RETURN_IF(ftCo_80098928(gobj));
    RETURN_IF(ftCo_8009872C(gobj));
    ftCo_80097D40(gobj);
}

void ftCo_800909D0(Fighter* fp)
{
    u8 _[8] = { 0 };
    Vec3 offset;
    Vec3 pos;
    {
        u8 _[4] = { 0 };
        float radius = fp->x34_scale.y * fp->co_attrs.damageice_ice_size;
        lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &pos);
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint,
                    NULL, &offset);
        lbVector_Sub(&offset, &pos);
        fp->mv.co.damageice.ice_coll.top = radius + offset.y;
        fp->mv.co.damageice.ice_coll.bottom = -radius + offset.y;
        fp->mv.co.damageice.ice_coll.right.x = radius + offset.x;
        fp->mv.co.damageice.ice_coll.right.y = 0;
        fp->mv.co.damageice.ice_coll.left.x = -radius + offset.x;
        fp->mv.co.damageice.ice_coll.left.y = 0;
        ftCommon_UnlockECB(fp);
        if (fp->ground_or_air == GA_Air) {
            ft_80082638(fp->gobj, &fp->mv.co.damageice.ice_coll);
        } else {
            ft_80082888(fp->gobj, &fp->mv.co.damageice.ice_coll);
        }
    }
}

static inline void ftCo_SpawnEffect_x415(Fighter_GObj* gobj, HSD_JObj* joint,
                                         float* param)
{
    Fighter* fp = GET_FIGHTER(gobj);
    efAsync_Spawn(gobj, &fp->x60C, 3, 0x415, joint, param);
}

void ftCo_80090AC0(Fighter* fp)
{
    float param;
    HSD_JObj* joint = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
    float size = fp->co_attrs.damageice_ice_size;
    float scl_y = fp->x34_scale.y * size;
    param = scl_y / p_ftCommonData->damageice_ice_size;
    ftCo_SpawnEffect_x415(fp->gobj, joint, &param);
    fp->x2219_b0 = true;
}

static void ftCo_DamageIce_OnHit(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x2227_b6 = false;
}

static inline void ftCo_DamageIce_StartJump(Fighter* fp)
{
    {
        ftCo_8009E140(fp, 0);
        ftCommon_8007F824(fp->gobj);
        fp->x2222_b3 = true;

        if (fp->ground_or_air == GA_Air) {
            fp->self_vel = fp->x8c_kb_vel;
            fp->x8c_kb_vel.x = fp->x8c_kb_vel.y = fp->x8c_kb_vel.z = 0;
        } else {
            fp->gr_vel = fp->xF0_ground_kb_vel;
            fp->xF0_ground_kb_vel = 0;
        }

        ftCommon_8007E2F4(fp, 0x1FF);
        fp->mv.co.damageice.wall_hit_dir = 0;
    }

    {
        float rand, rand_range, rot_min, rot_max;

        rand = HSD_Randf();
        rot_min = p_ftCommonData->damageice_rot_speed_min;
        rot_max = p_ftCommonData->damageice_rot_speed_max;
        rand_range = rot_max - rot_min;
        fp->mv.co.damageice.rot_speed = rand_range * rand + rot_min;
    }

    ftCo_800909D0(fp);
    ftCo_80090AC0(fp);
    ftColl_8007B0C0(fp->gobj, Intangible);

    {
        ftHurtboxInit hurt;
        Vec3 offset = ftCo_DamageIce_HurtboxOffset;

        hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        hurt.height = HurtHeight_Mid;
        hurt.is_grabbable = false;
        hurt.a_offset = hurt.b_offset = offset;
        hurt.scale = fp->co_attrs.damageice_ice_size;

        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }

    ftCommon_8007EBAC(fp, 1, 0);

    fp->take_dmg_2_cb = ftCo_DamageIce_OnHit2;
    fp->take_dmg_cb = ftCo_DamageIce_OnHit;
}

static inline void JObjRotMtx(Mtx mtx, HSD_JObj* jobj)
{
    Quaternion rot;
    Mtx rot_mtx;

    HSD_JObjGetRotation(jobj, &rot);
    if ((jobj->flags & JOBJ_USE_QUATERNION) == 0) {
        HSD_MkRotationMtx(rot_mtx, (Vec3*) &rot);
    } else {
        HSD_MtxQuat(rot_mtx, &rot);
    }
    PSMTXTranspose(rot_mtx, mtx);
}

void ftCo_DamageIce_Init(Fighter_GObj* gobj)
{
    Fighter* fp;
    HSD_JObj *xrotn, *yrotn;
    Vec3 pos;
    Mtx spEC, sp11C, sp14C, sp17C;
    PAD_STACK(16);

    fp = GET_FIGHTER(gobj);

    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x2227_b6 = true;

    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageIce, Ft_MF_Unk06, 0, 1, 0,
                              NULL);

    ftCommon_InitGrab(fp, false,
                      fp->dmg.x1838_percentTemp *
                          p_ftCommonData->x790_damageice_unk);

    xrotn = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
    yrotn = fp->parts[ftParts_GetBoneIndex(fp, FtPart_YRotN)].joint;

    pos.x = 0;
    pos.y = fp->co_attrs.x154_damageice_unk;
    pos.z = fp->co_attrs.x150_damageice_unk;
    PSMTXTrans(spEC, pos.x, pos.y, pos.z);

    JObjRotMtx(sp11C, yrotn);
    JObjRotMtx(sp14C, xrotn);

    PSMTXConcat(spEC, sp11C, sp17C);
    PSMTXConcat(sp17C, sp14C, sp17C);

    HSD_MtxGetTranslate(sp17C, &pos);

    HSD_JObjAddTranslationY(yrotn, pos.y);
    HSD_JObjAddTranslationZ(yrotn, pos.z);

    ftCo_DamageIce_StartJump(fp);

    ftCo_800886D8(fp, 0x122, 0x7F, 0x40);
}

void ftCo_DamageIce_HitWhileFrozen(Fighter_GObj* gobj)
{
    Fighter* fp;
    fp = GET_FIGHTER(gobj);

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x2227_b6 = true;

    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageIce,
                              Ft_MF_KeepGfx | Ft_MF_Unk06, 0, 1, 0, NULL);

    ftCo_DamageIce_StartJump(fp);
}

void ftCo_DamageIce_OnHit2(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->grab_timer -= fp->dmg.x1838_percentTemp *
                      p_ftCommonData->damageice_dmg_time_reduction_mult;
    if (fp->dmg.x1860_element == HitElement_Fire) {
        fp->grab_timer = 0;
    }
}

void ftCo_DamageIce_Anim(Fighter_GObj* gobj)
{
    HSD_JObj* jobj;
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        float rot_x = fp->mv.co.damageice.rot_speed;
        jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
        HSD_JObjAddRotationX(jobj, rot_x);
    }
    if (!fp->x2224_b2) {
        fp->grab_timer -= p_ftCommonData->x794_damageice_unk;
    }
    ftCommon_GrabMash(fp, p_ftCommonData->x798_damageice_unk);
    if (fp->grab_timer <= 0) {
        ftCo_80091854(gobj);
    }
}

void ftCo_DamageIce_IASA(Fighter_GObj* gobj) {}

void ftCo_DamageIce_Phys(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* co = &fp->co_attrs;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007CEF4(fp);
        ftCommon_Fall(fp, co->grav * p_ftCommonData->damageice_gravity_mult,
                      co->terminal_vel);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftCo_DamageIce_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCo_DamageIce_InAirUpdate(gobj);
    } else if (!ft_80082888(gobj, &fp->mv.co.damageice.ice_coll)) {
        ftCommon_8007D5D4(fp);
    }
}

void ftCo_DamageIce_InAirUpdate(Fighter_GObj* gobj)
{
    Fighter* fp;
    CollData* coll_data;
    bool ret;
    Vec3 vec, *normal;
    PAD_STACK(12);

    fp = GET_FIGHTER(gobj);
    coll_data = &fp->coll_data;

    if (fp->cur_anim_frame <= 3.0f) {
        ret = ft_80082638(gobj, &fp->mv.co.damageice.ice_coll);
    } else {
        ret = ft_800824A0(gobj, &fp->mv.co.damageice.ice_coll);
    }

    if ((coll_data->env_flags & Collide_RightWallHug) &&
        fp->mv.co.damageice.wall_hit_dir != 1)
    {
        vec.x = coll_data->ecb.left.x;
        vec.y = coll_data->ecb.left.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        normal = &coll_data->right_facing_wall.normal;
        ftCo_DamageIce_Collide(gobj, normal, &vec);
        fp->mv.co.damageice.wall_hit_dir = 1;
    } else if ((coll_data->env_flags & Collide_LeftWallHug) &&
               fp->mv.co.damageice.wall_hit_dir != 2)
    {
        vec.x = coll_data->ecb.right.x;
        vec.y = coll_data->ecb.right.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        normal = &coll_data->left_facing_wall.normal;
        ftCo_DamageIce_Collide(gobj, normal, &vec);
        fp->mv.co.damageice.wall_hit_dir = 2;
    } else if ((coll_data->env_flags & Collide_CeilingHug) &&
               fp->mv.co.damageice.wall_hit_dir != 3)
    {
        vec.x = 0;
        vec.y = coll_data->ecb.top.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        normal = &coll_data->ceiling.normal;
        ftCo_DamageIce_Collide(gobj, normal, &vec);
        fp->mv.co.damageice.wall_hit_dir = 3;
    } else if (ret) {
        ftCommon_8007D7FC(fp);
    }
}

static inline void ftCo_SpawnEffect_x406(Fighter_GObj* gobj, Vec3* vec, f32 f)
{
    Fighter* fp = GET_FIGHTER(gobj);

    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, 0x406, NULL, vec, &f);
}

static inline f32 ftCo_Speed(Fighter* fp)
{
    return sqrtf((fp->self_vel.x * fp->self_vel.x) +
                 (fp->self_vel.y * fp->self_vel.y) +
                 (fp->self_vel.z * fp->self_vel.z));
}

void ftCo_DamageIce_Collide(Fighter_GObj* gobj, Vec3* normal, Vec3* vec)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll_data = &fp->coll_data;

    u8 _s[0x10];
    Vec3 next_pos;

    next_pos.x = fp->cur_pos.x + vec->x;
    next_pos.y = fp->cur_pos.y + vec->y;
    next_pos.z = fp->cur_pos.z + vec->z;

    ftCo_SpawnEffect_x406(gobj, &next_pos, atan2f(-normal->x, normal->y));

    Camera_80030E44(2, &next_pos);

    ftCommon_8007EBAC(fp, 7, 0);
    ft_PlaySFX(fp, 0x123, SFX_VOLUME_MAX, SFX_PAN_MID);

    if (ftCo_Speed(fp) > p_ftCommonData->damageice_min_speed) {
        ft_PlaySFX(fp, 0x123, SFX_VOLUME_MAX, SFX_PAN_MID);

        fp->cur_pos = next_pos;
        fp->x2227_b6 = false;
        ftCo_80090780(gobj);
    } else {
        lbVector_Mirror(&fp->self_vel, normal);
        {
            float mult = p_ftCommonData->damageice_speed_mult_on_break;
            fp->self_vel.x *= mult;
            fp->self_vel.y *= mult;
        }

        if ((coll_data->env_flags & Collide_RightWallHug) != 0 ||
            (coll_data->env_flags & Collide_RightWallHug) != 0)
        {
            fp->cur_pos.x = -((fp->x68C_transNPos.z * -fp->facing_dir) -
                              (fp->cur_pos.x + vec->x));
        } else {
            fp->cur_pos.y = fp->cur_pos.y + vec->y + fp->x68C_transNPos.y;
        }

        if (ft_80081D0C(gobj)) {
            ftCommon_8007D7FC(fp);
        }
    }
}
void ftCo_80091854(HSD_GObj* gobj)
{
    Vec3 vec;
    float sp24;
    HSD_JObj* jobj;
    Fighter* fp;
    PAD_STACK(20);

    fp = GET_FIGHTER(gobj);
    if (ftCo_800C5240(gobj)) {
        ftCo_800C5A98(gobj);
    } else {
        ftCommon_8007D5D4(fp);
        fp->x2227_b6 = false;
        Fighter_ChangeMotionState(gobj, ftCo_MS_DamageIceJump, Ft_MF_Unk06, 0,
                                  0, 0, NULL);
        ft_PlaySFX(fp, 0x123, SFX_VOLUME_MAX, SFX_PAN_MID);
        jobj = fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint;
        vec = ftCo_803B74BC;
        sp24 = fp->x34_scale.y * fp->co_attrs.damageice_ice_size /
               p_ftCommonData->damageice_ice_size;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, 1091, jobj, &vec,
                      &sp24);
        fp->self_vel.x =
            fp->input.lstick.x * fp->co_attrs.damageicejump_vel_x_mult;
        fp->self_vel.y = fp->co_attrs.damageicejump_vel_y;
        fp->mv.co.damageicejump.escape_timer =
            p_ftCommonData->damageicejump_escape_time;
    }
}

void ftCo_DamageIceJump_Anim(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->mv.co.damageicejump.escape_timer > 0) {
        fp->mv.co.damageicejump.escape_timer -= 1;
        if (fp->mv.co.damageicejump.escape_timer <= 0) {
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftCo_DamageIceJump_IASA(Fighter_GObj* gobj) {}

void ftCo_DamageIceJump_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftCo_DamageIceJump_Coll(Fighter_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}
