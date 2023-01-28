void test(s32 x, s16 *y, s32 z, s8 *r, s16 *s, s32 *t, s32 *u) {
    s32 *var_s0;

    var_s0 = NULL;
loop_1:
    var_s0 = foo(var_s0, y, t);
    goto loop_1;
}
