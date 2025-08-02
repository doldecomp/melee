#include <placeholder.h>
#include <platform.h>

#include "ftCommon/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include "ftCo_DamageIce.h"

#include "ftCo_DownAttack.h"
#include "ftCo_DownBound.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_HammerJump.h"
#include "ftCo_HammerWait.h"
#include "ftCo_Lift.h"
#include "ftCo_PassiveStand.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0D14.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdynamics.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <baselib/debug.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <common_structs.h>
#include <dolphin/mtx.h>

/* 0909D0 */ static void ftCo_800909D0(ftCo_Fighter* fp);
/* 090B48 */ static void ftCo_80090B48(ftCo_GObj* gobj);
/* 091274 */ static void ftCo_80091274(ftCo_GObj* gobj);
/* 091620 */ static void ftCo_80091620(HSD_GObj* gobj, Vec3 *normal, Vec3 *vec);

static Vec3 const ftCo_803B74B0 = { 0 };
static Vec3 const ftCo_803B74BC = { 0 };
float atan2f(float, float);

void ftCo_80090984(ftCo_GObj* gobj)
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
        float radius = fp->x34_scale.y * fp->co_attrs.bubble_ratio;
        lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &pos);
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint, NULL,
            &offset);
        lbVector_Sub(&offset, &pos);
        fp->mv.co.damageice.x8.top = radius + offset.y;
        fp->mv.co.damageice.x8.bottom = -radius + offset.y;
        fp->mv.co.damageice.x8.right.x = radius + offset.x;
        fp->mv.co.damageice.x8.right.y = 0;
        fp->mv.co.damageice.x8.left.x = -radius + offset.x;
        fp->mv.co.damageice.x8.left.y = 0;
        ftCommon_8007D5BC(fp);
        if (fp->ground_or_air == GA_Air) {
            ft_80082638(fp->gobj, &fp->mv.co.damageice.x8);
        } else {
            ft_80082888(fp->gobj, &fp->mv.co.damageice.x8);
        }
    }
}

static inline void inlineA0(ftCo_GObj* gobj, HSD_JObj* joint, float* param)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    efAsync_Spawn(gobj, &fp->x60C, 3, 1045, joint, param);
}

void ftCo_80090AC0(Fighter* fp)
{
    float param;
    HSD_JObj* joint = fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint;
    float scl_y = fp->x34_scale.y * fp->co_attrs.bubble_ratio;
    param = scl_y / p_ftCommonData->x7A0;
    inlineA0(fp->gobj, joint, &param);
    fp->x2219_b0 = true;
}

void ftCo_80090B48(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x2227_b6 = false;
}

void ftCo_80090B60(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftCo_80091030(Fighter_GObj* gobj)
{
    float param;
    struct UNK_SAMUS_S2 sp2C;
    Vec3 sp20;
    HSD_JObj* temp_r7;
    float temp_f1;
    float temp_f2;
    Fighter* fp = gobj->user_data;
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x2227_b6 = true;
    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageIce,
        Ft_MF_KeepGfx | Ft_MF_Unk06, 0, 1, 0, NULL);
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
    fp->mv.co.damageice.x0 = 0;
    temp_f2 = p_ftCommonData->x788;
    fp->mv.ca.specialhi.vel.x = (p_ftCommonData->x78C - temp_f2) * HSD_Randf() + temp_f2;
    ftCo_800909D0(fp);
    temp_f1 = fp->x34_scale.y * fp->co_attrs.bubble_ratio;
    temp_r7 = fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint;
    {
        param = temp_f1 / p_ftCommonData->x7A0;
        {
            HSD_GObj* temp_r3 = fp->gobj;
            efAsync_Spawn(temp_r3, &GET_FIGHTER(temp_r3)->x60C, 3, 1045,
                temp_r7, &param);
            fp->x2219_b7 = true;
            ftColl_8007B0C0(fp->gobj, Intangible);
            {
                float temp_r0;
                sp20.x = ftCo_803B74B0.x;
                sp20.y = ftCo_803B74B0.y;
                temp_r0 = ftCo_803B74B0.z;
                sp20.z = temp_r0;
                sp2C.parts[0] = ftParts_8007500C(fp, FtPart_XRotN);
                sp2C.parts[1] = FtPart_TransN;
                sp2C.parts[2] = FtPart_TopN;
                sp2C.vec2.x = sp20.x;
                sp2C.vec2.y = sp20.y;
                sp2C.vec2.z = temp_r0;
                sp2C.vec1.x = sp2C.vec2.x;
                sp2C.vec1.y = sp2C.vec2.y;
                sp2C.vec1.z = temp_r0;
                sp2C.scale = fp->co_attrs.bubble_ratio;
                ftColl_8007B5AC(fp, fp->hurt_capsules, &sp2C);
                ftCommon_8007EBAC(fp, 1, 0);
                fp->x21F0 = ftCo_80091274;
                fp->take_dmg_cb = ftCo_80090B48;
            }
        }
    }
}

