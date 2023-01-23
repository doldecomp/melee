s32 test(void) {
    s32 var_a0;

    var_a0 = *(s32 *)0x8009A600 == 3;
    if (*(s8 *)0x800B0F15 == 5) {
        var_a0 = 1;
    }
    return var_a0;
}
