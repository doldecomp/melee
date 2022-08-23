struct A {
    char pad[4];
    void (*fptr)(void);
    short x, y, z, w;
};
void test(struct A *a, int b, short c) {
    a->x = 2;
    a->y = b;
    a->z = c;
    a->w = b + c;
}
