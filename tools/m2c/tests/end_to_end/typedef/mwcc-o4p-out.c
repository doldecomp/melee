s32 foo(s32, s32 *);                                /* static */

void test(s32 arg0, s32 *arg1) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r31;

    sp8 = arg0;
    temp_r30 = foo(arg0);
    temp_r31 = foo(arg0, &sp8);
    foo(*arg1, arg1);
}
