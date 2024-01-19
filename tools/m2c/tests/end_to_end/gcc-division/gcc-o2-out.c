void func_00400098(s8 arg0);                        /* static */
void func_004003A8(s16 arg0);                       /* static */
void func_004007C0(u32 arg0);                       /* static */
void func_00400F48(u32 arg0);                       /* static */
void func_00401AA0(u32 arg0);                       /* static */
void func_00401FC4(u32 arg0);                       /* static */

void test(u32 a) {
    func_00400098((s8) a);
    func_004003A8((s16) a);
    func_004007C0(a);
    func_00400F48(a);
    func_00401AA0(a);
    func_00401FC4(a);
}

void func_00400098(s8 arg0) {
    foo((u32) ((s32) ((s8) subroutine_arg4 + ((u32) (subroutine_arg4 << 0x18) >> 0x1F)) >> 1), /* extra? */ arg0);
    foo((u32) (s8) (subroutine_arg4 / 3));
    foo((u32) (s8) (subroutine_arg4 / 5));
    foo((u32) (s8) (subroutine_arg4 / 7));
    foo((u32) (s8) (subroutine_arg4 / 10));
    foo((u32) (s8) (subroutine_arg4 / 100));
    foo(subroutine_arg4 / 255);
    foo((u32) (s8) ((s8) subroutine_arg4 - (((s32) ((s8) subroutine_arg4 + ((u32) (subroutine_arg4 << 0x18) >> 0x1F)) >> 1) * 2)));
    foo((u32) (s8) (subroutine_arg4 % 3));
    foo((u32) (s8) (subroutine_arg4 % 5));
    foo((u32) (s8) (subroutine_arg4 % 7));
    foo((u32) (s8) (subroutine_arg4 % 10));
    foo((u32) (s8) (subroutine_arg4 % 100));
    foo(subroutine_arg4 % 255);
}

void func_004003A8(s16 arg0) {
    foo((u32) ((s32) ((s16) subroutine_arg4 + ((u32) (subroutine_arg4 << 0x10) >> 0x1F)) >> 1), /* extra? */ arg0);
    foo((u32) (s16) (subroutine_arg4 / 3));
    foo((u32) (s16) (subroutine_arg4 / 5));
    foo((u32) (s16) (subroutine_arg4 / 7));
    foo((u32) (s16) (subroutine_arg4 / 10));
    foo((u32) (s16) (subroutine_arg4 / 100));
    foo((u32) (s16) (subroutine_arg4 / 255));
    foo((u32) (s16) (subroutine_arg4 / 360));
    foo(subroutine_arg4 / 65534);
    foo((u32) (s16) ((s16) subroutine_arg4 - (((s32) ((s16) subroutine_arg4 + ((u32) (subroutine_arg4 << 0x10) >> 0x1F)) >> 1) * 2)));
    foo((u32) (s16) (subroutine_arg4 % 3));
    foo((u32) (s16) (subroutine_arg4 % 5));
    foo((u32) (s16) (subroutine_arg4 % 7));
    foo((u32) (s16) (subroutine_arg4 % 10));
    foo((u32) (s16) (subroutine_arg4 % 100));
    foo((u32) (s16) (subroutine_arg4 % 255));
    foo((u32) (s16) (subroutine_arg4 % 360));
    foo(subroutine_arg4 % 65534);
}

