u16 func_0040012C(?);                               /* static */
extern s32 D_410150;

u16 test(void) {
    u16 sp1E;

    sp1E = func_0040012C(1);
    if (sp1E != 0) {
        return sp1E;
    }
    if (D_410150 != 0x7B) {
        return func_0040012C(2);
    }
    return func_0040012C(3);
}
