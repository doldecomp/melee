f32 test(f32 arg8) {
    f32 sp14;                                       /* compiler-managed */
    f32 spC;
    f32 temp_f2;

    spC = arg8;
    sp14 = spC;
    sp14 = 0x5F3759DF - ((bitwise s32) spC >> 1);
    temp_f2 = (bitwise f32) sp14;
    spC = temp_f2;
    spC = temp_f2 * (1.5f - (temp_f2 * (0.5f * arg8 * temp_f2)));
    return spC;
}
