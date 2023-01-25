? func();                                           /* extern */
extern ? global_sym;
extern ? local_sym;

void test(u32 arg0) {
    s32 var_t2;

    var_t2 = 0;
    switch (arg0) {
    case 0:
        var_t2 = 1;
        break;
    case 1:
        var_t2 = 2;
        break;
    }
    local_sym.unk8 = var_t2;
    global_sym.unk8 = 0;
    func();
}
