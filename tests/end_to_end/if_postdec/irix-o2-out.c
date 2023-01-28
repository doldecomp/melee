extern s32 D_4100E0;

? test(void) {
    D_4100E0 -= 1;
    if (D_4100E0 <= 0) {
        return 4;
    }
    return 6;
}