void func_004007C0(u32 arg0) {
    u32 var_a0;
    u32 var_a0_2;
    u32 var_a0_3;
    u32 var_a0_4;
    u32 var_a0_5;
    u32 var_a0_6;

    foo(arg0);
    foo((u32) ((s32) (arg0 + (arg0 >> 0x1F)) >> 1));
    foo(arg0 / 3);
    var_a0 = arg0;
    if ((s32) var_a0 < 0) {
        var_a0 += 3;
    }
    foo((u32) ((s32) var_a0 >> 2));
    foo(arg0 / 5);
    foo(arg0 / 6);
    foo(arg0 / 7);
    var_a0_2 = arg0;
    if ((s32) var_a0_2 < 0) {
        var_a0_2 += 7;
    }
    foo((u32) ((s32) var_a0_2 >> 3));
    foo(arg0 / 9);
    foo(arg0 / 10);
    foo(arg0 / 11);
    foo(arg0 / 12);
    foo(arg0 / 13);
    foo(arg0 / 14);
    foo(arg0 / 15);
    var_a0_3 = arg0;
    if ((s32) var_a0_3 < 0) {
        var_a0_3 += 0xF;
    }
    foo((u32) ((s32) var_a0_3 >> 4));
    foo(arg0 / 17);
    foo(arg0 / 18);
    foo(arg0 / 19);
    foo(arg0 / 20);
    foo(arg0 / 21);
    foo(arg0 / 22);
    foo(arg0 / 23);
    foo(arg0 / 24);
    foo(arg0 / 25);
    foo(arg0 / 26);
    foo(arg0 / 27);
    foo(arg0 / 28);
    foo(arg0 / 29);
    foo(arg0 / 30);
    foo(arg0 / 31);
    var_a0_4 = arg0;
    if ((s32) var_a0_4 < 0) {
        var_a0_4 += 0x1F;
    }
    foo((u32) ((s32) var_a0_4 >> 5));
    foo(arg0 / 33);
    foo(arg0 / 100);
    foo(arg0 / 255);
    foo(arg0 / 360);
    foo(arg0 / 1000);
    foo(arg0 / 10000);
    foo(arg0 / 100000);
    foo(arg0 / 1000000);
    foo(arg0 / 10000000);
    foo(arg0 / 100000000);
    foo(arg0 / 1073741822);
    foo(arg0 / 1073741822);
    var_a0_5 = arg0;
    if ((s32) var_a0_5 < 0) {
        var_a0_5 += 0x3FFFFFFF;
    }
    foo((u32) ((s32) var_a0_5 >> 0x1E));
    foo(arg0 / 1073741824);
    foo(arg0 / 2147483648);
    foo(arg0 / 2147483645);
    foo(arg0 / 2147483648);
    foo(arg0 >> 0x1F);
    foo(arg0 / -2147483648);
    foo(arg0 / -2147483645);
    foo(arg0 / -10);
    foo(arg0 / -7);
    foo(arg0 / -5);
    var_a0_6 = arg0;
    if ((s32) var_a0_6 < 0) {
        var_a0_6 += 3;
    }
    foo((u32) -((s32) var_a0_6 >> 2));
    foo(arg0 / -3);
    foo((u32) -((s32) arg0 / 2));
    foo((u32) -(s32) arg0);
}

