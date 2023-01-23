int test(int (*fn)(int), int x) {
    return fn(x) + 1;
}
