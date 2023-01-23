s32 test(s32 arg0, ? arg1) {
    return (s32) (&arg1 - sp) >> 2;
}