void func_00400F48(s32 arg0) {
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;

    foo(0U);
    foo(arg0 % 2);
    foo(arg0 % 3);
    var_a0 = arg0;
    if (arg0 < 0) {
        var_a0 = arg0 + 3;
    }
    foo(arg0 - ((var_a0 >> 2) * 4));
    foo(arg0 % 5);
    foo(arg0 % 6);
    foo(arg0 % 7);
    var_a0_2 = arg0;
    if (arg0 < 0) {
        var_a0_2 = arg0 + 7;
    }
    foo(arg0 - ((var_a0_2 >> 3) * 8));
    foo(arg0 % 9);
    foo(arg0 % 10);
    foo(arg0 % 11);
    foo(arg0 % 12);
    foo(arg0 % 13);
    foo(arg0 % 14);
    foo(arg0 % 15);
    var_a0_3 = arg0;
    if (arg0 < 0) {
        var_a0_3 = arg0 + 0xF;
    }
    foo(arg0 - ((var_a0_3 >> 4) * 0x10));
    foo(arg0 % 17);
    foo(arg0 % 18);
    foo(arg0 % 19);
    foo(arg0 % 20);
    foo(arg0 % 21);
    foo(arg0 % 22);
    foo(arg0 % 23);
    foo(arg0 % 24);
    foo(arg0 % 25);
    foo(arg0 % 26);
    foo(arg0 % 27);
    foo(arg0 % 28);
    foo(arg0 % 29);
    foo(arg0 % 30);
    foo(arg0 % 31);
    var_a0_4 = arg0;
    if (arg0 < 0) {
        var_a0_4 = arg0 + 0x1F;
    }
    foo(arg0 - ((var_a0_4 >> 5) << 5));
    foo(arg0 % 33);
    foo(arg0 % 100);
    foo(arg0 % 255);
    foo(arg0 % 360);
    foo(arg0 % 1000);
    foo(arg0 % 10000);
    foo(arg0 % 100000);
    foo(arg0 % 1000000);
    foo(arg0 % 10000000);
    foo(arg0 % 100000000);
    foo(arg0 % 1073741822);
    foo(arg0 - ((arg0 / 1073741822) * 0x3FFFFFFF));
    var_a0_5 = arg0;
    if (arg0 < 0) {
        var_a0_5 = arg0 + 0x3FFFFFFF;
    }
    foo(arg0 - ((var_a0_5 >> 0x1E) << 0x1E));
    foo(arg0 - ((arg0 / 1073741824) * 0x40000001));
    foo(arg0 - ((arg0 / 2147483648) * 0x7FFFFFFD));
    foo(arg0 - ((arg0 / 2147483645) * 0x7FFFFFFE));
    foo(arg0 - ((arg0 / 2147483648) * 0x7FFFFFFF));
    foo(arg0 & 0x7FFFFFFF);
    foo(arg0 - ((arg0 / 2147483648) * 0x7FFFFFFF));
    foo(arg0 - ((arg0 / 2147483645) * 0x7FFFFFFE));
    foo(arg0 % 10);
    foo(arg0 % 7);
    foo(arg0 % 5);
    var_a0_6 = arg0;
    if (arg0 < 0) {
        var_a0_6 = arg0 + 3;
    }
    foo(arg0 - ((var_a0_6 >> 2) * 4));
    foo(arg0 % 3);
    foo(arg0 % 2);
    foo(0U);
}

void func_00401AA0(u32 arg0) {
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_hi_3;
    s32 temp_hi_4;
    s32 temp_hi_5;
    s32 temp_hi_6;

    foo(arg0);
    foo(arg0 >> 1);
    foo(arg0 / 3);
    foo(arg0 >> 2);
    foo(arg0 / 5);
    foo(arg0 / 6);
    temp_hi = arg0 / 7;
    foo((u32) (temp_hi + ((u32) (arg0 - temp_hi) >> 1)) >> 2);
    foo(arg0 >> 3);
    foo(arg0 / 9);
    foo(arg0 / 10);
    foo(arg0 / 11);
    foo(arg0 / 12);
    foo(arg0 / 13);
    foo(arg0 / 14);
    foo(arg0 / 15);
    foo(arg0 >> 4);
    foo(arg0 / 17);
    foo(arg0 / 18);
    temp_hi_2 = MULTU_HI(arg0, 0xAF286BCB);
    foo((u32) (temp_hi_2 + ((u32) (arg0 - temp_hi_2) >> 1)) >> 4);
    foo(arg0 / 20);
    temp_hi_3 = MULTU_HI(arg0, 0x86186187);
    foo((u32) (temp_hi_3 + ((u32) (arg0 - temp_hi_3) >> 1)) >> 4);
    foo(arg0 / 22);
    foo(arg0 / 23);
    foo(arg0 / 24);
    foo(arg0 / 25);
    foo(arg0 / 26);
    temp_hi_4 = MULTU_HI(arg0, 0x2F684BDB);
    foo((u32) (temp_hi_4 + ((u32) (arg0 - temp_hi_4) >> 1)) >> 4);
    foo(arg0 / 28);
    foo(arg0 / 29);
    foo(arg0 / 30);
    temp_hi_5 = arg0 / 31;
    foo((u32) (temp_hi_5 + ((u32) (arg0 - temp_hi_5) >> 1)) >> 4);
    foo(arg0 >> 5);
    foo(arg0 / 33);
    foo(arg0 / 100);
    foo(arg0 / 255);
    foo(arg0 / 360);
    foo(arg0 / 1000);
    foo(arg0 / 10000);
    foo(arg0 / 100000);
    foo(arg0 / 1000000);
    foo(arg0 / 10000000);
    foo(arg0 / 100000000);
    foo(arg0 >> 0x1E);
    foo((u32) MULTU_HI(arg0, -3) >> 0x1E);
    foo(arg0 / 2147483645);
    temp_hi_6 = arg0 / 1431655765;
    foo((u32) (temp_hi_6 + ((u32) (arg0 - temp_hi_6) >> 1)) >> 0x1E);
    foo(arg0 >> 0x1F);
    foo((arg0 < 0x80000001U) ^ 1);
    foo((arg0 < 0xFFFFFFFEU) ^ 1);
    foo((arg0 < 0xFFFFFFFFU) ^ 1);
}

