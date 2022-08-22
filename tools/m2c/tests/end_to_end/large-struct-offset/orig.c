struct A {
    char a[0x12345];
    int b;
};

int glob;

int *test(struct A *a) {
    glob = a->b;
    return &a->b;
}
