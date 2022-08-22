s32 test(s32 arg0) {
    s32 sp4;

    sp4 = 0;
    if (sp4 < arg0) {
        do {
            if (sp4 == 5) {
                sp4 *= 2;
            } else {
                sp4 += 4;
            }
        } while (sp4 < arg0);
    }
    return sp4;
}
