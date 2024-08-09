#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "ftDonkey/forward.h"
#include "ftKoopa/forward.h"
#include "lb/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_0A01.h"

#include "ftCo_0B3E.h"
#include "ftCo_ItemGet.h"

#include "ft/fighter.h"
#include "ft/ft_0877.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "gm/gm_1601.h"
#include "gr/grbigblue.h"
#include "gr/grcorneria.h"
#include "gr/grinishie1.h"
#include "gr/ground.h"
#include "gr/grvenom.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lbcollision.h"
#include "mp/mpisland.h"
#include "mp/mplib.h"
#include "mp/types.h"
#include "pl/player.h"

#include <math.h>
#include <math_ppc.h>
#include <placeholder.h>
#include <MetroTRK/intrinsics.h>

float const ftCo_804D87D8 = 0;
double const ftCo_804D87E0 = 30;
float const ftCo_804D87E8 = 0.6;
float const ftCo_804D87EC = 0.8;
float const ftCo_804D87F0 = 0.9;
double const ftCo_804D87F8 = 0.05;
double const ftCo_804D8800 = S32_TO_F32;
float const ftCo_804D8808 = 1;
double const ftCo_804D8810 = 9;
double const ftCo_804D8818 = 18;
double const ftCo_804D8820 = 4;
double const ftCo_804D8828 = 0;
double const ftCo_804D8830 = 0.5;
float const ftCo_804D8838 = 1000;
double const ftCo_804D8840 = 5;
float const ftCo_804D8848 = 5;
float const ftCo_804D884C = 15;
float const ftCo_804D8850 = 40;
float const ftCo_804D8854 = 50;
float const ftCo_804D8858 = 10;
double const ftCo_804D8860 = 10;
float const ftCo_804D8868 = 0.5;
float const ftCo_804D886C = 2.0;
float const ftCo_804D8870 = +1e-5;
float const ftCo_804D8874 = -1e-5;
double const ftCo_804D8878 = 2.0;
float const ftCo_804D8880 = 8.5;
float const ftCo_804D8884 = 17.0;
float const ftCo_804D8888 = 3.5;
float const ftCo_804D888C = 127.0;
float const ftCo_804D8890 = 0.0078125;
double const ftCo_804D8898 = +1;
double const ftCo_804D88A0 = -1;
float const ftCo_804D88A8 = -1;
double const ftCo_804D88B0 = 255;
double const ftCo_804D88B8 = U32_TO_F32;
double const ftCo_804D88C0 = 3;
float const ftCo_804D88C8 = 10000;
double const ftCo_804D88D0 = 1000;
float const ftCo_804D88D8 = -10;
double const ftCo_804D88E0 = -5;
float const ftCo_804D88E8 = 0.4;
float const ftCo_804D88EC = 0.2;
double const ftCo_804D88F0 = 0.4;
double const ftCo_804D88F8 = 0.01;
double const ftCo_804D8900 = -1.047197543084621429443359375;
float const ftCo_804D8908 = -35;
float const ftCo_804D890C = 0.1;
float const ftCo_804D8910 = -1.3089969158172607;
float const ftCo_804D8914 = 120;
float const ftCo_804D8918 = 20;
float const ftCo_804D891C = 0.7853981852531433;
double const ftCo_804D8920 = 50;
float const ftCo_804D8928 = 100;
float const ftCo_804D892C = 80;
float const ftCo_804D8930 = M_PI;
float const ftCo_804D8934 = -M_PI_2;
float const ftCo_804D8938 = M_PI_2;
double const ftCo_804D8940 = 60;
float const ftCo_804D8948 = 4.700000286102295;
float const ftCo_804D894C = -150;
float const ftCo_804D8950 = -90;
double const ftCo_804D8958 = 40;
double const ftCo_804D8960 = 37.5;
float const ftCo_804D8968 = 0.05;
double const ftCo_804D8970 = 0.61086523346602916717529296875;
double const ftCo_804D8978 = 1.30899692885577678680419921875;
double const ftCo_804D8980 = -0.78539815731346607208251953125;

/// Roughly -#M_PI / 12 or -15 degrees.
double const ftCo_804D8988 = -0.26179938577115535736083984375;

double const ftCo_804D8990 = 15;
double const ftCo_804D8998 = -1.30899692885577678680419921875;

/// Roughly #M_PI / 12 or 15 degrees.
double const ftCo_804D89A0 = 0.26179938577115535736083984375;

float const ftCo_804D89A8 = 128;
double const ftCo_804D89B0 = 0.95;
double const ftCo_804D89B8 = 625;
float const ftCo_804D89C0 = 0.3;
float const ftCo_804D89C4 = 0.04;

