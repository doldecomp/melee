? func_004000B0(? *);                               /* static */
extern ? D_400150;
extern ? D_400158;
extern ? D_410160;
extern ? D_410161;
extern ? D_410169;
extern ? D_410170;
extern s32 D_410178;

void test(void) {
    ? sp18;

    sp18.unk0 = (s32) D_400150.unk0;
    sp18.unk4 = (first 3 bytes) D_400150.unk4;
    func_004000B0(&sp18);
    D_410161 = (unaligned s32) D_410169;
    D_410170.unk0 = (unaligned s32) D_410160.unk0;
    D_410170.unk4 = (u8) D_410160.unk4;
    D_410178 = (unaligned s32) D_400158;
}
