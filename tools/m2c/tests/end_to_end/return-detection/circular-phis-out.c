? bar();                                            /* extern */

void test(void) {
    s32 var_v0;

    bar();
    var_v0 = 4;
    do {
        if (1 != 0) {
            bar();
            var_v0 = 5;
        }
    } while ((var_v0 > 1) < 0);
}
