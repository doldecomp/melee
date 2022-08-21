volatile int glob;

int test(int x) {
    int old;
    while (x == 5) {
        glob = x;
        x++;
        glob = x;
        x++;
        glob = x;
        x++;
        glob = x;
        old = x;
        x++;
        glob = x;
        glob = x++;
        glob = x++;
        glob = old;
    }
    return old;
}
