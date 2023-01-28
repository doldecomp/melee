static ? globals;

void test(s32 arg0) {
    s32 var_ctr;

    var_ctr = arg0;
    if (arg0 > 0) {
loop_1:
        globals.unk0 = 1;
        if ((s32) globals.unk4 == 2) {
            globals.unk8 = 3;
        } else {
            if ((s32) globals.unk8 == 2) {
                globals.unkC = 3;
                goto block_10;
            }
            if ((s32) globals.unk10 == 2) {
                globals.unk14 = 3;
            } else {
                if ((s32) globals.unk14 == 2) {
                    globals.unk18 = 3;
                } else {
                    globals.unkC = 4;
                }
block_10:
                var_ctr -= 1;
                if (var_ctr != 0) {
                    goto loop_1;
                }
            }
        }
    }
    globals.unk10 = 5;
}
