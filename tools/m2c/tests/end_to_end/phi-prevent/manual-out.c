s32 test(s32 arg0, s32 arg2) {
    s32 temp_v0;
    s32 var_t0;

    var_t0 = arg0 + 1;
    temp_v0 = var_t0;
    if (arg2 != 0) {
        var_t0 = arg0 + 2;
    }
    *NULL = var_t0;
    return temp_v0;
}
