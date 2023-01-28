struct A {
    char pad[4];
    void (*fptr)(void);
};
int foo(struct A *a, void *b);