int ftCo_803C5A68[] = {
    1, 0, 0, 1, 0, 0, 0, 1, 7, 6, 5, 4, 4, 3, 1, 1, 2, 1,
    5, 2, 2, 2, 3, 3, 3, 4, 0, 0, 8, 4, 1, 4, 4, 5, 5,
};

extern UNK_T* ftCo_803C6594;

#pragma force_active on

/// #ftCo_800A0148

/// #ftCo_800A0384

void ftCo_800A0508(ftCo_Fighter* fp)
{
    ftCo_800B46B8(fp, 0x80, 0);
    ftCo_800B46B8(fp, 0x81, 0);
    ftCo_800B463C(fp, 7);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 8);

    /// @todo Shared code with #ftCo_800A963C?
    ftCo_800B46B8(fp, 0x8E, 0x1E);
    ftCo_800B46B8(fp, 0x91, 0x50);
    ftCo_800B46B8(fp, 0x81, 0x7F);
    ftCo_800B463C(fp, 9);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 0xA);

    ftCo_800B46B8(fp, 0x81, 0);
    ftCo_800B463C(fp, 0x7F);
    ftCo_800B463C(fp, 0x7F);
}

/// #ftCo_800A05F4

/// #ftCo_800A0798

/// #ftCo_800A08F0

/// #ftCo_800A0AF4

void ftCo_800A0C8C(ftCo_Fighter* fp)
{
    ftCo_800B463C(fp, 127);
}

static inline float inlineA0(float x)
{
    return x * SQ(x);
}

void ftCo_800A0CB0(Fighter* fp)
{
    struct Fighter_x1A88_t* data = (void*) &fp->x1A88;
    if (fp->x1B04 % 600 == 0) {
        float rand = 1.0F - inlineA0(HSD_Randf());
        switch (fp->kind) {
        case FTKIND_DONKEY:
        case FTKIND_KOOPA:
            data->x56C = 9.0 * rand;
            return;
        case FTKIND_GKOOPS:
            data->x56C = 18.0 * rand;
            return;
        case FTKIND_NANA:
            data->x56C = 1.0 * rand;
            return;
        default:
            data->x56C = 4.0 * rand;
            return;
        }
    }
}

void ftCo_800A0DA4(Fighter* fp)
{
    Fighter* var_r31;
    HurtCapsule* hurt;
    float temp_f0;
    float temp_f0_2;
    float temp_f0_3;
    float temp_f0_4;
    float temp_f0_5;
    float temp_f0_6;
    float temp_f1;
    float temp_f3;
    float temp_f4;
    float temp_f5;
    float temp_f6;
    float var_f29;
    float var_f30;
    float var_f31;
    int var_r30;
    u32* temp_r28;

    var_r31 = fp;
    temp_r28 = &fp->x1A88;
    var_r30 = 0;
    var_f29 = 0.0f;
    var_f31 = 0.0f;
    var_f30 = 0.0f;
    while (var_r30 < (int) fp->hurt_capsules_len) {
        hurt = var_r31->hurt_capsules;
        lbColl_800083C4(hurt);
        temp_f5 = fp->cur_pos.x;
        temp_f4 = hurt->a_pos.x - temp_f5;
        temp_f3 = hurt->scale * fp->x34_scale.y;
        temp_f6 = fp->cur_pos.y;
        temp_f0 = temp_f4 - temp_f3;
        if (var_f31 > temp_f0) {
            var_f31 = temp_f0;
        }
        temp_f0_2 = temp_f4 + temp_f3;
        if (var_f30 < temp_f0_2) {
            var_f30 = temp_f0_2;
        }
        temp_f0_3 = (hurt->a_pos.y - temp_f6) + temp_f3;
        if (var_f29 < temp_f0_3) {
            var_f29 = temp_f0_3;
        }
        temp_f1 = hurt->b_pos.x - temp_f5;
        temp_f0_4 = temp_f1 - temp_f3;
        if (var_f31 > temp_f0_4) {
            var_f31 = temp_f0_4;
        }
        temp_f0_5 = temp_f1 + temp_f3;
        if (var_f30 < temp_f0_5) {
            var_f30 = temp_f0_5;
        }
        temp_f0_6 = (hurt->b_pos.y - temp_f6) + temp_f3;
        if (var_f29 < temp_f0_6) {
            var_f29 = temp_f0_6;
        }
        var_r31 += 0x4C;
        var_r30 += 1;
    }
    if (fp->facing_dir > (float) 0.0) {
        M2C_FIELD(temp_r28, float*, 0x55C) = var_f30;
        M2C_FIELD(temp_r28, float*, 0x560) = (float) -var_f31;
    } else {
        M2C_FIELD(temp_r28, float*, 0x55C) = (float) -var_f31;
        M2C_FIELD(temp_r28, float*, 0x560) = var_f30;
    }
    M2C_FIELD(temp_r28, float*, 0x564) =
        (float) (0.5 * (f64) (M2C_FIELD(temp_r28, float*, 0x55C) +
                              M2C_FIELD(temp_r28, float*, 0x560)));
    M2C_FIELD(temp_r28, float*, 0x568) = var_f29;
}

