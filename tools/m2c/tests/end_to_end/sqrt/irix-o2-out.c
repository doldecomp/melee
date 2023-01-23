void test(f32 arg0) {
    f32 spC;                                        /* compiler-managed */
    f32 sp4;                                        /* compiler-managed */

    sp4 = arg0;
    spC = sp4;
    spC = 0x5F3759DF - ((bitwise s32) sp4 >> 1);
    sp4 = spC;
    sp4 = (1.5f - (arg0 * 0.5f * (bitwise f32) spC * (bitwise f32) spC)) * (bitwise f32) spC;
}
