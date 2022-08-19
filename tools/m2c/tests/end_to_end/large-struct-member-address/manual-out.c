? foo(s8 *);                                        /* extern */

void test(struct A *a) {
    foo(&a->b);
}
