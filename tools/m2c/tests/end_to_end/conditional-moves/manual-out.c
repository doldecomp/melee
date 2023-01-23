s32 test(s32 arg2) {
    s32 temp_a2;

    temp_a2 = (arg2 <= 0) ? 1 : arg2;
    return (temp_a2 < 6) ? temp_a2 : 5;
}
