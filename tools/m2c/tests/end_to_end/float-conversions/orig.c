volatile float flt;
volatile double dbl;
volatile unsigned u;

void test(void) {
    u = (unsigned)flt;
    u = (unsigned)dbl;
    dbl = (double)u;
    flt = (float)u;
}
