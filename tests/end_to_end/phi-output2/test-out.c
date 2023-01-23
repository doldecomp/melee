s32 test(s32 arg0) {
    s32 temp_v0;
    s32 var_a3;
    void *temp_a2;
    s32 phi_v0;

    var_a3 = 0;
    do {
        temp_a2 = var_a3 + 1;
        temp_v0 = temp_a2->unk4;
        var_a3 = *NULL;
        phi_v0 = temp_v0;
        if (arg0 != 0) {
            phi_v0 = temp_a2->unk4;
        }
    } while (arg0 != 0);
    return phi_v0;
}
