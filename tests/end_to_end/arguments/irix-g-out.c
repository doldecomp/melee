extern s32 D_4100F0;
extern f32 D_4100F4;

void test(f32 arg0, s32 arg1, f32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    D_4100F4 = arg0 + arg2 + arg4;
    D_4100F0 = arg1 + arg3 + arg5;
}
