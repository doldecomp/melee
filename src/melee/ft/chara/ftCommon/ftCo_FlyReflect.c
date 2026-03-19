#include "ftCo_FlyReflect.h"

#include "ftCo_Damage.h"
#include "ftCo_DownBound.h"
#include "ftCo_PassiveCeil.h"
#include "ftCo_PassiveWall.h"
#include "placeholder.h"

#include "cm/camera.h"
#include "ft/ft_081B.h"
#include "ftCommon/inlines.h"
#include "ftKirby/ftKb_Init.h"
#include "lb/lbrefract.h"
#include "lb/lbvector.h"

#pragma force_active on

bool ftCo_800C15F4(Fighter_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    float threshold = p_ftCommonData->x1B0;
    float kb_vel_x = fp->x8c_kb_vel.x;
    if (kb_vel_x < -threshold && coll->env_flags & Collide_RightWallHug &&
        fp->mv.co.damage.x19 != ftCo_Surface_LeftWall)
    {
        u32 pad1 = 0;
        u32 pad2 = 0;
        vec.x = coll->ecb.left.x;
        vec.y = coll->ecb.left.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        {
            Vec3* normal = &coll->right_facing_wall.normal;
            ftCo_800C18A8(gobj, ftCo_MS_FlyReflectWall, normal, &vec);
        }
        fp->mv.co.damage.x19 = ftCo_Surface_LeftWall;
        return true;
    }
    if (kb_vel_x > threshold && coll->env_flags & Collide_LeftWallHug &&
        fp->mv.co.damage.x19 != ftCo_Surface_RightWall)
    {
        vec.x = coll->ecb.right.x;
        vec.y = coll->ecb.right.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        {
            Vec3* normal = &coll->left_facing_wall.normal;
            ftCo_800C18A8(gobj, ftCo_MS_FlyReflectWall, normal, &vec);
        }
        fp->mv.co.damage.x19 = ftCo_Surface_RightWall;
        return true;
    }
    return false;
}

#pragma push
#pragma dont_inline on
bool ftCo_800C1718(Fighter_GObj* gobj)
{
    Vec3 vec;
    u32 pad1 = 0;
    u32 pad2 = 0;
    Fighter* fp = gobj->user_data;
    CollData* coll = &fp->coll_data;
    if (fp->x8c_kb_vel.y > p_ftCommonData->x1B0 &&
        coll->env_flags & Collide_CeilingHug &&
        fp->mv.co.damage.x19 != ftCo_Surface_Ceiling)
    {
        vec.x = 0;
        vec.y = coll->ecb.top.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        {
            Vec3* normal = &coll->ceiling.normal;
            ftCo_800C18A8(gobj, ftCo_MS_FlyReflectCeil, normal, &vec);
        }
        fp->mv.co.damage.x19 = ftCo_Surface_Ceiling;
        return true;
    }
    return false;
}
#pragma pop

inline bool ftCo_800C1718_inline(Fighter_GObj* gobj)
{
    u32 pad = 0;
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    Vec3* normal;
    u32 pad1 = 0;
    u32 pad2 = 0;
    u32 pad3 = 0;
    u32 pad4 = 0;
    Vec3 vec;

    if (fp->x8c_kb_vel.y > p_ftCommonData->x1B0 &&
        coll->env_flags & Collide_CeilingHug &&
        fp->mv.co.damage.x19 != ftCo_Surface_Ceiling)
    {
        vec.x = 0;
        vec.y = coll->ecb.top.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        {
            normal = &coll->ceiling.normal;
            ftCo_800C18A8(gobj, ftCo_MS_FlyReflectCeil, normal, &vec);
        }
        fp->mv.co.damage.x19 = ftCo_Surface_Ceiling;
        return true;
    }
    return false;
}

bool ftCo_800C17CC(Fighter_GObj* gobj)
{
    CollData* coll;
    Vec3 vec;
    u8 _[4];
    Fighter* fp;
    s32 ret;
    PAD_STACK(0x10);

    if (ftCo_800C15F4(gobj)) {
        return true;
    }

    fp = GET_FIGHTER(gobj);
    coll = &fp->coll_data;
    if (fp->x8c_kb_vel.y > p_ftCommonData->x1B0 &&
        coll->env_flags & Collide_CeilingHug &&
        fp->mv.co.damage.x19 != ftCo_Surface_Ceiling)
    {
        vec.x = 0;
        vec.y = coll->ecb.top.y;
        vec.z = 0;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        {
            Vec3* normal = &coll->ceiling.normal;
            ftCo_800C18A8(gobj, ftCo_MS_FlyReflectCeil, normal, &vec);
        }
        fp->mv.co.damage.x19 = ftCo_Surface_Ceiling;
        ret = true;
    } else {
        ret = false;
    }
    if (ret != false) {
        return 1;
    }
    return 0;
}

