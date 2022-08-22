? foo(s32);                                         /* static */

void test(s32 arg0) {
    foo(arg0 + 1);
    foo(arg0 + 2);
}
