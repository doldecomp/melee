extern s32 D_410210;

s32 test(s32 arg0) {
    s32 var_a0;

    var_a0 = arg0;
    switch (var_a0) { // irregular
    case 1:
        return var_a0 * var_a0;
    case 2:
        var_a0 -= 1;
        // fallthrough
    case 3:
    case 101:
    case 200:
        return (var_a0 + 1) ^ var_a0;
    case 107:
        var_a0 += 1;
        D_410210 = var_a0;
        return 2;
    case -50:
        var_a0 -= 1;
        // Duplicate return node #24. Try simplifying control flow for better match
        D_410210 = var_a0;
        return 2;
    case 50:
        var_a0 += 1;
        // Duplicate return node #24. Try simplifying control flow for better match
        D_410210 = var_a0;
        return 2;
    case 6:
    case 7:
        var_a0 *= 2;
        // fallthrough
    case 102:
        if (D_410210 == 0) {
        case 103:
        case 104:
        case 105:
        case 106:
            var_a0 -= 1;
        default:
            var_a0 = var_a0 / 2;
        }
        // Duplicate return node #24. Try simplifying control flow for better match
        D_410210 = var_a0;
        return 2;
    }
}