void ftCo_80091274(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x1A4C = -(fp->dmg.x1838_percentTemp * p_ftCommonData->x79C - fp->x1A4C);
    if (fp->dmg.x1860_element == 1) {
        fp->x1A4C = 0;
    }
}

#define HSD_ASSERT2(file, line, msg, cond) \
    ((cond) ? ((void)0) : __assert((file), (line), (#msg)))

void ftCo_DamageIce_Anim(ftCo_GObj* gobj)
{
    HSD_JObj* jobj;
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        float rot_x = fp->mv.co.damageice.x4;
        jobj = fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint;
        HSD_ASSERT2("jobj.h", 1029, "jobj", jobj);
        jobj->rotate.x += rot_x;
        if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
            HSD_JObjSetMtxDirty(jobj);
        }
    }
    if (!fp->x2224_b2) {
        fp->x1A4C -= p_ftCommonData->x794;
    }
    ftCommon_8007DC08(fp, p_ftCommonData->x798);
    if (fp->x1A4C <= 0) {
        ftCo_80091854(gobj);
    }
}

void ftCo_DamageIce_IASA(ftCo_GObj* gobj) { }

void ftCo_DamageIce_Phys(ftCo_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* co = &fp->co_attrs;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007CEF4(fp);
        ftCommon_8007D494(fp, co->grav * p_ftCommonData->x77C,
            co->terminal_vel);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftCo_DamageIce_Coll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCo_800914A4(gobj);
    } else if (!ft_80082888(gobj, &fp->mv.co.damageice.x8)) {
        ftCommon_8007D5D4(fp);
    }
}

static float SOME_CONSTANT_IDK = 3.0f;
static float SOME_CONSTANT_IDK_2 = 0.0f;

void ftCo_800914A4(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp;
    CollData *coll_data;
    bool ret;
    Vec3 vec;
    PAD_STACK(12);
    
    fp = GET_FIGHTER(gobj);
    coll_data = &fp->coll_data;
    
    if (fp->cur_anim_frame <= SOME_CONSTANT_IDK) {
        ret = ft_80082638(gobj, &fp->mv.co.damageice.x8);
    } else {
        ret = ft_800824A0(gobj, &fp->mv.co.damageice.x8);
    }
    
    if ((coll_data->env_flags & 0x800) && fp->mv.co.damageice.x0 != 1) {
        vec.x = coll_data->xA4_ecbCurrCorrect.left.x;
        vec.y = coll_data->xA4_ecbCurrCorrect.left.y;
        vec.z = SOME_CONSTANT_IDK_2;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        ftCo_80091620(gobj, &coll_data->left_wall.normal, &vec);
        fp->mv.co.damageice.x0 = 1;
    } else if ((coll_data->env_flags & 0x20) && fp->mv.co.damageice.x0 != 2) {
        vec.x = coll_data->xA4_ecbCurrCorrect.right.x;
        vec.y = coll_data->xA4_ecbCurrCorrect.right.y;
        vec.z = SOME_CONSTANT_IDK_2;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        ftCo_80091620(gobj, &coll_data->right_wall.normal, &vec);
        fp->mv.co.damageice.x0 = 2;
    } else if ((coll_data->env_flags & 0x4000) && fp->mv.co.damageice.x0 != 3) {
        vec.x = SOME_CONSTANT_IDK_2;
        vec.y = coll_data->xA4_ecbCurrCorrect.top.y;
        vec.z = SOME_CONSTANT_IDK_2;
        ftKb_SpecialN_800F1F1C(gobj, &vec);
        ftCo_80091620(gobj, &coll_data->ceiling.normal, &vec);
        fp->mv.co.damageice.x0 = 3;
    } else if (ret) {
        ftCommon_8007D7FC(fp);
    }
}

