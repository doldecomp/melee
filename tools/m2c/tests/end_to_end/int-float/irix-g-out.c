extern s32 D_410130;
extern f32 D_410134;

f32 test(f32 arg0, s32 arg1, f32 arg2, s32 arg3) {
    D_410130 = (s32) arg0;
    D_410134 = (f32) arg1;
    arg2 += 5.0f;
    return (f32) (arg3 + 3) + arg2;
}
