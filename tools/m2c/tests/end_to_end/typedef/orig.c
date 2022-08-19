typedef int int_t;

int_t foo(int x, int_t *y) {
    return x + *y;
}

int_t test(int x, int_t *y) {
    return foo(x, &x) + foo(x, y) + foo(*y, y);
}
