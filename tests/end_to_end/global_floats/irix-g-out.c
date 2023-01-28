extern ? D_400160;
extern ? D_40016C;
extern f32 D_400180;
extern ? D_410190;
extern ? D_4101A0;
extern ? D_4101B0;

f32 test(s32 arg0) {
    *(&D_4101B0 + (arg0 * 4)) = *(&D_400160 + (arg0 * 4)) + *(&D_4101A0 + (arg0 * 4));
    D_410190.unk190 = (f32) (D_410190.unk0 * ((*(&D_4101B0 + (arg0 * 4)) * D_400180) + *(&D_40016C + (arg0 * 4))));
    return D_410190.unk0 / *(&D_4101B0 + (arg0 * 4));
}
