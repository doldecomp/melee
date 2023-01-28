struct B {
    int more_padding;
    int x;
};
struct A {
    int padding;
    int *array[10];
    struct B array2[10];
    int y;
};

volatile int glob;

void test(struct A *a, int b) {
    glob = (int)a->array[b];
    glob = (int)&a->array[b];
    glob = a->array2[b].x;
    glob = (int)&a->array2[b].x;
    glob = a[b].y;
    glob = a->array2[3].x;
    glob = (int)&a->array2[3].x;
}
