extern s32 glob;

? test(void) {
    s32 temp_r3;

    temp_r3 = glob;
    glob = temp_r3 - 1;
    if (temp_r3 < 1) {
        return 4;
    }
    return 6;
}
