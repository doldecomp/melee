int globali;
float globalf;

float test(float f1, int i1, float f2, unsigned i2) {
    globali = (int)f1;
    globalf = (float)i1;
    i2 += 3;
    f2 += 5.0;
    f2 += 0.0;
    f2 += 0.0f;
    f2 += 5.3;
    return (float)i2 + f2;
}
