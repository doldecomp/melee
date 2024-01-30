#include <platform.h>
#include "lb/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_0A01.h"

#include "ftCo_0B3E.h"

#include "ft/types.h"
#include "lb/lbcollision.h"
#include "pl/player.h"

#include <math.h>
#include <placeholder.h>
#include <MetroTRK/intrinsics.h>

/* 09D044 */ static UNK_RET ftCo_800A0148(UNK_PARAMS);
/* 09D06C */ static UNK_RET ftCo_800AC7D4(UNK_PARAMS);
/* 09D280 */ static UNK_RET ftCo_800A0384(UNK_PARAMS);
/* 09D3DC */ static UNK_RET ftCo_800ACB44(UNK_PARAMS);
/* 09D404 */ static UNK_RET ftCo_800A0508(UNK_PARAMS);
/* 09D5F4 */ static UNK_RET ftCo_800ACD5C(UNK_PARAMS);
/* 09D7EC */ static UNK_RET ftCo_800A08F0(UNK_PARAMS);
/* 09D9F0 */ static UNK_RET ftCo_800A0AF4(UNK_PARAMS);
/* 09DBAC */ static UNK_RET ftCo_800A0CB0(UNK_PARAMS);
/* 09DCC4 */ static UNK_RET ftCo_800AD42C(UNK_PARAMS);
/* 09DDE4 */ static UNK_RET ftCo_800AD54C(UNK_PARAMS);
/* 09DDFC */ static UNK_RET ftCo_800A0F00(UNK_PARAMS);
/* 09E094 */ static UNK_RET ftCo_800AD7FC(UNK_PARAMS);
/* 09E4C0 */ static UNK_RET ftCo_800ADC28(UNK_PARAMS);
/* 09E6E0 */ static UNK_RET ftCo_800ADE48(UNK_PARAMS);
/* 09EBC0 */ static UNK_RET ftCo_800A1CC4(UNK_PARAMS);
/* 09EE38 */ static UNK_RET ftCo_800A1F3C(UNK_PARAMS);
/* 09EE94 */ static UNK_RET ftCo_800A1F98(UNK_PARAMS);
/* 09EF9C */ static UNK_RET ftCo_800A20A0(UNK_PARAMS);
/* 09F044 */ static UNK_RET ftCo_800AE7AC(UNK_PARAMS);
/* 09F0F8 */ static UNK_RET ftCo_800A21FC(UNK_PARAMS);
/* 09F198 */ static UNK_RET ftCo_800A229C(UNK_PARAMS);
/* 09F324 */ static UNK_RET ftCo_800AEA8C(UNK_PARAMS);
/* 09F588 */ static UNK_RET ftCo_800AECF0(UNK_PARAMS);
/* 09F614 */ static UNK_RET ftCo_800A2718(UNK_PARAMS);
/* 09F850 */ static UNK_RET ftCo_800AEFB8(UNK_PARAMS);
/* 09FB28 */ static UNK_RET ftCo_800AF290(UNK_PARAMS);
/* 09FB7C */ static UNK_RET ftCo_800A2C80(UNK_PARAMS);
/* 0A0024 */ static UNK_RET ftCo_800AF78C(UNK_PARAMS);
/* 0A0130 */ static UNK_RET ftCo_800A3234(UNK_PARAMS);
/* 0A0394 */ static UNK_RET ftCo_800A3498(UNK_PARAMS);
/* 0A0450 */ static UNK_RET ftCo_800A3554(UNK_PARAMS);
/* 0A04D8 */ static UNK_RET ftCo_800AFC40(UNK_PARAMS);
/* 0A060C */ static UNK_RET ftCo_800A3710(UNK_PARAMS);
/* 0A06D4 */ static UNK_RET ftCo_800AFE3C(UNK_PARAMS);
/* 0A0804 */ static UNK_RET ftCo_800A3908(UNK_PARAMS);
/* 0A0990 */ static UNK_RET ftCo_800B00F8(UNK_PARAMS);
/* 0A0D74 */ static UNK_RET ftCo_800B04DC(UNK_PARAMS);
/* 0A0F34 */ static UNK_RET ftCo_800A4038(UNK_PARAMS);
/* 0A0FF8 */ static UNK_RET ftCo_800B0760(UNK_PARAMS);
/* 0A11B0 */ static UNK_RET ftCo_800B0918(UNK_PARAMS);
/* 0A138C */ static void ftCo_800B0AF4(ftCo_Fighter* fp);
/* 0A1540 */ static UNK_RET ftCo_800B0CA8(UNK_PARAMS);
/* 0A1664 */ static UNK_RET ftCo_800A4768(UNK_PARAMS);
/* 0A1730 */ static UNK_RET ftCo_800B0E98(UNK_PARAMS);
/* 0A18B0 */ static void ftCo_800A49B4(ftCo_Fighter* fp);
/* 0A18B4 */ static UNK_RET ftCo_800B101C(UNK_PARAMS);
/* 0A1AE8 */ static UNK_RET ftCo_800A4BEC(UNK_PARAMS);
/* 0A1B04 */ static UNK_RET ftCo_800B126C(UNK_PARAMS);
/* 0A1B38 */ static UNK_RET ftCo_800A1B38(UNK_PARAMS);
/* 0A1D10 */ static UNK_RET ftCo_800B1478(UNK_PARAMS);
/* 0A1FD0 */ static UNK_RET ftCo_800A50D4(UNK_PARAMS);
/* 0A2068 */ static UNK_RET ftCo_800B17D0(UNK_PARAMS);
/* 0A2190 */ static UNK_RET ftCo_800A5294(UNK_PARAMS);
/* 0A22D8 */ static UNK_RET ftCo_800A53DC(UNK_PARAMS);
/* 0A2350 */ static UNK_RET ftCo_800B1AB8(UNK_PARAMS);
/* 0A2638 */ static UNK_RET ftCo_800B1DA0(UNK_PARAMS);
/* 0A2788 */ static UNK_RET ftCo_800B1EF0(UNK_PARAMS);
/* 0A2798 */ static UNK_RET ftCo_800A589C(UNK_PARAMS);
/* 0A2840 */ static UNK_RET ftCo_800A5944(UNK_PARAMS);
/* 0A2A60 */ static UNK_RET ftCo_800B21C8(UNK_PARAMS);
/* 0A2D50 */ static UNK_RET ftCo_800B24B8(UNK_PARAMS);
/* 0A3028 */ static void ftCo_800B2790(ftCo_Fighter* fp);
/* 0A3C48 */ static void ftCo_800B33B0(ftCo_Fighter* fp);
/* 0A5ACC */ static UNK_RET ftCo_800A5ACC(UNK_PARAMS);
/* 0A5CE0 */ static UNK_RET ftCo_800A5CE0(UNK_PARAMS);
/* 0A5F4C */ static UNK_RET ftCo_800A5F4C(UNK_PARAMS);
/* 0A61D8 */ static UNK_RET ftCo_800A61D8(UNK_PARAMS);
/* 0A648C */ static UNK_RET ftCo_800A648C(UNK_PARAMS);
/* 0A6700 */ static UNK_RET ftCo_800A6700(UNK_PARAMS);
/* 0A6A98 */ static UNK_RET ftCo_800A6A98(UNK_PARAMS);
/* 0A6D2C */ static UNK_RET ftCo_800A6D2C(UNK_PARAMS);
/* 0A6FC4 */ static UNK_RET ftCo_800A6FC4(UNK_PARAMS);
/* 0A75DC */ static UNK_RET ftCo_800A75DC(UNK_PARAMS);
/* 0A7AAC */ static UNK_RET ftCo_800A7AAC(UNK_PARAMS);
/* 0A80E4 */ static UNK_RET ftCo_800A80E4(UNK_PARAMS);
/* 0A8210 */ static UNK_RET ftCo_800A8210(UNK_PARAMS);
/* 0A866C */ static UNK_RET ftCo_800A866C(UNK_PARAMS);
/* 0A8940 */ static UNK_RET ftCo_800A8940(UNK_PARAMS);
/* 0A8DE4 */ static UNK_RET ftCo_800A8DE4(UNK_PARAMS);
/* 0A8EB0 */ static UNK_RET ftCo_800A8EB0(UNK_PARAMS);
/* 0A92CC */ static UNK_RET ftCo_800A92CC(UNK_PARAMS);
/* 0A949C */ static UNK_RET ftCo_800A949C(UNK_PARAMS);
/* 0A963C */ static UNK_RET ftCo_800A963C(UNK_PARAMS);
/* 0A96B8 */ static UNK_RET ftCo_800A96B8(UNK_PARAMS);
/* 0A9904 */ static UNK_RET ftCo_800A9904(UNK_PARAMS);
/* 0A9CB4 */ static UNK_RET ftCo_800A9CB4(UNK_PARAMS);
/* 0AA320 */ static UNK_RET ftCo_800AA320(UNK_PARAMS);
/* 0AA42C */ static UNK_RET ftCo_800AA42C(UNK_PARAMS);
/* 0AA844 */ static UNK_RET ftCo_800AA844(UNK_PARAMS);
/* 0AABC8 */ static UNK_RET ftCo_800AABC8(UNK_PARAMS);
/* 0AACD0 */ static UNK_RET ftCo_800AACD0(UNK_PARAMS);
/* 0AAF48 */ static UNK_RET ftCo_800AAF48(UNK_PARAMS);
/* 0AB224 */ static UNK_RET ftCo_800AB224(UNK_PARAMS);
/* 0ABA34 */ static UNK_RET ftCo_800ABA34(UNK_PARAMS);
/* 0ABBA8 */ static UNK_RET ftCo_800ABBA8(UNK_PARAMS);
/* 0AC30C */ static UNK_RET ftCo_800AC30C(UNK_PARAMS);
/* 0AC434 */ static UNK_RET ftCo_800AC434(UNK_PARAMS);
/* 0AC5A0 */ static UNK_RET ftCo_800AC5A0(UNK_PARAMS);
/* 0B2AFC */ static void ftCo_800B2AFC(ftCo_Fighter* fp);

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

