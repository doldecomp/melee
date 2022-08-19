extern f32 D_410250;
extern f64 D_410258;
extern u32 D_410260;

void test(void) {
    f64 var_f18;
    u32 temp_t0;

    D_410260 = (u32) D_410250;
    D_410260 = (u32) D_410258;
    temp_t0 = D_410260;
    var_f18 = (f64) temp_t0;
    if ((s32) temp_t0 < 0) {
        var_f18 += 4294967296.0;
    }
    D_410258 = var_f18;
    D_410250 = (f32) D_410260;
}
