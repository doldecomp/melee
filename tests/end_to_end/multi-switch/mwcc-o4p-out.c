extern s32 glob;

s32 test(s32 arg0) {
    s32 var_r3;

    var_r3 = arg0;
    if (var_r3 != 0x00000032) {
        if (var_r3 < 0x32) {
            switch (var_r3) { // switch 1; irregular
            case 1: // switch 1
                return var_r3 * var_r3;
            case 2: // switch 1
                var_r3 -= 1;
                // Duplicate return node #23. Try simplifying control flow for better match
                return var_r3 ^ (var_r3 + 1);
            case -50: // switch 1
                var_r3 -= 1;
                // Duplicate return node #31. Try simplifying control flow for better match
                glob = var_r3;
                return 2;
            default: // switch 1
                var_r3 *= 2;
                goto block_28;
            }
        } else {
            switch (var_r3) { // irregular
            case 0xC8:
            case 0x65:
            case 3: // switch 1
                return var_r3 ^ (var_r3 + 1);
            case 0x6B:
                var_r3 += 1;
                // Duplicate return node #31. Try simplifying control flow for better match
                glob = var_r3;
                return 2;
            case 0x66:
block_28:
                if ((s32) glob == 0) {
                    var_r3 -= 1;
                    var_r3 = var_r3 / 2;
                }
                // Duplicate return node #31. Try simplifying control flow for better match
                glob = var_r3;
                return 2;
            }
        }
    } else {
        var_r3 += 1;
        glob = var_r3;
        return 2;
    }
}
