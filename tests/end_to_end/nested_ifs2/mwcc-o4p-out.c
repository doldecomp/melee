? foo(?);                                           /* static */

void test(s32 arg0) {
    if (arg0 == 7) {
        foo(1);
        if (arg0 == 8) {
            foo(2);
        }
        foo(3);
        return;
    }
    foo(4);
}
