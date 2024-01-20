s32 foo(s32);                                       /* static */

s32 test(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r0;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r31_2;
    s32 temp_r3;
    s32 temp_r3_2;

    temp_r0 = arg0 + arg1;
    temp_r31 = arg1 + arg2;
    temp_r29 = arg2 + arg3;
    if ((temp_r0 != 0) && (temp_r31 != 0) && (temp_r29 != 0)) {
        temp_r3 = foo(temp_r0 + arg0);
        if (temp_r3 > 0xA) {
            temp_r30 = foo(temp_r3 + arg1);
            temp_r31_2 = foo(temp_r31 + arg2);
            temp_r3_2 = foo(temp_r29 + arg3);
            if ((temp_r30 != 0) && (temp_r31_2 != 0) && (temp_r3_2 != 0)) {
                return 1;
            }
        }
    }
    return 0;
}