bool ftCo_800A0F00(ftCo_GObj* gobj)
{
    struct Fighter_x1A88_t* data = (void*) &GET_FIGHTER(gobj)->x1A88;
    PAD_STACK(4);
    if (ft_80087A18(gobj)) {
        /// @todo This matches if #ft_80087A80 returns an `int`.
        int result = ft_80087A80(gobj);
        if (result == 2) {
            return 1;
        }
        if (result == 1) {
            if (data->x7C % 240 > 120) {
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

bool ftCo_800A0FB0(Vec3* arg0, int* arg1, int arg2, int arg3, int arg4,
                   int arg5, int arg6, float arg7, float arg8, float arg9,
                   float arg10, float arg11)
{
    volatile int sp8;

    *arg1 = -1;
    sp8 = 0;
    {
        int ret = mpLib_8004F008(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0,
                                 arg7, arg8, arg9, arg10, arg11);
        if (ret && ftCo_800A1B38(*arg1)) {
            return false;
        }
        return ret;
    }
}

/// #ftCo_800A101C

float ftCo_800A17E4(ftCo_Fighter* fp)
{
    float result;
    if ((s8) fp->x1A8C > 0) {
        result = (s8) fp->x1A8C / 127.0f;
    } else {
        result = (s8) fp->x1A8C * 0.0078125f;
    }
    if (result > 1.0) {
        return 1.0;
    }
    if (result < -1.0) {
        result = -1.0;
    }
    return result;
}

static inline float inlineB0(s8 val, float a, float b)
{
    float ret = val > 0 ? val / a : val * b;
    return ret > +1.0 ? +1.0F : ret < -1.0 ? -1.0F : ret;
}

float ftCo_800A1874(ftCo_Fighter* fp)
{
    return inlineB0(fp->x1A8D, 127.0f, deg_to_rad);
}

float ftCo_800A1904(ftCo_Fighter* fp)
{
    float ret = fp->x1A90 / 255.0;
    return ret > 1.0 ? 1.0F : ret;
}

float ftCo_800A1948(ftCo_Fighter* fp)
{
    float ret = fp->x1A91 / 255.0;
    return ret > 1.0 ? 1.0F : ret;
}

HSD_Pad ftCo_800A198C(ftCo_Fighter* fp)
{
    return fp->x1A88;
}

float ftCo_800A1994(Fighter* fp)
{
    return inlineB0(fp->x1A8E, 127.0f, 128.0f);
}

float ftCo_800A1A24(ftCo_Fighter* fp)
{
    return inlineB0(fp->x1A8F, 127.0f, deg_to_rad);
}

f32 ftCo_800A1AB4(Fighter* fp0, Fighter* fp1)
{
    return sqrtf(SQ(fp0->cur_pos.y - fp1->cur_pos.y) +
                 SQ(fp0->cur_pos.x - fp1->cur_pos.x));
}

bool ftCo_800A1B38(enum_t arg0)
{
    if (grBigBlue_801EF844(arg0) || grInishie1_801FCAAC(arg0) ||
        grCorneria_801E2D90(arg0) || grVenom_80206D10(arg0))
    {
        return true;
    }
    return false;
}

bool ftCo_800A1BA8(ftCo_Fighter* fp)
{
    Fighter* other_fp = fp->x1ACC;
    if (other_fp == NULL) {
        return false;
    }
    {
        Vec3 coll_vec;
        PAD_STACK(2 * 4);
        {
            UNK_T sp14;
            UNK_T sp10;
            UNK_T spC;
            if (fp->facing_dir > 0.0) {
                return mpLib_800509B8(fp->cur_pos.x, fp->cur_pos.y,
                                      other_fp->cur_pos.x, other_fp->cur_pos.y,
                                      &coll_vec, &sp10, &spC, &sp14, -1, -1);
            }
            return mpLib_800501CC(fp->cur_pos.x, fp->cur_pos.y,
                                  other_fp->cur_pos.x, other_fp->cur_pos.y,
                                  &coll_vec, &sp10, &spC, &sp14, -1, -1);
        }
    }
}

bool ftCo_800A1C44(ftCo_Fighter* fp)
{
    if (fp->x2219_b1) {
        return true;
    }
    if (fp->x2164 != 0) {
        return true;
    }
    if (fp->x2168 != 0 && fp->x2338.x == 0) {
        return true;
    }
    if (fp->x221F_b3) {
        return true;
    }
    return false;
}

bool ftCo_800A1CA8(ftCo_Fighter* fp)
{
    return fp->x2168 ? true : false;
}

/// #ftCo_800A1CC4

void ftCo_800A1F3C(Fighter* fp, float arg1, float arg2, float arg3)
{
    struct Fighter_x1A88_t* data = (void*) &fp->x1A88;
    if (fp->x1AE8 == 0) {
        data->x54.x = arg1;
        data->x54.y = arg2;
        data->x38 = arg3;
        ftCo_800A1CC4(ftCo_803C6594[stage_info.internal_stage_id],
                      &stage_info.cam_info, data);
    }
}

bool ftCo_800A1F98(int x, float y)
{
    float slope;
    float intercept;
    PAD_STACK(1 * 4);

    if (stage_info.internal_stage_id != ZEBES) {
        return false;
    }
    Ground_801C4368(&slope, &intercept);
    if (y < slope) {
        return true;
    }
    if (y < intercept * x + slope) {
        return true;
    }
    return false;
}

bool ftCo_800A2040(ftCo_Fighter* fp)
{
    if (Player_8003248C(fp->player_id, fp->x221F_b4) != 1) {
        return false;
    }
    if ((signed) fp->x1A94 == 5) {
        return false;
    }
    return true;
}

/// #ftCo_800A20A0

void ftCo_800A20A0(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = (void*) &fp->x1A88;
    PAD_STACK(2 * 4);

    if (fp->x1ACC != NULL && fp->ground_or_air == GA_Ground) {
        ftCo_Fighter* other_fp = data->x44;
        float diff_y, diff_x;
        diff_x = fp->cur_pos.x - other_fp->cur_pos.x;
        diff_y = fp->cur_pos.y - other_fp->cur_pos.y;
        if (sqrtf__Ff(SQ(diff_x) + SQ(diff_y)) <
            2.0f * M2C_FIELD(Fighter_804D64FC, float**, 0x20)[fp->kind])
        {
            data->xF8_b6 = true;
        } else {
            data->xF8_b6 = false;
        }
    } else {
        data->xF8_b6 = false;
    }
}

bool ftCo_800A2170(Fighter* fp0, Fighter* fp1)
{
    if (fp0->ground_or_air == GA_Air) {
        return false;
    }
    if (fp1->ground_or_air == GA_Air) {
        return false;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp0->coll_data.floor.index);
        if (data == NULL) {
            return false;
        }
        if (mpIsland_8005AB54(fp1->coll_data.floor.index) == data) {
            return true;
        }
    }
    return false;
}

bool ftCo_800A21FC(ftCo_Fighter* fp)
{
    Vec3 vec;
    mp_UnkStruct0* data0;
    struct Fighter_x1A88_t* data1 = (void*) &fp->x1A88;
    PAD_STACK(9 * 4);

    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    data0 = mpIsland_8005AB54(fp->coll_data.floor.index);
    if (data0 == NULL) {
        return false;
    }
    vec.x = data1->x54.x;
    vec.y = 5.0 + data1->x54.y;
    vec.z = 0.0f;
    if (mpIsland_8005AC14(&vec, -10.0f) == data0) {
        return true;
    }
    return false;
}

/// #ftCo_800A229C

/// #ftCo_800A2718

bool ftCo_800A28D0(Fighter* fp, f32 arg1)
{
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (data == NULL) {
            return false;
        }
        {
            float x_offset;
            if (fp->facing_dir > 0.0) {
                x_offset = ABS(data->x14 - fp->cur_pos.x);
            } else {
                x_offset = ABS(data->x8 - fp->cur_pos.x);
            }
            if (x_offset < (5.0 * arg1)) {
                return true;
            }
        }
    }
    return false;
}

bool ftCo_800A2998(Fighter* fp, float arg1)
{
    if (fp->ground_or_air == GA_Air) {
        return false;
    }
    {
        mp_UnkStruct0* data = mpIsland_8005AB54(fp->coll_data.floor.index);
        if (data == NULL) {
            return false;
        }
        {
            float diff_x8, diff_x14;
            diff_x14 = ABS(data->x14 - fp->cur_pos.x);
            diff_x8 = ABS(data->x8 - fp->cur_pos.x);
            if (diff_x14 < diff_x8) {
                if (diff_x14 < 5.0 * arg1) {
                    return true;
                }
                return false;
            }
            if (diff_x8 < 5.0 * arg1) {
                return true;
            }
        }
    }
    return false;
}

/// #ftCo_800A2A70

bool ftCo_800A2BD4(ftCo_Fighter* fp)
{
    return fp->facing_dir * (fp->x1ADC - fp->cur_pos.x) >= 0.0 ? true : false;
}

bool ftCo_800A2C08(Fighter* fp)
{
    ftCo_Fighter* other_fp = fp->x1ACC;
    if (other_fp == NULL) {
        return true;
    }
    {
        float pos_x_diff = other_fp->cur_pos.x - fp->cur_pos.x;
        if (ABS(pos_x_diff) < 1.0f) {
            return true;
        }
        if (pos_x_diff * fp->facing_dir >= 0.0) {
            return true;
        }
        return false;
    }
}

/// #ftCo_800A2C80

enum_t ftCo_800A3134(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_DownBoundD:
    case ftCo_MS_DownBoundU:
        return 1;
    case ftCo_MS_DownWaitD:
    case ftCo_MS_DownWaitU:
        return 2;
    default:
        return 0;
    }
}

bool ftCo_IsGrabbing(ftCo_Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_CatchWait) {
        return true;
    }
    if (fp->kind == FTKIND_DONKEY) {
        if (fp->motion_id >= ftDk_MS_ThrowFWait0 &&
            fp->motion_id <= ftDk_MS_ThrowFKneebend)
        {
            return true;
        }
    }
    if (fp->kind == FTKIND_KOOPA || fp->kind == FTKIND_GKOOPS) {
        if (fp->motion_id == ftKp_MS_SpecialSHit0_1) {
            return true;
        }
    }
    if (fp->kind == FTKIND_KIRBY) {
        if (fp->motion_id >= ftKb_MS_SpecialNCapture0 &&
            fp->motion_id <= ftKb_MS_EatTurnAir)
        {
            return true;
        }
    }
    return false;
}

