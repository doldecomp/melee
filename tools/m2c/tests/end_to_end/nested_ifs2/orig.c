void foo(int x);
void test(int x) {
    if (x == 7) {
        foo(1);
        if (x == 8) {
            foo(2);
        }
        foo(3);
    } else {
        foo(4);
    }
}

void foo(int x) {}
