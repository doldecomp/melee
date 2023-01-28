f32 test(s32 arg0) {
    f64 var_ft1;
    f64 var_ft1_2;
    f64 var_ft2;
    f64 var_ft4;
    f64 var_ft5;
    f64 var_fv1;
    s32 temp_a1;
    s32 temp_ft0;
    s32 temp_ft3;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t8;
    s32 var_v0;

    var_fv1 = 0.0;
    var_v0 = arg0;
    if (arg0 != 0) {
        temp_a1 = -(arg0 & 3);
        if (temp_a1 != 0) {
            do {
                var_ft1 = (f64) var_v0;
                if (var_v0 < 0) {
                    var_ft1 += 4294967296.0;
                }
                var_fv1 *= var_ft1;
                var_v0 -= 1;
            } while ((temp_a1 + arg0) != var_v0);
            if (var_v0 != 0) {
                goto loop_6;
            }
        } else {
            do {
loop_6:
                temp_t6 = var_v0 - 1;
                var_ft4 = (f64) var_v0;
                if (var_v0 < 0) {
                    var_ft4 += 4294967296.0;
                }
                temp_t7 = var_v0 - 2;
                temp_t8 = var_v0 - 3;
                var_ft2 = (f64) temp_t6;
                if (temp_t6 < 0) {
                    var_ft2 += 4294967296.0;
                }
                temp_ft3 = temp_t7;
                temp_ft0 = temp_t8;
                var_v0 -= 4;
                var_ft5 = (f64) temp_ft3;
                if (temp_t7 < 0) {
                    var_ft5 += 4294967296.0;
                }
                var_ft1_2 = (f64) temp_ft0;
                if (temp_t8 < 0) {
                    var_ft1_2 += 4294967296.0;
                }
                var_fv1 = var_fv1 * var_ft4 * var_ft2 * var_ft5 * var_ft1_2;
            } while (var_v0 != 0);
        }
    }
    return (f32) var_fv1;
}
