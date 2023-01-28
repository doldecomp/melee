int test(int length) {
    int i = 0;
    int k = 0;

    while (i < length) {
        int j = 0;
        while (j < length) {
            k += (i * j);
            j++;
        }
        i++;
    }

    return k;
}
