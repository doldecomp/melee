extern f32 D_410230;
extern f64 D_410238;
extern u32 D_410240;

void test(void) {
    f32 var_f8;
    f64 var_f18;

    D_410240 = (u32) D_410230;
    D_410240 = (u32) D_410238;
    var_f18 = (f64) D_410240;
    if ((s32) D_410240 < 0) {
        var_f18 += 4294967296.0;
    }
    D_410238 = var_f18;
    var_f8 = (f32) D_410240;
    if ((s32) D_410240 < 0) {
        var_f8 += 4294967296.0f;
    }
    D_410230 = var_f8;
}
