s32 test(s32 arg0, s32 arg1) {
    s32 spC;
    s32 sp8;

    sp8 = arg0;
    spC = arg1;
    return (s32) (&spC - &sp8) / 4;
}
