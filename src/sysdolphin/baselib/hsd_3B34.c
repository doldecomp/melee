#include "hsd_3B34.h"

/// hsd_803B5C2C
static int lbl_804D6398 = 3;

void fn_803B376C(s32* arg0)
{
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f11_3;
    f32 temp_f11_4;
    f32 temp_f11_5;
    f32 temp_f11_6;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f27_3;
    f32 temp_f27_4;
    f32 temp_f27_5;
    f32 temp_f27_6;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f28_3;
    f32 temp_f28_4;
    f32 temp_f28_5;
    f32 temp_f28_6;
    f32 temp_f28_7;
    f32 temp_f29;
    f32 temp_f29_2;
    f32 temp_f29_3;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f30_3;
    f32 temp_f30_4;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f8;
    f32 temp_f8_2;
    f32 temp_f8_3;
    f32 temp_f8_4;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r12;
    s32 temp_r12_2;
    s32 temp_r29;
    s32 temp_r29_2;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    s32 temp_r31_2;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32* var_r3;
    s32* var_r4;
    s32* var_r4_2;

    var_r3 = arg0;
    var_ctr = 8;
    var_r4 = var_r3;
    do {
        temp_r29 = var_r4[0];
        temp_r30 = var_r4[7];
        temp_r31 = var_r4[1];
        temp_r12 = var_r4[6];
        temp_r11 = var_r4[2];
        temp_r10 = var_r4[5];
        temp_r9 = var_r4[3];
        temp_r7 = var_r4[4];
        temp_f11 = (f32) (temp_r29 + temp_r30);
        temp_f27 = (f32) (temp_r31 + temp_r12);
        temp_f28 = (f32) (temp_r11 + temp_r10);
        temp_f4 = (f32) (temp_r9 + temp_r7);
        temp_f30 = temp_f27 + temp_f28;
        temp_f6 = temp_f11 + temp_f4;
        temp_f26 = temp_f11 - temp_f4;
        temp_f27_2 = temp_f27 - temp_f28;
        temp_f27_3 = (f32) (temp_r9 - temp_r7);
        temp_f8 = (f32) (temp_r11 - temp_r10);
        temp_f11_2 = (f32) (temp_r31 - temp_r12);
        var_r4[0] = (s32) (0.707107L * (f64) (temp_f6 + temp_f30));
        temp_f28_2 = (f32) (temp_r29 - temp_r30);
        var_r4[4] = (s32) (0.707107L * (f64) (temp_f6 - temp_f30));
        var_r4[6] = (s32) ((-0.92388L * (f64) temp_f27_2) +
                           (0.382683L * (f64) temp_f26));
        var_r4[2] = (s32) ((0.382683L * (f64) temp_f27_2) +
                           (0.92388L * (f64) temp_f26));
        temp_f11_3 = (f32) (0.707107L * (f64) (temp_f8 + temp_f11_2));
        temp_f8_2 = (f32) (0.707107L * (f64) (temp_f8 - temp_f11_2));
        temp_f30_2 = temp_f11_3 + temp_f28_2;
        temp_f26_2 = -temp_f27_3 + temp_f8_2;
        temp_f28_3 = -temp_f11_3 + temp_f28_2;
        temp_f27_4 = temp_f27_3 + temp_f8_2;
        var_r4[7] = (s32) ((0.980785L * (f64) temp_f26_2) +
                           (0.19509L * (f64) temp_f30_2));
        var_r4[5] = (s32) ((0.83147L * (f64) temp_f27_4) +
                           (0.55557L * (f64) temp_f28_3));
        var_r4[3] = (s32) ((-0.55557L * (f64) temp_f27_4) +
                           (0.83147L * (f64) temp_f28_3));
        var_r4[1] = (s32) ((-0.19509L * (f64) temp_f26_2) +
                           (0.980785L * (f64) temp_f30_2));
        var_r4 += 8;
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_ctr_2 = 8;
    var_r4_2 = var_r3;
    do {
        temp_r31_2 = var_r4_2[0];
        temp_r30_2 = var_r4_2[56];
        temp_r29_2 = var_r4_2[8];
        temp_r12_2 = var_r4_2[48];
        temp_r11_2 = var_r4_2[16];
        temp_r10_2 = var_r4_2[40];
        temp_r9_2 = var_r4_2[24];
        temp_r7_2 = var_r4_2[32];
        temp_f11_4 = (f32) (temp_r31_2 + temp_r30_2);
        temp_f30_3 = (f32) (temp_r29_2 + temp_r12_2);
        temp_f28_4 = (f32) (temp_r11_2 + temp_r10_2);
        temp_f4_2 = (f32) (temp_r9_2 + temp_r7_2);
        temp_f29 = temp_f30_3 + temp_f28_4;
        temp_f6_2 = temp_f11_4 + temp_f4_2;
        temp_f27_5 = temp_f11_4 - temp_f4_2;
        temp_f28_5 = temp_f30_3 - temp_f28_4;
        temp_f28_6 = (f32) (temp_r9_2 - temp_r7_2);
        temp_f8_3 = (f32) (temp_r11_2 - temp_r10_2);
        temp_f11_5 = (f32) (temp_r29_2 - temp_r12_2);
        var_r4_2[0] = (s32) (0.707107L * (f64) (temp_f6_2 + temp_f29));
        temp_f29_2 = (f32) (temp_r31_2 - temp_r30_2);
        var_r4_2[32] = (s32) (0.707107L * (f64) (temp_f6_2 - temp_f29));
        var_r4_2[48] = (s32) ((-0.92388L * (f64) temp_f28_5) +
                              (0.382683L * (f64) temp_f27_5));
        var_r4_2[16] = (s32) ((0.382683L * (f64) temp_f28_5) +
                              (0.92388L * (f64) temp_f27_5));
        temp_f11_6 = (f32) (0.707107L * (f64) (temp_f8_3 + temp_f11_5));
        temp_f8_4 = (f32) (0.707107L * (f64) (temp_f8_3 - temp_f11_5));
        temp_f30_4 = temp_f11_6 + temp_f29_2;
        temp_f27_6 = -temp_f28_6 + temp_f8_4;
        temp_f29_3 = -temp_f11_6 + temp_f29_2;
        temp_f28_7 = temp_f28_6 + temp_f8_4;
        var_r4_2[56] = (s32) ((0.980785L * (f64) temp_f27_6) +
                              (0.19509L * (f64) temp_f30_4));
        var_r4_2[40] = (s32) ((0.83147L * (f64) temp_f28_7) +
                              (0.55557L * (f64) temp_f29_3));
        var_r4_2[24] = (s32) ((-0.55557L * (f64) temp_f28_7) +
                              (0.83147L * (f64) temp_f29_3));
        var_r4_2[8] = (s32) ((-0.19509L * (f64) temp_f27_6) +
                             (0.980785L * (f64) temp_f30_4));
        var_r4_2 += 1; // It was +4 for a void* which means +1 for s32*
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    var_ctr_3 = 4;
    do {
        var_r3[0] = var_r3[0] >> 2;
        var_r3[1] = var_r3[1] >> 2;
        var_r3[2] = var_r3[2] >> 2;
        var_r3[3] = var_r3[3] >> 2;
        var_r3[4] = var_r3[4] >> 2;
        var_r3[5] = var_r3[5] >> 2;
        var_r3[6] = var_r3[6] >> 2;
        var_r3[7] = var_r3[7] >> 2;
        var_r3[8] = var_r3[8] >> 2;
        var_r3[9] = var_r3[9] >> 2;
        var_r3[10] = var_r3[10] >> 2;
        var_r3[11] = var_r3[11] >> 2;
        var_r3[12] = var_r3[12] >> 2;
        var_r3[13] = var_r3[13] >> 2;
        var_r3[14] = var_r3[14] >> 2;
        var_r3[15] = var_r3[15] >> 2;
        var_r3 += 16;
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
}

void hsd_803B5C2C(int mode)
{
    lbl_804D6398 = mode;
    if ((mode < 1) || (mode > 10)) {
        lbl_804D6398 = 3;
    }
}

void fn_803B61B4(s32* arg0)
{
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f10_3;
    f32 temp_f11;
    f32 temp_f11_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f13_3;
    f32 temp_f13_4;
    f32 temp_f13_5;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f23;
    f32 temp_f23_2;
    f32 temp_f23_3;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f24_3;
    f32 temp_f24_4;
    f32 temp_f25;
    f32 temp_f25_2;
    f32 temp_f25_3;
    f32 temp_f25_4;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f27;
    f32 temp_f27_2;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 temp_f9;
    f32 temp_f9_2;
    f32 temp_f9_3;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r5_5;
    s32 temp_r5_6;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32* var_r3;
    s32* var_r4;
    s32* var_r4_2;

    var_r3 = arg0;
    var_ctr = 8;
    var_r4 = var_r3;
    do {
        temp_r5 = var_r4[1];
        temp_r0 = var_r4[3];
        temp_r6 = var_r4[7];
        temp_r5_2 = var_r4[5];
        temp_r11 = var_r4[0];
        temp_r10 = var_r4[4];
        temp_f22 = (f32) ((0.980785 * (f64) temp_r6) - (0.19509 * (f64) temp_r5));
        temp_f31 = (f32) ((0.83147 * (f64) temp_r5_2) - (0.55557 * (f64) temp_r0));
        temp_f23 = (f32) ((0.55557 * (f64) temp_r5_2) + (0.83147 * (f64) temp_r0));
        temp_f24 = (f32) ((0.19509 * (f64) temp_r6) + (0.980785 * (f64) temp_r5));
        temp_f10 = (f32) (0.707107 * (f64) (temp_r11 + temp_r10));
        temp_f11 = (f32) (0.707107 * (f64) (temp_r11 - temp_r10));
        temp_r0_2 = var_r4[2];
        temp_f12 = temp_f22 + temp_f31;
        temp_r5_3 = var_r4[6];
        temp_f13 = -temp_f23 + temp_f24;
        temp_f13_2 = temp_f23 + temp_f24;
        temp_f12_2 = (f32) ((0.382683 * (f64) temp_r5_3) + (0.92388 * (f64) temp_r0_2));
        temp_f9 = (f32) (0.707107 * (f64) (-temp_f12 + temp_f13));
        temp_f25 = (f32) ((-0.92388 * (f64) temp_r5_3) + (0.382683 * (f64) temp_r0_2));
        temp_f23_2 = temp_f10 + temp_f12_2;
        temp_f22_2 = (f32) (0.707107 * (f64) (temp_f12 + temp_f13));
        temp_f24_2 = temp_f11 + temp_f25;
        temp_f25_2 = temp_f11 - temp_f25;
        var_r4[0] = (s32) (temp_f23_2 + temp_f13_2);
        var_r4[1] = (s32) (temp_f24_2 + temp_f9);
        temp_f13_3 = -temp_f22 + temp_f31;
        temp_f10_2 = temp_f10 - temp_f12_2;
        var_r4[2] = (s32) (temp_f25_2 + temp_f22_2);
        var_r4[3] = (s32) (temp_f10_2 + temp_f13_3);
        var_r4[4] = (s32) (temp_f10_2 - temp_f13_3);
        var_r4[5] = (s32) (temp_f25_2 - temp_f22_2);
        var_r4[6] = (s32) (temp_f24_2 - temp_f9);
        var_r4[7] = (s32) (temp_f23_2 - temp_f13_2);
        var_r4 += 8;
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_ctr_2 = 8;
    var_r4_2 = var_r3;
    do {
        temp_r5_4 = var_r4_2[8];
        temp_r0_3 = var_r4_2[24];
        temp_r6_2 = var_r4_2[56];
        temp_r5_5 = var_r4_2[40];
        temp_r11_2 = var_r4_2[0];
        temp_r10_2 = var_r4_2[32];
        temp_f26 = (f32) ((0.980785 * (f64) temp_r6_2) - (0.19509 * (f64) temp_r5_4));
        temp_f9_2 = (f32) ((0.83147 * (f64) temp_r5_5) - (0.55557 * (f64) temp_r0_3));
        temp_f27 = (f32) ((0.55557 * (f64) temp_r5_5) + (0.83147 * (f64) temp_r0_3));
        temp_f30 = (f32) ((0.19509 * (f64) temp_r6_2) + (0.980785 * (f64) temp_r5_4));
        temp_f10_3 = (f32) (0.707107 * (f64) (temp_r11_2 + temp_r10_2));
        temp_f25_3 = (f32) (0.707107 * (f64) (temp_r11_2 - temp_r10_2));
        temp_r0_4 = var_r4_2[16];
        temp_f13_4 = temp_f26 + temp_f9_2;
        temp_r5_6 = var_r4_2[48];
        temp_f29 = -temp_f27 + temp_f30;
        temp_f11_2 = temp_f27 + temp_f30;
        temp_f26_2 = (f32) ((0.382683 * (f64) temp_r5_6) + (0.92388 * (f64) temp_r0_4));
        temp_f12_3 = (f32) (0.707107 * (f64) (-temp_f13_4 + temp_f29));
        temp_f13_5 = (f32) ((-0.92388 * (f64) temp_r5_6) + (0.382683 * (f64) temp_r0_4));
        temp_f27_2 = temp_f10_3 + temp_f26_2;
        temp_f23_3 = (f32) (0.707107 * (f64) (temp_f13_4 + temp_f29));
        temp_f24_3 = temp_f25_3 + temp_f13_5;
        temp_f25_4 = temp_f25_3 - temp_f13_5;
        var_r4_2[0] = (s32) (temp_f27_2 + temp_f11_2);
        var_r4_2[8] = (s32) (temp_f24_3 + temp_f12_3);
        temp_f9_3 = -temp_f26 + temp_f9_2;
        temp_f24_4 = temp_f10_3 - temp_f26_2;
        var_r4_2[16] = (s32) (temp_f25_4 + temp_f23_3);
        var_r4_2[24] = (s32) (temp_f24_4 + temp_f9_3);
        var_r4_2[32] = (s32) (temp_f24_4 - temp_f9_3);
        var_r4_2[40] = (s32) (temp_f25_4 - temp_f23_3);
        var_r4_2[48] = (s32) (temp_f24_3 - temp_f12_3);
        var_r4_2[56] = (s32) (temp_f27_2 - temp_f11_2);
        var_r4_2 += 1;
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    var_ctr_3 = 4;
    do {
        var_r3[0] = (s32) ((s32) var_r3[0] >> 2);
        var_r3[1] = (s32) ((s32) var_r3[1] >> 2);
        var_r3[2] = (s32) ((s32) var_r3[2] >> 2);
        var_r3[3] = (s32) ((s32) var_r3[3] >> 2);
        var_r3[4] = (s32) ((s32) var_r3[4] >> 2);
        var_r3[5] = (s32) ((s32) var_r3[5] >> 2);
        var_r3[6] = (s32) ((s32) var_r3[6] >> 2);
        var_r3[7] = (s32) ((s32) var_r3[7] >> 2);
        var_r3[8] = (s32) ((s32) var_r3[8] >> 2);
        var_r3[9] = (s32) ((s32) var_r3[9] >> 2);
        var_r3[10] = (s32) ((s32) var_r3[10] >> 2);
        var_r3[11] = (s32) ((s32) var_r3[11] >> 2);
        var_r3[12] = (s32) ((s32) var_r3[12] >> 2);
        var_r3[13] = (s32) ((s32) var_r3[13] >> 2);
        var_r3[14] = (s32) ((s32) var_r3[14] >> 2);
        var_r3[15] = (s32) ((s32) var_r3[15] >> 2);
        var_r3 += 16;
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
}
