s32 test(s32 arg0) {
    s32 spC;
    s32 sp8;
    s32 sp4;

    spC = 0;
    sp8 = 0;
    if (spC < arg0) {
        do {
            sp4 = 0;
            if (sp4 < arg0) {
                do {
                    sp8 += spC * sp4;
                    sp4 += 1;
                } while (sp4 < arg0);
            }
            spC += 1;
        } while (spC < arg0);
    }
    return sp8;
}
