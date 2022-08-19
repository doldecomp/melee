
int foo(int x);

void test(int x) {
    for (;;) {
        if (x > 2) {
            x = foo(x);
        }
    }
}

int foo(int x) { return x; }
