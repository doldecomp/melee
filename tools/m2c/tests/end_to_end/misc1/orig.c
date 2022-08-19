int foo(int a, int b, int c, int d, int e);
int bar(int a, int b, int c);

struct B {
    int a, b;
};
struct A {
    int a;
    struct B b[1];
};
struct A *global;
char global2[100];

int test(int arg0, int arg1) {
    int x;
    int z;
    int y;

    x = global->b[arg0].a + 1;
    y = global->b[arg0].b;
    z = foo(1, 2, x, arg1, arg0);
    if (z == 0)
    {
        return 0;
    }
    bar(y, z, x);
    global2[arg0] = 5;
    return z;
}

int foo(int a, int b, int c, int d, int e) { return 1; }
int bar(int a, int b, int c) { return 1; }
