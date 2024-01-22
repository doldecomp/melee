void foo(unsigned int a);

// If there are too many cases in a single function, GCC starts putting
// the MULT_HI constants on the stack to reuse them, which m2c won't fold.
//
// `volatile` prevents some optimizations, so GCC can't re-use the result
// of the division to compute the modulo. It's only needed on the 32-bit types?

void test_s8(volatile char c) {
    foo(c / 2);
    foo(c / 3);
    foo(c / 5);
    foo(c / 7);
    foo(c / 10);
    foo(c / 100);
    foo(c / 255);

    foo(c % 2);
    foo(c % 3);
    foo(c % 5);
    foo(c % 7);
    foo(c % 10);
    foo(c % 100);
    foo(c % 255);
}

void test_s16(volatile short h) {
    foo(h / 2);
    foo(h / 3);
    foo(h / 5);
    foo(h / 7);
    foo(h / 10);
    foo(h / 100);
    foo(h / 255);
    foo(h / 360);
    foo(h / 0xFFFE);

    foo(h % 2);
    foo(h % 3);
    foo(h % 5);
    foo(h % 7);
    foo(h % 10);
    foo(h % 100);
    foo(h % 255);
    foo(h % 360);
    foo(h % 0xFFFE);
}

void test_s32_div(volatile int d) {
    foo(d / 1);
    foo(d / 2);
    foo(d / 3);
    foo(d / 4);
    foo(d / 5);
    foo(d / 6);
    foo(d / 7);
    foo(d / 8);
    foo(d / 9);
    foo(d / 10);
    foo(d / 11);
    foo(d / 12);
    foo(d / 13);
    foo(d / 14);
    foo(d / 15);
    foo(d / 16);
    foo(d / 17);
    foo(d / 18);
    foo(d / 19);
    foo(d / 20);
    foo(d / 21);
    foo(d / 22);
    foo(d / 23);
    foo(d / 24);
    foo(d / 25);
    foo(d / 26);
    foo(d / 27);
    foo(d / 28);
    foo(d / 29);
    foo(d / 30);
    foo(d / 31);
    foo(d / 32);
    foo(d / 33);
    foo(d / 100);
    foo(d / 255);
    foo(d / 360);
    foo(d / 1000);
    foo(d / 10000);
    foo(d / 100000);
    foo(d / 1000000);
    foo(d / 10000000);
    foo(d / 100000000);
    foo(d / 0x3FFFFFFE);
    foo(d / 0x3FFFFFFF);
    foo(d / 0x40000000);
    foo(d / 0x40000001);
    foo(d / 0x7FFFFFFD);
    foo(d / 0x7FFFFFFE);
    foo(d / 0x7FFFFFFF);
    foo(d / -0x80000000);
    foo(d / -0x7FFFFFFF);
    foo(d / -0x7FFFFFFE);
    foo(d / -10);
    foo(d / -7);
    foo(d / -5);
    foo(d / -4);
    foo(d / -3);
    foo(d / -2);
    foo(d / -1);
}

void test_s32_mod(volatile int d) {
    foo(d % 1);
    foo(d % 2);
    foo(d % 3);
    foo(d % 4);
    foo(d % 5);
    foo(d % 6);
    foo(d % 7);
    foo(d % 8);
    foo(d % 9);
    foo(d % 10);
    foo(d % 11);
    foo(d % 12);
    foo(d % 13);
    foo(d % 14);
    foo(d % 15);
    foo(d % 16);
    foo(d % 17);
    foo(d % 18);
    foo(d % 19);
    foo(d % 20);
    foo(d % 21);
    foo(d % 22);
    foo(d % 23);
    foo(d % 24);
    foo(d % 25);
    foo(d % 26);
    foo(d % 27);
    foo(d % 28);
    foo(d % 29);
    foo(d % 30);
    foo(d % 31);
    foo(d % 32);
    foo(d % 33);
    foo(d % 100);
    foo(d % 255);
    foo(d % 360);
    foo(d % 1000);
    foo(d % 10000);
    foo(d % 100000);
    foo(d % 1000000);
    foo(d % 10000000);
    foo(d % 100000000);
    foo(d % 0x3FFFFFFE);
    foo(d % 0x3FFFFFFF);
    foo(d % 0x40000000);
    foo(d % 0x40000001);
    foo(d % 0x7FFFFFFD);
    foo(d % 0x7FFFFFFE);
    foo(d % 0x7FFFFFFF);
    foo(d % -0x80000000);
    foo(d % -0x7FFFFFFF);
    foo(d % -0x7FFFFFFE);
    foo(d % -10);
    foo(d % -7);
    foo(d % -5);
    foo(d % -4);
    foo(d % -3);
    foo(d % -2);
    foo(d % -1);
}

