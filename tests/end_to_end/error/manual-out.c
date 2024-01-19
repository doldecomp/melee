s32 test(s32 arg0) {
    s32 temp_t1;

    M2C_BREAK();
    M2C_BREAK(2);
    M2C_SYNC();
    M2C_TRAP_IF(arg0 == 0);
    M2C_TRAP_IF(arg0 != 0);
    M2C_TRAP_IF(arg0 > 0);
    M2C_TRAP_IF((u32) arg0 > 0U);
    M2C_TRAP_IF(arg0 <= 0);
    M2C_TRAP_IF((u32) arg0 <= 0U);
    M2C_TRAP_IF(arg0 == 1);
    M2C_TRAP_IF(arg0 != 2);
    M2C_TRAP_IF(arg0 < 3);
    M2C_TRAP_IF((u32) arg0 < 4U);
    M2C_TRAP_IF(arg0 >= 5);
    M2C_TRAP_IF((u32) arg0 >= 6U);
    M2C_ERROR(/* unknown instruction: badinstr $t0, $t0 */);
    temp_t1 = M2C_ERROR(/* unknown instruction: badinstr2 $t1, $t1 */);
    *NULL = temp_t1 << temp_t1;
    *NULL = (s32) (M2C_ERROR(/* Read from unset register $v1 */) + 2);
    return M2C_ERROR(/* unknown instruction: badinstr3 $v0, $t2 */);
}
