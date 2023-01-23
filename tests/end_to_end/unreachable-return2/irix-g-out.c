extern s32 D_4100F0;

void test(void) {
loop_0:
    if (D_4100F0 != 2) {
        D_4100F0 = 1;
        goto loop_0;
    }
}
