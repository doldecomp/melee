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
        if (x == 9) {
            foo(5);
        }
        foo(6);
    }
}

void foo(int x) {}
