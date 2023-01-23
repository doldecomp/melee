void test(s32 x, s16* y, s32 z, s8* r, s16* s, s32* t, s32* u) {
    s32* sp1C;

    sp1C = NULL;
loop_1:
    sp1C = foo(sp1C, y, t);
    goto loop_1;
}
