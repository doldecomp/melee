s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (((arg0 != 0) || (arg1 != 0)) && ((arg2 != 0) || (arg3 != 0))) {
        return arg0 + arg1;
    }
    return arg2 + arg3;
}
