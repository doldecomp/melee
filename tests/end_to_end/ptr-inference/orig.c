struct A {
    int x;
    float y;
    char z;
};

void foo(signed** ptr1, struct A **ptr2) {}

void test(void) {
    signed* var1;
    struct A* var2;

    foo(&var1, &var2);
}
