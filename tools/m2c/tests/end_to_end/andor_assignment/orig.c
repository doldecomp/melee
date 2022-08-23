int foo(int arg) {
    return arg + 1;
}

int test(int a, int b, int c, int d) {
    int var1;
    int var2;
    int ret;

    var1 = a + b;
    var2 = b + c;

    ret = 0;
    if (var1 || var2 || (var2 = foo(var2)) || (var1 = 2, d)) {
        ret = 1;
    } else if (a) {
        ret = -1;
    } else {
        ret = -2;
    }
    ret += c;

    if (var1 && var2 && ((var1 += var2), (var2 = foo(var1))) && d) {
        while (ret < 5) {
            ret += 1;
            ret *= 2;
        }
        ret += 5;
    }

    if (var1 && var2 && ((var1 += var2), (var2 = foo(var1))) && d) {
        while (ret < 5) {
            ret += 1;
            ret *= 2;
        }
        ret += 5;
    } else {
        ret += 6;
    }

    return ret;
}
