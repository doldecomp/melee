struct A {
    int x;
};

int test(struct A *a, struct A *b) {
    switch (a->x) {
        case 8:
            b->x += a->x;
            break;
        case 15:
            b->x -= a->x;
            break;
    }
    return 0;
}
