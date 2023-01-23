void test(s32 x, s16 *y, s32 z, s8 *r, s16 *s, s32 *t, s32 *u) {
    s32 *var_r3;

    var_r3 = NULL;
loop_1:
    var_r3 = foo(var_r3, y, t);
    goto loop_1;
}
