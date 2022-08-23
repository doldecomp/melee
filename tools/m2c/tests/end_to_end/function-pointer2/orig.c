int (*volatile glob)(float);
int (*volatile glob2)(float);
int foo(float x);
int bar(float x);

void test(void) {
    glob = foo;
    glob = bar;
    glob2 = foo;
    glob2 = bar;
}

int foo(float x) { return 1; }
int bar(float x) { return 2; }
