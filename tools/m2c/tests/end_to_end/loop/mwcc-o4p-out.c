void test(s32 arg0, s32 arg1) {
    s32 temp_r5;
    s32 var_ctr_2;
    s32 var_r6;
    s8 *var_r3;
    u32 var_ctr;
    void *temp_r5_2;

    var_r6 = 0;
    if (arg1 > 0) {
        temp_r5 = arg1 - 8;
        if (arg1 > 8) {
            var_ctr = (u32) (temp_r5 + 7) >> 3U;
            if (temp_r5 > 0) {
                do {
                    temp_r5_2 = arg0 + var_r6;
                    temp_r5_2->unk0 = 0;
                    var_r6 += 8;
                    temp_r5_2->unk1 = 0;
                    temp_r5_2->unk2 = 0;
                    temp_r5_2->unk3 = 0;
                    temp_r5_2->unk4 = 0;
                    temp_r5_2->unk5 = 0;
                    temp_r5_2->unk6 = 0;
                    temp_r5_2->unk7 = 0;
                    var_ctr -= 1;
                } while (var_ctr != 0);
            }
        }
        var_ctr_2 = arg1 - var_r6;
        var_r3 = arg0 + var_r6;
        if (var_r6 < arg1) {
            do {
                *var_r3 = 0;
                var_r3 += 1;
                var_ctr_2 -= 1;
            } while (var_ctr_2 != 0);
        }
    }
}
