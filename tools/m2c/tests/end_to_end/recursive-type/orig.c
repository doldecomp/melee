void foo(void **a, void **b) {
    *a = *b;
}

void test(void *a, void *b) {
    a = &a;
    b = &b;

    foo(a, b);
    a = b;
    foo(a, b);
}
