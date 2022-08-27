void *func_00400090(void * x) {
    return x;
}

int test(int *x) {
    char a;
    int *b;
    int c;

    a = x[0];
    b = &x[10];
    c = x[100];

    a += *(char *) func_00400090(&a);
    b = func_00400090(&b);
    c += *(int *) func_00400090(&c);

    return a + *b + c;
}
