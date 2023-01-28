extern f32 globalf;
extern s32 globali;

void test(s32 arg0, s32 arg1, s32 arg2, f32 arg8, f32 arg9, f32 argA) {
    globali = arg0 + (arg1 + arg2);
    globalf = argA + (arg8 + arg9);
}
