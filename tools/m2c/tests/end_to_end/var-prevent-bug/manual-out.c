extern s8 gChar;

void test(void) {
    s8 *var_v0;

    var_v0 = &gChar;
    gChar = 0;
    do {
        var_v0 += 1;
        var_v0->unk-1 = 0;
    } while (0 != 0);
}
