extern f32 a;
extern f64 b;
extern f64 c;
extern ? *d;
static ? $$25;                                      /* unable to generate initializer: unknown type */

void test(void) {
    a = 1.2f;
    b = 13.0;
    c = 14000000000.0;
    d = &$$25;
}
