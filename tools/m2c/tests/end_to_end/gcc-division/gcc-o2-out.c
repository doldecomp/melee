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
    func_00400090((u32) ((s32) ((s8) subroutine_arg4 + ((u32) (subroutine_arg4 << 0x18) >> 0x1F)) >> 1), /* extra? */ arg0);
    func_00400090((u32) (s8) (subroutine_arg4 / 3));
    func_00400090((u32) (s8) (subroutine_arg4 / 5));
    func_00400090((u32) (s8) (subroutine_arg4 / 7));
    func_00400090((u32) (s8) (subroutine_arg4 / 10));
    func_00400090((u32) (s8) (subroutine_arg4 / 100));
    func_00400090(subroutine_arg4 / 255);
    func_00400090((u32) (s8) ((s8) subroutine_arg4 - (((s32) ((s8) subroutine_arg4 + ((u32) (subroutine_arg4 << 0x18) >> 0x1F)) >> 1) * 2)));
    func_00400090((u32) (s8) (subroutine_arg4 % 3));
    func_00400090((u32) (s8) (subroutine_arg4 % 5));
    func_00400090((u32) (s8) (subroutine_arg4 % 7));
    func_00400090((u32) (s8) (subroutine_arg4 % 10));
    func_00400090((u32) (s8) (subroutine_arg4 % 100));
    func_00400090(subroutine_arg4 % 255);
}

void func_004003A8(s16 arg0) {
    func_00400090((u32) ((s32) ((s16) subroutine_arg4 + ((u32) (subroutine_arg4 << 0x10) >> 0x1F)) >> 1), /* extra? */ arg0);
    func_00400090((u32) (s16) (subroutine_arg4 / 3));
    func_00400090((u32) (s16) (subroutine_arg4 / 5));
    func_00400090((u32) (s16) (subroutine_arg4 / 7));
    func_00400090((u32) (s16) (subroutine_arg4 / 10));
    func_00400090((u32) (s16) (subroutine_arg4 / 100));
    func_00400090((u32) (s16) (subroutine_arg4 / 255));
    func_00400090((u32) (s16) (subroutine_arg4 / 360));
    func_00400090(subroutine_arg4 / 65534);
    func_00400090((u32) (s16) ((s16) subroutine_arg4 - (((s32) ((s16) subroutine_arg4 + ((u32) (subroutine_arg4 << 0x10) >> 0x1F)) >> 1) * 2)));
    func_00400090((u32) (s16) (subroutine_arg4 % 3));
    func_00400090((u32) (s16) (subroutine_arg4 % 5));
    func_00400090((u32) (s16) (subroutine_arg4 % 7));
    func_00400090((u32) (s16) (subroutine_arg4 % 10));
    func_00400090((u32) (s16) (subroutine_arg4 % 100));
    func_00400090((u32) (s16) (subroutine_arg4 % 255));
    func_00400090((u32) (s16) (subroutine_arg4 % 360));
    func_00400090(subroutine_arg4 % 65534);
}

