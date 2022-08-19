? bar();                                            /* static */
extern s32 foo;

void test(void) {
    bar();
    foo = 4;
}
