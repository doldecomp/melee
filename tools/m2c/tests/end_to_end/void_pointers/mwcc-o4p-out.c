s32 test(s32 *x) {
    s8 sp14;
    s32 *sp10;
    s32 spC;

    sp10 = x + 0x28;
    sp14 = (s8) x->unk0;
    spC = x->unk190;
    sp14 = (u8) sp14 + *func_00400090(&sp14);
    sp10 = func_00400090(&sp10);
    spC += *func_00400090(&spC);
    return (s8) (u8) sp14 + (*sp10 + spC);
}
