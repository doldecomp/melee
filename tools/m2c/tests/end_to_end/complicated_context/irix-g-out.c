s16 test(struct SomeStruct *arg, u8 should, f64 union_arg_unk0, ? union_arg_unk4, ...) {
    f64 sp0;
    s8 temp_a1;

    temp_a1 = should & 0xFF;
    sp0 = union_arg_unk0;
    if (temp_a1 != 0) {
        globalf = arg->float_field;
        globali = arg->int_field;
        arg->data_field.char_innerfield = temp_a1;
    } else {
        arg->pointer_field = NULL;
        arg->data_field.double_innerfield = 0.0;
    }
    return arg->unk2;
}
