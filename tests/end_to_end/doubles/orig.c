double global;

double test(double a, int b, double c) {
    double d = a * b + a / c, e;
    d -= 7;
    if (d < c || d == c || d > 9.0) {
        e = 5.0;
    } else {
        e = 6.0f;
    }
    global = e;
    return e;
}
