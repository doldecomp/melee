extern f64 dbl;
extern f32 flt;
extern u32 u;

void test(void) {
    u = (u32) flt;
    u = (u32) dbl;
    dbl = (f64) u;
    flt = (f32) u;
}
