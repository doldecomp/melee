
volatile int global;

void test(int a, int b, int c) {
    global = (a == b);
    global = (a != c);
    global = (a < b);
    global = (a <= b);
    global = (a == 0);
    global = (b != 0);
}