bool ftCo_800A3200(ftCo_Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_CliffCatch:
        return 1;
    case ftCo_MS_CliffWait:
        return 2;
    default:
        return 0;
    }
}

/// #ftCo_800A3234

static inline bool inlineC0(ftCo_Fighter* fp)
{
    if (fp->coll_data.env_flags & MPCOLL_WALL) {
        return true;
    } else {
        return false;
    }
}

bool ftCo_800A3498(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* temp_r4 = (void*) &fp->x1A88;
    if (fp->x1B82_b5) {
        return false;
    }
    if (fp->ground_or_air != GA_Air) {
        return false;
    }
    if (fp->pos_delta.y > 0.0) {
        return false;
    }
    if (inlineC0(fp)) {
        return true;
    }
    if (fp->kind == FTKIND_LUIGI) {
        if (fp->pos_delta.y < 0.0) {
            return true;
        }
    } else if (temp_r4->x54.y >
               temp_r4->x568 + (fp->coll_data.cur_topn.y +
                                fp->coll_data.xA4_ecbCurrCorrect.bottom.y))
    {
        return true;
    }
    return false;
}

/// #ftCo_800A3554

bool ftCo_800A3710(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = &fp->x1A88_t;
    Fighter* other_fp = fp->x1A88_t.x4C;
    if (!fp->x1A88_t.xF9_b7) {
        return false;
    }
    {
        if (other_fp == NULL) {
            return false;
        }
        if (Item_IsGrabbable(M2C_FIELD(data, HSD_GObj**, 4)) == 0) {
            data->x4C = NULL;
            return false;
        }
        if (fp->ground_or_air == GA_Air) {
            return false;
        }
        if (fp->item_gobj != NULL) {
            return false;
        }
        if (!ftCo_800A2170(fp, other_fp)) {
            return false;
        }
        if (ftCo_80094150(fp->gobj, M2C_FIELD(other_fp, HSD_GObj**, 4))) {
            return true;
        }
        return false;
    }
}

