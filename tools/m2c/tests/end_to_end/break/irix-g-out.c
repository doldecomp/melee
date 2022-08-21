extern ? D_4101D0;

void test(s32 arg0) {
    s32 sp4;
    s32 temp_t7;

    sp4 = 0;
    if (arg0 > 0) {
loop_1:
        D_4101D0.unk0 = 1;
        if (D_4101D0.unk4 == 2) {
            D_4101D0.unk8 = 3;
        } else {
            if (D_4101D0.unk8 == 2) {
                D_4101D0.unkC = 3;
                goto block_10;
            }
            if (D_4101D0.unk10 == 2) {
                D_4101D0.unk14 = 3;
            } else {
                if (D_4101D0.unk14 == 2) {
                    D_4101D0.unk18 = 3;
                } else {
                    D_4101D0.unkC = 4;
                }
block_10:
                temp_t7 = sp4 + 1;
                sp4 = temp_t7;
                if (temp_t7 < arg0) {
                    goto loop_1;
                }
            }
        }
    }
    D_4101D0.unk10 = 5;
}
