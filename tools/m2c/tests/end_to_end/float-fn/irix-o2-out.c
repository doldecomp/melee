f32 func_004000BC();                                /* static */
f64 func_004000C4(f64);                             /* static */

f32 test(void) {
    return (f32) func_004000C4((f64) func_004000BC());
}
