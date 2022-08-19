float a;
double b, c;
const char *d;

void test(void) {
    a = 1.2f;
    b = 13.0;
    c = 1.4e10;
    d = "\"hello\"\n\x01";
    "world  /* comment */ #";
}
