void foo(int x);

void test(int x) {
    foo(x + 1);
    foo(x + 2);
}

void foo(int x) {}
