extern f64 D_400180;
extern s32 D_410190;
extern f32 D_410194;

f32 test(f32 arg0, s32 arg1, f32 arg2, s32 arg3) {
    D_410190 = (s32) arg0;
    D_410194 = (f32) arg1;
    arg2 = (f32) ((f64) arg2 + 5.0);
    arg2 = (f32) ((f64) arg2 + 0.0);
    arg2 += 0.0f;
    arg2 = (f32) ((f64) arg2 + D_400180);
    return (f32) (arg3 + 3) + arg2;
}
