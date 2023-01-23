f32 func_004000DC(f32);                             /* static */
f64 func_004000F4(f64);                             /* static */

f32 test(f32 arg0) {
    arg0 = func_004000DC(arg0);
    arg0 = (f32) func_004000F4((f64) arg0);
    return arg0;
}
