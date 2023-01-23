s32 foo();                                          /* static */

void test(s32 arg0) {
    s32 var_r3;

    var_r3 = arg0;
loop_1:
    if (var_r3 <= 2) {
        goto loop_1;
    }
    var_r3 = foo();
    goto loop_1;
}