static inline float my_sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;
    u8 _[4] = { 0 };
    volatile float y;
    if (x > 0) {
        double guess = __frsqrte((double) x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        guess = _half * guess * (_three - guess * guess * x);
        y = (float) (x * guess);
        return y;
    }
    return x;
}

void ftCo_80091620(HSD_GObj* gobj, Vec3 *normal, Vec3 *vec)
{
    ftCo_Fighter* fp;
    CollData* coll_data;
    float sp24;
    Vec3 sp2C;
    
    fp = GET_FIGHTER(gobj);
    coll_data = &fp->coll_data;
    
    sp2C.x = fp->cur_pos.x + vec->x;
    sp2C.y = fp->cur_pos.y + vec->y;
    sp2C.z = fp->cur_pos.z + vec->z;
    
    sp24 = atan2f(-normal->x, normal->y);
    efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, 0x406, NULL, &sp2C, &sp24);
    
    Camera_80030E44(2, &sp2C);
    
    ftCommon_8007EBAC(fp, 7, 0);
    ft_80088148(fp, 0x123, 0x7f, 0x40);
    
    {
        float x, y, z, mag;
        x = fp->self_vel.x;
        y = fp->self_vel.y;
        z = fp->self_vel.z;
        x *= x;
        y *= y;
        z *= z;
        mag = my_sqrtf(x+y+z);
        
        if (mag > p_ftCommonData->x780) {
            ft_80088148(fp, 0x123, 0x7f, 0x40);
            
            fp->cur_pos = sp2C;
            fp->x2227_b6 &= (0 << 1);
            ftCo_80090780((Fighter_GObj *)gobj);
        } else {
            lbVector_Mirror(&fp->self_vel, normal);
            {
                float x784 = p_ftCommonData->x784;
                fp->self_vel.x *= x784;
                fp->self_vel.y *= x784;
            }
            
            if ((coll_data->env_flags & 0x800) != 0) {
                fp->cur_pos.x = -((fp->x68C_transNPos.z * -fp->facing_dir) - (fp->cur_pos.x + vec->x));
            } else {
                fp->cur_pos.y = fp->cur_pos.y + vec->y + fp->x68C_transNPos.y;
            }
            
            if (ft_80081D0C((Fighter_GObj *)gobj)) {
                ftCommon_8007D7FC(fp);
            }
        }
    }
}

void ftCo_80091854(HSD_GObj* gobj)
{
    Vec3 vec;
    float sp24;
    HSD_JObj* jobj;
    ftCo_Fighter* fp;
    PAD_STACK(20);

    fp = GET_FIGHTER(gobj);
    if (ftCo_800C5240(gobj)) {
        ftCo_800C5A98(gobj);
    } else {
        ftCommon_8007D5D4(fp);
        fp->x2227_b6 = false;
        Fighter_ChangeMotionState(gobj, 0x146, 0x40U, 0, 0, 0, NULL);
        ft_80088148(fp, 0x123, 0x7F, 0x40);
        jobj = fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint;
        vec = ftCo_803B74BC;
        sp24 = fp->x34_scale.y * fp->co_attrs.bubble_ratio / p_ftCommonData->x7A0;
        efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 5, 1091, jobj, &vec, &sp24);
        fp->self_vel.x = fp->input.lstick.x * *(float*)&fp->co_attrs.x144;
        fp->self_vel.y = fp->co_attrs.x140;
        fp->mv.co.damageicejump.x0 = p_ftCommonData->x7A4;
    }
}

void ftCo_DamageIceJump_Anim(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.damageicejump.x0 > 0) {
        fp->mv.co.damageicejump.x0 -= 1;
        if (fp->mv.co.damageicejump.x0 <= 0) {
            ftCo_Fall_Enter(gobj);
        }
    }
}

void ftCo_DamageIceJump_IASA(ftCo_GObj* gobj) { }

void ftCo_DamageIceJump_Phys(ftCo_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftCo_DamageIceJump_Coll(ftCo_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}
