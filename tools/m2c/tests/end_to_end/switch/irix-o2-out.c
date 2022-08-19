extern s32 D_410150;

s32 test(s32 arg0) {
    s32 var_a0;
    s32 var_a0_2;

    var_a0 = arg0;
    switch (var_a0) {
    case 0x1:
        return var_a0 * var_a0;
    case 0x2:
        var_a0 -= 1;
        /* fallthrough */
    case 0x3:
        return var_a0 * 2;
    case 0x4:
        var_a0_2 = var_a0 + 1;
        D_410150 = var_a0_2;
        return 2;
    case 0x6:
    case 0x7:
        var_a0_2 = var_a0 * 2;
        /* Duplicate return node #8. Try simplifying control flow for better match */
        D_410150 = var_a0_2;
        return 2;
    default:
        var_a0_2 = var_a0 / 2;
        /* Duplicate return node #8. Try simplifying control flow for better match */
        D_410150 = var_a0_2;
        return 2;
    }
}
