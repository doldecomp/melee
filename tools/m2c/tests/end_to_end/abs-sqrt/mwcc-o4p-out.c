? fabs();                                           /* extern */
? fabsf();                                          /* extern */
f64 sqrt();                                         /* extern */
? sqrtf();                                          /* extern */

f32 test(void) {
    fabsf();
    sqrtf();
    fabs();
    return (f32) sqrt();
}