void func_004007C0(u32 arg0) {
    u32 var_a0;
    u32 var_a0_2;
    u32 var_a0_3;
    u32 var_a0_4;
    u32 var_a0_5;
    u32 var_a0_6;

    func_00400090(arg0);
    func_00400090((u32) ((s32) (arg0 + (arg0 >> 0x1F)) >> 1));
    func_00400090(arg0 / 3);
    var_a0 = arg0;
    if ((s32) var_a0 < 0) {
        var_a0 += 3;
    }
    func_00400090((u32) ((s32) var_a0 >> 2));
    func_00400090(arg0 / 5);
    func_00400090(arg0 / 6);
    func_00400090(arg0 / 7);
    var_a0_2 = arg0;
    if ((s32) var_a0_2 < 0) {
        var_a0_2 += 7;
    }
    func_00400090((u32) ((s32) var_a0_2 >> 3));
    func_00400090(arg0 / 9);
    func_00400090(arg0 / 10);
    func_00400090(arg0 / 11);
    func_00400090(arg0 / 12);
    func_00400090(arg0 / 13);
    func_00400090(arg0 / 14);
    func_00400090(arg0 / 15);
    var_a0_3 = arg0;
    if ((s32) var_a0_3 < 0) {
        var_a0_3 += 0xF;
    }
    func_00400090((u32) ((s32) var_a0_3 >> 4));
    func_00400090(arg0 / 17);
    func_00400090(arg0 / 18);
    func_00400090(arg0 / 19);
    func_00400090(arg0 / 20);
    func_00400090(arg0 / 21);
    func_00400090(arg0 / 22);
    func_00400090(arg0 / 23);
    func_00400090(arg0 / 24);
    func_00400090(arg0 / 25);
    func_00400090(arg0 / 26);
    func_00400090(arg0 / 27);
    func_00400090(arg0 / 28);
    func_00400090(arg0 / 29);
    func_00400090(arg0 / 30);
    func_00400090(arg0 / 31);
    var_a0_4 = arg0;
    if ((s32) var_a0_4 < 0) {
        var_a0_4 += 0x1F;
    }
    func_00400090((u32) ((s32) var_a0_4 >> 5));
    func_00400090(arg0 / 33);
    func_00400090(arg0 / 100);
    func_00400090(arg0 / 255);
    func_00400090(arg0 / 360);
    func_00400090(arg0 / 1000);
    func_00400090(arg0 / 10000);
    func_00400090(arg0 / 100000);
    func_00400090(arg0 / 1000000);
    func_00400090(arg0 / 10000000);
    func_00400090(arg0 / 100000000);
    func_00400090(arg0 / 1073741822);
    func_00400090(arg0 / 1073741822);
    var_a0_5 = arg0;
    if ((s32) var_a0_5 < 0) {
        var_a0_5 += 0x3FFFFFFF;
    }
    func_00400090((u32) ((s32) var_a0_5 >> 0x1E));
    func_00400090(arg0 / 1073741824);
    func_00400090(arg0 / 2147483648);
    func_00400090(arg0 / 2147483645);
    func_00400090(arg0 / 2147483648);
    func_00400090(arg0 >> 0x1F);
    func_00400090(arg0 / -2147483648);
    func_00400090(arg0 / -2147483645);
    func_00400090(arg0 / -10);
    func_00400090(arg0 / -7);
    func_00400090(arg0 / -5);
    var_a0_6 = arg0;
    if ((s32) var_a0_6 < 0) {
        var_a0_6 += 3;
    }
    func_00400090((u32) -((s32) var_a0_6 >> 2));
    func_00400090(arg0 / -3);
    func_00400090((u32) -((s32) arg0 / 2));
    func_00400090((u32) -(s32) arg0);
}

