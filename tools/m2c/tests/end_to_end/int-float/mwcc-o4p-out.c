extern f32 globalf;
extern s32 globali;

f32 test(s32 arg0, s32 arg1, f32 arg8, f32 arg9) {
    globali = (s32) arg8;
    globalf = (f32) arg0;
    return (f32) (arg1 + 3) + (arg9 + 5.0f);
}
