void foo(int x);
void test(int x) {
    if (x == 7) {
        foo(1);
    } else {
        foo(2);
        if (x == 8) {
            foo(3);
        }
        foo(4);
    }
}

void foo(int x) {}
