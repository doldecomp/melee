void foo(int);
int test(int x) {
    goto label;

    while (x < 4) {
        foo(x);
        x++;
label:
        foo(x);
        x *= 2;
    }

    return x;
}

void foo(int x) {}