bool ftCo_IsAlly(Fighter* fp0, Fighter* fp1)
{
    if (fp0 == NULL) {
        return false;
    }
    if (fp1 == NULL) {
        return false;
    }
    if (fp0->player_id == fp1->player_id) {
        return true;
    }
    if (gm_8016B168()) {
        if (fp0->team == fp1->team) {
            return true;
        }
        return false;
    }
    if (gm_8016B14C()) {
        return false;
    }
    if (fp0->team == fp1->team) {
        return true;
    }
    return false;
}

/// #ftCo_800A3908

/// #ftCo_800A4038

/// #ftCo_800A4768

void ftCo_800A49B4(ftCo_Fighter* fp)
{
    float spC;
    float temp_f2;
    float temp_f3;
    float var_f4;
    f64 temp_f1;
    f64 temp_f1_2;
    f64 temp_f1_3;

    temp_f3 = M2C_FIELD(fp, float*, 0xB4) - M2C_FIELD(fp, float*, 0x1AE0);
    temp_f2 = M2C_FIELD(fp, float*, 0xB0) - M2C_FIELD(fp, float*, 0x1ADC);
    var_f4 = (temp_f2 * temp_f2) + (temp_f3 * temp_f3);
    if (var_f4 > 0.0f) {
        temp_f1 = __frsqrte(var_f4);
        temp_f1_2 =
            0.5 * temp_f1 * -(((f64) var_f4 * (temp_f1 * temp_f1)) - 3.0);
        temp_f1_3 = 0.5 * temp_f1_2 *
                    -(((f64) var_f4 * (temp_f1_2 * temp_f1_2)) - 3.0);
        spC = (float) ((f64) var_f4 *
                       (0.5 * temp_f1_3 *
                        -(((f64) var_f4 * (temp_f1_3 * temp_f1_3)) - 3.0)));
        var_f4 = spC;
    }
    M2C_FIELD((fp + 0x1A88), float*, 0x5C) = var_f4;
}

