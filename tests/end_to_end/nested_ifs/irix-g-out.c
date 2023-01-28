? func_004000FC(?);                                 /* static */

void test(s32 arg0) {
    if (arg0 == 7) {
        func_004000FC(1);
    } else {
        func_004000FC(2);
        if (arg0 == 8) {
            func_004000FC(3);
        }
        func_004000FC(4);
    }
}
