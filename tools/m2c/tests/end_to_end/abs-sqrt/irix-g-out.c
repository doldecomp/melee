f32 test(f32 arg0) {
    f64 sp10;

    sp10 = (f64) sqrtf(fabsf(arg0));
    return (f32) sqrt(fabs(sp10));
}
