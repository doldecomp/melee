void func_00400090(unsigned int a) {

}

// If there are too many cases in a single function, GCC starts putting
// the MULT_HI constants on the stack to reuse them, which m2c won't fold.
//
// `volatile` prevents some optimizations, so GCC can't re-use the result
// of the division to compute the modulo. It's only needed on the 32-bit types?

void test_s8(volatile char c) {
    func_00400090(c / 2);
    func_00400090(c / 3);
    func_00400090(c / 5);
    func_00400090(c / 7);
    func_00400090(c / 10);
    func_00400090(c / 100);
    func_00400090(c / 255);

    func_00400090(c % 2);
    func_00400090(c % 3);
    func_00400090(c % 5);
    func_00400090(c % 7);
    func_00400090(c % 10);
    func_00400090(c % 100);
    func_00400090(c % 255);
}

void test_s16(volatile short h) {
    func_00400090(h / 2);
    func_00400090(h / 3);
    func_00400090(h / 5);
    func_00400090(h / 7);
    func_00400090(h / 10);
    func_00400090(h / 100);
    func_00400090(h / 255);
    func_00400090(h / 360);
    func_00400090(h / 0xFFFE);

    func_00400090(h % 2);
    func_00400090(h % 3);
    func_00400090(h % 5);
    func_00400090(h % 7);
    func_00400090(h % 10);
    func_00400090(h % 100);
    func_00400090(h % 255);
    func_00400090(h % 360);
    func_00400090(h % 0xFFFE);
}

void test_s32_div(volatile int d) {
    func_00400090(d / 1);
    func_00400090(d / 2);
    func_00400090(d / 3);
    func_00400090(d / 4);
    func_00400090(d / 5);
    func_00400090(d / 6);
    func_00400090(d / 7);
    func_00400090(d / 8);
    func_00400090(d / 9);
    func_00400090(d / 10);
    func_00400090(d / 11);
    func_00400090(d / 12);
    func_00400090(d / 13);
    func_00400090(d / 14);
    func_00400090(d / 15);
    func_00400090(d / 16);
    func_00400090(d / 17);
    func_00400090(d / 18);
    func_00400090(d / 19);
    func_00400090(d / 20);
    func_00400090(d / 21);
    func_00400090(d / 22);
    func_00400090(d / 23);
    func_00400090(d / 24);
    func_00400090(d / 25);
    func_00400090(d / 26);
    func_00400090(d / 27);
    func_00400090(d / 28);
    func_00400090(d / 29);
    func_00400090(d / 30);
    func_00400090(d / 31);
    func_00400090(d / 32);
    func_00400090(d / 33);
    func_00400090(d / 100);
    func_00400090(d / 255);
    func_00400090(d / 360);
    func_00400090(d / 1000);
    func_00400090(d / 10000);
    func_00400090(d / 100000);
    func_00400090(d / 1000000);
    func_00400090(d / 10000000);
    func_00400090(d / 100000000);
    func_00400090(d / 0x3FFFFFFE);
    func_00400090(d / 0x3FFFFFFF);
    func_00400090(d / 0x40000000);
    func_00400090(d / 0x40000001);
    func_00400090(d / 0x7FFFFFFD);
    func_00400090(d / 0x7FFFFFFE);
    func_00400090(d / 0x7FFFFFFF);
    func_00400090(d / -0x80000000);
    func_00400090(d / -0x7FFFFFFF);
    func_00400090(d / -0x7FFFFFFE);
    func_00400090(d / -10);
    func_00400090(d / -7);
    func_00400090(d / -5);
    func_00400090(d / -4);
    func_00400090(d / -3);
    func_00400090(d / -2);
    func_00400090(d / -1);
}

void test_s32_mod(volatile int d) {
    func_00400090(d % 1);
    func_00400090(d % 2);
    func_00400090(d % 3);
    func_00400090(d % 4);
    func_00400090(d % 5);
    func_00400090(d % 6);
    func_00400090(d % 7);
    func_00400090(d % 8);
    func_00400090(d % 9);
    func_00400090(d % 10);
    func_00400090(d % 11);
    func_00400090(d % 12);
    func_00400090(d % 13);
    func_00400090(d % 14);
    func_00400090(d % 15);
    func_00400090(d % 16);
    func_00400090(d % 17);
    func_00400090(d % 18);
    func_00400090(d % 19);
    func_00400090(d % 20);
    func_00400090(d % 21);
    func_00400090(d % 22);
    func_00400090(d % 23);
    func_00400090(d % 24);
    func_00400090(d % 25);
    func_00400090(d % 26);
    func_00400090(d % 27);
    func_00400090(d % 28);
    func_00400090(d % 29);
    func_00400090(d % 30);
    func_00400090(d % 31);
    func_00400090(d % 32);
    func_00400090(d % 33);
    func_00400090(d % 100);
    func_00400090(d % 255);
    func_00400090(d % 360);
    func_00400090(d % 1000);
    func_00400090(d % 10000);
    func_00400090(d % 100000);
    func_00400090(d % 1000000);
    func_00400090(d % 10000000);
    func_00400090(d % 100000000);
    func_00400090(d % 0x3FFFFFFE);
    func_00400090(d % 0x3FFFFFFF);
    func_00400090(d % 0x40000000);
    func_00400090(d % 0x40000001);
    func_00400090(d % 0x7FFFFFFD);
    func_00400090(d % 0x7FFFFFFE);
    func_00400090(d % 0x7FFFFFFF);
    func_00400090(d % -0x80000000);
    func_00400090(d % -0x7FFFFFFF);
    func_00400090(d % -0x7FFFFFFE);
    func_00400090(d % -10);
    func_00400090(d % -7);
    func_00400090(d % -5);
    func_00400090(d % -4);
    func_00400090(d % -3);
    func_00400090(d % -2);
    func_00400090(d % -1);
}

