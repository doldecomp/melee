s32 func_0040010C(?);                               /* static */
extern s32 D_410120;

s32 test(void) {
    s32 temp_v0;

    temp_v0 = func_0040010C(1);
    if (temp_v0 != 0) {
        return temp_v0 & 0xFFFF;
    }
    if (D_410120 != 0x7B) {
        return func_0040010C(2);
    }
    return func_0040010C(3);
}
