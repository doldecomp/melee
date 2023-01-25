extern s32 glob;

? test(void) {
    s32 temp_cr0_lt;

    temp_cr0_lt = (s32) glob < 1;
    glob -= 1;
    if (temp_cr0_lt != 0) {
        return 4;
    }
    return 6;
}
