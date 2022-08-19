? bar(s32, s32, s32);                               /* static */
s32 foo(?, ?, s32, s32, s32);                       /* static */
extern s32 global;
static ? global2;

s32 test(s32 arg0, s32 arg1) {
    s32 temp_r29;
    s32 temp_r31;
    s32 temp_r3;
    void *temp_r5;

    temp_r5 = global + (arg0 * 8);
    temp_r29 = temp_r5->unk8;
    temp_r31 = temp_r5->unk4 + 1;
    temp_r3 = foo(1, 2, temp_r31, arg1, arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    bar(temp_r29, temp_r3, temp_r31);
    *(&global2 + arg0) = 5;
    return temp_r3;
}
