f32 test(f32 arg0) {
    f32 spC;                                        /* compiler-managed */
    f32 sp8;
    f32 sp4;                                        /* compiler-managed */
    f32 sp0;

    sp0 = 1.5f;
    sp8 = arg0 * 0.5f;
    sp4 = arg0;
    spC = sp4;
    spC = 0x5F3759DF - ((bitwise s32) spC >> 1);
    sp4 = spC;
    sp4 = (sp0 - (sp8 * (bitwise f32) sp4 * (bitwise f32) sp4)) * (bitwise f32) sp4;
    return sp4;
}
