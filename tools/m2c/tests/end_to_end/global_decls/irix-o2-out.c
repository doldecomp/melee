struct _m2c_stack_test {
    /* 0x00 */ char pad0[0x18];
};                                                  /* size = 0x18 */

M2C_UNK extern_fn(struct A *);                      /* extern */
M2C_UNK static_fn(struct A *);                      /* static */
extern f32 extern_float;
s32 static_int;
s32 static_bss_array[3];
struct A static_bss_A;

s32 test(void) {
    static_int *= 0x1C8;
    extern_float *= 456.0f;
    static_fn(&static_A);
    extern_fn(static_A_ptr);
    *static_bss_array = *static_array + *static_ro_array;
    return static_int;
}
