s32 test(s32 (*arg0)(?, ?), ? arg1) {
    return arg0(arg1, arg0) + 1;
}
