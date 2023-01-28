
int foo(void);
void bar(int);

int global;

void test(void) {
    int x = foo();
    global = 1;
    bar(x);
}

int foo(void) { return 1; }
void bar(int x) {}
