static ? a;
static ? b;

void test(s32 arg0, s32 arg1) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r3;
    s32 temp_r5;
    s32 var_ctr;
    s32 var_ctr_2;
    void *var_r4;
    void *var_r5;
    void *var_r6;
    void *var_r7;

    var_r7 = &a - 4;
    var_r6 = &b - 4;
    var_ctr = 0x32;
    do {
        temp_r5 = var_r6->unk4;
        temp_r0 = var_r6->unk8;
        var_r6 += 8;
        var_r7->unk4 = temp_r5;
        var_r7 += 8;
        var_r7->unk8 = temp_r0;
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_r5 = arg0 - 4;
    var_r4 = arg1 - 4;
    var_ctr_2 = 0xC;
    do {
        temp_r3 = var_r4->unk4;
        temp_r0_2 = var_r4->unk8;
        var_r4 += 8;
        var_r5->unk4 = temp_r3;
        var_r5 += 8;
        var_r5->unk8 = temp_r0_2;
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    var_r5->unk4 = (s32) var_r4->unk4;
}
