s32 func_004000E4();                                /* static */
? func_004000EC(s32);                               /* static */
extern s32 D_410100;

void test(void) {
    s32 temp_v0;

    temp_v0 = func_004000E4();
    D_410100 = 1;
    func_004000EC(temp_v0);
}