void test_u32_div(volatile unsigned int u) {
    foo(u / 1);
    foo(u / 2);
    foo(u / 3);
    foo(u / 4);
    foo(u / 5);
    foo(u / 6);
    foo(u / 7);
    foo(u / 8);
    foo(u / 9);
    foo(u / 10);
    foo(u / 11);
    foo(u / 12);
    foo(u / 13);
    foo(u / 14);
    foo(u / 15);
    foo(u / 16);
    foo(u / 17);
    foo(u / 18);
    foo(u / 19);
    foo(u / 20);
    foo(u / 21);
    foo(u / 22);
    foo(u / 23);
    foo(u / 24);
    foo(u / 25);
    foo(u / 26);
    foo(u / 27);
    foo(u / 28);
    foo(u / 29);
    foo(u / 30);
    foo(u / 31);
    foo(u / 32);
    foo(u / 33);
    foo(u / 100);
    foo(u / 255);
    foo(u / 360);
    foo(u / 1000);
    foo(u / 10000);
    foo(u / 100000);
    foo(u / 1000000);
    foo(u / 10000000);
    foo(u / 100000000);
    foo(u / 0x40000000);
    foo(u / 0x40000001);
    foo(u / 0x7FFFFFFE);
    foo(u / 0x7FFFFFFF);
    foo(u / 0x80000000);
    foo(u / 0x80000001);
    foo(u / 0xFFFFFFFE);
    foo(u / 0xFFFFFFFF);
}

void test_u32_mod(volatile unsigned u) {
    foo(u % 1);
    foo(u % 2);
    foo(u % 3);
    foo(u % 4);
    foo(u % 5);
    foo(u % 6);
    foo(u % 7);
    foo(u % 8);
    foo(u % 9);
    foo(u % 10);
    foo(u % 11);
    foo(u % 12);
    foo(u % 13);
    foo(u % 14);
    foo(u % 15);
    foo(u % 16);
    foo(u % 17);
    foo(u % 18);
    foo(u % 19);
    foo(u % 20);
    foo(u % 21);
    foo(u % 22);
    foo(u % 23);
    foo(u % 24);
    foo(u % 25);
    foo(u % 26);
    foo(u % 27);
    foo(u % 28);
    foo(u % 29);
    foo(u % 30);
    foo(u % 31);
    foo(u % 32);
    foo(u % 33);
    foo(u % 100);
    foo(u % 255);
    foo(u % 360);
    foo(u % 1000);
    foo(u % 10000);
    foo(u % 100000);
    foo(u % 1000000);
    foo(u % 10000000);
    foo(u % 100000000);
    foo(u % 0x40000000);
    foo(u % 0x40000001);
    foo(u % 0x7FFFFFFE);
    foo(u % 0x7FFFFFFF);
    foo(u % 0x80000000);
    foo(u % 0x80000001);
    foo(u % 0xFFFFFFFE);
    foo(u % 0xFFFFFFFF);
}

void test(unsigned int a) {
    test_s8(a);
    test_s16(a);
    test_s32_div(a);
    test_s32_mod(a);
    test_u32_div(a);
    test_u32_mod(a);
}
