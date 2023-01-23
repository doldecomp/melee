s32 test(s32 arg0, s32 arg1) {
    s32 sp4;

    sp4 = 0;
    return (s32) (&arg1 - &arg0) >> 2;
}
