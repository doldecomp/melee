void test(s32 *arg0, s32 *arg1) {
    s32 temp_r3;

    temp_r3 = *arg0;
    if (temp_r3 == 0xF) {
        goto block_5;
    }
    if (temp_r3 >= 0xF) {
        goto block_6;
    }
    if (temp_r3 == 8) {
        goto block_4;
    }
    goto block_6;
block_4:
    *arg1 += temp_r3;
    goto block_6;
block_5:
    *arg1 -= temp_r3;
block_6:
    return;
}
