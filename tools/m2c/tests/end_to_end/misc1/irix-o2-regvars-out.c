void *func_00400140(s32, s32, s32, s32, s32);       /* static */
? func_00400158(s32, void *, s32);                  /* static */
extern ? D_410170;
extern ? D_410178;

void *test(s32 arg0, s32 arg1) {
    s32 sp2C;
    void *sp28;
    s32 sp24;
    ? *var_t6;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_t1;
    s32 var_t7;
    s32 var_t8;
    s32 var_t9;
    void *temp_v0;
    void *var_a1;
    void *var_v0;

    var_t6 = &D_410170;
    var_t6 = D_410170;
    var_t8 = arg0 * 8;
    var_v0 = var_t6 + var_t8;
    var_a2 = var_v0->unk4;
    var_t9 = var_v0->unk8;
    var_a3 = arg1;
    var_t7 = arg0;
    var_a2 += 1;
    sp2C = var_a2;
    var_a0 = 1;
    var_a1 = (void *)2;
    sp24 = var_t9;
    temp_v0 = func_00400140(1, 2, var_a2, var_a3, var_t7);
    var_a1 = temp_v0;
    if (temp_v0 == NULL) {
        var_v0 = NULL;
        return NULL;
    }
    var_a0 = sp24;
    sp28 = var_a1;
    func_00400158(var_a0, var_a1, var_a2);
    var_t1 = arg0;
    var_t0 = 5;
    var_v0 = sp28;
    *(&D_410178 + var_t1) = 5;
    return var_v0;
}
