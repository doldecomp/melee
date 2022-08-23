struct Blah {
    int a, b;
};

typedef struct Blah Blah;

struct Blah *test(struct Blah *b, Blah *b2) {
    int c = b->a + b->b;
    b->b = c;
    *b2 = *b;
    return b;
}
