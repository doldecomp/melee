s32 func_00400090(s32, s8 *, s32);                  /* static */
s32 func_004000B0(s32, s8 *, s32);                  /* static */

s32 test(s32 arg0, s32 arg1) {
    ? sp120000;
    s8 sp20;
    s32 sp1C;
    s8 *temp_t3;

    sp120000.unk3478 = arg0;
    sp120000.unk347C = arg1;
    sp1C = 0x123456;
    sp1C = func_00400090(sp120000.unk3478, &sp20, sp1C);
    if (sp1C < 0) {
        return sp1C;
    }
    sp20 ^= 0x55;
    temp_t3 = &(&sp20)[sp1C];
    temp_t3->unk-1 = (s8) (temp_t3->unk-1 ^ 0x55);
    return func_004000B0(sp120000.unk347C, &sp20, sp1C);
}
