s32 func_004000F0();                                /* static */
? func_00400108(s32);                               /* static */
extern s32 D_410120;

void test(void) {
    s32 sp1C;

    sp1C = func_004000F0();
    D_410120 = 1;
    func_00400108(sp1C);
}
