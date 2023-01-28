? bar();                                            /* extern */

void test(void) {
    bar();
    do {
        if (1 != 0) {
            bar();
        }
    } while ((1 < 1) < 0);
}
