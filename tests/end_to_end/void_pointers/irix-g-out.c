s32 test(s32 *x) {
    s8 sp2F;
    s32 *sp28;
    s32 sp24;

    sp2F = (s8) x->unk0;
    sp28 = x + 0x28;
    sp24 = x->unk190;
    sp2F += *func_00400090(&sp2F);
    sp28 = func_00400090(&sp28);
    sp24 += *func_00400090(&sp24);
    return *sp28 + sp2F + sp24;
}
