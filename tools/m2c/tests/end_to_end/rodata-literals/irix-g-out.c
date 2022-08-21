extern f32 D_410130;
extern f64 D_410138;
extern f64 D_410140;
extern ? *D_410148;

void test(void) {
    D_410130 = 1.2f;
    D_410138 = 13.0;
    D_410140 = 14000000000.0;
    D_410148 = "\"hello\"\n\x01\0world  /* comment */ #";
}
