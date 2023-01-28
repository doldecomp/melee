void test(s32 *arg0, s32 *arg1) {
    s32 temp_v1;

    temp_v1 = *arg0;
    if (temp_v1 == 8) {
        goto block_3;
    }
    if (temp_v1 == 0xF) {
        goto block_4;
    }
    return;
block_3:
    *arg1 += temp_v1;
    return;
block_4:
    *arg1 -= temp_v1;
    return;
}
