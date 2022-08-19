Blah *test(Blah *b, Blah *b2) {
    s32 sp4;

    sp4 = b->a + b->b;
    b->b = sp4;
    b2->a = b->a;
    b2->b = b->b;
    return b;
}
