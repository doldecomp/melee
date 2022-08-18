extern f32 D_410230;
extern f64 D_410238;
extern u32 D_410240;

void test(void) {
    f32 var_f8;
    f64 var_f18;
    u32 temp_t0;
    u32 temp_t1;

    D_410240 = (u32) D_410230;
    D_410240 = (u32) D_410238;
    temp_t0 = D_410240;
    var_f18 = (f64) temp_t0;
    if ((s32) temp_t0 < 0) {
        var_f18 += 4294967296.0;
    }
    D_410238 = var_f18;
    temp_t1 = D_410240;
    var_f8 = (f32) temp_t1;
    if ((s32) temp_t1 < 0) {
        var_f8 += 4294967296.0f;
    }
    D_410230 = var_f8;
}