/// #ftCo_800A4A40

/// #ftCo_800A4BEC

/// #ftCo_800A4E8C

/// #ftCo_800A50D4

static inline bool inlineF0(ftCo_Fighter* fp, ftCo_Fighter* fp1)
{
    float y, x;
    struct Fighter_x1A88_t* data = &fp->x1A88_t;

    y = fp1->cur_pos.y;
    x = fp1->cur_pos.x;
    if (x < Stage_GetBlastZoneLeftOffset() + data->half_width ||
        x > Stage_GetBlastZoneRightOffset() - data->half_width ||
        y < Stage_GetBlastZoneBottomOffset() + data->half_height ||
        y > Stage_GetBlastZoneTopOffset() - data->half_height)
    {
        return true;
    }
    return false;
}

static inline bool inlineF1(ftCo_Fighter* fp)
{
    Fighter_GObj* gobj = fp->gobj;
    if (fp->x221F_b3 || fp->x2224_b2 || ftCo_800A0F00(gobj) ||
        ftLib_8008732C(gobj))
    {
        return true;
    } else {
        return false;
    }
}

ftCo_Fighter* ftCo_800A5294(ftCo_Fighter* fp, int player_id)
{
    PAD_STACK(2 * 4);
    if (fp == NULL) {
        return NULL;
    }
    {
        ftCo_Fighter* cur_fp;
        HSD_GObj* cur;
        for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
            if (fp->gobj != cur) {
                cur_fp = GET_FIGHTER(cur);
                if (!inlineF0(fp, cur_fp)) {
                    if (!inlineF1(cur_fp) && cur_fp->player_id == player_id) {
                        return cur_fp;
                    }
                }
            }
        }
    }
    return NULL;
}

/// #ftCo_800A53DC

ftCo_Fighter* ftCo_800A589C(Fighter* fp)
{
    if (fp == NULL) {
        return NULL;
    }
    {
        ftCo_GObj* cur;
        for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
            if (fp->gobj != cur) {
                ftCo_Fighter* cur_fp = GET_FIGHTER(cur);
                if (fp->player_id == cur_fp->player_id) {
                    if (cur_fp->x221F_b3) {
                        return NULL;
                    }
                    return cur_fp;
                }
            }
        }
    }
    return NULL;
}

bool ftCo_800A5908(ftCo_Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_DeadUpFallHitCameraFlat) {
        return true;
    }
    if (fp->motion_id == ftCo_MS_DeadUpFallIce) {
        return true;
    }
    if (fp->motion_id == ftCo_MS_Turn) {
        return true;
    }
    return false;
}

bool ftCo_800A5944(ftCo_Fighter* fp)
{
    if (fp->motion_id == ftCo_MS_DeadUpFall) {
        return true;
    }
    if (fp->motion_id == ftCo_MS_Wait) {
        return true;
    }
    if (fp->motion_id == ftCo_MS_WalkSlow) {
        return true;
    }
    return false;
}

bool ftCo_800A5980(ftCo_Fighter* fp)
{
    if (fp->motion_id >= ftCo_MS_LandingFallSpecial &&
        fp->motion_id < ftCo_MS_Attack100Start)
    {
        return true;
    }
    if (fp->motion_id - (unsigned) ftCo_MS_Furafura <= 2 ||
        fp->motion_id == ftCo_MS_CatchAttack)
    {
        return true;
    }
    return false;
}

bool ftCo_800A59C0(UNK_T arg0)
{
    if ((u32) (((u8) *M2C_FIELD(arg0, u8**, 0xCC) >> 3U) & 0xF) == 3) {
        return true;
    }
    return false;
}

bool ftCo_800A59E4(Fighter* fp)
{
    if (fp == NULL) {
        return false;
    }
    if (fp->motion_id == ftCo_MS_KneeBend ||
        fp->motion_id - (unsigned) ftCo_MS_RunDirect <= 1 ||
        fp->motion_id - (unsigned) ftCo_MS_Sleep <= 2)
    {
        return true;
    }
    return false;
}

