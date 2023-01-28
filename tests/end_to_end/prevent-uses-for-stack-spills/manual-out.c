? bar();                                            /* extern */
s32 foo();                                          /* extern */
extern s32 global;

void test(void) {
    s32 sp0;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = foo();
    sp0 = temp_v0;
    bar();
    global = temp_v0;
    temp_v0_2 = global;
    sp0 = temp_v0_2;
    bar();
    global = temp_v0_2;
}
