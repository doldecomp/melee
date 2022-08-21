int test(int a, int b, int c, int d) {
    if ((a || b) && (c || d)) {
        return a + b;
    }
    return c + d;
}
