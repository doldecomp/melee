extern s32 D_4100F0;

? test(void) {
    D_4100F0 -= 1;
    if (D_4100F0 < 1) {
        return 4;
    }
    return 6;
}
