int test(int length) {
    int i = 0;

    while (i < length) {
        if (i == 5) {
            i *= 2;
        } else {
            i += 4;
        }
    }

    return i;
}
