void test(s32 arg0, void *arg1) {
    s32 var_t1;
    s32 var_t2;
    void *var_a1;

    var_a1 = arg1;
    var_t1 = 0;
    do {
        if (arg0 != 0) {
            var_t2 = var_a1->unk1;
        } else {
            var_t2 = var_a1->unk1;
        }
        var_t1 += var_t2;
        var_a1 = NULL;
    } while (var_t1 != 0);
}
