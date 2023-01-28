extern s32 D_410210;

s32 test(s32 arg0) {
    s32 var_a0;

    var_a0 = arg0;
    if (var_a0 >= 0x33) {
        if (var_a0 >= 0x6C) {
            if (var_a0 != 0x000000C8) {
                goto block_23;
            }
            // Duplicate return node #16. Try simplifying control flow for better match
            return (var_a0 + 1) ^ var_a0;
        }
        switch (var_a0) { // switch 1
        case 0x6B: // switch 1
            var_a0 += 1;
            // Duplicate return node #24. Try simplifying control flow for better match
            D_410210 = var_a0;
            return 2;
        }
    } else {
        if (var_a0 >= 8) {
            if (var_a0 != 0x00000032) {
                goto block_23;
            }
            var_a0 += 1;
            // Duplicate return node #24. Try simplifying control flow for better match
            D_410210 = var_a0;
            return 2;
        }
        if (var_a0 >= -0x31) {
            switch (var_a0) { // switch 2
            case 1: // switch 2
                return var_a0 * var_a0;
            case 2: // switch 2
                var_a0 -= 1;
                // fallthrough
            case 3: // switch 2
            case 0x65: // switch 1
                return (var_a0 + 1) ^ var_a0;
            case 6: // switch 2
            case 7: // switch 2
                var_a0 *= 2;
            case 0x66: // switch 1
                if (D_410210 == 0) {
                case 0x67: // switch 1
                case 0x68: // switch 1
                case 0x69: // switch 1
                case 0x6A: // switch 1
                    var_a0 -= 1;
                    goto block_23;
                }
                // Duplicate return node #24. Try simplifying control flow for better match
                D_410210 = var_a0;
                return 2;
            }
        } else {
            if (var_a0 != -0x00000032) {
            default: // switch 2
            default: // switch 1
block_23:
                var_a0 = var_a0 / 2;
            } else {
                var_a0 -= 1;
            }
            D_410210 = var_a0;
            return 2;
        }
    }
}
