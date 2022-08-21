extern s32 D_410150;

s32 test(s32 arg0) {
    s32 var_a0;
    s32 var_a0_2;

    var_a0 = arg0;
    switch (var_a0) {
    case 1:
        return var_a0 * var_a0;
    case 2:
        var_a0 -= 1;
        /* fallthrough */
    case 3:
        return var_a0 * 2;
    case 4:
        var_a0_2 = var_a0 + 1;
        D_410150 = var_a0_2;
        return 2;
    case 6:
    case 7:
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