void test_u32_div(volatile unsigned int u) {
    func_00400090(u / 1);
    func_00400090(u / 2);
    func_00400090(u / 3);
    func_00400090(u / 4);
    func_00400090(u / 5);
    func_00400090(u / 6);
    func_00400090(u / 7);
    func_00400090(u / 8);
    func_00400090(u / 9);
    func_00400090(u / 10);
    func_00400090(u / 11);
    func_00400090(u / 12);
    func_00400090(u / 13);
    func_00400090(u / 14);
    func_00400090(u / 15);
    func_00400090(u / 16);
    func_00400090(u / 17);
    func_00400090(u / 18);
    func_00400090(u / 19);
    func_00400090(u / 20);
    func_00400090(u / 21);
    func_00400090(u / 22);
    func_00400090(u / 23);
    func_00400090(u / 24);
    func_00400090(u / 25);
    func_00400090(u / 26);
    func_00400090(u / 27);
    func_00400090(u / 28);
    func_00400090(u / 29);
    func_00400090(u / 30);
    func_00400090(u / 31);
    func_00400090(u / 32);
    func_00400090(u / 33);
    func_00400090(u / 100);
    func_00400090(u / 255);
    func_00400090(u / 360);
    func_00400090(u / 1000);
    func_00400090(u / 10000);
    func_00400090(u / 100000);
    func_00400090(u / 1000000);
    func_00400090(u / 10000000);
    func_00400090(u / 100000000);
    func_00400090(u / 0x40000000);
    func_00400090(u / 0x40000001);
    func_00400090(u / 0x7FFFFFFE);
    func_00400090(u / 0x7FFFFFFF);
    func_00400090(u / 0x80000000);
    func_00400090(u / 0x80000001);
    func_00400090(u / 0xFFFFFFFE);
    func_00400090(u / 0xFFFFFFFF);
}

void test_u32_mod(volatile unsigned u) {
    func_00400090(u / 1);
    func_00400090(u / 2);
    func_00400090(u / 3);
    func_00400090(u / 4);
    func_00400090(u / 5);
    func_00400090(u / 6);
    func_00400090(u / 7);
    func_00400090(u / 8);
    func_00400090(u / 9);
    func_00400090(u / 10);
    func_00400090(u / 11);
    func_00400090(u / 12);
    func_00400090(u / 13);
    func_00400090(u / 14);
    func_00400090(u / 15);
    func_00400090(u / 16);
    func_00400090(u / 17);
    func_00400090(u / 18);
    func_00400090(u / 19);
    func_00400090(u / 20);
    func_00400090(u / 21);
    func_00400090(u / 22);
    func_00400090(u / 23);
    func_00400090(u / 24);
    func_00400090(u / 25);
    func_00400090(u / 26);
    func_00400090(u / 27);
    func_00400090(u / 28);
    func_00400090(u / 29);
    func_00400090(u / 30);
    func_00400090(u / 31);
    func_00400090(u / 32);
    func_00400090(u / 33);
    func_00400090(u / 100);
    func_00400090(u / 255);
    func_00400090(u / 360);
    func_00400090(u / 1000);
    func_00400090(u / 10000);
    func_00400090(u / 100000);
    func_00400090(u / 1000000);
    func_00400090(u / 10000000);
    func_00400090(u / 100000000);
    func_00400090(u / 0x40000000);
    func_00400090(u / 0x40000001);
    func_00400090(u / 0x7FFFFFFE);
    func_00400090(u / 0x7FFFFFFF);
    func_00400090(u / 0x80000000);
    func_00400090(u / 0x80000001);
    func_00400090(u / 0xFFFFFFFE);
    func_00400090(u / 0xFFFFFFFF);
}

void test(unsigned int a) {
    test_s8(a);
    test_s16(a);
    test_s32_div(a);
    test_s32_mod(a);
    test_u32_div(a);
    test_u32_mod(a);
}