bool ftCo_800A5A28(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_DeadDown:
    case ftCo_MS_DeadUpFall:
    case ftCo_MS_DeadUpFallHitCamera:
    case ftCo_MS_Wait:
    case ftCo_MS_WalkSlow:
    case ftCo_MS_WalkFast:
    case ftCo_MS_TurnRun:
    case ftCo_MS_Dash:
    case ftCo_MS_FallAerialB:
        return true;
    default:
        return false;
    }
}

bool ftCo_800A5A5C(Fighter* fp)
{
    switch (fp->motion_id) {
    case ftCo_MS_DeadLeft:
    case ftCo_MS_DeadRight:
    case ftCo_MS_DeadUpStar:
    case ftCo_MS_DeadUpStarIce:
        return true;
    default:
        return false;
    }
}

bool ftCo_800A5A90(ftCo_Fighter* fp)
{
    if (fp->motion_id >= ftCo_MS_SwordSwing1 &&
        fp->motion_id <= ftCo_MS_StarRodSwingDash)
    {
        return true;
    }
    if (fp->motion_id >= ftCo_MS_LGunShoot &&
        fp->motion_id <= ftCo_MS_ItemScopeAirEndEmpty)
    {
        return true;
    }
    return false;
}

/// #ftCo_800A5ACC

/// #ftCo_800A5CE0

/// #ftCo_800A5F4C

/// #ftCo_800A61D8

/// #ftCo_800A648C

/// #ftCo_800A6700

/// #ftCo_800A6A98

/// #ftCo_800A6D2C

/// #ftCo_800A6FC4

/// #ftCo_800A75DC

/// #ftCo_800A7AAC

/// #ftCo_800A80E4

void ftCo_800A80E4(Fighter* fp)
{
    Fighter* other_fp = fp->x1ACC;
    if (other_fp != NULL && (fp->ground_or_air != GA_Air)) {
        Vec3 vec;
        if (!(ftCo_800A1AB4(fp, other_fp) > 50.0) &&
            ftCo_800A6700(fp, &other_fp->cur_pos, &vec))
        {
            ftCo_800A1F3C(fp, vec.x, vec.y, 5.0F);
        }
    }
}

/// #ftCo_800A8210

/// #ftCo_800A866C

/// #ftCo_800A8940

void ftCo_800A8DE4(Fighter* fp)
{
    struct Fighter_x1A88_t* data = (void*) &fp->x1A88;
    PAD_STACK(0x20);
    if (!fp->x1B82_b2) {
        data->xFA_b2 = true;
        data->x5C = 10000.0f;
        if (fp->facing_dir > 0.0) {
            if (!ftCo_800A4038(fp, true) && !ftCo_800A3908(fp, true)) {
                ftCo_800A4038(fp, false);
            }
        } else if (!ftCo_800A3908(fp, true) && !ftCo_800A4038(fp, true)) {
            ftCo_800A3908(fp, false);
        }
    }
}

/// #ftCo_800A8EB0

/// #ftCo_800A92CC

/// #ftCo_800A949C

void ftCo_800A963C(ftCo_Fighter* fp)
{
    PAD_STACK(4 * 14);
    ftCo_800B46B8(fp, 0x81, 0x58);
    ftCo_800B46B8(fp, 0x90, 0x58);
    ftCo_800B46B8(fp, 0x88, 1);
    ftCo_800B463C(fp, 4);
    ftCo_800B46B8(fp, 0x90, 0x7F);
    ftCo_800B463C(fp, 0x7F);
}

/// #ftCo_800A96B8

/// #ftCo_800A9904

/// #ftCo_800A9CB4

void ftCo_800AA320(ftCo_Fighter* fp, int* arg1, int* arg2)
{
    if (fp->kind == FTKIND_NANA) {
        *arg1 = 0x40;
        *arg2 = 0x7F;
        return;
    }
    switch (fp->x1A98) {
    case 0:
        *arg1 = 1;
        *arg2 = 0x43;
        return;
    case 1:
        *arg1 = 2;
        *arg2 = 0x48;
        return;
    case 2:
        *arg1 = 2;
        *arg2 = 0x4D;
        return;
    case 3:
        *arg1 = 2;
        *arg2 = 0x52;
        return;
    case 4:
        *arg1 = 2;
        *arg2 = 0x57;
        return;
    case 5:
        *arg1 = 2;
        *arg2 = 0x5C;
        return;
    case 6:
        *arg1 = 4;
        *arg2 = 0x61;
        return;
    case 7:
        *arg1 = 4;
        *arg2 = 0x6B;
        return;
    case 8:
        *arg1 = 8;
        *arg2 = 0x75;
        return;
    case 9:
        *arg1 = 8;
        *arg2 = 0x7F;
        return;
    }
}