void func_00400F48(s32 arg0) {
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_a0_6;

    func_00400090(0U);
    func_00400090(arg0 % 2);
    func_00400090(arg0 % 3);
    var_a0 = arg0;
    if (arg0 < 0) {
        var_a0 = arg0 + 3;
    }
    func_00400090(arg0 - ((var_a0 >> 2) * 4));
    func_00400090(arg0 % 5);
    func_00400090(arg0 % 6);
    func_00400090(arg0 % 7);
    var_a0_2 = arg0;
    if (arg0 < 0) {
        var_a0_2 = arg0 + 7;
    }
    func_00400090(arg0 - ((var_a0_2 >> 3) * 8));
    func_00400090(arg0 % 9);
    func_00400090(arg0 % 10);
    func_00400090(arg0 % 11);
    func_00400090(arg0 % 12);
    func_00400090(arg0 % 13);
    func_00400090(arg0 % 14);
    func_00400090(arg0 % 15);
    var_a0_3 = arg0;
    if (arg0 < 0) {
        var_a0_3 = arg0 + 0xF;
    }
    func_00400090(arg0 - ((var_a0_3 >> 4) * 0x10));
    func_00400090(arg0 % 17);
    func_00400090(arg0 % 18);
    func_00400090(arg0 % 19);
    func_00400090(arg0 % 20);
    func_00400090(arg0 % 21);
    func_00400090(arg0 % 22);
    func_00400090(arg0 % 23);
    func_00400090(arg0 % 24);
    func_00400090(arg0 % 25);
    func_00400090(arg0 % 26);
    func_00400090(arg0 % 27);
    func_00400090(arg0 % 28);
    func_00400090(arg0 % 29);
    func_00400090(arg0 % 30);
    func_00400090(arg0 % 31);
    var_a0_4 = arg0;
    if (arg0 < 0) {
        var_a0_4 = arg0 + 0x1F;
    }
    func_00400090(arg0 - ((var_a0_4 >> 5) << 5));
    func_00400090(arg0 % 33);
    func_00400090(arg0 % 100);
    func_00400090(arg0 % 255);
    func_00400090(arg0 % 360);
    func_00400090(arg0 % 1000);
    func_00400090(arg0 % 10000);
    func_00400090(arg0 % 100000);
    func_00400090(arg0 % 1000000);
    func_00400090(arg0 % 10000000);
    func_00400090(arg0 % 100000000);
    func_00400090(arg0 % 1073741822);
    func_00400090(arg0 - ((arg0 / 1073741822) * 0x3FFFFFFF));
    var_a0_5 = arg0;
    if (arg0 < 0) {
        var_a0_5 = arg0 + 0x3FFFFFFF;
    }
    func_00400090(arg0 - ((var_a0_5 >> 0x1E) << 0x1E));
    func_00400090(arg0 - ((arg0 / 1073741824) * 0x40000001));
    func_00400090(arg0 - ((arg0 / 2147483648) * 0x7FFFFFFD));
    func_00400090(arg0 - ((arg0 / 2147483645) * 0x7FFFFFFE));
    func_00400090(arg0 - ((arg0 / 2147483648) * 0x7FFFFFFF));
    func_00400090(arg0 & 0x7FFFFFFF);
    func_00400090(arg0 - ((arg0 / 2147483648) * 0x7FFFFFFF));
    func_00400090(arg0 - ((arg0 / 2147483645) * 0x7FFFFFFE));
    func_00400090(arg0 % 10);
    func_00400090(arg0 % 7);
    func_00400090(arg0 % 5);
    var_a0_6 = arg0;
    if (arg0 < 0) {
        var_a0_6 = arg0 + 3;
    }
    func_00400090(arg0 - ((var_a0_6 >> 2) * 4));
    func_00400090(arg0 % 3);
    func_00400090(arg0 % 2);
    func_00400090(0U);
}

void func_00401AA0(u32 arg0) {
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_hi_3;
    s32 temp_hi_4;
    s32 temp_hi_5;
    s32 temp_hi_6;

    func_00400090(arg0);
    func_00400090(arg0 >> 1);
    func_00400090(arg0 / 3);
    func_00400090(arg0 >> 2);
    func_00400090(arg0 / 5);
    func_00400090(arg0 / 6);
    temp_hi = arg0 / 7;
    func_00400090((u32) (temp_hi + ((u32) (arg0 - temp_hi) >> 1)) >> 2);
    func_00400090(arg0 >> 3);
    func_00400090(arg0 / 9);
    func_00400090(arg0 / 10);
    func_00400090(arg0 / 11);
    func_00400090(arg0 / 12);
    func_00400090(arg0 / 13);
    func_00400090(arg0 / 14);
    func_00400090(arg0 / 15);
    func_00400090(arg0 >> 4);
    func_00400090(arg0 / 17);
    func_00400090(arg0 / 18);
    temp_hi_2 = MULTU_HI(arg0, 0xAF286BCB);
    func_00400090((u32) (temp_hi_2 + ((u32) (arg0 - temp_hi_2) >> 1)) >> 4);
    func_00400090(arg0 / 20);
    temp_hi_3 = MULTU_HI(arg0, 0x86186187);
    func_00400090((u32) (temp_hi_3 + ((u32) (arg0 - temp_hi_3) >> 1)) >> 4);
    func_00400090(arg0 / 22);
    func_00400090(arg0 / 23);
    func_00400090(arg0 / 24);
    func_00400090(arg0 / 25);
    func_00400090(arg0 / 26);
    temp_hi_4 = MULTU_HI(arg0, 0x2F684BDB);
    func_00400090((u32) (temp_hi_4 + ((u32) (arg0 - temp_hi_4) >> 1)) >> 4);
    func_00400090(arg0 / 28);
    func_00400090(arg0 / 29);
    func_00400090(arg0 / 30);
    temp_hi_5 = arg0 / 31;
    func_00400090((u32) (temp_hi_5 + ((u32) (arg0 - temp_hi_5) >> 1)) >> 4);
    func_00400090(arg0 >> 5);
    func_00400090(arg0 / 33);
    func_00400090(arg0 / 100);
    func_00400090(arg0 / 255);
    func_00400090(arg0 / 360);
    func_00400090(arg0 / 1000);
    func_00400090(arg0 / 10000);
    func_00400090(arg0 / 100000);
    func_00400090(arg0 / 1000000);
    func_00400090(arg0 / 10000000);
    func_00400090(arg0 / 100000000);
    func_00400090(arg0 >> 0x1E);
    func_00400090((u32) MULTU_HI(arg0, -3) >> 0x1E);
    func_00400090(arg0 / 2147483645);
    temp_hi_6 = arg0 / 1431655765;
    func_00400090((u32) (temp_hi_6 + ((u32) (arg0 - temp_hi_6) >> 1)) >> 0x1E);
    func_00400090(arg0 >> 0x1F);
    func_00400090((arg0 < 0x80000001U) ^ 1);
    func_00400090((arg0 < 0xFFFFFFFEU) ^ 1);
    func_00400090((arg0 < 0xFFFFFFFFU) ^ 1);
}

