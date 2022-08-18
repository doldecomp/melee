int* foo(int* x, short* y, int* t) { return x; }

void test(int x, short* y, int z, char* r, short* s, int* t, long* u) {
    int* ptr = (void*) 0;
    for (;;) {
        ptr = foo(ptr, y, t);
    }
}
