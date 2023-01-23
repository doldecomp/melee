extern s32 glob;

s32 test(s32 arg0, s32 arg1) {
    s32 temp_r3;
    s32 temp_r3_2;
    s32 var_r3;
    s32 var_r4;

    var_r3 = arg0;
    var_r4 = arg1;
loop_2:
    if (var_r3 == 5) {
        glob = var_r3;
        var_r4 = var_r3 + 3;
        glob = var_r3 + 1;
        temp_r3 = var_r3 + 4;
        glob = var_r3 + 2;
        glob = var_r4;
        glob = temp_r3;
        temp_r3_2 = temp_r3 + 1;
        glob = temp_r3;
        glob = temp_r3_2;
        var_r3 = temp_r3_2 + 1;
        glob = var_r4;
        goto loop_2;
    }
    return var_r4;
}
