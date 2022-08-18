void test(s32 arg0, s32 arg1) {
    s32 sp4;
    s32 temp_t9;

    sp4 = 0;
    if (arg1 > 0) {
        do {
            *(arg0 + sp4) = 0;
            temp_t9 = sp4 + 1;
            sp4 = temp_t9;
        } while (temp_t9 < arg1);
    }
}
