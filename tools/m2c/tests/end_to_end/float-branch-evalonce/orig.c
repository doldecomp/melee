float x;
void test(void) {
    float y = x;
    x = 5;
    if (y < 0) {
        x = 6;
    }

    y = x;
    x = 3;
    if (!(y < 0)) {
        x = 7;
    }
}
