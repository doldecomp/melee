extern f32 D_410120;
extern f64 D_410128;
extern f64 D_410130;
extern ? *D_410138;

void test(void) {
    D_410120 = 1.2f;
    D_410128 = 13.0;
    D_410130 = 14000000000.0;
    D_410138 = "\"hello\"\n\x01\0world  /* comment */ #";
}
