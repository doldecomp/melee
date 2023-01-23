struct foo {
    int a: 1;
    unsigned int b: 1;
    int c: 5;
    unsigned int d: 5;
};

struct foo x;
struct foo y;

int test(char * ptr) {
    // Bitfield assignment
    x.a = ptr[0];
    x.b = ptr[1];
    x.c = ptr[2];
    x.d = ptr[3];

    // Flag setting/clearing
    y.a = 1;
    y.b = 0;
}
