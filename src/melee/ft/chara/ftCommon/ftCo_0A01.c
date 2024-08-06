#include <platform.h>
#include "lb/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_0A01.h"

#include "ftCo_0B3E.h"

#include "ft/types.h"
#include "lb/lbcollision.h"
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

extern UNK_T ftCo_803C6594;

#pragma force_active on

/// #ftCo_800A0148

/// #ftCo_800A0384

/// #ftCo_800A0508

/// #ftCo_800A05F4

/// #ftCo_800A0798

/// #ftCo_800A08F0

/// #ftCo_800A0AF4

void ftCo_800A0C8C(ftCo_Fighter* fp)
{
    ftCo_800B463C(fp, 127);
}

/// #ftCo_800A0CB0

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

/// #ftCo_800A0F00

/// #ftCo_800A0FB0

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

/// #ftCo_800A1874

float ftCo_800A1904(ftCo_Fighter* fp)
{
    float ret = fp->x1A90 / 255.0;
    if (ret > 1.0) {
        ret = 1.0;
    }
    return ret;
}

float ftCo_800A1948(ftCo_Fighter* fp)
{
    float result = fp->x1A91 / 255.0;
    if (result > 1.0) {
        result = 1.0;
    }
    return result;
}

HSD_Pad ftCo_800A198C(ftCo_Fighter* fp)
{
    return fp->x1A88;
}

float ftCo_800A1994(Fighter* fp)
{
    s8 x1A8E = fp->x1A8E;
    float ret;
    if (x1A8E > 0) {
        ret = x1A8E / 127.0f;
    } else {
        ret = x1A8E / 128.0f;
    }
    if (ret > +1.0) {
        return +1.0f;
    }
    if (ret < -1.0) {
        return -1.0f;
    }
    return ret;
}

/// #ftCo_800A1A24

/// #ftCo_800A1AB4

/// #ftCo_800A1B38

/// #ftCo_800A1BA8

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

/// #ftCo_800A1F3C

/// #ftCo_800A1F98

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

/// #ftCo_800A2170

/// #ftCo_800A21FC

/// #ftCo_800A229C

/// #ftCo_800A2718

/// #ftCo_800A28D0

/// #ftCo_800A2998

/// #ftCo_800A2A70

bool ftCo_800A2BD4(ftCo_Fighter* fp)
{
    return fp->facing_dir * (fp->x1ADC - fp->cur_pos.x) >= 0.0 ? true : false;
}

/// #ftCo_800A2C08

/// #ftCo_800A2C80

/// #ftCo_800A3134

/// #ftCo_800A3180

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

/// #ftCo_800A3498

/// #ftCo_800A3554

/// #ftCo_800A3710

/// #ftCo_800A3844

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

/// #ftCo_800A5294

/// #ftCo_800A53DC

/// #ftCo_800A589C

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

/// #ftCo_800A8210

/// #ftCo_800A866C

/// #ftCo_800A8940

/// #ftCo_800A8DE4

/// #ftCo_800A8EB0

/// #ftCo_800A92CC

/// #ftCo_800A949C

/// #ftCo_800A963C

/// #ftCo_800A96B8

/// #ftCo_800A9904

/// #ftCo_800A9CB4

/// #ftCo_800AA320

/// #ftCo_800AA42C

/// #ftCo_800AA844

/// #ftCo_800AABC8

/// #ftCo_800AACD0

/// #ftCo_800AAF48

/// #ftCo_800AB224

/// #ftCo_800ABA34

/// #ftCo_800ABBA8

/// #ftCo_800AC30C

/// #ftCo_800AC434

/// #ftCo_800AC5A0

/// #ftCo_800AC7D4

/// #ftCo_800ACB44

/// #ftCo_800ACD5C

/// #ftCo_800AD42C

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
