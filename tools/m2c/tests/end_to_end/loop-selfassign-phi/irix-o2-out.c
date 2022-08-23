s32 func_004000F4(s32);                             /* static */

void test(s32 arg0) {
    s32 var_s0;

    var_s0 = arg0;
loop_1:
    if (var_s0 < 3) {
        goto loop_1;
    }
    var_s0 = func_004000F4(var_s0);
    goto loop_1;
}
