float blahf(float x);
double blah(double x);

float test(float x) {
    x = blahf(x);
    x = (float) blah(x);
    return x;
}

float blahf(float x) { return x; }
double blah(double x) { return x; }