inline float fake_sqrtf(float x)
{
    u32 pad = 0;
    u32 pad2 = 0;
    volatile float y;

    if (x > 0.0f) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 12 sig bits
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 24 sig bits
        guess = .5 * guess * (3.0 - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}

void ftCo_800C18A8(Fighter_GObj* gobj, ftCommon_MotionState msid, Vec3* normal,
                   Vec3* offset)
{
    Vec3 vec1;
    Vec3 vec0;
    float param;

    Fighter* fp;

    fp = GET_FIGHTER(gobj);
    vec0.x = fp->cur_pos.x + offset->x;
    vec0.y = fp->cur_pos.y + offset->y;
    vec0.z = fp->cur_pos.z + offset->z;
    param = atan2f(-normal->x, normal->y);
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5,
                  (1 << 1) | (1 << 2) | (1 << 10), NULL, &vec0, &param);
    Camera_80030E44(2, &vec0);
    vec1 = fp->self_vel;
    lbVector_Add_xy(&vec1, &fp->x8c_kb_vel);
    lbVector_Mirror(&vec1, normal);
    {
        float co_x1BC;
        co_x1BC = p_ftCommonData->x1BC;
        vec1.x *= co_x1BC;
        vec1.y *= co_x1BC;
    }
    fp->x8c_kb_vel = vec1;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
    fp->facing_dir = fp->x8c_kb_vel.x < 0 ? -1.0F : 1.0F;
    Fighter_ChangeMotionState(gobj, msid,
                              Ft_MF_Unk06 | Ft_MF_SkipNametagVis |
                                  Ft_MF_KeepColAnimPartHitStatus |
                                  Ft_MF_SkipHitStun,
                              0, 1, 0, NULL);
    if (msid == ftCo_MS_FlyReflectWall) {
        fp->cur_pos.x = -(fp->x68C_transNPos.z * -fp->facing_dir -
                          (fp->cur_pos.x + offset->x));
        ft_80081F2C(gobj);
    } else {
        fp->cur_pos.y = fp->x68C_transNPos.y + (fp->cur_pos.y + offset->y);
        ft_80082084(gobj);
    }
    fp->mv.co.damage.x18 = p_ftCommonData->x1C0;
    ftCommon_8007EBAC(fp, 7, 0);
    ftColl_8007B760(gobj, p_ftCommonData->x1B8);
    {
        float vel_x = fp->self_vel.x + fp->x8c_kb_vel.x;
        float vel_y = fp->self_vel.y + fp->x8c_kb_vel.y;
        float mag = fake_sqrtf(SQ(vel_x) + SQ(vel_y));
        ftCo_80097630(fp, ftCo_DownBound_SfxIds, mag * fp->co_attrs.weight);
    }
}

void ftCo_FlyReflect_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.damage.x18 != 0) {
        --fp->mv.co.damage.x18;
    }
    ftCo_DamageFly_Anim(gobj);
}

void ftCo_FlyReflect_IASA(Fighter_GObj* gobj)
{
    ftCo_DamageFly_IASA(gobj);
}

void ftCo_FlyReflect_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftCo_FlyReflect_Coll(Fighter_GObj* gobj)
{
    s32 tmp;
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id == ftCo_MS_FlyReflectWall) {
        if (ft_80081F2C(gobj)) {
            ftCo_80090184(gobj);
            return;
        }
        RETURN_IF(ftCo_800C23A0(gobj));
        RETURN_IF(ftCo_800C1718_inline(gobj));
        if (fp->mv.co.damage.x18 == 0) {
            RETURN_IF(ftCo_800C1D38(gobj));

            if (ftCo_800C15F4(gobj)) {
                tmp = 1;
            } else {
                if (ftCo_800C1718(gobj)) {
                    tmp = 1;
                } else {
                    tmp = 0;
                }
            }

            if (tmp != 0) {
                return;
            }
        }
    } else {
        if (ft_80082084(gobj)) {
            ftCo_80090184(gobj);
            return;
        }
        RETURN_IF(ftCo_800C1D38(gobj));
        RETURN_IF(ftCo_800C15F4(gobj));
    }
}
