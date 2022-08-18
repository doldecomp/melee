? foo(?);                                           /* static */

void test(s32 arg0) {
    if (arg0 == 7) {
        foo(1);
        return;
    }
    foo(2);
    if (arg0 == 8) {
        foo(3);
    }
    foo(4);
}
