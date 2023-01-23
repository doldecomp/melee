typedef unsigned short u16;
u16 foo(int x);

int glob;

int test(void) {
    unsigned short temp = foo(1);
    if (temp != 0) {
        return temp;
    }

    if (glob != 123)
        return foo(2);
    else
        return foo(3);
}

u16 foo(int x) { return 1; }
