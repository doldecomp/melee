? foo(s32);                                         /* static */

s32 test(s32 arg0) {
    s32 temp_r31;
    s32 var_r31;

    var_r31 = arg0;
loop_2:
    foo(var_r31);
    temp_r31 = var_r31 * 2;
    if (temp_r31 < 4) {
        foo(temp_r31);
        var_r31 = temp_r31 + 1;
        goto loop_2;
    }
    return temp_r31;
}