UNK_RET ftCo_800A0148(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A0384(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A0508(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A05F4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A0798(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A08F0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A0AF4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800A0C8C(UNK_T arg0)
{
    ftCo_800B463C(arg0, 127);
}

UNK_RET ftCo_800A0CB0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
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
    while (var_r30 < (int) fp->x119E_hurtboxNum) {
        hurt = var_r31->x11A0_fighterHurtbox;
        lbColl_800083C4(hurt);
        temp_f5 = fp->cur_pos.x;
        temp_f4 = hurt->a_pos.x - temp_f5;
        temp_f3 = hurt->scl * fp->x34_scale.y;
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

UNK_RET ftCo_800A0F00(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A0FB0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800A101C(Fighter* fp, s8 arg1, s8 arg2, s32 arg3)
{
    NOT_IMPLEMENTED;
}

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

float ftCo_800A1874(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}

float ftCo_800A1904(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
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

float ftCo_800A1994(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}

float ftCo_800A1A24(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A1AB4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A1B38(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A1BA8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
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

UNK_RET ftCo_800A1CC4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A1F3C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A1F98(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
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

UNK_RET ftCo_800A20A0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A2170(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A21FC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A229C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A2718(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A28D0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A2998(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A2A70(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

bool ftCo_800A2BD4(ftCo_Fighter* fp)
{
    return fp->facing_dir * (fp->x1ADC - fp->cur_pos.x) >= 0.0 ? true : false;
}

UNK_RET ftCo_800A2C08(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A2C80(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A3134(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A3180(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
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

UNK_RET ftCo_800A3234(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A3498(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A3554(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A3710(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A3844(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A3908(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A4038(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A4768(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

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

UNK_RET ftCo_800A4A40(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A4BEC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A4E8C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A50D4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5294(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A53DC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A589C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5908(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5944(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5980(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

bool ftCo_800A59C0(UNK_T arg0)
{
    if ((u32) (((u8) *M2C_FIELD(arg0, u8**, 0xCC) >> 3U) & 0xF) == 3) {
        return true;
    }
    return false;
}

bool ftCo_800A59E4(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5A28(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5A5C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5A90(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5ACC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5CE0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A5F4C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A61D8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A648C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A6700(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A6A98(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A6D2C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A6FC4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A75DC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A7AAC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A80E4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A8210(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A866C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A8940(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A8DE4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A8EB0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A92CC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A949C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A963C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A96B8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A9904(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800A9CB4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AA320(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AA42C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AA844(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AABC8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AACD0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AAF48(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AB224(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800ABA34(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800ABBA8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AC30C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AC434(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AC5A0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AC7D4(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800ACB44(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800ACD5C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AD42C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AD54C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AD7FC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800ADC28(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800ADE48(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AE7AC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AEA8C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AECF0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AEFB8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AF290(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AF78C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AFC40(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800AFE3C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B00F8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B04DC(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B0760(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B0918(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800B0AF4(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B0CA8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B0E98(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B101C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B126C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B1478(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B17D0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B1AB8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B1DA0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B1EF0(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B21C8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

UNK_RET ftCo_800B24B8(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}

void ftCo_800B2790(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ftCo_800B2AFC(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}

void ftCo_800B33B0(ftCo_Fighter* fp)
{
    NOT_IMPLEMENTED;
}

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

UNK_RET ftCo_800B395C(UNK_PARAMS)
{
    NOT_IMPLEMENTED;
}
