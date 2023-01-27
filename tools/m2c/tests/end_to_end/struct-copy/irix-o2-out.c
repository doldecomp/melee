extern ? D_410150;
extern ? D_4102E0;

void test(s32 arg0, s32 arg1) {
    M2C_MEMCPY_ALIGNED(&D_410150, &D_4102E0, 0x18C);
    *(&D_410150 + 0x18C) = *(&D_4102E0 + 0x18C);
    M2C_MEMCPY_UNALIGNED(arg0, arg1, 0x60);
    *(arg0 + 0x60) = (unaligned s32) *(arg1 + 0x60);
}
