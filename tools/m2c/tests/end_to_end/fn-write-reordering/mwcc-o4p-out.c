? bar();                                            /* static */
? foo();                                            /* static */
extern s32 global;

void test(void) {
    foo();
    global = 1;
    bar();
}
