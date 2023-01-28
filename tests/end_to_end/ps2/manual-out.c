? foo(void *, ? *, s32, s32);                       /* extern */

void test(s32 arg2, s32 arg3) {
    ? sp4;
    s32 temp_a2;

    M2C_ERROR(unknown instruction: sq $ra, 0x20($sp));
    temp_a2 = arg2 * 2;
    foo(sp, &sp4, temp_a2, arg3 + (temp_a2 * 2));
    M2C_ERROR(unknown instruction: lq $ra, 0x20($sp));
}
