? foo(s16);                                         /* extern */

void test(void) {
    SomeStruct *var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = &glob;
    do {
        if (*NULL == 0) {
            foo(var_s0->unk2004);
        }
        var_s1 += 1;
        var_s0 += 0xC;
    } while (var_s1 < 5);
}
