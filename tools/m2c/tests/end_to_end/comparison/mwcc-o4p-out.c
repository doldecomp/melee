extern s32 global;

void test(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r3;
    s32 temp_r5;

    temp_r5 = arg2 - arg0;
    global = arg1 == arg0;
    global = (temp_r5 - (temp_r5 - 1)) - !M2C_CARRY;
    global = ((s32) (u32) ~(arg1 ^ arg0) / 2147483648) & 1;
    temp_r3 = -arg1;
    global = (arg1 >> 0x1F) + ((u32) arg0 >> 0x1FU) + M2C_CARRY;
    global = -arg0 == 0;
    global = (temp_r3 - (temp_r3 - 1)) - !M2C_CARRY;
}
