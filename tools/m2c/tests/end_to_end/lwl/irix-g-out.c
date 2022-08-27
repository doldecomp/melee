? func_004000B0(? *);                               /* static */
extern ? D_400170;
extern ? D_400178;
extern ? D_410180;
extern ? D_410181;
extern ? D_410189;
extern ? D_410190;
extern s32 D_410198;

void test(void) {
    ? sp18;

    sp18.unk0 = (s32) D_400170.unk0;
    sp18.unk4 = (first 3 bytes) D_400170.unk4;
    func_004000B0(&sp18);
    D_410181 = (unaligned s32) D_410189;
    D_410190.unk0 = (unaligned s32) D_410180.unk0;
    D_410190.unk4 = (u8) D_410180.unk4;
    D_410198 = (unaligned s32) D_400178;
}