void func_00401FC4(u32 arg0) {
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_hi_3;
    s32 temp_hi_4;
    s32 temp_hi_5;
    s32 temp_hi_6;

    func_00400090(arg0);
    func_00400090(arg0 >> 1);
    func_00400090(arg0 / 3);
    func_00400090(arg0 >> 2);
    func_00400090(arg0 / 5);
    func_00400090(arg0 / 6);
    temp_hi = arg0 / 7;
    func_00400090((u32) (temp_hi + ((u32) (arg0 - temp_hi) >> 1)) >> 2);
    func_00400090(arg0 >> 3);
    func_00400090(arg0 / 9);
    func_00400090(arg0 / 10);
    func_00400090(arg0 / 11);
    func_00400090(arg0 / 12);
    func_00400090(arg0 / 13);
    func_00400090(arg0 / 14);
    func_00400090(arg0 / 15);
    func_00400090(arg0 >> 4);
    func_00400090(arg0 / 17);
    func_00400090(arg0 / 18);
    temp_hi_2 = MULTU_HI(arg0, 0xAF286BCB);
    func_00400090((u32) (temp_hi_2 + ((u32) (arg0 - temp_hi_2) >> 1)) >> 4);
    func_00400090(arg0 / 20);
    temp_hi_3 = MULTU_HI(arg0, 0x86186187);
    func_00400090((u32) (temp_hi_3 + ((u32) (arg0 - temp_hi_3) >> 1)) >> 4);
    func_00400090(arg0 / 22);
    func_00400090(arg0 / 23);
    func_00400090(arg0 / 24);
    func_00400090(arg0 / 25);
    func_00400090(arg0 / 26);
    temp_hi_4 = MULTU_HI(arg0, 0x2F684BDB);
    func_00400090((u32) (temp_hi_4 + ((u32) (arg0 - temp_hi_4) >> 1)) >> 4);
    func_00400090(arg0 / 28);
    func_00400090(arg0 / 29);
    func_00400090(arg0 / 30);
    temp_hi_5 = arg0 / 31;
    func_00400090((u32) (temp_hi_5 + ((u32) (arg0 - temp_hi_5) >> 1)) >> 4);
    func_00400090(arg0 >> 5);
    func_00400090(arg0 / 33);
    func_00400090(arg0 / 100);
    func_00400090(arg0 / 255);
    func_00400090(arg0 / 360);
    func_00400090(arg0 / 1000);
    func_00400090(arg0 / 10000);
    func_00400090(arg0 / 100000);
    func_00400090(arg0 / 1000000);
    func_00400090(arg0 / 10000000);
    func_00400090(arg0 / 100000000);
    func_00400090(arg0 >> 0x1E);
    func_00400090((u32) MULTU_HI(arg0, -3) >> 0x1E);
    func_00400090(arg0 / 2147483645);
    temp_hi_6 = arg0 / 1431655765;
    func_00400090((u32) (temp_hi_6 + ((u32) (arg0 - temp_hi_6) >> 1)) >> 0x1E);
    func_00400090(arg0 >> 0x1F);
    func_00400090((arg0 < 0x80000001U) ^ 1);
    func_00400090((arg0 < 0xFFFFFFFEU) ^ 1);
    func_00400090((arg0 < 0xFFFFFFFFU) ^ 1);
}
