float test(unsigned int y) {
    double ret = 1.0;
    unsigned int i;

    for (i = y; i != 0; i--) {
        ret *= i;
    }

    return ret;
}
