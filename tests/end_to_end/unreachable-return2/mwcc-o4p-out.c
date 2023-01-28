extern s32 x;

void test(void) {
loop_1:
    if ((s32) x != 2) {
        x = 1;
        goto loop_1;
    }
}
