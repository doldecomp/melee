struct _m2c_stack_test {
    /* 0x00 */ char pad0[0x18];
};                                                  /* size = 0x18 */

M2C_UNK extern_fn(struct A *);                      /* extern */
M2C_UNK static_fn(struct A *);                      /* static */
extern f32 extern_float;
struct A static_A = {
    1,
    { 1, 2, 3, 4, 5 },
    {
        {
            { 1.0f, 2.0f, 3.0f, 4.0f },
            { 5.0f, 6.0f, 7.0f, 8.0f },
            { 9.0f, 0.0f, 1.0f, 2.0f },
        },
        {
            { 1.5f, 2.5f, 3.5f, 4.5f },
            { 5.5f, 6.5f, 7.5f, 8.5f },
            { 9.5f, 0.5f, 1.5f, 2.5f },
        },
    },
    { NULL, &static_int },
    &static_bss_A,
};
struct A *static_A_ptr = &static_A;
s32 static_array[3] = { 2, 4, 6 };
s16 unused_static_array[3] = { -8, 0x000A, 0x000C };
s32 static_int;
s32 static_bss_array[3];
struct A static_bss_A;
s32 static_ro_array[3] = { 7, 8, -9 };              /* const */
u32 unused_static_ro_array[3] = { 0x0000000A, 0xFFFFFFF5, 0x0000000C }; /* const */

s32 test(void) {
    static_int *= 0x1C8;
    extern_float *= 456.0f;
    static_fn(&static_A);
    extern_fn(static_A_ptr);
    *static_bss_array = *static_array + *static_ro_array;
    return static_int;
}
