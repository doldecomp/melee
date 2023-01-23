? fun();                                            /* extern */

s32 test(s32 arg0) {
    if (arg0 != 0) {
        fun();
    }
    return 0x10000 | 2;
}
