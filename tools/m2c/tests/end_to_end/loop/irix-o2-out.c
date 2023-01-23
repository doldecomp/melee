void test(s8 *arg0, s32 arg1) {
    s32 temp_a3;
    s32 var_v0;
    s8 *var_v1;
    void *var_v1_2;

    var_v0 = 0;
    if (arg1 > 0) {
        temp_a3 = arg1 & 3;
        if (temp_a3 != 0) {
            var_v1 = arg0;
            do {
                var_v0 += 1;
                *var_v1 = 0;
                var_v1 += 1;
            } while (temp_a3 != var_v0);
            if (var_v0 != arg1) {
                goto block_5;
            }
        } else {
block_5:
            var_v1_2 = arg0 + var_v0;
            do {
                var_v0 += 4;
                var_v1_2->unk1 = 0;
                var_v1_2->unk2 = 0;
                var_v1_2->unk3 = 0;
                var_v1_2 += 4;
                var_v1_2->unk-4 = 0;
            } while (var_v0 != arg1);
        }
    }
}