void func_00401FC4(u32 arg0) {
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_hi_3;
    s32 temp_hi_4;
    s32 temp_hi_5;
    s32 temp_hi_6;

    foo(arg0);
    foo(arg0 >> 1);
    foo(arg0 / 3);
    foo(arg0 >> 2);
    foo(arg0 / 5);
    foo(arg0 / 6);
    temp_hi = arg0 / 7;
    foo((u32) (temp_hi + ((u32) (arg0 - temp_hi) >> 1)) >> 2);
    foo(arg0 >> 3);
    foo(arg0 / 9);
    foo(arg0 / 10);
    foo(arg0 / 11);
    foo(arg0 / 12);
    foo(arg0 / 13);
    foo(arg0 / 14);
    foo(arg0 / 15);
    foo(arg0 >> 4);
    foo(arg0 / 17);
    foo(arg0 / 18);
    temp_hi_2 = MULTU_HI(arg0, 0xAF286BCB);
    foo((u32) (temp_hi_2 + ((u32) (arg0 - temp_hi_2) >> 1)) >> 4);
    foo(arg0 / 20);
    temp_hi_3 = MULTU_HI(arg0, 0x86186187);
    foo((u32) (temp_hi_3 + ((u32) (arg0 - temp_hi_3) >> 1)) >> 4);
    foo(arg0 / 22);
    foo(arg0 / 23);
    foo(arg0 / 24);
    foo(arg0 / 25);
    foo(arg0 / 26);
    temp_hi_4 = MULTU_HI(arg0, 0x2F684BDB);
    foo((u32) (temp_hi_4 + ((u32) (arg0 - temp_hi_4) >> 1)) >> 4);
    foo(arg0 / 28);
    foo(arg0 / 29);
    foo(arg0 / 30);
    temp_hi_5 = arg0 / 31;
    foo((u32) (temp_hi_5 + ((u32) (arg0 - temp_hi_5) >> 1)) >> 4);
    foo(arg0 >> 5);
    foo(arg0 / 33);
    foo(arg0 / 100);
    foo(arg0 / 255);
    foo(arg0 / 360);
    foo(arg0 / 1000);
    foo(arg0 / 10000);
    foo(arg0 / 100000);
    foo(arg0 / 1000000);
    foo(arg0 / 10000000);
    foo(arg0 / 100000000);
    foo(arg0 >> 0x1E);
    foo((u32) MULTU_HI(arg0, -3) >> 0x1E);
    foo(arg0 / 2147483645);
    temp_hi_6 = arg0 / 1431655765;
    foo((u32) (temp_hi_6 + ((u32) (arg0 - temp_hi_6) >> 1)) >> 0x1E);
    foo(arg0 >> 0x1F);
    foo((arg0 < 0x80000001U) ^ 1);
    foo((arg0 < 0xFFFFFFFEU) ^ 1);
    foo((arg0 < 0xFFFFFFFFU) ^ 1);
}
