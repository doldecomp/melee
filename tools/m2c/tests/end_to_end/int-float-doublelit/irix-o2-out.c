extern f64 D_400130;
extern s32 D_410140;
extern f32 D_410144;

f32 test(f32 arg0, s32 arg1, f32 arg2, s32 arg3) {
    f32 var_f18;
    s32 temp_a3;

    temp_a3 = arg3 + 3;
    D_410140 = (s32) arg0;
    D_410144 = (f32) arg1;
    var_f18 = (f32) temp_a3;
    if (temp_a3 < 0) {
        var_f18 += 4294967296.0f;
    }
    return var_f18 + (f32) ((f64) (f32) (f64) (f32) ((f64) arg2 + 5.0) + D_400130);
}
