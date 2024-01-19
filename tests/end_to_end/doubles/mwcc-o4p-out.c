extern f64 global;

void test(s32 arg0, f64 arg8, f64 arg9) {
    f64 temp_f1;
    f64 var_f1;

    temp_f1 = ((arg8 * (f64) arg0) + (arg8 / arg9)) - 7.0;
    if (((f32) temp_f1 < (f32) arg9) || ((f32) temp_f1 == (f32) arg9) || ((f32) temp_f1 > (bitwise f32) 9.0)) {
        var_f1 = 5.0;
    } else {
        var_f1 = 6.0;
    }
    global = var_f1;
}
