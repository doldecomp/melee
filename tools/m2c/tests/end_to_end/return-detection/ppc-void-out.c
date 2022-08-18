? foo();                                            /* extern */

void test(s32 arg0) {
    if (arg0 == 0) {
        foo();
    }
}