/// #ftCo_800AA42C

/// #ftCo_800AA844

static inline bool inlineD0(ftCo_Fighter* fp)
{
    if (fp->motion_id == 0xF5 || fp->motion_id == 0xF6) {
        return true;
    }
    return false;
}

void ftCo_800AABC8(ftCo_Fighter* fp)
{
    PAD_STACK(2 * 4);
    if (inlineD0(fp)) {
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x91, 0x7F);
        ftCo_800B46B8(fp, 0x8E, 1);
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B463C(fp, 0x7F);
    } else {
        int a, b;
        ftCo_800AA320(fp, &a, &b);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B4778(fp, 0xC2, a & 0xFF, b & 0xFF);
        ftCo_800B463C(fp, 0x7F);
    }
}

/// #ftCo_800AACD0

/// #ftCo_800AAF48

/// #ftCo_800AB224

/// #ftCo_800ABA34

/// #ftCo_800ABBA8

static inline bool inlineE0(ftCo_Fighter* fp)
{
    enum_t temp_r0 = fp->motion_id;
    bool ret;
    if (temp_r0 == 224) {
        ret = 1;
    } else if (temp_r0 == 227) {
        ret = 1;
    } else if ((temp_r0 >= 266) && (temp_r0 <= 270)) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

void ftCo_800AC30C(Fighter* fp)
{
    struct Fighter_x1A88_t* data = (void*) &fp->x1A88;
    PAD_STACK(4 * 4);
    if (!inlineE0(fp)) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (data->x7C % 3 == 0 && !(data->x10 * 0.1F < HSD_Randf())) {
        if (fp->x1A8C < 0) {
            ftCo_800B46B8(fp, 0x80, 0x7F);
        } else {
            ftCo_800B46B8(fp, 0x80, 0x81);
        }
        ftCo_800B463C(fp, 0x7F);
    }
}

/// #ftCo_800AC434

/// #ftCo_800AC5A0

/// #ftCo_800AC7D4

/// #ftCo_800ACB44

/// #ftCo_800ACD5C

void ftCo_800AD42C(ftCo_Fighter* fp)
{
    struct Fighter_x1A88_t* data = (void*) fp->x1A88;
    if (!ftCo_800A3554(fp, 1.0f)) {
        data->x18 = data->x1C;
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    if (fp->ground_or_air == GA_Air) {
        ftCo_800B46B8(fp, 0x80, 0);
        ftCo_800B46B8(fp, 0x81, 0);
        ftCo_800B463C(fp, 0x7F);
        return;
    }
    ftCo_800B46B8(fp, 0x80, 0);
    ftCo_800B46B8(fp, 0x81, 0);
    ftCo_800B463C(fp, 8);
    ftCo_800B46B8(fp, 0x8E, 1);
    ftCo_800B463C(fp, 7);
    ftCo_800B46B8(fp, 0x8E, p_ftCommonData->x74 + 1);
    ftCo_800B463C(fp, 8);
    ftCo_800B46B8(fp, 0x8E, 5);
    ftCo_800B463C(fp, 0x7F);
}

/// #ftCo_800AD54C

/// #ftCo_800AD7FC

/// #ftCo_800ADC28

/// #ftCo_800ADE48

/// #ftCo_800AE7AC

/// #ftCo_800AEA8C

/// #ftCo_800AECF0

/// #ftCo_800AEFB8

/// #ftCo_800AF290

/// #ftCo_800AF78C

/// #ftCo_800AFC40

/// #ftCo_800AFE3C

/// #ftCo_800B00F8

/// #ftCo_800B04DC

/// #ftCo_800B0760

/// #ftCo_800B0918

/// #ftCo_800B0AF4

/// #ftCo_800B0CA8

/// #ftCo_800B0E98

/// #ftCo_800B101C

/// #ftCo_800B126C

/// #ftCo_800B1478

/// #ftCo_800B17D0

/// #ftCo_800B1AB8

/// #ftCo_800B1DA0

/// #ftCo_800B1EF0

/// #ftCo_800B21C8

/// #ftCo_800B24B8

/// #ftCo_800B2790

/// #ftCo_800B2AFC

/// #ftCo_800B33B0

void ftCo_800B3900(Fighter_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    ftCo_800B33B0(fp);
    ftCo_800B2AFC(fp);
    ftCo_800B2790(fp);
    ftCo_800B3E04(fp);
    ftCo_800B0AF4(fp);
    M2C_FIELD(fp, int*, 0x1B04) = (int) (M2C_FIELD(fp, int*, 0x1B04) + 1);
}

/// #ftCo_800B395C
