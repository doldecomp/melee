int foo(int arg) {
    return arg + 1;
}

int test(int a, int b, int c, int d) {
    int var1;
    int var2;
    int var3;

    var1 = a + b;
    var2 = b + c;
    var3 = c + d;

    if (var1 && var2 && var3) {
        var1 = foo(var1 + a);
        if (var1 > 10) {
            var1 = foo(var1 + b);
            var2 = foo(var2 + c);
            var3 = foo(var3 + d);
            if (var1 && var2 && var3) {
                return 1;
            }
        }
    }
    return 0;
}
